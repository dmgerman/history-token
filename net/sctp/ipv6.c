multiline_comment|/* SCTP kernel reference Implementation&n; * Copyright (c) 2001 Nokia, Inc.&n; * Copyright (c) 2001 La Monte H.P. Yarroll&n; * Copyright (c) 2002 International Business Machines, Corp.&n; *&n; * This file is part of the SCTP kernel reference Implementation&n; *&n; * SCTP over IPv6.&n; *&n; * The SCTP reference implementation is free software;&n; * you can redistribute it and/or modify it under the terms of&n; * the GNU General Public License as published by&n; * the Free Software Foundation; either version 2, or (at your option)&n; * any later version.&n; *&n; * The SCTP reference implementation is distributed in the hope that it&n; * will be useful, but WITHOUT ANY WARRANTY; without even the implied&n; *                 ************************&n; * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; * See the GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with GNU CC; see the file COPYING.  If not, write to&n; * the Free Software Foundation, 59 Temple Place - Suite 330,&n; * Boston, MA 02111-1307, USA.&n; *&n; * Please send any bug reports or fixes you make to the&n; * email address(es):&n; *    lksctp developers &lt;lksctp-developers@lists.sourceforge.net&gt;&n; *&n; * Or submit a bug report through the following website:&n; *    http://www.sf.net/projects/lksctp&n; *&n; * Written or modified by:&n; *    Le Yanqun             &lt;yanqun.le@nokia.com&gt;&n; *    Hui Huang&t;&t;    &lt;hui.huang@nokia.com&gt;&n; *    La Monte H.P. Yarroll &lt;piggy@acm.org&gt;&n; *    Sridhar Samudrala&t;    &lt;sri@us.ibm.com&gt;&n; *    Jon Grimm             &lt;jgrimm@us.ibm.com&gt;&n; *&n; * Based on:&n; *      linux/net/ipv6/tcp_ipv6.c&n; *&n; * Any bugs reported given to us we will try to fix... any fixes shared will&n; * be incorporated into the next SCTP release.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/sockios.h&gt;
macro_line|#include &lt;linux/net.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/in6.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/ipsec.h&gt;
macro_line|#include &lt;linux/ipv6.h&gt;
macro_line|#include &lt;linux/icmpv6.h&gt;
macro_line|#include &lt;linux/random.h&gt;
macro_line|#include &lt;net/protocol.h&gt;
macro_line|#include &lt;net/tcp.h&gt;
macro_line|#include &lt;net/ndisc.h&gt;
macro_line|#include &lt;net/ipv6.h&gt;
macro_line|#include &lt;net/transp_v6.h&gt;
macro_line|#include &lt;net/addrconf.h&gt;
macro_line|#include &lt;net/ip6_route.h&gt;
macro_line|#include &lt;net/inet_common.h&gt;
macro_line|#include &lt;net/inet_ecn.h&gt;
macro_line|#include &lt;net/sctp/sctp.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
r_extern
r_struct
id|notifier_block
id|sctp_inetaddr_notifier
suffix:semicolon
multiline_comment|/* FIXME: This macro needs to be moved to a common header file. */
DECL|macro|NIP6
mdefine_line|#define NIP6(addr) &bslash;&n;        ntohs((addr)-&gt;s6_addr16[0]), &bslash;&n;        ntohs((addr)-&gt;s6_addr16[1]), &bslash;&n;        ntohs((addr)-&gt;s6_addr16[2]), &bslash;&n;        ntohs((addr)-&gt;s6_addr16[3]), &bslash;&n;        ntohs((addr)-&gt;s6_addr16[4]), &bslash;&n;        ntohs((addr)-&gt;s6_addr16[5]), &bslash;&n;        ntohs((addr)-&gt;s6_addr16[6]), &bslash;&n;        ntohs((addr)-&gt;s6_addr16[7])
multiline_comment|/* FIXME: Comments. */
DECL|function|sctp_v6_err
r_static
r_inline
r_void
id|sctp_v6_err
c_func
(paren
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
id|__u32
id|info
)paren
(brace
multiline_comment|/* BUG.  WRITE ME.  */
)brace
multiline_comment|/* Based on tcp_v6_xmit() in tcp_ipv6.c. */
DECL|function|sctp_v6_xmit
r_static
r_inline
r_int
id|sctp_v6_xmit
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|sctp_transport
op_star
id|transport
comma
r_int
id|ipfragok
)paren
(brace
r_struct
id|sock
op_star
id|sk
op_assign
id|skb-&gt;sk
suffix:semicolon
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
id|flowi
id|fl
suffix:semicolon
r_struct
id|dst_entry
op_star
id|dst
op_assign
id|skb-&gt;dst
suffix:semicolon
r_struct
id|rt6_info
op_star
id|rt6
op_assign
(paren
r_struct
id|rt6_info
op_star
)paren
id|dst
suffix:semicolon
id|fl.proto
op_assign
id|sk-&gt;protocol
suffix:semicolon
multiline_comment|/* Fill in the dest address from the route entry passed with the skb&n;&t; * and the source address from the transport.&n;&t; */
id|fl.fl6_dst
op_assign
op_amp
id|rt6-&gt;rt6i_dst.addr
suffix:semicolon
id|fl.fl6_src
op_assign
op_amp
id|transport-&gt;saddr.v6.sin6_addr
suffix:semicolon
id|fl.fl6_flowlabel
op_assign
id|np-&gt;flow_label
suffix:semicolon
id|IP6_ECN_flow_xmit
c_func
(paren
id|sk
comma
id|fl.fl6_flowlabel
)paren
suffix:semicolon
id|fl.oif
op_assign
id|sk-&gt;bound_dev_if
suffix:semicolon
id|fl.uli_u.ports.sport
op_assign
id|inet_sk
c_func
(paren
id|sk
)paren
op_member_access_from_pointer
id|sport
suffix:semicolon
id|fl.uli_u.ports.dport
op_assign
id|inet_sk
c_func
(paren
id|sk
)paren
op_member_access_from_pointer
id|dport
suffix:semicolon
r_if
c_cond
(paren
id|np-&gt;opt
op_logical_and
id|np-&gt;opt-&gt;srcrt
)paren
(brace
r_struct
id|rt0_hdr
op_star
id|rt0
op_assign
(paren
r_struct
id|rt0_hdr
op_star
)paren
id|np-&gt;opt-&gt;srcrt
suffix:semicolon
id|fl.nl_u.ip6_u.daddr
op_assign
id|rt0-&gt;addr
suffix:semicolon
)brace
id|SCTP_DEBUG_PRINTK
c_func
(paren
l_string|&quot;%s: skb:%p, len:%d, &quot;
l_string|&quot;src:%04x:%04x:%04x:%04x:%04x:%04x:%04x:%04x &quot;
l_string|&quot;dst:%04x:%04x:%04x:%04x:%04x:%04x:%04x:%04x&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|skb
comma
id|skb-&gt;len
comma
id|NIP6
c_func
(paren
id|fl.fl6_src
)paren
comma
id|NIP6
c_func
(paren
id|fl.fl6_dst
)paren
)paren
suffix:semicolon
r_return
id|ip6_xmit
c_func
(paren
id|sk
comma
id|skb
comma
op_amp
id|fl
comma
id|np-&gt;opt
)paren
suffix:semicolon
)brace
multiline_comment|/* Returns the dst cache entry for the given source and destination ip&n; * addresses.&n; */
DECL|function|sctp_v6_get_dst
r_struct
id|dst_entry
op_star
id|sctp_v6_get_dst
c_func
(paren
id|sctp_association_t
op_star
id|asoc
comma
r_union
id|sctp_addr
op_star
id|daddr
comma
r_union
id|sctp_addr
op_star
id|saddr
)paren
(brace
r_struct
id|dst_entry
op_star
id|dst
suffix:semicolon
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
id|ip6_u
op_assign
(brace
dot
id|daddr
op_assign
op_amp
id|daddr-&gt;v6.sin6_addr
comma
)brace
)brace
)brace
suffix:semicolon
id|SCTP_DEBUG_PRINTK
c_func
(paren
l_string|&quot;%s: DST=%04x:%04x:%04x:%04x:%04x:%04x:%04x:%04x &quot;
comma
id|__FUNCTION__
comma
id|NIP6
c_func
(paren
id|fl.fl6_dst
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|saddr
)paren
(brace
id|fl.fl6_src
op_assign
op_amp
id|saddr-&gt;v6.sin6_addr
suffix:semicolon
id|SCTP_DEBUG_PRINTK
c_func
(paren
l_string|&quot;SRC=%04x:%04x:%04x:%04x:%04x:%04x:%04x:%04x - &quot;
comma
id|NIP6
c_func
(paren
id|fl.fl6_src
)paren
)paren
suffix:semicolon
)brace
id|dst
op_assign
id|ip6_route_output
c_func
(paren
l_int|NULL
comma
op_amp
id|fl
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dst
)paren
(brace
r_struct
id|rt6_info
op_star
id|rt
suffix:semicolon
id|rt
op_assign
(paren
r_struct
id|rt6_info
op_star
)paren
id|dst
suffix:semicolon
id|SCTP_DEBUG_PRINTK
c_func
(paren
l_string|&quot;rt6_dst:%04x:%04x:%04x:%04x:%04x:%04x:%04x:%04x &quot;
l_string|&quot;rt6_src:%04x:%04x:%04x:%04x:%04x:%04x:%04x:%04x&bslash;n&quot;
comma
id|NIP6
c_func
(paren
op_amp
id|rt-&gt;rt6i_dst.addr
)paren
comma
id|NIP6
c_func
(paren
op_amp
id|rt-&gt;rt6i_src.addr
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|SCTP_DEBUG_PRINTK
c_func
(paren
l_string|&quot;NO ROUTE&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_return
id|dst
suffix:semicolon
)brace
multiline_comment|/* Returns the number of consecutive initial bits that match in the 2 ipv6&n; * addresses.&n; */
DECL|function|sctp_v6_addr_match_len
r_static
r_inline
r_int
id|sctp_v6_addr_match_len
c_func
(paren
r_union
id|sctp_addr
op_star
id|s1
comma
r_union
id|sctp_addr
op_star
id|s2
)paren
(brace
r_struct
id|in6_addr
op_star
id|a1
op_assign
op_amp
id|s1-&gt;v6.sin6_addr
suffix:semicolon
r_struct
id|in6_addr
op_star
id|a2
op_assign
op_amp
id|s2-&gt;v6.sin6_addr
suffix:semicolon
r_int
id|i
comma
id|j
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
l_int|4
suffix:semicolon
id|i
op_increment
)paren
(brace
id|__u32
id|a1xora2
suffix:semicolon
id|a1xora2
op_assign
id|a1-&gt;s6_addr32
(braket
id|i
)braket
op_xor
id|a2-&gt;s6_addr32
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
(paren
id|j
op_assign
id|fls
c_func
(paren
id|ntohl
c_func
(paren
id|a1xora2
)paren
)paren
)paren
)paren
r_return
(paren
id|i
op_star
l_int|32
op_plus
l_int|32
op_minus
id|j
)paren
suffix:semicolon
)brace
r_return
(paren
id|i
op_star
l_int|32
)paren
suffix:semicolon
)brace
multiline_comment|/* Fills in the source address(saddr) based on the destination address(daddr)&n; * and asoc&squot;s bind address list.&n; */
DECL|function|sctp_v6_get_saddr
r_void
id|sctp_v6_get_saddr
c_func
(paren
id|sctp_association_t
op_star
id|asoc
comma
r_struct
id|dst_entry
op_star
id|dst
comma
r_union
id|sctp_addr
op_star
id|daddr
comma
r_union
id|sctp_addr
op_star
id|saddr
)paren
(brace
id|sctp_bind_addr_t
op_star
id|bp
suffix:semicolon
id|rwlock_t
op_star
id|addr_lock
suffix:semicolon
r_struct
id|sockaddr_storage_list
op_star
id|laddr
suffix:semicolon
r_struct
id|list_head
op_star
id|pos
suffix:semicolon
id|sctp_scope_t
id|scope
suffix:semicolon
r_union
id|sctp_addr
op_star
id|baddr
op_assign
l_int|NULL
suffix:semicolon
id|__u8
id|matchlen
op_assign
l_int|0
suffix:semicolon
id|__u8
id|bmatchlen
suffix:semicolon
id|SCTP_DEBUG_PRINTK
c_func
(paren
l_string|&quot;%s: asoc:%p dst:%p &quot;
l_string|&quot;daddr:%04x:%04x:%04x:%04x:%04x:%04x:%04x:%04x &quot;
comma
id|__FUNCTION__
comma
id|asoc
comma
id|dst
comma
id|NIP6
c_func
(paren
op_amp
id|daddr-&gt;v6.sin6_addr
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|asoc
)paren
(brace
id|ipv6_get_saddr
c_func
(paren
id|dst
comma
op_amp
id|daddr-&gt;v6.sin6_addr
comma
op_amp
id|saddr-&gt;v6.sin6_addr
)paren
suffix:semicolon
id|SCTP_DEBUG_PRINTK
c_func
(paren
l_string|&quot;saddr from ipv6_get_saddr: &quot;
l_string|&quot;%04x:%04x:%04x:%04x:%04x:%04x:%04x:%04x&bslash;n&quot;
comma
id|NIP6
c_func
(paren
op_amp
id|saddr-&gt;v6.sin6_addr
)paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|scope
op_assign
id|sctp_scope
c_func
(paren
id|daddr
)paren
suffix:semicolon
id|bp
op_assign
op_amp
id|asoc-&gt;base.bind_addr
suffix:semicolon
id|addr_lock
op_assign
op_amp
id|asoc-&gt;base.addr_lock
suffix:semicolon
multiline_comment|/* Go through the bind address list and find the best source address&n;&t; * that matches the scope of the destination address.&n;&t; */
id|sctp_read_lock
c_func
(paren
id|addr_lock
)paren
suffix:semicolon
id|list_for_each
c_func
(paren
id|pos
comma
op_amp
id|bp-&gt;address_list
)paren
(brace
id|laddr
op_assign
id|list_entry
c_func
(paren
id|pos
comma
r_struct
id|sockaddr_storage_list
comma
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|laddr-&gt;a.sa.sa_family
op_eq
id|AF_INET6
)paren
op_logical_and
(paren
id|scope
op_le
id|sctp_scope
c_func
(paren
op_amp
id|laddr-&gt;a
)paren
)paren
)paren
(brace
id|bmatchlen
op_assign
id|sctp_v6_addr_match_len
c_func
(paren
id|daddr
comma
op_amp
id|laddr-&gt;a
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|baddr
op_logical_or
(paren
id|matchlen
OL
id|bmatchlen
)paren
)paren
(brace
id|baddr
op_assign
op_amp
id|laddr-&gt;a
suffix:semicolon
id|matchlen
op_assign
id|bmatchlen
suffix:semicolon
)brace
)brace
)brace
r_if
c_cond
(paren
id|baddr
)paren
(brace
id|memcpy
c_func
(paren
id|saddr
comma
id|baddr
comma
r_sizeof
(paren
r_union
id|sctp_addr
)paren
)paren
suffix:semicolon
id|SCTP_DEBUG_PRINTK
c_func
(paren
l_string|&quot;saddr: &quot;
l_string|&quot;%04x:%04x:%04x:%04x:%04x:%04x:%04x:%04x&bslash;n&quot;
comma
id|NIP6
c_func
(paren
op_amp
id|saddr-&gt;v6.sin6_addr
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: asoc:%p Could not find a valid source &quot;
l_string|&quot;address for the &quot;
l_string|&quot;dest:%04x:%04x:%04x:%04x:%04x:%04x:%04x:%04x&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|asoc
comma
id|NIP6
c_func
(paren
op_amp
id|daddr-&gt;v6.sin6_addr
)paren
)paren
suffix:semicolon
)brace
id|sctp_read_unlock
c_func
(paren
id|addr_lock
)paren
suffix:semicolon
)brace
multiline_comment|/* Make a copy of all potential local addresses. */
DECL|function|sctp_v6_copy_addrlist
r_static
r_void
id|sctp_v6_copy_addrlist
c_func
(paren
r_struct
id|list_head
op_star
id|addrlist
comma
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_struct
id|inet6_dev
op_star
id|in6_dev
suffix:semicolon
r_struct
id|inet6_ifaddr
op_star
id|ifp
suffix:semicolon
r_struct
id|sockaddr_storage_list
op_star
id|addr
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|addrconf_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|in6_dev
op_assign
id|__in6_dev_get
c_func
(paren
id|dev
)paren
)paren
op_eq
l_int|NULL
)paren
(brace
id|read_unlock
c_func
(paren
op_amp
id|addrconf_lock
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|read_lock
c_func
(paren
op_amp
id|in6_dev-&gt;lock
)paren
suffix:semicolon
r_for
c_loop
(paren
id|ifp
op_assign
id|in6_dev-&gt;addr_list
suffix:semicolon
id|ifp
suffix:semicolon
id|ifp
op_assign
id|ifp-&gt;if_next
)paren
(brace
multiline_comment|/* Add the address to the local list.  */
id|addr
op_assign
id|t_new
c_func
(paren
r_struct
id|sockaddr_storage_list
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|addr
)paren
(brace
id|addr-&gt;a.v6.sin6_family
op_assign
id|AF_INET6
suffix:semicolon
id|addr-&gt;a.v6.sin6_port
op_assign
l_int|0
suffix:semicolon
id|addr-&gt;a.v6.sin6_addr
op_assign
id|ifp-&gt;addr
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|addr-&gt;list
)paren
suffix:semicolon
id|list_add_tail
c_func
(paren
op_amp
id|addr-&gt;list
comma
id|addrlist
)paren
suffix:semicolon
)brace
)brace
id|read_unlock
c_func
(paren
op_amp
id|in6_dev-&gt;lock
)paren
suffix:semicolon
id|read_unlock
c_func
(paren
op_amp
id|addrconf_lock
)paren
suffix:semicolon
)brace
multiline_comment|/* Initialize a sockaddr_storage from in incoming skb. */
DECL|function|sctp_v6_from_skb
r_static
r_void
id|sctp_v6_from_skb
c_func
(paren
r_union
id|sctp_addr
op_star
id|addr
comma
r_struct
id|sk_buff
op_star
id|skb
comma
r_int
id|is_saddr
)paren
(brace
r_void
op_star
id|from
suffix:semicolon
id|__u16
op_star
id|port
suffix:semicolon
r_struct
id|sctphdr
op_star
id|sh
suffix:semicolon
id|port
op_assign
op_amp
id|addr-&gt;v6.sin6_port
suffix:semicolon
id|addr-&gt;v6.sin6_family
op_assign
id|AF_INET6
suffix:semicolon
id|addr-&gt;v6.sin6_flowinfo
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* FIXME */
id|addr-&gt;v6.sin6_scope_id
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* FIXME */
id|sh
op_assign
(paren
r_struct
id|sctphdr
op_star
)paren
id|skb-&gt;h.raw
suffix:semicolon
r_if
c_cond
(paren
id|is_saddr
)paren
(brace
op_star
id|port
op_assign
id|ntohs
c_func
(paren
id|sh-&gt;source
)paren
suffix:semicolon
id|from
op_assign
op_amp
id|skb-&gt;nh.ipv6h-&gt;saddr
suffix:semicolon
)brace
r_else
(brace
op_star
id|port
op_assign
id|ntohs
c_func
(paren
id|sh-&gt;dest
)paren
suffix:semicolon
id|from
op_assign
op_amp
id|skb-&gt;nh.ipv6h-&gt;daddr
suffix:semicolon
)brace
id|ipv6_addr_copy
c_func
(paren
op_amp
id|addr-&gt;v6.sin6_addr
comma
id|from
)paren
suffix:semicolon
)brace
multiline_comment|/* Initialize an sctp_addr from a socket. */
DECL|function|sctp_v6_from_sk
r_static
r_void
id|sctp_v6_from_sk
c_func
(paren
r_union
id|sctp_addr
op_star
id|addr
comma
r_struct
id|sock
op_star
id|sk
)paren
(brace
id|addr-&gt;v6.sin6_family
op_assign
id|AF_INET6
suffix:semicolon
id|addr-&gt;v6.sin6_port
op_assign
id|inet_sk
c_func
(paren
id|sk
)paren
op_member_access_from_pointer
id|num
suffix:semicolon
id|addr-&gt;v6.sin6_addr
op_assign
id|inet6_sk
c_func
(paren
id|sk
)paren
op_member_access_from_pointer
id|rcv_saddr
suffix:semicolon
)brace
multiline_comment|/* Initialize sk-&gt;rcv_saddr from sctp_addr. */
DECL|function|sctp_v6_to_sk
r_static
r_void
id|sctp_v6_to_sk
c_func
(paren
r_union
id|sctp_addr
op_star
id|addr
comma
r_struct
id|sock
op_star
id|sk
)paren
(brace
id|inet6_sk
c_func
(paren
id|sk
)paren
op_member_access_from_pointer
id|rcv_saddr
op_assign
id|addr-&gt;v6.sin6_addr
suffix:semicolon
)brace
multiline_comment|/* Initialize a sctp_addr from a dst_entry. */
DECL|function|sctp_v6_dst_saddr
r_static
r_void
id|sctp_v6_dst_saddr
c_func
(paren
r_union
id|sctp_addr
op_star
id|addr
comma
r_struct
id|dst_entry
op_star
id|dst
comma
r_int
r_int
id|port
)paren
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
id|addr-&gt;sa.sa_family
op_assign
id|AF_INET6
suffix:semicolon
id|addr-&gt;v6.sin6_port
op_assign
id|port
suffix:semicolon
id|ipv6_addr_copy
c_func
(paren
op_amp
id|addr-&gt;v6.sin6_addr
comma
op_amp
id|rt-&gt;rt6i_src.addr
)paren
suffix:semicolon
)brace
multiline_comment|/* Compare addresses exactly.  Well.. almost exactly; ignore scope_id&n; * for now.  FIXME: v4-mapped-v6.&n; */
DECL|function|sctp_v6_cmp_addr
r_static
r_int
id|sctp_v6_cmp_addr
c_func
(paren
r_const
r_union
id|sctp_addr
op_star
id|addr1
comma
r_const
r_union
id|sctp_addr
op_star
id|addr2
)paren
(brace
r_int
id|match
suffix:semicolon
r_if
c_cond
(paren
id|addr1-&gt;sa.sa_family
op_ne
id|addr2-&gt;sa.sa_family
)paren
r_return
l_int|0
suffix:semicolon
id|match
op_assign
op_logical_neg
id|ipv6_addr_cmp
c_func
(paren
(paren
r_struct
id|in6_addr
op_star
)paren
op_amp
id|addr1-&gt;v6.sin6_addr
comma
(paren
r_struct
id|in6_addr
op_star
)paren
op_amp
id|addr2-&gt;v6.sin6_addr
)paren
suffix:semicolon
r_return
id|match
suffix:semicolon
)brace
multiline_comment|/* Initialize addr struct to INADDR_ANY. */
DECL|function|sctp_v6_inaddr_any
r_static
r_void
id|sctp_v6_inaddr_any
c_func
(paren
r_union
id|sctp_addr
op_star
id|addr
comma
r_int
r_int
id|port
)paren
(brace
id|memset
c_func
(paren
id|addr
comma
l_int|0x00
comma
r_sizeof
(paren
r_union
id|sctp_addr
)paren
)paren
suffix:semicolon
id|addr-&gt;v6.sin6_family
op_assign
id|AF_INET6
suffix:semicolon
id|addr-&gt;v6.sin6_port
op_assign
id|port
suffix:semicolon
)brace
multiline_comment|/* Is this a wildcard address? */
DECL|function|sctp_v6_is_any
r_static
r_int
id|sctp_v6_is_any
c_func
(paren
r_const
r_union
id|sctp_addr
op_star
id|addr
)paren
(brace
r_int
id|type
suffix:semicolon
id|type
op_assign
id|ipv6_addr_type
c_func
(paren
(paren
r_struct
id|in6_addr
op_star
)paren
op_amp
id|addr-&gt;v6.sin6_addr
)paren
suffix:semicolon
r_return
id|IPV6_ADDR_ANY
op_eq
id|type
suffix:semicolon
)brace
multiline_comment|/* Should this be available for binding?   */
DECL|function|sctp_v6_available
r_static
r_int
id|sctp_v6_available
c_func
(paren
r_const
r_union
id|sctp_addr
op_star
id|addr
)paren
(brace
r_int
id|type
suffix:semicolon
r_struct
id|in6_addr
op_star
id|in6
op_assign
(paren
r_struct
id|in6_addr
op_star
)paren
op_amp
id|addr-&gt;v6.sin6_addr
suffix:semicolon
id|type
op_assign
id|ipv6_addr_type
c_func
(paren
id|in6
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IPV6_ADDR_ANY
op_eq
id|type
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|type
op_amp
id|IPV6_ADDR_UNICAST
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|ipv6_chk_addr
c_func
(paren
id|in6
comma
l_int|NULL
)paren
suffix:semicolon
)brace
multiline_comment|/* This function checks if the address is a valid address to be used for&n; * SCTP.&n; *&n; * Output:&n; * Return 0 - If the address is a non-unicast or an illegal address.&n; * Return 1 - If the address is a unicast.&n; */
DECL|function|sctp_v6_addr_valid
r_static
r_int
id|sctp_v6_addr_valid
c_func
(paren
r_union
id|sctp_addr
op_star
id|addr
)paren
(brace
r_int
id|ret
op_assign
id|ipv6_addr_type
c_func
(paren
op_amp
id|addr-&gt;v6.sin6_addr
)paren
suffix:semicolon
multiline_comment|/* FIXME:  v4-mapped-v6 address support. */
multiline_comment|/* Is this a non-unicast address */
r_if
c_cond
(paren
op_logical_neg
(paren
id|ret
op_amp
id|IPV6_ADDR_UNICAST
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/* What is the scope of &squot;addr&squot;?  */
DECL|function|sctp_v6_scope
r_static
id|sctp_scope_t
id|sctp_v6_scope
c_func
(paren
r_union
id|sctp_addr
op_star
id|addr
)paren
(brace
r_int
id|v6scope
suffix:semicolon
id|sctp_scope_t
id|retval
suffix:semicolon
multiline_comment|/* The IPv6 scope is really a set of bit fields.&n;&t; * See IFA_* in &lt;net/if_inet6.h&gt;.  Map to a generic SCTP scope.&n;&t; */
id|v6scope
op_assign
id|ipv6_addr_scope
c_func
(paren
op_amp
id|addr-&gt;v6.sin6_addr
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|v6scope
)paren
(brace
r_case
id|IFA_HOST
suffix:colon
id|retval
op_assign
id|SCTP_SCOPE_LOOPBACK
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IFA_LINK
suffix:colon
id|retval
op_assign
id|SCTP_SCOPE_LINK
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IFA_SITE
suffix:colon
id|retval
op_assign
id|SCTP_SCOPE_PRIVATE
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|retval
op_assign
id|SCTP_SCOPE_GLOBAL
suffix:semicolon
r_break
suffix:semicolon
)brace
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/* Initialize a PF_INET6 socket msg_name. */
DECL|function|sctp_inet6_msgname
r_static
r_void
id|sctp_inet6_msgname
c_func
(paren
r_char
op_star
id|msgname
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
suffix:semicolon
id|sin6
op_assign
(paren
r_struct
id|sockaddr_in6
op_star
)paren
id|msgname
suffix:semicolon
id|sin6-&gt;sin6_family
op_assign
id|AF_INET6
suffix:semicolon
id|sin6-&gt;sin6_flowinfo
op_assign
l_int|0
suffix:semicolon
id|sin6-&gt;sin6_scope_id
op_assign
l_int|0
suffix:semicolon
op_star
id|addr_len
op_assign
r_sizeof
(paren
r_struct
id|sockaddr_in6
)paren
suffix:semicolon
)brace
multiline_comment|/* Initialize a PF_INET msgname from a ulpevent. */
DECL|function|sctp_inet6_event_msgname
r_static
r_void
id|sctp_inet6_event_msgname
c_func
(paren
id|sctp_ulpevent_t
op_star
id|event
comma
r_char
op_star
id|msgname
comma
r_int
op_star
id|addrlen
)paren
(brace
r_struct
id|sockaddr_in6
op_star
id|sin6
comma
op_star
id|sin6from
suffix:semicolon
r_if
c_cond
(paren
id|msgname
)paren
(brace
r_union
id|sctp_addr
op_star
id|addr
suffix:semicolon
id|sctp_inet6_msgname
c_func
(paren
id|msgname
comma
id|addrlen
)paren
suffix:semicolon
id|sin6
op_assign
(paren
r_struct
id|sockaddr_in6
op_star
)paren
id|msgname
suffix:semicolon
id|sin6-&gt;sin6_port
op_assign
id|htons
c_func
(paren
id|event-&gt;asoc-&gt;peer.port
)paren
suffix:semicolon
id|addr
op_assign
op_amp
id|event-&gt;asoc-&gt;peer.primary_addr
suffix:semicolon
multiline_comment|/* Note: If we go to a common v6 format, this code&n;&t;&t; * will change.&n;&t;&t; */
multiline_comment|/* Map ipv4 address into v4-mapped-on-v6 address.  */
r_if
c_cond
(paren
id|AF_INET
op_eq
id|addr-&gt;sa.sa_family
)paren
(brace
multiline_comment|/* FIXME: Easy, but there was no way to test this&n;&t;&t;&t; * yet.&n;&t;&t;&t; */
r_return
suffix:semicolon
)brace
id|sin6from
op_assign
op_amp
id|event-&gt;asoc-&gt;peer.primary_addr.v6
suffix:semicolon
id|ipv6_addr_copy
c_func
(paren
op_amp
id|sin6-&gt;sin6_addr
comma
op_amp
id|sin6from-&gt;sin6_addr
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* Initialize a msg_name from an inbound skb. */
DECL|function|sctp_inet6_skb_msgname
r_static
r_void
id|sctp_inet6_skb_msgname
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_char
op_star
id|msgname
comma
r_int
op_star
id|addr_len
)paren
(brace
r_struct
id|sctphdr
op_star
id|sh
suffix:semicolon
r_struct
id|sockaddr_in6
op_star
id|sin6
suffix:semicolon
r_if
c_cond
(paren
id|msgname
)paren
(brace
id|sctp_inet6_msgname
c_func
(paren
id|msgname
comma
id|addr_len
)paren
suffix:semicolon
id|sin6
op_assign
(paren
r_struct
id|sockaddr_in6
op_star
)paren
id|msgname
suffix:semicolon
id|sh
op_assign
(paren
r_struct
id|sctphdr
op_star
)paren
id|skb-&gt;h.raw
suffix:semicolon
id|sin6-&gt;sin6_port
op_assign
id|sh-&gt;source
suffix:semicolon
multiline_comment|/* FIXME: Map ipv4 address into v4-mapped-on-v6 address. */
r_if
c_cond
(paren
id|__constant_htons
c_func
(paren
id|ETH_P_IP
)paren
op_eq
id|skb-&gt;protocol
)paren
(brace
multiline_comment|/* FIXME: Easy, but there was no way to test this&n;&t;&t;&t; * yet.&n;&t;&t;&t; */
r_return
suffix:semicolon
)brace
multiline_comment|/* Otherwise, just copy the v6 address. */
id|ipv6_addr_copy
c_func
(paren
op_amp
id|sin6-&gt;sin6_addr
comma
op_amp
id|skb-&gt;nh.ipv6h-&gt;saddr
)paren
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
)brace
multiline_comment|/* Do we support this AF? */
DECL|function|sctp_inet6_af_supported
r_static
r_int
id|sctp_inet6_af_supported
c_func
(paren
id|sa_family_t
id|family
)paren
(brace
multiline_comment|/* FIXME:  v4-mapped-v6 addresses.  The I-D is still waffling&n;&t; * on what to do with sockaddr formats for PF_INET6 sockets.&n;&t; * For now assume we&squot;ll support both.&n;&t; */
r_switch
c_cond
(paren
id|family
)paren
(brace
r_case
id|AF_INET6
suffix:colon
r_case
id|AF_INET
suffix:colon
r_return
l_int|1
suffix:semicolon
r_default
suffix:colon
r_return
l_int|0
suffix:semicolon
)brace
)brace
multiline_comment|/* Address matching with wildcards allowed.  This extra level&n; * of indirection lets us choose whether a PF_INET6 should&n; * disallow any v4 addresses if we so choose.&n; */
DECL|function|sctp_inet6_cmp_addr
r_static
r_int
id|sctp_inet6_cmp_addr
c_func
(paren
r_const
r_union
id|sctp_addr
op_star
id|addr1
comma
r_const
r_union
id|sctp_addr
op_star
id|addr2
comma
r_struct
id|sctp_opt
op_star
id|opt
)paren
(brace
r_struct
id|sctp_af
op_star
id|af1
comma
op_star
id|af2
suffix:semicolon
id|af1
op_assign
id|sctp_get_af_specific
c_func
(paren
id|addr1-&gt;sa.sa_family
)paren
suffix:semicolon
id|af2
op_assign
id|sctp_get_af_specific
c_func
(paren
id|addr2-&gt;sa.sa_family
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|af1
op_logical_or
op_logical_neg
id|af2
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* Today, wildcard AF_INET/AF_INET6. */
r_if
c_cond
(paren
id|sctp_is_any
c_func
(paren
id|addr1
)paren
op_logical_or
id|sctp_is_any
c_func
(paren
id|addr2
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|addr1-&gt;sa.sa_family
op_ne
id|addr2-&gt;sa.sa_family
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|af1
op_member_access_from_pointer
id|cmp_addr
c_func
(paren
id|addr1
comma
id|addr2
)paren
suffix:semicolon
)brace
multiline_comment|/* Verify that the provided sockaddr looks bindable.   Common verification,&n; * has already been taken care of.&n; */
DECL|function|sctp_inet6_bind_verify
r_static
r_int
id|sctp_inet6_bind_verify
c_func
(paren
r_struct
id|sctp_opt
op_star
id|opt
comma
r_union
id|sctp_addr
op_star
id|addr
)paren
(brace
r_struct
id|sctp_af
op_star
id|af
suffix:semicolon
multiline_comment|/* ASSERT: address family has already been verified. */
r_if
c_cond
(paren
id|addr-&gt;sa.sa_family
op_ne
id|AF_INET6
)paren
(brace
id|af
op_assign
id|sctp_get_af_specific
c_func
(paren
id|addr-&gt;sa.sa_family
)paren
suffix:semicolon
)brace
r_else
id|af
op_assign
id|opt-&gt;pf-&gt;af
suffix:semicolon
r_return
id|af
op_member_access_from_pointer
id|available
c_func
(paren
id|addr
)paren
suffix:semicolon
)brace
DECL|variable|inet6_seqpacket_ops
r_static
r_struct
id|proto_ops
id|inet6_seqpacket_ops
op_assign
(brace
dot
id|family
op_assign
id|PF_INET6
comma
dot
id|release
op_assign
id|inet6_release
comma
dot
id|bind
op_assign
id|inet6_bind
comma
dot
id|connect
op_assign
id|inet_dgram_connect
comma
dot
id|socketpair
op_assign
id|sock_no_socketpair
comma
dot
id|accept
op_assign
id|inet_accept
comma
dot
id|getname
op_assign
id|inet6_getname
comma
dot
id|poll
op_assign
id|sctp_poll
comma
dot
id|ioctl
op_assign
id|inet6_ioctl
comma
dot
id|listen
op_assign
id|sctp_inet_listen
comma
dot
id|shutdown
op_assign
id|inet_shutdown
comma
dot
id|setsockopt
op_assign
id|inet_setsockopt
comma
dot
id|getsockopt
op_assign
id|inet_getsockopt
comma
dot
id|sendmsg
op_assign
id|inet_sendmsg
comma
dot
id|recvmsg
op_assign
id|inet_recvmsg
comma
dot
id|mmap
op_assign
id|sock_no_mmap
comma
)brace
suffix:semicolon
DECL|variable|sctpv6_protosw
r_static
r_struct
id|inet_protosw
id|sctpv6_protosw
op_assign
(brace
dot
id|type
op_assign
id|SOCK_SEQPACKET
comma
dot
id|protocol
op_assign
id|IPPROTO_SCTP
comma
dot
id|prot
op_assign
op_amp
id|sctp_prot
comma
dot
id|ops
op_assign
op_amp
id|inet6_seqpacket_ops
comma
dot
id|capability
op_assign
op_minus
l_int|1
comma
dot
id|no_check
op_assign
l_int|0
comma
dot
id|flags
op_assign
id|SCTP_PROTOSW_FLAG
)brace
suffix:semicolon
DECL|variable|sctpv6_protocol
r_static
r_struct
id|inet6_protocol
id|sctpv6_protocol
op_assign
(brace
dot
id|handler
op_assign
id|sctp_rcv
comma
dot
id|err_handler
op_assign
id|sctp_v6_err
comma
)brace
suffix:semicolon
DECL|variable|sctp_ipv6_specific
r_static
r_struct
id|sctp_af
id|sctp_ipv6_specific
op_assign
(brace
dot
id|sctp_xmit
op_assign
id|sctp_v6_xmit
comma
dot
id|setsockopt
op_assign
id|ipv6_setsockopt
comma
dot
id|getsockopt
op_assign
id|ipv6_getsockopt
comma
dot
id|get_dst
op_assign
id|sctp_v6_get_dst
comma
dot
id|get_saddr
op_assign
id|sctp_v6_get_saddr
comma
dot
id|copy_addrlist
op_assign
id|sctp_v6_copy_addrlist
comma
dot
id|from_skb
op_assign
id|sctp_v6_from_skb
comma
dot
id|from_sk
op_assign
id|sctp_v6_from_sk
comma
dot
id|to_sk
op_assign
id|sctp_v6_to_sk
comma
dot
id|dst_saddr
op_assign
id|sctp_v6_dst_saddr
comma
dot
id|cmp_addr
op_assign
id|sctp_v6_cmp_addr
comma
dot
id|scope
op_assign
id|sctp_v6_scope
comma
dot
id|addr_valid
op_assign
id|sctp_v6_addr_valid
comma
dot
id|inaddr_any
op_assign
id|sctp_v6_inaddr_any
comma
dot
id|is_any
op_assign
id|sctp_v6_is_any
comma
dot
id|available
op_assign
id|sctp_v6_available
comma
dot
id|net_header_len
op_assign
r_sizeof
(paren
r_struct
id|ipv6hdr
)paren
comma
dot
id|sockaddr_len
op_assign
r_sizeof
(paren
r_struct
id|sockaddr_in6
)paren
comma
dot
id|sa_family
op_assign
id|AF_INET6
comma
)brace
suffix:semicolon
DECL|variable|sctp_pf_inet6_specific
r_static
r_struct
id|sctp_pf
id|sctp_pf_inet6_specific
op_assign
(brace
dot
id|event_msgname
op_assign
id|sctp_inet6_event_msgname
comma
dot
id|skb_msgname
op_assign
id|sctp_inet6_skb_msgname
comma
dot
id|af_supported
op_assign
id|sctp_inet6_af_supported
comma
dot
id|cmp_addr
op_assign
id|sctp_inet6_cmp_addr
comma
dot
id|bind_verify
op_assign
id|sctp_inet6_bind_verify
comma
dot
id|af
op_assign
op_amp
id|sctp_ipv6_specific
comma
)brace
suffix:semicolon
multiline_comment|/* Initialize IPv6 support and register with inet6 stack.  */
DECL|function|sctp_v6_init
r_int
id|sctp_v6_init
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* Register inet6 protocol. */
r_if
c_cond
(paren
id|inet6_add_protocol
c_func
(paren
op_amp
id|sctpv6_protocol
comma
id|IPPROTO_SCTP
)paren
OL
l_int|0
)paren
r_return
op_minus
id|EAGAIN
suffix:semicolon
multiline_comment|/* Add SCTPv6 to inetsw6 linked list. */
id|inet6_register_protosw
c_func
(paren
op_amp
id|sctpv6_protosw
)paren
suffix:semicolon
multiline_comment|/* Register the SCTP specfic PF_INET6 functions. */
id|sctp_register_pf
c_func
(paren
op_amp
id|sctp_pf_inet6_specific
comma
id|PF_INET6
)paren
suffix:semicolon
multiline_comment|/* Register the SCTP specfic AF_INET6 functions. */
id|sctp_register_af
c_func
(paren
op_amp
id|sctp_ipv6_specific
)paren
suffix:semicolon
multiline_comment|/* Register notifier for inet6 address additions/deletions. */
id|register_inet6addr_notifier
c_func
(paren
op_amp
id|sctp_inetaddr_notifier
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* IPv6 specific exit support. */
DECL|function|sctp_v6_exit
r_void
id|sctp_v6_exit
c_func
(paren
r_void
)paren
(brace
id|list_del
c_func
(paren
op_amp
id|sctp_ipv6_specific.list
)paren
suffix:semicolon
id|inet6_del_protocol
c_func
(paren
op_amp
id|sctpv6_protocol
comma
id|IPPROTO_SCTP
)paren
suffix:semicolon
id|inet6_unregister_protosw
c_func
(paren
op_amp
id|sctpv6_protosw
)paren
suffix:semicolon
id|unregister_inet6addr_notifier
c_func
(paren
op_amp
id|sctp_inetaddr_notifier
)paren
suffix:semicolon
)brace
eof
