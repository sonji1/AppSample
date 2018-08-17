// StatisticsDialog.cpp : implementation file
//

#include "stdafx.h"
#include "ACE400Statistics.h"
#include "StatisticsDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStatisticsDialog dialog


CStatisticsDialog::CStatisticsDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CStatisticsDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStatisticsDialog)
	m_strSelect = _T("");

	//}}AFX_DATA_INIT
	
}


void CStatisticsDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStatisticsDialog)
	DDX_Control(pDX, IDC_TREE, m_treeCtrl);
	DDX_Control(pDX, IDC_GRID, m_gridCtrl);
	DDX_Text(pDX, IDC_EDIT_SELECT, m_strSelect);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStatisticsDialog, CDialog)
	//{{AFX_MSG_MAP(CStatisticsDialog)
	ON_WM_SHOWWINDOW()
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE, OnSelchangedTree)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStatisticsDialog message handlers

BOOL CStatisticsDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	if (InitMember() == FALSE)
		return FALSE;

	if (InitView() == FALSE)
		return FALSE;

	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


BOOL CStatisticsDialog::InitMember()
{

	// Grid 관련 멤버 변수 초기화
	m_nFixCols = 1;
	m_nFixRows = 1;
	m_nCols = 10;
	m_nRows = 50;
	m_bEditable = TRUE;
/*
	m_bHorzLines = TRUE;
	m_bListMode = FALSE;
	m_bVertLines = TRUE;
	m_bSelectable = TRUE;
	m_bAllowColumnResize = TRUE;
	m_bAllowRowResize = TRUE;
	m_bHeaderSort = TRUE;
	m_bReadOnly = TRUE;
	m_bItalics = TRUE;
	m_btitleTips = TRUE;
	m_bSingleSelMode = FALSE;
*/

	// 측정 raw data 파일을 read한다.

	return TRUE;
}


BOOL CStatisticsDialog::InitView()
{
	UpdateData(TRUE);

	//----------------------------
	// grid 초기화 

	m_gridCtrl.SetEditable(m_bEditable);
	//m_gridCtrl.SetListMode(m_bListMode);
	//m_gridCtrl.EnableDragAndDrop(TRUE);
	m_gridCtrl.SetTextBkColor(RGB(0xFF, 0xFF, 0xE0));		// 연노랑색 back ground


	TRY {
		m_gridCtrl.SetRowCount(m_nRows);
		m_gridCtrl.SetColumnCount(m_nCols);
		m_gridCtrl.SetFixedRowCount(m_nFixRows);
		m_gridCtrl.SetFixedColumnCount(m_nFixCols);
	}
	CATCH (CMemoryException, e)
	{
		e->ReportError();
		e->Delete();
		return FALSE;
	}
    END_CATCH	

	//----------------------------
	// tree 초기화 
	
	// 'Total'을 root 항목으로 먼저 초기화
	TV_INSERTSTRUCT tvStruct;

	tvStruct.hParent = 0;					// 부모항목:  hParent가 0이면 root 항목
	tvStruct.hInsertAfter = TVI_LAST;		// 삽입방법 
	tvStruct.item.mask = TVIF_TEXT;			// item 멤버들의 유효화 설정: pszText 멤버 유효화
	tvStruct.item.pszText = "Total";		// 트리에 설정할 문자열
	m_hRoot = m_treeCtrl.InsertItem(&tvStruct);	

	Tree_InsertItemStr(m_hRoot, "aaa");
	Tree_InsertItemStr(m_hRoot, "bbb");

	UpdateData(FALSE);
}


// 창이 새로 보일때 때마다 초기화해야 하는 멤버들은 다음의 
// OnShowWindow()의 TOTO 밑에 초기화한다. 
void CStatisticsDialog::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
	// TODO: Add your message handler code here
	if(bShow == TRUE)
	{
		// 멤버 초기화


		// View 초기화 

	}
	
}

// Tree Control의 선택 item이 변경될 때 호출
void CStatisticsDialog::OnSelchangedTree(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	// 현재 선택한 아이템의 핸들 값을 멤버변수에 저장한다.
	m_hSelectedNode = pNMTreeView->itemNew.hItem;

	// 선택한 아이템의 이름을 대화상자의 에디트 상자에 설정한다. 
	m_strSelect = m_treeCtrl.GetItemText(m_hSelectedNode);

	// 대화상자의 컨트롤에 데이터를 출력한다.
	UpdateData(FALSE);
	
	*pResult = 0;
}



BOOL CStatisticsDialog::Tree_InsertItemStr(HTREEITEM& rf_hParent, LPTSTR pStrInsert) 
{
	// TODO: Add your control notification handler code here
	TV_INSERTSTRUCT tvStruct;

	// 에러처리 - 입력할 텍스트가 비어있나 검사한다.
	if(pStrInsert == "")
	{
		AfxMessageBox("입력 노드의 텍스트를 입력하세요");
		return FALSE;
	}

	// 에러처리 - strInsert가 기존 Tree에 존재하는지 검사한다.

	tvStruct.hParent = rf_hParent;		// 입력받은 부모 item을 hParent로
	tvStruct.hInsertAfter = TVI_LAST;
	tvStruct.item.mask = TVIF_TEXT;
	tvStruct.item.pszText = pStrInsert; // 텍스트를 노드 이름으로 한다.

	// 위에서 지정한 정보를 노드를 추가한다.
	m_treeCtrl.InsertItem(&tvStruct);

	m_treeCtrl.Expand(rf_hParent, TVE_EXPAND);

	
	return TRUE;
}
