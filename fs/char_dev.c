multiline_comment|/*&n; *  linux/fs/block_dev.c&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
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
eof
