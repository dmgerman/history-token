multiline_comment|/* Changes&n; *&n; *&t;Mitsuru KANDA @USAGI       : IPv6 Support &n; * &t;Kazunori MIYAZAWA @USAGI   :&n; * &t;YOSHIFUJI Hideaki @USAGI   :&n; * &t;Kunihiro Ishiguro          :&n; * &t;&n; */
macro_line|#include &lt;net/ip.h&gt;
macro_line|#include &lt;net/ipv6.h&gt;
macro_line|#include &lt;net/xfrm.h&gt;
DECL|variable|secpath_cachep
r_static
id|kmem_cache_t
op_star
id|secpath_cachep
suffix:semicolon
DECL|function|__secpath_destroy
r_void
id|__secpath_destroy
c_func
(paren
r_struct
id|sec_path
op_star
id|sp
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
id|sp-&gt;len
suffix:semicolon
id|i
op_increment
)paren
id|xfrm_state_put
c_func
(paren
id|sp-&gt;xvec
(braket
id|i
)braket
)paren
suffix:semicolon
id|kmem_cache_free
c_func
(paren
id|secpath_cachep
comma
id|sp
)paren
suffix:semicolon
)brace
multiline_comment|/* Fetch spi and seq frpm ipsec header */
DECL|function|xfrm_parse_spi
r_static
r_int
id|xfrm_parse_spi
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
id|u32
op_star
id|spi
comma
id|u32
op_star
id|seq
)paren
(brace
r_int
id|offset
comma
id|offset_seq
suffix:semicolon
r_switch
c_cond
(paren
id|skb-&gt;nh.iph-&gt;protocol
)paren
(brace
r_case
id|IPPROTO_AH
suffix:colon
id|offset
op_assign
m_offsetof
(paren
r_struct
id|ip_auth_hdr
comma
id|spi
)paren
suffix:semicolon
id|offset_seq
op_assign
m_offsetof
(paren
r_struct
id|ip_auth_hdr
comma
id|seq_no
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IPPROTO_ESP
suffix:colon
id|offset
op_assign
m_offsetof
(paren
r_struct
id|ip_esp_hdr
comma
id|spi
)paren
suffix:semicolon
id|offset_seq
op_assign
m_offsetof
(paren
r_struct
id|ip_esp_hdr
comma
id|seq_no
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IPPROTO_COMP
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|pskb_may_pull
c_func
(paren
id|skb
comma
l_int|4
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
op_star
id|spi
op_assign
id|ntohl
c_func
(paren
id|ntohs
c_func
(paren
op_star
(paren
id|u16
op_star
)paren
(paren
id|skb-&gt;h.raw
op_plus
l_int|2
)paren
)paren
)paren
suffix:semicolon
op_star
id|seq
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_default
suffix:colon
r_return
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|pskb_may_pull
c_func
(paren
id|skb
comma
l_int|16
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
op_star
id|spi
op_assign
op_star
(paren
id|u32
op_star
)paren
(paren
id|skb-&gt;h.raw
op_plus
id|offset
)paren
suffix:semicolon
op_star
id|seq
op_assign
op_star
(paren
id|u32
op_star
)paren
(paren
id|skb-&gt;h.raw
op_plus
id|offset_seq
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
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
r_int
id|err
suffix:semicolon
id|u32
id|spi
comma
id|seq
suffix:semicolon
r_struct
id|xfrm_state
op_star
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
id|xfrm4_state_lookup
c_func
(paren
id|iph-&gt;daddr
comma
id|spi
comma
id|iph-&gt;protocol
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
id|x-&gt;type
op_member_access_from_pointer
id|input
c_func
(paren
id|x
comma
id|skb
)paren
)paren
r_goto
id|drop_unlock
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
id|secpath_cachep
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
id|sp-&gt;len
op_assign
l_int|0
suffix:semicolon
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
id|skb-&gt;sp-&gt;xvec
op_plus
id|skb-&gt;sp-&gt;len
comma
id|xfrm_vec
comma
id|xfrm_nr
op_star
r_sizeof
(paren
r_void
op_star
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
DECL|function|xfrm_input_init
r_void
id|__init
id|xfrm_input_init
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
l_string|&quot;secpath_cache&quot;
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
l_string|&quot;IP: failed to allocate secpath_cache&bslash;n&quot;
)paren
suffix:semicolon
)brace
macro_line|#if defined (CONFIG_IPV6) || defined (CONFIG_IPV6_MODULE)
multiline_comment|/* Fetch spi and seq frpm ipsec header */
DECL|function|xfrm6_parse_spi
r_static
r_int
id|xfrm6_parse_spi
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
id|u8
id|nexthdr
comma
id|u32
op_star
id|spi
comma
id|u32
op_star
id|seq
)paren
(brace
r_int
id|offset
comma
id|offset_seq
suffix:semicolon
r_switch
c_cond
(paren
id|nexthdr
)paren
(brace
r_case
id|IPPROTO_AH
suffix:colon
id|offset
op_assign
m_offsetof
(paren
r_struct
id|ip_auth_hdr
comma
id|spi
)paren
suffix:semicolon
id|offset_seq
op_assign
m_offsetof
(paren
r_struct
id|ip_auth_hdr
comma
id|seq_no
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IPPROTO_ESP
suffix:colon
id|offset
op_assign
m_offsetof
(paren
r_struct
id|ip_esp_hdr
comma
id|spi
)paren
suffix:semicolon
id|offset_seq
op_assign
m_offsetof
(paren
r_struct
id|ip_esp_hdr
comma
id|seq_no
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IPPROTO_COMP
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|pskb_may_pull
c_func
(paren
id|skb
comma
l_int|4
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
op_star
id|spi
op_assign
id|ntohl
c_func
(paren
id|ntohs
c_func
(paren
op_star
(paren
id|u16
op_star
)paren
(paren
id|skb-&gt;h.raw
op_plus
l_int|2
)paren
)paren
)paren
suffix:semicolon
op_star
id|seq
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_default
suffix:colon
r_return
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|pskb_may_pull
c_func
(paren
id|skb
comma
l_int|16
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
op_star
id|spi
op_assign
op_star
(paren
id|u32
op_star
)paren
(paren
id|skb-&gt;h.raw
op_plus
id|offset
)paren
suffix:semicolon
op_star
id|seq
op_assign
op_star
(paren
id|u32
op_star
)paren
(paren
id|skb-&gt;h.raw
op_plus
id|offset_seq
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|zero_out_mutable_opts
r_static
r_int
id|zero_out_mutable_opts
c_func
(paren
r_struct
id|ipv6_opt_hdr
op_star
id|opthdr
)paren
(brace
id|u8
op_star
id|opt
op_assign
(paren
id|u8
op_star
)paren
id|opthdr
suffix:semicolon
r_int
id|len
op_assign
id|ipv6_optlen
c_func
(paren
id|opthdr
)paren
suffix:semicolon
r_int
id|off
op_assign
l_int|0
suffix:semicolon
r_int
id|optlen
op_assign
l_int|0
suffix:semicolon
id|off
op_add_assign
l_int|2
suffix:semicolon
id|len
op_sub_assign
l_int|2
suffix:semicolon
r_while
c_loop
(paren
id|len
OG
l_int|0
)paren
(brace
r_switch
c_cond
(paren
id|opt
(braket
id|off
)braket
)paren
(brace
r_case
id|IPV6_TLV_PAD0
suffix:colon
id|optlen
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
(brace
)brace
r_if
c_cond
(paren
id|len
OL
l_int|2
)paren
r_goto
id|bad
suffix:semicolon
id|optlen
op_assign
id|opt
(braket
id|off
op_plus
l_int|1
)braket
op_plus
l_int|2
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
id|optlen
)paren
r_goto
id|bad
suffix:semicolon
r_if
c_cond
(paren
id|opt
(braket
id|off
)braket
op_amp
l_int|0x20
)paren
id|memset
c_func
(paren
op_amp
id|opt
(braket
id|off
op_plus
l_int|2
)braket
comma
l_int|0
comma
id|opt
(braket
id|off
op_plus
l_int|1
)braket
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|off
op_add_assign
id|optlen
suffix:semicolon
id|len
op_sub_assign
id|optlen
suffix:semicolon
)brace
r_if
c_cond
(paren
id|len
op_eq
l_int|0
)paren
r_return
l_int|1
suffix:semicolon
id|bad
suffix:colon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|xfrm6_clear_mutable_options
r_int
id|xfrm6_clear_mutable_options
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
id|u16
op_star
id|nh_offset
comma
r_int
id|dir
)paren
(brace
id|u16
id|offset
op_assign
r_sizeof
(paren
r_struct
id|ipv6hdr
)paren
suffix:semicolon
r_struct
id|ipv6_opt_hdr
op_star
id|exthdr
op_assign
(paren
r_struct
id|ipv6_opt_hdr
op_star
)paren
(paren
id|skb-&gt;nh.raw
op_plus
id|offset
)paren
suffix:semicolon
r_int
r_int
id|packet_len
op_assign
id|skb-&gt;tail
op_minus
id|skb-&gt;nh.raw
suffix:semicolon
id|u8
id|nexthdr
op_assign
id|skb-&gt;nh.ipv6h-&gt;nexthdr
suffix:semicolon
id|u8
id|nextnexthdr
op_assign
l_int|0
suffix:semicolon
op_star
id|nh_offset
op_assign
(paren
(paren
r_int
r_char
op_star
)paren
op_amp
id|skb-&gt;nh.ipv6h-&gt;nexthdr
)paren
op_minus
id|skb-&gt;nh.raw
suffix:semicolon
r_while
c_loop
(paren
id|offset
op_plus
l_int|1
op_le
id|packet_len
)paren
(brace
r_switch
c_cond
(paren
id|nexthdr
)paren
(brace
r_case
id|NEXTHDR_HOP
suffix:colon
op_star
id|nh_offset
op_assign
id|offset
suffix:semicolon
id|offset
op_add_assign
id|ipv6_optlen
c_func
(paren
id|exthdr
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|zero_out_mutable_opts
c_func
(paren
id|exthdr
)paren
)paren
(brace
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
l_string|&quot;overrun hopopts&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|nexthdr
op_assign
id|exthdr-&gt;nexthdr
suffix:semicolon
id|exthdr
op_assign
(paren
r_struct
id|ipv6_opt_hdr
op_star
)paren
(paren
id|skb-&gt;nh.raw
op_plus
id|offset
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|NEXTHDR_ROUTING
suffix:colon
op_star
id|nh_offset
op_assign
id|offset
suffix:semicolon
id|offset
op_add_assign
id|ipv6_optlen
c_func
(paren
id|exthdr
)paren
suffix:semicolon
(paren
(paren
r_struct
id|ipv6_rt_hdr
op_star
)paren
id|exthdr
)paren
op_member_access_from_pointer
id|segments_left
op_assign
l_int|0
suffix:semicolon
id|nexthdr
op_assign
id|exthdr-&gt;nexthdr
suffix:semicolon
id|exthdr
op_assign
(paren
r_struct
id|ipv6_opt_hdr
op_star
)paren
(paren
id|skb-&gt;nh.raw
op_plus
id|offset
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|NEXTHDR_DEST
suffix:colon
op_star
id|nh_offset
op_assign
id|offset
suffix:semicolon
id|offset
op_add_assign
id|ipv6_optlen
c_func
(paren
id|exthdr
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|zero_out_mutable_opts
c_func
(paren
id|exthdr
)paren
)paren
(brace
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
l_string|&quot;overrun destopt&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|nexthdr
op_assign
id|exthdr-&gt;nexthdr
suffix:semicolon
id|exthdr
op_assign
(paren
r_struct
id|ipv6_opt_hdr
op_star
)paren
(paren
id|skb-&gt;nh.raw
op_plus
id|offset
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|NEXTHDR_AUTH
suffix:colon
r_if
c_cond
(paren
id|dir
op_eq
id|XFRM_POLICY_OUT
)paren
(brace
id|memset
c_func
(paren
(paren
(paren
r_struct
id|ipv6_auth_hdr
op_star
)paren
id|exthdr
)paren
op_member_access_from_pointer
id|auth_data
comma
l_int|0
comma
(paren
(paren
(paren
r_struct
id|ipv6_auth_hdr
op_star
)paren
id|exthdr
)paren
op_member_access_from_pointer
id|hdrlen
op_minus
l_int|1
)paren
op_lshift
l_int|2
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|exthdr-&gt;nexthdr
op_eq
id|NEXTHDR_DEST
)paren
(brace
id|offset
op_add_assign
(paren
(paren
(paren
r_struct
id|ipv6_auth_hdr
op_star
)paren
id|exthdr
)paren
op_member_access_from_pointer
id|hdrlen
op_plus
l_int|2
)paren
op_lshift
l_int|2
suffix:semicolon
id|exthdr
op_assign
(paren
r_struct
id|ipv6_opt_hdr
op_star
)paren
(paren
id|skb-&gt;nh.raw
op_plus
id|offset
)paren
suffix:semicolon
id|nextnexthdr
op_assign
id|exthdr-&gt;nexthdr
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|zero_out_mutable_opts
c_func
(paren
id|exthdr
)paren
)paren
(brace
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
l_string|&quot;overrun destopt&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
r_return
id|nexthdr
suffix:semicolon
r_default
suffix:colon
r_return
id|nexthdr
suffix:semicolon
)brace
)brace
r_return
id|nexthdr
suffix:semicolon
)brace
DECL|function|xfrm6_rcv
r_int
id|xfrm6_rcv
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
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
id|xfrm_state
op_star
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
r_struct
id|ipv6hdr
op_star
id|hdr
op_assign
id|skb-&gt;nh.ipv6h
suffix:semicolon
r_int
r_char
op_star
id|tmp_hdr
op_assign
l_int|NULL
suffix:semicolon
r_int
id|hdr_len
op_assign
l_int|0
suffix:semicolon
id|u16
id|nh_offset
op_assign
l_int|0
suffix:semicolon
id|u8
id|nexthdr
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|hdr-&gt;nexthdr
op_eq
id|IPPROTO_AH
op_logical_or
id|hdr-&gt;nexthdr
op_eq
id|IPPROTO_ESP
)paren
(brace
id|nh_offset
op_assign
(paren
(paren
r_int
r_char
op_star
)paren
op_amp
id|skb-&gt;nh.ipv6h-&gt;nexthdr
)paren
op_minus
id|skb-&gt;nh.raw
suffix:semicolon
id|hdr_len
op_assign
r_sizeof
(paren
r_struct
id|ipv6hdr
)paren
suffix:semicolon
)brace
r_else
(brace
id|hdr_len
op_assign
id|skb-&gt;h.raw
op_minus
id|skb-&gt;nh.raw
suffix:semicolon
)brace
id|tmp_hdr
op_assign
id|kmalloc
c_func
(paren
id|hdr_len
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tmp_hdr
)paren
r_goto
id|drop
suffix:semicolon
id|memcpy
c_func
(paren
id|tmp_hdr
comma
id|skb-&gt;nh.raw
comma
id|hdr_len
)paren
suffix:semicolon
id|nexthdr
op_assign
id|xfrm6_clear_mutable_options
c_func
(paren
id|skb
comma
op_amp
id|nh_offset
comma
id|XFRM_POLICY_IN
)paren
suffix:semicolon
id|hdr-&gt;priority
op_assign
l_int|0
suffix:semicolon
id|hdr-&gt;flow_lbl
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
id|hdr-&gt;flow_lbl
(braket
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
id|hdr-&gt;flow_lbl
(braket
l_int|2
)braket
op_assign
l_int|0
suffix:semicolon
id|hdr-&gt;hop_limit
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|xfrm6_parse_spi
c_func
(paren
id|skb
comma
id|nexthdr
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
id|ipv6hdr
op_star
id|iph
op_assign
id|skb-&gt;nh.ipv6h
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
id|xfrm6_state_lookup
c_func
(paren
op_amp
id|iph-&gt;daddr
comma
id|spi
comma
id|nexthdr
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
id|nexthdr
op_assign
id|x-&gt;type
op_member_access_from_pointer
id|input
c_func
(paren
id|x
comma
id|skb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nexthdr
op_le
l_int|0
)paren
r_goto
id|drop_unlock
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
op_assign
id|x
suffix:semicolon
id|iph
op_assign
id|skb-&gt;nh.ipv6h
suffix:semicolon
multiline_comment|/* ??? */
r_if
c_cond
(paren
id|nexthdr
op_eq
id|NEXTHDR_DEST
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|pskb_may_pull
c_func
(paren
id|skb
comma
(paren
id|skb-&gt;h.raw
op_minus
id|skb-&gt;data
)paren
op_plus
l_int|8
)paren
op_logical_or
op_logical_neg
id|pskb_may_pull
c_func
(paren
id|skb
comma
(paren
id|skb-&gt;h.raw
op_minus
id|skb-&gt;data
)paren
op_plus
(paren
(paren
id|skb-&gt;h.raw
(braket
l_int|1
)braket
op_plus
l_int|1
)paren
op_lshift
l_int|3
)paren
)paren
)paren
(brace
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|drop
suffix:semicolon
)brace
id|nexthdr
op_assign
id|skb-&gt;h.raw
(braket
l_int|0
)braket
suffix:semicolon
id|nh_offset
op_assign
id|skb-&gt;h.raw
op_minus
id|skb-&gt;nh.raw
suffix:semicolon
id|skb_pull
c_func
(paren
id|skb
comma
(paren
id|skb-&gt;h.raw
(braket
l_int|1
)braket
op_plus
l_int|1
)paren
op_lshift
l_int|3
)paren
suffix:semicolon
id|skb-&gt;h.raw
op_assign
id|skb-&gt;data
suffix:semicolon
)brace
r_if
c_cond
(paren
id|x-&gt;props.mode
)paren
(brace
multiline_comment|/* XXX */
r_if
c_cond
(paren
id|iph-&gt;nexthdr
op_ne
id|IPPROTO_IPV6
)paren
r_goto
id|drop
suffix:semicolon
id|skb-&gt;nh.raw
op_assign
id|skb-&gt;data
suffix:semicolon
id|iph
op_assign
id|skb-&gt;nh.ipv6h
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
id|xfrm6_parse_spi
c_func
(paren
id|skb
comma
id|nexthdr
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
id|memcpy
c_func
(paren
id|skb-&gt;nh.raw
comma
id|tmp_hdr
comma
id|hdr_len
)paren
suffix:semicolon
id|skb-&gt;nh.raw
(braket
id|nh_offset
)braket
op_assign
id|nexthdr
suffix:semicolon
id|skb-&gt;nh.ipv6h-&gt;payload_len
op_assign
id|htons
c_func
(paren
id|hdr_len
op_plus
id|skb-&gt;len
op_minus
r_sizeof
(paren
r_struct
id|ipv6hdr
)paren
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
id|secpath_cachep
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
id|sp-&gt;len
op_assign
l_int|0
suffix:semicolon
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
id|skb-&gt;sp-&gt;xvec
op_plus
id|skb-&gt;sp-&gt;len
comma
id|xfrm_vec
comma
id|xfrm_nr
op_star
r_sizeof
(paren
r_void
op_star
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
id|nexthdr
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
r_if
c_cond
(paren
id|tmp_hdr
)paren
id|kfree
c_func
(paren
id|tmp_hdr
)paren
suffix:semicolon
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
macro_line|#endif /* CONFIG_IPV6 || CONFIG_IPV6_MODULE */
eof
