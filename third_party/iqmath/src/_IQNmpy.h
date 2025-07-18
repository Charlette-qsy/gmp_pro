/*!****************************************************************************
 *  @file       _IQNmpy.c
 *  @brief      Functions to multiply two values of IQN type.
 *
 *  <hr>
 ******************************************************************************/
#ifndef ti_iq_iqnmpy__include
#define ti_iq_iqnmpy__include
#include <stdint.h>

#include "../support.h"
#if ((!defined (__IQMATH_USE_MATHACL__)) || (!defined (__MSPM0_HAS_MATHACL__)))
/**
 * @brief Multiply two values of IQN type.
 *
 * @param iqNInput1       IQN type value input to be multiplied.
 * @param iqNInput2       IQN type value input to be multiplied.
 * @param q_value         IQ format.
 *
 * @return                IQN type result of the multiplication.
 */
#if defined (__TI_COMPILER_VERSION__)
    #pragma FUNC_ALWAYS_INLINE(__IQNmpy)
#elif defined(__IAR_SYSTEMS_ICC__)
    #pragma inline=forced
#endif
__STATIC_INLINE int_fast32_t __IQNmpy(int_fast32_t iqNInput1, int_fast32_t iqNInput2, const int8_t q_value)
{
    int_fast32_t uLow,vLow;
    int_fast32_t uHigh,vHigh;
    int_fast64_t iqNResult;
    
    /* Implement MULHS, high side of 64-bit 32bitx32bit multiplication */
    uLow = iqNInput1 & 0xFFFF;
    vLow = iqNInput2 & 0xFFFF;
    
    uHigh = iqNInput1 >> 16;
    vHigh = iqNInput2 >> 16;
    
    iqNResult = (uLow*vLow);
    iqNResult += (int_fast64_t)(uHigh*vLow + uLow*vHigh) <<16 ;
    iqNResult += (int_fast64_t)(uHigh*vHigh) << 32;
    iqNResult = iqNResult >> q_value;
    
    return (int_fast32_t)iqNResult;
}   
#else
/**
 * @brief Multiply two values of IQN type, using MathACL.
 *
 * @param iqNInput1       IQN type value input to be multiplied.
 * @param iqNInput2       IQN type value input to be multiplied.
 * @param q_value         IQ format.
 *
 * @return                IQN type result of the multiplication.
 */
#if defined (__TI_COMPILER_VERSION__)
    #pragma FUNC_ALWAYS_INLINE(__IQNmpy)
#elif defined(__IAR_SYSTEMS_ICC__)
    #pragma inline=forced
#endif
__STATIC_INLINE int_fast32_t __IQNmpy(int_fast32_t iqNInput1, int_fast32_t iqNInput2, const int8_t q_value)
{
    /* write control */
    MATHACL->CTL = 6 | (q_value<<8) | (1 << 5);
    /* write operands to HWA */
    MATHACL->OP2 = iqNInput2;
    /* write trigger word last */
    MATHACL->OP1 = iqNInput1;
    /* read iqmpy product */
    return MATHACL->RES1;
}
#endif
#endif
