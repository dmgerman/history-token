multiline_comment|/* peer.h: Rx RPC per-transport peer record&n; *&n; * Copyright (C) 2002 Red Hat, Inc. All Rights Reserved.&n; * Written by David Howells (dhowells@redhat.com)&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _LINUX_RXRPC_PEER_H
DECL|macro|_LINUX_RXRPC_PEER_H
mdefine_line|#define _LINUX_RXRPC_PEER_H
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#include &lt;rxrpc/types.h&gt;
macro_line|#include &lt;rxrpc/krxtimod.h&gt;
DECL|struct|rxrpc_peer_ops
r_struct
id|rxrpc_peer_ops
(brace
multiline_comment|/* peer record being added */
DECL|member|adding
r_int
(paren
op_star
id|adding
)paren
(paren
r_struct
id|rxrpc_peer
op_star
id|peer
)paren
suffix:semicolon
multiline_comment|/* peer record being discarded from graveyard */
DECL|member|discarding
r_void
(paren
op_star
id|discarding
)paren
(paren
r_struct
id|rxrpc_peer
op_star
id|peer
)paren
suffix:semicolon
multiline_comment|/* change of epoch detected on connection */
DECL|member|change_of_epoch
r_void
(paren
op_star
id|change_of_epoch
)paren
(paren
r_struct
id|rxrpc_connection
op_star
id|conn
)paren
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * Rx RPC per-transport peer record&n; * - peers only retain a refcount on the transport when they are active&n; * - peers with refcount==0 are inactive and reside in the transport&squot;s graveyard&n; */
DECL|struct|rxrpc_peer
r_struct
id|rxrpc_peer
(brace
DECL|member|usage
id|atomic_t
id|usage
suffix:semicolon
DECL|member|ops
r_struct
id|rxrpc_peer_ops
op_star
id|ops
suffix:semicolon
multiline_comment|/* operations on this peer */
DECL|member|trans
r_struct
id|rxrpc_transport
op_star
id|trans
suffix:semicolon
multiline_comment|/* owner transport */
DECL|member|timeout
r_struct
id|rxrpc_timer
id|timeout
suffix:semicolon
multiline_comment|/* timeout for grave destruction */
DECL|member|link
r_struct
id|list_head
id|link
suffix:semicolon
multiline_comment|/* link in transport&squot;s peer list */
DECL|member|proc_link
r_struct
id|list_head
id|proc_link
suffix:semicolon
multiline_comment|/* link in /proc list */
DECL|member|conn_idlock
id|rwlock_t
id|conn_idlock
suffix:semicolon
multiline_comment|/* lock for connection IDs */
DECL|member|conn_idlist
r_struct
id|list_head
id|conn_idlist
suffix:semicolon
multiline_comment|/* list of connections granted IDs */
DECL|member|conn_idcounter
r_uint32
id|conn_idcounter
suffix:semicolon
multiline_comment|/* connection ID counter */
DECL|member|conn_lock
id|rwlock_t
id|conn_lock
suffix:semicolon
multiline_comment|/* lock for active/dead connections */
DECL|member|conn_active
r_struct
id|list_head
id|conn_active
suffix:semicolon
multiline_comment|/* active connections to/from this peer */
DECL|member|conn_graveyard
r_struct
id|list_head
id|conn_graveyard
suffix:semicolon
multiline_comment|/* graveyard for inactive connections */
DECL|member|conn_gylock
id|spinlock_t
id|conn_gylock
suffix:semicolon
multiline_comment|/* lock for conn_graveyard */
DECL|member|conn_gy_waitq
id|wait_queue_head_t
id|conn_gy_waitq
suffix:semicolon
multiline_comment|/* wait queue hit when graveyard is empty */
DECL|member|conn_count
id|atomic_t
id|conn_count
suffix:semicolon
multiline_comment|/* number of attached connections */
DECL|member|addr
r_struct
id|in_addr
id|addr
suffix:semicolon
multiline_comment|/* remote address */
DECL|member|if_mtu
r_int
id|if_mtu
suffix:semicolon
multiline_comment|/* interface MTU for this peer */
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
multiline_comment|/* access lock */
DECL|member|user
r_void
op_star
id|user
suffix:semicolon
multiline_comment|/* application layer data */
multiline_comment|/* calculated RTT cache */
DECL|macro|RXRPC_RTT_CACHE_SIZE
mdefine_line|#define RXRPC_RTT_CACHE_SIZE 32
DECL|member|rtt
id|suseconds_t
id|rtt
suffix:semicolon
multiline_comment|/* current RTT estimate (in uS) */
DECL|member|rtt_point
r_int
id|rtt_point
suffix:semicolon
multiline_comment|/* next entry at which to insert */
DECL|member|rtt_usage
r_int
id|rtt_usage
suffix:semicolon
multiline_comment|/* amount of cache actually used */
DECL|member|rtt_cache
id|suseconds_t
id|rtt_cache
(braket
id|RXRPC_RTT_CACHE_SIZE
)braket
suffix:semicolon
multiline_comment|/* calculated RTT cache */
)brace
suffix:semicolon
r_extern
r_int
id|rxrpc_peer_lookup
c_func
(paren
r_struct
id|rxrpc_transport
op_star
id|trans
comma
id|__be32
id|addr
comma
r_struct
id|rxrpc_peer
op_star
op_star
id|_peer
)paren
suffix:semicolon
DECL|function|rxrpc_get_peer
r_static
r_inline
r_void
id|rxrpc_get_peer
c_func
(paren
r_struct
id|rxrpc_peer
op_star
id|peer
)paren
(brace
id|BUG_ON
c_func
(paren
id|atomic_read
c_func
(paren
op_amp
id|peer-&gt;usage
)paren
OL
l_int|0
)paren
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|peer-&gt;usage
)paren
suffix:semicolon
singleline_comment|//printk(&quot;rxrpc_get_peer(%p{u=%d})&bslash;n&quot;,peer,atomic_read(&amp;peer-&gt;usage));
)brace
r_extern
r_void
id|rxrpc_put_peer
c_func
(paren
r_struct
id|rxrpc_peer
op_star
id|peer
)paren
suffix:semicolon
macro_line|#endif /* _LINUX_RXRPC_PEER_H */
eof
