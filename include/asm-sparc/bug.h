multiline_comment|/* $Id$ */
macro_line|#ifndef _SPARC_BUG_H
DECL|macro|_SPARC_BUG_H
mdefine_line|#define _SPARC_BUG_H
multiline_comment|/*&n; * XXX I am hitting compiler bugs with __builtin_trap. This has&n; * hit me before and rusty was blaming his netfilter bugs on&n; * this so lets disable it. - Anton&n; */
macro_line|#if 0
multiline_comment|/* We need the mb()&squot;s so we don&squot;t trigger a compiler bug - Anton */
mdefine_line|#define BUG() do { &bslash;&n;&t;mb(); &bslash;&n;&t;__builtin_trap(); &bslash;&n;&t;mb(); &bslash;&n;} while(0)
macro_line|#else
DECL|macro|BUG
mdefine_line|#define BUG() do { &bslash;&n;&t;printk(&quot;kernel BUG at %s:%d!&bslash;n&quot;, __FILE__, __LINE__); *(int *)0=0; &bslash;&n;} while (0)
macro_line|#endif
DECL|macro|PAGE_BUG
mdefine_line|#define PAGE_BUG(page)&t;BUG()
macro_line|#endif
eof
