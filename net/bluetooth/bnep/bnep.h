multiline_comment|/*&n;  BNEP protocol definition for Linux Bluetooth stack (BlueZ).&n;  Copyright (C) 2002 Maxim Krasnyansky &lt;maxk@qualcomm.com&gt;&n;&t;&n;  This program is free software; you can redistribute it and/or modify&n;  it under the terms of the GNU General Public License, version 2, as&n;  published by the Free Software Foundation.&n;&n;  This program is distributed in the hope that it will be useful,&n;  but WITHOUT ANY WARRANTY; without even the implied warranty of&n;  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;  GNU General Public License for more details.&n;&n;  You should have received a copy of the GNU General Public License&n;  along with this program; if not, write to the Free Software&n;  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n;*/
multiline_comment|/*&n; * $Id: bnep.h,v 1.5 2002/08/04 21:23:58 maxk Exp $&n; */
macro_line|#ifndef _BNEP_H
DECL|macro|_BNEP_H
mdefine_line|#define _BNEP_H
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/crc32.h&gt;
macro_line|#include &lt;net/bluetooth/bluetooth.h&gt;
singleline_comment|// Limits
DECL|macro|BNEP_MAX_PROTO_FILTERS
mdefine_line|#define BNEP_MAX_PROTO_FILTERS     5
DECL|macro|BNEP_MAX_MULTICAST_FILTERS
mdefine_line|#define BNEP_MAX_MULTICAST_FILTERS 20
singleline_comment|// UUIDs
DECL|macro|BNEP_BASE_UUID
mdefine_line|#define BNEP_BASE_UUID 0x0000000000001000800000805F9B34FB
DECL|macro|BNEP_UUID16
mdefine_line|#define BNEP_UUID16    0x02
DECL|macro|BNEP_UUID32
mdefine_line|#define BNEP_UUID32    0x04
DECL|macro|BNEP_UUID128
mdefine_line|#define BNEP_UUID128   0x16
DECL|macro|BNEP_SVC_PANU
mdefine_line|#define BNEP_SVC_PANU  0x1115
DECL|macro|BNEP_SVC_NAP
mdefine_line|#define BNEP_SVC_NAP   0x1116
DECL|macro|BNEP_SVC_GN
mdefine_line|#define BNEP_SVC_GN    0x1117
singleline_comment|// Packet types
DECL|macro|BNEP_GENERAL
mdefine_line|#define BNEP_GENERAL               0x00
DECL|macro|BNEP_CONTROL
mdefine_line|#define BNEP_CONTROL               0x01
DECL|macro|BNEP_COMPRESSED
mdefine_line|#define BNEP_COMPRESSED            0x02
DECL|macro|BNEP_COMPRESSED_SRC_ONLY
mdefine_line|#define BNEP_COMPRESSED_SRC_ONLY   0x03
DECL|macro|BNEP_COMPRESSED_DST_ONLY
mdefine_line|#define BNEP_COMPRESSED_DST_ONLY   0x04
singleline_comment|// Control types
DECL|macro|BNEP_CMD_NOT_UNDERSTOOD
mdefine_line|#define BNEP_CMD_NOT_UNDERSTOOD    0x00
DECL|macro|BNEP_SETUP_CONN_REQ
mdefine_line|#define BNEP_SETUP_CONN_REQ        0x01
DECL|macro|BNEP_SETUP_CONN_RSP
mdefine_line|#define BNEP_SETUP_CONN_RSP        0x02
DECL|macro|BNEP_FILTER_NET_TYPE_SET
mdefine_line|#define BNEP_FILTER_NET_TYPE_SET   0x03
DECL|macro|BNEP_FILTER_NET_TYPE_RSP
mdefine_line|#define BNEP_FILTER_NET_TYPE_RSP   0x04
DECL|macro|BNEP_FILTER_MULTI_ADDR_SET
mdefine_line|#define BNEP_FILTER_MULTI_ADDR_SET 0x05
DECL|macro|BNEP_FILTER_MULTI_ADDR_RSP
mdefine_line|#define BNEP_FILTER_MULTI_ADDR_RSP 0x06
singleline_comment|// Extension types
DECL|macro|BNEP_EXT_CONTROL
mdefine_line|#define BNEP_EXT_CONTROL           0x00
singleline_comment|// Response messages 
DECL|macro|BNEP_SUCCESS
mdefine_line|#define BNEP_SUCCESS               0x00
DECL|macro|BNEP_CONN_INVALID_DST
mdefine_line|#define BNEP_CONN_INVALID_DST      0x01
DECL|macro|BNEP_CONN_INVALID_SRC
mdefine_line|#define BNEP_CONN_INVALID_SRC      0x02
DECL|macro|BNEP_CONN_INVALID_SVC
mdefine_line|#define BNEP_CONN_INVALID_SVC      0x03
DECL|macro|BNEP_CONN_NOT_ALLOWED
mdefine_line|#define BNEP_CONN_NOT_ALLOWED      0x04
DECL|macro|BNEP_FILTER_UNSUPPORTED_REQ
mdefine_line|#define BNEP_FILTER_UNSUPPORTED_REQ    0x01
DECL|macro|BNEP_FILTER_INVALID_RANGE
mdefine_line|#define BNEP_FILTER_INVALID_RANGE      0x02
DECL|macro|BNEP_FILTER_INVALID_MCADDR
mdefine_line|#define BNEP_FILTER_INVALID_MCADDR     0x02
DECL|macro|BNEP_FILTER_LIMIT_REACHED
mdefine_line|#define BNEP_FILTER_LIMIT_REACHED      0x03
DECL|macro|BNEP_FILTER_DENIED_SECURITY
mdefine_line|#define BNEP_FILTER_DENIED_SECURITY    0x04
singleline_comment|// L2CAP settings
DECL|macro|BNEP_MTU
mdefine_line|#define BNEP_MTU         1691
DECL|macro|BNEP_PSM
mdefine_line|#define BNEP_PSM&t; 0x0f
DECL|macro|BNEP_FLUSH_TO
mdefine_line|#define BNEP_FLUSH_TO    0xffff
DECL|macro|BNEP_CONNECT_TO
mdefine_line|#define BNEP_CONNECT_TO  15
DECL|macro|BNEP_FILTER_TO
mdefine_line|#define BNEP_FILTER_TO   15
singleline_comment|// Headers 
DECL|macro|BNEP_TYPE_MASK
mdefine_line|#define BNEP_TYPE_MASK&t; 0x7f
DECL|macro|BNEP_EXT_HEADER
mdefine_line|#define BNEP_EXT_HEADER&t; 0x80
DECL|struct|bnep_setup_conn_req
r_struct
id|bnep_setup_conn_req
(brace
DECL|member|type
id|__u8
id|type
suffix:semicolon
DECL|member|ctrl
id|__u8
id|ctrl
suffix:semicolon
DECL|member|uuid_size
id|__u8
id|uuid_size
suffix:semicolon
DECL|member|service
id|__u8
id|service
(braket
l_int|0
)braket
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|struct|bnep_set_filter_req
r_struct
id|bnep_set_filter_req
(brace
DECL|member|type
id|__u8
id|type
suffix:semicolon
DECL|member|ctrl
id|__u8
id|ctrl
suffix:semicolon
DECL|member|len
id|__u16
id|len
suffix:semicolon
DECL|member|list
id|__u8
id|list
(braket
l_int|0
)braket
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|struct|bnep_control_rsp
r_struct
id|bnep_control_rsp
(brace
DECL|member|type
id|__u8
id|type
suffix:semicolon
DECL|member|ctrl
id|__u8
id|ctrl
suffix:semicolon
DECL|member|resp
id|__u16
id|resp
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|struct|bnep_ext_hdr
r_struct
id|bnep_ext_hdr
(brace
DECL|member|type
id|__u8
id|type
suffix:semicolon
DECL|member|len
id|__u8
id|len
suffix:semicolon
DECL|member|data
id|__u8
id|data
(braket
l_int|0
)braket
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* BNEP ioctl defines */
DECL|macro|BNEPCONNADD
mdefine_line|#define BNEPCONNADD&t;_IOW(&squot;B&squot;, 200, int)
DECL|macro|BNEPCONNDEL
mdefine_line|#define BNEPCONNDEL&t;_IOW(&squot;B&squot;, 201, int)
DECL|macro|BNEPGETCONNLIST
mdefine_line|#define BNEPGETCONNLIST&t;_IOR(&squot;B&squot;, 210, int)
DECL|macro|BNEPGETCONNINFO
mdefine_line|#define BNEPGETCONNINFO&t;_IOR(&squot;B&squot;, 211, int)
singleline_comment|// Ioctl interface
DECL|macro|BNEPCONADD
mdefine_line|#define BNEPCONADD      1
DECL|macro|BNEPCONDEL
mdefine_line|#define BNEPCONDEL      2
DECL|macro|BNEPGETCONLIST
mdefine_line|#define BNEPGETCONLIST  3
DECL|macro|BNEPGETCONINFO
mdefine_line|#define BNEPGETCONINFO  4
DECL|struct|bnep_connadd_req
r_struct
id|bnep_connadd_req
(brace
DECL|member|sock
r_int
id|sock
suffix:semicolon
singleline_comment|// Connected socket
DECL|member|flags
id|__u32
id|flags
suffix:semicolon
DECL|member|role
id|__u16
id|role
suffix:semicolon
DECL|member|device
r_char
id|device
(braket
l_int|16
)braket
suffix:semicolon
singleline_comment|// Name of the Ethernet device
)brace
suffix:semicolon
DECL|struct|bnep_conndel_req
r_struct
id|bnep_conndel_req
(brace
DECL|member|flags
id|__u32
id|flags
suffix:semicolon
DECL|member|dst
id|__u8
id|dst
(braket
id|ETH_ALEN
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|bnep_conninfo
r_struct
id|bnep_conninfo
(brace
DECL|member|flags
id|__u32
id|flags
suffix:semicolon
DECL|member|role
id|__u16
id|role
suffix:semicolon
DECL|member|state
id|__u16
id|state
suffix:semicolon
DECL|member|dst
id|__u8
id|dst
(braket
id|ETH_ALEN
)braket
suffix:semicolon
DECL|member|device
r_char
id|device
(braket
l_int|16
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|bnep_connlist_req
r_struct
id|bnep_connlist_req
(brace
DECL|member|cnum
id|__u32
id|cnum
suffix:semicolon
DECL|member|ci
r_struct
id|bnep_conninfo
op_star
id|ci
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|bnep_proto_filter
r_struct
id|bnep_proto_filter
(brace
DECL|member|start
id|__u16
id|start
suffix:semicolon
DECL|member|end
id|__u16
id|end
suffix:semicolon
)brace
suffix:semicolon
r_int
id|bnep_add_connection
c_func
(paren
r_struct
id|bnep_connadd_req
op_star
id|req
comma
r_struct
id|socket
op_star
id|sock
)paren
suffix:semicolon
r_int
id|bnep_del_connection
c_func
(paren
r_struct
id|bnep_conndel_req
op_star
id|req
)paren
suffix:semicolon
r_int
id|bnep_get_connlist
c_func
(paren
r_struct
id|bnep_connlist_req
op_star
id|req
)paren
suffix:semicolon
r_int
id|bnep_get_conninfo
c_func
(paren
r_struct
id|bnep_conninfo
op_star
id|ci
)paren
suffix:semicolon
singleline_comment|// BNEP sessions
DECL|struct|bnep_session
r_struct
id|bnep_session
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|role
r_int
r_int
id|role
suffix:semicolon
DECL|member|state
r_int
r_int
id|state
suffix:semicolon
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
DECL|member|killed
id|atomic_t
id|killed
suffix:semicolon
DECL|member|eh
r_struct
id|ethhdr
id|eh
suffix:semicolon
DECL|member|msg
r_struct
id|msghdr
id|msg
suffix:semicolon
DECL|member|proto_filter
r_struct
id|bnep_proto_filter
id|proto_filter
(braket
id|BNEP_MAX_PROTO_FILTERS
)braket
suffix:semicolon
DECL|member|mc_filter
id|u64
id|mc_filter
suffix:semicolon
DECL|member|sock
r_struct
id|socket
op_star
id|sock
suffix:semicolon
DECL|member|dev
r_struct
id|net_device
id|dev
suffix:semicolon
DECL|member|stats
r_struct
id|net_device_stats
id|stats
suffix:semicolon
)brace
suffix:semicolon
r_int
id|bnep_net_init
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_int
id|bnep_sock_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|bnep_sock_cleanup
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|function|bnep_mc_hash
r_static
r_inline
r_int
id|bnep_mc_hash
c_func
(paren
id|__u8
op_star
id|addr
)paren
(brace
r_return
(paren
id|crc32_be
c_func
(paren
op_complement
l_int|0
comma
id|addr
comma
id|ETH_ALEN
)paren
op_rshift
l_int|26
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
