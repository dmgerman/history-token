macro_line|#ifndef _ASM_GENERIC_BITOPS_H_
DECL|macro|_ASM_GENERIC_BITOPS_H_
mdefine_line|#define _ASM_GENERIC_BITOPS_H_
multiline_comment|/*&n; * For the benefit of those who are trying to port Linux to another&n; * architecture, here are some C-language equivalents.  You should&n; * recode these in the native assembly language, if at all possible.&n; * To guarantee atomicity, these routines call cli() and sti() to&n; * disable interrupts while they operate.  (You have to provide inline&n; * routines to cli() and sti().)&n; *&n; * Also note, these routines assume that you have 32 bit longs.&n; * You will have to change this if you are trying to port Linux to the&n; * Alpha architecture or to a Cray.  :-)&n; * &n; * C language equivalents written by Theodore Ts&squot;o, 9/26/92&n; */
DECL|function|set_bit
r_extern
id|__inline__
r_int
id|set_bit
c_func
(paren
r_int
id|nr
comma
r_int
op_star
id|addr
)paren
(brace
r_int
id|mask
comma
id|retval
suffix:semicolon
id|addr
op_add_assign
id|nr
op_rshift
l_int|5
suffix:semicolon
id|mask
op_assign
l_int|1
op_lshift
(paren
id|nr
op_amp
l_int|0x1f
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
id|retval
op_assign
(paren
id|mask
op_amp
op_star
id|addr
)paren
op_ne
l_int|0
suffix:semicolon
op_star
id|addr
op_or_assign
id|mask
suffix:semicolon
id|sti
c_func
(paren
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|clear_bit
r_extern
id|__inline__
r_int
id|clear_bit
c_func
(paren
r_int
id|nr
comma
r_int
op_star
id|addr
)paren
(brace
r_int
id|mask
comma
id|retval
suffix:semicolon
id|addr
op_add_assign
id|nr
op_rshift
l_int|5
suffix:semicolon
id|mask
op_assign
l_int|1
op_lshift
(paren
id|nr
op_amp
l_int|0x1f
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
id|retval
op_assign
(paren
id|mask
op_amp
op_star
id|addr
)paren
op_ne
l_int|0
suffix:semicolon
op_star
id|addr
op_and_assign
op_complement
id|mask
suffix:semicolon
id|sti
c_func
(paren
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|test_bit
r_extern
id|__inline__
r_int
id|test_bit
c_func
(paren
r_int
id|nr
comma
r_const
r_int
r_int
op_star
id|addr
)paren
(brace
r_int
id|mask
suffix:semicolon
id|addr
op_add_assign
id|nr
op_rshift
l_int|5
suffix:semicolon
id|mask
op_assign
l_int|1
op_lshift
(paren
id|nr
op_amp
l_int|0x1f
)paren
suffix:semicolon
r_return
(paren
(paren
id|mask
op_amp
op_star
id|addr
)paren
op_ne
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * fls: find last bit set.&n; */
DECL|macro|fls
mdefine_line|#define fls(x) generic_fls(x)
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * ffs: find first bit set. This is defined the same way as&n; * the libc and compiler builtin ffs routines, therefore&n; * differs in spirit from the above ffz (man ffs).&n; */
DECL|macro|ffs
mdefine_line|#define ffs(x) generic_ffs(x)
multiline_comment|/*&n; * hweightN: returns the hamming weight (i.e. the number&n; * of bits set) of a N-bit word&n; */
DECL|macro|hweight32
mdefine_line|#define hweight32(x) generic_hweight32(x)
DECL|macro|hweight16
mdefine_line|#define hweight16(x) generic_hweight16(x)
DECL|macro|hweight8
mdefine_line|#define hweight8(x) generic_hweight8(x)
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _ASM_GENERIC_BITOPS_H */
eof
