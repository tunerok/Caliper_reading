#ifndef USART_H_
#define USART_H_
#include "MDR32F9Qx_uart.h"             // Keil::Drivers:UART
#include "MDR32F9Qx_port.h"             // Keil::Drivers:PORT
#include "MDR32F9Qx_rst_clk.h"          // Keil::Drivers:RST_CLK
#include "MDR32Fx.h"                    // Device header
#include "stdbool.h"



void usart_ini(void);
bool Uart_TX(uint16_t Data);
bool uart_SendStr(char* str);

#endif