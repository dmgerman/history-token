multiline_comment|/* &n;   CMTP implementation for Linux Bluetooth stack (BlueZ).&n;   Copyright (C) 2002-2003 Marcel Holtmann &lt;marcel@holtmann.org&gt;&n;&n;   This program is free software; you can redistribute it and/or modify&n;   it under the terms of the GNU General Public License version 2 as&n;   published by the Free Software Foundation;&n;&n;   THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND, EXPRESS&n;   OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,&n;   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT OF THIRD PARTY RIGHTS.&n;   IN NO EVENT SHALL THE COPYRIGHT HOLDER(S) AND AUTHOR(S) BE LIABLE FOR ANY&n;   CLAIM, OR ANY SPECIAL INDIRECT OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES &n;   WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN &n;   ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF &n;   OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.&n;&n;   ALL LIABILITY, INCLUDING LIABILITY FOR INFRINGEMENT OF ANY PATENTS, &n;   COPYRIGHTS, TRADEMARKS OR OTHER RIGHTS, RELATING TO USE OF THIS &n;   SOFTWARE IS DISCLAIMED.&n;*/
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
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/ioctl.h&gt;
macro_line|#include &lt;linux/file.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;linux/isdn/capilli.h&gt;
macro_line|#include &lt;net/bluetooth/bluetooth.h&gt;
macro_line|#include &lt;net/bluetooth/l2cap.h&gt;
macro_line|#include &quot;cmtp.h&quot;
macro_line|#ifndef CONFIG_BT_CMTP_DEBUG
DECL|macro|BT_DBG
macro_line|#undef  BT_DBG
DECL|macro|BT_DBG
mdefine_line|#define BT_DBG(D...)
macro_line|#endif
DECL|macro|VERSION
mdefine_line|#define VERSION &quot;1.0&quot;
r_static
id|DECLARE_RWSEM
c_func
(paren
id|cmtp_session_sem
)paren
suffix:semicolon
r_static
id|LIST_HEAD
c_func
(paren
id|cmtp_session_list
)paren
suffix:semicolon
DECL|function|__cmtp_get_session
r_static
r_struct
id|cmtp_session
op_star
id|__cmtp_get_session
c_func
(paren
id|bdaddr_t
op_star
id|bdaddr
)paren
(brace
r_struct
id|cmtp_session
op_star
id|session
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
id|cmtp_session_list
)paren
(brace
id|session
op_assign
id|list_entry
c_func
(paren
id|p
comma
r_struct
id|cmtp_session
comma
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bacmp
c_func
(paren
id|bdaddr
comma
op_amp
id|session-&gt;bdaddr
)paren
)paren
r_return
id|session
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|__cmtp_link_session
r_static
r_void
id|__cmtp_link_session
c_func
(paren
r_struct
id|cmtp_session
op_star
id|session
)paren
(brace
id|__module_get
c_func
(paren
id|THIS_MODULE
)paren
suffix:semicolon
id|list_add
c_func
(paren
op_amp
id|session-&gt;list
comma
op_amp
id|cmtp_session_list
)paren
suffix:semicolon
)brace
DECL|function|__cmtp_unlink_session
r_static
r_void
id|__cmtp_unlink_session
c_func
(paren
r_struct
id|cmtp_session
op_star
id|session
)paren
(brace
id|list_del
c_func
(paren
op_amp
id|session-&gt;list
)paren
suffix:semicolon
id|module_put
c_func
(paren
id|THIS_MODULE
)paren
suffix:semicolon
)brace
DECL|function|__cmtp_copy_session
r_static
r_void
id|__cmtp_copy_session
c_func
(paren
r_struct
id|cmtp_session
op_star
id|session
comma
r_struct
id|cmtp_conninfo
op_star
id|ci
)paren
(brace
id|bacpy
c_func
(paren
op_amp
id|ci-&gt;bdaddr
comma
op_amp
id|session-&gt;bdaddr
)paren
suffix:semicolon
id|ci-&gt;flags
op_assign
id|session-&gt;flags
suffix:semicolon
id|ci-&gt;state
op_assign
id|session-&gt;state
suffix:semicolon
id|ci-&gt;num
op_assign
id|session-&gt;num
suffix:semicolon
)brace
DECL|function|cmtp_alloc_block_id
r_static
r_inline
r_int
id|cmtp_alloc_block_id
c_func
(paren
r_struct
id|cmtp_session
op_star
id|session
)paren
(brace
r_int
id|i
comma
id|id
op_assign
op_minus
l_int|1
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
l_int|16
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
op_logical_neg
id|test_and_set_bit
c_func
(paren
id|i
comma
op_amp
id|session-&gt;blockids
)paren
)paren
(brace
id|id
op_assign
id|i
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
id|id
suffix:semicolon
)brace
DECL|function|cmtp_free_block_id
r_static
r_inline
r_void
id|cmtp_free_block_id
c_func
(paren
r_struct
id|cmtp_session
op_star
id|session
comma
r_int
id|id
)paren
(brace
id|clear_bit
c_func
(paren
id|id
comma
op_amp
id|session-&gt;blockids
)paren
suffix:semicolon
)brace
DECL|function|cmtp_add_msgpart
r_static
r_inline
r_void
id|cmtp_add_msgpart
c_func
(paren
r_struct
id|cmtp_session
op_star
id|session
comma
r_int
id|id
comma
r_const
r_int
r_char
op_star
id|buf
comma
r_int
id|count
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb
op_assign
id|session-&gt;reassembly
(braket
id|id
)braket
comma
op_star
id|nskb
suffix:semicolon
r_int
id|size
suffix:semicolon
id|BT_DBG
c_func
(paren
l_string|&quot;session %p buf %p count %d&quot;
comma
id|session
comma
id|buf
comma
id|count
)paren
suffix:semicolon
id|size
op_assign
(paren
id|skb
)paren
ques
c_cond
id|skb-&gt;len
op_plus
id|count
suffix:colon
id|count
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|nskb
op_assign
id|alloc_skb
c_func
(paren
id|size
comma
id|GFP_ATOMIC
)paren
)paren
)paren
(brace
id|BT_ERR
c_func
(paren
l_string|&quot;Can&squot;t allocate memory for CAPI message&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|skb
op_logical_and
(paren
id|skb-&gt;len
OG
l_int|0
)paren
)paren
id|memcpy
c_func
(paren
id|skb_put
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
id|memcpy
c_func
(paren
id|skb_put
c_func
(paren
id|nskb
comma
id|count
)paren
comma
id|buf
comma
id|count
)paren
suffix:semicolon
id|session-&gt;reassembly
(braket
id|id
)braket
op_assign
id|nskb
suffix:semicolon
r_if
c_cond
(paren
id|skb
)paren
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
DECL|function|cmtp_recv_frame
r_static
r_inline
r_int
id|cmtp_recv_frame
c_func
(paren
r_struct
id|cmtp_session
op_star
id|session
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
id|__u8
id|hdr
comma
id|hdrlen
comma
id|id
suffix:semicolon
id|__u16
id|len
suffix:semicolon
id|BT_DBG
c_func
(paren
l_string|&quot;session %p skb %p len %d&quot;
comma
id|session
comma
id|skb
comma
id|skb-&gt;len
)paren
suffix:semicolon
r_while
c_loop
(paren
id|skb-&gt;len
OG
l_int|0
)paren
(brace
id|hdr
op_assign
id|skb-&gt;data
(braket
l_int|0
)braket
suffix:semicolon
r_switch
c_cond
(paren
id|hdr
op_amp
l_int|0xc0
)paren
(brace
r_case
l_int|0x40
suffix:colon
id|hdrlen
op_assign
l_int|2
suffix:semicolon
id|len
op_assign
id|skb-&gt;data
(braket
l_int|1
)braket
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x80
suffix:colon
id|hdrlen
op_assign
l_int|3
suffix:semicolon
id|len
op_assign
id|skb-&gt;data
(braket
l_int|1
)braket
op_or
(paren
id|skb-&gt;data
(braket
l_int|2
)braket
op_lshift
l_int|8
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|hdrlen
op_assign
l_int|1
suffix:semicolon
id|len
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
id|id
op_assign
(paren
id|hdr
op_amp
l_int|0x3c
)paren
op_rshift
l_int|2
suffix:semicolon
id|BT_DBG
c_func
(paren
l_string|&quot;hdr 0x%02x hdrlen %d len %d id %d&quot;
comma
id|hdr
comma
id|hdrlen
comma
id|len
comma
id|id
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hdrlen
op_plus
id|len
OG
id|skb-&gt;len
)paren
(brace
id|BT_ERR
c_func
(paren
l_string|&quot;Wrong size or header information in CMTP frame&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|len
op_eq
l_int|0
)paren
(brace
id|skb_pull
c_func
(paren
id|skb
comma
id|hdrlen
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|hdr
op_amp
l_int|0x03
)paren
(brace
r_case
l_int|0x00
suffix:colon
id|cmtp_add_msgpart
c_func
(paren
id|session
comma
id|id
comma
id|skb-&gt;data
op_plus
id|hdrlen
comma
id|len
)paren
suffix:semicolon
id|cmtp_recv_capimsg
c_func
(paren
id|session
comma
id|session-&gt;reassembly
(braket
id|id
)braket
)paren
suffix:semicolon
id|session-&gt;reassembly
(braket
id|id
)braket
op_assign
l_int|NULL
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x01
suffix:colon
id|cmtp_add_msgpart
c_func
(paren
id|session
comma
id|id
comma
id|skb-&gt;data
op_plus
id|hdrlen
comma
id|len
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
(brace
)brace
r_if
c_cond
(paren
id|session-&gt;reassembly
(braket
id|id
)braket
op_ne
l_int|NULL
)paren
id|kfree_skb
c_func
(paren
id|session-&gt;reassembly
(braket
id|id
)braket
)paren
suffix:semicolon
id|session-&gt;reassembly
(braket
id|id
)braket
op_assign
l_int|NULL
suffix:semicolon
r_break
suffix:semicolon
)brace
id|skb_pull
c_func
(paren
id|skb
comma
id|hdrlen
op_plus
id|len
)paren
suffix:semicolon
)brace
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
DECL|function|cmtp_send_frame
r_static
r_int
id|cmtp_send_frame
c_func
(paren
r_struct
id|cmtp_session
op_star
id|session
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
r_struct
id|socket
op_star
id|sock
op_assign
id|session-&gt;sock
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
r_struct
id|msghdr
id|msg
suffix:semicolon
id|BT_DBG
c_func
(paren
l_string|&quot;session %p data %p len %d&quot;
comma
id|session
comma
id|data
comma
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|len
)paren
r_return
l_int|0
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|msg
comma
l_int|0
comma
r_sizeof
(paren
id|msg
)paren
)paren
suffix:semicolon
id|msg.msg_iovlen
op_assign
l_int|1
suffix:semicolon
id|msg.msg_iov
op_assign
op_amp
id|iv
suffix:semicolon
r_return
id|sock_sendmsg
c_func
(paren
id|sock
comma
op_amp
id|msg
comma
id|len
)paren
suffix:semicolon
)brace
DECL|function|cmtp_process_transmit
r_static
r_int
id|cmtp_process_transmit
c_func
(paren
r_struct
id|cmtp_session
op_star
id|session
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb
comma
op_star
id|nskb
suffix:semicolon
r_int
r_char
op_star
id|hdr
suffix:semicolon
r_int
r_int
id|size
comma
id|tail
suffix:semicolon
id|BT_DBG
c_func
(paren
l_string|&quot;session %p&quot;
comma
id|session
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|nskb
op_assign
id|alloc_skb
c_func
(paren
id|session-&gt;mtu
comma
id|GFP_ATOMIC
)paren
)paren
)paren
(brace
id|BT_ERR
c_func
(paren
l_string|&quot;Can&squot;t allocate memory for new frame&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
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
id|session-&gt;transmit
)paren
)paren
)paren
(brace
r_struct
id|cmtp_scb
op_star
id|scb
op_assign
(paren
r_void
op_star
)paren
id|skb-&gt;cb
suffix:semicolon
r_if
c_cond
(paren
(paren
id|tail
op_assign
(paren
id|session-&gt;mtu
op_minus
id|nskb-&gt;len
)paren
)paren
OL
l_int|5
)paren
(brace
id|cmtp_send_frame
c_func
(paren
id|session
comma
id|nskb-&gt;data
comma
id|nskb-&gt;len
)paren
suffix:semicolon
id|skb_trim
c_func
(paren
id|nskb
comma
l_int|0
)paren
suffix:semicolon
id|tail
op_assign
id|session-&gt;mtu
suffix:semicolon
)brace
id|size
op_assign
id|min_t
c_func
(paren
id|uint
comma
(paren
(paren
id|tail
OL
l_int|258
)paren
ques
c_cond
(paren
id|tail
op_minus
l_int|2
)paren
suffix:colon
(paren
id|tail
op_minus
l_int|3
)paren
)paren
comma
id|skb-&gt;len
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|scb-&gt;id
OL
l_int|0
)paren
op_logical_and
(paren
(paren
id|scb-&gt;id
op_assign
id|cmtp_alloc_block_id
c_func
(paren
id|session
)paren
)paren
OL
l_int|0
)paren
)paren
(brace
id|skb_queue_head
c_func
(paren
op_amp
id|session-&gt;transmit
comma
id|skb
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|size
OL
l_int|256
)paren
(brace
id|hdr
op_assign
id|skb_put
c_func
(paren
id|nskb
comma
l_int|2
)paren
suffix:semicolon
id|hdr
(braket
l_int|0
)braket
op_assign
l_int|0x40
op_or
(paren
(paren
id|scb-&gt;id
op_lshift
l_int|2
)paren
op_amp
l_int|0x3c
)paren
op_or
(paren
(paren
id|skb-&gt;len
op_eq
id|size
)paren
ques
c_cond
l_int|0x00
suffix:colon
l_int|0x01
)paren
suffix:semicolon
id|hdr
(braket
l_int|1
)braket
op_assign
id|size
suffix:semicolon
)brace
r_else
(brace
id|hdr
op_assign
id|skb_put
c_func
(paren
id|nskb
comma
l_int|3
)paren
suffix:semicolon
id|hdr
(braket
l_int|0
)braket
op_assign
l_int|0x80
op_or
(paren
(paren
id|scb-&gt;id
op_lshift
l_int|2
)paren
op_amp
l_int|0x3c
)paren
op_or
(paren
(paren
id|skb-&gt;len
op_eq
id|size
)paren
ques
c_cond
l_int|0x00
suffix:colon
l_int|0x01
)paren
suffix:semicolon
id|hdr
(braket
l_int|1
)braket
op_assign
id|size
op_amp
l_int|0xff
suffix:semicolon
id|hdr
(braket
l_int|2
)braket
op_assign
id|size
op_rshift
l_int|8
suffix:semicolon
)brace
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
comma
id|size
)paren
suffix:semicolon
id|skb_pull
c_func
(paren
id|skb
comma
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb-&gt;len
OG
l_int|0
)paren
(brace
id|skb_queue_head
c_func
(paren
op_amp
id|session-&gt;transmit
comma
id|skb
)paren
suffix:semicolon
)brace
r_else
(brace
id|cmtp_free_block_id
c_func
(paren
id|session
comma
id|scb-&gt;id
)paren
suffix:semicolon
r_if
c_cond
(paren
id|scb-&gt;data
)paren
(brace
id|cmtp_send_frame
c_func
(paren
id|session
comma
id|nskb-&gt;data
comma
id|nskb-&gt;len
)paren
suffix:semicolon
id|skb_trim
c_func
(paren
id|nskb
comma
l_int|0
)paren
suffix:semicolon
)brace
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
)brace
id|cmtp_send_frame
c_func
(paren
id|session
comma
id|nskb-&gt;data
comma
id|nskb-&gt;len
)paren
suffix:semicolon
id|kfree_skb
c_func
(paren
id|nskb
)paren
suffix:semicolon
r_return
id|skb_queue_len
c_func
(paren
op_amp
id|session-&gt;transmit
)paren
suffix:semicolon
)brace
DECL|function|cmtp_session
r_static
r_int
id|cmtp_session
c_func
(paren
r_void
op_star
id|arg
)paren
(brace
r_struct
id|cmtp_session
op_star
id|session
op_assign
id|arg
suffix:semicolon
r_struct
id|sock
op_star
id|sk
op_assign
id|session-&gt;sock-&gt;sk
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
l_string|&quot;session %p&quot;
comma
id|session
)paren
suffix:semicolon
id|daemonize
c_func
(paren
l_string|&quot;kcmtpd_ctr_%d&quot;
comma
id|session-&gt;num
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
id|sk-&gt;sk_sleep
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
id|session-&gt;terminate
)paren
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
id|sk-&gt;sk_state
op_ne
id|BT_CONNECTED
)paren
r_break
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
id|sk-&gt;sk_receive_queue
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
id|cmtp_recv_frame
c_func
(paren
id|session
comma
id|skb
)paren
suffix:semicolon
)brace
id|cmtp_process_transmit
c_func
(paren
id|session
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
id|sk-&gt;sk_sleep
comma
op_amp
id|wait
)paren
suffix:semicolon
id|down_write
c_func
(paren
op_amp
id|cmtp_session_sem
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|session-&gt;flags
op_amp
(paren
l_int|1
op_lshift
id|CMTP_LOOPBACK
)paren
)paren
)paren
id|cmtp_detach_device
c_func
(paren
id|session
)paren
suffix:semicolon
id|fput
c_func
(paren
id|session-&gt;sock-&gt;file
)paren
suffix:semicolon
id|__cmtp_unlink_session
c_func
(paren
id|session
)paren
suffix:semicolon
id|up_write
c_func
(paren
op_amp
id|cmtp_session_sem
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|session
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cmtp_add_connection
r_int
id|cmtp_add_connection
c_func
(paren
r_struct
id|cmtp_connadd_req
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
id|cmtp_session
op_star
id|session
comma
op_star
id|s
suffix:semicolon
id|bdaddr_t
id|src
comma
id|dst
suffix:semicolon
r_int
id|i
comma
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
op_amp
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
id|baswap
c_func
(paren
op_amp
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
id|session
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|cmtp_session
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|session
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|memset
c_func
(paren
id|session
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|cmtp_session
)paren
)paren
suffix:semicolon
id|down_write
c_func
(paren
op_amp
id|cmtp_session_sem
)paren
suffix:semicolon
id|s
op_assign
id|__cmtp_get_session
c_func
(paren
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
r_if
c_cond
(paren
id|s
op_logical_and
id|s-&gt;state
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
id|bacpy
c_func
(paren
op_amp
id|session-&gt;bdaddr
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
id|session-&gt;mtu
op_assign
id|min_t
c_func
(paren
id|uint
comma
id|l2cap_pi
c_func
(paren
id|sock-&gt;sk
)paren
op_member_access_from_pointer
id|omtu
comma
id|l2cap_pi
c_func
(paren
id|sock-&gt;sk
)paren
op_member_access_from_pointer
id|imtu
)paren
suffix:semicolon
id|BT_DBG
c_func
(paren
l_string|&quot;mtu %d&quot;
comma
id|session-&gt;mtu
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|session-&gt;name
comma
l_string|&quot;%s&quot;
comma
id|batostr
c_func
(paren
op_amp
id|dst
)paren
)paren
suffix:semicolon
id|session-&gt;sock
op_assign
id|sock
suffix:semicolon
id|session-&gt;state
op_assign
id|BT_CONFIG
suffix:semicolon
id|init_waitqueue_head
c_func
(paren
op_amp
id|session-&gt;wait
)paren
suffix:semicolon
id|session-&gt;msgnum
op_assign
id|CMTP_INITIAL_MSGNUM
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|session-&gt;applications
)paren
suffix:semicolon
id|skb_queue_head_init
c_func
(paren
op_amp
id|session-&gt;transmit
)paren
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
l_int|16
suffix:semicolon
id|i
op_increment
)paren
id|session-&gt;reassembly
(braket
id|i
)braket
op_assign
l_int|NULL
suffix:semicolon
id|session-&gt;flags
op_assign
id|req-&gt;flags
suffix:semicolon
id|__cmtp_link_session
c_func
(paren
id|session
)paren
suffix:semicolon
id|err
op_assign
id|kernel_thread
c_func
(paren
id|cmtp_session
comma
id|session
comma
id|CLONE_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
r_goto
id|unlink
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|session-&gt;flags
op_amp
(paren
l_int|1
op_lshift
id|CMTP_LOOPBACK
)paren
)paren
)paren
(brace
id|err
op_assign
id|cmtp_attach_device
c_func
(paren
id|session
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
r_goto
id|detach
suffix:semicolon
)brace
id|up_write
c_func
(paren
op_amp
id|cmtp_session_sem
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|detach
suffix:colon
id|cmtp_detach_device
c_func
(paren
id|session
)paren
suffix:semicolon
id|unlink
suffix:colon
id|__cmtp_unlink_session
c_func
(paren
id|session
)paren
suffix:semicolon
id|failed
suffix:colon
id|up_write
c_func
(paren
op_amp
id|cmtp_session_sem
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|session
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|cmtp_del_connection
r_int
id|cmtp_del_connection
c_func
(paren
r_struct
id|cmtp_conndel_req
op_star
id|req
)paren
(brace
r_struct
id|cmtp_session
op_star
id|session
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
id|cmtp_session_sem
)paren
suffix:semicolon
id|session
op_assign
id|__cmtp_get_session
c_func
(paren
op_amp
id|req-&gt;bdaddr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|session
)paren
(brace
multiline_comment|/* Flush the transmit queue */
id|skb_queue_purge
c_func
(paren
op_amp
id|session-&gt;transmit
)paren
suffix:semicolon
multiline_comment|/* Kill session thread */
id|atomic_inc
c_func
(paren
op_amp
id|session-&gt;terminate
)paren
suffix:semicolon
id|cmtp_schedule
c_func
(paren
id|session
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
id|cmtp_session_sem
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|cmtp_get_connlist
r_int
id|cmtp_get_connlist
c_func
(paren
r_struct
id|cmtp_connlist_req
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
id|cmtp_session_sem
)paren
suffix:semicolon
id|list_for_each
c_func
(paren
id|p
comma
op_amp
id|cmtp_session_list
)paren
(brace
r_struct
id|cmtp_session
op_star
id|session
suffix:semicolon
r_struct
id|cmtp_conninfo
id|ci
suffix:semicolon
id|session
op_assign
id|list_entry
c_func
(paren
id|p
comma
r_struct
id|cmtp_session
comma
id|list
)paren
suffix:semicolon
id|__cmtp_copy_session
c_func
(paren
id|session
comma
op_amp
id|ci
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
id|cmtp_session_sem
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|cmtp_get_conninfo
r_int
id|cmtp_get_conninfo
c_func
(paren
r_struct
id|cmtp_conninfo
op_star
id|ci
)paren
(brace
r_struct
id|cmtp_session
op_star
id|session
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
id|cmtp_session_sem
)paren
suffix:semicolon
id|session
op_assign
id|__cmtp_get_session
c_func
(paren
op_amp
id|ci-&gt;bdaddr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|session
)paren
id|__cmtp_copy_session
c_func
(paren
id|session
comma
id|ci
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
id|cmtp_session_sem
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|init_cmtp
r_int
id|__init
id|init_cmtp
c_func
(paren
r_void
)paren
(brace
id|l2cap_load
c_func
(paren
)paren
suffix:semicolon
id|BT_INFO
c_func
(paren
l_string|&quot;CMTP (CAPI Emulation) ver %s&quot;
comma
id|VERSION
)paren
suffix:semicolon
id|cmtp_init_sockets
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|exit_cmtp
r_void
id|__exit
id|exit_cmtp
c_func
(paren
r_void
)paren
(brace
id|cmtp_cleanup_sockets
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|variable|init_cmtp
id|module_init
c_func
(paren
id|init_cmtp
)paren
suffix:semicolon
DECL|variable|exit_cmtp
id|module_exit
c_func
(paren
id|exit_cmtp
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
l_string|&quot;Bluetooth CMTP ver &quot;
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
id|MODULE_ALIAS
c_func
(paren
l_string|&quot;bt-proto-5&quot;
)paren
suffix:semicolon
eof
