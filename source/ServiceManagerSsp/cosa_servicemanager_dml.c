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
#include "servicemanager.h"
#include "cosa_servicemanager_dml.h"
#include "cosa_servicemanager_internal.h"
#include "ssp_global.h"
#include "svc_agt.h"
#include "svcagt_log.h"

#define SVCAGT_DIR_PATH  "/nvram"
#define SVCAGT_EXCLUDE_PATH  "/usr/ccsp/ccsp-servicemanager-broadband"

/* RDKB Logger defines */
#define LOG_FATAL 0
#define LOG_ERROR 1
#define LOG_WARN 2
#define LOG_NOTICE 3
#define LOG_INFO 4
#define LOG_DEBUG 5

#define DEBUG_INI_NAME  "/etc/debug.ini"

extern ANSC_HANDLE bus_handle;
service_list_item_t *service_list = NULL;
int numOfServices = -1;
static void __report_log (int level, const char * log_msg);


/**
 * @brief LOGInit Initialize RDK Logger
 */

void LOGInit()
{
#ifdef FEATURE_SUPPORT_RDKLOG
    RDK_LOGGER_INIT();
#endif
}

/**
 * @brief _SERVICEMANAGER_LOG SERVICEMANAGER RDK Logger API
 *
 * @param[in] level LOG Level
 * @param[in] msg Message to be logged 
 */
void _SERVICEMANAGER_LOG(unsigned int level, const char *msg, ...)
{
	va_list arg;
	char *pTempChar = NULL;
	int ret = 0;
	unsigned int rdkLogLevel = LOG_DEBUG;

	switch(level)
	{
		case SERVICEMANAGER_LOG_ERROR:
			rdkLogLevel = LOG_ERROR;
			break;

		case SERVICEMANAGER_LOG_INFO:
			rdkLogLevel = LOG_INFO;
			break;

		case SERVICEMANAGER_LOG_PRINT:
			rdkLogLevel = LOG_DEBUG;
			break;
	}
	
	
	if( rdkLogLevel <= LOG_INFO )
	{
		pTempChar = (char *)malloc(4096);
		if(pTempChar)
		{
			
			va_start(arg, msg);
			ret = vsnprintf(pTempChar, 4096, msg,arg);
			if(ret < 0)
			{
				perror(pTempChar);
			}
			va_end(arg);
			 
			RDK_LOG(rdkLogLevel, "LOG.RDK.ServiceManager", "%s", pTempChar);
			
			if(pTempChar !=NULL)
			{
				free(pTempChar);
				pTempChar = NULL;
			}
			
		}
	}
	
}



/**
 * @brief __report_log service-agent library log handler 
 * service-agent library log handler for integrating library logs with rdk-logger
 */
static void __report_log (int level, const char * log_msg)
{
	
	if (level == LEVEL_INFO) 
	{
		CcspServiceInfo("Service-Agent: %s", log_msg);
	}
	if (level == LEVEL_ERROR) 
	{
  	        CcspServiceError("Service-Agent: %s", log_msg);
	}
	if (level == LEVEL_DEBUG) 
	{
  	        CcspServicePrint("Service-Agent: %s", log_msg);
	}
	
	return;
}




ANSC_STATUS
CosaDmlServiceManagerInit
    (
        ANSC_HANDLE                 hThisObject
    )
{
	int svc_ret = -1;
   	
	CcspServicePrint("Initialize service-agent under :%s, exclude path is:%s\n", SVCAGT_DIR_PATH, SVCAGT_EXCLUDE_PATH);
	#ifdef SVCAGENT_LOGGER
		svc_ret = svc_agt_init (SVCAGT_DIR_PATH, SVCAGT_EXCLUDE_PATH, __report_log);
	#else
		svc_ret = svc_agt_init (SVCAGT_DIR_PATH, SVCAGT_EXCLUDE_PATH, NULL);
	#endif
 
	if (svc_ret == 0)
	{
		CcspServiceInfo("svc_agt initialized successfully\n");
	}
	else
	{
		CcspServiceError("svc_agt initialization failed, err no:%d\n", svc_ret);
		return ANSC_STATUS_FAILURE;
	}
	
	
	CcspServicePrint("setting db_query as true to get db state, no systemd\n");
	numOfServices = svc_agt_get_all (&service_list, true);
	
	 if (numOfServices >= 0) 
	 {
	 	CcspServiceInfo("Currently running %d services in system\n", numOfServices);
                svcagt_show_service_list (service_list);
               
         } 
         else 
         {
                CcspServiceError("Failed to get numOfServices from svc_agt list\n");
		return ANSC_STATUS_FAILURE;
         }

	return ANSC_STATUS_SUCCESS;
}


