multiline_comment|/*&n; * INET&t;&t;An implementation of the TCP/IP protocol suite for the LINUX&n; *&t;&t;operating system.  INET is implemented using the  BSD Socket&n; *&t;&t;interface as the means of communication with the user level.&n; *&n; *&t;&t;Dumb Network Address Translation.&n; *&n; * Version:&t;$Id: ip_nat_dumb.c,v 1.11 2000/12/13 18:31:48 davem Exp $&n; *&n; * Authors:&t;Alexey Kuznetsov, &lt;kuznet@ms2.inr.ac.ru&gt;&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; *&n; * Fixes:&n; *&t;&t;Rani Assaf&t;:&t;A zero checksum is a special case&n; *&t;&t;&t;&t;&t;only in UDP&n; * &t;&t;Rani Assaf&t;:&t;Added ICMP messages rewriting&n; * &t;&t;Rani Assaf&t;:&t;Repaired wrong changes, made by ANK.&n; *&n; *&n; * NOTE:&t;It is just working model of real NAT.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/ip.h&gt;
macro_line|#include &lt;linux/icmp.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;net/ip.h&gt;
macro_line|#include &lt;net/icmp.h&gt;
macro_line|#include &lt;linux/tcp.h&gt;
macro_line|#include &lt;linux/udp.h&gt;
macro_line|#include &lt;net/checksum.h&gt;
macro_line|#include &lt;linux/route.h&gt;
macro_line|#include &lt;net/route.h&gt;
macro_line|#include &lt;net/ip_fib.h&gt;
r_int
DECL|function|ip_do_nat
id|ip_do_nat
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|rtable
op_star
id|rt
op_assign
(paren
r_struct
id|rtable
op_star
)paren
id|skb-&gt;dst
suffix:semicolon
r_struct
id|iphdr
op_star
id|iph
op_assign
id|skb-&gt;nh.iph
suffix:semicolon
id|u32
id|odaddr
op_assign
id|iph-&gt;daddr
suffix:semicolon
id|u32
id|osaddr
op_assign
id|iph-&gt;saddr
suffix:semicolon
id|u16
id|check
suffix:semicolon
id|IPCB
c_func
(paren
id|skb
)paren
op_member_access_from_pointer
id|flags
op_or_assign
id|IPSKB_TRANSLATED
suffix:semicolon
multiline_comment|/* Rewrite IP header */
id|iph-&gt;daddr
op_assign
id|rt-&gt;rt_dst_map
suffix:semicolon
id|iph-&gt;saddr
op_assign
id|rt-&gt;rt_src_map
suffix:semicolon
id|iph-&gt;check
op_assign
l_int|0
suffix:semicolon
id|iph-&gt;check
op_assign
id|ip_fast_csum
c_func
(paren
(paren
r_int
r_char
op_star
)paren
id|iph
comma
id|iph-&gt;ihl
)paren
suffix:semicolon
multiline_comment|/* If it is the first fragment, rewrite protocol headers */
r_if
c_cond
(paren
op_logical_neg
(paren
id|iph-&gt;frag_off
op_amp
id|htons
c_func
(paren
id|IP_OFFSET
)paren
)paren
)paren
(brace
id|u16
op_star
id|cksum
suffix:semicolon
r_switch
c_cond
(paren
id|iph-&gt;protocol
)paren
(brace
r_case
id|IPPROTO_TCP
suffix:colon
id|cksum
op_assign
(paren
id|u16
op_star
)paren
op_amp
(paren
(paren
r_struct
id|tcphdr
op_star
)paren
(paren
(paren
(paren
r_char
op_star
)paren
id|iph
)paren
op_plus
(paren
id|iph-&gt;ihl
op_lshift
l_int|2
)paren
)paren
)paren
op_member_access_from_pointer
id|check
suffix:semicolon
r_if
c_cond
(paren
(paren
id|u8
op_star
)paren
(paren
id|cksum
op_plus
l_int|1
)paren
OG
id|skb-&gt;tail
)paren
r_goto
id|truncated
suffix:semicolon
id|check
op_assign
op_star
id|cksum
suffix:semicolon
r_if
c_cond
(paren
id|skb-&gt;ip_summed
op_ne
id|CHECKSUM_HW
)paren
id|check
op_assign
op_complement
id|check
suffix:semicolon
id|check
op_assign
id|csum_tcpudp_magic
c_func
(paren
id|iph-&gt;saddr
comma
id|iph-&gt;daddr
comma
l_int|0
comma
l_int|0
comma
id|check
)paren
suffix:semicolon
id|check
op_assign
id|csum_tcpudp_magic
c_func
(paren
op_complement
id|osaddr
comma
op_complement
id|odaddr
comma
l_int|0
comma
l_int|0
comma
op_complement
id|check
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb-&gt;ip_summed
op_eq
id|CHECKSUM_HW
)paren
id|check
op_assign
op_complement
id|check
suffix:semicolon
op_star
id|cksum
op_assign
id|check
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IPPROTO_UDP
suffix:colon
id|cksum
op_assign
(paren
id|u16
op_star
)paren
op_amp
(paren
(paren
r_struct
id|udphdr
op_star
)paren
(paren
(paren
(paren
r_char
op_star
)paren
id|iph
)paren
op_plus
(paren
id|iph-&gt;ihl
op_lshift
l_int|2
)paren
)paren
)paren
op_member_access_from_pointer
id|check
suffix:semicolon
r_if
c_cond
(paren
(paren
id|u8
op_star
)paren
(paren
id|cksum
op_plus
l_int|1
)paren
OG
id|skb-&gt;tail
)paren
r_goto
id|truncated
suffix:semicolon
r_if
c_cond
(paren
(paren
id|check
op_assign
op_star
id|cksum
)paren
op_ne
l_int|0
)paren
(brace
id|check
op_assign
id|csum_tcpudp_magic
c_func
(paren
id|iph-&gt;saddr
comma
id|iph-&gt;daddr
comma
l_int|0
comma
l_int|0
comma
op_complement
id|check
)paren
suffix:semicolon
id|check
op_assign
id|csum_tcpudp_magic
c_func
(paren
op_complement
id|osaddr
comma
op_complement
id|odaddr
comma
l_int|0
comma
l_int|0
comma
op_complement
id|check
)paren
suffix:semicolon
op_star
id|cksum
op_assign
id|check
ques
c_cond
suffix:colon
l_int|0xFFFF
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|IPPROTO_ICMP
suffix:colon
(brace
r_struct
id|icmphdr
op_star
id|icmph
op_assign
(paren
r_struct
id|icmphdr
op_star
)paren
(paren
(paren
r_char
op_star
)paren
id|iph
op_plus
(paren
id|iph-&gt;ihl
op_lshift
l_int|2
)paren
)paren
suffix:semicolon
r_struct
id|iphdr
op_star
id|ciph
suffix:semicolon
id|u32
id|idaddr
comma
id|isaddr
suffix:semicolon
r_int
id|updated
suffix:semicolon
r_if
c_cond
(paren
(paren
id|icmph-&gt;type
op_ne
id|ICMP_DEST_UNREACH
)paren
op_logical_and
(paren
id|icmph-&gt;type
op_ne
id|ICMP_TIME_EXCEEDED
)paren
op_logical_and
(paren
id|icmph-&gt;type
op_ne
id|ICMP_PARAMETERPROB
)paren
)paren
r_break
suffix:semicolon
id|ciph
op_assign
(paren
r_struct
id|iphdr
op_star
)paren
(paren
id|icmph
op_plus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|u8
op_star
)paren
(paren
id|ciph
op_plus
l_int|1
)paren
OG
id|skb-&gt;tail
)paren
r_goto
id|truncated
suffix:semicolon
id|isaddr
op_assign
id|ciph-&gt;saddr
suffix:semicolon
id|idaddr
op_assign
id|ciph-&gt;daddr
suffix:semicolon
id|updated
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|rt-&gt;rt_flags
op_amp
id|RTCF_DNAT
op_logical_and
id|ciph-&gt;saddr
op_eq
id|odaddr
)paren
(brace
id|ciph-&gt;saddr
op_assign
id|iph-&gt;daddr
suffix:semicolon
id|updated
op_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|rt-&gt;rt_flags
op_amp
id|RTCF_SNAT
)paren
(brace
r_if
c_cond
(paren
id|ciph-&gt;daddr
op_ne
id|osaddr
)paren
(brace
r_struct
id|fib_result
id|res
suffix:semicolon
r_int
id|flags
op_assign
l_int|0
suffix:semicolon
r_struct
id|flowi
id|fl
op_assign
(brace
dot
id|iif
op_assign
id|skb-&gt;dev-&gt;ifindex
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
id|ciph-&gt;saddr
comma
dot
id|saddr
op_assign
id|ciph-&gt;daddr
comma
macro_line|#ifdef CONFIG_IP_ROUTE_TOS
dot
id|tos
op_assign
id|RT_TOS
c_func
(paren
id|ciph-&gt;tos
)paren
macro_line|#endif
)brace
)brace
comma
dot
id|proto
op_assign
id|ciph-&gt;protocol
)brace
suffix:semicolon
multiline_comment|/* Use fib_lookup() until we get our own&n;&t;&t;&t;&t;&t; * hash table of NATed hosts -- Rani&n;&t;&t;&t;&t; &t; */
r_if
c_cond
(paren
id|fib_lookup
c_func
(paren
op_amp
id|fl
comma
op_amp
id|res
)paren
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|res.r
)paren
(brace
id|ciph-&gt;daddr
op_assign
id|fib_rules_policy
c_func
(paren
id|ciph-&gt;daddr
comma
op_amp
id|res
comma
op_amp
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ciph-&gt;daddr
op_ne
id|idaddr
)paren
id|updated
op_assign
l_int|1
suffix:semicolon
)brace
id|fib_res_put
c_func
(paren
op_amp
id|res
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
id|ciph-&gt;daddr
op_assign
id|iph-&gt;saddr
suffix:semicolon
id|updated
op_assign
l_int|1
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|updated
)paren
(brace
id|cksum
op_assign
op_amp
id|icmph-&gt;checksum
suffix:semicolon
multiline_comment|/* Using tcpudp primitive. Why not? */
id|check
op_assign
id|csum_tcpudp_magic
c_func
(paren
id|ciph-&gt;saddr
comma
id|ciph-&gt;daddr
comma
l_int|0
comma
l_int|0
comma
op_complement
(paren
op_star
id|cksum
)paren
)paren
suffix:semicolon
op_star
id|cksum
op_assign
id|csum_tcpudp_magic
c_func
(paren
op_complement
id|isaddr
comma
op_complement
id|idaddr
comma
l_int|0
comma
l_int|0
comma
op_complement
id|check
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
r_default
suffix:colon
r_break
suffix:semicolon
)brace
)brace
r_return
id|NET_RX_SUCCESS
suffix:semicolon
id|truncated
suffix:colon
multiline_comment|/* should be return NET_RX_BAD; */
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
eof
