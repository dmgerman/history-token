multiline_comment|/* &n;   BlueZ - Bluetooth protocol stack for Linux&n;   Copyright (C) 2000-2001 Qualcomm Incorporated&n;&n;   Written 2000,2001 by Maxim Krasnyansky &lt;maxk@qualcomm.com&gt;&n;&n;   This program is free software; you can redistribute it and/or modify&n;   it under the terms of the GNU General Public License version 2 as&n;   published by the Free Software Foundation;&n;&n;   THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND, EXPRESS&n;   OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,&n;   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT OF THIRD PARTY RIGHTS.&n;   IN NO EVENT SHALL THE COPYRIGHT HOLDER(S) AND AUTHOR(S) BE LIABLE FOR ANY&n;   CLAIM, OR ANY SPECIAL INDIRECT OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES &n;   WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN &n;   ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF &n;   OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.&n;&n;   ALL LIABILITY, INCLUDING LIABILITY FOR INFRINGEMENT OF ANY PATENTS, &n;   COPYRIGHTS, TRADEMARKS OR OTHER RIGHTS, RELATING TO USE OF THIS &n;   SOFTWARE IS DISCLAIMED.&n;*/
multiline_comment|/*&n; *  Bluetooth address family and sockets.&n; *&n; * $Id: af_bluetooth.c,v 1.3 2002/04/17 17:37:15 maxk Exp $&n; */
DECL|macro|VERSION
mdefine_line|#define VERSION &quot;2.4&quot;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/poll.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#if defined(CONFIG_KMOD)
macro_line|#include &lt;linux/kmod.h&gt;
macro_line|#endif
macro_line|#include &lt;net/bluetooth/bluetooth.h&gt;
macro_line|#ifndef CONFIG_BT_SOCK_DEBUG
DECL|macro|BT_DBG
macro_line|#undef  BT_DBG
DECL|macro|BT_DBG
mdefine_line|#define BT_DBG( A... )
macro_line|#endif
DECL|variable|proc_bt
r_struct
id|proc_dir_entry
op_star
id|proc_bt
suffix:semicolon
multiline_comment|/* Bluetooth sockets */
DECL|macro|BT_MAX_PROTO
mdefine_line|#define BT_MAX_PROTO&t;6
DECL|variable|bt_proto
r_static
r_struct
id|net_proto_family
op_star
id|bt_proto
(braket
id|BT_MAX_PROTO
)braket
suffix:semicolon
DECL|variable|bt_sock_cache
r_static
id|kmem_cache_t
op_star
id|bt_sock_cache
suffix:semicolon
DECL|function|bt_sock_register
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
(brace
r_if
c_cond
(paren
id|proto
op_ge
id|BT_MAX_PROTO
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|bt_proto
(braket
id|proto
)braket
)paren
r_return
op_minus
id|EEXIST
suffix:semicolon
id|bt_proto
(braket
id|proto
)braket
op_assign
id|ops
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|bt_sock_unregister
r_int
id|bt_sock_unregister
c_func
(paren
r_int
id|proto
)paren
(brace
r_if
c_cond
(paren
id|proto
op_ge
id|BT_MAX_PROTO
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bt_proto
(braket
id|proto
)braket
)paren
r_return
op_minus
id|ENOENT
suffix:semicolon
id|bt_proto
(braket
id|proto
)braket
op_assign
l_int|NULL
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|bt_sock_create
r_static
r_int
id|bt_sock_create
c_func
(paren
r_struct
id|socket
op_star
id|sock
comma
r_int
id|proto
)paren
(brace
r_int
id|err
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|proto
op_ge
id|BT_MAX_PROTO
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
macro_line|#if defined(CONFIG_KMOD)
r_if
c_cond
(paren
op_logical_neg
id|bt_proto
(braket
id|proto
)braket
)paren
(brace
id|request_module
c_func
(paren
l_string|&quot;bt-proto-%d&quot;
comma
id|proto
)paren
suffix:semicolon
)brace
macro_line|#endif
id|err
op_assign
op_minus
id|EPROTONOSUPPORT
suffix:semicolon
r_if
c_cond
(paren
id|bt_proto
(braket
id|proto
)braket
op_logical_and
id|try_module_get
c_func
(paren
id|bt_proto
(braket
id|proto
)braket
op_member_access_from_pointer
id|owner
)paren
)paren
(brace
id|err
op_assign
id|bt_proto
(braket
id|proto
)braket
op_member_access_from_pointer
id|create
c_func
(paren
id|sock
comma
id|proto
)paren
suffix:semicolon
id|module_put
c_func
(paren
id|bt_proto
(braket
id|proto
)braket
op_member_access_from_pointer
id|owner
)paren
suffix:semicolon
)brace
r_return
id|err
suffix:semicolon
)brace
DECL|function|bt_sock_alloc
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
(brace
r_struct
id|sock
op_star
id|sk
suffix:semicolon
r_void
op_star
id|pi
suffix:semicolon
id|sk
op_assign
id|sk_alloc
c_func
(paren
id|PF_BLUETOOTH
comma
id|prio
comma
r_sizeof
(paren
r_struct
id|bt_sock
)paren
comma
id|bt_sock_cache
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sk
)paren
r_return
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|pi_size
)paren
(brace
id|pi
op_assign
id|kmalloc
c_func
(paren
id|pi_size
comma
id|prio
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pi
)paren
(brace
id|sk_free
c_func
(paren
id|sk
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|memset
c_func
(paren
id|pi
comma
l_int|0
comma
id|pi_size
)paren
suffix:semicolon
id|sk-&gt;sk_protinfo
op_assign
id|pi
suffix:semicolon
)brace
id|sock_init_data
c_func
(paren
id|sock
comma
id|sk
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|bt_sk
c_func
(paren
id|sk
)paren
op_member_access_from_pointer
id|accept_q
)paren
suffix:semicolon
id|sk-&gt;sk_zapped
op_assign
l_int|0
suffix:semicolon
id|sk-&gt;sk_protocol
op_assign
id|proto
suffix:semicolon
id|sk-&gt;sk_state
op_assign
id|BT_OPEN
suffix:semicolon
r_return
id|sk
suffix:semicolon
)brace
DECL|function|bt_sock_link
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
id|sk
)paren
(brace
id|write_lock_bh
c_func
(paren
op_amp
id|l-&gt;lock
)paren
suffix:semicolon
id|sk_add_node
c_func
(paren
id|sk
comma
op_amp
id|l-&gt;head
)paren
suffix:semicolon
id|write_unlock_bh
c_func
(paren
op_amp
id|l-&gt;lock
)paren
suffix:semicolon
)brace
DECL|function|bt_sock_unlink
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
id|sk
)paren
(brace
id|write_lock_bh
c_func
(paren
op_amp
id|l-&gt;lock
)paren
suffix:semicolon
id|sk_del_node_init
c_func
(paren
id|sk
)paren
suffix:semicolon
id|write_unlock_bh
c_func
(paren
op_amp
id|l-&gt;lock
)paren
suffix:semicolon
)brace
DECL|function|bt_accept_enqueue
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
(brace
id|BT_DBG
c_func
(paren
l_string|&quot;parent %p, sk %p&quot;
comma
id|parent
comma
id|sk
)paren
suffix:semicolon
id|sock_hold
c_func
(paren
id|sk
)paren
suffix:semicolon
id|list_add_tail
c_func
(paren
op_amp
id|bt_sk
c_func
(paren
id|sk
)paren
op_member_access_from_pointer
id|accept_q
comma
op_amp
id|bt_sk
c_func
(paren
id|parent
)paren
op_member_access_from_pointer
id|accept_q
)paren
suffix:semicolon
id|bt_sk
c_func
(paren
id|sk
)paren
op_member_access_from_pointer
id|parent
op_assign
id|parent
suffix:semicolon
id|parent-&gt;sk_ack_backlog
op_increment
suffix:semicolon
)brace
DECL|function|bt_accept_unlink
r_static
r_void
id|bt_accept_unlink
c_func
(paren
r_struct
id|sock
op_star
id|sk
)paren
(brace
id|BT_DBG
c_func
(paren
l_string|&quot;sk %p state %d&quot;
comma
id|sk
comma
id|sk-&gt;sk_state
)paren
suffix:semicolon
id|list_del_init
c_func
(paren
op_amp
id|bt_sk
c_func
(paren
id|sk
)paren
op_member_access_from_pointer
id|accept_q
)paren
suffix:semicolon
id|bt_sk
c_func
(paren
id|sk
)paren
op_member_access_from_pointer
id|parent-&gt;sk_ack_backlog
op_decrement
suffix:semicolon
id|bt_sk
c_func
(paren
id|sk
)paren
op_member_access_from_pointer
id|parent
op_assign
l_int|NULL
suffix:semicolon
id|sock_put
c_func
(paren
id|sk
)paren
suffix:semicolon
)brace
DECL|function|bt_accept_dequeue
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
(brace
r_struct
id|list_head
op_star
id|p
comma
op_star
id|n
suffix:semicolon
r_struct
id|sock
op_star
id|sk
suffix:semicolon
id|BT_DBG
c_func
(paren
l_string|&quot;parent %p&quot;
comma
id|parent
)paren
suffix:semicolon
id|list_for_each_safe
c_func
(paren
id|p
comma
id|n
comma
op_amp
id|bt_sk
c_func
(paren
id|parent
)paren
op_member_access_from_pointer
id|accept_q
)paren
(brace
id|sk
op_assign
(paren
r_struct
id|sock
op_star
)paren
id|list_entry
c_func
(paren
id|p
comma
r_struct
id|bt_sock
comma
id|accept_q
)paren
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
id|sk-&gt;sk_state
op_eq
id|BT_CLOSED
)paren
(brace
id|release_sock
c_func
(paren
id|sk
)paren
suffix:semicolon
id|bt_accept_unlink
c_func
(paren
id|sk
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sk-&gt;sk_state
op_eq
id|BT_CONNECTED
op_logical_or
op_logical_neg
id|newsock
)paren
(brace
id|bt_accept_unlink
c_func
(paren
id|sk
)paren
suffix:semicolon
r_if
c_cond
(paren
id|newsock
)paren
id|sock_graft
c_func
(paren
id|sk
comma
id|newsock
)paren
suffix:semicolon
id|release_sock
c_func
(paren
id|sk
)paren
suffix:semicolon
r_return
id|sk
suffix:semicolon
)brace
id|release_sock
c_func
(paren
id|sk
)paren
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|bt_sock_recvmsg
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
suffix:semicolon
r_int
id|err
suffix:semicolon
id|BT_DBG
c_func
(paren
l_string|&quot;sock %p sk %p len %d&quot;
comma
id|sock
comma
id|sk
comma
id|len
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
(brace
r_if
c_cond
(paren
id|sk-&gt;sk_shutdown
op_amp
id|RCV_SHUTDOWN
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
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
DECL|function|bt_accept_poll
r_static
r_inline
r_int
r_int
id|bt_accept_poll
c_func
(paren
r_struct
id|sock
op_star
id|parent
)paren
(brace
r_struct
id|list_head
op_star
id|p
comma
op_star
id|n
suffix:semicolon
r_struct
id|sock
op_star
id|sk
suffix:semicolon
id|list_for_each_safe
c_func
(paren
id|p
comma
id|n
comma
op_amp
id|bt_sk
c_func
(paren
id|parent
)paren
op_member_access_from_pointer
id|accept_q
)paren
(brace
id|sk
op_assign
(paren
r_struct
id|sock
op_star
)paren
id|list_entry
c_func
(paren
id|p
comma
r_struct
id|bt_sock
comma
id|accept_q
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sk-&gt;sk_state
op_eq
id|BT_CONNECTED
)paren
r_return
id|POLLIN
op_or
id|POLLRDNORM
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|bt_sock_poll
r_int
r_int
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
(brace
r_struct
id|sock
op_star
id|sk
op_assign
id|sock-&gt;sk
suffix:semicolon
r_int
r_int
id|mask
op_assign
l_int|0
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
id|poll_wait
c_func
(paren
id|file
comma
id|sk-&gt;sk_sleep
comma
id|wait
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sk-&gt;sk_state
op_eq
id|BT_LISTEN
)paren
r_return
id|bt_accept_poll
c_func
(paren
id|sk
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sk-&gt;sk_err
op_logical_or
op_logical_neg
id|skb_queue_empty
c_func
(paren
op_amp
id|sk-&gt;sk_error_queue
)paren
)paren
id|mask
op_or_assign
id|POLLERR
suffix:semicolon
r_if
c_cond
(paren
id|sk-&gt;sk_shutdown
op_eq
id|SHUTDOWN_MASK
)paren
id|mask
op_or_assign
id|POLLHUP
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|skb_queue_empty
c_func
(paren
op_amp
id|sk-&gt;sk_receive_queue
)paren
op_logical_or
(paren
id|sk-&gt;sk_shutdown
op_amp
id|RCV_SHUTDOWN
)paren
)paren
id|mask
op_or_assign
id|POLLIN
op_or
id|POLLRDNORM
suffix:semicolon
r_if
c_cond
(paren
id|sk-&gt;sk_state
op_eq
id|BT_CLOSED
)paren
id|mask
op_or_assign
id|POLLHUP
suffix:semicolon
r_if
c_cond
(paren
id|sk-&gt;sk_state
op_eq
id|BT_CONNECT
op_logical_or
id|sk-&gt;sk_state
op_eq
id|BT_CONNECT2
op_logical_or
id|sk-&gt;sk_state
op_eq
id|BT_CONFIG
)paren
r_return
id|mask
suffix:semicolon
r_if
c_cond
(paren
id|sock_writeable
c_func
(paren
id|sk
)paren
)paren
id|mask
op_or_assign
id|POLLOUT
op_or
id|POLLWRNORM
op_or
id|POLLWRBAND
suffix:semicolon
r_else
id|set_bit
c_func
(paren
id|SOCK_ASYNC_NOSPACE
comma
op_amp
id|sk-&gt;sk_socket-&gt;flags
)paren
suffix:semicolon
r_return
id|mask
suffix:semicolon
)brace
DECL|function|bt_sock_wait_state
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
(brace
id|DECLARE_WAITQUEUE
c_func
(paren
id|wait
comma
id|current
)paren
suffix:semicolon
r_int
id|err
op_assign
l_int|0
suffix:semicolon
id|BT_DBG
c_func
(paren
l_string|&quot;sk %p&quot;
comma
id|sk
)paren
suffix:semicolon
id|add_wait_queue
c_func
(paren
id|sk-&gt;sk_sleep
comma
op_amp
id|wait
)paren
suffix:semicolon
r_while
c_loop
(paren
id|sk-&gt;sk_state
op_ne
id|state
)paren
(brace
id|set_current_state
c_func
(paren
id|TASK_INTERRUPTIBLE
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|timeo
)paren
(brace
id|err
op_assign
op_minus
id|EAGAIN
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|signal_pending
c_func
(paren
id|current
)paren
)paren
(brace
id|err
op_assign
id|sock_intr_errno
c_func
(paren
id|timeo
)paren
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
id|timeo
op_assign
id|schedule_timeout
c_func
(paren
id|timeo
)paren
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
id|sk-&gt;sk_err
)paren
(brace
id|err
op_assign
id|sock_error
c_func
(paren
id|sk
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
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
id|sk-&gt;sk_sleep
comma
op_amp
id|wait
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|variable|bt_sock_family_ops
r_static
r_struct
id|net_proto_family
id|bt_sock_family_ops
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|family
op_assign
id|PF_BLUETOOTH
comma
dot
id|create
op_assign
id|bt_sock_create
comma
)brace
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
r_extern
r_int
id|bt_sysfs_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|bt_sysfs_cleanup
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|function|bt_init
r_static
r_int
id|__init
id|bt_init
c_func
(paren
r_void
)paren
(brace
id|BT_INFO
c_func
(paren
l_string|&quot;Core ver %s&quot;
comma
id|VERSION
)paren
suffix:semicolon
id|proc_bt
op_assign
id|proc_mkdir
c_func
(paren
l_string|&quot;bluetooth&quot;
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|proc_bt
)paren
id|proc_bt-&gt;owner
op_assign
id|THIS_MODULE
suffix:semicolon
multiline_comment|/* Init socket cache */
id|bt_sock_cache
op_assign
id|kmem_cache_create
c_func
(paren
l_string|&quot;bt_sock&quot;
comma
r_sizeof
(paren
r_struct
id|bt_sock
)paren
comma
l_int|0
comma
id|SLAB_HWCACHE_ALIGN
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bt_sock_cache
)paren
(brace
id|BT_ERR
c_func
(paren
l_string|&quot;Socket cache creation failed&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|sock_register
c_func
(paren
op_amp
id|bt_sock_family_ops
)paren
suffix:semicolon
id|BT_INFO
c_func
(paren
l_string|&quot;HCI device and connection manager initialized&quot;
)paren
suffix:semicolon
id|bt_sysfs_init
c_func
(paren
)paren
suffix:semicolon
id|hci_sock_init
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|bt_exit
r_static
r_void
id|__exit
id|bt_exit
c_func
(paren
r_void
)paren
(brace
id|hci_sock_cleanup
c_func
(paren
)paren
suffix:semicolon
id|bt_sysfs_cleanup
c_func
(paren
)paren
suffix:semicolon
id|sock_unregister
c_func
(paren
id|PF_BLUETOOTH
)paren
suffix:semicolon
id|kmem_cache_destroy
c_func
(paren
id|bt_sock_cache
)paren
suffix:semicolon
id|remove_proc_entry
c_func
(paren
l_string|&quot;bluetooth&quot;
comma
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|variable|bt_init
id|subsys_initcall
c_func
(paren
id|bt_init
)paren
suffix:semicolon
DECL|variable|bt_exit
id|module_exit
c_func
(paren
id|bt_exit
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Maxim Krasnyansky &lt;maxk@qualcomm.com&gt;, Marcel Holtmann &lt;marcel@holtmann.org&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Bluetooth Core ver &quot;
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
DECL|variable|PF_BLUETOOTH
id|MODULE_ALIAS_NETPROTO
c_func
(paren
id|PF_BLUETOOTH
)paren
suffix:semicolon
eof
