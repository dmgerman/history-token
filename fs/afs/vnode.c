multiline_comment|/* vnode.c: AFS vnode management&n; *&n; * Copyright (C) 2002 Red Hat, Inc. All Rights Reserved.&n; * Written by David Howells (dhowells@redhat.com)&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &quot;volume.h&quot;
macro_line|#include &quot;cell.h&quot;
macro_line|#include &quot;cmservice.h&quot;
macro_line|#include &quot;fsclient.h&quot;
macro_line|#include &quot;vlclient.h&quot;
macro_line|#include &quot;vnode.h&quot;
macro_line|#include &quot;internal.h&quot;
r_static
r_void
id|afs_vnode_cb_timed_out
c_func
(paren
r_struct
id|afs_timer
op_star
id|timer
)paren
suffix:semicolon
DECL|variable|afs_vnode_cb_timed_out_ops
r_struct
id|afs_timer_ops
id|afs_vnode_cb_timed_out_ops
op_assign
(brace
dot
id|timed_out
op_assign
id|afs_vnode_cb_timed_out
comma
)brace
suffix:semicolon
macro_line|#ifdef AFS_CACHING_SUPPORT
r_static
id|cachefs_match_val_t
id|afs_vnode_cache_match
c_func
(paren
r_void
op_star
id|target
comma
r_const
r_void
op_star
id|entry
)paren
suffix:semicolon
r_static
r_void
id|afs_vnode_cache_update
c_func
(paren
r_void
op_star
id|source
comma
r_void
op_star
id|entry
)paren
suffix:semicolon
DECL|variable|afs_vnode_cache_index_def
r_struct
id|cachefs_index_def
id|afs_vnode_cache_index_def
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;vnode&quot;
comma
dot
id|data_size
op_assign
r_sizeof
(paren
r_struct
id|afs_cache_vnode
)paren
comma
dot
id|keys
(braket
l_int|0
)braket
op_assign
(brace
id|CACHEFS_INDEX_KEYS_BIN
comma
l_int|4
)brace
comma
dot
id|match
op_assign
id|afs_vnode_cache_match
comma
dot
id|update
op_assign
id|afs_vnode_cache_update
comma
)brace
suffix:semicolon
macro_line|#endif
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * handle a callback timing out&n; * TODO: retain a ref to vnode struct for an outstanding callback timeout&n; */
DECL|function|afs_vnode_cb_timed_out
r_static
r_void
id|afs_vnode_cb_timed_out
c_func
(paren
r_struct
id|afs_timer
op_star
id|timer
)paren
(brace
id|afs_server_t
op_star
id|oldserver
suffix:semicolon
id|afs_vnode_t
op_star
id|vnode
suffix:semicolon
id|vnode
op_assign
id|list_entry
c_func
(paren
id|timer
comma
id|afs_vnode_t
comma
id|cb_timeout
)paren
suffix:semicolon
id|_enter
c_func
(paren
l_string|&quot;%p&quot;
comma
id|vnode
)paren
suffix:semicolon
multiline_comment|/* set the changed flag in the vnode and release the server */
id|spin_lock
c_func
(paren
op_amp
id|vnode-&gt;lock
)paren
suffix:semicolon
id|oldserver
op_assign
id|xchg
c_func
(paren
op_amp
id|vnode-&gt;cb_server
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|oldserver
)paren
(brace
id|vnode-&gt;flags
op_or_assign
id|AFS_VNODE_CHANGED
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|afs_cb_hash_lock
)paren
suffix:semicolon
id|list_del_init
c_func
(paren
op_amp
id|vnode-&gt;cb_hash_link
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|afs_cb_hash_lock
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|oldserver-&gt;cb_lock
)paren
suffix:semicolon
id|list_del_init
c_func
(paren
op_amp
id|vnode-&gt;cb_link
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|oldserver-&gt;cb_lock
)paren
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|vnode-&gt;lock
)paren
suffix:semicolon
id|afs_put_server
c_func
(paren
id|oldserver
)paren
suffix:semicolon
id|_leave
c_func
(paren
l_string|&quot;&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* end afs_vnode_cb_timed_out() */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * finish off updating the recorded status of a file&n; * - starts callback expiry timer&n; * - adds to server&squot;s callback list&n; */
DECL|function|afs_vnode_finalise_status_update
r_void
id|afs_vnode_finalise_status_update
c_func
(paren
id|afs_vnode_t
op_star
id|vnode
comma
id|afs_server_t
op_star
id|server
comma
r_int
id|ret
)paren
(brace
id|afs_server_t
op_star
id|oldserver
op_assign
l_int|NULL
suffix:semicolon
id|_enter
c_func
(paren
l_string|&quot;%p,%p,%d&quot;
comma
id|vnode
comma
id|server
comma
id|ret
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|vnode-&gt;lock
)paren
suffix:semicolon
id|vnode-&gt;flags
op_and_assign
op_complement
id|AFS_VNODE_CHANGED
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
l_int|0
)paren
(brace
multiline_comment|/* adjust the callback timeout appropriately */
id|afs_kafstimod_add_timer
c_func
(paren
op_amp
id|vnode-&gt;cb_timeout
comma
id|vnode-&gt;cb_expiry
op_star
id|HZ
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|afs_cb_hash_lock
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|vnode-&gt;cb_hash_link
)paren
suffix:semicolon
id|list_add_tail
c_func
(paren
op_amp
id|vnode-&gt;cb_hash_link
comma
op_amp
id|afs_cb_hash
c_func
(paren
id|server
comma
op_amp
id|vnode-&gt;fid
)paren
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|afs_cb_hash_lock
)paren
suffix:semicolon
multiline_comment|/* swap ref to old callback server with that for new callback server */
id|oldserver
op_assign
id|xchg
c_func
(paren
op_amp
id|vnode-&gt;cb_server
comma
id|server
)paren
suffix:semicolon
r_if
c_cond
(paren
id|oldserver
op_ne
id|server
)paren
(brace
r_if
c_cond
(paren
id|oldserver
)paren
(brace
id|spin_lock
c_func
(paren
op_amp
id|oldserver-&gt;cb_lock
)paren
suffix:semicolon
id|list_del_init
c_func
(paren
op_amp
id|vnode-&gt;cb_link
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|oldserver-&gt;cb_lock
)paren
suffix:semicolon
)brace
id|afs_get_server
c_func
(paren
id|server
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|server-&gt;cb_lock
)paren
suffix:semicolon
id|list_add_tail
c_func
(paren
op_amp
id|vnode-&gt;cb_link
comma
op_amp
id|server-&gt;cb_promises
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|server-&gt;cb_lock
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* same server */
id|oldserver
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|ret
op_eq
op_minus
id|ENOENT
)paren
(brace
multiline_comment|/* the file was deleted - clear the callback timeout */
id|oldserver
op_assign
id|xchg
c_func
(paren
op_amp
id|vnode-&gt;cb_server
comma
l_int|NULL
)paren
suffix:semicolon
id|afs_kafstimod_del_timer
c_func
(paren
op_amp
id|vnode-&gt;cb_timeout
)paren
suffix:semicolon
id|_debug
c_func
(paren
l_string|&quot;got NOENT from server - marking file deleted&quot;
)paren
suffix:semicolon
id|vnode-&gt;flags
op_or_assign
id|AFS_VNODE_DELETED
suffix:semicolon
)brace
id|vnode-&gt;update_cnt
op_decrement
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|vnode-&gt;lock
)paren
suffix:semicolon
id|wake_up_all
c_func
(paren
op_amp
id|vnode-&gt;update_waitq
)paren
suffix:semicolon
id|afs_put_server
c_func
(paren
id|oldserver
)paren
suffix:semicolon
id|_leave
c_func
(paren
l_string|&quot;&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* end afs_vnode_finalise_status_update() */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * fetch file status from the volume&n; * - don&squot;t issue a fetch if:&n; *   - the changed bit is not set and there&squot;s a valid callback&n; *   - there are any outstanding ops that will fetch the status&n; * - TODO implement local caching&n; */
DECL|function|afs_vnode_fetch_status
r_int
id|afs_vnode_fetch_status
c_func
(paren
id|afs_vnode_t
op_star
id|vnode
)paren
(brace
id|afs_server_t
op_star
id|server
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|DECLARE_WAITQUEUE
c_func
(paren
id|myself
comma
id|current
)paren
suffix:semicolon
id|_enter
c_func
(paren
l_string|&quot;%s,{%u,%u,%u}&quot;
comma
id|vnode-&gt;volume-&gt;vlocation-&gt;vldb.name
comma
id|vnode-&gt;fid.vid
comma
id|vnode-&gt;fid.vnode
comma
id|vnode-&gt;fid.unique
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|vnode-&gt;flags
op_amp
id|AFS_VNODE_CHANGED
)paren
op_logical_and
id|vnode-&gt;cb_server
)paren
(brace
id|_leave
c_func
(paren
l_string|&quot; [unchanged]&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|vnode-&gt;flags
op_amp
id|AFS_VNODE_DELETED
)paren
(brace
id|_leave
c_func
(paren
l_string|&quot; [deleted]&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOENT
suffix:semicolon
)brace
id|spin_lock
c_func
(paren
op_amp
id|vnode-&gt;lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|vnode-&gt;flags
op_amp
id|AFS_VNODE_CHANGED
)paren
)paren
(brace
id|spin_unlock
c_func
(paren
op_amp
id|vnode-&gt;lock
)paren
suffix:semicolon
id|_leave
c_func
(paren
l_string|&quot; [unchanged]&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|vnode-&gt;update_cnt
OG
l_int|0
)paren
(brace
multiline_comment|/* someone else started a fetch */
id|set_current_state
c_func
(paren
id|TASK_UNINTERRUPTIBLE
)paren
suffix:semicolon
id|add_wait_queue
c_func
(paren
op_amp
id|vnode-&gt;update_waitq
comma
op_amp
id|myself
)paren
suffix:semicolon
multiline_comment|/* wait for the status to be updated */
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|vnode-&gt;flags
op_amp
id|AFS_VNODE_CHANGED
)paren
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|vnode-&gt;flags
op_amp
id|AFS_VNODE_DELETED
)paren
r_break
suffix:semicolon
multiline_comment|/* it got updated and invalidated all before we saw it */
r_if
c_cond
(paren
id|vnode-&gt;update_cnt
op_eq
l_int|0
)paren
(brace
id|remove_wait_queue
c_func
(paren
op_amp
id|vnode-&gt;update_waitq
comma
op_amp
id|myself
)paren
suffix:semicolon
id|set_current_state
c_func
(paren
id|TASK_RUNNING
)paren
suffix:semicolon
r_goto
id|get_anyway
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|vnode-&gt;lock
)paren
suffix:semicolon
id|schedule
c_func
(paren
)paren
suffix:semicolon
id|set_current_state
c_func
(paren
id|TASK_UNINTERRUPTIBLE
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|vnode-&gt;lock
)paren
suffix:semicolon
)brace
id|remove_wait_queue
c_func
(paren
op_amp
id|vnode-&gt;update_waitq
comma
op_amp
id|myself
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|vnode-&gt;lock
)paren
suffix:semicolon
id|set_current_state
c_func
(paren
id|TASK_RUNNING
)paren
suffix:semicolon
r_return
id|vnode-&gt;flags
op_amp
id|AFS_VNODE_DELETED
ques
c_cond
op_minus
id|ENOENT
suffix:colon
l_int|0
suffix:semicolon
)brace
id|get_anyway
suffix:colon
multiline_comment|/* okay... we&squot;re going to have to initiate the op */
id|vnode-&gt;update_cnt
op_increment
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|vnode-&gt;lock
)paren
suffix:semicolon
multiline_comment|/* merge AFS status fetches and clear outstanding callback on this vnode */
r_do
(brace
multiline_comment|/* pick a server to query */
id|ret
op_assign
id|afs_volume_pick_fileserver
c_func
(paren
id|vnode-&gt;volume
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
id|_debug
c_func
(paren
l_string|&quot;USING SERVER: %08x&bslash;n&quot;
comma
id|ntohl
c_func
(paren
id|server-&gt;addr.s_addr
)paren
)paren
suffix:semicolon
id|ret
op_assign
id|afs_rxfs_fetch_file_status
c_func
(paren
id|server
comma
id|vnode
comma
l_int|NULL
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
op_logical_neg
id|afs_volume_release_fileserver
c_func
(paren
id|vnode-&gt;volume
comma
id|server
comma
id|ret
)paren
)paren
suffix:semicolon
multiline_comment|/* adjust the flags */
id|afs_vnode_finalise_status_update
c_func
(paren
id|vnode
comma
id|server
comma
id|ret
)paren
suffix:semicolon
id|_leave
c_func
(paren
l_string|&quot; = %d&quot;
comma
id|ret
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/* end afs_vnode_fetch_status() */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * fetch file data from the volume&n; * - TODO implement caching and server failover&n; */
DECL|function|afs_vnode_fetch_data
r_int
id|afs_vnode_fetch_data
c_func
(paren
id|afs_vnode_t
op_star
id|vnode
comma
r_struct
id|afs_rxfs_fetch_descriptor
op_star
id|desc
)paren
(brace
id|afs_server_t
op_star
id|server
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|_enter
c_func
(paren
l_string|&quot;%s,{%u,%u,%u}&quot;
comma
id|vnode-&gt;volume-&gt;vlocation-&gt;vldb.name
comma
id|vnode-&gt;fid.vid
comma
id|vnode-&gt;fid.vnode
comma
id|vnode-&gt;fid.unique
)paren
suffix:semicolon
multiline_comment|/* this op will fetch the status */
id|spin_lock
c_func
(paren
op_amp
id|vnode-&gt;lock
)paren
suffix:semicolon
id|vnode-&gt;update_cnt
op_increment
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|vnode-&gt;lock
)paren
suffix:semicolon
multiline_comment|/* merge in AFS status fetches and clear outstanding callback on this vnode */
r_do
(brace
multiline_comment|/* pick a server to query */
id|ret
op_assign
id|afs_volume_pick_fileserver
c_func
(paren
id|vnode-&gt;volume
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
id|_debug
c_func
(paren
l_string|&quot;USING SERVER: %08x&bslash;n&quot;
comma
id|ntohl
c_func
(paren
id|server-&gt;addr.s_addr
)paren
)paren
suffix:semicolon
id|ret
op_assign
id|afs_rxfs_fetch_file_data
c_func
(paren
id|server
comma
id|vnode
comma
id|desc
comma
l_int|NULL
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
op_logical_neg
id|afs_volume_release_fileserver
c_func
(paren
id|vnode-&gt;volume
comma
id|server
comma
id|ret
)paren
)paren
suffix:semicolon
multiline_comment|/* adjust the flags */
id|afs_vnode_finalise_status_update
c_func
(paren
id|vnode
comma
id|server
comma
id|ret
)paren
suffix:semicolon
id|_leave
c_func
(paren
l_string|&quot; = %d&quot;
comma
id|ret
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/* end afs_vnode_fetch_data() */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * break any outstanding callback on a vnode&n; * - only relevent to server that issued it&n; */
DECL|function|afs_vnode_give_up_callback
r_int
id|afs_vnode_give_up_callback
c_func
(paren
id|afs_vnode_t
op_star
id|vnode
)paren
(brace
id|afs_server_t
op_star
id|server
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|_enter
c_func
(paren
l_string|&quot;%s,{%u,%u,%u}&quot;
comma
id|vnode-&gt;volume-&gt;vlocation-&gt;vldb.name
comma
id|vnode-&gt;fid.vid
comma
id|vnode-&gt;fid.vnode
comma
id|vnode-&gt;fid.unique
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|afs_cb_hash_lock
)paren
suffix:semicolon
id|list_del_init
c_func
(paren
op_amp
id|vnode-&gt;cb_hash_link
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|afs_cb_hash_lock
)paren
suffix:semicolon
multiline_comment|/* set the changed flag in the vnode and release the server */
id|spin_lock
c_func
(paren
op_amp
id|vnode-&gt;lock
)paren
suffix:semicolon
id|afs_kafstimod_del_timer
c_func
(paren
op_amp
id|vnode-&gt;cb_timeout
)paren
suffix:semicolon
id|server
op_assign
id|xchg
c_func
(paren
op_amp
id|vnode-&gt;cb_server
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|server
)paren
(brace
id|vnode-&gt;flags
op_or_assign
id|AFS_VNODE_CHANGED
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|server-&gt;cb_lock
)paren
suffix:semicolon
id|list_del_init
c_func
(paren
op_amp
id|vnode-&gt;cb_link
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|server-&gt;cb_lock
)paren
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|vnode-&gt;lock
)paren
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|server
)paren
(brace
id|ret
op_assign
id|afs_rxfs_give_up_callback
c_func
(paren
id|server
comma
id|vnode
)paren
suffix:semicolon
id|afs_put_server
c_func
(paren
id|server
)paren
suffix:semicolon
)brace
id|_leave
c_func
(paren
l_string|&quot; = %d&quot;
comma
id|ret
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/* end afs_vnode_give_up_callback() */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * match a vnode record stored in the cache&n; */
macro_line|#ifdef AFS_CACHING_SUPPORT
DECL|function|afs_vnode_cache_match
r_static
id|cachefs_match_val_t
id|afs_vnode_cache_match
c_func
(paren
r_void
op_star
id|target
comma
r_const
r_void
op_star
id|entry
)paren
(brace
r_const
r_struct
id|afs_cache_vnode
op_star
id|cvnode
op_assign
id|entry
suffix:semicolon
r_struct
id|afs_vnode
op_star
id|vnode
op_assign
id|target
suffix:semicolon
id|_enter
c_func
(paren
l_string|&quot;{%x,%x,%Lx},{%x,%x,%Lx}&quot;
comma
id|vnode-&gt;fid.vnode
comma
id|vnode-&gt;fid.unique
comma
id|vnode-&gt;status.version
comma
id|cvnode-&gt;vnode_id
comma
id|cvnode-&gt;vnode_unique
comma
id|cvnode-&gt;data_version
)paren
suffix:semicolon
r_if
c_cond
(paren
id|vnode-&gt;fid.vnode
op_ne
id|cvnode-&gt;vnode_id
)paren
(brace
id|_leave
c_func
(paren
l_string|&quot; = FAILED&quot;
)paren
suffix:semicolon
r_return
id|CACHEFS_MATCH_FAILED
suffix:semicolon
)brace
r_if
c_cond
(paren
id|vnode-&gt;fid.unique
op_ne
id|cvnode-&gt;vnode_unique
op_logical_or
id|vnode-&gt;status.version
op_ne
id|cvnode-&gt;data_version
)paren
(brace
id|_leave
c_func
(paren
l_string|&quot; = DELETE&quot;
)paren
suffix:semicolon
r_return
id|CACHEFS_MATCH_SUCCESS_DELETE
suffix:semicolon
)brace
id|_leave
c_func
(paren
l_string|&quot; = SUCCESS&quot;
)paren
suffix:semicolon
r_return
id|CACHEFS_MATCH_SUCCESS
suffix:semicolon
)brace
multiline_comment|/* end afs_vnode_cache_match() */
macro_line|#endif
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * update a vnode record stored in the cache&n; */
macro_line|#ifdef AFS_CACHING_SUPPORT
DECL|function|afs_vnode_cache_update
r_static
r_void
id|afs_vnode_cache_update
c_func
(paren
r_void
op_star
id|source
comma
r_void
op_star
id|entry
)paren
(brace
r_struct
id|afs_cache_vnode
op_star
id|cvnode
op_assign
id|entry
suffix:semicolon
r_struct
id|afs_vnode
op_star
id|vnode
op_assign
id|source
suffix:semicolon
id|_enter
c_func
(paren
l_string|&quot;&quot;
)paren
suffix:semicolon
id|cvnode-&gt;vnode_id
op_assign
id|vnode-&gt;fid.vnode
suffix:semicolon
id|cvnode-&gt;vnode_unique
op_assign
id|vnode-&gt;fid.unique
suffix:semicolon
id|cvnode-&gt;data_version
op_assign
id|vnode-&gt;status.version
suffix:semicolon
)brace
multiline_comment|/* end afs_vnode_cache_update() */
macro_line|#endif
eof
