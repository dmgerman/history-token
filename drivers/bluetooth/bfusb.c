multiline_comment|/*&n; *&n; *  AVM BlueFRITZ! USB driver&n; *&n; *  Copyright (C) 2003  Marcel Holtmann &lt;marcel@holtmann.org&gt;&n; *&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/firmware.h&gt;
macro_line|#include &lt;linux/usb.h&gt;
macro_line|#include &lt;net/bluetooth/bluetooth.h&gt;
macro_line|#include &lt;net/bluetooth/hci_core.h&gt;
macro_line|#ifndef CONFIG_BT_HCIBFUSB_DEBUG
DECL|macro|BT_DBG
macro_line|#undef  BT_DBG
DECL|macro|BT_DBG
mdefine_line|#define BT_DBG(D...)
macro_line|#endif
DECL|macro|VERSION
mdefine_line|#define VERSION &quot;1.1&quot;
DECL|variable|bfusb_driver
r_static
r_struct
id|usb_driver
id|bfusb_driver
suffix:semicolon
DECL|variable|bfusb_table
r_static
r_struct
id|usb_device_id
id|bfusb_table
(braket
)braket
op_assign
(brace
multiline_comment|/* AVM BlueFRITZ! USB */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x057c
comma
l_int|0x2200
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
id|bfusb_table
)paren
suffix:semicolon
DECL|macro|BFUSB_MAX_BLOCK_SIZE
mdefine_line|#define BFUSB_MAX_BLOCK_SIZE&t;256
DECL|macro|BFUSB_BLOCK_TIMEOUT
mdefine_line|#define BFUSB_BLOCK_TIMEOUT&t;(HZ * 3)
DECL|macro|BFUSB_TX_PROCESS
mdefine_line|#define BFUSB_TX_PROCESS&t;1
DECL|macro|BFUSB_TX_WAKEUP
mdefine_line|#define BFUSB_TX_WAKEUP&t;&t;2
DECL|macro|BFUSB_MAX_BULK_TX
mdefine_line|#define BFUSB_MAX_BULK_TX&t;2
DECL|macro|BFUSB_MAX_BULK_RX
mdefine_line|#define BFUSB_MAX_BULK_RX&t;2
DECL|struct|bfusb
r_struct
id|bfusb
(brace
DECL|member|hdev
r_struct
id|hci_dev
op_star
id|hdev
suffix:semicolon
DECL|member|state
r_int
r_int
id|state
suffix:semicolon
DECL|member|udev
r_struct
id|usb_device
op_star
id|udev
suffix:semicolon
DECL|member|bulk_in_ep
r_int
r_int
id|bulk_in_ep
suffix:semicolon
DECL|member|bulk_out_ep
r_int
r_int
id|bulk_out_ep
suffix:semicolon
DECL|member|bulk_pkt_size
r_int
r_int
id|bulk_pkt_size
suffix:semicolon
DECL|member|lock
id|rwlock_t
id|lock
suffix:semicolon
DECL|member|transmit_q
r_struct
id|sk_buff_head
id|transmit_q
suffix:semicolon
DECL|member|reassembly
r_struct
id|sk_buff
op_star
id|reassembly
suffix:semicolon
DECL|member|pending_tx
id|atomic_t
id|pending_tx
suffix:semicolon
DECL|member|pending_q
r_struct
id|sk_buff_head
id|pending_q
suffix:semicolon
DECL|member|completed_q
r_struct
id|sk_buff_head
id|completed_q
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|bfusb_scb
r_struct
id|bfusb_scb
(brace
DECL|member|urb
r_struct
id|urb
op_star
id|urb
suffix:semicolon
)brace
suffix:semicolon
r_static
r_void
id|bfusb_tx_complete
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
suffix:semicolon
r_static
r_void
id|bfusb_rx_complete
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
suffix:semicolon
DECL|function|bfusb_get_completed
r_static
r_struct
id|urb
op_star
id|bfusb_get_completed
c_func
(paren
r_struct
id|bfusb
op_star
id|bfusb
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
r_struct
id|urb
op_star
id|urb
op_assign
l_int|NULL
suffix:semicolon
id|BT_DBG
c_func
(paren
l_string|&quot;bfusb %p&quot;
comma
id|bfusb
)paren
suffix:semicolon
id|skb
op_assign
id|skb_dequeue
c_func
(paren
op_amp
id|bfusb-&gt;completed_q
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb
)paren
(brace
id|urb
op_assign
(paren
(paren
r_struct
id|bfusb_scb
op_star
)paren
id|skb-&gt;cb
)paren
op_member_access_from_pointer
id|urb
suffix:semicolon
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
r_return
id|urb
suffix:semicolon
)brace
DECL|function|bfusb_unlink_urbs
r_static
r_inline
r_void
id|bfusb_unlink_urbs
c_func
(paren
r_struct
id|bfusb
op_star
id|bfusb
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
r_struct
id|urb
op_star
id|urb
suffix:semicolon
id|BT_DBG
c_func
(paren
l_string|&quot;bfusb %p&quot;
comma
id|bfusb
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|skb
op_assign
id|skb_dequeue
c_func
(paren
op_amp
id|bfusb-&gt;pending_q
)paren
)paren
)paren
(brace
id|urb
op_assign
(paren
(paren
r_struct
id|bfusb_scb
op_star
)paren
id|skb-&gt;cb
)paren
op_member_access_from_pointer
id|urb
suffix:semicolon
id|usb_unlink_urb
c_func
(paren
id|urb
)paren
suffix:semicolon
id|skb_queue_tail
c_func
(paren
op_amp
id|bfusb-&gt;completed_q
comma
id|skb
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
id|urb
op_assign
id|bfusb_get_completed
c_func
(paren
id|bfusb
)paren
)paren
)paren
id|usb_free_urb
c_func
(paren
id|urb
)paren
suffix:semicolon
)brace
DECL|function|bfusb_send_bulk
r_static
r_int
id|bfusb_send_bulk
c_func
(paren
r_struct
id|bfusb
op_star
id|bfusb
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|bfusb_scb
op_star
id|scb
op_assign
(paren
r_void
op_star
)paren
id|skb-&gt;cb
suffix:semicolon
r_struct
id|urb
op_star
id|urb
op_assign
id|bfusb_get_completed
c_func
(paren
id|bfusb
)paren
suffix:semicolon
r_int
id|err
comma
id|pipe
suffix:semicolon
id|BT_DBG
c_func
(paren
l_string|&quot;bfusb %p skb %p len %d&quot;
comma
id|bfusb
comma
id|skb
comma
id|skb-&gt;len
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|urb
op_logical_and
op_logical_neg
(paren
id|urb
op_assign
id|usb_alloc_urb
c_func
(paren
l_int|0
comma
id|GFP_ATOMIC
)paren
)paren
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|pipe
op_assign
id|usb_sndbulkpipe
c_func
(paren
id|bfusb-&gt;udev
comma
id|bfusb-&gt;bulk_out_ep
)paren
suffix:semicolon
id|usb_fill_bulk_urb
c_func
(paren
id|urb
comma
id|bfusb-&gt;udev
comma
id|pipe
comma
id|skb-&gt;data
comma
id|skb-&gt;len
comma
id|bfusb_tx_complete
comma
id|skb
)paren
suffix:semicolon
id|scb-&gt;urb
op_assign
id|urb
suffix:semicolon
id|skb_queue_tail
c_func
(paren
op_amp
id|bfusb-&gt;pending_q
comma
id|skb
)paren
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
)paren
(brace
id|BT_ERR
c_func
(paren
l_string|&quot;%s bulk tx submit failed urb %p err %d&quot;
comma
id|bfusb-&gt;hdev-&gt;name
comma
id|urb
comma
id|err
)paren
suffix:semicolon
id|skb_unlink
c_func
(paren
id|skb
)paren
suffix:semicolon
id|usb_free_urb
c_func
(paren
id|urb
)paren
suffix:semicolon
)brace
r_else
id|atomic_inc
c_func
(paren
op_amp
id|bfusb-&gt;pending_tx
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|bfusb_tx_wakeup
r_static
r_void
id|bfusb_tx_wakeup
c_func
(paren
r_struct
id|bfusb
op_star
id|bfusb
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
id|BT_DBG
c_func
(paren
l_string|&quot;bfusb %p&quot;
comma
id|bfusb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|test_and_set_bit
c_func
(paren
id|BFUSB_TX_PROCESS
comma
op_amp
id|bfusb-&gt;state
)paren
)paren
(brace
id|set_bit
c_func
(paren
id|BFUSB_TX_WAKEUP
comma
op_amp
id|bfusb-&gt;state
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_do
(brace
id|clear_bit
c_func
(paren
id|BFUSB_TX_WAKEUP
comma
op_amp
id|bfusb-&gt;state
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|atomic_read
c_func
(paren
op_amp
id|bfusb-&gt;pending_tx
)paren
OL
id|BFUSB_MAX_BULK_TX
)paren
op_logical_and
(paren
id|skb
op_assign
id|skb_dequeue
c_func
(paren
op_amp
id|bfusb-&gt;transmit_q
)paren
)paren
)paren
(brace
r_if
c_cond
(paren
id|bfusb_send_bulk
c_func
(paren
id|bfusb
comma
id|skb
)paren
OL
l_int|0
)paren
(brace
id|skb_queue_head
c_func
(paren
op_amp
id|bfusb-&gt;transmit_q
comma
id|skb
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
)brace
r_while
c_loop
(paren
id|test_bit
c_func
(paren
id|BFUSB_TX_WAKEUP
comma
op_amp
id|bfusb-&gt;state
)paren
)paren
suffix:semicolon
id|clear_bit
c_func
(paren
id|BFUSB_TX_PROCESS
comma
op_amp
id|bfusb-&gt;state
)paren
suffix:semicolon
)brace
DECL|function|bfusb_tx_complete
r_static
r_void
id|bfusb_tx_complete
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
id|sk_buff
op_star
id|skb
op_assign
(paren
r_struct
id|sk_buff
op_star
)paren
id|urb-&gt;context
suffix:semicolon
r_struct
id|bfusb
op_star
id|bfusb
op_assign
(paren
r_struct
id|bfusb
op_star
)paren
id|skb-&gt;dev
suffix:semicolon
id|BT_DBG
c_func
(paren
l_string|&quot;bfusb %p urb %p skb %p len %d&quot;
comma
id|bfusb
comma
id|urb
comma
id|skb
comma
id|skb-&gt;len
)paren
suffix:semicolon
id|atomic_dec
c_func
(paren
op_amp
id|bfusb-&gt;pending_tx
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
id|bfusb-&gt;hdev-&gt;flags
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|urb-&gt;status
)paren
id|bfusb-&gt;hdev-&gt;stat.byte_tx
op_add_assign
id|skb-&gt;len
suffix:semicolon
r_else
id|bfusb-&gt;hdev-&gt;stat.err_tx
op_increment
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|bfusb-&gt;lock
)paren
suffix:semicolon
id|skb_unlink
c_func
(paren
id|skb
)paren
suffix:semicolon
id|skb_queue_tail
c_func
(paren
op_amp
id|bfusb-&gt;completed_q
comma
id|skb
)paren
suffix:semicolon
id|bfusb_tx_wakeup
c_func
(paren
id|bfusb
)paren
suffix:semicolon
id|read_unlock
c_func
(paren
op_amp
id|bfusb-&gt;lock
)paren
suffix:semicolon
)brace
DECL|function|bfusb_rx_submit
r_static
r_int
id|bfusb_rx_submit
c_func
(paren
r_struct
id|bfusb
op_star
id|bfusb
comma
r_struct
id|urb
op_star
id|urb
)paren
(brace
r_struct
id|bfusb_scb
op_star
id|scb
suffix:semicolon
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
r_int
id|err
comma
id|pipe
comma
id|size
op_assign
id|HCI_MAX_FRAME_SIZE
op_plus
l_int|32
suffix:semicolon
id|BT_DBG
c_func
(paren
l_string|&quot;bfusb %p urb %p&quot;
comma
id|bfusb
comma
id|urb
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|urb
op_logical_and
op_logical_neg
(paren
id|urb
op_assign
id|usb_alloc_urb
c_func
(paren
l_int|0
comma
id|GFP_ATOMIC
)paren
)paren
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|skb
op_assign
id|bt_skb_alloc
c_func
(paren
id|size
comma
id|GFP_ATOMIC
)paren
)paren
)paren
(brace
id|usb_free_urb
c_func
(paren
id|urb
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
id|bfusb
suffix:semicolon
id|scb
op_assign
(paren
r_struct
id|bfusb_scb
op_star
)paren
id|skb-&gt;cb
suffix:semicolon
id|scb-&gt;urb
op_assign
id|urb
suffix:semicolon
id|pipe
op_assign
id|usb_rcvbulkpipe
c_func
(paren
id|bfusb-&gt;udev
comma
id|bfusb-&gt;bulk_in_ep
)paren
suffix:semicolon
id|usb_fill_bulk_urb
c_func
(paren
id|urb
comma
id|bfusb-&gt;udev
comma
id|pipe
comma
id|skb-&gt;data
comma
id|size
comma
id|bfusb_rx_complete
comma
id|skb
)paren
suffix:semicolon
id|skb_queue_tail
c_func
(paren
op_amp
id|bfusb-&gt;pending_q
comma
id|skb
)paren
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
)paren
(brace
id|BT_ERR
c_func
(paren
l_string|&quot;%s bulk rx submit failed urb %p err %d&quot;
comma
id|bfusb-&gt;hdev-&gt;name
comma
id|urb
comma
id|err
)paren
suffix:semicolon
id|skb_unlink
c_func
(paren
id|skb
)paren
suffix:semicolon
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
id|usb_free_urb
c_func
(paren
id|urb
)paren
suffix:semicolon
)brace
r_return
id|err
suffix:semicolon
)brace
DECL|function|bfusb_recv_block
r_static
r_inline
r_int
id|bfusb_recv_block
c_func
(paren
r_struct
id|bfusb
op_star
id|bfusb
comma
r_int
id|hdr
comma
r_int
r_char
op_star
id|data
comma
r_int
id|len
)paren
(brace
id|BT_DBG
c_func
(paren
l_string|&quot;bfusb %p hdr 0x%02x data %p len %d&quot;
comma
id|bfusb
comma
id|hdr
comma
id|data
comma
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hdr
op_amp
l_int|0x10
)paren
(brace
id|BT_ERR
c_func
(paren
l_string|&quot;%s error in block&quot;
comma
id|bfusb-&gt;hdev-&gt;name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bfusb-&gt;reassembly
)paren
id|kfree_skb
c_func
(paren
id|bfusb-&gt;reassembly
)paren
suffix:semicolon
id|bfusb-&gt;reassembly
op_assign
l_int|NULL
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
r_if
c_cond
(paren
id|hdr
op_amp
l_int|0x04
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb
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
id|bfusb-&gt;reassembly
)paren
(brace
id|BT_ERR
c_func
(paren
l_string|&quot;%s unexpected start block&quot;
comma
id|bfusb-&gt;hdev-&gt;name
)paren
suffix:semicolon
id|kfree_skb
c_func
(paren
id|bfusb-&gt;reassembly
)paren
suffix:semicolon
id|bfusb-&gt;reassembly
op_assign
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|len
OL
l_int|1
)paren
(brace
id|BT_ERR
c_func
(paren
l_string|&quot;%s no packet type found&quot;
comma
id|bfusb-&gt;hdev-&gt;name
)paren
suffix:semicolon
r_return
op_minus
id|EPROTO
suffix:semicolon
)brace
id|pkt_type
op_assign
op_star
id|data
op_increment
suffix:semicolon
id|len
op_decrement
suffix:semicolon
r_switch
c_cond
(paren
id|pkt_type
)paren
(brace
r_case
id|HCI_EVENT_PKT
suffix:colon
r_if
c_cond
(paren
id|len
op_ge
id|HCI_EVENT_HDR_SIZE
)paren
(brace
r_struct
id|hci_event_hdr
op_star
id|hdr
op_assign
(paren
r_struct
id|hci_event_hdr
op_star
)paren
id|data
suffix:semicolon
id|pkt_len
op_assign
id|HCI_EVENT_HDR_SIZE
op_plus
id|hdr-&gt;plen
suffix:semicolon
)brace
r_else
(brace
id|BT_ERR
c_func
(paren
l_string|&quot;%s event block is too short&quot;
comma
id|bfusb-&gt;hdev-&gt;name
)paren
suffix:semicolon
r_return
op_minus
id|EILSEQ
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|HCI_ACLDATA_PKT
suffix:colon
r_if
c_cond
(paren
id|len
op_ge
id|HCI_ACL_HDR_SIZE
)paren
(brace
r_struct
id|hci_acl_hdr
op_star
id|hdr
op_assign
(paren
r_struct
id|hci_acl_hdr
op_star
)paren
id|data
suffix:semicolon
id|pkt_len
op_assign
id|HCI_ACL_HDR_SIZE
op_plus
id|__le16_to_cpu
c_func
(paren
id|hdr-&gt;dlen
)paren
suffix:semicolon
)brace
r_else
(brace
id|BT_ERR
c_func
(paren
l_string|&quot;%s data block is too short&quot;
comma
id|bfusb-&gt;hdev-&gt;name
)paren
suffix:semicolon
r_return
op_minus
id|EILSEQ
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|HCI_SCODATA_PKT
suffix:colon
r_if
c_cond
(paren
id|len
op_ge
id|HCI_SCO_HDR_SIZE
)paren
(brace
r_struct
id|hci_sco_hdr
op_star
id|hdr
op_assign
(paren
r_struct
id|hci_sco_hdr
op_star
)paren
id|data
suffix:semicolon
id|pkt_len
op_assign
id|HCI_SCO_HDR_SIZE
op_plus
id|hdr-&gt;dlen
suffix:semicolon
)brace
r_else
(brace
id|BT_ERR
c_func
(paren
l_string|&quot;%s audio block is too short&quot;
comma
id|bfusb-&gt;hdev-&gt;name
)paren
suffix:semicolon
r_return
op_minus
id|EILSEQ
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
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
l_string|&quot;%s no memory for the packet&quot;
comma
id|bfusb-&gt;hdev-&gt;name
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
id|bfusb-&gt;hdev
suffix:semicolon
id|skb-&gt;pkt_type
op_assign
id|pkt_type
suffix:semicolon
id|bfusb-&gt;reassembly
op_assign
id|skb
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
op_logical_neg
id|bfusb-&gt;reassembly
)paren
(brace
id|BT_ERR
c_func
(paren
l_string|&quot;%s unexpected continuation block&quot;
comma
id|bfusb-&gt;hdev-&gt;name
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|len
OG
l_int|0
)paren
id|memcpy
c_func
(paren
id|skb_put
c_func
(paren
id|bfusb-&gt;reassembly
comma
id|len
)paren
comma
id|data
comma
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hdr
op_amp
l_int|0x08
)paren
(brace
id|hci_recv_frame
c_func
(paren
id|bfusb-&gt;reassembly
)paren
suffix:semicolon
id|bfusb-&gt;reassembly
op_assign
l_int|NULL
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|bfusb_rx_complete
r_static
r_void
id|bfusb_rx_complete
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
id|sk_buff
op_star
id|skb
op_assign
(paren
r_struct
id|sk_buff
op_star
)paren
id|urb-&gt;context
suffix:semicolon
r_struct
id|bfusb
op_star
id|bfusb
op_assign
(paren
r_struct
id|bfusb
op_star
)paren
id|skb-&gt;dev
suffix:semicolon
r_int
r_char
op_star
id|buf
op_assign
id|urb-&gt;transfer_buffer
suffix:semicolon
r_int
id|count
op_assign
id|urb-&gt;actual_length
suffix:semicolon
r_int
id|err
comma
id|hdr
comma
id|len
suffix:semicolon
id|BT_DBG
c_func
(paren
l_string|&quot;bfusb %p urb %p skb %p len %d&quot;
comma
id|bfusb
comma
id|urb
comma
id|skb
comma
id|skb-&gt;len
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
id|bfusb-&gt;hdev-&gt;flags
)paren
)paren
r_return
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|bfusb-&gt;lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|urb-&gt;status
op_logical_or
op_logical_neg
id|count
)paren
r_goto
id|resubmit
suffix:semicolon
id|bfusb-&gt;hdev-&gt;stat.byte_rx
op_add_assign
id|count
suffix:semicolon
id|skb_put
c_func
(paren
id|skb
comma
id|count
)paren
suffix:semicolon
r_while
c_loop
(paren
id|count
)paren
(brace
id|hdr
op_assign
id|buf
(braket
l_int|0
)braket
op_or
(paren
id|buf
(braket
l_int|1
)braket
op_lshift
l_int|8
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hdr
op_amp
l_int|0x4000
)paren
(brace
id|len
op_assign
l_int|0
suffix:semicolon
id|count
op_sub_assign
l_int|2
suffix:semicolon
id|buf
op_add_assign
l_int|2
suffix:semicolon
)brace
r_else
(brace
id|len
op_assign
(paren
id|buf
(braket
l_int|2
)braket
op_eq
l_int|0
)paren
ques
c_cond
l_int|256
suffix:colon
id|buf
(braket
l_int|2
)braket
suffix:semicolon
id|count
op_sub_assign
l_int|3
suffix:semicolon
id|buf
op_add_assign
l_int|3
suffix:semicolon
)brace
r_if
c_cond
(paren
id|count
OL
id|len
)paren
(brace
id|BT_ERR
c_func
(paren
l_string|&quot;%s block extends over URB buffer ranges&quot;
comma
id|bfusb-&gt;hdev-&gt;name
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|hdr
op_amp
l_int|0xe1
)paren
op_eq
l_int|0xc1
)paren
id|bfusb_recv_block
c_func
(paren
id|bfusb
comma
id|hdr
comma
id|buf
comma
id|len
)paren
suffix:semicolon
id|count
op_sub_assign
id|len
suffix:semicolon
id|buf
op_add_assign
id|len
suffix:semicolon
)brace
id|skb_unlink
c_func
(paren
id|skb
)paren
suffix:semicolon
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
id|bfusb_rx_submit
c_func
(paren
id|bfusb
comma
id|urb
)paren
suffix:semicolon
id|read_unlock
c_func
(paren
op_amp
id|bfusb-&gt;lock
)paren
suffix:semicolon
r_return
suffix:semicolon
id|resubmit
suffix:colon
id|urb-&gt;dev
op_assign
id|bfusb-&gt;udev
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
)paren
(brace
id|BT_ERR
c_func
(paren
l_string|&quot;%s bulk resubmit failed urb %p err %d&quot;
comma
id|bfusb-&gt;hdev-&gt;name
comma
id|urb
comma
id|err
)paren
suffix:semicolon
)brace
id|read_unlock
c_func
(paren
op_amp
id|bfusb-&gt;lock
)paren
suffix:semicolon
)brace
DECL|function|bfusb_open
r_static
r_int
id|bfusb_open
c_func
(paren
r_struct
id|hci_dev
op_star
id|hdev
)paren
(brace
r_struct
id|bfusb
op_star
id|bfusb
op_assign
(paren
r_struct
id|bfusb
op_star
)paren
id|hdev-&gt;driver_data
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
id|i
comma
id|err
suffix:semicolon
id|BT_DBG
c_func
(paren
l_string|&quot;hdev %p bfusb %p&quot;
comma
id|hdev
comma
id|bfusb
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
id|write_lock_irqsave
c_func
(paren
op_amp
id|bfusb-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|err
op_assign
id|bfusb_rx_submit
c_func
(paren
id|bfusb
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|err
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
OL
id|BFUSB_MAX_BULK_RX
suffix:semicolon
id|i
op_increment
)paren
id|bfusb_rx_submit
c_func
(paren
id|bfusb
comma
l_int|NULL
)paren
suffix:semicolon
)brace
r_else
(brace
id|clear_bit
c_func
(paren
id|HCI_RUNNING
comma
op_amp
id|hdev-&gt;flags
)paren
suffix:semicolon
)brace
id|write_unlock_irqrestore
c_func
(paren
op_amp
id|bfusb-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|bfusb_flush
r_static
r_int
id|bfusb_flush
c_func
(paren
r_struct
id|hci_dev
op_star
id|hdev
)paren
(brace
r_struct
id|bfusb
op_star
id|bfusb
op_assign
(paren
r_struct
id|bfusb
op_star
)paren
id|hdev-&gt;driver_data
suffix:semicolon
id|BT_DBG
c_func
(paren
l_string|&quot;hdev %p bfusb %p&quot;
comma
id|hdev
comma
id|bfusb
)paren
suffix:semicolon
id|skb_queue_purge
c_func
(paren
op_amp
id|bfusb-&gt;transmit_q
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|bfusb_close
r_static
r_int
id|bfusb_close
c_func
(paren
r_struct
id|hci_dev
op_star
id|hdev
)paren
(brace
r_struct
id|bfusb
op_star
id|bfusb
op_assign
(paren
r_struct
id|bfusb
op_star
)paren
id|hdev-&gt;driver_data
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|BT_DBG
c_func
(paren
l_string|&quot;hdev %p bfusb %p&quot;
comma
id|hdev
comma
id|bfusb
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
id|bfusb-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|write_unlock_irqrestore
c_func
(paren
op_amp
id|bfusb-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|bfusb_unlink_urbs
c_func
(paren
id|bfusb
)paren
suffix:semicolon
id|bfusb_flush
c_func
(paren
id|hdev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|bfusb_send_frame
r_static
r_int
id|bfusb_send_frame
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
id|bfusb
op_star
id|bfusb
suffix:semicolon
r_struct
id|sk_buff
op_star
id|nskb
suffix:semicolon
r_int
r_char
id|buf
(braket
l_int|3
)braket
suffix:semicolon
r_int
id|sent
op_assign
l_int|0
comma
id|size
comma
id|count
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
l_string|&quot;Frame for unknown HCI device (hdev=NULL)&quot;
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
id|bfusb
op_assign
(paren
r_struct
id|bfusb
op_star
)paren
id|hdev-&gt;driver_data
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
r_break
suffix:semicolon
r_case
id|HCI_ACLDATA_PKT
suffix:colon
id|hdev-&gt;stat.acl_tx
op_increment
suffix:semicolon
r_break
suffix:semicolon
r_case
id|HCI_SCODATA_PKT
suffix:colon
id|hdev-&gt;stat.sco_tx
op_increment
suffix:semicolon
r_break
suffix:semicolon
)brace
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
id|count
op_assign
id|skb-&gt;len
suffix:semicolon
multiline_comment|/* Max HCI frame size seems to be 1511 + 1 */
r_if
c_cond
(paren
op_logical_neg
(paren
id|nskb
op_assign
id|bt_skb_alloc
c_func
(paren
id|count
op_plus
l_int|32
comma
id|GFP_ATOMIC
)paren
)paren
)paren
(brace
id|BT_ERR
c_func
(paren
l_string|&quot;Can&squot;t allocate memory for new packet&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|nskb-&gt;dev
op_assign
(paren
r_void
op_star
)paren
id|bfusb
suffix:semicolon
r_while
c_loop
(paren
id|count
)paren
(brace
id|size
op_assign
id|min_t
c_func
(paren
id|uint
comma
id|count
comma
id|BFUSB_MAX_BLOCK_SIZE
)paren
suffix:semicolon
id|buf
(braket
l_int|0
)braket
op_assign
l_int|0xc1
op_or
(paren
(paren
id|sent
op_eq
l_int|0
)paren
ques
c_cond
l_int|0x04
suffix:colon
l_int|0
)paren
op_or
(paren
(paren
id|count
op_eq
id|size
)paren
ques
c_cond
l_int|0x08
suffix:colon
l_int|0
)paren
suffix:semicolon
id|buf
(braket
l_int|1
)braket
op_assign
l_int|0x00
suffix:semicolon
id|buf
(braket
l_int|2
)braket
op_assign
(paren
id|size
op_eq
id|BFUSB_MAX_BLOCK_SIZE
)paren
ques
c_cond
l_int|0
suffix:colon
id|size
suffix:semicolon
id|memcpy
c_func
(paren
id|skb_put
c_func
(paren
id|nskb
comma
l_int|3
)paren
comma
id|buf
comma
l_int|3
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|skb_put
c_func
(paren
id|nskb
comma
id|size
)paren
comma
id|skb-&gt;data
op_plus
id|sent
comma
id|size
)paren
suffix:semicolon
id|sent
op_add_assign
id|size
suffix:semicolon
id|count
op_sub_assign
id|size
suffix:semicolon
)brace
multiline_comment|/* Don&squot;t send frame with multiple size of bulk max packet */
r_if
c_cond
(paren
(paren
id|nskb-&gt;len
op_mod
id|bfusb-&gt;bulk_pkt_size
)paren
op_eq
l_int|0
)paren
(brace
id|buf
(braket
l_int|0
)braket
op_assign
l_int|0xdd
suffix:semicolon
id|buf
(braket
l_int|1
)braket
op_assign
l_int|0x00
suffix:semicolon
id|memcpy
c_func
(paren
id|skb_put
c_func
(paren
id|nskb
comma
l_int|2
)paren
comma
id|buf
comma
l_int|2
)paren
suffix:semicolon
)brace
id|read_lock
c_func
(paren
op_amp
id|bfusb-&gt;lock
)paren
suffix:semicolon
id|skb_queue_tail
c_func
(paren
op_amp
id|bfusb-&gt;transmit_q
comma
id|nskb
)paren
suffix:semicolon
id|bfusb_tx_wakeup
c_func
(paren
id|bfusb
)paren
suffix:semicolon
id|read_unlock
c_func
(paren
op_amp
id|bfusb-&gt;lock
)paren
suffix:semicolon
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|bfusb_destruct
r_static
r_void
id|bfusb_destruct
c_func
(paren
r_struct
id|hci_dev
op_star
id|hdev
)paren
(brace
r_struct
id|bfusb
op_star
id|bfusb
op_assign
(paren
r_struct
id|bfusb
op_star
)paren
id|hdev-&gt;driver_data
suffix:semicolon
id|BT_DBG
c_func
(paren
l_string|&quot;hdev %p bfusb %p&quot;
comma
id|hdev
comma
id|bfusb
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|bfusb
)paren
suffix:semicolon
)brace
DECL|function|bfusb_ioctl
r_static
r_int
id|bfusb_ioctl
c_func
(paren
r_struct
id|hci_dev
op_star
id|hdev
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
(brace
r_return
op_minus
id|ENOIOCTLCMD
suffix:semicolon
)brace
DECL|function|bfusb_load_firmware
r_static
r_int
id|bfusb_load_firmware
c_func
(paren
r_struct
id|bfusb
op_star
id|bfusb
comma
r_int
r_char
op_star
id|firmware
comma
r_int
id|count
)paren
(brace
r_int
r_char
op_star
id|buf
suffix:semicolon
r_int
id|err
comma
id|pipe
comma
id|len
comma
id|size
comma
id|sent
op_assign
l_int|0
suffix:semicolon
id|BT_DBG
c_func
(paren
l_string|&quot;bfusb %p udev %p&quot;
comma
id|bfusb
comma
id|bfusb-&gt;udev
)paren
suffix:semicolon
id|BT_INFO
c_func
(paren
l_string|&quot;BlueFRITZ! USB loading firmware&quot;
)paren
suffix:semicolon
id|pipe
op_assign
id|usb_sndctrlpipe
c_func
(paren
id|bfusb-&gt;udev
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|usb_control_msg
c_func
(paren
id|bfusb-&gt;udev
comma
id|pipe
comma
id|USB_REQ_SET_CONFIGURATION
comma
l_int|0
comma
l_int|1
comma
l_int|0
comma
l_int|NULL
comma
l_int|0
comma
id|HZ
op_star
id|USB_CTRL_SET_TIMEOUT
)paren
OL
l_int|0
)paren
(brace
id|BT_ERR
c_func
(paren
l_string|&quot;Can&squot;t change to loading configuration&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|buf
op_assign
id|kmalloc
c_func
(paren
id|BFUSB_MAX_BLOCK_SIZE
op_plus
l_int|3
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|buf
)paren
(brace
id|BT_ERR
c_func
(paren
l_string|&quot;Can&squot;t allocate memory chunk for firmware&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|pipe
op_assign
id|usb_sndbulkpipe
c_func
(paren
id|bfusb-&gt;udev
comma
id|bfusb-&gt;bulk_out_ep
)paren
suffix:semicolon
r_while
c_loop
(paren
id|count
)paren
(brace
id|size
op_assign
id|min_t
c_func
(paren
id|uint
comma
id|count
comma
id|BFUSB_MAX_BLOCK_SIZE
op_plus
l_int|3
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|buf
comma
id|firmware
op_plus
id|sent
comma
id|size
)paren
suffix:semicolon
id|err
op_assign
id|usb_bulk_msg
c_func
(paren
id|bfusb-&gt;udev
comma
id|pipe
comma
id|buf
comma
id|size
comma
op_amp
id|len
comma
id|BFUSB_BLOCK_TIMEOUT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
op_logical_or
(paren
id|len
op_ne
id|size
)paren
)paren
(brace
id|BT_ERR
c_func
(paren
l_string|&quot;Error in firmware loading&quot;
)paren
suffix:semicolon
r_goto
id|error
suffix:semicolon
)brace
id|sent
op_add_assign
id|size
suffix:semicolon
id|count
op_sub_assign
id|size
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|err
op_assign
id|usb_bulk_msg
c_func
(paren
id|bfusb-&gt;udev
comma
id|pipe
comma
l_int|NULL
comma
l_int|0
comma
op_amp
id|len
comma
id|BFUSB_BLOCK_TIMEOUT
)paren
)paren
OL
l_int|0
)paren
(brace
id|BT_ERR
c_func
(paren
l_string|&quot;Error in null packet request&quot;
)paren
suffix:semicolon
r_goto
id|error
suffix:semicolon
)brace
id|pipe
op_assign
id|usb_sndctrlpipe
c_func
(paren
id|bfusb-&gt;udev
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|usb_control_msg
c_func
(paren
id|bfusb-&gt;udev
comma
id|pipe
comma
id|USB_REQ_SET_CONFIGURATION
comma
l_int|0
comma
l_int|2
comma
l_int|0
comma
l_int|NULL
comma
l_int|0
comma
id|HZ
op_star
id|USB_CTRL_SET_TIMEOUT
)paren
)paren
OL
l_int|0
)paren
(brace
id|BT_ERR
c_func
(paren
l_string|&quot;Can&squot;t change to running configuration&quot;
)paren
suffix:semicolon
r_goto
id|error
suffix:semicolon
)brace
id|BT_INFO
c_func
(paren
l_string|&quot;BlueFRITZ! USB device ready&quot;
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|buf
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|error
suffix:colon
id|kfree
c_func
(paren
id|buf
)paren
suffix:semicolon
id|pipe
op_assign
id|usb_sndctrlpipe
c_func
(paren
id|bfusb-&gt;udev
comma
l_int|0
)paren
suffix:semicolon
id|usb_control_msg
c_func
(paren
id|bfusb-&gt;udev
comma
id|pipe
comma
id|USB_REQ_SET_CONFIGURATION
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|NULL
comma
l_int|0
comma
id|HZ
op_star
id|USB_CTRL_SET_TIMEOUT
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|bfusb_probe
r_static
r_int
id|bfusb_probe
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
r_const
r_struct
id|firmware
op_star
id|firmware
suffix:semicolon
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
id|usb_host_endpoint
op_star
id|bulk_out_ep
suffix:semicolon
r_struct
id|usb_host_endpoint
op_star
id|bulk_in_ep
suffix:semicolon
r_struct
id|hci_dev
op_star
id|hdev
suffix:semicolon
r_struct
id|bfusb
op_star
id|bfusb
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
multiline_comment|/* Check number of endpoints */
r_if
c_cond
(paren
id|intf-&gt;altsetting
(braket
l_int|0
)braket
dot
id|desc.bNumEndpoints
OL
l_int|2
)paren
r_return
op_minus
id|EIO
suffix:semicolon
id|bulk_out_ep
op_assign
op_amp
id|intf-&gt;altsetting
(braket
l_int|0
)braket
dot
id|endpoint
(braket
l_int|0
)braket
suffix:semicolon
id|bulk_in_ep
op_assign
op_amp
id|intf-&gt;altsetting
(braket
l_int|0
)braket
dot
id|endpoint
(braket
l_int|1
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bulk_out_ep
op_logical_or
op_logical_neg
id|bulk_in_ep
)paren
(brace
id|BT_ERR
c_func
(paren
l_string|&quot;Bulk endpoints not found&quot;
)paren
suffix:semicolon
r_goto
id|done
suffix:semicolon
)brace
multiline_comment|/* Initialize control structure and load firmware */
r_if
c_cond
(paren
op_logical_neg
(paren
id|bfusb
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|bfusb
)paren
comma
id|GFP_KERNEL
)paren
)paren
)paren
(brace
id|BT_ERR
c_func
(paren
l_string|&quot;Can&squot;t allocate memory for control structure&quot;
)paren
suffix:semicolon
r_goto
id|done
suffix:semicolon
)brace
id|memset
c_func
(paren
id|bfusb
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|bfusb
)paren
)paren
suffix:semicolon
id|bfusb-&gt;udev
op_assign
id|udev
suffix:semicolon
id|bfusb-&gt;bulk_in_ep
op_assign
id|bulk_in_ep-&gt;desc.bEndpointAddress
suffix:semicolon
id|bfusb-&gt;bulk_out_ep
op_assign
id|bulk_out_ep-&gt;desc.bEndpointAddress
suffix:semicolon
id|bfusb-&gt;bulk_pkt_size
op_assign
id|bulk_out_ep-&gt;desc.wMaxPacketSize
suffix:semicolon
id|bfusb-&gt;lock
op_assign
id|RW_LOCK_UNLOCKED
suffix:semicolon
id|bfusb-&gt;reassembly
op_assign
l_int|NULL
suffix:semicolon
id|skb_queue_head_init
c_func
(paren
op_amp
id|bfusb-&gt;transmit_q
)paren
suffix:semicolon
id|skb_queue_head_init
c_func
(paren
op_amp
id|bfusb-&gt;pending_q
)paren
suffix:semicolon
id|skb_queue_head_init
c_func
(paren
op_amp
id|bfusb-&gt;completed_q
)paren
suffix:semicolon
r_if
c_cond
(paren
id|request_firmware
c_func
(paren
op_amp
id|firmware
comma
l_string|&quot;bfubase.frm&quot;
comma
op_amp
id|udev-&gt;dev
)paren
OL
l_int|0
)paren
(brace
id|BT_ERR
c_func
(paren
l_string|&quot;Firmware request failed&quot;
)paren
suffix:semicolon
r_goto
id|error
suffix:semicolon
)brace
id|BT_DBG
c_func
(paren
l_string|&quot;firmware data %p size %d&quot;
comma
id|firmware-&gt;data
comma
id|firmware-&gt;size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bfusb_load_firmware
c_func
(paren
id|bfusb
comma
id|firmware-&gt;data
comma
id|firmware-&gt;size
)paren
OL
l_int|0
)paren
(brace
id|BT_ERR
c_func
(paren
l_string|&quot;Firmware loading failed&quot;
)paren
suffix:semicolon
r_goto
id|release
suffix:semicolon
)brace
id|release_firmware
c_func
(paren
id|firmware
)paren
suffix:semicolon
multiline_comment|/* Initialize and register HCI device */
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
r_goto
id|error
suffix:semicolon
)brace
id|bfusb-&gt;hdev
op_assign
id|hdev
suffix:semicolon
id|hdev-&gt;type
op_assign
id|HCI_USB
suffix:semicolon
id|hdev-&gt;driver_data
op_assign
id|bfusb
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
id|bfusb_open
suffix:semicolon
id|hdev-&gt;close
op_assign
id|bfusb_close
suffix:semicolon
id|hdev-&gt;flush
op_assign
id|bfusb_flush
suffix:semicolon
id|hdev-&gt;send
op_assign
id|bfusb_send_frame
suffix:semicolon
id|hdev-&gt;destruct
op_assign
id|bfusb_destruct
suffix:semicolon
id|hdev-&gt;ioctl
op_assign
id|bfusb_ioctl
suffix:semicolon
id|hdev-&gt;owner
op_assign
id|THIS_MODULE
suffix:semicolon
r_if
c_cond
(paren
id|hci_register_dev
c_func
(paren
id|hdev
)paren
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
id|hci_free_dev
c_func
(paren
id|hdev
)paren
suffix:semicolon
r_goto
id|error
suffix:semicolon
)brace
id|usb_set_intfdata
c_func
(paren
id|intf
comma
id|bfusb
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|release
suffix:colon
id|release_firmware
c_func
(paren
id|firmware
)paren
suffix:semicolon
id|error
suffix:colon
id|kfree
c_func
(paren
id|bfusb
)paren
suffix:semicolon
id|done
suffix:colon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
DECL|function|bfusb_disconnect
r_static
r_void
id|bfusb_disconnect
c_func
(paren
r_struct
id|usb_interface
op_star
id|intf
)paren
(brace
r_struct
id|bfusb
op_star
id|bfusb
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
id|bfusb-&gt;hdev
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
id|bfusb_close
c_func
(paren
id|hdev
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
DECL|variable|bfusb_driver
r_static
r_struct
id|usb_driver
id|bfusb_driver
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
l_string|&quot;bfusb&quot;
comma
dot
id|probe
op_assign
id|bfusb_probe
comma
dot
id|disconnect
op_assign
id|bfusb_disconnect
comma
dot
id|id_table
op_assign
id|bfusb_table
comma
)brace
suffix:semicolon
DECL|function|bfusb_init
r_static
r_int
id|__init
id|bfusb_init
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
l_string|&quot;BlueFRITZ! USB driver ver %s&quot;
comma
id|VERSION
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|usb_register
c_func
(paren
op_amp
id|bfusb_driver
)paren
)paren
OL
l_int|0
)paren
id|BT_ERR
c_func
(paren
l_string|&quot;Failed to register BlueFRITZ! USB driver&quot;
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|bfusb_cleanup
r_static
r_void
id|__exit
id|bfusb_cleanup
c_func
(paren
r_void
)paren
(brace
id|usb_deregister
c_func
(paren
op_amp
id|bfusb_driver
)paren
suffix:semicolon
)brace
DECL|variable|bfusb_init
id|module_init
c_func
(paren
id|bfusb_init
)paren
suffix:semicolon
DECL|variable|bfusb_cleanup
id|module_exit
c_func
(paren
id|bfusb_cleanup
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
l_string|&quot;BlueFRITZ! USB driver ver &quot;
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
