multiline_comment|/*&n; * This is a module which is used for rejecting packets.&n; * Added support for customized reject packets (Jozsef Kadlecsik).&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/ip.h&gt;
macro_line|#include &lt;linux/udp.h&gt;
macro_line|#include &lt;linux/icmp.h&gt;
macro_line|#include &lt;net/icmp.h&gt;
macro_line|#include &lt;net/ip.h&gt;
macro_line|#include &lt;net/tcp.h&gt;
r_struct
id|in_device
suffix:semicolon
macro_line|#include &lt;net/route.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ip_tables.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ipt_REJECT.h&gt;
macro_line|#if 0
mdefine_line|#define DEBUGP printk
macro_line|#else
DECL|macro|DEBUGP
mdefine_line|#define DEBUGP(format, args...)
macro_line|#endif
multiline_comment|/* If the original packet is part of a connection, but the connection&n;   is not confirmed, our manufactured reply will not be associated&n;   with it, so we need to do this manually. */
DECL|function|connection_attach
r_static
r_void
id|connection_attach
c_func
(paren
r_struct
id|sk_buff
op_star
id|new_skb
comma
r_struct
id|nf_ct_info
op_star
id|nfct
)paren
(brace
r_void
(paren
op_star
id|attach
)paren
(paren
r_struct
id|sk_buff
op_star
comma
r_struct
id|nf_ct_info
op_star
)paren
suffix:semicolon
multiline_comment|/* Avoid module unload race with ip_ct_attach being NULLed out */
r_if
c_cond
(paren
id|nfct
op_logical_and
(paren
id|attach
op_assign
id|ip_ct_attach
)paren
op_ne
l_int|NULL
)paren
id|attach
c_func
(paren
id|new_skb
comma
id|nfct
)paren
suffix:semicolon
)brace
multiline_comment|/* Send RST reply */
DECL|function|send_reset
r_static
r_void
id|send_reset
c_func
(paren
r_struct
id|sk_buff
op_star
id|oldskb
comma
r_int
id|local
)paren
(brace
r_struct
id|sk_buff
op_star
id|nskb
suffix:semicolon
r_struct
id|tcphdr
op_star
id|otcph
comma
op_star
id|tcph
suffix:semicolon
r_struct
id|rtable
op_star
id|rt
suffix:semicolon
r_int
r_int
id|otcplen
suffix:semicolon
id|u_int16_t
id|tmp_port
suffix:semicolon
id|u_int32_t
id|tmp_addr
suffix:semicolon
r_int
id|needs_ack
suffix:semicolon
r_int
id|hh_len
suffix:semicolon
multiline_comment|/* IP header checks: fragment, too short. */
r_if
c_cond
(paren
id|oldskb-&gt;nh.iph-&gt;frag_off
op_amp
id|htons
c_func
(paren
id|IP_OFFSET
)paren
op_logical_or
id|oldskb-&gt;len
OL
(paren
id|oldskb-&gt;nh.iph-&gt;ihl
op_lshift
l_int|2
)paren
op_plus
r_sizeof
(paren
r_struct
id|tcphdr
)paren
)paren
r_return
suffix:semicolon
id|otcph
op_assign
(paren
r_struct
id|tcphdr
op_star
)paren
(paren
(paren
id|u_int32_t
op_star
)paren
id|oldskb-&gt;nh.iph
op_plus
id|oldskb-&gt;nh.iph-&gt;ihl
)paren
suffix:semicolon
id|otcplen
op_assign
id|oldskb-&gt;len
op_minus
id|oldskb-&gt;nh.iph-&gt;ihl
op_star
l_int|4
suffix:semicolon
multiline_comment|/* No RST for RST. */
r_if
c_cond
(paren
id|otcph-&gt;rst
)paren
r_return
suffix:semicolon
multiline_comment|/* Check checksum. */
r_if
c_cond
(paren
id|tcp_v4_check
c_func
(paren
id|otcph
comma
id|otcplen
comma
id|oldskb-&gt;nh.iph-&gt;saddr
comma
id|oldskb-&gt;nh.iph-&gt;daddr
comma
id|csum_partial
c_func
(paren
(paren
r_char
op_star
)paren
id|otcph
comma
id|otcplen
comma
l_int|0
)paren
)paren
op_ne
l_int|0
)paren
r_return
suffix:semicolon
(brace
r_struct
id|flowi
id|fl
op_assign
(brace
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
id|oldskb-&gt;nh.iph-&gt;saddr
comma
dot
id|saddr
op_assign
(paren
id|local
ques
c_cond
id|oldskb-&gt;nh.iph-&gt;daddr
suffix:colon
l_int|0
)paren
comma
dot
id|tos
op_assign
(paren
id|RT_TOS
c_func
(paren
id|oldskb-&gt;nh.iph-&gt;tos
)paren
op_or
id|RTO_CONN
)paren
)brace
)brace
)brace
suffix:semicolon
multiline_comment|/* Routing: if not headed for us, route won&squot;t like source */
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
r_return
suffix:semicolon
id|hh_len
op_assign
(paren
id|rt-&gt;u.dst.dev-&gt;hard_header_len
op_plus
l_int|15
)paren
op_amp
op_complement
l_int|15
suffix:semicolon
)brace
multiline_comment|/* Copy skb (even if skb is about to be dropped, we can&squot;t just&n;           clone it because there may be other things, such as tcpdump,&n;           interested in it). We also need to expand headroom in case&n;&t;   hh_len of incoming interface &lt; hh_len of outgoing interface */
id|nskb
op_assign
id|skb_copy_expand
c_func
(paren
id|oldskb
comma
id|hh_len
comma
id|skb_tailroom
c_func
(paren
id|oldskb
)paren
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|nskb
)paren
r_return
suffix:semicolon
id|dst_release
c_func
(paren
id|nskb-&gt;dst
)paren
suffix:semicolon
id|nskb-&gt;dst
op_assign
op_amp
id|rt-&gt;u.dst
suffix:semicolon
multiline_comment|/* This packet will not be the same as the other: clear nf fields */
id|nf_conntrack_put
c_func
(paren
id|nskb-&gt;nfct
)paren
suffix:semicolon
id|nskb-&gt;nfct
op_assign
l_int|NULL
suffix:semicolon
id|nskb-&gt;nfcache
op_assign
l_int|0
suffix:semicolon
macro_line|#ifdef CONFIG_NETFILTER_DEBUG
id|nskb-&gt;nf_debug
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
id|nskb-&gt;nfmark
op_assign
l_int|0
suffix:semicolon
id|tcph
op_assign
(paren
r_struct
id|tcphdr
op_star
)paren
(paren
(paren
id|u_int32_t
op_star
)paren
id|nskb-&gt;nh.iph
op_plus
id|nskb-&gt;nh.iph-&gt;ihl
)paren
suffix:semicolon
multiline_comment|/* Swap source and dest */
id|tmp_addr
op_assign
id|nskb-&gt;nh.iph-&gt;saddr
suffix:semicolon
id|nskb-&gt;nh.iph-&gt;saddr
op_assign
id|nskb-&gt;nh.iph-&gt;daddr
suffix:semicolon
id|nskb-&gt;nh.iph-&gt;daddr
op_assign
id|tmp_addr
suffix:semicolon
id|tmp_port
op_assign
id|tcph-&gt;source
suffix:semicolon
id|tcph-&gt;source
op_assign
id|tcph-&gt;dest
suffix:semicolon
id|tcph-&gt;dest
op_assign
id|tmp_port
suffix:semicolon
multiline_comment|/* Truncate to length (no data) */
id|tcph-&gt;doff
op_assign
r_sizeof
(paren
r_struct
id|tcphdr
)paren
op_div
l_int|4
suffix:semicolon
id|skb_trim
c_func
(paren
id|nskb
comma
id|nskb-&gt;nh.iph-&gt;ihl
op_star
l_int|4
op_plus
r_sizeof
(paren
r_struct
id|tcphdr
)paren
)paren
suffix:semicolon
id|nskb-&gt;nh.iph-&gt;tot_len
op_assign
id|htons
c_func
(paren
id|nskb-&gt;len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tcph-&gt;ack
)paren
(brace
id|needs_ack
op_assign
l_int|0
suffix:semicolon
id|tcph-&gt;seq
op_assign
id|otcph-&gt;ack_seq
suffix:semicolon
id|tcph-&gt;ack_seq
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|needs_ack
op_assign
l_int|1
suffix:semicolon
id|tcph-&gt;ack_seq
op_assign
id|htonl
c_func
(paren
id|ntohl
c_func
(paren
id|otcph-&gt;seq
)paren
op_plus
id|otcph-&gt;syn
op_plus
id|otcph-&gt;fin
op_plus
id|otcplen
op_minus
(paren
id|otcph-&gt;doff
op_lshift
l_int|2
)paren
)paren
suffix:semicolon
id|tcph-&gt;seq
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Reset flags */
(paren
(paren
id|u_int8_t
op_star
)paren
id|tcph
)paren
(braket
l_int|13
)braket
op_assign
l_int|0
suffix:semicolon
id|tcph-&gt;rst
op_assign
l_int|1
suffix:semicolon
id|tcph-&gt;ack
op_assign
id|needs_ack
suffix:semicolon
id|tcph-&gt;window
op_assign
l_int|0
suffix:semicolon
id|tcph-&gt;urg_ptr
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Adjust TCP checksum */
id|tcph-&gt;check
op_assign
l_int|0
suffix:semicolon
id|tcph-&gt;check
op_assign
id|tcp_v4_check
c_func
(paren
id|tcph
comma
r_sizeof
(paren
r_struct
id|tcphdr
)paren
comma
id|nskb-&gt;nh.iph-&gt;saddr
comma
id|nskb-&gt;nh.iph-&gt;daddr
comma
id|csum_partial
c_func
(paren
(paren
r_char
op_star
)paren
id|tcph
comma
r_sizeof
(paren
r_struct
id|tcphdr
)paren
comma
l_int|0
)paren
)paren
suffix:semicolon
multiline_comment|/* Adjust IP TTL, DF */
id|nskb-&gt;nh.iph-&gt;ttl
op_assign
id|MAXTTL
suffix:semicolon
multiline_comment|/* Set DF, id = 0 */
id|nskb-&gt;nh.iph-&gt;frag_off
op_assign
id|htons
c_func
(paren
id|IP_DF
)paren
suffix:semicolon
id|nskb-&gt;nh.iph-&gt;id
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Adjust IP checksum */
id|nskb-&gt;nh.iph-&gt;check
op_assign
l_int|0
suffix:semicolon
id|nskb-&gt;nh.iph-&gt;check
op_assign
id|ip_fast_csum
c_func
(paren
(paren
r_int
r_char
op_star
)paren
id|nskb-&gt;nh.iph
comma
id|nskb-&gt;nh.iph-&gt;ihl
)paren
suffix:semicolon
multiline_comment|/* &quot;Never happens&quot; */
r_if
c_cond
(paren
id|nskb-&gt;len
OG
id|dst_pmtu
c_func
(paren
id|nskb-&gt;dst
)paren
)paren
r_goto
id|free_nskb
suffix:semicolon
id|connection_attach
c_func
(paren
id|nskb
comma
id|oldskb-&gt;nfct
)paren
suffix:semicolon
id|NF_HOOK
c_func
(paren
id|PF_INET
comma
id|NF_IP_LOCAL_OUT
comma
id|nskb
comma
l_int|NULL
comma
id|nskb-&gt;dst-&gt;dev
comma
id|ip_finish_output
)paren
suffix:semicolon
r_return
suffix:semicolon
id|free_nskb
suffix:colon
id|kfree_skb
c_func
(paren
id|nskb
)paren
suffix:semicolon
)brace
DECL|function|send_unreach
r_static
r_void
id|send_unreach
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb_in
comma
r_int
id|code
)paren
(brace
r_struct
id|iphdr
op_star
id|iph
suffix:semicolon
r_struct
id|udphdr
op_star
id|udph
suffix:semicolon
r_struct
id|icmphdr
op_star
id|icmph
suffix:semicolon
r_struct
id|sk_buff
op_star
id|nskb
suffix:semicolon
id|u32
id|saddr
suffix:semicolon
id|u8
id|tos
suffix:semicolon
r_int
id|hh_len
comma
id|length
suffix:semicolon
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
id|skb_in-&gt;dst
suffix:semicolon
r_int
r_char
op_star
id|data
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rt
)paren
r_return
suffix:semicolon
multiline_comment|/* FIXME: Use sysctl number. --RR */
r_if
c_cond
(paren
op_logical_neg
id|xrlim_allow
c_func
(paren
op_amp
id|rt-&gt;u.dst
comma
l_int|1
op_star
id|HZ
)paren
)paren
r_return
suffix:semicolon
id|iph
op_assign
id|skb_in-&gt;nh.iph
suffix:semicolon
multiline_comment|/* No replies to physical multicast/broadcast */
r_if
c_cond
(paren
id|skb_in-&gt;pkt_type
op_ne
id|PACKET_HOST
)paren
r_return
suffix:semicolon
multiline_comment|/* Now check at the protocol level */
r_if
c_cond
(paren
id|rt-&gt;rt_flags
op_amp
(paren
id|RTCF_BROADCAST
op_or
id|RTCF_MULTICAST
)paren
)paren
r_return
suffix:semicolon
multiline_comment|/* Only reply to fragment 0. */
r_if
c_cond
(paren
id|iph-&gt;frag_off
op_amp
id|htons
c_func
(paren
id|IP_OFFSET
)paren
)paren
r_return
suffix:semicolon
multiline_comment|/* if UDP checksum is set, verify it&squot;s correct */
r_if
c_cond
(paren
id|iph-&gt;protocol
op_eq
id|IPPROTO_UDP
op_logical_and
id|skb_in-&gt;tail
op_minus
(paren
id|u8
op_star
)paren
id|iph
op_ge
r_sizeof
(paren
r_struct
id|udphdr
)paren
)paren
(brace
r_int
id|datalen
op_assign
id|skb_in-&gt;len
op_minus
(paren
id|iph-&gt;ihl
op_lshift
l_int|2
)paren
suffix:semicolon
id|udph
op_assign
(paren
r_struct
id|udphdr
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
r_if
c_cond
(paren
id|udph-&gt;check
op_logical_and
id|csum_tcpudp_magic
c_func
(paren
id|iph-&gt;saddr
comma
id|iph-&gt;daddr
comma
id|datalen
comma
id|IPPROTO_UDP
comma
id|csum_partial
c_func
(paren
(paren
r_char
op_star
)paren
id|udph
comma
id|datalen
comma
l_int|0
)paren
)paren
op_ne
l_int|0
)paren
r_return
suffix:semicolon
)brace
multiline_comment|/* If we send an ICMP error to an ICMP error a mess would result.. */
r_if
c_cond
(paren
id|iph-&gt;protocol
op_eq
id|IPPROTO_ICMP
op_logical_and
id|skb_in-&gt;tail
op_minus
(paren
id|u8
op_star
)paren
id|iph
op_ge
r_sizeof
(paren
r_struct
id|icmphdr
)paren
)paren
(brace
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
multiline_comment|/* Between echo-reply (0) and timestamp (13),&n;&t;&t;   everything except echo-request (8) is an error.&n;&t;&t;   Also, anything greater than NR_ICMP_TYPES is&n;&t;&t;   unknown, and hence should be treated as an error... */
r_if
c_cond
(paren
(paren
id|icmph-&gt;type
OL
id|ICMP_TIMESTAMP
op_logical_and
id|icmph-&gt;type
op_ne
id|ICMP_ECHOREPLY
op_logical_and
id|icmph-&gt;type
op_ne
id|ICMP_ECHO
)paren
op_logical_or
id|icmph-&gt;type
OG
id|NR_ICMP_TYPES
)paren
r_return
suffix:semicolon
)brace
id|saddr
op_assign
id|iph-&gt;daddr
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|rt-&gt;rt_flags
op_amp
id|RTCF_LOCAL
)paren
)paren
id|saddr
op_assign
l_int|0
suffix:semicolon
id|tos
op_assign
(paren
id|iph-&gt;tos
op_amp
id|IPTOS_TOS_MASK
)paren
op_or
id|IPTOS_PREC_INTERNETCONTROL
suffix:semicolon
(brace
r_struct
id|flowi
id|fl
op_assign
(brace
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
id|iph-&gt;saddr
comma
dot
id|saddr
op_assign
id|saddr
comma
dot
id|tos
op_assign
id|RT_TOS
c_func
(paren
id|tos
)paren
)brace
)brace
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
r_return
suffix:semicolon
)brace
multiline_comment|/* RFC says return as much as we can without exceeding 576 bytes. */
id|length
op_assign
id|skb_in-&gt;len
op_plus
r_sizeof
(paren
r_struct
id|iphdr
)paren
op_plus
r_sizeof
(paren
r_struct
id|icmphdr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|length
OG
id|dst_pmtu
c_func
(paren
op_amp
id|rt-&gt;u.dst
)paren
)paren
id|length
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
id|length
OG
l_int|576
)paren
id|length
op_assign
l_int|576
suffix:semicolon
id|hh_len
op_assign
(paren
id|rt-&gt;u.dst.dev-&gt;hard_header_len
op_plus
l_int|15
)paren
op_amp
op_complement
l_int|15
suffix:semicolon
id|nskb
op_assign
id|alloc_skb
c_func
(paren
id|hh_len
op_plus
l_int|15
op_plus
id|length
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|nskb
)paren
(brace
id|ip_rt_put
c_func
(paren
id|rt
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|nskb-&gt;priority
op_assign
l_int|0
suffix:semicolon
id|nskb-&gt;dst
op_assign
op_amp
id|rt-&gt;u.dst
suffix:semicolon
id|skb_reserve
c_func
(paren
id|nskb
comma
id|hh_len
)paren
suffix:semicolon
multiline_comment|/* Set up IP header */
id|iph
op_assign
id|nskb-&gt;nh.iph
op_assign
(paren
r_struct
id|iphdr
op_star
)paren
id|skb_put
c_func
(paren
id|nskb
comma
r_sizeof
(paren
r_struct
id|iphdr
)paren
)paren
suffix:semicolon
id|iph-&gt;version
op_assign
l_int|4
suffix:semicolon
id|iph-&gt;ihl
op_assign
l_int|5
suffix:semicolon
id|iph-&gt;tos
op_assign
id|tos
suffix:semicolon
id|iph-&gt;tot_len
op_assign
id|htons
c_func
(paren
id|length
)paren
suffix:semicolon
multiline_comment|/* PMTU discovery never applies to ICMP packets. */
id|iph-&gt;frag_off
op_assign
l_int|0
suffix:semicolon
id|iph-&gt;ttl
op_assign
id|MAXTTL
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
id|iph-&gt;protocol
op_assign
id|IPPROTO_ICMP
suffix:semicolon
id|iph-&gt;saddr
op_assign
id|rt-&gt;rt_src
suffix:semicolon
id|iph-&gt;daddr
op_assign
id|rt-&gt;rt_dst
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
multiline_comment|/* Set up ICMP header. */
id|icmph
op_assign
id|nskb-&gt;h.icmph
op_assign
(paren
r_struct
id|icmphdr
op_star
)paren
id|skb_put
c_func
(paren
id|nskb
comma
r_sizeof
(paren
r_struct
id|icmphdr
)paren
)paren
suffix:semicolon
id|icmph-&gt;type
op_assign
id|ICMP_DEST_UNREACH
suffix:semicolon
id|icmph-&gt;code
op_assign
id|code
suffix:semicolon
id|icmph-&gt;un.gateway
op_assign
l_int|0
suffix:semicolon
id|icmph-&gt;checksum
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Copy as much of original packet as will fit */
id|data
op_assign
id|skb_put
c_func
(paren
id|nskb
comma
id|length
op_minus
r_sizeof
(paren
r_struct
id|iphdr
)paren
op_minus
r_sizeof
(paren
r_struct
id|icmphdr
)paren
)paren
suffix:semicolon
multiline_comment|/* FIXME: won&squot;t work with nonlinear skbs --RR */
id|memcpy
c_func
(paren
id|data
comma
id|skb_in-&gt;nh.iph
comma
id|length
op_minus
r_sizeof
(paren
r_struct
id|iphdr
)paren
op_minus
r_sizeof
(paren
r_struct
id|icmphdr
)paren
)paren
suffix:semicolon
id|icmph-&gt;checksum
op_assign
id|ip_compute_csum
c_func
(paren
(paren
r_int
r_char
op_star
)paren
id|icmph
comma
id|length
op_minus
r_sizeof
(paren
r_struct
id|iphdr
)paren
)paren
suffix:semicolon
id|connection_attach
c_func
(paren
id|nskb
comma
id|skb_in-&gt;nfct
)paren
suffix:semicolon
id|NF_HOOK
c_func
(paren
id|PF_INET
comma
id|NF_IP_LOCAL_OUT
comma
id|nskb
comma
l_int|NULL
comma
id|nskb-&gt;dst-&gt;dev
comma
id|ip_finish_output
)paren
suffix:semicolon
)brace
DECL|function|reject
r_static
r_int
r_int
id|reject
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
id|hooknum
comma
r_const
r_struct
id|net_device
op_star
id|in
comma
r_const
r_struct
id|net_device
op_star
id|out
comma
r_const
r_void
op_star
id|targinfo
comma
r_void
op_star
id|userinfo
)paren
(brace
r_const
r_struct
id|ipt_reject_info
op_star
id|reject
op_assign
id|targinfo
suffix:semicolon
multiline_comment|/* Our naive response construction doesn&squot;t deal with IP&n;           options, and probably shouldn&squot;t try. */
r_if
c_cond
(paren
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|nh.iph-&gt;ihl
op_lshift
l_int|2
op_ne
r_sizeof
(paren
r_struct
id|iphdr
)paren
)paren
r_return
id|NF_DROP
suffix:semicolon
multiline_comment|/* WARNING: This code causes reentry within iptables.&n;&t;   This means that the iptables jump stack is now crap.  We&n;&t;   must return an absolute verdict. --RR */
r_switch
c_cond
(paren
id|reject-&gt;with
)paren
(brace
r_case
id|IPT_ICMP_NET_UNREACHABLE
suffix:colon
id|send_unreach
c_func
(paren
op_star
id|pskb
comma
id|ICMP_NET_UNREACH
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IPT_ICMP_HOST_UNREACHABLE
suffix:colon
id|send_unreach
c_func
(paren
op_star
id|pskb
comma
id|ICMP_HOST_UNREACH
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IPT_ICMP_PROT_UNREACHABLE
suffix:colon
id|send_unreach
c_func
(paren
op_star
id|pskb
comma
id|ICMP_PROT_UNREACH
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IPT_ICMP_PORT_UNREACHABLE
suffix:colon
id|send_unreach
c_func
(paren
op_star
id|pskb
comma
id|ICMP_PORT_UNREACH
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IPT_ICMP_NET_PROHIBITED
suffix:colon
id|send_unreach
c_func
(paren
op_star
id|pskb
comma
id|ICMP_NET_ANO
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IPT_ICMP_HOST_PROHIBITED
suffix:colon
id|send_unreach
c_func
(paren
op_star
id|pskb
comma
id|ICMP_HOST_ANO
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IPT_TCP_RESET
suffix:colon
id|send_reset
c_func
(paren
op_star
id|pskb
comma
id|hooknum
op_eq
id|NF_IP_LOCAL_IN
)paren
suffix:semicolon
r_case
id|IPT_ICMP_ECHOREPLY
suffix:colon
multiline_comment|/* Doesn&squot;t happen. */
r_break
suffix:semicolon
)brace
r_return
id|NF_DROP
suffix:semicolon
)brace
DECL|function|check
r_static
r_int
id|check
c_func
(paren
r_const
r_char
op_star
id|tablename
comma
r_const
r_struct
id|ipt_entry
op_star
id|e
comma
r_void
op_star
id|targinfo
comma
r_int
r_int
id|targinfosize
comma
r_int
r_int
id|hook_mask
)paren
(brace
r_const
r_struct
id|ipt_reject_info
op_star
id|rejinfo
op_assign
id|targinfo
suffix:semicolon
r_if
c_cond
(paren
id|targinfosize
op_ne
id|IPT_ALIGN
c_func
(paren
r_sizeof
(paren
r_struct
id|ipt_reject_info
)paren
)paren
)paren
(brace
id|DEBUGP
c_func
(paren
l_string|&quot;REJECT: targinfosize %u != 0&bslash;n&quot;
comma
id|targinfosize
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Only allow these for packet filtering. */
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|tablename
comma
l_string|&quot;filter&quot;
)paren
op_ne
l_int|0
)paren
(brace
id|DEBUGP
c_func
(paren
l_string|&quot;REJECT: bad table `%s&squot;.&bslash;n&quot;
comma
id|tablename
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|hook_mask
op_amp
op_complement
(paren
(paren
l_int|1
op_lshift
id|NF_IP_LOCAL_IN
)paren
op_or
(paren
l_int|1
op_lshift
id|NF_IP_FORWARD
)paren
op_or
(paren
l_int|1
op_lshift
id|NF_IP_LOCAL_OUT
)paren
)paren
)paren
op_ne
l_int|0
)paren
(brace
id|DEBUGP
c_func
(paren
l_string|&quot;REJECT: bad hook mask %X&bslash;n&quot;
comma
id|hook_mask
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|rejinfo-&gt;with
op_eq
id|IPT_ICMP_ECHOREPLY
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;REJECT: ECHOREPLY no longer supported.&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|rejinfo-&gt;with
op_eq
id|IPT_TCP_RESET
)paren
(brace
multiline_comment|/* Must specify that it&squot;s a TCP packet */
r_if
c_cond
(paren
id|e-&gt;ip.proto
op_ne
id|IPPROTO_TCP
op_logical_or
(paren
id|e-&gt;ip.invflags
op_amp
id|IPT_INV_PROTO
)paren
)paren
(brace
id|DEBUGP
c_func
(paren
l_string|&quot;REJECT: TCP_RESET illegal for non-tcp&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|variable|ipt_reject_reg
r_static
r_struct
id|ipt_target
id|ipt_reject_reg
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;REJECT&quot;
comma
dot
id|target
op_assign
id|reject
comma
dot
id|checkentry
op_assign
id|check
comma
dot
id|me
op_assign
id|THIS_MODULE
comma
)brace
suffix:semicolon
DECL|function|init
r_static
r_int
id|__init
id|init
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|ipt_register_target
c_func
(paren
op_amp
id|ipt_reject_reg
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|fini
r_static
r_void
id|__exit
id|fini
c_func
(paren
r_void
)paren
(brace
id|ipt_unregister_target
c_func
(paren
op_amp
id|ipt_reject_reg
)paren
suffix:semicolon
)brace
DECL|variable|init
id|module_init
c_func
(paren
id|init
)paren
suffix:semicolon
DECL|variable|fini
id|module_exit
c_func
(paren
id|fini
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
