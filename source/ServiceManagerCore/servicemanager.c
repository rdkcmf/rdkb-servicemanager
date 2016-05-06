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
    printf("### MURUGAN ### [ServiceManager] Registering ServiceManager component '%s' with CR ..\n", SERVICEMANAGER_COMPONENT_NAME);

    msgBusInit(SERVICEMANAGER_COMPONENT_NAME);
       
    printf("### MURUGAN ### [ServiceManager] Registered ServiceManager component '%s' with CR ..\n", SERVICEMANAGER_COMPONENT_NAME);

    while(1)
    {
        sleep(30);
    }

    printf("### MURUGAN ### [ServiceManager] ServiceManager %s EXIT\n", __FUNCTION__ );

    return 0;
}

