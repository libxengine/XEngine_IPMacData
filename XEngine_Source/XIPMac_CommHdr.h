#pragma once
/********************************************************************
//    Created:     2024/07/01  15:39:46
//    File Name:   D:\IPMacData\XEngine_Source\XIPMac_CommHdr.h
//    File Path:   D:\IPMacData\XEngine_Source
//    File Base:   XIPMac_CommHdr
//    File Ext:    h
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     公用头文件
//    History:
*********************************************************************/
//////////////////////////////////////////////////////////////////////////
//                          主协议定义;unOperatorType
//////////////////////////////////////////////////////////////////////////
#define XENGINE_COMMUNICATION_PROTOCOL_TYPE_IPMAC (ENUM_XENGINE_COMMUNICATION_PROTOCOL_TYPE_USER + 101)
//////////////////////////////////////////////////////////////////////////
//                          子协议定义:unOperatorCode
//////////////////////////////////////////////////////////////////////////
//MAC
#define XENGINE_COMMUNICATION_PROTOCOL_CODE_MAC 0x10101     
//////////////////////////////////////////////////////////////////////////
//                          数据结构定义
//////////////////////////////////////////////////////////////////////////
typedef struct
{
	XCHAR tszVendorName[MAX_PATH];     //厂商
	XCHAR tszMACPrefix[64];            //MAC地址
	XCHAR tszUPTime[16];               //更新时间
	XCHAR tszBlockType[8];             //类型
	XSHOT bPrivate;                    //是否是私有的
}XENGINE_MACADDRINFO;
typedef struct
{ 
	XCHAR tszIPContinent[128];  //大洲名称
	XCHAR tszIPAddr[128];       //IP地址
	XCHAR tszIPCountry[128];    //国家/地区
	XCHAR tszIPProvince[128];   //省/自治区
	XCHAR tszIPCity[128];       //市
	// XCHAR tszIPCounty[128];     //县 not support
	XCHAR tszIPISP[128];        //运营商
	XCHAR tszTimezone[128];     //时区
	double dlLatitude;          //纬度
	double dlLongitude;         //经度
}XENGINE_IPADDRINFO;