multiline_comment|/*&n; *&t;IPv6 BSD socket options interface&n; *&t;Linux INET6 implementation &n; *&n; *&t;Authors:&n; *&t;Pedro Roque&t;&t;&lt;roque@di.fc.ul.pt&gt;&t;&n; *&n; *&t;Based on linux/net/ipv4/ip_sockglue.c&n; *&n; *&t;$Id: ipv6_sockglue.c,v 1.41 2002/02/01 22:01:04 davem Exp $&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *      modify it under the terms of the GNU General Public License&n; *      as published by the Free Software Foundation; either version&n; *      2 of the License, or (at your option) any later version.&n; *&n; *&t;FIXME: Make the setsockopt code POSIX compliant: That is&n; *&n; *&t;o&t;Return -EINVAL for setsockopt of short lengths&n; *&t;o&t;Truncate getsockopt returns&n; *&t;o&t;Return an optlen of the truncated length if need be&n; *&n; *&t;Changes:&n; *&t;David L Stevens &lt;dlstevens@us.ibm.com&gt;:&n; *&t;&t;- added multicast source filtering API for MLDv2&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/sockios.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/net.h&gt;
macro_line|#include &lt;linux/in6.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/if_arp.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/sysctl.h&gt;
macro_line|#include &lt;linux/netfilter.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;net/snmp.h&gt;
macro_line|#include &lt;net/ipv6.h&gt;
macro_line|#include &lt;net/ndisc.h&gt;
macro_line|#include &lt;net/protocol.h&gt;
macro_line|#include &lt;net/transp_v6.h&gt;
macro_line|#include &lt;net/ip6_route.h&gt;
macro_line|#include &lt;net/addrconf.h&gt;
macro_line|#include &lt;net/inet_common.h&gt;
macro_line|#include &lt;net/tcp.h&gt;
macro_line|#include &lt;net/udp.h&gt;
macro_line|#include &lt;net/xfrm.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
id|DEFINE_SNMP_STAT
c_func
(paren
r_struct
id|ipv6_mib
comma
id|ipv6_statistics
)paren
suffix:semicolon
DECL|variable|ipv6_packet_type
r_static
r_struct
id|packet_type
id|ipv6_packet_type
op_assign
(brace
dot
id|type
op_assign
id|__constant_htons
c_func
(paren
id|ETH_P_IPV6
)paren
comma
dot
id|dev
op_assign
l_int|NULL
comma
multiline_comment|/* All devices */
dot
id|func
op_assign
id|ipv6_rcv
comma
dot
id|data
op_assign
id|PKT_CAN_SHARE_SKB
comma
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;addrconf module should be notified of a device going up&n; */
DECL|variable|ipv6_dev_notf
r_static
r_struct
id|notifier_block
id|ipv6_dev_notf
op_assign
(brace
dot
id|notifier_call
op_assign
id|addrconf_notify
comma
dot
id|priority
op_assign
l_int|0
)brace
suffix:semicolon
DECL|variable|ip6_ra_chain
r_struct
id|ip6_ra_chain
op_star
id|ip6_ra_chain
suffix:semicolon
DECL|variable|ip6_ra_lock
id|rwlock_t
id|ip6_ra_lock
op_assign
id|RW_LOCK_UNLOCKED
suffix:semicolon
DECL|function|ip6_ra_control
r_int
id|ip6_ra_control
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_int
id|sel
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
(brace
r_struct
id|ip6_ra_chain
op_star
id|ra
comma
op_star
id|new_ra
comma
op_star
op_star
id|rap
suffix:semicolon
multiline_comment|/* RA packet may be delivered ONLY to IPPROTO_RAW socket */
r_if
c_cond
(paren
id|sk-&gt;sk_type
op_ne
id|SOCK_RAW
op_logical_or
id|inet_sk
c_func
(paren
id|sk
)paren
op_member_access_from_pointer
id|num
op_ne
id|IPPROTO_RAW
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|new_ra
op_assign
(paren
id|sel
op_ge
l_int|0
)paren
ques
c_cond
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|new_ra
)paren
comma
id|GFP_KERNEL
)paren
suffix:colon
l_int|NULL
suffix:semicolon
id|write_lock_bh
c_func
(paren
op_amp
id|ip6_ra_lock
)paren
suffix:semicolon
r_for
c_loop
(paren
id|rap
op_assign
op_amp
id|ip6_ra_chain
suffix:semicolon
(paren
id|ra
op_assign
op_star
id|rap
)paren
op_ne
l_int|NULL
suffix:semicolon
id|rap
op_assign
op_amp
id|ra-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|ra-&gt;sk
op_eq
id|sk
)paren
(brace
r_if
c_cond
(paren
id|sel
op_ge
l_int|0
)paren
(brace
id|write_unlock_bh
c_func
(paren
op_amp
id|ip6_ra_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|new_ra
)paren
id|kfree
c_func
(paren
id|new_ra
)paren
suffix:semicolon
r_return
op_minus
id|EADDRINUSE
suffix:semicolon
)brace
op_star
id|rap
op_assign
id|ra-&gt;next
suffix:semicolon
id|write_unlock_bh
c_func
(paren
op_amp
id|ip6_ra_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ra-&gt;destructor
)paren
id|ra
op_member_access_from_pointer
id|destructor
c_func
(paren
id|sk
)paren
suffix:semicolon
id|sock_put
c_func
(paren
id|sk
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|ra
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|new_ra
op_eq
l_int|NULL
)paren
(brace
id|write_unlock_bh
c_func
(paren
op_amp
id|ip6_ra_lock
)paren
suffix:semicolon
r_return
op_minus
id|ENOBUFS
suffix:semicolon
)brace
id|new_ra-&gt;sk
op_assign
id|sk
suffix:semicolon
id|new_ra-&gt;sel
op_assign
id|sel
suffix:semicolon
id|new_ra-&gt;destructor
op_assign
id|destructor
suffix:semicolon
id|new_ra-&gt;next
op_assign
id|ra
suffix:semicolon
op_star
id|rap
op_assign
id|new_ra
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
id|ip6_ra_lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_extern
r_int
id|ip6_mc_source
c_func
(paren
r_int
id|add
comma
r_int
id|omode
comma
r_struct
id|sock
op_star
id|sk
comma
r_struct
id|group_source_req
op_star
id|pgsr
)paren
suffix:semicolon
r_extern
r_int
id|ip6_mc_msfilter
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_struct
id|group_filter
op_star
id|gsf
)paren
suffix:semicolon
r_extern
r_int
id|ip6_mc_msfget
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_struct
id|group_filter
op_star
id|gsf
comma
r_struct
id|group_filter
op_star
id|optval
comma
r_int
op_star
id|optlen
)paren
suffix:semicolon
DECL|function|ipv6_setsockopt
r_int
id|ipv6_setsockopt
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
r_int
id|val
comma
id|valbool
suffix:semicolon
r_int
id|retv
op_assign
op_minus
id|ENOPROTOOPT
suffix:semicolon
r_if
c_cond
(paren
id|level
op_eq
id|SOL_IP
op_logical_and
id|sk-&gt;sk_type
op_ne
id|SOCK_RAW
)paren
r_return
id|udp_prot
dot
id|setsockopt
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
r_if
c_cond
(paren
id|level
op_ne
id|SOL_IPV6
)paren
(brace
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|optval
op_eq
l_int|NULL
)paren
id|val
op_assign
l_int|0
suffix:semicolon
r_else
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
id|valbool
op_assign
(paren
id|val
op_ne
l_int|0
)paren
suffix:semicolon
id|lock_sock
c_func
(paren
id|sk
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|optname
)paren
(brace
r_case
id|IPV6_ADDRFORM
suffix:colon
r_if
c_cond
(paren
id|val
op_eq
id|PF_INET
)paren
(brace
r_struct
id|ipv6_txoptions
op_star
id|opt
suffix:semicolon
r_struct
id|sk_buff
op_star
id|pktopt
suffix:semicolon
r_if
c_cond
(paren
id|sk-&gt;sk_protocol
op_ne
id|IPPROTO_UDP
op_logical_and
id|sk-&gt;sk_protocol
op_ne
id|IPPROTO_TCP
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|sk-&gt;sk_state
op_ne
id|TCP_ESTABLISHED
)paren
(brace
id|retv
op_assign
op_minus
id|ENOTCONN
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ipv6_only_sock
c_func
(paren
id|sk
)paren
op_logical_or
op_logical_neg
(paren
id|ipv6_addr_type
c_func
(paren
op_amp
id|np-&gt;daddr
)paren
op_amp
id|IPV6_ADDR_MAPPED
)paren
)paren
(brace
id|retv
op_assign
op_minus
id|EADDRNOTAVAIL
suffix:semicolon
r_break
suffix:semicolon
)brace
id|fl6_free_socklist
c_func
(paren
id|sk
)paren
suffix:semicolon
id|ipv6_sock_mc_close
c_func
(paren
id|sk
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sk-&gt;sk_protocol
op_eq
id|IPPROTO_TCP
)paren
(brace
r_struct
id|tcp_opt
op_star
id|tp
op_assign
id|tcp_sk
c_func
(paren
id|sk
)paren
suffix:semicolon
id|local_bh_disable
c_func
(paren
)paren
suffix:semicolon
id|sock_prot_dec_use
c_func
(paren
id|sk-&gt;sk_prot
)paren
suffix:semicolon
id|sock_prot_inc_use
c_func
(paren
op_amp
id|tcp_prot
)paren
suffix:semicolon
id|local_bh_enable
c_func
(paren
)paren
suffix:semicolon
id|sk-&gt;sk_prot
op_assign
op_amp
id|tcp_prot
suffix:semicolon
id|tp-&gt;af_specific
op_assign
op_amp
id|ipv4_specific
suffix:semicolon
id|sk-&gt;sk_socket-&gt;ops
op_assign
op_amp
id|inet_stream_ops
suffix:semicolon
id|sk-&gt;sk_family
op_assign
id|PF_INET
suffix:semicolon
id|tcp_sync_mss
c_func
(paren
id|sk
comma
id|tp-&gt;pmtu_cookie
)paren
suffix:semicolon
)brace
r_else
(brace
id|local_bh_disable
c_func
(paren
)paren
suffix:semicolon
id|sock_prot_dec_use
c_func
(paren
id|sk-&gt;sk_prot
)paren
suffix:semicolon
id|sock_prot_inc_use
c_func
(paren
op_amp
id|udp_prot
)paren
suffix:semicolon
id|local_bh_enable
c_func
(paren
)paren
suffix:semicolon
id|sk-&gt;sk_prot
op_assign
op_amp
id|udp_prot
suffix:semicolon
id|sk-&gt;sk_socket-&gt;ops
op_assign
op_amp
id|inet_dgram_ops
suffix:semicolon
id|sk-&gt;sk_family
op_assign
id|PF_INET
suffix:semicolon
)brace
id|opt
op_assign
id|xchg
c_func
(paren
op_amp
id|np-&gt;opt
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|opt
)paren
id|sock_kfree_s
c_func
(paren
id|sk
comma
id|opt
comma
id|opt-&gt;tot_len
)paren
suffix:semicolon
id|pktopt
op_assign
id|xchg
c_func
(paren
op_amp
id|np-&gt;pktoptions
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pktopt
)paren
id|kfree_skb
c_func
(paren
id|pktopt
)paren
suffix:semicolon
id|sk-&gt;sk_destruct
op_assign
id|inet_sock_destruct
suffix:semicolon
macro_line|#ifdef INET_REFCNT_DEBUG
id|atomic_dec
c_func
(paren
op_amp
id|inet6_sock_nr
)paren
suffix:semicolon
macro_line|#endif
id|module_put
c_func
(paren
id|THIS_MODULE
)paren
suffix:semicolon
id|retv
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
r_goto
id|e_inval
suffix:semicolon
r_case
id|IPV6_V6ONLY
suffix:colon
r_if
c_cond
(paren
id|inet_sk
c_func
(paren
id|sk
)paren
op_member_access_from_pointer
id|num
)paren
r_goto
id|e_inval
suffix:semicolon
id|np-&gt;ipv6only
op_assign
id|valbool
suffix:semicolon
id|retv
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IPV6_PKTINFO
suffix:colon
id|np-&gt;rxopt.bits.rxinfo
op_assign
id|valbool
suffix:semicolon
id|retv
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IPV6_HOPLIMIT
suffix:colon
id|np-&gt;rxopt.bits.rxhlim
op_assign
id|valbool
suffix:semicolon
id|retv
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IPV6_RTHDR
suffix:colon
r_if
c_cond
(paren
id|val
template_param
l_int|2
)paren
r_goto
id|e_inval
suffix:semicolon
id|np-&gt;rxopt.bits.srcrt
op_assign
id|val
suffix:semicolon
id|retv
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IPV6_HOPOPTS
suffix:colon
id|np-&gt;rxopt.bits.hopopts
op_assign
id|valbool
suffix:semicolon
id|retv
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IPV6_AUTHHDR
suffix:colon
id|np-&gt;rxopt.bits.authhdr
op_assign
id|valbool
suffix:semicolon
id|retv
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IPV6_DSTOPTS
suffix:colon
id|np-&gt;rxopt.bits.dstopts
op_assign
id|valbool
suffix:semicolon
id|retv
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IPV6_FLOWINFO
suffix:colon
id|np-&gt;rxopt.bits.rxflow
op_assign
id|valbool
suffix:semicolon
id|retv
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IPV6_PKTOPTIONS
suffix:colon
(brace
r_struct
id|ipv6_txoptions
op_star
id|opt
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|msghdr
id|msg
suffix:semicolon
r_struct
id|flowi
id|fl
suffix:semicolon
r_int
id|junk
suffix:semicolon
id|fl.fl6_flowlabel
op_assign
l_int|0
suffix:semicolon
id|fl.oif
op_assign
id|sk-&gt;sk_bound_dev_if
suffix:semicolon
r_if
c_cond
(paren
id|optlen
op_eq
l_int|0
)paren
r_goto
id|update
suffix:semicolon
multiline_comment|/* 1K is probably excessive&n;&t;&t; * 1K is surely not enough, 2K per standard header is 16K.&n;&t;&t; */
id|retv
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|optlen
OG
l_int|64
op_star
l_int|1024
)paren
r_break
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
id|optlen
comma
id|GFP_KERNEL
)paren
suffix:semicolon
id|retv
op_assign
op_minus
id|ENOBUFS
suffix:semicolon
r_if
c_cond
(paren
id|opt
op_eq
l_int|NULL
)paren
r_break
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
id|optlen
suffix:semicolon
id|retv
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|opt
op_plus
l_int|1
comma
id|optval
comma
id|optlen
)paren
)paren
r_goto
id|done
suffix:semicolon
id|msg.msg_controllen
op_assign
id|optlen
suffix:semicolon
id|msg.msg_control
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
id|retv
op_assign
id|datagram_send_ctl
c_func
(paren
op_amp
id|msg
comma
op_amp
id|fl
comma
id|opt
comma
op_amp
id|junk
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retv
)paren
r_goto
id|done
suffix:semicolon
id|update
suffix:colon
id|retv
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|sk-&gt;sk_type
op_eq
id|SOCK_STREAM
)paren
(brace
r_if
c_cond
(paren
id|opt
)paren
(brace
r_struct
id|tcp_opt
op_star
id|tp
op_assign
id|tcp_sk
c_func
(paren
id|sk
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
(paren
l_int|1
op_lshift
id|sk-&gt;sk_state
)paren
op_amp
(paren
id|TCPF_LISTEN
op_or
id|TCPF_CLOSE
)paren
)paren
op_logical_and
id|inet_sk
c_func
(paren
id|sk
)paren
op_member_access_from_pointer
id|daddr
op_ne
id|LOOPBACK4_IPV6
)paren
(brace
id|tp-&gt;ext_header_len
op_assign
id|opt-&gt;opt_flen
op_plus
id|opt-&gt;opt_nflen
suffix:semicolon
id|tcp_sync_mss
c_func
(paren
id|sk
comma
id|tp-&gt;pmtu_cookie
)paren
suffix:semicolon
)brace
)brace
id|opt
op_assign
id|xchg
c_func
(paren
op_amp
id|np-&gt;opt
comma
id|opt
)paren
suffix:semicolon
id|sk_dst_reset
c_func
(paren
id|sk
)paren
suffix:semicolon
)brace
r_else
(brace
id|write_lock
c_func
(paren
op_amp
id|sk-&gt;sk_dst_lock
)paren
suffix:semicolon
id|opt
op_assign
id|xchg
c_func
(paren
op_amp
id|np-&gt;opt
comma
id|opt
)paren
suffix:semicolon
id|write_unlock
c_func
(paren
op_amp
id|sk-&gt;sk_dst_lock
)paren
suffix:semicolon
id|sk_dst_reset
c_func
(paren
id|sk
)paren
suffix:semicolon
)brace
id|done
suffix:colon
r_if
c_cond
(paren
id|opt
)paren
id|sock_kfree_s
c_func
(paren
id|sk
comma
id|opt
comma
id|opt-&gt;tot_len
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|IPV6_UNICAST_HOPS
suffix:colon
r_if
c_cond
(paren
id|val
OG
l_int|255
op_logical_or
id|val
OL
op_minus
l_int|1
)paren
r_goto
id|e_inval
suffix:semicolon
id|np-&gt;hop_limit
op_assign
id|val
suffix:semicolon
id|retv
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IPV6_MULTICAST_HOPS
suffix:colon
r_if
c_cond
(paren
id|sk-&gt;sk_type
op_eq
id|SOCK_STREAM
)paren
r_goto
id|e_inval
suffix:semicolon
r_if
c_cond
(paren
id|val
OG
l_int|255
op_logical_or
id|val
OL
op_minus
l_int|1
)paren
r_goto
id|e_inval
suffix:semicolon
id|np-&gt;mcast_hops
op_assign
id|val
suffix:semicolon
id|retv
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IPV6_MULTICAST_LOOP
suffix:colon
id|np-&gt;mc_loop
op_assign
id|valbool
suffix:semicolon
id|retv
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IPV6_MULTICAST_IF
suffix:colon
r_if
c_cond
(paren
id|sk-&gt;sk_type
op_eq
id|SOCK_STREAM
)paren
r_goto
id|e_inval
suffix:semicolon
r_if
c_cond
(paren
id|sk-&gt;sk_bound_dev_if
op_logical_and
id|sk-&gt;sk_bound_dev_if
op_ne
id|val
)paren
r_goto
id|e_inval
suffix:semicolon
r_if
c_cond
(paren
id|__dev_get_by_index
c_func
(paren
id|val
)paren
op_eq
l_int|NULL
)paren
(brace
id|retv
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_break
suffix:semicolon
)brace
id|np-&gt;mcast_oif
op_assign
id|val
suffix:semicolon
id|retv
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IPV6_ADD_MEMBERSHIP
suffix:colon
r_case
id|IPV6_DROP_MEMBERSHIP
suffix:colon
(brace
r_struct
id|ipv6_mreq
id|mreq
suffix:semicolon
id|retv
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|mreq
comma
id|optval
comma
r_sizeof
(paren
r_struct
id|ipv6_mreq
)paren
)paren
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|optname
op_eq
id|IPV6_ADD_MEMBERSHIP
)paren
id|retv
op_assign
id|ipv6_sock_mc_join
c_func
(paren
id|sk
comma
id|mreq.ipv6mr_ifindex
comma
op_amp
id|mreq.ipv6mr_multiaddr
)paren
suffix:semicolon
r_else
id|retv
op_assign
id|ipv6_sock_mc_drop
c_func
(paren
id|sk
comma
id|mreq.ipv6mr_ifindex
comma
op_amp
id|mreq.ipv6mr_multiaddr
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|IPV6_JOIN_ANYCAST
suffix:colon
r_case
id|IPV6_LEAVE_ANYCAST
suffix:colon
(brace
r_struct
id|ipv6_mreq
id|mreq
suffix:semicolon
r_if
c_cond
(paren
id|optlen
op_ne
r_sizeof
(paren
r_struct
id|ipv6_mreq
)paren
)paren
r_goto
id|e_inval
suffix:semicolon
id|retv
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|mreq
comma
id|optval
comma
r_sizeof
(paren
r_struct
id|ipv6_mreq
)paren
)paren
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|optname
op_eq
id|IPV6_JOIN_ANYCAST
)paren
id|retv
op_assign
id|ipv6_sock_ac_join
c_func
(paren
id|sk
comma
id|mreq.ipv6mr_ifindex
comma
op_amp
id|mreq.ipv6mr_acaddr
)paren
suffix:semicolon
r_else
id|retv
op_assign
id|ipv6_sock_ac_drop
c_func
(paren
id|sk
comma
id|mreq.ipv6mr_ifindex
comma
op_amp
id|mreq.ipv6mr_acaddr
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|MCAST_JOIN_GROUP
suffix:colon
r_case
id|MCAST_LEAVE_GROUP
suffix:colon
(brace
r_struct
id|group_req
id|greq
suffix:semicolon
r_struct
id|sockaddr_in6
op_star
id|psin6
suffix:semicolon
id|retv
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|greq
comma
id|optval
comma
r_sizeof
(paren
r_struct
id|group_req
)paren
)paren
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|greq.gr_group.ss_family
op_ne
id|AF_INET6
)paren
(brace
id|retv
op_assign
op_minus
id|EADDRNOTAVAIL
suffix:semicolon
r_break
suffix:semicolon
)brace
id|psin6
op_assign
(paren
r_struct
id|sockaddr_in6
op_star
)paren
op_amp
id|greq.gr_group
suffix:semicolon
r_if
c_cond
(paren
id|optname
op_eq
id|MCAST_JOIN_GROUP
)paren
id|retv
op_assign
id|ipv6_sock_mc_join
c_func
(paren
id|sk
comma
id|greq.gr_interface
comma
op_amp
id|psin6-&gt;sin6_addr
)paren
suffix:semicolon
r_else
id|retv
op_assign
id|ipv6_sock_mc_drop
c_func
(paren
id|sk
comma
id|greq.gr_interface
comma
op_amp
id|psin6-&gt;sin6_addr
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|MCAST_JOIN_SOURCE_GROUP
suffix:colon
r_case
id|MCAST_LEAVE_SOURCE_GROUP
suffix:colon
r_case
id|MCAST_BLOCK_SOURCE
suffix:colon
r_case
id|MCAST_UNBLOCK_SOURCE
suffix:colon
(brace
r_struct
id|group_source_req
id|greqs
suffix:semicolon
r_int
id|omode
comma
id|add
suffix:semicolon
r_if
c_cond
(paren
id|optlen
op_ne
r_sizeof
(paren
r_struct
id|group_source_req
)paren
)paren
r_goto
id|e_inval
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|greqs
comma
id|optval
comma
r_sizeof
(paren
id|greqs
)paren
)paren
)paren
(brace
id|retv
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|greqs.gsr_group.ss_family
op_ne
id|AF_INET6
op_logical_or
id|greqs.gsr_source.ss_family
op_ne
id|AF_INET6
)paren
(brace
id|retv
op_assign
op_minus
id|EADDRNOTAVAIL
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|optname
op_eq
id|MCAST_BLOCK_SOURCE
)paren
(brace
id|omode
op_assign
id|MCAST_EXCLUDE
suffix:semicolon
id|add
op_assign
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|optname
op_eq
id|MCAST_UNBLOCK_SOURCE
)paren
(brace
id|omode
op_assign
id|MCAST_EXCLUDE
suffix:semicolon
id|add
op_assign
l_int|0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|optname
op_eq
id|MCAST_JOIN_SOURCE_GROUP
)paren
(brace
r_struct
id|sockaddr_in6
op_star
id|psin6
suffix:semicolon
id|psin6
op_assign
(paren
r_struct
id|sockaddr_in6
op_star
)paren
op_amp
id|greqs.gsr_group
suffix:semicolon
id|retv
op_assign
id|ipv6_sock_mc_join
c_func
(paren
id|sk
comma
id|greqs.gsr_interface
comma
op_amp
id|psin6-&gt;sin6_addr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retv
)paren
r_break
suffix:semicolon
id|omode
op_assign
id|MCAST_INCLUDE
suffix:semicolon
id|add
op_assign
l_int|1
suffix:semicolon
)brace
r_else
multiline_comment|/*IP_DROP_SOURCE_MEMBERSHIP */
(brace
id|omode
op_assign
id|MCAST_INCLUDE
suffix:semicolon
id|add
op_assign
l_int|0
suffix:semicolon
)brace
id|retv
op_assign
id|ip6_mc_source
c_func
(paren
id|add
comma
id|omode
comma
id|sk
comma
op_amp
id|greqs
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|MCAST_MSFILTER
suffix:colon
(brace
r_struct
id|group_filter
op_star
id|gsf
suffix:semicolon
r_if
c_cond
(paren
id|optlen
OL
id|GROUP_FILTER_SIZE
c_func
(paren
l_int|0
)paren
)paren
r_goto
id|e_inval
suffix:semicolon
id|gsf
op_assign
(paren
r_struct
id|group_filter
op_star
)paren
id|kmalloc
c_func
(paren
id|optlen
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|gsf
op_eq
l_int|0
)paren
(brace
id|retv
op_assign
op_minus
id|ENOBUFS
suffix:semicolon
r_break
suffix:semicolon
)brace
id|retv
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|gsf
comma
id|optval
comma
id|optlen
)paren
)paren
(brace
id|kfree
c_func
(paren
id|gsf
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|retv
op_assign
id|ip6_mc_msfilter
c_func
(paren
id|sk
comma
id|gsf
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|gsf
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|IPV6_ROUTER_ALERT
suffix:colon
id|retv
op_assign
id|ip6_ra_control
c_func
(paren
id|sk
comma
id|val
comma
l_int|NULL
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IPV6_MTU_DISCOVER
suffix:colon
r_if
c_cond
(paren
id|val
l_int|2
)paren
r_goto
id|e_inval
suffix:semicolon
id|np-&gt;pmtudisc
op_assign
id|val
suffix:semicolon
id|retv
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IPV6_MTU
suffix:colon
r_if
c_cond
(paren
id|val
op_logical_and
id|val
OL
id|IPV6_MIN_MTU
)paren
r_goto
id|e_inval
suffix:semicolon
id|np-&gt;frag_size
op_assign
id|val
suffix:semicolon
id|retv
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IPV6_RECVERR
suffix:colon
id|np-&gt;recverr
op_assign
id|valbool
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|val
)paren
id|skb_queue_purge
c_func
(paren
op_amp
id|sk-&gt;sk_error_queue
)paren
suffix:semicolon
id|retv
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IPV6_FLOWINFO_SEND
suffix:colon
id|np-&gt;sndflow
op_assign
id|valbool
suffix:semicolon
id|retv
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IPV6_FLOWLABEL_MGR
suffix:colon
id|retv
op_assign
id|ipv6_flowlabel_opt
c_func
(paren
id|sk
comma
id|optval
comma
id|optlen
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IPV6_IPSEC_POLICY
suffix:colon
r_case
id|IPV6_XFRM_POLICY
suffix:colon
id|retv
op_assign
id|xfrm_user_policy
c_func
(paren
id|sk
comma
id|optname
comma
id|optval
comma
id|optlen
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#ifdef CONFIG_NETFILTER
r_default
suffix:colon
id|retv
op_assign
id|nf_setsockopt
c_func
(paren
id|sk
comma
id|PF_INET6
comma
id|optname
comma
id|optval
comma
id|optlen
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
)brace
id|release_sock
c_func
(paren
id|sk
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|retv
suffix:semicolon
id|e_inval
suffix:colon
id|release_sock
c_func
(paren
id|sk
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|function|ipv6_getsockopt
r_int
id|ipv6_getsockopt
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
r_int
id|len
suffix:semicolon
r_int
id|val
suffix:semicolon
r_if
c_cond
(paren
id|level
op_eq
id|SOL_IP
op_logical_and
id|sk-&gt;sk_type
op_ne
id|SOCK_RAW
)paren
r_return
id|udp_prot
dot
id|getsockopt
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
r_if
c_cond
(paren
id|level
op_ne
id|SOL_IPV6
)paren
(brace
r_return
op_minus
id|ENOPROTOOPT
suffix:semicolon
)brace
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
id|IPV6_ADDRFORM
suffix:colon
r_if
c_cond
(paren
id|sk-&gt;sk_protocol
op_ne
id|IPPROTO_UDP
op_logical_and
id|sk-&gt;sk_protocol
op_ne
id|IPPROTO_TCP
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|sk-&gt;sk_state
op_ne
id|TCP_ESTABLISHED
)paren
r_return
op_minus
id|ENOTCONN
suffix:semicolon
id|val
op_assign
id|sk-&gt;sk_family
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MCAST_MSFILTER
suffix:colon
(brace
r_struct
id|group_filter
id|gsf
suffix:semicolon
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
id|GROUP_FILTER_SIZE
c_func
(paren
l_int|0
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|gsf
comma
id|optval
comma
id|GROUP_FILTER_SIZE
c_func
(paren
l_int|0
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|lock_sock
c_func
(paren
id|sk
)paren
suffix:semicolon
id|err
op_assign
id|ip6_mc_msfget
c_func
(paren
id|sk
comma
op_amp
id|gsf
comma
(paren
r_struct
id|group_filter
op_star
)paren
id|optval
comma
id|optlen
)paren
suffix:semicolon
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
r_case
id|IPV6_PKTOPTIONS
suffix:colon
(brace
r_struct
id|msghdr
id|msg
suffix:semicolon
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
r_if
c_cond
(paren
id|sk-&gt;sk_type
op_ne
id|SOCK_STREAM
)paren
r_return
op_minus
id|ENOPROTOOPT
suffix:semicolon
id|msg.msg_control
op_assign
id|optval
suffix:semicolon
id|msg.msg_controllen
op_assign
id|len
suffix:semicolon
id|msg.msg_flags
op_assign
l_int|0
suffix:semicolon
id|lock_sock
c_func
(paren
id|sk
)paren
suffix:semicolon
id|skb
op_assign
id|np-&gt;pktoptions
suffix:semicolon
r_if
c_cond
(paren
id|skb
)paren
id|atomic_inc
c_func
(paren
op_amp
id|skb-&gt;users
)paren
suffix:semicolon
id|release_sock
c_func
(paren
id|sk
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb
)paren
(brace
r_int
id|err
op_assign
id|datagram_recv_ctl
c_func
(paren
id|sk
comma
op_amp
id|msg
comma
id|skb
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
id|err
)paren
r_return
id|err
suffix:semicolon
)brace
r_else
(brace
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
id|np-&gt;mcast_oif
suffix:semicolon
id|ipv6_addr_copy
c_func
(paren
op_amp
id|src_info.ipi6_addr
comma
op_amp
id|np-&gt;daddr
)paren
suffix:semicolon
id|put_cmsg
c_func
(paren
op_amp
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
id|np-&gt;mcast_hops
suffix:semicolon
id|put_cmsg
c_func
(paren
op_amp
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
)brace
id|len
op_sub_assign
id|msg.msg_controllen
suffix:semicolon
r_return
id|put_user
c_func
(paren
id|len
comma
id|optlen
)paren
suffix:semicolon
)brace
r_case
id|IPV6_MTU
suffix:colon
(brace
r_struct
id|dst_entry
op_star
id|dst
suffix:semicolon
id|val
op_assign
l_int|0
suffix:semicolon
id|lock_sock
c_func
(paren
id|sk
)paren
suffix:semicolon
id|dst
op_assign
id|sk_dst_get
c_func
(paren
id|sk
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dst
)paren
(brace
id|val
op_assign
id|dst_pmtu
c_func
(paren
id|dst
)paren
op_minus
id|dst-&gt;header_len
suffix:semicolon
id|dst_release
c_func
(paren
id|dst
)paren
suffix:semicolon
)brace
id|release_sock
c_func
(paren
id|sk
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|val
)paren
r_return
op_minus
id|ENOTCONN
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|IPV6_V6ONLY
suffix:colon
id|val
op_assign
id|np-&gt;ipv6only
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IPV6_PKTINFO
suffix:colon
id|val
op_assign
id|np-&gt;rxopt.bits.rxinfo
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IPV6_HOPLIMIT
suffix:colon
id|val
op_assign
id|np-&gt;rxopt.bits.rxhlim
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IPV6_RTHDR
suffix:colon
id|val
op_assign
id|np-&gt;rxopt.bits.srcrt
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IPV6_HOPOPTS
suffix:colon
id|val
op_assign
id|np-&gt;rxopt.bits.hopopts
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IPV6_AUTHHDR
suffix:colon
id|val
op_assign
id|np-&gt;rxopt.bits.authhdr
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IPV6_DSTOPTS
suffix:colon
id|val
op_assign
id|np-&gt;rxopt.bits.dstopts
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IPV6_FLOWINFO
suffix:colon
id|val
op_assign
id|np-&gt;rxopt.bits.rxflow
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IPV6_UNICAST_HOPS
suffix:colon
id|val
op_assign
id|np-&gt;hop_limit
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IPV6_MULTICAST_HOPS
suffix:colon
id|val
op_assign
id|np-&gt;mcast_hops
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IPV6_MULTICAST_LOOP
suffix:colon
id|val
op_assign
id|np-&gt;mc_loop
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IPV6_MULTICAST_IF
suffix:colon
id|val
op_assign
id|np-&gt;mcast_oif
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IPV6_MTU_DISCOVER
suffix:colon
id|val
op_assign
id|np-&gt;pmtudisc
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IPV6_RECVERR
suffix:colon
id|val
op_assign
id|np-&gt;recverr
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IPV6_FLOWINFO_SEND
suffix:colon
id|val
op_assign
id|np-&gt;sndflow
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
macro_line|#ifdef CONFIG_NETFILTER
id|lock_sock
c_func
(paren
id|sk
)paren
suffix:semicolon
id|val
op_assign
id|nf_getsockopt
c_func
(paren
id|sk
comma
id|PF_INET6
comma
id|optname
comma
id|optval
comma
op_amp
id|len
)paren
suffix:semicolon
id|release_sock
c_func
(paren
id|sk
)paren
suffix:semicolon
r_if
c_cond
(paren
id|val
op_ge
l_int|0
)paren
id|val
op_assign
id|put_user
c_func
(paren
id|len
comma
id|optlen
)paren
suffix:semicolon
r_return
id|val
suffix:semicolon
macro_line|#else
r_return
op_minus
id|EINVAL
suffix:semicolon
macro_line|#endif
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
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
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
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#if defined(MODULE) &amp;&amp; defined(CONFIG_SYSCTL)
multiline_comment|/*&n; *&t;sysctl registration functions defined in sysctl_net_ipv6.c&n; */
r_extern
r_void
id|ipv6_sysctl_register
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|ipv6_sysctl_unregister
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
DECL|function|ipv6_packet_init
r_void
id|__init
id|ipv6_packet_init
c_func
(paren
r_void
)paren
(brace
id|dev_add_pack
c_func
(paren
op_amp
id|ipv6_packet_type
)paren
suffix:semicolon
)brace
DECL|function|ipv6_netdev_notif_init
r_void
id|__init
id|ipv6_netdev_notif_init
c_func
(paren
r_void
)paren
(brace
id|register_netdevice_notifier
c_func
(paren
op_amp
id|ipv6_dev_notf
)paren
suffix:semicolon
)brace
macro_line|#ifdef MODULE
DECL|function|ipv6_packet_cleanup
r_void
id|ipv6_packet_cleanup
c_func
(paren
r_void
)paren
(brace
id|dev_remove_pack
c_func
(paren
op_amp
id|ipv6_packet_type
)paren
suffix:semicolon
)brace
DECL|function|ipv6_netdev_notif_cleanup
r_void
id|ipv6_netdev_notif_cleanup
c_func
(paren
r_void
)paren
(brace
id|unregister_netdevice_notifier
c_func
(paren
op_amp
id|ipv6_dev_notf
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
