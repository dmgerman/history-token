multiline_comment|/*&n; * ipmi_devintf.c&n; *&n; * Linux device interface for the IPMI message handler.&n; *&n; * Author: MontaVista Software, Inc.&n; *         Corey Minyard &lt;minyard@mvista.com&gt;&n; *         source@mvista.com&n; *&n; * Copyright 2002 MontaVista Software Inc.&n; *&n; *  This program is free software; you can redistribute it and/or modify it&n; *  under the terms of the GNU General Public License as published by the&n; *  Free Software Foundation; either version 2 of the License, or (at your&n; *  option) any later version.&n; *&n; *&n; *  THIS SOFTWARE IS PROVIDED ``AS IS&squot;&squot; AND ANY EXPRESS OR IMPLIED&n; *  WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF&n; *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.&n; *  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,&n; *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,&n; *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS&n; *  OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND&n; *  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR&n; *  TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE&n; *  USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; *  You should have received a copy of the GNU General Public License along&n; *  with this program; if not, write to the Free Software Foundation, Inc.,&n; *  675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/poll.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/devfs_fs_kernel.h&gt;
macro_line|#include &lt;linux/ipmi.h&gt;
macro_line|#include &lt;asm/semaphore.h&gt;
macro_line|#include &lt;linux/init.h&gt;
DECL|struct|ipmi_file_private
r_struct
id|ipmi_file_private
(brace
DECL|member|user
id|ipmi_user_t
id|user
suffix:semicolon
DECL|member|recv_msg_lock
id|spinlock_t
id|recv_msg_lock
suffix:semicolon
DECL|member|recv_msgs
r_struct
id|list_head
id|recv_msgs
suffix:semicolon
DECL|member|file
r_struct
id|file
op_star
id|file
suffix:semicolon
DECL|member|fasync_queue
r_struct
id|fasync_struct
op_star
id|fasync_queue
suffix:semicolon
DECL|member|wait
id|wait_queue_head_t
id|wait
suffix:semicolon
DECL|member|recv_sem
r_struct
id|semaphore
id|recv_sem
suffix:semicolon
)brace
suffix:semicolon
DECL|function|file_receive_handler
r_static
r_void
id|file_receive_handler
c_func
(paren
r_struct
id|ipmi_recv_msg
op_star
id|msg
comma
r_void
op_star
id|handler_data
)paren
(brace
r_struct
id|ipmi_file_private
op_star
id|priv
op_assign
id|handler_data
suffix:semicolon
r_int
id|was_empty
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
(paren
id|priv-&gt;recv_msg_lock
)paren
comma
id|flags
)paren
suffix:semicolon
id|was_empty
op_assign
id|list_empty
c_func
(paren
op_amp
(paren
id|priv-&gt;recv_msgs
)paren
)paren
suffix:semicolon
id|list_add_tail
c_func
(paren
op_amp
(paren
id|msg-&gt;link
)paren
comma
op_amp
(paren
id|priv-&gt;recv_msgs
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|was_empty
)paren
(brace
id|wake_up_interruptible
c_func
(paren
op_amp
id|priv-&gt;wait
)paren
suffix:semicolon
id|kill_fasync
c_func
(paren
op_amp
id|priv-&gt;fasync_queue
comma
id|SIGIO
comma
id|POLL_IN
)paren
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
(paren
id|priv-&gt;recv_msg_lock
)paren
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|ipmi_poll
r_static
r_int
r_int
id|ipmi_poll
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
id|ipmi_file_private
op_star
id|priv
op_assign
id|file-&gt;private_data
suffix:semicolon
r_int
r_int
id|mask
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|priv-&gt;recv_msg_lock
comma
id|flags
)paren
suffix:semicolon
id|poll_wait
c_func
(paren
id|file
comma
op_amp
id|priv-&gt;wait
comma
id|wait
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
(paren
id|priv-&gt;recv_msgs
)paren
)paren
)paren
id|mask
op_or_assign
(paren
id|POLLIN
op_or
id|POLLRDNORM
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|priv-&gt;recv_msg_lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|mask
suffix:semicolon
)brace
DECL|function|ipmi_fasync
r_static
r_int
id|ipmi_fasync
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
id|ipmi_file_private
op_star
id|priv
op_assign
id|file-&gt;private_data
suffix:semicolon
r_int
id|result
suffix:semicolon
id|result
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
id|priv-&gt;fasync_queue
)paren
suffix:semicolon
r_return
(paren
id|result
)paren
suffix:semicolon
)brace
DECL|variable|ipmi_hndlrs
r_static
r_struct
id|ipmi_user_hndl
id|ipmi_hndlrs
op_assign
(brace
dot
id|ipmi_recv_hndl
op_assign
id|file_receive_handler
comma
)brace
suffix:semicolon
DECL|function|ipmi_open
r_static
r_int
id|ipmi_open
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
r_int
id|if_num
op_assign
id|minor
c_func
(paren
id|inode-&gt;i_rdev
)paren
suffix:semicolon
r_int
id|rv
suffix:semicolon
r_struct
id|ipmi_file_private
op_star
id|priv
suffix:semicolon
id|priv
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|priv
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|priv
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|priv-&gt;file
op_assign
id|file
suffix:semicolon
id|rv
op_assign
id|ipmi_create_user
c_func
(paren
id|if_num
comma
op_amp
id|ipmi_hndlrs
comma
id|priv
comma
op_amp
(paren
id|priv-&gt;user
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rv
)paren
(brace
id|kfree
c_func
(paren
id|priv
)paren
suffix:semicolon
r_return
id|rv
suffix:semicolon
)brace
id|file-&gt;private_data
op_assign
id|priv
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
(paren
id|priv-&gt;recv_msg_lock
)paren
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
(paren
id|priv-&gt;recv_msgs
)paren
)paren
suffix:semicolon
id|init_waitqueue_head
c_func
(paren
op_amp
id|priv-&gt;wait
)paren
suffix:semicolon
id|priv-&gt;fasync_queue
op_assign
l_int|NULL
suffix:semicolon
id|sema_init
c_func
(paren
op_amp
(paren
id|priv-&gt;recv_sem
)paren
comma
l_int|1
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ipmi_release
r_static
r_int
id|ipmi_release
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
id|ipmi_file_private
op_star
id|priv
op_assign
id|file-&gt;private_data
suffix:semicolon
r_int
id|rv
suffix:semicolon
id|rv
op_assign
id|ipmi_destroy_user
c_func
(paren
id|priv-&gt;user
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rv
)paren
r_return
id|rv
suffix:semicolon
id|ipmi_fasync
(paren
op_minus
l_int|1
comma
id|file
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* FIXME - free the messages in the list. */
id|kfree
c_func
(paren
id|priv
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ipmi_ioctl
r_static
r_int
id|ipmi_ioctl
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
id|data
)paren
(brace
r_int
id|rv
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_struct
id|ipmi_file_private
op_star
id|priv
op_assign
id|file-&gt;private_data
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|IPMICTL_SEND_COMMAND
suffix:colon
(brace
r_struct
id|ipmi_req
id|req
suffix:semicolon
r_struct
id|ipmi_addr
id|addr
suffix:semicolon
r_int
r_char
id|msgdata
(braket
id|IPMI_MAX_MSG_LENGTH
)braket
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|req
comma
(paren
r_void
op_star
)paren
id|data
comma
r_sizeof
(paren
id|req
)paren
)paren
)paren
(brace
id|rv
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
id|req.addr_len
OG
r_sizeof
(paren
r_struct
id|ipmi_addr
)paren
)paren
(brace
id|rv
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|addr
comma
id|req.addr
comma
id|req.addr_len
)paren
)paren
(brace
id|rv
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_break
suffix:semicolon
)brace
id|rv
op_assign
id|ipmi_validate_addr
c_func
(paren
op_amp
id|addr
comma
id|req.addr_len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rv
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|req.msg.data
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
id|req.msg.data_len
OG
id|IPMI_MAX_MSG_LENGTH
)paren
(brace
id|rv
op_assign
op_minus
id|EMSGSIZE
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|msgdata
comma
id|req.msg.data
comma
id|req.msg.data_len
)paren
)paren
(brace
id|rv
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_else
(brace
id|req.msg.data_len
op_assign
l_int|0
suffix:semicolon
)brace
id|req.msg.data
op_assign
id|msgdata
suffix:semicolon
id|rv
op_assign
id|ipmi_request
c_func
(paren
id|priv-&gt;user
comma
op_amp
id|addr
comma
id|req.msgid
comma
op_amp
(paren
id|req.msg
)paren
comma
l_int|0
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|IPMICTL_RECEIVE_MSG
suffix:colon
r_case
id|IPMICTL_RECEIVE_MSG_TRUNC
suffix:colon
(brace
r_struct
id|ipmi_recv
id|rsp
suffix:semicolon
r_int
id|addr_len
suffix:semicolon
r_struct
id|list_head
op_star
id|entry
suffix:semicolon
r_struct
id|ipmi_recv_msg
op_star
id|msg
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|rv
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|rsp
comma
(paren
r_void
op_star
)paren
id|data
comma
r_sizeof
(paren
id|rsp
)paren
)paren
)paren
(brace
id|rv
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* We claim a semaphore because we don&squot;t want two&n;                   users getting something from the queue at a time.&n;                   Since we have to release the spinlock before we can&n;                   copy the data to the user, it&squot;s possible another&n;                   user will grab something from the queue, too.  Then&n;                   the messages might get out of order if something&n;                   fails and the message gets put back onto the&n;                   queue.  This semaphore prevents that problem. */
id|down
c_func
(paren
op_amp
(paren
id|priv-&gt;recv_sem
)paren
)paren
suffix:semicolon
multiline_comment|/* Grab the message off the list. */
id|spin_lock_irqsave
c_func
(paren
op_amp
(paren
id|priv-&gt;recv_msg_lock
)paren
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|list_empty
c_func
(paren
op_amp
(paren
id|priv-&gt;recv_msgs
)paren
)paren
)paren
(brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
(paren
id|priv-&gt;recv_msg_lock
)paren
comma
id|flags
)paren
suffix:semicolon
id|rv
op_assign
op_minus
id|EAGAIN
suffix:semicolon
r_goto
id|recv_err
suffix:semicolon
)brace
id|entry
op_assign
id|priv-&gt;recv_msgs.next
suffix:semicolon
id|msg
op_assign
id|list_entry
c_func
(paren
id|entry
comma
r_struct
id|ipmi_recv_msg
comma
id|link
)paren
suffix:semicolon
id|list_del
c_func
(paren
id|entry
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
(paren
id|priv-&gt;recv_msg_lock
)paren
comma
id|flags
)paren
suffix:semicolon
id|addr_len
op_assign
id|ipmi_addr_length
c_func
(paren
id|msg-&gt;addr.addr_type
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rsp.addr_len
OL
id|addr_len
)paren
(brace
id|rv
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|recv_putback_on_err
suffix:semicolon
)brace
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|rsp.addr
comma
op_amp
(paren
id|msg-&gt;addr
)paren
comma
id|addr_len
)paren
)paren
(brace
id|rv
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_goto
id|recv_putback_on_err
suffix:semicolon
)brace
id|rsp.addr_len
op_assign
id|addr_len
suffix:semicolon
id|rsp.recv_type
op_assign
id|msg-&gt;recv_type
suffix:semicolon
id|rsp.msgid
op_assign
id|msg-&gt;msgid
suffix:semicolon
id|rsp.msg.netfn
op_assign
id|msg-&gt;msg.netfn
suffix:semicolon
id|rsp.msg.cmd
op_assign
id|msg-&gt;msg.cmd
suffix:semicolon
r_if
c_cond
(paren
id|msg-&gt;msg.data_len
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|rsp.msg.data_len
OL
id|msg-&gt;msg.data_len
)paren
(brace
id|rv
op_assign
op_minus
id|EMSGSIZE
suffix:semicolon
r_if
c_cond
(paren
id|cmd
op_eq
id|IPMICTL_RECEIVE_MSG_TRUNC
)paren
(brace
id|msg-&gt;msg.data_len
op_assign
id|rsp.msg.data_len
suffix:semicolon
)brace
r_else
(brace
r_goto
id|recv_putback_on_err
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|rsp.msg.data
comma
id|msg-&gt;msg.data
comma
id|msg-&gt;msg.data_len
)paren
)paren
(brace
id|rv
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_goto
id|recv_putback_on_err
suffix:semicolon
)brace
id|rsp.msg.data_len
op_assign
id|msg-&gt;msg.data_len
suffix:semicolon
)brace
r_else
(brace
id|rsp.msg.data_len
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
(paren
r_void
op_star
)paren
id|data
comma
op_amp
id|rsp
comma
r_sizeof
(paren
id|rsp
)paren
)paren
)paren
(brace
id|rv
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_goto
id|recv_putback_on_err
suffix:semicolon
)brace
id|up
c_func
(paren
op_amp
(paren
id|priv-&gt;recv_sem
)paren
)paren
suffix:semicolon
id|ipmi_free_recv_msg
c_func
(paren
id|msg
)paren
suffix:semicolon
r_break
suffix:semicolon
id|recv_putback_on_err
suffix:colon
multiline_comment|/* If we got an error, put the message back onto&n;&t;&t;   the head of the queue. */
id|spin_lock_irqsave
c_func
(paren
op_amp
(paren
id|priv-&gt;recv_msg_lock
)paren
comma
id|flags
)paren
suffix:semicolon
id|list_add
c_func
(paren
id|entry
comma
op_amp
(paren
id|priv-&gt;recv_msgs
)paren
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
(paren
id|priv-&gt;recv_msg_lock
)paren
comma
id|flags
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
(paren
id|priv-&gt;recv_sem
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
id|recv_err
suffix:colon
id|up
c_func
(paren
op_amp
(paren
id|priv-&gt;recv_sem
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|IPMICTL_REGISTER_FOR_CMD
suffix:colon
(brace
r_struct
id|ipmi_cmdspec
id|val
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|val
comma
(paren
r_void
op_star
)paren
id|data
comma
r_sizeof
(paren
id|val
)paren
)paren
)paren
(brace
id|rv
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_break
suffix:semicolon
)brace
id|rv
op_assign
id|ipmi_register_for_cmd
c_func
(paren
id|priv-&gt;user
comma
id|val.netfn
comma
id|val.cmd
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|IPMICTL_UNREGISTER_FOR_CMD
suffix:colon
(brace
r_struct
id|ipmi_cmdspec
id|val
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|val
comma
(paren
r_void
op_star
)paren
id|data
comma
r_sizeof
(paren
id|val
)paren
)paren
)paren
(brace
id|rv
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_break
suffix:semicolon
)brace
id|rv
op_assign
id|ipmi_unregister_for_cmd
c_func
(paren
id|priv-&gt;user
comma
id|val.netfn
comma
id|val.cmd
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|IPMICTL_SET_GETS_EVENTS_CMD
suffix:colon
(brace
r_int
id|val
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|val
comma
(paren
r_void
op_star
)paren
id|data
comma
r_sizeof
(paren
id|val
)paren
)paren
)paren
(brace
id|rv
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_break
suffix:semicolon
)brace
id|rv
op_assign
id|ipmi_set_gets_events
c_func
(paren
id|priv-&gt;user
comma
id|val
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|IPMICTL_SET_MY_ADDRESS_CMD
suffix:colon
(brace
r_int
r_int
id|val
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|val
comma
(paren
r_void
op_star
)paren
id|data
comma
r_sizeof
(paren
id|val
)paren
)paren
)paren
(brace
id|rv
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_break
suffix:semicolon
)brace
id|ipmi_set_my_address
c_func
(paren
id|priv-&gt;user
comma
id|val
)paren
suffix:semicolon
id|rv
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|IPMICTL_GET_MY_ADDRESS_CMD
suffix:colon
(brace
r_int
r_int
id|val
suffix:semicolon
id|val
op_assign
id|ipmi_get_my_address
c_func
(paren
id|priv-&gt;user
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
(paren
r_void
op_star
)paren
id|data
comma
op_amp
id|val
comma
r_sizeof
(paren
id|val
)paren
)paren
)paren
(brace
id|rv
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_break
suffix:semicolon
)brace
id|rv
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|IPMICTL_SET_MY_LUN_CMD
suffix:colon
(brace
r_int
r_int
id|val
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|val
comma
(paren
r_void
op_star
)paren
id|data
comma
r_sizeof
(paren
id|val
)paren
)paren
)paren
(brace
id|rv
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_break
suffix:semicolon
)brace
id|ipmi_set_my_LUN
c_func
(paren
id|priv-&gt;user
comma
id|val
)paren
suffix:semicolon
id|rv
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|IPMICTL_GET_MY_LUN_CMD
suffix:colon
(brace
r_int
r_int
id|val
suffix:semicolon
id|val
op_assign
id|ipmi_get_my_LUN
c_func
(paren
id|priv-&gt;user
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
(paren
r_void
op_star
)paren
id|data
comma
op_amp
id|val
comma
r_sizeof
(paren
id|val
)paren
)paren
)paren
(brace
id|rv
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_break
suffix:semicolon
)brace
id|rv
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_return
id|rv
suffix:semicolon
)brace
DECL|variable|ipmi_fops
r_static
r_struct
id|file_operations
id|ipmi_fops
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|ioctl
op_assign
id|ipmi_ioctl
comma
dot
id|open
op_assign
id|ipmi_open
comma
dot
id|release
op_assign
id|ipmi_release
comma
dot
id|fasync
op_assign
id|ipmi_fasync
comma
dot
id|poll
op_assign
id|ipmi_poll
comma
)brace
suffix:semicolon
DECL|macro|DEVICE_NAME
mdefine_line|#define DEVICE_NAME     &quot;ipmidev&quot;
DECL|variable|ipmi_major
r_static
r_int
id|ipmi_major
op_assign
l_int|0
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|ipmi_major
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
DECL|variable|devfs_handle
r_static
id|devfs_handle_t
id|devfs_handle
suffix:semicolon
DECL|macro|MAX_DEVICES
mdefine_line|#define MAX_DEVICES 10
DECL|variable|handles
r_static
id|devfs_handle_t
id|handles
(braket
id|MAX_DEVICES
)braket
suffix:semicolon
DECL|function|ipmi_new_smi
r_static
r_void
id|ipmi_new_smi
c_func
(paren
r_int
id|if_num
)paren
(brace
r_char
id|name
(braket
l_int|2
)braket
suffix:semicolon
r_if
c_cond
(paren
id|if_num
OG
id|MAX_DEVICES
)paren
r_return
suffix:semicolon
id|name
(braket
l_int|0
)braket
op_assign
id|if_num
op_plus
l_char|&squot;0&squot;
suffix:semicolon
id|name
(braket
l_int|1
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|handles
(braket
id|if_num
)braket
op_assign
id|devfs_register
c_func
(paren
id|devfs_handle
comma
id|name
comma
id|DEVFS_FL_NONE
comma
id|ipmi_major
comma
id|if_num
comma
id|S_IFCHR
op_or
id|S_IRUSR
op_or
id|S_IWUSR
comma
op_amp
id|ipmi_fops
comma
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|function|ipmi_smi_gone
r_static
r_void
id|ipmi_smi_gone
c_func
(paren
r_int
id|if_num
)paren
(brace
r_if
c_cond
(paren
id|if_num
OG
id|MAX_DEVICES
)paren
r_return
suffix:semicolon
id|devfs_unregister
c_func
(paren
id|handles
(braket
id|if_num
)braket
)paren
suffix:semicolon
)brace
DECL|variable|smi_watcher
r_static
r_struct
id|ipmi_smi_watcher
id|smi_watcher
op_assign
(brace
dot
id|new_smi
op_assign
id|ipmi_new_smi
comma
dot
id|smi_gone
op_assign
id|ipmi_smi_gone
comma
)brace
suffix:semicolon
DECL|function|init_ipmi_devintf
r_static
id|__init
r_int
id|init_ipmi_devintf
c_func
(paren
r_void
)paren
(brace
r_int
id|rv
suffix:semicolon
r_if
c_cond
(paren
id|ipmi_major
OL
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|rv
op_assign
id|register_chrdev
c_func
(paren
id|ipmi_major
comma
id|DEVICE_NAME
comma
op_amp
id|ipmi_fops
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rv
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;ipmi: can&squot;t get major %d&bslash;n&quot;
comma
id|ipmi_major
)paren
suffix:semicolon
r_return
id|rv
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ipmi_major
op_eq
l_int|0
)paren
(brace
id|ipmi_major
op_assign
id|rv
suffix:semicolon
)brace
id|devfs_handle
op_assign
id|devfs_mk_dir
c_func
(paren
id|DEVICE_NAME
)paren
suffix:semicolon
id|rv
op_assign
id|ipmi_smi_watcher_register
c_func
(paren
op_amp
id|smi_watcher
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rv
)paren
(brace
id|unregister_chrdev
c_func
(paren
id|ipmi_major
comma
id|DEVICE_NAME
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;ipmi: can&squot;t register smi watcher&quot;
)paren
suffix:semicolon
r_return
id|rv
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;ipmi: device interface at char major %d&bslash;n&quot;
comma
id|ipmi_major
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|init_ipmi_devintf
id|module_init
c_func
(paren
id|init_ipmi_devintf
)paren
suffix:semicolon
DECL|function|cleanup_ipmi
r_static
id|__exit
r_void
id|cleanup_ipmi
c_func
(paren
r_void
)paren
(brace
id|ipmi_smi_watcher_unregister
c_func
(paren
op_amp
id|smi_watcher
)paren
suffix:semicolon
id|devfs_unregister
c_func
(paren
id|devfs_handle
)paren
suffix:semicolon
id|unregister_chrdev
c_func
(paren
id|ipmi_major
comma
id|DEVICE_NAME
)paren
suffix:semicolon
)brace
DECL|variable|cleanup_ipmi
id|module_exit
c_func
(paren
id|cleanup_ipmi
)paren
suffix:semicolon
macro_line|#ifndef MODULE
DECL|function|ipmi_setup
r_static
id|__init
r_int
id|ipmi_setup
(paren
r_char
op_star
id|str
)paren
(brace
r_int
id|x
suffix:semicolon
r_if
c_cond
(paren
id|get_option
(paren
op_amp
id|str
comma
op_amp
id|x
)paren
)paren
(brace
multiline_comment|/* ipmi=x sets the major number to x. */
id|ipmi_major
op_assign
id|x
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|str
comma
l_string|&quot;off&quot;
)paren
)paren
(brace
id|ipmi_major
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
macro_line|#endif
id|__setup
c_func
(paren
l_string|&quot;ipmi=&quot;
comma
id|ipmi_setup
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
