multiline_comment|/*&n; *     SUCS NET3:&n; *&n; *     Generic stream handling routines. These are generic for most&n; *     protocols. Even IP. Tonight 8-).&n; *     This is used because TCP, LLC (others too) layer all have mostly&n; *     identical sendmsg() and recvmsg() code.&n; *     So we (will) share it here.&n; *&n; *     Authors:        Arnaldo Carvalho de Melo &lt;acme@conectiva.com.br&gt;&n; *                     (from old tcp.c code)&n; *                     Alan Cox &lt;alan@redhat.com&gt; (Borrowed comments 8-))&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/net.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/tcp.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#include &lt;net/sock.h&gt;
multiline_comment|/**&n; * sk_stream_write_space - stream socket write_space callback.&n; * sk - socket&n; *&n; * FIXME: write proper description&n; */
DECL|function|sk_stream_write_space
r_void
id|sk_stream_write_space
c_func
(paren
r_struct
id|sock
op_star
id|sk
)paren
(brace
r_struct
id|socket
op_star
id|sock
op_assign
id|sk-&gt;sk_socket
suffix:semicolon
r_if
c_cond
(paren
id|sk_stream_wspace
c_func
(paren
id|sk
)paren
op_ge
id|sk_stream_min_wspace
c_func
(paren
id|sk
)paren
op_logical_and
id|sock
)paren
(brace
id|clear_bit
c_func
(paren
id|SOCK_NOSPACE
comma
op_amp
id|sock-&gt;flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sk-&gt;sk_sleep
op_logical_and
id|waitqueue_active
c_func
(paren
id|sk-&gt;sk_sleep
)paren
)paren
id|wake_up_interruptible
c_func
(paren
id|sk-&gt;sk_sleep
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sock-&gt;fasync_list
op_logical_and
op_logical_neg
(paren
id|sk-&gt;sk_shutdown
op_amp
id|SEND_SHUTDOWN
)paren
)paren
id|sock_wake_async
c_func
(paren
id|sock
comma
l_int|2
comma
id|POLL_OUT
)paren
suffix:semicolon
)brace
)brace
DECL|variable|sk_stream_write_space
id|EXPORT_SYMBOL
c_func
(paren
id|sk_stream_write_space
)paren
suffix:semicolon
multiline_comment|/**&n; * sk_stream_wait_connect - Wait for a socket to get into the connected state&n; * @sk - sock to wait on&n; * @timeo_p - for how long to wait&n; *&n; * Must be called with the socket locked.&n; */
DECL|function|sk_stream_wait_connect
r_int
id|sk_stream_wait_connect
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_int
op_star
id|timeo_p
)paren
(brace
r_struct
id|task_struct
op_star
id|tsk
op_assign
id|current
suffix:semicolon
id|DEFINE_WAIT
c_func
(paren
id|wait
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
r_if
c_cond
(paren
id|sk-&gt;sk_err
)paren
r_return
id|sock_error
c_func
(paren
id|sk
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
l_int|1
op_lshift
id|sk-&gt;sk_state
)paren
op_amp
op_complement
(paren
id|TCPF_SYN_SENT
op_or
id|TCPF_SYN_RECV
)paren
)paren
r_return
op_minus
id|EPIPE
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_star
id|timeo_p
)paren
r_return
op_minus
id|EAGAIN
suffix:semicolon
r_if
c_cond
(paren
id|signal_pending
c_func
(paren
id|tsk
)paren
)paren
r_return
id|sock_intr_errno
c_func
(paren
op_star
id|timeo_p
)paren
suffix:semicolon
id|prepare_to_wait
c_func
(paren
id|sk-&gt;sk_sleep
comma
op_amp
id|wait
comma
id|TASK_INTERRUPTIBLE
)paren
suffix:semicolon
id|sk-&gt;sk_write_pending
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|sk_wait_event
c_func
(paren
id|sk
comma
id|timeo_p
comma
op_logical_neg
(paren
(paren
l_int|1
op_lshift
id|sk-&gt;sk_state
)paren
op_amp
op_complement
(paren
id|TCPF_ESTABLISHED
op_or
id|TCPF_CLOSE_WAIT
)paren
)paren
)paren
)paren
r_break
suffix:semicolon
id|finish_wait
c_func
(paren
id|sk-&gt;sk_sleep
comma
op_amp
id|wait
)paren
suffix:semicolon
id|sk-&gt;sk_write_pending
op_decrement
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|sk_stream_wait_connect
id|EXPORT_SYMBOL
c_func
(paren
id|sk_stream_wait_connect
)paren
suffix:semicolon
multiline_comment|/**&n; * sk_stream_closing - Return 1 if we still have things to send in our buffers.&n; * @sk - socket to verify&n; */
DECL|function|sk_stream_closing
r_static
r_inline
r_int
id|sk_stream_closing
c_func
(paren
r_struct
id|sock
op_star
id|sk
)paren
(brace
r_return
(paren
l_int|1
op_lshift
id|sk-&gt;sk_state
)paren
op_amp
(paren
id|TCPF_FIN_WAIT1
op_or
id|TCPF_CLOSING
op_or
id|TCPF_LAST_ACK
)paren
suffix:semicolon
)brace
DECL|function|sk_stream_wait_close
r_void
id|sk_stream_wait_close
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_int
id|timeout
)paren
(brace
r_if
c_cond
(paren
id|timeout
)paren
(brace
id|DEFINE_WAIT
c_func
(paren
id|wait
)paren
suffix:semicolon
r_do
(brace
id|prepare_to_wait
c_func
(paren
id|sk-&gt;sk_sleep
comma
op_amp
id|wait
comma
id|TASK_INTERRUPTIBLE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sk_wait_event
c_func
(paren
id|sk
comma
op_amp
id|timeout
comma
op_logical_neg
id|sk_stream_closing
c_func
(paren
id|sk
)paren
)paren
)paren
r_break
suffix:semicolon
)brace
r_while
c_loop
(paren
op_logical_neg
id|signal_pending
c_func
(paren
id|current
)paren
op_logical_and
id|timeout
)paren
suffix:semicolon
id|finish_wait
c_func
(paren
id|sk-&gt;sk_sleep
comma
op_amp
id|wait
)paren
suffix:semicolon
)brace
)brace
DECL|variable|sk_stream_wait_close
id|EXPORT_SYMBOL
c_func
(paren
id|sk_stream_wait_close
)paren
suffix:semicolon
multiline_comment|/**&n; * sk_stream_wait_memory - Wait for more memory for a socket&n; * @sk - socket to wait for memory&n; * @timeo_p - for how long&n; */
DECL|function|sk_stream_wait_memory
r_int
id|sk_stream_wait_memory
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_int
op_star
id|timeo_p
)paren
(brace
r_int
id|err
op_assign
l_int|0
suffix:semicolon
r_int
id|vm_wait
op_assign
l_int|0
suffix:semicolon
r_int
id|current_timeo
op_assign
op_star
id|timeo_p
suffix:semicolon
id|DEFINE_WAIT
c_func
(paren
id|wait
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sk_stream_memory_free
c_func
(paren
id|sk
)paren
)paren
id|current_timeo
op_assign
id|vm_wait
op_assign
(paren
id|net_random
c_func
(paren
)paren
op_mod
(paren
id|HZ
op_div
l_int|5
)paren
)paren
op_plus
l_int|2
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
id|set_bit
c_func
(paren
id|SOCK_ASYNC_NOSPACE
comma
op_amp
id|sk-&gt;sk_socket-&gt;flags
)paren
suffix:semicolon
id|prepare_to_wait
c_func
(paren
id|sk-&gt;sk_sleep
comma
op_amp
id|wait
comma
id|TASK_INTERRUPTIBLE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sk-&gt;sk_err
op_logical_or
(paren
id|sk-&gt;sk_shutdown
op_amp
id|SEND_SHUTDOWN
)paren
)paren
r_goto
id|do_error
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_star
id|timeo_p
)paren
r_goto
id|do_nonblock
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
r_goto
id|do_interrupted
suffix:semicolon
id|clear_bit
c_func
(paren
id|SOCK_ASYNC_NOSPACE
comma
op_amp
id|sk-&gt;sk_socket-&gt;flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sk_stream_memory_free
c_func
(paren
id|sk
)paren
op_logical_and
op_logical_neg
id|vm_wait
)paren
r_break
suffix:semicolon
id|set_bit
c_func
(paren
id|SOCK_NOSPACE
comma
op_amp
id|sk-&gt;sk_socket-&gt;flags
)paren
suffix:semicolon
id|sk-&gt;sk_write_pending
op_increment
suffix:semicolon
id|sk_wait_event
c_func
(paren
id|sk
comma
op_amp
id|current_timeo
comma
id|sk_stream_memory_free
c_func
(paren
id|sk
)paren
op_logical_and
id|vm_wait
)paren
suffix:semicolon
id|sk-&gt;sk_write_pending
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|vm_wait
)paren
(brace
id|vm_wait
op_sub_assign
id|current_timeo
suffix:semicolon
id|current_timeo
op_assign
op_star
id|timeo_p
suffix:semicolon
r_if
c_cond
(paren
id|current_timeo
op_ne
id|MAX_SCHEDULE_TIMEOUT
op_logical_and
(paren
id|current_timeo
op_sub_assign
id|vm_wait
)paren
OL
l_int|0
)paren
id|current_timeo
op_assign
l_int|0
suffix:semicolon
id|vm_wait
op_assign
l_int|0
suffix:semicolon
)brace
op_star
id|timeo_p
op_assign
id|current_timeo
suffix:semicolon
)brace
id|out
suffix:colon
id|finish_wait
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
id|do_error
suffix:colon
id|err
op_assign
op_minus
id|EPIPE
suffix:semicolon
r_goto
id|out
suffix:semicolon
id|do_nonblock
suffix:colon
id|err
op_assign
op_minus
id|EAGAIN
suffix:semicolon
r_goto
id|out
suffix:semicolon
id|do_interrupted
suffix:colon
id|err
op_assign
id|sock_intr_errno
c_func
(paren
op_star
id|timeo_p
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
DECL|variable|sk_stream_wait_memory
id|EXPORT_SYMBOL
c_func
(paren
id|sk_stream_wait_memory
)paren
suffix:semicolon
eof
