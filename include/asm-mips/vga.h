multiline_comment|/*&n; *&t;Access to VGA videoram&n; *&n; *&t;(c) 1998 Martin Mares &lt;mj@ucw.cz&gt;&n; */
macro_line|#ifndef _ASM_VGA_H
DECL|macro|_ASM_VGA_H
mdefine_line|#define _ASM_VGA_H
multiline_comment|/*&n; *&t;On the PC, we can just recalculate addresses and then&n; *&t;access the videoram directly without any black magic.&n; */
DECL|macro|VGA_MAP_MEM
mdefine_line|#define VGA_MAP_MEM(x)&t;(0xb0000000L + (unsigned long)(x))
DECL|macro|vga_readb
mdefine_line|#define vga_readb(x)&t;(*(x))
DECL|macro|vga_writeb
mdefine_line|#define vga_writeb(x,y)&t;(*(y) = (x))
macro_line|#endif /* _ASM_VGA_H */
eof
