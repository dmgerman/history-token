macro_line|#ifndef __ASM_ARM_DIV64
DECL|macro|__ASM_ARM_DIV64
mdefine_line|#define __ASM_ARM_DIV64
multiline_comment|/* We&squot;re not 64-bit, but... */
DECL|macro|do_div
mdefine_line|#define do_div(n,base)&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;register int __res asm(&quot;r2&quot;) = base;&t;&t;&t;&bslash;&n;&t;register unsigned long long __n asm(&quot;r0&quot;) = n;&t;&t;&bslash;&n;&t;asm(&quot;bl do_div64&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;=r&quot; (__n), &quot;=r&quot; (__res)&t;&t;&t;&bslash;&n;&t;&t;: &quot;0&quot; (__n), &quot;1&quot; (__res)&t;&t;&t;&bslash;&n;&t;&t;: &quot;r3&quot;, &quot;ip&quot;, &quot;lr&quot;, &quot;cc&quot;);&t;&t;&t;&bslash;&n;&t;n = __n;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__res;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
macro_line|#endif
eof
