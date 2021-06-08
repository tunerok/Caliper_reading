#ifndef GPIO_H
#define GPIO_H

#include "MDR32F9Qx_port.h"             // Keil::Drivers:PORT
#include "MDR32F9Qx_rst_clk.h"          // Keil::Drivers:RST_CLK
#include <stdlib.h>

#define S_SPI_PORT MDR_PORTF
#define S_SPI_RST_PORT RST_CLK_PCLK_PORTF

#define S_SPI_SS_PIN PORT_Pin_0
#define S_SPI_CKL_PIN PORT_Pin_5

#define S_SPI_MISO_PIN PORT_Pin_6
#define S_SPI_MOSI_PIN PORT_Pin_3

void GPIO_sSPI_init(void);

void set_SPI_SS(uint8_t state);
void set_SPI_SCL(uint8_t state);
void set_SPI_MOSI(uint8_t state);
uint8_t read_SPI_MISO(void);
uint8_t read_SPI_SCL(void);



void set_pins(uint32_t Pins);
void reset_pins(uint32_t Pins);
void toggle_pin(uint32_t Pins);

#endif
