multiline_comment|/*&n; * INET&t;&t;An implementation of the TCP/IP protocol suite for the LINUX&n; *&t;&t;operating system.  INET is implemented using the  BSD Socket&n; *&t;&t;interface as the means of communication with the user level.&n; *&n; *&t;&t;Global definitions for the IP router interface.&n; *&n; * Version:&t;@(#)route.h&t;1.0.3&t;05/27/93&n; *&n; * Authors:&t;Original taken from Berkeley UNIX 4.3, (c) UCB 1986-1988&n; *&t;&t;for the purposes of compatibility only.&n; *&n; *&t;&t;Fred N. van Kempen, &lt;waltje@uWalt.NL.Mugnet.ORG&gt;&n; *&n; * Changes:&n; *              Mike McLagan    :       Routing by source&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _LINUX_ROUTE_H
DECL|macro|_LINUX_ROUTE_H
mdefine_line|#define _LINUX_ROUTE_H
macro_line|#include &lt;linux/if.h&gt;
multiline_comment|/* This structure gets passed by the SIOCADDRT and SIOCDELRT calls. */
DECL|struct|rtentry
r_struct
id|rtentry
(brace
DECL|member|rt_pad1
r_int
r_int
id|rt_pad1
suffix:semicolon
DECL|member|rt_dst
r_struct
id|sockaddr
id|rt_dst
suffix:semicolon
multiline_comment|/* target address&t;&t;*/
DECL|member|rt_gateway
r_struct
id|sockaddr
id|rt_gateway
suffix:semicolon
multiline_comment|/* gateway addr (RTF_GATEWAY)&t;*/
DECL|member|rt_genmask
r_struct
id|sockaddr
id|rt_genmask
suffix:semicolon
multiline_comment|/* target network mask (IP)&t;*/
DECL|member|rt_flags
r_int
r_int
id|rt_flags
suffix:semicolon
DECL|member|rt_pad2
r_int
id|rt_pad2
suffix:semicolon
DECL|member|rt_pad3
r_int
r_int
id|rt_pad3
suffix:semicolon
DECL|member|rt_pad4
r_void
op_star
id|rt_pad4
suffix:semicolon
DECL|member|rt_metric
r_int
id|rt_metric
suffix:semicolon
multiline_comment|/* +1 for binary compatibility!&t;*/
DECL|member|rt_dev
r_char
op_star
id|rt_dev
suffix:semicolon
multiline_comment|/* forcing the device at add&t;*/
DECL|member|rt_mtu
r_int
r_int
id|rt_mtu
suffix:semicolon
multiline_comment|/* per route MTU/Window &t;*/
macro_line|#ifndef __KERNEL__
DECL|macro|rt_mss
mdefine_line|#define rt_mss&t;rt_mtu&t;&t;&t;/* Compatibility :-(            */
macro_line|#endif
DECL|member|rt_window
r_int
r_int
id|rt_window
suffix:semicolon
multiline_comment|/* Window clamping &t;&t;*/
DECL|member|rt_irtt
r_int
r_int
id|rt_irtt
suffix:semicolon
multiline_comment|/* Initial RTT&t;&t;&t;*/
)brace
suffix:semicolon
DECL|macro|RTF_UP
mdefine_line|#define&t;RTF_UP&t;&t;0x0001&t;&t;/* route usable&t;&t;  &t;*/
DECL|macro|RTF_GATEWAY
mdefine_line|#define&t;RTF_GATEWAY&t;0x0002&t;&t;/* destination is a gateway&t;*/
DECL|macro|RTF_HOST
mdefine_line|#define&t;RTF_HOST&t;0x0004&t;&t;/* host entry (net otherwise)&t;*/
DECL|macro|RTF_REINSTATE
mdefine_line|#define RTF_REINSTATE&t;0x0008&t;&t;/* reinstate route after tmout&t;*/
DECL|macro|RTF_DYNAMIC
mdefine_line|#define&t;RTF_DYNAMIC&t;0x0010&t;&t;/* created dyn. (by redirect)&t;*/
DECL|macro|RTF_MODIFIED
mdefine_line|#define&t;RTF_MODIFIED&t;0x0020&t;&t;/* modified dyn. (by redirect)&t;*/
DECL|macro|RTF_MTU
mdefine_line|#define RTF_MTU&t;&t;0x0040&t;&t;/* specific MTU for this route&t;*/
DECL|macro|RTF_MSS
mdefine_line|#define RTF_MSS&t;&t;RTF_MTU&t;&t;/* Compatibility :-(&t;&t;*/
DECL|macro|RTF_WINDOW
mdefine_line|#define RTF_WINDOW&t;0x0080&t;&t;/* per route window clamping&t;*/
DECL|macro|RTF_IRTT
mdefine_line|#define RTF_IRTT&t;0x0100&t;&t;/* Initial round trip time&t;*/
DECL|macro|RTF_REJECT
mdefine_line|#define RTF_REJECT&t;0x0200&t;&t;/* Reject route&t;&t;&t;*/
multiline_comment|/*&n; *&t;&lt;linux/ipv6_route.h&gt; uses RTF values &gt;= 64k&n; */
macro_line|#endif&t;/* _LINUX_ROUTE_H */
eof
