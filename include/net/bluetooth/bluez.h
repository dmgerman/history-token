multiline_comment|/* &n;   BlueZ - Bluetooth protocol stack for Linux&n;   Copyright (C) 2000-2001 Qualcomm Incorporated&n;&n;   Written 2000,2001 by Maxim Krasnyansky &lt;maxk@qualcomm.com&gt;&n;&n;   This program is free software; you can redistribute it and/or modify&n;   it under the terms of the GNU General Public License version 2 as&n;   published by the Free Software Foundation;&n;&n;   THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND, EXPRESS&n;   OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,&n;   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT OF THIRD PARTY RIGHTS.&n;   IN NO EVENT SHALL THE COPYRIGHT HOLDER(S) AND AUTHOR(S) BE LIABLE FOR ANY&n;   CLAIM, OR ANY SPECIAL INDIRECT OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES &n;   WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN &n;   ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF &n;   OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.&n;&n;   ALL LIABILITY, INCLUDING LIABILITY FOR INFRINGEMENT OF ANY PATENTS, &n;   COPYRIGHTS, TRADEMARKS OR OTHER RIGHTS, RELATING TO USE OF THIS &n;   SOFTWARE IS DISCLAIMED.&n;*/
multiline_comment|/*&n; *  $Id: bluez.h,v 1.4 2001/08/03 04:19:49 maxk Exp $&n; */
macro_line|#ifndef __IF_BLUEZ_H
DECL|macro|__IF_BLUEZ_H
mdefine_line|#define __IF_BLUEZ_H
macro_line|#include &lt;net/sock.h&gt;
DECL|macro|BLUEZ_MAX_PROTO
mdefine_line|#define BLUEZ_MAX_PROTO &t;2
multiline_comment|/* Reserv for core and drivers use */
DECL|macro|BLUEZ_SKB_RESERVE
mdefine_line|#define BLUEZ_SKB_RESERVE&t;8
macro_line|#ifndef MIN
DECL|macro|MIN
mdefine_line|#define MIN(a,b) ((a) &lt; (b) ? (a) : (b))
macro_line|#endif
multiline_comment|/* Debugging */
macro_line|#ifdef BLUEZ_DEBUG
DECL|macro|HCI_CORE_DEBUG
mdefine_line|#define HCI_CORE_DEBUG&t;&t;1
DECL|macro|HCI_SOCK_DEBUG
mdefine_line|#define HCI_SOCK_DEBUG&t;&t;1
DECL|macro|HCI_UART_DEBUG
mdefine_line|#define HCI_UART_DEBUG&t;&t;1
DECL|macro|HCI_USB_DEBUG
mdefine_line|#define HCI_USB_DEBUG&t;&t;1
singleline_comment|//#define HCI_DATA_DUMP&t;&t;1
DECL|macro|L2CAP_DEBUG
mdefine_line|#define L2CAP_DEBUG&t;&t;&t;1
macro_line|#endif /* BLUEZ_DEBUG */
r_extern
r_void
id|bluez_dump
c_func
(paren
r_char
op_star
id|pref
comma
id|__u8
op_star
id|buf
comma
r_int
id|count
)paren
suffix:semicolon
DECL|macro|INF
mdefine_line|#define INF(fmt, arg...) printk(KERN_INFO fmt &quot;&bslash;n&quot; , ## arg)
DECL|macro|DBG
mdefine_line|#define DBG(fmt, arg...) printk(KERN_INFO __FUNCTION__ &quot;: &quot; fmt &quot;&bslash;n&quot; , ## arg)
DECL|macro|ERR
mdefine_line|#define ERR(fmt, arg...) printk(KERN_ERR  __FUNCTION__ &quot;: &quot; fmt &quot;&bslash;n&quot; , ## arg)
macro_line|#ifdef HCI_DATA_DUMP
DECL|macro|DMP
mdefine_line|#define DMP(buf, len)    bluez_dump(__FUNCTION__, buf, len)
macro_line|#else
DECL|macro|DMP
mdefine_line|#define DMP(D...)
macro_line|#endif
multiline_comment|/* ----- Sockets ------ */
DECL|struct|bluez_sock_list
r_struct
id|bluez_sock_list
(brace
DECL|member|head
r_struct
id|sock
op_star
id|head
suffix:semicolon
DECL|member|lock
id|rwlock_t
id|lock
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_int
id|bluez_sock_register
c_func
(paren
r_int
id|proto
comma
r_struct
id|net_proto_family
op_star
id|ops
)paren
suffix:semicolon
r_extern
r_int
id|bluez_sock_unregister
c_func
(paren
r_int
id|proto
)paren
suffix:semicolon
r_extern
r_void
id|bluez_sock_link
c_func
(paren
r_struct
id|bluez_sock_list
op_star
id|l
comma
r_struct
id|sock
op_star
id|s
)paren
suffix:semicolon
r_extern
r_void
id|bluez_sock_unlink
c_func
(paren
r_struct
id|bluez_sock_list
op_star
id|l
comma
r_struct
id|sock
op_star
id|s
)paren
suffix:semicolon
multiline_comment|/* ----- SKB helpers ----- */
DECL|struct|bluez_skb_cb
r_struct
id|bluez_skb_cb
(brace
DECL|member|incomming
r_int
id|incomming
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|bluez_cb
mdefine_line|#define bluez_cb(skb)&t;((struct bluez_skb_cb *)(skb-&gt;cb)) 
DECL|function|bluez_skb_alloc
r_static
r_inline
r_struct
id|sk_buff
op_star
id|bluez_skb_alloc
c_func
(paren
r_int
r_int
id|len
comma
r_int
id|how
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
r_if
c_cond
(paren
(paren
id|skb
op_assign
id|alloc_skb
c_func
(paren
id|len
op_plus
id|BLUEZ_SKB_RESERVE
comma
id|how
)paren
)paren
)paren
(brace
id|skb_reserve
c_func
(paren
id|skb
comma
id|BLUEZ_SKB_RESERVE
)paren
suffix:semicolon
id|bluez_cb
c_func
(paren
id|skb
)paren
op_member_access_from_pointer
id|incomming
op_assign
l_int|0
suffix:semicolon
)brace
r_return
id|skb
suffix:semicolon
)brace
DECL|function|bluez_skb_send_alloc
r_static
r_inline
r_struct
id|sk_buff
op_star
id|bluez_skb_send_alloc
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_int
r_int
id|len
comma
r_int
id|nb
comma
r_int
op_star
id|err
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
r_if
c_cond
(paren
(paren
id|skb
op_assign
id|sock_alloc_send_skb
c_func
(paren
id|sk
comma
id|len
op_plus
id|BLUEZ_SKB_RESERVE
comma
id|nb
comma
id|err
)paren
)paren
)paren
(brace
id|skb_reserve
c_func
(paren
id|skb
comma
id|BLUEZ_SKB_RESERVE
)paren
suffix:semicolon
id|bluez_cb
c_func
(paren
id|skb
)paren
op_member_access_from_pointer
id|incomming
op_assign
l_int|0
suffix:semicolon
)brace
r_return
id|skb
suffix:semicolon
)brace
DECL|function|skb_frags_no
r_static
r_inline
r_int
id|skb_frags_no
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_register
r_struct
id|sk_buff
op_star
id|frag
op_assign
id|skb_shinfo
c_func
(paren
id|skb
)paren
op_member_access_from_pointer
id|frag_list
suffix:semicolon
r_register
r_int
id|n
op_assign
l_int|1
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|frag
suffix:semicolon
id|frag
op_assign
id|frag-&gt;next
comma
id|n
op_increment
)paren
suffix:semicolon
r_return
id|n
suffix:semicolon
)brace
r_extern
r_int
id|hci_core_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|hci_core_cleanup
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|hci_sock_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|hci_sock_cleanup
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* __IF_BLUEZ_H */
eof
