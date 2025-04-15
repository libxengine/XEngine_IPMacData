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
    LPCXSTR lpszIPFile = _X("D:\\XEngine_IPMacData\\XEngine_DBFile\\GeoLite2-City.mmdb");
    LPCXSTR lpszISPFile = _X("D:\\XEngine_IPMacData\\XEngine_DBFile\\GeoLite2-ASN.mmdb");
    if (!APIModule_IPAddr_Init(lpszIPFile, lpszISPFile))
    {
        printf("APIModule_IPAddr_Init:%lX\n", APIIPMac_GetLastError());
        return -1;
    }

    XENGINE_IPADDRINFO st_IPAddrInfo = {};
    _xstprintf(st_IPAddrInfo.tszIPAddr, _X("117.172.221.14"));

    if (!APIModule_IPAddr_Query(&st_IPAddrInfo))
    {
		printf("APIModule_IPAddr_Query:%lX\n", APIIPMac_GetLastError());
		return -1;
    }
    printf("%s=%s,%s,%s,%s,%s\n", st_IPAddrInfo.tszIPAddr, st_IPAddrInfo.tszIPContinent, st_IPAddrInfo.tszIPCountry, st_IPAddrInfo.tszIPProvince, st_IPAddrInfo.tszIPCity, st_IPAddrInfo.tszIPISP);

    APIModule_IPAddr_UnInit();
    return 0;
}