/*
 * EEPROM.c
 *
 *  Created on: 2021年4月22日
 *      Author: Lee
 */
#include "include.h"
#include "DSP2833x_Device.h"

/*********************************************
 *
 * 模拟IIC
 * *******************************************/

/*******************************************************************************
Function:       // Set_SDA_Pin_Input
Description:    // set SDA pin as input
Input:          // none
Output:         // none
*******************************************************************************/
void Set_SDA_Pin_Input(void)
{
       EALLOW;

       GpioCtrlRegs.GPBPUD.bit.GPIO32 = 0;   /* Enable pullup on GPIO15  (SDA)*/
       GpioCtrlRegs.GPBMUX1.bit.GPIO32 = 0;  /* GPIO32 = GPIO32 */
       GpioCtrlRegs.GPBDIR.bit.GPIO32 = 0;   /* GPIO32 = intput*/

        EDIS;
}
/*******************************************************************************
Function:       // Set_SDA_Pin_Output
Description:    // set SDA pin as output
Input:          // none
Output:         // none
*******************************************************************************/
void Set_SDA_Pin_Output(void)
{
       EALLOW;

       GpioCtrlRegs.GPBPUD.bit.GPIO32 = 0;   /* Enable pullup on GPIO15  (SDA)*/
       GpioCtrlRegs.GPBMUX1.bit.GPIO32 = 0;  /* GPIO32 = GPIO32 */
       GpioCtrlRegs.GPBDIR.bit.GPIO32 = 1;   /* GPIO32 = output*/

        EDIS;
}
/*******************************************************************************
Function:       // set_IIC_SDA_High
Description:    // set IIC SDA pin high
Input:          // none
Output:         // none
*******************************************************************************/
void set_IIC_SDA_High(void)
{
    GpioDataRegs.GPBDAT.bit.GPIO32 = 1;   /* output high*/
}
/*******************************************************************************
Function:       // set_IIC_SDA_Low
Description:    // set IIC SDA pin low
Input:          // none
Output:         // none
*******************************************************************************/
void set_IIC_SDA_Low(void)
{
    GpioDataRegs.GPBDAT.bit.GPIO32 = 0;   /* output low*/
}
/*******************************************************************************
Function:       // set_IIC_SCL_High
Description:    // set IIC SCL pin high
Input:          // none
Output:         // none
*******************************************************************************/
void set_IIC_SCL_High(void)
{
    GpioDataRegs.GPBDAT.bit.GPIO33 = 1;   /* output high*/
}
/*******************************************************************************
Function:       // set_IIC_SCL_Low
Description:    // set IIC SCL pin low
Input:          // none
Output:         // none
*******************************************************************************/
void set_IIC_SCL_Low(void)
{
    GpioDataRegs.GPBDAT.bit.GPIO33 = 0;   /* output low*/
}
/*******************************************************************************
Function:       // Get_SDA_status
Description:    // get IIC SDA pin status
Input:          // none
Output:         // IIC SDA pin status
*******************************************************************************/
uint8_t Get_SDA_status(void)
{
    return GpioDataRegs.GPBDAT.bit.GPIO32;
}
/*******************************************************************************
Function:       // IIC_Start
Description:    // IIC start condition
Input:          // none
Output:         // none
*******************************************************************************/
void IIC_Start(void)
{
    Set_SDA_Pin_Output();
    set_IIC_SDA_High();
    set_IIC_SCL_High();
    DELAY_US(4);
    set_IIC_SDA_Low();
    DELAY_US(4);
    set_IIC_SCL_Low();
}
/*******************************************************************************
Function:       // IIC_Stop
Description:    // IIC stop condition
Input:          // none
Output:         // none
*******************************************************************************/
void IIC_Stop(void)
{
    Set_SDA_Pin_Output();
    set_IIC_SCL_Low();
    set_IIC_SDA_Low();
    DELAY_US(4);
    set_IIC_SCL_High();
    set_IIC_SDA_High();
    DELAY_US(4);
}
/*******************************************************************************
Function:       // IIC_Wait_Ack
Description:    // IIC wait ack
Input:          // none
Output:         // wait ACK result: 0--success; 1--fail
*******************************************************************************/
uint8_t IIC_Wait_Ack(void)
{
   uint8_t ucerrtime=0;
   Set_SDA_Pin_Input();
   set_IIC_SDA_High();
   DELAY_US(1);
   set_IIC_SCL_High();
   DELAY_US(1);
   while(Get_SDA_status())
   {
       ucerrtime++;
       if(ucerrtime>250)
       {
           IIC_Stop();
           return 1;
       }
   }
   set_IIC_SCL_Low();
   return 0;
}
/*******************************************************************************
Function:       // IIC_Ack
Description:    // IIC ack condition
Input:          // none
Output:         // none
*******************************************************************************/
void IIC_Ack(void)
{
    set_IIC_SCL_Low();
    Set_SDA_Pin_Output();
    set_IIC_SDA_Low();
    DELAY_US(2);
    set_IIC_SCL_High();
    DELAY_US(2);
    set_IIC_SCL_Low();
}
/*******************************************************************************
Function:       // IIC_NAck
Description:    // IIC no ack condition
Input:          // none
Output:         // none
*******************************************************************************/
void IIC_NAck(void)
{
    set_IIC_SCL_Low();
    Set_SDA_Pin_Output();
    set_IIC_SDA_High();
    DELAY_US(2);
    set_IIC_SCL_High();
    DELAY_US(2);
    set_IIC_SCL_Low();
}
/*******************************************************************************
Function:       // IIC_Send_Byte
Description:    // IIC send one byte
Input:          // senddata:send byte
Output:         // none
*******************************************************************************/
void IIC_Send_Byte(uint8_t senddata)
{
    uint8_t t;
    Set_SDA_Pin_Output();
    set_IIC_SCL_Low();
    for(t=0;t<8;t++)
    {
        if((senddata&0x80)>>7)
            set_IIC_SDA_High();
        else
            set_IIC_SDA_Low();
        senddata<<=1;
        DELAY_US(2);
        set_IIC_SCL_High();
        DELAY_US(2);
        set_IIC_SCL_Low();
        DELAY_US(2);
    }
}
/*******************************************************************************
Function:       // IIC_Read_Byte
Description:    // IIC read one byte
Input:          // none
Output:         // read byte
*******************************************************************************/
uint8_t IIC_Read_Byte(void)
{
    uint8_t i,revice=0;
    Set_SDA_Pin_Input();
    for(i=0;i<8;i++)
    {
        set_IIC_SCL_Low();
        DELAY_US(2);
        set_IIC_SCL_High();
        revice<<=1;
        if(Get_SDA_status())
            revice++;
        DELAY_US(1);
    }
    return revice;
}
/*******************************************************************************
Function:       // AT24C512_ReadOneByte
Description:    // Read one byte from AT24C512 specified address
Input:          // readaddr: read address
Output:         // read byte
*******************************************************************************/
uint8_t AT24C512_ReadOneByte(uint16_t readaddr)
{
    uint8_t temp=0;
    IIC_Start();
    IIC_Send_Byte(0xA0);
    IIC_Wait_Ack();
    IIC_Send_Byte(readaddr>>8);
    IIC_Wait_Ack();
    IIC_Send_Byte(readaddr%256);
    IIC_Wait_Ack();
    IIC_Start();
    IIC_Send_Byte(0xA1);
    IIC_Wait_Ack();
    temp=IIC_Read_Byte();
    IIC_NAck();
    IIC_Stop();
    return temp;
}
/*******************************************************************************
Function:       // AT24C512_WriteOneByte
Description:    // Write a byte to the specified address of AT24C512
Input:          // writeaddr: write address
                // writedata: write byte
Output:         // none
*******************************************************************************/
void AT24C512_WriteOneByte(uint16_t writeaddr,uint8_t writedata)
{
    IIC_Start();
    IIC_Send_Byte(0xA0);
    IIC_Wait_Ack();
    IIC_Send_Byte(writeaddr>>8);
    IIC_Wait_Ack();
    IIC_Send_Byte(writeaddr%256);
    IIC_Wait_Ack();
    IIC_Send_Byte(writedata);
    IIC_Wait_Ack();
    IIC_Stop();
    DELAY_US(10000);
}
/*******************************************************************************
Function:       // AT24C512_WritelenByte
Description:    // Write buff to the specified address of AT24C512
Input:          // writeaddr: write address
                // writedata: write datas
                // len: write length
Output:         // none
*******************************************************************************/
void AT24C512_WritelenByte(uint16_t writeaddr,uint8_t * writedata,uint8_t len)
{
    uint8_t i=0;
    for(i=0;i<len;i++)
    {
        AT24C512_WriteOneByte(writeaddr+i,writedata[i]);
    }
}
/*******************************************************************************
Function:       // AT24C512_ReadlenByte
Description:    // Read buff from AT24C512 specified address
Input:          // readaddr: read address
                // readdata: save read  data
                // len: read length
Output:         // none
*******************************************************************************/
void AT24C512_ReadlenByte(uint16_t readaddr,uint8_t * readdata,uint8_t len)
{
       uint8_t i=0;
        for(i=0;i<len;i++)
        {
            readdata[i]=AT24C512_ReadOneByte(readaddr+i);
        }
}
/*******************************************************************************
Function:       // AT24C512_WriteString
Description:    // Write buff to the specified address of AT24C512
Input:          // writeaddr: write address
                // writedata: write datas
                // len: write length
Output:         // none
*******************************************************************************/
void AT24C512_WriteString(uint16_t writeaddr,uint8_t * writedata,uint8_t len)
{
       uint8_t i=0;
       IIC_Start();
       IIC_Send_Byte(0xA0);
       IIC_Wait_Ack();
       IIC_Send_Byte(writeaddr>>8);
       IIC_Wait_Ack();
       IIC_Send_Byte(writeaddr%256);
       IIC_Wait_Ack();
       for(i=0;i<len;i++)
       {
           IIC_Send_Byte(writedata[i]);
           IIC_Wait_Ack();
           writeaddr++;
           if((((uint8_t)writeaddr)%32)==0)
           {
               IIC_Stop();
               DELAY_US(10000);
               IIC_Start();
               IIC_Send_Byte(0xA0);
               IIC_Wait_Ack();
               IIC_Send_Byte(writeaddr>>8);
               IIC_Wait_Ack();
               IIC_Send_Byte(writeaddr%256);
               IIC_Wait_Ack();
           }
       }
       IIC_Stop();
       DELAY_US(10000);
}
/*******************************************************************************
Function:       // AT24C512_ReadlenByte
Description:    // Read buff from AT24C512 specified address
Input:          // readaddr: read address
                // readdata: save read  data
                // len: read length
Output:         // none
*******************************************************************************/
void AT24C512_ReadString(uint16_t readaddr,uint8_t * revicedata,uint8_t readlen)
{
    uint8_t i=0;
    IIC_Start();
    IIC_Send_Byte(0xA0);
    IIC_Wait_Ack();
    IIC_Send_Byte(readaddr>>8);
    IIC_Wait_Ack();
    IIC_Send_Byte(readaddr%256);
    IIC_Wait_Ack();
    IIC_Start();
    IIC_Send_Byte(0xA1);
    IIC_Wait_Ack();
    for(i=0;i<readlen;i++)
    {
        revicedata[i]=IIC_Read_Byte();
           readaddr++;
           if(i<(readlen-1))
           {
               IIC_Ack();
           }
    }
    IIC_NAck();
    IIC_Stop();
    DELAY_US(10000);
}
