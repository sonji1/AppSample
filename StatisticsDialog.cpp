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

	// Grid ���� ��� ���� �ʱ�ȭ
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

	// ���� raw data ������ read�Ѵ�.

	return TRUE;
}


BOOL CStatisticsDialog::InitView()
{
	UpdateData(TRUE);

	//----------------------------
	// grid �ʱ�ȭ 

	m_gridCtrl.SetEditable(m_bEditable);
	//m_gridCtrl.SetListMode(m_bListMode);
	//m_gridCtrl.EnableDragAndDrop(TRUE);
	m_gridCtrl.SetTextBkColor(RGB(0xFF, 0xFF, 0xE0));		// ������� back ground


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
	// tree �ʱ�ȭ 
	
	// 'Total'�� root �׸����� ���� �ʱ�ȭ
	TV_INSERTSTRUCT tvStruct;

	tvStruct.hParent = 0;					// �θ��׸�:  hParent�� 0�̸� root �׸�
	tvStruct.hInsertAfter = TVI_LAST;		// ���Թ�� 
	tvStruct.item.mask = TVIF_TEXT;			// item ������� ��ȿȭ ����: pszText ��� ��ȿȭ
	tvStruct.item.pszText = "Total";		// Ʈ���� ������ ���ڿ�
	m_hRoot = m_treeCtrl.InsertItem(&tvStruct);	

	Tree_InsertItemStr(m_hRoot, "aaa");
	Tree_InsertItemStr(m_hRoot, "bbb");

	UpdateData(FALSE);
}


// â�� ���� ���϶� ������ �ʱ�ȭ�ؾ� �ϴ� ������� ������ 
// OnShowWindow()�� TOTO �ؿ� �ʱ�ȭ�Ѵ�. 
void CStatisticsDialog::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
	// TODO: Add your message handler code here
	if(bShow == TRUE)
	{
		// ��� �ʱ�ȭ


		// View �ʱ�ȭ 

	}
	
}

// Tree Control�� ���� item�� ����� �� ȣ��
void CStatisticsDialog::OnSelchangedTree(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	// ���� ������ �������� �ڵ� ���� ��������� �����Ѵ�.
	m_hSelectedNode = pNMTreeView->itemNew.hItem;

	// ������ �������� �̸��� ��ȭ������ ����Ʈ ���ڿ� �����Ѵ�. 
	m_strSelect = m_treeCtrl.GetItemText(m_hSelectedNode);

	// ��ȭ������ ��Ʈ�ѿ� �����͸� ����Ѵ�.
	UpdateData(FALSE);
	
	*pResult = 0;
}



BOOL CStatisticsDialog::Tree_InsertItemStr(HTREEITEM& rf_hParent, LPTSTR pStrInsert) 
{
	// TODO: Add your control notification handler code here
	TV_INSERTSTRUCT tvStruct;

	// ����ó�� - �Է��� �ؽ�Ʈ�� ����ֳ� �˻��Ѵ�.
	if(pStrInsert == "")
	{
		AfxMessageBox("�Է� ����� �ؽ�Ʈ�� �Է��ϼ���");
		return FALSE;
	}

	// ����ó�� - strInsert�� ���� Tree�� �����ϴ��� �˻��Ѵ�.

	tvStruct.hParent = rf_hParent;		// �Է¹��� �θ� item�� hParent��
	tvStruct.hInsertAfter = TVI_LAST;
	tvStruct.item.mask = TVIF_TEXT;
	tvStruct.item.pszText = pStrInsert; // �ؽ�Ʈ�� ��� �̸����� �Ѵ�.

	// ������ ������ ������ ��带 �߰��Ѵ�.
	m_treeCtrl.InsertItem(&tvStruct);

	m_treeCtrl.Expand(rf_hParent, TVE_EXPAND);

	
	return TRUE;
}
