macro_line|#ifndef __ASM_SH_SHMPARAM_H
DECL|macro|__ASM_SH_SHMPARAM_H
mdefine_line|#define __ASM_SH_SHMPARAM_H
macro_line|#if defined(__SH4__)
multiline_comment|/*&n; * SH-4 has D-cache alias issue&n; */
DECL|macro|SHMLBA
mdefine_line|#define&t;SHMLBA (PAGE_SIZE*4)&t;&t; /* attach addr a multiple of this */
macro_line|#else
DECL|macro|SHMLBA
mdefine_line|#define&t;SHMLBA PAGE_SIZE&t;&t; /* attach addr a multiple of this */
macro_line|#endif
macro_line|#endif /* __ASM_SH_SHMPARAM_H */
eof
