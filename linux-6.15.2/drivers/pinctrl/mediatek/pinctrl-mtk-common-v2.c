// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (C) 2018 MediaTek Inc.
 *
 * Author: Sean Wang <sean.wang@mediatek.com>
 *
 */

#include <dt-bindings/pinctrl/mt65xx.h>
#include <linux/device.h>
#include <linux/err.h>
#include <linux/gpio/driver.h>
#include <linux/platform_device.h>
#include <linux/io.h>
#include <linux/module.h>
#include <linux/of_address.h>
#include <linux/of_irq.h>

#include "mtk-eint.h"
#include "pinctrl-mtk-common-v2.h"

/**
 * struct mtk_drive_desc - the structure that holds the information
 *			    of the driving current
 * @min:	the minimum current of this group
 * @max:	the maximum current of this group
 * @step:	the step current of this group
 * @scal:	the weight factor
 *
 * formula: output = ((input) / step - 1) * scal
 */
struct mtk_drive_desc {
	u8 min;
	u8 max;
	u8 step;
	u8 scal;
};

/* The groups of drive strength */
static const struct mtk_drive_desc mtk_drive[] = {
	[DRV_GRP0] = { 4, 16, 4, 1 },
	[DRV_GRP1] = { 4, 16, 4, 2 },
	[DRV_GRP2] = { 2, 8, 2, 1 },
	[DRV_GRP3] = { 2, 8, 2, 2 },
	[DRV_GRP4] = { 2, 16, 2, 1 },
};

static void mtk_w32(struct mtk_pinctrl *pctl, u8 i, u32 reg, u32 val)
{
	writel_relaxed(val, pctl->base[i] + reg);
}

static u32 mtk_r32(struct mtk_pinctrl *pctl, u8 i, u32 reg)
{
	return readl_relaxed(pctl->base[i] + reg);
}

void mtk_rmw(struct mtk_pinctrl *pctl, u8 i, u32 reg, u32 mask, u32 set)
{
	u32 val;
	unsigned long flags;

	spin_lock_irqsave(&pctl->lock, flags);

	val = mtk_r32(pctl, i, reg);
	val &= ~mask;
	val |= set;
	mtk_w32(pctl, i, reg, val);

	spin_unlock_irqrestore(&pctl->lock, flags);
}

static int mtk_hw_pin_field_lookup(struct mtk_pinctrl *hw,
				   const struct mtk_pin_desc *desc,
				   int field, struct mtk_pin_field *pfd)
{
	const struct mtk_pin_field_calc *c;
	const struct mtk_pin_reg_calc *rc;
	int start = 0, end, check;
	bool found = false;
	u32 bits;

	if (hw->soc->reg_cal && hw->soc->reg_cal[field].range) {
		rc = &hw->soc->reg_cal[field];
	} else {
		dev_dbg(hw->dev,
			"Not support field %d for this soc\n", field);
		return -ENOTSUPP;
	}

	end = rc->nranges - 1;

	while (start <= end) {
		check = (start + end) >> 1;
		if (desc->number >= rc->range[check].s_pin
		 && desc->number <= rc->range[check].e_pin) {
			found = true;
			break;
		} else if (start == end)
			break;
		else if (desc->number < rc->range[check].s_pin)
			end = check - 1;
		else
			start = check + 1;
	}

	if (!found) {
		dev_dbg(hw->dev, "Not support field %d for pin = %d (%s)\n",
			field, desc->number, desc->name);
		return -ENOTSUPP;
	}

	c = rc->range + check;

	if (c->i_base > hw->nbase - 1) {
		dev_err(hw->dev,
			"Invalid base for field %d for pin = %d (%s)\n",
			field, desc->number, desc->name);
		return -EINVAL;
	}

	/* Calculated bits as the overall offset the pin is located at,
	 * if c->fixed is held, that determines the all the pins in the
	 * range use the same field with the s_pin.
	 */
	bits = c->fixed ? c->s_bit : c->s_bit +
	       (desc->number - c->s_pin) * (c->x_bits);

	/* Fill pfd from bits. For example 32-bit register applied is assumed
	 * when c->sz_reg is equal to 32.
	 */
	pfd->index = c->i_base;
	pfd->offset = c->s_addr + c->x_addrs * (bits / c->sz_reg);
	pfd->bitpos = bits % c->sz_reg;
	pfd->mask = (1 << c->x_bits) - 1;

	/* pfd->next is used for indicating that bit wrapping-around happens
	 * which requires the manipulation for bit 0 starting in the next
	 * register to form the complete field read/write.
	 */
	pfd->next = pfd->bitpos + c->x_bits > c->sz_reg ? c->x_addrs : 0;

	return 0;
}

static int mtk_hw_pin_field_get(struct mtk_pinctrl *hw,
				const struct mtk_pin_desc *desc,
				int field, struct mtk_pin_field *pfd)
{
	if (field < 0 || field >= PINCTRL_PIN_REG_MAX) {
		dev_err(hw->dev, "Invalid Field %d\n", field);
		return -EINVAL;
	}

	return mtk_hw_pin_field_lookup(hw, desc, field, pfd);
}

static void mtk_hw_bits_part(struct mtk_pin_field *pf, int *h, int *l)
{
	*l = 32 - pf->bitpos;
	*h = get_count_order(pf->mask) - *l;
}

