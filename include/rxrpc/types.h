multiline_comment|/* types.h: Rx types&n; *&n; * Copyright (C) 2002 Red Hat, Inc. All Rights Reserved.&n; * Written by David Howells (dhowells@redhat.com)&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _LINUX_RXRPC_TYPES_H
DECL|macro|_LINUX_RXRPC_TYPES_H
mdefine_line|#define _LINUX_RXRPC_TYPES_H
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
DECL|typedef|rxrpc_seq_t
r_typedef
r_uint32
id|rxrpc_seq_t
suffix:semicolon
multiline_comment|/* Rx message sequence number */
DECL|typedef|rxrpc_serial_t
r_typedef
r_uint32
id|rxrpc_serial_t
suffix:semicolon
multiline_comment|/* Rx message serial number */
DECL|typedef|rxrpc_seq_net_t
r_typedef
id|__be32
id|rxrpc_seq_net_t
suffix:semicolon
multiline_comment|/* on-the-wire Rx message sequence number */
DECL|typedef|rxrpc_serial_net_t
r_typedef
id|__be32
id|rxrpc_serial_net_t
suffix:semicolon
multiline_comment|/* on-the-wire Rx message serial number */
r_struct
id|rxrpc_call
suffix:semicolon
r_struct
id|rxrpc_connection
suffix:semicolon
r_struct
id|rxrpc_header
suffix:semicolon
r_struct
id|rxrpc_message
suffix:semicolon
r_struct
id|rxrpc_operation
suffix:semicolon
r_struct
id|rxrpc_peer
suffix:semicolon
r_struct
id|rxrpc_service
suffix:semicolon
DECL|typedef|rxrpc_timer_t
r_typedef
r_struct
id|rxrpc_timer
id|rxrpc_timer_t
suffix:semicolon
r_struct
id|rxrpc_transport
suffix:semicolon
DECL|typedef|rxrpc_call_attn_func_t
r_typedef
r_void
(paren
op_star
id|rxrpc_call_attn_func_t
)paren
(paren
r_struct
id|rxrpc_call
op_star
id|call
)paren
suffix:semicolon
DECL|typedef|rxrpc_call_error_func_t
r_typedef
r_void
(paren
op_star
id|rxrpc_call_error_func_t
)paren
(paren
r_struct
id|rxrpc_call
op_star
id|call
)paren
suffix:semicolon
DECL|typedef|rxrpc_call_aemap_func_t
r_typedef
r_void
(paren
op_star
id|rxrpc_call_aemap_func_t
)paren
(paren
r_struct
id|rxrpc_call
op_star
id|call
)paren
suffix:semicolon
macro_line|#endif /* _LINUX_RXRPC_TYPES_H */
eof
