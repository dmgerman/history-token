multiline_comment|/*&n; * linux/include/linux/nfsd/debug.h&n; *&n; * Debugging-related stuff for nfsd&n; *&n; * Copyright (C) 1995 Olaf Kirch &lt;okir@monad.swb.de&gt;&n; */
macro_line|#ifndef LINUX_NFSD_DEBUG_H
DECL|macro|LINUX_NFSD_DEBUG_H
mdefine_line|#define LINUX_NFSD_DEBUG_H
macro_line|#include &lt;linux/sunrpc/debug.h&gt;
multiline_comment|/*&n; * Enable debugging for nfsd.&n; * Requires RPC_DEBUG.&n; */
macro_line|#ifdef RPC_DEBUG
DECL|macro|NFSD_DEBUG
macro_line|# define NFSD_DEBUG&t;&t;1
macro_line|#endif
multiline_comment|/*&n; * knfsd debug flags&n; */
DECL|macro|NFSDDBG_SOCK
mdefine_line|#define NFSDDBG_SOCK&t;&t;0x0001
DECL|macro|NFSDDBG_FH
mdefine_line|#define NFSDDBG_FH&t;&t;0x0002
DECL|macro|NFSDDBG_EXPORT
mdefine_line|#define NFSDDBG_EXPORT&t;&t;0x0004
DECL|macro|NFSDDBG_SVC
mdefine_line|#define NFSDDBG_SVC&t;&t;0x0008
DECL|macro|NFSDDBG_PROC
mdefine_line|#define NFSDDBG_PROC&t;&t;0x0010
DECL|macro|NFSDDBG_FILEOP
mdefine_line|#define NFSDDBG_FILEOP&t;&t;0x0020
DECL|macro|NFSDDBG_AUTH
mdefine_line|#define NFSDDBG_AUTH&t;&t;0x0040
DECL|macro|NFSDDBG_REPCACHE
mdefine_line|#define NFSDDBG_REPCACHE&t;0x0080
DECL|macro|NFSDDBG_XDR
mdefine_line|#define NFSDDBG_XDR&t;&t;0x0100
DECL|macro|NFSDDBG_LOCKD
mdefine_line|#define NFSDDBG_LOCKD&t;&t;0x0200
DECL|macro|NFSDDBG_ALL
mdefine_line|#define NFSDDBG_ALL&t;&t;0x7FFF
DECL|macro|NFSDDBG_NOCHANGE
mdefine_line|#define NFSDDBG_NOCHANGE&t;0xFFFF
macro_line|#ifdef __KERNEL__
DECL|macro|ifdebug
macro_line|# undef ifdebug
macro_line|# ifdef NFSD_DEBUG
DECL|macro|ifdebug
macro_line|#  define ifdebug(flag)&t;&t;if (nfsd_debug &amp; NFSDDBG_##flag)
macro_line|# else
DECL|macro|ifdebug
macro_line|#  define ifdebug(flag)&t;&t;if (0)
macro_line|# endif
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* LINUX_NFSD_DEBUG_H */
eof
