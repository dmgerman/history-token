multiline_comment|/*&n; * Some of the code in this file has been gleaned from the 64 bit &n; * discontigmem support code base.&n; *&n; * Copyright (C) 2002, IBM Corp.&n; *&n; * All rights reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE, GOOD TITLE or&n; * NON INFRINGEMENT.  See the GNU General Public License for more&n; * details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; * Send feedback to Pat Gaughen &lt;gone@us.ibm.com&gt;&n; */
macro_line|#ifndef _ASM_SRAT_H_
DECL|macro|_ASM_SRAT_H_
mdefine_line|#define _ASM_SRAT_H_
r_extern
r_int
id|physnode_map
(braket
)braket
suffix:semicolon
DECL|macro|MAX_NUMNODES
mdefine_line|#define MAX_NUMNODES&t;&t;8
r_extern
r_void
id|get_memcfg_from_srat
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
r_int
op_star
id|get_zholes_size
c_func
(paren
r_int
)paren
suffix:semicolon
DECL|macro|get_memcfg_numa
mdefine_line|#define get_memcfg_numa() get_memcfg_from_srat()
macro_line|#endif /* _ASM_SRAT_H_ */
eof
