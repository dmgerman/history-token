multiline_comment|/*&n; *&t;Extension Header handling for IPv6&n; *&t;Linux INET6 implementation&n; *&n; *&t;Authors:&n; *&t;Pedro Roque&t;&t;&lt;roque@di.fc.ul.pt&gt;&n; *&t;Andi Kleen&t;&t;&lt;ak@muc.de&gt;&n; *&t;Alexey Kuznetsov&t;&lt;kuznet@ms2.inr.ac.ru&gt;&n; *&n; *&t;$Id: exthdrs.c,v 1.13 2001/06/19 15:58:56 davem Exp $&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *      modify it under the terms of the GNU General Public License&n; *      as published by the Free Software Foundation; either version&n; *      2 of the License, or (at your option) any later version.&n; */
multiline_comment|/* Changes:&n; *&t;yoshfuji&t;&t;: ensure not to overrun while parsing &n; *&t;&t;&t;&t;  tlv options.&n; *&t;Mitsuru KANDA @USAGI and: Remove ipv6_parse_exthdrs().&n; *&t;YOSHIFUJI Hideaki @USAGI  Register inbound extension header&n; *&t;&t;&t;&t;  handlers as inet6_protocol{}.&n; */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/sockios.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/net.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/in6.h&gt;
macro_line|#include &lt;linux/icmpv6.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;net/snmp.h&gt;
macro_line|#include &lt;net/ipv6.h&gt;
macro_line|#include &lt;net/protocol.h&gt;
macro_line|#include &lt;net/transp_v6.h&gt;
macro_line|#include &lt;net/rawv6.h&gt;
macro_line|#include &lt;net/ndisc.h&gt;
macro_line|#include &lt;net/ip6_route.h&gt;
macro_line|#include &lt;net/addrconf.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
multiline_comment|/*&n; *&t;Parsing tlv encoded headers.&n; *&n; *&t;Parsing function &quot;func&quot; returns 1, if parsing succeed&n; *&t;and 0, if it failed.&n; *&t;It MUST NOT touch skb-&gt;h.&n; */
DECL|struct|tlvtype_proc
r_struct
id|tlvtype_proc
(brace
DECL|member|type
r_int
id|type
suffix:semicolon
DECL|member|func
r_int
(paren
op_star
id|func
)paren
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_int
id|offset
)paren
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*********************&n;  Generic functions&n; *********************/
multiline_comment|/* An unknown option is detected, decide what to do */
DECL|function|ip6_tlvopt_unknown
r_static
r_int
id|ip6_tlvopt_unknown
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_int
id|optoff
)paren
(brace
r_switch
c_cond
(paren
(paren
id|skb-&gt;nh.raw
(braket
id|optoff
)braket
op_amp
l_int|0xC0
)paren
op_rshift
l_int|6
)paren
(brace
r_case
l_int|0
suffix:colon
multiline_comment|/* ignore */
r_return
l_int|1
suffix:semicolon
r_case
l_int|1
suffix:colon
multiline_comment|/* drop packet */
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
multiline_comment|/* Send ICMP if not a multicast address and drop packet */
multiline_comment|/* Actually, it is redundant check. icmp_send&n;&t;&t;   will recheck in any case.&n;&t;&t; */
r_if
c_cond
(paren
id|ipv6_addr_is_multicast
c_func
(paren
op_amp
id|skb-&gt;nh.ipv6h-&gt;daddr
)paren
)paren
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
multiline_comment|/* send ICMP PARM PROB regardless and drop packet */
id|icmpv6_param_prob
c_func
(paren
id|skb
comma
id|ICMPV6_UNK_OPTION
comma
id|optoff
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
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
multiline_comment|/* Parse tlv encoded option header (hop-by-hop or destination) */
DECL|function|ip6_parse_tlv
r_static
r_int
id|ip6_parse_tlv
c_func
(paren
r_struct
id|tlvtype_proc
op_star
id|procs
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|tlvtype_proc
op_star
id|curr
suffix:semicolon
r_int
id|off
op_assign
id|skb-&gt;h.raw
op_minus
id|skb-&gt;nh.raw
suffix:semicolon
r_int
id|len
op_assign
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
suffix:semicolon
r_if
c_cond
(paren
(paren
id|skb-&gt;h.raw
op_plus
id|len
)paren
op_minus
id|skb-&gt;data
OG
id|skb_headlen
c_func
(paren
id|skb
)paren
)paren
r_goto
id|bad
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
r_int
id|optlen
op_assign
id|skb-&gt;nh.raw
(braket
id|off
op_plus
l_int|1
)braket
op_plus
l_int|2
suffix:semicolon
r_switch
c_cond
(paren
id|skb-&gt;nh.raw
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
r_case
id|IPV6_TLV_PADN
suffix:colon
r_break
suffix:semicolon
r_default
suffix:colon
(brace
)brace
multiline_comment|/* Other TLV code so scan list */
r_if
c_cond
(paren
id|optlen
OG
id|len
)paren
r_goto
id|bad
suffix:semicolon
r_for
c_loop
(paren
id|curr
op_assign
id|procs
suffix:semicolon
id|curr-&gt;type
op_ge
l_int|0
suffix:semicolon
id|curr
op_increment
)paren
(brace
r_if
c_cond
(paren
id|curr-&gt;type
op_eq
id|skb-&gt;nh.raw
(braket
id|off
)braket
)paren
(brace
multiline_comment|/* type specific length/alignment &n;&t;&t;&t;&t;&t;   checks will be perfomed in the &n;&t;&t;&t;&t;&t;   func(). */
r_if
c_cond
(paren
id|curr
op_member_access_from_pointer
id|func
c_func
(paren
id|skb
comma
id|off
)paren
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|curr-&gt;type
OL
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|ip6_tlvopt_unknown
c_func
(paren
id|skb
comma
id|off
)paren
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
)brace
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
multiline_comment|/*****************************&n;  Destination options header.&n; *****************************/
DECL|variable|tlvprocdestopt_lst
r_static
r_struct
id|tlvtype_proc
id|tlvprocdestopt_lst
(braket
)braket
op_assign
(brace
multiline_comment|/* No destination options are defined now */
(brace
op_minus
l_int|1
comma
l_int|NULL
)brace
)brace
suffix:semicolon
DECL|function|ipv6_destopt_rcv
r_static
r_int
id|ipv6_destopt_rcv
c_func
(paren
r_struct
id|sk_buff
op_star
op_star
id|skbp
comma
r_int
r_int
op_star
id|nhoffp
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb
op_assign
op_star
id|skbp
suffix:semicolon
r_struct
id|inet6_skb_parm
op_star
id|opt
op_assign
(paren
r_struct
id|inet6_skb_parm
op_star
)paren
id|skb-&gt;cb
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
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|opt-&gt;dst1
op_assign
id|skb-&gt;h.raw
op_minus
id|skb-&gt;nh.raw
suffix:semicolon
r_if
c_cond
(paren
id|ip6_parse_tlv
c_func
(paren
id|tlvprocdestopt_lst
comma
id|skb
)paren
)paren
(brace
id|skb-&gt;h.raw
op_add_assign
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
suffix:semicolon
op_star
id|nhoffp
op_assign
id|opt-&gt;dst1
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
DECL|variable|destopt_protocol
r_static
r_struct
id|inet6_protocol
id|destopt_protocol
op_assign
(brace
dot
id|handler
op_assign
id|ipv6_destopt_rcv
comma
dot
id|flags
op_assign
id|INET6_PROTO_NOPOLICY
comma
)brace
suffix:semicolon
DECL|function|ipv6_destopt_init
r_void
id|__init
id|ipv6_destopt_init
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|inet6_add_protocol
c_func
(paren
op_amp
id|destopt_protocol
comma
id|IPPROTO_DSTOPTS
)paren
OL
l_int|0
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;ipv6_destopt_init: Could not register protocol&bslash;n&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/********************************&n;  NONE header. No data in packet.&n; ********************************/
DECL|function|ipv6_nodata_rcv
r_static
r_int
id|ipv6_nodata_rcv
c_func
(paren
r_struct
id|sk_buff
op_star
op_star
id|skbp
comma
r_int
r_int
op_star
id|nhoffp
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb
op_assign
op_star
id|skbp
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
DECL|variable|nodata_protocol
r_static
r_struct
id|inet6_protocol
id|nodata_protocol
op_assign
(brace
dot
id|handler
op_assign
id|ipv6_nodata_rcv
comma
dot
id|flags
op_assign
id|INET6_PROTO_NOPOLICY
comma
)brace
suffix:semicolon
DECL|function|ipv6_nodata_init
r_void
id|__init
id|ipv6_nodata_init
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|inet6_add_protocol
c_func
(paren
op_amp
id|nodata_protocol
comma
id|IPPROTO_NONE
)paren
OL
l_int|0
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;ipv6_nodata_init: Could not register protocol&bslash;n&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/********************************&n;  Routing header.&n; ********************************/
DECL|function|ipv6_rthdr_rcv
r_static
r_int
id|ipv6_rthdr_rcv
c_func
(paren
r_struct
id|sk_buff
op_star
op_star
id|skbp
comma
r_int
r_int
op_star
id|nhoffp
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb
op_assign
op_star
id|skbp
suffix:semicolon
r_struct
id|inet6_skb_parm
op_star
id|opt
op_assign
(paren
r_struct
id|inet6_skb_parm
op_star
)paren
id|skb-&gt;cb
suffix:semicolon
r_struct
id|in6_addr
op_star
id|addr
suffix:semicolon
r_struct
id|in6_addr
id|daddr
suffix:semicolon
r_int
id|addr_type
suffix:semicolon
r_int
id|n
comma
id|i
suffix:semicolon
r_struct
id|ipv6_rt_hdr
op_star
id|hdr
suffix:semicolon
r_struct
id|rt0_hdr
op_star
id|rthdr
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
id|IP6_INC_STATS_BH
c_func
(paren
id|Ip6InHdrErrors
)paren
suffix:semicolon
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|hdr
op_assign
(paren
r_struct
id|ipv6_rt_hdr
op_star
)paren
id|skb-&gt;h.raw
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ipv6_addr_type
c_func
(paren
op_amp
id|skb-&gt;nh.ipv6h-&gt;daddr
)paren
op_amp
id|IPV6_ADDR_MULTICAST
)paren
op_logical_or
id|skb-&gt;pkt_type
op_ne
id|PACKET_HOST
)paren
(brace
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|looped_back
suffix:colon
r_if
c_cond
(paren
id|hdr-&gt;segments_left
op_eq
l_int|0
)paren
(brace
id|opt-&gt;srcrt
op_assign
id|skb-&gt;h.raw
op_minus
id|skb-&gt;nh.raw
suffix:semicolon
id|skb-&gt;h.raw
op_add_assign
(paren
id|hdr-&gt;hdrlen
op_plus
l_int|1
)paren
op_lshift
l_int|3
suffix:semicolon
id|opt-&gt;dst0
op_assign
id|opt-&gt;dst1
suffix:semicolon
id|opt-&gt;dst1
op_assign
l_int|0
suffix:semicolon
op_star
id|nhoffp
op_assign
(paren
op_amp
id|hdr-&gt;nexthdr
)paren
op_minus
id|skb-&gt;nh.raw
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|hdr-&gt;type
op_ne
id|IPV6_SRCRT_TYPE_0
)paren
(brace
id|icmpv6_param_prob
c_func
(paren
id|skb
comma
id|ICMPV6_HDR_FIELD
comma
(paren
op_amp
id|hdr-&gt;type
)paren
op_minus
id|skb-&gt;nh.raw
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|hdr-&gt;hdrlen
op_amp
l_int|0x01
)paren
(brace
id|icmpv6_param_prob
c_func
(paren
id|skb
comma
id|ICMPV6_HDR_FIELD
comma
(paren
op_amp
id|hdr-&gt;hdrlen
)paren
op_minus
id|skb-&gt;nh.raw
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n;&t; *&t;This is the routing header forwarding algorithm from&n;&t; *&t;RFC 2460, page 16.&n;&t; */
id|n
op_assign
id|hdr-&gt;hdrlen
op_rshift
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|hdr-&gt;segments_left
OG
id|n
)paren
(brace
id|icmpv6_param_prob
c_func
(paren
id|skb
comma
id|ICMPV6_HDR_FIELD
comma
(paren
op_amp
id|hdr-&gt;segments_left
)paren
op_minus
id|skb-&gt;nh.raw
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/* We are about to mangle packet header. Be careful!&n;&t;   Do not damage packets queued somewhere.&n;&t; */
r_if
c_cond
(paren
id|skb_cloned
c_func
(paren
id|skb
)paren
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb2
op_assign
id|skb_copy
c_func
(paren
id|skb
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb2
op_eq
l_int|NULL
)paren
r_return
op_minus
l_int|1
suffix:semicolon
op_star
id|skbp
op_assign
id|skb
op_assign
id|skb2
suffix:semicolon
id|opt
op_assign
(paren
r_struct
id|inet6_skb_parm
op_star
)paren
id|skb2-&gt;cb
suffix:semicolon
id|hdr
op_assign
(paren
r_struct
id|ipv6_rt_hdr
op_star
)paren
id|skb2-&gt;h.raw
suffix:semicolon
)brace
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
id|i
op_assign
id|n
op_minus
op_decrement
id|hdr-&gt;segments_left
suffix:semicolon
id|rthdr
op_assign
(paren
r_struct
id|rt0_hdr
op_star
)paren
id|hdr
suffix:semicolon
id|addr
op_assign
id|rthdr-&gt;addr
suffix:semicolon
id|addr
op_add_assign
id|i
op_minus
l_int|1
suffix:semicolon
id|addr_type
op_assign
id|ipv6_addr_type
c_func
(paren
id|addr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|addr_type
op_amp
id|IPV6_ADDR_MULTICAST
)paren
(brace
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|ipv6_addr_copy
c_func
(paren
op_amp
id|daddr
comma
id|addr
)paren
suffix:semicolon
id|ipv6_addr_copy
c_func
(paren
id|addr
comma
op_amp
id|skb-&gt;nh.ipv6h-&gt;daddr
)paren
suffix:semicolon
id|ipv6_addr_copy
c_func
(paren
op_amp
id|skb-&gt;nh.ipv6h-&gt;daddr
comma
op_amp
id|daddr
)paren
suffix:semicolon
id|dst_release
c_func
(paren
id|xchg
c_func
(paren
op_amp
id|skb-&gt;dst
comma
l_int|NULL
)paren
)paren
suffix:semicolon
id|ip6_route_input
c_func
(paren
id|skb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb-&gt;dst-&gt;error
)paren
(brace
id|dst_input
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|skb-&gt;dst-&gt;dev-&gt;flags
op_amp
id|IFF_LOOPBACK
)paren
(brace
r_if
c_cond
(paren
id|skb-&gt;nh.ipv6h-&gt;hop_limit
op_le
l_int|1
)paren
(brace
id|icmpv6_send
c_func
(paren
id|skb
comma
id|ICMPV6_TIME_EXCEED
comma
id|ICMPV6_EXC_HOPLIMIT
comma
l_int|0
comma
id|skb-&gt;dev
)paren
suffix:semicolon
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|skb-&gt;nh.ipv6h-&gt;hop_limit
op_decrement
suffix:semicolon
r_goto
id|looped_back
suffix:semicolon
)brace
id|dst_input
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
DECL|variable|rthdr_protocol
r_static
r_struct
id|inet6_protocol
id|rthdr_protocol
op_assign
(brace
dot
id|handler
op_assign
id|ipv6_rthdr_rcv
comma
dot
id|flags
op_assign
id|INET6_PROTO_NOPOLICY
comma
)brace
suffix:semicolon
DECL|function|ipv6_rthdr_init
r_void
id|__init
id|ipv6_rthdr_init
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|inet6_add_protocol
c_func
(paren
op_amp
id|rthdr_protocol
comma
id|IPPROTO_ROUTING
)paren
OL
l_int|0
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;ipv6_rthdr_init: Could not register protocol&bslash;n&quot;
)paren
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n;   This function inverts received rthdr.&n;   NOTE: specs allow to make it automatically only if&n;   packet authenticated.&n;&n;   I will not discuss it here (though, I am really pissed off at&n;   this stupid requirement making rthdr idea useless)&n;&n;   Actually, it creates severe problems  for us.&n;   Embryonic requests has no associated sockets,&n;   so that user have no control over it and&n;   cannot not only to set reply options, but&n;   even to know, that someone wants to connect&n;   without success. :-(&n;&n;   For now we need to test the engine, so that I created&n;   temporary (or permanent) backdoor.&n;   If listening socket set IPV6_RTHDR to 2, then we invert header.&n;                                                   --ANK (980729)&n; */
r_struct
id|ipv6_txoptions
op_star
DECL|function|ipv6_invert_rthdr
id|ipv6_invert_rthdr
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_struct
id|ipv6_rt_hdr
op_star
id|hdr
)paren
(brace
multiline_comment|/* Received rthdr:&n;&n;&t;   [ H1 -&gt; H2 -&gt; ... H_prev ]  daddr=ME&n;&n;&t;   Inverted result:&n;&t;   [ H_prev -&gt; ... -&gt; H1 ] daddr =sender&n;&n;&t;   Note, that IP output engine will rewrite this rthdr&n;&t;   by rotating it left by one addr.&n;&t; */
r_int
id|n
comma
id|i
suffix:semicolon
r_struct
id|rt0_hdr
op_star
id|rthdr
op_assign
(paren
r_struct
id|rt0_hdr
op_star
)paren
id|hdr
suffix:semicolon
r_struct
id|rt0_hdr
op_star
id|irthdr
suffix:semicolon
r_struct
id|ipv6_txoptions
op_star
id|opt
suffix:semicolon
r_int
id|hdrlen
op_assign
id|ipv6_optlen
c_func
(paren
id|hdr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hdr-&gt;segments_left
op_logical_or
id|hdr-&gt;type
op_ne
id|IPV6_SRCRT_TYPE_0
op_logical_or
id|hdr-&gt;hdrlen
op_amp
l_int|0x01
)paren
r_return
l_int|NULL
suffix:semicolon
id|n
op_assign
id|hdr-&gt;hdrlen
op_rshift
l_int|1
suffix:semicolon
id|opt
op_assign
id|sock_kmalloc
c_func
(paren
id|sk
comma
r_sizeof
(paren
op_star
id|opt
)paren
op_plus
id|hdrlen
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|opt
op_eq
l_int|NULL
)paren
r_return
l_int|NULL
suffix:semicolon
id|memset
c_func
(paren
id|opt
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|opt
)paren
)paren
suffix:semicolon
id|opt-&gt;tot_len
op_assign
r_sizeof
(paren
op_star
id|opt
)paren
op_plus
id|hdrlen
suffix:semicolon
id|opt-&gt;srcrt
op_assign
(paren
r_void
op_star
)paren
(paren
id|opt
op_plus
l_int|1
)paren
suffix:semicolon
id|opt-&gt;opt_nflen
op_assign
id|hdrlen
suffix:semicolon
id|memcpy
c_func
(paren
id|opt-&gt;srcrt
comma
id|hdr
comma
r_sizeof
(paren
op_star
id|hdr
)paren
)paren
suffix:semicolon
id|irthdr
op_assign
(paren
r_struct
id|rt0_hdr
op_star
)paren
id|opt-&gt;srcrt
suffix:semicolon
multiline_comment|/* Obsolete field, MBZ, when originated by us */
id|irthdr-&gt;bitmap
op_assign
l_int|0
suffix:semicolon
id|opt-&gt;srcrt-&gt;segments_left
op_assign
id|n
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
id|memcpy
c_func
(paren
id|irthdr-&gt;addr
op_plus
id|i
comma
id|rthdr-&gt;addr
op_plus
(paren
id|n
op_minus
l_int|1
op_minus
id|i
)paren
comma
l_int|16
)paren
suffix:semicolon
r_return
id|opt
suffix:semicolon
)brace
multiline_comment|/**********************************&n;  Hop-by-hop options.&n; **********************************/
multiline_comment|/* Router Alert as of RFC 2711 */
DECL|function|ipv6_hop_ra
r_static
r_int
id|ipv6_hop_ra
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_int
id|optoff
)paren
(brace
r_if
c_cond
(paren
id|skb-&gt;nh.raw
(braket
id|optoff
op_plus
l_int|1
)braket
op_eq
l_int|2
)paren
(brace
(paren
(paren
r_struct
id|inet6_skb_parm
op_star
)paren
id|skb-&gt;cb
)paren
op_member_access_from_pointer
id|ra
op_assign
id|optoff
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
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
id|KERN_DEBUG
l_string|&quot;ipv6_hop_ra: wrong RA length %d&bslash;n&quot;
comma
id|skb-&gt;nh.raw
(braket
id|optoff
op_plus
l_int|1
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
multiline_comment|/* Jumbo payload */
DECL|function|ipv6_hop_jumbo
r_static
r_int
id|ipv6_hop_jumbo
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_int
id|optoff
)paren
(brace
id|u32
id|pkt_len
suffix:semicolon
r_if
c_cond
(paren
id|skb-&gt;nh.raw
(braket
id|optoff
op_plus
l_int|1
)braket
op_ne
l_int|4
op_logical_or
(paren
id|optoff
op_amp
l_int|3
)paren
op_ne
l_int|2
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
id|KERN_DEBUG
l_string|&quot;ipv6_hop_jumbo: wrong jumbo opt length/alignment %d&bslash;n&quot;
comma
id|skb-&gt;nh.raw
(braket
id|optoff
op_plus
l_int|1
)braket
)paren
suffix:semicolon
r_goto
id|drop
suffix:semicolon
)brace
id|pkt_len
op_assign
id|ntohl
c_func
(paren
op_star
(paren
id|u32
op_star
)paren
(paren
id|skb-&gt;nh.raw
op_plus
id|optoff
op_plus
l_int|2
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pkt_len
op_le
id|IPV6_MAXPLEN
)paren
(brace
id|icmpv6_param_prob
c_func
(paren
id|skb
comma
id|ICMPV6_HDR_FIELD
comma
id|optoff
op_plus
l_int|2
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|skb-&gt;nh.ipv6h-&gt;payload_len
)paren
(brace
id|icmpv6_param_prob
c_func
(paren
id|skb
comma
id|ICMPV6_HDR_FIELD
comma
id|optoff
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pkt_len
OG
id|skb-&gt;len
op_minus
r_sizeof
(paren
r_struct
id|ipv6hdr
)paren
)paren
(brace
id|IP6_INC_STATS_BH
c_func
(paren
id|Ip6InTruncatedPkts
)paren
suffix:semicolon
r_goto
id|drop
suffix:semicolon
)brace
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
r_return
l_int|1
suffix:semicolon
id|drop
suffix:colon
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
DECL|variable|tlvprochopopt_lst
r_static
r_struct
id|tlvtype_proc
id|tlvprochopopt_lst
(braket
)braket
op_assign
(brace
(brace
dot
id|type
op_assign
id|IPV6_TLV_ROUTERALERT
comma
dot
id|func
op_assign
id|ipv6_hop_ra
comma
)brace
comma
(brace
dot
id|type
op_assign
id|IPV6_TLV_JUMBO
comma
dot
id|func
op_assign
id|ipv6_hop_jumbo
comma
)brace
comma
(brace
op_minus
l_int|1
comma
)brace
)brace
suffix:semicolon
DECL|function|ipv6_parse_hopopts
r_int
id|ipv6_parse_hopopts
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_int
id|nhoff
)paren
(brace
(paren
(paren
r_struct
id|inet6_skb_parm
op_star
)paren
id|skb-&gt;cb
)paren
op_member_access_from_pointer
id|hop
op_assign
r_sizeof
(paren
r_struct
id|ipv6hdr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ip6_parse_tlv
c_func
(paren
id|tlvprochopopt_lst
comma
id|skb
)paren
)paren
r_return
r_sizeof
(paren
r_struct
id|ipv6hdr
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Creating outbound headers.&n; *&n; *&t;&quot;build&quot; functions work when skb is filled from head to tail (datagram)&n; *&t;&quot;push&quot;&t;functions work when headers are added from tail to head (tcp)&n; *&n; *&t;In both cases we assume, that caller reserved enough room&n; *&t;for headers.&n; */
DECL|function|ipv6_build_rthdr
r_static
id|u8
op_star
id|ipv6_build_rthdr
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
id|u8
op_star
id|prev_hdr
comma
r_struct
id|ipv6_rt_hdr
op_star
id|opt
comma
r_struct
id|in6_addr
op_star
id|addr
)paren
(brace
r_struct
id|rt0_hdr
op_star
id|phdr
comma
op_star
id|ihdr
suffix:semicolon
r_int
id|hops
suffix:semicolon
id|ihdr
op_assign
(paren
r_struct
id|rt0_hdr
op_star
)paren
id|opt
suffix:semicolon
id|phdr
op_assign
(paren
r_struct
id|rt0_hdr
op_star
)paren
id|skb_put
c_func
(paren
id|skb
comma
(paren
id|ihdr-&gt;rt_hdr.hdrlen
op_plus
l_int|1
)paren
op_lshift
l_int|3
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|phdr
comma
id|ihdr
comma
r_sizeof
(paren
r_struct
id|rt0_hdr
)paren
)paren
suffix:semicolon
id|hops
op_assign
id|ihdr-&gt;rt_hdr.hdrlen
op_rshift
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|hops
OG
l_int|1
)paren
id|memcpy
c_func
(paren
id|phdr-&gt;addr
comma
id|ihdr-&gt;addr
op_plus
l_int|1
comma
(paren
id|hops
op_minus
l_int|1
)paren
op_star
r_sizeof
(paren
r_struct
id|in6_addr
)paren
)paren
suffix:semicolon
id|ipv6_addr_copy
c_func
(paren
id|phdr-&gt;addr
op_plus
(paren
id|hops
op_minus
l_int|1
)paren
comma
id|addr
)paren
suffix:semicolon
id|phdr-&gt;rt_hdr.nexthdr
op_assign
op_star
id|prev_hdr
suffix:semicolon
op_star
id|prev_hdr
op_assign
id|NEXTHDR_ROUTING
suffix:semicolon
r_return
op_amp
id|phdr-&gt;rt_hdr.nexthdr
suffix:semicolon
)brace
DECL|function|ipv6_build_exthdr
r_static
id|u8
op_star
id|ipv6_build_exthdr
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
id|u8
op_star
id|prev_hdr
comma
id|u8
id|type
comma
r_struct
id|ipv6_opt_hdr
op_star
id|opt
)paren
(brace
r_struct
id|ipv6_opt_hdr
op_star
id|h
op_assign
(paren
r_struct
id|ipv6_opt_hdr
op_star
)paren
id|skb_put
c_func
(paren
id|skb
comma
id|ipv6_optlen
c_func
(paren
id|opt
)paren
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|h
comma
id|opt
comma
id|ipv6_optlen
c_func
(paren
id|opt
)paren
)paren
suffix:semicolon
id|h-&gt;nexthdr
op_assign
op_star
id|prev_hdr
suffix:semicolon
op_star
id|prev_hdr
op_assign
id|type
suffix:semicolon
r_return
op_amp
id|h-&gt;nexthdr
suffix:semicolon
)brace
DECL|function|ipv6_build_authhdr
r_static
id|u8
op_star
id|ipv6_build_authhdr
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
id|u8
op_star
id|prev_hdr
comma
r_struct
id|ipv6_opt_hdr
op_star
id|opt
)paren
(brace
r_struct
id|ipv6_opt_hdr
op_star
id|h
op_assign
(paren
r_struct
id|ipv6_opt_hdr
op_star
)paren
id|skb_put
c_func
(paren
id|skb
comma
(paren
id|opt-&gt;hdrlen
op_plus
l_int|2
)paren
op_lshift
l_int|2
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|h
comma
id|opt
comma
(paren
id|opt-&gt;hdrlen
op_plus
l_int|2
)paren
op_lshift
l_int|2
)paren
suffix:semicolon
id|h-&gt;nexthdr
op_assign
op_star
id|prev_hdr
suffix:semicolon
op_star
id|prev_hdr
op_assign
id|NEXTHDR_AUTH
suffix:semicolon
r_return
op_amp
id|h-&gt;nexthdr
suffix:semicolon
)brace
DECL|function|ipv6_build_nfrag_opts
id|u8
op_star
id|ipv6_build_nfrag_opts
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
id|u8
op_star
id|prev_hdr
comma
r_struct
id|ipv6_txoptions
op_star
id|opt
comma
r_struct
id|in6_addr
op_star
id|daddr
comma
id|u32
id|jumbolen
)paren
(brace
r_struct
id|ipv6_opt_hdr
op_star
id|h
op_assign
(paren
r_struct
id|ipv6_opt_hdr
op_star
)paren
id|skb-&gt;data
suffix:semicolon
r_if
c_cond
(paren
id|opt
op_logical_and
id|opt-&gt;hopopt
)paren
id|prev_hdr
op_assign
id|ipv6_build_exthdr
c_func
(paren
id|skb
comma
id|prev_hdr
comma
id|NEXTHDR_HOP
comma
id|opt-&gt;hopopt
)paren
suffix:semicolon
r_if
c_cond
(paren
id|jumbolen
)paren
(brace
id|u8
op_star
id|jumboopt
op_assign
(paren
id|u8
op_star
)paren
id|skb_put
c_func
(paren
id|skb
comma
l_int|8
)paren
suffix:semicolon
r_if
c_cond
(paren
id|opt
op_logical_and
id|opt-&gt;hopopt
)paren
(brace
op_star
id|jumboopt
op_increment
op_assign
id|IPV6_TLV_PADN
suffix:semicolon
op_star
id|jumboopt
op_increment
op_assign
l_int|0
suffix:semicolon
id|h-&gt;hdrlen
op_increment
suffix:semicolon
)brace
r_else
(brace
id|h
op_assign
(paren
r_struct
id|ipv6_opt_hdr
op_star
)paren
id|jumboopt
suffix:semicolon
id|h-&gt;nexthdr
op_assign
op_star
id|prev_hdr
suffix:semicolon
id|h-&gt;hdrlen
op_assign
l_int|0
suffix:semicolon
id|jumboopt
op_add_assign
l_int|2
suffix:semicolon
op_star
id|prev_hdr
op_assign
id|NEXTHDR_HOP
suffix:semicolon
id|prev_hdr
op_assign
op_amp
id|h-&gt;nexthdr
suffix:semicolon
)brace
id|jumboopt
(braket
l_int|0
)braket
op_assign
id|IPV6_TLV_JUMBO
suffix:semicolon
id|jumboopt
(braket
l_int|1
)braket
op_assign
l_int|4
suffix:semicolon
op_star
(paren
id|u32
op_star
)paren
(paren
id|jumboopt
op_plus
l_int|2
)paren
op_assign
id|htonl
c_func
(paren
id|jumbolen
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|opt
)paren
(brace
r_if
c_cond
(paren
id|opt-&gt;dst0opt
)paren
id|prev_hdr
op_assign
id|ipv6_build_exthdr
c_func
(paren
id|skb
comma
id|prev_hdr
comma
id|NEXTHDR_DEST
comma
id|opt-&gt;dst0opt
)paren
suffix:semicolon
r_if
c_cond
(paren
id|opt-&gt;srcrt
)paren
id|prev_hdr
op_assign
id|ipv6_build_rthdr
c_func
(paren
id|skb
comma
id|prev_hdr
comma
id|opt-&gt;srcrt
comma
id|daddr
)paren
suffix:semicolon
)brace
r_return
id|prev_hdr
suffix:semicolon
)brace
DECL|function|ipv6_build_frag_opts
id|u8
op_star
id|ipv6_build_frag_opts
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
id|u8
op_star
id|prev_hdr
comma
r_struct
id|ipv6_txoptions
op_star
id|opt
)paren
(brace
r_if
c_cond
(paren
id|opt-&gt;auth
)paren
id|prev_hdr
op_assign
id|ipv6_build_authhdr
c_func
(paren
id|skb
comma
id|prev_hdr
comma
id|opt-&gt;auth
)paren
suffix:semicolon
r_if
c_cond
(paren
id|opt-&gt;dst1opt
)paren
id|prev_hdr
op_assign
id|ipv6_build_exthdr
c_func
(paren
id|skb
comma
id|prev_hdr
comma
id|NEXTHDR_DEST
comma
id|opt-&gt;dst1opt
)paren
suffix:semicolon
r_return
id|prev_hdr
suffix:semicolon
)brace
DECL|function|ipv6_push_rthdr
r_static
r_void
id|ipv6_push_rthdr
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
id|u8
op_star
id|proto
comma
r_struct
id|ipv6_rt_hdr
op_star
id|opt
comma
r_struct
id|in6_addr
op_star
op_star
id|addr_p
)paren
(brace
r_struct
id|rt0_hdr
op_star
id|phdr
comma
op_star
id|ihdr
suffix:semicolon
r_int
id|hops
suffix:semicolon
id|ihdr
op_assign
(paren
r_struct
id|rt0_hdr
op_star
)paren
id|opt
suffix:semicolon
id|phdr
op_assign
(paren
r_struct
id|rt0_hdr
op_star
)paren
id|skb_push
c_func
(paren
id|skb
comma
(paren
id|ihdr-&gt;rt_hdr.hdrlen
op_plus
l_int|1
)paren
op_lshift
l_int|3
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|phdr
comma
id|ihdr
comma
r_sizeof
(paren
r_struct
id|rt0_hdr
)paren
)paren
suffix:semicolon
id|hops
op_assign
id|ihdr-&gt;rt_hdr.hdrlen
op_rshift
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|hops
OG
l_int|1
)paren
id|memcpy
c_func
(paren
id|phdr-&gt;addr
comma
id|ihdr-&gt;addr
op_plus
l_int|1
comma
(paren
id|hops
op_minus
l_int|1
)paren
op_star
r_sizeof
(paren
r_struct
id|in6_addr
)paren
)paren
suffix:semicolon
id|ipv6_addr_copy
c_func
(paren
id|phdr-&gt;addr
op_plus
(paren
id|hops
op_minus
l_int|1
)paren
comma
op_star
id|addr_p
)paren
suffix:semicolon
op_star
id|addr_p
op_assign
id|ihdr-&gt;addr
suffix:semicolon
id|phdr-&gt;rt_hdr.nexthdr
op_assign
op_star
id|proto
suffix:semicolon
op_star
id|proto
op_assign
id|NEXTHDR_ROUTING
suffix:semicolon
)brace
DECL|function|ipv6_push_exthdr
r_static
r_void
id|ipv6_push_exthdr
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
id|u8
op_star
id|proto
comma
id|u8
id|type
comma
r_struct
id|ipv6_opt_hdr
op_star
id|opt
)paren
(brace
r_struct
id|ipv6_opt_hdr
op_star
id|h
op_assign
(paren
r_struct
id|ipv6_opt_hdr
op_star
)paren
id|skb_push
c_func
(paren
id|skb
comma
id|ipv6_optlen
c_func
(paren
id|opt
)paren
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|h
comma
id|opt
comma
id|ipv6_optlen
c_func
(paren
id|opt
)paren
)paren
suffix:semicolon
id|h-&gt;nexthdr
op_assign
op_star
id|proto
suffix:semicolon
op_star
id|proto
op_assign
id|type
suffix:semicolon
)brace
DECL|function|ipv6_push_authhdr
r_static
r_void
id|ipv6_push_authhdr
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
id|u8
op_star
id|proto
comma
r_struct
id|ipv6_opt_hdr
op_star
id|opt
)paren
(brace
r_struct
id|ipv6_opt_hdr
op_star
id|h
op_assign
(paren
r_struct
id|ipv6_opt_hdr
op_star
)paren
id|skb_push
c_func
(paren
id|skb
comma
(paren
id|opt-&gt;hdrlen
op_plus
l_int|2
)paren
op_lshift
l_int|2
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|h
comma
id|opt
comma
(paren
id|opt-&gt;hdrlen
op_plus
l_int|2
)paren
op_lshift
l_int|2
)paren
suffix:semicolon
id|h-&gt;nexthdr
op_assign
op_star
id|proto
suffix:semicolon
op_star
id|proto
op_assign
id|NEXTHDR_AUTH
suffix:semicolon
)brace
DECL|function|ipv6_push_nfrag_opts
r_void
id|ipv6_push_nfrag_opts
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|ipv6_txoptions
op_star
id|opt
comma
id|u8
op_star
id|proto
comma
r_struct
id|in6_addr
op_star
op_star
id|daddr
)paren
(brace
r_if
c_cond
(paren
id|opt-&gt;srcrt
)paren
id|ipv6_push_rthdr
c_func
(paren
id|skb
comma
id|proto
comma
id|opt-&gt;srcrt
comma
id|daddr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|opt-&gt;dst0opt
)paren
id|ipv6_push_exthdr
c_func
(paren
id|skb
comma
id|proto
comma
id|NEXTHDR_DEST
comma
id|opt-&gt;dst0opt
)paren
suffix:semicolon
r_if
c_cond
(paren
id|opt-&gt;hopopt
)paren
id|ipv6_push_exthdr
c_func
(paren
id|skb
comma
id|proto
comma
id|NEXTHDR_HOP
comma
id|opt-&gt;hopopt
)paren
suffix:semicolon
)brace
DECL|function|ipv6_push_frag_opts
r_void
id|ipv6_push_frag_opts
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|ipv6_txoptions
op_star
id|opt
comma
id|u8
op_star
id|proto
)paren
(brace
r_if
c_cond
(paren
id|opt-&gt;dst1opt
)paren
id|ipv6_push_exthdr
c_func
(paren
id|skb
comma
id|proto
comma
id|NEXTHDR_DEST
comma
id|opt-&gt;dst1opt
)paren
suffix:semicolon
r_if
c_cond
(paren
id|opt-&gt;auth
)paren
id|ipv6_push_authhdr
c_func
(paren
id|skb
comma
id|proto
comma
id|opt-&gt;auth
)paren
suffix:semicolon
)brace
r_struct
id|ipv6_txoptions
op_star
DECL|function|ipv6_dup_options
id|ipv6_dup_options
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_struct
id|ipv6_txoptions
op_star
id|opt
)paren
(brace
r_struct
id|ipv6_txoptions
op_star
id|opt2
suffix:semicolon
id|opt2
op_assign
id|sock_kmalloc
c_func
(paren
id|sk
comma
id|opt-&gt;tot_len
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|opt2
)paren
(brace
r_int
id|dif
op_assign
(paren
r_char
op_star
)paren
id|opt2
op_minus
(paren
r_char
op_star
)paren
id|opt
suffix:semicolon
id|memcpy
c_func
(paren
id|opt2
comma
id|opt
comma
id|opt-&gt;tot_len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|opt2-&gt;hopopt
)paren
op_star
(paren
(paren
r_char
op_star
op_star
)paren
op_amp
id|opt2-&gt;hopopt
)paren
op_add_assign
id|dif
suffix:semicolon
r_if
c_cond
(paren
id|opt2-&gt;dst0opt
)paren
op_star
(paren
(paren
r_char
op_star
op_star
)paren
op_amp
id|opt2-&gt;dst0opt
)paren
op_add_assign
id|dif
suffix:semicolon
r_if
c_cond
(paren
id|opt2-&gt;dst1opt
)paren
op_star
(paren
(paren
r_char
op_star
op_star
)paren
op_amp
id|opt2-&gt;dst1opt
)paren
op_add_assign
id|dif
suffix:semicolon
r_if
c_cond
(paren
id|opt2-&gt;auth
)paren
op_star
(paren
(paren
r_char
op_star
op_star
)paren
op_amp
id|opt2-&gt;auth
)paren
op_add_assign
id|dif
suffix:semicolon
r_if
c_cond
(paren
id|opt2-&gt;srcrt
)paren
op_star
(paren
(paren
r_char
op_star
op_star
)paren
op_amp
id|opt2-&gt;srcrt
)paren
op_add_assign
id|dif
suffix:semicolon
)brace
r_return
id|opt2
suffix:semicolon
)brace
multiline_comment|/* &n; * find out if nexthdr is a well-known extension header or a protocol&n; */
DECL|function|ipv6_ext_hdr
r_int
id|ipv6_ext_hdr
c_func
(paren
id|u8
id|nexthdr
)paren
(brace
multiline_comment|/* &n;&t; * find out if nexthdr is an extension header or a protocol&n;&t; */
r_return
(paren
(paren
id|nexthdr
op_eq
id|NEXTHDR_HOP
)paren
op_logical_or
(paren
id|nexthdr
op_eq
id|NEXTHDR_ROUTING
)paren
op_logical_or
(paren
id|nexthdr
op_eq
id|NEXTHDR_FRAGMENT
)paren
op_logical_or
(paren
id|nexthdr
op_eq
id|NEXTHDR_AUTH
)paren
op_logical_or
(paren
id|nexthdr
op_eq
id|NEXTHDR_NONE
)paren
op_logical_or
(paren
id|nexthdr
op_eq
id|NEXTHDR_DEST
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Skip any extension headers. This is used by the ICMP module.&n; *&n; * Note that strictly speaking this conflicts with RFC 2460 4.0:&n; * ...The contents and semantics of each extension header determine whether &n; * or not to proceed to the next header.  Therefore, extension headers must&n; * be processed strictly in the order they appear in the packet; a&n; * receiver must not, for example, scan through a packet looking for a&n; * particular kind of extension header and process that header prior to&n; * processing all preceding ones.&n; * &n; * We do exactly this. This is a protocol bug. We can&squot;t decide after a&n; * seeing an unknown discard-with-error flavour TLV option if it&squot;s a &n; * ICMP error message or not (errors should never be send in reply to&n; * ICMP error messages).&n; * &n; * But I see no other way to do this. This might need to be reexamined&n; * when Linux implements ESP (and maybe AUTH) headers.&n; * --AK&n; *&n; * This function parses (probably truncated) exthdr set &quot;hdr&quot;&n; * of length &quot;len&quot;. &quot;nexthdrp&quot; initially points to some place,&n; * where type of the first header can be found.&n; *&n; * It skips all well-known exthdrs, and returns pointer to the start&n; * of unparsable area i.e. the first header with unknown type.&n; * If it is not NULL *nexthdr is updated by type/protocol of this header.&n; *&n; * NOTES: - if packet terminated with NEXTHDR_NONE it returns NULL.&n; *        - it may return pointer pointing beyond end of packet,&n; *&t;    if the last recognized header is truncated in the middle.&n; *        - if packet is truncated, so that all parsed headers are skipped,&n; *&t;    it returns NULL.&n; *&t;  - First fragment header is skipped, not-first ones&n; *&t;    are considered as unparsable.&n; *&t;  - ESP is unparsable for now and considered like&n; *&t;    normal payload protocol.&n; *&t;  - Note also special handling of AUTH header. Thanks to IPsec wizards.&n; *&n; * --ANK (980726)&n; */
DECL|function|ipv6_skip_exthdr
r_int
id|ipv6_skip_exthdr
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_int
id|start
comma
id|u8
op_star
id|nexthdrp
comma
r_int
id|len
)paren
(brace
id|u8
id|nexthdr
op_assign
op_star
id|nexthdrp
suffix:semicolon
r_while
c_loop
(paren
id|ipv6_ext_hdr
c_func
(paren
id|nexthdr
)paren
)paren
(brace
r_struct
id|ipv6_opt_hdr
id|hdr
suffix:semicolon
r_int
id|hdrlen
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
(paren
r_int
)paren
r_sizeof
(paren
r_struct
id|ipv6_opt_hdr
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|nexthdr
op_eq
id|NEXTHDR_NONE
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|skb_copy_bits
c_func
(paren
id|skb
comma
id|start
comma
op_amp
id|hdr
comma
r_sizeof
(paren
id|hdr
)paren
)paren
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nexthdr
op_eq
id|NEXTHDR_FRAGMENT
)paren
(brace
r_struct
id|frag_hdr
op_star
id|fhdr
op_assign
(paren
r_struct
id|frag_hdr
op_star
)paren
op_amp
id|hdr
suffix:semicolon
r_if
c_cond
(paren
id|ntohs
c_func
(paren
id|fhdr-&gt;frag_off
)paren
op_amp
op_complement
l_int|0x7
)paren
r_break
suffix:semicolon
id|hdrlen
op_assign
l_int|8
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|nexthdr
op_eq
id|NEXTHDR_AUTH
)paren
id|hdrlen
op_assign
(paren
id|hdr.hdrlen
op_plus
l_int|2
)paren
op_lshift
l_int|2
suffix:semicolon
r_else
id|hdrlen
op_assign
id|ipv6_optlen
c_func
(paren
op_amp
id|hdr
)paren
suffix:semicolon
id|nexthdr
op_assign
id|hdr.nexthdr
suffix:semicolon
id|len
op_sub_assign
id|hdrlen
suffix:semicolon
id|start
op_add_assign
id|hdrlen
suffix:semicolon
)brace
op_star
id|nexthdrp
op_assign
id|nexthdr
suffix:semicolon
r_return
id|start
suffix:semicolon
)brace
eof
