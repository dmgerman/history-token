multiline_comment|/*&n; * include/asm-v850/nb85e_teg.h -- NB85E-TEG cpu chip&n; *&n; *  Copyright (C) 2001,02  NEC Corporation&n; *  Copyright (C) 2001,02  Miles Bader &lt;miles@gnu.org&gt;&n; *&n; * This file is subject to the terms and conditions of the GNU General&n; * Public License.  See the file COPYING in the main directory of this&n; * archive for more details.&n; *&n; * Written by Miles Bader &lt;miles@gnu.org&gt;&n; */
macro_line|#ifndef __V850_NB85E_TEG_H__
DECL|macro|__V850_NB85E_TEG_H__
mdefine_line|#define __V850_NB85E_TEG_H__
multiline_comment|/* The NB85E_TEG uses the NB85E cpu core.  */
macro_line|#include &lt;asm/nb85e.h&gt;
DECL|macro|CHIP
mdefine_line|#define CHIP&t;&t;&quot;v850e/nb85e-teg&quot;
DECL|macro|CHIP_LONG
mdefine_line|#define CHIP_LONG&t;&quot;NEC V850E/NB85E TEG&quot;
multiline_comment|/* Hardware-specific interrupt numbers (in the kernel IRQ namespace).  */
DECL|macro|IRQ_INTOV
mdefine_line|#define IRQ_INTOV(n)&t;(n)&t;/* 0-3 */
DECL|macro|IRQ_INTOV_NUM
mdefine_line|#define IRQ_INTOV_NUM&t;4
DECL|macro|IRQ_INTCMD
mdefine_line|#define IRQ_INTCMD(n)&t;(0x1c + (n)) /* interval timer interrupts 0-3 */
DECL|macro|IRQ_INTCMD_NUM
mdefine_line|#define IRQ_INTCMD_NUM&t;4
DECL|macro|IRQ_INTDMA
mdefine_line|#define IRQ_INTDMA(n)&t;(0x20 + (n)) /* DMA interrupts 0-3 */
DECL|macro|IRQ_INTDMA_NUM
mdefine_line|#define IRQ_INTDMA_NUM&t;4
DECL|macro|IRQ_INTCSI
mdefine_line|#define IRQ_INTCSI(n)&t;(0x24 + (n)) /* CSI 0-2 transmit/receive completion */
DECL|macro|IRQ_INTCSI_NUM
mdefine_line|#define IRQ_INTCSI_NUM&t;3
DECL|macro|IRQ_INTSER
mdefine_line|#define IRQ_INTSER(n)&t;(0x25 + (n)) /* UART 0-2 reception error */
DECL|macro|IRQ_INTSER_NUM
mdefine_line|#define IRQ_INTSER_NUM&t;3
DECL|macro|IRQ_INTSR
mdefine_line|#define IRQ_INTSR(n)&t;(0x26 + (n)) /* UART 0-2 reception completion */
DECL|macro|IRQ_INTSR_NUM
mdefine_line|#define IRQ_INTSR_NUM&t;3
DECL|macro|IRQ_INTST
mdefine_line|#define IRQ_INTST(n)&t;(0x27 + (n)) /* UART 0-2 transmission completion */
DECL|macro|IRQ_INTST_NUM
mdefine_line|#define IRQ_INTST_NUM&t;3
multiline_comment|/* For &lt;asm/irq.h&gt; */
DECL|macro|NUM_MACH_IRQS
mdefine_line|#define NUM_MACH_IRQS&t;0x30
multiline_comment|/* TEG UART details.  */
DECL|macro|NB85E_UART_BASE_ADDR
mdefine_line|#define NB85E_UART_BASE_ADDR(n)&t;&t;(0xFFFFF600 + 0x10 * (n))
DECL|macro|NB85E_UART_ASIM_ADDR
mdefine_line|#define NB85E_UART_ASIM_ADDR(n)&t;&t;(NB85E_UART_BASE_ADDR(n) + 0x0)
DECL|macro|NB85E_UART_ASIS_ADDR
mdefine_line|#define NB85E_UART_ASIS_ADDR(n)&t;&t;(NB85E_UART_BASE_ADDR(n) + 0x2)
DECL|macro|NB85E_UART_ASIF_ADDR
mdefine_line|#define NB85E_UART_ASIF_ADDR(n)&t;&t;(NB85E_UART_BASE_ADDR(n) + 0x4)
DECL|macro|NB85E_UART_CKSR_ADDR
mdefine_line|#define NB85E_UART_CKSR_ADDR(n)&t;&t;(NB85E_UART_BASE_ADDR(n) + 0x6)
DECL|macro|NB85E_UART_BRGC_ADDR
mdefine_line|#define NB85E_UART_BRGC_ADDR(n)&t;&t;(NB85E_UART_BASE_ADDR(n) + 0x8)
DECL|macro|NB85E_UART_TXB_ADDR
mdefine_line|#define NB85E_UART_TXB_ADDR(n)&t;&t;(NB85E_UART_BASE_ADDR(n) + 0xA)
DECL|macro|NB85E_UART_RXB_ADDR
mdefine_line|#define NB85E_UART_RXB_ADDR(n)&t;&t;(NB85E_UART_BASE_ADDR(n) + 0xC)
DECL|macro|NB85E_UART_NUM_CHANNELS
mdefine_line|#define NB85E_UART_NUM_CHANNELS&t;&t;1
DECL|macro|NB85E_UART_BASE_FREQ
mdefine_line|#define NB85E_UART_BASE_FREQ&t;&t;CPU_CLOCK_FREQ
multiline_comment|/* The TEG RTPU.  */
DECL|macro|NB85E_RTPU_BASE_ADDR
mdefine_line|#define NB85E_RTPU_BASE_ADDR&t;&t;0xFFFFF210
macro_line|#endif /* __V850_NB85E_TEG_H__ */
eof
