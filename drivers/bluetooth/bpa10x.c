multiline_comment|/*&n; *&n; *  Digianswer Bluetooth USB driver&n; *&n; *  Copyright (C) 2004-2005  Marcel Holtmann &lt;marcel@holtmann.org&gt;&n; *&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/usb.h&gt;
macro_line|#include &lt;net/bluetooth/bluetooth.h&gt;
macro_line|#include &lt;net/bluetooth/hci_core.h&gt;
macro_line|#ifndef CONFIG_BT_HCIBPA10X_DEBUG
DECL|macro|BT_DBG
macro_line|#undef  BT_DBG
DECL|macro|BT_DBG
mdefine_line|#define BT_DBG(D...)
macro_line|#endif
DECL|macro|VERSION
mdefine_line|#define VERSION &quot;0.8&quot;
DECL|variable|ignore
r_static
r_int
id|ignore
op_assign
l_int|0
suffix:semicolon
DECL|variable|bpa10x_table
r_static
r_struct
id|usb_device_id
id|bpa10x_table
(braket
)braket
op_assign
(brace
multiline_comment|/* Tektronix BPA 100/105 (Digianswer) */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x08fd
comma
l_int|0x0002
)paren
)brace
comma
(brace
)brace
multiline_comment|/* Terminating entry */
)brace
suffix:semicolon
id|MODULE_DEVICE_TABLE
c_func
(paren
id|usb
comma
id|bpa10x_table
)paren
suffix:semicolon
DECL|macro|BPA10X_CMD_EP
mdefine_line|#define BPA10X_CMD_EP&t;&t;0x00
DECL|macro|BPA10X_EVT_EP
mdefine_line|#define BPA10X_EVT_EP&t;&t;0x81
DECL|macro|BPA10X_TX_EP
mdefine_line|#define BPA10X_TX_EP&t;&t;0x02
DECL|macro|BPA10X_RX_EP
mdefine_line|#define BPA10X_RX_EP&t;&t;0x82
DECL|macro|BPA10X_CMD_BUF_SIZE
mdefine_line|#define BPA10X_CMD_BUF_SIZE&t;252
DECL|macro|BPA10X_EVT_BUF_SIZE
mdefine_line|#define BPA10X_EVT_BUF_SIZE&t;16
DECL|macro|BPA10X_TX_BUF_SIZE
mdefine_line|#define BPA10X_TX_BUF_SIZE&t;384
DECL|macro|BPA10X_RX_BUF_SIZE
mdefine_line|#define BPA10X_RX_BUF_SIZE&t;384
DECL|struct|bpa10x_data
r_struct
id|bpa10x_data
(brace
DECL|member|hdev
r_struct
id|hci_dev
op_star
id|hdev
suffix:semicolon
DECL|member|udev
r_struct
id|usb_device
op_star
id|udev
suffix:semicolon
DECL|member|lock
id|rwlock_t
id|lock
suffix:semicolon
DECL|member|cmd_queue
r_struct
id|sk_buff_head
id|cmd_queue
suffix:semicolon
DECL|member|cmd_urb
r_struct
id|urb
op_star
id|cmd_urb
suffix:semicolon
DECL|member|evt_urb
r_struct
id|urb
op_star
id|evt_urb
suffix:semicolon
DECL|member|evt_skb
r_struct
id|sk_buff
op_star
id|evt_skb
suffix:semicolon
DECL|member|evt_len
r_int
r_int
id|evt_len
suffix:semicolon
DECL|member|tx_queue
r_struct
id|sk_buff_head
id|tx_queue
suffix:semicolon
DECL|member|tx_urb
r_struct
id|urb
op_star
id|tx_urb
suffix:semicolon
DECL|member|rx_urb
r_struct
id|urb
op_star
id|rx_urb
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|HCI_VENDOR_HDR_SIZE
mdefine_line|#define HCI_VENDOR_HDR_SIZE&t;5
DECL|struct|hci_vendor_hdr
r_struct
id|hci_vendor_hdr
(brace
DECL|member|type
id|__u8
id|type
suffix:semicolon
DECL|member|snum
id|__u16
id|snum
suffix:semicolon
DECL|member|dlen
id|__u16
id|dlen
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|function|bpa10x_recv_bulk
r_static
r_void
id|bpa10x_recv_bulk
c_func
(paren
r_struct
id|bpa10x_data
op_star
id|data
comma
r_int
r_char
op_star
id|buf
comma
r_int
id|count
)paren
(brace
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
r_struct
id|hci_vendor_hdr
op_star
id|vh
suffix:semicolon
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
r_int
id|len
suffix:semicolon
r_while
c_loop
(paren
id|count
)paren
(brace
r_switch
c_cond
(paren
op_star
id|buf
op_increment
)paren
(brace
r_case
id|HCI_ACLDATA_PKT
suffix:colon
id|ah
op_assign
(paren
r_struct
id|hci_acl_hdr
op_star
)paren
id|buf
suffix:semicolon
id|len
op_assign
id|HCI_ACL_HDR_SIZE
op_plus
id|__le16_to_cpu
c_func
(paren
id|ah-&gt;dlen
)paren
suffix:semicolon
id|skb
op_assign
id|bt_skb_alloc
c_func
(paren
id|len
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb
)paren
(brace
id|memcpy
c_func
(paren
id|skb_put
c_func
(paren
id|skb
comma
id|len
)paren
comma
id|buf
comma
id|len
)paren
suffix:semicolon
id|skb-&gt;dev
op_assign
(paren
r_void
op_star
)paren
id|data-&gt;hdev
suffix:semicolon
id|skb-&gt;pkt_type
op_assign
id|HCI_ACLDATA_PKT
suffix:semicolon
id|hci_recv_frame
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|HCI_SCODATA_PKT
suffix:colon
id|sh
op_assign
(paren
r_struct
id|hci_sco_hdr
op_star
)paren
id|buf
suffix:semicolon
id|len
op_assign
id|HCI_SCO_HDR_SIZE
op_plus
id|sh-&gt;dlen
suffix:semicolon
id|skb
op_assign
id|bt_skb_alloc
c_func
(paren
id|len
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb
)paren
(brace
id|memcpy
c_func
(paren
id|skb_put
c_func
(paren
id|skb
comma
id|len
)paren
comma
id|buf
comma
id|len
)paren
suffix:semicolon
id|skb-&gt;dev
op_assign
(paren
r_void
op_star
)paren
id|data-&gt;hdev
suffix:semicolon
id|skb-&gt;pkt_type
op_assign
id|HCI_SCODATA_PKT
suffix:semicolon
id|hci_recv_frame
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|HCI_VENDOR_PKT
suffix:colon
id|vh
op_assign
(paren
r_struct
id|hci_vendor_hdr
op_star
)paren
id|buf
suffix:semicolon
id|len
op_assign
id|HCI_VENDOR_HDR_SIZE
op_plus
id|__le16_to_cpu
c_func
(paren
id|vh-&gt;dlen
)paren
suffix:semicolon
id|skb
op_assign
id|bt_skb_alloc
c_func
(paren
id|len
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb
)paren
(brace
id|memcpy
c_func
(paren
id|skb_put
c_func
(paren
id|skb
comma
id|len
)paren
comma
id|buf
comma
id|len
)paren
suffix:semicolon
id|skb-&gt;dev
op_assign
(paren
r_void
op_star
)paren
id|data-&gt;hdev
suffix:semicolon
id|skb-&gt;pkt_type
op_assign
id|HCI_VENDOR_PKT
suffix:semicolon
id|hci_recv_frame
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_default
suffix:colon
id|len
op_assign
id|count
op_minus
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
id|buf
op_add_assign
id|len
suffix:semicolon
id|count
op_sub_assign
(paren
id|len
op_plus
l_int|1
)paren
suffix:semicolon
)brace
)brace
DECL|function|bpa10x_recv_event
r_static
r_int
id|bpa10x_recv_event
c_func
(paren
r_struct
id|bpa10x_data
op_star
id|data
comma
r_int
r_char
op_star
id|buf
comma
r_int
id|size
)paren
(brace
id|BT_DBG
c_func
(paren
l_string|&quot;data %p buf %p size %d&quot;
comma
id|data
comma
id|buf
comma
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|data-&gt;evt_skb
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb
op_assign
id|data-&gt;evt_skb
suffix:semicolon
id|memcpy
c_func
(paren
id|skb_put
c_func
(paren
id|skb
comma
id|size
)paren
comma
id|buf
comma
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb-&gt;len
op_eq
id|data-&gt;evt_len
)paren
(brace
id|data-&gt;evt_skb
op_assign
l_int|NULL
suffix:semicolon
id|data-&gt;evt_len
op_assign
l_int|0
suffix:semicolon
id|hci_recv_frame
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
r_struct
id|hci_event_hdr
op_star
id|hdr
suffix:semicolon
r_int
r_char
id|pkt_type
suffix:semicolon
r_int
id|pkt_len
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|size
OL
id|HCI_EVENT_HDR_SIZE
op_plus
l_int|1
)paren
(brace
id|BT_ERR
c_func
(paren
l_string|&quot;%s event packet block with size %d is too short&quot;
comma
id|data-&gt;hdev-&gt;name
comma
id|size
)paren
suffix:semicolon
r_return
op_minus
id|EILSEQ
suffix:semicolon
)brace
id|pkt_type
op_assign
op_star
id|buf
op_increment
suffix:semicolon
id|size
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|pkt_type
op_ne
id|HCI_EVENT_PKT
)paren
(brace
id|BT_ERR
c_func
(paren
l_string|&quot;%s unexpected event packet start byte 0x%02x&quot;
comma
id|data-&gt;hdev-&gt;name
comma
id|pkt_type
)paren
suffix:semicolon
r_return
op_minus
id|EPROTO
suffix:semicolon
)brace
id|hdr
op_assign
(paren
r_struct
id|hci_event_hdr
op_star
)paren
id|buf
suffix:semicolon
id|pkt_len
op_assign
id|HCI_EVENT_HDR_SIZE
op_plus
id|hdr-&gt;plen
suffix:semicolon
id|skb
op_assign
id|bt_skb_alloc
c_func
(paren
id|pkt_len
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|skb
)paren
(brace
id|BT_ERR
c_func
(paren
l_string|&quot;%s no memory for new event packet&quot;
comma
id|data-&gt;hdev-&gt;name
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|skb-&gt;dev
op_assign
(paren
r_void
op_star
)paren
id|data-&gt;hdev
suffix:semicolon
id|skb-&gt;pkt_type
op_assign
id|pkt_type
suffix:semicolon
id|memcpy
c_func
(paren
id|skb_put
c_func
(paren
id|skb
comma
id|size
)paren
comma
id|buf
comma
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pkt_len
op_eq
id|size
)paren
(brace
id|hci_recv_frame
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
r_else
(brace
id|data-&gt;evt_skb
op_assign
id|skb
suffix:semicolon
id|data-&gt;evt_len
op_assign
id|pkt_len
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|bpa10x_wakeup
r_static
r_void
id|bpa10x_wakeup
c_func
(paren
r_struct
id|bpa10x_data
op_star
id|data
)paren
(brace
r_struct
id|urb
op_star
id|urb
suffix:semicolon
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
r_int
id|err
suffix:semicolon
id|BT_DBG
c_func
(paren
l_string|&quot;data %p&quot;
comma
id|data
)paren
suffix:semicolon
id|urb
op_assign
id|data-&gt;cmd_urb
suffix:semicolon
r_if
c_cond
(paren
id|urb-&gt;status
op_eq
op_minus
id|EINPROGRESS
)paren
id|skb
op_assign
l_int|NULL
suffix:semicolon
r_else
id|skb
op_assign
id|skb_dequeue
c_func
(paren
op_amp
id|data-&gt;cmd_queue
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb
)paren
(brace
r_struct
id|usb_ctrlrequest
op_star
id|cr
suffix:semicolon
r_if
c_cond
(paren
id|skb-&gt;len
OG
id|BPA10X_CMD_BUF_SIZE
)paren
(brace
id|BT_ERR
c_func
(paren
l_string|&quot;%s command packet with size %d is too big&quot;
comma
id|data-&gt;hdev-&gt;name
comma
id|skb-&gt;len
)paren
suffix:semicolon
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|cr
op_assign
(paren
r_struct
id|usb_ctrlrequest
op_star
)paren
id|urb-&gt;setup_packet
suffix:semicolon
id|cr-&gt;wLength
op_assign
id|__cpu_to_le16
c_func
(paren
id|skb-&gt;len
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|urb-&gt;transfer_buffer
comma
id|skb-&gt;data
comma
id|skb-&gt;len
)paren
suffix:semicolon
id|urb-&gt;transfer_buffer_length
op_assign
id|skb-&gt;len
suffix:semicolon
id|err
op_assign
id|usb_submit_urb
c_func
(paren
id|urb
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
op_logical_and
id|err
op_ne
op_minus
id|ENODEV
)paren
(brace
id|BT_ERR
c_func
(paren
l_string|&quot;%s submit failed for command urb %p with error %d&quot;
comma
id|data-&gt;hdev-&gt;name
comma
id|urb
comma
id|err
)paren
suffix:semicolon
id|skb_queue_head
c_func
(paren
op_amp
id|data-&gt;cmd_queue
comma
id|skb
)paren
suffix:semicolon
)brace
r_else
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
id|urb
op_assign
id|data-&gt;tx_urb
suffix:semicolon
r_if
c_cond
(paren
id|urb-&gt;status
op_eq
op_minus
id|EINPROGRESS
)paren
id|skb
op_assign
l_int|NULL
suffix:semicolon
r_else
id|skb
op_assign
id|skb_dequeue
c_func
(paren
op_amp
id|data-&gt;tx_queue
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb
)paren
(brace
id|memcpy
c_func
(paren
id|urb-&gt;transfer_buffer
comma
id|skb-&gt;data
comma
id|skb-&gt;len
)paren
suffix:semicolon
id|urb-&gt;transfer_buffer_length
op_assign
id|skb-&gt;len
suffix:semicolon
id|err
op_assign
id|usb_submit_urb
c_func
(paren
id|urb
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
op_logical_and
id|err
op_ne
op_minus
id|ENODEV
)paren
(brace
id|BT_ERR
c_func
(paren
l_string|&quot;%s submit failed for command urb %p with error %d&quot;
comma
id|data-&gt;hdev-&gt;name
comma
id|urb
comma
id|err
)paren
suffix:semicolon
id|skb_queue_head
c_func
(paren
op_amp
id|data-&gt;tx_queue
comma
id|skb
)paren
suffix:semicolon
)brace
r_else
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
)brace
DECL|function|bpa10x_complete
r_static
r_void
id|bpa10x_complete
c_func
(paren
r_struct
id|urb
op_star
id|urb
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_struct
id|bpa10x_data
op_star
id|data
op_assign
id|urb-&gt;context
suffix:semicolon
r_int
r_char
op_star
id|buf
op_assign
id|urb-&gt;transfer_buffer
suffix:semicolon
r_int
id|err
comma
id|count
op_assign
id|urb-&gt;actual_length
suffix:semicolon
id|BT_DBG
c_func
(paren
l_string|&quot;data %p urb %p buf %p count %d&quot;
comma
id|data
comma
id|urb
comma
id|buf
comma
id|count
)paren
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|data-&gt;lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|test_bit
c_func
(paren
id|HCI_RUNNING
comma
op_amp
id|data-&gt;hdev-&gt;flags
)paren
)paren
r_goto
id|unlock
suffix:semicolon
r_if
c_cond
(paren
id|urb-&gt;status
OL
l_int|0
op_logical_or
op_logical_neg
id|count
)paren
r_goto
id|resubmit
suffix:semicolon
r_if
c_cond
(paren
id|usb_pipein
c_func
(paren
id|urb-&gt;pipe
)paren
)paren
(brace
id|data-&gt;hdev-&gt;stat.byte_rx
op_add_assign
id|count
suffix:semicolon
r_if
c_cond
(paren
id|usb_pipetype
c_func
(paren
id|urb-&gt;pipe
)paren
op_eq
id|PIPE_INTERRUPT
)paren
id|bpa10x_recv_event
c_func
(paren
id|data
comma
id|buf
comma
id|count
)paren
suffix:semicolon
r_if
c_cond
(paren
id|usb_pipetype
c_func
(paren
id|urb-&gt;pipe
)paren
op_eq
id|PIPE_BULK
)paren
id|bpa10x_recv_bulk
c_func
(paren
id|data
comma
id|buf
comma
id|count
)paren
suffix:semicolon
)brace
r_else
(brace
id|data-&gt;hdev-&gt;stat.byte_tx
op_add_assign
id|count
suffix:semicolon
id|bpa10x_wakeup
c_func
(paren
id|data
)paren
suffix:semicolon
)brace
id|resubmit
suffix:colon
r_if
c_cond
(paren
id|usb_pipein
c_func
(paren
id|urb-&gt;pipe
)paren
)paren
(brace
id|err
op_assign
id|usb_submit_urb
c_func
(paren
id|urb
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
op_logical_and
id|err
op_ne
op_minus
id|ENODEV
)paren
(brace
id|BT_ERR
c_func
(paren
l_string|&quot;%s urb %p type %d resubmit status %d&quot;
comma
id|data-&gt;hdev-&gt;name
comma
id|urb
comma
id|usb_pipetype
c_func
(paren
id|urb-&gt;pipe
)paren
comma
id|err
)paren
suffix:semicolon
)brace
)brace
id|unlock
suffix:colon
id|read_unlock
c_func
(paren
op_amp
id|data-&gt;lock
)paren
suffix:semicolon
)brace
DECL|function|bpa10x_alloc_urb
r_static
r_inline
r_struct
id|urb
op_star
id|bpa10x_alloc_urb
c_func
(paren
r_struct
id|usb_device
op_star
id|udev
comma
r_int
r_int
id|pipe
comma
r_int
id|size
comma
r_int
id|flags
comma
r_void
op_star
id|data
)paren
(brace
r_struct
id|urb
op_star
id|urb
suffix:semicolon
r_struct
id|usb_ctrlrequest
op_star
id|cr
suffix:semicolon
r_int
r_char
op_star
id|buf
suffix:semicolon
id|BT_DBG
c_func
(paren
l_string|&quot;udev %p data %p&quot;
comma
id|udev
comma
id|data
)paren
suffix:semicolon
id|urb
op_assign
id|usb_alloc_urb
c_func
(paren
l_int|0
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|urb
)paren
r_return
l_int|NULL
suffix:semicolon
id|buf
op_assign
id|kmalloc
c_func
(paren
id|size
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|buf
)paren
(brace
id|usb_free_urb
c_func
(paren
id|urb
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|usb_pipetype
c_func
(paren
id|pipe
)paren
)paren
(brace
r_case
id|PIPE_CONTROL
suffix:colon
id|cr
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|cr
)paren
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cr
)paren
(brace
id|kfree
c_func
(paren
id|buf
)paren
suffix:semicolon
id|usb_free_urb
c_func
(paren
id|urb
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|cr-&gt;bRequestType
op_assign
id|USB_TYPE_VENDOR
suffix:semicolon
id|cr-&gt;bRequest
op_assign
l_int|0
suffix:semicolon
id|cr-&gt;wIndex
op_assign
l_int|0
suffix:semicolon
id|cr-&gt;wValue
op_assign
l_int|0
suffix:semicolon
id|cr-&gt;wLength
op_assign
id|__cpu_to_le16
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|usb_fill_control_urb
c_func
(paren
id|urb
comma
id|udev
comma
id|pipe
comma
(paren
r_void
op_star
)paren
id|cr
comma
id|buf
comma
l_int|0
comma
id|bpa10x_complete
comma
id|data
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PIPE_INTERRUPT
suffix:colon
id|usb_fill_int_urb
c_func
(paren
id|urb
comma
id|udev
comma
id|pipe
comma
id|buf
comma
id|size
comma
id|bpa10x_complete
comma
id|data
comma
l_int|1
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PIPE_BULK
suffix:colon
id|usb_fill_bulk_urb
c_func
(paren
id|urb
comma
id|udev
comma
id|pipe
comma
id|buf
comma
id|size
comma
id|bpa10x_complete
comma
id|data
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|kfree
c_func
(paren
id|buf
)paren
suffix:semicolon
id|usb_free_urb
c_func
(paren
id|urb
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_return
id|urb
suffix:semicolon
)brace
DECL|function|bpa10x_free_urb
r_static
r_inline
r_void
id|bpa10x_free_urb
c_func
(paren
r_struct
id|urb
op_star
id|urb
)paren
(brace
id|BT_DBG
c_func
(paren
l_string|&quot;urb %p&quot;
comma
id|urb
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|urb
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|urb-&gt;setup_packet
)paren
id|kfree
c_func
(paren
id|urb-&gt;setup_packet
)paren
suffix:semicolon
r_if
c_cond
(paren
id|urb-&gt;transfer_buffer
)paren
id|kfree
c_func
(paren
id|urb-&gt;transfer_buffer
)paren
suffix:semicolon
id|usb_free_urb
c_func
(paren
id|urb
)paren
suffix:semicolon
)brace
DECL|function|bpa10x_open
r_static
r_int
id|bpa10x_open
c_func
(paren
r_struct
id|hci_dev
op_star
id|hdev
)paren
(brace
r_struct
id|bpa10x_data
op_star
id|data
op_assign
id|hdev-&gt;driver_data
suffix:semicolon
r_struct
id|usb_device
op_star
id|udev
op_assign
id|data-&gt;udev
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
id|err
suffix:semicolon
id|BT_DBG
c_func
(paren
l_string|&quot;hdev %p data %p&quot;
comma
id|hdev
comma
id|data
)paren
suffix:semicolon
r_if
c_cond
(paren
id|test_and_set_bit
c_func
(paren
id|HCI_RUNNING
comma
op_amp
id|hdev-&gt;flags
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|data-&gt;cmd_urb
op_assign
id|bpa10x_alloc_urb
c_func
(paren
id|udev
comma
id|usb_sndctrlpipe
c_func
(paren
id|udev
comma
id|BPA10X_CMD_EP
)paren
comma
id|BPA10X_CMD_BUF_SIZE
comma
id|GFP_KERNEL
comma
id|data
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|data-&gt;cmd_urb
)paren
(brace
id|err
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|done
suffix:semicolon
)brace
id|data-&gt;evt_urb
op_assign
id|bpa10x_alloc_urb
c_func
(paren
id|udev
comma
id|usb_rcvintpipe
c_func
(paren
id|udev
comma
id|BPA10X_EVT_EP
)paren
comma
id|BPA10X_EVT_BUF_SIZE
comma
id|GFP_KERNEL
comma
id|data
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|data-&gt;evt_urb
)paren
(brace
id|bpa10x_free_urb
c_func
(paren
id|data-&gt;cmd_urb
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|done
suffix:semicolon
)brace
id|data-&gt;rx_urb
op_assign
id|bpa10x_alloc_urb
c_func
(paren
id|udev
comma
id|usb_rcvbulkpipe
c_func
(paren
id|udev
comma
id|BPA10X_RX_EP
)paren
comma
id|BPA10X_RX_BUF_SIZE
comma
id|GFP_KERNEL
comma
id|data
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|data-&gt;rx_urb
)paren
(brace
id|bpa10x_free_urb
c_func
(paren
id|data-&gt;evt_urb
)paren
suffix:semicolon
id|bpa10x_free_urb
c_func
(paren
id|data-&gt;cmd_urb
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|done
suffix:semicolon
)brace
id|data-&gt;tx_urb
op_assign
id|bpa10x_alloc_urb
c_func
(paren
id|udev
comma
id|usb_sndbulkpipe
c_func
(paren
id|udev
comma
id|BPA10X_TX_EP
)paren
comma
id|BPA10X_TX_BUF_SIZE
comma
id|GFP_KERNEL
comma
id|data
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|data-&gt;rx_urb
)paren
(brace
id|bpa10x_free_urb
c_func
(paren
id|data-&gt;rx_urb
)paren
suffix:semicolon
id|bpa10x_free_urb
c_func
(paren
id|data-&gt;evt_urb
)paren
suffix:semicolon
id|bpa10x_free_urb
c_func
(paren
id|data-&gt;cmd_urb
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|done
suffix:semicolon
)brace
id|write_lock_irqsave
c_func
(paren
op_amp
id|data-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|err
op_assign
id|usb_submit_urb
c_func
(paren
id|data-&gt;evt_urb
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
(brace
id|BT_ERR
c_func
(paren
l_string|&quot;%s submit failed for event urb %p with error %d&quot;
comma
id|data-&gt;hdev-&gt;name
comma
id|data-&gt;evt_urb
comma
id|err
)paren
suffix:semicolon
)brace
r_else
(brace
id|err
op_assign
id|usb_submit_urb
c_func
(paren
id|data-&gt;rx_urb
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
(brace
id|BT_ERR
c_func
(paren
l_string|&quot;%s submit failed for rx urb %p with error %d&quot;
comma
id|data-&gt;hdev-&gt;name
comma
id|data-&gt;evt_urb
comma
id|err
)paren
suffix:semicolon
id|usb_kill_urb
c_func
(paren
id|data-&gt;evt_urb
)paren
suffix:semicolon
)brace
)brace
id|write_unlock_irqrestore
c_func
(paren
op_amp
id|data-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|done
suffix:colon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
id|clear_bit
c_func
(paren
id|HCI_RUNNING
comma
op_amp
id|hdev-&gt;flags
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|bpa10x_close
r_static
r_int
id|bpa10x_close
c_func
(paren
r_struct
id|hci_dev
op_star
id|hdev
)paren
(brace
r_struct
id|bpa10x_data
op_star
id|data
op_assign
id|hdev-&gt;driver_data
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|BT_DBG
c_func
(paren
l_string|&quot;hdev %p data %p&quot;
comma
id|hdev
comma
id|data
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|test_and_clear_bit
c_func
(paren
id|HCI_RUNNING
comma
op_amp
id|hdev-&gt;flags
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|write_lock_irqsave
c_func
(paren
op_amp
id|data-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|skb_queue_purge
c_func
(paren
op_amp
id|data-&gt;cmd_queue
)paren
suffix:semicolon
id|usb_kill_urb
c_func
(paren
id|data-&gt;cmd_urb
)paren
suffix:semicolon
id|usb_kill_urb
c_func
(paren
id|data-&gt;evt_urb
)paren
suffix:semicolon
id|usb_kill_urb
c_func
(paren
id|data-&gt;rx_urb
)paren
suffix:semicolon
id|usb_kill_urb
c_func
(paren
id|data-&gt;tx_urb
)paren
suffix:semicolon
id|write_unlock_irqrestore
c_func
(paren
op_amp
id|data-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|bpa10x_free_urb
c_func
(paren
id|data-&gt;cmd_urb
)paren
suffix:semicolon
id|bpa10x_free_urb
c_func
(paren
id|data-&gt;evt_urb
)paren
suffix:semicolon
id|bpa10x_free_urb
c_func
(paren
id|data-&gt;rx_urb
)paren
suffix:semicolon
id|bpa10x_free_urb
c_func
(paren
id|data-&gt;tx_urb
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|bpa10x_flush
r_static
r_int
id|bpa10x_flush
c_func
(paren
r_struct
id|hci_dev
op_star
id|hdev
)paren
(brace
r_struct
id|bpa10x_data
op_star
id|data
op_assign
id|hdev-&gt;driver_data
suffix:semicolon
id|BT_DBG
c_func
(paren
l_string|&quot;hdev %p data %p&quot;
comma
id|hdev
comma
id|data
)paren
suffix:semicolon
id|skb_queue_purge
c_func
(paren
op_amp
id|data-&gt;cmd_queue
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|bpa10x_send_frame
r_static
r_int
id|bpa10x_send_frame
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|hci_dev
op_star
id|hdev
op_assign
(paren
r_struct
id|hci_dev
op_star
)paren
id|skb-&gt;dev
suffix:semicolon
r_struct
id|bpa10x_data
op_star
id|data
suffix:semicolon
id|BT_DBG
c_func
(paren
l_string|&quot;hdev %p skb %p type %d len %d&quot;
comma
id|hdev
comma
id|skb
comma
id|skb-&gt;pkt_type
comma
id|skb-&gt;len
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hdev
)paren
(brace
id|BT_ERR
c_func
(paren
l_string|&quot;Frame for unknown HCI device&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|test_bit
c_func
(paren
id|HCI_RUNNING
comma
op_amp
id|hdev-&gt;flags
)paren
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
id|data
op_assign
id|hdev-&gt;driver_data
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
(paren
id|skb-&gt;pkt_type
)paren
comma
l_int|1
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|skb-&gt;pkt_type
)paren
(brace
r_case
id|HCI_COMMAND_PKT
suffix:colon
id|hdev-&gt;stat.cmd_tx
op_increment
suffix:semicolon
id|skb_queue_tail
c_func
(paren
op_amp
id|data-&gt;cmd_queue
comma
id|skb
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|HCI_ACLDATA_PKT
suffix:colon
id|hdev-&gt;stat.acl_tx
op_increment
suffix:semicolon
id|skb_queue_tail
c_func
(paren
op_amp
id|data-&gt;tx_queue
comma
id|skb
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|HCI_SCODATA_PKT
suffix:colon
id|hdev-&gt;stat.sco_tx
op_increment
suffix:semicolon
id|skb_queue_tail
c_func
(paren
op_amp
id|data-&gt;tx_queue
comma
id|skb
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|data-&gt;lock
)paren
suffix:semicolon
id|bpa10x_wakeup
c_func
(paren
id|data
)paren
suffix:semicolon
id|read_unlock
c_func
(paren
op_amp
id|data-&gt;lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|bpa10x_destruct
r_static
r_void
id|bpa10x_destruct
c_func
(paren
r_struct
id|hci_dev
op_star
id|hdev
)paren
(brace
r_struct
id|bpa10x_data
op_star
id|data
op_assign
id|hdev-&gt;driver_data
suffix:semicolon
id|BT_DBG
c_func
(paren
l_string|&quot;hdev %p data %p&quot;
comma
id|hdev
comma
id|data
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|data
)paren
suffix:semicolon
)brace
DECL|function|bpa10x_probe
r_static
r_int
id|bpa10x_probe
c_func
(paren
r_struct
id|usb_interface
op_star
id|intf
comma
r_const
r_struct
id|usb_device_id
op_star
id|id
)paren
(brace
r_struct
id|usb_device
op_star
id|udev
op_assign
id|interface_to_usbdev
c_func
(paren
id|intf
)paren
suffix:semicolon
r_struct
id|hci_dev
op_star
id|hdev
suffix:semicolon
r_struct
id|bpa10x_data
op_star
id|data
suffix:semicolon
r_int
id|err
suffix:semicolon
id|BT_DBG
c_func
(paren
l_string|&quot;intf %p id %p&quot;
comma
id|intf
comma
id|id
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ignore
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|data
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|data
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|data
)paren
(brace
id|BT_ERR
c_func
(paren
l_string|&quot;Can&squot;t allocate data structure&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|memset
c_func
(paren
id|data
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|data
)paren
)paren
suffix:semicolon
id|data-&gt;udev
op_assign
id|udev
suffix:semicolon
id|rwlock_init
c_func
(paren
op_amp
id|data-&gt;lock
)paren
suffix:semicolon
id|skb_queue_head_init
c_func
(paren
op_amp
id|data-&gt;cmd_queue
)paren
suffix:semicolon
id|skb_queue_head_init
c_func
(paren
op_amp
id|data-&gt;tx_queue
)paren
suffix:semicolon
id|hdev
op_assign
id|hci_alloc_dev
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hdev
)paren
(brace
id|BT_ERR
c_func
(paren
l_string|&quot;Can&squot;t allocate HCI device&quot;
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|data
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|data-&gt;hdev
op_assign
id|hdev
suffix:semicolon
id|hdev-&gt;type
op_assign
id|HCI_USB
suffix:semicolon
id|hdev-&gt;driver_data
op_assign
id|data
suffix:semicolon
id|SET_HCIDEV_DEV
c_func
(paren
id|hdev
comma
op_amp
id|intf-&gt;dev
)paren
suffix:semicolon
id|hdev-&gt;open
op_assign
id|bpa10x_open
suffix:semicolon
id|hdev-&gt;close
op_assign
id|bpa10x_close
suffix:semicolon
id|hdev-&gt;flush
op_assign
id|bpa10x_flush
suffix:semicolon
id|hdev-&gt;send
op_assign
id|bpa10x_send_frame
suffix:semicolon
id|hdev-&gt;destruct
op_assign
id|bpa10x_destruct
suffix:semicolon
id|hdev-&gt;owner
op_assign
id|THIS_MODULE
suffix:semicolon
id|err
op_assign
id|hci_register_dev
c_func
(paren
id|hdev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
(brace
id|BT_ERR
c_func
(paren
l_string|&quot;Can&squot;t register HCI device&quot;
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|data
)paren
suffix:semicolon
id|hci_free_dev
c_func
(paren
id|hdev
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
id|usb_set_intfdata
c_func
(paren
id|intf
comma
id|data
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|bpa10x_disconnect
r_static
r_void
id|bpa10x_disconnect
c_func
(paren
r_struct
id|usb_interface
op_star
id|intf
)paren
(brace
r_struct
id|bpa10x_data
op_star
id|data
op_assign
id|usb_get_intfdata
c_func
(paren
id|intf
)paren
suffix:semicolon
r_struct
id|hci_dev
op_star
id|hdev
op_assign
id|data-&gt;hdev
suffix:semicolon
id|BT_DBG
c_func
(paren
l_string|&quot;intf %p&quot;
comma
id|intf
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hdev
)paren
r_return
suffix:semicolon
id|usb_set_intfdata
c_func
(paren
id|intf
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hci_unregister_dev
c_func
(paren
id|hdev
)paren
OL
l_int|0
)paren
id|BT_ERR
c_func
(paren
l_string|&quot;Can&squot;t unregister HCI device %s&quot;
comma
id|hdev-&gt;name
)paren
suffix:semicolon
id|hci_free_dev
c_func
(paren
id|hdev
)paren
suffix:semicolon
)brace
DECL|variable|bpa10x_driver
r_static
r_struct
id|usb_driver
id|bpa10x_driver
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|name
op_assign
l_string|&quot;bpa10x&quot;
comma
dot
id|probe
op_assign
id|bpa10x_probe
comma
dot
id|disconnect
op_assign
id|bpa10x_disconnect
comma
dot
id|id_table
op_assign
id|bpa10x_table
comma
)brace
suffix:semicolon
DECL|function|bpa10x_init
r_static
r_int
id|__init
id|bpa10x_init
c_func
(paren
r_void
)paren
(brace
r_int
id|err
suffix:semicolon
id|BT_INFO
c_func
(paren
l_string|&quot;Digianswer Bluetooth USB driver ver %s&quot;
comma
id|VERSION
)paren
suffix:semicolon
id|err
op_assign
id|usb_register
c_func
(paren
op_amp
id|bpa10x_driver
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
id|BT_ERR
c_func
(paren
l_string|&quot;Failed to register USB driver&quot;
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|bpa10x_exit
r_static
r_void
id|__exit
id|bpa10x_exit
c_func
(paren
r_void
)paren
(brace
id|usb_deregister
c_func
(paren
op_amp
id|bpa10x_driver
)paren
suffix:semicolon
)brace
DECL|variable|bpa10x_init
id|module_init
c_func
(paren
id|bpa10x_init
)paren
suffix:semicolon
DECL|variable|bpa10x_exit
id|module_exit
c_func
(paren
id|bpa10x_exit
)paren
suffix:semicolon
id|module_param
c_func
(paren
id|ignore
comma
r_bool
comma
l_int|0644
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|ignore
comma
l_string|&quot;Ignore devices from the matching table&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Marcel Holtmann &lt;marcel@holtmann.org&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Digianswer Bluetooth USB driver ver &quot;
id|VERSION
)paren
suffix:semicolon
DECL|variable|VERSION
id|MODULE_VERSION
c_func
(paren
id|VERSION
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
