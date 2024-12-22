/*
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

#include <app_version.h>

LOG_MODULE_REGISTER(main, CONFIG_APP_LOG_LEVEL);

int main(void)
{
	LOG_INF("Starting app: version ");

	while (1) {
		LOG_INF("blink");
		k_sleep(K_MSEC(1000));
	}

	return 0;
}
