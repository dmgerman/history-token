multiline_comment|/*&n; *  linux/include/asm-m68k/ide.h&n; *&n; *  Copyright (C) 1994-1996  Linus Torvalds &amp; authors&n; */
multiline_comment|/* Copyright(c) 1996 Kars de Jong */
multiline_comment|/* Based on the ide driver from 1.2.13pl8 */
multiline_comment|/*&n; * Credits (alphabetical):&n; *&n; *  - Bjoern Brauel&n; *  - Kars de Jong&n; *  - Torsten Ebeling&n; *  - Dwight Engen&n; *  - Thorsten Floeck&n; *  - Roman Hodek&n; *  - Guenther Kelleter&n; *  - Chris Lawrence&n; *  - Michael Rausch&n; *  - Christian Sauer&n; *  - Michael Schmitz&n; *  - Jes Soerensen&n; *  - Michael Thurm&n; *  - Geert Uytterhoeven&n; */
macro_line|#ifndef _M68K_IDE_H
DECL|macro|_M68K_IDE_H
mdefine_line|#define _M68K_IDE_H
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#ifdef CONFIG_ATARI
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;asm/atari_stdma.h&gt;
macro_line|#endif
macro_line|#ifdef CONFIG_MAC
macro_line|#include &lt;asm/macints.h&gt;
macro_line|#endif
macro_line|#ifndef MAX_HWIFS
DECL|macro|MAX_HWIFS
mdefine_line|#define MAX_HWIFS&t;4&t;/* same as the other archs */
macro_line|#endif
DECL|function|ide_default_irq
r_static
id|__inline__
r_int
id|ide_default_irq
c_func
(paren
r_int
r_int
id|base
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ide_default_io_base
r_static
id|__inline__
r_int
r_int
id|ide_default_io_base
c_func
(paren
r_int
id|index
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Set up a hw structure for a specified data port, control port and IRQ.&n; * This should follow whatever the default interface uses.&n; */
DECL|function|ide_init_hwif_ports
r_static
id|__inline__
r_void
id|ide_init_hwif_ports
c_func
(paren
id|hw_regs_t
op_star
id|hw
comma
r_int
r_int
id|data_port
comma
r_int
r_int
id|ctrl_port
comma
r_int
op_star
id|irq
)paren
(brace
r_if
c_cond
(paren
id|data_port
op_logical_or
id|ctrl_port
)paren
id|printk
c_func
(paren
l_string|&quot;ide_init_hwif_ports: must not be called&bslash;n&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This registers the standard ports for this architecture with the IDE&n; * driver.&n; */
DECL|function|ide_init_default_hwifs
r_static
id|__inline__
r_void
id|ide_init_default_hwifs
c_func
(paren
r_void
)paren
(brace
)brace
multiline_comment|/*&n; * Get rid of defs from io.h - ide has its private and conflicting versions&n; * Since so far no single m68k platform uses ISA/PCI I/O space for IDE, we&n; * always use the `raw&squot; MMIO versions&n; */
DECL|macro|inb
macro_line|#undef inb
DECL|macro|inw
macro_line|#undef inw
DECL|macro|insw
macro_line|#undef insw
DECL|macro|inl
macro_line|#undef inl
DECL|macro|insl
macro_line|#undef insl
DECL|macro|outb
macro_line|#undef outb
DECL|macro|outw
macro_line|#undef outw
DECL|macro|outsw
macro_line|#undef outsw
DECL|macro|outl
macro_line|#undef outl
DECL|macro|outsl
macro_line|#undef outsl
DECL|macro|readb
macro_line|#undef readb
DECL|macro|readw
macro_line|#undef readw
DECL|macro|readl
macro_line|#undef readl
DECL|macro|writeb
macro_line|#undef writeb
DECL|macro|writew
macro_line|#undef writew
DECL|macro|writel
macro_line|#undef writel
DECL|macro|inb
mdefine_line|#define inb&t;&t;&t;&t;in_8
DECL|macro|inw
mdefine_line|#define inw&t;&t;&t;&t;in_be16
DECL|macro|insw
mdefine_line|#define insw(port, addr, n)&t;&t;raw_insw((u16 *)port, addr, n)
DECL|macro|inl
mdefine_line|#define inl&t;&t;&t;&t;in_be32
DECL|macro|insl
mdefine_line|#define insl(port, addr, n)&t;&t;raw_insl((u32 *)port, addr, n)
DECL|macro|outb
mdefine_line|#define outb(val, port)&t;&t;&t;out_8(port, val)
DECL|macro|outw
mdefine_line|#define outw(val, port)&t;&t;&t;out_be16(port, val)
DECL|macro|outsw
mdefine_line|#define outsw(port, addr, n)&t;&t;raw_outsw((u16 *)port, addr, n)
DECL|macro|outl
mdefine_line|#define outl(val, port)&t;&t;&t;out_be32(port, val)
DECL|macro|outsl
mdefine_line|#define outsl(port, addr, n)&t;&t;raw_outsl((u32 *)port, addr, n)
DECL|macro|readb
mdefine_line|#define readb&t;&t;&t;&t;in_8
DECL|macro|readw
mdefine_line|#define readw&t;&t;&t;&t;in_be16
DECL|macro|__ide_mm_insw
mdefine_line|#define __ide_mm_insw(port, addr, n)&t;raw_insw((u16 *)port, addr, n)
DECL|macro|readl
mdefine_line|#define readl&t;&t;&t;&t;in_be32
DECL|macro|__ide_mm_insl
mdefine_line|#define __ide_mm_insl(port, addr, n)&t;raw_insl((u32 *)port, addr, n)
DECL|macro|writeb
mdefine_line|#define writeb(val, port)&t;&t;out_8(port, val)
DECL|macro|writew
mdefine_line|#define writew(val, port)&t;&t;out_be16(port, val)
DECL|macro|__ide_mm_outsw
mdefine_line|#define __ide_mm_outsw(port, addr, n)&t;raw_outsw((u16 *)port, addr, n)
DECL|macro|writel
mdefine_line|#define writel(val, port)&t;&t;out_be32(port, val)
DECL|macro|__ide_mm_outsl
mdefine_line|#define __ide_mm_outsl(port, addr, n)&t;raw_outsl((u32 *)port, addr, n)
macro_line|#if defined(CONFIG_ATARI) || defined(CONFIG_Q40)
DECL|macro|insw_swapw
mdefine_line|#define insw_swapw(port, addr, n)&t;raw_insw_swapw((u16 *)port, addr, n)
DECL|macro|outsw_swapw
mdefine_line|#define outsw_swapw(port, addr, n)&t;raw_outsw_swapw((u16 *)port, addr, n)
macro_line|#endif
multiline_comment|/* Q40 and Atari have byteswapped IDE busses and since many interesting&n; * values in the identification string are text, chars and words they&n; * happened to be almost correct without swapping.. However *_capacity&n; * is needed for drives over 8 GB. RZ */
macro_line|#if defined(CONFIG_Q40) || defined(CONFIG_ATARI)
DECL|macro|M68K_IDE_SWAPW
mdefine_line|#define M68K_IDE_SWAPW  (MACH_IS_Q40 || MACH_IS_ATARI)
macro_line|#endif
macro_line|#ifdef CONFIG_BLK_DEV_FALCON_IDE
DECL|macro|IDE_ARCH_LOCK
mdefine_line|#define IDE_ARCH_LOCK
r_extern
r_int
id|falconide_intr_lock
suffix:semicolon
DECL|function|ide_release_lock
r_static
id|__inline__
r_void
id|ide_release_lock
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|MACH_IS_ATARI
)paren
(brace
r_if
c_cond
(paren
id|falconide_intr_lock
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;ide_release_lock: bug&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|falconide_intr_lock
op_assign
l_int|0
suffix:semicolon
id|stdma_release
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
r_static
id|__inline__
r_void
DECL|function|ide_get_lock
id|ide_get_lock
c_func
(paren
id|irqreturn_t
(paren
op_star
id|handler
)paren
(paren
r_int
comma
r_void
op_star
comma
r_struct
id|pt_regs
op_star
)paren
comma
r_void
op_star
id|data
)paren
(brace
r_if
c_cond
(paren
id|MACH_IS_ATARI
)paren
(brace
r_if
c_cond
(paren
id|falconide_intr_lock
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|in_interrupt
c_func
(paren
)paren
OG
l_int|0
)paren
id|panic
c_func
(paren
l_string|&quot;Falcon IDE hasn&squot;t ST-DMA lock in interrupt&quot;
)paren
suffix:semicolon
id|stdma_lock
c_func
(paren
id|handler
comma
id|data
)paren
suffix:semicolon
id|falconide_intr_lock
op_assign
l_int|1
suffix:semicolon
)brace
)brace
)brace
macro_line|#endif /* CONFIG_BLK_DEV_FALCON_IDE */
DECL|macro|IDE_ARCH_ACK_INTR
mdefine_line|#define IDE_ARCH_ACK_INTR
DECL|macro|ide_ack_intr
mdefine_line|#define ide_ack_intr(hwif)&t;((hwif)-&gt;hw.ack_intr ? (hwif)-&gt;hw.ack_intr(hwif) : 1)
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _M68K_IDE_H */
eof
