/*********************************************************************************************************
* 模块名称: Main.c
* 摘 	  要: 主函数
* 当前版本: 1.0.0
* 作 	  者: xrl
* 完成日期: 2023 年 08 月 01 日
* 内	  容: ADC单通道实验
* 注 	  意: none
**********************************************************************************************************
* 取代版本:
* 作 	  者:
* 完成日期:
* 修改内容:
* 修改文件:
*********************************************************************************************************/
 
 
/*********************************************************************************************************
* 包含头文件
*********************************************************************************************************/
#include "Config.h"

/*********************************************************************************************************
* 宏定义
*********************************************************************************************************/


/*********************************************************************************************************
* 枚举结构体定义
*********************************************************************************************************/

/*********************************************************************************************************
* 内部变量
*********************************************************************************************************/

/*********************************************************************************************************
* 内部函数声明
*********************************************************************************************************/
static void Hardware_Init(void);
static void Software_Init(void);
static void Proc2msTask(void);
static void Proc2msTask(void);

/*********************************************************************************************************
* 内部函数实现
*********************************************************************************************************/

/*********************************************************************************************************
* 函数名称: Hardware_Init
* 函数功能: 硬件初始化
* 输入参数: void
* 输出参数: void
* 返 回 值: void
* 创建日期: 2023 年 08 月 01 日
* 注		意: none
*********************************************************************************************************/

static void Hardware_Init(void){
  OLED_Init();
  Timer_Init();
  LED_Init();
}

/*********************************************************************************************************
* 函数名称: Software_Init
* 函数功能: 软件初始化
* 输入参数: void
* 输出参数: void
* 返 回 值: void
* 创建日期: 2023 年 08 月 01 日
* 注		意: none
*********************************************************************************************************/

static void Software_Init(void){
  ;
}

/*********************************************************************************************************
* 函数名称: Proc2msTask
* 函数功能: 2ms任务处理
* 输入参数: void
* 输出参数: void
* 返 回 值: void
* 创建日期: 2023 年 08 月 01 日
* 注		意: none
*********************************************************************************************************/

static void Proc2msTask(void){
  if(Timer_Get2msFlag()){
    static uint16_t s_icnt;
    if(s_icnt >= 100){
      LED_Flicker();
      s_icnt = 0;
    }
    s_icnt++;
    Timer_Clr2msFlag();
  }
}

/*********************************************************************************************************
* 函数名称: Proc1secTask
* 函数功能: 1s任务处理
* 输入参数: void
* 输出参数: void
* 返 回 值: void
* 创建日期: 2023 年 08 月 01 日
* 注		意: none
*********************************************************************************************************/

static void Proc1secTask(void){
  if(Timer_Get1secFlag()){
    LED_Flicker();        //LED闪烁
    Timer_Clr1secFlag();
  }
}

/*********************************************************************************************************
* API 函数实现
*********************************************************************************************************/



int main(void){
  Hardware_Init();
  Software_Init();
  OLED_ShowString(1, 1, "Program is OK!");
  while(1){
    Proc2msTask();
  }
}

