#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "printer_pins.h"

#include "printer_ctrl.h"

#include "printer_heat.h"
#include "printer_moto.h"


void VH_Gpio_Init(void)
{
    //zero-initialize the config structure.
    gpio_config_t io_conf = {};
    //disable interrupt
    io_conf.intr_type = GPIO_INTR_DISABLE;
    //set as output mode
    io_conf.mode = GPIO_MODE_OUTPUT;
    //bit mask of the pins that you want to set,e.g.GPIO18/19
    io_conf.pin_bit_mask = GPIO_VH_PIN_SEL;
    //disable pull-down mode
    io_conf.pull_down_en = 0;
    //disable pull-up mode
    io_conf.pull_up_en = 0;
    //configure GPIO with the given settings
    gpio_config(&io_conf);

    gpio_set_level(GPIO_VH, 0);
}

void VH_Enable(uint8_t level)
{
    gpio_set_level(GPIO_VH, level);
}

void printer_init(void)
{
    Moto_Gpio_Init();
    VH_Gpio_Init();

    Heat_Gpio_Init();
    SPI_Init();
}


void print_start(void)
{
    VH_Enable(1);
    vTaskDelay(100 / portTICK_PERIOD_MS);
    Moto_Enable(1);
}

void print_stop(void)
{
    VH_Enable(0);
    Moto_Enable(0);
}


//heat one stb by one stb
void print_one_line(uint8_t *data, uint8_t len)
{
    Printer_Send_Data(data, len);
    Heat_Enable(GPIO_STB1, 1);
    vTaskDelay(HEAT_TIME / portTICK_PERIOD_MS);
    Heat_Enable(GPIO_STB1, 0);

    // vTaskDelay(HEAT_TIME / portTICK_PERIOD_MS);
    Heat_Enable(GPIO_STB2, 1);
    vTaskDelay(HEAT_TIME / portTICK_PERIOD_MS);
    Heat_Enable(GPIO_STB2, 0);

    Heat_Enable(GPIO_STB3, 1);
    vTaskDelay(HEAT_TIME / portTICK_PERIOD_MS);
    Heat_Enable(GPIO_STB3, 0);

    Heat_Enable(GPIO_STB4, 1);
    vTaskDelay(HEAT_TIME / portTICK_PERIOD_MS);
    Heat_Enable(GPIO_STB4, 0);

    Heat_Enable(GPIO_STB5, 1);
    vTaskDelay(HEAT_TIME / portTICK_PERIOD_MS);
    Heat_Enable(GPIO_STB5, 0);

    Heat_Enable(GPIO_STB6, 1);
    vTaskDelay(HEAT_TIME / portTICK_PERIOD_MS);
    Heat_Enable(GPIO_STB6, 0);
    Motor_Run_Circle(4);
}

// void print_one_line(uint8_t *data, uint8_t len)
// {
//     Printer_Send_Data(data, len);
//     Heat_Enable(GPIO_STB1, 1);
//     Heat_Enable(GPIO_STB3, 1);
//     Heat_Enable(GPIO_STB5, 1);
//     vTaskDelay(HEAT_TIME / portTICK_PERIOD_MS);
//     Heat_Enable(GPIO_STB1, 0);
//     Heat_Enable(GPIO_STB3, 0);
//     Heat_Enable(GPIO_STB5, 0);

//     // vTaskDelay(HEAT_TIME / portTICK_PERIOD_MS);
//     Heat_Enable(GPIO_STB2, 1);
//     Heat_Enable(GPIO_STB4, 1);
//     Heat_Enable(GPIO_STB6, 1);
//     vTaskDelay(HEAT_TIME / portTICK_PERIOD_MS);
//     Heat_Enable(GPIO_STB2, 0);
//     Heat_Enable(GPIO_STB4, 0);
//     Heat_Enable(GPIO_STB6, 0);
//     Motor_Run_Circle(4);
// }