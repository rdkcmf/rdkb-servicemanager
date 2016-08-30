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
 * @brief Enables or disables debug logs.
 */
#define SERVICEMANAGER_LOG_ERROR                 0
#define SERVICEMANAGER_LOG_INFO                  1
#define SERVICEMANAGER_LOG_PRINT                 2
#define CcspServiceError(...)                   _SERVICEMANAGER_LOG(SERVICEMANAGER_LOG_ERROR, __VA_ARGS__)
#define CcspServiceInfo(...)                    _SERVICEMANAGER_LOG(SERVICEMANAGER_LOG_INFO, __VA_ARGS__)
#define CcspServicePrint(...)                   _SERVICEMANAGER_LOG(SERVICEMANAGER_LOG_PRINT, __VA_ARGS__)




/**
 * @brief Initializes the Message Bus and registers component with the stack.
 *
 * @param[in] name Component Name.
 * @return status 0 for success and 1 for failure
 */
int msgBusInit(const char *name);

/**
 * @brief LOGInit Initialize RDK Logger
 */
void LOGInit();

/**
 * @brief _SERVICEMANAGER_LOG SERVICEMANAGER RDK logger API
 */

void _SERVICEMANAGER_LOG(unsigned int level, const char *msg, ...)
    __attribute__((format (printf, 2, 3)));


#endif /* _SERVICEMANAGER_H_ */
