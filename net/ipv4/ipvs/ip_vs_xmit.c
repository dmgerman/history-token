multiline_comment|/*&n; * ip_vs_xmit.c: various packet transmitters for IPVS&n; *&n; * Version:     $Id: ip_vs_xmit.c,v 1.2 2002/11/30 01:50:35 wensong Exp $&n; *&n; * Authors:     Wensong Zhang &lt;wensong@linuxvirtualserver.org&gt;&n; *              Julian Anastasov &lt;ja@ssi.bg&gt;&n; *&n; *              This program is free software; you can redistribute it and/or&n; *              modify it under the terms of the GNU General Public License&n; *              as published by the Free Software Foundation; either version&n; *              2 of the License, or (at your option) any later version.&n; *&n; * Changes:&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/compiler.h&gt;
macro_line|#include &lt;linux/ip.h&gt;
macro_line|#include &lt;linux/tcp.h&gt;                  /* for tcphdr */
macro_line|#include &lt;net/tcp.h&gt;                    /* for csum_tcpudp_magic */
macro_line|#include &lt;net/udp.h&gt;
macro_line|#include &lt;net/icmp.h&gt;                   /* for icmp_send */
macro_line|#include &lt;net/route.h&gt;                  /* for ip_route_output */
macro_line|#include &lt;linux/netfilter.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4.h&gt;
macro_line|#include &lt;net/ip_vs.h&gt;
multiline_comment|/*&n; *      Destination cache to speed up outgoing route lookup&n; */
r_static
r_inline
r_void
DECL|function|__ip_vs_dst_set
id|__ip_vs_dst_set
c_func
(paren
r_struct
id|ip_vs_dest
op_star
id|dest
comma
id|u32
id|rtos
comma
r_struct
id|dst_entry
op_star
id|dst
)paren
(brace
r_struct
id|dst_entry
op_star
id|old_dst
suffix:semicolon
id|old_dst
op_assign
id|dest-&gt;dst_cache
suffix:semicolon
id|dest-&gt;dst_cache
op_assign
id|dst
suffix:semicolon
id|dest-&gt;dst_rtos
op_assign
id|rtos
suffix:semicolon
id|dst_release
c_func
(paren
id|old_dst
)paren
suffix:semicolon
)brace
r_static
r_inline
r_struct
id|dst_entry
op_star
DECL|function|__ip_vs_dst_check
id|__ip_vs_dst_check
c_func
(paren
r_struct
id|ip_vs_dest
op_star
id|dest
comma
id|u32
id|rtos
comma
id|u32
id|cookie
)paren
(brace
r_struct
id|dst_entry
op_star
id|dst
op_assign
id|dest-&gt;dst_cache
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
r_if
c_cond
(paren
(paren
id|dst-&gt;obsolete
op_logical_or
id|rtos
op_ne
id|dest-&gt;dst_rtos
)paren
op_logical_and
id|dst-&gt;ops
op_member_access_from_pointer
id|check
c_func
(paren
id|dst
comma
id|cookie
)paren
op_eq
l_int|NULL
)paren
(brace
id|dest-&gt;dst_cache
op_assign
l_int|0
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|dst_hold
c_func
(paren
id|dst
)paren
suffix:semicolon
r_return
id|dst
suffix:semicolon
)brace
r_static
r_inline
r_struct
id|rtable
op_star
DECL|function|__ip_vs_get_out_rt
id|__ip_vs_get_out_rt
c_func
(paren
r_struct
id|ip_vs_conn
op_star
id|cp
comma
id|u32
id|rtos
)paren
(brace
r_struct
id|rtable
op_star
id|rt
suffix:semicolon
multiline_comment|/* Route to the other host */
r_struct
id|ip_vs_dest
op_star
id|dest
op_assign
id|cp-&gt;dest
suffix:semicolon
r_if
c_cond
(paren
id|dest
)paren
(brace
id|spin_lock
c_func
(paren
op_amp
id|dest-&gt;dst_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|rt
op_assign
(paren
r_struct
id|rtable
op_star
)paren
id|__ip_vs_dst_check
c_func
(paren
id|dest
comma
id|rtos
comma
l_int|0
)paren
)paren
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
l_int|0
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
id|dest-&gt;addr
comma
dot
id|saddr
op_assign
l_int|0
comma
dot
id|tos
op_assign
id|rtos
comma
)brace
)brace
comma
)brace
suffix:semicolon
r_if
c_cond
(paren
id|ip_route_output_key
c_func
(paren
op_amp
id|rt
comma
op_amp
id|fl
)paren
)paren
(brace
id|spin_unlock
c_func
(paren
op_amp
id|dest-&gt;dst_lock
)paren
suffix:semicolon
id|IP_VS_DBG_RL
c_func
(paren
l_string|&quot;ip_route_output error, &quot;
l_string|&quot;dest: %u.%u.%u.%u&bslash;n&quot;
comma
id|NIPQUAD
c_func
(paren
id|dest-&gt;addr
)paren
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|__ip_vs_dst_set
c_func
(paren
id|dest
comma
id|rtos
comma
id|dst_clone
c_func
(paren
op_amp
id|rt-&gt;u.dst
)paren
)paren
suffix:semicolon
id|IP_VS_DBG
c_func
(paren
l_int|10
comma
l_string|&quot;new dst %u.%u.%u.%u, refcnt=%d, rtos=%X&bslash;n&quot;
comma
id|NIPQUAD
c_func
(paren
id|dest-&gt;addr
)paren
comma
id|atomic_read
c_func
(paren
op_amp
id|rt-&gt;u.dst.__refcnt
)paren
comma
id|rtos
)paren
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|dest-&gt;dst_lock
)paren
suffix:semicolon
)brace
r_else
(brace
r_struct
id|flowi
id|fl
op_assign
(brace
dot
id|oif
op_assign
l_int|0
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
id|cp-&gt;daddr
comma
dot
id|saddr
op_assign
l_int|0
comma
dot
id|tos
op_assign
id|rtos
comma
)brace
)brace
comma
)brace
suffix:semicolon
r_if
c_cond
(paren
id|ip_route_output_key
c_func
(paren
op_amp
id|rt
comma
op_amp
id|fl
)paren
)paren
(brace
id|IP_VS_DBG_RL
c_func
(paren
l_string|&quot;ip_route_output error, dest: &quot;
l_string|&quot;%u.%u.%u.%u&bslash;n&quot;
comma
id|NIPQUAD
c_func
(paren
id|cp-&gt;daddr
)paren
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
)brace
r_return
id|rt
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Release dest-&gt;dst_cache before a dest is removed&n; */
r_void
DECL|function|ip_vs_dst_reset
id|ip_vs_dst_reset
c_func
(paren
r_struct
id|ip_vs_dest
op_star
id|dest
)paren
(brace
r_struct
id|dst_entry
op_star
id|old_dst
suffix:semicolon
id|old_dst
op_assign
id|dest-&gt;dst_cache
suffix:semicolon
id|dest-&gt;dst_cache
op_assign
l_int|NULL
suffix:semicolon
id|dst_release
c_func
(paren
id|old_dst
)paren
suffix:semicolon
)brace
DECL|macro|IP_VS_XMIT
mdefine_line|#define IP_VS_XMIT(skb, rt)&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;(skb)-&gt;nfcache |= NFC_IPVS_PROPERTY;&t;&t;&bslash;&n;&t;NF_HOOK(PF_INET, NF_IP_LOCAL_OUT, (skb), NULL,&t;&bslash;&n;&t;&t;(rt)-&gt;u.dst.dev, dst_output);&t;&t;&bslash;&n;} while (0)
multiline_comment|/*&n; *      NULL transmitter (do nothing except return NF_ACCEPT)&n; */
r_int
DECL|function|ip_vs_null_xmit
id|ip_vs_null_xmit
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|ip_vs_conn
op_star
id|cp
comma
r_struct
id|ip_vs_protocol
op_star
id|pp
)paren
(brace
multiline_comment|/* we do not touch skb and do not need pskb ptr */
r_return
id|NF_ACCEPT
suffix:semicolon
)brace
multiline_comment|/*&n; *      Bypass transmitter&n; *      Let packets bypass the destination when the destination is not&n; *      available, it may be only used in transparent cache cluster.&n; */
r_int
DECL|function|ip_vs_bypass_xmit
id|ip_vs_bypass_xmit
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|ip_vs_conn
op_star
id|cp
comma
r_struct
id|ip_vs_protocol
op_star
id|pp
)paren
(brace
r_struct
id|rtable
op_star
id|rt
suffix:semicolon
multiline_comment|/* Route to the other host */
r_struct
id|iphdr
op_star
id|iph
op_assign
id|skb-&gt;nh.iph
suffix:semicolon
id|u8
id|tos
op_assign
id|iph-&gt;tos
suffix:semicolon
r_int
id|mtu
suffix:semicolon
r_struct
id|flowi
id|fl
op_assign
(brace
dot
id|oif
op_assign
l_int|0
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
id|iph-&gt;daddr
comma
dot
id|saddr
op_assign
l_int|0
comma
dot
id|tos
op_assign
id|RT_TOS
c_func
(paren
id|tos
)paren
comma
)brace
)brace
comma
)brace
suffix:semicolon
id|EnterFunction
c_func
(paren
l_int|10
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ip_route_output_key
c_func
(paren
op_amp
id|rt
comma
op_amp
id|fl
)paren
)paren
(brace
id|IP_VS_DBG_RL
c_func
(paren
l_string|&quot;ip_vs_bypass_xmit(): ip_route_output error, &quot;
l_string|&quot;dest: %u.%u.%u.%u&bslash;n&quot;
comma
id|NIPQUAD
c_func
(paren
id|iph-&gt;daddr
)paren
)paren
suffix:semicolon
r_goto
id|tx_error_icmp
suffix:semicolon
)brace
multiline_comment|/* MTU checking */
id|mtu
op_assign
id|dst_pmtu
c_func
(paren
op_amp
id|rt-&gt;u.dst
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|skb-&gt;len
OG
id|mtu
)paren
op_logical_and
(paren
id|iph-&gt;frag_off
op_amp
id|__constant_htons
c_func
(paren
id|IP_DF
)paren
)paren
)paren
(brace
id|ip_rt_put
c_func
(paren
id|rt
)paren
suffix:semicolon
id|icmp_send
c_func
(paren
id|skb
comma
id|ICMP_DEST_UNREACH
comma
id|ICMP_FRAG_NEEDED
comma
id|htonl
c_func
(paren
id|mtu
)paren
)paren
suffix:semicolon
id|IP_VS_DBG_RL
c_func
(paren
l_string|&quot;ip_vs_bypass_xmit(): frag needed&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|tx_error
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Call ip_send_check because we are not sure it is called&n;&t; * after ip_defrag. Is copy-on-write needed?&n;&t; */
r_if
c_cond
(paren
id|unlikely
c_func
(paren
(paren
id|skb
op_assign
id|skb_share_check
c_func
(paren
id|skb
comma
id|GFP_ATOMIC
)paren
)paren
op_eq
l_int|NULL
)paren
)paren
(brace
id|ip_rt_put
c_func
(paren
id|rt
)paren
suffix:semicolon
r_return
id|NF_STOLEN
suffix:semicolon
)brace
id|ip_send_check
c_func
(paren
id|skb-&gt;nh.iph
)paren
suffix:semicolon
multiline_comment|/* drop old route */
id|dst_release
c_func
(paren
id|skb-&gt;dst
)paren
suffix:semicolon
id|skb-&gt;dst
op_assign
op_amp
id|rt-&gt;u.dst
suffix:semicolon
multiline_comment|/* Another hack: avoid icmp_send in ip_fragment */
id|skb-&gt;local_df
op_assign
l_int|1
suffix:semicolon
macro_line|#ifdef CONFIG_NETFILTER_DEBUG
id|skb-&gt;nf_debug
op_assign
l_int|0
suffix:semicolon
macro_line|#endif /* CONFIG_NETFILTER_DEBUG */
id|IP_VS_XMIT
c_func
(paren
id|skb
comma
id|rt
)paren
suffix:semicolon
id|LeaveFunction
c_func
(paren
l_int|10
)paren
suffix:semicolon
r_return
id|NF_STOLEN
suffix:semicolon
id|tx_error_icmp
suffix:colon
id|dst_link_failure
c_func
(paren
id|skb
)paren
suffix:semicolon
id|tx_error
suffix:colon
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
id|LeaveFunction
c_func
(paren
l_int|10
)paren
suffix:semicolon
r_return
id|NF_STOLEN
suffix:semicolon
)brace
multiline_comment|/*&n; *      NAT transmitter (only for outside-to-inside nat forwarding)&n; *      Not used for related ICMP&n; */
r_int
DECL|function|ip_vs_nat_xmit
id|ip_vs_nat_xmit
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|ip_vs_conn
op_star
id|cp
comma
r_struct
id|ip_vs_protocol
op_star
id|pp
)paren
(brace
r_struct
id|rtable
op_star
id|rt
suffix:semicolon
multiline_comment|/* Route to the other host */
r_int
id|mtu
suffix:semicolon
r_struct
id|iphdr
op_star
id|iph
op_assign
id|skb-&gt;nh.iph
suffix:semicolon
id|EnterFunction
c_func
(paren
l_int|10
)paren
suffix:semicolon
multiline_comment|/* check if it is a connection of no-client-port */
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|cp-&gt;flags
op_amp
id|IP_VS_CONN_F_NO_CPORT
)paren
)paren
(brace
id|__u16
id|pt
suffix:semicolon
r_if
c_cond
(paren
id|skb_copy_bits
c_func
(paren
id|skb
comma
id|iph-&gt;ihl
op_star
l_int|4
comma
op_amp
id|pt
comma
r_sizeof
(paren
id|pt
)paren
)paren
OL
l_int|0
)paren
r_goto
id|tx_error
suffix:semicolon
id|ip_vs_conn_fill_cport
c_func
(paren
id|cp
comma
id|pt
)paren
suffix:semicolon
id|IP_VS_DBG
c_func
(paren
l_int|10
comma
l_string|&quot;filled cport=%d&bslash;n&quot;
comma
id|ntohs
c_func
(paren
id|pt
)paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|rt
op_assign
id|__ip_vs_get_out_rt
c_func
(paren
id|cp
comma
id|RT_TOS
c_func
(paren
id|iph-&gt;tos
)paren
)paren
)paren
)paren
r_goto
id|tx_error_icmp
suffix:semicolon
multiline_comment|/* MTU checking */
id|mtu
op_assign
id|dst_pmtu
c_func
(paren
op_amp
id|rt-&gt;u.dst
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|skb-&gt;len
OG
id|mtu
)paren
op_logical_and
(paren
id|iph-&gt;frag_off
op_amp
id|__constant_htons
c_func
(paren
id|IP_DF
)paren
)paren
)paren
(brace
id|ip_rt_put
c_func
(paren
id|rt
)paren
suffix:semicolon
id|icmp_send
c_func
(paren
id|skb
comma
id|ICMP_DEST_UNREACH
comma
id|ICMP_FRAG_NEEDED
comma
id|htonl
c_func
(paren
id|mtu
)paren
)paren
suffix:semicolon
id|IP_VS_DBG_RL_PKT
c_func
(paren
l_int|0
comma
id|pp
comma
id|skb
comma
l_int|0
comma
l_string|&quot;ip_vs_nat_xmit(): frag needed for&quot;
)paren
suffix:semicolon
r_goto
id|tx_error
suffix:semicolon
)brace
multiline_comment|/* copy-on-write the packet before mangling it */
r_if
c_cond
(paren
op_logical_neg
id|ip_vs_make_skb_writable
c_func
(paren
op_amp
id|skb
comma
r_sizeof
(paren
r_struct
id|iphdr
)paren
)paren
)paren
r_goto
id|tx_error_put
suffix:semicolon
r_if
c_cond
(paren
id|skb_cow
c_func
(paren
id|skb
comma
id|rt-&gt;u.dst.dev-&gt;hard_header_len
)paren
)paren
r_goto
id|tx_error_put
suffix:semicolon
multiline_comment|/* drop old route */
id|dst_release
c_func
(paren
id|skb-&gt;dst
)paren
suffix:semicolon
id|skb-&gt;dst
op_assign
op_amp
id|rt-&gt;u.dst
suffix:semicolon
multiline_comment|/* mangle the packet */
r_if
c_cond
(paren
id|pp-&gt;dnat_handler
op_logical_and
op_logical_neg
id|pp
op_member_access_from_pointer
id|dnat_handler
c_func
(paren
op_amp
id|skb
comma
id|pp
comma
id|cp
)paren
)paren
r_goto
id|tx_error
suffix:semicolon
id|skb-&gt;nh.iph-&gt;daddr
op_assign
id|cp-&gt;daddr
suffix:semicolon
id|ip_send_check
c_func
(paren
id|skb-&gt;nh.iph
)paren
suffix:semicolon
id|IP_VS_DBG_PKT
c_func
(paren
l_int|10
comma
id|pp
comma
id|skb
comma
l_int|0
comma
l_string|&quot;After DNAT&quot;
)paren
suffix:semicolon
multiline_comment|/* FIXME: when application helper enlarges the packet and the length&n;&t;   is larger than the MTU of outgoing device, there will be still&n;&t;   MTU problem. */
multiline_comment|/* Another hack: avoid icmp_send in ip_fragment */
id|skb-&gt;local_df
op_assign
l_int|1
suffix:semicolon
macro_line|#ifdef CONFIG_NETFILTER_DEBUG
id|skb-&gt;nf_debug
op_assign
l_int|0
suffix:semicolon
macro_line|#endif /* CONFIG_NETFILTER_DEBUG */
id|IP_VS_XMIT
c_func
(paren
id|skb
comma
id|rt
)paren
suffix:semicolon
id|LeaveFunction
c_func
(paren
l_int|10
)paren
suffix:semicolon
r_return
id|NF_STOLEN
suffix:semicolon
id|tx_error_icmp
suffix:colon
id|dst_link_failure
c_func
(paren
id|skb
)paren
suffix:semicolon
id|tx_error
suffix:colon
id|LeaveFunction
c_func
(paren
l_int|10
)paren
suffix:semicolon
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
id|NF_STOLEN
suffix:semicolon
id|tx_error_put
suffix:colon
id|ip_rt_put
c_func
(paren
id|rt
)paren
suffix:semicolon
r_goto
id|tx_error
suffix:semicolon
)brace
multiline_comment|/*&n; *   IP Tunneling transmitter&n; *&n; *   This function encapsulates the packet in a new IP packet, its&n; *   destination will be set to cp-&gt;daddr. Most code of this function&n; *   is taken from ipip.c.&n; *&n; *   It is used in VS/TUN cluster. The load balancer selects a real&n; *   server from a cluster based on a scheduling algorithm,&n; *   encapsulates the request packet and forwards it to the selected&n; *   server. For example, all real servers are configured with&n; *   &quot;ifconfig tunl0 &lt;Virtual IP Address&gt; up&quot;. When the server receives&n; *   the encapsulated packet, it will decapsulate the packet, processe&n; *   the request and return the response packets directly to the client&n; *   without passing the load balancer. This can greatly increase the&n; *   scalability of virtual server.&n; *&n; *   Used for ANY protocol&n; */
r_int
DECL|function|ip_vs_tunnel_xmit
id|ip_vs_tunnel_xmit
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|ip_vs_conn
op_star
id|cp
comma
r_struct
id|ip_vs_protocol
op_star
id|pp
)paren
(brace
r_struct
id|rtable
op_star
id|rt
suffix:semicolon
multiline_comment|/* Route to the other host */
r_struct
id|net_device
op_star
id|tdev
suffix:semicolon
multiline_comment|/* Device to other host */
r_struct
id|iphdr
op_star
id|old_iph
op_assign
id|skb-&gt;nh.iph
suffix:semicolon
id|u8
id|tos
op_assign
id|old_iph-&gt;tos
suffix:semicolon
id|u16
id|df
op_assign
id|old_iph-&gt;frag_off
suffix:semicolon
r_struct
id|iphdr
op_star
id|iph
suffix:semicolon
multiline_comment|/* Our new IP header */
r_int
id|max_headroom
suffix:semicolon
multiline_comment|/* The extra header space needed */
r_int
id|mtu
suffix:semicolon
id|EnterFunction
c_func
(paren
l_int|10
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb-&gt;protocol
op_ne
id|__constant_htons
c_func
(paren
id|ETH_P_IP
)paren
)paren
(brace
id|IP_VS_DBG_RL
c_func
(paren
l_string|&quot;ip_vs_tunnel_xmit(): protocol error, &quot;
l_string|&quot;ETH_P_IP: %d, skb protocol: %d&bslash;n&quot;
comma
id|__constant_htons
c_func
(paren
id|ETH_P_IP
)paren
comma
id|skb-&gt;protocol
)paren
suffix:semicolon
r_goto
id|tx_error
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|rt
op_assign
id|__ip_vs_get_out_rt
c_func
(paren
id|cp
comma
id|RT_TOS
c_func
(paren
id|tos
)paren
)paren
)paren
)paren
r_goto
id|tx_error_icmp
suffix:semicolon
id|tdev
op_assign
id|rt-&gt;u.dst.dev
suffix:semicolon
id|mtu
op_assign
id|dst_pmtu
c_func
(paren
op_amp
id|rt-&gt;u.dst
)paren
op_minus
r_sizeof
(paren
r_struct
id|iphdr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mtu
OL
l_int|68
)paren
(brace
id|ip_rt_put
c_func
(paren
id|rt
)paren
suffix:semicolon
id|IP_VS_DBG_RL
c_func
(paren
l_string|&quot;ip_vs_tunnel_xmit(): mtu less than 68&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|tx_error
suffix:semicolon
)brace
r_if
c_cond
(paren
id|skb-&gt;dst
)paren
id|skb-&gt;dst-&gt;ops
op_member_access_from_pointer
id|update_pmtu
c_func
(paren
id|skb-&gt;dst
comma
id|mtu
)paren
suffix:semicolon
id|df
op_or_assign
(paren
id|old_iph-&gt;frag_off
op_amp
id|__constant_htons
c_func
(paren
id|IP_DF
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|old_iph-&gt;frag_off
op_amp
id|__constant_htons
c_func
(paren
id|IP_DF
)paren
)paren
op_logical_and
id|mtu
OL
id|ntohs
c_func
(paren
id|old_iph-&gt;tot_len
)paren
)paren
(brace
id|icmp_send
c_func
(paren
id|skb
comma
id|ICMP_DEST_UNREACH
comma
id|ICMP_FRAG_NEEDED
comma
id|htonl
c_func
(paren
id|mtu
)paren
)paren
suffix:semicolon
id|ip_rt_put
c_func
(paren
id|rt
)paren
suffix:semicolon
id|IP_VS_DBG_RL
c_func
(paren
l_string|&quot;ip_vs_tunnel_xmit(): frag needed&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|tx_error
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Okay, now see if we can stuff it in the buffer as-is.&n;&t; */
id|max_headroom
op_assign
id|LL_RESERVED_SPACE
c_func
(paren
id|tdev
)paren
op_plus
r_sizeof
(paren
r_struct
id|iphdr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb_headroom
c_func
(paren
id|skb
)paren
OL
id|max_headroom
op_logical_or
id|skb_cloned
c_func
(paren
id|skb
)paren
op_logical_or
id|skb_shared
c_func
(paren
id|skb
)paren
)paren
(brace
r_struct
id|sk_buff
op_star
id|new_skb
op_assign
id|skb_realloc_headroom
c_func
(paren
id|skb
comma
id|max_headroom
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|new_skb
)paren
(brace
id|ip_rt_put
c_func
(paren
id|rt
)paren
suffix:semicolon
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
id|IP_VS_ERR_RL
c_func
(paren
l_string|&quot;ip_vs_tunnel_xmit(): no memory&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|NF_STOLEN
suffix:semicolon
)brace
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
id|skb
op_assign
id|new_skb
suffix:semicolon
id|old_iph
op_assign
id|skb-&gt;nh.iph
suffix:semicolon
)brace
id|skb-&gt;h.raw
op_assign
(paren
r_void
op_star
)paren
id|old_iph
suffix:semicolon
multiline_comment|/* fix old IP header checksum */
id|ip_send_check
c_func
(paren
id|old_iph
)paren
suffix:semicolon
id|skb-&gt;nh.raw
op_assign
id|skb_push
c_func
(paren
id|skb
comma
r_sizeof
(paren
r_struct
id|iphdr
)paren
)paren
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
id|IPCB
c_func
(paren
id|skb
)paren
op_member_access_from_pointer
id|opt
)paren
)paren
suffix:semicolon
multiline_comment|/* drop old route */
id|dst_release
c_func
(paren
id|skb-&gt;dst
)paren
suffix:semicolon
id|skb-&gt;dst
op_assign
op_amp
id|rt-&gt;u.dst
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Push down and install the IPIP header.&n;&t; */
id|iph
op_assign
id|skb-&gt;nh.iph
suffix:semicolon
id|iph-&gt;version
op_assign
l_int|4
suffix:semicolon
id|iph-&gt;ihl
op_assign
r_sizeof
(paren
r_struct
id|iphdr
)paren
op_rshift
l_int|2
suffix:semicolon
id|iph-&gt;frag_off
op_assign
id|df
suffix:semicolon
id|iph-&gt;protocol
op_assign
id|IPPROTO_IPIP
suffix:semicolon
id|iph-&gt;tos
op_assign
id|tos
suffix:semicolon
id|iph-&gt;daddr
op_assign
id|rt-&gt;rt_dst
suffix:semicolon
id|iph-&gt;saddr
op_assign
id|rt-&gt;rt_src
suffix:semicolon
id|iph-&gt;ttl
op_assign
id|old_iph-&gt;ttl
suffix:semicolon
id|iph-&gt;tot_len
op_assign
id|htons
c_func
(paren
id|skb-&gt;len
)paren
suffix:semicolon
id|ip_select_ident
c_func
(paren
id|iph
comma
op_amp
id|rt-&gt;u.dst
comma
l_int|NULL
)paren
suffix:semicolon
id|ip_send_check
c_func
(paren
id|iph
)paren
suffix:semicolon
id|skb-&gt;ip_summed
op_assign
id|CHECKSUM_NONE
suffix:semicolon
multiline_comment|/* Another hack: avoid icmp_send in ip_fragment */
id|skb-&gt;local_df
op_assign
l_int|1
suffix:semicolon
macro_line|#ifdef CONFIG_NETFILTER_DEBUG
id|skb-&gt;nf_debug
op_assign
l_int|0
suffix:semicolon
macro_line|#endif /* CONFIG_NETFILTER_DEBUG */
id|IP_VS_XMIT
c_func
(paren
id|skb
comma
id|rt
)paren
suffix:semicolon
id|LeaveFunction
c_func
(paren
l_int|10
)paren
suffix:semicolon
r_return
id|NF_STOLEN
suffix:semicolon
id|tx_error_icmp
suffix:colon
id|dst_link_failure
c_func
(paren
id|skb
)paren
suffix:semicolon
id|tx_error
suffix:colon
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
id|LeaveFunction
c_func
(paren
l_int|10
)paren
suffix:semicolon
r_return
id|NF_STOLEN
suffix:semicolon
)brace
multiline_comment|/*&n; *      Direct Routing transmitter&n; *      Used for ANY protocol&n; */
r_int
DECL|function|ip_vs_dr_xmit
id|ip_vs_dr_xmit
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|ip_vs_conn
op_star
id|cp
comma
r_struct
id|ip_vs_protocol
op_star
id|pp
)paren
(brace
r_struct
id|rtable
op_star
id|rt
suffix:semicolon
multiline_comment|/* Route to the other host */
r_struct
id|iphdr
op_star
id|iph
op_assign
id|skb-&gt;nh.iph
suffix:semicolon
r_int
id|mtu
suffix:semicolon
id|EnterFunction
c_func
(paren
l_int|10
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|rt
op_assign
id|__ip_vs_get_out_rt
c_func
(paren
id|cp
comma
id|RT_TOS
c_func
(paren
id|iph-&gt;tos
)paren
)paren
)paren
)paren
r_goto
id|tx_error_icmp
suffix:semicolon
multiline_comment|/* MTU checking */
id|mtu
op_assign
id|dst_pmtu
c_func
(paren
op_amp
id|rt-&gt;u.dst
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|iph-&gt;frag_off
op_amp
id|__constant_htons
c_func
(paren
id|IP_DF
)paren
)paren
op_logical_and
id|skb-&gt;len
OG
id|mtu
)paren
(brace
id|icmp_send
c_func
(paren
id|skb
comma
id|ICMP_DEST_UNREACH
comma
id|ICMP_FRAG_NEEDED
comma
id|htonl
c_func
(paren
id|mtu
)paren
)paren
suffix:semicolon
id|ip_rt_put
c_func
(paren
id|rt
)paren
suffix:semicolon
id|IP_VS_DBG_RL
c_func
(paren
l_string|&quot;ip_vs_dr_xmit(): frag needed&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|tx_error
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Call ip_send_check because we are not sure it is called&n;&t; * after ip_defrag. Is copy-on-write needed?&n;&t; */
r_if
c_cond
(paren
id|unlikely
c_func
(paren
(paren
id|skb
op_assign
id|skb_share_check
c_func
(paren
id|skb
comma
id|GFP_ATOMIC
)paren
)paren
op_eq
l_int|NULL
)paren
)paren
(brace
id|ip_rt_put
c_func
(paren
id|rt
)paren
suffix:semicolon
r_return
id|NF_STOLEN
suffix:semicolon
)brace
id|ip_send_check
c_func
(paren
id|skb-&gt;nh.iph
)paren
suffix:semicolon
multiline_comment|/* drop old route */
id|dst_release
c_func
(paren
id|skb-&gt;dst
)paren
suffix:semicolon
id|skb-&gt;dst
op_assign
op_amp
id|rt-&gt;u.dst
suffix:semicolon
multiline_comment|/* Another hack: avoid icmp_send in ip_fragment */
id|skb-&gt;local_df
op_assign
l_int|1
suffix:semicolon
macro_line|#ifdef CONFIG_NETFILTER_DEBUG
id|skb-&gt;nf_debug
op_assign
l_int|0
suffix:semicolon
macro_line|#endif /* CONFIG_NETFILTER_DEBUG */
id|IP_VS_XMIT
c_func
(paren
id|skb
comma
id|rt
)paren
suffix:semicolon
id|LeaveFunction
c_func
(paren
l_int|10
)paren
suffix:semicolon
r_return
id|NF_STOLEN
suffix:semicolon
id|tx_error_icmp
suffix:colon
id|dst_link_failure
c_func
(paren
id|skb
)paren
suffix:semicolon
id|tx_error
suffix:colon
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
id|LeaveFunction
c_func
(paren
l_int|10
)paren
suffix:semicolon
r_return
id|NF_STOLEN
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;ICMP packet transmitter&n; *&t;called by the ip_vs_in_icmp&n; */
r_int
DECL|function|ip_vs_icmp_xmit
id|ip_vs_icmp_xmit
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|ip_vs_conn
op_star
id|cp
comma
r_struct
id|ip_vs_protocol
op_star
id|pp
comma
r_int
id|offset
)paren
(brace
r_struct
id|rtable
op_star
id|rt
suffix:semicolon
multiline_comment|/* Route to the other host */
r_int
id|mtu
suffix:semicolon
r_int
id|rc
suffix:semicolon
id|EnterFunction
c_func
(paren
l_int|10
)paren
suffix:semicolon
multiline_comment|/* The ICMP packet for VS/TUN, VS/DR and LOCALNODE will be&n;&t;   forwarded directly here, because there is no need to&n;&t;   translate address/port back */
r_if
c_cond
(paren
id|IP_VS_FWD_METHOD
c_func
(paren
id|cp
)paren
op_ne
id|IP_VS_CONN_F_MASQ
)paren
(brace
r_if
c_cond
(paren
id|cp-&gt;packet_xmit
)paren
id|rc
op_assign
id|cp
op_member_access_from_pointer
id|packet_xmit
c_func
(paren
id|skb
comma
id|cp
comma
id|pp
)paren
suffix:semicolon
r_else
id|rc
op_assign
id|NF_ACCEPT
suffix:semicolon
multiline_comment|/* do not touch skb anymore */
id|atomic_inc
c_func
(paren
op_amp
id|cp-&gt;in_pkts
)paren
suffix:semicolon
id|__ip_vs_conn_put
c_func
(paren
id|cp
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * mangle and send the packet here (only for VS/NAT)&n;&t; */
r_if
c_cond
(paren
op_logical_neg
(paren
id|rt
op_assign
id|__ip_vs_get_out_rt
c_func
(paren
id|cp
comma
id|RT_TOS
c_func
(paren
id|skb-&gt;nh.iph-&gt;tos
)paren
)paren
)paren
)paren
r_goto
id|tx_error_icmp
suffix:semicolon
multiline_comment|/* MTU checking */
id|mtu
op_assign
id|dst_pmtu
c_func
(paren
op_amp
id|rt-&gt;u.dst
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|skb-&gt;len
OG
id|mtu
)paren
op_logical_and
(paren
id|skb-&gt;nh.iph-&gt;frag_off
op_amp
id|__constant_htons
c_func
(paren
id|IP_DF
)paren
)paren
)paren
(brace
id|ip_rt_put
c_func
(paren
id|rt
)paren
suffix:semicolon
id|icmp_send
c_func
(paren
id|skb
comma
id|ICMP_DEST_UNREACH
comma
id|ICMP_FRAG_NEEDED
comma
id|htonl
c_func
(paren
id|mtu
)paren
)paren
suffix:semicolon
id|IP_VS_DBG_RL
c_func
(paren
l_string|&quot;ip_vs_in_icmp(): frag needed&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|tx_error
suffix:semicolon
)brace
multiline_comment|/* copy-on-write the packet before mangling it */
r_if
c_cond
(paren
op_logical_neg
id|ip_vs_make_skb_writable
c_func
(paren
op_amp
id|skb
comma
id|offset
)paren
)paren
r_goto
id|tx_error_put
suffix:semicolon
r_if
c_cond
(paren
id|skb_cow
c_func
(paren
id|skb
comma
id|rt-&gt;u.dst.dev-&gt;hard_header_len
)paren
)paren
r_goto
id|tx_error_put
suffix:semicolon
multiline_comment|/* drop the old route when skb is not shared */
id|dst_release
c_func
(paren
id|skb-&gt;dst
)paren
suffix:semicolon
id|skb-&gt;dst
op_assign
op_amp
id|rt-&gt;u.dst
suffix:semicolon
id|ip_vs_nat_icmp
c_func
(paren
id|skb
comma
id|pp
comma
id|cp
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* Another hack: avoid icmp_send in ip_fragment */
id|skb-&gt;local_df
op_assign
l_int|1
suffix:semicolon
macro_line|#ifdef CONFIG_NETFILTER_DEBUG
id|skb-&gt;nf_debug
op_assign
l_int|0
suffix:semicolon
macro_line|#endif /* CONFIG_NETFILTER_DEBUG */
id|IP_VS_XMIT
c_func
(paren
id|skb
comma
id|rt
)paren
suffix:semicolon
id|rc
op_assign
id|NF_STOLEN
suffix:semicolon
r_goto
id|out
suffix:semicolon
id|tx_error_icmp
suffix:colon
id|dst_link_failure
c_func
(paren
id|skb
)paren
suffix:semicolon
id|tx_error
suffix:colon
id|dev_kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
id|rc
op_assign
id|NF_STOLEN
suffix:semicolon
id|out
suffix:colon
id|LeaveFunction
c_func
(paren
l_int|10
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
id|tx_error_put
suffix:colon
id|ip_rt_put
c_func
(paren
id|rt
)paren
suffix:semicolon
r_goto
id|tx_error
suffix:semicolon
)brace
eof