static void mtk_hw_write_cross_field(struct mtk_pinctrl *hw,
				     struct mtk_pin_field *pf, int value)
{
	int nbits_l, nbits_h;

	mtk_hw_bits_part(pf, &nbits_h, &nbits_l);

	mtk_rmw(hw, pf->index, pf->offset, pf->mask << pf->bitpos,
		(value & pf->mask) << pf->bitpos);

	mtk_rmw(hw, pf->index, pf->offset + pf->next, BIT(nbits_h) - 1,
		(value & pf->mask) >> nbits_l);
}

static void mtk_hw_read_cross_field(struct mtk_pinctrl *hw,
				    struct mtk_pin_field *pf, int *value)
{
	int nbits_l, nbits_h, h, l;

	mtk_hw_bits_part(pf, &nbits_h, &nbits_l);

	l  = (mtk_r32(hw, pf->index, pf->offset)
	      >> pf->bitpos) & (BIT(nbits_l) - 1);
	h  = (mtk_r32(hw, pf->index, pf->offset + pf->next))
	      & (BIT(nbits_h) - 1);

	*value = (h << nbits_l) | l;
}

int mtk_hw_set_value(struct mtk_pinctrl *hw, const struct mtk_pin_desc *desc,
		     int field, int value)
{
	struct mtk_pin_field pf;
	int err;

	err = mtk_hw_pin_field_get(hw, desc, field, &pf);
	if (err)
		return err;

	if (value < 0 || value > pf.mask)
		return -EINVAL;

	if (!pf.next)
		mtk_rmw(hw, pf.index, pf.offset, pf.mask << pf.bitpos,
			(value & pf.mask) << pf.bitpos);
	else
		mtk_hw_write_cross_field(hw, &pf, value);

	return 0;
}
EXPORT_SYMBOL_GPL(mtk_hw_set_value);

int mtk_hw_get_value(struct mtk_pinctrl *hw, const struct mtk_pin_desc *desc,
		     int field, int *value)
{
	struct mtk_pin_field pf;
	int err;

	err = mtk_hw_pin_field_get(hw, desc, field, &pf);
	if (err)
		return err;

	if (!pf.next)
		*value = (mtk_r32(hw, pf.index, pf.offset)
			  >> pf.bitpos) & pf.mask;
	else
		mtk_hw_read_cross_field(hw, &pf, value);

	return 0;
}
EXPORT_SYMBOL_GPL(mtk_hw_get_value);

static int mtk_xt_find_eint_num(struct mtk_pinctrl *hw, unsigned long eint_n)
{
	const struct mtk_pin_desc *desc;
	int i = 0;

	desc = (const struct mtk_pin_desc *)hw->soc->pins;

	while (i < hw->soc->npins) {
		if (desc[i].eint.eint_n == eint_n)
			return desc[i].number;
		i++;
	}

	return EINT_NA;
}

/*
 * Virtual GPIO only used inside SOC and not being exported to outside SOC.
 * Some modules use virtual GPIO as eint (e.g. pmif or usb).
 * In MTK platform, external interrupt (EINT) and GPIO is 1-1 mapping
 * and we can set GPIO as eint.
 * But some modules use specific eint which doesn't have real GPIO pin.
 * So we use virtual GPIO to map it.
 */

bool mtk_is_virt_gpio(struct mtk_pinctrl *hw, unsigned int gpio_n)
{
	const struct mtk_pin_desc *desc;
	bool virt_gpio = false;

	desc = (const struct mtk_pin_desc *)&hw->soc->pins[gpio_n];

	/* if the GPIO is not supported for eint mode */
	if (desc->eint.eint_m == NO_EINT_SUPPORT)
		return virt_gpio;

	if (desc->funcs && !desc->funcs[desc->eint.eint_m].name)
		virt_gpio = true;

	return virt_gpio;
}
EXPORT_SYMBOL_GPL(mtk_is_virt_gpio);

static int mtk_xt_get_gpio_n(void *data, unsigned long eint_n,
			     unsigned int *gpio_n,
			     struct gpio_chip **gpio_chip)
{
	struct mtk_pinctrl *hw = (struct mtk_pinctrl *)data;
	const struct mtk_pin_desc *desc;

	desc = (const struct mtk_pin_desc *)hw->soc->pins;
	*gpio_chip = &hw->chip;

	/*
	 * Be greedy to guess first gpio_n is equal to eint_n.
	 * Only eint virtual eint number is greater than gpio number.
	 */
	if (hw->soc->npins > eint_n &&
	    desc[eint_n].eint.eint_n == eint_n)
		*gpio_n = eint_n;
	else
		*gpio_n = mtk_xt_find_eint_num(hw, eint_n);

	return *gpio_n == EINT_NA ? -EINVAL : 0;
}

static int mtk_xt_get_gpio_state(void *data, unsigned long eint_n)
{
	struct mtk_pinctrl *hw = (struct mtk_pinctrl *)data;
	const struct mtk_pin_desc *desc;
	struct gpio_chip *gpio_chip;
	unsigned int gpio_n;
	int value, err;

	err = mtk_xt_get_gpio_n(hw, eint_n, &gpio_n, &gpio_chip);
	if (err)
		return err;

	desc = (const struct mtk_pin_desc *)&hw->soc->pins[gpio_n];

	err = mtk_hw_get_value(hw, desc, PINCTRL_PIN_REG_DI, &value);
	if (err)
		return err;

	return !!value;
}

