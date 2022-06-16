/*
 * pwm.c
 *
 *  Created on: 2021��4��20��
 *      Author: Lee
 */
#include "DSP2833x_Device.h"
#include "DSP2833x_Examples.h"
#include "include.h"
/*if External crystal is 16MHZ PWMx_TBPRD=4000;if External crystal is 30MHZ PWMx_TBPRD=7500;*/
#define PWM1_TBPRD 7500 /*pwm1 frequency parameter;*/
#define PWM2_TBPRD 7500 /*pwm2 frequency parameter;*/
#define PWM3_TBPRD 7500 /*pwm3 frequency parameter;*/
#define PWM4_TBPRD 7500 /*pwm4 frequency parameter;*/
#define PWM5_TBPRD 7500 /*pwm5 frequency parameter;*/
#define PWM6_TBPRD 7500 /*pwm6 frequency parameter;*/
/*******************************************************************************
Function:       // Pwm1_Switch1_Int
Description:    // Configuration the pwm1 to switch 1
Input:          // none
Output:         // none
*******************************************************************************/
void Pwm1_Switch1_Int(void)
{
    EPwm1Regs.TBPRD =PWM1_TBPRD;                        /* sets the PWM frequency*/
    EPwm1Regs.CMPA.half.CMPA = PWM1_TBPRD;               /* Setup compare *//*ռ�ձȣ�����PWM1_TBPRDΪ0%������0Ϊ100%*/
    EPwm1Regs.TBPHS.half.TBPHS= 0;
    EPwm1Regs.TBCTR = 0x0000;                      /* Clear counter*/
    EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP; /* Count up*/
    EPwm1Regs.TBCTL.bit.PHSEN = TB_DISABLE;        /* Disable phase loading*/
    EPwm1Regs.TBCTL.bit.PRDLD = TB_SHADOW;
    EPwm1Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_DISABLE;
    EPwm1Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;    /*Load registers every ZERO*/
    EPwm1Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;    /*Load registers every ZERO*/
    EPwm1Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
    EPwm1Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;
    EPwm1Regs.AQCTLA.bit.PRD = AQ_CLEAR;
    EPwm1Regs.AQCTLA.bit.CAU = AQ_SET;

}
/*******************************************************************************
Function:       // Pwm2_Switch2_Int
Description:    // Configuration the pwm2 to switch 2
Input:          // none
Output:         // none
*******************************************************************************/
void Pwm2_Switch2_Int(void)
{
       EPwm2Regs.TBPRD =PWM2_TBPRD;                        /* sets the PWM frequency*/
       EPwm2Regs.CMPA.half.CMPA = PWM2_TBPRD;               /* Setup compare *//*ռ�ձȣ�����PWM2_TBPRDΪ0%������0Ϊ100%*/
       EPwm2Regs.TBPHS.half.TBPHS= 0;
       EPwm2Regs.TBCTR = 0x0000;                      /* Clear counter*/
       EPwm2Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP; /* Count up*/
       EPwm2Regs.TBCTL.bit.PHSEN = TB_DISABLE;        /* Disable phase loading*/
       EPwm2Regs.TBCTL.bit.PRDLD = TB_SHADOW;
       EPwm2Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_DISABLE;
       EPwm2Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;    /*Load registers every ZERO*/
       EPwm2Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;    /*Load registers every ZERO*/
       EPwm2Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
       EPwm2Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;
       EPwm2Regs.AQCTLA.bit.PRD = AQ_CLEAR;
       EPwm2Regs.AQCTLA.bit.CAU = AQ_SET;

}
/*******************************************************************************
Function:       // Pwm3_Switch3_Int
Description:    // Configuration the pwm3 to switch 3
Input:          // none
Output:         // none
*******************************************************************************/
void Pwm3_Switch3_Int(void)
{
       EPwm3Regs.TBPRD =PWM3_TBPRD;                        /* sets the PWM frequency*/
       EPwm3Regs.CMPA.half.CMPA = PWM3_TBPRD;               /* Setup compare *//*ռ�ձȣ�����PWM3_TBPRDΪ0%������0Ϊ100%*/
       EPwm3Regs.TBPHS.half.TBPHS= 0;
       EPwm3Regs.TBCTR = 0x0000;                      /* Clear counter*/
       EPwm3Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP; /* Count up*/
       EPwm3Regs.TBCTL.bit.PHSEN = TB_DISABLE;        /* Disable phase loading*/
       EPwm3Regs.TBCTL.bit.PRDLD = TB_SHADOW;
       EPwm3Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_DISABLE;
       EPwm3Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;    /*Load registers every ZERO*/
       EPwm3Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;    /*Load registers every ZERO*/
       EPwm3Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
       EPwm3Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;
       EPwm3Regs.AQCTLA.bit.PRD = AQ_CLEAR;
       EPwm3Regs.AQCTLA.bit.CAU = AQ_SET;

}
/*******************************************************************************
Function:       // Pwm4_Switch4_Int
Description:    // Configuration the pwm4 to switch 4
Input:          // none
Output:         // none
*******************************************************************************/
void Pwm4_Switch4_Int(void)
{
       EPwm4Regs.TBPRD =PWM4_TBPRD;                        /* sets the PWM frequency*/
       EPwm4Regs.CMPA.half.CMPA = PWM4_TBPRD;               /* Setup compare *//*ռ�ձȣ�����PWM4_TBPRDΪ0%������0Ϊ100%*/
       EPwm4Regs.TBPHS.half.TBPHS= 0;
       EPwm4Regs.TBCTR = 0x0000;                      /* Clear counter*/
       EPwm4Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP; /* Count up*/
       EPwm4Regs.TBCTL.bit.PHSEN = TB_DISABLE;        /* Disable phase loading*/
       EPwm4Regs.TBCTL.bit.PRDLD = TB_SHADOW;
       EPwm4Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_DISABLE;
       EPwm4Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;    /*Load registers every ZERO*/
       EPwm4Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;    /*Load registers every ZERO*/
       EPwm4Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
       EPwm4Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;
       EPwm4Regs.AQCTLA.bit.PRD = AQ_CLEAR;
       EPwm4Regs.AQCTLA.bit.CAU = AQ_SET;

}
/*******************************************************************************
Function:       // Pwm5_Motor1_Int
Description:    // Configuration the pwm5 to motor 1
Input:          // none
Output:         // none
*******************************************************************************/
void Pwm5_Motor1_Int(void)
{
       EPwm5Regs.TBPRD =PWM5_TBPRD;                        /* sets the PWM frequency*/
       EPwm5Regs.CMPA.half.CMPA = PWM5_TBPRD;               /* Setup compare *//*ռ�ձȣ�����PWM5_TBPRDΪ0%������0Ϊ100%*/
       EPwm5Regs.TBPHS.half.TBPHS= 0;
       EPwm5Regs.TBCTR = 0x0000;                      /* Clear counter*/
       EPwm5Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP; /* Count up*/
       EPwm5Regs.TBCTL.bit.PHSEN = TB_DISABLE;        /* Disable phase loading*/
       EPwm5Regs.TBCTL.bit.PRDLD = TB_SHADOW;
       EPwm5Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_DISABLE;
       EPwm5Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;    /*Load registers every ZERO*/
       EPwm5Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;    /*Load registers every ZERO*/
       EPwm5Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
       EPwm5Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;
       EPwm5Regs.AQCTLA.bit.PRD = AQ_CLEAR;
       EPwm5Regs.AQCTLA.bit.CAU = AQ_SET;

}
/*******************************************************************************
Function:       // Pwm6_Motor2_Int
Description:    // Configuration the pwm6 to motor 2
Input:          // none
Output:         // none
*******************************************************************************/
void Pwm6_Motor2_Int(void)
{
       EPwm6Regs.TBPRD =PWM6_TBPRD;                        /* sets the PWM frequency*/
       EPwm6Regs.CMPA.half.CMPA = PWM6_TBPRD;               /* Setup compare *//*ռ�ձȣ�����PWM6_TBPRDΪ0%������0Ϊ100%*/
       EPwm6Regs.TBPHS.half.TBPHS= 0;
       EPwm6Regs.TBCTR = 0x0000;                      /* Clear counter*/
       EPwm6Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP; /* Count up*/
       EPwm6Regs.TBCTL.bit.PHSEN = TB_DISABLE;        /* Disable phase loading*/
       EPwm6Regs.TBCTL.bit.PRDLD = TB_SHADOW;
       EPwm6Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_DISABLE;
       EPwm6Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;    /*Load registers every ZERO*/
       EPwm6Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;    /*Load registers every ZERO*/
       EPwm6Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
       EPwm6Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;
       EPwm6Regs.AQCTLA.bit.PRD = AQ_CLEAR;
       EPwm6Regs.AQCTLA.bit.CAU = AQ_SET;

}
/*******************************************************************************
Function:       // set_switch1_status
Description:    // set pwm switch1 status (Duty cycle)
Input:          // status: Duty cycle
                    (status=0...100)
Output:         // none
*******************************************************************************/
void set_switch1_status(uint8_t status)
{
    uint16_t Duty_cycle=0;
    if(status<=100)
    {
        Duty_cycle=(100-status)*(PWM1_TBPRD/100);
    }
    EPwm1Regs.CMPA.half.CMPA = Duty_cycle;               /* Setup compare */
}
/*******************************************************************************
Function:       // set_switch2_status
Description:    // set pwm switch2 status (Duty cycle)
Input:          // status: Duty cycle
                    (status=0...100)
Output:         // none
*******************************************************************************/
void set_switch2_status(uint8_t status)
{
    uint16_t Duty_cycle=0;
    if(status<=100)
    {
        Duty_cycle=(100-status)*(PWM2_TBPRD/100);
    }
    EPwm2Regs.CMPA.half.CMPA = Duty_cycle;               /* Setup compare */
}
/*******************************************************************************
Function:       // set_switch3_status
Description:    // set pwm switch3 status (Duty cycle)
Input:          // status: Duty cycle
                    (status=0...100)
Output:         // none
*******************************************************************************/
void set_switch3_status(uint8_t status)
{
    uint16_t Duty_cycle=0;
    if(status<=100)
    {
        Duty_cycle=(100-status)*(PWM3_TBPRD/100);
    }
    EPwm3Regs.CMPA.half.CMPA = Duty_cycle;               /* Setup compare */
}
/*******************************************************************************
Function:       // set_switch4_status
Description:    // set pwm switch4 status (Duty cycle)
Input:          // status: Duty cycle
                    (status=0...100)
Output:         // none
*******************************************************************************/
void set_switch4_status(uint8_t status)
{
    uint16_t Duty_cycle=0;
    if(status<=100)
    {
        Duty_cycle=(100-status)*(PWM4_TBPRD/100);
    }
    EPwm4Regs.CMPA.half.CMPA = Duty_cycle;               /* Setup compare */
}
/*******************************************************************************
Function:       // set_motor1_status
Description:    // set pwm motor 1 status (Duty cycle)
Input:          // status: Duty cycle
                    (status=0...100)
Output:         // none
*******************************************************************************/
void set_motor1_status(uint8_t status)
{
    uint16_t Duty_cycle=0;
    if(status<=100)
    {
        Duty_cycle=(100-status)*(PWM5_TBPRD/100);
    }
    EPwm5Regs.CMPA.half.CMPA = Duty_cycle;               /* Setup compare */
}
/*******************************************************************************
Function:       // set_motor2_status
Description:    // set pwm motor 2 status (Duty cycle)
Input:          // status: Duty cycle
                    (status=0...100)
Output:         // none
*******************************************************************************/
void set_motor2_status(uint8_t status)
{
    uint16_t Duty_cycle=0;
    if(status<=100)
    {
        Duty_cycle=(100-status)*(PWM6_TBPRD/100);
    }
    EPwm6Regs.CMPA.half.CMPA = (Duty_cycle);               /* Setup compare */
}
