multiline_comment|/*&n; * include/asm-v850/as85ep1.h -- AS85EP1 evaluation CPU chip/board&n; *&n; *  Copyright (C) 2001,02,03  NEC Electronics Corporation&n; *  Copyright (C) 2001,02,03  Miles Bader &lt;miles@gnu.org&gt;&n; *&n; * This file is subject to the terms and conditions of the GNU General&n; * Public License.  See the file COPYING in the main directory of this&n; * archive for more details.&n; *&n; * Written by Miles Bader &lt;miles@gnu.org&gt;&n; */
macro_line|#ifndef __V850_AS85EP1_H__
DECL|macro|__V850_AS85EP1_H__
mdefine_line|#define __V850_AS85EP1_H__
macro_line|#include &lt;asm/v850e.h&gt;
DECL|macro|CPU_MODEL
mdefine_line|#define CPU_MODEL&t;&quot;as85ep1&quot;
DECL|macro|CPU_MODEL_LONG
mdefine_line|#define CPU_MODEL_LONG&t;&quot;NEC V850E/AS85EP1&quot;
DECL|macro|PLATFORM
mdefine_line|#define PLATFORM&t;&quot;AS85EP1&quot;
DECL|macro|PLATFORM_LONG
mdefine_line|#define PLATFORM_LONG&t;&quot;NEC V850E/AS85EP1 evaluation board&quot;
DECL|macro|CPU_CLOCK_FREQ
mdefine_line|#define CPU_CLOCK_FREQ&t;96000000 /*  96MHz */
DECL|macro|SYS_CLOCK_FREQ
mdefine_line|#define SYS_CLOCK_FREQ&t;CPU_CLOCK_FREQ
multiline_comment|/* 1MB of static RAM.  */
DECL|macro|SRAM_ADDR
mdefine_line|#define SRAM_ADDR&t;0x00400000
DECL|macro|SRAM_SIZE
mdefine_line|#define SRAM_SIZE&t;0x00100000 /* 1MB */
multiline_comment|/* About 58MB of DRAM.  This can actually be at one of two positions,&n;   determined by jump JP3; we have to use the first position because the&n;   second is partially out of processor instruction addressing range&n;   (though in the second position there&squot;s actually 64MB available).  */
DECL|macro|SDRAM_ADDR
mdefine_line|#define SDRAM_ADDR&t;0x00600000
DECL|macro|SDRAM_SIZE
mdefine_line|#define SDRAM_SIZE&t;0x039F8000 /* approx 58MB */
multiline_comment|/* For &lt;asm/page.h&gt; */
DECL|macro|PAGE_OFFSET
mdefine_line|#define PAGE_OFFSET &t;SRAM_ADDR
multiline_comment|/* We use on-chip RAM, for a few miscellaneous variables that must be&n;   accessible using a load instruction relative to R0.  The AS85EP1 chip&n;   16K of internal RAM located slightly before I/O space.  */
DECL|macro|R0_RAM_ADDR
mdefine_line|#define R0_RAM_ADDR&t;0xFFFF8000
multiline_comment|/* AS85EP1 specific control registers.  */
DECL|macro|AS85EP1_CSC_ADDR
mdefine_line|#define AS85EP1_CSC_ADDR(n)&t;(0xFFFFF060 + (n) * 2)
DECL|macro|AS85EP1_CSC
mdefine_line|#define AS85EP1_CSC(n)&t;&t;(*(volatile u16 *)AS85EP1_CSC_ADDR(n))
DECL|macro|AS85EP1_BSC_ADDR
mdefine_line|#define AS85EP1_BSC_ADDR&t;0xFFFFF066
DECL|macro|AS85EP1_BSC
mdefine_line|#define AS85EP1_BSC&t;&t;(*(volatile u16 *)AS85EP1_BSC_ADDR)
DECL|macro|AS85EP1_BCT_ADDR
mdefine_line|#define AS85EP1_BCT_ADDR(n)&t;(0xFFFFF480 + (n) * 2)
DECL|macro|AS85EP1_BCT
mdefine_line|#define AS85EP1_BCT(n)&t;&t;(*(volatile u16 *)AS85EP1_BCT_ADDR(n))
DECL|macro|AS85EP1_DWC_ADDR
mdefine_line|#define AS85EP1_DWC_ADDR(n)&t;(0xFFFFF484 + (n) * 2)
DECL|macro|AS85EP1_DWC
mdefine_line|#define AS85EP1_DWC(n)&t;&t;(*(volatile u16 *)AS85EP1_DWC_ADDR(n))
DECL|macro|AS85EP1_BCC_ADDR
mdefine_line|#define AS85EP1_BCC_ADDR&t;0xFFFFF488
DECL|macro|AS85EP1_BCC
mdefine_line|#define AS85EP1_BCC&t;&t;(*(volatile u16 *)AS85EP1_BCC_ADDR)
DECL|macro|AS85EP1_ASC_ADDR
mdefine_line|#define AS85EP1_ASC_ADDR&t;0xFFFFF48A
DECL|macro|AS85EP1_ASC
mdefine_line|#define AS85EP1_ASC&t;&t;(*(volatile u16 *)AS85EP1_ASC_ADDR)
DECL|macro|AS85EP1_BCP_ADDR
mdefine_line|#define AS85EP1_BCP_ADDR&t;0xFFFFF48C
DECL|macro|AS85EP1_BCP
mdefine_line|#define AS85EP1_BCP&t;&t;(*(volatile u16 *)AS85EP1_BCP_ADDR)
DECL|macro|AS85EP1_LBS_ADDR
mdefine_line|#define AS85EP1_LBS_ADDR&t;0xFFFFF48E
DECL|macro|AS85EP1_LBS
mdefine_line|#define AS85EP1_LBS&t;&t;(*(volatile u16 *)AS85EP1_LBS_ADDR)
DECL|macro|AS85EP1_BMC_ADDR
mdefine_line|#define AS85EP1_BMC_ADDR&t;0xFFFFF498
DECL|macro|AS85EP1_BMC
mdefine_line|#define AS85EP1_BMC&t;&t;(*(volatile u16 *)AS85EP1_BMC_ADDR)
DECL|macro|AS85EP1_PRC_ADDR
mdefine_line|#define AS85EP1_PRC_ADDR&t;0xFFFFF49A
DECL|macro|AS85EP1_PRC
mdefine_line|#define AS85EP1_PRC&t;&t;(*(volatile u16 *)AS85EP1_PRC_ADDR)
DECL|macro|AS85EP1_SCR_ADDR
mdefine_line|#define AS85EP1_SCR_ADDR(n)&t;(0xFFFFF4A0 + (n) * 4)
DECL|macro|AS85EP1_SCR
mdefine_line|#define AS85EP1_SCR(n)&t;&t;(*(volatile u16 *)AS85EP1_SCR_ADDR(n))
DECL|macro|AS85EP1_RFS_ADDR
mdefine_line|#define AS85EP1_RFS_ADDR(n)&t;(0xFFFFF4A2 + (n) * 4)
DECL|macro|AS85EP1_RFS
mdefine_line|#define AS85EP1_RFS(n)&t;&t;(*(volatile u16 *)AS85EP1_RFS_ADDR(n))
DECL|macro|AS85EP1_IRAMM_ADDR
mdefine_line|#define AS85EP1_IRAMM_ADDR&t;0xFFFFF80A
DECL|macro|AS85EP1_IRAMM
mdefine_line|#define AS85EP1_IRAMM&t;&t;(*(volatile u8 *)AS85EP1_IRAMM_ADDR)
multiline_comment|/* I/O port P0-P13. */
multiline_comment|/* Direct I/O.  Bits 0-7 are pins Pn0-Pn7.  */
DECL|macro|AS85EP1_PORT_IO_ADDR
mdefine_line|#define AS85EP1_PORT_IO_ADDR(n)&t;(0xFFFFF400 + (n) * 2)
DECL|macro|AS85EP1_PORT_IO
mdefine_line|#define AS85EP1_PORT_IO(n)&t;(*(volatile u8 *)AS85EP1_PORT_IO_ADDR(n))
multiline_comment|/* Port mode (for direct I/O, 0 = output, 1 = input).  */
DECL|macro|AS85EP1_PORT_PM_ADDR
mdefine_line|#define AS85EP1_PORT_PM_ADDR(n)&t;(0xFFFFF420 + (n) * 2)
DECL|macro|AS85EP1_PORT_PM
mdefine_line|#define AS85EP1_PORT_PM(n)&t;(*(volatile u8 *)AS85EP1_PORT_PM_ADDR(n))
multiline_comment|/* Port mode control (0 = direct I/O mode, 1 = alternative I/O mode).  */
DECL|macro|AS85EP1_PORT_PMC_ADDR
mdefine_line|#define AS85EP1_PORT_PMC_ADDR(n) (0xFFFFF440 + (n) * 2)
DECL|macro|AS85EP1_PORT_PMC
mdefine_line|#define AS85EP1_PORT_PMC(n)&t;(*(volatile u8 *)AS85EP1_PORT_PMC_ADDR(n))
multiline_comment|/* Hardware-specific interrupt numbers (in the kernel IRQ namespace).  */
DECL|macro|IRQ_INTCCC
mdefine_line|#define IRQ_INTCCC(n)&t;(0x0C + (n))
DECL|macro|IRQ_INTCCC_NUM
mdefine_line|#define IRQ_INTCCC_NUM&t;8
DECL|macro|IRQ_INTCMD
mdefine_line|#define IRQ_INTCMD(n)&t;(0x14 + (n)) /* interval timer interrupts 0-5 */
DECL|macro|IRQ_INTCMD_NUM
mdefine_line|#define IRQ_INTCMD_NUM&t;6
DECL|macro|IRQ_INTSRE
mdefine_line|#define IRQ_INTSRE(n)&t;(0x1E + (n)*3) /* UART 0-1 reception error */
DECL|macro|IRQ_INTSRE_NUM
mdefine_line|#define IRQ_INTSRE_NUM&t;2
DECL|macro|IRQ_INTSR
mdefine_line|#define IRQ_INTSR(n)&t;(0x1F + (n)*3) /* UART 0-1 reception completion */
DECL|macro|IRQ_INTSR_NUM
mdefine_line|#define IRQ_INTSR_NUM&t;2
DECL|macro|IRQ_INTST
mdefine_line|#define IRQ_INTST(n)&t;(0x20 + (n)*3) /* UART 0-1 transmission completion */
DECL|macro|IRQ_INTST_NUM
mdefine_line|#define IRQ_INTST_NUM&t;2
DECL|macro|NUM_CPU_IRQS
mdefine_line|#define NUM_CPU_IRQS&t;64
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/* Initialize chip interrupts.  */
r_extern
r_void
id|as85ep1_init_irqs
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* AS85EP1 UART details (basically the same as the V850E/MA1, but 2 channels).  */
DECL|macro|V850E_UART_NUM_CHANNELS
mdefine_line|#define V850E_UART_NUM_CHANNELS&t;&t;2
DECL|macro|V850E_UART_BASE_FREQ
mdefine_line|#define V850E_UART_BASE_FREQ&t;&t;(SYS_CLOCK_FREQ / 4)
DECL|macro|V850E_UART_CHIP_NAME
mdefine_line|#define V850E_UART_CHIP_NAME &t;&t;&quot;V850E/NA85E&quot;
multiline_comment|/* This is a function that gets called before configuring the UART.  */
DECL|macro|V850E_UART_PRE_CONFIGURE
mdefine_line|#define V850E_UART_PRE_CONFIGURE&t;as85ep1_uart_pre_configure
macro_line|#ifndef __ASSEMBLY__
r_extern
r_void
id|as85ep1_uart_pre_configure
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
multiline_comment|/* This board supports RTS/CTS for the on-chip UART, but only for channel 1. */
multiline_comment|/* CTS for UART channel 1 is pin P54 (bit 4 of port 5).  */
DECL|macro|V850E_UART_CTS
mdefine_line|#define V850E_UART_CTS(chan)   ((chan) == 1 ? !(AS85EP1_PORT_IO(5) &amp; 0x10) : 1)
multiline_comment|/* RTS for UART channel 1 is pin P53 (bit 3 of port 5).  */
DECL|macro|V850E_UART_SET_RTS
mdefine_line|#define V850E_UART_SET_RTS(chan, val)&t;&t;&t;&t;&t;      &bslash;&n;   do {&t;&t;&t;&t;&t;&t;&t;&t;&t;      &bslash;&n;&t;   if (chan == 1) {&t;&t;&t;&t;&t;&t;      &bslash;&n;&t;&t;   unsigned old = AS85EP1_PORT_IO(5); &t;&t;&t;      &bslash;&n;&t;&t;   if (val)&t;&t;&t;&t;&t;&t;      &bslash;&n;&t;&t;&t;   AS85EP1_PORT_IO(5) = old &amp; ~0x8;&t;&t;      &bslash;&n;&t;&t;   else&t;&t;&t;&t;&t;&t;&t;      &bslash;&n;&t;&t;&t;   AS85EP1_PORT_IO(5) = old | 0x8;&t;&t;      &bslash;&n;&t;   }&t;&t;&t;&t;&t;&t;&t;&t;      &bslash;&n;   } while (0)
multiline_comment|/* Timer C details.  */
DECL|macro|V850E_TIMER_C_BASE_ADDR
mdefine_line|#define V850E_TIMER_C_BASE_ADDR&t;&t;0xFFFFF600
multiline_comment|/* Timer D details (the AS85EP1 actually has 5 of these; should change later). */
DECL|macro|V850E_TIMER_D_BASE_ADDR
mdefine_line|#define V850E_TIMER_D_BASE_ADDR&t;&t;0xFFFFF540
DECL|macro|V850E_TIMER_D_TMD_BASE_ADDR
mdefine_line|#define V850E_TIMER_D_TMD_BASE_ADDR &t;(V850E_TIMER_D_BASE_ADDR + 0x0)
DECL|macro|V850E_TIMER_D_CMD_BASE_ADDR
mdefine_line|#define V850E_TIMER_D_CMD_BASE_ADDR &t;(V850E_TIMER_D_BASE_ADDR + 0x2)
DECL|macro|V850E_TIMER_D_TMCD_BASE_ADDR
mdefine_line|#define V850E_TIMER_D_TMCD_BASE_ADDR &t;(V850E_TIMER_D_BASE_ADDR + 0x4)
DECL|macro|V850E_TIMER_D_BASE_FREQ
mdefine_line|#define V850E_TIMER_D_BASE_FREQ&t;&t;SYS_CLOCK_FREQ
DECL|macro|V850E_TIMER_D_TMCD_CS_MIN
mdefine_line|#define V850E_TIMER_D_TMCD_CS_MIN&t;2 /* min 2^2 divider */
multiline_comment|/* For &lt;asm/param.h&gt; */
macro_line|#ifndef HZ
DECL|macro|HZ
mdefine_line|#define HZ&t;100
macro_line|#endif
macro_line|#endif /* __V850_AS85EP1_H__ */
eof
