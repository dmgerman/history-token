macro_line|#ifndef _PPC64_PROC_FS_H
DECL|macro|_PPC64_PROC_FS_H
mdefine_line|#define _PPC64_PROC_FS_H
multiline_comment|/*&n; * proc_fs.h&n; * Copyright (C) 2001  Mike Corrigan  IBM Corporation&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; */
multiline_comment|/* Change Activity: */
multiline_comment|/* tgall -- merge of iSeries/iSeries_proc.h and proc_pmc.h */
multiline_comment|/* End Change Activity */
macro_line|#include &lt;linux/proc_fs.h&gt;
r_void
id|pmc_proc_init
c_func
(paren
r_struct
id|proc_dir_entry
op_star
id|iSeries_proc
)paren
suffix:semicolon
r_void
id|proc_ppc64_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#include &lt;asm/iSeries/iSeries_proc.h&gt;
macro_line|#endif
eof
