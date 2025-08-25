#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <XEngine_Include/XEngine_CommHdr.h>
#include <XEngine_Include/XEngine_Types.h>
#include <XEngine_Include/XEngine_ProtocolHdr.h>
#include "../XIPMac_CommHdr.h"
#include "../XEngine_APIModuleIPMac/APIIPMac_Define.h"
#include "../XEngine_APIModuleIPMac/APIIPMac_Error.h"


#ifdef _MSC_BUILD
#ifdef _DEBUG
#ifdef _M_X64
#pragma comment(lib,"../x64/Debug/XEngine_APIModuleIPMac")
#elif _M_ARM64
#pragma comment(lib,"../ARM64/Debug/XEngine_APIModuleIPMac")
#elif _M_IX86
#pragma comment(lib,"../Debug/XEngine_APIModuleIPMac")
#endif
#else
#ifdef _M_X64
#pragma comment(lib,"../x64/Release/XEngine_APIModuleIPMac")
#elif _M_ARM64
#pragma comment(lib,"../ARM64/Release/XEngine_APIModuleIPMac")
#elif _M_IX86
#pragma comment(lib,"../Release/XEngine_APIModuleIPMac")
#endif
#endif
#endif


int main()
{
#ifndef _DEBUG
	if (setlocale(LC_ALL, ".UTF8") == NULL)
	{
		printf("Error setting locale.\n");
		return -1;
	}
#endif
	LPCXSTR lpszDBFile = _X("D:\\XEngine_IPMacData\\XEngine_DBFile\\macaddr.xdb");
	if (!APIModule_MACInfo_Init(lpszDBFile))
	{
		printf("APIModule_MACInfo_Init:%lX\n", APIIPMac_GetLastError());
		return -1;
	}

	XENGINE_MACADDRINFO st_MACInfo = {};
	_xstprintf(st_MACInfo.tszMACPrefix, _X("00:00:0C:12"));

	if (!APIModule_MACInfo_Query(&st_MACInfo))
	{
		printf("APIModule_MACInfo_Query:%lX\n", APIIPMac_GetLastError());
		return -1;
	}
	printf("%s=%s,%s,%s,%d\n", st_MACInfo.tszMACPrefix, st_MACInfo.tszVendorName, st_MACInfo.tszBlockType, st_MACInfo.tszUPTime, st_MACInfo.bPrivate);

	APIModule_MACInfo_UnInit();
	return 0;
}