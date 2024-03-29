/*
 -------------------------------------------------------------------------------
 This file is part of the Plink, Plonk, Plank libraries
  by Martin Robinson
 
 http://code.google.com/p/pl-nk/
 
 Copyright University of the West of England, Bristol 2011-15
 All rights reserved.
 
 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:
 
 * Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.
 * Neither the name of University of the West of England, Bristol nor 
   the names of its contributors may be used to endorse or promote products
   derived from this software without specific prior written permission.
 
 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
 DISCLAIMED. IN NO EVENT SHALL UNIVERSITY OF THE WEST OF ENGLAND, BRISTOL BE 
 LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
 CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE 
 GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) 
 HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT 
 LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT 
 OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 
 
 This software makes use of third party libraries. For more information see:
 doc/license.txt included in the distribution.
 -------------------------------------------------------------------------------
 */

#ifndef PLANK_MATHS_H
#define PLANK_MATHS_H


/** @defgroup PlankMathsFunctions Plank maths functions
 @ingroup PlankFunctions
 @{
*/
    
                    //3.14159265358979323846264338327950288419716939937510
#define PLANK_PI_D    3.1415926535897932384626433832795
#define PLANK_PI_F    3.14159265358979323846f
#define PLANK_SQRT2_D 1.41421356237309514547462185873883
#define PLANK_SQRT2_F 1.41421356237309514547f
#define PLANK_BILLION_D 1000000000.0
#define PLANK_BILLION_F 1000000000.f
#define PLANK_MILLION_D 1000000.0
#define PLANK_MILLION_F 1000000.f
#define PLANK_440_D   440.0
#define PLANK_440_F   440.f
#define PLANK_360_D   360.0
#define PLANK_360_F   360.f
#define PLANK_69_D    69.0
#define PLANK_69_F    69.f
#define PLANK_20_D    20.0
#define PLANK_20_F    20.f
#define PLANK_12_D    12.0
#define PLANK_12_F    12.f
#define PLANK_2_D     2.0
#define PLANK_2_F     2.f
#define PLANK_1_D     1.0
#define PLANK_1_F     1.f
#define PLANK_0_D     0.0
#define PLANK_0_F     0.f

#define PLANK_CHARPEAK_I CHAR_MAX
#define PLANK_CHARPEAK_F ((float)PLANK_CHARPEAK_I)
#define PLANK_CHARPEAK_D ((double)PLANK_CHARPEAK_I)

#define PLANK_SHORTPEAK_I SHRT_MAX
#define PLANK_SHORTPEAK_F ((float)PLANK_SHORTPEAK_I)
#define PLANK_SHORTPEAK_D ((double)PLANK_SHORTPEAK_I)

#define PLANK_INTPEAK_I INT_MAX
#define PLANK_INTPEAK_F ((float)PLANK_INTPEAK_I)
#define PLANK_INTPEAK_D ((double)PLANK_INTPEAK_I)

#define PLANK_INT24PEAK_I PLANK_INT24_MAX
#define PLANK_INT24PEAK_F ((float)PLANK_INT24PEAK_I)
#define PLANK_INT24PEAK_D ((double)PLANK_INT24PEAK_I)


#if (defined (_WIN32) || defined (_WIN64))
//    #define PLANK_INC(a) a = a + 1
    #define PLANK_INC(a) ++a
#else
    #define PLANK_INC(a) ++a
#endif

PLANK_BEGIN_C_LINKAGE

PlankB pl_IsInfF (float a);
PlankB pl_IsInfD (double a);
PlankB pl_IsNanF (float a);
PlankB pl_IsNanD (double a);

PLANK_END_C_LINKAGE


//#if (defined (_WIN32) || defined (_WIN64))
//static inline PlankB pl_IsInfF (float a)				{ return _finite ((double)a) == 0; }
//static inline PlankB pl_IsInfD (double a)				{ return _finite (a) == 0; }
//static inline PlankB pl_IsNanF (float a)				{ return _isnan ((double)a) != 0; }
//static inline PlankB pl_IsNanD (double a)				{ return _isnan (a) != 0; }
//#else
//static inline PlankB pl_IsInfF (float a)				{ return isinf (a); }
//static inline PlankB pl_IsInfD (double a)				{ return isinf (a); }
//static inline PlankB pl_IsNanF (float a)				{ return isnan (a); }
//static inline PlankB pl_IsNanD (double a)				{ return isnan (a); }
//#endif


// unary ops

/** Just returns the input argument. 
 This is just added as a convenience for the vector-based functions. */
static inline float pl_MoveF (float a)              { return a; }
/** Just returns the input argument. 
 This is just added as a convenience for the vector-based functions. */
