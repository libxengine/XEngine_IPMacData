#include "pch.h"
#include "APIModule_MACInfo.h"
/********************************************************************
//    Created:     2024/07/01  15:48:56
//    File Name:   D:\IPMacData\XEngine_Source\XEngine_APIModuleIPMac\APIModule_MACInfo\APIModule_MACInfo.cpp
//    File Path:   D:\IPMacData\XEngine_Source\XEngine_APIModuleIPMac\APIModule_MACInfo
//    File Base:   APIModule_MACInfo
//    File Ext:    cpp
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     MAC信息查询
//    History:
*********************************************************************/
CAPIModule_MACInfo::CAPIModule_MACInfo()
{
}
CAPIModule_MACInfo::~CAPIModule_MACInfo()
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
bool CAPIModule_MACInfo::APIModule_MACInfo_Init(LPCXSTR lpszDBFile)
{
	IPMac_IsErrorOccur = false;

	if (NULL == lpszDBFile)
	{
		IPMac_IsErrorOccur = true;
		IPMac_dwErrorCode = ERROR_XENGINE_IPMAC_APIMODULE_MACINFO_PARAMENT;
		return false;
	}
	FILE* pSt_File = _xtfopen(lpszDBFile, _X("rb"));
	if (NULL == pSt_File)
	{
		IPMac_IsErrorOccur = true;
		IPMac_dwErrorCode = ERROR_XENGINE_IPMAC_APIMODULE_MACINFO_OPEN;
		return false;
	}
	
	XENGINE_PROTOCOLHDR st_ProtocolHdr = {};
	size_t nRet = fread(&st_ProtocolHdr, 1, sizeof(XENGINE_PROTOCOLHDR), pSt_File);
	if (nRet != sizeof(XENGINE_PROTOCOLHDR))
	{
		IPMac_IsErrorOccur = true;
		IPMac_dwErrorCode = ERROR_XENGINE_IPMAC_APIMODULE_MACINFO_SIZE;
		return false;
	}
	if ((XENGIEN_COMMUNICATION_PACKET_PROTOCOL_HEADER != st_ProtocolHdr.wHeader) || (XENGIEN_COMMUNICATION_PACKET_PROTOCOL_TAIL != st_ProtocolHdr.wTail) || (XENGINE_COMMUNICATION_PROTOCOL_TYPE_IPMAC != st_ProtocolHdr.unOperatorType) || (XENGINE_COMMUNICATION_PROTOCOL_CODE_MAC != st_ProtocolHdr.unOperatorCode))
	{
		IPMac_IsErrorOccur = true;
		IPMac_dwErrorCode = ERROR_XENGINE_IPMAC_APIMODULE_MACINFO_PROTOCOL;
		return false;
	}
	//循环
	for (XSHOT i = 0; i < st_ProtocolHdr.wPacketSerial; i++)
	{
		XENGINE_MACADDRINFO st_MACInfo = {};
		nRet = fread(&st_MACInfo, 1, sizeof(XENGINE_MACADDRINFO), pSt_File);
		if (nRet != sizeof(XENGINE_MACADDRINFO))
		{
			break;
		}
		stl_MapMACInfo.insert(make_pair(st_MACInfo.tszMACPrefix, st_MACInfo));
	}
	fclose(pSt_File);
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
void CAPIModule_MACInfo::APIModule_MACInfo_UnInit()
{
	IPMac_IsErrorOccur = false;

	stl_MapMACInfo.clear();
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
bool CAPIModule_MACInfo::APIModule_MACInfo_Query(XENGINE_MACADDRINFO* pSt_IPAddrInfo)
{
	IPMac_IsErrorOccur = false;

	if (NULL == pSt_IPAddrInfo)
	{
		IPMac_IsErrorOccur = true;
		IPMac_dwErrorCode = ERROR_XENGINE_IPMAC_APIMODULE_IPADDR_PARAMENT;
		return false;
	}
	
	auto stl_MapIterator = stl_MapMACInfo.find(pSt_IPAddrInfo->tszMACPrefix);
	if (stl_MapIterator == stl_MapMACInfo.end())
	{
		IPMac_IsErrorOccur = true;
		IPMac_dwErrorCode = ERROR_XENGINE_IPMAC_APIMODULE_IPADDR_NOTFOUND;
		return false;
	}
	*pSt_IPAddrInfo = stl_MapIterator->second;
	return true;
}