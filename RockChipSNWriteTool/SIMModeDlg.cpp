// SIMModeDlg.cpp : implementation file
//

#include "pch.h"
#include "RockChipSNWriteTool.h"
#include "SIMModeDlg.h"
#include "afxdialogex.h"
#include "Utils.h"
extern MetaData g_Tmp;

// SIMModeDlg dialog

IMPLEMENT_DYNAMIC(SIMModeDlg, CDialogEx)

SIMModeDlg::SIMModeDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SIM_MODE, pParent)
{

}

SIMModeDlg::~SIMModeDlg()
{
}

void SIMModeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(SIMModeDlg, CDialogEx)
	ON_BN_CLICKED(IDC_CHECK1, &SIMModeDlg::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_RADIO1, &SIMModeDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &SIMModeDlg::OnBnClickedRadio2)

END_MESSAGE_MAP()


// SIMModeDlg message handlers

void SIMModeDlg::UpdateOptionsData()
{
	GetDlgItem(IDC_EDIT1)->GetWindowTextW(g_Tmp.prefix);
	GetDlgItem(IDC_EDIT2)->GetWindowTextW(g_Tmp.postfix);
	g_Tmp.len = (UINT)GetDlgItemInt(IDC_EDIT3);
	GetDlgItem(IDC_EDIT4)->GetWindowTextW(g_Tmp.strNum);
	GetDlgItem(IDC_EDIT5)->GetWindowTextW(g_Tmp.curNum);
	GetDlgItem(IDC_EDIT6)->GetWindowTextW(g_Tmp.endNum);
	g_Tmp.Remain = (UINT)GetDlgItemInt(IDC_EDIT7);
}
void SIMModeDlg::OnBnClickedCheck1()
{
	g_Tmp.Mode = 4;

}


void SIMModeDlg::OnBnClickedRadio1()
{
	g_Tmp.Option = FALSE;
}


void SIMModeDlg::OnBnClickedRadio2()
{
	g_Tmp.Option = TRUE;
}


/*void SIMModeDlg::OnNcDestroy()
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



BOOL SIMModeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	TCHAR num[5];
	((CButton*)GetDlgItem(IDC_CHECK1))->SetCheck(TRUE);
	if (g_Tmp.Option == TRUE)((CButton*)GetDlgItem(IDC_RADIO2))->SetCheck(TRUE);
	else ((CButton*)GetDlgItem(IDC_RADIO1))->SetCheck(TRUE);
	GetDlgItem(IDC_EDIT1)->SetWindowTextW(g_Tmp.prefix);
	GetDlgItem(IDC_EDIT2)->SetWindowTextW(g_Tmp.postfix);
	GetDlgItem(IDC_EDIT3)->SetWindowTextW(_itow(g_Tmp.len, num, 10));
	GetDlgItem(IDC_EDIT4)->SetWindowTextW(g_Tmp.strNum);
	GetDlgItem(IDC_EDIT5)->SetWindowTextW(g_Tmp.curNum);
	GetDlgItem(IDC_EDIT6)->SetWindowTextW(g_Tmp.endNum);
	GetDlgItem(IDC_EDIT7)->SetWindowTextW(_itow(g_Tmp.Remain, num, 10));


	// TODO:  Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}



// SIMModeDlg message handlers