static inline double pl_MoveD (double a)            { return a; } 

static inline float pl_IncF (float a)               { return a + 1.f; }
static inline double pl_IncD (double a)             { return a + 1.0; } 

static inline float pl_DecF (float a)               { return a - 1.f; }
static inline double pl_DecD (double a)             { return a - 1.0; } 


/** Returns the negative of the input argument. */
static inline float pl_NegF (float a)               { return -a; }
/** Returns the negative of the input argument. */
static inline double pl_NegD (double a)             { return -a; }  


/** Returns the absolute of the input argument. */
static inline float pl_AbsF (float a)               { return fabsf (a); }
/** Returns the absolute of the input argument. */
static inline double pl_AbsD (double a)             { return fabs (a); }



#if PLANK_WIN || PLANK_ANDROID
static inline float pl_Log2F (float a)              { return logf (a) / logf (2.f); }
static inline double pl_Log2D (double a)            { return log (a) / log (2.0); }
#else
/** Returns the logarithm base 2 of the input argument. */
static inline float pl_Log2F (float a)              { return log2f (a); }
/** Returns the logarithm base 2 of the input argument. */
static inline double pl_Log2D (double a)            { return log2 (a); }
#endif

/** Returns the reciprocal of the input argument (i.e, @f$ \frac{1}{a} @f$). */
static inline float pl_ReciprocalF (float a)        { return 1.f / a; }
/** Returns the reciprocal of the input argument (i.e, @f$ \frac{1}{a} @f$). */
static inline double pl_ReciprocalD (double a)      { return 1.0 / a; }

/** Returns the sine of the input argument. */
static inline float pl_SinF (float a)               { return sinf (a); }
/** Returns the sine of the input argument. */
static inline double pl_SinD (double a)             { return sin (a); }

/** Returns the cosine of the input argument. */
static inline float pl_CosF (float a)               { return cosf (a); }
/** Returns the cosine of the input argument. */
static inline double pl_CosD (double a)             { return cos (a); }

/** Returns the tangent of the input argument. */
static inline float pl_TanF (float a)               { return tanf (a); }
/** Returns the tangent of the input argument. */
static inline double pl_TanD (double a)             { return tan (a); }

/** Returns the arcsine of the input argument. */
static inline float pl_AsinF (float a)              { return asinf (a); }
/** Returns the arcsine of the input argument. */
static inline double pl_AsinD (double a)            { return asin (a); }

/** Returns the arcosine of the input argument. */
static inline float pl_AcosF (float a)              { return acosf (a); }
/** Returns the arcosine of the input argument. */
static inline double pl_AcosD (double a)            { return acos (a); }

/** Returns the arctangent of the input argument. */
static inline float pl_AtanF (float a)              { return atanf (a); }
/** Returns the arctangent of the input argument. */
static inline double pl_AtanD (double a)            { return atan (a); }

/** Returns the hyperbolic sine of the input argument. */
static inline float pl_SinhF (float a)              { return sinhf (a); }
/** Returns the hyperbolic sine of the input argument. */
static inline double pl_SinhD (double a)            { return sinh (a); }

/** Returns the hyperbolic cosine of the input argument. */
static inline float pl_CoshF (float a)              { return coshf (a); }
/** Returns the hyperbolic cosine of the input argument. */
static inline double pl_CoshD (double a)            { return cosh (a); }

/** Returns the hyperbolic tangent of the input argument. */
static inline float pl_TanhF (float a)              { return tanhf (a); }
/** Returns the hyperbolic tangent of the input argument. */
static inline double pl_TanhD (double a)            { return tanh (a); }

/** Returns the square root of the input argument. */
static inline float pl_SqrtF (float a)              { return sqrtf (a); }
/** Returns the square root of the input argument. */
static inline double pl_SqrtD (double a)            { return sqrt (a); }

/** Returns the natural logarithm of the input argument. */
static inline float pl_LogF (float a)               { return logf (a); }
/** Returns the natural logarithm of the input argument. */
static inline double pl_LogD (double a)             { return log (a); }

/** Returns the logarithm base 10 of the input argument. */
static inline float pl_Log10F (float a)             { return log10f (a); }
/** Returns the logarithm base 10 of the input argument. */
static inline double pl_Log10D (double a)           { return log10 (a); }

/** Returns the exponent of the input argument. */
static inline float pl_ExpF (float a)               { return expf (a); }
/** Returns the exponent of the input argument. */
static inline double pl_ExpD (double a)             { return exp (a); }

/** Returns the input argument squared. */
static inline float pl_SquaredF (float a)           { return a * a; }
/** Returns the input argument squared. */
static inline double pl_SquaredD (double a)         { return a * a; }

