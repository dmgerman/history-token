macro_line|#ifndef _ASM_IA64_DIV64_H
DECL|macro|_ASM_IA64_DIV64_H
mdefine_line|#define _ASM_IA64_DIV64_H
multiline_comment|/*&n; * Copyright (C) 1999 Hewlett-Packard Co&n; * Copyright (C) 1999 David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; *&n; * vsprintf uses this to divide a 64-bit integer N by a small integer BASE.&n; * This is incredibly hard on IA-64...&n; */
DECL|macro|do_div
mdefine_line|#define do_div(n,base)&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;int _res;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;_res = ((unsigned long) (n)) % (unsigned) (base);&t;&bslash;&n;&t;(n) = ((unsigned long) (n)) / (unsigned) (base);&t;&bslash;&n;&t;_res;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
macro_line|#endif /* _ASM_IA64_DIV64_H */
eof
