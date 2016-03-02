multiline_comment|/*&n; * Copyright (c) 2000-2002 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.&t; Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
macro_line|#ifndef __XFS_CRED_H__
DECL|macro|__XFS_CRED_H__
mdefine_line|#define __XFS_CRED_H__
multiline_comment|/*&n; * Credentials&n; */
DECL|struct|cred
r_typedef
r_struct
id|cred
(brace
multiline_comment|/* EMPTY */
DECL|typedef|cred_t
)brace
id|cred_t
suffix:semicolon
r_extern
r_struct
id|cred
op_star
id|sys_cred
suffix:semicolon
multiline_comment|/* this is a hack.. (assums sys_cred is the only cred_t in the system) */
DECL|function|capable_cred
r_static
id|__inline
r_int
id|capable_cred
c_func
(paren
id|cred_t
op_star
id|cr
comma
r_int
id|cid
)paren
(brace
r_return
(paren
id|cr
op_eq
id|sys_cred
)paren
ques
c_cond
l_int|1
suffix:colon
id|capable
c_func
(paren
id|cid
)paren
suffix:semicolon
)brace
macro_line|#endif&t;/* __XFS_CRED_H__ */
eof
