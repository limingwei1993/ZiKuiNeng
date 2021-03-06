/*
 * RS422.c
 *
 *  Created on: 2021年4月21日
 *      Author: Lee
 */

#include "include.h"
#define REVICE_MODE  0
SCI_RecvQueue RS422_revice; /*Save the data received by RS422*/
uint8_t RS422_Comm=5;
uint8_t Brake_State=1;
extern uint8_t test_7;
/**
  * @function SciaRxIsr
  * @brief    This function handles SCIB Handler.
  * @param    none
  * @retval   none
  */
uint8_t buff[100]={0}; /*test code*/
uint8_t len=0; /*test code*/

__interrupt void ScibRxInpur(void)
{
    Uint16 i;
    uint8_t rev_len=0;
    uint8_t revice_data=0;
    static uint8_t revice_buff[24]={0};
    static uint8_t revice_len=0;
    rev_len=(ScibRegs.SCIFFRX.bit.RXFFST & 0xff);
#if REVICE_MODE==1
    for(i=0;i<rev_len;i++)
    {
        revice_data=(ScibRegs.SCIRXBUF.bit.RXDT & 0xff);   // Read data
        SCI_RecvQueueIn(&RS422_revice, revice_data);
    }
#else

    for(i=0;i<rev_len;i++)
    {
           revice_data=(uint8_t)(ScibRegs.SCIRXBUF.bit.RXDT & 0xff);   /* Read data*/
           buff[len++]=revice_data;
           if(revice_len==0 && revice_data==0xAA) /*测试使用，由于测试改成了0xAA。正式使用改为0xEB*/
           {
               revice_buff[0]=0xeb;
               revice_len++;
           }
           else if(revice_len==1 && revice_data==0x55)/*测试使用，由于测试改成了0x55。正式使用改为0x90*/
           {
               revice_buff[1]=0x90;
               revice_len++;
           }
           else if(revice_len>1)
           {
               revice_buff[revice_len]=revice_data;
               revice_len++;
               if(revice_len>=5)/*测试使用，由于测试改成了>=50。正式使用改为>=11*/
               {
                  /* if(CRC_Get_Cumulative_Sum(revice_buff, 10)== revice_buff[10])
                   {

                       Rs422_Message_Process(revice_buff,revice_len);
                       RS422_Comm=5;
                       revice_len=0;
                   }
                   else*/ /*由于测试此处被屏蔽了，正式使用，打开屏蔽*/
                    revice_len=0;
                    if(revice_buff[3]==0x55 && revice_buff[4]==0xAA)/*测试使用，正式使用时，删除此处*/
                    {
                        Rs422_revice=1;
                        Rs422_revice_type=revice_buff[2];
                    }
               }
            }
           else
               revice_len=0;
     }

#endif
    ScibRegs.SCIFFRX.bit.RXFFOVRCLR=1;      // Clear Overflow flag
    ScibRegs.SCIFFRX.bit.RXFFINTCLR=1;      // Clear Interrupt flag

    PieCtrlRegs.PIEACK.all|=0x100;          // Issue PIE ack
}
/**
  * @function RS422_Int
  * @brief    Configure the scib
  * @param    Baud: Baud rate  2400--0X7A0h; 4800--0X3D0h; 9600--0X1e7h; 19200--0Xf3h; 38400--0X790h;
  * @retval   None
  */
void RS422_Int(uint32_t Baud)
{
       uint16_t BRR=0;
       uint32_t num=0;
       num=46875000/Baud;  /*if External crystal is 30MHZ */
//    num=25000000/Baud;      /*if External crystal is 16MHZ */
       num=num/10+((num%10)>=5?1:0);
       BRR= num-1;
      //set SCIA register
      ScibRegs.SCICCR.all =0x0067;   // 1 stop bit,  No loopback
                                     // Even parity,8 char bits,
                                     // async mode, idle-line protocol
      ScibRegs.SCICTL1.all =0x0003;  // enable TX, RX, internal SCICLK,
                                     // Disable RX ERR, SLEEP, TXWAKE
      ScibRegs.SCICTL2.bit.TXINTENA =1;
      ScibRegs.SCICTL2.bit.RXBKINTENA =1;
       //set Baud BRR
      ScibRegs.SCIHBAUD    = (BRR>>8);  // 9600 baud @LSPCLK = 37.5MHz.
      ScibRegs.SCILBAUD    = (BRR&0x00ff);

      ScibRegs.SCIFFTX.all=0xC021;
      ScibRegs.SCIFFRX.all=0x0021;
      ScibRegs.SCIFFCT.all=0x00;
      ScibRegs.SCICTL1.all =0x0023;     // Relinquish SCI from Reset
      ScibRegs.SCIFFRX.bit.RXFIFORESET=1;
      ScibRegs.SCIFFTX.bit.TXFIFOXRESET=1;
}

/**
  * @function RS422_Send_Byte
  * @brief    send byte by scib
  * @param    senddata : send data
  * @retval   none
  */
void RS422_Send_Byte(uint8_t senddata)
{
    uint16_t send_data=0;
    send_data=(senddata & 0x00FF);
    while (ScibRegs.SCIFFTX.bit.TXFFST != 0) ;
    ScibRegs.SCITXBUF=send_data;
}

/**
  * @function RS422_Send_String
  * @brief    send string by scib
  * @param    senddata : send data
  * @retval   none
  */
