macro_line|#ifndef ASMARM_VGA_H
DECL|macro|ASMARM_VGA_H
mdefine_line|#define ASMARM_VGA_H
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/io.h&gt;
DECL|macro|VGA_MAP_MEM
mdefine_line|#define VGA_MAP_MEM(x)&t;(PCIMEM_BASE + (x))
DECL|macro|vga_readb
mdefine_line|#define vga_readb(x)&t;(*((volatile unsigned char *)x))
DECL|macro|vga_writeb
mdefine_line|#define vga_writeb(x,y)&t;(*((volatile unsigned char *)y) = (x))
macro_line|#endif
eof
