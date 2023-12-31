#include "timer3.h"
#include "counter.h"
uint32_t cnt=0;
uint32_t frequent=0;
uint8_t TIM3_COUNT_DONE=0;
uint16_t TIM3_COUNT_CYCLES=0;
//////////////////////////////////////////////////////////////////////////////////
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK战舰STM32开发板
//定时器 驱动代码
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/3
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved
//////////////////////////////////////////////////////////////////////////////////

//通用定时器3中断初始化
//这里时钟选择为APB1的2倍，而APB1为36M
//arr：自动重装值。
//psc：时钟预分频数
//这里使用的是定时器3!
//TIM3_Init(499,359);//72MHz/(500*360)=400Hz
void TIM3_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef TIM3_TimeBaseInitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
    TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
    TIM3_TimeBaseInitStructure.TIM_Period = arr;
    TIM3_TimeBaseInitStructure.TIM_Prescaler = psc;
    TIM3_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM3_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM3,&TIM3_TimeBaseInitStructure);

    TIM_Cmd(TIM3,ENABLE);
    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE );


    NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

}


void TIM3_IRQHandler()
{
    TIM_ClearITPendingBit(TIM3,TIM_IT_Update);   //???
    if(TIM3_COUNT_DONE==0)
    {
        if(TIM3_COUNT_CYCLES<399)
        {
            cnt += TIM1->CNT;  //统计计数器1的计数值
            TIM1->CNT=0;    //计数器1清零
            TIM3_COUNT_CYCLES++;
        }
        else
        {
            cnt += TIM1->CNT;
            TIM1->CNT=0;
            cnt += cnt*0.0003;	//校准
            frequent = cnt;
            TIM3_COUNT_DONE=1;
            TIM3_COUNT_CYCLES = 0;
            cnt = 0;
        }
    }
}









