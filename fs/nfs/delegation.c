multiline_comment|/*&n; * linux/fs/nfs/delegation.c&n; *&n; * Copyright (C) 2004 Trond Myklebust&n; *&n; * NFS file delegation management&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/completion.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/nfs4.h&gt;
macro_line|#include &lt;linux/nfs_fs.h&gt;
macro_line|#include &lt;linux/nfs_xdr.h&gt;
macro_line|#include &quot;delegation.h&quot;
DECL|function|nfs_alloc_delegation
r_static
r_struct
id|nfs_delegation
op_star
id|nfs_alloc_delegation
c_func
(paren
r_void
)paren
(brace
r_return
(paren
r_struct
id|nfs_delegation
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|nfs_delegation
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
)brace
DECL|function|nfs_free_delegation
r_static
r_void
id|nfs_free_delegation
c_func
(paren
r_struct
id|nfs_delegation
op_star
id|delegation
)paren
(brace
r_if
c_cond
(paren
id|delegation-&gt;cred
)paren
id|put_rpccred
c_func
(paren
id|delegation-&gt;cred
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|delegation
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Set up a delegation on an inode&n; */
DECL|function|nfs_inode_set_delegation
r_int
id|nfs_inode_set_delegation
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|rpc_cred
op_star
id|cred
comma
r_struct
id|nfs_openres
op_star
id|res
)paren
(brace
r_struct
id|nfs4_client
op_star
id|clp
op_assign
id|NFS_SERVER
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|nfs4_state
suffix:semicolon
r_struct
id|nfs_inode
op_star
id|nfsi
op_assign
id|NFS_I
c_func
(paren
id|inode
)paren
suffix:semicolon
r_struct
id|nfs_delegation
op_star
id|delegation
suffix:semicolon
r_int
id|status
op_assign
l_int|0
suffix:semicolon
id|delegation
op_assign
id|nfs_alloc_delegation
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|delegation
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|memcpy
c_func
(paren
id|delegation-&gt;stateid.data
comma
id|res-&gt;delegation.data
comma
r_sizeof
(paren
id|delegation-&gt;stateid.data
)paren
)paren
suffix:semicolon
id|delegation-&gt;type
op_assign
id|res-&gt;delegation_type
suffix:semicolon
id|delegation-&gt;maxsize
op_assign
id|res-&gt;maxsize
suffix:semicolon
id|delegation-&gt;cred
op_assign
id|get_rpccred
c_func
(paren
id|cred
)paren
suffix:semicolon
id|delegation-&gt;inode
op_assign
id|inode
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|clp-&gt;cl_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nfsi-&gt;delegation
op_eq
l_int|NULL
)paren
(brace
id|list_add
c_func
(paren
op_amp
id|delegation-&gt;super_list
comma
op_amp
id|clp-&gt;cl_delegations
)paren
suffix:semicolon
id|nfsi-&gt;delegation
op_assign
id|delegation
suffix:semicolon
id|delegation
op_assign
l_int|NULL
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|memcmp
c_func
(paren
op_amp
id|delegation-&gt;stateid
comma
op_amp
id|nfsi-&gt;delegation-&gt;stateid
comma
r_sizeof
(paren
id|delegation-&gt;stateid
)paren
)paren
op_ne
l_int|0
op_logical_or
id|delegation-&gt;type
op_ne
id|nfsi-&gt;delegation-&gt;type
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: server %u.%u.%u.%u, handed out a duplicate delegation!&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|NIPQUAD
c_func
(paren
id|clp-&gt;cl_addr
)paren
)paren
suffix:semicolon
id|status
op_assign
op_minus
id|EIO
suffix:semicolon
)brace
)brace
id|spin_unlock
c_func
(paren
op_amp
id|clp-&gt;cl_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|delegation
op_ne
l_int|NULL
)paren
id|kfree
c_func
(paren
id|delegation
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
DECL|function|nfs_do_return_delegation
r_static
r_int
id|nfs_do_return_delegation
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|nfs_delegation
op_star
id|delegation
)paren
(brace
r_int
id|res
op_assign
l_int|0
suffix:semicolon
id|__nfs_revalidate_inode
c_func
(paren
id|NFS_SERVER
c_func
(paren
id|inode
)paren
comma
id|inode
)paren
suffix:semicolon
id|res
op_assign
id|nfs4_proc_delegreturn
c_func
(paren
id|inode
comma
id|delegation-&gt;cred
comma
op_amp
id|delegation-&gt;stateid
)paren
suffix:semicolon
id|nfs_free_delegation
c_func
(paren
id|delegation
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
multiline_comment|/* Sync all data to disk upon delegation return */
DECL|function|nfs_msync_inode
r_static
r_void
id|nfs_msync_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
id|filemap_fdatawrite
c_func
(paren
id|inode-&gt;i_mapping
)paren
suffix:semicolon
id|nfs_wb_all
c_func
(paren
id|inode
)paren
suffix:semicolon
id|filemap_fdatawait
c_func
(paren
id|inode-&gt;i_mapping
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Basic procedure for returning a delegation to the server&n; */
DECL|function|nfs_inode_return_delegation
r_int
id|nfs_inode_return_delegation
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_struct
id|nfs4_client
op_star
id|clp
op_assign
id|NFS_SERVER
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|nfs4_state
suffix:semicolon
r_struct
id|nfs_inode
op_star
id|nfsi
op_assign
id|NFS_I
c_func
(paren
id|inode
)paren
suffix:semicolon
r_struct
id|nfs_delegation
op_star
id|delegation
suffix:semicolon
r_int
id|res
op_assign
l_int|0
suffix:semicolon
id|nfs_msync_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
id|down_read
c_func
(paren
op_amp
id|clp-&gt;cl_sem
)paren
suffix:semicolon
multiline_comment|/* Guard against new delegated open calls */
id|down_write
c_func
(paren
op_amp
id|nfsi-&gt;rwsem
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|clp-&gt;cl_lock
)paren
suffix:semicolon
id|delegation
op_assign
id|nfsi-&gt;delegation
suffix:semicolon
r_if
c_cond
(paren
id|delegation
op_ne
l_int|NULL
)paren
(brace
id|list_del_init
c_func
(paren
op_amp
id|delegation-&gt;super_list
)paren
suffix:semicolon
id|nfsi-&gt;delegation
op_assign
l_int|NULL
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|clp-&gt;cl_lock
)paren
suffix:semicolon
id|up_write
c_func
(paren
op_amp
id|nfsi-&gt;rwsem
)paren
suffix:semicolon
id|up_read
c_func
(paren
op_amp
id|clp-&gt;cl_sem
)paren
suffix:semicolon
id|nfs_msync_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|delegation
op_ne
l_int|NULL
)paren
id|res
op_assign
id|nfs_do_return_delegation
c_func
(paren
id|inode
comma
id|delegation
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
multiline_comment|/*&n; * Return all delegations associated to a super block&n; */
DECL|function|nfs_return_all_delegations
r_void
id|nfs_return_all_delegations
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
r_struct
id|nfs4_client
op_star
id|clp
op_assign
id|NFS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|nfs4_state
suffix:semicolon
r_struct
id|nfs_delegation
op_star
id|delegation
suffix:semicolon
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_if
c_cond
(paren
id|clp
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
id|restart
suffix:colon
id|spin_lock
c_func
(paren
op_amp
id|clp-&gt;cl_lock
)paren
suffix:semicolon
id|list_for_each_entry
c_func
(paren
id|delegation
comma
op_amp
id|clp-&gt;cl_delegations
comma
id|super_list
)paren
(brace
r_if
c_cond
(paren
id|delegation-&gt;inode-&gt;i_sb
op_ne
id|sb
)paren
r_continue
suffix:semicolon
id|inode
op_assign
id|igrab
c_func
(paren
id|delegation-&gt;inode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|inode
op_eq
l_int|NULL
)paren
r_continue
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|clp-&gt;cl_lock
)paren
suffix:semicolon
id|nfs_inode_return_delegation
c_func
(paren
id|inode
)paren
suffix:semicolon
id|iput
c_func
(paren
id|inode
)paren
suffix:semicolon
r_goto
id|restart
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|clp-&gt;cl_lock
)paren
suffix:semicolon
)brace
DECL|struct|recall_threadargs
r_struct
id|recall_threadargs
(brace
DECL|member|inode
r_struct
id|inode
op_star
id|inode
suffix:semicolon
DECL|member|clp
r_struct
id|nfs4_client
op_star
id|clp
suffix:semicolon
DECL|member|stateid
r_const
id|nfs4_stateid
op_star
id|stateid
suffix:semicolon
DECL|member|started
r_struct
id|completion
id|started
suffix:semicolon
DECL|member|result
r_int
id|result
suffix:semicolon
)brace
suffix:semicolon
DECL|function|recall_thread
r_static
r_int
id|recall_thread
c_func
(paren
r_void
op_star
id|data
)paren
(brace
r_struct
id|recall_threadargs
op_star
id|args
op_assign
(paren
r_struct
id|recall_threadargs
op_star
)paren
id|data
suffix:semicolon
r_struct
id|inode
op_star
id|inode
op_assign
id|igrab
c_func
(paren
id|args-&gt;inode
)paren
suffix:semicolon
r_struct
id|nfs4_client
op_star
id|clp
op_assign
id|NFS_SERVER
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|nfs4_state
suffix:semicolon
r_struct
id|nfs_inode
op_star
id|nfsi
op_assign
id|NFS_I
c_func
(paren
id|inode
)paren
suffix:semicolon
r_struct
id|nfs_delegation
op_star
id|delegation
suffix:semicolon
id|daemonize
c_func
(paren
l_string|&quot;nfsv4-delegreturn&quot;
)paren
suffix:semicolon
id|nfs_msync_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
id|down_read
c_func
(paren
op_amp
id|clp-&gt;cl_sem
)paren
suffix:semicolon
id|down_write
c_func
(paren
op_amp
id|nfsi-&gt;rwsem
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|clp-&gt;cl_lock
)paren
suffix:semicolon
id|delegation
op_assign
id|nfsi-&gt;delegation
suffix:semicolon
r_if
c_cond
(paren
id|delegation
op_ne
l_int|NULL
op_logical_and
id|memcmp
c_func
(paren
id|delegation-&gt;stateid.data
comma
id|args-&gt;stateid-&gt;data
comma
r_sizeof
(paren
id|delegation-&gt;stateid.data
)paren
)paren
op_eq
l_int|0
)paren
(brace
id|list_del_init
c_func
(paren
op_amp
id|delegation-&gt;super_list
)paren
suffix:semicolon
id|nfsi-&gt;delegation
op_assign
l_int|NULL
suffix:semicolon
id|args-&gt;result
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|delegation
op_assign
l_int|NULL
suffix:semicolon
id|args-&gt;result
op_assign
op_minus
id|ENOENT
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|clp-&gt;cl_lock
)paren
suffix:semicolon
id|complete
c_func
(paren
op_amp
id|args-&gt;started
)paren
suffix:semicolon
id|up_write
c_func
(paren
op_amp
id|nfsi-&gt;rwsem
)paren
suffix:semicolon
id|up_read
c_func
(paren
op_amp
id|clp-&gt;cl_sem
)paren
suffix:semicolon
id|nfs_msync_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|delegation
op_ne
l_int|NULL
)paren
id|nfs_do_return_delegation
c_func
(paren
id|inode
comma
id|delegation
)paren
suffix:semicolon
id|iput
c_func
(paren
id|inode
)paren
suffix:semicolon
id|module_put_and_exit
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Asynchronous delegation recall!&n; */
DECL|function|nfs_async_inode_return_delegation
r_int
id|nfs_async_inode_return_delegation
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_const
id|nfs4_stateid
op_star
id|stateid
)paren
(brace
r_struct
id|recall_threadargs
id|data
op_assign
(brace
dot
id|inode
op_assign
id|inode
comma
dot
id|stateid
op_assign
id|stateid
comma
)brace
suffix:semicolon
r_int
id|status
suffix:semicolon
id|init_completion
c_func
(paren
op_amp
id|data.started
)paren
suffix:semicolon
id|__module_get
c_func
(paren
id|THIS_MODULE
)paren
suffix:semicolon
id|status
op_assign
id|kernel_thread
c_func
(paren
id|recall_thread
comma
op_amp
id|data
comma
id|CLONE_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
OL
l_int|0
)paren
r_goto
id|out_module_put
suffix:semicolon
id|wait_for_completion
c_func
(paren
op_amp
id|data.started
)paren
suffix:semicolon
r_return
id|data.result
suffix:semicolon
id|out_module_put
suffix:colon
id|module_put
c_func
(paren
id|THIS_MODULE
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
multiline_comment|/*&n; * Retrieve the inode associated with a delegation&n; */
DECL|function|nfs_delegation_find_inode
r_struct
id|inode
op_star
id|nfs_delegation_find_inode
c_func
(paren
r_struct
id|nfs4_client
op_star
id|clp
comma
r_const
r_struct
id|nfs_fh
op_star
id|fhandle
)paren
(brace
r_struct
id|nfs_delegation
op_star
id|delegation
suffix:semicolon
r_struct
id|inode
op_star
id|res
op_assign
l_int|NULL
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|clp-&gt;cl_lock
)paren
suffix:semicolon
id|list_for_each_entry
c_func
(paren
id|delegation
comma
op_amp
id|clp-&gt;cl_delegations
comma
id|super_list
)paren
(brace
r_if
c_cond
(paren
id|nfs_compare_fh
c_func
(paren
id|fhandle
comma
op_amp
id|NFS_I
c_func
(paren
id|delegation-&gt;inode
)paren
op_member_access_from_pointer
id|fh
)paren
op_eq
l_int|0
)paren
(brace
id|res
op_assign
id|igrab
c_func
(paren
id|delegation-&gt;inode
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|spin_unlock
c_func
(paren
op_amp
id|clp-&gt;cl_lock
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
eof
