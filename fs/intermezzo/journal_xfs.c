multiline_comment|/*&n; *  * Intermezzo. (C) 1998 Peter J. Braam&n; *   */
macro_line|#include &lt;linux/types.h&gt;
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
macro_line|#ifdef CONFIG_FS_XFS
macro_line|#include &lt;linux/xfs_fs.h&gt;
macro_line|#endif
macro_line|#include &lt;linux/intermezzo_fs.h&gt;
macro_line|#include &lt;linux/intermezzo_upcall.h&gt;
macro_line|#include &lt;linux/intermezzo_psdev.h&gt;
macro_line|#include &lt;linux/intermezzo_kml.h&gt;
macro_line|#include &lt;linux/intermezzo_journal.h&gt;
macro_line|#if 0
multiline_comment|/* XFS has journalling, but these functions do nothing yet... */
r_static
r_int
r_int
id|presto_xfs_freespace
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
macro_line|#if 0
id|vfs_t
op_star
id|vfsp
op_assign
id|LINVFS_GET_VFS
c_func
(paren
id|sb
)paren
suffix:semicolon
r_struct
id|statvfs_t
id|stat
suffix:semicolon
id|bhv_desc_t
op_star
id|bdp
suffix:semicolon
r_int
r_int
id|avail
suffix:semicolon
r_int
id|rc
suffix:semicolon
id|VFS_STATVFS
c_func
(paren
id|vfsp
comma
op_amp
id|stat
comma
l_int|NULL
comma
id|rc
)paren
suffix:semicolon
id|avail
op_assign
id|statp.f_bfree
suffix:semicolon
r_return
id|sbp-&gt;sb_fdblocks
suffix:semicolon
suffix:semicolon
macro_line|#endif
r_return
l_int|0x0fffffff
suffix:semicolon
)brace
multiline_comment|/* start the filesystem journal operations */
r_static
r_void
op_star
id|presto_xfs_trans_start
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
id|xfs_op
suffix:semicolon
multiline_comment|/* do a free blocks check as in journal_ext3? does anything protect&n;&t; * the space in that case or can it disappear out from under us&n;&t; * anyway? */
multiline_comment|/* copied from xfs_trans.h, skipping header maze for now */
mdefine_line|#define XFS_TRANS_SETATTR_NOT_SIZE      1
mdefine_line|#define XFS_TRANS_SETATTR_SIZE          2
mdefine_line|#define XFS_TRANS_INACTIVE              3
mdefine_line|#define XFS_TRANS_CREATE                4
mdefine_line|#define XFS_TRANS_CREATE_TRUNC          5
mdefine_line|#define XFS_TRANS_TRUNCATE_FILE         6
mdefine_line|#define XFS_TRANS_REMOVE                7
mdefine_line|#define XFS_TRANS_LINK                  8
mdefine_line|#define XFS_TRANS_RENAME                9
mdefine_line|#define XFS_TRANS_MKDIR                 10
mdefine_line|#define XFS_TRANS_RMDIR                 11
mdefine_line|#define XFS_TRANS_SYMLINK               12
multiline_comment|/* map the op onto the values for XFS so it can do reservation. if&n;&t; * we don&squot;t have enough info to differentiate between e.g. setattr&n;&t; * with or without size, what do we do? will it adjust? */
r_switch
c_cond
(paren
id|op
)paren
(brace
r_case
id|PRESTO_OP_SETATTR
suffix:colon
multiline_comment|/* or XFS_TRANS_SETATTR_NOT_SIZE? */
id|xfs_op
op_assign
id|XFS_TRANS_SETATTR_SIZE
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PRESTO_OP_CREATE
suffix:colon
multiline_comment|/* or CREATE_TRUNC? */
id|xfs_op
op_assign
id|XFS_TRANS_CREATE
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PRESTO_OP_LINK
suffix:colon
id|xfs_op
op_assign
id|XFS_TRANS_LINK
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PRESTO_OP_UNLINK
suffix:colon
id|xfs_op
op_assign
id|XFS_TRANS_REMOVE
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PRESTO_OP_SYMLINK
suffix:colon
id|xfs_op
op_assign
id|XFS_TRANS_SYMLINK
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PRESTO_OP_MKDIR
suffix:colon
id|xfs_op
op_assign
id|XFS_TRANS_MKDIR
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PRESTO_OP_RMDIR
suffix:colon
id|xfs_op
op_assign
id|XFS_TRANS_RMDIR
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PRESTO_OP_MKNOD
suffix:colon
multiline_comment|/* XXX can&squot;t find an analog for mknod? */
id|xfs_op
op_assign
id|XFS_TRANS_CREATE
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PRESTO_OP_RENAME
suffix:colon
id|xfs_op
op_assign
id|XFS_TRANS_RENAME
suffix:semicolon
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
r_return
id|xfs_trans_start
c_func
(paren
id|inode
comma
id|xfs_op
)paren
suffix:semicolon
)brace
r_static
r_void
id|presto_xfs_trans_commit
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
multiline_comment|/* assert (handle == current-&gt;j_handle) */
id|xfs_trans_stop
c_func
(paren
id|handle
)paren
suffix:semicolon
)brace
r_void
id|presto_xfs_journal_file_data
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_return
suffix:semicolon
)brace
r_struct
id|journal_ops
id|presto_xfs_journal_ops
op_assign
(brace
id|tr_avail
suffix:colon
id|presto_xfs_freespace
comma
id|tr_start
suffix:colon
id|presto_xfs_trans_start
comma
id|tr_commit
suffix:colon
id|presto_xfs_trans_commit
comma
id|tr_journal_data
suffix:colon
id|presto_xfs_journal_file_data
)brace
suffix:semicolon
macro_line|#endif /* CONFIG_XFS_FS */
eof
