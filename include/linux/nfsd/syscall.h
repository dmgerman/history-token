multiline_comment|/*&n; * include/linux/nfsd/syscall.h&n; *&n; * This file holds all declarations for the knfsd syscall interface.&n; *&n; * Copyright (C) 1995-1997 Olaf Kirch &lt;okir@monad.swb.de&gt;&n; */
macro_line|#ifndef NFSD_SYSCALL_H
DECL|macro|NFSD_SYSCALL_H
mdefine_line|#define NFSD_SYSCALL_H
macro_line|#include &lt;asm/types.h&gt;
macro_line|#ifdef __KERNEL__
macro_line|# include &lt;linux/config.h&gt;
macro_line|# include &lt;linux/types.h&gt;
macro_line|# include &lt;linux/in.h&gt;
macro_line|#endif 
macro_line|#include &lt;linux/posix_types.h&gt;
macro_line|#include &lt;linux/nfsd/const.h&gt;
macro_line|#include &lt;linux/nfsd/export.h&gt;
macro_line|#include &lt;linux/nfsd/nfsfh.h&gt;
macro_line|#include &lt;linux/nfsd/auth.h&gt;
multiline_comment|/*&n; * Version of the syscall interface&n; */
DECL|macro|NFSCTL_VERSION
mdefine_line|#define NFSCTL_VERSION&t;&t;0x0201
multiline_comment|/*&n; * These are the commands understood by nfsctl().&n; */
DECL|macro|NFSCTL_SVC
mdefine_line|#define NFSCTL_SVC&t;&t;0&t;/* This is a server process. */
DECL|macro|NFSCTL_ADDCLIENT
mdefine_line|#define NFSCTL_ADDCLIENT&t;1&t;/* Add an NFS client. */
DECL|macro|NFSCTL_DELCLIENT
mdefine_line|#define NFSCTL_DELCLIENT&t;2&t;/* Remove an NFS client. */
DECL|macro|NFSCTL_EXPORT
mdefine_line|#define NFSCTL_EXPORT&t;&t;3&t;/* export a file system. */
DECL|macro|NFSCTL_UNEXPORT
mdefine_line|#define NFSCTL_UNEXPORT&t;&t;4&t;/* unexport a file system. */
DECL|macro|NFSCTL_UGIDUPDATE
mdefine_line|#define NFSCTL_UGIDUPDATE&t;5&t;/* update a client&squot;s uid/gid map. */
DECL|macro|NFSCTL_GETFH
mdefine_line|#define NFSCTL_GETFH&t;&t;6&t;/* get an fh by ino (used by mountd) */
DECL|macro|NFSCTL_GETFD
mdefine_line|#define NFSCTL_GETFD&t;&t;7&t;/* get an fh by path (used by mountd) */
DECL|macro|NFSCTL_GETFS
mdefine_line|#define&t;NFSCTL_GETFS&t;&t;8&t;/* get an fh by path with max FH len */
multiline_comment|/* SVC */
DECL|struct|nfsctl_svc
r_struct
id|nfsctl_svc
(brace
DECL|member|svc_port
r_int
r_int
id|svc_port
suffix:semicolon
DECL|member|svc_nthreads
r_int
id|svc_nthreads
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* ADDCLIENT/DELCLIENT */
DECL|struct|nfsctl_client
r_struct
id|nfsctl_client
(brace
DECL|member|cl_ident
r_char
id|cl_ident
(braket
id|NFSCLNT_IDMAX
op_plus
l_int|1
)braket
suffix:semicolon
DECL|member|cl_naddr
r_int
id|cl_naddr
suffix:semicolon
DECL|member|cl_addrlist
r_struct
id|in_addr
id|cl_addrlist
(braket
id|NFSCLNT_ADDRMAX
)braket
suffix:semicolon
DECL|member|cl_fhkeytype
r_int
id|cl_fhkeytype
suffix:semicolon
DECL|member|cl_fhkeylen
r_int
id|cl_fhkeylen
suffix:semicolon
DECL|member|cl_fhkey
r_int
r_char
id|cl_fhkey
(braket
id|NFSCLNT_KEYMAX
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* EXPORT/UNEXPORT */
DECL|struct|nfsctl_export
r_struct
id|nfsctl_export
(brace
DECL|member|ex_client
r_char
id|ex_client
(braket
id|NFSCLNT_IDMAX
op_plus
l_int|1
)braket
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
DECL|member|ex_dev
id|__kernel_dev_t
id|ex_dev
suffix:semicolon
DECL|member|ex_ino
id|__kernel_ino_t
id|ex_ino
suffix:semicolon
DECL|member|ex_flags
r_int
id|ex_flags
suffix:semicolon
DECL|member|ex_anon_uid
id|__kernel_uid_t
id|ex_anon_uid
suffix:semicolon
DECL|member|ex_anon_gid
id|__kernel_gid_t
id|ex_anon_gid
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* UGIDUPDATE */
DECL|struct|nfsctl_uidmap
r_struct
id|nfsctl_uidmap
(brace
DECL|member|ug_ident
r_char
op_star
id|ug_ident
suffix:semicolon
DECL|member|ug_uidbase
id|__kernel_uid_t
id|ug_uidbase
suffix:semicolon
DECL|member|ug_uidlen
r_int
id|ug_uidlen
suffix:semicolon
DECL|member|ug_udimap
id|__kernel_uid_t
op_star
id|ug_udimap
suffix:semicolon
DECL|member|ug_gidbase
id|__kernel_gid_t
id|ug_gidbase
suffix:semicolon
DECL|member|ug_gidlen
r_int
id|ug_gidlen
suffix:semicolon
DECL|member|ug_gdimap
id|__kernel_gid_t
op_star
id|ug_gdimap
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* GETFH */
DECL|struct|nfsctl_fhparm
r_struct
id|nfsctl_fhparm
(brace
DECL|member|gf_addr
r_struct
id|sockaddr
id|gf_addr
suffix:semicolon
DECL|member|gf_dev
id|__kernel_dev_t
id|gf_dev
suffix:semicolon
DECL|member|gf_ino
id|__kernel_ino_t
id|gf_ino
suffix:semicolon
DECL|member|gf_version
r_int
id|gf_version
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* GETFD */
DECL|struct|nfsctl_fdparm
r_struct
id|nfsctl_fdparm
(brace
DECL|member|gd_addr
r_struct
id|sockaddr
id|gd_addr
suffix:semicolon
DECL|member|gd_path
r_char
id|gd_path
(braket
id|NFS_MAXPATHLEN
op_plus
l_int|1
)braket
suffix:semicolon
DECL|member|gd_version
r_int
id|gd_version
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* GETFS - GET Filehandle with Size */
DECL|struct|nfsctl_fsparm
r_struct
id|nfsctl_fsparm
(brace
DECL|member|gd_addr
r_struct
id|sockaddr
id|gd_addr
suffix:semicolon
DECL|member|gd_path
r_char
id|gd_path
(braket
id|NFS_MAXPATHLEN
op_plus
l_int|1
)braket
suffix:semicolon
DECL|member|gd_maxlen
r_int
id|gd_maxlen
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * This is the argument union.&n; */
DECL|struct|nfsctl_arg
r_struct
id|nfsctl_arg
(brace
DECL|member|ca_version
r_int
id|ca_version
suffix:semicolon
multiline_comment|/* safeguard */
r_union
(brace
DECL|member|u_svc
r_struct
id|nfsctl_svc
id|u_svc
suffix:semicolon
DECL|member|u_client
r_struct
id|nfsctl_client
id|u_client
suffix:semicolon
DECL|member|u_export
r_struct
id|nfsctl_export
id|u_export
suffix:semicolon
DECL|member|u_umap
r_struct
id|nfsctl_uidmap
id|u_umap
suffix:semicolon
DECL|member|u_getfh
r_struct
id|nfsctl_fhparm
id|u_getfh
suffix:semicolon
DECL|member|u_getfd
r_struct
id|nfsctl_fdparm
id|u_getfd
suffix:semicolon
DECL|member|u_getfs
r_struct
id|nfsctl_fsparm
id|u_getfs
suffix:semicolon
DECL|member|u
)brace
id|u
suffix:semicolon
DECL|macro|ca_svc
mdefine_line|#define ca_svc&t;&t;u.u_svc
DECL|macro|ca_client
mdefine_line|#define ca_client&t;u.u_client
DECL|macro|ca_export
mdefine_line|#define ca_export&t;u.u_export
DECL|macro|ca_umap
mdefine_line|#define ca_umap&t;&t;u.u_umap
DECL|macro|ca_getfh
mdefine_line|#define ca_getfh&t;u.u_getfh
DECL|macro|ca_getfd
mdefine_line|#define ca_getfd&t;u.u_getfd
DECL|macro|ca_getfs
mdefine_line|#define&t;ca_getfs&t;u.u_getfs
DECL|macro|ca_authd
mdefine_line|#define ca_authd&t;u.u_authd
)brace
suffix:semicolon
DECL|union|nfsctl_res
r_union
id|nfsctl_res
(brace
DECL|member|cr_getfh
id|__u8
id|cr_getfh
(braket
id|NFS_FHSIZE
)braket
suffix:semicolon
DECL|member|cr_getfs
r_struct
id|knfsd_fh
id|cr_getfs
suffix:semicolon
)brace
suffix:semicolon
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * Kernel syscall implementation.&n; */
r_extern
id|asmlinkage
r_int
id|sys_nfsservctl
c_func
(paren
r_int
comma
r_struct
id|nfsctl_arg
op_star
comma
r_void
op_star
)paren
suffix:semicolon
r_extern
r_int
id|exp_addclient
c_func
(paren
r_struct
id|nfsctl_client
op_star
id|ncp
)paren
suffix:semicolon
r_extern
r_int
id|exp_delclient
c_func
(paren
r_struct
id|nfsctl_client
op_star
id|ncp
)paren
suffix:semicolon
r_extern
r_int
id|exp_export
c_func
(paren
r_struct
id|nfsctl_export
op_star
id|nxp
)paren
suffix:semicolon
r_extern
r_int
id|exp_unexport
c_func
(paren
r_struct
id|nfsctl_export
op_star
id|nxp
)paren
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* NFSD_SYSCALL_H */
eof
