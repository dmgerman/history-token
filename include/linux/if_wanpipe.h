multiline_comment|/*****************************************************************************&n;* if_wanpipe.h&t;Header file for the Sangoma AF_WANPIPE Socket &t;&n;*&n;* Author: &t;Nenad Corbic &t;&n;*&n;* Copyright:&t;(c) 2000 Sangoma Technologies Inc.&n;*&n;*&t;&t;This program is free software; you can redistribute it and/or&n;*&t;&t;modify it under the terms of the GNU General Public License&n;*&t;&t;as published by the Free Software Foundation; either version&n;*&t;&t;2 of the License, or (at your option) any later version.&n;* ============================================================================&n;*&n;* Jan 28, 2000&t;Nenad Corbic &t;Initial Version&n;*&n;*****************************************************************************/
macro_line|#ifndef __LINUX_IF_WAN_PACKET_H
DECL|macro|__LINUX_IF_WAN_PACKET_H
mdefine_line|#define __LINUX_IF_WAN_PACKET_H
DECL|struct|wan_sockaddr_ll
r_struct
id|wan_sockaddr_ll
(brace
DECL|member|sll_family
r_int
r_int
id|sll_family
suffix:semicolon
DECL|member|sll_protocol
r_int
r_int
id|sll_protocol
suffix:semicolon
DECL|member|sll_ifindex
r_int
id|sll_ifindex
suffix:semicolon
DECL|member|sll_hatype
r_int
r_int
id|sll_hatype
suffix:semicolon
DECL|member|sll_pkttype
r_int
r_char
id|sll_pkttype
suffix:semicolon
DECL|member|sll_halen
r_int
r_char
id|sll_halen
suffix:semicolon
DECL|member|sll_addr
r_int
r_char
id|sll_addr
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|sll_device
r_int
r_char
id|sll_device
(braket
l_int|14
)braket
suffix:semicolon
DECL|member|sll_card
r_int
r_char
id|sll_card
(braket
l_int|14
)braket
suffix:semicolon
)brace
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|free
r_int
r_char
id|free
suffix:semicolon
DECL|member|sk_state
r_int
r_char
id|sk_state
suffix:semicolon
DECL|member|rcvbuf
r_int
id|rcvbuf
suffix:semicolon
DECL|member|sndbuf
r_int
id|sndbuf
suffix:semicolon
DECL|member|rmem
r_int
id|rmem
suffix:semicolon
DECL|member|wmem
r_int
id|wmem
suffix:semicolon
DECL|member|sk_count
r_int
id|sk_count
suffix:semicolon
DECL|member|bound
r_int
r_char
id|bound
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
l_int|14
)braket
suffix:semicolon
DECL|member|d_state
r_int
r_char
id|d_state
suffix:semicolon
DECL|member|svc
r_int
r_char
id|svc
suffix:semicolon
DECL|member|lcn
r_int
r_int
id|lcn
suffix:semicolon
DECL|member|mbox
r_int
r_char
id|mbox
suffix:semicolon
DECL|member|cmd_busy
r_int
r_char
id|cmd_busy
suffix:semicolon
DECL|member|command
r_int
r_char
id|command
suffix:semicolon
DECL|member|poll
r_int
id|poll
suffix:semicolon
DECL|member|poll_cnt
r_int
id|poll_cnt
suffix:semicolon
DECL|member|rblock
r_int
id|rblock
suffix:semicolon
DECL|typedef|wan_debug_hdr_t
)brace
id|wan_debug_hdr_t
suffix:semicolon
DECL|macro|MAX_NUM_DEBUG
mdefine_line|#define MAX_NUM_DEBUG  10
DECL|macro|X25_PROT
mdefine_line|#define X25_PROT       0x16
DECL|macro|PVC_PROT
mdefine_line|#define PVC_PROT       0x17&t;
r_typedef
r_struct
(brace
DECL|member|debug
id|wan_debug_hdr_t
id|debug
(braket
id|MAX_NUM_DEBUG
)braket
suffix:semicolon
DECL|typedef|wan_debug_t
)brace
id|wan_debug_t
suffix:semicolon
DECL|macro|SIOC_WANPIPE_GET_CALL_DATA
mdefine_line|#define&t;SIOC_WANPIPE_GET_CALL_DATA&t;(SIOCPROTOPRIVATE + 0)
DECL|macro|SIOC_WANPIPE_SET_CALL_DATA
mdefine_line|#define&t;SIOC_WANPIPE_SET_CALL_DATA&t;(SIOCPROTOPRIVATE + 1)
DECL|macro|SIOC_WANPIPE_ACCEPT_CALL
mdefine_line|#define SIOC_WANPIPE_ACCEPT_CALL&t;(SIOCPROTOPRIVATE + 2)
DECL|macro|SIOC_WANPIPE_CLEAR_CALL
mdefine_line|#define SIOC_WANPIPE_CLEAR_CALL&t;        (SIOCPROTOPRIVATE + 3)
DECL|macro|SIOC_WANPIPE_RESET_CALL
mdefine_line|#define SIOC_WANPIPE_RESET_CALL&t;        (SIOCPROTOPRIVATE + 4)
DECL|macro|SIOC_WANPIPE_DEBUG
mdefine_line|#define SIOC_WANPIPE_DEBUG&t;        (SIOCPROTOPRIVATE + 5)
DECL|macro|SIOC_WANPIPE_SET_NONBLOCK
mdefine_line|#define SIOC_WANPIPE_SET_NONBLOCK&t;(SIOCPROTOPRIVATE + 6)
DECL|macro|SIOC_WANPIPE_CHECK_TX
mdefine_line|#define SIOC_WANPIPE_CHECK_TX&t;&t;(SIOCPROTOPRIVATE + 7)
DECL|macro|SIOC_WANPIPE_SOCK_STATE
mdefine_line|#define SIOC_WANPIPE_SOCK_STATE&t;&t;(SIOCPROTOPRIVATE + 8)
multiline_comment|/* Packet types */
DECL|macro|WAN_PACKET_HOST
mdefine_line|#define WAN_PACKET_HOST&t;&t;0&t;&t;/* To us&t;&t;*/
DECL|macro|WAN_PACKET_BROADCAST
mdefine_line|#define WAN_PACKET_BROADCAST&t;1&t;&t;/* To all&t;&t;*/
DECL|macro|WAN_PACKET_MULTICAST
mdefine_line|#define WAN_PACKET_MULTICAST&t;2&t;&t;/* To group&t;&t;*/
DECL|macro|WAN_PACKET_OTHERHOST
mdefine_line|#define WAN_PACKET_OTHERHOST&t;3&t;&t;/* To someone else &t;*/
DECL|macro|WAN_PACKET_OUTGOING
mdefine_line|#define WAN_PACKET_OUTGOING&t;&t;4&t;&t;/* Outgoing of any type */
multiline_comment|/* These ones are invisible by user level */
DECL|macro|WAN_PACKET_LOOPBACK
mdefine_line|#define WAN_PACKET_LOOPBACK&t;&t;5&t;&t;/* MC/BRD frame looped back */
DECL|macro|WAN_PACKET_FASTROUTE
mdefine_line|#define WAN_PACKET_FASTROUTE&t;6&t;&t;/* Fastrouted frame&t;*/
multiline_comment|/* X25 specific */
DECL|macro|WAN_PACKET_DATA
mdefine_line|#define WAN_PACKET_DATA &t;7
DECL|macro|WAN_PACKET_CMD
mdefine_line|#define WAN_PACKET_CMD &t;&t;8
DECL|macro|WAN_PACKET_ASYNC
mdefine_line|#define WAN_PACKET_ASYNC&t;9
DECL|macro|WAN_PACKET_ERR
mdefine_line|#define WAN_PACKET_ERR&t;       10
multiline_comment|/* Packet socket options */
DECL|macro|WAN_PACKET_ADD_MEMBERSHIP
mdefine_line|#define WAN_PACKET_ADD_MEMBERSHIP&t;&t;1
DECL|macro|WAN_PACKET_DROP_MEMBERSHIP
mdefine_line|#define WAN_PACKET_DROP_MEMBERSHIP&t;&t;2
DECL|macro|WAN_PACKET_MR_MULTICAST
mdefine_line|#define WAN_PACKET_MR_MULTICAST&t;0
DECL|macro|WAN_PACKET_MR_PROMISC
mdefine_line|#define WAN_PACKET_MR_PROMISC&t;1
DECL|macro|WAN_PACKET_MR_ALLMULTI
mdefine_line|#define WAN_PACKET_MR_ALLMULTI&t;2
macro_line|#ifdef __KERNEL__
macro_line|#ifndef netdevice_t
macro_line|#include &lt;linux/version.h&gt;
macro_line|#if LINUX_VERSION_CODE &gt;= KERNEL_VERSION(2,3,0)
DECL|macro|netdevice_t
mdefine_line|#define netdevice_t struct net_device
macro_line|#else
DECL|macro|netdevice_t
mdefine_line|#define netdevice_t struct device
macro_line|#endif
macro_line|#endif
multiline_comment|/* Private wanpipe socket structures. */
DECL|struct|wanpipe_opt
r_struct
id|wanpipe_opt
(brace
DECL|member|mbox
r_void
op_star
id|mbox
suffix:semicolon
multiline_comment|/* Mail box  */
DECL|member|card
r_void
op_star
id|card
suffix:semicolon
multiline_comment|/* Card bouded to */
DECL|member|dev
id|netdevice_t
op_star
id|dev
suffix:semicolon
multiline_comment|/* Bounded device */
DECL|member|lcn
r_int
r_int
id|lcn
suffix:semicolon
multiline_comment|/* Binded LCN */
DECL|member|svc
r_int
r_char
id|svc
suffix:semicolon
multiline_comment|/* 0=pvc, 1=svc */
DECL|member|timer
r_int
r_char
id|timer
suffix:semicolon
multiline_comment|/* flag for delayed transmit*/
DECL|member|tx_timer
r_struct
id|timer_list
id|tx_timer
suffix:semicolon
DECL|member|poll_cnt
r_int
id|poll_cnt
suffix:semicolon
DECL|member|force
r_int
r_char
id|force
suffix:semicolon
multiline_comment|/* Used to force sock release */
DECL|member|packet_sent
id|atomic_t
id|packet_sent
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
macro_line|#endif
eof
