macro_line|#ifndef _IPV6_H
DECL|macro|_IPV6_H
mdefine_line|#define _IPV6_H
macro_line|#include &lt;linux/config.h&gt;
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
DECL|struct|ipv6_auth_hdr
r_struct
id|ipv6_auth_hdr
(brace
DECL|member|nexthdr
id|__u8
id|nexthdr
suffix:semicolon
DECL|member|hdrlen
id|__u8
id|hdrlen
suffix:semicolon
multiline_comment|/* This one is measured in 32 bit units! */
DECL|member|reserved
id|__u16
id|reserved
suffix:semicolon
DECL|member|spi
id|__u32
id|spi
suffix:semicolon
DECL|member|seq_no
id|__u32
id|seq_no
suffix:semicolon
multiline_comment|/* Sequence number */
DECL|member|auth_data
id|__u8
id|auth_data
(braket
l_int|0
)braket
suffix:semicolon
multiline_comment|/* Length variable but &gt;=4. Mind the 64 bit alignment! */
)brace
suffix:semicolon
DECL|struct|ipv6_esp_hdr
r_struct
id|ipv6_esp_hdr
(brace
DECL|member|spi
id|__u32
id|spi
suffix:semicolon
DECL|member|seq_no
id|__u32
id|seq_no
suffix:semicolon
multiline_comment|/* Sequence number */
DECL|member|enc_data
id|__u8
id|enc_data
(braket
l_int|0
)braket
suffix:semicolon
multiline_comment|/* Length variable but &gt;=8. Mind the 64 bit alignment! */
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
macro_line|#include &lt;linux/in6.h&gt;          /* struct sockaddr_in6 */
macro_line|#include &lt;linux/icmpv6.h&gt;
macro_line|#include &lt;net/if_inet6.h&gt;       /* struct ipv6_mc_socklist */
macro_line|#include &lt;linux/tcp.h&gt;
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
DECL|struct|ipv6_pinfo
r_struct
id|ipv6_pinfo
(brace
DECL|member|saddr
r_struct
id|in6_addr
id|saddr
suffix:semicolon
DECL|member|rcv_saddr
r_struct
id|in6_addr
id|rcv_saddr
suffix:semicolon
DECL|member|daddr
r_struct
id|in6_addr
id|daddr
suffix:semicolon
DECL|member|daddr_cache
r_struct
id|in6_addr
op_star
id|daddr_cache
suffix:semicolon
DECL|member|flow_label
id|__u32
id|flow_label
suffix:semicolon
DECL|member|frag_size
id|__u32
id|frag_size
suffix:semicolon
DECL|member|hop_limit
r_int
id|hop_limit
suffix:semicolon
DECL|member|mcast_hops
r_int
id|mcast_hops
suffix:semicolon
DECL|member|mcast_oif
r_int
id|mcast_oif
suffix:semicolon
multiline_comment|/* pktoption flags */
r_union
(brace
r_struct
(brace
DECL|member|srcrt
id|__u8
id|srcrt
suffix:colon
l_int|2
comma
DECL|member|rxinfo
id|rxinfo
suffix:colon
l_int|1
comma
DECL|member|rxhlim
id|rxhlim
suffix:colon
l_int|1
comma
DECL|member|hopopts
id|hopopts
suffix:colon
l_int|1
comma
DECL|member|dstopts
id|dstopts
suffix:colon
l_int|1
comma
DECL|member|authhdr
id|authhdr
suffix:colon
l_int|1
comma
DECL|member|rxflow
id|rxflow
suffix:colon
l_int|1
suffix:semicolon
DECL|member|bits
)brace
id|bits
suffix:semicolon
DECL|member|all
id|__u8
id|all
suffix:semicolon
DECL|member|rxopt
)brace
id|rxopt
suffix:semicolon
multiline_comment|/* sockopt flags */
DECL|member|mc_loop
id|__u8
id|mc_loop
suffix:colon
l_int|1
comma
DECL|member|recverr
id|recverr
suffix:colon
l_int|1
comma
DECL|member|sndflow
id|sndflow
suffix:colon
l_int|1
comma
DECL|member|pmtudisc
id|pmtudisc
suffix:colon
l_int|2
comma
DECL|member|ipv6only
id|ipv6only
suffix:colon
l_int|1
suffix:semicolon
DECL|member|ipv6_mc_list
r_struct
id|ipv6_mc_socklist
op_star
id|ipv6_mc_list
suffix:semicolon
DECL|member|ipv6_ac_list
r_struct
id|ipv6_ac_socklist
op_star
id|ipv6_ac_list
suffix:semicolon
DECL|member|ipv6_fl_list
r_struct
id|ipv6_fl_socklist
op_star
id|ipv6_fl_list
suffix:semicolon
DECL|member|dst_cookie
id|__u32
id|dst_cookie
suffix:semicolon
DECL|member|opt
r_struct
id|ipv6_txoptions
op_star
id|opt
suffix:semicolon
DECL|member|pktoptions
r_struct
id|sk_buff
op_star
id|pktoptions
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|raw6_opt
r_struct
id|raw6_opt
(brace
DECL|member|checksum
id|__u32
id|checksum
suffix:semicolon
multiline_comment|/* perform checksum */
DECL|member|offset
id|__u32
id|offset
suffix:semicolon
multiline_comment|/* checksum offset  */
DECL|member|filter
r_struct
id|icmp6_filter
id|filter
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* WARNING: don&squot;t change the layout of the members in {raw,udp,tcp}6_sock! */
DECL|struct|raw6_sock
r_struct
id|raw6_sock
(brace
DECL|member|sk
r_struct
id|sock
id|sk
suffix:semicolon
DECL|member|pinet6
r_struct
id|ipv6_pinfo
op_star
id|pinet6
suffix:semicolon
DECL|member|inet
r_struct
id|inet_opt
id|inet
suffix:semicolon
DECL|member|raw6
r_struct
id|raw6_opt
id|raw6
suffix:semicolon
DECL|member|inet6
r_struct
id|ipv6_pinfo
id|inet6
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|udp6_sock
r_struct
id|udp6_sock
(brace
DECL|member|sk
r_struct
id|sock
id|sk
suffix:semicolon
DECL|member|pinet6
r_struct
id|ipv6_pinfo
op_star
id|pinet6
suffix:semicolon
DECL|member|inet
r_struct
id|inet_opt
id|inet
suffix:semicolon
DECL|member|inet6
r_struct
id|ipv6_pinfo
id|inet6
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|tcp6_sock
r_struct
id|tcp6_sock
(brace
DECL|member|sk
r_struct
id|sock
id|sk
suffix:semicolon
DECL|member|pinet6
r_struct
id|ipv6_pinfo
op_star
id|pinet6
suffix:semicolon
DECL|member|inet
r_struct
id|inet_opt
id|inet
suffix:semicolon
DECL|member|tcp
r_struct
id|tcp_opt
id|tcp
suffix:semicolon
DECL|member|inet6
r_struct
id|ipv6_pinfo
id|inet6
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|inet6_sk
mdefine_line|#define inet6_sk(__sk) ((struct raw6_sock *)__sk)-&gt;pinet6
DECL|macro|raw6_sk
mdefine_line|#define raw6_sk(__sk) (&amp;((struct raw6_sock *)__sk)-&gt;raw6)
macro_line|#if defined(CONFIG_IPV6) || defined(CONFIG_IPV6_MODULE)
DECL|macro|__ipv6_only_sock
mdefine_line|#define __ipv6_only_sock(sk)&t;(inet6_sk(sk)-&gt;ipv6only)
DECL|macro|ipv6_only_sock
mdefine_line|#define ipv6_only_sock(sk)&t;((sk)-&gt;family == PF_INET6 &amp;&amp; __ipv6_only_sock(sk))
macro_line|#else
DECL|macro|__ipv6_only_sock
mdefine_line|#define __ipv6_only_sock(sk)&t;0
DECL|macro|ipv6_only_sock
mdefine_line|#define ipv6_only_sock(sk)&t;0
macro_line|#endif
macro_line|#endif
macro_line|#endif
eof
