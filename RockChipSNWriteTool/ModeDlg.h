#pragma once

#include "SNModeDlg.h"
#include "WifiModeDlg.h"
#include "BTModeDlg.h"
// ModeDlg dialog

class ModeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ModeDlg)

public:
	ModeDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~ModeDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_MODE };
#endif
protected:
	CTabCtrl m_tab;
	SNModeDlg *m_dlg;
	WifiModeDlg *wifi_dlg;
	BTModeDlg* bt_dlg;
	CButton m_button[3];
	
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	afx_msg void UpdateOptions();
	afx_msg void ChangeTabSel();
	afx_msg void OnTcnSelchangeTabcontrol(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg LRESULT	OnNotifySetAutomaticMode(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
	BOOL WriteCFGToDisk();
	virtual BOOL OnInitDialog();
};
