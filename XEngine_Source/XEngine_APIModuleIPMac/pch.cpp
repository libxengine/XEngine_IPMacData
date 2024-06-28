#include "pch.h"
#include "APIModule_IPAddr/APIModule_IPAddr.h"
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
extern "C" bool APIModule_IPAddr_Init(LPCXSTR lpszDBFile)
{
	return m_APIIPAddr.APIModule_IPAddr_Init(lpszDBFile);
}
extern "C" void APIModule_IPAddr_UnInit()
{
	return m_APIIPAddr.APIModule_IPAddr_UnInit();
}
extern "C" bool APIModule_IPAddr_Query(XENGINE_IPADDRINFO* pSt_IPAddrInfo)
{
	return m_APIIPAddr.APIModule_IPAddr_Query(pSt_IPAddrInfo);
}