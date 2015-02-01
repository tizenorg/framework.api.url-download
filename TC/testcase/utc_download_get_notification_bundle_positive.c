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

static void startup(void);
static void cleanup(void);

void (*tet_startup)(void) = startup;
void (*tet_cleanup)(void) = cleanup;

static void utc_download_get_notification_bundle_positive1(void);

struct tet_testlist tet_testlist[] = {
	{utc_download_get_notification_bundle_positive1, 1},
	{NULL, 0},
};

static void startup(void)
{

}

static void cleanup(void)
{
	/* end of TC */
}

void utc_download_get_notification_bundle_positive1(void)
{
	const char *TC_NAME = __FUNCTION__;
	int retcode = 0;
	char *input = "ongoing";
	char *output = NULL;
	int id = 0;
	bundle *b = bundle_create();
	bundle *b_db = NULL;
	bundle_add(b, "key", input);

	download_create(&id);
	download_set_notification_bundle(id, DOWNLOAD_NOTIFICATION_BUNDLE_TYPE_ONGOING, b);
	retcode = download_get_notification_bundle(id, DOWNLOAD_NOTIFICATION_BUNDLE_TYPE_ONGOING, &b_db);
	output = bundle_get_val(b_db, "key");
	download_destroy(id);
	if (retcode == DOWNLOAD_ERROR_NONE && !strcmp(input, output))
		dts_pass(TC_NAME, "retcode has no error and the bundle of set API is same to bundle of get API ");
	else
		dts_fail(TC_NAME, "retcode has error or the bundle of set API is not same to bundle of get API");
	bundle_free(b);
	bundle_free(b_db);
}

