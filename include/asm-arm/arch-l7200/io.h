multiline_comment|/*&n; * linux/include/asm-arm/arch-l7200/io.h&n; *&n; * Copyright (C) 2000 Steve Hill (sjhill@cotw.com)&n; *&n; * Modifications:&n; *  03-21-2000&t;SJH&t;Created from linux/include/asm-arm/arch-nexuspci/io.h&n; */
macro_line|#ifndef __ASM_ARM_ARCH_IO_H
DECL|macro|__ASM_ARM_ARCH_IO_H
mdefine_line|#define __ASM_ARM_ARCH_IO_H
macro_line|#include &lt;asm/arch/hardware.h&gt;
DECL|macro|IO_SPACE_LIMIT
mdefine_line|#define IO_SPACE_LIMIT 0xffffffff
multiline_comment|/*&n; * Translated address IO functions&n; *&n; * IO address has already been translated to a virtual address&n; */
DECL|macro|outb_t
mdefine_line|#define outb_t(v,p)&t;(*(volatile unsigned char *)(p) = (v))
DECL|macro|inb_t
mdefine_line|#define inb_t(p)&t;(*(volatile unsigned char *)(p))
DECL|macro|outw_t
mdefine_line|#define outw_t(v,p)&t;(*(volatile unsigned int *)(p) = (v))
DECL|macro|inw_t
mdefine_line|#define inw_t(p)&t;(*(volatile unsigned int *)(p))
DECL|macro|outl_t
mdefine_line|#define outl_t(v,p)&t;(*(volatile unsigned long *)(p) = (v))
DECL|macro|inl_t
mdefine_line|#define inl_t(p)&t;(*(volatile unsigned long *)(p))
multiline_comment|/*&n; * FIXME - These are to allow for linking. On all the other&n; *         ARM platforms, the entire IO space is contiguous.&n; *         The 7200 has three separate IO spaces. The below&n; *         macros will eventually become more involved. Use&n; *         with caution and don&squot;t be surprised by kernel oopses!!!&n; */
DECL|macro|inb
mdefine_line|#define inb(p)&t; &t;inb_t(p)
DECL|macro|inw
mdefine_line|#define inw(p)&t; &t;inw_t(p)
DECL|macro|inl
mdefine_line|#define inl(p)&t; &t;inl_t(p)
DECL|macro|outb
mdefine_line|#define outb(v,p)&t;outb_t(v,p)
DECL|macro|outw
mdefine_line|#define outw(v,p)&t;outw_t(v,p)
DECL|macro|outl
mdefine_line|#define outl(v,p)&t;outl_t(v,p)
macro_line|#endif
eof
