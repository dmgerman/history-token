multiline_comment|/* -*- mode: c; c-basic-offset: 8; indent-tabs-mode: nil; -*-&n; * vim:expandtab:shiftwidth=8:tabstop=8:&n; *&n; *  Copyright (C) 1998 Peter J. Braam &lt;braam@clusterfs.com&gt;&n; *  Copyright (C) 2000 Red Hat, Inc.&n; *  Copyright (C) 2000 Los Alamos National Laboratory&n; *  Copyright (C) 2000 TurboLinux, Inc.&n; *  Copyright (C) 2001 Mountain View Data, Inc.&n; *&n; *   This file is part of InterMezzo, http://www.inter-mezzo.org.&n; *&n; *   InterMezzo is free software; you can redistribute it and/or&n; *   modify it under the terms of version 2 of the GNU General Public&n; *   License as published by the Free Software Foundation.&n; *&n; *   InterMezzo is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with InterMezzo; if not, write to the Free Software&n; *   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/param.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#if 0
macro_line|#if defined(CONFIG_REISERFS_FS) || defined(CONFIG_REISERFS_FS_MODULE)
macro_line|#include &lt;linux/reiserfs_fs.h&gt;
macro_line|#include &lt;linux/reiserfs_fs_sb.h&gt;
macro_line|#include &lt;linux/reiserfs_fs_i.h&gt;
macro_line|#endif
macro_line|#include &lt;linux/intermezzo_fs.h&gt;
macro_line|#include &lt;linux/intermezzo_psdev.h&gt;
macro_line|#if defined(CONFIG_REISERFS_FS) || defined(CONFIG_REISERFS_FS_MODULE)
r_static
id|loff_t
id|presto_reiserfs_freespace
c_func
(paren
r_struct
id|presto_cache
op_star
id|cache
comma
r_struct
id|super_block
op_star
id|sb
)paren
(brace
r_struct
id|reiserfs_super_block
op_star
id|rs
op_assign
id|SB_DISK_SUPER_BLOCK
(paren
id|sb
)paren
suffix:semicolon
id|loff_t
id|avail
suffix:semicolon
id|avail
op_assign
id|le32_to_cpu
c_func
(paren
id|rs-&gt;s_free_blocks
)paren
op_star
id|le16_to_cpu
c_func
(paren
id|rs-&gt;s_blocksize
)paren
suffix:semicolon
r_return
id|avail
suffix:semicolon
)brace
multiline_comment|/* start the filesystem journal operations */
r_static
r_void
op_star
id|presto_reiserfs_trans_start
c_func
(paren
r_struct
id|presto_file_set
op_star
id|fset
comma
r_struct
id|inode
op_star
id|inode
comma
r_int
id|op
)paren
(brace
r_int
id|jblocks
suffix:semicolon
id|__u32
id|avail_kmlblocks
suffix:semicolon
r_struct
id|reiserfs_transaction_handle
op_star
id|th
suffix:semicolon
id|PRESTO_ALLOC
c_func
(paren
id|th
comma
r_sizeof
(paren
op_star
id|th
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|th
)paren
(brace
id|CERROR
c_func
(paren
l_string|&quot;presto: No memory for trans handle&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|avail_kmlblocks
op_assign
id|presto_reiserfs_freespace
c_func
(paren
id|fset-&gt;fset_cache
comma
id|inode-&gt;i_sb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|presto_no_journal
c_func
(paren
id|fset
)paren
op_logical_or
id|strcmp
c_func
(paren
id|fset-&gt;fset_cache-&gt;cache_type
comma
l_string|&quot;reiserfs&quot;
)paren
)paren
(brace
id|CDEBUG
c_func
(paren
id|D_JOURNAL
comma
l_string|&quot;got cache_type &bslash;&quot;%s&bslash;&quot;&bslash;n&quot;
comma
id|fset-&gt;fset_cache-&gt;cache_type
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|avail_kmlblocks
OL
l_int|3
)paren
(brace
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|ENOSPC
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|op
op_ne
id|PRESTO_OP_UNLINK
op_logical_and
id|op
op_ne
id|PRESTO_OP_RMDIR
)paren
op_logical_and
id|avail_kmlblocks
OL
l_int|6
)paren
(brace
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|ENOSPC
)paren
suffix:semicolon
)brace
id|jblocks
op_assign
l_int|3
op_plus
id|JOURNAL_PER_BALANCE_CNT
op_star
l_int|4
suffix:semicolon
id|CDEBUG
c_func
(paren
id|D_JOURNAL
comma
l_string|&quot;creating journal handle (%d blocks)&bslash;n&quot;
comma
id|jblocks
)paren
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|journal_begin
c_func
(paren
id|th
comma
id|inode-&gt;i_sb
comma
id|jblocks
)paren
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
id|th
suffix:semicolon
)brace
r_static
r_void
id|presto_reiserfs_trans_commit
c_func
(paren
r_struct
id|presto_file_set
op_star
id|fset
comma
r_void
op_star
id|handle
)paren
(brace
r_int
id|jblocks
suffix:semicolon
id|jblocks
op_assign
l_int|3
op_plus
id|JOURNAL_PER_BALANCE_CNT
op_star
l_int|4
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|journal_end
c_func
(paren
id|handle
comma
id|fset-&gt;fset_cache-&gt;cache_sb
comma
id|jblocks
)paren
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
id|PRESTO_FREE
c_func
(paren
id|handle
comma
r_sizeof
(paren
r_struct
id|reiserfs_transaction_handle
)paren
)paren
suffix:semicolon
)brace
r_static
r_void
id|presto_reiserfs_journal_file_data
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
macro_line|#ifdef EXT3_JOURNAL_DATA_FL
id|inode-&gt;u.ext3_i.i_flags
op_or_assign
id|EXT3_JOURNAL_DATA_FL
suffix:semicolon
macro_line|#else
macro_line|#warning You must have a facility to enable journaled writes for recovery!
macro_line|#endif
)brace
r_static
r_int
id|presto_reiserfs_has_all_data
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_struct
id|journal_ops
id|presto_reiserfs_journal_ops
op_assign
(brace
dot
id|tr_all_data
op_assign
id|presto_reiserfs_has_all_data
comma
dot
id|tr_avail
op_assign
id|presto_reiserfs_freespace
comma
dot
id|tr_start
op_assign
id|presto_reiserfs_trans_start
comma
dot
id|tr_commit
op_assign
id|presto_reiserfs_trans_commit
comma
dot
id|tr_journal_data
op_assign
id|presto_reiserfs_journal_file_data
)brace
suffix:semicolon
macro_line|#endif
macro_line|#endif
eof
