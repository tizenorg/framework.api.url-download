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

#include <tet_api.h>
#include <download.h>
#include <glib.h>
#include <glib-object.h>


static void startup(void);
static void cleanup(void);

void (*tet_startup)(void) = startup;
void (*tet_cleanup)(void) = cleanup;

static void utc_download_get_downloaded_file_path_positive1(void);

struct tet_testlist tet_testlist[] = {
	{utc_download_get_downloaded_file_path_positive1, 1},
	{NULL, 0},
};

static GMainLoop* gloop = NULL;
#define TEST_URL "http://static.campaign.naver.com/0/hangeul/2011/img/img_family.gif"

static void state_cb (int download_id, download_state_e state, void *user_data)
{
	const char *TC_NAME = __FUNCTION__;
	int retcode = 0;
	download_error_e err = DOWNLOAD_ERROR_NONE;
	if (state == DOWNLOAD_STATE_COMPLETED)
		g_main_loop_quit(gloop);
	
	retcode = download_get_error(download_id, &err);
	if (retcode != DOWNLOAD_ERROR_NONE) {
		dts_fail(TC_NAME, "Fail to get error");
		g_main_loop_quit(gloop);
		return;
	}
	dts_message(TC_NAME, "err[%d]", err);
	if (err == DOWNLOAD_ERROR_INVALID_URL)
		dts_message(TC_NAME, "invaild url err");
	else
		dts_message(TC_NAME, "another error[%d]", err);
}


static void startup(void)
{
	g_type_init();
	gloop = g_main_loop_new (NULL, 0);
}

static void cleanup(void)
{
	g_main_loop_unref(gloop);
	gloop = NULL;
}


void utc_download_get_downloaded_file_path_positive1(void)
{
	const char *TC_NAME = __FUNCTION__;
	int retcode = 0;
	char *output = NULL;
	int id = 0;

	retcode = download_create(&id);
	if (retcode != DOWNLOAD_ERROR_NONE)	{
		dts_fail(TC_NAME,"Fail to create download handle");
		return;
	}
	retcode = download_set_url(id, TEST_URL);
	if ( retcode != DOWNLOAD_ERROR_NONE ) {
		dts_fail(TC_NAME,"Fail to set url");
		return;
	}
	retcode = download_set_state_changed_cb(id, state_cb, NULL);
	if (retcode != DOWNLOAD_ERROR_NONE)
		dts_fail(TC_NAME, "Fail to set callback");

	retcode = download_start(id);
	if (retcode == DOWNLOAD_ERROR_NONE)
		g_main_loop_run(gloop);

	retcode = download_get_downloaded_file_path(id, &output);
	if ( retcode != DOWNLOAD_ERROR_NONE )
		dts_message(TC_NAME,"Fail to get content name");

	download_unset_state_changed_cb(id);
	download_destroy(id);

	if (retcode == DOWNLOAD_ERROR_NONE)
		dts_pass(TC_NAME, "retcode has no error");
	else
		dts_fail(TC_NAME, "retcode has error");
}

