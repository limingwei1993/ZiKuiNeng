/*
 * GPIO.c
 *
 *  Created on: 2021??4??20??
 *      Author: Lee
 */
#include "DSP2833x_Device.h"     /* DSP2833x Headerfile Include File*/
#include "include.h"
__interrupt void Time0_Interrupt_Handler(void);
__interrupt void ScibRxInpur(void);
/*******************************************************************************
Function:       // GPIO_int
Description:    // Configuration the GPIO
Input:          // none
Output:         // none
*******************************************************************************/
void GIOP_Int(void)
{
        EALLOW;
        /*pwm*/
        GpioCtrlRegs.GPAPUD.bit.GPIO0 = 0;    /* Enable pull-up on GPIO0 (EPWM1A) */
        GpioCtrlRegs.GPAPUD.bit.GPIO2 = 0;    /* Enable pull-up on GPIO2 (EPWM2A) */
        GpioCtrlRegs.GPAPUD.bit.GPIO4 = 0;    /* Enable pull-up on GPIO4 (EPWM3A) */
        GpioCtrlRegs.GPAPUD.bit.GPIO6 = 0;    /* Enable pull-up on GPIO6 (EPWM4A) */
        GpioCtrlRegs.GPAPUD.bit.GPIO8 = 0;    /* Enable pull-up on GPIO8 (EPWM5A) */
        GpioCtrlRegs.GPAPUD.bit.GPIO10 = 0;    /* Enable pull-up on GPIO10 (EPWM6A) */

        GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 1;   /* Configure GPIO0 as EPWM1A */
        GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 1;   /* Configure GPIO2 as EPWM2A */
        GpioCtrlRegs.GPAMUX1.bit.GPIO4 = 1;   /* Configure GPIO4 as EPWM3A */
        GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 1;   /* Configure GPIO6 as EPWM4A */
        GpioCtrlRegs.GPAMUX1.bit.GPIO8 = 1;   /* Configure GPIO8 as EPWM5A */
        GpioCtrlRegs.GPAMUX1.bit.GPIO10 = 1;   /* Configure GPIO10 as EPWM6A */
        /*RS422*/
        GpioCtrlRegs.GPAPUD.bit.GPIO11 = 0;    // Enable pull-up for GPIO11 (SCIRXDA)
        GpioCtrlRegs.GPAPUD.bit.GPIO9 = 0;       // Enable pull-up for GPIO9 (SCITXDA)
        GpioCtrlRegs.GPAQSEL1.bit.GPIO11 = 3;  // Asynch input GPIO11 (SCIRXDA)
        GpioCtrlRegs.GPAMUX1.bit.GPIO11 = 2;   // Configure GPIO11 for SCIRXDA operation
        GpioCtrlRegs.GPAMUX1.bit.GPIO9 = 2;   // Configure GPIO9 for SCITXDA operation
        /*ADS1258*/
        GpioCtrlRegs.GPAPUD.bit.GPIO15 = 0;   /* Enable pullup on GPIO15  (SPISTART)*/
        GpioCtrlRegs.GPAMUX1.bit.GPIO15 = 0;  /* GPIO15 = GPIO15 */
        GpioCtrlRegs.GPADIR.bit.GPIO15 = 1;   /* GPIO15 = output*/

        GpioCtrlRegs.GPBPUD.bit.GPIO49 = 0;   /* Enable pullup on GPIO49  (DRDY)*/
        GpioCtrlRegs.GPBMUX2.bit.GPIO49 = 0;  /* GPIO49 = GPIO49 */
        GpioCtrlRegs.GPBDIR.bit.GPIO49 = 0;   /* GPIO49 = input*/

        GpioCtrlRegs.GPAPUD.bit.GPIO16 = 0;   //Enable pull-up on GPIO16 (SPISIMOA)
        GpioCtrlRegs.GPAPUD.bit.GPIO17 = 0;   //Enable pull-up on GPIO17 (SPISOMIA)
        GpioCtrlRegs.GPAPUD.bit.GPIO18 = 0;   //Enable pull-up on GPIO18 (SPICLKA)
        GpioCtrlRegs.GPAPUD.bit.GPIO19 = 0;   //Enable pull-up on GPIO19 (SPISTEA)
#if (SPI_MODE == HARDWARE_SPI)
        GpioCtrlRegs.GPAQSEL2.bit.GPIO16 = 3; // Asynch input GPIO16 (SPISIMOA)
        GpioCtrlRegs.GPAQSEL2.bit.GPIO17 = 3; // Asynch input GPIO17 (SPISOMIA)
        GpioCtrlRegs.GPAQSEL2.bit.GPIO18 = 3; // Asynch input GPIO18 (SPICLKA)
        GpioCtrlRegs.GPAQSEL2.bit.GPIO19 = 3; // Asynch input GPIO19 (SPISTEA)

        GpioCtrlRegs.GPAMUX2.bit.GPIO16 = 1; // Configure GPIO16 as SPISIMOA
        GpioCtrlRegs.GPAMUX2.bit.GPIO17 = 1; // Configure GPIO17 as SPISOMIA
        GpioCtrlRegs.GPAMUX2.bit.GPIO18 = 1; // Configure GPIO18 as SPICLKA
        GpioCtrlRegs.GPAMUX2.bit.GPIO19 = 1; // Configure GPIO19 as SPISTEA
#else

        GpioCtrlRegs.GPAMUX2.bit.GPIO16 = 0; // Configure GPIO16 as GPIO16
        GpioCtrlRegs.GPAMUX2.bit.GPIO17 = 0; // Configure GPIO17 as GPIO17
        GpioCtrlRegs.GPAMUX2.bit.GPIO18 = 0; // Configure GPIO18 as GPIO18
        GpioCtrlRegs.GPAMUX2.bit.GPIO19 = 0; // Configure GPIO19 as GPIO19

        GpioCtrlRegs.GPADIR.bit.GPIO16 = 1; // GPIO16 = output
        GpioCtrlRegs.GPADIR.bit.GPIO17 = 0; // GPIO17 = input
        GpioCtrlRegs.GPADIR.bit.GPIO18 = 1; // GPIO18 = output
        GpioCtrlRegs.GPADIR.bit.GPIO19 = 1; // GPIO19 = output
#endif
        /*SD*/
        GpioCtrlRegs.GPCPUD.bit.GPIO74 = 0;   //Enable pull-up on GPIO74 (SPISIMOA)
        GpioCtrlRegs.GPCPUD.bit.GPIO75 = 0;   //Enable pull-up on GPIO75 (SPISOMIA)
        GpioCtrlRegs.GPCPUD.bit.GPIO73 = 0;   //Enable pull-up on GPIO73 (SPICLKA)
        GpioCtrlRegs.GPCPUD.bit.GPIO72 = 0;   //Enable pull-up on GPIO72 (SPISTEA)

        GpioCtrlRegs.GPCMUX1.bit.GPIO74 = 0; // Configure GPIO74 as GPIO74
        GpioCtrlRegs.GPCMUX1.bit.GPIO75 = 0; // Configure GPIO75 as GPIO75
        GpioCtrlRegs.GPCMUX1.bit.GPIO73 = 0; // Configure GPIO73 as GPIO73
        GpioCtrlRegs.GPCMUX1.bit.GPIO72 = 0; // Configure GPIO72 as GPIO72

        GpioCtrlRegs.GPCDIR.bit.GPIO74 = 1;   // GPIO74 = output
        GpioCtrlRegs.GPCDIR.bit.GPIO75 = 0;   // GPIO75 = input
        GpioCtrlRegs.GPCDIR.bit.GPIO73 = 1;   // GPIO73 = output
        GpioCtrlRegs.GPCDIR.bit.GPIO72 = 1;   // GPIO72 = output

        /*EEPROM*/
        GpioCtrlRegs.GPBPUD.bit.GPIO32 = 0;   /* Enable pullup on GPIO32  (SDA)*/
        GpioCtrlRegs.GPBMUX1.bit.GPIO32 = 0;  /* GPIO32 = GPIO32 */
        GpioCtrlRegs.GPBDIR.bit.GPIO32 = 1;   /* GPIO32 = output*/

        GpioCtrlRegs.GPBPUD.bit.GPIO33 = 0;   /* Enable pullup on GPIO33  (SCL)*/
        GpioCtrlRegs.GPBMUX1.bit.GPIO33 = 0;  /* GPIO33 = GPIO33 */
        GpioCtrlRegs.GPBDIR.bit.GPIO33 = 1;   /* GPIO33 = output*/

        /*Dial Code*/
        GpioCtrlRegs.GPCPUD.bit.GPIO76 = 0;   //Enable pull-up on GPIO76
        GpioCtrlRegs.GPCPUD.bit.GPIO77 = 0;   //Enable pull-up on GPIO77
        GpioCtrlRegs.GPCPUD.bit.GPIO78 = 0;   //Enable pull-up on GPIO78
        GpioCtrlRegs.GPCPUD.bit.GPIO79 = 0;   //Enable pull-up on GPIO79

        GpioCtrlRegs.GPCMUX1.bit.GPIO76 = 0; // Configure GPIO76 as GPIO
        GpioCtrlRegs.GPCMUX1.bit.GPIO77 = 0; // Configure GPIO77 as GPIO
        GpioCtrlRegs.GPCMUX1.bit.GPIO78 = 0; // Configure GPIO78 as GPIO
        GpioCtrlRegs.GPCMUX1.bit.GPIO79 = 0; // Configure GPIO79 as GPIO

        GpioCtrlRegs.GPCDIR.bit.GPIO76 = 0; // GPIO76 = input
        GpioCtrlRegs.GPCDIR.bit.GPIO77 = 0; // GPIO77 = input
        GpioCtrlRegs.GPCDIR.bit.GPIO78 = 0; // GPIO78 = input
        GpioCtrlRegs.GPCDIR.bit.GPIO79 = 0; // GPIO79 = input
        EDIS;

}


