multiline_comment|/*&n; * linux/include/linux/lockd/debug.h&n; *&n; * Debugging stuff.&n; *&n; * Copyright (C) 1996 Olaf Kirch &lt;okir@monad.swb.de&gt;&n; */
macro_line|#ifndef LINUX_LOCKD_DEBUG_H
DECL|macro|LINUX_LOCKD_DEBUG_H
mdefine_line|#define LINUX_LOCKD_DEBUG_H
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/sunrpc/debug.h&gt;
multiline_comment|/*&n; * Enable lockd debugging.&n; * Requires RPC_DEBUG.&n; */
macro_line|#ifdef RPC_DEBUG
DECL|macro|LOCKD_DEBUG
macro_line|# define LOCKD_DEBUG&t;&t;1
macro_line|#endif
DECL|macro|ifdebug
macro_line|#undef ifdebug
macro_line|#if defined(RPC_DEBUG) &amp;&amp; defined(LOCKD_DEBUG)
DECL|macro|ifdebug
macro_line|# define ifdebug(flag)&t;&t;if (nlm_debug &amp; NLMDBG_##flag)
macro_line|#else
DECL|macro|ifdebug
macro_line|# define ifdebug(flag)&t;&t;if (0)
macro_line|#endif
macro_line|#ifdef LOCKD_DEBUG
r_char
op_star
id|nlm_procname
c_func
(paren
id|u32
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif /* __KERNEL__ */
multiline_comment|/*&n; * Debug flags&n; */
DECL|macro|NLMDBG_SVC
mdefine_line|#define NLMDBG_SVC&t;&t;0x0001
DECL|macro|NLMDBG_CLIENT
mdefine_line|#define NLMDBG_CLIENT&t;&t;0x0002
DECL|macro|NLMDBG_CLNTLOCK
mdefine_line|#define NLMDBG_CLNTLOCK&t;&t;0x0004
DECL|macro|NLMDBG_SVCLOCK
mdefine_line|#define NLMDBG_SVCLOCK&t;&t;0x0008
DECL|macro|NLMDBG_MONITOR
mdefine_line|#define NLMDBG_MONITOR&t;&t;0x0010
DECL|macro|NLMDBG_CLNTSUBS
mdefine_line|#define NLMDBG_CLNTSUBS&t;&t;0x0020
DECL|macro|NLMDBG_SVCSUBS
mdefine_line|#define NLMDBG_SVCSUBS&t;&t;0x0040
DECL|macro|NLMDBG_HOSTCACHE
mdefine_line|#define NLMDBG_HOSTCACHE&t;0x0080
DECL|macro|NLMDBG_XDR
mdefine_line|#define NLMDBG_XDR&t;&t;0x0100
DECL|macro|NLMDBG_ALL
mdefine_line|#define NLMDBG_ALL&t;&t;0x7fff
macro_line|#endif /* LINUX_LOCKD_DEBUG_H */
eof
