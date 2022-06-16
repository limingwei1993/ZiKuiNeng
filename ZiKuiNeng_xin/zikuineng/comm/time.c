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
    static uint32_t motor_time_count=0;
    static uint8_t Motor1_speed=0;
    static uint8_t Motor2_speed=0;
    static uint8_t Motor_start_end_count=0;
    time_count++;
    ADS_count++;
    if(power_on==1)  /*电机的软起动*/
    {
        motor_time_count++;
        if(motor_time_count>=5)
        {
            if(Motor1_speed<=Motor1_Start_speed)
            {
                set_motor1_status(Motor1_speed);
                Motor1_speed++;
            }
            else
            {
                Motor_start_end_count++;
            }
            if(Motor2_speed<=Motor2_Start_speed)
            {
                set_motor2_status(Motor2_speed);
                Motor2_speed++;
             }
            else
            {
                Motor_start_end_count++;
            }
            if(Motor_start_end_count>=2)
            {
                power_on=0;
            }
            motor_time_count=0;
        }
    }

    if(time_count%5==0)/*ADC采集周期控制*/
    {
        Collection_ADC=1;

    }
    if(time_count%5000==0)/*测试使用，测试EEPROM、SD卡、ADC采集数据发送*/
    {
        test_eeprom_read=1;
        test_eeprom_write=1;
        test_sd_write=1;
        test_sd_read=1;
        send_ADC_value=1;
    }
    if(time_count%1000==0)/*测试使用，测试开关阀和电机10秒打开*/
    {
     if(switch1_on_off>0)/*测试使用，测试开关阀1打开*/
     {
         switch1_on_off--;
         if(switch1_on_off==5)
         {
             set_switch1_status(30);
         }
         else if(switch1_on_off==0)
         {
           set_switch1_status(0);
         }
     }
     if(switch2_on_off>0)/*测试使用，测试开关阀2打开10秒*/
      {
         switch2_on_off--;
         if(switch2_on_off==5)
         {
              set_switch2_status(30);
         }
         else if(switch2_on_off==0)
          {
            set_switch2_status(0);
          }
      }
     if(switch3_on_off>0)/*测试使用，测试开关阀3打开10秒*/
      {
         switch3_on_off--;
         if(switch3_on_off==119)
          {
              set_switch3_status(30);
          }
         else if(switch3_on_off==0)
          {
            set_switch3_status(0);
          }
      }
     if(switch4_on_off>0)/*测试使用，测试开关阀4打开10秒*/
      {
         switch4_on_off--;
         if(switch4_on_off==119)
          {
              set_switch4_status(30);
          }
          if(switch4_on_off==0)
          {
            set_switch4_status(0);
          }
      }
     if(motor1_on_off>0)/*测试使用，测试电机1打开10秒*/
      {
         motor1_on_off--;
          if(motor1_on_off==0)
          {
            set_motor1_status(0);
          }
      }
     if(motor2_on_off>0) /*测试使用，测试电机2打开10秒*/
     {
         motor2_on_off--;
       if(motor2_on_off==0)
       {
          set_motor2_status(0);
       }
     }

    }
    if(time_count==1000*10)
    {
        time_count=0;
    }
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
