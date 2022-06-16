/*
 * ADC_temperature.c
 *
 *  Created on: 2021骞�4鏈�20鏃�
 *      Author: Lee
 *      read message register at 36
 */
#include "include.h"
ADC_CURRENT ADC_CURRENT_mA;
void ADS_SCLK_H(void)
{
    GpioDataRegs.GPADAT.bit.GPIO18 = 1;   /* output low*/
}

void ADS_SCLK_L(void)
{
    GpioDataRegs.GPADAT.bit.GPIO18 = 0;   /* output low*/
}
void SPI_MOSI_High(void)
{
    GpioDataRegs.GPADAT.bit.GPIO16 = 1;   /* output low*/
}
void SPI_MOSI_Low(void)
{
    GpioDataRegs.GPADAT.bit.GPIO16 = 0;   /* output low*/
}

uint8_t Get_SPI_MISO(void)
{
    return(GpioDataRegs.GPADAT.bit.GPIO17 &0x00ff);
}
/*******************************************************************************
Function:       // ADS_START_L
Description:    // set START pin  low
Input:          // none
Output:         // none
*******************************************************************************/
void ADS_START_L(void)
{
    GpioDataRegs.GPADAT.bit.GPIO15 = 0;   /* output low*/
}
/*******************************************************************************
Function:       // ADS_START_H
Description:    // set START pin  high
Input:          // none
Output:         // none
*******************************************************************************/
void ADS_START_H(void)
{
    GpioDataRegs.GPADAT.bit.GPIO15 = 1;   /* output high*/
}
/*******************************************************************************
Function:       // ADS_CS_L
Description:    // set CS pin  low
Input:          // none
Output:         // none
*******************************************************************************/
void ADS_CS_L(void)
{
    GpioDataRegs.GPADAT.bit.GPIO19 = 0;   /* output low*/
}
/*******************************************************************************
Function:       // ADS_CS_H
Description:    // set CS pin  high
Input:          // none
Output:         // none
*******************************************************************************/
void ADS_CS_H(void)
{
    GpioDataRegs.GPADAT.bit.GPIO19 = 1;   /* output high*/
}
/*******************************************************************************
Function:       // Read_ADS_DRDY
Description:    // get DRDY pin  status
Input:          // none
Output:         // pin  status
*******************************************************************************/
uint8_t Read_ADS_DRDY(void)
{
    return GpioDataRegs.GPBDAT.bit.GPIO49;
}
#if (SPI_MODE == HARDWARE_SPI)
/*******************************************************************************
Function:       // ADS8698_Int
Description:    // Configuration the ADS8698
Input:          // none
Output:         // none
*******************************************************************************/
void ADS1258_SPI_Int(void)
{
    SpiaRegs.SPIFFTX.all=0xE040;
    SpiaRegs.SPIFFRX.all=0x2040;
    SpiaRegs.SPIFFCT.all=0x0;

    SpiaRegs.SPICCR.all =0x0007;

    SpiaRegs.SPICTL.all =0x0006;
 //   SpiaRegs.SPIBRR =0x007F;    //SPI娉㈢壒鐜�=25M/128    =195.3KHZ锛�   =37.5/128293KHZ
    SpiaRegs.SPIBRR =0x001a;
    SpiaRegs.SPICCR.all =0x0087;

    SpiaRegs.SPIPRI.bit.FREE = 1;

}
/******************************************************************************
Function:       // ADS1258_Int
Description:    // ADS1258 initialization (hardware spi)
Input:          // none
Output:         // none
*******************************************************************************/
void ADS1258_Int(void)
{
       ADC_CURRENT_mA.signal_1_temperature = 0;
       ADC_CURRENT_mA.signal_1_pressure = 0;
       ADC_CURRENT_mA.signal_2_temperature = 0;
       ADC_CURRENT_mA.signal_2_pressure = 0;
       ADC_CURRENT_mA.signal_3_temperature = 0;
       ADC_CURRENT_mA.signal_3_pressure = 0;
       ADC_CURRENT_mA.signa2_1_temperature = 0;
       ADC_CURRENT_mA.signa2_1_pressure = 0;
       ADC_CURRENT_mA.signa2_2_temperature = 0;
       ADC_CURRENT_mA.signa2_2_pressure = 0;
       ADC_CURRENT_mA.signa2_3_temperature = 0;
       ADC_CURRENT_mA.signa2_3_pressure = 0;

       ADS_START_L();
       ADS_CS_L();
       AD_Delay();
       ADS_CS_H();
       DELAY_US(260);

       ADS_CS_L();
       AD_Delay();
       uint8_t TXData = 0;
       TXData = 0xC0;
       Spi_Send(TXData);//RESET
       DELAY_US(260);
       ADS_CS_H();

           //[0]
           ADS_CS_L();
           AD_Delay();
           TXData = 0x60;
           Spi_Send(TXData);
           TXData = 0x0A;
           Spi_Send(TXData);
           AD_Delay();
           ADS_CS_H();

           //[1]
           ADS_CS_L();
           AD_Delay();
           TXData = 0x61;
           Spi_Send(TXData);
           TXData = 0xB3;
           Spi_Send(TXData);
           AD_Delay();
           ADS_CS_H();

           //[2]
           ADS_CS_L();
           AD_Delay();
           TXData = 0x62;
           Spi_Send(TXData);
           TXData = 0x00;
           Spi_Send(TXData);
           AD_Delay();
           ADS_CS_H();

           //[3]
           ADS_CS_L();
           AD_Delay();
           TXData = 0x63;
           Spi_Send(TXData);
           TXData = 0x00;
           Spi_Send(TXData);
           AD_Delay();
           ADS_CS_H();

           //[4]
           ADS_CS_L();
           AD_Delay();
           TXData = 0x64;
           Spi_Send(TXData);
           TXData = 0xff;
           Spi_Send(TXData);
           AD_Delay();
           ADS_CS_H();

           //[5]
           ADS_CS_L();
           AD_Delay();
           TXData = 0x65;
           Spi_Send(TXData);
           TXData = 0x0f;
           Spi_Send(TXData);
           AD_Delay();
           ADS_CS_H();

           //[6]
           ADS_CS_L();
           AD_Delay();
           TXData = 0x66;
           Spi_Send(TXData);
           TXData = 0x00;
           Spi_Send(TXData);
           AD_Delay();
           ADS_CS_H();

           //[7]
           ADS_CS_L();
           AD_Delay();
           TXData = 0x67;
           Spi_Send(TXData);
           TXData = 0x00;
           Spi_Send(TXData);
           AD_Delay();
           ADS_CS_H();

           //[8]
           ADS_CS_L();
           AD_Delay();
           TXData = 0x68;
           Spi_Send(TXData);
           TXData = 0x00;
           Spi_Send(TXData);
           AD_Delay();
           ADS_CS_H();

        ADS_START_H();
}
/*******************************************************************************
Function:       // Spi_Send
Description:    // spi send a data
Input:          // data: send data
Output:         // none
*******************************************************************************/
uint8_t Spi_Send(uint8_t data)
{
    SpiaRegs.SPITXBUF=(data<<8);
    while(SpiaRegs.SPIFFRX.bit.RXFFST ==0);
    return (SpiaRegs.SPIRXBUF);
}
/*******************************************************************************
Function:       // SPI_Read_Data
Description:    // spi send command and read data
Input:          // *revice_data: save revice data
Output:         // revice len
*******************************************************************************/
uint8_t  SPI_Read_Data(void)
{
      uint8_t len=0;
      uint8_t i=0;
      uint8_t redata=0;
      SpiaRegs.SPITXBUF=0;
      len=SpiaRegs.SPIFFRX.bit.RXFFST;
      if(len>0)
      {
          for(i=0;i<len;i++)
          {
              redata=(uint8_t)(SpiaRegs.SPIRXBUF& 0xff);     // Read data
          }
      }
      return redata;
}
#else
/******************************************************************************
Function:       // ADS1258_Int
Description:    // ADS1258 initialization (simulation spi)
Input:          // none
Output:         // none
*******************************************************************************/
void ADS1258_Int(void)
{
    ADC_CURRENT_mA.signal_1_temperature = 0;
    ADC_CURRENT_mA.signal_1_pressure = 0;
    ADC_CURRENT_mA.signal_2_temperature = 0;
    ADC_CURRENT_mA.signal_2_pressure = 0;
    ADC_CURRENT_mA.signal_3_temperature = 0;
    ADC_CURRENT_mA.signal_3_pressure = 0;
    ADC_CURRENT_mA.signa2_1_temperature = 0;
    ADC_CURRENT_mA.signa2_1_pressure = 0;
    ADC_CURRENT_mA.signa2_2_temperature = 0;
    ADC_CURRENT_mA.signa2_2_pressure = 0;
    ADC_CURRENT_mA.signa2_3_temperature = 0;
    ADC_CURRENT_mA.signa2_3_pressure = 0;

    ADC_CURRENT_mA.signal_1_temperature_err = 0;
    ADC_CURRENT_mA.signal_1_pressure_err = 0;
    ADC_CURRENT_mA.signal_2_temperature_err = 0;
    ADC_CURRENT_mA.signal_2_pressure_err = 0;
    ADC_CURRENT_mA.signal_3_temperature_err = 0;
    ADC_CURRENT_mA.signal_3_pressure_err = 0;
    ADC_CURRENT_mA.signa2_1_temperature_err = 0;
    ADC_CURRENT_mA.signa2_1_pressure_err = 0;
    ADC_CURRENT_mA.signa2_2_temperature_err = 0;
    ADC_CURRENT_mA.signa2_2_pressure_err = 0;
    ADC_CURRENT_mA.signa2_3_temperature_err = 0;
    ADC_CURRENT_mA.signa2_3_pressure_err = 0;

       ADS_START_L();
       ADS_CS_L();
       AD_Delay();
       ADS_CS_H();
       DELAY_US(260);

       uint8_t TXData = 0;
       SPI_START();
       TXData = 0x00C0;
       SPI_SEND_BYTE(TXData);
       SPI_END();

       SPI_START();
       TXData = 0x0060;
       SPI_SEND_BYTE(TXData);
       TXData = 0x000A;
       SPI_SEND_BYTE(TXData);
       SPI_END();

        SPI_START();
        TXData = 0x0061;
        SPI_SEND_BYTE(TXData);
        TXData = 0x00B3;
        SPI_SEND_BYTE(TXData);
        SPI_END();

        SPI_START();
        TXData = 0x0062;
        SPI_SEND_BYTE(TXData);
        TXData = 0x0000;
        SPI_SEND_BYTE(TXData);
        SPI_END();

        SPI_START();
        TXData = 0x0063;
        SPI_SEND_BYTE(TXData);
        TXData = 0x0000;
        SPI_SEND_BYTE(TXData);
        SPI_END();

        SPI_START();
        TXData = 0x0064;
        SPI_SEND_BYTE(TXData);
        TXData = 0x00FF;
        SPI_SEND_BYTE(TXData);
        SPI_END();

        SPI_START();
        TXData = 0x0065;
        SPI_SEND_BYTE(TXData);
        TXData = 0x000F;
        SPI_SEND_BYTE(TXData);
        SPI_END();

        SPI_START();
        TXData = 0x0066;
        SPI_SEND_BYTE(TXData);
        TXData = 0x0000;
        SPI_SEND_BYTE(TXData);
        SPI_END();

        SPI_START();
        TXData = 0x0067;
        SPI_SEND_BYTE(TXData);
        TXData = 0x0000;
        SPI_SEND_BYTE(TXData);
        SPI_END();

        SPI_START();
        TXData = 0x0068;
        SPI_SEND_BYTE(TXData);
        TXData = 0x0000;
        SPI_SEND_BYTE(TXData);
        SPI_END();

        ADS_START_H();
}
/******************************************************************************
Function:       // SPI_START
Description:    // spi start condition
Input:          // none
Output:         // none
*******************************************************************************/
void SPI_START(void)
{
         ADS_CS_H();
         ADS_SCLK_L();
         AD_Delay();
         ADS_CS_L();
}
/******************************************************************************
Function:       // SPI_END
Description:    // spi end condition
Input:          // none
Output:         // none
*******************************************************************************/
void SPI_END(void)
{
    ADS_CS_L();
    ADS_SCLK_L();
    AD_Delay();
    ADS_CS_H();
}
/******************************************************************************
Function:       // SPI_SEND_BYTE
Description:    // spi send byte
Input:          // senddata : send byte
Output:         // none
*******************************************************************************/
void SPI_SEND_BYTE(uint8_t senddata)
{
     uint8_t t=0;
    for(t=0;t<8;t++)
     {
         if((senddata&0x80))
             SPI_MOSI_High();
         else
             SPI_MOSI_Low();
         senddata<<=1;
         ADS_SCLK_H();
         AD_Delay1();
         ADS_SCLK_L();
         AD_Delay1();
     }
}
/******************************************************************************
Function:       // SPI_READ_BYTE1
Description:    // spi revice byte
Input:          // none
Output:         // revice data
*******************************************************************************/
uint8_t SPI_READ_BYTE1(void)
{
    uint8_t i,revice=0;
     for(i=0;i<8;i++)
     {
         ADS_SCLK_L();
         AD_Delay1();
         ADS_SCLK_H();
         revice<<=1;
         if(Get_SPI_MISO())
             revice++;
         AD_Delay1();
     }
     return revice;
}
#endif
/*******************************************************************************
Function:       // ADS1258_ReadDate
Description:    // Get ADS1258 12 channel vale
Input:          // none
Output:         // 0--Collection ok; 1--Collection error;
*******************************************************************************/
uint32_t time=0; /*test code*/
uint32_t readcount=0; /*test code*/
uint32_t timecount=0; /*test code*/
unsigned char ADS1258_ReadDate(void)
{
    uint32_t adc_value;
    uint8_t TXData;
    uint8_t i=0;
    uint8_t RXData[50]={0};
    uint8_t Collection_results=0;
    int  CH=0;
    float Voltage_value = 0;
#if (SPI_MODE == HARDWARE_SPI)
    while(Read_ADS_DRDY() && dalay_adc<30000)
   {
       dalay_adc++;
    }
    ADS_CS_L();
    AD_Delay();
    TXData = 0x0030;
    Spi_Send(TXData);
    TXData = 0x0000;
    while(time_out--)
    {
        RXData[len++]=Spi_Send(TXData);
        if(len>=4) break;
    }
    ADS_CS_H();

#else
    SPI_START();
    TXData = 0x30;
    SPI_SEND_BYTE(TXData);
    for(i=0;i<4;i++)
    {
        RXData[i]=SPI_READ_BYTE1();
    }
   SPI_END();
#endif

    adc_value = (uint32_t)
            (
                    ((((uint32_t)RXData[1]) << 16) & 0xFF0000) |
                    ((((uint32_t)RXData[2]) << 8 ) & 0x00FF00) |
                     (((uint32_t)RXData[3]) << 0 )
            );
    int32 data = (int32)(adc_value << 8);
    data = data / 256;
    CH = (uint8_t)(RXData[0] & 0x1F);
    if((CH < 8)||(CH >19))
    {
        return 0;
    }
    Voltage_value = ((data * Reference_Voltage / 0x780000));
    if((Voltage_value >= -0.2) && (Voltage_value <=3.52))
    {
        float* p = &ADC_CURRENT_mA.signal_1_temperature;
        p += (CH - 8);
        *p = Voltage_value;
        ADC_CURRENT_mA.collection_valid |= 1 << (CH - 8);
    }
    else
    {
        unsigned char* p = &ADC_CURRENT_mA.signal_1_temperature_err;
        p += (CH - 8);
        (*p)++;
        if((*p)>=5)
        {
            Collection_results=1;
        }
    }
    return Collection_results;
}

/*******************************************************************************
Function:       // AD_Delay
Description:    // Delay for ADS1258
Input:          // none
Output:         // none
*******************************************************************************/
void AD_Delay(void)
{
   int count_1=0;
   for(count_1=0;count_1<5;count_1++)  //50
    {}
}

void AD_Delay1(void)
{
    int count_1=0;
    for(count_1=0;count_1<1;count_1++)  //5
    {}
}
/******************************************************************************
Function:       // ADC_Read
Description:    // Read 16-channel ADC value
Input:          // none
Output:         // sucess 0;fail 1;
*******************************************************************************/
uint8_t ADC_Read(void)
{
    uint8_t read_num=0;
    uint8_t Collection_results=0;
    ADS_count=0;
    for(read_num=0;read_num<200;read_num++)
    {
        Collection_results=ADS1258_ReadDate();
        if(ADC_CURRENT_mA.collection_valid==0x0fff) break;
    }
    time=ADS_count;
    readcount=read_num;
    ADC_CURRENT_mA.collection_valid=0x0000;
    if(read_num>=20 || Collection_results==1)
        return 1;
    else
        return 0;
}

