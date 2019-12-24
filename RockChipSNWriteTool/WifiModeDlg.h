#pragma once


// WifiModeDlg dialog

class WifiModeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(WifiModeDlg)

public:
	WifiModeDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~WifiModeDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_WIFI_MODE };
#endif
private:
	static WifiModeDlg* wifiInterface;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	
	DECLARE_MESSAGE_MAP()
public:
	BOOL WriteCFGToDisk();
	static WifiModeDlg* GetWifiInterface();
	BOOL UpdateOptionsData();
	virtual BOOL OnInitDialog();
};