/** Returns the input argument cubed. */
static inline float pl_CubedF (float a)             { return a * a * a; }
/** Returns the input argument cubed. */
static inline double pl_CubedD (double a)           { return a * a * a; }

/** Returns the input argument rounded up to the next highest integer. */
static inline float pl_CeilF (float a)              { return ceilf (a); }
/** Returns the input argument rounded up to the next highest integer. */
static inline double pl_CeilD (double a)            { return ceil (a); }

/** Returns the input argument rounded down to the next lowest integer. */
static inline float pl_FloorF (float a)             { return floorf (a); }
/** Returns the input argument rounded down to the next lowest integer. */
static inline double pl_FloorD (double a)           { return floor (a); }

/** Returns the fractional part of the input argument. */
static inline float pl_FracF (float a)              { return a - floorf (a); }
/** Returns the fractional part of the input argument. */
static inline double pl_FracD (double a)            { return a - floor (a); }

/** Returns 0 if the input is 0, -1 if the input is negative or 1 if the input argument is positive. */
static inline float pl_SignF (float a)              { return (a == 0.f) ? 0.f : (a < 0.f) ? -1.f : 1.f; }
/** Returns 0 if the input is 0, -1 if the input is negative or 1 if the input argument is positive. */
static inline double pl_SignD (double a)            { return (a == 0.0) ? 0.0 : (a < 0.0) ? -1.0 : 1.0; }

/** Returns the input argument converted from MIDI note numbers to frequency (in Hz). */
static inline float pl_M2FF (float a)               { return 440.f * powf(2.f, (a - 69.f) * (1.f / 12.f)); }
/** Returns the input argument converted from MIDI note numbers to frequency (in Hz). */
static inline double pl_M2FD (double a)             { return 440.0 * pow (2.0, (a - 69.0) * (1.0 / 12.0)); }

/** Returns the input argument converted from frequency (in Hz) to MIDI note numbers. */
static inline float pl_F2MF (float a)               { return pl_Log2F (a * (1.f / 440.f)) * 12.f + 69.f; }
/** Returns the input argument converted from frequency (in Hz) to MIDI note numbers. */
static inline double pl_F2MD (double a)             { return pl_Log2D (a * (1.0 / 440.0)) * 12.0 + 69.0; }

/** Returns the input argument converted from linear amplitude to decibels where 0dB is an amplitude of 1. */
static inline float pl_A2dBF (float a)              { return log10f(a) * 20.f; }
/** Returns the input argument converted from linear amplitude to decibels where 0dB is an amplitude of 1. */
static inline double pl_A2dBD (double a)            { return log10 (a) * 20.0; }

/** Returns the input argument converted from decibels to linear amplitude where 0dB is an amplitude of 1. */
static inline float pl_dB2AF (float a)              { return powf(10.f, a * (1.f / 20.f)); }
/** Returns the input argument converted from decibels to linear amplitude where 0dB is an amplitude of 1. */
static inline double pl_dB2AD (double a)            { return pow (10.0, a * (1.0 / 20.0)); }

/** Returns the input argument converted from degrees to radians. */
static inline float pl_D2RF (float a)               { return a * (1.f / 360.f) * PLANK_PI_F; }
/** Returns the input argument converted from degrees to radians. */
static inline double pl_D2RD (double a)             { return a * (1.0 / 360.0) * PLANK_PI_D; }

/** Returns the input argument converted from radians to degrees. */
static inline float pl_R2DF (float a)               { return a * (1.f / PLANK_PI_F) * 360.f; }
/** Returns the input argument converted from radians to degrees. */
static inline double pl_R2DD (double a)             { return a * (1.0 / PLANK_PI_D) * 360.0; }

/** Returns the input argument distorted. */
static inline float pl_DistortF (float a)           { return a / (1.f + fabsf(a)); }
/** Returns the input argument distorted. */
static inline double pl_DistortD (double a)         { return a / (1.0 + fabs (a)); }

/** Returns the input argument with infinities, NaNs and denormallised numbers removed. 
 from music-dsp list*/
static inline float pl_ZapF (float x)           
{ 
    float absx = pl_AbsF (x);
    return (absx > (float)1e-15 && absx < (float)1e15) ? x : 0.f;
}

/** Returns the input argument with infinities, NaNs and denormallised numbers removed. */
static inline double pl_ZapD (double x)
{ 
    double absx = pl_AbsD (x);
    return (absx > 1e-15 && absx < 1e15) ? x : 0.0;
}


// binary ops


