macro_line|#ifndef __ASM_CRIS_DIV64
DECL|macro|__ASM_CRIS_DIV64
mdefine_line|#define __ASM_CRIS_DIV64
multiline_comment|/* copy from asm-arm */
multiline_comment|/* We&squot;re not 64-bit, but... */
DECL|macro|do_div
mdefine_line|#define do_div(n,base)&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;int __res;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__res = ((unsigned long)n) % (unsigned int)base;&t;&bslash;&n;&t;n = ((unsigned long)n) / (unsigned int)base;&t;&t;&bslash;&n;&t;__res;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
macro_line|#endif
eof
