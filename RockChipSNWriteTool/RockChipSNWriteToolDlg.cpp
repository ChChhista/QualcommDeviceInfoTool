
// RockChipSNWriteToolDlg.cpp : implementation file
//
#include "pch.h"
#include "framework.h"
#include "RockChipSNWriteTool.h"
#include "RockChipSNWriteToolDlg.h"
#include "afxdialogex.h"
#include "Dbt.h"
#include <initguid.h>
#include "Usbiodef.h"
#include "Ntddmodm.h"
#include <vector>
#include "Utils.h"
#include "VMProtectSDK.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


static INT opeMode = CRockChipSNWriteToolDlg::__WRITE;
// CAboutDlg dialog used for App About
MetaData g_Tmp;
MetaData wifi_g_Tmp;
MetaData bt_g_Tmp;
BOOL MetaData::SNMODE = 0;
BOOL MetaData::WIFIMODE = 0;
BOOL MetaData::BTMODE = 0;
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CRockChipSNWriteToolDlg dialog



CRockChipSNWriteToolDlg::CRockChipSNWriteToolDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ROCKCHIPSNWRITETOOL_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	
}

CRockChipSNWriteToolDlg::~CRockChipSNWriteToolDlg()
{
}

void CRockChipSNWriteToolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CRockChipSNWriteToolDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(ID_WRITE_SN_BUTTON, OnWriteSNButtonClicked)
	ON_BN_CLICKED(ID_SIM_1_HOT_PLUG, OnSim1HotPlugClicked)
	ON_BN_CLICKED(ID_SIM_2_HOT_PLUG, OnSim2HotPlugClicked)
	ON_BN_CLICKED(ID_SIM_1_NOT_HOT_PLUG, OnSim1NotHotPlugClicked)
	ON_BN_CLICKED(ID_SIM_2_NOT_HOT_PLUG, OnSim2NotHotPlugClicked)
	ON_BN_CLICKED(ID_READ_SIM_STATE, OnReadSimStateClicked)
	ON_MESSAGE(WM_DEVICECHANGE, UsbDeviceMsgHandler)
	//ON_REGISTERED_MESSAGE(SetAutoMaticMode, OnSetToAutomaticMode)
	ON_MESSAGE(SetAutoMaticMode, OnNotifySetAutomaticMode)
	ON_COMMAND(ID_32771,OnModeClicked)
	ON_COMMAND(ID_32772, OnReadClicked)
