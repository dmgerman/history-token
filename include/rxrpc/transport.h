multiline_comment|/* transport.h: Rx transport management&n; *&n; * Copyright (C) 2002 Red Hat, Inc. All Rights Reserved.&n; * Written by David Howells (dhowells@redhat.com)&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _LINUX_RXRPC_TRANSPORT_H
DECL|macro|_LINUX_RXRPC_TRANSPORT_H
mdefine_line|#define _LINUX_RXRPC_TRANSPORT_H
macro_line|#include &lt;rxrpc/types.h&gt;
macro_line|#include &lt;rxrpc/krxiod.h&gt;
macro_line|#include &lt;rxrpc/rxrpc.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/rwsem.h&gt;
DECL|typedef|rxrpc_newcall_fnx_t
r_typedef
r_int
(paren
op_star
id|rxrpc_newcall_fnx_t
)paren
(paren
r_struct
id|rxrpc_call
op_star
id|call
)paren
suffix:semicolon
r_extern
id|wait_queue_head_t
id|rxrpc_krxiod_wq
suffix:semicolon
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * Rx operation specification&n; * - tables of these must be sorted by op ID so that they can be binary-chop searched&n; */
DECL|struct|rxrpc_operation
r_struct
id|rxrpc_operation
(brace
DECL|member|id
r_int
id|id
suffix:semicolon
multiline_comment|/* operation ID */
DECL|member|asize
r_int
id|asize
suffix:semicolon
multiline_comment|/* minimum size of argument block */
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
multiline_comment|/* name of operation */
DECL|member|user
r_void
op_star
id|user
suffix:semicolon
multiline_comment|/* initial user data */
)brace
suffix:semicolon
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * Rx transport service record&n; */
DECL|struct|rxrpc_service
r_struct
id|rxrpc_service
(brace
DECL|member|link
r_struct
id|list_head
id|link
suffix:semicolon
multiline_comment|/* link in services list on transport */
DECL|member|owner
r_struct
id|module
op_star
id|owner
suffix:semicolon
multiline_comment|/* owner module */
DECL|member|new_call
id|rxrpc_newcall_fnx_t
id|new_call
suffix:semicolon
multiline_comment|/* new call handler function */
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
multiline_comment|/* name of service */
DECL|member|service_id
r_int
r_int
id|service_id
suffix:semicolon
multiline_comment|/* Rx service ID */
DECL|member|attn_func
id|rxrpc_call_attn_func_t
id|attn_func
suffix:semicolon
multiline_comment|/* call requires attention callback */
DECL|member|error_func
id|rxrpc_call_error_func_t
id|error_func
suffix:semicolon
multiline_comment|/* call error callback */
DECL|member|aemap_func
id|rxrpc_call_aemap_func_t
id|aemap_func
suffix:semicolon
multiline_comment|/* abort -&gt; errno mapping callback */
DECL|member|ops_begin
r_const
r_struct
id|rxrpc_operation
op_star
id|ops_begin
suffix:semicolon
multiline_comment|/* beginning of operations table */
DECL|member|ops_end
r_const
r_struct
id|rxrpc_operation
op_star
id|ops_end
suffix:semicolon
multiline_comment|/* end of operations table */
)brace
suffix:semicolon
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * Rx transport endpoint record&n; */
DECL|struct|rxrpc_transport
r_struct
id|rxrpc_transport
(brace
DECL|member|usage
id|atomic_t
id|usage
suffix:semicolon
DECL|member|socket
r_struct
id|socket
op_star
id|socket
suffix:semicolon
multiline_comment|/* my UDP socket */
DECL|member|services
r_struct
id|list_head
id|services
suffix:semicolon
multiline_comment|/* services listening on this socket */
DECL|member|link
r_struct
id|list_head
id|link
suffix:semicolon
multiline_comment|/* link in transport list */
DECL|member|proc_link
r_struct
id|list_head
id|proc_link
suffix:semicolon
multiline_comment|/* link in transport proc list */
DECL|member|krxiodq_link
r_struct
id|list_head
id|krxiodq_link
suffix:semicolon
multiline_comment|/* krxiod attention queue link */
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
multiline_comment|/* access lock */
DECL|member|peer_active
r_struct
id|list_head
id|peer_active
suffix:semicolon
multiline_comment|/* active peers connected to over this socket */
DECL|member|peer_graveyard
r_struct
id|list_head
id|peer_graveyard
suffix:semicolon
multiline_comment|/* inactive peer list */
DECL|member|peer_gylock
id|spinlock_t
id|peer_gylock
suffix:semicolon
multiline_comment|/* peer graveyard lock */
DECL|member|peer_gy_waitq
id|wait_queue_head_t
id|peer_gy_waitq
suffix:semicolon
multiline_comment|/* wait queue hit when peer graveyard is empty */
DECL|member|peer_lock
id|rwlock_t
id|peer_lock
suffix:semicolon
multiline_comment|/* peer list access lock */
DECL|member|peer_count
id|atomic_t
id|peer_count
suffix:semicolon
multiline_comment|/* number of peers */
DECL|member|peer_ops
r_struct
id|rxrpc_peer_ops
op_star
id|peer_ops
suffix:semicolon
multiline_comment|/* default peer operations */
DECL|member|port
r_int
r_int
id|port
suffix:semicolon
multiline_comment|/* port upon which listening */
DECL|member|error_rcvd
r_volatile
r_char
id|error_rcvd
suffix:semicolon
multiline_comment|/* T if received ICMP error outstanding */
)brace
suffix:semicolon
r_extern
r_int
id|rxrpc_create_transport
c_func
(paren
r_int
r_int
id|port
comma
r_struct
id|rxrpc_transport
op_star
op_star
id|_trans
)paren
suffix:semicolon
DECL|function|rxrpc_get_transport
r_static
r_inline
r_void
id|rxrpc_get_transport
c_func
(paren
r_struct
id|rxrpc_transport
op_star
id|trans
)paren
(brace
id|BUG_ON
c_func
(paren
id|atomic_read
c_func
(paren
op_amp
id|trans-&gt;usage
)paren
op_le
l_int|0
)paren
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|trans-&gt;usage
)paren
suffix:semicolon
singleline_comment|//printk(&quot;rxrpc_get_transport(%p{u=%d})&bslash;n&quot;,
singleline_comment|//       trans, atomic_read(&amp;trans-&gt;usage));
)brace
r_extern
r_void
id|rxrpc_put_transport
c_func
(paren
r_struct
id|rxrpc_transport
op_star
id|trans
)paren
suffix:semicolon
r_extern
r_int
id|rxrpc_add_service
c_func
(paren
r_struct
id|rxrpc_transport
op_star
id|trans
comma
r_struct
id|rxrpc_service
op_star
id|srv
)paren
suffix:semicolon
r_extern
r_void
id|rxrpc_del_service
c_func
(paren
r_struct
id|rxrpc_transport
op_star
id|trans
comma
r_struct
id|rxrpc_service
op_star
id|srv
)paren
suffix:semicolon
r_extern
r_void
id|rxrpc_trans_receive_packet
c_func
(paren
r_struct
id|rxrpc_transport
op_star
id|trans
)paren
suffix:semicolon
r_extern
r_int
id|rxrpc_trans_immediate_abort
c_func
(paren
r_struct
id|rxrpc_transport
op_star
id|trans
comma
r_struct
id|rxrpc_message
op_star
id|msg
comma
r_int
id|error
)paren
suffix:semicolon
macro_line|#endif /* _LINUX_RXRPC_TRANSPORT_H */
eof