/***********************************************************************

 APIs for Object:

    X_RDKCENTRAL_COM_ServiceAgent.Services.{i}.

    *  Services_GetEntryCount
    *  Services_GetEntry
    *  Services_GetParamStringValue
    *  Services_SetParamStringValue
    *  Services_Validate
    *  Services_Commit
    *  Services_Rollback

***********************************************************************/
/**********************************************************************  

    caller:     owner of this object 

    prototype: 

        ULONG
        Services_GetEntryCount
            (
                ANSC_HANDLE                 hInsContext
            );

    description:

        This function is called to retrieve the count of the table.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     The count of the table

**********************************************************************/
ULONG
Services_GetEntryCount
    (
        ANSC_HANDLE                 hInsContext
    )
{
	
	ULONG services_count = 0; 
	
	//This is to get the index value
	
	if( numOfServices >= 0) 
	{
		services_count = numOfServices;
		CcspServicePrint("services_count:%d\n", services_count);
		
	}
        
	return services_count;
}

/**********************************************************************  

    caller:     owner of this object 

    prototype: 

        ANSC_HANDLE
        Services_GetEntry
            (
                ANSC_HANDLE                 hInsContext,
                ULONG                       nIndex,
                ULONG*                      pInsNumber
            );

    description:

        This function is called to retrieve the entry specified by the index.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                ULONG                       nIndex,
                The index of this entry;

                ULONG*                      pInsNumber
                The output instance number;

    return:     The handle to identify the entry

**********************************************************************/
ANSC_HANDLE
Services_GetEntry
    (
        ANSC_HANDLE                 hInsContext,
        ULONG                       nIndex,
        ULONG*                      pInsNumber
    )
{

	
	service_list_item_t *pCur = NULL;
	 
	//Traverse through list with given index
	
	for(pCur = service_list; (pCur != NULL) && (nIndex > pCur->index); pCur = pCur->next);
	
 
   	CcspServicePrint("Services_GetEntry.. %p, %ld\n", (ANSC_HANDLE) (pCur), nIndex);
	*pInsNumber = pCur->index + 1;
	
    	return (ANSC_HANDLE) (pCur);
	

}


/**********************************************************************  

    caller:     owner of this object 

    prototype: 

        ULONG
        Services_GetParamStringValue
            (
                ANSC_HANDLE                 hInsContext,
                char*                       ParamName,
                char*                       pValue,
                ULONG*                      pUlSize
            );

    description:

        This function is called to retrieve string parameter value; 

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                char*                       pValue,
                The string value buffer;

                ULONG*                      pUlSize
                The buffer of length of string value;
                Usually size of 1023 will be used.
                If it's not big enough, put required size here and return 1;

    return:     0 if succeeded;
                1 if short of buffer size; (*pUlSize = required size)
                -1 if not supported.

**********************************************************************/
ULONG
Services_GetParamStringValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       ParamName,
        char*                       pValue,
        ULONG*                      pUlSize
    )
{
  
	int ret = -1;
	unsigned index = 0; 
	service_info_t svc_info;
	
	service_list_item_t *pServices = (service_list_item_t*) hInsContext;
    	index = pServices->index;
    	
	
	if( AnscEqualString(ParamName, "Name", TRUE))
	{
		
		ret = svc_agt_get (index, &svc_info, true);
		
		if(ret ==0)
		{
			CcspServicePrint("svc_agt_get get success for parameter:%s", ParamName);
			
			if(svc_info.svc_name != NULL)
			{
				AnscCopyString(pValue, svc_info.svc_name);
				return 0;
			}
		}
		else
		{
			CcspServiceError("Failed to Get value for parameter:%s\n", ParamName);
			return -1;
		}
	}
	
	if( AnscEqualString(ParamName, "GoalState", TRUE))
	{
		
		ret = svc_agt_get (index, &svc_info, true);
		
		if(ret ==0)
		{
			CcspServicePrint("svc_agt_get get success for parameter:%s", ParamName);
		
			if(svc_info.goal_state != NULL)
			{
				AnscCopyString(pValue, svc_info.goal_state);
				return 0;
			}
		}
		else
		{
			CcspServiceError("Failed to Get value for parameter:%s\n", ParamName);
			return -1;
		}
	}
	
	CcspServiceError("Unsupported Namespace:%s\n", ParamName);
	return -1;
	
		
}

