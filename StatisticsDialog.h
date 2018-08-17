#if !defined(AFX_STATISTICSDIALOG_H__2ECC17B6_A785_4CA6_B46A_85C1648A9469__INCLUDED_)
#define AFX_STATISTICSDIALOG_H__2ECC17B6_A785_4CA6_B46A_85C1648A9469__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StatisticsDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStatisticsDialog dialog

#include "GridCtrl.h"

class CStatisticsDialog : public CDialog
{
// Construction
public:
	CStatisticsDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CStatisticsDialog)
	enum { IDD = IDD_STATISTICS_DIALOG };
	CTreeCtrl	m_treeCtrl;
	CGridCtrl	m_gridCtrl;
	CString		m_strSelect;

	//}}AFX_DATA
	

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStatisticsDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CStatisticsDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnSelchangedTree(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()


public:
	// member for tree control
	HTREEITEM m_hRoot;
	HTREEITEM m_hSelectedNode;

	// member for grid control
	int		m_nFixCols;
	int		m_nFixRows;
	int		m_nCols;
	int		m_nRows;
	BOOL	m_bEditable;
/*
	BOOL	m_bHorzLines;
	BOOL	m_bListMode;
	BOOL	m_bVertLines;
	BOOL	m_bSelectable;
	BOOL	m_bAllowColumnResize;
	BOOL	m_bAllowRowResize;
	BOOL	m_bHeaderSort;
	BOOL	m_bReadOnly;
	BOOL	m_bItalics;
	BOOL	m_btitleTips;
	BOOL	m_bSingleSelMode;	
*/
	BOOL 	InitMember();
	BOOL 	InitView();
	BOOL 	Tree_InsertItemStr(HTREEITEM& rfParent, LPTSTR pStrInsert); 

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STATISTICSDIALOG_H__2ECC17B6_A785_4CA6_B46A_85C1648A9469__INCLUDED_)
