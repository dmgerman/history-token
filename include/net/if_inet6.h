multiline_comment|/*&n; *&t;inet6 interface/address list definitions&n; *&t;Linux INET6 implementation &n; *&n; *&t;Authors:&n; *&t;Pedro Roque&t;&t;&lt;roque@di.fc.ul.pt&gt;&t;&n; *&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *      modify it under the terms of the GNU General Public License&n; *      as published by the Free Software Foundation; either version&n; *      2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _NET_IF_INET6_H
DECL|macro|_NET_IF_INET6_H
mdefine_line|#define _NET_IF_INET6_H
macro_line|#include &lt;net/snmp.h&gt;
macro_line|#include &lt;linux/ipv6.h&gt;
multiline_comment|/* inet6_dev.if_flags */
DECL|macro|IF_RA_OTHERCONF
mdefine_line|#define IF_RA_OTHERCONF&t;0x80
DECL|macro|IF_RA_MANAGED
mdefine_line|#define IF_RA_MANAGED&t;0x40
DECL|macro|IF_RA_RCVD
mdefine_line|#define IF_RA_RCVD&t;0x20
DECL|macro|IF_RS_SENT
mdefine_line|#define IF_RS_SENT&t;0x10
multiline_comment|/* prefix flags */
DECL|macro|IF_PREFIX_ONLINK
mdefine_line|#define IF_PREFIX_ONLINK&t;0x01
DECL|macro|IF_PREFIX_AUTOCONF
mdefine_line|#define IF_PREFIX_AUTOCONF&t;0x02
macro_line|#ifdef __KERNEL__
DECL|struct|inet6_ifaddr
r_struct
id|inet6_ifaddr
(brace
DECL|member|addr
r_struct
id|in6_addr
id|addr
suffix:semicolon
DECL|member|prefix_len
id|__u32
id|prefix_len
suffix:semicolon
DECL|member|valid_lft
id|__u32
id|valid_lft
suffix:semicolon
DECL|member|prefered_lft
id|__u32
id|prefered_lft
suffix:semicolon
DECL|member|cstamp
r_int
r_int
id|cstamp
suffix:semicolon
multiline_comment|/* created timestamp */
DECL|member|tstamp
r_int
r_int
id|tstamp
suffix:semicolon
multiline_comment|/* updated timestamp */
DECL|member|refcnt
id|atomic_t
id|refcnt
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|probes
id|__u8
id|probes
suffix:semicolon
DECL|member|flags
id|__u8
id|flags
suffix:semicolon
DECL|member|scope
id|__u16
id|scope
suffix:semicolon
DECL|member|timer
r_struct
id|timer_list
id|timer
suffix:semicolon
DECL|member|idev
r_struct
id|inet6_dev
op_star
id|idev
suffix:semicolon
DECL|member|rt
r_struct
id|rt6_info
op_star
id|rt
suffix:semicolon
DECL|member|lst_next
r_struct
id|inet6_ifaddr
op_star
id|lst_next
suffix:semicolon
multiline_comment|/* next addr in addr_lst */
DECL|member|if_next
r_struct
id|inet6_ifaddr
op_star
id|if_next
suffix:semicolon
multiline_comment|/* next addr in inet6_dev */
macro_line|#ifdef CONFIG_IPV6_PRIVACY
DECL|member|tmp_next
r_struct
id|inet6_ifaddr
op_star
id|tmp_next
suffix:semicolon
multiline_comment|/* next addr in tempaddr_lst */
DECL|member|ifpub
r_struct
id|inet6_ifaddr
op_star
id|ifpub
suffix:semicolon
DECL|member|regen_count
r_int
id|regen_count
suffix:semicolon
macro_line|#endif
DECL|member|dead
r_int
id|dead
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ip6_sf_socklist
r_struct
id|ip6_sf_socklist
(brace
DECL|member|sl_max
r_int
r_int
id|sl_max
suffix:semicolon
DECL|member|sl_count
r_int
r_int
id|sl_count
suffix:semicolon
DECL|member|sl_addr
r_struct
id|in6_addr
id|sl_addr
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|IP6_SFLSIZE
mdefine_line|#define IP6_SFLSIZE(count)&t;(sizeof(struct ip6_sf_socklist) + &bslash;&n;&t;(count) * sizeof(struct in6_addr))
DECL|macro|IP6_SFBLOCK
mdefine_line|#define IP6_SFBLOCK&t;10&t;/* allocate this many at once */
DECL|struct|ipv6_mc_socklist
r_struct
id|ipv6_mc_socklist
(brace
DECL|member|addr
r_struct
id|in6_addr
id|addr
suffix:semicolon
DECL|member|ifindex
r_int
id|ifindex
suffix:semicolon
DECL|member|next
r_struct
id|ipv6_mc_socklist
op_star
id|next
suffix:semicolon
DECL|member|sfmode
r_int
r_int
id|sfmode
suffix:semicolon
multiline_comment|/* MCAST_{INCLUDE,EXCLUDE} */
DECL|member|sflist
r_struct
id|ip6_sf_socklist
op_star
id|sflist
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ip6_sf_list
r_struct
id|ip6_sf_list
(brace
DECL|member|sf_next
r_struct
id|ip6_sf_list
op_star
id|sf_next
suffix:semicolon
DECL|member|sf_addr
r_struct
id|in6_addr
id|sf_addr
suffix:semicolon
DECL|member|sf_count
r_int
r_int
id|sf_count
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* include/exclude counts */
DECL|member|sf_gsresp
r_int
r_char
id|sf_gsresp
suffix:semicolon
multiline_comment|/* include in g &amp; s response? */
DECL|member|sf_oldin
r_int
r_char
id|sf_oldin
suffix:semicolon
multiline_comment|/* change state */
DECL|member|sf_crcount
r_int
r_char
id|sf_crcount
suffix:semicolon
multiline_comment|/* retrans. left to send */
)brace
suffix:semicolon
DECL|macro|MAF_TIMER_RUNNING
mdefine_line|#define MAF_TIMER_RUNNING&t;0x01
DECL|macro|MAF_LAST_REPORTER
mdefine_line|#define MAF_LAST_REPORTER&t;0x02
DECL|macro|MAF_LOADED
mdefine_line|#define MAF_LOADED&t;&t;0x04
DECL|macro|MAF_NOREPORT
mdefine_line|#define MAF_NOREPORT&t;&t;0x08
DECL|macro|MAF_GSQUERY
mdefine_line|#define MAF_GSQUERY&t;&t;0x10
DECL|struct|ifmcaddr6
r_struct
id|ifmcaddr6
(brace
DECL|member|mca_addr
r_struct
id|in6_addr
id|mca_addr
suffix:semicolon
DECL|member|idev
r_struct
id|inet6_dev
op_star
id|idev
suffix:semicolon
DECL|member|next
r_struct
id|ifmcaddr6
op_star
id|next
suffix:semicolon
DECL|member|mca_sources
r_struct
id|ip6_sf_list
op_star
id|mca_sources
suffix:semicolon
DECL|member|mca_tomb
r_struct
id|ip6_sf_list
op_star
id|mca_tomb
suffix:semicolon
DECL|member|mca_sfmode
r_int
r_int
id|mca_sfmode
suffix:semicolon
DECL|member|mca_sfcount
r_int
r_int
id|mca_sfcount
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|mca_timer
r_struct
id|timer_list
id|mca_timer
suffix:semicolon
DECL|member|mca_flags
r_int
id|mca_flags
suffix:semicolon
DECL|member|mca_users
r_int
id|mca_users
suffix:semicolon
DECL|member|mca_refcnt
id|atomic_t
id|mca_refcnt
suffix:semicolon
DECL|member|mca_lock
id|spinlock_t
id|mca_lock
suffix:semicolon
DECL|member|mca_crcount
r_int
r_char
id|mca_crcount
suffix:semicolon
DECL|member|mca_cstamp
r_int
r_int
id|mca_cstamp
suffix:semicolon
DECL|member|mca_tstamp
r_int
r_int
id|mca_tstamp
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Anycast stuff */
DECL|struct|ipv6_ac_socklist
r_struct
id|ipv6_ac_socklist
(brace
DECL|member|acl_addr
r_struct
id|in6_addr
id|acl_addr
suffix:semicolon
DECL|member|acl_ifindex
r_int
id|acl_ifindex
suffix:semicolon
DECL|member|acl_next
r_struct
id|ipv6_ac_socklist
op_star
id|acl_next
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ifacaddr6
r_struct
id|ifacaddr6
(brace
DECL|member|aca_addr
r_struct
id|in6_addr
id|aca_addr
suffix:semicolon
DECL|member|aca_idev
r_struct
id|inet6_dev
op_star
id|aca_idev
suffix:semicolon
DECL|member|aca_rt
r_struct
id|rt6_info
op_star
id|aca_rt
suffix:semicolon
DECL|member|aca_next
r_struct
id|ifacaddr6
op_star
id|aca_next
suffix:semicolon
DECL|member|aca_users
r_int
id|aca_users
suffix:semicolon
DECL|member|aca_refcnt
id|atomic_t
id|aca_refcnt
suffix:semicolon
DECL|member|aca_lock
id|spinlock_t
id|aca_lock
suffix:semicolon
DECL|member|aca_cstamp
r_int
r_int
id|aca_cstamp
suffix:semicolon
DECL|member|aca_tstamp
r_int
r_int
id|aca_tstamp
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|IFA_HOST
mdefine_line|#define&t;IFA_HOST&t;IPV6_ADDR_LOOPBACK
DECL|macro|IFA_LINK
mdefine_line|#define&t;IFA_LINK&t;IPV6_ADDR_LINKLOCAL
DECL|macro|IFA_SITE
mdefine_line|#define&t;IFA_SITE&t;IPV6_ADDR_SITELOCAL
DECL|macro|IFA_GLOBAL
mdefine_line|#define&t;IFA_GLOBAL&t;0x0000U
DECL|struct|ipv6_devstat
r_struct
id|ipv6_devstat
(brace
DECL|member|proc_dir_entry
r_struct
id|proc_dir_entry
op_star
id|proc_dir_entry
suffix:semicolon
id|DEFINE_SNMP_STAT
c_func
(paren
r_struct
id|icmpv6_mib
comma
id|icmpv6
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|inet6_dev
r_struct
id|inet6_dev
(brace
DECL|member|dev
r_struct
id|net_device
op_star
id|dev
suffix:semicolon
DECL|member|addr_list
r_struct
id|inet6_ifaddr
op_star
id|addr_list
suffix:semicolon
DECL|member|mc_list
r_struct
id|ifmcaddr6
op_star
id|mc_list
suffix:semicolon
DECL|member|mc_tomb
r_struct
id|ifmcaddr6
op_star
id|mc_tomb
suffix:semicolon
DECL|member|mc_lock
id|rwlock_t
id|mc_lock
suffix:semicolon
DECL|member|mc_v1_seen
r_int
r_int
id|mc_v1_seen
suffix:semicolon
DECL|member|mc_maxdelay
r_int
r_int
id|mc_maxdelay
suffix:semicolon
DECL|member|mc_qrv
r_int
r_char
id|mc_qrv
suffix:semicolon
DECL|member|mc_gq_running
r_int
r_char
id|mc_gq_running
suffix:semicolon
DECL|member|mc_ifc_count
r_int
r_char
id|mc_ifc_count
suffix:semicolon
DECL|member|mc_gq_timer
r_struct
id|timer_list
id|mc_gq_timer
suffix:semicolon
multiline_comment|/* general query timer */
DECL|member|mc_ifc_timer
r_struct
id|timer_list
id|mc_ifc_timer
suffix:semicolon
multiline_comment|/* interface change timer */
DECL|member|ac_list
r_struct
id|ifacaddr6
op_star
id|ac_list
suffix:semicolon
DECL|member|lock
id|rwlock_t
id|lock
suffix:semicolon
DECL|member|refcnt
id|atomic_t
id|refcnt
suffix:semicolon
DECL|member|if_flags
id|__u32
id|if_flags
suffix:semicolon
DECL|member|dead
r_int
id|dead
suffix:semicolon
macro_line|#ifdef CONFIG_IPV6_PRIVACY
DECL|member|rndid
id|u8
id|rndid
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|entropy
id|u8
id|entropy
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|regen_timer
r_struct
id|timer_list
id|regen_timer
suffix:semicolon
DECL|member|tempaddr_list
r_struct
id|inet6_ifaddr
op_star
id|tempaddr_list
suffix:semicolon
DECL|member|work_eui64
id|__u8
id|work_eui64
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|work_digest
id|__u8
id|work_digest
(braket
l_int|16
)braket
suffix:semicolon
macro_line|#endif
DECL|member|nd_parms
r_struct
id|neigh_parms
op_star
id|nd_parms
suffix:semicolon
DECL|member|next
r_struct
id|inet6_dev
op_star
id|next
suffix:semicolon
DECL|member|cnf
r_struct
id|ipv6_devconf
id|cnf
suffix:semicolon
DECL|member|stats
r_struct
id|ipv6_devstat
id|stats
suffix:semicolon
DECL|member|tstamp
r_int
r_int
id|tstamp
suffix:semicolon
multiline_comment|/* ipv6InterfaceTable update timestamp */
)brace
suffix:semicolon
r_extern
r_struct
id|ipv6_devconf
id|ipv6_devconf
suffix:semicolon
DECL|function|ipv6_eth_mc_map
r_static
r_inline
r_void
id|ipv6_eth_mc_map
c_func
(paren
r_struct
id|in6_addr
op_star
id|addr
comma
r_char
op_star
id|buf
)paren
(brace
multiline_comment|/*&n;&t; *&t;+-------+-------+-------+-------+-------+-------+&n;&t; *      |   33  |   33  | DST13 | DST14 | DST15 | DST16 |&n;&t; *      +-------+-------+-------+-------+-------+-------+&n;&t; */
id|buf
(braket
l_int|0
)braket
op_assign
l_int|0x33
suffix:semicolon
id|buf
(braket
l_int|1
)braket
op_assign
l_int|0x33
suffix:semicolon
id|memcpy
c_func
(paren
id|buf
op_plus
l_int|2
comma
op_amp
id|addr-&gt;s6_addr32
(braket
l_int|3
)braket
comma
r_sizeof
(paren
id|__u32
)paren
)paren
suffix:semicolon
)brace
DECL|function|ipv6_tr_mc_map
r_static
r_inline
r_void
id|ipv6_tr_mc_map
c_func
(paren
r_struct
id|in6_addr
op_star
id|addr
comma
r_char
op_star
id|buf
)paren
(brace
multiline_comment|/* All nodes FF01::1, FF02::1, FF02::1:FFxx:xxxx */
r_if
c_cond
(paren
(paren
(paren
id|addr-&gt;s6_addr
(braket
l_int|0
)braket
op_eq
l_int|0xFF
)paren
op_logical_and
(paren
(paren
id|addr-&gt;s6_addr
(braket
l_int|1
)braket
op_eq
l_int|0x01
)paren
op_logical_or
(paren
id|addr-&gt;s6_addr
(braket
l_int|1
)braket
op_eq
l_int|0x02
)paren
)paren
op_logical_and
(paren
id|addr-&gt;s6_addr16
(braket
l_int|1
)braket
op_eq
l_int|0
)paren
op_logical_and
(paren
id|addr-&gt;s6_addr32
(braket
l_int|1
)braket
op_eq
l_int|0
)paren
op_logical_and
(paren
id|addr-&gt;s6_addr32
(braket
l_int|2
)braket
op_eq
l_int|0
)paren
op_logical_and
(paren
id|addr-&gt;s6_addr16
(braket
l_int|6
)braket
op_eq
l_int|0
)paren
op_logical_and
(paren
id|addr-&gt;s6_addr
(braket
l_int|15
)braket
op_eq
l_int|1
)paren
)paren
op_logical_or
(paren
(paren
id|addr-&gt;s6_addr
(braket
l_int|0
)braket
op_eq
l_int|0xFF
)paren
op_logical_and
(paren
id|addr-&gt;s6_addr
(braket
l_int|1
)braket
op_eq
l_int|0x02
)paren
op_logical_and
(paren
id|addr-&gt;s6_addr16
(braket
l_int|1
)braket
op_eq
l_int|0
)paren
op_logical_and
(paren
id|addr-&gt;s6_addr32
(braket
l_int|1
)braket
op_eq
l_int|0
)paren
op_logical_and
(paren
id|addr-&gt;s6_addr16
(braket
l_int|4
)braket
op_eq
l_int|0
)paren
op_logical_and
(paren
id|addr-&gt;s6_addr
(braket
l_int|10
)braket
op_eq
l_int|0
)paren
op_logical_and
(paren
id|addr-&gt;s6_addr
(braket
l_int|11
)braket
op_eq
l_int|1
)paren
op_logical_and
(paren
id|addr-&gt;s6_addr
(braket
l_int|12
)braket
op_eq
l_int|0xff
)paren
)paren
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
l_int|0x01
suffix:semicolon
id|buf
(braket
l_int|3
)braket
op_assign
l_int|0x00
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
multiline_comment|/* All routers FF0x::2 */
)brace
r_else
r_if
c_cond
(paren
(paren
id|addr-&gt;s6_addr
(braket
l_int|0
)braket
op_eq
l_int|0xff
)paren
op_logical_and
(paren
(paren
id|addr-&gt;s6_addr
(braket
l_int|1
)braket
op_amp
l_int|0xF0
)paren
op_eq
l_int|0
)paren
op_logical_and
(paren
id|addr-&gt;s6_addr16
(braket
l_int|1
)braket
op_eq
l_int|0
)paren
op_logical_and
(paren
id|addr-&gt;s6_addr32
(braket
l_int|1
)braket
op_eq
l_int|0
)paren
op_logical_and
(paren
id|addr-&gt;s6_addr32
(braket
l_int|2
)braket
op_eq
l_int|0
)paren
op_logical_and
(paren
id|addr-&gt;s6_addr16
(braket
l_int|6
)braket
op_eq
l_int|0
)paren
op_logical_and
(paren
id|addr-&gt;s6_addr
(braket
l_int|15
)braket
op_eq
l_int|2
)paren
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
l_int|0x02
suffix:semicolon
id|buf
(braket
l_int|3
)braket
op_assign
l_int|0x00
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
r_else
(brace
r_int
r_char
id|i
suffix:semicolon
id|i
op_assign
id|addr-&gt;s6_addr
(braket
l_int|15
)braket
op_amp
l_int|7
suffix:semicolon
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
l_int|0x01
op_lshift
id|i
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
)brace
DECL|function|ipv6_arcnet_mc_map
r_static
r_inline
r_void
id|ipv6_arcnet_mc_map
c_func
(paren
r_const
r_struct
id|in6_addr
op_star
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
l_int|0x00
suffix:semicolon
)brace
macro_line|#endif
macro_line|#endif
eof
