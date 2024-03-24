#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#define PRINTER_HOST  SPI2_HOST
#define PRINTER_DATA_LEN 48

void Heat_Gpio_Init(void);
void Heat_Enable(uint8_t stb_num, uint16_t heat_time);
void SPI_Init(void);
void Printer_Send_Data(uint8_t *data, uint8_t len);


#ifdef __cplusplus
}
#endif