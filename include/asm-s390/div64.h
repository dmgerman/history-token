macro_line|#ifndef __S390_DIV64
DECL|macro|__S390_DIV64
mdefine_line|#define __S390_DIV64
multiline_comment|/* for do_div &quot;base&quot; needs to be smaller than 2^31-1 */
DECL|macro|do_div
mdefine_line|#define do_div(n, base) ({                                      &bslash;&n;&t;unsigned long long __n = (n);&t;&t;&t;&t;&bslash;&n;&t;unsigned long __r;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;asm (&quot;   slr  0,0&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;     &quot;   l    1,%1&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;     &quot;   srdl 0,1&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;     &quot;   dr   0,%2&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;     &quot;   alr  1,1&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;     &quot;   alr  0,0&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;     &quot;   lhi  2,1&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;     &quot;   n    2,%1&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;     &quot;   alr  0,2&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;     &quot;   clr  0,%2&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;     &quot;   jl   0f&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;     &quot;   slr  0,%2&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;             &quot;   ahi  1,1&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;     &quot;0: st   1,%1&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;     &quot;   l    1,4+%1&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;     &quot;   srdl 0,1&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;             &quot;   dr   0,%2&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;     &quot;   alr  1,1&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;     &quot;   alr  0,0&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;     &quot;   lhi  2,1&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;     &quot;   n    2,4+%1&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;     &quot;   alr  0,2&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;     &quot;   clr  0,%2&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;             &quot;   jl   1f&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;     &quot;   slr  0,%2&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;     &quot;   ahi  1,1&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;     &quot;1: st   1,4+%1&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;             &quot;   lr   %0,0&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;     : &quot;=d&quot; (__r), &quot;+m&quot; (__n)&t;&t;&t;&t;&bslash;&n;&t;     : &quot;d&quot; (base) : &quot;0&quot;, &quot;1&quot;, &quot;2&quot; );&t;&t;&t;&bslash;&n;&t;(n) = (__n);&t;&t;&t;&t;&t;&t;&bslash;&n;        __r;                                                    &bslash;&n;})
macro_line|#endif
eof
