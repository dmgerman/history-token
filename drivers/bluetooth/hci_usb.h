multiline_comment|/* &n;   BlueZ - Bluetooth protocol stack for Linux&n;   Copyright (C) 2000-2001 Qualcomm Incorporated&n;&n;   Written 2000,2001 by Maxim Krasnyansky &lt;maxk@qualcomm.com&gt;&n;&n;   This program is free software; you can redistribute it and/or modify&n;   it under the terms of the GNU General Public License version 2 as&n;   published by the Free Software Foundation;&n;&n;   THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND, EXPRESS&n;   OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,&n;   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT OF THIRD PARTY RIGHTS.&n;   IN NO EVENT SHALL THE COPYRIGHT HOLDER(S) AND AUTHOR(S) BE LIABLE FOR ANY&n;   CLAIM, OR ANY SPECIAL INDIRECT OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES &n;   WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN &n;   ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF &n;   OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.&n;&n;   ALL LIABILITY, INCLUDING LIABILITY FOR INFRINGEMENT OF ANY PATENTS, &n;   COPYRIGHTS, TRADEMARKS OR OTHER RIGHTS, RELATING TO USE OF THIS &n;   SOFTWARE IS DISCLAIMED.&n;*/
multiline_comment|/*&n; * $Id: hci_usb.h,v 1.2 2002/03/18 19:10:04 maxk Exp $&n; */
macro_line|#ifdef __KERNEL__
multiline_comment|/* Class, SubClass, and Protocol codes that describe a Bluetooth device */
DECL|macro|HCI_DEV_CLASS
mdefine_line|#define HCI_DEV_CLASS        0xe0&t;/* Wireless class */
DECL|macro|HCI_DEV_SUBCLASS
mdefine_line|#define HCI_DEV_SUBCLASS     0x01&t;/* RF subclass */
DECL|macro|HCI_DEV_PROTOCOL
mdefine_line|#define HCI_DEV_PROTOCOL     0x01&t;/* Bluetooth programming protocol */
DECL|macro|HCI_CTRL_REQ
mdefine_line|#define HCI_CTRL_REQ&t;     0x20
DECL|macro|HCI_MAX_IFACE_NUM
mdefine_line|#define HCI_MAX_IFACE_NUM&t;3 
DECL|macro|HCI_MAX_BULK_TX
mdefine_line|#define HCI_MAX_BULK_TX     &t;4
DECL|macro|HCI_MAX_BULK_RX
mdefine_line|#define HCI_MAX_BULK_RX     &t;1
DECL|struct|hci_usb
r_struct
id|hci_usb
(brace
DECL|member|hdev
r_struct
id|hci_dev
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
DECL|member|isoc_iface
r_struct
id|usb_interface
op_star
id|isoc_iface
suffix:semicolon
DECL|member|bulk_out_ep
id|__u8
id|bulk_out_ep
suffix:semicolon
DECL|member|bulk_in_ep
id|__u8
id|bulk_in_ep
suffix:semicolon
DECL|member|isoc_out_ep
id|__u8
id|isoc_out_ep
suffix:semicolon
DECL|member|isoc_in_ep
id|__u8
id|isoc_in_ep
suffix:semicolon
DECL|member|intr_ep
id|__u8
id|intr_ep
suffix:semicolon
DECL|member|intr_interval
id|__u8
id|intr_interval
suffix:semicolon
DECL|member|intr_urb
r_struct
id|urb
op_star
id|intr_urb
suffix:semicolon
DECL|member|intr_skb
r_struct
id|sk_buff
op_star
id|intr_skb
suffix:semicolon
DECL|member|completion_lock
id|rwlock_t
id|completion_lock
suffix:semicolon
DECL|member|cmd_q
r_struct
id|sk_buff_head
id|cmd_q
suffix:semicolon
singleline_comment|// TX Commands
DECL|member|acl_q
r_struct
id|sk_buff_head
id|acl_q
suffix:semicolon
singleline_comment|// TX ACLs
DECL|member|pending_q
r_struct
id|sk_buff_head
id|pending_q
suffix:semicolon
singleline_comment|// Pending requests
DECL|member|completed_q
r_struct
id|sk_buff_head
id|completed_q
suffix:semicolon
singleline_comment|// Completed requests
)brace
suffix:semicolon
DECL|struct|hci_usb_scb
r_struct
id|hci_usb_scb
(brace
DECL|member|urb
r_struct
id|urb
op_star
id|urb
suffix:semicolon
DECL|member|intr_len
r_int
id|intr_len
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* States  */
DECL|macro|HCI_USB_TX_PROCESS
mdefine_line|#define HCI_USB_TX_PROCESS&t;1
DECL|macro|HCI_USB_TX_WAKEUP
mdefine_line|#define HCI_USB_TX_WAKEUP&t;2
DECL|macro|HCI_USB_CTRL_TX
mdefine_line|#define HCI_USB_CTRL_TX&t;&t;3
macro_line|#endif /* __KERNEL__ */
eof
