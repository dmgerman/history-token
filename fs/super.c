multiline_comment|/*&n; *  linux/fs/super.c&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; *&n; *  super.c contains code to handle: - mount structures&n; *                                   - super-block tables&n; *                                   - filesystem drivers list&n; *                                   - mount system call&n; *                                   - umount system call&n; *                                   - ustat system call&n; *&n; * GK 2/5/95  -  Changed to support mounting the root fs via NFS&n; *&n; *  Added kerneld support: Jacques Gelinas and Bjorn Ekwall&n; *  Added change_root: Werner Almesberger &amp; Hans Lermen, Feb &squot;96&n; *  Added options to /proc/mounts:&n; *    Torbj&#xfffd;rn Lindh (torbjorn.lindh@gopta.se), April 14, 1996.&n; *  Added devfs support: Richard Gooch &lt;rgooch@atnf.csiro.au&gt;, 13-JAN-1998&n; *  Heavily rewritten for &squot;one fs - one tree&squot; dcache architecture. AV, Mar 2000&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/devfs_fs_kernel.h&gt;
macro_line|#include &lt;linux/acct.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/quotaops.h&gt;
macro_line|#include &lt;linux/namei.h&gt;
macro_line|#include &lt;linux/buffer_head.h&gt;&t;&t;/* for fsync_super() */
macro_line|#include &lt;asm/uaccess.h&gt;
r_void
id|get_filesystem
c_func
(paren
r_struct
id|file_system_type
op_star
id|fs
)paren
suffix:semicolon
r_void
id|put_filesystem
c_func
(paren
r_struct
id|file_system_type
op_star
id|fs
)paren
suffix:semicolon
r_struct
id|file_system_type
op_star
id|get_fs_type
c_func
(paren
r_const
r_char
op_star
id|name
)paren
suffix:semicolon
DECL|variable|super_blocks
id|LIST_HEAD
c_func
(paren
id|super_blocks
)paren
suffix:semicolon
DECL|variable|sb_lock
id|spinlock_t
id|sb_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
multiline_comment|/**&n; *&t;alloc_super&t;-&t;create new superblock&n; *&n; *&t;Allocates and initializes a new &amp;struct super_block.  alloc_super()&n; *&t;returns a pointer new superblock or %NULL if allocation had failed.&n; */
DECL|function|alloc_super
r_static
r_struct
id|super_block
op_star
id|alloc_super
c_func
(paren
r_void
)paren
(brace
r_struct
id|super_block
op_star
id|s
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|super_block
)paren
comma
id|GFP_USER
)paren
suffix:semicolon
r_if
c_cond
(paren
id|s
)paren
(brace
id|memset
c_func
(paren
id|s
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|super_block
)paren
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|s-&gt;s_dirty
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|s-&gt;s_io
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|s-&gt;s_locked_inodes
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|s-&gt;s_files
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|s-&gt;s_instances
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|s-&gt;s_anon
)paren
suffix:semicolon
id|init_rwsem
c_func
(paren
op_amp
id|s-&gt;s_umount
)paren
suffix:semicolon
id|sema_init
c_func
(paren
op_amp
id|s-&gt;s_lock
comma
l_int|1
)paren
suffix:semicolon
id|down_write
c_func
(paren
op_amp
id|s-&gt;s_umount
)paren
suffix:semicolon
id|s-&gt;s_count
op_assign
id|S_BIAS
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|s-&gt;s_active
comma
l_int|1
)paren
suffix:semicolon
id|sema_init
c_func
(paren
op_amp
id|s-&gt;s_vfs_rename_sem
comma
l_int|1
)paren
suffix:semicolon
id|sema_init
c_func
(paren
op_amp
id|s-&gt;s_dquot.dqio_sem
comma
l_int|1
)paren
suffix:semicolon
id|sema_init
c_func
(paren
op_amp
id|s-&gt;s_dquot.dqoff_sem
comma
l_int|1
)paren
suffix:semicolon
id|s-&gt;s_maxbytes
op_assign
id|MAX_NON_LFS
suffix:semicolon
id|s-&gt;dq_op
op_assign
id|sb_dquot_ops
suffix:semicolon
id|s-&gt;s_qcop
op_assign
id|sb_quotactl_ops
suffix:semicolon
)brace
r_return
id|s
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;destroy_super&t;-&t;frees a superblock&n; *&t;@s: superblock to free&n; *&n; *&t;Frees a superblock.&n; */
DECL|function|destroy_super
r_static
r_inline
r_void
id|destroy_super
c_func
(paren
r_struct
id|super_block
op_star
id|s
)paren
(brace
id|kfree
c_func
(paren
id|s
)paren
suffix:semicolon
)brace
multiline_comment|/* Superblock refcounting  */
multiline_comment|/**&n; *&t;put_super&t;-&t;drop a temporary reference to superblock&n; *&t;@s: superblock in question&n; *&n; *&t;Drops a temporary reference, frees superblock if there&squot;s no&n; *&t;references left.&n; */
DECL|function|put_super
r_static
r_inline
r_void
id|put_super
c_func
(paren
r_struct
id|super_block
op_star
id|s
)paren
(brace
id|spin_lock
c_func
(paren
op_amp
id|sb_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_decrement
id|s-&gt;s_count
)paren
id|destroy_super
c_func
(paren
id|s
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|sb_lock
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;deactivate_super&t;-&t;drop an active reference to superblock&n; *&t;@s: superblock to deactivate&n; *&n; *&t;Drops an active reference to superblock, acquiring a temprory one if&n; *&t;there is no active references left.  In that case we lock superblock,&n; *&t;tell fs driver to shut it down and drop the temporary reference we&n; *&t;had just acquired.&n; */
DECL|function|deactivate_super
r_void
id|deactivate_super
c_func
(paren
r_struct
id|super_block
op_star
id|s
)paren
(brace
r_struct
id|file_system_type
op_star
id|fs
op_assign
id|s-&gt;s_type
suffix:semicolon
r_if
c_cond
(paren
id|atomic_dec_and_lock
c_func
(paren
op_amp
id|s-&gt;s_active
comma
op_amp
id|sb_lock
)paren
)paren
(brace
id|s-&gt;s_count
op_sub_assign
id|S_BIAS
op_minus
l_int|1
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|sb_lock
)paren
suffix:semicolon
id|down_write
c_func
(paren
op_amp
id|s-&gt;s_umount
)paren
suffix:semicolon
id|fs
op_member_access_from_pointer
id|kill_sb
c_func
(paren
id|s
)paren
suffix:semicolon
id|put_filesystem
c_func
(paren
id|fs
)paren
suffix:semicolon
id|put_super
c_func
(paren
id|s
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/**&n; *&t;grab_super&t;- acquire an active reference&n; *&t;@s&t;- reference we are trying to make active&n; *&n; *&t;Tries to acquire an active reference.  grab_super() is used when we&n; * &t;had just found a superblock in super_blocks or fs_type-&gt;fs_supers&n; *&t;and want to turn it into a full-blown active reference.  grab_super()&n; *&t;is called with sb_lock held and drops it.  Returns 1 in case of&n; *&t;success, 0 if we had failed (superblock contents was already dead or&n; *&t;dying when grab_super() had been called).&n; */
DECL|function|grab_super
r_static
r_int
id|grab_super
c_func
(paren
r_struct
id|super_block
op_star
id|s
)paren
(brace
id|s-&gt;s_count
op_increment
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|sb_lock
)paren
suffix:semicolon
id|down_write
c_func
(paren
op_amp
id|s-&gt;s_umount
)paren
suffix:semicolon
r_if
c_cond
(paren
id|s-&gt;s_root
)paren
(brace
id|spin_lock
c_func
(paren
op_amp
id|sb_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|s-&gt;s_count
OG
id|S_BIAS
)paren
(brace
id|atomic_inc
c_func
(paren
op_amp
id|s-&gt;s_active
)paren
suffix:semicolon
id|s-&gt;s_count
op_decrement
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|sb_lock
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|sb_lock
)paren
suffix:semicolon
)brace
id|up_write
c_func
(paren
op_amp
id|s-&gt;s_umount
)paren
suffix:semicolon
id|put_super
c_func
(paren
id|s
)paren
suffix:semicolon
id|yield
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;generic_shutdown_super&t;-&t;common helper for -&gt;kill_sb()&n; *&t;@sb: superblock to kill&n; *&n; *&t;generic_shutdown_super() does all fs-independent work on superblock&n; *&t;shutdown.  Typical -&gt;kill_sb() should pick all fs-specific objects&n; *&t;that need destruction out of superblock, call generic_shutdown_super()&n; *&t;and release aforementioned objects.  Note: dentries and inodes _are_&n; *&t;taken care of and do not need specific handling.&n; */
DECL|function|generic_shutdown_super
r_void
id|generic_shutdown_super
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
r_struct
id|dentry
op_star
id|root
op_assign
id|sb-&gt;s_root
suffix:semicolon
r_struct
id|super_operations
op_star
id|sop
op_assign
id|sb-&gt;s_op
suffix:semicolon
r_if
c_cond
(paren
id|root
)paren
(brace
id|sb-&gt;s_root
op_assign
l_int|NULL
suffix:semicolon
id|shrink_dcache_parent
c_func
(paren
id|root
)paren
suffix:semicolon
id|shrink_dcache_anon
c_func
(paren
op_amp
id|sb-&gt;s_anon
)paren
suffix:semicolon
id|dput
c_func
(paren
id|root
)paren
suffix:semicolon
id|fsync_super
c_func
(paren
id|sb
)paren
suffix:semicolon
id|lock_super
c_func
(paren
id|sb
)paren
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|sb-&gt;s_flags
op_and_assign
op_complement
id|MS_ACTIVE
suffix:semicolon
multiline_comment|/* bad name - it should be evict_inodes() */
id|invalidate_inodes
c_func
(paren
id|sb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sop
)paren
(brace
r_if
c_cond
(paren
id|sop-&gt;write_super
op_logical_and
id|sb-&gt;s_dirt
)paren
id|sop
op_member_access_from_pointer
id|write_super
c_func
(paren
id|sb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sop-&gt;put_super
)paren
id|sop
op_member_access_from_pointer
id|put_super
c_func
(paren
id|sb
)paren
suffix:semicolon
)brace
multiline_comment|/* Forget any remaining inodes */
r_if
c_cond
(paren
id|invalidate_inodes
c_func
(paren
id|sb
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;VFS: Busy inodes after unmount. &quot;
l_string|&quot;Self-destruct in 5 seconds.  Have a nice day...&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
id|unlock_super
c_func
(paren
id|sb
)paren
suffix:semicolon
)brace
id|spin_lock
c_func
(paren
op_amp
id|sb_lock
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|sb-&gt;s_list
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|sb-&gt;s_instances
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|sb_lock
)paren
suffix:semicolon
id|up_write
c_func
(paren
op_amp
id|sb-&gt;s_umount
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;sget&t;-&t;find or create a superblock&n; *&t;@type:&t;filesystem type superblock should belong to&n; *&t;@test:&t;comparison callback&n; *&t;@set:&t;setup callback&n; *&t;@data:&t;argument to each of them&n; */
DECL|function|sget
r_struct
id|super_block
op_star
id|sget
c_func
(paren
r_struct
id|file_system_type
op_star
id|type
comma
r_int
(paren
op_star
id|test
)paren
(paren
r_struct
id|super_block
op_star
comma
r_void
op_star
)paren
comma
r_int
(paren
op_star
id|set
)paren
(paren
r_struct
id|super_block
op_star
comma
r_void
op_star
)paren
comma
r_void
op_star
id|data
)paren
(brace
r_struct
id|super_block
op_star
id|s
op_assign
id|alloc_super
c_func
(paren
)paren
suffix:semicolon
r_struct
id|list_head
op_star
id|p
suffix:semicolon
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|s
)paren
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|ENOMEM
)paren
suffix:semicolon
id|retry
suffix:colon
id|spin_lock
c_func
(paren
op_amp
id|sb_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|test
)paren
id|list_for_each
c_func
(paren
id|p
comma
op_amp
id|type-&gt;fs_supers
)paren
(brace
r_struct
id|super_block
op_star
id|old
suffix:semicolon
id|old
op_assign
id|list_entry
c_func
(paren
id|p
comma
r_struct
id|super_block
comma
id|s_instances
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|test
c_func
(paren
id|old
comma
id|data
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|grab_super
c_func
(paren
id|old
)paren
)paren
r_goto
id|retry
suffix:semicolon
id|destroy_super
c_func
(paren
id|s
)paren
suffix:semicolon
r_return
id|old
suffix:semicolon
)brace
id|err
op_assign
id|set
c_func
(paren
id|s
comma
id|data
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
id|spin_unlock
c_func
(paren
op_amp
id|sb_lock
)paren
suffix:semicolon
id|destroy_super
c_func
(paren
id|s
)paren
suffix:semicolon
r_return
id|ERR_PTR
c_func
(paren
id|err
)paren
suffix:semicolon
)brace
id|s-&gt;s_type
op_assign
id|type
suffix:semicolon
id|list_add
c_func
(paren
op_amp
id|s-&gt;s_list
comma
id|super_blocks.prev
)paren
suffix:semicolon
id|list_add
c_func
(paren
op_amp
id|s-&gt;s_instances
comma
op_amp
id|type-&gt;fs_supers
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|sb_lock
)paren
suffix:semicolon
id|get_filesystem
c_func
(paren
id|type
)paren
suffix:semicolon
r_return
id|s
suffix:semicolon
)brace
r_struct
id|vfsmount
op_star
id|alloc_vfsmnt
c_func
(paren
r_char
op_star
id|name
)paren
suffix:semicolon
r_void
id|free_vfsmnt
c_func
(paren
r_struct
id|vfsmount
op_star
id|mnt
)paren
suffix:semicolon
DECL|function|drop_super
r_void
id|drop_super
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
id|up_read
c_func
(paren
op_amp
id|sb-&gt;s_umount
)paren
suffix:semicolon
id|put_super
c_func
(paren
id|sb
)paren
suffix:semicolon
)brace
DECL|function|write_super
r_static
r_inline
r_void
id|write_super
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
id|lock_super
c_func
(paren
id|sb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sb-&gt;s_root
op_logical_and
id|sb-&gt;s_dirt
)paren
r_if
c_cond
(paren
id|sb-&gt;s_op
op_logical_and
id|sb-&gt;s_op-&gt;write_super
)paren
id|sb-&gt;s_op
op_member_access_from_pointer
id|write_super
c_func
(paren
id|sb
)paren
suffix:semicolon
id|unlock_super
c_func
(paren
id|sb
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Note: check the dirty flag before waiting, so we don&squot;t&n; * hold up the sync while mounting a device. (The newly&n; * mounted device won&squot;t need syncing.)&n; */
DECL|function|sync_supers
r_void
id|sync_supers
c_func
(paren
r_void
)paren
(brace
r_struct
id|super_block
op_star
id|sb
suffix:semicolon
id|restart
suffix:colon
id|spin_lock
c_func
(paren
op_amp
id|sb_lock
)paren
suffix:semicolon
id|sb
op_assign
id|sb_entry
c_func
(paren
id|super_blocks.next
)paren
suffix:semicolon
r_while
c_loop
(paren
id|sb
op_ne
id|sb_entry
c_func
(paren
op_amp
id|super_blocks
)paren
)paren
r_if
c_cond
(paren
id|sb-&gt;s_dirt
)paren
(brace
id|sb-&gt;s_count
op_increment
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|sb_lock
)paren
suffix:semicolon
id|down_read
c_func
(paren
op_amp
id|sb-&gt;s_umount
)paren
suffix:semicolon
id|write_super
c_func
(paren
id|sb
)paren
suffix:semicolon
id|drop_super
c_func
(paren
id|sb
)paren
suffix:semicolon
r_goto
id|restart
suffix:semicolon
)brace
r_else
id|sb
op_assign
id|sb_entry
c_func
(paren
id|sb-&gt;s_list.next
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|sb_lock
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;get_super&t;-&t;get the superblock of a device&n; *&t;@dev: device to get the superblock for&n; *&t;&n; *&t;Scans the superblock list and finds the superblock of the file system&n; *&t;mounted on the device given. %NULL is returned if no match is found.&n; */
DECL|function|get_super
r_struct
id|super_block
op_star
id|get_super
c_func
(paren
r_struct
id|block_device
op_star
id|bdev
)paren
(brace
r_struct
id|list_head
op_star
id|p
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bdev
)paren
r_return
l_int|NULL
suffix:semicolon
id|rescan
suffix:colon
id|spin_lock
c_func
(paren
op_amp
id|sb_lock
)paren
suffix:semicolon
id|list_for_each
c_func
(paren
id|p
comma
op_amp
id|super_blocks
)paren
(brace
r_struct
id|super_block
op_star
id|s
op_assign
id|sb_entry
c_func
(paren
id|p
)paren
suffix:semicolon
r_if
c_cond
(paren
id|s-&gt;s_bdev
op_eq
id|bdev
)paren
(brace
id|s-&gt;s_count
op_increment
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|sb_lock
)paren
suffix:semicolon
id|down_read
c_func
(paren
op_amp
id|s-&gt;s_umount
)paren
suffix:semicolon
r_if
c_cond
(paren
id|s-&gt;s_root
)paren
r_return
id|s
suffix:semicolon
id|drop_super
c_func
(paren
id|s
)paren
suffix:semicolon
r_goto
id|rescan
suffix:semicolon
)brace
)brace
id|spin_unlock
c_func
(paren
op_amp
id|sb_lock
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|user_get_super
r_struct
id|super_block
op_star
id|user_get_super
c_func
(paren
id|dev_t
id|dev
)paren
(brace
r_struct
id|list_head
op_star
id|p
suffix:semicolon
id|rescan
suffix:colon
id|spin_lock
c_func
(paren
op_amp
id|sb_lock
)paren
suffix:semicolon
id|list_for_each
c_func
(paren
id|p
comma
op_amp
id|super_blocks
)paren
(brace
r_struct
id|super_block
op_star
id|s
op_assign
id|sb_entry
c_func
(paren
id|p
)paren
suffix:semicolon
r_if
c_cond
(paren
id|s-&gt;s_dev
op_eq
id|dev
)paren
(brace
id|s-&gt;s_count
op_increment
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|sb_lock
)paren
suffix:semicolon
id|down_read
c_func
(paren
op_amp
id|s-&gt;s_umount
)paren
suffix:semicolon
r_if
c_cond
(paren
id|s-&gt;s_root
)paren
r_return
id|s
suffix:semicolon
id|drop_super
c_func
(paren
id|s
)paren
suffix:semicolon
r_goto
id|rescan
suffix:semicolon
)brace
)brace
id|spin_unlock
c_func
(paren
op_amp
id|sb_lock
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|sys_ustat
id|asmlinkage
r_int
id|sys_ustat
c_func
(paren
id|dev_t
id|dev
comma
r_struct
id|ustat
op_star
id|ubuf
)paren
(brace
r_struct
id|super_block
op_star
id|s
suffix:semicolon
r_struct
id|ustat
id|tmp
suffix:semicolon
r_struct
id|statfs
id|sbuf
suffix:semicolon
r_int
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
id|s
op_assign
id|user_get_super
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|s
op_eq
l_int|NULL
)paren
r_goto
id|out
suffix:semicolon
id|err
op_assign
id|vfs_statfs
c_func
(paren
id|s
comma
op_amp
id|sbuf
)paren
suffix:semicolon
id|drop_super
c_func
(paren
id|s
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_goto
id|out
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
r_struct
id|ustat
)paren
)paren
suffix:semicolon
id|tmp.f_tfree
op_assign
id|sbuf.f_bfree
suffix:semicolon
id|tmp.f_tinode
op_assign
id|sbuf.f_ffree
suffix:semicolon
id|err
op_assign
id|copy_to_user
c_func
(paren
id|ubuf
comma
op_amp
id|tmp
comma
r_sizeof
(paren
r_struct
id|ustat
)paren
)paren
ques
c_cond
op_minus
id|EFAULT
suffix:colon
l_int|0
suffix:semicolon
id|out
suffix:colon
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;do_remount_sb&t;-&t;asks filesystem to change mount options.&n; *&t;@sb:&t;superblock in question&n; *&t;@flags:&t;numeric part of options&n; *&t;@data:&t;the rest of options&n; *&n; *&t;Alters the mount options of a mounted file system.&n; */
DECL|function|do_remount_sb
r_int
id|do_remount_sb
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
id|flags
comma
r_void
op_star
id|data
)paren
(brace
r_int
id|retval
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|flags
op_amp
id|MS_RDONLY
)paren
op_logical_and
id|bdev_read_only
c_func
(paren
id|sb-&gt;s_bdev
)paren
)paren
r_return
op_minus
id|EACCES
suffix:semicolon
multiline_comment|/*flags |= MS_RDONLY;*/
r_if
c_cond
(paren
id|flags
op_amp
id|MS_RDONLY
)paren
id|acct_auto_close
c_func
(paren
id|sb
)paren
suffix:semicolon
id|shrink_dcache_sb
c_func
(paren
id|sb
)paren
suffix:semicolon
id|fsync_super
c_func
(paren
id|sb
)paren
suffix:semicolon
multiline_comment|/* If we are remounting RDONLY, make sure there are no rw files open */
r_if
c_cond
(paren
(paren
id|flags
op_amp
id|MS_RDONLY
)paren
op_logical_and
op_logical_neg
(paren
id|sb-&gt;s_flags
op_amp
id|MS_RDONLY
)paren
)paren
r_if
c_cond
(paren
op_logical_neg
id|fs_may_remount_ro
c_func
(paren
id|sb
)paren
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
r_if
c_cond
(paren
id|sb-&gt;s_op
op_logical_and
id|sb-&gt;s_op-&gt;remount_fs
)paren
(brace
id|lock_super
c_func
(paren
id|sb
)paren
suffix:semicolon
id|retval
op_assign
id|sb-&gt;s_op
op_member_access_from_pointer
id|remount_fs
c_func
(paren
id|sb
comma
op_amp
id|flags
comma
id|data
)paren
suffix:semicolon
id|unlock_super
c_func
(paren
id|sb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
r_return
id|retval
suffix:semicolon
)brace
id|sb-&gt;s_flags
op_assign
(paren
id|sb-&gt;s_flags
op_amp
op_complement
id|MS_RMT_MASK
)paren
op_or
(paren
id|flags
op_amp
id|MS_RMT_MASK
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Unnamed block devices are dummy devices used by virtual&n; * filesystems which don&squot;t use real block-devices.  -- jrs&n; */
DECL|enumerator|Max_anon
r_enum
(brace
id|Max_anon
op_assign
l_int|256
)brace
suffix:semicolon
DECL|variable|unnamed_dev_in_use
r_static
r_int
r_int
id|unnamed_dev_in_use
(braket
id|Max_anon
op_div
(paren
l_int|8
op_star
r_sizeof
(paren
r_int
r_int
)paren
)paren
)braket
suffix:semicolon
DECL|variable|unnamed_dev_lock
r_static
id|spinlock_t
id|unnamed_dev_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
multiline_comment|/* protects the above */
DECL|function|set_anon_super
r_int
id|set_anon_super
c_func
(paren
r_struct
id|super_block
op_star
id|s
comma
r_void
op_star
id|data
)paren
(brace
r_int
id|dev
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|unnamed_dev_lock
)paren
suffix:semicolon
id|dev
op_assign
id|find_first_zero_bit
c_func
(paren
id|unnamed_dev_in_use
comma
id|Max_anon
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev
op_eq
id|Max_anon
)paren
(brace
id|spin_unlock
c_func
(paren
op_amp
id|unnamed_dev_lock
)paren
suffix:semicolon
r_return
op_minus
id|EMFILE
suffix:semicolon
)brace
id|set_bit
c_func
(paren
id|dev
comma
id|unnamed_dev_in_use
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|unnamed_dev_lock
)paren
suffix:semicolon
id|s-&gt;s_dev
op_assign
id|MKDEV
c_func
(paren
l_int|0
comma
id|dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|kill_anon_super
r_void
id|kill_anon_super
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
r_int
id|slot
op_assign
id|MINOR
c_func
(paren
id|sb-&gt;s_dev
)paren
suffix:semicolon
id|generic_shutdown_super
c_func
(paren
id|sb
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|unnamed_dev_lock
)paren
suffix:semicolon
id|clear_bit
c_func
(paren
id|slot
comma
id|unnamed_dev_in_use
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|unnamed_dev_lock
)paren
suffix:semicolon
)brace
DECL|function|kill_litter_super
r_void
id|kill_litter_super
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
r_if
c_cond
(paren
id|sb-&gt;s_root
)paren
id|d_genocide
c_func
(paren
id|sb-&gt;s_root
)paren
suffix:semicolon
id|kill_anon_super
c_func
(paren
id|sb
)paren
suffix:semicolon
)brace
DECL|function|set_bdev_super
r_static
r_int
id|set_bdev_super
c_func
(paren
r_struct
id|super_block
op_star
id|s
comma
r_void
op_star
id|data
)paren
(brace
id|s-&gt;s_bdev
op_assign
id|data
suffix:semicolon
id|s-&gt;s_dev
op_assign
id|s-&gt;s_bdev-&gt;bd_dev
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|test_bdev_super
r_static
r_int
id|test_bdev_super
c_func
(paren
r_struct
id|super_block
op_star
id|s
comma
r_void
op_star
id|data
)paren
(brace
r_return
(paren
r_void
op_star
)paren
id|s-&gt;s_bdev
op_eq
id|data
suffix:semicolon
)brace
DECL|function|get_sb_bdev
r_struct
id|super_block
op_star
id|get_sb_bdev
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
comma
r_int
(paren
op_star
id|fill_super
)paren
(paren
r_struct
id|super_block
op_star
comma
r_void
op_star
comma
r_int
)paren
)paren
(brace
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_struct
id|block_device
op_star
id|bdev
suffix:semicolon
r_struct
id|block_device_operations
op_star
id|bdops
suffix:semicolon
id|devfs_handle_t
id|de
suffix:semicolon
r_struct
id|super_block
op_star
id|s
suffix:semicolon
r_struct
id|nameidata
id|nd
suffix:semicolon
id|kdev_t
id|dev
suffix:semicolon
r_int
id|error
op_assign
l_int|0
suffix:semicolon
id|mode_t
id|mode
op_assign
id|FMODE_READ
suffix:semicolon
multiline_comment|/* we always need it ;-) */
multiline_comment|/* What device it is? */
r_if
c_cond
(paren
op_logical_neg
id|dev_name
op_logical_or
op_logical_neg
op_star
id|dev_name
)paren
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|EINVAL
)paren
suffix:semicolon
id|error
op_assign
id|path_lookup
c_func
(paren
id|dev_name
comma
id|LOOKUP_FOLLOW
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
id|inode
op_assign
id|nd.dentry-&gt;d_inode
suffix:semicolon
id|error
op_assign
op_minus
id|ENOTBLK
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|S_ISBLK
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
r_goto
id|out
suffix:semicolon
id|error
op_assign
op_minus
id|EACCES
suffix:semicolon
r_if
c_cond
(paren
id|nd.mnt-&gt;mnt_flags
op_amp
id|MNT_NODEV
)paren
r_goto
id|out
suffix:semicolon
id|error
op_assign
id|bd_acquire
c_func
(paren
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_goto
id|out
suffix:semicolon
id|bdev
op_assign
id|inode-&gt;i_bdev
suffix:semicolon
id|de
op_assign
id|devfs_get_handle_from_inode
(paren
id|inode
)paren
suffix:semicolon
id|bdops
op_assign
id|devfs_get_ops
(paren
id|de
)paren
suffix:semicolon
multiline_comment|/*  Increments module use count  */
r_if
c_cond
(paren
id|bdops
)paren
id|bdev-&gt;bd_op
op_assign
id|bdops
suffix:semicolon
multiline_comment|/* Done with lookups, semaphore down */
id|dev
op_assign
id|to_kdev_t
c_func
(paren
id|bdev-&gt;bd_dev
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|flags
op_amp
id|MS_RDONLY
)paren
)paren
id|mode
op_or_assign
id|FMODE_WRITE
suffix:semicolon
id|error
op_assign
id|blkdev_get
c_func
(paren
id|bdev
comma
id|mode
comma
l_int|0
comma
id|BDEV_FS
)paren
suffix:semicolon
id|devfs_put_ops
(paren
id|de
)paren
suffix:semicolon
multiline_comment|/*  Decrement module use count now we&squot;re safe  */
r_if
c_cond
(paren
id|error
)paren
r_goto
id|out
suffix:semicolon
id|check_disk_change
c_func
(paren
id|dev
)paren
suffix:semicolon
id|error
op_assign
op_minus
id|EACCES
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|flags
op_amp
id|MS_RDONLY
)paren
op_logical_and
id|bdev_read_only
c_func
(paren
id|bdev
)paren
)paren
r_goto
id|out1
suffix:semicolon
id|error
op_assign
id|bd_claim
c_func
(paren
id|bdev
comma
id|fs_type
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_goto
id|out1
suffix:semicolon
id|s
op_assign
id|sget
c_func
(paren
id|fs_type
comma
id|test_bdev_super
comma
id|set_bdev_super
comma
id|bdev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|s
)paren
)paren
(brace
id|bd_release
c_func
(paren
id|bdev
)paren
suffix:semicolon
id|blkdev_put
c_func
(paren
id|bdev
comma
id|BDEV_FS
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|s-&gt;s_root
)paren
(brace
r_if
c_cond
(paren
(paren
id|flags
op_xor
id|s-&gt;s_flags
)paren
op_amp
id|MS_RDONLY
)paren
(brace
id|up_write
c_func
(paren
op_amp
id|s-&gt;s_umount
)paren
suffix:semicolon
id|deactivate_super
c_func
(paren
id|s
)paren
suffix:semicolon
id|s
op_assign
id|ERR_PTR
c_func
(paren
op_minus
id|EBUSY
)paren
suffix:semicolon
)brace
id|bd_release
c_func
(paren
id|bdev
)paren
suffix:semicolon
id|blkdev_put
c_func
(paren
id|bdev
comma
id|BDEV_FS
)paren
suffix:semicolon
)brace
r_else
(brace
id|s-&gt;s_flags
op_assign
id|flags
suffix:semicolon
id|strncpy
c_func
(paren
id|s-&gt;s_id
comma
id|bdevname
c_func
(paren
id|bdev
)paren
comma
r_sizeof
(paren
id|s-&gt;s_id
)paren
)paren
suffix:semicolon
id|s-&gt;s_old_blocksize
op_assign
id|block_size
c_func
(paren
id|bdev
)paren
suffix:semicolon
id|sb_set_blocksize
c_func
(paren
id|s
comma
id|s-&gt;s_old_blocksize
)paren
suffix:semicolon
id|error
op_assign
id|fill_super
c_func
(paren
id|s
comma
id|data
comma
id|flags
op_amp
id|MS_VERBOSE
ques
c_cond
l_int|1
suffix:colon
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
(brace
id|up_write
c_func
(paren
op_amp
id|s-&gt;s_umount
)paren
suffix:semicolon
id|deactivate_super
c_func
(paren
id|s
)paren
suffix:semicolon
id|s
op_assign
id|ERR_PTR
c_func
(paren
id|error
)paren
suffix:semicolon
)brace
r_else
id|s-&gt;s_flags
op_or_assign
id|MS_ACTIVE
suffix:semicolon
)brace
id|path_release
c_func
(paren
op_amp
id|nd
)paren
suffix:semicolon
r_return
id|s
suffix:semicolon
id|out1
suffix:colon
id|blkdev_put
c_func
(paren
id|bdev
comma
id|BDEV_FS
)paren
suffix:semicolon
id|out
suffix:colon
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
DECL|function|kill_block_super
r_void
id|kill_block_super
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
r_struct
id|block_device
op_star
id|bdev
op_assign
id|sb-&gt;s_bdev
suffix:semicolon
id|generic_shutdown_super
c_func
(paren
id|sb
)paren
suffix:semicolon
id|set_blocksize
c_func
(paren
id|bdev
comma
id|sb-&gt;s_old_blocksize
)paren
suffix:semicolon
id|bd_release
c_func
(paren
id|bdev
)paren
suffix:semicolon
id|blkdev_put
c_func
(paren
id|bdev
comma
id|BDEV_FS
)paren
suffix:semicolon
)brace
DECL|function|get_sb_nodev
r_struct
id|super_block
op_star
id|get_sb_nodev
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
r_void
op_star
id|data
comma
r_int
(paren
op_star
id|fill_super
)paren
(paren
r_struct
id|super_block
op_star
comma
r_void
op_star
comma
r_int
)paren
)paren
(brace
r_int
id|error
suffix:semicolon
r_struct
id|super_block
op_star
id|s
op_assign
id|sget
c_func
(paren
id|fs_type
comma
l_int|NULL
comma
id|set_anon_super
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
id|s
)paren
)paren
r_return
id|s
suffix:semicolon
id|s-&gt;s_flags
op_assign
id|flags
suffix:semicolon
id|error
op_assign
id|fill_super
c_func
(paren
id|s
comma
id|data
comma
id|flags
op_amp
id|MS_VERBOSE
ques
c_cond
l_int|1
suffix:colon
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
(brace
id|up_write
c_func
(paren
op_amp
id|s-&gt;s_umount
)paren
suffix:semicolon
id|deactivate_super
c_func
(paren
id|s
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
id|s-&gt;s_flags
op_or_assign
id|MS_ACTIVE
suffix:semicolon
r_return
id|s
suffix:semicolon
)brace
DECL|function|compare_single
r_static
r_int
id|compare_single
c_func
(paren
r_struct
id|super_block
op_star
id|s
comma
r_void
op_star
id|p
)paren
(brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|get_sb_single
r_struct
id|super_block
op_star
id|get_sb_single
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
r_void
op_star
id|data
comma
r_int
(paren
op_star
id|fill_super
)paren
(paren
r_struct
id|super_block
op_star
comma
r_void
op_star
comma
r_int
)paren
)paren
(brace
r_struct
id|super_block
op_star
id|s
suffix:semicolon
r_int
id|error
suffix:semicolon
id|s
op_assign
id|sget
c_func
(paren
id|fs_type
comma
id|compare_single
comma
id|set_anon_super
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
id|s
)paren
)paren
r_return
id|s
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|s-&gt;s_root
)paren
(brace
id|s-&gt;s_flags
op_assign
id|flags
suffix:semicolon
id|error
op_assign
id|fill_super
c_func
(paren
id|s
comma
id|data
comma
id|flags
op_amp
id|MS_VERBOSE
ques
c_cond
l_int|1
suffix:colon
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
(brace
id|up_write
c_func
(paren
op_amp
id|s-&gt;s_umount
)paren
suffix:semicolon
id|deactivate_super
c_func
(paren
id|s
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
id|s-&gt;s_flags
op_or_assign
id|MS_ACTIVE
suffix:semicolon
)brace
id|do_remount_sb
c_func
(paren
id|s
comma
id|flags
comma
id|data
)paren
suffix:semicolon
r_return
id|s
suffix:semicolon
)brace
r_struct
id|vfsmount
op_star
DECL|function|do_kern_mount
id|do_kern_mount
c_func
(paren
r_const
r_char
op_star
id|fstype
comma
r_int
id|flags
comma
r_char
op_star
id|name
comma
r_void
op_star
id|data
)paren
(brace
r_struct
id|file_system_type
op_star
id|type
op_assign
id|get_fs_type
c_func
(paren
id|fstype
)paren
suffix:semicolon
r_struct
id|super_block
op_star
id|sb
op_assign
id|ERR_PTR
c_func
(paren
op_minus
id|ENOMEM
)paren
suffix:semicolon
r_struct
id|vfsmount
op_star
id|mnt
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|type
)paren
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|ENODEV
)paren
suffix:semicolon
id|mnt
op_assign
id|alloc_vfsmnt
c_func
(paren
id|name
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mnt
)paren
r_goto
id|out
suffix:semicolon
id|sb
op_assign
id|type
op_member_access_from_pointer
id|get_sb
c_func
(paren
id|type
comma
id|flags
comma
id|name
comma
id|data
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|sb
)paren
)paren
r_goto
id|out_mnt
suffix:semicolon
id|mnt-&gt;mnt_sb
op_assign
id|sb
suffix:semicolon
id|mnt-&gt;mnt_root
op_assign
id|dget
c_func
(paren
id|sb-&gt;s_root
)paren
suffix:semicolon
id|mnt-&gt;mnt_mountpoint
op_assign
id|sb-&gt;s_root
suffix:semicolon
id|mnt-&gt;mnt_parent
op_assign
id|mnt
suffix:semicolon
id|up_write
c_func
(paren
op_amp
id|sb-&gt;s_umount
)paren
suffix:semicolon
id|put_filesystem
c_func
(paren
id|type
)paren
suffix:semicolon
r_return
id|mnt
suffix:semicolon
id|out_mnt
suffix:colon
id|free_vfsmnt
c_func
(paren
id|mnt
)paren
suffix:semicolon
id|out
suffix:colon
id|put_filesystem
c_func
(paren
id|type
)paren
suffix:semicolon
r_return
(paren
r_struct
id|vfsmount
op_star
)paren
id|sb
suffix:semicolon
)brace
DECL|function|kern_mount
r_struct
id|vfsmount
op_star
id|kern_mount
c_func
(paren
r_struct
id|file_system_type
op_star
id|type
)paren
(brace
r_return
id|do_kern_mount
c_func
(paren
id|type-&gt;name
comma
l_int|0
comma
(paren
r_char
op_star
)paren
id|type-&gt;name
comma
l_int|NULL
)paren
suffix:semicolon
)brace
eof
