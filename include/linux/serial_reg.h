multiline_comment|/*&n; * include/linux/serial_reg.h&n; *&n; * Copyright (C) 1992, 1994 by Theodore Ts&squot;o.&n; * &n; * Redistribution of this file is permitted under the terms of the GNU &n; * Public License (GPL)&n; * &n; * These are the UART port assignments, expressed as offsets from the base&n; * register.  These assignments should hold for any serial port based on&n; * a 8250, 16450, or 16550(A).&n; */
macro_line|#ifndef _LINUX_SERIAL_REG_H
DECL|macro|_LINUX_SERIAL_REG_H
mdefine_line|#define _LINUX_SERIAL_REG_H
multiline_comment|/*&n; * DLAB=0&n; */
DECL|macro|UART_RX
mdefine_line|#define UART_RX&t;&t;0&t;/* In:  Receive buffer */
DECL|macro|UART_TX
mdefine_line|#define UART_TX&t;&t;0&t;/* Out: Transmit buffer */
DECL|macro|UART_IER
mdefine_line|#define UART_IER&t;1&t;/* Out: Interrupt Enable Register */
DECL|macro|UART_IER_MSI
mdefine_line|#define UART_IER_MSI&t;&t;0x08 /* Enable Modem status interrupt */
DECL|macro|UART_IER_RLSI
mdefine_line|#define UART_IER_RLSI&t;&t;0x04 /* Enable receiver line status interrupt */
DECL|macro|UART_IER_THRI
mdefine_line|#define UART_IER_THRI&t;&t;0x02 /* Enable Transmitter holding register int. */
DECL|macro|UART_IER_RDI
mdefine_line|#define UART_IER_RDI&t;&t;0x01 /* Enable receiver data interrupt */
multiline_comment|/*&n; * Sleep mode for ST16650 and TI16750.  For the ST16650, EFR[4]=1&n; */
DECL|macro|UART_IERX_SLEEP
mdefine_line|#define UART_IERX_SLEEP&t;&t;0x10 /* Enable sleep mode */
DECL|macro|UART_IIR
mdefine_line|#define UART_IIR&t;2&t;/* In:  Interrupt ID Register */
DECL|macro|UART_IIR_NO_INT
mdefine_line|#define UART_IIR_NO_INT&t;&t;0x01 /* No interrupts pending */
DECL|macro|UART_IIR_ID
mdefine_line|#define UART_IIR_ID&t;&t;0x06 /* Mask for the interrupt ID */
DECL|macro|UART_IIR_MSI
mdefine_line|#define UART_IIR_MSI&t;&t;0x00 /* Modem status interrupt */
DECL|macro|UART_IIR_THRI
mdefine_line|#define UART_IIR_THRI&t;&t;0x02 /* Transmitter holding register empty */
DECL|macro|UART_IIR_RDI
mdefine_line|#define UART_IIR_RDI&t;&t;0x04 /* Receiver data interrupt */
DECL|macro|UART_IIR_RLSI
mdefine_line|#define UART_IIR_RLSI&t;&t;0x06 /* Receiver line status interrupt */
DECL|macro|UART_FCR
mdefine_line|#define UART_FCR&t;2&t;/* Out: FIFO Control Register */
DECL|macro|UART_FCR_ENABLE_FIFO
mdefine_line|#define UART_FCR_ENABLE_FIFO&t;0x01 /* Enable the FIFO */
DECL|macro|UART_FCR_CLEAR_RCVR
mdefine_line|#define UART_FCR_CLEAR_RCVR&t;0x02 /* Clear the RCVR FIFO */
DECL|macro|UART_FCR_CLEAR_XMIT
mdefine_line|#define UART_FCR_CLEAR_XMIT&t;0x04 /* Clear the XMIT FIFO */
DECL|macro|UART_FCR_DMA_SELECT
mdefine_line|#define UART_FCR_DMA_SELECT&t;0x08 /* For DMA applications */
multiline_comment|/*&n; * Note: The FIFO trigger levels are chip specific:&n; *&t;RX:76 = 00  01  10  11&t;TX:54 = 00  01  10  11&n; * PC16550D:&t; 1   4   8  14&t;&t;xx  xx  xx  xx&n; * TI16C550A:&t; 1   4   8  14          xx  xx  xx  xx&n; * TI16C550C:&t; 1   4   8  14          xx  xx  xx  xx&n; * ST16C550:&t; 1   4   8  14&t;&t;xx  xx  xx  xx&n; * ST16C650:&t; 8  16  24  28&t;&t;16   8  24  30&t;PORT_16650V2&n; * NS16C552:&t; 1   4   8  14&t;&t;xx  xx  xx  xx&n; * ST16C654:&t; 8  16  56  60&t;&t; 8  16  32  56&t;PORT_16654&n; * TI16C750:&t; 1  16  32  56&t;&t;xx  xx  xx  xx&t;PORT_16750&n; * TI16C752:&t; 8  16  56  60&t;&t; 8  16  32  56&n; */
DECL|macro|UART_FCR_R_TRIG_00
mdefine_line|#define UART_FCR_R_TRIG_00&t;0x00
DECL|macro|UART_FCR_R_TRIG_01
mdefine_line|#define UART_FCR_R_TRIG_01&t;0x40
DECL|macro|UART_FCR_R_TRIG_10
mdefine_line|#define UART_FCR_R_TRIG_10&t;0x80
DECL|macro|UART_FCR_R_TRIG_11
mdefine_line|#define UART_FCR_R_TRIG_11&t;0xc0
DECL|macro|UART_FCR_T_TRIG_00
mdefine_line|#define UART_FCR_T_TRIG_00&t;0x00
DECL|macro|UART_FCR_T_TRIG_01
mdefine_line|#define UART_FCR_T_TRIG_01&t;0x10
DECL|macro|UART_FCR_T_TRIG_10
mdefine_line|#define UART_FCR_T_TRIG_10&t;0x20
DECL|macro|UART_FCR_T_TRIG_11
mdefine_line|#define UART_FCR_T_TRIG_11&t;0x30
DECL|macro|UART_FCR_TRIGGER_MASK
mdefine_line|#define UART_FCR_TRIGGER_MASK&t;0xC0 /* Mask for the FIFO trigger range */
DECL|macro|UART_FCR_TRIGGER_1
mdefine_line|#define UART_FCR_TRIGGER_1&t;0x00 /* Mask for trigger set at 1 */
DECL|macro|UART_FCR_TRIGGER_4
mdefine_line|#define UART_FCR_TRIGGER_4&t;0x40 /* Mask for trigger set at 4 */
DECL|macro|UART_FCR_TRIGGER_8
mdefine_line|#define UART_FCR_TRIGGER_8&t;0x80 /* Mask for trigger set at 8 */
DECL|macro|UART_FCR_TRIGGER_14
mdefine_line|#define UART_FCR_TRIGGER_14&t;0xC0 /* Mask for trigger set at 14 */
multiline_comment|/* 16650 definitions */
DECL|macro|UART_FCR6_R_TRIGGER_8
mdefine_line|#define UART_FCR6_R_TRIGGER_8&t;0x00 /* Mask for receive trigger set at 1 */
DECL|macro|UART_FCR6_R_TRIGGER_16
mdefine_line|#define UART_FCR6_R_TRIGGER_16&t;0x40 /* Mask for receive trigger set at 4 */
DECL|macro|UART_FCR6_R_TRIGGER_24
mdefine_line|#define UART_FCR6_R_TRIGGER_24  0x80 /* Mask for receive trigger set at 8 */
DECL|macro|UART_FCR6_R_TRIGGER_28
mdefine_line|#define UART_FCR6_R_TRIGGER_28&t;0xC0 /* Mask for receive trigger set at 14 */
DECL|macro|UART_FCR6_T_TRIGGER_16
mdefine_line|#define UART_FCR6_T_TRIGGER_16&t;0x00 /* Mask for transmit trigger set at 16 */
DECL|macro|UART_FCR6_T_TRIGGER_8
mdefine_line|#define UART_FCR6_T_TRIGGER_8&t;0x10 /* Mask for transmit trigger set at 8 */
DECL|macro|UART_FCR6_T_TRIGGER_24
mdefine_line|#define UART_FCR6_T_TRIGGER_24  0x20 /* Mask for transmit trigger set at 24 */
DECL|macro|UART_FCR6_T_TRIGGER_30
mdefine_line|#define UART_FCR6_T_TRIGGER_30&t;0x30 /* Mask for transmit trigger set at 30 */
DECL|macro|UART_FCR7_64BYTE
mdefine_line|#define UART_FCR7_64BYTE&t;0x20 /* Go into 64 byte mode (TI16C750) */
DECL|macro|UART_LCR
mdefine_line|#define UART_LCR&t;3&t;/* Out: Line Control Register */
multiline_comment|/*&n; * Note: if the word length is 5 bits (UART_LCR_WLEN5), then setting &n; * UART_LCR_STOP will select 1.5 stop bits, not 2 stop bits.&n; */
DECL|macro|UART_LCR_DLAB
mdefine_line|#define UART_LCR_DLAB&t;&t;0x80 /* Divisor latch access bit */
DECL|macro|UART_LCR_SBC
mdefine_line|#define UART_LCR_SBC&t;&t;0x40 /* Set break control */
DECL|macro|UART_LCR_SPAR
mdefine_line|#define UART_LCR_SPAR&t;&t;0x20 /* Stick parity (?) */
DECL|macro|UART_LCR_EPAR
mdefine_line|#define UART_LCR_EPAR&t;&t;0x10 /* Even parity select */
DECL|macro|UART_LCR_PARITY
mdefine_line|#define UART_LCR_PARITY&t;&t;0x08 /* Parity Enable */
DECL|macro|UART_LCR_STOP
mdefine_line|#define UART_LCR_STOP&t;&t;0x04 /* Stop bits: 0=1 bit, 1=2 bits */
DECL|macro|UART_LCR_WLEN5
mdefine_line|#define UART_LCR_WLEN5&t;&t;0x00 /* Wordlength: 5 bits */
DECL|macro|UART_LCR_WLEN6
mdefine_line|#define UART_LCR_WLEN6&t;&t;0x01 /* Wordlength: 6 bits */
DECL|macro|UART_LCR_WLEN7
mdefine_line|#define UART_LCR_WLEN7&t;&t;0x02 /* Wordlength: 7 bits */
DECL|macro|UART_LCR_WLEN8
mdefine_line|#define UART_LCR_WLEN8&t;&t;0x03 /* Wordlength: 8 bits */
DECL|macro|UART_MCR
mdefine_line|#define UART_MCR&t;4&t;/* Out: Modem Control Register */
DECL|macro|UART_MCR_CLKSEL
mdefine_line|#define UART_MCR_CLKSEL&t;&t;0x80 /* Divide clock by 4 (TI16C752, EFR[4]=1) */
DECL|macro|UART_MCR_TCRTLR
mdefine_line|#define UART_MCR_TCRTLR&t;&t;0x40 /* Access TCR/TLR (TI16C752, EFR[4]=1) */
DECL|macro|UART_MCR_XONANY
mdefine_line|#define UART_MCR_XONANY&t;&t;0x20 /* Enable Xon Any (TI16C752, EFR[4]=1) */
DECL|macro|UART_MCR_AFE
mdefine_line|#define UART_MCR_AFE&t;&t;0x20 /* Enable auto-RTS/CTS (TI16C550C/TI16C750) */
DECL|macro|UART_MCR_LOOP
mdefine_line|#define UART_MCR_LOOP&t;&t;0x10 /* Enable loopback test mode */
DECL|macro|UART_MCR_OUT2
mdefine_line|#define UART_MCR_OUT2&t;&t;0x08 /* Out2 complement */
DECL|macro|UART_MCR_OUT1
mdefine_line|#define UART_MCR_OUT1&t;&t;0x04 /* Out1 complement */
DECL|macro|UART_MCR_RTS
mdefine_line|#define UART_MCR_RTS&t;&t;0x02 /* RTS complement */
DECL|macro|UART_MCR_DTR
mdefine_line|#define UART_MCR_DTR&t;&t;0x01 /* DTR complement */
DECL|macro|UART_LSR
mdefine_line|#define UART_LSR&t;5&t;/* In:  Line Status Register */
DECL|macro|UART_LSR_TEMT
mdefine_line|#define UART_LSR_TEMT&t;&t;0x40 /* Transmitter empty */
DECL|macro|UART_LSR_THRE
mdefine_line|#define UART_LSR_THRE&t;&t;0x20 /* Transmit-hold-register empty */
DECL|macro|UART_LSR_BI
mdefine_line|#define UART_LSR_BI&t;&t;0x10 /* Break interrupt indicator */
DECL|macro|UART_LSR_FE
mdefine_line|#define UART_LSR_FE&t;&t;0x08 /* Frame error indicator */
DECL|macro|UART_LSR_PE
mdefine_line|#define UART_LSR_PE&t;&t;0x04 /* Parity error indicator */
DECL|macro|UART_LSR_OE
mdefine_line|#define UART_LSR_OE&t;&t;0x02 /* Overrun error indicator */
DECL|macro|UART_LSR_DR
mdefine_line|#define UART_LSR_DR&t;&t;0x01 /* Receiver data ready */
DECL|macro|UART_MSR
mdefine_line|#define UART_MSR&t;6&t;/* In:  Modem Status Register */
DECL|macro|UART_MSR_DCD
mdefine_line|#define UART_MSR_DCD&t;&t;0x80 /* Data Carrier Detect */
DECL|macro|UART_MSR_RI
mdefine_line|#define UART_MSR_RI&t;&t;0x40 /* Ring Indicator */
DECL|macro|UART_MSR_DSR
mdefine_line|#define UART_MSR_DSR&t;&t;0x20 /* Data Set Ready */
DECL|macro|UART_MSR_CTS
mdefine_line|#define UART_MSR_CTS&t;&t;0x10 /* Clear to Send */
DECL|macro|UART_MSR_DDCD
mdefine_line|#define UART_MSR_DDCD&t;&t;0x08 /* Delta DCD */
DECL|macro|UART_MSR_TERI
mdefine_line|#define UART_MSR_TERI&t;&t;0x04 /* Trailing edge ring indicator */
DECL|macro|UART_MSR_DDSR
mdefine_line|#define UART_MSR_DDSR&t;&t;0x02 /* Delta DSR */
DECL|macro|UART_MSR_DCTS
mdefine_line|#define UART_MSR_DCTS&t;&t;0x01 /* Delta CTS */
DECL|macro|UART_MSR_ANY_DELTA
mdefine_line|#define UART_MSR_ANY_DELTA&t;0x0F /* Any of the delta bits! */
DECL|macro|UART_SCR
mdefine_line|#define UART_SCR&t;7&t;/* I/O: Scratch Register */
multiline_comment|/*&n; * DLAB=1&n; */
DECL|macro|UART_DLL
mdefine_line|#define UART_DLL&t;0&t;/* Out: Divisor Latch Low */
DECL|macro|UART_DLM
mdefine_line|#define UART_DLM&t;1&t;/* Out: Divisor Latch High */
multiline_comment|/*&n; * LCR=0xBF (or DLAB=1 for 16C660)&n; */
DECL|macro|UART_EFR
mdefine_line|#define UART_EFR&t;2&t;/* I/O: Extended Features Register */
DECL|macro|UART_EFR_CTS
mdefine_line|#define UART_EFR_CTS&t;&t;0x80 /* CTS flow control */
DECL|macro|UART_EFR_RTS
mdefine_line|#define UART_EFR_RTS&t;&t;0x40 /* RTS flow control */
DECL|macro|UART_EFR_SCD
mdefine_line|#define UART_EFR_SCD&t;&t;0x20 /* Special character detect */
DECL|macro|UART_EFR_ECB
mdefine_line|#define UART_EFR_ECB&t;&t;0x10 /* Enhanced control bit */
multiline_comment|/*&n; * the low four bits control software flow control&n; */
multiline_comment|/*&n; * LCR=0xBF, TI16C752, ST16650, ST16650A, ST16654&n; */
DECL|macro|UART_XON1
mdefine_line|#define UART_XON1&t;4&t;/* I/O: Xon character 1 */
DECL|macro|UART_XON2
mdefine_line|#define UART_XON2&t;5&t;/* I/O: Xon character 2 */
DECL|macro|UART_XOFF1
mdefine_line|#define UART_XOFF1&t;6&t;/* I/O: Xoff character 1 */
DECL|macro|UART_XOFF2
mdefine_line|#define UART_XOFF2&t;7&t;/* I/O: Xoff character 2 */
multiline_comment|/*&n; * EFR[4]=1 MCR[6]=1, TI16C752&n; */
DECL|macro|UART_TI752_TCR
mdefine_line|#define UART_TI752_TCR&t;6&t;/* I/O: transmission control register */
DECL|macro|UART_TI752_TLR
mdefine_line|#define UART_TI752_TLR&t;7&t;/* I/O: trigger level register */
multiline_comment|/*&n; * LCR=0xBF, XR16C85x&n; */
DECL|macro|UART_TRG
mdefine_line|#define UART_TRG&t;0&t;/* FCTR bit 7 selects Rx or Tx&n;&t;&t;&t;&t; * In: Fifo count&n;&t;&t;&t;&t; * Out: Fifo custom trigger levels */
multiline_comment|/*&n; * These are the definitions for the Programmable Trigger Register&n; */
DECL|macro|UART_TRG_1
mdefine_line|#define UART_TRG_1&t;&t;0x01
DECL|macro|UART_TRG_4
mdefine_line|#define UART_TRG_4&t;&t;0x04
DECL|macro|UART_TRG_8
mdefine_line|#define UART_TRG_8&t;&t;0x08
DECL|macro|UART_TRG_16
mdefine_line|#define UART_TRG_16&t;&t;0x10
DECL|macro|UART_TRG_32
mdefine_line|#define UART_TRG_32&t;&t;0x20
DECL|macro|UART_TRG_64
mdefine_line|#define UART_TRG_64&t;&t;0x40
DECL|macro|UART_TRG_96
mdefine_line|#define UART_TRG_96&t;&t;0x60
DECL|macro|UART_TRG_120
mdefine_line|#define UART_TRG_120&t;&t;0x78
DECL|macro|UART_TRG_128
mdefine_line|#define UART_TRG_128&t;&t;0x80
DECL|macro|UART_FCTR
mdefine_line|#define UART_FCTR&t;1&t;/* Feature Control Register */
DECL|macro|UART_FCTR_RTS_NODELAY
mdefine_line|#define UART_FCTR_RTS_NODELAY&t;0x00  /* RTS flow control delay */
DECL|macro|UART_FCTR_RTS_4DELAY
mdefine_line|#define UART_FCTR_RTS_4DELAY&t;0x01
DECL|macro|UART_FCTR_RTS_6DELAY
mdefine_line|#define UART_FCTR_RTS_6DELAY&t;0x02
DECL|macro|UART_FCTR_RTS_8DELAY
mdefine_line|#define UART_FCTR_RTS_8DELAY&t;0x03
DECL|macro|UART_FCTR_IRDA
mdefine_line|#define UART_FCTR_IRDA&t;&t;0x04  /* IrDa data encode select */
DECL|macro|UART_FCTR_TX_INT
mdefine_line|#define UART_FCTR_TX_INT&t;0x08  /* Tx interrupt type select */
DECL|macro|UART_FCTR_TRGA
mdefine_line|#define UART_FCTR_TRGA&t;&t;0x00  /* Tx/Rx 550 trigger table select */
DECL|macro|UART_FCTR_TRGB
mdefine_line|#define UART_FCTR_TRGB&t;&t;0x10  /* Tx/Rx 650 trigger table select */
DECL|macro|UART_FCTR_TRGC
mdefine_line|#define UART_FCTR_TRGC&t;&t;0x20  /* Tx/Rx 654 trigger table select */
DECL|macro|UART_FCTR_TRGD
mdefine_line|#define UART_FCTR_TRGD&t;&t;0x30  /* Tx/Rx 850 programmable trigger select */
DECL|macro|UART_FCTR_SCR_SWAP
mdefine_line|#define UART_FCTR_SCR_SWAP&t;0x40  /* Scratch pad register swap */
DECL|macro|UART_FCTR_RX
mdefine_line|#define UART_FCTR_RX&t;&t;0x00  /* Programmable trigger mode select */
DECL|macro|UART_FCTR_TX
mdefine_line|#define UART_FCTR_TX&t;&t;0x80  /* Programmable trigger mode select */
multiline_comment|/*&n; * LCR=0xBF, FCTR[6]=1&n; */
DECL|macro|UART_EMSR
mdefine_line|#define UART_EMSR&t;7&t;/* Extended Mode Select Register */
DECL|macro|UART_EMSR_FIFO_COUNT
mdefine_line|#define UART_EMSR_FIFO_COUNT&t;0x01  /* Rx/Tx select */
DECL|macro|UART_EMSR_ALT_COUNT
mdefine_line|#define UART_EMSR_ALT_COUNT&t;0x02  /* Alternating count select */
multiline_comment|/*&n; * The Intel XScale on-chip UARTs define these bits&n; */
DECL|macro|UART_IER_DMAE
mdefine_line|#define UART_IER_DMAE&t;0x80&t;/* DMA Requests Enable */
DECL|macro|UART_IER_UUE
mdefine_line|#define UART_IER_UUE&t;0x40&t;/* UART Unit Enable */
DECL|macro|UART_IER_NRZE
mdefine_line|#define UART_IER_NRZE&t;0x20&t;/* NRZ coding Enable */
DECL|macro|UART_IER_RTOIE
mdefine_line|#define UART_IER_RTOIE&t;0x10&t;/* Receiver Time Out Interrupt Enable */
DECL|macro|UART_IIR_TOD
mdefine_line|#define UART_IIR_TOD&t;0x08&t;/* Character Timeout Indication Detected */
DECL|macro|UART_FCR_PXAR1
mdefine_line|#define UART_FCR_PXAR1&t;0x00&t;/* receive FIFO treshold = 1 */
DECL|macro|UART_FCR_PXAR8
mdefine_line|#define UART_FCR_PXAR8&t;0x40&t;/* receive FIFO treshold = 8 */
DECL|macro|UART_FCR_PXAR16
mdefine_line|#define UART_FCR_PXAR16&t;0x80&t;/* receive FIFO treshold = 16 */
DECL|macro|UART_FCR_PXAR32
mdefine_line|#define UART_FCR_PXAR32&t;0xc0&t;/* receive FIFO treshold = 32 */
multiline_comment|/*&n; * These register definitions are for the 16C950&n; */
DECL|macro|UART_ASR
mdefine_line|#define UART_ASR&t;0x01&t;/* Additional Status Register */
DECL|macro|UART_RFL
mdefine_line|#define UART_RFL&t;0x03&t;/* Receiver FIFO level */
DECL|macro|UART_TFL
mdefine_line|#define UART_TFL &t;0x04&t;/* Transmitter FIFO level */
DECL|macro|UART_ICR
mdefine_line|#define UART_ICR&t;0x05&t;/* Index Control Register */
multiline_comment|/* The 16950 ICR registers */
DECL|macro|UART_ACR
mdefine_line|#define UART_ACR&t;0x00&t;/* Additional Control Register */
DECL|macro|UART_CPR
mdefine_line|#define UART_CPR&t;0x01&t;/* Clock Prescalar Register */
DECL|macro|UART_TCR
mdefine_line|#define UART_TCR&t;0x02&t;/* Times Clock Register */
DECL|macro|UART_CKS
mdefine_line|#define UART_CKS&t;0x03&t;/* Clock Select Register */
DECL|macro|UART_TTL
mdefine_line|#define UART_TTL&t;0x04&t;/* Transmitter Interrupt Trigger Level */
DECL|macro|UART_RTL
mdefine_line|#define UART_RTL&t;0x05&t;/* Receiver Interrupt Trigger Level */
DECL|macro|UART_FCL
mdefine_line|#define UART_FCL&t;0x06&t;/* Flow Control Level Lower */
DECL|macro|UART_FCH
mdefine_line|#define UART_FCH&t;0x07&t;/* Flow Control Level Higher */
DECL|macro|UART_ID1
mdefine_line|#define UART_ID1&t;0x08&t;/* ID #1 */
DECL|macro|UART_ID2
mdefine_line|#define UART_ID2&t;0x09&t;/* ID #2 */
DECL|macro|UART_ID3
mdefine_line|#define UART_ID3&t;0x0A&t;/* ID #3 */
DECL|macro|UART_REV
mdefine_line|#define UART_REV&t;0x0B&t;/* Revision */
DECL|macro|UART_CSR
mdefine_line|#define UART_CSR&t;0x0C&t;/* Channel Software Reset */
DECL|macro|UART_NMR
mdefine_line|#define UART_NMR&t;0x0D&t;/* Nine-bit Mode Register */
DECL|macro|UART_CTR
mdefine_line|#define UART_CTR&t;0xFF
multiline_comment|/*&n; * The 16C950 Additional Control Reigster&n; */
DECL|macro|UART_ACR_RXDIS
mdefine_line|#define UART_ACR_RXDIS&t;0x01&t;/* Receiver disable */
DECL|macro|UART_ACR_TXDIS
mdefine_line|#define UART_ACR_TXDIS&t;0x02&t;/* Receiver disable */
DECL|macro|UART_ACR_DSRFC
mdefine_line|#define UART_ACR_DSRFC&t;0x04&t;/* DSR Flow Control */
DECL|macro|UART_ACR_TLENB
mdefine_line|#define UART_ACR_TLENB&t;0x20&t;/* 950 trigger levels enable */
DECL|macro|UART_ACR_ICRRD
mdefine_line|#define UART_ACR_ICRRD&t;0x40&t;/* ICR Read enable */
DECL|macro|UART_ACR_ASREN
mdefine_line|#define UART_ACR_ASREN&t;0x80&t;/* Additional status enable */
multiline_comment|/*&n; * These definitions are for the RSA-DV II/S card, from&n; *&n; * Kiyokazu SUTO &lt;suto@ks-and-ks.ne.jp&gt;&n; */
DECL|macro|UART_RSA_BASE
mdefine_line|#define UART_RSA_BASE (-8)
DECL|macro|UART_RSA_MSR
mdefine_line|#define UART_RSA_MSR ((UART_RSA_BASE) + 0) /* I/O: Mode Select Register */
DECL|macro|UART_RSA_MSR_SWAP
mdefine_line|#define UART_RSA_MSR_SWAP (1 &lt;&lt; 0) /* Swap low/high 8 bytes in I/O port addr */
DECL|macro|UART_RSA_MSR_FIFO
mdefine_line|#define UART_RSA_MSR_FIFO (1 &lt;&lt; 2) /* Enable the external FIFO */
DECL|macro|UART_RSA_MSR_FLOW
mdefine_line|#define UART_RSA_MSR_FLOW (1 &lt;&lt; 3) /* Enable the auto RTS/CTS flow control */
DECL|macro|UART_RSA_MSR_ITYP
mdefine_line|#define UART_RSA_MSR_ITYP (1 &lt;&lt; 4) /* Level (1) / Edge triger (0) */
DECL|macro|UART_RSA_IER
mdefine_line|#define UART_RSA_IER ((UART_RSA_BASE) + 1) /* I/O: Interrupt Enable Register */
DECL|macro|UART_RSA_IER_Rx_FIFO_H
mdefine_line|#define UART_RSA_IER_Rx_FIFO_H (1 &lt;&lt; 0) /* Enable Rx FIFO half full int. */
DECL|macro|UART_RSA_IER_Tx_FIFO_H
mdefine_line|#define UART_RSA_IER_Tx_FIFO_H (1 &lt;&lt; 1) /* Enable Tx FIFO half full int. */
DECL|macro|UART_RSA_IER_Tx_FIFO_E
mdefine_line|#define UART_RSA_IER_Tx_FIFO_E (1 &lt;&lt; 2) /* Enable Tx FIFO empty int. */
DECL|macro|UART_RSA_IER_Rx_TOUT
mdefine_line|#define UART_RSA_IER_Rx_TOUT (1 &lt;&lt; 3) /* Enable char receive timeout int */
DECL|macro|UART_RSA_IER_TIMER
mdefine_line|#define UART_RSA_IER_TIMER (1 &lt;&lt; 4) /* Enable timer interrupt */
DECL|macro|UART_RSA_SRR
mdefine_line|#define UART_RSA_SRR ((UART_RSA_BASE) + 2) /* IN: Status Read Register */
DECL|macro|UART_RSA_SRR_Tx_FIFO_NEMP
mdefine_line|#define UART_RSA_SRR_Tx_FIFO_NEMP (1 &lt;&lt; 0) /* Tx FIFO is not empty (1) */
DECL|macro|UART_RSA_SRR_Tx_FIFO_NHFL
mdefine_line|#define UART_RSA_SRR_Tx_FIFO_NHFL (1 &lt;&lt; 1) /* Tx FIFO is not half full (1) */
DECL|macro|UART_RSA_SRR_Tx_FIFO_NFUL
mdefine_line|#define UART_RSA_SRR_Tx_FIFO_NFUL (1 &lt;&lt; 2) /* Tx FIFO is not full (1) */
DECL|macro|UART_RSA_SRR_Rx_FIFO_NEMP
mdefine_line|#define UART_RSA_SRR_Rx_FIFO_NEMP (1 &lt;&lt; 3) /* Rx FIFO is not empty (1) */
DECL|macro|UART_RSA_SRR_Rx_FIFO_NHFL
mdefine_line|#define UART_RSA_SRR_Rx_FIFO_NHFL (1 &lt;&lt; 4) /* Rx FIFO is not half full (1) */
DECL|macro|UART_RSA_SRR_Rx_FIFO_NFUL
mdefine_line|#define UART_RSA_SRR_Rx_FIFO_NFUL (1 &lt;&lt; 5) /* Rx FIFO is not full (1) */
DECL|macro|UART_RSA_SRR_Rx_TOUT
mdefine_line|#define UART_RSA_SRR_Rx_TOUT (1 &lt;&lt; 6) /* Character reception timeout occurred (1) */
DECL|macro|UART_RSA_SRR_TIMER
mdefine_line|#define UART_RSA_SRR_TIMER (1 &lt;&lt; 7) /* Timer interrupt occurred */
DECL|macro|UART_RSA_FRR
mdefine_line|#define UART_RSA_FRR ((UART_RSA_BASE) + 2) /* OUT: FIFO Reset Register */
DECL|macro|UART_RSA_TIVSR
mdefine_line|#define UART_RSA_TIVSR ((UART_RSA_BASE) + 3) /* I/O: Timer Interval Value Set Register */
DECL|macro|UART_RSA_TCR
mdefine_line|#define UART_RSA_TCR ((UART_RSA_BASE) + 4) /* OUT: Timer Control Register */
DECL|macro|UART_RSA_TCR_SWITCH
mdefine_line|#define UART_RSA_TCR_SWITCH (1 &lt;&lt; 0) /* Timer on */
multiline_comment|/*&n; * The RSA DSV/II board has two fixed clock frequencies.  One is the&n; * standard rate, and the other is 8 times faster.&n; */
DECL|macro|SERIAL_RSA_BAUD_BASE
mdefine_line|#define SERIAL_RSA_BAUD_BASE (921600)
DECL|macro|SERIAL_RSA_BAUD_BASE_LO
mdefine_line|#define SERIAL_RSA_BAUD_BASE_LO (SERIAL_RSA_BAUD_BASE / 8)
multiline_comment|/*&n; * Extra serial register definitions for the internal UARTs&n; * in TI OMAP processors.&n; */
DECL|macro|UART_OMAP_MDR1
mdefine_line|#define UART_OMAP_MDR1&t;&t;0x08&t;/* Mode definition register */
DECL|macro|UART_OMAP_MDR2
mdefine_line|#define UART_OMAP_MDR2&t;&t;0x09&t;/* Mode definition register 2 */
DECL|macro|UART_OMAP_SCR
mdefine_line|#define UART_OMAP_SCR&t;&t;0x10&t;/* Supplementary control register */
DECL|macro|UART_OMAP_SSR
mdefine_line|#define UART_OMAP_SSR&t;&t;0x11&t;/* Supplementary status register */
DECL|macro|UART_OMAP_EBLR
mdefine_line|#define UART_OMAP_EBLR&t;&t;0x12&t;/* BOF length register */
DECL|macro|UART_OMAP_OSC_12M_SEL
mdefine_line|#define UART_OMAP_OSC_12M_SEL&t;0x13&t;/* OMAP1510 12MHz osc select */
DECL|macro|UART_OMAP_MVER
mdefine_line|#define UART_OMAP_MVER&t;&t;0x14&t;/* Module version register */
DECL|macro|UART_OMAP_SYSC
mdefine_line|#define UART_OMAP_SYSC&t;&t;0x15&t;/* System configuration register */
DECL|macro|UART_OMAP_SYSS
mdefine_line|#define UART_OMAP_SYSS&t;&t;0x16&t;/* System status register */
macro_line|#endif /* _LINUX_SERIAL_REG_H */
eof
