multiline_comment|/*&n; * include/asm-sh/io_bigsur.h&n; *&n; * By Dustin McIntire (dustin@sensoria.com) (c)2001&n; * Derived from io_hd64465.h, which bore the message:&n; * By Greg Banks &lt;gbanks@pocketpenguins.com&gt;&n; * (c) 2000 PocketPenguins Inc. &n; * and from io_hd64461.h, which bore the message:&n; * Copyright 2000 Stuart Menefy (stuart.menefy@st.com)&n; *&n; * May be copied or modified under the terms of the GNU General Public&n; * License.  See linux/COPYING for more information.&n; *&n; * IO functions for a Hitachi Big Sur Evaluation Board.&n; */
macro_line|#ifndef _ASM_SH_IO_BIGSUR_H
DECL|macro|_ASM_SH_IO_BIGSUR_H
mdefine_line|#define _ASM_SH_IO_BIGSUR_H
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/io_generic.h&gt;
r_extern
r_int
r_char
id|bigsur_inb
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
id|bigsur_inw
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
id|bigsur_inl
c_func
(paren
r_int
r_int
id|port
)paren
suffix:semicolon
r_extern
r_void
id|bigsur_outb
c_func
(paren
r_int
r_char
id|value
comma
r_int
r_int
id|port
)paren
suffix:semicolon
r_extern
r_void
id|bigsur_outw
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
id|bigsur_outl
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
r_char
id|bigsur_inb_p
c_func
(paren
r_int
r_int
id|port
)paren
suffix:semicolon
r_extern
r_void
id|bigsur_outb_p
c_func
(paren
r_int
r_char
id|value
comma
r_int
r_int
id|port
)paren
suffix:semicolon
r_extern
r_void
id|bigsur_insb
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
id|bigsur_insw
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
id|bigsur_insl
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
id|bigsur_outsb
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
id|bigsur_outsw
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
id|bigsur_outsl
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
id|bigsur_isa_port2addr
c_func
(paren
r_int
r_int
id|offset
)paren
suffix:semicolon
r_extern
r_int
id|bigsur_irq_demux
c_func
(paren
r_int
id|irq
)paren
suffix:semicolon
r_extern
r_void
id|bigsur_init_pci
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Provision for generic secondary demux step -- used by PCMCIA code */
r_extern
r_void
id|bigsur_register_irq_demux
c_func
(paren
r_int
id|irq
comma
r_int
(paren
op_star
id|demux
)paren
(paren
r_int
id|irq
comma
r_void
op_star
id|dev
)paren
comma
r_void
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_void
id|bigsur_unregister_irq_demux
c_func
(paren
r_int
id|irq
)paren
suffix:semicolon
multiline_comment|/* Set this variable to 1 to see port traffic */
r_extern
r_int
id|bigsur_io_debug
suffix:semicolon
multiline_comment|/* Map a range of ports to a range of kernel virtual memory. */
r_extern
r_void
id|bigsur_port_map
c_func
(paren
id|u32
id|baseport
comma
id|u32
id|nports
comma
id|u32
id|addr
comma
id|u8
id|shift
)paren
suffix:semicolon
r_extern
r_void
id|bigsur_port_unmap
c_func
(paren
id|u32
id|baseport
comma
id|u32
id|nports
)paren
suffix:semicolon
macro_line|#endif /* _ASM_SH_IO_BIGSUR_H */
macro_line|#ifdef __WANT_IO_DEF
DECL|macro|__inb
macro_line|# define __inb&t;&t;&t;bigsur_inb
DECL|macro|__inw
macro_line|# define __inw&t;&t;&t;bigsur_inw
DECL|macro|__inl
macro_line|# define __inl&t;&t;&t;bigsur_inl
DECL|macro|__outb
macro_line|# define __outb&t;&t;&t;bigsur_outb
DECL|macro|__outw
macro_line|# define __outw&t;&t;&t;bigsur_outw
DECL|macro|__outl
macro_line|# define __outl&t;&t;&t;bigsur_outl
DECL|macro|__inb_p
macro_line|# define __inb_p&t;&t;bigsur_inb_p
DECL|macro|__inw_p
macro_line|# define __inw_p&t;&t;bigsur_inw
DECL|macro|__inl_p
macro_line|# define __inl_p&t;&t;bigsur_inl
DECL|macro|__outb_p
macro_line|# define __outb_p&t;&t;bigsur_outb_p
DECL|macro|__outw_p
macro_line|# define __outw_p&t;&t;bigsur_outw
DECL|macro|__outl_p
macro_line|# define __outl_p&t;&t;bigsur_outl
DECL|macro|__insb
macro_line|# define __insb&t;&t;&t;bigsur_insb
DECL|macro|__insw
macro_line|# define __insw&t;&t;&t;bigsur_insw
DECL|macro|__insl
macro_line|# define __insl&t;&t;&t;bigsur_insl
DECL|macro|__outsb
macro_line|# define __outsb&t;&t;bigsur_outsb
DECL|macro|__outsw
macro_line|# define __outsw&t;&t;bigsur_outsw
DECL|macro|__outsl
macro_line|# define __outsl&t;&t;bigsur_outsl
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
macro_line|# define __isa_port2addr&t;bigsur_isa_port2addr
DECL|macro|__ioremap
macro_line|# define __ioremap&t;&t;generic_ioremap
DECL|macro|__iounmap
macro_line|# define __iounmap&t;&t;generic_iounmap
macro_line|#endif
eof
