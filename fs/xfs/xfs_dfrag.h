multiline_comment|/*&n; * Copyright (c) 2000 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.&t; Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
macro_line|#ifndef __XFS_DFRAG_H__
DECL|macro|__XFS_DFRAG_H__
mdefine_line|#define __XFS_DFRAG_H__
multiline_comment|/*&n; * Structure passed to xfs_swapext&n; */
DECL|struct|xfs_swapext
r_typedef
r_struct
id|xfs_swapext
(brace
DECL|member|sx_version
id|__int64_t
id|sx_version
suffix:semicolon
multiline_comment|/* version */
DECL|member|sx_fdtarget
id|__int64_t
id|sx_fdtarget
suffix:semicolon
multiline_comment|/* fd of target file */
DECL|member|sx_fdtmp
id|__int64_t
id|sx_fdtmp
suffix:semicolon
multiline_comment|/* fd of tmp file */
DECL|member|sx_offset
id|xfs_off_t
id|sx_offset
suffix:semicolon
multiline_comment|/* offset into file */
DECL|member|sx_length
id|xfs_off_t
id|sx_length
suffix:semicolon
multiline_comment|/* leng from offset */
DECL|member|sx_pad
r_char
id|sx_pad
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* pad space, unused */
DECL|member|sx_stat
id|xfs_bstat_t
id|sx_stat
suffix:semicolon
multiline_comment|/* stat of target b4 copy */
DECL|typedef|xfs_swapext_t
)brace
id|xfs_swapext_t
suffix:semicolon
multiline_comment|/*&n; * Version flag&n; */
DECL|macro|XFS_SX_VERSION
mdefine_line|#define XFS_SX_VERSION&t;&t;0
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * Prototypes for visible xfs_dfrag.c routines.&n; */
multiline_comment|/*&n; * Syscall interface for xfs_swapext&n; */
r_int
id|xfs_swapext
c_func
(paren
r_struct
id|xfs_swapext
op_star
id|sx
)paren
suffix:semicolon
macro_line|#endif&t;/* __KERNEL__ */
macro_line|#endif&t;/* __XFS_DFRAG_H__ */
eof
