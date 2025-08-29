// ResultCheck02Dlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "ResultCheck02.h"
#include "ResultCheck02Dlg.h"
#include "afxdialogex.h"

#include "Point.h"
#include "Polygon.h"
#include "PolygonFilter.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CResultCheck02Dlg 对话框



CResultCheck02Dlg::CResultCheck02Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_RESULTCHECK02_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CResultCheck02Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CResultCheck02Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_DRAW_LINE, &CResultCheck02Dlg::OnDrawLine)
	ON_BN_CLICKED(IDOK, &CResultCheck02Dlg::OnBnClickedOk)
	ON_COMMAND(ID_DRAW_POLYGON, &CResultCheck02Dlg::OnDrawPolygon)
	ON_COMMAND(ID_FILE_OPEN32773, &CResultCheck02Dlg::OnFileOpen32773)
END_MESSAGE_MAP()


// CResultCheck02Dlg 消息处理程序

BOOL CResultCheck02Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	// 设置窗口大小（宽800，高600）
	SetWindowPos(NULL, 0, 0, 800, 600, SWP_NOMOVE | SWP_NOZORDER);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CResultCheck02Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CResultCheck02Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
		OnDrawPolygon(); // 自动绘制多边形
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CResultCheck02Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CResultCheck02Dlg::OnDrawLine()
{

}

void CResultCheck02Dlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码


	CDialogEx::OnOK();


}

void CResultCheck02Dlg::OnDrawPolygon()
{
    CClientDC dc(this);

	COLORREF colors[] = {
		RGB(255,0,0),     // 红
		RGB(0,128,0),     // 绿
		RGB(0,0,255),     // 蓝
		RGB(255,128,0),   // 橙
		RGB(128,0,255),   // 紫
		RGB(0,200,200),   // 青
		RGB(255,0,128),   // 粉
		RGB(128,128,0),   // 橄榄
		RGB(0,128,128),   // 深青
		RGB(128,0,0),     // 棕
		RGB(0,0,128),     // 深蓝
		RGB(128,128,128), // 灰
		RGB(255,255,0),   // 黄
		RGB(0,255,0),     // 亮绿
		RGB(0,255,255),   // 浅青
		RGB(255,0,255),   // 洋红
		RGB(192,192,192), // 银
		RGB(255,192,203), // 浅粉
		RGB(210,105,30),  // 巧克力
		RGB(0,100,0)      // 深绿
	};
	int colorCount = sizeof(colors) / sizeof(colors[0]);

    double minX = DBL_MAX, maxX = -DBL_MAX, minY = DBL_MAX, maxY = -DBL_MAX;
    for (const auto& poly : m_polygons) {
        for (const auto& pt : poly.points_) {
            if (pt.getX() < minX) minX = pt.getX();
            if (pt.getX() > maxX) maxX = pt.getX();
            if (pt.getY() < minY) minY = pt.getY();
            if (pt.getY() > maxY) maxY = pt.getY();
        }
    }

    if (maxX - minX < 1e-6) maxX = minX + 1.0;
    if (maxY - minY < 1e-6) maxY = minY + 1.0;

    CRect rect;
    GetClientRect(&rect);
    int w = rect.Width();
    int h = rect.Height();

    int margin = 20;
    double scaleX = (w - 2 * margin) / (maxX - minX);
    double scaleY = (h - 2 * margin) / (maxY - minY);

    for (size_t i = 0; i < m_polygons.size(); ++i) {
        const auto& poly = m_polygons[i];
        const auto& pts = poly.points_;
        if (pts.size() < 3) continue;

        std::vector<POINT> drawPts;
        double sumX = 0, sumY = 0;
        for (const auto& pt : pts) {
            POINT p;
            p.x = static_cast<LONG>(margin + (pt.getX() - minX) * scaleX);
            p.y = static_cast<LONG>(margin + (maxY - pt.getY()) * scaleY);
            drawPts.push_back(p);
            sumX += p.x;
            sumY += p.y;
        }

        CPen pen(PS_SOLID, 2, colors[i % colorCount]);
        CPen* pOldPen = dc.SelectObject(&pen);
        CBrush* pOldBrush = dc.SelectObject(CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH)));

        dc.Polygon(drawPts.data(), (int)drawPts.size());

        dc.SelectObject(pOldPen);
        dc.SelectObject(pOldBrush);

        // 设置文本颜色为边界线颜色
        dc.SetTextColor(colors[i % colorCount]);

        // 标注ID
        CString strId;
        strId.Format(_T("ID:%d"), poly.get_polygon_id());
        int cx = static_cast<int>(sumX / pts.size());
        int cy = static_cast<int>(sumY / pts.size());
        dc.TextOut(cx + 5, cy + 5, strId);
    }
}


void CResultCheck02Dlg::OnFileOpen32773()
{
    // 打开文件选择对话框，只显示 .json 文件
    CFileDialog dlg(TRUE, _T("json"), NULL, OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST,
        _T("JSON 文件 (*.json)|*.json|所有文件 (*.*)|*.*||"));
    if (dlg.DoModal() == IDOK)
    {
        CString cstrPath = dlg.GetPathName();
        // CString 转 std::string
        CT2A pszPath(cstrPath);
        std::string input_json(pszPath);

        try {
            PolygonFilter filter;
            m_polygons = filter.read_from_json(input_json); // 保存到成员变量
            Invalidate(); // 触发重绘
        }
        catch (const std::exception& ex) {
            AfxMessageBox(CString("Exception occurred: ") + ex.what());
        }
    }
}
