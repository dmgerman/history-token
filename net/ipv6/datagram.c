multiline_comment|/*&n; *&t;common UDP/RAW code&n; *&t;Linux INET6 implementation &n; *&n; *&t;Authors:&n; *&t;Pedro Roque&t;&t;&lt;roque@di.fc.ul.pt&gt;&t;&n; *&n; *&t;$Id: datagram.c,v 1.24 2002/02/01 22:01:04 davem Exp $&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *      modify it under the terms of the GNU General Public License&n; *      as published by the Free Software Foundation; either version&n; *      2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/sockios.h&gt;
macro_line|#include &lt;linux/in6.h&gt;
macro_line|#include &lt;linux/ipv6.h&gt;
macro_line|#include &lt;linux/route.h&gt;
macro_line|#include &lt;net/ipv6.h&gt;
macro_line|#include &lt;net/ndisc.h&gt;
macro_line|#include &lt;net/addrconf.h&gt;
macro_line|#include &lt;net/transp_v6.h&gt;
macro_line|#include &lt;linux/errqueue.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
DECL|function|ipv6_icmp_error
r_void
id|ipv6_icmp_error
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
(brace
r_struct
id|ipv6_pinfo
op_star
id|np
op_assign
id|inet6_sk
c_func
(paren
id|sk
)paren
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
id|sock_exterr_skb
op_star
id|serr
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|np-&gt;recverr
)paren
r_return
suffix:semicolon
id|skb
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
op_logical_neg
id|skb
)paren
r_return
suffix:semicolon
id|serr
op_assign
id|SKB_EXT_ERR
c_func
(paren
id|skb
)paren
suffix:semicolon
id|serr-&gt;ee.ee_errno
op_assign
id|err
suffix:semicolon
id|serr-&gt;ee.ee_origin
op_assign
id|SO_EE_ORIGIN_ICMP6
suffix:semicolon
id|serr-&gt;ee.ee_type
op_assign
id|icmph-&gt;icmp6_type
suffix:semicolon
id|serr-&gt;ee.ee_code
op_assign
id|icmph-&gt;icmp6_code
suffix:semicolon
id|serr-&gt;ee.ee_pad
op_assign
l_int|0
suffix:semicolon
id|serr-&gt;ee.ee_info
op_assign
id|info
suffix:semicolon
id|serr-&gt;ee.ee_data
op_assign
l_int|0
suffix:semicolon
id|serr-&gt;addr_offset
op_assign
(paren
id|u8
op_star
)paren
op_amp
(paren
(paren
(paren
r_struct
id|ipv6hdr
op_star
)paren
(paren
id|icmph
op_plus
l_int|1
)paren
)paren
op_member_access_from_pointer
id|daddr
)paren
op_minus
id|skb-&gt;nh.raw
suffix:semicolon
id|serr-&gt;port
op_assign
id|port
suffix:semicolon
id|skb-&gt;h.raw
op_assign
id|payload
suffix:semicolon
id|__skb_pull
c_func
(paren
id|skb
comma
id|payload
op_minus
id|skb-&gt;data
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sock_queue_err_skb
c_func
(paren
id|sk
comma
id|skb
)paren
)paren
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
DECL|function|ipv6_local_error
r_void
id|ipv6_local_error
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
r_struct
id|flowi
op_star
id|fl
comma
id|u32
id|info
)paren
(brace
r_struct
id|ipv6_pinfo
op_star
id|np
op_assign
id|inet6_sk
c_func
(paren
id|sk
)paren
suffix:semicolon
r_struct
id|sock_exterr_skb
op_star
id|serr
suffix:semicolon
r_struct
id|ipv6hdr
op_star
id|iph
suffix:semicolon
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|np-&gt;recverr
)paren
r_return
suffix:semicolon
id|skb
op_assign
id|alloc_skb
c_func
(paren
r_sizeof
(paren
r_struct
id|ipv6hdr
)paren
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|skb
)paren
r_return
suffix:semicolon
id|iph
op_assign
(paren
r_struct
id|ipv6hdr
op_star
)paren
id|skb_put
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
suffix:semicolon
id|skb-&gt;nh.ipv6h
op_assign
id|iph
suffix:semicolon
id|ipv6_addr_copy
c_func
(paren
op_amp
id|iph-&gt;daddr
comma
op_amp
id|fl-&gt;fl6_dst
)paren
suffix:semicolon
id|serr
op_assign
id|SKB_EXT_ERR
c_func
(paren
id|skb
)paren
suffix:semicolon
id|serr-&gt;ee.ee_errno
op_assign
id|err
suffix:semicolon
id|serr-&gt;ee.ee_origin
op_assign
id|SO_EE_ORIGIN_LOCAL
suffix:semicolon
id|serr-&gt;ee.ee_type
op_assign
l_int|0
suffix:semicolon
id|serr-&gt;ee.ee_code
op_assign
l_int|0
suffix:semicolon
id|serr-&gt;ee.ee_pad
op_assign
l_int|0
suffix:semicolon
id|serr-&gt;ee.ee_info
op_assign
id|info
suffix:semicolon
id|serr-&gt;ee.ee_data
op_assign
l_int|0
suffix:semicolon
id|serr-&gt;addr_offset
op_assign
(paren
id|u8
op_star
)paren
op_amp
id|iph-&gt;daddr
op_minus
id|skb-&gt;nh.raw
suffix:semicolon
id|serr-&gt;port
op_assign
id|fl-&gt;fl_ip_dport
suffix:semicolon
id|skb-&gt;h.raw
op_assign
id|skb-&gt;tail
suffix:semicolon
id|__skb_pull
c_func
(paren
id|skb
comma
id|skb-&gt;tail
op_minus
id|skb-&gt;data
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sock_queue_err_skb
c_func
(paren
id|sk
comma
id|skb
)paren
)paren
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
multiline_comment|/* &n; *&t;Handle MSG_ERRQUEUE&n; */
DECL|function|ipv6_recv_error
r_int
id|ipv6_recv_error
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
id|ipv6_pinfo
op_star
id|np
op_assign
id|inet6_sk
c_func
(paren
id|sk
)paren
suffix:semicolon
r_struct
id|sock_exterr_skb
op_star
id|serr
suffix:semicolon
r_struct
id|sk_buff
op_star
id|skb
comma
op_star
id|skb2
suffix:semicolon
r_struct
id|sockaddr_in6
op_star
id|sin
suffix:semicolon
r_struct
(brace
r_struct
id|sock_extended_err
id|ee
suffix:semicolon
r_struct
id|sockaddr_in6
id|offender
suffix:semicolon
)brace
id|errhdr
suffix:semicolon
r_int
id|err
suffix:semicolon
r_int
id|copied
suffix:semicolon
id|err
op_assign
op_minus
id|EAGAIN
suffix:semicolon
id|skb
op_assign
id|skb_dequeue
c_func
(paren
op_amp
id|sk-&gt;sk_error_queue
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb
op_eq
l_int|NULL
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
id|msg-&gt;msg_flags
op_or_assign
id|MSG_TRUNC
suffix:semicolon
id|copied
op_assign
id|len
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
id|out_free_skb
suffix:semicolon
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
id|serr
op_assign
id|SKB_EXT_ERR
c_func
(paren
id|skb
)paren
suffix:semicolon
id|sin
op_assign
(paren
r_struct
id|sockaddr_in6
op_star
)paren
id|msg-&gt;msg_name
suffix:semicolon
r_if
c_cond
(paren
id|sin
)paren
(brace
id|sin-&gt;sin6_family
op_assign
id|AF_INET6
suffix:semicolon
id|sin-&gt;sin6_flowinfo
op_assign
l_int|0
suffix:semicolon
id|sin-&gt;sin6_port
op_assign
id|serr-&gt;port
suffix:semicolon
id|sin-&gt;sin6_scope_id
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|serr-&gt;ee.ee_origin
op_eq
id|SO_EE_ORIGIN_ICMP6
)paren
(brace
id|ipv6_addr_copy
c_func
(paren
op_amp
id|sin-&gt;sin6_addr
comma
(paren
r_struct
id|in6_addr
op_star
)paren
(paren
id|skb-&gt;nh.raw
op_plus
id|serr-&gt;addr_offset
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|np-&gt;sndflow
)paren
id|sin-&gt;sin6_flowinfo
op_assign
op_star
(paren
id|u32
op_star
)paren
(paren
id|skb-&gt;nh.raw
op_plus
id|serr-&gt;addr_offset
op_minus
l_int|24
)paren
op_amp
id|IPV6_FLOWINFO_MASK
suffix:semicolon
r_if
c_cond
(paren
id|ipv6_addr_type
c_func
(paren
op_amp
id|sin-&gt;sin6_addr
)paren
op_amp
id|IPV6_ADDR_LINKLOCAL
)paren
id|sin-&gt;sin6_scope_id
op_assign
id|IP6CB
c_func
(paren
id|skb
)paren
op_member_access_from_pointer
id|iif
suffix:semicolon
)brace
r_else
(brace
id|ipv6_addr_set
c_func
(paren
op_amp
id|sin-&gt;sin6_addr
comma
l_int|0
comma
l_int|0
comma
id|htonl
c_func
(paren
l_int|0xffff
)paren
comma
op_star
(paren
id|u32
op_star
)paren
(paren
id|skb-&gt;nh.raw
op_plus
id|serr-&gt;addr_offset
)paren
)paren
suffix:semicolon
)brace
)brace
id|memcpy
c_func
(paren
op_amp
id|errhdr.ee
comma
op_amp
id|serr-&gt;ee
comma
r_sizeof
(paren
r_struct
id|sock_extended_err
)paren
)paren
suffix:semicolon
id|sin
op_assign
op_amp
id|errhdr.offender
suffix:semicolon
id|sin-&gt;sin6_family
op_assign
id|AF_UNSPEC
suffix:semicolon
r_if
c_cond
(paren
id|serr-&gt;ee.ee_origin
op_ne
id|SO_EE_ORIGIN_LOCAL
)paren
(brace
id|sin-&gt;sin6_family
op_assign
id|AF_INET6
suffix:semicolon
id|sin-&gt;sin6_flowinfo
op_assign
l_int|0
suffix:semicolon
id|sin-&gt;sin6_scope_id
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|serr-&gt;ee.ee_origin
op_eq
id|SO_EE_ORIGIN_ICMP6
)paren
(brace
id|ipv6_addr_copy
c_func
(paren
op_amp
id|sin-&gt;sin6_addr
comma
op_amp
id|skb-&gt;nh.ipv6h-&gt;saddr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|np-&gt;rxopt.all
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
r_if
c_cond
(paren
id|ipv6_addr_type
c_func
(paren
op_amp
id|sin-&gt;sin6_addr
)paren
op_amp
id|IPV6_ADDR_LINKLOCAL
)paren
id|sin-&gt;sin6_scope_id
op_assign
id|IP6CB
c_func
(paren
id|skb
)paren
op_member_access_from_pointer
id|iif
suffix:semicolon
)brace
r_else
(brace
r_struct
id|inet_opt
op_star
id|inet
op_assign
id|inet_sk
c_func
(paren
id|sk
)paren
suffix:semicolon
id|ipv6_addr_set
c_func
(paren
op_amp
id|sin-&gt;sin6_addr
comma
l_int|0
comma
l_int|0
comma
id|htonl
c_func
(paren
l_int|0xffff
)paren
comma
id|skb-&gt;nh.iph-&gt;saddr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|inet-&gt;cmsg_flags
)paren
id|ip_cmsg_recv
c_func
(paren
id|msg
comma
id|skb
)paren
suffix:semicolon
)brace
)brace
id|put_cmsg
c_func
(paren
id|msg
comma
id|SOL_IPV6
comma
id|IPV6_RECVERR
comma
r_sizeof
(paren
id|errhdr
)paren
comma
op_amp
id|errhdr
)paren
suffix:semicolon
multiline_comment|/* Now we could try to dump offended packet options */
id|msg-&gt;msg_flags
op_or_assign
id|MSG_ERRQUEUE
suffix:semicolon
id|err
op_assign
id|copied
suffix:semicolon
multiline_comment|/* Reset and regenerate socket error */
id|spin_lock_irq
c_func
(paren
op_amp
id|sk-&gt;sk_error_queue.lock
)paren
suffix:semicolon
id|sk-&gt;sk_err
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|skb2
op_assign
id|skb_peek
c_func
(paren
op_amp
id|sk-&gt;sk_error_queue
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
id|sk-&gt;sk_err
op_assign
id|SKB_EXT_ERR
c_func
(paren
id|skb2
)paren
op_member_access_from_pointer
id|ee.ee_errno
suffix:semicolon
id|spin_unlock_irq
c_func
(paren
op_amp
id|sk-&gt;sk_error_queue.lock
)paren
suffix:semicolon
id|sk
op_member_access_from_pointer
id|sk_error_report
c_func
(paren
id|sk
)paren
suffix:semicolon
)brace
r_else
(brace
id|spin_unlock_irq
c_func
(paren
op_amp
id|sk-&gt;sk_error_queue.lock
)paren
suffix:semicolon
)brace
id|out_free_skb
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
id|err
suffix:semicolon
)brace
DECL|function|datagram_recv_ctl
r_int
id|datagram_recv_ctl
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
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|ipv6_pinfo
op_star
id|np
op_assign
id|inet6_sk
c_func
(paren
id|sk
)paren
suffix:semicolon
r_struct
id|inet6_skb_parm
op_star
id|opt
op_assign
id|IP6CB
c_func
(paren
id|skb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|np-&gt;rxopt.bits.rxinfo
)paren
(brace
r_struct
id|in6_pktinfo
id|src_info
suffix:semicolon
id|src_info.ipi6_ifindex
op_assign
id|opt-&gt;iif
suffix:semicolon
id|ipv6_addr_copy
c_func
(paren
op_amp
id|src_info.ipi6_addr
comma
op_amp
id|skb-&gt;nh.ipv6h-&gt;daddr
)paren
suffix:semicolon
id|put_cmsg
c_func
(paren
id|msg
comma
id|SOL_IPV6
comma
id|IPV6_PKTINFO
comma
r_sizeof
(paren
id|src_info
)paren
comma
op_amp
id|src_info
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|np-&gt;rxopt.bits.rxhlim
)paren
(brace
r_int
id|hlim
op_assign
id|skb-&gt;nh.ipv6h-&gt;hop_limit
suffix:semicolon
id|put_cmsg
c_func
(paren
id|msg
comma
id|SOL_IPV6
comma
id|IPV6_HOPLIMIT
comma
r_sizeof
(paren
id|hlim
)paren
comma
op_amp
id|hlim
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|np-&gt;rxopt.bits.rxflow
op_logical_and
(paren
op_star
(paren
id|u32
op_star
)paren
id|skb-&gt;nh.raw
op_amp
id|IPV6_FLOWINFO_MASK
)paren
)paren
(brace
id|u32
id|flowinfo
op_assign
op_star
(paren
id|u32
op_star
)paren
id|skb-&gt;nh.raw
op_amp
id|IPV6_FLOWINFO_MASK
suffix:semicolon
id|put_cmsg
c_func
(paren
id|msg
comma
id|SOL_IPV6
comma
id|IPV6_FLOWINFO
comma
r_sizeof
(paren
id|flowinfo
)paren
comma
op_amp
id|flowinfo
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|np-&gt;rxopt.bits.hopopts
op_logical_and
id|opt-&gt;hop
)paren
(brace
id|u8
op_star
id|ptr
op_assign
id|skb-&gt;nh.raw
op_plus
id|opt-&gt;hop
suffix:semicolon
id|put_cmsg
c_func
(paren
id|msg
comma
id|SOL_IPV6
comma
id|IPV6_HOPOPTS
comma
(paren
id|ptr
(braket
l_int|1
)braket
op_plus
l_int|1
)paren
op_lshift
l_int|3
comma
id|ptr
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|np-&gt;rxopt.bits.dstopts
op_logical_and
id|opt-&gt;dst0
)paren
(brace
id|u8
op_star
id|ptr
op_assign
id|skb-&gt;nh.raw
op_plus
id|opt-&gt;dst0
suffix:semicolon
id|put_cmsg
c_func
(paren
id|msg
comma
id|SOL_IPV6
comma
id|IPV6_DSTOPTS
comma
(paren
id|ptr
(braket
l_int|1
)braket
op_plus
l_int|1
)paren
op_lshift
l_int|3
comma
id|ptr
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|np-&gt;rxopt.bits.srcrt
op_logical_and
id|opt-&gt;srcrt
)paren
(brace
r_struct
id|ipv6_rt_hdr
op_star
id|rthdr
op_assign
(paren
r_struct
id|ipv6_rt_hdr
op_star
)paren
(paren
id|skb-&gt;nh.raw
op_plus
id|opt-&gt;srcrt
)paren
suffix:semicolon
id|put_cmsg
c_func
(paren
id|msg
comma
id|SOL_IPV6
comma
id|IPV6_RTHDR
comma
(paren
id|rthdr-&gt;hdrlen
op_plus
l_int|1
)paren
op_lshift
l_int|3
comma
id|rthdr
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|np-&gt;rxopt.bits.dstopts
op_logical_and
id|opt-&gt;dst1
)paren
(brace
id|u8
op_star
id|ptr
op_assign
id|skb-&gt;nh.raw
op_plus
id|opt-&gt;dst1
suffix:semicolon
id|put_cmsg
c_func
(paren
id|msg
comma
id|SOL_IPV6
comma
id|IPV6_DSTOPTS
comma
(paren
id|ptr
(braket
l_int|1
)braket
op_plus
l_int|1
)paren
op_lshift
l_int|3
comma
id|ptr
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|datagram_send_ctl
r_int
id|datagram_send_ctl
c_func
(paren
r_struct
id|msghdr
op_star
id|msg
comma
r_struct
id|flowi
op_star
id|fl
comma
r_struct
id|ipv6_txoptions
op_star
id|opt
comma
r_int
op_star
id|hlimit
)paren
(brace
r_struct
id|in6_pktinfo
op_star
id|src_info
suffix:semicolon
r_struct
id|cmsghdr
op_star
id|cmsg
suffix:semicolon
r_struct
id|ipv6_rt_hdr
op_star
id|rthdr
suffix:semicolon
r_struct
id|ipv6_opt_hdr
op_star
id|hdr
suffix:semicolon
r_int
id|len
suffix:semicolon
r_int
id|err
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|cmsg
op_assign
id|CMSG_FIRSTHDR
c_func
(paren
id|msg
)paren
suffix:semicolon
id|cmsg
suffix:semicolon
id|cmsg
op_assign
id|CMSG_NXTHDR
c_func
(paren
id|msg
comma
id|cmsg
)paren
)paren
(brace
r_int
id|addr_type
suffix:semicolon
r_struct
id|net_device
op_star
id|dev
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|cmsg-&gt;cmsg_len
template_param
id|msg-&gt;msg_controllen
)paren
(brace
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|exit_f
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cmsg-&gt;cmsg_level
op_ne
id|SOL_IPV6
)paren
r_continue
suffix:semicolon
r_switch
c_cond
(paren
id|cmsg-&gt;cmsg_type
)paren
(brace
r_case
id|IPV6_PKTINFO
suffix:colon
r_if
c_cond
(paren
id|cmsg-&gt;cmsg_len
OL
id|CMSG_LEN
c_func
(paren
r_sizeof
(paren
r_struct
id|in6_pktinfo
)paren
)paren
)paren
(brace
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|exit_f
suffix:semicolon
)brace
id|src_info
op_assign
(paren
r_struct
id|in6_pktinfo
op_star
)paren
id|CMSG_DATA
c_func
(paren
id|cmsg
)paren
suffix:semicolon
r_if
c_cond
(paren
id|src_info-&gt;ipi6_ifindex
)paren
(brace
r_if
c_cond
(paren
id|fl-&gt;oif
op_logical_and
id|src_info-&gt;ipi6_ifindex
op_ne
id|fl-&gt;oif
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|fl-&gt;oif
op_assign
id|src_info-&gt;ipi6_ifindex
suffix:semicolon
)brace
id|addr_type
op_assign
id|ipv6_addr_type
c_func
(paren
op_amp
id|src_info-&gt;ipi6_addr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|addr_type
op_eq
id|IPV6_ADDR_ANY
)paren
r_break
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
op_logical_neg
id|src_info-&gt;ipi6_ifindex
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_else
(brace
id|dev
op_assign
id|dev_get_by_index
c_func
(paren
id|src_info-&gt;ipi6_ifindex
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|ipv6_chk_addr
c_func
(paren
op_amp
id|src_info-&gt;ipi6_addr
comma
id|dev
comma
l_int|0
)paren
)paren
(brace
r_if
c_cond
(paren
id|dev
)paren
id|dev_put
c_func
(paren
id|dev
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|exit_f
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dev
)paren
id|dev_put
c_func
(paren
id|dev
)paren
suffix:semicolon
id|ipv6_addr_copy
c_func
(paren
op_amp
id|fl-&gt;fl6_src
comma
op_amp
id|src_info-&gt;ipi6_addr
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IPV6_FLOWINFO
suffix:colon
r_if
c_cond
(paren
id|cmsg-&gt;cmsg_len
OL
id|CMSG_LEN
c_func
(paren
l_int|4
)paren
)paren
(brace
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|exit_f
suffix:semicolon
)brace
r_if
c_cond
(paren
id|fl-&gt;fl6_flowlabel
op_amp
id|IPV6_FLOWINFO_MASK
)paren
(brace
r_if
c_cond
(paren
(paren
id|fl-&gt;fl6_flowlabel
op_xor
op_star
(paren
id|u32
op_star
)paren
id|CMSG_DATA
c_func
(paren
id|cmsg
)paren
)paren
op_amp
op_complement
id|IPV6_FLOWINFO_MASK
)paren
(brace
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|exit_f
suffix:semicolon
)brace
)brace
id|fl-&gt;fl6_flowlabel
op_assign
id|IPV6_FLOWINFO_MASK
op_amp
op_star
(paren
id|u32
op_star
)paren
id|CMSG_DATA
c_func
(paren
id|cmsg
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IPV6_HOPOPTS
suffix:colon
r_if
c_cond
(paren
id|opt-&gt;hopopt
op_logical_or
id|cmsg-&gt;cmsg_len
OL
id|CMSG_LEN
c_func
(paren
r_sizeof
(paren
r_struct
id|ipv6_opt_hdr
)paren
)paren
)paren
(brace
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|exit_f
suffix:semicolon
)brace
id|hdr
op_assign
(paren
r_struct
id|ipv6_opt_hdr
op_star
)paren
id|CMSG_DATA
c_func
(paren
id|cmsg
)paren
suffix:semicolon
id|len
op_assign
(paren
(paren
id|hdr-&gt;hdrlen
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
id|cmsg-&gt;cmsg_len
OL
id|CMSG_LEN
c_func
(paren
id|len
)paren
)paren
(brace
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|exit_f
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_NET_RAW
)paren
)paren
(brace
id|err
op_assign
op_minus
id|EPERM
suffix:semicolon
r_goto
id|exit_f
suffix:semicolon
)brace
id|opt-&gt;opt_nflen
op_add_assign
id|len
suffix:semicolon
id|opt-&gt;hopopt
op_assign
id|hdr
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IPV6_DSTOPTS
suffix:colon
r_if
c_cond
(paren
id|cmsg-&gt;cmsg_len
OL
id|CMSG_LEN
c_func
(paren
r_sizeof
(paren
r_struct
id|ipv6_opt_hdr
)paren
)paren
)paren
(brace
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|exit_f
suffix:semicolon
)brace
id|hdr
op_assign
(paren
r_struct
id|ipv6_opt_hdr
op_star
)paren
id|CMSG_DATA
c_func
(paren
id|cmsg
)paren
suffix:semicolon
id|len
op_assign
(paren
(paren
id|hdr-&gt;hdrlen
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
id|cmsg-&gt;cmsg_len
OL
id|CMSG_LEN
c_func
(paren
id|len
)paren
)paren
(brace
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|exit_f
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_NET_RAW
)paren
)paren
(brace
id|err
op_assign
op_minus
id|EPERM
suffix:semicolon
r_goto
id|exit_f
suffix:semicolon
)brace
r_if
c_cond
(paren
id|opt-&gt;dst1opt
)paren
(brace
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|exit_f
suffix:semicolon
)brace
id|opt-&gt;opt_flen
op_add_assign
id|len
suffix:semicolon
id|opt-&gt;dst1opt
op_assign
id|hdr
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IPV6_RTHDR
suffix:colon
r_if
c_cond
(paren
id|cmsg-&gt;cmsg_len
OL
id|CMSG_LEN
c_func
(paren
r_sizeof
(paren
r_struct
id|ipv6_rt_hdr
)paren
)paren
)paren
(brace
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|exit_f
suffix:semicolon
)brace
id|rthdr
op_assign
(paren
r_struct
id|ipv6_rt_hdr
op_star
)paren
id|CMSG_DATA
c_func
(paren
id|cmsg
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; *&t;TYPE 0&n;&t;&t;&t; */
r_if
c_cond
(paren
id|rthdr-&gt;type
)paren
(brace
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|exit_f
suffix:semicolon
)brace
id|len
op_assign
(paren
(paren
id|rthdr-&gt;hdrlen
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
id|cmsg-&gt;cmsg_len
OL
id|CMSG_LEN
c_func
(paren
id|len
)paren
)paren
(brace
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|exit_f
suffix:semicolon
)brace
multiline_comment|/* segments left must also match */
r_if
c_cond
(paren
(paren
id|rthdr-&gt;hdrlen
op_rshift
l_int|1
)paren
op_ne
id|rthdr-&gt;segments_left
)paren
(brace
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|exit_f
suffix:semicolon
)brace
id|opt-&gt;opt_nflen
op_add_assign
id|len
suffix:semicolon
id|opt-&gt;srcrt
op_assign
id|rthdr
suffix:semicolon
r_if
c_cond
(paren
id|opt-&gt;dst1opt
)paren
(brace
r_int
id|dsthdrlen
op_assign
(paren
(paren
id|opt-&gt;dst1opt-&gt;hdrlen
op_plus
l_int|1
)paren
op_lshift
l_int|3
)paren
suffix:semicolon
id|opt-&gt;opt_nflen
op_add_assign
id|dsthdrlen
suffix:semicolon
id|opt-&gt;dst0opt
op_assign
id|opt-&gt;dst1opt
suffix:semicolon
id|opt-&gt;dst1opt
op_assign
l_int|NULL
suffix:semicolon
id|opt-&gt;opt_flen
op_sub_assign
id|dsthdrlen
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|IPV6_HOPLIMIT
suffix:colon
r_if
c_cond
(paren
id|cmsg-&gt;cmsg_len
op_ne
id|CMSG_LEN
c_func
(paren
r_sizeof
(paren
r_int
)paren
)paren
)paren
(brace
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|exit_f
suffix:semicolon
)brace
op_star
id|hlimit
op_assign
op_star
(paren
r_int
op_star
)paren
id|CMSG_DATA
c_func
(paren
id|cmsg
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|LIMIT_NETDEBUG
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;invalid cmsg type: %d&bslash;n&quot;
comma
id|cmsg-&gt;cmsg_type
)paren
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_break
suffix:semicolon
)brace
suffix:semicolon
)brace
id|exit_f
suffix:colon
r_return
id|err
suffix:semicolon
)brace
eof
