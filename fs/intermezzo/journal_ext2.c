multiline_comment|/*&n; * Intermezzo. (C) 1998 Peter J. Braam&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/locks.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/ext2_fs.h&gt; 
macro_line|#include &lt;linux/intermezzo_fs.h&gt;
macro_line|#include &lt;linux/intermezzo_upcall.h&gt;
macro_line|#include &lt;linux/intermezzo_psdev.h&gt;
macro_line|#include &lt;linux/intermezzo_kml.h&gt;
macro_line|#if defined(CONFIG_EXT2_FS)
multiline_comment|/* EXT2 has no journalling, so these functions do nothing */
DECL|function|presto_e2_freespace
r_static
id|loff_t
id|presto_e2_freespace
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
r_int
r_int
id|freebl
op_assign
id|le32_to_cpu
c_func
(paren
id|sb-&gt;u.ext2_sb.s_es-&gt;s_free_blocks_count
)paren
suffix:semicolon
r_int
r_int
id|avail
op_assign
id|freebl
op_minus
id|le32_to_cpu
c_func
(paren
id|sb-&gt;u.ext2_sb.s_es-&gt;s_r_blocks_count
)paren
suffix:semicolon
r_return
(paren
id|avail
op_lshift
id|EXT2_BLOCK_SIZE_BITS
c_func
(paren
id|sb
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* start the filesystem journal operations */
DECL|function|presto_e2_trans_start
r_static
r_void
op_star
id|presto_e2_trans_start
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
l_string|&quot;ext2&quot;
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
id|avail_kmlblocks
op_assign
id|inode-&gt;i_sb-&gt;u.ext2_sb.s_es-&gt;s_free_blocks_count
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
r_return
(paren
r_void
op_star
)paren
l_int|1
suffix:semicolon
)brace
DECL|function|presto_e2_trans_commit
r_static
r_void
id|presto_e2_trans_commit
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
r_do
(brace
)brace
r_while
c_loop
(paren
l_int|0
)paren
suffix:semicolon
)brace
DECL|variable|presto_ext2_journal_ops
r_struct
id|journal_ops
id|presto_ext2_journal_ops
op_assign
(brace
id|tr_avail
suffix:colon
id|presto_e2_freespace
comma
id|tr_start
suffix:colon
id|presto_e2_trans_start
comma
id|tr_commit
suffix:colon
id|presto_e2_trans_commit
comma
id|tr_journal_data
suffix:colon
l_int|NULL
)brace
suffix:semicolon
macro_line|#endif /* CONFIG_EXT2_FS */
eof
