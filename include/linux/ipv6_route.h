multiline_comment|/*&n; *&t;Linux INET6 implementation &n; *&n; *&t;Authors:&n; *&t;Pedro Roque&t;&t;&lt;roque@di.fc.ul.pt&gt;&t;&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *      modify it under the terms of the GNU General Public License&n; *      as published by the Free Software Foundation; either version&n; *      2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _LINUX_IPV6_ROUTE_H
DECL|macro|_LINUX_IPV6_ROUTE_H
mdefine_line|#define _LINUX_IPV6_ROUTE_H
r_enum
(brace
DECL|enumerator|RTA_IPV6_UNSPEC
id|RTA_IPV6_UNSPEC
comma
DECL|enumerator|RTA_IPV6_HOPLIMIT
id|RTA_IPV6_HOPLIMIT
comma
)brace
suffix:semicolon
DECL|macro|RTA_IPV6_MAX
mdefine_line|#define&t;RTA_IPV6_MAX RTA_IPV6_HOPLIMIT
DECL|macro|RTF_DEFAULT
mdefine_line|#define RTF_DEFAULT&t;0x00010000&t;/* default - learned via ND&t;*/
DECL|macro|RTF_ALLONLINK
mdefine_line|#define RTF_ALLONLINK&t;0x00020000&t;/* fallback, no routers on link&t;*/
DECL|macro|RTF_ADDRCONF
mdefine_line|#define RTF_ADDRCONF&t;0x00040000&t;/* addrconf route - RA&t;&t;*/
DECL|macro|RTF_NONEXTHOP
mdefine_line|#define RTF_NONEXTHOP&t;0x00200000&t;/* route with no nexthop&t;*/
DECL|macro|RTF_EXPIRES
mdefine_line|#define RTF_EXPIRES&t;0x00400000
DECL|macro|RTF_CACHE
mdefine_line|#define RTF_CACHE&t;0x01000000&t;/* cache entry&t;&t;&t;*/
DECL|macro|RTF_FLOW
mdefine_line|#define RTF_FLOW&t;0x02000000&t;/* flow significant route&t;*/
DECL|macro|RTF_POLICY
mdefine_line|#define RTF_POLICY&t;0x04000000&t;/* policy route&t;&t;&t;*/
DECL|macro|RTF_LOCAL
mdefine_line|#define RTF_LOCAL&t;0x80000000
DECL|struct|in6_rtmsg
r_struct
id|in6_rtmsg
(brace
DECL|member|rtmsg_dst
r_struct
id|in6_addr
id|rtmsg_dst
suffix:semicolon
DECL|member|rtmsg_src
r_struct
id|in6_addr
id|rtmsg_src
suffix:semicolon
DECL|member|rtmsg_gateway
r_struct
id|in6_addr
id|rtmsg_gateway
suffix:semicolon
DECL|member|rtmsg_type
id|__u32
id|rtmsg_type
suffix:semicolon
DECL|member|rtmsg_dst_len
id|__u16
id|rtmsg_dst_len
suffix:semicolon
DECL|member|rtmsg_src_len
id|__u16
id|rtmsg_src_len
suffix:semicolon
DECL|member|rtmsg_metric
id|__u32
id|rtmsg_metric
suffix:semicolon
DECL|member|rtmsg_info
r_int
r_int
id|rtmsg_info
suffix:semicolon
DECL|member|rtmsg_flags
id|__u32
id|rtmsg_flags
suffix:semicolon
DECL|member|rtmsg_ifindex
r_int
id|rtmsg_ifindex
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|RTMSG_NEWDEVICE
mdefine_line|#define RTMSG_NEWDEVICE&t;&t;0x11
DECL|macro|RTMSG_DELDEVICE
mdefine_line|#define RTMSG_DELDEVICE&t;&t;0x12
DECL|macro|RTMSG_NEWROUTE
mdefine_line|#define RTMSG_NEWROUTE&t;&t;0x21
DECL|macro|RTMSG_DELROUTE
mdefine_line|#define RTMSG_DELROUTE&t;&t;0x22
macro_line|#endif
eof
