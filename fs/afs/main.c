multiline_comment|/* main.c: AFS client file system&n; *&n; * Copyright (C) 2002 Red Hat, Inc. All Rights Reserved.&n; * Written by David Howells (dhowells@redhat.com)&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/moduleparam.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/completion.h&gt;
macro_line|#include &lt;rxrpc/rxrpc.h&gt;
macro_line|#include &lt;rxrpc/transport.h&gt;
macro_line|#include &lt;rxrpc/call.h&gt;
macro_line|#include &lt;rxrpc/peer.h&gt;
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;cell.h&quot;
macro_line|#include &quot;server.h&quot;
macro_line|#include &quot;fsclient.h&quot;
macro_line|#include &quot;cmservice.h&quot;
macro_line|#include &quot;kafstimod.h&quot;
macro_line|#include &quot;kafsasyncd.h&quot;
macro_line|#include &quot;internal.h&quot;
DECL|variable|afs_transport
r_struct
id|rxrpc_transport
op_star
id|afs_transport
suffix:semicolon
r_static
r_int
id|afs_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_void
id|afs_exit
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_int
id|afs_adding_peer
c_func
(paren
r_struct
id|rxrpc_peer
op_star
id|peer
)paren
suffix:semicolon
r_static
r_void
id|afs_discarding_peer
c_func
(paren
r_struct
id|rxrpc_peer
op_star
id|peer
)paren
suffix:semicolon
multiline_comment|/* XXX late_initcall is kludgy, but the only alternative seems to create&n; * a transport upon the first mount, which is worse. Or is it?&n; */
multiline_comment|/* module_init(afs_init); */
DECL|variable|afs_init
id|late_initcall
c_func
(paren
id|afs_init
)paren
suffix:semicolon
multiline_comment|/* must be called after net/ to create socket */
DECL|variable|afs_exit
id|module_exit
c_func
(paren
id|afs_exit
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;AFS Client File System&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Red Hat, Inc.&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|rootcell
r_static
r_char
op_star
id|rootcell
suffix:semicolon
id|module_param
c_func
(paren
id|rootcell
comma
id|charp
comma
l_int|0
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|rootcell
comma
l_string|&quot;root AFS cell name and VL server IP addr list&quot;
)paren
suffix:semicolon
DECL|variable|afs_peer_ops
r_static
r_struct
id|rxrpc_peer_ops
id|afs_peer_ops
op_assign
(brace
dot
id|adding
op_assign
id|afs_adding_peer
comma
dot
id|discarding
op_assign
id|afs_discarding_peer
comma
)brace
suffix:semicolon
DECL|variable|afs_cb_hash_tbl
r_struct
id|list_head
id|afs_cb_hash_tbl
(braket
id|AFS_CB_HASH_COUNT
)braket
suffix:semicolon
DECL|variable|afs_cb_hash_lock
id|spinlock_t
id|afs_cb_hash_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
macro_line|#ifdef AFS_CACHING_SUPPORT
DECL|variable|afs_cache_ops
r_static
r_struct
id|cachefs_netfs_operations
id|afs_cache_ops
op_assign
(brace
dot
id|get_page_cookie
op_assign
id|afs_cache_get_page_cookie
comma
)brace
suffix:semicolon
DECL|variable|afs_cache_netfs
r_struct
id|cachefs_netfs
id|afs_cache_netfs
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;afs&quot;
comma
dot
id|version
op_assign
l_int|0
comma
dot
id|ops
op_assign
op_amp
id|afs_cache_ops
comma
)brace
suffix:semicolon
macro_line|#endif
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * initialise the AFS client FS module&n; */
DECL|function|afs_init
r_static
r_int
id|afs_init
c_func
(paren
r_void
)paren
(brace
r_int
id|loop
comma
id|ret
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;kAFS: Red Hat AFS client v0.1 registering.&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* initialise the callback hash table */
id|spin_lock_init
c_func
(paren
op_amp
id|afs_cb_hash_lock
)paren
suffix:semicolon
r_for
c_loop
(paren
id|loop
op_assign
id|AFS_CB_HASH_COUNT
op_minus
l_int|1
suffix:semicolon
id|loop
op_ge
l_int|0
suffix:semicolon
id|loop
op_decrement
)paren
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|afs_cb_hash_tbl
(braket
id|loop
)braket
)paren
suffix:semicolon
multiline_comment|/* register the /proc stuff */
id|ret
op_assign
id|afs_proc_init
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
r_return
id|ret
suffix:semicolon
macro_line|#ifdef AFS_CACHING_SUPPORT
multiline_comment|/* we want to be able to cache */
id|ret
op_assign
id|cachefs_register_netfs
c_func
(paren
op_amp
id|afs_cache_netfs
comma
op_amp
id|afs_cache_cell_index_def
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
r_goto
id|error
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_KEYS
id|ret
op_assign
id|afs_key_register
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
r_goto
id|error_cache
suffix:semicolon
macro_line|#endif
multiline_comment|/* initialise the cell DB */
id|ret
op_assign
id|afs_cell_init
c_func
(paren
id|rootcell
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
r_goto
id|error_keys
suffix:semicolon
multiline_comment|/* start the timeout daemon */
id|ret
op_assign
id|afs_kafstimod_start
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
r_goto
id|error_keys
suffix:semicolon
multiline_comment|/* start the async operation daemon */
id|ret
op_assign
id|afs_kafsasyncd_start
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
r_goto
id|error_kafstimod
suffix:semicolon
multiline_comment|/* create the RxRPC transport */
id|ret
op_assign
id|rxrpc_create_transport
c_func
(paren
l_int|7001
comma
op_amp
id|afs_transport
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
r_goto
id|error_kafsasyncd
suffix:semicolon
id|afs_transport-&gt;peer_ops
op_assign
op_amp
id|afs_peer_ops
suffix:semicolon
multiline_comment|/* register the filesystems */
id|ret
op_assign
id|afs_fs_init
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
r_goto
id|error_transport
suffix:semicolon
r_return
id|ret
suffix:semicolon
id|error_transport
suffix:colon
id|rxrpc_put_transport
c_func
(paren
id|afs_transport
)paren
suffix:semicolon
id|error_kafsasyncd
suffix:colon
id|afs_kafsasyncd_stop
c_func
(paren
)paren
suffix:semicolon
id|error_kafstimod
suffix:colon
id|afs_kafstimod_stop
c_func
(paren
)paren
suffix:semicolon
id|error_keys
suffix:colon
macro_line|#ifdef CONFIG_KEYS
id|afs_key_unregister
c_func
(paren
)paren
suffix:semicolon
id|error_cache
suffix:colon
macro_line|#endif
macro_line|#ifdef AFS_CACHING_SUPPORT
id|cachefs_unregister_netfs
c_func
(paren
op_amp
id|afs_cache_netfs
)paren
suffix:semicolon
id|error
suffix:colon
macro_line|#endif
id|afs_cell_purge
c_func
(paren
)paren
suffix:semicolon
id|afs_proc_cleanup
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;kAFS: failed to register: %d&bslash;n&quot;
comma
id|ret
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/* end afs_init() */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * clean up on module removal&n; */
DECL|function|afs_exit
r_static
r_void
id|__exit
id|afs_exit
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;kAFS: Red Hat AFS client v0.1 unregistering.&bslash;n&quot;
)paren
suffix:semicolon
id|afs_fs_exit
c_func
(paren
)paren
suffix:semicolon
id|rxrpc_put_transport
c_func
(paren
id|afs_transport
)paren
suffix:semicolon
id|afs_kafstimod_stop
c_func
(paren
)paren
suffix:semicolon
id|afs_kafsasyncd_stop
c_func
(paren
)paren
suffix:semicolon
id|afs_cell_purge
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_KEYS
id|afs_key_unregister
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef AFS_CACHING_SUPPORT
id|cachefs_unregister_netfs
c_func
(paren
op_amp
id|afs_cache_netfs
)paren
suffix:semicolon
macro_line|#endif
id|afs_proc_cleanup
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* end afs_exit() */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * notification that new peer record is being added&n; * - called from krxsecd&n; * - return an error to induce an abort&n; * - mustn&squot;t sleep (caller holds an rwlock)&n; */
DECL|function|afs_adding_peer
r_static
r_int
id|afs_adding_peer
c_func
(paren
r_struct
id|rxrpc_peer
op_star
id|peer
)paren
(brace
r_struct
id|afs_server
op_star
id|server
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|_debug
c_func
(paren
l_string|&quot;kAFS: Adding new peer %08x&bslash;n&quot;
comma
id|ntohl
c_func
(paren
id|peer-&gt;addr.s_addr
)paren
)paren
suffix:semicolon
multiline_comment|/* determine which server the peer resides in (if any) */
id|ret
op_assign
id|afs_server_find_by_peer
c_func
(paren
id|peer
comma
op_amp
id|server
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
r_return
id|ret
suffix:semicolon
multiline_comment|/* none that we recognise, so abort */
id|_debug
c_func
(paren
l_string|&quot;Server %p{u=%d}&bslash;n&quot;
comma
id|server
comma
id|atomic_read
c_func
(paren
op_amp
id|server-&gt;usage
)paren
)paren
suffix:semicolon
id|_debug
c_func
(paren
l_string|&quot;Cell %p{u=%d}&bslash;n&quot;
comma
id|server-&gt;cell
comma
id|atomic_read
c_func
(paren
op_amp
id|server-&gt;cell-&gt;usage
)paren
)paren
suffix:semicolon
multiline_comment|/* cross-point the structs under a global lock */
id|spin_lock
c_func
(paren
op_amp
id|afs_server_peer_lock
)paren
suffix:semicolon
id|peer-&gt;user
op_assign
id|server
suffix:semicolon
id|server-&gt;peer
op_assign
id|peer
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|afs_server_peer_lock
)paren
suffix:semicolon
id|afs_put_server
c_func
(paren
id|server
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* end afs_adding_peer() */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * notification that a peer record is being discarded&n; * - called from krxiod or krxsecd&n; */
DECL|function|afs_discarding_peer
r_static
r_void
id|afs_discarding_peer
c_func
(paren
r_struct
id|rxrpc_peer
op_star
id|peer
)paren
(brace
r_struct
id|afs_server
op_star
id|server
suffix:semicolon
id|_enter
c_func
(paren
l_string|&quot;%p&quot;
comma
id|peer
)paren
suffix:semicolon
id|_debug
c_func
(paren
l_string|&quot;Discarding peer %08x (rtt=%lu.%lumS)&bslash;n&quot;
comma
id|ntohl
c_func
(paren
id|peer-&gt;addr.s_addr
)paren
comma
(paren
r_int
)paren
(paren
id|peer-&gt;rtt
op_div
l_int|1000
)paren
comma
(paren
r_int
)paren
(paren
id|peer-&gt;rtt
op_mod
l_int|1000
)paren
)paren
suffix:semicolon
multiline_comment|/* uncross-point the structs under a global lock */
id|spin_lock
c_func
(paren
op_amp
id|afs_server_peer_lock
)paren
suffix:semicolon
id|server
op_assign
id|peer-&gt;user
suffix:semicolon
r_if
c_cond
(paren
id|server
)paren
(brace
id|peer-&gt;user
op_assign
l_int|NULL
suffix:semicolon
id|server-&gt;peer
op_assign
l_int|NULL
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|afs_server_peer_lock
)paren
suffix:semicolon
id|_leave
c_func
(paren
l_string|&quot;&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* end afs_discarding_peer() */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * clear the dead space between task_struct and kernel stack&n; * - called by supplying -finstrument-functions to gcc&n; */
macro_line|#if 0
r_void
id|__cyg_profile_func_enter
(paren
r_void
op_star
id|this_fn
comma
r_void
op_star
id|call_site
)paren
id|__attribute__
c_func
(paren
(paren
id|no_instrument_function
)paren
)paren
suffix:semicolon
r_void
id|__cyg_profile_func_enter
(paren
r_void
op_star
id|this_fn
comma
r_void
op_star
id|call_site
)paren
(brace
id|asm
r_volatile
(paren
l_string|&quot;  movl    %%esp,%%edi     &bslash;n&quot;
l_string|&quot;  andl    %0,%%edi        &bslash;n&quot;
l_string|&quot;  addl    %1,%%edi        &bslash;n&quot;
l_string|&quot;  movl    %%esp,%%ecx     &bslash;n&quot;
l_string|&quot;  subl    %%edi,%%ecx     &bslash;n&quot;
l_string|&quot;  shrl    $2,%%ecx        &bslash;n&quot;
l_string|&quot;  movl    $0xedededed,%%eax     &bslash;n&quot;
l_string|&quot;  rep stosl               &bslash;n&quot;
suffix:colon
suffix:colon
l_string|&quot;i&quot;
(paren
op_complement
(paren
id|THREAD_SIZE
op_minus
l_int|1
)paren
)paren
comma
l_string|&quot;i&quot;
(paren
r_sizeof
(paren
r_struct
id|thread_info
)paren
)paren
suffix:colon
l_string|&quot;eax&quot;
comma
l_string|&quot;ecx&quot;
comma
l_string|&quot;edi&quot;
comma
l_string|&quot;memory&quot;
comma
l_string|&quot;cc&quot;
)paren
suffix:semicolon
)brace
r_void
id|__cyg_profile_func_exit
c_func
(paren
r_void
op_star
id|this_fn
comma
r_void
op_star
id|call_site
)paren
id|__attribute__
c_func
(paren
(paren
id|no_instrument_function
)paren
)paren
suffix:semicolon
r_void
id|__cyg_profile_func_exit
c_func
(paren
r_void
op_star
id|this_fn
comma
r_void
op_star
id|call_site
)paren
(brace
id|asm
r_volatile
(paren
l_string|&quot;  movl    %%esp,%%edi     &bslash;n&quot;
l_string|&quot;  andl    %0,%%edi        &bslash;n&quot;
l_string|&quot;  addl    %1,%%edi        &bslash;n&quot;
l_string|&quot;  movl    %%esp,%%ecx     &bslash;n&quot;
l_string|&quot;  subl    %%edi,%%ecx     &bslash;n&quot;
l_string|&quot;  shrl    $2,%%ecx        &bslash;n&quot;
l_string|&quot;  movl    $0xdadadada,%%eax     &bslash;n&quot;
l_string|&quot;  rep stosl               &bslash;n&quot;
suffix:colon
suffix:colon
l_string|&quot;i&quot;
(paren
op_complement
(paren
id|THREAD_SIZE
op_minus
l_int|1
)paren
)paren
comma
l_string|&quot;i&quot;
(paren
r_sizeof
(paren
r_struct
id|thread_info
)paren
)paren
suffix:colon
l_string|&quot;eax&quot;
comma
l_string|&quot;ecx&quot;
comma
l_string|&quot;edi&quot;
comma
l_string|&quot;memory&quot;
comma
l_string|&quot;cc&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
