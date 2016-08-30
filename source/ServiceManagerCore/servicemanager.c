/******************************************************************************
   Copyright [2016] [Comcast]

   Comcast Proprietary and Confidential

   All Rights Reserved.

   Unauthorized copying of this file, via any medium is strictly prohibited

******************************************************************************/
   
#include <stdio.h>
#include "ansc_platform.h"
#include "servicemanager.h"

int main(int argc, char* argv[])
{   

    /* Initialize logger*/
    
    LOGInit();
    
    CcspServiceInfo("Registering ServiceManager component '%s' with CR ..\n", SERVICEMANAGER_COMPONENT_NAME);
    
    msgBusInit(SERVICEMANAGER_COMPONENT_NAME);
       
    CcspServiceInfo("Registered ServiceManager component '%s' with CR ..\n", SERVICEMANAGER_COMPONENT_NAME);

    while(1)
    {
        sleep(30);
    }

    CcspServiceInfo("ServiceManager %s EXIT\n", __FUNCTION__ );

    return 0;
}