static int mtk_xt_set_gpio_as_eint(void *data, unsigned long eint_n)
{
	struct mtk_pinctrl *hw = (struct mtk_pinctrl *)data;
	const struct mtk_pin_desc *desc;
	struct gpio_chip *gpio_chip;
	unsigned int gpio_n;
	int err;

	err = mtk_xt_get_gpio_n(hw, eint_n, &gpio_n, &gpio_chip);
	if (err)
		return err;

	if (mtk_is_virt_gpio(hw, gpio_n))
		return 0;

	desc = (const struct mtk_pin_desc *)&hw->soc->pins[gpio_n];

	err = mtk_hw_set_value(hw, desc, PINCTRL_PIN_REG_MODE,
			       desc->eint.eint_m);
	if (err)
		return err;

	err = mtk_hw_set_value(hw, desc, PINCTRL_PIN_REG_DIR, MTK_INPUT);
	if (err)
		return err;

	err = mtk_hw_set_value(hw, desc, PINCTRL_PIN_REG_SMT, MTK_ENABLE);
	/* SMT is supposed to be supported by every real GPIO and doesn't
	 * support virtual GPIOs, so the extra condition err != -ENOTSUPP
	 * is just for adding EINT support to these virtual GPIOs. It should
	 * add an extra flag in the pin descriptor when more pins with
	 * distinctive characteristic come out.
	 */
	if (err && err != -ENOTSUPP)
		return err;

	return 0;
}

static const struct mtk_eint_xt mtk_eint_xt = {
	.get_gpio_n = mtk_xt_get_gpio_n,
	.get_gpio_state = mtk_xt_get_gpio_state,
	.set_gpio_as_eint = mtk_xt_set_gpio_as_eint,
};

int mtk_build_eint(struct mtk_pinctrl *hw, struct platform_device *pdev)
{
	struct device_node *np = pdev->dev.of_node;
	int ret, i, j, count_reg_names;

	if (!IS_ENABLED(CONFIG_EINT_MTK))
		return 0;

	if (!of_property_read_bool(np, "interrupt-controller"))
		return -ENODEV;

	hw->eint = devm_kzalloc(hw->dev, sizeof(*hw->eint), GFP_KERNEL);
	if (!hw->eint)
		return -ENOMEM;

	count_reg_names = of_property_count_strings(np, "reg-names");
	if (count_reg_names < hw->soc->nbase_names)
		return -EINVAL;

	hw->eint->nbase = count_reg_names - hw->soc->nbase_names;
	hw->eint->base = devm_kmalloc_array(&pdev->dev, hw->eint->nbase,
					    sizeof(*hw->eint->base), GFP_KERNEL | __GFP_ZERO);
	if (!hw->eint->base) {
		ret = -ENOMEM;
		goto err_free_base;
	}

	for (i = hw->soc->nbase_names, j = 0; i < count_reg_names; i++, j++) {
		hw->eint->base[j] = of_iomap(np, i);
		if (IS_ERR(hw->eint->base[j])) {
			ret = PTR_ERR(hw->eint->base[j]);
			goto err_free_eint;
		}
	}

	hw->eint->irq = irq_of_parse_and_map(np, 0);
	if (!hw->eint->irq) {
		ret = -EINVAL;
		goto err_free_eint;
	}

	if (!hw->soc->eint_hw) {
		ret = -ENODEV;
		goto err_free_eint;
	}

	hw->eint->dev = &pdev->dev;
	hw->eint->hw = hw->soc->eint_hw;
	hw->eint->pctl = hw;
	hw->eint->gpio_xlate = &mtk_eint_xt;

	ret = mtk_eint_do_init(hw->eint, hw->soc->eint_pin);
	if (ret)
		goto err_free_eint;

	return 0;

err_free_eint:
	for (j = 0; j < hw->eint->nbase; j++) {
		if (hw->eint->base[j])
			iounmap(hw->eint->base[j]);
	}
	devm_kfree(hw->dev, hw->eint->base);
err_free_base:
	devm_kfree(hw->dev, hw->eint);
	hw->eint = NULL;
	return ret;
}
EXPORT_SYMBOL_GPL(mtk_build_eint);

/* Revision 0 */
int mtk_pinconf_bias_disable_set(struct mtk_pinctrl *hw,
				 const struct mtk_pin_desc *desc)
{
	int err;

	err = mtk_hw_set_value(hw, desc, PINCTRL_PIN_REG_PU,
			       MTK_DISABLE);
	if (err)
		return err;

	err = mtk_hw_set_value(hw, desc, PINCTRL_PIN_REG_PD,
			       MTK_DISABLE);
	if (err)
		return err;

	return 0;
}
EXPORT_SYMBOL_GPL(mtk_pinconf_bias_disable_set);

int mtk_pinconf_bias_disable_get(struct mtk_pinctrl *hw,
				 const struct mtk_pin_desc *desc, int *res)
{
	int v, v2;
	int err;

	err = mtk_hw_get_value(hw, desc, PINCTRL_PIN_REG_PU, &v);
	if (err)
		return err;

	err = mtk_hw_get_value(hw, desc, PINCTRL_PIN_REG_PD, &v2);
	if (err)
		return err;

	if (v == MTK_ENABLE || v2 == MTK_ENABLE)
		return -EINVAL;

	*res = 1;

	return 0;
}
EXPORT_SYMBOL_GPL(mtk_pinconf_bias_disable_get);

