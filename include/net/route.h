multiline_comment|/*&n; * INET&t;&t;An implementation of the TCP/IP protocol suite for the LINUX&n; *&t;&t;operating system.  INET  is implemented using the  BSD Socket&n; *&t;&t;interface as the means of communication with the user level.&n; *&n; *&t;&t;Definitions for the IP router.&n; *&n; * Version:&t;@(#)route.h&t;1.0.4&t;05/27/93&n; *&n; * Authors:&t;Ross Biro, &lt;bir7@leland.Stanford.Edu&gt;&n; *&t;&t;Fred N. van Kempen, &lt;waltje@uWalt.NL.Mugnet.ORG&gt;&n; * Fixes:&n; *&t;&t;Alan Cox&t;:&t;Reformatted. Added ip_rt_local()&n; *&t;&t;Alan Cox&t;:&t;Support for TCP parameters.&n; *&t;&t;Alexey Kuznetsov:&t;Major changes for new routing code.&n; *&t;&t;Mike McLagan    :&t;Routing by source&n; *&t;&t;Robert Olsson   :&t;Added rt_cache statistics&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _ROUTE_H
DECL|macro|_ROUTE_H
mdefine_line|#define _ROUTE_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;net/dst.h&gt;
macro_line|#include &lt;net/inetpeer.h&gt;
macro_line|#include &lt;net/flow.h&gt;
macro_line|#include &lt;linux/in_route.h&gt;
macro_line|#include &lt;linux/rtnetlink.h&gt;
macro_line|#include &lt;linux/route.h&gt;
macro_line|#include &lt;linux/ip.h&gt;
macro_line|#include &lt;linux/cache.h&gt;
macro_line|#ifndef __KERNEL__
macro_line|#warning This file is not supposed to be used outside of kernel.
macro_line|#endif
DECL|macro|RTO_ONLINK
mdefine_line|#define RTO_ONLINK&t;0x01
DECL|macro|RTO_CONN
mdefine_line|#define RTO_CONN&t;0
multiline_comment|/* RTO_CONN is not used (being alias for 0), but preserved not to break&n; * some modules referring to it. */
DECL|macro|RT_CONN_FLAGS
mdefine_line|#define RT_CONN_FLAGS(sk)   (RT_TOS(inet_sk(sk)-&gt;tos) | sk-&gt;localroute)
r_struct
id|inet_peer
suffix:semicolon
DECL|struct|rtable
r_struct
id|rtable
(brace
r_union
(brace
DECL|member|dst
r_struct
id|dst_entry
id|dst
suffix:semicolon
DECL|member|rt_next
r_struct
id|rtable
op_star
id|rt_next
suffix:semicolon
DECL|member|u
)brace
id|u
suffix:semicolon
DECL|member|rt_flags
r_int
id|rt_flags
suffix:semicolon
DECL|member|rt_type
r_int
id|rt_type
suffix:semicolon
DECL|member|rt_dst
id|__u32
id|rt_dst
suffix:semicolon
multiline_comment|/* Path destination&t;*/
DECL|member|rt_src
id|__u32
id|rt_src
suffix:semicolon
multiline_comment|/* Path source&t;&t;*/
DECL|member|rt_iif
r_int
id|rt_iif
suffix:semicolon
multiline_comment|/* Info on neighbour */
DECL|member|rt_gateway
id|__u32
id|rt_gateway
suffix:semicolon
multiline_comment|/* Cache lookup keys */
DECL|member|fl
r_struct
id|flowi
id|fl
suffix:semicolon
multiline_comment|/* Miscellaneous cached information */
DECL|member|rt_spec_dst
id|__u32
id|rt_spec_dst
suffix:semicolon
multiline_comment|/* RFC1122 specific destination */
DECL|member|peer
r_struct
id|inet_peer
op_star
id|peer
suffix:semicolon
multiline_comment|/* long-living peer info */
macro_line|#ifdef CONFIG_IP_ROUTE_NAT
DECL|member|rt_src_map
id|__u32
id|rt_src_map
suffix:semicolon
DECL|member|rt_dst_map
id|__u32
id|rt_dst_map
suffix:semicolon
macro_line|#endif
)brace
suffix:semicolon
DECL|struct|ip_rt_acct
r_struct
id|ip_rt_acct
(brace
DECL|member|o_bytes
id|__u32
id|o_bytes
suffix:semicolon
DECL|member|o_packets
id|__u32
id|o_packets
suffix:semicolon
DECL|member|i_bytes
id|__u32
id|i_bytes
suffix:semicolon
DECL|member|i_packets
id|__u32
id|i_packets
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|rt_cache_stat
r_struct
id|rt_cache_stat
(brace
DECL|member|in_hit
r_int
r_int
id|in_hit
suffix:semicolon
DECL|member|in_slow_tot
r_int
r_int
id|in_slow_tot
suffix:semicolon
DECL|member|in_slow_mc
r_int
r_int
id|in_slow_mc
suffix:semicolon
DECL|member|in_no_route
r_int
r_int
id|in_no_route
suffix:semicolon
DECL|member|in_brd
r_int
r_int
id|in_brd
suffix:semicolon
DECL|member|in_martian_dst
r_int
r_int
id|in_martian_dst
suffix:semicolon
DECL|member|in_martian_src
r_int
r_int
id|in_martian_src
suffix:semicolon
DECL|member|out_hit
r_int
r_int
id|out_hit
suffix:semicolon
DECL|member|out_slow_tot
r_int
r_int
id|out_slow_tot
suffix:semicolon
DECL|member|out_slow_mc
r_int
r_int
id|out_slow_mc
suffix:semicolon
DECL|member|gc_total
r_int
r_int
id|gc_total
suffix:semicolon
DECL|member|gc_ignored
r_int
r_int
id|gc_ignored
suffix:semicolon
DECL|member|gc_goal_miss
r_int
r_int
id|gc_goal_miss
suffix:semicolon
DECL|member|gc_dst_overflow
r_int
r_int
id|gc_dst_overflow
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|rt_cache_stat
op_star
id|rt_cache_stat
suffix:semicolon
DECL|macro|RT_CACHE_STAT_INC
mdefine_line|#define RT_CACHE_STAT_INC(field)&t;&t;&t;&t;&t;  &bslash;&n;&t;&t;(per_cpu_ptr(rt_cache_stat, smp_processor_id())-&gt;field++)
r_extern
r_struct
id|ip_rt_acct
op_star
id|ip_rt_acct
suffix:semicolon
r_struct
id|in_device
suffix:semicolon
r_extern
r_int
id|ip_rt_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|ip_rt_redirect
c_func
(paren
id|u32
id|old_gw
comma
id|u32
id|dst
comma
id|u32
id|new_gw
comma
id|u32
id|src
comma
id|u8
id|tos
comma
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_void
id|ip_rt_advice
c_func
(paren
r_struct
id|rtable
op_star
op_star
id|rp
comma
r_int
id|advice
)paren
suffix:semicolon
r_extern
r_void
id|rt_cache_flush
c_func
(paren
r_int
id|how
)paren
suffix:semicolon
r_extern
r_int
id|__ip_route_output_key
c_func
(paren
r_struct
id|rtable
op_star
op_star
comma
r_const
r_struct
id|flowi
op_star
id|flp
)paren
suffix:semicolon
r_extern
r_int
id|ip_route_output_key
c_func
(paren
r_struct
id|rtable
op_star
op_star
comma
r_struct
id|flowi
op_star
id|flp
)paren
suffix:semicolon
r_extern
r_int
id|ip_route_output_flow
c_func
(paren
r_struct
id|rtable
op_star
op_star
id|rp
comma
r_struct
id|flowi
op_star
id|flp
comma
r_struct
id|sock
op_star
id|sk
comma
r_int
id|flags
)paren
suffix:semicolon
r_extern
r_int
id|ip_route_input
c_func
(paren
r_struct
id|sk_buff
op_star
comma
id|u32
id|dst
comma
id|u32
id|src
comma
id|u8
id|tos
comma
r_struct
id|net_device
op_star
id|devin
)paren
suffix:semicolon
r_extern
r_int
r_int
id|ip_rt_frag_needed
c_func
(paren
r_struct
id|iphdr
op_star
id|iph
comma
r_int
r_int
id|new_mtu
)paren
suffix:semicolon
r_extern
r_void
id|ip_rt_send_redirect
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
r_extern
r_int
id|inet_addr_type
c_func
(paren
id|u32
id|addr
)paren
suffix:semicolon
r_extern
r_void
id|ip_rt_multicast_event
c_func
(paren
r_struct
id|in_device
op_star
)paren
suffix:semicolon
r_extern
r_int
id|ip_rt_ioctl
c_func
(paren
r_int
r_int
id|cmd
comma
r_void
op_star
id|arg
)paren
suffix:semicolon
r_extern
r_void
id|ip_rt_get_source
c_func
(paren
id|u8
op_star
id|src
comma
r_struct
id|rtable
op_star
id|rt
)paren
suffix:semicolon
r_extern
r_int
id|ip_rt_dump
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|netlink_callback
op_star
id|cb
)paren
suffix:semicolon
DECL|function|ip_rt_put
r_static
r_inline
r_void
id|ip_rt_put
c_func
(paren
r_struct
id|rtable
op_star
id|rt
)paren
(brace
r_if
c_cond
(paren
id|rt
)paren
id|dst_release
c_func
(paren
op_amp
id|rt-&gt;u.dst
)paren
suffix:semicolon
)brace
DECL|macro|IPTOS_RT_MASK
mdefine_line|#define IPTOS_RT_MASK&t;(IPTOS_TOS_MASK &amp; ~3)
r_extern
id|__u8
id|ip_tos2prio
(braket
l_int|16
)braket
suffix:semicolon
DECL|function|rt_tos2priority
r_static
r_inline
r_char
id|rt_tos2priority
c_func
(paren
id|u8
id|tos
)paren
(brace
r_return
id|ip_tos2prio
(braket
id|IPTOS_TOS
c_func
(paren
id|tos
)paren
op_rshift
l_int|1
)braket
suffix:semicolon
)brace
DECL|function|ip_route_connect
r_static
r_inline
r_int
id|ip_route_connect
c_func
(paren
r_struct
id|rtable
op_star
op_star
id|rp
comma
id|u32
id|dst
comma
id|u32
id|src
comma
id|u32
id|tos
comma
r_int
id|oif
comma
id|u8
id|protocol
comma
id|u16
id|sport
comma
id|u16
id|dport
comma
r_struct
id|sock
op_star
id|sk
)paren
(brace
r_struct
id|flowi
id|fl
op_assign
(brace
dot
id|oif
op_assign
id|oif
comma
dot
id|nl_u
op_assign
(brace
dot
id|ip4_u
op_assign
(brace
dot
id|daddr
op_assign
id|dst
comma
dot
id|saddr
op_assign
id|src
comma
dot
id|tos
op_assign
id|tos
)brace
)brace
comma
dot
id|proto
op_assign
id|protocol
comma
dot
id|uli_u
op_assign
(brace
dot
id|ports
op_assign
(brace
dot
id|sport
op_assign
id|sport
comma
dot
id|dport
op_assign
id|dport
)brace
)brace
)brace
suffix:semicolon
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dst
op_logical_or
op_logical_neg
id|src
)paren
(brace
id|err
op_assign
id|__ip_route_output_key
c_func
(paren
id|rp
comma
op_amp
id|fl
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_return
id|err
suffix:semicolon
id|fl.fl4_dst
op_assign
(paren
op_star
id|rp
)paren
op_member_access_from_pointer
id|rt_dst
suffix:semicolon
id|fl.fl4_src
op_assign
(paren
op_star
id|rp
)paren
op_member_access_from_pointer
id|rt_src
suffix:semicolon
id|ip_rt_put
c_func
(paren
op_star
id|rp
)paren
suffix:semicolon
op_star
id|rp
op_assign
l_int|NULL
suffix:semicolon
)brace
r_return
id|ip_route_output_flow
c_func
(paren
id|rp
comma
op_amp
id|fl
comma
id|sk
comma
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|ip_route_newports
r_static
r_inline
r_int
id|ip_route_newports
c_func
(paren
r_struct
id|rtable
op_star
op_star
id|rp
comma
id|u16
id|sport
comma
id|u16
id|dport
comma
r_struct
id|sock
op_star
id|sk
)paren
(brace
r_if
c_cond
(paren
id|sport
op_ne
(paren
op_star
id|rp
)paren
op_member_access_from_pointer
id|fl.uli_u.ports.sport
op_logical_or
id|dport
op_ne
(paren
op_star
id|rp
)paren
op_member_access_from_pointer
id|fl.uli_u.ports.dport
)paren
(brace
r_struct
id|flowi
id|fl
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|fl
comma
op_amp
(paren
op_star
id|rp
)paren
op_member_access_from_pointer
id|fl
comma
r_sizeof
(paren
id|fl
)paren
)paren
suffix:semicolon
id|fl.uli_u.ports.sport
op_assign
id|sport
suffix:semicolon
id|fl.uli_u.ports.dport
op_assign
id|dport
suffix:semicolon
id|ip_rt_put
c_func
(paren
op_star
id|rp
)paren
suffix:semicolon
op_star
id|rp
op_assign
l_int|NULL
suffix:semicolon
r_return
id|ip_route_output_flow
c_func
(paren
id|rp
comma
op_amp
id|fl
comma
id|sk
comma
l_int|0
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_extern
r_void
id|rt_bind_peer
c_func
(paren
r_struct
id|rtable
op_star
id|rt
comma
r_int
id|create
)paren
suffix:semicolon
DECL|function|rt_get_peer
r_static
r_inline
r_struct
id|inet_peer
op_star
id|rt_get_peer
c_func
(paren
r_struct
id|rtable
op_star
id|rt
)paren
(brace
r_if
c_cond
(paren
id|rt-&gt;peer
)paren
r_return
id|rt-&gt;peer
suffix:semicolon
id|rt_bind_peer
c_func
(paren
id|rt
comma
l_int|0
)paren
suffix:semicolon
r_return
id|rt-&gt;peer
suffix:semicolon
)brace
macro_line|#endif&t;/* _ROUTE_H */
eof
