#include "usart.h"

void usart_ini(void){
    UART_DeInit(MDR_UART1);
    
    
    RST_CLK_PCLKcmd (RST_CLK_PCLK_PORTB, ENABLE);	
    PORT_InitTypeDef PortInit;
    
    //Выставить настройки структуры в дефолтное положение
      PORT_StructInit (&PortInit);
    
    PortInit.PORT_PULL_UP = PORT_PULL_UP_OFF;
	PortInit.PORT_PULL_DOWN = PORT_PULL_DOWN_OFF;
	PortInit.PORT_PD_SHM = PORT_PD_SHM_OFF;
	PortInit.PORT_PD = PORT_PD_DRIVER;
	PortInit.PORT_GFEN = PORT_GFEN_OFF;
	PortInit.PORT_FUNC = PORT_FUNC_ALTER;
	PortInit.PORT_SPEED = PORT_SPEED_FAST;
	PortInit.PORT_MODE = PORT_MODE_DIGITAL;
    
    PortInit.PORT_OE = PORT_OE_OUT;
	PortInit.PORT_Pin = PORT_Pin_5;
    PORT_Init(MDR_PORTB, &PortInit);
    
    PortInit.PORT_OE = PORT_OE_IN;
	PortInit.PORT_Pin = PORT_Pin_6;
    PORT_Init(MDR_PORTB, &PortInit);
    RST_CLK_PCLKcmd(RST_CLK_PCLK_UART1, ENABLE);
    
    UART_BRGInit(MDR_UART1, UART_HCLKdiv2);
        
    UART_InitTypeDef UART_InitStructure;
    UART_InitStructure.UART_BaudRate = 9600;
    UART_InitStructure.UART_WordLength = UART_WordLength8b;
	UART_InitStructure.UART_StopBits = UART_StopBits1;
	UART_InitStructure.UART_Parity = UART_Parity_No;
	UART_InitStructure.UART_FIFOMode = UART_FIFO_OFF;
	UART_InitStructure.UART_HardwareFlowControl = UART_HardwareFlowControl_RXE
												| UART_HardwareFlowControl_TXE;
    
    
    
    UART_Init(MDR_UART1, &UART_InitStructure);
    
    UART_Cmd(MDR_UART1, ENABLE);
    
}



bool Uart_TX(uint16_t Data){

    UART_SendData(MDR_UART1, Data);
    while(UART_GetFlagStatus(MDR_UART1, UART_FLAG_BUSY) == SET){};

    return true;
}

bool uart_SendStr(char* str)
{
	bool res = false;
	while(*str != 0)
		if((res = Uart_TX(*str++)) == false) break;		
	return res;
}

bool uart_SendU32(uint32_t worded){
    
    char srting[4] = {0,0,0,0};
    
    srting[0] = (uint8_t)(worded & 0xFFu);
    srting[1] = (uint8_t)(worded >> 8 & 0xFFu);
    srting[2] = (uint8_t)(worded >> 16 & 0xFFu);
    srting[3] = (uint8_t)(worded >> 24 & 0xFFu);
    
    uart_SendStr(srting);
    
}