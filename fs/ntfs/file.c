multiline_comment|/*&n; * file.c - NTFS kernel file operations. Part of the Linux-NTFS project.&n; *&n; * Copyright (c) 2001 Anton Altaparmakov.&n; *&n; * This program/include file is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License as published&n; * by the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program/include file is distributed in the hope that it will be &n; * useful, but WITHOUT ANY WARRANTY; without even the implied warranty &n; * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program (in the main directory of the Linux-NTFS &n; * distribution in the file COPYING); if not, write to the Free Software&n; * Foundation,Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &quot;ntfs.h&quot;
multiline_comment|/**&n; * ntfs_file_open - called when an inode is about to be opened&n; * @vi:&t;&t;inode to be opened&n; * @filp:&t;file structure describing the inode&n; *&n; * Limit file size to the page cache limit on architectures where unsigned long&n; * is 32-bits. This is the most we can do for now without overflowing the page&n; * cache page index. Doing it this way means we don&squot;t run into problems because&n; * of existing too large files. It would be better to allow the user to read&n; * the beginning of the file but I doubt very much anyone is going to hit this&n; * check on a 32-bit architecture, so there is no point in adding the extra&n; * complexity required to support this.&n; *&n; * On 64-bit architectures, the check is hopefully optimized away by the&n; * compiler.&n; *&n; * After the check passes, just call generic_file_open() to do its work.&n; */
DECL|function|ntfs_file_open
r_static
r_int
id|ntfs_file_open
c_func
(paren
r_struct
id|inode
op_star
id|vi
comma
r_struct
id|file
op_star
id|filp
)paren
(brace
r_if
c_cond
(paren
r_sizeof
(paren
r_int
r_int
)paren
OL
l_int|8
)paren
(brace
r_if
c_cond
(paren
id|vi-&gt;i_size
OG
id|MAX_LFS_FILESIZE
)paren
r_return
op_minus
id|EFBIG
suffix:semicolon
)brace
r_return
id|generic_file_open
c_func
(paren
id|vi
comma
id|filp
)paren
suffix:semicolon
)brace
DECL|variable|ntfs_file_ops
r_struct
id|file_operations
id|ntfs_file_ops
op_assign
(brace
dot
id|llseek
op_assign
id|generic_file_llseek
comma
multiline_comment|/* Seek inside file. */
dot
id|read
op_assign
id|generic_file_read
comma
multiline_comment|/* Read from file. */
dot
id|write
op_assign
id|generic_file_write
comma
multiline_comment|/* Write to a file. */
dot
id|mmap
op_assign
id|generic_file_mmap
comma
multiline_comment|/* Mmap file. */
dot
id|open
op_assign
id|ntfs_file_open
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
