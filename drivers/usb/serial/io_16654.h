multiline_comment|/************************************************************************&n; *&n; *&t;16654.H&t;&t;Definitions for 16C654 UART used on EdgePorts&n; *&n; *&t;Copyright (c) 1998 Inside Out Networks, Inc.&n; *&t;This program is free software; you can redistribute it and/or modify&n; *&t;it under the terms of the GNU General Public License as published by&n; *&t;the Free Software Foundation; either version 2 of the License, or&n; *&t;(at your option) any later version.&n; *&n; ************************************************************************/
macro_line|#if !defined(_16654_H)
DECL|macro|_16654_H
mdefine_line|#define&t;_16654_H
multiline_comment|/************************************************************************&n; *&n; *&t;&t;&t;D e f i n e s   /   T y p e d e f s&n; *&n; ************************************************************************/
singleline_comment|//
singleline_comment|// UART register numbers
singleline_comment|// Numbers 0-7 are passed to the Edgeport directly. Numbers 8 and
singleline_comment|// above are used internally to indicate that we must enable access
singleline_comment|// to them via LCR bit 0x80 or LCR = 0xBF.
singleline_comment|// The register number sent to the Edgeport is then (x &amp; 0x7).
singleline_comment|//
singleline_comment|// Driver must not access registers that affect operation of the
singleline_comment|// the EdgePort firmware -- that includes THR, RHR, IER, FCR.
DECL|macro|THR
mdefine_line|#define THR&t;&t;&t;0&t;
singleline_comment|// ! Transmit Holding Register (Write)
DECL|macro|RDR
mdefine_line|#define RDR&t;&t;&t;0&t;
singleline_comment|// ! Receive Holding Register (Read)
DECL|macro|IER
mdefine_line|#define IER&t;&t;&t;1&t;
singleline_comment|// ! Interrupt Enable Register
DECL|macro|FCR
mdefine_line|#define FCR&t;&t;&t;2&t;
singleline_comment|// ! Fifo Control Register (Write)
DECL|macro|ISR
mdefine_line|#define ISR&t;&t;&t;2&t;
singleline_comment|// Interrupt Status Register (Read)
DECL|macro|LCR
mdefine_line|#define LCR&t;&t;&t;3&t;
singleline_comment|// Line Control Register
DECL|macro|MCR
mdefine_line|#define MCR&t;&t;&t;4&t;
singleline_comment|// Modem Control Register
DECL|macro|LSR
mdefine_line|#define LSR&t;&t;&t;5&t;
singleline_comment|// Line Status Register
DECL|macro|MSR
mdefine_line|#define MSR&t;&t;&t;6&t;
singleline_comment|// Modem Status Register
DECL|macro|SPR
mdefine_line|#define SPR&t;&t;&t;7&t;
singleline_comment|// ScratchPad Register
DECL|macro|DLL
mdefine_line|#define DLL&t;&t;&t;8&t;
singleline_comment|// Bank2[ 0 ] Divisor Latch LSB
DECL|macro|DLM
mdefine_line|#define DLM&t;&t;&t;9&t;
singleline_comment|// Bank2[ 1 ] Divisor Latch MSB
DECL|macro|EFR
mdefine_line|#define EFR&t;&t;&t;10&t;
singleline_comment|// Bank2[ 2 ] Extended Function Register
singleline_comment|//efine unused&t;&t;&t;11&t;// Bank2[ 3 ]
DECL|macro|XON1
mdefine_line|#define XON1&t;&t;&t;12&t;
singleline_comment|// Bank2[ 4 ] Xon-1
DECL|macro|XON2
mdefine_line|#define XON2&t;&t;&t;13&t;
singleline_comment|// Bank2[ 5 ] Xon-2
DECL|macro|XOFF1
mdefine_line|#define XOFF1&t;&t;&t;14&t;
singleline_comment|// Bank2[ 6 ] Xoff-1
DECL|macro|XOFF2
mdefine_line|#define XOFF2&t;&t;&t;15&t;
singleline_comment|// Bank2[ 7 ] Xoff-2
DECL|macro|NUM_16654_REGS
mdefine_line|#define&t;NUM_16654_REGS&t;&t;16
DECL|macro|IS_REG_2ND_BANK
mdefine_line|#define IS_REG_2ND_BANK(x)&t;((x) &gt;= 8)
singleline_comment|//
singleline_comment|// Bit definitions for each register
singleline_comment|//
DECL|macro|IER_RX
mdefine_line|#define IER_RX&t;&t;&t;0x01&t;
singleline_comment|// Enable receive interrupt
DECL|macro|IER_TX
mdefine_line|#define IER_TX&t;&t;&t;0x02&t;
singleline_comment|// Enable transmit interrupt
DECL|macro|IER_RXS
mdefine_line|#define IER_RXS&t;&t;&t;0x04&t;
singleline_comment|// Enable receive status interrupt
DECL|macro|IER_MDM
mdefine_line|#define IER_MDM&t;&t;&t;0x08&t;
singleline_comment|// Enable modem status interrupt
DECL|macro|IER_SLEEP
mdefine_line|#define IER_SLEEP&t;&t;0x10&t;
singleline_comment|// Enable sleep mode
DECL|macro|IER_XOFF
mdefine_line|#define IER_XOFF&t;&t;0x20&t;
singleline_comment|// Enable s/w flow control (XOFF) interrupt
DECL|macro|IER_RTS
mdefine_line|#define IER_RTS&t;&t;&t;0x40&t;
singleline_comment|// Enable RTS interrupt
DECL|macro|IER_CTS
mdefine_line|#define IER_CTS&t;&t;&t;0x80&t;
singleline_comment|// Enable CTS interrupt
DECL|macro|IER_ENABLE_ALL
mdefine_line|#define IER_ENABLE_ALL&t;&t;0xFF&t;
singleline_comment|// Enable all ints
DECL|macro|FCR_FIFO_EN
mdefine_line|#define FCR_FIFO_EN&t;&t;0x01&t;
singleline_comment|// Enable FIFOs
DECL|macro|FCR_RXCLR
mdefine_line|#define FCR_RXCLR&t;&t;0x02&t;
singleline_comment|// Reset Rx FIFO
DECL|macro|FCR_TXCLR
mdefine_line|#define FCR_TXCLR&t;&t;0x04&t;
singleline_comment|// Reset Tx FIFO
DECL|macro|FCR_DMA_BLK
mdefine_line|#define FCR_DMA_BLK&t;&t;0x08&t;
singleline_comment|// Enable DMA block mode
DECL|macro|FCR_TX_LEVEL_MASK
mdefine_line|#define FCR_TX_LEVEL_MASK&t;0x30&t;
singleline_comment|// Mask for Tx FIFO Level
DECL|macro|FCR_TX_LEVEL_8
mdefine_line|#define FCR_TX_LEVEL_8&t;&t;0x00&t;
singleline_comment|// Tx FIFO Level =  8 bytes
DECL|macro|FCR_TX_LEVEL_16
mdefine_line|#define FCR_TX_LEVEL_16&t;&t;0x10&t;
singleline_comment|// Tx FIFO Level = 16 bytes
DECL|macro|FCR_TX_LEVEL_32
mdefine_line|#define FCR_TX_LEVEL_32&t;&t;0x20&t;
singleline_comment|// Tx FIFO Level = 32 bytes
DECL|macro|FCR_TX_LEVEL_56
mdefine_line|#define FCR_TX_LEVEL_56&t;&t;0x30&t;
singleline_comment|// Tx FIFO Level = 56 bytes
DECL|macro|FCR_RX_LEVEL_MASK
mdefine_line|#define FCR_RX_LEVEL_MASK&t;0xC0&t;
singleline_comment|// Mask for Rx FIFO Level
DECL|macro|FCR_RX_LEVEL_8
mdefine_line|#define FCR_RX_LEVEL_8&t;&t;0x00&t;
singleline_comment|// Rx FIFO Level =  8 bytes
DECL|macro|FCR_RX_LEVEL_16
mdefine_line|#define FCR_RX_LEVEL_16&t;&t;0x40&t;
singleline_comment|// Rx FIFO Level = 16 bytes
DECL|macro|FCR_RX_LEVEL_56
mdefine_line|#define FCR_RX_LEVEL_56&t;&t;0x80&t;
singleline_comment|// Rx FIFO Level = 56 bytes
DECL|macro|FCR_RX_LEVEL_60
mdefine_line|#define FCR_RX_LEVEL_60&t;&t;0xC0&t;
singleline_comment|// Rx FIFO Level = 60 bytes
DECL|macro|ISR_INT_MDM_STATUS
mdefine_line|#define ISR_INT_MDM_STATUS&t;0x00&t;
singleline_comment|// Modem status int pending
DECL|macro|ISR_INT_NONE
mdefine_line|#define ISR_INT_NONE&t;&t;0x01&t;
singleline_comment|// No interrupt pending
DECL|macro|ISR_INT_TXRDY
mdefine_line|#define ISR_INT_TXRDY&t;&t;0x02&t;
singleline_comment|// Tx ready int pending
DECL|macro|ISR_INT_RXRDY
mdefine_line|#define ISR_INT_RXRDY&t;&t;0x04&t;
singleline_comment|// Rx ready int pending
DECL|macro|ISR_INT_LINE_STATUS
mdefine_line|#define ISR_INT_LINE_STATUS&t;0x06&t;
singleline_comment|// Line status int pending
DECL|macro|ISR_INT_RX_TIMEOUT
mdefine_line|#define ISR_INT_RX_TIMEOUT&t;0x0C&t;
singleline_comment|// Rx timeout int pending
DECL|macro|ISR_INT_RX_XOFF
mdefine_line|#define ISR_INT_RX_XOFF&t;&t;0x10&t;
singleline_comment|// Rx Xoff int pending
DECL|macro|ISR_INT_RTS_CTS
mdefine_line|#define ISR_INT_RTS_CTS&t;&t;0x20&t;
singleline_comment|// RTS/CTS change int pending
DECL|macro|ISR_FIFO_ENABLED
mdefine_line|#define ISR_FIFO_ENABLED&t;0xC0&t;
singleline_comment|// Bits set if FIFOs enabled
DECL|macro|ISR_INT_BITS_MASK
mdefine_line|#define ISR_INT_BITS_MASK&t;0x3E&t;
singleline_comment|// Mask to isolate valid int causes
DECL|macro|LCR_BITS_5
mdefine_line|#define LCR_BITS_5&t;&t;0x00&t;
singleline_comment|// 5 bits/char
DECL|macro|LCR_BITS_6
mdefine_line|#define LCR_BITS_6&t;&t;0x01&t;
singleline_comment|// 6 bits/char
DECL|macro|LCR_BITS_7
mdefine_line|#define LCR_BITS_7&t;&t;0x02&t;
singleline_comment|// 7 bits/char
DECL|macro|LCR_BITS_8
mdefine_line|#define LCR_BITS_8&t;&t;0x03&t;
singleline_comment|// 8 bits/char
DECL|macro|LCR_BITS_MASK
mdefine_line|#define LCR_BITS_MASK&t;&t;0x03&t;
singleline_comment|// Mask for bits/char field
DECL|macro|LCR_STOP_1
mdefine_line|#define LCR_STOP_1&t;&t;0x00&t;
singleline_comment|// 1 stop bit
DECL|macro|LCR_STOP_1_5
mdefine_line|#define LCR_STOP_1_5&t;&t;0x04&t;
singleline_comment|// 1.5 stop bits (if 5   bits/char)
DECL|macro|LCR_STOP_2
mdefine_line|#define LCR_STOP_2&t;&t;0x04&t;
singleline_comment|// 2 stop bits   (if 6-8 bits/char)
DECL|macro|LCR_STOP_MASK
mdefine_line|#define LCR_STOP_MASK&t;&t;0x04&t;
singleline_comment|// Mask for stop bits field
DECL|macro|LCR_PAR_NONE
mdefine_line|#define LCR_PAR_NONE&t;&t;0x00&t;
singleline_comment|// No parity
DECL|macro|LCR_PAR_ODD
mdefine_line|#define LCR_PAR_ODD&t;&t;0x08&t;
singleline_comment|// Odd parity
DECL|macro|LCR_PAR_EVEN
mdefine_line|#define LCR_PAR_EVEN&t;&t;0x18&t;
singleline_comment|// Even parity
DECL|macro|LCR_PAR_MARK
mdefine_line|#define LCR_PAR_MARK&t;&t;0x28&t;
singleline_comment|// Force parity bit to 1
DECL|macro|LCR_PAR_SPACE
mdefine_line|#define LCR_PAR_SPACE&t;&t;0x38&t;
singleline_comment|// Force parity bit to 0
DECL|macro|LCR_PAR_MASK
mdefine_line|#define LCR_PAR_MASK&t;&t;0x38&t;
singleline_comment|// Mask for parity field
DECL|macro|LCR_SET_BREAK
mdefine_line|#define LCR_SET_BREAK&t;&t;0x40&t;
singleline_comment|// Set Break condition
DECL|macro|LCR_DL_ENABLE
mdefine_line|#define LCR_DL_ENABLE&t;&t;0x80&t;
singleline_comment|// Enable access to divisor latch
DECL|macro|LCR_ACCESS_EFR
mdefine_line|#define LCR_ACCESS_EFR&t;&t;0xBF&t;
singleline_comment|// Load this value to access DLL,DLM,
singleline_comment|// and also the &squot;654-only registers
singleline_comment|// EFR, XON1, XON2, XOFF1, XOFF2
DECL|macro|MCR_DTR
mdefine_line|#define MCR_DTR&t;&t;&t;0x01&t;
singleline_comment|// Assert DTR
DECL|macro|MCR_RTS
mdefine_line|#define MCR_RTS&t;&t;&t;0x02&t;
singleline_comment|// Assert RTS
DECL|macro|MCR_OUT1
mdefine_line|#define MCR_OUT1&t;&t;0x04&t;
singleline_comment|// Loopback only: Sets state of RI
DECL|macro|MCR_MASTER_IE
mdefine_line|#define MCR_MASTER_IE&t;&t;0x08&t;
singleline_comment|// Enable interrupt outputs
DECL|macro|MCR_LOOPBACK
mdefine_line|#define MCR_LOOPBACK&t;&t;0x10&t;
singleline_comment|// Set internal (digital) loopback mode
DECL|macro|MCR_XON_ANY
mdefine_line|#define MCR_XON_ANY&t;&t;0x20&t;
singleline_comment|// Enable any char to exit XOFF mode
DECL|macro|MCR_IR_ENABLE
mdefine_line|#define MCR_IR_ENABLE&t;&t;0x40&t;
singleline_comment|// Enable IrDA functions
DECL|macro|MCR_BRG_DIV_4
mdefine_line|#define MCR_BRG_DIV_4&t;&t;0x80&t;
singleline_comment|// Divide baud rate clk by /4 instead of /1
DECL|macro|LSR_RX_AVAIL
mdefine_line|#define LSR_RX_AVAIL&t;&t;0x01&t;
singleline_comment|// Rx data available
DECL|macro|LSR_OVER_ERR
mdefine_line|#define LSR_OVER_ERR&t;&t;0x02&t;
singleline_comment|// Rx overrun
DECL|macro|LSR_PAR_ERR
mdefine_line|#define LSR_PAR_ERR&t;&t;0x04&t;
singleline_comment|// Rx parity error
DECL|macro|LSR_FRM_ERR
mdefine_line|#define LSR_FRM_ERR&t;&t;0x08&t;
singleline_comment|// Rx framing error
DECL|macro|LSR_BREAK
mdefine_line|#define LSR_BREAK&t;&t;0x10&t;
singleline_comment|// Rx break condition detected
DECL|macro|LSR_TX_EMPTY
mdefine_line|#define LSR_TX_EMPTY&t;&t;0x20&t;
singleline_comment|// Tx Fifo empty
DECL|macro|LSR_TX_ALL_EMPTY
mdefine_line|#define LSR_TX_ALL_EMPTY&t;0x40&t;
singleline_comment|// Tx Fifo and shift register empty
DECL|macro|LSR_FIFO_ERR
mdefine_line|#define LSR_FIFO_ERR&t;&t;0x80&t;
singleline_comment|// Rx Fifo contains at least 1 erred char
DECL|macro|MSR_DELTA_CTS
mdefine_line|#define MSR_DELTA_CTS&t;&t;0x01&t;
singleline_comment|// CTS changed from last read
DECL|macro|MSR_DELTA_DSR
mdefine_line|#define MSR_DELTA_DSR&t;&t;0x02&t;
singleline_comment|// DSR changed from last read
DECL|macro|MSR_DELTA_RI
mdefine_line|#define MSR_DELTA_RI&t;&t;0x04&t;
singleline_comment|// RI  changed from 0 -&gt; 1
DECL|macro|MSR_DELTA_CD
mdefine_line|#define MSR_DELTA_CD&t;&t;0x08&t;
singleline_comment|// CD  changed from last read
DECL|macro|MSR_CTS
mdefine_line|#define MSR_CTS&t;&t;&t;0x10&t;
singleline_comment|// Current state of CTS
DECL|macro|MSR_DSR
mdefine_line|#define MSR_DSR&t;&t;&t;0x20&t;
singleline_comment|// Current state of DSR
DECL|macro|MSR_RI
mdefine_line|#define MSR_RI&t;&t;&t;0x40&t;
singleline_comment|// Current state of RI
DECL|macro|MSR_CD
mdefine_line|#define MSR_CD&t;&t;&t;0x80&t;
singleline_comment|// Current state of CD
singleline_comment|//&t;Tx&t;&t;Rx
singleline_comment|//-------------------------------
DECL|macro|EFR_SWFC_NONE
mdefine_line|#define EFR_SWFC_NONE&t;&t;0x00&t;
singleline_comment|//&t;None&t;&t;None
DECL|macro|EFR_SWFC_RX1
mdefine_line|#define EFR_SWFC_RX1&t;&t;0x02 &t;
singleline_comment|//&t;None&t;&t;XOFF1
DECL|macro|EFR_SWFC_RX2
mdefine_line|#define EFR_SWFC_RX2&t;&t;0x01 &t;
singleline_comment|//&t;None&t;&t;XOFF2
DECL|macro|EFR_SWFC_RX12
mdefine_line|#define EFR_SWFC_RX12&t;&t;0x03 &t;
singleline_comment|//&t;None&t;&t;XOFF1 &amp; XOFF2
DECL|macro|EFR_SWFC_TX1
mdefine_line|#define EFR_SWFC_TX1&t;&t;0x08 &t;
singleline_comment|//&t;XOFF1&t;&t;None
DECL|macro|EFR_SWFC_TX1_RX1
mdefine_line|#define EFR_SWFC_TX1_RX1&t;0x0a &t;
singleline_comment|//&t;XOFF1&t;&t;XOFF1
DECL|macro|EFR_SWFC_TX1_RX2
mdefine_line|#define EFR_SWFC_TX1_RX2&t;0x09 &t;
singleline_comment|//&t;XOFF1&t;&t;XOFF2
DECL|macro|EFR_SWFC_TX1_RX12
mdefine_line|#define EFR_SWFC_TX1_RX12&t;0x0b &t;
singleline_comment|//&t;XOFF1&t;&t;XOFF1 &amp; XOFF2
DECL|macro|EFR_SWFC_TX2
mdefine_line|#define EFR_SWFC_TX2&t;&t;0x04 &t;
singleline_comment|//&t;XOFF2&t;&t;None
DECL|macro|EFR_SWFC_TX2_RX1
mdefine_line|#define EFR_SWFC_TX2_RX1&t;0x06 &t;
singleline_comment|//&t;XOFF2&t;&t;XOFF1
DECL|macro|EFR_SWFC_TX2_RX2
mdefine_line|#define EFR_SWFC_TX2_RX2&t;0x05 &t;
singleline_comment|//&t;XOFF2&t;&t;XOFF2
DECL|macro|EFR_SWFC_TX2_RX12
mdefine_line|#define EFR_SWFC_TX2_RX12&t;0x07 &t;
singleline_comment|//&t;XOFF2&t;&t;XOFF1 &amp; XOFF2
DECL|macro|EFR_SWFC_TX12
mdefine_line|#define EFR_SWFC_TX12&t;&t;0x0c &t;
singleline_comment|//&t;XOFF1 &amp; XOFF2&t;None
DECL|macro|EFR_SWFC_TX12_RX1
mdefine_line|#define EFR_SWFC_TX12_RX1&t;0x0e &t;
singleline_comment|//&t;XOFF1 &amp; XOFF2&t;XOFF1
DECL|macro|EFR_SWFC_TX12_RX2
mdefine_line|#define EFR_SWFC_TX12_RX2&t;0x0d &t;
singleline_comment|//&t;XOFF1 &amp; XOFF2&t;XOFF2
DECL|macro|EFR_SWFC_TX12_RX12
mdefine_line|#define EFR_SWFC_TX12_RX12&t;0x0f &t;
singleline_comment|//&t;XOFF1 &amp; XOFF2&t;XOFF1 &amp; XOFF2
DECL|macro|EFR_TX_FC_MASK
mdefine_line|#define EFR_TX_FC_MASK&t;&t;0x0c&t;
singleline_comment|// Mask to isolate Rx flow control
DECL|macro|EFR_TX_FC_NONE
mdefine_line|#define EFR_TX_FC_NONE&t;&t;0x00&t;
singleline_comment|// No Tx Xon/Xoff flow control
DECL|macro|EFR_TX_FC_X1
mdefine_line|#define EFR_TX_FC_X1&t;&t;0x08&t;
singleline_comment|// Transmit Xon1/Xoff1
DECL|macro|EFR_TX_FC_X2
mdefine_line|#define EFR_TX_FC_X2&t;&t;0x04&t;
singleline_comment|// Transmit Xon2/Xoff2
DECL|macro|EFR_TX_FC_X1_2
mdefine_line|#define EFR_TX_FC_X1_2&t;&t;0x0c&t;
singleline_comment|// Transmit Xon1&amp;2/Xoff1&amp;2
DECL|macro|EFR_RX_FC_MASK
mdefine_line|#define EFR_RX_FC_MASK&t;&t;0x03&t;
singleline_comment|// Mask to isolate Rx flow control
DECL|macro|EFR_RX_FC_NONE
mdefine_line|#define EFR_RX_FC_NONE&t;&t;0x00&t;
singleline_comment|// No Rx Xon/Xoff flow control
DECL|macro|EFR_RX_FC_X1
mdefine_line|#define EFR_RX_FC_X1&t;&t;0x02&t;
singleline_comment|// Receiver compares Xon1/Xoff1
DECL|macro|EFR_RX_FC_X2
mdefine_line|#define EFR_RX_FC_X2&t;&t;0x01&t;
singleline_comment|// Receiver compares Xon2/Xoff2
DECL|macro|EFR_RX_FC_X1_2
mdefine_line|#define EFR_RX_FC_X1_2&t;&t;0x03&t;
singleline_comment|// Receiver compares Xon1&amp;2/Xoff1&amp;2
DECL|macro|EFR_SWFC_MASK
mdefine_line|#define EFR_SWFC_MASK&t;&t;0x0F&t;
singleline_comment|// Mask for software flow control field
DECL|macro|EFR_ENABLE_16654
mdefine_line|#define EFR_ENABLE_16654&t;0x10&t;
singleline_comment|// Enable 16C654 features
DECL|macro|EFR_SPEC_DETECT
mdefine_line|#define EFR_SPEC_DETECT&t;&t;0x20&t;
singleline_comment|// Enable special character detect interrupt
DECL|macro|EFR_AUTO_RTS
mdefine_line|#define EFR_AUTO_RTS&t;&t;0x40&t;
singleline_comment|// Use RTS for Rx flow control
DECL|macro|EFR_AUTO_CTS
mdefine_line|#define EFR_AUTO_CTS&t;&t;0x80&t;
singleline_comment|// Use CTS for Tx flow control
macro_line|#endif&t;
singleline_comment|// if !defined(_16654_H)
eof
