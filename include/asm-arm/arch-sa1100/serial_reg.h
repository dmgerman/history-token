multiline_comment|/*&n; * include/asm/arch/serial_reg.h&n; *&n; * Redistribution of this file is permitted under the terms of the GNU &n; * Public License (GPL)&n; * &n; * These are the SA1100 UART port assignments, expressed as long index &n; * of the base address.&n; */
macro_line|#ifndef ASM_ARCH_SERIAL_REG_H
DECL|macro|ASM_ARCH_SERIAL_REG_H
mdefine_line|#define ASM_ARCH_SERIAL_REG_H
multiline_comment|/*&n; * Register index.&n; */
DECL|macro|UTCR0
mdefine_line|#define UTCR0 &t;&t;0&t;/* 0x00 UART_LCR  Line control register */
DECL|macro|UTCR1
mdefine_line|#define UTCR1 &t;&t;1&t;/* 0x04 UART_DLLSB */
DECL|macro|UTCR2
mdefine_line|#define UTCR2 &t;&t;2&t;/* 0x08 UART_DLMSB */
DECL|macro|UTCR3
mdefine_line|#define UTCR3 &t;&t;3&t;/* 0x0c UART_IER */
DECL|macro|UTDR
mdefine_line|#define UTDR &t;&t;5&t;/* 0x14 UART_RX, UART_TX */
DECL|macro|UTSR0
mdefine_line|#define UTSR0 &t;&t;7&t;/* 0x1c */
DECL|macro|UTSR1
mdefine_line|#define UTSR1 &t;&t;8&t;/* 0x20 UART_LSR  Line Status register */
DECL|macro|UART_RX
mdefine_line|#define UART_RX &t;UTDR&t;&t;/* Receive port, read only */
DECL|macro|UART_TX
mdefine_line|#define UART_TX &t;UTDR&t;&t;/* transmit port, write only */
macro_line|#if 0
multiline_comment|/*&n; * Line control register flags&n; */
mdefine_line|#define UTCR0_PE &t;1&t;&t;/* Parity enable */
mdefine_line|#define UTCR0_EP &t;2&t;&t;/* Even parity */
mdefine_line|#define UTCR0_SB &t;4&t;&t;/* Stop bit */
mdefine_line|#define UTCR0_DB &t;8&t;&t;/* Data bits in transmission (0 = 7, 1 = 8) */
mdefine_line|#define UTCR0_OES&t;UTCR0_EP
mdefine_line|#define UTCR0_SBS&t;UTCR0_SB
mdefine_line|#define UTCR0_DSS&t;UTCR0_DB
mdefine_line|#define UTCR0_SCE&t;16&t;&t;/* Sample clock enable */
mdefine_line|#define UTCR0_RCE&t;32&t;&t;/* Receive clock edge select */
mdefine_line|#define UTCR0_TCE&t;64&t;&t;/* Transmit clock edge select */
multiline_comment|/*&n; * Line status bits.&n; */
mdefine_line|#define UTSR1_TBY &t;1&t;&t;/* transmitter busy flag */
mdefine_line|#define UTSR1_RNE &t;2&t;&t;/* receiver not empty (LSR_DR) */
mdefine_line|#define UTSR1_TNF &t;4&t;&t;/* transmit fifo non full */
mdefine_line|#define UTSR1_PRE &t;8&t;&t;/* parity read error (LSR_PE) */
mdefine_line|#define UTSR1_FRE &t;16&t;&t;/* framing error (LSR_FE) */
mdefine_line|#define UTSR1_ROR &t;32&t;&t;/* receive fifo overrun (LSR_OE) */
mdefine_line|#define UTSR1_ERROR &t;(UTSR1_PRE | UTSR1_FRE | UTSR1_ROR)  /* LSR_ERROR */
mdefine_line|#define UTSR0_TFS &t;1&t;&t;/* transmit fifo service request */
mdefine_line|#define UTSR0_RFS &t;2&t;&t;/* receive fifo service request */
mdefine_line|#define UTSR0_RID&t;4&t;&t;/* receiver idle */
mdefine_line|#define UTSR0_RBB &t;8&t;&t;/* receiver begin of break */
mdefine_line|#define UTSR0_REB &t;16&t;&t;/* receiver end of break */
mdefine_line|#define UTSR0_EIF &t;32&t;&t;/* error in fifo */
multiline_comment|/*&n; * Interrupt enable register (IER)&n; */
mdefine_line|#define UTCR3_RXE &t;1&t;&t;/* Receiver enable */
mdefine_line|#define UTCR3_TXE &t;2&t;&t;/* Transmit enable */
mdefine_line|#define UTCR3_BRK &t;4&t;&t;/* Break */
mdefine_line|#define UTCR3_RIM &t;8&t;&t;/* Receive FIFO interrupt mask (IER_RDA) */
mdefine_line|#define UTCR3_TIM &t;16&t;&t;/* Transmit FIFO interrupt mask (IER_THRE) */
mdefine_line|#define UTCR3_LBM &t;32&t;&t;/* Loop Back Mode */
macro_line|#endif 
macro_line|#endif /* ASM_ARCH_SERIAL_REG_H */
eof
