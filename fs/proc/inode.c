multiline_comment|/*&n; *  linux/fs/proc/inode.c&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; */
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/file.h&gt;
macro_line|#include &lt;linux/locks.h&gt;
macro_line|#include &lt;linux/limits.h&gt;
DECL|macro|__NO_VERSION__
mdefine_line|#define __NO_VERSION__
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
r_extern
r_void
id|free_proc_entry
c_func
(paren
r_struct
id|proc_dir_entry
op_star
)paren
suffix:semicolon
DECL|function|de_get
r_struct
id|proc_dir_entry
op_star
id|de_get
c_func
(paren
r_struct
id|proc_dir_entry
op_star
id|de
)paren
(brace
r_if
c_cond
(paren
id|de
)paren
id|atomic_inc
c_func
(paren
op_amp
id|de-&gt;count
)paren
suffix:semicolon
r_return
id|de
suffix:semicolon
)brace
multiline_comment|/*&n; * Decrements the use count and checks for deferred deletion.&n; */
DECL|function|de_put
r_void
id|de_put
c_func
(paren
r_struct
id|proc_dir_entry
op_star
id|de
)paren
(brace
r_if
c_cond
(paren
id|de
)paren
(brace
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|atomic_read
c_func
(paren
op_amp
id|de-&gt;count
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;de_put: entry %s already free!&bslash;n&quot;
comma
id|de-&gt;name
)paren
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|atomic_dec_and_test
c_func
(paren
op_amp
id|de-&gt;count
)paren
)paren
(brace
r_if
c_cond
(paren
id|de-&gt;deleted
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;de_put: deferred delete of %s&bslash;n&quot;
comma
id|de-&gt;name
)paren
suffix:semicolon
id|free_proc_entry
c_func
(paren
id|de
)paren
suffix:semicolon
)brace
)brace
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Decrement the use count of the proc_dir_entry.&n; */
DECL|function|proc_delete_inode
r_static
r_void
id|proc_delete_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_struct
id|proc_dir_entry
op_star
id|de
op_assign
id|PDE
c_func
(paren
id|inode
)paren
suffix:semicolon
id|inode-&gt;i_state
op_assign
id|I_CLEAR
suffix:semicolon
r_if
c_cond
(paren
id|PROC_INODE_PROPER
c_func
(paren
id|inode
)paren
)paren
(brace
id|proc_pid_delete_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|de
)paren
(brace
r_if
c_cond
(paren
id|de-&gt;owner
)paren
id|__MOD_DEC_USE_COUNT
c_func
(paren
id|de-&gt;owner
)paren
suffix:semicolon
id|de_put
c_func
(paren
id|de
)paren
suffix:semicolon
)brace
)brace
DECL|variable|proc_mnt
r_struct
id|vfsmount
op_star
id|proc_mnt
suffix:semicolon
DECL|function|proc_read_inode
r_static
r_void
id|proc_read_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
id|inode-&gt;i_mtime
op_assign
id|inode-&gt;i_atime
op_assign
id|inode-&gt;i_ctime
op_assign
id|CURRENT_TIME
suffix:semicolon
)brace
DECL|function|proc_statfs
r_static
r_int
id|proc_statfs
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|statfs
op_star
id|buf
)paren
(brace
id|buf-&gt;f_type
op_assign
id|PROC_SUPER_MAGIC
suffix:semicolon
id|buf-&gt;f_bsize
op_assign
id|PAGE_SIZE
op_div
r_sizeof
(paren
r_int
)paren
suffix:semicolon
id|buf-&gt;f_bfree
op_assign
l_int|0
suffix:semicolon
id|buf-&gt;f_bavail
op_assign
l_int|0
suffix:semicolon
id|buf-&gt;f_ffree
op_assign
l_int|0
suffix:semicolon
id|buf-&gt;f_namelen
op_assign
id|NAME_MAX
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|proc_inode_cachep
r_static
id|kmem_cache_t
op_star
id|proc_inode_cachep
suffix:semicolon
DECL|function|proc_alloc_inode
r_static
r_struct
id|inode
op_star
id|proc_alloc_inode
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
r_struct
id|proc_inode
op_star
id|ei
suffix:semicolon
id|ei
op_assign
(paren
r_struct
id|proc_inode
op_star
)paren
id|kmem_cache_alloc
c_func
(paren
id|proc_inode_cachep
comma
id|SLAB_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ei
)paren
r_return
l_int|NULL
suffix:semicolon
r_return
op_amp
id|ei-&gt;vfs_inode
suffix:semicolon
)brace
DECL|function|proc_destroy_inode
r_static
r_void
id|proc_destroy_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
id|kmem_cache_free
c_func
(paren
id|proc_inode_cachep
comma
id|PROC_I
c_func
(paren
id|inode
)paren
)paren
suffix:semicolon
)brace
DECL|function|init_once
r_static
r_void
id|init_once
c_func
(paren
r_void
op_star
id|foo
comma
id|kmem_cache_t
op_star
id|cachep
comma
r_int
r_int
id|flags
)paren
(brace
r_struct
id|proc_inode
op_star
id|ei
op_assign
(paren
r_struct
id|proc_inode
op_star
)paren
id|foo
suffix:semicolon
r_if
c_cond
(paren
(paren
id|flags
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
id|inode_init_once
c_func
(paren
op_amp
id|ei-&gt;vfs_inode
)paren
suffix:semicolon
)brace
DECL|function|proc_init_inodecache
r_int
id|__init
id|proc_init_inodecache
c_func
(paren
r_void
)paren
(brace
id|proc_inode_cachep
op_assign
id|kmem_cache_create
c_func
(paren
l_string|&quot;proc_inode_cache&quot;
comma
r_sizeof
(paren
r_struct
id|proc_inode
)paren
comma
l_int|0
comma
id|SLAB_HWCACHE_ALIGN
comma
id|init_once
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|proc_inode_cachep
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|proc_sops
r_static
r_struct
id|super_operations
id|proc_sops
op_assign
(brace
id|alloc_inode
suffix:colon
id|proc_alloc_inode
comma
id|destroy_inode
suffix:colon
id|proc_destroy_inode
comma
id|read_inode
suffix:colon
id|proc_read_inode
comma
id|put_inode
suffix:colon
id|force_delete
comma
id|delete_inode
suffix:colon
id|proc_delete_inode
comma
id|statfs
suffix:colon
id|proc_statfs
comma
)brace
suffix:semicolon
DECL|function|parse_options
r_static
r_int
id|parse_options
c_func
(paren
r_char
op_star
id|options
comma
id|uid_t
op_star
id|uid
comma
id|gid_t
op_star
id|gid
)paren
(brace
r_char
op_star
id|this_char
comma
op_star
id|value
suffix:semicolon
op_star
id|uid
op_assign
id|current-&gt;uid
suffix:semicolon
op_star
id|gid
op_assign
id|current-&gt;gid
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|options
)paren
r_return
l_int|1
suffix:semicolon
r_for
c_loop
(paren
id|this_char
op_assign
id|strtok
c_func
(paren
id|options
comma
l_string|&quot;,&quot;
)paren
suffix:semicolon
id|this_char
suffix:semicolon
id|this_char
op_assign
id|strtok
c_func
(paren
l_int|NULL
comma
l_string|&quot;,&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
(paren
id|value
op_assign
id|strchr
c_func
(paren
id|this_char
comma
l_char|&squot;=&squot;
)paren
)paren
op_ne
l_int|NULL
)paren
op_star
id|value
op_increment
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|this_char
comma
l_string|&quot;uid&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|value
op_logical_or
op_logical_neg
op_star
id|value
)paren
r_return
l_int|0
suffix:semicolon
op_star
id|uid
op_assign
id|simple_strtoul
c_func
(paren
id|value
comma
op_amp
id|value
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|value
)paren
r_return
l_int|0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|this_char
comma
l_string|&quot;gid&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|value
op_logical_or
op_logical_neg
op_star
id|value
)paren
r_return
l_int|0
suffix:semicolon
op_star
id|gid
op_assign
id|simple_strtoul
c_func
(paren
id|value
comma
op_amp
id|value
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|value
)paren
r_return
l_int|0
suffix:semicolon
)brace
r_else
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|proc_get_inode
r_struct
id|inode
op_star
id|proc_get_inode
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
id|ino
comma
r_struct
id|proc_dir_entry
op_star
id|de
)paren
(brace
r_struct
id|inode
op_star
id|inode
suffix:semicolon
multiline_comment|/*&n;&t; * Increment the use count so the dir entry can&squot;t disappear.&n;&t; */
id|de_get
c_func
(paren
id|de
)paren
suffix:semicolon
macro_line|#if 1
multiline_comment|/* shouldn&squot;t ever happen */
r_if
c_cond
(paren
id|de
op_logical_and
id|de-&gt;deleted
)paren
id|printk
c_func
(paren
l_string|&quot;proc_iget: using deleted entry %s, count=%d&bslash;n&quot;
comma
id|de-&gt;name
comma
id|atomic_read
c_func
(paren
op_amp
id|de-&gt;count
)paren
)paren
suffix:semicolon
macro_line|#endif
id|inode
op_assign
id|iget
c_func
(paren
id|sb
comma
id|ino
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode
)paren
r_goto
id|out_fail
suffix:semicolon
id|PROC_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|pde
op_assign
id|de
suffix:semicolon
r_if
c_cond
(paren
id|de
)paren
(brace
r_if
c_cond
(paren
id|de-&gt;mode
)paren
(brace
id|inode-&gt;i_mode
op_assign
id|de-&gt;mode
suffix:semicolon
id|inode-&gt;i_uid
op_assign
id|de-&gt;uid
suffix:semicolon
id|inode-&gt;i_gid
op_assign
id|de-&gt;gid
suffix:semicolon
)brace
r_if
c_cond
(paren
id|de-&gt;size
)paren
id|inode-&gt;i_size
op_assign
id|de-&gt;size
suffix:semicolon
r_if
c_cond
(paren
id|de-&gt;nlink
)paren
id|inode-&gt;i_nlink
op_assign
id|de-&gt;nlink
suffix:semicolon
r_if
c_cond
(paren
id|de-&gt;owner
)paren
id|__MOD_INC_USE_COUNT
c_func
(paren
id|de-&gt;owner
)paren
suffix:semicolon
r_if
c_cond
(paren
id|de-&gt;proc_iops
)paren
id|inode-&gt;i_op
op_assign
id|de-&gt;proc_iops
suffix:semicolon
r_if
c_cond
(paren
id|de-&gt;proc_fops
)paren
id|inode-&gt;i_fop
op_assign
id|de-&gt;proc_fops
suffix:semicolon
r_else
r_if
c_cond
(paren
id|S_ISBLK
c_func
(paren
id|de-&gt;mode
)paren
op_logical_or
id|S_ISCHR
c_func
(paren
id|de-&gt;mode
)paren
op_logical_or
id|S_ISFIFO
c_func
(paren
id|de-&gt;mode
)paren
)paren
id|init_special_inode
c_func
(paren
id|inode
comma
id|de-&gt;mode
comma
id|kdev_t_to_nr
c_func
(paren
id|de-&gt;rdev
)paren
)paren
suffix:semicolon
)brace
id|out
suffix:colon
r_return
id|inode
suffix:semicolon
id|out_fail
suffix:colon
id|de_put
c_func
(paren
id|de
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
DECL|function|proc_fill_super
r_int
id|proc_fill_super
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
comma
r_int
id|silent
)paren
(brace
r_struct
id|inode
op_star
id|root_inode
suffix:semicolon
r_struct
id|task_struct
op_star
id|p
suffix:semicolon
id|s-&gt;s_blocksize
op_assign
l_int|1024
suffix:semicolon
id|s-&gt;s_blocksize_bits
op_assign
l_int|10
suffix:semicolon
id|s-&gt;s_magic
op_assign
id|PROC_SUPER_MAGIC
suffix:semicolon
id|s-&gt;s_op
op_assign
op_amp
id|proc_sops
suffix:semicolon
id|root_inode
op_assign
id|proc_get_inode
c_func
(paren
id|s
comma
id|PROC_ROOT_INO
comma
op_amp
id|proc_root
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|root_inode
)paren
r_goto
id|out_no_root
suffix:semicolon
multiline_comment|/*&n;&t; * Fixup the root inode&squot;s nlink value&n;&t; */
id|read_lock
c_func
(paren
op_amp
id|tasklist_lock
)paren
suffix:semicolon
id|for_each_task
c_func
(paren
id|p
)paren
r_if
c_cond
(paren
id|p-&gt;pid
)paren
id|root_inode-&gt;i_nlink
op_increment
suffix:semicolon
id|read_unlock
c_func
(paren
op_amp
id|tasklist_lock
)paren
suffix:semicolon
id|s-&gt;s_root
op_assign
id|d_alloc_root
c_func
(paren
id|root_inode
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|s-&gt;s_root
)paren
r_goto
id|out_no_root
suffix:semicolon
id|parse_options
c_func
(paren
id|data
comma
op_amp
id|root_inode-&gt;i_uid
comma
op_amp
id|root_inode-&gt;i_gid
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|out_no_root
suffix:colon
id|printk
c_func
(paren
l_string|&quot;proc_read_super: get root inode failed&bslash;n&quot;
)paren
suffix:semicolon
id|iput
c_func
(paren
id|root_inode
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
