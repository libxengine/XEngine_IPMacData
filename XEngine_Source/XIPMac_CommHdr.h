#pragma once
/********************************************************************
//    Created:     2024/07/01  15:39:46
//    File Name:   D:\IPMacData\XEngine_Source\XIPMac_CommHdr.h
//    File Path:   D:\IPMacData\XEngine_Source
//    File Base:   XIPMac_CommHdr
//    File Ext:    h
//    Project:     XEngine(����ͨ������)
//    Author:      qyt
//    Purpose:     ����ͷ�ļ�
//    History:
*********************************************************************/
//////////////////////////////////////////////////////////////////////////
//                          ��Э�鶨��;unOperatorType
//////////////////////////////////////////////////////////////////////////
#define XENGINE_COMMUNICATION_PROTOCOL_TYPE_IPMAC (ENUM_XENGINE_COMMUNICATION_PROTOCOL_TYPE_USER + 101)
//////////////////////////////////////////////////////////////////////////
//                          ��Э�鶨��:unOperatorCode
//////////////////////////////////////////////////////////////////////////
//MAC
#define XENGINE_COMMUNICATION_PROTOCOL_CODE_MAC 0x10101     
//////////////////////////////////////////////////////////////////////////
//                          ���ݽṹ����
//////////////////////////////////////////////////////////////////////////
typedef struct
{
	XCHAR tszVendorName[MAX_PATH];     //����
	XCHAR tszMACPrefix[64];            //MAC��ַ
	XCHAR tszUPTime[16];               //����ʱ��
	XCHAR tszBlockType[8];             //����
	XSHOT bPrivate;                    //�Ƿ���˽�е�
}XENGINE_MACADDRINFO;
typedef struct
{
	XCHAR tszIPAddr[128];       //IP��ַ
	XCHAR tszIPCountry[128];    //����/����
	XCHAR tszIPProvince[128];   //ʡ/������
	XCHAR tszIPCity[128];       //��
	XCHAR tszIPCounty[128];     //��
	XCHAR tszIPISP[128];        //��Ӫ��
}XENGINE_IPADDRINFO;