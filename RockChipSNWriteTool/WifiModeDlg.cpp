// WifiModeDlg.cpp : implementation file
//

#include "pch.h"
#include "RockChipSNWriteTool.h"
#include "WifiModeDlg.h"
#include "afxdialogex.h"
#include "utils.h"
#include <string>
extern MetaData wifi_g_Tmp;
// WifiModeDlg dialog

IMPLEMENT_DYNAMIC(WifiModeDlg, CDialogEx)
WifiModeDlg* WifiModeDlg::wifiInterface = nullptr;
WifiModeDlg::WifiModeDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_WIFI_MODE, pParent)
{

}

WifiModeDlg::~WifiModeDlg()
{
	delete wifiInterface;
}

void WifiModeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(WifiModeDlg, CDialogEx)
	ON_BN_CLICKED(IDC_CHECK1, &WifiModeDlg::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_RADIO1, &WifiModeDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &WifiModeDlg::OnBnClickedRadio2)

END_MESSAGE_MAP()


// WifiModeDlg message handlers
BOOL WifiModeDlg::WriteCFGToDisk()
{
	wifi_g_Tmp.UpdatePrivateProfile(WIFIAPPNAME);
	return TRUE;
}
WifiModeDlg* WifiModeDlg::GetWifiInterface()
{
	if (WifiModeDlg::wifiInterface == nullptr) WifiModeDlg::wifiInterface = new WifiModeDlg;
	return WifiModeDlg::wifiInterface;
}

BOOL WifiModeDlg::UpdateOptionsData()
{
	CString strNum;
	CString Num;
	TCHAR tmp[10] = { 0 };
	PTCHAR serial = NULL;
	INT len=-1,tmplen = -1;
	GetDlgItem(IDC_EDIT4)->GetWindowTextW(wifi_g_Tmp.strNum);
	GetDlgItem(IDC_EDIT5)->GetWindowTextW(wifi_g_Tmp.curNum);
	GetDlgItem(IDC_EDIT6)->GetWindowTextW(wifi_g_Tmp.endNum);
	wifi_g_Tmp.Remain = (UINT)GetDlgItemInt(IDC_EDIT7);
	strNum = wifi_g_Tmp.strNum;
	len = tmplen = strNum.GetLength();
	if (len != 12)
	{
		AfxMessageBox(L"WIFI地址必须为12位");
		return FALSE;
	}
	for (int i = 0; i < len - 1; i++)
	{
		if (!iswxdigit(strNum.GetAt(i)))
		{
			AfxMessageBox(L"起始序列号包含非十六进制字符");
			return FALSE;
		}
	}
	wifi_g_Tmp.curDigital = wcstoll(strNum.GetBuffer(), NULL, 16);
	Num = wifi_g_Tmp.endNum;
	len = Num.GetLength();
	if (len != 12)
	{
		AfxMessageBox(L"WIFI地址必须为12位");
		return FALSE;
	}
	for (int i = 0; i < len - 1; i++)
	{
		if (!iswxdigit(Num.GetAt(i)))
		{
			AfxMessageBox(L"结束序列号包含非十六进制字符");
			return FALSE;
		}
	}
	wifi_g_Tmp.endDigital = wcstoll(Num.GetBuffer(), NULL, 16);
/*	if (strNum.Find(L'G')>=0 || strNum.Find(L'H') >= 0 || strNum.Find(L'I') >= 0 || strNum.Find(L'J') >= 0 || strNum.Find(L'K') >= 0 || strNum.Find(L'L') >= 0 || strNum.Find(L'M') >= 0 || strNum.Find(L'N') >= 0 || strNum.Find(L'O') >= 0 || strNum.Find(L'P') >= 0
		|| strNum.Find(L'Q') >= 0 || strNum.Find(L'R') >= 0 || strNum.Find(L'S') >= 0 || strNum.Find(L'T') >= 0 || strNum.Find(L'U') >= 0 || strNum.Find(L'V') >= 0 || strNum.Find(L'W') >= 0 || strNum.Find(L'X') >= 0 || strNum.Find(L'Y') >= 0 || strNum.Find(L'Z') >= 0)
	{
		AfxMessageBox(L"WIFI MAC地址只支持16进制字符");
		return FALSE;
	}
	while (len > -1)
	{
		if (iswalpha(strNum.GetAt(len)))
		{
			wifi_g_Tmp.prefix = strNum.Left(len + 1);
			wifi_g_Tmp.curDigital = _wtoi(strNum.Right(tmplen - len));
			wifi_g_Tmp.zeroNum = L"";
			while (strNum.GetAt(++len) == L'0') wifi_g_Tmp.zeroNum.Append(L"0");
			break;
		}

		len--;
	}


	if (wifi_g_Tmp.strNum.Find(wifi_g_Tmp.prefix) == -1 || wifi_g_Tmp.endNum.Find(wifi_g_Tmp.prefix) == -1 || wifi_g_Tmp.curNum.Find(wifi_g_Tmp.prefix) == -1)
	{
		AfxMessageBox(L"起始号码或当前号码或终止号码不包含前缀");
		return FALSE;
	}
	if (wifi_g_Tmp.strNum.Find(wifi_g_Tmp.postfix) == -1 || wifi_g_Tmp.endNum.Find(wifi_g_Tmp.postfix) == -1 || wifi_g_Tmp.curNum.Find(wifi_g_Tmp.postfix) == -1)
	{
		AfxMessageBox(L"起始号码或当前号码或终止号码不包含后缀");
		return FALSE;
	}
	Num = wifi_g_Tmp.curNum;
	Num.Replace(wifi_g_Tmp.prefix, L"");
	Num.Replace(wifi_g_Tmp.postfix, L"");
	wifi_g_Tmp.curDigital = _wtoi(Num);*/
	GetDlgItem(IDC_EDIT7)->SetWindowTextW(std::to_wstring(wifi_g_Tmp.endDigital - wifi_g_Tmp.curDigital + 1).c_str());
	wifi_g_Tmp.Remain = (UINT)GetDlgItemInt(IDC_EDIT7);
	wifi_g_Tmp.UpdatePrivateProfile(WIFIAPPNAME);
	return TRUE;
}
void WifiModeDlg::OnBnClickedCheck1()
{
	if(((CButton*)GetDlgItem(IDC_CHECK1))->GetCheck()==BST_CHECKED) wifi_g_Tmp.SetWIFIMode(TRUE);
	else wifi_g_Tmp.SetWIFIMode(FALSE);
	

}


