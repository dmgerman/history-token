multiline_comment|/*&n; * Carsten Langgaard, carstenl@mips.com&n; * Copyright (C) 2000 MIPS Technologies, Inc.  All rights reserved.&n; *&n; * ########################################################################&n; *&n; *  This program is free software; you can distribute it and/or modify it&n; *  under the terms of the GNU General Public License (Version 2) as&n; *  published by the Free Software Foundation.&n; *&n; *  This program is distributed in the hope it will be useful, but WITHOUT&n; *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or&n; *  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License&n; *  for more details.&n; *&n; *  You should have received a copy of the GNU General Public License along&n; *  with this program; if not, write to the Free Software Foundation, Inc.,&n; *  59 Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * ########################################################################&n; *&n; * Register definitions for the UART part of the Philips SAA9730 chip.&n; *&n; */
macro_line|#ifndef SAA9730_UART_H
DECL|macro|SAA9730_UART_H
mdefine_line|#define SAA9730_UART_H
multiline_comment|/* The SAA9730 UART register map, as seen via the PCI bus */
DECL|macro|SAA9730_UART_REGS_ADDR
mdefine_line|#define SAA9730_UART_REGS_ADDR&t;0x21800
DECL|struct|uart_saa9730_regmap
r_struct
id|uart_saa9730_regmap
(brace
DECL|member|Thr_Rbr
r_volatile
r_int
r_char
id|Thr_Rbr
suffix:semicolon
DECL|member|Ier
r_volatile
r_int
r_char
id|Ier
suffix:semicolon
DECL|member|Iir_Fcr
r_volatile
r_int
r_char
id|Iir_Fcr
suffix:semicolon
DECL|member|Lcr
r_volatile
r_int
r_char
id|Lcr
suffix:semicolon
DECL|member|Mcr
r_volatile
r_int
r_char
id|Mcr
suffix:semicolon
DECL|member|Lsr
r_volatile
r_int
r_char
id|Lsr
suffix:semicolon
DECL|member|Msr
r_volatile
r_int
r_char
id|Msr
suffix:semicolon
DECL|member|Scr
r_volatile
r_int
r_char
id|Scr
suffix:semicolon
DECL|member|BaudDivLsb
r_volatile
r_int
r_char
id|BaudDivLsb
suffix:semicolon
DECL|member|BaudDivMsb
r_volatile
r_int
r_char
id|BaudDivMsb
suffix:semicolon
DECL|member|Junk0
r_volatile
r_int
r_char
id|Junk0
suffix:semicolon
DECL|member|Junk1
r_volatile
r_int
r_char
id|Junk1
suffix:semicolon
DECL|member|Config
r_volatile
r_int
r_int
id|Config
suffix:semicolon
multiline_comment|/* 0x2180c */
DECL|member|TxStart
r_volatile
r_int
r_int
id|TxStart
suffix:semicolon
multiline_comment|/* 0x21810 */
DECL|member|TxLength
r_volatile
r_int
r_int
id|TxLength
suffix:semicolon
multiline_comment|/* 0x21814 */
DECL|member|TxCounter
r_volatile
r_int
r_int
id|TxCounter
suffix:semicolon
multiline_comment|/* 0x21818 */
DECL|member|RxStart
r_volatile
r_int
r_int
id|RxStart
suffix:semicolon
multiline_comment|/* 0x2181c */
DECL|member|RxLength
r_volatile
r_int
r_int
id|RxLength
suffix:semicolon
multiline_comment|/* 0x21820 */
DECL|member|RxCounter
r_volatile
r_int
r_int
id|RxCounter
suffix:semicolon
multiline_comment|/* 0x21824 */
)brace
suffix:semicolon
DECL|typedef|t_uart_saa9730_regmap
r_typedef
r_volatile
r_struct
id|uart_saa9730_regmap
id|t_uart_saa9730_regmap
suffix:semicolon
multiline_comment|/*&n; * Only a subset of the UART control bits are defined here,&n; * enough to make the serial debug port work.&n; */
DECL|macro|SAA9730_LCR_DATA8
mdefine_line|#define SAA9730_LCR_DATA8&t;0x03
DECL|macro|SAA9730_MCR_DTR
mdefine_line|#define SAA9730_MCR_DTR&t;&t;0x01
DECL|macro|SAA9730_MCR_RTS
mdefine_line|#define SAA9730_MCR_RTS&t;&t;0x02
DECL|macro|SAA9730_LSR_DR
mdefine_line|#define SAA9730_LSR_DR&t;&t;0x01
DECL|macro|SAA9730_LSR_THRE
mdefine_line|#define SAA9730_LSR_THRE&t;0x20
macro_line|#endif /* !(SAA9730_UART_H) */
eof
