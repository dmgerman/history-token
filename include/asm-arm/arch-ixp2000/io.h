multiline_comment|/*&n; * linux/include/asm-arm/arch-ixdp2000/io.h&n; *&n; * Original Author: Naeem M Afzal &lt;naeem.m.afzal@intel.com&gt;&n; * Maintainer: Deepak Saxena &lt;dsaxena@plexity.net&gt;&n; *&n; * Copyright (C) 2002  Intel Corp.&n; * Copyrgiht (C) 2003-2004 MontaVista Software, Inc.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#ifndef __ASM_ARM_ARCH_IO_H
DECL|macro|__ASM_ARM_ARCH_IO_H
mdefine_line|#define __ASM_ARM_ARCH_IO_H
DECL|macro|IO_SPACE_LIMIT
mdefine_line|#define IO_SPACE_LIMIT&t;&t;0xffffffff
DECL|macro|__mem_pci
mdefine_line|#define __mem_pci(a)&t;&t;(a)
multiline_comment|/*&n; * Pick up VMALLOC_END&n; */
DECL|macro|___io
mdefine_line|#define ___io(p)&t;&t;((void __iomem *)((p)+IXP2000_PCI_IO_VIRT_BASE))
multiline_comment|/*&n; * IXP2000 does not do proper byte-lane conversion for PCI addresses,&n; * so we need to override standard functions.&n; */
DECL|macro|alignb
mdefine_line|#define alignb(addr)&t;&t;(void __iomem *)(((unsigned long)addr &amp; ~3) + (3 - ((unsigned long)addr &amp; 3)))
DECL|macro|alignw
mdefine_line|#define alignw(addr)&t;&t;(void __iomem *)(((unsigned long)addr &amp; ~2) + (2 - ((unsigned long)addr &amp; 2)))
DECL|macro|outb
mdefine_line|#define outb(v,p)&t;&t;__raw_writeb(v,alignb(___io(p)))
DECL|macro|outw
mdefine_line|#define outw(v,p)&t;&t;__raw_writew((v),alignw(___io(p)))
DECL|macro|outl
mdefine_line|#define outl(v,p)&t;&t;__raw_writel((v),___io(p))
DECL|macro|inb
mdefine_line|#define inb(p)&t;&t;({ unsigned int __v = __raw_readb(alignb(___io(p))); __v; })
DECL|macro|inw
mdefine_line|#define inw(p)&t;&t;&bslash;&n;&t;({ unsigned int __v = (__raw_readw(alignw(___io(p)))); __v; })
DECL|macro|inl
mdefine_line|#define inl(p)&t;&t;&bslash;&n;&t;({ unsigned int __v = (__raw_readl(___io(p))); __v; })
DECL|macro|outsb
mdefine_line|#define outsb(p,d,l)&t;&t;__raw_writesb(alignb(___io(p)),d,l)
DECL|macro|outsw
mdefine_line|#define outsw(p,d,l)&t;&t;__raw_writesw(alignw(___io(p)),d,l)
DECL|macro|outsl
mdefine_line|#define outsl(p,d,l)&t;&t;__raw_writesl(___io(p),d,l)
DECL|macro|insb
mdefine_line|#define insb(p,d,l)&t;&t;__raw_readsb(alignb(___io(p)),d,l)
DECL|macro|insw
mdefine_line|#define insw(p,d,l)&t;&t;__raw_readsw(alignw(___io(p)),d,l)
DECL|macro|insl
mdefine_line|#define insl(p,d,l)&t;&t;__raw_readsl(___io(p),d,l)
macro_line|#ifdef CONFIG_ARCH_IXDP2X01
multiline_comment|/*&n; * This is an ugly hack but the CS8900 on the 2x01&squot;s does not sit in any sort&n; * of &quot;I/O space&quot; and is just direct mapped into a 32-bit-only addressable&n; * bus. The address space for this bus is such that we can&squot;t really easilly&n; * make it contigous to the PCI I/O address range, and it also does not&n; * need swapping like PCI addresses do (IXDP2x01 is a BE platform).&n; * B/C of this we can&squot;t use the standard in/out functions and need to&n; * runtime check if the incoming address is a PCI address or for&n; * the CS89x0.&n; */
DECL|macro|inw
macro_line|#undef inw
DECL|macro|outw
macro_line|#undef outw
DECL|macro|insw
macro_line|#undef insw
DECL|macro|outsw
macro_line|#undef outsw
macro_line|#include &lt;asm/mach-types.h&gt;
DECL|function|insw
r_static
r_inline
r_void
id|insw
c_func
(paren
id|u32
id|ptr
comma
r_void
op_star
id|buf
comma
r_int
id|length
)paren
(brace
r_register
r_volatile
id|u32
op_star
id|port
op_assign
(paren
r_volatile
id|u32
op_star
)paren
id|ptr
suffix:semicolon
multiline_comment|/*&n;&t; * Is this cycle meant for the CS8900?&n;&t; */
r_if
c_cond
(paren
(paren
id|machine_is_ixdp2401
c_func
(paren
)paren
op_logical_or
id|machine_is_ixdp2801
c_func
(paren
)paren
)paren
op_logical_and
(paren
(paren
id|port
op_ge
id|IXDP2X01_CS8900_VIRT_BASE
)paren
op_logical_and
(paren
id|port
op_le
id|IXDP2X01_CS8900_VIRT_END
)paren
)paren
)paren
(brace
id|u8
op_star
id|buf8
op_assign
(paren
id|u8
op_star
)paren
id|buf
suffix:semicolon
r_register
id|u32
id|tmp32
suffix:semicolon
r_do
(brace
id|tmp32
op_assign
op_star
id|port
suffix:semicolon
op_star
id|buf8
op_increment
op_assign
(paren
id|u8
)paren
id|tmp32
suffix:semicolon
op_star
id|buf8
op_increment
op_assign
(paren
id|u8
)paren
(paren
id|tmp32
op_rshift
l_int|8
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
op_decrement
id|length
)paren
(brace
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
id|__raw_readsw
c_func
(paren
id|alignw
c_func
(paren
id|___io
c_func
(paren
id|ptr
)paren
)paren
comma
id|buf
comma
id|length
)paren
suffix:semicolon
)brace
DECL|function|outsw
r_static
r_inline
r_void
id|outsw
c_func
(paren
id|u32
id|ptr
comma
r_void
op_star
id|buf
comma
r_int
id|length
)paren
(brace
r_register
r_volatile
id|u32
op_star
id|port
op_assign
(paren
r_volatile
id|u32
op_star
)paren
id|ptr
suffix:semicolon
multiline_comment|/*&n;&t; * Is this cycle meant for the CS8900?&n;&t; */
r_if
c_cond
(paren
(paren
id|machine_is_ixdp2401
c_func
(paren
)paren
op_logical_or
id|machine_is_ixdp2801
c_func
(paren
)paren
)paren
op_logical_and
(paren
(paren
id|port
op_ge
id|IXDP2X01_CS8900_VIRT_BASE
)paren
op_logical_and
(paren
id|port
op_le
id|IXDP2X01_CS8900_VIRT_END
)paren
)paren
)paren
(brace
r_register
id|u32
id|tmp32
suffix:semicolon
id|u8
op_star
id|buf8
op_assign
(paren
id|u8
op_star
)paren
id|buf
suffix:semicolon
r_do
(brace
id|tmp32
op_assign
op_star
id|buf8
op_increment
suffix:semicolon
id|tmp32
op_or_assign
(paren
op_star
id|buf8
op_increment
)paren
op_lshift
l_int|8
suffix:semicolon
op_star
id|port
op_assign
id|tmp32
suffix:semicolon
)brace
r_while
c_loop
(paren
op_decrement
id|length
)paren
(brace
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
id|__raw_writesw
c_func
(paren
id|alignw
c_func
(paren
id|___io
c_func
(paren
id|ptr
)paren
)paren
comma
id|buf
comma
id|length
)paren
suffix:semicolon
)brace
DECL|function|inw
r_static
r_inline
id|u16
id|inw
c_func
(paren
id|u32
id|ptr
)paren
(brace
r_register
r_volatile
id|u32
op_star
id|port
op_assign
(paren
r_volatile
id|u32
op_star
)paren
id|ptr
suffix:semicolon
multiline_comment|/*&n;&t; * Is this cycle meant for the CS8900?&n;&t; */
r_if
c_cond
(paren
(paren
id|machine_is_ixdp2401
c_func
(paren
)paren
op_logical_or
id|machine_is_ixdp2801
c_func
(paren
)paren
)paren
op_logical_and
(paren
(paren
id|port
op_ge
id|IXDP2X01_CS8900_VIRT_BASE
)paren
op_logical_and
(paren
id|port
op_le
id|IXDP2X01_CS8900_VIRT_END
)paren
)paren
)paren
(brace
r_return
(paren
id|u16
)paren
(paren
op_star
id|port
)paren
suffix:semicolon
)brace
r_return
id|__raw_readw
c_func
(paren
id|alignw
c_func
(paren
id|___io
c_func
(paren
id|ptr
)paren
)paren
)paren
suffix:semicolon
)brace
DECL|function|outw
r_static
r_inline
r_void
id|outw
c_func
(paren
id|u16
id|value
comma
id|u32
id|ptr
)paren
(brace
r_register
r_volatile
id|u32
op_star
id|port
op_assign
(paren
r_volatile
id|u32
op_star
)paren
id|ptr
suffix:semicolon
r_if
c_cond
(paren
(paren
id|machine_is_ixdp2401
c_func
(paren
)paren
op_logical_or
id|machine_is_ixdp2801
c_func
(paren
)paren
)paren
op_logical_and
(paren
(paren
id|port
op_ge
id|IXDP2X01_CS8900_VIRT_BASE
)paren
op_logical_and
(paren
id|port
op_le
id|IXDP2X01_CS8900_VIRT_END
)paren
)paren
)paren
(brace
op_star
id|port
op_assign
id|value
suffix:semicolon
r_return
suffix:semicolon
)brace
id|__raw_writew
c_func
(paren
(paren
id|value
)paren
comma
id|alignw
c_func
(paren
id|___io
c_func
(paren
id|ptr
)paren
)paren
)paren
suffix:semicolon
)brace
macro_line|#endif&t;/* IXDP2x01 */
macro_line|#endif
eof
