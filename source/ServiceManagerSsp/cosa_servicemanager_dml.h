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


***********************************************************************/
BOOL
X_RDKCENTRAL_COM_ServiceManager_GetParamBoolValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       ParamName,
        BOOL*                       pBool
    );

BOOL
X_RDKCENTRAL_COM_ServiceManager_SetParamBoolValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       ParamName,
        BOOL                        bValue
    );

BOOL
X_RDKCENTRAL_COM_ServiceManager_GetParamUlongValue
    (
		ANSC_HANDLE                 hInsContext,
		char*                       ParamName,
		ULONG*                      puLong
    );

BOOL
X_RDKCENTRAL_COM_ServiceManager_SetParamUlongValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       ParamName,
       ULONG                      uValue
    );

BOOL
X_RDKCENTRAL_COM_ServiceManager_GetParamStringValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       ParamName,
        char*                       pValue,
        ULONG*                      pUlSize
    );

BOOL
X_RDKCENTRAL_COM_ServiceManager_SetParamStringValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       ParamName,
        char*                       pString
    );


#endif //_COSA_SERVICEMANAGER_DML_H



