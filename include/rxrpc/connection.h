multiline_comment|/* connection.h: Rx connection record&n; *&n; * Copyright (C) 2002 Red Hat, Inc. All Rights Reserved.&n; * Written by David Howells (dhowells@redhat.com)&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _LINUX_RXRPC_CONNECTION_H
DECL|macro|_LINUX_RXRPC_CONNECTION_H
mdefine_line|#define _LINUX_RXRPC_CONNECTION_H
macro_line|#include &lt;rxrpc/types.h&gt;
macro_line|#include &lt;rxrpc/krxtimod.h&gt;
r_struct
id|sk_buff
suffix:semicolon
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * Rx connection&n; * - connections are matched by (rmt_port,rmt_addr,service_id,conn_id,clientflag)&n; * - connections only retain a refcount on the peer when they are active&n; * - connections with refcount==0 are inactive and reside in the peer&squot;s graveyard&n; */
DECL|struct|rxrpc_connection
r_struct
id|rxrpc_connection
(brace
DECL|member|usage
id|atomic_t
id|usage
suffix:semicolon
DECL|member|trans
r_struct
id|rxrpc_transport
op_star
id|trans
suffix:semicolon
multiline_comment|/* transport endpoint */
DECL|member|peer
r_struct
id|rxrpc_peer
op_star
id|peer
suffix:semicolon
multiline_comment|/* peer from/to which connected */
DECL|member|service
r_struct
id|rxrpc_service
op_star
id|service
suffix:semicolon
multiline_comment|/* responsible service (inbound conns) */
DECL|member|timeout
r_struct
id|rxrpc_timer
id|timeout
suffix:semicolon
multiline_comment|/* decaching timer */
DECL|member|link
r_struct
id|list_head
id|link
suffix:semicolon
multiline_comment|/* link in peer&squot;s list */
DECL|member|proc_link
r_struct
id|list_head
id|proc_link
suffix:semicolon
multiline_comment|/* link in proc list */
DECL|member|err_link
r_struct
id|list_head
id|err_link
suffix:semicolon
multiline_comment|/* link in ICMP error processing list */
DECL|member|id_link
r_struct
id|list_head
id|id_link
suffix:semicolon
multiline_comment|/* link in ID grant list */
DECL|member|addr
r_struct
id|sockaddr_in
id|addr
suffix:semicolon
multiline_comment|/* remote address */
DECL|member|channels
r_struct
id|rxrpc_call
op_star
id|channels
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* channels (active calls) */
DECL|member|chanwait
id|wait_queue_head_t
id|chanwait
suffix:semicolon
multiline_comment|/* wait for channel to become available */
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
multiline_comment|/* access lock */
DECL|member|atime
r_struct
id|timeval
id|atime
suffix:semicolon
multiline_comment|/* last access time */
DECL|member|mtu_size
r_int
id|mtu_size
suffix:semicolon
multiline_comment|/* MTU size for outbound messages */
DECL|member|call_counter
r_int
id|call_counter
suffix:semicolon
multiline_comment|/* call ID counter */
DECL|member|serial_counter
id|rxrpc_serial_t
id|serial_counter
suffix:semicolon
multiline_comment|/* packet serial number counter */
multiline_comment|/* the following should all be in net order */
DECL|member|in_epoch
id|__be32
id|in_epoch
suffix:semicolon
multiline_comment|/* peer&squot;s epoch */
DECL|member|out_epoch
id|__be32
id|out_epoch
suffix:semicolon
multiline_comment|/* my epoch */
DECL|member|conn_id
id|__be32
id|conn_id
suffix:semicolon
multiline_comment|/* connection ID, appropriately shifted */
DECL|member|service_id
id|__be16
id|service_id
suffix:semicolon
multiline_comment|/* service ID */
DECL|member|security_ix
r_uint8
id|security_ix
suffix:semicolon
multiline_comment|/* security ID */
DECL|member|in_clientflag
r_uint8
id|in_clientflag
suffix:semicolon
multiline_comment|/* RXRPC_CLIENT_INITIATED if we are server */
DECL|member|out_clientflag
r_uint8
id|out_clientflag
suffix:semicolon
multiline_comment|/* RXRPC_CLIENT_INITIATED if we are client */
)brace
suffix:semicolon
r_extern
r_int
id|rxrpc_create_connection
c_func
(paren
r_struct
id|rxrpc_transport
op_star
id|trans
comma
id|__be16
id|port
comma
id|__be32
id|addr
comma
r_uint16
id|service_id
comma
r_void
op_star
id|security
comma
r_struct
id|rxrpc_connection
op_star
op_star
id|_conn
)paren
suffix:semicolon
r_extern
r_int
id|rxrpc_connection_lookup
c_func
(paren
r_struct
id|rxrpc_peer
op_star
id|peer
comma
r_struct
id|rxrpc_message
op_star
id|msg
comma
r_struct
id|rxrpc_connection
op_star
op_star
id|_conn
)paren
suffix:semicolon
DECL|function|rxrpc_get_connection
r_static
r_inline
r_void
id|rxrpc_get_connection
c_func
(paren
r_struct
id|rxrpc_connection
op_star
id|conn
)paren
(brace
id|BUG_ON
c_func
(paren
id|atomic_read
c_func
(paren
op_amp
id|conn-&gt;usage
)paren
OL
l_int|0
)paren
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|conn-&gt;usage
)paren
suffix:semicolon
singleline_comment|//printk(&quot;rxrpc_get_conn(%p{u=%d})&bslash;n&quot;,conn,atomic_read(&amp;conn-&gt;usage));
)brace
r_extern
r_void
id|rxrpc_put_connection
c_func
(paren
r_struct
id|rxrpc_connection
op_star
id|conn
)paren
suffix:semicolon
r_extern
r_int
id|rxrpc_conn_receive_call_packet
c_func
(paren
r_struct
id|rxrpc_connection
op_star
id|conn
comma
r_struct
id|rxrpc_call
op_star
id|call
comma
r_struct
id|rxrpc_message
op_star
id|msg
)paren
suffix:semicolon
r_extern
r_void
id|rxrpc_conn_handle_error
c_func
(paren
r_struct
id|rxrpc_connection
op_star
id|conn
comma
r_int
id|local
comma
r_int
id|errno
)paren
suffix:semicolon
macro_line|#endif /* _LINUX_RXRPC_CONNECTION_H */
eof
