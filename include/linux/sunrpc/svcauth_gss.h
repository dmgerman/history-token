multiline_comment|/*&n; * linux/include/linux/svcauth_gss.h&n; *&n; * Bruce Fields &lt;bfields@umich.edu&gt;&n; * Copyright (c) 2002 The Regents of the Unviersity of Michigan&n; *&n; * $Id$&n; *&n; */
macro_line|#ifndef _LINUX_SUNRPC_SVCAUTH_GSS_H
DECL|macro|_LINUX_SUNRPC_SVCAUTH_GSS_H
mdefine_line|#define _LINUX_SUNRPC_SVCAUTH_GSS_H
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/sunrpc/types.h&gt;
macro_line|#include &lt;linux/sunrpc/xdr.h&gt;
macro_line|#include &lt;linux/sunrpc/svcauth.h&gt;
macro_line|#include &lt;linux/sunrpc/svcsock.h&gt;
macro_line|#include &lt;linux/sunrpc/auth_gss.h&gt;
r_int
id|gss_svc_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|gss_svc_shutdown
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|svcauth_gss_register_pseudoflavor
c_func
(paren
id|u32
id|pseudoflavor
comma
r_char
op_star
id|name
)paren
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _LINUX_SUNRPC_SVCAUTH_GSS_H */
eof
