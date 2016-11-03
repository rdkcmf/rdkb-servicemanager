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
#ifndef  _COSA_SERVICEMANAGER_DML_H
#define  _COSA_SERVICEMANAGER_DML_H


#include "slap_definitions.h"


ANSC_STATUS
CosaDmlServiceManagerInit
    (
        ANSC_HANDLE                 hThisObject
    );


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
ULONG
Services_GetEntryCount
    (
        ANSC_HANDLE
    );

ANSC_HANDLE
Services_GetEntry
    (
        ANSC_HANDLE                 hInsContext,
        ULONG                       nIndex,
        ULONG*                      pInsNumber
    );


ULONG
Services_GetParamStringValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       ParamName,
        char*                       pValue,
        ULONG*                      pUlSize
    );
    
    
BOOL
Services_SetParamStringValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       ParamName,
        char*                       strValue
    );
    

BOOL
Services_Validate
    (
        ANSC_HANDLE                 hInsContext,
        char*                       pReturnParamName,
        ULONG*                      puLength
    );

ULONG
Services_Commit
    (
        ANSC_HANDLE                 hInsContext
    );

ULONG
Services_Rollback
    (
        ANSC_HANDLE                 hInsContext
    );


#endif //_COSA_SERVICEMANAGER_DML_H