/** Returns @f$ a + b @f$. */
static inline float pl_AddF (float a, float b)                          { return a + b; }
/** Returns @f$ a + b @f$. */
static inline double pl_AddD (double a, double b)                       { return a + b; }

/** Returns @f$ a - b @f$. */
static inline float pl_SubF (float a, float b)                          { return a - b; }
/** Returns @f$ a - b @f$. */
static inline double pl_SubD (double a, double b)                       { return a - b; }

/** Returns @f$ a \times b @f$. */
static inline float pl_MulF (float a, float b)                          { return a * b; }
/** Returns @f$ a \times b @f$. */
static inline double pl_MulD (double a, double b)                       { return a * b; }

/** Returns @f$ \frac{a}{b} @f$. */
static inline float pl_DivF (float a, float b)                          { return a / b; }
/** Returns @f$ \frac{a}{b} @f$. */
static inline double pl_DivD (double a, double b)                       { return a / b; }

/** Returns @f$ a % b @f$. */
static inline float pl_ModF (float a, float b)                          { return fmodf (a, b); }
/** Returns @f$ a % b @f$. */
static inline double pl_ModD (double a, double b)                       { return fmod (a, b); }


/** Returns minimum of @e a and @e b. */
static inline float pl_MinF (float a, float b)                          { return (a > b) ? b : a; }
/** Returns minimum of @e a and @e b. */
static inline double pl_MinD (double a, double b)                       { return (a > b) ? b : a; }

/** Returns maximum of @e a and @e b. */
static inline float pl_MaxF (float a, float b)                          { return (a < b) ? b : a; }
/** Returns maximum of @e a and @e b. */
static inline double pl_MaxD (double a, double b)                       { return (a < b) ? b : a; }


/** Returns @e a raised to the power @e b. */
static inline float pl_PowF (float a, float b)                          { return powf(a, b); }
/** Returns @e a raised to the power @e b. */
static inline double pl_PowD (double a, double b)                       { return pow (a, b); }

/** Returns 1 if the inputs are equal otherwise returns 0.  */
static inline float pl_IsEqualToF (float a, float b)                    { return (a == b) ? 1.f : 0.f; }
/** Returns 1 if the inputs are equal otherwise returns 0.  */
static inline double pl_IsEqualToD (double a, double b)                 { return (a == b) ? 1.0 : 0.0; }

/** Returns 1 if the inputs are not equal otherwise returns 0.  */
static inline float pl_IsNotEqualToF (float a, float b)                 { return (a != b) ? 1.f : 0.f; }
/** Returns 1 if the inputs are not equal otherwise returns 0.  */
static inline double pl_IsNotEqualToD (double a, double b)              { return (a != b) ? 1.0 : 0.0; }

/** Returns 1 if the @e a is greater than @e b otherwise returns 0.  */
static inline float pl_IsGreaterThanF (float a, float b)                { return (a > b) ? 1.f : 0.f; }
/** Returns 1 if the @e a is greater than @e b otherwise returns 0.  */
static inline double pl_IsGreaterThanD (double a, double b)             { return (a > b) ? 1.0 : 0.0; }

/** Returns 1 if the @e a is greater than or equal to @e b otherwise returns 0.  */
static inline float pl_IsGreaterThanOrEqualToF (float a, float b)       { return (a >= b) ? 1.f : 0.f; }
/** Returns 1 if the @e a is greater than or equal to @e b otherwise returns 0.  */
static inline double pl_IsGreaterThanOrEqualToD (double a, double b)    { return (a >= b) ? 1.0 : 0.0; }

/** Returns 1 if the @e a is less than @e b otherwise returns 0.  */
static inline float pl_IsLessThanF (float a, float b)                   { return (a < b) ? 1.f : 0.f; }
/** Returns 1 if the @e a is less than @e b otherwise returns 0.  */
static inline double pl_IsLessThanD (double a, double b)                { return (a < b) ? 1.0 : 0.0; }

/** Returns 1 if the @e a is less than or equal to @e b otherwise returns 0.  */
static inline float pl_IsLessThanOrEqualToF (float a, float b)          { return (a <= b) ? 1.f : 0.f; }
/** Returns 1 if the @e a is less than or equal to @e b otherwise returns 0.  */
static inline double pl_IsLessThanOrEqualToD (double a, double b)       { return (a <= b) ? 1.0 : 0.0; }

/** Returns @f$ \sqrt{ a^2 + b^2 } @f$.  */
static inline float pl_HypotF (float a, float b)                        { return hypotf(a, b); }
/** Returns @f$ \sqrt{ a^2 + b^2 } @f$.  */
static inline double pl_HypotD (double a, double b)                     { return hypot (a, b); }

