macro_line|#ifndef __ASM_PARISC_DIV64
DECL|macro|__ASM_PARISC_DIV64
mdefine_line|#define __ASM_PARISC_DIV64
macro_line|#ifdef __LP64__
multiline_comment|/*&n; * Copyright (C) 1999 Hewlett-Packard Co&n; * Copyright (C) 1999 David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; *&n; * vsprintf uses this to divide a 64-bit integer N by a small integer BASE.&n; * This is incredibly hard on IA-64 and HPPA&n; */
DECL|macro|do_div
mdefine_line|#define do_div(n,base)&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;int _res;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;_res = ((unsigned long) (n)) % (unsigned) (base);&t;&bslash;&n;&t;(n) = ((unsigned long) (n)) / (unsigned) (base);&t;&bslash;&n;&t;_res;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
macro_line|#else
multiline_comment|/*&n; * unsigned long long division.  Yuck Yuck!  What is Linux coming to?&n; * This is 100% disgusting&n; */
DECL|macro|do_div
mdefine_line|#define do_div(n,base)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long __low, __low2, __high, __rem;&t;&t;&t;&bslash;&n;&t;__low  = (n) &amp; 0xffffffff;&t;&t;&t;&t;&t;&bslash;&n;&t;__high = (n) &gt;&gt; 32;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (__high) {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__rem   = __high % (unsigned long)base;&t;&t;&t;&bslash;&n;&t;&t;__high  = __high / (unsigned long)base;&t;&t;&t;&bslash;&n;&t;&t;__low2  = __low &gt;&gt; 16;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__low2 += __rem &lt;&lt; 16;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__rem   = __low2 % (unsigned long)base;&t;&t;&t;&bslash;&n;&t;&t;__low2  = __low2 / (unsigned long)base;&t;&t;&t;&bslash;&n;&t;&t;__low   = __low &amp; 0xffff;&t;&t;&t;&t;&bslash;&n;&t;&t;__low  += __rem &lt;&lt; 16;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__rem   = __low  % (unsigned long)base;&t;&t;&t;&bslash;&n;&t;&t;__low   = __low  / (unsigned long)base;&t;&t;&t;&bslash;&n;&t;&t;n = __low  + ((long long)__low2 &lt;&lt; 16) +&t;&t;&bslash;&n;&t;&t;&t;((long long) __high &lt;&lt; 32);&t;&t;&t;&bslash;&n;&t;} else {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__rem = __low % (unsigned long)base;&t;&t;&t;&bslash;&n;&t;&t;n = (__low / (unsigned long)base);&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__rem;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
macro_line|#endif
macro_line|#endif
eof
