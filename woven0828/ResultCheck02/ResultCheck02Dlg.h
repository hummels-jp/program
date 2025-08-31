// ResultCheck02Dlg.h: 头文件
//

#pragma once

#include "Point.h"
#include "Polygon.h"
#include "PolygonFilter.h"
#include <vector>

// CResultCheck02Dlg 对话框
class CResultCheck02Dlg : public CDialogEx
{
// 构造
public:
	CResultCheck02Dlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RESULTCHECK02_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDrawLine();
	afx_msg void OnBnClickedOk();
	afx_msg void OnDrawPolygon();
	afx_msg void OnFileOpen32773();
	std::vector<Polygon2D> m_polygons;
	afx_msg void OnJsonfileOpenoutputjson();
};
