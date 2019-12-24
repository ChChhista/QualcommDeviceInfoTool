// BTModeDlg.cpp : implementation file
//

#include "pch.h"
#include "RockChipSNWriteTool.h"
#include "BTModeDlg.h"
#include "afxdialogex.h"
#include "Utils.h"
#include <string>
extern MetaData bt_g_Tmp;

// BTModeDlg dialog
BTModeDlg* BTModeDlg::btInterface = nullptr;
IMPLEMENT_DYNAMIC(BTModeDlg, CDialogEx)

BTModeDlg::BTModeDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_BT_MODE, pParent)
{

}

BTModeDlg::~BTModeDlg()
{
	delete btInterface;
}

void BTModeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(BTModeDlg, CDialogEx)
	ON_BN_CLICKED(IDC_CHECK1, &BTModeDlg::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_RADIO1, &BTModeDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &BTModeDlg::OnBnClickedRadio2)

END_MESSAGE_MAP()


// BTModeDlg message handlers
BOOL BTModeDlg::WriteCFGToDisk()
{
	bt_g_Tmp.UpdatePrivateProfile(BTAPPNAME);
	return TRUE;
}
BOOL BTModeDlg::UpdateOptionsData()
{
	CString Num;
	CString strNum;
	INT len, tmplen;
	TCHAR tmp[10] = { 0 };
	GetDlgItem(IDC_EDIT4)->GetWindowTextW(bt_g_Tmp.strNum);
	GetDlgItem(IDC_EDIT5)->GetWindowTextW(bt_g_Tmp.curNum);
	GetDlgItem(IDC_EDIT6)->GetWindowTextW(bt_g_Tmp.endNum);
	bt_g_Tmp.Remain = (UINT)GetDlgItemInt(IDC_EDIT7);
	strNum = bt_g_Tmp.strNum;
	len = strNum.GetLength();
/*	if (strNum.Find(L'G') >= 0 || strNum.Find(L'H') >= 0 || strNum.Find(L'I') >= 0 || strNum.Find(L'J') >= 0 || strNum.Find(L'K') >= 0 || strNum.Find(L'L') >= 0 || strNum.Find(L'M') >= 0 || strNum.Find(L'N') >= 0 || strNum.Find(L'O') >= 0 || strNum.Find(L'P') >= 0
		|| strNum.Find(L'Q') >= 0 || strNum.Find(L'R') >= 0 || strNum.Find(L'S') >= 0 || strNum.Find(L'T') >= 0 || strNum.Find(L'U') >= 0 || strNum.Find(L'V') >= 0 || strNum.Find(L'W') >= 0 || strNum.Find(L'X') >= 0 || strNum.Find(L'Y') >= 0 || strNum.Find(L'Z') >= 0)
	{
		AfxMessageBox(L"WIFI MAC地址只支持16进制字符");
		return FALSE;
	}
	while (len > -1)
	{
		if (iswalpha(strNum.GetAt(len)))
		{
			bt_g_Tmp.prefix = strNum.Left(len + 1);
			bt_g_Tmp.curDigital = _wtoi(strNum.Right(tmplen - len));
			bt_g_Tmp.zeroNum = L"";
			while (strNum.GetAt(++len) == L'0')	bt_g_Tmp.zeroNum.Append(L"0");
			break;
		}

		len--;
	}*/
	/*if (bt_g_Tmp.strNum.Find(bt_g_Tmp.prefix) == -1 || bt_g_Tmp.endNum.Find(bt_g_Tmp.prefix) == -1 || bt_g_Tmp.curNum.Find(bt_g_Tmp.prefix) == -1)
{
	AfxMessageBox(L"起始号码或当前号码或终止号码不包含前缀");
	return FALSE;
}

if (bt_g_Tmp.strNum.Find(bt_g_Tmp.postfix) == -1 || bt_g_Tmp.endNum.Find(bt_g_Tmp.postfix) == -1 || bt_g_Tmp.curNum.Find(bt_g_Tmp.postfix) == -1)
{
	AfxMessageBox(L"起始号码或当前号码或终止号码不包含后缀");
	return FALSE;
}
Num = bt_g_Tmp.curNum;
Num.Replace(bt_g_Tmp.prefix, L"");
Num.Replace(bt_g_Tmp.postfix, L"");
bt_g_Tmp.curDigital = _wtoi(Num);*/
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
	bt_g_Tmp.curDigital=wcstoll(strNum.GetBuffer(), NULL, 16);
	Num = bt_g_Tmp.endNum;
	len = Num.GetLength();
	if(len!=12)
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
	bt_g_Tmp.endDigital = wcstoll(Num.GetBuffer(), NULL, 16);
	GetDlgItem(IDC_EDIT7)->SetWindowTextW(std::to_wstring(bt_g_Tmp.endDigital - bt_g_Tmp.curDigital + 1).c_str());
	bt_g_Tmp.UpdatePrivateProfile(BTAPPNAME);
	return TRUE;
}
void BTModeDlg::OnBnClickedCheck1()
{
	if (((CButton*)GetDlgItem(IDC_CHECK1))->GetCheck() == BST_CHECKED) bt_g_Tmp.SetBTMode(TRUE);
	else bt_g_Tmp.SetBTMode(FALSE);

}


void BTModeDlg::OnBnClickedRadio1()
{
	bt_g_Tmp.Option = FALSE;
	GetDlgItem(IDC_EDIT4)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT5)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT6)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT7)->EnableWindow(FALSE);
	GetParent()->GetParent()->SendMessage(SetAutoMaticMode,BTMODEMESSAGE,TRUE);

}


void BTModeDlg::OnBnClickedRadio2()
{
	bt_g_Tmp.Option = TRUE;
	GetDlgItem(IDC_EDIT4)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT5)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT6)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT7)->EnableWindow(TRUE);
	GetParent()->GetParent()->SendMessage(SetAutoMaticMode, BTMODEMESSAGE, FALSE);

}


/*void BTModeDlg::OnNcDestroy()
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



BTModeDlg* BTModeDlg::GetBTModeInterface()
{
	if (btInterface == nullptr)	btInterface = new BTModeDlg;
	return btInterface;
	
}

BOOL BTModeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	TCHAR num[20];
	if(MetaData::BTMODE) ((CButton*)GetDlgItem(IDC_CHECK1))->SetCheck(TRUE);
	if (bt_g_Tmp.Option == TRUE)
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

	
	GetDlgItem(IDC_EDIT4)->SetWindowTextW(bt_g_Tmp.strNum);
	GetDlgItem(IDC_EDIT5)->SetWindowTextW(bt_g_Tmp.curNum);
	GetDlgItem(IDC_EDIT6)->SetWindowTextW(bt_g_Tmp.endNum);
	GetDlgItem(IDC_EDIT7)->SetWindowTextW(_itow(bt_g_Tmp.Remain, num, 10));


	// TODO:  Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


// BTModeDlg message handlers


void BTModeDlg::PostNcDestroy()
{

	// TODO: Add your specialized code here and/or call the base class

	CDialogEx::PostNcDestroy();
}
