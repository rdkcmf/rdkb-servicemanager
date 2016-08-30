/******************************************************************************
   Copyright [2016] [Comcast]

   Comcast Proprietary and Confidential

   All Rights Reserved.

   Unauthorized copying of this file, via any medium is strictly prohibited

******************************************************************************/
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

