multiline_comment|/*&n; * include/linux/serial_reg.h&n; *&n; * Copyright (C) 1992, 1994 by Theodore Ts&squot;o.&n; * &n; * Redistribution of this file is permitted under the terms of the GNU &n; * Public License (GPL)&n; * &n; * These are the UART port assignments, expressed as offsets from the base&n; * register.  These assignments should hold for any serial port based on&n; * a 8250, 16450, or 16550(A).&n; */
macro_line|#ifndef _LINUX_SERIAL_REG_H
DECL|macro|_LINUX_SERIAL_REG_H
mdefine_line|#define _LINUX_SERIAL_REG_H
DECL|macro|UART_RX
mdefine_line|#define UART_RX&t;&t;0&t;/* In:  Receive buffer (DLAB=0) */
DECL|macro|UART_TX
mdefine_line|#define UART_TX&t;&t;0&t;/* Out: Transmit buffer (DLAB=0) */
DECL|macro|UART_DLL
mdefine_line|#define UART_DLL&t;0&t;/* Out: Divisor Latch Low (DLAB=1) */
DECL|macro|UART_TRG
mdefine_line|#define UART_TRG&t;0&t;/* (LCR=BF) FCTR bit 7 selects Rx or Tx&n;&t;&t;&t;&t; * In: Fifo count&n;&t;&t;&t;&t; * Out: Fifo custom trigger levels&n;&t;&t;&t;&t; * XR16C85x only */
DECL|macro|UART_DLM
mdefine_line|#define UART_DLM&t;1&t;/* Out: Divisor Latch High (DLAB=1) */
DECL|macro|UART_IER
mdefine_line|#define UART_IER&t;1&t;/* Out: Interrupt Enable Register */
DECL|macro|UART_FCTR
mdefine_line|#define UART_FCTR&t;1&t;/* (LCR=BF) Feature Control Register&n;&t;&t;&t;&t; * XR16C85x only */
DECL|macro|UART_IIR
mdefine_line|#define UART_IIR&t;2&t;/* In:  Interrupt ID Register */
DECL|macro|UART_FCR
mdefine_line|#define UART_FCR&t;2&t;/* Out: FIFO Control Register */
DECL|macro|UART_EFR
mdefine_line|#define UART_EFR&t;2&t;/* I/O: Extended Features Register */
multiline_comment|/* (DLAB=1, 16C660 only) */
DECL|macro|UART_LCR
mdefine_line|#define UART_LCR&t;3&t;/* Out: Line Control Register */
DECL|macro|UART_MCR
mdefine_line|#define UART_MCR&t;4&t;/* Out: Modem Control Register */
DECL|macro|UART_LSR
mdefine_line|#define UART_LSR&t;5&t;/* In:  Line Status Register */
DECL|macro|UART_MSR
mdefine_line|#define UART_MSR&t;6&t;/* In:  Modem Status Register */
DECL|macro|UART_SCR
mdefine_line|#define UART_SCR&t;7&t;/* I/O: Scratch Register */
DECL|macro|UART_EMSR
mdefine_line|#define UART_EMSR&t;7&t;/* (LCR=BF) Extended Mode Select Register &n;&t;&t;&t;&t; * FCTR bit 6 selects SCR or EMSR&n;&t;&t;&t;&t; * XR16c85x only */
multiline_comment|/*&n; * These are the definitions for the FIFO Control Register&n; * (16650 only)&n; */
DECL|macro|UART_FCR_ENABLE_FIFO
mdefine_line|#define UART_FCR_ENABLE_FIFO&t;0x01 /* Enable the FIFO */
DECL|macro|UART_FCR_CLEAR_RCVR
mdefine_line|#define UART_FCR_CLEAR_RCVR&t;0x02 /* Clear the RCVR FIFO */
DECL|macro|UART_FCR_CLEAR_XMIT
mdefine_line|#define UART_FCR_CLEAR_XMIT&t;0x04 /* Clear the XMIT FIFO */
DECL|macro|UART_FCR_DMA_SELECT
mdefine_line|#define UART_FCR_DMA_SELECT&t;0x08 /* For DMA applications */
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
multiline_comment|/* 16650 redefinitions */
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
multiline_comment|/* TI 16750 definitions */
DECL|macro|UART_FCR7_64BYTE
mdefine_line|#define UART_FCR7_64BYTE&t;0x20 /* Go into 64 byte mode */
multiline_comment|/*&n; * These are the definitions for the Line Control Register&n; * &n; * Note: if the word length is 5 bits (UART_LCR_WLEN5), then setting &n; * UART_LCR_STOP will select 1.5 stop bits, not 2 stop bits.&n; */
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
mdefine_line|#define UART_LSR_TEMT&t;0x40&t;/* Transmitter empty */
DECL|macro|UART_LSR_THRE
mdefine_line|#define UART_LSR_THRE&t;0x20&t;/* Transmit-hold-register empty */
DECL|macro|UART_LSR_BI
mdefine_line|#define UART_LSR_BI&t;0x10&t;/* Break interrupt indicator */
DECL|macro|UART_LSR_FE
mdefine_line|#define UART_LSR_FE&t;0x08&t;/* Frame error indicator */
DECL|macro|UART_LSR_PE
mdefine_line|#define UART_LSR_PE&t;0x04&t;/* Parity error indicator */
DECL|macro|UART_LSR_OE
mdefine_line|#define UART_LSR_OE&t;0x02&t;/* Overrun error indicator */
DECL|macro|UART_LSR_DR
mdefine_line|#define UART_LSR_DR&t;0x01&t;/* Receiver data ready */
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
mdefine_line|#define UART_IER_MSI&t;0x08&t;/* Enable Modem status interrupt */
DECL|macro|UART_IER_RLSI
mdefine_line|#define UART_IER_RLSI&t;0x04&t;/* Enable receiver line status interrupt */
DECL|macro|UART_IER_THRI
mdefine_line|#define UART_IER_THRI&t;0x02&t;/* Enable Transmitter holding register int. */
DECL|macro|UART_IER_RDI
mdefine_line|#define UART_IER_RDI&t;0x01&t;/* Enable receiver data interrupt */
multiline_comment|/*&n; * Sleep mode for ST16650 and TI16750.&n; * Note that for 16650, EFR-bit 4 must be selected as well.&n; */
DECL|macro|UART_IERX_SLEEP
mdefine_line|#define UART_IERX_SLEEP  0x10&t;/* Enable sleep mode */
multiline_comment|/*&n; * These are the definitions for the Modem Control Register&n; */
DECL|macro|UART_MCR_LOOP
mdefine_line|#define UART_MCR_LOOP&t;0x10&t;/* Enable loopback test mode */
DECL|macro|UART_MCR_OUT2
mdefine_line|#define UART_MCR_OUT2&t;0x08&t;/* Out2 complement */
DECL|macro|UART_MCR_OUT1
mdefine_line|#define UART_MCR_OUT1&t;0x04&t;/* Out1 complement */
DECL|macro|UART_MCR_RTS
mdefine_line|#define UART_MCR_RTS&t;0x02&t;/* RTS complement */
DECL|macro|UART_MCR_DTR
mdefine_line|#define UART_MCR_DTR&t;0x01&t;/* DTR complement */
multiline_comment|/*&n; * These are the definitions for the Modem Status Register&n; */
DECL|macro|UART_MSR_DCD
mdefine_line|#define UART_MSR_DCD&t;0x80&t;/* Data Carrier Detect */
DECL|macro|UART_MSR_RI
mdefine_line|#define UART_MSR_RI&t;0x40&t;/* Ring Indicator */
DECL|macro|UART_MSR_DSR
mdefine_line|#define UART_MSR_DSR&t;0x20&t;/* Data Set Ready */
DECL|macro|UART_MSR_CTS
mdefine_line|#define UART_MSR_CTS&t;0x10&t;/* Clear to Send */
DECL|macro|UART_MSR_DDCD
mdefine_line|#define UART_MSR_DDCD&t;0x08&t;/* Delta DCD */
DECL|macro|UART_MSR_TERI
mdefine_line|#define UART_MSR_TERI&t;0x04&t;/* Trailing edge ring indicator */
DECL|macro|UART_MSR_DDSR
mdefine_line|#define UART_MSR_DDSR&t;0x02&t;/* Delta DSR */
DECL|macro|UART_MSR_DCTS
mdefine_line|#define UART_MSR_DCTS&t;0x01&t;/* Delta CTS */
DECL|macro|UART_MSR_ANY_DELTA
mdefine_line|#define UART_MSR_ANY_DELTA 0x0F&t;/* Any of the delta bits! */
multiline_comment|/*&n; * These are the definitions for the Extended Features Register&n; * (StarTech 16C660 only, when DLAB=1)&n; */
DECL|macro|UART_EFR_CTS
mdefine_line|#define UART_EFR_CTS&t;0x80&t;/* CTS flow control */
DECL|macro|UART_EFR_RTS
mdefine_line|#define UART_EFR_RTS&t;0x40&t;/* RTS flow control */
DECL|macro|UART_EFR_SCD
mdefine_line|#define UART_EFR_SCD&t;0x20&t;/* Special character detect */
DECL|macro|UART_EFR_ECB
mdefine_line|#define UART_EFR_ECB&t;0x10&t;/* Enhanced control bit */
multiline_comment|/*&n; * the low four bits control software flow control&n; */
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
multiline_comment|/*&n; * These are the definitions for the Feature Control Register&n; * (XR16C85x only, when LCR=bf; doubles with the Interrupt Enable&n; * Register, UART register #1)&n; */
DECL|macro|UART_FCTR_RTS_NODELAY
mdefine_line|#define UART_FCTR_RTS_NODELAY&t;0x00  /* RTS flow control delay */
DECL|macro|UART_FCTR_RTS_4DELAY
mdefine_line|#define UART_FCTR_RTS_4DELAY&t;0x01
DECL|macro|UART_FCTR_RTS_6DELAY
mdefine_line|#define UART_FCTR_RTS_6DELAY&t;0x02
DECL|macro|UART_FCTR_RTS_8DELAY
mdefine_line|#define UART_FCTR_RTS_8DELAY&t;0x03
DECL|macro|UART_FCTR_IRDA
mdefine_line|#define UART_FCTR_IRDA&t;0x04  /* IrDa data encode select */
DECL|macro|UART_FCTR_TX_INT
mdefine_line|#define UART_FCTR_TX_INT&t;0x08  /* Tx interrupt type select */
DECL|macro|UART_FCTR_TRGA
mdefine_line|#define UART_FCTR_TRGA&t;0x00  /* Tx/Rx 550 trigger table select */
DECL|macro|UART_FCTR_TRGB
mdefine_line|#define UART_FCTR_TRGB&t;0x10  /* Tx/Rx 650 trigger table select */
DECL|macro|UART_FCTR_TRGC
mdefine_line|#define UART_FCTR_TRGC&t;0x20  /* Tx/Rx 654 trigger table select */
DECL|macro|UART_FCTR_TRGD
mdefine_line|#define UART_FCTR_TRGD&t;0x30  /* Tx/Rx 850 programmable trigger select */
DECL|macro|UART_FCTR_SCR_SWAP
mdefine_line|#define UART_FCTR_SCR_SWAP&t;0x40  /* Scratch pad register swap */
DECL|macro|UART_FCTR_RX
mdefine_line|#define UART_FCTR_RX&t;0x00  /* Programmable trigger mode select */
DECL|macro|UART_FCTR_TX
mdefine_line|#define UART_FCTR_TX&t;0x80  /* Programmable trigger mode select */
multiline_comment|/*&n; * These are the definitions for the Enhanced Mode Select Register&n; * (XR16C85x only, when LCR=bf and FCTR bit 6=1; doubles with the&n; * Scratch register, UART register #7)&n; */
DECL|macro|UART_EMSR_FIFO_COUNT
mdefine_line|#define UART_EMSR_FIFO_COUNT&t;0x01  /* Rx/Tx select */
DECL|macro|UART_EMSR_ALT_COUNT
mdefine_line|#define UART_EMSR_ALT_COUNT&t;0x02  /* Alternating count select */
multiline_comment|/*&n; * These are the definitions for the Programmable Trigger&n; * Register (XR16C85x only, when LCR=bf; doubles with the UART RX/TX&n; * register, UART register #0)&n; */
DECL|macro|UART_TRG_1
mdefine_line|#define UART_TRG_1&t;0x01
DECL|macro|UART_TRG_4
mdefine_line|#define UART_TRG_4&t;0x04
DECL|macro|UART_TRG_8
mdefine_line|#define UART_TRG_8&t;0x08
DECL|macro|UART_TRG_16
mdefine_line|#define UART_TRG_16&t;0x10
DECL|macro|UART_TRG_32
mdefine_line|#define UART_TRG_32&t;0x20
DECL|macro|UART_TRG_64
mdefine_line|#define UART_TRG_64&t;0x40
DECL|macro|UART_TRG_96
mdefine_line|#define UART_TRG_96&t;0x60
DECL|macro|UART_TRG_120
mdefine_line|#define UART_TRG_120&t;0x78
DECL|macro|UART_TRG_128
mdefine_line|#define UART_TRG_128&t;0x80
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
mdefine_line|#define UART_RSA_SRR_Rx_TOUT (1 &lt;&lt; 6) /* Character reception timeout occured (1) */
DECL|macro|UART_RSA_SRR_TIMER
mdefine_line|#define UART_RSA_SRR_TIMER (1 &lt;&lt; 7) /* Timer interrupt occured */
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
macro_line|#endif /* _LINUX_SERIAL_REG_H */
eof
