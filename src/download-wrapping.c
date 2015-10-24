#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

#include <dlog.h>
#include <download.h>
#include <download-provider-interface.h>

#define DEBUG_MSG
#ifdef DEBUG_MSG
#include <dlog.h>
#ifdef LOG_TAG
#undef LOG_TAG
#endif
#define LOG_TAG "TIZEN_N_URL_DOWNLOAD"
#define TRACE_ERROR(format, ARG...)  \
{ \
LOGE(format, ##ARG); \
}
#define TRACE_STRERROR(format, ARG...)  \
{ \
LOGE(format" [%s]", ##ARG, strerror(errno)); \
}
#define TRACE_INFO(format, ARG...)  \
{ \
LOGI(format, ##ARG); \
}
#else
#define TRACE_DEBUG_MSG(format, ARG...) ;
#endif

/////////////////////// APIs /////////////////////////////////

int download_create(int *download_id)
{
	TRACE_INFO("");
	if (download_id == NULL)
		return DOWNLOAD_ERROR_INVALID_PARAMETER;
	return dp_interface_create(download_id);
}

int download_destroy(int download_id)
{
	TRACE_INFO("");
	return dp_interface_destroy(download_id);
}

int download_start(int download_id)
{
	TRACE_INFO("");
	return dp_interface_start(download_id);
}

int download_pause(int download_id)
{
	TRACE_INFO("");
	return dp_interface_pause(download_id);
}

int download_cancel(int download_id)
{
	TRACE_INFO("");
	return dp_interface_cancel(download_id);
}


int download_set_url(int download_id, const char *url)
{
	TRACE_INFO("");
	if (url == NULL)
		return DOWNLOAD_ERROR_INVALID_PARAMETER;
	return dp_interface_set_url(download_id, url);
}


int download_get_url(int download_id, char **url)
{
	TRACE_INFO("");
	if (url == NULL)
		return DOWNLOAD_ERROR_INVALID_PARAMETER;
	return dp_interface_get_url(download_id, url);
}

int download_set_network_type(int download_id,
						download_network_type_e net_type)
{
	TRACE_INFO("");
	return dp_interface_set_network_type(download_id, (int)net_type);
}

int download_get_network_type(int download_id,
							download_network_type_e *net_type)
{
	TRACE_INFO("");

	if (net_type == NULL) {
		TRACE_ERROR("Parameter NULL Check");
		return DOWNLOAD_ERROR_INVALID_PARAMETER;
	}
	int network_type = DOWNLOAD_ADAPTOR_NETWORK_ALL;
	int ret = dp_interface_get_network_type(download_id, &network_type);
	if (ret == DOWNLOAD_ADAPTOR_ERROR_NONE)
		*net_type = network_type;
	return ret;
}

int download_set_destination(int download_id, const char *path)
{
	TRACE_INFO("");
	if (path == NULL)
		return DOWNLOAD_ERROR_INVALID_PARAMETER;
	return dp_interface_set_destination(download_id, path);
}


int download_get_destination(int download_id, char **path)
{
	TRACE_INFO("");
	if (path == NULL)
		return DOWNLOAD_ERROR_INVALID_PARAMETER;
	return dp_interface_get_destination(download_id, path);
}

int download_set_file_name(int download_id, const char *file_name)
{
	TRACE_INFO("");
	if (file_name == NULL)
		return DOWNLOAD_ERROR_INVALID_PARAMETER;
	return dp_interface_set_file_name(download_id, file_name);
}

int download_get_file_name(int download_id, char **file_name)
{
	TRACE_INFO("");
	if (file_name == NULL)
		return DOWNLOAD_ERROR_INVALID_PARAMETER;
	return dp_interface_get_file_name(download_id, file_name);
}

int download_get_downloaded_file_path(int download_id, char **path)
{
	TRACE_INFO("");
	if (path == NULL)
		return DOWNLOAD_ERROR_INVALID_PARAMETER;
	return dp_interface_get_downloaded_file_path(download_id, path);
}

int download_add_http_header_field(int download_id, const char *field,
	const char *value)
{
	TRACE_INFO("");
	if (field == NULL || value == NULL)
		return DOWNLOAD_ERROR_INVALID_PARAMETER;
	return
		dp_interface_add_http_header_field(download_id, field, value);
}

int download_get_http_header_field(int download_id,
	const char *field, char **value)
{
	TRACE_INFO("");
	if (field == NULL || value == NULL)
		return DOWNLOAD_ERROR_INVALID_PARAMETER;
	return
		dp_interface_get_http_header_field(download_id, field, value);
}

int download_get_http_header_field_list(int download_id, char ***fields,
	int *length)
{
	TRACE_INFO("");
	if (fields == NULL || length == NULL)
		return DOWNLOAD_ERROR_INVALID_PARAMETER;
	return dp_interface_get_http_header_field_list(download_id, fields,
		length);
}

int download_remove_http_header_field(int download_id,
	const char *field)
{
	TRACE_INFO("");
	if (field == NULL)
		return DOWNLOAD_ERROR_INVALID_PARAMETER;
	return dp_interface_remove_http_header_field(download_id, field);
}

// download_state_changed_cb is different with dp_interface_state_changed_cb.
int download_set_state_changed_cb(int download_id,
	download_state_changed_cb callback, void* user_data)
{
	TRACE_INFO("");
	return dp_interface_set_state_changed_cb(download_id,
		(dp_interface_state_changed_cb)callback, user_data);
}

int download_unset_state_changed_cb(int download_id)
{
	TRACE_INFO("");
	return dp_interface_unset_state_changed_cb(download_id);
}

// download_progress_cb is same with dp_interface_progress_cb.
int download_set_progress_cb(int download_id,
	download_progress_cb callback, void *user_data)
{
	TRACE_INFO("");
	return dp_interface_set_progress_cb(download_id,
			(dp_interface_progress_cb)callback, user_data);
}

int download_unset_progress_cb(int download_id)
{
	TRACE_INFO("");
	return dp_interface_unset_progress_cb(download_id);
}

int download_get_state(int download_id, download_state_e *state)
{
	int statecode = 0;
	TRACE_INFO("");
	if (state == NULL) {
		TRACE_ERROR("Parameter NULL Check");
		return DOWNLOAD_ERROR_INVALID_PARAMETER;
	}
	int ret = dp_interface_get_state(download_id, &statecode);
	if (ret == DOWNLOAD_ADAPTOR_ERROR_NONE)
		*state = statecode;
	return ret;
}

int download_get_temp_path(int download_id, char **temp_path)
{
	TRACE_INFO("");
	if (temp_path == NULL)
		return DOWNLOAD_ERROR_INVALID_PARAMETER;
	return dp_interface_get_temp_path(download_id, temp_path);
}

int download_get_content_name(int download_id, char **content_name)
{
	TRACE_INFO("");
	if (content_name == NULL)
		return DOWNLOAD_ERROR_INVALID_PARAMETER;
	return dp_interface_get_content_name(download_id, content_name);
}

int download_get_content_size(int download_id,
	unsigned long long *content_size)
{
	TRACE_INFO("");
	if (content_size == NULL)
		return DOWNLOAD_ERROR_INVALID_PARAMETER;
	return dp_interface_get_content_size(download_id, content_size);
}

int download_get_mime_type(int download_id, char **mime_type)
{
	TRACE_INFO("");
	if (mime_type == NULL)
		return DOWNLOAD_ERROR_INVALID_PARAMETER;
	return dp_interface_get_mime_type(download_id, mime_type);
}

int download_set_auto_download(int download_id, bool enable)
{
	TRACE_INFO("");
	return dp_interface_set_auto_download(download_id, (int)enable);
}

int download_get_auto_download(int download_id, bool *enable)
{
	int is_set = 0;
	TRACE_INFO("");
	if (enable == NULL) {
		TRACE_ERROR("Parameter NULL Check");
		return DOWNLOAD_ERROR_INVALID_PARAMETER;
	}
	int ret = dp_interface_get_auto_download(download_id, &is_set);
	if (ret == DOWNLOAD_ADAPTOR_ERROR_NONE)
		*enable = (bool)is_set;
	return ret;
}

int download_get_error(int download_id, download_error_e *error)
{
	int errorcode = 0;
	TRACE_INFO("");
	if (error == NULL) {
		TRACE_ERROR("Parameter NULL Check");
		return DOWNLOAD_ERROR_INVALID_PARAMETER;
	}
	int ret = dp_interface_get_error(download_id, &errorcode);
	if (ret == DOWNLOAD_ADAPTOR_ERROR_NONE)
		*error = errorcode;
	return ret;
}

int download_get_http_status(int download_id, int *http_status)
{
	TRACE_INFO("");
	if (http_status == NULL)
		return DOWNLOAD_ERROR_INVALID_PARAMETER;
	return dp_interface_get_http_status(download_id, http_status);
}

int download_set_notification_app_control(int download_id, download_notification_app_control_type_e type, app_control_h handle)
{
	TRACE_INFO("");
	if (handle == NULL)
		return DOWNLOAD_ERROR_INVALID_PARAMETER;
	return dp_interface_set_notification_service_handle(download_id, (int)type, handle);
}

int download_get_notification_app_control(int download_id, download_notification_app_control_type_e type, app_control_h *handle)
{
	TRACE_INFO("");
	if (handle == NULL)
		return DOWNLOAD_ERROR_INVALID_PARAMETER;
	return dp_interface_get_notification_service_handle(download_id, (int)type, handle);
}

int download_set_notification_title(int download_id, const char *title)
{
	TRACE_INFO("");
	if (title == NULL)
		return DOWNLOAD_ERROR_INVALID_PARAMETER;
	return dp_interface_set_notification_title(download_id, title);
}

int download_get_notification_title(int download_id, char **title)
{
	TRACE_INFO("");
	if (title == NULL)
		return DOWNLOAD_ERROR_INVALID_PARAMETER;
	return dp_interface_get_notification_title(download_id, title);
}

int download_set_notification_description(int download_id, const char *description)
{
	TRACE_INFO("");
	if (description == NULL)
		return DOWNLOAD_ERROR_INVALID_PARAMETER;
	return dp_interface_set_notification_description(download_id, description);
}

int download_get_notification_description(int download_id, char **description)
{
	TRACE_INFO("");
	if (description == NULL)
		return DOWNLOAD_ERROR_INVALID_PARAMETER;
	return dp_interface_get_notification_description(download_id, description);
}

int download_set_notification_type(int download_id, download_notification_type_e type)
{
	TRACE_INFO("");
	return dp_interface_set_notification_type(download_id, (int)type);
}

int download_get_notification_type(int download_id, download_notification_type_e *type)
{
	int noti_type = 0;
	TRACE_INFO("");
	if (type == NULL) {
		TRACE_ERROR("Parameter NULL Check");
		return DOWNLOAD_ERROR_INVALID_PARAMETER;
	}
	int ret = dp_interface_get_notification_type(download_id, &noti_type);
	if (ret == DOWNLOAD_ADAPTOR_ERROR_NONE)
		*type = (download_notification_type_e)noti_type;
	return ret;
}

int download_get_etag(int download_id, char **etag)
{
	TRACE_INFO("");
	if (etag == NULL)
		return DOWNLOAD_ERROR_INVALID_PARAMETER;
	return dp_interface_get_etag(download_id, etag);
}

int download_set_temp_file_path(int download_id, char *path)
{
	TRACE_INFO("");
	if (path == NULL)
		return DOWNLOAD_ERROR_INVALID_PARAMETER;
	return dp_interface_set_temp_file_path(download_id, path);
}
