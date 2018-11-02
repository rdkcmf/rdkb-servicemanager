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
#include "servicemanager.h"
ANSC_HANDLE
CosaServiceManagerCreate
    (
        VOID
    )
{
	
	PCOSA_DATAMODEL_SERVICEMANAGER       pMyObject    = (PCOSA_DATAMODEL_SERVICEMANAGER)NULL;

    /*
     * We create object by first allocating memory for holding the variables and member functions.
     */
    pMyObject = (PCOSA_DATAMODEL_SERVICEMANAGER)AnscAllocateMemory(sizeof(COSA_DATAMODEL_SERVICEMANAGER));

    if ( !pMyObject )
    {
    	CcspServicePrint("%s exit ERROR \n", __FUNCTION__);
        return  (ANSC_HANDLE)NULL;
    }

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


    returnStatus = CosaDmlServiceManagerInit((ANSC_HANDLE)pMyObject);
    
    if ( returnStatus != ANSC_STATUS_SUCCESS )
    {

	CcspServicePrint("%s Exit ERROR \n", __FUNCTION__);
        return  returnStatus;
    }
    
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

    /* Remove self */
    AnscFreeMemory((ANSC_HANDLE)pMyObject);
    CcspServicePrint("%s EXIT \n", __FUNCTION__);

	return returnStatus;
}

