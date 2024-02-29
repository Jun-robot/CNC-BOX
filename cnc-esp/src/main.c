#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
// #include "esp_system.h"
// #include "esp_spi_flash.h"

#include "driver/gpio.h"

void app_main() {
	gpio_set_direction(GPIO_NUM_26, GPIO_MODE_OUTPUT);

	int level = 0;
	while(1){
		gpio_set_level(GPIO_NUM_26, level);
		level = !level;
		vTaskDelay(50/ portTICK_PERIOD_MS);
	}
}