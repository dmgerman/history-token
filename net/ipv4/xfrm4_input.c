multiline_comment|/*&n; * xfrm4_input.c&n; *&n; * Changes:&n; *&t;YOSHIFUJI Hideaki @USAGI&n; *&t;&t;Split up af-specific portion&n; *&t;Derek Atkins &lt;derek@ihtfp.com&gt;&n; *&t;&t;Add Encapsulation support&n; * &t;&n; */
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;net/inet_ecn.h&gt;
macro_line|#include &lt;net/ip.h&gt;
macro_line|#include &lt;net/xfrm.h&gt;
DECL|variable|secpath_cachep
r_static
id|kmem_cache_t
op_star
id|secpath_cachep
suffix:semicolon
DECL|function|xfrm4_rcv
r_int
id|xfrm4_rcv
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_return
id|xfrm4_rcv_encap
c_func
(paren
id|skb
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|ipip_ecn_decapsulate
r_static
r_inline
r_void
id|ipip_ecn_decapsulate
c_func
(paren
r_struct
id|iphdr
op_star
id|outer_iph
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|iphdr
op_star
id|inner_iph
op_assign
id|skb-&gt;nh.iph
suffix:semicolon
r_if
c_cond
(paren
id|INET_ECN_is_ce
c_func
(paren
id|outer_iph-&gt;tos
)paren
op_logical_and
id|INET_ECN_is_not_ce
c_func
(paren
id|inner_iph-&gt;tos
)paren
)paren
id|IP_ECN_set_ce
c_func
(paren
id|inner_iph
)paren
suffix:semicolon
)brace
DECL|function|xfrm4_rcv_encap
r_int
id|xfrm4_rcv_encap
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
id|__u16
id|encap_type
)paren
(brace
r_int
id|err
suffix:semicolon
id|u32
id|spi
comma
id|seq
suffix:semicolon
r_struct
id|sec_decap_state
id|xfrm_vec
(braket
id|XFRM_MAX_DEPTH
)braket
suffix:semicolon
r_struct
id|xfrm_state
op_star
id|x
suffix:semicolon
r_int
id|xfrm_nr
op_assign
l_int|0
suffix:semicolon
r_int
id|decaps
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|xfrm_parse_spi
c_func
(paren
id|skb
comma
id|skb-&gt;nh.iph-&gt;protocol
comma
op_amp
id|spi
comma
op_amp
id|seq
)paren
)paren
op_ne
l_int|0
)paren
r_goto
id|drop
suffix:semicolon
r_do
(brace
r_struct
id|iphdr
op_star
id|iph
op_assign
id|skb-&gt;nh.iph
suffix:semicolon
r_if
c_cond
(paren
id|xfrm_nr
op_eq
id|XFRM_MAX_DEPTH
)paren
r_goto
id|drop
suffix:semicolon
id|x
op_assign
id|xfrm_state_lookup
c_func
(paren
(paren
id|xfrm_address_t
op_star
)paren
op_amp
id|iph-&gt;daddr
comma
id|spi
comma
id|iph-&gt;protocol
comma
id|AF_INET
)paren
suffix:semicolon
r_if
c_cond
(paren
id|x
op_eq
l_int|NULL
)paren
r_goto
id|drop
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|x-&gt;lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|x-&gt;km.state
op_ne
id|XFRM_STATE_VALID
)paren
)paren
r_goto
id|drop_unlock
suffix:semicolon
r_if
c_cond
(paren
id|x-&gt;props.replay_window
op_logical_and
id|xfrm_replay_check
c_func
(paren
id|x
comma
id|seq
)paren
)paren
r_goto
id|drop_unlock
suffix:semicolon
r_if
c_cond
(paren
id|xfrm_state_check_expire
c_func
(paren
id|x
)paren
)paren
r_goto
id|drop_unlock
suffix:semicolon
id|xfrm_vec
(braket
id|xfrm_nr
)braket
dot
id|decap.decap_type
op_assign
id|encap_type
suffix:semicolon
r_if
c_cond
(paren
id|x-&gt;type
op_member_access_from_pointer
id|input
c_func
(paren
id|x
comma
op_amp
(paren
id|xfrm_vec
(braket
id|xfrm_nr
)braket
dot
id|decap
)paren
comma
id|skb
)paren
)paren
r_goto
id|drop_unlock
suffix:semicolon
multiline_comment|/* only the first xfrm gets the encap type */
id|encap_type
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|x-&gt;props.replay_window
)paren
id|xfrm_replay_advance
c_func
(paren
id|x
comma
id|seq
)paren
suffix:semicolon
id|x-&gt;curlft.bytes
op_add_assign
id|skb-&gt;len
suffix:semicolon
id|x-&gt;curlft.packets
op_increment
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|x-&gt;lock
)paren
suffix:semicolon
id|xfrm_vec
(braket
id|xfrm_nr
op_increment
)braket
dot
id|xvec
op_assign
id|x
suffix:semicolon
id|iph
op_assign
id|skb-&gt;nh.iph
suffix:semicolon
r_if
c_cond
(paren
id|x-&gt;props.mode
)paren
(brace
r_if
c_cond
(paren
id|iph-&gt;protocol
op_ne
id|IPPROTO_IPIP
)paren
r_goto
id|drop
suffix:semicolon
id|skb-&gt;nh.raw
op_assign
id|skb-&gt;data
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|x-&gt;props.flags
op_amp
id|XFRM_STATE_NOECN
)paren
)paren
id|ipip_ecn_decapsulate
c_func
(paren
id|iph
comma
id|skb
)paren
suffix:semicolon
id|iph
op_assign
id|skb-&gt;nh.iph
suffix:semicolon
id|memset
c_func
(paren
op_amp
(paren
id|IPCB
c_func
(paren
id|skb
)paren
op_member_access_from_pointer
id|opt
)paren
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|ip_options
)paren
)paren
suffix:semicolon
id|decaps
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|err
op_assign
id|xfrm_parse_spi
c_func
(paren
id|skb
comma
id|skb-&gt;nh.iph-&gt;protocol
comma
op_amp
id|spi
comma
op_amp
id|seq
)paren
)paren
OL
l_int|0
)paren
r_goto
id|drop
suffix:semicolon
)brace
r_while
c_loop
(paren
op_logical_neg
id|err
)paren
suffix:semicolon
multiline_comment|/* Allocate new secpath or COW existing one. */
r_if
c_cond
(paren
op_logical_neg
id|skb-&gt;sp
op_logical_or
id|atomic_read
c_func
(paren
op_amp
id|skb-&gt;sp-&gt;refcnt
)paren
op_ne
l_int|1
)paren
(brace
id|kmem_cache_t
op_star
id|pool
op_assign
id|skb-&gt;sp
ques
c_cond
id|skb-&gt;sp-&gt;pool
suffix:colon
id|secpath_cachep
suffix:semicolon
r_struct
id|sec_path
op_star
id|sp
suffix:semicolon
id|sp
op_assign
id|kmem_cache_alloc
c_func
(paren
id|pool
comma
id|SLAB_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sp
)paren
r_goto
id|drop
suffix:semicolon
r_if
c_cond
(paren
id|skb-&gt;sp
)paren
(brace
id|memcpy
c_func
(paren
id|sp
comma
id|skb-&gt;sp
comma
r_sizeof
(paren
r_struct
id|sec_path
)paren
)paren
suffix:semicolon
id|secpath_put
c_func
(paren
id|skb-&gt;sp
)paren
suffix:semicolon
)brace
r_else
(brace
id|sp-&gt;pool
op_assign
id|pool
suffix:semicolon
id|sp-&gt;len
op_assign
l_int|0
suffix:semicolon
)brace
id|atomic_set
c_func
(paren
op_amp
id|sp-&gt;refcnt
comma
l_int|1
)paren
suffix:semicolon
id|skb-&gt;sp
op_assign
id|sp
suffix:semicolon
)brace
r_if
c_cond
(paren
id|xfrm_nr
op_plus
id|skb-&gt;sp-&gt;len
OG
id|XFRM_MAX_DEPTH
)paren
r_goto
id|drop
suffix:semicolon
id|memcpy
c_func
(paren
id|skb-&gt;sp-&gt;x
op_plus
id|skb-&gt;sp-&gt;len
comma
id|xfrm_vec
comma
id|xfrm_nr
op_star
r_sizeof
(paren
r_struct
id|sec_decap_state
)paren
)paren
suffix:semicolon
id|skb-&gt;sp-&gt;len
op_add_assign
id|xfrm_nr
suffix:semicolon
r_if
c_cond
(paren
id|decaps
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|skb-&gt;dev-&gt;flags
op_amp
id|IFF_LOOPBACK
)paren
)paren
(brace
id|dst_release
c_func
(paren
id|skb-&gt;dst
)paren
suffix:semicolon
id|skb-&gt;dst
op_assign
l_int|NULL
suffix:semicolon
)brace
id|netif_rx
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_else
(brace
r_return
op_minus
id|skb-&gt;nh.iph-&gt;protocol
suffix:semicolon
)brace
id|drop_unlock
suffix:colon
id|spin_unlock
c_func
(paren
op_amp
id|x-&gt;lock
)paren
suffix:semicolon
id|xfrm_state_put
c_func
(paren
id|x
)paren
suffix:semicolon
id|drop
suffix:colon
r_while
c_loop
(paren
op_decrement
id|xfrm_nr
op_ge
l_int|0
)paren
id|xfrm_state_put
c_func
(paren
id|xfrm_vec
(braket
id|xfrm_nr
)braket
dot
id|xvec
)paren
suffix:semicolon
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
DECL|function|xfrm4_input_init
r_void
id|__init
id|xfrm4_input_init
c_func
(paren
r_void
)paren
(brace
id|secpath_cachep
op_assign
id|kmem_cache_create
c_func
(paren
l_string|&quot;secpath4_cache&quot;
comma
r_sizeof
(paren
r_struct
id|sec_path
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
id|secpath_cachep
)paren
id|panic
c_func
(paren
l_string|&quot;IP: failed to allocate secpath4_cache&bslash;n&quot;
)paren
suffix:semicolon
)brace
eof
