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
/**
 * @file ssp_action.c
 *
 * @description This file creates component which would register with RDK-B stack, uses functions for registration/deregistration functions of components provided by RDK-B.
 * 
 */

#include "ssp_global.h"
#include "dslh_dmagnt_interface.h"
#include "ccsp_trace.h"
#include "servicemanager.h"
/*----------------------------------------------------------------------------*/
/*                                   Macros                                   */
/*----------------------------------------------------------------------------*/
 
 #define  CCSP_DATAMODEL_XML_FILE           "/usr/ccsp/ccsp-servicemanager-broadband/TR181-ServiceManager.xml"


/*----------------------------------------------------------------------------*/
/*                               Library Objects                              */
/*----------------------------------------------------------------------------*/

PDSLH_CPE_CONTROLLER_OBJECT     pDslhCpeController              = NULL;
PCOMPONENT_COMMON    g_pComponent_COMMON  = NULL;
PCCSP_CCD_INTERFACE             pSsdCcdIf                       = (PCCSP_CCD_INTERFACE)NULL;
PDSLH_LCB_INTERFACE             pDslhLcbIf                      = (PDSLH_LCB_INTERFACE)NULL;


/*----------------------------------------------------------------------------*/
/*                           External Variables                               */
/*----------------------------------------------------------------------------*/

extern char                     g_Subsystem[32];
extern  ANSC_HANDLE             bus_handle;
extern  ULONG                   g_ulAllocatedSizePeak;

/*----------------------------------------------------------------------------*/
/*                           External Functions                               */
/*----------------------------------------------------------------------------*/

/**
 * @brief 
 * This function creates component object in the CR(Component Registrar).
 */
ANSC_STATUS ssp_create()
{
    /* Create component common data model object */

     g_pComponent_COMMON = (PCOMPONENT_COMMON)AnscAllocateMemory(sizeof(COMPONENT_COMMON));

    if ( ! g_pComponent_COMMON )
    {
       CcspServiceError(" %s exit ERROR - no memory \n", __FUNCTION__);
       return ANSC_STATUS_RESOURCES;
    }

    CcspServicePrint("%s - ComponentCommonDmInit called \n", __FUNCTION__);

    ComponentCommonDmInit( g_pComponent_COMMON);

     g_pComponent_COMMON->Name     = AnscCloneString(CCSP_COMPONENT_NAME);
     g_pComponent_COMMON->Version  = 1;
     g_pComponent_COMMON->Author   = AnscCloneString("Your name");

    /* Create ComponentCommonDatamodel interface*/
    if ( !pSsdCcdIf )
    {
        pSsdCcdIf = (PCCSP_CCD_INTERFACE)AnscAllocateMemory(sizeof(CCSP_CCD_INTERFACE));

        if ( !pSsdCcdIf )
        {
           	CcspServiceError(" %s exit ERROR - no memory \n", __FUNCTION__);
            return ANSC_STATUS_RESOURCES;
        }
        else
        {
            AnscCopyString(pSsdCcdIf->Name, CCSP_CCD_INTERFACE_NAME);

            pSsdCcdIf->InterfaceId              = CCSP_CCD_INTERFACE_ID;
            pSsdCcdIf->hOwnerContext            = NULL;
            pSsdCcdIf->Size                     = sizeof(CCSP_CCD_INTERFACE);

            pSsdCcdIf->GetComponentName         = ssp_CcdIfGetComponentName;
            pSsdCcdIf->GetComponentVersion      = ssp_CcdIfGetComponentVersion;
            pSsdCcdIf->GetComponentAuthor       = ssp_CcdIfGetComponentAuthor;
            pSsdCcdIf->GetComponentHealth       = ssp_CcdIfGetComponentHealth;
            pSsdCcdIf->GetComponentState        = ssp_CcdIfGetComponentState;
            pSsdCcdIf->GetLoggingEnabled        = ssp_CcdIfGetLoggingEnabled;
            pSsdCcdIf->SetLoggingEnabled        = ssp_CcdIfSetLoggingEnabled;
            pSsdCcdIf->GetLoggingLevel          = ssp_CcdIfGetLoggingLevel;
            pSsdCcdIf->SetLoggingLevel          = ssp_CcdIfSetLoggingLevel;
            pSsdCcdIf->GetMemMaxUsage           = ssp_CcdIfGetMemMaxUsage;
            pSsdCcdIf->GetMemMinUsage           = ssp_CcdIfGetMemMinUsage;
            pSsdCcdIf->GetMemConsumed           = ssp_CcdIfGetMemConsumed;
            pSsdCcdIf->ApplyChanges             = ssp_CcdIfApplyChanges;
        }
    }

    /* Create ComponentCommonDatamodel interface*/
    if ( !pDslhLcbIf )
    {
        pDslhLcbIf = (PDSLH_LCB_INTERFACE)AnscAllocateMemory(sizeof(DSLH_LCB_INTERFACE));

        if ( !pDslhLcbIf )
        {
        	CcspServiceError(" %s exit ERROR - no memory \n", __FUNCTION__);

            return ANSC_STATUS_RESOURCES;
        }
        else
        {
            AnscCopyString(pDslhLcbIf->Name, CCSP_LIBCBK_INTERFACE_NAME);

            pDslhLcbIf->InterfaceId              = CCSP_LIBCBK_INTERFACE_ID;
            pDslhLcbIf->hOwnerContext            = NULL;
            pDslhLcbIf->Size                     = sizeof(DSLH_LCB_INTERFACE);
        }
    }
   	

    pDslhCpeController = DslhCreateCpeController(NULL, NULL, NULL);

    if ( !pDslhCpeController )
    {
        CcspServiceError("CANNOT Create pDslhCpeController... Exit!\n");

        return ANSC_STATUS_RESOURCES;
    }
	
    return ANSC_STATUS_SUCCESS;
}

