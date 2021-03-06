multiline_comment|/*&n; *&t;fs/nfsctl.c&n; *&n; *&t;This should eventually move to userland.&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/file.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/sunrpc/svc.h&gt;
macro_line|#include &lt;linux/nfsd/nfsd.h&gt;
macro_line|#include &lt;linux/nfsd/syscall.h&gt;
macro_line|#include &lt;linux/linkage.h&gt;
macro_line|#include &lt;linux/namei.h&gt;
macro_line|#include &lt;linux/mount.h&gt;
macro_line|#include &lt;linux/syscalls.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
multiline_comment|/*&n; * open a file on nfsd fs&n; */
DECL|function|do_open
r_static
r_struct
id|file
op_star
id|do_open
c_func
(paren
r_char
op_star
id|name
comma
r_int
id|flags
)paren
(brace
r_struct
id|nameidata
id|nd
suffix:semicolon
r_int
id|error
suffix:semicolon
id|nd.mnt
op_assign
id|do_kern_mount
c_func
(paren
l_string|&quot;nfsd&quot;
comma
l_int|0
comma
l_string|&quot;nfsd&quot;
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|nd.mnt
)paren
)paren
r_return
(paren
r_struct
id|file
op_star
)paren
id|nd.mnt
suffix:semicolon
id|nd.dentry
op_assign
id|dget
c_func
(paren
id|nd.mnt-&gt;mnt_root
)paren
suffix:semicolon
id|nd.last_type
op_assign
id|LAST_ROOT
suffix:semicolon
id|nd.flags
op_assign
l_int|0
suffix:semicolon
id|nd.depth
op_assign
l_int|0
suffix:semicolon
id|error
op_assign
id|path_walk
c_func
(paren
id|name
comma
op_amp
id|nd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_return
id|ERR_PTR
c_func
(paren
id|error
)paren
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_eq
id|O_RDWR
)paren
id|error
op_assign
id|may_open
c_func
(paren
op_amp
id|nd
comma
id|MAY_READ
op_or
id|MAY_WRITE
comma
id|FMODE_READ
op_or
id|FMODE_WRITE
)paren
suffix:semicolon
r_else
id|error
op_assign
id|may_open
c_func
(paren
op_amp
id|nd
comma
id|MAY_WRITE
comma
id|FMODE_WRITE
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|error
)paren
r_return
id|dentry_open
c_func
(paren
id|nd.dentry
comma
id|nd.mnt
comma
id|flags
)paren
suffix:semicolon
id|path_release
c_func
(paren
op_amp
id|nd
)paren
suffix:semicolon
r_return
id|ERR_PTR
c_func
(paren
id|error
)paren
suffix:semicolon
)brace
r_static
r_struct
(brace
DECL|member|name
DECL|member|wsize
DECL|member|rsize
r_char
op_star
id|name
suffix:semicolon
r_int
id|wsize
suffix:semicolon
r_int
id|rsize
suffix:semicolon
DECL|variable|map
)brace
id|map
(braket
)braket
op_assign
(brace
(braket
id|NFSCTL_SVC
)braket
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;.svc&quot;
comma
dot
id|wsize
op_assign
r_sizeof
(paren
r_struct
id|nfsctl_svc
)paren
)brace
comma
(braket
id|NFSCTL_ADDCLIENT
)braket
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;.add&quot;
comma
dot
id|wsize
op_assign
r_sizeof
(paren
r_struct
id|nfsctl_client
)paren
)brace
comma
(braket
id|NFSCTL_DELCLIENT
)braket
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;.del&quot;
comma
dot
id|wsize
op_assign
r_sizeof
(paren
r_struct
id|nfsctl_client
)paren
)brace
comma
(braket
id|NFSCTL_EXPORT
)braket
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;.export&quot;
comma
dot
id|wsize
op_assign
r_sizeof
(paren
r_struct
id|nfsctl_export
)paren
)brace
comma
(braket
id|NFSCTL_UNEXPORT
)braket
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;.unexport&quot;
comma
dot
id|wsize
op_assign
r_sizeof
(paren
r_struct
id|nfsctl_export
)paren
)brace
comma
(braket
id|NFSCTL_GETFD
)braket
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;.getfd&quot;
comma
dot
id|wsize
op_assign
r_sizeof
(paren
r_struct
id|nfsctl_fdparm
)paren
comma
dot
id|rsize
op_assign
id|NFS_FHSIZE
)brace
comma
(braket
id|NFSCTL_GETFS
)braket
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;.getfs&quot;
comma
dot
id|wsize
op_assign
r_sizeof
(paren
r_struct
id|nfsctl_fsparm
)paren
comma
dot
id|rsize
op_assign
r_sizeof
(paren
r_struct
id|knfsd_fh
)paren
)brace
comma
)brace
suffix:semicolon
r_int
DECL|function|sys_nfsservctl
id|asmlinkage
id|sys_nfsservctl
c_func
(paren
r_int
id|cmd
comma
r_struct
id|nfsctl_arg
id|__user
op_star
id|arg
comma
r_void
id|__user
op_star
id|res
)paren
(brace
r_struct
id|file
op_star
id|file
suffix:semicolon
r_void
id|__user
op_star
id|p
op_assign
op_amp
id|arg-&gt;u
suffix:semicolon
r_int
id|version
suffix:semicolon
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|version
comma
op_amp
id|arg-&gt;ca_version
comma
r_sizeof
(paren
r_int
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|version
op_ne
id|NFSCTL_VERSION
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;nfsd: incompatible version in syscall.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cmd
OL
l_int|0
op_logical_or
id|cmd
op_ge
r_sizeof
(paren
id|map
)paren
op_div
r_sizeof
(paren
id|map
(braket
l_int|0
)braket
)paren
op_logical_or
op_logical_neg
id|map
(braket
id|cmd
)braket
dot
id|name
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|file
op_assign
id|do_open
c_func
(paren
id|map
(braket
id|cmd
)braket
dot
id|name
comma
id|map
(braket
id|cmd
)braket
dot
id|rsize
ques
c_cond
id|O_RDWR
suffix:colon
id|O_WRONLY
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|file
)paren
)paren
r_return
id|PTR_ERR
c_func
(paren
id|file
)paren
suffix:semicolon
id|err
op_assign
id|file-&gt;f_op
op_member_access_from_pointer
id|write
c_func
(paren
id|file
comma
id|p
comma
id|map
(braket
id|cmd
)braket
dot
id|wsize
comma
op_amp
id|file-&gt;f_pos
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
op_ge
l_int|0
op_logical_and
id|map
(braket
id|cmd
)braket
dot
id|rsize
)paren
id|err
op_assign
id|file-&gt;f_op
op_member_access_from_pointer
id|read
c_func
(paren
id|file
comma
id|res
comma
id|map
(braket
id|cmd
)braket
dot
id|rsize
comma
op_amp
id|file-&gt;f_pos
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
op_ge
l_int|0
)paren
id|err
op_assign
l_int|0
suffix:semicolon
id|fput
c_func
(paren
id|file
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
eof
