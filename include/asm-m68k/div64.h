macro_line|#ifndef _M68K_DIV64_H
DECL|macro|_M68K_DIV64_H
mdefine_line|#define _M68K_DIV64_H
multiline_comment|/* n = n / base; return rem; */
macro_line|#if 1
DECL|macro|do_div
mdefine_line|#define do_div(n, base) ({&t;&t;&t;&t;&t;&bslash;&n;&t;union {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;unsigned long n32[2];&t;&t;&t;&t;&bslash;&n;&t;&t;unsigned long long n64;&t;&t;&t;&t;&bslash;&n;&t;} __n;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long __rem, __upper;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__n.n64 = (n);&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if ((__upper = __n.n32[0])) {&t;&t;&t;&t;&bslash;&n;&t;&t;asm (&quot;divul.l %2,%1:%0&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;: &quot;=d&quot; (__n.n32[0]), &quot;=d&quot; (__upper)&t;&bslash;&n;&t;&t;&t;: &quot;d&quot; (base), &quot;0&quot; (__n.n32[0]));&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;asm (&quot;divu.l %2,%1:%0&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;=d&quot; (__n.n32[1]), &quot;=d&quot; (__rem)&t;&t;&bslash;&n;&t;&t;: &quot;d&quot; (base), &quot;1&quot; (__upper), &quot;0&quot; (__n.n32[1]));&t;&bslash;&n;&t;(n) = __n.n64;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__rem;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
macro_line|#else
DECL|macro|do_div
mdefine_line|#define do_div(n,base) ({&t;&t;&t;&t;&t;&bslash;&n;&t;int __res;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__res = ((unsigned long) n) % (unsigned) base;&t;&t;&bslash;&n;&t;n = ((unsigned long) n) / (unsigned) base;&t;&t;&bslash;&n;&t;__res;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
macro_line|#endif
macro_line|#endif /* _M68K_DIV64_H */
eof
