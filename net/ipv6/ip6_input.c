multiline_comment|/*&n; *&t;IPv6 input&n; *&t;Linux INET6 implementation &n; *&n; *&t;Authors:&n; *&t;Pedro Roque&t;&t;&lt;roque@di.fc.ul.pt&gt;&n; *&t;Ian P. Morris&t;&t;&lt;I.P.Morris@soton.ac.uk&gt;&n; *&n; *&t;$Id: ip6_input.c,v 1.19 2000/12/13 18:31:50 davem Exp $&n; *&n; *&t;Based in linux/net/ipv4/ip_input.c&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *      modify it under the terms of the GNU General Public License&n; *      as published by the Free Software Foundation; either version&n; *      2 of the License, or (at your option) any later version.&n; */
multiline_comment|/* Changes&n; *&n; * &t;Mitsuru KANDA @USAGI and&n; * &t;YOSHIFUJI Hideaki @USAGI: Remove ipv6_parse_exthdrs().&n; */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/sockios.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/net.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/in6.h&gt;
macro_line|#include &lt;linux/icmpv6.h&gt;
macro_line|#include &lt;linux/netfilter.h&gt;
macro_line|#include &lt;linux/netfilter_ipv6.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;net/snmp.h&gt;
macro_line|#include &lt;net/ipv6.h&gt;
macro_line|#include &lt;net/protocol.h&gt;
macro_line|#include &lt;net/transp_v6.h&gt;
macro_line|#include &lt;net/rawv6.h&gt;
macro_line|#include &lt;net/ndisc.h&gt;
macro_line|#include &lt;net/ip6_route.h&gt;
macro_line|#include &lt;net/addrconf.h&gt;
macro_line|#include &lt;net/xfrm.h&gt;
DECL|function|ip6_rcv_finish
r_static
r_inline
r_int
id|ip6_rcv_finish
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_if
c_cond
(paren
id|skb-&gt;dst
op_eq
l_int|NULL
)paren
id|ip6_route_input
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
id|dst_input
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
DECL|function|ipv6_rcv
r_int
id|ipv6_rcv
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|net_device
op_star
id|dev
comma
r_struct
id|packet_type
op_star
id|pt
)paren
(brace
r_struct
id|ipv6hdr
op_star
id|hdr
suffix:semicolon
id|u32
id|pkt_len
suffix:semicolon
r_if
c_cond
(paren
id|skb-&gt;pkt_type
op_eq
id|PACKET_OTHERHOST
)paren
r_goto
id|drop
suffix:semicolon
id|IP6_INC_STATS_BH
c_func
(paren
id|Ip6InReceives
)paren
suffix:semicolon
r_if
c_cond
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
(brace
id|IP6_INC_STATS_BH
c_func
(paren
id|Ip6InDiscards
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/* Store incoming device index. When the packet will&n;&t;   be queued, we cannot refer to skb-&gt;dev anymore.&n;&t; */
(paren
(paren
r_struct
id|inet6_skb_parm
op_star
)paren
id|skb-&gt;cb
)paren
op_member_access_from_pointer
id|iif
op_assign
id|dev-&gt;ifindex
suffix:semicolon
r_if
c_cond
(paren
id|skb-&gt;len
OL
r_sizeof
(paren
r_struct
id|ipv6hdr
)paren
)paren
r_goto
id|err
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pskb_may_pull
c_func
(paren
id|skb
comma
r_sizeof
(paren
r_struct
id|ipv6hdr
)paren
)paren
)paren
(brace
id|IP6_INC_STATS_BH
c_func
(paren
id|Ip6InHdrErrors
)paren
suffix:semicolon
r_goto
id|drop
suffix:semicolon
)brace
id|hdr
op_assign
id|skb-&gt;nh.ipv6h
suffix:semicolon
r_if
c_cond
(paren
id|hdr-&gt;version
op_ne
l_int|6
)paren
r_goto
id|err
suffix:semicolon
id|pkt_len
op_assign
id|ntohs
c_func
(paren
id|hdr-&gt;payload_len
)paren
suffix:semicolon
multiline_comment|/* pkt_len may be zero if Jumbo payload option is present */
r_if
c_cond
(paren
id|pkt_len
op_logical_or
id|hdr-&gt;nexthdr
op_ne
id|NEXTHDR_HOP
)paren
(brace
r_if
c_cond
(paren
id|pkt_len
op_plus
r_sizeof
(paren
r_struct
id|ipv6hdr
)paren
OG
id|skb-&gt;len
)paren
r_goto
id|truncated
suffix:semicolon
r_if
c_cond
(paren
id|pkt_len
op_plus
r_sizeof
(paren
r_struct
id|ipv6hdr
)paren
OL
id|skb-&gt;len
)paren
(brace
r_if
c_cond
(paren
id|__pskb_trim
c_func
(paren
id|skb
comma
id|pkt_len
op_plus
r_sizeof
(paren
r_struct
id|ipv6hdr
)paren
)paren
)paren
(brace
id|IP6_INC_STATS_BH
c_func
(paren
id|Ip6InHdrErrors
)paren
suffix:semicolon
r_goto
id|drop
suffix:semicolon
)brace
id|hdr
op_assign
id|skb-&gt;nh.ipv6h
suffix:semicolon
r_if
c_cond
(paren
id|skb-&gt;ip_summed
op_eq
id|CHECKSUM_HW
)paren
id|skb-&gt;ip_summed
op_assign
id|CHECKSUM_NONE
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|hdr-&gt;nexthdr
op_eq
id|NEXTHDR_HOP
)paren
(brace
id|skb-&gt;h.raw
op_assign
(paren
id|u8
op_star
)paren
(paren
id|hdr
op_plus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ipv6_parse_hopopts
c_func
(paren
id|skb
comma
m_offsetof
(paren
r_struct
id|ipv6hdr
comma
id|nexthdr
)paren
)paren
OL
l_int|0
)paren
(brace
id|IP6_INC_STATS_BH
c_func
(paren
id|Ip6InHdrErrors
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|hdr
op_assign
id|skb-&gt;nh.ipv6h
suffix:semicolon
)brace
r_return
id|NF_HOOK
c_func
(paren
id|PF_INET6
comma
id|NF_IP6_PRE_ROUTING
comma
id|skb
comma
id|dev
comma
l_int|NULL
comma
id|ip6_rcv_finish
)paren
suffix:semicolon
id|truncated
suffix:colon
id|IP6_INC_STATS_BH
c_func
(paren
id|Ip6InTruncatedPkts
)paren
suffix:semicolon
id|err
suffix:colon
id|IP6_INC_STATS_BH
c_func
(paren
id|Ip6InHdrErrors
)paren
suffix:semicolon
id|drop
suffix:colon
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
id|out
suffix:colon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Deliver the packet to the host&n; */
DECL|function|ip6_input_finish
r_static
r_inline
r_int
id|ip6_input_finish
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|inet6_protocol
op_star
id|ipprot
suffix:semicolon
r_struct
id|sock
op_star
id|raw_sk
suffix:semicolon
r_int
r_int
id|nhoff
suffix:semicolon
r_int
id|nexthdr
suffix:semicolon
id|u8
id|hash
suffix:semicolon
r_int
id|cksum_sub
op_assign
l_int|0
suffix:semicolon
id|skb-&gt;h.raw
op_assign
id|skb-&gt;nh.raw
op_plus
r_sizeof
(paren
r_struct
id|ipv6hdr
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Parse extension headers&n;&t; */
id|nexthdr
op_assign
id|skb-&gt;nh.ipv6h-&gt;nexthdr
suffix:semicolon
id|nhoff
op_assign
m_offsetof
(paren
r_struct
id|ipv6hdr
comma
id|nexthdr
)paren
suffix:semicolon
multiline_comment|/* Skip hop-by-hop options, they are already parsed. */
r_if
c_cond
(paren
id|nexthdr
op_eq
id|NEXTHDR_HOP
)paren
(brace
id|nhoff
op_assign
r_sizeof
(paren
r_struct
id|ipv6hdr
)paren
suffix:semicolon
id|nexthdr
op_assign
id|skb-&gt;h.raw
(braket
l_int|0
)braket
suffix:semicolon
id|skb-&gt;h.raw
op_add_assign
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
suffix:semicolon
)brace
id|rcu_read_lock
c_func
(paren
)paren
suffix:semicolon
id|resubmit
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|pskb_pull
c_func
(paren
id|skb
comma
id|skb-&gt;h.raw
op_minus
id|skb-&gt;data
)paren
)paren
r_goto
id|discard
suffix:semicolon
id|nexthdr
op_assign
id|skb-&gt;nh.raw
(braket
id|nhoff
)braket
suffix:semicolon
id|raw_sk
op_assign
id|sk_head
c_func
(paren
op_amp
id|raw_v6_htable
(braket
id|nexthdr
op_amp
(paren
id|MAX_INET_PROTOS
op_minus
l_int|1
)paren
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|raw_sk
)paren
id|ipv6_raw_deliver
c_func
(paren
id|skb
comma
id|nexthdr
)paren
suffix:semicolon
id|hash
op_assign
id|nexthdr
op_amp
(paren
id|MAX_INET_PROTOS
op_minus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ipprot
op_assign
id|inet6_protos
(braket
id|hash
)braket
)paren
op_ne
l_int|NULL
)paren
(brace
r_int
id|ret
suffix:semicolon
id|smp_read_barrier_depends
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ipprot-&gt;flags
op_amp
id|INET6_PROTO_FINAL
)paren
(brace
r_struct
id|ipv6hdr
op_star
id|hdr
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cksum_sub
op_logical_and
id|skb-&gt;ip_summed
op_eq
id|CHECKSUM_HW
)paren
(brace
id|skb-&gt;csum
op_assign
id|csum_sub
c_func
(paren
id|skb-&gt;csum
comma
id|csum_partial
c_func
(paren
id|skb-&gt;nh.raw
comma
id|skb-&gt;h.raw
op_minus
id|skb-&gt;nh.raw
comma
l_int|0
)paren
)paren
suffix:semicolon
id|cksum_sub
op_increment
suffix:semicolon
)brace
id|hdr
op_assign
id|skb-&gt;nh.ipv6h
suffix:semicolon
r_if
c_cond
(paren
id|ipv6_addr_is_multicast
c_func
(paren
op_amp
id|hdr-&gt;daddr
)paren
op_logical_and
op_logical_neg
id|ipv6_chk_mcast_addr
c_func
(paren
id|skb-&gt;dev
comma
op_amp
id|hdr-&gt;daddr
comma
op_amp
id|hdr-&gt;saddr
)paren
op_logical_and
op_logical_neg
id|ipv6_is_mld
c_func
(paren
id|skb
comma
id|nexthdr
)paren
)paren
r_goto
id|discard
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|ipprot-&gt;flags
op_amp
id|INET6_PROTO_NOPOLICY
)paren
op_logical_and
op_logical_neg
id|xfrm6_policy_check
c_func
(paren
l_int|NULL
comma
id|XFRM_POLICY_IN
comma
id|skb
)paren
)paren
r_goto
id|discard
suffix:semicolon
id|ret
op_assign
id|ipprot
op_member_access_from_pointer
id|handler
c_func
(paren
op_amp
id|skb
comma
op_amp
id|nhoff
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OG
l_int|0
)paren
r_goto
id|resubmit
suffix:semicolon
r_else
r_if
c_cond
(paren
id|ret
op_eq
l_int|0
)paren
id|IP6_INC_STATS_BH
c_func
(paren
id|Ip6InDelivers
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
op_logical_neg
id|raw_sk
)paren
(brace
r_if
c_cond
(paren
id|xfrm6_policy_check
c_func
(paren
l_int|NULL
comma
id|XFRM_POLICY_IN
comma
id|skb
)paren
)paren
(brace
id|IP6_INC_STATS_BH
c_func
(paren
id|Ip6InUnknownProtos
)paren
suffix:semicolon
id|icmpv6_param_prob
c_func
(paren
id|skb
comma
id|ICMPV6_UNK_NEXTHDR
comma
id|nhoff
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
id|IP6_INC_STATS_BH
c_func
(paren
id|Ip6InDelivers
)paren
suffix:semicolon
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
)brace
id|rcu_read_unlock
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|discard
suffix:colon
id|IP6_INC_STATS_BH
c_func
(paren
id|Ip6InDiscards
)paren
suffix:semicolon
id|rcu_read_unlock
c_func
(paren
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
DECL|function|ip6_input
r_int
id|ip6_input
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_return
id|NF_HOOK
c_func
(paren
id|PF_INET6
comma
id|NF_IP6_LOCAL_IN
comma
id|skb
comma
id|skb-&gt;dev
comma
l_int|NULL
comma
id|ip6_input_finish
)paren
suffix:semicolon
)brace
DECL|function|ip6_mc_input
r_int
id|ip6_mc_input
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|ipv6hdr
op_star
id|hdr
suffix:semicolon
r_int
id|deliver
suffix:semicolon
id|IP6_INC_STATS_BH
c_func
(paren
id|Ip6InMcastPkts
)paren
suffix:semicolon
id|hdr
op_assign
id|skb-&gt;nh.ipv6h
suffix:semicolon
id|deliver
op_assign
id|likely
c_func
(paren
op_logical_neg
(paren
id|skb-&gt;dev-&gt;flags
op_amp
(paren
id|IFF_PROMISC
op_or
id|IFF_ALLMULTI
)paren
)paren
)paren
op_logical_or
id|ipv6_chk_mcast_addr
c_func
(paren
id|skb-&gt;dev
comma
op_amp
id|hdr-&gt;daddr
comma
l_int|NULL
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *&t;IPv6 multicast router mode isnt currently supported.&n;&t; */
macro_line|#if 0
r_if
c_cond
(paren
id|ipv6_config.multicast_route
)paren
(brace
r_int
id|addr_type
suffix:semicolon
id|addr_type
op_assign
id|ipv6_addr_type
c_func
(paren
op_amp
id|hdr-&gt;daddr
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|addr_type
op_amp
(paren
id|IPV6_ADDR_LOOPBACK
op_or
id|IPV6_ADDR_LINKLOCAL
)paren
)paren
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb2
suffix:semicolon
r_struct
id|dst_entry
op_star
id|dst
suffix:semicolon
id|dst
op_assign
id|skb-&gt;dst
suffix:semicolon
r_if
c_cond
(paren
id|deliver
)paren
(brace
id|skb2
op_assign
id|skb_clone
c_func
(paren
id|skb
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
id|dst_output
c_func
(paren
id|skb2
)paren
suffix:semicolon
)brace
r_else
(brace
id|dst_output
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
)brace
macro_line|#endif
r_if
c_cond
(paren
id|likely
c_func
(paren
id|deliver
)paren
)paren
(brace
id|ip6_input
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* discard */
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
eof
