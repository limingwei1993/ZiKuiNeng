/*
 * eqep.c
 *
 *  Created on: 2022��6��30��
 *      Author: EDY
 */
#include "DSP2833x_EQep.h"

void Eqep_Init(void)
{
    EQep1Regs.QUPRD=800000;    // Unit Timer for 100Hz at 150MHz SYSCLKOUT

    EQep1Regs.QDECCTL.bit.QSRC=2;       // Up count mode (freq. measurement)����������ʽ
    EQep1Regs.QDECCTL.bit.XCR=1;  //�����ؼ���

    EQep1Regs.QEPCTL.bit.FREE_SOFT=2;   //���ܷ���Ӱ��
    EQep1Regs.QEPCTL.bit.PCRM=1;       // ���λ��ʱ������λ
    EQep1Regs.QEPCTL.bit.UTE=1;         // ʹ�ܵ�λ��ʱ��
    EQep1Regs.QEPCTL.bit.QCLM=1;        // ����ģʽ��ֱ����ʱ
    EQep1Regs.QPOSMAX=0xffffffff;
    EQep1Regs.QEPCTL.bit.QPEN=1;        // λ�ü�����ʹ��

    EQep1Regs.QCAPCTL.bit.UPPS=2;  // λ���¼�Ԥ���꣬

    EQep1Regs.QCAPCTL.bit.CCPS=7;       // ����ʱ��ʱ��Ԥ�� ��
    EQep1Regs.QCAPCTL.bit.CEN=1;        // ʹ�ܲ���
    //
    EQep2Regs.QUPRD=800000;    // Unit Timer for 100Hz at 150MHz SYSCLKOUT

    EQep2Regs.QDECCTL.bit.QSRC=2;       // Up count mode (freq. measurement)����������ʽ
    EQep2Regs.QDECCTL.bit.XCR=1;  //�����ؼ���

    EQep2Regs.QEPCTL.bit.FREE_SOFT=2;   //���ܷ���Ӱ��
    EQep2Regs.QEPCTL.bit.PCRM=1;       // ���λ��ʱ������λ
    EQep2Regs.QEPCTL.bit.UTE=1;         // ʹ�ܵ�λ��ʱ��
    EQep2Regs.QEPCTL.bit.QCLM=1;        // ����ģʽ��ֱ����ʱ
    EQep2Regs.QPOSMAX=0xffffffff;
    EQep2Regs.QEPCTL.bit.QPEN=1;        // λ�ü�����ʹ��

    EQep2Regs.QCAPCTL.bit.UPPS=2;  // λ���¼�Ԥ���꣬

    EQep2Regs.QCAPCTL.bit.CCPS=7;       // ����ʱ��ʱ��Ԥ�� ��
    EQep2Regs.QCAPCTL.bit.CEN=1;        // ʹ�ܲ���
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
