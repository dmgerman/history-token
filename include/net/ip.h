multiline_comment|/*&n; * INET&t;&t;An implementation of the TCP/IP protocol suite for the LINUX&n; *&t;&t;operating system.  INET is implemented using the  BSD Socket&n; *&t;&t;interface as the means of communication with the user level.&n; *&n; *&t;&t;Definitions for the IP module.&n; *&n; * Version:&t;@(#)ip.h&t;1.0.2&t;05/07/93&n; *&n; * Authors:&t;Ross Biro, &lt;bir7@leland.Stanford.Edu&gt;&n; *&t;&t;Fred N. van Kempen, &lt;waltje@uWalt.NL.Mugnet.ORG&gt;&n; *&t;&t;Alan Cox, &lt;gw4pts@gw4pts.ampr.org&gt;&n; *&n; * Changes:&n; *&t;&t;Mike McLagan    :       Routing by source&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _IP_H
DECL|macro|_IP_H
mdefine_line|#define _IP_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/ip.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/inetdevice.h&gt;
macro_line|#include &lt;linux/in_route.h&gt;
macro_line|#include &lt;net/route.h&gt;
macro_line|#include &lt;net/arp.h&gt;
macro_line|#ifndef _SNMP_H
macro_line|#include &lt;net/snmp.h&gt;
macro_line|#endif
macro_line|#include &lt;net/sock.h&gt;&t;/* struct sock */
DECL|struct|inet_skb_parm
r_struct
id|inet_skb_parm
(brace
DECL|member|opt
r_struct
id|ip_options
id|opt
suffix:semicolon
multiline_comment|/* Compiled IP options&t;&t;*/
DECL|member|flags
r_int
r_char
id|flags
suffix:semicolon
DECL|macro|IPSKB_MASQUERADED
mdefine_line|#define IPSKB_MASQUERADED&t;1
DECL|macro|IPSKB_TRANSLATED
mdefine_line|#define IPSKB_TRANSLATED&t;2
DECL|macro|IPSKB_FORWARDED
mdefine_line|#define IPSKB_FORWARDED&t;&t;4
DECL|macro|IPSKB_XFRM_TUNNEL_SIZE
mdefine_line|#define IPSKB_XFRM_TUNNEL_SIZE&t;8
)brace
suffix:semicolon
DECL|struct|ipcm_cookie
r_struct
id|ipcm_cookie
(brace
DECL|member|addr
id|u32
id|addr
suffix:semicolon
DECL|member|oif
r_int
id|oif
suffix:semicolon
DECL|member|opt
r_struct
id|ip_options
op_star
id|opt
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|IPCB
mdefine_line|#define IPCB(skb) ((struct inet_skb_parm*)((skb)-&gt;cb))
DECL|struct|ip_ra_chain
r_struct
id|ip_ra_chain
(brace
DECL|member|next
r_struct
id|ip_ra_chain
op_star
id|next
suffix:semicolon
DECL|member|sk
r_struct
id|sock
op_star
id|sk
suffix:semicolon
DECL|member|destructor
r_void
(paren
op_star
id|destructor
)paren
(paren
r_struct
id|sock
op_star
)paren
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|ip_ra_chain
op_star
id|ip_ra_chain
suffix:semicolon
r_extern
id|rwlock_t
id|ip_ra_lock
suffix:semicolon
multiline_comment|/* IP flags. */
DECL|macro|IP_CE
mdefine_line|#define IP_CE&t;&t;0x8000&t;&t;/* Flag: &quot;Congestion&quot;&t;&t;*/
DECL|macro|IP_DF
mdefine_line|#define IP_DF&t;&t;0x4000&t;&t;/* Flag: &quot;Don&squot;t Fragment&quot;&t;*/
DECL|macro|IP_MF
mdefine_line|#define IP_MF&t;&t;0x2000&t;&t;/* Flag: &quot;More Fragments&quot;&t;*/
DECL|macro|IP_OFFSET
mdefine_line|#define IP_OFFSET&t;0x1FFF&t;&t;/* &quot;Fragment Offset&quot; part&t;*/
DECL|macro|IP_FRAG_TIME
mdefine_line|#define IP_FRAG_TIME&t;(30 * HZ)&t;&t;/* fragment lifetime&t;*/
r_extern
r_void
id|ip_mc_dropsocket
c_func
(paren
r_struct
id|sock
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ip_mc_dropdevice
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_int
id|ip_mc_procinfo
c_func
(paren
r_char
op_star
comma
r_char
op_star
op_star
comma
id|off_t
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|ip_mcf_procinfo
c_func
(paren
r_char
op_star
comma
r_char
op_star
op_star
comma
id|off_t
comma
r_int
)paren
suffix:semicolon
multiline_comment|/*&n; *&t;Functions provided by ip.c&n; */
r_extern
r_int
id|ip_build_and_send_pkt
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|sock
op_star
id|sk
comma
id|u32
id|saddr
comma
id|u32
id|daddr
comma
r_struct
id|ip_options
op_star
id|opt
)paren
suffix:semicolon
r_extern
r_int
id|ip_rcv
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
suffix:semicolon
r_extern
r_int
id|ip_local_deliver
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
id|ip_mr_input
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
id|ip_output
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
id|ip_mc_output
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
id|ip_fragment
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_int
(paren
op_star
id|out
)paren
(paren
r_struct
id|sk_buff
op_star
)paren
)paren
suffix:semicolon
r_extern
r_int
id|ip_do_nat
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
r_extern
r_void
id|ip_send_check
c_func
(paren
r_struct
id|iphdr
op_star
id|ip
)paren
suffix:semicolon
r_extern
r_int
id|ip_queue_xmit
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_int
id|ipfragok
)paren
suffix:semicolon
r_extern
r_void
id|ip_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|ip_append_data
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_int
id|getfrag
c_func
(paren
r_void
op_star
id|from
comma
r_char
op_star
id|to
comma
r_int
id|offset
comma
r_int
id|len
comma
r_int
id|odd
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
comma
r_void
op_star
id|from
comma
r_int
id|len
comma
r_int
id|protolen
comma
r_struct
id|ipcm_cookie
op_star
id|ipc
comma
r_struct
id|rtable
op_star
id|rt
comma
r_int
r_int
id|flags
)paren
suffix:semicolon
r_extern
r_int
id|ip_generic_getfrag
c_func
(paren
r_void
op_star
id|from
comma
r_char
op_star
id|to
comma
r_int
id|offset
comma
r_int
id|len
comma
r_int
id|odd
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
r_extern
id|ssize_t
id|ip_append_page
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_struct
id|page
op_star
id|page
comma
r_int
id|offset
comma
r_int
id|size
comma
r_int
id|flags
)paren
suffix:semicolon
r_extern
r_int
id|ip_push_pending_frames
c_func
(paren
r_struct
id|sock
op_star
id|sk
)paren
suffix:semicolon
r_extern
r_void
id|ip_flush_pending_frames
c_func
(paren
r_struct
id|sock
op_star
id|sk
)paren
suffix:semicolon
multiline_comment|/*&n; *&t;Map a multicast IP onto multicast MAC for type Token Ring.&n; *      This conforms to RFC1469 Option 2 Multicasting i.e.&n; *      using a functional address to transmit / receive &n; *      multicast packets.&n; */
DECL|function|ip_tr_mc_map
r_static
r_inline
r_void
id|ip_tr_mc_map
c_func
(paren
id|u32
id|addr
comma
r_char
op_star
id|buf
)paren
(brace
id|buf
(braket
l_int|0
)braket
op_assign
l_int|0xC0
suffix:semicolon
id|buf
(braket
l_int|1
)braket
op_assign
l_int|0x00
suffix:semicolon
id|buf
(braket
l_int|2
)braket
op_assign
l_int|0x00
suffix:semicolon
id|buf
(braket
l_int|3
)braket
op_assign
l_int|0x04
suffix:semicolon
id|buf
(braket
l_int|4
)braket
op_assign
l_int|0x00
suffix:semicolon
id|buf
(braket
l_int|5
)braket
op_assign
l_int|0x00
suffix:semicolon
)brace
DECL|struct|ip_reply_arg
r_struct
id|ip_reply_arg
(brace
DECL|member|iov
r_struct
id|iovec
id|iov
(braket
l_int|1
)braket
suffix:semicolon
DECL|member|csum
id|u32
id|csum
suffix:semicolon
DECL|member|csumoffset
r_int
id|csumoffset
suffix:semicolon
multiline_comment|/* u16 offset of csum in iov[0].iov_base */
multiline_comment|/* -1 if not needed */
)brace
suffix:semicolon
r_void
id|ip_send_reply
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|ip_reply_arg
op_star
id|arg
comma
r_int
r_int
id|len
)paren
suffix:semicolon
r_extern
id|__inline__
r_int
id|ip_finish_output
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
DECL|struct|ipv4_config
r_struct
id|ipv4_config
(brace
DECL|member|log_martians
r_int
id|log_martians
suffix:semicolon
DECL|member|autoconfig
r_int
id|autoconfig
suffix:semicolon
DECL|member|no_pmtu_disc
r_int
id|no_pmtu_disc
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|ipv4_config
id|ipv4_config
suffix:semicolon
id|DECLARE_SNMP_STAT
c_func
(paren
r_struct
id|ip_mib
comma
id|ip_statistics
)paren
suffix:semicolon
DECL|macro|IP_INC_STATS
mdefine_line|#define IP_INC_STATS(field)&t;&t;SNMP_INC_STATS(ip_statistics, field)
DECL|macro|IP_INC_STATS_BH
mdefine_line|#define IP_INC_STATS_BH(field)&t;&t;SNMP_INC_STATS_BH(ip_statistics, field)
DECL|macro|IP_INC_STATS_USER
mdefine_line|#define IP_INC_STATS_USER(field) &t;SNMP_INC_STATS_USER(ip_statistics, field)
id|DECLARE_SNMP_STAT
c_func
(paren
r_struct
id|linux_mib
comma
id|net_statistics
)paren
suffix:semicolon
DECL|macro|NET_INC_STATS
mdefine_line|#define NET_INC_STATS(field)&t;&t;SNMP_INC_STATS(net_statistics, field)
DECL|macro|NET_INC_STATS_BH
mdefine_line|#define NET_INC_STATS_BH(field)&t;&t;SNMP_INC_STATS_BH(net_statistics, field)
DECL|macro|NET_INC_STATS_USER
mdefine_line|#define NET_INC_STATS_USER(field) &t;SNMP_INC_STATS_USER(net_statistics, field)
DECL|macro|NET_ADD_STATS_BH
mdefine_line|#define NET_ADD_STATS_BH(field, adnd)&t;SNMP_ADD_STATS_BH(net_statistics, field, adnd)
DECL|macro|NET_ADD_STATS_USER
mdefine_line|#define NET_ADD_STATS_USER(field, adnd)&t;SNMP_ADD_STATS_USER(net_statistics, field, adnd)
r_extern
r_int
id|sysctl_local_port_range
(braket
l_int|2
)braket
suffix:semicolon
r_extern
r_int
id|sysctl_ip_default_ttl
suffix:semicolon
macro_line|#ifdef CONFIG_INET
multiline_comment|/* The function in 2.2 was invalid, producing wrong result for&n; * check=0xFEFF. It was noticed by Arthur Skawina _year_ ago. --ANK(000625) */
r_static
r_inline
DECL|function|ip_decrease_ttl
r_int
id|ip_decrease_ttl
c_func
(paren
r_struct
id|iphdr
op_star
id|iph
)paren
(brace
id|u32
id|check
op_assign
id|iph-&gt;check
suffix:semicolon
id|check
op_add_assign
id|htons
c_func
(paren
l_int|0x0100
)paren
suffix:semicolon
id|iph-&gt;check
op_assign
id|check
op_plus
(paren
id|check
op_ge
l_int|0xFFFF
)paren
suffix:semicolon
r_return
op_decrement
id|iph-&gt;ttl
suffix:semicolon
)brace
r_static
r_inline
DECL|function|ip_dont_fragment
r_int
id|ip_dont_fragment
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_struct
id|dst_entry
op_star
id|dst
)paren
(brace
r_return
(paren
id|inet_sk
c_func
(paren
id|sk
)paren
op_member_access_from_pointer
id|pmtudisc
op_eq
id|IP_PMTUDISC_DO
op_logical_or
(paren
id|inet_sk
c_func
(paren
id|sk
)paren
op_member_access_from_pointer
id|pmtudisc
op_eq
id|IP_PMTUDISC_WANT
op_logical_and
op_logical_neg
(paren
id|dst_metric
c_func
(paren
id|dst
comma
id|RTAX_LOCK
)paren
op_amp
(paren
l_int|1
op_lshift
id|RTAX_MTU
)paren
)paren
)paren
)paren
suffix:semicolon
)brace
r_extern
r_void
id|__ip_select_ident
c_func
(paren
r_struct
id|iphdr
op_star
id|iph
comma
r_struct
id|dst_entry
op_star
id|dst
comma
r_int
id|more
)paren
suffix:semicolon
DECL|function|ip_select_ident
r_static
r_inline
r_void
id|ip_select_ident
c_func
(paren
r_struct
id|iphdr
op_star
id|iph
comma
r_struct
id|dst_entry
op_star
id|dst
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
id|iph-&gt;frag_off
op_amp
id|htons
c_func
(paren
id|IP_DF
)paren
)paren
(brace
multiline_comment|/* This is only to work around buggy Windows95/2000&n;&t;&t; * VJ compression implementations.  If the ID field&n;&t;&t; * does not change, they drop every other packet in&n;&t;&t; * a TCP stream using header compression.&n;&t;&t; */
id|iph-&gt;id
op_assign
(paren
id|sk
op_logical_and
id|inet_sk
c_func
(paren
id|sk
)paren
op_member_access_from_pointer
id|daddr
)paren
ques
c_cond
id|htons
c_func
(paren
id|inet_sk
c_func
(paren
id|sk
)paren
op_member_access_from_pointer
id|id
op_increment
)paren
suffix:colon
l_int|0
suffix:semicolon
)brace
r_else
id|__ip_select_ident
c_func
(paren
id|iph
comma
id|dst
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|ip_select_ident_more
r_static
r_inline
r_void
id|ip_select_ident_more
c_func
(paren
r_struct
id|iphdr
op_star
id|iph
comma
r_struct
id|dst_entry
op_star
id|dst
comma
r_struct
id|sock
op_star
id|sk
comma
r_int
id|more
)paren
(brace
r_if
c_cond
(paren
id|iph-&gt;frag_off
op_amp
id|htons
c_func
(paren
id|IP_DF
)paren
)paren
(brace
r_if
c_cond
(paren
id|sk
op_logical_and
id|inet_sk
c_func
(paren
id|sk
)paren
op_member_access_from_pointer
id|daddr
)paren
(brace
id|iph-&gt;id
op_assign
id|htons
c_func
(paren
id|inet_sk
c_func
(paren
id|sk
)paren
op_member_access_from_pointer
id|id
)paren
suffix:semicolon
id|inet_sk
c_func
(paren
id|sk
)paren
op_member_access_from_pointer
id|id
op_add_assign
l_int|1
op_plus
id|more
suffix:semicolon
)brace
r_else
id|iph-&gt;id
op_assign
l_int|0
suffix:semicolon
)brace
r_else
id|__ip_select_ident
c_func
(paren
id|iph
comma
id|dst
comma
id|more
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Map a multicast IP onto multicast MAC for type ethernet.&n; */
DECL|function|ip_eth_mc_map
r_static
r_inline
r_void
id|ip_eth_mc_map
c_func
(paren
id|u32
id|addr
comma
r_char
op_star
id|buf
)paren
(brace
id|addr
op_assign
id|ntohl
c_func
(paren
id|addr
)paren
suffix:semicolon
id|buf
(braket
l_int|0
)braket
op_assign
l_int|0x01
suffix:semicolon
id|buf
(braket
l_int|1
)braket
op_assign
l_int|0x00
suffix:semicolon
id|buf
(braket
l_int|2
)braket
op_assign
l_int|0x5e
suffix:semicolon
id|buf
(braket
l_int|5
)braket
op_assign
id|addr
op_amp
l_int|0xFF
suffix:semicolon
id|addr
op_rshift_assign
l_int|8
suffix:semicolon
id|buf
(braket
l_int|4
)braket
op_assign
id|addr
op_amp
l_int|0xFF
suffix:semicolon
id|addr
op_rshift_assign
l_int|8
suffix:semicolon
id|buf
(braket
l_int|3
)braket
op_assign
id|addr
op_amp
l_int|0x7F
suffix:semicolon
)brace
macro_line|#endif
r_extern
r_int
id|ip_call_ra_chain
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
multiline_comment|/*&n; *&t;Functions provided by ip_fragment.o&n; */
r_struct
id|sk_buff
op_star
id|ip_defrag
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
id|ip_frag_nqueues
suffix:semicolon
r_extern
id|atomic_t
id|ip_frag_mem
suffix:semicolon
multiline_comment|/*&n; *&t;Functions provided by ip_forward.c&n; */
r_extern
r_int
id|ip_forward
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
id|ip_net_unreachable
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
multiline_comment|/*&n; *&t;Functions provided by ip_options.c&n; */
r_extern
r_void
id|ip_options_build
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|ip_options
op_star
id|opt
comma
id|u32
id|daddr
comma
r_struct
id|rtable
op_star
id|rt
comma
r_int
id|is_frag
)paren
suffix:semicolon
r_extern
r_int
id|ip_options_echo
c_func
(paren
r_struct
id|ip_options
op_star
id|dopt
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
r_extern
r_void
id|ip_options_fragment
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
id|ip_options_compile
c_func
(paren
r_struct
id|ip_options
op_star
id|opt
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
r_extern
r_int
id|ip_options_get
c_func
(paren
r_struct
id|ip_options
op_star
op_star
id|optp
comma
r_int
r_char
op_star
id|data
comma
r_int
id|optlen
comma
r_int
id|user
)paren
suffix:semicolon
r_extern
r_void
id|ip_options_undo
c_func
(paren
r_struct
id|ip_options
op_star
id|opt
)paren
suffix:semicolon
r_extern
r_void
id|ip_forward_options
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
id|ip_options_rcv_srr
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
multiline_comment|/*&n; *&t;Functions provided by ip_sockglue.c&n; */
r_extern
r_void
id|ip_cmsg_recv
c_func
(paren
r_struct
id|msghdr
op_star
id|msg
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
r_extern
r_int
id|ip_cmsg_send
c_func
(paren
r_struct
id|msghdr
op_star
id|msg
comma
r_struct
id|ipcm_cookie
op_star
id|ipc
)paren
suffix:semicolon
r_extern
r_int
id|ip_setsockopt
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_int
id|level
comma
r_int
id|optname
comma
r_char
op_star
id|optval
comma
r_int
id|optlen
)paren
suffix:semicolon
r_extern
r_int
id|ip_getsockopt
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_int
id|level
comma
r_int
id|optname
comma
r_char
op_star
id|optval
comma
r_int
op_star
id|optlen
)paren
suffix:semicolon
r_extern
r_int
id|ip_ra_control
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_int
r_char
id|on
comma
r_void
(paren
op_star
id|destructor
)paren
(paren
r_struct
id|sock
op_star
)paren
)paren
suffix:semicolon
r_extern
r_int
id|ip_recv_error
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_struct
id|msghdr
op_star
id|msg
comma
r_int
id|len
)paren
suffix:semicolon
r_extern
r_void
id|ip_icmp_error
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_struct
id|sk_buff
op_star
id|skb
comma
r_int
id|err
comma
id|u16
id|port
comma
id|u32
id|info
comma
id|u8
op_star
id|payload
)paren
suffix:semicolon
r_extern
r_void
id|ip_local_error
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_int
id|err
comma
id|u32
id|daddr
comma
id|u16
id|dport
comma
id|u32
id|info
)paren
suffix:semicolon
r_extern
r_int
id|ip_seq_release
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
)paren
suffix:semicolon
r_extern
r_int
id|ipv4_proc_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif&t;/* _IP_H */
eof
