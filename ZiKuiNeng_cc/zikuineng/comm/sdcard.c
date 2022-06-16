/*----------------------------------------------------------------------------
 * Name:    sdcard.c
 * Purpose: MCBTMS570 low level SDCard functions
 * Version: V1.00
 * Note(s):
 *----------------------------------------------------------------------------
 * SDCARD-SCLK  :SPI_PIN_CLK   GPIO22
 * SDCARD-CS    :SPI_PIN_CS3   GPIO23
 * SDCARD-MOSI  :SPI_PIN_ENA   GPIO20
 * SDCARD-MISO  :SPI_PIN_CS0   GPIO21
 *----------------------------------------------------------------------------*/
#include "sdcard.h"
#include "SPI_SDCard.h"
SdCardStatus sd_card_status;
SD_CardInfo SDCardInfo;
unsigned int SPI_Speed = SPI_HIGH;
uint8_t SD_Type;
/* Local variables */

unsigned char SD_Init(void)
{
    unsigned char time,temp,i;
    unsigned char buff[6];
    SPI_Speed = SPI_LOW;
    Set_SPI_CS_Low();
    delay_ms(5);
    for (i = 0; i < 10; i++)
    {
        SPI_ReadWriteByte(0x00ff);
    }
    time=0;
    do
    {
        temp=SD_Write_Cmd(CMD0, 0, 0x95);
        time++;
        if(time>=TRY_TIME)
        {
            return(INIT_CMD1_ERROR);
        }
    }
    while(temp!=0x01);
    temp = SD_Write_Cmd(CMD8, 0x1aa, 0x87);
    if (temp == 0x01)
    {
        buff[0] = SPI_ReadWriteByte(0xFF);
        buff[1] = SPI_ReadWriteByte(0xFF);
        buff[2] = SPI_ReadWriteByte(0xFF);
        buff[3] = SPI_ReadWriteByte(0xFF);
        Set_SPI_CS_High();
        SPI_ReadWriteByte(0xFF);
        time = 0;
        do
        {
            temp = SD_Write_Cmd(CMD55, 0, 0);
            if (temp != 0x0001)
                return temp;
            temp = SD_Write_Cmd(CMD41, 0x40000000, 1);
            time++;
            if (time > 200)
                return temp;
        } while (temp != 0);
        temp = SD_Write_Cmd_NoDeassert(CMD58, 0, 0);

        if (temp != 0x0000)
            return temp;
        buff[0] = SPI_ReadWriteByte(0xFF);
        buff[1] = SPI_ReadWriteByte(0xFF);
        buff[2] = SPI_ReadWriteByte(0xFF);
        buff[3] = SPI_ReadWriteByte(0xFF);
        Set_SPI_CS_High();
        SPI_ReadWriteByte(0xFF);
        if (buff[0] & 0x40)
        {
            SD_Type = SD_TYPE_V2HC;
        }
        else
        {
            SD_Type = SD_TYPE_V2;
        }
        SPI_Speed = SPI_HIGH;
    }
    return(0);
}

unsigned char SPI_ReadWriteByte(unsigned char data)
{
    unsigned char ReceivedBit = 0x0000;
    int j;
    delay_ns(500);
    for(j=0; j<8; j++)
    {
        Set_SPI_CLK_High();
        delay_ns(SPI_Speed);
        if(data & 0x80)
        {
              Set_SPI_MOSI_High();
        }
        else
        {
             Set_SPI_MOSI_Low();
        }

        delay_ns(SPI_Speed);
        Set_SPI_CLK_Low();
        delay_ns(SPI_Speed);
        data<<=1;
        ReceivedBit<<=1;
        if(0x01==Get_SPI_MISO_Status())
        {
            ReceivedBit ++;
        }
        Set_SPI_CLK_High();
    }
    return ReceivedBit;
}


unsigned char SD_Write_Cmd(uint8_t cmd, uint32_t arg, uint8_t crc)
{
    unsigned char temp,time=0;
    Set_SPI_CS_High();
    SPI_ReadWriteByte(0xFF);
    Set_SPI_CS_Low();
    SPI_ReadWriteByte(cmd);
    SPI_ReadWriteByte((uint8_t)(arg >> 24));
    SPI_ReadWriteByte((uint8_t)(arg >> 16));
    SPI_ReadWriteByte((uint8_t)(arg >> 8));
    SPI_ReadWriteByte((uint8_t)arg);
    SPI_ReadWriteByte(crc);
    do
    {
        temp = SPI_ReadWriteByte(0xff);
        time++;
    }
    while((temp==0xff)&&(time<TRY_TIME));
    Set_SPI_CS_High();
    SPI_ReadWriteByte(0xFF);
    return(temp);
}

