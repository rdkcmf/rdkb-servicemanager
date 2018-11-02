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