/**********************************************************************  

    caller:     owner of this object 

    prototype: 

        BOOL
        Services_SetParamStringValue
            (
                ANSC_HANDLE                 hInsContext,
                char*                       ParamName,
                 int                         pString
            );

    description:

       This function is called to set string parameter value; 

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                char*                       pString
                The updated string value;

    return:     TRUE if succeeded.

**********************************************************************/
// Currently, SET is not supported for Name parameter

BOOL
Services_SetParamStringValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       ParamName,
        char*                       pString
    )
{
    /* check the parameter name and set the corresponding value */

    int ret = -1;
    unsigned index =0;  
  
       
    // Extract index of the service to be queried from list
    service_list_item_t *pServices = (service_list_item_t*) hInsContext;
    index = pServices->index;

    if( AnscEqualString(ParamName, "GoalState", TRUE))
    {
    	    ret = svc_agt_set (index, pString);
    	    
    	    if(ret ==0)
    	    {
    	    	 CcspServicePrint("svc_agt_set success for param:%s, index:%d\n", ParamName, index);
        	      return TRUE;

    	    }
    	    else
    	    {
    	    
    	        CcspServiceError("svc_agt_set failed for param:%s, index:%d\n", ParamName, index);
        	    return FALSE;
    	    }
    }
    
    else
    {
        CcspServiceError("SET is not supported for '%s'\n", ParamName); 
        return FALSE;
    }
}


/**********************************************************************  

    caller:     owner of this object 

    prototype: 

        BOOL
        Services_Validate
            (
                ANSC_HANDLE                 hInsContext,
                char*                       pReturnParamName,
                ULONG*                      puLength
            );

    description:

        This function is called to finally commit all the update.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       pReturnParamName,
                The buffer (128 bytes) of parameter name if there's a validation. 

                ULONG*                      puLength
                The output length of the param name. 

    return:     TRUE if there's no validation.

**********************************************************************/
BOOL
Services_Validate
    (
        ANSC_HANDLE                 hInsContext,
        char*                       pReturnParamName,
        ULONG*                      puLength
    )
{
 
    return TRUE;
}

/**********************************************************************  

    caller:     owner of this object 

    prototype: 

        ULONG
        Services_Commit
            (
                ANSC_HANDLE                 hInsContext
            );

    description:

        This function is called to finally commit all the update.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     The status of the operation.

**********************************************************************/
ULONG
Services_Commit
    (
        ANSC_HANDLE                 hInsContext
    )
{
    
    return 0;
}

/**********************************************************************  

    caller:     owner of this object 

    prototype: 

        ULONG
        Services_Rollback
            (
                ANSC_HANDLE                 hInsContext
            );

    description:

        This function is called to roll back the update whenever there's a 
        validation found.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     The status of the operation.

**********************************************************************/
ULONG
Services_Rollback
    (
        ANSC_HANDLE                 hInsContext
    )
{
	
    return 0;
}


