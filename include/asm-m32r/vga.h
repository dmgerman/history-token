macro_line|#ifndef _ASM_M32R_VGA_H
DECL|macro|_ASM_M32R_VGA_H
mdefine_line|#define _ASM_M32R_VGA_H
multiline_comment|/* $Id$ */
multiline_comment|/*&n; *&t;Access to VGA videoram&n; *&n; *&t;(c) 1998 Martin Mares &lt;mj@ucw.cz&gt;&n; */
multiline_comment|/*&n; *&t;On the PC, we can just recalculate addresses and then&n; *&t;access the videoram directly without any black magic.&n; */
DECL|macro|VGA_MAP_MEM
mdefine_line|#define VGA_MAP_MEM(x) (unsigned long)phys_to_virt(x)
DECL|macro|vga_readb
mdefine_line|#define vga_readb(x) (*(x))
DECL|macro|vga_writeb
mdefine_line|#define vga_writeb(x,y) (*(y) = (x))
macro_line|#endif  /* _ASM_M32R_VGA_H */
eof
