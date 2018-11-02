/*
 * If not stated otherwise in this file or this component's Licenses.txt file the
 * following copyright and licenses apply:
 *
 * Copyright 2016 RDK Management
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
*/

#include "ansc_platform.h"
#include "ansc_load_library.h"
#include "cosa_plugin_api.h"
#include "plugin_main.h"
#include "servicemanager.h"
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
	
    PCOSA_PLUGIN_INFO               pPlugInfo  = (PCOSA_PLUGIN_INFO)hCosaPlugInfo;

    if ( uMaxVersionSupported < THIS_PLUGIN_VERSION )
    {
    	CcspServiceError("%s Exit ERROR Version not supported! \n", __FUNCTION__);

      /* this version is not supported */
        return -1;
    }   
    
    pPlugInfo->uPluginVersion       = THIS_PLUGIN_VERSION;
    /* register the back-end apis for the data model */
    CcspServicePrint("Registering the back-end apis for the data model\n");

    pPlugInfo->RegisterFunction(pPlugInfo->hContext, "Services_GetEntryCount",  Services_GetEntryCount);
    pPlugInfo->RegisterFunction(pPlugInfo->hContext, "Services_GetEntry",  Services_GetEntry);
    pPlugInfo->RegisterFunction(pPlugInfo->hContext, "Services_GetParamStringValue",  Services_GetParamStringValue);
    pPlugInfo->RegisterFunction(pPlugInfo->hContext, "Services_SetParamStringValue",  Services_SetParamStringValue);
    pPlugInfo->RegisterFunction(pPlugInfo->hContext, "Services_Validate",  Services_Validate);
    pPlugInfo->RegisterFunction(pPlugInfo->hContext, "Services_Commit",  Services_Commit);
    pPlugInfo->RegisterFunction(pPlugInfo->hContext, "Services_Rollback",  Services_Rollback);
    

    /* Create ServiceManager Object for Settings */
    g_pServiceManager = (PCOSA_DATAMODEL_SERVICEMANAGER)CosaServiceManagerCreate();

    if ( g_pServiceManager )
    {
    	  CcspServicePrint("Initializing CosaServiceManager\n");
    	  CosaServiceManagerInitialize(g_pServiceManager);
    }
    else
    {
    	CcspServiceError("%s exit ERROR CosaServiceManagerCreate returned 0!!!\n", __FUNCTION__);
    }

	

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
        
        CosaServiceManagerRemove(g_pServiceManager);
    }

    g_pServiceManager = NULL;
}
