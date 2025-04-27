#ifndef __MATH_FUNC_H__
#define __MATH_FUNC_H__

// Global IQ 24

#define GLOBAL_Q 24

typedef long _iq;

#define   _IQ(A)      (long) ((A) * 16777216.0L)


// �������Ҳ�����
extern void Silan_Sin_Cos_PU(_iq Theta, _iq *Sin, _iq *Cos); 

// �����Ų�����
extern _iq Silan_Sqrt(_iq A);                                

#endif
