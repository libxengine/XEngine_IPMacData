#include "pch.h"
#include "APIModule_IPAddr/APIModule_IPAddr.h"
#include "APIModule_MACInfo/APIModule_MACInfo.h"
/********************************************************************
//    Created:     2024/06/28  16:29:36
//    File Name:   D:\IPMacData\XEngine_Source\XEngine_APIModuleIPMac\pch.cpp
//    File Path:   D:\IPMacData\XEngine_Source\XEngine_APIModuleIPMac
//    File Base:   pch
//    File Ext:    cpp
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     导出实现
//    History:
*********************************************************************/
bool IPMac_IsErrorOccur = false;
XLONG IPMac_dwErrorCode = 0;
//////////////////////////////////////////////////////////////////////////
CAPIModule_IPAddr m_APIIPAddr;
CAPIModule_MACInfo m_APIMacInfo;
//////////////////////////////////////////////////////////////////////////
//                        导出实现
//////////////////////////////////////////////////////////////////////////
extern "C" XLONG APIIPMac_GetLastError(int* pInt_ErrorCode)
{
	if (NULL != pInt_ErrorCode)
	{
		*pInt_ErrorCode = errno;
	}
	return IPMac_dwErrorCode;
}
/************************************************************************/
/*                         号码查询                                     */
/************************************************************************/
extern "C" bool APIModule_IPAddr_Init(LPCXSTR lpszIPFile, LPCXSTR lpszISPFile)
{
	return m_APIIPAddr.APIModule_IPAddr_Init(lpszIPFile, lpszISPFile);
}
extern "C" void APIModule_IPAddr_UnInit()
{
	return m_APIIPAddr.APIModule_IPAddr_UnInit();
}
extern "C" bool APIModule_IPAddr_Query(XENGINE_IPADDRINFO* pSt_IPAddrInfo, LPCXSTR lpszLanguageStr)
{
	return m_APIIPAddr.APIModule_IPAddr_Query(pSt_IPAddrInfo, lpszLanguageStr);
}
/*********************************************************************************
*                                MAC查询函数定义                                 *
*********************************************************************************/
extern "C" bool APIModule_MACInfo_Init(LPCXSTR lpszDBFile)
{
	return m_APIMacInfo.APIModule_MACInfo_Init(lpszDBFile);
}
extern "C" void APIModule_MACInfo_UnInit()
{
	return m_APIMacInfo.APIModule_MACInfo_UnInit();
}
extern "C" bool APIModule_MACInfo_Query(XENGINE_MACADDRINFO* pSt_IPAddrInfo)
{
	return m_APIMacInfo.APIModule_MACInfo_Query(pSt_IPAddrInfo);
}