multiline_comment|/*&n; *  linux/fs/bad_inode.c&n; *&n; *  Copyright (C) 1997, Stephen Tweedie&n; *&n; *  Provide stub functions for unreadable inodes&n; */
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
multiline_comment|/*&n; * The follow_link operation is special: it must behave as a no-op&n; * so that a bad root inode can at least be unmounted. To do this&n; * we must dput() the base and return the dentry with a dget().&n; */
DECL|function|bad_follow_link
r_static
r_int
id|bad_follow_link
c_func
(paren
r_struct
id|dentry
op_star
id|dent
comma
r_struct
id|nameidata
op_star
id|nd
)paren
(brace
r_return
id|vfs_follow_link
c_func
(paren
id|nd
comma
id|ERR_PTR
c_func
(paren
op_minus
id|EIO
)paren
)paren
suffix:semicolon
)brace
DECL|function|return_EIO
r_static
r_int
id|return_EIO
c_func
(paren
r_void
)paren
(brace
r_return
op_minus
id|EIO
suffix:semicolon
)brace
DECL|macro|EIO_ERROR
mdefine_line|#define EIO_ERROR ((void *) (return_EIO))
DECL|variable|bad_file_ops
r_static
r_struct
id|file_operations
id|bad_file_ops
op_assign
(brace
dot
id|llseek
op_assign
id|EIO_ERROR
comma
dot
id|read
op_assign
id|EIO_ERROR
comma
dot
id|write
op_assign
id|EIO_ERROR
comma
dot
id|readdir
op_assign
id|EIO_ERROR
comma
dot
id|poll
op_assign
id|EIO_ERROR
comma
dot
id|ioctl
op_assign
id|EIO_ERROR
comma
dot
id|mmap
op_assign
id|EIO_ERROR
comma
dot
id|open
op_assign
id|EIO_ERROR
comma
dot
id|flush
op_assign
id|EIO_ERROR
comma
dot
id|release
op_assign
id|EIO_ERROR
comma
dot
id|fsync
op_assign
id|EIO_ERROR
comma
dot
id|fasync
op_assign
id|EIO_ERROR
comma
dot
id|lock
op_assign
id|EIO_ERROR
comma
)brace
suffix:semicolon
DECL|variable|bad_inode_ops
r_struct
id|inode_operations
id|bad_inode_ops
op_assign
(brace
dot
id|create
op_assign
id|EIO_ERROR
comma
dot
id|lookup
op_assign
id|EIO_ERROR
comma
dot
id|link
op_assign
id|EIO_ERROR
comma
dot
id|unlink
op_assign
id|EIO_ERROR
comma
dot
id|symlink
op_assign
id|EIO_ERROR
comma
dot
id|mkdir
op_assign
id|EIO_ERROR
comma
dot
id|rmdir
op_assign
id|EIO_ERROR
comma
dot
id|mknod
op_assign
id|EIO_ERROR
comma
dot
id|rename
op_assign
id|EIO_ERROR
comma
dot
id|readlink
op_assign
id|EIO_ERROR
comma
dot
id|follow_link
op_assign
id|bad_follow_link
comma
dot
id|truncate
op_assign
id|EIO_ERROR
comma
dot
id|permission
op_assign
id|EIO_ERROR
comma
dot
id|getattr
op_assign
id|EIO_ERROR
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * When a filesystem is unable to read an inode due to an I/O error in&n; * its read_inode() function, it can call make_bad_inode() to return a&n; * set of stubs which will return EIO errors as required. &n; *&n; * We only need to do limited initialisation: all other fields are&n; * preinitialised to zero automatically.&n; */
multiline_comment|/**&n; *&t;make_bad_inode - mark an inode bad due to an I/O error&n; *&t;@inode: Inode to mark bad&n; *&n; *&t;When an inode cannot be read due to a media or remote network&n; *&t;failure this function makes the inode &quot;bad&quot; and causes I/O operations&n; *&t;on it to fail from this point on.&n; */
DECL|function|make_bad_inode
r_void
id|make_bad_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
id|remove_inode_hash
c_func
(paren
id|inode
)paren
suffix:semicolon
id|inode-&gt;i_mode
op_assign
id|S_IFREG
suffix:semicolon
id|inode-&gt;i_atime
op_assign
id|inode-&gt;i_mtime
op_assign
id|inode-&gt;i_ctime
op_assign
id|CURRENT_TIME
suffix:semicolon
id|inode-&gt;i_op
op_assign
op_amp
id|bad_inode_ops
suffix:semicolon
id|inode-&gt;i_fop
op_assign
op_amp
id|bad_file_ops
suffix:semicolon
)brace
multiline_comment|/*&n; * This tests whether an inode has been flagged as bad. The test uses&n; * &amp;bad_inode_ops to cover the case of invalidated inodes as well as&n; * those created by make_bad_inode() above.&n; */
multiline_comment|/**&n; *&t;is_bad_inode - is an inode errored&n; *&t;@inode: inode to test&n; *&n; *&t;Returns true if the inode in question has been marked as bad.&n; */
DECL|function|is_bad_inode
r_int
id|is_bad_inode
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
id|inode-&gt;i_op
op_eq
op_amp
id|bad_inode_ops
)paren
suffix:semicolon
)brace
eof
