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
 参数.一：lpszIPFile
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：输入IP数据库路径
 参数.二：lpszISPFile
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：输入IP编码信息数据库路径
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CAPIModule_IPAddr::APIModule_IPAddr_Init(LPCXSTR lpszIPFile, LPCXSTR lpszISPFile /* = NULL */)
{
	IPMac_IsErrorOccur = false;

	if (NULL == lpszIPFile)
	{
		IPMac_IsErrorOccur = true;
		IPMac_dwErrorCode = ERROR_XENGINE_IPMAC_APIMODULE_IPADDR_PARAMENT;
		return false;
	}
	
	int nRet = MMDB_open(lpszIPFile, MMDB_MODE_MMAP, &st_MMIPInfo);
	if (nRet != MMDB_SUCCESS)
	{
		IPMac_IsErrorOccur = true;
		IPMac_dwErrorCode = ERROR_XENGINE_IPMAC_APIMODULE_IPADDR_OPENFILE;
		return false;
	}
	if (NULL != lpszISPFile)
	{
		nRet = MMDB_open(lpszISPFile, MMDB_MODE_MMAP, &st_MMISPInfo);
		if (nRet != MMDB_SUCCESS)
		{
			IPMac_IsErrorOccur = true;
			IPMac_dwErrorCode = ERROR_XENGINE_IPMAC_APIMODULE_IPADDR_OPENFILE;
			return false;
		}
		bISPInit = true;
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

	MMDB_close(&st_MMIPInfo);
	if (bISPInit)
	{
		MMDB_close(&st_MMISPInfo);
		bISPInit = false;
	}
}
/********************************************************************
函数名称：APIModule_IPAddr_Query
函数功能：查询指定IP地址的信息
 参数.一：pSt_IPAddrInfo
  In/Out：In/Out
  类型：数据结构指针
  可空：N
  意思：输入要查询的地址,输出查询到的信息
 参数.二：lpszLanguageStr
  In/Out：In/Out
  类型：常量字符指针
  可空：N
  意思：输入要获取的语言信息,en为英语,zh-CN为中文
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CAPIModule_IPAddr::APIModule_IPAddr_Query(XENGINE_IPADDRINFO* pSt_IPAddrInfo,LPCXSTR lpszLanguageStr /* = _X("zh-CN") */)
{
	IPMac_IsErrorOccur = false;

	if (NULL == pSt_IPAddrInfo)
	{
		IPMac_IsErrorOccur = true;
		IPMac_dwErrorCode = ERROR_XENGINE_IPMAC_APIMODULE_IPADDR_PARAMENT;
		return false;
	}
	int nGaiError = 0;
	int nMMDBError = 0;
	MMDB_lookup_result_s m_Result = MMDB_lookup_string(&st_MMIPInfo, pSt_IPAddrInfo->tszIPAddr, &nGaiError, &nMMDBError);
	if (0 != nGaiError && MMDB_SUCCESS != nMMDBError && !m_Result.found_entry)
	{
		IPMac_IsErrorOccur = true;
		IPMac_dwErrorCode = ERROR_XENGINE_IPMAC_APIMODULE_IPADDR_NOTFOUND;
		return false;
	}
	MMDB_entry_data_s m_EntryDatas;
	// 大洲名称
	if (MMDB_get_value(&m_Result.entry, &m_EntryDatas, "continent", "names", lpszLanguageStr, NULL) == MMDB_SUCCESS && m_EntryDatas.has_data)
	{
		memcpy(pSt_IPAddrInfo->tszIPContinent, m_EntryDatas.utf8_string, m_EntryDatas.data_size);
	}
	// 国家名称
	if (MMDB_get_value(&m_Result.entry, &m_EntryDatas, "country", "names", lpszLanguageStr, NULL) == MMDB_SUCCESS && m_EntryDatas.has_data)
	{
		memcpy(pSt_IPAddrInfo->tszIPCountry, m_EntryDatas.utf8_string, m_EntryDatas.data_size);
	}
	// 省份名称
	if (MMDB_get_value(&m_Result.entry, &m_EntryDatas, "subdivisions", "0", "names", lpszLanguageStr, NULL) == MMDB_SUCCESS && m_EntryDatas.has_data)
	{
		memcpy(pSt_IPAddrInfo->tszIPProvince, m_EntryDatas.utf8_string, m_EntryDatas.data_size);
	}
	// 城市名称
	if (MMDB_get_value(&m_Result.entry, &m_EntryDatas, "city", "names", lpszLanguageStr, NULL) == MMDB_SUCCESS && m_EntryDatas.has_data)
	{
		memcpy(pSt_IPAddrInfo->tszIPCity, m_EntryDatas.utf8_string, m_EntryDatas.data_size);
	}
	// 纬度
	if (MMDB_get_value(&m_Result.entry, &m_EntryDatas, "location", "latitude", NULL) == MMDB_SUCCESS && m_EntryDatas.has_data)
	{
		pSt_IPAddrInfo->dlLatitude = m_EntryDatas.double_value;
	}
	// 经度
	if (MMDB_get_value(&m_Result.entry, &m_EntryDatas, "location", "longitude", NULL) == MMDB_SUCCESS && m_EntryDatas.has_data)
	{
		pSt_IPAddrInfo->dlLongitude = m_EntryDatas.double_value;
	}
	// 时区
	if (MMDB_get_value(&m_Result.entry, &m_EntryDatas, "location", "time_zone", NULL) == MMDB_SUCCESS && m_EntryDatas.has_data)
	{
		memcpy(pSt_IPAddrInfo->tszTimezone, m_EntryDatas.utf8_string, m_EntryDatas.data_size);
	}

	if (bISPInit)
	{
		APIModule_IPAddr_ISPQuery(pSt_IPAddrInfo);
	}
	return true;
}
//////////////////////////////////////////////////////////////////////////
//                       保护函数
//////////////////////////////////////////////////////////////////////////
bool CAPIModule_IPAddr::APIModule_IPAddr_ISPQuery(XENGINE_IPADDRINFO* pSt_IPAddrInfo)
{
	IPMac_IsErrorOccur = false;

	if (NULL == pSt_IPAddrInfo)
	{
		IPMac_IsErrorOccur = true;
		IPMac_dwErrorCode = ERROR_XENGINE_IPMAC_APIMODULE_IPADDR_PARAMENT;
		return false;
	}
	int nGaiError = 0;
	int nMMDBError = 0;
	MMDB_lookup_result_s m_Result = MMDB_lookup_string(&st_MMISPInfo, pSt_IPAddrInfo->tszIPAddr, &nGaiError, &nMMDBError);
	if (0 != nGaiError && MMDB_SUCCESS != nMMDBError && !m_Result.found_entry)
	{
		IPMac_IsErrorOccur = true;
		IPMac_dwErrorCode = ERROR_XENGINE_IPMAC_APIMODULE_IPADDR_NOTFOUND;
		return false;
	}
	MMDB_entry_data_s m_EntryDatas;
	if (MMDB_get_value(&m_Result.entry, &m_EntryDatas, "autonomous_system_organization", NULL) == MMDB_SUCCESS && m_EntryDatas.has_data)
	{
		memcpy(pSt_IPAddrInfo->tszIPISP, m_EntryDatas.utf8_string, m_EntryDatas.data_size);
	}
	return true;
}