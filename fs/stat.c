multiline_comment|/*&n; *  linux/fs/stat.c&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/file.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/highuid.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/namei.h&gt;
macro_line|#include &lt;linux/security.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
DECL|function|generic_fillattr
r_void
id|generic_fillattr
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|kstat
op_star
id|stat
)paren
(brace
id|stat-&gt;dev
op_assign
id|inode-&gt;i_dev
suffix:semicolon
id|stat-&gt;ino
op_assign
id|inode-&gt;i_ino
suffix:semicolon
id|stat-&gt;mode
op_assign
id|inode-&gt;i_mode
suffix:semicolon
id|stat-&gt;nlink
op_assign
id|inode-&gt;i_nlink
suffix:semicolon
id|stat-&gt;uid
op_assign
id|inode-&gt;i_uid
suffix:semicolon
id|stat-&gt;gid
op_assign
id|inode-&gt;i_gid
suffix:semicolon
id|stat-&gt;rdev
op_assign
id|kdev_t_to_nr
c_func
(paren
id|inode-&gt;i_rdev
)paren
suffix:semicolon
id|stat-&gt;atime
op_assign
id|inode-&gt;i_atime
suffix:semicolon
id|stat-&gt;mtime
op_assign
id|inode-&gt;i_mtime
suffix:semicolon
id|stat-&gt;ctime
op_assign
id|inode-&gt;i_ctime
suffix:semicolon
id|stat-&gt;ctime
op_assign
id|inode-&gt;i_ctime
suffix:semicolon
id|stat-&gt;size
op_assign
id|inode-&gt;i_size
suffix:semicolon
id|stat-&gt;blocks
op_assign
id|inode-&gt;i_blocks
suffix:semicolon
id|stat-&gt;blksize
op_assign
id|inode-&gt;i_blksize
suffix:semicolon
)brace
DECL|function|vfs_getattr
r_int
id|vfs_getattr
c_func
(paren
r_struct
id|vfsmount
op_star
id|mnt
comma
r_struct
id|dentry
op_star
id|dentry
comma
r_struct
id|kstat
op_star
id|stat
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|dentry-&gt;d_inode
suffix:semicolon
r_int
id|retval
suffix:semicolon
r_if
c_cond
(paren
(paren
id|retval
op_assign
id|security_inode_getattr
c_func
(paren
id|mnt
comma
id|dentry
)paren
)paren
)paren
r_return
id|retval
suffix:semicolon
r_if
c_cond
(paren
id|inode-&gt;i_op-&gt;getattr
)paren
r_return
id|inode-&gt;i_op
op_member_access_from_pointer
id|getattr
c_func
(paren
id|mnt
comma
id|dentry
comma
id|stat
)paren
suffix:semicolon
id|generic_fillattr
c_func
(paren
id|inode
comma
id|stat
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|stat-&gt;blksize
)paren
(brace
r_struct
id|super_block
op_star
id|s
op_assign
id|inode-&gt;i_sb
suffix:semicolon
r_int
id|blocks
suffix:semicolon
id|blocks
op_assign
(paren
id|stat-&gt;size
op_plus
id|s-&gt;s_blocksize
op_minus
l_int|1
)paren
op_rshift
id|s-&gt;s_blocksize_bits
suffix:semicolon
id|stat-&gt;blocks
op_assign
(paren
id|s-&gt;s_blocksize
op_div
l_int|512
)paren
op_star
id|blocks
suffix:semicolon
id|stat-&gt;blksize
op_assign
id|s-&gt;s_blocksize
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|vfs_stat
r_int
id|vfs_stat
c_func
(paren
r_char
op_star
id|name
comma
r_struct
id|kstat
op_star
id|stat
)paren
(brace
r_struct
id|nameidata
id|nd
suffix:semicolon
r_int
id|error
suffix:semicolon
id|error
op_assign
id|user_path_walk
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
op_logical_neg
id|error
)paren
(brace
id|error
op_assign
id|vfs_getattr
c_func
(paren
id|nd.mnt
comma
id|nd.dentry
comma
id|stat
)paren
suffix:semicolon
id|path_release
c_func
(paren
op_amp
id|nd
)paren
suffix:semicolon
)brace
r_return
id|error
suffix:semicolon
)brace
DECL|function|vfs_lstat
r_int
id|vfs_lstat
c_func
(paren
r_char
op_star
id|name
comma
r_struct
id|kstat
op_star
id|stat
)paren
(brace
r_struct
id|nameidata
id|nd
suffix:semicolon
r_int
id|error
suffix:semicolon
id|error
op_assign
id|user_path_walk_link
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
op_logical_neg
id|error
)paren
(brace
id|error
op_assign
id|vfs_getattr
c_func
(paren
id|nd.mnt
comma
id|nd.dentry
comma
id|stat
)paren
suffix:semicolon
id|path_release
c_func
(paren
op_amp
id|nd
)paren
suffix:semicolon
)brace
r_return
id|error
suffix:semicolon
)brace
DECL|function|vfs_fstat
r_int
id|vfs_fstat
c_func
(paren
r_int
r_int
id|fd
comma
r_struct
id|kstat
op_star
id|stat
)paren
(brace
r_struct
id|file
op_star
id|f
op_assign
id|fget
c_func
(paren
id|fd
)paren
suffix:semicolon
r_int
id|error
op_assign
op_minus
id|EBADF
suffix:semicolon
r_if
c_cond
(paren
id|f
)paren
(brace
id|error
op_assign
id|vfs_getattr
c_func
(paren
id|f-&gt;f_vfsmnt
comma
id|f-&gt;f_dentry
comma
id|stat
)paren
suffix:semicolon
id|fput
c_func
(paren
id|f
)paren
suffix:semicolon
)brace
r_return
id|error
suffix:semicolon
)brace
macro_line|#if !defined(__alpha__) &amp;&amp; !defined(__sparc__) &amp;&amp; !defined(__ia64__) &bslash;&n; &amp;&amp; !defined(CONFIG_ARCH_S390) &amp;&amp; !defined(__hppa__) &amp;&amp; !defined(__x86_64__) &bslash;&n; &amp;&amp; !defined(__arm__)
multiline_comment|/*&n; * For backward compatibility?  Maybe this should be moved&n; * into arch/i386 instead?&n; */
DECL|function|cp_old_stat
r_static
r_int
id|cp_old_stat
c_func
(paren
r_struct
id|kstat
op_star
id|stat
comma
r_struct
id|__old_kernel_stat
op_star
id|statbuf
)paren
(brace
r_static
r_int
id|warncount
op_assign
l_int|5
suffix:semicolon
r_struct
id|__old_kernel_stat
id|tmp
suffix:semicolon
r_if
c_cond
(paren
id|warncount
OG
l_int|0
)paren
(brace
id|warncount
op_decrement
suffix:semicolon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;VFS: Warning: %s using old stat() call. Recompile your binary.&bslash;n&quot;
comma
id|current-&gt;comm
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|warncount
OL
l_int|0
)paren
(brace
multiline_comment|/* it&squot;s laughable, but... */
id|warncount
op_assign
l_int|0
suffix:semicolon
)brace
id|tmp.st_dev
op_assign
id|stat-&gt;dev
suffix:semicolon
id|tmp.st_ino
op_assign
id|stat-&gt;ino
suffix:semicolon
id|tmp.st_mode
op_assign
id|stat-&gt;mode
suffix:semicolon
id|tmp.st_nlink
op_assign
id|stat-&gt;nlink
suffix:semicolon
id|SET_OLDSTAT_UID
c_func
(paren
id|tmp
comma
id|stat-&gt;uid
)paren
suffix:semicolon
id|SET_OLDSTAT_GID
c_func
(paren
id|tmp
comma
id|stat-&gt;gid
)paren
suffix:semicolon
id|tmp.st_rdev
op_assign
id|stat-&gt;rdev
suffix:semicolon
macro_line|#if BITS_PER_LONG == 32
r_if
c_cond
(paren
id|stat-&gt;size
OG
id|MAX_NON_LFS
)paren
r_return
op_minus
id|EOVERFLOW
suffix:semicolon
macro_line|#endif&t;
id|tmp.st_size
op_assign
id|stat-&gt;size
suffix:semicolon
id|tmp.st_atime
op_assign
id|stat-&gt;atime
suffix:semicolon
id|tmp.st_mtime
op_assign
id|stat-&gt;mtime
suffix:semicolon
id|tmp.st_ctime
op_assign
id|stat-&gt;ctime
suffix:semicolon
r_return
id|copy_to_user
c_func
(paren
id|statbuf
comma
op_amp
id|tmp
comma
r_sizeof
(paren
id|tmp
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
DECL|function|sys_stat
id|asmlinkage
r_int
id|sys_stat
c_func
(paren
r_char
op_star
id|filename
comma
r_struct
id|__old_kernel_stat
op_star
id|statbuf
)paren
(brace
r_struct
id|kstat
id|stat
suffix:semicolon
r_int
id|error
op_assign
id|vfs_stat
c_func
(paren
id|filename
comma
op_amp
id|stat
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|error
)paren
id|error
op_assign
id|cp_old_stat
c_func
(paren
op_amp
id|stat
comma
id|statbuf
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
DECL|function|sys_lstat
id|asmlinkage
r_int
id|sys_lstat
c_func
(paren
r_char
op_star
id|filename
comma
r_struct
id|__old_kernel_stat
op_star
id|statbuf
)paren
(brace
r_struct
id|kstat
id|stat
suffix:semicolon
r_int
id|error
op_assign
id|vfs_lstat
c_func
(paren
id|filename
comma
op_amp
id|stat
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|error
)paren
id|error
op_assign
id|cp_old_stat
c_func
(paren
op_amp
id|stat
comma
id|statbuf
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
DECL|function|sys_fstat
id|asmlinkage
r_int
id|sys_fstat
c_func
(paren
r_int
r_int
id|fd
comma
r_struct
id|__old_kernel_stat
op_star
id|statbuf
)paren
(brace
r_struct
id|kstat
id|stat
suffix:semicolon
r_int
id|error
op_assign
id|vfs_fstat
c_func
(paren
id|fd
comma
op_amp
id|stat
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|error
)paren
id|error
op_assign
id|cp_old_stat
c_func
(paren
op_amp
id|stat
comma
id|statbuf
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
macro_line|#endif
DECL|function|cp_new_stat
r_static
r_int
id|cp_new_stat
c_func
(paren
r_struct
id|kstat
op_star
id|stat
comma
r_struct
id|stat
op_star
id|statbuf
)paren
(brace
r_struct
id|stat
id|tmp
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|tmp
comma
l_int|0
comma
r_sizeof
(paren
id|tmp
)paren
)paren
suffix:semicolon
id|tmp.st_dev
op_assign
id|stat-&gt;dev
suffix:semicolon
id|tmp.st_ino
op_assign
id|stat-&gt;ino
suffix:semicolon
id|tmp.st_mode
op_assign
id|stat-&gt;mode
suffix:semicolon
id|tmp.st_nlink
op_assign
id|stat-&gt;nlink
suffix:semicolon
id|SET_STAT_UID
c_func
(paren
id|tmp
comma
id|stat-&gt;uid
)paren
suffix:semicolon
id|SET_STAT_GID
c_func
(paren
id|tmp
comma
id|stat-&gt;gid
)paren
suffix:semicolon
id|tmp.st_rdev
op_assign
id|stat-&gt;rdev
suffix:semicolon
macro_line|#if BITS_PER_LONG == 32
r_if
c_cond
(paren
id|stat-&gt;size
OG
id|MAX_NON_LFS
)paren
r_return
op_minus
id|EOVERFLOW
suffix:semicolon
macro_line|#endif&t;
id|tmp.st_size
op_assign
id|stat-&gt;size
suffix:semicolon
id|tmp.st_atime
op_assign
id|stat-&gt;atime
suffix:semicolon
id|tmp.st_mtime
op_assign
id|stat-&gt;mtime
suffix:semicolon
id|tmp.st_ctime
op_assign
id|stat-&gt;ctime
suffix:semicolon
id|tmp.st_blocks
op_assign
id|stat-&gt;blocks
suffix:semicolon
id|tmp.st_blksize
op_assign
id|stat-&gt;blksize
suffix:semicolon
r_return
id|copy_to_user
c_func
(paren
id|statbuf
comma
op_amp
id|tmp
comma
r_sizeof
(paren
id|tmp
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
DECL|function|sys_newstat
id|asmlinkage
r_int
id|sys_newstat
c_func
(paren
r_char
op_star
id|filename
comma
r_struct
id|stat
op_star
id|statbuf
)paren
(brace
r_struct
id|kstat
id|stat
suffix:semicolon
r_int
id|error
op_assign
id|vfs_stat
c_func
(paren
id|filename
comma
op_amp
id|stat
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|error
)paren
id|error
op_assign
id|cp_new_stat
c_func
(paren
op_amp
id|stat
comma
id|statbuf
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
DECL|function|sys_newlstat
id|asmlinkage
r_int
id|sys_newlstat
c_func
(paren
r_char
op_star
id|filename
comma
r_struct
id|stat
op_star
id|statbuf
)paren
(brace
r_struct
id|kstat
id|stat
suffix:semicolon
r_int
id|error
op_assign
id|vfs_lstat
c_func
(paren
id|filename
comma
op_amp
id|stat
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|error
)paren
id|error
op_assign
id|cp_new_stat
c_func
(paren
op_amp
id|stat
comma
id|statbuf
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
DECL|function|sys_newfstat
id|asmlinkage
r_int
id|sys_newfstat
c_func
(paren
r_int
r_int
id|fd
comma
r_struct
id|stat
op_star
id|statbuf
)paren
(brace
r_struct
id|kstat
id|stat
suffix:semicolon
r_int
id|error
op_assign
id|vfs_fstat
c_func
(paren
id|fd
comma
op_amp
id|stat
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|error
)paren
id|error
op_assign
id|cp_new_stat
c_func
(paren
op_amp
id|stat
comma
id|statbuf
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
DECL|function|sys_readlink
id|asmlinkage
r_int
id|sys_readlink
c_func
(paren
r_const
r_char
op_star
id|path
comma
r_char
op_star
id|buf
comma
r_int
id|bufsiz
)paren
(brace
r_struct
id|nameidata
id|nd
suffix:semicolon
r_int
id|error
suffix:semicolon
r_if
c_cond
(paren
id|bufsiz
op_le
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|error
op_assign
id|user_path_walk_link
c_func
(paren
id|path
comma
op_amp
id|nd
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|error
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|nd.dentry-&gt;d_inode
suffix:semicolon
id|error
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|inode-&gt;i_op
op_logical_and
id|inode-&gt;i_op-&gt;readlink
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|error
op_assign
id|security_inode_readlink
c_func
(paren
id|nd.dentry
)paren
)paren
)paren
(brace
id|UPDATE_ATIME
c_func
(paren
id|inode
)paren
suffix:semicolon
id|error
op_assign
id|inode-&gt;i_op
op_member_access_from_pointer
id|readlink
c_func
(paren
id|nd.dentry
comma
id|buf
comma
id|bufsiz
)paren
suffix:semicolon
)brace
)brace
id|path_release
c_func
(paren
op_amp
id|nd
)paren
suffix:semicolon
)brace
r_return
id|error
suffix:semicolon
)brace
multiline_comment|/* ---------- LFS-64 ----------- */
macro_line|#if !defined(__alpha__) &amp;&amp; !defined(__ia64__) &amp;&amp; !defined(__mips64) &amp;&amp; !defined(__x86_64__) &amp;&amp; !defined(CONFIG_ARCH_S390X)
DECL|function|cp_new_stat64
r_static
r_int
id|cp_new_stat64
c_func
(paren
r_struct
id|kstat
op_star
id|stat
comma
r_struct
id|stat64
op_star
id|statbuf
)paren
(brace
r_struct
id|stat64
id|tmp
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|tmp
comma
l_int|0
comma
r_sizeof
(paren
id|tmp
)paren
)paren
suffix:semicolon
id|tmp.st_dev
op_assign
id|stat-&gt;dev
suffix:semicolon
id|tmp.st_ino
op_assign
id|stat-&gt;ino
suffix:semicolon
macro_line|#ifdef STAT64_HAS_BROKEN_ST_INO
id|tmp.__st_ino
op_assign
id|stat-&gt;ino
suffix:semicolon
macro_line|#endif
id|tmp.st_mode
op_assign
id|stat-&gt;mode
suffix:semicolon
id|tmp.st_nlink
op_assign
id|stat-&gt;nlink
suffix:semicolon
id|tmp.st_uid
op_assign
id|stat-&gt;uid
suffix:semicolon
id|tmp.st_gid
op_assign
id|stat-&gt;gid
suffix:semicolon
id|tmp.st_rdev
op_assign
id|stat-&gt;rdev
suffix:semicolon
id|tmp.st_atime
op_assign
id|stat-&gt;atime
suffix:semicolon
id|tmp.st_mtime
op_assign
id|stat-&gt;mtime
suffix:semicolon
id|tmp.st_ctime
op_assign
id|stat-&gt;ctime
suffix:semicolon
id|tmp.st_size
op_assign
id|stat-&gt;size
suffix:semicolon
id|tmp.st_blocks
op_assign
id|stat-&gt;blocks
suffix:semicolon
id|tmp.st_blksize
op_assign
id|stat-&gt;blksize
suffix:semicolon
r_return
id|copy_to_user
c_func
(paren
id|statbuf
comma
op_amp
id|tmp
comma
r_sizeof
(paren
id|tmp
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
DECL|function|sys_stat64
id|asmlinkage
r_int
id|sys_stat64
c_func
(paren
r_char
op_star
id|filename
comma
r_struct
id|stat64
op_star
id|statbuf
comma
r_int
id|flags
)paren
(brace
r_struct
id|kstat
id|stat
suffix:semicolon
r_int
id|error
op_assign
id|vfs_stat
c_func
(paren
id|filename
comma
op_amp
id|stat
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|error
)paren
id|error
op_assign
id|cp_new_stat64
c_func
(paren
op_amp
id|stat
comma
id|statbuf
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
DECL|function|sys_lstat64
id|asmlinkage
r_int
id|sys_lstat64
c_func
(paren
r_char
op_star
id|filename
comma
r_struct
id|stat64
op_star
id|statbuf
comma
r_int
id|flags
)paren
(brace
r_struct
id|kstat
id|stat
suffix:semicolon
r_int
id|error
op_assign
id|vfs_lstat
c_func
(paren
id|filename
comma
op_amp
id|stat
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|error
)paren
id|error
op_assign
id|cp_new_stat64
c_func
(paren
op_amp
id|stat
comma
id|statbuf
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
DECL|function|sys_fstat64
id|asmlinkage
r_int
id|sys_fstat64
c_func
(paren
r_int
r_int
id|fd
comma
r_struct
id|stat64
op_star
id|statbuf
comma
r_int
id|flags
)paren
(brace
r_struct
id|kstat
id|stat
suffix:semicolon
r_int
id|error
op_assign
id|vfs_fstat
c_func
(paren
id|fd
comma
op_amp
id|stat
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|error
)paren
id|error
op_assign
id|cp_new_stat64
c_func
(paren
op_amp
id|stat
comma
id|statbuf
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
macro_line|#endif /* LFS-64 */
eof
