macro_line|#ifndef __ASM_SH_DIV64
DECL|macro|__ASM_SH_DIV64
mdefine_line|#define __ASM_SH_DIV64
r_extern
id|u64
id|__div64_32
c_func
(paren
id|u64
id|n
comma
id|u32
id|d
)paren
suffix:semicolon
DECL|macro|do_div
mdefine_line|#define do_div(n,base) ({ &bslash;&n;u64 __n = (n), __q; &bslash;&n;u32 __base = (base); &bslash;&n;u32 __res; &bslash;&n;if ((__n &gt;&gt; 32) == 0) { &bslash;&n;&t;__res = ((unsigned long) __n) % (unsigned) __base; &bslash;&n;&t;(n) = ((unsigned long) __n) / (unsigned) __base; &bslash;&n;} else { &bslash;&n;&t;__q = __div64_32(__n, __base); &bslash;&n;&t;__res = __n - __q * __base; &bslash;&n;&t;(n) = __q; &bslash;&n;} &bslash;&n;__res; })
macro_line|#endif /* __ASM_SH_DIV64 */
eof
