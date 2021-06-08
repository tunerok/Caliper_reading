#include "soft_spi.h"


void _spi_init(void)
{
    
   // первоначаотное положение линий SPI
   set_SPI_SS(1);
   set_SPI_SCL(0);
   set_SPI_MOSI(0);
   

}


void _spi_start(void)
{
   set_SPI_SCL(0);
   set_SPI_SS(0);

}

void _spi_stop(void)
{
   set_SPI_SCL(1);
   set_SPI_SS(0);
}

void _spi_sendbyte(uint8_t d)
{
   uint8_t i;
 
   // отправить 1 байт
   for(i=0; i<8; i++)
   {
     // CLRWDT();
 
      // проверить старш бит = 1
      if (d & 0x80)
      {
         set_SPI_MOSI(1); // передать 1
      }
      else
      {
         set_SPI_MOSI(0); // передать 0
      }
 
      set_SPI_SCL(1); // синхроимпульс
      d <<= 1;     // сдвиг для передачи след бита
      my_NOP
      
      set_SPI_SCL(0); // синхроимпульс
   }
}

uint8_t _spi_readbyte(void)
{
   uint8_t i, spiReadData=0;
 
   for(i=0; i<8; i++)
   {
      //CLRWDT();
 
      spiReadData <<= 1; // сдвиг для передачи след бита
 
      set_SPI_SCL(1); // синхроимпульс
      my_NOP
      if (read_SPI_MISO() == 1) { spiReadData |= 0x01; } // читаем бит
      my_NOP;
      set_SPI_SCL(0); // синхроимпульс
   }
 
   return spiReadData;
}



void _caliper_read_data(uint32_t* in_data){
    recive_timeout = 0;
    uint8_t state = 0;
    uint32_t data = 0;
    
    uint8_t data_counter = 0;
    uint8_t SCK_readed = 0; 

    //check if we at gigh state
    while(!read_SPI_SCL()){}
    	start_timing();
	    {
	        while (!recive_timeout && data_counter < 24)
	            switch (state)
	            {
	                case 0:
	                    //NOP && reading scl
	                    my_NOP;
	                    SCK_readed = read_SPI_SCL();
	                    //if it's high then goto next state
	                    if (SCK_readed)
	                    {
	                        state = 1;
	                    }
	                    //else NOP
	                    break;
	                case 1:
	                    //NOP && reading scl
	                    my_NOP;
	                    SCK_readed = read_SPI_SCL();
	                    if (!SCK_readed)
	                    {
	                        state = 2;
	                    }
	                    break;
	                    
	                case 2:
	                    //reading MISO
	                    data = data << 1;
	                    if (read_SPI_MISO() == 1) { 
	                        data |= 0x01; 
	                    }
	                    data_counter++;
	                    state = 0;
	                    break;
	            }
	            //end of data reading
	        }
	            //if(recive_timeout){
	            //    my_NOP;
	            //}



        stop_timing();
        swap_word_bits(&data);
        *in_data = data;
}

void swap_word_bits(uint32_t* input_data){
    uint32_t tmp = *input_data;
    uint32_t data = 0;
    data |= (uint32_t)(swap_bits((uint8_t)tmp & 0xFFu))<< 16;
    data |= (uint32_t)(swap_bits((uint8_t)((tmp >> 8) & 0xFFu))) << 8;
    data |= (uint32_t)(swap_bits((uint8_t)((tmp >> 16) & 0xFFu))) ;
    *input_data = data;
}


uint8_t swap_bits(uint8_t x)
{
  x = ((x & 0x55) << 1) | ((x & 0xAA) >> 1);
  x = ((x & 0xCC) >> 2) | ((x & 0x33) << 2);
  x = (x >> 4) | (x << 4);
  return x;
}


