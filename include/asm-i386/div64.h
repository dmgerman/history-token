macro_line|#ifndef __I386_DIV64
DECL|macro|__I386_DIV64
mdefine_line|#define __I386_DIV64
DECL|macro|do_div
mdefine_line|#define do_div(n,base) ({ &bslash;&n;&t;unsigned long __upper, __low, __high, __mod; &bslash;&n;&t;asm(&quot;&quot;:&quot;=a&quot; (__low), &quot;=d&quot; (__high):&quot;A&quot; (n)); &bslash;&n;&t;__upper = __high; &bslash;&n;&t;if (__high) { &bslash;&n;&t;&t;__upper = __high % (base); &bslash;&n;&t;&t;__high = __high / (base); &bslash;&n;&t;} &bslash;&n;&t;asm(&quot;divl %2&quot;:&quot;=a&quot; (__low), &quot;=d&quot; (__mod):&quot;rm&quot; (base), &quot;0&quot; (__low), &quot;1&quot; (__upper)); &bslash;&n;&t;asm(&quot;&quot;:&quot;=A&quot; (n):&quot;a&quot; (__low),&quot;d&quot; (__high)); &bslash;&n;&t;__mod; &bslash;&n;})
macro_line|#endif
eof
