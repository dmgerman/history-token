multiline_comment|/* -*- c -*- --------------------------------------------------------------- *&n; *&n; * linux/fs/autofs/waitq.c&n; *&n; *  Copyright 1997-1998 Transmeta Corporation -- All Rights Reserved&n; *&n; * This file is part of the Linux kernel and is made available under&n; * the terms of the GNU General Public License, version 2, or at your&n; * option, any later version, incorporated herein by reference.&n; *&n; * ------------------------------------------------------------------------- */
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/file.h&gt;
macro_line|#include &quot;autofs_i.h&quot;
multiline_comment|/* We make this a static variable rather than a part of the superblock; it&n;   is better if we don&squot;t reassign numbers easily even across filesystems */
DECL|variable|autofs4_next_wait_queue
r_static
id|autofs_wqt_t
id|autofs4_next_wait_queue
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* These are the signals we allow interrupting a pending mount */
DECL|macro|SHUTDOWN_SIGS
mdefine_line|#define SHUTDOWN_SIGS&t;(sigmask(SIGKILL) | sigmask(SIGINT) | sigmask(SIGQUIT))
DECL|function|autofs4_catatonic_mode
r_void
id|autofs4_catatonic_mode
c_func
(paren
r_struct
id|autofs_sb_info
op_star
id|sbi
)paren
(brace
r_struct
id|autofs_wait_queue
op_star
id|wq
comma
op_star
id|nwq
suffix:semicolon
id|DPRINTK
c_func
(paren
(paren
l_string|&quot;autofs: entering catatonic mode&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|sbi-&gt;catatonic
op_assign
l_int|1
suffix:semicolon
id|wq
op_assign
id|sbi-&gt;queues
suffix:semicolon
id|sbi-&gt;queues
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* Erase all wait queues */
r_while
c_loop
(paren
id|wq
)paren
(brace
id|nwq
op_assign
id|wq-&gt;next
suffix:semicolon
id|wq-&gt;status
op_assign
op_minus
id|ENOENT
suffix:semicolon
multiline_comment|/* Magic is gone - report failure */
id|kfree
c_func
(paren
id|wq-&gt;name
)paren
suffix:semicolon
id|wq-&gt;name
op_assign
l_int|NULL
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|wq-&gt;queue
)paren
suffix:semicolon
id|wq
op_assign
id|nwq
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sbi-&gt;pipe
)paren
(brace
id|fput
c_func
(paren
id|sbi-&gt;pipe
)paren
suffix:semicolon
multiline_comment|/* Close the pipe */
id|sbi-&gt;pipe
op_assign
l_int|NULL
suffix:semicolon
)brace
id|shrink_dcache_sb
c_func
(paren
id|sbi-&gt;sb
)paren
suffix:semicolon
)brace
DECL|function|autofs4_write
r_static
r_int
id|autofs4_write
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_const
r_void
op_star
id|addr
comma
r_int
id|bytes
)paren
(brace
r_int
r_int
id|sigpipe
comma
id|flags
suffix:semicolon
id|mm_segment_t
id|fs
suffix:semicolon
r_const
r_char
op_star
id|data
op_assign
(paren
r_const
r_char
op_star
)paren
id|addr
suffix:semicolon
id|ssize_t
id|wr
op_assign
l_int|0
suffix:semicolon
multiline_comment|/** WARNING: this is not safe for writing more than PIPE_BUF bytes! **/
id|sigpipe
op_assign
id|sigismember
c_func
(paren
op_amp
id|current-&gt;pending.signal
comma
id|SIGPIPE
)paren
suffix:semicolon
multiline_comment|/* Save pointer to user space and point back to kernel space */
id|fs
op_assign
id|get_fs
c_func
(paren
)paren
suffix:semicolon
id|set_fs
c_func
(paren
id|KERNEL_DS
)paren
suffix:semicolon
r_while
c_loop
(paren
id|bytes
op_logical_and
(paren
id|wr
op_assign
id|file-&gt;f_op
op_member_access_from_pointer
id|write
c_func
(paren
id|file
comma
id|data
comma
id|bytes
comma
op_amp
id|file-&gt;f_pos
)paren
)paren
OG
l_int|0
)paren
(brace
id|data
op_add_assign
id|wr
suffix:semicolon
id|bytes
op_sub_assign
id|wr
suffix:semicolon
)brace
id|set_fs
c_func
(paren
id|fs
)paren
suffix:semicolon
multiline_comment|/* Keep the currently executing process from receiving a&n;&t;   SIGPIPE unless it was already supposed to get one */
r_if
c_cond
(paren
id|wr
op_eq
op_minus
id|EPIPE
op_logical_and
op_logical_neg
id|sigpipe
)paren
(brace
id|spin_lock_irqsave
c_func
(paren
op_amp
id|current-&gt;sigmask_lock
comma
id|flags
)paren
suffix:semicolon
id|sigdelset
c_func
(paren
op_amp
id|current-&gt;pending.signal
comma
id|SIGPIPE
)paren
suffix:semicolon
id|recalc_sigpending
c_func
(paren
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|current-&gt;sigmask_lock
comma
id|flags
)paren
suffix:semicolon
)brace
r_return
(paren
id|bytes
OG
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|autofs4_notify_daemon
r_static
r_void
id|autofs4_notify_daemon
c_func
(paren
r_struct
id|autofs_sb_info
op_star
id|sbi
comma
r_struct
id|autofs_wait_queue
op_star
id|wq
comma
r_int
id|type
)paren
(brace
r_union
id|autofs_packet_union
id|pkt
suffix:semicolon
r_int
id|pktsz
suffix:semicolon
id|DPRINTK
c_func
(paren
(paren
l_string|&quot;autofs_notify: wait id = 0x%08lx, name = %.*s, type=%d&bslash;n&quot;
comma
id|wq-&gt;wait_queue_token
comma
id|wq-&gt;len
comma
id|wq-&gt;name
comma
id|type
)paren
)paren
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|pkt
comma
l_int|0
comma
r_sizeof
id|pkt
)paren
suffix:semicolon
multiline_comment|/* For security reasons */
id|pkt.hdr.proto_version
op_assign
id|sbi-&gt;version
suffix:semicolon
id|pkt.hdr.type
op_assign
id|type
suffix:semicolon
r_if
c_cond
(paren
id|type
op_eq
id|autofs_ptype_missing
)paren
(brace
r_struct
id|autofs_packet_missing
op_star
id|mp
op_assign
op_amp
id|pkt.missing
suffix:semicolon
id|pktsz
op_assign
r_sizeof
(paren
op_star
id|mp
)paren
suffix:semicolon
id|mp-&gt;wait_queue_token
op_assign
id|wq-&gt;wait_queue_token
suffix:semicolon
id|mp-&gt;len
op_assign
id|wq-&gt;len
suffix:semicolon
id|memcpy
c_func
(paren
id|mp-&gt;name
comma
id|wq-&gt;name
comma
id|wq-&gt;len
)paren
suffix:semicolon
id|mp-&gt;name
(braket
id|wq-&gt;len
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|type
op_eq
id|autofs_ptype_expire_multi
)paren
(brace
r_struct
id|autofs_packet_expire_multi
op_star
id|ep
op_assign
op_amp
id|pkt.expire_multi
suffix:semicolon
id|pktsz
op_assign
r_sizeof
(paren
op_star
id|ep
)paren
suffix:semicolon
id|ep-&gt;wait_queue_token
op_assign
id|wq-&gt;wait_queue_token
suffix:semicolon
id|ep-&gt;len
op_assign
id|wq-&gt;len
suffix:semicolon
id|memcpy
c_func
(paren
id|ep-&gt;name
comma
id|wq-&gt;name
comma
id|wq-&gt;len
)paren
suffix:semicolon
id|ep-&gt;name
(braket
id|wq-&gt;len
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
l_string|&quot;autofs_notify_daemon: bad type %d!&bslash;n&quot;
comma
id|type
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|autofs4_write
c_func
(paren
id|sbi-&gt;pipe
comma
op_amp
id|pkt
comma
id|pktsz
)paren
)paren
id|autofs4_catatonic_mode
c_func
(paren
id|sbi
)paren
suffix:semicolon
)brace
DECL|function|autofs4_wait
r_int
id|autofs4_wait
c_func
(paren
r_struct
id|autofs_sb_info
op_star
id|sbi
comma
r_struct
id|qstr
op_star
id|name
comma
r_enum
id|autofs_notify
id|notify
)paren
(brace
r_struct
id|autofs_wait_queue
op_star
id|wq
suffix:semicolon
r_int
id|status
suffix:semicolon
multiline_comment|/* In catatonic mode, we don&squot;t wait for nobody */
r_if
c_cond
(paren
id|sbi-&gt;catatonic
)paren
r_return
op_minus
id|ENOENT
suffix:semicolon
multiline_comment|/* We shouldn&squot;t be able to get here, but just in case */
r_if
c_cond
(paren
id|name-&gt;len
OG
id|NAME_MAX
)paren
r_return
op_minus
id|ENOENT
suffix:semicolon
r_for
c_loop
(paren
id|wq
op_assign
id|sbi-&gt;queues
suffix:semicolon
id|wq
suffix:semicolon
id|wq
op_assign
id|wq-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|wq-&gt;hash
op_eq
id|name-&gt;hash
op_logical_and
id|wq-&gt;len
op_eq
id|name-&gt;len
op_logical_and
id|wq-&gt;name
op_logical_and
op_logical_neg
id|memcmp
c_func
(paren
id|wq-&gt;name
comma
id|name-&gt;name
comma
id|name-&gt;len
)paren
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|wq
)paren
(brace
multiline_comment|/* Create a new wait queue */
id|wq
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|autofs_wait_queue
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|wq
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|wq-&gt;name
op_assign
id|kmalloc
c_func
(paren
id|name-&gt;len
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|wq-&gt;name
)paren
(brace
id|kfree
c_func
(paren
id|wq
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|wq-&gt;wait_queue_token
op_assign
id|autofs4_next_wait_queue
suffix:semicolon
r_if
c_cond
(paren
op_increment
id|autofs4_next_wait_queue
op_eq
l_int|0
)paren
id|autofs4_next_wait_queue
op_assign
l_int|1
suffix:semicolon
id|init_waitqueue_head
c_func
(paren
op_amp
id|wq-&gt;queue
)paren
suffix:semicolon
id|wq-&gt;hash
op_assign
id|name-&gt;hash
suffix:semicolon
id|wq-&gt;len
op_assign
id|name-&gt;len
suffix:semicolon
id|wq-&gt;status
op_assign
op_minus
id|EINTR
suffix:semicolon
multiline_comment|/* Status return if interrupted */
id|memcpy
c_func
(paren
id|wq-&gt;name
comma
id|name-&gt;name
comma
id|name-&gt;len
)paren
suffix:semicolon
id|wq-&gt;next
op_assign
id|sbi-&gt;queues
suffix:semicolon
id|sbi-&gt;queues
op_assign
id|wq
suffix:semicolon
id|DPRINTK
c_func
(paren
(paren
l_string|&quot;autofs_wait: new wait id = 0x%08lx, name = %.*s, nfy=%d&bslash;n&quot;
comma
id|wq-&gt;wait_queue_token
comma
id|wq-&gt;len
comma
id|wq-&gt;name
comma
id|notify
)paren
)paren
suffix:semicolon
multiline_comment|/* autofs4_notify_daemon() may block */
id|wq-&gt;wait_ctr
op_assign
l_int|2
suffix:semicolon
r_if
c_cond
(paren
id|notify
op_ne
id|NFY_NONE
)paren
(brace
id|autofs4_notify_daemon
c_func
(paren
id|sbi
comma
id|wq
comma
id|notify
op_eq
id|NFY_MOUNT
ques
c_cond
id|autofs_ptype_missing
suffix:colon
id|autofs_ptype_expire_multi
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
id|wq-&gt;wait_ctr
op_increment
suffix:semicolon
id|DPRINTK
c_func
(paren
(paren
l_string|&quot;autofs_wait: existing wait id = 0x%08lx, name = %.*s, nfy=%d&bslash;n&quot;
comma
id|wq-&gt;wait_queue_token
comma
id|wq-&gt;len
comma
id|wq-&gt;name
comma
id|notify
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* wq-&gt;name is NULL if and only if the lock is already released */
r_if
c_cond
(paren
id|sbi-&gt;catatonic
)paren
(brace
multiline_comment|/* We might have slept, so check again for catatonic mode */
id|wq-&gt;status
op_assign
op_minus
id|ENOENT
suffix:semicolon
r_if
c_cond
(paren
id|wq-&gt;name
)paren
(brace
id|kfree
c_func
(paren
id|wq-&gt;name
)paren
suffix:semicolon
id|wq-&gt;name
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|wq-&gt;name
)paren
(brace
multiline_comment|/* Block all but &quot;shutdown&quot; signals while waiting */
id|sigset_t
id|oldset
suffix:semicolon
r_int
r_int
id|irqflags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|current-&gt;sigmask_lock
comma
id|irqflags
)paren
suffix:semicolon
id|oldset
op_assign
id|current-&gt;blocked
suffix:semicolon
id|siginitsetinv
c_func
(paren
op_amp
id|current-&gt;blocked
comma
id|SHUTDOWN_SIGS
op_amp
op_complement
id|oldset.sig
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|recalc_sigpending
c_func
(paren
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|current-&gt;sigmask_lock
comma
id|irqflags
)paren
suffix:semicolon
id|interruptible_sleep_on
c_func
(paren
op_amp
id|wq-&gt;queue
)paren
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|current-&gt;sigmask_lock
comma
id|irqflags
)paren
suffix:semicolon
id|current-&gt;blocked
op_assign
id|oldset
suffix:semicolon
id|recalc_sigpending
c_func
(paren
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|current-&gt;sigmask_lock
comma
id|irqflags
)paren
suffix:semicolon
)brace
r_else
(brace
id|DPRINTK
c_func
(paren
(paren
l_string|&quot;autofs_wait: skipped sleeping&bslash;n&quot;
)paren
)paren
suffix:semicolon
)brace
id|status
op_assign
id|wq-&gt;status
suffix:semicolon
r_if
c_cond
(paren
op_decrement
id|wq-&gt;wait_ctr
op_eq
l_int|0
)paren
multiline_comment|/* Are we the last process to need status? */
id|kfree
c_func
(paren
id|wq
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
DECL|function|autofs4_wait_release
r_int
id|autofs4_wait_release
c_func
(paren
r_struct
id|autofs_sb_info
op_star
id|sbi
comma
id|autofs_wqt_t
id|wait_queue_token
comma
r_int
id|status
)paren
(brace
r_struct
id|autofs_wait_queue
op_star
id|wq
comma
op_star
op_star
id|wql
suffix:semicolon
r_for
c_loop
(paren
id|wql
op_assign
op_amp
id|sbi-&gt;queues
suffix:semicolon
(paren
id|wq
op_assign
op_star
id|wql
)paren
suffix:semicolon
id|wql
op_assign
op_amp
id|wq-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|wq-&gt;wait_queue_token
op_eq
id|wait_queue_token
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|wq
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
op_star
id|wql
op_assign
id|wq-&gt;next
suffix:semicolon
multiline_comment|/* Unlink from chain */
id|kfree
c_func
(paren
id|wq-&gt;name
)paren
suffix:semicolon
id|wq-&gt;name
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* Do not wait on this queue */
id|wq-&gt;status
op_assign
id|status
suffix:semicolon
r_if
c_cond
(paren
op_decrement
id|wq-&gt;wait_ctr
op_eq
l_int|0
)paren
multiline_comment|/* Is anyone still waiting for this guy? */
id|kfree
c_func
(paren
id|wq
)paren
suffix:semicolon
r_else
id|wake_up
c_func
(paren
op_amp
id|wq-&gt;queue
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
