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
	
	XCHAR tszMSGBuffer[XPATH_MAX] = {};
	//第一行数据为格式数据
	if (NULL == fgets(tszMSGBuffer, XPATH_MAX, pSt_File))
	{
		IPMac_IsErrorOccur = true;
		IPMac_dwErrorCode = ERROR_XENGINE_IPMAC_APIMODULE_MACINFO_SIZE;
		return false;
	}
	tszMSGBuffer[strcspn(tszMSGBuffer, "\n")] = 0;

	std::vector<xstring> stl_ListField;
	APIModule_MACInfo_CSVParse(tszMSGBuffer, &stl_ListField);

	if (5 != stl_ListField.size())
	{
		IPMac_IsErrorOccur = true;
		IPMac_dwErrorCode = ERROR_XENGINE_IPMAC_APIMODULE_MACINFO_PROTOCOL;
		return false;
	}
	//读取真实数据
	while (true)
	{
		memset(tszMSGBuffer, 0, sizeof(tszMSGBuffer));
		if (NULL == fgets(tszMSGBuffer, XPATH_MAX, pSt_File))
		{
			break;
		}
		tszMSGBuffer[strcspn(tszMSGBuffer, "\n")] = 0;

		XENGINE_MACADDRINFO st_MACInfo = {};
		std::vector<xstring> stl_ListField;
		APIModule_MACInfo_CSVParse(tszMSGBuffer, &stl_ListField);
		
		_tcsxcpy(st_MACInfo.tszMACPrefix, stl_ListField[0].c_str());
		_tcsxcpy(st_MACInfo.tszVendorName, stl_ListField[1].c_str());
		_tcsxcpy(st_MACInfo.tszBlockType, stl_ListField[3].c_str());
		_tcsxcpy(st_MACInfo.tszUPTime, stl_ListField[4].c_str());
		if (0 == _tcsxicmp("false", stl_ListField[2].c_str()))
		{
			st_MACInfo.bPrivate = false;
		}
		else
		{
			st_MACInfo.bPrivate = true;
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
//////////////////////////////////////////////////////////////////////////
//                       公有函数
//////////////////////////////////////////////////////////////////////////
void CAPIModule_MACInfo::APIModule_MACInfo_CSVParse(LPCXSTR lpszMSGBuffer, std::vector<xstring>* pStl_ListField)
{
	XCHAR tszFieldStr[XPATH_MIN] = {};
	int nIndex = 0;
	bool bFlags = false;

	while (*lpszMSGBuffer)
	{
		if (*lpszMSGBuffer == '"')
		{
			// 进入或退出引号状态
			bFlags = !bFlags;
		}
		else if (*lpszMSGBuffer == ',' && !bFlags)
		{
			// 遇到分隔符并且不在引号内，字段结束
			tszFieldStr[nIndex] = '\0';
			pStl_ListField->push_back(tszFieldStr);
			nIndex = 0;
		}
		else 
		{
			tszFieldStr[nIndex++] = *lpszMSGBuffer;
		}
		lpszMSGBuffer++;
	}
	// 最后一个字段
	tszFieldStr[nIndex] = '\0';
	pStl_ListField->push_back(tszFieldStr);
}
