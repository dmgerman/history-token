multiline_comment|/*&n; * QNX4 file system, Linux implementation.&n; *&n; * Version : 0.2.1&n; *&n; * Using parts of the xiafs filesystem.&n; *&n; * History :&n; *&n; * 25-05-1998 by Richard Frowijn : first release.&n; * 21-06-1998 by Frank Denis : wrote qnx4_readpage to use generic_file_read.&n; * 27-06-1998 by Frank Denis : file overwriting.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/qnx4_fs.h&gt;
multiline_comment|/*&n; * We have mostly NULL&squot;s here: the current defaults are ok for&n; * the qnx4 filesystem.&n; */
DECL|variable|qnx4_file_operations
r_struct
id|file_operations
id|qnx4_file_operations
op_assign
(brace
id|llseek
suffix:colon
id|generic_file_llseek
comma
id|read
suffix:colon
id|generic_file_read
comma
macro_line|#ifdef CONFIG_QNX4FS_RW
id|write
suffix:colon
id|generic_file_write
comma
macro_line|#endif
id|mmap
suffix:colon
id|generic_file_mmap
comma
macro_line|#ifdef CONFIG_QNX4FS_RW
id|fsync
suffix:colon
id|qnx4_sync_file
comma
macro_line|#endif
)brace
suffix:semicolon
DECL|variable|qnx4_file_inode_operations
r_struct
id|inode_operations
id|qnx4_file_inode_operations
op_assign
(brace
macro_line|#ifdef CONFIG_QNX4FS_RW
id|truncate
suffix:colon
id|qnx4_truncate
comma
macro_line|#endif
)brace
suffix:semicolon
eof