END_MESSAGE_MAP()
LRESULT	CRockChipSNWriteToolDlg::OnNotifySetAutomaticMode(WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{
	case SNMODEMESSAGE:
		if (lParam)
		{
			m_edit[0].EnableWindow(TRUE);
			m_edit[0].SetWindowTextW(L"");
		}
		else
		{
			m_edit[0].EnableWindow(FALSE);
			m_edit[0].SetWindowTextW(L"已设置为自动");
		}

		break;
	case WIFIMODEMESSAGE:
		if (lParam)
		{
			m_edit[1].EnableWindow(TRUE);
			m_edit[1].SetWindowTextW(L"");
		}

		else
		{
			m_edit[1].EnableWindow(FALSE);
			m_edit[1].SetWindowTextW(L"已设置为自动");
		}
		break;
	case BTMODEMESSAGE:
		if (lParam)
		{
			m_edit[3].EnableWindow(TRUE);
			m_edit[3].SetWindowTextW(L"");
		}

		else
		{
			m_edit[3].EnableWindow(FALSE);
			m_edit[3].SetWindowTextW(L"已设置为自动");
		}

		break;
	}

	return 1;
}
void CRockChipSNWriteToolDlg::OnSim1HotPlugClicked()
{
	DWORD ret = -1;
	CHAR tmp[50] = { 0 };
	if (p_Qualcom == INVALID_HANDLE_VALUE)
	{
		AfxMessageBox(L"调制解调器端口读取失败");
		return;
	}
	WriteFile(p_Qualcom, SIM1HOTPLUGCMD, strlen(SIM1HOTPLUGCMD), &ret, NULL);
	ReadFile(p_Qualcom, tmp, 50, &ret, NULL);
	m_listbox.AddString(L"写入SIM1可热插拔成功！");
}
void CRockChipSNWriteToolDlg::OnSim2HotPlugClicked()
{
	DWORD ret = -1;
	CHAR tmp[50] = { 0 };
	if (p_Qualcom == INVALID_HANDLE_VALUE)
	{
		AfxMessageBox(L"调制解调器端口读取失败");
		return;
	}
	WriteFile(p_Qualcom, SIM2HOTPLUGCMD, strlen(SIM2HOTPLUGCMD), &ret, NULL);
	ReadFile(p_Qualcom, tmp, 50, &ret, NULL);
	m_listbox.AddString(L"写入SIM2可热插拔成功！");
}
void CRockChipSNWriteToolDlg::OnSim1NotHotPlugClicked()
{
	DWORD ret = -1;
	CHAR tmp[50] = { 0 };
	if (p_Qualcom == INVALID_HANDLE_VALUE)
	{
		AfxMessageBox(L"调制解调器端口读取失败");
		return;
	}
	WriteFile(p_Qualcom, SIM1NOTHOTPLUGCMD, strlen(SIM1NOTHOTPLUGCMD), &ret, NULL);
	ReadFile(p_Qualcom, tmp, 50, &ret, NULL);
	m_listbox.AddString(L"写入SIM1不可热插拔成功！");
	return;
}
void CRockChipSNWriteToolDlg::OnSim2NotHotPlugClicked()
{
	DWORD ret = -1;
	CHAR tmp[50] = { 0 };
	if (p_Qualcom == INVALID_HANDLE_VALUE)
	{
		AfxMessageBox(L"调制解调器端口读取失败");
		return;
	}
	WriteFile(p_Qualcom, SIM2NOTHOTPLUGCMD, strlen(SIM2NOTHOTPLUGCMD), &ret, NULL);
	ReadFile(p_Qualcom, tmp, 50, &ret, NULL);
	m_listbox.AddString(L"写入SIM2不可热插拔成功！");
	return;
}
void CRockChipSNWriteToolDlg::OnReadSimStateClicked()
{
	DWORD ret = -1;
	DWORD index = 0;
	CHAR SimState[MAX_PATH] = {0};
	TCHAR tmp[10] = { 0 };
	if (p_Qualcom == INVALID_HANDLE_VALUE)
	{
		AfxMessageBox(L"调制解调器端口读取失败");
		return;
	}
	WriteFile(p_Qualcom, READSIMSTATE, strlen(READSIMSTATE), &ret, NULL);
	ReadFile(p_Qualcom, SimState, MAX_PATH, &ret, NULL);
	while (SimState[index] != ':') index++;
	if (SimState[index + 2] == '0') GetDlgItem(0x1009)->SetWindowTextW(L"SIM1非热插拔");
	else GetDlgItem(0x1009)->SetWindowTextW(L"SIM1热插拔");
	if(SimState[index + 5] == '0') GetDlgItem(0x1010)->SetWindowTextW(L"SIM2非热插拔");
	else 	GetDlgItem(0x1010)->SetWindowTextW(L"SIM2热插拔");
	return;
}
BOOL CRockChipSNWriteToolDlg::RegisterDeviceFilter(DWORD t_Device)
{
	DEV_BROADCAST_DEVICEINTERFACE dBPA;
	ZeroMemory(&dBPA, sizeof(dBPA));
	dBPA.dbcc_size = sizeof(dBPA);
	dBPA.dbcc_devicetype = t_Device;
	dBPA.dbcc_classguid = GUID_DEVINTERFACE_MODEM;
	HDEVNOTIFY hDevNotify = RegisterDeviceNotification(this->GetSafeHwnd(), &dBPA, DEVICE_NOTIFY_WINDOW_HANDLE);
	if (!hDevNotify) return false;
	return true;

}
BOOL CRockChipSNWriteToolDlg::WriteToSerialPortReqHandler1()
{
	CHAR psz_buffer[50] = { 0 };
	DWORD WrittenBytes = -1;
	TCHAR Comment[MAX_PATH] = { 0 };
	CHAR Command[MAX_PATH] = { 0 };
	CHAR CMDTmp[256] = { 0 };
	PCHAR dlgText = NULL;
	TCHAR tmp[MAX_PATH] = { 0 };
	TCHAR prefix[20] = {0};
	TCHAR postfix[20] = { 0 };
	CString strSN = g_Tmp.strNum;
	CString curSN = g_Tmp.curNum;
	CString endSN = g_Tmp.endNum;
	LONGLONG Num = 0, endNum = 0;
	INT num = g_Tmp.len;
	//DWORD Mode = g_Tmp.Mode;
	if (p_Qualcom == INVALID_HANDLE_VALUE)
	{
		AfxMessageBox(L"Modem句柄错误");
		return FALSE;
	}
	if (::opeMode == CRockChipSNWriteToolDlg::__READ)
	{
		sprintf(Command, READSNNUMBERCMD);
		WriteFile(p_Qualcom, Command, strlen(Command), &WrittenBytes, NULL);
		ReadFile(p_Qualcom, Command, MAX_PATH, &WrittenBytes, NULL);
		//swprintf_s(tmp, L"写入设备序列号%lld成功！", Num);
		m_listbox.AddString(tmp);
		g_Tmp.curDigital++;
		return TRUE;
	}
	/*if (lstrlenW(prefix)!=0&&strSN.Find(prefix) == -1)
	{
		AfxMessageBox(L"起始号码不包含前缀"); return FALSE;
	}
	if (lstrlenW(postfix) != 0 && strSN.Find(postfix) == -1)
	{
		AfxMessageBox(L"起始号码不包含后缀！"); return FALSE;
	}
	strSN.Replace(prefix, L"");
	strSN.Replace(postfix, L"");
	endSN.Replace(prefix, L"");
	endSN.Replace(postfix, L"");
	Num = _wtoi(strSN);
	endNum = _wtoi(endSN);
	if (Num > endNum)
	{
		AfxMessageBox(L"起始号码大于终止号码");
		return FALSE;
	}
	for (int i = Num; i < endNum; i++)
	{*/
#ifndef _DEBUG
	VMProtectBegin("Manual Write SN");
#endif
	if (MetaData::SNMODE)
	{
		Num = g_Tmp.curDigital;
		endNum = g_Tmp.endDigital;
		ZeroMemory(Command, sizeof(CHAR) * MAX_PATH);
		if (Num > endNum) { AfxMessageBox(L"序列号已经写完"); return FALSE; }
		if (!g_Tmp.Option)
		{
			::GetWindowTextA(m_edit[0].GetSafeHwnd(), psz_buffer, sizeof(CHAR) * 50);
			
			sprintf(Command, SNCOMMAND, psz_buffer);
		}else sprintf(Command, "AT+SYSCMD=lserialn%ws%lld%ws\r", g_Tmp.prefix.GetBuffer(), Num, g_Tmp.postfix.GetBuffer());
		WriteFile(p_Qualcom, Command, strlen(Command), &WrittenBytes, NULL);
		ReadFile(p_Qualcom, Command, MAX_PATH, &WrittenBytes, NULL);
		swprintf_s(tmp, L"写入设备序列号%lld成功！", Num);
		m_listbox.AddString(tmp);
		g_Tmp.curDigital++;
	}
	if (MetaData::WIFIMODE)
	{
		Num = wifi_g_Tmp.curDigital;
		endNum = wifi_g_Tmp.endDigital;
		ZeroMemory(Command, sizeof(CHAR) * MAX_PATH);
		if (Num > endNum) { AfxMessageBox(L"序列号已经写完"); return FALSE; }
		if (!wifi_g_Tmp.Option)
		{
			::GetWindowTextA(m_edit[1].GetSafeHwnd(), psz_buffer, sizeof(CHAR) * 50);
			dlgText = psz_buffer;
			if (strlen(psz_buffer) != 12)
			{
				AfxMessageBox(L"序列号长度必须为12个字节");
				return FALSE;
			}
			while (isxdigit(*dlgText)) dlgText++;
			if ((dlgText - psz_buffer) != 12)
			{
				AfxMessageBox(L"序列号只能由16进制字符构成");
				return  FALSE;
			}
			sprintf(Command,WIFISNCOMMAND, psz_buffer);	
		}
		else sprintf(Command, "AT+LCTSN=1,12,\"%llx\"\r",Num);
		WriteFile(p_Qualcom, Command, strlen(Command), &WrittenBytes, NULL);
		ReadFile(p_Qualcom, Command, MAX_PATH, &WrittenBytes, NULL);
		swprintf_s(Comment, L"写入WIFI序列号 %llx成功！", Num);
		if (strstr(Command, "ERROR"))
		{
			AfxMessageBox(L"Wifi 序列号写入失败");
			m_listbox.AddString(L"Wifi 序列号写入失败");
			return FALSE;
		}
		m_listbox.AddString(Comment);
		wifi_g_Tmp.curDigital++;
	}
	if (MetaData::BTMODE)
	{
		Num = bt_g_Tmp.curDigital;
		endNum = bt_g_Tmp.endDigital;
		ZeroMemory(Command, sizeof(CHAR) * MAX_PATH);
		if (Num > endNum) { AfxMessageBox(L"序列号已经写完"); return FALSE; }
		if (!bt_g_Tmp.Option)
		{
			::GetWindowTextA(m_edit[3].GetSafeHwnd(), psz_buffer, sizeof(CHAR) * 50);
			dlgText = psz_buffer;
			if (strlen(psz_buffer) != 12)
			{
				AfxMessageBox(L"序列号长度必须为12个字节");
				return FALSE;
			}
			while (isxdigit(*dlgText)) dlgText++;
			if ((dlgText - psz_buffer) != 12)
			{
				AfxMessageBox(L"序列号只能由16进制字符构成");
				return  FALSE;
			}
			sprintf(Command,BTSNCOMMAND, psz_buffer);
		}else sprintf(Command, "AT+LCTSN=1,10,\"%llx\"\r", Num);
		WriteFile(p_Qualcom, Command, strlen(Command), &WrittenBytes, NULL);
		ReadFile(p_Qualcom, Command, MAX_PATH, &WrittenBytes, NULL);
		bt_g_Tmp.curDigital++;
		swprintf_s(Comment, L"写入蓝牙序列号 %llx成功！", Num);
		if (strstr(Command, "ERROR"))
		{
			AfxMessageBox(L"Wifi 序列号写入失败");
			m_listbox.AddString(L"Wifi 序列号写入失败");
			return FALSE;
		}
		m_listbox.AddString(Comment);
		m_listbox.SetCurSel(m_listbox.GetCount() - 1);
		
	}
#ifndef _DEBUG
	VMProtectEnd();
#endif
	


	return TRUE;
}
BOOL CRockChipSNWriteToolDlg::WriteToSerialPortReqHandler2()
{
	this->WriteToSerialPortReqHandler1();
	return TRUE;
}
BOOL CRockChipSNWriteToolDlg::WriteToSerialPortReqHandler3()
{
	this->WriteToSerialPortReqHandler1();
	return TRUE;
}
BOOL CRockChipSNWriteToolDlg::WriteToSerialPortReqDispatcher()
{
	this->WriteToSerialPortReqHandler1();
	/*switch (g_Tmp.Mode)
	{
	case 1:
		this->WriteToSerialPortReqHandler1();
		break;
	case 2:
		this->WriteToSerialPortReqHandler2();
		break;
	case 3:
		this->WriteToSerialPortReqHandler3();
		break;
	case 4:
		break;
	case 5 :
		break;
	}*/
	return TRUE;
}
BOOL CRockChipSNWriteToolDlg::ReadFromSerialPort(TCHAR*)
{
	return TRUE;
}
// CRockChipSNWriteToolDlg message handlers
void CRockChipSNWriteToolDlg::OnModeClicked()
{
	modeDlg.DoModal();
}
void CRockChipSNWriteToolDlg::OnReadClicked()
{
	//::opeMode = CRockChipSNWriteToolDlg::__READ;
	//m_button[2].SetWindowTextW(L"READ");

}
void CRockChipSNWriteToolDlg::OnWriteSNButtonClicked()
{
	this->WriteToSerialPortReqDispatcher();
}
LRESULT CRockChipSNWriteToolDlg::UsbDeviceMsgHandler(WPARAM wParam, LPARAM lParam)
{
		TRACE(L"Usb Device Change Start:");
		PDEV_BROADCAST_HDR pdhdr = NULL; 
		PDEV_BROADCAST_DEVICEINTERFACE_A pport = NULL;
		INT index = 0;
		CString modem;
CString seperator = L"#";
CString key_Path;
CString Compath = L"\\\\.\\";
TCHAR ComValue[10] = { 0 };
DWORD ret = -1;
DWORD LPTYPE = REG_SZ;
LONG p_length = -1;
LONG lRes = -1;
HKEY h_Key = NULL;
CHAR* writeSN = "AT+SYSCMD=lserialnZhongZongbei123456\r";
DCB dcbSerialParams = { 0 };
dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
dcbSerialParams.BaudRate = CBR_115200;
dcbSerialParams.ByteSize = 8;
dcbSerialParams.StopBits = ONESTOPBIT;
dcbSerialParams.Parity = NOPARITY;
dcbSerialParams.fRtsControl = RTS_CONTROL_ENABLE;
dcbSerialParams.fBinary = 0;
COMMTIMEOUTS timeouts = { 0 };
timeouts.ReadIntervalTimeout = 50;
timeouts.ReadTotalTimeoutConstant = 50;
timeouts.ReadTotalTimeoutMultiplier = 10;
timeouts.WriteTotalTimeoutConstant = 50;
timeouts.WriteTotalTimeoutMultiplier = 10;
std::vector<CString> part;
char tmp[1024] = { 0 };
if (wParam == DBT_DEVICEREMOVECOMPLETE)
{
	pport = (PDEV_BROADCAST_DEVICEINTERFACE_A)lParam;
	modem = (PTCHAR)pport->dbcc_name;
	if (modem.Find(L"PID_9091")!=-1)
	{
		CloseHandle(p_Qualcom);
		p_Qualcom = INVALID_HANDLE_VALUE;
		m_label[14].SetWindowTextW(L"设备移除成功");
	}

}
if (wParam == DBT_DEVICEARRIVAL)
{
	pdhdr = (PDEV_BROADCAST_HDR)lParam;
	switch (pdhdr->dbch_devicetype)
	{
	case DBT_DEVTYP_DEVICEINTERFACE:
#ifndef _DEBUG
		VMProtectBegin("PortDeviceDetection");
#endif
		if (p_Qualcom != INVALID_HANDLE_VALUE) return 1;
		pport = (PDEV_BROADCAST_DEVICEINTERFACE_A)lParam;
		modem = (PTCHAR)pport->dbcc_name;
		while (index < modem.GetLength())
		{
			part.push_back(modem.Tokenize(seperator, index));
		}
		key_Path = L"SYSTEM\\CurrentControlSet\\Enum\\USB\\" + part[1] + L"\\" + part[2] + L"\\Device Parameters";
		lRes = RegOpenKeyExW(HKEY_LOCAL_MACHINE, key_Path.GetBuffer(), 0, KEY_READ | KEY_WOW64_64KEY, &h_Key);
		ret = RegQueryValueEx(h_Key, L"PortName", 0, &LPTYPE, (LPBYTE)ComValue, (LPDWORD)&p_length);
		TRACE(L"Get Port Name %s", ComValue);
		RegCloseKey(h_Key);
		Compath += ComValue;
		p_Qualcom = CreateFile(Compath, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, 0, 0);
		if (p_Qualcom == INVALID_HANDLE_VALUE)
		{
			AfxMessageBox(L"Open Com Port Failed");
			ret=GetLastError();
		}
		else
		{
			m_label[14].SetWindowTextW(L"设备就绪");
			m_listbox.AddString(L"初始化Modem成功");
			SetupComm(p_Qualcom, 1024, 1024);
			if (!SetCommState(p_Qualcom, &dcbSerialParams)) AfxMessageBox(L"SetSerialState Failed");
			else m_listbox.AddString(L"设置串口参数成功");
			if (!SetCommTimeouts(p_Qualcom, &timeouts)) { AfxMessageBox(L"SetSerialState Failed"); }
			else m_listbox.AddString(L"设置超时时间成功！");
		}
#ifndef _DEBUG
		VMProtectEnd();
#endif
		//ret=WriteFile(p_Qualcom,writeSN, strlen(writeSN), (LPDWORD)&p_length, NULL);
		//ReadFile(p_Qualcom, tmp, 1024,(LPDWORD)&p_length, NULL);
		//CloseHandle(p_Qualcom);
		break;
	case DBT_DEVTYP_PORT:
		break;
	}
}
return 0;
}
LRESULT CRockChipSNWriteToolDlg::OnSetToAutomaticMode(WPARAM wParam, LPARAM lParam)
{
	return 0;
}
BOOL CRockChipSNWriteToolDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CRect m_cor = { 0 };
	GetWindowRect(&m_cor);
	// Add "About..." menu item to system menu.
	INT ret;
	TCHAR d_DeviceName[5] = { 0 };
	TCHAR T_path[20] = { 0 };
	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	HANDLE m_hMutex = CreateMutex(NULL, TRUE, L"RockChipSNTOOL");
	DWORD dwRet = GetLastError();
	if (m_hMutex)
	{
		if (dwRet == ERROR_ALREADY_EXISTS)
		{
			AfxMessageBox(L"本程序仅允许一个进程启动");
			CloseHandle(m_hMutex);
			ExitProcess(0x0);
		}
	}
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	m_menu.LoadMenu(IDR_MENU1);
	this->SetMenu(&m_menu);
