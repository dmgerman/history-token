multiline_comment|/*&n; * linux/include/linux/sunrpc/types.h&n; *&n; * Generic types and misc stuff for RPC.&n; *&n; * Copyright (C) 1996, Olaf Kirch &lt;okir@monad.swb.de&gt;&n; */
macro_line|#ifndef _LINUX_SUNRPC_TYPES_H_
DECL|macro|_LINUX_SUNRPC_TYPES_H_
mdefine_line|#define _LINUX_SUNRPC_TYPES_H_
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/tqueue.h&gt;
macro_line|#include &lt;linux/sunrpc/debug.h&gt;
macro_line|#include &lt;linux/list.h&gt;
multiline_comment|/*&n; * Shorthands&n; */
DECL|macro|signalled
mdefine_line|#define signalled()&t;&t;(signal_pending(current))
macro_line|#endif /* _LINUX_SUNRPC_TYPES_H_ */
eof
