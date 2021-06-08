#include "gpio.h"


void GPIO_sSPI_init(void){
    // Структура для инициализации портов
      PORT_InitTypeDef gpio_s_spi_port;
    
    
    // Разрешить тактирование требуемых периферийных устройств
      RST_CLK_PCLKcmd (S_SPI_RST_PORT, ENABLE);	
    
    //Выставить настройки структуры в дефолтное положение
      PORT_StructInit (&gpio_s_spi_port);	

      gpio_s_spi_port.PORT_Pin = S_SPI_CKL_PIN;
      gpio_s_spi_port.PORT_MODE  = PORT_MODE_DIGITAL;
      gpio_s_spi_port.PORT_FUNC  = PORT_FUNC_PORT;
      gpio_s_spi_port.PORT_OE    = PORT_OE_IN;
      gpio_s_spi_port.PORT_SPEED = PORT_SPEED_FAST;
      PORT_Init (S_SPI_PORT, &gpio_s_spi_port);
    
    
      gpio_s_spi_port.PORT_Pin = S_SPI_MISO_PIN;
      PORT_Init (S_SPI_PORT, &gpio_s_spi_port);
      
}

void set_SPI_SS(uint8_t state){
    //nop
}

void set_SPI_SCL(uint8_t state){
    if(state){
        set_pins(S_SPI_SS_PIN);
    }
    else{
        reset_pins(S_SPI_SS_PIN);
    }
}

void set_SPI_MOSI(uint8_t state){
    if(state){
        set_pins(S_SPI_SS_PIN);
    }
    else{
        reset_pins(S_SPI_SS_PIN);
    }
}

uint8_t read_SPI_MISO(void){
    uint8_t data = 0;
    
    data = PORT_ReadInputDataBit(S_SPI_PORT, S_SPI_MISO_PIN);
    
    return data;
}


uint8_t read_SPI_SCL(void){
    
    uint8_t data = 0;   
    data = PORT_ReadInputDataBit(S_SPI_PORT, S_SPI_CKL_PIN);

    
   /* 
    PORT_SetBits (S_SPI_PORT, S_SPI_MISO_PIN);
    for(int i = 0; i < 2000; i++){}
    PORT_ResetBits (S_SPI_PORT, S_SPI_MISO_PIN);
    for(int i = 0; i < 2000; i++){}
        
    PORT_SetBits (S_SPI_PORT, S_SPI_CKL_PIN);
    for(int i = 0; i < 2000; i++){}
    PORT_ResetBits (S_SPI_PORT, S_SPI_CKL_PIN);
    for(int i = 0; i < 2000; i++){}    
        */
    return data;
}



void set_pins(uint32_t Pins){
    PORT_ResetBits (S_SPI_PORT, Pins);
}


void reset_pins(uint32_t Pins){
    PORT_SetBits (S_SPI_PORT, Pins);
}


void toggle_pin(uint32_t Pins){
    uint32_t data;
	data	= PORT_ReadInputData (S_SPI_PORT);
	PORT_Write (S_SPI_PORT, data ^= Pins);
}