/** Returns @f$ atan2(a,b) @f$.  */
static inline float pl_Atan2F (float a, float b)                        { return atan2f(a, b); }
/** Returns @f$ atan2(a,b) @f$.  */
static inline double pl_Atan2D (double a, double b)                     { return atan2 (a, b); }

/** Returns @f$ a * a + b * b @f$.  */
static inline float pl_SumSqrF (float a, float b)                       { return a * a + b * b; }
/** Returns @f$ a * a + b * b @f$.  */
static inline double pl_SumSqrD (double a, double b)                    { return a * a + b * b; }

/** Returns @f$ a * a - b * b @f$.  */
static inline float pl_DifSqrF (float a, float b)                       { return a * a - b * b; }
/** Returns @f$ a * a - b * b @f$.  */
static inline double pl_DifSqrD (double a, double b)                    { return a * a - b * b; }

/** Returns @f$ (a + b) * (a + b) @f$.  */
static inline float pl_SqrSumF (float a, float b)                       { a += b; return a * a; }
/** Returns @f$ (a + b) * (a + b) @f$.  */
static inline double pl_SqrSumD (double a, double b)                    { a += b; return a * a; }

/** Returns @f$ (a - b) * (a - b) @f$.  */
static inline float pl_SqrDifF (float a, float b)                       { a -= b; return a * a; }
/** Returns @f$ (a - b) * (a - b) @f$.  */
static inline double pl_SqrDifD (double a, double b)                    { a -= b; return a * a; }

/** Returns the absolute difference between the input arguments.  */
static inline float pl_AbsDifF (float a, float b)                       { return fabsf (a - b); }
/** Returns the absolute difference between the input arguments.  */
static inline double pl_AbsDifD (double a, double b)                    { return fabs (a - b); }

/** If @e a is less than @e b returns 0 otherwise return @e a. */
static inline float pl_ThreshF (float a, float b)                       { return (a < b) ? 0.f : a; }
/** If @e a is less than @e b returns 0 otherwise return @e a. */
static inline double pl_ThreshD (double a, double b)                    { return (a < b) ? 0.0 : a; }


// integer versions

static inline short pl_MoveS (short a)                      { return a; } 
static inline int pl_MoveI (int a)                          { return a; } 
static inline PlankLL pl_MoveLL (PlankLL a)                 { return a; } 
static inline short pl_IncS (short a)                       { return a + 1; } 
static inline int pl_IncI (int a)                           { return a + 1; } 
static inline PlankLL pl_IncLL (PlankLL a)                  { return a + 1; } 
static inline short pl_DecS (short a)                       { return a - 1; } 
static inline int pl_DecI (int a)                           { return a - 1; } 
static inline PlankLL pl_DecLL (PlankLL a)                  { return a - 1; } 
static inline short pl_NegS (short a)                       { return -a; }  
static inline int pl_NegI (int a)                           { return -a; }  
static inline PlankLL pl_NegLL (PlankLL a)                  { return -a; }  
static inline short pl_AbsS (short a)                       { return a < 0 ? -a : a; }
static inline int pl_AbsI (int a)                           { return a < 0 ? -a : a; }
static inline PlankLL pl_AbsLL (PlankLL a)                  { return a < 0 ? -a : a; }
static inline short pl_SquaredS (short a)                   { return a * a; }
static inline int pl_SquaredI (int a)                       { return a * a; }
static inline PlankLL pl_SquaredLL (PlankLL a)              { return a * a; }
static inline short pl_CubedS (short a)                     { return a * a * a; }
static inline int pl_CubedI (int a)                         { return a * a * a; }
static inline PlankLL pl_CubedLL (PlankLL a)                { return a * a * a; }
static inline short pl_SignS (short a)                      { return (a == 0) ? 0 : (a < 0) ? -1 : 1; }
static inline int pl_SignI (int a)                          { return (a == 0) ? 0 : (a < 0) ? -1 : 1; }
static inline PlankLL pl_SignLL (PlankLL a)                 { return (a == 0) ? 0 : (a < 0) ? -1 : 1; }
static inline short pl_AddS (short a, short b)              { return a + b; }
static inline int pl_AddI (int a, int b)                    { return a + b; }
static inline PlankLL pl_AddLL (PlankLL a, PlankLL b)       { return a + b; }
static inline short pl_SubS (short a, short b)              { return a - b; }
static inline int pl_SubI (int a, int b)                    { return a - b; }
static inline PlankLL pl_SubLL (PlankLL a, PlankLL b)       { return a - b; }
static inline short pl_MulS (short a, short b)              { return a * b; }
static inline int pl_MulI (int a, int b)                    { return a * b; }
static inline PlankLL pl_MulLL (PlankLL a, PlankLL b)       { return a * b; }
static inline short pl_DivS (short a, short b)              { return a / b; }
static inline int pl_DivI (int a, int b)                    { return a / b; }
static inline PlankLL pl_DivLL (PlankLL a, PlankLL b)       { return a / b; }
static inline short pl_ModS (short a, short b)              { return a % b; }
static inline int pl_ModI (int a, int b)                    { return a % b; }
static inline PlankLL pl_ModLL (PlankLL a, PlankLL b)       { return a % b; }

