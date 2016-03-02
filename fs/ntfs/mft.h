multiline_comment|/*&n; * mft.h - Defines for mft record handling in NTFS Linux kernel driver.&n; *&t;   Part of the Linux-NTFS project.&n; *&n; * Copyright (c) 2001-2004 Anton Altaparmakov.&n; *&n; * This program/include file is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License as published&n; * by the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program/include file is distributed in the hope that it will be&n; * useful, but WITHOUT ANY WARRANTY; without even the implied warranty&n; * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program (in the main directory of the Linux-NTFS&n; * distribution in the file COPYING); if not, write to the Free Software&n; * Foundation,Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#ifndef _LINUX_NTFS_MFT_H
DECL|macro|_LINUX_NTFS_MFT_H
mdefine_line|#define _LINUX_NTFS_MFT_H
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &quot;inode.h&quot;
r_extern
r_int
id|format_mft_record
c_func
(paren
id|ntfs_inode
op_star
id|ni
comma
id|MFT_RECORD
op_star
id|m
)paren
suffix:semicolon
singleline_comment|//extern int format_mft_record2(struct super_block *vfs_sb,
singleline_comment|//&t;&t;const unsigned long inum, MFT_RECORD *m);
r_extern
id|MFT_RECORD
op_star
id|map_mft_record
c_func
(paren
id|ntfs_inode
op_star
id|ni
)paren
suffix:semicolon
r_extern
r_void
id|unmap_mft_record
c_func
(paren
id|ntfs_inode
op_star
id|ni
)paren
suffix:semicolon
r_extern
id|MFT_RECORD
op_star
id|map_extent_mft_record
c_func
(paren
id|ntfs_inode
op_star
id|base_ni
comma
id|MFT_REF
id|mref
comma
id|ntfs_inode
op_star
op_star
id|ntfs_ino
)paren
suffix:semicolon
DECL|function|unmap_extent_mft_record
r_static
r_inline
r_void
id|unmap_extent_mft_record
c_func
(paren
id|ntfs_inode
op_star
id|ni
)paren
(brace
id|unmap_mft_record
c_func
(paren
id|ni
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
macro_line|#ifdef NTFS_RW
multiline_comment|/**&n; * flush_dcache_mft_record_page - flush_dcache_page() for mft records&n; * @ni:&t;&t;ntfs inode structure of mft record&n; *&n; * Call flush_dcache_page() for the page in which an mft record resides.&n; *&n; * This must be called every time an mft record is modified, just after the&n; * modification.&n; */
DECL|function|flush_dcache_mft_record_page
r_static
r_inline
r_void
id|flush_dcache_mft_record_page
c_func
(paren
id|ntfs_inode
op_star
id|ni
)paren
(brace
id|flush_dcache_page
c_func
(paren
id|ni-&gt;page
)paren
suffix:semicolon
)brace
macro_line|#endif /* NTFS_RW */
macro_line|#endif /* _LINUX_NTFS_MFT_H */
eof
