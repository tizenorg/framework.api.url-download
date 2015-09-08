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

static void utc_download_get_http_header_field_list_negative1(void);
static void utc_download_get_http_header_field_list_negative2(void);
static void utc_download_get_http_header_field_list_negative3(void);

struct tet_testlist tet_testlist[] = {
	{utc_download_get_http_header_field_list_negative1, 1},
	{utc_download_get_http_header_field_list_negative2, 2},
	{utc_download_get_http_header_field_list_negative3, 3},
	{NULL, 0},
};

static void startup(void)
{

}

static void cleanup(void)
{
	/* end of TC */
}

void utc_download_get_http_header_field_list_negative1(void)
{
	const char *TC_NAME = __FUNCTION__;
	int retcode = 0;
	int id = 0;
	int length=0;
	
	download_create(&id);
	download_add_http_header_field(id, "field1","value1");
	retcode = download_get_http_header_field_list(id, NULL, &length);
	download_destroy(id);

	if (retcode == DOWNLOAD_ERROR_INVALID_PARAMETER)
		dts_pass(TC_NAME, "retcode has invalid parameter");
	else
		dts_fail(TC_NAME, "retcode does not have invalid parameter");
}

void utc_download_get_http_header_field_list_negative2(void)
{
	const char *TC_NAME = __FUNCTION__;
	int retcode = 0;
	int id = 0;
	char **fields = NULL;
	
	download_create(&id);
	download_add_http_header_field(id, "field1","value1");
	retcode = download_get_http_header_field_list(id, &fields, NULL);
	download_destroy(id);

	if (retcode == DOWNLOAD_ERROR_INVALID_PARAMETER)
		dts_pass(TC_NAME, "retcode has invalid parameter");
	else
		dts_fail(TC_NAME, "retcode does not have invalid parameter");
}

void utc_download_get_http_header_field_list_negative3(void)
{
	const char *TC_NAME = __FUNCTION__;
	int retcode = 0;
	char **fields = NULL;
	int length = 0;
	int id = 0;

	download_create(&id);
	download_add_http_header_field(id, "field1","value1");
	retcode = download_get_http_header_field_list(-1, &fields, &length);
	download_destroy(id);

	if (retcode == DOWNLOAD_ERROR_INVALID_PARAMETER)
		dts_pass(TC_NAME, "retcode has invalid parameter");
	else
		dts_fail(TC_NAME, "retcode does not have invalid parameter");
}