void RS422_Send_String(uint8_t * senddata,uint8_t length)
{
    uint8_t i=0;
   for(i=0;i<length;i++)
    {
       RS422_Send_Byte(senddata[i]);
    }
}

/**
  * @function SCI_RecvQueueIn
  * @brief    Queue in
  * @param    *q : queue point
              data : data
  * @retval   0:queue full ；1，queue not full
  */
uint8_t SCI_RecvQueueIn(SCI_RecvQueue *q, uint8_t data)
{
  if ((q->tail + 1) % USART_QUEUEMAX == q->head)
  {
    /*The queue is full, and the data at the head of the column is discarded. */
    q->data[q->tail] = data;
    q->head = (q->head + 1) % USART_QUEUEMAX;
    q->tail = (q->tail + 1) % USART_QUEUEMAX;
    return 0;
  }
  else
  {
    q->data[q->tail] = data;
    q->tail = (q->tail + 1) % USART_QUEUEMAX;
    return 1;
  }
}
/**
  * @function SCI_RecvQueueOut
  * @brief    Queue out
  * @param    *q:queue point
  * @retval   the out data
  */
uint8_t SCI_RecvQueueOut(SCI_RecvQueue *q)
{
  uint8_t data = 0;
  data = q->data[q->head];
  q->head = (q->head + 1) % USART_QUEUEMAX;
  return data;
}
/**
  * @function SCI_RecvQueueEmpty
  * @brief    Ckeck if the queue is emtpy
  * @param    *q:queue point
  * @retval   1: queue is empty;0: queue is not empty
  */
uint8_t SCI_RecvQueueEmpty(SCI_RecvQueue *q)
{
  return (q->head == q->tail);
}
/**
  * @function CRC_Get_Cumulative_Sum
  * @brief    Get Cumulative Sum
  * @param    * buff:queue point
  *           len:data len
  * @retval  : Check result
  */
uint8_t CRC_Get_Cumulative_Sum(uint8_t * buff,uint8_t len)
{
    uint8_t result=0;
    uint8_t i=0;
    for(i=0;i<len;i++)
    {
        result+=buff[i];
    }
    return result;
}
/**
  * @function FrameProcess
  * @brief    Process the data received by RS422
  * @param    * q:queue point
  * @retval  : none
  */
void FrameProcess(SCI_RecvQueue *q)
{
  uint8_t res = 0;
  res = GetFrameFromQueue(q);
  if(res==8)
  {
      RS422_Comm=5;
      Rs422_Message_Process(q->frame_temp,8);
  }
}
/**
  * @function GetFrameFromQueue
  * @brief    Get Frame From Queue
  * @param    * q:queue point
  * @retval  : Check result;0--no frame; other--frame data len
  */
uint8_t GetFrameFromQueue(SCI_RecvQueue *q)
{
  uint8_t Rx_data = 0;
  uint8_t res = 0;
  while (!SCI_RecvQueueEmpty(q) && !res)
  {
    Rx_data = SCI_RecvQueueOut(q);
    if (q->frame_len == 0 && Rx_data == 0xeb)
    {
      q->frame_temp[q->frame_len] = Rx_data;
      q->frame_len++;
    }
    else if (q->frame_len == 1 && Rx_data == 0x90)
    {
        q->frame_temp[q->frame_len] = Rx_data;
        q->frame_len++;
    }
    else if (q->frame_len > 1)
    {
      q->frame_temp[q->frame_len++] = Rx_data;
      if (q->frame_len >= 11)
      {
        if (q->frame_temp[10] == CRC_Get_Cumulative_Sum(q->frame_temp, 10)) /*crc校验通过*/
        {
          res = q->frame_len;
        }
        q->frame_len = 0;
      }
    }
    else
    {
        q->frame_temp[0] = 0;
        q->frame_len=0;
    }
  }
  return res;
}
/**
  * @function Rs422_Message_Process
  * @brief    process rs422 message
  * @param    * data: data point
  *           len:data len
  * @retval  : none
  */
void Rs422_Message_Process(uint8_t * data,uint8_t len)
{

}
/**
  * @function RS422_Send_Data
  * @brief    Report RS422 data regularly
  * @param    none
  * @retval   none
  */
void RS422_Send_Data(void)
{
    static uint8_t index=0;
    uint8_t send_buff[20]={0};
    uint8_t statue_com=0;
    uint8_t send_len=0;
    send_buff[send_len++]=0xEB;  //EB
    send_buff[send_len++]=0x90;
    send_buff[send_len++]=0x0a;
    send_buff[send_len++]=index++;
    send_buff[send_len++]=(uint8_t)(((ADC_CURRENT_mA.signal_1_pressure + ADC_CURRENT_mA.signal_2_pressure + ADC_CURRENT_mA.signal_3_pressure)/3)/0.079);
    send_buff[send_len++]=(uint8_t)(((ADC_CURRENT_mA.signa2_1_pressure + ADC_CURRENT_mA.signa2_2_pressure + ADC_CURRENT_mA.signa2_3_pressure)/3)/0.079);
    if(RS422_Comm>0)
      statue_com |=0x01;
    if(Brake_State==1)
          statue_com |=0x02;
    send_buff[send_len++]=statue_com;
    send_buff[send_len++]=0;
    send_buff[send_len++]=0;
    send_buff[send_len]=CRC_Get_Cumulative_Sum(send_buff,send_len);
    send_len++;
    RS422_Send_String(send_buff,send_len);
}
