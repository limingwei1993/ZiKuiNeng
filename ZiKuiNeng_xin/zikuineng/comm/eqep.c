/*
 * eqep.c
 *
 *  Created on: 2022年6月30日
 *      Author: EDY
 */
#include "DSP2833x_EQep.h"

void Eqep_Init(void)
{
    EQep1Regs.QUPRD=800000;    // Unit Timer for 100Hz at 150MHz SYSCLKOUT

    EQep1Regs.QDECCTL.bit.QSRC=2;       // Up count mode (freq. measurement)递增计数方式
    EQep1Regs.QDECCTL.bit.XCR=1;  //上升沿计数

    EQep1Regs.QEPCTL.bit.FREE_SOFT=2;   //不受仿真影响
    EQep1Regs.QEPCTL.bit.PCRM=1;       // 最大位置时计数复位
    EQep1Regs.QEPCTL.bit.UTE=1;         // 使能单位定时器
    EQep1Regs.QEPCTL.bit.QCLM=1;        // 锁存模式，直到超时
    EQep1Regs.QPOSMAX=0xffffffff;
    EQep1Regs.QEPCTL.bit.QPEN=1;        // 位置计数器使能

    EQep1Regs.QCAPCTL.bit.UPPS=2;  // 位置事件预定标，

    EQep1Regs.QCAPCTL.bit.CCPS=7;       // 捕获定时器时钟预定 标
    EQep1Regs.QCAPCTL.bit.CEN=1;        // 使能捕获
    //
    EQep2Regs.QUPRD=800000;    // Unit Timer for 100Hz at 150MHz SYSCLKOUT

    EQep2Regs.QDECCTL.bit.QSRC=2;       // Up count mode (freq. measurement)递增计数方式
    EQep2Regs.QDECCTL.bit.XCR=1;  //上升沿计数

    EQep2Regs.QEPCTL.bit.FREE_SOFT=2;   //不受仿真影响
    EQep2Regs.QEPCTL.bit.PCRM=1;       // 最大位置时计数复位
    EQep2Regs.QEPCTL.bit.UTE=1;         // 使能单位定时器
    EQep2Regs.QEPCTL.bit.QCLM=1;        // 锁存模式，直到超时
    EQep2Regs.QPOSMAX=0xffffffff;
    EQep2Regs.QEPCTL.bit.QPEN=1;        // 位置计数器使能

    EQep2Regs.QCAPCTL.bit.UPPS=2;  // 位置事件预定标，

    EQep2Regs.QCAPCTL.bit.CCPS=7;       // 捕获定时器时钟预定 标
    EQep2Regs.QCAPCTL.bit.CEN=1;        // 使能捕获
}

unsigned int Get_Eqep_Value(unsigned char EqepNum )
{
    unsigned int count=0;
   if(EqepNum==0)
   {
      count=EQep1Regs.QPOSCNT;
      EQep1Regs.QPOSCNT=0;
      return count;
   }
   else
  {
       count=EQep2Regs.QPOSCNT;
      EQep2Regs.QPOSCNT=0;
      return count;
  }
}
