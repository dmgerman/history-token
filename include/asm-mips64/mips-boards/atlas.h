multiline_comment|/*&n; * Carsten Langgaard, carstenl@mips.com&n; * Copyright (C) 2000 MIPS Technologies, Inc.  All rights reserved.&n; *&n; * ########################################################################&n; *&n; *  This program is free software; you can distribute it and/or modify it&n; *  under the terms of the GNU General Public License (Version 2) as&n; *  published by the Free Software Foundation.&n; *&n; *  This program is distributed in the hope it will be useful, but WITHOUT&n; *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or&n; *  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License&n; *  for more details.&n; *&n; *  You should have received a copy of the GNU General Public License along&n; *  with this program; if not, write to the Free Software Foundation, Inc.,&n; *  59 Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * ########################################################################&n; *&n; * Defines of the Atlas board specific address-MAP, registers, etc.&n; *&n; */
macro_line|#ifndef _MIPS_ATLAS_H
DECL|macro|_MIPS_ATLAS_H
mdefine_line|#define _MIPS_ATLAS_H
macro_line|#include &lt;asm/addrspace.h&gt;
multiline_comment|/* &n; * Atlas RTC-device indirect register access.&n; */
DECL|macro|ATLAS_RTC_ADR_REG
mdefine_line|#define ATLAS_RTC_ADR_REG       (KSEG1ADDR(0x1f000800))
DECL|macro|ATLAS_RTC_DAT_REG
mdefine_line|#define ATLAS_RTC_DAT_REG       (KSEG1ADDR(0x1f000808))
multiline_comment|/*&n; * Atlas interrupt controller register base.&n; */
DECL|macro|ATLAS_ICTRL_REGS_BASE
mdefine_line|#define ATLAS_ICTRL_REGS_BASE   (KSEG1ADDR(0x1f000000))
multiline_comment|/*&n; * Atlas UART register base.&n; */
DECL|macro|ATLAS_UART_REGS_BASE
mdefine_line|#define ATLAS_UART_REGS_BASE    (0x1f000900)
DECL|macro|ATLAS_BASE_BAUD
mdefine_line|#define ATLAS_BASE_BAUD ( 3686400 / 16 ) 
multiline_comment|/*&n; * Atlas PSU standby register.&n; */
DECL|macro|ATLAS_PSUSTBY_REG
mdefine_line|#define ATLAS_PSUSTBY_REG       (KSEG1ADDR(0x1f000600))
DECL|macro|ATLAS_GOSTBY
mdefine_line|#define ATLAS_GOSTBY            0x4d
multiline_comment|/*&n; * We make a universal assumption about the way the bootloader (YAMON)&n; * have located the Philips SAA9730 chip.&n; * This is not ideal, but is needed for setting up remote debugging as &n; * soon as possible.&n; */
DECL|macro|ATLAS_SAA9730_REG
mdefine_line|#define ATLAS_SAA9730_REG  (KSEG1ADDR(0x08800000))
macro_line|#endif /* !(_MIPS_ATLAS_H) */
eof
