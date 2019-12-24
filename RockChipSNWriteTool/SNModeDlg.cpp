// SNModeDlg.cpp : implementation file
//

#include "pch.h"
#include "RockChipSNWriteTool.h"
#include "SNModeDlg.h"
#include "WifiModeDlg.h"
#include "afxdialogex.h"
#include "Utils.h"
#include <string>
// SNModeDlg dialog
extern MetaData g_Tmp;
IMPLEMENT_DYNAMIC(SNModeDlg, CDialogEx)
SNModeDlg* SNModeDlg::snInterface = nullptr;
SNModeDlg::SNModeDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SN_MODE, pParent)
{

}

SNModeDlg::~SNModeDlg()
{
	delete snInterface;
}

void SNModeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(SNModeDlg, CDialogEx)
	ON_BN_CLICKED(IDC_CHECK1, &SNModeDlg::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_RADIO1, &SNModeDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &SNModeDlg::OnBnClickedRadio2)
	
END_MESSAGE_MAP()


// SNModeDlg message handlers
BOOL SNModeDlg::WriteCFGToDisk()
{
	g_Tmp.UpdatePrivateProfile(APPNAME);
	return TRUE;
}
BOOL SNModeDlg::UpdateOptionsData()
{
	CString Num;
	TCHAR tmp[10] = { 0 };
	GetDlgItem(IDC_EDIT1)->GetWindowTextW(g_Tmp.prefix);
	GetDlgItem(IDC_EDIT2)->GetWindowTextW(g_Tmp.postfix);
	g_Tmp.len = (UINT)GetDlgItemInt(IDC_EDIT3);
	 GetDlgItem(IDC_EDIT4)->GetWindowTextW(g_Tmp.strNum);
	 GetDlgItem(IDC_EDIT5)->GetWindowTextW(g_Tmp.curNum);
	 GetDlgItem(IDC_EDIT6)->GetWindowTextW(g_Tmp.endNum);
	 if (g_Tmp.strNum.Find(g_Tmp.prefix) == -1||g_Tmp.endNum.Find(g_Tmp.prefix)==-1||g_Tmp.curNum.Find(g_Tmp.prefix)==-1)
	 {
		 AfxMessageBox(L"起始号码或当前号码或终止号码不包含前缀");
		 return FALSE;
	 }
	 if(g_Tmp.strNum.Find(g_Tmp.postfix) == -1|| g_Tmp.endNum.Find(g_Tmp.postfix) == -1 || g_Tmp.curNum.Find(g_Tmp.postfix) == -1)
	 {
		 AfxMessageBox(L"起始号码或当前号码或终止号码不包含后缀");
		 return FALSE;
	 }
	 Num = g_Tmp.curNum;
	 Num.Replace(g_Tmp.prefix, L"");
	 Num.Replace(g_Tmp.postfix, L"");
	 g_Tmp.curDigital = _wtoi(Num);
	 Num = g_Tmp.endNum;
	 Num.Replace(g_Tmp.prefix, L"");
	 Num.Replace(g_Tmp.postfix, L""); 
	 g_Tmp.endDigital = _wtoi(Num);
	 GetDlgItem(IDC_EDIT7)->SetWindowTextW(std::to_wstring(g_Tmp.endDigital-g_Tmp.curDigital+1).c_str());
	g_Tmp.Remain = (UINT)GetDlgItemInt(IDC_EDIT7);
	g_Tmp.UpdatePrivateProfile(APPNAME);
	return TRUE;
}
SNModeDlg* SNModeDlg::GetSNModeInterface()
{
	if (SNModeDlg::snInterface == nullptr) SNModeDlg::snInterface = new SNModeDlg;
	return SNModeDlg::snInterface;
}
void SNModeDlg::OnBnClickedCheck1()
{
	if (((CButton*)GetDlgItem(IDC_CHECK1))->GetCheck() == BST_CHECKED) g_Tmp.SetSNMode(TRUE);
	else g_Tmp.SetSNMode(FALSE);


}


void SNModeDlg::OnBnClickedRadio1()
{
	g_Tmp.Option = FALSE;
	GetDlgItem(IDC_EDIT1)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT2)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT3)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT4)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT5)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT6)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT7)->EnableWindow(FALSE);
	GetParent()->GetParent()->SendMessage(SetAutoMaticMode, SNMODEMESSAGE, TRUE);
}


void SNModeDlg::OnBnClickedRadio2()
{
	g_Tmp.Option =TRUE;
	GetDlgItem(IDC_EDIT1)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT2)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT3)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT4)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT5)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT6)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT7)->EnableWindow(TRUE);
	GetParent()->GetParent()->SendMessage(SetAutoMaticMode, SNMODEMESSAGE, FALSE);
}


/*void SNModeDlg::OnNcDestroy()
{
	CDialogEx::OnNcDestroy();
	GetDlgItem(IDC_EDIT1)->GetWindowTextW(prefix);
	GetDlgItem(IDC_EDIT2)->GetWindowTextW(postfix);
	len =(UINT)GetDlgItemInt(IDC_EDIT3);
	strNum = (UINT)GetDlgItemInt(IDC_EDIT4);
	curNum= (UINT)GetDlgItemInt(IDC_EDIT5);
	endNum= (UINT)GetDlgItemInt(IDC_EDIT6);
	Remain= (UINT)GetDlgItemInt(IDC_EDIT7);
	// TODO: Add your message handler code here
}*/



BOOL SNModeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	TCHAR num[20];
	if (MetaData::SNMODE) ((CButton*)GetDlgItem(IDC_CHECK1))->SetCheck(TRUE);
	else ((CButton*)GetDlgItem(IDC_CHECK1))->SetCheck(FALSE);
	if (g_Tmp.Option == TRUE)
	{
		((CButton*)GetDlgItem(IDC_RADIO2))->SetCheck(TRUE);
		GetDlgItem(IDC_EDIT1)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT2)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT3)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT4)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT5)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT6)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT7)->EnableWindow(TRUE);
	}
	else {
		((CButton*)GetDlgItem(IDC_RADIO1))->SetCheck(TRUE);
		GetDlgItem(IDC_EDIT1)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT2)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT3)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT4)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT5)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT6)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT7)->EnableWindow(FALSE);
	}
	GetDlgItem(IDC_EDIT1)->SetWindowTextW(g_Tmp.prefix);
	GetDlgItem(IDC_EDIT2)->SetWindowTextW(g_Tmp.postfix);
	GetDlgItem(IDC_EDIT3)->SetWindowTextW(_itow(g_Tmp.len,num,10));
	GetDlgItem(IDC_EDIT4)->SetWindowTextW(g_Tmp.strNum);
	GetDlgItem(IDC_EDIT5)->SetWindowTextW(g_Tmp.curNum);
	GetDlgItem(IDC_EDIT6)->SetWindowTextW(g_Tmp.endNum);
	GetDlgItem(IDC_EDIT7)->SetWindowTextW(_itow(g_Tmp.Remain, num, 10));


	// TODO:  Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}
