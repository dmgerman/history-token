multiline_comment|/*****************************************************************************&n;* if_wanipe_common.h   Sangoma Driver/Socket common area definitions.&n;*&n;* Author:       Nenad Corbic &lt;ncorbic@sangoma.com&gt;&n;*&n;* Copyright:    (c) 2000 Sangoma Technologies Inc.&n;*&n;*               This program is free software; you can redistribute it and/or&n;*               modify it under the terms of the GNU General Public License&n;*               as published by the Free Software Foundation; either version&n;*               2 of the License, or (at your option) any later version.&n;* ============================================================================&n;* Jan 13, 2000  Nenad Corbic      Initial version&n;*****************************************************************************/
macro_line|#ifndef _WANPIPE_SOCK_DRIVER_COMMON_H
DECL|macro|_WANPIPE_SOCK_DRIVER_COMMON_H
mdefine_line|#define _WANPIPE_SOCK_DRIVER_COMMON_H
macro_line|#include &lt;linux/version.h&gt;
macro_line|#if LINUX_VERSION_CODE &gt;= KERNEL_VERSION(2,3,0)
DECL|macro|netdevice_t
mdefine_line|#define netdevice_t struct net_device
macro_line|#else
DECL|macro|netdevice_t
mdefine_line|#define netdevice_t struct device
macro_line|#endif
r_typedef
r_struct
(brace
DECL|member|slave
id|netdevice_t
op_star
id|slave
suffix:semicolon
DECL|member|packet_sent
id|atomic_t
id|packet_sent
suffix:semicolon
DECL|member|receive_block
id|atomic_t
id|receive_block
suffix:semicolon
DECL|member|command
id|atomic_t
id|command
suffix:semicolon
DECL|member|disconnect
id|atomic_t
id|disconnect
suffix:semicolon
DECL|member|driver_busy
id|atomic_t
id|driver_busy
suffix:semicolon
DECL|member|common_critical
r_int
r_char
id|common_critical
suffix:semicolon
DECL|member|tx_timer
r_struct
id|timer_list
op_star
id|tx_timer
suffix:semicolon
DECL|member|sk
r_struct
id|sock
op_star
id|sk
suffix:semicolon
multiline_comment|/* Wanpipe Sock bind&squot;s here */
DECL|member|func
r_int
(paren
op_star
id|func
)paren
(paren
r_struct
id|sk_buff
op_star
comma
id|netdevice_t
op_star
comma
r_struct
id|sock
op_star
)paren
suffix:semicolon
DECL|member|wanpipe_task
r_struct
id|tq_struct
id|wanpipe_task
suffix:semicolon
multiline_comment|/* Immediate BH handler task */
DECL|member|rw_bind
r_int
r_char
id|rw_bind
suffix:semicolon
multiline_comment|/* Sock bind state */
DECL|member|usedby
r_int
r_char
id|usedby
suffix:semicolon
DECL|member|state
r_int
r_char
id|state
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
r_void
op_star
id|mbox
suffix:semicolon
DECL|typedef|wanpipe_common_t
)brace
id|wanpipe_common_t
suffix:semicolon
r_enum
(brace
DECL|enumerator|WANSOCK_UNCONFIGURED
id|WANSOCK_UNCONFIGURED
comma
multiline_comment|/* link/channel is not configured */
DECL|enumerator|WANSOCK_DISCONNECTED
id|WANSOCK_DISCONNECTED
comma
multiline_comment|/* link/channel is disconnected */
DECL|enumerator|WANSOCK_CONNECTING
id|WANSOCK_CONNECTING
comma
multiline_comment|/* connection is in progress */
DECL|enumerator|WANSOCK_CONNECTED
id|WANSOCK_CONNECTED
comma
multiline_comment|/* link/channel is operational */
DECL|enumerator|WANSOCK_LIMIT
id|WANSOCK_LIMIT
comma
multiline_comment|/* for verification only */
DECL|enumerator|WANSOCK_DUALPORT
id|WANSOCK_DUALPORT
comma
multiline_comment|/* for Dual Port cards */
DECL|enumerator|WANSOCK_DISCONNECTING
id|WANSOCK_DISCONNECTING
comma
DECL|enumerator|WANSOCK_BINDED
id|WANSOCK_BINDED
comma
DECL|enumerator|WANSOCK_BIND_LISTEN
id|WANSOCK_BIND_LISTEN
comma
DECL|enumerator|WANSOCK_LISTEN
id|WANSOCK_LISTEN
)brace
suffix:semicolon
macro_line|#endif
eof
