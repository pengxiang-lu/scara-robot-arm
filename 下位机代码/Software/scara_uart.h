#ifndef __SCARA_UART_H_
#define __SCARA_UART_H_
#include <stdint.h>

void scara_driver_control_callback(uint8_t receive_data);
void scara_uart_loop(void);
#endif

