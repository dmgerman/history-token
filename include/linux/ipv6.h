macro_line|#ifndef _IPV6_H
DECL|macro|_IPV6_H
mdefine_line|#define _IPV6_H
macro_line|#include &lt;linux/in6.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
multiline_comment|/* The latest drafts declared increase in minimal mtu up to 1280. */
DECL|macro|IPV6_MIN_MTU
mdefine_line|#define IPV6_MIN_MTU&t;1280
multiline_comment|/*&n; *&t;Advanced API&n; *&t;source interface/address selection, source routing, etc...&n; *&t;*under construction*&n; */
DECL|struct|in6_pktinfo
r_struct
id|in6_pktinfo
(brace
DECL|member|ipi6_addr
r_struct
id|in6_addr
id|ipi6_addr
suffix:semicolon
DECL|member|ipi6_ifindex
r_int
id|ipi6_ifindex
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|in6_ifreq
r_struct
id|in6_ifreq
(brace
DECL|member|ifr6_addr
r_struct
id|in6_addr
id|ifr6_addr
suffix:semicolon
DECL|member|ifr6_prefixlen
id|__u32
id|ifr6_prefixlen
suffix:semicolon
DECL|member|ifr6_ifindex
r_int
id|ifr6_ifindex
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|IPV6_SRCRT_STRICT
mdefine_line|#define IPV6_SRCRT_STRICT&t;0x01&t;/* this hop must be a neighbor&t;*/
DECL|macro|IPV6_SRCRT_TYPE_0
mdefine_line|#define IPV6_SRCRT_TYPE_0&t;0&t;/* IPv6 type 0 Routing Header&t;*/
multiline_comment|/*&n; *&t;routing header&n; */
DECL|struct|ipv6_rt_hdr
r_struct
id|ipv6_rt_hdr
(brace
DECL|member|nexthdr
id|__u8
id|nexthdr
suffix:semicolon
DECL|member|hdrlen
id|__u8
id|hdrlen
suffix:semicolon
DECL|member|type
id|__u8
id|type
suffix:semicolon
DECL|member|segments_left
id|__u8
id|segments_left
suffix:semicolon
multiline_comment|/*&n;&t; *&t;type specific data&n;&t; *&t;variable length field&n;&t; */
)brace
suffix:semicolon
DECL|struct|ipv6_opt_hdr
r_struct
id|ipv6_opt_hdr
(brace
DECL|member|nexthdr
id|__u8
id|nexthdr
suffix:semicolon
DECL|member|hdrlen
id|__u8
id|hdrlen
suffix:semicolon
multiline_comment|/* &n;&t; * TLV encoded option data follows.&n;&t; */
)brace
suffix:semicolon
DECL|macro|ipv6_destopt_hdr
mdefine_line|#define ipv6_destopt_hdr ipv6_opt_hdr
DECL|macro|ipv6_hopopt_hdr
mdefine_line|#define ipv6_hopopt_hdr  ipv6_opt_hdr
macro_line|#ifdef __KERNEL__
DECL|macro|ipv6_optlen
mdefine_line|#define ipv6_optlen(p)  (((p)-&gt;hdrlen+1) &lt;&lt; 3)
macro_line|#endif
multiline_comment|/*&n; *&t;routing header type 0 (used in cmsghdr struct)&n; */
DECL|struct|rt0_hdr
r_struct
id|rt0_hdr
(brace
DECL|member|rt_hdr
r_struct
id|ipv6_rt_hdr
id|rt_hdr
suffix:semicolon
DECL|member|bitmap
id|__u32
id|bitmap
suffix:semicolon
multiline_comment|/* strict/loose bit map */
DECL|member|addr
r_struct
id|in6_addr
id|addr
(braket
l_int|0
)braket
suffix:semicolon
DECL|macro|rt0_type
mdefine_line|#define rt0_type&t;&t;rt_hdr.type;
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;IPv6 fixed header&n; *&n; *&t;BEWARE, it is incorrect. The first 4 bits of flow_lbl&n; *&t;are glued to priority now, forming &quot;class&quot;.&n; */
DECL|struct|ipv6hdr
r_struct
id|ipv6hdr
(brace
macro_line|#if defined(__LITTLE_ENDIAN_BITFIELD)
DECL|member|priority
id|__u8
id|priority
suffix:colon
l_int|4
comma
DECL|member|version
id|version
suffix:colon
l_int|4
suffix:semicolon
macro_line|#elif defined(__BIG_ENDIAN_BITFIELD)
id|__u8
id|version
suffix:colon
l_int|4
comma
id|priority
suffix:colon
l_int|4
suffix:semicolon
macro_line|#else
macro_line|#error&t;&quot;Please fix &lt;asm/byteorder.h&gt;&quot;
macro_line|#endif
DECL|member|flow_lbl
id|__u8
id|flow_lbl
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|payload_len
id|__u16
id|payload_len
suffix:semicolon
DECL|member|nexthdr
id|__u8
id|nexthdr
suffix:semicolon
DECL|member|hop_limit
id|__u8
id|hop_limit
suffix:semicolon
DECL|member|saddr
r_struct
id|in6_addr
id|saddr
suffix:semicolon
DECL|member|daddr
r_struct
id|in6_addr
id|daddr
suffix:semicolon
)brace
suffix:semicolon
macro_line|#ifdef __KERNEL__
multiline_comment|/* &n;   This structure contains results of exthdrs parsing&n;   as offsets from skb-&gt;nh.&n; */
DECL|struct|inet6_skb_parm
r_struct
id|inet6_skb_parm
(brace
DECL|member|iif
r_int
id|iif
suffix:semicolon
DECL|member|ra
id|__u16
id|ra
suffix:semicolon
DECL|member|hop
id|__u16
id|hop
suffix:semicolon
DECL|member|auth
id|__u16
id|auth
suffix:semicolon
DECL|member|dst0
id|__u16
id|dst0
suffix:semicolon
DECL|member|srcrt
id|__u16
id|srcrt
suffix:semicolon
DECL|member|dst1
id|__u16
id|dst1
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
macro_line|#endif
eof
