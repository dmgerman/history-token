multiline_comment|/*&n; * file.c - NTFS kernel file operations. Part of the Linux-NTFS project.&n; *&n; * Copyright (c) 2001 Anton Altaparmakov.&n; *&n; * This program/include file is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License as published&n; * by the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program/include file is distributed in the hope that it will be &n; * useful, but WITHOUT ANY WARRANTY; without even the implied warranty &n; * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program (in the main directory of the Linux-NTFS &n; * distribution in the file COPYING); if not, write to the Free Software&n; * Foundation,Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &quot;ntfs.h&quot;
DECL|variable|ntfs_file_ops
r_struct
id|file_operations
id|ntfs_file_ops
op_assign
(brace
id|llseek
suffix:colon
id|generic_file_llseek
comma
multiline_comment|/* Seek inside file. */
id|read
suffix:colon
id|generic_file_read
comma
multiline_comment|/* Read from file. */
id|mmap
suffix:colon
id|generic_file_mmap
comma
multiline_comment|/* Mmap file. */
id|open
suffix:colon
id|generic_file_open
comma
multiline_comment|/* Open file. */
)brace
suffix:semicolon
DECL|variable|ntfs_file_inode_ops
r_struct
id|inode_operations
id|ntfs_file_inode_ops
op_assign
(brace
)brace
suffix:semicolon
DECL|variable|ntfs_empty_file_ops
r_struct
id|file_operations
id|ntfs_empty_file_ops
op_assign
(brace
)brace
suffix:semicolon
DECL|variable|ntfs_empty_inode_ops
r_struct
id|inode_operations
id|ntfs_empty_inode_ops
op_assign
(brace
)brace
suffix:semicolon
eof
