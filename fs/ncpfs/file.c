multiline_comment|/*&n; *  file.c&n; *&n; *  Copyright (C) 1995, 1996 by Volker Lendecke&n; *  Modified 1997 Peter Waltenberg, Bill Hawes, David Woodhouse for 2.1 dcache&n; *&n; */
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/locks.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;linux/ncp_fs.h&gt;
macro_line|#include &quot;ncplib_kernel.h&quot;
DECL|function|ncp_fsync
r_static
r_int
id|ncp_fsync
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_struct
id|dentry
op_star
id|dentry
comma
r_int
id|datasync
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Open a file with the specified read/write mode.&n; */
DECL|function|ncp_make_open
r_int
id|ncp_make_open
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|right
)paren
(brace
r_int
id|error
suffix:semicolon
r_int
id|access
suffix:semicolon
id|error
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;ncp_make_open: got NULL inode&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|DPRINTK
c_func
(paren
l_string|&quot;ncp_make_open: opened=%d, volume # %u, dir entry # %u&bslash;n&quot;
comma
id|atomic_read
c_func
(paren
op_amp
id|NCP_FINFO
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|opened
)paren
comma
id|NCP_FINFO
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|volNumber
comma
id|NCP_FINFO
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|dirEntNum
)paren
suffix:semicolon
id|error
op_assign
op_minus
id|EACCES
suffix:semicolon
id|down
c_func
(paren
op_amp
id|NCP_FINFO
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|open_sem
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|atomic_read
c_func
(paren
op_amp
id|NCP_FINFO
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|opened
)paren
)paren
(brace
r_struct
id|ncp_entry_info
id|finfo
suffix:semicolon
r_int
id|result
suffix:semicolon
id|finfo.i.dirEntNum
op_assign
id|NCP_FINFO
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|dirEntNum
suffix:semicolon
id|finfo.i.volNumber
op_assign
id|NCP_FINFO
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|volNumber
suffix:semicolon
multiline_comment|/* tries max. rights */
id|finfo.access
op_assign
id|O_RDWR
suffix:semicolon
id|result
op_assign
id|ncp_open_create_file_or_subdir
c_func
(paren
id|NCP_SERVER
c_func
(paren
id|inode
)paren
comma
l_int|NULL
comma
l_int|NULL
comma
id|OC_MODE_OPEN
comma
l_int|0
comma
id|AR_READ
op_or
id|AR_WRITE
comma
op_amp
id|finfo
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|result
)paren
r_goto
id|update
suffix:semicolon
multiline_comment|/* RDWR did not succeeded, try readonly or writeonly as requested */
r_switch
c_cond
(paren
id|right
)paren
(brace
r_case
id|O_RDONLY
suffix:colon
id|finfo.access
op_assign
id|O_RDONLY
suffix:semicolon
id|result
op_assign
id|ncp_open_create_file_or_subdir
c_func
(paren
id|NCP_SERVER
c_func
(paren
id|inode
)paren
comma
l_int|NULL
comma
l_int|NULL
comma
id|OC_MODE_OPEN
comma
l_int|0
comma
id|AR_READ
comma
op_amp
id|finfo
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|O_WRONLY
suffix:colon
id|finfo.access
op_assign
id|O_WRONLY
suffix:semicolon
id|result
op_assign
id|ncp_open_create_file_or_subdir
c_func
(paren
id|NCP_SERVER
c_func
(paren
id|inode
)paren
comma
l_int|NULL
comma
l_int|NULL
comma
id|OC_MODE_OPEN
comma
l_int|0
comma
id|AR_WRITE
comma
op_amp
id|finfo
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|result
)paren
(brace
id|PPRINTK
c_func
(paren
l_string|&quot;ncp_make_open: failed, result=%d&bslash;n&quot;
comma
id|result
)paren
suffix:semicolon
r_goto
id|out_unlock
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * Update the inode information.&n;&t;&t; */
id|update
suffix:colon
id|ncp_update_inode
c_func
(paren
id|inode
comma
op_amp
id|finfo
)paren
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|NCP_FINFO
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|opened
comma
l_int|1
)paren
suffix:semicolon
)brace
id|access
op_assign
id|NCP_FINFO
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|access
suffix:semicolon
id|PPRINTK
c_func
(paren
l_string|&quot;ncp_make_open: file open, access=%x&bslash;n&quot;
comma
id|access
)paren
suffix:semicolon
r_if
c_cond
(paren
id|access
op_eq
id|right
op_logical_or
id|access
op_eq
id|O_RDWR
)paren
(brace
id|atomic_inc
c_func
(paren
op_amp
id|NCP_FINFO
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|opened
)paren
suffix:semicolon
id|error
op_assign
l_int|0
suffix:semicolon
)brace
id|out_unlock
suffix:colon
id|up
c_func
(paren
op_amp
id|NCP_FINFO
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|open_sem
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|error
suffix:semicolon
)brace
r_static
id|ssize_t
DECL|function|ncp_file_read
id|ncp_file_read
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_char
op_star
id|buf
comma
r_int
id|count
comma
id|loff_t
op_star
id|ppos
)paren
(brace
r_struct
id|dentry
op_star
id|dentry
op_assign
id|file-&gt;f_dentry
suffix:semicolon
r_struct
id|inode
op_star
id|inode
op_assign
id|dentry-&gt;d_inode
suffix:semicolon
r_int
id|already_read
op_assign
l_int|0
suffix:semicolon
id|off_t
id|pos
suffix:semicolon
r_int
id|bufsize
suffix:semicolon
r_int
id|error
suffix:semicolon
r_void
op_star
id|freepage
suffix:semicolon
r_int
id|freelen
suffix:semicolon
id|DPRINTK
c_func
(paren
l_string|&quot;ncp_file_read: enter %s/%s&bslash;n&quot;
comma
id|dentry-&gt;d_parent-&gt;d_name.name
comma
id|dentry-&gt;d_name.name
)paren
suffix:semicolon
id|error
op_assign
op_minus
id|EIO
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ncp_conn_valid
c_func
(paren
id|NCP_SERVER
c_func
(paren
id|inode
)paren
)paren
)paren
r_goto
id|out
suffix:semicolon
id|error
op_assign
op_minus
id|EINVAL
suffix:semicolon
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
(brace
id|DPRINTK
c_func
(paren
l_string|&quot;ncp_file_read: read from non-file, mode %07o&bslash;n&quot;
comma
id|inode-&gt;i_mode
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|pos
op_assign
op_star
id|ppos
suffix:semicolon
multiline_comment|/* leave it out on server ...&n;&t;if (pos + count &gt; inode-&gt;i_size) {&n;&t;&t;count = inode-&gt;i_size - pos;&n;&t;}&n;*/
id|error
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|count
)paren
multiline_comment|/* size_t is never &lt; 0 */
r_goto
id|out
suffix:semicolon
id|error
op_assign
id|ncp_make_open
c_func
(paren
id|inode
comma
id|O_RDONLY
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
(brace
id|DPRINTK
c_func
(paren
id|KERN_ERR
l_string|&quot;ncp_file_read: open failed, error=%d&bslash;n&quot;
comma
id|error
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|bufsize
op_assign
id|NCP_SERVER
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|buffer_size
suffix:semicolon
id|error
op_assign
op_minus
id|EIO
suffix:semicolon
id|freelen
op_assign
id|ncp_read_bounce_size
c_func
(paren
id|bufsize
)paren
suffix:semicolon
id|freepage
op_assign
id|vmalloc
c_func
(paren
id|freelen
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|freepage
)paren
r_goto
id|outrel
suffix:semicolon
id|error
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* First read in as much as possible for each bufsize. */
r_while
c_loop
(paren
id|already_read
OL
id|count
)paren
(brace
r_int
id|read_this_time
suffix:semicolon
r_int
id|to_read
op_assign
id|min
c_func
(paren
r_int
r_int
comma
id|bufsize
op_minus
(paren
id|pos
op_mod
id|bufsize
)paren
comma
id|count
op_minus
id|already_read
)paren
suffix:semicolon
id|error
op_assign
id|ncp_read_bounce
c_func
(paren
id|NCP_SERVER
c_func
(paren
id|inode
)paren
comma
id|NCP_FINFO
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|file_handle
comma
id|pos
comma
id|to_read
comma
id|buf
comma
op_amp
id|read_this_time
comma
id|freepage
comma
id|freelen
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
(brace
id|error
op_assign
op_minus
id|EIO
suffix:semicolon
multiline_comment|/* NW errno -&gt; Linux errno */
r_break
suffix:semicolon
)brace
id|pos
op_add_assign
id|read_this_time
suffix:semicolon
id|buf
op_add_assign
id|read_this_time
suffix:semicolon
id|already_read
op_add_assign
id|read_this_time
suffix:semicolon
r_if
c_cond
(paren
id|read_this_time
op_ne
id|to_read
)paren
(brace
r_break
suffix:semicolon
)brace
)brace
id|vfree
c_func
(paren
id|freepage
)paren
suffix:semicolon
op_star
id|ppos
op_assign
id|pos
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|IS_RDONLY
c_func
(paren
id|inode
)paren
)paren
(brace
id|inode-&gt;i_atime
op_assign
id|CURRENT_TIME
suffix:semicolon
)brace
id|DPRINTK
c_func
(paren
l_string|&quot;ncp_file_read: exit %s/%s&bslash;n&quot;
comma
id|dentry-&gt;d_parent-&gt;d_name.name
comma
id|dentry-&gt;d_name.name
)paren
suffix:semicolon
id|outrel
suffix:colon
id|ncp_inode_close
c_func
(paren
id|inode
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|already_read
ques
c_cond
id|already_read
suffix:colon
id|error
suffix:semicolon
)brace
r_static
id|ssize_t
DECL|function|ncp_file_write
id|ncp_file_write
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_const
r_char
op_star
id|buf
comma
r_int
id|count
comma
id|loff_t
op_star
id|ppos
)paren
(brace
r_struct
id|dentry
op_star
id|dentry
op_assign
id|file-&gt;f_dentry
suffix:semicolon
r_struct
id|inode
op_star
id|inode
op_assign
id|dentry-&gt;d_inode
suffix:semicolon
r_int
id|already_written
op_assign
l_int|0
suffix:semicolon
id|off_t
id|pos
suffix:semicolon
r_int
id|bufsize
suffix:semicolon
r_int
id|errno
suffix:semicolon
r_void
op_star
id|bouncebuffer
suffix:semicolon
id|DPRINTK
c_func
(paren
l_string|&quot;ncp_file_write: enter %s/%s&bslash;n&quot;
comma
id|dentry-&gt;d_parent-&gt;d_name.name
comma
id|dentry-&gt;d_name.name
)paren
suffix:semicolon
id|errno
op_assign
op_minus
id|EIO
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ncp_conn_valid
c_func
(paren
id|NCP_SERVER
c_func
(paren
id|inode
)paren
)paren
)paren
r_goto
id|out
suffix:semicolon
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
(brace
id|DPRINTK
c_func
(paren
l_string|&quot;ncp_file_write: write to non-file, mode %07o&bslash;n&quot;
comma
id|inode-&gt;i_mode
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|errno
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|count
)paren
r_goto
id|out
suffix:semicolon
id|errno
op_assign
id|ncp_make_open
c_func
(paren
id|inode
comma
id|O_WRONLY
)paren
suffix:semicolon
r_if
c_cond
(paren
id|errno
)paren
(brace
id|DPRINTK
c_func
(paren
id|KERN_ERR
l_string|&quot;ncp_file_write: open failed, error=%d&bslash;n&quot;
comma
id|errno
)paren
suffix:semicolon
r_return
id|errno
suffix:semicolon
)brace
id|pos
op_assign
op_star
id|ppos
suffix:semicolon
r_if
c_cond
(paren
id|file-&gt;f_flags
op_amp
id|O_APPEND
)paren
(brace
id|pos
op_assign
id|inode-&gt;i_size
suffix:semicolon
)brace
id|bufsize
op_assign
id|NCP_SERVER
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|buffer_size
suffix:semicolon
id|already_written
op_assign
l_int|0
suffix:semicolon
id|bouncebuffer
op_assign
id|vmalloc
c_func
(paren
id|bufsize
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bouncebuffer
)paren
(brace
id|errno
op_assign
op_minus
id|EIO
suffix:semicolon
multiline_comment|/* -ENOMEM */
r_goto
id|outrel
suffix:semicolon
)brace
r_while
c_loop
(paren
id|already_written
OL
id|count
)paren
(brace
r_int
id|written_this_time
suffix:semicolon
r_int
id|to_write
op_assign
id|min
c_func
(paren
r_int
r_int
comma
id|bufsize
op_minus
(paren
id|pos
op_mod
id|bufsize
)paren
comma
id|count
op_minus
id|already_written
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|bouncebuffer
comma
id|buf
comma
id|to_write
)paren
)paren
(brace
id|errno
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ncp_write_kernel
c_func
(paren
id|NCP_SERVER
c_func
(paren
id|inode
)paren
comma
id|NCP_FINFO
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|file_handle
comma
id|pos
comma
id|to_write
comma
id|bouncebuffer
comma
op_amp
id|written_this_time
)paren
op_ne
l_int|0
)paren
(brace
id|errno
op_assign
op_minus
id|EIO
suffix:semicolon
r_break
suffix:semicolon
)brace
id|pos
op_add_assign
id|written_this_time
suffix:semicolon
id|buf
op_add_assign
id|written_this_time
suffix:semicolon
id|already_written
op_add_assign
id|written_this_time
suffix:semicolon
r_if
c_cond
(paren
id|written_this_time
op_ne
id|to_write
)paren
(brace
r_break
suffix:semicolon
)brace
)brace
id|vfree
c_func
(paren
id|bouncebuffer
)paren
suffix:semicolon
id|inode-&gt;i_mtime
op_assign
id|inode-&gt;i_atime
op_assign
id|CURRENT_TIME
suffix:semicolon
op_star
id|ppos
op_assign
id|pos
suffix:semicolon
r_if
c_cond
(paren
id|pos
OG
id|inode-&gt;i_size
)paren
(brace
id|inode-&gt;i_size
op_assign
id|pos
suffix:semicolon
)brace
id|DPRINTK
c_func
(paren
l_string|&quot;ncp_file_write: exit %s/%s&bslash;n&quot;
comma
id|dentry-&gt;d_parent-&gt;d_name.name
comma
id|dentry-&gt;d_name.name
)paren
suffix:semicolon
id|outrel
suffix:colon
id|ncp_inode_close
c_func
(paren
id|inode
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|already_written
ques
c_cond
id|already_written
suffix:colon
id|errno
suffix:semicolon
)brace
DECL|function|ncp_release
r_static
r_int
id|ncp_release
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
)paren
(brace
r_if
c_cond
(paren
id|ncp_make_closed
c_func
(paren
id|inode
)paren
)paren
(brace
id|DPRINTK
c_func
(paren
l_string|&quot;ncp_release: failed to close&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|ncp_file_operations
r_struct
id|file_operations
id|ncp_file_operations
op_assign
(brace
id|llseek
suffix:colon
id|generic_file_llseek
comma
id|read
suffix:colon
id|ncp_file_read
comma
id|write
suffix:colon
id|ncp_file_write
comma
id|ioctl
suffix:colon
id|ncp_ioctl
comma
id|mmap
suffix:colon
id|ncp_mmap
comma
id|release
suffix:colon
id|ncp_release
comma
id|fsync
suffix:colon
id|ncp_fsync
comma
)brace
suffix:semicolon
DECL|variable|ncp_file_inode_operations
r_struct
id|inode_operations
id|ncp_file_inode_operations
op_assign
(brace
id|setattr
suffix:colon
id|ncp_notify_change
comma
)brace
suffix:semicolon
eof
