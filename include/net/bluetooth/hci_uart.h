multiline_comment|/* &n;   BlueZ - Bluetooth protocol stack for Linux&n;   Copyright (C) 2000-2001 Qualcomm Incorporated&n;&n;   Written 2000,2001 by Maxim Krasnyansky &lt;maxk@qualcomm.com&gt;&n;&n;   This program is free software; you can redistribute it and/or modify&n;   it under the terms of the GNU General Public License version 2 as&n;   published by the Free Software Foundation;&n;&n;   THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND, EXPRESS&n;   OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,&n;   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT OF THIRD PARTY RIGHTS.&n;   IN NO EVENT SHALL THE COPYRIGHT HOLDER(S) AND AUTHOR(S) BE LIABLE FOR ANY&n;   CLAIM, OR ANY SPECIAL INDIRECT OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES &n;   WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN &n;   ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF &n;   OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.&n;&n;   ALL LIABILITY, INCLUDING LIABILITY FOR INFRINGEMENT OF ANY PATENTS, &n;   COPYRIGHTS, TRADEMARKS OR OTHER RIGHTS, RELATING TO USE OF THIS &n;   SOFTWARE IS DISCLAIMED.&n;*/
multiline_comment|/*&n; * $Id: hci_uart.h,v 1.2 2001/06/02 01:40:08 maxk Exp $&n; */
macro_line|#ifndef N_HCI
DECL|macro|N_HCI
mdefine_line|#define N_HCI&t;15
macro_line|#endif
macro_line|#ifdef __KERNEL__
DECL|macro|tty2n_hci
mdefine_line|#define tty2n_hci(tty)  ((struct n_hci *)((tty)-&gt;disc_data))
DECL|macro|n_hci2tty
mdefine_line|#define n_hci2tty(n_hci) ((n_hci)-&gt;tty)
DECL|struct|n_hci
r_struct
id|n_hci
(brace
DECL|member|tty
r_struct
id|tty_struct
op_star
id|tty
suffix:semicolon
DECL|member|hdev
r_struct
id|hci_dev
id|hdev
suffix:semicolon
DECL|member|txq
r_struct
id|sk_buff_head
id|txq
suffix:semicolon
DECL|member|tx_state
r_int
r_int
id|tx_state
suffix:semicolon
DECL|member|rx_lock
id|spinlock_t
id|rx_lock
suffix:semicolon
DECL|member|rx_state
r_int
r_int
id|rx_state
suffix:semicolon
DECL|member|rx_count
r_int
r_int
id|rx_count
suffix:semicolon
DECL|member|rx_skb
r_struct
id|sk_buff
op_star
id|rx_skb
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Transmit states  */
DECL|macro|TRANS_SENDING
mdefine_line|#define TRANS_SENDING&t;&t;1
DECL|macro|TRANS_WAKEUP
mdefine_line|#define TRANS_WAKEUP&t;&t;2
multiline_comment|/* Receiver States */
DECL|macro|WAIT_PACKET_TYPE
mdefine_line|#define WAIT_PACKET_TYPE&t;0
DECL|macro|WAIT_EVENT_HDR
mdefine_line|#define WAIT_EVENT_HDR&t; &t;1
DECL|macro|WAIT_ACL_HDR
mdefine_line|#define WAIT_ACL_HDR&t;&t;2
DECL|macro|WAIT_SCO_HDR
mdefine_line|#define WAIT_SCO_HDR&t;&t;3
DECL|macro|WAIT_DATA
mdefine_line|#define WAIT_DATA&t;        4
macro_line|#endif /* __KERNEL__ */
eof
