multiline_comment|/* &n; * QNX4 file system, Linux implementation.&n; * &n; * Version : 0.1&n; * &n; * Using parts of the xiafs filesystem.&n; * &n; * History :&n; * &n; * 30-06-1998 by Frank DENIS : ugly filler.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/qnx4_fs.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/locks.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#ifdef CONFIG_QNX4FS_RW
DECL|function|qnx4_truncate
r_void
id|qnx4_truncate
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
(paren
id|S_ISREG
c_func
(paren
id|inode-&gt;i_mode
)paren
op_logical_or
id|S_ISDIR
c_func
(paren
id|inode-&gt;i_mode
)paren
op_logical_or
id|S_ISLNK
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
)paren
(brace
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|S_ISDIR
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
)paren
(brace
multiline_comment|/* TODO */
)brace
id|QNX4DEBUG
c_func
(paren
(paren
l_string|&quot;qnx4: qnx4_truncate called&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|inode-&gt;i_mtime
op_assign
id|inode-&gt;i_ctime
op_assign
id|CURRENT_TIME
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|inode
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
