multiline_comment|/*&n; * File operations for Coda.&n; * Original version: (C) 1996 Peter Braam &n; * Rewritten for Linux 2.1: (C) 1997 Carnegie Mellon University&n; *&n; * Carnegie Mellon encourages users of this code to contribute improvements&n; * to the Coda project. Contact Peter Braam &lt;coda@cs.cmu.edu&gt;.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/file.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/locks.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;linux/coda.h&gt;
macro_line|#include &lt;linux/coda_linux.h&gt;
macro_line|#include &lt;linux/coda_fs_i.h&gt;
macro_line|#include &lt;linux/coda_psdev.h&gt;
macro_line|#include &lt;linux/coda_proc.h&gt;
multiline_comment|/* if CODA_STORE fails with EOPNOTSUPP, venus clearly doesn&squot;t support&n; * CODA_STORE/CODA_RELEASE and we fall back on using the CODA_CLOSE upcall */
DECL|variable|use_coda_close
r_int
id|use_coda_close
suffix:semicolon
r_static
id|ssize_t
DECL|function|coda_file_read
id|coda_file_read
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
id|inode
op_star
id|inode
op_assign
id|file-&gt;f_dentry-&gt;d_inode
suffix:semicolon
r_struct
id|coda_inode_info
op_star
id|cii
op_assign
id|ITOC
c_func
(paren
id|inode
)paren
suffix:semicolon
r_struct
id|file
op_star
id|cfile
suffix:semicolon
id|cfile
op_assign
id|cii-&gt;c_container
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cfile
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cfile-&gt;f_op
op_logical_or
op_logical_neg
id|cfile-&gt;f_op-&gt;read
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_return
id|cfile-&gt;f_op
op_member_access_from_pointer
id|read
c_func
(paren
id|cfile
comma
id|buf
comma
id|count
comma
id|ppos
)paren
suffix:semicolon
)brace
r_static
id|ssize_t
DECL|function|coda_file_write
id|coda_file_write
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
id|inode
op_star
id|cinode
comma
op_star
id|inode
op_assign
id|file-&gt;f_dentry-&gt;d_inode
suffix:semicolon
r_struct
id|coda_inode_info
op_star
id|cii
op_assign
id|ITOC
c_func
(paren
id|inode
)paren
suffix:semicolon
r_struct
id|file
op_star
id|cfile
suffix:semicolon
id|ssize_t
id|ret
suffix:semicolon
r_int
id|flags
suffix:semicolon
id|cfile
op_assign
id|cii-&gt;c_container
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cfile
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cfile-&gt;f_op
op_logical_or
op_logical_neg
id|cfile-&gt;f_op-&gt;write
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|cinode
op_assign
id|cfile-&gt;f_dentry-&gt;d_inode
suffix:semicolon
id|down
c_func
(paren
op_amp
id|inode-&gt;i_sem
)paren
suffix:semicolon
id|flags
op_assign
id|cfile-&gt;f_flags
suffix:semicolon
id|cfile-&gt;f_flags
op_or_assign
id|file-&gt;f_flags
op_amp
(paren
id|O_APPEND
op_or
id|O_SYNC
)paren
suffix:semicolon
id|ret
op_assign
id|cfile-&gt;f_op
op_member_access_from_pointer
id|write
c_func
(paren
id|cfile
comma
id|buf
comma
id|count
comma
id|ppos
)paren
suffix:semicolon
id|cfile-&gt;f_flags
op_assign
id|flags
suffix:semicolon
id|inode-&gt;i_size
op_assign
id|cinode-&gt;i_size
suffix:semicolon
id|inode-&gt;i_mtime
op_assign
id|inode-&gt;i_ctime
op_assign
id|CURRENT_TIME
suffix:semicolon
id|up
c_func
(paren
op_amp
id|inode-&gt;i_sem
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
r_static
r_int
DECL|function|coda_file_mmap
id|coda_file_mmap
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_struct
id|vm_area_struct
op_star
id|vma
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|file-&gt;f_dentry-&gt;d_inode
suffix:semicolon
r_struct
id|coda_inode_info
op_star
id|cii
op_assign
id|ITOC
c_func
(paren
id|inode
)paren
suffix:semicolon
r_struct
id|file
op_star
id|cfile
suffix:semicolon
id|cfile
op_assign
id|cii-&gt;c_container
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cfile
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cfile-&gt;f_op
op_logical_or
op_logical_neg
id|cfile-&gt;f_op-&gt;mmap
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_return
id|cfile-&gt;f_op
op_member_access_from_pointer
id|mmap
c_func
(paren
id|cfile
comma
id|vma
)paren
suffix:semicolon
)brace
DECL|function|coda_open
r_int
id|coda_open
c_func
(paren
r_struct
id|inode
op_star
id|i
comma
r_struct
id|file
op_star
id|f
)paren
(brace
r_struct
id|file
op_star
id|fh
op_assign
l_int|NULL
suffix:semicolon
r_int
id|error
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|flags
op_assign
id|f-&gt;f_flags
op_amp
(paren
op_complement
id|O_EXCL
)paren
suffix:semicolon
r_int
r_int
id|coda_flags
op_assign
id|coda_flags_to_cflags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_struct
id|coda_cred
op_star
id|cred
suffix:semicolon
r_struct
id|coda_inode_info
op_star
id|cii
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|coda_vfs_stat.open
op_increment
suffix:semicolon
id|error
op_assign
id|venus_open
c_func
(paren
id|i-&gt;i_sb
comma
id|coda_i2f
c_func
(paren
id|i
)paren
comma
id|coda_flags
comma
op_amp
id|fh
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
op_logical_or
op_logical_neg
id|fh
)paren
(brace
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
multiline_comment|/* coda_upcall returns filehandle of container file object */
id|cii
op_assign
id|ITOC
c_func
(paren
id|i
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cii-&gt;c_container
)paren
id|fput
c_func
(paren
id|cii-&gt;c_container
)paren
suffix:semicolon
id|cii-&gt;c_contcount
op_increment
suffix:semicolon
id|cii-&gt;c_container
op_assign
id|fh
suffix:semicolon
id|i-&gt;i_mapping
op_assign
op_amp
id|cii-&gt;c_container-&gt;f_dentry-&gt;d_inode-&gt;i_data
suffix:semicolon
id|cred
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|coda_cred
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
multiline_comment|/* If the allocation failed, we&squot;ll just muddle on. This actually works&n;&t; * fine for normal cases. (i.e. when open credentials are the same as&n;&t; * close credentials) */
r_if
c_cond
(paren
id|cred
)paren
(brace
id|coda_load_creds
c_func
(paren
id|cred
)paren
suffix:semicolon
id|f-&gt;private_data
op_assign
id|cred
suffix:semicolon
)brace
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|coda_flush
r_int
id|coda_flush
c_func
(paren
r_struct
id|file
op_star
id|file
)paren
(brace
r_int
r_int
id|flags
op_assign
(paren
id|file-&gt;f_flags
)paren
op_amp
(paren
op_complement
id|O_EXCL
)paren
suffix:semicolon
r_int
r_int
id|cflags
suffix:semicolon
r_struct
id|coda_inode_info
op_star
id|cii
suffix:semicolon
r_struct
id|file
op_star
id|cfile
suffix:semicolon
r_struct
id|inode
op_star
id|cinode
comma
op_star
id|inode
suffix:semicolon
r_int
id|err
op_assign
l_int|0
comma
id|fcnt
suffix:semicolon
id|coda_vfs_stat.flush
op_increment
suffix:semicolon
multiline_comment|/* No need to make an upcall when we have not made any modifications&n;&t; * to the file */
r_if
c_cond
(paren
(paren
id|file-&gt;f_flags
op_amp
id|O_ACCMODE
)paren
op_eq
id|O_RDONLY
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|use_coda_close
)paren
r_return
l_int|0
suffix:semicolon
id|fcnt
op_assign
id|file_count
c_func
(paren
id|file
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fcnt
OG
l_int|1
)paren
r_return
l_int|0
suffix:semicolon
id|cflags
op_assign
id|coda_flags_to_cflags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|inode
op_assign
id|file-&gt;f_dentry-&gt;d_inode
suffix:semicolon
id|cii
op_assign
id|ITOC
c_func
(paren
id|inode
)paren
suffix:semicolon
id|cfile
op_assign
id|cii-&gt;c_container
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cfile
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|cinode
op_assign
id|cfile-&gt;f_dentry-&gt;d_inode
suffix:semicolon
id|err
op_assign
id|venus_store
c_func
(paren
id|inode-&gt;i_sb
comma
id|coda_i2f
c_func
(paren
id|inode
)paren
comma
id|cflags
comma
(paren
r_struct
id|coda_cred
op_star
)paren
id|file-&gt;private_data
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
op_eq
op_minus
id|EOPNOTSUPP
)paren
(brace
id|use_coda_close
op_assign
l_int|1
suffix:semicolon
id|err
op_assign
l_int|0
suffix:semicolon
)brace
r_return
id|err
suffix:semicolon
)brace
DECL|function|coda_release
r_int
id|coda_release
c_func
(paren
r_struct
id|inode
op_star
id|i
comma
r_struct
id|file
op_star
id|f
)paren
(brace
r_int
r_int
id|flags
op_assign
(paren
id|f-&gt;f_flags
)paren
op_amp
(paren
op_complement
id|O_EXCL
)paren
suffix:semicolon
r_int
r_int
id|cflags
op_assign
id|coda_flags_to_cflags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_struct
id|coda_inode_info
op_star
id|cii
suffix:semicolon
r_struct
id|file
op_star
id|cfile
suffix:semicolon
r_int
id|err
op_assign
l_int|0
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|coda_vfs_stat.release
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|use_coda_close
)paren
(brace
id|err
op_assign
id|venus_release
c_func
(paren
id|i-&gt;i_sb
comma
id|coda_i2f
c_func
(paren
id|i
)paren
comma
id|cflags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
op_eq
op_minus
id|EOPNOTSUPP
)paren
(brace
id|use_coda_close
op_assign
l_int|1
suffix:semicolon
id|err
op_assign
l_int|0
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|use_coda_close
)paren
id|err
op_assign
id|venus_close
c_func
(paren
id|i-&gt;i_sb
comma
id|coda_i2f
c_func
(paren
id|i
)paren
comma
id|cflags
comma
(paren
r_struct
id|coda_cred
op_star
)paren
id|f-&gt;private_data
)paren
suffix:semicolon
id|cii
op_assign
id|ITOC
c_func
(paren
id|i
)paren
suffix:semicolon
id|cfile
op_assign
id|cii-&gt;c_container
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cfile
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_decrement
id|cii-&gt;c_contcount
)paren
(brace
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
id|i-&gt;i_mapping
op_assign
op_amp
id|i-&gt;i_data
suffix:semicolon
id|fput
c_func
(paren
id|cfile
)paren
suffix:semicolon
id|cii-&gt;c_container
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|f-&gt;private_data
)paren
(brace
id|kfree
c_func
(paren
id|f-&gt;private_data
)paren
suffix:semicolon
id|f-&gt;private_data
op_assign
l_int|NULL
suffix:semicolon
)brace
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|coda_fsync
r_int
id|coda_fsync
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
r_struct
id|file
op_star
id|cfile
suffix:semicolon
r_struct
id|dentry
op_star
id|cdentry
suffix:semicolon
r_struct
id|inode
op_star
id|cinode
comma
op_star
id|inode
op_assign
id|dentry-&gt;d_inode
suffix:semicolon
r_struct
id|coda_inode_info
op_star
id|cii
op_assign
id|ITOC
c_func
(paren
id|inode
)paren
suffix:semicolon
r_int
id|err
op_assign
l_int|0
suffix:semicolon
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
r_return
op_minus
id|EINVAL
suffix:semicolon
id|cfile
op_assign
id|cii-&gt;c_container
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cfile
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|coda_vfs_stat.fsync
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|cfile-&gt;f_op
op_logical_and
id|cfile-&gt;f_op-&gt;fsync
)paren
(brace
id|cdentry
op_assign
id|cfile-&gt;f_dentry
suffix:semicolon
id|cinode
op_assign
id|cdentry-&gt;d_inode
suffix:semicolon
id|down
c_func
(paren
op_amp
id|cinode-&gt;i_sem
)paren
suffix:semicolon
id|err
op_assign
id|cfile-&gt;f_op
op_member_access_from_pointer
id|fsync
c_func
(paren
id|cfile
comma
id|cdentry
comma
id|datasync
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|cinode-&gt;i_sem
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|err
op_logical_and
op_logical_neg
id|datasync
)paren
(brace
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|err
op_assign
id|venus_fsync
c_func
(paren
id|inode-&gt;i_sb
comma
id|coda_i2f
c_func
(paren
id|inode
)paren
)paren
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
)brace
r_return
id|err
suffix:semicolon
)brace
DECL|variable|coda_file_operations
r_struct
id|file_operations
id|coda_file_operations
op_assign
(brace
id|llseek
suffix:colon
id|generic_file_llseek
comma
id|read
suffix:colon
id|coda_file_read
comma
id|write
suffix:colon
id|coda_file_write
comma
id|mmap
suffix:colon
id|coda_file_mmap
comma
id|open
suffix:colon
id|coda_open
comma
id|flush
suffix:colon
id|coda_flush
comma
id|release
suffix:colon
id|coda_release
comma
id|fsync
suffix:colon
id|coda_fsync
comma
)brace
suffix:semicolon
eof
