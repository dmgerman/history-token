multiline_comment|/* &n;   BlueZ - Bluetooth protocol stack for Linux&n;   Copyright (C) 2000-2001 Qualcomm Incorporated&n;&n;   Written 2000,2001 by Maxim Krasnyansky &lt;maxk@qualcomm.com&gt;&n;&n;   This program is free software; you can redistribute it and/or modify&n;   it under the terms of the GNU General Public License version 2 as&n;   published by the Free Software Foundation;&n;&n;   THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND, EXPRESS&n;   OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,&n;   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT OF THIRD PARTY RIGHTS.&n;   IN NO EVENT SHALL THE COPYRIGHT HOLDER(S) AND AUTHOR(S) BE LIABLE FOR ANY&n;   CLAIM, OR ANY SPECIAL INDIRECT OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES &n;   WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN &n;   ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF &n;   OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.&n;&n;   ALL LIABILITY, INCLUDING LIABILITY FOR INFRINGEMENT OF ANY PATENTS, &n;   COPYRIGHTS, TRADEMARKS OR OTHER RIGHTS, RELATING TO USE OF THIS &n;   SOFTWARE IS DISCLAIMED.&n;*/
multiline_comment|/*&n; *  $Id: bluetooth.h,v 1.8 2002/04/17 17:37:20 maxk Exp $&n; */
macro_line|#ifndef __BLUETOOTH_H
DECL|macro|__BLUETOOTH_H
mdefine_line|#define __BLUETOOTH_H
macro_line|#include &lt;asm/types.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/poll.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#ifndef AF_BLUETOOTH
DECL|macro|AF_BLUETOOTH
mdefine_line|#define AF_BLUETOOTH&t;31
DECL|macro|PF_BLUETOOTH
mdefine_line|#define PF_BLUETOOTH&t;AF_BLUETOOTH
macro_line|#endif
multiline_comment|/* Reserv for core and drivers use */
DECL|macro|BT_SKB_RESERVE
mdefine_line|#define BT_SKB_RESERVE       8
DECL|macro|BTPROTO_L2CAP
mdefine_line|#define BTPROTO_L2CAP   0
DECL|macro|BTPROTO_HCI
mdefine_line|#define BTPROTO_HCI     1
DECL|macro|BTPROTO_SCO
mdefine_line|#define BTPROTO_SCO   &t;2
DECL|macro|BTPROTO_RFCOMM
mdefine_line|#define BTPROTO_RFCOMM&t;3
DECL|macro|BTPROTO_BNEP
mdefine_line|#define BTPROTO_BNEP    4
DECL|macro|SOL_HCI
mdefine_line|#define SOL_HCI     0
DECL|macro|SOL_L2CAP
mdefine_line|#define SOL_L2CAP   6
DECL|macro|SOL_SCO
mdefine_line|#define SOL_SCO     17
DECL|macro|SOL_RFCOMM
mdefine_line|#define SOL_RFCOMM  18
DECL|macro|BT_INFO
mdefine_line|#define BT_INFO(fmt, arg...) printk(KERN_INFO &quot;Bluetooth: &quot; fmt &quot;&bslash;n&quot; , ## arg)
DECL|macro|BT_DBG
mdefine_line|#define BT_DBG(fmt, arg...)  printk(KERN_INFO &quot;%s: &quot; fmt &quot;&bslash;n&quot; , __FUNCTION__ , ## arg)
DECL|macro|BT_ERR
mdefine_line|#define BT_ERR(fmt, arg...)  printk(KERN_ERR  &quot;%s: &quot; fmt &quot;&bslash;n&quot; , __FUNCTION__ , ## arg)
macro_line|#ifdef HCI_DATA_DUMP
DECL|macro|BT_DMP
mdefine_line|#define BT_DMP(buf, len)    bt_dump(__FUNCTION__, buf, len)
macro_line|#else
DECL|macro|BT_DMP
mdefine_line|#define BT_DMP(D...)
macro_line|#endif
r_extern
r_struct
id|proc_dir_entry
op_star
id|proc_bt
suffix:semicolon
multiline_comment|/* Connection and socket states */
r_enum
(brace
DECL|enumerator|BT_CONNECTED
id|BT_CONNECTED
op_assign
l_int|1
comma
multiline_comment|/* Equal to TCP_ESTABLISHED to make net code happy */
DECL|enumerator|BT_OPEN
id|BT_OPEN
comma
DECL|enumerator|BT_BOUND
id|BT_BOUND
comma
DECL|enumerator|BT_LISTEN
id|BT_LISTEN
comma
DECL|enumerator|BT_CONNECT
id|BT_CONNECT
comma
DECL|enumerator|BT_CONNECT2
id|BT_CONNECT2
comma
DECL|enumerator|BT_CONFIG
id|BT_CONFIG
comma
DECL|enumerator|BT_DISCONN
id|BT_DISCONN
comma
DECL|enumerator|BT_CLOSED
id|BT_CLOSED
)brace
suffix:semicolon
multiline_comment|/* Endianness conversions */
DECL|macro|htobs
mdefine_line|#define htobs(a)&t;__cpu_to_le16(a)
DECL|macro|htobl
mdefine_line|#define htobl(a)&t;__cpu_to_le32(a)
DECL|macro|btohs
mdefine_line|#define btohs(a)&t;__le16_to_cpu(a)
DECL|macro|btohl
mdefine_line|#define btohl(a)&t;__le32_to_cpu(a)
multiline_comment|/* BD Address */
r_typedef
r_struct
(brace
DECL|member|b
id|__u8
id|b
(braket
l_int|6
)braket
suffix:semicolon
DECL|typedef|bdaddr_t
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
id|bdaddr_t
suffix:semicolon
DECL|macro|BDADDR_ANY
mdefine_line|#define BDADDR_ANY   (&amp;(bdaddr_t) {{0, 0, 0, 0, 0, 0}})
DECL|macro|BDADDR_LOCAL
mdefine_line|#define BDADDR_LOCAL (&amp;(bdaddr_t) {{0, 0, 0, 0xff, 0xff, 0xff}})
multiline_comment|/* Copy, swap, convert BD Address */
DECL|function|bacmp
r_static
r_inline
r_int
id|bacmp
c_func
(paren
id|bdaddr_t
op_star
id|ba1
comma
id|bdaddr_t
op_star
id|ba2
)paren
(brace
r_return
id|memcmp
c_func
(paren
id|ba1
comma
id|ba2
comma
r_sizeof
(paren
id|bdaddr_t
)paren
)paren
suffix:semicolon
)brace
DECL|function|bacpy
r_static
r_inline
r_void
id|bacpy
c_func
(paren
id|bdaddr_t
op_star
id|dst
comma
id|bdaddr_t
op_star
id|src
)paren
(brace
id|memcpy
c_func
(paren
id|dst
comma
id|src
comma
r_sizeof
(paren
id|bdaddr_t
)paren
)paren
suffix:semicolon
)brace
r_void
id|baswap
c_func
(paren
id|bdaddr_t
op_star
id|dst
comma
id|bdaddr_t
op_star
id|src
)paren
suffix:semicolon
r_char
op_star
id|batostr
c_func
(paren
id|bdaddr_t
op_star
id|ba
)paren
suffix:semicolon
id|bdaddr_t
op_star
id|strtoba
c_func
(paren
r_char
op_star
id|str
)paren
suffix:semicolon
multiline_comment|/* Common socket structures and functions */
DECL|macro|bt_sk
mdefine_line|#define bt_sk(__sk) ((struct bt_sock *) __sk)
DECL|struct|bt_sock
r_struct
id|bt_sock
(brace
DECL|member|sk
r_struct
id|sock
id|sk
suffix:semicolon
DECL|member|src
id|bdaddr_t
id|src
suffix:semicolon
DECL|member|dst
id|bdaddr_t
id|dst
suffix:semicolon
DECL|member|accept_q
r_struct
id|list_head
id|accept_q
suffix:semicolon
DECL|member|parent
r_struct
id|sock
op_star
id|parent
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|bt_sock_list
r_struct
id|bt_sock_list
(brace
DECL|member|head
r_struct
id|hlist_head
id|head
suffix:semicolon
DECL|member|lock
id|rwlock_t
id|lock
suffix:semicolon
)brace
suffix:semicolon
r_int
id|bt_sock_register
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
r_int
id|bt_sock_unregister
c_func
(paren
r_int
id|proto
)paren
suffix:semicolon
r_struct
id|sock
op_star
id|bt_sock_alloc
c_func
(paren
r_struct
id|socket
op_star
id|sock
comma
r_int
id|proto
comma
r_int
id|pi_size
comma
r_int
id|prio
)paren
suffix:semicolon
r_void
id|bt_sock_link
c_func
(paren
r_struct
id|bt_sock_list
op_star
id|l
comma
r_struct
id|sock
op_star
id|s
)paren
suffix:semicolon
r_void
id|bt_sock_unlink
c_func
(paren
r_struct
id|bt_sock_list
op_star
id|l
comma
r_struct
id|sock
op_star
id|s
)paren
suffix:semicolon
r_int
id|bt_sock_recvmsg
c_func
(paren
r_struct
id|kiocb
op_star
id|iocb
comma
r_struct
id|socket
op_star
id|sock
comma
r_struct
id|msghdr
op_star
id|msg
comma
r_int
id|len
comma
r_int
id|flags
)paren
suffix:semicolon
id|uint
id|bt_sock_poll
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_struct
id|socket
op_star
id|sock
comma
id|poll_table
op_star
id|wait
)paren
suffix:semicolon
r_int
id|bt_sock_wait_state
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_int
id|state
comma
r_int
r_int
id|timeo
)paren
suffix:semicolon
r_void
id|bt_accept_enqueue
c_func
(paren
r_struct
id|sock
op_star
id|parent
comma
r_struct
id|sock
op_star
id|sk
)paren
suffix:semicolon
r_struct
id|sock
op_star
id|bt_accept_dequeue
c_func
(paren
r_struct
id|sock
op_star
id|parent
comma
r_struct
id|socket
op_star
id|newsock
)paren
suffix:semicolon
multiline_comment|/* Skb helpers */
DECL|struct|bt_skb_cb
r_struct
id|bt_skb_cb
(brace
DECL|member|incoming
r_int
id|incoming
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|bt_cb
mdefine_line|#define bt_cb(skb) ((struct bt_skb_cb *)(skb-&gt;cb)) 
DECL|function|bt_skb_alloc
r_static
r_inline
r_struct
id|sk_buff
op_star
id|bt_skb_alloc
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
id|BT_SKB_RESERVE
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
id|BT_SKB_RESERVE
)paren
suffix:semicolon
id|bt_cb
c_func
(paren
id|skb
)paren
op_member_access_from_pointer
id|incoming
op_assign
l_int|0
suffix:semicolon
)brace
r_return
id|skb
suffix:semicolon
)brace
DECL|function|bt_skb_send_alloc
r_static
r_inline
r_struct
id|sk_buff
op_star
id|bt_skb_send_alloc
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
id|BT_SKB_RESERVE
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
id|BT_SKB_RESERVE
)paren
suffix:semicolon
id|bt_cb
c_func
(paren
id|skb
)paren
op_member_access_from_pointer
id|incoming
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
r_void
id|bt_dump
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
r_int
id|bt_err
c_func
(paren
id|__u16
id|code
)paren
suffix:semicolon
macro_line|#endif /* __BLUETOOTH_H */
eof