/**
 * @brief 
 * This function establish connection from the component to the CR(Component Registrar).
 */
ANSC_STATUS ssp_engage()
{
	ANSC_STATUS					    returnStatus                = ANSC_STATUS_SUCCESS;
    PCCC_MBI_INTERFACE              pSsdMbiIf                   = (PCCC_MBI_INTERFACE)MsgHelper_CreateCcdMbiIf((void*)bus_handle, g_Subsystem);
    char                            CrName[256];


     g_pComponent_COMMON->Health = CCSP_COMMON_COMPONENT_HEALTH_Yellow;

    /* data model configuration */
    pDslhCpeController->AddInterface((ANSC_HANDLE)pDslhCpeController, (ANSC_HANDLE)pDslhLcbIf);
    pDslhCpeController->AddInterface((ANSC_HANDLE)pDslhCpeController, (ANSC_HANDLE)pSsdMbiIf);
    pDslhCpeController->AddInterface((ANSC_HANDLE)pDslhCpeController, (ANSC_HANDLE)pSsdCcdIf);
    pDslhCpeController->SetDbusHandle((ANSC_HANDLE)pDslhCpeController, (ANSC_HANDLE)bus_handle);
    pDslhCpeController->Engage((ANSC_HANDLE)pDslhCpeController);

    if ( g_Subsystem[0] != 0 )
    {
        _ansc_sprintf(CrName, "%s%s", g_Subsystem, CCSP_DBUS_INTERFACE_CR);
    }
    else
    {
        _ansc_sprintf(CrName, "%s", CCSP_DBUS_INTERFACE_CR);
    }
  	

    returnStatus =
        pDslhCpeController->RegisterCcspDataModel
            (
                (ANSC_HANDLE)pDslhCpeController,
                CrName,                                    /* CCSP_DBUS_INTERFACE_CR, CCSP CR ID */
                CCSP_DATAMODEL_XML_FILE,                   /* Data Model XML file. Can be empty if only base data model supported. */
                CCSP_COMPONENT_NAME,            /* Component Name    */
                CCSP_COMPONENT_VERSION,         /* Component Version */
                CCSP_COMPONENT_PATH,            /* Component Path    */
                g_Subsystem                                /* Component Prefix  */
            );

    if ( returnStatus == ANSC_STATUS_SUCCESS )
    {
        /* System is fully initialized */
     	CcspServiceInfo(" %s - RegisterCcspDataModel success.  System is fully initialized.\n", __FUNCTION__);
     	g_pComponent_COMMON->Health = CCSP_COMMON_COMPONENT_HEALTH_Green;
    }
    else
    {
     	CcspServiceError(" %s - RegisterCcspDataModel returned FAILURE!!! \n", __FUNCTION__);

    }
	

    return ANSC_STATUS_SUCCESS;
}

/**
 * @brief 
 * This function cancel the connection and delete component object from CR(Component Registrar).
 */
