multiline_comment|/*&n; *&t;Linux ethernet bridge&n; *&n; *&t;Authors:&n; *&t;Lennert Buytenhek&t;&t;&lt;buytenh@gnu.org&gt;&n; *&n; *&t;$Id: if_bridge.h,v 1.1 2000/02/18 16:47:01 davem Exp $&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *&t;modify it under the terms of the GNU General Public License&n; *&t;as published by the Free Software Foundation; either version&n; *&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _LINUX_IF_BRIDGE_H
DECL|macro|_LINUX_IF_BRIDGE_H
mdefine_line|#define _LINUX_IF_BRIDGE_H
macro_line|#include &lt;linux/types.h&gt;
DECL|macro|BRCTL_VERSION
mdefine_line|#define BRCTL_VERSION 1
DECL|macro|BRCTL_GET_VERSION
mdefine_line|#define BRCTL_GET_VERSION 0
DECL|macro|BRCTL_GET_BRIDGES
mdefine_line|#define BRCTL_GET_BRIDGES 1
DECL|macro|BRCTL_ADD_BRIDGE
mdefine_line|#define BRCTL_ADD_BRIDGE 2
DECL|macro|BRCTL_DEL_BRIDGE
mdefine_line|#define BRCTL_DEL_BRIDGE 3
DECL|macro|BRCTL_ADD_IF
mdefine_line|#define BRCTL_ADD_IF 4
DECL|macro|BRCTL_DEL_IF
mdefine_line|#define BRCTL_DEL_IF 5
DECL|macro|BRCTL_GET_BRIDGE_INFO
mdefine_line|#define BRCTL_GET_BRIDGE_INFO 6
DECL|macro|BRCTL_GET_PORT_LIST
mdefine_line|#define BRCTL_GET_PORT_LIST 7
DECL|macro|BRCTL_SET_BRIDGE_FORWARD_DELAY
mdefine_line|#define BRCTL_SET_BRIDGE_FORWARD_DELAY 8
DECL|macro|BRCTL_SET_BRIDGE_HELLO_TIME
mdefine_line|#define BRCTL_SET_BRIDGE_HELLO_TIME 9
DECL|macro|BRCTL_SET_BRIDGE_MAX_AGE
mdefine_line|#define BRCTL_SET_BRIDGE_MAX_AGE 10
DECL|macro|BRCTL_SET_AGEING_TIME
mdefine_line|#define BRCTL_SET_AGEING_TIME 11
DECL|macro|BRCTL_SET_GC_INTERVAL
mdefine_line|#define BRCTL_SET_GC_INTERVAL 12
DECL|macro|BRCTL_GET_PORT_INFO
mdefine_line|#define BRCTL_GET_PORT_INFO 13
DECL|macro|BRCTL_SET_BRIDGE_STP_STATE
mdefine_line|#define BRCTL_SET_BRIDGE_STP_STATE 14
DECL|macro|BRCTL_SET_BRIDGE_PRIORITY
mdefine_line|#define BRCTL_SET_BRIDGE_PRIORITY 15
DECL|macro|BRCTL_SET_PORT_PRIORITY
mdefine_line|#define BRCTL_SET_PORT_PRIORITY 16
DECL|macro|BRCTL_SET_PATH_COST
mdefine_line|#define BRCTL_SET_PATH_COST 17
DECL|macro|BRCTL_GET_FDB_ENTRIES
mdefine_line|#define BRCTL_GET_FDB_ENTRIES 18
DECL|macro|BR_STATE_DISABLED
mdefine_line|#define BR_STATE_DISABLED 0
DECL|macro|BR_STATE_LISTENING
mdefine_line|#define BR_STATE_LISTENING 1
DECL|macro|BR_STATE_LEARNING
mdefine_line|#define BR_STATE_LEARNING 2
DECL|macro|BR_STATE_FORWARDING
mdefine_line|#define BR_STATE_FORWARDING 3
DECL|macro|BR_STATE_BLOCKING
mdefine_line|#define BR_STATE_BLOCKING 4
DECL|struct|__bridge_info
r_struct
id|__bridge_info
(brace
DECL|member|designated_root
id|__u64
id|designated_root
suffix:semicolon
DECL|member|bridge_id
id|__u64
id|bridge_id
suffix:semicolon
DECL|member|root_path_cost
id|__u32
id|root_path_cost
suffix:semicolon
DECL|member|max_age
id|__u32
id|max_age
suffix:semicolon
DECL|member|hello_time
id|__u32
id|hello_time
suffix:semicolon
DECL|member|forward_delay
id|__u32
id|forward_delay
suffix:semicolon
DECL|member|bridge_max_age
id|__u32
id|bridge_max_age
suffix:semicolon
DECL|member|bridge_hello_time
id|__u32
id|bridge_hello_time
suffix:semicolon
DECL|member|bridge_forward_delay
id|__u32
id|bridge_forward_delay
suffix:semicolon
DECL|member|topology_change
id|__u8
id|topology_change
suffix:semicolon
DECL|member|topology_change_detected
id|__u8
id|topology_change_detected
suffix:semicolon
DECL|member|root_port
id|__u8
id|root_port
suffix:semicolon
DECL|member|stp_enabled
id|__u8
id|stp_enabled
suffix:semicolon
DECL|member|ageing_time
id|__u32
id|ageing_time
suffix:semicolon
DECL|member|gc_interval
id|__u32
id|gc_interval
suffix:semicolon
DECL|member|hello_timer_value
id|__u32
id|hello_timer_value
suffix:semicolon
DECL|member|tcn_timer_value
id|__u32
id|tcn_timer_value
suffix:semicolon
DECL|member|topology_change_timer_value
id|__u32
id|topology_change_timer_value
suffix:semicolon
DECL|member|gc_timer_value
id|__u32
id|gc_timer_value
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|__port_info
r_struct
id|__port_info
(brace
DECL|member|designated_root
id|__u64
id|designated_root
suffix:semicolon
DECL|member|designated_bridge
id|__u64
id|designated_bridge
suffix:semicolon
DECL|member|port_id
id|__u16
id|port_id
suffix:semicolon
DECL|member|designated_port
id|__u16
id|designated_port
suffix:semicolon
DECL|member|path_cost
id|__u32
id|path_cost
suffix:semicolon
DECL|member|designated_cost
id|__u32
id|designated_cost
suffix:semicolon
DECL|member|state
id|__u8
id|state
suffix:semicolon
DECL|member|top_change_ack
id|__u8
id|top_change_ack
suffix:semicolon
DECL|member|config_pending
id|__u8
id|config_pending
suffix:semicolon
DECL|member|unused0
id|__u8
id|unused0
suffix:semicolon
DECL|member|message_age_timer_value
id|__u32
id|message_age_timer_value
suffix:semicolon
DECL|member|forward_delay_timer_value
id|__u32
id|forward_delay_timer_value
suffix:semicolon
DECL|member|hold_timer_value
id|__u32
id|hold_timer_value
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|__fdb_entry
r_struct
id|__fdb_entry
(brace
DECL|member|mac_addr
id|__u8
id|mac_addr
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|port_no
id|__u8
id|port_no
suffix:semicolon
DECL|member|is_local
id|__u8
id|is_local
suffix:semicolon
DECL|member|ageing_timer_value
id|__u32
id|ageing_timer_value
suffix:semicolon
DECL|member|unused
id|__u32
id|unused
suffix:semicolon
)brace
suffix:semicolon
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/netdevice.h&gt;
r_struct
id|net_bridge
suffix:semicolon
r_struct
id|net_bridge_port
suffix:semicolon
r_extern
r_int
(paren
op_star
id|br_ioctl_hook
)paren
(paren
r_int
r_int
id|arg
)paren
suffix:semicolon
r_extern
r_void
(paren
op_star
id|br_handle_frame_hook
)paren
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif
eof
