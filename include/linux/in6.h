multiline_comment|/*&n; *&t;Types and definitions for AF_INET6 &n; *&t;Linux INET6 implementation &n; *&n; *&t;Authors:&n; *&t;Pedro Roque&t;&t;&lt;roque@di.fc.ul.pt&gt;&t;&n; *&n; *&t;Sources:&n; *&t;IPv6 Program Interfaces for BSD Systems&n; *      &lt;draft-ietf-ipngwg-bsd-api-05.txt&gt;&n; *&n; *&t;Advanced Sockets API for IPv6&n; *&t;&lt;draft-stevens-advanced-api-00.txt&gt;&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *      modify it under the terms of the GNU General Public License&n; *      as published by the Free Software Foundation; either version&n; *      2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _LINUX_IN6_H
DECL|macro|_LINUX_IN6_H
mdefine_line|#define _LINUX_IN6_H
macro_line|#include &lt;linux/types.h&gt;
multiline_comment|/*&n; *&t;IPv6 address structure&n; */
DECL|struct|in6_addr
r_struct
id|in6_addr
(brace
r_union
(brace
DECL|member|u6_addr8
id|__u8
id|u6_addr8
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|u6_addr16
id|__u16
id|u6_addr16
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|u6_addr32
id|__u32
id|u6_addr32
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|in6_u
)brace
id|in6_u
suffix:semicolon
DECL|macro|s6_addr
mdefine_line|#define s6_addr&t;&t;&t;in6_u.u6_addr8
DECL|macro|s6_addr16
mdefine_line|#define s6_addr16&t;&t;in6_u.u6_addr16
DECL|macro|s6_addr32
mdefine_line|#define s6_addr32&t;&t;in6_u.u6_addr32
)brace
suffix:semicolon
DECL|struct|sockaddr_in6
r_struct
id|sockaddr_in6
(brace
DECL|member|sin6_family
r_int
r_int
r_int
id|sin6_family
suffix:semicolon
multiline_comment|/* AF_INET6 */
DECL|member|sin6_port
id|__u16
id|sin6_port
suffix:semicolon
multiline_comment|/* Transport layer port # */
DECL|member|sin6_flowinfo
id|__u32
id|sin6_flowinfo
suffix:semicolon
multiline_comment|/* IPv6 flow information */
DECL|member|sin6_addr
r_struct
id|in6_addr
id|sin6_addr
suffix:semicolon
multiline_comment|/* IPv6 address */
DECL|member|sin6_scope_id
id|__u32
id|sin6_scope_id
suffix:semicolon
multiline_comment|/* scope id (new in RFC2553) */
)brace
suffix:semicolon
DECL|struct|ipv6_mreq
r_struct
id|ipv6_mreq
(brace
multiline_comment|/* IPv6 multicast address of group */
DECL|member|ipv6mr_multiaddr
r_struct
id|in6_addr
id|ipv6mr_multiaddr
suffix:semicolon
multiline_comment|/* local IPv6 address of interface */
DECL|member|ipv6mr_ifindex
r_int
id|ipv6mr_ifindex
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|in6_flowlabel_req
r_struct
id|in6_flowlabel_req
(brace
DECL|member|flr_dst
r_struct
id|in6_addr
id|flr_dst
suffix:semicolon
DECL|member|flr_label
id|__u32
id|flr_label
suffix:semicolon
DECL|member|flr_action
id|__u8
id|flr_action
suffix:semicolon
DECL|member|flr_share
id|__u8
id|flr_share
suffix:semicolon
DECL|member|flr_flags
id|__u16
id|flr_flags
suffix:semicolon
DECL|member|flr_expires
id|__u16
id|flr_expires
suffix:semicolon
DECL|member|flr_linger
id|__u16
id|flr_linger
suffix:semicolon
DECL|member|__flr_pad
id|__u32
id|__flr_pad
suffix:semicolon
multiline_comment|/* Options in format of IPV6_PKTOPTIONS */
)brace
suffix:semicolon
DECL|macro|IPV6_FL_A_GET
mdefine_line|#define IPV6_FL_A_GET&t;0
DECL|macro|IPV6_FL_A_PUT
mdefine_line|#define IPV6_FL_A_PUT&t;1
DECL|macro|IPV6_FL_A_RENEW
mdefine_line|#define IPV6_FL_A_RENEW&t;2
DECL|macro|IPV6_FL_F_CREATE
mdefine_line|#define IPV6_FL_F_CREATE&t;1
DECL|macro|IPV6_FL_F_EXCL
mdefine_line|#define IPV6_FL_F_EXCL&t;&t;2
DECL|macro|IPV6_FL_S_NONE
mdefine_line|#define IPV6_FL_S_NONE&t;&t;0
DECL|macro|IPV6_FL_S_EXCL
mdefine_line|#define IPV6_FL_S_EXCL&t;&t;1
DECL|macro|IPV6_FL_S_PROCESS
mdefine_line|#define IPV6_FL_S_PROCESS&t;2
DECL|macro|IPV6_FL_S_USER
mdefine_line|#define IPV6_FL_S_USER&t;&t;3
DECL|macro|IPV6_FL_S_ANY
mdefine_line|#define IPV6_FL_S_ANY&t;&t;255
multiline_comment|/*&n; *&t;Bitmask constant declarations to help applications select out the &n; *&t;flow label and priority fields.&n; *&n; *&t;Note that this are in host byte order while the flowinfo field of&n; *&t;sockaddr_in6 is in network byte order.&n; */
DECL|macro|IPV6_FLOWINFO_FLOWLABEL
mdefine_line|#define IPV6_FLOWINFO_FLOWLABEL&t;&t;0x000fffff
DECL|macro|IPV6_FLOWINFO_PRIORITY
mdefine_line|#define IPV6_FLOWINFO_PRIORITY&t;&t;0x0ff00000
multiline_comment|/* These defintions are obsolete */
DECL|macro|IPV6_PRIORITY_UNCHARACTERIZED
mdefine_line|#define IPV6_PRIORITY_UNCHARACTERIZED&t;0x0000
DECL|macro|IPV6_PRIORITY_FILLER
mdefine_line|#define IPV6_PRIORITY_FILLER&t;&t;0x0100
DECL|macro|IPV6_PRIORITY_UNATTENDED
mdefine_line|#define IPV6_PRIORITY_UNATTENDED&t;0x0200
DECL|macro|IPV6_PRIORITY_RESERVED1
mdefine_line|#define IPV6_PRIORITY_RESERVED1&t;&t;0x0300
DECL|macro|IPV6_PRIORITY_BULK
mdefine_line|#define IPV6_PRIORITY_BULK&t;&t;0x0400
DECL|macro|IPV6_PRIORITY_RESERVED2
mdefine_line|#define IPV6_PRIORITY_RESERVED2&t;&t;0x0500
DECL|macro|IPV6_PRIORITY_INTERACTIVE
mdefine_line|#define IPV6_PRIORITY_INTERACTIVE&t;0x0600
DECL|macro|IPV6_PRIORITY_CONTROL
mdefine_line|#define IPV6_PRIORITY_CONTROL&t;&t;0x0700
DECL|macro|IPV6_PRIORITY_8
mdefine_line|#define IPV6_PRIORITY_8&t;&t;&t;0x0800
DECL|macro|IPV6_PRIORITY_9
mdefine_line|#define IPV6_PRIORITY_9&t;&t;&t;0x0900
DECL|macro|IPV6_PRIORITY_10
mdefine_line|#define IPV6_PRIORITY_10&t;&t;0x0a00
DECL|macro|IPV6_PRIORITY_11
mdefine_line|#define IPV6_PRIORITY_11&t;&t;0x0b00
DECL|macro|IPV6_PRIORITY_12
mdefine_line|#define IPV6_PRIORITY_12&t;&t;0x0c00
DECL|macro|IPV6_PRIORITY_13
mdefine_line|#define IPV6_PRIORITY_13&t;&t;0x0d00
DECL|macro|IPV6_PRIORITY_14
mdefine_line|#define IPV6_PRIORITY_14&t;&t;0x0e00
DECL|macro|IPV6_PRIORITY_15
mdefine_line|#define IPV6_PRIORITY_15&t;&t;0x0f00
multiline_comment|/*&n; *&t;IPV6 extension headers&n; */
DECL|macro|IPPROTO_HOPOPTS
mdefine_line|#define IPPROTO_HOPOPTS&t;&t;0&t;/* IPv6 hop-by-hop options&t;*/
DECL|macro|IPPROTO_ROUTING
mdefine_line|#define IPPROTO_ROUTING&t;&t;43&t;/* IPv6 routing header&t;&t;*/
DECL|macro|IPPROTO_FRAGMENT
mdefine_line|#define IPPROTO_FRAGMENT&t;44&t;/* IPv6 fragmentation header&t;*/
DECL|macro|IPPROTO_ICMPV6
mdefine_line|#define IPPROTO_ICMPV6&t;&t;58&t;/* ICMPv6&t;&t;&t;*/
DECL|macro|IPPROTO_NONE
mdefine_line|#define IPPROTO_NONE&t;&t;59&t;/* IPv6 no next header&t;&t;*/
DECL|macro|IPPROTO_DSTOPTS
mdefine_line|#define IPPROTO_DSTOPTS&t;&t;60&t;/* IPv6 destination options&t;*/
multiline_comment|/*&n; *&t;IPv6 TLV options.&n; */
DECL|macro|IPV6_TLV_PAD0
mdefine_line|#define IPV6_TLV_PAD0&t;&t;0
DECL|macro|IPV6_TLV_PADN
mdefine_line|#define IPV6_TLV_PADN&t;&t;1
DECL|macro|IPV6_TLV_ROUTERALERT
mdefine_line|#define IPV6_TLV_ROUTERALERT&t;5
DECL|macro|IPV6_TLV_JUMBO
mdefine_line|#define IPV6_TLV_JUMBO&t;&t;194
multiline_comment|/*&n; *&t;IPV6 socket options&n; */
DECL|macro|IPV6_ADDRFORM
mdefine_line|#define IPV6_ADDRFORM&t;&t;1
DECL|macro|IPV6_PKTINFO
mdefine_line|#define IPV6_PKTINFO&t;&t;2
DECL|macro|IPV6_HOPOPTS
mdefine_line|#define IPV6_HOPOPTS&t;&t;3
DECL|macro|IPV6_DSTOPTS
mdefine_line|#define IPV6_DSTOPTS&t;&t;4
DECL|macro|IPV6_RTHDR
mdefine_line|#define IPV6_RTHDR&t;&t;5
DECL|macro|IPV6_PKTOPTIONS
mdefine_line|#define IPV6_PKTOPTIONS&t;&t;6
DECL|macro|IPV6_CHECKSUM
mdefine_line|#define IPV6_CHECKSUM&t;&t;7
DECL|macro|IPV6_HOPLIMIT
mdefine_line|#define IPV6_HOPLIMIT&t;&t;8
DECL|macro|IPV6_NEXTHOP
mdefine_line|#define IPV6_NEXTHOP&t;&t;9
DECL|macro|IPV6_AUTHHDR
mdefine_line|#define IPV6_AUTHHDR&t;&t;10
DECL|macro|IPV6_FLOWINFO
mdefine_line|#define IPV6_FLOWINFO&t;&t;11
DECL|macro|IPV6_UNICAST_HOPS
mdefine_line|#define IPV6_UNICAST_HOPS&t;16
DECL|macro|IPV6_MULTICAST_IF
mdefine_line|#define IPV6_MULTICAST_IF&t;17
DECL|macro|IPV6_MULTICAST_HOPS
mdefine_line|#define IPV6_MULTICAST_HOPS&t;18
DECL|macro|IPV6_MULTICAST_LOOP
mdefine_line|#define IPV6_MULTICAST_LOOP&t;19
DECL|macro|IPV6_ADD_MEMBERSHIP
mdefine_line|#define IPV6_ADD_MEMBERSHIP&t;20
DECL|macro|IPV6_DROP_MEMBERSHIP
mdefine_line|#define IPV6_DROP_MEMBERSHIP&t;21
DECL|macro|IPV6_ROUTER_ALERT
mdefine_line|#define IPV6_ROUTER_ALERT&t;22
DECL|macro|IPV6_MTU_DISCOVER
mdefine_line|#define IPV6_MTU_DISCOVER&t;23
DECL|macro|IPV6_MTU
mdefine_line|#define IPV6_MTU&t;&t;24
DECL|macro|IPV6_RECVERR
mdefine_line|#define IPV6_RECVERR&t;&t;25
multiline_comment|/* IPV6_MTU_DISCOVER values */
DECL|macro|IPV6_PMTUDISC_DONT
mdefine_line|#define IPV6_PMTUDISC_DONT&t;&t;0
DECL|macro|IPV6_PMTUDISC_WANT
mdefine_line|#define IPV6_PMTUDISC_WANT&t;&t;1
DECL|macro|IPV6_PMTUDISC_DO
mdefine_line|#define IPV6_PMTUDISC_DO&t;&t;2
multiline_comment|/* Flowlabel */
DECL|macro|IPV6_FLOWLABEL_MGR
mdefine_line|#define IPV6_FLOWLABEL_MGR&t;32
DECL|macro|IPV6_FLOWINFO_SEND
mdefine_line|#define IPV6_FLOWINFO_SEND&t;33
macro_line|#endif
eof
