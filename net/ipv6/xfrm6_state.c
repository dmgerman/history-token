multiline_comment|/*&n; * xfrm6_state.c: based on xfrm4_state.c&n; *&n; * Authors:&n; *&t;Mitsuru KANDA @USAGI&n; * &t;Kazunori MIYAZAWA @USAGI&n; * &t;Kunihiro Ishiguro &lt;kunihiro@ipinfusion.com&gt;&n; * &t;&t;IPv6 support&n; * &t;YOSHIFUJI Hideaki @USAGI&n; * &t;&t;Split up af-specific portion&n; * &t;&n; */
macro_line|#include &lt;net/xfrm.h&gt;
macro_line|#include &lt;linux/pfkeyv2.h&gt;
macro_line|#include &lt;linux/ipsec.h&gt;
macro_line|#include &lt;net/ipv6.h&gt;
r_extern
r_struct
id|xfrm_state_afinfo
id|xfrm6_state_afinfo
suffix:semicolon
r_static
r_void
DECL|function|__xfrm6_init_tempsel
id|__xfrm6_init_tempsel
c_func
(paren
r_struct
id|xfrm_state
op_star
id|x
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
id|xfrm_address_t
op_star
id|daddr
comma
id|xfrm_address_t
op_star
id|saddr
)paren
(brace
multiline_comment|/* Initialize temporary selector matching only&n;&t; * to current session. */
id|ipv6_addr_copy
c_func
(paren
(paren
r_struct
id|in6_addr
op_star
)paren
op_amp
id|x-&gt;sel.daddr
comma
op_amp
id|fl-&gt;fl6_dst
)paren
suffix:semicolon
id|ipv6_addr_copy
c_func
(paren
(paren
r_struct
id|in6_addr
op_star
)paren
op_amp
id|x-&gt;sel.saddr
comma
op_amp
id|fl-&gt;fl6_src
)paren
suffix:semicolon
id|x-&gt;sel.dport
op_assign
id|fl-&gt;fl_ip_dport
suffix:semicolon
id|x-&gt;sel.dport_mask
op_assign
op_complement
l_int|0
suffix:semicolon
id|x-&gt;sel.sport
op_assign
id|fl-&gt;fl_ip_sport
suffix:semicolon
id|x-&gt;sel.sport_mask
op_assign
op_complement
l_int|0
suffix:semicolon
id|x-&gt;sel.prefixlen_d
op_assign
l_int|128
suffix:semicolon
id|x-&gt;sel.prefixlen_s
op_assign
l_int|128
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
id|ipv6_addr_any
c_func
(paren
(paren
r_struct
id|in6_addr
op_star
)paren
op_amp
id|x-&gt;id.daddr
)paren
)paren
id|memcpy
c_func
(paren
op_amp
id|x-&gt;id.daddr
comma
id|daddr
comma
r_sizeof
(paren
id|x-&gt;sel.daddr
)paren
)paren
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|x-&gt;props.saddr
comma
op_amp
id|tmpl-&gt;saddr
comma
r_sizeof
(paren
id|x-&gt;props.saddr
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ipv6_addr_any
c_func
(paren
(paren
r_struct
id|in6_addr
op_star
)paren
op_amp
id|x-&gt;props.saddr
)paren
)paren
id|memcpy
c_func
(paren
op_amp
id|x-&gt;props.saddr
comma
id|saddr
comma
r_sizeof
(paren
id|x-&gt;props.saddr
)paren
)paren
suffix:semicolon
id|x-&gt;props.mode
op_assign
id|tmpl-&gt;mode
suffix:semicolon
id|x-&gt;props.reqid
op_assign
id|tmpl-&gt;reqid
suffix:semicolon
id|x-&gt;props.family
op_assign
id|AF_INET6
suffix:semicolon
)brace
r_static
r_struct
id|xfrm_state
op_star
DECL|function|__xfrm6_state_lookup
id|__xfrm6_state_lookup
c_func
(paren
id|xfrm_address_t
op_star
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
id|__xfrm6_spi_hash
c_func
(paren
id|daddr
comma
id|spi
comma
id|proto
)paren
suffix:semicolon
r_struct
id|xfrm_state
op_star
id|x
suffix:semicolon
id|list_for_each_entry
c_func
(paren
id|x
comma
id|xfrm6_state_afinfo.state_byspi
op_plus
id|h
comma
id|byspi
)paren
(brace
r_if
c_cond
(paren
id|x-&gt;props.family
op_eq
id|AF_INET6
op_logical_and
id|spi
op_eq
id|x-&gt;id.spi
op_logical_and
op_logical_neg
id|ipv6_addr_cmp
c_func
(paren
(paren
r_struct
id|in6_addr
op_star
)paren
id|daddr
comma
(paren
r_struct
id|in6_addr
op_star
)paren
id|x-&gt;id.daddr.a6
)paren
op_logical_and
id|proto
op_eq
id|x-&gt;id.proto
)paren
(brace
id|xfrm_state_hold
c_func
(paren
id|x
)paren
suffix:semicolon
r_return
id|x
suffix:semicolon
)brace
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
r_static
r_struct
id|xfrm_state
op_star
DECL|function|__xfrm6_find_acq
id|__xfrm6_find_acq
c_func
(paren
id|u8
id|mode
comma
id|u32
id|reqid
comma
id|u8
id|proto
comma
id|xfrm_address_t
op_star
id|daddr
comma
id|xfrm_address_t
op_star
id|saddr
comma
r_int
id|create
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
id|__xfrm6_dst_hash
c_func
(paren
id|daddr
)paren
suffix:semicolon
id|x0
op_assign
l_int|NULL
suffix:semicolon
id|list_for_each_entry
c_func
(paren
id|x
comma
id|xfrm6_state_afinfo.state_bydst
op_plus
id|h
comma
id|bydst
)paren
(brace
r_if
c_cond
(paren
id|x-&gt;props.family
op_eq
id|AF_INET6
op_logical_and
op_logical_neg
id|ipv6_addr_cmp
c_func
(paren
(paren
r_struct
id|in6_addr
op_star
)paren
id|daddr
comma
(paren
r_struct
id|in6_addr
op_star
)paren
id|x-&gt;id.daddr.a6
)paren
op_logical_and
id|mode
op_eq
id|x-&gt;props.mode
op_logical_and
id|proto
op_eq
id|x-&gt;id.proto
op_logical_and
op_logical_neg
id|ipv6_addr_cmp
c_func
(paren
(paren
r_struct
id|in6_addr
op_star
)paren
id|saddr
comma
(paren
r_struct
id|in6_addr
op_star
)paren
id|x-&gt;props.saddr.a6
)paren
op_logical_and
id|reqid
op_eq
id|x-&gt;props.reqid
op_logical_and
id|x-&gt;km.state
op_eq
id|XFRM_STATE_ACQ
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
id|x-&gt;id.spi
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
op_logical_neg
id|x0
op_logical_and
id|create
op_logical_and
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
id|ipv6_addr_copy
c_func
(paren
(paren
r_struct
id|in6_addr
op_star
)paren
id|x0-&gt;sel.daddr.a6
comma
(paren
r_struct
id|in6_addr
op_star
)paren
id|daddr
)paren
suffix:semicolon
id|ipv6_addr_copy
c_func
(paren
(paren
r_struct
id|in6_addr
op_star
)paren
id|x0-&gt;sel.saddr.a6
comma
(paren
r_struct
id|in6_addr
op_star
)paren
id|saddr
)paren
suffix:semicolon
id|x0-&gt;sel.prefixlen_d
op_assign
l_int|128
suffix:semicolon
id|x0-&gt;sel.prefixlen_s
op_assign
l_int|128
suffix:semicolon
id|ipv6_addr_copy
c_func
(paren
(paren
r_struct
id|in6_addr
op_star
)paren
id|x0-&gt;props.saddr.a6
comma
(paren
r_struct
id|in6_addr
op_star
)paren
id|saddr
)paren
suffix:semicolon
id|x0-&gt;km.state
op_assign
id|XFRM_STATE_ACQ
suffix:semicolon
id|ipv6_addr_copy
c_func
(paren
(paren
r_struct
id|in6_addr
op_star
)paren
id|x0-&gt;id.daddr.a6
comma
(paren
r_struct
id|in6_addr
op_star
)paren
id|daddr
)paren
suffix:semicolon
id|x0-&gt;id.proto
op_assign
id|proto
suffix:semicolon
id|x0-&gt;props.family
op_assign
id|AF_INET6
suffix:semicolon
id|x0-&gt;props.mode
op_assign
id|mode
suffix:semicolon
id|x0-&gt;props.reqid
op_assign
id|reqid
suffix:semicolon
id|x0-&gt;lft.hard_add_expires_seconds
op_assign
id|XFRM_ACQ_EXPIRES
suffix:semicolon
id|xfrm_state_hold
c_func
(paren
id|x0
)paren
suffix:semicolon
id|mod_timer
c_func
(paren
op_amp
id|x0-&gt;timer
comma
id|jiffies
op_plus
id|XFRM_ACQ_EXPIRES
op_star
id|HZ
)paren
suffix:semicolon
id|xfrm_state_hold
c_func
(paren
id|x0
)paren
suffix:semicolon
id|list_add_tail
c_func
(paren
op_amp
id|x0-&gt;bydst
comma
id|xfrm6_state_afinfo.state_bydst
op_plus
id|h
)paren
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|km_waitq
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|x0
)paren
id|xfrm_state_hold
c_func
(paren
id|x0
)paren
suffix:semicolon
r_return
id|x0
suffix:semicolon
)brace
DECL|variable|xfrm6_state_afinfo
r_static
r_struct
id|xfrm_state_afinfo
id|xfrm6_state_afinfo
op_assign
(brace
dot
id|family
op_assign
id|AF_INET6
comma
dot
id|lock
op_assign
id|RW_LOCK_UNLOCKED
comma
dot
id|init_tempsel
op_assign
id|__xfrm6_init_tempsel
comma
dot
id|state_lookup
op_assign
id|__xfrm6_state_lookup
comma
dot
id|find_acq
op_assign
id|__xfrm6_find_acq
comma
)brace
suffix:semicolon
DECL|function|xfrm6_state_init
r_void
id|__init
id|xfrm6_state_init
c_func
(paren
r_void
)paren
(brace
id|xfrm_state_register_afinfo
c_func
(paren
op_amp
id|xfrm6_state_afinfo
)paren
suffix:semicolon
)brace
DECL|function|xfrm6_state_fini
r_void
id|__exit
id|xfrm6_state_fini
c_func
(paren
r_void
)paren
(brace
id|xfrm_state_unregister_afinfo
c_func
(paren
op_amp
id|xfrm6_state_afinfo
)paren
suffix:semicolon
)brace
eof
