multiline_comment|/*&n; * INET&t;&t;An implementation of the TCP/IP protocol suite for the LINUX&n; *&t;&t;operating system.  INET is implemented using the  BSD Socket&n; *&t;&t;interface as the means of communication with the user level.&n; *&n; *&t;&t;Definitions for the IP protocol.&n; *&n; * Version:&t;@(#)ip.h&t;1.0.2&t;04/28/93&n; *&n; * Authors:&t;Fred N. van Kempen, &lt;waltje@uWalt.NL.Mugnet.ORG&gt;&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _LINUX_IP_H
DECL|macro|_LINUX_IP_H
mdefine_line|#define _LINUX_IP_H
macro_line|#include &lt;asm/byteorder.h&gt;
multiline_comment|/* SOL_IP socket options */
DECL|macro|IPTOS_TOS_MASK
mdefine_line|#define IPTOS_TOS_MASK&t;&t;0x1E
DECL|macro|IPTOS_TOS
mdefine_line|#define IPTOS_TOS(tos)&t;&t;((tos)&amp;IPTOS_TOS_MASK)
DECL|macro|IPTOS_LOWDELAY
mdefine_line|#define&t;IPTOS_LOWDELAY&t;&t;0x10
DECL|macro|IPTOS_THROUGHPUT
mdefine_line|#define&t;IPTOS_THROUGHPUT&t;0x08
DECL|macro|IPTOS_RELIABILITY
mdefine_line|#define&t;IPTOS_RELIABILITY&t;0x04
DECL|macro|IPTOS_MINCOST
mdefine_line|#define&t;IPTOS_MINCOST&t;&t;0x02
DECL|macro|IPTOS_PREC_MASK
mdefine_line|#define IPTOS_PREC_MASK&t;&t;0xE0
DECL|macro|IPTOS_PREC
mdefine_line|#define IPTOS_PREC(tos)&t;&t;((tos)&amp;IPTOS_PREC_MASK)
DECL|macro|IPTOS_PREC_NETCONTROL
mdefine_line|#define IPTOS_PREC_NETCONTROL           0xe0
DECL|macro|IPTOS_PREC_INTERNETCONTROL
mdefine_line|#define IPTOS_PREC_INTERNETCONTROL      0xc0
DECL|macro|IPTOS_PREC_CRITIC_ECP
mdefine_line|#define IPTOS_PREC_CRITIC_ECP           0xa0
DECL|macro|IPTOS_PREC_FLASHOVERRIDE
mdefine_line|#define IPTOS_PREC_FLASHOVERRIDE        0x80
DECL|macro|IPTOS_PREC_FLASH
mdefine_line|#define IPTOS_PREC_FLASH                0x60
DECL|macro|IPTOS_PREC_IMMEDIATE
mdefine_line|#define IPTOS_PREC_IMMEDIATE            0x40
DECL|macro|IPTOS_PREC_PRIORITY
mdefine_line|#define IPTOS_PREC_PRIORITY             0x20
DECL|macro|IPTOS_PREC_ROUTINE
mdefine_line|#define IPTOS_PREC_ROUTINE              0x00
multiline_comment|/* IP options */
DECL|macro|IPOPT_COPY
mdefine_line|#define IPOPT_COPY&t;&t;0x80
DECL|macro|IPOPT_CLASS_MASK
mdefine_line|#define IPOPT_CLASS_MASK&t;0x60
DECL|macro|IPOPT_NUMBER_MASK
mdefine_line|#define IPOPT_NUMBER_MASK&t;0x1f
DECL|macro|IPOPT_COPIED
mdefine_line|#define&t;IPOPT_COPIED(o)&t;&t;((o)&amp;IPOPT_COPY)
DECL|macro|IPOPT_CLASS
mdefine_line|#define&t;IPOPT_CLASS(o)&t;&t;((o)&amp;IPOPT_CLASS_MASK)
DECL|macro|IPOPT_NUMBER
mdefine_line|#define&t;IPOPT_NUMBER(o)&t;&t;((o)&amp;IPOPT_NUMBER_MASK)
DECL|macro|IPOPT_CONTROL
mdefine_line|#define&t;IPOPT_CONTROL&t;&t;0x00
DECL|macro|IPOPT_RESERVED1
mdefine_line|#define&t;IPOPT_RESERVED1&t;&t;0x20
DECL|macro|IPOPT_MEASUREMENT
mdefine_line|#define&t;IPOPT_MEASUREMENT&t;0x40
DECL|macro|IPOPT_RESERVED2
mdefine_line|#define&t;IPOPT_RESERVED2&t;&t;0x60
DECL|macro|IPOPT_END
mdefine_line|#define IPOPT_END&t;(0 |IPOPT_CONTROL)
DECL|macro|IPOPT_NOOP
mdefine_line|#define IPOPT_NOOP&t;(1 |IPOPT_CONTROL)
DECL|macro|IPOPT_SEC
mdefine_line|#define IPOPT_SEC&t;(2 |IPOPT_CONTROL|IPOPT_COPY)
DECL|macro|IPOPT_LSRR
mdefine_line|#define IPOPT_LSRR&t;(3 |IPOPT_CONTROL|IPOPT_COPY)
DECL|macro|IPOPT_TIMESTAMP
mdefine_line|#define IPOPT_TIMESTAMP&t;(4 |IPOPT_MEASUREMENT)
DECL|macro|IPOPT_RR
mdefine_line|#define IPOPT_RR&t;(7 |IPOPT_CONTROL)
DECL|macro|IPOPT_SID
mdefine_line|#define IPOPT_SID&t;(8 |IPOPT_CONTROL|IPOPT_COPY)
DECL|macro|IPOPT_SSRR
mdefine_line|#define IPOPT_SSRR&t;(9 |IPOPT_CONTROL|IPOPT_COPY)
DECL|macro|IPOPT_RA
mdefine_line|#define IPOPT_RA&t;(20|IPOPT_CONTROL|IPOPT_COPY)
DECL|macro|IPVERSION
mdefine_line|#define IPVERSION&t;4
DECL|macro|MAXTTL
mdefine_line|#define MAXTTL&t;&t;255
DECL|macro|IPDEFTTL
mdefine_line|#define IPDEFTTL&t;64
multiline_comment|/* struct timestamp, struct route and MAX_ROUTES are removed.&n;&n;   REASONS: it is clear that nobody used them because:&n;   - MAX_ROUTES value was wrong.&n;   - &quot;struct route&quot; was wrong.&n;   - &quot;struct timestamp&quot; had fatally misaligned bitfields and was completely unusable.&n; */
DECL|macro|IPOPT_OPTVAL
mdefine_line|#define IPOPT_OPTVAL 0
DECL|macro|IPOPT_OLEN
mdefine_line|#define IPOPT_OLEN   1
DECL|macro|IPOPT_OFFSET
mdefine_line|#define IPOPT_OFFSET 2
DECL|macro|IPOPT_MINOFF
mdefine_line|#define IPOPT_MINOFF 4
DECL|macro|MAX_IPOPTLEN
mdefine_line|#define MAX_IPOPTLEN 40
DECL|macro|IPOPT_NOP
mdefine_line|#define IPOPT_NOP IPOPT_NOOP
DECL|macro|IPOPT_EOL
mdefine_line|#define IPOPT_EOL IPOPT_END
DECL|macro|IPOPT_TS
mdefine_line|#define IPOPT_TS  IPOPT_TIMESTAMP
DECL|macro|IPOPT_TS_TSONLY
mdefine_line|#define&t;IPOPT_TS_TSONLY&t;&t;0&t;&t;/* timestamps only */
DECL|macro|IPOPT_TS_TSANDADDR
mdefine_line|#define&t;IPOPT_TS_TSANDADDR&t;1&t;&t;/* timestamps and addresses */
DECL|macro|IPOPT_TS_PRESPEC
mdefine_line|#define&t;IPOPT_TS_PRESPEC&t;3&t;&t;/* specified modules only */
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;linux/igmp.h&gt;
DECL|struct|ip_options
r_struct
id|ip_options
(brace
DECL|member|faddr
id|__u32
id|faddr
suffix:semicolon
multiline_comment|/* Saved first hop address */
DECL|member|optlen
r_int
r_char
id|optlen
suffix:semicolon
DECL|member|srr
r_int
r_char
id|srr
suffix:semicolon
DECL|member|rr
r_int
r_char
id|rr
suffix:semicolon
DECL|member|ts
r_int
r_char
id|ts
suffix:semicolon
DECL|member|is_setbyuser
r_int
r_char
id|is_setbyuser
suffix:colon
l_int|1
comma
multiline_comment|/* Set by setsockopt?&t;&t;&t;*/
DECL|member|is_data
id|is_data
suffix:colon
l_int|1
comma
multiline_comment|/* Options in __data, rather than skb&t;*/
DECL|member|is_strictroute
id|is_strictroute
suffix:colon
l_int|1
comma
multiline_comment|/* Strict source route&t;&t;&t;*/
DECL|member|srr_is_hit
id|srr_is_hit
suffix:colon
l_int|1
comma
multiline_comment|/* Packet destination addr was our one&t;*/
DECL|member|is_changed
id|is_changed
suffix:colon
l_int|1
comma
multiline_comment|/* IP checksum more not valid&t;&t;*/
DECL|member|rr_needaddr
id|rr_needaddr
suffix:colon
l_int|1
comma
multiline_comment|/* Need to record addr of outgoing dev&t;*/
DECL|member|ts_needtime
id|ts_needtime
suffix:colon
l_int|1
comma
multiline_comment|/* Need to record timestamp&t;&t;*/
DECL|member|ts_needaddr
id|ts_needaddr
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Need to record addr of outgoing dev  */
DECL|member|router_alert
r_int
r_char
id|router_alert
suffix:semicolon
DECL|member|__pad1
r_int
r_char
id|__pad1
suffix:semicolon
DECL|member|__pad2
r_int
r_char
id|__pad2
suffix:semicolon
DECL|member|__data
r_int
r_char
id|__data
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|optlength
mdefine_line|#define optlength(opt) (sizeof(struct ip_options) + opt-&gt;optlen)
DECL|struct|inet_opt
r_struct
id|inet_opt
(brace
multiline_comment|/* Socket demultiplex comparisons on incoming packets. */
DECL|member|daddr
id|__u32
id|daddr
suffix:semicolon
multiline_comment|/* Foreign IPv4 addr */
DECL|member|rcv_saddr
id|__u32
id|rcv_saddr
suffix:semicolon
multiline_comment|/* Bound local IPv4 addr */
DECL|member|dport
id|__u16
id|dport
suffix:semicolon
multiline_comment|/* Destination port */
DECL|member|num
id|__u16
id|num
suffix:semicolon
multiline_comment|/* Local port */
DECL|member|saddr
id|__u32
id|saddr
suffix:semicolon
multiline_comment|/* Sending source */
DECL|member|ttl
r_int
id|ttl
suffix:semicolon
multiline_comment|/* TTL setting */
DECL|member|tos
r_int
id|tos
suffix:semicolon
multiline_comment|/* TOS */
DECL|member|cmsg_flags
r_int
id|cmsg_flags
suffix:semicolon
DECL|member|opt
r_struct
id|ip_options
op_star
id|opt
suffix:semicolon
DECL|member|sport
id|__u16
id|sport
suffix:semicolon
multiline_comment|/* Source port */
DECL|member|hdrincl
r_int
r_char
id|hdrincl
suffix:semicolon
multiline_comment|/* Include headers ? */
DECL|member|mc_ttl
id|__u8
id|mc_ttl
suffix:semicolon
multiline_comment|/* Multicasting TTL */
DECL|member|mc_loop
id|__u8
id|mc_loop
suffix:semicolon
multiline_comment|/* Loopback */
DECL|member|pmtudisc
id|__u8
id|pmtudisc
suffix:semicolon
DECL|member|id
id|__u16
id|id
suffix:semicolon
multiline_comment|/* ID counter for DF pkts */
DECL|member|recverr
r_int
id|recverr
suffix:colon
l_int|1
comma
DECL|member|freebind
id|freebind
suffix:colon
l_int|1
suffix:semicolon
DECL|member|mc_index
r_int
id|mc_index
suffix:semicolon
multiline_comment|/* Multicast device index */
DECL|member|mc_addr
id|__u32
id|mc_addr
suffix:semicolon
DECL|member|mc_list
r_struct
id|ip_mc_socklist
op_star
id|mc_list
suffix:semicolon
multiline_comment|/* Group array */
)brace
suffix:semicolon
r_struct
id|ipv6_pinfo
suffix:semicolon
multiline_comment|/* WARNING: don&squot;t change the layout of the members in inet_sock! */
DECL|struct|inet_sock
r_struct
id|inet_sock
(brace
DECL|member|sk
r_struct
id|sock
id|sk
suffix:semicolon
macro_line|#if defined(CONFIG_IPV6) || defined(CONFIG_IPV6_MODULE)
DECL|member|pinet6
r_struct
id|ipv6_pinfo
op_star
id|pinet6
suffix:semicolon
macro_line|#endif
DECL|member|inet
r_struct
id|inet_opt
id|inet
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|inet_sk
mdefine_line|#define inet_sk(__sk) (&amp;((struct inet_sock *)__sk)-&gt;inet)
macro_line|#endif
DECL|struct|iphdr
r_struct
id|iphdr
(brace
macro_line|#if defined(__LITTLE_ENDIAN_BITFIELD)
DECL|member|ihl
id|__u8
id|ihl
suffix:colon
l_int|4
comma
DECL|member|version
id|version
suffix:colon
l_int|4
suffix:semicolon
macro_line|#elif defined (__BIG_ENDIAN_BITFIELD)
id|__u8
id|version
suffix:colon
l_int|4
comma
id|ihl
suffix:colon
l_int|4
suffix:semicolon
macro_line|#else
macro_line|#error&t;&quot;Please fix &lt;asm/byteorder.h&gt;&quot;
macro_line|#endif
DECL|member|tos
id|__u8
id|tos
suffix:semicolon
DECL|member|tot_len
id|__u16
id|tot_len
suffix:semicolon
DECL|member|id
id|__u16
id|id
suffix:semicolon
DECL|member|frag_off
id|__u16
id|frag_off
suffix:semicolon
DECL|member|ttl
id|__u8
id|ttl
suffix:semicolon
DECL|member|protocol
id|__u8
id|protocol
suffix:semicolon
DECL|member|check
id|__u16
id|check
suffix:semicolon
DECL|member|saddr
id|__u32
id|saddr
suffix:semicolon
DECL|member|daddr
id|__u32
id|daddr
suffix:semicolon
multiline_comment|/*The options start here. */
)brace
suffix:semicolon
macro_line|#endif&t;/* _LINUX_IP_H */
eof
