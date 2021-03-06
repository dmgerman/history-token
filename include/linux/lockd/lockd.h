multiline_comment|/*&n; * linux/include/linux/lockd/lockd.h&n; *&n; * General-purpose lockd include file.&n; *&n; * Copyright (C) 1996 Olaf Kirch &lt;okir@monad.swb.de&gt;&n; */
macro_line|#ifndef LINUX_LOCKD_LOCKD_H
DECL|macro|LINUX_LOCKD_LOCKD_H
mdefine_line|#define LINUX_LOCKD_LOCKD_H
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/utsname.h&gt;
macro_line|#include &lt;linux/nfsd/nfsfh.h&gt;
macro_line|#include &lt;linux/lockd/bind.h&gt;
macro_line|#include &lt;linux/lockd/xdr.h&gt;
macro_line|#ifdef CONFIG_LOCKD_V4
macro_line|#include &lt;linux/lockd/xdr4.h&gt;
macro_line|#endif
macro_line|#include &lt;linux/lockd/debug.h&gt;
multiline_comment|/*&n; * Version string&n; */
DECL|macro|LOCKD_VERSION
mdefine_line|#define LOCKD_VERSION&t;&t;&quot;0.5&quot;
multiline_comment|/*&n; * Default timeout for RPC calls (seconds)&n; */
DECL|macro|LOCKD_DFLT_TIMEO
mdefine_line|#define LOCKD_DFLT_TIMEO&t;10
multiline_comment|/*&n; * Lockd host handle (used both by the client and server personality).&n; */
DECL|struct|nlm_host
r_struct
id|nlm_host
(brace
DECL|member|h_next
r_struct
id|nlm_host
op_star
id|h_next
suffix:semicolon
multiline_comment|/* linked list (hash table) */
DECL|member|h_addr
r_struct
id|sockaddr_in
id|h_addr
suffix:semicolon
multiline_comment|/* peer address */
DECL|member|h_rpcclnt
r_struct
id|rpc_clnt
op_star
id|h_rpcclnt
suffix:semicolon
multiline_comment|/* RPC client to talk to peer */
DECL|member|h_name
r_char
id|h_name
(braket
l_int|20
)braket
suffix:semicolon
multiline_comment|/* remote hostname */
DECL|member|h_version
id|u32
id|h_version
suffix:semicolon
multiline_comment|/* interface version */
DECL|member|h_proto
r_int
r_int
id|h_proto
suffix:semicolon
multiline_comment|/* transport proto */
DECL|member|h_reclaiming
r_int
r_int
id|h_reclaiming
suffix:colon
l_int|1
comma
DECL|member|h_server
id|h_server
suffix:colon
l_int|1
comma
multiline_comment|/* server side, not client side */
DECL|member|h_inuse
id|h_inuse
suffix:colon
l_int|1
comma
DECL|member|h_killed
id|h_killed
suffix:colon
l_int|1
comma
DECL|member|h_monitored
id|h_monitored
suffix:colon
l_int|1
suffix:semicolon
DECL|member|h_gracewait
id|wait_queue_head_t
id|h_gracewait
suffix:semicolon
multiline_comment|/* wait while reclaiming */
DECL|member|h_state
id|u32
id|h_state
suffix:semicolon
multiline_comment|/* pseudo-state counter */
DECL|member|h_nsmstate
id|u32
id|h_nsmstate
suffix:semicolon
multiline_comment|/* true remote NSM state */
DECL|member|h_pidcount
id|u32
id|h_pidcount
suffix:semicolon
multiline_comment|/* Pseudopids */
DECL|member|h_count
id|atomic_t
id|h_count
suffix:semicolon
multiline_comment|/* reference count */
DECL|member|h_sema
r_struct
id|semaphore
id|h_sema
suffix:semicolon
multiline_comment|/* mutex for pmap binding */
DECL|member|h_nextrebind
r_int
r_int
id|h_nextrebind
suffix:semicolon
multiline_comment|/* next portmap call */
DECL|member|h_expires
r_int
r_int
id|h_expires
suffix:semicolon
multiline_comment|/* eligible for GC */
DECL|member|h_lockowners
r_struct
id|list_head
id|h_lockowners
suffix:semicolon
multiline_comment|/* Lockowners for the client */
DECL|member|h_lock
id|spinlock_t
id|h_lock
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Map an fl_owner_t into a unique 32-bit &quot;pid&quot;&n; */
DECL|struct|nlm_lockowner
r_struct
id|nlm_lockowner
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|count
id|atomic_t
id|count
suffix:semicolon
DECL|member|host
r_struct
id|nlm_host
op_star
id|host
suffix:semicolon
DECL|member|owner
id|fl_owner_t
id|owner
suffix:semicolon
DECL|member|pid
r_uint32
id|pid
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Memory chunk for NLM client RPC request.&n; */
DECL|macro|NLMCLNT_OHSIZE
mdefine_line|#define NLMCLNT_OHSIZE&t;&t;(sizeof(system_utsname.nodename)+10)
DECL|struct|nlm_rqst
r_struct
id|nlm_rqst
(brace
DECL|member|a_flags
r_int
r_int
id|a_flags
suffix:semicolon
multiline_comment|/* initial RPC task flags */
DECL|member|a_host
r_struct
id|nlm_host
op_star
id|a_host
suffix:semicolon
multiline_comment|/* host handle */
DECL|member|a_args
r_struct
id|nlm_args
id|a_args
suffix:semicolon
multiline_comment|/* arguments */
DECL|member|a_res
r_struct
id|nlm_res
id|a_res
suffix:semicolon
multiline_comment|/* result */
DECL|member|a_owner
r_char
id|a_owner
(braket
id|NLMCLNT_OHSIZE
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * This struct describes a file held open by lockd on behalf of&n; * an NFS client.&n; */
DECL|struct|nlm_file
r_struct
id|nlm_file
(brace
DECL|member|f_next
r_struct
id|nlm_file
op_star
id|f_next
suffix:semicolon
multiline_comment|/* linked list */
DECL|member|f_handle
r_struct
id|nfs_fh
id|f_handle
suffix:semicolon
multiline_comment|/* NFS file handle */
DECL|member|f_file
r_struct
id|file
op_star
id|f_file
suffix:semicolon
multiline_comment|/* VFS file pointer */
DECL|member|f_shares
r_struct
id|nlm_share
op_star
id|f_shares
suffix:semicolon
multiline_comment|/* DOS shares */
DECL|member|f_blocks
r_struct
id|nlm_block
op_star
id|f_blocks
suffix:semicolon
multiline_comment|/* blocked locks */
DECL|member|f_locks
r_int
r_int
id|f_locks
suffix:semicolon
multiline_comment|/* guesstimate # of locks */
DECL|member|f_count
r_int
r_int
id|f_count
suffix:semicolon
multiline_comment|/* reference count */
DECL|member|f_sema
r_struct
id|semaphore
id|f_sema
suffix:semicolon
multiline_comment|/* avoid concurrent access */
DECL|member|f_hash
r_int
id|f_hash
suffix:semicolon
multiline_comment|/* hash of f_handle */
)brace
suffix:semicolon
multiline_comment|/*&n; * This is a server block (i.e. a lock requested by some client which&n; * couldn&squot;t be granted because of a conflicting lock).&n; */
DECL|macro|NLM_NEVER
mdefine_line|#define NLM_NEVER&t;&t;(~(unsigned long) 0)
DECL|struct|nlm_block
r_struct
id|nlm_block
(brace
DECL|member|b_next
r_struct
id|nlm_block
op_star
id|b_next
suffix:semicolon
multiline_comment|/* linked list (all blocks) */
DECL|member|b_fnext
r_struct
id|nlm_block
op_star
id|b_fnext
suffix:semicolon
multiline_comment|/* linked list (per file) */
DECL|member|b_call
r_struct
id|nlm_rqst
id|b_call
suffix:semicolon
multiline_comment|/* RPC args &amp; callback info */
DECL|member|b_daemon
r_struct
id|svc_serv
op_star
id|b_daemon
suffix:semicolon
multiline_comment|/* NLM service */
DECL|member|b_host
r_struct
id|nlm_host
op_star
id|b_host
suffix:semicolon
multiline_comment|/* host handle for RPC clnt */
DECL|member|b_when
r_int
r_int
id|b_when
suffix:semicolon
multiline_comment|/* next re-xmit */
DECL|member|b_id
r_int
r_int
id|b_id
suffix:semicolon
multiline_comment|/* block id */
DECL|member|b_queued
r_int
r_char
id|b_queued
suffix:semicolon
multiline_comment|/* re-queued */
DECL|member|b_granted
r_int
r_char
id|b_granted
suffix:semicolon
multiline_comment|/* VFS granted lock */
DECL|member|b_incall
r_int
r_char
id|b_incall
suffix:semicolon
multiline_comment|/* doing callback */
DECL|member|b_done
r_int
r_char
id|b_done
suffix:semicolon
multiline_comment|/* callback complete */
DECL|member|b_file
r_struct
id|nlm_file
op_star
id|b_file
suffix:semicolon
multiline_comment|/* file in question */
)brace
suffix:semicolon
multiline_comment|/*&n; * Valid actions for nlmsvc_traverse_files&n; */
DECL|macro|NLM_ACT_CHECK
mdefine_line|#define NLM_ACT_CHECK&t;&t;0&t;&t;/* check for locks */
DECL|macro|NLM_ACT_MARK
mdefine_line|#define NLM_ACT_MARK&t;&t;1&t;&t;/* mark &amp; sweep */
DECL|macro|NLM_ACT_UNLOCK
mdefine_line|#define NLM_ACT_UNLOCK&t;&t;2&t;&t;/* release all locks */
multiline_comment|/*&n; * Global variables&n; */
r_extern
r_struct
id|rpc_program
id|nlm_program
suffix:semicolon
r_extern
r_struct
id|svc_procedure
id|nlmsvc_procedures
(braket
)braket
suffix:semicolon
macro_line|#ifdef CONFIG_LOCKD_V4
r_extern
r_struct
id|svc_procedure
id|nlmsvc_procedures4
(braket
)braket
suffix:semicolon
macro_line|#endif
r_extern
r_int
id|nlmsvc_grace_period
suffix:semicolon
r_extern
r_int
r_int
id|nlmsvc_timeout
suffix:semicolon
multiline_comment|/*&n; * Lockd client functions&n; */
r_struct
id|nlm_rqst
op_star
id|nlmclnt_alloc_call
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|nlmclnt_block
c_func
(paren
r_struct
id|nlm_host
op_star
comma
r_struct
id|file_lock
op_star
comma
id|u32
op_star
)paren
suffix:semicolon
r_int
id|nlmclnt_cancel
c_func
(paren
r_struct
id|nlm_host
op_star
comma
r_struct
id|file_lock
op_star
)paren
suffix:semicolon
id|u32
id|nlmclnt_grant
c_func
(paren
r_struct
id|nlm_lock
op_star
)paren
suffix:semicolon
r_void
id|nlmclnt_recovery
c_func
(paren
r_struct
id|nlm_host
op_star
comma
id|u32
)paren
suffix:semicolon
r_int
id|nlmclnt_reclaim
c_func
(paren
r_struct
id|nlm_host
op_star
comma
r_struct
id|file_lock
op_star
)paren
suffix:semicolon
r_int
id|nlmclnt_setgrantargs
c_func
(paren
r_struct
id|nlm_rqst
op_star
comma
r_struct
id|nlm_lock
op_star
)paren
suffix:semicolon
r_void
id|nlmclnt_freegrantargs
c_func
(paren
r_struct
id|nlm_rqst
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; * Host cache&n; */
r_struct
id|nlm_host
op_star
id|nlmclnt_lookup_host
c_func
(paren
r_struct
id|sockaddr_in
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_struct
id|nlm_host
op_star
id|nlmsvc_lookup_host
c_func
(paren
r_struct
id|svc_rqst
op_star
)paren
suffix:semicolon
r_struct
id|nlm_host
op_star
id|nlm_lookup_host
c_func
(paren
r_int
id|server
comma
r_struct
id|sockaddr_in
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_struct
id|rpc_clnt
op_star
id|nlm_bind_host
c_func
(paren
r_struct
id|nlm_host
op_star
)paren
suffix:semicolon
r_void
id|nlm_rebind_host
c_func
(paren
r_struct
id|nlm_host
op_star
)paren
suffix:semicolon
r_struct
id|nlm_host
op_star
id|nlm_get_host
c_func
(paren
r_struct
id|nlm_host
op_star
)paren
suffix:semicolon
r_void
id|nlm_release_host
c_func
(paren
r_struct
id|nlm_host
op_star
)paren
suffix:semicolon
r_void
id|nlm_shutdown_hosts
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_struct
id|nlm_host
op_star
id|nlm_find_client
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * Server-side lock handling&n; */
r_int
id|nlmsvc_async_call
c_func
(paren
r_struct
id|nlm_rqst
op_star
comma
id|u32
comma
id|rpc_action
)paren
suffix:semicolon
id|u32
id|nlmsvc_lock
c_func
(paren
r_struct
id|svc_rqst
op_star
comma
r_struct
id|nlm_file
op_star
comma
r_struct
id|nlm_lock
op_star
comma
r_int
comma
r_struct
id|nlm_cookie
op_star
)paren
suffix:semicolon
id|u32
id|nlmsvc_unlock
c_func
(paren
r_struct
id|nlm_file
op_star
comma
r_struct
id|nlm_lock
op_star
)paren
suffix:semicolon
id|u32
id|nlmsvc_testlock
c_func
(paren
r_struct
id|nlm_file
op_star
comma
r_struct
id|nlm_lock
op_star
comma
r_struct
id|nlm_lock
op_star
)paren
suffix:semicolon
id|u32
id|nlmsvc_cancel_blocked
c_func
(paren
r_struct
id|nlm_file
op_star
comma
r_struct
id|nlm_lock
op_star
)paren
suffix:semicolon
r_int
r_int
id|nlmsvc_retry_blocked
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|nlmsvc_traverse_blocks
c_func
(paren
r_struct
id|nlm_host
op_star
comma
r_struct
id|nlm_file
op_star
comma
r_int
id|action
)paren
suffix:semicolon
r_void
id|nlmsvc_grant_reply
c_func
(paren
r_struct
id|svc_rqst
op_star
comma
r_struct
id|nlm_cookie
op_star
comma
id|u32
)paren
suffix:semicolon
multiline_comment|/*&n; * File handling for the server personality&n; */
id|u32
id|nlm_lookup_file
c_func
(paren
r_struct
id|svc_rqst
op_star
comma
r_struct
id|nlm_file
op_star
op_star
comma
r_struct
id|nfs_fh
op_star
)paren
suffix:semicolon
r_void
id|nlm_release_file
c_func
(paren
r_struct
id|nlm_file
op_star
)paren
suffix:semicolon
r_void
id|nlmsvc_mark_resources
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|nlmsvc_free_host_resources
c_func
(paren
r_struct
id|nlm_host
op_star
)paren
suffix:semicolon
r_void
id|nlmsvc_invalidate_all
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
id|__inline__
r_struct
id|inode
op_star
DECL|function|nlmsvc_file_inode
id|nlmsvc_file_inode
c_func
(paren
r_struct
id|nlm_file
op_star
id|file
)paren
(brace
r_return
id|file-&gt;f_file-&gt;f_dentry-&gt;d_inode
suffix:semicolon
)brace
multiline_comment|/*&n; * Compare two host addresses (needs modifying for ipv6)&n; */
r_static
id|__inline__
r_int
DECL|function|nlm_cmp_addr
id|nlm_cmp_addr
c_func
(paren
r_struct
id|sockaddr_in
op_star
id|sin1
comma
r_struct
id|sockaddr_in
op_star
id|sin2
)paren
(brace
r_return
id|sin1-&gt;sin_addr.s_addr
op_eq
id|sin2-&gt;sin_addr.s_addr
suffix:semicolon
)brace
multiline_comment|/*&n; * Compare two NLM locks.&n; * When the second lock is of type F_UNLCK, this acts like a wildcard.&n; */
r_static
id|__inline__
r_int
DECL|function|nlm_compare_locks
id|nlm_compare_locks
c_func
(paren
r_struct
id|file_lock
op_star
id|fl1
comma
r_struct
id|file_lock
op_star
id|fl2
)paren
(brace
r_return
id|fl1-&gt;fl_pid
op_eq
id|fl2-&gt;fl_pid
op_logical_and
id|fl1-&gt;fl_start
op_eq
id|fl2-&gt;fl_start
op_logical_and
id|fl1-&gt;fl_end
op_eq
id|fl2-&gt;fl_end
op_logical_and
(paren
id|fl1-&gt;fl_type
op_eq
id|fl2-&gt;fl_type
op_logical_or
id|fl2-&gt;fl_type
op_eq
id|F_UNLCK
)paren
suffix:semicolon
)brace
r_extern
r_struct
id|lock_manager_operations
id|nlmsvc_lock_operations
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* LINUX_LOCKD_LOCKD_H */
eof
