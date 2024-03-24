#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#define MOTO_TIME  10

void Moto_Gpio_Init(void);
void Moto_Enable(uint8_t enable);
void Motor_Run(uint8_t motor);
void Motor_Stop(void);
void Motor_Run_Circle(uint8_t times);

#ifdef __cplusplus
}
#endif