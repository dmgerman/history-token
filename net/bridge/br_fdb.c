multiline_comment|/*&n; *&t;Forwarding database&n; *&t;Linux ethernet bridge&n; *&n; *&t;Authors:&n; *&t;Lennert Buytenhek&t;&t;&lt;buytenh@gnu.org&gt;&n; *&n; *&t;$Id: br_fdb.c,v 1.6 2002/01/17 00:57:07 davem Exp $&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *&t;modify it under the terms of the GNU General Public License&n; *&t;as published by the Free Software Foundation; either version&n; *&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/if_bridge.h&gt;
macro_line|#include &lt;linux/times.h&gt;
macro_line|#include &lt;linux/etherdevice.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &quot;br_private.h&quot;
DECL|variable|br_fdb_cache
r_static
id|kmem_cache_t
op_star
id|br_fdb_cache
suffix:semicolon
DECL|function|br_fdb_init
r_void
id|__init
id|br_fdb_init
c_func
(paren
r_void
)paren
(brace
id|br_fdb_cache
op_assign
id|kmem_cache_create
c_func
(paren
l_string|&quot;bridge_fdb_cache&quot;
comma
r_sizeof
(paren
r_struct
id|net_bridge_fdb_entry
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
)brace
DECL|function|br_fdb_fini
r_void
id|__exit
id|br_fdb_fini
c_func
(paren
r_void
)paren
(brace
id|kmem_cache_destroy
c_func
(paren
id|br_fdb_cache
)paren
suffix:semicolon
)brace
multiline_comment|/* if topology_changing then use forward_delay (default 15 sec)&n; * otherwise keep longer (default 5 minutes)&n; */
DECL|function|hold_time
r_static
id|__inline__
r_int
r_int
id|hold_time
c_func
(paren
r_const
r_struct
id|net_bridge
op_star
id|br
)paren
(brace
r_return
id|br-&gt;topology_change
ques
c_cond
id|br-&gt;forward_delay
suffix:colon
id|br-&gt;ageing_time
suffix:semicolon
)brace
DECL|function|has_expired
r_static
id|__inline__
r_int
id|has_expired
c_func
(paren
r_const
r_struct
id|net_bridge
op_star
id|br
comma
r_const
r_struct
id|net_bridge_fdb_entry
op_star
id|fdb
)paren
(brace
r_return
op_logical_neg
id|fdb-&gt;is_static
op_logical_and
id|time_before_eq
c_func
(paren
id|fdb-&gt;ageing_timer
op_plus
id|hold_time
c_func
(paren
id|br
)paren
comma
id|jiffies
)paren
suffix:semicolon
)brace
DECL|function|copy_fdb
r_static
r_inline
r_void
id|copy_fdb
c_func
(paren
r_struct
id|__fdb_entry
op_star
id|ent
comma
r_const
r_struct
id|net_bridge_fdb_entry
op_star
id|f
)paren
(brace
id|memset
c_func
(paren
id|ent
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|__fdb_entry
)paren
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|ent-&gt;mac_addr
comma
id|f-&gt;addr.addr
comma
id|ETH_ALEN
)paren
suffix:semicolon
id|ent-&gt;port_no
op_assign
id|f-&gt;dst
ques
c_cond
id|f-&gt;dst-&gt;port_no
suffix:colon
l_int|0
suffix:semicolon
id|ent-&gt;is_local
op_assign
id|f-&gt;is_local
suffix:semicolon
id|ent-&gt;ageing_timer_value
op_assign
id|f-&gt;is_static
ques
c_cond
l_int|0
suffix:colon
id|jiffies_to_clock_t
c_func
(paren
id|jiffies
op_minus
id|f-&gt;ageing_timer
)paren
suffix:semicolon
)brace
DECL|function|br_mac_hash
r_static
id|__inline__
r_int
id|br_mac_hash
c_func
(paren
r_const
r_int
r_char
op_star
id|mac
)paren
(brace
r_int
r_int
id|x
suffix:semicolon
id|x
op_assign
id|mac
(braket
l_int|0
)braket
suffix:semicolon
id|x
op_assign
(paren
id|x
op_lshift
l_int|2
)paren
op_xor
id|mac
(braket
l_int|1
)braket
suffix:semicolon
id|x
op_assign
(paren
id|x
op_lshift
l_int|2
)paren
op_xor
id|mac
(braket
l_int|2
)braket
suffix:semicolon
id|x
op_assign
(paren
id|x
op_lshift
l_int|2
)paren
op_xor
id|mac
(braket
l_int|3
)braket
suffix:semicolon
id|x
op_assign
(paren
id|x
op_lshift
l_int|2
)paren
op_xor
id|mac
(braket
l_int|4
)braket
suffix:semicolon
id|x
op_assign
(paren
id|x
op_lshift
l_int|2
)paren
op_xor
id|mac
(braket
l_int|5
)braket
suffix:semicolon
id|x
op_xor_assign
id|x
op_rshift
l_int|8
suffix:semicolon
r_return
id|x
op_amp
(paren
id|BR_HASH_SIZE
op_minus
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|fdb_delete
r_static
id|__inline__
r_void
id|fdb_delete
c_func
(paren
r_struct
id|net_bridge_fdb_entry
op_star
id|f
)paren
(brace
id|hlist_del
c_func
(paren
op_amp
id|f-&gt;hlist
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|f-&gt;age_list
)paren
suffix:semicolon
id|br_fdb_put
c_func
(paren
id|f
)paren
suffix:semicolon
)brace
DECL|function|br_fdb_changeaddr
r_void
id|br_fdb_changeaddr
c_func
(paren
r_struct
id|net_bridge_port
op_star
id|p
comma
r_const
r_int
r_char
op_star
id|newaddr
)paren
(brace
r_struct
id|net_bridge
op_star
id|br
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
id|newhash
op_assign
id|br_mac_hash
c_func
(paren
id|newaddr
)paren
suffix:semicolon
id|br
op_assign
id|p-&gt;br
suffix:semicolon
id|write_lock_bh
c_func
(paren
op_amp
id|br-&gt;hash_lock
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
id|BR_HASH_SIZE
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|hlist_node
op_star
id|h
suffix:semicolon
id|hlist_for_each
c_func
(paren
id|h
comma
op_amp
id|br-&gt;hash
(braket
id|i
)braket
)paren
(brace
r_struct
id|net_bridge_fdb_entry
op_star
id|f
op_assign
id|hlist_entry
c_func
(paren
id|h
comma
r_struct
id|net_bridge_fdb_entry
comma
id|hlist
)paren
suffix:semicolon
r_if
c_cond
(paren
id|f-&gt;dst
op_eq
id|p
op_logical_and
id|f-&gt;is_local
)paren
(brace
id|memcpy
c_func
(paren
id|f-&gt;addr.addr
comma
id|newaddr
comma
id|ETH_ALEN
)paren
suffix:semicolon
r_if
c_cond
(paren
id|newhash
op_ne
id|i
)paren
(brace
id|hlist_del
c_func
(paren
op_amp
id|f-&gt;hlist
)paren
suffix:semicolon
id|hlist_add_head
c_func
(paren
op_amp
id|f-&gt;hlist
comma
op_amp
id|br-&gt;hash
(braket
id|newhash
)braket
)paren
suffix:semicolon
)brace
r_goto
id|out
suffix:semicolon
)brace
)brace
)brace
id|out
suffix:colon
id|write_unlock_bh
c_func
(paren
op_amp
id|br-&gt;hash_lock
)paren
suffix:semicolon
)brace
DECL|function|br_fdb_cleanup
r_void
id|br_fdb_cleanup
c_func
(paren
r_int
r_int
id|_data
)paren
(brace
r_struct
id|net_bridge
op_star
id|br
op_assign
(paren
r_struct
id|net_bridge
op_star
)paren
id|_data
suffix:semicolon
r_struct
id|list_head
op_star
id|l
comma
op_star
id|n
suffix:semicolon
r_int
r_int
id|delay
suffix:semicolon
id|write_lock_bh
c_func
(paren
op_amp
id|br-&gt;hash_lock
)paren
suffix:semicolon
id|delay
op_assign
id|hold_time
c_func
(paren
id|br
)paren
suffix:semicolon
id|list_for_each_safe
c_func
(paren
id|l
comma
id|n
comma
op_amp
id|br-&gt;age_list
)paren
(brace
r_struct
id|net_bridge_fdb_entry
op_star
id|f
op_assign
id|list_entry
c_func
(paren
id|l
comma
r_struct
id|net_bridge_fdb_entry
comma
id|age_list
)paren
suffix:semicolon
r_int
r_int
id|expires
op_assign
id|f-&gt;ageing_timer
op_plus
id|delay
suffix:semicolon
r_if
c_cond
(paren
id|time_before_eq
c_func
(paren
id|expires
comma
id|jiffies
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|f-&gt;is_static
)paren
(brace
id|pr_debug
c_func
(paren
l_string|&quot;expire age %lu jiffies %lu&bslash;n&quot;
comma
id|f-&gt;ageing_timer
comma
id|jiffies
)paren
suffix:semicolon
id|fdb_delete
c_func
(paren
id|f
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
id|mod_timer
c_func
(paren
op_amp
id|br-&gt;gc_timer
comma
id|expires
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|write_unlock_bh
c_func
(paren
op_amp
id|br-&gt;hash_lock
)paren
suffix:semicolon
)brace
DECL|function|br_fdb_delete_by_port
r_void
id|br_fdb_delete_by_port
c_func
(paren
r_struct
id|net_bridge
op_star
id|br
comma
r_struct
id|net_bridge_port
op_star
id|p
)paren
(brace
r_int
id|i
suffix:semicolon
id|write_lock_bh
c_func
(paren
op_amp
id|br-&gt;hash_lock
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
id|BR_HASH_SIZE
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|hlist_node
op_star
id|h
comma
op_star
id|g
suffix:semicolon
id|hlist_for_each_safe
c_func
(paren
id|h
comma
id|g
comma
op_amp
id|br-&gt;hash
(braket
id|i
)braket
)paren
(brace
r_struct
id|net_bridge_fdb_entry
op_star
id|f
op_assign
id|hlist_entry
c_func
(paren
id|h
comma
r_struct
id|net_bridge_fdb_entry
comma
id|hlist
)paren
suffix:semicolon
r_if
c_cond
(paren
id|f-&gt;dst
op_eq
id|p
)paren
(brace
id|fdb_delete
c_func
(paren
id|f
)paren
suffix:semicolon
)brace
)brace
)brace
id|write_unlock_bh
c_func
(paren
op_amp
id|br-&gt;hash_lock
)paren
suffix:semicolon
)brace
DECL|function|br_fdb_get
r_struct
id|net_bridge_fdb_entry
op_star
id|br_fdb_get
c_func
(paren
r_struct
id|net_bridge
op_star
id|br
comma
r_int
r_char
op_star
id|addr
)paren
(brace
r_struct
id|hlist_node
op_star
id|h
suffix:semicolon
id|read_lock_bh
c_func
(paren
op_amp
id|br-&gt;hash_lock
)paren
suffix:semicolon
id|hlist_for_each
c_func
(paren
id|h
comma
op_amp
id|br-&gt;hash
(braket
id|br_mac_hash
c_func
(paren
id|addr
)paren
)braket
)paren
(brace
r_struct
id|net_bridge_fdb_entry
op_star
id|fdb
op_assign
id|hlist_entry
c_func
(paren
id|h
comma
r_struct
id|net_bridge_fdb_entry
comma
id|hlist
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|memcmp
c_func
(paren
id|fdb-&gt;addr.addr
comma
id|addr
comma
id|ETH_ALEN
)paren
)paren
(brace
r_if
c_cond
(paren
id|has_expired
c_func
(paren
id|br
comma
id|fdb
)paren
)paren
r_goto
id|ret_null
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|fdb-&gt;use_count
)paren
suffix:semicolon
id|read_unlock_bh
c_func
(paren
op_amp
id|br-&gt;hash_lock
)paren
suffix:semicolon
r_return
id|fdb
suffix:semicolon
)brace
)brace
id|ret_null
suffix:colon
id|read_unlock_bh
c_func
(paren
op_amp
id|br-&gt;hash_lock
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|br_fdb_put
r_void
id|br_fdb_put
c_func
(paren
r_struct
id|net_bridge_fdb_entry
op_star
id|ent
)paren
(brace
r_if
c_cond
(paren
id|atomic_dec_and_test
c_func
(paren
op_amp
id|ent-&gt;use_count
)paren
)paren
id|kmem_cache_free
c_func
(paren
id|br_fdb_cache
comma
id|ent
)paren
suffix:semicolon
)brace
DECL|function|br_fdb_get_entries
r_int
id|br_fdb_get_entries
c_func
(paren
r_struct
id|net_bridge
op_star
id|br
comma
r_int
r_char
op_star
id|_buf
comma
r_int
id|maxnum
comma
r_int
id|offset
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
id|num
suffix:semicolon
r_struct
id|__fdb_entry
op_star
id|walk
suffix:semicolon
id|num
op_assign
l_int|0
suffix:semicolon
id|walk
op_assign
(paren
r_struct
id|__fdb_entry
op_star
)paren
id|_buf
suffix:semicolon
id|read_lock_bh
c_func
(paren
op_amp
id|br-&gt;hash_lock
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
id|BR_HASH_SIZE
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|hlist_node
op_star
id|h
suffix:semicolon
id|hlist_for_each
c_func
(paren
id|h
comma
op_amp
id|br-&gt;hash
(braket
id|i
)braket
)paren
(brace
r_struct
id|net_bridge_fdb_entry
op_star
id|f
op_assign
id|hlist_entry
c_func
(paren
id|h
comma
r_struct
id|net_bridge_fdb_entry
comma
id|hlist
)paren
suffix:semicolon
r_struct
id|__fdb_entry
id|ent
suffix:semicolon
r_if
c_cond
(paren
id|num
op_ge
id|maxnum
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|has_expired
c_func
(paren
id|br
comma
id|f
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|offset
)paren
(brace
id|offset
op_decrement
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|copy_fdb
c_func
(paren
op_amp
id|ent
comma
id|f
)paren
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|f-&gt;use_count
)paren
suffix:semicolon
id|read_unlock_bh
c_func
(paren
op_amp
id|br-&gt;hash_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|walk
comma
op_amp
id|ent
comma
r_sizeof
(paren
r_struct
id|__fdb_entry
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|read_lock_bh
c_func
(paren
op_amp
id|br-&gt;hash_lock
)paren
suffix:semicolon
multiline_comment|/* entry was deleted during copy_to_user */
r_if
c_cond
(paren
id|atomic_dec_and_test
c_func
(paren
op_amp
id|f-&gt;use_count
)paren
)paren
(brace
id|kmem_cache_free
c_func
(paren
id|br_fdb_cache
comma
id|f
)paren
suffix:semicolon
id|num
op_assign
op_minus
id|EAGAIN
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/* entry changed address hash while copying */
r_if
c_cond
(paren
id|br_mac_hash
c_func
(paren
id|f-&gt;addr.addr
)paren
op_ne
id|i
)paren
(brace
id|num
op_assign
op_minus
id|EAGAIN
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|num
op_increment
suffix:semicolon
id|walk
op_increment
suffix:semicolon
)brace
)brace
id|out
suffix:colon
id|read_unlock_bh
c_func
(paren
op_amp
id|br-&gt;hash_lock
)paren
suffix:semicolon
r_return
id|num
suffix:semicolon
)brace
DECL|function|br_fdb_insert
r_int
id|br_fdb_insert
c_func
(paren
r_struct
id|net_bridge
op_star
id|br
comma
r_struct
id|net_bridge_port
op_star
id|source
comma
r_const
r_int
r_char
op_star
id|addr
comma
r_int
id|is_local
)paren
(brace
r_struct
id|hlist_node
op_star
id|h
suffix:semicolon
r_struct
id|net_bridge_fdb_entry
op_star
id|fdb
suffix:semicolon
r_int
id|hash
op_assign
id|br_mac_hash
c_func
(paren
id|addr
)paren
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|is_valid_ether_addr
c_func
(paren
id|addr
)paren
)paren
r_return
op_minus
id|EADDRNOTAVAIL
suffix:semicolon
id|write_lock_bh
c_func
(paren
op_amp
id|br-&gt;hash_lock
)paren
suffix:semicolon
id|hlist_for_each
c_func
(paren
id|h
comma
op_amp
id|br-&gt;hash
(braket
id|hash
)braket
)paren
(brace
id|fdb
op_assign
id|hlist_entry
c_func
(paren
id|h
comma
r_struct
id|net_bridge_fdb_entry
comma
id|hlist
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|memcmp
c_func
(paren
id|fdb-&gt;addr.addr
comma
id|addr
comma
id|ETH_ALEN
)paren
)paren
(brace
multiline_comment|/* attempt to update an entry for a local interface */
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|fdb-&gt;is_local
)paren
)paren
(brace
r_if
c_cond
(paren
id|is_local
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: attempt to add&quot;
l_string|&quot; interface with same source address.&bslash;n&quot;
comma
id|source-&gt;dev-&gt;name
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|net_ratelimit
c_func
(paren
)paren
)paren
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s: received packet with &quot;
l_string|&quot; own address as source address&bslash;n&quot;
comma
id|source-&gt;dev-&gt;name
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|EEXIST
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|likely
c_func
(paren
op_logical_neg
id|fdb-&gt;is_static
op_logical_or
id|is_local
)paren
)paren
(brace
multiline_comment|/* move to end of age list */
id|list_del
c_func
(paren
op_amp
id|fdb-&gt;age_list
)paren
suffix:semicolon
r_goto
id|update
suffix:semicolon
)brace
r_goto
id|out
suffix:semicolon
)brace
)brace
id|fdb
op_assign
id|kmem_cache_alloc
c_func
(paren
id|br_fdb_cache
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|fdb
op_eq
l_int|NULL
)paren
)paren
(brace
id|ret
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|memcpy
c_func
(paren
id|fdb-&gt;addr.addr
comma
id|addr
comma
id|ETH_ALEN
)paren
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|fdb-&gt;use_count
comma
l_int|1
)paren
suffix:semicolon
id|hlist_add_head
c_func
(paren
op_amp
id|fdb-&gt;hlist
comma
op_amp
id|br-&gt;hash
(braket
id|hash
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|timer_pending
c_func
(paren
op_amp
id|br-&gt;gc_timer
)paren
)paren
(brace
id|br-&gt;gc_timer.expires
op_assign
id|jiffies
op_plus
id|hold_time
c_func
(paren
id|br
)paren
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|br-&gt;gc_timer
)paren
suffix:semicolon
)brace
id|update
suffix:colon
id|fdb-&gt;dst
op_assign
id|source
suffix:semicolon
id|fdb-&gt;is_local
op_assign
id|is_local
suffix:semicolon
id|fdb-&gt;is_static
op_assign
id|is_local
suffix:semicolon
id|fdb-&gt;ageing_timer
op_assign
id|jiffies
suffix:semicolon
id|list_add_tail
c_func
(paren
op_amp
id|fdb-&gt;age_list
comma
op_amp
id|br-&gt;age_list
)paren
suffix:semicolon
id|out
suffix:colon
id|write_unlock_bh
c_func
(paren
op_amp
id|br-&gt;hash_lock
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
eof
