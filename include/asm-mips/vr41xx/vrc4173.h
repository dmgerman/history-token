multiline_comment|/*&n; *  vrc4173.h, Include file for NEC VRC4173.&n; *&n; *  Copyright (C) 2000  Michael R. McDonald&n; *  Copyright (C) 2001-2003 Montavista Software Inc.&n; *    Author: Yoichi Yuasa &lt;yyuasa@mvista.com, or source@mvista.com&gt;&n; *  Copyright (C) 2004  Yoichi Yuasa &lt;yuasa@hh.iij4u.or.jp&gt;&n; *  Copyright (C) 2005 Ralf Baechle (ralf@linux-mips.org)&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#ifndef __NEC_VRC4173_H 
DECL|macro|__NEC_VRC4173_H
mdefine_line|#define __NEC_VRC4173_H 
macro_line|#include &lt;linux/config.h&gt;
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
macro_line|#ifdef CONFIG_VRC4173
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
macro_line|#else
DECL|macro|set_vrc4173_io_offset
mdefine_line|#define set_vrc4173_io_offset(offset)&t;do {} while (0)
DECL|macro|vrc4173_outb
mdefine_line|#define vrc4173_outb(val,port)&t;&t;do {} while (0)
DECL|macro|vrc4173_outw
mdefine_line|#define vrc4173_outw(val,port)&t;&t;do {} while (0)
DECL|macro|vrc4173_outl
mdefine_line|#define vrc4173_outl(val,port)&t;&t;do {} while (0)
DECL|macro|vrc4173_outb_p
mdefine_line|#define vrc4173_outb_p(val,port)&t;do {} while (0)
DECL|macro|vrc4173_outw_p
mdefine_line|#define vrc4173_outw_p(val,port)&t;do {} while (0)
DECL|macro|vrc4173_outl_p
mdefine_line|#define vrc4173_outl_p(val,port)&t;do {} while (0)
DECL|macro|vrc4173_inb
mdefine_line|#define vrc4173_inb(port)&t;&t;0
DECL|macro|vrc4173_inw
mdefine_line|#define vrc4173_inw(port)&t;&t;0
DECL|macro|vrc4173_inl
mdefine_line|#define vrc4173_inl(port)&t;&t;0
DECL|macro|vrc4173_inb_p
mdefine_line|#define vrc4173_inb_p(port)&t;&t;0
DECL|macro|vrc4173_inw_p
mdefine_line|#define vrc4173_inw_p(port)&t;&t;0
DECL|macro|vrc4173_inl_p
mdefine_line|#define vrc4173_inl_p(port)&t;&t;0
DECL|macro|vrc4173_outsb
mdefine_line|#define vrc4173_outsb(port,addr,count)&t;do {} while (0)
DECL|macro|vrc4173_outsw
mdefine_line|#define vrc4173_outsw(port,addr,count)&t;do {} while (0)
DECL|macro|vrc4173_outsl
mdefine_line|#define vrc4173_outsl(port,addr,count)&t;do {} while (0)
DECL|macro|vrc4173_insb
mdefine_line|#define vrc4173_insb(port,addr,count)&t;do {} while (0)
DECL|macro|vrc4173_insw
mdefine_line|#define vrc4173_insw(port,addr,count)&t;do {} while (0)
DECL|macro|vrc4173_insl
mdefine_line|#define vrc4173_insl(port,addr,count)&t;do {} while (0)
macro_line|#endif
multiline_comment|/*&n; * Clock Mask Unit&n; */
DECL|enum|vrc4173_clock
r_typedef
r_enum
id|vrc4173_clock
(brace
DECL|enumerator|VRC4173_PIU_CLOCK
id|VRC4173_PIU_CLOCK
comma
DECL|enumerator|VRC4173_KIU_CLOCK
id|VRC4173_KIU_CLOCK
comma
DECL|enumerator|VRC4173_AIU_CLOCK
id|VRC4173_AIU_CLOCK
comma
DECL|enumerator|VRC4173_PS2_CH1_CLOCK
id|VRC4173_PS2_CH1_CLOCK
comma
DECL|enumerator|VRC4173_PS2_CH2_CLOCK
id|VRC4173_PS2_CH2_CLOCK
comma
DECL|enumerator|VRC4173_USBU_PCI_CLOCK
id|VRC4173_USBU_PCI_CLOCK
comma
DECL|enumerator|VRC4173_CARDU1_PCI_CLOCK
id|VRC4173_CARDU1_PCI_CLOCK
comma
DECL|enumerator|VRC4173_CARDU2_PCI_CLOCK
id|VRC4173_CARDU2_PCI_CLOCK
comma
DECL|enumerator|VRC4173_AC97U_PCI_CLOCK
id|VRC4173_AC97U_PCI_CLOCK
comma
DECL|enumerator|VRC4173_USBU_48MHz_CLOCK
id|VRC4173_USBU_48MHz_CLOCK
comma
DECL|enumerator|VRC4173_EXT_48MHz_CLOCK
id|VRC4173_EXT_48MHz_CLOCK
comma
DECL|enumerator|VRC4173_48MHz_CLOCK
id|VRC4173_48MHz_CLOCK
comma
DECL|typedef|vrc4173_clock_t
)brace
id|vrc4173_clock_t
suffix:semicolon
macro_line|#ifdef CONFIG_VRC4173
r_extern
r_void
id|vrc4173_supply_clock
c_func
(paren
id|vrc4173_clock_t
id|clock
)paren
suffix:semicolon
r_extern
r_void
id|vrc4173_mask_clock
c_func
(paren
id|vrc4173_clock_t
id|clock
)paren
suffix:semicolon
macro_line|#else
DECL|function|vrc4173_supply_clock
r_static
r_inline
r_void
id|vrc4173_supply_clock
c_func
(paren
id|vrc4173_clock_t
id|clock
)paren
(brace
)brace
DECL|function|vrc4173_mask_clock
r_static
r_inline
r_void
id|vrc4173_mask_clock
c_func
(paren
id|vrc4173_clock_t
id|clock
)paren
(brace
)brace
macro_line|#endif
multiline_comment|/*&n; * Interupt Control Unit&n; */
DECL|macro|VRC4173_PIUINT_COMMAND
mdefine_line|#define VRC4173_PIUINT_COMMAND&t;&t;0x0040
DECL|macro|VRC4173_PIUINT_DATA
mdefine_line|#define VRC4173_PIUINT_DATA&t;&t;0x0020
DECL|macro|VRC4173_PIUINT_PAGE1
mdefine_line|#define VRC4173_PIUINT_PAGE1&t;&t;0x0010
DECL|macro|VRC4173_PIUINT_PAGE0
mdefine_line|#define VRC4173_PIUINT_PAGE0&t;&t;0x0008
DECL|macro|VRC4173_PIUINT_DATALOST
mdefine_line|#define VRC4173_PIUINT_DATALOST&t;&t;0x0004
DECL|macro|VRC4173_PIUINT_STATUSCHANGE
mdefine_line|#define VRC4173_PIUINT_STATUSCHANGE&t;0x0001
macro_line|#ifdef CONFIG_VRC4173
r_extern
r_void
id|vrc4173_enable_piuint
c_func
(paren
r_uint16
id|mask
)paren
suffix:semicolon
r_extern
r_void
id|vrc4173_disable_piuint
c_func
(paren
r_uint16
id|mask
)paren
suffix:semicolon
macro_line|#else
DECL|function|vrc4173_enable_piuint
r_static
r_inline
r_void
id|vrc4173_enable_piuint
c_func
(paren
r_uint16
id|mask
)paren
(brace
)brace
DECL|function|vrc4173_disable_piuint
r_static
r_inline
r_void
id|vrc4173_disable_piuint
c_func
(paren
r_uint16
id|mask
)paren
(brace
)brace
macro_line|#endif
DECL|macro|VRC4173_AIUINT_INPUT_DMAEND
mdefine_line|#define VRC4173_AIUINT_INPUT_DMAEND&t;0x0800
DECL|macro|VRC4173_AIUINT_INPUT_DMAHALT
mdefine_line|#define VRC4173_AIUINT_INPUT_DMAHALT&t;0x0400
DECL|macro|VRC4173_AIUINT_INPUT_DATALOST
mdefine_line|#define VRC4173_AIUINT_INPUT_DATALOST&t;0x0200
DECL|macro|VRC4173_AIUINT_INPUT_DATA
mdefine_line|#define VRC4173_AIUINT_INPUT_DATA&t;0x0100
DECL|macro|VRC4173_AIUINT_OUTPUT_DMAEND
mdefine_line|#define VRC4173_AIUINT_OUTPUT_DMAEND&t;0x0008
DECL|macro|VRC4173_AIUINT_OUTPUT_DMAHALT
mdefine_line|#define VRC4173_AIUINT_OUTPUT_DMAHALT&t;0x0004
DECL|macro|VRC4173_AIUINT_OUTPUT_NODATA
mdefine_line|#define VRC4173_AIUINT_OUTPUT_NODATA&t;0x0002
macro_line|#ifdef CONFIG_VRC4173
r_extern
r_void
id|vrc4173_enable_aiuint
c_func
(paren
r_uint16
id|mask
)paren
suffix:semicolon
r_extern
r_void
id|vrc4173_disable_aiuint
c_func
(paren
r_uint16
id|mask
)paren
suffix:semicolon
macro_line|#else
DECL|function|vrc4173_enable_aiuint
r_static
r_inline
r_void
id|vrc4173_enable_aiuint
c_func
(paren
r_uint16
id|mask
)paren
(brace
)brace
DECL|function|vrc4173_disable_aiuint
r_static
r_inline
r_void
id|vrc4173_disable_aiuint
c_func
(paren
r_uint16
id|mask
)paren
(brace
)brace
macro_line|#endif
DECL|macro|VRC4173_KIUINT_DATALOST
mdefine_line|#define VRC4173_KIUINT_DATALOST&t;&t;0x0004
DECL|macro|VRC4173_KIUINT_DATAREADY
mdefine_line|#define VRC4173_KIUINT_DATAREADY&t;0x0002
DECL|macro|VRC4173_KIUINT_SCAN
mdefine_line|#define VRC4173_KIUINT_SCAN&t;&t;0x0001
macro_line|#ifdef CONFIG_VRC4173
r_extern
r_void
id|vrc4173_enable_kiuint
c_func
(paren
r_uint16
id|mask
)paren
suffix:semicolon
r_extern
r_void
id|vrc4173_disable_kiuint
c_func
(paren
r_uint16
id|mask
)paren
suffix:semicolon
macro_line|#else
DECL|function|vrc4173_enable_kiuint
r_static
r_inline
r_void
id|vrc4173_enable_kiuint
c_func
(paren
r_uint16
id|mask
)paren
(brace
)brace
DECL|function|vrc4173_disable_kiuint
r_static
r_inline
r_void
id|vrc4173_disable_kiuint
c_func
(paren
r_uint16
id|mask
)paren
(brace
)brace
macro_line|#endif
multiline_comment|/*&n; * General-Purpose I/O Unit&n; */
DECL|enum|vrc4173_function
r_typedef
r_enum
id|vrc4173_function
(brace
DECL|enumerator|PS2_CHANNEL1
id|PS2_CHANNEL1
comma
DECL|enumerator|PS2_CHANNEL2
id|PS2_CHANNEL2
comma
DECL|enumerator|TOUCHPANEL
id|TOUCHPANEL
comma
DECL|enumerator|KEYBOARD_8SCANLINES
id|KEYBOARD_8SCANLINES
comma
DECL|enumerator|KEYBOARD_10SCANLINES
id|KEYBOARD_10SCANLINES
comma
DECL|enumerator|KEYBOARD_12SCANLINES
id|KEYBOARD_12SCANLINES
comma
DECL|enumerator|GPIO_0_15PINS
id|GPIO_0_15PINS
comma
DECL|enumerator|GPIO_16_20PINS
id|GPIO_16_20PINS
comma
DECL|typedef|vrc4173_function_t
)brace
id|vrc4173_function_t
suffix:semicolon
macro_line|#ifdef CONFIG_VRC4173
r_extern
r_void
id|vrc4173_select_function
c_func
(paren
id|vrc4173_function_t
id|function
)paren
suffix:semicolon
macro_line|#else
DECL|function|vrc4173_select_function
r_static
r_inline
r_void
id|vrc4173_select_function
c_func
(paren
id|vrc4173_function_t
id|function
)paren
(brace
)brace
macro_line|#endif
macro_line|#endif /* __NEC_VRC4173_H */
eof
