multiline_comment|/*&n; *&t;Access to VGA videoram&n; *&n; *&t;(c) 1998 Martin Mares &lt;mj@ucw.cz&gt;&n; *&t;(c) 1999 Asit Mallick &lt;asit.k.mallick@intel.com&gt;&n; *&t;(c) 1999 Don Dugger &lt;don.dugger@intel.com&gt;&n; */
macro_line|#ifndef __ASM_IA64_VGA_H_
DECL|macro|__ASM_IA64_VGA_H_
mdefine_line|#define __ASM_IA64_VGA_H_
multiline_comment|/*&n; * On the PC, we can just recalculate addresses and then access the&n; * videoram directly without any black magic.&n; */
DECL|macro|VGA_MAP_MEM
mdefine_line|#define VGA_MAP_MEM(x)&t;((unsigned long) ioremap((x), 0))
DECL|macro|vga_readb
mdefine_line|#define vga_readb(x)&t;(*(x))
DECL|macro|vga_writeb
mdefine_line|#define vga_writeb(x,y)&t;(*(y) = (x))
macro_line|#endif /* __ASM_IA64_VGA_H_ */
eof
