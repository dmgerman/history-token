multiline_comment|/*&n; *&t;Forwarding database&n; *&t;Linux ethernet bridge&n; *&n; *&t;Authors:&n; *&t;Lennert Buytenhek&t;&t;&lt;buytenh@gnu.org&gt;&n; *&n; *&t;$Id: br_fdb.c,v 1.6 2002/01/17 00:57:07 davem Exp $&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *&t;modify it under the terms of the GNU General Public License&n; *&t;as published by the Free Software Foundation; either version&n; *&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/if_bridge.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &quot;br_private.h&quot;
DECL|function|__timeout
r_static
id|__inline__
r_int
r_int
id|__timeout
c_func
(paren
r_struct
id|net_bridge
op_star
id|br
)paren
(brace
r_int
r_int
id|timeout
suffix:semicolon
id|timeout
op_assign
id|jiffies
op_minus
id|br-&gt;ageing_time
suffix:semicolon
r_if
c_cond
(paren
id|br-&gt;topology_change
)paren
id|timeout
op_assign
id|jiffies
op_minus
id|br-&gt;forward_delay
suffix:semicolon
r_return
id|timeout
suffix:semicolon
)brace
DECL|function|has_expired
r_static
id|__inline__
r_int
id|has_expired
c_func
(paren
r_struct
id|net_bridge
op_star
id|br
comma
r_struct
id|net_bridge_fdb_entry
op_star
id|fdb
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|fdb-&gt;is_static
op_logical_and
id|time_before_eq
c_func
(paren
id|fdb-&gt;ageing_timer
comma
id|__timeout
c_func
(paren
id|br
)paren
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|copy_fdb
r_static
id|__inline__
r_void
id|copy_fdb
c_func
(paren
r_struct
id|__fdb_entry
op_star
id|ent
comma
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
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|f-&gt;is_static
)paren
id|ent-&gt;ageing_timer_value
op_assign
id|jiffies
op_minus
id|f-&gt;ageing_timer
suffix:semicolon
)brace
DECL|function|br_mac_hash
r_static
id|__inline__
r_int
id|br_mac_hash
c_func
(paren
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
DECL|function|__hash_link
r_static
id|__inline__
r_void
id|__hash_link
c_func
(paren
r_struct
id|net_bridge
op_star
id|br
comma
r_struct
id|net_bridge_fdb_entry
op_star
id|ent
comma
r_int
id|hash
)paren
(brace
id|ent-&gt;next_hash
op_assign
id|br-&gt;hash
(braket
id|hash
)braket
suffix:semicolon
r_if
c_cond
(paren
id|ent-&gt;next_hash
op_ne
l_int|NULL
)paren
id|ent-&gt;next_hash-&gt;pprev_hash
op_assign
op_amp
id|ent-&gt;next_hash
suffix:semicolon
id|br-&gt;hash
(braket
id|hash
)braket
op_assign
id|ent
suffix:semicolon
id|ent-&gt;pprev_hash
op_assign
op_amp
id|br-&gt;hash
(braket
id|hash
)braket
suffix:semicolon
)brace
DECL|function|__hash_unlink
r_static
id|__inline__
r_void
id|__hash_unlink
c_func
(paren
r_struct
id|net_bridge_fdb_entry
op_star
id|ent
)paren
(brace
op_star
(paren
id|ent-&gt;pprev_hash
)paren
op_assign
id|ent-&gt;next_hash
suffix:semicolon
r_if
c_cond
(paren
id|ent-&gt;next_hash
op_ne
l_int|NULL
)paren
id|ent-&gt;next_hash-&gt;pprev_hash
op_assign
id|ent-&gt;pprev_hash
suffix:semicolon
id|ent-&gt;next_hash
op_assign
l_int|NULL
suffix:semicolon
id|ent-&gt;pprev_hash
op_assign
l_int|NULL
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
id|net_bridge_fdb_entry
op_star
id|f
suffix:semicolon
id|f
op_assign
id|br-&gt;hash
(braket
id|i
)braket
suffix:semicolon
r_while
c_loop
(paren
id|f
op_ne
l_int|NULL
)paren
(brace
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
id|__hash_unlink
c_func
(paren
id|f
)paren
suffix:semicolon
id|__hash_link
c_func
(paren
id|br
comma
id|f
comma
id|newhash
)paren
suffix:semicolon
)brace
id|write_unlock_bh
c_func
(paren
op_amp
id|br-&gt;hash_lock
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|f
op_assign
id|f-&gt;next_hash
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
DECL|function|br_fdb_cleanup
r_void
id|br_fdb_cleanup
c_func
(paren
r_struct
id|net_bridge
op_star
id|br
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
r_int
id|timeout
suffix:semicolon
id|timeout
op_assign
id|__timeout
c_func
(paren
id|br
)paren
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
id|net_bridge_fdb_entry
op_star
id|f
suffix:semicolon
id|f
op_assign
id|br-&gt;hash
(braket
id|i
)braket
suffix:semicolon
r_while
c_loop
(paren
id|f
op_ne
l_int|NULL
)paren
(brace
r_struct
id|net_bridge_fdb_entry
op_star
id|g
suffix:semicolon
id|g
op_assign
id|f-&gt;next_hash
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|f-&gt;is_static
op_logical_and
id|time_before_eq
c_func
(paren
id|f-&gt;ageing_timer
comma
id|timeout
)paren
)paren
(brace
id|__hash_unlink
c_func
(paren
id|f
)paren
suffix:semicolon
id|br_fdb_put
c_func
(paren
id|f
)paren
suffix:semicolon
)brace
id|f
op_assign
id|g
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
id|net_bridge_fdb_entry
op_star
id|f
suffix:semicolon
id|f
op_assign
id|br-&gt;hash
(braket
id|i
)braket
suffix:semicolon
r_while
c_loop
(paren
id|f
op_ne
l_int|NULL
)paren
(brace
r_struct
id|net_bridge_fdb_entry
op_star
id|g
suffix:semicolon
id|g
op_assign
id|f-&gt;next_hash
suffix:semicolon
r_if
c_cond
(paren
id|f-&gt;dst
op_eq
id|p
)paren
(brace
id|__hash_unlink
c_func
(paren
id|f
)paren
suffix:semicolon
id|br_fdb_put
c_func
(paren
id|f
)paren
suffix:semicolon
)brace
id|f
op_assign
id|g
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
id|net_bridge_fdb_entry
op_star
id|fdb
suffix:semicolon
id|read_lock_bh
c_func
(paren
op_amp
id|br-&gt;hash_lock
)paren
suffix:semicolon
id|fdb
op_assign
id|br-&gt;hash
(braket
id|br_mac_hash
c_func
(paren
id|addr
)paren
)braket
suffix:semicolon
r_while
c_loop
(paren
id|fdb
op_ne
l_int|NULL
)paren
(brace
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
op_logical_neg
id|has_expired
c_func
(paren
id|br
comma
id|fdb
)paren
)paren
(brace
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
id|fdb
op_assign
id|fdb-&gt;next_hash
suffix:semicolon
)brace
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
id|kfree
c_func
(paren
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
id|net_bridge_fdb_entry
op_star
id|f
suffix:semicolon
r_for
c_loop
(paren
id|f
op_assign
id|br-&gt;hash
(braket
id|i
)braket
suffix:semicolon
id|f
op_ne
l_int|NULL
op_logical_and
id|num
OL
id|maxnum
suffix:semicolon
id|f
op_assign
id|f-&gt;next_hash
)paren
(brace
r_struct
id|__fdb_entry
id|ent
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
id|kfree
c_func
(paren
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
DECL|function|__fdb_possibly_replace
r_static
id|__inline__
r_void
id|__fdb_possibly_replace
c_func
(paren
r_struct
id|net_bridge_fdb_entry
op_star
id|fdb
comma
r_struct
id|net_bridge_port
op_star
id|source
comma
r_int
id|is_local
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|fdb-&gt;is_static
op_logical_or
id|is_local
)paren
(brace
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
)brace
)brace
DECL|function|br_fdb_insert
r_void
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
id|net_bridge_fdb_entry
op_star
id|fdb
suffix:semicolon
r_int
id|hash
suffix:semicolon
id|hash
op_assign
id|br_mac_hash
c_func
(paren
id|addr
)paren
suffix:semicolon
id|write_lock_bh
c_func
(paren
op_amp
id|br-&gt;hash_lock
)paren
suffix:semicolon
id|fdb
op_assign
id|br-&gt;hash
(braket
id|hash
)braket
suffix:semicolon
r_while
c_loop
(paren
id|fdb
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|fdb-&gt;is_local
op_logical_and
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
id|__fdb_possibly_replace
c_func
(paren
id|fdb
comma
id|source
comma
id|is_local
)paren
suffix:semicolon
id|write_unlock_bh
c_func
(paren
op_amp
id|br-&gt;hash_lock
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|fdb
op_assign
id|fdb-&gt;next_hash
suffix:semicolon
)brace
id|fdb
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|fdb
)paren
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fdb
op_eq
l_int|NULL
)paren
(brace
id|write_unlock_bh
c_func
(paren
op_amp
id|br-&gt;hash_lock
)paren
suffix:semicolon
r_return
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
id|__hash_link
c_func
(paren
id|br
comma
id|fdb
comma
id|hash
)paren
suffix:semicolon
id|write_unlock_bh
c_func
(paren
op_amp
id|br-&gt;hash_lock
)paren
suffix:semicolon
)brace
eof
