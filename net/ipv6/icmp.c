multiline_comment|/*&n; *&t;Internet Control Message Protocol (ICMPv6)&n; *&t;Linux INET6 implementation&n; *&n; *&t;Authors:&n; *&t;Pedro Roque&t;&t;&lt;roque@di.fc.ul.pt&gt;&n; *&n; *&t;$Id: icmp.c,v 1.38 2002/02/08 03:57:19 davem Exp $&n; *&n; *&t;Based on net/ipv4/icmp.c&n; *&n; *&t;RFC 1885&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *      modify it under the terms of the GNU General Public License&n; *      as published by the Free Software Foundation; either version&n; *      2 of the License, or (at your option) any later version.&n; */
multiline_comment|/*&n; *&t;Changes:&n; *&n; *&t;Andi Kleen&t;&t;:&t;exception handling&n; *&t;Andi Kleen&t;&t;&t;add rate limits. never reply to a icmp.&n; *&t;&t;&t;&t;&t;add more length checks and other fixes.&n; *&t;yoshfuji&t;&t;:&t;ensure to sent parameter problem for&n; *&t;&t;&t;&t;&t;fragments.&n; *&t;YOSHIFUJI Hideaki @USAGI:&t;added sysctl for icmp rate limit.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/sockios.h&gt;
macro_line|#include &lt;linux/net.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#ifdef CONFIG_SYSCTL
macro_line|#include &lt;linux/sysctl.h&gt;
macro_line|#endif
macro_line|#include &lt;linux/inet.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/icmpv6.h&gt;
macro_line|#include &lt;net/ip.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;net/ipv6.h&gt;
macro_line|#include &lt;net/checksum.h&gt;
macro_line|#include &lt;net/protocol.h&gt;
macro_line|#include &lt;net/raw.h&gt;
macro_line|#include &lt;net/rawv6.h&gt;
macro_line|#include &lt;net/transp_v6.h&gt;
macro_line|#include &lt;net/ip6_route.h&gt;
macro_line|#include &lt;net/addrconf.h&gt;
macro_line|#include &lt;net/icmp.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
id|DEFINE_SNMP_STAT
c_func
(paren
r_struct
id|icmpv6_mib
comma
id|icmpv6_statistics
)paren
suffix:semicolon
multiline_comment|/*&n; *&t;ICMP socket(s) for flow control.&n; */
multiline_comment|/* XXX We can&squot;t use per_cpu because this can be modular... */
DECL|variable|__icmpv6_socket
r_static
r_struct
id|socket
op_star
id|__icmpv6_socket
(braket
id|NR_CPUS
)braket
suffix:semicolon
DECL|macro|icmpv6_socket
mdefine_line|#define icmpv6_socket&t;__icmpv6_socket[smp_processor_id()]
r_static
r_int
id|icmpv6_rcv
c_func
(paren
r_struct
id|sk_buff
op_star
op_star
id|pskb
comma
r_int
r_int
op_star
id|nhoffp
)paren
suffix:semicolon
DECL|variable|icmpv6_protocol
r_static
r_struct
id|inet6_protocol
id|icmpv6_protocol
op_assign
(brace
dot
id|handler
op_assign
id|icmpv6_rcv
comma
dot
id|flags
op_assign
id|INET6_PROTO_FINAL
comma
)brace
suffix:semicolon
DECL|struct|icmpv6_msg
r_struct
id|icmpv6_msg
(brace
DECL|member|icmph
r_struct
id|icmp6hdr
id|icmph
suffix:semicolon
DECL|member|skb
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
DECL|member|offset
r_int
id|offset
suffix:semicolon
DECL|member|daddr
r_struct
id|in6_addr
op_star
id|daddr
suffix:semicolon
DECL|member|len
r_int
id|len
suffix:semicolon
DECL|member|csum
id|__u32
id|csum
suffix:semicolon
)brace
suffix:semicolon
DECL|function|icmpv6_xmit_lock
r_static
id|__inline__
r_void
id|icmpv6_xmit_lock
c_func
(paren
r_void
)paren
(brace
id|local_bh_disable
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
op_logical_neg
id|spin_trylock
c_func
(paren
op_amp
id|icmpv6_socket-&gt;sk-&gt;lock.slock
)paren
)paren
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|icmpv6_xmit_unlock
r_static
id|__inline__
r_void
id|icmpv6_xmit_unlock
c_func
(paren
r_void
)paren
(brace
id|spin_unlock_bh
c_func
(paren
op_amp
id|icmpv6_socket-&gt;sk-&gt;lock.slock
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;getfrag callback&n; */
DECL|function|icmpv6_getfrag
r_static
r_int
id|icmpv6_getfrag
c_func
(paren
r_const
r_void
op_star
id|data
comma
r_struct
id|in6_addr
op_star
id|saddr
comma
r_char
op_star
id|buff
comma
r_int
r_int
id|offset
comma
r_int
r_int
id|len
)paren
(brace
r_struct
id|icmpv6_msg
op_star
id|msg
op_assign
(paren
r_struct
id|icmpv6_msg
op_star
)paren
id|data
suffix:semicolon
r_struct
id|icmp6hdr
op_star
id|icmph
suffix:semicolon
id|__u32
id|csum
suffix:semicolon
r_if
c_cond
(paren
id|offset
)paren
(brace
id|csum
op_assign
id|skb_copy_and_csum_bits
c_func
(paren
id|msg-&gt;skb
comma
id|msg-&gt;offset
op_plus
(paren
id|offset
op_minus
r_sizeof
(paren
r_struct
id|icmp6hdr
)paren
)paren
comma
id|buff
comma
id|len
comma
id|msg-&gt;csum
)paren
suffix:semicolon
id|msg-&gt;csum
op_assign
id|csum
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|csum
op_assign
id|csum_partial_copy_nocheck
c_func
(paren
(paren
r_void
op_star
)paren
op_amp
id|msg-&gt;icmph
comma
id|buff
comma
r_sizeof
(paren
r_struct
id|icmp6hdr
)paren
comma
id|msg-&gt;csum
)paren
suffix:semicolon
id|csum
op_assign
id|skb_copy_and_csum_bits
c_func
(paren
id|msg-&gt;skb
comma
id|msg-&gt;offset
comma
id|buff
op_plus
r_sizeof
(paren
r_struct
id|icmp6hdr
)paren
comma
id|len
op_minus
r_sizeof
(paren
r_struct
id|icmp6hdr
)paren
comma
id|csum
)paren
suffix:semicolon
id|icmph
op_assign
(paren
r_struct
id|icmp6hdr
op_star
)paren
id|buff
suffix:semicolon
id|icmph-&gt;icmp6_cksum
op_assign
id|csum_ipv6_magic
c_func
(paren
id|saddr
comma
id|msg-&gt;daddr
comma
id|msg-&gt;len
comma
id|IPPROTO_ICMPV6
comma
id|csum
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* &n; * Slightly more convenient version of icmpv6_send.&n; */
DECL|function|icmpv6_param_prob
r_void
id|icmpv6_param_prob
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_int
id|code
comma
r_int
id|pos
)paren
(brace
id|icmpv6_send
c_func
(paren
id|skb
comma
id|ICMPV6_PARAMPROB
comma
id|code
comma
id|pos
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
)brace
multiline_comment|/*&n; * Figure out, may we reply to this packet with icmp error.&n; *&n; * We do not reply, if:&n; *&t;- it was icmp error message.&n; *&t;- it is truncated, so that it is known, that protocol is ICMPV6&n; *&t;  (i.e. in the middle of some exthdr)&n; *&n; *&t;--ANK (980726)&n; */
DECL|function|is_ineligible
r_static
r_int
id|is_ineligible
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_int
id|ptr
op_assign
(paren
id|u8
op_star
)paren
(paren
id|skb-&gt;nh.ipv6h
op_plus
l_int|1
)paren
op_minus
id|skb-&gt;data
suffix:semicolon
r_int
id|len
op_assign
id|skb-&gt;len
op_minus
id|ptr
suffix:semicolon
id|__u8
id|nexthdr
op_assign
id|skb-&gt;nh.ipv6h-&gt;nexthdr
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
l_int|0
)paren
r_return
l_int|1
suffix:semicolon
id|ptr
op_assign
id|ipv6_skip_exthdr
c_func
(paren
id|skb
comma
id|ptr
comma
op_amp
id|nexthdr
comma
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ptr
OL
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|nexthdr
op_eq
id|IPPROTO_ICMPV6
)paren
(brace
id|u8
id|type
suffix:semicolon
r_if
c_cond
(paren
id|skb_copy_bits
c_func
(paren
id|skb
comma
id|ptr
op_plus
m_offsetof
(paren
r_struct
id|icmp6hdr
comma
id|icmp6_type
)paren
comma
op_amp
id|type
comma
l_int|1
)paren
op_logical_or
op_logical_neg
(paren
id|type
op_amp
id|ICMPV6_INFOMSG_MASK
)paren
)paren
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|sysctl_icmpv6_time
r_static
r_int
id|sysctl_icmpv6_time
op_assign
l_int|1
op_star
id|HZ
suffix:semicolon
multiline_comment|/* &n; * Check the ICMP output rate limit &n; */
DECL|function|icmpv6_xrlim_allow
r_static
r_inline
r_int
id|icmpv6_xrlim_allow
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_int
id|type
comma
r_struct
id|flowi
op_star
id|fl
)paren
(brace
r_struct
id|dst_entry
op_star
id|dst
suffix:semicolon
r_int
id|res
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Informational messages are not limited. */
r_if
c_cond
(paren
id|type
op_amp
id|ICMPV6_INFOMSG_MASK
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/* Do not limit pmtu discovery, it would break it. */
r_if
c_cond
(paren
id|type
op_eq
id|ICMPV6_PKT_TOOBIG
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/* &n;&t; * Look up the output route.&n;&t; * XXX: perhaps the expire for routing entries cloned by&n;&t; * this lookup should be more aggressive (not longer than timeout).&n;&t; */
id|dst
op_assign
id|ip6_route_output
c_func
(paren
id|sk
comma
id|fl
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dst-&gt;error
)paren
(brace
id|IP6_INC_STATS
c_func
(paren
id|Ip6OutNoRoutes
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|dst-&gt;dev
op_logical_and
(paren
id|dst-&gt;dev-&gt;flags
op_amp
id|IFF_LOOPBACK
)paren
)paren
(brace
id|res
op_assign
l_int|1
suffix:semicolon
)brace
r_else
(brace
r_struct
id|rt6_info
op_star
id|rt
op_assign
(paren
r_struct
id|rt6_info
op_star
)paren
id|dst
suffix:semicolon
r_int
id|tmo
op_assign
id|sysctl_icmpv6_time
suffix:semicolon
multiline_comment|/* Give more bandwidth to wider prefixes. */
r_if
c_cond
(paren
id|rt-&gt;rt6i_dst.plen
OL
l_int|128
)paren
id|tmo
op_rshift_assign
(paren
(paren
l_int|128
op_minus
id|rt-&gt;rt6i_dst.plen
)paren
op_rshift
l_int|5
)paren
suffix:semicolon
id|res
op_assign
id|xrlim_allow
c_func
(paren
id|dst
comma
id|tmo
)paren
suffix:semicolon
)brace
id|dst_release
c_func
(paren
id|dst
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;an inline helper for the &quot;simple&quot; if statement below&n; *&t;checks if parameter problem report is caused by an&n; *&t;unrecognized IPv6 option that has the Option Type &n; *&t;highest-order two bits set to 10&n; */
DECL|function|opt_unrec
r_static
id|__inline__
r_int
id|opt_unrec
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
id|__u32
id|offset
)paren
(brace
id|u8
id|optval
suffix:semicolon
id|offset
op_add_assign
id|skb-&gt;nh.raw
op_minus
id|skb-&gt;data
suffix:semicolon
r_if
c_cond
(paren
id|skb_copy_bits
c_func
(paren
id|skb
comma
id|offset
comma
op_amp
id|optval
comma
l_int|1
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_return
(paren
id|optval
op_amp
l_int|0xC0
)paren
op_eq
l_int|0x80
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Send an ICMP message in response to a packet in error&n; */
DECL|function|icmpv6_send
r_void
id|icmpv6_send
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_int
id|type
comma
r_int
id|code
comma
id|__u32
id|info
comma
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_struct
id|ipv6hdr
op_star
id|hdr
op_assign
id|skb-&gt;nh.ipv6h
suffix:semicolon
r_struct
id|sock
op_star
id|sk
op_assign
id|icmpv6_socket-&gt;sk
suffix:semicolon
r_struct
id|in6_addr
op_star
id|saddr
op_assign
l_int|NULL
suffix:semicolon
r_int
id|iif
op_assign
l_int|0
suffix:semicolon
r_struct
id|icmpv6_msg
id|msg
suffix:semicolon
r_struct
id|flowi
id|fl
suffix:semicolon
r_int
id|addr_type
op_assign
l_int|0
suffix:semicolon
r_int
id|len
suffix:semicolon
r_if
c_cond
(paren
(paren
id|u8
op_star
)paren
id|hdr
template_param
id|skb-&gt;tail
)paren
r_return
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Make sure we respect the rules &n;&t; *&t;i.e. RFC 1885 2.4(e)&n;&t; *&t;Rule (e.1) is enforced by not using icmpv6_send&n;&t; *&t;in any code that processes icmp errors.&n;&t; */
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
id|ipv6_chk_addr
c_func
(paren
op_amp
id|hdr-&gt;daddr
comma
id|skb-&gt;dev
)paren
)paren
id|saddr
op_assign
op_amp
id|hdr-&gt;daddr
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Dest addr check&n;&t; */
r_if
c_cond
(paren
(paren
id|addr_type
op_amp
id|IPV6_ADDR_MULTICAST
op_logical_or
id|skb-&gt;pkt_type
op_ne
id|PACKET_HOST
)paren
)paren
(brace
r_if
c_cond
(paren
id|type
op_ne
id|ICMPV6_PKT_TOOBIG
op_logical_and
op_logical_neg
(paren
id|type
op_eq
id|ICMPV6_PARAMPROB
op_logical_and
id|code
op_eq
id|ICMPV6_UNK_OPTION
op_logical_and
(paren
id|opt_unrec
c_func
(paren
id|skb
comma
id|info
)paren
)paren
)paren
)paren
r_return
suffix:semicolon
id|saddr
op_assign
l_int|NULL
suffix:semicolon
)brace
id|addr_type
op_assign
id|ipv6_addr_type
c_func
(paren
op_amp
id|hdr-&gt;saddr
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Source addr check&n;&t; */
r_if
c_cond
(paren
id|addr_type
op_amp
id|IPV6_ADDR_LINKLOCAL
)paren
id|iif
op_assign
id|skb-&gt;dev-&gt;ifindex
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Must not send if we know that source is Anycast also.&n;&t; *&t;for now we don&squot;t know that.&n;&t; */
r_if
c_cond
(paren
(paren
id|addr_type
op_eq
id|IPV6_ADDR_ANY
)paren
op_logical_or
(paren
id|addr_type
op_amp
id|IPV6_ADDR_MULTICAST
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
id|KERN_DEBUG
l_string|&quot;icmpv6_send: addr_any/mcast source&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* &n;&t; *&t;Never answer to a ICMP packet.&n;&t; */
r_if
c_cond
(paren
id|is_ineligible
c_func
(paren
id|skb
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
id|KERN_DEBUG
l_string|&quot;icmpv6_send: no reply to icmp error&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|fl.proto
op_assign
id|IPPROTO_ICMPV6
suffix:semicolon
id|fl.nl_u.ip6_u.daddr
op_assign
op_amp
id|hdr-&gt;saddr
suffix:semicolon
id|fl.nl_u.ip6_u.saddr
op_assign
id|saddr
suffix:semicolon
id|fl.oif
op_assign
id|iif
suffix:semicolon
id|fl.fl6_flowlabel
op_assign
l_int|0
suffix:semicolon
id|fl.uli_u.icmpt.type
op_assign
id|type
suffix:semicolon
id|fl.uli_u.icmpt.code
op_assign
id|code
suffix:semicolon
id|icmpv6_xmit_lock
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|icmpv6_xrlim_allow
c_func
(paren
id|sk
comma
id|type
comma
op_amp
id|fl
)paren
)paren
r_goto
id|out
suffix:semicolon
multiline_comment|/*&n;&t; *&t;ok. kick it. checksum will be provided by the &n;&t; *&t;getfrag_t callback.&n;&t; */
id|msg.icmph.icmp6_type
op_assign
id|type
suffix:semicolon
id|msg.icmph.icmp6_code
op_assign
id|code
suffix:semicolon
id|msg.icmph.icmp6_cksum
op_assign
l_int|0
suffix:semicolon
id|msg.icmph.icmp6_pointer
op_assign
id|htonl
c_func
(paren
id|info
)paren
suffix:semicolon
id|msg.skb
op_assign
id|skb
suffix:semicolon
id|msg.offset
op_assign
id|skb-&gt;nh.raw
op_minus
id|skb-&gt;data
suffix:semicolon
id|msg.csum
op_assign
l_int|0
suffix:semicolon
id|msg.daddr
op_assign
op_amp
id|hdr-&gt;saddr
suffix:semicolon
id|len
op_assign
id|skb-&gt;len
op_minus
id|msg.offset
op_plus
r_sizeof
(paren
r_struct
id|icmp6hdr
)paren
suffix:semicolon
id|len
op_assign
id|min_t
c_func
(paren
r_int
r_int
comma
id|len
comma
id|IPV6_MIN_MTU
op_minus
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
id|len
OL
l_int|0
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
l_string|&quot;icmp: len problem&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|msg.len
op_assign
id|len
suffix:semicolon
id|ip6_build_xmit
c_func
(paren
id|sk
comma
id|icmpv6_getfrag
comma
op_amp
id|msg
comma
op_amp
id|fl
comma
id|len
comma
l_int|NULL
comma
op_minus
l_int|1
comma
id|MSG_DONTWAIT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|type
op_ge
id|ICMPV6_DEST_UNREACH
op_logical_and
id|type
op_le
id|ICMPV6_PARAMPROB
)paren
id|ICMP6_STATS_PTR_BH
c_func
(paren
id|Icmp6OutDestUnreachs
)paren
(braket
id|type
op_minus
id|ICMPV6_DEST_UNREACH
)braket
op_increment
suffix:semicolon
id|ICMP6_INC_STATS_BH
c_func
(paren
id|Icmp6OutMsgs
)paren
suffix:semicolon
id|out
suffix:colon
id|icmpv6_xmit_unlock
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|icmpv6_echo_reply
r_static
r_void
id|icmpv6_echo_reply
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|sock
op_star
id|sk
op_assign
id|icmpv6_socket-&gt;sk
suffix:semicolon
r_struct
id|icmp6hdr
op_star
id|icmph
op_assign
(paren
r_struct
id|icmp6hdr
op_star
)paren
id|skb-&gt;h.raw
suffix:semicolon
r_struct
id|in6_addr
op_star
id|saddr
suffix:semicolon
r_struct
id|icmpv6_msg
id|msg
suffix:semicolon
r_struct
id|flowi
id|fl
suffix:semicolon
id|saddr
op_assign
op_amp
id|skb-&gt;nh.ipv6h-&gt;daddr
suffix:semicolon
r_if
c_cond
(paren
id|ipv6_addr_type
c_func
(paren
id|saddr
)paren
op_amp
id|IPV6_ADDR_MULTICAST
op_logical_or
id|ipv6_chk_acast_addr
c_func
(paren
l_int|0
comma
id|saddr
)paren
)paren
id|saddr
op_assign
l_int|NULL
suffix:semicolon
id|msg.icmph.icmp6_type
op_assign
id|ICMPV6_ECHO_REPLY
suffix:semicolon
id|msg.icmph.icmp6_code
op_assign
l_int|0
suffix:semicolon
id|msg.icmph.icmp6_cksum
op_assign
l_int|0
suffix:semicolon
id|msg.icmph.icmp6_identifier
op_assign
id|icmph-&gt;icmp6_identifier
suffix:semicolon
id|msg.icmph.icmp6_sequence
op_assign
id|icmph-&gt;icmp6_sequence
suffix:semicolon
id|msg.skb
op_assign
id|skb
suffix:semicolon
id|msg.offset
op_assign
l_int|0
suffix:semicolon
id|msg.csum
op_assign
l_int|0
suffix:semicolon
id|msg.len
op_assign
id|skb-&gt;len
op_plus
r_sizeof
(paren
r_struct
id|icmp6hdr
)paren
suffix:semicolon
id|msg.daddr
op_assign
op_amp
id|skb-&gt;nh.ipv6h-&gt;saddr
suffix:semicolon
id|fl.proto
op_assign
id|IPPROTO_ICMPV6
suffix:semicolon
id|fl.nl_u.ip6_u.daddr
op_assign
id|msg.daddr
suffix:semicolon
id|fl.nl_u.ip6_u.saddr
op_assign
id|saddr
suffix:semicolon
id|fl.oif
op_assign
id|skb-&gt;dev-&gt;ifindex
suffix:semicolon
id|fl.fl6_flowlabel
op_assign
l_int|0
suffix:semicolon
id|fl.uli_u.icmpt.type
op_assign
id|ICMPV6_ECHO_REPLY
suffix:semicolon
id|fl.uli_u.icmpt.code
op_assign
l_int|0
suffix:semicolon
id|icmpv6_xmit_lock
c_func
(paren
)paren
suffix:semicolon
id|ip6_build_xmit
c_func
(paren
id|sk
comma
id|icmpv6_getfrag
comma
op_amp
id|msg
comma
op_amp
id|fl
comma
id|msg.len
comma
l_int|NULL
comma
op_minus
l_int|1
comma
id|MSG_DONTWAIT
)paren
suffix:semicolon
id|ICMP6_INC_STATS_BH
c_func
(paren
id|Icmp6OutEchoReplies
)paren
suffix:semicolon
id|ICMP6_INC_STATS_BH
c_func
(paren
id|Icmp6OutMsgs
)paren
suffix:semicolon
id|icmpv6_xmit_unlock
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|icmpv6_notify
r_static
r_void
id|icmpv6_notify
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_int
id|type
comma
r_int
id|code
comma
id|u32
id|info
)paren
(brace
r_struct
id|in6_addr
op_star
id|saddr
comma
op_star
id|daddr
suffix:semicolon
r_struct
id|inet6_protocol
op_star
id|ipprot
suffix:semicolon
r_struct
id|sock
op_star
id|sk
suffix:semicolon
r_int
id|inner_offset
suffix:semicolon
r_int
id|hash
suffix:semicolon
id|u8
id|nexthdr
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
r_return
suffix:semicolon
id|nexthdr
op_assign
(paren
(paren
r_struct
id|ipv6hdr
op_star
)paren
id|skb-&gt;data
)paren
op_member_access_from_pointer
id|nexthdr
suffix:semicolon
r_if
c_cond
(paren
id|ipv6_ext_hdr
c_func
(paren
id|nexthdr
)paren
)paren
(brace
multiline_comment|/* now skip over extension headers */
id|inner_offset
op_assign
id|ipv6_skip_exthdr
c_func
(paren
id|skb
comma
r_sizeof
(paren
r_struct
id|ipv6hdr
)paren
comma
op_amp
id|nexthdr
comma
id|skb-&gt;len
op_minus
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
id|inner_offset
OL
l_int|0
)paren
r_return
suffix:semicolon
)brace
r_else
(brace
id|inner_offset
op_assign
r_sizeof
(paren
r_struct
id|ipv6hdr
)paren
suffix:semicolon
)brace
multiline_comment|/* Checkin header including 8 bytes of inner protocol header. */
r_if
c_cond
(paren
op_logical_neg
id|pskb_may_pull
c_func
(paren
id|skb
comma
id|inner_offset
op_plus
l_int|8
)paren
)paren
r_return
suffix:semicolon
id|saddr
op_assign
op_amp
id|skb-&gt;nh.ipv6h-&gt;saddr
suffix:semicolon
id|daddr
op_assign
op_amp
id|skb-&gt;nh.ipv6h-&gt;daddr
suffix:semicolon
multiline_comment|/* BUGGG_FUTURE: we should try to parse exthdrs in this packet.&n;&t;   Without this we will not able f.e. to make source routed&n;&t;   pmtu discovery.&n;&t;   Corresponding argument (opt) to notifiers is already added.&n;&t;   --ANK (980726)&n;&t; */
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
id|ipprot
op_assign
id|inet6_protos
(braket
id|hash
)braket
suffix:semicolon
r_if
c_cond
(paren
id|ipprot
op_logical_and
id|ipprot-&gt;err_handler
)paren
id|ipprot
op_member_access_from_pointer
id|err_handler
c_func
(paren
id|skb
comma
l_int|NULL
comma
id|type
comma
id|code
comma
id|inner_offset
comma
id|info
)paren
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|raw_v6_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|sk
op_assign
id|raw_v6_htable
(braket
id|hash
)braket
)paren
op_ne
l_int|NULL
)paren
(brace
r_while
c_loop
(paren
(paren
id|sk
op_assign
id|__raw_v6_lookup
c_func
(paren
id|sk
comma
id|nexthdr
comma
id|daddr
comma
id|saddr
)paren
)paren
)paren
(brace
id|rawv6_err
c_func
(paren
id|sk
comma
id|skb
comma
l_int|NULL
comma
id|type
comma
id|code
comma
id|inner_offset
comma
id|info
)paren
suffix:semicolon
id|sk
op_assign
id|sk-&gt;next
suffix:semicolon
)brace
)brace
id|read_unlock
c_func
(paren
op_amp
id|raw_v6_lock
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Handle icmp messages&n; */
DECL|function|icmpv6_rcv
r_static
r_int
id|icmpv6_rcv
c_func
(paren
r_struct
id|sk_buff
op_star
op_star
id|pskb
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
id|pskb
suffix:semicolon
r_struct
id|net_device
op_star
id|dev
op_assign
id|skb-&gt;dev
suffix:semicolon
r_struct
id|in6_addr
op_star
id|saddr
comma
op_star
id|daddr
suffix:semicolon
r_struct
id|ipv6hdr
op_star
id|orig_hdr
suffix:semicolon
r_struct
id|icmp6hdr
op_star
id|hdr
suffix:semicolon
r_int
id|type
suffix:semicolon
id|ICMP6_INC_STATS_BH
c_func
(paren
id|Icmp6InMsgs
)paren
suffix:semicolon
id|saddr
op_assign
op_amp
id|skb-&gt;nh.ipv6h-&gt;saddr
suffix:semicolon
id|daddr
op_assign
op_amp
id|skb-&gt;nh.ipv6h-&gt;daddr
suffix:semicolon
multiline_comment|/* Perform checksum. */
r_if
c_cond
(paren
id|skb-&gt;ip_summed
op_eq
id|CHECKSUM_HW
)paren
(brace
id|skb-&gt;ip_summed
op_assign
id|CHECKSUM_UNNECESSARY
suffix:semicolon
r_if
c_cond
(paren
id|csum_ipv6_magic
c_func
(paren
id|saddr
comma
id|daddr
comma
id|skb-&gt;len
comma
id|IPPROTO_ICMPV6
comma
id|skb-&gt;csum
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
id|KERN_DEBUG
l_string|&quot;ICMPv6 hw checksum failed&bslash;n&quot;
)paren
suffix:semicolon
id|skb-&gt;ip_summed
op_assign
id|CHECKSUM_NONE
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|skb-&gt;ip_summed
op_eq
id|CHECKSUM_NONE
)paren
(brace
r_if
c_cond
(paren
id|csum_ipv6_magic
c_func
(paren
id|saddr
comma
id|daddr
comma
id|skb-&gt;len
comma
id|IPPROTO_ICMPV6
comma
id|skb_checksum
c_func
(paren
id|skb
comma
l_int|0
comma
id|skb-&gt;len
comma
l_int|0
)paren
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
id|KERN_DEBUG
l_string|&quot;ICMPv6 checksum failed [%04x:%04x:%04x:%04x:%04x:%04x:%04x:%04x &gt; %04x:%04x:%04x:%04x:%04x:%04x:%04x:%04x]&bslash;n&quot;
comma
id|ntohs
c_func
(paren
id|saddr-&gt;s6_addr16
(braket
l_int|0
)braket
)paren
comma
id|ntohs
c_func
(paren
id|saddr-&gt;s6_addr16
(braket
l_int|1
)braket
)paren
comma
id|ntohs
c_func
(paren
id|saddr-&gt;s6_addr16
(braket
l_int|2
)braket
)paren
comma
id|ntohs
c_func
(paren
id|saddr-&gt;s6_addr16
(braket
l_int|3
)braket
)paren
comma
id|ntohs
c_func
(paren
id|saddr-&gt;s6_addr16
(braket
l_int|4
)braket
)paren
comma
id|ntohs
c_func
(paren
id|saddr-&gt;s6_addr16
(braket
l_int|5
)braket
)paren
comma
id|ntohs
c_func
(paren
id|saddr-&gt;s6_addr16
(braket
l_int|6
)braket
)paren
comma
id|ntohs
c_func
(paren
id|saddr-&gt;s6_addr16
(braket
l_int|7
)braket
)paren
comma
id|ntohs
c_func
(paren
id|daddr-&gt;s6_addr16
(braket
l_int|0
)braket
)paren
comma
id|ntohs
c_func
(paren
id|daddr-&gt;s6_addr16
(braket
l_int|1
)braket
)paren
comma
id|ntohs
c_func
(paren
id|daddr-&gt;s6_addr16
(braket
l_int|2
)braket
)paren
comma
id|ntohs
c_func
(paren
id|daddr-&gt;s6_addr16
(braket
l_int|3
)braket
)paren
comma
id|ntohs
c_func
(paren
id|daddr-&gt;s6_addr16
(braket
l_int|4
)braket
)paren
comma
id|ntohs
c_func
(paren
id|daddr-&gt;s6_addr16
(braket
l_int|5
)braket
)paren
comma
id|ntohs
c_func
(paren
id|daddr-&gt;s6_addr16
(braket
l_int|6
)braket
)paren
comma
id|ntohs
c_func
(paren
id|daddr-&gt;s6_addr16
(braket
l_int|7
)braket
)paren
)paren
suffix:semicolon
r_goto
id|discard_it
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|pskb_pull
c_func
(paren
id|skb
comma
r_sizeof
(paren
r_struct
id|icmp6hdr
)paren
)paren
)paren
r_goto
id|discard_it
suffix:semicolon
id|hdr
op_assign
(paren
r_struct
id|icmp6hdr
op_star
)paren
id|skb-&gt;h.raw
suffix:semicolon
id|type
op_assign
id|hdr-&gt;icmp6_type
suffix:semicolon
r_if
c_cond
(paren
id|type
op_ge
id|ICMPV6_DEST_UNREACH
op_logical_and
id|type
op_le
id|ICMPV6_PARAMPROB
)paren
id|ICMP6_STATS_PTR_BH
c_func
(paren
id|Icmp6InDestUnreachs
)paren
(braket
id|type
op_minus
id|ICMPV6_DEST_UNREACH
)braket
op_increment
suffix:semicolon
r_else
r_if
c_cond
(paren
id|type
op_ge
id|ICMPV6_ECHO_REQUEST
op_logical_and
id|type
op_le
id|NDISC_REDIRECT
)paren
id|ICMP6_STATS_PTR_BH
c_func
(paren
id|Icmp6InEchos
)paren
(braket
id|type
op_minus
id|ICMPV6_ECHO_REQUEST
)braket
op_increment
suffix:semicolon
r_switch
c_cond
(paren
id|type
)paren
(brace
r_case
id|ICMPV6_ECHO_REQUEST
suffix:colon
id|icmpv6_echo_reply
c_func
(paren
id|skb
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ICMPV6_ECHO_REPLY
suffix:colon
multiline_comment|/* we couldn&squot;t care less */
r_break
suffix:semicolon
r_case
id|ICMPV6_PKT_TOOBIG
suffix:colon
multiline_comment|/* BUGGG_FUTURE: if packet contains rthdr, we cannot update&n;&t;&t;   standard destination cache. Seems, only &quot;advanced&quot;&n;&t;&t;   destination cache will allow to solve this problem&n;&t;&t;   --ANK (980726)&n;&t;&t; */
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
r_goto
id|discard_it
suffix:semicolon
id|hdr
op_assign
(paren
r_struct
id|icmp6hdr
op_star
)paren
id|skb-&gt;h.raw
suffix:semicolon
id|orig_hdr
op_assign
(paren
r_struct
id|ipv6hdr
op_star
)paren
(paren
id|hdr
op_plus
l_int|1
)paren
suffix:semicolon
id|rt6_pmtu_discovery
c_func
(paren
op_amp
id|orig_hdr-&gt;daddr
comma
op_amp
id|orig_hdr-&gt;saddr
comma
id|dev
comma
id|ntohl
c_func
(paren
id|hdr-&gt;icmp6_mtu
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; *&t;Drop through to notify&n;&t;&t; */
r_case
id|ICMPV6_DEST_UNREACH
suffix:colon
r_case
id|ICMPV6_TIME_EXCEED
suffix:colon
r_case
id|ICMPV6_PARAMPROB
suffix:colon
id|icmpv6_notify
c_func
(paren
id|skb
comma
id|type
comma
id|hdr-&gt;icmp6_code
comma
id|hdr-&gt;icmp6_mtu
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|NDISC_ROUTER_SOLICITATION
suffix:colon
r_case
id|NDISC_ROUTER_ADVERTISEMENT
suffix:colon
r_case
id|NDISC_NEIGHBOUR_SOLICITATION
suffix:colon
r_case
id|NDISC_NEIGHBOUR_ADVERTISEMENT
suffix:colon
r_case
id|NDISC_REDIRECT
suffix:colon
r_if
c_cond
(paren
id|skb_is_nonlinear
c_func
(paren
id|skb
)paren
op_logical_and
id|skb_linearize
c_func
(paren
id|skb
comma
id|GFP_ATOMIC
)paren
op_ne
l_int|0
)paren
(brace
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
id|ndisc_rcv
c_func
(paren
id|skb
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ICMPV6_MGM_QUERY
suffix:colon
id|igmp6_event_query
c_func
(paren
id|skb
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ICMPV6_MGM_REPORT
suffix:colon
id|igmp6_event_report
c_func
(paren
id|skb
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ICMPV6_MGM_REDUCTION
suffix:colon
r_break
suffix:semicolon
r_default
suffix:colon
(brace
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
l_string|&quot;icmpv6: msg of unknown type&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* informational */
r_if
c_cond
(paren
id|type
op_amp
id|ICMPV6_INFOMSG_MASK
)paren
r_break
suffix:semicolon
multiline_comment|/* &n;&t;&t; * error of unkown type. &n;&t;&t; * must pass to upper level &n;&t;&t; */
id|icmpv6_notify
c_func
(paren
id|skb
comma
id|type
comma
id|hdr-&gt;icmp6_code
comma
id|hdr-&gt;icmp6_mtu
)paren
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
id|discard_it
suffix:colon
id|ICMP6_INC_STATS_BH
c_func
(paren
id|Icmp6InErrors
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
DECL|function|icmpv6_init
r_int
id|__init
id|icmpv6_init
c_func
(paren
r_struct
id|net_proto_family
op_star
id|ops
)paren
(brace
r_struct
id|sock
op_star
id|sk
suffix:semicolon
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
id|NR_CPUS
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cpu_possible
c_func
(paren
id|i
)paren
)paren
r_continue
suffix:semicolon
id|err
op_assign
id|sock_create
c_func
(paren
id|PF_INET6
comma
id|SOCK_RAW
comma
id|IPPROTO_ICMPV6
comma
op_amp
id|__icmpv6_socket
(braket
id|i
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
(brace
r_int
id|j
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Failed to initialize the ICMP6 control socket &quot;
l_string|&quot;(err %d).&bslash;n&quot;
comma
id|err
)paren
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|i
suffix:semicolon
id|j
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|cpu_possible
c_func
(paren
id|j
)paren
)paren
r_continue
suffix:semicolon
id|sock_release
c_func
(paren
id|__icmpv6_socket
(braket
id|j
)braket
)paren
suffix:semicolon
id|__icmpv6_socket
(braket
id|j
)braket
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* for safety */
)brace
r_return
id|err
suffix:semicolon
)brace
id|sk
op_assign
id|__icmpv6_socket
(braket
id|i
)braket
op_member_access_from_pointer
id|sk
suffix:semicolon
id|sk-&gt;allocation
op_assign
id|GFP_ATOMIC
suffix:semicolon
id|sk-&gt;sndbuf
op_assign
id|SK_WMEM_MAX
op_star
l_int|2
suffix:semicolon
id|sk-&gt;prot
op_member_access_from_pointer
id|unhash
c_func
(paren
id|sk
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|inet6_add_protocol
c_func
(paren
op_amp
id|icmpv6_protocol
comma
id|IPPROTO_ICMPV6
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Failed to register ICMP6 protocol&bslash;n&quot;
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
id|NR_CPUS
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|cpu_possible
c_func
(paren
id|i
)paren
)paren
r_continue
suffix:semicolon
id|sock_release
c_func
(paren
id|__icmpv6_socket
(braket
id|i
)braket
)paren
suffix:semicolon
id|__icmpv6_socket
(braket
id|i
)braket
op_assign
l_int|NULL
suffix:semicolon
)brace
r_return
op_minus
id|EAGAIN
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|icmpv6_cleanup
r_void
id|icmpv6_cleanup
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
id|NR_CPUS
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|cpu_possible
c_func
(paren
id|i
)paren
)paren
r_continue
suffix:semicolon
id|sock_release
c_func
(paren
id|__icmpv6_socket
(braket
id|i
)braket
)paren
suffix:semicolon
id|__icmpv6_socket
(braket
id|i
)braket
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* For safety. */
)brace
id|inet6_del_protocol
c_func
(paren
op_amp
id|icmpv6_protocol
comma
id|IPPROTO_ICMPV6
)paren
suffix:semicolon
)brace
DECL|struct|icmp6_err
r_static
r_struct
id|icmp6_err
(brace
DECL|member|err
r_int
id|err
suffix:semicolon
DECL|member|fatal
r_int
id|fatal
suffix:semicolon
DECL|variable|tab_unreach
)brace
id|tab_unreach
(braket
)braket
op_assign
(brace
(brace
id|ENETUNREACH
comma
l_int|0
)brace
comma
multiline_comment|/* NOROUTE&t;&t;*/
(brace
id|EACCES
comma
l_int|1
)brace
comma
multiline_comment|/* ADM_PROHIBITED&t;*/
(brace
id|EHOSTUNREACH
comma
l_int|0
)brace
comma
multiline_comment|/* Was NOT_NEIGHBOUR, now reserved */
(brace
id|EHOSTUNREACH
comma
l_int|0
)brace
comma
multiline_comment|/* ADDR_UNREACH&t;&t;*/
(brace
id|ECONNREFUSED
comma
l_int|1
)brace
comma
multiline_comment|/* PORT_UNREACH&t;&t;*/
)brace
suffix:semicolon
DECL|function|icmpv6_err_convert
r_int
id|icmpv6_err_convert
c_func
(paren
r_int
id|type
comma
r_int
id|code
comma
r_int
op_star
id|err
)paren
(brace
r_int
id|fatal
op_assign
l_int|0
suffix:semicolon
op_star
id|err
op_assign
id|EPROTO
suffix:semicolon
r_switch
c_cond
(paren
id|type
)paren
(brace
r_case
id|ICMPV6_DEST_UNREACH
suffix:colon
id|fatal
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|code
op_le
id|ICMPV6_PORT_UNREACH
)paren
(brace
op_star
id|err
op_assign
id|tab_unreach
(braket
id|code
)braket
dot
id|err
suffix:semicolon
id|fatal
op_assign
id|tab_unreach
(braket
id|code
)braket
dot
id|fatal
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|ICMPV6_PKT_TOOBIG
suffix:colon
op_star
id|err
op_assign
id|EMSGSIZE
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ICMPV6_PARAMPROB
suffix:colon
op_star
id|err
op_assign
id|EPROTO
suffix:semicolon
id|fatal
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ICMPV6_TIME_EXCEED
suffix:colon
op_star
id|err
op_assign
id|EHOSTUNREACH
suffix:semicolon
r_break
suffix:semicolon
)brace
suffix:semicolon
r_return
id|fatal
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_SYSCTL
DECL|variable|ipv6_icmp_table
id|ctl_table
id|ipv6_icmp_table
(braket
)braket
op_assign
(brace
(brace
dot
id|ctl_name
op_assign
id|NET_IPV6_ICMP_RATELIMIT
comma
dot
id|procname
op_assign
l_string|&quot;ratelimit&quot;
comma
dot
id|data
op_assign
op_amp
id|sysctl_icmpv6_time
comma
dot
id|maxlen
op_assign
r_sizeof
(paren
r_int
)paren
comma
dot
id|mode
op_assign
l_int|0644
comma
dot
id|proc_handler
op_assign
op_amp
id|proc_dointvec
)brace
comma
(brace
dot
id|ctl_name
op_assign
l_int|0
)brace
comma
)brace
suffix:semicolon
macro_line|#endif
eof
