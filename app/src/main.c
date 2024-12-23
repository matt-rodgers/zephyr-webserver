/*
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/net/http/server.h>
#include <zephyr/net/http/service.h>

#include <app_version.h>

LOG_MODULE_REGISTER(main, CONFIG_APP_LOG_LEVEL);

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
