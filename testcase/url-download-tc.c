#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>

#include <download.h>
#include <app_control.h>

#define TRACE_DEBUG_MSG(format, ARG...)  \
{ \
printf("[url-download][%s:%d] "format"\n", __FUNCTION__, __LINE__, ##ARG); \
}

#define TRACE_ERROR_MSG(format, ARG...)  \
{ \
printf("[url-download][ERROR][%s:%d] "format"\n", __FUNCTION__, __LINE__, ##ARG); \
}

static char *g_tc_storage = "/opt/usr/media/.url-download-tc";

static char *__print_state(int state)
{
	switch (state) {
	case DOWNLOAD_STATE_READY:
		return "READY";
	case DOWNLOAD_STATE_QUEUED:
		return "QUEUED";
	case DOWNLOAD_STATE_DOWNLOADING:
		return "DOWNLOADING";
	case DOWNLOAD_STATE_PAUSED:
		return "PAUSED";
	case DOWNLOAD_STATE_COMPLETED:
		return "COMPLETED";
	case DOWNLOAD_STATE_FAILED:
		return "FAILED";
	case DOWNLOAD_STATE_CANCELED:
		return "CANCELED";
	default:
		break;
	}
	return "UNKNOWN";
}

static char *__print_errorcode(int errorcode)
{
	switch (errorcode) {
	case DOWNLOAD_ERROR_NONE:
		return "NONE";
	case DOWNLOAD_ERROR_INVALID_PARAMETER:
		return "INVALID_PARAMETER";
	case DOWNLOAD_ERROR_OUT_OF_MEMORY:
		return "OUT_OF_MEMORY";
	case DOWNLOAD_ERROR_IO_ERROR:
		return "IO_ERROR";
	case DOWNLOAD_ERROR_NETWORK_UNREACHABLE:
		return "NETWORK_UNREACHABLE";
	case DOWNLOAD_ERROR_NO_SPACE:
		return "NO_SPACE";
	case DOWNLOAD_ERROR_FIELD_NOT_FOUND:
		return "FIELD_NOT_FOUND";
	case DOWNLOAD_ERROR_INVALID_STATE:
		return "INVALID_STATE";
	case DOWNLOAD_ERROR_CONNECTION_TIMED_OUT:
		return "CONNECTION_TIMED_OUT";
	case DOWNLOAD_ERROR_INVALID_URL:
		return "INVALID_URL";
	case DOWNLOAD_ERROR_INVALID_DESTINATION:
		return "INVALID_DESTINATION";
	case DOWNLOAD_ERROR_PERMISSION_DENIED:
		return "PERMISSION_DENIED";
	case DOWNLOAD_ERROR_QUEUE_FULL:
		return "QUEUE_FULL";
	case DOWNLOAD_ERROR_ALREADY_COMPLETED:
		return "ALREADY_COMPLETED";
	case DOWNLOAD_ERROR_FILE_ALREADY_EXISTS:
		return "FILE_ALREADY_EXISTS";
	case DOWNLOAD_ERROR_TOO_MANY_DOWNLOADS:
		return "TOO_MANY_DOWNLOADS";
	case DOWNLOAD_ERROR_NO_DATA:
		return "NO_DATA";
	case DOWNLOAD_ERROR_UNHANDLED_HTTP_CODE:
		return "UNHANDLED_HTTP_CODE";
	case DOWNLOAD_ERROR_CANNOT_RESUME:
		return "CANNOT_RESUME";
	case DOWNLOAD_ERROR_ID_NOT_FOUND:
		return "ID_NOT_FOUND";
	default:
		break;
	}
	return "UNKOWN";
}

static void __download_get_content_name(int download_id)
{
	char *str = NULL;
	download_error_e errorcode = DOWNLOAD_ERROR_NONE;
	errorcode = download_get_content_name(download_id, &str);
	if (errorcode != DOWNLOAD_ERROR_NONE) {
		TRACE_ERROR_MSG("download:%d content_name error:%s",download_id, __print_errorcode(errorcode));
	} else {
		TRACE_DEBUG_MSG("download:%d content_name (%s)", download_id, str);
	}
	free(str);
}

static void __download_get_mime_type(int download_id)
{
	char *str = NULL;
	download_error_e errorcode = DOWNLOAD_ERROR_NONE;
	errorcode = download_get_mime_type(download_id, &str);
	if (errorcode != DOWNLOAD_ERROR_NONE) {
		TRACE_ERROR_MSG("download:%d mime_type error:%s",download_id, __print_errorcode(errorcode));
	} else {
		TRACE_DEBUG_MSG("download:%d mime_type (%s)", download_id, str);
	}
	free(str);
}

static void __download_get_file_name(int download_id)
{
	char *str = NULL;
	download_error_e errorcode = DOWNLOAD_ERROR_NONE;
	errorcode = download_get_file_name(download_id, &str);
	if (errorcode != DOWNLOAD_ERROR_NONE) {
		TRACE_ERROR_MSG("download:%d file_name error:%s",download_id, __print_errorcode(errorcode));
	} else {
		TRACE_DEBUG_MSG("download:%d file_name (%s)", download_id, str);
	}
	free(str);
}

static void __download_get_temp_path(int download_id)
{
	char *str = NULL;
	download_error_e errorcode = DOWNLOAD_ERROR_NONE;
	errorcode = download_get_temp_path(download_id, &str);
	if (errorcode != DOWNLOAD_ERROR_NONE) {
		download_get_error(download_id, &errorcode);
		TRACE_ERROR_MSG("download:%d temp_path error:%s",download_id, __print_errorcode(errorcode));
	} else {
		TRACE_DEBUG_MSG("download:%d temp_path (%s)", download_id, str);
	}
	free(str);
}

static void __download_get_destination(int download_id)
{
	char *str = NULL;
	download_error_e errorcode = DOWNLOAD_ERROR_NONE;
	errorcode = download_get_destination(download_id, &str);
	if (errorcode != DOWNLOAD_ERROR_NONE) {
		TRACE_ERROR_MSG("download:%d destination error:%s",download_id, __print_errorcode(errorcode));
	} else {
		TRACE_DEBUG_MSG("download:%d destination (%s)", download_id, str);
	}
	free(str);
}

static void __download_get_content_size(int download_id)
{
	unsigned long long content_size = 0;
	download_error_e errorcode = DOWNLOAD_ERROR_NONE;
	errorcode = download_get_content_size(download_id, &content_size);
	if (errorcode != DOWNLOAD_ERROR_NONE) {
		TRACE_ERROR_MSG("download:%d content_size error:%s",download_id, __print_errorcode(errorcode));
	} else {
		TRACE_DEBUG_MSG("download:%d content_size (%lld)", download_id, content_size);
	}
}

static download_state_e __download_get_state(int download_id)
{
	download_state_e state = DOWNLOAD_STATE_NONE;
	download_error_e errorcode = DOWNLOAD_ERROR_NONE;
	errorcode = download_get_state(download_id, &state);
	if (errorcode != DOWNLOAD_ERROR_NONE) {
		TRACE_ERROR_MSG("download:%d state error:%s",download_id, __print_errorcode(errorcode));
	} else {
		TRACE_DEBUG_MSG("download:%d state(%s:%d)", download_id, __print_state(state), state);
	}
	return state;
}

static void __download_manager_progress_cb (int download_id, unsigned long long received, void *user_data)
{
	// ignore log. too many
	//TRACE_DEBUG_MSG("download:%d progress(%lld)", download_id, received);
}

static void __download_manager_state_changed_cb (int download_id, download_state_e state, void *user_data)
{
	TRACE_DEBUG_MSG("download:%d state(%s:%d)", download_id, __print_state(state), state);
	__download_get_state(download_id);
	if (state == DOWNLOAD_STATE_FAILED) {
		download_error_e errorcode = DOWNLOAD_ERROR_NONE;
		download_get_error(download_id, &errorcode);
		TRACE_DEBUG_MSG("download:%d check error:%s", download_id, __print_errorcode(errorcode));
	}
	if (state == DOWNLOAD_STATE_DOWNLOADING) {
		__download_get_content_name(download_id);
		__download_get_mime_type(download_id);
		__download_get_content_size(download_id);
	}
	if (state == DOWNLOAD_STATE_PAUSED) {
	}
	if (state == DOWNLOAD_STATE_COMPLETED) {
		__download_get_content_name(download_id);
		__download_get_mime_type(download_id);
		__download_get_temp_path(download_id);
		__download_get_file_name(download_id);
		__download_get_destination(download_id);
		__download_get_content_size(download_id);
	}
	if (state == DOWNLOAD_STATE_FAILED || state == DOWNLOAD_STATE_COMPLETED || state == DOWNLOAD_STATE_CANCELED)
	{
		download_destroy(download_id);
		TRACE_DEBUG_MSG("download:%d is finished", download_id);
	}
}

static int __download_start(char *url, int force)
{
	int download_id = 0;
	download_error_e errorcode = DOWNLOAD_ERROR_NONE;

	errorcode = download_create(&download_id);
	if (errorcode != DOWNLOAD_ERROR_NONE) {
		TRACE_ERROR_MSG("download:%d create error:%s", download_id, __print_errorcode(errorcode));
	} else {
		errorcode = download_set_state_changed_cb(download_id, __download_manager_state_changed_cb, NULL);
		if (errorcode != DOWNLOAD_ERROR_NONE) {
			TRACE_ERROR_MSG("download:%d set_state_changed_cb error:%s", download_id, __print_errorcode(errorcode));
		}
		errorcode = download_set_progress_cb(download_id, __download_manager_progress_cb, NULL);
		if (errorcode != DOWNLOAD_ERROR_NONE) {
			TRACE_ERROR_MSG("download:%d set_progress_cb error:%s", download_id, __print_errorcode(errorcode));
		}
		errorcode = download_set_destination(download_id, g_tc_storage);
		if (errorcode != DOWNLOAD_ERROR_NONE) {
			TRACE_ERROR_MSG("download:%d set_destination error:%s", download_id, __print_errorcode(errorcode));
		}
		errorcode = download_set_url(download_id, url);
		if (errorcode != DOWNLOAD_ERROR_NONE) {
			TRACE_ERROR_MSG("download:%d set_url error:%s", download_id, __print_errorcode(errorcode));
		}
		if (force > 0) {
			errorcode = download_set_auto_download(download_id, 1);
			if (errorcode != DOWNLOAD_ERROR_NONE) {
				TRACE_ERROR_MSG("download:%d set_auto error:%s", download_id, __print_errorcode(errorcode));
			}
		}
		errorcode = download_set_notification_type(download_id, DOWNLOAD_NOTIFICATION_TYPE_ALL);
		if (errorcode != DOWNLOAD_ERROR_NONE) {
			TRACE_ERROR_MSG("download:%d et_notification error:%s", download_id, __print_errorcode(errorcode));
		}
		errorcode = download_start(download_id);
		if (errorcode != DOWNLOAD_ERROR_NONE) {
			TRACE_ERROR_MSG("download:%d start error:%s", download_id, __print_errorcode(errorcode));
		}
	}
	return download_id;
}


int main(int argc, char** argv)
{
	download_error_e errorcode = DOWNLOAD_ERROR_NONE;
	download_state_e state = DOWNLOAD_STATE_NONE;
	int download_id_state = 0;
	int download_id_api = 0;

	TRACE_DEBUG_MSG("url-download-tc : start");

	// video content, sometimes network error
	__download_start("http://wap2.samsungmobile.com/weblogic/TestContentsDownload/avi__MP4_352x288_30fps_araw_2ch_44khz.avi/video_avi/MP4_352x288_30fps_araw_2ch_44khz.avi", 0);
	// big binary 1.7G from tizen.org
	download_id_api = __download_start("http://download.tizen.org/sdk/sdk-images/2.2/tizen-sdk-image-2.2.0-windows32.zip", 1);
	// big tar file 1.2G from webkit.org
	download_id_state = __download_start("http://nightly.webkit.org/files/WebKit-SVN-source.tar.bz2", 1);

	//stop
	errorcode = download_cancel(download_id_state);
	if (errorcode != DOWNLOAD_ERROR_NONE) {
		TRACE_ERROR_MSG("download:%d stop error:%s", download_id_state, __print_errorcode(errorcode));
	} else {
		// start again
		errorcode = download_start(download_id_state);
		if (errorcode != DOWNLOAD_ERROR_NONE) {
			TRACE_ERROR_MSG("download:%d start error:%s", download_id_state, __print_errorcode(errorcode));
		} else {
			// pause
			errorcode = download_pause(download_id_state);
			if (errorcode != DOWNLOAD_ERROR_NONE) {
				TRACE_ERROR_MSG("download:%d pause error:%s", download_id_state, __print_errorcode(errorcode));
			} else {
				// resume
				errorcode = download_start(download_id_state);
				if (errorcode != DOWNLOAD_ERROR_NONE) {
					TRACE_ERROR_MSG("download:%d resume error:%s", download_id_state, __print_errorcode(errorcode));
				}
			}
		}
	}


	// API test.
	errorcode = download_set_notification_type(download_id_api, DOWNLOAD_NOTIFICATION_TYPE_ALL);
	if (errorcode != DOWNLOAD_ERROR_NONE) {
		TRACE_ERROR_MSG("download:%d stop error:%s", download_id_api, __print_errorcode(errorcode));
	}
	const char *notivalues[3] = {"test1","test2","test3"};
	app_control_h h;
	if (app_control_create(&h) != APP_CONTROL_ERROR_NONE) {
		TRACE_ERROR_MSG("download:%d fail to create app control handle", download_id_api);
	}
	if (app_control_add_extra_data(h, "__APP_SVC_PKG_NAME__", "com.samsung.test-app") < 0) {
		TRACE_ERROR_MSG("download:%d fail to set test pkg name", download_id_api);
	}
	if (app_control_add_extra_data_array(h,(const char *)"test-notification-extra-param", notivalues, 3) < 0) {
		TRACE_ERROR_MSG("download:%d fail to add data to app control handle", download_id_api);
	}
	errorcode = download_set_notification_app_control(download_id_api, DOWNLOAD_NOTIFICATION_APP_CONTROL_TYPE_ONGOING, h);
	errorcode = download_set_notification_app_control(download_id_api, DOWNLOAD_NOTIFICATION_APP_CONTROL_TYPE_FAILED, h);
	if (h != NULL)
		app_control_destroy(h);
	h = NULL;
	if (errorcode != DOWNLOAD_ERROR_NONE) {
		TRACE_ERROR_MSG("download:%d set_notification_app_control error:%s", download_id_api, __print_errorcode(errorcode));
		download_set_notification_title(download_id_api, "test subject");
		download_set_notification_description(download_id_api, "test description");
	} else {
		char **noti_value = NULL;
		int values_count = 0;
		errorcode = download_get_notification_app_control(download_id_api, DOWNLOAD_NOTIFICATION_APP_CONTROL_TYPE_ONGOING, &h);
		if (errorcode != DOWNLOAD_ERROR_NONE) {
			TRACE_ERROR_MSG("download:%d get_notification_app_control error:%s", download_id_api, __print_errorcode(errorcode));
		} else {
			app_control_get_extra_data_array(h, "test-notification-extra-param", &noti_value, &values_count);
			if (!noti_value) {
				TRACE_ERROR_MSG("download:%d fail to get data to app_control", download_id_api);
			} else {
				int i = 0;
				for (; i < values_count; i++) {
					TRACE_DEBUG_MSG("noti_value[%d] : %s", i, noti_value[i]);
					free(noti_value[i]);
				}
			}
		}
		app_control_destroy(h);
		noti_value = NULL;
	}
	state = __download_get_state(download_id_api);
	download_error_e download_errorcode = DOWNLOAD_ERROR_NONE;
	errorcode = download_get_error(download_id_api, &download_errorcode);
	if (errorcode != DOWNLOAD_ERROR_NONE) {
		TRACE_ERROR_MSG("download:%d check error:%s", download_id_api, __print_errorcode(errorcode));
	} else {
		TRACE_DEBUG_MSG("download:%d check error:%s", download_id_api, __print_errorcode(download_errorcode));
	}
	errorcode = download_add_http_header_field(download_id_api, "test-header-field1", "test-header-data1");
	if (errorcode != DOWNLOAD_ERROR_NONE) {
		TRACE_ERROR_MSG("download:%d add_http_header_field error:%s", download_id_api, __print_errorcode(errorcode));
	}
	errorcode = download_add_http_header_field(download_id_api, "test-header-field3", "test-header-data3");
	if (errorcode != DOWNLOAD_ERROR_NONE) {
		TRACE_ERROR_MSG("download:%d add_http_header_field error:%s", download_id_api, __print_errorcode(errorcode));
	}
	errorcode = download_add_http_header_field(download_id_api, "test-header-field4", "test-header-data4");
	if (errorcode != DOWNLOAD_ERROR_NONE) {
		TRACE_ERROR_MSG("download:%d add_http_header_field error:%s", download_id_api, __print_errorcode(errorcode));
	}
	errorcode = download_add_http_header_field(download_id_api, "test-header-field2", "test-header-data2");
	if (errorcode != DOWNLOAD_ERROR_NONE) {
		TRACE_ERROR_MSG("download:%d add_http_header_field error:%s", download_id_api, __print_errorcode(errorcode));
	} else {
		char *header_value = NULL;
		errorcode = download_get_http_header_field(download_id_api, "test-header-field2", &header_value);
		if (errorcode != DOWNLOAD_ERROR_NONE) {
			TRACE_ERROR_MSG("download:%d get_http_header_field error:%s", download_id_api, __print_errorcode(errorcode));
		} else {
			if (header_value == NULL)
				TRACE_ERROR_MSG("download:%d get_http_header_field value null", download_id_api);
			if (header_value != NULL && strncmp(header_value, "test-header-data2", strlen(header_value)) != 0) {
				TRACE_ERROR_MSG("download:%d get_http_header_field return wrong value", download_id_api);
			}
		}
		free(header_value);
		header_value = NULL;
		errorcode = download_remove_http_header_field(download_id_api, "test-header-field2");
		if (errorcode != DOWNLOAD_ERROR_NONE) {
			TRACE_ERROR_MSG("download:%d remove_http_header_field error:%s", download_id_api, __print_errorcode(errorcode));
		} else {
			// after removing , get_http_header_field must be failed. expected errorcode : DOWNLOAD_ERROR_NO_DATA
			errorcode = download_get_http_header_field(download_id_api, "test-header-field2", &header_value);
			if (errorcode != DOWNLOAD_ERROR_NONE) {
				TRACE_DEBUG_MSG("download:%d get_http_header_field error:%s", download_id_api, __print_errorcode(errorcode));
				if (errorcode != DOWNLOAD_ERROR_NO_DATA)
					TRACE_DEBUG_MSG("download:%d get_http_header_field error:%s", download_id_api, __print_errorcode(errorcode));
			} else {
				TRACE_ERROR_MSG("download:%d get_http_header_field after deleting return value:%s", download_id_api, header_value);
			}
		}
	}

	char **fields = NULL;
	int length = 0;
	errorcode = download_get_http_header_field_list(download_id_api, &fields, &length);
	if (errorcode != DOWNLOAD_ERROR_NONE) {
		TRACE_ERROR_MSG("download:%d get_http_header_field_list error:%s", download_id_api, __print_errorcode(errorcode));
	} else {
		if (fields == NULL) {
			TRACE_ERROR_MSG("download:%d get_http_header_field_list array null, length:%d", download_id_api, length);
		} else {
			int i = 0;
			for (; i < length; i++) {
				TRACE_DEBUG_MSG("download:%d get_http_header_field_list %d:%s, length:%d", download_id_api, i, fields[i], length);
				free(fields[i]);
			}
			free(fields);
		}
	}

	state = __download_get_state(download_id_api);
	if (state == DOWNLOAD_STATE_DOWNLOADING) {
		// in downloading, set_url api must be failed. expected errorcode : DOWNLOAD_ERROR_INVALID_STATE
		errorcode = download_set_url(download_id_api, "http://test.com");
		if (errorcode != DOWNLOAD_ERROR_NONE) {
			TRACE_DEBUG_MSG("download:%d set_url error:%s", download_id_api, __print_errorcode(errorcode));
			if (errorcode != DOWNLOAD_ERROR_INVALID_STATE)
				TRACE_ERROR_MSG("download:%d set_url error:%s", download_id_api, __print_errorcode(errorcode));
		} else {
			TRACE_ERROR_MSG("download:%d set_url in doownloading wrong action", download_id_api);
		}
	}

	// 3.8M from tizen.org
	int download_id = __download_start("http://download.tizen.org/sdk/InstallManager/tizen-sdk-2.2/tizen-sdk-ubuntu32-v2.2.32.bin", 1);
	struct timespec ts;
	ts.tv_sec = 0;
	ts.tv_nsec = 100000;
	do {
		nanosleep(&ts, NULL);
		errorcode = download_get_state(download_id, &state);
		if (errorcode != DOWNLOAD_ERROR_NONE) {
			TRACE_ERROR_MSG("download:%d state error:%s",download_id, __print_errorcode(errorcode));
			break;
		}
		if (state == DOWNLOAD_STATE_QUEUED || state == DOWNLOAD_STATE_DOWNLOADING) {
			sleep(1);
		}
	} while (!(state == DOWNLOAD_STATE_FAILED || state == DOWNLOAD_STATE_COMPLETED || state == DOWNLOAD_STATE_CANCELED));

	download_destroy(download_id);
	download_destroy(download_id_api);
	download_destroy(download_id_state);

	TRACE_DEBUG_MSG("url-download-tc : finished");
	exit(EXIT_SUCCESS);
}
