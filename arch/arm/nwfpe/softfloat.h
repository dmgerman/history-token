multiline_comment|/*&n;===============================================================================&n;&n;This C header file is part of the SoftFloat IEC/IEEE Floating-point&n;Arithmetic Package, Release 2.&n;&n;Written by John R. Hauser.  This work was made possible in part by the&n;International Computer Science Institute, located at Suite 600, 1947 Center&n;Street, Berkeley, California 94704.  Funding was partially provided by the&n;National Science Foundation under grant MIP-9311980.  The original version&n;of this code was written as part of a project to build a fixed-point vector&n;processor in collaboration with the University of California at Berkeley,&n;overseen by Profs. Nelson Morgan and John Wawrzynek.  More information&n;is available through the Web page `http://HTTP.CS.Berkeley.EDU/~jhauser/&n;arithmetic/softfloat.html&squot;.&n;&n;THIS SOFTWARE IS DISTRIBUTED AS IS, FOR FREE.  Although reasonable effort&n;has been made to avoid it, THIS SOFTWARE MAY CONTAIN FAULTS THAT WILL AT&n;TIMES RESULT IN INCORRECT BEHAVIOR.  USE OF THIS SOFTWARE IS RESTRICTED TO&n;PERSONS AND ORGANIZATIONS WHO CAN AND WILL TAKE FULL RESPONSIBILITY FOR ANY&n;AND ALL LOSSES, COSTS, OR OTHER PROBLEMS ARISING FROM ITS USE.&n;&n;Derivative works are acceptable, even for commercial purposes, so long as&n;(1) they include prominent notice that the work is derivative, and (2) they&n;include prominent notice akin to these three paragraphs for those parts of&n;this code that are retained.&n;&n;===============================================================================&n;*/
macro_line|#ifndef __SOFTFLOAT_H__
DECL|macro|__SOFTFLOAT_H__
mdefine_line|#define __SOFTFLOAT_H__
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/*&n;-------------------------------------------------------------------------------&n;The macro `FLOATX80&squot; must be defined to enable the extended double-precision&n;floating-point format `floatx80&squot;.  If this macro is not defined, the&n;`floatx80&squot; type will not be defined, and none of the functions that either&n;input or output the `floatx80&squot; type will be defined.&n;-------------------------------------------------------------------------------&n;*/
macro_line|#ifdef CONFIG_FPE_NWFPE_XP
DECL|macro|FLOATX80
mdefine_line|#define FLOATX80
macro_line|#endif
multiline_comment|/*&n;-------------------------------------------------------------------------------&n;Software IEC/IEEE floating-point types.&n;-------------------------------------------------------------------------------&n;*/
DECL|typedef|float32
r_typedef
r_int
r_int
r_int
id|float32
suffix:semicolon
DECL|typedef|float64
r_typedef
r_int
r_int
r_int
id|float64
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|high
r_int
r_int
id|high
suffix:semicolon
DECL|member|low
r_int
r_int
r_int
id|low
suffix:semicolon
DECL|typedef|floatx80
)brace
id|floatx80
suffix:semicolon
multiline_comment|/*&n;-------------------------------------------------------------------------------&n;Software IEC/IEEE floating-point underflow tininess-detection mode.&n;-------------------------------------------------------------------------------&n;*/
r_extern
r_int
r_char
id|float_detect_tininess
suffix:semicolon
r_enum
(brace
DECL|enumerator|float_tininess_after_rounding
id|float_tininess_after_rounding
op_assign
l_int|0
comma
DECL|enumerator|float_tininess_before_rounding
id|float_tininess_before_rounding
op_assign
l_int|1
)brace
suffix:semicolon
multiline_comment|/*&n;-------------------------------------------------------------------------------&n;Software IEC/IEEE floating-point rounding mode.&n;-------------------------------------------------------------------------------&n;*/
r_extern
r_int
r_char
id|float_rounding_mode
suffix:semicolon
r_enum
(brace
DECL|enumerator|float_round_nearest_even
id|float_round_nearest_even
op_assign
l_int|0
comma
DECL|enumerator|float_round_to_zero
id|float_round_to_zero
op_assign
l_int|1
comma
DECL|enumerator|float_round_down
id|float_round_down
op_assign
l_int|2
comma
DECL|enumerator|float_round_up
id|float_round_up
op_assign
l_int|3
)brace
suffix:semicolon
multiline_comment|/*&n;-------------------------------------------------------------------------------&n;Software IEC/IEEE floating-point exception flags.&n;-------------------------------------------------------------------------------&n;extern signed char float_exception_flags;&n;enum {&n;    float_flag_inexact   =  1,&n;    float_flag_underflow =  2,&n;    float_flag_overflow  =  4,&n;    float_flag_divbyzero =  8,&n;    float_flag_invalid   = 16&n;};&n;&n;ScottB: November 4, 1998&n;Changed the enumeration to match the bit order in the FPA11.&n;*/
r_extern
r_int
r_char
id|float_exception_flags
suffix:semicolon
r_enum
(brace
DECL|enumerator|float_flag_invalid
id|float_flag_invalid
op_assign
l_int|1
comma
DECL|enumerator|float_flag_divbyzero
id|float_flag_divbyzero
op_assign
l_int|2
comma
DECL|enumerator|float_flag_overflow
id|float_flag_overflow
op_assign
l_int|4
comma
DECL|enumerator|float_flag_underflow
id|float_flag_underflow
op_assign
l_int|8
comma
DECL|enumerator|float_flag_inexact
id|float_flag_inexact
op_assign
l_int|16
)brace
suffix:semicolon
multiline_comment|/*&n;-------------------------------------------------------------------------------&n;Routine to raise any or all of the software IEC/IEEE floating-point&n;exception flags.&n;-------------------------------------------------------------------------------&n;*/
r_void
id|float_raise
c_func
(paren
r_int
r_char
)paren
suffix:semicolon
multiline_comment|/*&n;-------------------------------------------------------------------------------&n;Software IEC/IEEE integer-to-floating-point conversion routines.&n;-------------------------------------------------------------------------------&n;*/
id|float32
id|int32_to_float32
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
id|float64
id|int32_to_float64
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
macro_line|#ifdef FLOATX80
id|floatx80
id|int32_to_floatx80
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;-------------------------------------------------------------------------------&n;Software IEC/IEEE single-precision conversion routines.&n;-------------------------------------------------------------------------------&n;*/
r_int
r_int
id|float32_to_int32
c_func
(paren
id|float32
)paren
suffix:semicolon
r_int
r_int
id|float32_to_int32_round_to_zero
c_func
(paren
id|float32
)paren
suffix:semicolon
id|float64
id|float32_to_float64
c_func
(paren
id|float32
)paren
suffix:semicolon
macro_line|#ifdef FLOATX80
id|floatx80
id|float32_to_floatx80
c_func
(paren
id|float32
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;-------------------------------------------------------------------------------&n;Software IEC/IEEE single-precision operations.&n;-------------------------------------------------------------------------------&n;*/
id|float32
id|float32_round_to_int
c_func
(paren
id|float32
)paren
suffix:semicolon
id|float32
id|float32_add
c_func
(paren
id|float32
comma
id|float32
)paren
suffix:semicolon
id|float32
id|float32_sub
c_func
(paren
id|float32
comma
id|float32
)paren
suffix:semicolon
id|float32
id|float32_mul
c_func
(paren
id|float32
comma
id|float32
)paren
suffix:semicolon
id|float32
id|float32_div
c_func
(paren
id|float32
comma
id|float32
)paren
suffix:semicolon
id|float32
id|float32_rem
c_func
(paren
id|float32
comma
id|float32
)paren
suffix:semicolon
id|float32
id|float32_sqrt
c_func
(paren
id|float32
)paren
suffix:semicolon
r_char
id|float32_eq
c_func
(paren
id|float32
comma
id|float32
)paren
suffix:semicolon
r_char
id|float32_le
c_func
(paren
id|float32
comma
id|float32
)paren
suffix:semicolon
r_char
id|float32_lt
c_func
(paren
id|float32
comma
id|float32
)paren
suffix:semicolon
r_char
id|float32_eq_signaling
c_func
(paren
id|float32
comma
id|float32
)paren
suffix:semicolon
r_char
id|float32_le_quiet
c_func
(paren
id|float32
comma
id|float32
)paren
suffix:semicolon
r_char
id|float32_lt_quiet
c_func
(paren
id|float32
comma
id|float32
)paren
suffix:semicolon
r_char
id|float32_is_signaling_nan
c_func
(paren
id|float32
)paren
suffix:semicolon
multiline_comment|/*&n;-------------------------------------------------------------------------------&n;Software IEC/IEEE double-precision conversion routines.&n;-------------------------------------------------------------------------------&n;*/
r_int
r_int
id|float64_to_int32
c_func
(paren
id|float64
)paren
suffix:semicolon
r_int
r_int
id|float64_to_int32_round_to_zero
c_func
(paren
id|float64
)paren
suffix:semicolon
id|float32
id|float64_to_float32
c_func
(paren
id|float64
)paren
suffix:semicolon
macro_line|#ifdef FLOATX80
id|floatx80
id|float64_to_floatx80
c_func
(paren
id|float64
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;-------------------------------------------------------------------------------&n;Software IEC/IEEE double-precision operations.&n;-------------------------------------------------------------------------------&n;*/
id|float64
id|float64_round_to_int
c_func
(paren
id|float64
)paren
suffix:semicolon
id|float64
id|float64_add
c_func
(paren
id|float64
comma
id|float64
)paren
suffix:semicolon
id|float64
id|float64_sub
c_func
(paren
id|float64
comma
id|float64
)paren
suffix:semicolon
id|float64
id|float64_mul
c_func
(paren
id|float64
comma
id|float64
)paren
suffix:semicolon
id|float64
id|float64_div
c_func
(paren
id|float64
comma
id|float64
)paren
suffix:semicolon
id|float64
id|float64_rem
c_func
(paren
id|float64
comma
id|float64
)paren
suffix:semicolon
id|float64
id|float64_sqrt
c_func
(paren
id|float64
)paren
suffix:semicolon
r_char
id|float64_eq
c_func
(paren
id|float64
comma
id|float64
)paren
suffix:semicolon
r_char
id|float64_le
c_func
(paren
id|float64
comma
id|float64
)paren
suffix:semicolon
r_char
id|float64_lt
c_func
(paren
id|float64
comma
id|float64
)paren
suffix:semicolon
r_char
id|float64_eq_signaling
c_func
(paren
id|float64
comma
id|float64
)paren
suffix:semicolon
r_char
id|float64_le_quiet
c_func
(paren
id|float64
comma
id|float64
)paren
suffix:semicolon
r_char
id|float64_lt_quiet
c_func
(paren
id|float64
comma
id|float64
)paren
suffix:semicolon
r_char
id|float64_is_signaling_nan
c_func
(paren
id|float64
)paren
suffix:semicolon
macro_line|#ifdef FLOATX80
multiline_comment|/*&n;-------------------------------------------------------------------------------&n;Software IEC/IEEE extended double-precision conversion routines.&n;-------------------------------------------------------------------------------&n;*/
r_int
r_int
id|floatx80_to_int32
c_func
(paren
id|floatx80
)paren
suffix:semicolon
r_int
r_int
id|floatx80_to_int32_round_to_zero
c_func
(paren
id|floatx80
)paren
suffix:semicolon
id|float32
id|floatx80_to_float32
c_func
(paren
id|floatx80
)paren
suffix:semicolon
id|float64
id|floatx80_to_float64
c_func
(paren
id|floatx80
)paren
suffix:semicolon
multiline_comment|/*&n;-------------------------------------------------------------------------------&n;Software IEC/IEEE extended double-precision rounding precision.  Valid&n;values are 32, 64, and 80.&n;-------------------------------------------------------------------------------&n;*/
r_extern
r_int
r_char
id|floatx80_rounding_precision
suffix:semicolon
multiline_comment|/*&n;-------------------------------------------------------------------------------&n;Software IEC/IEEE extended double-precision operations.&n;-------------------------------------------------------------------------------&n;*/
id|floatx80
id|floatx80_round_to_int
c_func
(paren
id|floatx80
)paren
suffix:semicolon
id|floatx80
id|floatx80_add
c_func
(paren
id|floatx80
comma
id|floatx80
)paren
suffix:semicolon
id|floatx80
id|floatx80_sub
c_func
(paren
id|floatx80
comma
id|floatx80
)paren
suffix:semicolon
id|floatx80
id|floatx80_mul
c_func
(paren
id|floatx80
comma
id|floatx80
)paren
suffix:semicolon
id|floatx80
id|floatx80_div
c_func
(paren
id|floatx80
comma
id|floatx80
)paren
suffix:semicolon
id|floatx80
id|floatx80_rem
c_func
(paren
id|floatx80
comma
id|floatx80
)paren
suffix:semicolon
id|floatx80
id|floatx80_sqrt
c_func
(paren
id|floatx80
)paren
suffix:semicolon
r_char
id|floatx80_eq
c_func
(paren
id|floatx80
comma
id|floatx80
)paren
suffix:semicolon
r_char
id|floatx80_le
c_func
(paren
id|floatx80
comma
id|floatx80
)paren
suffix:semicolon
r_char
id|floatx80_lt
c_func
(paren
id|floatx80
comma
id|floatx80
)paren
suffix:semicolon
r_char
id|floatx80_eq_signaling
c_func
(paren
id|floatx80
comma
id|floatx80
)paren
suffix:semicolon
r_char
id|floatx80_le_quiet
c_func
(paren
id|floatx80
comma
id|floatx80
)paren
suffix:semicolon
r_char
id|floatx80_lt_quiet
c_func
(paren
id|floatx80
comma
id|floatx80
)paren
suffix:semicolon
r_char
id|floatx80_is_signaling_nan
c_func
(paren
id|floatx80
)paren
suffix:semicolon
macro_line|#endif
DECL|function|extractFloat32Sign
r_static
r_inline
id|flag
id|extractFloat32Sign
c_func
(paren
id|float32
id|a
)paren
(brace
r_return
id|a
op_rshift
l_int|31
suffix:semicolon
)brace
DECL|function|float32_eq_nocheck
r_static
r_inline
id|flag
id|float32_eq_nocheck
c_func
(paren
id|float32
id|a
comma
id|float32
id|b
)paren
(brace
r_return
(paren
id|a
op_eq
id|b
)paren
op_logical_or
(paren
(paren
id|bits32
)paren
(paren
(paren
id|a
op_or
id|b
)paren
op_lshift
l_int|1
)paren
op_eq
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|float32_lt_nocheck
r_static
r_inline
id|flag
id|float32_lt_nocheck
c_func
(paren
id|float32
id|a
comma
id|float32
id|b
)paren
(brace
id|flag
id|aSign
comma
id|bSign
suffix:semicolon
id|aSign
op_assign
id|extractFloat32Sign
c_func
(paren
id|a
)paren
suffix:semicolon
id|bSign
op_assign
id|extractFloat32Sign
c_func
(paren
id|b
)paren
suffix:semicolon
r_if
c_cond
(paren
id|aSign
op_ne
id|bSign
)paren
r_return
id|aSign
op_logical_and
(paren
(paren
id|bits32
)paren
(paren
(paren
id|a
op_or
id|b
)paren
op_lshift
l_int|1
)paren
op_ne
l_int|0
)paren
suffix:semicolon
r_return
(paren
id|a
op_ne
id|b
)paren
op_logical_and
(paren
id|aSign
op_xor
(paren
id|a
OL
id|b
)paren
)paren
suffix:semicolon
)brace
DECL|function|extractFloat64Sign
r_static
r_inline
id|flag
id|extractFloat64Sign
c_func
(paren
id|float64
id|a
)paren
(brace
r_return
id|a
op_rshift
l_int|63
suffix:semicolon
)brace
DECL|function|float64_eq_nocheck
r_static
r_inline
id|flag
id|float64_eq_nocheck
c_func
(paren
id|float64
id|a
comma
id|float64
id|b
)paren
(brace
r_return
(paren
id|a
op_eq
id|b
)paren
op_logical_or
(paren
(paren
id|bits64
)paren
(paren
(paren
id|a
op_or
id|b
)paren
op_lshift
l_int|1
)paren
op_eq
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|float64_lt_nocheck
r_static
r_inline
id|flag
id|float64_lt_nocheck
c_func
(paren
id|float64
id|a
comma
id|float64
id|b
)paren
(brace
id|flag
id|aSign
comma
id|bSign
suffix:semicolon
id|aSign
op_assign
id|extractFloat64Sign
c_func
(paren
id|a
)paren
suffix:semicolon
id|bSign
op_assign
id|extractFloat64Sign
c_func
(paren
id|b
)paren
suffix:semicolon
r_if
c_cond
(paren
id|aSign
op_ne
id|bSign
)paren
r_return
id|aSign
op_logical_and
(paren
(paren
id|bits64
)paren
(paren
(paren
id|a
op_or
id|b
)paren
op_lshift
l_int|1
)paren
op_ne
l_int|0
)paren
suffix:semicolon
r_return
(paren
id|a
op_ne
id|b
)paren
op_logical_and
(paren
id|aSign
op_xor
(paren
id|a
OL
id|b
)paren
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
