macro_line|#include &lt;net/xfrm.h&gt;
macro_line|#include &lt;linux/pfkeyv2.h&gt;
macro_line|#include &lt;linux/ipsec.h&gt;
multiline_comment|/* Each xfrm_state is linked to three tables:&n;&n;   1. Hash table by (spi,daddr,ah/esp) to find SA by SPI. (input,ctl)&n;   2. Hash table by daddr to find what SAs exist for given&n;      destination/tunnel endpoint. (output)&n;   3. (optional, NI) Radix tree by _selector_ for the case,&n;      when we have to find a tunnel mode SA appropriate for given flow,&n;      but do not know tunnel endpoint. At the moment we do&n;      not support this and assume that tunnel endpoint is given&n;      by policy. (output)&n; */
DECL|variable|xfrm_state_lock
r_static
id|spinlock_t
id|xfrm_state_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|macro|XFRM_DST_HSIZE
mdefine_line|#define XFRM_DST_HSIZE&t;&t;1024
multiline_comment|/* Hash table to find appropriate SA towards given target (endpoint&n; * of tunnel or destination of transport mode) allowed by selector.&n; *&n; * Main use is finding SA after policy selected tunnel or transport mode.&n; * Also, it can be used by ah/esp icmp error handler to find offending SA.&n; */
DECL|variable|xfrm_state_bydst
r_static
r_struct
id|list_head
id|xfrm_state_bydst
(braket
id|XFRM_DST_HSIZE
)braket
suffix:semicolon
DECL|variable|xfrm_state_byspi
r_static
r_struct
id|list_head
id|xfrm_state_byspi
(braket
id|XFRM_DST_HSIZE
)braket
suffix:semicolon
DECL|variable|km_waitq
id|wait_queue_head_t
op_star
id|km_waitq
suffix:semicolon
DECL|function|xfrm_state_alloc
r_struct
id|xfrm_state
op_star
id|xfrm_state_alloc
c_func
(paren
r_void
)paren
(brace
r_struct
id|xfrm_state
op_star
id|x
suffix:semicolon
id|x
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|xfrm_state
)paren
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|x
)paren
(brace
id|memset
c_func
(paren
id|x
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|xfrm_state
)paren
)paren
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|x-&gt;refcnt
comma
l_int|1
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|x-&gt;bydst
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|x-&gt;byspi
)paren
suffix:semicolon
id|x-&gt;lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
)brace
r_return
id|x
suffix:semicolon
)brace
DECL|function|__xfrm_state_destroy
r_void
id|__xfrm_state_destroy
c_func
(paren
r_struct
id|xfrm_state
op_star
id|x
)paren
(brace
id|BUG_TRAP
c_func
(paren
id|x-&gt;km.state
op_eq
id|XFRM_STATE_DEAD
)paren
suffix:semicolon
r_if
c_cond
(paren
id|x-&gt;aalg
)paren
id|kfree
c_func
(paren
id|x-&gt;aalg
)paren
suffix:semicolon
r_if
c_cond
(paren
id|x-&gt;ealg
)paren
id|kfree
c_func
(paren
id|x-&gt;ealg
)paren
suffix:semicolon
r_if
c_cond
(paren
id|x-&gt;calg
)paren
id|kfree
c_func
(paren
id|x-&gt;calg
)paren
suffix:semicolon
r_if
c_cond
(paren
id|x-&gt;type
)paren
id|xfrm_put_type
c_func
(paren
id|x-&gt;type
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|x
)paren
suffix:semicolon
)brace
DECL|function|xfrm_state_delete
r_void
id|xfrm_state_delete
c_func
(paren
r_struct
id|xfrm_state
op_star
id|x
)paren
(brace
r_int
id|kill
op_assign
l_int|0
suffix:semicolon
id|spin_lock_bh
c_func
(paren
op_amp
id|x-&gt;lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|x-&gt;km.state
op_ne
id|XFRM_STATE_DEAD
)paren
(brace
id|x-&gt;km.state
op_assign
id|XFRM_STATE_DEAD
suffix:semicolon
id|kill
op_assign
l_int|1
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|xfrm_state_lock
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|x-&gt;bydst
)paren
suffix:semicolon
id|atomic_dec
c_func
(paren
op_amp
id|x-&gt;refcnt
)paren
suffix:semicolon
r_if
c_cond
(paren
id|x-&gt;id.spi
)paren
(brace
id|list_del
c_func
(paren
op_amp
id|x-&gt;byspi
)paren
suffix:semicolon
id|atomic_dec
c_func
(paren
op_amp
id|x-&gt;refcnt
)paren
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|xfrm_state_lock
)paren
suffix:semicolon
)brace
id|spin_unlock_bh
c_func
(paren
op_amp
id|x-&gt;lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|kill
op_logical_and
id|x-&gt;type
)paren
id|x-&gt;type
op_member_access_from_pointer
id|destructor
c_func
(paren
id|x
)paren
suffix:semicolon
id|wake_up
c_func
(paren
id|km_waitq
)paren
suffix:semicolon
)brace
DECL|function|xfrm_state_flush
r_void
id|xfrm_state_flush
c_func
(paren
id|u8
id|proto
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|xfrm_state
op_star
id|x
suffix:semicolon
id|spin_lock_bh
c_func
(paren
op_amp
id|xfrm_state_lock
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
id|XFRM_DST_HSIZE
suffix:semicolon
id|i
op_increment
)paren
(brace
id|restart
suffix:colon
id|list_for_each_entry
c_func
(paren
id|x
comma
id|xfrm_state_bydst
op_plus
id|i
comma
id|bydst
)paren
(brace
r_if
c_cond
(paren
id|proto
op_eq
id|IPSEC_PROTO_ANY
op_logical_or
id|x-&gt;id.proto
op_eq
id|proto
)paren
(brace
id|atomic_inc
c_func
(paren
op_amp
id|x-&gt;refcnt
)paren
suffix:semicolon
id|spin_unlock_bh
c_func
(paren
op_amp
id|xfrm_state_lock
)paren
suffix:semicolon
id|xfrm_state_delete
c_func
(paren
id|x
)paren
suffix:semicolon
id|xfrm_state_put
c_func
(paren
id|x
)paren
suffix:semicolon
id|spin_lock_bh
c_func
(paren
op_amp
id|xfrm_state_lock
)paren
suffix:semicolon
r_goto
id|restart
suffix:semicolon
)brace
)brace
)brace
id|spin_unlock_bh
c_func
(paren
op_amp
id|xfrm_state_lock
)paren
suffix:semicolon
id|wake_up
c_func
(paren
id|km_waitq
)paren
suffix:semicolon
)brace
r_struct
id|xfrm_state
op_star
DECL|function|xfrm_state_find
id|xfrm_state_find
c_func
(paren
id|u32
id|daddr
comma
r_struct
id|flowi
op_star
id|fl
comma
r_struct
id|xfrm_tmpl
op_star
id|tmpl
comma
r_struct
id|xfrm_policy
op_star
id|pol
)paren
(brace
r_int
id|h
op_assign
id|ntohl
c_func
(paren
id|daddr
)paren
suffix:semicolon
r_struct
id|xfrm_state
op_star
id|x
suffix:semicolon
r_int
id|acquire_in_progress
op_assign
l_int|0
suffix:semicolon
r_int
id|error
op_assign
l_int|0
suffix:semicolon
id|h
op_assign
(paren
id|h
op_xor
(paren
id|h
op_rshift
l_int|16
)paren
)paren
op_mod
id|XFRM_DST_HSIZE
suffix:semicolon
id|spin_lock_bh
c_func
(paren
op_amp
id|xfrm_state_lock
)paren
suffix:semicolon
id|list_for_each_entry
c_func
(paren
id|x
comma
id|xfrm_state_bydst
op_plus
id|h
comma
id|bydst
)paren
(brace
r_if
c_cond
(paren
id|daddr
op_eq
id|x-&gt;id.daddr.xfrm4_addr
op_logical_and
id|tmpl-&gt;mode
op_eq
id|x-&gt;props.mode
op_logical_and
id|tmpl-&gt;id.proto
op_eq
id|x-&gt;id.proto
)paren
(brace
multiline_comment|/* Resolution logic:&n;&t;&t;&t;   1. There is a valid state with matching selector.&n;&t;&t;&t;      Done.&n;&t;&t;&t;   2. Valid state with inappropriate selector. Skip.&n;&n;&t;&t;&t;   Entering area of &quot;sysdeps&quot;.&n;&n;&t;&t;&t;   3. If state is not valid, selector is temporary,&n;&t;&t;&t;      it selects only session which triggered&n;&t;&t;&t;      previous resolution. Key manager will do&n;&t;&t;&t;      something to install a state with proper&n;&t;&t;&t;      selector.&n;&t;&t;&t; */
r_if
c_cond
(paren
id|x-&gt;km.state
op_eq
id|XFRM_STATE_VALID
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|xfrm4_selector_match
c_func
(paren
op_amp
id|x-&gt;sel
comma
id|fl
)paren
)paren
r_continue
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|x-&gt;refcnt
)paren
suffix:semicolon
id|spin_unlock_bh
c_func
(paren
op_amp
id|xfrm_state_lock
)paren
suffix:semicolon
r_return
id|x
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|x-&gt;km.state
op_eq
id|XFRM_STATE_ACQ
)paren
(brace
id|acquire_in_progress
op_assign
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|x-&gt;km.state
op_eq
id|XFRM_STATE_ERROR
op_logical_or
id|x-&gt;km.state
op_eq
id|XFRM_STATE_EXPIRED
)paren
(brace
r_if
c_cond
(paren
id|xfrm4_selector_match
c_func
(paren
op_amp
id|x-&gt;sel
comma
id|fl
)paren
)paren
id|error
op_assign
l_int|1
suffix:semicolon
)brace
)brace
)brace
id|x
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|error
op_logical_and
op_logical_neg
id|acquire_in_progress
op_logical_and
(paren
(paren
id|x
op_assign
id|xfrm_state_alloc
c_func
(paren
)paren
)paren
op_ne
l_int|NULL
)paren
)paren
(brace
multiline_comment|/* Initialize temporary selector matching only&n;&t;&t; * to current session. */
id|x-&gt;sel.daddr.xfrm4_addr
op_assign
id|fl-&gt;fl4_dst
suffix:semicolon
id|x-&gt;sel.daddr.xfrm4_mask
op_assign
op_complement
l_int|0
suffix:semicolon
id|x-&gt;sel.saddr.xfrm4_addr
op_assign
id|fl-&gt;fl4_src
suffix:semicolon
id|x-&gt;sel.saddr.xfrm4_mask
op_assign
op_complement
l_int|0
suffix:semicolon
id|x-&gt;sel.dport
op_assign
id|fl-&gt;uli_u.ports.dport
suffix:semicolon
id|x-&gt;sel.dport_mask
op_assign
op_complement
l_int|0
suffix:semicolon
id|x-&gt;sel.sport
op_assign
id|fl-&gt;uli_u.ports.sport
suffix:semicolon
id|x-&gt;sel.sport_mask
op_assign
op_complement
l_int|0
suffix:semicolon
id|x-&gt;sel.prefixlen_d
op_assign
l_int|32
suffix:semicolon
id|x-&gt;sel.prefixlen_s
op_assign
l_int|32
suffix:semicolon
id|x-&gt;sel.proto
op_assign
id|fl-&gt;proto
suffix:semicolon
id|x-&gt;sel.ifindex
op_assign
id|fl-&gt;oif
suffix:semicolon
id|x-&gt;id
op_assign
id|tmpl-&gt;id
suffix:semicolon
r_if
c_cond
(paren
id|x-&gt;id.daddr.xfrm4_addr
op_eq
l_int|0
)paren
id|x-&gt;id.daddr
op_assign
id|x-&gt;sel.daddr
suffix:semicolon
id|x-&gt;props.saddr
op_assign
id|tmpl-&gt;saddr
suffix:semicolon
r_if
c_cond
(paren
id|x-&gt;props.saddr.xfrm4_addr
op_eq
l_int|0
)paren
id|x-&gt;props.saddr
op_assign
id|x-&gt;sel.saddr
suffix:semicolon
id|x-&gt;props.mode
op_assign
id|tmpl-&gt;mode
suffix:semicolon
r_if
c_cond
(paren
id|km_query
c_func
(paren
id|x
comma
id|tmpl
comma
id|pol
)paren
op_eq
l_int|0
)paren
(brace
id|x-&gt;km.state
op_assign
id|XFRM_STATE_ACQ
suffix:semicolon
id|list_add_tail
c_func
(paren
op_amp
id|x-&gt;bydst
comma
id|xfrm_state_bydst
op_plus
id|h
)paren
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|x-&gt;refcnt
)paren
suffix:semicolon
r_if
c_cond
(paren
id|x-&gt;id.spi
)paren
(brace
id|h
op_assign
id|ntohl
c_func
(paren
id|x-&gt;id.daddr.xfrm4_addr
op_xor
id|x-&gt;id.spi
op_xor
id|x-&gt;id.proto
)paren
suffix:semicolon
id|h
op_assign
(paren
id|h
op_xor
(paren
id|h
op_rshift
l_int|10
)paren
op_xor
(paren
id|h
op_rshift
l_int|20
)paren
)paren
op_mod
id|XFRM_DST_HSIZE
suffix:semicolon
id|list_add
c_func
(paren
op_amp
id|x-&gt;byspi
comma
id|xfrm_state_byspi
op_plus
id|h
)paren
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|x-&gt;refcnt
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
id|x-&gt;km.state
op_assign
id|XFRM_STATE_DEAD
suffix:semicolon
id|xfrm_state_put
c_func
(paren
id|x
)paren
suffix:semicolon
id|x
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
id|spin_unlock_bh
c_func
(paren
op_amp
id|xfrm_state_lock
)paren
suffix:semicolon
r_return
id|x
suffix:semicolon
)brace
DECL|function|xfrm_state_insert
r_void
id|xfrm_state_insert
c_func
(paren
r_struct
id|xfrm_state
op_star
id|x
)paren
(brace
r_int
id|h
op_assign
id|ntohl
c_func
(paren
id|x-&gt;id.daddr.xfrm4_addr
)paren
suffix:semicolon
id|h
op_assign
(paren
id|h
op_xor
(paren
id|h
op_rshift
l_int|16
)paren
)paren
op_mod
id|XFRM_DST_HSIZE
suffix:semicolon
id|spin_lock_bh
c_func
(paren
op_amp
id|xfrm_state_lock
)paren
suffix:semicolon
id|list_add
c_func
(paren
op_amp
id|x-&gt;bydst
comma
id|xfrm_state_bydst
op_plus
id|h
)paren
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|x-&gt;refcnt
)paren
suffix:semicolon
id|h
op_assign
id|ntohl
c_func
(paren
id|x-&gt;id.daddr.xfrm4_addr
op_xor
id|x-&gt;id.spi
op_xor
id|x-&gt;id.proto
)paren
suffix:semicolon
id|h
op_assign
(paren
id|h
op_xor
(paren
id|h
op_rshift
l_int|10
)paren
op_xor
(paren
id|h
op_rshift
l_int|20
)paren
)paren
op_mod
id|XFRM_DST_HSIZE
suffix:semicolon
id|list_add
c_func
(paren
op_amp
id|x-&gt;byspi
comma
id|xfrm_state_byspi
op_plus
id|h
)paren
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|x-&gt;refcnt
)paren
suffix:semicolon
id|spin_unlock_bh
c_func
(paren
op_amp
id|xfrm_state_lock
)paren
suffix:semicolon
id|wake_up
c_func
(paren
id|km_waitq
)paren
suffix:semicolon
)brace
DECL|function|xfrm_state_check_expire
r_int
id|xfrm_state_check_expire
c_func
(paren
r_struct
id|xfrm_state
op_star
id|x
)paren
(brace
r_if
c_cond
(paren
id|x-&gt;km.state
op_ne
id|XFRM_STATE_VALID
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|x-&gt;lft.hard_byte_limit
op_logical_and
id|x-&gt;curlft.bytes
op_ge
id|x-&gt;lft.hard_byte_limit
)paren
(brace
id|km_expired
c_func
(paren
id|x
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|x-&gt;km.warn_bytes
op_logical_and
id|x-&gt;curlft.bytes
op_ge
id|x-&gt;km.warn_bytes
)paren
(brace
id|x-&gt;km.warn_bytes
op_assign
l_int|0
suffix:semicolon
id|km_warn_expired
c_func
(paren
id|x
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|xfrm_state_check_space
r_int
id|xfrm_state_check_space
c_func
(paren
r_struct
id|xfrm_state
op_star
id|x
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_int
id|nhead
op_assign
id|x-&gt;props.header_len
op_plus
id|skb-&gt;dst-&gt;dev-&gt;hard_header_len
op_minus
id|skb_headroom
c_func
(paren
id|skb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nhead
OG
l_int|0
)paren
r_return
id|pskb_expand_head
c_func
(paren
id|skb
comma
id|nhead
comma
l_int|0
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
multiline_comment|/* Check tail too... */
r_return
l_int|0
suffix:semicolon
)brace
r_struct
id|xfrm_state
op_star
DECL|function|xfrm_state_lookup
id|xfrm_state_lookup
c_func
(paren
id|u32
id|daddr
comma
id|u32
id|spi
comma
id|u8
id|proto
)paren
(brace
r_int
id|h
op_assign
id|ntohl
c_func
(paren
id|daddr
op_xor
id|spi
op_xor
id|proto
)paren
suffix:semicolon
r_struct
id|xfrm_state
op_star
id|x
suffix:semicolon
id|h
op_assign
(paren
id|h
op_xor
(paren
id|h
op_rshift
l_int|10
)paren
op_xor
(paren
id|h
op_rshift
l_int|20
)paren
)paren
op_mod
id|XFRM_DST_HSIZE
suffix:semicolon
id|spin_lock_bh
c_func
(paren
op_amp
id|xfrm_state_lock
)paren
suffix:semicolon
id|list_for_each_entry
c_func
(paren
id|x
comma
id|xfrm_state_byspi
op_plus
id|h
comma
id|byspi
)paren
(brace
r_if
c_cond
(paren
id|spi
op_eq
id|x-&gt;id.spi
op_logical_and
id|daddr
op_eq
id|x-&gt;id.daddr.xfrm4_addr
op_logical_and
id|proto
op_eq
id|x-&gt;id.proto
)paren
(brace
id|atomic_inc
c_func
(paren
op_amp
id|x-&gt;refcnt
)paren
suffix:semicolon
id|spin_unlock_bh
c_func
(paren
op_amp
id|xfrm_state_lock
)paren
suffix:semicolon
r_return
id|x
suffix:semicolon
)brace
)brace
id|spin_unlock_bh
c_func
(paren
op_amp
id|xfrm_state_lock
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_struct
id|xfrm_state
op_star
DECL|function|xfrm_find_acq
id|xfrm_find_acq
c_func
(paren
id|u8
id|mode
comma
id|u16
id|reqid
comma
id|u8
id|proto
comma
id|u32
id|daddr
comma
id|u32
id|saddr
)paren
(brace
r_struct
id|xfrm_state
op_star
id|x
comma
op_star
id|x0
suffix:semicolon
r_int
id|h
op_assign
id|ntohl
c_func
(paren
id|daddr
)paren
suffix:semicolon
id|h
op_assign
(paren
id|h
op_xor
(paren
id|h
op_rshift
l_int|16
)paren
)paren
op_mod
id|XFRM_DST_HSIZE
suffix:semicolon
id|x0
op_assign
l_int|NULL
suffix:semicolon
id|spin_lock_bh
c_func
(paren
op_amp
id|xfrm_state_lock
)paren
suffix:semicolon
id|list_for_each_entry
c_func
(paren
id|x
comma
id|xfrm_state_bydst
op_plus
id|h
comma
id|bydst
)paren
(brace
r_if
c_cond
(paren
id|daddr
op_eq
id|x-&gt;id.daddr.xfrm4_addr
op_logical_and
id|mode
op_eq
id|x-&gt;props.mode
op_logical_and
id|proto
op_eq
id|x-&gt;id.proto
op_logical_and
id|saddr
op_eq
id|x-&gt;props.saddr.xfrm4_addr
op_logical_and
(paren
op_logical_neg
id|reqid
op_logical_or
id|reqid
op_eq
id|x-&gt;props.reqid
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|x0
)paren
id|x0
op_assign
id|x
suffix:semicolon
r_if
c_cond
(paren
id|x-&gt;km.state
op_ne
id|XFRM_STATE_ACQ
)paren
r_continue
suffix:semicolon
id|x0
op_assign
id|x
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|x0
)paren
(brace
id|atomic_inc
c_func
(paren
op_amp
id|x0-&gt;refcnt
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|x0
op_assign
id|xfrm_state_alloc
c_func
(paren
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
id|x0-&gt;sel.daddr.xfrm4_addr
op_assign
id|daddr
suffix:semicolon
id|x0-&gt;sel.daddr.xfrm4_mask
op_assign
op_complement
l_int|0
suffix:semicolon
id|x0-&gt;sel.saddr.xfrm4_addr
op_assign
id|saddr
suffix:semicolon
id|x0-&gt;sel.saddr.xfrm4_mask
op_assign
op_complement
l_int|0
suffix:semicolon
id|x0-&gt;sel.prefixlen_d
op_assign
l_int|32
suffix:semicolon
id|x0-&gt;sel.prefixlen_s
op_assign
l_int|32
suffix:semicolon
id|x0-&gt;props.saddr.xfrm4_addr
op_assign
id|saddr
suffix:semicolon
id|x0-&gt;km.state
op_assign
id|XFRM_STATE_ACQ
suffix:semicolon
id|x0-&gt;id.daddr.xfrm4_addr
op_assign
id|daddr
suffix:semicolon
id|x0-&gt;id.proto
op_assign
id|proto
suffix:semicolon
id|x0-&gt;props.mode
op_assign
id|mode
suffix:semicolon
id|x0-&gt;props.reqid
op_assign
id|reqid
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|x0-&gt;refcnt
)paren
suffix:semicolon
id|list_add_tail
c_func
(paren
op_amp
id|x0-&gt;bydst
comma
id|xfrm_state_bydst
op_plus
id|h
)paren
suffix:semicolon
id|wake_up
c_func
(paren
id|km_waitq
)paren
suffix:semicolon
)brace
id|spin_unlock_bh
c_func
(paren
op_amp
id|xfrm_state_lock
)paren
suffix:semicolon
r_return
id|x0
suffix:semicolon
)brace
multiline_comment|/* Silly enough, but I&squot;m lazy to build resolution list */
DECL|function|xfrm_find_acq_byseq
r_struct
id|xfrm_state
op_star
id|xfrm_find_acq_byseq
c_func
(paren
id|u32
id|seq
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|xfrm_state
op_star
id|x
suffix:semicolon
id|spin_lock_bh
c_func
(paren
op_amp
id|xfrm_state_lock
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
id|XFRM_DST_HSIZE
suffix:semicolon
id|i
op_increment
)paren
(brace
id|list_for_each_entry
c_func
(paren
id|x
comma
id|xfrm_state_bydst
op_plus
id|i
comma
id|bydst
)paren
(brace
r_if
c_cond
(paren
id|x-&gt;km.seq
op_eq
id|seq
)paren
(brace
id|atomic_inc
c_func
(paren
op_amp
id|x-&gt;refcnt
)paren
suffix:semicolon
id|spin_unlock_bh
c_func
(paren
op_amp
id|xfrm_state_lock
)paren
suffix:semicolon
r_return
id|x
suffix:semicolon
)brace
)brace
)brace
id|spin_unlock_bh
c_func
(paren
op_amp
id|xfrm_state_lock
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_void
DECL|function|xfrm_alloc_spi
id|xfrm_alloc_spi
c_func
(paren
r_struct
id|xfrm_state
op_star
id|x
comma
id|u32
id|minspi
comma
id|u32
id|maxspi
)paren
(brace
id|u32
id|h
suffix:semicolon
r_struct
id|xfrm_state
op_star
id|x0
suffix:semicolon
r_if
c_cond
(paren
id|x-&gt;id.spi
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|minspi
op_eq
id|maxspi
)paren
(brace
id|x0
op_assign
id|xfrm_state_lookup
c_func
(paren
id|x-&gt;id.daddr.xfrm4_addr
comma
id|minspi
comma
id|x-&gt;id.proto
)paren
suffix:semicolon
r_if
c_cond
(paren
id|x0
)paren
(brace
id|xfrm_state_put
c_func
(paren
id|x0
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|x-&gt;id.spi
op_assign
id|minspi
suffix:semicolon
)brace
r_else
(brace
id|u32
id|spi
op_assign
l_int|0
suffix:semicolon
id|minspi
op_assign
id|ntohl
c_func
(paren
id|minspi
)paren
suffix:semicolon
id|maxspi
op_assign
id|ntohl
c_func
(paren
id|maxspi
)paren
suffix:semicolon
r_for
c_loop
(paren
id|h
op_assign
l_int|0
suffix:semicolon
id|h
OL
id|maxspi
op_minus
id|minspi
op_plus
l_int|1
suffix:semicolon
id|h
op_increment
)paren
(brace
id|spi
op_assign
id|minspi
op_plus
id|net_random
c_func
(paren
)paren
op_mod
(paren
id|maxspi
op_minus
id|minspi
op_plus
l_int|1
)paren
suffix:semicolon
id|x0
op_assign
id|xfrm_state_lookup
c_func
(paren
id|x-&gt;id.daddr.xfrm4_addr
comma
id|htonl
c_func
(paren
id|spi
)paren
comma
id|x-&gt;id.proto
)paren
suffix:semicolon
r_if
c_cond
(paren
id|x0
op_eq
l_int|NULL
)paren
r_break
suffix:semicolon
id|xfrm_state_put
c_func
(paren
id|x0
)paren
suffix:semicolon
)brace
id|x-&gt;id.spi
op_assign
id|htonl
c_func
(paren
id|spi
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|x-&gt;id.spi
)paren
(brace
id|spin_lock_bh
c_func
(paren
op_amp
id|xfrm_state_lock
)paren
suffix:semicolon
id|h
op_assign
id|ntohl
c_func
(paren
id|x-&gt;id.daddr.xfrm4_addr
op_xor
id|x-&gt;id.spi
op_xor
id|x-&gt;id.proto
)paren
suffix:semicolon
id|h
op_assign
(paren
id|h
op_xor
(paren
id|h
op_rshift
l_int|10
)paren
op_xor
(paren
id|h
op_rshift
l_int|20
)paren
)paren
op_mod
id|XFRM_DST_HSIZE
suffix:semicolon
id|list_add
c_func
(paren
op_amp
id|x-&gt;byspi
comma
id|xfrm_state_byspi
op_plus
id|h
)paren
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|x-&gt;refcnt
)paren
suffix:semicolon
id|spin_unlock_bh
c_func
(paren
op_amp
id|xfrm_state_lock
)paren
suffix:semicolon
id|wake_up
c_func
(paren
id|km_waitq
)paren
suffix:semicolon
)brace
)brace
DECL|function|xfrm_state_walk
r_int
id|xfrm_state_walk
c_func
(paren
id|u8
id|proto
comma
r_int
(paren
op_star
id|func
)paren
(paren
r_struct
id|xfrm_state
op_star
comma
r_int
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
r_int
id|i
suffix:semicolon
r_struct
id|xfrm_state
op_star
id|x
suffix:semicolon
r_int
id|count
op_assign
l_int|0
suffix:semicolon
r_int
id|err
op_assign
l_int|0
suffix:semicolon
id|spin_lock_bh
c_func
(paren
op_amp
id|xfrm_state_lock
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
id|XFRM_DST_HSIZE
suffix:semicolon
id|i
op_increment
)paren
(brace
id|list_for_each_entry
c_func
(paren
id|x
comma
id|xfrm_state_bydst
op_plus
id|i
comma
id|bydst
)paren
(brace
r_if
c_cond
(paren
id|proto
op_eq
id|IPSEC_PROTO_ANY
op_logical_or
id|x-&gt;id.proto
op_eq
id|proto
)paren
id|count
op_increment
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|count
op_eq
l_int|0
)paren
(brace
id|err
op_assign
op_minus
id|ENOENT
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|XFRM_DST_HSIZE
suffix:semicolon
id|i
op_increment
)paren
(brace
id|list_for_each_entry
c_func
(paren
id|x
comma
id|xfrm_state_bydst
op_plus
id|i
comma
id|bydst
)paren
(brace
r_if
c_cond
(paren
id|proto
op_ne
id|IPSEC_PROTO_ANY
op_logical_and
id|x-&gt;id.proto
op_ne
id|proto
)paren
r_continue
suffix:semicolon
id|err
op_assign
id|func
c_func
(paren
id|x
comma
op_decrement
id|count
comma
id|data
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
)brace
)brace
id|out
suffix:colon
id|spin_unlock_bh
c_func
(paren
op_amp
id|xfrm_state_lock
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|xfrm_replay_check
r_int
id|xfrm_replay_check
c_func
(paren
r_struct
id|xfrm_state
op_star
id|x
comma
id|u32
id|seq
)paren
(brace
id|u32
id|diff
suffix:semicolon
id|seq
op_assign
id|ntohl
c_func
(paren
id|seq
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|seq
op_eq
l_int|0
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|likely
c_func
(paren
id|seq
OG
id|x-&gt;replay.seq
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|diff
op_assign
id|x-&gt;replay.seq
op_minus
id|seq
suffix:semicolon
r_if
c_cond
(paren
id|diff
op_ge
id|x-&gt;props.replay_window
)paren
(brace
id|x-&gt;stats.replay_window
op_increment
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|x-&gt;replay.bitmap
op_amp
(paren
l_int|1U
op_lshift
id|diff
)paren
)paren
(brace
id|x-&gt;stats.replay
op_increment
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|xfrm_replay_advance
r_void
id|xfrm_replay_advance
c_func
(paren
r_struct
id|xfrm_state
op_star
id|x
comma
id|u32
id|seq
)paren
(brace
id|u32
id|diff
suffix:semicolon
id|seq
op_assign
id|ntohl
c_func
(paren
id|seq
)paren
suffix:semicolon
r_if
c_cond
(paren
id|seq
OG
id|x-&gt;replay.seq
)paren
(brace
id|diff
op_assign
id|seq
op_minus
id|x-&gt;replay.seq
suffix:semicolon
r_if
c_cond
(paren
id|diff
OL
id|x-&gt;props.replay_window
)paren
id|x-&gt;replay.bitmap
op_assign
(paren
(paren
id|x-&gt;replay.bitmap
)paren
op_lshift
id|diff
)paren
op_or
l_int|1
suffix:semicolon
r_else
id|x-&gt;replay.bitmap
op_assign
l_int|1
suffix:semicolon
id|x-&gt;replay.seq
op_assign
id|seq
suffix:semicolon
)brace
r_else
(brace
id|diff
op_assign
id|x-&gt;replay.seq
op_minus
id|seq
suffix:semicolon
id|x-&gt;replay.bitmap
op_or_assign
(paren
l_int|1U
op_lshift
id|diff
)paren
suffix:semicolon
)brace
)brace
DECL|function|xfrm_check_selectors
r_int
id|xfrm_check_selectors
c_func
(paren
r_struct
id|xfrm_state
op_star
op_star
id|x
comma
r_int
id|n
comma
r_struct
id|flowi
op_star
id|fl
)paren
(brace
r_int
id|i
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
id|n
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|xfrm4_selector_match
c_func
(paren
op_amp
id|x
(braket
id|i
)braket
op_member_access_from_pointer
id|sel
comma
id|fl
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|xfrm_km_list
r_static
r_struct
id|list_head
id|xfrm_km_list
op_assign
id|LIST_HEAD_INIT
c_func
(paren
id|xfrm_km_list
)paren
suffix:semicolon
DECL|variable|xfrm_km_lock
r_static
id|rwlock_t
id|xfrm_km_lock
op_assign
id|RW_LOCK_UNLOCKED
suffix:semicolon
DECL|function|km_warn_expired
r_void
id|km_warn_expired
c_func
(paren
r_struct
id|xfrm_state
op_star
id|x
)paren
(brace
r_struct
id|xfrm_mgr
op_star
id|km
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|xfrm_km_lock
)paren
suffix:semicolon
id|list_for_each_entry
c_func
(paren
id|km
comma
op_amp
id|xfrm_km_list
comma
id|list
)paren
id|km
op_member_access_from_pointer
id|notify
c_func
(paren
id|x
comma
l_int|0
)paren
suffix:semicolon
id|read_unlock
c_func
(paren
op_amp
id|xfrm_km_lock
)paren
suffix:semicolon
)brace
DECL|function|km_expired
r_void
id|km_expired
c_func
(paren
r_struct
id|xfrm_state
op_star
id|x
)paren
(brace
r_struct
id|xfrm_mgr
op_star
id|km
suffix:semicolon
id|x-&gt;km.state
op_assign
id|XFRM_STATE_EXPIRED
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|xfrm_km_lock
)paren
suffix:semicolon
id|list_for_each_entry
c_func
(paren
id|km
comma
op_amp
id|xfrm_km_list
comma
id|list
)paren
id|km
op_member_access_from_pointer
id|notify
c_func
(paren
id|x
comma
l_int|1
)paren
suffix:semicolon
id|read_unlock
c_func
(paren
op_amp
id|xfrm_km_lock
)paren
suffix:semicolon
)brace
DECL|function|km_query
r_int
id|km_query
c_func
(paren
r_struct
id|xfrm_state
op_star
id|x
comma
r_struct
id|xfrm_tmpl
op_star
id|t
comma
r_struct
id|xfrm_policy
op_star
id|pol
)paren
(brace
r_int
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_struct
id|xfrm_mgr
op_star
id|km
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|xfrm_km_lock
)paren
suffix:semicolon
id|list_for_each_entry
c_func
(paren
id|km
comma
op_amp
id|xfrm_km_list
comma
id|list
)paren
(brace
id|err
op_assign
id|km
op_member_access_from_pointer
id|acquire
c_func
(paren
id|x
comma
id|t
comma
id|pol
comma
id|XFRM_POLICY_OUT
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|err
)paren
r_break
suffix:semicolon
)brace
id|read_unlock
c_func
(paren
op_amp
id|xfrm_km_lock
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|xfrm_user_policy
r_int
id|xfrm_user_policy
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_int
id|optname
comma
id|u8
op_star
id|optval
comma
r_int
id|optlen
)paren
(brace
r_int
id|err
suffix:semicolon
id|u8
op_star
id|data
suffix:semicolon
r_struct
id|xfrm_mgr
op_star
id|km
suffix:semicolon
r_struct
id|xfrm_policy
op_star
id|pol
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|optlen
op_le
l_int|0
op_logical_or
id|optlen
OG
id|PAGE_SIZE
)paren
r_return
op_minus
id|EMSGSIZE
suffix:semicolon
id|data
op_assign
id|kmalloc
c_func
(paren
id|optlen
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|data
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|err
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|data
comma
id|optval
comma
id|optlen
)paren
)paren
r_goto
id|out
suffix:semicolon
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|xfrm_km_lock
)paren
suffix:semicolon
id|list_for_each_entry
c_func
(paren
id|km
comma
op_amp
id|xfrm_km_list
comma
id|list
)paren
(brace
id|pol
op_assign
id|km
op_member_access_from_pointer
id|compile_policy
c_func
(paren
id|optname
comma
id|data
comma
id|optlen
comma
op_amp
id|err
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
op_ge
l_int|0
)paren
r_break
suffix:semicolon
)brace
id|read_unlock
c_func
(paren
op_amp
id|xfrm_km_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
op_ge
l_int|0
)paren
(brace
id|xfrm_sk_policy_insert
c_func
(paren
id|sk
comma
id|err
comma
id|pol
)paren
suffix:semicolon
id|err
op_assign
l_int|0
suffix:semicolon
)brace
id|out
suffix:colon
id|kfree
c_func
(paren
id|data
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|xfrm_register_km
r_int
id|xfrm_register_km
c_func
(paren
r_struct
id|xfrm_mgr
op_star
id|km
)paren
(brace
id|write_lock_bh
c_func
(paren
op_amp
id|xfrm_km_lock
)paren
suffix:semicolon
id|list_add_tail
c_func
(paren
op_amp
id|km-&gt;list
comma
op_amp
id|xfrm_km_list
)paren
suffix:semicolon
id|write_unlock_bh
c_func
(paren
op_amp
id|xfrm_km_lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|xfrm_unregister_km
r_int
id|xfrm_unregister_km
c_func
(paren
r_struct
id|xfrm_mgr
op_star
id|km
)paren
(brace
id|write_lock_bh
c_func
(paren
op_amp
id|xfrm_km_lock
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|km-&gt;list
)paren
suffix:semicolon
id|write_unlock_bh
c_func
(paren
op_amp
id|xfrm_km_lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|xfrm_state_init
r_void
id|__init
id|xfrm_state_init
c_func
(paren
r_void
)paren
(brace
r_int
id|i
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
id|XFRM_DST_HSIZE
suffix:semicolon
id|i
op_increment
)paren
(brace
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|xfrm_state_bydst
(braket
id|i
)braket
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|xfrm_state_byspi
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
)brace
eof
