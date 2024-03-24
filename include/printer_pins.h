#pragma once

#define GPIO_VH   18
#define GPIO_VH_PIN_SEL  (1ULL<<GPIO_VH)

#define GPIO_AP    7
#define GPIO_AM    2
#define GPIO_BP    39
#define GPIO_BM    38
#define GPIO_MOTO_ENABLE    17
#define GPIO_MOTO_PIN_SEL  ((1ULL<<GPIO_AP) | (1ULL<<GPIO_AM) | (1ULL<<GPIO_BP) | (1ULL<<GPIO_BM) | (1ULL<<GPIO_MOTO_ENABLE))

#define GPIO_STB1    6
#define GPIO_STB2    10
#define GPIO_STB3    5
#define GPIO_STB4    14
#define GPIO_STB5    13
#define GPIO_STB6    3
#define GPIO_STB_PIN_SEL  ((1ULL<<GPIO_STB1) | (1ULL<<GPIO_STB2) | (1ULL<<GPIO_STB3) | (1ULL<<GPIO_STB4) | (1ULL<<GPIO_STB5) | (1ULL<<GPIO_STB6))

#define PIN_NUM_SCLK 4
#define PIN_NUM_DO 11
#define PIN_NUM_LAT 12

// #define GPIO_DATA_PIN_SEL  ((1ULL<<PIN_NUM_LAT) | (1ULL<<PIN_NUM_DO) | (1ULL<<PIN_NUM_SCLK))
#define GPIO_DATA_PIN_SEL  (1ULL<<PIN_NUM_LAT)