multiline_comment|/*&n; * FILE NAME&n; *&t;include/asm-mips/vr41xx/vrc4173.h&n; *&n; * BRIEF MODULE DESCRIPTION&n; *&t;Include file for NEC VRC4173.&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 2000 by Michael R. McDonald&n; *&n; * Copyright 2001-2003 Montavista Software Inc.&n; * Author: Yoichi Yuasa&n; *         yyuasa@mvista.com or source@mvista.com&n; */
macro_line|#ifndef __NEC_VRC4173_H 
DECL|macro|__NEC_VRC4173_H
mdefine_line|#define __NEC_VRC4173_H 
macro_line|#include &lt;asm/io.h&gt;
multiline_comment|/*&n; * Interrupt Number&n; */
DECL|macro|VRC4173_IRQ_BASE
mdefine_line|#define VRC4173_IRQ_BASE&t;72
DECL|macro|VRC4173_IRQ
mdefine_line|#define VRC4173_IRQ(x)&t;&t;(VRC4173_IRQ_BASE + (x))
DECL|macro|VRC4173_USB_IRQ
mdefine_line|#define VRC4173_USB_IRQ&t;&t;VRC4173_IRQ(0)
DECL|macro|VRC4173_PCMCIA2_IRQ
mdefine_line|#define VRC4173_PCMCIA2_IRQ&t;VRC4173_IRQ(1)
DECL|macro|VRC4173_PCMCIA1_IRQ
mdefine_line|#define VRC4173_PCMCIA1_IRQ&t;VRC4173_IRQ(2)
DECL|macro|VRC4173_PS2CH2_IRQ
mdefine_line|#define VRC4173_PS2CH2_IRQ&t;VRC4173_IRQ(3)
DECL|macro|VRC4173_PS2CH1_IRQ
mdefine_line|#define VRC4173_PS2CH1_IRQ&t;VRC4173_IRQ(4)
DECL|macro|VRC4173_PIU_IRQ
mdefine_line|#define VRC4173_PIU_IRQ&t;&t;VRC4173_IRQ(5)
DECL|macro|VRC4173_AIU_IRQ
mdefine_line|#define VRC4173_AIU_IRQ&t;&t;VRC4173_IRQ(6)
DECL|macro|VRC4173_KIU_IRQ
mdefine_line|#define VRC4173_KIU_IRQ&t;&t;VRC4173_IRQ(7)
DECL|macro|VRC4173_GIU_IRQ
mdefine_line|#define VRC4173_GIU_IRQ&t;&t;VRC4173_IRQ(8)
DECL|macro|VRC4173_AC97_IRQ
mdefine_line|#define VRC4173_AC97_IRQ&t;VRC4173_IRQ(9)
DECL|macro|VRC4173_AC97INT1_IRQ
mdefine_line|#define VRC4173_AC97INT1_IRQ&t;VRC4173_IRQ(10)
multiline_comment|/* RFU */
DECL|macro|VRC4173_DOZEPIU_IRQ
mdefine_line|#define VRC4173_DOZEPIU_IRQ&t;VRC4173_IRQ(13)
DECL|macro|VRC4173_IRQ_LAST
mdefine_line|#define VRC4173_IRQ_LAST&t;VRC4173_DOZEPIU_IRQ
multiline_comment|/*&n; * PCI I/O accesses&n; */
r_extern
r_int
r_int
id|vrc4173_io_offset
suffix:semicolon
DECL|macro|set_vrc4173_io_offset
mdefine_line|#define set_vrc4173_io_offset(offset)&t;do { vrc4173_io_offset = (offset); } while (0)
DECL|macro|vrc4173_outb
mdefine_line|#define vrc4173_outb(val,port)&t;&t;outb((val), vrc4173_io_offset+(port))
DECL|macro|vrc4173_outw
mdefine_line|#define vrc4173_outw(val,port)&t;&t;outw((val), vrc4173_io_offset+(port))
DECL|macro|vrc4173_outl
mdefine_line|#define vrc4173_outl(val,port)&t;&t;outl((val), vrc4173_io_offset+(port))
DECL|macro|vrc4173_outb_p
mdefine_line|#define vrc4173_outb_p(val,port)&t;outb_p((val), vrc4173_io_offset+(port))
DECL|macro|vrc4173_outw_p
mdefine_line|#define vrc4173_outw_p(val,port)&t;outw_p((val), vrc4173_io_offset+(port))
DECL|macro|vrc4173_outl_p
mdefine_line|#define vrc4173_outl_p(val,port)&t;outl_p((val), vrc4173_io_offset+(port))
DECL|macro|vrc4173_inb
mdefine_line|#define vrc4173_inb(port)&t;&t;inb(vrc4173_io_offset+(port))
DECL|macro|vrc4173_inw
mdefine_line|#define vrc4173_inw(port)&t;&t;inw(vrc4173_io_offset+(port))
DECL|macro|vrc4173_inl
mdefine_line|#define vrc4173_inl(port)&t;&t;inl(vrc4173_io_offset+(port))
DECL|macro|vrc4173_inb_p
mdefine_line|#define vrc4173_inb_p(port)&t;&t;inb_p(vrc4173_io_offset+(port))
DECL|macro|vrc4173_inw_p
mdefine_line|#define vrc4173_inw_p(port)&t;&t;inw_p(vrc4173_io_offset+(port))
DECL|macro|vrc4173_inl_p
mdefine_line|#define vrc4173_inl_p(port)&t;&t;inl_p(vrc4173_io_offset+(port))
DECL|macro|vrc4173_outsb
mdefine_line|#define vrc4173_outsb(port,addr,count)&t;outsb(vrc4173_io_offset+(port),(addr),(count))
DECL|macro|vrc4173_outsw
mdefine_line|#define vrc4173_outsw(port,addr,count)&t;outsw(vrc4173_io_offset+(port),(addr),(count))
DECL|macro|vrc4173_outsl
mdefine_line|#define vrc4173_outsl(port,addr,count)&t;outsl(vrc4173_io_offset+(port),(addr),(count))
DECL|macro|vrc4173_insb
mdefine_line|#define vrc4173_insb(port,addr,count)&t;insb(vrc4173_io_offset+(port),(addr),(count))
DECL|macro|vrc4173_insw
mdefine_line|#define vrc4173_insw(port,addr,count)&t;insw(vrc4173_io_offset+(port),(addr),(count))
DECL|macro|vrc4173_insl
mdefine_line|#define vrc4173_insl(port,addr,count)&t;insl(vrc4173_io_offset+(port),(addr),(count))
multiline_comment|/*&n; * Clock Mask Unit&n; */
r_extern
r_void
id|vrc4173_clock_supply
c_func
(paren
id|u16
id|mask
)paren
suffix:semicolon
r_extern
r_void
id|vrc4173_clock_mask
c_func
(paren
id|u16
id|mask
)paren
suffix:semicolon
multiline_comment|/*&n; * General-Purpose I/O Unit&n; */
r_enum
(brace
DECL|enumerator|PS2CH1_SELECT
id|PS2CH1_SELECT
comma
DECL|enumerator|PS2CH2_SELECT
id|PS2CH2_SELECT
comma
DECL|enumerator|TOUCHPANEL_SELECT
id|TOUCHPANEL_SELECT
comma
DECL|enumerator|KIU8_SELECT
id|KIU8_SELECT
comma
DECL|enumerator|KIU10_SELECT
id|KIU10_SELECT
comma
DECL|enumerator|KIU12_SELECT
id|KIU12_SELECT
comma
DECL|enumerator|GPIO_SELECT
id|GPIO_SELECT
)brace
suffix:semicolon
r_extern
r_void
id|vrc4173_select_function
c_func
(paren
r_int
id|func
)paren
suffix:semicolon
macro_line|#endif /* __NEC_VRC4173_H */
eof