static inline PlankS pl_MinS (PlankS a, PlankS b)           { return (a > b) ? b : a; }
static inline PlankI pl_MinI (PlankI a, PlankI b)           { return (a > b) ? b : a; }
static inline PlankLL pl_MinLL (PlankLL a, PlankLL b)       { return (a > b) ? b : a; }
static inline PlankS pl_MaxS (PlankS a, PlankS b)           { return (a < b) ? b : a; }
static inline PlankI pl_MaxI (PlankI a, PlankI b)           { return (a < b) ? b : a; }
static inline PlankLL pl_MaxLL (PlankLL a, PlankLL b)       { return (a < b) ? b : a; }

static inline PlankUS pl_MinUS (PlankUS a, PlankUS b)           { return (a > b) ? b : a; }
static inline PlankUI pl_MinUI (PlankUI a, PlankUI b)           { return (a > b) ? b : a; }
static inline PlankULL pl_MinULL (PlankULL a, PlankULL b)       { return (a > b) ? b : a; }
static inline PlankUS pl_MaxUS (PlankUS a, PlankUS b)           { return (a < b) ? b : a; }
static inline PlankUI pl_MaxUI (PlankUI a, PlankUI b)           { return (a < b) ? b : a; }
static inline PlankULL pl_MaxULL (PlankULL a, PlankULL b)       { return (a < b) ? b : a; }

static inline short pl_IsEqualToS (short a, short b)                        { return a == b ? 1 : 0; }
static inline int pl_IsEqualToI (int a, int b)                              { return a == b ? 1 : 0; }
static inline PlankLL pl_IsEqualToLL (PlankLL a, PlankLL b)                 { return a == b ? 1 : 0; }
static inline short pl_IsNotEqualToS (short a, short b)                     { return a != b ? 1 : 0; }
static inline int pl_IsNotEqualToI (int a, int b)                           { return a != b ? 1 : 0; }
static inline PlankLL pl_IsNotEqualToLL (PlankLL a, PlankLL b)              { return a != b ? 1 : 0; }
static inline short pl_IsGreaterThanS (short a, short b)                    { return a > b ? 1 : 0; }
static inline int pl_IsGreaterThanI (int a, int b)                          { return a > b ? 1 : 0; }
static inline PlankLL pl_IsGreaterThanLL (PlankLL a, PlankLL b)             { return a > b ? 1 : 0; }
static inline short pl_IsGreaterThanOrEqualToS (short a, short b)           { return a >= b ? 1 : 0; }
static inline int pl_IsGreaterThanOrEqualToI (int a, int b)                 { return a >= b ? 1 : 0; }
static inline PlankLL pl_IsGreaterThanOrEqualToLL (PlankLL a, PlankLL b)    { return a >= b ? 1 : 0; }
static inline short pl_IsLessThanS (short a, short b)                       { return a < b ? 1 : 0; }
static inline int pl_IsLessThanI (int a, int b)                             { return a < b ? 1 : 0; }
static inline PlankLL pl_IsLessThanLL (PlankLL a, PlankLL b)                { return a < b ? 1 : 0; }
static inline short pl_IsLessThanOrEqualToS (short a, short b)              { return a <= b ? 1 : 0; }
static inline int pl_IsLessThanOrEqualToI (int a, int b)                    { return a <= b ? 1 : 0; }
static inline PlankLL pl_IsLessThanOrEqualToLL (PlankLL a, PlankLL b)       { return a <= b ? 1 : 0; }


static inline short pl_SumSqrS (short a, short b)                   { return a * a + b * b; }
static inline int pl_SumSqrI (int a, int b)                         { return a * a + b * b; }
static inline PlankLL pl_SumSqrLL (PlankLL a, PlankLL b)            { return a * a + b * b; }

static inline short pl_DifSqrS (short a, short b)                   { return a * a - b * b; }
static inline int pl_DifSqrI (int a, int b)                         { return a * a - b * b; }
static inline PlankLL pl_DifSqrLL (PlankLL a, PlankLL b)            { return a * a - b * b; }

