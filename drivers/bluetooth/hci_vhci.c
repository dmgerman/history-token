multiline_comment|/* &n;   BlueZ - Bluetooth protocol stack for Linux&n;   Copyright (C) 2000-2001 Qualcomm Incorporated&n;&n;   Written 2000,2001 by Maxim Krasnyansky &lt;maxk@qualcomm.com&gt;&n;&n;   This program is free software; you can redistribute it and/or modify&n;   it under the terms of the GNU General Public License version 2 as&n;   published by the Free Software Foundation;&n;&n;   THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND, EXPRESS&n;   OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,&n;   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT OF THIRD PARTY RIGHTS.&n;   IN NO EVENT SHALL THE COPYRIGHT HOLDER(S) AND AUTHOR(S) BE LIABLE FOR ANY&n;   CLAIM, OR ANY SPECIAL INDIRECT OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES &n;   WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN &n;   ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF &n;   OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.&n;&n;   ALL LIABILITY, INCLUDING LIABILITY FOR INFRINGEMENT OF ANY PATENTS, &n;   COPYRIGHTS, TRADEMARKS OR OTHER RIGHTS, RELATING TO USE OF THIS &n;   SOFTWARE IS DISCLAIMED.&n;*/
multiline_comment|/*&n; * Bluetooth HCI virtual device driver.&n; *&n; * $Id: hci_vhci.c,v 1.3 2002/04/17 17:37:20 maxk Exp $ &n; */
DECL|macro|VERSION
mdefine_line|#define VERSION &quot;1.1&quot;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/poll.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/random.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/miscdevice.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;net/bluetooth/bluetooth.h&gt;
macro_line|#include &lt;net/bluetooth/hci_core.h&gt;
macro_line|#include &quot;hci_vhci.h&quot;
multiline_comment|/* HCI device part */
DECL|function|hci_vhci_open
r_static
r_int
id|hci_vhci_open
c_func
(paren
r_struct
id|hci_dev
op_star
id|hdev
)paren
(brace
id|set_bit
c_func
(paren
id|HCI_RUNNING
comma
op_amp
id|hdev-&gt;flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|hci_vhci_flush
r_static
r_int
id|hci_vhci_flush
c_func
(paren
r_struct
id|hci_dev
op_star
id|hdev
)paren
(brace
r_struct
id|hci_vhci_struct
op_star
id|hci_vhci
op_assign
(paren
r_struct
id|hci_vhci_struct
op_star
)paren
id|hdev-&gt;driver_data
suffix:semicolon
id|skb_queue_purge
c_func
(paren
op_amp
id|hci_vhci-&gt;readq
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|hci_vhci_close
r_static
r_int
id|hci_vhci_close
c_func
(paren
r_struct
id|hci_dev
op_star
id|hdev
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|test_and_clear_bit
c_func
(paren
id|HCI_RUNNING
comma
op_amp
id|hdev-&gt;flags
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|hci_vhci_flush
c_func
(paren
id|hdev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|hci_vhci_destruct
r_static
r_void
id|hci_vhci_destruct
c_func
(paren
r_struct
id|hci_dev
op_star
id|hdev
)paren
(brace
r_struct
id|hci_vhci_struct
op_star
id|vhci
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hdev
)paren
r_return
suffix:semicolon
id|vhci
op_assign
(paren
r_struct
id|hci_vhci_struct
op_star
)paren
id|hdev-&gt;driver_data
suffix:semicolon
id|kfree
c_func
(paren
id|vhci
)paren
suffix:semicolon
)brace
DECL|function|hci_vhci_send_frame
r_static
r_int
id|hci_vhci_send_frame
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
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
id|skb-&gt;dev
suffix:semicolon
r_struct
id|hci_vhci_struct
op_star
id|hci_vhci
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hdev
)paren
(brace
id|BT_ERR
c_func
(paren
l_string|&quot;Frame for uknown device (hdev=NULL)&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|test_bit
c_func
(paren
id|HCI_RUNNING
comma
op_amp
id|hdev-&gt;flags
)paren
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
id|hci_vhci
op_assign
(paren
r_struct
id|hci_vhci_struct
op_star
)paren
id|hdev-&gt;driver_data
suffix:semicolon
id|memcpy
c_func
(paren
id|skb_push
c_func
(paren
id|skb
comma
l_int|1
)paren
comma
op_amp
id|skb-&gt;pkt_type
comma
l_int|1
)paren
suffix:semicolon
id|skb_queue_tail
c_func
(paren
op_amp
id|hci_vhci-&gt;readq
comma
id|skb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hci_vhci-&gt;flags
op_amp
id|VHCI_FASYNC
)paren
id|kill_fasync
c_func
(paren
op_amp
id|hci_vhci-&gt;fasync
comma
id|SIGIO
comma
id|POLL_IN
)paren
suffix:semicolon
id|wake_up_interruptible
c_func
(paren
op_amp
id|hci_vhci-&gt;read_wait
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Character device part */
multiline_comment|/* Poll */
DECL|function|hci_vhci_chr_poll
r_static
r_int
r_int
id|hci_vhci_chr_poll
c_func
(paren
r_struct
id|file
op_star
id|file
comma
id|poll_table
op_star
id|wait
)paren
(brace
r_struct
id|hci_vhci_struct
op_star
id|hci_vhci
op_assign
(paren
r_struct
id|hci_vhci_struct
op_star
)paren
id|file-&gt;private_data
suffix:semicolon
id|poll_wait
c_func
(paren
id|file
comma
op_amp
id|hci_vhci-&gt;read_wait
comma
id|wait
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb_queue_len
c_func
(paren
op_amp
id|hci_vhci-&gt;readq
)paren
)paren
r_return
id|POLLIN
op_or
id|POLLRDNORM
suffix:semicolon
r_return
id|POLLOUT
op_or
id|POLLWRNORM
suffix:semicolon
)brace
multiline_comment|/* Get packet from user space buffer(already verified) */
DECL|function|hci_vhci_get_user
r_static
r_inline
id|ssize_t
id|hci_vhci_get_user
c_func
(paren
r_struct
id|hci_vhci_struct
op_star
id|hci_vhci
comma
r_const
r_char
id|__user
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
suffix:semicolon
r_if
c_cond
(paren
id|count
OG
id|HCI_MAX_FRAME_SIZE
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|skb
op_assign
id|bt_skb_alloc
c_func
(paren
id|count
comma
id|GFP_KERNEL
)paren
)paren
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|skb_put
c_func
(paren
id|skb
comma
id|count
)paren
comma
id|buf
comma
id|count
)paren
)paren
(brace
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
id|skb-&gt;dev
op_assign
(paren
r_void
op_star
)paren
id|hci_vhci-&gt;hdev
suffix:semicolon
id|skb-&gt;pkt_type
op_assign
op_star
(paren
(paren
id|__u8
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
id|hci_recv_frame
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
multiline_comment|/* Write */
DECL|function|hci_vhci_chr_write
r_static
id|ssize_t
id|hci_vhci_chr_write
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_const
r_char
id|__user
op_star
id|buf
comma
r_int
id|count
comma
id|loff_t
op_star
id|pos
)paren
(brace
r_struct
id|hci_vhci_struct
op_star
id|hci_vhci
op_assign
(paren
r_struct
id|hci_vhci_struct
op_star
)paren
id|file-&gt;private_data
suffix:semicolon
r_if
c_cond
(paren
id|verify_area
c_func
(paren
id|VERIFY_READ
comma
id|buf
comma
id|count
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
id|hci_vhci_get_user
c_func
(paren
id|hci_vhci
comma
id|buf
comma
id|count
)paren
suffix:semicolon
)brace
multiline_comment|/* Put packet to user space buffer(already verified) */
DECL|function|hci_vhci_put_user
r_static
r_inline
id|ssize_t
id|hci_vhci_put_user
c_func
(paren
r_struct
id|hci_vhci_struct
op_star
id|hci_vhci
comma
r_struct
id|sk_buff
op_star
id|skb
comma
r_char
id|__user
op_star
id|buf
comma
r_int
id|count
)paren
(brace
r_int
id|len
op_assign
id|count
comma
id|total
op_assign
l_int|0
suffix:semicolon
r_char
id|__user
op_star
id|ptr
op_assign
id|buf
suffix:semicolon
id|len
op_assign
id|min_t
c_func
(paren
r_int
r_int
comma
id|skb-&gt;len
comma
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|ptr
comma
id|skb-&gt;data
comma
id|len
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|total
op_add_assign
id|len
suffix:semicolon
id|hci_vhci-&gt;hdev-&gt;stat.byte_tx
op_add_assign
id|len
suffix:semicolon
r_switch
c_cond
(paren
id|skb-&gt;pkt_type
)paren
(brace
r_case
id|HCI_COMMAND_PKT
suffix:colon
id|hci_vhci-&gt;hdev-&gt;stat.cmd_tx
op_increment
suffix:semicolon
r_break
suffix:semicolon
r_case
id|HCI_ACLDATA_PKT
suffix:colon
id|hci_vhci-&gt;hdev-&gt;stat.acl_tx
op_increment
suffix:semicolon
r_break
suffix:semicolon
r_case
id|HCI_SCODATA_PKT
suffix:colon
id|hci_vhci-&gt;hdev-&gt;stat.cmd_tx
op_increment
suffix:semicolon
r_break
suffix:semicolon
)brace
suffix:semicolon
r_return
id|total
suffix:semicolon
)brace
multiline_comment|/* Read */
DECL|function|hci_vhci_chr_read
r_static
id|ssize_t
id|hci_vhci_chr_read
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_char
id|__user
op_star
id|buf
comma
r_int
id|count
comma
id|loff_t
op_star
id|pos
)paren
(brace
r_struct
id|hci_vhci_struct
op_star
id|hci_vhci
op_assign
(paren
r_struct
id|hci_vhci_struct
op_star
)paren
id|file-&gt;private_data
suffix:semicolon
id|DECLARE_WAITQUEUE
c_func
(paren
id|wait
comma
id|current
)paren
suffix:semicolon
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
id|ssize_t
id|ret
op_assign
l_int|0
suffix:semicolon
id|add_wait_queue
c_func
(paren
op_amp
id|hci_vhci-&gt;read_wait
comma
op_amp
id|wait
)paren
suffix:semicolon
r_while
c_loop
(paren
id|count
)paren
(brace
id|set_current_state
c_func
(paren
id|TASK_INTERRUPTIBLE
)paren
suffix:semicolon
multiline_comment|/* Read frames from device queue */
r_if
c_cond
(paren
op_logical_neg
(paren
id|skb
op_assign
id|skb_dequeue
c_func
(paren
op_amp
id|hci_vhci-&gt;readq
)paren
)paren
)paren
(brace
r_if
c_cond
(paren
id|file-&gt;f_flags
op_amp
id|O_NONBLOCK
)paren
(brace
id|ret
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
id|ret
op_assign
op_minus
id|ERESTARTSYS
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* Nothing to read, let&squot;s sleep */
id|schedule
c_func
(paren
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|verify_area
c_func
(paren
id|VERIFY_WRITE
comma
id|buf
comma
id|count
)paren
)paren
id|ret
op_assign
id|hci_vhci_put_user
c_func
(paren
id|hci_vhci
comma
id|skb
comma
id|buf
comma
id|count
)paren
suffix:semicolon
r_else
id|ret
op_assign
op_minus
id|EFAULT
suffix:semicolon
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_break
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
op_amp
id|hci_vhci-&gt;read_wait
comma
op_amp
id|wait
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|hci_vhci_chr_lseek
r_static
id|loff_t
id|hci_vhci_chr_lseek
c_func
(paren
r_struct
id|file
op_star
id|file
comma
id|loff_t
id|offset
comma
r_int
id|origin
)paren
(brace
r_return
op_minus
id|ESPIPE
suffix:semicolon
)brace
DECL|function|hci_vhci_chr_ioctl
r_static
r_int
id|hci_vhci_chr_ioctl
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
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
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|function|hci_vhci_chr_fasync
r_static
r_int
id|hci_vhci_chr_fasync
c_func
(paren
r_int
id|fd
comma
r_struct
id|file
op_star
id|file
comma
r_int
id|on
)paren
(brace
r_struct
id|hci_vhci_struct
op_star
id|hci_vhci
op_assign
(paren
r_struct
id|hci_vhci_struct
op_star
)paren
id|file-&gt;private_data
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|fasync_helper
c_func
(paren
id|fd
comma
id|file
comma
id|on
comma
op_amp
id|hci_vhci-&gt;fasync
)paren
)paren
OL
l_int|0
)paren
r_return
id|ret
suffix:semicolon
r_if
c_cond
(paren
id|on
)paren
id|hci_vhci-&gt;flags
op_or_assign
id|VHCI_FASYNC
suffix:semicolon
r_else
id|hci_vhci-&gt;flags
op_and_assign
op_complement
id|VHCI_FASYNC
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|hci_vhci_chr_open
r_static
r_int
id|hci_vhci_chr_open
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
)paren
(brace
r_struct
id|hci_vhci_struct
op_star
id|hci_vhci
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|hci_dev
op_star
id|hdev
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|hci_vhci
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|hci_vhci_struct
)paren
comma
id|GFP_KERNEL
)paren
)paren
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|memset
c_func
(paren
id|hci_vhci
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|hci_vhci_struct
)paren
)paren
suffix:semicolon
id|skb_queue_head_init
c_func
(paren
op_amp
id|hci_vhci-&gt;readq
)paren
suffix:semicolon
id|init_waitqueue_head
c_func
(paren
op_amp
id|hci_vhci-&gt;read_wait
)paren
suffix:semicolon
multiline_comment|/* Initialize and register HCI device */
id|hdev
op_assign
id|hci_alloc_dev
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hdev
)paren
(brace
id|kfree
c_func
(paren
id|hci_vhci
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|hci_vhci-&gt;hdev
op_assign
id|hdev
suffix:semicolon
id|hdev-&gt;type
op_assign
id|HCI_VHCI
suffix:semicolon
id|hdev-&gt;driver_data
op_assign
id|hci_vhci
suffix:semicolon
id|hdev-&gt;open
op_assign
id|hci_vhci_open
suffix:semicolon
id|hdev-&gt;close
op_assign
id|hci_vhci_close
suffix:semicolon
id|hdev-&gt;flush
op_assign
id|hci_vhci_flush
suffix:semicolon
id|hdev-&gt;send
op_assign
id|hci_vhci_send_frame
suffix:semicolon
id|hdev-&gt;destruct
op_assign
id|hci_vhci_destruct
suffix:semicolon
id|hdev-&gt;owner
op_assign
id|THIS_MODULE
suffix:semicolon
r_if
c_cond
(paren
id|hci_register_dev
c_func
(paren
id|hdev
)paren
OL
l_int|0
)paren
(brace
id|kfree
c_func
(paren
id|hci_vhci
)paren
suffix:semicolon
id|hci_free_dev
c_func
(paren
id|hdev
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|file-&gt;private_data
op_assign
id|hci_vhci
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|hci_vhci_chr_close
r_static
r_int
id|hci_vhci_chr_close
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
)paren
(brace
r_struct
id|hci_vhci_struct
op_star
id|hci_vhci
op_assign
(paren
r_struct
id|hci_vhci_struct
op_star
)paren
id|file-&gt;private_data
suffix:semicolon
r_if
c_cond
(paren
id|hci_unregister_dev
c_func
(paren
id|hci_vhci-&gt;hdev
)paren
OL
l_int|0
)paren
(brace
id|BT_ERR
c_func
(paren
l_string|&quot;Can&squot;t unregister HCI device %s&quot;
comma
id|hci_vhci-&gt;hdev-&gt;name
)paren
suffix:semicolon
)brace
id|hci_free_dev
c_func
(paren
id|hci_vhci-&gt;hdev
)paren
suffix:semicolon
id|file-&gt;private_data
op_assign
l_int|NULL
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|hci_vhci_fops
r_static
r_struct
id|file_operations
id|hci_vhci_fops
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|llseek
op_assign
id|hci_vhci_chr_lseek
comma
dot
id|read
op_assign
id|hci_vhci_chr_read
comma
dot
id|write
op_assign
id|hci_vhci_chr_write
comma
dot
id|poll
op_assign
id|hci_vhci_chr_poll
comma
dot
id|ioctl
op_assign
id|hci_vhci_chr_ioctl
comma
dot
id|open
op_assign
id|hci_vhci_chr_open
comma
dot
id|release
op_assign
id|hci_vhci_chr_close
comma
dot
id|fasync
op_assign
id|hci_vhci_chr_fasync
)brace
suffix:semicolon
DECL|variable|hci_vhci_miscdev
r_static
r_struct
id|miscdevice
id|hci_vhci_miscdev
op_assign
(brace
id|VHCI_MINOR
comma
l_string|&quot;hci_vhci&quot;
comma
op_amp
id|hci_vhci_fops
)brace
suffix:semicolon
DECL|function|hci_vhci_init
r_int
id|__init
id|hci_vhci_init
c_func
(paren
r_void
)paren
(brace
id|BT_INFO
c_func
(paren
l_string|&quot;VHCI driver ver %s&quot;
comma
id|VERSION
)paren
suffix:semicolon
r_if
c_cond
(paren
id|misc_register
c_func
(paren
op_amp
id|hci_vhci_miscdev
)paren
)paren
(brace
id|BT_ERR
c_func
(paren
l_string|&quot;Can&squot;t register misc device %d&bslash;n&quot;
comma
id|VHCI_MINOR
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|hci_vhci_cleanup
r_void
id|hci_vhci_cleanup
c_func
(paren
r_void
)paren
(brace
id|misc_deregister
c_func
(paren
op_amp
id|hci_vhci_miscdev
)paren
suffix:semicolon
)brace
DECL|variable|hci_vhci_init
id|module_init
c_func
(paren
id|hci_vhci_init
)paren
suffix:semicolon
DECL|variable|hci_vhci_cleanup
id|module_exit
c_func
(paren
id|hci_vhci_cleanup
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Maxim Krasnyansky &lt;maxk@qualcomm.com&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Bluetooth VHCI driver ver &quot;
id|VERSION
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
