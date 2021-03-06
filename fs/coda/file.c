multiline_comment|/*&n; * File operations for Coda.&n; * Original version: (C) 1996 Peter Braam &n; * Rewritten for Linux 2.1: (C) 1997 Carnegie Mellon University&n; *&n; * Carnegie Mellon encourages users of this code to contribute improvements&n; * to the Coda project. Contact Peter Braam &lt;coda@cs.cmu.edu&gt;.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/file.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
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
r_static
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
id|coda_file
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
id|ppos
)paren
(brace
r_struct
id|coda_file_info
op_star
id|cfi
suffix:semicolon
r_struct
id|file
op_star
id|host_file
suffix:semicolon
id|cfi
op_assign
id|CODA_FTOC
c_func
(paren
id|coda_file
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
op_logical_neg
id|cfi
op_logical_or
id|cfi-&gt;cfi_magic
op_ne
id|CODA_MAGIC
)paren
suffix:semicolon
id|host_file
op_assign
id|cfi-&gt;cfi_container
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|host_file-&gt;f_op
op_logical_or
op_logical_neg
id|host_file-&gt;f_op-&gt;read
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_return
id|host_file-&gt;f_op
op_member_access_from_pointer
id|read
c_func
(paren
id|host_file
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
DECL|function|coda_file_sendfile
id|coda_file_sendfile
c_func
(paren
r_struct
id|file
op_star
id|coda_file
comma
id|loff_t
op_star
id|ppos
comma
r_int
id|count
comma
id|read_actor_t
id|actor
comma
r_void
op_star
id|target
)paren
(brace
r_struct
id|coda_file_info
op_star
id|cfi
suffix:semicolon
r_struct
id|file
op_star
id|host_file
suffix:semicolon
id|cfi
op_assign
id|CODA_FTOC
c_func
(paren
id|coda_file
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
op_logical_neg
id|cfi
op_logical_or
id|cfi-&gt;cfi_magic
op_ne
id|CODA_MAGIC
)paren
suffix:semicolon
id|host_file
op_assign
id|cfi-&gt;cfi_container
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|host_file-&gt;f_op
op_logical_or
op_logical_neg
id|host_file-&gt;f_op-&gt;sendfile
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_return
id|host_file-&gt;f_op
op_member_access_from_pointer
id|sendfile
c_func
(paren
id|host_file
comma
id|ppos
comma
id|count
comma
id|actor
comma
id|target
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
id|coda_file
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
id|ppos
)paren
(brace
r_struct
id|inode
op_star
id|host_inode
comma
op_star
id|coda_inode
op_assign
id|coda_file-&gt;f_dentry-&gt;d_inode
suffix:semicolon
r_struct
id|coda_file_info
op_star
id|cfi
suffix:semicolon
r_struct
id|file
op_star
id|host_file
suffix:semicolon
id|ssize_t
id|ret
suffix:semicolon
id|cfi
op_assign
id|CODA_FTOC
c_func
(paren
id|coda_file
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
op_logical_neg
id|cfi
op_logical_or
id|cfi-&gt;cfi_magic
op_ne
id|CODA_MAGIC
)paren
suffix:semicolon
id|host_file
op_assign
id|cfi-&gt;cfi_container
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|host_file-&gt;f_op
op_logical_or
op_logical_neg
id|host_file-&gt;f_op-&gt;write
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|host_inode
op_assign
id|host_file-&gt;f_dentry-&gt;d_inode
suffix:semicolon
id|down
c_func
(paren
op_amp
id|coda_inode-&gt;i_sem
)paren
suffix:semicolon
id|ret
op_assign
id|host_file-&gt;f_op
op_member_access_from_pointer
id|write
c_func
(paren
id|host_file
comma
id|buf
comma
id|count
comma
id|ppos
)paren
suffix:semicolon
id|coda_inode-&gt;i_size
op_assign
id|host_inode-&gt;i_size
suffix:semicolon
id|coda_inode-&gt;i_blocks
op_assign
(paren
id|coda_inode-&gt;i_size
op_plus
l_int|511
)paren
op_rshift
l_int|9
suffix:semicolon
id|coda_inode-&gt;i_mtime
op_assign
id|coda_inode-&gt;i_ctime
op_assign
id|CURRENT_TIME_SEC
suffix:semicolon
id|up
c_func
(paren
op_amp
id|coda_inode-&gt;i_sem
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
id|coda_file
comma
r_struct
id|vm_area_struct
op_star
id|vma
)paren
(brace
r_struct
id|coda_file_info
op_star
id|cfi
suffix:semicolon
r_struct
id|coda_inode_info
op_star
id|cii
suffix:semicolon
r_struct
id|file
op_star
id|host_file
suffix:semicolon
r_struct
id|inode
op_star
id|coda_inode
comma
op_star
id|host_inode
suffix:semicolon
id|cfi
op_assign
id|CODA_FTOC
c_func
(paren
id|coda_file
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
op_logical_neg
id|cfi
op_logical_or
id|cfi-&gt;cfi_magic
op_ne
id|CODA_MAGIC
)paren
suffix:semicolon
id|host_file
op_assign
id|cfi-&gt;cfi_container
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|host_file-&gt;f_op
op_logical_or
op_logical_neg
id|host_file-&gt;f_op-&gt;mmap
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|coda_inode
op_assign
id|coda_file-&gt;f_dentry-&gt;d_inode
suffix:semicolon
id|host_inode
op_assign
id|host_file-&gt;f_dentry-&gt;d_inode
suffix:semicolon
id|coda_file-&gt;f_mapping
op_assign
id|host_file-&gt;f_mapping
suffix:semicolon
r_if
c_cond
(paren
id|coda_inode-&gt;i_mapping
op_eq
op_amp
id|coda_inode-&gt;i_data
)paren
id|coda_inode-&gt;i_mapping
op_assign
id|host_inode-&gt;i_mapping
suffix:semicolon
multiline_comment|/* only allow additional mmaps as long as userspace isn&squot;t changing&n;&t; * the container file on us! */
r_else
r_if
c_cond
(paren
id|coda_inode-&gt;i_mapping
op_ne
id|host_inode-&gt;i_mapping
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
multiline_comment|/* keep track of how often the coda_inode/host_file has been mmapped */
id|cii
op_assign
id|ITOC
c_func
(paren
id|coda_inode
)paren
suffix:semicolon
id|cii-&gt;c_mapcount
op_increment
suffix:semicolon
id|cfi-&gt;cfi_mapcount
op_increment
suffix:semicolon
r_return
id|host_file-&gt;f_op
op_member_access_from_pointer
id|mmap
c_func
(paren
id|host_file
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
id|coda_inode
comma
r_struct
id|file
op_star
id|coda_file
)paren
(brace
r_struct
id|file
op_star
id|host_file
op_assign
l_int|NULL
suffix:semicolon
r_int
id|error
suffix:semicolon
r_int
r_int
id|flags
op_assign
id|coda_file-&gt;f_flags
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
id|coda_file_info
op_star
id|cfi
suffix:semicolon
id|coda_vfs_stat.open
op_increment
suffix:semicolon
id|cfi
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|coda_file_info
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cfi
)paren
(brace
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|error
op_assign
id|venus_open
c_func
(paren
id|coda_inode-&gt;i_sb
comma
id|coda_i2f
c_func
(paren
id|coda_inode
)paren
comma
id|coda_flags
comma
op_amp
id|host_file
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
op_logical_or
op_logical_neg
id|host_file
)paren
(brace
id|kfree
c_func
(paren
id|cfi
)paren
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
id|host_file-&gt;f_flags
op_or_assign
id|coda_file-&gt;f_flags
op_amp
(paren
id|O_APPEND
op_or
id|O_SYNC
)paren
suffix:semicolon
id|cfi-&gt;cfi_magic
op_assign
id|CODA_MAGIC
suffix:semicolon
id|cfi-&gt;cfi_mapcount
op_assign
l_int|0
suffix:semicolon
id|cfi-&gt;cfi_container
op_assign
id|host_file
suffix:semicolon
id|BUG_ON
c_func
(paren
id|coda_file-&gt;private_data
op_ne
l_int|NULL
)paren
suffix:semicolon
id|coda_file-&gt;private_data
op_assign
id|cfi
suffix:semicolon
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
id|coda_file
)paren
(brace
r_int
r_int
id|flags
op_assign
id|coda_file-&gt;f_flags
op_amp
op_complement
id|O_EXCL
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
id|coda_file_info
op_star
id|cfi
suffix:semicolon
r_struct
id|inode
op_star
id|coda_inode
suffix:semicolon
r_int
id|err
op_assign
l_int|0
comma
id|fcnt
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|coda_vfs_stat.flush
op_increment
suffix:semicolon
multiline_comment|/* last close semantics */
id|fcnt
op_assign
id|file_count
c_func
(paren
id|coda_file
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fcnt
OG
l_int|1
)paren
r_goto
id|out
suffix:semicolon
multiline_comment|/* No need to make an upcall when we have not made any modifications&n;&t; * to the file */
r_if
c_cond
(paren
(paren
id|coda_file-&gt;f_flags
op_amp
id|O_ACCMODE
)paren
op_eq
id|O_RDONLY
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|use_coda_close
)paren
r_goto
id|out
suffix:semicolon
id|cfi
op_assign
id|CODA_FTOC
c_func
(paren
id|coda_file
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
op_logical_neg
id|cfi
op_logical_or
id|cfi-&gt;cfi_magic
op_ne
id|CODA_MAGIC
)paren
suffix:semicolon
id|coda_inode
op_assign
id|coda_file-&gt;f_dentry-&gt;d_inode
suffix:semicolon
id|err
op_assign
id|venus_store
c_func
(paren
id|coda_inode-&gt;i_sb
comma
id|coda_i2f
c_func
(paren
id|coda_inode
)paren
comma
id|coda_flags
comma
id|coda_file-&gt;f_uid
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
id|out
suffix:colon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
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
id|coda_inode
comma
r_struct
id|file
op_star
id|coda_file
)paren
(brace
r_int
r_int
id|flags
op_assign
(paren
id|coda_file-&gt;f_flags
)paren
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
id|coda_file_info
op_star
id|cfi
suffix:semicolon
r_struct
id|coda_inode_info
op_star
id|cii
suffix:semicolon
r_struct
id|inode
op_star
id|host_inode
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
id|coda_inode-&gt;i_sb
comma
id|coda_i2f
c_func
(paren
id|coda_inode
)paren
comma
id|coda_flags
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
id|cfi
op_assign
id|CODA_FTOC
c_func
(paren
id|coda_file
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
op_logical_neg
id|cfi
op_logical_or
id|cfi-&gt;cfi_magic
op_ne
id|CODA_MAGIC
)paren
suffix:semicolon
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
id|coda_inode-&gt;i_sb
comma
id|coda_i2f
c_func
(paren
id|coda_inode
)paren
comma
id|coda_flags
comma
id|coda_file-&gt;f_uid
)paren
suffix:semicolon
id|host_inode
op_assign
id|cfi-&gt;cfi_container-&gt;f_dentry-&gt;d_inode
suffix:semicolon
id|cii
op_assign
id|ITOC
c_func
(paren
id|coda_inode
)paren
suffix:semicolon
multiline_comment|/* did we mmap this file? */
r_if
c_cond
(paren
id|coda_inode-&gt;i_mapping
op_eq
op_amp
id|host_inode-&gt;i_data
)paren
(brace
id|cii-&gt;c_mapcount
op_sub_assign
id|cfi-&gt;cfi_mapcount
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cii-&gt;c_mapcount
)paren
id|coda_inode-&gt;i_mapping
op_assign
op_amp
id|coda_inode-&gt;i_data
suffix:semicolon
)brace
id|fput
c_func
(paren
id|cfi-&gt;cfi_container
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|coda_file-&gt;private_data
)paren
suffix:semicolon
id|coda_file-&gt;private_data
op_assign
l_int|NULL
suffix:semicolon
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
id|coda_file
comma
r_struct
id|dentry
op_star
id|coda_dentry
comma
r_int
id|datasync
)paren
(brace
r_struct
id|file
op_star
id|host_file
suffix:semicolon
r_struct
id|dentry
op_star
id|host_dentry
suffix:semicolon
r_struct
id|inode
op_star
id|host_inode
comma
op_star
id|coda_inode
op_assign
id|coda_dentry-&gt;d_inode
suffix:semicolon
r_struct
id|coda_file_info
op_star
id|cfi
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
id|coda_inode-&gt;i_mode
)paren
op_logical_or
id|S_ISDIR
c_func
(paren
id|coda_inode-&gt;i_mode
)paren
op_logical_or
id|S_ISLNK
c_func
(paren
id|coda_inode-&gt;i_mode
)paren
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|cfi
op_assign
id|CODA_FTOC
c_func
(paren
id|coda_file
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
op_logical_neg
id|cfi
op_logical_or
id|cfi-&gt;cfi_magic
op_ne
id|CODA_MAGIC
)paren
suffix:semicolon
id|host_file
op_assign
id|cfi-&gt;cfi_container
suffix:semicolon
id|coda_vfs_stat.fsync
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|host_file-&gt;f_op
op_logical_and
id|host_file-&gt;f_op-&gt;fsync
)paren
(brace
id|host_dentry
op_assign
id|host_file-&gt;f_dentry
suffix:semicolon
id|host_inode
op_assign
id|host_dentry-&gt;d_inode
suffix:semicolon
id|down
c_func
(paren
op_amp
id|host_inode-&gt;i_sem
)paren
suffix:semicolon
id|err
op_assign
id|host_file-&gt;f_op
op_member_access_from_pointer
id|fsync
c_func
(paren
id|host_file
comma
id|host_dentry
comma
id|datasync
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|host_inode-&gt;i_sem
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
id|coda_inode-&gt;i_sb
comma
id|coda_i2f
c_func
(paren
id|coda_inode
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
dot
id|llseek
op_assign
id|generic_file_llseek
comma
dot
id|read
op_assign
id|coda_file_read
comma
dot
id|write
op_assign
id|coda_file_write
comma
dot
id|mmap
op_assign
id|coda_file_mmap
comma
dot
id|open
op_assign
id|coda_open
comma
dot
id|flush
op_assign
id|coda_flush
comma
dot
id|release
op_assign
id|coda_release
comma
dot
id|fsync
op_assign
id|coda_fsync
comma
dot
id|sendfile
op_assign
id|coda_file_sendfile
comma
)brace
suffix:semicolon
eof
