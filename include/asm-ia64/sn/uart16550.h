multiline_comment|/*&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1992 - 1997, 2000-2001 Silicon Graphics, Inc. All rights reserved.&n; */
macro_line|#ifndef _ASM_IA64_SN_UART16550_H
DECL|macro|_ASM_IA64_SN_UART16550_H
mdefine_line|#define _ASM_IA64_SN_UART16550_H
multiline_comment|/*&n; * Definitions for 16550  chip&n; */
multiline_comment|/* defined as offsets from the data register */
DECL|macro|REG_DAT
mdefine_line|#define REG_DAT     0   /* receive/transmit data */
DECL|macro|REG_ICR
mdefine_line|#define REG_ICR     1   /* interrupt control register */
DECL|macro|REG_ISR
mdefine_line|#define REG_ISR     2   /* interrupt status register */
DECL|macro|REG_FCR
mdefine_line|#define REG_FCR     2   /* fifo control register */
DECL|macro|REG_LCR
mdefine_line|#define REG_LCR     3   /* line control register */
DECL|macro|REG_MCR
mdefine_line|#define REG_MCR     4   /* modem control register */
DECL|macro|REG_LSR
mdefine_line|#define REG_LSR     5   /* line status register */
DECL|macro|REG_MSR
mdefine_line|#define REG_MSR     6   /* modem status register */
DECL|macro|REG_SCR
mdefine_line|#define REG_SCR     7   /* Scratch register      */
DECL|macro|REG_DLL
mdefine_line|#define REG_DLL     0   /* divisor latch (lsb) */
DECL|macro|REG_DLH
mdefine_line|#define REG_DLH     1   /* divisor latch (msb) */
DECL|macro|REG_EFR
mdefine_line|#define REG_EFR&t;&t;2&t;/* 16650 enhanced feature register */
multiline_comment|/*&n; * 16450/16550 Registers Structure.&n; */
multiline_comment|/* Line Control Register */
DECL|macro|LCR_WLS0
mdefine_line|#define&t;&t;LCR_WLS0&t;0x01&t;/*word length select bit 0 */&t;
DECL|macro|LCR_WLS1
mdefine_line|#define&t;&t;LCR_WLS1&t;0x02&t;/*word length select bit 2 */&t;
DECL|macro|LCR_STB
mdefine_line|#define&t;&t;LCR_STB&t;0x04&t;&t;/* number of stop bits */
DECL|macro|LCR_PEN
mdefine_line|#define&t;&t;LCR_PEN&t;0x08&t;&t;/* parity enable */
DECL|macro|LCR_EPS
mdefine_line|#define&t;&t;LCR_EPS&t;0x10&t;&t;/* even parity select */
DECL|macro|LCR_SETBREAK
mdefine_line|#define&t;&t;LCR_SETBREAK 0x40&t;/* break key */
DECL|macro|LCR_DLAB
mdefine_line|#define&t;&t;LCR_DLAB&t;0x80&t;/* divisor latch access bit */
DECL|macro|LCR_RXLEN
mdefine_line|#define &t;LCR_RXLEN   0x03    /* # of data bits per received/xmitted char */
DECL|macro|LCR_STOP1
mdefine_line|#define &t;LCR_STOP1   0x00
DECL|macro|LCR_STOP2
mdefine_line|#define &t;LCR_STOP2   0x04
DECL|macro|LCR_PAREN
mdefine_line|#define &t;LCR_PAREN   0x08
DECL|macro|LCR_PAREVN
mdefine_line|#define &t;LCR_PAREVN  0x10
DECL|macro|LCR_PARMARK
mdefine_line|#define &t;LCR_PARMARK 0x20
DECL|macro|LCR_SNDBRK
mdefine_line|#define &t;LCR_SNDBRK  0x40
DECL|macro|LCR_DLAB
mdefine_line|#define &t;LCR_DLAB    0x80
DECL|macro|LCR_BITS5
mdefine_line|#define&t;&t;LCR_BITS5&t;0x00&t;/* 5 bits per char */
DECL|macro|LCR_BITS6
mdefine_line|#define&t;&t;LCR_BITS6&t;0x01&t;/* 6 bits per char */
DECL|macro|LCR_BITS7
mdefine_line|#define&t;&t;LCR_BITS7&t;0x02&t;/* 7 bits per char */
DECL|macro|LCR_BITS8
mdefine_line|#define&t;&t;LCR_BITS8&t;0x03&t;/* 8 bits per char */
DECL|macro|LCR_MASK_BITS_CHAR
mdefine_line|#define&t;&t;LCR_MASK_BITS_CHAR &t;&t;0x03
DECL|macro|LCR_MASK_STOP_BITS
mdefine_line|#define &t;LCR_MASK_STOP_BITS&t;&t;0x04
DECL|macro|LCR_MASK_PARITY_BITS
mdefine_line|#define&t;&t;LCR_MASK_PARITY_BITS&t;0x18
multiline_comment|/* Line Status Register */
DECL|macro|LSR_RCA
mdefine_line|#define&t;&t;LSR_RCA&t;0x01&t;&t;/* data ready */
DECL|macro|LSR_OVRRUN
mdefine_line|#define&t;&t;LSR_OVRRUN&t;0x02&t;/* overrun error */
DECL|macro|LSR_PARERR
mdefine_line|#define&t;&t;LSR_PARERR&t;0x04&t;/* parity error */
DECL|macro|LSR_FRMERR
mdefine_line|#define&t;&t;LSR_FRMERR&t;0x08&t;/* framing error */
DECL|macro|LSR_BRKDET
mdefine_line|#define&t;&t;LSR_BRKDET &t;0x10&t;/* a break has arrived */
DECL|macro|LSR_XHRE
mdefine_line|#define&t;&t;LSR_XHRE&t;0x20&t;/* tx hold reg is now empty */
DECL|macro|LSR_XSRE
mdefine_line|#define&t;&t;LSR_XSRE&t;0x40&t;/* tx shift reg is now empty */
DECL|macro|LSR_RFBE
mdefine_line|#define&t;&t;LSR_RFBE&t;0x80&t;/* rx FIFO Buffer error */
multiline_comment|/* Interrupt Status Regisger */
DECL|macro|ISR_MSTATUS
mdefine_line|#define&t;&t;ISR_MSTATUS&t;0x00
DECL|macro|ISR_TxRDY
mdefine_line|#define&t;&t;ISR_TxRDY&t;0x02
DECL|macro|ISR_RxRDY
mdefine_line|#define&t;&t;ISR_RxRDY&t;0x04
DECL|macro|ISR_ERROR_INTR
mdefine_line|#define&t;&t;ISR_ERROR_INTR&t;0x08
DECL|macro|ISR_FFTMOUT
mdefine_line|#define&t;&t;ISR_FFTMOUT 0x0c&t;/* FIFO Timeout */
DECL|macro|ISR_RSTATUS
mdefine_line|#define&t;&t;ISR_RSTATUS 0x06&t;/* Receiver Line status */
multiline_comment|/* Interrupt Enable Register */
DECL|macro|ICR_RIEN
mdefine_line|#define&t;&t;ICR_RIEN&t;0x01&t;/* Received Data Ready */
DECL|macro|ICR_TIEN
mdefine_line|#define&t;&t;ICR_TIEN&t;0x02&t;/* Tx Hold Register Empty */
DECL|macro|ICR_SIEN
mdefine_line|#define&t;&t;ICR_SIEN&t;0x04&t;/* Receiver Line Status */
DECL|macro|ICR_MIEN
mdefine_line|#define&t;&t;ICR_MIEN&t;0x08&t;/* Modem Status */
multiline_comment|/* Modem Control Register */
DECL|macro|MCR_DTR
mdefine_line|#define&t;&t;MCR_DTR&t;&t;0x01&t;/* Data Terminal Ready */
DECL|macro|MCR_RTS
mdefine_line|#define&t;&t;MCR_RTS&t;&t;0x02&t;/* Request To Send */
DECL|macro|MCR_OUT1
mdefine_line|#define&t;&t;MCR_OUT1&t;0x04&t;/* Aux output - not used */
DECL|macro|MCR_OUT2
mdefine_line|#define&t;&t;MCR_OUT2&t;0x08&t;/* turns intr to 386 on/off */&t;
DECL|macro|MCR_LOOP
mdefine_line|#define&t;&t;MCR_LOOP&t;0x10&t;/* loopback for diagnostics */
DECL|macro|MCR_AFE
mdefine_line|#define&t;&t;MCR_AFE &t;0x20&t;/* Auto flow control enable */
multiline_comment|/* Modem Status Register */
DECL|macro|MSR_DCTS
mdefine_line|#define&t;&t;MSR_DCTS&t;0x01&t;/* Delta Clear To Send */
DECL|macro|MSR_DDSR
mdefine_line|#define&t;&t;MSR_DDSR&t;0x02&t;/* Delta Data Set Ready */
DECL|macro|MSR_DRI
mdefine_line|#define&t;&t;MSR_DRI&t;&t;0x04&t;/* Trail Edge Ring Indicator */
DECL|macro|MSR_DDCD
mdefine_line|#define&t;&t;MSR_DDCD&t;0x08&t;/* Delta Data Carrier Detect */
DECL|macro|MSR_CTS
mdefine_line|#define&t;&t;MSR_CTS&t;&t;0x10&t;/* Clear To Send */
DECL|macro|MSR_DSR
mdefine_line|#define&t;&t;MSR_DSR&t;&t;0x20&t;/* Data Set Ready */
DECL|macro|MSR_RI
mdefine_line|#define&t;&t;MSR_RI&t;&t;0x40&t;/* Ring Indicator */
DECL|macro|MSR_DCD
mdefine_line|#define&t;&t;MSR_DCD&t;&t;0x80&t;/* Data Carrier Detect */
DECL|macro|DELTAS
mdefine_line|#define &t;DELTAS(x) &t;((x)&amp;(MSR_DCTS|MSR_DDSR|MSR_DRI|MSR_DDCD))
DECL|macro|STATES
mdefine_line|#define &t;STATES(x) &t;((x)(MSR_CTS|MSR_DSR|MSR_RI|MSR_DCD))
DECL|macro|FCR_FIFOEN
mdefine_line|#define&t;&t;FCR_FIFOEN&t;0x01&t;/* enable receive/transmit fifo */
DECL|macro|FCR_RxFIFO
mdefine_line|#define&t;&t;FCR_RxFIFO&t;0x02&t;/* enable receive fifo */
DECL|macro|FCR_TxFIFO
mdefine_line|#define&t;&t;FCR_TxFIFO&t;0x04&t;/* enable transmit fifo */
DECL|macro|FCR_MODE1
mdefine_line|#define &t;FCR_MODE1&t;0x08&t;/* change to mode 1 */
DECL|macro|RxLVL0
mdefine_line|#define&t;&t;RxLVL0&t;&t;0x00&t;/* Rx fifo level at 1&t;*/
DECL|macro|RxLVL1
mdefine_line|#define&t;&t;RxLVL1&t;&t;0x40&t;/* Rx fifo level at 4 */
DECL|macro|RxLVL2
mdefine_line|#define&t;&t;RxLVL2&t;&t;0x80&t;/* Rx fifo level at 8 */
DECL|macro|RxLVL3
mdefine_line|#define&t;&t;RxLVL3&t;&t;0xc0&t;/* Rx fifo level at 14 */
DECL|macro|FIFOEN
mdefine_line|#define &t;FIFOEN&t;&t;(FCR_FIFOEN | FCR_RxFIFO | FCR_TxFIFO | RxLVL3 | FCR_MODE1) 
DECL|macro|FCT_TxMASK
mdefine_line|#define&t;&t;FCT_TxMASK&t;0x30&t;/* mask for Tx trigger */
DECL|macro|FCT_RxMASK
mdefine_line|#define&t;&t;FCT_RxMASK&t;0xc0&t;/* mask for Rx trigger */
multiline_comment|/* enhanced festures register */
DECL|macro|EFR_SFLOW
mdefine_line|#define&t;&t;EFR_SFLOW&t;0x0f&t;/* various S/w Flow Controls */
DECL|macro|EFR_EIC
mdefine_line|#define &t;EFR_EIC&t;&t;0x10&t;/* Enhanced Interrupt Control bit */
DECL|macro|EFR_SCD
mdefine_line|#define &t;EFR_SCD&t;&t;0x20&t;/* Special Character Detect */
DECL|macro|EFR_RTS
mdefine_line|#define &t;EFR_RTS&t;&t;0x40&t;/* RTS flow control */
DECL|macro|EFR_CTS
mdefine_line|#define &t;EFR_CTS&t;&t;0x80&t;/* CTS flow control */
multiline_comment|/* Rx Tx software flow controls in 16650 enhanced mode */
DECL|macro|SFLOW_Tx0
mdefine_line|#define&t;&t;SFLOW_Tx0&t;0x00&t;/* no Xmit flow control */
DECL|macro|SFLOW_Tx1
mdefine_line|#define&t;&t;SFLOW_Tx1&t;0x08&t;/* Transmit Xon1, Xoff1 */
DECL|macro|SFLOW_Tx2
mdefine_line|#define&t;&t;SFLOW_Tx2&t;0x04&t;/* Transmit Xon2, Xoff2 */
DECL|macro|SFLOW_Tx3
mdefine_line|#define&t;&t;SFLOW_Tx3&t;0x0c&t;/* Transmit Xon1,Xon2, Xoff1,Xoff2 */
DECL|macro|SFLOW_Rx0
mdefine_line|#define&t;&t;SFLOW_Rx0&t;0x00&t;/* no Rcv flow control */
DECL|macro|SFLOW_Rx1
mdefine_line|#define&t;&t;SFLOW_Rx1&t;0x02&t;/* Receiver compares Xon1, Xoff1 */
DECL|macro|SFLOW_Rx2
mdefine_line|#define&t;&t;SFLOW_Rx2&t;0x01&t;/* Receiver compares Xon2, Xoff2 */
DECL|macro|ASSERT_DTR
mdefine_line|#define&t;ASSERT_DTR(x)&t;&t;(x |= MCR_DTR)
DECL|macro|ASSERT_RTS
mdefine_line|#define&t;ASSERT_RTS(x)&t;&t;(x |= MCR_RTS)
DECL|macro|DU_RTS_ASSERTED
mdefine_line|#define DU_RTS_ASSERTED(x)  (((x) &amp; MCR_RTS) != 0)
DECL|macro|DU_RTS_ASSERT
mdefine_line|#define DU_RTS_ASSERT(x)    ((x) |= MCR_RTS)
DECL|macro|DU_RTS_DEASSERT
mdefine_line|#define DU_RTS_DEASSERT(x)  ((x) &amp;= ~MCR_RTS)
multiline_comment|/*&n; * ioctl(fd, I_STR, arg)&n; * use the SIOC_RS422 and SIOC_EXTCLK combination to support MIDI&n; */
DECL|macro|SIOC
mdefine_line|#define SIOC        (&squot;z&squot; &lt;&lt; 8)  /* z for z85130 */
DECL|macro|SIOC_EXTCLK
mdefine_line|#define SIOC_EXTCLK (SIOC | 1)  /* select/de-select external clock */
DECL|macro|SIOC_RS422
mdefine_line|#define SIOC_RS422  (SIOC | 2)  /* select/de-select RS422 protocol */
DECL|macro|SIOC_ITIMER
mdefine_line|#define SIOC_ITIMER (SIOC | 3)  /* upstream timer adjustment */
DECL|macro|SIOC_LOOPBACK
mdefine_line|#define SIOC_LOOPBACK   (SIOC | 4)  /* diagnostic loopback test mode */
multiline_comment|/* channel control register */
DECL|macro|DMA_INT_MASK
mdefine_line|#define&t;DMA_INT_MASK&t;&t;0xe0&t;/* ring intr mask */
DECL|macro|DMA_INT_TH25
mdefine_line|#define DMA_INT_TH25&t;&t;0x20&t;/* 25% threshold */
DECL|macro|DMA_INT_TH50
mdefine_line|#define DMA_INT_TH50&t;&t;0x40&t;/* 50% threshold */
DECL|macro|DMA_INT_TH75
mdefine_line|#define DMA_INT_TH75&t;&t;0x60&t;/* 75% threshold */
DECL|macro|DMA_INT_EMPTY
mdefine_line|#define DMA_INT_EMPTY&t;&t;0x80&t;/* ring buffer empty */
DECL|macro|DMA_INT_NEMPTY
mdefine_line|#define DMA_INT_NEMPTY&t;&t;0xa0&t;/* ring buffer not empty */
DECL|macro|DMA_INT_FULL
mdefine_line|#define DMA_INT_FULL&t;&t;0xc0&t;/* ring buffer full */
DECL|macro|DMA_INT_NFULL
mdefine_line|#define DMA_INT_NFULL&t;&t;0xe0&t;/* ring buffer not full */
DECL|macro|DMA_CHANNEL_RESET
mdefine_line|#define DMA_CHANNEL_RESET&t;0x400&t;/* reset dma channel */
DECL|macro|DMA_ENABLE
mdefine_line|#define DMA_ENABLE&t;&t;&t;0x200&t;/* enable DMA */
multiline_comment|/* peripheral controller intr status bits applicable to serial ports */
DECL|macro|ISA_SERIAL0_MASK
mdefine_line|#define ISA_SERIAL0_MASK &t;&t;0x03f00000&t;/* mask for port #1 intrs */
DECL|macro|ISA_SERIAL0_DIR
mdefine_line|#define ISA_SERIAL0_DIR&t;&t;&t;0x00100000&t;/* device intr request */
DECL|macro|ISA_SERIAL0_Tx_THIR
mdefine_line|#define ISA_SERIAL0_Tx_THIR&t;&t;0x00200000&t;/* Transmit DMA threshold */
DECL|macro|ISA_SERIAL0_Tx_PREQ
mdefine_line|#define ISA_SERIAL0_Tx_PREQ&t;&t;0x00400000&t;/* Transmit DMA pair req */
DECL|macro|ISA_SERIAL0_Tx_MEMERR
mdefine_line|#define ISA_SERIAL0_Tx_MEMERR&t;0x00800000&t;/* Transmit DMA memory err */
DECL|macro|ISA_SERIAL0_Rx_THIR
mdefine_line|#define ISA_SERIAL0_Rx_THIR&t;&t;0x01000000&t;/* Receive DMA threshold  */
DECL|macro|ISA_SERIAL0_Rx_OVERRUN
mdefine_line|#define ISA_SERIAL0_Rx_OVERRUN&t;0x02000000&t;/* Receive DMA over-run  */
DECL|macro|ISA_SERIAL1_MASK
mdefine_line|#define ISA_SERIAL1_MASK &t;&t;0xfc000000&t;/* mask for port #1 intrs */
DECL|macro|ISA_SERIAL1_DIR
mdefine_line|#define ISA_SERIAL1_DIR&t;&t;&t;0x04000000&t;/* device intr request */
DECL|macro|ISA_SERIAL1_Tx_THIR
mdefine_line|#define ISA_SERIAL1_Tx_THIR&t;&t;0x08000000&t;/* Transmit DMA threshold */
DECL|macro|ISA_SERIAL1_Tx_PREQ
mdefine_line|#define ISA_SERIAL1_Tx_PREQ&t;&t;0x10000000&t;/* Transmit DMA pair req */
DECL|macro|ISA_SERIAL1_Tx_MEMERR
mdefine_line|#define ISA_SERIAL1_Tx_MEMERR&t;0x20000000&t;/* Transmit DMA memory err */
DECL|macro|ISA_SERIAL1_Rx_THIR
mdefine_line|#define ISA_SERIAL1_Rx_THIR&t;&t;0x40000000&t;/* Receive DMA threshold  */
DECL|macro|ISA_SERIAL1_Rx_OVERRUN
mdefine_line|#define ISA_SERIAL1_Rx_OVERRUN&t;0x80000000&t;/* Receive DMA over-run  */
DECL|macro|MAX_RING_BLOCKS
mdefine_line|#define MAX_RING_BLOCKS&t;&t;128&t;&t;&t;/* 4096/32 */
DECL|macro|MAX_RING_SIZE
mdefine_line|#define MAX_RING_SIZE&t;&t;4096
multiline_comment|/* DMA Input Control Byte */
DECL|macro|DMA_IC_OVRRUN
mdefine_line|#define&t;DMA_IC_OVRRUN&t;0x01&t;/* overrun error */
DECL|macro|DMA_IC_PARERR
mdefine_line|#define&t;DMA_IC_PARERR&t;0x02&t;/* parity error */
DECL|macro|DMA_IC_FRMERR
mdefine_line|#define&t;DMA_IC_FRMERR&t;0x04&t;/* framing error */
DECL|macro|DMA_IC_BRKDET
mdefine_line|#define&t;DMA_IC_BRKDET &t;0x08&t;/* a break has arrived */
DECL|macro|DMA_IC_VALID
mdefine_line|#define DMA_IC_VALID&t;0x80&t;/* pair is valid */
multiline_comment|/* DMA Output Control Byte */
DECL|macro|DMA_OC_TxINTR
mdefine_line|#define DMA_OC_TxINTR&t;0x20&t;/* set Tx intr after processing byte */
DECL|macro|DMA_OC_INVALID
mdefine_line|#define DMA_OC_INVALID&t;0x00&t;/* invalid pair */
DECL|macro|DMA_OC_WTHR
mdefine_line|#define DMA_OC_WTHR&t;&t;0x40&t;/* Write byte to THR */
DECL|macro|DMA_OC_WMCR
mdefine_line|#define DMA_OC_WMCR&t;&t;0x80&t;/* Write byte to MCR */
DECL|macro|DMA_OC_DELAY
mdefine_line|#define DMA_OC_DELAY&t;0xc0&t;/* time delay before next xmit */
multiline_comment|/* ring id&squot;s */
DECL|macro|RID_SERIAL0_TX
mdefine_line|#define RID_SERIAL0_TX&t;0x4&t;&t;/* serial port 0, transmit ring buffer */
DECL|macro|RID_SERIAL0_RX
mdefine_line|#define RID_SERIAL0_RX&t;0x5&t;&t;/* serial port 0, receive ring buffer */
DECL|macro|RID_SERIAL1_TX
mdefine_line|#define RID_SERIAL1_TX&t;0x6&t;&t;/* serial port 1, transmit ring buffer */
DECL|macro|RID_SERIAL1_RX
mdefine_line|#define RID_SERIAL1_RX&t;0x7&t;&t;/* serial port 1, receive ring buffer */
DECL|macro|CLOCK_XIN
mdefine_line|#define CLOCK_XIN&t;&t;&t;22
DECL|macro|PRESCALER_DIVISOR
mdefine_line|#define PRESCALER_DIVISOR&t;3
DECL|macro|CLOCK_ACE
mdefine_line|#define CLOCK_ACE&t;&t;&t;7333333
multiline_comment|/*&n; * increment the ring offset. One way to do this would be to add b&squot;100000.&n; * this would let the offset value roll over automatically when it reaches&n; * its maximum value (127). However when we use the offset, we must use&n; * the appropriate bits only by masking with 0xfe0.&n; * The other option is to shift the offset right by 5 bits and look at its&n; * value. Then increment if required and shift back&n; * note: 127 * 2^5 = 4064&n; */
DECL|macro|INC_RING_POINTER
mdefine_line|#define INC_RING_POINTER(x) &bslash;&n;&t;( ((x &amp; 0xffe0) &lt; 4064) ? (x += 32) : 0 )
macro_line|#endif /* _ASM_IA64_SN_UART16550_H */
eof
