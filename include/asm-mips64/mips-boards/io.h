multiline_comment|/*&n; * Carsten Langgaard, carstenl@mips.com&n; * Copyright (C) 2000 MIPS Technologies, Inc.  All rights reserved.&n; *&n; * ########################################################################&n; *&n; *  This program is free software; you can distribute it and/or modify it&n; *  under the terms of the GNU General Public License (Version 2) as&n; *  published by the Free Software Foundation.&n; *&n; *  This program is distributed in the hope it will be useful, but WITHOUT&n; *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or&n; *  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License&n; *  for more details.&n; *&n; *  You should have received a copy of the GNU General Public License along&n; *  with this program; if not, write to the Free Software Foundation, Inc.,&n; *  59 Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * ########################################################################&n; *&n; * Defines of the MIPS boards specific IO address-MAP.&n; *&n; */
macro_line|#ifndef _ASM_MIPS_BOARDS_IO_H
DECL|macro|_ASM_MIPS_BOARDS_IO_H
mdefine_line|#define _ASM_MIPS_BOARDS_IO_H
macro_line|#include &lt;asm/addrspace.h&gt;
DECL|macro|IO_SPACE_BASE
mdefine_line|#define IO_SPACE_BASE K1BASE
DECL|macro|IO_SPACE_LIMIT
mdefine_line|#define IO_SPACE_LIMIT 0xffffffff
macro_line|#endif /* _ASM_MIPS_BOARDS_IO_H */
eof
