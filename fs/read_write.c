multiline_comment|/*&n; *  linux/fs/read_write.c&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; */
macro_line|#include &lt;linux/slab.h&gt; 
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/file.h&gt;
macro_line|#include &lt;linux/uio.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/dnotify.h&gt;
macro_line|#include &lt;linux/security.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
DECL|variable|generic_ro_fops
r_struct
id|file_operations
id|generic_ro_fops
op_assign
(brace
dot
id|llseek
op_assign
id|generic_file_llseek
comma
dot
id|read
op_assign
id|generic_file_read
comma
dot
id|mmap
op_assign
id|generic_file_readonly_mmap
comma
dot
id|sendfile
op_assign
id|generic_file_sendfile
comma
)brace
suffix:semicolon
DECL|variable|generic_ro_fops
id|EXPORT_SYMBOL
c_func
(paren
id|generic_ro_fops
)paren
suffix:semicolon
DECL|function|generic_file_llseek
id|loff_t
id|generic_file_llseek
c_func
(paren
r_struct
id|file
op_star
id|file
comma
id|loff_t
id|offset
comma
r_int
id|origin
)paren
(brace
r_int
r_int
id|retval
suffix:semicolon
r_struct
id|inode
op_star
id|inode
op_assign
id|file-&gt;f_mapping-&gt;host
suffix:semicolon
id|down
c_func
(paren
op_amp
id|inode-&gt;i_sem
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|origin
)paren
(brace
r_case
l_int|2
suffix:colon
id|offset
op_add_assign
id|inode-&gt;i_size
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|offset
op_add_assign
id|file-&gt;f_pos
suffix:semicolon
)brace
id|retval
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|offset
op_ge
l_int|0
op_logical_and
id|offset
op_le
id|inode-&gt;i_sb-&gt;s_maxbytes
)paren
(brace
r_if
c_cond
(paren
id|offset
op_ne
id|file-&gt;f_pos
)paren
(brace
id|file-&gt;f_pos
op_assign
id|offset
suffix:semicolon
id|file-&gt;f_version
op_assign
l_int|0
suffix:semicolon
)brace
id|retval
op_assign
id|offset
suffix:semicolon
)brace
id|up
c_func
(paren
op_amp
id|inode-&gt;i_sem
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|variable|generic_file_llseek
id|EXPORT_SYMBOL
c_func
(paren
id|generic_file_llseek
)paren
suffix:semicolon
DECL|function|remote_llseek
id|loff_t
id|remote_llseek
c_func
(paren
r_struct
id|file
op_star
id|file
comma
id|loff_t
id|offset
comma
r_int
id|origin
)paren
(brace
r_int
r_int
id|retval
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|origin
)paren
(brace
r_case
l_int|2
suffix:colon
id|offset
op_add_assign
id|i_size_read
c_func
(paren
id|file-&gt;f_dentry-&gt;d_inode
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|offset
op_add_assign
id|file-&gt;f_pos
suffix:semicolon
)brace
id|retval
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|offset
op_ge
l_int|0
op_logical_and
id|offset
op_le
id|file-&gt;f_dentry-&gt;d_inode-&gt;i_sb-&gt;s_maxbytes
)paren
(brace
r_if
c_cond
(paren
id|offset
op_ne
id|file-&gt;f_pos
)paren
(brace
id|file-&gt;f_pos
op_assign
id|offset
suffix:semicolon
id|file-&gt;f_version
op_assign
l_int|0
suffix:semicolon
)brace
id|retval
op_assign
id|offset
suffix:semicolon
)brace
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|variable|remote_llseek
id|EXPORT_SYMBOL
c_func
(paren
id|remote_llseek
)paren
suffix:semicolon
DECL|function|no_llseek
id|loff_t
id|no_llseek
c_func
(paren
r_struct
id|file
op_star
id|file
comma
id|loff_t
id|offset
comma
r_int
id|origin
)paren
(brace
r_return
op_minus
id|ESPIPE
suffix:semicolon
)brace
DECL|variable|no_llseek
id|EXPORT_SYMBOL
c_func
(paren
id|no_llseek
)paren
suffix:semicolon
DECL|function|default_llseek
id|loff_t
id|default_llseek
c_func
(paren
r_struct
id|file
op_star
id|file
comma
id|loff_t
id|offset
comma
r_int
id|origin
)paren
(brace
r_int
r_int
id|retval
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|origin
)paren
(brace
r_case
l_int|2
suffix:colon
id|offset
op_add_assign
id|i_size_read
c_func
(paren
id|file-&gt;f_dentry-&gt;d_inode
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|offset
op_add_assign
id|file-&gt;f_pos
suffix:semicolon
)brace
id|retval
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|offset
op_ge
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|offset
op_ne
id|file-&gt;f_pos
)paren
(brace
id|file-&gt;f_pos
op_assign
id|offset
suffix:semicolon
id|file-&gt;f_version
op_assign
l_int|0
suffix:semicolon
)brace
id|retval
op_assign
id|offset
suffix:semicolon
)brace
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|variable|default_llseek
id|EXPORT_SYMBOL
c_func
(paren
id|default_llseek
)paren
suffix:semicolon
DECL|function|llseek
r_static
r_inline
id|loff_t
id|llseek
c_func
(paren
r_struct
id|file
op_star
id|file
comma
id|loff_t
id|offset
comma
r_int
id|origin
)paren
(brace
id|loff_t
(paren
op_star
id|fn
)paren
(paren
r_struct
id|file
op_star
comma
id|loff_t
comma
r_int
)paren
suffix:semicolon
id|fn
op_assign
id|default_llseek
suffix:semicolon
r_if
c_cond
(paren
id|file-&gt;f_op
op_logical_and
id|file-&gt;f_op-&gt;llseek
)paren
id|fn
op_assign
id|file-&gt;f_op-&gt;llseek
suffix:semicolon
r_return
id|fn
c_func
(paren
id|file
comma
id|offset
comma
id|origin
)paren
suffix:semicolon
)brace
DECL|function|sys_lseek
id|asmlinkage
id|off_t
id|sys_lseek
c_func
(paren
r_int
r_int
id|fd
comma
id|off_t
id|offset
comma
r_int
r_int
id|origin
)paren
(brace
id|off_t
id|retval
suffix:semicolon
r_struct
id|file
op_star
id|file
suffix:semicolon
r_int
id|fput_needed
suffix:semicolon
id|retval
op_assign
op_minus
id|EBADF
suffix:semicolon
id|file
op_assign
id|fget_light
c_func
(paren
id|fd
comma
op_amp
id|fput_needed
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|file
)paren
r_goto
id|bad
suffix:semicolon
id|retval
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|origin
op_le
l_int|2
)paren
(brace
id|loff_t
id|res
op_assign
id|llseek
c_func
(paren
id|file
comma
id|offset
comma
id|origin
)paren
suffix:semicolon
id|retval
op_assign
id|res
suffix:semicolon
r_if
c_cond
(paren
id|res
op_ne
(paren
id|loff_t
)paren
id|retval
)paren
id|retval
op_assign
op_minus
id|EOVERFLOW
suffix:semicolon
multiline_comment|/* LFS: should only happen on 32 bit platforms */
)brace
id|fput_light
c_func
(paren
id|file
comma
id|fput_needed
)paren
suffix:semicolon
id|bad
suffix:colon
r_return
id|retval
suffix:semicolon
)brace
macro_line|#if !defined(__alpha__)
DECL|function|sys_llseek
id|asmlinkage
r_int
id|sys_llseek
c_func
(paren
r_int
r_int
id|fd
comma
r_int
r_int
id|offset_high
comma
r_int
r_int
id|offset_low
comma
id|loff_t
id|__user
op_star
id|result
comma
r_int
r_int
id|origin
)paren
(brace
r_int
id|retval
suffix:semicolon
r_struct
id|file
op_star
id|file
suffix:semicolon
id|loff_t
id|offset
suffix:semicolon
r_int
id|fput_needed
suffix:semicolon
id|retval
op_assign
op_minus
id|EBADF
suffix:semicolon
id|file
op_assign
id|fget_light
c_func
(paren
id|fd
comma
op_amp
id|fput_needed
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|file
)paren
r_goto
id|bad
suffix:semicolon
id|retval
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|origin
OG
l_int|2
)paren
r_goto
id|out_putf
suffix:semicolon
id|offset
op_assign
id|llseek
c_func
(paren
id|file
comma
(paren
(paren
id|loff_t
)paren
id|offset_high
op_lshift
l_int|32
)paren
op_or
id|offset_low
comma
id|origin
)paren
suffix:semicolon
id|retval
op_assign
(paren
r_int
)paren
id|offset
suffix:semicolon
r_if
c_cond
(paren
id|offset
op_ge
l_int|0
)paren
(brace
id|retval
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|copy_to_user
c_func
(paren
id|result
comma
op_amp
id|offset
comma
r_sizeof
(paren
id|offset
)paren
)paren
)paren
id|retval
op_assign
l_int|0
suffix:semicolon
)brace
id|out_putf
suffix:colon
id|fput_light
c_func
(paren
id|file
comma
id|fput_needed
)paren
suffix:semicolon
id|bad
suffix:colon
r_return
id|retval
suffix:semicolon
)brace
macro_line|#endif
DECL|function|do_sync_read
id|ssize_t
id|do_sync_read
c_func
(paren
r_struct
id|file
op_star
id|filp
comma
r_char
id|__user
op_star
id|buf
comma
r_int
id|len
comma
id|loff_t
op_star
id|ppos
)paren
(brace
r_struct
id|kiocb
id|kiocb
suffix:semicolon
id|ssize_t
id|ret
suffix:semicolon
id|init_sync_kiocb
c_func
(paren
op_amp
id|kiocb
comma
id|filp
)paren
suffix:semicolon
id|kiocb.ki_pos
op_assign
op_star
id|ppos
suffix:semicolon
id|ret
op_assign
id|filp-&gt;f_op
op_member_access_from_pointer
id|aio_read
c_func
(paren
op_amp
id|kiocb
comma
id|buf
comma
id|len
comma
id|kiocb.ki_pos
)paren
suffix:semicolon
r_if
c_cond
(paren
op_minus
id|EIOCBQUEUED
op_eq
id|ret
)paren
id|ret
op_assign
id|wait_on_sync_kiocb
c_func
(paren
op_amp
id|kiocb
)paren
suffix:semicolon
op_star
id|ppos
op_assign
id|kiocb.ki_pos
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|variable|do_sync_read
id|EXPORT_SYMBOL
c_func
(paren
id|do_sync_read
)paren
suffix:semicolon
DECL|function|vfs_read
id|ssize_t
id|vfs_read
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_char
id|__user
op_star
id|buf
comma
r_int
id|count
comma
id|loff_t
op_star
id|pos
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|file-&gt;f_dentry-&gt;d_inode
suffix:semicolon
id|ssize_t
id|ret
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|file-&gt;f_mode
op_amp
id|FMODE_READ
)paren
)paren
r_return
op_minus
id|EBADF
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|file-&gt;f_op
op_logical_or
(paren
op_logical_neg
id|file-&gt;f_op-&gt;read
op_logical_and
op_logical_neg
id|file-&gt;f_op-&gt;aio_read
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|ret
op_assign
id|locks_verify_area
c_func
(paren
id|FLOCK_VERIFY_READ
comma
id|inode
comma
id|file
comma
op_star
id|pos
comma
id|count
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ret
)paren
(brace
id|ret
op_assign
id|security_file_permission
(paren
id|file
comma
id|MAY_READ
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ret
)paren
(brace
r_if
c_cond
(paren
id|file-&gt;f_op-&gt;read
)paren
id|ret
op_assign
id|file-&gt;f_op
op_member_access_from_pointer
id|read
c_func
(paren
id|file
comma
id|buf
comma
id|count
comma
id|pos
)paren
suffix:semicolon
r_else
id|ret
op_assign
id|do_sync_read
c_func
(paren
id|file
comma
id|buf
comma
id|count
comma
id|pos
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OG
l_int|0
)paren
id|dnotify_parent
c_func
(paren
id|file-&gt;f_dentry
comma
id|DN_ACCESS
)paren
suffix:semicolon
)brace
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|variable|vfs_read
id|EXPORT_SYMBOL
c_func
(paren
id|vfs_read
)paren
suffix:semicolon
DECL|function|do_sync_write
id|ssize_t
id|do_sync_write
c_func
(paren
r_struct
id|file
op_star
id|filp
comma
r_const
r_char
id|__user
op_star
id|buf
comma
r_int
id|len
comma
id|loff_t
op_star
id|ppos
)paren
(brace
r_struct
id|kiocb
id|kiocb
suffix:semicolon
id|ssize_t
id|ret
suffix:semicolon
id|init_sync_kiocb
c_func
(paren
op_amp
id|kiocb
comma
id|filp
)paren
suffix:semicolon
id|kiocb.ki_pos
op_assign
op_star
id|ppos
suffix:semicolon
id|ret
op_assign
id|filp-&gt;f_op
op_member_access_from_pointer
id|aio_write
c_func
(paren
op_amp
id|kiocb
comma
id|buf
comma
id|len
comma
id|kiocb.ki_pos
)paren
suffix:semicolon
r_if
c_cond
(paren
op_minus
id|EIOCBQUEUED
op_eq
id|ret
)paren
id|ret
op_assign
id|wait_on_sync_kiocb
c_func
(paren
op_amp
id|kiocb
)paren
suffix:semicolon
op_star
id|ppos
op_assign
id|kiocb.ki_pos
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|variable|do_sync_write
id|EXPORT_SYMBOL
c_func
(paren
id|do_sync_write
)paren
suffix:semicolon
DECL|function|vfs_write
id|ssize_t
id|vfs_write
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_const
r_char
id|__user
op_star
id|buf
comma
r_int
id|count
comma
id|loff_t
op_star
id|pos
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|file-&gt;f_dentry-&gt;d_inode
suffix:semicolon
id|ssize_t
id|ret
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|file-&gt;f_mode
op_amp
id|FMODE_WRITE
)paren
)paren
r_return
op_minus
id|EBADF
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|file-&gt;f_op
op_logical_or
(paren
op_logical_neg
id|file-&gt;f_op-&gt;write
op_logical_and
op_logical_neg
id|file-&gt;f_op-&gt;aio_write
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|ret
op_assign
id|locks_verify_area
c_func
(paren
id|FLOCK_VERIFY_WRITE
comma
id|inode
comma
id|file
comma
op_star
id|pos
comma
id|count
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ret
)paren
(brace
id|ret
op_assign
id|security_file_permission
(paren
id|file
comma
id|MAY_WRITE
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ret
)paren
(brace
r_if
c_cond
(paren
id|file-&gt;f_op-&gt;write
)paren
id|ret
op_assign
id|file-&gt;f_op
op_member_access_from_pointer
id|write
c_func
(paren
id|file
comma
id|buf
comma
id|count
comma
id|pos
)paren
suffix:semicolon
r_else
id|ret
op_assign
id|do_sync_write
c_func
(paren
id|file
comma
id|buf
comma
id|count
comma
id|pos
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OG
l_int|0
)paren
id|dnotify_parent
c_func
(paren
id|file-&gt;f_dentry
comma
id|DN_MODIFY
)paren
suffix:semicolon
)brace
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|variable|vfs_write
id|EXPORT_SYMBOL
c_func
(paren
id|vfs_write
)paren
suffix:semicolon
DECL|function|sys_read
id|asmlinkage
id|ssize_t
id|sys_read
c_func
(paren
r_int
r_int
id|fd
comma
r_char
id|__user
op_star
id|buf
comma
r_int
id|count
)paren
(brace
r_struct
id|file
op_star
id|file
suffix:semicolon
id|ssize_t
id|ret
op_assign
op_minus
id|EBADF
suffix:semicolon
r_int
id|fput_needed
suffix:semicolon
id|file
op_assign
id|fget_light
c_func
(paren
id|fd
comma
op_amp
id|fput_needed
)paren
suffix:semicolon
r_if
c_cond
(paren
id|file
)paren
(brace
id|ret
op_assign
id|vfs_read
c_func
(paren
id|file
comma
id|buf
comma
id|count
comma
op_amp
id|file-&gt;f_pos
)paren
suffix:semicolon
id|fput_light
c_func
(paren
id|file
comma
id|fput_needed
)paren
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|function|sys_write
id|asmlinkage
id|ssize_t
id|sys_write
c_func
(paren
r_int
r_int
id|fd
comma
r_const
r_char
id|__user
op_star
id|buf
comma
r_int
id|count
)paren
(brace
r_struct
id|file
op_star
id|file
suffix:semicolon
id|ssize_t
id|ret
op_assign
op_minus
id|EBADF
suffix:semicolon
r_int
id|fput_needed
suffix:semicolon
id|file
op_assign
id|fget_light
c_func
(paren
id|fd
comma
op_amp
id|fput_needed
)paren
suffix:semicolon
r_if
c_cond
(paren
id|file
)paren
(brace
id|ret
op_assign
id|vfs_write
c_func
(paren
id|file
comma
id|buf
comma
id|count
comma
op_amp
id|file-&gt;f_pos
)paren
suffix:semicolon
id|fput_light
c_func
(paren
id|file
comma
id|fput_needed
)paren
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|function|sys_pread64
id|asmlinkage
id|ssize_t
id|sys_pread64
c_func
(paren
r_int
r_int
id|fd
comma
r_char
id|__user
op_star
id|buf
comma
r_int
id|count
comma
id|loff_t
id|pos
)paren
(brace
r_struct
id|file
op_star
id|file
suffix:semicolon
id|ssize_t
id|ret
op_assign
op_minus
id|EBADF
suffix:semicolon
r_int
id|fput_needed
suffix:semicolon
r_if
c_cond
(paren
id|pos
OL
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|file
op_assign
id|fget_light
c_func
(paren
id|fd
comma
op_amp
id|fput_needed
)paren
suffix:semicolon
r_if
c_cond
(paren
id|file
)paren
(brace
id|ret
op_assign
id|vfs_read
c_func
(paren
id|file
comma
id|buf
comma
id|count
comma
op_amp
id|pos
)paren
suffix:semicolon
id|fput_light
c_func
(paren
id|file
comma
id|fput_needed
)paren
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|function|sys_pwrite64
id|asmlinkage
id|ssize_t
id|sys_pwrite64
c_func
(paren
r_int
r_int
id|fd
comma
r_const
r_char
id|__user
op_star
id|buf
comma
r_int
id|count
comma
id|loff_t
id|pos
)paren
(brace
r_struct
id|file
op_star
id|file
suffix:semicolon
id|ssize_t
id|ret
op_assign
op_minus
id|EBADF
suffix:semicolon
r_int
id|fput_needed
suffix:semicolon
r_if
c_cond
(paren
id|pos
OL
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|file
op_assign
id|fget_light
c_func
(paren
id|fd
comma
op_amp
id|fput_needed
)paren
suffix:semicolon
r_if
c_cond
(paren
id|file
)paren
(brace
id|ret
op_assign
id|vfs_write
c_func
(paren
id|file
comma
id|buf
comma
id|count
comma
op_amp
id|pos
)paren
suffix:semicolon
id|fput_light
c_func
(paren
id|file
comma
id|fput_needed
)paren
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * Reduce an iovec&squot;s length in-place.  Return the resulting number of segments&n; */
DECL|function|iov_shorten
r_int
r_int
id|iov_shorten
c_func
(paren
r_struct
id|iovec
op_star
id|iov
comma
r_int
r_int
id|nr_segs
comma
r_int
id|to
)paren
(brace
r_int
r_int
id|seg
op_assign
l_int|0
suffix:semicolon
r_int
id|len
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|seg
OL
id|nr_segs
)paren
(brace
id|seg
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|len
op_plus
id|iov-&gt;iov_len
op_ge
id|to
)paren
(brace
id|iov-&gt;iov_len
op_assign
id|to
op_minus
id|len
suffix:semicolon
r_break
suffix:semicolon
)brace
id|len
op_add_assign
id|iov-&gt;iov_len
suffix:semicolon
id|iov
op_increment
suffix:semicolon
)brace
r_return
id|seg
suffix:semicolon
)brace
DECL|variable|iov_shorten
id|EXPORT_SYMBOL
c_func
(paren
id|iov_shorten
)paren
suffix:semicolon
DECL|function|do_readv_writev
r_static
id|ssize_t
id|do_readv_writev
c_func
(paren
r_int
id|type
comma
r_struct
id|file
op_star
id|file
comma
r_const
r_struct
id|iovec
id|__user
op_star
id|uvector
comma
r_int
r_int
id|nr_segs
comma
id|loff_t
op_star
id|pos
)paren
(brace
r_typedef
id|ssize_t
(paren
op_star
id|io_fn_t
)paren
(paren
r_struct
id|file
op_star
comma
r_char
id|__user
op_star
comma
r_int
comma
id|loff_t
op_star
)paren
suffix:semicolon
r_typedef
id|ssize_t
(paren
op_star
id|iov_fn_t
)paren
(paren
r_struct
id|file
op_star
comma
r_const
r_struct
id|iovec
op_star
comma
r_int
r_int
comma
id|loff_t
op_star
)paren
suffix:semicolon
r_int
id|tot_len
suffix:semicolon
r_struct
id|iovec
id|iovstack
(braket
id|UIO_FASTIOV
)braket
suffix:semicolon
r_struct
id|iovec
op_star
id|iov
op_assign
id|iovstack
comma
op_star
id|vector
suffix:semicolon
id|ssize_t
id|ret
suffix:semicolon
r_int
id|seg
suffix:semicolon
id|io_fn_t
id|fn
suffix:semicolon
id|iov_fn_t
id|fnv
suffix:semicolon
r_struct
id|inode
op_star
id|inode
suffix:semicolon
multiline_comment|/*&n;&t; * SuS says &quot;The readv() function *may* fail if the iovcnt argument&n;&t; * was less than or equal to 0, or greater than {IOV_MAX}.  Linux has&n;&t; * traditionally returned zero for zero segments, so...&n;&t; */
id|ret
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|nr_segs
op_eq
l_int|0
)paren
r_goto
id|out
suffix:semicolon
multiline_comment|/*&n;&t; * First get the &quot;struct iovec&quot; from user memory and&n;&t; * verify all the pointers&n;&t; */
id|ret
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
(paren
id|nr_segs
OG
id|UIO_MAXIOV
)paren
op_logical_or
(paren
id|nr_segs
op_le
l_int|0
)paren
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|file-&gt;f_op
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|nr_segs
OG
id|UIO_FASTIOV
)paren
(brace
id|ret
op_assign
op_minus
id|ENOMEM
suffix:semicolon
id|iov
op_assign
id|kmalloc
c_func
(paren
id|nr_segs
op_star
r_sizeof
(paren
r_struct
id|iovec
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|iov
)paren
r_goto
id|out
suffix:semicolon
)brace
id|ret
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|iov
comma
id|uvector
comma
id|nr_segs
op_star
r_sizeof
(paren
op_star
id|uvector
)paren
)paren
)paren
r_goto
id|out
suffix:semicolon
multiline_comment|/*&n;&t; * Single unix specification:&n;&t; * We should -EINVAL if an element length is not &gt;= 0 and fitting an&n;&t; * ssize_t.  The total length is fitting an ssize_t&n;&t; *&n;&t; * Be careful here because iov_len is a size_t not an ssize_t&n;&t; */
id|tot_len
op_assign
l_int|0
suffix:semicolon
id|ret
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_for
c_loop
(paren
id|seg
op_assign
l_int|0
suffix:semicolon
id|seg
OL
id|nr_segs
suffix:semicolon
id|seg
op_increment
)paren
(brace
id|ssize_t
id|tmp
op_assign
id|tot_len
suffix:semicolon
id|ssize_t
id|len
op_assign
(paren
id|ssize_t
)paren
id|iov
(braket
id|seg
)braket
dot
id|iov_len
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
l_int|0
)paren
multiline_comment|/* size_t not fitting an ssize_t .. */
r_goto
id|out
suffix:semicolon
id|tot_len
op_add_assign
id|len
suffix:semicolon
r_if
c_cond
(paren
id|tot_len
OL
id|tmp
)paren
multiline_comment|/* maths overflow on the ssize_t */
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|tot_len
op_eq
l_int|0
)paren
(brace
id|ret
op_assign
l_int|0
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|inode
op_assign
id|file-&gt;f_dentry-&gt;d_inode
suffix:semicolon
multiline_comment|/* VERIFY_WRITE actually means a read, as we write to user space */
id|ret
op_assign
id|locks_verify_area
c_func
(paren
(paren
id|type
op_eq
id|READ
ques
c_cond
id|FLOCK_VERIFY_READ
suffix:colon
id|FLOCK_VERIFY_WRITE
)paren
comma
id|inode
comma
id|file
comma
op_star
id|pos
comma
id|tot_len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_goto
id|out
suffix:semicolon
id|fnv
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|type
op_eq
id|READ
)paren
(brace
id|fn
op_assign
id|file-&gt;f_op-&gt;read
suffix:semicolon
id|fnv
op_assign
id|file-&gt;f_op-&gt;readv
suffix:semicolon
)brace
r_else
(brace
id|fn
op_assign
(paren
id|io_fn_t
)paren
id|file-&gt;f_op-&gt;write
suffix:semicolon
id|fnv
op_assign
id|file-&gt;f_op-&gt;writev
suffix:semicolon
)brace
r_if
c_cond
(paren
id|fnv
)paren
(brace
id|ret
op_assign
id|fnv
c_func
(paren
id|file
comma
id|iov
comma
id|nr_segs
comma
id|pos
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/* Do it by hand, with file-ops */
id|ret
op_assign
l_int|0
suffix:semicolon
id|vector
op_assign
id|iov
suffix:semicolon
r_while
c_loop
(paren
id|nr_segs
OG
l_int|0
)paren
(brace
r_void
id|__user
op_star
id|base
suffix:semicolon
r_int
id|len
suffix:semicolon
id|ssize_t
id|nr
suffix:semicolon
id|base
op_assign
id|vector-&gt;iov_base
suffix:semicolon
id|len
op_assign
id|vector-&gt;iov_len
suffix:semicolon
id|vector
op_increment
suffix:semicolon
id|nr_segs
op_decrement
suffix:semicolon
id|nr
op_assign
id|fn
c_func
(paren
id|file
comma
id|base
comma
id|len
comma
id|pos
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nr
OL
l_int|0
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|ret
)paren
id|ret
op_assign
id|nr
suffix:semicolon
r_break
suffix:semicolon
)brace
id|ret
op_add_assign
id|nr
suffix:semicolon
r_if
c_cond
(paren
id|nr
op_ne
id|len
)paren
r_break
suffix:semicolon
)brace
id|out
suffix:colon
r_if
c_cond
(paren
id|iov
op_ne
id|iovstack
)paren
id|kfree
c_func
(paren
id|iov
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret
op_plus
(paren
id|type
op_eq
id|READ
)paren
)paren
OG
l_int|0
)paren
id|dnotify_parent
c_func
(paren
id|file-&gt;f_dentry
comma
(paren
id|type
op_eq
id|READ
)paren
ques
c_cond
id|DN_ACCESS
suffix:colon
id|DN_MODIFY
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|vfs_readv
id|ssize_t
id|vfs_readv
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_const
r_struct
id|iovec
id|__user
op_star
id|vec
comma
r_int
r_int
id|vlen
comma
id|loff_t
op_star
id|pos
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|file-&gt;f_mode
op_amp
id|FMODE_READ
)paren
)paren
r_return
op_minus
id|EBADF
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|file-&gt;f_op
op_logical_or
(paren
op_logical_neg
id|file-&gt;f_op-&gt;readv
op_logical_and
op_logical_neg
id|file-&gt;f_op-&gt;read
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_return
id|do_readv_writev
c_func
(paren
id|READ
comma
id|file
comma
id|vec
comma
id|vlen
comma
id|pos
)paren
suffix:semicolon
)brace
DECL|variable|vfs_readv
id|EXPORT_SYMBOL
c_func
(paren
id|vfs_readv
)paren
suffix:semicolon
DECL|function|vfs_writev
id|ssize_t
id|vfs_writev
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_const
r_struct
id|iovec
id|__user
op_star
id|vec
comma
r_int
r_int
id|vlen
comma
id|loff_t
op_star
id|pos
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|file-&gt;f_mode
op_amp
id|FMODE_WRITE
)paren
)paren
r_return
op_minus
id|EBADF
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|file-&gt;f_op
op_logical_or
(paren
op_logical_neg
id|file-&gt;f_op-&gt;writev
op_logical_and
op_logical_neg
id|file-&gt;f_op-&gt;write
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_return
id|do_readv_writev
c_func
(paren
id|WRITE
comma
id|file
comma
id|vec
comma
id|vlen
comma
id|pos
)paren
suffix:semicolon
)brace
DECL|variable|vfs_writev
id|EXPORT_SYMBOL
c_func
(paren
id|vfs_writev
)paren
suffix:semicolon
id|asmlinkage
id|ssize_t
DECL|function|sys_readv
id|sys_readv
c_func
(paren
r_int
r_int
id|fd
comma
r_const
r_struct
id|iovec
id|__user
op_star
id|vec
comma
r_int
r_int
id|vlen
)paren
(brace
r_struct
id|file
op_star
id|file
suffix:semicolon
id|ssize_t
id|ret
op_assign
op_minus
id|EBADF
suffix:semicolon
r_int
id|fput_needed
suffix:semicolon
id|file
op_assign
id|fget_light
c_func
(paren
id|fd
comma
op_amp
id|fput_needed
)paren
suffix:semicolon
r_if
c_cond
(paren
id|file
)paren
(brace
id|ret
op_assign
id|vfs_readv
c_func
(paren
id|file
comma
id|vec
comma
id|vlen
comma
op_amp
id|file-&gt;f_pos
)paren
suffix:semicolon
id|fput_light
c_func
(paren
id|file
comma
id|fput_needed
)paren
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
id|asmlinkage
id|ssize_t
DECL|function|sys_writev
id|sys_writev
c_func
(paren
r_int
r_int
id|fd
comma
r_const
r_struct
id|iovec
id|__user
op_star
id|vec
comma
r_int
r_int
id|vlen
)paren
(brace
r_struct
id|file
op_star
id|file
suffix:semicolon
id|ssize_t
id|ret
op_assign
op_minus
id|EBADF
suffix:semicolon
r_int
id|fput_needed
suffix:semicolon
id|file
op_assign
id|fget_light
c_func
(paren
id|fd
comma
op_amp
id|fput_needed
)paren
suffix:semicolon
r_if
c_cond
(paren
id|file
)paren
(brace
id|ret
op_assign
id|vfs_writev
c_func
(paren
id|file
comma
id|vec
comma
id|vlen
comma
op_amp
id|file-&gt;f_pos
)paren
suffix:semicolon
id|fput_light
c_func
(paren
id|file
comma
id|fput_needed
)paren
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|function|do_sendfile
r_static
id|ssize_t
id|do_sendfile
c_func
(paren
r_int
id|out_fd
comma
r_int
id|in_fd
comma
id|loff_t
op_star
id|ppos
comma
r_int
id|count
comma
id|loff_t
id|max
)paren
(brace
r_struct
id|file
op_star
id|in_file
comma
op_star
id|out_file
suffix:semicolon
r_struct
id|inode
op_star
id|in_inode
comma
op_star
id|out_inode
suffix:semicolon
id|loff_t
id|pos
suffix:semicolon
id|ssize_t
id|retval
suffix:semicolon
r_int
id|fput_needed_in
comma
id|fput_needed_out
suffix:semicolon
multiline_comment|/*&n;&t; * Get input file, and verify that it is ok..&n;&t; */
id|retval
op_assign
op_minus
id|EBADF
suffix:semicolon
id|in_file
op_assign
id|fget_light
c_func
(paren
id|in_fd
comma
op_amp
id|fput_needed_in
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|in_file
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|in_file-&gt;f_mode
op_amp
id|FMODE_READ
)paren
)paren
r_goto
id|fput_in
suffix:semicolon
id|retval
op_assign
op_minus
id|EINVAL
suffix:semicolon
id|in_inode
op_assign
id|in_file-&gt;f_dentry-&gt;d_inode
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|in_inode
)paren
r_goto
id|fput_in
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|in_file-&gt;f_op
op_logical_or
op_logical_neg
id|in_file-&gt;f_op-&gt;sendfile
)paren
r_goto
id|fput_in
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ppos
)paren
id|ppos
op_assign
op_amp
id|in_file-&gt;f_pos
suffix:semicolon
id|retval
op_assign
id|locks_verify_area
c_func
(paren
id|FLOCK_VERIFY_READ
comma
id|in_inode
comma
id|in_file
comma
op_star
id|ppos
comma
id|count
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
r_goto
id|fput_in
suffix:semicolon
id|retval
op_assign
id|security_file_permission
(paren
id|in_file
comma
id|MAY_READ
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
r_goto
id|fput_in
suffix:semicolon
multiline_comment|/*&n;&t; * Get output file, and verify that it is ok..&n;&t; */
id|retval
op_assign
op_minus
id|EBADF
suffix:semicolon
id|out_file
op_assign
id|fget_light
c_func
(paren
id|out_fd
comma
op_amp
id|fput_needed_out
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|out_file
)paren
r_goto
id|fput_in
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|out_file-&gt;f_mode
op_amp
id|FMODE_WRITE
)paren
)paren
r_goto
id|fput_out
suffix:semicolon
id|retval
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|out_file-&gt;f_op
op_logical_or
op_logical_neg
id|out_file-&gt;f_op-&gt;sendpage
)paren
r_goto
id|fput_out
suffix:semicolon
id|out_inode
op_assign
id|out_file-&gt;f_dentry-&gt;d_inode
suffix:semicolon
id|retval
op_assign
id|locks_verify_area
c_func
(paren
id|FLOCK_VERIFY_WRITE
comma
id|out_inode
comma
id|out_file
comma
id|out_file-&gt;f_pos
comma
id|count
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
r_goto
id|fput_out
suffix:semicolon
id|retval
op_assign
id|security_file_permission
(paren
id|out_file
comma
id|MAY_WRITE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
r_goto
id|fput_out
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|max
)paren
id|max
op_assign
id|min
c_func
(paren
id|in_inode-&gt;i_sb-&gt;s_maxbytes
comma
id|out_inode-&gt;i_sb-&gt;s_maxbytes
)paren
suffix:semicolon
id|pos
op_assign
op_star
id|ppos
suffix:semicolon
id|retval
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|pos
OL
l_int|0
)paren
)paren
r_goto
id|fput_out
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|pos
op_plus
id|count
OG
id|max
)paren
)paren
(brace
id|retval
op_assign
op_minus
id|EOVERFLOW
suffix:semicolon
r_if
c_cond
(paren
id|pos
op_ge
id|max
)paren
r_goto
id|fput_out
suffix:semicolon
id|count
op_assign
id|max
op_minus
id|pos
suffix:semicolon
)brace
id|retval
op_assign
id|in_file-&gt;f_op
op_member_access_from_pointer
id|sendfile
c_func
(paren
id|in_file
comma
id|ppos
comma
id|count
comma
id|file_send_actor
comma
id|out_file
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|ppos
OG
id|max
)paren
id|retval
op_assign
op_minus
id|EOVERFLOW
suffix:semicolon
id|fput_out
suffix:colon
id|fput_light
c_func
(paren
id|out_file
comma
id|fput_needed_out
)paren
suffix:semicolon
id|fput_in
suffix:colon
id|fput_light
c_func
(paren
id|in_file
comma
id|fput_needed_in
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|sys_sendfile
id|asmlinkage
id|ssize_t
id|sys_sendfile
c_func
(paren
r_int
id|out_fd
comma
r_int
id|in_fd
comma
id|off_t
id|__user
op_star
id|offset
comma
r_int
id|count
)paren
(brace
id|loff_t
id|pos
suffix:semicolon
id|off_t
id|off
suffix:semicolon
id|ssize_t
id|ret
suffix:semicolon
r_if
c_cond
(paren
id|offset
)paren
(brace
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|get_user
c_func
(paren
id|off
comma
id|offset
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|pos
op_assign
id|off
suffix:semicolon
id|ret
op_assign
id|do_sendfile
c_func
(paren
id|out_fd
comma
id|in_fd
comma
op_amp
id|pos
comma
id|count
comma
id|MAX_NON_LFS
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|put_user
c_func
(paren
id|pos
comma
id|offset
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
r_return
id|do_sendfile
c_func
(paren
id|out_fd
comma
id|in_fd
comma
l_int|NULL
comma
id|count
comma
id|MAX_NON_LFS
)paren
suffix:semicolon
)brace
DECL|function|sys_sendfile64
id|asmlinkage
id|ssize_t
id|sys_sendfile64
c_func
(paren
r_int
id|out_fd
comma
r_int
id|in_fd
comma
id|loff_t
id|__user
op_star
id|offset
comma
r_int
id|count
)paren
(brace
id|loff_t
id|pos
suffix:semicolon
id|ssize_t
id|ret
suffix:semicolon
r_if
c_cond
(paren
id|offset
)paren
(brace
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|copy_from_user
c_func
(paren
op_amp
id|pos
comma
id|offset
comma
r_sizeof
(paren
id|loff_t
)paren
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|ret
op_assign
id|do_sendfile
c_func
(paren
id|out_fd
comma
id|in_fd
comma
op_amp
id|pos
comma
id|count
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|put_user
c_func
(paren
id|pos
comma
id|offset
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
r_return
id|do_sendfile
c_func
(paren
id|out_fd
comma
id|in_fd
comma
l_int|NULL
comma
id|count
comma
l_int|0
)paren
suffix:semicolon
)brace
eof
