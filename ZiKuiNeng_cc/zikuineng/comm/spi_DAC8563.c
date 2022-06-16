/*
 * spi_DAC8563.c
 *
 *  Created on: 2022年4月1日
 *      Author: EDY
 */
#include "include.h"

/*******************************
 * void set_CS(unsigned char status)
 * 设置CS的输出状态。
 ******************************/
void set_CS(unsigned char status)
{
   if(status==HIGH)
   {
       GpioDataRegs.GPCDAT.bit.GPIO76 = 1;   /* output high*/
   }
   else
   {
       GpioDataRegs.GPCDAT.bit.GPIO76 = 0;   /* output LOW*/
   }
}

/*******************************
 * void set_CLK(unsigned char status)
 * 设置CLK的输出状态。
 ******************************/
void set_CLK(unsigned char status)
{
   if(status==HIGH)
   {
       GpioDataRegs.GPCDAT.bit.GPIO77 = 1;   /* output high*/
   }
   else
   {
       GpioDataRegs.GPCDAT.bit.GPIO77 = 0;   /* output LOW*/
   }
}

/*******************************
 * void set_MOSI(unsigned char status)
 * 设置MOSI的输出状态。
 ******************************/
void set_MOSI(unsigned char status)
{
   if(status==HIGH)
   {
       GpioDataRegs.GPCDAT.bit.GPIO78 = 1;   /* output high*/
   }
   else
   {
       GpioDataRegs.GPCDAT.bit.GPIO78 = 0;   /* output LOW*/
   }
}

/*******************************
 * void DAC8563_Init(void)
 * DAC8563模块初始化。
 ******************************/
void DAC8563_Init(void)
{
    set_CS(HIGH);
    set_CLK(HIGH);
    set_MOSI(HIGH);
    delay_us(10000);
    set_CS(LOW);
    set_CLK(LOW);
    set_MOSI(LOW);
    uint8_t i=0;
    for(i=0;i<10;i++)
    {
        delay_us(10000);
        delay_us(10000);
        delay_us(10000);
    }
    uint32_t cmd_data=0;
    cmd_data |=((uint32_t)4 << 19) | ((uint32_t)0 << 16) | (3 << 0);
    /* Power up DAC-A and DAC-B */
    SpiWriteCmd(cmd_data);
    cmd_data=0;
    cmd_data |=((uint32_t)6 << 19) | ((uint32_t)0 << 16) | (3 << 0);
     /* LDAC pin inactive for DAC-B and DAC-A  不使用LDAC引脚更新数据 */
    SpiWriteCmd(cmd_data);
    cmd_data=0;
    cmd_data |=((uint32_t)7 << 19) | ((uint32_t)0 << 16) | (1 << 0);
    /* 选择内部参考并复位2个DAC的增益=2 （复位时，内部参考是禁止的) */
    SpiWriteCmd(cmd_data);
}

/*******************************
 * void SpiWriteCmd(unsigned long cmd)
 * SPI写指令
 * *cmd: 指令
 ******************************/
void SpiWriteCmd(unsigned long cmd)
{
    int i;
    set_CS(LOW);
    for(i=0; i<24; i++)
    {
            set_CLK(HIGH);
            /***********WRITE DATA**************/
            if(0x800000==(cmd & 0x800000))
            {
                set_MOSI(HIGH);
            }
            else
            {
                set_MOSI(LOW);
            }
            cmd<<=1;
            delay_us(1000);
            set_CLK(LOW);
            delay_us(1000);
     }
    set_CS(HIGH);
    delay_us(10000);
    set_CLK(HIGH);
}

/*******************************
 * void DAC8563_SetData(uint8_t _ch, uint16_t _dac)
 * 跟新指定通道的电压
 * _ch：通道号 0~1
 * _dac: 电压数据
 ******************************/
void DAC8563_SetData(uint8_t _ch, uint16_t _dac)
{
    uint32_t cmd_data=0;
    if (_ch == 0)
    {
        cmd_data |=((uint32_t)3 << 19) | ((uint32_t)0 << 16) | (_dac << 0);
        /* Write to DAC-A input register and update DAC-A; */
        SpiWriteCmd(cmd_data);
    }
    else if (_ch == 1)
    {
        cmd_data |=((uint32_t)3 << 19) | ((uint32_t)1 << 16) | (_dac << 0);
        /* Write to DAC-B input register and update DAC-A; */
        SpiWriteCmd(cmd_data);
    }
}

/*******************************
 * void DAC8563_SetVoltage_mv(unsigned int DACselect, unsigned long Voltage)
 * 输出DAC值。
 * DACselect:   DAC_A | DAC_B
 * Voltage:     0  ~ 3000mV
 *
 ******************************/
void DAC8563_SetVoltage_mv(uint8_t DACselect, unsigned long Voltage)
{
    if(Voltage >3000)
        Voltage = 3000;
    unsigned long dacV =Voltage*3267.8/1000+32768;
    DAC8563_SetData(DACselect, dacV);
    delay_ns(100);
}

