macro_line|#ifndef _PPC64_PROC_FS_H
DECL|macro|_PPC64_PROC_FS_H
mdefine_line|#define _PPC64_PROC_FS_H
multiline_comment|/*&n; * proc_fs.h&n; * Copyright (C) 2001  Mike Corrigan  IBM Corporation&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; */
multiline_comment|/* Change Activity: */
multiline_comment|/* tgall -- merge of iSeries/iSeries_proc.h and proc_pmc.h */
multiline_comment|/* End Change Activity */
macro_line|#include &lt;linux/proc_fs.h&gt;
DECL|struct|proc_ppc64_t
r_struct
id|proc_ppc64_t
(brace
DECL|member|root
r_struct
id|proc_dir_entry
op_star
id|root
suffix:semicolon
DECL|member|naca
r_struct
id|proc_dir_entry
op_star
id|naca
suffix:semicolon
DECL|member|paca
r_struct
id|proc_dir_entry
op_star
id|paca
suffix:semicolon
DECL|member|systemcfg
r_struct
id|proc_dir_entry
op_star
id|systemcfg
suffix:semicolon
DECL|member|rtas
r_struct
id|proc_dir_entry
op_star
id|rtas
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|proc_ppc64_t
id|proc_ppc64
suffix:semicolon
r_extern
r_int
id|proc_ppc64_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* _PPC64_PROC_FS_H */
eof
