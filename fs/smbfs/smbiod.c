multiline_comment|/*&n; *  smbiod.c&n; *&n; *  Copyright (C) 2000, Charles Loep / Corel Corp.&n; *  Copyright (C) 2001, Urban Widmark&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/file.h&gt;
macro_line|#include &lt;linux/dcache.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/net.h&gt;
macro_line|#include &lt;net/ip.h&gt;
macro_line|#include &lt;linux/smb_fs.h&gt;
macro_line|#include &lt;linux/smbno.h&gt;
macro_line|#include &lt;linux/smb_mount.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &quot;smb_debug.h&quot;
macro_line|#include &quot;request.h&quot;
macro_line|#include &quot;proto.h&quot;
DECL|enum|smbiod_state
r_enum
id|smbiod_state
(brace
DECL|enumerator|SMBIOD_DEAD
id|SMBIOD_DEAD
comma
DECL|enumerator|SMBIOD_STARTING
id|SMBIOD_STARTING
comma
DECL|enumerator|SMBIOD_RUNNING
id|SMBIOD_RUNNING
comma
)brace
suffix:semicolon
DECL|variable|smbiod_state
r_static
r_enum
id|smbiod_state
id|smbiod_state
op_assign
id|SMBIOD_DEAD
suffix:semicolon
DECL|variable|smbiod_pid
r_static
id|pid_t
id|smbiod_pid
suffix:semicolon
r_static
id|DECLARE_WAIT_QUEUE_HEAD
c_func
(paren
id|smbiod_wait
)paren
suffix:semicolon
r_static
id|LIST_HEAD
c_func
(paren
id|smb_servers
)paren
suffix:semicolon
DECL|variable|servers_lock
r_static
id|spinlock_t
id|servers_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|macro|SMBIOD_DATA_READY
mdefine_line|#define SMBIOD_DATA_READY&t;(1&lt;&lt;0)
DECL|variable|smbiod_flags
r_static
r_int
id|smbiod_flags
suffix:semicolon
r_static
r_int
id|smbiod
c_func
(paren
r_void
op_star
)paren
suffix:semicolon
r_static
r_int
id|smbiod_start
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * called when there&squot;s work for us to do&n; */
DECL|function|smbiod_wake_up
r_void
id|smbiod_wake_up
c_func
(paren
)paren
(brace
r_if
c_cond
(paren
id|smbiod_state
op_eq
id|SMBIOD_DEAD
)paren
r_return
suffix:semicolon
id|set_bit
c_func
(paren
id|SMBIOD_DATA_READY
comma
op_amp
id|smbiod_flags
)paren
suffix:semicolon
id|wake_up_interruptible
c_func
(paren
op_amp
id|smbiod_wait
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * start smbiod if none is running&n; */
DECL|function|smbiod_start
r_static
r_int
id|smbiod_start
c_func
(paren
)paren
(brace
id|pid_t
id|pid
suffix:semicolon
r_if
c_cond
(paren
id|smbiod_state
op_ne
id|SMBIOD_DEAD
)paren
r_return
l_int|0
suffix:semicolon
id|smbiod_state
op_assign
id|SMBIOD_STARTING
suffix:semicolon
id|__module_get
c_func
(paren
id|THIS_MODULE
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|servers_lock
)paren
suffix:semicolon
id|pid
op_assign
id|kernel_thread
c_func
(paren
id|smbiod
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pid
OL
l_int|0
)paren
id|module_put
c_func
(paren
id|THIS_MODULE
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|servers_lock
)paren
suffix:semicolon
id|smbiod_state
op_assign
id|pid
OL
l_int|0
ques
c_cond
id|SMBIOD_DEAD
suffix:colon
id|SMBIOD_RUNNING
suffix:semicolon
id|smbiod_pid
op_assign
id|pid
suffix:semicolon
r_return
id|pid
suffix:semicolon
)brace
multiline_comment|/*&n; * register a server &amp; start smbiod if necessary&n; */
DECL|function|smbiod_register_server
r_int
id|smbiod_register_server
c_func
(paren
r_struct
id|smb_sb_info
op_star
id|server
)paren
(brace
r_int
id|ret
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|servers_lock
)paren
suffix:semicolon
id|list_add
c_func
(paren
op_amp
id|server-&gt;entry
comma
op_amp
id|smb_servers
)paren
suffix:semicolon
id|VERBOSE
c_func
(paren
l_string|&quot;%p&bslash;n&quot;
comma
id|server
)paren
suffix:semicolon
id|ret
op_assign
id|smbiod_start
c_func
(paren
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|servers_lock
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * Unregister a server&n; * Must be called with the server lock held.&n; */
DECL|function|smbiod_unregister_server
r_void
id|smbiod_unregister_server
c_func
(paren
r_struct
id|smb_sb_info
op_star
id|server
)paren
(brace
id|spin_lock
c_func
(paren
op_amp
id|servers_lock
)paren
suffix:semicolon
id|list_del_init
c_func
(paren
op_amp
id|server-&gt;entry
)paren
suffix:semicolon
id|VERBOSE
c_func
(paren
l_string|&quot;%p&bslash;n&quot;
comma
id|server
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|servers_lock
)paren
suffix:semicolon
id|smbiod_wake_up
c_func
(paren
)paren
suffix:semicolon
id|smbiod_flush
c_func
(paren
id|server
)paren
suffix:semicolon
)brace
DECL|function|smbiod_flush
r_void
id|smbiod_flush
c_func
(paren
r_struct
id|smb_sb_info
op_star
id|server
)paren
(brace
r_struct
id|list_head
op_star
id|tmp
comma
op_star
id|n
suffix:semicolon
r_struct
id|smb_request
op_star
id|req
suffix:semicolon
id|list_for_each_safe
c_func
(paren
id|tmp
comma
id|n
comma
op_amp
id|server-&gt;xmitq
)paren
(brace
id|req
op_assign
id|list_entry
c_func
(paren
id|tmp
comma
r_struct
id|smb_request
comma
id|rq_queue
)paren
suffix:semicolon
id|req-&gt;rq_errno
op_assign
op_minus
id|EIO
suffix:semicolon
id|list_del_init
c_func
(paren
op_amp
id|req-&gt;rq_queue
)paren
suffix:semicolon
id|smb_rput
c_func
(paren
id|req
)paren
suffix:semicolon
id|wake_up_interruptible
c_func
(paren
op_amp
id|req-&gt;rq_wait
)paren
suffix:semicolon
)brace
id|list_for_each_safe
c_func
(paren
id|tmp
comma
id|n
comma
op_amp
id|server-&gt;recvq
)paren
(brace
id|req
op_assign
id|list_entry
c_func
(paren
id|tmp
comma
r_struct
id|smb_request
comma
id|rq_queue
)paren
suffix:semicolon
id|req-&gt;rq_errno
op_assign
op_minus
id|EIO
suffix:semicolon
id|list_del_init
c_func
(paren
op_amp
id|req-&gt;rq_queue
)paren
suffix:semicolon
id|smb_rput
c_func
(paren
id|req
)paren
suffix:semicolon
id|wake_up_interruptible
c_func
(paren
op_amp
id|req-&gt;rq_wait
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Wake up smbmount and make it reconnect to the server.&n; * This must be called with the server locked.&n; *&n; * FIXME: add smbconnect version to this&n; */
DECL|function|smbiod_retry
r_int
id|smbiod_retry
c_func
(paren
r_struct
id|smb_sb_info
op_star
id|server
)paren
(brace
r_struct
id|list_head
op_star
id|head
suffix:semicolon
r_struct
id|smb_request
op_star
id|req
suffix:semicolon
id|pid_t
id|pid
op_assign
id|server-&gt;conn_pid
suffix:semicolon
r_int
id|result
op_assign
l_int|0
suffix:semicolon
id|VERBOSE
c_func
(paren
l_string|&quot;state: %d&bslash;n&quot;
comma
id|server-&gt;state
)paren
suffix:semicolon
r_if
c_cond
(paren
id|server-&gt;state
op_eq
id|CONN_VALID
op_logical_or
id|server-&gt;state
op_eq
id|CONN_RETRYING
)paren
r_goto
id|out
suffix:semicolon
id|smb_invalidate_inodes
c_func
(paren
id|server
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Some requests are meaningless after a retry, so we abort them.&n;&t; * One example are all requests using &squot;fileid&squot; since the files are&n;&t; * closed on retry.&n;&t; */
id|head
op_assign
id|server-&gt;xmitq.next
suffix:semicolon
r_while
c_loop
(paren
id|head
op_ne
op_amp
id|server-&gt;xmitq
)paren
(brace
id|req
op_assign
id|list_entry
c_func
(paren
id|head
comma
r_struct
id|smb_request
comma
id|rq_queue
)paren
suffix:semicolon
id|head
op_assign
id|head-&gt;next
suffix:semicolon
id|WSET
c_func
(paren
id|req-&gt;rq_header
comma
id|smb_uid
comma
op_minus
l_int|1
)paren
suffix:semicolon
id|req-&gt;rq_bytes_sent
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|req-&gt;rq_flags
op_amp
id|SMB_REQ_NORETRY
)paren
(brace
id|VERBOSE
c_func
(paren
l_string|&quot;aborting request %p on xmitq&bslash;n&quot;
comma
id|req
)paren
suffix:semicolon
id|req-&gt;rq_errno
op_assign
op_minus
id|EIO
suffix:semicolon
id|list_del_init
c_func
(paren
op_amp
id|req-&gt;rq_queue
)paren
suffix:semicolon
id|smb_rput
c_func
(paren
id|req
)paren
suffix:semicolon
id|wake_up_interruptible
c_func
(paren
op_amp
id|req-&gt;rq_wait
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t; * FIXME: test the code for retrying request we already sent&n;&t; */
id|head
op_assign
id|server-&gt;recvq.next
suffix:semicolon
r_while
c_loop
(paren
id|head
op_ne
op_amp
id|server-&gt;recvq
)paren
(brace
id|req
op_assign
id|list_entry
c_func
(paren
id|head
comma
r_struct
id|smb_request
comma
id|rq_queue
)paren
suffix:semicolon
id|head
op_assign
id|head-&gt;next
suffix:semicolon
macro_line|#if 0
r_if
c_cond
(paren
id|req-&gt;rq_flags
op_amp
id|SMB_REQ_RETRY
)paren
(brace
multiline_comment|/* must move the request to the xmitq */
id|VERBOSE
c_func
(paren
l_string|&quot;retrying request %p on recvq&bslash;n&quot;
comma
id|req
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|req-&gt;rq_queue
)paren
suffix:semicolon
id|list_add
c_func
(paren
op_amp
id|req-&gt;rq_queue
comma
op_amp
id|server-&gt;xmitq
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
macro_line|#endif
id|VERBOSE
c_func
(paren
l_string|&quot;aborting request %p on recvq&bslash;n&quot;
comma
id|req
)paren
suffix:semicolon
multiline_comment|/* req-&gt;rq_rcls = ???; */
multiline_comment|/* FIXME: set smb error code too? */
id|req-&gt;rq_errno
op_assign
op_minus
id|EIO
suffix:semicolon
id|list_del_init
c_func
(paren
op_amp
id|req-&gt;rq_queue
)paren
suffix:semicolon
id|smb_rput
c_func
(paren
id|req
)paren
suffix:semicolon
id|wake_up_interruptible
c_func
(paren
op_amp
id|req-&gt;rq_wait
)paren
suffix:semicolon
)brace
id|smb_close_socket
c_func
(paren
id|server
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pid
op_eq
l_int|0
)paren
(brace
multiline_comment|/* FIXME: this is fatal, umount? */
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;smb_retry: no connection process&bslash;n&quot;
)paren
suffix:semicolon
id|server-&gt;state
op_assign
id|CONN_RETRIED
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Change state so that only one retry per server will be started.&n;&t; */
id|server-&gt;state
op_assign
id|CONN_RETRYING
suffix:semicolon
multiline_comment|/*&n;&t; * Note: use the &quot;priv&quot; flag, as a user process may need to reconnect.&n;&t; */
id|result
op_assign
id|kill_proc
c_func
(paren
id|pid
comma
id|SIGUSR1
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
)paren
(brace
multiline_comment|/* FIXME: this is most likely fatal, umount? */
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;smb_retry: signal failed [%d]&bslash;n&quot;
comma
id|result
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|VERBOSE
c_func
(paren
l_string|&quot;signalled pid %d&bslash;n&quot;
comma
id|pid
)paren
suffix:semicolon
multiline_comment|/* FIXME: The retried requests should perhaps get a &quot;time boost&quot;. */
id|out
suffix:colon
r_return
id|result
suffix:semicolon
)brace
multiline_comment|/*&n; * Currently handles lockingX packets.&n; */
DECL|function|smbiod_handle_request
r_static
r_void
id|smbiod_handle_request
c_func
(paren
r_struct
id|smb_sb_info
op_star
id|server
)paren
(brace
id|PARANOIA
c_func
(paren
l_string|&quot;smbiod got a request ... and we don&squot;t implement oplocks!&bslash;n&quot;
)paren
suffix:semicolon
id|server-&gt;rstate
op_assign
id|SMB_RECV_DROP
suffix:semicolon
)brace
multiline_comment|/*&n; * Do some IO for one server.&n; */
DECL|function|smbiod_doio
r_static
r_void
id|smbiod_doio
c_func
(paren
r_struct
id|smb_sb_info
op_star
id|server
)paren
(brace
r_int
id|result
suffix:semicolon
r_int
id|maxwork
op_assign
l_int|7
suffix:semicolon
r_if
c_cond
(paren
id|server-&gt;state
op_ne
id|CONN_VALID
)paren
r_goto
id|out
suffix:semicolon
r_do
(brace
id|result
op_assign
id|smb_request_recv
c_func
(paren
id|server
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
OL
l_int|0
)paren
(brace
id|server-&gt;state
op_assign
id|CONN_INVALID
suffix:semicolon
id|smbiod_retry
c_func
(paren
id|server
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
multiline_comment|/* reconnecting is slow */
)brace
r_else
r_if
c_cond
(paren
id|server-&gt;rstate
op_eq
id|SMB_RECV_REQUEST
)paren
id|smbiod_handle_request
c_func
(paren
id|server
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|result
OG
l_int|0
op_logical_and
id|maxwork
op_decrement
OG
l_int|0
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * If there is more to read then we want to be sure to wake up again.&n;&t; */
r_if
c_cond
(paren
id|server-&gt;state
op_ne
id|CONN_VALID
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|smb_recv_available
c_func
(paren
id|server
)paren
OG
l_int|0
)paren
id|set_bit
c_func
(paren
id|SMBIOD_DATA_READY
comma
op_amp
id|smbiod_flags
)paren
suffix:semicolon
r_do
(brace
id|result
op_assign
id|smb_request_send_server
c_func
(paren
id|server
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
OL
l_int|0
)paren
(brace
id|server-&gt;state
op_assign
id|CONN_INVALID
suffix:semicolon
id|smbiod_retry
c_func
(paren
id|server
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
multiline_comment|/* reconnecting is slow */
)brace
)brace
r_while
c_loop
(paren
id|result
OG
l_int|0
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * If the last request was not sent out we want to wake up again.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|server-&gt;xmitq
)paren
)paren
id|set_bit
c_func
(paren
id|SMBIOD_DATA_READY
comma
op_amp
id|smbiod_flags
)paren
suffix:semicolon
id|out
suffix:colon
r_return
suffix:semicolon
)brace
multiline_comment|/*&n; * smbiod kernel thread&n; */
DECL|function|smbiod
r_static
r_int
id|smbiod
c_func
(paren
r_void
op_star
id|unused
)paren
(brace
id|daemonize
c_func
(paren
l_string|&quot;smbiod&quot;
)paren
suffix:semicolon
id|allow_signal
c_func
(paren
id|SIGKILL
)paren
suffix:semicolon
id|VERBOSE
c_func
(paren
l_string|&quot;SMB Kernel thread starting (%d) ...&bslash;n&quot;
comma
id|current-&gt;pid
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_struct
id|smb_sb_info
op_star
id|server
suffix:semicolon
r_struct
id|list_head
op_star
id|pos
comma
op_star
id|n
suffix:semicolon
multiline_comment|/* FIXME: Use poll? */
id|wait_event_interruptible
c_func
(paren
id|smbiod_wait
comma
id|test_bit
c_func
(paren
id|SMBIOD_DATA_READY
comma
op_amp
id|smbiod_flags
)paren
)paren
suffix:semicolon
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
id|spin_lock
c_func
(paren
op_amp
id|servers_lock
)paren
suffix:semicolon
id|smbiod_state
op_assign
id|SMBIOD_DEAD
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|servers_lock
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|clear_bit
c_func
(paren
id|SMBIOD_DATA_READY
comma
op_amp
id|smbiod_flags
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|servers_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|list_empty
c_func
(paren
op_amp
id|smb_servers
)paren
)paren
(brace
id|smbiod_state
op_assign
id|SMBIOD_DEAD
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|servers_lock
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|list_for_each_safe
c_func
(paren
id|pos
comma
id|n
comma
op_amp
id|smb_servers
)paren
(brace
id|server
op_assign
id|list_entry
c_func
(paren
id|pos
comma
r_struct
id|smb_sb_info
comma
id|entry
)paren
suffix:semicolon
id|VERBOSE
c_func
(paren
l_string|&quot;checking server %p&bslash;n&quot;
comma
id|server
)paren
suffix:semicolon
r_if
c_cond
(paren
id|server-&gt;state
op_eq
id|CONN_VALID
)paren
(brace
id|spin_unlock
c_func
(paren
op_amp
id|servers_lock
)paren
suffix:semicolon
id|smb_lock_server
c_func
(paren
id|server
)paren
suffix:semicolon
id|smbiod_doio
c_func
(paren
id|server
)paren
suffix:semicolon
id|smb_unlock_server
c_func
(paren
id|server
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|servers_lock
)paren
suffix:semicolon
)brace
)brace
id|spin_unlock
c_func
(paren
op_amp
id|servers_lock
)paren
suffix:semicolon
)brace
id|VERBOSE
c_func
(paren
l_string|&quot;SMB Kernel thread exiting (%d) ...&bslash;n&quot;
comma
id|current-&gt;pid
)paren
suffix:semicolon
id|module_put_and_exit
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
eof
