multiline_comment|/*&n; * include/asm-v850/rte_nb85e_cb.h -- Midas labs RTE-V850/NB85E-CB board&n; *&n; *  Copyright (C) 2001,02,03  NEC Electronics Corporation&n; *  Copyright (C) 2001,02,03  Miles Bader &lt;miles@gnu.org&gt;&n; *&n; * This file is subject to the terms and conditions of the GNU General&n; * Public License.  See the file COPYING in the main directory of this&n; * archive for more details.&n; *&n; * Written by Miles Bader &lt;miles@gnu.org&gt;&n; */
macro_line|#ifndef __V850_RTE_NB85E_CB_H__
DECL|macro|__V850_RTE_NB85E_CB_H__
mdefine_line|#define __V850_RTE_NB85E_CB_H__
macro_line|#include &lt;asm/rte_cb.h&gt;&t;&t;/* Common defs for Midas RTE-CB boards.  */
DECL|macro|PLATFORM
mdefine_line|#define PLATFORM&t;&t;&quot;rte-v850e/nb85e-cb&quot;
DECL|macro|PLATFORM_LONG
mdefine_line|#define PLATFORM_LONG&t;&t;&quot;Midas lab RTE-V850E/NB85E-CB&quot;
DECL|macro|CPU_CLOCK_FREQ
mdefine_line|#define CPU_CLOCK_FREQ&t;&t;50000000 /* 50MHz */
multiline_comment|/* 1MB of onboard SRAM.  Note that the monitor ROM uses parts of this&n;   for its own purposes, so care must be taken.  */
DECL|macro|SRAM_ADDR
mdefine_line|#define SRAM_ADDR&t;&t;0x03C00000
DECL|macro|SRAM_SIZE
mdefine_line|#define SRAM_SIZE&t;&t;0x00100000 /* 1MB */
multiline_comment|/* 16MB of onbard SDRAM.  */
DECL|macro|SDRAM_ADDR
mdefine_line|#define SDRAM_ADDR&t;&t;0x01000000
DECL|macro|SDRAM_SIZE
mdefine_line|#define SDRAM_SIZE&t;&t;0x01000000 /* 16MB */
multiline_comment|/* CPU addresses of GBUS memory spaces.  */
DECL|macro|GCS0_ADDR
mdefine_line|#define GCS0_ADDR&t;&t;0x00400000 /* GCS0 - Common SRAM (2MB) */
DECL|macro|GCS0_SIZE
mdefine_line|#define GCS0_SIZE&t;&t;0x00400000 /*   4MB */
DECL|macro|GCS1_ADDR
mdefine_line|#define GCS1_ADDR&t;&t;0x02000000 /* GCS1 - Flash ROM (8MB) */
DECL|macro|GCS1_SIZE
mdefine_line|#define GCS1_SIZE&t;&t;0x00800000 /*   8MB */
DECL|macro|GCS2_ADDR
mdefine_line|#define GCS2_ADDR&t;&t;0x03900000 /* GCS2 - I/O registers */
DECL|macro|GCS2_SIZE
mdefine_line|#define GCS2_SIZE&t;&t;0x00080000 /*   512KB */
DECL|macro|GCS3_ADDR
mdefine_line|#define GCS3_ADDR&t;&t;0x02800000 /* GCS3 - EXT-bus: memory space */
DECL|macro|GCS3_SIZE
mdefine_line|#define GCS3_SIZE&t;&t;0x00800000 /*   8MB */
DECL|macro|GCS4_ADDR
mdefine_line|#define GCS4_ADDR&t;&t;0x03A00000 /* GCS4 - EXT-bus: I/O space */
DECL|macro|GCS4_SIZE
mdefine_line|#define GCS4_SIZE&t;&t;0x00200000 /*   2MB */
DECL|macro|GCS5_ADDR
mdefine_line|#define GCS5_ADDR&t;&t;0x00800000 /* GCS5 - PCI bus space */
DECL|macro|GCS5_SIZE
mdefine_line|#define GCS5_SIZE&t;&t;0x00800000 /*   8MB */
DECL|macro|GCS6_ADDR
mdefine_line|#define GCS6_ADDR&t;&t;0x03980000 /* GCS6 - PCI control registers */
DECL|macro|GCS6_SIZE
mdefine_line|#define GCS6_SIZE&t;&t;0x00010000 /*   64KB */
multiline_comment|/* The GBUS GINT0 - GINT3 interrupts are connected to CPU interrupts 10-12.&n;   These are shared among the GBUS interrupts.  */
DECL|macro|IRQ_GINT
mdefine_line|#define IRQ_GINT(n)&t;&t;(10 + (n))
DECL|macro|IRQ_GINT_NUM
mdefine_line|#define IRQ_GINT_NUM&t;&t;3
multiline_comment|/* Used by &lt;asm/rte_cb.h&gt; to derive NUM_MACH_IRQS.  */
DECL|macro|NUM_RTE_CB_IRQS
mdefine_line|#define NUM_RTE_CB_IRQS&t;&t;NUM_CPU_IRQS
macro_line|#ifdef CONFIG_ROM_KERNEL
multiline_comment|/* Kernel is in ROM, starting at address 0.  */
DECL|macro|INTV_BASE
mdefine_line|#define INTV_BASE&t;0
macro_line|#else /* !CONFIG_ROM_KERNEL */
multiline_comment|/* We&squot;re using the ROM monitor.  */
multiline_comment|/* The chip&squot;s real interrupt vectors are in ROM, but they jump to a&n;   secondary interrupt vector table in RAM.  */
DECL|macro|INTV_BASE
mdefine_line|#define INTV_BASE&t;&t;0x03CF8000
multiline_comment|/* Scratch memory used by the ROM monitor, which shouldn&squot;t be used by&n;   linux (except for the alternate interrupt vector area, defined&n;   above).  */
DECL|macro|MON_SCRATCH_ADDR
mdefine_line|#define MON_SCRATCH_ADDR&t;0x03CE8000
DECL|macro|MON_SCRATCH_SIZE
mdefine_line|#define MON_SCRATCH_SIZE&t;0x00018000 /* 96KB */
macro_line|#endif /* CONFIG_ROM_KERNEL */
multiline_comment|/* Some misc. on-board devices.  */
multiline_comment|/* Seven-segment LED display (two digits).  Write-only.  */
DECL|macro|LED_ADDR
mdefine_line|#define LED_ADDR(n)&t;(0x03802000 + (n))
DECL|macro|LED
mdefine_line|#define LED(n)&t;&t;(*(volatile unsigned char *)LED_ADDR(n))
DECL|macro|LED_NUM_DIGITS
mdefine_line|#define LED_NUM_DIGITS&t;4
multiline_comment|/* Override the basic TEG UART pre-initialization so that we can&n;   initialize extra stuff.  */
DECL|macro|V850E_UART_PRE_CONFIGURE
macro_line|#undef V850E_UART_PRE_CONFIGURE&t;/* should be defined by &lt;asm/teg.h&gt; */
DECL|macro|V850E_UART_PRE_CONFIGURE
mdefine_line|#define V850E_UART_PRE_CONFIGURE&t;rte_nb85e_cb_uart_pre_configure
macro_line|#ifndef __ASSEMBLY__
r_extern
r_void
id|rte_nb85e_cb_uart_pre_configure
(paren
r_int
id|chan
comma
r_int
id|cflags
comma
r_int
id|baud
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* This board supports RTS/CTS for the on-chip UART. */
multiline_comment|/* CTS is pin P00.  */
DECL|macro|V850E_UART_CTS
mdefine_line|#define V850E_UART_CTS(chan)&t;(! (TEG_PORT0_IO &amp; 0x1))
multiline_comment|/* RTS is pin P02.  */
DECL|macro|V850E_UART_SET_RTS
mdefine_line|#define V850E_UART_SET_RTS(chan, val)&t;&t;&t;&t;&t;      &bslash;&n;   do {&t;&t;&t;&t;&t;&t;&t;&t;&t;      &bslash;&n;&t;   unsigned old = TEG_PORT0_IO;&t;&t;&t;&t;&t;      &bslash;&n;&t;   TEG_PORT0_IO = val ? (old &amp; ~0x4) : (old | 0x4);&t;&t;      &bslash;&n;   } while (0)
macro_line|#endif /* __V850_RTE_NB85E_CB_H__ */
eof
