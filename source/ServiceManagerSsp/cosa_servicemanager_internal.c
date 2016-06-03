/******************************************************************************
   Copyright [2016] [Comcast]

   Comcast Proprietary and Confidential

   All Rights Reserved.

   Unauthorized copying of this file, via any medium is strictly prohibited

******************************************************************************/

/**************************************************************************

    module: cosa_servicemanager_internal.c

        For COSA Data Model Library Development

    -------------------------------------------------------------------

    description:

        This file implementes back-end apis for the COSA Data Model Library

    -------------------------------------------------------------------

    environment:

        platform independent

**************************************************************************/

#include "cosa_servicemanager_internal.h"
#include "cosa_servicemanager_dml.h"

ANSC_HANDLE
CosaServiceManagerCreate
    (
        VOID
    )
{
	printf("%s ENTER \n", __FUNCTION__);
	PCOSA_DATAMODEL_SERVICEMANAGER       pMyObject    = (PCOSA_DATAMODEL_SERVICEMANAGER)NULL;

    /*
     * We create object by first allocating memory for holding the variables and member functions.
     */
    pMyObject = (PCOSA_DATAMODEL_SERVICEMANAGER)AnscAllocateMemory(sizeof(COSA_DATAMODEL_SERVICEMANAGER));

    if ( !pMyObject )
    {
    	printf("%s exit ERROR \n", __FUNCTION__);

        return  (ANSC_HANDLE)NULL;
    }
	printf("%s EXIT \n", __FUNCTION__);

    return  (ANSC_HANDLE)pMyObject;
}


ANSC_STATUS
CosaServiceManagerInitialize
    (
        ANSC_HANDLE                 hThisObject
    )
{
    ANSC_STATUS                     returnStatus        = ANSC_STATUS_SUCCESS;
    PCOSA_DATAMODEL_SERVICEMANAGER       pMyObject           = (PCOSA_DATAMODEL_SERVICEMANAGER)hThisObject;
	printf("%s ENTER \n", __FUNCTION__);


    returnStatus = CosaDmlServiceManagerInit((ANSC_HANDLE)pMyObject);
    
    if ( returnStatus != ANSC_STATUS_SUCCESS )
    {
    	printf("%s Exit ERROR \n", __FUNCTION__);

        return  returnStatus;
    }
    
	printf("%s EXIT \n", __FUNCTION__);

    return returnStatus;
}


ANSC_STATUS
CosaServiceManagerRemove
    (
        ANSC_HANDLE                 hThisObject
    )
{
    ANSC_STATUS                     returnStatus = ANSC_STATUS_SUCCESS;
    PCOSA_DATAMODEL_SERVICEMANAGER            pMyObject    = (PCOSA_DATAMODEL_SERVICEMANAGER)hThisObject;    
	printf("%s ENTER \n", __FUNCTION__);

    /* Remove self */
    AnscFreeMemory((ANSC_HANDLE)pMyObject);
	printf("%s EXIT \n", __FUNCTION__);

	return returnStatus;
}

