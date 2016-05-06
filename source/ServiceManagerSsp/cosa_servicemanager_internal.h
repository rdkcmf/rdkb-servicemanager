/******************************************************************************
   Copyright [2016] [Comcast]

   Comcast Proprietary and Confidential

   All Rights Reserved.

   Unauthorized copying of this file, via any medium is strictly prohibited

******************************************************************************/

#ifndef  _COSA_SERVICEMANAGER_INTERNAL_H
#define  _COSA_SERVICEMANAGER_INTERNAL_H


#include "ansc_platform.h"
#include "ansc_string_util.h"

#define COSA_DATAMODEL_SERVICEMANAGER_OID                                                  10

//#define  COSA_DATAMODEL_HARVESTER_CLASS_CONTENT                                             \
    /* start of WIFI object class content */                                                \
    ULONG                           uExpirationTime;   	    

typedef  struct
_COSA_DATAMODEL_SERVICEMANAGER                                               
{
//	COSA_DATAMODEL_SERVICEMANAGER_CLASS_CONTENT
}
COSA_DATAMODEL_SERVICEMANAGER,  *PCOSA_DATAMODEL_SERVICEMANAGER;

/*
    Standard function declaration 
*/
ANSC_HANDLE
CosaServiceManagerCreate
    (
        VOID
    );

ANSC_STATUS
CosaServiceManagerInitialize
    (
        ANSC_HANDLE                 hThisObject
    );

ANSC_STATUS
CosaServiceManagerRemove
    (
        ANSC_HANDLE                 hThisObject
    );
    

#endif 
