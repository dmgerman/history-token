multiline_comment|/*&n; * include/asm-v850/ma.h -- V850E/MA series of cpu chips&n; *&n; *  Copyright (C) 2001,02,03  NEC Electronics Corporation&n; *  Copyright (C) 2001,02,03  Miles Bader &lt;miles@gnu.org&gt;&n; *&n; * This file is subject to the terms and conditions of the GNU General&n; * Public License.  See the file COPYING in the main directory of this&n; * archive for more details.&n; *&n; * Written by Miles Bader &lt;miles@gnu.org&gt;&n; */
macro_line|#ifndef __V850_MA_H__
DECL|macro|__V850_MA_H__
mdefine_line|#define __V850_MA_H__
multiline_comment|/* The MA series uses the V850E cpu core.  */
macro_line|#include &lt;asm/v850e.h&gt;
multiline_comment|/* For &lt;asm/entry.h&gt; */
multiline_comment|/* We use on-chip RAM, for a few miscellaneous variables that must be&n;   accessible using a load instruction relative to R0.  The amount&n;   varies between chip models, but there&squot;s always at least 4K, and it&n;   should always start at FFFFC000.  */
DECL|macro|R0_RAM_ADDR
mdefine_line|#define R0_RAM_ADDR&t;&t;&t;0xFFFFC000
multiline_comment|/* MA series UART details.  */
DECL|macro|V850E_UART_BASE_FREQ
mdefine_line|#define V850E_UART_BASE_FREQ&t;&t;CPU_CLOCK_FREQ
multiline_comment|/* This is a function that gets called before configuring the UART.  */
DECL|macro|V850E_UART_PRE_CONFIGURE
mdefine_line|#define V850E_UART_PRE_CONFIGURE&t;ma_uart_pre_configure
macro_line|#ifndef __ASSEMBLY__
r_extern
r_void
id|ma_uart_pre_configure
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
multiline_comment|/* MA series timer C details.  */
DECL|macro|V850E_TIMER_C_BASE_ADDR
mdefine_line|#define V850E_TIMER_C_BASE_ADDR&t;&t;0xFFFFF600
multiline_comment|/* MA series timer D details.  */
DECL|macro|V850E_TIMER_D_BASE_ADDR
mdefine_line|#define V850E_TIMER_D_BASE_ADDR&t;&t;0xFFFFF540
DECL|macro|V850E_TIMER_D_TMD_BASE_ADDR
mdefine_line|#define V850E_TIMER_D_TMD_BASE_ADDR &t;(V850E_TIMER_D_BASE_ADDR + 0x0)
DECL|macro|V850E_TIMER_D_CMD_BASE_ADDR
mdefine_line|#define V850E_TIMER_D_CMD_BASE_ADDR &t;(V850E_TIMER_D_BASE_ADDR + 0x2)
DECL|macro|V850E_TIMER_D_TMCD_BASE_ADDR
mdefine_line|#define V850E_TIMER_D_TMCD_BASE_ADDR &t;(V850E_TIMER_D_BASE_ADDR + 0x4)
DECL|macro|V850E_TIMER_D_BASE_FREQ
mdefine_line|#define V850E_TIMER_D_BASE_FREQ&t;&t;CPU_CLOCK_FREQ
multiline_comment|/* Port 0 */
multiline_comment|/* Direct I/O.  Bits 0-7 are pins P00-P07.  */
DECL|macro|MA_PORT0_IO_ADDR
mdefine_line|#define MA_PORT0_IO_ADDR&t;&t;0xFFFFF400
DECL|macro|MA_PORT0_IO
mdefine_line|#define MA_PORT0_IO&t;&t;&t;(*(volatile u8 *)MA_PORT0_IO_ADDR)
multiline_comment|/* Port mode (for direct I/O, 0 = output, 1 = input).  */
DECL|macro|MA_PORT0_PM_ADDR
mdefine_line|#define MA_PORT0_PM_ADDR&t;&t;0xFFFFF420
DECL|macro|MA_PORT0_PM
mdefine_line|#define MA_PORT0_PM&t;&t;&t;(*(volatile u8 *)MA_PORT0_PM_ADDR)
multiline_comment|/* Port mode control (0 = direct I/O mode, 1 = alternative I/O mode).  */
DECL|macro|MA_PORT0_PMC_ADDR
mdefine_line|#define MA_PORT0_PMC_ADDR&t;&t;0xFFFFF440
DECL|macro|MA_PORT0_PMC
mdefine_line|#define MA_PORT0_PMC&t;&t;&t;(*(volatile u8 *)MA_PORT0_PMC_ADDR)
multiline_comment|/* Port function control (for P04-P07, 0 = IRQ, 1 = DMARQ).  */
DECL|macro|MA_PORT0_PFC_ADDR
mdefine_line|#define MA_PORT0_PFC_ADDR&t;&t;0xFFFFF460
DECL|macro|MA_PORT0_PFC
mdefine_line|#define MA_PORT0_PFC&t;&t;&t;(*(volatile u8 *)MA_PORT0_PFC_ADDR)
multiline_comment|/* Port 1 */
multiline_comment|/* Direct I/O.  Bits 0-3 are pins P10-P13.  */
DECL|macro|MA_PORT1_IO_ADDR
mdefine_line|#define MA_PORT1_IO_ADDR&t;&t;0xFFFFF402
DECL|macro|MA_PORT1_IO
mdefine_line|#define MA_PORT1_IO&t;&t;&t;(*(volatile u8 *)MA_PORT1_IO_ADDR)
multiline_comment|/* Port mode (for direct I/O, 0 = output, 1 = input).  */
DECL|macro|MA_PORT1_PM_ADDR
mdefine_line|#define MA_PORT1_PM_ADDR&t;&t;0xFFFFF420
DECL|macro|MA_PORT1_PM
mdefine_line|#define MA_PORT1_PM&t;&t;&t;(*(volatile u8 *)MA_PORT1_PM_ADDR)
multiline_comment|/* Port mode control (0 = direct I/O mode, 1 = alternative I/O mode).  */
DECL|macro|MA_PORT1_PMC_ADDR
mdefine_line|#define MA_PORT1_PMC_ADDR&t;&t;0xFFFFF442
DECL|macro|MA_PORT1_PMC
mdefine_line|#define MA_PORT1_PMC&t;&t;&t;(*(volatile u8 *)MA_PORT1_PMC_ADDR)
multiline_comment|/* Port 4 */
multiline_comment|/* Direct I/O.  Bits 0-5 are pins P40-P45.  */
DECL|macro|MA_PORT4_IO_ADDR
mdefine_line|#define MA_PORT4_IO_ADDR&t;&t;0xFFFFF408
DECL|macro|MA_PORT4_IO
mdefine_line|#define MA_PORT4_IO&t;&t;&t;(*(volatile u8 *)MA_PORT4_IO_ADDR)
multiline_comment|/* Port mode (for direct I/O, 0 = output, 1 = input).  */
DECL|macro|MA_PORT4_PM_ADDR
mdefine_line|#define MA_PORT4_PM_ADDR&t;&t;0xFFFFF428
DECL|macro|MA_PORT4_PM
mdefine_line|#define MA_PORT4_PM&t;&t;&t;(*(volatile u8 *)MA_PORT4_PM_ADDR)
multiline_comment|/* Port mode control (0 = direct I/O mode, 1 = alternative I/O mode).  */
DECL|macro|MA_PORT4_PMC_ADDR
mdefine_line|#define MA_PORT4_PMC_ADDR&t;&t;0xFFFFF448
DECL|macro|MA_PORT4_PMC
mdefine_line|#define MA_PORT4_PMC&t;&t;&t;(*(volatile u8 *)MA_PORT4_PMC_ADDR)
multiline_comment|/* Port function control (for serial interfaces, 0 = CSI, 1 = UART).  */
DECL|macro|MA_PORT4_PFC_ADDR
mdefine_line|#define MA_PORT4_PFC_ADDR&t;&t;0xFFFFF468
DECL|macro|MA_PORT4_PFC
mdefine_line|#define MA_PORT4_PFC&t;&t;&t;(*(volatile u8 *)MA_PORT4_PFC_ADDR)
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/* Initialize MA chip interrupts.  */
r_extern
r_void
id|ma_init_irqs
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* !__ASSEMBLY__ */
macro_line|#endif /* __V850_MA_H__ */
eof
