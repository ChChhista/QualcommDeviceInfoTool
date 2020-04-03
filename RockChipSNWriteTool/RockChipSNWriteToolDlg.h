
// RockChipSNWriteToolDlg.h : header file
//

#pragma once
#include "Windows.h"
#include "ModeDlg.h"
// CRockChipSNWriteToolDlg dialog
class CRockChipSNWriteToolDlg : public CDialogEx
{
// Construction
public:
	CRockChipSNWriteToolDlg(CWnd* pParent = nullptr);	// standard constructor
	~CRockChipSNWriteToolDlg();
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ROCKCHIPSNWRITETOOL_DIALOG };
#endif
	enum opeMode
	{
		__WRITE = 1,
		__READ = 2,
	};
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:

	HICON m_hIcon;
	CMenu m_menu;
	CStatic m_label[16];
	CEdit m_edit[7];
	CButton m_button[8];
	CListBox m_listbox;
	BOOL AutoGenSN = false;
	ModeDlg modeDlg;

	HANDLE p_Qualcom = INVALID_HANDLE_VALUE;
	HANDLE m_serialp = NULL;
	// Generated message map functions
	virtual BOOL OnInitDialog();
	virtual void PostNcDestroy();
	BOOL ReadFromSerialPort(TCHAR*);
	BOOL RegisterDeviceFilter(DWORD t_Device);
	BOOL WriteToSerialPortReqDispatcher();
	BOOL WriteToSerialPortReqHandler1();
	BOOL WriteToSerialPortReqHandler2();
	BOOL WriteToSerialPortReqHandler3();
	afx_msg LRESULT	OnNotifySetAutomaticMode(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSetToAutomaticMode(WPARAM wParam, LPARAM lParam);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg LRESULT UsbDeviceMsgHandler(WPARAM wParam, LPARAM lParam);
	afx_msg void OnWriteSNButtonClicked();
	afx_msg void OnSim1HotPlugClicked();
	afx_msg void OnSim2HotPlugClicked();
	afx_msg void OnSim1NotHotPlugClicked();
	afx_msg void OnSim2NotHotPlugClicked();
	afx_msg void OnReadSimStateClicked();
	afx_msg void OnPaint();
	afx_msg void OnModeClicked();
	afx_msg void OnReadClicked();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
};
