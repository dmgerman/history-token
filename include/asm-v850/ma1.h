multiline_comment|/*&n; * include/asm-v850/ma1.h -- V850E/MA1 cpu chip&n; *&n; *  Copyright (C) 2001,02,03  NEC Electronics Corporation&n; *  Copyright (C) 2001,02,03  Miles Bader &lt;miles@gnu.org&gt;&n; *&n; * This file is subject to the terms and conditions of the GNU General&n; * Public License.  See the file COPYING in the main directory of this&n; * archive for more details.&n; *&n; * Written by Miles Bader &lt;miles@gnu.org&gt;&n; */
macro_line|#ifndef __V850_MA1_H__
DECL|macro|__V850_MA1_H__
mdefine_line|#define __V850_MA1_H__
multiline_comment|/* Inherit more generic details from MA series.  */
macro_line|#include &lt;asm/ma.h&gt;
DECL|macro|CPU_MODEL
mdefine_line|#define CPU_MODEL&t;&quot;v850e/ma1&quot;
DECL|macro|CPU_MODEL_LONG
mdefine_line|#define CPU_MODEL_LONG&t;&quot;NEC V850E/MA1&quot;
multiline_comment|/* Hardware-specific interrupt numbers (in the kernel IRQ namespace).  */
DECL|macro|IRQ_INTOV
mdefine_line|#define IRQ_INTOV(n)&t;(n)&t;/* 0-3 */
DECL|macro|IRQ_INTOV_NUM
mdefine_line|#define IRQ_INTOV_NUM&t;4
DECL|macro|IRQ_INTP
mdefine_line|#define IRQ_INTP(n)&t;(0x4  + (n)) /* Pnnn (pin) interrupts */
DECL|macro|IRQ_INTP_NUM
mdefine_line|#define IRQ_INTP_NUM&t;24
DECL|macro|IRQ_INTCMD
mdefine_line|#define IRQ_INTCMD(n)&t;(0x1c + (n)) /* interval timer interrupts 0-3 */
DECL|macro|IRQ_INTCMD_NUM
mdefine_line|#define IRQ_INTCMD_NUM&t;4
DECL|macro|IRQ_INTDMA
mdefine_line|#define IRQ_INTDMA(n)&t;(0x20 + (n)) /* DMA interrupts 0-3 */
DECL|macro|IRQ_INTDMA_NUM
mdefine_line|#define IRQ_INTDMA_NUM&t;4
DECL|macro|IRQ_INTCSI
mdefine_line|#define IRQ_INTCSI(n)&t;(0x24 + (n)*4)/* CSI 0-2 transmit/receive completion */
DECL|macro|IRQ_INTCSI_NUM
mdefine_line|#define IRQ_INTCSI_NUM&t;3
DECL|macro|IRQ_INTSER
mdefine_line|#define IRQ_INTSER(n)&t;(0x25 + (n)*4) /* UART 0-2 reception error */
DECL|macro|IRQ_INTSER_NUM
mdefine_line|#define IRQ_INTSER_NUM&t;3
DECL|macro|IRQ_INTSR
mdefine_line|#define IRQ_INTSR(n)&t;(0x26 + (n)*4) /* UART 0-2 reception completion */
DECL|macro|IRQ_INTSR_NUM
mdefine_line|#define IRQ_INTSR_NUM&t;3
DECL|macro|IRQ_INTST
mdefine_line|#define IRQ_INTST(n)&t;(0x27 + (n)*4) /* UART 0-2 transmission completion */
DECL|macro|IRQ_INTST_NUM
mdefine_line|#define IRQ_INTST_NUM&t;3
DECL|macro|NUM_CPU_IRQS
mdefine_line|#define NUM_CPU_IRQS&t;0x30
multiline_comment|/* The MA1 has a UART with 3 channels.  */
DECL|macro|V850E_UART_NUM_CHANNELS
mdefine_line|#define V850E_UART_NUM_CHANNELS&t;3
macro_line|#endif /* __V850_MA1_H__ */
eof
