multiline_comment|/*&n; * include/linux/nfsd/auth.h&n; *&n; * nfsd-specific authentication stuff.&n; * uid/gid mapping not yet implemented.&n; *&n; * Copyright (C) 1995, 1996 Olaf Kirch &lt;okir@monad.swb.de&gt;&n; */
macro_line|#ifndef LINUX_NFSD_AUTH_H
DECL|macro|LINUX_NFSD_AUTH_H
mdefine_line|#define LINUX_NFSD_AUTH_H
macro_line|#ifdef __KERNEL__
DECL|macro|nfsd_luid
mdefine_line|#define nfsd_luid(rq, uid)&t;((u32)(uid))
DECL|macro|nfsd_lgid
mdefine_line|#define nfsd_lgid(rq, gid)&t;((u32)(gid))
DECL|macro|nfsd_ruid
mdefine_line|#define nfsd_ruid(rq, uid)&t;((u32)(uid))
DECL|macro|nfsd_rgid
mdefine_line|#define nfsd_rgid(rq, gid)&t;((u32)(gid))
multiline_comment|/*&n; * Set the current process&squot;s fsuid/fsgid etc to those of the NFS&n; * client user&n; */
r_void
id|nfsd_setuser
c_func
(paren
r_struct
id|svc_rqst
op_star
comma
r_struct
id|svc_export
op_star
)paren
suffix:semicolon
macro_line|#if 0
multiline_comment|/*&n; * These must match the actual size of uid_t and gid_t&n; */
mdefine_line|#define UGID_BITS&t;&t;(8 * sizeof(uid_t))
mdefine_line|#define UGID_SHIFT&t;&t;8
mdefine_line|#define UGID_MASK&t;&t;((1 &lt;&lt; UGID_SHIFT) - 1)
mdefine_line|#define UGID_NRENTRIES&t;&t;((1 &lt;&lt; (UGID_BITS - UGID_SHIFT)) + 1)
mdefine_line|#define UGID_NONE&t;&t;((unsigned short)-1)
r_typedef
r_struct
id|svc_uidmap
(brace
id|uid_t
op_star
id|um_ruid
(braket
id|UGID_NRENTRIES
)braket
suffix:semicolon
id|uid_t
op_star
id|um_luid
(braket
id|UGID_NRENTRIES
)braket
suffix:semicolon
id|gid_t
op_star
id|um_rgid
(braket
id|UGID_NRENTRIES
)braket
suffix:semicolon
id|gid_t
op_star
id|um_lgid
(braket
id|UGID_NRENTRIES
)braket
suffix:semicolon
)brace
id|svc_uidmap
suffix:semicolon
macro_line|#endif
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* LINUX_NFSD_AUTH_H */
eof
