multiline_comment|/*&n; * include/linux/nfsd/export.h&n; * &n; * Public declarations for NFS exports. The definitions for the&n; * syscall interface are in nfsctl.h&n; *&n; * Copyright (C) 1995-1997 Olaf Kirch &lt;okir@monad.swb.de&gt;&n; */
macro_line|#ifndef NFSD_EXPORT_H
DECL|macro|NFSD_EXPORT_H
mdefine_line|#define NFSD_EXPORT_H
macro_line|#include &lt;asm/types.h&gt;
macro_line|#ifdef __KERNEL__
macro_line|# include &lt;linux/types.h&gt;
macro_line|# include &lt;linux/in.h&gt;
macro_line|#endif
multiline_comment|/*&n; * Important limits for the exports stuff.&n; */
DECL|macro|NFSCLNT_IDMAX
mdefine_line|#define NFSCLNT_IDMAX&t;&t;1024
DECL|macro|NFSCLNT_ADDRMAX
mdefine_line|#define NFSCLNT_ADDRMAX&t;&t;16
DECL|macro|NFSCLNT_KEYMAX
mdefine_line|#define NFSCLNT_KEYMAX&t;&t;32
multiline_comment|/*&n; * Export flags.&n; */
DECL|macro|NFSEXP_READONLY
mdefine_line|#define NFSEXP_READONLY&t;&t;0x0001
DECL|macro|NFSEXP_INSECURE_PORT
mdefine_line|#define NFSEXP_INSECURE_PORT&t;0x0002
DECL|macro|NFSEXP_ROOTSQUASH
mdefine_line|#define NFSEXP_ROOTSQUASH&t;0x0004
DECL|macro|NFSEXP_ALLSQUASH
mdefine_line|#define NFSEXP_ALLSQUASH&t;0x0008
DECL|macro|NFSEXP_ASYNC
mdefine_line|#define NFSEXP_ASYNC&t;&t;0x0010
DECL|macro|NFSEXP_GATHERED_WRITES
mdefine_line|#define NFSEXP_GATHERED_WRITES&t;0x0020
DECL|macro|NFSEXP_UIDMAP
mdefine_line|#define NFSEXP_UIDMAP&t;&t;0x0040
DECL|macro|NFSEXP_KERBEROS
mdefine_line|#define NFSEXP_KERBEROS&t;&t;0x0080&t;&t;/* not available */
DECL|macro|NFSEXP_SUNSECURE
mdefine_line|#define NFSEXP_SUNSECURE&t;0x0100
DECL|macro|NFSEXP_CROSSMNT
mdefine_line|#define NFSEXP_CROSSMNT&t;&t;0x0200
DECL|macro|NFSEXP_NOSUBTREECHECK
mdefine_line|#define NFSEXP_NOSUBTREECHECK&t;0x0400
DECL|macro|NFSEXP_NOAUTHNLM
mdefine_line|#define&t;NFSEXP_NOAUTHNLM&t;0x0800&t;&t;/* Don&squot;t authenticate NLM requests - just trust */
DECL|macro|NFSEXP_MSNFS
mdefine_line|#define NFSEXP_MSNFS&t;&t;0x1000&t;/* do silly things that MS clients expect */
DECL|macro|NFSEXP_FSID
mdefine_line|#define NFSEXP_FSID&t;&t;0x2000
DECL|macro|NFSEXP_ALLFLAGS
mdefine_line|#define NFSEXP_ALLFLAGS&t;&t;0x3FFF
macro_line|#ifdef __KERNEL__
multiline_comment|/* The following are hashtable sizes and must be powers of 2 */
DECL|macro|NFSCLNT_EXPMAX
mdefine_line|#define NFSCLNT_EXPMAX&t;&t;16
DECL|struct|svc_client
r_struct
id|svc_client
(brace
DECL|member|cl_next
r_struct
id|svc_client
op_star
id|cl_next
suffix:semicolon
DECL|member|cl_ident
r_char
id|cl_ident
(braket
id|NFSCLNT_IDMAX
)braket
suffix:semicolon
DECL|member|cl_idlen
r_int
id|cl_idlen
suffix:semicolon
DECL|member|cl_naddr
r_int
id|cl_naddr
suffix:semicolon
DECL|member|cl_addr
r_struct
id|in_addr
id|cl_addr
(braket
id|NFSCLNT_ADDRMAX
)braket
suffix:semicolon
DECL|member|cl_umap
r_struct
id|svc_uidmap
op_star
id|cl_umap
suffix:semicolon
DECL|member|cl_export
r_struct
id|list_head
id|cl_export
(braket
id|NFSCLNT_EXPMAX
)braket
suffix:semicolon
DECL|member|cl_expfsid
r_struct
id|list_head
id|cl_expfsid
(braket
id|NFSCLNT_EXPMAX
)braket
suffix:semicolon
DECL|member|cl_list
r_struct
id|list_head
id|cl_list
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|svc_export
r_struct
id|svc_export
(brace
DECL|member|ex_hash
r_struct
id|list_head
id|ex_hash
suffix:semicolon
DECL|member|ex_fsid_hash
r_struct
id|list_head
id|ex_fsid_hash
suffix:semicolon
DECL|member|ex_list
r_struct
id|list_head
id|ex_list
suffix:semicolon
DECL|member|ex_path
r_char
id|ex_path
(braket
id|NFS_MAXPATHLEN
op_plus
l_int|1
)braket
suffix:semicolon
DECL|member|ex_parent
r_struct
id|svc_export
op_star
id|ex_parent
suffix:semicolon
DECL|member|ex_client
r_struct
id|svc_client
op_star
id|ex_client
suffix:semicolon
DECL|member|ex_flags
r_int
id|ex_flags
suffix:semicolon
DECL|member|ex_mnt
r_struct
id|vfsmount
op_star
id|ex_mnt
suffix:semicolon
DECL|member|ex_dentry
r_struct
id|dentry
op_star
id|ex_dentry
suffix:semicolon
DECL|member|ex_dev
id|kdev_t
id|ex_dev
suffix:semicolon
DECL|member|ex_ino
id|ino_t
id|ex_ino
suffix:semicolon
DECL|member|ex_anon_uid
id|uid_t
id|ex_anon_uid
suffix:semicolon
DECL|member|ex_anon_gid
id|gid_t
id|ex_anon_gid
suffix:semicolon
DECL|member|ex_fsid
r_int
id|ex_fsid
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|EX_SECURE
mdefine_line|#define EX_SECURE(exp)&t;&t;(!((exp)-&gt;ex_flags &amp; NFSEXP_INSECURE_PORT))
DECL|macro|EX_ISSYNC
mdefine_line|#define EX_ISSYNC(exp)&t;&t;(!((exp)-&gt;ex_flags &amp; NFSEXP_ASYNC))
DECL|macro|EX_RDONLY
mdefine_line|#define EX_RDONLY(exp)&t;&t;((exp)-&gt;ex_flags &amp; NFSEXP_READONLY)
DECL|macro|EX_CROSSMNT
mdefine_line|#define EX_CROSSMNT(exp)&t;((exp)-&gt;ex_flags &amp; NFSEXP_CROSSMNT)
DECL|macro|EX_SUNSECURE
mdefine_line|#define EX_SUNSECURE(exp)&t;((exp)-&gt;ex_flags &amp; NFSEXP_SUNSECURE)
DECL|macro|EX_WGATHER
mdefine_line|#define EX_WGATHER(exp)&t;&t;((exp)-&gt;ex_flags &amp; NFSEXP_GATHERED_WRITES)
multiline_comment|/*&n; * Function declarations&n; */
r_void
id|nfsd_export_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|nfsd_export_shutdown
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|exp_readlock
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|exp_readunlock
c_func
(paren
r_void
)paren
suffix:semicolon
r_struct
id|svc_client
op_star
id|exp_getclient
c_func
(paren
r_struct
id|sockaddr_in
op_star
id|sin
)paren
suffix:semicolon
r_void
id|exp_putclient
c_func
(paren
r_struct
id|svc_client
op_star
id|clp
)paren
suffix:semicolon
r_struct
id|svc_export
op_star
id|exp_get
c_func
(paren
r_struct
id|svc_client
op_star
id|clp
comma
id|kdev_t
id|dev
comma
id|ino_t
id|ino
)paren
suffix:semicolon
r_struct
id|svc_export
op_star
id|exp_get_fsid
c_func
(paren
r_struct
id|svc_client
op_star
id|clp
comma
r_int
id|fsid
)paren
suffix:semicolon
r_struct
id|svc_export
op_star
id|exp_get_by_name
c_func
(paren
r_struct
id|svc_client
op_star
id|clp
comma
r_struct
id|vfsmount
op_star
id|mnt
comma
r_struct
id|dentry
op_star
id|dentry
)paren
suffix:semicolon
r_int
id|exp_rootfh
c_func
(paren
r_struct
id|svc_client
op_star
comma
r_char
op_star
id|path
comma
r_struct
id|knfsd_fh
op_star
comma
r_int
id|maxsize
)paren
suffix:semicolon
r_int
id|nfserrno
c_func
(paren
r_int
id|errno
)paren
suffix:semicolon
r_void
id|exp_nlmdetach
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* NFSD_EXPORT_H */
eof
