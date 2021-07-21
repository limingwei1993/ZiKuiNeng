/*
 * EEPROM.h
 *
 *  Created on: 2021Äê4ÔÂ22ÈÕ
 *      Author: Lee
 */

#ifndef COMM_EEPROM_H_
#define COMM_EEPROM_H_

void Set_SDA_Pin_Input(void);
void Set_SDA_Pin_Output(void);
void set_IIC_SDA_High(void);
void set_IIC_SDA_Low(void);
void set_IIC_SCL_High(void);
void set_IIC_SCL_Low(void);
uint8_t Get_SDA_status(void);
void IIC_Start(void);
void IIC_Stop(void);
uint8_t IIC_Wait_Ack(void);
void IIC_Ack(void);
void IIC_NAck(void);
void IIC_Send_Byte(uint8_t senddata);
uint8_t IIC_Read_Byte(void);
uint8_t AT24C512_ReadOneByte(uint16_t readaddr);
void AT24C512_WriteOneByte(uint16_t writeaddr,uint8_t writedata);
void AT24C512_WritelenByte(uint16_t writeaddr,uint8_t * writedata,uint8_t len);
void AT24C512_ReadlenByte(uint16_t readaddr,uint8_t * readdata,uint8_t len);
void AT24C512_WriteString(uint16_t writeaddr,uint8_t * writedata,uint8_t len);
void AT24C512_ReadString(uint16_t readaddr,uint8_t * revicedata,uint8_t readlen);

#endif /* COMM_EEPROM_H_ */
