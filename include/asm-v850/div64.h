macro_line|#ifndef __V850_DIV64_H__
DECL|macro|__V850_DIV64_H__
mdefine_line|#define __V850_DIV64_H__
multiline_comment|/* We&squot;re not 64-bit, but... */
DECL|macro|do_div
mdefine_line|#define do_div(n,base) ({ &bslash;&n;&t;int __res; &bslash;&n;&t;__res = ((unsigned long) n) % (unsigned) base; &bslash;&n;&t;n = ((unsigned long) n) / (unsigned) base; &bslash;&n;&t;__res; })
macro_line|#endif /* __V850_DIV64_H__ */
eof
