multiline_comment|/*&n; * include/asm-sh/saturn/io.h&n; *&n; * I/O functions for use on the Sega Saturn.&n; *&n; * Copyright (C) 2002 Paul Mundt&n; *&n; * Released under the terms of the GNU GPL v2.0.&n; */
macro_line|#ifndef __ASM_SH_SATURN_IO_H
DECL|macro|__ASM_SH_SATURN_IO_H
mdefine_line|#define __ASM_SH_SATURN_IO_H
macro_line|#include &lt;asm/io_generic.h&gt;
multiline_comment|/* arch/sh/boards/saturn/io.c */
r_extern
r_int
r_int
id|saturn_isa_port2addr
c_func
(paren
r_int
r_int
id|offset
)paren
suffix:semicolon
r_extern
r_void
op_star
id|saturn_ioremap
c_func
(paren
r_int
r_int
id|offset
comma
r_int
r_int
id|size
)paren
suffix:semicolon
r_extern
r_void
id|saturn_iounmap
c_func
(paren
r_void
op_star
id|addr
)paren
suffix:semicolon
macro_line|#ifdef __WANT_IO_DEF
DECL|macro|__inb
macro_line|# define __inb&t;&t;&t;generic_inb
DECL|macro|__inw
macro_line|# define __inw&t;&t;&t;generic_inw
DECL|macro|__inl
macro_line|# define __inl&t;&t;&t;generic_inl
DECL|macro|__outb
macro_line|# define __outb&t;&t;&t;generic_outb
DECL|macro|__outw
macro_line|# define __outw&t;&t;&t;generic_outw
DECL|macro|__outl
macro_line|# define __outl&t;&t;&t;generic_outl
DECL|macro|__inb_p
macro_line|# define __inb_p&t;&t;generic_inb_p
DECL|macro|__inw_p
macro_line|# define __inw_p&t;&t;generic_inw
DECL|macro|__inl_p
macro_line|# define __inl_p&t;&t;generic_inl
DECL|macro|__outb_p
macro_line|# define __outb_p&t;&t;generic_outb_p
DECL|macro|__outw_p
macro_line|# define __outw_p&t;&t;generic_outw
DECL|macro|__outl_p
macro_line|# define __outl_p&t;&t;generic_outl
DECL|macro|__insb
macro_line|# define __insb&t;&t;&t;generic_insb
DECL|macro|__insw
macro_line|# define __insw&t;&t;&t;generic_insw
DECL|macro|__insl
macro_line|# define __insl&t;&t;&t;generic_insl
DECL|macro|__outsb
macro_line|# define __outsb&t;&t;generic_outsb
DECL|macro|__outsw
macro_line|# define __outsw&t;&t;generic_outsw
DECL|macro|__outsl
macro_line|# define __outsl&t;&t;generic_outsl
DECL|macro|__readb
macro_line|# define __readb&t;&t;generic_readb
DECL|macro|__readw
macro_line|# define __readw&t;&t;generic_readw
DECL|macro|__readl
macro_line|# define __readl&t;&t;generic_readl
DECL|macro|__writeb
macro_line|# define __writeb&t;&t;generic_writeb
DECL|macro|__writew
macro_line|# define __writew&t;&t;generic_writew
DECL|macro|__writel
macro_line|# define __writel&t;&t;generic_writel
DECL|macro|__isa_port2addr
macro_line|# define __isa_port2addr&t;saturn_isa_port2addr
DECL|macro|__ioremap
macro_line|# define __ioremap&t;&t;saturn_ioremap
DECL|macro|__iounmap
macro_line|# define __iounmap&t;&t;saturn_iounmap
macro_line|#endif
macro_line|#endif /* __ASM_SH_SATURN_IO_H */
eof
