multiline_comment|/*&n; * include/asm-v850/rte_ma1_cb.h -- Midas labs RTE-V850/MA1-CB board&n; *&n; *  Copyright (C) 2001,02,03  NEC Electronics Corporation&n; *  Copyright (C) 2001,02,03  Miles Bader &lt;miles@gnu.org&gt;&n; *&n; * This file is subject to the terms and conditions of the GNU General&n; * Public License.  See the file COPYING in the main directory of this&n; * archive for more details.&n; *&n; * Written by Miles Bader &lt;miles@gnu.org&gt;&n; */
macro_line|#ifndef __V850_RTE_MA1_CB_H__
DECL|macro|__V850_RTE_MA1_CB_H__
mdefine_line|#define __V850_RTE_MA1_CB_H__
macro_line|#include &lt;asm/rte_cb.h&gt;&t;&t;/* Common defs for Midas RTE-CB boards.  */
DECL|macro|PLATFORM
mdefine_line|#define PLATFORM&t;&t;&quot;rte-v850e/ma1-cb&quot;
DECL|macro|PLATFORM_LONG
mdefine_line|#define PLATFORM_LONG&t;&t;&quot;Midas lab RTE-V850E/MA1-CB&quot;
DECL|macro|CPU_CLOCK_FREQ
mdefine_line|#define CPU_CLOCK_FREQ&t;&t;50000000 /* 50MHz */
multiline_comment|/* 1MB of onboard SRAM.  Note that the monitor ROM uses parts of this&n;   for its own purposes, so care must be taken.  Some address lines are&n;   not decoded, so the SRAM area is mirrored every 1MB from 0x400000 to&n;   0x800000 (exclusive).  */
DECL|macro|SRAM_ADDR
mdefine_line|#define SRAM_ADDR&t;&t;0x00400000
DECL|macro|SRAM_SIZE
mdefine_line|#define SRAM_SIZE&t;&t;0x00100000 /* 1MB */
multiline_comment|/* 32MB of onbard SDRAM.  */
DECL|macro|SDRAM_ADDR
mdefine_line|#define SDRAM_ADDR&t;&t;0x00800000
DECL|macro|SDRAM_SIZE
mdefine_line|#define SDRAM_SIZE&t;&t;0x02000000 /* 32MB */
multiline_comment|/* CPU addresses of GBUS memory spaces.  */
DECL|macro|GCS0_ADDR
mdefine_line|#define GCS0_ADDR&t;&t;0x05000000 /* GCS0 - Common SRAM (2MB) */
DECL|macro|GCS0_SIZE
mdefine_line|#define GCS0_SIZE&t;&t;0x00200000 /*   2MB */
DECL|macro|GCS1_ADDR
mdefine_line|#define GCS1_ADDR&t;&t;0x06000000 /* GCS1 - Flash ROM (8MB) */
DECL|macro|GCS1_SIZE
mdefine_line|#define GCS1_SIZE&t;&t;0x00800000 /*   8MB */
DECL|macro|GCS2_ADDR
mdefine_line|#define GCS2_ADDR&t;&t;0x07900000 /* GCS2 - I/O registers */
DECL|macro|GCS2_SIZE
mdefine_line|#define GCS2_SIZE&t;&t;0x00400000 /*   4MB */
DECL|macro|GCS5_ADDR
mdefine_line|#define GCS5_ADDR&t;&t;0x04000000 /* GCS5 - PCI bus space */
DECL|macro|GCS5_SIZE
mdefine_line|#define GCS5_SIZE&t;&t;0x01000000 /*   16MB */
DECL|macro|GCS6_ADDR
mdefine_line|#define GCS6_ADDR&t;&t;0x07980000 /* GCS6 - PCI control registers */
DECL|macro|GCS6_SIZE
mdefine_line|#define GCS6_SIZE&t;&t;0x00000200 /*   512B */
multiline_comment|/* For &lt;asm/page.h&gt; */
DECL|macro|PAGE_OFFSET
mdefine_line|#define PAGE_OFFSET &t;&t;SRAM_ADDR
multiline_comment|/* The GBUS GINT0 - GINT3 interrupts are connected to the INTP000 - INTP011&n;   pins on the CPU.  These are shared among the GBUS interrupts.  */
DECL|macro|IRQ_GINT
mdefine_line|#define IRQ_GINT(n)&t;&t;IRQ_INTP(n)
DECL|macro|IRQ_GINT_NUM
mdefine_line|#define IRQ_GINT_NUM&t;&t;4
multiline_comment|/* Used by &lt;asm/rte_cb.h&gt; to derive NUM_MACH_IRQS.  */
DECL|macro|NUM_RTE_CB_IRQS
mdefine_line|#define NUM_RTE_CB_IRQS&t;&t;NUM_CPU_IRQS
macro_line|#ifdef CONFIG_ROM_KERNEL
multiline_comment|/* Kernel is in ROM, starting at address 0.  */
DECL|macro|INTV_BASE
mdefine_line|#define INTV_BASE&t;&t;0
macro_line|#else /* !CONFIG_ROM_KERNEL */
macro_line|#ifdef CONFIG_RTE_CB_MULTI
multiline_comment|/* Using RAM kernel with ROM monitor for Multi debugger.  */
multiline_comment|/* The chip&squot;s real interrupt vectors are in ROM, but they jump to a&n;   secondary interrupt vector table in RAM.  */
DECL|macro|INTV_BASE
mdefine_line|#define INTV_BASE&t;&t;0x004F8000
multiline_comment|/* Scratch memory used by the ROM monitor, which shouldn&squot;t be used by&n;   linux (except for the alternate interrupt vector area, defined&n;   above).  */
DECL|macro|MON_SCRATCH_ADDR
mdefine_line|#define MON_SCRATCH_ADDR&t;0x004F8000
DECL|macro|MON_SCRATCH_SIZE
mdefine_line|#define MON_SCRATCH_SIZE&t;0x00008000 /* 32KB */
macro_line|#else /* !CONFIG_RTE_CB_MULTI */
multiline_comment|/* Using RAM-kernel.  Assume some sort of boot-loader got us loaded at&n;   address 0.  */
DECL|macro|INTV_BASE
mdefine_line|#define INTV_BASE&t;&t;0
macro_line|#endif /* CONFIG_RTE_CB_MULTI */
macro_line|#endif /* CONFIG_ROM_KERNEL */
multiline_comment|/* Some misc. on-board devices.  */
multiline_comment|/* Seven-segment LED display (two digits).  Write-only.  */
DECL|macro|LED_ADDR
mdefine_line|#define LED_ADDR(n)&t;&t;(0x07802000 + (n))
DECL|macro|LED
mdefine_line|#define LED(n)&t;&t;&t;(*(volatile unsigned char *)LED_ADDR(n))
DECL|macro|LED_NUM_DIGITS
mdefine_line|#define LED_NUM_DIGITS&t;&t;2
multiline_comment|/* Override the basic MA uart pre-initialization so that we can&n;   initialize extra stuff.  */
DECL|macro|V850E_UART_PRE_CONFIGURE
macro_line|#undef V850E_UART_PRE_CONFIGURE&t;/* should be defined by &lt;asm/ma.h&gt; */
DECL|macro|V850E_UART_PRE_CONFIGURE
mdefine_line|#define V850E_UART_PRE_CONFIGURE&t;rte_ma1_cb_uart_pre_configure
macro_line|#ifndef __ASSEMBLY__
r_extern
r_void
id|rte_ma1_cb_uart_pre_configure
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
multiline_comment|/* This board supports RTS/CTS for the on-chip UART, but only for channel 0. */
multiline_comment|/* CTS for UART channel 0 is pin P43 (bit 3 of port 4).  */
DECL|macro|V850E_UART_CTS
mdefine_line|#define V850E_UART_CTS(chan)&t;((chan) == 0 ? !(MA_PORT4_IO &amp; 0x8) : 1)
multiline_comment|/* RTS for UART channel 0 is pin P42 (bit 2 of port 4).  */
DECL|macro|V850E_UART_SET_RTS
mdefine_line|#define V850E_UART_SET_RTS(chan, val)&t;&t;&t;&t;&t;      &bslash;&n;   do {&t;&t;&t;&t;&t;&t;&t;&t;&t;      &bslash;&n;&t;   if (chan == 0) {&t;&t;&t;&t;&t;&t;      &bslash;&n;&t;&t;   unsigned old = MA_PORT4_IO; &t;&t;&t;&t;      &bslash;&n;&t;&t;   if (val)&t;&t;&t;&t;&t;&t;      &bslash;&n;&t;&t;&t;   MA_PORT4_IO = old &amp; ~0x4;&t;&t;&t;      &bslash;&n;&t;&t;   else&t;&t;&t;&t;&t;&t;&t;      &bslash;&n;&t;&t;&t;   MA_PORT4_IO = old | 0x4;&t;&t;&t;      &bslash;&n;&t;   }&t;&t;&t;&t;&t;&t;&t;&t;      &bslash;&n;   } while (0)
macro_line|#endif /* __V850_RTE_MA1_CB_H__ */
eof
