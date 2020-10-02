#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "esp_wifi.h"
#include "esp_system.h"
#include "esp_event.h"
#include "esp_event.h"
#include "nvs_flash.h"
#include "driver/uart.h"
#include "string.h"
#include "driver/gpio.h"
#include "esp_log.h"

//pin definition for uart_1 and uart_2
#define TXD_PIN_1 (GPIO_NUM_1)
#define RXD_PIN_1 (GPIO_NUM_3)

#define TXD_PIN_2 (GPIO_NUM_17)
#define RXD_PIN_2 (GPIO_NUM_16)

//receiver buffer size definition
static const int RX_BUF_SIZE_1 = 1024;
static const int RX_BUF_SIZE_2 = 1024;

// uart_1 for comm. with GPS/GSM
void uart_1(void)
{
	const uart_config_t uart_config = {
			.baud_rate = 115200,   // set baud rate
			.data_bits = UART_DATA_8_BITS,
			.parity = UART_PARITY_DISABLE,
			.stop_bits = UART_STOP_BITS_1,
			.flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
			.source_clk = UART_SCLK_APB,
	};

	uart_driver_install(UART_NUM_1, RX_BUF_SIZE_1 *2, 0, 0, NULL, 0);
	uart_param_config(UART_NUM_1, &uart_config);
	uart_set_pin(UART_NUM_1, TXD_PIN_1, RXD_PIN_1, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);  //set uart_1 pins

}

// uart_2 comm. for elm327
void uart_2(void)
{
	const uart_config_t uart_config = {
			.baud_rate = 38400,   // set baud rate
			.data_bits = UART_DATA_8_BITS,
			.parity = UART_PARITY_DISABLE,
			.stop_bits = UART_STOP_BITS_1,
			.flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
			.source_clk = UART_SCLK_APB,
	};

	uart_driver_install(UART_NUM_2, RX_BUF_SIZE_2 *2, 0, 0, NULL, 0);
	uart_param_config(UART_NUM_2, &uart_config);
	uart_set_pin(UART_NUM_2, TXD_PIN_2, RXD_PIN_2, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);  // set uart_2 pins

}

//tx to gps/gsm
static void tx_task_1(void *arg)
{
    static const char *TX_TASK_TAG = "TX_TASK_1";
    esp_log_level_set(TX_TASK_TAG, ESP_LOG_INFO);
    while (1)
    {
    	sendData(TX_TASK_TAG, " ");

        vTaskDelay(2000 / portTICK_PERIOD_MS);
    }
}

//rx from gps/gsm
static void rx_task_1(void *arg)
{
	static const char *RX_TASK_TAG = "RX_TASK_1";
	esp_log_level_set(RX_TASK_TAG, ESP_LOG_INFO);
	uint8_t* data = (uint8_t*) malloc(RX_BUF_SIZE_1+1);

	while(1)
	{
		const int rxBytes = uart_read_bytes(UART_NUM_1, data, RX_BUF_SIZE_1, 1000 / portTICK_RATE_MS);
		if(rxBytes > 0)
		{
			data[rxBytes] = 0;
			ESP_LOGI(RX_TASK_TAG, "Read %d bytes: '%s'", rxBytes, data);
			ESP_LOG_BUFFER_HEXDUMP(RX_TASK_TAG, data, rxBytes, ESP_LOG_INFO);

		}
	}

	free(data);

}

// tx to elm327
static void tx_task_2(void *arg)
{
    static const char *TX_TASK_TAG = "TX_TASK_2";
    esp_log_level_set(TX_TASK_TAG, ESP_LOG_INFO);
    while (1)
    {
    	sendData(TX_TASK_TAG, " ");

        vTaskDelay(2000 / portTICK_PERIOD_MS);
    }
}

// rx from elm327
static void rx_task_2(void *arg)
{
	static const char *RX_TASK_TAG = "RX_TASK_2";
	esp_log_level_set(RX_TASK_TAG, ESP_LOG_INFO);
	uint8_t* data = (uint8_t*) malloc(RX_BUF_SIZE_2+1);

	while(1)
	{
		const int rxBytes = uart_read_bytes(UART_NUM_2, data, RX_BUF_SIZE_2, 1000 / portTICK_RATE_MS);
		if(rxBytes > 0)
		{
			data[rxBytes] = 0;
			ESP_LOGI(RX_TASK_TAG, "Read %d bytes: '%s'", rxBytes, data);
			ESP_LOG_BUFFER_HEXDUMP(RX_TASK_TAG, data, rxBytes, ESP_LOG_INFO);

		}
	}

	free(data);

}

// function to send data using uart
int sendData(const char* logName, const char* data)
{
    const int len = strlen(data);
    const int txBytes = uart_write_bytes(UART_NUM_1, data, len);
    ESP_LOGI(logName, "Wrote %d bytes", txBytes);
    return txBytes;
}

void app_main(void)
{
	uart_1();
	uart_2();

	xTaskCreate(tx_task_1, "uart_1_tx_task", 1024*2, NULL, 10, NULL);
    xTaskCreate(rx_task_1, "uart_1_rx_task", 1024*2, NULL, 10, NULL);

    xTaskCreate(tx_task_2, "uart_1_tx_task", 1024*2, NULL, 10, NULL);
    xTaskCreate(rx_task_2, "uart_2_rx_task", 1024*2, NULL, 10, NULL);

}




















