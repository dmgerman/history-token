macro_line|#ifndef _LINUX_BITOPS_H
DECL|macro|_LINUX_BITOPS_H
mdefine_line|#define _LINUX_BITOPS_H
macro_line|#include &lt;asm/bitops.h&gt;
multiline_comment|/*&n; * ffs: find first bit set. This is defined the same way as&n; * the libc and compiler builtin ffs routines, therefore&n; * differs in spirit from the above ffz (man ffs).&n; */
DECL|function|generic_ffs
r_static
r_inline
r_int
id|generic_ffs
c_func
(paren
r_int
id|x
)paren
(brace
r_int
id|r
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|x
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|x
op_amp
l_int|0xffff
)paren
)paren
(brace
id|x
op_rshift_assign
l_int|16
suffix:semicolon
id|r
op_add_assign
l_int|16
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|x
op_amp
l_int|0xff
)paren
)paren
(brace
id|x
op_rshift_assign
l_int|8
suffix:semicolon
id|r
op_add_assign
l_int|8
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|x
op_amp
l_int|0xf
)paren
)paren
(brace
id|x
op_rshift_assign
l_int|4
suffix:semicolon
id|r
op_add_assign
l_int|4
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|x
op_amp
l_int|3
)paren
)paren
(brace
id|x
op_rshift_assign
l_int|2
suffix:semicolon
id|r
op_add_assign
l_int|2
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|x
op_amp
l_int|1
)paren
)paren
(brace
id|x
op_rshift_assign
l_int|1
suffix:semicolon
id|r
op_add_assign
l_int|1
suffix:semicolon
)brace
r_return
id|r
suffix:semicolon
)brace
multiline_comment|/*&n; * fls: find last bit set.&n; */
DECL|function|generic_fls
r_extern
id|__inline__
r_int
id|generic_fls
c_func
(paren
r_int
id|x
)paren
(brace
r_int
id|r
op_assign
l_int|32
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|x
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|x
op_amp
l_int|0xffff0000
)paren
)paren
(brace
id|x
op_lshift_assign
l_int|16
suffix:semicolon
id|r
op_sub_assign
l_int|16
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|x
op_amp
l_int|0xff000000
)paren
)paren
(brace
id|x
op_lshift_assign
l_int|8
suffix:semicolon
id|r
op_sub_assign
l_int|8
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|x
op_amp
l_int|0xf0000000
)paren
)paren
(brace
id|x
op_lshift_assign
l_int|4
suffix:semicolon
id|r
op_sub_assign
l_int|4
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|x
op_amp
l_int|0xc0000000
)paren
)paren
(brace
id|x
op_lshift_assign
l_int|2
suffix:semicolon
id|r
op_sub_assign
l_int|2
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|x
op_amp
l_int|0x80000000
)paren
)paren
(brace
id|x
op_lshift_assign
l_int|1
suffix:semicolon
id|r
op_sub_assign
l_int|1
suffix:semicolon
)brace
r_return
id|r
suffix:semicolon
)brace
DECL|function|get_bitmask_order
r_extern
id|__inline__
r_int
id|get_bitmask_order
c_func
(paren
r_int
r_int
id|count
)paren
(brace
r_int
id|order
suffix:semicolon
id|order
op_assign
id|fls
c_func
(paren
id|count
)paren
suffix:semicolon
r_return
id|order
suffix:semicolon
multiline_comment|/* We could be slightly more clever with -1 here... */
)brace
multiline_comment|/*&n; * hweightN: returns the hamming weight (i.e. the number&n; * of bits set) of a N-bit word&n; */
DECL|function|generic_hweight32
r_static
r_inline
r_int
r_int
id|generic_hweight32
c_func
(paren
r_int
r_int
id|w
)paren
(brace
r_int
r_int
id|res
op_assign
(paren
id|w
op_amp
l_int|0x55555555
)paren
op_plus
(paren
(paren
id|w
op_rshift
l_int|1
)paren
op_amp
l_int|0x55555555
)paren
suffix:semicolon
id|res
op_assign
(paren
id|res
op_amp
l_int|0x33333333
)paren
op_plus
(paren
(paren
id|res
op_rshift
l_int|2
)paren
op_amp
l_int|0x33333333
)paren
suffix:semicolon
id|res
op_assign
(paren
id|res
op_amp
l_int|0x0F0F0F0F
)paren
op_plus
(paren
(paren
id|res
op_rshift
l_int|4
)paren
op_amp
l_int|0x0F0F0F0F
)paren
suffix:semicolon
id|res
op_assign
(paren
id|res
op_amp
l_int|0x00FF00FF
)paren
op_plus
(paren
(paren
id|res
op_rshift
l_int|8
)paren
op_amp
l_int|0x00FF00FF
)paren
suffix:semicolon
r_return
(paren
id|res
op_amp
l_int|0x0000FFFF
)paren
op_plus
(paren
(paren
id|res
op_rshift
l_int|16
)paren
op_amp
l_int|0x0000FFFF
)paren
suffix:semicolon
)brace
DECL|function|generic_hweight16
r_static
r_inline
r_int
r_int
id|generic_hweight16
c_func
(paren
r_int
r_int
id|w
)paren
(brace
r_int
r_int
id|res
op_assign
(paren
id|w
op_amp
l_int|0x5555
)paren
op_plus
(paren
(paren
id|w
op_rshift
l_int|1
)paren
op_amp
l_int|0x5555
)paren
suffix:semicolon
id|res
op_assign
(paren
id|res
op_amp
l_int|0x3333
)paren
op_plus
(paren
(paren
id|res
op_rshift
l_int|2
)paren
op_amp
l_int|0x3333
)paren
suffix:semicolon
id|res
op_assign
(paren
id|res
op_amp
l_int|0x0F0F
)paren
op_plus
(paren
(paren
id|res
op_rshift
l_int|4
)paren
op_amp
l_int|0x0F0F
)paren
suffix:semicolon
r_return
(paren
id|res
op_amp
l_int|0x00FF
)paren
op_plus
(paren
(paren
id|res
op_rshift
l_int|8
)paren
op_amp
l_int|0x00FF
)paren
suffix:semicolon
)brace
DECL|function|generic_hweight8
r_static
r_inline
r_int
r_int
id|generic_hweight8
c_func
(paren
r_int
r_int
id|w
)paren
(brace
r_int
r_int
id|res
op_assign
(paren
id|w
op_amp
l_int|0x55
)paren
op_plus
(paren
(paren
id|w
op_rshift
l_int|1
)paren
op_amp
l_int|0x55
)paren
suffix:semicolon
id|res
op_assign
(paren
id|res
op_amp
l_int|0x33
)paren
op_plus
(paren
(paren
id|res
op_rshift
l_int|2
)paren
op_amp
l_int|0x33
)paren
suffix:semicolon
r_return
(paren
id|res
op_amp
l_int|0x0F
)paren
op_plus
(paren
(paren
id|res
op_rshift
l_int|4
)paren
op_amp
l_int|0x0F
)paren
suffix:semicolon
)brace
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#endif
eof