#ifndef _DEBUG
	VMProtectBegin("InitializeDialog");
#endif
	this->SetWindowTextW(L"YS-WNpctool v1.0");
	this->MoveWindow(m_cor.left, m_cor.top, 800, 750);
	m_label[0].Create(L"SN:", WS_CHILD | WS_VISIBLE|SS_CENTER | SS_CENTERIMAGE | WS_BORDER, CRect(20, 30, 100, 60), this);
	m_label[1].Create(L"WIFIMAC:", WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE | WS_BORDER, CRect(20, 70, 100, 100), this);
	m_label[2].Create(L"LANMAC:", WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE | WS_BORDER, CRect(20, 110, 100, 140), this);
	m_label[3].Create(L"BTMAC:", WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE | WS_BORDER, CRect(20, 150, 100, 180), this);
	m_label[4].Create(L"IMEI:", WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE | WS_BORDER, CRect(20, 190, 100, 220), this);
	m_button[0].Create(L"Loader", WS_CHILD | WS_VISIBLE | WS_BORDER, CRect(20, 230, 100, 270),this,0x1000);
	m_label[5].Create(L"OEMLOCK:", WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE | WS_BORDER, CRect(20, 290, 100, 320), this);
	m_edit[0].Create(WS_CHILD | WS_VISIBLE|ES_CENTER|WS_BORDER, CRect(120, 30, 520, 60),this,0x2000);
	m_edit[1].Create(WS_CHILD | WS_VISIBLE | ES_CENTER | WS_BORDER, CRect(120, 70, 520, 100), this,0x2001);
	m_edit[2].Create(WS_CHILD | WS_VISIBLE | ES_CENTER | WS_BORDER, CRect(120, 110, 520, 140), this, 0x2002);
	m_edit[3].Create(WS_CHILD | WS_VISIBLE | ES_CENTER | WS_BORDER, CRect(120, 150, 520, 180), this, 0x2003);
	m_edit[4].Create(WS_CHILD | WS_VISIBLE | ES_CENTER | WS_BORDER, CRect(120, 190, 520, 220), this, 0x2004);
	m_edit[5].Create(WS_CHILD | WS_VISIBLE | ES_CENTER | WS_BORDER, CRect(120, 230, 520, 270), this, 0x2005);
	m_button[1].Create(NULL, WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, CRect(120, 290, 140, 320), this, 0x1001);
	m_button[2].Create(L"Write", WS_CHILD | WS_VISIBLE, CRect(540, 150, 700, 250), this, ID_WRITE_SN_BUTTON);
	m_label[14].Create(L"等待插入设备", WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE | WS_BORDER, CRect(540, 100, 650, 140), this, 0x1003);
	m_label[6].Create(L"Success:", WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE | WS_BORDER, CRect(540, 270, 600, 290), this, 0x1003);
	m_label[7].Create(L"Fail:", WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE | WS_BORDER, CRect(540, 310, 600, 330), this, 0x1004);
	m_label[8].Create(L"Total:", WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE | WS_BORDER, CRect(540, 350, 600, 370), this, 0x1005);
	m_label[9].Create(NULL, WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE | WS_BORDER, CRect(610, 270, 700, 290), this, 0x1006);
	m_label[10].Create(NULL, WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE | WS_BORDER, CRect(610, 310, 700, 330), this, 0x1007);
	m_label[11].Create(NULL, WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE | WS_BORDER, CRect(610, 350, 700, 370), this, 0x1008);
	m_label[12].Create(NULL, WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE | WS_BORDER, CRect(160, 280, 260, 310), this, 0x1009);
	m_label[13].Create(NULL, WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE | WS_BORDER, CRect(280, 280, 380, 310), this, 0x1010);
	m_button[3].Create(L"SIM1可插拔", WS_VISIBLE | WS_CHILD, CRect(160, 320, 260, 350), this, 0x1004);
	m_button[4].Create(L"SIM1不可插拔", WS_VISIBLE | WS_CHILD, CRect(280, 320, 380, 350), this, 0x1005);
	m_button[5].Create(L"SIM2可插拔", WS_VISIBLE | WS_CHILD, CRect(160, 360, 260, 390), this, 0x1006);
	m_button[6].Create(L"SIM2不可插拔", WS_VISIBLE | WS_CHILD, CRect(280, 360, 380, 390), this, 0x1007);
	m_button[7].Create(L"读取SIM卡状态", WS_VISIBLE | WS_CHILD, CRect(400, 320, 520, 390), this, 0x1008);
	m_listbox.Create(WS_CHILD | WS_VISIBLE|WS_BORDER, CRect(20, 390, 760, 650), this, 0x3000);
	m_edit[2].EnableWindow(FALSE);
	m_edit[2].SetWindowTextW(L"此功能未开放");
	m_edit[4].EnableWindow(FALSE);
	m_edit[4].SetWindowTextW(L"此功能未开放");
	m_edit[5].EnableWindow(FALSE);
	m_edit[5].SetWindowTextW(L"此功能未开放");
	ret = GetPrivateProfileString(APPNAME, APPVERSION, NULL, T_path, sizeof(T_path), CONFILENAME);
	if (GetLastError() == 0x2)
	{
		AfxMessageBox(L"配置文件不存在，软件将自动重建");
		MetaData::SetSNMode(0);
		MetaData::SetWIFIMode(0);
		MetaData::SetBTMode(0);
		g_Tmp.SetVersion(APPCURVERSION);
		g_Tmp.SetMetaData( TRUE, L"SN", L"YS", 20, L"SN123456YS", L"SN123456YS", L"SN987654YS", 123456, 654321, 530886,L"");
		g_Tmp.UpdatePrivateProfile(APPNAME);
		wifi_g_Tmp.SetVersion(APPCURVERSION);
		wifi_g_Tmp.SetMetaData(TRUE, L"WIFISN", L"ys", 20, L"AB1232456512", L"AB1232456512", L"AB1232456512", 123456, 654321, 530886,L"");
		wifi_g_Tmp.UpdatePrivateProfile(WIFIAPPNAME);
		bt_g_Tmp.SetVersion(APPCURVERSION);
		bt_g_Tmp.SetMetaData(TRUE, L"BTSN", L"SY", 20, L"CD1245789630", L"CD1245789630", L"CD1245789644", 123456, 654321, 530886,L"");
		bt_g_Tmp.UpdatePrivateProfile(BTAPPNAME);

	}
