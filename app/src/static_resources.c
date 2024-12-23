/*
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/net/http/server.h>
#include <zephyr/net/http/service.h>

/*
 * index.html
 */
static uint8_t index_html_gz[] = {
#include "index.html.gz.inc"
};

static struct http_resource_detail_static index_html_res_detail = {
    .common =
        {
            .type = HTTP_RESOURCE_TYPE_STATIC,
            .bitmask_of_supported_http_methods = BIT(HTTP_GET),
            .content_encoding = "gzip",
            .content_type = "text/html",
        },
    .static_data = index_html_gz,
    .static_data_len = sizeof(index_html_gz),
};

HTTP_RESOURCE_DEFINE(index_html_res, http_service, "/", &index_html_res_detail);

/*
 * index.js
 */
static uint8_t index_js_gz[] = {
#include "assets/index.js.gz.inc"
};

static struct http_resource_detail_static index_js_res_detail = {
    .common =
        {
            .type = HTTP_RESOURCE_TYPE_STATIC,
            .bitmask_of_supported_http_methods = BIT(HTTP_GET),
            .content_encoding = "gzip",
            .content_type = "text/javascript",
        },
    .static_data = index_js_gz,
    .static_data_len = sizeof(index_js_gz),
};

HTTP_RESOURCE_DEFINE(index_js_res, http_service, "/assets/index.js", &index_js_res_detail);

/*
 * index.css
 */
static uint8_t index_css_gz[] = {
#include "assets/index.css.gz.inc"
};

static struct http_resource_detail_static index_css_res_detail = {
    .common =
        {
            .type = HTTP_RESOURCE_TYPE_STATIC,
            .bitmask_of_supported_http_methods = BIT(HTTP_GET),
            .content_encoding = "gzip",
            .content_type = "text/css",
        },
    .static_data = index_css_gz,
    .static_data_len = sizeof(index_css_gz),
};

HTTP_RESOURCE_DEFINE(index_css_res, http_service, "/assets/index.css", &index_css_res_detail);