int mtk_pinconf_bias_set(struct mtk_pinctrl *hw,
			 const struct mtk_pin_desc *desc, bool pullup)
{
	int err, arg;

	arg = pullup ? 1 : 2;

	err = mtk_hw_set_value(hw, desc, PINCTRL_PIN_REG_PU, arg & 1);
	if (err)
		return err;

	err = mtk_hw_set_value(hw, desc, PINCTRL_PIN_REG_PD,
			       !!(arg & 2));
	if (err)
		return err;

	return 0;
}
EXPORT_SYMBOL_GPL(mtk_pinconf_bias_set);

int mtk_pinconf_bias_get(struct mtk_pinctrl *hw,
			 const struct mtk_pin_desc *desc, bool pullup, int *res)
{
	int reg, err, v;

	reg = pullup ? PINCTRL_PIN_REG_PU : PINCTRL_PIN_REG_PD;

	err = mtk_hw_get_value(hw, desc, reg, &v);
	if (err)
		return err;

	if (!v)
		return -EINVAL;

	*res = 1;

	return 0;
}
EXPORT_SYMBOL_GPL(mtk_pinconf_bias_get);

/* Revision 1 */
int mtk_pinconf_bias_disable_set_rev1(struct mtk_pinctrl *hw,
				      const struct mtk_pin_desc *desc)
{
	return mtk_hw_set_value(hw, desc, PINCTRL_PIN_REG_PULLEN,
				MTK_DISABLE);
}
EXPORT_SYMBOL_GPL(mtk_pinconf_bias_disable_set_rev1);

int mtk_pinconf_bias_disable_get_rev1(struct mtk_pinctrl *hw,
				      const struct mtk_pin_desc *desc, int *res)
{
	int v, err;

	err = mtk_hw_get_value(hw, desc, PINCTRL_PIN_REG_PULLEN, &v);
	if (err)
		return err;

	if (v == MTK_ENABLE)
		return -EINVAL;

	*res = 1;

	return 0;
}
EXPORT_SYMBOL_GPL(mtk_pinconf_bias_disable_get_rev1);

int mtk_pinconf_bias_set_rev1(struct mtk_pinctrl *hw,
			      const struct mtk_pin_desc *desc, bool pullup)
{
	int err, arg;

	arg = pullup ? MTK_PULLUP : MTK_PULLDOWN;

	err = mtk_hw_set_value(hw, desc, PINCTRL_PIN_REG_PULLEN,
			       MTK_ENABLE);
	if (err)
		return err;

	err = mtk_hw_set_value(hw, desc, PINCTRL_PIN_REG_PULLSEL, arg);
	if (err)
		return err;

	return 0;
}
EXPORT_SYMBOL_GPL(mtk_pinconf_bias_set_rev1);

int mtk_pinconf_bias_get_rev1(struct mtk_pinctrl *hw,
			      const struct mtk_pin_desc *desc, bool pullup,
			      int *res)
{
	int err, v;

	err = mtk_hw_get_value(hw, desc, PINCTRL_PIN_REG_PULLEN, &v);
	if (err)
		return err;

	if (v == MTK_DISABLE)
		return -EINVAL;

	err = mtk_hw_get_value(hw, desc, PINCTRL_PIN_REG_PULLSEL, &v);
	if (err)
		return err;

	if (pullup ^ (v == MTK_PULLUP))
		return -EINVAL;

	*res = 1;

	return 0;
}
EXPORT_SYMBOL_GPL(mtk_pinconf_bias_get_rev1);

/* Combo for the following pull register type:
 * 1. PU + PD
 * 2. PULLSEL + PULLEN
 * 3. PUPD + R0 + R1
 */
static int mtk_pinconf_bias_set_pu_pd(struct mtk_pinctrl *hw,
				const struct mtk_pin_desc *desc,
				u32 pullup, u32 arg, bool pd_only)
{
	int err, pu, pd;

	if (arg == MTK_DISABLE) {
		pu = 0;
		pd = 0;
	} else if ((arg == MTK_ENABLE) && pullup) {
		pu = 1;
		pd = 0;
	} else if ((arg == MTK_ENABLE) && !pullup) {
		pu = 0;
		pd = 1;
	} else {
		return -EINVAL;
	}

	if (!pd_only) {
		err = mtk_hw_set_value(hw, desc, PINCTRL_PIN_REG_PU, pu);
		if (err)
			return err;
	}

	return mtk_hw_set_value(hw, desc, PINCTRL_PIN_REG_PD, pd);
}

static int mtk_pinconf_bias_set_pullsel_pullen(struct mtk_pinctrl *hw,
				const struct mtk_pin_desc *desc,
				u32 pullup, u32 arg)
{
	int err, enable;

	if (arg == MTK_DISABLE)
		enable = 0;
	else if (arg == MTK_ENABLE)
		enable = 1;
	else {
		err = -EINVAL;
		goto out;
	}

	err = mtk_hw_set_value(hw, desc, PINCTRL_PIN_REG_PULLEN, enable);
	if (err)
		goto out;

	err = mtk_hw_set_value(hw, desc, PINCTRL_PIN_REG_PULLSEL, pullup);

out:
	return err;
}

