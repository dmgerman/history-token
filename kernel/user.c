multiline_comment|/*&n; * The &quot;user cache&quot;.&n; *&n; * (C) Copyright 1991-2000 Linus Torvalds&n; *&n; * We have a per-user structure to keep track of how many&n; * processes, files etc the user has claimed, in order to be&n; * able to have per-user limits for system resources. &n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/bitops.h&gt;
multiline_comment|/*&n; * UID task count cache, to get fast user lookup in &quot;alloc_uid&quot;&n; * when changing user ID&squot;s (ie setuid() and friends).&n; */
DECL|macro|UIDHASH_BITS
mdefine_line|#define UIDHASH_BITS&t;&t;8
DECL|macro|UIDHASH_SZ
mdefine_line|#define UIDHASH_SZ&t;&t;(1 &lt;&lt; UIDHASH_BITS)
DECL|macro|UIDHASH_MASK
mdefine_line|#define UIDHASH_MASK&t;&t;(UIDHASH_SZ - 1)
DECL|macro|__uidhashfn
mdefine_line|#define __uidhashfn(uid)&t;(((uid &gt;&gt; UIDHASH_BITS) + uid) &amp; UIDHASH_MASK)
DECL|macro|uidhashentry
mdefine_line|#define uidhashentry(uid)&t;(uidhash_table + __uidhashfn((uid)))
DECL|variable|uid_cachep
r_static
id|kmem_cache_t
op_star
id|uid_cachep
suffix:semicolon
DECL|variable|uidhash_table
r_static
r_struct
id|list_head
id|uidhash_table
(braket
id|UIDHASH_SZ
)braket
suffix:semicolon
DECL|variable|uidhash_lock
r_static
id|spinlock_t
id|uidhash_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|variable|root_user
r_struct
id|user_struct
id|root_user
op_assign
(brace
dot
id|__count
op_assign
id|ATOMIC_INIT
c_func
(paren
l_int|1
)paren
comma
dot
id|processes
op_assign
id|ATOMIC_INIT
c_func
(paren
l_int|1
)paren
comma
dot
id|files
op_assign
id|ATOMIC_INIT
c_func
(paren
l_int|0
)paren
)brace
suffix:semicolon
multiline_comment|/*&n; * These routines must be called with the uidhash spinlock held!&n; */
DECL|function|uid_hash_insert
r_static
r_inline
r_void
id|uid_hash_insert
c_func
(paren
r_struct
id|user_struct
op_star
id|up
comma
r_struct
id|list_head
op_star
id|hashent
)paren
(brace
id|list_add
c_func
(paren
op_amp
id|up-&gt;uidhash_list
comma
id|hashent
)paren
suffix:semicolon
)brace
DECL|function|uid_hash_remove
r_static
r_inline
r_void
id|uid_hash_remove
c_func
(paren
r_struct
id|user_struct
op_star
id|up
)paren
(brace
id|list_del
c_func
(paren
op_amp
id|up-&gt;uidhash_list
)paren
suffix:semicolon
)brace
DECL|function|uid_hash_find
r_static
r_inline
r_struct
id|user_struct
op_star
id|uid_hash_find
c_func
(paren
id|uid_t
id|uid
comma
r_struct
id|list_head
op_star
id|hashent
)paren
(brace
r_struct
id|list_head
op_star
id|up
suffix:semicolon
id|list_for_each
c_func
(paren
id|up
comma
id|hashent
)paren
(brace
r_struct
id|user_struct
op_star
id|user
suffix:semicolon
id|user
op_assign
id|list_entry
c_func
(paren
id|up
comma
r_struct
id|user_struct
comma
id|uidhash_list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|user-&gt;uid
op_eq
id|uid
)paren
(brace
id|atomic_inc
c_func
(paren
op_amp
id|user-&gt;__count
)paren
suffix:semicolon
r_return
id|user
suffix:semicolon
)brace
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|find_user
r_struct
id|user_struct
op_star
id|find_user
c_func
(paren
id|uid_t
id|uid
)paren
(brace
r_return
id|uid_hash_find
c_func
(paren
id|uid
comma
id|uidhashentry
c_func
(paren
id|uid
)paren
)paren
suffix:semicolon
)brace
DECL|function|free_uid
r_void
id|free_uid
c_func
(paren
r_struct
id|user_struct
op_star
id|up
)paren
(brace
r_if
c_cond
(paren
id|up
op_logical_and
id|atomic_dec_and_lock
c_func
(paren
op_amp
id|up-&gt;__count
comma
op_amp
id|uidhash_lock
)paren
)paren
(brace
id|uid_hash_remove
c_func
(paren
id|up
)paren
suffix:semicolon
id|kmem_cache_free
c_func
(paren
id|uid_cachep
comma
id|up
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|uidhash_lock
)paren
suffix:semicolon
)brace
)brace
DECL|function|alloc_uid
r_struct
id|user_struct
op_star
id|alloc_uid
c_func
(paren
id|uid_t
id|uid
)paren
(brace
r_struct
id|list_head
op_star
id|hashent
op_assign
id|uidhashentry
c_func
(paren
id|uid
)paren
suffix:semicolon
r_struct
id|user_struct
op_star
id|up
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|uidhash_lock
)paren
suffix:semicolon
id|up
op_assign
id|uid_hash_find
c_func
(paren
id|uid
comma
id|hashent
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|uidhash_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|up
)paren
(brace
r_struct
id|user_struct
op_star
r_new
suffix:semicolon
r_new
op_assign
id|kmem_cache_alloc
c_func
(paren
id|uid_cachep
comma
id|SLAB_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
r_new
)paren
r_return
l_int|NULL
suffix:semicolon
r_new
op_member_access_from_pointer
id|uid
op_assign
id|uid
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
r_new
op_member_access_from_pointer
id|__count
comma
l_int|1
)paren
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
r_new
op_member_access_from_pointer
id|processes
comma
l_int|0
)paren
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
r_new
op_member_access_from_pointer
id|files
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Before adding this, check whether we raced&n;&t;&t; * on adding the same user already..&n;&t;&t; */
id|spin_lock
c_func
(paren
op_amp
id|uidhash_lock
)paren
suffix:semicolon
id|up
op_assign
id|uid_hash_find
c_func
(paren
id|uid
comma
id|hashent
)paren
suffix:semicolon
r_if
c_cond
(paren
id|up
)paren
(brace
id|kmem_cache_free
c_func
(paren
id|uid_cachep
comma
r_new
)paren
suffix:semicolon
)brace
r_else
(brace
id|uid_hash_insert
c_func
(paren
r_new
comma
id|hashent
)paren
suffix:semicolon
id|up
op_assign
r_new
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|uidhash_lock
)paren
suffix:semicolon
)brace
r_return
id|up
suffix:semicolon
)brace
DECL|function|switch_uid
r_void
id|switch_uid
c_func
(paren
r_struct
id|user_struct
op_star
id|new_user
)paren
(brace
r_struct
id|user_struct
op_star
id|old_user
suffix:semicolon
multiline_comment|/* What if a process setreuid()&squot;s and this brings the&n;&t; * new uid over his NPROC rlimit?  We can check this now&n;&t; * cheaply with the new uid cache, so if it matters&n;&t; * we should be checking for it.  -DaveM&n;&t; */
id|old_user
op_assign
id|current-&gt;user
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|new_user-&gt;processes
)paren
suffix:semicolon
id|atomic_dec
c_func
(paren
op_amp
id|old_user-&gt;processes
)paren
suffix:semicolon
id|current-&gt;user
op_assign
id|new_user
suffix:semicolon
id|free_uid
c_func
(paren
id|old_user
)paren
suffix:semicolon
)brace
DECL|function|uid_cache_init
r_static
r_int
id|__init
id|uid_cache_init
c_func
(paren
r_void
)paren
(brace
r_int
id|n
suffix:semicolon
id|uid_cachep
op_assign
id|kmem_cache_create
c_func
(paren
l_string|&quot;uid_cache&quot;
comma
r_sizeof
(paren
r_struct
id|user_struct
)paren
comma
l_int|0
comma
id|SLAB_HWCACHE_ALIGN
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|uid_cachep
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;Cannot create uid taskcount SLAB cache&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_for
c_loop
(paren
id|n
op_assign
l_int|0
suffix:semicolon
id|n
OL
id|UIDHASH_SZ
suffix:semicolon
op_increment
id|n
)paren
(brace
id|INIT_LIST_HEAD
c_func
(paren
id|uidhash_table
op_plus
id|n
)paren
suffix:semicolon
)brace
multiline_comment|/* Insert the root user immediately - init already runs with this */
id|uid_hash_insert
c_func
(paren
op_amp
id|root_user
comma
id|uidhashentry
c_func
(paren
l_int|0
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|uid_cache_init
id|module_init
c_func
(paren
id|uid_cache_init
)paren
suffix:semicolon
eof
