multiline_comment|/* &n;   HCI USB driver for Linux Bluetooth protocol stack (BlueZ)&n;   Copyright (C) 2000-2001 Qualcomm Incorporated&n;   Written 2000,2001 by Maxim Krasnyansky &lt;maxk@qualcomm.com&gt;&n;&n;   Copyright (C) 2003 Maxim Krasnyansky &lt;maxk@qualcomm.com&gt;&n;&n;   This program is free software; you can redistribute it and/or modify&n;   it under the terms of the GNU General Public License version 2 as&n;   published by the Free Software Foundation;&n;&n;   THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND, EXPRESS&n;   OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,&n;   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT OF THIRD PARTY RIGHTS.&n;   IN NO EVENT SHALL THE COPYRIGHT HOLDER(S) AND AUTHOR(S) BE LIABLE FOR ANY&n;   CLAIM, OR ANY SPECIAL INDIRECT OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES &n;   WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN &n;   ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF &n;   OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.&n;&n;   ALL LIABILITY, INCLUDING LIABILITY FOR INFRINGEMENT OF ANY PATENTS, &n;   COPYRIGHTS, TRADEMARKS OR OTHER RIGHTS, RELATING TO USE OF THIS &n;   SOFTWARE IS DISCLAIMED.&n;*/
multiline_comment|/* Class, SubClass, and Protocol codes that describe a Bluetooth device */
DECL|macro|HCI_DEV_CLASS
mdefine_line|#define HCI_DEV_CLASS&t;&t;0xe0&t;/* Wireless class */
DECL|macro|HCI_DEV_SUBCLASS
mdefine_line|#define HCI_DEV_SUBCLASS&t;0x01&t;/* RF subclass */
DECL|macro|HCI_DEV_PROTOCOL
mdefine_line|#define HCI_DEV_PROTOCOL&t;0x01&t;/* Bluetooth programming protocol */
DECL|macro|HCI_IGNORE
mdefine_line|#define HCI_IGNORE&t;&t;0x01
DECL|macro|HCI_RESET
mdefine_line|#define HCI_RESET&t;&t;0x02
DECL|macro|HCI_DIGIANSWER
mdefine_line|#define HCI_DIGIANSWER&t;&t;0x04
DECL|macro|HCI_SNIFFER
mdefine_line|#define HCI_SNIFFER&t;&t;0x08
DECL|macro|HCI_BROKEN_ISOC
mdefine_line|#define HCI_BROKEN_ISOC&t;&t;0x10
DECL|macro|HCI_BCM92035
mdefine_line|#define HCI_BCM92035&t;&t;0x20
DECL|macro|HCI_MAX_IFACE_NUM
mdefine_line|#define HCI_MAX_IFACE_NUM&t;3
DECL|macro|HCI_MAX_BULK_TX
mdefine_line|#define HCI_MAX_BULK_TX&t;&t;4
DECL|macro|HCI_MAX_BULK_RX
mdefine_line|#define HCI_MAX_BULK_RX&t;&t;1
DECL|macro|HCI_MAX_ISOC_RX
mdefine_line|#define HCI_MAX_ISOC_RX&t;&t;2
DECL|macro|HCI_MAX_ISOC_TX
mdefine_line|#define HCI_MAX_ISOC_TX&t;&t;2
DECL|macro|HCI_MAX_ISOC_FRAMES
mdefine_line|#define HCI_MAX_ISOC_FRAMES&t;10
DECL|struct|_urb_queue
r_struct
id|_urb_queue
(brace
DECL|member|head
r_struct
id|list_head
id|head
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|_urb
r_struct
id|_urb
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|queue
r_struct
id|_urb_queue
op_star
id|queue
suffix:semicolon
DECL|member|type
r_int
id|type
suffix:semicolon
DECL|member|priv
r_void
op_star
id|priv
suffix:semicolon
DECL|member|urb
r_struct
id|urb
id|urb
suffix:semicolon
)brace
suffix:semicolon
DECL|function|_urb_free
r_static
r_inline
r_void
id|_urb_free
c_func
(paren
r_struct
id|_urb
op_star
id|_urb
)paren
(brace
id|kfree
c_func
(paren
id|_urb
)paren
suffix:semicolon
)brace
DECL|function|_urb_queue_init
r_static
r_inline
r_void
id|_urb_queue_init
c_func
(paren
r_struct
id|_urb_queue
op_star
id|q
)paren
(brace
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|q-&gt;head
)paren
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|q-&gt;lock
)paren
suffix:semicolon
)brace
DECL|function|_urb_queue_head
r_static
r_inline
r_void
id|_urb_queue_head
c_func
(paren
r_struct
id|_urb_queue
op_star
id|q
comma
r_struct
id|_urb
op_star
id|_urb
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|q-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|list_add
c_func
(paren
op_amp
id|_urb-&gt;list
comma
op_amp
id|q-&gt;head
)paren
suffix:semicolon
id|_urb-&gt;queue
op_assign
id|q
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|q-&gt;lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|_urb_queue_tail
r_static
r_inline
r_void
id|_urb_queue_tail
c_func
(paren
r_struct
id|_urb_queue
op_star
id|q
comma
r_struct
id|_urb
op_star
id|_urb
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|q-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|list_add_tail
c_func
(paren
op_amp
id|_urb-&gt;list
comma
op_amp
id|q-&gt;head
)paren
suffix:semicolon
id|_urb-&gt;queue
op_assign
id|q
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|q-&gt;lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|_urb_unlink
r_static
r_inline
r_void
id|_urb_unlink
c_func
(paren
r_struct
id|_urb
op_star
id|_urb
)paren
(brace
r_struct
id|_urb_queue
op_star
id|q
op_assign
id|_urb-&gt;queue
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
id|q
)paren
(brace
id|spin_lock_irqsave
c_func
(paren
op_amp
id|q-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|_urb-&gt;list
)paren
suffix:semicolon
id|_urb-&gt;queue
op_assign
l_int|NULL
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|q-&gt;lock
comma
id|flags
)paren
suffix:semicolon
)brace
)brace
DECL|struct|hci_usb
r_struct
id|hci_usb
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
r_struct
id|usb_host_endpoint
op_star
id|bulk_in_ep
suffix:semicolon
DECL|member|bulk_out_ep
r_struct
id|usb_host_endpoint
op_star
id|bulk_out_ep
suffix:semicolon
DECL|member|intr_in_ep
r_struct
id|usb_host_endpoint
op_star
id|intr_in_ep
suffix:semicolon
DECL|member|isoc_iface
r_struct
id|usb_interface
op_star
id|isoc_iface
suffix:semicolon
DECL|member|isoc_out_ep
r_struct
id|usb_host_endpoint
op_star
id|isoc_out_ep
suffix:semicolon
DECL|member|isoc_in_ep
r_struct
id|usb_host_endpoint
op_star
id|isoc_in_ep
suffix:semicolon
DECL|member|ctrl_req
id|__u8
id|ctrl_req
suffix:semicolon
DECL|member|transmit_q
r_struct
id|sk_buff_head
id|transmit_q
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|reassembly
r_struct
id|sk_buff
op_star
id|reassembly
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* Reassembly buffers */
DECL|member|completion_lock
id|rwlock_t
id|completion_lock
suffix:semicolon
DECL|member|pending_tx
id|atomic_t
id|pending_tx
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* Number of pending requests */
DECL|member|pending_q
r_struct
id|_urb_queue
id|pending_q
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* Pending requests */
DECL|member|completed_q
r_struct
id|_urb_queue
id|completed_q
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* Completed requests */
)brace
suffix:semicolon
multiline_comment|/* States  */
DECL|macro|HCI_USB_TX_PROCESS
mdefine_line|#define HCI_USB_TX_PROCESS&t;1
DECL|macro|HCI_USB_TX_WAKEUP
mdefine_line|#define HCI_USB_TX_WAKEUP&t;2
eof
