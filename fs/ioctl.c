multiline_comment|/*&n; *  linux/fs/ioctl.c&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; */
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/file.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/security.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/ioctls.h&gt;
DECL|function|file_ioctl
r_static
r_int
id|file_ioctl
c_func
(paren
r_struct
id|file
op_star
id|filp
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
(brace
r_int
id|error
suffix:semicolon
r_int
id|block
suffix:semicolon
r_struct
id|inode
op_star
id|inode
op_assign
id|filp-&gt;f_dentry-&gt;d_inode
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|FIBMAP
suffix:colon
(brace
r_struct
id|address_space
op_star
id|mapping
op_assign
id|inode-&gt;i_mapping
suffix:semicolon
r_int
id|res
suffix:semicolon
multiline_comment|/* do we support this mess? */
r_if
c_cond
(paren
op_logical_neg
id|mapping-&gt;a_ops-&gt;bmap
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_SYS_RAWIO
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
r_if
c_cond
(paren
(paren
id|error
op_assign
id|get_user
c_func
(paren
id|block
comma
(paren
r_int
op_star
)paren
id|arg
)paren
)paren
op_ne
l_int|0
)paren
r_return
id|error
suffix:semicolon
id|res
op_assign
id|mapping-&gt;a_ops
op_member_access_from_pointer
id|bmap
c_func
(paren
id|mapping
comma
id|block
)paren
suffix:semicolon
r_return
id|put_user
c_func
(paren
id|res
comma
(paren
r_int
op_star
)paren
id|arg
)paren
suffix:semicolon
)brace
r_case
id|FIGETBSZ
suffix:colon
r_if
c_cond
(paren
id|inode-&gt;i_sb
op_eq
l_int|NULL
)paren
r_return
op_minus
id|EBADF
suffix:semicolon
r_return
id|put_user
c_func
(paren
id|inode-&gt;i_sb-&gt;s_blocksize
comma
(paren
r_int
op_star
)paren
id|arg
)paren
suffix:semicolon
r_case
id|FIONREAD
suffix:colon
r_return
id|put_user
c_func
(paren
id|i_size_read
c_func
(paren
id|inode
)paren
op_minus
id|filp-&gt;f_pos
comma
(paren
r_int
op_star
)paren
id|arg
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|filp-&gt;f_op
op_logical_and
id|filp-&gt;f_op-&gt;ioctl
)paren
r_return
id|filp-&gt;f_op
op_member_access_from_pointer
id|ioctl
c_func
(paren
id|inode
comma
id|filp
comma
id|cmd
comma
id|arg
)paren
suffix:semicolon
r_return
op_minus
id|ENOTTY
suffix:semicolon
)brace
DECL|function|sys_ioctl
id|asmlinkage
r_int
id|sys_ioctl
c_func
(paren
r_int
r_int
id|fd
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
(brace
r_struct
id|file
op_star
id|filp
suffix:semicolon
r_int
r_int
id|flag
suffix:semicolon
r_int
id|on
comma
id|error
op_assign
op_minus
id|EBADF
suffix:semicolon
id|filp
op_assign
id|fget
c_func
(paren
id|fd
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|filp
)paren
r_goto
id|out
suffix:semicolon
id|error
op_assign
id|security_file_ioctl
c_func
(paren
id|filp
comma
id|cmd
comma
id|arg
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
(brace
id|fput
c_func
(paren
id|filp
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|FIOCLEX
suffix:colon
id|set_close_on_exec
c_func
(paren
id|fd
comma
l_int|1
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|FIONCLEX
suffix:colon
id|set_close_on_exec
c_func
(paren
id|fd
comma
l_int|0
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|FIONBIO
suffix:colon
r_if
c_cond
(paren
(paren
id|error
op_assign
id|get_user
c_func
(paren
id|on
comma
(paren
r_int
id|__user
op_star
)paren
id|arg
)paren
)paren
op_ne
l_int|0
)paren
r_break
suffix:semicolon
id|flag
op_assign
id|O_NONBLOCK
suffix:semicolon
macro_line|#ifdef __sparc__
multiline_comment|/* SunOS compatibility item. */
r_if
c_cond
(paren
id|O_NONBLOCK
op_ne
id|O_NDELAY
)paren
(brace
id|flag
op_or_assign
id|O_NDELAY
suffix:semicolon
)brace
macro_line|#endif
r_if
c_cond
(paren
id|on
)paren
id|filp-&gt;f_flags
op_or_assign
id|flag
suffix:semicolon
r_else
id|filp-&gt;f_flags
op_and_assign
op_complement
id|flag
suffix:semicolon
r_break
suffix:semicolon
r_case
id|FIOASYNC
suffix:colon
r_if
c_cond
(paren
(paren
id|error
op_assign
id|get_user
c_func
(paren
id|on
comma
(paren
r_int
id|__user
op_star
)paren
id|arg
)paren
)paren
op_ne
l_int|0
)paren
r_break
suffix:semicolon
id|flag
op_assign
id|on
ques
c_cond
id|FASYNC
suffix:colon
l_int|0
suffix:semicolon
multiline_comment|/* Did FASYNC state change ? */
r_if
c_cond
(paren
(paren
id|flag
op_xor
id|filp-&gt;f_flags
)paren
op_amp
id|FASYNC
)paren
(brace
r_if
c_cond
(paren
id|filp-&gt;f_op
op_logical_and
id|filp-&gt;f_op-&gt;fasync
)paren
id|error
op_assign
id|filp-&gt;f_op
op_member_access_from_pointer
id|fasync
c_func
(paren
id|fd
comma
id|filp
comma
id|on
)paren
suffix:semicolon
r_else
id|error
op_assign
op_minus
id|ENOTTY
suffix:semicolon
)brace
r_if
c_cond
(paren
id|error
op_ne
l_int|0
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|on
)paren
id|filp-&gt;f_flags
op_or_assign
id|FASYNC
suffix:semicolon
r_else
id|filp-&gt;f_flags
op_and_assign
op_complement
id|FASYNC
suffix:semicolon
r_break
suffix:semicolon
r_case
id|FIOQSIZE
suffix:colon
r_if
c_cond
(paren
id|S_ISDIR
c_func
(paren
id|filp-&gt;f_dentry-&gt;d_inode-&gt;i_mode
)paren
op_logical_or
id|S_ISREG
c_func
(paren
id|filp-&gt;f_dentry-&gt;d_inode-&gt;i_mode
)paren
op_logical_or
id|S_ISLNK
c_func
(paren
id|filp-&gt;f_dentry-&gt;d_inode-&gt;i_mode
)paren
)paren
(brace
id|loff_t
id|res
op_assign
id|inode_get_bytes
c_func
(paren
id|filp-&gt;f_dentry-&gt;d_inode
)paren
suffix:semicolon
id|error
op_assign
id|copy_to_user
c_func
(paren
(paren
id|loff_t
id|__user
op_star
)paren
id|arg
comma
op_amp
id|res
comma
r_sizeof
(paren
id|res
)paren
)paren
ques
c_cond
op_minus
id|EFAULT
suffix:colon
l_int|0
suffix:semicolon
)brace
r_else
id|error
op_assign
op_minus
id|ENOTTY
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|error
op_assign
op_minus
id|ENOTTY
suffix:semicolon
r_if
c_cond
(paren
id|S_ISREG
c_func
(paren
id|filp-&gt;f_dentry-&gt;d_inode-&gt;i_mode
)paren
)paren
id|error
op_assign
id|file_ioctl
c_func
(paren
id|filp
comma
id|cmd
comma
id|arg
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|filp-&gt;f_op
op_logical_and
id|filp-&gt;f_op-&gt;ioctl
)paren
id|error
op_assign
id|filp-&gt;f_op
op_member_access_from_pointer
id|ioctl
c_func
(paren
id|filp-&gt;f_dentry-&gt;d_inode
comma
id|filp
comma
id|cmd
comma
id|arg
)paren
suffix:semicolon
)brace
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
id|fput
c_func
(paren
id|filp
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|error
suffix:semicolon
)brace
eof