static inline short pl_SqrSumS (short a, short b)                   { a += b; return a * a; }
static inline int pl_SqrSumI (int a, int b)                         { a += b; return a * a; }
static inline PlankLL pl_SqrSumLL (PlankLL a, PlankLL b)            { a += b; return a * a; }

static inline short pl_SqrDifS (short a, short b)                   { a -= b; return a * a; }
static inline int pl_SqrDifI (int a, int b)                         { a -= b; return a * a; }
static inline PlankLL pl_SqrDifLL (PlankLL a, PlankLL b)            { a -= b; return a * a; }

static inline short pl_AbsDifS (short a, short b)                   { return pl_AbsS (a - b); }
static inline int pl_AbsDifI (int a, int b)                         { return pl_AbsI (a - b); }
static inline PlankLL pl_AbsDifLL (PlankLL a, PlankLL b)            { return pl_AbsLL (a - b); }

static inline short pl_ThreshS (float a, short b)                   { return (a < b) ? 0 : a; }
static inline int pl_ThreshI (int a, int b)                         { return (a < b) ? 0 : a; }
static inline PlankLL pl_ThreshLL (PlankLL a, PlankLL b)            { return (a < b) ? 0 : a; }


/** Returns minimum of @e a and @e b. */
static inline PlankL pl_MinL (PlankL a, PlankL b)                       { return (a > b) ? b : a; }
/** Returns maximum of @e a and @e b. */
static inline PlankL pl_MaxL (PlankL a, PlankL b)                       { return (a < b) ? b : a; }

static inline float pl_ClipF (float a, float lo, float hi)              { return pl_MinF (pl_MaxF (a, lo), hi); }
static inline double pl_ClipD (double a, double lo, double hi)          { return pl_MinD (pl_MaxD (a, lo), hi); }

static inline PlankI pl_ClipI (PlankI a, PlankI lo, PlankI hi)          { return pl_MinI (pl_MaxI (a, lo), hi); }
static inline PlankS pl_ClipS (PlankS a, PlankS lo, PlankS hi)          { return pl_MinS (pl_MaxS (a, lo), hi); }
static inline PlankL pl_ClipL (PlankL a, PlankL lo, PlankL hi)          { return pl_MinL (pl_MaxL (a, lo), hi); }
static inline PlankLL pl_ClipLL (PlankLL a, PlankLL lo, PlankLL hi)     { return pl_MinLL (pl_MaxLL (a, lo), hi); }

//round
//trunc
//clip2
//wrap?

// ternary

// quarternary

// quinary

/** Maps a value from one linear range to another. 
 @param input The input value to map.
 @param inLow The minimum value of the input value range. 
 @param inHigh The maximum value of the input value range.
 @param outLow The minimum value of the output value range. 
 @param outHigh The maximum value of the output value range.
 @return The mapped value. */
static inline float pl_LinLinF (float input, 
                                float inLow, float inHigh, 
                                float outLow, float outHigh)
{
    float inRange, outRange;
	inRange = inHigh - inLow;
	outRange = outHigh - outLow;
	return (input - inLow) * outRange / inRange + outLow;    
}

/** Maps a value from one linear range to another. 
 @param input The input value to map.
 @param inLow The minimum value of the input value range. 
 @param inHigh The maximum value of the input value range.
 @param outLow The minimum value of the output value range. 
 @param outHigh The maximum value of the output value range.
 @return The mapped value. */
static inline double pl_LinLinD (double input, 
                                 double inLow, double inHigh, 
                                 double outLow, double outHigh)
{
    double inRange, outRange;
	inRange = inHigh - inLow;
	outRange = outHigh - outLow;
	return (input - inLow) * outRange / inRange + outLow;    
}

/** Maps a value from one linear range to another.
 @param input The input value to map.
 @param inLow The minimum value of the input value range. 
 @param inRange The maximum value of the input value range 
                (i.e., @f$ inHigh = inLow + inRange @f$).
 @param outLow The minimum value of the output value range. 
 @param outRange The range of the output value 
                 (i.e., @f$ outHigh = outLow + outRange @f$).
 @return The mapped value. */
static inline float pl_LinLin2F (float input, 
                                 float inLow, float inRange,
                                 float outLow, float outRange)
{
	return (input - inLow) * outRange / inRange + outLow;    
}

/** Maps a value from one linear range to another.
 @param input The input value to map.
 @param inLow The minimum value of the input value range. 
 @param inRange The maximum value of the input value range 
                (i.e., @f$ inHigh = inLow + inRange @f$).
 @param outLow The minimum value of the output value range. 
 @param outRange The range of the output value 
                 (i.e., @f$ outHigh = outLow + outRange @f$).
 @return The mapped value. */
