#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#define HEAT_TIME  20

void printer_init(void);

void print_start(void);
void print_stop(void);

void print_one_line(uint8_t *data, uint8_t len);

#ifdef __cplusplus
}
#endif