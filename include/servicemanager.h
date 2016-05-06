/******************************************************************************
   Copyright [2016] [Comcast]

   Comcast Proprietary and Confidential

   All Rights Reserved.

   Unauthorized copying of this file, via any medium is strictly prohibited

******************************************************************************/

#ifndef _SERVICEMANAGER_H_
#define _SERVICEMANAGER_H_

#define SERVICEMANAGER_COMPONENT_NAME		"CcspServiceManager"


/**
 * @brief Initializes the Message Bus and registers component with the stack.
 *
 * @param[in] name Component Name.
 * @return status 0 for success and 1 for failure
 */
int msgBusInit(const char *name);


#endif /* _SERVICEMANAGER_H_ */
