multiline_comment|/*&n; * linux/include/linux/sunrpc/debug.h&n; *&n; * Debugging support for sunrpc module&n; *&n; * Copyright (C) 1996, Olaf Kirch &lt;okir@monad.swb.de&gt;&n; */
macro_line|#ifndef _LINUX_SUNRPC_DEBUG_H_
DECL|macro|_LINUX_SUNRPC_DEBUG_H_
mdefine_line|#define _LINUX_SUNRPC_DEBUG_H_
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/tqueue.h&gt;
multiline_comment|/*&n; * Enable RPC debugging/profiling.&n; */
macro_line|#ifdef CONFIG_SYSCTL
DECL|macro|RPC_DEBUG
mdefine_line|#define  RPC_DEBUG
macro_line|#endif
multiline_comment|/* #define  RPC_PROFILE */
multiline_comment|/*&n; * RPC debug facilities&n; */
DECL|macro|RPCDBG_XPRT
mdefine_line|#define RPCDBG_XPRT&t;&t;0x0001
DECL|macro|RPCDBG_CALL
mdefine_line|#define RPCDBG_CALL&t;&t;0x0002
DECL|macro|RPCDBG_DEBUG
mdefine_line|#define RPCDBG_DEBUG&t;&t;0x0004
DECL|macro|RPCDBG_NFS
mdefine_line|#define RPCDBG_NFS&t;&t;0x0008
DECL|macro|RPCDBG_AUTH
mdefine_line|#define RPCDBG_AUTH&t;&t;0x0010
DECL|macro|RPCDBG_PMAP
mdefine_line|#define RPCDBG_PMAP&t;&t;0x0020
DECL|macro|RPCDBG_SCHED
mdefine_line|#define RPCDBG_SCHED&t;&t;0x0040
DECL|macro|RPCDBG_SVCSOCK
mdefine_line|#define RPCDBG_SVCSOCK&t;&t;0x0100
DECL|macro|RPCDBG_SVCDSP
mdefine_line|#define RPCDBG_SVCDSP&t;&t;0x0200
DECL|macro|RPCDBG_MISC
mdefine_line|#define RPCDBG_MISC&t;&t;0x0400
DECL|macro|RPCDBG_ALL
mdefine_line|#define RPCDBG_ALL&t;&t;0x7fff
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * Debugging macros etc&n; */
macro_line|#ifdef RPC_DEBUG
r_extern
r_int
r_int
id|rpc_debug
suffix:semicolon
r_extern
r_int
r_int
id|nfs_debug
suffix:semicolon
r_extern
r_int
r_int
id|nfsd_debug
suffix:semicolon
r_extern
r_int
r_int
id|nlm_debug
suffix:semicolon
macro_line|#endif
DECL|macro|dprintk
mdefine_line|#define dprintk(args...)&t;dfprintk(FACILITY, ## args)
DECL|macro|ifdebug
macro_line|#undef ifdebug
macro_line|#ifdef RPC_DEBUG&t;&t;&t;
DECL|macro|ifdebug
macro_line|# define ifdebug(fac)&t;&t;if (rpc_debug &amp; RPCDBG_##fac)
DECL|macro|dfprintk
macro_line|# define dfprintk(fac, args...)&t;do { ifdebug(fac) printk(args); } while(0)
DECL|macro|RPC_IFDEBUG
macro_line|# define RPC_IFDEBUG(x)&t;&t;x
macro_line|#else
DECL|macro|dfprintk
macro_line|# define dfprintk(fac, args...)&t;do ; while (0)
DECL|macro|RPC_IFDEBUG
macro_line|# define RPC_IFDEBUG(x)
macro_line|#endif
macro_line|#ifdef RPC_PROFILE
DECL|macro|pprintk
macro_line|# define pprintk(args...)&t;printk(## args)
macro_line|#else
DECL|macro|pprintk
macro_line|# define pprintk(args...)&t;do ; while (0)
macro_line|#endif
multiline_comment|/*&n; * Sysctl interface for RPC debugging&n; */
macro_line|#ifdef RPC_DEBUG
r_void
id|rpc_register_sysctl
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|rpc_unregister_sysctl
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif /* __KERNEL__ */
multiline_comment|/*&n; * Declarations for the sysctl debug interface, which allows to read or&n; * change the debug flags for rpc, nfs, nfsd, and lockd. Since the sunrpc&n; * module currently registers its sysctl table dynamically, the sysctl path&n; * for module FOO is &lt;CTL_SUNRPC, CTL_FOODEBUG&gt;.&n; */
DECL|macro|CTL_SUNRPC
mdefine_line|#define CTL_SUNRPC&t;7249&t;/* arbitrary and hopefully unused */
r_enum
(brace
DECL|enumerator|CTL_RPCDEBUG
id|CTL_RPCDEBUG
op_assign
l_int|1
comma
DECL|enumerator|CTL_NFSDEBUG
id|CTL_NFSDEBUG
comma
DECL|enumerator|CTL_NFSDDEBUG
id|CTL_NFSDDEBUG
comma
DECL|enumerator|CTL_NLMDEBUG
id|CTL_NLMDEBUG
comma
)brace
suffix:semicolon
macro_line|#endif /* _LINUX_SUNRPC_DEBUG_H_ */
eof
