multiline_comment|/*&n; * include/asm-v850/anna.h -- Anna V850E2 evaluation cpu chip/board&n; *&n; *  Copyright (C) 2001,2002  NEC Corporation&n; *  Copyright (C) 2001,2002  Miles Bader &lt;miles@gnu.org&gt;&n; *&n; * This file is subject to the terms and conditions of the GNU General&n; * Public License.  See the file COPYING in the main directory of this&n; * archive for more details.&n; *&n; * Written by Miles Bader &lt;miles@gnu.org&gt;&n; */
macro_line|#ifndef __V850_ANNA_H__
DECL|macro|__V850_ANNA_H__
mdefine_line|#define __V850_ANNA_H__
DECL|macro|CPU_ARCH
mdefine_line|#define CPU_ARCH &t;&quot;v850e2&quot;
DECL|macro|CPU_MODEL
mdefine_line|#define CPU_MODEL&t;&quot;v850e2/anna&quot;
DECL|macro|CPU_MODEL_LONG
mdefine_line|#define CPU_MODEL_LONG&t;&quot;NEC V850E2/Anna&quot;
DECL|macro|PLATFORM
mdefine_line|#define PLATFORM&t;&quot;anna&quot;
DECL|macro|PLATFORM_LONG
mdefine_line|#define PLATFORM_LONG&t;&quot;NEC/Midas lab V850E2/Anna evaluation board&quot;
DECL|macro|CPU_CLOCK_FREQ
mdefine_line|#define CPU_CLOCK_FREQ&t;200000000 /*  200MHz */
DECL|macro|SYS_CLOCK_FREQ
mdefine_line|#define SYS_CLOCK_FREQ&t; 33300000 /* 33.3MHz */
multiline_comment|/* 1MB of static RAM.  This memory is mirrored 64 times.  */
DECL|macro|SRAM_ADDR
mdefine_line|#define SRAM_ADDR&t;0x04000000
DECL|macro|SRAM_SIZE
mdefine_line|#define SRAM_SIZE&t;0x00100000 /* 1MB */
multiline_comment|/* 64MB of DRAM.  */
DECL|macro|SDRAM_ADDR
mdefine_line|#define SDRAM_ADDR&t;0x08000000&t;
DECL|macro|SDRAM_SIZE
mdefine_line|#define SDRAM_SIZE&t;0x04000000 /* 64MB */
multiline_comment|/* For &lt;asm/page.h&gt; */
DECL|macro|PAGE_OFFSET
mdefine_line|#define PAGE_OFFSET &t;SRAM_ADDR
multiline_comment|/* We use on-chip RAM, for a few miscellaneous variables that must be&n;   accessible using a load instruction relative to R0.  The Anna chip has&n;   128K of `dLB&squot; ram nominally located at 0xFFF00000, but it&squot;s mirrored&n;   every 128K, so we can use the `last mirror&squot; (except for the portion at&n;   the top which is overridden by I/O space).  In addition, the early&n;   sample chip we&squot;re using has lots of memory errors in the dLB ram, so we&n;   use a specially chosen location that has at least 20 bytes of contiguous&n;   valid memory (xxxF0020 - xxxF003F).  */
DECL|macro|R0_RAM_ADDR
mdefine_line|#define R0_RAM_ADDR&t;&t;&t;0xFFFF8020
multiline_comment|/* Anna specific control registers.  */
DECL|macro|ANNA_CSC_ADDR
mdefine_line|#define ANNA_CSC_ADDR(n)&t;&t;(0xFFFFF060 + (n) * 2)
DECL|macro|ANNA_CSC
mdefine_line|#define ANNA_CSC(n)&t;&t;&t;(*(volatile u16 *)ANNA_CSC_ADDR(n))
DECL|macro|ANNA_BPC_ADDR
mdefine_line|#define ANNA_BPC_ADDR&t;&t;&t;0xFFFFF064
DECL|macro|ANNA_BPC
mdefine_line|#define ANNA_BPC&t;&t;&t;(*(volatile u16 *)ANNA_BPC_ADDR)
DECL|macro|ANNA_BSC_ADDR
mdefine_line|#define ANNA_BSC_ADDR&t;&t;&t;0xFFFFF066
DECL|macro|ANNA_BSC
mdefine_line|#define ANNA_BSC&t;&t;&t;(*(volatile u16 *)ANNA_BSC_ADDR)
DECL|macro|ANNA_BEC_ADDR
mdefine_line|#define ANNA_BEC_ADDR&t;&t;&t;0xFFFFF068
DECL|macro|ANNA_BEC
mdefine_line|#define ANNA_BEC&t;&t;&t;(*(volatile u16 *)ANNA_BEC_ADDR)
DECL|macro|ANNA_BHC_ADDR
mdefine_line|#define ANNA_BHC_ADDR&t;&t;&t;0xFFFFF06A
DECL|macro|ANNA_BHC
mdefine_line|#define ANNA_BHC&t;&t;&t;(*(volatile u16 *)ANNA_BHC_ADDR)
DECL|macro|ANNA_BCT_ADDR
mdefine_line|#define ANNA_BCT_ADDR(n)&t;&t;(0xFFFFF480 + (n) * 2)
DECL|macro|ANNA_BCT
mdefine_line|#define ANNA_BCT(n)&t;&t;&t;(*(volatile u16 *)ANNA_BCT_ADDR(n))
DECL|macro|ANNA_DWC_ADDR
mdefine_line|#define ANNA_DWC_ADDR(n)&t;&t;(0xFFFFF484 + (n) * 2)
DECL|macro|ANNA_DWC
mdefine_line|#define ANNA_DWC(n)&t;&t;&t;(*(volatile u16 *)ANNA_DWC_ADDR(n))
DECL|macro|ANNA_BCC_ADDR
mdefine_line|#define ANNA_BCC_ADDR&t;&t;&t;0xFFFFF488
DECL|macro|ANNA_BCC
mdefine_line|#define ANNA_BCC&t;&t;&t;(*(volatile u16 *)ANNA_BCC_ADDR)
DECL|macro|ANNA_ASC_ADDR
mdefine_line|#define ANNA_ASC_ADDR&t;&t;&t;0xFFFFF48A
DECL|macro|ANNA_ASC
mdefine_line|#define ANNA_ASC&t;&t;&t;(*(volatile u16 *)ANNA_ASC_ADDR)
DECL|macro|ANNA_LBS_ADDR
mdefine_line|#define ANNA_LBS_ADDR&t;&t;&t;0xFFFFF48E
DECL|macro|ANNA_LBS
mdefine_line|#define ANNA_LBS&t;&t;&t;(*(volatile u16 *)ANNA_LBS_ADDR)
DECL|macro|ANNA_SCR3_ADDR
mdefine_line|#define ANNA_SCR3_ADDR&t;&t;&t;0xFFFFF4AC
DECL|macro|ANNA_SCR3
mdefine_line|#define ANNA_SCR3&t;&t;&t;(*(volatile u16 *)ANNA_SCR3_ADDR)
DECL|macro|ANNA_RFS3_ADDR
mdefine_line|#define ANNA_RFS3_ADDR&t;&t;&t;0xFFFFF4AE
DECL|macro|ANNA_RFS3
mdefine_line|#define ANNA_RFS3&t;&t;&t;(*(volatile u16 *)ANNA_RFS3_ADDR)
DECL|macro|ANNA_ILBEN_ADDR
mdefine_line|#define ANNA_ILBEN_ADDR&t;&t;&t;0xFFFFF7F2
DECL|macro|ANNA_ILBEN
mdefine_line|#define ANNA_ILBEN&t;&t;&t;(*(volatile u16 *)ANNA_ILBEN_ADDR)
multiline_comment|/* I/O port P0-P3. */
multiline_comment|/* Direct I/O.  Bits 0-7 are pins Pn0-Pn7.  */
DECL|macro|ANNA_PORT_IO_ADDR
mdefine_line|#define ANNA_PORT_IO_ADDR(n)&t;&t;(0xFFFFF400 + (n) * 2)
DECL|macro|ANNA_PORT_IO
mdefine_line|#define ANNA_PORT_IO(n)&t;&t;&t;(*(volatile u8 *)ANNA_PORT_IO_ADDR(n))
multiline_comment|/* Port mode (for direct I/O, 0 = output, 1 = input).  */
DECL|macro|ANNA_PORT_PM_ADDR
mdefine_line|#define ANNA_PORT_PM_ADDR(n)&t;&t;(0xFFFFF410 + (n) * 2)
DECL|macro|ANNA_PORT_PM
mdefine_line|#define ANNA_PORT_PM(n)&t;&t;&t;(*(volatile u8 *)ANNA_PORT_PM_ADDR(n))
multiline_comment|/* NB85E-style interrupt system.  */
macro_line|#include &lt;asm/nb85e_intc.h&gt;
multiline_comment|/* Hardware-specific interrupt numbers (in the kernel IRQ namespace).  */
DECL|macro|IRQ_INTP
mdefine_line|#define IRQ_INTP(n)&t;(n)&t;/* Pnnn (pin) interrupts 0-15 */
DECL|macro|IRQ_INTP_NUM
mdefine_line|#define IRQ_INTP_NUM&t;16
DECL|macro|IRQ_INTOV
mdefine_line|#define IRQ_INTOV(n)&t;(0x10 + (n)) /* 0-2 */
DECL|macro|IRQ_INTOV_NUM
mdefine_line|#define IRQ_INTOV_NUM&t;2
DECL|macro|IRQ_INTCCC
mdefine_line|#define IRQ_INTCCC(n)&t;(0x12 + (n))
DECL|macro|IRQ_INTCCC_NUM
mdefine_line|#define IRQ_INTCCC_NUM&t;4
DECL|macro|IRQ_INTCMD
mdefine_line|#define IRQ_INTCMD(n)&t;(0x16 + (n)) /* interval timer interrupts 0-5 */
DECL|macro|IRQ_INTCMD_NUM
mdefine_line|#define IRQ_INTCMD_NUM&t;6
DECL|macro|IRQ_INTDMA
mdefine_line|#define IRQ_INTDMA(n)&t;(0x1C + (n)) /* DMA interrupts 0-3 */
DECL|macro|IRQ_INTDMA_NUM
mdefine_line|#define IRQ_INTDMA_NUM&t;4
DECL|macro|IRQ_INTDMXER
mdefine_line|#define IRQ_INTDMXER&t;0x20
DECL|macro|IRQ_INTSRE
mdefine_line|#define IRQ_INTSRE(n)&t;(0x21 + (n)*3) /* UART 0-1 reception error */
DECL|macro|IRQ_INTSRE_NUM
mdefine_line|#define IRQ_INTSRE_NUM&t;2
DECL|macro|IRQ_INTSR
mdefine_line|#define IRQ_INTSR(n)&t;(0x22 + (n)*3) /* UART 0-1 reception completion */
DECL|macro|IRQ_INTSR_NUM
mdefine_line|#define IRQ_INTSR_NUM&t;2
DECL|macro|IRQ_INTST
mdefine_line|#define IRQ_INTST(n)&t;(0x23 + (n)*3) /* UART 0-1 transmission completion */
DECL|macro|IRQ_INTST_NUM
mdefine_line|#define IRQ_INTST_NUM&t;2
DECL|macro|NUM_CPU_IRQS
mdefine_line|#define NUM_CPU_IRQS&t;64
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/* Initialize chip interrupts.  */
r_extern
r_void
id|anna_init_irqs
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* Anna UART details (basically the same as the V850E/MA1, but 2 channels).  */
DECL|macro|V850E_UART_NUM_CHANNELS
mdefine_line|#define V850E_UART_NUM_CHANNELS&t;&t;2
DECL|macro|V850E_UART_BASE_FREQ
mdefine_line|#define V850E_UART_BASE_FREQ&t;&t;(SYS_CLOCK_FREQ / 2)
DECL|macro|V850E_UART_CHIP_NAME
mdefine_line|#define V850E_UART_CHIP_NAME &t;&t;&quot;V850E2/NA85E2A&quot;
multiline_comment|/* This is the UART channel that&squot;s actually connected on the board.  */
DECL|macro|V850E_UART_CONSOLE_CHANNEL
mdefine_line|#define V850E_UART_CONSOLE_CHANNEL&t;1
multiline_comment|/* This is a function that gets called before configuring the UART.  */
DECL|macro|V850E_UART_PRE_CONFIGURE
mdefine_line|#define V850E_UART_PRE_CONFIGURE&t;anna_uart_pre_configure
macro_line|#ifndef __ASSEMBLY__
r_extern
r_void
id|anna_uart_pre_configure
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
multiline_comment|/* CTS for UART channel 1 is pin P37 (bit 7 of port 3).  */
DECL|macro|V850E_UART_CTS
mdefine_line|#define V850E_UART_CTS(chan)&t;((chan) == 1 ? !(ANNA_PORT_IO(3) &amp; 0x80) : 1)
multiline_comment|/* RTS for UART channel 1 is pin P07 (bit 7 of port 0).  */
DECL|macro|V850E_UART_SET_RTS
mdefine_line|#define V850E_UART_SET_RTS(chan, val)&t;&t;&t;&t;&t;      &bslash;&n;   do {&t;&t;&t;&t;&t;&t;&t;&t;&t;      &bslash;&n;&t;   if (chan == 1) {&t;&t;&t;&t;&t;&t;      &bslash;&n;&t;&t;   unsigned old = ANNA_PORT_IO(0); &t;&t;&t;      &bslash;&n;&t;&t;   if (val)&t;&t;&t;&t;&t;&t;      &bslash;&n;&t;&t;&t;   ANNA_PORT_IO(0) = old &amp; ~0x80;&t;&t;      &bslash;&n;&t;&t;   else&t;&t;&t;&t;&t;&t;&t;      &bslash;&n;&t;&t;&t;   ANNA_PORT_IO(0) = old | 0x80;&t;&t;      &bslash;&n;&t;   }&t;&t;&t;&t;&t;&t;&t;&t;      &bslash;&n;   } while (0)
multiline_comment|/* Timer C details.  */
DECL|macro|V850E_TIMER_C_BASE_ADDR
mdefine_line|#define V850E_TIMER_C_BASE_ADDR&t;&t;0xFFFFF600
multiline_comment|/* Timer D details (the Anna actually has 5 of these; should change later). */
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
mdefine_line|#define V850E_TIMER_D_TMCD_CS_MIN&t;1 /* min 2^1 divider */
multiline_comment|/* For &lt;asm/param.h&gt; */
macro_line|#ifndef HZ
DECL|macro|HZ
mdefine_line|#define HZ&t;100
macro_line|#endif
macro_line|#endif /* __V850_ANNA_H__ */
eof
