#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "printer_moto.h"

const uint8_t motorTable[][4] =
{
    {1, 0, 0, 0},
    {1, 0, 0, 1},
    {0, 0, 0, 1},
    {0, 0, 1, 1},
    {0, 0, 1, 0},
    {0, 1, 1, 0},
    {0, 1, 0, 0},
    {1, 1, 0, 0}
};

void Moto_Gpio_Init(void)
{
    //zero-initialize the config structure.
    gpio_config_t io_conf = {};
    //disable interrupt
    io_conf.intr_type = GPIO_INTR_DISABLE;
    //set as output mode
    io_conf.mode = GPIO_MODE_OUTPUT;
    //bit mask of the pins that you want to set,e.g.GPIO18/19
    io_conf.pin_bit_mask = GPIO_MOTO_PIN_SEL;
    //disable pull-down mode
    io_conf.pull_down_en = 0;
    //disable pull-up mode
    io_conf.pull_up_en = 0;
    //configure GPIO with the given settings
    gpio_config(&io_conf);

    gpio_set_level(GPIO_AP, 0);
    gpio_set_level(GPIO_BP, 0);
    gpio_set_level(GPIO_AM, 0);
    gpio_set_level(GPIO_BM, 0);
    gpio_set_level(GPIO_MOTO_ENABLE, 0);
}

void Moto_Enable(uint8_t enable)
{
    gpio_set_level(GPIO_MOTO_ENABLE, enable);
}

void Motor_Run(uint8_t motor)
{
    gpio_set_level(GPIO_AP, motorTable[motor][0]);
    gpio_set_level(GPIO_BP, motorTable[motor][1]);
    gpio_set_level(GPIO_AM, motorTable[motor][2]);
    gpio_set_level(GPIO_BM, motorTable[motor][3]);
}

void Motor_Stop(void)
{
    gpio_set_level(GPIO_AP, 0);
    gpio_set_level(GPIO_AM, 0);
    gpio_set_level(GPIO_BP, 0);
    gpio_set_level(GPIO_BM, 0);
}

// void Motor_Run_Circle(uint8_t times)
// {
//     for(int i = 0; i < times; i++)
//     {
//         for(int j = 0; j <8; j++)
//         {
//             Motor_Run(j);
//             vTaskDelay(10 / portTICK_PERIOD_MS);
//         }
//     }
//     Motor_Stop();
// }

void Motor_Run_Circle(uint8_t times)
{
    static uint8_t current_Motor = 0;
    for(int i = 0; i < times; i++)
    {
        Motor_Run(current_Motor);
        vTaskDelay(20 / portTICK_PERIOD_MS);
        current_Motor++;
        if(current_Motor == 8)
        {
            current_Motor = 0;
        }
    }
    Motor_Stop();
}