void WifiModeDlg::OnBnClickedRadio1()
{
	wifi_g_Tmp.Option = FALSE;
	GetDlgItem(IDC_EDIT4)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT5)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT6)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT7)->EnableWindow(FALSE);
	GetParent()->GetParent()->SendMessage(SetAutoMaticMode, WIFIMODEMESSAGE, TRUE);
}


void WifiModeDlg::OnBnClickedRadio2()
{
	wifi_g_Tmp.Option = TRUE;
	GetDlgItem(IDC_EDIT4)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT5)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT6)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT7)->EnableWindow(TRUE);
	GetParent()->GetParent()->SendMessage(SetAutoMaticMode, WIFIMODEMESSAGE, FALSE);
}


/*void WifiModeDlg::OnNcDestroy()
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



BOOL WifiModeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	TCHAR num[20];
	if (MetaData::WIFIMODE) ((CButton*)GetDlgItem(IDC_CHECK1))->SetCheck(TRUE);
	if (wifi_g_Tmp.Option == TRUE)
	{
		((CButton*)GetDlgItem(IDC_RADIO2))->SetCheck(TRUE);
		GetDlgItem(IDC_EDIT4)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT5)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT6)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT7)->EnableWindow(TRUE);
	}
	else {
		((CButton*)GetDlgItem(IDC_RADIO1))->SetCheck(TRUE);
		GetDlgItem(IDC_EDIT4)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT5)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT6)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT7)->EnableWindow(FALSE);
	}
	GetDlgItem(IDC_EDIT4)->SetWindowTextW(wifi_g_Tmp.strNum);
	GetDlgItem(IDC_EDIT5)->SetWindowTextW(wifi_g_Tmp.curNum);
	GetDlgItem(IDC_EDIT6)->SetWindowTextW(wifi_g_Tmp.endNum);
	GetDlgItem(IDC_EDIT7)->SetWindowTextW(_itow(wifi_g_Tmp.Remain, num, 10));


	// TODO:  Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


// WifiModeDlg message handlers
