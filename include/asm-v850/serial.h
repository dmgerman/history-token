multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1999 by Ralf Baechle&n; * Copyright (C) 1999, 2000 Silicon Graphics, Inc.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_RTE_CB_ME2
macro_line|#include &lt;asm/rte_me2_cb.h&gt;
DECL|macro|STD_COM_FLAGS
mdefine_line|#define STD_COM_FLAGS (ASYNC_BOOT_AUTOCONF | ASYNC_SKIP_TEST)
DECL|macro|irq_cannonicalize
mdefine_line|#define irq_cannonicalize(x) (x)
DECL|macro|BASE_BAUD
mdefine_line|#define BASE_BAUD&t;250000&t;/* (16MHz / (16 * 38400)) * 9600 */
DECL|macro|RS_TABLE_SIZE
mdefine_line|#define RS_TABLE_SIZE&t;1
DECL|macro|SERIAL_PORT_DFNS
mdefine_line|#define SERIAL_PORT_DFNS &bslash;&n;   { 0, BASE_BAUD, CB_UART_BASE, IRQ_CB_EXTSIO, STD_COM_FLAGS },
multiline_comment|/* Redefine UART register offsets.  */
DECL|macro|UART_RX
macro_line|#undef UART_RX
DECL|macro|UART_TX
macro_line|#undef UART_TX
DECL|macro|UART_DLL
macro_line|#undef UART_DLL
DECL|macro|UART_TRG
macro_line|#undef UART_TRG
DECL|macro|UART_DLM
macro_line|#undef UART_DLM
DECL|macro|UART_IER
macro_line|#undef UART_IER
DECL|macro|UART_FCTR
macro_line|#undef UART_FCTR
DECL|macro|UART_IIR
macro_line|#undef UART_IIR
DECL|macro|UART_FCR
macro_line|#undef UART_FCR
DECL|macro|UART_EFR
macro_line|#undef UART_EFR
DECL|macro|UART_LCR
macro_line|#undef UART_LCR
DECL|macro|UART_MCR
macro_line|#undef UART_MCR
DECL|macro|UART_LSR
macro_line|#undef UART_LSR
DECL|macro|UART_MSR
macro_line|#undef UART_MSR
DECL|macro|UART_SCR
macro_line|#undef UART_SCR
DECL|macro|UART_EMSR
macro_line|#undef UART_EMSR
DECL|macro|UART_RX
mdefine_line|#define UART_RX&t;&t;(0 * CB_UART_REG_GAP)
DECL|macro|UART_TX
mdefine_line|#define UART_TX&t;&t;(0 * CB_UART_REG_GAP)
DECL|macro|UART_DLL
mdefine_line|#define UART_DLL&t;(0 * CB_UART_REG_GAP)
DECL|macro|UART_TRG
mdefine_line|#define UART_TRG&t;(0 * CB_UART_REG_GAP)
DECL|macro|UART_DLM
mdefine_line|#define UART_DLM&t;(1 * CB_UART_REG_GAP)
DECL|macro|UART_IER
mdefine_line|#define UART_IER&t;(1 * CB_UART_REG_GAP)
DECL|macro|UART_FCTR
mdefine_line|#define UART_FCTR&t;(1 * CB_UART_REG_GAP)
DECL|macro|UART_IIR
mdefine_line|#define UART_IIR&t;(2 * CB_UART_REG_GAP)
DECL|macro|UART_FCR
mdefine_line|#define UART_FCR&t;(2 * CB_UART_REG_GAP)
DECL|macro|UART_EFR
mdefine_line|#define UART_EFR&t;(2 * CB_UART_REG_GAP)
DECL|macro|UART_LCR
mdefine_line|#define UART_LCR&t;(3 * CB_UART_REG_GAP)
DECL|macro|UART_MCR
mdefine_line|#define UART_MCR&t;(4 * CB_UART_REG_GAP)
DECL|macro|UART_LSR
mdefine_line|#define UART_LSR&t;(5 * CB_UART_REG_GAP)
DECL|macro|UART_MSR
mdefine_line|#define UART_MSR&t;(6 * CB_UART_REG_GAP)
DECL|macro|UART_SCR
mdefine_line|#define UART_SCR&t;(7 * CB_UART_REG_GAP)
DECL|macro|UART_EMSR
mdefine_line|#define UART_EMSR&t;(7 * CB_UART_REG_GAP)
macro_line|#endif /* CONFIG_RTE_CB_ME2 */
eof
