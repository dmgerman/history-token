multiline_comment|/* &n;   HIDP implementation for Linux Bluetooth stack (BlueZ).&n;   Copyright (C) 2003-2004 Marcel Holtmann &lt;marcel@holtmann.org&gt;&n;&n;   This program is free software; you can redistribute it and/or modify&n;   it under the terms of the GNU General Public License version 2 as&n;   published by the Free Software Foundation;&n;&n;   THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND, EXPRESS&n;   OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,&n;   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT OF THIRD PARTY RIGHTS.&n;   IN NO EVENT SHALL THE COPYRIGHT HOLDER(S) AND AUTHOR(S) BE LIABLE FOR ANY&n;   CLAIM, OR ANY SPECIAL INDIRECT OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES &n;   WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN &n;   ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF &n;   OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.&n;&n;   ALL LIABILITY, INCLUDING LIABILITY FOR INFRINGEMENT OF ANY PATENTS, &n;   COPYRIGHTS, TRADEMARKS OR OTHER RIGHTS, RELATING TO USE OF THIS &n;   SOFTWARE IS DISCLAIMED.&n;*/
macro_line|#ifndef __HIDP_H
DECL|macro|__HIDP_H
mdefine_line|#define __HIDP_H
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;net/bluetooth/bluetooth.h&gt;
multiline_comment|/* HIDP header masks */
DECL|macro|HIDP_HEADER_TRANS_MASK
mdefine_line|#define HIDP_HEADER_TRANS_MASK&t;&t;&t;0xf0
DECL|macro|HIDP_HEADER_PARAM_MASK
mdefine_line|#define HIDP_HEADER_PARAM_MASK&t;&t;&t;0x0f
multiline_comment|/* HIDP transaction types */
DECL|macro|HIDP_TRANS_HANDSHAKE
mdefine_line|#define HIDP_TRANS_HANDSHAKE&t;&t;&t;0x00
DECL|macro|HIDP_TRANS_HID_CONTROL
mdefine_line|#define HIDP_TRANS_HID_CONTROL&t;&t;&t;0x10
DECL|macro|HIDP_TRANS_GET_REPORT
mdefine_line|#define HIDP_TRANS_GET_REPORT&t;&t;&t;0x40
DECL|macro|HIDP_TRANS_SET_REPORT
mdefine_line|#define HIDP_TRANS_SET_REPORT&t;&t;&t;0x50
DECL|macro|HIDP_TRANS_GET_PROTOCOL
mdefine_line|#define HIDP_TRANS_GET_PROTOCOL&t;&t;&t;0x60
DECL|macro|HIDP_TRANS_SET_PROTOCOL
mdefine_line|#define HIDP_TRANS_SET_PROTOCOL&t;&t;&t;0x70
DECL|macro|HIDP_TRANS_GET_IDLE
mdefine_line|#define HIDP_TRANS_GET_IDLE&t;&t;&t;0x80
DECL|macro|HIDP_TRANS_SET_IDLE
mdefine_line|#define HIDP_TRANS_SET_IDLE&t;&t;&t;0x90
DECL|macro|HIDP_TRANS_DATA
mdefine_line|#define HIDP_TRANS_DATA&t;&t;&t;&t;0xa0
DECL|macro|HIDP_TRANS_DATC
mdefine_line|#define HIDP_TRANS_DATC&t;&t;&t;&t;0xb0
multiline_comment|/* HIDP handshake results */
DECL|macro|HIDP_HSHK_SUCCESSFUL
mdefine_line|#define HIDP_HSHK_SUCCESSFUL&t;&t;&t;0x00
DECL|macro|HIDP_HSHK_NOT_READY
mdefine_line|#define HIDP_HSHK_NOT_READY&t;&t;&t;0x01
DECL|macro|HIDP_HSHK_ERR_INVALID_REPORT_ID
mdefine_line|#define HIDP_HSHK_ERR_INVALID_REPORT_ID&t;&t;0x02
DECL|macro|HIDP_HSHK_ERR_UNSUPPORTED_REQUEST
mdefine_line|#define HIDP_HSHK_ERR_UNSUPPORTED_REQUEST&t;0x03
DECL|macro|HIDP_HSHK_ERR_INVALID_PARAMETER
mdefine_line|#define HIDP_HSHK_ERR_INVALID_PARAMETER&t;&t;0x04
DECL|macro|HIDP_HSHK_ERR_UNKNOWN
mdefine_line|#define HIDP_HSHK_ERR_UNKNOWN&t;&t;&t;0x0e
DECL|macro|HIDP_HSHK_ERR_FATAL
mdefine_line|#define HIDP_HSHK_ERR_FATAL&t;&t;&t;0x0f
multiline_comment|/* HIDP control operation parameters */
DECL|macro|HIDP_CTRL_NOP
mdefine_line|#define HIDP_CTRL_NOP&t;&t;&t;&t;0x00
DECL|macro|HIDP_CTRL_HARD_RESET
mdefine_line|#define HIDP_CTRL_HARD_RESET&t;&t;&t;0x01
DECL|macro|HIDP_CTRL_SOFT_RESET
mdefine_line|#define HIDP_CTRL_SOFT_RESET&t;&t;&t;0x02
DECL|macro|HIDP_CTRL_SUSPEND
mdefine_line|#define HIDP_CTRL_SUSPEND&t;&t;&t;0x03
DECL|macro|HIDP_CTRL_EXIT_SUSPEND
mdefine_line|#define HIDP_CTRL_EXIT_SUSPEND&t;&t;&t;0x04
DECL|macro|HIDP_CTRL_VIRTUAL_CABLE_UNPLUG
mdefine_line|#define HIDP_CTRL_VIRTUAL_CABLE_UNPLUG&t;&t;0x05
multiline_comment|/* HIDP data transaction headers */
DECL|macro|HIDP_DATA_RTYPE_MASK
mdefine_line|#define HIDP_DATA_RTYPE_MASK&t;&t;&t;0x03
DECL|macro|HIDP_DATA_RSRVD_MASK
mdefine_line|#define HIDP_DATA_RSRVD_MASK&t;&t;&t;0x0c
DECL|macro|HIDP_DATA_RTYPE_OTHER
mdefine_line|#define HIDP_DATA_RTYPE_OTHER&t;&t;&t;0x00
DECL|macro|HIDP_DATA_RTYPE_INPUT
mdefine_line|#define HIDP_DATA_RTYPE_INPUT&t;&t;&t;0x01
DECL|macro|HIDP_DATA_RTYPE_OUPUT
mdefine_line|#define HIDP_DATA_RTYPE_OUPUT&t;&t;&t;0x02
DECL|macro|HIDP_DATA_RTYPE_FEATURE
mdefine_line|#define HIDP_DATA_RTYPE_FEATURE&t;&t;&t;0x03
multiline_comment|/* HIDP protocol header parameters */
DECL|macro|HIDP_PROTO_BOOT
mdefine_line|#define HIDP_PROTO_BOOT&t;&t;&t;&t;0x00
DECL|macro|HIDP_PROTO_REPORT
mdefine_line|#define HIDP_PROTO_REPORT&t;&t;&t;0x01
multiline_comment|/* HIDP ioctl defines */
DECL|macro|HIDPCONNADD
mdefine_line|#define HIDPCONNADD&t;_IOW(&squot;H&squot;, 200, int)
DECL|macro|HIDPCONNDEL
mdefine_line|#define HIDPCONNDEL&t;_IOW(&squot;H&squot;, 201, int)
DECL|macro|HIDPGETCONNLIST
mdefine_line|#define HIDPGETCONNLIST&t;_IOR(&squot;H&squot;, 210, int)
DECL|macro|HIDPGETCONNINFO
mdefine_line|#define HIDPGETCONNINFO&t;_IOR(&squot;H&squot;, 211, int)
DECL|macro|HIDP_VIRTUAL_CABLE_UNPLUG
mdefine_line|#define HIDP_VIRTUAL_CABLE_UNPLUG&t;0
DECL|macro|HIDP_BOOT_PROTOCOL_MODE
mdefine_line|#define HIDP_BOOT_PROTOCOL_MODE&t;&t;1
DECL|macro|HIDP_BLUETOOTH_VENDOR_ID
mdefine_line|#define HIDP_BLUETOOTH_VENDOR_ID&t;9
DECL|struct|hidp_connadd_req
r_struct
id|hidp_connadd_req
(brace
DECL|member|ctrl_sock
r_int
id|ctrl_sock
suffix:semicolon
singleline_comment|// Connected control socket
DECL|member|intr_sock
r_int
id|intr_sock
suffix:semicolon
singleline_comment|// Connteted interrupt socket
DECL|member|parser
id|__u16
id|parser
suffix:semicolon
DECL|member|rd_size
id|__u16
id|rd_size
suffix:semicolon
DECL|member|rd_data
id|__u8
op_star
id|rd_data
suffix:semicolon
DECL|member|country
id|__u8
id|country
suffix:semicolon
DECL|member|subclass
id|__u8
id|subclass
suffix:semicolon
DECL|member|vendor
id|__u16
id|vendor
suffix:semicolon
DECL|member|product
id|__u16
id|product
suffix:semicolon
DECL|member|version
id|__u16
id|version
suffix:semicolon
DECL|member|flags
id|__u32
id|flags
suffix:semicolon
DECL|member|idle_to
id|__u32
id|idle_to
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
l_int|128
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|hidp_conndel_req
r_struct
id|hidp_conndel_req
(brace
DECL|member|bdaddr
id|bdaddr_t
id|bdaddr
suffix:semicolon
DECL|member|flags
id|__u32
id|flags
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|hidp_conninfo
r_struct
id|hidp_conninfo
(brace
DECL|member|bdaddr
id|bdaddr_t
id|bdaddr
suffix:semicolon
DECL|member|flags
id|__u32
id|flags
suffix:semicolon
DECL|member|state
id|__u16
id|state
suffix:semicolon
DECL|member|vendor
id|__u16
id|vendor
suffix:semicolon
DECL|member|product
id|__u16
id|product
suffix:semicolon
DECL|member|version
id|__u16
id|version
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
l_int|128
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|hidp_connlist_req
r_struct
id|hidp_connlist_req
(brace
DECL|member|cnum
id|__u32
id|cnum
suffix:semicolon
DECL|member|ci
r_struct
id|hidp_conninfo
id|__user
op_star
id|ci
suffix:semicolon
)brace
suffix:semicolon
r_int
id|hidp_add_connection
c_func
(paren
r_struct
id|hidp_connadd_req
op_star
id|req
comma
r_struct
id|socket
op_star
id|ctrl_sock
comma
r_struct
id|socket
op_star
id|intr_sock
)paren
suffix:semicolon
r_int
id|hidp_del_connection
c_func
(paren
r_struct
id|hidp_conndel_req
op_star
id|req
)paren
suffix:semicolon
r_int
id|hidp_get_connlist
c_func
(paren
r_struct
id|hidp_connlist_req
op_star
id|req
)paren
suffix:semicolon
r_int
id|hidp_get_conninfo
c_func
(paren
r_struct
id|hidp_conninfo
op_star
id|ci
)paren
suffix:semicolon
multiline_comment|/* HIDP session defines */
DECL|struct|hidp_session
r_struct
id|hidp_session
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|ctrl_sock
r_struct
id|socket
op_star
id|ctrl_sock
suffix:semicolon
DECL|member|intr_sock
r_struct
id|socket
op_star
id|intr_sock
suffix:semicolon
DECL|member|bdaddr
id|bdaddr_t
id|bdaddr
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
DECL|member|idle_to
r_int
r_int
id|idle_to
suffix:semicolon
DECL|member|ctrl_mtu
id|uint
id|ctrl_mtu
suffix:semicolon
DECL|member|intr_mtu
id|uint
id|intr_mtu
suffix:semicolon
DECL|member|terminate
id|atomic_t
id|terminate
suffix:semicolon
DECL|member|keys
r_int
r_char
id|keys
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|leds
r_int
r_char
id|leds
suffix:semicolon
DECL|member|input
r_struct
id|input_dev
op_star
id|input
suffix:semicolon
DECL|member|timer
r_struct
id|timer_list
id|timer
suffix:semicolon
DECL|member|ctrl_transmit
r_struct
id|sk_buff_head
id|ctrl_transmit
suffix:semicolon
DECL|member|intr_transmit
r_struct
id|sk_buff_head
id|intr_transmit
suffix:semicolon
)brace
suffix:semicolon
DECL|function|hidp_schedule
r_static
r_inline
r_void
id|hidp_schedule
c_func
(paren
r_struct
id|hidp_session
op_star
id|session
)paren
(brace
r_struct
id|sock
op_star
id|ctrl_sk
op_assign
id|session-&gt;ctrl_sock-&gt;sk
suffix:semicolon
r_struct
id|sock
op_star
id|intr_sk
op_assign
id|session-&gt;intr_sock-&gt;sk
suffix:semicolon
id|wake_up_interruptible
c_func
(paren
id|ctrl_sk-&gt;sk_sleep
)paren
suffix:semicolon
id|wake_up_interruptible
c_func
(paren
id|intr_sk-&gt;sk_sleep
)paren
suffix:semicolon
)brace
multiline_comment|/* HIDP init defines */
r_extern
r_int
id|__init
id|hidp_init_sockets
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__exit
id|hidp_cleanup_sockets
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* __HIDP_H */
eof
