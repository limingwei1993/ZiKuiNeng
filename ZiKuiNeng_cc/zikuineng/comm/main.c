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
uint8_t test_1=200;/*测试使用，测试开关阀1*/
uint8_t test_2=200;/*测试使用，测试开关阀2*/
uint8_t test_3=200;/*测试使用，测试开关阀3*/
uint8_t test_4=200;/*测试使用，测试开关阀4*/
uint8_t test_5=200;/*测试使用，测试电机1*/
uint8_t test_6=200;/*测试使用，测试电机1*/
uint8_t test_7=200;/*测试使用，测试rs422*/
uint32_t test_9=0;/*测试使用，测试DAC输出电压mA*/
uint8_t num=0;/*测试使用，测试拨码开关*/
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
uint8_t send_ADC_value=0;/*测试使用，测试ADC采样*/
uint8_t adc_buff[100]={0};/*测试使用，测试ADC采样*/
uint8_t framelen=0;/*测试使用，测试ADC采样*/
uint8_t Rs422_revice=0;/*测试使用，测试串口*/
uint8_t Rs422_revice_type=0;/*测试使用，测试串口*/
uint8_t eeprom_send_buff[120]={0};/*测试使用*/
uint8_t switch1_on_off=0;/*测试使用，测试开关阀1*/
uint8_t switch2_on_off=0;/*测试使用，测试开关阀2*/
uint8_t switch3_on_off=0;/*测试使用，测试开关阀3*/
uint8_t switch4_on_off=0;/*测试使用，测试开关阀4*/
uint8_t motor1_on_off=0;/*测试使用，测试电机1*/
uint8_t motor2_on_off=0;/*测试使用，测试电机1*/
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
    Pwm1_Switch1_Int();
    Pwm2_Switch2_Int();
    Pwm3_Switch3_Int();
    Pwm4_Switch4_Int();
    Pwm5_Motor1_Int();
    Pwm6_Motor2_Int();
    GIOP_Int();
    RS422_Int(115200);
    EINT; /*Enable interrupt*/
    ERTM; /*Enable debug event*/
    ADS1258_Int();
    DAC8563_Init();
    power_on=0;  /*出于测试目的，将电机的软启动关闭了*/
    if(f_mount(&fs,"0:",1) != FR_OK)/*用于测试SD卡，挂在文件系统*/
   {
          RS422_Send_String("\r\nSD_CARD_LOAD_ERR\r\n",18);/*测试使用*/
   }
    for(i=0;i<100;i++)/*测试使用，写数据到EEPROM*/
    {
      eeprom_write_buff[i]= 0;
      sd_write_buff[i]=0;
      AT24C512_WritelenByte(i*100,&eeprom_write_buff[i],1);
    }
    AT24C512_WriteString(100,eeprom_write_buff,100);
    while(1)
    {
        if(test_1!=200)/*测试使用，测试开关阀1*/
        {
            set_switch1_status(test_1);
            test_1=200;
        }
        if(test_2!=200)/*测试使用，测试开关阀2*/
        {
            set_switch2_status(test_2);
            test_2=200;
        }
        if(test_3!=200)/*测试使用，测试开关阀3*/
        {
            set_switch3_status(test_3);
            test_3=200;
        }
        if(test_4!=200)/*测试使用，测试开关阀4*/
        {
            set_switch4_status(test_4);
            test_4=200;
        }
        if(test_5!=200)/*测试使用，测试电机1*/
        {
            set_motor1_status(test_5);
            test_5=200;
        }
        if(test_6!=200)/*测试使用，测试电机2*/
        {
            set_motor2_status(test_6);
            test_6=200;
        }
        if(test_7!=200)/*测试使用，测试rs422发送*/
        {
            RS422_Send_Data();
                    test_7=200;
        }
        if(test_9!=0)/**/
        {
             DAC8563_SetVoltage_mv(0,test_9);
        }
        if(test_eeprom_read==1)/*测试使用，测试EEPROM*/
        {
            /*将保存EEPROM读取的数据打包发送*/
            eeprom_send_buff[0]=0x00;
            eeprom_send_buff[1]=0x55;
            for(i=0;i<100;i++)
            {
                eeprom_send_buff[i+2]=eeprom_read_buff[i];
            }
            eeprom_send_buff[i+2]=0x55;
            eeprom_send_buff[i+3]=0x00;
            eeprom_send_buff[i+4]=0x0D;
            eeprom_send_buff[i+5]=0x0A;
            RS422_Send_String(eeprom_send_buff,106);
            /*读取EEPROM数据*/
            test_eeprom_read=0;
            AT24C512_ReadString(100,eeprom_read_buff,100);
            for(i=0;i<100;i++)
            {
                AT24C512_ReadlenByte(i*100,&eeprom_read_buff[i],1);
               /* if(eeprom_read_buff[i]!=eeprom_write_buff[i])
                {
                    i=100;
                }*/
            }
        }
        if(test_eeprom_write==1)
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
        if(test_sd_write==1)/*测试使用，写数据到SD卡*/
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
        if(test_sd_read==1)/*测试使用，从SD卡读取数据*/
        {
            f_open (&file,  (const TCHAR *)"0:30.txt",FA_READ);
            f_read (&file, sd_read_buff, 100, &readlen);
            f_close (&file);
            test_sd_read=0;
            for(i=0;i<100;i++)
            {
                 if(sd_read_buff[i]!=sd_write_buff[i])
                 {
                     i=100;
                     adc_buff[0]=0x00;
                     adc_buff[1]=0xBB;
                     adc_buff[2]=0xCC;
                     adc_buff[3]=0x00;
                     adc_buff[4]=0xCC;
                     adc_buff[5]=0xBB;
                     adc_buff[6]=0x00;
                     RS422_Send_String(adc_buff,7);
                     break;
                 }
            }
        }
        task_run();/*用于ADC采集*/
        if(send_ADC_value==1)/*测试使用，发送ADC采样的数据*/
        {
            send_ADC_value=0;
            framelen=0;
            adc_buff[framelen++]=0x00;
            adc_buff[framelen++]=0xAA;
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
            adc_buff[framelen++]=0xAA;
            adc_buff[framelen++]=0x00;
            adc_buff[framelen++]='\r';
            adc_buff[framelen++]='\n';
            RS422_Send_String(adc_buff,30);/*将采集到的AD值（电压值）通过串口发送，每个通道用2个字节表示，第一个字节为整数，第二个为小数*/
        }
        if(Rs422_revice==1)/*测试使用，对RS422接收的数据进行处理*/
        {
            Rs422_revice=0;
            switch(Rs422_revice_type)
            {
            case 0x11:  /*测试使用，开关阀1打开10秒*/
                switch1_on_off=7;
                set_switch1_status(70);
                break;
            case 0x12:  /*测试使用，开关阀2打开10秒*/
                switch2_on_off=7;
                set_switch2_status(70);
                break;
            case 0x13:  /*测试使用，开关阀3打开10秒*/
                switch3_on_off=120;
                set_switch3_status(70);
                break;
            case 0x14:  /*测试使用，开关阀4打开10秒*/
                switch4_on_off=120;
                set_switch4_status(70);
                break;
            case 0x21:  /*测试使用，电机打开10秒*/
                motor1_on_off=3;
                set_motor1_status(50);
                break;
            case 0x22:  /*测试使用，电机打开10秒*/
                motor2_on_off=3;
                set_motor2_status(50);
                break;
            case 0x31:  /*测试使用，控制DAC8653输出1V，控制外部电机*/
                DAC8563_SetVoltage_mv(0,1000);
                break;
            case 0x32:  /*测试使用，控制DAC8653输出2V，控制外部电机*/
                DAC8563_SetVoltage_mv(0,2000);
                break;
            case 0x33:  /*测试使用，控制DAC8653输出3V，控制外部电机*/
                DAC8563_SetVoltage_mv(0,3000);
                break;
            }
        }

    }
}
