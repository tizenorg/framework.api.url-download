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

#ifndef __TIZEN_WEB_DOWNLOAD_H__
#define __TIZEN_WEB_DOWNLOAD_H__

#include <tizen.h>

#ifdef __cplusplus
extern "C"
{
#endif

 /**
 * @addtogroup CAPI_WEB_DOWNLOAD_MODULE
 * @{
 */

/**
 * @brief Enumeration of error code for URL download
 */
typedef enum
{
	DOWNLOAD_ERROR_NONE = TIZEN_ERROR_NONE, /**< Successful */
	DOWNLOAD_ERROR_INVALID_PARAMETER = TIZEN_ERROR_INVALID_PARAMETER, /**< Invalid parameter */
	DOWNLOAD_ERROR_OUT_OF_MEMORY = TIZEN_ERROR_OUT_OF_MEMORY, /**< Out of memory */
	DOWNLOAD_ERROR_NETWORK_UNREACHABLE = TIZEN_ERROR_NETWORK_UNREACHABLE, /**< Network is unreachable */
	DOWNLOAD_ERROR_CONNECTION_TIMED_OUT = TIZEN_ERROR_CONNECTION_TIME_OUT, /**< Http session time-out */
	DOWNLOAD_ERROR_NO_SPACE = TIZEN_ERROR_FILE_NO_SPACE_ON_DEVICE, /**< No space left on device */
	DOWNLOAD_ERROR_FIELD_NOT_FOUND = TIZEN_ERROR_KEY_NOT_AVAILABLE, /**< Specified field not found */
	DOWNLOAD_ERROR_PERMISSION_DENIED = TIZEN_ERROR_PERMISSION_DENIED, /**< Permission denied */
	DOWNLOAD_ERROR_INVALID_STATE = TIZEN_ERROR_WEB_CLASS | 0x21, /**< Invalid state */
	DOWNLOAD_ERROR_CONNECTION_FAILED = TIZEN_ERROR_WEB_CLASS | 0x22, /**< Connection failed */
	DOWNLOAD_ERROR_INVALID_URL = TIZEN_ERROR_WEB_CLASS | 0x24, /**< Invalid URL */
	DOWNLOAD_ERROR_INVALID_DESTINATION = TIZEN_ERROR_WEB_CLASS | 0x25, /**< Invalid destination */
	DOWNLOAD_ERROR_TOO_MANY_DOWNLOADS = TIZEN_ERROR_WEB_CLASS | 0x26, /**< Full of available simultaneous downloads */
	DOWNLOAD_ERROR_QUEUE_FULL = TIZEN_ERROR_WEB_CLASS | 0x27, /**< Full of available downloading items from server*/
	DOWNLOAD_ERROR_ALREADY_COMPLETED = TIZEN_ERROR_WEB_CLASS | 0x28, /**< The download is already completed */
	DOWNLOAD_ERROR_FILE_ALREADY_EXISTS = TIZEN_ERROR_WEB_CLASS | 0x29, /**< It is failed to rename the downloaded file */
	DOWNLOAD_ERROR_CANNOT_RESUME = TIZEN_ERROR_WEB_CLASS | 0x2a, /**< It cannot resume */
	DOWNLOAD_ERROR_TOO_MANY_REDIRECTS = TIZEN_ERROR_WEB_CLASS | 0x30, /**< In case of too may redirects from http response header*/
	DOWNLOAD_ERROR_UNHANDLED_HTTP_CODE = TIZEN_ERROR_WEB_CLASS | 0x31,  /**< The download cannot handle the http status value */
	DOWNLOAD_ERROR_REQUEST_TIMEOUT = TIZEN_ERROR_WEB_CLASS | 0x32, /**< There are no action after client create a download id*/
	DOWNLOAD_ERROR_RESPONSE_TIMEOUT = TIZEN_ERROR_WEB_CLASS | 0x33, /**< It does not call start API in some time although the download is created*/
	DOWNLOAD_ERROR_SYSTEM_DOWN = TIZEN_ERROR_WEB_CLASS | 0x34, /**< There are no response from client after rebooting download daemon*/
	DOWNLOAD_ERROR_ID_NOT_FOUND = TIZEN_ERROR_WEB_CLASS | 0x35, /**< The download id is not existed in download service module*/
	DOWNLOAD_ERROR_NO_DATA = TIZEN_ERROR_NO_DATA, /**< No data because the set API is not called */
	DOWNLOAD_ERROR_IO_ERROR = TIZEN_ERROR_IO_ERROR , /**< Internal I/O error */
} download_error_e;


/**
 * @brief Enumerations of state of download
 */
typedef enum
{
	DOWNLOAD_STATE_NONE, /**< It is ready to download */
	DOWNLOAD_STATE_READY, /**< It is ready to download */
	DOWNLOAD_STATE_QUEUED, /**< It is queued to start downloading */
	DOWNLOAD_STATE_DOWNLOADING, /**< The download is currently running */
	DOWNLOAD_STATE_PAUSED, /**< The download is waiting to resume */
	DOWNLOAD_STATE_COMPLETED, /**< The download is completed. */
	DOWNLOAD_STATE_FAILED, /**< The download failed. */
	DOWNLOAD_STATE_CANCELED, /**< User cancel the download item. */
} download_state_e;

/**
 * @brief Enumerations of network type for download
 */
typedef enum
{
	DOWNLOAD_NETWORK_DATA_NETWORK, /**< Download is available through data network */
	DOWNLOAD_NETWORK_WIFI, /**< Download is available through Wi-Fi */
	DOWNLOAD_NETWORK_WIFI_DIRECT, /**< Download is available through WiFi-Direct */
	DOWNLOAD_NETWORK_ALL /**< Download is available through either data network or Wi-Fi */
} download_network_type_e ;


/**
 * @brief Called when the download status is changed.
 *
 * @param [in] download The download id
 * @param [in] state The state of download 
 * @param [in] user_data The user data passed from download_set_state_changed_cb()
 * @pre download_start()  will cause this callback if you register this callback using download_set_state_changed_cb()
 * @see download_set_state_changed_cb()
 * @see download_unset_state_changed_cb()
 */
typedef void (*download_state_changed_cb) (int download_id,
	download_state_e state, void *user_data);

/**
 * @brief Called when the progress of download changes.
 *
 * @remarks This callback function is only invoked in the downloading state.
 * @param [in] download The download id
 * @param [in] received The size of the data received in bytes
 * @param [in] user_data The user data passed from download_set_progress_cb()
 * @pre This callback function is invoked if you register this callback using download_set_progress_cb().
 * @see download_cancel()
 * @see download_set_progress_cb()
 * @see download_unset_progress_cb()
 */
typedef void (*download_progress_cb) (int download_id, unsigned long long received, void *user_data);

/**
 * @brief Creates a download id.
 *
 * @remarks The @a download is released with download_destroy() by client.\n
 * @param [out] download A download id to be newly created on success
 * @return 0 on success, otherwise a negative error value.
 * @retval #DOWNLOAD_ERROR_NONE Successful
 * @retval #DOWNLOAD_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #DOWNLOAD_ERROR_OUT_OF_MEMORY Out of memory
 * @retval #DOWNLOAD_ERROR_IO_ERROR Internal I/O error
 * @retval #DOWNLOAD_ERROR_QUEUE_FULL Full of queue from download server
 * @post The download state will be #DOWNLOAD_STATE_READY
 * @see download_destroy()
 */
int download_create(int *download_id);


/**
 * @brief Unload all data concerning a download id from memory.
 *
 * @detail After calling this API, a download ID is existed at DB in certain time.\n
 * Within that time, it is able to use the other API with the download ID.
 * @remark If #DOWNLOAD_ERROR_ID_NOT_FOUND is returned, it means that the download ID is completely removed from DB.
 * @param [in] download The download id
 * @return 0 on success, otherwise a negative error value.
 * @retval #DOWNLOAD_ERROR_NONE Successful
 * @retval #DOWNLOAD_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #DOWNLOAD_ERROR_ID_NOT_FOUND No Download ID
 * @see download_create()
 */
int download_destroy(int download_id);


/**
 * @brief Sets the URL to download.
 *
 * @remarks This function should be called before downloading (See download_start())
 * @param [in] download The download id
 * @param [in] url The URL to download \n
 *  If the @a url is NULL, it clears the previous value.
 * @return 0 on success, otherwise a negative error value.
 * @retval #DOWNLOAD_ERROR_NONE Successful
 * @retval #DOWNLOAD_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #DOWNLOAD_ERROR_OUT_OF_MEMORY Out of memory
 * @retval #DOWNLOAD_ERROR_INVALID_STATE Invalid state
 * @retval #DOWNLOAD_ERROR_ID_NOT_FOUND No Download ID
 * @pre The state must be #DOWNLOAD_STATE_READY, #DOWNLOAD_STATE_FAILED, #DOWNLOAD_STATE_CANCELED
 * @see download_get_url()
 */
int download_set_url(int download_id, const char *url);


/**
 * @brief Gets the URL to download.
 *
 * @remarks The @a url must be released with free() by you.
 * @param [in] download The download id
 * @param [out] url The URL to download
 * @return 0 on success, otherwise a negative error value.
 * @retval #DOWNLOAD_ERROR_NONE Successful
 * @retval #DOWNLOAD_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #DOWNLOAD_ERROR_OUT_OF_MEMORY Out of memory
 * @retval #DOWNLOAD_ERROR_ID_NOT_FOUND No Download ID
 * @see download_set_url()
 */
int download_get_url(int download_id, char **url);


/**
 * @brief Sets the allowed network type for the downloaded file
 *
 * @details The file can be downloaded only under the allowed network.
 *
 * @remarks This function should be called before downloading (see download_start())
 * @param [in] download The download id
 * @param [in] net_type The network type which the client prefer
 * @return 0 on success, otherwise a negative error value.
 * @retval #DOWNLOAD_ERROR_NONE Successful
 * @retval #DOWNLOAD_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #DOWNLOAD_ERROR_INVALID_STATE Invalid state
 * @retval #DOWNLOAD_ERROR_ID_NOT_FOUND No Download ID
 * @pre The state must be #DOWNLOAD_STATE_READY, #DOWNLOAD_STATE_FAILED, #DOWNLOAD_STATE_CANCELED
 * @see download_get_network_type()
 * @see #download_network_type_e
 */
int download_set_network_type(int download_id, download_network_type_e net_type);


/**
 * @brief Gets the netowork type for the downloaded file
 *
 * @param [in] download The download id
 * @param [out] net_type The network type which is defined by client. 
 * @return 0 on success, otherwise a negative error value.
 * @retval #DOWNLOAD_ERROR_NONE Successful
 * @retval #DOWNLOAD_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #DOWNLOAD_ERROR_ID_NOT_FOUND No Download ID
 * @see download_set_network_type()
 * @see #download_network_type_e
 */
int download_get_network_type(int download_id, download_network_type_e *net_type);


/**
 * @brief Sets the destination for the downloaded file.
 *
 * @details The file will be downloaded to the specified destination.
 * The downloaded file is saved to an auto-generated file name in the destination.
 * If the destination is not specified, the file will be downloaded to default storage. (See the @ref CAPI_STORAGE_MODULE API)
 *
 * @remarks This function should be called before downloading (see download_start())
 * @param [in] download The download id
 * @param [in] path The absolute path to the downloaded file
 *  If the @a path is NULL, it clears the previous value.
 * @return 0 on success, otherwise a negative error value.
 * @retval #DOWNLOAD_ERROR_NONE Successful
 * @retval #DOWNLOAD_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #DOWNLOAD_ERROR_OUT_OF_MEMORY Out of memory
 * @retval #DOWNLOAD_ERROR_INVALID_STATE Invalid state
 * @retval #DOWNLOAD_ERROR_ID_NOT_FOUND No Download ID
 * @pre The state must be #DOWNLOAD_STATE_READY, #DOWNLOAD_STATE_FAILED, #DOWNLOAD_STATE_CANCELED
 * @see download_get_destination()
 */
int download_set_destination(int download_id, const char *path);


/**
 * @brief Gets the destination for the downloaded file.
 *
 * @remarks The @a path must be released with free() by you.
 * @param [in] download The download id
 * @param [out] path The absolute path to the downloaded file
 * @return 0 on success, otherwise a negative error value.
 * @retval #DOWNLOAD_ERROR_NONE Successful
 * @retval #DOWNLOAD_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #DOWNLOAD_ERROR_OUT_OF_MEMORY Out of memory
 * @retval #DOWNLOAD_ERROR_ID_NOT_FOUND No Download ID
 * @see download_set_destination()
 */
int download_get_destination(int download_id, char **path);


/**
 * @brief Sets the name for the downloaded file.
 *
 * @details The file will be downloaded to the specified destination as the given file name.
 * If the file name is not specified, the downloaded file is saved to an auto-generated file name in the destination.
 *
 * @remarks This function should be called before downloading (see download_start())
 * @param [in] download The download id
 * @param [in] file_name The file name for the downloaded file
 *  If the @a name is NULL, it clears the previous value.
 * @return 0 on success, otherwise a negative error value.
 * @retval #DOWNLOAD_ERROR_NONE Successful
 * @retval #DOWNLOAD_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #DOWNLOAD_ERROR_OUT_OF_MEMORY Out of memory
 * @retval #DOWNLOAD_ERROR_INVALID_STATE Invalid state
 * @retval #DOWNLOAD_ERROR_ID_NOT_FOUND No Download ID
 * @pre The state must be #DOWNLOAD_STATE_READY, #DOWNLOAD_STATE_FAILED, #DOWNLOAD_STATE_CANCELED
 * @see download_get_file_name()
 */
int download_set_file_name(int download_id, const char *file_name);


/**
 * @brief Gets the name which is set by user.
 *
 * @details If user do not set any name, it retruns NULL.
 *
 * @remarks The @a file_name must be released with free() by you.
 * @param [in] download The download id
 * @param [out] file_name The file name which is set by user.
 * @return 0 on success, otherwise a negative error value.
 * @retval #DOWNLOAD_ERROR_NONE Successful
 * @retval #DOWNLOAD_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #DOWNLOAD_ERROR_OUT_OF_MEMORY Out of memory
 * @retval #DOWNLOAD_ERROR_ID_NOT_FOUND No Download ID
 * @see download_set_file_name()
 */
int download_get_file_name(int download_id, char **file_name);


/**
 * @brief Sets the option value to register notification messages by download service module.
 * @details The tree types of notification message can be posted. Those are completion, failed and ongoing type.
 * When the notification message of failed and ongoing types from the notification tray, \n
 * the client application which call this API will be launched. \n
 *
 * @remarks The extra param should be set together (See download_set_notification_extra_param()). \n
 * The downloading and failed notification can be registerd only if the extra param for noticiation message is set. \n
 * If it is not, the client application can not know who request to launch itself. \n
 * It should be necessary to understand the action operation of notification click event.
 * @remarks If the competition notification message is selected from the notification tray,\n
 * the proper player application is launched automatically.
 * @remarks The default value is false. So if the client don't enable it, any notification messages are not registered.
 * @remarks This function should be called before downloading (See download_start())
 * @param[in] download The download id
 * @param[in] enable The boolean type. The true or false value is available.
 * @return 0 on success, otherwise a negative error value.
 * @retval #DOWNLOAD_ERROR_NONE Successful
 * @retval #DOWNLOAD_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #DOWNLOAD_ERROR_ID_NOT_FOUND No Download ID
 * @pre The state must be #DOWNLOAD_STATE_READY, #DOWNLOAD_STATE_FAILED, #DOWNLOAD_STATE_CANCELED
 * @see download_get_notification()
 * @see service_get_operation()
 */
int download_set_notification(int download_id, bool enable);

/**
 * @brief Gets the option value to register notification messages by download service module.
 * @param[in] download The download id
 * @param[out] enable The boolean type. The true or false value is retruned
 * @return 0 on success, otherwise a negative error value.
 * @retval #DOWNLOAD_ERROR_NONE Successful
 * @retval #DOWNLOAD_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #DOWNLOAD_ERROR_ID_NOT_FOUND No Download ID
 * @see download_set_notification()
 */
int download_get_notification(int download_id, bool *enable);

/**
 * @brief Sets the extra param data which pass by application service data when notification message is clicked
 * @details When client set the extra param data for ongoing notificaiton action, \n
 * it can get the data through service_get_extra_data() when client application is launched by notification action.
 *
 * @remarks This function should be called before downloading (See download_start())
 *
 * @param[in] download The download id
 * @param[in] key The character pointer type. The extra param has a pair of key and value
 * @param[in] values The character pointer array type. The extra param has a pair of key and value array
 * @param[in] length The length of value array
 * @return 0 on success, otherwise a negative error value.
 * @retval #DOWNLOAD_ERROR_NONE Successful
 * @retval #DOWNLOAD_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #DOWNLOAD_ERROR_ID_NOT_FOUND No Download ID
 * @see download_get_notification_extra_param()
 * @see download_remove_notification_extra_param()
 */
int download_add_notification_extra_param(int download_id, const char *key, const char **values, const unsigned int length);

/**
 * @brief Remove the extra param data which pass by application service data when notification message is clicked
 *
 * @remarks This function should be called before downloading (See download_start())
 *
 * @param[in] download The download id
 * @param[in] key The character pointer type. The extra param has a pair of key and value
 * @return 0 on success, otherwise a negative error value.
 * @retval #DOWNLOAD_ERROR_NONE Successful
 * @retval #DOWNLOAD_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #DOWNLOAD_ERROR_ID_NOT_FOUND No Download ID
 * @see download_add_notification_extra_param()
 * @see download_get_notification_extra_param()
 */
int download_remove_notification_extra_param(int download_id, const char *key);

/**
 * @brief Gets the extra param value to set by download_set_notification_extra_param
 * @param[in] download The download id
 * @param[out] key The character pointer type. The extra param has a pair of key and value
 * @param[out] values param The character pointer array type. The extra param has a pair of key and value array
 * @param[out] length The length of value array
 * @return 0 on success, otherwise a negative error value.
 * @retval #DOWNLOAD_ERROR_NONE Successful
 * @retval #DOWNLOAD_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #DOWNLOAD_ERROR_ID_NOT_FOUND No Download ID
 * @see download_set_notification_extra_param()
 */
int download_get_notification_extra_param(int download_id, const char *key, char ***values, unsigned int *length);

/**
 * @brief Gets the absolute path to save the downloaded file
 *
 * @remarks This function returns #DOWNLOAD_ERROR_INVALID_STATE if the download is not completed. \n
 * The @a path must be released with free() by you.
 * @param [in] download The download id
 * @param [out] path The absolute path to the downloaded file
 * @return 0 on success, otherwise a negative error value.
 * @retval #DOWNLOAD_ERROR_NONE Successful
 * @retval #DOWNLOAD_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #DOWNLOAD_ERROR_OUT_OF_MEMORY Out of memory
 * @retval #DOWNLOAD_ERROR_ID_NOT_FOUND No Download ID
 * @pre The download state must be #DOWNLOAD_STATE_COMPLETED.
 * @see download_set_file_name()
 * @see download_set_destination()
 */
int download_get_downloaded_file_path(int download_id, char **path);


/**
 * @brief Gets the mime type for downloading a content.
 *
 * @remarks This function returns #DOWNLOAD_ERROR_INVALID_STATE if the download has not been started. \n
 * The @a mime_type must be released with free() by you.
 * @param [in] download The download id
 * @param [out] mime_type The MIME type of the downloaded file
 * @return 0 on success, otherwise a negative error value.
 * @retval #DOWNLOAD_ERROR_NONE Successful
 * @retval #DOWNLOAD_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #DOWNLOAD_ERROR_OUT_OF_MEMORY Out of memory
 * @retval #DOWNLOAD_ERROR_ID_NOT_FOUND No Download ID
 * @see download_set_file_name()
 * @see download_set_destination()
 * @see download_get_downloaded_file_path()
 */
int download_get_mime_type(int download_id, char **mime_type);


/**
 * @brief Sets the option for auto download.
 * @details If this option is enabled, \n
 *  the previous downloading item is restarted automatically as soon as the download daemon is restarted. \n
 * And the download progress keep going after the client process is terminated.  \n
 * @remarks The client should call download_set_notification() and download_set_notification_extra_param() after call this API. \n
 *  If it is not, user do not receive the download result in case the client process is not alive.
 * @remarks The default value is false.
 * @param[in] download The download id
 * @param[in] enable The boolean value for auto download which is defined by clinet. 
 * @return 0 on success, otherwise a negative error value.
 * @retval #DOWNLOAD_ERROR_NONE Successful
 * @retval #DOWNLOAD_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #DOWNLOAD_ERROR_ID_NOT_FOUND No Download ID
 * @pre The state must be #DOWNLOAD_STATE_READY, #DOWNLOAD_STATE_FAILED, #DOWNLOAD_STATE_CANCELED
 * @see download_get_auto_download()
 * @see download_set_ongoing_notification()
 * @see download_set_notification_extra_param()
 *
 */
int download_set_auto_download(int download_id, bool enable);


/**
 * @brief Gets the value of option for auto download.
 *
 * @param [in] download The download id
 * @param [out] enable The boolean value for auto download which is defined by clinet. 
 * @return 0 on success, otherwise a negative error value.
 * @retval #DOWNLOAD_ERROR_NONE Successful
 * @retval #DOWNLOAD_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #DOWNLOAD_ERROR_ID_NOT_FOUND No Download ID
 * @see download_set_auto_download()
 */
int download_get_auto_download(int download_id, bool *enable);


/**
 * @brief Adds an HTTP header field to the download request
 *
 * @details The given HTTP header field will be included with the HTTP request of the download request. \n
 * Refer to the <a href="http://www.w3.org/Protocols/rfc2616/rfc2616-sec4.html#sec4.2">HTTP/1.1: HTTP Message Headers</a>
 * @remarks This function should be called before downloading (see download_start()) \n
 * This function replaces any existing value for the given key. \n
 * This function returns #DOWNLOAD_ERROR_INVALID_PARAMETER if field or value is zero-length string. 
 * @param [in] download The download id
 * @param [in] field The name of the HTTP header field
 * @param [in] value The value associated with given field
 * @return 0 on success, otherwise a negative error value.
 * @retval #DOWNLOAD_ERROR_NONE Successful
 * @retval #DOWNLOAD_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #DOWNLOAD_ERROR_OUT_OF_MEMORY Out of memory
 * @retval #DOWNLOAD_ERROR_INVALID_STATE Invalid state
 * @retval #DOWNLOAD_ERROR_IO_ERROR Internal I/O error
 * @retval #DOWNLOAD_ERROR_ID_NOT_FOUND No Download ID
 * @pre The state must be #DOWNLOAD_STATE_READY, #DOWNLOAD_STATE_FAILED, #DOWNLOAD_STATE_CANCELED
 * @see download_get_http_header_field()
 * @see download_remove_http_header_field()
 */
int download_add_http_header_field(int download_id, const char *field, const char *value);


/**
 * @brief Gets the value associated with given HTTP header field from the download
 *
 * @remarks This function returns #DOWNLOAD_ERROR_INVALID_PARAMETER if field is zero-length string. \n
 * The @a value must be released with free() by you.
 * @param [in] download The download id
 * @param [in] field The name of the HTTP header field
 * @param [out] value The value associated with given field
 * @return 0 on success, otherwise a negative error value.
 * @retval #DOWNLOAD_ERROR_NONE Successful
 * @retval #DOWNLOAD_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #DOWNLOAD_ERROR_OUT_OF_MEMORY Out of memory
 * @retval #DOWNLOAD_ERROR_INVALID_STATE Invalid state
 * @retval #DOWNLOAD_ERROR_FIELD_NOT_FOUND Specified field not found
 * @retval #DOWNLOAD_ERROR_ID_NOT_FOUND No Download ID
 * @see download_add_http_header_field()
 * @see download_remove_http_header_field()
 */
int download_get_http_header_field(int download_id, const char *field, char **value);

/**
 * @brief Gets all of the field added to the download request
 *
 * @remarks The @a value must be released with free() by you.
 * @param [in] download The download id
 * @param [out] the array of the HTTP header fields
 * @param [out] the number of the HTTP header fields
 * @return 0 on success, otherwise a negative error value.
 * @retval #DOWNLOAD_ERROR_NONE Successful
 * @retval #DOWNLOAD_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #DOWNLOAD_ERROR_OUT_OF_MEMORY Out of memory
 * @retval #DOWNLOAD_ERROR_INVALID_STATE Invalid state
 * @retval #DOWNLOAD_ERROR_ID_NOT_FOUND No Download ID
 * @see download_add_http_header_field()
 * @see download_remove_http_header_field()
 */
int download_get_http_header_field_list(int download_id, char ***fields, int *length);

/**
 * @brief Removes the given HTTP header field from the download
 *
 * @remarks This function should be called before downloading (see download_start()) \n
 * This function returns #DOWNLOAD_ERROR_INVALID_PARAMETER if field is zero-length string. 
 * @param [in] download The download id
 * @param [in] field The name of the HTTP header field
 * @return 0 on success, otherwise a negative error value.
 * @retval #DOWNLOAD_ERROR_NONE Successful
 * @retval #DOWNLOAD_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #DOWNLOAD_ERROR_OUT_OF_MEMORY Out of memory
 * @retval #DOWNLOAD_ERROR_INVALID_STATE Invalid state
 * @retval #DOWNLOAD_ERROR_FIELD_NOT_FOUND Specified field not found
 * @retval #DOWNLOAD_ERROR_IO_ERROR Internal I/O error
 * @retval #DOWNLOAD_ERROR_ID_NOT_FOUND No Download ID
 * @pre The state must be #DOWNLOAD_STATE_READY, #DOWNLOAD_STATE_FAILED, #DOWNLOAD_STATE_CANCELED
 * @see download_add_http_header_field()
 * @see download_get_http_header_field()
 */
int download_remove_http_header_field(int download_id, const char *field);


/**
 * @brief Registers a callback function to be invoked when the download state is changed.
 *
 * @remarks This function should be called before downloading (see download_start())
 * @param [in] download The download id
 * @param [in] callback The callback function to register
 * @param [in] user_data The user data to be passed to the callback function
 * @return 0 on success, otherwise a negative error value.
 * @retval #DOWNLOAD_ERROR_NONE Successful
 * @retval #DOWNLOAD_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #DOWNLOAD_ERROR_ID_NOT_FOUND No Download ID
 * @post download_state_changed_cb() will be invoked.
 * @see download_unset_state_changed_cb()
 * @see download_state_changed_cb()
*/
int download_set_state_changed_cb(int download_id, download_state_changed_cb callback, void* user_data);


/**
 * @brief Unregisters the callback function.
 *
 * @remarks This function should be called before downloading (see download_start())
 * @param [in] download The download id
 * @return 0 on success, otherwise a negative error value.
 * @retval #DOWNLOAD_ERROR_NONE Successful
 * @retval #DOWNLOAD_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #DOWNLOAD_ERROR_ID_NOT_FOUND No Download ID
 * @see download_set_state_changed_cb()
 * @see download_state_changed_cb()
*/
int download_unset_state_changed_cb(int download_id);


/**
 * @brief Registers a callback function to be invoked when progress of the download changes
 *
 * @remarks This function should be called before downloading (see download_start())
 * @param [in] download The download id
 * @param [in] callback The callback function to register
 * @param [in] user_data The user data to be passed to the callback function
 * @return 0 on success, otherwise a negative error value.
 * @retval #DOWNLOAD_ERROR_NONE Successful
 * @retval #DOWNLOAD_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #DOWNLOAD_ERROR_INVALID_STATE Invalid state
 * @retval #DOWNLOAD_ERROR_ID_NOT_FOUND No Download ID
 * @post download_progress_cb() will be invoked.
 * @see download_unset_progress_cb()
 * @see download_progress_cb()
*/
int download_set_progress_cb(int download_id, download_progress_cb callback, void *user_data);


/**
 * @brief Unregisters the callback function.
 *
 * @remarks This function should be called before downloading (see download_start())
 * @param [in] download The download id
 * @return 0 on success, otherwise a negative error value.
 * @retval #DOWNLOAD_ERROR_NONE Successful
 * @retval #DOWNLOAD_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #DOWNLOAD_ERROR_INVALID_STATE Invalid state
 * @retval #DOWNLOAD_ERROR_ID_NOT_FOUND No Download ID
 * @see download_set_progress_cb()
 * @see download_progress_cb()
*/
int download_unset_progress_cb(int download_id);


/**
 * @brief Starts or resumes the download, asynchronously.
 *
 * @details This function starts to download the current URL, or resumes the download if paused.
 *
 * @remarks The URL is the mandatory information to start the download.
 * @remarks It should call download_set_progress_cb() and download_set_state_changed_cb() again \n
 *  after the client process is restarted or download_destry() is called
 * @param [in] download The download id
 * @return 0 on success, otherwise a negative error value.
 * @retval #DOWNLOAD_ERROR_NONE Successful
 * @retval #DOWNLOAD_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #DOWNLOAD_ERROR_OUT_OF_MEMORY Out of memory
 * @retval #DOWNLOAD_ERROR_INVALID_STATE Invalid state
 * @retval #DOWNLOAD_ERROR_IO_ERROR Internal I/O error
 * @retval #DOWNLOAD_ERROR_URL Invalid URL
 * @retval #DOWNLOAD_ERROR_DESTINATION Invalid destination
 * @retval #DOWNLOAD_ERROR_ID_NOT_FOUND No Download ID
 * @retval #DOWNLOAD_ERROR_QUEUE_FULL Full of queue from download server
 * @pre The download state must be #DOWNLOAD_STATE_READY, #DOWNLOAD_STATE_PAUSED, #DOWNLOAD_STATE_CANCELED, #DOWNLOAD_STATE_FAILED.
 * @post The download state will be #DOWNLOAD_STATE_QUEUED or #DOWNLOAD_STATE_DOWNLOADING
 * @see download_set_url()
 * @see download_pause()
 * @see download_cancel()
 */
int download_start(int download_id);


/**
 * @brief Pauses the download, asynchronously.
 *
 * @remarks The paused download can be restarted with download_start() or canceled with download_cancel()
 * @param [in] download The download id
 * @return 0 on success, otherwise a negative error value.
 * @retval #DOWNLOAD_ERROR_NONE Successful
 * @retval #DOWNLOAD_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #DOWNLOAD_ERROR_OUT_OF_MEMORY Out of memory
 * @retval #DOWNLOAD_ERROR_INVALID_STATE Invalid state
 * @retval #DOWNLOAD_ERROR_IO_ERROR Internal I/O error
 * @retval #DOWNLOAD_ERROR_ID_NOT_FOUND No Download ID
 * @pre The download state must be #DOWNLOAD_STATE_DOWNLOADING.
 * @post The download state will be #DOWNLOAD_STATE_PAUSED.
 * @see download_start()
 * @see download_cancel()
 */
int download_pause(int download_id);


/**
 * @brief Cancel the download, asynchronously.
 *
 * @details This function cancels the running download and its state will be #DOWNLOAD_STATE_READY
 * @remarks The cancelled download can be restarted with download_start().
 * @param [in] download The download id
 * @return 0 on success, otherwise a negative error value.
 * @retval #DOWNLOAD_ERROR_NONE Successful
 * @retval #DOWNLOAD_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #DOWNLOAD_ERROR_OUT_OF_MEMORY Out of memory
 * @retval #DOWNLOAD_ERROR_INVALID_STATE Invalid state
 * @retval #DOWNLOAD_ERROR_IO_ERROR Internal I/O error
 * @retval #DOWNLOAD_ERROR_ID_NOT_FOUND No Download ID
 * @pre The download state must be #DOWNLOAD_STATE_QUEUED, #DOWNLOAD_STATE_DOWNLOADING, #DOWNLOAD_STATE_PAUSED.
 * @post The download state will be #DOWNLOAD_STATE_CANCELED.
 * @see download_start()
 */
int download_cancel(int download_id);


/**
 * @brief Gets the download's current state.
 *
 * @param [in] download The download id
 * @param [out] state The current state of the download
 * @return 0 on success, otherwise a negative error value.
 * @retval #DOWNLOAD_ERROR_NONE Successful
 * @retval #DOWNLOAD_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #DOWNLOAD_ERROR_ID_NOT_FOUND No Download ID
 * @see #download_state_e
 */
int download_get_state(int download_id, download_state_e *state);


/**
 * @brief Gets the full path of temporary file for downloading a content.
 *
 * @param [in] download The download id
 * @param [out] temp_path The full path of temporary file 
 * @return 0 on success, otherwise a negative error value.
 * @retval #DOWNLOAD_ERROR_NONE Successful
 * @retval #DOWNLOAD_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #DOWNLOAD_ERROR_ID_NOT_FOUND No Download ID
 * @pre The download state must be one of state after #DOWNLOAD_STATE_DOWNLOADING.
 * @see #download_set_state_changed_cb()
 * @see #download_unset_state_changed_cb()
 * @see download_start()
 */
int download_get_temp_path(int download_id, char **temp_path);


/**
 * @brief Gets the content name for downloading a file.
 *
 * @details This can be defined with referense of HTTP response header data.
 * The content name can be received when HTTP response header is received.
 *
 * @param [in] download The download id
 * @param [out] content_name The content name for displaying to user
 * @return 0 on success, otherwise a negative error value.
 * @retval #DOWNLOAD_ERROR_NONE Successful
 * @retval #DOWNLOAD_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #DOWNLOAD_ERROR_ID_NOT_FOUND No Download ID
 * @pre The download state must be one of state after #DOWNLOAD_STATE_DOWNLOADING.
 * @see #download_set_state_changed_cb()
 * @see #download_unset_state_changed_cb()
 * @see download_start()
 */
int download_get_content_name(int download_id, char **content_name);


/**
 * @brief Gets the total size for downloading a content.
 *
 * @details This data receive from content server. If the content sever don't send total size of the content, the value set as zero.
 *
 * @param [in] download The download id
 * @param [out] content_size The content size for displaying to user
 * @return 0 on success, otherwise a negative error value.
 * @retval #DOWNLOAD_ERROR_NONE Successful
 * @retval #DOWNLOAD_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #DOWNLOAD_ERROR_ID_NOT_FOUND No Download ID
 * @pre The download state must be one of state after #DOWNLOAD_STATE_DOWNLOADING.
 * @see #download_set_state_changed_cb()
 * @see #download_unset_state_changed_cb()
 * @see download_start()
 */
int download_get_content_size(int download_id, unsigned long long *content_size);


/**
 * @brief Gets the error value when the download is failed.
 *
 * @param [in] download The download id
 * @param [out] error The error value 
 * @return 0 on success, otherwise a negative error value.
 * @retval #DOWNLOAD_ERROR_NONE Successful
 * @retval #DOWNLOAD_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #DOWNLOAD_ERROR_ID_NOT_FOUND No Download ID
 * @pre The download state must be #DOWNLOAD_STATE_FAILED.
 * @pre The download state must be #DOWNLOAD_STATE_CANCELED.
 * @see #download_set_state_changed_cb()
 * @see #download_unset_state_changed_cb()
 * @see download_start()
 * @see download_error_e
 */
int download_get_error(int download_id, download_error_e *error);


/**
 * @brief Gets the http status code when the download error is happened.
 *
 * @param [in] download The download id
 * @param [out] http_status The http status code which is defined in RFC 2616 
 * @return 0 on success, otherwise a negative error value.
 * @retval #DOWNLOAD_ERROR_NONE Successful
 * @retval #DOWNLOAD_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #DOWNLOAD_ERROR_ID_NOT_FOUND No Download ID
 * @pre The download state must be #DOWNLOAD_STATE_FAILED.
 * @see #download_set_download_status_cb()
 * @see #download_unset_download_status_cb()
 * @see download_start()
 */
int download_get_http_status(int download_id, int *http_status);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __TIZEN_WEB_DOWNLOAD_H__ */
