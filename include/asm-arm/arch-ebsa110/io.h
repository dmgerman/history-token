multiline_comment|/*&n; *  linux/include/asm-arm/arch-ebsa110/io.h&n; *&n; *  Copyright (C) 1997,1998 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; * Modifications:&n; *  06-Dec-1997&t;RMK&t;Created.&n; */
macro_line|#ifndef __ASM_ARM_ARCH_IO_H
DECL|macro|__ASM_ARM_ARCH_IO_H
mdefine_line|#define __ASM_ARM_ARCH_IO_H
DECL|macro|IO_SPACE_LIMIT
mdefine_line|#define IO_SPACE_LIMIT 0xffff
multiline_comment|/*&n; * Generic virtual read/write&n; */
DECL|macro|__arch_getw
mdefine_line|#define __arch_getw(a)&t;&t;(*(volatile unsigned short *)(a))
DECL|macro|__arch_putw
mdefine_line|#define __arch_putw(v,a)&t;(*(volatile unsigned short *)(a) = (v))
id|u8
id|__inb
c_func
(paren
r_int
id|port
)paren
suffix:semicolon
id|u16
id|__inw
c_func
(paren
r_int
id|port
)paren
suffix:semicolon
id|u32
id|__inl
c_func
(paren
r_int
id|port
)paren
suffix:semicolon
DECL|macro|inb
mdefine_line|#define inb(p)&t;&t;&t;__inb(p)
DECL|macro|inw
mdefine_line|#define inw(p)&t;&t;&t;__inw(p)
DECL|macro|inl
mdefine_line|#define inl(p)&t;&t;&t;__inl(p)
r_void
id|__outb
c_func
(paren
id|u8
id|val
comma
r_int
id|port
)paren
suffix:semicolon
r_void
id|__outw
c_func
(paren
id|u16
id|val
comma
r_int
id|port
)paren
suffix:semicolon
r_void
id|__outl
c_func
(paren
id|u32
id|val
comma
r_int
id|port
)paren
suffix:semicolon
DECL|macro|outb
mdefine_line|#define outb(v,p)&t;&t;__outb(v,p)
DECL|macro|outw
mdefine_line|#define outw(v,p)&t;&t;__outw(v,p)
DECL|macro|outl
mdefine_line|#define outl(v,p)&t;&t;__outl(v,p)
id|u8
id|__readb
c_func
(paren
r_void
op_star
id|addr
)paren
suffix:semicolon
id|u16
id|__readw
c_func
(paren
r_void
op_star
id|addr
)paren
suffix:semicolon
id|u32
id|__readl
c_func
(paren
r_void
op_star
id|addr
)paren
suffix:semicolon
DECL|macro|readb
mdefine_line|#define readb(b)&t;&t;__readb(b)
DECL|macro|readw
mdefine_line|#define readw(b)&t;&t;__readw(b)
DECL|macro|readl
mdefine_line|#define readl(b)&t;&t;__readl(b)
r_void
id|__writeb
c_func
(paren
id|u8
id|val
comma
r_void
op_star
id|addr
)paren
suffix:semicolon
r_void
id|__writew
c_func
(paren
id|u16
id|val
comma
r_void
op_star
id|addr
)paren
suffix:semicolon
r_void
id|__writel
c_func
(paren
id|u32
id|val
comma
r_void
op_star
id|addr
)paren
suffix:semicolon
DECL|macro|writeb
mdefine_line|#define writeb(v,b)&t;&t;__writeb(v,b)
DECL|macro|writew
mdefine_line|#define writew(v,b)&t;&t;__writew(v,b)
DECL|macro|writel
mdefine_line|#define writel(v,b)&t;&t;__writel(v,b)
DECL|macro|__arch_ioremap
mdefine_line|#define __arch_ioremap(off,sz,c)&t;((void *)(off))
DECL|macro|__arch_iounmap
mdefine_line|#define __arch_iounmap(virt)&t;&t;do { } while (0)
macro_line|#endif
eof
