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
id|ide_ioreg_t
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
id|ide_ioreg_t
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
id|ide_ioreg_t
id|data_port
comma
id|ide_ioreg_t
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
DECL|macro|SUPPORT_SLOW_DATA_PORTS
macro_line|#undef SUPPORT_SLOW_DATA_PORTS
DECL|macro|SUPPORT_SLOW_DATA_PORTS
mdefine_line|#define SUPPORT_SLOW_DATA_PORTS 0
multiline_comment|/* this definition is used only on startup .. */
DECL|macro|HD_DATA
macro_line|#undef HD_DATA
DECL|macro|HD_DATA
mdefine_line|#define HD_DATA NULL
multiline_comment|/* get rid of defs from io.h - ide has its private and conflicting versions */
DECL|macro|inb
macro_line|#undef inb
DECL|macro|inw
macro_line|#undef inw
DECL|macro|outb
macro_line|#undef outb
DECL|macro|outw
macro_line|#undef outw
DECL|macro|inb_p
macro_line|#undef inb_p
DECL|macro|outb_p
macro_line|#undef outb_p
DECL|macro|insw
macro_line|#undef insw
DECL|macro|outsw
macro_line|#undef outsw
DECL|macro|insw_swapw
macro_line|#undef insw_swapw
DECL|macro|outsw_swapw
macro_line|#undef outsw_swapw
multiline_comment|/* &n; * define IO method and translation,&n; * so far only Q40 has ide-if on ISA &n;*/
macro_line|#ifndef CONFIG_Q40
DECL|macro|ADDR_TRANS_B
mdefine_line|#define ADDR_TRANS_B(_addr_) (_addr_)
DECL|macro|ADDR_TRANS_W
mdefine_line|#define ADDR_TRANS_W(_addr_) (_addr_)
macro_line|#else
DECL|macro|ADDR_TRANS_B
mdefine_line|#define ADDR_TRANS_B(_addr_) (MACH_IS_Q40 ? ((unsigned char *)Q40_ISA_IO_B(_addr_)) : (_addr_))
DECL|macro|ADDR_TRANS_W
mdefine_line|#define ADDR_TRANS_W(_addr_) (MACH_IS_Q40 ? ((unsigned char *)Q40_ISA_IO_W(_addr_)) : (_addr_))
macro_line|#endif
DECL|macro|inb
mdefine_line|#define inb(p)     in_8(ADDR_TRANS_B(p))
DECL|macro|inb_p
mdefine_line|#define inb_p(p)     in_8(ADDR_TRANS_B(p))
DECL|macro|inw
mdefine_line|#define inw(p)     in_be16(ADDR_TRANS_W(p))
DECL|macro|inw_p
mdefine_line|#define inw_p(p)     in_be16(ADDR_TRANS_W(p))
DECL|macro|outb
mdefine_line|#define outb(v,p)  out_8(ADDR_TRANS_B(p),v)
DECL|macro|outb_p
mdefine_line|#define outb_p(v,p)  out_8(ADDR_TRANS_B(p),v)
DECL|macro|outw
mdefine_line|#define outw(v,p)  out_be16(ADDR_TRANS_W(p),v)
DECL|macro|insw
mdefine_line|#define insw(port, buf, nr) raw_insw(ADDR_TRANS_W(port), buf, nr)
DECL|macro|outsw
mdefine_line|#define outsw(port, buf, nr) raw_outsw(ADDR_TRANS_W(port), buf, nr)
DECL|macro|insl
mdefine_line|#define insl(data_reg, buffer, wcount) insw(data_reg, buffer, (wcount)&lt;&lt;1)
DECL|macro|outsl
mdefine_line|#define outsl(data_reg, buffer, wcount) outsw(data_reg, buffer, (wcount)&lt;&lt;1)
macro_line|#if defined(CONFIG_ATARI) || defined(CONFIG_Q40)
DECL|macro|insl_swapw
mdefine_line|#define insl_swapw(data_reg, buffer, wcount) &bslash;&n;    insw_swapw(data_reg, buffer, (wcount)&lt;&lt;1)
DECL|macro|outsl_swapw
mdefine_line|#define outsl_swapw(data_reg, buffer, wcount) &bslash;&n;    outsw_swapw(data_reg, buffer, (wcount)&lt;&lt;1)
DECL|macro|insw_swapw
mdefine_line|#define insw_swapw(port, buf, nr) raw_insw_swapw(ADDR_TRANS_W(port), buf, nr)
DECL|macro|outsw_swapw
mdefine_line|#define outsw_swapw(port, buf, nr) raw_outsw_swapw(ADDR_TRANS_W(port),buf,nr)
macro_line|#endif /* CONFIG_ATARI || CONFIG_Q40 */
DECL|macro|ATA_ARCH_ACK_INTR
mdefine_line|#define ATA_ARCH_ACK_INTR
macro_line|#ifdef CONFIG_ATARI
DECL|macro|ATA_ARCH_LOCK
mdefine_line|#define ATA_ARCH_LOCK
DECL|function|ide_release_lock
r_static
id|__inline__
r_void
id|ide_release_lock
(paren
r_int
op_star
id|ide_lock
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
op_star
id|ide_lock
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
op_star
id|ide_lock
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
DECL|function|ide_get_lock
r_static
id|__inline__
r_void
id|ide_get_lock
(paren
r_int
op_star
id|ide_lock
comma
r_void
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
op_star
id|ide_lock
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
op_star
id|ide_lock
op_assign
l_int|1
suffix:semicolon
)brace
)brace
)brace
macro_line|#endif /* CONFIG_ATARI */
multiline_comment|/*&n; * On the Atari, we sometimes can&squot;t enable interrupts:&n; */
multiline_comment|/* MSch: changed sti() to STI() wherever possible in ide.c; moved STI() def. &n; * to asm/ide.h &n; */
multiline_comment|/* The Atari interrupt structure strictly requires that the IPL isn&squot;t lowered&n; * uncontrolled in an interrupt handler. In the concrete case, the IDE&n; * interrupt is already a slow int, so the irq is already disabled at the time&n; * the handler is called, and the IPL has been lowered to the minimum value&n; * possible. To avoid going below that, STI() checks for being called inside&n; * an interrupt, and in that case it does nothing. Hope that is reasonable and&n; * works. (Roman)&n; */
macro_line|#ifdef MACH_ATARI_ONLY
DECL|macro|ide__sti
mdefine_line|#define&t;ide__sti()&t;&t;&t;&t;&t;&bslash;&n;    do {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (!in_interrupt()) __sti();&t;&t;&t;&bslash;&n;    } while(0)
macro_line|#elif defined(CONFIG_ATARI)
DECL|macro|ide__sti
mdefine_line|#define&t;ide__sti()&t;&t;&t;&t;&t;&t;&bslash;&n;    do {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (!MACH_IS_ATARI || !in_interrupt()) sti();&t;&t;&bslash;&n;    } while(0)
macro_line|#else /* !defined(CONFIG_ATARI) */
DECL|macro|ide__sti
mdefine_line|#define&t;ide__sti()&t;__sti()
macro_line|#endif
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _M68K_IDE_H */
eof
