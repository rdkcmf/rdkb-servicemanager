/******************************************************************************
   Copyright [2016] [Comcast]

   Comcast Proprietary and Confidential

   All Rights Reserved.

   Unauthorized copying of this file, via any medium is strictly prohibited

******************************************************************************/

#include "ansc_platform.h"
#include "ansc_load_library.h"
#include "cosa_plugin_api.h"
#include "plugin_main.h"
#include "cosa_servicemanager_dml.h"
#include "cosa_servicemanager_internal.h"

#define THIS_PLUGIN_VERSION                         1

COSA_DATAMODEL_SERVICEMANAGER* g_pServiceManager = NULL;

int ANSC_EXPORT_API
COSA_Init
    (
        ULONG                       uMaxVersionSupported, 
        void*                       hCosaPlugInfo         /* PCOSA_PLUGIN_INFO passed in by the caller */
    )
{
	printf("MURUGAN: %s ENTER \n", __FUNCTION__);
    PCOSA_PLUGIN_INFO               pPlugInfo  = (PCOSA_PLUGIN_INFO)hCosaPlugInfo;

    if ( uMaxVersionSupported < THIS_PLUGIN_VERSION )
    {
    	printf("MURUGAN: %s Exit ERROR Version not supported! \n", __FUNCTION__);

      /* this version is not supported */
        return -1;
    }   
    
    pPlugInfo->uPluginVersion       = THIS_PLUGIN_VERSION;
    /* register the back-end apis for the data model */
    printf("MURUGAN: register the back-end apis for the data model\n");
    pPlugInfo->RegisterFunction(pPlugInfo->hContext, "X_RDKCENTRAL_COM_ServiceManager_GetParamBoolValue",  X_RDKCENTRAL_COM_ServiceManager_GetParamBoolValue);
    pPlugInfo->RegisterFunction(pPlugInfo->hContext, "X_RDKCENTRAL_COM_ServiceManager_SetParamBoolValue",  X_RDKCENTRAL_COM_ServiceManager_SetParamBoolValue);
    pPlugInfo->RegisterFunction(pPlugInfo->hContext, "X_RDKCENTRAL_COM_ServiceManager_GetParamUlongValue",  X_RDKCENTRAL_COM_ServiceManager_GetParamUlongValue);
    pPlugInfo->RegisterFunction(pPlugInfo->hContext, "X_RDKCENTRAL_COM_ServiceManager_SetParamUlongValue",  X_RDKCENTRAL_COM_ServiceManager_SetParamUlongValue);
    pPlugInfo->RegisterFunction(pPlugInfo->hContext, "X_RDKCENTRAL_COM_ServiceManager_GetParamStringValue",  X_RDKCENTRAL_COM_ServiceManager_GetParamStringValue);
    pPlugInfo->RegisterFunction(pPlugInfo->hContext, "X_RDKCENTRAL_COM_ServiceManager_SetParamStringValue",  X_RDKCENTRAL_COM_ServiceManager_SetParamStringValue);

    printf("MURUGAN: COSA_Init() - CosaServiceManagerCreate called\n");
    /* Create ServiceManager Object for Settings */
    g_pServiceManager = (PCOSA_DATAMODEL_SERVICEMANAGER)CosaServiceManagerCreate();

    if ( g_pServiceManager )
    {
        // print success
    	   printf("MURUGAN: COSA_Init() - CosaServiceManagerInitialize called\n");
    	  CosaServiceManagerInitialize(g_pServiceManager);
    }
    else
    {
    	printf("MURUGAN: %s exit ERROR CosaServiceManagerCreate returned 0!!!\n", __FUNCTION__);
    }

	printf("MURUGAN: %s EXIT \n", __FUNCTION__);

    return  0;
}

BOOL ANSC_EXPORT_API
COSA_IsObjectSupported
    (
        char*                        pObjName
    )
{
    
    return TRUE;
}

void ANSC_EXPORT_API
COSA_Unload
    (
        void
    )
{
    /* unload the memory here */
    if ( g_pServiceManager )
    {
        // print success
        CosaServiceManagerRemove(g_pServiceManager);
    }

    g_pServiceManager = NULL;
}
