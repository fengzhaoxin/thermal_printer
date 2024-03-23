#pragma once

#ifdef __cplusplus
extern "C" {
#endif

// define STB GPIO pin number
#define GPIO_STB1    5
#define GPIO_STB2    6
#define GPIO_STB3    7
#define GPIO_STB4    12
#define GPIO_STB5    13
#define GPIO_STB6    3
#define GPIO_STB_PIN_SEL  ((1ULL<<GPIO_STB1) | (1ULL<<GPIO_STB2) | (1ULL<<GPIO_STB3) | (1ULL<<GPIO_STB4) | (1ULL<<GPIO_STB5) | (1ULL<<GPIO_STB6))


#define PRINTER_HOST  SPI2_HOST
#define PRINTER_DATA_LEN 48

#define PIN_NUM_SCLK 9
#define PIN_NUM_DO 10
#define PIN_NUM_LAT 11

#define GPIO_DATA_PIN_SEL  (1ULL<<PIN_NUM_LAT)

// Initialize GPIO for STB and LAT
void Heat_Gpio_Init(void);
// Enable heat for a specific STB and a specific time
void Heat_Enable(uint8_t stb_num, uint16_t heat_time);
// Initialize SPI for printer
void SPI_Init(void);
// Send data to printer
void Printer_Send_Data(uint8_t *data, uint8_t len);


#ifdef __cplusplus
}
#endif