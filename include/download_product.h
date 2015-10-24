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

#ifndef __TIZEN_WEB_DOWNLOAD_PRODUCT_H__
#define __TIZEN_WEB_DOWNLOAD_PRODUCT_H__

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @internal
 * @addtogroup CAPI_WEB_DOWNLOAD_MODULE
 * @brief download product APIs
 * @{
 */

/**
 * @brief Sets the 'enabled' state of the network bonding feature.
 *
 * @details This is only available depending on specific platform.
 *"Network bonding" feature use both data network and wifi network concurrently,
 *if the content size is over than specific size.
 *
 * @since_tizen 2.3
 * @privlevel public 
 * @privilege %http://tizen.org/privilege/download
 * @remarks This function should be called before downloading (see download_start()).
 * @remarks If the network type is not set as DOWNLOAD_NETWORK_ALL, the error is happened.
 * @param[in] download_id The download id
 * @param[in] enable The enable value
 * @return 0 on success, otherwise a negative error value
 * @retval #DOWNLOAD_ERROR_NONE              Successful
 * @retval #DOWNLOAD_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #DOWNLOAD_ERROR_INVALID_STATE     Invalid state
 * @retval #DOWNLOAD_ERROR_ID_NOT_FOUND      No Download ID
 * @retval #DOWNLOAD_ERROR_PERMISSION_DENIED Permission denied
 * @pre The state must not be #DOWNLOAD_STATE_DOWNLOADING, #DOWNLOAD_STATE_COMPLETED.
 * @see download_get_network_bonding()
  */
int download_set_network_bonding(int download_id, bool enable);


/**
 * @brief Gets the 'enabled' state of the network bonding feature.
 *
 * @since_tizen 2.3
 * @privlevel public 
 * @privilege %http://tizen.org/privilege/download
 * @param[in] download_id The download id
 * @param[out] enable The enable value
 * @return 0 on success, otherwise a negative error value
 * @retval #DOWNLOAD_ERROR_NONE              Successful
 * @retval #DOWNLOAD_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #DOWNLOAD_ERROR_ID_NOT_FOUND      No Download ID
 * @retval #DOWNLOAD_ERROR_PERMISSION_DENIED Permission denied
 * @see download_set_network_bonding()
 */
int download_get_network_bonding(int download_id, bool *enable);
/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __TIZEN_WEB_DOWNLOAD_PRODUCT_H__ */
