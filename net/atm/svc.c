multiline_comment|/* net/atm/svc.c - ATM SVC sockets */
multiline_comment|/* Written 1995-2000 by Werner Almesberger, EPFL LRC/ICA */
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/net.h&gt;&t;&t;/* struct socket, struct proto_ops */
macro_line|#include &lt;linux/errno.h&gt;&t;/* error codes */
macro_line|#include &lt;linux/kernel.h&gt;&t;/* printk */
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#include &lt;linux/sched.h&gt;&t;/* jiffies and HZ */
macro_line|#include &lt;linux/fcntl.h&gt;&t;/* O_NONBLOCK */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/atm.h&gt;&t;&t;/* ATM stuff */
macro_line|#include &lt;linux/atmsap.h&gt;
macro_line|#include &lt;linux/atmsvc.h&gt;
macro_line|#include &lt;linux/atmdev.h&gt;
macro_line|#include &lt;linux/bitops.h&gt;
macro_line|#include &lt;net/sock.h&gt;&t;&t;/* for sock_no_* */
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &quot;resources.h&quot;
macro_line|#include &quot;common.h&quot;&t;&t;/* common for PVCs and SVCs */
macro_line|#include &quot;signaling.h&quot;
macro_line|#include &quot;addr.h&quot;
macro_line|#if 0
mdefine_line|#define DPRINTK(format,args...) printk(KERN_DEBUG format,##args)
macro_line|#else
DECL|macro|DPRINTK
mdefine_line|#define DPRINTK(format,args...)
macro_line|#endif
r_static
r_int
id|svc_create
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
suffix:semicolon
multiline_comment|/*&n; * Note: since all this is still nicely synchronized with the signaling demon,&n; *       there&squot;s no need to protect sleep loops with clis. If signaling is&n; *       moved into the kernel, that would change.&n; */
DECL|function|svc_shutdown
r_static
r_int
id|svc_shutdown
c_func
(paren
r_struct
id|socket
op_star
id|sock
comma
r_int
id|how
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|svc_disconnect
r_static
r_void
id|svc_disconnect
c_func
(paren
r_struct
id|atm_vcc
op_star
id|vcc
)paren
(brace
id|DEFINE_WAIT
c_func
(paren
id|wait
)paren
suffix:semicolon
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
id|DPRINTK
c_func
(paren
l_string|&quot;svc_disconnect %p&bslash;n&quot;
comma
id|vcc
)paren
suffix:semicolon
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|ATM_VF_REGIS
comma
op_amp
id|vcc-&gt;flags
)paren
)paren
(brace
id|prepare_to_wait
c_func
(paren
id|vcc-&gt;sk-&gt;sk_sleep
comma
op_amp
id|wait
comma
id|TASK_UNINTERRUPTIBLE
)paren
suffix:semicolon
id|sigd_enq
c_func
(paren
id|vcc
comma
id|as_close
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|test_bit
c_func
(paren
id|ATM_VF_RELEASED
comma
op_amp
id|vcc-&gt;flags
)paren
op_logical_and
id|sigd
)paren
(brace
id|schedule
c_func
(paren
)paren
suffix:semicolon
id|prepare_to_wait
c_func
(paren
id|vcc-&gt;sk-&gt;sk_sleep
comma
op_amp
id|wait
comma
id|TASK_UNINTERRUPTIBLE
)paren
suffix:semicolon
)brace
id|finish_wait
c_func
(paren
id|vcc-&gt;sk-&gt;sk_sleep
comma
op_amp
id|wait
)paren
suffix:semicolon
)brace
multiline_comment|/* beware - socket is still in use by atmsigd until the last&n;&t;   as_indicate has been answered */
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
id|vcc-&gt;sk-&gt;sk_receive_queue
)paren
)paren
)paren
(brace
id|DPRINTK
c_func
(paren
l_string|&quot;LISTEN REL&bslash;n&quot;
)paren
suffix:semicolon
id|sigd_enq2
c_func
(paren
l_int|NULL
comma
id|as_reject
comma
id|vcc
comma
l_int|NULL
comma
l_int|NULL
comma
op_amp
id|vcc-&gt;qos
comma
l_int|0
)paren
suffix:semicolon
id|dev_kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
id|clear_bit
c_func
(paren
id|ATM_VF_REGIS
comma
op_amp
id|vcc-&gt;flags
)paren
suffix:semicolon
id|clear_bit
c_func
(paren
id|ATM_VF_RELEASED
comma
op_amp
id|vcc-&gt;flags
)paren
suffix:semicolon
id|clear_bit
c_func
(paren
id|ATM_VF_CLOSE
comma
op_amp
id|vcc-&gt;flags
)paren
suffix:semicolon
multiline_comment|/* ... may retry later */
)brace
DECL|function|svc_release
r_static
r_int
id|svc_release
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
id|atm_vcc
op_star
id|vcc
suffix:semicolon
r_if
c_cond
(paren
id|sk
)paren
(brace
id|vcc
op_assign
id|ATM_SD
c_func
(paren
id|sock
)paren
suffix:semicolon
id|DPRINTK
c_func
(paren
l_string|&quot;svc_release %p&bslash;n&quot;
comma
id|vcc
)paren
suffix:semicolon
id|clear_bit
c_func
(paren
id|ATM_VF_READY
comma
op_amp
id|vcc-&gt;flags
)paren
suffix:semicolon
multiline_comment|/* VCC pointer is used as a reference, so we must not free it&n;&t;&t;   (thereby subjecting it to re-use) before all pending connections&n;&t;           are closed */
id|sock_hold
c_func
(paren
id|sk
)paren
suffix:semicolon
id|vcc_release
c_func
(paren
id|sock
)paren
suffix:semicolon
id|svc_disconnect
c_func
(paren
id|vcc
)paren
suffix:semicolon
id|sock_put
c_func
(paren
id|sk
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|svc_bind
r_static
r_int
id|svc_bind
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
id|sockaddr
comma
r_int
id|sockaddr_len
)paren
(brace
id|DEFINE_WAIT
c_func
(paren
id|wait
)paren
suffix:semicolon
r_struct
id|sock
op_star
id|sk
op_assign
id|sock-&gt;sk
suffix:semicolon
r_struct
id|sockaddr_atmsvc
op_star
id|addr
suffix:semicolon
r_struct
id|atm_vcc
op_star
id|vcc
suffix:semicolon
r_int
id|error
suffix:semicolon
r_if
c_cond
(paren
id|sockaddr_len
op_ne
r_sizeof
(paren
r_struct
id|sockaddr_atmsvc
)paren
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
id|sock-&gt;state
op_eq
id|SS_CONNECTED
)paren
(brace
id|error
op_assign
op_minus
id|EISCONN
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sock-&gt;state
op_ne
id|SS_UNCONNECTED
)paren
(brace
id|error
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|vcc
op_assign
id|ATM_SD
c_func
(paren
id|sock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|ATM_VF_SESSION
comma
op_amp
id|vcc-&gt;flags
)paren
)paren
(brace
id|error
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|addr
op_assign
(paren
r_struct
id|sockaddr_atmsvc
op_star
)paren
id|sockaddr
suffix:semicolon
r_if
c_cond
(paren
id|addr-&gt;sas_family
op_ne
id|AF_ATMSVC
)paren
(brace
id|error
op_assign
op_minus
id|EAFNOSUPPORT
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|clear_bit
c_func
(paren
id|ATM_VF_BOUND
comma
op_amp
id|vcc-&gt;flags
)paren
suffix:semicolon
multiline_comment|/* failing rebind will kill old binding */
multiline_comment|/* @@@ check memory (de)allocation on rebind */
r_if
c_cond
(paren
op_logical_neg
id|test_bit
c_func
(paren
id|ATM_VF_HASQOS
comma
op_amp
id|vcc-&gt;flags
)paren
)paren
(brace
id|error
op_assign
op_minus
id|EBADFD
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|vcc-&gt;local
op_assign
op_star
id|addr
suffix:semicolon
id|set_bit
c_func
(paren
id|ATM_VF_WAITING
comma
op_amp
id|vcc-&gt;flags
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
id|TASK_UNINTERRUPTIBLE
)paren
suffix:semicolon
id|sigd_enq
c_func
(paren
id|vcc
comma
id|as_bind
comma
l_int|NULL
comma
l_int|NULL
comma
op_amp
id|vcc-&gt;local
)paren
suffix:semicolon
r_while
c_loop
(paren
id|test_bit
c_func
(paren
id|ATM_VF_WAITING
comma
op_amp
id|vcc-&gt;flags
)paren
op_logical_and
id|sigd
)paren
(brace
id|schedule
c_func
(paren
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
id|TASK_UNINTERRUPTIBLE
)paren
suffix:semicolon
)brace
id|finish_wait
c_func
(paren
id|sk-&gt;sk_sleep
comma
op_amp
id|wait
)paren
suffix:semicolon
id|clear_bit
c_func
(paren
id|ATM_VF_REGIS
comma
op_amp
id|vcc-&gt;flags
)paren
suffix:semicolon
multiline_comment|/* doesn&squot;t count */
r_if
c_cond
(paren
op_logical_neg
id|sigd
)paren
(brace
id|error
op_assign
op_minus
id|EUNATCH
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|sk-&gt;sk_err
)paren
id|set_bit
c_func
(paren
id|ATM_VF_BOUND
comma
op_amp
id|vcc-&gt;flags
)paren
suffix:semicolon
id|error
op_assign
op_minus
id|sk-&gt;sk_err
suffix:semicolon
id|out
suffix:colon
id|release_sock
c_func
(paren
id|sk
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
DECL|function|svc_connect
r_static
r_int
id|svc_connect
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
id|sockaddr
comma
r_int
id|sockaddr_len
comma
r_int
id|flags
)paren
(brace
id|DEFINE_WAIT
c_func
(paren
id|wait
)paren
suffix:semicolon
r_struct
id|sock
op_star
id|sk
op_assign
id|sock-&gt;sk
suffix:semicolon
r_struct
id|sockaddr_atmsvc
op_star
id|addr
suffix:semicolon
r_struct
id|atm_vcc
op_star
id|vcc
op_assign
id|ATM_SD
c_func
(paren
id|sock
)paren
suffix:semicolon
r_int
id|error
suffix:semicolon
id|DPRINTK
c_func
(paren
l_string|&quot;svc_connect %p&bslash;n&quot;
comma
id|vcc
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
id|sockaddr_len
op_ne
r_sizeof
(paren
r_struct
id|sockaddr_atmsvc
)paren
)paren
(brace
id|error
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|sock-&gt;state
)paren
(brace
r_default
suffix:colon
id|error
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|out
suffix:semicolon
r_case
id|SS_CONNECTED
suffix:colon
id|error
op_assign
op_minus
id|EISCONN
suffix:semicolon
r_goto
id|out
suffix:semicolon
r_case
id|SS_CONNECTING
suffix:colon
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|ATM_VF_WAITING
comma
op_amp
id|vcc-&gt;flags
)paren
)paren
(brace
id|error
op_assign
op_minus
id|EALREADY
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|sock-&gt;state
op_assign
id|SS_UNCONNECTED
suffix:semicolon
r_if
c_cond
(paren
id|sk-&gt;sk_err
)paren
(brace
id|error
op_assign
op_minus
id|sk-&gt;sk_err
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|SS_UNCONNECTED
suffix:colon
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|ATM_VF_SESSION
comma
op_amp
id|vcc-&gt;flags
)paren
)paren
(brace
id|error
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|addr
op_assign
(paren
r_struct
id|sockaddr_atmsvc
op_star
)paren
id|sockaddr
suffix:semicolon
r_if
c_cond
(paren
id|addr-&gt;sas_family
op_ne
id|AF_ATMSVC
)paren
(brace
id|error
op_assign
op_minus
id|EAFNOSUPPORT
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|test_bit
c_func
(paren
id|ATM_VF_HASQOS
comma
op_amp
id|vcc-&gt;flags
)paren
)paren
(brace
id|error
op_assign
op_minus
id|EBADFD
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|vcc-&gt;qos.txtp.traffic_class
op_eq
id|ATM_ANYCLASS
op_logical_or
id|vcc-&gt;qos.rxtp.traffic_class
op_eq
id|ATM_ANYCLASS
)paren
(brace
id|error
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|vcc-&gt;qos.txtp.traffic_class
op_logical_and
op_logical_neg
id|vcc-&gt;qos.rxtp.traffic_class
)paren
(brace
id|error
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|vcc-&gt;remote
op_assign
op_star
id|addr
suffix:semicolon
id|set_bit
c_func
(paren
id|ATM_VF_WAITING
comma
op_amp
id|vcc-&gt;flags
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
id|sigd_enq
c_func
(paren
id|vcc
comma
id|as_connect
comma
l_int|NULL
comma
l_int|NULL
comma
op_amp
id|vcc-&gt;remote
)paren
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
id|O_NONBLOCK
)paren
(brace
id|finish_wait
c_func
(paren
id|sk-&gt;sk_sleep
comma
op_amp
id|wait
)paren
suffix:semicolon
id|sock-&gt;state
op_assign
id|SS_CONNECTING
suffix:semicolon
id|error
op_assign
op_minus
id|EINPROGRESS
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|error
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|test_bit
c_func
(paren
id|ATM_VF_WAITING
comma
op_amp
id|vcc-&gt;flags
)paren
op_logical_and
id|sigd
)paren
(brace
id|schedule
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|signal_pending
c_func
(paren
id|current
)paren
)paren
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
r_continue
suffix:semicolon
)brace
id|DPRINTK
c_func
(paren
l_string|&quot;*ABORT*&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * This is tricky:&n;&t;&t;&t; *   Kernel ---close--&gt; Demon&n;&t;&t;&t; *   Kernel &lt;--close--- Demon&n;&t;&t;         * or&n;&t;&t;&t; *   Kernel ---close--&gt; Demon&n;&t;&t;&t; *   Kernel &lt;--error--- Demon&n;&t;&t;&t; * or&n;&t;&t;&t; *   Kernel ---close--&gt; Demon&n;&t;&t;&t; *   Kernel &lt;--okay---- Demon&n;&t;&t;&t; *   Kernel &lt;--close--- Demon&n;&t;&t;&t; */
id|sigd_enq
c_func
(paren
id|vcc
comma
id|as_close
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
r_while
c_loop
(paren
id|test_bit
c_func
(paren
id|ATM_VF_WAITING
comma
op_amp
id|vcc-&gt;flags
)paren
op_logical_and
id|sigd
)paren
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
id|schedule
c_func
(paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|sk-&gt;sk_err
)paren
r_while
c_loop
(paren
op_logical_neg
id|test_bit
c_func
(paren
id|ATM_VF_RELEASED
comma
op_amp
id|vcc-&gt;flags
)paren
op_logical_and
id|sigd
)paren
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
id|schedule
c_func
(paren
)paren
suffix:semicolon
)brace
id|clear_bit
c_func
(paren
id|ATM_VF_REGIS
comma
op_amp
id|vcc-&gt;flags
)paren
suffix:semicolon
id|clear_bit
c_func
(paren
id|ATM_VF_RELEASED
comma
op_amp
id|vcc-&gt;flags
)paren
suffix:semicolon
id|clear_bit
c_func
(paren
id|ATM_VF_CLOSE
comma
op_amp
id|vcc-&gt;flags
)paren
suffix:semicolon
multiline_comment|/* we&squot;re gone now but may connect later */
id|error
op_assign
op_minus
id|EINTR
suffix:semicolon
r_break
suffix:semicolon
)brace
id|finish_wait
c_func
(paren
id|sk-&gt;sk_sleep
comma
op_amp
id|wait
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sigd
)paren
(brace
id|error
op_assign
op_minus
id|EUNATCH
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sk-&gt;sk_err
)paren
(brace
id|error
op_assign
op_minus
id|sk-&gt;sk_err
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Not supported yet&n; *&n; * #ifndef CONFIG_SINGLE_SIGITF&n; */
id|vcc-&gt;qos.txtp.max_pcr
op_assign
id|SELECT_TOP_PCR
c_func
(paren
id|vcc-&gt;qos.txtp
)paren
suffix:semicolon
id|vcc-&gt;qos.txtp.pcr
op_assign
l_int|0
suffix:semicolon
id|vcc-&gt;qos.txtp.min_pcr
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n; * #endif&n; */
r_if
c_cond
(paren
op_logical_neg
(paren
id|error
op_assign
id|vcc_connect
c_func
(paren
id|sock
comma
id|vcc-&gt;itf
comma
id|vcc-&gt;vpi
comma
id|vcc-&gt;vci
)paren
)paren
)paren
id|sock-&gt;state
op_assign
id|SS_CONNECTED
suffix:semicolon
r_else
(paren
r_void
)paren
id|svc_disconnect
c_func
(paren
id|vcc
)paren
suffix:semicolon
id|out
suffix:colon
id|release_sock
c_func
(paren
id|sk
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
DECL|function|svc_listen
r_static
r_int
id|svc_listen
c_func
(paren
r_struct
id|socket
op_star
id|sock
comma
r_int
id|backlog
)paren
(brace
id|DEFINE_WAIT
c_func
(paren
id|wait
)paren
suffix:semicolon
r_struct
id|sock
op_star
id|sk
op_assign
id|sock-&gt;sk
suffix:semicolon
r_struct
id|atm_vcc
op_star
id|vcc
op_assign
id|ATM_SD
c_func
(paren
id|sock
)paren
suffix:semicolon
r_int
id|error
suffix:semicolon
id|DPRINTK
c_func
(paren
l_string|&quot;svc_listen %p&bslash;n&quot;
comma
id|vcc
)paren
suffix:semicolon
id|lock_sock
c_func
(paren
id|sk
)paren
suffix:semicolon
multiline_comment|/* let server handle listen on unbound sockets */
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|ATM_VF_SESSION
comma
op_amp
id|vcc-&gt;flags
)paren
)paren
(brace
id|error
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|set_bit
c_func
(paren
id|ATM_VF_WAITING
comma
op_amp
id|vcc-&gt;flags
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
id|TASK_UNINTERRUPTIBLE
)paren
suffix:semicolon
id|sigd_enq
c_func
(paren
id|vcc
comma
id|as_listen
comma
l_int|NULL
comma
l_int|NULL
comma
op_amp
id|vcc-&gt;local
)paren
suffix:semicolon
r_while
c_loop
(paren
id|test_bit
c_func
(paren
id|ATM_VF_WAITING
comma
op_amp
id|vcc-&gt;flags
)paren
op_logical_and
id|sigd
)paren
(brace
id|schedule
c_func
(paren
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
id|TASK_UNINTERRUPTIBLE
)paren
suffix:semicolon
)brace
id|finish_wait
c_func
(paren
id|sk-&gt;sk_sleep
comma
op_amp
id|wait
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sigd
)paren
(brace
id|error
op_assign
op_minus
id|EUNATCH
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|set_bit
c_func
(paren
id|ATM_VF_LISTEN
comma
op_amp
id|vcc-&gt;flags
)paren
suffix:semicolon
id|vcc-&gt;sk-&gt;sk_max_ack_backlog
op_assign
id|backlog
OG
l_int|0
ques
c_cond
id|backlog
suffix:colon
id|ATM_BACKLOG_DEFAULT
suffix:semicolon
id|error
op_assign
op_minus
id|sk-&gt;sk_err
suffix:semicolon
id|out
suffix:colon
id|release_sock
c_func
(paren
id|sk
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
DECL|function|svc_accept
r_static
r_int
id|svc_accept
c_func
(paren
r_struct
id|socket
op_star
id|sock
comma
r_struct
id|socket
op_star
id|newsock
comma
r_int
id|flags
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
id|sk_buff
op_star
id|skb
suffix:semicolon
r_struct
id|atmsvc_msg
op_star
id|msg
suffix:semicolon
r_struct
id|atm_vcc
op_star
id|old_vcc
op_assign
id|ATM_SD
c_func
(paren
id|sock
)paren
suffix:semicolon
r_struct
id|atm_vcc
op_star
id|new_vcc
suffix:semicolon
r_int
id|error
suffix:semicolon
id|lock_sock
c_func
(paren
id|sk
)paren
suffix:semicolon
id|error
op_assign
id|svc_create
c_func
(paren
id|newsock
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_goto
id|out
suffix:semicolon
id|new_vcc
op_assign
id|ATM_SD
c_func
(paren
id|newsock
)paren
suffix:semicolon
id|DPRINTK
c_func
(paren
l_string|&quot;svc_accept %p -&gt; %p&bslash;n&quot;
comma
id|old_vcc
comma
id|new_vcc
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
id|DEFINE_WAIT
c_func
(paren
id|wait
)paren
suffix:semicolon
id|prepare_to_wait
c_func
(paren
id|old_vcc-&gt;sk-&gt;sk_sleep
comma
op_amp
id|wait
comma
id|TASK_INTERRUPTIBLE
)paren
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
(paren
id|skb
op_assign
id|skb_dequeue
c_func
(paren
op_amp
id|old_vcc-&gt;sk-&gt;sk_receive_queue
)paren
)paren
op_logical_and
id|sigd
)paren
(brace
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|ATM_VF_RELEASED
comma
op_amp
id|old_vcc-&gt;flags
)paren
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|ATM_VF_CLOSE
comma
op_amp
id|old_vcc-&gt;flags
)paren
)paren
(brace
id|error
op_assign
op_minus
id|sk-&gt;sk_err
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|flags
op_amp
id|O_NONBLOCK
)paren
(brace
id|error
op_assign
op_minus
id|EAGAIN
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
id|schedule
c_func
(paren
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
id|signal_pending
c_func
(paren
id|current
)paren
)paren
(brace
id|error
op_assign
op_minus
id|ERESTARTSYS
suffix:semicolon
r_break
suffix:semicolon
)brace
id|prepare_to_wait
c_func
(paren
id|old_vcc-&gt;sk-&gt;sk_sleep
comma
op_amp
id|wait
comma
id|TASK_INTERRUPTIBLE
)paren
suffix:semicolon
)brace
id|finish_wait
c_func
(paren
id|old_vcc-&gt;sk-&gt;sk_sleep
comma
op_amp
id|wait
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|skb
)paren
(brace
id|error
op_assign
op_minus
id|EUNATCH
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|msg
op_assign
(paren
r_struct
id|atmsvc_msg
op_star
)paren
id|skb-&gt;data
suffix:semicolon
id|new_vcc-&gt;qos
op_assign
id|msg-&gt;qos
suffix:semicolon
id|set_bit
c_func
(paren
id|ATM_VF_HASQOS
comma
op_amp
id|new_vcc-&gt;flags
)paren
suffix:semicolon
id|new_vcc-&gt;remote
op_assign
id|msg-&gt;svc
suffix:semicolon
id|new_vcc-&gt;local
op_assign
id|msg-&gt;local
suffix:semicolon
id|new_vcc-&gt;sap
op_assign
id|msg-&gt;sap
suffix:semicolon
id|error
op_assign
id|vcc_connect
c_func
(paren
id|newsock
comma
id|msg-&gt;pvc.sap_addr.itf
comma
id|msg-&gt;pvc.sap_addr.vpi
comma
id|msg-&gt;pvc.sap_addr.vci
)paren
suffix:semicolon
id|dev_kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
id|old_vcc-&gt;sk-&gt;sk_ack_backlog
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
(brace
id|sigd_enq2
c_func
(paren
l_int|NULL
comma
id|as_reject
comma
id|old_vcc
comma
l_int|NULL
comma
l_int|NULL
comma
op_amp
id|old_vcc-&gt;qos
comma
id|error
)paren
suffix:semicolon
id|error
op_assign
id|error
op_eq
op_minus
id|EAGAIN
ques
c_cond
op_minus
id|EBUSY
suffix:colon
id|error
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/* wait should be short, so we ignore the non-blocking flag */
id|set_bit
c_func
(paren
id|ATM_VF_WAITING
comma
op_amp
id|new_vcc-&gt;flags
)paren
suffix:semicolon
id|prepare_to_wait
c_func
(paren
id|new_vcc-&gt;sk-&gt;sk_sleep
comma
op_amp
id|wait
comma
id|TASK_UNINTERRUPTIBLE
)paren
suffix:semicolon
id|sigd_enq
c_func
(paren
id|new_vcc
comma
id|as_accept
comma
id|old_vcc
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
r_while
c_loop
(paren
id|test_bit
c_func
(paren
id|ATM_VF_WAITING
comma
op_amp
id|new_vcc-&gt;flags
)paren
op_logical_and
id|sigd
)paren
(brace
id|release_sock
c_func
(paren
id|sk
)paren
suffix:semicolon
id|schedule
c_func
(paren
)paren
suffix:semicolon
id|lock_sock
c_func
(paren
id|sk
)paren
suffix:semicolon
id|prepare_to_wait
c_func
(paren
id|new_vcc-&gt;sk-&gt;sk_sleep
comma
op_amp
id|wait
comma
id|TASK_UNINTERRUPTIBLE
)paren
suffix:semicolon
)brace
id|finish_wait
c_func
(paren
id|new_vcc-&gt;sk-&gt;sk_sleep
comma
op_amp
id|wait
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sigd
)paren
(brace
id|error
op_assign
op_minus
id|EUNATCH
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|new_vcc-&gt;sk-&gt;sk_err
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|new_vcc-&gt;sk-&gt;sk_err
op_ne
id|ERESTARTSYS
)paren
(brace
id|error
op_assign
op_minus
id|new_vcc-&gt;sk-&gt;sk_err
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
)brace
id|newsock-&gt;state
op_assign
id|SS_CONNECTED
suffix:semicolon
id|out
suffix:colon
id|release_sock
c_func
(paren
id|sk
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
DECL|function|svc_getname
r_static
r_int
id|svc_getname
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
id|sockaddr
comma
r_int
op_star
id|sockaddr_len
comma
r_int
id|peer
)paren
(brace
r_struct
id|sockaddr_atmsvc
op_star
id|addr
suffix:semicolon
op_star
id|sockaddr_len
op_assign
r_sizeof
(paren
r_struct
id|sockaddr_atmsvc
)paren
suffix:semicolon
id|addr
op_assign
(paren
r_struct
id|sockaddr_atmsvc
op_star
)paren
id|sockaddr
suffix:semicolon
id|memcpy
c_func
(paren
id|addr
comma
id|peer
ques
c_cond
op_amp
id|ATM_SD
c_func
(paren
id|sock
)paren
op_member_access_from_pointer
id|remote
suffix:colon
op_amp
id|ATM_SD
c_func
(paren
id|sock
)paren
op_member_access_from_pointer
id|local
comma
r_sizeof
(paren
r_struct
id|sockaddr_atmsvc
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|svc_change_qos
r_int
id|svc_change_qos
c_func
(paren
r_struct
id|atm_vcc
op_star
id|vcc
comma
r_struct
id|atm_qos
op_star
id|qos
)paren
(brace
id|DEFINE_WAIT
c_func
(paren
id|wait
)paren
suffix:semicolon
id|set_bit
c_func
(paren
id|ATM_VF_WAITING
comma
op_amp
id|vcc-&gt;flags
)paren
suffix:semicolon
id|prepare_to_wait
c_func
(paren
id|vcc-&gt;sk-&gt;sk_sleep
comma
op_amp
id|wait
comma
id|TASK_UNINTERRUPTIBLE
)paren
suffix:semicolon
id|sigd_enq2
c_func
(paren
id|vcc
comma
id|as_modify
comma
l_int|NULL
comma
l_int|NULL
comma
op_amp
id|vcc-&gt;local
comma
id|qos
comma
l_int|0
)paren
suffix:semicolon
r_while
c_loop
(paren
id|test_bit
c_func
(paren
id|ATM_VF_WAITING
comma
op_amp
id|vcc-&gt;flags
)paren
op_logical_and
op_logical_neg
id|test_bit
c_func
(paren
id|ATM_VF_RELEASED
comma
op_amp
id|vcc-&gt;flags
)paren
op_logical_and
id|sigd
)paren
(brace
id|schedule
c_func
(paren
)paren
suffix:semicolon
id|prepare_to_wait
c_func
(paren
id|vcc-&gt;sk-&gt;sk_sleep
comma
op_amp
id|wait
comma
id|TASK_UNINTERRUPTIBLE
)paren
suffix:semicolon
)brace
id|finish_wait
c_func
(paren
id|vcc-&gt;sk-&gt;sk_sleep
comma
op_amp
id|wait
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sigd
)paren
r_return
op_minus
id|EUNATCH
suffix:semicolon
r_return
op_minus
id|vcc-&gt;sk-&gt;sk_err
suffix:semicolon
)brace
DECL|function|svc_setsockopt
r_static
r_int
id|svc_setsockopt
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
id|optlen
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
id|atm_vcc
op_star
id|vcc
suffix:semicolon
r_int
id|error
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|__SO_LEVEL_MATCH
c_func
(paren
id|optname
comma
id|level
)paren
op_logical_or
id|optname
op_ne
id|SO_ATMSAP
op_logical_or
id|optlen
op_ne
r_sizeof
(paren
r_struct
id|atm_sap
)paren
)paren
(brace
id|error
op_assign
id|vcc_setsockopt
c_func
(paren
id|sock
comma
id|level
comma
id|optname
comma
id|optval
comma
id|optlen
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|vcc
op_assign
id|ATM_SD
c_func
(paren
id|sock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|vcc-&gt;sap
comma
id|optval
comma
id|optlen
)paren
)paren
(brace
id|error
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|set_bit
c_func
(paren
id|ATM_VF_HASSAP
comma
op_amp
id|vcc-&gt;flags
)paren
suffix:semicolon
id|out
suffix:colon
id|release_sock
c_func
(paren
id|sk
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
DECL|function|svc_getsockopt
r_static
r_int
id|svc_getsockopt
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
id|sock
op_star
id|sk
op_assign
id|sock-&gt;sk
suffix:semicolon
r_int
id|error
op_assign
l_int|0
comma
id|len
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
id|__SO_LEVEL_MATCH
c_func
(paren
id|optname
comma
id|level
)paren
op_logical_or
id|optname
op_ne
id|SO_ATMSAP
)paren
(brace
id|error
op_assign
id|vcc_getsockopt
c_func
(paren
id|sock
comma
id|level
comma
id|optname
comma
id|optval
comma
id|optlen
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
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
(brace
id|error
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|len
op_ne
r_sizeof
(paren
r_struct
id|atm_sap
)paren
)paren
(brace
id|error
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|optval
comma
op_amp
id|ATM_SD
c_func
(paren
id|sock
)paren
op_member_access_from_pointer
id|sap
comma
r_sizeof
(paren
r_struct
id|atm_sap
)paren
)paren
)paren
(brace
id|error
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|out
suffix:colon
id|release_sock
c_func
(paren
id|sk
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
DECL|variable|svc_proto_ops
r_static
r_struct
id|proto_ops
id|svc_proto_ops
op_assign
(brace
dot
id|family
op_assign
id|PF_ATMSVC
comma
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|release
op_assign
id|svc_release
comma
dot
id|bind
op_assign
id|svc_bind
comma
dot
id|connect
op_assign
id|svc_connect
comma
dot
id|socketpair
op_assign
id|sock_no_socketpair
comma
dot
id|accept
op_assign
id|svc_accept
comma
dot
id|getname
op_assign
id|svc_getname
comma
dot
id|poll
op_assign
id|vcc_poll
comma
dot
id|ioctl
op_assign
id|vcc_ioctl
comma
dot
id|listen
op_assign
id|svc_listen
comma
dot
id|shutdown
op_assign
id|svc_shutdown
comma
dot
id|setsockopt
op_assign
id|svc_setsockopt
comma
dot
id|getsockopt
op_assign
id|svc_getsockopt
comma
dot
id|sendmsg
op_assign
id|vcc_sendmsg
comma
dot
id|recvmsg
op_assign
id|vcc_recvmsg
comma
dot
id|mmap
op_assign
id|sock_no_mmap
comma
dot
id|sendpage
op_assign
id|sock_no_sendpage
comma
)brace
suffix:semicolon
DECL|function|svc_create
r_static
r_int
id|svc_create
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
r_int
id|error
suffix:semicolon
id|sock-&gt;ops
op_assign
op_amp
id|svc_proto_ops
suffix:semicolon
id|error
op_assign
id|vcc_create
c_func
(paren
id|sock
comma
id|protocol
comma
id|AF_ATMSVC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_return
id|error
suffix:semicolon
id|ATM_SD
c_func
(paren
id|sock
)paren
op_member_access_from_pointer
id|local.sas_family
op_assign
id|AF_ATMSVC
suffix:semicolon
id|ATM_SD
c_func
(paren
id|sock
)paren
op_member_access_from_pointer
id|remote.sas_family
op_assign
id|AF_ATMSVC
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|svc_family_ops
r_static
r_struct
id|net_proto_family
id|svc_family_ops
op_assign
(brace
dot
id|family
op_assign
id|PF_ATMSVC
comma
dot
id|create
op_assign
id|svc_create
comma
dot
id|owner
op_assign
id|THIS_MODULE
comma
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;Initialize the ATM SVC protocol family&n; */
DECL|function|atmsvc_init
r_int
id|__init
id|atmsvc_init
c_func
(paren
r_void
)paren
(brace
r_return
id|sock_register
c_func
(paren
op_amp
id|svc_family_ops
)paren
suffix:semicolon
)brace
DECL|function|atmsvc_exit
r_void
id|atmsvc_exit
c_func
(paren
r_void
)paren
(brace
id|sock_unregister
c_func
(paren
id|PF_ATMSVC
)paren
suffix:semicolon
)brace
eof
