multiline_comment|/*&n; * linux/fs/nfsd/nfsctl.c&n; *&n; * Syscall interface to knfsd.&n; *&n; * Copyright (C) 1995, 1996 Olaf Kirch &lt;okir@monad.swb.de&gt;&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/linkage.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/net.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/seq_file.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/nfs.h&gt;
macro_line|#include &lt;linux/sunrpc/svc.h&gt;
macro_line|#include &lt;linux/nfsd/nfsd.h&gt;
macro_line|#include &lt;linux/nfsd/cache.h&gt;
macro_line|#include &lt;linux/nfsd/xdr.h&gt;
macro_line|#include &lt;linux/nfsd/syscall.h&gt;
macro_line|#include &lt;linux/nfsd/interface.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
multiline_comment|/*&n; *&t;We have a single directory with 8 nodes in it.&n; */
r_enum
(brace
DECL|enumerator|NFSD_Root
id|NFSD_Root
op_assign
l_int|1
comma
DECL|enumerator|NFSD_Svc
id|NFSD_Svc
comma
DECL|enumerator|NFSD_Add
id|NFSD_Add
comma
DECL|enumerator|NFSD_Del
id|NFSD_Del
comma
DECL|enumerator|NFSD_Export
id|NFSD_Export
comma
DECL|enumerator|NFSD_Unexport
id|NFSD_Unexport
comma
DECL|enumerator|NFSD_Getfd
id|NFSD_Getfd
comma
DECL|enumerator|NFSD_Getfs
id|NFSD_Getfs
comma
DECL|enumerator|NFSD_List
id|NFSD_List
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * write() for these nodes.&n; */
r_static
id|ssize_t
id|write_svc
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
id|size
)paren
suffix:semicolon
r_static
id|ssize_t
id|write_add
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
id|size
)paren
suffix:semicolon
r_static
id|ssize_t
id|write_del
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
id|size
)paren
suffix:semicolon
r_static
id|ssize_t
id|write_export
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
id|size
)paren
suffix:semicolon
r_static
id|ssize_t
id|write_unexport
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
id|size
)paren
suffix:semicolon
r_static
id|ssize_t
id|write_getfd
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
id|size
)paren
suffix:semicolon
r_static
id|ssize_t
id|write_getfs
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
id|size
)paren
suffix:semicolon
DECL|variable|write_op
r_static
id|ssize_t
(paren
op_star
id|write_op
(braket
)braket
)paren
(paren
r_struct
id|file
op_star
comma
r_const
r_char
op_star
comma
r_int
)paren
op_assign
(brace
(braket
id|NFSD_Svc
)braket
op_assign
id|write_svc
comma
(braket
id|NFSD_Add
)braket
op_assign
id|write_add
comma
(braket
id|NFSD_Del
)braket
op_assign
id|write_del
comma
(braket
id|NFSD_Export
)braket
op_assign
id|write_export
comma
(braket
id|NFSD_Unexport
)braket
op_assign
id|write_unexport
comma
(braket
id|NFSD_Getfd
)braket
op_assign
id|write_getfd
comma
(braket
id|NFSD_Getfs
)braket
op_assign
id|write_getfs
comma
)brace
suffix:semicolon
DECL|function|fs_write
r_static
id|ssize_t
id|fs_write
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
id|size
comma
id|loff_t
op_star
id|pos
)paren
(brace
id|ino_t
id|ino
op_assign
id|file-&gt;f_dentry-&gt;d_inode-&gt;i_ino
suffix:semicolon
r_if
c_cond
(paren
id|ino
op_ge
r_sizeof
(paren
id|write_op
)paren
op_div
r_sizeof
(paren
id|write_op
(braket
l_int|0
)braket
)paren
op_logical_or
op_logical_neg
id|write_op
(braket
id|ino
)braket
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_return
id|write_op
(braket
id|ino
)braket
(paren
id|file
comma
id|buf
comma
id|size
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * read(), open() and release() for getfs and getfd (read/write ones).&n; * IO on these is a simple transaction - you open() the file, write() to it&n; * and that generates a (stored) response.  After that read() will simply&n; * access that response.&n; */
DECL|function|TA_read
r_static
id|ssize_t
id|TA_read
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
id|size
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
id|file-&gt;private_data
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_star
id|pos
op_ge
id|file-&gt;f_dentry-&gt;d_inode-&gt;i_size
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_star
id|pos
op_plus
id|size
OG
id|file-&gt;f_dentry-&gt;d_inode-&gt;i_size
)paren
id|size
op_assign
id|file-&gt;f_dentry-&gt;d_inode-&gt;i_size
op_minus
op_star
id|pos
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|buf
comma
id|file-&gt;private_data
op_plus
op_star
id|pos
comma
id|size
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
op_star
id|pos
op_add_assign
id|size
suffix:semicolon
r_return
id|size
suffix:semicolon
)brace
DECL|function|TA_open
r_static
r_int
id|TA_open
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
id|file-&gt;private_data
op_assign
l_int|NULL
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|TA_release
r_static
r_int
id|TA_release
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
r_void
op_star
id|p
op_assign
id|file-&gt;private_data
suffix:semicolon
id|file-&gt;private_data
op_assign
l_int|NULL
suffix:semicolon
id|kfree
c_func
(paren
id|p
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|writer_ops
r_static
r_struct
id|file_operations
id|writer_ops
op_assign
(brace
dot
id|write
op_assign
id|fs_write
comma
)brace
suffix:semicolon
DECL|variable|reader_ops
r_static
r_struct
id|file_operations
id|reader_ops
op_assign
(brace
dot
id|write
op_assign
id|fs_write
comma
dot
id|read
op_assign
id|TA_read
comma
dot
id|open
op_assign
id|TA_open
comma
dot
id|release
op_assign
id|TA_release
comma
)brace
suffix:semicolon
r_extern
r_struct
id|seq_operations
id|nfs_exports_op
suffix:semicolon
DECL|function|exports_open
r_static
r_int
id|exports_open
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
r_int
id|res
suffix:semicolon
id|res
op_assign
id|seq_open
c_func
(paren
id|file
comma
op_amp
id|nfs_exports_op
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|res
)paren
(brace
r_char
op_star
id|namebuf
op_assign
id|kmalloc
c_func
(paren
id|PAGE_SIZE
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|namebuf
op_eq
l_int|NULL
)paren
id|res
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_else
(paren
(paren
r_struct
id|seq_file
op_star
)paren
id|file-&gt;private_data
)paren
op_member_access_from_pointer
r_private
op_assign
id|namebuf
suffix:semicolon
)brace
r_return
id|res
suffix:semicolon
)brace
DECL|function|exports_release
r_static
r_int
id|exports_release
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
r_struct
id|seq_file
op_star
id|m
op_assign
(paren
r_struct
id|seq_file
op_star
)paren
id|file-&gt;private_data
suffix:semicolon
id|kfree
c_func
(paren
id|m
op_member_access_from_pointer
r_private
)paren
suffix:semicolon
id|m
op_member_access_from_pointer
r_private
op_assign
l_int|NULL
suffix:semicolon
r_return
id|seq_release
c_func
(paren
id|inode
comma
id|file
)paren
suffix:semicolon
)brace
DECL|variable|exports_operations
r_static
r_struct
id|file_operations
id|exports_operations
op_assign
(brace
dot
id|open
op_assign
id|exports_open
comma
dot
id|read
op_assign
id|seq_read
comma
dot
id|llseek
op_assign
id|seq_lseek
comma
dot
id|release
op_assign
id|exports_release
comma
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;Description of fs contents.&n; */
DECL|member|name
DECL|member|ops
DECL|member|mode
DECL|variable|files
r_static
r_struct
(brace
r_char
op_star
id|name
suffix:semicolon
r_struct
id|file_operations
op_star
id|ops
suffix:semicolon
r_int
id|mode
suffix:semicolon
)brace
id|files
(braket
)braket
op_assign
(brace
(braket
id|NFSD_Svc
)braket
op_assign
(brace
l_string|&quot;svc&quot;
comma
op_amp
id|writer_ops
comma
id|S_IWUSR
)brace
comma
(braket
id|NFSD_Add
)braket
op_assign
(brace
l_string|&quot;add&quot;
comma
op_amp
id|writer_ops
comma
id|S_IWUSR
)brace
comma
(braket
id|NFSD_Del
)braket
op_assign
(brace
l_string|&quot;del&quot;
comma
op_amp
id|writer_ops
comma
id|S_IWUSR
)brace
comma
(braket
id|NFSD_Export
)braket
op_assign
(brace
l_string|&quot;export&quot;
comma
op_amp
id|writer_ops
comma
id|S_IWUSR
)brace
comma
(braket
id|NFSD_Unexport
)braket
op_assign
(brace
l_string|&quot;unexport&quot;
comma
op_amp
id|writer_ops
comma
id|S_IWUSR
)brace
comma
(braket
id|NFSD_Getfd
)braket
op_assign
(brace
l_string|&quot;getfd&quot;
comma
op_amp
id|reader_ops
comma
id|S_IWUSR
op_or
id|S_IRUSR
)brace
comma
(braket
id|NFSD_Getfs
)braket
op_assign
(brace
l_string|&quot;getfs&quot;
comma
op_amp
id|reader_ops
comma
id|S_IWUSR
op_or
id|S_IRUSR
)brace
comma
(braket
id|NFSD_List
)braket
op_assign
(brace
l_string|&quot;exports&quot;
comma
op_amp
id|exports_operations
comma
id|S_IRUGO
)brace
comma
)brace
suffix:semicolon
multiline_comment|/*----------------------------------------------------------------------------*/
multiline_comment|/*&n; * payload - write methods&n; */
DECL|function|write_svc
r_static
id|ssize_t
id|write_svc
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
id|size
)paren
(brace
r_struct
id|nfsctl_svc
id|data
suffix:semicolon
r_if
c_cond
(paren
id|size
OL
r_sizeof
(paren
id|data
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|data
comma
id|buf
comma
id|size
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
id|nfsd_svc
c_func
(paren
id|data.svc_port
comma
id|data.svc_nthreads
)paren
suffix:semicolon
)brace
DECL|function|write_add
r_static
id|ssize_t
id|write_add
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
id|size
)paren
(brace
r_struct
id|nfsctl_client
id|data
suffix:semicolon
r_if
c_cond
(paren
id|size
OL
r_sizeof
(paren
id|data
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|data
comma
id|buf
comma
id|size
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
id|exp_addclient
c_func
(paren
op_amp
id|data
)paren
suffix:semicolon
)brace
DECL|function|write_del
r_static
id|ssize_t
id|write_del
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
id|size
)paren
(brace
r_struct
id|nfsctl_client
id|data
suffix:semicolon
r_if
c_cond
(paren
id|size
OL
r_sizeof
(paren
id|data
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|data
comma
id|buf
comma
id|size
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
id|exp_delclient
c_func
(paren
op_amp
id|data
)paren
suffix:semicolon
)brace
DECL|function|write_export
r_static
id|ssize_t
id|write_export
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
id|size
)paren
(brace
r_struct
id|nfsctl_export
id|data
suffix:semicolon
r_if
c_cond
(paren
id|size
OL
r_sizeof
(paren
id|data
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|data
comma
id|buf
comma
id|size
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
id|exp_export
c_func
(paren
op_amp
id|data
)paren
suffix:semicolon
)brace
DECL|function|write_unexport
r_static
id|ssize_t
id|write_unexport
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
id|size
)paren
(brace
r_struct
id|nfsctl_export
id|data
suffix:semicolon
r_if
c_cond
(paren
id|size
OL
r_sizeof
(paren
id|data
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|data
comma
id|buf
comma
id|size
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
id|exp_unexport
c_func
(paren
op_amp
id|data
)paren
suffix:semicolon
)brace
DECL|function|write_getfs
r_static
id|ssize_t
id|write_getfs
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
id|size
)paren
(brace
r_struct
id|nfsctl_fsparm
id|data
suffix:semicolon
r_struct
id|sockaddr_in
op_star
id|sin
suffix:semicolon
r_struct
id|auth_domain
op_star
id|clp
suffix:semicolon
r_int
id|err
op_assign
l_int|0
suffix:semicolon
r_struct
id|knfsd_fh
op_star
id|res
suffix:semicolon
r_if
c_cond
(paren
id|file-&gt;private_data
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|size
OL
r_sizeof
(paren
id|data
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|data
comma
id|buf
comma
id|size
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|data.gd_addr.sa_family
op_ne
id|AF_INET
)paren
r_return
op_minus
id|EPROTONOSUPPORT
suffix:semicolon
id|sin
op_assign
(paren
r_struct
id|sockaddr_in
op_star
)paren
op_amp
id|data.gd_addr
suffix:semicolon
r_if
c_cond
(paren
id|data.gd_maxlen
OG
id|NFS3_FHSIZE
)paren
id|data.gd_maxlen
op_assign
id|NFS3_FHSIZE
suffix:semicolon
id|res
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|knfsd_fh
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|res
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|memset
c_func
(paren
id|res
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|knfsd_fh
)paren
)paren
suffix:semicolon
id|exp_readlock
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|clp
op_assign
id|auth_unix_lookup
c_func
(paren
id|sin-&gt;sin_addr
)paren
)paren
)paren
id|err
op_assign
op_minus
id|EPERM
suffix:semicolon
r_else
(brace
id|err
op_assign
id|exp_rootfh
c_func
(paren
id|clp
comma
id|data.gd_path
comma
id|res
comma
id|data.gd_maxlen
)paren
suffix:semicolon
id|auth_domain_put
c_func
(paren
id|clp
)paren
suffix:semicolon
)brace
id|exp_readunlock
c_func
(paren
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|file-&gt;f_dentry-&gt;d_inode-&gt;i_sem
)paren
suffix:semicolon
r_if
c_cond
(paren
id|file-&gt;private_data
)paren
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
id|kfree
c_func
(paren
id|res
)paren
suffix:semicolon
r_else
(brace
id|file-&gt;f_dentry-&gt;d_inode-&gt;i_size
op_assign
id|res-&gt;fh_size
op_plus
(paren
r_int
)paren
op_amp
(paren
(paren
r_struct
id|knfsd_fh
op_star
)paren
l_int|0
)paren
op_member_access_from_pointer
id|fh_base
suffix:semicolon
id|file-&gt;private_data
op_assign
id|res
suffix:semicolon
id|err
op_assign
r_sizeof
(paren
id|data
)paren
suffix:semicolon
)brace
id|up
c_func
(paren
op_amp
id|file-&gt;f_dentry-&gt;d_inode-&gt;i_sem
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|write_getfd
r_static
id|ssize_t
id|write_getfd
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
id|size
)paren
(brace
r_struct
id|nfsctl_fdparm
id|data
suffix:semicolon
r_struct
id|sockaddr_in
op_star
id|sin
suffix:semicolon
r_struct
id|auth_domain
op_star
id|clp
suffix:semicolon
r_int
id|err
op_assign
l_int|0
suffix:semicolon
r_struct
id|knfsd_fh
id|fh
suffix:semicolon
r_char
op_star
id|res
suffix:semicolon
r_if
c_cond
(paren
id|file-&gt;private_data
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|size
OL
r_sizeof
(paren
id|data
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|data
comma
id|buf
comma
id|size
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|data.gd_addr.sa_family
op_ne
id|AF_INET
)paren
r_return
op_minus
id|EPROTONOSUPPORT
suffix:semicolon
r_if
c_cond
(paren
id|data.gd_version
template_param
id|NFSSVC_MAXVERS
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|res
op_assign
id|kmalloc
c_func
(paren
id|NFS_FHSIZE
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|res
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|sin
op_assign
(paren
r_struct
id|sockaddr_in
op_star
)paren
op_amp
id|data.gd_addr
suffix:semicolon
id|exp_readlock
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|clp
op_assign
id|auth_unix_lookup
c_func
(paren
id|sin-&gt;sin_addr
)paren
)paren
)paren
id|err
op_assign
op_minus
id|EPERM
suffix:semicolon
r_else
(brace
id|err
op_assign
id|exp_rootfh
c_func
(paren
id|clp
comma
id|data.gd_path
comma
op_amp
id|fh
comma
id|NFS_FHSIZE
)paren
suffix:semicolon
id|auth_domain_put
c_func
(paren
id|clp
)paren
suffix:semicolon
)brace
id|exp_readunlock
c_func
(paren
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|file-&gt;f_dentry-&gt;d_inode-&gt;i_sem
)paren
suffix:semicolon
r_if
c_cond
(paren
id|file-&gt;private_data
)paren
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|err
op_logical_and
id|fh.fh_size
OG
id|NFS_FHSIZE
)paren
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
id|kfree
c_func
(paren
id|res
)paren
suffix:semicolon
r_else
(brace
id|memset
c_func
(paren
id|res
comma
l_int|0
comma
id|NFS_FHSIZE
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|res
comma
op_amp
id|fh.fh_base
comma
id|fh.fh_size
)paren
suffix:semicolon
id|file-&gt;f_dentry-&gt;d_inode-&gt;i_size
op_assign
id|NFS_FHSIZE
suffix:semicolon
id|file-&gt;private_data
op_assign
id|res
suffix:semicolon
id|err
op_assign
r_sizeof
(paren
id|data
)paren
suffix:semicolon
)brace
id|up
c_func
(paren
op_amp
id|file-&gt;f_dentry-&gt;d_inode-&gt;i_sem
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/*----------------------------------------------------------------------------*/
multiline_comment|/*&n; *&t;populating the filesystem.&n; */
DECL|variable|s_ops
r_static
r_struct
id|super_operations
id|s_ops
op_assign
(brace
dot
id|statfs
op_assign
id|simple_statfs
comma
)brace
suffix:semicolon
DECL|function|nfsd_fill_super
r_static
r_int
id|nfsd_fill_super
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_void
op_star
id|data
comma
r_int
id|silent
)paren
(brace
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_struct
id|dentry
op_star
id|root
suffix:semicolon
r_struct
id|dentry
op_star
id|dentry
suffix:semicolon
r_int
id|i
suffix:semicolon
id|sb-&gt;s_blocksize
op_assign
id|PAGE_CACHE_SIZE
suffix:semicolon
id|sb-&gt;s_blocksize_bits
op_assign
id|PAGE_CACHE_SHIFT
suffix:semicolon
id|sb-&gt;s_magic
op_assign
l_int|0x6e667364
suffix:semicolon
id|sb-&gt;s_op
op_assign
op_amp
id|s_ops
suffix:semicolon
id|inode
op_assign
id|new_inode
c_func
(paren
id|sb
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|inode-&gt;i_mode
op_assign
id|S_IFDIR
op_or
l_int|0755
suffix:semicolon
id|inode-&gt;i_uid
op_assign
id|inode-&gt;i_gid
op_assign
l_int|0
suffix:semicolon
id|inode-&gt;i_blksize
op_assign
id|PAGE_CACHE_SIZE
suffix:semicolon
id|inode-&gt;i_blocks
op_assign
l_int|0
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
id|simple_dir_inode_operations
suffix:semicolon
id|inode-&gt;i_fop
op_assign
op_amp
id|simple_dir_operations
suffix:semicolon
id|root
op_assign
id|d_alloc_root
c_func
(paren
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|root
)paren
(brace
id|iput
c_func
(paren
id|inode
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
id|NFSD_Svc
suffix:semicolon
id|i
op_le
id|NFSD_List
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|qstr
id|name
suffix:semicolon
id|name.name
op_assign
id|files
(braket
id|i
)braket
dot
id|name
suffix:semicolon
id|name.len
op_assign
id|strlen
c_func
(paren
id|name.name
)paren
suffix:semicolon
id|name.hash
op_assign
id|full_name_hash
c_func
(paren
id|name.name
comma
id|name.len
)paren
suffix:semicolon
id|dentry
op_assign
id|d_alloc
c_func
(paren
id|root
comma
op_amp
id|name
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dentry
)paren
r_goto
id|out
suffix:semicolon
id|inode
op_assign
id|new_inode
c_func
(paren
id|sb
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode
)paren
r_goto
id|out
suffix:semicolon
id|inode-&gt;i_mode
op_assign
id|S_IFREG
op_or
id|files
(braket
id|i
)braket
dot
id|mode
suffix:semicolon
id|inode-&gt;i_uid
op_assign
id|inode-&gt;i_gid
op_assign
l_int|0
suffix:semicolon
id|inode-&gt;i_blksize
op_assign
id|PAGE_CACHE_SIZE
suffix:semicolon
id|inode-&gt;i_blocks
op_assign
l_int|0
suffix:semicolon
id|inode-&gt;i_atime
op_assign
id|inode-&gt;i_mtime
op_assign
id|inode-&gt;i_ctime
op_assign
id|CURRENT_TIME
suffix:semicolon
id|inode-&gt;i_fop
op_assign
id|files
(braket
id|i
)braket
dot
id|ops
suffix:semicolon
id|inode-&gt;i_ino
op_assign
id|i
suffix:semicolon
id|d_add
c_func
(paren
id|dentry
comma
id|inode
)paren
suffix:semicolon
)brace
id|sb-&gt;s_root
op_assign
id|root
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|out
suffix:colon
id|d_genocide
c_func
(paren
id|root
)paren
suffix:semicolon
id|dput
c_func
(paren
id|root
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
DECL|function|nfsd_get_sb
r_static
r_struct
id|super_block
op_star
id|nfsd_get_sb
c_func
(paren
r_struct
id|file_system_type
op_star
id|fs_type
comma
r_int
id|flags
comma
r_char
op_star
id|dev_name
comma
r_void
op_star
id|data
)paren
(brace
r_return
id|get_sb_single
c_func
(paren
id|fs_type
comma
id|flags
comma
id|data
comma
id|nfsd_fill_super
)paren
suffix:semicolon
)brace
DECL|variable|nfsd_fs_type
r_static
r_struct
id|file_system_type
id|nfsd_fs_type
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|name
op_assign
l_string|&quot;nfsd&quot;
comma
dot
id|get_sb
op_assign
id|nfsd_get_sb
comma
dot
id|kill_sb
op_assign
id|kill_litter_super
comma
)brace
suffix:semicolon
DECL|function|init_nfsd
r_static
r_int
id|__init
id|init_nfsd
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Installing knfsd (copyright (C) 1996 okir@monad.swb.de).&bslash;n&quot;
)paren
suffix:semicolon
id|nfsd_stat_init
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Statistics */
id|nfsd_cache_init
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* RPC reply cache */
id|nfsd_export_init
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Exports table */
id|nfsd_lockd_init
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* lockd-&gt;nfsd callbacks */
r_if
c_cond
(paren
id|proc_mkdir
c_func
(paren
l_string|&quot;fs/nfs&quot;
comma
l_int|0
)paren
)paren
(brace
r_struct
id|proc_dir_entry
op_star
id|entry
suffix:semicolon
id|entry
op_assign
id|create_proc_entry
c_func
(paren
l_string|&quot;fs/nfs/exports&quot;
comma
l_int|0
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|entry
)paren
id|entry-&gt;proc_fops
op_assign
op_amp
id|exports_operations
suffix:semicolon
)brace
id|register_filesystem
c_func
(paren
op_amp
id|nfsd_fs_type
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|exit_nfsd
r_static
r_void
id|__exit
id|exit_nfsd
c_func
(paren
r_void
)paren
(brace
id|nfsd_export_shutdown
c_func
(paren
)paren
suffix:semicolon
id|nfsd_cache_shutdown
c_func
(paren
)paren
suffix:semicolon
id|remove_proc_entry
c_func
(paren
l_string|&quot;fs/nfs/exports&quot;
comma
l_int|NULL
)paren
suffix:semicolon
id|remove_proc_entry
c_func
(paren
l_string|&quot;fs/nfs&quot;
comma
l_int|NULL
)paren
suffix:semicolon
id|nfsd_stat_shutdown
c_func
(paren
)paren
suffix:semicolon
id|nfsd_lockd_shutdown
c_func
(paren
)paren
suffix:semicolon
id|unregister_filesystem
c_func
(paren
op_amp
id|nfsd_fs_type
)paren
suffix:semicolon
)brace
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Olaf Kirch &lt;okir@monad.swb.de&gt;&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|module_init
c_func
(paren
id|init_nfsd
)paren
id|module_exit
c_func
(paren
id|exit_nfsd
)paren
eof
