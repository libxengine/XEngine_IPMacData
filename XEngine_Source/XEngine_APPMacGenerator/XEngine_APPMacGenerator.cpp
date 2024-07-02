#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <list>
#include <XEngine_Include/XEngine_CommHdr.h>
#include <XEngine_Include/XEngine_Types.h>
#include <XEngine_Include/XEngine_ProtocolHdr.h>
#include <json/json.h>
#include "../XIPMac_CommHdr.h"
#include "../XEngine_APIModuleIPMac/APIIPMac_Define.h"

#ifdef _DEBUG
#ifdef _WIN64
#pragma comment(lib,"../x64/Debug/jsoncpp")
#else
#pragma comment(lib,"../Debug/jsoncpp")
#endif
#else
#ifdef _WIN64
#pragma comment(lib,"../x64/Release/jsoncpp")
#else
#pragma comment(lib,"../Release/jsoncpp")
#endif
#endif

bool XEngine_APPGenerator_DBParse(XCHAR* ptszMSGBuffer, int* pInt_MSGLen)
{
	LPCXSTR lpszFile = _X("D:\\IPMacData\\XEngine_DBFile\\mac-vendors-export.json");

	FILE* pSt_File = _xtfopen(lpszFile, _X("rb"));
	if (NULL == pSt_File)
	{
		return false;
	}
	int nRet = fread(ptszMSGBuffer, 1, XENGINE_MEMORY_SIZE_MAX, pSt_File);
	if (nRet <= 0)
	{
		return false;
	}
	fclose(pSt_File);

	*pInt_MSGLen = nRet;
	return true;
}
bool XEngine_APPGenerator_DBPacket(std::list<XENGINE_MACADDRINFO> *pStl_ListMACAddr)
{
	LPCXSTR lpszFile = _X("D:\\IPMacData\\XEngine_DBFile\\macaddr.xdb");

	FILE* pSt_File = _xtfopen(lpszFile, _X("wb"));
	if (NULL == pSt_File)
	{
		return false;
	}
	XENGINE_PROTOCOLHDR st_ProtocolHdr = {};

	st_ProtocolHdr.wHeader = XENGIEN_COMMUNICATION_PACKET_PROTOCOL_HEADER;
	st_ProtocolHdr.unOperatorType = ENUM_XENGINE_COMMUNICATION_PROTOCOL_TYPE_IPMAC;
	st_ProtocolHdr.unOperatorCode = XENGINE_COMMUNICATION_PROTOCOL_OPERATOR_CODE_MAC;
	st_ProtocolHdr.unPacketSize = sizeof(XENGINE_MACADDRINFO) * pStl_ListMACAddr->size();
	st_ProtocolHdr.wPacketSerial = pStl_ListMACAddr->size();
	st_ProtocolHdr.wTail = XENGIEN_COMMUNICATION_PACKET_PROTOCOL_TAIL;
	fwrite(&st_ProtocolHdr, 1, sizeof(XENGINE_PROTOCOLHDR), pSt_File);

	int nCount = 0;
	for (auto stl_ListIterator = pStl_ListMACAddr->begin(); stl_ListIterator != pStl_ListMACAddr->end(); stl_ListIterator++)
	{
		XENGINE_MACADDRINFO st_MACInfo = *stl_ListIterator;
		
		int nRet = fwrite(&st_MACInfo, 1, sizeof(XENGINE_MACADDRINFO), pSt_File);
		if (nRet <= 0)
		{
			return false;
		}
		nCount += nRet;
	}
	fclose(pSt_File);
	return true;
}
int main()
{
	int nMSGLen = 0;
	XCHAR* ptszMSGBuffer = (XCHAR*)malloc(XENGINE_MEMORY_SIZE_MAX);
	if (NULL == ptszMSGBuffer)
	{
		return -1;
	}
	memset(ptszMSGBuffer, '\0', XENGINE_MEMORY_SIZE_MAX);

	if (!XEngine_APPGenerator_DBParse(ptszMSGBuffer, &nMSGLen))
	{
		printf("XEngine_APPGenerator_DBParse\n");
		return -1;
	}
	Json::Value st_JsonRoot;
	JSONCPP_STRING st_JsonError;
	Json::CharReaderBuilder st_ReaderBuilder;

	std::unique_ptr<Json::CharReader> const pSt_JsonReader(st_ReaderBuilder.newCharReader());
	if (!pSt_JsonReader->parse(ptszMSGBuffer, ptszMSGBuffer + nMSGLen, &st_JsonRoot, &st_JsonError))
	{
		return -1;
	}
	std::list<XENGINE_MACADDRINFO> stl_ListMACAddr;
	int nCount = st_JsonRoot.size();
	for (int i = 0; i < nCount; i++)
	{
		Json::Value st_JsonObject = st_JsonRoot[i];

		XENGINE_MACADDRINFO st_MACInfo = {};
		_tcsxcpy(st_MACInfo.tszMACPrefix, st_JsonObject["macPrefix"].asCString());
		_tcsxcpy(st_MACInfo.tszVendorName, st_JsonObject["vendorName"].asCString());
		_tcsxcpy(st_MACInfo.tszBlockType, st_JsonObject["blockType"].asCString());
		_tcsxcpy(st_MACInfo.tszUPTime, st_JsonObject["lastUpdate"].asCString());
		st_MACInfo.bPrivate = st_JsonObject["private"].asBool();

		stl_ListMACAddr.push_back(st_MACInfo);
	}
	XEngine_APPGenerator_DBPacket(&stl_ListMACAddr);
	return 0;
}