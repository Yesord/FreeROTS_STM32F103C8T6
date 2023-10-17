/*********************************************************************************************************
* 模块名称：SysTick.c
* 摘    要：SysTick模块，包含SysTick模块初始化以及微秒和毫秒级延时函数
* 当前版本：1.0.0
* 作    者：SZLY(COPYRIGHT 2018 - 2020 SZLY. All rights reserved.)
* 完成日期：2020年01月01日 
* 内    容：
* 注    意：                                                                  
**********************************************************************************************************
* 取代版本：
* 作    者：
* 完成日期：
* 修改内容：           
* 修改文件：
*********************************************************************************************************/

/*********************************************************************************************************
*                                              包含头文件
*********************************************************************************************************/
#include "SysTick.h"
#include "sys.h"

#ifdef USE_FREERTOS

#include "FreeRTOS.h"
#include "task.h"

#endif

/*********************************************************************************************************
*                                              宏定义
*********************************************************************************************************/
#ifdef USE_FREERTOS

extern void xPortSysTickHandler(void);

#endif
/*********************************************************************************************************
*                                              枚举结构体定义
*********************************************************************************************************/

/*********************************************************************************************************
*                                              内部变量
*********************************************************************************************************/
 static uint32_t s_ims = 0;
 
/*********************************************************************************************************
*                                              内部函数声明
*********************************************************************************************************/
#ifndef USE_OS
static void TimDelayDec(void);
#endif
/*********************************************************************************************************
*                                              内部函数实现
*********************************************************************************************************/

#ifndef USE_OS
/*********************************************************************************************************
* 函数名称：TimDelayDec
* 函数功能：
* 输入参数：
* 输出参数：
* 返 回 值：
* 创建日期：2018年01月01日
* 注    意：
*********************************************************************************************************/
static void TimDelayDec(void){
  if(!s_ims){
    s_ims--;
  }
}
#endif
/*********************************************************************************************************
*                                              API函数实现
*********************************************************************************************************/
/*********************************************************************************************************
* 函数名称：InitSysTick
* 函数功能：初始化SysTick模块  
* 输入参数：void  
* 输出参数：void  
* 返 回 值：void
* 创建日期：2018年01月01日
* 注    意：SystemCoreClock / 1000      1ms中断一次（计数1000次为1s，每计一次位1/1000s=1ms）
*           SystemCoreClock / 4000      0.25ms中断一次（计数4000次为1s，每计一次位1/4000s=0.25ms）
*           SystemCoreClock / 100000    10us中断一次（计数100000次为1s，每计一次位1/100000s=10us）
*           SystemCoreClock / 1000000   1us中断一次（计数1000000次为1s，每计一次位1/1000000s=1us）
*********************************************************************************************************/

void SysTick_Init(void){//配置系统滴答定时器1ms中断一次  
  if(SysTick_Config(SystemCoreClock / 1000)){//配置滴答时钟，如果出问题则。。。
    ;
  }
//SystemCoreClock自己设置
//  SysTick->CTRL = 0x00000007; //操作寄存器如左
//  SysTick->LOAD = 72 * 1000;  
  //  SysTick->VAL = 0;//其实可以不开中断的只要计数1us然后重复1000次即可1ms同理1s
}
/*********************************************************************************************************
* 函数名称：DelayNms
* 函数功能：毫秒级延时函数  
* 输入参数：nms
* 输出参数：void
* 返 回 值：void
* 创建日期：2018年01月01日
* 注    意：
*********************************************************************************************************/
void Delay_ms(__IO uint32_t ms){
  s_ims = ms;//将延时计数器s_ims的数值赋为ms
  while(!s_ims){//延时计数器的数值为0时，表示延时了ms，跳出while语句
    ;
  }
}
/*********************************************************************************************************
* 函数名称：DelayNus
* 函数功能：微秒级延时函数  
* 输入参数：nus
* 输出参数：void
* 返 回 值：void
* 创建日期：2018年01月01日
* 注    意：经测试，100us和200us基本准确
*********************************************************************************************************/

void Delay_us(__IO uint32_t us){
  uint32_t s_ius = us;//定义一个变量s_ius作为延时计数器，赋值为us
  uint8_t i;//定义一个变量作为循环计数器
  while(!s_ius){//延时计数器s_ius的值不为0
    for(i = 0; i < 7; i++){//空循环，产生延时功能
      ;
    }
    s_ius--; //成功延时1us，变量s_ius减1
  }
}



#ifdef USE_FREERTOS

void SysTick_Handler(void){
  if(xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED){
    xPortSysTickHandler();
  }
}
#endif

#ifndef USE_OS

void SysTick_Handler(void){
  TimDelayDec();
}

#endif


