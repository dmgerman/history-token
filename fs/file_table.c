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
multiline_comment|/* sysctl tunables... */
DECL|variable|files_stat
r_struct
id|files_stat_struct
id|files_stat
op_assign
(brace
l_int|0
comma
l_int|0
comma
id|NR_FILE
)brace
suffix:semicolon
multiline_comment|/* Here the new files go */
r_static
id|LIST_HEAD
c_func
(paren
id|anon_list
)paren
suffix:semicolon
multiline_comment|/* And here the free ones sit */
r_static
id|LIST_HEAD
c_func
(paren
id|free_list
)paren
suffix:semicolon
multiline_comment|/* public *and* exported. Not pretty! */
DECL|variable|files_lock
id|spinlock_t
id|files_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
multiline_comment|/* Find an unused file structure and return a pointer to it.&n; * Returns NULL, if there are no more free file structures or&n; * we run out of memory.&n; *&n; * SMP-safe.&n; */
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
op_assign
l_int|0
suffix:semicolon
r_struct
id|file
op_star
id|f
suffix:semicolon
id|file_list_lock
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|files_stat.nr_free_files
OG
id|NR_RESERVED_FILES
)paren
(brace
id|used_one
suffix:colon
id|f
op_assign
id|list_entry
c_func
(paren
id|free_list.next
comma
r_struct
id|file
comma
id|f_list
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|f-&gt;f_list
)paren
suffix:semicolon
id|files_stat.nr_free_files
op_decrement
suffix:semicolon
id|new_one
suffix:colon
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
id|list_add
c_func
(paren
op_amp
id|f-&gt;f_list
comma
op_amp
id|free_list
)paren
suffix:semicolon
id|files_stat.nr_free_files
op_increment
suffix:semicolon
id|file_list_unlock
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|NULL
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
id|f-&gt;f_version
op_assign
l_int|0
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
id|list_add
c_func
(paren
op_amp
id|f-&gt;f_list
comma
op_amp
id|anon_list
)paren
suffix:semicolon
id|file_list_unlock
c_func
(paren
)paren
suffix:semicolon
r_return
id|f
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Use a reserved one if we&squot;re the superuser&n;&t; */
r_if
c_cond
(paren
id|files_stat.nr_free_files
op_logical_and
op_logical_neg
id|current-&gt;euid
)paren
r_goto
id|used_one
suffix:semicolon
multiline_comment|/*&n;&t; * Allocate a new one if we&squot;re below the limit.&n;&t; */
r_if
c_cond
(paren
id|files_stat.nr_files
OL
id|files_stat.max_files
)paren
(brace
id|file_list_unlock
c_func
(paren
)paren
suffix:semicolon
id|f
op_assign
id|kmem_cache_alloc
c_func
(paren
id|filp_cachep
comma
id|SLAB_KERNEL
)paren
suffix:semicolon
id|file_list_lock
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|f
)paren
(brace
id|files_stat.nr_files
op_increment
suffix:semicolon
r_goto
id|new_one
suffix:semicolon
)brace
multiline_comment|/* Big problems... */
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;VFS: filp allocation failed&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|files_stat.max_files
OG
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
id|file_list_unlock
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n; * Clear and initialize a (private) struct file for the given dentry,&n; * and call the open function (if any).  The caller must verify that&n; * inode-&gt;i_fop is not NULL.&n; */
DECL|function|init_private_file
r_int
id|init_private_file
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
id|mode
)paren
(brace
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
id|filp-&gt;f_mode
op_assign
id|mode
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
r_if
c_cond
(paren
id|filp-&gt;f_op-&gt;open
)paren
r_return
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
r_else
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|fput
r_void
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
multiline_comment|/* __fput is called from task context when aio completion releases the last&n; * last use of a struct file *.  Do not use otherwise.&n; */
DECL|function|__fput
r_void
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
id|file_list_lock
c_func
(paren
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
id|list_del
c_func
(paren
op_amp
id|file-&gt;f_list
)paren
suffix:semicolon
id|list_add
c_func
(paren
op_amp
id|file-&gt;f_list
comma
op_amp
id|free_list
)paren
suffix:semicolon
id|files_stat.nr_free_files
op_increment
suffix:semicolon
id|file_list_unlock
c_func
(paren
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
id|read_lock
c_func
(paren
op_amp
id|files-&gt;file_lock
)paren
suffix:semicolon
id|file
op_assign
id|fcheck
c_func
(paren
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
id|read_unlock
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
multiline_comment|/* Here. put_filp() is SMP-safe now. */
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
id|file_list_lock
c_func
(paren
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|file-&gt;f_list
)paren
suffix:semicolon
id|list_add
c_func
(paren
op_amp
id|file-&gt;f_list
comma
op_amp
id|free_list
)paren
suffix:semicolon
id|files_stat.nr_free_files
op_increment
suffix:semicolon
id|file_list_unlock
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
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
id|list_del
c_func
(paren
op_amp
id|file-&gt;f_list
)paren
suffix:semicolon
id|list_add
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
multiline_comment|/* Writable file? */
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
