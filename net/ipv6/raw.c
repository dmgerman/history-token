multiline_comment|/*&n; *&t;RAW sockets for IPv6&n; *&t;Linux INET6 implementation &n; *&n; *&t;Authors:&n; *&t;Pedro Roque&t;&t;&lt;roque@di.fc.ul.pt&gt;&t;&n; *&n; *&t;Adapted from linux/net/ipv4/raw.c&n; *&n; *&t;$Id: raw.c,v 1.49 2001/08/13 18:56:13 davem Exp $&n; *&n; *&t;Fixes:&n; *&t;Hideaki YOSHIFUJI&t;:&t;sin6_scope_id support&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *      modify it under the terms of the GNU General Public License&n; *      as published by the Free Software Foundation; either version&n; *      2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/sockios.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/net.h&gt;
macro_line|#include &lt;linux/in6.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/if_arp.h&gt;
macro_line|#include &lt;linux/icmpv6.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/ioctls.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;net/snmp.h&gt;
macro_line|#include &lt;net/ipv6.h&gt;
macro_line|#include &lt;net/ndisc.h&gt;
macro_line|#include &lt;net/protocol.h&gt;
macro_line|#include &lt;net/ip6_route.h&gt;
macro_line|#include &lt;net/addrconf.h&gt;
macro_line|#include &lt;net/transp_v6.h&gt;
macro_line|#include &lt;net/udp.h&gt;
macro_line|#include &lt;net/inet_common.h&gt;
macro_line|#include &lt;net/rawv6.h&gt;
DECL|variable|raw_v6_htable
r_struct
id|sock
op_star
id|raw_v6_htable
(braket
id|RAWV6_HTABLE_SIZE
)braket
suffix:semicolon
DECL|variable|raw_v6_lock
id|rwlock_t
id|raw_v6_lock
op_assign
id|RW_LOCK_UNLOCKED
suffix:semicolon
DECL|function|raw_v6_hash
r_static
r_void
id|raw_v6_hash
c_func
(paren
r_struct
id|sock
op_star
id|sk
)paren
(brace
r_struct
id|sock
op_star
op_star
id|skp
op_assign
op_amp
id|raw_v6_htable
(braket
id|sk-&gt;num
op_amp
(paren
id|RAWV6_HTABLE_SIZE
op_minus
l_int|1
)paren
)braket
suffix:semicolon
id|write_lock_bh
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
id|sk-&gt;next
op_assign
op_star
id|skp
)paren
op_ne
l_int|NULL
)paren
(paren
op_star
id|skp
)paren
op_member_access_from_pointer
id|pprev
op_assign
op_amp
id|sk-&gt;next
suffix:semicolon
op_star
id|skp
op_assign
id|sk
suffix:semicolon
id|sk-&gt;pprev
op_assign
id|skp
suffix:semicolon
id|sock_prot_inc_use
c_func
(paren
id|sk-&gt;prot
)paren
suffix:semicolon
id|sock_hold
c_func
(paren
id|sk
)paren
suffix:semicolon
id|write_unlock_bh
c_func
(paren
op_amp
id|raw_v6_lock
)paren
suffix:semicolon
)brace
DECL|function|raw_v6_unhash
r_static
r_void
id|raw_v6_unhash
c_func
(paren
r_struct
id|sock
op_star
id|sk
)paren
(brace
id|write_lock_bh
c_func
(paren
op_amp
id|raw_v6_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sk-&gt;pprev
)paren
(brace
r_if
c_cond
(paren
id|sk-&gt;next
)paren
id|sk-&gt;next-&gt;pprev
op_assign
id|sk-&gt;pprev
suffix:semicolon
op_star
id|sk-&gt;pprev
op_assign
id|sk-&gt;next
suffix:semicolon
id|sk-&gt;pprev
op_assign
l_int|NULL
suffix:semicolon
id|sock_prot_dec_use
c_func
(paren
id|sk-&gt;prot
)paren
suffix:semicolon
id|__sock_put
c_func
(paren
id|sk
)paren
suffix:semicolon
)brace
id|write_unlock_bh
c_func
(paren
op_amp
id|raw_v6_lock
)paren
suffix:semicolon
)brace
multiline_comment|/* Grumble... icmp and ip_input want to get at this... */
DECL|function|__raw_v6_lookup
r_struct
id|sock
op_star
id|__raw_v6_lookup
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_int
r_int
id|num
comma
r_struct
id|in6_addr
op_star
id|loc_addr
comma
r_struct
id|in6_addr
op_star
id|rmt_addr
)paren
(brace
r_struct
id|sock
op_star
id|s
op_assign
id|sk
suffix:semicolon
r_int
id|addr_type
op_assign
id|ipv6_addr_type
c_func
(paren
id|loc_addr
)paren
suffix:semicolon
r_for
c_loop
(paren
id|s
op_assign
id|sk
suffix:semicolon
id|s
suffix:semicolon
id|s
op_assign
id|s-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|s-&gt;num
op_eq
id|num
)paren
(brace
r_struct
id|ipv6_pinfo
op_star
id|np
op_assign
op_amp
id|s-&gt;net_pinfo.af_inet6
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ipv6_addr_any
c_func
(paren
op_amp
id|np-&gt;daddr
)paren
op_logical_and
id|ipv6_addr_cmp
c_func
(paren
op_amp
id|np-&gt;daddr
comma
id|rmt_addr
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ipv6_addr_any
c_func
(paren
op_amp
id|np-&gt;rcv_saddr
)paren
)paren
(brace
r_if
c_cond
(paren
id|ipv6_addr_cmp
c_func
(paren
op_amp
id|np-&gt;rcv_saddr
comma
id|loc_addr
)paren
op_eq
l_int|0
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
(paren
id|addr_type
op_amp
id|IPV6_ADDR_MULTICAST
)paren
op_logical_and
id|inet6_mc_check
c_func
(paren
id|s
comma
id|loc_addr
)paren
)paren
r_break
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
)brace
r_return
id|s
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;0 - deliver&n; *&t;1 - block&n; */
DECL|function|icmpv6_filter
r_static
id|__inline__
r_int
id|icmpv6_filter
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
)paren
(brace
r_struct
id|icmp6hdr
op_star
id|icmph
suffix:semicolon
r_struct
id|raw6_opt
op_star
id|opt
suffix:semicolon
id|opt
op_assign
op_amp
id|sk-&gt;tp_pinfo.tp_raw
suffix:semicolon
r_if
c_cond
(paren
id|pskb_may_pull
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
(brace
id|__u32
op_star
id|data
op_assign
op_amp
id|opt-&gt;filter.data
(braket
l_int|0
)braket
suffix:semicolon
r_int
id|bit_nr
suffix:semicolon
id|icmph
op_assign
(paren
r_struct
id|icmp6hdr
op_star
)paren
id|skb-&gt;data
suffix:semicolon
id|bit_nr
op_assign
id|icmph-&gt;icmp6_type
suffix:semicolon
r_return
(paren
id|data
(braket
id|bit_nr
op_rshift
l_int|5
)braket
op_amp
(paren
l_int|1
op_lshift
(paren
id|bit_nr
op_amp
l_int|31
)paren
)paren
)paren
op_ne
l_int|0
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;demultiplex raw sockets.&n; *&t;(should consider queueing the skb in the sock receive_queue&n; *&t;without calling rawv6.c)&n; */
DECL|function|ipv6_raw_deliver
r_struct
id|sock
op_star
id|ipv6_raw_deliver
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_int
id|nexthdr
)paren
(brace
r_struct
id|in6_addr
op_star
id|saddr
suffix:semicolon
r_struct
id|in6_addr
op_star
id|daddr
suffix:semicolon
r_struct
id|sock
op_star
id|sk
comma
op_star
id|sk2
suffix:semicolon
id|__u8
id|hash
suffix:semicolon
id|saddr
op_assign
op_amp
id|skb-&gt;nh.ipv6h-&gt;saddr
suffix:semicolon
id|daddr
op_assign
id|saddr
op_plus
l_int|1
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
id|read_lock
c_func
(paren
op_amp
id|raw_v6_lock
)paren
suffix:semicolon
id|sk
op_assign
id|raw_v6_htable
(braket
id|hash
)braket
suffix:semicolon
multiline_comment|/*&n;&t; *&t;The first socket found will be delivered after&n;&t; *&t;delivery to transport protocols.&n;&t; */
r_if
c_cond
(paren
id|sk
op_eq
l_int|NULL
)paren
r_goto
id|out
suffix:semicolon
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
suffix:semicolon
r_if
c_cond
(paren
id|sk
)paren
(brace
id|sk2
op_assign
id|sk
suffix:semicolon
r_while
c_loop
(paren
(paren
id|sk2
op_assign
id|__raw_v6_lookup
c_func
(paren
id|sk2-&gt;next
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
r_struct
id|sk_buff
op_star
id|buff
suffix:semicolon
r_if
c_cond
(paren
id|nexthdr
op_eq
id|IPPROTO_ICMPV6
op_logical_and
id|icmpv6_filter
c_func
(paren
id|sk2
comma
id|skb
)paren
)paren
r_continue
suffix:semicolon
id|buff
op_assign
id|skb_clone
c_func
(paren
id|skb
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|buff
)paren
id|rawv6_rcv
c_func
(paren
id|sk2
comma
id|buff
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|sk
op_logical_and
id|nexthdr
op_eq
id|IPPROTO_ICMPV6
op_logical_and
id|icmpv6_filter
c_func
(paren
id|sk
comma
id|skb
)paren
)paren
id|sk
op_assign
l_int|NULL
suffix:semicolon
id|out
suffix:colon
r_if
c_cond
(paren
id|sk
)paren
id|sock_hold
c_func
(paren
id|sk
)paren
suffix:semicolon
id|read_unlock
c_func
(paren
op_amp
id|raw_v6_lock
)paren
suffix:semicolon
r_return
id|sk
suffix:semicolon
)brace
multiline_comment|/* This cleans up af_inet6 a bit. -DaveM */
DECL|function|rawv6_bind
r_static
r_int
id|rawv6_bind
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_struct
id|sockaddr
op_star
id|uaddr
comma
r_int
id|addr_len
)paren
(brace
r_struct
id|sockaddr_in6
op_star
id|addr
op_assign
(paren
r_struct
id|sockaddr_in6
op_star
)paren
id|uaddr
suffix:semicolon
id|__u32
id|v4addr
op_assign
l_int|0
suffix:semicolon
r_int
id|addr_type
suffix:semicolon
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
id|addr_len
OL
id|SIN6_LEN_RFC2133
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|addr_type
op_assign
id|ipv6_addr_type
c_func
(paren
op_amp
id|addr-&gt;sin6_addr
)paren
suffix:semicolon
multiline_comment|/* Raw sockets are IPv6 only */
r_if
c_cond
(paren
id|addr_type
op_eq
id|IPV6_ADDR_MAPPED
)paren
r_return
op_minus
id|EADDRNOTAVAIL
suffix:semicolon
id|lock_sock
c_func
(paren
id|sk
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|sk-&gt;state
op_ne
id|TCP_CLOSE
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|addr_type
op_amp
id|IPV6_ADDR_LINKLOCAL
)paren
(brace
r_if
c_cond
(paren
id|addr_len
op_ge
r_sizeof
(paren
r_struct
id|sockaddr_in6
)paren
op_logical_and
id|addr-&gt;sin6_scope_id
)paren
(brace
multiline_comment|/* Override any existing binding, if another one&n;&t;&t;&t; * is supplied by user.&n;&t;&t;&t; */
id|sk-&gt;bound_dev_if
op_assign
id|addr-&gt;sin6_scope_id
suffix:semicolon
)brace
multiline_comment|/* Binding to link-local address requires an interface */
r_if
c_cond
(paren
id|sk-&gt;bound_dev_if
op_eq
l_int|0
)paren
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/* Check if the address belongs to the host. */
r_if
c_cond
(paren
id|addr_type
op_ne
id|IPV6_ADDR_ANY
)paren
(brace
multiline_comment|/* ipv4 addr of the socket is invalid.  Only the&n;&t;&t; * unpecified and mapped address have a v4 equivalent.&n;&t;&t; */
id|v4addr
op_assign
id|LOOPBACK4_IPV6
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|addr_type
op_amp
id|IPV6_ADDR_MULTICAST
)paren
)paren
(brace
id|err
op_assign
op_minus
id|EADDRNOTAVAIL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ipv6_chk_addr
c_func
(paren
op_amp
id|addr-&gt;sin6_addr
comma
l_int|NULL
)paren
)paren
r_goto
id|out
suffix:semicolon
)brace
)brace
id|sk-&gt;rcv_saddr
op_assign
id|v4addr
suffix:semicolon
id|sk-&gt;saddr
op_assign
id|v4addr
suffix:semicolon
id|ipv6_addr_copy
c_func
(paren
op_amp
id|sk-&gt;net_pinfo.af_inet6.rcv_saddr
comma
op_amp
id|addr-&gt;sin6_addr
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|addr_type
op_amp
id|IPV6_ADDR_MULTICAST
)paren
)paren
id|ipv6_addr_copy
c_func
(paren
op_amp
id|sk-&gt;net_pinfo.af_inet6.saddr
comma
op_amp
id|addr-&gt;sin6_addr
)paren
suffix:semicolon
id|err
op_assign
l_int|0
suffix:semicolon
id|out
suffix:colon
id|release_sock
c_func
(paren
id|sk
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|rawv6_err
r_void
id|rawv6_err
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
id|inet6_skb_parm
op_star
id|opt
comma
r_int
id|type
comma
r_int
id|code
comma
r_int
id|offset
comma
id|u32
id|info
)paren
(brace
r_int
id|err
suffix:semicolon
r_int
id|harderr
suffix:semicolon
multiline_comment|/* Report error on raw socket, if:&n;&t;   1. User requested recverr.&n;&t;   2. Socket is connected (otherwise the error indication&n;&t;      is useless without recverr and error is hard.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|sk-&gt;net_pinfo.af_inet6.recverr
op_logical_and
id|sk-&gt;state
op_ne
id|TCP_ESTABLISHED
)paren
r_return
suffix:semicolon
id|harderr
op_assign
id|icmpv6_err_convert
c_func
(paren
id|type
comma
id|code
comma
op_amp
id|err
)paren
suffix:semicolon
r_if
c_cond
(paren
id|type
op_eq
id|ICMPV6_PKT_TOOBIG
)paren
id|harderr
op_assign
(paren
id|sk-&gt;net_pinfo.af_inet6.pmtudisc
op_eq
id|IPV6_PMTUDISC_DO
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sk-&gt;net_pinfo.af_inet6.recverr
)paren
(brace
id|u8
op_star
id|payload
op_assign
id|skb-&gt;data
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sk-&gt;protinfo.af_inet.hdrincl
)paren
id|payload
op_add_assign
id|offset
suffix:semicolon
id|ipv6_icmp_error
c_func
(paren
id|sk
comma
id|skb
comma
id|err
comma
l_int|0
comma
id|ntohl
c_func
(paren
id|info
)paren
comma
id|payload
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sk-&gt;net_pinfo.af_inet6.recverr
op_logical_or
id|harderr
)paren
(brace
id|sk-&gt;err
op_assign
id|err
suffix:semicolon
id|sk
op_member_access_from_pointer
id|error_report
c_func
(paren
id|sk
)paren
suffix:semicolon
)brace
)brace
DECL|function|rawv6_rcv_skb
r_static
r_inline
r_int
id|rawv6_rcv_skb
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
)paren
(brace
multiline_comment|/* Charge it to the socket. */
r_if
c_cond
(paren
id|sock_queue_rcv_skb
c_func
(paren
id|sk
comma
id|skb
)paren
OL
l_int|0
)paren
(brace
id|IP6_INC_STATS_BH
c_func
(paren
id|Ip6InDiscards
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
id|IP6_INC_STATS_BH
c_func
(paren
id|Ip6InDelivers
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;This is next to useless... &n; *&t;if we demultiplex in network layer we don&squot;t need the extra call&n; *&t;just to queue the skb... &n; *&t;maybe we could have the network decide uppon a hint if it &n; *&t;should call raw_rcv for demultiplexing&n; */
DECL|function|rawv6_rcv
r_int
id|rawv6_rcv
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
)paren
(brace
r_if
c_cond
(paren
id|sk-&gt;protinfo.af_inet.hdrincl
)paren
(brace
id|__skb_push
c_func
(paren
id|skb
comma
id|skb-&gt;nh.raw
op_minus
id|skb-&gt;data
)paren
suffix:semicolon
id|skb-&gt;h.raw
op_assign
id|skb-&gt;nh.raw
suffix:semicolon
)brace
id|rawv6_rcv_skb
c_func
(paren
id|sk
comma
id|skb
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;This should be easy, if there is something there&n; *&t;we return it, otherwise we block.&n; */
DECL|function|rawv6_recvmsg
r_int
id|rawv6_recvmsg
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
comma
r_int
id|noblock
comma
r_int
id|flags
comma
r_int
op_star
id|addr_len
)paren
(brace
r_struct
id|sockaddr_in6
op_star
id|sin6
op_assign
(paren
r_struct
id|sockaddr_in6
op_star
)paren
id|msg-&gt;msg_name
suffix:semicolon
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
r_int
id|copied
comma
id|err
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
id|MSG_OOB
)paren
r_return
op_minus
id|EOPNOTSUPP
suffix:semicolon
r_if
c_cond
(paren
id|addr_len
)paren
op_star
id|addr_len
op_assign
r_sizeof
(paren
op_star
id|sin6
)paren
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
id|MSG_ERRQUEUE
)paren
r_return
id|ipv6_recv_error
c_func
(paren
id|sk
comma
id|msg
comma
id|len
)paren
suffix:semicolon
id|skb
op_assign
id|skb_recv_datagram
c_func
(paren
id|sk
comma
id|flags
comma
id|noblock
comma
op_amp
id|err
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|skb
)paren
r_goto
id|out
suffix:semicolon
id|copied
op_assign
id|skb-&gt;len
suffix:semicolon
r_if
c_cond
(paren
id|copied
OG
id|len
)paren
(brace
id|copied
op_assign
id|len
suffix:semicolon
id|msg-&gt;msg_flags
op_or_assign
id|MSG_TRUNC
suffix:semicolon
)brace
id|err
op_assign
id|skb_copy_datagram_iovec
c_func
(paren
id|skb
comma
l_int|0
comma
id|msg-&gt;msg_iov
comma
id|copied
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_goto
id|out_free
suffix:semicolon
multiline_comment|/* Copy the address. */
r_if
c_cond
(paren
id|sin6
)paren
(brace
id|sin6-&gt;sin6_family
op_assign
id|AF_INET6
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|sin6-&gt;sin6_addr
comma
op_amp
id|skb-&gt;nh.ipv6h-&gt;saddr
comma
r_sizeof
(paren
r_struct
id|in6_addr
)paren
)paren
suffix:semicolon
id|sin6-&gt;sin6_flowinfo
op_assign
l_int|0
suffix:semicolon
id|sin6-&gt;sin6_scope_id
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|ipv6_addr_type
c_func
(paren
op_amp
id|sin6-&gt;sin6_addr
)paren
op_amp
id|IPV6_ADDR_LINKLOCAL
)paren
(brace
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
id|sin6-&gt;sin6_scope_id
op_assign
id|opt-&gt;iif
suffix:semicolon
)brace
)brace
id|sock_recv_timestamp
c_func
(paren
id|msg
comma
id|sk
comma
id|skb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sk-&gt;net_pinfo.af_inet6.rxopt.all
)paren
id|datagram_recv_ctl
c_func
(paren
id|sk
comma
id|msg
comma
id|skb
)paren
suffix:semicolon
id|err
op_assign
id|copied
suffix:semicolon
id|out_free
suffix:colon
id|skb_free_datagram
c_func
(paren
id|sk
comma
id|skb
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Sending...&n; */
DECL|struct|rawv6_fakehdr
r_struct
id|rawv6_fakehdr
(brace
DECL|member|iov
r_struct
id|iovec
op_star
id|iov
suffix:semicolon
DECL|member|sk
r_struct
id|sock
op_star
id|sk
suffix:semicolon
DECL|member|len
id|__u32
id|len
suffix:semicolon
DECL|member|cksum
id|__u32
id|cksum
suffix:semicolon
DECL|member|proto
id|__u32
id|proto
suffix:semicolon
DECL|member|daddr
r_struct
id|in6_addr
op_star
id|daddr
suffix:semicolon
)brace
suffix:semicolon
DECL|function|rawv6_getfrag
r_static
r_int
id|rawv6_getfrag
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
id|iovec
op_star
id|iov
op_assign
(paren
r_struct
id|iovec
op_star
)paren
id|data
suffix:semicolon
r_return
id|memcpy_fromiovecend
c_func
(paren
id|buff
comma
id|iov
comma
id|offset
comma
id|len
)paren
suffix:semicolon
)brace
DECL|function|rawv6_frag_cksum
r_static
r_int
id|rawv6_frag_cksum
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
id|addr
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
id|rawv6_fakehdr
op_star
id|hdr
op_assign
(paren
r_struct
id|rawv6_fakehdr
op_star
)paren
id|data
suffix:semicolon
r_if
c_cond
(paren
id|csum_partial_copy_fromiovecend
c_func
(paren
id|buff
comma
id|hdr-&gt;iov
comma
id|offset
comma
id|len
comma
op_amp
id|hdr-&gt;cksum
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|offset
op_eq
l_int|0
)paren
(brace
r_struct
id|sock
op_star
id|sk
suffix:semicolon
r_struct
id|raw6_opt
op_star
id|opt
suffix:semicolon
r_struct
id|in6_addr
op_star
id|daddr
suffix:semicolon
id|sk
op_assign
id|hdr-&gt;sk
suffix:semicolon
id|opt
op_assign
op_amp
id|sk-&gt;tp_pinfo.tp_raw
suffix:semicolon
r_if
c_cond
(paren
id|hdr-&gt;daddr
)paren
id|daddr
op_assign
id|hdr-&gt;daddr
suffix:semicolon
r_else
id|daddr
op_assign
id|addr
op_plus
l_int|1
suffix:semicolon
id|hdr-&gt;cksum
op_assign
id|csum_ipv6_magic
c_func
(paren
id|addr
comma
id|daddr
comma
id|hdr-&gt;len
comma
id|hdr-&gt;proto
comma
id|hdr-&gt;cksum
)paren
suffix:semicolon
r_if
c_cond
(paren
id|opt-&gt;offset
OL
id|len
)paren
(brace
id|__u16
op_star
id|csum
suffix:semicolon
id|csum
op_assign
(paren
id|__u16
op_star
)paren
(paren
id|buff
op_plus
id|opt-&gt;offset
)paren
suffix:semicolon
op_star
id|csum
op_assign
id|hdr-&gt;cksum
suffix:semicolon
)brace
r_else
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
l_string|&quot;icmp: cksum offset too big&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|rawv6_sendmsg
r_static
r_int
id|rawv6_sendmsg
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
(brace
r_struct
id|ipv6_txoptions
id|opt_space
suffix:semicolon
r_struct
id|sockaddr_in6
op_star
id|sin6
op_assign
(paren
r_struct
id|sockaddr_in6
op_star
)paren
id|msg-&gt;msg_name
suffix:semicolon
r_struct
id|ipv6_pinfo
op_star
id|np
op_assign
op_amp
id|sk-&gt;net_pinfo.af_inet6
suffix:semicolon
r_struct
id|ipv6_txoptions
op_star
id|opt
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|ip6_flowlabel
op_star
id|flowlabel
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|flowi
id|fl
suffix:semicolon
r_int
id|addr_len
op_assign
id|msg-&gt;msg_namelen
suffix:semicolon
r_struct
id|in6_addr
op_star
id|daddr
suffix:semicolon
r_struct
id|raw6_opt
op_star
id|raw_opt
suffix:semicolon
r_int
id|hlimit
op_assign
op_minus
l_int|1
suffix:semicolon
id|u16
id|proto
suffix:semicolon
r_int
id|err
suffix:semicolon
multiline_comment|/* Rough check on arithmetic overflow,&n;&t;   better check is made in ip6_build_xmit&n;&t; */
r_if
c_cond
(paren
id|len
OL
l_int|0
)paren
r_return
op_minus
id|EMSGSIZE
suffix:semicolon
multiline_comment|/* Mirror BSD error message compatibility */
r_if
c_cond
(paren
id|msg-&gt;msg_flags
op_amp
id|MSG_OOB
)paren
r_return
op_minus
id|EOPNOTSUPP
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Get and verify the address. &n;&t; */
id|fl.fl6_flowlabel
op_assign
l_int|0
suffix:semicolon
id|fl.oif
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|sin6
)paren
(brace
r_if
c_cond
(paren
id|addr_len
OL
id|SIN6_LEN_RFC2133
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|sin6-&gt;sin6_family
op_logical_and
id|sin6-&gt;sin6_family
op_ne
id|AF_INET6
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/* port is the proto value [0..255] carried in nexthdr */
id|proto
op_assign
id|ntohs
c_func
(paren
id|sin6-&gt;sin6_port
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|proto
)paren
id|proto
op_assign
id|sk-&gt;num
suffix:semicolon
r_if
c_cond
(paren
id|proto
OG
l_int|255
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|daddr
op_assign
op_amp
id|sin6-&gt;sin6_addr
suffix:semicolon
r_if
c_cond
(paren
id|np-&gt;sndflow
)paren
(brace
id|fl.fl6_flowlabel
op_assign
id|sin6-&gt;sin6_flowinfo
op_amp
id|IPV6_FLOWINFO_MASK
suffix:semicolon
r_if
c_cond
(paren
id|fl.fl6_flowlabel
op_amp
id|IPV6_FLOWLABEL_MASK
)paren
(brace
id|flowlabel
op_assign
id|fl6_sock_lookup
c_func
(paren
id|sk
comma
id|fl.fl6_flowlabel
)paren
suffix:semicolon
r_if
c_cond
(paren
id|flowlabel
op_eq
l_int|NULL
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|daddr
op_assign
op_amp
id|flowlabel-&gt;dst
suffix:semicolon
)brace
)brace
multiline_comment|/* Otherwise it will be difficult to maintain sk-&gt;dst_cache. */
r_if
c_cond
(paren
id|sk-&gt;state
op_eq
id|TCP_ESTABLISHED
op_logical_and
op_logical_neg
id|ipv6_addr_cmp
c_func
(paren
id|daddr
comma
op_amp
id|sk-&gt;net_pinfo.af_inet6.daddr
)paren
)paren
id|daddr
op_assign
op_amp
id|sk-&gt;net_pinfo.af_inet6.daddr
suffix:semicolon
r_if
c_cond
(paren
id|addr_len
op_ge
r_sizeof
(paren
r_struct
id|sockaddr_in6
)paren
op_logical_and
id|sin6-&gt;sin6_scope_id
op_logical_and
id|ipv6_addr_type
c_func
(paren
id|daddr
)paren
op_amp
id|IPV6_ADDR_LINKLOCAL
)paren
id|fl.oif
op_assign
id|sin6-&gt;sin6_scope_id
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|sk-&gt;state
op_ne
id|TCP_ESTABLISHED
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|proto
op_assign
id|sk-&gt;num
suffix:semicolon
id|daddr
op_assign
op_amp
(paren
id|sk-&gt;net_pinfo.af_inet6.daddr
)paren
suffix:semicolon
id|fl.fl6_flowlabel
op_assign
id|np-&gt;flow_label
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ipv6_addr_any
c_func
(paren
id|daddr
)paren
)paren
(brace
multiline_comment|/* &n;&t;&t; * unspecfied destination address &n;&t;&t; * treated as error... is this correct ?&n;&t;&t; */
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|fl.oif
op_eq
l_int|0
)paren
id|fl.oif
op_assign
id|sk-&gt;bound_dev_if
suffix:semicolon
id|fl.fl6_src
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|msg-&gt;msg_controllen
)paren
(brace
id|opt
op_assign
op_amp
id|opt_space
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
r_struct
id|ipv6_txoptions
)paren
)paren
suffix:semicolon
id|err
op_assign
id|datagram_send_ctl
c_func
(paren
id|msg
comma
op_amp
id|fl
comma
id|opt
comma
op_amp
id|hlimit
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
id|fl6_sock_release
c_func
(paren
id|flowlabel
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|fl.fl6_flowlabel
op_amp
id|IPV6_FLOWLABEL_MASK
)paren
op_logical_and
op_logical_neg
id|flowlabel
)paren
(brace
id|flowlabel
op_assign
id|fl6_sock_lookup
c_func
(paren
id|sk
comma
id|fl.fl6_flowlabel
)paren
suffix:semicolon
r_if
c_cond
(paren
id|flowlabel
op_eq
l_int|NULL
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|opt-&gt;opt_nflen
op_or
id|opt-&gt;opt_flen
)paren
)paren
id|opt
op_assign
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|opt
op_eq
l_int|NULL
)paren
id|opt
op_assign
id|np-&gt;opt
suffix:semicolon
r_if
c_cond
(paren
id|flowlabel
)paren
id|opt
op_assign
id|fl6_merge_options
c_func
(paren
op_amp
id|opt_space
comma
id|flowlabel
comma
id|opt
)paren
suffix:semicolon
id|raw_opt
op_assign
op_amp
id|sk-&gt;tp_pinfo.tp_raw
suffix:semicolon
id|fl.proto
op_assign
id|proto
suffix:semicolon
id|fl.fl6_dst
op_assign
id|daddr
suffix:semicolon
r_if
c_cond
(paren
id|fl.fl6_src
op_eq
l_int|NULL
op_logical_and
op_logical_neg
id|ipv6_addr_any
c_func
(paren
op_amp
id|np-&gt;saddr
)paren
)paren
id|fl.fl6_src
op_assign
op_amp
id|np-&gt;saddr
suffix:semicolon
id|fl.uli_u.icmpt.type
op_assign
l_int|0
suffix:semicolon
id|fl.uli_u.icmpt.code
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|raw_opt-&gt;checksum
)paren
(brace
r_struct
id|rawv6_fakehdr
id|hdr
suffix:semicolon
id|hdr.iov
op_assign
id|msg-&gt;msg_iov
suffix:semicolon
id|hdr.sk
op_assign
id|sk
suffix:semicolon
id|hdr.len
op_assign
id|len
suffix:semicolon
id|hdr.cksum
op_assign
l_int|0
suffix:semicolon
id|hdr.proto
op_assign
id|proto
suffix:semicolon
r_if
c_cond
(paren
id|opt
op_logical_and
id|opt-&gt;srcrt
)paren
id|hdr.daddr
op_assign
id|daddr
suffix:semicolon
r_else
id|hdr.daddr
op_assign
l_int|NULL
suffix:semicolon
id|err
op_assign
id|ip6_build_xmit
c_func
(paren
id|sk
comma
id|rawv6_frag_cksum
comma
op_amp
id|hdr
comma
op_amp
id|fl
comma
id|len
comma
id|opt
comma
id|hlimit
comma
id|msg-&gt;msg_flags
)paren
suffix:semicolon
)brace
r_else
(brace
id|err
op_assign
id|ip6_build_xmit
c_func
(paren
id|sk
comma
id|rawv6_getfrag
comma
id|msg-&gt;msg_iov
comma
op_amp
id|fl
comma
id|len
comma
id|opt
comma
id|hlimit
comma
id|msg-&gt;msg_flags
)paren
suffix:semicolon
)brace
id|fl6_sock_release
c_func
(paren
id|flowlabel
)paren
suffix:semicolon
r_return
id|err
OL
l_int|0
ques
c_cond
id|err
suffix:colon
id|len
suffix:semicolon
)brace
DECL|function|rawv6_seticmpfilter
r_static
r_int
id|rawv6_seticmpfilter
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
(brace
r_switch
c_cond
(paren
id|optname
)paren
(brace
r_case
id|ICMPV6_FILTER
suffix:colon
r_if
c_cond
(paren
id|optlen
OG
r_sizeof
(paren
r_struct
id|icmp6_filter
)paren
)paren
id|optlen
op_assign
r_sizeof
(paren
r_struct
id|icmp6_filter
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|sk-&gt;tp_pinfo.tp_raw.filter
comma
id|optval
comma
id|optlen
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|ENOPROTOOPT
suffix:semicolon
)brace
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|rawv6_geticmpfilter
r_static
r_int
id|rawv6_geticmpfilter
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
(brace
r_int
id|len
suffix:semicolon
r_switch
c_cond
(paren
id|optname
)paren
(brace
r_case
id|ICMPV6_FILTER
suffix:colon
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|len
comma
id|optlen
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
r_sizeof
(paren
r_struct
id|icmp6_filter
)paren
)paren
id|len
op_assign
r_sizeof
(paren
r_struct
id|icmp6_filter
)paren
suffix:semicolon
r_if
c_cond
(paren
id|put_user
c_func
(paren
id|len
comma
id|optlen
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|optval
comma
op_amp
id|sk-&gt;tp_pinfo.tp_raw.filter
comma
id|len
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|ENOPROTOOPT
suffix:semicolon
)brace
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|rawv6_setsockopt
r_static
r_int
id|rawv6_setsockopt
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
(brace
r_struct
id|raw6_opt
op_star
id|opt
op_assign
op_amp
id|sk-&gt;tp_pinfo.tp_raw
suffix:semicolon
r_int
id|val
suffix:semicolon
r_switch
c_cond
(paren
id|level
)paren
(brace
r_case
id|SOL_RAW
suffix:colon
r_break
suffix:semicolon
r_case
id|SOL_ICMPV6
suffix:colon
r_if
c_cond
(paren
id|sk-&gt;num
op_ne
id|IPPROTO_ICMPV6
)paren
r_return
op_minus
id|EOPNOTSUPP
suffix:semicolon
r_return
id|rawv6_seticmpfilter
c_func
(paren
id|sk
comma
id|level
comma
id|optname
comma
id|optval
comma
id|optlen
)paren
suffix:semicolon
r_case
id|SOL_IPV6
suffix:colon
r_if
c_cond
(paren
id|optname
op_eq
id|IPV6_CHECKSUM
)paren
r_break
suffix:semicolon
r_default
suffix:colon
r_return
id|ipv6_setsockopt
c_func
(paren
id|sk
comma
id|level
comma
id|optname
comma
id|optval
comma
id|optlen
)paren
suffix:semicolon
)brace
suffix:semicolon
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|val
comma
(paren
r_int
op_star
)paren
id|optval
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_switch
c_cond
(paren
id|optname
)paren
(brace
r_case
id|IPV6_CHECKSUM
suffix:colon
r_if
c_cond
(paren
id|val
OL
l_int|0
)paren
(brace
id|opt-&gt;checksum
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|opt-&gt;checksum
op_assign
l_int|1
suffix:semicolon
id|opt-&gt;offset
op_assign
id|val
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|ENOPROTOOPT
suffix:semicolon
)brace
)brace
DECL|function|rawv6_getsockopt
r_static
r_int
id|rawv6_getsockopt
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
(brace
r_struct
id|raw6_opt
op_star
id|opt
op_assign
op_amp
id|sk-&gt;tp_pinfo.tp_raw
suffix:semicolon
r_int
id|val
comma
id|len
suffix:semicolon
r_switch
c_cond
(paren
id|level
)paren
(brace
r_case
id|SOL_RAW
suffix:colon
r_break
suffix:semicolon
r_case
id|SOL_ICMPV6
suffix:colon
r_if
c_cond
(paren
id|sk-&gt;num
op_ne
id|IPPROTO_ICMPV6
)paren
r_return
op_minus
id|EOPNOTSUPP
suffix:semicolon
r_return
id|rawv6_geticmpfilter
c_func
(paren
id|sk
comma
id|level
comma
id|optname
comma
id|optval
comma
id|optlen
)paren
suffix:semicolon
r_case
id|SOL_IPV6
suffix:colon
r_if
c_cond
(paren
id|optname
op_eq
id|IPV6_CHECKSUM
)paren
r_break
suffix:semicolon
r_default
suffix:colon
r_return
id|ipv6_getsockopt
c_func
(paren
id|sk
comma
id|level
comma
id|optname
comma
id|optval
comma
id|optlen
)paren
suffix:semicolon
)brace
suffix:semicolon
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|len
comma
id|optlen
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_switch
c_cond
(paren
id|optname
)paren
(brace
r_case
id|IPV6_CHECKSUM
suffix:colon
r_if
c_cond
(paren
id|opt-&gt;checksum
op_eq
l_int|0
)paren
id|val
op_assign
op_minus
l_int|1
suffix:semicolon
r_else
id|val
op_assign
id|opt-&gt;offset
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|ENOPROTOOPT
suffix:semicolon
)brace
id|len
op_assign
id|min_t
c_func
(paren
r_int
r_int
comma
r_sizeof
(paren
r_int
)paren
comma
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|put_user
c_func
(paren
id|len
comma
id|optlen
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|optval
comma
op_amp
id|val
comma
id|len
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|rawv6_ioctl
r_static
r_int
id|rawv6_ioctl
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
(brace
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|SIOCOUTQ
suffix:colon
(brace
r_int
id|amount
op_assign
id|atomic_read
c_func
(paren
op_amp
id|sk-&gt;wmem_alloc
)paren
suffix:semicolon
r_return
id|put_user
c_func
(paren
id|amount
comma
(paren
r_int
op_star
)paren
id|arg
)paren
suffix:semicolon
)brace
r_case
id|SIOCINQ
suffix:colon
(brace
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
r_int
id|amount
op_assign
l_int|0
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|sk-&gt;receive_queue.lock
)paren
suffix:semicolon
id|skb
op_assign
id|skb_peek
c_func
(paren
op_amp
id|sk-&gt;receive_queue
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb
op_ne
l_int|NULL
)paren
id|amount
op_assign
id|skb-&gt;tail
op_minus
id|skb-&gt;h.raw
suffix:semicolon
id|spin_unlock_irq
c_func
(paren
op_amp
id|sk-&gt;receive_queue.lock
)paren
suffix:semicolon
r_return
id|put_user
c_func
(paren
id|amount
comma
(paren
r_int
op_star
)paren
id|arg
)paren
suffix:semicolon
)brace
r_default
suffix:colon
r_return
op_minus
id|ENOIOCTLCMD
suffix:semicolon
)brace
)brace
DECL|function|rawv6_close
r_static
r_void
id|rawv6_close
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_int
id|timeout
)paren
(brace
r_if
c_cond
(paren
id|sk-&gt;num
op_eq
id|IPPROTO_RAW
)paren
id|ip6_ra_control
c_func
(paren
id|sk
comma
op_minus
l_int|1
comma
l_int|NULL
)paren
suffix:semicolon
id|inet_sock_release
c_func
(paren
id|sk
)paren
suffix:semicolon
)brace
DECL|function|rawv6_init_sk
r_static
r_int
id|rawv6_init_sk
c_func
(paren
r_struct
id|sock
op_star
id|sk
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|macro|LINE_LEN
mdefine_line|#define LINE_LEN 190
DECL|macro|LINE_FMT
mdefine_line|#define LINE_FMT &quot;%-190s&bslash;n&quot;
DECL|function|get_raw6_sock
r_static
r_void
id|get_raw6_sock
c_func
(paren
r_struct
id|sock
op_star
id|sp
comma
r_char
op_star
id|tmpbuf
comma
r_int
id|i
)paren
(brace
r_struct
id|in6_addr
op_star
id|dest
comma
op_star
id|src
suffix:semicolon
id|__u16
id|destp
comma
id|srcp
suffix:semicolon
id|dest
op_assign
op_amp
id|sp-&gt;net_pinfo.af_inet6.daddr
suffix:semicolon
id|src
op_assign
op_amp
id|sp-&gt;net_pinfo.af_inet6.rcv_saddr
suffix:semicolon
id|destp
op_assign
l_int|0
suffix:semicolon
id|srcp
op_assign
id|sp-&gt;num
suffix:semicolon
id|sprintf
c_func
(paren
id|tmpbuf
comma
l_string|&quot;%4d: %08X%08X%08X%08X:%04X %08X%08X%08X%08X:%04X &quot;
l_string|&quot;%02X %08X:%08X %02X:%08lX %08X %5d %8d %ld %d %p&quot;
comma
id|i
comma
id|src-&gt;s6_addr32
(braket
l_int|0
)braket
comma
id|src-&gt;s6_addr32
(braket
l_int|1
)braket
comma
id|src-&gt;s6_addr32
(braket
l_int|2
)braket
comma
id|src-&gt;s6_addr32
(braket
l_int|3
)braket
comma
id|srcp
comma
id|dest-&gt;s6_addr32
(braket
l_int|0
)braket
comma
id|dest-&gt;s6_addr32
(braket
l_int|1
)braket
comma
id|dest-&gt;s6_addr32
(braket
l_int|2
)braket
comma
id|dest-&gt;s6_addr32
(braket
l_int|3
)braket
comma
id|destp
comma
id|sp-&gt;state
comma
id|atomic_read
c_func
(paren
op_amp
id|sp-&gt;wmem_alloc
)paren
comma
id|atomic_read
c_func
(paren
op_amp
id|sp-&gt;rmem_alloc
)paren
comma
l_int|0
comma
l_int|0L
comma
l_int|0
comma
id|sock_i_uid
c_func
(paren
id|sp
)paren
comma
l_int|0
comma
id|sock_i_ino
c_func
(paren
id|sp
)paren
comma
id|atomic_read
c_func
(paren
op_amp
id|sp-&gt;refcnt
)paren
comma
id|sp
)paren
suffix:semicolon
)brace
DECL|function|raw6_get_info
r_int
id|raw6_get_info
c_func
(paren
r_char
op_star
id|buffer
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|offset
comma
r_int
id|length
)paren
(brace
r_int
id|len
op_assign
l_int|0
comma
id|num
op_assign
l_int|0
comma
id|i
suffix:semicolon
id|off_t
id|pos
op_assign
l_int|0
suffix:semicolon
id|off_t
id|begin
suffix:semicolon
r_char
id|tmpbuf
(braket
id|LINE_LEN
op_plus
l_int|2
)braket
suffix:semicolon
r_if
c_cond
(paren
id|offset
OL
id|LINE_LEN
op_plus
l_int|1
)paren
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
comma
id|LINE_FMT
comma
l_string|&quot;  sl  &quot;
multiline_comment|/* 6 */
l_string|&quot;local_address                         &quot;
multiline_comment|/* 38 */
l_string|&quot;remote_address                        &quot;
multiline_comment|/* 38 */
l_string|&quot;st tx_queue rx_queue tr tm-&gt;when retrnsmt&quot;
multiline_comment|/* 41 */
l_string|&quot;   uid  timeout inode&quot;
)paren
suffix:semicolon
multiline_comment|/* 21 */
multiline_comment|/*----*/
multiline_comment|/*144 */
id|pos
op_assign
id|LINE_LEN
op_plus
l_int|1
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|raw_v6_lock
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
id|RAWV6_HTABLE_SIZE
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|sock
op_star
id|sk
suffix:semicolon
r_for
c_loop
(paren
id|sk
op_assign
id|raw_v6_htable
(braket
id|i
)braket
suffix:semicolon
id|sk
suffix:semicolon
id|sk
op_assign
id|sk-&gt;next
comma
id|num
op_increment
)paren
(brace
r_if
c_cond
(paren
id|sk-&gt;family
op_ne
id|PF_INET6
)paren
r_continue
suffix:semicolon
id|pos
op_add_assign
id|LINE_LEN
op_plus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|pos
op_le
id|offset
)paren
r_continue
suffix:semicolon
id|get_raw6_sock
c_func
(paren
id|sk
comma
id|tmpbuf
comma
id|i
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
id|LINE_FMT
comma
id|tmpbuf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
op_ge
id|length
)paren
(brace
r_goto
id|out
suffix:semicolon
)brace
)brace
)brace
id|out
suffix:colon
id|read_unlock
c_func
(paren
op_amp
id|raw_v6_lock
)paren
suffix:semicolon
id|begin
op_assign
id|len
op_minus
(paren
id|pos
op_minus
id|offset
)paren
suffix:semicolon
op_star
id|start
op_assign
id|buffer
op_plus
id|begin
suffix:semicolon
id|len
op_sub_assign
id|begin
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
id|length
)paren
(brace
id|len
op_assign
id|length
suffix:semicolon
)brace
r_if
c_cond
(paren
id|len
OL
l_int|0
)paren
id|len
op_assign
l_int|0
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
DECL|variable|rawv6_prot
r_struct
id|proto
id|rawv6_prot
op_assign
(brace
id|name
suffix:colon
l_string|&quot;RAW&quot;
comma
id|close
suffix:colon
id|rawv6_close
comma
id|connect
suffix:colon
id|udpv6_connect
comma
id|disconnect
suffix:colon
id|udp_disconnect
comma
id|ioctl
suffix:colon
id|rawv6_ioctl
comma
id|init
suffix:colon
id|rawv6_init_sk
comma
id|destroy
suffix:colon
id|inet6_destroy_sock
comma
id|setsockopt
suffix:colon
id|rawv6_setsockopt
comma
id|getsockopt
suffix:colon
id|rawv6_getsockopt
comma
id|sendmsg
suffix:colon
id|rawv6_sendmsg
comma
id|recvmsg
suffix:colon
id|rawv6_recvmsg
comma
id|bind
suffix:colon
id|rawv6_bind
comma
id|backlog_rcv
suffix:colon
id|rawv6_rcv_skb
comma
id|hash
suffix:colon
id|raw_v6_hash
comma
id|unhash
suffix:colon
id|raw_v6_unhash
comma
)brace
suffix:semicolon
eof
