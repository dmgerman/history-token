multiline_comment|/*&n; * iSeries_proc.h&n; * Copyright (C) 2001  Kyle A. Lucke IBM Corporation&n; * &n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; * &n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; * &n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; */
multiline_comment|/* Change Activity: */
multiline_comment|/* End Change Activity */
macro_line|#ifndef _ISERIES_PROC_H
DECL|macro|_ISERIES_PROC_H
mdefine_line|#define _ISERIES_PROC_H
macro_line|#include &lt;linux/proc_fs.h&gt;
r_extern
r_void
id|iSeries_proc_early_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|iSeries_proc_create
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|typedef|iSeriesProcFunction
r_typedef
r_void
(paren
op_star
id|iSeriesProcFunction
)paren
(paren
r_struct
id|proc_dir_entry
op_star
id|iSeries_proc
)paren
suffix:semicolon
r_extern
r_void
id|iSeries_proc_callback
c_func
(paren
id|iSeriesProcFunction
id|initFunction
)paren
suffix:semicolon
macro_line|#endif /* _iSeries_PROC_H */
eof
