multiline_comment|/**&n; * aops.h - Defines for NTFS kernel address space operations and page cache&n; *&t;    handling.  Part of the Linux-NTFS project.&n; *&n; * Copyright (c) 2001-2004 Anton Altaparmakov&n; * Copyright (c) 2002 Richard Russon&n; *&n; * This program/include file is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License as published&n; * by the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program/include file is distributed in the hope that it will be&n; * useful, but WITHOUT ANY WARRANTY; without even the implied warranty&n; * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program (in the main directory of the Linux-NTFS&n; * distribution in the file COPYING); if not, write to the Free Software&n; * Foundation,Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#ifndef _LINUX_NTFS_AOPS_H
DECL|macro|_LINUX_NTFS_AOPS_H
mdefine_line|#define _LINUX_NTFS_AOPS_H
macro_line|#ifdef NTFS_RW
macro_line|#include &quot;inode.h&quot;
r_extern
r_void
id|mark_ntfs_record_dirty
c_func
(paren
id|ntfs_inode
op_star
id|ni
comma
r_struct
id|page
op_star
id|page
comma
r_int
r_int
id|rec_start
)paren
suffix:semicolon
macro_line|#endif /* NTFS_RW */
macro_line|#endif /* _LINUX_NTFS_AOPS_H */
eof
