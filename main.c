#include "main.h"

volatile uint8_t recive_timeout;

int main(void){
    clk_init();
    ini_timer();
    GPIO_sSPI_init();
    usart_ini();
    _spi_init();
    
    uint32_t caliper_data = 0;
    uint8_t caliper_data_mm[3];
    uint32_t out_data = 0;
    uint8_t sign_data = 0;
    while(1)
    {
        caliper_data = 0;
        out_data = 0;
        sign_data = 0;
        
        _caliper_read_data(&caliper_data);
        caliper_data = ~caliper_data;
        
        
        sign_data |= (uint8_t)((caliper_data & 0x00F00000u) >> 20);
        out_data = (uint32_t)(caliper_data & 0x000FFFFFu );
        
        //if (sign_data){
         //   out_data *= -1;
       // }
        
        uart_SendU32(out_data);
        
        //caliper_data_mm[0] = (uint8_t)caliper_data & 0xFFu;
        //caliper_data_mm[1] = (uint8_t)((caliper_data >> 8) & 0xFFu);
        //caliper_data_mm[2] = (uint8_t)((caliper_data >> 16) & 0xFFu);
        
			}
        
        
        
    return 0;
}


