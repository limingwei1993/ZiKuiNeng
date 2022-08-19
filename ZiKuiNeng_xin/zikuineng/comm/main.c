/*
 * main.c
 *
 *  Created on: 2021骞�4鏈�20鏃�
 *      Author: Lee
 */

/*
 * V 0.0.1
 * 修改：
 * 一、关于外部晶振30MHZ修改：
 *      1、RS422波特率参数
 *      2、PWM波特率参数
 *      3、ADS1258 延时参数
 *      4、SD卡延时参数
 * 二、PWM占空比与高低电平关联。
 * 三、修改RS422接收发送的个数。
 *
 *V 0.0.2
 *修改：
 *一、增加拨码开关
 *二、修改串口协议
 *
 *V 0.0.3 /2021-8-31
 *一、修改PWM配置，6个PWM配置结构统一。
 *二、修改串口，修改串口协议与串口参数。
 * */
#include "include.h"
uint8_t test_Switch1=0;/*测试使用，测试开关阀1*/
uint8_t test_Switch1_duty=0;/*测试使用，开关阀1目前占空比*/
uint8_t test_Switch2=0;/*测试使用，测试开关阀2*/
uint8_t test_Switch2_duty=0;/*测试使用，开关阀2目前占空比*/
uint8_t test_Switch3=0;/*测试使用，测试开关阀3*/
uint8_t test_Switch3_duty=0;/*测试使用，开关阀3目前占空比*/
uint8_t test_Switch4=0;/*测试使用，测试开关阀4*/
uint8_t test_Switch4_duty=0;/*测试使用，开关阀4目前占空比*/
uint8_t test_motor1=0;/*测试使用，测试电机1*/
uint8_t test_motor1_duty=0;/*测试使用，电机1目前占空比*/
uint8_t test_motor2=0;/*测试使用，测试电机1*/
uint8_t test_motor2_duty=0;/*测试使用，电机2目前占空比*/
uint8_t test_rs422=200;/*测试使用，测试rs422*/
uint32_t test_Dial=0;/*测试使用，获取拨码开关值*/
uint8_t dial_value=0;/*测试使用，拨o码开关值*/
//uint8_t =0;/*测试使用，测试拨码开关*/
uint8_t sd_write_buff[120]={0};/*测试使用，测试SD卡*/
uint8_t sd_read_buff[120]={0};/*测试使用，测试SD卡*/
uint8_t readlen=0;/*测试使用，测试SD卡*/
uint8_t test_sd_read=0;/*测试使用，测试SD卡*/
uint8_t test_sd_write=0;/*测试使用，测试SD卡*/
FATFS   fs;         /*测试使用，测试SD卡*/
FIL     file;       /*测试使用，测试SD卡*/
uint8_t power_on=0; /*电机软起动标志，当该变量为1时，会进行软起动，1秒内电机由最慢变为最快*/
uint8_t eeprom_write_buff[120]={0};/*测试使用，测试EEPROM*/
uint8_t eeprom_read_buff[120]={0};/*测试使用，测试EEPROM*/
uint8_t test_eeprom_read=0;/*测试使用，测试EEPROM*/
uint8_t test_eeprom_write=0;/*测试使用，测试EEPROM*/
uint8_t i=0;/*测试使用*/
uint8_t send_RS232_value=0;/*测试使用，测试ADC采样*/
uint8_t adc_buff[100]={0};/*测试使用，测试ADC采样*/
uint8_t framelen=0;/*测试使用，测试ADC采样*/
uint8_t Rs422_revice=0;/*测试使用，测试串口*/
uint8_t Rs422_revice_type=0;/*测试使用，测试串口*/
uint8_t Rs422_revice_data=0;/*测试使用，测试串口*/
uint8_t eeprom_send_buff[120]={0};/*测试使用*/
uint8_t test_motor_out=0;/*测试使用，置1改变电机BRK或DIR的状态*/
uint8_t test_motor_pinx=0;/*测试使用，选择电机BRK或DIR*/
uint8_t test_motor_status=0;/*测试使用，电机BRK或DIR的状态*/
uint8_t nFUT_motor1_status=0; /*nFUT_Motor1的状态*/
uint8_t nFUT_motor2_status=0; /*nFUT_Motor2的状态*/
uint8_t test_EEPROM_status=1; /*测试使用，EEPROM的状态*/
uint8_t test_SD_status=6; /*测试使用，SD卡的状态*/
unsigned int EQEP1_COUNT=0;/*FGOUT_MOTOR1 频率。1s计数*/
unsigned int EQEP2_COUNT=0;/*FGOUT_MOTOR2 频率。1s计数*/
#define BUFF_SIZE   6
float SampleTable[BUFF_SIZE];
void main(void)
{
   /*Run from flash*/
   MemCopy(&RamfuncsLoadStart, &RamfuncsLoadEnd, &RamfuncsRunStart);
   InitFlash();
   InitSysCtrl(); /*system initialization*/
   DINT;   /*Disenable interrupt*/
   InitPieCtrl(); /*initializes the PIE*/
   IER = 0x0000; /*Interrupt enable register*/
   IFR = 0x0000; /*Interrupt flag register*/
   InitPieVectTable(); /*initializes the PIE vector table*/
    Time0_Int(150, 1000); /*1ms*/
#if (SPI_MODE == HARDWARE_SPI)
    ADS1258_SPI_Int();
#endif
    Configuration_Interrupt();  /*Configure interrupt*/
    GIOP_Int();
    Pwm1_Switch1_Int();
    Pwm2_Switch2_Int();
    Pwm3_Switch3_Int();
    Pwm4_Switch4_Int();
    Pwm5_Motor1_Int();
    Pwm6_Motor2_Int();
    RS422_Int(115200);
    ADC_Init();
    EINT; /*Enable interrupt*/
    ERTM; /*Enable debug event*/
    ADS1258_Int();
    Eqep_Init();
    power_on=0;  /*出于测试目的，将电机的软启动关闭了*/
    if(f_mount(&fs,"0:",1) != FR_OK)/*用于测试SD卡，挂在文件系统*/
   {
        test_SD_status=0;
   }
    for(i=0;i<100;i++)/*测试使用，写数据到EEPROM*/
    {
      eeprom_write_buff[i]= 0;
      sd_write_buff[i]=0;
    }
    AT24C512_WriteString(100,eeprom_write_buff,100);
    for(i = 0; i < BUFF_SIZE; i++)
   {
       SampleTable[i] = 0;
   }
    while(1)
    {
        if(AdcRegs.ADCST.bit.INT_SEQ1 == 1)
        {
            AdcRegs.ADCST.bit.INT_SEQ1_CLR = 1;         //清除中断标识
            SampleTable[0] = (float)(AdcRegs.ADCRESULT0>>4)*3.3/4096;
            SampleTable[1] = (float)(AdcRegs.ADCRESULT1>>4)*3.3/4096;
            SampleTable[2] = (float)(AdcRegs.ADCRESULT2>>4)*3.3/4096;
            SampleTable[3] = (float)(AdcRegs.ADCRESULT3>>4)*3.3/4096;
            SampleTable[4] = (float)(AdcRegs.ADCRESULT4>>4)*3.3/4096;
            SampleTable[5] = (float)(AdcRegs.ADCRESULT5>>4)*3.3/4096;
        }
        if(test_Switch1!=test_Switch1_duty)/*测试使用，测试开关阀1*/
        {
            test_Switch1_duty=test_Switch1;
            set_switch1_status(test_Switch1_duty);
        }
        if(test_Switch2!=test_Switch2_duty)/*测试使用，测试开关阀2*/
        {
            test_Switch2_duty=test_Switch2;
            set_switch2_status(test_Switch2_duty);
        }
        if(test_Switch3!=test_Switch3_duty)/*测试使用，测试开关阀3*/
        {
            test_Switch3_duty=test_Switch3;
            set_switch3_status(test_Switch3_duty);
        }
        if(test_Switch4!=test_Switch4_duty)/*测试使用，测试开关阀4*/
        {
            test_Switch4_duty=test_Switch4;
            set_switch4_status(test_Switch4_duty);
        }
        if(test_motor1!=test_motor1_duty)/*测试使用，测试电机1*/
        {
            test_motor1_duty=test_motor1;
            set_motor1_status(test_motor1_duty);
        }
        if(test_motor2!=test_motor2_duty)/*测试使用，测试电机2*/
        {
            test_motor2_duty=test_motor2;
            set_motor2_status(test_motor2_duty);
        }
        if(test_rs422!=0)/*测试使用，测试rs422发送*/
        {
            RS422_Send_Data();
            test_rs422=0;
        }
        dial_value=Get_Dial_Code();
        if(test_motor_out==1)/*测试使用，控制电机引脚输出状态*/
        {
            test_motor_out=0;
           Set_Motor_pin((motor_pinx)test_motor_pinx,test_motor_status);
        }
        nFUT_motor1_status=Get_nFUT_Status(MOTOR1_nFUT);
        nFUT_motor2_status=Get_nFUT_Status(MOTOR2_nFUT);
        if(test_eeprom_read==1)/*测试使用，测试EEPROM*/
        {
            /*读取EEPROM数据*/
            test_eeprom_read=0;
            AT24C512_ReadString(100,eeprom_read_buff,100);
            for(i=0;i<100;i++)
            {
                if(eeprom_read_buff[i]!=eeprom_write_buff[i])
                {
                    test_EEPROM_status=0;
                    break;
                }
            }
            if(i==100)
            {
                test_EEPROM_status=1;
            }
        }
        if(test_eeprom_write==1)/*测试使用，测试EEPROM*/
        {
            /*写数据到EEPROM*/
            test_eeprom_write=0;
            for(i=0;i<100;i++)
            {
                if(eeprom_write_buff[i]<0xff)
                  eeprom_write_buff[i]= eeprom_write_buff[i]+1;
                else
                    eeprom_write_buff[i]=0;
                AT24C512_WritelenByte(i*100,&eeprom_write_buff[i],1);
            }
            AT24C512_WriteString(100,eeprom_write_buff,100);
        }
        if(test_sd_write==1 && test_SD_status!=0)/*测试使用，写数据到SD卡*/
       {
          f_open (&file,  (const TCHAR *)"0:30.txt",  FA_OPEN_ALWAYS | FA_WRITE);
          for(i=0;i<100;i++)
          {
              if(sd_write_buff[i]<0xff)
               sd_write_buff[i]=sd_write_buff[i]+1;
              else
                  sd_write_buff[i]=0;
          }
          f_puts(sd_write_buff, &file);
          f_sync(&file);
          f_close (&file);
          test_sd_write=0;
       }
        if(test_sd_read==1 && test_SD_status!=0)/*测试使用，从SD卡读取数据*/
        {
            f_open (&file,  (const TCHAR *)"0:30.txt",FA_READ);
            f_read (&file, sd_read_buff, 100, &readlen);
            f_close (&file);
            test_sd_read=0;
            for(i=0;i<100;i++)
            {
                 if(sd_read_buff[i]!=sd_write_buff[i])
                 {
                     test_SD_status=1;
                     break;
                 }
            }
            if(i==100)
            {
                test_SD_status=6;
            }
        }
        task_run();/*用于ADC采集*/
        if(send_RS232_value==1)/*测试使用，发送ADC采样的数据*/
        {
            send_RS232_value=0;
            framelen=0;
            adc_buff[framelen++]=0xAA;
            adc_buff[framelen++]=0x55;
            adc_buff[framelen++]=0x00;
            adc_buff[framelen++]=test_EEPROM_status;
            adc_buff[framelen++]=test_SD_status;
            adc_buff[framelen++]=dial_value;
            adc_buff[framelen++]=((uint8_t)(SampleTable[3]*100)/100);
            adc_buff[framelen++]=((uint8_t)(SampleTable[3]*100)%100);
            adc_buff[framelen++]=((uint8_t)(SampleTable[2]*100)/100);
            adc_buff[framelen++]=((uint8_t)(SampleTable[2]*100)%100);
            adc_buff[framelen++]=((uint8_t)(SampleTable[1]*100)/100);
            adc_buff[framelen++]=((uint8_t)(SampleTable[1]*100)%100);
            adc_buff[framelen++]=((uint8_t)(SampleTable[0]*100)/100);
            adc_buff[framelen++]=((uint8_t)(SampleTable[0]*100)%100);
            adc_buff[framelen++]=((uint8_t)(SampleTable[5]*100)/100);
            adc_buff[framelen++]=((uint8_t)(SampleTable[5]*100)%100);
            adc_buff[framelen++]=((uint8_t)(SampleTable[4]*100)/100);
            adc_buff[framelen++]=((uint8_t)(SampleTable[4]*100)%100);
            adc_buff[framelen++]=nFUT_motor1_status;
            adc_buff[framelen++]=nFUT_motor2_status;
            adc_buff[framelen++]=(EQEP1_COUNT>>8)&0xff;
            adc_buff[framelen++]=(EQEP1_COUNT>>0)&0xff;
            adc_buff[framelen++]=(EQEP2_COUNT>>8)&0xff;
            adc_buff[framelen++]=(EQEP2_COUNT>>0)&0xff;
            adc_buff[framelen++]=((uint8_t)(ADC_CURRENT_mA.signal_1_temperature*100)/100);
            adc_buff[framelen++]=((uint8_t)(ADC_CURRENT_mA.signal_1_temperature*100)%100);
            adc_buff[framelen++]=((uint8_t)(ADC_CURRENT_mA.signal_1_pressure*100)/100);
            adc_buff[framelen++]=((uint8_t)(ADC_CURRENT_mA.signal_1_pressure*100)%100);
            adc_buff[framelen++]=((uint8_t)(ADC_CURRENT_mA.signal_2_temperature*100)/100);
            adc_buff[framelen++]=((uint8_t)(ADC_CURRENT_mA.signal_2_temperature*100)%100);
            adc_buff[framelen++]=((uint8_t)(ADC_CURRENT_mA.signal_2_pressure*100)/100);
            adc_buff[framelen++]=((uint8_t)(ADC_CURRENT_mA.signal_2_pressure*100)%100);
            adc_buff[framelen++]=((uint8_t)(ADC_CURRENT_mA.signal_3_temperature*100)/100);
            adc_buff[framelen++]=((uint8_t)(ADC_CURRENT_mA.signal_3_temperature*100)%100);
            adc_buff[framelen++]=((uint8_t)(ADC_CURRENT_mA.signal_3_pressure*100)/100);
            adc_buff[framelen++]=((uint8_t)(ADC_CURRENT_mA.signal_3_pressure*100)%100);
            adc_buff[framelen++]=((uint8_t)(ADC_CURRENT_mA.signa2_1_temperature*100)/100);
            adc_buff[framelen++]=((uint8_t)(ADC_CURRENT_mA.signa2_1_temperature*100)%100);
            adc_buff[framelen++]=((uint8_t)(ADC_CURRENT_mA.signa2_1_pressure*100)/100);
            adc_buff[framelen++]=((uint8_t)(ADC_CURRENT_mA.signa2_1_pressure*100)%100);
            adc_buff[framelen++]=((uint8_t)(ADC_CURRENT_mA.signa2_2_temperature*100)/100);
            adc_buff[framelen++]=((uint8_t)(ADC_CURRENT_mA.signa2_2_temperature*100)%100);
            adc_buff[framelen++]=((uint8_t)(ADC_CURRENT_mA.signa2_2_pressure*100)/100);
            adc_buff[framelen++]=((uint8_t)(ADC_CURRENT_mA.signa2_2_pressure*100)%100);
            adc_buff[framelen++]=((uint8_t)(ADC_CURRENT_mA.signa2_3_temperature*100)/100);
            adc_buff[framelen++]=((uint8_t)(ADC_CURRENT_mA.signa2_3_temperature*100)%100);
            adc_buff[framelen++]=((uint8_t)(ADC_CURRENT_mA.signa2_3_pressure*100)/100);
            adc_buff[framelen++]=((uint8_t)(ADC_CURRENT_mA.signa2_3_pressure*100)%100);
            adc_buff[framelen++]=0x55;
            adc_buff[framelen++]=0xAA;
            adc_buff[2]=framelen-5;
            RS422_Send_String(adc_buff,framelen);/*将采集到的数据通过串口发送，每个通道用2个字节表示，第一个字节为整数，第二个为小数*/
        }
        if(Rs422_revice==1)/*测试使用，对RS422接收的数据进行处理*/
        {
            Rs422_revice=0;
            switch(Rs422_revice_type)
            {
            case 0x11:  /*测试使用，修改开关阀1占空比*/
                set_switch1_status(Rs422_revice_data%101);
                break;
            case 0x12:  /*测试使用，修改开关阀2占空比*/
                set_switch2_status(Rs422_revice_data%101);
                break;
            case 0x13:  /*测试使用，修改开关阀3占空比*/
                set_switch3_status(Rs422_revice_data%101);
                break;
            case 0x14:  /*测试使用，修改开关阀4占空比*/
                set_switch4_status(Rs422_revice_data%101);
                break;
            case 0x21:  /*测试使用，修改电机1占空比*/
                set_motor1_status(Rs422_revice_data%101);
                break;
            case 0x22:  /*测试使用，修改电机2占空比*/
                set_motor2_status(Rs422_revice_data%101);
                break;
            case 0x31:  /*测试使用，修改motor1 BRK 输出状态*/
                Set_Motor_pin(MOTOR1_BRK,Rs422_revice_data%2);
                break;
            case 0x32:  /*测试使用，修改motor1 DIR 输出状态*/
                Set_Motor_pin(MOTOR1_DIR,Rs422_revice_data%2);
                break;
            case 0x33:  /*测试使用，修改motor1 BRK 输出状态*/
                Set_Motor_pin(MOTOR2_BRK,Rs422_revice_data%2);
                break;
            case 0x34:  /*测试使用，修改motor1 DIR 输出状态*/
                Set_Motor_pin(MOTOR2_DIR,Rs422_revice_data%2);
                break;
            }
        }

    }
}
