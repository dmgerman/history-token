multiline_comment|/*&n; *   Copyright (c) International Business Machines Corp., 2000-2002&n; *   Portions Copyright (c) Christoph Hellwig, 2001-2002&n; *&n; *   This program is free software;  you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or &n; *   (at your option) any later version.&n; * &n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY;  without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See&n; *   the GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program;  if not, write to the Free Software &n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; */
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/buffer_head.h&gt;
macro_line|#include &quot;jfs_incore.h&quot;
macro_line|#include &quot;jfs_filsys.h&quot;
macro_line|#include &quot;jfs_imap.h&quot;
macro_line|#include &quot;jfs_extent.h&quot;
macro_line|#include &quot;jfs_unicode.h&quot;
macro_line|#include &quot;jfs_debug.h&quot;
r_extern
r_struct
id|inode_operations
id|jfs_dir_inode_operations
suffix:semicolon
r_extern
r_struct
id|inode_operations
id|jfs_file_inode_operations
suffix:semicolon
r_extern
r_struct
id|inode_operations
id|jfs_symlink_inode_operations
suffix:semicolon
r_extern
r_struct
id|file_operations
id|jfs_dir_operations
suffix:semicolon
r_extern
r_struct
id|file_operations
id|jfs_file_operations
suffix:semicolon
DECL|variable|jfs_aops
r_struct
id|address_space_operations
id|jfs_aops
suffix:semicolon
r_extern
r_int
id|freeZeroLink
c_func
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
DECL|function|jfs_iget
r_struct
id|inode
op_star
id|jfs_iget
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
id|ino_t
id|ino
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|iget_locked
c_func
(paren
id|sb
comma
id|ino
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode
op_logical_or
op_logical_neg
(paren
id|inode-&gt;i_state
op_amp
id|I_NEW
)paren
)paren
r_return
id|inode
suffix:semicolon
r_if
c_cond
(paren
id|diRead
c_func
(paren
id|inode
)paren
)paren
(brace
id|make_bad_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
id|unlock_new_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|S_ISREG
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
(brace
id|inode-&gt;i_op
op_assign
op_amp
id|jfs_file_inode_operations
suffix:semicolon
id|inode-&gt;i_fop
op_assign
op_amp
id|jfs_file_operations
suffix:semicolon
id|inode-&gt;i_mapping-&gt;a_ops
op_assign
op_amp
id|jfs_aops
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|S_ISDIR
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
(brace
id|inode-&gt;i_op
op_assign
op_amp
id|jfs_dir_inode_operations
suffix:semicolon
id|inode-&gt;i_fop
op_assign
op_amp
id|jfs_dir_operations
suffix:semicolon
id|inode-&gt;i_mapping-&gt;a_ops
op_assign
op_amp
id|jfs_aops
suffix:semicolon
id|inode-&gt;i_mapping-&gt;gfp_mask
op_assign
id|GFP_NOFS
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|S_ISLNK
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
(brace
r_if
c_cond
(paren
id|inode-&gt;i_size
OG
id|IDATASIZE
)paren
(brace
id|inode-&gt;i_op
op_assign
op_amp
id|page_symlink_inode_operations
suffix:semicolon
id|inode-&gt;i_mapping-&gt;a_ops
op_assign
op_amp
id|jfs_aops
suffix:semicolon
)brace
r_else
id|inode-&gt;i_op
op_assign
op_amp
id|jfs_symlink_inode_operations
suffix:semicolon
)brace
r_else
(brace
id|init_special_inode
c_func
(paren
id|inode
comma
id|inode-&gt;i_mode
comma
id|kdev_t_to_nr
c_func
(paren
id|inode-&gt;i_rdev
)paren
)paren
suffix:semicolon
)brace
id|unlock_new_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
r_return
id|inode
suffix:semicolon
)brace
multiline_comment|/* This define is from fs/open.c */
DECL|macro|special_file
mdefine_line|#define special_file(m) (S_ISCHR(m)||S_ISBLK(m)||S_ISFIFO(m)||S_ISSOCK(m))
multiline_comment|/*&n; * Workhorse of both fsync &amp; write_inode&n; */
DECL|function|jfs_commit_inode
r_int
id|jfs_commit_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|wait
)paren
(brace
r_int
id|rc
op_assign
l_int|0
suffix:semicolon
id|tid_t
id|tid
suffix:semicolon
r_static
r_int
id|noisy
op_assign
l_int|5
suffix:semicolon
id|jFYI
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;In jfs_commit_inode, inode = 0x%p&bslash;n&quot;
comma
id|inode
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Don&squot;t commit if inode has been committed since last being&n;&t; * marked dirty, or if it has been deleted.&n;&t; */
r_if
c_cond
(paren
id|test_cflag
c_func
(paren
id|COMMIT_Nolink
comma
id|inode
)paren
op_logical_or
op_logical_neg
id|test_cflag
c_func
(paren
id|COMMIT_Dirty
comma
id|inode
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|isReadOnly
c_func
(paren
id|inode
)paren
)paren
(brace
multiline_comment|/* kernel allows writes to devices on read-only&n;&t;&t; * partitions and may think inode is dirty&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|special_file
c_func
(paren
id|inode-&gt;i_mode
)paren
op_logical_and
id|noisy
)paren
(brace
id|jERROR
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;jfs_commit_inode(0x%p) called on &quot;
l_string|&quot;read-only volume&bslash;n&quot;
comma
id|inode
)paren
)paren
suffix:semicolon
id|jERROR
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;Is remount racy?&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|noisy
op_decrement
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
id|tid
op_assign
id|txBegin
c_func
(paren
id|inode-&gt;i_sb
comma
id|COMMIT_INODE
)paren
suffix:semicolon
id|rc
op_assign
id|txCommit
c_func
(paren
id|tid
comma
l_int|1
comma
op_amp
id|inode
comma
id|wait
ques
c_cond
id|COMMIT_SYNC
suffix:colon
l_int|0
)paren
suffix:semicolon
id|txEnd
c_func
(paren
id|tid
)paren
suffix:semicolon
r_return
op_minus
id|rc
suffix:semicolon
)brace
DECL|function|jfs_write_inode
r_void
id|jfs_write_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|wait
)paren
(brace
multiline_comment|/*&n;&t; * If COMMIT_DIRTY is not set, the inode isn&squot;t really dirty.&n;&t; * It has been committed since the last change, but was still&n;&t; * on the dirty inode list&n;&t; */
r_if
c_cond
(paren
id|test_cflag
c_func
(paren
id|COMMIT_Nolink
comma
id|inode
)paren
op_logical_or
op_logical_neg
id|test_cflag
c_func
(paren
id|COMMIT_Dirty
comma
id|inode
)paren
)paren
r_return
suffix:semicolon
id|IWRITE_LOCK
c_func
(paren
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|jfs_commit_inode
c_func
(paren
id|inode
comma
id|wait
)paren
)paren
(brace
id|jERROR
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;jfs_write_inode: jfs_commit_inode failed!&bslash;n&quot;
)paren
)paren
suffix:semicolon
)brace
id|IWRITE_UNLOCK
c_func
(paren
id|inode
)paren
suffix:semicolon
)brace
DECL|function|jfs_delete_inode
r_void
id|jfs_delete_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
id|jFYI
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;In jfs_delete_inode, inode = 0x%p&bslash;n&quot;
comma
id|inode
)paren
)paren
suffix:semicolon
id|IWRITE_LOCK
c_func
(paren
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|test_cflag
c_func
(paren
id|COMMIT_Freewmap
comma
id|inode
)paren
)paren
id|freeZeroLink
c_func
(paren
id|inode
)paren
suffix:semicolon
id|diFree
c_func
(paren
id|inode
)paren
suffix:semicolon
id|IWRITE_UNLOCK
c_func
(paren
id|inode
)paren
suffix:semicolon
id|clear_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
)brace
DECL|function|jfs_dirty_inode
r_void
id|jfs_dirty_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_static
r_int
id|noisy
op_assign
l_int|5
suffix:semicolon
r_if
c_cond
(paren
id|isReadOnly
c_func
(paren
id|inode
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|special_file
c_func
(paren
id|inode-&gt;i_mode
)paren
op_logical_and
id|noisy
)paren
(brace
multiline_comment|/* kernel allows writes to devices on read-only&n;&t;&t;&t; * partitions and may try to mark inode dirty&n;&t;&t;&t; */
id|jERROR
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;jfs_dirty_inode called on &quot;
l_string|&quot;read-only volume&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|jERROR
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;Is remount racy?&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|noisy
op_decrement
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
id|set_cflag
c_func
(paren
id|COMMIT_Dirty
comma
id|inode
)paren
suffix:semicolon
)brace
DECL|function|jfs_get_block
r_static
r_int
id|jfs_get_block
c_func
(paren
r_struct
id|inode
op_star
id|ip
comma
id|sector_t
id|lblock
comma
r_struct
id|buffer_head
op_star
id|bh_result
comma
r_int
id|create
)paren
(brace
id|s64
id|lblock64
op_assign
id|lblock
suffix:semicolon
r_int
id|no_size_check
op_assign
l_int|0
suffix:semicolon
r_int
id|rc
op_assign
l_int|0
suffix:semicolon
r_int
id|take_locks
suffix:semicolon
id|xad_t
id|xad
suffix:semicolon
id|s64
id|xaddr
suffix:semicolon
r_int
id|xflag
suffix:semicolon
id|s32
id|xlen
suffix:semicolon
multiline_comment|/*&n;&t; * If this is a special inode (imap, dmap) or directory,&n;&t; * the lock should already be taken&n;&t; */
id|take_locks
op_assign
(paren
(paren
id|JFS_IP
c_func
(paren
id|ip
)paren
op_member_access_from_pointer
id|fileset
op_ne
id|AGGREGATE_I
)paren
op_logical_and
op_logical_neg
id|S_ISDIR
c_func
(paren
id|ip-&gt;i_mode
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Take appropriate lock on inode&n;&t; */
r_if
c_cond
(paren
id|take_locks
)paren
(brace
r_if
c_cond
(paren
id|create
)paren
id|IWRITE_LOCK
c_func
(paren
id|ip
)paren
suffix:semicolon
r_else
id|IREAD_LOCK
c_func
(paren
id|ip
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * A directory&squot;s &quot;data&quot; is the inode index table, but i_size is the&n;&t; * size of the d-tree, so don&squot;t check the offset against i_size&n;&t; */
r_if
c_cond
(paren
id|S_ISDIR
c_func
(paren
id|ip-&gt;i_mode
)paren
)paren
id|no_size_check
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
(paren
id|no_size_check
op_logical_or
(paren
(paren
id|lblock64
op_lshift
id|ip-&gt;i_sb-&gt;s_blocksize_bits
)paren
OL
id|ip-&gt;i_size
)paren
)paren
op_logical_and
(paren
id|xtLookup
(paren
id|ip
comma
id|lblock64
comma
l_int|1
comma
op_amp
id|xflag
comma
op_amp
id|xaddr
comma
op_amp
id|xlen
comma
id|no_size_check
)paren
op_eq
l_int|0
)paren
op_logical_and
id|xlen
)paren
(brace
r_if
c_cond
(paren
id|xflag
op_amp
id|XAD_NOTRECORDED
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|create
)paren
multiline_comment|/*&n;&t;&t;&t;&t; * Allocated but not recorded, read treats&n;&t;&t;&t;&t; * this as a hole&n;&t;&t;&t;&t; */
r_goto
id|unlock
suffix:semicolon
macro_line|#ifdef _JFS_4K
id|XADoffset
c_func
(paren
op_amp
id|xad
comma
id|lblock64
)paren
suffix:semicolon
id|XADlength
c_func
(paren
op_amp
id|xad
comma
id|xlen
)paren
suffix:semicolon
id|XADaddress
c_func
(paren
op_amp
id|xad
comma
id|xaddr
)paren
suffix:semicolon
macro_line|#else&t;&t;&t;&t;/* _JFS_4K */
multiline_comment|/*&n;&t;&t;&t; * As long as block size = 4K, this isn&squot;t a problem.&n;&t;&t;&t; * We should mark the whole page not ABNR, but how&n;&t;&t;&t; * will we know to mark the other blocks BH_New?&n;&t;&t;&t; */
id|BUG
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif&t;&t;&t;&t;/* _JFS_4K */
id|rc
op_assign
id|extRecord
c_func
(paren
id|ip
comma
op_amp
id|xad
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
r_goto
id|unlock
suffix:semicolon
id|set_buffer_new
c_func
(paren
id|bh_result
)paren
suffix:semicolon
)brace
id|map_bh
c_func
(paren
id|bh_result
comma
id|ip-&gt;i_sb
comma
id|xaddr
)paren
suffix:semicolon
r_goto
id|unlock
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|create
)paren
r_goto
id|unlock
suffix:semicolon
multiline_comment|/*&n;&t; * Allocate a new block&n;&t; */
macro_line|#ifdef _JFS_4K
r_if
c_cond
(paren
(paren
id|rc
op_assign
id|extHint
c_func
(paren
id|ip
comma
id|lblock64
op_lshift
id|ip-&gt;i_sb-&gt;s_blocksize_bits
comma
op_amp
id|xad
)paren
)paren
)paren
r_goto
id|unlock
suffix:semicolon
id|rc
op_assign
id|extAlloc
c_func
(paren
id|ip
comma
l_int|1
comma
id|lblock64
comma
op_amp
id|xad
comma
id|FALSE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
r_goto
id|unlock
suffix:semicolon
id|set_buffer_new
c_func
(paren
id|bh_result
)paren
suffix:semicolon
id|map_bh
c_func
(paren
id|bh_result
comma
id|ip-&gt;i_sb
comma
id|addressXAD
c_func
(paren
op_amp
id|xad
)paren
)paren
suffix:semicolon
macro_line|#else&t;&t;&t;&t;/* _JFS_4K */
multiline_comment|/*&n;&t; * We need to do whatever it takes to keep all but the last buffers&n;&t; * in 4K pages - see jfs_write.c&n;&t; */
id|BUG
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif&t;&t;&t;&t;/* _JFS_4K */
id|unlock
suffix:colon
multiline_comment|/*&n;&t; * Release lock on inode&n;&t; */
r_if
c_cond
(paren
id|take_locks
)paren
(brace
r_if
c_cond
(paren
id|create
)paren
id|IWRITE_UNLOCK
c_func
(paren
id|ip
)paren
suffix:semicolon
r_else
id|IREAD_UNLOCK
c_func
(paren
id|ip
)paren
suffix:semicolon
)brace
r_return
op_minus
id|rc
suffix:semicolon
)brace
DECL|function|jfs_writepage
r_static
r_int
id|jfs_writepage
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
(brace
r_return
id|block_write_full_page
c_func
(paren
id|page
comma
id|jfs_get_block
)paren
suffix:semicolon
)brace
DECL|function|jfs_readpage
r_static
r_int
id|jfs_readpage
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_struct
id|page
op_star
id|page
)paren
(brace
r_return
id|block_read_full_page
c_func
(paren
id|page
comma
id|jfs_get_block
)paren
suffix:semicolon
)brace
DECL|function|jfs_prepare_write
r_static
r_int
id|jfs_prepare_write
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_struct
id|page
op_star
id|page
comma
r_int
id|from
comma
r_int
id|to
)paren
(brace
r_return
id|block_prepare_write
c_func
(paren
id|page
comma
id|from
comma
id|to
comma
id|jfs_get_block
)paren
suffix:semicolon
)brace
DECL|function|jfs_bmap
r_static
r_int
id|jfs_bmap
c_func
(paren
r_struct
id|address_space
op_star
id|mapping
comma
r_int
id|block
)paren
(brace
r_return
id|generic_block_bmap
c_func
(paren
id|mapping
comma
id|block
comma
id|jfs_get_block
)paren
suffix:semicolon
)brace
DECL|function|jfs_direct_IO
r_static
r_int
id|jfs_direct_IO
c_func
(paren
r_int
id|rw
comma
r_struct
id|inode
op_star
id|inode
comma
r_char
op_star
id|buf
comma
id|loff_t
id|offset
comma
r_int
id|count
)paren
(brace
r_return
id|generic_direct_IO
c_func
(paren
id|rw
comma
id|inode
comma
id|buf
comma
id|offset
comma
id|count
comma
id|jfs_get_block
)paren
suffix:semicolon
)brace
DECL|variable|jfs_aops
r_struct
id|address_space_operations
id|jfs_aops
op_assign
(brace
dot
id|readpage
op_assign
id|jfs_readpage
comma
dot
id|writepage
op_assign
id|jfs_writepage
comma
dot
id|sync_page
op_assign
id|block_sync_page
comma
dot
id|prepare_write
op_assign
id|jfs_prepare_write
comma
dot
id|commit_write
op_assign
id|generic_commit_write
comma
dot
id|bmap
op_assign
id|jfs_bmap
comma
dot
id|direct_IO
op_assign
id|jfs_direct_IO
comma
)brace
suffix:semicolon
eof