/*******************************************************************************
Function:       // Configuration_Interrupt
Description:    // Configuration the interrupt(time0 sci_revice)
Input:          // none
Output:         // none
*******************************************************************************/
void Configuration_Interrupt(void)
{
        EALLOW; /*Open protection*/

        PieVectTable.TINT0 = &Time0_Interrupt_Handler; /*time0 interrupt handler*/
        PieVectTable.SCIRXINTB = &ScibRxInpur; /*scib interrupt handler*/

        EDIS; /*close protection*/



        CpuTimer0Regs.TCR.all = 0x4000; /*time0 interrupt enable*/
        IER |= M_INT1;
        PieCtrlRegs.PIEIER1.bit.INTx7 = 1;

        PieCtrlRegs.PIECTRL.bit.ENPIE = 1;   // Enable the PIE block
        PieCtrlRegs.PIEIER9.bit.INTx3=1;     // PIE Group 9, INT3
        IER |= M_INT9;
}

/*******************************************************************************
Function:       // Get_Dial_Code
Description:    // Get Dial Code
Input:          // none
Output:         // dial code number
*******************************************************************************/
uint8_t Get_Dial_Code(void)
{
    uint8_t num=0;
    if((GpioDataRegs.GPCDAT.bit.GPIO76 & 0xff)==0)
        num |= 0x08;
    if((GpioDataRegs.GPCDAT.bit.GPIO77 & 0xff)==0)
        num |= 0x04;
    if((GpioDataRegs.GPCDAT.bit.GPIO78 & 0xff)==0)
        num |= 0x02;
    if((GpioDataRegs.GPCDAT.bit.GPIO79 & 0xff)==0)
        num |= 0x01;
    return num;
}
