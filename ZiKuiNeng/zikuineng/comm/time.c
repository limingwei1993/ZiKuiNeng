/*
 * time.c
 *
 *  Created on: 2021年4月21日
 *      Author: Lee
 */
#include "include.h"
uint8_t Collection_ADC=0; /*Collection ADC glag ;1--start collection*/
/**
  * @function Time0_Int
  * @brief    Configure the time0
  * @param    Freq:  The "Freq" is entered as "MHz"   Freq=150(150MHZ)
  *           Period: the period in "uSeconds"     Period=1000(1MS)...1000000(1S)
  * @retval   None
  */
void Time0_Int(float Freq, float Period)
{
    uint32_t temp=0;
    CpuTimer0.CPUFreqInMHz = Freq;
    CpuTimer0.PeriodInUSec = Period;
    temp = (long) (Freq * Period);
    CpuTimer0Regs.PRD.all = temp-1;

     // Set pre-scale counter to divide by 1 (SYSCLKOUT):
     CpuTimer0Regs.TPR.all  = 0;
     CpuTimer0Regs.TPRH.all  = 0;
    // 确保定时器0停止:
    CpuTimer0Regs.TCR.bit.TSS = 1;
   // 重加载计数器周期值:
    CpuTimer0Regs.TCR.bit.TRB = 1;
    //
    CpuTimer0Regs.TCR.bit.SOFT=1;
    CpuTimer0Regs.TCR.bit.FREE=1;
    //enable interrupt
    CpuTimer0Regs.TCR.bit.TIE=1;

    // 复位中断计时器:
    CpuTimer0.InterruptCount = 0;


}
/**
  * @function Time0_Interrupt_Handler
  * @brief    This function handles timeo Handler.
  * @param    none
  * @retval   none
  */
uint32_t ADS_count=0; /*test code*/
__interrupt void Time0_Interrupt_Handler(void)
{
    static uint32_t time_count=0;
    time_count++;
    ADS_count++;
    if(time_count%5==0)
    {
        Collection_ADC=1;
    }
    if(time_count==1000*10)
        time_count=0;
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}
/**
  * @function task_run
  * @brief    Timing task processing.
  * @param    none
  * @retval   none
  */
void task_run(void)
{
    if(Collection_ADC==1)
    {
        ADC_Read();
        Collection_ADC=0;
    }
}