#ifndef _DEBUG
	VMProtectEnd();
#endif
	MetaData::GetMode();
	g_Tmp.SetPrivateProfile(APPNAME);
	wifi_g_Tmp.SetPrivateProfile(WIFIAPPNAME);
	bt_g_Tmp.SetPrivateProfile(BTAPPNAME);
	if (g_Tmp.Option)
	{
		m_edit[0].EnableWindow(FALSE);
		m_edit[0].SetWindowTextW(L"已设置为自动");
	}

	if (wifi_g_Tmp.Option)
	{
		m_edit[1].EnableWindow(FALSE);
		m_edit[1].SetWindowTextW(L"已设置为自动");
	}

	if (bt_g_Tmp.Option) {
		m_edit[3].EnableWindow(FALSE);
		m_edit[3].SetWindowTextW(L"已设置为自动");
	}

	//if(ret==errorno)
if (!this->RegisterDeviceFilter(DBT_DEVTYP_DEVICEINTERFACE)) {
		AfxMessageBox(L"Register Device Notification Filter Failed");
		return false;
	}
	

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CRockChipSNWriteToolDlg::PostNcDestroy()
{
	modeDlg.WriteCFGToDisk();
}

void CRockChipSNWriteToolDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CRockChipSNWriteToolDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CRockChipSNWriteToolDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

