multiline_comment|/*&n; * linux/include/linux/nfsd/nfsd.h&n; *&n; * Hodge-podge collection of knfsd-related stuff.&n; * I will sort this out later.&n; *&n; * Copyright (C) 1995-1997 Olaf Kirch &lt;okir@monad.swb.de&gt;&n; */
macro_line|#ifndef LINUX_NFSD_NFSD_H
DECL|macro|LINUX_NFSD_NFSD_H
mdefine_line|#define LINUX_NFSD_NFSD_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;linux/dirent.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/nfsd/debug.h&gt;
macro_line|#include &lt;linux/nfsd/nfsfh.h&gt;
macro_line|#include &lt;linux/nfsd/export.h&gt;
macro_line|#include &lt;linux/nfsd/auth.h&gt;
macro_line|#include &lt;linux/nfsd/stats.h&gt;
macro_line|#include &lt;linux/nfsd/interface.h&gt;
multiline_comment|/*&n; * nfsd version&n; */
DECL|macro|NFSD_VERSION
mdefine_line|#define NFSD_VERSION&t;&t;&quot;0.5&quot;
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * Special flags for nfsd_permission. These must be different from MAY_READ,&n; * MAY_WRITE, and MAY_EXEC.&n; */
DECL|macro|MAY_NOP
mdefine_line|#define MAY_NOP&t;&t;&t;0
DECL|macro|MAY_SATTR
mdefine_line|#define MAY_SATTR&t;&t;8
DECL|macro|MAY_TRUNC
mdefine_line|#define MAY_TRUNC&t;&t;16
DECL|macro|MAY_LOCK
mdefine_line|#define MAY_LOCK&t;&t;32
DECL|macro|MAY_OWNER_OVERRIDE
mdefine_line|#define MAY_OWNER_OVERRIDE&t;64
macro_line|#if (MAY_SATTR | MAY_TRUNC | MAY_LOCK | MAX_OWNER_OVERRIDE) &amp; (MAY_READ | MAY_WRITE | MAY_EXEC | MAY_OWNER_OVERRIDE)
macro_line|# error &quot;please use a different value for MAY_SATTR or MAY_TRUNC or MAY_LOCK or MAY_OWNER_OVERRIDE.&quot;
macro_line|#endif
DECL|macro|MAY_CREATE
mdefine_line|#define MAY_CREATE&t;&t;(MAY_EXEC|MAY_WRITE)
DECL|macro|MAY_REMOVE
mdefine_line|#define MAY_REMOVE&t;&t;(MAY_EXEC|MAY_WRITE|MAY_TRUNC)
multiline_comment|/*&n; * Callback function for readdir&n; */
DECL|struct|readdir_cd
r_struct
id|readdir_cd
(brace
DECL|member|rqstp
r_struct
id|svc_rqst
op_star
id|rqstp
suffix:semicolon
DECL|member|dirfh
r_struct
id|svc_fh
op_star
id|dirfh
suffix:semicolon
DECL|member|buffer
id|u32
op_star
id|buffer
suffix:semicolon
DECL|member|buflen
r_int
id|buflen
suffix:semicolon
DECL|member|offset
id|u32
op_star
id|offset
suffix:semicolon
multiline_comment|/* previous dirent-&gt;d_next */
DECL|member|plus
r_char
id|plus
suffix:semicolon
multiline_comment|/* readdirplus */
DECL|member|eob
r_char
id|eob
suffix:semicolon
multiline_comment|/* end of buffer */
DECL|member|dotonly
r_char
id|dotonly
suffix:semicolon
DECL|member|nfserr
r_int
id|nfserr
suffix:semicolon
multiline_comment|/* v4 only */
DECL|member|bmval
id|u32
id|bmval
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* v4 only */
)brace
suffix:semicolon
DECL|typedef|encode_dent_fn
r_typedef
r_int
(paren
op_star
id|encode_dent_fn
)paren
(paren
r_struct
id|readdir_cd
op_star
comma
r_const
r_char
op_star
comma
r_int
comma
id|loff_t
comma
id|ino_t
comma
r_int
r_int
)paren
suffix:semicolon
DECL|typedef|nfsd_dirop_t
r_typedef
r_int
(paren
op_star
id|nfsd_dirop_t
)paren
(paren
r_struct
id|inode
op_star
comma
r_struct
id|dentry
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
multiline_comment|/*&n; * Procedure table for NFSv2&n; */
r_extern
r_struct
id|svc_procedure
id|nfsd_procedures2
(braket
)braket
suffix:semicolon
macro_line|#ifdef CONFIG_NFSD_V3
r_extern
r_struct
id|svc_procedure
id|nfsd_procedures3
(braket
)braket
suffix:semicolon
macro_line|#endif /* CONFIG_NFSD_V3 */
r_extern
r_struct
id|svc_program
id|nfsd_program
suffix:semicolon
multiline_comment|/*&n; * Function prototypes.&n; */
r_int
id|nfsd_svc
c_func
(paren
r_int
r_int
id|port
comma
r_int
id|nrservs
)paren
suffix:semicolon
multiline_comment|/* nfsd/vfs.c */
r_int
id|fh_lock_parent
c_func
(paren
r_struct
id|svc_fh
op_star
comma
r_struct
id|dentry
op_star
)paren
suffix:semicolon
r_int
id|nfsd_racache_init
c_func
(paren
r_int
)paren
suffix:semicolon
r_void
id|nfsd_racache_shutdown
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|nfsd_lookup
c_func
(paren
r_struct
id|svc_rqst
op_star
comma
r_struct
id|svc_fh
op_star
comma
r_const
r_char
op_star
comma
r_int
comma
r_struct
id|svc_fh
op_star
)paren
suffix:semicolon
r_int
id|nfsd_setattr
c_func
(paren
r_struct
id|svc_rqst
op_star
comma
r_struct
id|svc_fh
op_star
comma
r_struct
id|iattr
op_star
comma
r_int
comma
id|time_t
)paren
suffix:semicolon
r_int
id|nfsd_create
c_func
(paren
r_struct
id|svc_rqst
op_star
comma
r_struct
id|svc_fh
op_star
comma
r_char
op_star
id|name
comma
r_int
id|len
comma
r_struct
id|iattr
op_star
id|attrs
comma
r_int
id|type
comma
id|dev_t
id|rdev
comma
r_struct
id|svc_fh
op_star
id|res
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_NFSD_V3
r_int
id|nfsd_access
c_func
(paren
r_struct
id|svc_rqst
op_star
comma
r_struct
id|svc_fh
op_star
comma
id|u32
op_star
comma
id|u32
op_star
)paren
suffix:semicolon
r_int
id|nfsd_create_v3
c_func
(paren
r_struct
id|svc_rqst
op_star
comma
r_struct
id|svc_fh
op_star
comma
r_char
op_star
id|name
comma
r_int
id|len
comma
r_struct
id|iattr
op_star
id|attrs
comma
r_struct
id|svc_fh
op_star
id|res
comma
r_int
id|createmode
comma
id|u32
op_star
id|verifier
comma
r_int
op_star
id|truncp
)paren
suffix:semicolon
r_int
id|nfsd_commit
c_func
(paren
r_struct
id|svc_rqst
op_star
comma
r_struct
id|svc_fh
op_star
comma
id|off_t
comma
r_int
r_int
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_NFSD_V3 */
r_int
id|nfsd_open
c_func
(paren
r_struct
id|svc_rqst
op_star
comma
r_struct
id|svc_fh
op_star
comma
r_int
comma
r_int
comma
r_struct
id|file
op_star
)paren
suffix:semicolon
r_void
id|nfsd_close
c_func
(paren
r_struct
id|file
op_star
)paren
suffix:semicolon
r_int
id|nfsd_read
c_func
(paren
r_struct
id|svc_rqst
op_star
comma
r_struct
id|svc_fh
op_star
comma
id|loff_t
comma
r_char
op_star
comma
r_int
r_int
op_star
)paren
suffix:semicolon
r_int
id|nfsd_write
c_func
(paren
r_struct
id|svc_rqst
op_star
comma
r_struct
id|svc_fh
op_star
comma
id|loff_t
comma
r_char
op_star
comma
r_int
r_int
comma
r_int
op_star
)paren
suffix:semicolon
r_int
id|nfsd_readlink
c_func
(paren
r_struct
id|svc_rqst
op_star
comma
r_struct
id|svc_fh
op_star
comma
r_char
op_star
comma
r_int
op_star
)paren
suffix:semicolon
r_int
id|nfsd_symlink
c_func
(paren
r_struct
id|svc_rqst
op_star
comma
r_struct
id|svc_fh
op_star
comma
r_char
op_star
id|name
comma
r_int
id|len
comma
r_char
op_star
id|path
comma
r_int
id|plen
comma
r_struct
id|svc_fh
op_star
id|res
comma
r_struct
id|iattr
op_star
)paren
suffix:semicolon
r_int
id|nfsd_link
c_func
(paren
r_struct
id|svc_rqst
op_star
comma
r_struct
id|svc_fh
op_star
comma
r_char
op_star
comma
r_int
comma
r_struct
id|svc_fh
op_star
)paren
suffix:semicolon
r_int
id|nfsd_rename
c_func
(paren
r_struct
id|svc_rqst
op_star
comma
r_struct
id|svc_fh
op_star
comma
r_char
op_star
comma
r_int
comma
r_struct
id|svc_fh
op_star
comma
r_char
op_star
comma
r_int
)paren
suffix:semicolon
r_int
id|nfsd_remove
c_func
(paren
r_struct
id|svc_rqst
op_star
comma
r_struct
id|svc_fh
op_star
comma
r_char
op_star
comma
r_int
)paren
suffix:semicolon
r_int
id|nfsd_unlink
c_func
(paren
r_struct
id|svc_rqst
op_star
comma
r_struct
id|svc_fh
op_star
comma
r_int
id|type
comma
r_char
op_star
id|name
comma
r_int
id|len
)paren
suffix:semicolon
r_int
id|nfsd_truncate
c_func
(paren
r_struct
id|svc_rqst
op_star
comma
r_struct
id|svc_fh
op_star
comma
r_int
r_int
id|size
)paren
suffix:semicolon
r_int
id|nfsd_readdir
c_func
(paren
r_struct
id|svc_rqst
op_star
comma
r_struct
id|svc_fh
op_star
comma
id|loff_t
comma
id|encode_dent_fn
comma
id|u32
op_star
id|buffer
comma
r_int
op_star
id|countp
comma
id|u32
op_star
id|verf
comma
id|u32
op_star
id|bmval
)paren
suffix:semicolon
r_int
id|nfsd_statfs
c_func
(paren
r_struct
id|svc_rqst
op_star
comma
r_struct
id|svc_fh
op_star
comma
r_struct
id|statfs
op_star
)paren
suffix:semicolon
r_int
id|nfsd_notify_change
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|iattr
op_star
)paren
suffix:semicolon
r_int
id|nfsd_permission
c_func
(paren
r_struct
id|svc_export
op_star
comma
r_struct
id|dentry
op_star
comma
r_int
)paren
suffix:semicolon
multiline_comment|/*&n; * lockd binding&n; */
r_void
id|nfsd_lockd_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|nfsd_lockd_shutdown
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|nfsd_lockd_unexport
c_func
(paren
r_struct
id|svc_client
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; * These macros provide pre-xdr&squot;ed values for faster operation.&n; */
DECL|macro|nfs_ok
mdefine_line|#define&t;nfs_ok&t;&t;&t;__constant_htonl(NFS_OK)
DECL|macro|nfserr_perm
mdefine_line|#define&t;nfserr_perm&t;&t;__constant_htonl(NFSERR_PERM)
DECL|macro|nfserr_noent
mdefine_line|#define&t;nfserr_noent&t;&t;__constant_htonl(NFSERR_NOENT)
DECL|macro|nfserr_io
mdefine_line|#define&t;nfserr_io&t;&t;__constant_htonl(NFSERR_IO)
DECL|macro|nfserr_nxio
mdefine_line|#define&t;nfserr_nxio&t;&t;__constant_htonl(NFSERR_NXIO)
DECL|macro|nfserr_eagain
mdefine_line|#define&t;nfserr_eagain&t;&t;__constant_htonl(NFSERR_EAGAIN)
DECL|macro|nfserr_acces
mdefine_line|#define&t;nfserr_acces&t;&t;__constant_htonl(NFSERR_ACCES)
DECL|macro|nfserr_exist
mdefine_line|#define&t;nfserr_exist&t;&t;__constant_htonl(NFSERR_EXIST)
DECL|macro|nfserr_xdev
mdefine_line|#define&t;nfserr_xdev&t;&t;__constant_htonl(NFSERR_XDEV)
DECL|macro|nfserr_nodev
mdefine_line|#define&t;nfserr_nodev&t;&t;__constant_htonl(NFSERR_NODEV)
DECL|macro|nfserr_notdir
mdefine_line|#define&t;nfserr_notdir&t;&t;__constant_htonl(NFSERR_NOTDIR)
DECL|macro|nfserr_isdir
mdefine_line|#define&t;nfserr_isdir&t;&t;__constant_htonl(NFSERR_ISDIR)
DECL|macro|nfserr_inval
mdefine_line|#define&t;nfserr_inval&t;&t;__constant_htonl(NFSERR_INVAL)
DECL|macro|nfserr_fbig
mdefine_line|#define&t;nfserr_fbig&t;&t;__constant_htonl(NFSERR_FBIG)
DECL|macro|nfserr_nospc
mdefine_line|#define&t;nfserr_nospc&t;&t;__constant_htonl(NFSERR_NOSPC)
DECL|macro|nfserr_rofs
mdefine_line|#define&t;nfserr_rofs&t;&t;__constant_htonl(NFSERR_ROFS)
DECL|macro|nfserr_mlink
mdefine_line|#define&t;nfserr_mlink&t;&t;__constant_htonl(NFSERR_MLINK)
DECL|macro|nfserr_opnotsupp
mdefine_line|#define&t;nfserr_opnotsupp&t;__constant_htonl(NFSERR_OPNOTSUPP)
DECL|macro|nfserr_nametoolong
mdefine_line|#define&t;nfserr_nametoolong&t;__constant_htonl(NFSERR_NAMETOOLONG)
DECL|macro|nfserr_notempty
mdefine_line|#define&t;nfserr_notempty&t;&t;__constant_htonl(NFSERR_NOTEMPTY)
DECL|macro|nfserr_dquot
mdefine_line|#define&t;nfserr_dquot&t;&t;__constant_htonl(NFSERR_DQUOT)
DECL|macro|nfserr_stale
mdefine_line|#define&t;nfserr_stale&t;&t;__constant_htonl(NFSERR_STALE)
DECL|macro|nfserr_remote
mdefine_line|#define&t;nfserr_remote&t;&t;__constant_htonl(NFSERR_REMOTE)
DECL|macro|nfserr_wflush
mdefine_line|#define&t;nfserr_wflush&t;&t;__constant_htonl(NFSERR_WFLUSH)
DECL|macro|nfserr_badhandle
mdefine_line|#define&t;nfserr_badhandle&t;__constant_htonl(NFSERR_BADHANDLE)
DECL|macro|nfserr_notsync
mdefine_line|#define&t;nfserr_notsync&t;&t;__constant_htonl(NFSERR_NOT_SYNC)
DECL|macro|nfserr_badcookie
mdefine_line|#define&t;nfserr_badcookie&t;__constant_htonl(NFSERR_BAD_COOKIE)
DECL|macro|nfserr_notsupp
mdefine_line|#define&t;nfserr_notsupp&t;&t;__constant_htonl(NFSERR_NOTSUPP)
DECL|macro|nfserr_toosmall
mdefine_line|#define&t;nfserr_toosmall&t;&t;__constant_htonl(NFSERR_TOOSMALL)
DECL|macro|nfserr_serverfault
mdefine_line|#define&t;nfserr_serverfault&t;__constant_htonl(NFSERR_SERVERFAULT)
DECL|macro|nfserr_badtype
mdefine_line|#define&t;nfserr_badtype&t;&t;__constant_htonl(NFSERR_BADTYPE)
DECL|macro|nfserr_jukebox
mdefine_line|#define&t;nfserr_jukebox&t;&t;__constant_htonl(NFSERR_JUKEBOX)
DECL|macro|nfserr_bad_cookie
mdefine_line|#define&t;nfserr_bad_cookie&t;__constant_htonl(NFSERR_BAD_COOKIE)
DECL|macro|nfserr_same
mdefine_line|#define&t;nfserr_same&t;&t;__constant_htonl(NFSERR_SAME)
DECL|macro|nfserr_clid_inuse
mdefine_line|#define&t;nfserr_clid_inuse&t;__constant_htonl(NFSERR_CLID_INUSE)
DECL|macro|nfserr_resource
mdefine_line|#define&t;nfserr_resource&t;&t;__constant_htonl(NFSERR_RESOURCE)
DECL|macro|nfserr_nofilehandle
mdefine_line|#define&t;nfserr_nofilehandle&t;__constant_htonl(NFSERR_NOFILEHANDLE)
DECL|macro|nfserr_minor_vers_mismatch
mdefine_line|#define&t;nfserr_minor_vers_mismatch&t;__constant_htonl(NFSERR_MINOR_VERS_MISMATCH)
DECL|macro|nfserr_symlink
mdefine_line|#define&t;nfserr_symlink&t;&t;__constant_htonl(NFSERR_SYMLINK)
DECL|macro|nfserr_not_same
mdefine_line|#define&t;nfserr_not_same&t;&t;__constant_htonl(NFSERR_NOT_SAME)
DECL|macro|nfserr_readdir_nospc
mdefine_line|#define&t;nfserr_readdir_nospc&t;__constant_htonl(NFSERR_READDIR_NOSPC)
DECL|macro|nfserr_bad_xdr
mdefine_line|#define&t;nfserr_bad_xdr&t;&t;__constant_htonl(NFSERR_BAD_XDR)
multiline_comment|/* error code for internal use - if a request fails due to&n; * kmalloc failure, it gets dropped.  Client should resend eventually&n; */
DECL|macro|nfserr_dropit
mdefine_line|#define&t;nfserr_dropit&t;&t;__constant_htonl(30000)
multiline_comment|/* Check for dir entries &squot;.&squot; and &squot;..&squot; */
DECL|macro|isdotent
mdefine_line|#define isdotent(n, l)&t;(l &lt; 3 &amp;&amp; n[0] == &squot;.&squot; &amp;&amp; (l == 1 || n[1] == &squot;.&squot;))
multiline_comment|/*&n; * Time of server startup&n; */
r_extern
r_struct
id|timeval
id|nfssvc_boot
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* LINUX_NFSD_NFSD_H */
eof
