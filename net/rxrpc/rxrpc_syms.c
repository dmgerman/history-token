multiline_comment|/* rxrpc_syms.c: exported Rx RPC layer interface symbols&n; *&n; * Copyright (C) 2002 Red Hat, Inc. All Rights Reserved.&n; * Written by David Howells (dhowells@redhat.com)&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;rxrpc/transport.h&gt;
macro_line|#include &lt;rxrpc/connection.h&gt;
macro_line|#include &lt;rxrpc/call.h&gt;
macro_line|#include &lt;rxrpc/krxiod.h&gt;
multiline_comment|/* call.c */
DECL|variable|rxrpc_create_call
id|EXPORT_SYMBOL
c_func
(paren
id|rxrpc_create_call
)paren
suffix:semicolon
DECL|variable|rxrpc_put_call
id|EXPORT_SYMBOL
c_func
(paren
id|rxrpc_put_call
)paren
suffix:semicolon
DECL|variable|rxrpc_call_abort
id|EXPORT_SYMBOL
c_func
(paren
id|rxrpc_call_abort
)paren
suffix:semicolon
DECL|variable|rxrpc_call_read_data
id|EXPORT_SYMBOL
c_func
(paren
id|rxrpc_call_read_data
)paren
suffix:semicolon
DECL|variable|rxrpc_call_write_data
id|EXPORT_SYMBOL
c_func
(paren
id|rxrpc_call_write_data
)paren
suffix:semicolon
multiline_comment|/* connection.c */
DECL|variable|rxrpc_create_connection
id|EXPORT_SYMBOL
c_func
(paren
id|rxrpc_create_connection
)paren
suffix:semicolon
DECL|variable|rxrpc_put_connection
id|EXPORT_SYMBOL
c_func
(paren
id|rxrpc_put_connection
)paren
suffix:semicolon
multiline_comment|/* transport.c */
DECL|variable|rxrpc_create_transport
id|EXPORT_SYMBOL
c_func
(paren
id|rxrpc_create_transport
)paren
suffix:semicolon
DECL|variable|rxrpc_put_transport
id|EXPORT_SYMBOL
c_func
(paren
id|rxrpc_put_transport
)paren
suffix:semicolon
DECL|variable|rxrpc_add_service
id|EXPORT_SYMBOL
c_func
(paren
id|rxrpc_add_service
)paren
suffix:semicolon
DECL|variable|rxrpc_del_service
id|EXPORT_SYMBOL
c_func
(paren
id|rxrpc_del_service
)paren
suffix:semicolon
eof
