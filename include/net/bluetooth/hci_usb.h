multiline_comment|/* &n;   BlueZ - Bluetooth protocol stack for Linux&n;   Copyright (C) 2000-2001 Qualcomm Incorporated&n;&n;   Written 2000,2001 by Maxim Krasnyansky &lt;maxk@qualcomm.com&gt;&n;&n;   This program is free software; you can redistribute it and/or modify&n;   it under the terms of the GNU General Public License version 2 as&n;   published by the Free Software Foundation;&n;&n;   THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND, EXPRESS&n;   OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,&n;   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT OF THIRD PARTY RIGHTS.&n;   IN NO EVENT SHALL THE COPYRIGHT HOLDER(S) AND AUTHOR(S) BE LIABLE FOR ANY&n;   CLAIM, OR ANY SPECIAL INDIRECT OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES &n;   WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN &n;   ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF &n;   OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.&n;&n;   ALL LIABILITY, INCLUDING LIABILITY FOR INFRINGEMENT OF ANY PATENTS, &n;   COPYRIGHTS, TRADEMARKS OR OTHER RIGHTS, RELATING TO USE OF THIS &n;   SOFTWARE IS DISCLAIMED.&n;*/
multiline_comment|/*&n; * $Id: hci_usb.h,v 1.3 2001/06/02 01:40:08 maxk Exp $&n; */
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
DECL|struct|hci_usb
r_struct
id|hci_usb
(brace
DECL|member|udev
r_struct
id|usb_device
op_star
id|udev
suffix:semicolon
DECL|member|dev_req
r_struct
id|usb_ctrlrequest
id|dev_req
suffix:semicolon
DECL|member|ctrl_urb
r_struct
id|urb
op_star
id|ctrl_urb
suffix:semicolon
DECL|member|intr_urb
r_struct
id|urb
op_star
id|intr_urb
suffix:semicolon
DECL|member|read_urb
r_struct
id|urb
op_star
id|read_urb
suffix:semicolon
DECL|member|write_urb
r_struct
id|urb
op_star
id|write_urb
suffix:semicolon
DECL|member|read_buf
id|__u8
op_star
id|read_buf
suffix:semicolon
DECL|member|intr_buf
id|__u8
op_star
id|intr_buf
suffix:semicolon
DECL|member|intr_skb
r_struct
id|sk_buff
op_star
id|intr_skb
suffix:semicolon
DECL|member|intr_count
r_int
id|intr_count
suffix:semicolon
DECL|member|bulk_out_ep_addr
id|__u8
id|bulk_out_ep_addr
suffix:semicolon
DECL|member|bulk_in_ep_addr
id|__u8
id|bulk_in_ep_addr
suffix:semicolon
DECL|member|intr_in_ep_addr
id|__u8
id|intr_in_ep_addr
suffix:semicolon
DECL|member|intr_in_interval
id|__u8
id|intr_in_interval
suffix:semicolon
DECL|member|hdev
r_struct
id|hci_dev
id|hdev
suffix:semicolon
DECL|member|tx_state
r_int
r_int
id|tx_state
suffix:semicolon
DECL|member|tx_ctrl_q
r_struct
id|sk_buff_head
id|tx_ctrl_q
suffix:semicolon
DECL|member|tx_write_q
r_struct
id|sk_buff_head
id|tx_write_q
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Transmit states  */
DECL|macro|HCI_TX_CTRL
mdefine_line|#define HCI_TX_CTRL&t;1
DECL|macro|HCI_TX_WRITE
mdefine_line|#define HCI_TX_WRITE&t;2
macro_line|#endif /* __KERNEL__ */
eof