unsigned char SD_Write_Cmd_NoDeassert(uint8_t cmd, uint32_t arg, uint8_t crc)
{
    unsigned char temp,time=0;
    Set_SPI_CS_High();
    SPI_ReadWriteByte(0xFF);
    Set_SPI_CS_Low();
    SPI_ReadWriteByte(cmd);
    SPI_ReadWriteByte((uint8_t)(arg >> 24));
    SPI_ReadWriteByte((uint8_t)(arg >> 16));
    SPI_ReadWriteByte((uint8_t)(arg >> 8));
    SPI_ReadWriteByte((uint8_t)arg);
    SPI_ReadWriteByte(crc);
    do
    {
        temp = SPI_ReadWriteByte(0xff);
        time++;
    }
    while((temp==0xff)&&(time<TRY_TIME));
    return(temp);
}

unsigned char SD_Reset(void)
{
    unsigned char time,temp,i;
    SPI_Speed = SPI_LOW;
    Set_SPI_CS_High();
    for(i=0;i<10;i++)
    {
        SPI_ReadWriteByte(0xff);
    }
    Set_SPI_CS_Low();
    time=0;
    do
    {
        temp = SD_Write_Cmd(CMD0, 0, 0x95);
        time++;
        if(time>=30)
        {
            return(INIT_CMD0_ERROR);
        }
    }
    while(temp!=0x01);
    Set_SPI_CS_High();
    SPI_ReadWriteByte(0xff);
    SPI_Speed = SPI_HIGH;
    return 0;
}


/*
 * Write one sector operation
 * sector:  sector-ID
 * data:    512Bytes
 */
unsigned char SD_WriteSingleBlock(uint32_t sector, const uint8_t* data)
{
    uint8_t r1;
    uint16_t i,retry;
    SPI_Speed = SPI_HIGH;
    if (SD_Type != SD_TYPE_V2HC)
    {
        sector = sector << 9;
    }
    r1 = SD_Write_Cmd(CMD24, sector, 0x00);
    if (r1 != 0x00)
    {
        return r1;
    }
    Set_SPI_CS_Low();
    SPI_ReadWriteByte(0xff);
    SPI_ReadWriteByte(0xff);
    SPI_ReadWriteByte(0xff);
    SPI_ReadWriteByte(0xFE);
    for (i = 0; i < 512; i++)
    {
        SPI_ReadWriteByte(*data++);
    }
    SPI_ReadWriteByte(0xff);
    SPI_ReadWriteByte(0xff);
    r1 = SPI_ReadWriteByte(0xff);
    if ((r1 & 0x1F) != 0x05)
    {
        Set_SPI_CS_High();
        return r1;
    }
    retry = 0;
    while (!SPI_ReadWriteByte(0xff))
    {
        retry++;
        if (retry > 65534)
        {
            Set_SPI_CS_High();
            return 1;
        }
    }
    Set_SPI_CS_High();
    SPI_ReadWriteByte(0xff);
    return 0;
}

/*
 * Write multi sectors operation
 * sector:  sector-ID
 * data:    n*512Bytes
 * count:   nums
 */
unsigned char SD_WriteMultiBlock(uint32_t sector, const uint8_t* data, uint8_t count)
{
    uint8_t r1;
    uint16_t i;
    SPI_Speed = SPI_HIGH;
    if (SD_Type != SD_TYPE_V2HC)
    {
        sector = sector << 9;
    }
    if (SD_Type != SD_TYPE_MMC)
    {
        r1 = SD_Write_Cmd(CMD23, count, 0x01);
    }
    r1 = SD_Write_Cmd(CMD25, sector, 0x01);
    if (r1 != 0x00)
    {
        return r1;
    }
    Set_SPI_CS_Low();
    SPI_ReadWriteByte(0xff);
    SPI_ReadWriteByte(0xff);
    SPI_ReadWriteByte(0xff);
    do
    {
        SPI_ReadWriteByte(0xFC);
        for (i = 0; i < 512; i++)
        {
            SPI_ReadWriteByte(*data++);
        }
        SPI_ReadWriteByte(0xff);
        SPI_ReadWriteByte(0xff);
        r1 = SPI_ReadWriteByte(0xff);
        if ((r1 & 0x1F) != 0x05)
        {
            Set_SPI_CS_High();
            return r1;
        }
        if (SD_WaitReady() == 1)
        {
            Set_SPI_CS_High();
            return 1;
        }
    }
    while (--count);

    SPI_ReadWriteByte(0xFD);

    if (SD_WaitReady())
    {
        Set_SPI_CS_High();
        return 1;
    }
    Set_SPI_CS_High();
    SPI_ReadWriteByte(0xff);
    return 0;
}

