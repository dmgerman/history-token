multiline_comment|/*&n; * include/asm-v850/teg.h -- NB85E-TEG cpu chip&n; *&n; *  Copyright (C) 2001,02,03  NEC Electronics Corporation&n; *  Copyright (C) 2001,02,03  Miles Bader &lt;miles@gnu.org&gt;&n; *&n; * This file is subject to the terms and conditions of the GNU General&n; * Public License.  See the file COPYING in the main directory of this&n; * archive for more details.&n; *&n; * Written by Miles Bader &lt;miles@gnu.org&gt;&n; */
macro_line|#ifndef __V850_TEG_H__
DECL|macro|__V850_TEG_H__
mdefine_line|#define __V850_TEG_H__
multiline_comment|/* The TEG uses the V850E cpu core.  */
macro_line|#include &lt;asm/v850e.h&gt;
macro_line|#include &lt;asm/v850e_cache.h&gt;
DECL|macro|CPU_MODEL
mdefine_line|#define CPU_MODEL&t;&quot;v850e/nb85e-teg&quot;
DECL|macro|CPU_MODEL_LONG
mdefine_line|#define CPU_MODEL_LONG&t;&quot;NEC V850E/NB85E TEG&quot;
multiline_comment|/* For &lt;asm/entry.h&gt; */
multiline_comment|/* We use on-chip RAM, for a few miscellaneous variables that must be&n;   accessible using a load instruction relative to R0.  On the NB85E/TEG,&n;   There&squot;s 60KB of iRAM starting at 0xFFFF0000, however we need the base&n;   address to be addressable by a 16-bit signed offset, so we only use the&n;   second half of it starting from 0xFFFF8000.  */
DECL|macro|R0_RAM_ADDR
mdefine_line|#define R0_RAM_ADDR&t;&t;&t;0xFFFF8000
multiline_comment|/* Hardware-specific interrupt numbers (in the kernel IRQ namespace).&n;   Some of these are parameterized even though there&squot;s only a single&n;   interrupt, for compatibility with some generic code that works on other&n;   processor models.  */
DECL|macro|IRQ_INTCMD
mdefine_line|#define IRQ_INTCMD(n)&t;6&t;/* interval timer interrupt */
DECL|macro|IRQ_INTCMD_NUM
mdefine_line|#define IRQ_INTCMD_NUM&t;1
DECL|macro|IRQ_INTSER
mdefine_line|#define IRQ_INTSER(n)&t;16&t;/* UART reception error */
DECL|macro|IRQ_INTSER_NUM
mdefine_line|#define IRQ_INTSER_NUM&t;1
DECL|macro|IRQ_INTSR
mdefine_line|#define IRQ_INTSR(n)&t;17&t;/* UART reception completion */
DECL|macro|IRQ_INTSR_NUM
mdefine_line|#define IRQ_INTSR_NUM&t;1
DECL|macro|IRQ_INTST
mdefine_line|#define IRQ_INTST(n)&t;18&t;/* UART transmission completion */
DECL|macro|IRQ_INTST_NUM
mdefine_line|#define IRQ_INTST_NUM&t;1
multiline_comment|/* For &lt;asm/irq.h&gt; */
DECL|macro|NUM_CPU_IRQS
mdefine_line|#define NUM_CPU_IRQS&t;64
multiline_comment|/* TEG UART details.  */
DECL|macro|V850E_UART_BASE_ADDR
mdefine_line|#define V850E_UART_BASE_ADDR(n)&t;&t;(0xFFFFF600 + 0x10 * (n))
DECL|macro|V850E_UART_ASIM_ADDR
mdefine_line|#define V850E_UART_ASIM_ADDR(n)&t;&t;(V850E_UART_BASE_ADDR(n) + 0x0)
DECL|macro|V850E_UART_ASIS_ADDR
mdefine_line|#define V850E_UART_ASIS_ADDR(n)&t;&t;(V850E_UART_BASE_ADDR(n) + 0x2)
DECL|macro|V850E_UART_ASIF_ADDR
mdefine_line|#define V850E_UART_ASIF_ADDR(n)&t;&t;(V850E_UART_BASE_ADDR(n) + 0x4)
DECL|macro|V850E_UART_CKSR_ADDR
mdefine_line|#define V850E_UART_CKSR_ADDR(n)&t;&t;(V850E_UART_BASE_ADDR(n) + 0x6)
DECL|macro|V850E_UART_BRGC_ADDR
mdefine_line|#define V850E_UART_BRGC_ADDR(n)&t;&t;(V850E_UART_BASE_ADDR(n) + 0x8)
DECL|macro|V850E_UART_TXB_ADDR
mdefine_line|#define V850E_UART_TXB_ADDR(n)&t;&t;(V850E_UART_BASE_ADDR(n) + 0xA)
DECL|macro|V850E_UART_RXB_ADDR
mdefine_line|#define V850E_UART_RXB_ADDR(n)&t;&t;(V850E_UART_BASE_ADDR(n) + 0xC)
DECL|macro|V850E_UART_NUM_CHANNELS
mdefine_line|#define V850E_UART_NUM_CHANNELS&t;&t;1
DECL|macro|V850E_UART_BASE_FREQ
mdefine_line|#define V850E_UART_BASE_FREQ&t;&t;CPU_CLOCK_FREQ
multiline_comment|/* This is a function that gets called before configuring the UART.  */
DECL|macro|V850E_UART_PRE_CONFIGURE
mdefine_line|#define V850E_UART_PRE_CONFIGURE&t;teg_uart_pre_configure
macro_line|#ifndef __ASSEMBLY__
r_extern
r_void
id|teg_uart_pre_configure
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
multiline_comment|/* The TEG RTPU.  */
DECL|macro|V850E_RTPU_BASE_ADDR
mdefine_line|#define V850E_RTPU_BASE_ADDR&t;&t;0xFFFFF210
multiline_comment|/* TEG series timer D details.  */
DECL|macro|V850E_TIMER_D_BASE_ADDR
mdefine_line|#define V850E_TIMER_D_BASE_ADDR&t;&t;0xFFFFF210
DECL|macro|V850E_TIMER_D_TMCD_BASE_ADDR
mdefine_line|#define V850E_TIMER_D_TMCD_BASE_ADDR &t;(V850E_TIMER_D_BASE_ADDR + 0x0)
DECL|macro|V850E_TIMER_D_TMD_BASE_ADDR
mdefine_line|#define V850E_TIMER_D_TMD_BASE_ADDR &t;(V850E_TIMER_D_BASE_ADDR + 0x4)
DECL|macro|V850E_TIMER_D_CMD_BASE_ADDR
mdefine_line|#define V850E_TIMER_D_CMD_BASE_ADDR &t;(V850E_TIMER_D_BASE_ADDR + 0x8)
DECL|macro|V850E_TIMER_D_BASE_FREQ
mdefine_line|#define V850E_TIMER_D_BASE_FREQ&t;&t;CPU_CLOCK_FREQ
multiline_comment|/* `Interrupt Source Select&squot; control register.  */
DECL|macro|TEG_ISS_ADDR
mdefine_line|#define TEG_ISS_ADDR&t;&t;&t;0xFFFFF7FA
DECL|macro|TEG_ISS
mdefine_line|#define TEG_ISS&t;&t;&t;&t;(*(volatile u8 *)TEG_ISS_ADDR)
multiline_comment|/* Port 0 I/O register (bits 0-3 used).  */
DECL|macro|TEG_PORT0_IO_ADDR
mdefine_line|#define TEG_PORT0_IO_ADDR&t;&t;0xFFFFF7F2
DECL|macro|TEG_PORT0_IO
mdefine_line|#define TEG_PORT0_IO&t;&t;&t;(*(volatile u8 *)TEG_PORT0_IO_ADDR)
multiline_comment|/* Port 0 control register (bits 0-3 control mode, 0 = output, 1 = input).  */
DECL|macro|TEG_PORT0_PM_ADDR
mdefine_line|#define TEG_PORT0_PM_ADDR&t;&t;0xFFFFF7F4
DECL|macro|TEG_PORT0_PM
mdefine_line|#define TEG_PORT0_PM&t;&t;&t;(*(volatile u8 *)TEG_PORT0_PM_ADDR)
macro_line|#ifndef __ASSEMBLY__
r_extern
r_void
id|teg_init_irqs
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif /* __V850_TEG_H__ */
eof
