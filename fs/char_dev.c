multiline_comment|/*&n; *  linux/fs/block_dev.c&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/devfs_fs_kernel.h&gt;
macro_line|#ifdef CONFIG_KMOD
macro_line|#include &lt;linux/kmod.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
multiline_comment|/* serial module kmod load support */
r_struct
id|tty_driver
op_star
id|get_tty_driver
c_func
(paren
id|kdev_t
id|device
)paren
suffix:semicolon
DECL|macro|isa_tty_dev
mdefine_line|#define isa_tty_dev(ma)&t;(ma == TTY_MAJOR || ma == TTYAUX_MAJOR)
DECL|macro|need_serial
mdefine_line|#define need_serial(ma,mi) (get_tty_driver(mk_kdev(ma,mi)) == NULL)
macro_line|#endif
DECL|macro|HASH_BITS
mdefine_line|#define HASH_BITS&t;6
DECL|macro|HASH_SIZE
mdefine_line|#define HASH_SIZE&t;(1UL &lt;&lt; HASH_BITS)
DECL|macro|HASH_MASK
mdefine_line|#define HASH_MASK&t;(HASH_SIZE-1)
DECL|variable|cdev_hashtable
r_static
r_struct
id|list_head
id|cdev_hashtable
(braket
id|HASH_SIZE
)braket
suffix:semicolon
DECL|variable|cdev_lock
r_static
id|spinlock_t
id|cdev_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|variable|cdev_cachep
r_static
id|kmem_cache_t
op_star
id|cdev_cachep
suffix:semicolon
DECL|macro|alloc_cdev
mdefine_line|#define alloc_cdev() &bslash;&n;&t; ((struct char_device *) kmem_cache_alloc(cdev_cachep, SLAB_KERNEL))
DECL|macro|destroy_cdev
mdefine_line|#define destroy_cdev(cdev) kmem_cache_free(cdev_cachep, (cdev))
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
id|char_device
op_star
id|cdev
op_assign
(paren
r_struct
id|char_device
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
(brace
id|memset
c_func
(paren
id|cdev
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|cdev
)paren
)paren
suffix:semicolon
id|sema_init
c_func
(paren
op_amp
id|cdev-&gt;sem
comma
l_int|1
)paren
suffix:semicolon
)brace
)brace
DECL|function|cdev_cache_init
r_void
id|__init
id|cdev_cache_init
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|list_head
op_star
id|head
op_assign
id|cdev_hashtable
suffix:semicolon
id|i
op_assign
id|HASH_SIZE
suffix:semicolon
r_do
(brace
id|INIT_LIST_HEAD
c_func
(paren
id|head
)paren
suffix:semicolon
id|head
op_increment
suffix:semicolon
id|i
op_decrement
suffix:semicolon
)brace
r_while
c_loop
(paren
id|i
)paren
suffix:semicolon
id|cdev_cachep
op_assign
id|kmem_cache_create
c_func
(paren
l_string|&quot;cdev_cache&quot;
comma
r_sizeof
(paren
r_struct
id|char_device
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
op_logical_neg
id|cdev_cachep
)paren
id|panic
c_func
(paren
l_string|&quot;Cannot create cdev_cache SLAB cache&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Most likely _very_ bad one - but then it&squot;s hardly critical for small&n; * /dev and can be fixed when somebody will need really large one.&n; */
DECL|function|hash
r_static
r_inline
r_int
r_int
id|hash
c_func
(paren
id|dev_t
id|dev
)paren
(brace
r_int
r_int
id|tmp
op_assign
id|dev
suffix:semicolon
id|tmp
op_assign
id|tmp
op_plus
(paren
id|tmp
op_rshift
id|HASH_BITS
)paren
op_plus
(paren
id|tmp
op_rshift
id|HASH_BITS
op_star
l_int|2
)paren
suffix:semicolon
r_return
id|tmp
op_amp
id|HASH_MASK
suffix:semicolon
)brace
DECL|function|cdfind
r_static
r_struct
id|char_device
op_star
id|cdfind
c_func
(paren
id|dev_t
id|dev
comma
r_struct
id|list_head
op_star
id|head
)paren
(brace
r_struct
id|list_head
op_star
id|p
suffix:semicolon
r_struct
id|char_device
op_star
id|cdev
suffix:semicolon
id|list_for_each
c_func
(paren
id|p
comma
id|head
)paren
(brace
id|cdev
op_assign
id|list_entry
c_func
(paren
id|p
comma
r_struct
id|char_device
comma
id|hash
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cdev-&gt;dev
op_ne
id|dev
)paren
r_continue
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|cdev-&gt;count
)paren
suffix:semicolon
r_return
id|cdev
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|cdget
r_struct
id|char_device
op_star
id|cdget
c_func
(paren
id|dev_t
id|dev
)paren
(brace
r_struct
id|list_head
op_star
id|head
op_assign
id|cdev_hashtable
op_plus
id|hash
c_func
(paren
id|dev
)paren
suffix:semicolon
r_struct
id|char_device
op_star
id|cdev
comma
op_star
id|new_cdev
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|cdev_lock
)paren
suffix:semicolon
id|cdev
op_assign
id|cdfind
c_func
(paren
id|dev
comma
id|head
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|cdev_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cdev
)paren
r_return
id|cdev
suffix:semicolon
id|new_cdev
op_assign
id|alloc_cdev
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|new_cdev
)paren
r_return
l_int|NULL
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|new_cdev-&gt;count
comma
l_int|1
)paren
suffix:semicolon
id|new_cdev-&gt;dev
op_assign
id|dev
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|cdev_lock
)paren
suffix:semicolon
id|cdev
op_assign
id|cdfind
c_func
(paren
id|dev
comma
id|head
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cdev
)paren
(brace
id|list_add
c_func
(paren
op_amp
id|new_cdev-&gt;hash
comma
id|head
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|cdev_lock
)paren
suffix:semicolon
r_return
id|new_cdev
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|cdev_lock
)paren
suffix:semicolon
id|destroy_cdev
c_func
(paren
id|new_cdev
)paren
suffix:semicolon
r_return
id|cdev
suffix:semicolon
)brace
DECL|function|cdput
r_void
id|cdput
c_func
(paren
r_struct
id|char_device
op_star
id|cdev
)paren
(brace
r_if
c_cond
(paren
id|atomic_dec_and_lock
c_func
(paren
op_amp
id|cdev-&gt;count
comma
op_amp
id|cdev_lock
)paren
)paren
(brace
id|list_del
c_func
(paren
op_amp
id|cdev-&gt;hash
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|cdev_lock
)paren
suffix:semicolon
id|destroy_cdev
c_func
(paren
id|cdev
)paren
suffix:semicolon
)brace
)brace
DECL|struct|device_struct
r_struct
id|device_struct
(brace
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
DECL|member|fops
r_struct
id|file_operations
op_star
id|fops
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|chrdevs_lock
r_static
id|rwlock_t
id|chrdevs_lock
op_assign
id|RW_LOCK_UNLOCKED
suffix:semicolon
DECL|variable|chrdevs
r_static
r_struct
id|device_struct
id|chrdevs
(braket
id|MAX_CHRDEV
)braket
suffix:semicolon
DECL|function|get_chrdev_list
r_int
id|get_chrdev_list
c_func
(paren
r_char
op_star
id|page
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
id|len
suffix:semicolon
id|len
op_assign
id|sprintf
c_func
(paren
id|page
comma
l_string|&quot;Character devices:&bslash;n&quot;
)paren
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|chrdevs_lock
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|MAX_CHRDEV
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|chrdevs
(braket
id|i
)braket
dot
id|fops
)paren
(brace
id|len
op_add_assign
id|sprintf
c_func
(paren
id|page
op_plus
id|len
comma
l_string|&quot;%3d %s&bslash;n&quot;
comma
id|i
comma
id|chrdevs
(braket
id|i
)braket
dot
id|name
)paren
suffix:semicolon
)brace
)brace
id|read_unlock
c_func
(paren
op_amp
id|chrdevs_lock
)paren
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
multiline_comment|/*&n;&t;Return the function table of a device.&n;&t;Load the driver if needed.&n;&t;Increment the reference count of module in question.&n;*/
DECL|function|get_chrfops
r_static
r_struct
id|file_operations
op_star
id|get_chrfops
c_func
(paren
r_int
r_int
id|major
comma
r_int
r_int
id|minor
)paren
(brace
r_struct
id|file_operations
op_star
id|ret
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|major
op_logical_or
id|major
op_ge
id|MAX_CHRDEV
)paren
r_return
l_int|NULL
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|chrdevs_lock
)paren
suffix:semicolon
id|ret
op_assign
id|fops_get
c_func
(paren
id|chrdevs
(braket
id|major
)braket
dot
id|fops
)paren
suffix:semicolon
id|read_unlock
c_func
(paren
op_amp
id|chrdevs_lock
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_KMOD
r_if
c_cond
(paren
id|ret
op_logical_and
id|isa_tty_dev
c_func
(paren
id|major
)paren
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
id|need_serial
c_func
(paren
id|major
comma
id|minor
)paren
)paren
(brace
multiline_comment|/* Force request_module anyway, but what for? */
id|fops_put
c_func
(paren
id|ret
)paren
suffix:semicolon
id|ret
op_assign
l_int|NULL
suffix:semicolon
)brace
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|ret
)paren
(brace
r_char
id|name
(braket
l_int|20
)braket
suffix:semicolon
id|sprintf
c_func
(paren
id|name
comma
l_string|&quot;char-major-%d&quot;
comma
id|major
)paren
suffix:semicolon
id|request_module
c_func
(paren
id|name
)paren
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|chrdevs_lock
)paren
suffix:semicolon
id|ret
op_assign
id|fops_get
c_func
(paren
id|chrdevs
(braket
id|major
)braket
dot
id|fops
)paren
suffix:semicolon
id|read_unlock
c_func
(paren
op_amp
id|chrdevs_lock
)paren
suffix:semicolon
)brace
macro_line|#endif
r_return
id|ret
suffix:semicolon
)brace
DECL|function|register_chrdev
r_int
id|register_chrdev
c_func
(paren
r_int
r_int
id|major
comma
r_const
r_char
op_star
id|name
comma
r_struct
id|file_operations
op_star
id|fops
)paren
(brace
r_if
c_cond
(paren
id|devfs_only
c_func
(paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|major
op_eq
l_int|0
)paren
(brace
id|write_lock
c_func
(paren
op_amp
id|chrdevs_lock
)paren
suffix:semicolon
r_for
c_loop
(paren
id|major
op_assign
id|MAX_CHRDEV
op_minus
l_int|1
suffix:semicolon
id|major
OG
l_int|0
suffix:semicolon
id|major
op_decrement
)paren
(brace
r_if
c_cond
(paren
id|chrdevs
(braket
id|major
)braket
dot
id|fops
op_eq
l_int|NULL
)paren
(brace
id|chrdevs
(braket
id|major
)braket
dot
id|name
op_assign
id|name
suffix:semicolon
id|chrdevs
(braket
id|major
)braket
dot
id|fops
op_assign
id|fops
suffix:semicolon
id|write_unlock
c_func
(paren
op_amp
id|chrdevs_lock
)paren
suffix:semicolon
r_return
id|major
suffix:semicolon
)brace
)brace
id|write_unlock
c_func
(paren
op_amp
id|chrdevs_lock
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
r_if
c_cond
(paren
id|major
op_ge
id|MAX_CHRDEV
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|write_lock
c_func
(paren
op_amp
id|chrdevs_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|chrdevs
(braket
id|major
)braket
dot
id|fops
op_logical_and
id|chrdevs
(braket
id|major
)braket
dot
id|fops
op_ne
id|fops
)paren
(brace
id|write_unlock
c_func
(paren
op_amp
id|chrdevs_lock
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|chrdevs
(braket
id|major
)braket
dot
id|name
op_assign
id|name
suffix:semicolon
id|chrdevs
(braket
id|major
)braket
dot
id|fops
op_assign
id|fops
suffix:semicolon
id|write_unlock
c_func
(paren
op_amp
id|chrdevs_lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|unregister_chrdev
r_int
id|unregister_chrdev
c_func
(paren
r_int
r_int
id|major
comma
r_const
r_char
op_star
id|name
)paren
(brace
r_if
c_cond
(paren
id|devfs_only
c_func
(paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|major
op_ge
id|MAX_CHRDEV
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|write_lock
c_func
(paren
op_amp
id|chrdevs_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|chrdevs
(braket
id|major
)braket
dot
id|fops
op_logical_or
id|strcmp
c_func
(paren
id|chrdevs
(braket
id|major
)braket
dot
id|name
comma
id|name
)paren
)paren
(brace
id|write_unlock
c_func
(paren
op_amp
id|chrdevs_lock
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|chrdevs
(braket
id|major
)braket
dot
id|name
op_assign
l_int|NULL
suffix:semicolon
id|chrdevs
(braket
id|major
)braket
dot
id|fops
op_assign
l_int|NULL
suffix:semicolon
id|write_unlock
c_func
(paren
op_amp
id|chrdevs_lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Called every time a character special file is opened&n; */
DECL|function|chrdev_open
r_int
id|chrdev_open
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
id|filp
)paren
(brace
r_int
id|ret
op_assign
op_minus
id|ENODEV
suffix:semicolon
id|filp-&gt;f_op
op_assign
id|get_chrfops
c_func
(paren
id|major
c_func
(paren
id|inode-&gt;i_rdev
)paren
comma
id|minor
c_func
(paren
id|inode-&gt;i_rdev
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|filp-&gt;f_op
)paren
(brace
id|ret
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|filp-&gt;f_op-&gt;open
op_ne
l_int|NULL
)paren
(brace
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|ret
op_assign
id|filp-&gt;f_op
op_member_access_from_pointer
id|open
c_func
(paren
id|inode
comma
id|filp
)paren
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * Dummy default file-operations: the only thing this does&n; * is contain the open that then fills in the correct operations&n; * depending on the special file...&n; */
DECL|variable|def_chr_fops
r_struct
id|file_operations
id|def_chr_fops
op_assign
(brace
dot
id|open
op_assign
id|chrdev_open
comma
)brace
suffix:semicolon
DECL|function|cdevname
r_const
r_char
op_star
id|cdevname
c_func
(paren
id|kdev_t
id|dev
)paren
(brace
r_static
r_char
id|buffer
(braket
l_int|32
)braket
suffix:semicolon
r_const
r_char
op_star
id|name
op_assign
id|chrdevs
(braket
id|major
c_func
(paren
id|dev
)paren
)braket
dot
id|name
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|name
)paren
id|name
op_assign
l_string|&quot;unknown-char&quot;
suffix:semicolon
id|sprintf
c_func
(paren
id|buffer
comma
l_string|&quot;%s(%d,%d)&quot;
comma
id|name
comma
id|major
c_func
(paren
id|dev
)paren
comma
id|minor
c_func
(paren
id|dev
)paren
)paren
suffix:semicolon
r_return
id|buffer
suffix:semicolon
)brace
eof
