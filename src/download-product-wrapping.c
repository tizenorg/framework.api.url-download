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
#include <download_product.h>
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

int download_set_network_bonding(int download_id, bool enable)
{
	TRACE_INFO("");
	return dp_interface_set_network_bonding(download_id, (int)enable);
}

int download_get_network_bonding(int download_id, bool *enable)
{
	int is_set = 0;
	TRACE_INFO("");
	if (enable == NULL) {
		TRACE_ERROR("Parameter NULL Check");
		return DOWNLOAD_ERROR_INVALID_PARAMETER;
	}
	int ret = dp_interface_get_network_bonding(download_id, &is_set);
	if (ret == DOWNLOAD_ADAPTOR_ERROR_NONE)
		*enable = (bool)is_set;
	return ret;
}
