multiline_comment|/*&n; * Carsten Langgaard, carstenl@mips.com&n; * Copyright (C) 2002 MIPS Technologies, Inc.  All rights reserved.&n; *&n; * ########################################################################&n; *&n; *  This program is free software; you can distribute it and/or modify it&n; *  under the terms of the GNU General Public License (Version 2) as&n; *  published by the Free Software Foundation.&n; *&n; *  This program is distributed in the hope it will be useful, but WITHOUT&n; *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or&n; *  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License&n; *  for more details.&n; *&n; *  You should have received a copy of the GNU General Public License along&n; *  with this program; if not, write to the Free Software Foundation, Inc.,&n; *  59 Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * ########################################################################&n; *&n; * Defines for the SEAD interrupt controller.&n; *&n; */
macro_line|#ifndef _MIPS_SEADINT_H
DECL|macro|_MIPS_SEADINT_H
mdefine_line|#define _MIPS_SEADINT_H
multiline_comment|/* Number of IRQ supported */
DECL|macro|SEADINT_UART0
mdefine_line|#define SEADINT_UART0     0
DECL|macro|SEADINT_UART1
mdefine_line|#define SEADINT_UART1     1
DECL|macro|SEADINT_END
mdefine_line|#define SEADINT_END       2
r_extern
r_void
id|seadint_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* !(_MIPS_SEADINT_H) */
eof
