macro_line|#ifndef _ASM_GENERIC_DIV64_H
DECL|macro|_ASM_GENERIC_DIV64_H
mdefine_line|#define _ASM_GENERIC_DIV64_H
multiline_comment|/*&n; * Copyright (C) 2003 Bernardo Innocenti &lt;bernie@develer.com&gt;&n; * Based on former asm-ppc/div64.h and asm-m68knommu/div64.h&n; *&n; * The semantics of do_div() are:&n; *&n; * uint32_t do_div(uint64_t *n, uint32_t base)&n; * {&n; * &t;uint32_t remainder = *n % base;&n; * &t;*n = *n / base;&n; * &t;return remainder;&n; * }&n; *&n; * NOTE: macro parameter n is evaluated multiple times,&n; *       beware of side effects!&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#if BITS_PER_LONG == 64
DECL|macro|do_div
macro_line|# define do_div(n,base) ({&t;&t;&t;&t;&t;&bslash;&n;&t;uint32_t __base = (base);&t;&t;&t;&t;&bslash;&n;&t;uint32_t __rem;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__rem = ((uint64_t)(n)) % __base;&t;&t;&t;&bslash;&n;&t;(n) = ((uint64_t)(n)) / __base;&t;&t;&t;&t;&bslash;&n;&t;__rem;&t;&t;&t;&t;&t;&t;&t;&bslash;&n; })
macro_line|#elif BITS_PER_LONG == 32
r_extern
r_uint32
id|__div64_32
c_func
(paren
r_uint64
op_star
id|dividend
comma
r_uint32
id|divisor
)paren
suffix:semicolon
DECL|macro|do_div
macro_line|# define do_div(n,base) ({&t;&t;&t;&t;&bslash;&n;&t;uint32_t __base = (base);&t;&t;&t;&bslash;&n;&t;uint32_t __rem;&t;&t;&t;&t;&t;&bslash;&n;&t;if (((n) &gt;&gt; 32) == 0) {&t;&t;&t;&t;&bslash;&n;&t;&t;__rem = (uint32_t)(n) % __base;&t;&t;&bslash;&n;&t;&t;(n) = (uint32_t)(n) / __base;&t;&t;&bslash;&n;&t;} else &t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__rem = __div64_32(&amp;(n), __base);&t;&bslash;&n;&t;__rem;&t;&t;&t;&t;&t;&t;&bslash;&n; })
macro_line|#else /* BITS_PER_LONG == ?? */
macro_line|# error do_div() does not yet support the C64
macro_line|#endif /* BITS_PER_LONG */
macro_line|#endif /* _ASM_GENERIC_DIV64_H */
eof
