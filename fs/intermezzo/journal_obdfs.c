multiline_comment|/*&n; * Intermezzo. (C) 1998 Peter J. Braam&n; * Intermezzo. (C) 2000 Red Hat, Inc.&n; * Intermezzo. (C) 2000 Los Alamos National Laboratory&n; * Intermezzo. (C) 2000 TurboLinux, Inc.&n; * Intermezzo. (C) 2001 Mountain View Data, Inc.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/param.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/locks.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#ifdef CONFIG_OBDFS_FS
macro_line|#include /usr/src/obd/include/linux/obdfs.h
macro_line|#endif
macro_line|#include &lt;linux/intermezzo_fs.h&gt;
macro_line|#include &lt;linux/intermezzo_upcall.h&gt;
macro_line|#include &lt;linux/intermezzo_psdev.h&gt;
macro_line|#include &lt;linux/intermezzo_kml.h&gt;
macro_line|#ifdef CONFIG_OBDFS_FS
DECL|function|presto_obdfs_freespace
r_static
r_int
r_int
id|presto_obdfs_freespace
c_func
(paren
r_struct
id|presto_file_set
op_star
id|fset
comma
r_struct
id|super_block
op_star
id|sb
)paren
(brace
r_return
l_int|0x0fffff
suffix:semicolon
)brace
multiline_comment|/* start the filesystem journal operations */
DECL|function|presto_obdfs_trans_start
r_static
r_void
op_star
id|presto_obdfs_trans_start
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
r_return
(paren
r_void
op_star
)paren
l_int|1
suffix:semicolon
)brace
macro_line|#if 0
r_int
id|jblocks
suffix:semicolon
r_int
id|trunc_blks
comma
id|one_path_blks
comma
id|extra_path_blks
comma
id|extra_name_blks
comma
id|lml_blks
suffix:semicolon
id|__u32
id|avail_kmlblocks
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
l_string|&quot;ext3&quot;
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
id|avail_kmlblocks
op_assign
id|inode-&gt;i_sb-&gt;u.ext3_sb.s_es-&gt;s_free_blocks_count
suffix:semicolon
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
multiline_comment|/* Need journal space for:&n;             at least three writes to KML (two one block writes, one a path) &n;             possibly a second name (unlink, rmdir)&n;             possibly a second path (symlink, rename)&n;             a one block write to the last rcvd file &n;        */
id|trunc_blks
op_assign
id|EXT3_DATA_TRANS_BLOCKS
op_plus
l_int|1
suffix:semicolon
id|one_path_blks
op_assign
l_int|4
op_star
id|EXT3_DATA_TRANS_BLOCKS
op_plus
id|MAX_PATH_BLOCKS
c_func
(paren
id|inode
)paren
op_plus
l_int|3
suffix:semicolon
id|lml_blks
op_assign
l_int|4
op_star
id|EXT3_DATA_TRANS_BLOCKS
op_plus
id|MAX_PATH_BLOCKS
c_func
(paren
id|inode
)paren
op_plus
l_int|2
suffix:semicolon
id|extra_path_blks
op_assign
id|EXT3_DATA_TRANS_BLOCKS
op_plus
id|MAX_PATH_BLOCKS
c_func
(paren
id|inode
)paren
suffix:semicolon
id|extra_name_blks
op_assign
id|EXT3_DATA_TRANS_BLOCKS
op_plus
id|MAX_NAME_BLOCKS
c_func
(paren
id|inode
)paren
suffix:semicolon
multiline_comment|/* additional blocks appear for &quot;two pathname&quot; operations&n;           and operations involving the LML records &n;        */
r_switch
c_cond
(paren
id|op
)paren
(brace
r_case
id|PRESTO_OP_TRUNC
suffix:colon
id|jblocks
op_assign
id|one_path_blks
op_plus
id|extra_name_blks
op_plus
id|trunc_blks
op_plus
id|EXT3_DELETE_TRANS_BLOCKS
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PRESTO_OP_RELEASE
suffix:colon
multiline_comment|/* &n;                jblocks = one_path_blks + lml_blks + 2*trunc_blks; &n;                */
id|jblocks
op_assign
id|one_path_blks
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PRESTO_OP_SETATTR
suffix:colon
id|jblocks
op_assign
id|one_path_blks
op_plus
id|trunc_blks
op_plus
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PRESTO_OP_CREATE
suffix:colon
id|jblocks
op_assign
id|one_path_blks
op_plus
id|trunc_blks
op_plus
id|EXT3_DATA_TRANS_BLOCKS
op_plus
l_int|3
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PRESTO_OP_LINK
suffix:colon
id|jblocks
op_assign
id|one_path_blks
op_plus
id|trunc_blks
op_plus
id|EXT3_DATA_TRANS_BLOCKS
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PRESTO_OP_UNLINK
suffix:colon
id|jblocks
op_assign
id|one_path_blks
op_plus
id|extra_name_blks
op_plus
id|trunc_blks
op_plus
id|EXT3_DELETE_TRANS_BLOCKS
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PRESTO_OP_SYMLINK
suffix:colon
id|jblocks
op_assign
id|one_path_blks
op_plus
id|extra_path_blks
op_plus
id|trunc_blks
op_plus
id|EXT3_DATA_TRANS_BLOCKS
op_plus
l_int|5
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PRESTO_OP_MKDIR
suffix:colon
id|jblocks
op_assign
id|one_path_blks
op_plus
id|trunc_blks
op_plus
id|EXT3_DATA_TRANS_BLOCKS
op_plus
l_int|4
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PRESTO_OP_RMDIR
suffix:colon
id|jblocks
op_assign
id|one_path_blks
op_plus
id|extra_name_blks
op_plus
id|trunc_blks
op_plus
id|EXT3_DELETE_TRANS_BLOCKS
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PRESTO_OP_MKNOD
suffix:colon
id|jblocks
op_assign
id|one_path_blks
op_plus
id|trunc_blks
op_plus
id|EXT3_DATA_TRANS_BLOCKS
op_plus
l_int|3
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PRESTO_OP_RENAME
suffix:colon
id|jblocks
op_assign
id|one_path_blks
op_plus
id|extra_path_blks
op_plus
id|trunc_blks
op_plus
l_int|2
op_star
id|EXT3_DATA_TRANS_BLOCKS
op_plus
l_int|2
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PRESTO_OP_WRITE
suffix:colon
id|jblocks
op_assign
id|one_path_blks
suffix:semicolon
multiline_comment|/*  add this when we can wrap our transaction with &n;                    that of ext3_file_write (ordered writes)&n;                    +  EXT3_DATA_TRANS_BLOCKS;&n;                */
r_break
suffix:semicolon
r_default
suffix:colon
id|CDEBUG
c_func
(paren
id|D_JOURNAL
comma
l_string|&quot;invalid operation %d for journal&bslash;n&quot;
comma
id|op
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
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
r_return
id|journal_start
c_func
(paren
id|EXT3_JOURNAL
c_func
(paren
id|inode
)paren
comma
id|jblocks
)paren
suffix:semicolon
)brace
macro_line|#endif
DECL|function|presto_obdfs_trans_commit
r_void
id|presto_obdfs_trans_commit
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
macro_line|#if 0
r_if
c_cond
(paren
id|presto_no_journal
c_func
(paren
id|fset
)paren
op_logical_or
op_logical_neg
id|handle
)paren
r_return
suffix:semicolon
id|journal_stop
c_func
(paren
id|handle
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|function|presto_obdfs_journal_file_data
r_void
id|presto_obdfs_journal_file_data
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
macro_line|#ifdef EXT3_JOURNAL_DATA_FL
id|EXT3_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|i_flags
op_or_assign
id|EXT3_JOURNAL_DATA_FL
suffix:semicolon
macro_line|#else
macro_line|#warning You must have a facility to enable journaled writes for recovery!
macro_line|#endif
)brace
DECL|variable|presto_obdfs_journal_ops
r_struct
id|journal_ops
id|presto_obdfs_journal_ops
op_assign
(brace
id|tr_avail
suffix:colon
id|presto_obdfs_freespace
comma
id|tr_start
suffix:colon
id|presto_obdfs_trans_start
comma
id|tr_commit
suffix:colon
id|presto_obdfs_trans_commit
comma
id|tr_journal_data
suffix:colon
id|presto_obdfs_journal_file_data
)brace
suffix:semicolon
macro_line|#endif
eof
