multiline_comment|/*&n; * m32r_sio_reg.h&n; *&n; * Copyright (C) 1992, 1994 by Theodore Ts&squot;o.&n; * Copyright (C) 2004  Hirokazu Takata &lt;takata at linux-m32r.org&gt;&n; *&n; * Redistribution of this file is permitted under the terms of the GNU&n; * Public License (GPL)&n; *&n; * These are the UART port assignments, expressed as offsets from the base&n; * register.  These assignments should hold for any serial port based on&n; * a 8250, 16450, or 16550(A).&n; */
macro_line|#ifndef _M32R_SIO_REG_H
DECL|macro|_M32R_SIO_REG_H
mdefine_line|#define _M32R_SIO_REG_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_SERIAL_M32R_PLDSIO
DECL|macro|SIOCR
mdefine_line|#define SIOCR&t;&t;0x000
DECL|macro|SIOMOD0
mdefine_line|#define SIOMOD0&t;&t;0x002
DECL|macro|SIOMOD1
mdefine_line|#define SIOMOD1&t;&t;0x004
DECL|macro|SIOSTS
mdefine_line|#define SIOSTS&t;&t;0x006
DECL|macro|SIOTRCR
mdefine_line|#define SIOTRCR&t;&t;0x008
DECL|macro|SIOBAUR
mdefine_line|#define SIOBAUR&t;&t;0x00a
singleline_comment|// #define SIORBAUR&t;0x018
DECL|macro|SIOTXB
mdefine_line|#define SIOTXB&t;&t;0x00c
DECL|macro|SIORXB
mdefine_line|#define SIORXB&t;&t;0x00e
DECL|macro|UART_RX
mdefine_line|#define UART_RX&t;&t;((unsigned long) PLD_ESIO0RXB)
multiline_comment|/* In:  Receive buffer (DLAB=0) */
DECL|macro|UART_TX
mdefine_line|#define UART_TX&t;&t;((unsigned long) PLD_ESIO0TXB)
multiline_comment|/* Out: Transmit buffer (DLAB=0) */
DECL|macro|UART_DLL
mdefine_line|#define UART_DLL&t;0&t;/* Out: Divisor Latch Low (DLAB=1) */
DECL|macro|UART_TRG
mdefine_line|#define UART_TRG&t;0&t;/* (LCR=BF) FCTR bit 7 selects Rx or Tx&n;&t;&t;&t;&t; * In: Fifo count&n;&t;&t;&t;&t; * Out: Fifo custom trigger levels&n;&t;&t;&t;&t; * XR16C85x only */
DECL|macro|UART_DLM
mdefine_line|#define UART_DLM&t;0&t;/* Out: Divisor Latch High (DLAB=1) */
DECL|macro|UART_IER
mdefine_line|#define UART_IER&t;((unsigned long) PLD_ESIO0INTCR)
multiline_comment|/* Out: Interrupt Enable Register */
DECL|macro|UART_FCTR
mdefine_line|#define UART_FCTR&t;0&t;/* (LCR=BF) Feature Control Register&n;&t;&t;&t;&t; * XR16C85x only */
DECL|macro|UART_IIR
mdefine_line|#define UART_IIR&t;0&t;/* In:  Interrupt ID Register */
DECL|macro|UART_FCR
mdefine_line|#define UART_FCR&t;0&t;/* Out: FIFO Control Register */
DECL|macro|UART_EFR
mdefine_line|#define UART_EFR&t;0&t;/* I/O: Extended Features Register */
multiline_comment|/* (DLAB=1, 16C660 only) */
DECL|macro|UART_LCR
mdefine_line|#define UART_LCR&t;0&t;/* Out: Line Control Register */
DECL|macro|UART_MCR
mdefine_line|#define UART_MCR&t;0&t;/* Out: Modem Control Register */
DECL|macro|UART_LSR
mdefine_line|#define UART_LSR&t;((unsigned long) PLD_ESIO0STS)
multiline_comment|/* In:  Line Status Register */
DECL|macro|UART_MSR
mdefine_line|#define UART_MSR&t;0&t;/* In:  Modem Status Register */
DECL|macro|UART_SCR
mdefine_line|#define UART_SCR&t;0&t;/* I/O: Scratch Register */
DECL|macro|UART_EMSR
mdefine_line|#define UART_EMSR&t;0&t;/* (LCR=BF) Extended Mode Select Register&n;&t;&t;&t;&t; * FCTR bit 6 selects SCR or EMSR&n;&t;&t;&t;&t; * XR16c85x only */
macro_line|#else /* not CONFIG_SERIAL_M32R_PLDSIO */
DECL|macro|SIOCR
mdefine_line|#define SIOCR&t;&t;0x000
DECL|macro|SIOMOD0
mdefine_line|#define SIOMOD0&t;&t;0x004
DECL|macro|SIOMOD1
mdefine_line|#define SIOMOD1&t;&t;0x008
DECL|macro|SIOSTS
mdefine_line|#define SIOSTS&t;&t;0x00c
DECL|macro|SIOTRCR
mdefine_line|#define SIOTRCR&t;&t;0x010
DECL|macro|SIOBAUR
mdefine_line|#define SIOBAUR&t;&t;0x014
DECL|macro|SIORBAUR
mdefine_line|#define SIORBAUR&t;0x018
DECL|macro|SIOTXB
mdefine_line|#define SIOTXB&t;&t;0x01c
DECL|macro|SIORXB
mdefine_line|#define SIORXB&t;&t;0x020
DECL|macro|UART_RX
mdefine_line|#define UART_RX&t;&t;M32R_SIO0_RXB_PORTL&t;/* In:  Receive buffer (DLAB=0) */
DECL|macro|UART_TX
mdefine_line|#define UART_TX&t;&t;M32R_SIO0_TXB_PORTL&t;/* Out: Transmit buffer (DLAB=0) */
DECL|macro|UART_DLL
mdefine_line|#define UART_DLL&t;0&t;/* Out: Divisor Latch Low (DLAB=1) */
DECL|macro|UART_TRG
mdefine_line|#define UART_TRG&t;0&t;/* (LCR=BF) FCTR bit 7 selects Rx or Tx&n;&t;&t;&t;&t; * In: Fifo count&n;&t;&t;&t;&t; * Out: Fifo custom trigger levels&n;&t;&t;&t;&t; * XR16C85x only */
DECL|macro|UART_DLM
mdefine_line|#define UART_DLM&t;0&t;/* Out: Divisor Latch High (DLAB=1) */
DECL|macro|UART_IER
mdefine_line|#define UART_IER&t;M32R_SIO0_TRCR_PORTL&t;/* Out: Interrupt Enable Register */
DECL|macro|UART_FCTR
mdefine_line|#define UART_FCTR&t;0&t;/* (LCR=BF) Feature Control Register&n;&t;&t;&t;&t; * XR16C85x only */
DECL|macro|UART_IIR
mdefine_line|#define UART_IIR&t;0&t;/* In:  Interrupt ID Register */
DECL|macro|UART_FCR
mdefine_line|#define UART_FCR&t;0&t;/* Out: FIFO Control Register */
DECL|macro|UART_EFR
mdefine_line|#define UART_EFR&t;0&t;/* I/O: Extended Features Register */
multiline_comment|/* (DLAB=1, 16C660 only) */
DECL|macro|UART_LCR
mdefine_line|#define UART_LCR&t;0&t;/* Out: Line Control Register */
DECL|macro|UART_MCR
mdefine_line|#define UART_MCR&t;0&t;/* Out: Modem Control Register */
DECL|macro|UART_LSR
mdefine_line|#define UART_LSR&t;M32R_SIO0_STS_PORTL&t;/* In:  Line Status Register */
DECL|macro|UART_MSR
mdefine_line|#define UART_MSR&t;0&t;/* In:  Modem Status Register */
DECL|macro|UART_SCR
mdefine_line|#define UART_SCR&t;0&t;/* I/O: Scratch Register */
DECL|macro|UART_EMSR
mdefine_line|#define UART_EMSR&t;0&t;/* (LCR=BF) Extended Mode Select Register&n;&t;&t;&t;&t; * FCTR bit 6 selects SCR or EMSR&n;&t;&t;&t;&t; * XR16c85x only */
macro_line|#endif /* CONFIG_SERIAL_M32R_PLDSIO */
DECL|macro|UART_EMPTY
mdefine_line|#define UART_EMPTY&t;(UART_LSR_TEMT | UART_LSR_THRE)
multiline_comment|/*&n; * These are the definitions for the Line Control Register&n; *&n; * Note: if the word length is 5 bits (UART_LCR_WLEN5), then setting&n; * UART_LCR_STOP will select 1.5 stop bits, not 2 stop bits.&n; */
DECL|macro|UART_LCR_DLAB
mdefine_line|#define UART_LCR_DLAB&t;0x80&t;/* Divisor latch access bit */
DECL|macro|UART_LCR_SBC
mdefine_line|#define UART_LCR_SBC&t;0x40&t;/* Set break control */
DECL|macro|UART_LCR_SPAR
mdefine_line|#define UART_LCR_SPAR&t;0x20&t;/* Stick parity (?) */
DECL|macro|UART_LCR_EPAR
mdefine_line|#define UART_LCR_EPAR&t;0x10&t;/* Even parity select */
DECL|macro|UART_LCR_PARITY
mdefine_line|#define UART_LCR_PARITY&t;0x08&t;/* Parity Enable */
DECL|macro|UART_LCR_STOP
mdefine_line|#define UART_LCR_STOP&t;0x04&t;/* Stop bits: 0=1 stop bit, 1= 2 stop bits */
DECL|macro|UART_LCR_WLEN5
mdefine_line|#define UART_LCR_WLEN5  0x00&t;/* Wordlength: 5 bits */
DECL|macro|UART_LCR_WLEN6
mdefine_line|#define UART_LCR_WLEN6  0x01&t;/* Wordlength: 6 bits */
DECL|macro|UART_LCR_WLEN7
mdefine_line|#define UART_LCR_WLEN7  0x02&t;/* Wordlength: 7 bits */
DECL|macro|UART_LCR_WLEN8
mdefine_line|#define UART_LCR_WLEN8  0x03&t;/* Wordlength: 8 bits */
multiline_comment|/*&n; * These are the definitions for the Line Status Register&n; */
DECL|macro|UART_LSR_TEMT
mdefine_line|#define UART_LSR_TEMT&t;0x02&t;/* Transmitter empty */
DECL|macro|UART_LSR_THRE
mdefine_line|#define UART_LSR_THRE&t;0x01&t;/* Transmit-hold-register empty */
DECL|macro|UART_LSR_BI
mdefine_line|#define UART_LSR_BI&t;0x00&t;/* Break interrupt indicator */
DECL|macro|UART_LSR_FE
mdefine_line|#define UART_LSR_FE&t;0x80&t;/* Frame error indicator */
DECL|macro|UART_LSR_PE
mdefine_line|#define UART_LSR_PE&t;0x40&t;/* Parity error indicator */
DECL|macro|UART_LSR_OE
mdefine_line|#define UART_LSR_OE&t;0x20&t;/* Overrun error indicator */
DECL|macro|UART_LSR_DR
mdefine_line|#define UART_LSR_DR&t;0x04&t;/* Receiver data ready */
multiline_comment|/*&n; * These are the definitions for the Interrupt Identification Register&n; */
DECL|macro|UART_IIR_NO_INT
mdefine_line|#define UART_IIR_NO_INT&t;0x01&t;/* No interrupts pending */
DECL|macro|UART_IIR_ID
mdefine_line|#define UART_IIR_ID&t;0x06&t;/* Mask for the interrupt ID */
DECL|macro|UART_IIR_MSI
mdefine_line|#define UART_IIR_MSI&t;0x00&t;/* Modem status interrupt */
DECL|macro|UART_IIR_THRI
mdefine_line|#define UART_IIR_THRI&t;0x02&t;/* Transmitter holding register empty */
DECL|macro|UART_IIR_RDI
mdefine_line|#define UART_IIR_RDI&t;0x04&t;/* Receiver data interrupt */
DECL|macro|UART_IIR_RLSI
mdefine_line|#define UART_IIR_RLSI&t;0x06&t;/* Receiver line status interrupt */
multiline_comment|/*&n; * These are the definitions for the Interrupt Enable Register&n; */
DECL|macro|UART_IER_MSI
mdefine_line|#define UART_IER_MSI&t;0x00&t;/* Enable Modem status interrupt */
DECL|macro|UART_IER_RLSI
mdefine_line|#define UART_IER_RLSI&t;0x08&t;/* Enable receiver line status interrupt */
DECL|macro|UART_IER_THRI
mdefine_line|#define UART_IER_THRI&t;0x03&t;/* Enable Transmitter holding register int. */
DECL|macro|UART_IER_RDI
mdefine_line|#define UART_IER_RDI&t;0x04&t;/* Enable receiver data interrupt */
macro_line|#endif /* _M32R_SIO_REG_H */
eof
