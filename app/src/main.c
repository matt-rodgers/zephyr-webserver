/*
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/net/http/server.h>
#include <zephyr/net/http/service.h>

#include <app_version.h>

LOG_MODULE_REGISTER(main, CONFIG_APP_LOG_LEVEL);

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

static uint16_t http_port = 80;
HTTP_SERVICE_DEFINE(http_service, NULL, &http_port, CONFIG_HTTP_SERVER_MAX_CLIENTS, 10, NULL);

int main(void)
{
    LOG_INF("Starting app: version " APP_VERSION_EXTENDED_STRING
            ", build version " STRINGIFY(APP_BUILD_VERSION));

    if (0 != http_server_start()) {
        LOG_ERR("Failed to start HTTP server");
        return -EINVAL;
    }

    return 0;
}
