multiline_comment|/*&n; *  linux/include/asm-arm/hardware/serial_amba.h&n; *&n; *  Internal header file for AMBA serial ports&n; *&n; *  Copyright (C) ARM Limited&n; *  Copyright (C) 2000 Deep Blue Solutions Ltd.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#ifndef ASM_ARM_HARDWARE_SERIAL_AMBA_H
DECL|macro|ASM_ARM_HARDWARE_SERIAL_AMBA_H
mdefine_line|#define ASM_ARM_HARDWARE_SERIAL_AMBA_H
multiline_comment|/* -------------------------------------------------------------------------------&n; *  From AMBA UART (PL010) Block Specification (ARM-0001-CUST-DSPC-A03)&n; * -------------------------------------------------------------------------------&n; *  UART Register Offsets.&n; */
DECL|macro|AMBA_UARTDR
mdefine_line|#define AMBA_UARTDR                     0x00&t; /*  Data read or written from the interface. */
DECL|macro|AMBA_UARTRSR
mdefine_line|#define AMBA_UARTRSR                    0x04&t; /*  Receive status register (Read). */
DECL|macro|AMBA_UARTECR
mdefine_line|#define AMBA_UARTECR                    0x04&t; /*  Error clear register (Write). */
DECL|macro|AMBA_UARTLCR_H
mdefine_line|#define AMBA_UARTLCR_H                  0x08&t; /*  Line control register, high byte. */
DECL|macro|AMBA_UARTLCR_M
mdefine_line|#define AMBA_UARTLCR_M                  0x0C&t; /*  Line control register, middle byte. */
DECL|macro|AMBA_UARTLCR_L
mdefine_line|#define AMBA_UARTLCR_L                  0x10&t; /*  Line control register, low byte. */
DECL|macro|AMBA_UARTCR
mdefine_line|#define AMBA_UARTCR                     0x14&t; /*  Control register. */
DECL|macro|AMBA_UARTFR
mdefine_line|#define AMBA_UARTFR                     0x18&t; /*  Flag register (Read only). */
DECL|macro|AMBA_UARTIIR
mdefine_line|#define AMBA_UARTIIR                    0x1C&t; /*  Interrupt indentification register (Read). */
DECL|macro|AMBA_UARTICR
mdefine_line|#define AMBA_UARTICR                    0x1C&t; /*  Interrupt clear register (Write). */
DECL|macro|AMBA_UARTILPR
mdefine_line|#define AMBA_UARTILPR                   0x20&t; /*  IrDA low power counter register. */
DECL|macro|AMBA_UARTRSR_OE
mdefine_line|#define AMBA_UARTRSR_OE                 0x08
DECL|macro|AMBA_UARTRSR_BE
mdefine_line|#define AMBA_UARTRSR_BE                 0x04
DECL|macro|AMBA_UARTRSR_PE
mdefine_line|#define AMBA_UARTRSR_PE                 0x02
DECL|macro|AMBA_UARTRSR_FE
mdefine_line|#define AMBA_UARTRSR_FE                 0x01
DECL|macro|AMBA_UARTFR_TXFF
mdefine_line|#define AMBA_UARTFR_TXFF                0x20
DECL|macro|AMBA_UARTFR_RXFE
mdefine_line|#define AMBA_UARTFR_RXFE                0x10
DECL|macro|AMBA_UARTFR_BUSY
mdefine_line|#define AMBA_UARTFR_BUSY                0x08
DECL|macro|AMBA_UARTFR_DCD
mdefine_line|#define AMBA_UARTFR_DCD&t;&t;&t;0x04
DECL|macro|AMBA_UARTFR_DSR
mdefine_line|#define AMBA_UARTFR_DSR&t;&t;&t;0x02
DECL|macro|AMBA_UARTFR_CTS
mdefine_line|#define AMBA_UARTFR_CTS&t;&t;&t;0x01
DECL|macro|AMBA_UARTFR_TMSK
mdefine_line|#define AMBA_UARTFR_TMSK                (AMBA_UARTFR_TXFF + AMBA_UARTFR_BUSY)
DECL|macro|AMBA_UARTCR_RTIE
mdefine_line|#define AMBA_UARTCR_RTIE                0x40
DECL|macro|AMBA_UARTCR_TIE
mdefine_line|#define AMBA_UARTCR_TIE                 0x20
DECL|macro|AMBA_UARTCR_RIE
mdefine_line|#define AMBA_UARTCR_RIE                 0x10
DECL|macro|AMBA_UARTCR_MSIE
mdefine_line|#define AMBA_UARTCR_MSIE                0x08
DECL|macro|AMBA_UARTCR_IIRLP
mdefine_line|#define AMBA_UARTCR_IIRLP               0x04
DECL|macro|AMBA_UARTCR_SIREN
mdefine_line|#define AMBA_UARTCR_SIREN               0x02
DECL|macro|AMBA_UARTCR_UARTEN
mdefine_line|#define AMBA_UARTCR_UARTEN              0x01
DECL|macro|AMBA_UARTLCR_H_WLEN_8
mdefine_line|#define AMBA_UARTLCR_H_WLEN_8           0x60
DECL|macro|AMBA_UARTLCR_H_WLEN_7
mdefine_line|#define AMBA_UARTLCR_H_WLEN_7           0x40
DECL|macro|AMBA_UARTLCR_H_WLEN_6
mdefine_line|#define AMBA_UARTLCR_H_WLEN_6           0x20
DECL|macro|AMBA_UARTLCR_H_WLEN_5
mdefine_line|#define AMBA_UARTLCR_H_WLEN_5           0x00
DECL|macro|AMBA_UARTLCR_H_FEN
mdefine_line|#define AMBA_UARTLCR_H_FEN              0x10
DECL|macro|AMBA_UARTLCR_H_STP2
mdefine_line|#define AMBA_UARTLCR_H_STP2             0x08
DECL|macro|AMBA_UARTLCR_H_EPS
mdefine_line|#define AMBA_UARTLCR_H_EPS              0x04
DECL|macro|AMBA_UARTLCR_H_PEN
mdefine_line|#define AMBA_UARTLCR_H_PEN              0x02
DECL|macro|AMBA_UARTLCR_H_BRK
mdefine_line|#define AMBA_UARTLCR_H_BRK              0x01
DECL|macro|AMBA_UARTIIR_RTIS
mdefine_line|#define AMBA_UARTIIR_RTIS               0x08
DECL|macro|AMBA_UARTIIR_TIS
mdefine_line|#define AMBA_UARTIIR_TIS                0x04
DECL|macro|AMBA_UARTIIR_RIS
mdefine_line|#define AMBA_UARTIIR_RIS                0x02
DECL|macro|AMBA_UARTIIR_MIS
mdefine_line|#define AMBA_UARTIIR_MIS                0x01
DECL|macro|ARM_BAUD_460800
mdefine_line|#define ARM_BAUD_460800                 1
DECL|macro|ARM_BAUD_230400
mdefine_line|#define ARM_BAUD_230400                 3
DECL|macro|ARM_BAUD_115200
mdefine_line|#define ARM_BAUD_115200                 7
DECL|macro|ARM_BAUD_57600
mdefine_line|#define ARM_BAUD_57600                  15
DECL|macro|ARM_BAUD_38400
mdefine_line|#define ARM_BAUD_38400                  23
DECL|macro|ARM_BAUD_19200
mdefine_line|#define ARM_BAUD_19200                  47
DECL|macro|ARM_BAUD_14400
mdefine_line|#define ARM_BAUD_14400                  63
DECL|macro|ARM_BAUD_9600
mdefine_line|#define ARM_BAUD_9600                   95
DECL|macro|ARM_BAUD_4800
mdefine_line|#define ARM_BAUD_4800                   191
DECL|macro|ARM_BAUD_2400
mdefine_line|#define ARM_BAUD_2400                   383
DECL|macro|ARM_BAUD_1200
mdefine_line|#define ARM_BAUD_1200                   767
macro_line|#endif
eof
