multiline_comment|/*&n; * Carsten Langgaard, carstenl@mips.com&n; * Copyright (C) 2000 MIPS Technologies, Inc.  All rights reserved.&n; *&n; * ########################################################################&n; *&n; *  This program is free software; you can distribute it and/or modify it&n; *  under the terms of the GNU General Public License (Version 2) as&n; *  published by the Free Software Foundation.&n; *&n; *  This program is distributed in the hope it will be useful, but WITHOUT&n; *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or&n; *  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License&n; *  for more details.&n; *&n; *  You should have received a copy of the GNU General Public License along&n; *  with this program; if not, write to the Free Software Foundation, Inc.,&n; *  59 Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * ########################################################################&n; *&n; * Defines for the Atlas interrupt controller.&n; *&n; */
macro_line|#ifndef _MIPS_ATLASINT_H
DECL|macro|_MIPS_ATLASINT_H
mdefine_line|#define _MIPS_ATLASINT_H
multiline_comment|/* Number of IRQ supported on hw interrupt 0. */
DECL|macro|ATLASINT_UART
mdefine_line|#define ATLASINT_UART      0
DECL|macro|ATLASINT_END
mdefine_line|#define ATLASINT_END      32
multiline_comment|/* &n; * Atlas registers are memory mapped on 64-bit aligned boundaries and &n; * only word access are allowed.&n; */
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
