multiline_comment|/* krxsecd.h: Rx RPC security kernel thread interface&n; *&n; * Copyright (C) 2002 Red Hat, Inc. All Rights Reserved.&n; * Written by David Howells (dhowells@redhat.com)&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _LINUX_RXRPC_KRXSECD_H
DECL|macro|_LINUX_RXRPC_KRXSECD_H
mdefine_line|#define _LINUX_RXRPC_KRXSECD_H
macro_line|#include &lt;rxrpc/types.h&gt;
r_extern
r_int
id|rxrpc_krxsecd_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|rxrpc_krxsecd_kill
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|rxrpc_krxsecd_clear_transport
c_func
(paren
r_struct
id|rxrpc_transport
op_star
id|trans
)paren
suffix:semicolon
r_extern
r_void
id|rxrpc_krxsecd_queue_incoming_call
c_func
(paren
r_struct
id|rxrpc_message
op_star
id|msg
)paren
suffix:semicolon
macro_line|#endif /* _LINUX_RXRPC_KRXSECD_H */
eof
