/**
 * @file compiler_sup.h
 * @author Javnson (javnson@zju.edu.cn)
 * @brief 
 * @version 0.1
 * @date 2024-09-30
 * 
 * @copyright Copyright GMP(c) 2024
 * 
 */
 
// This file provided a set of macros to help user to config the code.

#ifndef _FILE_COMPILER_SUP_H_
#define _FILE_COMPILER_SUP_H_



//////////////////////////////////////////////////////////////////////////
// Global Switch: Judge Compiler Types
// 
// Check C++ compiler, and ensure it is fulfilling the requirement.
// + Microsoft MSVC doesn't support `__cplusplus` macro 
//
// + old version of compiler only support C++03
//
// + newer version of compiler at least support C++11
//

// ....................................................................//
#if defined _MSC_VER // MSVC compiler

#include <core/std/cc/cc.msvc.inl>

// ....................................................................//
// GCC compiler
// Containing Keil AC6 Compiler
//
#elif defined __GNUC__ 

#include <core/std/cc/cc.gnuc.inl>

// ....................................................................//
#elif defined __CC_ARM // ARM compiler

#include <core/std/cc/cc.armcc.inl>

// ....................................................................//
#elif defined __TI_COMPILER_VERSION__ // TI DSP C2000 Compiler

#include <core/std/cc/cc.c2000.inl>

// ....................................................................//
#else // compiler with no name

#include <core/std/cc/cc.default.inl>

#endif // end of compiler type


//////////////////////////////////////////////////////////////////////////
// Step II 


// Mark static inline function 
#ifndef DISABLE_STATIC_INLINE_FUNC
#define GMP_STATIC_INLINE static inline
#else
#define GMP_STATIC_INLINE
#endif // GMP_STATIC_INLINE 

// Mark inline function 
#ifndef DISABLE_INLINE_FUNC
#ifndef GMP_INLINE 
#define GMP_INLINE inline
#endif
#else
#undef GMP_INLINE
#define GMP_INLINE
#endif // GMP_INLINE

// Mark a function that should invoke as quick as possible 
#ifndef FAST_FUNCTION
#define FAST_FUNCTION GMP_STATIC_INLINE
#endif // FAST_FUNCTION

//////////////////////////////////////////////////////////////////////////
// MSVC Configure



#endif // _FILE_COMPILER_SUP_H_
