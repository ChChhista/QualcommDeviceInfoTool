#pragma once
#include "windows.h"
#include "framework.h"
#define COPYRIGHT "Copyright Belongs To destinyhu1996@gmail.com [Xiaohu]"
#define SNCOMMAND "AT+SYSCMD=lserialn%s\r"
#define WIFISNCOMMAND "AT+LCTSN=1,12,\"%s\"\r"
#define BTSNCOMMAND "AT+LCTSN=1,10,\"%s\"\r"
#define SIM1HOTPLUGCMD "AT+SIMSWAPEN=1,1\r"
#define SIM2HOTPLUGCMD "AT+SIMSWAPEN=1,2\r"
#define SIM1NOTHOTPLUGCMD "AT+SIMSWAPEN=0,1\r"
#define SIM2NOTHOTPLUGCMD "AT+SIMSWAPEN=0,2\r"
#define READSIMSTATE "AT+SIMSWAPEN?\r"
#define READSNNUMBERCMD "AT+SYSCMD=readsn"
#define APPNAME L"SerialNumberConfig"
#define WIFIAPPNAME L"WifiNumberConfig"
#define BTAPPNAME L"BTNumberConfig"
#define MODE L"mode"
#define OPTION L"option"
#define PREFIX L"prefix"
#define POSTFIX L"postfix"
#define LENGTH L"length"
#define STARTSN L"strsn"
#define CURRENTSN L"cursn"
#define ENDSN L"endsn"
#define CURRENTNUM L"curnum"
#define ENDNUM L"endnum"
#define REMAINSN L"remainsn"
#define ZERONUM L"zeroNum"
#define APPVERSION L"app-version"
#define APPCURVERSION L"YS-201912"
#define CONFILENAME L".//YS-SNTOOL.ini"
#define SERIALCURNUM L"SerialCurNum"
#define SERIALENDNUM L"SerialEndNum"
#include <string>
class MetaData
{
public:
	enum mode
	{
		SN = 1,
		WIFI,
		LAN,
		BT,
		IMEI
	};
	CString Version;
	static BOOL SNMODE;
	static BOOL WIFIMODE;
	static BOOL BTMODE;
	BOOL Option;
	CString prefix;
	CString postfix;
	DWORD len;
	CString strNum;
	CString curNum;
	CString endNum;
	LONGLONG curDigital;
	LONGLONG endDigital;
	DWORD Remain;
	CString zeroNum;
public:
	VOID SetVersion(CONST PTCHAR version)
	{
		Version = version;
	}
	static VOID SetSNMode(DWORD Mode)
	{
		MetaData::SNMODE = Mode;
		TCHAR tmp[20] = { 0 };
		WritePrivateProfileStringW(L"SNMode", MODE, _itow(MetaData::SNMODE, tmp, 10), CONFILENAME);
	}
	static VOID SetWIFIMode(DWORD Mode)
	{
		MetaData::WIFIMODE = Mode;
		TCHAR tmp[20] = { 0 };
		WritePrivateProfileStringW(L"WIFIMode", MODE, _itow(MetaData::WIFIMODE, tmp, 10), CONFILENAME);
	}
	static VOID SetBTMode(DWORD Mode)
	{
		MetaData::BTMODE = Mode;
		TCHAR tmp[20] = { 0 };
		WritePrivateProfileStringW(L"BTMode", MODE, _itow(MetaData::BTMODE, tmp, 10), CONFILENAME);
	}
	static VOID GetMode()
	{
		MetaData::SNMODE =GetPrivateProfileInt(L"SNMode", MODE,NULL,CONFILENAME);
		MetaData::WIFIMODE = GetPrivateProfileInt(L"WIFIMode", MODE, NULL, CONFILENAME);
		MetaData::BTMODE = GetPrivateProfileInt(L"BTMode", MODE, NULL, CONFILENAME);
		return;
	}
	void  SetMetaData(BOOL option, CString prefix, CString postfix, DWORD len, CString strNum, CString curNum, CString endNum,DWORD curDigital,DWORD endDigital, DWORD Remain,CString zeroNum)
	{

		this->Option = option;
		this->prefix = prefix;
		this->postfix = postfix;
		this->len = len;
		this->strNum = strNum;
		this->curNum = curNum;
		this->endNum = endNum;
		this->curDigital = curDigital;
		this->endDigital = endDigital;
		this->Remain = Remain;
		this->zeroNum = zeroNum;
	}
	BOOL UpdatePrivateProfile(const PTCHAR appname)
	{
		TCHAR tmp[20] = { 0 };
		if (SNMODE< 0 || SNMODE>1||WIFIMODE<0||WIFIMODE>1||BTMODE<0||BTMODE>1) {
			AfxMessageBox(L"模式错误，高通平台仅支持1、2、3模式");
			return FALSE;
		}
		WritePrivateProfileStringW(appname, APPVERSION, this->Version, CONFILENAME);
		WritePrivateProfileStringW(appname, OPTION, _itow(this->Option, tmp, 10), CONFILENAME);
		WritePrivateProfileStringW(appname, PREFIX, this->prefix, CONFILENAME);
		WritePrivateProfileStringW(appname, POSTFIX,this->postfix, CONFILENAME);
		WritePrivateProfileStringW(appname, LENGTH, _itow(this->len,tmp,10), CONFILENAME);
		WritePrivateProfileStringW(appname, STARTSN, this->strNum, CONFILENAME);
		WritePrivateProfileStringW(appname, CURRENTSN, this->curNum, CONFILENAME);
		WritePrivateProfileStringW(appname, ENDSN, this->endNum, CONFILENAME);
		WritePrivateProfileStringW (appname, SERIALCURNUM,std::to_wstring(this->curDigital).c_str(), CONFILENAME);
		WritePrivateProfileStringW(appname, SERIALENDNUM,std::to_wstring(this->endDigital).c_str(), CONFILENAME);
		WritePrivateProfileStringW(appname, REMAINSN, _itow(this->Remain, tmp, 10), CONFILENAME);
		WritePrivateProfileStringW(appname, ZERONUM, this->zeroNum, CONFILENAME);
		return TRUE;
	}
	BOOL SetPrivateProfile(const PTCHAR appname)
	{
		DWORD ret = -1;
		TCHAR T_path[MAX_PATH] = { 0 };
		ret = GetPrivateProfileString(appname, APPVERSION, NULL, T_path, MAX_PATH, CONFILENAME);
		this->SetVersion(T_path);
		ret = GetPrivateProfileString(appname, OPTION, NULL, T_path, MAX_PATH, CONFILENAME);
		this->Option = _wtoi(T_path);
		ret = GetPrivateProfileString(appname, PREFIX, NULL, T_path, MAX_PATH, CONFILENAME);
		this->prefix = T_path;
		ret = GetPrivateProfileString(appname, POSTFIX, NULL, T_path, MAX_PATH, CONFILENAME);
		this->postfix = T_path;
		ret = GetPrivateProfileString(appname, LENGTH, NULL, T_path, MAX_PATH, CONFILENAME);
		this->len = _wtoi(T_path);
		ret = GetPrivateProfileString(appname, STARTSN, NULL, T_path, MAX_PATH, CONFILENAME);
		this->strNum = T_path;
		ret = GetPrivateProfileString(appname, CURRENTSN, NULL, T_path, MAX_PATH, CONFILENAME);
		this->curNum = T_path;
		ret = GetPrivateProfileString(appname, ENDSN, NULL, T_path, MAX_PATH, CONFILENAME);
		this->endNum = T_path;
		ret = GetPrivateProfileString(appname, REMAINSN, NULL, T_path, MAX_PATH, CONFILENAME);
		this->Remain = _wtoi(T_path);
		ret = GetPrivateProfileString(appname, SERIALCURNUM, NULL, T_path, MAX_PATH, CONFILENAME);
		this->curDigital = wcstoll(T_path,NULL,10);
		ret = GetPrivateProfileString(appname, SERIALENDNUM, NULL, T_path, MAX_PATH, CONFILENAME);
		this->endDigital = wcstoll(T_path, NULL, 10);
		ret = GetPrivateProfileString(appname, ZERONUM, NULL, T_path, MAX_PATH, CONFILENAME);
		this->zeroNum =T_path;
		return TRUE;
	}



};
