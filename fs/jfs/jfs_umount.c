multiline_comment|/*&n; *   Copyright (C) International Business Machines Corp., 2000-2004&n; *&n; *   This program is free software;  you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or &n; *   (at your option) any later version.&n; * &n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY;  without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See&n; *   the GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program;  if not, write to the Free Software &n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; */
multiline_comment|/*&n; *&t;jfs_umount.c&n; *&n; * note: file system in transition to aggregate/fileset:&n; * (ref. jfs_mount.c)&n; *&n; * file system unmount is interpreted as mount of the single/only &n; * fileset in the aggregate and, if unmount of the last fileset, &n; * as unmount of the aggerate;&n; */
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &quot;jfs_incore.h&quot;
macro_line|#include &quot;jfs_filsys.h&quot;
macro_line|#include &quot;jfs_superblock.h&quot;
macro_line|#include &quot;jfs_dmap.h&quot;
macro_line|#include &quot;jfs_imap.h&quot;
macro_line|#include &quot;jfs_metapage.h&quot;
macro_line|#include &quot;jfs_debug.h&quot;
multiline_comment|/*&n; * NAME:&t;jfs_umount(vfsp, flags, crp)&n; *&n; * FUNCTION:&t;vfs_umount()&n; *&n; * PARAMETERS:&t;vfsp&t;- virtual file system pointer&n; *&t;&t;flags&t;- unmount for shutdown&n; *&t;&t;crp&t;- credential&n; *&n; * RETURN :&t;EBUSY&t;- device has open files&n; */
DECL|function|jfs_umount
r_int
id|jfs_umount
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
r_struct
id|address_space
op_star
id|bdev_mapping
op_assign
id|sb-&gt;s_bdev-&gt;bd_inode-&gt;i_mapping
suffix:semicolon
r_struct
id|jfs_sb_info
op_star
id|sbi
op_assign
id|JFS_SBI
c_func
(paren
id|sb
)paren
suffix:semicolon
r_struct
id|inode
op_star
id|ipbmap
op_assign
id|sbi-&gt;ipbmap
suffix:semicolon
r_struct
id|inode
op_star
id|ipimap
op_assign
id|sbi-&gt;ipimap
suffix:semicolon
r_struct
id|inode
op_star
id|ipaimap
op_assign
id|sbi-&gt;ipaimap
suffix:semicolon
r_struct
id|inode
op_star
id|ipaimap2
op_assign
id|sbi-&gt;ipaimap2
suffix:semicolon
r_struct
id|jfs_log
op_star
id|log
suffix:semicolon
r_int
id|rc
op_assign
l_int|0
suffix:semicolon
id|jfs_info
c_func
(paren
l_string|&quot;UnMount JFS: sb:0x%p&quot;
comma
id|sb
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *      update superblock and close log &n;&t; *&n;&t; * if mounted read-write and log based recovery was enabled&n;&t; */
r_if
c_cond
(paren
(paren
id|log
op_assign
id|sbi-&gt;log
)paren
)paren
multiline_comment|/*&n;&t;&t; * Wait for outstanding transactions to be written to log: &n;&t;&t; */
id|jfs_flush_journal
c_func
(paren
id|log
comma
l_int|2
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * close fileset inode allocation map (aka fileset inode)&n;&t; */
id|diUnmount
c_func
(paren
id|ipimap
comma
l_int|0
)paren
suffix:semicolon
id|diFreeSpecial
c_func
(paren
id|ipimap
)paren
suffix:semicolon
id|sbi-&gt;ipimap
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/*&n;&t; * close secondary aggregate inode allocation map&n;&t; */
id|ipaimap2
op_assign
id|sbi-&gt;ipaimap2
suffix:semicolon
r_if
c_cond
(paren
id|ipaimap2
)paren
(brace
id|diUnmount
c_func
(paren
id|ipaimap2
comma
l_int|0
)paren
suffix:semicolon
id|diFreeSpecial
c_func
(paren
id|ipaimap2
)paren
suffix:semicolon
id|sbi-&gt;ipaimap2
op_assign
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * close aggregate inode allocation map&n;&t; */
id|ipaimap
op_assign
id|sbi-&gt;ipaimap
suffix:semicolon
id|diUnmount
c_func
(paren
id|ipaimap
comma
l_int|0
)paren
suffix:semicolon
id|diFreeSpecial
c_func
(paren
id|ipaimap
)paren
suffix:semicolon
id|sbi-&gt;ipaimap
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/*&n;&t; * close aggregate block allocation map&n;&t; */
id|dbUnmount
c_func
(paren
id|ipbmap
comma
l_int|0
)paren
suffix:semicolon
id|diFreeSpecial
c_func
(paren
id|ipbmap
)paren
suffix:semicolon
id|sbi-&gt;ipimap
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/*&n;&t; * Make sure all metadata makes it to disk before we mark&n;&t; * the superblock as clean&n;&t; */
id|filemap_fdatawrite
c_func
(paren
id|bdev_mapping
)paren
suffix:semicolon
id|filemap_fdatawait
c_func
(paren
id|bdev_mapping
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * ensure all file system file pages are propagated to their&n;&t; * home blocks on disk (and their in-memory buffer pages are &n;&t; * invalidated) BEFORE updating file system superblock state&n;&t; * (to signify file system is unmounted cleanly, and thus in &n;&t; * consistent state) and log superblock active file system &n;&t; * list (to signify skip logredo()).&n;&t; */
r_if
c_cond
(paren
id|log
)paren
(brace
multiline_comment|/* log = NULL if read-only mount */
id|rc
op_assign
id|updateSuper
c_func
(paren
id|sb
comma
id|FM_CLEAN
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * close log: &n;&t;&t; *&n;&t;&t; * remove file system from log active file system list.&n;&t;&t; */
id|rc
op_assign
id|lmLogClose
c_func
(paren
id|sb
)paren
suffix:semicolon
)brace
id|jfs_info
c_func
(paren
l_string|&quot;UnMount JFS Complete: rc = %d&quot;
comma
id|rc
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
DECL|function|jfs_umount_rw
r_int
id|jfs_umount_rw
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
r_struct
id|address_space
op_star
id|bdev_mapping
op_assign
id|sb-&gt;s_bdev-&gt;bd_inode-&gt;i_mapping
suffix:semicolon
r_struct
id|jfs_sb_info
op_star
id|sbi
op_assign
id|JFS_SBI
c_func
(paren
id|sb
)paren
suffix:semicolon
r_struct
id|jfs_log
op_star
id|log
op_assign
id|sbi-&gt;log
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|log
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * close log: &n;&t; *&n;&t; * remove file system from log active file system list.&n;&t; */
id|jfs_flush_journal
c_func
(paren
id|log
comma
l_int|2
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Make sure all metadata makes it to disk&n;&t; */
id|dbSync
c_func
(paren
id|sbi-&gt;ipbmap
)paren
suffix:semicolon
id|diSync
c_func
(paren
id|sbi-&gt;ipimap
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Note that we have to do this even if sync_blockdev() will&n;&t; * do exactly the same a few instructions later:  We can&squot;t&n;&t; * mark the superblock clean before everything is flushed to&n;&t; * disk.&n;&t; */
id|filemap_fdatawrite
c_func
(paren
id|bdev_mapping
)paren
suffix:semicolon
id|filemap_fdatawait
c_func
(paren
id|bdev_mapping
)paren
suffix:semicolon
id|updateSuper
c_func
(paren
id|sb
comma
id|FM_CLEAN
)paren
suffix:semicolon
r_return
id|lmLogClose
c_func
(paren
id|sb
)paren
suffix:semicolon
)brace
eof
