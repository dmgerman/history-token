multiline_comment|/*&n; *  linux/arch/arm/vfp/vfp.h&n; *&n; *  Copyright (C) 2004 ARM Limited.&n; *  Written by Deep Blue Solutions Limited.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
DECL|function|vfp_shiftright32jamming
r_static
r_inline
id|u32
id|vfp_shiftright32jamming
c_func
(paren
id|u32
id|val
comma
r_int
r_int
id|shift
)paren
(brace
r_if
c_cond
(paren
id|shift
)paren
(brace
r_if
c_cond
(paren
id|shift
OL
l_int|32
)paren
id|val
op_assign
id|val
op_rshift
id|shift
op_or
(paren
(paren
id|val
op_lshift
(paren
l_int|32
op_minus
id|shift
)paren
)paren
op_ne
l_int|0
)paren
suffix:semicolon
r_else
id|val
op_assign
id|val
op_ne
l_int|0
suffix:semicolon
)brace
r_return
id|val
suffix:semicolon
)brace
DECL|function|vfp_shiftright64jamming
r_static
r_inline
id|u64
id|vfp_shiftright64jamming
c_func
(paren
id|u64
id|val
comma
r_int
r_int
id|shift
)paren
(brace
r_if
c_cond
(paren
id|shift
)paren
(brace
r_if
c_cond
(paren
id|shift
OL
l_int|64
)paren
id|val
op_assign
id|val
op_rshift
id|shift
op_or
(paren
(paren
id|val
op_lshift
(paren
l_int|64
op_minus
id|shift
)paren
)paren
op_ne
l_int|0
)paren
suffix:semicolon
r_else
id|val
op_assign
id|val
op_ne
l_int|0
suffix:semicolon
)brace
r_return
id|val
suffix:semicolon
)brace
DECL|function|vfp_hi64to32jamming
r_static
r_inline
id|u32
id|vfp_hi64to32jamming
c_func
(paren
id|u64
id|val
)paren
(brace
id|u32
id|v
suffix:semicolon
id|asm
c_func
(paren
l_string|&quot;cmp&t;%Q1, #1&t;&t;@ vfp_hi64to32jamming&bslash;n&bslash;t&quot;
l_string|&quot;movcc&t;%0, %R1&bslash;n&bslash;t&quot;
l_string|&quot;orrcs&t;%0, %R1, #1&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|v
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|val
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_return
id|v
suffix:semicolon
)brace
DECL|function|add128
r_static
r_inline
r_void
id|add128
c_func
(paren
id|u64
op_star
id|resh
comma
id|u64
op_star
id|resl
comma
id|u64
id|nh
comma
id|u64
id|nl
comma
id|u64
id|mh
comma
id|u64
id|ml
)paren
(brace
id|asm
c_func
(paren
l_string|&quot;adds&t;%Q0, %Q2, %Q4&bslash;n&bslash;t&quot;
l_string|&quot;adcs&t;%R0, %R2, %R4&bslash;n&bslash;t&quot;
l_string|&quot;adcs&t;%Q1, %Q3, %Q5&bslash;n&bslash;t&quot;
l_string|&quot;adc&t;%R1, %R3, %R5&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|nl
)paren
comma
l_string|&quot;=r&quot;
(paren
id|nh
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|nl
)paren
comma
l_string|&quot;1&quot;
(paren
id|nh
)paren
comma
l_string|&quot;r&quot;
(paren
id|ml
)paren
comma
l_string|&quot;r&quot;
(paren
id|mh
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
op_star
id|resh
op_assign
id|nh
suffix:semicolon
op_star
id|resl
op_assign
id|nl
suffix:semicolon
)brace
DECL|function|sub128
r_static
r_inline
r_void
id|sub128
c_func
(paren
id|u64
op_star
id|resh
comma
id|u64
op_star
id|resl
comma
id|u64
id|nh
comma
id|u64
id|nl
comma
id|u64
id|mh
comma
id|u64
id|ml
)paren
(brace
id|asm
c_func
(paren
l_string|&quot;subs&t;%Q0, %Q2, %Q4&bslash;n&bslash;t&quot;
l_string|&quot;sbcs&t;%R0, %R2, %R4&bslash;n&bslash;t&quot;
l_string|&quot;sbcs&t;%Q1, %Q3, %Q5&bslash;n&bslash;t&quot;
l_string|&quot;sbc&t;%R1, %R3, %R5&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|nl
)paren
comma
l_string|&quot;=r&quot;
(paren
id|nh
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|nl
)paren
comma
l_string|&quot;1&quot;
(paren
id|nh
)paren
comma
l_string|&quot;r&quot;
(paren
id|ml
)paren
comma
l_string|&quot;r&quot;
(paren
id|mh
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
op_star
id|resh
op_assign
id|nh
suffix:semicolon
op_star
id|resl
op_assign
id|nl
suffix:semicolon
)brace
DECL|function|mul64to128
r_static
r_inline
r_void
id|mul64to128
c_func
(paren
id|u64
op_star
id|resh
comma
id|u64
op_star
id|resl
comma
id|u64
id|n
comma
id|u64
id|m
)paren
(brace
id|u32
id|nh
comma
id|nl
comma
id|mh
comma
id|ml
suffix:semicolon
id|u64
id|rh
comma
id|rma
comma
id|rmb
comma
id|rl
suffix:semicolon
id|nl
op_assign
id|n
suffix:semicolon
id|ml
op_assign
id|m
suffix:semicolon
id|rl
op_assign
(paren
id|u64
)paren
id|nl
op_star
id|ml
suffix:semicolon
id|nh
op_assign
id|n
op_rshift
l_int|32
suffix:semicolon
id|rma
op_assign
(paren
id|u64
)paren
id|nh
op_star
id|ml
suffix:semicolon
id|mh
op_assign
id|m
op_rshift
l_int|32
suffix:semicolon
id|rmb
op_assign
(paren
id|u64
)paren
id|nl
op_star
id|mh
suffix:semicolon
id|rma
op_add_assign
id|rmb
suffix:semicolon
id|rh
op_assign
(paren
id|u64
)paren
id|nh
op_star
id|mh
suffix:semicolon
id|rh
op_add_assign
(paren
(paren
id|u64
)paren
(paren
id|rma
OL
id|rmb
)paren
op_lshift
l_int|32
)paren
op_plus
(paren
id|rma
op_rshift
l_int|32
)paren
suffix:semicolon
id|rma
op_lshift_assign
l_int|32
suffix:semicolon
id|rl
op_add_assign
id|rma
suffix:semicolon
id|rh
op_add_assign
(paren
id|rl
OL
id|rma
)paren
suffix:semicolon
op_star
id|resl
op_assign
id|rl
suffix:semicolon
op_star
id|resh
op_assign
id|rh
suffix:semicolon
)brace
DECL|function|shift64left
r_static
r_inline
r_void
id|shift64left
c_func
(paren
id|u64
op_star
id|resh
comma
id|u64
op_star
id|resl
comma
id|u64
id|n
)paren
(brace
op_star
id|resh
op_assign
id|n
op_rshift
l_int|63
suffix:semicolon
op_star
id|resl
op_assign
id|n
op_lshift
l_int|1
suffix:semicolon
)brace
DECL|function|vfp_hi64multiply64
r_static
r_inline
id|u64
id|vfp_hi64multiply64
c_func
(paren
id|u64
id|n
comma
id|u64
id|m
)paren
(brace
id|u64
id|rh
comma
id|rl
suffix:semicolon
id|mul64to128
c_func
(paren
op_amp
id|rh
comma
op_amp
id|rl
comma
id|n
comma
id|m
)paren
suffix:semicolon
r_return
id|rh
op_or
(paren
id|rl
op_ne
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|vfp_estimate_div128to64
r_static
r_inline
id|u64
id|vfp_estimate_div128to64
c_func
(paren
id|u64
id|nh
comma
id|u64
id|nl
comma
id|u64
id|m
)paren
(brace
id|u64
id|mh
comma
id|ml
comma
id|remh
comma
id|reml
comma
id|termh
comma
id|terml
comma
id|z
suffix:semicolon
r_if
c_cond
(paren
id|nh
op_ge
id|m
)paren
r_return
op_complement
l_int|0ULL
suffix:semicolon
id|mh
op_assign
id|m
op_rshift
l_int|32
suffix:semicolon
id|z
op_assign
(paren
id|mh
op_lshift
l_int|32
op_le
id|nh
)paren
ques
c_cond
l_int|0xffffffff00000000ULL
suffix:colon
(paren
id|nh
op_div
id|mh
)paren
op_lshift
l_int|32
suffix:semicolon
id|mul64to128
c_func
(paren
op_amp
id|termh
comma
op_amp
id|terml
comma
id|m
comma
id|z
)paren
suffix:semicolon
id|sub128
c_func
(paren
op_amp
id|remh
comma
op_amp
id|reml
comma
id|nh
comma
id|nl
comma
id|termh
comma
id|terml
)paren
suffix:semicolon
id|ml
op_assign
id|m
op_lshift
l_int|32
suffix:semicolon
r_while
c_loop
(paren
(paren
id|s64
)paren
id|remh
OL
l_int|0
)paren
(brace
id|z
op_sub_assign
l_int|0x100000000ULL
suffix:semicolon
id|add128
c_func
(paren
op_amp
id|remh
comma
op_amp
id|reml
comma
id|remh
comma
id|reml
comma
id|mh
comma
id|ml
)paren
suffix:semicolon
)brace
id|remh
op_assign
(paren
id|remh
op_lshift
l_int|32
)paren
op_or
(paren
id|reml
op_rshift
l_int|32
)paren
suffix:semicolon
id|z
op_or_assign
(paren
id|mh
op_lshift
l_int|32
op_le
id|remh
)paren
ques
c_cond
l_int|0xffffffff
suffix:colon
id|remh
op_div
id|mh
suffix:semicolon
r_return
id|z
suffix:semicolon
)brace
multiline_comment|/*&n; * Operations on unpacked elements&n; */
DECL|macro|vfp_sign_negate
mdefine_line|#define vfp_sign_negate(sign)&t;(sign ^ 0x8000)
multiline_comment|/*&n; * Single-precision&n; */
DECL|struct|vfp_single
r_struct
id|vfp_single
(brace
DECL|member|exponent
id|s16
id|exponent
suffix:semicolon
DECL|member|sign
id|u16
id|sign
suffix:semicolon
DECL|member|significand
id|u32
id|significand
suffix:semicolon
)brace
suffix:semicolon
r_extern
id|s32
id|vfp_get_float
c_func
(paren
r_int
r_int
id|reg
)paren
suffix:semicolon
r_extern
r_void
id|vfp_put_float
c_func
(paren
r_int
r_int
id|reg
comma
id|s32
id|val
)paren
suffix:semicolon
multiline_comment|/*&n; * VFP_SINGLE_MANTISSA_BITS - number of bits in the mantissa&n; * VFP_SINGLE_EXPONENT_BITS - number of bits in the exponent&n; * VFP_SINGLE_LOW_BITS - number of low bits in the unpacked significand&n; *  which are not propagated to the float upon packing.&n; */
DECL|macro|VFP_SINGLE_MANTISSA_BITS
mdefine_line|#define VFP_SINGLE_MANTISSA_BITS&t;(23)
DECL|macro|VFP_SINGLE_EXPONENT_BITS
mdefine_line|#define VFP_SINGLE_EXPONENT_BITS&t;(8)
DECL|macro|VFP_SINGLE_LOW_BITS
mdefine_line|#define VFP_SINGLE_LOW_BITS&t;&t;(32 - VFP_SINGLE_MANTISSA_BITS - 2)
DECL|macro|VFP_SINGLE_LOW_BITS_MASK
mdefine_line|#define VFP_SINGLE_LOW_BITS_MASK&t;((1 &lt;&lt; VFP_SINGLE_LOW_BITS) - 1)
multiline_comment|/*&n; * The bit in an unpacked float which indicates that it is a quiet NaN&n; */
DECL|macro|VFP_SINGLE_SIGNIFICAND_QNAN
mdefine_line|#define VFP_SINGLE_SIGNIFICAND_QNAN&t;(1 &lt;&lt; (VFP_SINGLE_MANTISSA_BITS - 1 + VFP_SINGLE_LOW_BITS))
multiline_comment|/*&n; * Operations on packed single-precision numbers&n; */
DECL|macro|vfp_single_packed_sign
mdefine_line|#define vfp_single_packed_sign(v)&t;((v) &amp; 0x80000000)
DECL|macro|vfp_single_packed_negate
mdefine_line|#define vfp_single_packed_negate(v)&t;((v) ^ 0x80000000)
DECL|macro|vfp_single_packed_abs
mdefine_line|#define vfp_single_packed_abs(v)&t;((v) &amp; ~0x80000000)
DECL|macro|vfp_single_packed_exponent
mdefine_line|#define vfp_single_packed_exponent(v)&t;(((v) &gt;&gt; VFP_SINGLE_MANTISSA_BITS) &amp; ((1 &lt;&lt; VFP_SINGLE_EXPONENT_BITS) - 1))
DECL|macro|vfp_single_packed_mantissa
mdefine_line|#define vfp_single_packed_mantissa(v)&t;((v) &amp; ((1 &lt;&lt; VFP_SINGLE_MANTISSA_BITS) - 1))
multiline_comment|/*&n; * Unpack a single-precision float.  Note that this returns the magnitude&n; * of the single-precision float mantissa with the 1. if necessary,&n; * aligned to bit 30.&n; */
DECL|function|vfp_single_unpack
r_static
r_inline
r_void
id|vfp_single_unpack
c_func
(paren
r_struct
id|vfp_single
op_star
id|s
comma
id|s32
id|val
)paren
(brace
id|u32
id|significand
suffix:semicolon
id|s-&gt;sign
op_assign
id|vfp_single_packed_sign
c_func
(paren
id|val
)paren
op_rshift
l_int|16
comma
id|s-&gt;exponent
op_assign
id|vfp_single_packed_exponent
c_func
(paren
id|val
)paren
suffix:semicolon
id|significand
op_assign
(paren
id|u32
)paren
id|val
suffix:semicolon
id|significand
op_assign
(paren
id|significand
op_lshift
(paren
l_int|32
op_minus
id|VFP_SINGLE_MANTISSA_BITS
)paren
)paren
op_rshift
l_int|2
suffix:semicolon
r_if
c_cond
(paren
id|s-&gt;exponent
op_logical_and
id|s-&gt;exponent
op_ne
l_int|255
)paren
id|significand
op_or_assign
l_int|0x40000000
suffix:semicolon
id|s-&gt;significand
op_assign
id|significand
suffix:semicolon
)brace
multiline_comment|/*&n; * Re-pack a single-precision float.  This assumes that the float is&n; * already normalised such that the MSB is bit 30, _not_ bit 31.&n; */
DECL|function|vfp_single_pack
r_static
r_inline
id|s32
id|vfp_single_pack
c_func
(paren
r_struct
id|vfp_single
op_star
id|s
)paren
(brace
id|u32
id|val
suffix:semicolon
id|val
op_assign
(paren
id|s-&gt;sign
op_lshift
l_int|16
)paren
op_plus
(paren
id|s-&gt;exponent
op_lshift
id|VFP_SINGLE_MANTISSA_BITS
)paren
op_plus
(paren
id|s-&gt;significand
op_rshift
id|VFP_SINGLE_LOW_BITS
)paren
suffix:semicolon
r_return
(paren
id|s32
)paren
id|val
suffix:semicolon
)brace
DECL|macro|VFP_NUMBER
mdefine_line|#define VFP_NUMBER&t;&t;(1&lt;&lt;0)
DECL|macro|VFP_ZERO
mdefine_line|#define VFP_ZERO&t;&t;(1&lt;&lt;1)
DECL|macro|VFP_DENORMAL
mdefine_line|#define VFP_DENORMAL&t;&t;(1&lt;&lt;2)
DECL|macro|VFP_INFINITY
mdefine_line|#define VFP_INFINITY&t;&t;(1&lt;&lt;3)
DECL|macro|VFP_NAN
mdefine_line|#define VFP_NAN&t;&t;&t;(1&lt;&lt;4)
DECL|macro|VFP_NAN_SIGNAL
mdefine_line|#define VFP_NAN_SIGNAL&t;&t;(1&lt;&lt;5)
DECL|macro|VFP_QNAN
mdefine_line|#define VFP_QNAN&t;&t;(VFP_NAN)
DECL|macro|VFP_SNAN
mdefine_line|#define VFP_SNAN&t;&t;(VFP_NAN|VFP_NAN_SIGNAL)
DECL|function|vfp_single_type
r_static
r_inline
r_int
id|vfp_single_type
c_func
(paren
r_struct
id|vfp_single
op_star
id|s
)paren
(brace
r_int
id|type
op_assign
id|VFP_NUMBER
suffix:semicolon
r_if
c_cond
(paren
id|s-&gt;exponent
op_eq
l_int|255
)paren
(brace
r_if
c_cond
(paren
id|s-&gt;significand
op_eq
l_int|0
)paren
id|type
op_assign
id|VFP_INFINITY
suffix:semicolon
r_else
r_if
c_cond
(paren
id|s-&gt;significand
op_amp
id|VFP_SINGLE_SIGNIFICAND_QNAN
)paren
id|type
op_assign
id|VFP_QNAN
suffix:semicolon
r_else
id|type
op_assign
id|VFP_SNAN
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|s-&gt;exponent
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|s-&gt;significand
op_eq
l_int|0
)paren
id|type
op_or_assign
id|VFP_ZERO
suffix:semicolon
r_else
id|type
op_or_assign
id|VFP_DENORMAL
suffix:semicolon
)brace
r_return
id|type
suffix:semicolon
)brace
macro_line|#ifndef DEBUG
DECL|macro|vfp_single_normaliseround
mdefine_line|#define vfp_single_normaliseround(sd,vsd,fpscr,except,func) __vfp_single_normaliseround(sd,vsd,fpscr,except)
id|u32
id|__vfp_single_normaliseround
c_func
(paren
r_int
id|sd
comma
r_struct
id|vfp_single
op_star
id|vs
comma
id|u32
id|fpscr
comma
id|u32
id|exceptions
)paren
suffix:semicolon
macro_line|#else
id|u32
id|vfp_single_normaliseround
c_func
(paren
r_int
id|sd
comma
r_struct
id|vfp_single
op_star
id|vs
comma
id|u32
id|fpscr
comma
id|u32
id|exceptions
comma
r_const
r_char
op_star
id|func
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * Double-precision&n; */
DECL|struct|vfp_double
r_struct
id|vfp_double
(brace
DECL|member|exponent
id|s16
id|exponent
suffix:semicolon
DECL|member|sign
id|u16
id|sign
suffix:semicolon
DECL|member|significand
id|u64
id|significand
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * VFP_REG_ZERO is a special register number for vfp_get_double&n; * which returns (double)0.0.  This is useful for the compare with&n; * zero instructions.&n; */
DECL|macro|VFP_REG_ZERO
mdefine_line|#define VFP_REG_ZERO&t;16
r_extern
id|u64
id|vfp_get_double
c_func
(paren
r_int
r_int
id|reg
)paren
suffix:semicolon
r_extern
r_void
id|vfp_put_double
c_func
(paren
r_int
r_int
id|reg
comma
id|u64
id|val
)paren
suffix:semicolon
DECL|macro|VFP_DOUBLE_MANTISSA_BITS
mdefine_line|#define VFP_DOUBLE_MANTISSA_BITS&t;(52)
DECL|macro|VFP_DOUBLE_EXPONENT_BITS
mdefine_line|#define VFP_DOUBLE_EXPONENT_BITS&t;(11)
DECL|macro|VFP_DOUBLE_LOW_BITS
mdefine_line|#define VFP_DOUBLE_LOW_BITS&t;&t;(64 - VFP_DOUBLE_MANTISSA_BITS - 2)
DECL|macro|VFP_DOUBLE_LOW_BITS_MASK
mdefine_line|#define VFP_DOUBLE_LOW_BITS_MASK&t;((1 &lt;&lt; VFP_DOUBLE_LOW_BITS) - 1)
multiline_comment|/*&n; * The bit in an unpacked double which indicates that it is a quiet NaN&n; */
DECL|macro|VFP_DOUBLE_SIGNIFICAND_QNAN
mdefine_line|#define VFP_DOUBLE_SIGNIFICAND_QNAN&t;(1ULL &lt;&lt; (VFP_DOUBLE_MANTISSA_BITS - 1 + VFP_DOUBLE_LOW_BITS))
multiline_comment|/*&n; * Operations on packed single-precision numbers&n; */
DECL|macro|vfp_double_packed_sign
mdefine_line|#define vfp_double_packed_sign(v)&t;((v) &amp; (1ULL &lt;&lt; 63))
DECL|macro|vfp_double_packed_negate
mdefine_line|#define vfp_double_packed_negate(v)&t;((v) ^ (1ULL &lt;&lt; 63))
DECL|macro|vfp_double_packed_abs
mdefine_line|#define vfp_double_packed_abs(v)&t;((v) &amp; ~(1ULL &lt;&lt; 63))
DECL|macro|vfp_double_packed_exponent
mdefine_line|#define vfp_double_packed_exponent(v)&t;(((v) &gt;&gt; VFP_DOUBLE_MANTISSA_BITS) &amp; ((1 &lt;&lt; VFP_DOUBLE_EXPONENT_BITS) - 1))
DECL|macro|vfp_double_packed_mantissa
mdefine_line|#define vfp_double_packed_mantissa(v)&t;((v) &amp; ((1ULL &lt;&lt; VFP_DOUBLE_MANTISSA_BITS) - 1))
multiline_comment|/*&n; * Unpack a double-precision float.  Note that this returns the magnitude&n; * of the double-precision float mantissa with the 1. if necessary,&n; * aligned to bit 62.&n; */
DECL|function|vfp_double_unpack
r_static
r_inline
r_void
id|vfp_double_unpack
c_func
(paren
r_struct
id|vfp_double
op_star
id|s
comma
id|s64
id|val
)paren
(brace
id|u64
id|significand
suffix:semicolon
id|s-&gt;sign
op_assign
id|vfp_double_packed_sign
c_func
(paren
id|val
)paren
op_rshift
l_int|48
suffix:semicolon
id|s-&gt;exponent
op_assign
id|vfp_double_packed_exponent
c_func
(paren
id|val
)paren
suffix:semicolon
id|significand
op_assign
(paren
id|u64
)paren
id|val
suffix:semicolon
id|significand
op_assign
(paren
id|significand
op_lshift
(paren
l_int|64
op_minus
id|VFP_DOUBLE_MANTISSA_BITS
)paren
)paren
op_rshift
l_int|2
suffix:semicolon
r_if
c_cond
(paren
id|s-&gt;exponent
op_logical_and
id|s-&gt;exponent
op_ne
l_int|2047
)paren
id|significand
op_or_assign
(paren
l_int|1ULL
op_lshift
l_int|62
)paren
suffix:semicolon
id|s-&gt;significand
op_assign
id|significand
suffix:semicolon
)brace
multiline_comment|/*&n; * Re-pack a double-precision float.  This assumes that the float is&n; * already normalised such that the MSB is bit 30, _not_ bit 31.&n; */
DECL|function|vfp_double_pack
r_static
r_inline
id|s64
id|vfp_double_pack
c_func
(paren
r_struct
id|vfp_double
op_star
id|s
)paren
(brace
id|u64
id|val
suffix:semicolon
id|val
op_assign
(paren
(paren
id|u64
)paren
id|s-&gt;sign
op_lshift
l_int|48
)paren
op_plus
(paren
(paren
id|u64
)paren
id|s-&gt;exponent
op_lshift
id|VFP_DOUBLE_MANTISSA_BITS
)paren
op_plus
(paren
id|s-&gt;significand
op_rshift
id|VFP_DOUBLE_LOW_BITS
)paren
suffix:semicolon
r_return
(paren
id|s64
)paren
id|val
suffix:semicolon
)brace
DECL|function|vfp_double_type
r_static
r_inline
r_int
id|vfp_double_type
c_func
(paren
r_struct
id|vfp_double
op_star
id|s
)paren
(brace
r_int
id|type
op_assign
id|VFP_NUMBER
suffix:semicolon
r_if
c_cond
(paren
id|s-&gt;exponent
op_eq
l_int|2047
)paren
(brace
r_if
c_cond
(paren
id|s-&gt;significand
op_eq
l_int|0
)paren
id|type
op_assign
id|VFP_INFINITY
suffix:semicolon
r_else
r_if
c_cond
(paren
id|s-&gt;significand
op_amp
id|VFP_DOUBLE_SIGNIFICAND_QNAN
)paren
id|type
op_assign
id|VFP_QNAN
suffix:semicolon
r_else
id|type
op_assign
id|VFP_SNAN
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|s-&gt;exponent
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|s-&gt;significand
op_eq
l_int|0
)paren
id|type
op_or_assign
id|VFP_ZERO
suffix:semicolon
r_else
id|type
op_or_assign
id|VFP_DENORMAL
suffix:semicolon
)brace
r_return
id|type
suffix:semicolon
)brace
id|u32
id|vfp_double_normaliseround
c_func
(paren
r_int
id|dd
comma
r_struct
id|vfp_double
op_star
id|vd
comma
id|u32
id|fpscr
comma
id|u32
id|exceptions
comma
r_const
r_char
op_star
id|func
)paren
suffix:semicolon
multiline_comment|/*&n; * System registers&n; */
r_extern
id|u32
id|vfp_get_sys
c_func
(paren
r_int
r_int
id|reg
)paren
suffix:semicolon
r_extern
r_void
id|vfp_put_sys
c_func
(paren
r_int
r_int
id|reg
comma
id|u32
id|val
)paren
suffix:semicolon
id|u32
id|vfp_estimate_sqrt_significand
c_func
(paren
id|u32
id|exponent
comma
id|u32
id|significand
)paren
suffix:semicolon
eof
