multiline_comment|/*&n; * xfrm4_state.c&n; *&n; * Changes:&n; * &t;YOSHIFUJI Hideaki @USAGI&n; * &t;&t;Split up af-specific portion&n; *&n; */
macro_line|#include &lt;net/xfrm.h&gt;
macro_line|#include &lt;linux/pfkeyv2.h&gt;
macro_line|#include &lt;linux/ipsec.h&gt;
r_extern
r_struct
id|xfrm_state_afinfo
id|xfrm4_state_afinfo
suffix:semicolon
r_static
r_void
DECL|function|__xfrm4_init_tempsel
id|__xfrm4_init_tempsel
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
id|x-&gt;sel.daddr.a4
op_assign
id|fl-&gt;fl4_dst
suffix:semicolon
id|x-&gt;sel.saddr.a4
op_assign
id|fl-&gt;fl4_src
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
id|x-&gt;id.daddr.a4
op_eq
l_int|0
)paren
id|x-&gt;id.daddr.a4
op_assign
id|daddr-&gt;a4
suffix:semicolon
id|x-&gt;props.saddr
op_assign
id|tmpl-&gt;saddr
suffix:semicolon
r_if
c_cond
(paren
id|x-&gt;props.saddr.a4
op_eq
l_int|0
)paren
id|x-&gt;props.saddr.a4
op_assign
id|saddr-&gt;a4
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
id|AF_INET
suffix:semicolon
)brace
r_static
r_struct
id|xfrm_state
op_star
DECL|function|__xfrm4_state_lookup
id|__xfrm4_state_lookup
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
id|__xfrm4_spi_hash
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
id|xfrm4_state_afinfo.state_byspi
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
id|AF_INET
op_logical_and
id|spi
op_eq
id|x-&gt;id.spi
op_logical_and
id|daddr-&gt;a4
op_eq
id|x-&gt;id.daddr.a4
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
DECL|function|__xfrm4_find_acq
id|__xfrm4_find_acq
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
id|__xfrm4_dst_hash
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
id|xfrm4_state_afinfo.state_bydst
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
id|AF_INET
op_logical_and
id|daddr-&gt;a4
op_eq
id|x-&gt;id.daddr.a4
op_logical_and
id|mode
op_eq
id|x-&gt;props.mode
op_logical_and
id|proto
op_eq
id|x-&gt;id.proto
op_logical_and
id|saddr-&gt;a4
op_eq
id|x-&gt;props.saddr.a4
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
id|x0
)paren
(brace
id|xfrm_state_hold
c_func
(paren
id|x0
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
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
id|x0-&gt;sel.daddr.a4
op_assign
id|daddr-&gt;a4
suffix:semicolon
id|x0-&gt;sel.saddr.a4
op_assign
id|saddr-&gt;a4
suffix:semicolon
id|x0-&gt;sel.prefixlen_d
op_assign
l_int|32
suffix:semicolon
id|x0-&gt;sel.prefixlen_s
op_assign
l_int|32
suffix:semicolon
id|x0-&gt;props.saddr.a4
op_assign
id|saddr-&gt;a4
suffix:semicolon
id|x0-&gt;km.state
op_assign
id|XFRM_STATE_ACQ
suffix:semicolon
id|x0-&gt;id.daddr.a4
op_assign
id|daddr-&gt;a4
suffix:semicolon
id|x0-&gt;id.proto
op_assign
id|proto
suffix:semicolon
id|x0-&gt;props.family
op_assign
id|AF_INET
suffix:semicolon
id|x0-&gt;props.mode
op_assign
id|mode
suffix:semicolon
id|x0-&gt;props.reqid
op_assign
id|reqid
suffix:semicolon
id|x0-&gt;props.family
op_assign
id|AF_INET
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
l_int|0
)paren
suffix:semicolon
id|list_add_tail
c_func
(paren
op_amp
id|x0-&gt;bydst
comma
id|xfrm4_state_afinfo.state_bydst
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
r_return
id|x0
suffix:semicolon
)brace
DECL|variable|xfrm4_state_afinfo
r_static
r_struct
id|xfrm_state_afinfo
id|xfrm4_state_afinfo
op_assign
(brace
dot
id|family
op_assign
id|AF_INET
comma
dot
id|lock
op_assign
id|RW_LOCK_UNLOCKED
comma
dot
id|init_tempsel
op_assign
id|__xfrm4_init_tempsel
comma
dot
id|state_lookup
op_assign
id|__xfrm4_state_lookup
comma
dot
id|find_acq
op_assign
id|__xfrm4_find_acq
comma
)brace
suffix:semicolon
DECL|function|xfrm4_state_init
r_void
id|__init
id|xfrm4_state_init
c_func
(paren
r_void
)paren
(brace
id|xfrm_state_register_afinfo
c_func
(paren
op_amp
id|xfrm4_state_afinfo
)paren
suffix:semicolon
)brace
DECL|function|xfrm4_state_fini
r_void
id|__exit
id|xfrm4_state_fini
c_func
(paren
r_void
)paren
(brace
id|xfrm_state_unregister_afinfo
c_func
(paren
op_amp
id|xfrm4_state_afinfo
)paren
suffix:semicolon
)brace
eof