uint8_t SD_WaitReady(void)
{
    uint8_t r1;
    uint16_t retry = 0;
    do
    {
        r1 = SPI_ReadWriteByte(0xFF);
        retry++;
        if (retry == 0xfffe)
            return 1;
    } while (r1 != 0xFF);
    return 0;
}

/*
 * Read one sector operation
 * sector:  sector-ID
 * buffer:  512Bytes
 */
unsigned char SD_ReadSingleBlock(uint32_t sector, uint8_t* buffer)
{
    uint8_t r1;
    SPI_Speed = SPI_HIGH;
    if (SD_Type != SD_TYPE_V2HC)
    {
        sector = sector << 9;
    }
    r1 = SD_Write_Cmd(CMD17, sector, 1);
    if (r1 != 0x00)
        return r1;
    r1 = SD_ReceiveData(buffer, 512, RELEASE);  //Each sector is 512 bytes
    if (r1 != 0)
        return r1;   //Error Read
    else
        return 0;    //OK
}

/*
 * Read multi sectors operation
 * sector:  sector-ID
 * buffer:  n*512Bytes
 * count:   nums
 */
uint8_t SD_ReadMultiBlock(uint32_t sector, uint8_t* buffer, uint8_t count)
{
    uint8_t r1;
    SPI_Speed = SPI_HIGH;
    if (SD_Type != SD_TYPE_V2HC)
    {
        sector = sector << 9;
    }
    r1 = SD_Write_Cmd(CMD18, sector, 1);
    if (r1 != 0x00)
        return r1;
    do
    {
        if (SD_ReceiveData(buffer, 512, UN_RELEASE) != 0x00)
        {
            break;
        }
        buffer += 512;
    } while (--count);
    SD_Write_Cmd(CMD12, 0, 1);
    Set_SPI_CS_High();
    SPI_ReadWriteByte(0xFF);
    if (count != 0)
        return count;
    else
        return 0;
}


uint8_t SD_ReceiveData(uint8_t* data, uint16_t len, uint8_t release)
{
    uint16_t retry;
    uint8_t r1;
    Set_SPI_CS_Low();
    retry = 0;
    do
    {
        r1 = SPI_ReadWriteByte(0xFF);
        retry++;
        if (retry > 4000)
        {
            Set_SPI_CS_High();
            return 1;
        }
    }
    while (r1 != 0xFE);
    while (len--)
    {
        *data = SPI_ReadWriteByte(0xFF);
        data++;
    }
    SPI_ReadWriteByte(0xFF);
    SPI_ReadWriteByte(0xFF);
    if (release == RELEASE)
    {
        Set_SPI_CS_High();
        SPI_ReadWriteByte(0xFF);
    }

    return 0;
}

uint8_t SD_GetCID(uint8_t* cid_data)
{
    uint8_t r1;
    r1 = SD_Write_Cmd(CMD10, 0, 0xFF);
    if (r1 != 0x00)
        return r1;
    SD_ReceiveData(cid_data, 16, RELEASE);
    return 0;
}


uint32_t SD_GetCapacity(void)
{
    uint8_t csd[16];
    uint32_t Capacity;
    uint8_t r1;
    uint16_t i;
    uint16_t temp;
    if (SD_GetCSD(csd) != 0)
        return 0;
    if ((csd[0] & 0xC0) == 0x40)
    {
        Capacity = ((uint32_t)csd[8]) << 8;
        Capacity += (uint32_t)csd[9] + 1;
        Capacity = (Capacity) * 1024;
        Capacity *= 512;
    }
    else
    {
        i = csd[6] & 0x03;
        i <<= 8;
        i += csd[7];
        i <<= 2;
        i += ((csd[8] & 0xc0) >> 6);
        r1 = csd[9] & 0x03;
        r1 <<= 1;
        r1 += ((csd[10] & 0x80) >> 7);
        r1 += 2;
        temp = 1;
        while (r1)
        {
            temp *= 2;
            r1--;
        }
        Capacity = ((uint32_t)(i + 1)) * ((uint32_t)temp);
        i = csd[5] & 0x0f;
        temp = 1;
        while (i)
        {
            temp *= 2;
            i--;
        }
        Capacity *= (uint32_t)temp;
    }
    return (uint32_t)Capacity;
}


uint8_t SD_GetCSD(uint8_t *csd_data)
{
    uint8_t response;
    response = SD_Write_Cmd(CMD9, 0, 0xFF);
    if(response != 0x00)
    {
        return response;
    }
    SD_ReceiveData(csd_data, 16, RELEASE);
    return 0;
}

