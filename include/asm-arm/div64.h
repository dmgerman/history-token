macro_line|#ifndef __ASM_ARM_DIV64
DECL|macro|__ASM_ARM_DIV64
mdefine_line|#define __ASM_ARM_DIV64
multiline_comment|/*&n; * The semantics of do_div() are:&n; *&n; * uint32_t do_div(uint64_t *n, uint32_t base)&n; * {&n; * &t;uint32_t remainder = *n % base;&n; * &t;*n = *n / base;&n; * &t;return remainder;&n; * }&n; *&n; * In other words, a 64-bit dividend with a 32-bit divisor producing&n; * a 64-bit result and a 32-bit remainder.  To accomplish this optimally&n; * we call a special __do_div64 helper with completely non standard&n; * calling convention for arguments and results (beware).&n; */
macro_line|#ifdef __ARMEB__
DECL|macro|__xh
mdefine_line|#define __xh &quot;r0&quot;
DECL|macro|__xl
mdefine_line|#define __xl &quot;r1&quot;
macro_line|#else
DECL|macro|__xl
mdefine_line|#define __xl &quot;r0&quot;
DECL|macro|__xh
mdefine_line|#define __xh &quot;r1&quot;
macro_line|#endif
DECL|macro|do_div
mdefine_line|#define do_div(n,base)&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;register unsigned int __base      asm(&quot;r4&quot;) = base;&t;&bslash;&n;&t;register unsigned long long __n   asm(&quot;r0&quot;) = n;&t;&bslash;&n;&t;register unsigned long long __res asm(&quot;r2&quot;);&t;&t;&bslash;&n;&t;register unsigned int __rem       asm(__xh);&t;&t;&bslash;&n;&t;asm(&quot;bl&t;__do_div64&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;=r&quot; (__rem), &quot;=r&quot; (__res)&t;&t;&t;&bslash;&n;&t;&t;: &quot;r&quot; (__n), &quot;r&quot; (__base)&t;&t;&t;&bslash;&n;&t;&t;: &quot;ip&quot;, &quot;lr&quot;, &quot;cc&quot;);&t;&t;&t;&t;&bslash;&n;&t;n = __res;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__rem;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
macro_line|#endif
eof
