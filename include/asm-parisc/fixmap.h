macro_line|#ifndef _ASM_FIXMAP_H
DECL|macro|_ASM_FIXMAP_H
mdefine_line|#define _ASM_FIXMAP_H
DECL|macro|FIXADDR_TOP
mdefine_line|#define FIXADDR_TOP&t;(0xffffe000UL)
DECL|macro|FIXADDR_SIZE
mdefine_line|#define FIXADDR_SIZE&t;(0 &lt;&lt; PAGE_SHIFT)
DECL|macro|FIXADDR_START
mdefine_line|#define FIXADDR_START&t;(FIXADDR_TOP - FIXADDR_SIZE)
macro_line|#endif
eof
