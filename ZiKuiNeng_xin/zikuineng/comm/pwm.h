/*
 * pwm.h
 *
 *  Created on: 2021Äê4ÔÂ20ÈÕ
 *      Author: Lee
 */

#ifndef COMM_PWM_H_
#define COMM_PWM_H_
typedef enum MOTOR_PIN
{
    MOTOR1_BRK =0,
    MOTOR1_DIR =1,
    MOTOR1_nFUT=2,
    MOTOR2_BRK =3,
    MOTOR2_DIR =4,
    MOTOR2_nFUT=5,
}motor_pinx;
#define MOTOR1      1
#define MOTOR2      2
void Pwm1_Switch1_Int(void);
void Pwm2_Switch2_Int(void);
void Pwm3_Switch3_Int(void);
void Pwm4_Switch4_Int(void);
void Pwm5_Motor1_Int(void);
void Pwm6_Motor2_Int(void);
void set_switch1_status(uint8_t status);
void set_switch2_status(uint8_t status);
void set_switch3_status(uint8_t status);
void set_switch4_status(uint8_t status);
void set_motor1_status(uint8_t status);
void set_motor2_status(uint8_t status);
void Set_Motor_pin(motor_pinx pinx,uint8_t status);
uint8_t Get_nFUT_Status(motor_pinx pinx);
#endif /* COMM_PWM_H_ */
