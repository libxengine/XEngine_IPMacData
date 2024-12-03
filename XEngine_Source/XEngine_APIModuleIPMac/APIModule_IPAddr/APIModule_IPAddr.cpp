#include "pch.h"
#include "APIModule_IPAddr.h"
/********************************************************************
//    Created:     2024/06/28  16:19:36
//    File Name:   D:\IPMacData\XEngine_Source\XEngine_APIModuleIPMac\APIModule_IPAddr\APIModule_IPAddr.cpp
//    File Path:   D:\IPMacData\XEngine_Source\XEngine_APIModuleIPMac\APIModule_IPAddr
//    File Base:   APIModule_IPAddr
//    File Ext:    cpp
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     IP地址归属地查询
//    History:
*********************************************************************/
CAPIModule_IPAddr::CAPIModule_IPAddr()
{
}
CAPIModule_IPAddr::~CAPIModule_IPAddr()
{
}
//////////////////////////////////////////////////////////////////////////
//                       公有函数
//////////////////////////////////////////////////////////////////////////
/********************************************************************
函数名称：APIModule_IPAddr_Init
函数功能：初始化模块
 参数.一：lpszDBFile
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：输入数据库路径
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CAPIModule_IPAddr::APIModule_IPAddr_Init(LPCXSTR lpszDBFile)
{
	IPMac_IsErrorOccur = false;

	if (NULL == lpszDBFile)
	{
		IPMac_IsErrorOccur = true;
		IPMac_dwErrorCode = ERROR_XENGINE_IPMAC_APIMODULE_IPADDR_PARAMENT;
		return false;
	}
	// 1、从 db_path 初始化 xdb 查询对象
	int err = xdb_new_with_file_only(&st_DBSearch, lpszDBFile);
	if (err != 0)
	{
		IPMac_IsErrorOccur = true;
		IPMac_dwErrorCode = ERROR_XENGINE_IPMAC_APIMODULE_IPADDR_OPENFILE;
		return false;
	}

    return true;
}
/********************************************************************
函数名称：APIModule_IPAddr_UnInit
函数功能：反初始化
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
void CAPIModule_IPAddr::APIModule_IPAddr_UnInit()
{
	IPMac_IsErrorOccur = false;

	xdb_close(&st_DBSearch);
}
/********************************************************************
函数名称：APIModule_IPAddr_Query
函数功能：查询指定IP地址的信息
 参数.一：pSt_IPAddrInfo
  In/Out：In/Out
  类型：数据结构指针
  可空：N
  意思：输入要查询的地址,输出查询到的信息
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CAPIModule_IPAddr::APIModule_IPAddr_Query(XENGINE_IPADDRINFO* pSt_IPAddrInfo)
{
	IPMac_IsErrorOccur = false;

	if (NULL == pSt_IPAddrInfo)
	{
		IPMac_IsErrorOccur = true;
		IPMac_dwErrorCode = ERROR_XENGINE_IPMAC_APIMODULE_IPADDR_PARAMENT;
		return false;
	}
	XCHAR tszKeyName[128];
	XCHAR tszMsgBuffer[128];

	memset(tszKeyName, '\0', sizeof(tszKeyName));
	memset(tszMsgBuffer, '\0', sizeof(tszMsgBuffer));

	if (0 != xdb_search_by_string(&st_DBSearch, pSt_IPAddrInfo->tszIPAddr, tszMsgBuffer, sizeof(tszMsgBuffer)))
	{
		IPMac_IsErrorOccur = true;
		IPMac_dwErrorCode = ERROR_XENGINE_IPMAC_APIMODULE_IPADDR_NOTFOUND;
		return false;
	}
	int nRet = 0;
#ifdef _MSC_BUILD
	XCHAR tszGBKBuffer[MAX_PATH] = {};
	int nUTFLen = _tcsxlen(tszMsgBuffer);
	BaseLib_Charset_UTFToAnsi(tszMsgBuffer, tszGBKBuffer, &nUTFLen);
	nRet = _stxscanf(tszGBKBuffer, _X("%[^|]|%[^|]|%[^|]|%[^|]|%[^|]"), pSt_IPAddrInfo->tszIPCountry, pSt_IPAddrInfo->tszIPCounty, pSt_IPAddrInfo->tszIPProvince, pSt_IPAddrInfo->tszIPCity, pSt_IPAddrInfo->tszIPISP);
#else
	nRet = _stxscanf(tszMsgBuffer, _X("%[^|]|%[^|]|%[^|]|%[^|]|%[^|]"), pSt_IPAddrInfo->tszIPCountry, pSt_IPAddrInfo->tszIPCounty, pSt_IPAddrInfo->tszIPProvince, pSt_IPAddrInfo->tszIPCity, pSt_IPAddrInfo->tszIPISP);
#endif
	if (nRet != 5)
	{
		IPMac_IsErrorOccur = true;
		IPMac_dwErrorCode = ERROR_XENGINE_IPMAC_APIMODULE_IPADDR_VER;
		return false;
	}
	return true;
}