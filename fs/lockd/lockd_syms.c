multiline_comment|/*&n; * linux/fs/lockd/lockd_syms.c&n; *&n; * Symbols exported by the lockd module.&n; *&n; * Authors:&t;Olaf Kirch (okir@monad.swb.de)&n; *&n; * Copyright (C) 1997 Olaf Kirch &lt;okir@monad.swb.de&gt;&n; */
DECL|macro|__NO_VERSION__
mdefine_line|#define __NO_VERSION__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#ifdef CONFIG_MODULES
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/uio.h&gt;
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;linux/sunrpc/clnt.h&gt;
macro_line|#include &lt;linux/sunrpc/svc.h&gt;
macro_line|#include &lt;linux/lockd/lockd.h&gt;
multiline_comment|/* Start/stop the daemon */
DECL|variable|lockd_up
id|EXPORT_SYMBOL
c_func
(paren
id|lockd_up
)paren
suffix:semicolon
DECL|variable|lockd_down
id|EXPORT_SYMBOL
c_func
(paren
id|lockd_down
)paren
suffix:semicolon
multiline_comment|/* NFS client entry */
DECL|variable|nlmclnt_proc
id|EXPORT_SYMBOL
c_func
(paren
id|nlmclnt_proc
)paren
suffix:semicolon
multiline_comment|/* NFS server entry points/hooks */
DECL|variable|nlmsvc_invalidate_client
id|EXPORT_SYMBOL
c_func
(paren
id|nlmsvc_invalidate_client
)paren
suffix:semicolon
DECL|variable|nlmsvc_ops
id|EXPORT_SYMBOL
c_func
(paren
id|nlmsvc_ops
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_MODULES */
eof
