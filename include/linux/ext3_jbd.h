multiline_comment|/*&n; * linux/include/linux/ext3_jbd.h&n; *&n; * Written by Stephen C. Tweedie &lt;sct@redhat.com&gt;, 1999&n; *&n; * Copyright 1998--1999 Red Hat corp --- All Rights Reserved&n; *&n; * This file is part of the Linux kernel and is made available under&n; * the terms of the GNU General Public License, version 2, or at your&n; * option, any later version, incorporated herein by reference.&n; *&n; * Ext3-specific journaling extensions.&n; */
macro_line|#ifndef _LINUX_EXT3_JBD_H
DECL|macro|_LINUX_EXT3_JBD_H
mdefine_line|#define _LINUX_EXT3_JBD_H
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/jbd.h&gt;
macro_line|#include &lt;linux/ext3_fs.h&gt;
DECL|macro|EXT3_JOURNAL
mdefine_line|#define EXT3_JOURNAL(inode)&t;(EXT3_SB((inode)-&gt;i_sb)-&gt;s_journal)
multiline_comment|/* Define the number of blocks we need to account to a transaction to&n; * modify one block of data.&n; * &n; * We may have to touch one inode, one bitmap buffer, up to three&n; * indirection blocks, the group and superblock summaries, and the data&n; * block to complete the transaction.  */
DECL|macro|EXT3_SINGLEDATA_TRANS_BLOCKS
mdefine_line|#define EXT3_SINGLEDATA_TRANS_BLOCKS&t;8U
multiline_comment|/* Extended attributes may touch two data buffers, two bitmap buffers,&n; * and two group and summaries. */
DECL|macro|EXT3_XATTR_TRANS_BLOCKS
mdefine_line|#define EXT3_XATTR_TRANS_BLOCKS&t;&t;8
multiline_comment|/* Define the minimum size for a transaction which modifies data.  This&n; * needs to take into account the fact that we may end up modifying two&n; * quota files too (one for the group, one for the user quota).  The&n; * superblock only gets updated once, of course, so don&squot;t bother&n; * counting that again for the quota updates. */
DECL|macro|EXT3_DATA_TRANS_BLOCKS
mdefine_line|#define EXT3_DATA_TRANS_BLOCKS&t;&t;(3 * EXT3_SINGLEDATA_TRANS_BLOCKS + &bslash;&n;&t;&t;&t;&t;&t; EXT3_XATTR_TRANS_BLOCKS - 2)
r_extern
r_int
id|ext3_writepage_trans_blocks
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
suffix:semicolon
multiline_comment|/* Delete operations potentially hit one directory&squot;s namespace plus an&n; * entire inode, plus arbitrary amounts of bitmap/indirection data.  Be&n; * generous.  We can grow the delete transaction later if necessary. */
DECL|macro|EXT3_DELETE_TRANS_BLOCKS
mdefine_line|#define EXT3_DELETE_TRANS_BLOCKS&t;(2 * EXT3_DATA_TRANS_BLOCKS + 64)
multiline_comment|/* Define an arbitrary limit for the amount of data we will anticipate&n; * writing to any given transaction.  For unbounded transactions such as&n; * write(2) and truncate(2) we can write more than this, but we always&n; * start off at the maximum transaction size and grow the transaction&n; * optimistically as we go. */
DECL|macro|EXT3_MAX_TRANS_DATA
mdefine_line|#define EXT3_MAX_TRANS_DATA&t;&t;64U
multiline_comment|/* We break up a large truncate or write transaction once the handle&squot;s&n; * buffer credits gets this low, we need either to extend the&n; * transaction or to start a new one.  Reserve enough space here for&n; * inode, bitmap, superblock, group and indirection updates for at least&n; * one block, plus two quota updates.  Quota allocations are not&n; * needed. */
DECL|macro|EXT3_RESERVE_TRANS_BLOCKS
mdefine_line|#define EXT3_RESERVE_TRANS_BLOCKS&t;12U
DECL|macro|EXT3_INDEX_EXTRA_TRANS_BLOCKS
mdefine_line|#define EXT3_INDEX_EXTRA_TRANS_BLOCKS&t;8
r_int
id|ext3_mark_iloc_dirty
c_func
(paren
id|handle_t
op_star
id|handle
comma
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|ext3_iloc
op_star
id|iloc
)paren
suffix:semicolon
multiline_comment|/* &n; * On success, We end up with an outstanding reference count against&n; * iloc-&gt;bh.  This _must_ be cleaned up later. &n; */
r_int
id|ext3_reserve_inode_write
c_func
(paren
id|handle_t
op_star
id|handle
comma
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|ext3_iloc
op_star
id|iloc
)paren
suffix:semicolon
r_int
id|ext3_mark_inode_dirty
c_func
(paren
id|handle_t
op_star
id|handle
comma
r_struct
id|inode
op_star
id|inode
)paren
suffix:semicolon
multiline_comment|/*&n; * Wrapper functions with which ext3 calls into JBD.  The intent here is&n; * to allow these to be turned into appropriate stubs so ext3 can control&n; * ext2 filesystems, so ext2+ext3 systems only nee one fs.  This work hasn&squot;t&n; * been done yet.&n; */
DECL|function|ext3_journal_abort_handle
r_static
r_inline
r_void
id|ext3_journal_abort_handle
c_func
(paren
r_const
r_char
op_star
id|caller
comma
r_const
r_char
op_star
id|err_fn
comma
r_struct
id|buffer_head
op_star
id|bh
comma
id|handle_t
op_star
id|handle
comma
r_int
id|err
)paren
(brace
r_char
id|nbuf
(braket
l_int|16
)braket
suffix:semicolon
r_const
r_char
op_star
id|errstr
op_assign
id|ext3_decode_error
c_func
(paren
l_int|NULL
comma
id|err
comma
id|nbuf
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: aborting transaction: %s in %s&quot;
comma
id|caller
comma
id|errstr
comma
id|err_fn
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bh
)paren
id|BUFFER_TRACE
c_func
(paren
id|bh
comma
l_string|&quot;abort&quot;
)paren
suffix:semicolon
id|journal_abort_handle
c_func
(paren
id|handle
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|handle-&gt;h_err
)paren
id|handle-&gt;h_err
op_assign
id|err
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|__ext3_journal_get_undo_access
id|__ext3_journal_get_undo_access
c_func
(paren
r_const
r_char
op_star
id|where
comma
id|handle_t
op_star
id|handle
comma
r_struct
id|buffer_head
op_star
id|bh
)paren
(brace
r_int
id|err
op_assign
id|journal_get_undo_access
c_func
(paren
id|handle
comma
id|bh
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
id|ext3_journal_abort_handle
c_func
(paren
id|where
comma
id|__FUNCTION__
comma
id|bh
comma
id|handle
comma
id|err
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|__ext3_journal_get_write_access
id|__ext3_journal_get_write_access
c_func
(paren
r_const
r_char
op_star
id|where
comma
id|handle_t
op_star
id|handle
comma
r_struct
id|buffer_head
op_star
id|bh
)paren
(brace
r_int
id|err
op_assign
id|journal_get_write_access
c_func
(paren
id|handle
comma
id|bh
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
id|ext3_journal_abort_handle
c_func
(paren
id|where
comma
id|__FUNCTION__
comma
id|bh
comma
id|handle
comma
id|err
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|ext3_journal_forget
id|ext3_journal_forget
c_func
(paren
id|handle_t
op_star
id|handle
comma
r_struct
id|buffer_head
op_star
id|bh
)paren
(brace
id|journal_forget
c_func
(paren
id|handle
comma
id|bh
)paren
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|__ext3_journal_revoke
id|__ext3_journal_revoke
c_func
(paren
r_const
r_char
op_star
id|where
comma
id|handle_t
op_star
id|handle
comma
r_int
r_int
id|blocknr
comma
r_struct
id|buffer_head
op_star
id|bh
)paren
(brace
r_int
id|err
op_assign
id|journal_revoke
c_func
(paren
id|handle
comma
id|blocknr
comma
id|bh
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
id|ext3_journal_abort_handle
c_func
(paren
id|where
comma
id|__FUNCTION__
comma
id|bh
comma
id|handle
comma
id|err
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|__ext3_journal_get_create_access
id|__ext3_journal_get_create_access
c_func
(paren
r_const
r_char
op_star
id|where
comma
id|handle_t
op_star
id|handle
comma
r_struct
id|buffer_head
op_star
id|bh
)paren
(brace
r_int
id|err
op_assign
id|journal_get_create_access
c_func
(paren
id|handle
comma
id|bh
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
id|ext3_journal_abort_handle
c_func
(paren
id|where
comma
id|__FUNCTION__
comma
id|bh
comma
id|handle
comma
id|err
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|__ext3_journal_dirty_metadata
id|__ext3_journal_dirty_metadata
c_func
(paren
r_const
r_char
op_star
id|where
comma
id|handle_t
op_star
id|handle
comma
r_struct
id|buffer_head
op_star
id|bh
)paren
(brace
r_int
id|err
op_assign
id|journal_dirty_metadata
c_func
(paren
id|handle
comma
id|bh
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
id|ext3_journal_abort_handle
c_func
(paren
id|where
comma
id|__FUNCTION__
comma
id|bh
comma
id|handle
comma
id|err
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|macro|ext3_journal_get_undo_access
mdefine_line|#define ext3_journal_get_undo_access(handle, bh) &bslash;&n;&t;__ext3_journal_get_undo_access(__FUNCTION__, (handle), (bh))
DECL|macro|ext3_journal_get_write_access
mdefine_line|#define ext3_journal_get_write_access(handle, bh) &bslash;&n;&t;__ext3_journal_get_write_access(__FUNCTION__, (handle), (bh))
DECL|macro|ext3_journal_revoke
mdefine_line|#define ext3_journal_revoke(handle, blocknr, bh) &bslash;&n;&t;__ext3_journal_revoke(__FUNCTION__, (handle), (blocknr), (bh))
DECL|macro|ext3_journal_get_create_access
mdefine_line|#define ext3_journal_get_create_access(handle, bh) &bslash;&n;&t;__ext3_journal_get_create_access(__FUNCTION__, (handle), (bh))
DECL|macro|ext3_journal_dirty_metadata
mdefine_line|#define ext3_journal_dirty_metadata(handle, bh) &bslash;&n;&t;__ext3_journal_dirty_metadata(__FUNCTION__, (handle), (bh))
multiline_comment|/* &n; * Wrappers for journal_start/end.&n; *&n; * The only special thing we need to do here is to make sure that all&n; * journal_end calls result in the superblock being marked dirty, so&n; * that sync() will call the filesystem&squot;s write_super callback if&n; * appropriate. &n; */
DECL|function|ext3_journal_start
r_static
r_inline
id|handle_t
op_star
id|ext3_journal_start
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|nblocks
)paren
(brace
id|journal_t
op_star
id|journal
suffix:semicolon
r_if
c_cond
(paren
id|inode-&gt;i_sb-&gt;s_flags
op_amp
id|MS_RDONLY
)paren
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|EROFS
)paren
suffix:semicolon
multiline_comment|/* Special case here: if the journal has aborted behind our&n;&t; * backs (eg. EIO in the commit thread), then we still need to&n;&t; * take the FS itself readonly cleanly. */
id|journal
op_assign
id|EXT3_JOURNAL
c_func
(paren
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|is_journal_aborted
c_func
(paren
id|journal
)paren
)paren
(brace
id|ext3_abort
c_func
(paren
id|inode-&gt;i_sb
comma
id|__FUNCTION__
comma
l_string|&quot;Detected aborted journal&quot;
)paren
suffix:semicolon
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|EROFS
)paren
suffix:semicolon
)brace
r_return
id|journal_start
c_func
(paren
id|journal
comma
id|nblocks
)paren
suffix:semicolon
)brace
r_static
r_inline
id|handle_t
op_star
DECL|function|ext3_journal_try_start
id|ext3_journal_try_start
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|nblocks
)paren
(brace
r_if
c_cond
(paren
id|inode-&gt;i_sb-&gt;s_flags
op_amp
id|MS_RDONLY
)paren
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|EROFS
)paren
suffix:semicolon
r_return
id|journal_try_start
c_func
(paren
id|EXT3_JOURNAL
c_func
(paren
id|inode
)paren
comma
id|nblocks
)paren
suffix:semicolon
)brace
multiline_comment|/* &n; * The only special thing we need to do here is to make sure that all&n; * journal_stop calls result in the superblock being marked dirty, so&n; * that sync() will call the filesystem&squot;s write_super callback if&n; * appropriate. &n; */
DECL|function|__ext3_journal_stop
r_static
r_inline
r_int
id|__ext3_journal_stop
c_func
(paren
r_const
r_char
op_star
id|where
comma
id|handle_t
op_star
id|handle
comma
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_int
id|err
op_assign
id|handle-&gt;h_err
suffix:semicolon
r_int
id|rc
op_assign
id|journal_stop
c_func
(paren
id|handle
)paren
suffix:semicolon
id|inode-&gt;i_sb-&gt;s_dirt
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|err
)paren
id|err
op_assign
id|rc
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
id|__ext3_std_error
c_func
(paren
id|inode-&gt;i_sb
comma
id|where
comma
id|err
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|macro|ext3_journal_stop
mdefine_line|#define ext3_journal_stop(handle, inode) &bslash;&n;&t;__ext3_journal_stop(__FUNCTION__, (handle), (inode))
DECL|function|ext3_journal_current_handle
r_static
r_inline
id|handle_t
op_star
id|ext3_journal_current_handle
c_func
(paren
r_void
)paren
(brace
r_return
id|journal_current_handle
c_func
(paren
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|ext3_log_start_commit
id|ext3_log_start_commit
c_func
(paren
id|journal_t
op_star
id|journal
comma
id|transaction_t
op_star
id|transaction
)paren
(brace
id|log_start_commit
c_func
(paren
id|journal
comma
id|transaction
)paren
suffix:semicolon
)brace
DECL|function|ext3_log_wait_commit
r_static
r_inline
r_void
id|ext3_log_wait_commit
c_func
(paren
id|journal_t
op_star
id|journal
comma
id|tid_t
id|tid
)paren
(brace
id|log_wait_commit
c_func
(paren
id|journal
comma
id|tid
)paren
suffix:semicolon
)brace
DECL|function|ext3_journal_extend
r_static
r_inline
r_int
id|ext3_journal_extend
c_func
(paren
id|handle_t
op_star
id|handle
comma
r_int
id|nblocks
)paren
(brace
r_return
id|journal_extend
c_func
(paren
id|handle
comma
id|nblocks
)paren
suffix:semicolon
)brace
DECL|function|ext3_journal_restart
r_static
r_inline
r_int
id|ext3_journal_restart
c_func
(paren
id|handle_t
op_star
id|handle
comma
r_int
id|nblocks
)paren
(brace
r_return
id|journal_restart
c_func
(paren
id|handle
comma
id|nblocks
)paren
suffix:semicolon
)brace
DECL|function|ext3_journal_blocks_per_page
r_static
r_inline
r_int
id|ext3_journal_blocks_per_page
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_return
id|journal_blocks_per_page
c_func
(paren
id|inode
)paren
suffix:semicolon
)brace
DECL|function|ext3_journal_force_commit
r_static
r_inline
r_int
id|ext3_journal_force_commit
c_func
(paren
id|journal_t
op_star
id|journal
)paren
(brace
r_return
id|journal_force_commit
c_func
(paren
id|journal
)paren
suffix:semicolon
)brace
multiline_comment|/* super.c */
r_int
id|ext3_force_commit
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
suffix:semicolon
DECL|function|ext3_should_journal_data
r_static
r_inline
r_int
id|ext3_should_journal_data
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|S_ISREG
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|test_opt
c_func
(paren
id|inode-&gt;i_sb
comma
id|DATA_FLAGS
)paren
op_eq
id|EXT3_MOUNT_JOURNAL_DATA
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|EXT3_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|i_flags
op_amp
id|EXT3_JOURNAL_DATA_FL
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ext3_should_order_data
r_static
r_inline
r_int
id|ext3_should_order_data
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_return
(paren
id|test_opt
c_func
(paren
id|inode-&gt;i_sb
comma
id|DATA_FLAGS
)paren
op_eq
id|EXT3_MOUNT_ORDERED_DATA
)paren
suffix:semicolon
)brace
DECL|function|ext3_should_writeback_data
r_static
r_inline
r_int
id|ext3_should_writeback_data
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_return
op_logical_neg
id|ext3_should_journal_data
c_func
(paren
id|inode
)paren
op_logical_and
op_logical_neg
id|ext3_should_order_data
c_func
(paren
id|inode
)paren
suffix:semicolon
)brace
macro_line|#endif&t;/* _LINUX_EXT3_JBD_H */
eof
