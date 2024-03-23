#pragma once

#ifdef __cplusplus
extern "C" {
#endif

// GPIO define
#define GPIO_AP    15
#define GPIO_AM    16
#define GPIO_BP    18
#define GPIO_BM    17
#define GPIO_MOTO_ENABLE    4
#define GPIO_MOTO_PIN_SEL  ((1ULL<<GPIO_AP) | (1ULL<<GPIO_AM) | (1ULL<<GPIO_BP) | (1ULL<<GPIO_BM) | (1ULL<<GPIO_MOTO_ENABLE))

// Init Moto GPIO
void Moto_Gpio_Init(void);
// Enable Moto
void Moto_Enable(uint8_t enable);
// Run Moto with direction
void Motor_Run(uint8_t motor);
// Stop Moto
void Motor_Stop(void);
// Run Moto with specific steps
void Motor_Run_Circle(uint8_t times);

#ifdef __cplusplus
}
#endif