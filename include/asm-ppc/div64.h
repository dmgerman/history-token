macro_line|#ifndef __PPC_DIV64
DECL|macro|__PPC_DIV64
mdefine_line|#define __PPC_DIV64
macro_line|#include &lt;linux/types.h&gt;
r_extern
id|u32
id|__div64_32
c_func
(paren
id|u64
op_star
id|dividend
comma
id|u32
id|div
)paren
suffix:semicolon
DECL|macro|do_div
mdefine_line|#define do_div(n, div)&t;({&t;&t;&t;&bslash;&n;&t;u64 __n = (n);&t;&t;&t;&t;&bslash;&n;&t;u32 __d = (div);&t;&t;&t;&bslash;&n;&t;u32 __q, __r;&t;&t;&t;&t;&bslash;&n;&t;if ((__n &gt;&gt; 32) == 0) {&t;&t;&t;&bslash;&n;&t;&t;__q = (u32)__n / __d;&t;&t;&bslash;&n;&t;&t;__r = (u32)__n - __q * __d;&t;&bslash;&n;&t;&t;(n) = __q;&t;&t;&t;&bslash;&n;&t;} else {&t;&t;&t;&t;&bslash;&n;&t;&t;__r = __div64_32(&amp;__n, __d);&t;&bslash;&n;&t;&t;(n) = __n;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&bslash;&n;&t;__r;&t;&t;&t;&t;&t;&bslash;&n;})
macro_line|#endif
eof
