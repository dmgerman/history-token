multiline_comment|/* &n;   BlueZ - Bluetooth protocol stack for Linux&n;   Copyright (C) 2000-2001 Qualcomm Incorporated&n;&n;   Written 2000,2001 by Maxim Krasnyansky &lt;maxk@qualcomm.com&gt;&n;&n;   This program is free software; you can redistribute it and/or modify&n;   it under the terms of the GNU General Public License version 2 as&n;   published by the Free Software Foundation;&n;&n;   THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND, EXPRESS&n;   OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,&n;   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT OF THIRD PARTY RIGHTS.&n;   IN NO EVENT SHALL THE COPYRIGHT HOLDER(S) AND AUTHOR(S) BE LIABLE FOR ANY&n;   CLAIM, OR ANY SPECIAL INDIRECT OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES &n;   WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN &n;   ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF &n;   OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.&n;&n;   ALL LIABILITY, INCLUDING LIABILITY FOR INFRINGEMENT OF ANY PATENTS, &n;   COPYRIGHTS, TRADEMARKS OR OTHER RIGHTS, RELATING TO USE OF THIS &n;   SOFTWARE IS DISCLAIMED.&n;*/
multiline_comment|/*&n; * Bluetooth HCI UART(H4) protocol.&n; *&n; * $Id: hci_h4.c,v 1.3 2002/09/09 01:17:32 maxk Exp $    &n; */
DECL|macro|VERSION
mdefine_line|#define VERSION &quot;1.2&quot;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/poll.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/ioctl.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;net/bluetooth/bluetooth.h&gt;
macro_line|#include &lt;net/bluetooth/hci_core.h&gt;
macro_line|#include &quot;hci_uart.h&quot;
macro_line|#include &quot;hci_h4.h&quot;
macro_line|#ifndef CONFIG_BT_HCIUART_DEBUG
DECL|macro|BT_DBG
macro_line|#undef  BT_DBG
DECL|macro|BT_DBG
mdefine_line|#define BT_DBG( A... )
DECL|macro|BT_DMP
macro_line|#undef  BT_DMP
DECL|macro|BT_DMP
mdefine_line|#define BT_DMP( A... )
macro_line|#endif
multiline_comment|/* Initialize protocol */
DECL|function|h4_open
r_static
r_int
id|h4_open
c_func
(paren
r_struct
id|hci_uart
op_star
id|hu
)paren
(brace
r_struct
id|h4_struct
op_star
id|h4
suffix:semicolon
id|BT_DBG
c_func
(paren
l_string|&quot;hu %p&quot;
comma
id|hu
)paren
suffix:semicolon
id|h4
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|h4
)paren
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|h4
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|memset
c_func
(paren
id|h4
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|h4
)paren
)paren
suffix:semicolon
id|skb_queue_head_init
c_func
(paren
op_amp
id|h4-&gt;txq
)paren
suffix:semicolon
id|hu-&gt;priv
op_assign
id|h4
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Flush protocol data */
DECL|function|h4_flush
r_static
r_int
id|h4_flush
c_func
(paren
r_struct
id|hci_uart
op_star
id|hu
)paren
(brace
r_struct
id|h4_struct
op_star
id|h4
op_assign
id|hu-&gt;priv
suffix:semicolon
id|BT_DBG
c_func
(paren
l_string|&quot;hu %p&quot;
comma
id|hu
)paren
suffix:semicolon
id|skb_queue_purge
c_func
(paren
op_amp
id|h4-&gt;txq
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Close protocol */
DECL|function|h4_close
r_static
r_int
id|h4_close
c_func
(paren
r_struct
id|hci_uart
op_star
id|hu
)paren
(brace
r_struct
id|h4_struct
op_star
id|h4
op_assign
id|hu-&gt;priv
suffix:semicolon
id|hu-&gt;priv
op_assign
l_int|NULL
suffix:semicolon
id|BT_DBG
c_func
(paren
l_string|&quot;hu %p&quot;
comma
id|hu
)paren
suffix:semicolon
id|skb_queue_purge
c_func
(paren
op_amp
id|h4-&gt;txq
)paren
suffix:semicolon
r_if
c_cond
(paren
id|h4-&gt;rx_skb
)paren
id|kfree_skb
c_func
(paren
id|h4-&gt;rx_skb
)paren
suffix:semicolon
id|hu-&gt;priv
op_assign
l_int|NULL
suffix:semicolon
id|kfree
c_func
(paren
id|h4
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Enqueue frame for transmittion (padding, crc, etc) */
DECL|function|h4_enqueue
r_static
r_int
id|h4_enqueue
c_func
(paren
r_struct
id|hci_uart
op_star
id|hu
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|h4_struct
op_star
id|h4
op_assign
id|hu-&gt;priv
suffix:semicolon
id|BT_DBG
c_func
(paren
l_string|&quot;hu %p skb %p&quot;
comma
id|hu
comma
id|skb
)paren
suffix:semicolon
multiline_comment|/* Prepend skb with frame type */
id|memcpy
c_func
(paren
id|skb_push
c_func
(paren
id|skb
comma
l_int|1
)paren
comma
op_amp
id|skb-&gt;pkt_type
comma
l_int|1
)paren
suffix:semicolon
id|skb_queue_tail
c_func
(paren
op_amp
id|h4-&gt;txq
comma
id|skb
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|h4_check_data_len
r_static
r_inline
r_int
id|h4_check_data_len
c_func
(paren
r_struct
id|h4_struct
op_star
id|h4
comma
r_int
id|len
)paren
(brace
r_register
r_int
id|room
op_assign
id|skb_tailroom
c_func
(paren
id|h4-&gt;rx_skb
)paren
suffix:semicolon
id|BT_DBG
c_func
(paren
l_string|&quot;len %d room %d&quot;
comma
id|len
comma
id|room
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|len
)paren
(brace
id|BT_DMP
c_func
(paren
id|h4-&gt;rx_skb-&gt;data
comma
id|h4-&gt;rx_skb-&gt;len
)paren
suffix:semicolon
id|hci_recv_frame
c_func
(paren
id|h4-&gt;rx_skb
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|len
OG
id|room
)paren
(brace
id|BT_ERR
c_func
(paren
l_string|&quot;Data length is too large&quot;
)paren
suffix:semicolon
id|kfree_skb
c_func
(paren
id|h4-&gt;rx_skb
)paren
suffix:semicolon
)brace
r_else
(brace
id|h4-&gt;rx_state
op_assign
id|H4_W4_DATA
suffix:semicolon
id|h4-&gt;rx_count
op_assign
id|len
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
id|h4-&gt;rx_state
op_assign
id|H4_W4_PACKET_TYPE
suffix:semicolon
id|h4-&gt;rx_skb
op_assign
l_int|NULL
suffix:semicolon
id|h4-&gt;rx_count
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Recv data */
DECL|function|h4_recv
r_static
r_int
id|h4_recv
c_func
(paren
r_struct
id|hci_uart
op_star
id|hu
comma
r_void
op_star
id|data
comma
r_int
id|count
)paren
(brace
r_struct
id|h4_struct
op_star
id|h4
op_assign
id|hu-&gt;priv
suffix:semicolon
r_register
r_char
op_star
id|ptr
suffix:semicolon
r_struct
id|hci_event_hdr
op_star
id|eh
suffix:semicolon
r_struct
id|hci_acl_hdr
op_star
id|ah
suffix:semicolon
r_struct
id|hci_sco_hdr
op_star
id|sh
suffix:semicolon
r_register
r_int
id|len
comma
id|type
comma
id|dlen
suffix:semicolon
id|BT_DBG
c_func
(paren
l_string|&quot;hu %p count %d rx_state %ld rx_count %ld&quot;
comma
id|hu
comma
id|count
comma
id|h4-&gt;rx_state
comma
id|h4-&gt;rx_count
)paren
suffix:semicolon
id|ptr
op_assign
id|data
suffix:semicolon
r_while
c_loop
(paren
id|count
)paren
(brace
r_if
c_cond
(paren
id|h4-&gt;rx_count
)paren
(brace
id|len
op_assign
id|min_t
c_func
(paren
r_int
r_int
comma
id|h4-&gt;rx_count
comma
id|count
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|skb_put
c_func
(paren
id|h4-&gt;rx_skb
comma
id|len
)paren
comma
id|ptr
comma
id|len
)paren
suffix:semicolon
id|h4-&gt;rx_count
op_sub_assign
id|len
suffix:semicolon
id|count
op_sub_assign
id|len
suffix:semicolon
id|ptr
op_add_assign
id|len
suffix:semicolon
r_if
c_cond
(paren
id|h4-&gt;rx_count
)paren
r_continue
suffix:semicolon
r_switch
c_cond
(paren
id|h4-&gt;rx_state
)paren
(brace
r_case
id|H4_W4_DATA
suffix:colon
id|BT_DBG
c_func
(paren
l_string|&quot;Complete data&quot;
)paren
suffix:semicolon
id|BT_DMP
c_func
(paren
id|h4-&gt;rx_skb-&gt;data
comma
id|h4-&gt;rx_skb-&gt;len
)paren
suffix:semicolon
id|hci_recv_frame
c_func
(paren
id|h4-&gt;rx_skb
)paren
suffix:semicolon
id|h4-&gt;rx_state
op_assign
id|H4_W4_PACKET_TYPE
suffix:semicolon
id|h4-&gt;rx_skb
op_assign
l_int|NULL
suffix:semicolon
r_continue
suffix:semicolon
r_case
id|H4_W4_EVENT_HDR
suffix:colon
id|eh
op_assign
(paren
r_struct
id|hci_event_hdr
op_star
)paren
id|h4-&gt;rx_skb-&gt;data
suffix:semicolon
id|BT_DBG
c_func
(paren
l_string|&quot;Event header: evt 0x%2.2x plen %d&quot;
comma
id|eh-&gt;evt
comma
id|eh-&gt;plen
)paren
suffix:semicolon
id|h4_check_data_len
c_func
(paren
id|h4
comma
id|eh-&gt;plen
)paren
suffix:semicolon
r_continue
suffix:semicolon
r_case
id|H4_W4_ACL_HDR
suffix:colon
id|ah
op_assign
(paren
r_struct
id|hci_acl_hdr
op_star
)paren
id|h4-&gt;rx_skb-&gt;data
suffix:semicolon
id|dlen
op_assign
id|__le16_to_cpu
c_func
(paren
id|ah-&gt;dlen
)paren
suffix:semicolon
id|BT_DBG
c_func
(paren
l_string|&quot;ACL header: dlen %d&quot;
comma
id|dlen
)paren
suffix:semicolon
id|h4_check_data_len
c_func
(paren
id|h4
comma
id|dlen
)paren
suffix:semicolon
r_continue
suffix:semicolon
r_case
id|H4_W4_SCO_HDR
suffix:colon
id|sh
op_assign
(paren
r_struct
id|hci_sco_hdr
op_star
)paren
id|h4-&gt;rx_skb-&gt;data
suffix:semicolon
id|BT_DBG
c_func
(paren
l_string|&quot;SCO header: dlen %d&quot;
comma
id|sh-&gt;dlen
)paren
suffix:semicolon
id|h4_check_data_len
c_func
(paren
id|h4
comma
id|sh-&gt;dlen
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
)brace
multiline_comment|/* H4_W4_PACKET_TYPE */
r_switch
c_cond
(paren
op_star
id|ptr
)paren
(brace
r_case
id|HCI_EVENT_PKT
suffix:colon
id|BT_DBG
c_func
(paren
l_string|&quot;Event packet&quot;
)paren
suffix:semicolon
id|h4-&gt;rx_state
op_assign
id|H4_W4_EVENT_HDR
suffix:semicolon
id|h4-&gt;rx_count
op_assign
id|HCI_EVENT_HDR_SIZE
suffix:semicolon
id|type
op_assign
id|HCI_EVENT_PKT
suffix:semicolon
r_break
suffix:semicolon
r_case
id|HCI_ACLDATA_PKT
suffix:colon
id|BT_DBG
c_func
(paren
l_string|&quot;ACL packet&quot;
)paren
suffix:semicolon
id|h4-&gt;rx_state
op_assign
id|H4_W4_ACL_HDR
suffix:semicolon
id|h4-&gt;rx_count
op_assign
id|HCI_ACL_HDR_SIZE
suffix:semicolon
id|type
op_assign
id|HCI_ACLDATA_PKT
suffix:semicolon
r_break
suffix:semicolon
r_case
id|HCI_SCODATA_PKT
suffix:colon
id|BT_DBG
c_func
(paren
l_string|&quot;SCO packet&quot;
)paren
suffix:semicolon
id|h4-&gt;rx_state
op_assign
id|H4_W4_SCO_HDR
suffix:semicolon
id|h4-&gt;rx_count
op_assign
id|HCI_SCO_HDR_SIZE
suffix:semicolon
id|type
op_assign
id|HCI_SCODATA_PKT
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|BT_ERR
c_func
(paren
l_string|&quot;Unknown HCI packet type %2.2x&quot;
comma
(paren
id|__u8
)paren
op_star
id|ptr
)paren
suffix:semicolon
id|hu-&gt;hdev.stat.err_rx
op_increment
suffix:semicolon
id|ptr
op_increment
suffix:semicolon
id|count
op_decrement
suffix:semicolon
r_continue
suffix:semicolon
)brace
suffix:semicolon
id|ptr
op_increment
suffix:semicolon
id|count
op_decrement
suffix:semicolon
multiline_comment|/* Allocate packet */
id|h4-&gt;rx_skb
op_assign
id|bt_skb_alloc
c_func
(paren
id|HCI_MAX_FRAME_SIZE
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|h4-&gt;rx_skb
)paren
(brace
id|BT_ERR
c_func
(paren
l_string|&quot;Can&squot;t allocate mem for new packet&quot;
)paren
suffix:semicolon
id|h4-&gt;rx_state
op_assign
id|H4_W4_PACKET_TYPE
suffix:semicolon
id|h4-&gt;rx_count
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|h4-&gt;rx_skb-&gt;dev
op_assign
(paren
r_void
op_star
)paren
op_amp
id|hu-&gt;hdev
suffix:semicolon
id|h4-&gt;rx_skb-&gt;pkt_type
op_assign
id|type
suffix:semicolon
)brace
r_return
id|count
suffix:semicolon
)brace
DECL|function|h4_dequeue
r_static
r_struct
id|sk_buff
op_star
id|h4_dequeue
c_func
(paren
r_struct
id|hci_uart
op_star
id|hu
)paren
(brace
r_struct
id|h4_struct
op_star
id|h4
op_assign
id|hu-&gt;priv
suffix:semicolon
r_return
id|skb_dequeue
c_func
(paren
op_amp
id|h4-&gt;txq
)paren
suffix:semicolon
)brace
DECL|variable|h4p
r_static
r_struct
id|hci_uart_proto
id|h4p
op_assign
(brace
dot
id|id
op_assign
id|HCI_UART_H4
comma
dot
id|open
op_assign
id|h4_open
comma
dot
id|close
op_assign
id|h4_close
comma
dot
id|recv
op_assign
id|h4_recv
comma
dot
id|enqueue
op_assign
id|h4_enqueue
comma
dot
id|dequeue
op_assign
id|h4_dequeue
comma
dot
id|flush
op_assign
id|h4_flush
comma
)brace
suffix:semicolon
DECL|function|h4_init
r_int
id|h4_init
c_func
(paren
r_void
)paren
(brace
r_int
id|err
op_assign
id|hci_uart_register_proto
c_func
(paren
op_amp
id|h4p
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|err
)paren
id|BT_INFO
c_func
(paren
l_string|&quot;HCI H4 protocol initialized&quot;
)paren
suffix:semicolon
r_else
id|BT_ERR
c_func
(paren
l_string|&quot;HCI H4 protocol registration failed&quot;
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|h4_deinit
r_int
id|h4_deinit
c_func
(paren
r_void
)paren
(brace
r_return
id|hci_uart_unregister_proto
c_func
(paren
op_amp
id|h4p
)paren
suffix:semicolon
)brace
eof
