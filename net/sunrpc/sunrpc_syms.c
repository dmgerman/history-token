multiline_comment|/*&n; * linux/net/sunrpc/sunrpc_syms.c&n; *&n; * Symbols exported by the sunrpc module.&n; *&n; * Copyright (C) 1997 Olaf Kirch &lt;okir@monad.swb.de&gt;&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/uio.h&gt;
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/sunrpc/sched.h&gt;
macro_line|#include &lt;linux/sunrpc/clnt.h&gt;
macro_line|#include &lt;linux/sunrpc/svc.h&gt;
macro_line|#include &lt;linux/sunrpc/svcsock.h&gt;
macro_line|#include &lt;linux/sunrpc/auth.h&gt;
macro_line|#include &lt;linux/sunrpc/rpc_pipe_fs.h&gt;
multiline_comment|/* RPC scheduler */
DECL|variable|rpc_execute
id|EXPORT_SYMBOL
c_func
(paren
id|rpc_execute
)paren
suffix:semicolon
DECL|variable|rpc_init_task
id|EXPORT_SYMBOL
c_func
(paren
id|rpc_init_task
)paren
suffix:semicolon
DECL|variable|rpc_sleep_on
id|EXPORT_SYMBOL
c_func
(paren
id|rpc_sleep_on
)paren
suffix:semicolon
DECL|variable|rpc_wake_up_next
id|EXPORT_SYMBOL
c_func
(paren
id|rpc_wake_up_next
)paren
suffix:semicolon
DECL|variable|rpc_wake_up_task
id|EXPORT_SYMBOL
c_func
(paren
id|rpc_wake_up_task
)paren
suffix:semicolon
DECL|variable|rpc_new_child
id|EXPORT_SYMBOL
c_func
(paren
id|rpc_new_child
)paren
suffix:semicolon
DECL|variable|rpc_run_child
id|EXPORT_SYMBOL
c_func
(paren
id|rpc_run_child
)paren
suffix:semicolon
DECL|variable|rpciod_down
id|EXPORT_SYMBOL
c_func
(paren
id|rpciod_down
)paren
suffix:semicolon
DECL|variable|rpciod_up
id|EXPORT_SYMBOL
c_func
(paren
id|rpciod_up
)paren
suffix:semicolon
DECL|variable|rpc_new_task
id|EXPORT_SYMBOL
c_func
(paren
id|rpc_new_task
)paren
suffix:semicolon
DECL|variable|rpc_wake_up_status
id|EXPORT_SYMBOL
c_func
(paren
id|rpc_wake_up_status
)paren
suffix:semicolon
DECL|variable|rpc_release_task
id|EXPORT_SYMBOL
c_func
(paren
id|rpc_release_task
)paren
suffix:semicolon
multiline_comment|/* RPC client functions */
DECL|variable|rpc_create_client
id|EXPORT_SYMBOL
c_func
(paren
id|rpc_create_client
)paren
suffix:semicolon
DECL|variable|rpc_destroy_client
id|EXPORT_SYMBOL
c_func
(paren
id|rpc_destroy_client
)paren
suffix:semicolon
DECL|variable|rpc_shutdown_client
id|EXPORT_SYMBOL
c_func
(paren
id|rpc_shutdown_client
)paren
suffix:semicolon
DECL|variable|rpc_release_client
id|EXPORT_SYMBOL
c_func
(paren
id|rpc_release_client
)paren
suffix:semicolon
DECL|variable|rpc_killall_tasks
id|EXPORT_SYMBOL
c_func
(paren
id|rpc_killall_tasks
)paren
suffix:semicolon
DECL|variable|rpc_call_sync
id|EXPORT_SYMBOL
c_func
(paren
id|rpc_call_sync
)paren
suffix:semicolon
DECL|variable|rpc_call_async
id|EXPORT_SYMBOL
c_func
(paren
id|rpc_call_async
)paren
suffix:semicolon
DECL|variable|rpc_call_setup
id|EXPORT_SYMBOL
c_func
(paren
id|rpc_call_setup
)paren
suffix:semicolon
DECL|variable|rpc_clnt_sigmask
id|EXPORT_SYMBOL
c_func
(paren
id|rpc_clnt_sigmask
)paren
suffix:semicolon
DECL|variable|rpc_clnt_sigunmask
id|EXPORT_SYMBOL
c_func
(paren
id|rpc_clnt_sigunmask
)paren
suffix:semicolon
DECL|variable|rpc_delay
id|EXPORT_SYMBOL
c_func
(paren
id|rpc_delay
)paren
suffix:semicolon
DECL|variable|rpc_restart_call
id|EXPORT_SYMBOL
c_func
(paren
id|rpc_restart_call
)paren
suffix:semicolon
DECL|variable|rpc_setbufsize
id|EXPORT_SYMBOL
c_func
(paren
id|rpc_setbufsize
)paren
suffix:semicolon
DECL|variable|rpc_unlink
id|EXPORT_SYMBOL
c_func
(paren
id|rpc_unlink
)paren
suffix:semicolon
DECL|variable|rpc_wake_up
id|EXPORT_SYMBOL
c_func
(paren
id|rpc_wake_up
)paren
suffix:semicolon
DECL|variable|rpc_queue_upcall
id|EXPORT_SYMBOL
c_func
(paren
id|rpc_queue_upcall
)paren
suffix:semicolon
DECL|variable|rpc_mkpipe
id|EXPORT_SYMBOL
c_func
(paren
id|rpc_mkpipe
)paren
suffix:semicolon
DECL|variable|__rpc_purge_current_upcall
id|EXPORT_SYMBOL
c_func
(paren
id|__rpc_purge_current_upcall
)paren
suffix:semicolon
multiline_comment|/* Client transport */
DECL|variable|xprt_create_proto
id|EXPORT_SYMBOL
c_func
(paren
id|xprt_create_proto
)paren
suffix:semicolon
DECL|variable|xprt_destroy
id|EXPORT_SYMBOL
c_func
(paren
id|xprt_destroy
)paren
suffix:semicolon
DECL|variable|xprt_set_timeout
id|EXPORT_SYMBOL
c_func
(paren
id|xprt_set_timeout
)paren
suffix:semicolon
multiline_comment|/* Client credential cache */
DECL|variable|rpcauth_register
id|EXPORT_SYMBOL
c_func
(paren
id|rpcauth_register
)paren
suffix:semicolon
DECL|variable|rpcauth_unregister
id|EXPORT_SYMBOL
c_func
(paren
id|rpcauth_unregister
)paren
suffix:semicolon
DECL|variable|rpcauth_lookupcred
id|EXPORT_SYMBOL
c_func
(paren
id|rpcauth_lookupcred
)paren
suffix:semicolon
DECL|variable|rpcauth_lookup_credcache
id|EXPORT_SYMBOL
c_func
(paren
id|rpcauth_lookup_credcache
)paren
suffix:semicolon
DECL|variable|rpcauth_free_credcache
id|EXPORT_SYMBOL
c_func
(paren
id|rpcauth_free_credcache
)paren
suffix:semicolon
DECL|variable|rpcauth_init_credcache
id|EXPORT_SYMBOL
c_func
(paren
id|rpcauth_init_credcache
)paren
suffix:semicolon
DECL|variable|put_rpccred
id|EXPORT_SYMBOL
c_func
(paren
id|put_rpccred
)paren
suffix:semicolon
multiline_comment|/* RPC server stuff */
DECL|variable|svc_create
id|EXPORT_SYMBOL
c_func
(paren
id|svc_create
)paren
suffix:semicolon
DECL|variable|svc_create_thread
id|EXPORT_SYMBOL
c_func
(paren
id|svc_create_thread
)paren
suffix:semicolon
DECL|variable|svc_exit_thread
id|EXPORT_SYMBOL
c_func
(paren
id|svc_exit_thread
)paren
suffix:semicolon
DECL|variable|svc_destroy
id|EXPORT_SYMBOL
c_func
(paren
id|svc_destroy
)paren
suffix:semicolon
DECL|variable|svc_drop
id|EXPORT_SYMBOL
c_func
(paren
id|svc_drop
)paren
suffix:semicolon
DECL|variable|svc_process
id|EXPORT_SYMBOL
c_func
(paren
id|svc_process
)paren
suffix:semicolon
DECL|variable|svc_recv
id|EXPORT_SYMBOL
c_func
(paren
id|svc_recv
)paren
suffix:semicolon
DECL|variable|svc_wake_up
id|EXPORT_SYMBOL
c_func
(paren
id|svc_wake_up
)paren
suffix:semicolon
DECL|variable|svc_makesock
id|EXPORT_SYMBOL
c_func
(paren
id|svc_makesock
)paren
suffix:semicolon
DECL|variable|svc_reserve
id|EXPORT_SYMBOL
c_func
(paren
id|svc_reserve
)paren
suffix:semicolon
multiline_comment|/* RPC statistics */
macro_line|#ifdef CONFIG_PROC_FS
DECL|variable|rpc_proc_register
id|EXPORT_SYMBOL
c_func
(paren
id|rpc_proc_register
)paren
suffix:semicolon
DECL|variable|rpc_proc_unregister
id|EXPORT_SYMBOL
c_func
(paren
id|rpc_proc_unregister
)paren
suffix:semicolon
DECL|variable|rpc_proc_read
id|EXPORT_SYMBOL
c_func
(paren
id|rpc_proc_read
)paren
suffix:semicolon
DECL|variable|svc_proc_register
id|EXPORT_SYMBOL
c_func
(paren
id|svc_proc_register
)paren
suffix:semicolon
DECL|variable|svc_proc_unregister
id|EXPORT_SYMBOL
c_func
(paren
id|svc_proc_unregister
)paren
suffix:semicolon
DECL|variable|svc_proc_read
id|EXPORT_SYMBOL
c_func
(paren
id|svc_proc_read
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* caching... */
DECL|variable|auth_domain_find
id|EXPORT_SYMBOL
c_func
(paren
id|auth_domain_find
)paren
suffix:semicolon
DECL|variable|auth_domain_put
id|EXPORT_SYMBOL
c_func
(paren
id|auth_domain_put
)paren
suffix:semicolon
DECL|variable|auth_unix_add_addr
id|EXPORT_SYMBOL
c_func
(paren
id|auth_unix_add_addr
)paren
suffix:semicolon
DECL|variable|auth_unix_forget_old
id|EXPORT_SYMBOL
c_func
(paren
id|auth_unix_forget_old
)paren
suffix:semicolon
DECL|variable|auth_unix_lookup
id|EXPORT_SYMBOL
c_func
(paren
id|auth_unix_lookup
)paren
suffix:semicolon
DECL|variable|cache_check
id|EXPORT_SYMBOL
c_func
(paren
id|cache_check
)paren
suffix:semicolon
DECL|variable|cache_clean
id|EXPORT_SYMBOL
c_func
(paren
id|cache_clean
)paren
suffix:semicolon
DECL|variable|cache_flush
id|EXPORT_SYMBOL
c_func
(paren
id|cache_flush
)paren
suffix:semicolon
DECL|variable|cache_purge
id|EXPORT_SYMBOL
c_func
(paren
id|cache_purge
)paren
suffix:semicolon
DECL|variable|cache_fresh
id|EXPORT_SYMBOL
c_func
(paren
id|cache_fresh
)paren
suffix:semicolon
DECL|variable|cache_init
id|EXPORT_SYMBOL
c_func
(paren
id|cache_init
)paren
suffix:semicolon
DECL|variable|cache_register
id|EXPORT_SYMBOL
c_func
(paren
id|cache_register
)paren
suffix:semicolon
DECL|variable|cache_unregister
id|EXPORT_SYMBOL
c_func
(paren
id|cache_unregister
)paren
suffix:semicolon
DECL|variable|qword_add
id|EXPORT_SYMBOL
c_func
(paren
id|qword_add
)paren
suffix:semicolon
DECL|variable|qword_addhex
id|EXPORT_SYMBOL
c_func
(paren
id|qword_addhex
)paren
suffix:semicolon
DECL|variable|qword_get
id|EXPORT_SYMBOL
c_func
(paren
id|qword_get
)paren
suffix:semicolon
DECL|variable|svcauth_unix_purge
id|EXPORT_SYMBOL
c_func
(paren
id|svcauth_unix_purge
)paren
suffix:semicolon
DECL|variable|unix_domain_find
id|EXPORT_SYMBOL
c_func
(paren
id|unix_domain_find
)paren
suffix:semicolon
multiline_comment|/* Generic XDR */
DECL|variable|xdr_encode_array
id|EXPORT_SYMBOL
c_func
(paren
id|xdr_encode_array
)paren
suffix:semicolon
DECL|variable|xdr_encode_string
id|EXPORT_SYMBOL
c_func
(paren
id|xdr_encode_string
)paren
suffix:semicolon
DECL|variable|xdr_decode_string
id|EXPORT_SYMBOL
c_func
(paren
id|xdr_decode_string
)paren
suffix:semicolon
DECL|variable|xdr_decode_string_inplace
id|EXPORT_SYMBOL
c_func
(paren
id|xdr_decode_string_inplace
)paren
suffix:semicolon
DECL|variable|xdr_decode_netobj
id|EXPORT_SYMBOL
c_func
(paren
id|xdr_decode_netobj
)paren
suffix:semicolon
DECL|variable|xdr_encode_netobj
id|EXPORT_SYMBOL
c_func
(paren
id|xdr_encode_netobj
)paren
suffix:semicolon
DECL|variable|xdr_encode_pages
id|EXPORT_SYMBOL
c_func
(paren
id|xdr_encode_pages
)paren
suffix:semicolon
DECL|variable|xdr_inline_pages
id|EXPORT_SYMBOL
c_func
(paren
id|xdr_inline_pages
)paren
suffix:semicolon
DECL|variable|xdr_shift_buf
id|EXPORT_SYMBOL
c_func
(paren
id|xdr_shift_buf
)paren
suffix:semicolon
DECL|variable|xdr_write_pages
id|EXPORT_SYMBOL
c_func
(paren
id|xdr_write_pages
)paren
suffix:semicolon
DECL|variable|xdr_read_pages
id|EXPORT_SYMBOL
c_func
(paren
id|xdr_read_pages
)paren
suffix:semicolon
multiline_comment|/* Debugging symbols */
macro_line|#ifdef RPC_DEBUG
DECL|variable|rpc_debug
id|EXPORT_SYMBOL
c_func
(paren
id|rpc_debug
)paren
suffix:semicolon
DECL|variable|nfs_debug
id|EXPORT_SYMBOL
c_func
(paren
id|nfs_debug
)paren
suffix:semicolon
DECL|variable|nfsd_debug
id|EXPORT_SYMBOL
c_func
(paren
id|nfsd_debug
)paren
suffix:semicolon
DECL|variable|nlm_debug
id|EXPORT_SYMBOL
c_func
(paren
id|nlm_debug
)paren
suffix:semicolon
macro_line|#endif
r_extern
r_int
id|register_rpc_pipefs
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|unregister_rpc_pipefs
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_int
id|__init
DECL|function|init_sunrpc
id|init_sunrpc
c_func
(paren
r_void
)paren
(brace
r_int
id|err
op_assign
id|register_rpc_pipefs
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_goto
id|out
suffix:semicolon
id|err
op_assign
id|rpc_init_mempool
c_func
(paren
)paren
op_ne
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_goto
id|out
suffix:semicolon
macro_line|#ifdef RPC_DEBUG
id|rpc_register_sysctl
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_PROC_FS
id|rpc_proc_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
id|cache_register
c_func
(paren
op_amp
id|auth_domain_cache
)paren
suffix:semicolon
id|cache_register
c_func
(paren
op_amp
id|ip_map_cache
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|err
suffix:semicolon
)brace
r_static
r_void
id|__exit
DECL|function|cleanup_sunrpc
id|cleanup_sunrpc
c_func
(paren
r_void
)paren
(brace
id|unregister_rpc_pipefs
c_func
(paren
)paren
suffix:semicolon
id|rpc_destroy_mempool
c_func
(paren
)paren
suffix:semicolon
id|cache_unregister
c_func
(paren
op_amp
id|auth_domain_cache
)paren
suffix:semicolon
id|cache_unregister
c_func
(paren
op_amp
id|ip_map_cache
)paren
suffix:semicolon
macro_line|#ifdef RPC_DEBUG
id|rpc_unregister_sysctl
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_PROCFS
id|rpc_proc_exit
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
)brace
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|init_sunrpc
id|module_init
c_func
(paren
id|init_sunrpc
)paren
suffix:semicolon
DECL|variable|cleanup_sunrpc
id|module_exit
c_func
(paren
id|cleanup_sunrpc
)paren
suffix:semicolon
eof