static inline double pl_LinLin2D (double input, 
                                  double inLow, double inRange,
                                  double outLow, double outRange)
{
	return (input - inLow) * outRange / inRange + outLow;    
}

/** Maps a value from a linear range to an exponential range.
 NB Neither the input nor output range may meet or cross zero.
 @param input The input value to map.
 @param inLow The minimum value of the linear input value range. 
 @param inHigh The maximum value of the linear input value range.
 @param outLow The minimum value of the exponential output value range. 
 @param outHigh The maximum value of the exponential output value range.
 @return The mapped value. */
static inline float pl_LinExpF (float input, 
                                float inLow, float inHigh, 
                                float outLow, float outHigh)
{
    float outRatio, reciprocalInRange, inLowOverInRange;
	outRatio = outHigh / outLow;
    reciprocalInRange = 1.f / (inHigh - inLow);
    inLowOverInRange = reciprocalInRange * inLow;
    return outLow * powf (outRatio, input * reciprocalInRange - inLowOverInRange);	
}

/** Maps a value from a linear range to an exponential range.
 NB Neither the input nor output range may meet or cross zero.
 @param input The input value to map.
 @param inLow The minimum value of the linear input value range. 
 @param inHigh The maximum value of the linear input value range.
 @param outLow The minimum value of the exponential output value range. 
 @param outHigh The maximum value of the exponential output value range.
 @return The mapped value. */
static inline double pl_LinExpD (double input, 
                                 double inLow, double inHigh, 
                                 double outLow, double outHigh)
{
    double outRatio, reciprocalInRange, inLowOverInRange;
	outRatio = outHigh / outLow;
    reciprocalInRange = 1.0 / (inHigh - inLow);
    inLowOverInRange = reciprocalInRange * inLow;
    return outLow * pow (outRatio, input * reciprocalInRange - inLowOverInRange);	
}


//linsin
//linwelch
//explin

/** Perform linear interpolation on two values. 
 @param a Value a.
 @param b Value b.
 @param frac The interpolation fraction, this must be between 0 and 1. 
 @return @f$ a + (frac \times (b - a)) @f$*/
static inline float pl_LinInterpF (float a, float b, float frac)
{
    return a + (frac * (b - a));
}

/** Perform linear interpolation on two values. 
 @param a Value a.
 @param b Value b.
 @param frac The interpolation fraction, this must be between 0 and 1. 
 @return @f$ a + (frac \times (b - a)) @f$*/
static inline double pl_LinInterpD (double a, double b, double frac)
{
    return a + (frac * (b - a));
}

/** Lookup a value in a table at the given index performing linear interpolation if necessary.
 @param table A pointer to the lookup table.
 @param index The index into the table, the fractional part will be used to perform linear interpolation.
 @return The looked-up value. */
static inline float pl_LookupF (const float* table, float index)
{
    int index0;
	float frac;
	index0 = (int)index;
    frac = index - (float)index0;
    return pl_LinInterpF (table[index0], table[index0 + 1], frac);
}

/** Lookup a value in a table at the given index performing linear interpolation if necessary.
 @param table A pointer to the lookup table.
 @param index The index into the table, the fractional part will be used to perform linear interpolation.
 @return The looked-up value. */
static inline double pl_LookupD (const double* table, double index)
{
    int index0;
	double frac;
	index0 = (int)index;
    frac = index - (double)index0;
    return pl_LinInterpD (table[index0], table[index0 + 1], frac);
}

static inline short pl_LookupS (const short* table, short index) { return table[index]; }
static inline int pl_LookupI (const int* table, int index) { return table[index]; }
static inline PlankLL pl_LookupLL (const PlankLL* table, PlankLL index) { return table[index]; }


static inline float pl_Lag3InterpF (float value_1, float value0, float value1, float value2, float frac)
{    
    float c0 = value0;
    float c1 = value1 - (1.f/3.f) * value_1 - 0.5f * value0 - (1.f/3.f) * value2;
    float c2 = 0.5f * (value_1 + value1) - value0;
    float c3 = (1.f/6.f) * (value2 - value_1) + 0.5f * (value0 - value1);
    return ((c3 * frac + c2) * frac + c1) * frac + c0;
}

static inline float pl_LookupLag3F (const float* table, float index)
{
    int index0, index1, index_1, index2;
    float frac;
    index0 = (int)index;
    index1 = index0 + 1;
    index_1 = index0 - 1;
    index2 = index1 + 1;
    frac = index - (float)index0;
    return pl_Lag3InterpF (table[index_1], table[index0], table[index1], table[index2], frac);
}



/// @} // End group PlankMathsFunctions

#endif // PLANK_MATHS_H

