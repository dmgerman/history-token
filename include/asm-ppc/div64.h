multiline_comment|/*&n; * BK Id: SCCS/s.div64.h 1.5 05/17/01 18:14:24 cort&n; */
macro_line|#ifndef __PPC_DIV64
DECL|macro|__PPC_DIV64
mdefine_line|#define __PPC_DIV64
DECL|macro|do_div
mdefine_line|#define do_div(n,base) ({ &bslash;&n;int __res; &bslash;&n;__res = ((unsigned long) n) % (unsigned) base; &bslash;&n;n = ((unsigned long) n) / (unsigned) base; &bslash;&n;__res; })
macro_line|#endif
eof
