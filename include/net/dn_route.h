macro_line|#ifndef _NET_DN_ROUTE_H
DECL|macro|_NET_DN_ROUTE_H
mdefine_line|#define _NET_DN_ROUTE_H
multiline_comment|/******************************************************************************&n;    (c) 1995-1998 E.M. Serrat&t;&t;emserrat@geocities.com&n;    &n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;*******************************************************************************/
r_extern
r_struct
id|sk_buff
op_star
id|dn_alloc_skb
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_int
id|size
comma
r_int
id|pri
)paren
suffix:semicolon
r_extern
r_int
id|dn_route_output_sock
c_func
(paren
r_struct
id|dst_entry
op_star
op_star
id|pprt
comma
r_struct
id|flowi
op_star
comma
r_struct
id|sock
op_star
id|sk
comma
r_int
id|flags
)paren
suffix:semicolon
r_extern
r_int
id|dn_cache_dump
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
id|dn_cache_getroute
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|nlmsghdr
op_star
id|nlh
comma
r_void
op_star
id|arg
)paren
suffix:semicolon
r_extern
r_void
id|dn_rt_cache_flush
c_func
(paren
r_int
id|delay
)paren
suffix:semicolon
multiline_comment|/* Masks for flags field */
DECL|macro|DN_RT_F_PID
mdefine_line|#define DN_RT_F_PID 0x07 /* Mask for packet type                      */
DECL|macro|DN_RT_F_PF
mdefine_line|#define DN_RT_F_PF  0x80 /* Padding Follows                           */
DECL|macro|DN_RT_F_VER
mdefine_line|#define DN_RT_F_VER 0x40 /* Version =0 discard packet if ==1          */
DECL|macro|DN_RT_F_IE
mdefine_line|#define DN_RT_F_IE  0x20 /* Intra Ethernet, Reserved in short pkt     */
DECL|macro|DN_RT_F_RTS
mdefine_line|#define DN_RT_F_RTS 0x10 /* Packet is being returned to sender        */
DECL|macro|DN_RT_F_RQR
mdefine_line|#define DN_RT_F_RQR 0x08 /* Return packet to sender upon non-delivery */
multiline_comment|/* Mask for types of routing packets */
DECL|macro|DN_RT_PKT_MSK
mdefine_line|#define DN_RT_PKT_MSK   0x06
multiline_comment|/* Types of routing packets */
DECL|macro|DN_RT_PKT_SHORT
mdefine_line|#define DN_RT_PKT_SHORT 0x02 /* Short routing packet */
DECL|macro|DN_RT_PKT_LONG
mdefine_line|#define DN_RT_PKT_LONG  0x06 /* Long routing packet  */
multiline_comment|/* Mask for control/routing selection */
DECL|macro|DN_RT_PKT_CNTL
mdefine_line|#define DN_RT_PKT_CNTL  0x01 /* Set to 1 if a control packet  */
multiline_comment|/* Types of control packets */
DECL|macro|DN_RT_CNTL_MSK
mdefine_line|#define DN_RT_CNTL_MSK  0x0f /* Mask for control packets      */
DECL|macro|DN_RT_PKT_INIT
mdefine_line|#define DN_RT_PKT_INIT  0x01 /* Initialisation packet         */
DECL|macro|DN_RT_PKT_VERI
mdefine_line|#define DN_RT_PKT_VERI  0x03 /* Verification Message          */
DECL|macro|DN_RT_PKT_HELO
mdefine_line|#define DN_RT_PKT_HELO  0x05 /* Hello and Test Message        */
DECL|macro|DN_RT_PKT_L1RT
mdefine_line|#define DN_RT_PKT_L1RT  0x07 /* Level 1 Routing Message       */
DECL|macro|DN_RT_PKT_L2RT
mdefine_line|#define DN_RT_PKT_L2RT  0x09 /* Level 2 Routing Message       */
DECL|macro|DN_RT_PKT_ERTH
mdefine_line|#define DN_RT_PKT_ERTH  0x0b /* Ethernet Router Hello         */
DECL|macro|DN_RT_PKT_EEDH
mdefine_line|#define DN_RT_PKT_EEDH  0x0d /* Ethernet EndNode Hello        */
multiline_comment|/* Values for info field in hello message */
DECL|macro|DN_RT_INFO_TYPE
mdefine_line|#define DN_RT_INFO_TYPE 0x03 /* Type mask                     */
DECL|macro|DN_RT_INFO_L1RT
mdefine_line|#define DN_RT_INFO_L1RT 0x02 /* L1 Router                     */
DECL|macro|DN_RT_INFO_L2RT
mdefine_line|#define DN_RT_INFO_L2RT 0x01 /* L2 Router                     */
DECL|macro|DN_RT_INFO_ENDN
mdefine_line|#define DN_RT_INFO_ENDN 0x03 /* EndNode                       */
DECL|macro|DN_RT_INFO_VERI
mdefine_line|#define DN_RT_INFO_VERI 0x04 /* Verification Reqd.            */
DECL|macro|DN_RT_INFO_RJCT
mdefine_line|#define DN_RT_INFO_RJCT 0x08 /* Reject Flag, Reserved         */
DECL|macro|DN_RT_INFO_VFLD
mdefine_line|#define DN_RT_INFO_VFLD 0x10 /* Verification Failed, Reserved */
DECL|macro|DN_RT_INFO_NOML
mdefine_line|#define DN_RT_INFO_NOML 0x20 /* No Multicast traffic accepted */
DECL|macro|DN_RT_INFO_BLKR
mdefine_line|#define DN_RT_INFO_BLKR 0x40 /* Blocking Requested            */
multiline_comment|/*&n; * The fl structure is what we used to look up the route.&n; * The rt_saddr &amp; rt_daddr entries are the same as key.saddr &amp; key.daddr&n; * except for local input routes, where the rt_saddr = fl.fld_dst and&n; * rt_daddr = fl.fld_src to allow the route to be used for returning&n; * packets to the originating host.&n; */
DECL|struct|dn_route
r_struct
id|dn_route
(brace
r_union
(brace
DECL|member|dst
r_struct
id|dst_entry
id|dst
suffix:semicolon
DECL|member|rt_next
r_struct
id|dn_route
op_star
id|rt_next
suffix:semicolon
DECL|member|u
)brace
id|u
suffix:semicolon
DECL|member|rt_saddr
id|__u16
id|rt_saddr
suffix:semicolon
DECL|member|rt_daddr
id|__u16
id|rt_daddr
suffix:semicolon
DECL|member|rt_gateway
id|__u16
id|rt_gateway
suffix:semicolon
DECL|member|rt_local_src
id|__u16
id|rt_local_src
suffix:semicolon
multiline_comment|/* Source used for forwarding packets */
DECL|member|rt_src_map
id|__u16
id|rt_src_map
suffix:semicolon
DECL|member|rt_dst_map
id|__u16
id|rt_dst_map
suffix:semicolon
DECL|member|rt_flags
r_int
id|rt_flags
suffix:semicolon
DECL|member|rt_type
r_int
id|rt_type
suffix:semicolon
DECL|member|fl
r_struct
id|flowi
id|fl
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_void
id|dn_route_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|dn_route_cleanup
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;linux/if_arp.h&gt;
DECL|function|dn_rt_send
r_static
r_inline
r_void
id|dn_rt_send
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
id|dev_queue_xmit
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
DECL|function|dn_rt_finish_output
r_static
r_inline
r_void
id|dn_rt_finish_output
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_char
op_star
id|dst
comma
r_char
op_star
id|src
)paren
(brace
r_struct
id|net_device
op_star
id|dev
op_assign
id|skb-&gt;dev
suffix:semicolon
r_if
c_cond
(paren
(paren
id|dev-&gt;type
op_ne
id|ARPHRD_ETHER
)paren
op_logical_and
(paren
id|dev-&gt;type
op_ne
id|ARPHRD_LOOPBACK
)paren
)paren
id|dst
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;hard_header
op_logical_or
(paren
id|dev
op_member_access_from_pointer
id|hard_header
c_func
(paren
id|skb
comma
id|dev
comma
id|ETH_P_DNA_RT
comma
id|dst
comma
id|src
comma
id|skb-&gt;len
)paren
op_ge
l_int|0
)paren
)paren
id|dn_rt_send
c_func
(paren
id|skb
)paren
suffix:semicolon
r_else
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
macro_line|#endif /* _NET_DN_ROUTE_H */
eof
