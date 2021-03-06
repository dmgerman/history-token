multiline_comment|/*&n;&n;  fp_trig.c: floating-point math routines for the Linux-m68k&n;  floating point emulator.&n;&n;  Copyright (c) 1998-1999 David Huggins-Daines / Roman Zippel.&n;&n;  I hereby give permission, free of charge, to copy, modify, and&n;  redistribute this software, in source or binary form, provided that&n;  the above copyright notice and the following disclaimer are included&n;  in all such copies.&n;&n;  THIS SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITH ABSOLUTELY NO WARRANTY, REAL&n;  OR IMPLIED.&n;&n;*/
macro_line|#include &quot;fp_emu.h&quot;
DECL|variable|fp_one
r_static
r_const
r_struct
id|fp_ext
id|fp_one
op_assign
(brace
dot
id|exp
op_assign
l_int|0x3fff
comma
)brace
suffix:semicolon
r_extern
r_struct
id|fp_ext
op_star
id|fp_fadd
c_func
(paren
r_struct
id|fp_ext
op_star
id|dest
comma
r_const
r_struct
id|fp_ext
op_star
id|src
)paren
suffix:semicolon
r_extern
r_struct
id|fp_ext
op_star
id|fp_fdiv
c_func
(paren
r_struct
id|fp_ext
op_star
id|dest
comma
r_const
r_struct
id|fp_ext
op_star
id|src
)paren
suffix:semicolon
r_extern
r_struct
id|fp_ext
op_star
id|fp_fmul
c_func
(paren
r_struct
id|fp_ext
op_star
id|dest
comma
r_const
r_struct
id|fp_ext
op_star
id|src
)paren
suffix:semicolon
r_struct
id|fp_ext
op_star
DECL|function|fp_fsqrt
id|fp_fsqrt
c_func
(paren
r_struct
id|fp_ext
op_star
id|dest
comma
r_struct
id|fp_ext
op_star
id|src
)paren
(brace
r_struct
id|fp_ext
id|tmp
comma
id|src2
suffix:semicolon
r_int
id|i
comma
id|exp
suffix:semicolon
id|dprint
c_func
(paren
id|PINSTR
comma
l_string|&quot;fsqrt&bslash;n&quot;
)paren
suffix:semicolon
id|fp_monadic_check
c_func
(paren
id|dest
comma
id|src
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ZERO
c_func
(paren
id|dest
)paren
)paren
r_return
id|dest
suffix:semicolon
r_if
c_cond
(paren
id|dest-&gt;sign
)paren
(brace
id|fp_set_nan
c_func
(paren
id|dest
)paren
suffix:semicolon
r_return
id|dest
suffix:semicolon
)brace
r_if
c_cond
(paren
id|IS_INF
c_func
(paren
id|dest
)paren
)paren
r_return
id|dest
suffix:semicolon
multiline_comment|/*&n;&t; *&t;&t; sqrt(m) * 2^(p)&t;, if e = 2*p&n;&t; * sqrt(m*2^e) =&n;&t; *&t;&t; sqrt(2*m) * 2^(p)&t;, if e = 2*p + 1&n;&t; *&n;&t; * So we use the last bit of the exponent to decide wether to&n;&t; * use the m or 2*m.&n;&t; *&n;&t; * Since only the fractional part of the mantissa is stored and&n;&t; * the integer part is assumed to be one, we place a 1 or 2 into&n;&t; * the fixed point representation.&n;&t; */
id|exp
op_assign
id|dest-&gt;exp
suffix:semicolon
id|dest-&gt;exp
op_assign
l_int|0x3FFF
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|exp
op_amp
l_int|1
)paren
)paren
multiline_comment|/* lowest bit of exponent is set */
id|dest-&gt;exp
op_increment
suffix:semicolon
id|fp_copy_ext
c_func
(paren
op_amp
id|src2
comma
id|dest
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * The taylor row arround a for sqrt(x) is:&n;&t; *&t;sqrt(x) = sqrt(a) + 1/(2*sqrt(a))*(x-a) + R&n;&t; * With a=1 this gives:&n;&t; *&t;sqrt(x) = 1 + 1/2*(x-1)&n;&t; *&t;&t;= 1/2*(1+x)&n;&t; */
id|fp_fadd
c_func
(paren
id|dest
comma
op_amp
id|fp_one
)paren
suffix:semicolon
id|dest-&gt;exp
op_decrement
suffix:semicolon
multiline_comment|/* * 1/2 */
multiline_comment|/*&n;&t; * We now apply the newton rule to the function&n;&t; *&t;f(x) := x^2 - r&n;&t; * which has a null point on x = sqrt(r).&n;&t; *&n;&t; * It gives:&n;&t; *&t;x&squot; := x - f(x)/f&squot;(x)&n;&t; *&t;    = x - (x^2 -r)/(2*x)&n;&t; *&t;    = x - (x - r/x)/2&n;&t; *          = (2*x - x + r/x)/2&n;&t; *&t;    = (x + r/x)/2&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|9
suffix:semicolon
id|i
op_increment
)paren
(brace
id|fp_copy_ext
c_func
(paren
op_amp
id|tmp
comma
op_amp
id|src2
)paren
suffix:semicolon
id|fp_fdiv
c_func
(paren
op_amp
id|tmp
comma
id|dest
)paren
suffix:semicolon
id|fp_fadd
c_func
(paren
id|dest
comma
op_amp
id|tmp
)paren
suffix:semicolon
id|dest-&gt;exp
op_decrement
suffix:semicolon
)brace
id|dest-&gt;exp
op_add_assign
(paren
id|exp
op_minus
l_int|0x3FFF
)paren
op_div
l_int|2
suffix:semicolon
r_return
id|dest
suffix:semicolon
)brace
r_struct
id|fp_ext
op_star
DECL|function|fp_fetoxm1
id|fp_fetoxm1
c_func
(paren
r_struct
id|fp_ext
op_star
id|dest
comma
r_struct
id|fp_ext
op_star
id|src
)paren
(brace
id|uprint
c_func
(paren
l_string|&quot;fetoxm1&bslash;n&quot;
)paren
suffix:semicolon
id|fp_monadic_check
c_func
(paren
id|dest
comma
id|src
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ZERO
c_func
(paren
id|dest
)paren
)paren
r_return
id|dest
suffix:semicolon
r_return
id|dest
suffix:semicolon
)brace
r_struct
id|fp_ext
op_star
DECL|function|fp_fetox
id|fp_fetox
c_func
(paren
r_struct
id|fp_ext
op_star
id|dest
comma
r_struct
id|fp_ext
op_star
id|src
)paren
(brace
id|uprint
c_func
(paren
l_string|&quot;fetox&bslash;n&quot;
)paren
suffix:semicolon
id|fp_monadic_check
c_func
(paren
id|dest
comma
id|src
)paren
suffix:semicolon
r_return
id|dest
suffix:semicolon
)brace
r_struct
id|fp_ext
op_star
DECL|function|fp_ftwotox
id|fp_ftwotox
c_func
(paren
r_struct
id|fp_ext
op_star
id|dest
comma
r_struct
id|fp_ext
op_star
id|src
)paren
(brace
id|uprint
c_func
(paren
l_string|&quot;ftwotox&bslash;n&quot;
)paren
suffix:semicolon
id|fp_monadic_check
c_func
(paren
id|dest
comma
id|src
)paren
suffix:semicolon
r_return
id|dest
suffix:semicolon
)brace
r_struct
id|fp_ext
op_star
DECL|function|fp_ftentox
id|fp_ftentox
c_func
(paren
r_struct
id|fp_ext
op_star
id|dest
comma
r_struct
id|fp_ext
op_star
id|src
)paren
(brace
id|uprint
c_func
(paren
l_string|&quot;ftentox&bslash;n&quot;
)paren
suffix:semicolon
id|fp_monadic_check
c_func
(paren
id|dest
comma
id|src
)paren
suffix:semicolon
r_return
id|dest
suffix:semicolon
)brace
r_struct
id|fp_ext
op_star
DECL|function|fp_flogn
id|fp_flogn
c_func
(paren
r_struct
id|fp_ext
op_star
id|dest
comma
r_struct
id|fp_ext
op_star
id|src
)paren
(brace
id|uprint
c_func
(paren
l_string|&quot;flogn&bslash;n&quot;
)paren
suffix:semicolon
id|fp_monadic_check
c_func
(paren
id|dest
comma
id|src
)paren
suffix:semicolon
r_return
id|dest
suffix:semicolon
)brace
r_struct
id|fp_ext
op_star
DECL|function|fp_flognp1
id|fp_flognp1
c_func
(paren
r_struct
id|fp_ext
op_star
id|dest
comma
r_struct
id|fp_ext
op_star
id|src
)paren
(brace
id|uprint
c_func
(paren
l_string|&quot;flognp1&bslash;n&quot;
)paren
suffix:semicolon
id|fp_monadic_check
c_func
(paren
id|dest
comma
id|src
)paren
suffix:semicolon
r_return
id|dest
suffix:semicolon
)brace
r_struct
id|fp_ext
op_star
DECL|function|fp_flog10
id|fp_flog10
c_func
(paren
r_struct
id|fp_ext
op_star
id|dest
comma
r_struct
id|fp_ext
op_star
id|src
)paren
(brace
id|uprint
c_func
(paren
l_string|&quot;flog10&bslash;n&quot;
)paren
suffix:semicolon
id|fp_monadic_check
c_func
(paren
id|dest
comma
id|src
)paren
suffix:semicolon
r_return
id|dest
suffix:semicolon
)brace
r_struct
id|fp_ext
op_star
DECL|function|fp_flog2
id|fp_flog2
c_func
(paren
r_struct
id|fp_ext
op_star
id|dest
comma
r_struct
id|fp_ext
op_star
id|src
)paren
(brace
id|uprint
c_func
(paren
l_string|&quot;flog2&bslash;n&quot;
)paren
suffix:semicolon
id|fp_monadic_check
c_func
(paren
id|dest
comma
id|src
)paren
suffix:semicolon
r_return
id|dest
suffix:semicolon
)brace
r_struct
id|fp_ext
op_star
DECL|function|fp_fgetexp
id|fp_fgetexp
c_func
(paren
r_struct
id|fp_ext
op_star
id|dest
comma
r_struct
id|fp_ext
op_star
id|src
)paren
(brace
id|dprint
c_func
(paren
id|PINSTR
comma
l_string|&quot;fgetexp&bslash;n&quot;
)paren
suffix:semicolon
id|fp_monadic_check
c_func
(paren
id|dest
comma
id|src
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_INF
c_func
(paren
id|dest
)paren
)paren
(brace
id|fp_set_nan
c_func
(paren
id|dest
)paren
suffix:semicolon
r_return
id|dest
suffix:semicolon
)brace
r_if
c_cond
(paren
id|IS_ZERO
c_func
(paren
id|dest
)paren
)paren
r_return
id|dest
suffix:semicolon
id|fp_conv_long2ext
c_func
(paren
id|dest
comma
(paren
r_int
)paren
id|dest-&gt;exp
op_minus
l_int|0x3FFF
)paren
suffix:semicolon
id|fp_normalize_ext
c_func
(paren
id|dest
)paren
suffix:semicolon
r_return
id|dest
suffix:semicolon
)brace
r_struct
id|fp_ext
op_star
DECL|function|fp_fgetman
id|fp_fgetman
c_func
(paren
r_struct
id|fp_ext
op_star
id|dest
comma
r_struct
id|fp_ext
op_star
id|src
)paren
(brace
id|dprint
c_func
(paren
id|PINSTR
comma
l_string|&quot;fgetman&bslash;n&quot;
)paren
suffix:semicolon
id|fp_monadic_check
c_func
(paren
id|dest
comma
id|src
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ZERO
c_func
(paren
id|dest
)paren
)paren
r_return
id|dest
suffix:semicolon
r_if
c_cond
(paren
id|IS_INF
c_func
(paren
id|dest
)paren
)paren
r_return
id|dest
suffix:semicolon
id|dest-&gt;exp
op_assign
l_int|0x3FFF
suffix:semicolon
r_return
id|dest
suffix:semicolon
)brace
eof
