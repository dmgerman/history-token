multiline_comment|/*&n; *&t;Linux INET6 implementation&n; *&n; *&t;Authors:&n; *&t;Pedro Roque&t;&t;&lt;roque@di.fc.ul.pt&gt;&n; *&n; *&t;$Id: ipv6.h,v 1.1 2002/05/20 15:13:07 jgrimm Exp $&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *      modify it under the terms of the GNU General Public License&n; *      as published by the Free Software Foundation; either version&n; *      2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _NET_IPV6_H
DECL|macro|_NET_IPV6_H
mdefine_line|#define _NET_IPV6_H
macro_line|#include &lt;linux/ipv6.h&gt;
macro_line|#include &lt;asm/hardirq.h&gt;
macro_line|#include &lt;net/ndisc.h&gt;
macro_line|#include &lt;net/flow.h&gt;
macro_line|#include &lt;net/snmp.h&gt;
DECL|macro|SIN6_LEN_RFC2133
mdefine_line|#define SIN6_LEN_RFC2133&t;24
DECL|macro|IPV6_MAXPLEN
mdefine_line|#define IPV6_MAXPLEN&t;&t;65535
multiline_comment|/*&n; *&t;NextHeader field of IPv6 header&n; */
DECL|macro|NEXTHDR_HOP
mdefine_line|#define NEXTHDR_HOP&t;&t;0&t;/* Hop-by-hop option header. */
DECL|macro|NEXTHDR_TCP
mdefine_line|#define NEXTHDR_TCP&t;&t;6&t;/* TCP segment. */
DECL|macro|NEXTHDR_UDP
mdefine_line|#define NEXTHDR_UDP&t;&t;17&t;/* UDP message. */
DECL|macro|NEXTHDR_IPV6
mdefine_line|#define NEXTHDR_IPV6&t;&t;41&t;/* IPv6 in IPv6 */
DECL|macro|NEXTHDR_ROUTING
mdefine_line|#define NEXTHDR_ROUTING&t;&t;43&t;/* Routing header. */
DECL|macro|NEXTHDR_FRAGMENT
mdefine_line|#define NEXTHDR_FRAGMENT&t;44&t;/* Fragmentation/reassembly header. */
DECL|macro|NEXTHDR_ESP
mdefine_line|#define NEXTHDR_ESP&t;&t;50&t;/* Encapsulating security payload. */
DECL|macro|NEXTHDR_AUTH
mdefine_line|#define NEXTHDR_AUTH&t;&t;51&t;/* Authentication header. */
DECL|macro|NEXTHDR_ICMP
mdefine_line|#define NEXTHDR_ICMP&t;&t;58&t;/* ICMP for IPv6. */
DECL|macro|NEXTHDR_NONE
mdefine_line|#define NEXTHDR_NONE&t;&t;59&t;/* No next header */
DECL|macro|NEXTHDR_DEST
mdefine_line|#define NEXTHDR_DEST&t;&t;60&t;/* Destination options header. */
DECL|macro|NEXTHDR_MAX
mdefine_line|#define NEXTHDR_MAX&t;&t;255
DECL|macro|IPV6_DEFAULT_HOPLIMIT
mdefine_line|#define IPV6_DEFAULT_HOPLIMIT   64
DECL|macro|IPV6_DEFAULT_MCASTHOPS
mdefine_line|#define IPV6_DEFAULT_MCASTHOPS&t;1
multiline_comment|/*&n; *&t;Addr type&n; *&t;&n; *&t;type&t;-&t;unicast | multicast&n; *&t;scope&t;-&t;local&t;| site&t;    | global&n; *&t;v4&t;-&t;compat&n; *&t;v4mapped&n; *&t;any&n; *&t;loopback&n; */
DECL|macro|IPV6_ADDR_ANY
mdefine_line|#define IPV6_ADDR_ANY&t;&t;0x0000U
DECL|macro|IPV6_ADDR_UNICAST
mdefine_line|#define IPV6_ADDR_UNICAST      &t;0x0001U&t;
DECL|macro|IPV6_ADDR_MULTICAST
mdefine_line|#define IPV6_ADDR_MULTICAST    &t;0x0002U&t;
DECL|macro|IPV6_ADDR_LOOPBACK
mdefine_line|#define IPV6_ADDR_LOOPBACK&t;0x0010U
DECL|macro|IPV6_ADDR_LINKLOCAL
mdefine_line|#define IPV6_ADDR_LINKLOCAL&t;0x0020U
DECL|macro|IPV6_ADDR_SITELOCAL
mdefine_line|#define IPV6_ADDR_SITELOCAL&t;0x0040U
DECL|macro|IPV6_ADDR_COMPATv4
mdefine_line|#define IPV6_ADDR_COMPATv4&t;0x0080U
DECL|macro|IPV6_ADDR_SCOPE_MASK
mdefine_line|#define IPV6_ADDR_SCOPE_MASK&t;0x00f0U
DECL|macro|IPV6_ADDR_MAPPED
mdefine_line|#define IPV6_ADDR_MAPPED&t;0x1000U
DECL|macro|IPV6_ADDR_RESERVED
mdefine_line|#define IPV6_ADDR_RESERVED&t;0x2000U&t;/* reserved address space */
multiline_comment|/*&n; *&t;Addr scopes&n; */
macro_line|#ifdef __KERNEL__
DECL|macro|IPV6_ADDR_MC_SCOPE
mdefine_line|#define IPV6_ADDR_MC_SCOPE(a)&t;&bslash;&n;&t;((a)-&gt;s6_addr[1] &amp; 0x0f)&t;/* nonstandard */
DECL|macro|__IPV6_ADDR_SCOPE_INVALID
mdefine_line|#define __IPV6_ADDR_SCOPE_INVALID&t;-1
macro_line|#endif
DECL|macro|IPV6_ADDR_SCOPE_NODELOCAL
mdefine_line|#define IPV6_ADDR_SCOPE_NODELOCAL&t;0x01
DECL|macro|IPV6_ADDR_SCOPE_LINKLOCAL
mdefine_line|#define IPV6_ADDR_SCOPE_LINKLOCAL&t;0x02
DECL|macro|IPV6_ADDR_SCOPE_SITELOCAL
mdefine_line|#define IPV6_ADDR_SCOPE_SITELOCAL&t;0x05
DECL|macro|IPV6_ADDR_SCOPE_ORGLOCAL
mdefine_line|#define IPV6_ADDR_SCOPE_ORGLOCAL&t;0x08
DECL|macro|IPV6_ADDR_SCOPE_GLOBAL
mdefine_line|#define IPV6_ADDR_SCOPE_GLOBAL&t;&t;0x0e
multiline_comment|/*&n; *&t;fragmentation header&n; */
DECL|struct|frag_hdr
r_struct
id|frag_hdr
(brace
DECL|member|nexthdr
r_int
r_char
id|nexthdr
suffix:semicolon
DECL|member|reserved
r_int
r_char
id|reserved
suffix:semicolon
DECL|member|frag_off
r_int
r_int
id|frag_off
suffix:semicolon
DECL|member|identification
id|__u32
id|identification
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|IP6_MF
mdefine_line|#define&t;IP6_MF&t;0x0001
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;net/sock.h&gt;
multiline_comment|/* sysctls */
r_extern
r_int
id|sysctl_ipv6_bindv6only
suffix:semicolon
r_extern
r_int
id|sysctl_mld_max_msf
suffix:semicolon
multiline_comment|/* MIBs */
id|DECLARE_SNMP_STAT
c_func
(paren
r_struct
id|ipv6_mib
comma
id|ipv6_statistics
)paren
suffix:semicolon
DECL|macro|IP6_INC_STATS
mdefine_line|#define IP6_INC_STATS(field)&t;&t;SNMP_INC_STATS(ipv6_statistics, field)
DECL|macro|IP6_INC_STATS_BH
mdefine_line|#define IP6_INC_STATS_BH(field)&t;&t;SNMP_INC_STATS_BH(ipv6_statistics, field)
DECL|macro|IP6_INC_STATS_USER
mdefine_line|#define IP6_INC_STATS_USER(field) &t;SNMP_INC_STATS_USER(ipv6_statistics, field)
id|DECLARE_SNMP_STAT
c_func
(paren
r_struct
id|icmpv6_mib
comma
id|icmpv6_statistics
)paren
suffix:semicolon
DECL|macro|ICMP6_INC_STATS
mdefine_line|#define ICMP6_INC_STATS(idev, field)&t;&t;({&t;&t;&t;&bslash;&n;&t;struct inet6_dev *_idev = (idev);&t;&t;&t;&t;&bslash;&n;&t;if (likely(_idev != NULL))&t;&t;&t;&t;&t;&bslash;&n;&t;&t;SNMP_INC_STATS(idev-&gt;stats.icmpv6, field); &t;&t;&bslash;&n;&t;SNMP_INC_STATS(icmpv6_statistics, field);&t;&t;&t;&bslash;&n;})
DECL|macro|ICMP6_INC_STATS_BH
mdefine_line|#define ICMP6_INC_STATS_BH(idev, field)&t;&t;({&t;&t;&t;&bslash;&n;&t;struct inet6_dev *_idev = (idev);&t;&t;&t;&t;&bslash;&n;&t;if (likely(_idev != NULL))&t;&t;&t;&t;&t;&bslash;&n;&t;&t;SNMP_INC_STATS_BH((_idev)-&gt;stats.icmpv6, field);&t;&bslash;&n;&t;SNMP_INC_STATS_BH(icmpv6_statistics, field);&t;&t;&t;&bslash;&n;})
DECL|macro|ICMP6_INC_STATS_USER
mdefine_line|#define ICMP6_INC_STATS_USER(idev, field) &t;({&t;&t;&t;&bslash;&n;&t;struct inet6_dev *_idev = (idev);&t;&t;&t;&t;&bslash;&n;&t;if (likely(_idev != NULL))&t;&t;&t;&t;&t;&bslash;&n;&t;&t;SNMP_INC_STATS_USER(_idev-&gt;stats.icmpv6, field);&t;&bslash;&n;&t;SNMP_INC_STATS_USER(icmpv6_statistics, field);&t;&t;&t;&bslash;&n;})
DECL|macro|ICMP6_INC_STATS_OFFSET_BH
mdefine_line|#define ICMP6_INC_STATS_OFFSET_BH(idev, field, offset)&t;({&t;&t;&t;&bslash;&n;&t;struct inet6_dev *_idev = idev;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__typeof__(offset) _offset = (offset);&t;&t;&t;&t;&t;&bslash;&n;&t;if (likely(_idev != NULL))&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;SNMP_INC_STATS_OFFSET_BH(_idev-&gt;stats.icmpv6, field, _offset);&t;&bslash;&n;&t;SNMP_INC_STATS_OFFSET_BH(icmpv6_statistics, field, _offset);    &t;&bslash;&n;})
id|DECLARE_SNMP_STAT
c_func
(paren
r_struct
id|udp_mib
comma
id|udp_stats_in6
)paren
suffix:semicolon
DECL|macro|UDP6_INC_STATS
mdefine_line|#define UDP6_INC_STATS(field)&t;&t;SNMP_INC_STATS(udp_stats_in6, field)
DECL|macro|UDP6_INC_STATS_BH
mdefine_line|#define UDP6_INC_STATS_BH(field)&t;SNMP_INC_STATS_BH(udp_stats_in6, field)
DECL|macro|UDP6_INC_STATS_USER
mdefine_line|#define UDP6_INC_STATS_USER(field) &t;SNMP_INC_STATS_USER(udp_stats_in6, field)
r_extern
id|atomic_t
id|inet6_sock_nr
suffix:semicolon
r_int
id|snmp6_register_dev
c_func
(paren
r_struct
id|inet6_dev
op_star
id|idev
)paren
suffix:semicolon
r_int
id|snmp6_unregister_dev
c_func
(paren
r_struct
id|inet6_dev
op_star
id|idev
)paren
suffix:semicolon
r_int
id|snmp6_mib_init
c_func
(paren
r_void
op_star
id|ptr
(braket
l_int|2
)braket
comma
r_int
id|mibsize
comma
r_int
id|mibalign
)paren
suffix:semicolon
r_void
id|snmp6_mib_free
c_func
(paren
r_void
op_star
id|ptr
(braket
l_int|2
)braket
)paren
suffix:semicolon
DECL|struct|ip6_ra_chain
r_struct
id|ip6_ra_chain
(brace
DECL|member|next
r_struct
id|ip6_ra_chain
op_star
id|next
suffix:semicolon
DECL|member|sk
r_struct
id|sock
op_star
id|sk
suffix:semicolon
DECL|member|sel
r_int
id|sel
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
id|ip6_ra_chain
op_star
id|ip6_ra_chain
suffix:semicolon
r_extern
id|rwlock_t
id|ip6_ra_lock
suffix:semicolon
multiline_comment|/*&n;   This structure is prepared by protocol, when parsing&n;   ancillary data and passed to IPv6.&n; */
DECL|struct|ipv6_txoptions
r_struct
id|ipv6_txoptions
(brace
multiline_comment|/* Length of this structure */
DECL|member|tot_len
r_int
id|tot_len
suffix:semicolon
multiline_comment|/* length of extension headers   */
DECL|member|opt_flen
id|__u16
id|opt_flen
suffix:semicolon
multiline_comment|/* after fragment hdr */
DECL|member|opt_nflen
id|__u16
id|opt_nflen
suffix:semicolon
multiline_comment|/* before fragment hdr */
DECL|member|hopopt
r_struct
id|ipv6_opt_hdr
op_star
id|hopopt
suffix:semicolon
DECL|member|dst0opt
r_struct
id|ipv6_opt_hdr
op_star
id|dst0opt
suffix:semicolon
DECL|member|srcrt
r_struct
id|ipv6_rt_hdr
op_star
id|srcrt
suffix:semicolon
multiline_comment|/* Routing Header */
DECL|member|auth
r_struct
id|ipv6_opt_hdr
op_star
id|auth
suffix:semicolon
DECL|member|dst1opt
r_struct
id|ipv6_opt_hdr
op_star
id|dst1opt
suffix:semicolon
multiline_comment|/* Option buffer, as read by IPV6_PKTOPTIONS, starts here. */
)brace
suffix:semicolon
DECL|struct|ip6_flowlabel
r_struct
id|ip6_flowlabel
(brace
DECL|member|next
r_struct
id|ip6_flowlabel
op_star
id|next
suffix:semicolon
DECL|member|label
id|u32
id|label
suffix:semicolon
DECL|member|dst
r_struct
id|in6_addr
id|dst
suffix:semicolon
DECL|member|opt
r_struct
id|ipv6_txoptions
op_star
id|opt
suffix:semicolon
DECL|member|users
id|atomic_t
id|users
suffix:semicolon
DECL|member|linger
r_int
r_int
id|linger
suffix:semicolon
DECL|member|share
id|u8
id|share
suffix:semicolon
DECL|member|owner
id|u32
id|owner
suffix:semicolon
DECL|member|lastuse
r_int
r_int
id|lastuse
suffix:semicolon
DECL|member|expires
r_int
r_int
id|expires
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|IPV6_FLOWINFO_MASK
mdefine_line|#define IPV6_FLOWINFO_MASK&t;__constant_htonl(0x0FFFFFFF)
DECL|macro|IPV6_FLOWLABEL_MASK
mdefine_line|#define IPV6_FLOWLABEL_MASK&t;__constant_htonl(0x000FFFFF)
DECL|struct|ipv6_fl_socklist
r_struct
id|ipv6_fl_socklist
(brace
DECL|member|next
r_struct
id|ipv6_fl_socklist
op_star
id|next
suffix:semicolon
DECL|member|fl
r_struct
id|ip6_flowlabel
op_star
id|fl
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|ip6_flowlabel
op_star
id|fl6_sock_lookup
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
id|u32
id|label
)paren
suffix:semicolon
r_extern
r_struct
id|ipv6_txoptions
op_star
id|fl6_merge_options
c_func
(paren
r_struct
id|ipv6_txoptions
op_star
id|opt_space
comma
r_struct
id|ip6_flowlabel
op_star
id|fl
comma
r_struct
id|ipv6_txoptions
op_star
id|fopt
)paren
suffix:semicolon
r_extern
r_void
id|fl6_free_socklist
c_func
(paren
r_struct
id|sock
op_star
id|sk
)paren
suffix:semicolon
r_extern
r_int
id|ipv6_flowlabel_opt
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_char
id|__user
op_star
id|optval
comma
r_int
id|optlen
)paren
suffix:semicolon
r_extern
r_void
id|ip6_flowlabel_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|ip6_flowlabel_cleanup
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|function|fl6_sock_release
r_static
r_inline
r_void
id|fl6_sock_release
c_func
(paren
r_struct
id|ip6_flowlabel
op_star
id|fl
)paren
(brace
r_if
c_cond
(paren
id|fl
)paren
id|atomic_dec
c_func
(paren
op_amp
id|fl-&gt;users
)paren
suffix:semicolon
)brace
r_extern
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
suffix:semicolon
r_extern
r_int
id|ip6_call_ra_chain
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_int
id|sel
)paren
suffix:semicolon
r_extern
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
)paren
suffix:semicolon
r_extern
r_struct
id|ipv6_txoptions
op_star
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
suffix:semicolon
r_extern
r_int
id|ip6_frag_nqueues
suffix:semicolon
r_extern
id|atomic_t
id|ip6_frag_mem
suffix:semicolon
DECL|macro|IPV6_FRAG_TIMEOUT
mdefine_line|#define IPV6_FRAG_TIMEOUT&t;(60*HZ)&t;&t;/* 60 seconds */
multiline_comment|/*&n; *&t;Function prototype for build_xmit&n; */
DECL|typedef|inet_getfrag_t
r_typedef
r_int
(paren
op_star
id|inet_getfrag_t
)paren
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
comma
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
id|ipv6_addr_type
c_func
(paren
r_const
r_struct
id|in6_addr
op_star
id|addr
)paren
suffix:semicolon
DECL|function|ipv6_addr_scope
r_static
r_inline
r_int
id|ipv6_addr_scope
c_func
(paren
r_const
r_struct
id|in6_addr
op_star
id|addr
)paren
(brace
r_return
id|ipv6_addr_type
c_func
(paren
id|addr
)paren
op_amp
id|IPV6_ADDR_SCOPE_MASK
suffix:semicolon
)brace
DECL|function|ipv6_addr_cmp
r_static
r_inline
r_int
id|ipv6_addr_cmp
c_func
(paren
r_const
r_struct
id|in6_addr
op_star
id|a1
comma
r_const
r_struct
id|in6_addr
op_star
id|a2
)paren
(brace
r_return
id|memcmp
c_func
(paren
(paren
r_const
r_void
op_star
)paren
id|a1
comma
(paren
r_const
r_void
op_star
)paren
id|a2
comma
r_sizeof
(paren
r_struct
id|in6_addr
)paren
)paren
suffix:semicolon
)brace
DECL|function|ipv6_addr_copy
r_static
r_inline
r_void
id|ipv6_addr_copy
c_func
(paren
r_struct
id|in6_addr
op_star
id|a1
comma
r_const
r_struct
id|in6_addr
op_star
id|a2
)paren
(brace
id|memcpy
c_func
(paren
(paren
r_void
op_star
)paren
id|a1
comma
(paren
r_const
r_void
op_star
)paren
id|a2
comma
r_sizeof
(paren
r_struct
id|in6_addr
)paren
)paren
suffix:semicolon
)brace
DECL|function|ipv6_addr_prefix
r_static
r_inline
r_void
id|ipv6_addr_prefix
c_func
(paren
r_struct
id|in6_addr
op_star
id|pfx
comma
r_const
r_struct
id|in6_addr
op_star
id|addr
comma
r_int
id|plen
)paren
(brace
multiline_comment|/* caller must guarantee 0 &lt;= plen &lt;= 128 */
r_int
id|o
op_assign
id|plen
op_rshift
l_int|3
comma
id|b
op_assign
id|plen
op_amp
l_int|0x7
suffix:semicolon
id|memcpy
c_func
(paren
id|pfx-&gt;s6_addr
comma
id|addr
comma
id|o
)paren
suffix:semicolon
r_if
c_cond
(paren
id|b
op_ne
l_int|0
)paren
(brace
id|pfx-&gt;s6_addr
(braket
id|o
)braket
op_assign
id|addr-&gt;s6_addr
(braket
id|o
)braket
op_amp
(paren
l_int|0xff00
op_rshift
id|b
)paren
suffix:semicolon
id|o
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|o
OL
l_int|16
)paren
id|memset
c_func
(paren
id|pfx-&gt;s6_addr
op_plus
id|o
comma
l_int|0
comma
l_int|16
op_minus
id|o
)paren
suffix:semicolon
)brace
macro_line|#ifndef __HAVE_ARCH_ADDR_SET
DECL|function|ipv6_addr_set
r_static
r_inline
r_void
id|ipv6_addr_set
c_func
(paren
r_struct
id|in6_addr
op_star
id|addr
comma
id|__u32
id|w1
comma
id|__u32
id|w2
comma
id|__u32
id|w3
comma
id|__u32
id|w4
)paren
(brace
id|addr-&gt;s6_addr32
(braket
l_int|0
)braket
op_assign
id|w1
suffix:semicolon
id|addr-&gt;s6_addr32
(braket
l_int|1
)braket
op_assign
id|w2
suffix:semicolon
id|addr-&gt;s6_addr32
(braket
l_int|2
)braket
op_assign
id|w3
suffix:semicolon
id|addr-&gt;s6_addr32
(braket
l_int|3
)braket
op_assign
id|w4
suffix:semicolon
)brace
macro_line|#endif
DECL|function|ipv6_addr_any
r_static
r_inline
r_int
id|ipv6_addr_any
c_func
(paren
r_const
r_struct
id|in6_addr
op_star
id|a
)paren
(brace
r_return
(paren
(paren
id|a-&gt;s6_addr32
(braket
l_int|0
)braket
op_or
id|a-&gt;s6_addr32
(braket
l_int|1
)braket
op_or
id|a-&gt;s6_addr32
(braket
l_int|2
)braket
op_or
id|a-&gt;s6_addr32
(braket
l_int|3
)braket
)paren
op_eq
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Prototypes exported by ipv6&n; */
multiline_comment|/*&n; *&t;rcv function (called from netdevice level)&n; */
r_extern
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
suffix:semicolon
multiline_comment|/*&n; *&t;upper-layer output functions&n; */
r_extern
r_int
id|ip6_xmit
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
id|ipfragok
)paren
suffix:semicolon
r_extern
r_int
id|ip6_nd_hdr
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
id|net_device
op_star
id|dev
comma
r_struct
id|in6_addr
op_star
id|saddr
comma
r_struct
id|in6_addr
op_star
id|daddr
comma
r_int
id|proto
comma
r_int
id|len
)paren
suffix:semicolon
r_extern
r_int
id|ip6_find_1stfragopt
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
id|u8
op_star
op_star
id|nexthdr
)paren
suffix:semicolon
r_extern
r_int
id|ip6_append_data
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
id|length
comma
r_int
id|transhdrlen
comma
r_int
id|hlimit
comma
r_struct
id|ipv6_txoptions
op_star
id|opt
comma
r_struct
id|flowi
op_star
id|fl
comma
r_struct
id|rt6_info
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
id|ip6_push_pending_frames
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
id|ip6_flush_pending_frames
c_func
(paren
r_struct
id|sock
op_star
id|sk
)paren
suffix:semicolon
r_extern
r_int
id|ip6_dst_lookup
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
op_star
id|dst
comma
r_struct
id|flowi
op_star
id|fl
)paren
suffix:semicolon
multiline_comment|/*&n; *&t;skb processing functions&n; */
r_extern
r_int
id|ip6_output
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
id|ip6_output2
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
id|ip6_forward
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
id|ip6_input
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
id|ip6_mc_input
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
multiline_comment|/*&n; *&t;Extension header (options) processing&n; */
r_extern
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
suffix:semicolon
r_extern
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
suffix:semicolon
r_extern
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
id|daddr_p
)paren
suffix:semicolon
r_extern
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
suffix:semicolon
r_extern
r_int
id|ipv6_skip_exthdr
c_func
(paren
r_const
r_struct
id|sk_buff
op_star
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
suffix:semicolon
r_extern
r_int
id|ipv6_ext_hdr
c_func
(paren
id|u8
id|nexthdr
)paren
suffix:semicolon
r_extern
r_struct
id|ipv6_txoptions
op_star
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
suffix:semicolon
multiline_comment|/*&n; *&t;socket options (ipv6_sockglue.c)&n; */
r_extern
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
id|__user
op_star
id|optval
comma
r_int
id|optlen
)paren
suffix:semicolon
r_extern
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
id|__user
op_star
id|optval
comma
r_int
id|__user
op_star
id|optlen
)paren
suffix:semicolon
r_extern
r_void
id|ipv6_packet_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|ipv6_packet_cleanup
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
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
suffix:semicolon
r_extern
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
suffix:semicolon
r_extern
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
suffix:semicolon
r_extern
r_int
id|inet6_release
c_func
(paren
r_struct
id|socket
op_star
id|sock
)paren
suffix:semicolon
r_extern
r_int
id|inet6_bind
c_func
(paren
r_struct
id|socket
op_star
id|sock
comma
r_struct
id|sockaddr
op_star
id|uaddr
comma
r_int
id|addr_len
)paren
suffix:semicolon
r_extern
r_int
id|inet6_getname
c_func
(paren
r_struct
id|socket
op_star
id|sock
comma
r_struct
id|sockaddr
op_star
id|uaddr
comma
r_int
op_star
id|uaddr_len
comma
r_int
id|peer
)paren
suffix:semicolon
r_extern
r_int
id|inet6_ioctl
c_func
(paren
r_struct
id|socket
op_star
id|sock
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
suffix:semicolon
multiline_comment|/*&n; * reassembly.c&n; */
r_extern
r_int
id|sysctl_ip6frag_high_thresh
suffix:semicolon
r_extern
r_int
id|sysctl_ip6frag_low_thresh
suffix:semicolon
r_extern
r_int
id|sysctl_ip6frag_time
suffix:semicolon
r_extern
r_int
id|sysctl_ip6frag_secret_interval
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _NET_IPV6_H */
eof
