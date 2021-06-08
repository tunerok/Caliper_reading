#ifndef SOFT_SPI_H
#define SOFT_SPI_H

#include "MDR32F9Qx_wwdg.h"             // Keil::Drivers:WWDG
#include "MDR32F9Qx_port.h"             // Keil::Drivers:PORT
#include "gpio.h"
#include "timer.h"

//#define CLRWDT() WWDG_ClearFlag() 
#define my_NOP for(int i = 0; i<10;i++){} 
    
void _spi_init(void);
void _spi_start(void);
void _spi_stop(void);
void _spi_sendbyte(uint8_t d);
uint8_t _spi_readbyte(void);
void _caliper_read_data(uint32_t* data);
    
void swap_word_bits(uint32_t *input_data);
uint8_t swap_bits(uint8_t x);

#endif