ANSC_STATUS ssp_cancel()
{
	int                             nRet  = 0;
    char                            CrName[256];
    char                            CpName[256];
	

    if(  g_pComponent_COMMON == NULL)
    {
    	CcspServicePrint(" %s exit ERROR \n", __FUNCTION__);

        return ANSC_STATUS_SUCCESS;
    }

    if ( g_Subsystem[0] != 0 )
    {
        _ansc_sprintf(CrName, "%s%s", g_Subsystem, CCSP_DBUS_INTERFACE_CR);
        _ansc_sprintf(CpName, "%s%s", g_Subsystem, CCSP_COMPONENT_NAME);
    }
    else
    {
        _ansc_sprintf(CrName, "%s", CCSP_DBUS_INTERFACE_CR);
        _ansc_sprintf(CpName, "%s", CCSP_COMPONENT_NAME);
    }
    /* unregister component */
    nRet = CcspBaseIf_unregisterComponent(bus_handle, CrName, CpName );  
    AnscTrace("unregisterComponent returns %d\n", nRet);

    pDslhCpeController->Cancel((ANSC_HANDLE)pDslhCpeController);
    AnscFreeMemory(pDslhCpeController);

    if ( pSsdCcdIf ) AnscFreeMemory(pSsdCcdIf);
    if (  g_pComponent_COMMON ) AnscFreeMemory( g_pComponent_COMMON);

     g_pComponent_COMMON = NULL;
    pSsdCcdIf                = NULL;
    pDslhCpeController       = NULL;

    return ANSC_STATUS_SUCCESS;
}


char* ssp_CcdIfGetComponentName(ANSC_HANDLE  hThisObject)
{
    return  g_pComponent_COMMON->Name;
}


ULONG ssp_CcdIfGetComponentVersion(ANSC_HANDLE  hThisObject)
{
    return  g_pComponent_COMMON->Version;
}


char* ssp_CcdIfGetComponentAuthor(ANSC_HANDLE hThisObject)
{
    return  g_pComponent_COMMON->Author;
}


ULONG ssp_CcdIfGetComponentHealth(ANSC_HANDLE  hThisObject)
{
    return  g_pComponent_COMMON->Health;
}


ULONG ssp_CcdIfGetComponentState(ANSC_HANDLE hThisObject)
{
    return  g_pComponent_COMMON->State;
}



BOOL ssp_CcdIfGetLoggingEnabled(ANSC_HANDLE hThisObject)
{
    return  g_pComponent_COMMON->LogEnable;
}


ANSC_STATUS ssp_CcdIfSetLoggingEnabled(ANSC_HANDLE  hThisObject,BOOL bEnabled)
{
    if( g_pComponent_COMMON->LogEnable == bEnabled) return ANSC_STATUS_SUCCESS;
     g_pComponent_COMMON->LogEnable = bEnabled;
    if(bEnabled) g_iTraceLevel = (INT)  g_pComponent_COMMON->LogLevel;
    else g_iTraceLevel = CCSP_TRACE_INVALID_LEVEL;

    return ANSC_STATUS_SUCCESS;
}


ULONG ssp_CcdIfGetLoggingLevel(ANSC_HANDLE hThisObject)
{
    return  g_pComponent_COMMON->LogLevel;
}


ANSC_STATUS ssp_CcdIfSetLoggingLevel(ANSC_HANDLE hThisObject,ULONG LogLevel)
{
    if( g_pComponent_COMMON->LogLevel == LogLevel) return ANSC_STATUS_SUCCESS;
     g_pComponent_COMMON->LogLevel = LogLevel;
    if( g_pComponent_COMMON->LogEnable) g_iTraceLevel = (INT)  g_pComponent_COMMON->LogLevel;

    return ANSC_STATUS_SUCCESS;
}


ULONG ssp_CcdIfGetMemMaxUsage(ANSC_HANDLE hThisObject)
{
    return g_ulAllocatedSizePeak;
}


ULONG ssp_CcdIfGetMemMinUsage(ANSC_HANDLE  hThisObject)
{
    return  g_pComponent_COMMON->MemMinUsage;
}


ULONG ssp_CcdIfGetMemConsumed(ANSC_HANDLE  hThisObject)
{
    LONG             size = 0;

    size = AnscGetComponentMemorySize(CCSP_COMPONENT_NAME);
    if (size == -1 )
        size = 0;

    return size;
}


ANSC_STATUS ssp_CcdIfApplyChanges(ANSC_HANDLE hThisObject)
{
    ANSC_STATUS                         returnStatus    = ANSC_STATUS_SUCCESS;
    /* Assume the parameter settings are committed immediately. */
    /* AnscSetTraceLevel((INT) g_pComponent_COMMON->LogLevel); */

    return returnStatus;
}
