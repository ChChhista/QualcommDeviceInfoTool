#pragma once


// SNModeDlg dialog

class SNModeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(SNModeDlg)

public:
	SNModeDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~SNModeDlg();
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SN_MODE };
#endif
private:
	static SNModeDlg* snInterface;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	BOOL WriteCFGToDisk();
	BOOL UpdateOptionsData();
	static SNModeDlg *GetSNModeInterface();
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnNcDestroy();
	afx_msg void OnEnChangeEdit1();
	virtual BOOL OnInitDialog();
};
