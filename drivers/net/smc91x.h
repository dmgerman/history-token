multiline_comment|/*------------------------------------------------------------------------&n; . smc91x.h - macros for SMSC&squot;s 91C9x/91C1xx single-chip Ethernet device.&n; .&n; . Copyright (C) 1996 by Erik Stahlman&n; . Copyright (C) 2001 Standard Microsystems Corporation&n; .&t;Developed by Simple Network Magic Corporation&n; . Copyright (C) 2003 Monta Vista Software, Inc.&n; .&t;Unified SMC91x driver by Nicolas Pitre&n; .&n; . This program is free software; you can redistribute it and/or modify&n; . it under the terms of the GNU General Public License as published by&n; . the Free Software Foundation; either version 2 of the License, or&n; . (at your option) any later version.&n; .&n; . This program is distributed in the hope that it will be useful,&n; . but WITHOUT ANY WARRANTY; without even the implied warranty of&n; . MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; . GNU General Public License for more details.&n; .&n; . You should have received a copy of the GNU General Public License&n; . along with this program; if not, write to the Free Software&n; . Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; .&n; . Information contained in this file was obtained from the LAN91C111&n; . manual from SMC.  To get a copy, if you really want one, you can find&n; . information under www.smsc.com.&n; .&n; . Authors&n; .&t;Erik Stahlman&t;&t;&lt;erik@vt.edu&gt;&n; .&t;Daris A Nevil&t;&t;&lt;dnevil@snmc.com&gt;&n; .&t;Nicolas Pitre &t;&t;&lt;nico@cam.org&gt;&n; .&n; ---------------------------------------------------------------------------*/
macro_line|#ifndef _SMC91X_H_
DECL|macro|_SMC91X_H_
mdefine_line|#define _SMC91X_H_
multiline_comment|/*&n; * Define your architecture specific bus configuration parameters here.&n; */
macro_line|#if&t;defined(CONFIG_ARCH_LUBBOCK)
multiline_comment|/* We can only do 16-bit reads and writes in the static memory space. */
DECL|macro|SMC_CAN_USE_8BIT
mdefine_line|#define SMC_CAN_USE_8BIT&t;0
DECL|macro|SMC_CAN_USE_16BIT
mdefine_line|#define SMC_CAN_USE_16BIT&t;1
DECL|macro|SMC_CAN_USE_32BIT
mdefine_line|#define SMC_CAN_USE_32BIT&t;0
DECL|macro|SMC_NOWAIT
mdefine_line|#define SMC_NOWAIT&t;&t;1
multiline_comment|/* The first two address lines aren&squot;t connected... */
DECL|macro|SMC_IO_SHIFT
mdefine_line|#define SMC_IO_SHIFT&t;&t;2
DECL|macro|SMC_inw
mdefine_line|#define SMC_inw(a, r)&t;&t;readw((a) + (r))
DECL|macro|SMC_outw
mdefine_line|#define SMC_outw(v, a, r)&t;writew(v, (a) + (r))
DECL|macro|SMC_insw
mdefine_line|#define SMC_insw(a, r, p, l)&t;readsw((a) + (r), p, l)
DECL|macro|SMC_outsw
mdefine_line|#define SMC_outsw(a, r, p, l)&t;writesw((a) + (r), p, l)
macro_line|#elif defined(CONFIG_REDWOOD_5) || defined(CONFIG_REDWOOD_6)
multiline_comment|/* We can only do 16-bit reads and writes in the static memory space. */
DECL|macro|SMC_CAN_USE_8BIT
mdefine_line|#define SMC_CAN_USE_8BIT&t;0
DECL|macro|SMC_CAN_USE_16BIT
mdefine_line|#define SMC_CAN_USE_16BIT&t;1
DECL|macro|SMC_CAN_USE_32BIT
mdefine_line|#define SMC_CAN_USE_32BIT&t;0
DECL|macro|SMC_NOWAIT
mdefine_line|#define SMC_NOWAIT&t;&t;1
DECL|macro|SMC_IO_SHIFT
mdefine_line|#define SMC_IO_SHIFT&t;&t;0
DECL|macro|SMC_inw
mdefine_line|#define SMC_inw(a, r)&t;&t;in_be16((volatile u16 *)((a) + (r)))
DECL|macro|SMC_outw
mdefine_line|#define SMC_outw(v, a, r)&t;out_be16((volatile u16 *)((a) + (r)), v)
DECL|macro|SMC_insw
mdefine_line|#define SMC_insw(a, r, p, l) &t;&t;&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;unsigned long __port = (a) + (r);&t;&t;&t;&bslash;&n;&t;&t;u16 *__p = (u16 *)(p);&t;&t;&t;&t;&t;&bslash;&n;&t;&t;int __l = (l);&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;insw(__port, __p, __l);&t;&t;&t;&t;&t;&bslash;&n;&t;&t;while (__l &gt; 0) {&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;*__p = swab16(*__p);&t;&t;&t;&t;&bslash;&n;&t;&t;&t;__p++;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;__l--;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;}&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;} while (0)
DECL|macro|SMC_outsw
mdefine_line|#define SMC_outsw(a, r, p, l) &t;&t;&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;unsigned long __port = (a) + (r);&t;&t;&t;&bslash;&n;&t;&t;u16 *__p = (u16 *)(p);&t;&t;&t;&t;&t;&bslash;&n;&t;&t;int __l = (l);&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;while (__l &gt; 0) {&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;/* Believe it or not, the swab isn&squot;t needed. */&t;&bslash;&n;&t;&t;&t;outw( /* swab16 */ (*__p++), __port);&t;&t;&bslash;&n;&t;&t;&t;__l--;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;}&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;} while (0)
DECL|macro|set_irq_type
mdefine_line|#define set_irq_type(irq, type)
macro_line|#elif defined(CONFIG_SA1100_PLEB)
multiline_comment|/* We can only do 16-bit reads and writes in the static memory space. */
DECL|macro|SMC_CAN_USE_8BIT
mdefine_line|#define SMC_CAN_USE_8BIT&t;1
DECL|macro|SMC_CAN_USE_16BIT
mdefine_line|#define SMC_CAN_USE_16BIT&t;1
DECL|macro|SMC_CAN_USE_32BIT
mdefine_line|#define SMC_CAN_USE_32BIT&t;0
DECL|macro|SMC_IO_SHIFT
mdefine_line|#define SMC_IO_SHIFT&t;&t;0
DECL|macro|SMC_NOWAIT
mdefine_line|#define SMC_NOWAIT&t;&t;1
DECL|macro|SMC_inb
mdefine_line|#define SMC_inb(a, r)&t;&t;inb((a) + (r))
DECL|macro|SMC_insb
mdefine_line|#define SMC_insb(a, r, p, l)&t;insb((a) + (r), p, (l))
DECL|macro|SMC_inw
mdefine_line|#define SMC_inw(a, r)&t;&t;inw((a) + (r))
DECL|macro|SMC_insw
mdefine_line|#define SMC_insw(a, r, p, l)&t;insw((a) + (r), p, l)
DECL|macro|SMC_outb
mdefine_line|#define SMC_outb(v, a, r)&t;outb(v, (a) + (r))
DECL|macro|SMC_outsb
mdefine_line|#define SMC_outsb(a, r, p, l)&t;outsb((a) + (r), p, (l))
DECL|macro|SMC_outw
mdefine_line|#define SMC_outw(v, a, r)&t;outw(v, (a) + (r))
DECL|macro|SMC_outsw
mdefine_line|#define SMC_outsw(a, r, p, l)&t;outsw((a) + (r), p, l)
DECL|macro|set_irq_type
mdefine_line|#define set_irq_type(irq, type) do {} while (0)
macro_line|#elif defined(CONFIG_SA1100_ASSABET)
macro_line|#include &lt;asm/arch/neponset.h&gt;
multiline_comment|/* We can only do 8-bit reads and writes in the static memory space. */
DECL|macro|SMC_CAN_USE_8BIT
mdefine_line|#define SMC_CAN_USE_8BIT&t;1
DECL|macro|SMC_CAN_USE_16BIT
mdefine_line|#define SMC_CAN_USE_16BIT&t;0
DECL|macro|SMC_CAN_USE_32BIT
mdefine_line|#define SMC_CAN_USE_32BIT&t;0
DECL|macro|SMC_NOWAIT
mdefine_line|#define SMC_NOWAIT&t;&t;1
multiline_comment|/* The first two address lines aren&squot;t connected... */
DECL|macro|SMC_IO_SHIFT
mdefine_line|#define SMC_IO_SHIFT&t;&t;2
DECL|macro|SMC_inb
mdefine_line|#define SMC_inb(a, r)&t;&t;readb((a) + (r))
DECL|macro|SMC_outb
mdefine_line|#define SMC_outb(v, a, r)&t;writeb(v, (a) + (r))
DECL|macro|SMC_insb
mdefine_line|#define SMC_insb(a, r, p, l)&t;readsb((a) + (r), p, (l))
DECL|macro|SMC_outsb
mdefine_line|#define SMC_outsb(a, r, p, l)&t;writesb((a) + (r), p, (l))
macro_line|#elif&t;defined(CONFIG_ARCH_INNOKOM) || &bslash;&n;&t;defined(CONFIG_MACH_MAINSTONE) || &bslash;&n;&t;defined(CONFIG_ARCH_PXA_IDP) || &bslash;&n;&t;defined(CONFIG_ARCH_RAMSES)
DECL|macro|SMC_CAN_USE_8BIT
mdefine_line|#define SMC_CAN_USE_8BIT&t;1
DECL|macro|SMC_CAN_USE_16BIT
mdefine_line|#define SMC_CAN_USE_16BIT&t;1
DECL|macro|SMC_CAN_USE_32BIT
mdefine_line|#define SMC_CAN_USE_32BIT&t;1
DECL|macro|SMC_IO_SHIFT
mdefine_line|#define SMC_IO_SHIFT&t;&t;0
DECL|macro|SMC_NOWAIT
mdefine_line|#define SMC_NOWAIT&t;&t;1
DECL|macro|SMC_USE_PXA_DMA
mdefine_line|#define SMC_USE_PXA_DMA&t;&t;1
DECL|macro|SMC_inb
mdefine_line|#define SMC_inb(a, r)&t;&t;readb((a) + (r))
DECL|macro|SMC_inw
mdefine_line|#define SMC_inw(a, r)&t;&t;readw((a) + (r))
DECL|macro|SMC_inl
mdefine_line|#define SMC_inl(a, r)&t;&t;readl((a) + (r))
DECL|macro|SMC_outb
mdefine_line|#define SMC_outb(v, a, r)&t;writeb(v, (a) + (r))
DECL|macro|SMC_outl
mdefine_line|#define SMC_outl(v, a, r)&t;writel(v, (a) + (r))
DECL|macro|SMC_insl
mdefine_line|#define SMC_insl(a, r, p, l)&t;readsl((a) + (r), p, l)
DECL|macro|SMC_outsl
mdefine_line|#define SMC_outsl(a, r, p, l)&t;writesl((a) + (r), p, l)
multiline_comment|/* We actually can&squot;t write halfwords properly if not word aligned */
r_static
r_inline
r_void
DECL|function|SMC_outw
id|SMC_outw
c_func
(paren
id|u16
id|val
comma
r_int
r_int
id|ioaddr
comma
r_int
id|reg
)paren
(brace
r_if
c_cond
(paren
id|reg
op_amp
l_int|2
)paren
(brace
r_int
r_int
id|v
op_assign
id|val
op_lshift
l_int|16
suffix:semicolon
id|v
op_or_assign
id|readl
c_func
(paren
id|ioaddr
op_plus
(paren
id|reg
op_amp
op_complement
l_int|2
)paren
)paren
op_amp
l_int|0xffff
suffix:semicolon
id|writel
c_func
(paren
id|v
comma
id|ioaddr
op_plus
(paren
id|reg
op_amp
op_complement
l_int|2
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|writew
c_func
(paren
id|val
comma
id|ioaddr
op_plus
id|reg
)paren
suffix:semicolon
)brace
)brace
macro_line|#elif&t;defined(CONFIG_ISA)
DECL|macro|SMC_CAN_USE_8BIT
mdefine_line|#define SMC_CAN_USE_8BIT&t;1
DECL|macro|SMC_CAN_USE_16BIT
mdefine_line|#define SMC_CAN_USE_16BIT&t;1
DECL|macro|SMC_CAN_USE_32BIT
mdefine_line|#define SMC_CAN_USE_32BIT&t;0
DECL|macro|SMC_inb
mdefine_line|#define SMC_inb(a, r)&t;&t;inb((a) + (r))
DECL|macro|SMC_inw
mdefine_line|#define SMC_inw(a, r)&t;&t;inw((a) + (r))
DECL|macro|SMC_outb
mdefine_line|#define SMC_outb(v, a, r)&t;outb(v, (a) + (r))
DECL|macro|SMC_outw
mdefine_line|#define SMC_outw(v, a, r)&t;outw(v, (a) + (r))
DECL|macro|SMC_insw
mdefine_line|#define SMC_insw(a, r, p, l)&t;insw((a) + (r), p, l)
DECL|macro|SMC_outsw
mdefine_line|#define SMC_outsw(a, r, p, l)&t;outsw((a) + (r), p, l)
macro_line|#elif   defined(CONFIG_M32R)
DECL|macro|SMC_CAN_USE_8BIT
mdefine_line|#define SMC_CAN_USE_8BIT&t;0
DECL|macro|SMC_CAN_USE_16BIT
mdefine_line|#define SMC_CAN_USE_16BIT&t;1
DECL|macro|SMC_CAN_USE_32BIT
mdefine_line|#define SMC_CAN_USE_32BIT&t;0
DECL|macro|SMC_inb
mdefine_line|#define SMC_inb(a, r)&t;&t;inb((a) + (r) - 0xa0000000)
DECL|macro|SMC_inw
mdefine_line|#define SMC_inw(a, r)&t;&t;inw((a) + (r) - 0xa0000000)
DECL|macro|SMC_outb
mdefine_line|#define SMC_outb(v, a, r)&t;outb(v, (a) + (r) - 0xa0000000)
DECL|macro|SMC_outw
mdefine_line|#define SMC_outw(v, a, r)&t;outw(v, (a) + (r) - 0xa0000000)
DECL|macro|SMC_insw
mdefine_line|#define SMC_insw(a, r, p, l)&t;insw((a) + (r) - 0xa0000000, p, l)
DECL|macro|SMC_outsw
mdefine_line|#define SMC_outsw(a, r, p, l)&t;outsw((a) + (r) - 0xa0000000, p, l)
DECL|macro|set_irq_type
mdefine_line|#define set_irq_type(irq, type)&t;do {} while(0)
DECL|macro|RPC_LSA_DEFAULT
mdefine_line|#define RPC_LSA_DEFAULT&t;&t;RPC_LED_TX_RX
DECL|macro|RPC_LSB_DEFAULT
mdefine_line|#define RPC_LSB_DEFAULT&t;&t;RPC_LED_100_10
macro_line|#elif&t;defined(CONFIG_MACH_LPD7A400) || defined(CONFIG_MACH_LPD7A404)
multiline_comment|/* The LPD7A40X_IOBARRIER is necessary to overcome a mismatch between&n; * the way that the CPU handles chip selects and the way that the SMC&n; * chip expects the chip select to operate.  Refer to&n; * Documentation/arm/Sharp-LH/IOBarrier for details.  The read from&n; * IOBARRIER is a byte as a least-common denominator of possible&n; * regions to use as the barrier.  It would be wasteful to read 32&n; * bits from a byte oriented region.&n; *&n; * There is no explicit protection against interrupts intervening&n; * between the writew and the IOBARRIER.  In SMC ISR there is a&n; * preamble that performs an IOBARRIER in the extremely unlikely event&n; * that the driver interrupts itself between a writew to the chip an&n; * the IOBARRIER that follows *and* the cache is large enough that the&n; * first off-chip access while handing the interrupt is to the SMC&n; * chip.  Other devices in the same address space as the SMC chip must&n; * be aware of the potential for trouble and perform a similar&n; * IOBARRIER on entry to their ISR.&n; */
macro_line|#include &lt;asm/arch/constants.h&gt;&t;/* IOBARRIER_VIRT */
DECL|macro|SMC_CAN_USE_8BIT
mdefine_line|#define SMC_CAN_USE_8BIT&t;0
DECL|macro|SMC_CAN_USE_16BIT
mdefine_line|#define SMC_CAN_USE_16BIT&t;1
DECL|macro|SMC_CAN_USE_32BIT
mdefine_line|#define SMC_CAN_USE_32BIT&t;0
DECL|macro|SMC_NOWAIT
mdefine_line|#define SMC_NOWAIT&t;&t;0
DECL|macro|LPD7A40X_IOBARRIER
mdefine_line|#define LPD7A40X_IOBARRIER&t;readb (IOBARRIER_VIRT)
DECL|macro|SMC_inw
mdefine_line|#define SMC_inw(a,r)&t;&t;readw ((void*) ((a) + (r)))
DECL|macro|SMC_insw
mdefine_line|#define SMC_insw(a,r,p,l)&t;readsw ((void*) ((a) + (r)), p, l)
DECL|macro|SMC_outw
mdefine_line|#define SMC_outw(v,a,r)&t;     ({ writew ((v), (a) + (r)); LPD7A40X_IOBARRIER; })
DECL|function|SMC_outsw
r_static
r_inline
r_void
id|SMC_outsw
(paren
r_int
r_int
id|a
comma
r_int
id|r
comma
r_int
r_char
op_star
id|p
comma
r_int
id|l
)paren
(brace
r_int
r_int
op_star
id|ps
op_assign
(paren
r_int
r_int
op_star
)paren
id|p
suffix:semicolon
r_while
c_loop
(paren
id|l
op_decrement
OG
l_int|0
)paren
(brace
id|writew
(paren
op_star
id|ps
op_increment
comma
id|a
op_plus
id|r
)paren
suffix:semicolon
id|LPD7A40X_IOBARRIER
suffix:semicolon
)brace
)brace
DECL|macro|SMC_INTERRUPT_PREAMBLE
mdefine_line|#define SMC_INTERRUPT_PREAMBLE&t;LPD7A40X_IOBARRIER
DECL|macro|RPC_LSA_DEFAULT
mdefine_line|#define RPC_LSA_DEFAULT&t;&t;RPC_LED_TX_RX
DECL|macro|RPC_LSB_DEFAULT
mdefine_line|#define RPC_LSB_DEFAULT&t;&t;RPC_LED_100_10
macro_line|#else
DECL|macro|SMC_CAN_USE_8BIT
mdefine_line|#define SMC_CAN_USE_8BIT&t;1
DECL|macro|SMC_CAN_USE_16BIT
mdefine_line|#define SMC_CAN_USE_16BIT&t;1
DECL|macro|SMC_CAN_USE_32BIT
mdefine_line|#define SMC_CAN_USE_32BIT&t;1
DECL|macro|SMC_NOWAIT
mdefine_line|#define SMC_NOWAIT&t;&t;1
DECL|macro|SMC_inb
mdefine_line|#define SMC_inb(a, r)&t;&t;readb((a) + (r))
DECL|macro|SMC_inw
mdefine_line|#define SMC_inw(a, r)&t;&t;readw((a) + (r))
DECL|macro|SMC_inl
mdefine_line|#define SMC_inl(a, r)&t;&t;readl((a) + (r))
DECL|macro|SMC_outb
mdefine_line|#define SMC_outb(v, a, r)&t;writeb(v, (a) + (r))
DECL|macro|SMC_outw
mdefine_line|#define SMC_outw(v, a, r)&t;writew(v, (a) + (r))
DECL|macro|SMC_outl
mdefine_line|#define SMC_outl(v, a, r)&t;writel(v, (a) + (r))
DECL|macro|SMC_insl
mdefine_line|#define SMC_insl(a, r, p, l)&t;readsl((a) + (r), p, l)
DECL|macro|SMC_outsl
mdefine_line|#define SMC_outsl(a, r, p, l)&t;writesl((a) + (r), p, l)
DECL|macro|RPC_LSA_DEFAULT
mdefine_line|#define RPC_LSA_DEFAULT&t;&t;RPC_LED_100_10
DECL|macro|RPC_LSB_DEFAULT
mdefine_line|#define RPC_LSB_DEFAULT&t;&t;RPC_LED_TX_RX
macro_line|#endif
macro_line|#ifdef SMC_USE_PXA_DMA
multiline_comment|/*&n; * Let&squot;s use the DMA engine on the XScale PXA2xx for RX packets. This is&n; * always happening in irq context so no need to worry about races.  TX is&n; * different and probably not worth it for that reason, and not as critical&n; * as RX which can overrun memory and lose packets.&n; */
macro_line|#include &lt;linux/dma-mapping.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &lt;asm/arch/pxa-regs.h&gt;
macro_line|#ifdef SMC_insl
DECL|macro|SMC_insl
macro_line|#undef SMC_insl
DECL|macro|SMC_insl
mdefine_line|#define SMC_insl(a, r, p, l) &bslash;&n;&t;smc_pxa_dma_insl(a, lp-&gt;physaddr, r, dev-&gt;dma, p, l)
r_static
r_inline
r_void
DECL|function|smc_pxa_dma_insl
id|smc_pxa_dma_insl
c_func
(paren
id|u_long
id|ioaddr
comma
id|u_long
id|physaddr
comma
r_int
id|reg
comma
r_int
id|dma
comma
id|u_char
op_star
id|buf
comma
r_int
id|len
)paren
(brace
id|dma_addr_t
id|dmabuf
suffix:semicolon
multiline_comment|/* fallback if no DMA available */
r_if
c_cond
(paren
id|dma
op_eq
(paren
r_int
r_char
)paren
op_minus
l_int|1
)paren
(brace
id|readsl
c_func
(paren
id|ioaddr
op_plus
id|reg
comma
id|buf
comma
id|len
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* 64 bit alignment is required for memory to memory DMA */
r_if
c_cond
(paren
(paren
r_int
)paren
id|buf
op_amp
l_int|4
)paren
(brace
op_star
(paren
(paren
id|u32
op_star
)paren
id|buf
)paren
op_assign
id|SMC_inl
c_func
(paren
id|ioaddr
comma
id|reg
)paren
suffix:semicolon
id|buf
op_add_assign
l_int|4
suffix:semicolon
id|len
op_decrement
suffix:semicolon
)brace
id|len
op_mul_assign
l_int|4
suffix:semicolon
id|dmabuf
op_assign
id|dma_map_single
c_func
(paren
l_int|NULL
comma
id|buf
comma
id|len
comma
id|DMA_FROM_DEVICE
)paren
suffix:semicolon
id|DCSR
c_func
(paren
id|dma
)paren
op_assign
id|DCSR_NODESC
suffix:semicolon
id|DTADR
c_func
(paren
id|dma
)paren
op_assign
id|dmabuf
suffix:semicolon
id|DSADR
c_func
(paren
id|dma
)paren
op_assign
id|physaddr
op_plus
id|reg
suffix:semicolon
id|DCMD
c_func
(paren
id|dma
)paren
op_assign
(paren
id|DCMD_INCTRGADDR
op_or
id|DCMD_BURST32
op_or
id|DCMD_WIDTH4
op_or
(paren
id|DCMD_LENGTH
op_amp
id|len
)paren
)paren
suffix:semicolon
id|DCSR
c_func
(paren
id|dma
)paren
op_assign
id|DCSR_NODESC
op_or
id|DCSR_RUN
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
(paren
id|DCSR
c_func
(paren
id|dma
)paren
op_amp
id|DCSR_STOPSTATE
)paren
)paren
id|cpu_relax
c_func
(paren
)paren
suffix:semicolon
id|DCSR
c_func
(paren
id|dma
)paren
op_assign
l_int|0
suffix:semicolon
id|dma_unmap_single
c_func
(paren
l_int|NULL
comma
id|dmabuf
comma
id|len
comma
id|DMA_FROM_DEVICE
)paren
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifdef SMC_insw
DECL|macro|SMC_insw
macro_line|#undef SMC_insw
DECL|macro|SMC_insw
mdefine_line|#define SMC_insw(a, r, p, l) &bslash;&n;&t;smc_pxa_dma_insw(a, lp-&gt;physaddr, r, dev-&gt;dma, p, l)
r_static
r_inline
r_void
DECL|function|smc_pxa_dma_insw
id|smc_pxa_dma_insw
c_func
(paren
id|u_long
id|ioaddr
comma
id|u_long
id|physaddr
comma
r_int
id|reg
comma
r_int
id|dma
comma
id|u_char
op_star
id|buf
comma
r_int
id|len
)paren
(brace
id|dma_addr_t
id|dmabuf
suffix:semicolon
multiline_comment|/* fallback if no DMA available */
r_if
c_cond
(paren
id|dma
op_eq
(paren
r_int
r_char
)paren
op_minus
l_int|1
)paren
(brace
id|readsw
c_func
(paren
id|ioaddr
op_plus
id|reg
comma
id|buf
comma
id|len
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* 64 bit alignment is required for memory to memory DMA */
r_while
c_loop
(paren
(paren
r_int
)paren
id|buf
op_amp
l_int|6
)paren
(brace
op_star
(paren
(paren
id|u16
op_star
)paren
id|buf
)paren
op_assign
id|SMC_inw
c_func
(paren
id|ioaddr
comma
id|reg
)paren
suffix:semicolon
id|buf
op_add_assign
l_int|2
suffix:semicolon
id|len
op_decrement
suffix:semicolon
)brace
id|len
op_mul_assign
l_int|2
suffix:semicolon
id|dmabuf
op_assign
id|dma_map_single
c_func
(paren
l_int|NULL
comma
id|buf
comma
id|len
comma
id|DMA_FROM_DEVICE
)paren
suffix:semicolon
id|DCSR
c_func
(paren
id|dma
)paren
op_assign
id|DCSR_NODESC
suffix:semicolon
id|DTADR
c_func
(paren
id|dma
)paren
op_assign
id|dmabuf
suffix:semicolon
id|DSADR
c_func
(paren
id|dma
)paren
op_assign
id|physaddr
op_plus
id|reg
suffix:semicolon
id|DCMD
c_func
(paren
id|dma
)paren
op_assign
(paren
id|DCMD_INCTRGADDR
op_or
id|DCMD_BURST32
op_or
id|DCMD_WIDTH2
op_or
(paren
id|DCMD_LENGTH
op_amp
id|len
)paren
)paren
suffix:semicolon
id|DCSR
c_func
(paren
id|dma
)paren
op_assign
id|DCSR_NODESC
op_or
id|DCSR_RUN
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
(paren
id|DCSR
c_func
(paren
id|dma
)paren
op_amp
id|DCSR_STOPSTATE
)paren
)paren
id|cpu_relax
c_func
(paren
)paren
suffix:semicolon
id|DCSR
c_func
(paren
id|dma
)paren
op_assign
l_int|0
suffix:semicolon
id|dma_unmap_single
c_func
(paren
l_int|NULL
comma
id|dmabuf
comma
id|len
comma
id|DMA_FROM_DEVICE
)paren
suffix:semicolon
)brace
macro_line|#endif
r_static
r_void
DECL|function|smc_pxa_dma_irq
id|smc_pxa_dma_irq
c_func
(paren
r_int
id|dma
comma
r_void
op_star
id|dummy
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|DCSR
c_func
(paren
id|dma
)paren
op_assign
l_int|0
suffix:semicolon
)brace
macro_line|#endif  /* SMC_USE_PXA_DMA */
multiline_comment|/* Because of bank switching, the LAN91x uses only 16 I/O ports */
macro_line|#ifndef SMC_IO_SHIFT
DECL|macro|SMC_IO_SHIFT
mdefine_line|#define SMC_IO_SHIFT&t;0
macro_line|#endif
DECL|macro|SMC_IO_EXTENT
mdefine_line|#define SMC_IO_EXTENT&t;(16 &lt;&lt; SMC_IO_SHIFT)
multiline_comment|/*&n; . Bank Select Register:&n; .&n; .&t;&t;yyyy yyyy 0000 00xx&n; .&t;&t;xx &t;&t;= bank number&n; .&t;&t;yyyy yyyy&t;= 0x33, for identification purposes.&n;*/
DECL|macro|BANK_SELECT
mdefine_line|#define BANK_SELECT&t;&t;(14 &lt;&lt; SMC_IO_SHIFT)
singleline_comment|// Transmit Control Register
multiline_comment|/* BANK 0  */
DECL|macro|TCR_REG
mdefine_line|#define TCR_REG &t;SMC_REG(0x0000, 0)
DECL|macro|TCR_ENABLE
mdefine_line|#define TCR_ENABLE&t;0x0001&t;
singleline_comment|// When 1 we can transmit
DECL|macro|TCR_LOOP
mdefine_line|#define TCR_LOOP&t;0x0002&t;
singleline_comment|// Controls output pin LBK
DECL|macro|TCR_FORCOL
mdefine_line|#define TCR_FORCOL&t;0x0004&t;
singleline_comment|// When 1 will force a collision
DECL|macro|TCR_PAD_EN
mdefine_line|#define TCR_PAD_EN&t;0x0080&t;
singleline_comment|// When 1 will pad tx frames &lt; 64 bytes w/0
DECL|macro|TCR_NOCRC
mdefine_line|#define TCR_NOCRC&t;0x0100&t;
singleline_comment|// When 1 will not append CRC to tx frames
DECL|macro|TCR_MON_CSN
mdefine_line|#define TCR_MON_CSN&t;0x0400&t;
singleline_comment|// When 1 tx monitors carrier
DECL|macro|TCR_FDUPLX
mdefine_line|#define TCR_FDUPLX    &t;0x0800  
singleline_comment|// When 1 enables full duplex operation
DECL|macro|TCR_STP_SQET
mdefine_line|#define TCR_STP_SQET&t;0x1000&t;
singleline_comment|// When 1 stops tx if Signal Quality Error
DECL|macro|TCR_EPH_LOOP
mdefine_line|#define TCR_EPH_LOOP&t;0x2000&t;
singleline_comment|// When 1 enables EPH block loopback
DECL|macro|TCR_SWFDUP
mdefine_line|#define TCR_SWFDUP&t;0x8000&t;
singleline_comment|// When 1 enables Switched Full Duplex mode
DECL|macro|TCR_CLEAR
mdefine_line|#define TCR_CLEAR&t;0&t;/* do NOTHING */
multiline_comment|/* the default settings for the TCR register : */
DECL|macro|TCR_DEFAULT
mdefine_line|#define TCR_DEFAULT&t;(TCR_ENABLE | TCR_PAD_EN)
singleline_comment|// EPH Status Register
multiline_comment|/* BANK 0  */
DECL|macro|EPH_STATUS_REG
mdefine_line|#define EPH_STATUS_REG&t;SMC_REG(0x0002, 0)
DECL|macro|ES_TX_SUC
mdefine_line|#define ES_TX_SUC&t;0x0001&t;
singleline_comment|// Last TX was successful
DECL|macro|ES_SNGL_COL
mdefine_line|#define ES_SNGL_COL&t;0x0002&t;
singleline_comment|// Single collision detected for last tx
DECL|macro|ES_MUL_COL
mdefine_line|#define ES_MUL_COL&t;0x0004&t;
singleline_comment|// Multiple collisions detected for last tx
DECL|macro|ES_LTX_MULT
mdefine_line|#define ES_LTX_MULT&t;0x0008&t;
singleline_comment|// Last tx was a multicast
DECL|macro|ES_16COL
mdefine_line|#define ES_16COL&t;0x0010&t;
singleline_comment|// 16 Collisions Reached
DECL|macro|ES_SQET
mdefine_line|#define ES_SQET&t;&t;0x0020&t;
singleline_comment|// Signal Quality Error Test
DECL|macro|ES_LTXBRD
mdefine_line|#define ES_LTXBRD&t;0x0040&t;
singleline_comment|// Last tx was a broadcast
DECL|macro|ES_TXDEFR
mdefine_line|#define ES_TXDEFR&t;0x0080&t;
singleline_comment|// Transmit Deferred
DECL|macro|ES_LATCOL
mdefine_line|#define ES_LATCOL&t;0x0200&t;
singleline_comment|// Late collision detected on last tx
DECL|macro|ES_LOSTCARR
mdefine_line|#define ES_LOSTCARR&t;0x0400&t;
singleline_comment|// Lost Carrier Sense
DECL|macro|ES_EXC_DEF
mdefine_line|#define ES_EXC_DEF&t;0x0800&t;
singleline_comment|// Excessive Deferral
DECL|macro|ES_CTR_ROL
mdefine_line|#define ES_CTR_ROL&t;0x1000&t;
singleline_comment|// Counter Roll Over indication
DECL|macro|ES_LINK_OK
mdefine_line|#define ES_LINK_OK&t;0x4000&t;
singleline_comment|// Driven by inverted value of nLNK pin
DECL|macro|ES_TXUNRN
mdefine_line|#define ES_TXUNRN&t;0x8000&t;
singleline_comment|// Tx Underrun
singleline_comment|// Receive Control Register
multiline_comment|/* BANK 0  */
DECL|macro|RCR_REG
mdefine_line|#define RCR_REG&t;&t;SMC_REG(0x0004, 0)
DECL|macro|RCR_RX_ABORT
mdefine_line|#define RCR_RX_ABORT&t;0x0001&t;
singleline_comment|// Set if a rx frame was aborted
DECL|macro|RCR_PRMS
mdefine_line|#define RCR_PRMS&t;0x0002&t;
singleline_comment|// Enable promiscuous mode
DECL|macro|RCR_ALMUL
mdefine_line|#define RCR_ALMUL&t;0x0004&t;
singleline_comment|// When set accepts all multicast frames
DECL|macro|RCR_RXEN
mdefine_line|#define RCR_RXEN&t;0x0100&t;
singleline_comment|// IFF this is set, we can receive packets
DECL|macro|RCR_STRIP_CRC
mdefine_line|#define RCR_STRIP_CRC&t;0x0200&t;
singleline_comment|// When set strips CRC from rx packets
DECL|macro|RCR_ABORT_ENB
mdefine_line|#define RCR_ABORT_ENB&t;0x0200&t;
singleline_comment|// When set will abort rx on collision
DECL|macro|RCR_FILT_CAR
mdefine_line|#define RCR_FILT_CAR&t;0x0400&t;
singleline_comment|// When set filters leading 12 bit s of carrier
DECL|macro|RCR_SOFTRST
mdefine_line|#define RCR_SOFTRST&t;0x8000 &t;
singleline_comment|// resets the chip
multiline_comment|/* the normal settings for the RCR register : */
DECL|macro|RCR_DEFAULT
mdefine_line|#define RCR_DEFAULT&t;(RCR_STRIP_CRC | RCR_RXEN)
DECL|macro|RCR_CLEAR
mdefine_line|#define RCR_CLEAR&t;0x0&t;
singleline_comment|// set it to a base state
singleline_comment|// Counter Register
multiline_comment|/* BANK 0  */
DECL|macro|COUNTER_REG
mdefine_line|#define COUNTER_REG&t;SMC_REG(0x0006, 0)
singleline_comment|// Memory Information Register
multiline_comment|/* BANK 0  */
DECL|macro|MIR_REG
mdefine_line|#define MIR_REG&t;&t;SMC_REG(0x0008, 0)
singleline_comment|// Receive/Phy Control Register
multiline_comment|/* BANK 0  */
DECL|macro|RPC_REG
mdefine_line|#define RPC_REG&t;&t;SMC_REG(0x000A, 0)
DECL|macro|RPC_SPEED
mdefine_line|#define RPC_SPEED&t;0x2000&t;
singleline_comment|// When 1 PHY is in 100Mbps mode.
DECL|macro|RPC_DPLX
mdefine_line|#define RPC_DPLX&t;0x1000&t;
singleline_comment|// When 1 PHY is in Full-Duplex Mode
DECL|macro|RPC_ANEG
mdefine_line|#define RPC_ANEG&t;0x0800&t;
singleline_comment|// When 1 PHY is in Auto-Negotiate Mode
DECL|macro|RPC_LSXA_SHFT
mdefine_line|#define RPC_LSXA_SHFT&t;5&t;
singleline_comment|// Bits to shift LS2A,LS1A,LS0A to lsb
DECL|macro|RPC_LSXB_SHFT
mdefine_line|#define RPC_LSXB_SHFT&t;2&t;
singleline_comment|// Bits to get LS2B,LS1B,LS0B to lsb
DECL|macro|RPC_LED_100_10
mdefine_line|#define RPC_LED_100_10&t;(0x00)&t;
singleline_comment|// LED = 100Mbps OR&squot;s with 10Mbps link detect
DECL|macro|RPC_LED_RES
mdefine_line|#define RPC_LED_RES&t;(0x01)&t;
singleline_comment|// LED = Reserved
DECL|macro|RPC_LED_10
mdefine_line|#define RPC_LED_10&t;(0x02)&t;
singleline_comment|// LED = 10Mbps link detect
DECL|macro|RPC_LED_FD
mdefine_line|#define RPC_LED_FD&t;(0x03)&t;
singleline_comment|// LED = Full Duplex Mode
DECL|macro|RPC_LED_TX_RX
mdefine_line|#define RPC_LED_TX_RX&t;(0x04)&t;
singleline_comment|// LED = TX or RX packet occurred
DECL|macro|RPC_LED_100
mdefine_line|#define RPC_LED_100&t;(0x05)&t;
singleline_comment|// LED = 100Mbps link dectect
DECL|macro|RPC_LED_TX
mdefine_line|#define RPC_LED_TX&t;(0x06)&t;
singleline_comment|// LED = TX packet occurred
DECL|macro|RPC_LED_RX
mdefine_line|#define RPC_LED_RX&t;(0x07)&t;
singleline_comment|// LED = RX packet occurred
macro_line|#ifndef RPC_LSA_DEFAULT
DECL|macro|RPC_LSA_DEFAULT
mdefine_line|#define RPC_LSA_DEFAULT&t;RPC_LED_100
macro_line|#endif
macro_line|#ifndef RPC_LSB_DEFAULT
DECL|macro|RPC_LSB_DEFAULT
mdefine_line|#define RPC_LSB_DEFAULT RPC_LED_FD
macro_line|#endif
DECL|macro|RPC_DEFAULT
mdefine_line|#define RPC_DEFAULT (RPC_ANEG | (RPC_LSA_DEFAULT &lt;&lt; RPC_LSXA_SHFT) | (RPC_LSB_DEFAULT &lt;&lt; RPC_LSXB_SHFT) | RPC_SPEED | RPC_DPLX)
multiline_comment|/* Bank 0 0x0C is reserved */
singleline_comment|// Bank Select Register
multiline_comment|/* All Banks */
DECL|macro|BSR_REG
mdefine_line|#define BSR_REG&t;&t;0x000E
singleline_comment|// Configuration Reg
multiline_comment|/* BANK 1 */
DECL|macro|CONFIG_REG
mdefine_line|#define CONFIG_REG&t;SMC_REG(0x0000,&t;1)
DECL|macro|CONFIG_EXT_PHY
mdefine_line|#define CONFIG_EXT_PHY&t;0x0200&t;
singleline_comment|// 1=external MII, 0=internal Phy
DECL|macro|CONFIG_GPCNTRL
mdefine_line|#define CONFIG_GPCNTRL&t;0x0400&t;
singleline_comment|// Inverse value drives pin nCNTRL
DECL|macro|CONFIG_NO_WAIT
mdefine_line|#define CONFIG_NO_WAIT&t;0x1000&t;
singleline_comment|// When 1 no extra wait states on ISA bus
DECL|macro|CONFIG_EPH_POWER_EN
mdefine_line|#define CONFIG_EPH_POWER_EN 0x8000 
singleline_comment|// When 0 EPH is placed into low power mode.
singleline_comment|// Default is powered-up, Internal Phy, Wait States, and pin nCNTRL=low
DECL|macro|CONFIG_DEFAULT
mdefine_line|#define CONFIG_DEFAULT&t;(CONFIG_EPH_POWER_EN)
singleline_comment|// Base Address Register
multiline_comment|/* BANK 1 */
DECL|macro|BASE_REG
mdefine_line|#define BASE_REG&t;SMC_REG(0x0002, 1)
singleline_comment|// Individual Address Registers
multiline_comment|/* BANK 1 */
DECL|macro|ADDR0_REG
mdefine_line|#define ADDR0_REG&t;SMC_REG(0x0004, 1)
DECL|macro|ADDR1_REG
mdefine_line|#define ADDR1_REG&t;SMC_REG(0x0006, 1)
DECL|macro|ADDR2_REG
mdefine_line|#define ADDR2_REG&t;SMC_REG(0x0008, 1)
singleline_comment|// General Purpose Register
multiline_comment|/* BANK 1 */
DECL|macro|GP_REG
mdefine_line|#define GP_REG&t;&t;SMC_REG(0x000A, 1)
singleline_comment|// Control Register
multiline_comment|/* BANK 1 */
DECL|macro|CTL_REG
mdefine_line|#define CTL_REG&t;&t;SMC_REG(0x000C, 1)
DECL|macro|CTL_RCV_BAD
mdefine_line|#define CTL_RCV_BAD&t;0x4000 
singleline_comment|// When 1 bad CRC packets are received
DECL|macro|CTL_AUTO_RELEASE
mdefine_line|#define CTL_AUTO_RELEASE 0x0800 
singleline_comment|// When 1 tx pages are released automatically
DECL|macro|CTL_LE_ENABLE
mdefine_line|#define CTL_LE_ENABLE&t;0x0080 
singleline_comment|// When 1 enables Link Error interrupt
DECL|macro|CTL_CR_ENABLE
mdefine_line|#define CTL_CR_ENABLE&t;0x0040 
singleline_comment|// When 1 enables Counter Rollover interrupt
DECL|macro|CTL_TE_ENABLE
mdefine_line|#define CTL_TE_ENABLE&t;0x0020 
singleline_comment|// When 1 enables Transmit Error interrupt
DECL|macro|CTL_EEPROM_SELECT
mdefine_line|#define CTL_EEPROM_SELECT 0x0004 
singleline_comment|// Controls EEPROM reload &amp; store
DECL|macro|CTL_RELOAD
mdefine_line|#define CTL_RELOAD&t;0x0002 
singleline_comment|// When set reads EEPROM into registers
DECL|macro|CTL_STORE
mdefine_line|#define CTL_STORE&t;0x0001 
singleline_comment|// When set stores registers into EEPROM
singleline_comment|// MMU Command Register
multiline_comment|/* BANK 2 */
DECL|macro|MMU_CMD_REG
mdefine_line|#define MMU_CMD_REG&t;SMC_REG(0x0000, 2)
DECL|macro|MC_BUSY
mdefine_line|#define MC_BUSY&t;&t;1&t;
singleline_comment|// When 1 the last release has not completed
DECL|macro|MC_NOP
mdefine_line|#define MC_NOP&t;&t;(0&lt;&lt;5)&t;
singleline_comment|// No Op
DECL|macro|MC_ALLOC
mdefine_line|#define MC_ALLOC&t;(1&lt;&lt;5) &t;
singleline_comment|// OR with number of 256 byte packets
DECL|macro|MC_RESET
mdefine_line|#define MC_RESET&t;(2&lt;&lt;5)&t;
singleline_comment|// Reset MMU to initial state
DECL|macro|MC_REMOVE
mdefine_line|#define MC_REMOVE&t;(3&lt;&lt;5) &t;
singleline_comment|// Remove the current rx packet
DECL|macro|MC_RELEASE
mdefine_line|#define MC_RELEASE  &t;(4&lt;&lt;5) &t;
singleline_comment|// Remove and release the current rx packet
DECL|macro|MC_FREEPKT
mdefine_line|#define MC_FREEPKT  &t;(5&lt;&lt;5) &t;
singleline_comment|// Release packet in PNR register
DECL|macro|MC_ENQUEUE
mdefine_line|#define MC_ENQUEUE&t;(6&lt;&lt;5)&t;
singleline_comment|// Enqueue the packet for transmit
DECL|macro|MC_RSTTXFIFO
mdefine_line|#define MC_RSTTXFIFO&t;(7&lt;&lt;5)&t;
singleline_comment|// Reset the TX FIFOs
singleline_comment|// Packet Number Register
multiline_comment|/* BANK 2 */
DECL|macro|PN_REG
mdefine_line|#define PN_REG&t;&t;SMC_REG(0x0002, 2)
singleline_comment|// Allocation Result Register
multiline_comment|/* BANK 2 */
DECL|macro|AR_REG
mdefine_line|#define AR_REG&t;&t;SMC_REG(0x0003, 2)
DECL|macro|AR_FAILED
mdefine_line|#define AR_FAILED&t;0x80&t;
singleline_comment|// Alocation Failed
singleline_comment|// TX FIFO Ports Register
multiline_comment|/* BANK 2 */
DECL|macro|TXFIFO_REG
mdefine_line|#define TXFIFO_REG&t;SMC_REG(0x0004, 2)
DECL|macro|TXFIFO_TEMPTY
mdefine_line|#define TXFIFO_TEMPTY&t;0x80&t;
singleline_comment|// TX FIFO Empty
singleline_comment|// RX FIFO Ports Register
multiline_comment|/* BANK 2 */
DECL|macro|RXFIFO_REG
mdefine_line|#define RXFIFO_REG&t;SMC_REG(0x0005, 2)
DECL|macro|RXFIFO_REMPTY
mdefine_line|#define RXFIFO_REMPTY&t;0x80&t;
singleline_comment|// RX FIFO Empty
DECL|macro|FIFO_REG
mdefine_line|#define FIFO_REG&t;SMC_REG(0x0004, 2)
singleline_comment|// Pointer Register
multiline_comment|/* BANK 2 */
DECL|macro|PTR_REG
mdefine_line|#define PTR_REG&t;&t;SMC_REG(0x0006, 2)
DECL|macro|PTR_RCV
mdefine_line|#define PTR_RCV&t;&t;0x8000 
singleline_comment|// 1=Receive area, 0=Transmit area
DECL|macro|PTR_AUTOINC
mdefine_line|#define PTR_AUTOINC &t;0x4000 
singleline_comment|// Auto increment the pointer on each access
DECL|macro|PTR_READ
mdefine_line|#define PTR_READ&t;0x2000 
singleline_comment|// When 1 the operation is a read
singleline_comment|// Data Register
multiline_comment|/* BANK 2 */
DECL|macro|DATA_REG
mdefine_line|#define DATA_REG&t;SMC_REG(0x0008, 2)
singleline_comment|// Interrupt Status/Acknowledge Register
multiline_comment|/* BANK 2 */
DECL|macro|INT_REG
mdefine_line|#define INT_REG&t;&t;SMC_REG(0x000C, 2)
singleline_comment|// Interrupt Mask Register
multiline_comment|/* BANK 2 */
DECL|macro|IM_REG
mdefine_line|#define IM_REG&t;&t;SMC_REG(0x000D, 2)
DECL|macro|IM_MDINT
mdefine_line|#define IM_MDINT&t;0x80 
singleline_comment|// PHY MI Register 18 Interrupt
DECL|macro|IM_ERCV_INT
mdefine_line|#define IM_ERCV_INT&t;0x40 
singleline_comment|// Early Receive Interrupt
DECL|macro|IM_EPH_INT
mdefine_line|#define IM_EPH_INT&t;0x20 
singleline_comment|// Set by Ethernet Protocol Handler section
DECL|macro|IM_RX_OVRN_INT
mdefine_line|#define IM_RX_OVRN_INT&t;0x10 
singleline_comment|// Set by Receiver Overruns
DECL|macro|IM_ALLOC_INT
mdefine_line|#define IM_ALLOC_INT&t;0x08 
singleline_comment|// Set when allocation request is completed
DECL|macro|IM_TX_EMPTY_INT
mdefine_line|#define IM_TX_EMPTY_INT&t;0x04 
singleline_comment|// Set if the TX FIFO goes empty
DECL|macro|IM_TX_INT
mdefine_line|#define IM_TX_INT&t;0x02 
singleline_comment|// Transmit Interrupt
DECL|macro|IM_RCV_INT
mdefine_line|#define IM_RCV_INT&t;0x01 
singleline_comment|// Receive Interrupt
singleline_comment|// Multicast Table Registers
multiline_comment|/* BANK 3 */
DECL|macro|MCAST_REG1
mdefine_line|#define MCAST_REG1&t;SMC_REG(0x0000, 3)
DECL|macro|MCAST_REG2
mdefine_line|#define MCAST_REG2&t;SMC_REG(0x0002, 3)
DECL|macro|MCAST_REG3
mdefine_line|#define MCAST_REG3&t;SMC_REG(0x0004, 3)
DECL|macro|MCAST_REG4
mdefine_line|#define MCAST_REG4&t;SMC_REG(0x0006, 3)
singleline_comment|// Management Interface Register (MII)
multiline_comment|/* BANK 3 */
DECL|macro|MII_REG
mdefine_line|#define MII_REG&t;&t;SMC_REG(0x0008, 3)
DECL|macro|MII_MSK_CRS100
mdefine_line|#define MII_MSK_CRS100&t;0x4000 
singleline_comment|// Disables CRS100 detection during tx half dup
DECL|macro|MII_MDOE
mdefine_line|#define MII_MDOE&t;0x0008 
singleline_comment|// MII Output Enable
DECL|macro|MII_MCLK
mdefine_line|#define MII_MCLK&t;0x0004 
singleline_comment|// MII Clock, pin MDCLK
DECL|macro|MII_MDI
mdefine_line|#define MII_MDI&t;&t;0x0002 
singleline_comment|// MII Input, pin MDI
DECL|macro|MII_MDO
mdefine_line|#define MII_MDO&t;&t;0x0001 
singleline_comment|// MII Output, pin MDO
singleline_comment|// Revision Register
multiline_comment|/* BANK 3 */
multiline_comment|/* ( hi: chip id   low: rev # ) */
DECL|macro|REV_REG
mdefine_line|#define REV_REG&t;&t;SMC_REG(0x000A, 3)
singleline_comment|// Early RCV Register
multiline_comment|/* BANK 3 */
multiline_comment|/* this is NOT on SMC9192 */
DECL|macro|ERCV_REG
mdefine_line|#define ERCV_REG&t;SMC_REG(0x000C, 3)
DECL|macro|ERCV_RCV_DISCRD
mdefine_line|#define ERCV_RCV_DISCRD&t;0x0080 
singleline_comment|// When 1 discards a packet being received
DECL|macro|ERCV_THRESHOLD
mdefine_line|#define ERCV_THRESHOLD&t;0x001F 
singleline_comment|// ERCV Threshold Mask
singleline_comment|// External Register
multiline_comment|/* BANK 7 */
DECL|macro|EXT_REG
mdefine_line|#define EXT_REG&t;&t;SMC_REG(0x0000, 7)
DECL|macro|CHIP_9192
mdefine_line|#define CHIP_9192&t;3
DECL|macro|CHIP_9194
mdefine_line|#define CHIP_9194&t;4
DECL|macro|CHIP_9195
mdefine_line|#define CHIP_9195&t;5
DECL|macro|CHIP_9196
mdefine_line|#define CHIP_9196&t;6
DECL|macro|CHIP_91100
mdefine_line|#define CHIP_91100&t;7
DECL|macro|CHIP_91100FD
mdefine_line|#define CHIP_91100FD&t;8
DECL|macro|CHIP_91111FD
mdefine_line|#define CHIP_91111FD&t;9
DECL|variable|chip_ids
r_static
r_const
r_char
op_star
id|chip_ids
(braket
l_int|16
)braket
op_assign
(brace
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
multiline_comment|/* 3 */
l_string|&quot;SMC91C90/91C92&quot;
comma
multiline_comment|/* 4 */
l_string|&quot;SMC91C94&quot;
comma
multiline_comment|/* 5 */
l_string|&quot;SMC91C95&quot;
comma
multiline_comment|/* 6 */
l_string|&quot;SMC91C96&quot;
comma
multiline_comment|/* 7 */
l_string|&quot;SMC91C100&quot;
comma
multiline_comment|/* 8 */
l_string|&quot;SMC91C100FD&quot;
comma
multiline_comment|/* 9 */
l_string|&quot;SMC91C11xFD&quot;
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
)brace
suffix:semicolon
multiline_comment|/*&n; . Transmit status bits&n;*/
DECL|macro|TS_SUCCESS
mdefine_line|#define TS_SUCCESS 0x0001
DECL|macro|TS_LOSTCAR
mdefine_line|#define TS_LOSTCAR 0x0400
DECL|macro|TS_LATCOL
mdefine_line|#define TS_LATCOL  0x0200
DECL|macro|TS_16COL
mdefine_line|#define TS_16COL   0x0010
multiline_comment|/*&n; . Receive status bits&n;*/
DECL|macro|RS_ALGNERR
mdefine_line|#define RS_ALGNERR&t;0x8000
DECL|macro|RS_BRODCAST
mdefine_line|#define RS_BRODCAST&t;0x4000
DECL|macro|RS_BADCRC
mdefine_line|#define RS_BADCRC&t;0x2000
DECL|macro|RS_ODDFRAME
mdefine_line|#define RS_ODDFRAME&t;0x1000
DECL|macro|RS_TOOLONG
mdefine_line|#define RS_TOOLONG&t;0x0800
DECL|macro|RS_TOOSHORT
mdefine_line|#define RS_TOOSHORT&t;0x0400
DECL|macro|RS_MULTICAST
mdefine_line|#define RS_MULTICAST&t;0x0001
DECL|macro|RS_ERRORS
mdefine_line|#define RS_ERRORS&t;(RS_ALGNERR | RS_BADCRC | RS_TOOLONG | RS_TOOSHORT)
multiline_comment|/*&n; * PHY IDs&n; *  LAN83C183 == LAN91C111 Internal PHY&n; */
DECL|macro|PHY_LAN83C183
mdefine_line|#define PHY_LAN83C183&t;0x0016f840
DECL|macro|PHY_LAN83C180
mdefine_line|#define PHY_LAN83C180&t;0x02821c50
multiline_comment|/*&n; * PHY Register Addresses (LAN91C111 Internal PHY)&n; *&n; * Generic PHY registers can be found in &lt;linux/mii.h&gt;&n; *&n; * These phy registers are specific to our on-board phy.&n; */
singleline_comment|// PHY Configuration Register 1
DECL|macro|PHY_CFG1_REG
mdefine_line|#define PHY_CFG1_REG&t;&t;0x10
DECL|macro|PHY_CFG1_LNKDIS
mdefine_line|#define PHY_CFG1_LNKDIS&t;&t;0x8000&t;
singleline_comment|// 1=Rx Link Detect Function disabled
DECL|macro|PHY_CFG1_XMTDIS
mdefine_line|#define PHY_CFG1_XMTDIS&t;&t;0x4000&t;
singleline_comment|// 1=TP Transmitter Disabled
DECL|macro|PHY_CFG1_XMTPDN
mdefine_line|#define PHY_CFG1_XMTPDN&t;&t;0x2000&t;
singleline_comment|// 1=TP Transmitter Powered Down
DECL|macro|PHY_CFG1_BYPSCR
mdefine_line|#define PHY_CFG1_BYPSCR&t;&t;0x0400&t;
singleline_comment|// 1=Bypass scrambler/descrambler
DECL|macro|PHY_CFG1_UNSCDS
mdefine_line|#define PHY_CFG1_UNSCDS&t;&t;0x0200&t;
singleline_comment|// 1=Unscramble Idle Reception Disable
DECL|macro|PHY_CFG1_EQLZR
mdefine_line|#define PHY_CFG1_EQLZR&t;&t;0x0100&t;
singleline_comment|// 1=Rx Equalizer Disabled
DECL|macro|PHY_CFG1_CABLE
mdefine_line|#define PHY_CFG1_CABLE&t;&t;0x0080&t;
singleline_comment|// 1=STP(150ohm), 0=UTP(100ohm)
DECL|macro|PHY_CFG1_RLVL0
mdefine_line|#define PHY_CFG1_RLVL0&t;&t;0x0040&t;
singleline_comment|// 1=Rx Squelch level reduced by 4.5db
DECL|macro|PHY_CFG1_TLVL_SHIFT
mdefine_line|#define PHY_CFG1_TLVL_SHIFT&t;2&t;
singleline_comment|// Transmit Output Level Adjust
DECL|macro|PHY_CFG1_TLVL_MASK
mdefine_line|#define PHY_CFG1_TLVL_MASK&t;0x003C
DECL|macro|PHY_CFG1_TRF_MASK
mdefine_line|#define PHY_CFG1_TRF_MASK&t;0x0003&t;
singleline_comment|// Transmitter Rise/Fall time
singleline_comment|// PHY Configuration Register 2
DECL|macro|PHY_CFG2_REG
mdefine_line|#define PHY_CFG2_REG&t;&t;0x11
DECL|macro|PHY_CFG2_APOLDIS
mdefine_line|#define PHY_CFG2_APOLDIS&t;0x0020&t;
singleline_comment|// 1=Auto Polarity Correction disabled
DECL|macro|PHY_CFG2_JABDIS
mdefine_line|#define PHY_CFG2_JABDIS&t;&t;0x0010&t;
singleline_comment|// 1=Jabber disabled
DECL|macro|PHY_CFG2_MREG
mdefine_line|#define PHY_CFG2_MREG&t;&t;0x0008&t;
singleline_comment|// 1=Multiple register access (MII mgt)
DECL|macro|PHY_CFG2_INTMDIO
mdefine_line|#define PHY_CFG2_INTMDIO&t;0x0004&t;
singleline_comment|// 1=Interrupt signaled with MDIO pulseo
singleline_comment|// PHY Status Output (and Interrupt status) Register
DECL|macro|PHY_INT_REG
mdefine_line|#define PHY_INT_REG&t;&t;0x12&t;
singleline_comment|// Status Output (Interrupt Status)
DECL|macro|PHY_INT_INT
mdefine_line|#define PHY_INT_INT&t;&t;0x8000&t;
singleline_comment|// 1=bits have changed since last read
DECL|macro|PHY_INT_LNKFAIL
mdefine_line|#define PHY_INT_LNKFAIL&t;&t;0x4000&t;
singleline_comment|// 1=Link Not detected
DECL|macro|PHY_INT_LOSSSYNC
mdefine_line|#define PHY_INT_LOSSSYNC&t;0x2000&t;
singleline_comment|// 1=Descrambler has lost sync
DECL|macro|PHY_INT_CWRD
mdefine_line|#define PHY_INT_CWRD&t;&t;0x1000&t;
singleline_comment|// 1=Invalid 4B5B code detected on rx
DECL|macro|PHY_INT_SSD
mdefine_line|#define PHY_INT_SSD&t;&t;0x0800&t;
singleline_comment|// 1=No Start Of Stream detected on rx
DECL|macro|PHY_INT_ESD
mdefine_line|#define PHY_INT_ESD&t;&t;0x0400&t;
singleline_comment|// 1=No End Of Stream detected on rx
DECL|macro|PHY_INT_RPOL
mdefine_line|#define PHY_INT_RPOL&t;&t;0x0200&t;
singleline_comment|// 1=Reverse Polarity detected
DECL|macro|PHY_INT_JAB
mdefine_line|#define PHY_INT_JAB&t;&t;0x0100&t;
singleline_comment|// 1=Jabber detected
DECL|macro|PHY_INT_SPDDET
mdefine_line|#define PHY_INT_SPDDET&t;&t;0x0080&t;
singleline_comment|// 1=100Base-TX mode, 0=10Base-T mode
DECL|macro|PHY_INT_DPLXDET
mdefine_line|#define PHY_INT_DPLXDET&t;&t;0x0040&t;
singleline_comment|// 1=Device in Full Duplex
singleline_comment|// PHY Interrupt/Status Mask Register
DECL|macro|PHY_MASK_REG
mdefine_line|#define PHY_MASK_REG&t;&t;0x13&t;
singleline_comment|// Interrupt Mask
singleline_comment|// Uses the same bit definitions as PHY_INT_REG
multiline_comment|/*&n; * SMC91C96 ethernet config and status registers.&n; * These are in the &quot;attribute&quot; space.&n; */
DECL|macro|ECOR
mdefine_line|#define ECOR&t;&t;&t;0x8000
DECL|macro|ECOR_RESET
mdefine_line|#define ECOR_RESET&t;&t;0x80
DECL|macro|ECOR_LEVEL_IRQ
mdefine_line|#define ECOR_LEVEL_IRQ&t;&t;0x40
DECL|macro|ECOR_WR_ATTRIB
mdefine_line|#define ECOR_WR_ATTRIB&t;&t;0x04
DECL|macro|ECOR_ENABLE
mdefine_line|#define ECOR_ENABLE&t;&t;0x01
DECL|macro|ECSR
mdefine_line|#define ECSR&t;&t;&t;0x8002
DECL|macro|ECSR_IOIS8
mdefine_line|#define ECSR_IOIS8&t;&t;0x20
DECL|macro|ECSR_PWRDWN
mdefine_line|#define ECSR_PWRDWN&t;&t;0x04
DECL|macro|ECSR_INT
mdefine_line|#define ECSR_INT&t;&t;0x02
DECL|macro|ATTRIB_SIZE
mdefine_line|#define ATTRIB_SIZE&t;&t;((64*1024) &lt;&lt; SMC_IO_SHIFT)
multiline_comment|/*&n; * Macros to abstract register access according to the data bus&n; * capabilities.  Please use those and not the in/out primitives.&n; * Note: the following macros do *not* select the bank -- this must&n; * be done separately as needed in the main code.  The SMC_REG() macro&n; * only uses the bank argument for debugging purposes (when enabled).&n; */
macro_line|#if SMC_DEBUG &gt; 0
DECL|macro|SMC_REG
mdefine_line|#define SMC_REG(reg, bank)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;({&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;int __b = SMC_CURRENT_BANK();&t;&t;&t;&t;&bslash;&n;&t;&t;if (unlikely((__b &amp; ~0xf0) != (0x3300 | bank))) {&t;&bslash;&n;&t;&t;&t;printk( &quot;%s: bank reg screwed (0x%04x)&bslash;n&quot;,&t;&bslash;&n;&t;&t;&t;&t;CARDNAME, __b );&t;&t;&t;&bslash;&n;&t;&t;&t;BUG();&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;}&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;reg&lt;&lt;SMC_IO_SHIFT;&t;&t;&t;&t;&t;&bslash;&n;&t;})
macro_line|#else
DECL|macro|SMC_REG
mdefine_line|#define SMC_REG(reg, bank)&t;(reg&lt;&lt;SMC_IO_SHIFT)
macro_line|#endif
macro_line|#if SMC_CAN_USE_8BIT
DECL|macro|SMC_GET_PN
mdefine_line|#define SMC_GET_PN()&t;&t;SMC_inb( ioaddr, PN_REG )
DECL|macro|SMC_SET_PN
mdefine_line|#define SMC_SET_PN(x)&t;&t;SMC_outb( x, ioaddr, PN_REG )
DECL|macro|SMC_GET_AR
mdefine_line|#define SMC_GET_AR()&t;&t;SMC_inb( ioaddr, AR_REG )
DECL|macro|SMC_GET_TXFIFO
mdefine_line|#define SMC_GET_TXFIFO()&t;SMC_inb( ioaddr, TXFIFO_REG )
DECL|macro|SMC_GET_RXFIFO
mdefine_line|#define SMC_GET_RXFIFO()&t;SMC_inb( ioaddr, RXFIFO_REG )
DECL|macro|SMC_GET_INT
mdefine_line|#define SMC_GET_INT()&t;&t;SMC_inb( ioaddr, INT_REG )
DECL|macro|SMC_ACK_INT
mdefine_line|#define SMC_ACK_INT(x)&t;&t;SMC_outb( x, ioaddr, INT_REG )
DECL|macro|SMC_GET_INT_MASK
mdefine_line|#define SMC_GET_INT_MASK()&t;SMC_inb( ioaddr, IM_REG )
DECL|macro|SMC_SET_INT_MASK
mdefine_line|#define SMC_SET_INT_MASK(x)&t;SMC_outb( x, ioaddr, IM_REG )
macro_line|#else
DECL|macro|SMC_GET_PN
mdefine_line|#define SMC_GET_PN()&t;&t;(SMC_inw( ioaddr, PN_REG ) &amp; 0xFF)
DECL|macro|SMC_SET_PN
mdefine_line|#define SMC_SET_PN(x)&t;&t;SMC_outw( x, ioaddr, PN_REG )
DECL|macro|SMC_GET_AR
mdefine_line|#define SMC_GET_AR()&t;&t;(SMC_inw( ioaddr, PN_REG ) &gt;&gt; 8)
DECL|macro|SMC_GET_TXFIFO
mdefine_line|#define SMC_GET_TXFIFO()&t;(SMC_inw( ioaddr, TXFIFO_REG ) &amp; 0xFF)
DECL|macro|SMC_GET_RXFIFO
mdefine_line|#define SMC_GET_RXFIFO()&t;(SMC_inw( ioaddr, TXFIFO_REG ) &gt;&gt; 8)
DECL|macro|SMC_GET_INT
mdefine_line|#define SMC_GET_INT()&t;&t;(SMC_inw( ioaddr, INT_REG ) &amp; 0xFF)
DECL|macro|SMC_ACK_INT
mdefine_line|#define SMC_ACK_INT(x)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;unsigned long __flags;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;int __mask;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;local_irq_save(__flags);&t;&t;&t;&t;&bslash;&n;&t;&t;__mask = SMC_inw( ioaddr, INT_REG ) &amp; ~0xff;&t;&t;&bslash;&n;&t;&t;SMC_outw( __mask | (x), ioaddr, INT_REG );&t;&t;&bslash;&n;&t;&t;local_irq_restore(__flags);&t;&t;&t;&t;&bslash;&n;&t;} while (0)
DECL|macro|SMC_GET_INT_MASK
mdefine_line|#define SMC_GET_INT_MASK()&t;(SMC_inw( ioaddr, INT_REG ) &gt;&gt; 8)
DECL|macro|SMC_SET_INT_MASK
mdefine_line|#define SMC_SET_INT_MASK(x)&t;SMC_outw( (x) &lt;&lt; 8, ioaddr, INT_REG )
macro_line|#endif
DECL|macro|SMC_CURRENT_BANK
mdefine_line|#define SMC_CURRENT_BANK()&t;SMC_inw( ioaddr, BANK_SELECT )
DECL|macro|SMC_SELECT_BANK
mdefine_line|#define SMC_SELECT_BANK(x)&t;SMC_outw( x, ioaddr, BANK_SELECT )
DECL|macro|SMC_GET_BASE
mdefine_line|#define SMC_GET_BASE()&t;&t;SMC_inw( ioaddr, BASE_REG )
DECL|macro|SMC_SET_BASE
mdefine_line|#define SMC_SET_BASE(x)&t;&t;SMC_outw( x, ioaddr, BASE_REG )
DECL|macro|SMC_GET_CONFIG
mdefine_line|#define SMC_GET_CONFIG()&t;SMC_inw( ioaddr, CONFIG_REG )
DECL|macro|SMC_SET_CONFIG
mdefine_line|#define SMC_SET_CONFIG(x)&t;SMC_outw( x, ioaddr, CONFIG_REG )
DECL|macro|SMC_GET_COUNTER
mdefine_line|#define SMC_GET_COUNTER()&t;SMC_inw( ioaddr, COUNTER_REG )
DECL|macro|SMC_GET_CTL
mdefine_line|#define SMC_GET_CTL()&t;&t;SMC_inw( ioaddr, CTL_REG )
DECL|macro|SMC_SET_CTL
mdefine_line|#define SMC_SET_CTL(x)&t;&t;SMC_outw( x, ioaddr, CTL_REG )
DECL|macro|SMC_GET_MII
mdefine_line|#define SMC_GET_MII()&t;&t;SMC_inw( ioaddr, MII_REG )
DECL|macro|SMC_SET_MII
mdefine_line|#define SMC_SET_MII(x)&t;&t;SMC_outw( x, ioaddr, MII_REG )
DECL|macro|SMC_GET_MIR
mdefine_line|#define SMC_GET_MIR()&t;&t;SMC_inw( ioaddr, MIR_REG )
DECL|macro|SMC_SET_MIR
mdefine_line|#define SMC_SET_MIR(x)&t;&t;SMC_outw( x, ioaddr, MIR_REG )
DECL|macro|SMC_GET_MMU_CMD
mdefine_line|#define SMC_GET_MMU_CMD()&t;SMC_inw( ioaddr, MMU_CMD_REG )
DECL|macro|SMC_SET_MMU_CMD
mdefine_line|#define SMC_SET_MMU_CMD(x)&t;SMC_outw( x, ioaddr, MMU_CMD_REG )
DECL|macro|SMC_GET_FIFO
mdefine_line|#define SMC_GET_FIFO()&t;&t;SMC_inw( ioaddr, FIFO_REG )
DECL|macro|SMC_GET_PTR
mdefine_line|#define SMC_GET_PTR()&t;&t;SMC_inw( ioaddr, PTR_REG )
DECL|macro|SMC_SET_PTR
mdefine_line|#define SMC_SET_PTR(x)&t;&t;SMC_outw( x, ioaddr, PTR_REG )
DECL|macro|SMC_GET_RCR
mdefine_line|#define SMC_GET_RCR()&t;&t;SMC_inw( ioaddr, RCR_REG )
DECL|macro|SMC_SET_RCR
mdefine_line|#define SMC_SET_RCR(x)&t;&t;SMC_outw( x, ioaddr, RCR_REG )
DECL|macro|SMC_GET_REV
mdefine_line|#define SMC_GET_REV()&t;&t;SMC_inw( ioaddr, REV_REG )
DECL|macro|SMC_GET_RPC
mdefine_line|#define SMC_GET_RPC()&t;&t;SMC_inw( ioaddr, RPC_REG )
DECL|macro|SMC_SET_RPC
mdefine_line|#define SMC_SET_RPC(x)&t;&t;SMC_outw( x, ioaddr, RPC_REG )
DECL|macro|SMC_GET_TCR
mdefine_line|#define SMC_GET_TCR()&t;&t;SMC_inw( ioaddr, TCR_REG )
DECL|macro|SMC_SET_TCR
mdefine_line|#define SMC_SET_TCR(x)&t;&t;SMC_outw( x, ioaddr, TCR_REG )
macro_line|#ifndef SMC_GET_MAC_ADDR
DECL|macro|SMC_GET_MAC_ADDR
mdefine_line|#define SMC_GET_MAC_ADDR(addr)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;unsigned int __v;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__v = SMC_inw( ioaddr, ADDR0_REG );&t;&t;&t;&bslash;&n;&t;&t;addr[0] = __v; addr[1] = __v &gt;&gt; 8;&t;&t;&t;&bslash;&n;&t;&t;__v = SMC_inw( ioaddr, ADDR1_REG );&t;&t;&t;&bslash;&n;&t;&t;addr[2] = __v; addr[3] = __v &gt;&gt; 8;&t;&t;&t;&bslash;&n;&t;&t;__v = SMC_inw( ioaddr, ADDR2_REG );&t;&t;&t;&bslash;&n;&t;&t;addr[4] = __v; addr[5] = __v &gt;&gt; 8;&t;&t;&t;&bslash;&n;&t;} while (0)
macro_line|#endif
DECL|macro|SMC_SET_MAC_ADDR
mdefine_line|#define SMC_SET_MAC_ADDR(addr)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;SMC_outw( addr[0]|(addr[1] &lt;&lt; 8), ioaddr, ADDR0_REG );&t;&bslash;&n;&t;&t;SMC_outw( addr[2]|(addr[3] &lt;&lt; 8), ioaddr, ADDR1_REG );&t;&bslash;&n;&t;&t;SMC_outw( addr[4]|(addr[5] &lt;&lt; 8), ioaddr, ADDR2_REG );&t;&bslash;&n;&t;} while (0)
DECL|macro|SMC_SET_MCAST
mdefine_line|#define SMC_SET_MCAST(x)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;const unsigned char *mt = (x);&t;&t;&t;&t;&bslash;&n;&t;&t;SMC_outw( mt[0] | (mt[1] &lt;&lt; 8), ioaddr, MCAST_REG1 );&t;&bslash;&n;&t;&t;SMC_outw( mt[2] | (mt[3] &lt;&lt; 8), ioaddr, MCAST_REG2 );&t;&bslash;&n;&t;&t;SMC_outw( mt[4] | (mt[5] &lt;&lt; 8), ioaddr, MCAST_REG3 );&t;&bslash;&n;&t;&t;SMC_outw( mt[6] | (mt[7] &lt;&lt; 8), ioaddr, MCAST_REG4 );&t;&bslash;&n;&t;} while (0)
macro_line|#if SMC_CAN_USE_32BIT
multiline_comment|/*&n; * Some setups just can&squot;t write 8 or 16 bits reliably when not aligned&n; * to a 32 bit boundary.  I tell you that exists!&n; * We re-do the ones here that can be easily worked around if they can have&n; * their low parts written to 0 without adverse effects.&n; */
DECL|macro|SMC_SELECT_BANK
macro_line|#undef SMC_SELECT_BANK
DECL|macro|SMC_SELECT_BANK
mdefine_line|#define SMC_SELECT_BANK(x)&t;SMC_outl( (x)&lt;&lt;16, ioaddr, 12&lt;&lt;SMC_IO_SHIFT )
DECL|macro|SMC_SET_RPC
macro_line|#undef SMC_SET_RPC
DECL|macro|SMC_SET_RPC
mdefine_line|#define SMC_SET_RPC(x)&t;&t;SMC_outl( (x)&lt;&lt;16, ioaddr, SMC_REG(8, 0) )
DECL|macro|SMC_SET_PN
macro_line|#undef SMC_SET_PN
DECL|macro|SMC_SET_PN
mdefine_line|#define SMC_SET_PN(x)&t;&t;SMC_outl( (x)&lt;&lt;16, ioaddr, SMC_REG(0, 2) )
DECL|macro|SMC_SET_PTR
macro_line|#undef SMC_SET_PTR
DECL|macro|SMC_SET_PTR
mdefine_line|#define SMC_SET_PTR(x)&t;&t;SMC_outl( (x)&lt;&lt;16, ioaddr, SMC_REG(4, 2) )
macro_line|#endif
macro_line|#if SMC_CAN_USE_32BIT
DECL|macro|SMC_PUT_PKT_HDR
mdefine_line|#define SMC_PUT_PKT_HDR(status, length)&t;&t;&t;&t;&t;&bslash;&n;&t;SMC_outl( (status) | (length) &lt;&lt; 16, ioaddr, DATA_REG )
DECL|macro|SMC_GET_PKT_HDR
mdefine_line|#define SMC_GET_PKT_HDR(status, length)&t;&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;unsigned int __val = SMC_inl( ioaddr, DATA_REG );&t;&bslash;&n;&t;&t;(status) = __val &amp; 0xffff;&t;&t;&t;&t;&bslash;&n;&t;&t;(length) = __val &gt;&gt; 16;&t;&t;&t;&t;&t;&bslash;&n;&t;} while (0)
macro_line|#else
DECL|macro|SMC_PUT_PKT_HDR
mdefine_line|#define SMC_PUT_PKT_HDR(status, length)&t;&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;SMC_outw( status, ioaddr, DATA_REG );&t;&t;&t;&bslash;&n;&t;&t;SMC_outw( length, ioaddr, DATA_REG );&t;&t;&t;&bslash;&n;&t;} while (0)
DECL|macro|SMC_GET_PKT_HDR
mdefine_line|#define SMC_GET_PKT_HDR(status, length)&t;&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;(status) = SMC_inw( ioaddr, DATA_REG );&t;&t;&t;&bslash;&n;&t;&t;(length) = SMC_inw( ioaddr, DATA_REG );&t;&t;&t;&bslash;&n;&t;} while (0)
macro_line|#endif
macro_line|#if SMC_CAN_USE_32BIT
DECL|macro|SMC_PUSH_DATA
mdefine_line|#define SMC_PUSH_DATA(p, l)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;char *__ptr = (p);&t;&t;&t;&t;&t;&bslash;&n;&t;&t;int __len = (l);&t;&t;&t;&t;&t;&bslash;&n;&t;&t;if (__len &gt;= 2 &amp;&amp; (unsigned long)__ptr &amp; 2) {&t;&t;&bslash;&n;&t;&t;&t;__len -= 2;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;SMC_outw( *(u16 *)__ptr, ioaddr, DATA_REG );&t;&bslash;&n;&t;&t;&t;__ptr += 2;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;}&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;SMC_outsl( ioaddr, DATA_REG, __ptr, __len &gt;&gt; 2);&t;&bslash;&n;&t;&t;if (__len &amp; 2) {&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;__ptr += (__len &amp; ~3);&t;&t;&t;&t;&bslash;&n;&t;&t;&t;SMC_outw( *((u16 *)__ptr), ioaddr, DATA_REG );&t;&bslash;&n;&t;&t;}&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;} while (0)
DECL|macro|SMC_PULL_DATA
mdefine_line|#define SMC_PULL_DATA(p, l)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;char *__ptr = (p);&t;&t;&t;&t;&t;&bslash;&n;&t;&t;int __len = (l);&t;&t;&t;&t;&t;&bslash;&n;&t;&t;if ((unsigned long)__ptr &amp; 2) {&t;&t;&t;&t;&bslash;&n;&t;&t;&t;/*&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t; * We want 32bit alignment here.&t;&t;&bslash;&n;&t;&t;&t; * Since some buses perform a full 32bit&t;&bslash;&n;&t;&t;&t; * fetch even for 16bit data we can&squot;t use&t;&bslash;&n;&t;&t;&t; * SMC_inw() here.  Back both source (on chip&t;&bslash;&n;&t;&t;&t; * and destination) pointers of 2 bytes.&t;&bslash;&n;&t;&t;&t; */&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;__ptr -= 2;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;__len += 2;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;SMC_SET_PTR( 2|PTR_READ|PTR_RCV|PTR_AUTOINC );&t;&bslash;&n;&t;&t;}&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__len += 2;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;SMC_insl( ioaddr, DATA_REG, __ptr, __len &gt;&gt; 2);&t;&t;&bslash;&n;&t;} while (0)
macro_line|#elif SMC_CAN_USE_16BIT
DECL|macro|SMC_PUSH_DATA
mdefine_line|#define SMC_PUSH_DATA(p, l)&t;SMC_outsw( ioaddr, DATA_REG, p, (l) &gt;&gt; 1 )
DECL|macro|SMC_PULL_DATA
mdefine_line|#define SMC_PULL_DATA(p, l)&t;SMC_insw ( ioaddr, DATA_REG, p, (l) &gt;&gt; 1 )
macro_line|#elif SMC_CAN_USE_8BIT
DECL|macro|SMC_PUSH_DATA
mdefine_line|#define SMC_PUSH_DATA(p, l)&t;SMC_outsb( ioaddr, DATA_REG, p, l )
DECL|macro|SMC_PULL_DATA
mdefine_line|#define SMC_PULL_DATA(p, l)&t;SMC_insb ( ioaddr, DATA_REG, p, l )
macro_line|#endif
macro_line|#if ! SMC_CAN_USE_16BIT
DECL|macro|SMC_outw
mdefine_line|#define SMC_outw(x, ioaddr, reg)&t;&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;unsigned int __val16 = (x);&t;&t;&t;&t;&bslash;&n;&t;&t;SMC_outb( __val16, ioaddr, reg );&t;&t;&t;&bslash;&n;&t;&t;SMC_outb( __val16 &gt;&gt; 8, ioaddr, reg + (1 &lt;&lt; SMC_IO_SHIFT));&bslash;&n;&t;} while (0)
DECL|macro|SMC_inw
mdefine_line|#define SMC_inw(ioaddr, reg)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;({&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;unsigned int __val16;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__val16 =  SMC_inb( ioaddr, reg );&t;&t;&t;&bslash;&n;&t;&t;__val16 |= SMC_inb( ioaddr, reg + (1 &lt;&lt; SMC_IO_SHIFT)) &lt;&lt; 8; &bslash;&n;&t;&t;__val16;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;})
macro_line|#endif
macro_line|#if !defined (SMC_INTERRUPT_PREAMBLE)
DECL|macro|SMC_INTERRUPT_PREAMBLE
macro_line|# define SMC_INTERRUPT_PREAMBLE
macro_line|#endif
macro_line|#endif  /* _SMC91X_H_ */
eof
