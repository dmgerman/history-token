multiline_comment|/*&n; * linux/fs/nfsd/xdr.c&n; *&n; * XDR support for nfsd&n; *&n; * Copyright (C) 1995, 1996 Olaf Kirch &lt;okir@monad.swb.de&gt;&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/nfs.h&gt;
macro_line|#include &lt;linux/sunrpc/xdr.h&gt;
macro_line|#include &lt;linux/sunrpc/svc.h&gt;
macro_line|#include &lt;linux/nfsd/nfsd.h&gt;
macro_line|#include &lt;linux/nfsd/xdr.h&gt;
DECL|macro|NFSDDBG_FACILITY
mdefine_line|#define NFSDDBG_FACILITY&t;&t;NFSDDBG_XDR
macro_line|#ifdef NFSD_OPTIMIZE_SPACE
DECL|macro|inline
macro_line|# define inline
macro_line|#endif
multiline_comment|/*&n; * Mapping of S_IF* types to NFS file types&n; */
DECL|variable|nfs_ftypes
r_static
id|u32
id|nfs_ftypes
(braket
)braket
op_assign
(brace
id|NFNON
comma
id|NFCHR
comma
id|NFCHR
comma
id|NFBAD
comma
id|NFDIR
comma
id|NFBAD
comma
id|NFBLK
comma
id|NFBAD
comma
id|NFREG
comma
id|NFBAD
comma
id|NFLNK
comma
id|NFBAD
comma
id|NFSOCK
comma
id|NFBAD
comma
id|NFLNK
comma
id|NFBAD
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * XDR functions for basic NFS types&n; */
r_static
r_inline
id|u32
op_star
DECL|function|decode_fh
id|decode_fh
c_func
(paren
id|u32
op_star
id|p
comma
r_struct
id|svc_fh
op_star
id|fhp
)paren
(brace
id|fh_init
c_func
(paren
id|fhp
comma
id|NFS_FHSIZE
)paren
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|fhp-&gt;fh_handle.fh_base
comma
id|p
comma
id|NFS_FHSIZE
)paren
suffix:semicolon
id|fhp-&gt;fh_handle.fh_size
op_assign
id|NFS_FHSIZE
suffix:semicolon
multiline_comment|/* FIXME: Look up export pointer here and verify&n;&t; * Sun Secure RPC if requested */
r_return
id|p
op_plus
(paren
id|NFS_FHSIZE
op_rshift
l_int|2
)paren
suffix:semicolon
)brace
r_static
r_inline
id|u32
op_star
DECL|function|encode_fh
id|encode_fh
c_func
(paren
id|u32
op_star
id|p
comma
r_struct
id|svc_fh
op_star
id|fhp
)paren
(brace
id|memcpy
c_func
(paren
id|p
comma
op_amp
id|fhp-&gt;fh_handle.fh_base
comma
id|NFS_FHSIZE
)paren
suffix:semicolon
r_return
id|p
op_plus
(paren
id|NFS_FHSIZE
op_rshift
l_int|2
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Decode a file name and make sure that the path contains&n; * no slashes or null bytes.&n; */
r_static
r_inline
id|u32
op_star
DECL|function|decode_filename
id|decode_filename
c_func
(paren
id|u32
op_star
id|p
comma
r_char
op_star
op_star
id|namp
comma
r_int
op_star
id|lenp
)paren
(brace
r_char
op_star
id|name
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
(paren
id|p
op_assign
id|xdr_decode_string_inplace
c_func
(paren
id|p
comma
id|namp
comma
id|lenp
comma
id|NFS_MAXNAMLEN
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
comma
id|name
op_assign
op_star
id|namp
suffix:semicolon
id|i
OL
op_star
id|lenp
suffix:semicolon
id|i
op_increment
comma
id|name
op_increment
)paren
(brace
r_if
c_cond
(paren
op_star
id|name
op_eq
l_char|&squot;&bslash;0&squot;
op_logical_or
op_star
id|name
op_eq
l_char|&squot;/&squot;
)paren
r_return
l_int|NULL
suffix:semicolon
)brace
)brace
r_return
id|p
suffix:semicolon
)brace
r_static
r_inline
id|u32
op_star
DECL|function|decode_pathname
id|decode_pathname
c_func
(paren
id|u32
op_star
id|p
comma
r_char
op_star
op_star
id|namp
comma
r_int
op_star
id|lenp
)paren
(brace
r_char
op_star
id|name
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
(paren
id|p
op_assign
id|xdr_decode_string
c_func
(paren
id|p
comma
id|namp
comma
id|lenp
comma
id|NFS_MAXPATHLEN
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
comma
id|name
op_assign
op_star
id|namp
suffix:semicolon
id|i
OL
op_star
id|lenp
suffix:semicolon
id|i
op_increment
comma
id|name
op_increment
)paren
(brace
r_if
c_cond
(paren
op_star
id|name
op_eq
l_char|&squot;&bslash;0&squot;
)paren
r_return
l_int|NULL
suffix:semicolon
)brace
)brace
r_return
id|p
suffix:semicolon
)brace
r_static
r_inline
id|u32
op_star
DECL|function|decode_sattr
id|decode_sattr
c_func
(paren
id|u32
op_star
id|p
comma
r_struct
id|iattr
op_star
id|iap
)paren
(brace
id|u32
id|tmp
comma
id|tmp1
suffix:semicolon
id|iap-&gt;ia_valid
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Sun client bug compatibility check: some sun clients seem to&n;&t; * put 0xffff in the mode field when they mean 0xffffffff.&n;&t; * Quoting the 4.4BSD nfs server code: Nah nah nah nah na nah.&n;&t; */
r_if
c_cond
(paren
(paren
id|tmp
op_assign
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
)paren
op_ne
(paren
id|u32
)paren
op_minus
l_int|1
op_logical_and
id|tmp
op_ne
l_int|0xffff
)paren
(brace
id|iap-&gt;ia_valid
op_or_assign
id|ATTR_MODE
suffix:semicolon
id|iap-&gt;ia_mode
op_assign
id|tmp
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|tmp
op_assign
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
)paren
op_ne
(paren
id|u32
)paren
op_minus
l_int|1
)paren
(brace
id|iap-&gt;ia_valid
op_or_assign
id|ATTR_UID
suffix:semicolon
id|iap-&gt;ia_uid
op_assign
id|tmp
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|tmp
op_assign
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
)paren
op_ne
(paren
id|u32
)paren
op_minus
l_int|1
)paren
(brace
id|iap-&gt;ia_valid
op_or_assign
id|ATTR_GID
suffix:semicolon
id|iap-&gt;ia_gid
op_assign
id|tmp
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|tmp
op_assign
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
)paren
op_ne
(paren
id|u32
)paren
op_minus
l_int|1
)paren
(brace
id|iap-&gt;ia_valid
op_or_assign
id|ATTR_SIZE
suffix:semicolon
id|iap-&gt;ia_size
op_assign
id|tmp
suffix:semicolon
)brace
id|tmp
op_assign
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
suffix:semicolon
id|tmp1
op_assign
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_ne
(paren
id|u32
)paren
op_minus
l_int|1
op_logical_and
id|tmp1
op_ne
(paren
id|u32
)paren
op_minus
l_int|1
)paren
(brace
id|iap-&gt;ia_valid
op_or_assign
id|ATTR_ATIME
op_or
id|ATTR_ATIME_SET
suffix:semicolon
id|iap-&gt;ia_atime
op_assign
id|tmp
suffix:semicolon
)brace
id|tmp
op_assign
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
suffix:semicolon
id|tmp1
op_assign
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_ne
(paren
id|u32
)paren
op_minus
l_int|1
op_logical_and
id|tmp1
op_ne
(paren
id|u32
)paren
op_minus
l_int|1
)paren
(brace
id|iap-&gt;ia_valid
op_or_assign
id|ATTR_MTIME
op_or
id|ATTR_MTIME_SET
suffix:semicolon
id|iap-&gt;ia_mtime
op_assign
id|tmp
suffix:semicolon
)brace
r_return
id|p
suffix:semicolon
)brace
r_static
r_inline
id|u32
op_star
DECL|function|encode_fattr
id|encode_fattr
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
id|u32
op_star
id|p
comma
r_struct
id|svc_fh
op_star
id|fhp
)paren
(brace
r_struct
id|vfsmount
op_star
id|mnt
op_assign
id|fhp-&gt;fh_export-&gt;ex_mnt
suffix:semicolon
r_struct
id|dentry
op_star
id|dentry
op_assign
id|fhp-&gt;fh_dentry
suffix:semicolon
r_struct
id|kstat
id|stat
suffix:semicolon
r_int
id|type
suffix:semicolon
id|vfs_getattr
c_func
(paren
id|mnt
comma
id|dentry
comma
op_amp
id|stat
)paren
suffix:semicolon
id|type
op_assign
(paren
id|stat.mode
op_amp
id|S_IFMT
)paren
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|htonl
c_func
(paren
id|nfs_ftypes
(braket
id|type
op_rshift
l_int|12
)braket
)paren
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|htonl
c_func
(paren
(paren
id|u32
)paren
id|stat.mode
)paren
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|htonl
c_func
(paren
(paren
id|u32
)paren
id|stat.nlink
)paren
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|htonl
c_func
(paren
(paren
id|u32
)paren
id|nfsd_ruid
c_func
(paren
id|rqstp
comma
id|stat.uid
)paren
)paren
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|htonl
c_func
(paren
(paren
id|u32
)paren
id|nfsd_rgid
c_func
(paren
id|rqstp
comma
id|stat.gid
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|S_ISLNK
c_func
(paren
id|type
)paren
op_logical_and
id|stat.size
OG
id|NFS_MAXPATHLEN
)paren
(brace
op_star
id|p
op_increment
op_assign
id|htonl
c_func
(paren
id|NFS_MAXPATHLEN
)paren
suffix:semicolon
)brace
r_else
(brace
op_star
id|p
op_increment
op_assign
id|htonl
c_func
(paren
(paren
id|u32
)paren
id|stat.size
)paren
suffix:semicolon
)brace
op_star
id|p
op_increment
op_assign
id|htonl
c_func
(paren
(paren
id|u32
)paren
id|stat.blksize
)paren
suffix:semicolon
r_if
c_cond
(paren
id|S_ISCHR
c_func
(paren
id|type
)paren
op_logical_or
id|S_ISBLK
c_func
(paren
id|type
)paren
)paren
op_star
id|p
op_increment
op_assign
id|htonl
c_func
(paren
(paren
id|u32
)paren
id|stat.rdev
)paren
suffix:semicolon
r_else
op_star
id|p
op_increment
op_assign
id|htonl
c_func
(paren
l_int|0xffffffff
)paren
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|htonl
c_func
(paren
(paren
id|u32
)paren
id|stat.blocks
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rqstp-&gt;rq_reffh-&gt;fh_version
op_eq
l_int|1
op_logical_and
id|rqstp-&gt;rq_reffh-&gt;fh_fsid_type
op_eq
l_int|1
op_logical_and
(paren
id|fhp-&gt;fh_export-&gt;ex_flags
op_amp
id|NFSEXP_FSID
)paren
)paren
op_star
id|p
op_increment
op_assign
id|htonl
c_func
(paren
(paren
id|u32
)paren
id|fhp-&gt;fh_export-&gt;ex_fsid
)paren
suffix:semicolon
r_else
op_star
id|p
op_increment
op_assign
id|htonl
c_func
(paren
(paren
id|u32
)paren
id|stat.dev
)paren
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|htonl
c_func
(paren
(paren
id|u32
)paren
id|stat.ino
)paren
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|htonl
c_func
(paren
(paren
id|u32
)paren
id|stat.atime
)paren
suffix:semicolon
op_star
id|p
op_increment
op_assign
l_int|0
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|htonl
c_func
(paren
(paren
id|u32
)paren
id|lease_get_mtime
c_func
(paren
id|dentry-&gt;d_inode
)paren
)paren
suffix:semicolon
op_star
id|p
op_increment
op_assign
l_int|0
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|htonl
c_func
(paren
(paren
id|u32
)paren
id|stat.ctime
)paren
suffix:semicolon
op_star
id|p
op_increment
op_assign
l_int|0
suffix:semicolon
r_return
id|p
suffix:semicolon
)brace
multiline_comment|/*&n; * Check buffer bounds after decoding arguments&n; */
r_static
r_inline
r_int
DECL|function|xdr_argsize_check
id|xdr_argsize_check
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
id|u32
op_star
id|p
)paren
(brace
r_struct
id|svc_buf
op_star
id|buf
op_assign
op_amp
id|rqstp-&gt;rq_argbuf
suffix:semicolon
r_return
id|p
op_minus
id|buf-&gt;base
op_le
id|buf-&gt;buflen
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|xdr_ressize_check
id|xdr_ressize_check
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
id|u32
op_star
id|p
)paren
(brace
r_struct
id|svc_buf
op_star
id|buf
op_assign
op_amp
id|rqstp-&gt;rq_resbuf
suffix:semicolon
id|buf-&gt;len
op_assign
id|p
op_minus
id|buf-&gt;base
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;nfsd: ressize_check p %p base %p len %d&bslash;n&quot;
comma
id|p
comma
id|buf-&gt;base
comma
id|buf-&gt;buflen
)paren
suffix:semicolon
r_return
(paren
id|buf-&gt;len
op_le
id|buf-&gt;buflen
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * XDR decode functions&n; */
r_int
DECL|function|nfssvc_decode_void
id|nfssvc_decode_void
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
id|u32
op_star
id|p
comma
r_void
op_star
id|dummy
)paren
(brace
r_return
id|xdr_argsize_check
c_func
(paren
id|rqstp
comma
id|p
)paren
suffix:semicolon
)brace
r_int
DECL|function|nfssvc_decode_fhandle
id|nfssvc_decode_fhandle
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
id|u32
op_star
id|p
comma
r_struct
id|svc_fh
op_star
id|fhp
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|p
op_assign
id|decode_fh
c_func
(paren
id|p
comma
id|fhp
)paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|xdr_argsize_check
c_func
(paren
id|rqstp
comma
id|p
)paren
suffix:semicolon
)brace
r_int
DECL|function|nfssvc_decode_sattrargs
id|nfssvc_decode_sattrargs
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
id|u32
op_star
id|p
comma
r_struct
id|nfsd_sattrargs
op_star
id|args
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|p
op_assign
id|decode_fh
c_func
(paren
id|p
comma
op_amp
id|args-&gt;fh
)paren
)paren
op_logical_or
op_logical_neg
(paren
id|p
op_assign
id|decode_sattr
c_func
(paren
id|p
comma
op_amp
id|args-&gt;attrs
)paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|xdr_argsize_check
c_func
(paren
id|rqstp
comma
id|p
)paren
suffix:semicolon
)brace
r_int
DECL|function|nfssvc_decode_diropargs
id|nfssvc_decode_diropargs
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
id|u32
op_star
id|p
comma
r_struct
id|nfsd_diropargs
op_star
id|args
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|p
op_assign
id|decode_fh
c_func
(paren
id|p
comma
op_amp
id|args-&gt;fh
)paren
)paren
op_logical_or
op_logical_neg
(paren
id|p
op_assign
id|decode_filename
c_func
(paren
id|p
comma
op_amp
id|args-&gt;name
comma
op_amp
id|args-&gt;len
)paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|xdr_argsize_check
c_func
(paren
id|rqstp
comma
id|p
)paren
suffix:semicolon
)brace
r_int
DECL|function|nfssvc_decode_readargs
id|nfssvc_decode_readargs
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
id|u32
op_star
id|p
comma
r_struct
id|nfsd_readargs
op_star
id|args
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|p
op_assign
id|decode_fh
c_func
(paren
id|p
comma
op_amp
id|args-&gt;fh
)paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|args-&gt;offset
op_assign
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
suffix:semicolon
id|args-&gt;count
op_assign
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
suffix:semicolon
id|args-&gt;totalsize
op_assign
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
suffix:semicolon
r_return
id|xdr_argsize_check
c_func
(paren
id|rqstp
comma
id|p
)paren
suffix:semicolon
)brace
r_int
DECL|function|nfssvc_decode_writeargs
id|nfssvc_decode_writeargs
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
id|u32
op_star
id|p
comma
r_struct
id|nfsd_writeargs
op_star
id|args
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|p
op_assign
id|decode_fh
c_func
(paren
id|p
comma
op_amp
id|args-&gt;fh
)paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|p
op_increment
suffix:semicolon
multiline_comment|/* beginoffset */
id|args-&gt;offset
op_assign
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
suffix:semicolon
multiline_comment|/* offset */
id|p
op_increment
suffix:semicolon
multiline_comment|/* totalcount */
id|args-&gt;len
op_assign
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
suffix:semicolon
id|args-&gt;data
op_assign
(paren
r_char
op_star
)paren
id|p
suffix:semicolon
id|p
op_add_assign
id|XDR_QUADLEN
c_func
(paren
id|args-&gt;len
)paren
suffix:semicolon
r_return
id|xdr_argsize_check
c_func
(paren
id|rqstp
comma
id|p
)paren
suffix:semicolon
)brace
r_int
DECL|function|nfssvc_decode_createargs
id|nfssvc_decode_createargs
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
id|u32
op_star
id|p
comma
r_struct
id|nfsd_createargs
op_star
id|args
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|p
op_assign
id|decode_fh
c_func
(paren
id|p
comma
op_amp
id|args-&gt;fh
)paren
)paren
op_logical_or
op_logical_neg
(paren
id|p
op_assign
id|decode_filename
c_func
(paren
id|p
comma
op_amp
id|args-&gt;name
comma
op_amp
id|args-&gt;len
)paren
)paren
op_logical_or
op_logical_neg
(paren
id|p
op_assign
id|decode_sattr
c_func
(paren
id|p
comma
op_amp
id|args-&gt;attrs
)paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|xdr_argsize_check
c_func
(paren
id|rqstp
comma
id|p
)paren
suffix:semicolon
)brace
r_int
DECL|function|nfssvc_decode_renameargs
id|nfssvc_decode_renameargs
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
id|u32
op_star
id|p
comma
r_struct
id|nfsd_renameargs
op_star
id|args
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|p
op_assign
id|decode_fh
c_func
(paren
id|p
comma
op_amp
id|args-&gt;ffh
)paren
)paren
op_logical_or
op_logical_neg
(paren
id|p
op_assign
id|decode_filename
c_func
(paren
id|p
comma
op_amp
id|args-&gt;fname
comma
op_amp
id|args-&gt;flen
)paren
)paren
op_logical_or
op_logical_neg
(paren
id|p
op_assign
id|decode_fh
c_func
(paren
id|p
comma
op_amp
id|args-&gt;tfh
)paren
)paren
op_logical_or
op_logical_neg
(paren
id|p
op_assign
id|decode_filename
c_func
(paren
id|p
comma
op_amp
id|args-&gt;tname
comma
op_amp
id|args-&gt;tlen
)paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|xdr_argsize_check
c_func
(paren
id|rqstp
comma
id|p
)paren
suffix:semicolon
)brace
r_int
DECL|function|nfssvc_decode_linkargs
id|nfssvc_decode_linkargs
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
id|u32
op_star
id|p
comma
r_struct
id|nfsd_linkargs
op_star
id|args
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|p
op_assign
id|decode_fh
c_func
(paren
id|p
comma
op_amp
id|args-&gt;ffh
)paren
)paren
op_logical_or
op_logical_neg
(paren
id|p
op_assign
id|decode_fh
c_func
(paren
id|p
comma
op_amp
id|args-&gt;tfh
)paren
)paren
op_logical_or
op_logical_neg
(paren
id|p
op_assign
id|decode_filename
c_func
(paren
id|p
comma
op_amp
id|args-&gt;tname
comma
op_amp
id|args-&gt;tlen
)paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|xdr_argsize_check
c_func
(paren
id|rqstp
comma
id|p
)paren
suffix:semicolon
)brace
r_int
DECL|function|nfssvc_decode_symlinkargs
id|nfssvc_decode_symlinkargs
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
id|u32
op_star
id|p
comma
r_struct
id|nfsd_symlinkargs
op_star
id|args
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|p
op_assign
id|decode_fh
c_func
(paren
id|p
comma
op_amp
id|args-&gt;ffh
)paren
)paren
op_logical_or
op_logical_neg
(paren
id|p
op_assign
id|decode_filename
c_func
(paren
id|p
comma
op_amp
id|args-&gt;fname
comma
op_amp
id|args-&gt;flen
)paren
)paren
op_logical_or
op_logical_neg
(paren
id|p
op_assign
id|decode_pathname
c_func
(paren
id|p
comma
op_amp
id|args-&gt;tname
comma
op_amp
id|args-&gt;tlen
)paren
)paren
op_logical_or
op_logical_neg
(paren
id|p
op_assign
id|decode_sattr
c_func
(paren
id|p
comma
op_amp
id|args-&gt;attrs
)paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|xdr_argsize_check
c_func
(paren
id|rqstp
comma
id|p
)paren
suffix:semicolon
)brace
r_int
DECL|function|nfssvc_decode_readdirargs
id|nfssvc_decode_readdirargs
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
id|u32
op_star
id|p
comma
r_struct
id|nfsd_readdirargs
op_star
id|args
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|p
op_assign
id|decode_fh
c_func
(paren
id|p
comma
op_amp
id|args-&gt;fh
)paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|args-&gt;cookie
op_assign
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
suffix:semicolon
id|args-&gt;count
op_assign
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
suffix:semicolon
r_return
id|xdr_argsize_check
c_func
(paren
id|rqstp
comma
id|p
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * XDR encode functions&n; */
r_int
DECL|function|nfssvc_encode_void
id|nfssvc_encode_void
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
id|u32
op_star
id|p
comma
r_void
op_star
id|dummy
)paren
(brace
r_return
id|xdr_ressize_check
c_func
(paren
id|rqstp
comma
id|p
)paren
suffix:semicolon
)brace
r_int
DECL|function|nfssvc_encode_attrstat
id|nfssvc_encode_attrstat
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
id|u32
op_star
id|p
comma
r_struct
id|nfsd_attrstat
op_star
id|resp
)paren
(brace
id|p
op_assign
id|encode_fattr
c_func
(paren
id|rqstp
comma
id|p
comma
op_amp
id|resp-&gt;fh
)paren
suffix:semicolon
r_return
id|xdr_ressize_check
c_func
(paren
id|rqstp
comma
id|p
)paren
suffix:semicolon
)brace
r_int
DECL|function|nfssvc_encode_diropres
id|nfssvc_encode_diropres
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
id|u32
op_star
id|p
comma
r_struct
id|nfsd_diropres
op_star
id|resp
)paren
(brace
id|p
op_assign
id|encode_fh
c_func
(paren
id|p
comma
op_amp
id|resp-&gt;fh
)paren
suffix:semicolon
id|p
op_assign
id|encode_fattr
c_func
(paren
id|rqstp
comma
id|p
comma
op_amp
id|resp-&gt;fh
)paren
suffix:semicolon
r_return
id|xdr_ressize_check
c_func
(paren
id|rqstp
comma
id|p
)paren
suffix:semicolon
)brace
r_int
DECL|function|nfssvc_encode_readlinkres
id|nfssvc_encode_readlinkres
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
id|u32
op_star
id|p
comma
r_struct
id|nfsd_readlinkres
op_star
id|resp
)paren
(brace
op_star
id|p
op_increment
op_assign
id|htonl
c_func
(paren
id|resp-&gt;len
)paren
suffix:semicolon
id|p
op_add_assign
id|XDR_QUADLEN
c_func
(paren
id|resp-&gt;len
)paren
suffix:semicolon
r_return
id|xdr_ressize_check
c_func
(paren
id|rqstp
comma
id|p
)paren
suffix:semicolon
)brace
r_int
DECL|function|nfssvc_encode_readres
id|nfssvc_encode_readres
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
id|u32
op_star
id|p
comma
r_struct
id|nfsd_readres
op_star
id|resp
)paren
(brace
id|p
op_assign
id|encode_fattr
c_func
(paren
id|rqstp
comma
id|p
comma
op_amp
id|resp-&gt;fh
)paren
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|htonl
c_func
(paren
id|resp-&gt;count
)paren
suffix:semicolon
id|p
op_add_assign
id|XDR_QUADLEN
c_func
(paren
id|resp-&gt;count
)paren
suffix:semicolon
r_return
id|xdr_ressize_check
c_func
(paren
id|rqstp
comma
id|p
)paren
suffix:semicolon
)brace
r_int
DECL|function|nfssvc_encode_readdirres
id|nfssvc_encode_readdirres
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
id|u32
op_star
id|p
comma
r_struct
id|nfsd_readdirres
op_star
id|resp
)paren
(brace
id|p
op_add_assign
id|XDR_QUADLEN
c_func
(paren
id|resp-&gt;count
)paren
suffix:semicolon
r_return
id|xdr_ressize_check
c_func
(paren
id|rqstp
comma
id|p
)paren
suffix:semicolon
)brace
r_int
DECL|function|nfssvc_encode_statfsres
id|nfssvc_encode_statfsres
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
id|u32
op_star
id|p
comma
r_struct
id|nfsd_statfsres
op_star
id|resp
)paren
(brace
r_struct
id|statfs
op_star
id|stat
op_assign
op_amp
id|resp-&gt;stats
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|htonl
c_func
(paren
id|NFSSVC_MAXBLKSIZE
)paren
suffix:semicolon
multiline_comment|/* max transfer size */
op_star
id|p
op_increment
op_assign
id|htonl
c_func
(paren
id|stat-&gt;f_bsize
)paren
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|htonl
c_func
(paren
id|stat-&gt;f_blocks
)paren
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|htonl
c_func
(paren
id|stat-&gt;f_bfree
)paren
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|htonl
c_func
(paren
id|stat-&gt;f_bavail
)paren
suffix:semicolon
r_return
id|xdr_ressize_check
c_func
(paren
id|rqstp
comma
id|p
)paren
suffix:semicolon
)brace
r_int
DECL|function|nfssvc_encode_entry
id|nfssvc_encode_entry
c_func
(paren
r_struct
id|readdir_cd
op_star
id|cd
comma
r_const
r_char
op_star
id|name
comma
r_int
id|namlen
comma
id|loff_t
id|offset
comma
id|ino_t
id|ino
comma
r_int
r_int
id|d_type
)paren
(brace
id|u32
op_star
id|p
op_assign
id|cd-&gt;buffer
suffix:semicolon
r_int
id|buflen
comma
id|slen
suffix:semicolon
multiline_comment|/*&n;&t;dprintk(&quot;nfsd: entry(%.*s off %ld ino %ld)&bslash;n&quot;,&n;&t;&t;&t;namlen, name, offset, ino);&n;&t; */
r_if
c_cond
(paren
id|offset
OG
op_complement
(paren
(paren
id|u32
)paren
l_int|0
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|cd-&gt;offset
)paren
op_star
id|cd-&gt;offset
op_assign
id|htonl
c_func
(paren
id|offset
)paren
suffix:semicolon
r_if
c_cond
(paren
id|namlen
OG
id|NFS2_MAXNAMLEN
)paren
id|namlen
op_assign
id|NFS2_MAXNAMLEN
suffix:semicolon
multiline_comment|/* truncate filename */
id|slen
op_assign
id|XDR_QUADLEN
c_func
(paren
id|namlen
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|buflen
op_assign
id|cd-&gt;buflen
op_minus
id|slen
op_minus
l_int|4
)paren
OL
l_int|0
)paren
(brace
id|cd-&gt;eob
op_assign
l_int|1
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
op_star
id|p
op_increment
op_assign
id|xdr_one
suffix:semicolon
multiline_comment|/* mark entry present */
op_star
id|p
op_increment
op_assign
id|htonl
c_func
(paren
(paren
id|u32
)paren
id|ino
)paren
suffix:semicolon
multiline_comment|/* file id */
id|p
op_assign
id|xdr_encode_array
c_func
(paren
id|p
comma
id|name
comma
id|namlen
)paren
suffix:semicolon
multiline_comment|/* name length &amp; name */
id|cd-&gt;offset
op_assign
id|p
suffix:semicolon
multiline_comment|/* remember pointer */
op_star
id|p
op_increment
op_assign
op_complement
(paren
id|u32
)paren
l_int|0
suffix:semicolon
multiline_comment|/* offset of next entry */
id|cd-&gt;buflen
op_assign
id|buflen
suffix:semicolon
id|cd-&gt;buffer
op_assign
id|p
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * XDR release functions&n; */
r_int
DECL|function|nfssvc_release_fhandle
id|nfssvc_release_fhandle
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
id|u32
op_star
id|p
comma
r_struct
id|nfsd_fhandle
op_star
id|resp
)paren
(brace
id|fh_put
c_func
(paren
op_amp
id|resp-&gt;fh
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
eof