static int mtk_pinconf_bias_set_pupd_r1_r0(struct mtk_pinctrl *hw,
				const struct mtk_pin_desc *desc,
				u32 pullup, u32 arg)
{
	int err, r0, r1;

	if ((arg == MTK_DISABLE) || (arg == MTK_PUPD_SET_R1R0_00)) {
		pullup = 0;
		r0 = 0;
		r1 = 0;
	} else if (arg == MTK_PUPD_SET_R1R0_01) {
		r0 = 1;
		r1 = 0;
	} else if (arg == MTK_PUPD_SET_R1R0_10) {
		r0 = 0;
		r1 = 1;
	} else if (arg == MTK_PUPD_SET_R1R0_11) {
		r0 = 1;
		r1 = 1;
	} else {
		err = -EINVAL;
		goto out;
	}

	/* MTK HW PUPD bit: 1 for pull-down, 0 for pull-up */
	err = mtk_hw_set_value(hw, desc, PINCTRL_PIN_REG_PUPD, !pullup);
	if (err)
		goto out;

	err = mtk_hw_set_value(hw, desc, PINCTRL_PIN_REG_R0, r0);
	if (err)
		goto out;

	err = mtk_hw_set_value(hw, desc, PINCTRL_PIN_REG_R1, r1);

out:
	return err;
}

static int mtk_hw_pin_rsel_lookup(struct mtk_pinctrl *hw,
				  const struct mtk_pin_desc *desc,
				  u32 pullup, u32 arg, u32 *rsel_val)
{
	const struct mtk_pin_rsel *rsel;
	int check;
	bool found = false;

	rsel = hw->soc->pin_rsel;

	for (check = 0; check <= hw->soc->npin_rsel - 1; check++) {
		if (desc->number >= rsel[check].s_pin &&
		    desc->number <= rsel[check].e_pin) {
			if (pullup) {
				if (rsel[check].up_rsel == arg) {
					found = true;
					*rsel_val = rsel[check].rsel_index;
					break;
				}
			} else {
				if (rsel[check].down_rsel == arg) {
					found = true;
					*rsel_val = rsel[check].rsel_index;
					break;
				}
			}
		}
	}

	if (!found) {
		dev_err(hw->dev, "Not support rsel value %d Ohm for pin = %d (%s)\n",
			arg, desc->number, desc->name);
		return -ENOTSUPP;
	}

	return 0;
}

static int mtk_pinconf_bias_set_rsel(struct mtk_pinctrl *hw,
				     const struct mtk_pin_desc *desc,
				     u32 pullup, u32 arg)
{
	int err, rsel_val;

	if (hw->rsel_si_unit) {
		/* find pin rsel_index from pin_rsel array*/
		err = mtk_hw_pin_rsel_lookup(hw, desc, pullup, arg, &rsel_val);
		if (err)
			return err;
	} else {
		if (arg < MTK_PULL_SET_RSEL_000 || arg > MTK_PULL_SET_RSEL_111)
			return -EINVAL;

		rsel_val = arg - MTK_PULL_SET_RSEL_000;
	}

	return mtk_hw_set_value(hw, desc, PINCTRL_PIN_REG_RSEL, rsel_val);
}

static int mtk_pinconf_bias_set_pu_pd_rsel(struct mtk_pinctrl *hw,
					   const struct mtk_pin_desc *desc,
					   u32 pullup, u32 arg)
{
	u32 enable = arg == MTK_DISABLE ? MTK_DISABLE : MTK_ENABLE;
	int err;

	if (arg != MTK_DISABLE) {
		err = mtk_pinconf_bias_set_rsel(hw, desc, pullup, arg);
		if (err)
			return err;
	}

	return mtk_pinconf_bias_set_pu_pd(hw, desc, pullup, enable, false);
}

int mtk_pinconf_bias_set_combo(struct mtk_pinctrl *hw,
			       const struct mtk_pin_desc *desc,
			       u32 pullup, u32 arg)
{
	int err = -ENOTSUPP;
	u32 try_all_type;

	if (hw->soc->pull_type)
		try_all_type = hw->soc->pull_type[desc->number];
	else
		try_all_type = MTK_PULL_TYPE_MASK;

	if (try_all_type & MTK_PULL_RSEL_TYPE) {
		err = mtk_pinconf_bias_set_pu_pd_rsel(hw, desc, pullup, arg);
		if (!err)
			return 0;
	}

	if (try_all_type & MTK_PULL_PD_TYPE) {
		err = mtk_pinconf_bias_set_pu_pd(hw, desc, pullup, arg, true);
		if (!err)
			return err;
	}

	if (try_all_type & MTK_PULL_PU_PD_TYPE) {
		err = mtk_pinconf_bias_set_pu_pd(hw, desc, pullup, arg, false);
		if (!err)
			return 0;
	}

	if (try_all_type & MTK_PULL_PULLSEL_TYPE) {
		err = mtk_pinconf_bias_set_pullsel_pullen(hw, desc,
							  pullup, arg);
		if (!err)
			return 0;
	}

	if (try_all_type & MTK_PULL_PUPD_R1R0_TYPE)
		err = mtk_pinconf_bias_set_pupd_r1_r0(hw, desc, pullup, arg);

	if (err)
		dev_err(hw->dev, "Invalid pull argument\n");

	return err;
}
EXPORT_SYMBOL_GPL(mtk_pinconf_bias_set_combo);

