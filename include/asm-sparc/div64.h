macro_line|#ifndef __SPARC_DIV64
DECL|macro|__SPARC_DIV64
mdefine_line|#define __SPARC_DIV64
multiline_comment|/* We&squot;re not 64-bit, but... */
DECL|macro|do_div
mdefine_line|#define do_div(n,base) ({ &bslash;&n;&t;int __res; &bslash;&n;&t;__res = ((unsigned long) n) % (unsigned) base; &bslash;&n;&t;n = ((unsigned long) n) / (unsigned) base; &bslash;&n;&t;__res; })
macro_line|#endif /* __SPARC_DIV64 */
eof
