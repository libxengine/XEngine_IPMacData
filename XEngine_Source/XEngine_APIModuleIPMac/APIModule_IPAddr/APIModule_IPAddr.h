#pragma once
#include "maxminddb.h"
/********************************************************************
//    Created:     2024/06/28  16:15:40
//    File Name:   D:\IPMacData\XEngine_Source\XEngine_APIModuleIPMac\APIModule_IPAddr\APIModule_IPAddr.h
//    File Path:   D:\IPMacData\XEngine_Source\XEngine_APIModuleIPMac\APIModule_IPAddr
//    File Base:   APIModule_IPAddr
//    File Ext:    h
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     IP地址归属地查询
//    History:
*********************************************************************/

class CAPIModule_IPAddr
{
public:
	CAPIModule_IPAddr();
	~CAPIModule_IPAddr();
public:
	bool APIModule_IPAddr_Init(LPCXSTR lpszIPFile, LPCXSTR lpszISPFile = NULL);
	void APIModule_IPAddr_UnInit();
	bool APIModule_IPAddr_Query(XENGINE_IPADDRINFO* pSt_IPAddrInfo,LPCXSTR lpszLanguageStr = _X("en"));
protected:
	bool APIModule_IPAddr_ISPQuery(XENGINE_IPADDRINFO* pSt_IPAddrInfo);
private:
	bool bISPInit = false;
private:
	MMDB_s st_MMIPInfo;
	MMDB_s st_MMISPInfo;
};
