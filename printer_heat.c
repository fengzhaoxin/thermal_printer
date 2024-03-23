#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/spi_master.h"
#include "driver/spi_common.h"
#include "printer_heat.h"

spi_device_handle_t spi2_handle;
spi_transaction_t transaction_config; //定义数据结构体
uint8_t temp_tx[48]={0};
uint8_t temp_rx[48]={0};

void Heat_Gpio_Init(void)
{
    //zero-initialize the config structure.
    gpio_config_t io_conf = {};
    //disable interrupt
    io_conf.intr_type = GPIO_INTR_DISABLE;
    //set as output mode
    io_conf.mode = GPIO_MODE_OUTPUT;
    //bit mask of the pins that you want to set,e.g.GPIO18/19
    io_conf.pin_bit_mask = GPIO_STB_PIN_SEL;
    //disable pull-down mode
    io_conf.pull_down_en = 0;
    //disable pull-up mode
    io_conf.pull_up_en = 0;
    //configure GPIO with the given settings
    gpio_config(&io_conf);

    io_conf.pin_bit_mask = GPIO_DATA_PIN_SEL;
    gpio_config(&io_conf);

    gpio_set_level(GPIO_STB1, 0);
    gpio_set_level(GPIO_STB2, 0);
    gpio_set_level(GPIO_STB3, 0);
    gpio_set_level(GPIO_STB4, 0);
    gpio_set_level(GPIO_STB5, 0);
    gpio_set_level(GPIO_STB6, 0);
    gpio_set_level(PIN_NUM_LAT, 1);
    // gpio_set_level(PIN_NUM_SCLK, 0);
    // gpio_set_level(PIN_NUM_DO, 0);
}

void Heat_Enable(uint8_t stb_num, uint16_t heat_time)
{
    gpio_set_level(stb_num, 1);
    vTaskDelay(heat_time / portTICK_PERIOD_MS);
    gpio_set_level(stb_num, 0);
}

void SPI_Init(void)
{
    spi_bus_config_t buscfg={    //总线配置结构体
		// .miso_io_num = -1,    //gpio12->miso
		.mosi_io_num = PIN_NUM_DO,    //gpio13->mosi
		.sclk_io_num = PIN_NUM_SCLK,    //gpio14-> sclk
        .flags = SPICOMMON_BUSFLAG_MASTER
	};
    spi_device_interface_config_t interface_config={ //设备配置结构体
	    .address_bits = 0,
	    .command_bits = 0,
	    .clock_speed_hz = 3 *1000 * 1000,
	    .mode = 0, //设置SPI通讯的相位特性和采样边沿。包括了mode0-3四种。要看从设备能够使用哪种模式
	    // interface_config.spics_io_num = 25; //配置片选线
        .duty_cycle_pos = 0,
	    .queue_size = 6 //传输队列的长度，表示可以在通讯的时候挂起多少个spi通讯。在中断通讯模式的时候会把当前spi通讯进程挂起到队列中
    };

	ESP_ERROR_CHECK(spi_bus_initialize(PRINTER_HOST, &buscfg, SPI_DMA_CH_AUTO));
    
    memset(&spi2_handle, 0, sizeof(spi2_handle));  //为数据结构体分配内存
    ESP_ERROR_CHECK(spi_bus_add_device(PRINTER_HOST, &interface_config, &spi2_handle));


    memset(&transaction_config, 0, sizeof(transaction_config));  //为数据结构体分配内存
	transaction_config.length = 48 * 8;  //要发送或者接收的数据的长度，不算前面的cmd/address/dummy的长度
	transaction_config.tx_buffer =temp_tx;  //发送没有指定内部空间，使用的是外部区域，因此要自己指定
	transaction_config.rx_buffer = temp_rx; //接收定义了SPI_TRANS_USE_RXDATA，使用的是内部空间。
	// transaction_config.flags = SPI_TRANS_USE_RXDATA;
}

void Printer_Send_Data(uint8_t *data, uint8_t len)
{   
    memcpy(temp_tx,data,len);

    spi_device_acquire_bus(spi2_handle, portMAX_DELAY);
    spi_device_polling_transmit(spi2_handle, &transaction_config);
    spi_device_polling_start(spi2_handle, &transaction_config, portMAX_DELAY);
    spi_device_polling_end(spi2_handle, portMAX_DELAY);
    spi_device_release_bus(spi2_handle);

    vTaskDelay(5 / portTICK_PERIOD_MS);
    gpio_set_level(PIN_NUM_LAT, 0);
    vTaskDelay(1 / portTICK_PERIOD_MS);
    gpio_set_level(PIN_NUM_LAT, 1);
    memset(temp_tx, 0, sizeof(temp_tx));
}