multiline_comment|/*&n; * include/asm-sh/io_od.h&n; *&n; * Copyright 2000 Stuart Menefy (stuart.menefy@st.com)&n; *&n; * May be copied or modified under the terms of the GNU General Public&n; * License.  See linux/COPYING for more information.&n; *&n; * IO functions for an STMicroelectronics Overdrive&n; */
macro_line|#ifndef _ASM_SH_IO_OD_H
DECL|macro|_ASM_SH_IO_OD_H
mdefine_line|#define _ASM_SH_IO_OD_H
macro_line|#include &lt;asm/io_generic.h&gt;
r_extern
r_int
r_int
id|od_inb
c_func
(paren
r_int
r_int
id|port
)paren
suffix:semicolon
r_extern
r_int
r_int
id|od_inw
c_func
(paren
r_int
r_int
id|port
)paren
suffix:semicolon
r_extern
r_int
r_int
id|od_inl
c_func
(paren
r_int
r_int
id|port
)paren
suffix:semicolon
r_extern
r_void
id|od_outb
c_func
(paren
r_int
r_int
id|value
comma
r_int
r_int
id|port
)paren
suffix:semicolon
r_extern
r_void
id|od_outw
c_func
(paren
r_int
r_int
id|value
comma
r_int
r_int
id|port
)paren
suffix:semicolon
r_extern
r_void
id|od_outl
c_func
(paren
r_int
r_int
id|value
comma
r_int
r_int
id|port
)paren
suffix:semicolon
r_extern
r_int
r_int
id|od_inb_p
c_func
(paren
r_int
r_int
id|port
)paren
suffix:semicolon
r_extern
r_int
r_int
id|od_inw_p
c_func
(paren
r_int
r_int
id|port
)paren
suffix:semicolon
r_extern
r_int
r_int
id|od_inl_p
c_func
(paren
r_int
r_int
id|port
)paren
suffix:semicolon
r_extern
r_void
id|od_outb_p
c_func
(paren
r_int
r_int
id|value
comma
r_int
r_int
id|port
)paren
suffix:semicolon
r_extern
r_void
id|od_outw_p
c_func
(paren
r_int
r_int
id|value
comma
r_int
r_int
id|port
)paren
suffix:semicolon
r_extern
r_void
id|od_outl_p
c_func
(paren
r_int
r_int
id|value
comma
r_int
r_int
id|port
)paren
suffix:semicolon
r_extern
r_void
id|od_insb
c_func
(paren
r_int
r_int
id|port
comma
r_void
op_star
id|addr
comma
r_int
r_int
id|count
)paren
suffix:semicolon
r_extern
r_void
id|od_insw
c_func
(paren
r_int
r_int
id|port
comma
r_void
op_star
id|addr
comma
r_int
r_int
id|count
)paren
suffix:semicolon
r_extern
r_void
id|od_insl
c_func
(paren
r_int
r_int
id|port
comma
r_void
op_star
id|addr
comma
r_int
r_int
id|count
)paren
suffix:semicolon
r_extern
r_void
id|od_outsb
c_func
(paren
r_int
r_int
id|port
comma
r_const
r_void
op_star
id|addr
comma
r_int
r_int
id|count
)paren
suffix:semicolon
r_extern
r_void
id|od_outsw
c_func
(paren
r_int
r_int
id|port
comma
r_const
r_void
op_star
id|addr
comma
r_int
r_int
id|count
)paren
suffix:semicolon
r_extern
r_void
id|od_outsl
c_func
(paren
r_int
r_int
id|port
comma
r_const
r_void
op_star
id|addr
comma
r_int
r_int
id|count
)paren
suffix:semicolon
r_extern
r_int
r_int
id|od_isa_port2addr
c_func
(paren
r_int
r_int
id|offset
)paren
suffix:semicolon
macro_line|#ifdef __WANT_IO_DEF
DECL|macro|__inb
macro_line|# define __inb&t;&t;&t;od_inb
DECL|macro|__inw
macro_line|# define __inw&t;&t;&t;od_inw
DECL|macro|__inl
macro_line|# define __inl&t;&t;&t;od_inl
DECL|macro|__outb
macro_line|# define __outb&t;&t;&t;od_outb
DECL|macro|__outw
macro_line|# define __outw&t;&t;&t;od_outw
DECL|macro|__outl
macro_line|# define __outl&t;&t;&t;od_outl
DECL|macro|__inb_p
macro_line|# define __inb_p&t;&t;od_inb_p
DECL|macro|__inw_p
macro_line|# define __inw_p&t;&t;od_inw_p
DECL|macro|__inl_p
macro_line|# define __inl_p&t;&t;od_inl_p
DECL|macro|__outb_p
macro_line|# define __outb_p&t;&t;od_outb_p
DECL|macro|__outw_p
macro_line|# define __outw_p&t;&t;od_outw_p
DECL|macro|__outl_p
macro_line|# define __outl_p&t;&t;od_outl_p
DECL|macro|__insb
macro_line|# define __insb&t;&t;&t;od_insb
DECL|macro|__insw
macro_line|# define __insw&t;&t;&t;od_insw
DECL|macro|__insl
macro_line|# define __insl&t;&t;&t;od_insl
DECL|macro|__outsb
macro_line|# define __outsb&t;&t;od_outsb
DECL|macro|__outsw
macro_line|# define __outsw&t;&t;od_outsw
DECL|macro|__outsl
macro_line|# define __outsl&t;&t;od_outsl
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
macro_line|# define __isa_port2addr&t;od_isa_port2addr
DECL|macro|__ioremap
macro_line|# define __ioremap&t;&t;generic_ioremap
DECL|macro|__ioremap_nocache
macro_line|# define __ioremap_nocache&t;generic_ioremap_nocache
DECL|macro|__iounmap
macro_line|# define __iounmap&t;&t;generic_iounmap
macro_line|#endif
macro_line|#endif /* _ASM_SH_IO_OD_H */
eof