static int mtk_rsel_get_si_unit(struct mtk_pinctrl *hw,
				const struct mtk_pin_desc *desc,
				u32 pullup, u32 rsel_val, u32 *si_unit)
{
	const struct mtk_pin_rsel *rsel;
	int check;

	rsel = hw->soc->pin_rsel;

	for (check = 0; check <= hw->soc->npin_rsel - 1; check++) {
		if (desc->number >= rsel[check].s_pin &&
		    desc->number <= rsel[check].e_pin) {
			if (rsel_val == rsel[check].rsel_index) {
				if (pullup)
					*si_unit = rsel[check].up_rsel;
				else
					*si_unit = rsel[check].down_rsel;
				break;
			}
		}
	}

	return 0;
}

static int mtk_pinconf_bias_get_pu_pd_rsel(struct mtk_pinctrl *hw,
					   const struct mtk_pin_desc *desc,
					   u32 *pullup, u32 *enable)
{
	int pu, pd, rsel, err;

	err = mtk_hw_get_value(hw, desc, PINCTRL_PIN_REG_RSEL, &rsel);
	if (err)
		goto out;

	err = mtk_hw_get_value(hw, desc, PINCTRL_PIN_REG_PU, &pu);
	if (err)
		goto out;

	err = mtk_hw_get_value(hw, desc, PINCTRL_PIN_REG_PD, &pd);
	if (err)
		goto out;

	if (pu == 0 && pd == 0) {
		*pullup = 0;
		*enable = MTK_DISABLE;
	} else if (pu == 1 && pd == 0) {
		*pullup = 1;
		if (hw->rsel_si_unit)
			mtk_rsel_get_si_unit(hw, desc, *pullup, rsel, enable);
		else
			*enable = rsel + MTK_PULL_SET_RSEL_000;
	} else if (pu == 0 && pd == 1) {
		*pullup = 0;
		if (hw->rsel_si_unit)
			mtk_rsel_get_si_unit(hw, desc, *pullup, rsel, enable);
		else
			*enable = rsel + MTK_PULL_SET_RSEL_000;
	} else {
		err = -EINVAL;
		goto out;
	}

out:
	return err;
}

static int mtk_pinconf_bias_get_pu_pd(struct mtk_pinctrl *hw,
				const struct mtk_pin_desc *desc,
				u32 *pullup, u32 *enable)
{
	int err, pu, pd;

	err = mtk_hw_get_value(hw, desc, PINCTRL_PIN_REG_PU, &pu);
	if (err)
		goto out;

	err = mtk_hw_get_value(hw, desc, PINCTRL_PIN_REG_PD, &pd);
	if (err)
		goto out;

	if (pu == 0 && pd == 0) {
		*pullup = 0;
		*enable = MTK_DISABLE;
	} else if (pu == 1 && pd == 0) {
		*pullup = 1;
		*enable = MTK_ENABLE;
	} else if (pu == 0 && pd == 1) {
		*pullup = 0;
		*enable = MTK_ENABLE;
	} else
		err = -EINVAL;

out:
	return err;
}

static int mtk_pinconf_bias_get_pd(struct mtk_pinctrl *hw,
				const struct mtk_pin_desc *desc,
				u32 *pullup, u32 *enable)
{
	int err, pd;

	err = mtk_hw_get_value(hw, desc, PINCTRL_PIN_REG_PD, &pd);
	if (err)
		goto out;

	if (pd == 0) {
		*pullup = 0;
		*enable = MTK_DISABLE;
	} else if (pd == 1) {
		*pullup = 0;
		*enable = MTK_ENABLE;
	} else
		err = -EINVAL;

out:
	return err;
}

static int mtk_pinconf_bias_get_pullsel_pullen(struct mtk_pinctrl *hw,
				const struct mtk_pin_desc *desc,
				u32 *pullup, u32 *enable)
{
	int err;

	err = mtk_hw_get_value(hw, desc, PINCTRL_PIN_REG_PULLSEL, pullup);
	if (err)
		goto out;

	err = mtk_hw_get_value(hw, desc, PINCTRL_PIN_REG_PULLEN, enable);

out:
	return err;
}

static int mtk_pinconf_bias_get_pupd_r1_r0(struct mtk_pinctrl *hw,
				const struct mtk_pin_desc *desc,
				u32 *pullup, u32 *enable)
{
	int err, r0, r1;

	err = mtk_hw_get_value(hw, desc, PINCTRL_PIN_REG_PUPD, pullup);
	if (err)
		goto out;
	/* MTK HW PUPD bit: 1 for pull-down, 0 for pull-up */
	*pullup = !(*pullup);

	err = mtk_hw_get_value(hw, desc, PINCTRL_PIN_REG_R0, &r0);
	if (err)
		goto out;

	err = mtk_hw_get_value(hw, desc, PINCTRL_PIN_REG_R1, &r1);
	if (err)
		goto out;

	if ((r1 == 0) && (r0 == 0))
		*enable = MTK_PUPD_SET_R1R0_00;
	else if ((r1 == 0) && (r0 == 1))
		*enable = MTK_PUPD_SET_R1R0_01;
	else if ((r1 == 1) && (r0 == 0))
		*enable = MTK_PUPD_SET_R1R0_10;
	else if ((r1 == 1) && (r0 == 1))
		*enable = MTK_PUPD_SET_R1R0_11;
	else
		err = -EINVAL;

out:
	return err;
}

