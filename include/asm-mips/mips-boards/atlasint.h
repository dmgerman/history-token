multiline_comment|/*&n; * Carsten Langgaard, carstenl@mips.com&n; * Copyright (C) 1999 MIPS Technologies, Inc.  All rights reserved.&n; *&n; * ########################################################################&n; *&n; *  This program is free software; you can distribute it and/or modify it&n; *  under the terms of the GNU General Public License (Version 2) as&n; *  published by the Free Software Foundation.&n; *&n; *  This program is distributed in the hope it will be useful, but WITHOUT&n; *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or&n; *  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License&n; *  for more details.&n; *&n; *  You should have received a copy of the GNU General Public License along&n; *  with this program; if not, write to the Free Software Foundation, Inc.,&n; *  59 Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * ########################################################################&n; *&n; * Defines for the Atlas interrupt controller.&n; *&n; */
macro_line|#ifndef _MIPS_ATLASINT_H
DECL|macro|_MIPS_ATLASINT_H
mdefine_line|#define _MIPS_ATLASINT_H
DECL|macro|ATLASINT_BASE
mdefine_line|#define ATLASINT_BASE&t;&t;1
DECL|macro|ATLASINT_UART
mdefine_line|#define ATLASINT_UART&t;&t;(ATLASINT_BASE+0)
DECL|macro|ATLASINT_TIM0
mdefine_line|#define ATLASINT_TIM0&t;&t;(ATLASINT_BASE+1)
DECL|macro|ATLASINT_RES2
mdefine_line|#define ATLASINT_RES2&t;&t;(ATLASINT_BASE+2)
DECL|macro|ATLASINT_RES3
mdefine_line|#define ATLASINT_RES3&t;&t;(ATLASINT_BASE+3)
DECL|macro|ATLASINT_RTC
mdefine_line|#define ATLASINT_RTC&t;&t;(ATLASINT_BASE+4)
DECL|macro|ATLASINT_COREHI
mdefine_line|#define ATLASINT_COREHI&t;&t;(ATLASINT_BASE+5)
DECL|macro|ATLASINT_CORELO
mdefine_line|#define ATLASINT_CORELO&t;&t;(ATLASINT_BASE+6)
DECL|macro|ATLASINT_RES7
mdefine_line|#define ATLASINT_RES7&t;&t;(ATLASINT_BASE+7)
DECL|macro|ATLASINT_PCIA
mdefine_line|#define ATLASINT_PCIA&t;&t;(ATLASINT_BASE+8)
DECL|macro|ATLASINT_PCIB
mdefine_line|#define ATLASINT_PCIB&t;&t;(ATLASINT_BASE+9)
DECL|macro|ATLASINT_PCIC
mdefine_line|#define ATLASINT_PCIC&t;&t;(ATLASINT_BASE+10)
DECL|macro|ATLASINT_PCID
mdefine_line|#define ATLASINT_PCID&t;&t;(ATLASINT_BASE+11)
DECL|macro|ATLASINT_ENUM
mdefine_line|#define ATLASINT_ENUM&t;&t;(ATLASINT_BASE+12)
DECL|macro|ATLASINT_DEG
mdefine_line|#define ATLASINT_DEG&t;&t;(ATLASINT_BASE+13)
DECL|macro|ATLASINT_ATXFAIL
mdefine_line|#define ATLASINT_ATXFAIL&t;(ATLASINT_BASE+14)
DECL|macro|ATLASINT_INTA
mdefine_line|#define ATLASINT_INTA&t;&t;(ATLASINT_BASE+15)
DECL|macro|ATLASINT_INTB
mdefine_line|#define ATLASINT_INTB&t;&t;(ATLASINT_BASE+16)
DECL|macro|ATLASINT_ETH
mdefine_line|#define ATLASINT_ETH&t;&t;ATLASINT_INTB
DECL|macro|ATLASINT_INTC
mdefine_line|#define ATLASINT_INTC&t;&t;(ATLASINT_BASE+17)
DECL|macro|ATLASINT_SCSI
mdefine_line|#define ATLASINT_SCSI&t;&t;ATLASINT_INTC
DECL|macro|ATLASINT_INTD
mdefine_line|#define ATLASINT_INTD&t;&t;(ATLASINT_BASE+18)
DECL|macro|ATLASINT_SERR
mdefine_line|#define ATLASINT_SERR&t;&t;(ATLASINT_BASE+19)
DECL|macro|ATLASINT_RES20
mdefine_line|#define ATLASINT_RES20&t;&t;(ATLASINT_BASE+20)
DECL|macro|ATLASINT_RES21
mdefine_line|#define ATLASINT_RES21&t;&t;(ATLASINT_BASE+21)
DECL|macro|ATLASINT_RES22
mdefine_line|#define ATLASINT_RES22&t;&t;(ATLASINT_BASE+22)
DECL|macro|ATLASINT_RES23
mdefine_line|#define ATLASINT_RES23&t;&t;(ATLASINT_BASE+23)
DECL|macro|ATLASINT_RES24
mdefine_line|#define ATLASINT_RES24&t;&t;(ATLASINT_BASE+24)
DECL|macro|ATLASINT_RES25
mdefine_line|#define ATLASINT_RES25&t;&t;(ATLASINT_BASE+25)
DECL|macro|ATLASINT_RES26
mdefine_line|#define ATLASINT_RES26&t;&t;(ATLASINT_BASE+26)
DECL|macro|ATLASINT_RES27
mdefine_line|#define ATLASINT_RES27&t;&t;(ATLASINT_BASE+27)
DECL|macro|ATLASINT_RES28
mdefine_line|#define ATLASINT_RES28&t;&t;(ATLASINT_BASE+28)
DECL|macro|ATLASINT_RES29
mdefine_line|#define ATLASINT_RES29&t;&t;(ATLASINT_BASE+29)
DECL|macro|ATLASINT_RES30
mdefine_line|#define ATLASINT_RES30&t;&t;(ATLASINT_BASE+30)
DECL|macro|ATLASINT_RES31
mdefine_line|#define ATLASINT_RES31&t;&t;(ATLASINT_BASE+31)
DECL|macro|ATLASINT_END
mdefine_line|#define ATLASINT_END&t;&t;(ATLASINT_BASE+31)
multiline_comment|/*&n; * Atlas registers are memory mapped on 64-bit aligned boundaries and&n; * only word access are allowed.&n; */
DECL|struct|atlas_ictrl_regs
r_struct
id|atlas_ictrl_regs
(brace
DECL|member|intraw
r_volatile
r_int
r_int
id|intraw
suffix:semicolon
DECL|member|dummy1
r_int
id|dummy1
suffix:semicolon
DECL|member|intseten
r_volatile
r_int
r_int
id|intseten
suffix:semicolon
DECL|member|dummy2
r_int
id|dummy2
suffix:semicolon
DECL|member|intrsten
r_volatile
r_int
r_int
id|intrsten
suffix:semicolon
DECL|member|dummy3
r_int
id|dummy3
suffix:semicolon
DECL|member|intenable
r_volatile
r_int
r_int
id|intenable
suffix:semicolon
DECL|member|dummy4
r_int
id|dummy4
suffix:semicolon
DECL|member|intstatus
r_volatile
r_int
r_int
id|intstatus
suffix:semicolon
DECL|member|dummy5
r_int
id|dummy5
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_void
id|atlasint_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* !(_MIPS_ATLASINT_H) */
eof
