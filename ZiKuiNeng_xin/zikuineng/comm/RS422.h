/*
 * RS422.h
 *
 *  Created on: 2021Äê4ÔÂ21ÈÕ
 *      Author: Lee
 */

#ifndef COMM_RS422_H_
#define COMM_RS422_H_
#define USART_QUEUEMAX 1024
#define SCI_LSPCLK 20000
typedef struct
{
  /*Receive data byte queue */
  uint8_t data[USART_QUEUEMAX];
  uint16_t head;
  uint16_t tail;
  /*Unframe buffer */
  uint8_t frame_temp[50];
  uint8_t frame_len;
  uint16_t len_err;
} SCI_RecvQueue;
extern SCI_RecvQueue RS422_revice;
extern uint8_t RS422_Comm;
void RS422_Int(uint32_t Baud);
void RS422_Send_Byte(uint8_t senddata);
void RS422_Send_String(uint8_t * senddata,uint8_t length);
uint8_t SCI_RecvQueueIn(SCI_RecvQueue *q, uint8_t data);
uint8_t SCI_RecvQueueOut(SCI_RecvQueue *q);
uint8_t SCI_RecvQueueEmpty(SCI_RecvQueue *q);
void Rs422_Message_Process(uint8_t * data,uint8_t len);
uint8_t GetFrameFromQueue(SCI_RecvQueue *q);
void FrameProcess(SCI_RecvQueue *q);
uint8_t CRC_Get_Cumulative_Sum(uint8_t * buff,uint8_t len);
void RS422_Send_Data();
__interrupt void ScibRxInpur(void);
#endif /* COMM_RS422_H_ */
