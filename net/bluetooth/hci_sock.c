multiline_comment|/* &n;   BlueZ - Bluetooth protocol stack for Linux&n;   Copyright (C) 2000-2001 Qualcomm Incorporated&n;&n;   Written 2000,2001 by Maxim Krasnyansky &lt;maxk@qualcomm.com&gt;&n;&n;   This program is free software; you can redistribute it and/or modify&n;   it under the terms of the GNU General Public License version 2 as&n;   published by the Free Software Foundation;&n;&n;   THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND, EXPRESS&n;   OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,&n;   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT OF THIRD PARTY RIGHTS.&n;   IN NO EVENT SHALL THE COPYRIGHT HOLDER(S) AND AUTHOR(S) BE LIABLE FOR ANY&n;   CLAIM, OR ANY SPECIAL INDIRECT OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES &n;   WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN &n;   ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF &n;   OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.&n;&n;   ALL LIABILITY, INCLUDING LIABILITY FOR INFRINGEMENT OF ANY PATENTS, &n;   COPYRIGHTS, TRADEMARKS OR OTHER RIGHTS, RELATING TO USE OF THIS &n;   SOFTWARE IS DISCLAIMED.&n;*/
multiline_comment|/*&n; * Bluetooth HCI socket layer.&n; *&n; * $Id: hci_sock.c,v 1.4 2002/04/18 22:26:14 maxk Exp $&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/poll.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/workqueue.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/ioctl.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;net/bluetooth/bluetooth.h&gt;
macro_line|#include &lt;net/bluetooth/hci_core.h&gt;
macro_line|#ifndef CONFIG_BT_HCI_SOCK_DEBUG
DECL|macro|BT_DBG
macro_line|#undef  BT_DBG
DECL|macro|BT_DBG
mdefine_line|#define BT_DBG( A... )
macro_line|#endif
multiline_comment|/* ----- HCI socket interface ----- */
multiline_comment|/* Security filter */
DECL|variable|hci_sec_filter
r_static
r_struct
id|hci_sec_filter
id|hci_sec_filter
op_assign
(brace
multiline_comment|/* Packet types */
l_int|0x10
comma
multiline_comment|/* Events */
(brace
l_int|0xd9fe
comma
l_int|0x0
)brace
comma
multiline_comment|/* Commands */
(brace
multiline_comment|/* OGF_LINK_CTL */
(brace
l_int|0x2a000002
comma
l_int|0x0
comma
l_int|0x0
comma
l_int|0x0
)brace
comma
multiline_comment|/* OGF_LINK_POLICY */
(brace
l_int|0x1200
comma
l_int|0x0
comma
l_int|0x0
comma
l_int|0x0
)brace
comma
multiline_comment|/* OGF_HOST_CTL */
(brace
l_int|0x80100000
comma
l_int|0xa
comma
l_int|0x0
comma
l_int|0x0
)brace
comma
multiline_comment|/* OGF_INFO_PARAM */
(brace
l_int|0x22a
comma
l_int|0x0
comma
l_int|0x0
comma
l_int|0x0
)brace
)brace
)brace
suffix:semicolon
DECL|variable|hci_sk_list
r_static
r_struct
id|bt_sock_list
id|hci_sk_list
op_assign
(brace
dot
id|lock
op_assign
id|RW_LOCK_UNLOCKED
)brace
suffix:semicolon
multiline_comment|/* Send frame to RAW socket */
DECL|function|hci_send_to_sock
r_void
id|hci_send_to_sock
c_func
(paren
r_struct
id|hci_dev
op_star
id|hdev
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|sock
op_star
id|sk
suffix:semicolon
id|BT_DBG
c_func
(paren
l_string|&quot;hdev %p len %d&quot;
comma
id|hdev
comma
id|skb-&gt;len
)paren
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|hci_sk_list.lock
)paren
suffix:semicolon
r_for
c_loop
(paren
id|sk
op_assign
id|hci_sk_list.head
suffix:semicolon
id|sk
suffix:semicolon
id|sk
op_assign
id|sk-&gt;next
)paren
(brace
r_struct
id|hci_filter
op_star
id|flt
suffix:semicolon
r_struct
id|sk_buff
op_star
id|nskb
suffix:semicolon
r_if
c_cond
(paren
id|sk-&gt;state
op_ne
id|BT_BOUND
op_logical_or
id|hci_pi
c_func
(paren
id|sk
)paren
op_member_access_from_pointer
id|hdev
op_ne
id|hdev
)paren
r_continue
suffix:semicolon
multiline_comment|/* Don&squot;t send frame to the socket it came from */
r_if
c_cond
(paren
id|skb-&gt;sk
op_eq
id|sk
)paren
r_continue
suffix:semicolon
multiline_comment|/* Apply filter */
id|flt
op_assign
op_amp
id|hci_pi
c_func
(paren
id|sk
)paren
op_member_access_from_pointer
id|filter
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|test_bit
c_func
(paren
(paren
id|skb-&gt;pkt_type
op_amp
id|HCI_FLT_TYPE_BITS
)paren
comma
op_amp
id|flt-&gt;type_mask
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|skb-&gt;pkt_type
op_eq
id|HCI_EVENT_PKT
)paren
(brace
r_register
r_int
id|evt
op_assign
(paren
op_star
(paren
id|__u8
op_star
)paren
id|skb-&gt;data
op_amp
id|HCI_FLT_EVENT_BITS
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|test_bit
c_func
(paren
id|evt
comma
id|flt-&gt;event_mask
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|flt-&gt;opcode
op_logical_and
(paren
(paren
id|evt
op_eq
id|HCI_EV_CMD_COMPLETE
op_logical_and
id|flt-&gt;opcode
op_ne
op_star
(paren
id|__u16
op_star
)paren
(paren
id|skb-&gt;data
op_plus
l_int|3
)paren
)paren
op_logical_or
(paren
id|evt
op_eq
id|HCI_EV_CMD_STATUS
op_logical_and
id|flt-&gt;opcode
op_ne
op_star
(paren
id|__u16
op_star
)paren
(paren
id|skb-&gt;data
op_plus
l_int|4
)paren
)paren
)paren
)paren
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|nskb
op_assign
id|skb_clone
c_func
(paren
id|skb
comma
id|GFP_ATOMIC
)paren
)paren
)paren
r_continue
suffix:semicolon
multiline_comment|/* Put type byte before the data */
id|memcpy
c_func
(paren
id|skb_push
c_func
(paren
id|nskb
comma
l_int|1
)paren
comma
op_amp
id|nskb-&gt;pkt_type
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sock_queue_rcv_skb
c_func
(paren
id|sk
comma
id|nskb
)paren
)paren
id|kfree_skb
c_func
(paren
id|nskb
)paren
suffix:semicolon
)brace
id|read_unlock
c_func
(paren
op_amp
id|hci_sk_list.lock
)paren
suffix:semicolon
)brace
DECL|function|hci_sock_release
r_static
r_int
id|hci_sock_release
c_func
(paren
r_struct
id|socket
op_star
id|sock
)paren
(brace
r_struct
id|sock
op_star
id|sk
op_assign
id|sock-&gt;sk
suffix:semicolon
r_struct
id|hci_dev
op_star
id|hdev
op_assign
id|hci_pi
c_func
(paren
id|sk
)paren
op_member_access_from_pointer
id|hdev
suffix:semicolon
id|BT_DBG
c_func
(paren
l_string|&quot;sock %p sk %p&quot;
comma
id|sock
comma
id|sk
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sk
)paren
r_return
l_int|0
suffix:semicolon
id|bt_sock_unlink
c_func
(paren
op_amp
id|hci_sk_list
comma
id|sk
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hdev
)paren
(brace
id|atomic_dec
c_func
(paren
op_amp
id|hdev-&gt;promisc
)paren
suffix:semicolon
id|hci_dev_put
c_func
(paren
id|hdev
)paren
suffix:semicolon
)brace
id|sock_orphan
c_func
(paren
id|sk
)paren
suffix:semicolon
id|skb_queue_purge
c_func
(paren
op_amp
id|sk-&gt;receive_queue
)paren
suffix:semicolon
id|skb_queue_purge
c_func
(paren
op_amp
id|sk-&gt;write_queue
)paren
suffix:semicolon
id|sock_put
c_func
(paren
id|sk
)paren
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Ioctls that require bound socket */
DECL|function|hci_sock_bound_ioctl
r_static
r_inline
r_int
id|hci_sock_bound_ioctl
c_func
(paren
r_struct
id|sock
op_star
id|sk
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
r_struct
id|hci_dev
op_star
id|hdev
op_assign
id|hci_pi
c_func
(paren
id|sk
)paren
op_member_access_from_pointer
id|hdev
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hdev
)paren
r_return
op_minus
id|EBADFD
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|HCISETRAW
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_NET_ADMIN
)paren
)paren
r_return
op_minus
id|EACCES
suffix:semicolon
r_if
c_cond
(paren
id|arg
)paren
id|set_bit
c_func
(paren
id|HCI_RAW
comma
op_amp
id|hdev-&gt;flags
)paren
suffix:semicolon
r_else
id|clear_bit
c_func
(paren
id|HCI_RAW
comma
op_amp
id|hdev-&gt;flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|HCIGETCONNINFO
suffix:colon
r_return
id|hci_get_conn_info
c_func
(paren
id|hdev
comma
id|arg
)paren
suffix:semicolon
r_default
suffix:colon
(brace
)brace
r_if
c_cond
(paren
id|hdev-&gt;ioctl
)paren
r_return
id|hdev
op_member_access_from_pointer
id|ioctl
c_func
(paren
id|hdev
comma
id|cmd
comma
id|arg
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
)brace
DECL|function|hci_sock_ioctl
r_static
r_int
id|hci_sock_ioctl
c_func
(paren
r_struct
id|socket
op_star
id|sock
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
r_struct
id|sock
op_star
id|sk
op_assign
id|sock-&gt;sk
suffix:semicolon
r_int
id|err
suffix:semicolon
id|BT_DBG
c_func
(paren
l_string|&quot;cmd %x arg %lx&quot;
comma
id|cmd
comma
id|arg
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|HCIGETDEVLIST
suffix:colon
r_return
id|hci_get_dev_list
c_func
(paren
id|arg
)paren
suffix:semicolon
r_case
id|HCIGETDEVINFO
suffix:colon
r_return
id|hci_get_dev_info
c_func
(paren
id|arg
)paren
suffix:semicolon
r_case
id|HCIGETCONNLIST
suffix:colon
r_return
id|hci_get_conn_list
c_func
(paren
id|arg
)paren
suffix:semicolon
r_case
id|HCIDEVUP
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_NET_ADMIN
)paren
)paren
r_return
op_minus
id|EACCES
suffix:semicolon
r_return
id|hci_dev_open
c_func
(paren
id|arg
)paren
suffix:semicolon
r_case
id|HCIDEVDOWN
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_NET_ADMIN
)paren
)paren
r_return
op_minus
id|EACCES
suffix:semicolon
r_return
id|hci_dev_close
c_func
(paren
id|arg
)paren
suffix:semicolon
r_case
id|HCIDEVRESET
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_NET_ADMIN
)paren
)paren
r_return
op_minus
id|EACCES
suffix:semicolon
r_return
id|hci_dev_reset
c_func
(paren
id|arg
)paren
suffix:semicolon
r_case
id|HCIDEVRESTAT
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_NET_ADMIN
)paren
)paren
r_return
op_minus
id|EACCES
suffix:semicolon
r_return
id|hci_dev_reset_stat
c_func
(paren
id|arg
)paren
suffix:semicolon
r_case
id|HCISETSCAN
suffix:colon
r_case
id|HCISETAUTH
suffix:colon
r_case
id|HCISETENCRYPT
suffix:colon
r_case
id|HCISETPTYPE
suffix:colon
r_case
id|HCISETLINKPOL
suffix:colon
r_case
id|HCISETLINKMODE
suffix:colon
r_case
id|HCISETACLMTU
suffix:colon
r_case
id|HCISETSCOMTU
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_NET_ADMIN
)paren
)paren
r_return
op_minus
id|EACCES
suffix:semicolon
r_return
id|hci_dev_cmd
c_func
(paren
id|cmd
comma
id|arg
)paren
suffix:semicolon
r_case
id|HCIINQUIRY
suffix:colon
r_return
id|hci_inquiry
c_func
(paren
id|arg
)paren
suffix:semicolon
r_default
suffix:colon
id|lock_sock
c_func
(paren
id|sk
)paren
suffix:semicolon
id|err
op_assign
id|hci_sock_bound_ioctl
c_func
(paren
id|sk
comma
id|cmd
comma
id|arg
)paren
suffix:semicolon
id|release_sock
c_func
(paren
id|sk
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
)brace
DECL|function|hci_sock_bind
r_static
r_int
id|hci_sock_bind
c_func
(paren
r_struct
id|socket
op_star
id|sock
comma
r_struct
id|sockaddr
op_star
id|addr
comma
r_int
id|addr_len
)paren
(brace
r_struct
id|sockaddr_hci
op_star
id|haddr
op_assign
(paren
r_struct
id|sockaddr_hci
op_star
)paren
id|addr
suffix:semicolon
r_struct
id|sock
op_star
id|sk
op_assign
id|sock-&gt;sk
suffix:semicolon
r_struct
id|hci_dev
op_star
id|hdev
op_assign
l_int|NULL
suffix:semicolon
r_int
id|err
op_assign
l_int|0
suffix:semicolon
id|BT_DBG
c_func
(paren
l_string|&quot;sock %p sk %p&quot;
comma
id|sock
comma
id|sk
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|haddr
op_logical_or
id|haddr-&gt;hci_family
op_ne
id|AF_BLUETOOTH
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|lock_sock
c_func
(paren
id|sk
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hci_pi
c_func
(paren
id|sk
)paren
op_member_access_from_pointer
id|hdev
)paren
(brace
id|err
op_assign
op_minus
id|EALREADY
suffix:semicolon
r_goto
id|done
suffix:semicolon
)brace
r_if
c_cond
(paren
id|haddr-&gt;hci_dev
op_ne
id|HCI_DEV_NONE
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|hdev
op_assign
id|hci_dev_get
c_func
(paren
id|haddr-&gt;hci_dev
)paren
)paren
)paren
(brace
id|err
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_goto
id|done
suffix:semicolon
)brace
id|atomic_inc
c_func
(paren
op_amp
id|hdev-&gt;promisc
)paren
suffix:semicolon
)brace
id|hci_pi
c_func
(paren
id|sk
)paren
op_member_access_from_pointer
id|hdev
op_assign
id|hdev
suffix:semicolon
id|sk-&gt;state
op_assign
id|BT_BOUND
suffix:semicolon
id|done
suffix:colon
id|release_sock
c_func
(paren
id|sk
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|hci_sock_getname
r_static
r_int
id|hci_sock_getname
c_func
(paren
r_struct
id|socket
op_star
id|sock
comma
r_struct
id|sockaddr
op_star
id|addr
comma
r_int
op_star
id|addr_len
comma
r_int
id|peer
)paren
(brace
r_struct
id|sockaddr_hci
op_star
id|haddr
op_assign
(paren
r_struct
id|sockaddr_hci
op_star
)paren
id|addr
suffix:semicolon
r_struct
id|sock
op_star
id|sk
op_assign
id|sock-&gt;sk
suffix:semicolon
id|BT_DBG
c_func
(paren
l_string|&quot;sock %p sk %p&quot;
comma
id|sock
comma
id|sk
)paren
suffix:semicolon
id|lock_sock
c_func
(paren
id|sk
)paren
suffix:semicolon
op_star
id|addr_len
op_assign
r_sizeof
(paren
op_star
id|haddr
)paren
suffix:semicolon
id|haddr-&gt;hci_family
op_assign
id|AF_BLUETOOTH
suffix:semicolon
id|haddr-&gt;hci_dev
op_assign
id|hci_pi
c_func
(paren
id|sk
)paren
op_member_access_from_pointer
id|hdev-&gt;id
suffix:semicolon
id|release_sock
c_func
(paren
id|sk
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|hci_sock_cmsg
r_static
r_inline
r_void
id|hci_sock_cmsg
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_struct
id|msghdr
op_star
id|msg
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
id|__u32
id|mask
op_assign
id|hci_pi
c_func
(paren
id|sk
)paren
op_member_access_from_pointer
id|cmsg_mask
suffix:semicolon
r_if
c_cond
(paren
id|mask
op_amp
id|HCI_CMSG_DIR
)paren
id|put_cmsg
c_func
(paren
id|msg
comma
id|SOL_HCI
comma
id|HCI_CMSG_DIR
comma
r_sizeof
(paren
r_int
)paren
comma
op_amp
id|bt_cb
c_func
(paren
id|skb
)paren
op_member_access_from_pointer
id|incoming
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mask
op_amp
id|HCI_CMSG_TSTAMP
)paren
id|put_cmsg
c_func
(paren
id|msg
comma
id|SOL_HCI
comma
id|HCI_CMSG_TSTAMP
comma
r_sizeof
(paren
id|skb-&gt;stamp
)paren
comma
op_amp
id|skb-&gt;stamp
)paren
suffix:semicolon
)brace
DECL|function|hci_sock_recvmsg
r_static
r_int
id|hci_sock_recvmsg
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
comma
r_struct
id|scm_cookie
op_star
id|scm
)paren
(brace
r_int
id|noblock
op_assign
id|flags
op_amp
id|MSG_DONTWAIT
suffix:semicolon
r_struct
id|sock
op_star
id|sk
op_assign
id|sock-&gt;sk
suffix:semicolon
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
r_int
id|copied
comma
id|err
suffix:semicolon
id|BT_DBG
c_func
(paren
l_string|&quot;sock %p, sk %p&quot;
comma
id|sock
comma
id|sk
)paren
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
(paren
id|MSG_OOB
)paren
)paren
r_return
op_minus
id|EOPNOTSUPP
suffix:semicolon
r_if
c_cond
(paren
id|sk-&gt;state
op_eq
id|BT_CLOSED
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|skb
op_assign
id|skb_recv_datagram
c_func
(paren
id|sk
comma
id|flags
comma
id|noblock
comma
op_amp
id|err
)paren
)paren
)paren
r_return
id|err
suffix:semicolon
id|msg-&gt;msg_namelen
op_assign
l_int|0
suffix:semicolon
id|copied
op_assign
id|skb-&gt;len
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
id|copied
)paren
(brace
id|msg-&gt;msg_flags
op_or_assign
id|MSG_TRUNC
suffix:semicolon
id|copied
op_assign
id|len
suffix:semicolon
)brace
id|skb-&gt;h.raw
op_assign
id|skb-&gt;data
suffix:semicolon
id|err
op_assign
id|skb_copy_datagram_iovec
c_func
(paren
id|skb
comma
l_int|0
comma
id|msg-&gt;msg_iov
comma
id|copied
)paren
suffix:semicolon
id|hci_sock_cmsg
c_func
(paren
id|sk
comma
id|msg
comma
id|skb
)paren
suffix:semicolon
id|skb_free_datagram
c_func
(paren
id|sk
comma
id|skb
)paren
suffix:semicolon
r_return
id|err
ques
c_cond
suffix:colon
id|copied
suffix:semicolon
)brace
DECL|function|hci_sock_sendmsg
r_static
r_int
id|hci_sock_sendmsg
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
r_struct
id|scm_cookie
op_star
id|scm
)paren
(brace
r_struct
id|sock
op_star
id|sk
op_assign
id|sock-&gt;sk
suffix:semicolon
r_struct
id|hci_dev
op_star
id|hdev
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
l_string|&quot;sock %p sk %p&quot;
comma
id|sock
comma
id|sk
)paren
suffix:semicolon
r_if
c_cond
(paren
id|msg-&gt;msg_flags
op_amp
id|MSG_OOB
)paren
r_return
op_minus
id|EOPNOTSUPP
suffix:semicolon
r_if
c_cond
(paren
id|msg-&gt;msg_flags
op_amp
op_complement
(paren
id|MSG_DONTWAIT
op_or
id|MSG_NOSIGNAL
op_or
id|MSG_ERRQUEUE
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
l_int|4
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|lock_sock
c_func
(paren
id|sk
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|hdev
op_assign
id|hci_pi
c_func
(paren
id|sk
)paren
op_member_access_from_pointer
id|hdev
)paren
)paren
(brace
id|err
op_assign
op_minus
id|EBADFD
suffix:semicolon
r_goto
id|done
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|skb
op_assign
id|bt_skb_send_alloc
c_func
(paren
id|sk
comma
id|len
comma
id|msg-&gt;msg_flags
op_amp
id|MSG_DONTWAIT
comma
op_amp
id|err
)paren
)paren
)paren
r_goto
id|done
suffix:semicolon
r_if
c_cond
(paren
id|memcpy_fromiovec
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
id|msg-&gt;msg_iov
comma
id|len
)paren
)paren
(brace
id|err
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_goto
id|drop
suffix:semicolon
)brace
id|skb-&gt;pkt_type
op_assign
op_star
(paren
(paren
r_int
r_char
op_star
)paren
id|skb-&gt;data
)paren
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
op_logical_neg
id|capable
c_func
(paren
id|CAP_NET_RAW
)paren
)paren
(brace
id|err
op_assign
op_minus
id|EPERM
suffix:semicolon
r_if
c_cond
(paren
id|skb-&gt;pkt_type
op_eq
id|HCI_COMMAND_PKT
)paren
(brace
id|u16
id|opcode
op_assign
id|__le16_to_cpu
c_func
(paren
op_star
(paren
id|__u16
op_star
)paren
id|skb-&gt;data
)paren
suffix:semicolon
id|u16
id|ogf
op_assign
id|hci_opcode_ogf
c_func
(paren
id|opcode
)paren
op_minus
l_int|1
suffix:semicolon
id|u16
id|ocf
op_assign
id|hci_opcode_ocf
c_func
(paren
id|opcode
)paren
op_amp
id|HCI_FLT_OCF_BITS
suffix:semicolon
r_if
c_cond
(paren
id|ogf
OG
id|HCI_SFLT_MAX_OGF
op_logical_or
op_logical_neg
id|test_bit
c_func
(paren
id|ocf
comma
id|hci_sec_filter.ocf_mask
(braket
id|ogf
)braket
)paren
)paren
r_goto
id|drop
suffix:semicolon
)brace
r_else
r_goto
id|drop
suffix:semicolon
)brace
multiline_comment|/* Send frame to HCI core */
id|skb-&gt;dev
op_assign
(paren
r_void
op_star
)paren
id|hdev
suffix:semicolon
id|hci_send_raw
c_func
(paren
id|skb
)paren
suffix:semicolon
id|err
op_assign
id|len
suffix:semicolon
id|done
suffix:colon
id|release_sock
c_func
(paren
id|sk
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
id|drop
suffix:colon
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_goto
id|done
suffix:semicolon
)brace
DECL|function|hci_sock_setsockopt
r_int
id|hci_sock_setsockopt
c_func
(paren
r_struct
id|socket
op_star
id|sock
comma
r_int
id|level
comma
r_int
id|optname
comma
r_char
op_star
id|optval
comma
r_int
id|len
)paren
(brace
r_struct
id|hci_ufilter
id|uf
op_assign
(brace
dot
id|opcode
op_assign
l_int|0
)brace
suffix:semicolon
r_struct
id|sock
op_star
id|sk
op_assign
id|sock-&gt;sk
suffix:semicolon
r_int
id|err
op_assign
l_int|0
comma
id|opt
op_assign
l_int|0
suffix:semicolon
id|BT_DBG
c_func
(paren
l_string|&quot;sk %p, opt %d&quot;
comma
id|sk
comma
id|optname
)paren
suffix:semicolon
id|lock_sock
c_func
(paren
id|sk
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|optname
)paren
(brace
r_case
id|HCI_DATA_DIR
suffix:colon
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|opt
comma
(paren
r_int
op_star
)paren
id|optval
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
id|opt
)paren
id|hci_pi
c_func
(paren
id|sk
)paren
op_member_access_from_pointer
id|cmsg_mask
op_or_assign
id|HCI_CMSG_DIR
suffix:semicolon
r_else
id|hci_pi
c_func
(paren
id|sk
)paren
op_member_access_from_pointer
id|cmsg_mask
op_and_assign
op_complement
id|HCI_CMSG_DIR
suffix:semicolon
r_break
suffix:semicolon
r_case
id|HCI_TIME_STAMP
suffix:colon
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|opt
comma
(paren
r_int
op_star
)paren
id|optval
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
id|opt
)paren
id|hci_pi
c_func
(paren
id|sk
)paren
op_member_access_from_pointer
id|cmsg_mask
op_or_assign
id|HCI_CMSG_TSTAMP
suffix:semicolon
r_else
id|hci_pi
c_func
(paren
id|sk
)paren
op_member_access_from_pointer
id|cmsg_mask
op_and_assign
op_complement
id|HCI_CMSG_TSTAMP
suffix:semicolon
r_break
suffix:semicolon
r_case
id|HCI_FILTER
suffix:colon
id|len
op_assign
id|min_t
c_func
(paren
r_int
r_int
comma
id|len
comma
r_sizeof
(paren
id|uf
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|uf
comma
id|optval
comma
id|len
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
op_logical_neg
id|capable
c_func
(paren
id|CAP_NET_RAW
)paren
)paren
(brace
id|uf.type_mask
op_and_assign
id|hci_sec_filter.type_mask
suffix:semicolon
id|uf.event_mask
(braket
l_int|0
)braket
op_and_assign
op_star
(paren
(paren
id|u32
op_star
)paren
id|hci_sec_filter.event_mask
op_plus
l_int|0
)paren
suffix:semicolon
id|uf.event_mask
(braket
l_int|1
)braket
op_and_assign
op_star
(paren
(paren
id|u32
op_star
)paren
id|hci_sec_filter.event_mask
op_plus
l_int|1
)paren
suffix:semicolon
)brace
(brace
r_struct
id|hci_filter
op_star
id|f
op_assign
op_amp
id|hci_pi
c_func
(paren
id|sk
)paren
op_member_access_from_pointer
id|filter
suffix:semicolon
id|f-&gt;type_mask
op_assign
id|uf.type_mask
suffix:semicolon
id|f-&gt;opcode
op_assign
id|uf.opcode
suffix:semicolon
op_star
(paren
(paren
id|u32
op_star
)paren
id|f-&gt;event_mask
op_plus
l_int|0
)paren
op_assign
id|uf.event_mask
(braket
l_int|0
)braket
suffix:semicolon
op_star
(paren
(paren
id|u32
op_star
)paren
id|f-&gt;event_mask
op_plus
l_int|1
)paren
op_assign
id|uf.event_mask
(braket
l_int|1
)braket
suffix:semicolon
)brace
r_break
suffix:semicolon
r_default
suffix:colon
id|err
op_assign
op_minus
id|ENOPROTOOPT
suffix:semicolon
r_break
suffix:semicolon
)brace
id|release_sock
c_func
(paren
id|sk
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|hci_sock_getsockopt
r_int
id|hci_sock_getsockopt
c_func
(paren
r_struct
id|socket
op_star
id|sock
comma
r_int
id|level
comma
r_int
id|optname
comma
r_char
op_star
id|optval
comma
r_int
op_star
id|optlen
)paren
(brace
r_struct
id|hci_ufilter
id|uf
suffix:semicolon
r_struct
id|sock
op_star
id|sk
op_assign
id|sock-&gt;sk
suffix:semicolon
r_int
id|len
comma
id|opt
suffix:semicolon
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|len
comma
id|optlen
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_switch
c_cond
(paren
id|optname
)paren
(brace
r_case
id|HCI_DATA_DIR
suffix:colon
r_if
c_cond
(paren
id|hci_pi
c_func
(paren
id|sk
)paren
op_member_access_from_pointer
id|cmsg_mask
op_amp
id|HCI_CMSG_DIR
)paren
id|opt
op_assign
l_int|1
suffix:semicolon
r_else
id|opt
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|put_user
c_func
(paren
id|opt
comma
id|optval
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_break
suffix:semicolon
r_case
id|HCI_TIME_STAMP
suffix:colon
r_if
c_cond
(paren
id|hci_pi
c_func
(paren
id|sk
)paren
op_member_access_from_pointer
id|cmsg_mask
op_amp
id|HCI_CMSG_TSTAMP
)paren
id|opt
op_assign
l_int|1
suffix:semicolon
r_else
id|opt
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|put_user
c_func
(paren
id|opt
comma
id|optval
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_break
suffix:semicolon
r_case
id|HCI_FILTER
suffix:colon
(brace
r_struct
id|hci_filter
op_star
id|f
op_assign
op_amp
id|hci_pi
c_func
(paren
id|sk
)paren
op_member_access_from_pointer
id|filter
suffix:semicolon
id|uf.type_mask
op_assign
id|f-&gt;type_mask
suffix:semicolon
id|uf.opcode
op_assign
id|f-&gt;opcode
suffix:semicolon
id|uf.event_mask
(braket
l_int|0
)braket
op_assign
op_star
(paren
(paren
id|u32
op_star
)paren
id|f-&gt;event_mask
op_plus
l_int|0
)paren
suffix:semicolon
id|uf.event_mask
(braket
l_int|1
)braket
op_assign
op_star
(paren
(paren
id|u32
op_star
)paren
id|f-&gt;event_mask
op_plus
l_int|1
)paren
suffix:semicolon
)brace
id|len
op_assign
id|min_t
c_func
(paren
r_int
r_int
comma
id|len
comma
r_sizeof
(paren
id|uf
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|optval
comma
op_amp
id|uf
comma
id|len
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|ENOPROTOOPT
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|hci_sock_ops
r_struct
id|proto_ops
id|hci_sock_ops
op_assign
(brace
dot
id|family
op_assign
id|PF_BLUETOOTH
comma
dot
id|release
op_assign
id|hci_sock_release
comma
dot
id|bind
op_assign
id|hci_sock_bind
comma
dot
id|getname
op_assign
id|hci_sock_getname
comma
dot
id|sendmsg
op_assign
id|hci_sock_sendmsg
comma
dot
id|recvmsg
op_assign
id|hci_sock_recvmsg
comma
dot
id|ioctl
op_assign
id|hci_sock_ioctl
comma
dot
id|poll
op_assign
id|datagram_poll
comma
dot
id|listen
op_assign
id|sock_no_listen
comma
dot
id|shutdown
op_assign
id|sock_no_shutdown
comma
dot
id|setsockopt
op_assign
id|hci_sock_setsockopt
comma
dot
id|getsockopt
op_assign
id|hci_sock_getsockopt
comma
dot
id|connect
op_assign
id|sock_no_connect
comma
dot
id|socketpair
op_assign
id|sock_no_socketpair
comma
dot
id|accept
op_assign
id|sock_no_accept
comma
dot
id|mmap
op_assign
id|sock_no_mmap
)brace
suffix:semicolon
DECL|function|hci_sock_create
r_static
r_int
id|hci_sock_create
c_func
(paren
r_struct
id|socket
op_star
id|sock
comma
r_int
id|protocol
)paren
(brace
r_struct
id|sock
op_star
id|sk
suffix:semicolon
id|BT_DBG
c_func
(paren
l_string|&quot;sock %p&quot;
comma
id|sock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sock-&gt;type
op_ne
id|SOCK_RAW
)paren
r_return
op_minus
id|ESOCKTNOSUPPORT
suffix:semicolon
id|sock-&gt;ops
op_assign
op_amp
id|hci_sock_ops
suffix:semicolon
id|sk
op_assign
id|bt_sock_alloc
c_func
(paren
id|sock
comma
id|protocol
comma
r_sizeof
(paren
r_struct
id|hci_pinfo
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sk
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|sock-&gt;state
op_assign
id|SS_UNCONNECTED
suffix:semicolon
id|sk-&gt;state
op_assign
id|BT_OPEN
suffix:semicolon
id|bt_sock_link
c_func
(paren
op_amp
id|hci_sk_list
comma
id|sk
)paren
suffix:semicolon
id|MOD_INC_USE_COUNT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|hci_sock_dev_event
r_static
r_int
id|hci_sock_dev_event
c_func
(paren
r_struct
id|notifier_block
op_star
id|this
comma
r_int
r_int
id|event
comma
r_void
op_star
id|ptr
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
id|ptr
suffix:semicolon
r_struct
id|hci_ev_si_device
id|ev
suffix:semicolon
id|BT_DBG
c_func
(paren
l_string|&quot;hdev %s event %ld&quot;
comma
id|hdev-&gt;name
comma
id|event
)paren
suffix:semicolon
multiline_comment|/* Send event to sockets */
id|ev.event
op_assign
id|event
suffix:semicolon
id|ev.dev_id
op_assign
id|hdev-&gt;id
suffix:semicolon
id|hci_si_event
c_func
(paren
l_int|NULL
comma
id|HCI_EV_SI_DEVICE
comma
r_sizeof
(paren
id|ev
)paren
comma
op_amp
id|ev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|event
op_eq
id|HCI_DEV_UNREG
)paren
(brace
r_struct
id|sock
op_star
id|sk
suffix:semicolon
multiline_comment|/* Detach sockets from device */
id|read_lock
c_func
(paren
op_amp
id|hci_sk_list.lock
)paren
suffix:semicolon
r_for
c_loop
(paren
id|sk
op_assign
id|hci_sk_list.head
suffix:semicolon
id|sk
suffix:semicolon
id|sk
op_assign
id|sk-&gt;next
)paren
(brace
id|bh_lock_sock
c_func
(paren
id|sk
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hci_pi
c_func
(paren
id|sk
)paren
op_member_access_from_pointer
id|hdev
op_eq
id|hdev
)paren
(brace
id|hci_pi
c_func
(paren
id|sk
)paren
op_member_access_from_pointer
id|hdev
op_assign
l_int|NULL
suffix:semicolon
id|sk-&gt;err
op_assign
id|EPIPE
suffix:semicolon
id|sk-&gt;state
op_assign
id|BT_OPEN
suffix:semicolon
id|sk
op_member_access_from_pointer
id|state_change
c_func
(paren
id|sk
)paren
suffix:semicolon
id|hci_dev_put
c_func
(paren
id|hdev
)paren
suffix:semicolon
)brace
id|bh_unlock_sock
c_func
(paren
id|sk
)paren
suffix:semicolon
)brace
id|read_unlock
c_func
(paren
op_amp
id|hci_sk_list.lock
)paren
suffix:semicolon
)brace
r_return
id|NOTIFY_DONE
suffix:semicolon
)brace
DECL|variable|hci_sock_family_ops
r_struct
id|net_proto_family
id|hci_sock_family_ops
op_assign
(brace
dot
id|family
op_assign
id|PF_BLUETOOTH
comma
dot
id|create
op_assign
id|hci_sock_create
)brace
suffix:semicolon
DECL|variable|hci_sock_nblock
r_struct
id|notifier_block
id|hci_sock_nblock
op_assign
(brace
dot
id|notifier_call
op_assign
id|hci_sock_dev_event
)brace
suffix:semicolon
DECL|function|hci_sock_init
r_int
id|hci_sock_init
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|bt_sock_register
c_func
(paren
id|BTPROTO_HCI
comma
op_amp
id|hci_sock_family_ops
)paren
)paren
(brace
id|BT_ERR
c_func
(paren
l_string|&quot;HCI socket registration failed&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EPROTO
suffix:semicolon
)brace
id|hci_register_notifier
c_func
(paren
op_amp
id|hci_sock_nblock
)paren
suffix:semicolon
id|BT_INFO
c_func
(paren
l_string|&quot;HCI socket layer initialized&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|hci_sock_cleanup
r_int
id|hci_sock_cleanup
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|bt_sock_unregister
c_func
(paren
id|BTPROTO_HCI
)paren
)paren
id|BT_ERR
c_func
(paren
l_string|&quot;HCI socket unregistration failed&quot;
)paren
suffix:semicolon
id|hci_unregister_notifier
c_func
(paren
op_amp
id|hci_sock_nblock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
