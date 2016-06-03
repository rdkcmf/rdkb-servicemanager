/******************************************************************************
   Copyright [2016] [Comcast]

   Comcast Proprietary and Confidential

   All Rights Reserved.

   Unauthorized copying of this file, via any medium is strictly prohibited

******************************************************************************/
   
#include "ansc_platform.h"
#include "cosa_servicemanager_dml.h"
#include "cosa_servicemanager_internal.h"
#include "ssp_global.h"

extern ANSC_HANDLE bus_handle;
extern char g_Subsystem[32];
extern COSA_DATAMODEL_SERVICEMANAGER* g_pServiceManager;

//MURUGAN STUB instead of HAL
ULONG g_ServiceManager_ExpirationTime = 123456789;
char g_ServiceManager_Token[1024];

ANSC_STATUS
CosaDmlServiceManagerInit
    (
        ANSC_HANDLE                 hThisObject
    )
{
    ANSC_STATUS                     returnStatus        = ANSC_STATUS_SUCCESS;

	return returnStatus;
}


BOOL
X_RDKCENTRAL_COM_ServiceManager_GetParamBoolValue
(
    ANSC_HANDLE                 hInsContext,
    char*                       ParamName,
    BOOL*                       pBool
)
{
    printf("[ServiceManager] %s : ENTER \n", __FUNCTION__ );

    //nothing to do

    printf("[ServiceManager] %s : EXIT \n", __FUNCTION__ );
    return TRUE;
}


BOOL
X_RDKCENTRAL_COM_ServiceManager_SetParamBoolValue
(
	ANSC_HANDLE                 hInsContext,
	char*                       ParamName,
	BOOL                        bValue
)
{
    printf("[ServiceManager] %s : ENTER \n", __FUNCTION__ );

    //nothing to do

    printf("[ServiceManager] %s : EXIT \n", __FUNCTION__ );
    return TRUE;
}

BOOL
X_RDKCENTRAL_COM_ServiceManager_GetParamUlongValue
(
    ANSC_HANDLE                 hInsContext,
    char*                       ParamName,
    ULONG*                      puLong
)
{
	printf("[ServiceManager] %s : ENTER \n", __FUNCTION__ );

	if ( AnscEqualString(ParamName, "Expires", TRUE))
	{
		*puLong =  g_ServiceManager_ExpirationTime;
		printf("[ServiceManager] : ParamName[%s] Value[%d] \n" , ParamName, *puLong );
		return TRUE;
	}

	printf("[ServiceManager] %s : EXIT \n", __FUNCTION__ );
    return FALSE;
}


BOOL
X_RDKCENTRAL_COM_ServiceManager_SetParamUlongValue
(
    ANSC_HANDLE                 hInsContext,
    char*                       ParamName,
    ULONG                       uValue
)
{

	printf("[ServiceManager] %s : ENTER \n", __FUNCTION__ );
	
    if ( AnscEqualString(ParamName, "Expires", TRUE))
    {
        g_ServiceManager_ExpirationTime = uValue;
        printf("[ServiceManager] : ParamName[%s] Value[%d] \n", ParamName, uValue );
        return TRUE;
    }

	printf("[ServiceManager] %s : EXIT \n", __FUNCTION__ );
    return FALSE;
}


BOOL
X_RDKCENTRAL_COM_ServiceManager_GetParamStringValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       ParamName,
        char*                       pValue,
        ULONG*                      pUlSize
    )
{
	printf("[ServiceManager] %s : ENTER \n", __FUNCTION__ );

    if( AnscEqualString(ParamName, "Token", TRUE))
    {
		AnscCopyString(pValue, (char*)&g_ServiceManager_Token);
		*pUlSize = strlen(g_ServiceManager_Token) +1;
		printf("### MURUGAN ### [ServiceManager] : ParamName[%s] Value[%s] \n", ParamName, pValue );
		return TRUE;
    }

    printf("[ServiceManager] Unsupported parameter '%s'\n", ParamName);
    printf("[ServiceManager] %s : EXIT \n", __FUNCTION__ );

    return FALSE;
}


BOOL
X_RDKCENTRAL_COM_ServiceManager_SetParamStringValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       ParamName,
        char*                       pString
    )
{
	printf("[ServiceManager] %s : ENTER \n", __FUNCTION__ );

    if( AnscEqualString(ParamName, "Token", TRUE))
    {
    	//g_ServiceManager_Token = "";
		AnscCopyString(g_ServiceManager_Token, pString);
		printf("[ServiceManager] : ParamName[%s] Value[%s] \n", ParamName, pString );
		return TRUE;
    }

    printf("[ServiceManager] Unsupported parameter '%s'\n", ParamName);
    printf("[ServiceManager] %s : EXIT \n", __FUNCTION__ );

    return FALSE;
}


