macro_line|#ifndef __LINUX_RTNETLINK_H
DECL|macro|__LINUX_RTNETLINK_H
mdefine_line|#define __LINUX_RTNETLINK_H
macro_line|#include &lt;linux/netlink.h&gt;
DECL|macro|RTNL_DEBUG
mdefine_line|#define RTNL_DEBUG 1
multiline_comment|/****&n; *&t;&t;Routing/neighbour discovery messages.&n; ****/
multiline_comment|/* Types of messages */
DECL|macro|RTM_BASE
mdefine_line|#define RTM_BASE&t;0x10
DECL|macro|RTM_NEWLINK
mdefine_line|#define&t;RTM_NEWLINK&t;(RTM_BASE+0)
DECL|macro|RTM_DELLINK
mdefine_line|#define&t;RTM_DELLINK&t;(RTM_BASE+1)
DECL|macro|RTM_GETLINK
mdefine_line|#define&t;RTM_GETLINK&t;(RTM_BASE+2)
DECL|macro|RTM_NEWADDR
mdefine_line|#define&t;RTM_NEWADDR&t;(RTM_BASE+4)
DECL|macro|RTM_DELADDR
mdefine_line|#define&t;RTM_DELADDR&t;(RTM_BASE+5)
DECL|macro|RTM_GETADDR
mdefine_line|#define&t;RTM_GETADDR&t;(RTM_BASE+6)
DECL|macro|RTM_NEWROUTE
mdefine_line|#define&t;RTM_NEWROUTE&t;(RTM_BASE+8)
DECL|macro|RTM_DELROUTE
mdefine_line|#define&t;RTM_DELROUTE&t;(RTM_BASE+9)
DECL|macro|RTM_GETROUTE
mdefine_line|#define&t;RTM_GETROUTE&t;(RTM_BASE+10)
DECL|macro|RTM_NEWNEIGH
mdefine_line|#define&t;RTM_NEWNEIGH&t;(RTM_BASE+12)
DECL|macro|RTM_DELNEIGH
mdefine_line|#define&t;RTM_DELNEIGH&t;(RTM_BASE+13)
DECL|macro|RTM_GETNEIGH
mdefine_line|#define&t;RTM_GETNEIGH&t;(RTM_BASE+14)
DECL|macro|RTM_NEWRULE
mdefine_line|#define&t;RTM_NEWRULE&t;(RTM_BASE+16)
DECL|macro|RTM_DELRULE
mdefine_line|#define&t;RTM_DELRULE&t;(RTM_BASE+17)
DECL|macro|RTM_GETRULE
mdefine_line|#define&t;RTM_GETRULE&t;(RTM_BASE+18)
DECL|macro|RTM_NEWQDISC
mdefine_line|#define&t;RTM_NEWQDISC&t;(RTM_BASE+20)
DECL|macro|RTM_DELQDISC
mdefine_line|#define&t;RTM_DELQDISC&t;(RTM_BASE+21)
DECL|macro|RTM_GETQDISC
mdefine_line|#define&t;RTM_GETQDISC&t;(RTM_BASE+22)
DECL|macro|RTM_NEWTCLASS
mdefine_line|#define&t;RTM_NEWTCLASS&t;(RTM_BASE+24)
DECL|macro|RTM_DELTCLASS
mdefine_line|#define&t;RTM_DELTCLASS&t;(RTM_BASE+25)
DECL|macro|RTM_GETTCLASS
mdefine_line|#define&t;RTM_GETTCLASS&t;(RTM_BASE+26)
DECL|macro|RTM_NEWTFILTER
mdefine_line|#define&t;RTM_NEWTFILTER&t;(RTM_BASE+28)
DECL|macro|RTM_DELTFILTER
mdefine_line|#define&t;RTM_DELTFILTER&t;(RTM_BASE+29)
DECL|macro|RTM_GETTFILTER
mdefine_line|#define&t;RTM_GETTFILTER&t;(RTM_BASE+30)
DECL|macro|RTM_MAX
mdefine_line|#define&t;RTM_MAX&t;&t;(RTM_BASE+31)
multiline_comment|/* &n;   Generic structure for encapsulation optional route information.&n;   It is reminiscent of sockaddr, but with sa_family replaced&n;   with attribute type.&n; */
DECL|struct|rtattr
r_struct
id|rtattr
(brace
DECL|member|rta_len
r_int
r_int
id|rta_len
suffix:semicolon
DECL|member|rta_type
r_int
r_int
id|rta_type
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Macros to handle rtattributes */
DECL|macro|RTA_ALIGNTO
mdefine_line|#define RTA_ALIGNTO&t;4
DECL|macro|RTA_ALIGN
mdefine_line|#define RTA_ALIGN(len) ( ((len)+RTA_ALIGNTO-1) &amp; ~(RTA_ALIGNTO-1) )
DECL|macro|RTA_OK
mdefine_line|#define RTA_OK(rta,len) ((len) &gt; 0 &amp;&amp; (rta)-&gt;rta_len &gt;= sizeof(struct rtattr) &amp;&amp; &bslash;&n;&t;&t;&t; (rta)-&gt;rta_len &lt;= (len))
DECL|macro|RTA_NEXT
mdefine_line|#define RTA_NEXT(rta,attrlen)&t;((attrlen) -= RTA_ALIGN((rta)-&gt;rta_len), &bslash;&n;&t;&t;&t;&t; (struct rtattr*)(((char*)(rta)) + RTA_ALIGN((rta)-&gt;rta_len)))
DECL|macro|RTA_LENGTH
mdefine_line|#define RTA_LENGTH(len)&t;(RTA_ALIGN(sizeof(struct rtattr)) + (len))
DECL|macro|RTA_SPACE
mdefine_line|#define RTA_SPACE(len)&t;RTA_ALIGN(RTA_LENGTH(len))
DECL|macro|RTA_DATA
mdefine_line|#define RTA_DATA(rta)   ((void*)(((char*)(rta)) + RTA_LENGTH(0)))
DECL|macro|RTA_PAYLOAD
mdefine_line|#define RTA_PAYLOAD(rta) ((int)((rta)-&gt;rta_len) - RTA_LENGTH(0))
multiline_comment|/******************************************************************************&n; *&t;&t;Definitions used in routing table administation.&n; ****/
DECL|struct|rtmsg
r_struct
id|rtmsg
(brace
DECL|member|rtm_family
r_int
r_char
id|rtm_family
suffix:semicolon
DECL|member|rtm_dst_len
r_int
r_char
id|rtm_dst_len
suffix:semicolon
DECL|member|rtm_src_len
r_int
r_char
id|rtm_src_len
suffix:semicolon
DECL|member|rtm_tos
r_int
r_char
id|rtm_tos
suffix:semicolon
DECL|member|rtm_table
r_int
r_char
id|rtm_table
suffix:semicolon
multiline_comment|/* Routing table id */
DECL|member|rtm_protocol
r_int
r_char
id|rtm_protocol
suffix:semicolon
multiline_comment|/* Routing protocol; see below&t;*/
DECL|member|rtm_scope
r_int
r_char
id|rtm_scope
suffix:semicolon
multiline_comment|/* See below */
DECL|member|rtm_type
r_int
r_char
id|rtm_type
suffix:semicolon
multiline_comment|/* See below&t;*/
DECL|member|rtm_flags
r_int
id|rtm_flags
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* rtm_type */
r_enum
(brace
DECL|enumerator|RTN_UNSPEC
id|RTN_UNSPEC
comma
DECL|enumerator|RTN_UNICAST
id|RTN_UNICAST
comma
multiline_comment|/* Gateway or direct route&t;*/
DECL|enumerator|RTN_LOCAL
id|RTN_LOCAL
comma
multiline_comment|/* Accept locally&t;&t;*/
DECL|enumerator|RTN_BROADCAST
id|RTN_BROADCAST
comma
multiline_comment|/* Accept locally as broadcast,&n;&t;&t;&t;&t;   send as broadcast */
DECL|enumerator|RTN_ANYCAST
id|RTN_ANYCAST
comma
multiline_comment|/* Accept locally as broadcast,&n;&t;&t;&t;&t;   but send as unicast */
DECL|enumerator|RTN_MULTICAST
id|RTN_MULTICAST
comma
multiline_comment|/* Multicast route&t;&t;*/
DECL|enumerator|RTN_BLACKHOLE
id|RTN_BLACKHOLE
comma
multiline_comment|/* Drop&t;&t;&t;&t;*/
DECL|enumerator|RTN_UNREACHABLE
id|RTN_UNREACHABLE
comma
multiline_comment|/* Destination is unreachable   */
DECL|enumerator|RTN_PROHIBIT
id|RTN_PROHIBIT
comma
multiline_comment|/* Administratively prohibited&t;*/
DECL|enumerator|RTN_THROW
id|RTN_THROW
comma
multiline_comment|/* Not in this table&t;&t;*/
DECL|enumerator|RTN_NAT
id|RTN_NAT
comma
multiline_comment|/* Translate this address&t;*/
DECL|enumerator|RTN_XRESOLVE
id|RTN_XRESOLVE
comma
multiline_comment|/* Use external resolver&t;*/
)brace
suffix:semicolon
DECL|macro|RTN_MAX
mdefine_line|#define RTN_MAX RTN_XRESOLVE
multiline_comment|/* rtm_protocol */
DECL|macro|RTPROT_UNSPEC
mdefine_line|#define RTPROT_UNSPEC&t;0
DECL|macro|RTPROT_REDIRECT
mdefine_line|#define RTPROT_REDIRECT&t;1&t;/* Route installed by ICMP redirects;&n;&t;&t;&t;&t;   not used by current IPv4 */
DECL|macro|RTPROT_KERNEL
mdefine_line|#define RTPROT_KERNEL&t;2&t;/* Route installed by kernel&t;&t;*/
DECL|macro|RTPROT_BOOT
mdefine_line|#define RTPROT_BOOT&t;3&t;/* Route installed during boot&t;&t;*/
DECL|macro|RTPROT_STATIC
mdefine_line|#define RTPROT_STATIC&t;4&t;/* Route installed by administrator&t;*/
multiline_comment|/* Values of protocol &gt;= RTPROT_STATIC are not interpreted by kernel;&n;   they just passed from user and back as is.&n;   It will be used by hypothetical multiple routing daemons.&n;   Note that protocol values should be standardized in order to&n;   avoid conflicts.&n; */
DECL|macro|RTPROT_GATED
mdefine_line|#define RTPROT_GATED&t;8&t;/* Apparently, GateD */
DECL|macro|RTPROT_RA
mdefine_line|#define RTPROT_RA&t;9&t;/* RDISC/ND router advertisments */
DECL|macro|RTPROT_MRT
mdefine_line|#define RTPROT_MRT&t;10&t;/* Merit MRT */
DECL|macro|RTPROT_ZEBRA
mdefine_line|#define RTPROT_ZEBRA&t;11&t;/* Zebra */
DECL|macro|RTPROT_BIRD
mdefine_line|#define RTPROT_BIRD&t;12&t;/* BIRD */
DECL|macro|RTPROT_DNROUTED
mdefine_line|#define RTPROT_DNROUTED&t;13&t;/* DECnet routing daemon */
multiline_comment|/* rtm_scope&n;&n;   Really it is not scope, but sort of distance to the destination.&n;   NOWHERE are reserved for not existing destinations, HOST is our&n;   local addresses, LINK are destinations, located on directly attached&n;   link and UNIVERSE is everywhere in the Universe.&n;&n;   Intermediate values are also possible f.e. interior routes&n;   could be assigned a value between UNIVERSE and LINK.&n;*/
DECL|enum|rt_scope_t
r_enum
id|rt_scope_t
(brace
DECL|enumerator|RT_SCOPE_UNIVERSE
id|RT_SCOPE_UNIVERSE
op_assign
l_int|0
comma
multiline_comment|/* User defined values  */
DECL|enumerator|RT_SCOPE_SITE
id|RT_SCOPE_SITE
op_assign
l_int|200
comma
DECL|enumerator|RT_SCOPE_LINK
id|RT_SCOPE_LINK
op_assign
l_int|253
comma
DECL|enumerator|RT_SCOPE_HOST
id|RT_SCOPE_HOST
op_assign
l_int|254
comma
DECL|enumerator|RT_SCOPE_NOWHERE
id|RT_SCOPE_NOWHERE
op_assign
l_int|255
)brace
suffix:semicolon
multiline_comment|/* rtm_flags */
DECL|macro|RTM_F_NOTIFY
mdefine_line|#define RTM_F_NOTIFY&t;&t;0x100&t;/* Notify user of route change&t;*/
DECL|macro|RTM_F_CLONED
mdefine_line|#define RTM_F_CLONED&t;&t;0x200&t;/* This route is cloned&t;&t;*/
DECL|macro|RTM_F_EQUALIZE
mdefine_line|#define RTM_F_EQUALIZE&t;&t;0x400&t;/* Multipath equalizer: NI&t;*/
multiline_comment|/* Reserved table identifiers */
DECL|enum|rt_class_t
r_enum
id|rt_class_t
(brace
DECL|enumerator|RT_TABLE_UNSPEC
id|RT_TABLE_UNSPEC
op_assign
l_int|0
comma
multiline_comment|/* User defined values */
DECL|enumerator|RT_TABLE_DEFAULT
id|RT_TABLE_DEFAULT
op_assign
l_int|253
comma
DECL|enumerator|RT_TABLE_MAIN
id|RT_TABLE_MAIN
op_assign
l_int|254
comma
DECL|enumerator|RT_TABLE_LOCAL
id|RT_TABLE_LOCAL
op_assign
l_int|255
)brace
suffix:semicolon
DECL|macro|RT_TABLE_MAX
mdefine_line|#define RT_TABLE_MAX RT_TABLE_LOCAL
multiline_comment|/* Routing message attributes */
DECL|enum|rtattr_type_t
r_enum
id|rtattr_type_t
(brace
DECL|enumerator|RTA_UNSPEC
id|RTA_UNSPEC
comma
DECL|enumerator|RTA_DST
id|RTA_DST
comma
DECL|enumerator|RTA_SRC
id|RTA_SRC
comma
DECL|enumerator|RTA_IIF
id|RTA_IIF
comma
DECL|enumerator|RTA_OIF
id|RTA_OIF
comma
DECL|enumerator|RTA_GATEWAY
id|RTA_GATEWAY
comma
DECL|enumerator|RTA_PRIORITY
id|RTA_PRIORITY
comma
DECL|enumerator|RTA_PREFSRC
id|RTA_PREFSRC
comma
DECL|enumerator|RTA_METRICS
id|RTA_METRICS
comma
DECL|enumerator|RTA_MULTIPATH
id|RTA_MULTIPATH
comma
DECL|enumerator|RTA_PROTOINFO
id|RTA_PROTOINFO
comma
DECL|enumerator|RTA_FLOW
id|RTA_FLOW
comma
DECL|enumerator|RTA_CACHEINFO
id|RTA_CACHEINFO
)brace
suffix:semicolon
DECL|macro|RTA_MAX
mdefine_line|#define RTA_MAX RTA_CACHEINFO
DECL|macro|RTM_RTA
mdefine_line|#define RTM_RTA(r)  ((struct rtattr*)(((char*)(r)) + NLMSG_ALIGN(sizeof(struct rtmsg))))
DECL|macro|RTM_PAYLOAD
mdefine_line|#define RTM_PAYLOAD(n) NLMSG_PAYLOAD(n,sizeof(struct rtmsg))
multiline_comment|/* RTM_MULTIPATH --- array of struct rtnexthop.&n; *&n; * &quot;struct rtnexthop&quot; describres all necessary nexthop information,&n; * i.e. parameters of path to a destination via this nextop.&n; *&n; * At the moment it is impossible to set different prefsrc, mtu, window&n; * and rtt for different paths from multipath.&n; */
DECL|struct|rtnexthop
r_struct
id|rtnexthop
(brace
DECL|member|rtnh_len
r_int
r_int
id|rtnh_len
suffix:semicolon
DECL|member|rtnh_flags
r_int
r_char
id|rtnh_flags
suffix:semicolon
DECL|member|rtnh_hops
r_int
r_char
id|rtnh_hops
suffix:semicolon
DECL|member|rtnh_ifindex
r_int
id|rtnh_ifindex
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* rtnh_flags */
DECL|macro|RTNH_F_DEAD
mdefine_line|#define RTNH_F_DEAD&t;&t;1&t;/* Nexthop is dead (used by multipath)&t;*/
DECL|macro|RTNH_F_PERVASIVE
mdefine_line|#define RTNH_F_PERVASIVE&t;2&t;/* Do recursive gateway lookup&t;*/
DECL|macro|RTNH_F_ONLINK
mdefine_line|#define RTNH_F_ONLINK&t;&t;4&t;/* Gateway is forced on link&t;*/
multiline_comment|/* Macros to handle hexthops */
DECL|macro|RTNH_ALIGNTO
mdefine_line|#define RTNH_ALIGNTO&t;4
DECL|macro|RTNH_ALIGN
mdefine_line|#define RTNH_ALIGN(len) ( ((len)+RTNH_ALIGNTO-1) &amp; ~(RTNH_ALIGNTO-1) )
DECL|macro|RTNH_OK
mdefine_line|#define RTNH_OK(rtnh,len) ((rtnh)-&gt;rtnh_len &gt;= sizeof(struct rtnexthop) &amp;&amp; &bslash;&n;&t;&t;&t;   ((int)(rtnh)-&gt;rtnh_len) &lt;= (len))
DECL|macro|RTNH_NEXT
mdefine_line|#define RTNH_NEXT(rtnh)&t;((struct rtnexthop*)(((char*)(rtnh)) + RTNH_ALIGN((rtnh)-&gt;rtnh_len)))
DECL|macro|RTNH_LENGTH
mdefine_line|#define RTNH_LENGTH(len) (RTNH_ALIGN(sizeof(struct rtnexthop)) + (len))
DECL|macro|RTNH_SPACE
mdefine_line|#define RTNH_SPACE(len)&t;RTNH_ALIGN(RTNH_LENGTH(len))
DECL|macro|RTNH_DATA
mdefine_line|#define RTNH_DATA(rtnh)   ((struct rtattr*)(((char*)(rtnh)) + RTNH_LENGTH(0)))
multiline_comment|/* RTM_CACHEINFO */
DECL|struct|rta_cacheinfo
r_struct
id|rta_cacheinfo
(brace
DECL|member|rta_clntref
id|__u32
id|rta_clntref
suffix:semicolon
DECL|member|rta_lastuse
id|__u32
id|rta_lastuse
suffix:semicolon
DECL|member|rta_expires
id|__s32
id|rta_expires
suffix:semicolon
DECL|member|rta_error
id|__u32
id|rta_error
suffix:semicolon
DECL|member|rta_used
id|__u32
id|rta_used
suffix:semicolon
DECL|macro|RTNETLINK_HAVE_PEERINFO
mdefine_line|#define RTNETLINK_HAVE_PEERINFO 1
DECL|member|rta_id
id|__u32
id|rta_id
suffix:semicolon
DECL|member|rta_ts
id|__u32
id|rta_ts
suffix:semicolon
DECL|member|rta_tsage
id|__u32
id|rta_tsage
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* RTM_METRICS --- array of struct rtattr with types of RTAX_* */
r_enum
(brace
DECL|enumerator|RTAX_UNSPEC
id|RTAX_UNSPEC
comma
DECL|macro|RTAX_UNSPEC
mdefine_line|#define RTAX_UNSPEC RTAX_UNSPEC
DECL|enumerator|RTAX_LOCK
id|RTAX_LOCK
comma
DECL|macro|RTAX_LOCK
mdefine_line|#define RTAX_LOCK RTAX_LOCK
DECL|enumerator|RTAX_MTU
id|RTAX_MTU
comma
DECL|macro|RTAX_MTU
mdefine_line|#define RTAX_MTU RTAX_MTU
DECL|enumerator|RTAX_WINDOW
id|RTAX_WINDOW
comma
DECL|macro|RTAX_WINDOW
mdefine_line|#define RTAX_WINDOW RTAX_WINDOW
DECL|enumerator|RTAX_RTT
id|RTAX_RTT
comma
DECL|macro|RTAX_RTT
mdefine_line|#define RTAX_RTT RTAX_RTT
DECL|enumerator|RTAX_RTTVAR
id|RTAX_RTTVAR
comma
DECL|macro|RTAX_RTTVAR
mdefine_line|#define RTAX_RTTVAR RTAX_RTTVAR
DECL|enumerator|RTAX_SSTHRESH
id|RTAX_SSTHRESH
comma
DECL|macro|RTAX_SSTHRESH
mdefine_line|#define RTAX_SSTHRESH RTAX_SSTHRESH
DECL|enumerator|RTAX_CWND
id|RTAX_CWND
comma
DECL|macro|RTAX_CWND
mdefine_line|#define RTAX_CWND RTAX_CWND
DECL|enumerator|RTAX_ADVMSS
id|RTAX_ADVMSS
comma
DECL|macro|RTAX_ADVMSS
mdefine_line|#define RTAX_ADVMSS RTAX_ADVMSS
DECL|enumerator|RTAX_REORDERING
id|RTAX_REORDERING
comma
DECL|macro|RTAX_REORDERING
mdefine_line|#define RTAX_REORDERING RTAX_REORDERING
)brace
suffix:semicolon
DECL|macro|RTAX_MAX
mdefine_line|#define RTAX_MAX RTAX_REORDERING
multiline_comment|/*********************************************************&n; *&t;&t;Interface address.&n; ****/
DECL|struct|ifaddrmsg
r_struct
id|ifaddrmsg
(brace
DECL|member|ifa_family
r_int
r_char
id|ifa_family
suffix:semicolon
DECL|member|ifa_prefixlen
r_int
r_char
id|ifa_prefixlen
suffix:semicolon
multiline_comment|/* The prefix length&t;&t;*/
DECL|member|ifa_flags
r_int
r_char
id|ifa_flags
suffix:semicolon
multiline_comment|/* Flags&t;&t;&t;*/
DECL|member|ifa_scope
r_int
r_char
id|ifa_scope
suffix:semicolon
multiline_comment|/* See above&t;&t;&t;*/
DECL|member|ifa_index
r_int
id|ifa_index
suffix:semicolon
multiline_comment|/* Link index&t;&t;&t;*/
)brace
suffix:semicolon
r_enum
(brace
DECL|enumerator|IFA_UNSPEC
id|IFA_UNSPEC
comma
DECL|enumerator|IFA_ADDRESS
id|IFA_ADDRESS
comma
DECL|enumerator|IFA_LOCAL
id|IFA_LOCAL
comma
DECL|enumerator|IFA_LABEL
id|IFA_LABEL
comma
DECL|enumerator|IFA_BROADCAST
id|IFA_BROADCAST
comma
DECL|enumerator|IFA_ANYCAST
id|IFA_ANYCAST
comma
DECL|enumerator|IFA_CACHEINFO
id|IFA_CACHEINFO
)brace
suffix:semicolon
DECL|macro|IFA_MAX
mdefine_line|#define IFA_MAX IFA_CACHEINFO
multiline_comment|/* ifa_flags */
DECL|macro|IFA_F_SECONDARY
mdefine_line|#define IFA_F_SECONDARY&t;&t;0x01
DECL|macro|IFA_F_DEPRECATED
mdefine_line|#define IFA_F_DEPRECATED&t;0x20
DECL|macro|IFA_F_TENTATIVE
mdefine_line|#define IFA_F_TENTATIVE&t;&t;0x40
DECL|macro|IFA_F_PERMANENT
mdefine_line|#define IFA_F_PERMANENT&t;&t;0x80
DECL|struct|ifa_cacheinfo
r_struct
id|ifa_cacheinfo
(brace
DECL|member|ifa_prefered
id|__s32
id|ifa_prefered
suffix:semicolon
DECL|member|ifa_valid
id|__s32
id|ifa_valid
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|IFA_RTA
mdefine_line|#define IFA_RTA(r)  ((struct rtattr*)(((char*)(r)) + NLMSG_ALIGN(sizeof(struct ifaddrmsg))))
DECL|macro|IFA_PAYLOAD
mdefine_line|#define IFA_PAYLOAD(n) NLMSG_PAYLOAD(n,sizeof(struct ifaddrmsg))
multiline_comment|/*&n;   Important comment:&n;   IFA_ADDRESS is prefix address, rather than local interface address.&n;   It makes no difference for normally configured broadcast interfaces,&n;   but for point-to-point IFA_ADDRESS is DESTINATION address,&n;   local address is supplied in IFA_LOCAL attribute.&n; */
multiline_comment|/**************************************************************&n; *&t;&t;Neighbour discovery.&n; ****/
DECL|struct|ndmsg
r_struct
id|ndmsg
(brace
DECL|member|ndm_family
r_int
r_char
id|ndm_family
suffix:semicolon
DECL|member|ndm_pad1
r_int
r_char
id|ndm_pad1
suffix:semicolon
DECL|member|ndm_pad2
r_int
r_int
id|ndm_pad2
suffix:semicolon
DECL|member|ndm_ifindex
r_int
id|ndm_ifindex
suffix:semicolon
multiline_comment|/* Link index&t;&t;&t;*/
DECL|member|ndm_state
id|__u16
id|ndm_state
suffix:semicolon
DECL|member|ndm_flags
id|__u8
id|ndm_flags
suffix:semicolon
DECL|member|ndm_type
id|__u8
id|ndm_type
suffix:semicolon
)brace
suffix:semicolon
r_enum
(brace
DECL|enumerator|NDA_UNSPEC
id|NDA_UNSPEC
comma
DECL|enumerator|NDA_DST
id|NDA_DST
comma
DECL|enumerator|NDA_LLADDR
id|NDA_LLADDR
comma
DECL|enumerator|NDA_CACHEINFO
id|NDA_CACHEINFO
)brace
suffix:semicolon
DECL|macro|NDA_MAX
mdefine_line|#define NDA_MAX NDA_CACHEINFO
DECL|macro|NDA_RTA
mdefine_line|#define NDA_RTA(r)  ((struct rtattr*)(((char*)(r)) + NLMSG_ALIGN(sizeof(struct ndmsg))))
DECL|macro|NDA_PAYLOAD
mdefine_line|#define NDA_PAYLOAD(n) NLMSG_PAYLOAD(n,sizeof(struct ndmsg))
multiline_comment|/*&n; *&t;Neighbor Cache Entry Flags&n; */
DECL|macro|NTF_PROXY
mdefine_line|#define NTF_PROXY&t;0x08&t;/* == ATF_PUBL */
DECL|macro|NTF_ROUTER
mdefine_line|#define NTF_ROUTER&t;0x80
multiline_comment|/*&n; *&t;Neighbor Cache Entry States.&n; */
DECL|macro|NUD_INCOMPLETE
mdefine_line|#define NUD_INCOMPLETE&t;0x01
DECL|macro|NUD_REACHABLE
mdefine_line|#define NUD_REACHABLE&t;0x02
DECL|macro|NUD_STALE
mdefine_line|#define NUD_STALE&t;0x04
DECL|macro|NUD_DELAY
mdefine_line|#define NUD_DELAY&t;0x08
DECL|macro|NUD_PROBE
mdefine_line|#define NUD_PROBE&t;0x10
DECL|macro|NUD_FAILED
mdefine_line|#define NUD_FAILED&t;0x20
multiline_comment|/* Dummy states */
DECL|macro|NUD_NOARP
mdefine_line|#define NUD_NOARP&t;0x40
DECL|macro|NUD_PERMANENT
mdefine_line|#define NUD_PERMANENT&t;0x80
DECL|macro|NUD_NONE
mdefine_line|#define NUD_NONE&t;0x00
DECL|struct|nda_cacheinfo
r_struct
id|nda_cacheinfo
(brace
DECL|member|ndm_confirmed
id|__u32
id|ndm_confirmed
suffix:semicolon
DECL|member|ndm_used
id|__u32
id|ndm_used
suffix:semicolon
DECL|member|ndm_updated
id|__u32
id|ndm_updated
suffix:semicolon
DECL|member|ndm_refcnt
id|__u32
id|ndm_refcnt
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/****&n; *&t;&t;General form of address family dependent message.&n; ****/
DECL|struct|rtgenmsg
r_struct
id|rtgenmsg
(brace
DECL|member|rtgen_family
r_int
r_char
id|rtgen_family
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*****************************************************************&n; *&t;&t;Link layer specific messages.&n; ****/
multiline_comment|/* struct ifinfomsg&n; * passes link level specific information, not dependent&n; * on network protocol.&n; */
DECL|struct|ifinfomsg
r_struct
id|ifinfomsg
(brace
DECL|member|ifi_family
r_int
r_char
id|ifi_family
suffix:semicolon
DECL|member|__ifi_pad
r_int
r_char
id|__ifi_pad
suffix:semicolon
DECL|member|ifi_type
r_int
r_int
id|ifi_type
suffix:semicolon
multiline_comment|/* ARPHRD_* */
DECL|member|ifi_index
r_int
id|ifi_index
suffix:semicolon
multiline_comment|/* Link index&t;*/
DECL|member|ifi_flags
r_int
id|ifi_flags
suffix:semicolon
multiline_comment|/* IFF_* flags&t;*/
DECL|member|ifi_change
r_int
id|ifi_change
suffix:semicolon
multiline_comment|/* IFF_* change mask */
)brace
suffix:semicolon
r_enum
(brace
DECL|enumerator|IFLA_UNSPEC
id|IFLA_UNSPEC
comma
DECL|enumerator|IFLA_ADDRESS
id|IFLA_ADDRESS
comma
DECL|enumerator|IFLA_BROADCAST
id|IFLA_BROADCAST
comma
DECL|enumerator|IFLA_IFNAME
id|IFLA_IFNAME
comma
DECL|enumerator|IFLA_MTU
id|IFLA_MTU
comma
DECL|enumerator|IFLA_LINK
id|IFLA_LINK
comma
DECL|enumerator|IFLA_QDISC
id|IFLA_QDISC
comma
DECL|enumerator|IFLA_STATS
id|IFLA_STATS
comma
DECL|enumerator|IFLA_COST
id|IFLA_COST
comma
DECL|macro|IFLA_COST
mdefine_line|#define IFLA_COST IFLA_COST
DECL|enumerator|IFLA_PRIORITY
id|IFLA_PRIORITY
comma
DECL|macro|IFLA_PRIORITY
mdefine_line|#define IFLA_PRIORITY IFLA_PRIORITY
DECL|enumerator|IFLA_MASTER
id|IFLA_MASTER
DECL|macro|IFLA_MASTER
mdefine_line|#define IFLA_MASTER IFLA_MASTER
)brace
suffix:semicolon
DECL|macro|IFLA_MAX
mdefine_line|#define IFLA_MAX IFLA_MASTER
DECL|macro|IFLA_RTA
mdefine_line|#define IFLA_RTA(r)  ((struct rtattr*)(((char*)(r)) + NLMSG_ALIGN(sizeof(struct ifinfomsg))))
DECL|macro|IFLA_PAYLOAD
mdefine_line|#define IFLA_PAYLOAD(n) NLMSG_PAYLOAD(n,sizeof(struct ifinfomsg))
multiline_comment|/* ifi_flags.&n;&n;   IFF_* flags.&n;&n;   The only change is:&n;   IFF_LOOPBACK, IFF_BROADCAST and IFF_POINTOPOINT are&n;   more not changeable by user. They describe link media&n;   characteristics and set by device driver.&n;&n;   Comments:&n;   - Combination IFF_BROADCAST|IFF_POINTOPOINT is invalid&n;   - If neiher of these three flags are set;&n;     the interface is NBMA.&n;&n;   - IFF_MULTICAST does not mean anything special:&n;   multicasts can be used on all not-NBMA links.&n;   IFF_MULTICAST means that this media uses special encapsulation&n;   for multicast frames. Apparently, all IFF_POINTOPOINT and&n;   IFF_BROADCAST devices are able to use multicasts too.&n; */
multiline_comment|/* IFLA_LINK.&n;   For usual devices it is equal ifi_index.&n;   If it is a &quot;virtual interface&quot; (f.e. tunnel), ifi_link&n;   can point to real physical interface (f.e. for bandwidth calculations),&n;   or maybe 0, what means, that real media is unknown (usual&n;   for IPIP tunnels, when route to endpoint is allowed to change)&n; */
multiline_comment|/*****************************************************************&n; *&t;&t;Traffic control messages.&n; ****/
DECL|struct|tcmsg
r_struct
id|tcmsg
(brace
DECL|member|tcm_family
r_int
r_char
id|tcm_family
suffix:semicolon
DECL|member|tcm__pad1
r_int
r_char
id|tcm__pad1
suffix:semicolon
DECL|member|tcm__pad2
r_int
r_int
id|tcm__pad2
suffix:semicolon
DECL|member|tcm_ifindex
r_int
id|tcm_ifindex
suffix:semicolon
DECL|member|tcm_handle
id|__u32
id|tcm_handle
suffix:semicolon
DECL|member|tcm_parent
id|__u32
id|tcm_parent
suffix:semicolon
DECL|member|tcm_info
id|__u32
id|tcm_info
suffix:semicolon
)brace
suffix:semicolon
r_enum
(brace
DECL|enumerator|TCA_UNSPEC
id|TCA_UNSPEC
comma
DECL|enumerator|TCA_KIND
id|TCA_KIND
comma
DECL|enumerator|TCA_OPTIONS
id|TCA_OPTIONS
comma
DECL|enumerator|TCA_STATS
id|TCA_STATS
comma
DECL|enumerator|TCA_XSTATS
id|TCA_XSTATS
comma
DECL|enumerator|TCA_RATE
id|TCA_RATE
comma
)brace
suffix:semicolon
DECL|macro|TCA_MAX
mdefine_line|#define TCA_MAX TCA_RATE
DECL|macro|TCA_RTA
mdefine_line|#define TCA_RTA(r)  ((struct rtattr*)(((char*)(r)) + NLMSG_ALIGN(sizeof(struct tcmsg))))
DECL|macro|TCA_PAYLOAD
mdefine_line|#define TCA_PAYLOAD(n) NLMSG_PAYLOAD(n,sizeof(struct tcmsg))
multiline_comment|/* SUMMARY: maximal rtattr understood by kernel */
DECL|macro|RTATTR_MAX
mdefine_line|#define RTATTR_MAX&t;&t;RTA_MAX
multiline_comment|/* RTnetlink multicast groups */
DECL|macro|RTMGRP_LINK
mdefine_line|#define RTMGRP_LINK&t;&t;1
DECL|macro|RTMGRP_NOTIFY
mdefine_line|#define RTMGRP_NOTIFY&t;&t;2
DECL|macro|RTMGRP_NEIGH
mdefine_line|#define RTMGRP_NEIGH&t;&t;4
DECL|macro|RTMGRP_TC
mdefine_line|#define RTMGRP_TC&t;&t;8
DECL|macro|RTMGRP_IPV4_IFADDR
mdefine_line|#define RTMGRP_IPV4_IFADDR&t;0x10
DECL|macro|RTMGRP_IPV4_MROUTE
mdefine_line|#define RTMGRP_IPV4_MROUTE&t;0x20
DECL|macro|RTMGRP_IPV4_ROUTE
mdefine_line|#define RTMGRP_IPV4_ROUTE&t;0x40
DECL|macro|RTMGRP_IPV6_IFADDR
mdefine_line|#define RTMGRP_IPV6_IFADDR&t;0x100
DECL|macro|RTMGRP_IPV6_MROUTE
mdefine_line|#define RTMGRP_IPV6_MROUTE&t;0x200
DECL|macro|RTMGRP_IPV6_ROUTE
mdefine_line|#define RTMGRP_IPV6_ROUTE&t;0x400
DECL|macro|RTMGRP_DECnet_IFADDR
mdefine_line|#define RTMGRP_DECnet_IFADDR    0x1000
DECL|macro|RTMGRP_DECnet_ROUTE
mdefine_line|#define RTMGRP_DECnet_ROUTE     0x4000
multiline_comment|/* End of information exported to user level */
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/config.h&gt;
DECL|function|rtattr_strcmp
r_extern
id|__inline__
r_int
id|rtattr_strcmp
c_func
(paren
r_struct
id|rtattr
op_star
id|rta
comma
r_char
op_star
id|str
)paren
(brace
r_int
id|len
op_assign
id|strlen
c_func
(paren
id|str
)paren
op_plus
l_int|1
suffix:semicolon
r_return
id|len
OG
id|rta-&gt;rta_len
op_logical_or
id|memcmp
c_func
(paren
id|RTA_DATA
c_func
(paren
id|rta
)paren
comma
id|str
comma
id|len
)paren
suffix:semicolon
)brace
r_extern
r_int
id|rtattr_parse
c_func
(paren
r_struct
id|rtattr
op_star
id|tb
(braket
)braket
comma
r_int
id|maxattr
comma
r_struct
id|rtattr
op_star
id|rta
comma
r_int
id|len
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_RTNETLINK
r_extern
r_struct
id|sock
op_star
id|rtnl
suffix:semicolon
DECL|struct|rtnetlink_link
r_struct
id|rtnetlink_link
(brace
DECL|member|doit
r_int
(paren
op_star
id|doit
)paren
(paren
r_struct
id|sk_buff
op_star
comma
r_struct
id|nlmsghdr
op_star
comma
r_void
op_star
id|attr
)paren
suffix:semicolon
DECL|member|dumpit
r_int
(paren
op_star
id|dumpit
)paren
(paren
r_struct
id|sk_buff
op_star
comma
r_struct
id|netlink_callback
op_star
id|cb
)paren
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|rtnetlink_link
op_star
id|rtnetlink_links
(braket
id|NPROTO
)braket
suffix:semicolon
r_extern
r_int
id|rtnetlink_dump_ifinfo
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|netlink_callback
op_star
id|cb
)paren
suffix:semicolon
r_extern
r_int
id|rtnetlink_send
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
id|u32
id|pid
comma
id|u32
id|group
comma
r_int
id|echo
)paren
suffix:semicolon
r_extern
r_int
id|rtnetlink_put_metrics
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_int
op_star
id|metrics
)paren
suffix:semicolon
r_extern
r_void
id|__rta_fill
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_int
id|attrtype
comma
r_int
id|attrlen
comma
r_const
r_void
op_star
id|data
)paren
suffix:semicolon
DECL|macro|RTA_PUT
mdefine_line|#define RTA_PUT(skb, attrtype, attrlen, data) &bslash;&n;({ if (skb_tailroom(skb) &lt; (int)RTA_SPACE(attrlen)) goto rtattr_failure; &bslash;&n;   __rta_fill(skb, attrtype, attrlen, data); })
r_extern
r_void
id|rtmsg_ifinfo
c_func
(paren
r_int
id|type
comma
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|change
)paren
suffix:semicolon
macro_line|#else
DECL|macro|rtmsg_ifinfo
mdefine_line|#define rtmsg_ifinfo(a,b,c) do { } while (0)
macro_line|#endif
r_extern
r_struct
id|semaphore
id|rtnl_sem
suffix:semicolon
DECL|macro|rtnl_exlock
mdefine_line|#define rtnl_exlock()&t;&t;do { } while(0)
DECL|macro|rtnl_exunlock
mdefine_line|#define rtnl_exunlock()&t;&t;do { } while(0)
DECL|macro|rtnl_exlock_nowait
mdefine_line|#define rtnl_exlock_nowait()&t;(0)
DECL|macro|rtnl_shlock
mdefine_line|#define rtnl_shlock()&t;&t;down(&amp;rtnl_sem)
DECL|macro|rtnl_shlock_nowait
mdefine_line|#define rtnl_shlock_nowait()&t;down_trylock(&amp;rtnl_sem)
macro_line|#ifndef CONFIG_RTNETLINK
DECL|macro|rtnl_shunlock
mdefine_line|#define rtnl_shunlock()&t;up(&amp;rtnl_sem)
macro_line|#else
DECL|macro|rtnl_shunlock
mdefine_line|#define rtnl_shunlock()&t;do { up(&amp;rtnl_sem); &bslash;&n;&t;&t;             if (rtnl &amp;&amp; rtnl-&gt;receive_queue.qlen) &bslash;&n;&t;&t;&t;&t;     rtnl-&gt;data_ready(rtnl, 0); &bslash;&n;&t;&t;        } while(0)
macro_line|#endif
r_extern
r_void
id|rtnl_lock
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|rtnl_unlock
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|rtnetlink_init
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|ASSERT_RTNL
mdefine_line|#define ASSERT_RTNL() do { if (down_trylock(&amp;rtnl_sem) == 0)  { up(&amp;rtnl_sem); &bslash;&n;printk(&quot;RTNL: assertion failed at &quot; __FILE__ &quot;(%d):&quot; __FUNCTION__ &quot;&bslash;n&quot;, __LINE__); } &bslash;&n;&t;&t;   } while(0);
DECL|macro|BUG_TRAP
mdefine_line|#define BUG_TRAP(x) if (!(x)) { printk(&quot;KERNEL: assertion (&quot; #x &quot;) failed at &quot; __FILE__ &quot;(%d):&quot; __FUNCTION__ &quot;&bslash;n&quot;, __LINE__); }
macro_line|#endif /* __KERNEL__ */
macro_line|#endif&t;/* __LINUX_RTNETLINK_H */
eof
