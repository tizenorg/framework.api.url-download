/*
 * Copyright (c) 2011 Samsung Electronics Co., Ltd All Rights Reserved
 *
 * Licensed under the Apache License, Version 2.0 (the License);
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __TIZEN_WEB_DOWNLOAD_DOC_H__
#define __TIZEN_WEB_DOWNLOAD_DOC_H__

/**
 * @ingroup CAPI_CONTENT_FRAMEWORK
 * @defgroup CAPI_WEB_DOWNLOAD_MODULE Download
 * @brief  The DOWNLOAD API provides functions to create and manage one or more download requests.
 *
 * @section CAPI_WEB_DOWNLOAD_MODULE_HEADER Required Header
 *   \#include <download.h>
 *
 * @section CAPI_WEB_DOWNLOAD_MODULE_OVERVIEW Overview
 * The DOWNLOAD API provides functions to create and manage one or more download requests.
 *
 * Major features :
 * - After getting @a download_id from download_create(), other APIs use @a download_id as parameter.
 * - Even if the device is off, @a download_id is available for 48 hours if the user does not call download_destroy().
 * - Supports the callback that is called whenever the status of download changes.
 * - Even if the client process is terminated, download is going on.
 *   If you want to stop a download, download_cancel() or download_destroy() should be called.
 *
 * @section CAPI_WEB_DOWNLOAD_MODULE_FEATURE Related Features
 * This API is related with the following features:\n
 *  - http://tizen.org/feature/network.telephony\n
 *  - http://tizen.org/feature/network.wifi\n
 *  - http://tizen.org/feature/network.wifi.direct\n
 *
 * It is recommended to design feature related codes in your application for reliability.\n
 *
 * You can check if a device supports the related features for this API by using @ref CAPI_SYSTEM_SYSTEM_INFO_MODULE, thereby controlling the procedure of your application.\n
 *
 * To ensure your application is only running on the device with specific features, please define the features in your manifest file using the manifest editor in the SDK.\n
 *
 * More details on featuring your application can be found from <a href="../org.tizen.mobile.native.appprogramming/html/ide_sdk_tools/feature_element.htm"><b>Feature Element</b>.</a>
 *
 */

#endif /* __TIZEN_WEB_DOWNLOAD_DOC_H__ */
