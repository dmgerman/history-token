multiline_comment|/*&n; *&t;&t;INETPEER - A storage for permanent information about peers&n; *&n; *  This source is covered by the GNU GPL, the same as all kernel sources.&n; *&n; *  Version:&t;$Id: inetpeer.c,v 1.6 2001/06/21 20:30:14 davem Exp $&n; *&n; *  Authors:&t;Andrey V. Savochkin &lt;saw@msu.ru&gt;&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/random.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;net/inetpeer.h&gt;
multiline_comment|/*&n; *  Theory of operations.&n; *  We keep one entry for each peer IP address.  The nodes contains long-living&n; *  information about the peer which doesn&squot;t depend on routes.&n; *  At this moment this information consists only of ID field for the next&n; *  outgoing IP packet.  This field is incremented with each packet as encoded&n; *  in inet_getid() function (include/net/inetpeer.h).&n; *  At the moment of writing this notes identifier of IP packets is generated&n; *  to be unpredictable using this code only for packets subjected&n; *  (actually or potentially) to defragmentation.  I.e. DF packets less than&n; *  PMTU in size uses a constant ID and do not use this code (see&n; *  ip_select_ident() in include/net/ip.h).&n; *&n; *  Route cache entries hold references to our nodes.&n; *  New cache entries get references via lookup by destination IP address in&n; *  the avl tree.  The reference is grabbed only when it&squot;s needed i.e. only&n; *  when we try to output IP packet which needs an unpredictable ID (see&n; *  __ip_select_ident() in net/ipv4/route.c).&n; *  Nodes are removed only when reference counter goes to 0.&n; *  When it&squot;s happened the node may be removed when a sufficient amount of&n; *  time has been passed since its last use.  The less-recently-used entry can&n; *  also be removed if the pool is overloaded i.e. if the total amount of&n; *  entries is greater-or-equal than the threshold.&n; *&n; *  Node pool is organised as an AVL tree.&n; *  Such an implementation has been chosen not just for fun.  It&squot;s a way to&n; *  prevent easy and efficient DoS attacks by creating hash collisions.  A huge&n; *  amount of long living nodes in a single hash slot would significantly delay&n; *  lookups performed with disabled BHs.&n; *&n; *  Serialisation issues.&n; *  1.  Nodes may appear in the tree only with the pool write lock held.&n; *  2.  Nodes may disappear from the tree only with the pool write lock held&n; *      AND reference count being 0.&n; *  3.  Nodes appears and disappears from unused node list only under&n; *      &quot;inet_peer_unused_lock&quot;.&n; *  4.  Global variable peer_total is modified under the pool lock.&n; *  5.  struct inet_peer fields modification:&n; *&t;&t;avl_left, avl_right, avl_parent, avl_height: pool lock&n; *&t;&t;unused_next, unused_prevp: unused node list lock&n; *&t;&t;refcnt: atomically against modifications on other CPU;&n; *&t;&t;   usually under some other lock to prevent node disappearing&n; *&t;&t;dtime: unused node list lock&n; *&t;&t;v4daddr: unchangeable&n; *&t;&t;ip_id_count: idlock&n; */
DECL|variable|inet_peer_idlock
id|spinlock_t
id|inet_peer_idlock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|variable|peer_cachep
r_static
id|kmem_cache_t
op_star
id|peer_cachep
suffix:semicolon
DECL|macro|node_height
mdefine_line|#define node_height(x) x-&gt;avl_height
DECL|variable|peer_fake_node
r_static
r_struct
id|inet_peer
id|peer_fake_node
op_assign
(brace
id|avl_left
suffix:colon
op_amp
id|peer_fake_node
comma
id|avl_right
suffix:colon
op_amp
id|peer_fake_node
comma
id|avl_height
suffix:colon
l_int|0
)brace
suffix:semicolon
DECL|macro|peer_avl_empty
mdefine_line|#define peer_avl_empty (&amp;peer_fake_node)
DECL|variable|peer_root
r_static
r_struct
id|inet_peer
op_star
id|peer_root
op_assign
id|peer_avl_empty
suffix:semicolon
DECL|variable|peer_pool_lock
r_static
id|rwlock_t
id|peer_pool_lock
op_assign
id|RW_LOCK_UNLOCKED
suffix:semicolon
DECL|macro|PEER_MAXDEPTH
mdefine_line|#define PEER_MAXDEPTH 40 /* sufficient for about 2^27 nodes */
DECL|variable|peer_total
r_static
r_volatile
r_int
id|peer_total
suffix:semicolon
DECL|variable|inet_peer_threshold
r_int
id|inet_peer_threshold
op_assign
l_int|65536
op_plus
l_int|128
suffix:semicolon
multiline_comment|/* start to throw entries more&n;&t;&t;&t;&t;&t; * aggressively at this stage */
DECL|variable|inet_peer_minttl
r_int
id|inet_peer_minttl
op_assign
l_int|120
op_star
id|HZ
suffix:semicolon
multiline_comment|/* TTL under high load: 120 sec */
DECL|variable|inet_peer_maxttl
r_int
id|inet_peer_maxttl
op_assign
l_int|10
op_star
l_int|60
op_star
id|HZ
suffix:semicolon
multiline_comment|/* usual time to live: 10 min */
DECL|variable|inet_peer_unused_head
r_struct
id|inet_peer
op_star
id|inet_peer_unused_head
comma
DECL|variable|inet_peer_unused_tailp
op_star
op_star
id|inet_peer_unused_tailp
op_assign
op_amp
id|inet_peer_unused_head
suffix:semicolon
DECL|variable|inet_peer_unused_lock
id|spinlock_t
id|inet_peer_unused_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|macro|PEER_MAX_CLEANUP_WORK
mdefine_line|#define PEER_MAX_CLEANUP_WORK 30
r_static
r_void
id|peer_check_expire
c_func
(paren
r_int
r_int
id|dummy
)paren
suffix:semicolon
DECL|variable|peer_periodic_timer
r_static
r_struct
id|timer_list
id|peer_periodic_timer
op_assign
(brace
(brace
l_int|NULL
comma
l_int|NULL
)brace
comma
l_int|0
comma
l_int|0
comma
op_amp
id|peer_check_expire
)brace
suffix:semicolon
DECL|variable|inet_peer_gc_mintime
r_int
id|inet_peer_gc_mintime
op_assign
l_int|10
op_star
id|HZ
comma
DECL|variable|inet_peer_gc_maxtime
id|inet_peer_gc_maxtime
op_assign
l_int|120
op_star
id|HZ
suffix:semicolon
DECL|function|inet_initpeers
r_void
id|__init
id|inet_initpeers
c_func
(paren
r_void
)paren
(brace
r_struct
id|sysinfo
id|si
suffix:semicolon
multiline_comment|/* Use the straight interface to information about memory. */
id|si_meminfo
c_func
(paren
op_amp
id|si
)paren
suffix:semicolon
multiline_comment|/* The values below were suggested by Alexey Kuznetsov&n;&t; * &lt;kuznet@ms2.inr.ac.ru&gt;.  I don&squot;t have any opinion about the values&n;&t; * myself.  --SAW&n;&t; */
r_if
c_cond
(paren
id|si.totalram
op_le
(paren
l_int|32768
op_star
l_int|1024
)paren
op_div
id|PAGE_SIZE
)paren
id|inet_peer_threshold
op_rshift_assign
l_int|1
suffix:semicolon
multiline_comment|/* max pool size about 1MB on IA32 */
r_if
c_cond
(paren
id|si.totalram
op_le
(paren
l_int|16384
op_star
l_int|1024
)paren
op_div
id|PAGE_SIZE
)paren
id|inet_peer_threshold
op_rshift_assign
l_int|1
suffix:semicolon
multiline_comment|/* about 512KB */
r_if
c_cond
(paren
id|si.totalram
op_le
(paren
l_int|8192
op_star
l_int|1024
)paren
op_div
id|PAGE_SIZE
)paren
id|inet_peer_threshold
op_rshift_assign
l_int|2
suffix:semicolon
multiline_comment|/* about 128KB */
id|peer_cachep
op_assign
id|kmem_cache_create
c_func
(paren
l_string|&quot;inet_peer_cache&quot;
comma
r_sizeof
(paren
r_struct
id|inet_peer
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
multiline_comment|/* All the timers, started at system startup tend&n;&t;   to synchronize. Perturb it a bit.&n;&t; */
id|peer_periodic_timer.expires
op_assign
id|jiffies
op_plus
id|net_random
c_func
(paren
)paren
op_mod
id|inet_peer_gc_maxtime
op_plus
id|inet_peer_gc_maxtime
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|peer_periodic_timer
)paren
suffix:semicolon
)brace
multiline_comment|/* Called with or without local BH being disabled. */
DECL|function|unlink_from_unused
r_static
r_void
id|unlink_from_unused
c_func
(paren
r_struct
id|inet_peer
op_star
id|p
)paren
(brace
id|spin_lock_bh
c_func
(paren
op_amp
id|inet_peer_unused_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;unused_prevp
op_ne
l_int|NULL
)paren
(brace
multiline_comment|/* On unused list. */
op_star
id|p-&gt;unused_prevp
op_assign
id|p-&gt;unused_next
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;unused_next
op_ne
l_int|NULL
)paren
id|p-&gt;unused_next-&gt;unused_prevp
op_assign
id|p-&gt;unused_prevp
suffix:semicolon
r_else
id|inet_peer_unused_tailp
op_assign
id|p-&gt;unused_prevp
suffix:semicolon
id|p-&gt;unused_prevp
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* mark it as removed */
)brace
id|spin_unlock_bh
c_func
(paren
op_amp
id|inet_peer_unused_lock
)paren
suffix:semicolon
)brace
multiline_comment|/* Called with local BH disabled and the pool lock held. */
DECL|macro|lookup
mdefine_line|#define lookup(daddr) &t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;struct inet_peer *u, **v;&t;&t;&t;&t;&bslash;&n;&t;stackptr = stack;&t;&t;&t;&t;&t;&bslash;&n;&t;*stackptr++ = &amp;peer_root;&t;&t;&t;&t;&bslash;&n;&t;for (u = peer_root; u != peer_avl_empty; ) {&t;&t;&bslash;&n;&t;&t;if (daddr == u-&gt;v4daddr)&t;&t;&t;&bslash;&n;&t;&t;&t;break;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;if (daddr &lt; u-&gt;v4daddr)&t;&t;&t;&t;&bslash;&n;&t;&t;&t;v = &amp;u-&gt;avl_left;&t;&t;&t;&bslash;&n;&t;&t;else&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;v = &amp;u-&gt;avl_right;&t;&t;&t;&bslash;&n;&t;&t;*stackptr++ = v;&t;&t;&t;&t;&bslash;&n;&t;&t;u = *v;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;u;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
multiline_comment|/* Called with local BH disabled and the pool write lock held. */
DECL|macro|lookup_rightempty
mdefine_line|#define lookup_rightempty(start)&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;struct inet_peer *u, **v;&t;&t;&t;&t;&bslash;&n;&t;*stackptr++ = &amp;start-&gt;avl_left;&t;&t;&t;&t;&bslash;&n;&t;v = &amp;start-&gt;avl_left;&t;&t;&t;&t;&t;&bslash;&n;&t;for (u = *v; u-&gt;avl_right != peer_avl_empty; ) {&t;&bslash;&n;&t;&t;v = &amp;u-&gt;avl_right;&t;&t;&t;&t;&bslash;&n;&t;&t;*stackptr++ = v;&t;&t;&t;&t;&bslash;&n;&t;&t;u = *v;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;u;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
multiline_comment|/* Called with local BH disabled and the pool write lock held.&n; * Variable names are the proof of operation correctness.&n; * Look into mm/map_avl.c for more detail description of the ideas.  */
DECL|function|peer_avl_rebalance
r_static
r_void
id|peer_avl_rebalance
c_func
(paren
r_struct
id|inet_peer
op_star
op_star
id|stack
(braket
)braket
comma
r_struct
id|inet_peer
op_star
op_star
op_star
id|stackend
)paren
(brace
r_struct
id|inet_peer
op_star
op_star
id|nodep
comma
op_star
id|node
comma
op_star
id|l
comma
op_star
id|r
suffix:semicolon
r_int
id|lh
comma
id|rh
suffix:semicolon
r_while
c_loop
(paren
id|stackend
OG
id|stack
)paren
(brace
id|nodep
op_assign
op_star
op_decrement
id|stackend
suffix:semicolon
id|node
op_assign
op_star
id|nodep
suffix:semicolon
id|l
op_assign
id|node-&gt;avl_left
suffix:semicolon
id|r
op_assign
id|node-&gt;avl_right
suffix:semicolon
id|lh
op_assign
id|node_height
c_func
(paren
id|l
)paren
suffix:semicolon
id|rh
op_assign
id|node_height
c_func
(paren
id|r
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lh
OG
id|rh
op_plus
l_int|1
)paren
(brace
multiline_comment|/* l: RH+2 */
r_struct
id|inet_peer
op_star
id|ll
comma
op_star
id|lr
comma
op_star
id|lrl
comma
op_star
id|lrr
suffix:semicolon
r_int
id|lrh
suffix:semicolon
id|ll
op_assign
id|l-&gt;avl_left
suffix:semicolon
id|lr
op_assign
id|l-&gt;avl_right
suffix:semicolon
id|lrh
op_assign
id|node_height
c_func
(paren
id|lr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lrh
op_le
id|node_height
c_func
(paren
id|ll
)paren
)paren
(brace
multiline_comment|/* ll: RH+1 */
id|node-&gt;avl_left
op_assign
id|lr
suffix:semicolon
multiline_comment|/* lr: RH or RH+1 */
id|node-&gt;avl_right
op_assign
id|r
suffix:semicolon
multiline_comment|/* r: RH */
id|node-&gt;avl_height
op_assign
id|lrh
op_plus
l_int|1
suffix:semicolon
multiline_comment|/* RH+1 or RH+2 */
id|l-&gt;avl_left
op_assign
id|ll
suffix:semicolon
multiline_comment|/* ll: RH+1 */
id|l-&gt;avl_right
op_assign
id|node
suffix:semicolon
multiline_comment|/* node: RH+1 or RH+2 */
id|l-&gt;avl_height
op_assign
id|node-&gt;avl_height
op_plus
l_int|1
suffix:semicolon
op_star
id|nodep
op_assign
id|l
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* ll: RH, lr: RH+1 */
id|lrl
op_assign
id|lr-&gt;avl_left
suffix:semicolon
multiline_comment|/* lrl: RH or RH-1 */
id|lrr
op_assign
id|lr-&gt;avl_right
suffix:semicolon
multiline_comment|/* lrr: RH or RH-1 */
id|node-&gt;avl_left
op_assign
id|lrr
suffix:semicolon
multiline_comment|/* lrr: RH or RH-1 */
id|node-&gt;avl_right
op_assign
id|r
suffix:semicolon
multiline_comment|/* r: RH */
id|node-&gt;avl_height
op_assign
id|rh
op_plus
l_int|1
suffix:semicolon
multiline_comment|/* node: RH+1 */
id|l-&gt;avl_left
op_assign
id|ll
suffix:semicolon
multiline_comment|/* ll: RH */
id|l-&gt;avl_right
op_assign
id|lrl
suffix:semicolon
multiline_comment|/* lrl: RH or RH-1 */
id|l-&gt;avl_height
op_assign
id|rh
op_plus
l_int|1
suffix:semicolon
multiline_comment|/* l: RH+1 */
id|lr-&gt;avl_left
op_assign
id|l
suffix:semicolon
multiline_comment|/* l: RH+1 */
id|lr-&gt;avl_right
op_assign
id|node
suffix:semicolon
multiline_comment|/* node: RH+1 */
id|lr-&gt;avl_height
op_assign
id|rh
op_plus
l_int|2
suffix:semicolon
op_star
id|nodep
op_assign
id|lr
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|rh
OG
id|lh
op_plus
l_int|1
)paren
(brace
multiline_comment|/* r: LH+2 */
r_struct
id|inet_peer
op_star
id|rr
comma
op_star
id|rl
comma
op_star
id|rlr
comma
op_star
id|rll
suffix:semicolon
r_int
id|rlh
suffix:semicolon
id|rr
op_assign
id|r-&gt;avl_right
suffix:semicolon
id|rl
op_assign
id|r-&gt;avl_left
suffix:semicolon
id|rlh
op_assign
id|node_height
c_func
(paren
id|rl
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rlh
op_le
id|node_height
c_func
(paren
id|rr
)paren
)paren
(brace
multiline_comment|/* rr: LH+1 */
id|node-&gt;avl_right
op_assign
id|rl
suffix:semicolon
multiline_comment|/* rl: LH or LH+1 */
id|node-&gt;avl_left
op_assign
id|l
suffix:semicolon
multiline_comment|/* l: LH */
id|node-&gt;avl_height
op_assign
id|rlh
op_plus
l_int|1
suffix:semicolon
multiline_comment|/* LH+1 or LH+2 */
id|r-&gt;avl_right
op_assign
id|rr
suffix:semicolon
multiline_comment|/* rr: LH+1 */
id|r-&gt;avl_left
op_assign
id|node
suffix:semicolon
multiline_comment|/* node: LH+1 or LH+2 */
id|r-&gt;avl_height
op_assign
id|node-&gt;avl_height
op_plus
l_int|1
suffix:semicolon
op_star
id|nodep
op_assign
id|r
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* rr: RH, rl: RH+1 */
id|rlr
op_assign
id|rl-&gt;avl_right
suffix:semicolon
multiline_comment|/* rlr: LH or LH-1 */
id|rll
op_assign
id|rl-&gt;avl_left
suffix:semicolon
multiline_comment|/* rll: LH or LH-1 */
id|node-&gt;avl_right
op_assign
id|rll
suffix:semicolon
multiline_comment|/* rll: LH or LH-1 */
id|node-&gt;avl_left
op_assign
id|l
suffix:semicolon
multiline_comment|/* l: LH */
id|node-&gt;avl_height
op_assign
id|lh
op_plus
l_int|1
suffix:semicolon
multiline_comment|/* node: LH+1 */
id|r-&gt;avl_right
op_assign
id|rr
suffix:semicolon
multiline_comment|/* rr: LH */
id|r-&gt;avl_left
op_assign
id|rlr
suffix:semicolon
multiline_comment|/* rlr: LH or LH-1 */
id|r-&gt;avl_height
op_assign
id|lh
op_plus
l_int|1
suffix:semicolon
multiline_comment|/* r: LH+1 */
id|rl-&gt;avl_right
op_assign
id|r
suffix:semicolon
multiline_comment|/* r: LH+1 */
id|rl-&gt;avl_left
op_assign
id|node
suffix:semicolon
multiline_comment|/* node: LH+1 */
id|rl-&gt;avl_height
op_assign
id|lh
op_plus
l_int|2
suffix:semicolon
op_star
id|nodep
op_assign
id|rl
suffix:semicolon
)brace
)brace
r_else
(brace
id|node-&gt;avl_height
op_assign
(paren
id|lh
OG
id|rh
ques
c_cond
id|lh
suffix:colon
id|rh
)paren
op_plus
l_int|1
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/* Called with local BH disabled and the pool write lock held. */
DECL|macro|link_to_pool
mdefine_line|#define link_to_pool(n)&t;&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;n-&gt;avl_height = 1;&t;&t;&t;&t;&t;&bslash;&n;&t;n-&gt;avl_left = peer_avl_empty;&t;&t;&t;&t;&bslash;&n;&t;n-&gt;avl_right = peer_avl_empty;&t;&t;&t;&t;&bslash;&n;&t;**--stackptr = n;&t;&t;&t;&t;&t;&bslash;&n;&t;peer_avl_rebalance(stack, stackptr);&t;&t;&t;&bslash;&n;} while(0)
multiline_comment|/* May be called with local BH enabled. */
DECL|function|unlink_from_pool
r_static
r_void
id|unlink_from_pool
c_func
(paren
r_struct
id|inet_peer
op_star
id|p
)paren
(brace
r_int
id|do_free
suffix:semicolon
id|do_free
op_assign
l_int|0
suffix:semicolon
id|write_lock_bh
c_func
(paren
op_amp
id|peer_pool_lock
)paren
suffix:semicolon
multiline_comment|/* Check the reference counter.  It was artificially incremented by 1&n;&t; * in cleanup() function to prevent sudden disappearing.  If the&n;&t; * reference count is still 1 then the node is referenced only as `p&squot;&n;&t; * here and from the pool.  So under the exclusive pool lock it&squot;s safe&n;&t; * to remove the node and free it later. */
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|p-&gt;refcnt
)paren
op_eq
l_int|1
)paren
(brace
r_struct
id|inet_peer
op_star
op_star
id|stack
(braket
id|PEER_MAXDEPTH
)braket
suffix:semicolon
r_struct
id|inet_peer
op_star
op_star
op_star
id|stackptr
comma
op_star
op_star
op_star
id|delp
suffix:semicolon
r_if
c_cond
(paren
id|lookup
c_func
(paren
id|p-&gt;v4daddr
)paren
op_ne
id|p
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|delp
op_assign
id|stackptr
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* *delp[0] == p */
r_if
c_cond
(paren
id|p-&gt;avl_left
op_eq
id|peer_avl_empty
)paren
(brace
op_star
id|delp
(braket
l_int|0
)braket
op_assign
id|p-&gt;avl_right
suffix:semicolon
op_decrement
id|stackptr
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* look for a node to insert instead of p */
r_struct
id|inet_peer
op_star
id|t
suffix:semicolon
id|t
op_assign
id|lookup_rightempty
c_func
(paren
id|p
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|stackptr
(braket
op_minus
l_int|1
)braket
op_ne
id|t
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
op_star
op_star
op_decrement
id|stackptr
op_assign
id|t-&gt;avl_left
suffix:semicolon
multiline_comment|/* t is removed, t-&gt;v4daddr &gt; x-&gt;v4daddr for any&n;&t;&t;&t; * x in p-&gt;avl_left subtree.&n;&t;&t;&t; * Put t in the old place of p. */
op_star
id|delp
(braket
l_int|0
)braket
op_assign
id|t
suffix:semicolon
id|t-&gt;avl_left
op_assign
id|p-&gt;avl_left
suffix:semicolon
id|t-&gt;avl_right
op_assign
id|p-&gt;avl_right
suffix:semicolon
id|t-&gt;avl_height
op_assign
id|p-&gt;avl_height
suffix:semicolon
r_if
c_cond
(paren
id|delp
(braket
l_int|1
)braket
op_ne
op_amp
id|p-&gt;avl_left
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|delp
(braket
l_int|1
)braket
op_assign
op_amp
id|t-&gt;avl_left
suffix:semicolon
multiline_comment|/* was &amp;p-&gt;avl_left */
)brace
id|peer_avl_rebalance
c_func
(paren
id|stack
comma
id|stackptr
)paren
suffix:semicolon
id|peer_total
op_decrement
suffix:semicolon
id|do_free
op_assign
l_int|1
suffix:semicolon
)brace
id|write_unlock_bh
c_func
(paren
op_amp
id|peer_pool_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|do_free
)paren
id|kmem_cache_free
c_func
(paren
id|peer_cachep
comma
id|p
)paren
suffix:semicolon
r_else
multiline_comment|/* The node is used again.  Decrease the reference counter&n;&t;&t; * back.  The loop &quot;cleanup -&gt; unlink_from_unused&n;&t;&t; *   -&gt; unlink_from_pool -&gt; putpeer -&gt; link_to_unused&n;&t;&t; *   -&gt; cleanup (for the same node)&quot;&n;&t;&t; * doesn&squot;t really exist because the entry will have a&n;&t;&t; * recent deletion time and will not be cleaned again soon. */
id|inet_putpeer
c_func
(paren
id|p
)paren
suffix:semicolon
)brace
multiline_comment|/* May be called with local BH enabled. */
DECL|function|cleanup_once
r_static
r_int
id|cleanup_once
c_func
(paren
r_int
r_int
id|ttl
)paren
(brace
r_struct
id|inet_peer
op_star
id|p
suffix:semicolon
multiline_comment|/* Remove the first entry from the list of unused nodes. */
id|spin_lock_bh
c_func
(paren
op_amp
id|inet_peer_unused_lock
)paren
suffix:semicolon
id|p
op_assign
id|inet_peer_unused_head
suffix:semicolon
r_if
c_cond
(paren
id|p
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
id|time_after
c_func
(paren
id|p-&gt;dtime
op_plus
id|ttl
comma
id|jiffies
)paren
)paren
(brace
multiline_comment|/* Do not prune fresh entries. */
id|spin_unlock_bh
c_func
(paren
op_amp
id|inet_peer_unused_lock
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|inet_peer_unused_head
op_assign
id|p-&gt;unused_next
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;unused_next
op_ne
l_int|NULL
)paren
id|p-&gt;unused_next-&gt;unused_prevp
op_assign
id|p-&gt;unused_prevp
suffix:semicolon
r_else
id|inet_peer_unused_tailp
op_assign
id|p-&gt;unused_prevp
suffix:semicolon
id|p-&gt;unused_prevp
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* mark as not on the list */
multiline_comment|/* Grab an extra reference to prevent node disappearing&n;&t;&t; * before unlink_from_pool() call. */
id|atomic_inc
c_func
(paren
op_amp
id|p-&gt;refcnt
)paren
suffix:semicolon
)brace
id|spin_unlock_bh
c_func
(paren
op_amp
id|inet_peer_unused_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p
op_eq
l_int|NULL
)paren
multiline_comment|/* It means that the total number of USED entries has&n;&t;&t; * grown over inet_peer_threshold.  It shouldn&squot;t really&n;&t;&t; * happen because of entry limits in route cache. */
r_return
op_minus
l_int|1
suffix:semicolon
id|unlink_from_pool
c_func
(paren
id|p
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Called with or without local BH being disabled. */
DECL|function|inet_getpeer
r_struct
id|inet_peer
op_star
id|inet_getpeer
c_func
(paren
id|__u32
id|daddr
comma
r_int
id|create
)paren
(brace
r_struct
id|inet_peer
op_star
id|p
comma
op_star
id|n
suffix:semicolon
r_struct
id|inet_peer
op_star
op_star
id|stack
(braket
id|PEER_MAXDEPTH
)braket
comma
op_star
op_star
op_star
id|stackptr
suffix:semicolon
multiline_comment|/* Look up for the address quickly. */
id|read_lock_bh
c_func
(paren
op_amp
id|peer_pool_lock
)paren
suffix:semicolon
id|p
op_assign
id|lookup
c_func
(paren
id|daddr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p
op_ne
id|peer_avl_empty
)paren
id|atomic_inc
c_func
(paren
op_amp
id|p-&gt;refcnt
)paren
suffix:semicolon
id|read_unlock_bh
c_func
(paren
op_amp
id|peer_pool_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p
op_ne
id|peer_avl_empty
)paren
(brace
multiline_comment|/* The existing node has been found. */
multiline_comment|/* Remove the entry from unused list if it was there. */
id|unlink_from_unused
c_func
(paren
id|p
)paren
suffix:semicolon
r_return
id|p
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|create
)paren
r_return
l_int|NULL
suffix:semicolon
multiline_comment|/* Allocate the space outside the locked region. */
id|n
op_assign
id|kmem_cache_alloc
c_func
(paren
id|peer_cachep
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|n
op_eq
l_int|NULL
)paren
r_return
l_int|NULL
suffix:semicolon
id|n-&gt;v4daddr
op_assign
id|daddr
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|n-&gt;refcnt
comma
l_int|1
)paren
suffix:semicolon
id|n-&gt;ip_id_count
op_assign
id|secure_ip_id
c_func
(paren
id|daddr
)paren
suffix:semicolon
id|n-&gt;tcp_ts_stamp
op_assign
l_int|0
suffix:semicolon
id|write_lock_bh
c_func
(paren
op_amp
id|peer_pool_lock
)paren
suffix:semicolon
multiline_comment|/* Check if an entry has suddenly appeared. */
id|p
op_assign
id|lookup
c_func
(paren
id|daddr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p
op_ne
id|peer_avl_empty
)paren
r_goto
id|out_free
suffix:semicolon
multiline_comment|/* Link the node. */
id|link_to_pool
c_func
(paren
id|n
)paren
suffix:semicolon
id|n-&gt;unused_prevp
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* not on the list */
id|peer_total
op_increment
suffix:semicolon
id|write_unlock_bh
c_func
(paren
op_amp
id|peer_pool_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|peer_total
op_ge
id|inet_peer_threshold
)paren
multiline_comment|/* Remove one less-recently-used entry. */
id|cleanup_once
c_func
(paren
l_int|0
)paren
suffix:semicolon
r_return
id|n
suffix:semicolon
id|out_free
suffix:colon
multiline_comment|/* The appropriate node is already in the pool. */
id|atomic_inc
c_func
(paren
op_amp
id|p-&gt;refcnt
)paren
suffix:semicolon
id|write_unlock_bh
c_func
(paren
op_amp
id|peer_pool_lock
)paren
suffix:semicolon
multiline_comment|/* Remove the entry from unused list if it was there. */
id|unlink_from_unused
c_func
(paren
id|p
)paren
suffix:semicolon
multiline_comment|/* Free preallocated the preallocated node. */
id|kmem_cache_free
c_func
(paren
id|peer_cachep
comma
id|n
)paren
suffix:semicolon
r_return
id|p
suffix:semicolon
)brace
multiline_comment|/* Called with local BH disabled. */
DECL|function|peer_check_expire
r_static
r_void
id|peer_check_expire
c_func
(paren
r_int
r_int
id|dummy
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
id|ttl
suffix:semicolon
r_if
c_cond
(paren
id|peer_total
op_ge
id|inet_peer_threshold
)paren
id|ttl
op_assign
id|inet_peer_minttl
suffix:semicolon
r_else
id|ttl
op_assign
id|inet_peer_maxttl
op_minus
(paren
id|inet_peer_maxttl
op_minus
id|inet_peer_minttl
)paren
op_div
id|HZ
op_star
id|peer_total
op_div
id|inet_peer_threshold
op_star
id|HZ
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
id|PEER_MAX_CLEANUP_WORK
op_logical_and
op_logical_neg
id|cleanup_once
c_func
(paren
id|ttl
)paren
suffix:semicolon
id|i
op_increment
)paren
suffix:semicolon
multiline_comment|/* Trigger the timer after inet_peer_gc_mintime .. inet_peer_gc_maxtime&n;&t; * interval depending on the total number of entries (more entries,&n;&t; * less interval). */
id|peer_periodic_timer.expires
op_assign
id|jiffies
op_plus
id|inet_peer_gc_maxtime
op_minus
(paren
id|inet_peer_gc_maxtime
op_minus
id|inet_peer_gc_mintime
)paren
op_div
id|HZ
op_star
id|peer_total
op_div
id|inet_peer_threshold
op_star
id|HZ
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|peer_periodic_timer
)paren
suffix:semicolon
)brace
eof
