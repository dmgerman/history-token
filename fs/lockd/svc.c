multiline_comment|/*&n; * linux/fs/lockd/svc.c&n; *&n; * This is the central lockd service.&n; *&n; * FIXME: Separate the lockd NFS server functionality from the lockd NFS&n; * &t;  client functionality. Oh why didn&squot;t Sun create two separate&n; *&t;  services in the first place?&n; *&n; * Authors:&t;Olaf Kirch (okir@monad.swb.de)&n; *&n; * Copyright (C) 1995, 1996 Olaf Kirch &lt;okir@monad.swb.de&gt;&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/sysctl.h&gt;
macro_line|#include &lt;linux/moduleparam.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/uio.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/sunrpc/types.h&gt;
macro_line|#include &lt;linux/sunrpc/stats.h&gt;
macro_line|#include &lt;linux/sunrpc/clnt.h&gt;
macro_line|#include &lt;linux/sunrpc/svc.h&gt;
macro_line|#include &lt;linux/sunrpc/svcsock.h&gt;
macro_line|#include &lt;linux/lockd/lockd.h&gt;
macro_line|#include &lt;linux/nfs.h&gt;
DECL|macro|NLMDBG_FACILITY
mdefine_line|#define NLMDBG_FACILITY&t;&t;NLMDBG_SVC
DECL|macro|LOCKD_BUFSIZE
mdefine_line|#define LOCKD_BUFSIZE&t;&t;(1024 + NLMSVC_XDRSIZE)
DECL|macro|ALLOWED_SIGS
mdefine_line|#define ALLOWED_SIGS&t;&t;(sigmask(SIGKILL))
DECL|variable|nlmsvc_program
r_static
r_struct
id|svc_program
id|nlmsvc_program
suffix:semicolon
DECL|variable|nlmsvc_ops
r_struct
id|nlmsvc_binding
op_star
id|nlmsvc_ops
suffix:semicolon
DECL|variable|nlmsvc_ops
id|EXPORT_SYMBOL
c_func
(paren
id|nlmsvc_ops
)paren
suffix:semicolon
r_static
id|DECLARE_MUTEX
c_func
(paren
id|nlmsvc_sema
)paren
suffix:semicolon
DECL|variable|nlmsvc_users
r_static
r_int
r_int
id|nlmsvc_users
suffix:semicolon
DECL|variable|nlmsvc_pid
r_static
id|pid_t
id|nlmsvc_pid
suffix:semicolon
DECL|variable|nlmsvc_grace_period
r_int
id|nlmsvc_grace_period
suffix:semicolon
DECL|variable|nlmsvc_timeout
r_int
r_int
id|nlmsvc_timeout
suffix:semicolon
r_static
id|DECLARE_MUTEX_LOCKED
c_func
(paren
id|lockd_start
)paren
suffix:semicolon
r_static
id|DECLARE_WAIT_QUEUE_HEAD
c_func
(paren
id|lockd_exit
)paren
suffix:semicolon
multiline_comment|/*&n; * These can be set at insmod time (useful for NFS as root filesystem),&n; * and also changed through the sysctl interface.  -- Jamie Lokier, Aug 2003&n; */
DECL|variable|nlm_grace_period
r_static
r_int
r_int
id|nlm_grace_period
suffix:semicolon
DECL|variable|nlm_timeout
r_static
r_int
r_int
id|nlm_timeout
op_assign
id|LOCKD_DFLT_TIMEO
suffix:semicolon
DECL|variable|nlm_udpport
DECL|variable|nlm_tcpport
r_static
r_int
id|nlm_udpport
comma
id|nlm_tcpport
suffix:semicolon
multiline_comment|/*&n; * Constants needed for the sysctl interface.&n; */
DECL|variable|nlm_grace_period_min
r_static
r_const
r_int
r_int
id|nlm_grace_period_min
op_assign
l_int|0
suffix:semicolon
DECL|variable|nlm_grace_period_max
r_static
r_const
r_int
r_int
id|nlm_grace_period_max
op_assign
l_int|240
suffix:semicolon
DECL|variable|nlm_timeout_min
r_static
r_const
r_int
r_int
id|nlm_timeout_min
op_assign
l_int|3
suffix:semicolon
DECL|variable|nlm_timeout_max
r_static
r_const
r_int
r_int
id|nlm_timeout_max
op_assign
l_int|20
suffix:semicolon
DECL|variable|nlm_port_min
DECL|variable|nlm_port_max
r_static
r_const
r_int
id|nlm_port_min
op_assign
l_int|0
comma
id|nlm_port_max
op_assign
l_int|65535
suffix:semicolon
DECL|variable|nlm_sysctl_table
r_static
r_struct
id|ctl_table_header
op_star
id|nlm_sysctl_table
suffix:semicolon
DECL|function|set_grace_period
r_static
r_int
r_int
id|set_grace_period
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|grace_period
suffix:semicolon
multiline_comment|/* Note: nlm_timeout should always be nonzero */
r_if
c_cond
(paren
id|nlm_grace_period
)paren
id|grace_period
op_assign
(paren
(paren
id|nlm_grace_period
op_plus
id|nlm_timeout
op_minus
l_int|1
)paren
op_div
id|nlm_timeout
)paren
op_star
id|nlm_timeout
op_star
id|HZ
suffix:semicolon
r_else
id|grace_period
op_assign
id|nlm_timeout
op_star
l_int|5
op_star
id|HZ
suffix:semicolon
id|nlmsvc_grace_period
op_assign
l_int|1
suffix:semicolon
r_return
id|grace_period
op_plus
id|jiffies
suffix:semicolon
)brace
DECL|function|clear_grace_period
r_static
r_inline
r_void
id|clear_grace_period
c_func
(paren
r_void
)paren
(brace
id|nlmsvc_grace_period
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * This is the lockd kernel thread&n; */
r_static
r_void
DECL|function|lockd
id|lockd
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
)paren
(brace
r_struct
id|svc_serv
op_star
id|serv
op_assign
id|rqstp-&gt;rq_server
suffix:semicolon
r_int
id|err
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|grace_period_expire
suffix:semicolon
multiline_comment|/* Lock module and set up kernel thread */
multiline_comment|/* lockd_up is waiting for us to startup, so will&n;&t; * be holding a reference to this module, so it&n;&t; * is safe to just claim another reference&n;&t; */
id|__module_get
c_func
(paren
id|THIS_MODULE
)paren
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Let our maker know we&squot;re running.&n;&t; */
id|nlmsvc_pid
op_assign
id|current-&gt;pid
suffix:semicolon
id|up
c_func
(paren
op_amp
id|lockd_start
)paren
suffix:semicolon
id|daemonize
c_func
(paren
l_string|&quot;lockd&quot;
)paren
suffix:semicolon
multiline_comment|/* Process request with signals blocked, but allow SIGKILL.  */
id|allow_signal
c_func
(paren
id|SIGKILL
)paren
suffix:semicolon
multiline_comment|/* kick rpciod */
id|rpciod_up
c_func
(paren
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;NFS locking service started (ver &quot;
id|LOCKD_VERSION
l_string|&quot;).&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|nlm_timeout
)paren
id|nlm_timeout
op_assign
id|LOCKD_DFLT_TIMEO
suffix:semicolon
id|nlmsvc_timeout
op_assign
id|nlm_timeout
op_star
id|HZ
suffix:semicolon
id|grace_period_expire
op_assign
id|set_grace_period
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * The main request loop. We don&squot;t terminate until the last&n;&t; * NFS mount or NFS daemon has gone away, and we&squot;ve been sent a&n;&t; * signal, or else another process has taken over our job.&n;&t; */
r_while
c_loop
(paren
(paren
id|nlmsvc_users
op_logical_or
op_logical_neg
id|signalled
c_func
(paren
)paren
)paren
op_logical_and
id|nlmsvc_pid
op_eq
id|current-&gt;pid
)paren
(brace
r_int
id|timeout
op_assign
id|MAX_SCHEDULE_TIMEOUT
suffix:semicolon
r_if
c_cond
(paren
id|signalled
c_func
(paren
)paren
)paren
(brace
id|flush_signals
c_func
(paren
id|current
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nlmsvc_ops
)paren
(brace
id|nlmsvc_invalidate_all
c_func
(paren
)paren
suffix:semicolon
id|grace_period_expire
op_assign
id|set_grace_period
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t;&t; * Retry any blocked locks that have been notified by&n;&t;&t; * the VFS. Don&squot;t do this during grace period.&n;&t;&t; * (Theoretically, there shouldn&squot;t even be blocked locks&n;&t;&t; * during grace period).&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|nlmsvc_grace_period
)paren
(brace
id|timeout
op_assign
id|nlmsvc_retry_blocked
c_func
(paren
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|time_before
c_func
(paren
id|grace_period_expire
comma
id|jiffies
)paren
)paren
id|clear_grace_period
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Find a socket with data available and call its&n;&t;&t; * recvfrom routine.&n;&t;&t; */
id|err
op_assign
id|svc_recv
c_func
(paren
id|serv
comma
id|rqstp
comma
id|timeout
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
op_eq
op_minus
id|EAGAIN
op_logical_or
id|err
op_eq
op_minus
id|EINTR
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;lockd: terminating on error %d&bslash;n&quot;
comma
op_minus
id|err
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|dprintk
c_func
(paren
l_string|&quot;lockd: request from %08x&bslash;n&quot;
comma
(paren
r_int
)paren
id|ntohl
c_func
(paren
id|rqstp-&gt;rq_addr.sin_addr.s_addr
)paren
)paren
suffix:semicolon
id|svc_process
c_func
(paren
id|serv
comma
id|rqstp
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Check whether there&squot;s a new lockd process before&n;&t; * shutting down the hosts and clearing the slot.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|nlmsvc_pid
op_logical_or
id|current-&gt;pid
op_eq
id|nlmsvc_pid
)paren
(brace
r_if
c_cond
(paren
id|nlmsvc_ops
)paren
id|nlmsvc_invalidate_all
c_func
(paren
)paren
suffix:semicolon
id|nlm_shutdown_hosts
c_func
(paren
)paren
suffix:semicolon
id|nlmsvc_pid
op_assign
l_int|0
suffix:semicolon
)brace
r_else
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;lockd: new process, skipping host shutdown&bslash;n&quot;
)paren
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|lockd_exit
)paren
suffix:semicolon
multiline_comment|/* Exit the RPC thread */
id|svc_exit_thread
c_func
(paren
id|rqstp
)paren
suffix:semicolon
multiline_comment|/* release rpciod */
id|rpciod_down
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Release module */
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
id|module_put_and_exit
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Bring up the lockd process if it&squot;s not already up.&n; */
r_int
DECL|function|lockd_up
id|lockd_up
c_func
(paren
r_void
)paren
(brace
r_static
r_int
id|warned
suffix:semicolon
r_struct
id|svc_serv
op_star
id|serv
suffix:semicolon
r_int
id|error
op_assign
l_int|0
suffix:semicolon
id|down
c_func
(paren
op_amp
id|nlmsvc_sema
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Unconditionally increment the user count ... this is&n;&t; * the number of clients who _want_ a lockd process.&n;&t; */
id|nlmsvc_users
op_increment
suffix:semicolon
multiline_comment|/*&n;&t; * Check whether we&squot;re already up and running.&n;&t; */
r_if
c_cond
(paren
id|nlmsvc_pid
)paren
r_goto
id|out
suffix:semicolon
multiline_comment|/*&n;&t; * Sanity check: if there&squot;s no pid,&n;&t; * we should be the first user ...&n;&t; */
r_if
c_cond
(paren
id|nlmsvc_users
OG
l_int|1
)paren
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;lockd_up: no pid, %d users??&bslash;n&quot;
comma
id|nlmsvc_users
)paren
suffix:semicolon
id|error
op_assign
op_minus
id|ENOMEM
suffix:semicolon
id|serv
op_assign
id|svc_create
c_func
(paren
op_amp
id|nlmsvc_program
comma
id|LOCKD_BUFSIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|serv
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;lockd_up: create service failed&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|error
op_assign
id|svc_makesock
c_func
(paren
id|serv
comma
id|IPPROTO_UDP
comma
id|nlm_udpport
)paren
)paren
OL
l_int|0
macro_line|#ifdef CONFIG_NFSD_TCP
op_logical_or
(paren
id|error
op_assign
id|svc_makesock
c_func
(paren
id|serv
comma
id|IPPROTO_TCP
comma
id|nlm_tcpport
)paren
)paren
OL
l_int|0
macro_line|#endif
)paren
(brace
r_if
c_cond
(paren
id|warned
op_increment
op_eq
l_int|0
)paren
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;lockd_up: makesock failed, error=%d&bslash;n&quot;
comma
id|error
)paren
suffix:semicolon
r_goto
id|destroy_and_out
suffix:semicolon
)brace
id|warned
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * Create the kernel thread and wait for it to start.&n;&t; */
id|error
op_assign
id|svc_create_thread
c_func
(paren
id|lockd
comma
id|serv
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;lockd_up: create thread failed, error=%d&bslash;n&quot;
comma
id|error
)paren
suffix:semicolon
r_goto
id|destroy_and_out
suffix:semicolon
)brace
id|down
c_func
(paren
op_amp
id|lockd_start
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Note: svc_serv structures have an initial use count of 1,&n;&t; * so we exit through here on both success and failure.&n;&t; */
id|destroy_and_out
suffix:colon
id|svc_destroy
c_func
(paren
id|serv
)paren
suffix:semicolon
id|out
suffix:colon
id|up
c_func
(paren
op_amp
id|nlmsvc_sema
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
DECL|variable|lockd_up
id|EXPORT_SYMBOL
c_func
(paren
id|lockd_up
)paren
suffix:semicolon
multiline_comment|/*&n; * Decrement the user count and bring down lockd if we&squot;re the last.&n; */
r_void
DECL|function|lockd_down
id|lockd_down
c_func
(paren
r_void
)paren
(brace
r_static
r_int
id|warned
suffix:semicolon
id|down
c_func
(paren
op_amp
id|nlmsvc_sema
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nlmsvc_users
)paren
(brace
r_if
c_cond
(paren
op_decrement
id|nlmsvc_users
)paren
r_goto
id|out
suffix:semicolon
)brace
r_else
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;lockd_down: no users! pid=%d&bslash;n&quot;
comma
id|nlmsvc_pid
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|nlmsvc_pid
)paren
(brace
r_if
c_cond
(paren
id|warned
op_increment
op_eq
l_int|0
)paren
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;lockd_down: no lockd running.&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|warned
op_assign
l_int|0
suffix:semicolon
id|kill_proc
c_func
(paren
id|nlmsvc_pid
comma
id|SIGKILL
comma
l_int|1
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Wait for the lockd process to exit, but since we&squot;re holding&n;&t; * the lockd semaphore, we can&squot;t wait around forever ...&n;&t; */
id|clear_thread_flag
c_func
(paren
id|TIF_SIGPENDING
)paren
suffix:semicolon
id|interruptible_sleep_on_timeout
c_func
(paren
op_amp
id|lockd_exit
comma
id|HZ
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nlmsvc_pid
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;lockd_down: lockd failed to exit, clearing pid&bslash;n&quot;
)paren
suffix:semicolon
id|nlmsvc_pid
op_assign
l_int|0
suffix:semicolon
)brace
id|spin_lock_irq
c_func
(paren
op_amp
id|current-&gt;sighand-&gt;siglock
)paren
suffix:semicolon
id|recalc_sigpending
c_func
(paren
)paren
suffix:semicolon
id|spin_unlock_irq
c_func
(paren
op_amp
id|current-&gt;sighand-&gt;siglock
)paren
suffix:semicolon
id|out
suffix:colon
id|up
c_func
(paren
op_amp
id|nlmsvc_sema
)paren
suffix:semicolon
)brace
DECL|variable|lockd_down
id|EXPORT_SYMBOL
c_func
(paren
id|lockd_down
)paren
suffix:semicolon
multiline_comment|/*&n; * Sysctl parameters (same as module parameters, different interface).&n; */
multiline_comment|/* Something that isn&squot;t CTL_ANY, CTL_NONE or a value that may clash. */
DECL|macro|CTL_UNNUMBERED
mdefine_line|#define CTL_UNNUMBERED&t;&t;-2
DECL|variable|nlm_sysctls
r_static
id|ctl_table
id|nlm_sysctls
(braket
)braket
op_assign
(brace
(brace
dot
id|ctl_name
op_assign
id|CTL_UNNUMBERED
comma
dot
id|procname
op_assign
l_string|&quot;nlm_grace_period&quot;
comma
dot
id|data
op_assign
op_amp
id|nlm_grace_period
comma
dot
id|maxlen
op_assign
r_sizeof
(paren
r_int
)paren
comma
dot
id|mode
op_assign
l_int|0644
comma
dot
id|proc_handler
op_assign
op_amp
id|proc_doulongvec_minmax
comma
dot
id|extra1
op_assign
(paren
r_int
r_int
op_star
)paren
op_amp
id|nlm_grace_period_min
comma
dot
id|extra2
op_assign
(paren
r_int
r_int
op_star
)paren
op_amp
id|nlm_grace_period_max
comma
)brace
comma
(brace
dot
id|ctl_name
op_assign
id|CTL_UNNUMBERED
comma
dot
id|procname
op_assign
l_string|&quot;nlm_timeout&quot;
comma
dot
id|data
op_assign
op_amp
id|nlm_timeout
comma
dot
id|maxlen
op_assign
r_sizeof
(paren
r_int
)paren
comma
dot
id|mode
op_assign
l_int|0644
comma
dot
id|proc_handler
op_assign
op_amp
id|proc_doulongvec_minmax
comma
dot
id|extra1
op_assign
(paren
r_int
r_int
op_star
)paren
op_amp
id|nlm_timeout_min
comma
dot
id|extra2
op_assign
(paren
r_int
r_int
op_star
)paren
op_amp
id|nlm_timeout_max
comma
)brace
comma
(brace
dot
id|ctl_name
op_assign
id|CTL_UNNUMBERED
comma
dot
id|procname
op_assign
l_string|&quot;nlm_udpport&quot;
comma
dot
id|data
op_assign
op_amp
id|nlm_udpport
comma
dot
id|maxlen
op_assign
r_sizeof
(paren
r_int
)paren
comma
dot
id|mode
op_assign
l_int|0644
comma
dot
id|proc_handler
op_assign
op_amp
id|proc_dointvec_minmax
comma
dot
id|extra1
op_assign
(paren
r_int
op_star
)paren
op_amp
id|nlm_port_min
comma
dot
id|extra2
op_assign
(paren
r_int
op_star
)paren
op_amp
id|nlm_port_max
comma
)brace
comma
(brace
dot
id|ctl_name
op_assign
id|CTL_UNNUMBERED
comma
dot
id|procname
op_assign
l_string|&quot;nlm_tcpport&quot;
comma
dot
id|data
op_assign
op_amp
id|nlm_tcpport
comma
dot
id|maxlen
op_assign
r_sizeof
(paren
r_int
)paren
comma
dot
id|mode
op_assign
l_int|0644
comma
dot
id|proc_handler
op_assign
op_amp
id|proc_dointvec_minmax
comma
dot
id|extra1
op_assign
(paren
r_int
op_star
)paren
op_amp
id|nlm_port_min
comma
dot
id|extra2
op_assign
(paren
r_int
op_star
)paren
op_amp
id|nlm_port_max
comma
)brace
comma
(brace
dot
id|ctl_name
op_assign
l_int|0
)brace
)brace
suffix:semicolon
DECL|variable|nlm_sysctl_dir
r_static
id|ctl_table
id|nlm_sysctl_dir
(braket
)braket
op_assign
(brace
(brace
dot
id|ctl_name
op_assign
id|CTL_UNNUMBERED
comma
dot
id|procname
op_assign
l_string|&quot;nfs&quot;
comma
dot
id|mode
op_assign
l_int|0555
comma
dot
id|child
op_assign
id|nlm_sysctls
comma
)brace
comma
(brace
dot
id|ctl_name
op_assign
l_int|0
)brace
)brace
suffix:semicolon
DECL|variable|nlm_sysctl_root
r_static
id|ctl_table
id|nlm_sysctl_root
(braket
)braket
op_assign
(brace
(brace
dot
id|ctl_name
op_assign
id|CTL_FS
comma
dot
id|procname
op_assign
l_string|&quot;fs&quot;
comma
dot
id|mode
op_assign
l_int|0555
comma
dot
id|child
op_assign
id|nlm_sysctl_dir
comma
)brace
comma
(brace
dot
id|ctl_name
op_assign
l_int|0
)brace
)brace
suffix:semicolon
multiline_comment|/*&n; * Module (and driverfs) parameters.&n; */
DECL|macro|param_set_min_max
mdefine_line|#define param_set_min_max(name, type, which_strtol, min, max)&t;&t;&bslash;&n;static int param_set_##name(const char *val, struct kernel_param *kp)&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;char *endp;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__typeof__(type) num = which_strtol(val, &amp;endp, 0);&t;&t;&bslash;&n;&t;if (endp == val || *endp || num &lt; (min) || num &gt; (max))&t;&t;&bslash;&n;&t;&t;return -EINVAL;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;*((int *) kp-&gt;arg) = num;&t;&t;&t;&t;&t;&bslash;&n;&t;return 0;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;}
id|param_set_min_max
c_func
(paren
id|port
comma
r_int
comma
id|simple_strtol
comma
l_int|0
comma
l_int|65535
)paren
id|param_set_min_max
c_func
(paren
id|grace_period
comma
r_int
r_int
comma
id|simple_strtoul
comma
id|nlm_grace_period_min
comma
id|nlm_grace_period_max
)paren
id|param_set_min_max
c_func
(paren
id|timeout
comma
r_int
r_int
comma
id|simple_strtoul
comma
id|nlm_timeout_min
comma
id|nlm_timeout_max
)paren
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Olaf Kirch &lt;okir@monad.swb.de&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;NFS file locking service version &quot;
id|LOCKD_VERSION
l_string|&quot;.&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|module_param_call
c_func
(paren
id|nlm_grace_period
comma
id|param_set_grace_period
comma
id|param_get_ulong
comma
op_amp
id|nlm_grace_period
comma
l_int|0644
)paren
suffix:semicolon
id|module_param_call
c_func
(paren
id|nlm_timeout
comma
id|param_set_timeout
comma
id|param_get_ulong
comma
op_amp
id|nlm_timeout
comma
l_int|0644
)paren
suffix:semicolon
id|module_param_call
c_func
(paren
id|nlm_udpport
comma
id|param_set_port
comma
id|param_get_int
comma
op_amp
id|nlm_udpport
comma
l_int|0644
)paren
suffix:semicolon
id|module_param_call
c_func
(paren
id|nlm_tcpport
comma
id|param_set_port
comma
id|param_get_int
comma
op_amp
id|nlm_tcpport
comma
l_int|0644
)paren
suffix:semicolon
multiline_comment|/*&n; * Initialising and terminating the module.&n; */
DECL|function|init_nlm
r_static
r_int
id|__init
id|init_nlm
c_func
(paren
r_void
)paren
(brace
id|nlm_sysctl_table
op_assign
id|register_sysctl_table
c_func
(paren
id|nlm_sysctl_root
comma
l_int|0
)paren
suffix:semicolon
r_return
id|nlm_sysctl_table
ques
c_cond
l_int|0
suffix:colon
op_minus
id|ENOMEM
suffix:semicolon
)brace
DECL|function|exit_nlm
r_static
r_void
id|__exit
id|exit_nlm
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* FIXME: delete all NLM clients */
id|nlm_shutdown_hosts
c_func
(paren
)paren
suffix:semicolon
id|unregister_sysctl_table
c_func
(paren
id|nlm_sysctl_table
)paren
suffix:semicolon
)brace
DECL|variable|init_nlm
id|module_init
c_func
(paren
id|init_nlm
)paren
suffix:semicolon
DECL|variable|exit_nlm
id|module_exit
c_func
(paren
id|exit_nlm
)paren
suffix:semicolon
multiline_comment|/*&n; * Define NLM program and procedures&n; */
DECL|variable|nlmsvc_version1
r_static
r_struct
id|svc_version
id|nlmsvc_version1
op_assign
(brace
dot
id|vs_vers
op_assign
l_int|1
comma
dot
id|vs_nproc
op_assign
l_int|17
comma
dot
id|vs_proc
op_assign
id|nlmsvc_procedures
comma
dot
id|vs_xdrsize
op_assign
id|NLMSVC_XDRSIZE
comma
)brace
suffix:semicolon
DECL|variable|nlmsvc_version3
r_static
r_struct
id|svc_version
id|nlmsvc_version3
op_assign
(brace
dot
id|vs_vers
op_assign
l_int|3
comma
dot
id|vs_nproc
op_assign
l_int|24
comma
dot
id|vs_proc
op_assign
id|nlmsvc_procedures
comma
dot
id|vs_xdrsize
op_assign
id|NLMSVC_XDRSIZE
comma
)brace
suffix:semicolon
macro_line|#ifdef CONFIG_LOCKD_V4
DECL|variable|nlmsvc_version4
r_static
r_struct
id|svc_version
id|nlmsvc_version4
op_assign
(brace
dot
id|vs_vers
op_assign
l_int|4
comma
dot
id|vs_nproc
op_assign
l_int|24
comma
dot
id|vs_proc
op_assign
id|nlmsvc_procedures4
comma
dot
id|vs_xdrsize
op_assign
id|NLMSVC_XDRSIZE
comma
)brace
suffix:semicolon
macro_line|#endif
DECL|variable|nlmsvc_version
r_static
r_struct
id|svc_version
op_star
id|nlmsvc_version
(braket
)braket
op_assign
(brace
(braket
l_int|1
)braket
op_assign
op_amp
id|nlmsvc_version1
comma
(braket
l_int|3
)braket
op_assign
op_amp
id|nlmsvc_version3
comma
macro_line|#ifdef CONFIG_LOCKD_V4
(braket
l_int|4
)braket
op_assign
op_amp
id|nlmsvc_version4
comma
macro_line|#endif
)brace
suffix:semicolon
DECL|variable|nlmsvc_stats
r_static
r_struct
id|svc_stat
id|nlmsvc_stats
suffix:semicolon
DECL|macro|NLM_NRVERS
mdefine_line|#define NLM_NRVERS&t;(sizeof(nlmsvc_version)/sizeof(nlmsvc_version[0]))
DECL|variable|nlmsvc_program
r_static
r_struct
id|svc_program
id|nlmsvc_program
op_assign
(brace
dot
id|pg_prog
op_assign
id|NLM_PROGRAM
comma
multiline_comment|/* program number */
dot
id|pg_nvers
op_assign
id|NLM_NRVERS
comma
multiline_comment|/* number of entries in nlmsvc_version */
dot
id|pg_vers
op_assign
id|nlmsvc_version
comma
multiline_comment|/* version table */
dot
id|pg_name
op_assign
l_string|&quot;lockd&quot;
comma
multiline_comment|/* service name */
dot
id|pg_class
op_assign
l_string|&quot;nfsd&quot;
comma
multiline_comment|/* share authentication with nfsd */
dot
id|pg_stats
op_assign
op_amp
id|nlmsvc_stats
comma
multiline_comment|/* stats table */
)brace
suffix:semicolon
eof
