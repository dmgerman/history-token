multiline_comment|/*&n; *  linux/include/asm-arm/hardware/serial_amba.h&n; *&n; *  Internal header file for AMBA serial ports&n; *&n; *  Copyright (C) ARM Limited&n; *  Copyright (C) 2000 Deep Blue Solutions Ltd.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#ifndef ASM_ARM_HARDWARE_SERIAL_AMBA_H
DECL|macro|ASM_ARM_HARDWARE_SERIAL_AMBA_H
mdefine_line|#define ASM_ARM_HARDWARE_SERIAL_AMBA_H
multiline_comment|/* -------------------------------------------------------------------------------&n; *  From AMBA UART (PL010) Block Specification&n; * -------------------------------------------------------------------------------&n; *  UART Register Offsets.&n; */
DECL|macro|UART01x_DR
mdefine_line|#define UART01x_DR&t;&t;0x00&t;/* Data read or written from the interface. */
DECL|macro|UART01x_RSR
mdefine_line|#define UART01x_RSR&t;&t;0x04&t;/* Receive status register (Read). */
DECL|macro|UART01x_ECR
mdefine_line|#define UART01x_ECR&t;&t;0x04&t;/* Error clear register (Write). */
DECL|macro|UART010_LCRH
mdefine_line|#define UART010_LCRH&t;&t;0x08&t;/* Line control register, high byte. */
DECL|macro|UART010_LCRM
mdefine_line|#define UART010_LCRM&t;&t;0x0C&t;/* Line control register, middle byte. */
DECL|macro|UART010_LCRL
mdefine_line|#define UART010_LCRL&t;&t;0x10&t;/* Line control register, low byte. */
DECL|macro|UART010_CR
mdefine_line|#define UART010_CR&t;&t;0x14&t;/* Control register. */
DECL|macro|UART01x_FR
mdefine_line|#define UART01x_FR&t;&t;0x18&t;/* Flag register (Read only). */
DECL|macro|UART010_IIR
mdefine_line|#define UART010_IIR&t;&t;0x1C&t;/* Interrupt indentification register (Read). */
DECL|macro|UART010_ICR
mdefine_line|#define UART010_ICR&t;&t;0x1C&t;/* Interrupt clear register (Write). */
DECL|macro|UART01x_ILPR
mdefine_line|#define UART01x_ILPR&t;&t;0x20&t;/* IrDA low power counter register. */
DECL|macro|UART011_IBRD
mdefine_line|#define UART011_IBRD&t;&t;0x24&t;/* Integer baud rate divisor register. */
DECL|macro|UART011_FBRD
mdefine_line|#define UART011_FBRD&t;&t;0x28&t;/* Fractional baud rate divisor register. */
DECL|macro|UART011_LCRH
mdefine_line|#define UART011_LCRH&t;&t;0x2c&t;/* Line control register. */
DECL|macro|UART011_CR
mdefine_line|#define UART011_CR&t;&t;0x30&t;/* Control register. */
DECL|macro|UART011_IFLS
mdefine_line|#define UART011_IFLS&t;&t;0x34&t;/* Interrupt fifo level select. */
DECL|macro|UART011_IMSC
mdefine_line|#define UART011_IMSC&t;&t;0x38&t;/* Interrupt mask. */
DECL|macro|UART011_RIS
mdefine_line|#define UART011_RIS&t;&t;0x3c&t;/* Raw interrupt status. */
DECL|macro|UART011_MIS
mdefine_line|#define UART011_MIS&t;&t;0x40&t;/* Masked interrupt status. */
DECL|macro|UART011_ICR
mdefine_line|#define UART011_ICR&t;&t;0x44&t;/* Interrupt clear register. */
DECL|macro|UART011_DMACR
mdefine_line|#define UART011_DMACR&t;&t;0x48&t;/* DMA control register. */
DECL|macro|UART01x_RSR_OE
mdefine_line|#define UART01x_RSR_OE &t;&t;0x08
DECL|macro|UART01x_RSR_BE
mdefine_line|#define UART01x_RSR_BE &t;&t;0x04
DECL|macro|UART01x_RSR_PE
mdefine_line|#define UART01x_RSR_PE &t;&t;0x02
DECL|macro|UART01x_RSR_FE
mdefine_line|#define UART01x_RSR_FE &t;&t;0x01
DECL|macro|UART011_FR_RI
mdefine_line|#define UART011_FR_RI&t;&t;0x100
DECL|macro|UART011_FR_TXFE
mdefine_line|#define UART011_FR_TXFE&t;&t;0x080
DECL|macro|UART011_FR_RXFF
mdefine_line|#define UART011_FR_RXFF&t;&t;0x040
DECL|macro|UART01x_FR_TXFF
mdefine_line|#define UART01x_FR_TXFF&t;&t;0x020
DECL|macro|UART01x_FR_RXFE
mdefine_line|#define UART01x_FR_RXFE&t;&t;0x010
DECL|macro|UART01x_FR_BUSY
mdefine_line|#define UART01x_FR_BUSY&t;&t;0x008
DECL|macro|UART01x_FR_DCD
mdefine_line|#define UART01x_FR_DCD &t;&t;0x004
DECL|macro|UART01x_FR_DSR
mdefine_line|#define UART01x_FR_DSR &t;&t;0x002
DECL|macro|UART01x_FR_CTS
mdefine_line|#define UART01x_FR_CTS &t;&t;0x001
DECL|macro|UART01x_FR_TMSK
mdefine_line|#define UART01x_FR_TMSK&t;&t;(UART01x_FR_TXFF + UART01x_FR_BUSY)
DECL|macro|UART011_CR_CTSEN
mdefine_line|#define UART011_CR_CTSEN&t;0x8000&t;/* CTS hardware flow control */
DECL|macro|UART011_CR_RTSEN
mdefine_line|#define UART011_CR_RTSEN&t;0x4000&t;/* RTS hardware flow control */
DECL|macro|UART011_CR_OUT2
mdefine_line|#define UART011_CR_OUT2&t;&t;0x2000&t;/* OUT2 */
DECL|macro|UART011_CR_OUT1
mdefine_line|#define UART011_CR_OUT1&t;&t;0x1000&t;/* OUT1 */
DECL|macro|UART011_CR_RTS
mdefine_line|#define UART011_CR_RTS&t;&t;0x0800&t;/* RTS */
DECL|macro|UART011_CR_DTR
mdefine_line|#define UART011_CR_DTR&t;&t;0x0400&t;/* DTR */
DECL|macro|UART011_CR_RXE
mdefine_line|#define UART011_CR_RXE&t;&t;0x0200&t;/* receive enable */
DECL|macro|UART011_CR_TXE
mdefine_line|#define UART011_CR_TXE&t;&t;0x0100&t;/* transmit enable */
DECL|macro|UART011_CR_LBE
mdefine_line|#define UART011_CR_LBE&t;&t;0x0080&t;/* loopback enable */
DECL|macro|UART010_CR_RTIE
mdefine_line|#define UART010_CR_RTIE&t;&t;0x0040
DECL|macro|UART010_CR_TIE
mdefine_line|#define UART010_CR_TIE &t;&t;0x0020
DECL|macro|UART010_CR_RIE
mdefine_line|#define UART010_CR_RIE &t;&t;0x0010
DECL|macro|UART010_CR_MSIE
mdefine_line|#define UART010_CR_MSIE&t;&t;0x0008
DECL|macro|UART01x_CR_IIRLP
mdefine_line|#define UART01x_CR_IIRLP&t;0x0004&t;/* SIR low power mode */
DECL|macro|UART01x_CR_SIREN
mdefine_line|#define UART01x_CR_SIREN&t;0x0002&t;/* SIR enable */
DECL|macro|UART01x_CR_UARTEN
mdefine_line|#define UART01x_CR_UARTEN&t;0x0001&t;/* UART enable */
DECL|macro|UART011_LCRH_SPS
mdefine_line|#define UART011_LCRH_SPS&t;0x80
DECL|macro|UART01x_LCRH_WLEN_8
mdefine_line|#define UART01x_LCRH_WLEN_8&t;0x60
DECL|macro|UART01x_LCRH_WLEN_7
mdefine_line|#define UART01x_LCRH_WLEN_7&t;0x40
DECL|macro|UART01x_LCRH_WLEN_6
mdefine_line|#define UART01x_LCRH_WLEN_6&t;0x20
DECL|macro|UART01x_LCRH_WLEN_5
mdefine_line|#define UART01x_LCRH_WLEN_5&t;0x00
DECL|macro|UART01x_LCRH_FEN
mdefine_line|#define UART01x_LCRH_FEN&t;0x10
DECL|macro|UART01x_LCRH_STP2
mdefine_line|#define UART01x_LCRH_STP2&t;0x08
DECL|macro|UART01x_LCRH_EPS
mdefine_line|#define UART01x_LCRH_EPS&t;0x04
DECL|macro|UART01x_LCRH_PEN
mdefine_line|#define UART01x_LCRH_PEN&t;0x02
DECL|macro|UART01x_LCRH_BRK
mdefine_line|#define UART01x_LCRH_BRK&t;0x01
DECL|macro|UART010_IIR_RTIS
mdefine_line|#define UART010_IIR_RTIS&t;0x08
DECL|macro|UART010_IIR_TIS
mdefine_line|#define UART010_IIR_TIS&t;&t;0x04
DECL|macro|UART010_IIR_RIS
mdefine_line|#define UART010_IIR_RIS&t;&t;0x02
DECL|macro|UART010_IIR_MIS
mdefine_line|#define UART010_IIR_MIS&t;&t;0x01
DECL|macro|UART011_IFLS_RX1_8
mdefine_line|#define UART011_IFLS_RX1_8&t;(0 &lt;&lt; 3)
DECL|macro|UART011_IFLS_RX2_8
mdefine_line|#define UART011_IFLS_RX2_8&t;(1 &lt;&lt; 3)
DECL|macro|UART011_IFLS_RX4_8
mdefine_line|#define UART011_IFLS_RX4_8&t;(2 &lt;&lt; 3)
DECL|macro|UART011_IFLS_RX6_8
mdefine_line|#define UART011_IFLS_RX6_8&t;(3 &lt;&lt; 3)
DECL|macro|UART011_IFLS_RX7_8
mdefine_line|#define UART011_IFLS_RX7_8&t;(4 &lt;&lt; 3)
DECL|macro|UART011_IFLS_TX1_8
mdefine_line|#define UART011_IFLS_TX1_8&t;(0 &lt;&lt; 0)
DECL|macro|UART011_IFLS_TX2_8
mdefine_line|#define UART011_IFLS_TX2_8&t;(1 &lt;&lt; 0)
DECL|macro|UART011_IFLS_TX4_8
mdefine_line|#define UART011_IFLS_TX4_8&t;(2 &lt;&lt; 0)
DECL|macro|UART011_IFLS_TX6_8
mdefine_line|#define UART011_IFLS_TX6_8&t;(3 &lt;&lt; 0)
DECL|macro|UART011_IFLS_TX7_8
mdefine_line|#define UART011_IFLS_TX7_8&t;(4 &lt;&lt; 0)
DECL|macro|UART011_OEIM
mdefine_line|#define UART011_OEIM&t;&t;(1 &lt;&lt; 10)&t;/* overrun error interrupt mask */
DECL|macro|UART011_BEIM
mdefine_line|#define UART011_BEIM&t;&t;(1 &lt;&lt; 9)&t;/* break error interrupt mask */
DECL|macro|UART011_PEIM
mdefine_line|#define UART011_PEIM&t;&t;(1 &lt;&lt; 8)&t;/* parity error interrupt mask */
DECL|macro|UART011_FEIM
mdefine_line|#define UART011_FEIM&t;&t;(1 &lt;&lt; 7)&t;/* framing error interrupt mask */
DECL|macro|UART011_RTIM
mdefine_line|#define UART011_RTIM&t;&t;(1 &lt;&lt; 6)&t;/* receive timeout interrupt mask */
DECL|macro|UART011_TXIM
mdefine_line|#define UART011_TXIM&t;&t;(1 &lt;&lt; 5)&t;/* transmit interrupt mask */
DECL|macro|UART011_RXIM
mdefine_line|#define UART011_RXIM&t;&t;(1 &lt;&lt; 4)&t;/* receive interrupt mask */
DECL|macro|UART011_DSRMIM
mdefine_line|#define UART011_DSRMIM&t;&t;(1 &lt;&lt; 3)&t;/* DSR interrupt mask */
DECL|macro|UART011_DCDMIM
mdefine_line|#define UART011_DCDMIM&t;&t;(1 &lt;&lt; 2)&t;/* DCD interrupt mask */
DECL|macro|UART011_CTSMIM
mdefine_line|#define UART011_CTSMIM&t;&t;(1 &lt;&lt; 1)&t;/* CTS interrupt mask */
DECL|macro|UART011_RIMIM
mdefine_line|#define UART011_RIMIM&t;&t;(1 &lt;&lt; 0)&t;/* RI interrupt mask */
DECL|macro|UART011_OEIS
mdefine_line|#define UART011_OEIS&t;&t;(1 &lt;&lt; 10)&t;/* overrun error interrupt status */
DECL|macro|UART011_BEIS
mdefine_line|#define UART011_BEIS&t;&t;(1 &lt;&lt; 9)&t;/* break error interrupt status */
DECL|macro|UART011_PEIS
mdefine_line|#define UART011_PEIS&t;&t;(1 &lt;&lt; 8)&t;/* parity error interrupt status */
DECL|macro|UART011_FEIS
mdefine_line|#define UART011_FEIS&t;&t;(1 &lt;&lt; 7)&t;/* framing error interrupt status */
DECL|macro|UART011_RTIS
mdefine_line|#define UART011_RTIS&t;&t;(1 &lt;&lt; 6)&t;/* receive timeout interrupt status */
DECL|macro|UART011_TXIS
mdefine_line|#define UART011_TXIS&t;&t;(1 &lt;&lt; 5)&t;/* transmit interrupt status */
DECL|macro|UART011_RXIS
mdefine_line|#define UART011_RXIS&t;&t;(1 &lt;&lt; 4)&t;/* receive interrupt status */
DECL|macro|UART011_DSRMIS
mdefine_line|#define UART011_DSRMIS&t;&t;(1 &lt;&lt; 3)&t;/* DSR interrupt status */
DECL|macro|UART011_DCDMIS
mdefine_line|#define UART011_DCDMIS&t;&t;(1 &lt;&lt; 2)&t;/* DCD interrupt status */
DECL|macro|UART011_CTSMIS
mdefine_line|#define UART011_CTSMIS&t;&t;(1 &lt;&lt; 1)&t;/* CTS interrupt status */
DECL|macro|UART011_RIMIS
mdefine_line|#define UART011_RIMIS&t;&t;(1 &lt;&lt; 0)&t;/* RI interrupt status */
DECL|macro|UART011_OEIC
mdefine_line|#define UART011_OEIC&t;&t;(1 &lt;&lt; 10)&t;/* overrun error interrupt clear */
DECL|macro|UART011_BEIC
mdefine_line|#define UART011_BEIC&t;&t;(1 &lt;&lt; 9)&t;/* break error interrupt clear */
DECL|macro|UART011_PEIC
mdefine_line|#define UART011_PEIC&t;&t;(1 &lt;&lt; 8)&t;/* parity error interrupt clear */
DECL|macro|UART011_FEIC
mdefine_line|#define UART011_FEIC&t;&t;(1 &lt;&lt; 7)&t;/* framing error interrupt clear */
DECL|macro|UART011_RTIC
mdefine_line|#define UART011_RTIC&t;&t;(1 &lt;&lt; 6)&t;/* receive timeout interrupt clear */
DECL|macro|UART011_TXIC
mdefine_line|#define UART011_TXIC&t;&t;(1 &lt;&lt; 5)&t;/* transmit interrupt clear */
DECL|macro|UART011_RXIC
mdefine_line|#define UART011_RXIC&t;&t;(1 &lt;&lt; 4)&t;/* receive interrupt clear */
DECL|macro|UART011_DSRMIC
mdefine_line|#define UART011_DSRMIC&t;&t;(1 &lt;&lt; 3)&t;/* DSR interrupt clear */
DECL|macro|UART011_DCDMIC
mdefine_line|#define UART011_DCDMIC&t;&t;(1 &lt;&lt; 2)&t;/* DCD interrupt clear */
DECL|macro|UART011_CTSMIC
mdefine_line|#define UART011_CTSMIC&t;&t;(1 &lt;&lt; 1)&t;/* CTS interrupt clear */
DECL|macro|UART011_RIMIC
mdefine_line|#define UART011_RIMIC&t;&t;(1 &lt;&lt; 0)&t;/* RI interrupt clear */
DECL|macro|UART011_DMAONERR
mdefine_line|#define UART011_DMAONERR&t;(1 &lt;&lt; 2)&t;/* disable dma on error */
DECL|macro|UART011_TXDMAE
mdefine_line|#define UART011_TXDMAE&t;&t;(1 &lt;&lt; 1)&t;/* enable transmit dma */
DECL|macro|UART011_RXDMAE
mdefine_line|#define UART011_RXDMAE&t;&t;(1 &lt;&lt; 0)&t;/* enable receive dma */
DECL|macro|UART01x_RSR_ANY
mdefine_line|#define UART01x_RSR_ANY&t;&t;(UART01x_RSR_OE|UART01x_RSR_BE|UART01x_RSR_PE|UART01x_RSR_FE)
DECL|macro|UART01x_FR_MODEM_ANY
mdefine_line|#define UART01x_FR_MODEM_ANY&t;(UART01x_FR_DCD|UART01x_FR_DSR|UART01x_FR_CTS)
macro_line|#endif
eof
