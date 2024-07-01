#pragma once
/********************************************************************
//    Created:     2024/06/28  16:22:09
//    File Name:   D:\IPMacData\XEngine_Source\XEngine_APIModuleIPMac\APIIPMac_Error.h
//    File Path:   D:\IPMacData\XEngine_Source\XEngine_APIModuleIPMac
//    File Base:   APIIPMac_Error
//    File Ext:    h
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     IPMAC地址信息查询
//    History:
*********************************************************************/
//////////////////////////////////////////////////////////////////////////
//                       IP错误
//////////////////////////////////////////////////////////////////////////
#define ERROR_XENGINE_IPMAC_APIMODULE_IPADDR_PARAMENT 0xFB0001            //初始化失败.参数错误
#define ERROR_XENGINE_IPMAC_APIMODULE_IPADDR_OPENFILE 0xFB0002            //打开文件失败
#define ERROR_XENGINE_IPMAC_APIMODULE_IPADDR_NOTFOUND 0xFB0003            //没有找到
#define ERROR_XENGINE_IPMAC_APIMODULE_IPADDR_VER 0xFB0004                 //数据验证失败,数据错误
//////////////////////////////////////////////////////////////////////////
//                       MAC错误
//////////////////////////////////////////////////////////////////////////
#define ERROR_XENGINE_IPMAC_APIMODULE_MACINFO_PARAMENT 0xFB1001           //初始化失败.参数错误
#define ERROR_XENGINE_IPMAC_APIMODULE_MACINFO_OPEN 0xFB1002               //打开文件失败
#define ERROR_XENGINE_IPMAC_APIMODULE_MACINFO_SIZE 0xFB1003               //文件大小错误
#define ERROR_XENGINE_IPMAC_APIMODULE_MACINFO_PROTOCOL 0xFB1004           //协议验证失败
#define ERROR_XENGINE_IPMAC_APIMODULE_MACINFO_NOTFOUND 0xFB1005           //没有找到