int mtk_pinconf_bias_get_combo(struct mtk_pinctrl *hw,
			      const struct mtk_pin_desc *desc,
			      u32 *pullup, u32 *enable)
{
	int err = -ENOTSUPP;
	u32 try_all_type;

	if (hw->soc->pull_type)
		try_all_type = hw->soc->pull_type[desc->number];
	else
		try_all_type = MTK_PULL_TYPE_MASK;

	if (try_all_type & MTK_PULL_RSEL_TYPE) {
		err = mtk_pinconf_bias_get_pu_pd_rsel(hw, desc, pullup, enable);
		if (!err)
			return 0;
	}

	if (try_all_type & MTK_PULL_PD_TYPE) {
		err = mtk_pinconf_bias_get_pd(hw, desc, pullup, enable);
		if (!err)
			return err;
	}

	if (try_all_type & MTK_PULL_PU_PD_TYPE) {
		err = mtk_pinconf_bias_get_pu_pd(hw, desc, pullup, enable);
		if (!err)
			return 0;
	}

	if (try_all_type & MTK_PULL_PULLSEL_TYPE) {
		err = mtk_pinconf_bias_get_pullsel_pullen(hw, desc,
							  pullup, enable);
		if (!err)
			return 0;
	}

	if (try_all_type & MTK_PULL_PUPD_R1R0_TYPE)
		err = mtk_pinconf_bias_get_pupd_r1_r0(hw, desc, pullup, enable);

	return err;
}
EXPORT_SYMBOL_GPL(mtk_pinconf_bias_get_combo);

/* Revision 0 */
int mtk_pinconf_drive_set(struct mtk_pinctrl *hw,
			  const struct mtk_pin_desc *desc, u32 arg)
{
	const struct mtk_drive_desc *tb;
	int err = -ENOTSUPP;

	tb = &mtk_drive[desc->drv_n];
	/* 4mA when (e8, e4) = (0, 0)
	 * 8mA when (e8, e4) = (0, 1)
	 * 12mA when (e8, e4) = (1, 0)
	 * 16mA when (e8, e4) = (1, 1)
	 */
	if ((arg >= tb->min && arg <= tb->max) && !(arg % tb->step)) {
		arg = (arg / tb->step - 1) * tb->scal;
		err = mtk_hw_set_value(hw, desc, PINCTRL_PIN_REG_E4,
				       arg & 0x1);
		if (err)
			return err;

		err = mtk_hw_set_value(hw, desc, PINCTRL_PIN_REG_E8,
				       (arg & 0x2) >> 1);
		if (err)
			return err;
	}

	return err;
}
EXPORT_SYMBOL_GPL(mtk_pinconf_drive_set);

int mtk_pinconf_drive_get(struct mtk_pinctrl *hw,
			  const struct mtk_pin_desc *desc, int *val)
{
	const struct mtk_drive_desc *tb;
	int err, val1, val2;

	tb = &mtk_drive[desc->drv_n];

	err = mtk_hw_get_value(hw, desc, PINCTRL_PIN_REG_E4, &val1);
	if (err)
		return err;

	err = mtk_hw_get_value(hw, desc, PINCTRL_PIN_REG_E8, &val2);
	if (err)
		return err;

	/* 4mA when (e8, e4) = (0, 0); 8mA when (e8, e4) = (0, 1)
	 * 12mA when (e8, e4) = (1, 0); 16mA when (e8, e4) = (1, 1)
	 */
	*val = (((val2 << 1) + val1) / tb->scal + 1) * tb->step;

	return 0;
}
EXPORT_SYMBOL_GPL(mtk_pinconf_drive_get);

/* Revision 1 */
int mtk_pinconf_drive_set_rev1(struct mtk_pinctrl *hw,
			       const struct mtk_pin_desc *desc, u32 arg)
{
	const struct mtk_drive_desc *tb;
	int err = -ENOTSUPP;

	tb = &mtk_drive[desc->drv_n];

	if ((arg >= tb->min && arg <= tb->max) && !(arg % tb->step)) {
		arg = (arg / tb->step - 1) * tb->scal;

		err = mtk_hw_set_value(hw, desc, PINCTRL_PIN_REG_DRV,
				       arg);
		if (err)
			return err;
	}

	return err;
}
EXPORT_SYMBOL_GPL(mtk_pinconf_drive_set_rev1);

int mtk_pinconf_drive_get_rev1(struct mtk_pinctrl *hw,
			       const struct mtk_pin_desc *desc, int *val)
{
	const struct mtk_drive_desc *tb;
	int err, val1;

	tb = &mtk_drive[desc->drv_n];

	err = mtk_hw_get_value(hw, desc, PINCTRL_PIN_REG_DRV, &val1);
	if (err)
		return err;

	*val = ((val1 & 0x7) / tb->scal + 1) * tb->step;

	return 0;
}
EXPORT_SYMBOL_GPL(mtk_pinconf_drive_get_rev1);

int mtk_pinconf_drive_set_raw(struct mtk_pinctrl *hw,
			       const struct mtk_pin_desc *desc, u32 arg)
{
	return mtk_hw_set_value(hw, desc, PINCTRL_PIN_REG_DRV, arg);
}
EXPORT_SYMBOL_GPL(mtk_pinconf_drive_set_raw);

int mtk_pinconf_drive_get_raw(struct mtk_pinctrl *hw,
			       const struct mtk_pin_desc *desc, int *val)
{
	return mtk_hw_get_value(hw, desc, PINCTRL_PIN_REG_DRV, val);
}
EXPORT_SYMBOL_GPL(mtk_pinconf_drive_get_raw);

