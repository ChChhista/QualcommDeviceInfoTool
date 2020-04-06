#pragma once
#include "pch.h"
#include "windows.h"
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include "Dbt.h"
#include "info.h"
#ifdef __cplusplus
extern "C"{
#endif

	HANDLE p_Qualcom = INVALID_HANDLE_VALUE;
__declspec(dllexport) int __cdecl MyMessageBox(LPCWSTR psz_str)
{
	MessageBoxW(NULL, psz_str, psz_str, MB_OK);
	return 0;
}
LRESULT UsbDeviceMsgHandler(WPARAM wParam, LPARAM lParam)
{
	using namespace std;
	//TRACE(L"Usb Device Change Start:");
	PDEV_BROADCAST_HDR pdhdr = NULL;
	PDEV_BROADCAST_DEVICEINTERFACE_A pport = NULL;
	INT index = 0;
	wstring modem;
	wstring seperator = L"#";
	wstring key_Path(L"SYSTEM\\CurrentControlSet\\Enum\\USB\\");
	wstring Compath(L"\\\\.\\");
	wstring tmp;
    wstringstream m_ss;
	TCHAR ComValue[10] = { 0 };
	DWORD ret = -1;
	DWORD LPTYPE = REG_SZ;
	LONG p_length = -1;
	LONG lRes = -1;
	HKEY h_Key = NULL;
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
	std::vector<wstring> part;
	if (wParam == DBT_DEVICEREMOVECOMPLETE)
	{
		pport = (PDEV_BROADCAST_DEVICEINTERFACE_A)lParam;
		modem = (PTCHAR)pport->dbcc_name;
		if (modem.find(L"PID_9091") != -1)
		{
			CloseHandle(p_Qualcom);
			p_Qualcom = INVALID_HANDLE_VALUE;
			//m_label[14].SetWindowTextW(L"设备移除成功");
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
			m_ss.str(modem);
			while (std::getline(m_ss, tmp, L'#'))
				part.push_back(tmp);
			//	part.push_back(modem.Tokenize(seperator, index));
			key_Path += part[1];
			key_Path += L"\\";
			key_Path += part[2];
			key_Path+= +L"\\Device Parameters";
			lRes = RegOpenKeyExW(HKEY_LOCAL_MACHINE, key_Path.c_str(), 0, KEY_READ | KEY_WOW64_64KEY, &h_Key);
			ret = RegQueryValueEx(h_Key, L"PortName", 0, &LPTYPE, (LPBYTE)ComValue, (LPDWORD)&p_length);
			//TRACE(L"Get Port Name %s", ComValue);
			RegCloseKey(h_Key);
			Compath += ComValue;
			p_Qualcom = CreateFile(Compath.c_str(), GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, 0, 0);
			if (p_Qualcom == INVALID_HANDLE_VALUE)
			{
				MyMessageBox(OPEN_PORT_FAILED);
				ret = GetLastError();
			}
			else
			{
				SetupComm(p_Qualcom, 1024, 1024);
				/*m_label[14].SetWindowTextW(L"设备就绪");
				m_listbox.AddString(L"初始化Modem成功");
				if (!SetCommState(p_Qualcom, &dcbSerialParams)) AfxMessageBox(L"SetSerialState Failed");
				else m_listbox.AddString(L"设置串口参数成功");
				if (!SetCommTimeouts(p_Qualcom, &timeouts)) { AfxMessageBox(L"SetSerialState Failed"); }
				else m_listbox.AddString(L"设置超时时间成功！");*/
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
#ifdef __cplusplus
}
#endif