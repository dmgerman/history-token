multiline_comment|/* server.h: AFS server record&n; *&n; * Copyright (C) 2002 Red Hat, Inc. All Rights Reserved.&n; * Written by David Howells (dhowells@redhat.com)&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _LINUX_AFS_SERVER_H
DECL|macro|_LINUX_AFS_SERVER_H
mdefine_line|#define _LINUX_AFS_SERVER_H
macro_line|#include &quot;types.h&quot;
macro_line|#include &quot;kafstimod.h&quot;
macro_line|#include &lt;rxrpc/peer.h&gt;
macro_line|#include &lt;linux/rwsem.h&gt;
r_extern
id|spinlock_t
id|afs_server_peer_lock
suffix:semicolon
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * AFS server record&n; */
DECL|struct|afs_server
r_struct
id|afs_server
(brace
DECL|member|usage
id|atomic_t
id|usage
suffix:semicolon
DECL|member|cell
r_struct
id|afs_cell
op_star
id|cell
suffix:semicolon
multiline_comment|/* cell in which server resides */
DECL|member|link
r_struct
id|list_head
id|link
suffix:semicolon
multiline_comment|/* link in cell&squot;s server list */
DECL|member|sem
r_struct
id|rw_semaphore
id|sem
suffix:semicolon
multiline_comment|/* access lock */
DECL|member|timeout
r_struct
id|afs_timer
id|timeout
suffix:semicolon
multiline_comment|/* graveyard timeout */
DECL|member|addr
r_struct
id|in_addr
id|addr
suffix:semicolon
multiline_comment|/* server address */
DECL|member|peer
r_struct
id|rxrpc_peer
op_star
id|peer
suffix:semicolon
multiline_comment|/* peer record for this server */
DECL|member|vlserver
r_struct
id|rxrpc_connection
op_star
id|vlserver
suffix:semicolon
multiline_comment|/* connection to the volume location service */
multiline_comment|/* file service access */
DECL|macro|AFS_SERVER_CONN_LIST_SIZE
mdefine_line|#define AFS_SERVER_CONN_LIST_SIZE 2
DECL|member|fs_conn
r_struct
id|rxrpc_connection
op_star
id|fs_conn
(braket
id|AFS_SERVER_CONN_LIST_SIZE
)braket
suffix:semicolon
multiline_comment|/* FS connections */
DECL|member|fs_conn_cnt
r_int
id|fs_conn_cnt
(braket
id|AFS_SERVER_CONN_LIST_SIZE
)braket
suffix:semicolon
multiline_comment|/* per conn call count */
DECL|member|fs_callq
r_struct
id|list_head
id|fs_callq
suffix:semicolon
multiline_comment|/* queue of processes waiting to make a call */
DECL|member|fs_lock
id|spinlock_t
id|fs_lock
suffix:semicolon
multiline_comment|/* access lock */
DECL|member|fs_state
r_int
id|fs_state
suffix:semicolon
multiline_comment|/* 0 or reason FS currently marked dead (-errno) */
DECL|member|fs_rtt
r_int
id|fs_rtt
suffix:semicolon
multiline_comment|/* FS round trip time */
DECL|member|fs_act_jif
r_int
r_int
id|fs_act_jif
suffix:semicolon
multiline_comment|/* time at which last activity occurred */
DECL|member|fs_dead_jif
r_int
r_int
id|fs_dead_jif
suffix:semicolon
multiline_comment|/* time at which no longer to be considered dead */
multiline_comment|/* callback promise management */
DECL|member|cb_promises
r_struct
id|list_head
id|cb_promises
suffix:semicolon
multiline_comment|/* as yet unbroken promises from this server */
DECL|member|cb_lock
id|spinlock_t
id|cb_lock
suffix:semicolon
multiline_comment|/* access lock */
)brace
suffix:semicolon
r_extern
r_int
id|afs_server_lookup
c_func
(paren
r_struct
id|afs_cell
op_star
id|cell
comma
r_const
r_struct
id|in_addr
op_star
id|addr
comma
r_struct
id|afs_server
op_star
op_star
id|_server
)paren
suffix:semicolon
DECL|macro|afs_get_server
mdefine_line|#define afs_get_server(S) do { atomic_inc(&amp;(S)-&gt;usage); } while(0)
r_extern
r_void
id|afs_put_server
c_func
(paren
r_struct
id|afs_server
op_star
id|server
)paren
suffix:semicolon
r_extern
r_void
id|afs_server_do_timeout
c_func
(paren
r_struct
id|afs_server
op_star
id|server
)paren
suffix:semicolon
r_extern
r_int
id|afs_server_find_by_peer
c_func
(paren
r_const
r_struct
id|rxrpc_peer
op_star
id|peer
comma
r_struct
id|afs_server
op_star
op_star
id|_server
)paren
suffix:semicolon
r_extern
r_int
id|afs_server_get_vlconn
c_func
(paren
r_struct
id|afs_server
op_star
id|server
comma
r_struct
id|rxrpc_connection
op_star
op_star
id|_conn
)paren
suffix:semicolon
r_static
r_inline
DECL|function|afs_server_get_from_peer
r_struct
id|afs_server
op_star
id|afs_server_get_from_peer
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
id|afs_get_server
c_func
(paren
id|server
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|afs_server_peer_lock
)paren
suffix:semicolon
r_return
id|server
suffix:semicolon
)brace
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * AFS server callslot grant record&n; */
DECL|struct|afs_server_callslot
r_struct
id|afs_server_callslot
(brace
DECL|member|link
r_struct
id|list_head
id|link
suffix:semicolon
multiline_comment|/* link in server&squot;s list */
DECL|member|task
r_struct
id|task_struct
op_star
id|task
suffix:semicolon
multiline_comment|/* process waiting to make call */
DECL|member|conn
r_struct
id|rxrpc_connection
op_star
id|conn
suffix:semicolon
multiline_comment|/* connection to use (or NULL on error) */
DECL|member|nconn
r_int
id|nconn
suffix:semicolon
multiline_comment|/* connection slot number (-1 on error) */
DECL|member|ready
r_char
id|ready
suffix:semicolon
multiline_comment|/* T when ready */
DECL|member|errno
r_int
id|errno
suffix:semicolon
multiline_comment|/* error number if nconn==-1 */
)brace
suffix:semicolon
r_extern
r_int
id|afs_server_request_callslot
c_func
(paren
r_struct
id|afs_server
op_star
id|server
comma
r_struct
id|afs_server_callslot
op_star
id|callslot
)paren
suffix:semicolon
r_extern
r_void
id|afs_server_release_callslot
c_func
(paren
r_struct
id|afs_server
op_star
id|server
comma
r_struct
id|afs_server_callslot
op_star
id|callslot
)paren
suffix:semicolon
macro_line|#endif /* _LINUX_AFS_SERVER_H */
eof
