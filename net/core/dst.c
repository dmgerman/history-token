multiline_comment|/*&n; * net/core/dst.c&t;Protocol independent destination cache.&n; *&n; * Authors:&t;&t;Alexey Kuznetsov, &lt;kuznet@ms2.inr.ac.ru&gt;&n; *&n; */
macro_line|#include &lt;linux/bitops.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;net/dst.h&gt;
multiline_comment|/* Locking strategy:&n; * 1) Garbage collection state of dead destination cache&n; *    entries is protected by dst_lock.&n; * 2) GC is run only from BH context, and is the only remover&n; *    of entries.&n; * 3) Entries are added to the garbage list from both BH&n; *    and non-BH context, so local BH disabling is needed.&n; * 4) All operations modify state, so a spinlock is used.&n; */
DECL|variable|dst_garbage_list
r_static
r_struct
id|dst_entry
op_star
id|dst_garbage_list
suffix:semicolon
macro_line|#if RT_CACHE_DEBUG &gt;= 2 
DECL|variable|dst_total
r_static
id|atomic_t
id|dst_total
op_assign
id|ATOMIC_INIT
c_func
(paren
l_int|0
)paren
suffix:semicolon
macro_line|#endif
DECL|variable|dst_lock
r_static
id|spinlock_t
id|dst_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|variable|dst_gc_timer_expires
r_static
r_int
r_int
id|dst_gc_timer_expires
suffix:semicolon
DECL|variable|dst_gc_timer_inc
r_static
r_int
r_int
id|dst_gc_timer_inc
op_assign
id|DST_GC_MAX
suffix:semicolon
r_static
r_void
id|dst_run_gc
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_static
r_void
id|___dst_free
c_func
(paren
r_struct
id|dst_entry
op_star
id|dst
)paren
suffix:semicolon
DECL|variable|dst_gc_timer
r_static
r_struct
id|timer_list
id|dst_gc_timer
op_assign
id|TIMER_INITIALIZER
c_func
(paren
id|dst_run_gc
comma
l_int|0
comma
id|DST_GC_MIN
)paren
suffix:semicolon
DECL|function|dst_run_gc
r_static
r_void
id|dst_run_gc
c_func
(paren
r_int
r_int
id|dummy
)paren
(brace
r_int
id|delayed
op_assign
l_int|0
suffix:semicolon
r_struct
id|dst_entry
op_star
id|dst
comma
op_star
op_star
id|dstp
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|spin_trylock
c_func
(paren
op_amp
id|dst_lock
)paren
)paren
(brace
id|mod_timer
c_func
(paren
op_amp
id|dst_gc_timer
comma
id|jiffies
op_plus
id|HZ
op_div
l_int|10
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|del_timer
c_func
(paren
op_amp
id|dst_gc_timer
)paren
suffix:semicolon
id|dstp
op_assign
op_amp
id|dst_garbage_list
suffix:semicolon
r_while
c_loop
(paren
(paren
id|dst
op_assign
op_star
id|dstp
)paren
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|dst-&gt;__refcnt
)paren
)paren
(brace
id|dstp
op_assign
op_amp
id|dst-&gt;next
suffix:semicolon
id|delayed
op_increment
suffix:semicolon
r_continue
suffix:semicolon
)brace
op_star
id|dstp
op_assign
id|dst-&gt;next
suffix:semicolon
id|dst
op_assign
id|dst_destroy
c_func
(paren
id|dst
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dst
)paren
(brace
multiline_comment|/* NOHASH and still referenced. Unless it is already&n;&t;&t;&t; * on gc list, invalidate it and add to gc list.&n;&t;&t;&t; *&n;&t;&t;&t; * Note: this is temporary. Actually, NOHASH dst&squot;s&n;&t;&t;&t; * must be obsoleted when parent is obsoleted.&n;&t;&t;&t; * But we do not have state &quot;obsoleted, but&n;&t;&t;&t; * referenced by parent&quot;, so it is right.&n;&t;&t;&t; */
r_if
c_cond
(paren
id|dst-&gt;obsolete
OG
l_int|1
)paren
r_continue
suffix:semicolon
id|___dst_free
c_func
(paren
id|dst
)paren
suffix:semicolon
id|dst-&gt;next
op_assign
op_star
id|dstp
suffix:semicolon
op_star
id|dstp
op_assign
id|dst
suffix:semicolon
id|dstp
op_assign
op_amp
id|dst-&gt;next
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|dst_garbage_list
)paren
(brace
id|dst_gc_timer_inc
op_assign
id|DST_GC_MAX
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|dst_gc_timer_expires
op_add_assign
id|dst_gc_timer_inc
)paren
OG
id|DST_GC_MAX
)paren
id|dst_gc_timer_expires
op_assign
id|DST_GC_MAX
suffix:semicolon
id|dst_gc_timer_inc
op_add_assign
id|DST_GC_INC
suffix:semicolon
id|dst_gc_timer.expires
op_assign
id|jiffies
op_plus
id|dst_gc_timer_expires
suffix:semicolon
macro_line|#if RT_CACHE_DEBUG &gt;= 2
id|printk
c_func
(paren
l_string|&quot;dst_total: %d/%d %ld&bslash;n&quot;
comma
id|atomic_read
c_func
(paren
op_amp
id|dst_total
)paren
comma
id|delayed
comma
id|dst_gc_timer_expires
)paren
suffix:semicolon
macro_line|#endif
id|add_timer
c_func
(paren
op_amp
id|dst_gc_timer
)paren
suffix:semicolon
id|out
suffix:colon
id|spin_unlock
c_func
(paren
op_amp
id|dst_lock
)paren
suffix:semicolon
)brace
DECL|function|dst_discard
r_static
r_int
id|dst_discard
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dst_blackhole
r_static
r_int
id|dst_blackhole
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dst_alloc
r_void
op_star
id|dst_alloc
c_func
(paren
r_struct
id|dst_ops
op_star
id|ops
)paren
(brace
r_struct
id|dst_entry
op_star
id|dst
suffix:semicolon
r_if
c_cond
(paren
id|ops-&gt;gc
op_logical_and
id|atomic_read
c_func
(paren
op_amp
id|ops-&gt;entries
)paren
OG
id|ops-&gt;gc_thresh
)paren
(brace
r_if
c_cond
(paren
id|ops
op_member_access_from_pointer
id|gc
c_func
(paren
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
)brace
id|dst
op_assign
id|kmem_cache_alloc
c_func
(paren
id|ops-&gt;kmem_cachep
comma
id|SLAB_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dst
)paren
r_return
l_int|NULL
suffix:semicolon
id|memset
c_func
(paren
id|dst
comma
l_int|0
comma
id|ops-&gt;entry_size
)paren
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|dst-&gt;__refcnt
comma
l_int|0
)paren
suffix:semicolon
id|dst-&gt;ops
op_assign
id|ops
suffix:semicolon
id|dst-&gt;lastuse
op_assign
id|jiffies
suffix:semicolon
id|dst-&gt;path
op_assign
id|dst
suffix:semicolon
id|dst-&gt;input
op_assign
id|dst_discard
suffix:semicolon
id|dst-&gt;output
op_assign
id|dst_blackhole
suffix:semicolon
macro_line|#if RT_CACHE_DEBUG &gt;= 2 
id|atomic_inc
c_func
(paren
op_amp
id|dst_total
)paren
suffix:semicolon
macro_line|#endif
id|atomic_inc
c_func
(paren
op_amp
id|ops-&gt;entries
)paren
suffix:semicolon
r_return
id|dst
suffix:semicolon
)brace
DECL|function|___dst_free
r_static
r_void
id|___dst_free
c_func
(paren
r_struct
id|dst_entry
op_star
id|dst
)paren
(brace
multiline_comment|/* The first case (dev==NULL) is required, when&n;&t;   protocol module is unloaded.&n;&t; */
r_if
c_cond
(paren
id|dst-&gt;dev
op_eq
l_int|NULL
op_logical_or
op_logical_neg
(paren
id|dst-&gt;dev-&gt;flags
op_amp
id|IFF_UP
)paren
)paren
(brace
id|dst-&gt;input
op_assign
id|dst_discard
suffix:semicolon
id|dst-&gt;output
op_assign
id|dst_blackhole
suffix:semicolon
)brace
id|dst-&gt;obsolete
op_assign
l_int|2
suffix:semicolon
)brace
DECL|function|__dst_free
r_void
id|__dst_free
c_func
(paren
r_struct
id|dst_entry
op_star
id|dst
)paren
(brace
id|spin_lock_bh
c_func
(paren
op_amp
id|dst_lock
)paren
suffix:semicolon
id|___dst_free
c_func
(paren
id|dst
)paren
suffix:semicolon
id|dst-&gt;next
op_assign
id|dst_garbage_list
suffix:semicolon
id|dst_garbage_list
op_assign
id|dst
suffix:semicolon
r_if
c_cond
(paren
id|dst_gc_timer_inc
OG
id|DST_GC_INC
)paren
(brace
id|dst_gc_timer_inc
op_assign
id|DST_GC_INC
suffix:semicolon
id|dst_gc_timer_expires
op_assign
id|DST_GC_MIN
suffix:semicolon
id|mod_timer
c_func
(paren
op_amp
id|dst_gc_timer
comma
id|jiffies
op_plus
id|dst_gc_timer_expires
)paren
suffix:semicolon
)brace
id|spin_unlock_bh
c_func
(paren
op_amp
id|dst_lock
)paren
suffix:semicolon
)brace
DECL|function|dst_destroy
r_struct
id|dst_entry
op_star
id|dst_destroy
c_func
(paren
r_struct
id|dst_entry
op_star
id|dst
)paren
(brace
r_struct
id|dst_entry
op_star
id|child
suffix:semicolon
r_struct
id|neighbour
op_star
id|neigh
suffix:semicolon
r_struct
id|hh_cache
op_star
id|hh
suffix:semicolon
id|again
suffix:colon
id|neigh
op_assign
id|dst-&gt;neighbour
suffix:semicolon
id|hh
op_assign
id|dst-&gt;hh
suffix:semicolon
id|child
op_assign
id|dst-&gt;child
suffix:semicolon
id|dst-&gt;hh
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|hh
op_logical_and
id|atomic_dec_and_test
c_func
(paren
op_amp
id|hh-&gt;hh_refcnt
)paren
)paren
id|kfree
c_func
(paren
id|hh
)paren
suffix:semicolon
r_if
c_cond
(paren
id|neigh
)paren
(brace
id|dst-&gt;neighbour
op_assign
l_int|NULL
suffix:semicolon
id|neigh_release
c_func
(paren
id|neigh
)paren
suffix:semicolon
)brace
id|atomic_dec
c_func
(paren
op_amp
id|dst-&gt;ops-&gt;entries
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dst-&gt;ops-&gt;destroy
)paren
id|dst-&gt;ops
op_member_access_from_pointer
id|destroy
c_func
(paren
id|dst
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dst-&gt;dev
)paren
id|dev_put
c_func
(paren
id|dst-&gt;dev
)paren
suffix:semicolon
macro_line|#if RT_CACHE_DEBUG &gt;= 2 
id|atomic_dec
c_func
(paren
op_amp
id|dst_total
)paren
suffix:semicolon
macro_line|#endif
id|kmem_cache_free
c_func
(paren
id|dst-&gt;ops-&gt;kmem_cachep
comma
id|dst
)paren
suffix:semicolon
id|dst
op_assign
id|child
suffix:semicolon
r_if
c_cond
(paren
id|dst
)paren
(brace
r_if
c_cond
(paren
id|atomic_dec_and_test
c_func
(paren
op_amp
id|dst-&gt;__refcnt
)paren
)paren
(brace
multiline_comment|/* We were real parent of this dst, so kill child. */
r_if
c_cond
(paren
id|dst-&gt;flags
op_amp
id|DST_NOHASH
)paren
r_goto
id|again
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Child is still referenced, return it for freeing. */
r_if
c_cond
(paren
id|dst-&gt;flags
op_amp
id|DST_NOHASH
)paren
r_return
id|dst
suffix:semicolon
multiline_comment|/* Child is still in his hash table */
)brace
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|dst_dev_event
r_static
r_int
id|dst_dev_event
c_func
(paren
r_struct
id|notifier_block
op_star
id|this
comma
r_int
r_int
id|event
comma
r_void
op_star
id|ptr
)paren
(brace
r_struct
id|net_device
op_star
id|dev
op_assign
id|ptr
suffix:semicolon
r_struct
id|dst_entry
op_star
id|dst
suffix:semicolon
r_switch
c_cond
(paren
id|event
)paren
(brace
r_case
id|NETDEV_UNREGISTER
suffix:colon
r_case
id|NETDEV_DOWN
suffix:colon
id|spin_lock_bh
c_func
(paren
op_amp
id|dst_lock
)paren
suffix:semicolon
r_for
c_loop
(paren
id|dst
op_assign
id|dst_garbage_list
suffix:semicolon
id|dst
suffix:semicolon
id|dst
op_assign
id|dst-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|dst-&gt;dev
op_eq
id|dev
)paren
(brace
multiline_comment|/* Dirty hack. We did it in 2.2 (in __dst_free),&n;&t;&t;&t;&t;   we have _very_ good reasons not to repeat&n;&t;&t;&t;&t;   this mistake in 2.3, but we have no choice&n;&t;&t;&t;&t;   now. _It_ _is_ _explicit_ _deliberate_&n;&t;&t;&t;&t;   _race_ _condition_.&n;&t;&t;&t;&t; */
r_if
c_cond
(paren
id|event
op_ne
id|NETDEV_DOWN
op_logical_and
id|dst-&gt;output
op_eq
id|dst_blackhole
)paren
(brace
id|dst-&gt;dev
op_assign
op_amp
id|loopback_dev
suffix:semicolon
id|dev_put
c_func
(paren
id|dev
)paren
suffix:semicolon
id|dev_hold
c_func
(paren
op_amp
id|loopback_dev
)paren
suffix:semicolon
id|dst-&gt;output
op_assign
id|dst_discard
suffix:semicolon
r_if
c_cond
(paren
id|dst-&gt;neighbour
op_logical_and
id|dst-&gt;neighbour-&gt;dev
op_eq
id|dev
)paren
(brace
id|dst-&gt;neighbour-&gt;dev
op_assign
op_amp
id|loopback_dev
suffix:semicolon
id|dev_put
c_func
(paren
id|dev
)paren
suffix:semicolon
id|dev_hold
c_func
(paren
op_amp
id|loopback_dev
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
id|dst-&gt;input
op_assign
id|dst_discard
suffix:semicolon
id|dst-&gt;output
op_assign
id|dst_blackhole
suffix:semicolon
)brace
)brace
)brace
id|spin_unlock_bh
c_func
(paren
op_amp
id|dst_lock
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
id|NOTIFY_DONE
suffix:semicolon
)brace
DECL|variable|dst_dev_notifier
r_struct
id|notifier_block
id|dst_dev_notifier
op_assign
(brace
dot
id|notifier_call
op_assign
id|dst_dev_event
comma
)brace
suffix:semicolon
DECL|function|dst_init
r_void
id|__init
id|dst_init
c_func
(paren
r_void
)paren
(brace
id|register_netdevice_notifier
c_func
(paren
op_amp
id|dst_dev_notifier
)paren
suffix:semicolon
)brace
eof
