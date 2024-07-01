#pragma once
/********************************************************************
//    Created:     2024/07/01  15:48:33
//    File Name:   D:\IPMacData\XEngine_Source\XEngine_APIModuleIPMac\APIModule_MACInfo\APIModule_MACInfo.h
//    File Path:   D:\IPMacData\XEngine_Source\XEngine_APIModuleIPMac\APIModule_MACInfo
//    File Base:   APIModule_MACInfo
//    File Ext:    h
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     MAC信息查询
//    History:
*********************************************************************/

class CAPIModule_MACInfo
{
public:
	CAPIModule_MACInfo();
	~CAPIModule_MACInfo();
public:
	bool APIModule_MACInfo_Init(LPCXSTR lpszDBFile);
	void APIModule_MACInfo_UnInit();
	bool APIModule_MACInfo_Query(XENGINE_MACADDRINFO* pSt_IPAddrInfo);
protected:
private:
	unordered_map<string, XENGINE_MACADDRINFO> stl_MapMACInfo;
};
