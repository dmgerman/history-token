multiline_comment|/*&n; * dir.h - Defines for directory handling in NTFS Linux kernel driver. Part of&n; *&t;   the Linux-NTFS project.&n; *&n; * Copyright (c) 2002 Anton Altaparmakov.&n; *&n; * This program/include file is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License as published&n; * by the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program/include file is distributed in the hope that it will be &n; * useful, but WITHOUT ANY WARRANTY; without even the implied warranty &n; * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program (in the main directory of the Linux-NTFS &n; * distribution in the file COPYING); if not, write to the Free Software&n; * Foundation,Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#ifndef _LINUX_NTFS_DIR_H
DECL|macro|_LINUX_NTFS_DIR_H
mdefine_line|#define _LINUX_NTFS_DIR_H
macro_line|#include &quot;layout.h&quot;
multiline_comment|/*&n; * ntfs_name is used to return the file name to the caller of&n; * ntfs_lookup_inode_by_name() in order for the caller (namei.c::ntfs_lookup())&n; * to be able to deal with dcache aliasing issues.&n; */
r_typedef
r_struct
(brace
DECL|member|mref
id|MFT_REF
id|mref
suffix:semicolon
DECL|member|type
id|FILE_NAME_TYPE_FLAGS
id|type
suffix:semicolon
DECL|member|len
id|u8
id|len
suffix:semicolon
DECL|member|name
id|uchar_t
id|name
(braket
l_int|0
)braket
suffix:semicolon
DECL|typedef|ntfs_name
)brace
id|__attribute__
(paren
(paren
id|__packed__
)paren
)paren
id|ntfs_name
suffix:semicolon
multiline_comment|/* The little endian Unicode string $I30 as a global constant. */
r_extern
id|uchar_t
id|I30
(braket
l_int|5
)braket
suffix:semicolon
r_extern
id|MFT_REF
id|ntfs_lookup_inode_by_name
c_func
(paren
id|ntfs_inode
op_star
id|dir_ni
comma
r_const
id|uchar_t
op_star
id|uname
comma
r_const
r_int
id|uname_len
comma
id|ntfs_name
op_star
op_star
id|res
)paren
suffix:semicolon
macro_line|#endif /* _LINUX_NTFS_FS_DIR_H */
eof
