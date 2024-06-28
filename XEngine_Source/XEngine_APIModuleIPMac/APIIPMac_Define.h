﻿#pragma once
/********************************************************************
//    Created:     2024/06/28  14:55:29
//    File Name:   D:\phonedata\Source\C\XEngine_APIModulePhone\APIPhone_Define.h
//    File Path:   D:\phonedata\Source\C\XEngine_APIModulePhone
//    File Base:   APIPhone_Define
//    File Ext:    h
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     电话号码信息查询模块
//    History:
*********************************************************************/
//////////////////////////////////////////////////////////////////////////
//                       导出函数定义
//////////////////////////////////////////////////////////////////////////
typedef struct
{
	XCHAR tszIPAddr[128];       //IP地址
	XCHAR tszIPCountry[128];    //国家/地区
	XCHAR tszIPProvince[128];   //省/自治区
	XCHAR tszIPCity[128];       //市
	XCHAR tszIPCounty[128];     //县
	XCHAR tszIPISP[128];        //运营商
}XENGINE_IPADDRINFO;
//////////////////////////////////////////////////////////////////////////
//                       导出函数定义
//////////////////////////////////////////////////////////////////////////
extern "C" XLONG APIIPMac_GetLastError(int* pInt_ErrorCode = NULL);
/*********************************************************************************
*                                导出函数定义                                    *
*********************************************************************************/
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
extern "C" bool APIModule_IPAddr_Init(LPCXSTR lpszDBFile);
/********************************************************************
函数名称：APIModule_IPAddr_UnInit
函数功能：反初始化
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" void APIModule_IPAddr_UnInit();
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
extern "C" bool APIModule_IPAddr_Query(XENGINE_IPADDRINFO* pSt_IPAddrInfo);