int mtk_pinconf_adv_pull_set(struct mtk_pinctrl *hw,
			     const struct mtk_pin_desc *desc, bool pullup,
			     u32 arg)
{
	int err;

	/* 10K off & 50K (75K) off, when (R0, R1) = (0, 0);
	 * 10K off & 50K (75K) on, when (R0, R1) = (0, 1);
	 * 10K on & 50K (75K) off, when (R0, R1) = (1, 0);
	 * 10K on & 50K (75K) on, when (R0, R1) = (1, 1)
	 */
	err = mtk_hw_set_value(hw, desc, PINCTRL_PIN_REG_R0, arg & 1);
	if (err)
		return 0;

	err = mtk_hw_set_value(hw, desc, PINCTRL_PIN_REG_R1,
			       !!(arg & 2));
	if (err)
		return 0;

	arg = pullup ? 0 : 1;

	err = mtk_hw_set_value(hw, desc, PINCTRL_PIN_REG_PUPD, arg);

	/* If PUPD register is not supported for that pin, let's fallback to
	 * general bias control.
	 */
	if (err == -ENOTSUPP) {
		if (hw->soc->bias_set) {
			err = hw->soc->bias_set(hw, desc, pullup);
			if (err)
				return err;
		} else {
			err = mtk_pinconf_bias_set_rev1(hw, desc, pullup);
			if (err)
				err = mtk_pinconf_bias_set(hw, desc, pullup);
		}
	}

	return err;
}
EXPORT_SYMBOL_GPL(mtk_pinconf_adv_pull_set);

int mtk_pinconf_adv_pull_get(struct mtk_pinctrl *hw,
			     const struct mtk_pin_desc *desc, bool pullup,
			     u32 *val)
{
	u32 t, t2;
	int err;

	err = mtk_hw_get_value(hw, desc, PINCTRL_PIN_REG_PUPD, &t);

	/* If PUPD register is not supported for that pin, let's fallback to
	 * general bias control.
	 */
	if (err == -ENOTSUPP) {
		if (hw->soc->bias_get) {
			err = hw->soc->bias_get(hw, desc, pullup, val);
			if (err)
				return err;
		} else {
			return -ENOTSUPP;
		}
	} else {
		/* t == 0 supposes PULLUP for the customized PULL setup */
		if (err)
			return err;

		if (pullup ^ !t)
			return -EINVAL;
	}

	err = mtk_hw_get_value(hw, desc, PINCTRL_PIN_REG_R0, &t);
	if (err)
		return err;

	err = mtk_hw_get_value(hw, desc, PINCTRL_PIN_REG_R1, &t2);
	if (err)
		return err;

	*val = (t | t2 << 1) & 0x7;

	return 0;
}
EXPORT_SYMBOL_GPL(mtk_pinconf_adv_pull_get);

int mtk_pinconf_adv_drive_set(struct mtk_pinctrl *hw,
			      const struct mtk_pin_desc *desc, u32 arg)
{
	int err;
	int en = arg & 1;
	int e0 = !!(arg & 2);
	int e1 = !!(arg & 4);

	err = mtk_hw_set_value(hw, desc, PINCTRL_PIN_REG_DRV_EN, en);
	if (err)
		return err;

	if (!en)
		return err;

	err = mtk_hw_set_value(hw, desc, PINCTRL_PIN_REG_DRV_E0, e0);
	if (err)
		return err;

	err = mtk_hw_set_value(hw, desc, PINCTRL_PIN_REG_DRV_E1, e1);
	if (err)
		return err;

	return err;
}
EXPORT_SYMBOL_GPL(mtk_pinconf_adv_drive_set);

int mtk_pinconf_adv_drive_get(struct mtk_pinctrl *hw,
			      const struct mtk_pin_desc *desc, u32 *val)
{
	u32 en, e0, e1;
	int err;

	err = mtk_hw_get_value(hw, desc, PINCTRL_PIN_REG_DRV_EN, &en);
	if (err)
		return err;

	err = mtk_hw_get_value(hw, desc, PINCTRL_PIN_REG_DRV_E0, &e0);
	if (err)
		return err;

	err = mtk_hw_get_value(hw, desc, PINCTRL_PIN_REG_DRV_E1, &e1);
	if (err)
		return err;

	*val = (en | e0 << 1 | e1 << 2) & 0x7;

	return 0;
}
EXPORT_SYMBOL_GPL(mtk_pinconf_adv_drive_get);

int mtk_pinconf_adv_drive_set_raw(struct mtk_pinctrl *hw,
				  const struct mtk_pin_desc *desc, u32 arg)
{
	return mtk_hw_set_value(hw, desc, PINCTRL_PIN_REG_DRV_ADV, arg);
}
EXPORT_SYMBOL_GPL(mtk_pinconf_adv_drive_set_raw);

int mtk_pinconf_adv_drive_get_raw(struct mtk_pinctrl *hw,
				  const struct mtk_pin_desc *desc, u32 *val)
{
	return mtk_hw_get_value(hw, desc, PINCTRL_PIN_REG_DRV_ADV, val);
}
EXPORT_SYMBOL_GPL(mtk_pinconf_adv_drive_get_raw);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Sean Wang <sean.wang@mediatek.com>");
MODULE_DESCRIPTION("Pin configuration library module for mediatek SoCs");
