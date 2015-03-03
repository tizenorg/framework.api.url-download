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
 * @ingroup CAPI_WEB_FRAMEWORK
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
 * - After getting download_id from download_create(), other APIs use download_id as parameter.
 * - Even if the device is off, download_id is available for 48 hours if user did't call download_destroy().
 * - support the callback that called whenever changed the status of download.
 * - Even if the client process is terminated, download is going on.
 *   If wanna stop a download, download_cancel() or download_destroy() should be called.
 *
 */

#endif /* __TIZEN_WEB_DOWNLOAD_DOC_H__ */
