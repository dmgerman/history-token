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
r_typedef
r_union
(brace
r_int
id|all
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* all of the bits together */
r_struct
(brace
DECL|member|bit7
r_int
id|bit7
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* always 1 */
DECL|member|lba
r_int
id|lba
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* using LBA instead of CHS */
DECL|member|bit5
r_int
id|bit5
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* always 1 */
DECL|member|unit
r_int
id|unit
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* drive select number, 0 or 1 */
DECL|member|head
r_int
id|head
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* always zeros here */
DECL|member|b
)brace
id|b
suffix:semicolon
DECL|typedef|select_t
)brace
id|select_t
suffix:semicolon
r_typedef
r_union
(brace
r_int
id|all
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* all of the bits together */
r_struct
(brace
DECL|member|HOB
r_int
id|HOB
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 48-bit address ordering */
DECL|member|reserved456
r_int
id|reserved456
suffix:colon
l_int|3
suffix:semicolon
DECL|member|bit3
r_int
id|bit3
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* ATA-2 thingy */
DECL|member|SRST
r_int
id|SRST
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* host soft reset bit */
DECL|member|nIEN
r_int
id|nIEN
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* device INTRQ to host */
DECL|member|bit0
r_int
id|bit0
suffix:colon
l_int|1
suffix:semicolon
DECL|member|b
)brace
id|b
suffix:semicolon
DECL|typedef|control_t
)brace
id|control_t
suffix:semicolon
DECL|macro|SUPPORT_SLOW_DATA_PORTS
macro_line|#undef SUPPORT_SLOW_DATA_PORTS
DECL|macro|SUPPORT_SLOW_DATA_PORTS
mdefine_line|#define SUPPORT_SLOW_DATA_PORTS 0
DECL|macro|SUPPORT_VLB_SYNC
macro_line|#undef SUPPORT_VLB_SYNC
DECL|macro|SUPPORT_VLB_SYNC
mdefine_line|#define SUPPORT_VLB_SYNC 0
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
DECL|macro|T_CHAR
mdefine_line|#define T_CHAR          (0x0000)        /* char:  don&squot;t touch  */
DECL|macro|T_SHORT
mdefine_line|#define T_SHORT         (0x4000)        /* short: 12 -&gt; 21     */
DECL|macro|T_INT
mdefine_line|#define T_INT           (0x8000)        /* int:   1234 -&gt; 4321 */
DECL|macro|T_TEXT
mdefine_line|#define T_TEXT          (0xc000)        /* text:  12 -&gt; 21     */
DECL|macro|T_MASK_TYPE
mdefine_line|#define T_MASK_TYPE     (0xc000)
DECL|macro|T_MASK_COUNT
mdefine_line|#define T_MASK_COUNT    (0x3fff)
DECL|macro|D_CHAR
mdefine_line|#define D_CHAR(cnt)     (T_CHAR  | (cnt))
DECL|macro|D_SHORT
mdefine_line|#define D_SHORT(cnt)    (T_SHORT | (cnt))
DECL|macro|D_INT
mdefine_line|#define D_INT(cnt)      (T_INT   | (cnt))
DECL|macro|D_TEXT
mdefine_line|#define D_TEXT(cnt)     (T_TEXT  | (cnt))
multiline_comment|/* Q40 and Atari have byteswapped IDE bus and since many interesting&n; * values in the identification string are text, chars and words they&n; * happened to be almost correct without swapping.. However *_capacity &n; * is needed for drives over 8 GB. RZ */
macro_line|#if defined(CONFIG_Q40) || defined(CONFIG_ATARI)
DECL|macro|M68K_IDE_SWAPW
mdefine_line|#define M68K_IDE_SWAPW  (MACH_IS_Q40 || MACH_IS_ATARI)
macro_line|#endif
macro_line|#if defined(CONFIG_AMIGA) || defined (CONFIG_MAC) || defined(M68K_IDE_SWAPW)
DECL|variable|driveid_types
r_static
id|u_short
id|driveid_types
(braket
)braket
op_assign
(brace
id|D_SHORT
c_func
(paren
l_int|10
)paren
comma
multiline_comment|/* config - vendor2 */
id|D_TEXT
c_func
(paren
l_int|20
)paren
comma
multiline_comment|/* serial_no */
id|D_SHORT
c_func
(paren
l_int|3
)paren
comma
multiline_comment|/* buf_type, buf_size - ecc_bytes */
id|D_TEXT
c_func
(paren
l_int|48
)paren
comma
multiline_comment|/* fw_rev - model */
id|D_CHAR
c_func
(paren
l_int|2
)paren
comma
multiline_comment|/* max_multsect - vendor3 */
id|D_SHORT
c_func
(paren
l_int|1
)paren
comma
multiline_comment|/* dword_io */
id|D_CHAR
c_func
(paren
l_int|2
)paren
comma
multiline_comment|/* vendor4 - capability */
id|D_SHORT
c_func
(paren
l_int|1
)paren
comma
multiline_comment|/* reserved50 */
id|D_CHAR
c_func
(paren
l_int|4
)paren
comma
multiline_comment|/* vendor5 - tDMA */
id|D_SHORT
c_func
(paren
l_int|4
)paren
comma
multiline_comment|/* field_valid - cur_sectors */
id|D_INT
c_func
(paren
l_int|1
)paren
comma
multiline_comment|/* cur_capacity */
id|D_CHAR
c_func
(paren
l_int|2
)paren
comma
multiline_comment|/* multsect - multsect_valid */
id|D_INT
c_func
(paren
l_int|1
)paren
comma
multiline_comment|/* lba_capacity */
id|D_SHORT
c_func
(paren
l_int|194
)paren
multiline_comment|/* dma_1word - reserved */
)brace
suffix:semicolon
DECL|macro|num_driveid_types
mdefine_line|#define num_driveid_types       (sizeof(driveid_types)/sizeof(*driveid_types))
macro_line|#endif /* CONFIG_AMIGA */
DECL|function|ide_fix_driveid
r_static
id|__inline__
r_void
id|ide_fix_driveid
c_func
(paren
r_struct
id|hd_driveid
op_star
id|id
)paren
(brace
macro_line|#if defined(CONFIG_AMIGA) || defined (CONFIG_MAC) || defined(M68K_IDE_SWAPW)
id|u_char
op_star
id|p
op_assign
(paren
id|u_char
op_star
)paren
id|id
suffix:semicolon
r_int
id|i
comma
id|j
comma
id|cnt
suffix:semicolon
id|u_char
id|t
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|MACH_IS_AMIGA
op_logical_and
op_logical_neg
id|MACH_IS_MAC
op_logical_and
op_logical_neg
id|MACH_IS_Q40
op_logical_and
op_logical_neg
id|MACH_IS_ATARI
)paren
r_return
suffix:semicolon
macro_line|#ifdef M68K_IDE_SWAPW
r_if
c_cond
(paren
id|M68K_IDE_SWAPW
)paren
multiline_comment|/* fix bus byteorder first */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|512
suffix:semicolon
id|i
op_add_assign
l_int|2
)paren
(brace
id|t
op_assign
id|p
(braket
id|i
)braket
suffix:semicolon
id|p
(braket
id|i
)braket
op_assign
id|p
(braket
id|i
op_plus
l_int|1
)braket
suffix:semicolon
id|p
(braket
id|i
op_plus
l_int|1
)braket
op_assign
id|t
suffix:semicolon
)brace
macro_line|#endif
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|num_driveid_types
suffix:semicolon
id|i
op_increment
)paren
(brace
id|cnt
op_assign
id|driveid_types
(braket
id|i
)braket
op_amp
id|T_MASK_COUNT
suffix:semicolon
r_switch
c_cond
(paren
id|driveid_types
(braket
id|i
)braket
op_amp
id|T_MASK_TYPE
)paren
(brace
r_case
id|T_CHAR
suffix:colon
id|p
op_add_assign
id|cnt
suffix:semicolon
r_break
suffix:semicolon
r_case
id|T_SHORT
suffix:colon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|cnt
suffix:semicolon
id|j
op_increment
)paren
(brace
id|t
op_assign
id|p
(braket
l_int|0
)braket
suffix:semicolon
id|p
(braket
l_int|0
)braket
op_assign
id|p
(braket
l_int|1
)braket
suffix:semicolon
id|p
(braket
l_int|1
)braket
op_assign
id|t
suffix:semicolon
id|p
op_add_assign
l_int|2
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|T_INT
suffix:colon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|cnt
suffix:semicolon
id|j
op_increment
)paren
(brace
id|t
op_assign
id|p
(braket
l_int|0
)braket
suffix:semicolon
id|p
(braket
l_int|0
)braket
op_assign
id|p
(braket
l_int|3
)braket
suffix:semicolon
id|p
(braket
l_int|3
)braket
op_assign
id|t
suffix:semicolon
id|t
op_assign
id|p
(braket
l_int|1
)braket
suffix:semicolon
id|p
(braket
l_int|1
)braket
op_assign
id|p
(braket
l_int|2
)braket
suffix:semicolon
id|p
(braket
l_int|2
)braket
op_assign
id|t
suffix:semicolon
id|p
op_add_assign
l_int|4
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|T_TEXT
suffix:colon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|cnt
suffix:semicolon
id|j
op_add_assign
l_int|2
)paren
(brace
id|t
op_assign
id|p
(braket
l_int|0
)braket
suffix:semicolon
id|p
(braket
l_int|0
)braket
op_assign
id|p
(braket
l_int|1
)braket
suffix:semicolon
id|p
(braket
l_int|1
)braket
op_assign
id|t
suffix:semicolon
id|p
op_add_assign
l_int|2
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
)brace
macro_line|#endif /* CONFIG_AMIGA */
)brace
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
macro_line|#ifdef CONFIG_ATARI
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
macro_line|#endif /* CONFIG_ATARI */
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
macro_line|#ifdef CONFIG_ATARI
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
macro_line|#endif /* CONFIG_ATARI */
)brace
DECL|macro|ide_ack_intr
mdefine_line|#define ide_ack_intr(hwif)&t;((hwif)-&gt;hw.ack_intr ? (hwif)-&gt;hw.ack_intr(hwif) : 1)
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
