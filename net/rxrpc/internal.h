multiline_comment|/* internal.h: internal Rx RPC stuff&n; *&n; * Copyright (c) 2002   David Howells (dhowells@redhat.com).&n; */
macro_line|#ifndef RXRPC_INTERNAL_H
DECL|macro|RXRPC_INTERNAL_H
mdefine_line|#define RXRPC_INTERNAL_H
macro_line|#include &lt;linux/compiler.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
multiline_comment|/*&n; * debug accounting&n; */
macro_line|#if 1
DECL|macro|__RXACCT_DECL
mdefine_line|#define __RXACCT_DECL(X) X
DECL|macro|__RXACCT
mdefine_line|#define __RXACCT(X) do { X; } while(0) 
macro_line|#else
DECL|macro|__RXACCT_DECL
mdefine_line|#define __RXACCT_DECL(X)
DECL|macro|__RXACCT
mdefine_line|#define __RXACCT(X) do { } while(0)
macro_line|#endif
id|__RXACCT_DECL
c_func
(paren
r_extern
id|atomic_t
id|rxrpc_transport_count
)paren
suffix:semicolon
id|__RXACCT_DECL
c_func
(paren
r_extern
id|atomic_t
id|rxrpc_peer_count
)paren
suffix:semicolon
id|__RXACCT_DECL
c_func
(paren
r_extern
id|atomic_t
id|rxrpc_connection_count
)paren
suffix:semicolon
id|__RXACCT_DECL
c_func
(paren
r_extern
id|atomic_t
id|rxrpc_call_count
)paren
suffix:semicolon
id|__RXACCT_DECL
c_func
(paren
r_extern
id|atomic_t
id|rxrpc_message_count
)paren
suffix:semicolon
multiline_comment|/*&n; * debug tracing&n; */
DECL|macro|kenter
mdefine_line|#define kenter(FMT, a...)&t;printk(&quot;==&gt; %s(&quot;FMT&quot;)&bslash;n&quot;,__FUNCTION__ , ##a)
DECL|macro|kleave
mdefine_line|#define kleave(FMT, a...)&t;printk(&quot;&lt;== %s()&quot;FMT&quot;&bslash;n&quot;,__FUNCTION__ , ##a)
DECL|macro|kdebug
mdefine_line|#define kdebug(FMT, a...)&t;printk(&quot;    &quot;FMT&quot;&bslash;n&quot; , ##a)
DECL|macro|kproto
mdefine_line|#define kproto(FMT, a...)&t;printk(&quot;### &quot;FMT&quot;&bslash;n&quot; , ##a)
DECL|macro|knet
mdefine_line|#define knet(FMT, a...)&t;&t;printk(&quot;    &quot;FMT&quot;&bslash;n&quot; , ##a)
macro_line|#if 0
mdefine_line|#define _enter(FMT, a...)&t;kenter(FMT , ##a)
mdefine_line|#define _leave(FMT, a...)&t;kleave(FMT , ##a)
mdefine_line|#define _debug(FMT, a...)&t;kdebug(FMT , ##a)
mdefine_line|#define _proto(FMT, a...)&t;kproto(FMT , ##a)
mdefine_line|#define _net(FMT, a...)&t;&t;knet(FMT , ##a)
macro_line|#else
DECL|macro|_enter
mdefine_line|#define _enter(FMT, a...)&t;do { if (rxrpc_ktrace) kenter(FMT , ##a); } while(0)
DECL|macro|_leave
mdefine_line|#define _leave(FMT, a...)&t;do { if (rxrpc_ktrace) kleave(FMT , ##a); } while(0)
DECL|macro|_debug
mdefine_line|#define _debug(FMT, a...)&t;do { if (rxrpc_kdebug) kdebug(FMT , ##a); } while(0)
DECL|macro|_proto
mdefine_line|#define _proto(FMT, a...)&t;do { if (rxrpc_kproto) kproto(FMT , ##a); } while(0)
DECL|macro|_net
mdefine_line|#define _net(FMT, a...)&t;&t;do { if (rxrpc_knet)   knet  (FMT , ##a); } while(0)
macro_line|#endif
DECL|function|rxrpc_discard_my_signals
r_static
r_inline
r_void
id|rxrpc_discard_my_signals
c_func
(paren
r_void
)paren
(brace
r_while
c_loop
(paren
id|signal_pending
c_func
(paren
id|current
)paren
)paren
(brace
id|siginfo_t
id|sinfo
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|current-&gt;sighand-&gt;siglock
)paren
suffix:semicolon
id|dequeue_signal
c_func
(paren
id|current
comma
op_amp
id|current-&gt;blocked
comma
op_amp
id|sinfo
)paren
suffix:semicolon
id|spin_unlock_irq
c_func
(paren
op_amp
id|current-&gt;sighand-&gt;siglock
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * call.c&n; */
r_extern
r_struct
id|list_head
id|rxrpc_calls
suffix:semicolon
r_extern
r_struct
id|rw_semaphore
id|rxrpc_calls_sem
suffix:semicolon
multiline_comment|/*&n; * connection.c&n; */
r_extern
r_struct
id|list_head
id|rxrpc_conns
suffix:semicolon
r_extern
r_struct
id|rw_semaphore
id|rxrpc_conns_sem
suffix:semicolon
r_extern
r_int
r_int
id|rxrpc_conn_timeout
suffix:semicolon
r_extern
r_void
id|rxrpc_conn_clearall
c_func
(paren
r_struct
id|rxrpc_peer
op_star
id|peer
)paren
suffix:semicolon
multiline_comment|/*&n; * peer.c&n; */
r_extern
r_struct
id|list_head
id|rxrpc_peers
suffix:semicolon
r_extern
r_struct
id|rw_semaphore
id|rxrpc_peers_sem
suffix:semicolon
r_extern
r_int
r_int
id|rxrpc_peer_timeout
suffix:semicolon
r_extern
r_void
id|rxrpc_peer_calculate_rtt
c_func
(paren
r_struct
id|rxrpc_peer
op_star
id|peer
comma
r_struct
id|rxrpc_message
op_star
id|msg
comma
r_struct
id|rxrpc_message
op_star
id|resp
)paren
suffix:semicolon
r_extern
r_void
id|rxrpc_peer_clearall
c_func
(paren
r_struct
id|rxrpc_transport
op_star
id|trans
)paren
suffix:semicolon
multiline_comment|/*&n; * proc.c&n; */
macro_line|#ifdef CONFIG_PROC_FS
r_extern
r_int
id|rxrpc_proc_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|rxrpc_proc_cleanup
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * transport.c&n; */
r_extern
r_struct
id|list_head
id|rxrpc_proc_transports
suffix:semicolon
r_extern
r_struct
id|rw_semaphore
id|rxrpc_proc_transports_sem
suffix:semicolon
macro_line|#endif /* RXRPC_INTERNAL_H */
eof
