multiline_comment|/*&n; * INET&t;&t;An implementation of the TCP/IP protocol suite for the LINUX&n; *&t;&t;operating system.  INET is implemented using the  BSD Socket&n; *&t;&t;interface as the means of communication with the user level.&n; *&n; *&t;&t;Definitions of the Internet Protocol.&n; *&n; * Version:&t;@(#)in.h&t;1.0.1&t;04/21/93&n; *&n; * Authors:&t;Original taken from the GNU Project &lt;netinet/in.h&gt; file.&n; *&t;&t;Fred N. van Kempen, &lt;waltje@uWalt.NL.Mugnet.ORG&gt;&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _LINUX_IN_H
DECL|macro|_LINUX_IN_H
mdefine_line|#define _LINUX_IN_H
macro_line|#include &lt;linux/types.h&gt;
multiline_comment|/* Standard well-defined IP protocols.  */
r_enum
(brace
DECL|enumerator|IPPROTO_IP
id|IPPROTO_IP
op_assign
l_int|0
comma
multiline_comment|/* Dummy protocol for TCP&t;&t;*/
DECL|enumerator|IPPROTO_ICMP
id|IPPROTO_ICMP
op_assign
l_int|1
comma
multiline_comment|/* Internet Control Message Protocol&t;*/
DECL|enumerator|IPPROTO_IGMP
id|IPPROTO_IGMP
op_assign
l_int|2
comma
multiline_comment|/* Internet Group Management Protocol&t;*/
DECL|enumerator|IPPROTO_IPIP
id|IPPROTO_IPIP
op_assign
l_int|4
comma
multiline_comment|/* IPIP tunnels (older KA9Q tunnels use 94) */
DECL|enumerator|IPPROTO_TCP
id|IPPROTO_TCP
op_assign
l_int|6
comma
multiline_comment|/* Transmission Control Protocol&t;*/
DECL|enumerator|IPPROTO_EGP
id|IPPROTO_EGP
op_assign
l_int|8
comma
multiline_comment|/* Exterior Gateway Protocol&t;&t;*/
DECL|enumerator|IPPROTO_PUP
id|IPPROTO_PUP
op_assign
l_int|12
comma
multiline_comment|/* PUP protocol&t;&t;&t;&t;*/
DECL|enumerator|IPPROTO_UDP
id|IPPROTO_UDP
op_assign
l_int|17
comma
multiline_comment|/* User Datagram Protocol&t;&t;*/
DECL|enumerator|IPPROTO_IDP
id|IPPROTO_IDP
op_assign
l_int|22
comma
multiline_comment|/* XNS IDP protocol&t;&t;&t;*/
DECL|enumerator|IPPROTO_RSVP
id|IPPROTO_RSVP
op_assign
l_int|46
comma
multiline_comment|/* RSVP protocol&t;&t;&t;*/
DECL|enumerator|IPPROTO_GRE
id|IPPROTO_GRE
op_assign
l_int|47
comma
multiline_comment|/* Cisco GRE tunnels (rfc 1701,1702)&t;*/
DECL|enumerator|IPPROTO_IPV6
id|IPPROTO_IPV6
op_assign
l_int|41
comma
multiline_comment|/* IPv6-in-IPv4 tunnelling&t;&t;*/
DECL|enumerator|IPPROTO_PIM
id|IPPROTO_PIM
op_assign
l_int|103
comma
multiline_comment|/* Protocol Independent Multicast&t;*/
DECL|enumerator|IPPROTO_ESP
id|IPPROTO_ESP
op_assign
l_int|50
comma
multiline_comment|/* Encapsulation Security Payload protocol */
DECL|enumerator|IPPROTO_AH
id|IPPROTO_AH
op_assign
l_int|51
comma
multiline_comment|/* Authentication Header protocol       */
DECL|enumerator|IPPROTO_COMP
id|IPPROTO_COMP
op_assign
l_int|108
comma
multiline_comment|/* Compression Header protocol */
DECL|enumerator|IPPROTO_RAW
id|IPPROTO_RAW
op_assign
l_int|255
comma
multiline_comment|/* Raw IP packets&t;&t;&t;*/
DECL|enumerator|IPPROTO_MAX
id|IPPROTO_MAX
)brace
suffix:semicolon
multiline_comment|/* Internet address. */
DECL|struct|in_addr
r_struct
id|in_addr
(brace
DECL|member|s_addr
id|__u32
id|s_addr
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|IP_TOS
mdefine_line|#define IP_TOS&t;&t;1
DECL|macro|IP_TTL
mdefine_line|#define IP_TTL&t;&t;2
DECL|macro|IP_HDRINCL
mdefine_line|#define IP_HDRINCL&t;3
DECL|macro|IP_OPTIONS
mdefine_line|#define IP_OPTIONS&t;4
DECL|macro|IP_ROUTER_ALERT
mdefine_line|#define IP_ROUTER_ALERT&t;5
DECL|macro|IP_RECVOPTS
mdefine_line|#define IP_RECVOPTS&t;6
DECL|macro|IP_RETOPTS
mdefine_line|#define IP_RETOPTS&t;7
DECL|macro|IP_PKTINFO
mdefine_line|#define IP_PKTINFO&t;8
DECL|macro|IP_PKTOPTIONS
mdefine_line|#define IP_PKTOPTIONS&t;9
DECL|macro|IP_MTU_DISCOVER
mdefine_line|#define IP_MTU_DISCOVER&t;10
DECL|macro|IP_RECVERR
mdefine_line|#define IP_RECVERR&t;11
DECL|macro|IP_RECVTTL
mdefine_line|#define IP_RECVTTL&t;12
DECL|macro|IP_RECVTOS
mdefine_line|#define&t;IP_RECVTOS&t;13
DECL|macro|IP_MTU
mdefine_line|#define IP_MTU&t;&t;14
DECL|macro|IP_FREEBIND
mdefine_line|#define IP_FREEBIND&t;15
multiline_comment|/* BSD compatibility */
DECL|macro|IP_RECVRETOPTS
mdefine_line|#define IP_RECVRETOPTS&t;IP_RETOPTS
multiline_comment|/* IP_MTU_DISCOVER values */
DECL|macro|IP_PMTUDISC_DONT
mdefine_line|#define IP_PMTUDISC_DONT&t;&t;0&t;/* Never send DF frames */
DECL|macro|IP_PMTUDISC_WANT
mdefine_line|#define IP_PMTUDISC_WANT&t;&t;1&t;/* Use per route hints&t;*/
DECL|macro|IP_PMTUDISC_DO
mdefine_line|#define IP_PMTUDISC_DO&t;&t;&t;2&t;/* Always DF&t;&t;*/
DECL|macro|IP_MULTICAST_IF
mdefine_line|#define IP_MULTICAST_IF&t;&t;&t;32
DECL|macro|IP_MULTICAST_TTL
mdefine_line|#define IP_MULTICAST_TTL &t;&t;33
DECL|macro|IP_MULTICAST_LOOP
mdefine_line|#define IP_MULTICAST_LOOP &t;&t;34
DECL|macro|IP_ADD_MEMBERSHIP
mdefine_line|#define IP_ADD_MEMBERSHIP&t;&t;35
DECL|macro|IP_DROP_MEMBERSHIP
mdefine_line|#define IP_DROP_MEMBERSHIP&t;&t;36
multiline_comment|/* These need to appear somewhere around here */
DECL|macro|IP_DEFAULT_MULTICAST_TTL
mdefine_line|#define IP_DEFAULT_MULTICAST_TTL        1
DECL|macro|IP_DEFAULT_MULTICAST_LOOP
mdefine_line|#define IP_DEFAULT_MULTICAST_LOOP       1
multiline_comment|/* Request struct for multicast socket ops */
DECL|struct|ip_mreq
r_struct
id|ip_mreq
(brace
DECL|member|imr_multiaddr
r_struct
id|in_addr
id|imr_multiaddr
suffix:semicolon
multiline_comment|/* IP multicast address of group */
DECL|member|imr_interface
r_struct
id|in_addr
id|imr_interface
suffix:semicolon
multiline_comment|/* local IP address of interface */
)brace
suffix:semicolon
DECL|struct|ip_mreqn
r_struct
id|ip_mreqn
(brace
DECL|member|imr_multiaddr
r_struct
id|in_addr
id|imr_multiaddr
suffix:semicolon
multiline_comment|/* IP multicast address of group */
DECL|member|imr_address
r_struct
id|in_addr
id|imr_address
suffix:semicolon
multiline_comment|/* local IP address of interface */
DECL|member|imr_ifindex
r_int
id|imr_ifindex
suffix:semicolon
multiline_comment|/* Interface index */
)brace
suffix:semicolon
DECL|struct|in_pktinfo
r_struct
id|in_pktinfo
(brace
DECL|member|ipi_ifindex
r_int
id|ipi_ifindex
suffix:semicolon
DECL|member|ipi_spec_dst
r_struct
id|in_addr
id|ipi_spec_dst
suffix:semicolon
DECL|member|ipi_addr
r_struct
id|in_addr
id|ipi_addr
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Structure describing an Internet (IP) socket address. */
DECL|macro|__SOCK_SIZE__
mdefine_line|#define __SOCK_SIZE__&t;16&t;&t;/* sizeof(struct sockaddr)&t;*/
DECL|struct|sockaddr_in
r_struct
id|sockaddr_in
(brace
DECL|member|sin_family
id|sa_family_t
id|sin_family
suffix:semicolon
multiline_comment|/* Address family&t;&t;*/
DECL|member|sin_port
r_int
r_int
r_int
id|sin_port
suffix:semicolon
multiline_comment|/* Port number&t;&t;&t;*/
DECL|member|sin_addr
r_struct
id|in_addr
id|sin_addr
suffix:semicolon
multiline_comment|/* Internet address&t;&t;*/
multiline_comment|/* Pad to size of `struct sockaddr&squot;. */
DECL|member|__pad
r_int
r_char
id|__pad
(braket
id|__SOCK_SIZE__
op_minus
r_sizeof
(paren
r_int
r_int
)paren
op_minus
r_sizeof
(paren
r_int
r_int
r_int
)paren
op_minus
r_sizeof
(paren
r_struct
id|in_addr
)paren
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|sin_zero
mdefine_line|#define sin_zero&t;__pad&t;&t;/* for BSD UNIX comp. -FvK&t;*/
multiline_comment|/*&n; * Definitions of the bits in an Internet address integer.&n; * On subnets, host and network parts are found according&n; * to the subnet mask, not these masks.&n; */
DECL|macro|IN_CLASSA
mdefine_line|#define&t;IN_CLASSA(a)&t;&t;((((long int) (a)) &amp; 0x80000000) == 0)
DECL|macro|IN_CLASSA_NET
mdefine_line|#define&t;IN_CLASSA_NET&t;&t;0xff000000
DECL|macro|IN_CLASSA_NSHIFT
mdefine_line|#define&t;IN_CLASSA_NSHIFT&t;24
DECL|macro|IN_CLASSA_HOST
mdefine_line|#define&t;IN_CLASSA_HOST&t;&t;(0xffffffff &amp; ~IN_CLASSA_NET)
DECL|macro|IN_CLASSA_MAX
mdefine_line|#define&t;IN_CLASSA_MAX&t;&t;128
DECL|macro|IN_CLASSB
mdefine_line|#define&t;IN_CLASSB(a)&t;&t;((((long int) (a)) &amp; 0xc0000000) == 0x80000000)
DECL|macro|IN_CLASSB_NET
mdefine_line|#define&t;IN_CLASSB_NET&t;&t;0xffff0000
DECL|macro|IN_CLASSB_NSHIFT
mdefine_line|#define&t;IN_CLASSB_NSHIFT&t;16
DECL|macro|IN_CLASSB_HOST
mdefine_line|#define&t;IN_CLASSB_HOST&t;&t;(0xffffffff &amp; ~IN_CLASSB_NET)
DECL|macro|IN_CLASSB_MAX
mdefine_line|#define&t;IN_CLASSB_MAX&t;&t;65536
DECL|macro|IN_CLASSC
mdefine_line|#define&t;IN_CLASSC(a)&t;&t;((((long int) (a)) &amp; 0xe0000000) == 0xc0000000)
DECL|macro|IN_CLASSC_NET
mdefine_line|#define&t;IN_CLASSC_NET&t;&t;0xffffff00
DECL|macro|IN_CLASSC_NSHIFT
mdefine_line|#define&t;IN_CLASSC_NSHIFT&t;8
DECL|macro|IN_CLASSC_HOST
mdefine_line|#define&t;IN_CLASSC_HOST&t;&t;(0xffffffff &amp; ~IN_CLASSC_NET)
DECL|macro|IN_CLASSD
mdefine_line|#define&t;IN_CLASSD(a)&t;&t;((((long int) (a)) &amp; 0xf0000000) == 0xe0000000)
DECL|macro|IN_MULTICAST
mdefine_line|#define&t;IN_MULTICAST(a)&t;&t;IN_CLASSD(a)
DECL|macro|IN_MULTICAST_NET
mdefine_line|#define IN_MULTICAST_NET&t;0xF0000000
DECL|macro|IN_EXPERIMENTAL
mdefine_line|#define&t;IN_EXPERIMENTAL(a)&t;((((long int) (a)) &amp; 0xf0000000) == 0xf0000000)
DECL|macro|IN_BADCLASS
mdefine_line|#define&t;IN_BADCLASS(a)&t;&t;IN_EXPERIMENTAL((a))
multiline_comment|/* Address to accept any incoming messages. */
DECL|macro|INADDR_ANY
mdefine_line|#define&t;INADDR_ANY&t;&t;((unsigned long int) 0x00000000)
multiline_comment|/* Address to send to all hosts. */
DECL|macro|INADDR_BROADCAST
mdefine_line|#define&t;INADDR_BROADCAST&t;((unsigned long int) 0xffffffff)
multiline_comment|/* Address indicating an error return. */
DECL|macro|INADDR_NONE
mdefine_line|#define&t;INADDR_NONE&t;&t;((unsigned long int) 0xffffffff)
multiline_comment|/* Network number for local host loopback. */
DECL|macro|IN_LOOPBACKNET
mdefine_line|#define&t;IN_LOOPBACKNET&t;&t;127
multiline_comment|/* Address to loopback in software to local host.  */
DECL|macro|INADDR_LOOPBACK
mdefine_line|#define&t;INADDR_LOOPBACK&t;&t;0x7f000001&t;/* 127.0.0.1   */
DECL|macro|IN_LOOPBACK
mdefine_line|#define&t;IN_LOOPBACK(a)&t;&t;((((long int) (a)) &amp; 0xff000000) == 0x7f000000)
multiline_comment|/* Defines for Multicast INADDR */
DECL|macro|INADDR_UNSPEC_GROUP
mdefine_line|#define INADDR_UNSPEC_GROUP   &t;0xe0000000U&t;/* 224.0.0.0   */
DECL|macro|INADDR_ALLHOSTS_GROUP
mdefine_line|#define INADDR_ALLHOSTS_GROUP &t;0xe0000001U&t;/* 224.0.0.1   */
DECL|macro|INADDR_ALLRTRS_GROUP
mdefine_line|#define INADDR_ALLRTRS_GROUP    0xe0000002U&t;/* 224.0.0.2 */
DECL|macro|INADDR_MAX_LOCAL_GROUP
mdefine_line|#define INADDR_MAX_LOCAL_GROUP  0xe00000ffU&t;/* 224.0.0.255 */
multiline_comment|/* &lt;asm/byteorder.h&gt; contains the htonl type stuff.. */
macro_line|#include &lt;asm/byteorder.h&gt; 
macro_line|#ifdef __KERNEL__
multiline_comment|/* Some random defines to make it easier in the kernel.. */
DECL|macro|LOOPBACK
mdefine_line|#define LOOPBACK(x)&t;(((x) &amp; htonl(0xff000000)) == htonl(0x7f000000))
DECL|macro|MULTICAST
mdefine_line|#define MULTICAST(x)&t;(((x) &amp; htonl(0xf0000000)) == htonl(0xe0000000))
DECL|macro|BADCLASS
mdefine_line|#define BADCLASS(x)&t;(((x) &amp; htonl(0xf0000000)) == htonl(0xf0000000))
DECL|macro|ZERONET
mdefine_line|#define ZERONET(x)&t;(((x) &amp; htonl(0xff000000)) == htonl(0x00000000))
DECL|macro|LOCAL_MCAST
mdefine_line|#define LOCAL_MCAST(x)&t;(((x) &amp; htonl(0xFFFFFF00)) == htonl(0xE0000000))
macro_line|#endif
macro_line|#endif&t;/* _LINUX_IN_H */
eof
