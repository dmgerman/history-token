multiline_comment|/*********************************************************************&n; *                &n; * Filename:      irlan_common.h&n; * Version:       0.8&n; * Description:   IrDA LAN access layer&n; * Status:        Experimental.&n; * Author:        Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * Created at:    Sun Aug 31 20:14:37 1997&n; * Modified at:   Sun Oct 31 19:41:24 1999&n; * Modified by:   Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * &n; *     Copyright (c) 1998-1999 Dag Brattli &lt;dagb@cs.uit.no&gt;, &n; *     All Rights Reserved.&n; *     &n; *     This program is free software; you can redistribute it and/or &n; *     modify it under the terms of the GNU General Public License as &n; *     published by the Free Software Foundation; either version 2 of &n; *     the License, or (at your option) any later version.&n; *&n; *     Neither Dag Brattli nor University of Troms&#xfffd; admit liability nor&n; *     provide warranty for any of this software. This material is &n; *     provided &quot;AS-IS&quot; and at no charge.&n; *&n; ********************************************************************/
macro_line|#ifndef IRLAN_H
DECL|macro|IRLAN_H
mdefine_line|#define IRLAN_H
macro_line|#include &lt;asm/param.h&gt;  /* for HZ */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;net/irda/irqueue.h&gt;
macro_line|#include &lt;net/irda/irttp.h&gt;
DECL|macro|IRLAN_MTU
mdefine_line|#define IRLAN_MTU        1518
DECL|macro|IRLAN_TIMEOUT
mdefine_line|#define IRLAN_TIMEOUT    10*HZ /* 10 seconds */
multiline_comment|/* Command packet types */
DECL|macro|CMD_GET_PROVIDER_INFO
mdefine_line|#define CMD_GET_PROVIDER_INFO   0
DECL|macro|CMD_GET_MEDIA_CHAR
mdefine_line|#define CMD_GET_MEDIA_CHAR      1
DECL|macro|CMD_OPEN_DATA_CHANNEL
mdefine_line|#define CMD_OPEN_DATA_CHANNEL   2
DECL|macro|CMD_CLOSE_DATA_CHAN
mdefine_line|#define CMD_CLOSE_DATA_CHAN     3
DECL|macro|CMD_RECONNECT_DATA_CHAN
mdefine_line|#define CMD_RECONNECT_DATA_CHAN 4
DECL|macro|CMD_FILTER_OPERATION
mdefine_line|#define CMD_FILTER_OPERATION    5
multiline_comment|/* Some responses */
DECL|macro|RSP_SUCCESS
mdefine_line|#define RSP_SUCCESS                 0
DECL|macro|RSP_INSUFFICIENT_RESOURCES
mdefine_line|#define RSP_INSUFFICIENT_RESOURCES  1
DECL|macro|RSP_INVALID_COMMAND_FORMAT
mdefine_line|#define RSP_INVALID_COMMAND_FORMAT  2
DECL|macro|RSP_COMMAND_NOT_SUPPORTED
mdefine_line|#define RSP_COMMAND_NOT_SUPPORTED   3
DECL|macro|RSP_PARAM_NOT_SUPPORTED
mdefine_line|#define RSP_PARAM_NOT_SUPPORTED     4
DECL|macro|RSP_VALUE_NOT_SUPPORTED
mdefine_line|#define RSP_VALUE_NOT_SUPPORTED     5
DECL|macro|RSP_NOT_OPEN
mdefine_line|#define RSP_NOT_OPEN                6
DECL|macro|RSP_AUTHENTICATION_REQUIRED
mdefine_line|#define RSP_AUTHENTICATION_REQUIRED 7
DECL|macro|RSP_INVALID_PASSWORD
mdefine_line|#define RSP_INVALID_PASSWORD        8
DECL|macro|RSP_PROTOCOL_ERROR
mdefine_line|#define RSP_PROTOCOL_ERROR          9
DECL|macro|RSP_ASYNCHRONOUS_ERROR
mdefine_line|#define RSP_ASYNCHRONOUS_ERROR    255
multiline_comment|/* Media types */
DECL|macro|MEDIA_802_3
mdefine_line|#define MEDIA_802_3 1
DECL|macro|MEDIA_802_5
mdefine_line|#define MEDIA_802_5 2
multiline_comment|/* Filter parameters */
DECL|macro|DATA_CHAN
mdefine_line|#define DATA_CHAN   1
DECL|macro|FILTER_TYPE
mdefine_line|#define FILTER_TYPE 2
DECL|macro|FILTER_MODE
mdefine_line|#define FILTER_MODE 3
multiline_comment|/* Filter types */
DECL|macro|IRLAN_DIRECTED
mdefine_line|#define IRLAN_DIRECTED   0x01
DECL|macro|IRLAN_FUNCTIONAL
mdefine_line|#define IRLAN_FUNCTIONAL 0x02
DECL|macro|IRLAN_GROUP
mdefine_line|#define IRLAN_GROUP      0x04
DECL|macro|IRLAN_MAC_FRAME
mdefine_line|#define IRLAN_MAC_FRAME  0x08
DECL|macro|IRLAN_MULTICAST
mdefine_line|#define IRLAN_MULTICAST  0x10
DECL|macro|IRLAN_BROADCAST
mdefine_line|#define IRLAN_BROADCAST  0x20
DECL|macro|IRLAN_IPX_SOCKET
mdefine_line|#define IRLAN_IPX_SOCKET 0x40
multiline_comment|/* Filter modes */
DECL|macro|ALL
mdefine_line|#define ALL     1
DECL|macro|FILTER
mdefine_line|#define FILTER  2
DECL|macro|NONE
mdefine_line|#define NONE    3
multiline_comment|/* Filter operations */
DECL|macro|GET
mdefine_line|#define GET     1
DECL|macro|CLEAR
mdefine_line|#define CLEAR   2
DECL|macro|ADD
mdefine_line|#define ADD     3
DECL|macro|REMOVE
mdefine_line|#define REMOVE  4
DECL|macro|DYNAMIC
mdefine_line|#define DYNAMIC 5
multiline_comment|/* Access types */
DECL|macro|ACCESS_DIRECT
mdefine_line|#define ACCESS_DIRECT  1
DECL|macro|ACCESS_PEER
mdefine_line|#define ACCESS_PEER    2
DECL|macro|ACCESS_HOSTED
mdefine_line|#define ACCESS_HOSTED  3
DECL|macro|IRLAN_BYTE
mdefine_line|#define IRLAN_BYTE   0
DECL|macro|IRLAN_SHORT
mdefine_line|#define IRLAN_SHORT  1
DECL|macro|IRLAN_ARRAY
mdefine_line|#define IRLAN_ARRAY  2
DECL|macro|IRLAN_MAX_HEADER
mdefine_line|#define IRLAN_MAX_HEADER (TTP_HEADER+LMP_HEADER+LAP_MAX_HEADER)
multiline_comment|/*&n; *  IrLAN client&n; */
DECL|struct|irlan_client_cb
r_struct
id|irlan_client_cb
(brace
DECL|member|state
r_int
id|state
suffix:semicolon
DECL|member|open_retries
r_int
id|open_retries
suffix:semicolon
DECL|member|tsap_ctrl
r_struct
id|tsap_cb
op_star
id|tsap_ctrl
suffix:semicolon
DECL|member|max_sdu_size
id|__u32
id|max_sdu_size
suffix:semicolon
DECL|member|max_header_size
id|__u8
id|max_header_size
suffix:semicolon
DECL|member|access_type
r_int
id|access_type
suffix:semicolon
multiline_comment|/* Access type of provider */
DECL|member|reconnect_key
id|__u8
id|reconnect_key
(braket
l_int|255
)braket
suffix:semicolon
DECL|member|key_len
id|__u8
id|key_len
suffix:semicolon
DECL|member|recv_arb_val
id|__u16
id|recv_arb_val
suffix:semicolon
DECL|member|max_frame
id|__u16
id|max_frame
suffix:semicolon
DECL|member|filter_type
r_int
id|filter_type
suffix:semicolon
DECL|member|unicast_open
r_int
id|unicast_open
suffix:semicolon
DECL|member|broadcast_open
r_int
id|broadcast_open
suffix:semicolon
DECL|member|tx_busy
r_int
id|tx_busy
suffix:semicolon
DECL|member|txq
r_struct
id|sk_buff_head
id|txq
suffix:semicolon
multiline_comment|/* Transmit control queue */
DECL|member|iriap
r_struct
id|iriap_cb
op_star
id|iriap
suffix:semicolon
DECL|member|kick_timer
r_struct
id|timer_list
id|kick_timer
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * IrLAN provider&n; */
DECL|struct|irlan_provider_cb
r_struct
id|irlan_provider_cb
(brace
DECL|member|state
r_int
id|state
suffix:semicolon
DECL|member|tsap_ctrl
r_struct
id|tsap_cb
op_star
id|tsap_ctrl
suffix:semicolon
DECL|member|max_sdu_size
id|__u32
id|max_sdu_size
suffix:semicolon
DECL|member|max_header_size
id|__u8
id|max_header_size
suffix:semicolon
multiline_comment|/*&n;&t; *  Store some values here which are used by the provider to parse&n;&t; *  the filter operations&n;&t; */
DECL|member|data_chan
r_int
id|data_chan
suffix:semicolon
DECL|member|filter_type
r_int
id|filter_type
suffix:semicolon
DECL|member|filter_mode
r_int
id|filter_mode
suffix:semicolon
DECL|member|filter_operation
r_int
id|filter_operation
suffix:semicolon
DECL|member|filter_entry
r_int
id|filter_entry
suffix:semicolon
DECL|member|access_type
r_int
id|access_type
suffix:semicolon
multiline_comment|/* Access type */
DECL|member|send_arb_val
id|__u16
id|send_arb_val
suffix:semicolon
DECL|member|mac_address
id|__u8
id|mac_address
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* Generated MAC address for peer device */
)brace
suffix:semicolon
multiline_comment|/*&n; *  IrLAN control block&n; */
DECL|struct|irlan_cb
r_struct
id|irlan_cb
(brace
DECL|member|q
id|irda_queue_t
id|q
suffix:semicolon
multiline_comment|/* Must be first */
DECL|member|magic
r_int
id|magic
suffix:semicolon
DECL|member|dev
r_struct
id|net_device
id|dev
suffix:semicolon
multiline_comment|/* Ethernet device structure*/
DECL|member|stats
r_struct
id|net_device_stats
id|stats
suffix:semicolon
DECL|member|saddr
id|__u32
id|saddr
suffix:semicolon
multiline_comment|/* Source device address */
DECL|member|daddr
id|__u32
id|daddr
suffix:semicolon
multiline_comment|/* Destination device address */
DECL|member|disconnect_reason
r_int
id|disconnect_reason
suffix:semicolon
multiline_comment|/* Why we got disconnected */
DECL|member|media
r_int
id|media
suffix:semicolon
multiline_comment|/* Media type */
DECL|member|version
id|__u8
id|version
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* IrLAN version */
DECL|member|tsap_data
r_struct
id|tsap_cb
op_star
id|tsap_data
suffix:semicolon
multiline_comment|/* Data TSAP */
DECL|member|use_udata
r_int
id|use_udata
suffix:semicolon
multiline_comment|/* Use Unit Data transfers */
DECL|member|stsap_sel_data
id|__u8
id|stsap_sel_data
suffix:semicolon
multiline_comment|/* Source data TSAP selector */
DECL|member|dtsap_sel_data
id|__u8
id|dtsap_sel_data
suffix:semicolon
multiline_comment|/* Destination data TSAP selector */
DECL|member|dtsap_sel_ctrl
id|__u8
id|dtsap_sel_ctrl
suffix:semicolon
multiline_comment|/* Destination ctrl TSAP selector */
DECL|member|client
r_struct
id|irlan_client_cb
id|client
suffix:semicolon
multiline_comment|/* Client specific fields */
DECL|member|provider
r_struct
id|irlan_provider_cb
id|provider
suffix:semicolon
multiline_comment|/* Provider specific fields */
DECL|member|max_sdu_size
id|__u32
id|max_sdu_size
suffix:semicolon
DECL|member|max_header_size
id|__u8
id|max_header_size
suffix:semicolon
DECL|member|open_wait
id|wait_queue_head_t
id|open_wait
suffix:semicolon
DECL|member|watchdog_timer
r_struct
id|timer_list
id|watchdog_timer
suffix:semicolon
)brace
suffix:semicolon
r_struct
id|irlan_cb
op_star
id|irlan_open
c_func
(paren
id|__u32
id|saddr
comma
id|__u32
id|daddr
)paren
suffix:semicolon
r_void
id|irlan_close
c_func
(paren
r_struct
id|irlan_cb
op_star
id|self
)paren
suffix:semicolon
r_void
id|irlan_close_tsaps
c_func
(paren
r_struct
id|irlan_cb
op_star
id|self
)paren
suffix:semicolon
r_void
id|irlan_mod_inc_use_count
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|irlan_mod_dec_use_count
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|irlan_register_netdev
c_func
(paren
r_struct
id|irlan_cb
op_star
id|self
)paren
suffix:semicolon
r_void
id|irlan_ias_register
c_func
(paren
r_struct
id|irlan_cb
op_star
id|self
comma
id|__u8
id|tsap_sel
)paren
suffix:semicolon
r_void
id|irlan_start_watchdog_timer
c_func
(paren
r_struct
id|irlan_cb
op_star
id|self
comma
r_int
id|timeout
)paren
suffix:semicolon
r_void
id|irlan_open_data_tsap
c_func
(paren
r_struct
id|irlan_cb
op_star
id|self
)paren
suffix:semicolon
r_int
id|irlan_run_ctrl_tx_queue
c_func
(paren
r_struct
id|irlan_cb
op_star
id|self
)paren
suffix:semicolon
r_void
id|irlan_get_provider_info
c_func
(paren
r_struct
id|irlan_cb
op_star
id|self
)paren
suffix:semicolon
r_void
id|irlan_get_unicast_addr
c_func
(paren
r_struct
id|irlan_cb
op_star
id|self
)paren
suffix:semicolon
r_void
id|irlan_get_media_char
c_func
(paren
r_struct
id|irlan_cb
op_star
id|self
)paren
suffix:semicolon
r_void
id|irlan_open_data_channel
c_func
(paren
r_struct
id|irlan_cb
op_star
id|self
)paren
suffix:semicolon
r_void
id|irlan_close_data_channel
c_func
(paren
r_struct
id|irlan_cb
op_star
id|self
)paren
suffix:semicolon
r_void
id|irlan_set_multicast_filter
c_func
(paren
r_struct
id|irlan_cb
op_star
id|self
comma
r_int
id|status
)paren
suffix:semicolon
r_void
id|irlan_set_broadcast_filter
c_func
(paren
r_struct
id|irlan_cb
op_star
id|self
comma
r_int
id|status
)paren
suffix:semicolon
r_void
id|irlan_open_unicast_addr
c_func
(paren
r_struct
id|irlan_cb
op_star
id|self
)paren
suffix:semicolon
r_int
id|irlan_insert_byte_param
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_char
op_star
id|param
comma
id|__u8
id|value
)paren
suffix:semicolon
r_int
id|irlan_insert_short_param
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_char
op_star
id|param
comma
id|__u16
id|value
)paren
suffix:semicolon
r_int
id|irlan_insert_string_param
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_char
op_star
id|param
comma
r_char
op_star
id|value
)paren
suffix:semicolon
r_int
id|irlan_insert_array_param
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_char
op_star
id|name
comma
id|__u8
op_star
id|value
comma
id|__u16
id|value_len
)paren
suffix:semicolon
r_int
id|irlan_extract_param
c_func
(paren
id|__u8
op_star
id|buf
comma
r_char
op_star
id|name
comma
r_char
op_star
id|value
comma
id|__u16
op_star
id|len
)paren
suffix:semicolon
r_void
id|print_ret_code
c_func
(paren
id|__u8
id|code
)paren
suffix:semicolon
r_extern
id|hashbin_t
op_star
id|irlan
suffix:semicolon
macro_line|#endif
eof
