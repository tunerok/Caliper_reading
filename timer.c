#include "timer.h"



void ini_timer(void){
    
    TIMER_DeInit(MDR_TIMER1);
    
   TIMER_BRGInit(MDR_TIMER1, TIMER_HCLKdiv64);
    
    TIMER_CntInitTypeDef timer1_ini;
    
    timer1_ini.TIMER_IniCounter = 0x0U;
    timer1_ini.TIMER_Prescaler = 0x257U; // 1999+1//PSG
    timer1_ini.TIMER_Period = 0x14D4U;//92//ARR
    timer1_ini.TIMER_CounterMode = TIMER_CntMode_ClkFixedDir;
    timer1_ini.TIMER_CounterDirection = TIMER_CntDir_Up;
    timer1_ini.TIMER_EventSource = TIMER_EvSrc_TM1;
    timer1_ini.TIMER_FilterSampling = TIMER_FDTS_TIMER_CLK_div_1;
    timer1_ini.TIMER_ARR_UpdateMode = TIMER_ARR_Update_Immediately;
    timer1_ini.TIMER_ETR_FilterConf = TIMER_Filter_1FF_at_TIMER_CLK;
    timer1_ini.TIMER_ETR_Prescaler = TIMER_ETR_Prescaler_None;
    timer1_ini.TIMER_ETR_Polarity = TIMER_ETRPolarity_NonInverted;
    timer1_ini.TIMER_BRK_Polarity = TIMER_BRKPolarity_NonInverted;

    TIMER_CntInit(MDR_TIMER1, &timer1_ini);
    
    TIMER_ITConfig(MDR_TIMER1, TIMER_STATUS_CNT_ARR, ENABLE);
    
    TIMER_Cmd(MDR_TIMER1,ENABLE);
    //MDR_TIMER1->IE 	= TIMER_IE_CNT_ARR_EVENT_IE;
    NVIC_EnableIRQ(Timer1_IRQn);
   
   // MDR_RST_CLK->PER_CLOCK |= 1 << 14;  //разрешение тактирования Таймера 1
    
    //MDR_TIMER1->CNT = 0;
    //MDR_RST_CLK->TIM_CLOCK = (6 /* делитель тактовой частоты Таймера 1 */
     //                       |(1 << 24));  /* разешение тактирования Таймера 1 */
    //
    //MDR_TIMER1->PSG = 0x7CF;
    //MDR_TIMER1->ARR = 0x8;
    //MDR_TIMER1->IE = (1 << 1);//разрешение прерывания по совпадению
    //MDR_TIMER1->CNTRL = TIMER_CNTRL_CNT_EN;//счет вверх по TIM_CLK, таймер вкл.
    
    
}




//Прерывание ( 40 мс )
void TIMER1_IRQHandler ( void  ){
    
    TIMER_ClearFlag(MDR_TIMER1, TIMER_STATUS_CNT_ARR);//clear ARR==CNT FLAG
    TIMER_SetCounter(MDR_TIMER1, 0x0000); //RESET CNT
    recive_timeout = 1;
    TIMER_Cmd(MDR_TIMER1, DISABLE);
    NVIC_ClearPendingIRQ(Timer1_IRQn);  //reset interrupt

}

void start_timing(void){
    TIMER_ClearFlag(MDR_TIMER1, TIMER_STATUS_CNT_ARR);//clear ARR==CNT FLAG
    TIMER_SetCounter(MDR_TIMER1, 0x0000); //RESET CNT
    
    TIMER_Cmd(MDR_TIMER1, ENABLE);
}

void stop_timing(void){
    TIMER_ClearFlag(MDR_TIMER1, TIMER_STATUS_CNT_ARR);//clear ARR==CNT FLAG
    TIMER_SetCounter(MDR_TIMER1, 0x0000); //RESET CNT
    
    TIMER_Cmd(MDR_TIMER1, DISABLE);
    
}

