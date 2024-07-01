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
typedef enum
{
	//用户消息
	ENUM_XENGINE_COMMUNICATION_PROTOCOL_TYPE_IPMAC = ENUM_XENGINE_COMMUNICATION_PROTOCOL_TYPE_USER + 101
}ENUM_XENGINE_COMMUNICATION_PROTOCOL_TYPE_CUSTOM;
//////////////////////////////////////////////////////////////////////////
//                          子协议定义:unOperatorCode
//////////////////////////////////////////////////////////////////////////
//MAC
#define XENGINE_COMMUNICATION_PROTOCOL_OPERATOR_CODE_MAC 0x10101     
//////////////////////////////////////////////////////////////////////////
//                          数据结构定义
//////////////////////////////////////////////////////////////////////////
typedef struct
{
	XCHAR tszVendorName[MAX_PATH];
	XCHAR tszMACPrefix[64];
	XCHAR tszUPTime[16];
	XCHAR tszBlockType[8];
	bool bPrivate;
}XENGINE_MACADDRINFO;