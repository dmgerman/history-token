multiline_comment|/*&n; * include/linux/nfsd/const.h&n; *&n; * Various constants related to NFS.&n; *&n; * Copyright (C) 1995-1997 Olaf Kirch &lt;okir@monad.swb.de&gt;&n; */
macro_line|#ifndef _LINUX_NFSD_CONST_H
DECL|macro|_LINUX_NFSD_CONST_H
mdefine_line|#define _LINUX_NFSD_CONST_H
macro_line|#include &lt;linux/nfs.h&gt;
macro_line|#include &lt;linux/nfs2.h&gt;
macro_line|#include &lt;linux/nfs3.h&gt;
multiline_comment|/*&n; * Maximum protocol version supported by knfsd&n; */
DECL|macro|NFSSVC_MAXVERS
mdefine_line|#define NFSSVC_MAXVERS&t;&t;3
multiline_comment|/*&n; * Maximum blocksize supported by daemon currently at 32K&n; */
DECL|macro|NFSSVC_MAXBLKSIZE
mdefine_line|#define NFSSVC_MAXBLKSIZE&t;(32*1024)
macro_line|#ifdef __KERNEL__
macro_line|#ifndef NFS_SUPER_MAGIC
DECL|macro|NFS_SUPER_MAGIC
macro_line|# define NFS_SUPER_MAGIC&t;0x6969
macro_line|#endif
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _LINUX_NFSD_CONST_H */
eof
