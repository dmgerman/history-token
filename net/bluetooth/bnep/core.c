multiline_comment|/* &n;   BNEP implementation for Linux Bluetooth stack (BlueZ).&n;   Copyright (C) 2001-2002 Inventel Systemes&n;   Written 2001-2002 by&n;&t;Cl&#xfffd;ment Moreau &lt;clement.moreau@inventel.fr&gt;&n;&t;David Libault  &lt;david.libault@inventel.fr&gt;&n;&n;   Copyright (C) 2002 Maxim Krasnyanskiy &lt;maxk@qualcomm.com&gt;&n;&n;   This program is free software; you can redistribute it and/or modify&n;   it under the terms of the GNU General Public License version 2 as&n;   published by the Free Software Foundation;&n;&n;   THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND, EXPRESS&n;   OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,&n;   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT OF THIRD PARTY RIGHTS.&n;   IN NO EVENT SHALL THE COPYRIGHT HOLDER(S) AND AUTHOR(S) BE LIABLE FOR ANY&n;   CLAIM, OR ANY SPECIAL INDIRECT OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES &n;   WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN &n;   ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF &n;   OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.&n;&n;   ALL LIABILITY, INCLUDING LIABILITY FOR INFRINGEMENT OF ANY PATENTS, &n;   COPYRIGHTS, TRADEMARKS OR OTHER RIGHTS, RELATING TO USE OF THIS &n;   SOFTWARE IS DISCLAIMED.&n;*/
multiline_comment|/*&n; * $Id: core.c,v 1.20 2002/08/04 21:23:58 maxk Exp $&n; */
DECL|macro|__KERNEL_SYSCALLS__
mdefine_line|#define __KERNEL_SYSCALLS__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/net.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/file.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/etherdevice.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;asm/unaligned.h&gt;
macro_line|#include &lt;net/bluetooth/bluetooth.h&gt;
macro_line|#include &lt;net/bluetooth/l2cap.h&gt;
macro_line|#include &quot;bnep.h&quot;
macro_line|#ifndef CONFIG_BT_BNEP_DEBUG
DECL|macro|BT_DBG
macro_line|#undef  BT_DBG
DECL|macro|BT_DBG
mdefine_line|#define BT_DBG(D...)
macro_line|#endif
DECL|macro|VERSION
mdefine_line|#define VERSION &quot;1.0&quot;
r_static
id|LIST_HEAD
c_func
(paren
id|bnep_session_list
)paren
suffix:semicolon
r_static
id|DECLARE_RWSEM
c_func
(paren
id|bnep_session_sem
)paren
suffix:semicolon
DECL|function|__bnep_get_session
r_static
r_struct
id|bnep_session
op_star
id|__bnep_get_session
c_func
(paren
id|u8
op_star
id|dst
)paren
(brace
r_struct
id|bnep_session
op_star
id|s
suffix:semicolon
r_struct
id|list_head
op_star
id|p
suffix:semicolon
id|BT_DBG
c_func
(paren
l_string|&quot;&quot;
)paren
suffix:semicolon
id|list_for_each
c_func
(paren
id|p
comma
op_amp
id|bnep_session_list
)paren
(brace
id|s
op_assign
id|list_entry
c_func
(paren
id|p
comma
r_struct
id|bnep_session
comma
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|memcmp
c_func
(paren
id|dst
comma
id|s-&gt;eh.h_source
comma
id|ETH_ALEN
)paren
)paren
r_return
id|s
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|__bnep_link_session
r_static
r_void
id|__bnep_link_session
c_func
(paren
r_struct
id|bnep_session
op_star
id|s
)paren
(brace
id|MOD_INC_USE_COUNT
suffix:semicolon
id|list_add
c_func
(paren
op_amp
id|s-&gt;list
comma
op_amp
id|bnep_session_list
)paren
suffix:semicolon
)brace
DECL|function|__bnep_unlink_session
r_static
r_void
id|__bnep_unlink_session
c_func
(paren
r_struct
id|bnep_session
op_star
id|s
)paren
(brace
id|list_del
c_func
(paren
op_amp
id|s-&gt;list
)paren
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
)brace
DECL|function|bnep_send
r_static
r_int
id|bnep_send
c_func
(paren
r_struct
id|bnep_session
op_star
id|s
comma
r_void
op_star
id|data
comma
r_int
id|len
)paren
(brace
r_struct
id|kiocb
id|iocb
suffix:semicolon
r_struct
id|sock_iocb
op_star
id|si
suffix:semicolon
r_struct
id|socket
op_star
id|sock
op_assign
id|s-&gt;sock
suffix:semicolon
r_struct
id|iovec
id|iv
op_assign
(brace
id|data
comma
id|len
)brace
suffix:semicolon
r_int
id|err
suffix:semicolon
id|s-&gt;msg.msg_iov
op_assign
op_amp
id|iv
suffix:semicolon
id|s-&gt;msg.msg_iovlen
op_assign
l_int|1
suffix:semicolon
id|init_sync_kiocb
c_func
(paren
op_amp
id|iocb
comma
l_int|NULL
)paren
suffix:semicolon
id|si
op_assign
id|kiocb_to_siocb
c_func
(paren
op_amp
id|iocb
)paren
suffix:semicolon
id|si-&gt;scm
op_assign
l_int|NULL
suffix:semicolon
id|si-&gt;sock
op_assign
id|sock
suffix:semicolon
id|si-&gt;msg
op_assign
op_amp
id|s-&gt;msg
suffix:semicolon
id|si-&gt;size
op_assign
id|len
suffix:semicolon
id|err
op_assign
id|sock-&gt;ops
op_member_access_from_pointer
id|sendmsg
c_func
(paren
op_amp
id|iocb
comma
id|sock
comma
op_amp
id|s-&gt;msg
comma
id|len
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_minus
id|EIOCBQUEUED
op_eq
id|err
)paren
id|err
op_assign
id|wait_on_sync_kiocb
c_func
(paren
op_amp
id|iocb
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|bnep_send_rsp
r_static
r_int
id|bnep_send_rsp
c_func
(paren
r_struct
id|bnep_session
op_star
id|s
comma
id|u8
id|ctrl
comma
id|u16
id|resp
)paren
(brace
r_struct
id|bnep_control_rsp
id|rsp
suffix:semicolon
id|rsp.type
op_assign
id|BNEP_CONTROL
suffix:semicolon
id|rsp.ctrl
op_assign
id|ctrl
suffix:semicolon
id|rsp.resp
op_assign
id|htons
c_func
(paren
id|resp
)paren
suffix:semicolon
r_return
id|bnep_send
c_func
(paren
id|s
comma
op_amp
id|rsp
comma
r_sizeof
(paren
id|rsp
)paren
)paren
suffix:semicolon
)brace
DECL|function|bnep_ctrl_set_netfilter
r_static
r_int
id|bnep_ctrl_set_netfilter
c_func
(paren
r_struct
id|bnep_session
op_star
id|s
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
id|u16
op_star
id|data
suffix:semicolon
r_int
id|n
suffix:semicolon
id|data
op_assign
(paren
r_void
op_star
)paren
id|skb-&gt;data
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|skb_pull
c_func
(paren
id|skb
comma
l_int|2
)paren
)paren
r_return
op_minus
id|EILSEQ
suffix:semicolon
id|n
op_assign
id|ntohs
c_func
(paren
id|get_unaligned
c_func
(paren
id|data
)paren
)paren
suffix:semicolon
id|data
op_assign
(paren
r_void
op_star
)paren
id|skb-&gt;data
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|skb_pull
c_func
(paren
id|skb
comma
id|n
)paren
)paren
r_return
op_minus
id|EILSEQ
suffix:semicolon
id|BT_DBG
c_func
(paren
l_string|&quot;filter len %d&quot;
comma
id|n
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_BT_BNEP_PROTO_FILTER
id|n
op_div_assign
l_int|4
suffix:semicolon
r_if
c_cond
(paren
id|n
op_le
id|BNEP_MAX_PROTO_FILTERS
)paren
(brace
r_struct
id|bnep_proto_filter
op_star
id|f
op_assign
id|s-&gt;proto_filter
suffix:semicolon
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|n
suffix:semicolon
id|i
op_increment
)paren
(brace
id|f
(braket
id|i
)braket
dot
id|start
op_assign
id|get_unaligned
c_func
(paren
id|data
op_increment
)paren
suffix:semicolon
id|f
(braket
id|i
)braket
dot
id|end
op_assign
id|get_unaligned
c_func
(paren
id|data
op_increment
)paren
suffix:semicolon
id|BT_DBG
c_func
(paren
l_string|&quot;proto filter start %d end %d&quot;
comma
id|f
(braket
id|i
)braket
dot
id|start
comma
id|f
(braket
id|i
)braket
dot
id|end
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|i
OL
id|BNEP_MAX_PROTO_FILTERS
)paren
id|memset
c_func
(paren
id|f
op_plus
id|i
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|f
)paren
)paren
suffix:semicolon
id|bnep_send_rsp
c_func
(paren
id|s
comma
id|BNEP_FILTER_NET_TYPE_RSP
comma
id|BNEP_SUCCESS
)paren
suffix:semicolon
)brace
r_else
(brace
id|bnep_send_rsp
c_func
(paren
id|s
comma
id|BNEP_FILTER_NET_TYPE_RSP
comma
id|BNEP_FILTER_LIMIT_REACHED
)paren
suffix:semicolon
)brace
macro_line|#else
id|bnep_send_rsp
c_func
(paren
id|s
comma
id|BNEP_FILTER_NET_TYPE_RSP
comma
id|BNEP_FILTER_UNSUPPORTED_REQ
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|bnep_ctrl_set_mcfilter
r_static
r_int
id|bnep_ctrl_set_mcfilter
c_func
(paren
r_struct
id|bnep_session
op_star
id|s
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
id|u8
op_star
id|data
suffix:semicolon
r_int
id|n
suffix:semicolon
id|data
op_assign
(paren
r_void
op_star
)paren
id|skb-&gt;data
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|skb_pull
c_func
(paren
id|skb
comma
l_int|2
)paren
)paren
r_return
op_minus
id|EILSEQ
suffix:semicolon
id|n
op_assign
id|ntohs
c_func
(paren
id|get_unaligned
c_func
(paren
(paren
id|u16
op_star
)paren
id|data
)paren
)paren
suffix:semicolon
id|data
op_assign
(paren
r_void
op_star
)paren
id|skb-&gt;data
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|skb_pull
c_func
(paren
id|skb
comma
id|n
)paren
)paren
r_return
op_minus
id|EILSEQ
suffix:semicolon
id|BT_DBG
c_func
(paren
l_string|&quot;filter len %d&quot;
comma
id|n
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_BT_BNEP_MC_FILTER
id|n
op_div_assign
(paren
id|ETH_ALEN
op_star
l_int|2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|n
OG
l_int|0
)paren
(brace
id|s-&gt;mc_filter
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Always send broadcast */
id|set_bit
c_func
(paren
id|bnep_mc_hash
c_func
(paren
id|s-&gt;dev.broadcast
)paren
comma
(paren
id|ulong
op_star
)paren
op_amp
id|s-&gt;mc_filter
)paren
suffix:semicolon
multiline_comment|/* Add address ranges to the multicast hash */
r_for
c_loop
(paren
suffix:semicolon
id|n
OG
l_int|0
suffix:semicolon
id|n
op_decrement
)paren
(brace
id|u8
id|a1
(braket
l_int|6
)braket
comma
op_star
id|a2
suffix:semicolon
id|memcpy
c_func
(paren
id|a1
comma
id|data
comma
id|ETH_ALEN
)paren
suffix:semicolon
id|data
op_add_assign
id|ETH_ALEN
suffix:semicolon
id|a2
op_assign
id|data
suffix:semicolon
id|data
op_add_assign
id|ETH_ALEN
suffix:semicolon
id|BT_DBG
c_func
(paren
l_string|&quot;mc filter %s -&gt; %s&quot;
comma
id|batostr
c_func
(paren
(paren
r_void
op_star
)paren
id|a1
)paren
comma
id|batostr
c_func
(paren
(paren
r_void
op_star
)paren
id|a2
)paren
)paren
suffix:semicolon
DECL|macro|INCA
mdefine_line|#define INCA(a) { int i = 5; while (i &gt;=0 &amp;&amp; ++a[i--] == 0); }
multiline_comment|/* Iterate from a1 to a2 */
id|set_bit
c_func
(paren
id|bnep_mc_hash
c_func
(paren
id|a1
)paren
comma
(paren
id|ulong
op_star
)paren
op_amp
id|s-&gt;mc_filter
)paren
suffix:semicolon
r_while
c_loop
(paren
id|memcmp
c_func
(paren
id|a1
comma
id|a2
comma
l_int|6
)paren
OL
l_int|0
op_logical_and
id|s-&gt;mc_filter
op_ne
op_complement
l_int|0LL
)paren
(brace
id|INCA
c_func
(paren
id|a1
)paren
suffix:semicolon
id|set_bit
c_func
(paren
id|bnep_mc_hash
c_func
(paren
id|a1
)paren
comma
(paren
id|ulong
op_star
)paren
op_amp
id|s-&gt;mc_filter
)paren
suffix:semicolon
)brace
)brace
)brace
id|BT_DBG
c_func
(paren
l_string|&quot;mc filter hash 0x%llx&quot;
comma
id|s-&gt;mc_filter
)paren
suffix:semicolon
id|bnep_send_rsp
c_func
(paren
id|s
comma
id|BNEP_FILTER_MULTI_ADDR_RSP
comma
id|BNEP_SUCCESS
)paren
suffix:semicolon
macro_line|#else
id|bnep_send_rsp
c_func
(paren
id|s
comma
id|BNEP_FILTER_MULTI_ADDR_RSP
comma
id|BNEP_FILTER_UNSUPPORTED_REQ
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|bnep_rx_control
r_static
r_int
id|bnep_rx_control
c_func
(paren
r_struct
id|bnep_session
op_star
id|s
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_int
id|err
op_assign
l_int|0
suffix:semicolon
id|u8
id|cmd
op_assign
op_star
(paren
id|u8
op_star
)paren
id|skb-&gt;data
suffix:semicolon
id|skb_pull
c_func
(paren
id|skb
comma
l_int|1
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|BNEP_CMD_NOT_UNDERSTOOD
suffix:colon
r_case
id|BNEP_SETUP_CONN_REQ
suffix:colon
r_case
id|BNEP_SETUP_CONN_RSP
suffix:colon
r_case
id|BNEP_FILTER_NET_TYPE_RSP
suffix:colon
r_case
id|BNEP_FILTER_MULTI_ADDR_RSP
suffix:colon
multiline_comment|/* Ignore these for now */
r_break
suffix:semicolon
r_case
id|BNEP_FILTER_NET_TYPE_SET
suffix:colon
id|err
op_assign
id|bnep_ctrl_set_netfilter
c_func
(paren
id|s
comma
id|skb
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|BNEP_FILTER_MULTI_ADDR_SET
suffix:colon
id|err
op_assign
id|bnep_ctrl_set_mcfilter
c_func
(paren
id|s
comma
id|skb
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
(brace
)brace
(brace
id|u8
id|pkt
(braket
l_int|3
)braket
suffix:semicolon
id|pkt
(braket
l_int|0
)braket
op_assign
id|BNEP_CONTROL
suffix:semicolon
id|pkt
(braket
l_int|1
)braket
op_assign
id|BNEP_CMD_NOT_UNDERSTOOD
suffix:semicolon
id|pkt
(braket
l_int|2
)braket
op_assign
id|cmd
suffix:semicolon
id|bnep_send
c_func
(paren
id|s
comma
id|pkt
comma
r_sizeof
(paren
id|pkt
)paren
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
r_return
id|err
suffix:semicolon
)brace
DECL|function|bnep_rx_extension
r_static
r_int
id|bnep_rx_extension
c_func
(paren
r_struct
id|bnep_session
op_star
id|s
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|bnep_ext_hdr
op_star
id|h
suffix:semicolon
r_int
id|err
op_assign
l_int|0
suffix:semicolon
r_do
(brace
id|h
op_assign
(paren
r_void
op_star
)paren
id|skb-&gt;data
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|skb_pull
c_func
(paren
id|skb
comma
r_sizeof
(paren
op_star
id|h
)paren
)paren
)paren
(brace
id|err
op_assign
op_minus
id|EILSEQ
suffix:semicolon
r_break
suffix:semicolon
)brace
id|BT_DBG
c_func
(paren
l_string|&quot;type 0x%x len %d&quot;
comma
id|h-&gt;type
comma
id|h-&gt;len
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|h-&gt;type
op_amp
id|BNEP_TYPE_MASK
)paren
(brace
r_case
id|BNEP_EXT_CONTROL
suffix:colon
id|err
op_assign
id|bnep_rx_control
c_func
(paren
id|s
comma
id|skb
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
(brace
)brace
multiline_comment|/* Unknown extension */
r_if
c_cond
(paren
op_logical_neg
id|skb_pull
c_func
(paren
id|skb
comma
id|h-&gt;len
)paren
)paren
id|err
op_assign
op_minus
id|EILSEQ
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
op_logical_neg
id|err
op_logical_and
(paren
id|h-&gt;type
op_amp
id|BNEP_EXT_HEADER
)paren
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|variable|__bnep_rx_hlen
r_static
id|u8
id|__bnep_rx_hlen
(braket
)braket
op_assign
(brace
id|ETH_HLEN
comma
multiline_comment|/* BNEP_GENERAL */
l_int|0
comma
multiline_comment|/* BNEP_CONTROL */
l_int|2
comma
multiline_comment|/* BNEP_COMPRESSED */
id|ETH_ALEN
op_plus
l_int|2
comma
multiline_comment|/* BNEP_COMPRESSED_SRC_ONLY */
id|ETH_ALEN
op_plus
l_int|2
multiline_comment|/* BNEP_COMPRESSED_DST_ONLY */
)brace
suffix:semicolon
DECL|macro|BNEP_RX_TYPES
mdefine_line|#define BNEP_RX_TYPES&t;(sizeof(__bnep_rx_hlen) - 1)
DECL|function|bnep_rx_frame
r_static
r_inline
r_int
id|bnep_rx_frame
c_func
(paren
r_struct
id|bnep_session
op_star
id|s
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|net_device
op_star
id|dev
op_assign
op_amp
id|s-&gt;dev
suffix:semicolon
r_struct
id|sk_buff
op_star
id|nskb
suffix:semicolon
id|u8
id|type
suffix:semicolon
id|dev-&gt;last_rx
op_assign
id|jiffies
suffix:semicolon
id|s-&gt;stats.rx_bytes
op_add_assign
id|skb-&gt;len
suffix:semicolon
id|type
op_assign
op_star
(paren
id|u8
op_star
)paren
id|skb-&gt;data
suffix:semicolon
id|skb_pull
c_func
(paren
id|skb
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|type
op_amp
id|BNEP_TYPE_MASK
)paren
OG
id|BNEP_RX_TYPES
)paren
r_goto
id|badframe
suffix:semicolon
r_if
c_cond
(paren
(paren
id|type
op_amp
id|BNEP_TYPE_MASK
)paren
op_eq
id|BNEP_CONTROL
)paren
(brace
id|bnep_rx_control
c_func
(paren
id|s
comma
id|skb
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
id|skb-&gt;mac.raw
op_assign
id|skb-&gt;data
suffix:semicolon
multiline_comment|/* Verify and pull out header */
r_if
c_cond
(paren
op_logical_neg
id|skb_pull
c_func
(paren
id|skb
comma
id|__bnep_rx_hlen
(braket
id|type
op_amp
id|BNEP_TYPE_MASK
)braket
)paren
)paren
r_goto
id|badframe
suffix:semicolon
id|s-&gt;eh.h_proto
op_assign
id|get_unaligned
c_func
(paren
(paren
id|u16
op_star
)paren
(paren
id|skb-&gt;data
op_minus
l_int|2
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|type
op_amp
id|BNEP_EXT_HEADER
)paren
(brace
r_if
c_cond
(paren
id|bnep_rx_extension
c_func
(paren
id|s
comma
id|skb
)paren
OL
l_int|0
)paren
r_goto
id|badframe
suffix:semicolon
)brace
multiline_comment|/* Strip 802.1p header */
r_if
c_cond
(paren
id|ntohs
c_func
(paren
id|s-&gt;eh.h_proto
)paren
op_eq
l_int|0x8100
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|skb_pull
c_func
(paren
id|skb
comma
l_int|4
)paren
)paren
r_goto
id|badframe
suffix:semicolon
id|s-&gt;eh.h_proto
op_assign
id|get_unaligned
c_func
(paren
(paren
id|u16
op_star
)paren
(paren
id|skb-&gt;data
op_minus
l_int|2
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* We have to alloc new skb and copy data here :(. Because original skb&n;&t; * may not be modified and because of the alignment requirements. */
id|nskb
op_assign
id|alloc_skb
c_func
(paren
l_int|2
op_plus
id|ETH_HLEN
op_plus
id|skb-&gt;len
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|nskb
)paren
(brace
id|s-&gt;stats.rx_dropped
op_increment
suffix:semicolon
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|skb_reserve
c_func
(paren
id|nskb
comma
l_int|2
)paren
suffix:semicolon
multiline_comment|/* Decompress header and construct ether frame */
r_switch
c_cond
(paren
id|type
op_amp
id|BNEP_TYPE_MASK
)paren
(brace
r_case
id|BNEP_COMPRESSED
suffix:colon
id|memcpy
c_func
(paren
id|__skb_put
c_func
(paren
id|nskb
comma
id|ETH_HLEN
)paren
comma
op_amp
id|s-&gt;eh
comma
id|ETH_HLEN
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|BNEP_COMPRESSED_SRC_ONLY
suffix:colon
id|memcpy
c_func
(paren
id|__skb_put
c_func
(paren
id|nskb
comma
id|ETH_ALEN
)paren
comma
id|s-&gt;eh.h_dest
comma
id|ETH_ALEN
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|__skb_put
c_func
(paren
id|nskb
comma
id|ETH_ALEN
)paren
comma
id|skb-&gt;mac.raw
comma
id|ETH_ALEN
)paren
suffix:semicolon
id|put_unaligned
c_func
(paren
id|s-&gt;eh.h_proto
comma
(paren
id|u16
op_star
)paren
id|__skb_put
c_func
(paren
id|nskb
comma
l_int|2
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|BNEP_COMPRESSED_DST_ONLY
suffix:colon
id|memcpy
c_func
(paren
id|__skb_put
c_func
(paren
id|nskb
comma
id|ETH_ALEN
)paren
comma
id|skb-&gt;mac.raw
comma
id|ETH_ALEN
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|__skb_put
c_func
(paren
id|nskb
comma
id|ETH_ALEN
op_plus
l_int|2
)paren
comma
id|s-&gt;eh.h_source
comma
id|ETH_ALEN
op_plus
l_int|2
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|BNEP_GENERAL
suffix:colon
id|memcpy
c_func
(paren
id|__skb_put
c_func
(paren
id|nskb
comma
id|ETH_ALEN
op_star
l_int|2
)paren
comma
id|skb-&gt;mac.raw
comma
id|ETH_ALEN
op_star
l_int|2
)paren
suffix:semicolon
id|put_unaligned
c_func
(paren
id|s-&gt;eh.h_proto
comma
(paren
id|u16
op_star
)paren
id|__skb_put
c_func
(paren
id|nskb
comma
l_int|2
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|memcpy
c_func
(paren
id|__skb_put
c_func
(paren
id|nskb
comma
id|skb-&gt;len
)paren
comma
id|skb-&gt;data
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
id|s-&gt;stats.rx_packets
op_increment
suffix:semicolon
id|nskb-&gt;dev
op_assign
id|dev
suffix:semicolon
id|nskb-&gt;ip_summed
op_assign
id|CHECKSUM_UNNECESSARY
suffix:semicolon
id|nskb-&gt;protocol
op_assign
id|eth_type_trans
c_func
(paren
id|nskb
comma
id|dev
)paren
suffix:semicolon
id|netif_rx_ni
c_func
(paren
id|nskb
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|badframe
suffix:colon
id|s-&gt;stats.rx_errors
op_increment
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
DECL|variable|__bnep_tx_types
r_static
id|u8
id|__bnep_tx_types
(braket
)braket
op_assign
(brace
id|BNEP_GENERAL
comma
id|BNEP_COMPRESSED_SRC_ONLY
comma
id|BNEP_COMPRESSED_DST_ONLY
comma
id|BNEP_COMPRESSED
)brace
suffix:semicolon
DECL|function|bnep_tx_frame
r_static
r_inline
r_int
id|bnep_tx_frame
c_func
(paren
r_struct
id|bnep_session
op_star
id|s
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|ethhdr
op_star
id|eh
op_assign
(paren
r_void
op_star
)paren
id|skb-&gt;data
suffix:semicolon
r_struct
id|socket
op_star
id|sock
op_assign
id|s-&gt;sock
suffix:semicolon
r_struct
id|iovec
id|iv
(braket
l_int|3
)braket
suffix:semicolon
r_int
id|len
op_assign
l_int|0
comma
id|il
op_assign
l_int|0
suffix:semicolon
id|u8
id|type
op_assign
l_int|0
suffix:semicolon
id|BT_DBG
c_func
(paren
l_string|&quot;skb %p dev %p type %d&quot;
comma
id|skb
comma
id|skb-&gt;dev
comma
id|skb-&gt;pkt_type
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|skb-&gt;dev
)paren
(brace
multiline_comment|/* Control frame sent by us */
r_goto
id|send
suffix:semicolon
)brace
id|iv
(braket
id|il
op_increment
)braket
op_assign
(paren
r_struct
id|iovec
)paren
(brace
op_amp
id|type
comma
l_int|1
)brace
suffix:semicolon
id|len
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|memcmp
c_func
(paren
id|eh-&gt;h_dest
comma
id|s-&gt;eh.h_source
comma
id|ETH_ALEN
)paren
)paren
id|type
op_or_assign
l_int|0x01
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|memcmp
c_func
(paren
id|eh-&gt;h_source
comma
id|s-&gt;eh.h_dest
comma
id|ETH_ALEN
)paren
)paren
id|type
op_or_assign
l_int|0x02
suffix:semicolon
r_if
c_cond
(paren
id|type
)paren
id|skb_pull
c_func
(paren
id|skb
comma
id|ETH_ALEN
op_star
l_int|2
)paren
suffix:semicolon
id|type
op_assign
id|__bnep_tx_types
(braket
id|type
)braket
suffix:semicolon
r_switch
c_cond
(paren
id|type
)paren
(brace
r_case
id|BNEP_COMPRESSED_SRC_ONLY
suffix:colon
id|iv
(braket
id|il
op_increment
)braket
op_assign
(paren
r_struct
id|iovec
)paren
(brace
id|eh-&gt;h_source
comma
id|ETH_ALEN
)brace
suffix:semicolon
id|len
op_add_assign
id|ETH_ALEN
suffix:semicolon
r_break
suffix:semicolon
r_case
id|BNEP_COMPRESSED_DST_ONLY
suffix:colon
id|iv
(braket
id|il
op_increment
)braket
op_assign
(paren
r_struct
id|iovec
)paren
(brace
id|eh-&gt;h_dest
comma
id|ETH_ALEN
)brace
suffix:semicolon
id|len
op_add_assign
id|ETH_ALEN
suffix:semicolon
r_break
suffix:semicolon
)brace
id|send
suffix:colon
id|iv
(braket
id|il
op_increment
)braket
op_assign
(paren
r_struct
id|iovec
)paren
(brace
id|skb-&gt;data
comma
id|skb-&gt;len
)brace
suffix:semicolon
id|len
op_add_assign
id|skb-&gt;len
suffix:semicolon
multiline_comment|/* FIXME: linearize skb */
(brace
r_struct
id|kiocb
id|iocb
suffix:semicolon
r_struct
id|sock_iocb
op_star
id|si
suffix:semicolon
id|s-&gt;msg.msg_iov
op_assign
id|iv
suffix:semicolon
id|s-&gt;msg.msg_iovlen
op_assign
id|il
suffix:semicolon
id|init_sync_kiocb
c_func
(paren
op_amp
id|iocb
comma
l_int|NULL
)paren
suffix:semicolon
id|si
op_assign
id|kiocb_to_siocb
c_func
(paren
op_amp
id|iocb
)paren
suffix:semicolon
id|si-&gt;scm
op_assign
l_int|NULL
suffix:semicolon
id|si-&gt;sock
op_assign
id|sock
suffix:semicolon
id|si-&gt;msg
op_assign
op_amp
id|s-&gt;msg
suffix:semicolon
id|si-&gt;size
op_assign
id|len
suffix:semicolon
id|len
op_assign
id|sock-&gt;ops
op_member_access_from_pointer
id|sendmsg
c_func
(paren
op_amp
id|iocb
comma
id|sock
comma
op_amp
id|s-&gt;msg
comma
id|len
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_minus
id|EIOCBQUEUED
op_eq
id|len
)paren
id|len
op_assign
id|wait_on_sync_kiocb
c_func
(paren
op_amp
id|iocb
)paren
suffix:semicolon
)brace
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
l_int|0
)paren
(brace
id|s-&gt;stats.tx_bytes
op_add_assign
id|len
suffix:semicolon
id|s-&gt;stats.tx_packets
op_increment
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
id|len
suffix:semicolon
)brace
DECL|function|bnep_session
r_static
r_int
id|bnep_session
c_func
(paren
r_void
op_star
id|arg
)paren
(brace
r_struct
id|bnep_session
op_star
id|s
op_assign
id|arg
suffix:semicolon
r_struct
id|net_device
op_star
id|dev
op_assign
op_amp
id|s-&gt;dev
suffix:semicolon
r_struct
id|sock
op_star
id|sk
op_assign
id|s-&gt;sock-&gt;sk
suffix:semicolon
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
id|wait_queue_t
id|wait
suffix:semicolon
id|BT_DBG
c_func
(paren
l_string|&quot;&quot;
)paren
suffix:semicolon
id|daemonize
c_func
(paren
l_string|&quot;kbnepd %s&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
id|set_user_nice
c_func
(paren
id|current
comma
op_minus
l_int|15
)paren
suffix:semicolon
id|current-&gt;flags
op_or_assign
id|PF_IOTHREAD
suffix:semicolon
id|set_fs
c_func
(paren
id|KERNEL_DS
)paren
suffix:semicolon
id|init_waitqueue_entry
c_func
(paren
op_amp
id|wait
comma
id|current
)paren
suffix:semicolon
id|add_wait_queue
c_func
(paren
id|sk-&gt;sleep
comma
op_amp
id|wait
)paren
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|atomic_read
c_func
(paren
op_amp
id|s-&gt;killed
)paren
)paren
(brace
id|set_current_state
c_func
(paren
id|TASK_INTERRUPTIBLE
)paren
suffix:semicolon
singleline_comment|// RX
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
id|sk-&gt;receive_queue
)paren
)paren
)paren
(brace
id|skb_orphan
c_func
(paren
id|skb
)paren
suffix:semicolon
id|bnep_rx_frame
c_func
(paren
id|s
comma
id|skb
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sk-&gt;state
op_ne
id|BT_CONNECTED
)paren
r_break
suffix:semicolon
singleline_comment|// TX
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
id|sk-&gt;write_queue
)paren
)paren
)paren
r_if
c_cond
(paren
id|bnep_tx_frame
c_func
(paren
id|s
comma
id|skb
)paren
)paren
r_break
suffix:semicolon
id|netif_wake_queue
c_func
(paren
id|dev
)paren
suffix:semicolon
id|schedule
c_func
(paren
)paren
suffix:semicolon
)brace
id|set_current_state
c_func
(paren
id|TASK_RUNNING
)paren
suffix:semicolon
id|remove_wait_queue
c_func
(paren
id|sk-&gt;sleep
comma
op_amp
id|wait
)paren
suffix:semicolon
multiline_comment|/* Cleanup session */
id|down_write
c_func
(paren
op_amp
id|bnep_session_sem
)paren
suffix:semicolon
multiline_comment|/* Delete network device */
id|unregister_netdev
c_func
(paren
id|dev
)paren
suffix:semicolon
multiline_comment|/* Release the socket */
id|fput
c_func
(paren
id|s-&gt;sock-&gt;file
)paren
suffix:semicolon
id|__bnep_unlink_session
c_func
(paren
id|s
)paren
suffix:semicolon
id|up_write
c_func
(paren
op_amp
id|bnep_session_sem
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|s
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|bnep_add_connection
r_int
id|bnep_add_connection
c_func
(paren
r_struct
id|bnep_conadd_req
op_star
id|req
comma
r_struct
id|socket
op_star
id|sock
)paren
(brace
r_struct
id|net_device
op_star
id|dev
suffix:semicolon
r_struct
id|bnep_session
op_star
id|s
comma
op_star
id|ss
suffix:semicolon
id|u8
id|dst
(braket
id|ETH_ALEN
)braket
comma
id|src
(braket
id|ETH_ALEN
)braket
suffix:semicolon
r_int
id|err
suffix:semicolon
id|BT_DBG
c_func
(paren
l_string|&quot;&quot;
)paren
suffix:semicolon
id|baswap
c_func
(paren
(paren
r_void
op_star
)paren
id|dst
comma
op_amp
id|bt_sk
c_func
(paren
id|sock-&gt;sk
)paren
op_member_access_from_pointer
id|dst
)paren
suffix:semicolon
id|baswap
c_func
(paren
(paren
r_void
op_star
)paren
id|src
comma
op_amp
id|bt_sk
c_func
(paren
id|sock-&gt;sk
)paren
op_member_access_from_pointer
id|src
)paren
suffix:semicolon
id|s
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|bnep_session
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|s
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|memset
c_func
(paren
id|s
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|bnep_session
)paren
)paren
suffix:semicolon
id|down_write
c_func
(paren
op_amp
id|bnep_session_sem
)paren
suffix:semicolon
id|ss
op_assign
id|__bnep_get_session
c_func
(paren
id|dst
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ss
op_logical_and
id|ss-&gt;state
op_eq
id|BT_CONNECTED
)paren
(brace
id|err
op_assign
op_minus
id|EEXIST
suffix:semicolon
r_goto
id|failed
suffix:semicolon
)brace
id|dev
op_assign
op_amp
id|s-&gt;dev
suffix:semicolon
r_if
c_cond
(paren
op_star
id|req-&gt;device
)paren
id|strcpy
c_func
(paren
id|dev-&gt;name
comma
id|req-&gt;device
)paren
suffix:semicolon
r_else
id|strcpy
c_func
(paren
id|dev-&gt;name
comma
l_string|&quot;bnep%d&quot;
)paren
suffix:semicolon
id|memset
c_func
(paren
id|dev-&gt;broadcast
comma
l_int|0xff
comma
id|ETH_ALEN
)paren
suffix:semicolon
multiline_comment|/* This is rx header therefor addresses are swaped.&n;&t; * ie eh.h_dest is our local address. */
id|memcpy
c_func
(paren
id|s-&gt;eh.h_dest
comma
op_amp
id|src
comma
id|ETH_ALEN
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|s-&gt;eh.h_source
comma
op_amp
id|dst
comma
id|ETH_ALEN
)paren
suffix:semicolon
id|s-&gt;sock
op_assign
id|sock
suffix:semicolon
id|s-&gt;role
op_assign
id|req-&gt;role
suffix:semicolon
id|s-&gt;state
op_assign
id|BT_CONNECTED
suffix:semicolon
id|s-&gt;msg.msg_flags
op_assign
id|MSG_NOSIGNAL
suffix:semicolon
macro_line|#ifdef CONFIG_BT_BNEP_MC_FILTER
multiline_comment|/* Set default mc filter */
id|set_bit
c_func
(paren
id|bnep_mc_hash
c_func
(paren
id|dev-&gt;broadcast
)paren
comma
(paren
id|ulong
op_star
)paren
op_amp
id|s-&gt;mc_filter
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_BT_BNEP_PROTO_FILTER
multiline_comment|/* Set default protocol filter */
multiline_comment|/* (IPv4, ARP)  */
id|s-&gt;proto_filter
(braket
l_int|0
)braket
dot
id|start
op_assign
id|htons
c_func
(paren
l_int|0x0800
)paren
suffix:semicolon
id|s-&gt;proto_filter
(braket
l_int|0
)braket
dot
id|end
op_assign
id|htons
c_func
(paren
l_int|0x0806
)paren
suffix:semicolon
multiline_comment|/* (RARP, AppleTalk) */
id|s-&gt;proto_filter
(braket
l_int|1
)braket
dot
id|start
op_assign
id|htons
c_func
(paren
l_int|0x8035
)paren
suffix:semicolon
id|s-&gt;proto_filter
(braket
l_int|1
)braket
dot
id|end
op_assign
id|htons
c_func
(paren
l_int|0x80F3
)paren
suffix:semicolon
multiline_comment|/* (IPX, IPv6) */
id|s-&gt;proto_filter
(braket
l_int|2
)braket
dot
id|start
op_assign
id|htons
c_func
(paren
l_int|0x8137
)paren
suffix:semicolon
id|s-&gt;proto_filter
(braket
l_int|2
)braket
dot
id|end
op_assign
id|htons
c_func
(paren
l_int|0x86DD
)paren
suffix:semicolon
macro_line|#endif
id|dev-&gt;init
op_assign
id|bnep_net_init
suffix:semicolon
id|dev-&gt;priv
op_assign
id|s
suffix:semicolon
id|err
op_assign
id|register_netdev
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
r_goto
id|failed
suffix:semicolon
)brace
id|__bnep_link_session
c_func
(paren
id|s
)paren
suffix:semicolon
id|err
op_assign
id|kernel_thread
c_func
(paren
id|bnep_session
comma
id|s
comma
id|CLONE_FS
op_or
id|CLONE_FILES
op_or
id|CLONE_SIGHAND
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
multiline_comment|/* Session thread start failed, gotta cleanup. */
id|unregister_netdev
c_func
(paren
id|dev
)paren
suffix:semicolon
id|__bnep_unlink_session
c_func
(paren
id|s
)paren
suffix:semicolon
r_goto
id|failed
suffix:semicolon
)brace
id|up_write
c_func
(paren
op_amp
id|bnep_session_sem
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|req-&gt;device
comma
id|dev-&gt;name
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|failed
suffix:colon
id|up_write
c_func
(paren
op_amp
id|bnep_session_sem
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|s
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|bnep_del_connection
r_int
id|bnep_del_connection
c_func
(paren
r_struct
id|bnep_condel_req
op_star
id|req
)paren
(brace
r_struct
id|bnep_session
op_star
id|s
suffix:semicolon
r_int
id|err
op_assign
l_int|0
suffix:semicolon
id|BT_DBG
c_func
(paren
l_string|&quot;&quot;
)paren
suffix:semicolon
id|down_read
c_func
(paren
op_amp
id|bnep_session_sem
)paren
suffix:semicolon
id|s
op_assign
id|__bnep_get_session
c_func
(paren
id|req-&gt;dst
)paren
suffix:semicolon
r_if
c_cond
(paren
id|s
)paren
(brace
multiline_comment|/* Wakeup user-space which is polling for socket errors.&n;&t;&t; * This is temporary hack untill we have shutdown in L2CAP */
id|s-&gt;sock-&gt;sk-&gt;err
op_assign
id|EUNATCH
suffix:semicolon
multiline_comment|/* Kill session thread */
id|atomic_inc
c_func
(paren
op_amp
id|s-&gt;killed
)paren
suffix:semicolon
id|wake_up_interruptible
c_func
(paren
id|s-&gt;sock-&gt;sk-&gt;sleep
)paren
suffix:semicolon
)brace
r_else
id|err
op_assign
op_minus
id|ENOENT
suffix:semicolon
id|up_read
c_func
(paren
op_amp
id|bnep_session_sem
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|__bnep_copy_ci
r_static
r_void
id|__bnep_copy_ci
c_func
(paren
r_struct
id|bnep_coninfo
op_star
id|ci
comma
r_struct
id|bnep_session
op_star
id|s
)paren
(brace
id|memcpy
c_func
(paren
id|ci-&gt;dst
comma
id|s-&gt;eh.h_source
comma
id|ETH_ALEN
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|ci-&gt;device
comma
id|s-&gt;dev.name
)paren
suffix:semicolon
id|ci-&gt;flags
op_assign
id|s-&gt;flags
suffix:semicolon
id|ci-&gt;state
op_assign
id|s-&gt;state
suffix:semicolon
id|ci-&gt;role
op_assign
id|s-&gt;role
suffix:semicolon
)brace
DECL|function|bnep_get_conlist
r_int
id|bnep_get_conlist
c_func
(paren
r_struct
id|bnep_conlist_req
op_star
id|req
)paren
(brace
r_struct
id|list_head
op_star
id|p
suffix:semicolon
r_int
id|err
op_assign
l_int|0
comma
id|n
op_assign
l_int|0
suffix:semicolon
id|down_read
c_func
(paren
op_amp
id|bnep_session_sem
)paren
suffix:semicolon
id|list_for_each
c_func
(paren
id|p
comma
op_amp
id|bnep_session_list
)paren
(brace
r_struct
id|bnep_session
op_star
id|s
suffix:semicolon
r_struct
id|bnep_coninfo
id|ci
suffix:semicolon
id|s
op_assign
id|list_entry
c_func
(paren
id|p
comma
r_struct
id|bnep_session
comma
id|list
)paren
suffix:semicolon
id|__bnep_copy_ci
c_func
(paren
op_amp
id|ci
comma
id|s
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|req-&gt;ci
comma
op_amp
id|ci
comma
r_sizeof
(paren
id|ci
)paren
)paren
)paren
(brace
id|err
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
op_increment
id|n
op_ge
id|req-&gt;cnum
)paren
r_break
suffix:semicolon
id|req-&gt;ci
op_increment
suffix:semicolon
)brace
id|req-&gt;cnum
op_assign
id|n
suffix:semicolon
id|up_read
c_func
(paren
op_amp
id|bnep_session_sem
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|bnep_get_coninfo
r_int
id|bnep_get_coninfo
c_func
(paren
r_struct
id|bnep_coninfo
op_star
id|ci
)paren
(brace
r_struct
id|bnep_session
op_star
id|s
suffix:semicolon
r_int
id|err
op_assign
l_int|0
suffix:semicolon
id|down_read
c_func
(paren
op_amp
id|bnep_session_sem
)paren
suffix:semicolon
id|s
op_assign
id|__bnep_get_session
c_func
(paren
id|ci-&gt;dst
)paren
suffix:semicolon
r_if
c_cond
(paren
id|s
)paren
id|__bnep_copy_ci
c_func
(paren
id|ci
comma
id|s
)paren
suffix:semicolon
r_else
id|err
op_assign
op_minus
id|ENOENT
suffix:semicolon
id|up_read
c_func
(paren
op_amp
id|bnep_session_sem
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|bnep_init_module
r_static
r_int
id|__init
id|bnep_init_module
c_func
(paren
r_void
)paren
(brace
r_char
id|flt
(braket
l_int|50
)braket
op_assign
l_string|&quot;&quot;
suffix:semicolon
macro_line|#ifdef CONFIG_BT_BNEP_PROTO_FILTER
id|strcat
c_func
(paren
id|flt
comma
l_string|&quot;protocol &quot;
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_BT_BNEP_MC_FILTER
id|strcat
c_func
(paren
id|flt
comma
l_string|&quot;multicast&quot;
)paren
suffix:semicolon
macro_line|#endif
id|BT_INFO
c_func
(paren
l_string|&quot;BNEP (Ethernet Emulation) ver %s&quot;
comma
id|VERSION
)paren
suffix:semicolon
r_if
c_cond
(paren
id|flt
(braket
l_int|0
)braket
)paren
id|BT_INFO
c_func
(paren
l_string|&quot;BNEP filters: %s&quot;
comma
id|flt
)paren
suffix:semicolon
id|bnep_sock_init
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|bnep_cleanup_module
r_static
r_void
id|__exit
id|bnep_cleanup_module
c_func
(paren
r_void
)paren
(brace
id|bnep_sock_cleanup
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|variable|bnep_init_module
id|module_init
c_func
(paren
id|bnep_init_module
)paren
suffix:semicolon
DECL|variable|bnep_cleanup_module
id|module_exit
c_func
(paren
id|bnep_cleanup_module
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Bluetooth BNEP ver &quot;
id|VERSION
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;David Libault &lt;david.libault@inventel.fr&gt;, Maxim Krasnyanskiy &lt;maxk@qualcomm.com&gt;&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
