multiline_comment|/*&n; * Copyright (c) 2000-2002 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.&t; Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
macro_line|#ifndef __XFS_GLOBALS_H__
DECL|macro|__XFS_GLOBALS_H__
mdefine_line|#define __XFS_GLOBALS_H__
multiline_comment|/*&n; * This file declares globals needed by XFS that were normally defined&n; * somewhere else in IRIX.&n; */
r_extern
r_uint64
id|xfs_panic_mask
suffix:semicolon
multiline_comment|/* set to cause more panics */
r_extern
r_int
id|restricted_chown
suffix:semicolon
r_extern
r_int
r_int
id|xfs_physmem
suffix:semicolon
r_extern
r_struct
id|cred
op_star
id|sys_cred
suffix:semicolon
r_extern
r_struct
id|xfs_qm
op_star
id|xfs_Gqm
suffix:semicolon
r_extern
id|mutex_t
id|xfs_Gqm_lock
suffix:semicolon
macro_line|#endif&t;/* __XFS_GLOBALS_H__ */
eof
