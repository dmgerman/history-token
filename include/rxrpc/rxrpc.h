multiline_comment|/* rx.h: Rx RPC interface&n; *&n; * Copyright (C) 2002 Red Hat, Inc. All Rights Reserved.&n; * Written by David Howells (dhowells@redhat.com)&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _LINUX_RXRPC_RXRPC_H
DECL|macro|_LINUX_RXRPC_RXRPC_H
mdefine_line|#define _LINUX_RXRPC_RXRPC_H
macro_line|#ifdef __KERNEL__
r_extern
id|__be32
id|rxrpc_epoch
suffix:semicolon
macro_line|#ifdef CONFIG_SYSCTL
r_extern
r_int
id|rxrpc_ktrace
suffix:semicolon
r_extern
r_int
id|rxrpc_kdebug
suffix:semicolon
r_extern
r_int
id|rxrpc_kproto
suffix:semicolon
r_extern
r_int
id|rxrpc_knet
suffix:semicolon
macro_line|#else
DECL|macro|rxrpc_ktrace
mdefine_line|#define rxrpc_ktrace&t;0
DECL|macro|rxrpc_kdebug
mdefine_line|#define rxrpc_kdebug&t;0
DECL|macro|rxrpc_kproto
mdefine_line|#define rxrpc_kproto&t;0
DECL|macro|rxrpc_knet
mdefine_line|#define rxrpc_knet&t;0
macro_line|#endif
r_extern
r_int
id|rxrpc_sysctl_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|rxrpc_sysctl_cleanup
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _LINUX_RXRPC_RXRPC_H */
eof
