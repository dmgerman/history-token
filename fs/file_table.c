multiline_comment|/*&n; *  linux/fs/file_table.c&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; *  Copyright (C) 1997 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/file.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/security.h&gt;
macro_line|#include &lt;linux/eventpoll.h&gt;
macro_line|#include &lt;linux/mount.h&gt;
macro_line|#include &lt;linux/cdev.h&gt;
multiline_comment|/* sysctl tunables... */
DECL|variable|files_stat
r_struct
id|files_stat_struct
id|files_stat
op_assign
(brace
dot
id|max_files
op_assign
id|NR_FILE
)brace
suffix:semicolon
DECL|variable|files_stat
id|EXPORT_SYMBOL
c_func
(paren
id|files_stat
)paren
suffix:semicolon
multiline_comment|/* Needed by unix.o */
multiline_comment|/* public *and* exported. Not pretty! */
DECL|variable|files_lock
id|spinlock_t
id|__cacheline_aligned_in_smp
id|files_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|variable|files_lock
id|EXPORT_SYMBOL
c_func
(paren
id|files_lock
)paren
suffix:semicolon
DECL|variable|filp_count_lock
r_static
id|spinlock_t
id|filp_count_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
multiline_comment|/* slab constructors and destructors are called from arbitrary&n; * context and must be fully threaded - use a local spinlock&n; * to protect files_stat.nr_files&n; */
DECL|function|filp_ctor
r_void
id|filp_ctor
c_func
(paren
r_void
op_star
id|objp
comma
r_struct
id|kmem_cache_s
op_star
id|cachep
comma
r_int
r_int
id|cflags
)paren
(brace
r_if
c_cond
(paren
(paren
id|cflags
op_amp
(paren
id|SLAB_CTOR_VERIFY
op_or
id|SLAB_CTOR_CONSTRUCTOR
)paren
)paren
op_eq
id|SLAB_CTOR_CONSTRUCTOR
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|filp_count_lock
comma
id|flags
)paren
suffix:semicolon
id|files_stat.nr_files
op_increment
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|filp_count_lock
comma
id|flags
)paren
suffix:semicolon
)brace
)brace
DECL|function|filp_dtor
r_void
id|filp_dtor
c_func
(paren
r_void
op_star
id|objp
comma
r_struct
id|kmem_cache_s
op_star
id|cachep
comma
r_int
r_int
id|dflags
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|filp_count_lock
comma
id|flags
)paren
suffix:semicolon
id|files_stat.nr_files
op_decrement
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|filp_count_lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|file_free
r_static
r_inline
r_void
id|file_free
c_func
(paren
r_struct
id|file
op_star
id|f
)paren
(brace
id|kmem_cache_free
c_func
(paren
id|filp_cachep
comma
id|f
)paren
suffix:semicolon
)brace
multiline_comment|/* Find an unused file structure and return a pointer to it.&n; * Returns NULL, if there are no more free file structures or&n; * we run out of memory.&n; */
DECL|function|get_empty_filp
r_struct
id|file
op_star
id|get_empty_filp
c_func
(paren
r_void
)paren
(brace
r_static
r_int
id|old_max
suffix:semicolon
r_struct
id|file
op_star
id|f
suffix:semicolon
multiline_comment|/*&n;&t; * Privileged users can go above max_files&n;&t; */
r_if
c_cond
(paren
id|files_stat.nr_files
OL
id|files_stat.max_files
op_logical_or
id|capable
c_func
(paren
id|CAP_SYS_ADMIN
)paren
)paren
(brace
id|f
op_assign
id|kmem_cache_alloc
c_func
(paren
id|filp_cachep
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|f
)paren
(brace
id|memset
c_func
(paren
id|f
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|f
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|security_file_alloc
c_func
(paren
id|f
)paren
)paren
(brace
id|file_free
c_func
(paren
id|f
)paren
suffix:semicolon
r_goto
id|fail
suffix:semicolon
)brace
id|eventpoll_init_file
c_func
(paren
id|f
)paren
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|f-&gt;f_count
comma
l_int|1
)paren
suffix:semicolon
id|f-&gt;f_uid
op_assign
id|current-&gt;fsuid
suffix:semicolon
id|f-&gt;f_gid
op_assign
id|current-&gt;fsgid
suffix:semicolon
id|f-&gt;f_owner.lock
op_assign
id|RW_LOCK_UNLOCKED
suffix:semicolon
multiline_comment|/* f-&gt;f_version: 0 */
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|f-&gt;f_list
)paren
suffix:semicolon
r_return
id|f
suffix:semicolon
)brace
)brace
multiline_comment|/* Ran out of filps - report that */
r_if
c_cond
(paren
id|files_stat.max_files
op_ge
id|old_max
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;VFS: file-max limit %d reached&bslash;n&quot;
comma
id|files_stat.max_files
)paren
suffix:semicolon
id|old_max
op_assign
id|files_stat.max_files
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Big problems... */
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;VFS: filp allocation failed&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|fail
suffix:colon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|variable|get_empty_filp
id|EXPORT_SYMBOL
c_func
(paren
id|get_empty_filp
)paren
suffix:semicolon
multiline_comment|/*&n; * Clear and initialize a (private) struct file for the given dentry,&n; * allocate the security structure, and call the open function (if any).  &n; * The file should be released using close_private_file.&n; */
DECL|function|open_private_file
r_int
id|open_private_file
c_func
(paren
r_struct
id|file
op_star
id|filp
comma
r_struct
id|dentry
op_star
id|dentry
comma
r_int
id|flags
)paren
(brace
r_int
id|error
suffix:semicolon
id|memset
c_func
(paren
id|filp
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|filp
)paren
)paren
suffix:semicolon
id|eventpoll_init_file
c_func
(paren
id|filp
)paren
suffix:semicolon
id|filp-&gt;f_flags
op_assign
id|flags
suffix:semicolon
id|filp-&gt;f_mode
op_assign
(paren
id|flags
op_plus
l_int|1
)paren
op_amp
id|O_ACCMODE
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|filp-&gt;f_count
comma
l_int|1
)paren
suffix:semicolon
id|filp-&gt;f_dentry
op_assign
id|dentry
suffix:semicolon
id|filp-&gt;f_mapping
op_assign
id|dentry-&gt;d_inode-&gt;i_mapping
suffix:semicolon
id|filp-&gt;f_uid
op_assign
id|current-&gt;fsuid
suffix:semicolon
id|filp-&gt;f_gid
op_assign
id|current-&gt;fsgid
suffix:semicolon
id|filp-&gt;f_op
op_assign
id|dentry-&gt;d_inode-&gt;i_fop
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|filp-&gt;f_list
)paren
suffix:semicolon
id|error
op_assign
id|security_file_alloc
c_func
(paren
id|filp
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|error
)paren
r_if
c_cond
(paren
id|filp-&gt;f_op
op_logical_and
id|filp-&gt;f_op-&gt;open
)paren
(brace
id|error
op_assign
id|filp-&gt;f_op
op_member_access_from_pointer
id|open
c_func
(paren
id|dentry-&gt;d_inode
comma
id|filp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
id|security_file_free
c_func
(paren
id|filp
)paren
suffix:semicolon
)brace
r_return
id|error
suffix:semicolon
)brace
DECL|variable|open_private_file
id|EXPORT_SYMBOL
c_func
(paren
id|open_private_file
)paren
suffix:semicolon
multiline_comment|/*&n; * Release a private file by calling the release function (if any) and&n; * freeing the security structure.&n; */
DECL|function|close_private_file
r_void
id|close_private_file
c_func
(paren
r_struct
id|file
op_star
id|file
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|file-&gt;f_dentry-&gt;d_inode
suffix:semicolon
r_if
c_cond
(paren
id|file-&gt;f_op
op_logical_and
id|file-&gt;f_op-&gt;release
)paren
id|file-&gt;f_op
op_member_access_from_pointer
id|release
c_func
(paren
id|inode
comma
id|file
)paren
suffix:semicolon
id|security_file_free
c_func
(paren
id|file
)paren
suffix:semicolon
)brace
DECL|variable|close_private_file
id|EXPORT_SYMBOL
c_func
(paren
id|close_private_file
)paren
suffix:semicolon
DECL|function|fput
r_void
id|fastcall
id|fput
c_func
(paren
r_struct
id|file
op_star
id|file
)paren
(brace
r_if
c_cond
(paren
id|atomic_dec_and_test
c_func
(paren
op_amp
id|file-&gt;f_count
)paren
)paren
id|__fput
c_func
(paren
id|file
)paren
suffix:semicolon
)brace
DECL|variable|fput
id|EXPORT_SYMBOL
c_func
(paren
id|fput
)paren
suffix:semicolon
multiline_comment|/* __fput is called from task context when aio completion releases the last&n; * last use of a struct file *.  Do not use otherwise.&n; */
DECL|function|__fput
r_void
id|fastcall
id|__fput
c_func
(paren
r_struct
id|file
op_star
id|file
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
id|vfsmount
op_star
id|mnt
op_assign
id|file-&gt;f_vfsmnt
suffix:semicolon
r_struct
id|inode
op_star
id|inode
op_assign
id|dentry-&gt;d_inode
suffix:semicolon
multiline_comment|/*&n;&t; * The function eventpoll_release() should be the first called&n;&t; * in the file cleanup chain.&n;&t; */
id|eventpoll_release
c_func
(paren
id|file
)paren
suffix:semicolon
id|locks_remove_flock
c_func
(paren
id|file
)paren
suffix:semicolon
r_if
c_cond
(paren
id|file-&gt;f_op
op_logical_and
id|file-&gt;f_op-&gt;release
)paren
id|file-&gt;f_op
op_member_access_from_pointer
id|release
c_func
(paren
id|inode
comma
id|file
)paren
suffix:semicolon
id|security_file_free
c_func
(paren
id|file
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|inode-&gt;i_cdev
op_ne
l_int|NULL
)paren
)paren
id|cdev_put
c_func
(paren
id|inode-&gt;i_cdev
)paren
suffix:semicolon
id|fops_put
c_func
(paren
id|file-&gt;f_op
)paren
suffix:semicolon
r_if
c_cond
(paren
id|file-&gt;f_mode
op_amp
id|FMODE_WRITE
)paren
id|put_write_access
c_func
(paren
id|inode
)paren
suffix:semicolon
id|file_kill
c_func
(paren
id|file
)paren
suffix:semicolon
id|file-&gt;f_dentry
op_assign
l_int|NULL
suffix:semicolon
id|file-&gt;f_vfsmnt
op_assign
l_int|NULL
suffix:semicolon
id|file_free
c_func
(paren
id|file
)paren
suffix:semicolon
id|dput
c_func
(paren
id|dentry
)paren
suffix:semicolon
id|mntput
c_func
(paren
id|mnt
)paren
suffix:semicolon
)brace
DECL|function|fget
r_struct
id|file
id|fastcall
op_star
id|fget
c_func
(paren
r_int
r_int
id|fd
)paren
(brace
r_struct
id|file
op_star
id|file
suffix:semicolon
r_struct
id|files_struct
op_star
id|files
op_assign
id|current-&gt;files
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|files-&gt;file_lock
)paren
suffix:semicolon
id|file
op_assign
id|fcheck_files
c_func
(paren
id|files
comma
id|fd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|file
)paren
id|get_file
c_func
(paren
id|file
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|files-&gt;file_lock
)paren
suffix:semicolon
r_return
id|file
suffix:semicolon
)brace
DECL|variable|fget
id|EXPORT_SYMBOL
c_func
(paren
id|fget
)paren
suffix:semicolon
multiline_comment|/*&n; * Lightweight file lookup - no refcnt increment if fd table isn&squot;t shared. &n; * You can use this only if it is guranteed that the current task already &n; * holds a refcnt to that file. That check has to be done at fget() only&n; * and a flag is returned to be passed to the corresponding fput_light().&n; * There must not be a cloning between an fget_light/fput_light pair.&n; */
DECL|function|fget_light
r_struct
id|file
id|fastcall
op_star
id|fget_light
c_func
(paren
r_int
r_int
id|fd
comma
r_int
op_star
id|fput_needed
)paren
(brace
r_struct
id|file
op_star
id|file
suffix:semicolon
r_struct
id|files_struct
op_star
id|files
op_assign
id|current-&gt;files
suffix:semicolon
op_star
id|fput_needed
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|likely
c_func
(paren
(paren
id|atomic_read
c_func
(paren
op_amp
id|files-&gt;count
)paren
op_eq
l_int|1
)paren
)paren
)paren
(brace
id|file
op_assign
id|fcheck_files
c_func
(paren
id|files
comma
id|fd
)paren
suffix:semicolon
)brace
r_else
(brace
id|spin_lock
c_func
(paren
op_amp
id|files-&gt;file_lock
)paren
suffix:semicolon
id|file
op_assign
id|fcheck_files
c_func
(paren
id|files
comma
id|fd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|file
)paren
(brace
id|get_file
c_func
(paren
id|file
)paren
suffix:semicolon
op_star
id|fput_needed
op_assign
l_int|1
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|files-&gt;file_lock
)paren
suffix:semicolon
)brace
r_return
id|file
suffix:semicolon
)brace
DECL|function|put_filp
r_void
id|put_filp
c_func
(paren
r_struct
id|file
op_star
id|file
)paren
(brace
r_if
c_cond
(paren
id|atomic_dec_and_test
c_func
(paren
op_amp
id|file-&gt;f_count
)paren
)paren
(brace
id|security_file_free
c_func
(paren
id|file
)paren
suffix:semicolon
id|file_kill
c_func
(paren
id|file
)paren
suffix:semicolon
id|file_free
c_func
(paren
id|file
)paren
suffix:semicolon
)brace
)brace
DECL|variable|put_filp
id|EXPORT_SYMBOL
c_func
(paren
id|put_filp
)paren
suffix:semicolon
DECL|function|file_move
r_void
id|file_move
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_struct
id|list_head
op_star
id|list
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|list
)paren
r_return
suffix:semicolon
id|file_list_lock
c_func
(paren
)paren
suffix:semicolon
id|list_move
c_func
(paren
op_amp
id|file-&gt;f_list
comma
id|list
)paren
suffix:semicolon
id|file_list_unlock
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|file_kill
r_void
id|file_kill
c_func
(paren
r_struct
id|file
op_star
id|file
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|file-&gt;f_list
)paren
)paren
(brace
id|file_list_lock
c_func
(paren
)paren
suffix:semicolon
id|list_del_init
c_func
(paren
op_amp
id|file-&gt;f_list
)paren
suffix:semicolon
id|file_list_unlock
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
DECL|function|fs_may_remount_ro
r_int
id|fs_may_remount_ro
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
r_struct
id|list_head
op_star
id|p
suffix:semicolon
multiline_comment|/* Check that no files are currently opened for writing. */
id|file_list_lock
c_func
(paren
)paren
suffix:semicolon
id|list_for_each
c_func
(paren
id|p
comma
op_amp
id|sb-&gt;s_files
)paren
(brace
r_struct
id|file
op_star
id|file
op_assign
id|list_entry
c_func
(paren
id|p
comma
r_struct
id|file
comma
id|f_list
)paren
suffix:semicolon
r_struct
id|inode
op_star
id|inode
op_assign
id|file-&gt;f_dentry-&gt;d_inode
suffix:semicolon
multiline_comment|/* File with pending delete? */
r_if
c_cond
(paren
id|inode-&gt;i_nlink
op_eq
l_int|0
)paren
r_goto
id|too_bad
suffix:semicolon
multiline_comment|/* Writeable file? */
r_if
c_cond
(paren
id|S_ISREG
c_func
(paren
id|inode-&gt;i_mode
)paren
op_logical_and
(paren
id|file-&gt;f_mode
op_amp
id|FMODE_WRITE
)paren
)paren
r_goto
id|too_bad
suffix:semicolon
)brace
id|file_list_unlock
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
multiline_comment|/* Tis&squot; cool bro. */
id|too_bad
suffix:colon
id|file_list_unlock
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|files_init
r_void
id|__init
id|files_init
c_func
(paren
r_int
r_int
id|mempages
)paren
(brace
r_int
id|n
suffix:semicolon
multiline_comment|/* One file with associated inode and dcache is very roughly 1K. &n;&t; * Per default don&squot;t use more than 10% of our memory for files. &n;&t; */
id|n
op_assign
(paren
id|mempages
op_star
(paren
id|PAGE_SIZE
op_div
l_int|1024
)paren
)paren
op_div
l_int|10
suffix:semicolon
id|files_stat.max_files
op_assign
id|n
suffix:semicolon
r_if
c_cond
(paren
id|files_stat.max_files
OL
id|NR_FILE
)paren
id|files_stat.max_files
op_assign
id|NR_FILE
suffix:semicolon
)brace
eof
