multiline_comment|/*&n; * Carsten Langgaard, carstenl@mips.com&n; * Copyright (C) 2002 MIPS Technologies, Inc.  All rights reserved.&n; *&n; * ########################################################################&n; *&n; *  This program is free software; you can distribute it and/or modify it&n; *  under the terms of the GNU General Public License (Version 2) as&n; *  published by the Free Software Foundation.&n; *&n; *  This program is distributed in the hope it will be useful, but WITHOUT&n; *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or&n; *  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License&n; *  for more details.&n; *&n; *  You should have received a copy of the GNU General Public License along&n; *  with this program; if not, write to the Free Software Foundation, Inc.,&n; *  59 Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * ########################################################################&n; *&n; * Defines of the SEAD board specific address-MAP, registers, etc.&n; *&n; */
macro_line|#ifndef _MIPS_SEAD_H
DECL|macro|_MIPS_SEAD_H
mdefine_line|#define _MIPS_SEAD_H
macro_line|#include &lt;asm/addrspace.h&gt;
multiline_comment|/*&n; * SEAD UART register base.&n; */
DECL|macro|SEAD_UART0_REGS_BASE
mdefine_line|#define SEAD_UART0_REGS_BASE    (0x1f000800)
DECL|macro|SEAD_BASE_BAUD
mdefine_line|#define SEAD_BASE_BAUD ( 3686400 / 16 )
macro_line|#endif /* !(_MIPS_SEAD_H) */
eof
