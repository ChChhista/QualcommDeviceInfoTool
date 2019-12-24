#pragma once


// BTModeDlg dialog

class BTModeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(BTModeDlg)

public:
	BTModeDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~BTModeDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BT_MODE };
#endif
private:
	static BTModeDlg* btInterface;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	
	BOOL UpdateOptionsData();
	BOOL WriteCFGToDisk();
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnNcDestroy();
	afx_msg void OnEnChangeEdit1();
	static  BTModeDlg *GetBTModeInterface();
	virtual BOOL OnInitDialog();
	virtual void PostNcDestroy();
};
