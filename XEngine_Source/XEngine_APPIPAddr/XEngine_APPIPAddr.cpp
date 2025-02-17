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

#ifdef _DEBUG
#ifdef _WIN64
#pragma comment(lib,"../x64/Debug/XEngine_APIModuleIPMac")
#else
#pragma comment(lib,"../Debug/XEngine_APIModuleIPMac")
#endif
#else
#ifdef _WIN64
#pragma comment(lib,"../x64/Release/XEngine_APIModuleIPMac")
#else
#pragma comment(lib,"../Release/XEngine_APIModuleIPMac")
#endif
#endif


int main()
{
#ifndef _DEBUG
	if (setlocale(LC_ALL, ".UTF8") == NULL)
	{
		AfxMessageBox(_T("Error setting locale.\n"));
		return false;
	}
#endif
    LPCXSTR lpszDBFile = _X("D:\\IPMacData\\XEngine_DBFile\\ip2region.xdb");
    if (!APIModule_IPAddr_Init(lpszDBFile))
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
    printf("%s=%s,%s,%s,%s,%s\n", st_IPAddrInfo.tszIPAddr, st_IPAddrInfo.tszIPCountry,st_IPAddrInfo.tszIPProvince, st_IPAddrInfo.tszIPCity, st_IPAddrInfo.tszIPCounty,st_IPAddrInfo.tszIPISP);

    APIModule_IPAddr_UnInit();
    return 0;
}