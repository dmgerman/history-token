macro_line|#ifndef _ASM_ZORRO_H
DECL|macro|_ASM_ZORRO_H
mdefine_line|#define _ASM_ZORRO_H
macro_line|#include &lt;asm/raw_io.h&gt;
DECL|macro|z_readb
mdefine_line|#define z_readb raw_inb
DECL|macro|z_readw
mdefine_line|#define z_readw raw_inw
DECL|macro|z_readl
mdefine_line|#define z_readl raw_inl
DECL|macro|z_writeb
mdefine_line|#define z_writeb raw_outb
DECL|macro|z_writew
mdefine_line|#define z_writew raw_outw
DECL|macro|z_writel
mdefine_line|#define z_writel raw_outl
DECL|macro|z_memset_io
mdefine_line|#define z_memset_io(a,b,c)&t;memset((void *)(a),(b),(c))
DECL|macro|z_memcpy_fromio
mdefine_line|#define z_memcpy_fromio(a,b,c)&t;memcpy((a),(void *)(b),(c))
DECL|macro|z_memcpy_toio
mdefine_line|#define z_memcpy_toio(a,b,c)&t;memcpy((void *)(a),(b),(c))
macro_line|#endif /* _ASM_ZORRO_H */
eof
