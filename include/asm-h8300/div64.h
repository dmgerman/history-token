macro_line|#ifndef H8300_DIV64_H
DECL|macro|H8300_DIV64_H
mdefine_line|#define H8300_DIV64_H
multiline_comment|/* n = n / base; return rem; */
DECL|macro|do_div
mdefine_line|#define do_div(n,base) ({&t;&t;&t;&t;&t;&bslash;&n;&t;int __res;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__res = ((unsigned long) n) % (unsigned) base;&t;&t;&bslash;&n;&t;n = ((unsigned long) n) / (unsigned) base;&t;&t;&bslash;&n;&t;__res;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
macro_line|#endif /* _H8300_DIV64_H */
eof
