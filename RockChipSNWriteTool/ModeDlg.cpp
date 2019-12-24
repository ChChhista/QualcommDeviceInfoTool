// ModeDlg.cpp : implementation file
//

#include "pch.h"
#include "RockChipSNWriteTool.h"
#include "ModeDlg.h"
#include "Utils.h"
extern MetaData g_Tmp;
IMPLEMENT_DYNAMIC(ModeDlg, CDialogEx)
ModeDlg::ModeDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_MODE, pParent)
{
	

}

ModeDlg::~ModeDlg()
{
}

void ModeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ModeDlg, CDialogEx)
	ON_BN_CLICKED(0X4001,UpdateOptions)
	ON_NOTIFY(TCN_SELCHANGE, 0x1000,OnTcnSelchangeTabcontrol)
	ON_MESSAGE(SetAutoMaticMode, OnNotifySetAutomaticMode)
END_MESSAGE_MAP()
BOOL ModeDlg::WriteCFGToDisk()
{
	m_dlg->WriteCFGToDisk();
	wifi_dlg->WriteCFGToDisk();
	bt_dlg->WriteCFGToDisk();
	return TRUE;
}
LRESULT	ModeDlg::OnNotifySetAutomaticMode(WPARAM wParam, LPARAM lParam)
{
	GetParent()->SendMessage(SetAutoMaticMode, wParam, lParam);
	return 1;
}
void ModeDlg::OnTcnSelchangeTabcontrol(NMHDR* pNMHDR, LRESULT* pResult)
{
	
	if (m_tab.GetCurSel() == 0)
	{
		m_dlg->ShowWindow(SW_SHOW);
		wifi_dlg->ShowWindow(SW_HIDE);
		bt_dlg->ShowWindow(SW_HIDE);


	}
	else if (m_tab.GetCurSel() == 1)
	{
		m_dlg->ShowWindow(SW_HIDE);
		wifi_dlg->ShowWindow(SW_SHOW);
		bt_dlg->ShowWindow(SW_HIDE);

	}
	else if (m_tab.GetCurSel() == 2)
	{
		m_dlg->ShowWindow(SW_HIDE);
		wifi_dlg->ShowWindow(SW_HIDE);
		bt_dlg->ShowWindow(SW_SHOW);

	}
	return;
}
// ModeDlg message handlers
void ModeDlg::ChangeTabSel()
{
	return;
}
void ModeDlg::UpdateOptions()
{
	if (!m_dlg->UpdateOptionsData()) return ;
	if (!wifi_dlg->UpdateOptionsData()) return ;
	if (!bt_dlg->UpdateOptionsData()) return;
	EndDialog(0x0);
}
BOOL ModeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CRect w_rect = { 0 };
	CRect w_dlg = { 0 };
	GetClientRect(w_rect);
	MoveWindow(w_rect.left+550, w_rect.top+300, 500, 500);

	m_tab.Create(WS_CHILD | WS_VISIBLE, CRect(10, 10, 500, 300), this, 0x1000);
	m_tab.GetClientRect(w_rect);
	m_tab.GetItemRect(0,&w_dlg);
	m_tab.InsertItem(0, L"SN");
	m_tab.InsertItem(1, L"WIFI MAC");
	m_tab.InsertItem(2, L"BTMAC");
	w_rect.left += 0;
	w_rect.top += 20;
	m_dlg = SNModeDlg::GetSNModeInterface();
	m_dlg->Create(IDD_DIALOG1, &m_tab);
	m_dlg->MoveWindow(&w_rect);
	m_dlg->ShowWindow(SW_HIDE);
	wifi_dlg=WifiModeDlg::GetWifiInterface();
	wifi_dlg->Create(IDD_WIFI_MODE, &m_tab);
	wifi_dlg->MoveWindow(&w_rect);
	wifi_dlg->ShowWindow(SW_HIDE);
	bt_dlg = BTModeDlg::GetBTModeInterface();
	bt_dlg->Create(IDD_BT_MODE, &m_tab);
	bt_dlg->MoveWindow(&w_rect);
	bt_dlg->ShowWindow(SW_HIDE);
	m_button[0].Create(L"Confirm", WS_CHILD | WS_VISIBLE, CRect(10, 300,100, 330), this,0x4001);
	/*switch (g_Tmp.Mode)
	{
	case 1:
		m_tab.SetCurSel(0);
		m_dlg->ShowWindow(SW_SHOW);
		break;
	case 2:
		m_tab.SetCurSel(1);
		wifi_dlg->ShowWindow(SW_SHOW);
		break;
	case 3:
		m_tab.SetCurSel(2);
		bt_dlg->ShowWindow(SW_SHOW);
		break;
	}*/
	m_dlg->ShowWindow(SW_SHOW);
	// TODO:  Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}
