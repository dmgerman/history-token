multiline_comment|/*&n; * linux/fs/nfs/nfs2xdr.c&n; *&n; * XDR functions to encode/decode NFS RPC arguments and results.&n; *&n; * Copyright (C) 1992, 1993, 1994  Rick Sladkey&n; * Copyright (C) 1996 Olaf Kirch&n; * 04 Aug 1998  Ion Badulescu &lt;ionut@cs.columbia.edu&gt;&n; * &t;&t;FIFO&squot;s need special handling in NFSv2&n; */
macro_line|#include &lt;linux/param.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/utsname.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/sunrpc/clnt.h&gt;
macro_line|#include &lt;linux/nfs.h&gt;
macro_line|#include &lt;linux/nfs2.h&gt;
macro_line|#include &lt;linux/nfs_fs.h&gt;
DECL|macro|NFSDBG_FACILITY
mdefine_line|#define NFSDBG_FACILITY&t;&t;NFSDBG_XDR
multiline_comment|/* #define NFS_PARANOIA 1 */
r_extern
r_int
id|nfs_stat_to_errno
c_func
(paren
r_int
id|stat
)paren
suffix:semicolon
multiline_comment|/* Mapping from NFS error code to &quot;errno&quot; error code. */
DECL|macro|errno_NFSERR_IO
mdefine_line|#define errno_NFSERR_IO&t;&t;EIO
multiline_comment|/*&n; * Declare the space requirements for NFS arguments and replies as&n; * number of 32bit-words&n; */
DECL|macro|NFS_fhandle_sz
mdefine_line|#define NFS_fhandle_sz&t;&t;8
DECL|macro|NFS_sattr_sz
mdefine_line|#define NFS_sattr_sz&t;&t;8
DECL|macro|NFS_filename_sz
mdefine_line|#define NFS_filename_sz&t;&t;1+(NFS2_MAXNAMLEN&gt;&gt;2)
DECL|macro|NFS_path_sz
mdefine_line|#define NFS_path_sz&t;&t;1+(NFS2_MAXPATHLEN&gt;&gt;2)
DECL|macro|NFS_fattr_sz
mdefine_line|#define NFS_fattr_sz&t;&t;17
DECL|macro|NFS_info_sz
mdefine_line|#define NFS_info_sz&t;&t;5
DECL|macro|NFS_entry_sz
mdefine_line|#define NFS_entry_sz&t;&t;NFS_filename_sz+3
DECL|macro|NFS_enc_void_sz
mdefine_line|#define NFS_enc_void_sz&t;&t;0
DECL|macro|NFS_diropargs_sz
mdefine_line|#define NFS_diropargs_sz&t;NFS_fhandle_sz+NFS_filename_sz
DECL|macro|NFS_sattrargs_sz
mdefine_line|#define NFS_sattrargs_sz&t;NFS_fhandle_sz+NFS_sattr_sz
DECL|macro|NFS_readlinkargs_sz
mdefine_line|#define NFS_readlinkargs_sz&t;NFS_fhandle_sz
DECL|macro|NFS_readargs_sz
mdefine_line|#define NFS_readargs_sz&t;&t;NFS_fhandle_sz+3
DECL|macro|NFS_writeargs_sz
mdefine_line|#define NFS_writeargs_sz&t;NFS_fhandle_sz+4
DECL|macro|NFS_createargs_sz
mdefine_line|#define NFS_createargs_sz&t;NFS_diropargs_sz+NFS_sattr_sz
DECL|macro|NFS_renameargs_sz
mdefine_line|#define NFS_renameargs_sz&t;NFS_diropargs_sz+NFS_diropargs_sz
DECL|macro|NFS_linkargs_sz
mdefine_line|#define NFS_linkargs_sz&t;&t;NFS_fhandle_sz+NFS_diropargs_sz
DECL|macro|NFS_symlinkargs_sz
mdefine_line|#define NFS_symlinkargs_sz&t;NFS_diropargs_sz+NFS_path_sz+NFS_sattr_sz
DECL|macro|NFS_readdirargs_sz
mdefine_line|#define NFS_readdirargs_sz&t;NFS_fhandle_sz+2
DECL|macro|NFS_dec_void_sz
mdefine_line|#define NFS_dec_void_sz&t;&t;0
DECL|macro|NFS_attrstat_sz
mdefine_line|#define NFS_attrstat_sz&t;&t;1+NFS_fattr_sz
DECL|macro|NFS_diropres_sz
mdefine_line|#define NFS_diropres_sz&t;&t;1+NFS_fhandle_sz+NFS_fattr_sz
DECL|macro|NFS_readlinkres_sz
mdefine_line|#define NFS_readlinkres_sz&t;1
DECL|macro|NFS_readres_sz
mdefine_line|#define NFS_readres_sz&t;&t;1+NFS_fattr_sz+1
DECL|macro|NFS_writeres_sz
mdefine_line|#define NFS_writeres_sz         NFS_attrstat_sz
DECL|macro|NFS_stat_sz
mdefine_line|#define NFS_stat_sz&t;&t;1
DECL|macro|NFS_readdirres_sz
mdefine_line|#define NFS_readdirres_sz&t;1
DECL|macro|NFS_statfsres_sz
mdefine_line|#define NFS_statfsres_sz&t;1+NFS_info_sz
multiline_comment|/*&n; * Common NFS XDR functions as inlines&n; */
r_static
r_inline
id|u32
op_star
DECL|function|xdr_encode_fhandle
id|xdr_encode_fhandle
c_func
(paren
id|u32
op_star
id|p
comma
r_struct
id|nfs_fh
op_star
id|fhandle
)paren
(brace
id|memcpy
c_func
(paren
id|p
comma
id|fhandle-&gt;data
comma
id|NFS2_FHSIZE
)paren
suffix:semicolon
r_return
id|p
op_plus
id|XDR_QUADLEN
c_func
(paren
id|NFS2_FHSIZE
)paren
suffix:semicolon
)brace
r_static
r_inline
id|u32
op_star
DECL|function|xdr_decode_fhandle
id|xdr_decode_fhandle
c_func
(paren
id|u32
op_star
id|p
comma
r_struct
id|nfs_fh
op_star
id|fhandle
)paren
(brace
multiline_comment|/* Zero handle first to allow comparisons */
id|memset
c_func
(paren
id|fhandle
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|fhandle
)paren
)paren
suffix:semicolon
multiline_comment|/* NFSv2 handles have a fixed length */
id|fhandle-&gt;size
op_assign
id|NFS2_FHSIZE
suffix:semicolon
id|memcpy
c_func
(paren
id|fhandle-&gt;data
comma
id|p
comma
id|NFS2_FHSIZE
)paren
suffix:semicolon
r_return
id|p
op_plus
id|XDR_QUADLEN
c_func
(paren
id|NFS2_FHSIZE
)paren
suffix:semicolon
)brace
r_static
r_inline
id|u32
op_star
DECL|function|xdr_decode_time
id|xdr_decode_time
c_func
(paren
id|u32
op_star
id|p
comma
id|u64
op_star
id|timep
)paren
(brace
id|u64
id|tmp
op_assign
(paren
id|u64
)paren
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
op_lshift
l_int|32
suffix:semicolon
op_star
id|timep
op_assign
id|tmp
op_plus
(paren
id|u64
)paren
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
suffix:semicolon
r_return
id|p
suffix:semicolon
)brace
r_static
id|u32
op_star
DECL|function|xdr_decode_fattr
id|xdr_decode_fattr
c_func
(paren
id|u32
op_star
id|p
comma
r_struct
id|nfs_fattr
op_star
id|fattr
)paren
(brace
id|fattr-&gt;type
op_assign
(paren
r_enum
id|nfs_ftype
)paren
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
suffix:semicolon
id|fattr-&gt;mode
op_assign
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
suffix:semicolon
id|fattr-&gt;nlink
op_assign
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
suffix:semicolon
id|fattr-&gt;uid
op_assign
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
suffix:semicolon
id|fattr-&gt;gid
op_assign
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
suffix:semicolon
id|fattr-&gt;size
op_assign
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
suffix:semicolon
id|fattr-&gt;du.nfs2.blocksize
op_assign
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
suffix:semicolon
id|fattr-&gt;rdev
op_assign
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
suffix:semicolon
id|fattr-&gt;du.nfs2.blocks
op_assign
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
suffix:semicolon
id|fattr-&gt;fsid_u.nfs3
op_assign
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
suffix:semicolon
id|fattr-&gt;fileid
op_assign
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
suffix:semicolon
id|p
op_assign
id|xdr_decode_time
c_func
(paren
id|p
comma
op_amp
id|fattr-&gt;atime
)paren
suffix:semicolon
id|p
op_assign
id|xdr_decode_time
c_func
(paren
id|p
comma
op_amp
id|fattr-&gt;mtime
)paren
suffix:semicolon
id|p
op_assign
id|xdr_decode_time
c_func
(paren
id|p
comma
op_amp
id|fattr-&gt;ctime
)paren
suffix:semicolon
id|fattr-&gt;valid
op_or_assign
id|NFS_ATTR_FATTR
suffix:semicolon
r_if
c_cond
(paren
id|fattr-&gt;type
op_eq
id|NFCHR
op_logical_and
id|fattr-&gt;rdev
op_eq
id|NFS2_FIFO_DEV
)paren
(brace
id|fattr-&gt;type
op_assign
id|NFFIFO
suffix:semicolon
id|fattr-&gt;mode
op_assign
(paren
id|fattr-&gt;mode
op_amp
op_complement
id|S_IFMT
)paren
op_or
id|S_IFIFO
suffix:semicolon
id|fattr-&gt;rdev
op_assign
l_int|0
suffix:semicolon
)brace
id|fattr-&gt;timestamp
op_assign
id|jiffies
suffix:semicolon
r_return
id|p
suffix:semicolon
)brace
DECL|macro|SATTR
mdefine_line|#define SATTR(p, attr, flag, field) &bslash;&n;        *p++ = (attr-&gt;ia_valid &amp; flag) ? htonl(attr-&gt;field) : ~(u32) 0
r_static
r_inline
id|u32
op_star
DECL|function|xdr_encode_sattr
id|xdr_encode_sattr
c_func
(paren
id|u32
op_star
id|p
comma
r_struct
id|iattr
op_star
id|attr
)paren
(brace
id|SATTR
c_func
(paren
id|p
comma
id|attr
comma
id|ATTR_MODE
comma
id|ia_mode
)paren
suffix:semicolon
id|SATTR
c_func
(paren
id|p
comma
id|attr
comma
id|ATTR_UID
comma
id|ia_uid
)paren
suffix:semicolon
id|SATTR
c_func
(paren
id|p
comma
id|attr
comma
id|ATTR_GID
comma
id|ia_gid
)paren
suffix:semicolon
id|SATTR
c_func
(paren
id|p
comma
id|attr
comma
id|ATTR_SIZE
comma
id|ia_size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|attr-&gt;ia_valid
op_amp
(paren
id|ATTR_ATIME
op_or
id|ATTR_ATIME_SET
)paren
)paren
(brace
op_star
id|p
op_increment
op_assign
id|htonl
c_func
(paren
id|attr-&gt;ia_atime.tv_sec
)paren
suffix:semicolon
op_star
id|p
op_increment
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
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
)brace
r_if
c_cond
(paren
id|attr-&gt;ia_valid
op_amp
(paren
id|ATTR_MTIME
op_or
id|ATTR_MTIME_SET
)paren
)paren
(brace
op_star
id|p
op_increment
op_assign
id|htonl
c_func
(paren
id|attr-&gt;ia_mtime.tv_sec
)paren
suffix:semicolon
op_star
id|p
op_increment
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
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
)brace
r_return
id|p
suffix:semicolon
)brace
DECL|macro|SATTR
macro_line|#undef SATTR
multiline_comment|/*&n; * NFS encode functions&n; */
multiline_comment|/*&n; * Encode void argument&n; */
r_static
r_int
DECL|function|nfs_xdr_enc_void
id|nfs_xdr_enc_void
c_func
(paren
r_struct
id|rpc_rqst
op_star
id|req
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
id|req-&gt;rq_slen
op_assign
id|xdr_adjust_iovec
c_func
(paren
id|req-&gt;rq_svec
comma
id|p
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Encode file handle argument&n; * GETATTR, READLINK, STATFS&n; */
r_static
r_int
DECL|function|nfs_xdr_fhandle
id|nfs_xdr_fhandle
c_func
(paren
r_struct
id|rpc_rqst
op_star
id|req
comma
id|u32
op_star
id|p
comma
r_struct
id|nfs_fh
op_star
id|fh
)paren
(brace
id|p
op_assign
id|xdr_encode_fhandle
c_func
(paren
id|p
comma
id|fh
)paren
suffix:semicolon
id|req-&gt;rq_slen
op_assign
id|xdr_adjust_iovec
c_func
(paren
id|req-&gt;rq_svec
comma
id|p
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Encode SETATTR arguments&n; */
r_static
r_int
DECL|function|nfs_xdr_sattrargs
id|nfs_xdr_sattrargs
c_func
(paren
r_struct
id|rpc_rqst
op_star
id|req
comma
id|u32
op_star
id|p
comma
r_struct
id|nfs_sattrargs
op_star
id|args
)paren
(brace
id|p
op_assign
id|xdr_encode_fhandle
c_func
(paren
id|p
comma
id|args-&gt;fh
)paren
suffix:semicolon
id|p
op_assign
id|xdr_encode_sattr
c_func
(paren
id|p
comma
id|args-&gt;sattr
)paren
suffix:semicolon
id|req-&gt;rq_slen
op_assign
id|xdr_adjust_iovec
c_func
(paren
id|req-&gt;rq_svec
comma
id|p
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Encode directory ops argument&n; * LOOKUP, REMOVE, RMDIR&n; */
r_static
r_int
DECL|function|nfs_xdr_diropargs
id|nfs_xdr_diropargs
c_func
(paren
r_struct
id|rpc_rqst
op_star
id|req
comma
id|u32
op_star
id|p
comma
r_struct
id|nfs_diropargs
op_star
id|args
)paren
(brace
id|p
op_assign
id|xdr_encode_fhandle
c_func
(paren
id|p
comma
id|args-&gt;fh
)paren
suffix:semicolon
id|p
op_assign
id|xdr_encode_array
c_func
(paren
id|p
comma
id|args-&gt;name
comma
id|args-&gt;len
)paren
suffix:semicolon
id|req-&gt;rq_slen
op_assign
id|xdr_adjust_iovec
c_func
(paren
id|req-&gt;rq_svec
comma
id|p
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Arguments to a READ call. Since we read data directly into the page&n; * cache, we also set up the reply iovec here so that iov[1] points&n; * exactly to the page we want to fetch.&n; */
r_static
r_int
DECL|function|nfs_xdr_readargs
id|nfs_xdr_readargs
c_func
(paren
r_struct
id|rpc_rqst
op_star
id|req
comma
id|u32
op_star
id|p
comma
r_struct
id|nfs_readargs
op_star
id|args
)paren
(brace
r_struct
id|rpc_auth
op_star
id|auth
op_assign
id|req-&gt;rq_task-&gt;tk_auth
suffix:semicolon
r_int
r_int
id|replen
suffix:semicolon
id|u32
id|offset
op_assign
(paren
id|u32
)paren
id|args-&gt;offset
suffix:semicolon
id|u32
id|count
op_assign
id|args-&gt;count
suffix:semicolon
id|p
op_assign
id|xdr_encode_fhandle
c_func
(paren
id|p
comma
id|args-&gt;fh
)paren
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|htonl
c_func
(paren
id|offset
)paren
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|htonl
c_func
(paren
id|count
)paren
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|htonl
c_func
(paren
id|count
)paren
suffix:semicolon
id|req-&gt;rq_slen
op_assign
id|xdr_adjust_iovec
c_func
(paren
id|req-&gt;rq_svec
comma
id|p
)paren
suffix:semicolon
multiline_comment|/* Inline the page array */
id|replen
op_assign
(paren
id|RPC_REPHDRSIZE
op_plus
id|auth-&gt;au_rslack
op_plus
id|NFS_readres_sz
)paren
op_lshift
l_int|2
suffix:semicolon
id|xdr_inline_pages
c_func
(paren
op_amp
id|req-&gt;rq_rcv_buf
comma
id|replen
comma
id|args-&gt;pages
comma
id|args-&gt;pgbase
comma
id|count
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Decode READ reply&n; */
r_static
r_int
DECL|function|nfs_xdr_readres
id|nfs_xdr_readres
c_func
(paren
r_struct
id|rpc_rqst
op_star
id|req
comma
id|u32
op_star
id|p
comma
r_struct
id|nfs_readres
op_star
id|res
)paren
(brace
r_struct
id|iovec
op_star
id|iov
op_assign
id|req-&gt;rq_rvec
suffix:semicolon
r_int
id|status
comma
id|count
comma
id|recvd
comma
id|hdrlen
suffix:semicolon
r_if
c_cond
(paren
(paren
id|status
op_assign
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
)paren
)paren
r_return
op_minus
id|nfs_stat_to_errno
c_func
(paren
id|status
)paren
suffix:semicolon
id|p
op_assign
id|xdr_decode_fattr
c_func
(paren
id|p
comma
id|res-&gt;fattr
)paren
suffix:semicolon
id|count
op_assign
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
suffix:semicolon
id|res-&gt;eof
op_assign
l_int|0
suffix:semicolon
id|hdrlen
op_assign
(paren
id|u8
op_star
)paren
id|p
op_minus
(paren
id|u8
op_star
)paren
id|iov-&gt;iov_base
suffix:semicolon
r_if
c_cond
(paren
id|iov-&gt;iov_len
OL
id|hdrlen
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;NFS: READ reply header overflowed:&quot;
l_string|&quot;length %d &gt; %Zu&bslash;n&quot;
comma
id|hdrlen
comma
id|iov-&gt;iov_len
)paren
suffix:semicolon
r_return
op_minus
id|errno_NFSERR_IO
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|iov-&gt;iov_len
op_ne
id|hdrlen
)paren
(brace
id|dprintk
c_func
(paren
l_string|&quot;NFS: READ header is short. iovec will be shifted.&bslash;n&quot;
)paren
suffix:semicolon
id|xdr_shift_buf
c_func
(paren
op_amp
id|req-&gt;rq_rcv_buf
comma
id|iov-&gt;iov_len
op_minus
id|hdrlen
)paren
suffix:semicolon
)brace
id|recvd
op_assign
id|req-&gt;rq_received
op_minus
id|hdrlen
suffix:semicolon
r_if
c_cond
(paren
id|count
OG
id|recvd
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;NFS: server cheating in read reply: &quot;
l_string|&quot;count %d &gt; recvd %d&bslash;n&quot;
comma
id|count
comma
id|recvd
)paren
suffix:semicolon
id|count
op_assign
id|recvd
suffix:semicolon
)brace
id|dprintk
c_func
(paren
l_string|&quot;RPC:      readres OK count %d&bslash;n&quot;
comma
id|count
)paren
suffix:semicolon
r_if
c_cond
(paren
id|count
OL
id|res-&gt;count
)paren
id|res-&gt;count
op_assign
id|count
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
multiline_comment|/*&n; * Write arguments. Splice the buffer to be written into the iovec.&n; */
r_static
r_int
DECL|function|nfs_xdr_writeargs
id|nfs_xdr_writeargs
c_func
(paren
r_struct
id|rpc_rqst
op_star
id|req
comma
id|u32
op_star
id|p
comma
r_struct
id|nfs_writeargs
op_star
id|args
)paren
(brace
r_struct
id|xdr_buf
op_star
id|sndbuf
op_assign
op_amp
id|req-&gt;rq_snd_buf
suffix:semicolon
id|u32
id|offset
op_assign
(paren
id|u32
)paren
id|args-&gt;offset
suffix:semicolon
id|u32
id|count
op_assign
id|args-&gt;count
suffix:semicolon
id|p
op_assign
id|xdr_encode_fhandle
c_func
(paren
id|p
comma
id|args-&gt;fh
)paren
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|htonl
c_func
(paren
id|offset
)paren
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|htonl
c_func
(paren
id|offset
)paren
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|htonl
c_func
(paren
id|count
)paren
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|htonl
c_func
(paren
id|count
)paren
suffix:semicolon
id|sndbuf-&gt;len
op_assign
id|xdr_adjust_iovec
c_func
(paren
id|sndbuf-&gt;head
comma
id|p
)paren
suffix:semicolon
multiline_comment|/* Copy the page array */
id|xdr_encode_pages
c_func
(paren
id|sndbuf
comma
id|args-&gt;pages
comma
id|args-&gt;pgbase
comma
id|count
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Encode create arguments&n; * CREATE, MKDIR&n; */
r_static
r_int
DECL|function|nfs_xdr_createargs
id|nfs_xdr_createargs
c_func
(paren
r_struct
id|rpc_rqst
op_star
id|req
comma
id|u32
op_star
id|p
comma
r_struct
id|nfs_createargs
op_star
id|args
)paren
(brace
id|p
op_assign
id|xdr_encode_fhandle
c_func
(paren
id|p
comma
id|args-&gt;fh
)paren
suffix:semicolon
id|p
op_assign
id|xdr_encode_array
c_func
(paren
id|p
comma
id|args-&gt;name
comma
id|args-&gt;len
)paren
suffix:semicolon
id|p
op_assign
id|xdr_encode_sattr
c_func
(paren
id|p
comma
id|args-&gt;sattr
)paren
suffix:semicolon
id|req-&gt;rq_slen
op_assign
id|xdr_adjust_iovec
c_func
(paren
id|req-&gt;rq_svec
comma
id|p
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Encode RENAME arguments&n; */
r_static
r_int
DECL|function|nfs_xdr_renameargs
id|nfs_xdr_renameargs
c_func
(paren
r_struct
id|rpc_rqst
op_star
id|req
comma
id|u32
op_star
id|p
comma
r_struct
id|nfs_renameargs
op_star
id|args
)paren
(brace
id|p
op_assign
id|xdr_encode_fhandle
c_func
(paren
id|p
comma
id|args-&gt;fromfh
)paren
suffix:semicolon
id|p
op_assign
id|xdr_encode_array
c_func
(paren
id|p
comma
id|args-&gt;fromname
comma
id|args-&gt;fromlen
)paren
suffix:semicolon
id|p
op_assign
id|xdr_encode_fhandle
c_func
(paren
id|p
comma
id|args-&gt;tofh
)paren
suffix:semicolon
id|p
op_assign
id|xdr_encode_array
c_func
(paren
id|p
comma
id|args-&gt;toname
comma
id|args-&gt;tolen
)paren
suffix:semicolon
id|req-&gt;rq_slen
op_assign
id|xdr_adjust_iovec
c_func
(paren
id|req-&gt;rq_svec
comma
id|p
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Encode LINK arguments&n; */
r_static
r_int
DECL|function|nfs_xdr_linkargs
id|nfs_xdr_linkargs
c_func
(paren
r_struct
id|rpc_rqst
op_star
id|req
comma
id|u32
op_star
id|p
comma
r_struct
id|nfs_linkargs
op_star
id|args
)paren
(brace
id|p
op_assign
id|xdr_encode_fhandle
c_func
(paren
id|p
comma
id|args-&gt;fromfh
)paren
suffix:semicolon
id|p
op_assign
id|xdr_encode_fhandle
c_func
(paren
id|p
comma
id|args-&gt;tofh
)paren
suffix:semicolon
id|p
op_assign
id|xdr_encode_array
c_func
(paren
id|p
comma
id|args-&gt;toname
comma
id|args-&gt;tolen
)paren
suffix:semicolon
id|req-&gt;rq_slen
op_assign
id|xdr_adjust_iovec
c_func
(paren
id|req-&gt;rq_svec
comma
id|p
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Encode SYMLINK arguments&n; */
r_static
r_int
DECL|function|nfs_xdr_symlinkargs
id|nfs_xdr_symlinkargs
c_func
(paren
r_struct
id|rpc_rqst
op_star
id|req
comma
id|u32
op_star
id|p
comma
r_struct
id|nfs_symlinkargs
op_star
id|args
)paren
(brace
id|p
op_assign
id|xdr_encode_fhandle
c_func
(paren
id|p
comma
id|args-&gt;fromfh
)paren
suffix:semicolon
id|p
op_assign
id|xdr_encode_array
c_func
(paren
id|p
comma
id|args-&gt;fromname
comma
id|args-&gt;fromlen
)paren
suffix:semicolon
id|p
op_assign
id|xdr_encode_array
c_func
(paren
id|p
comma
id|args-&gt;topath
comma
id|args-&gt;tolen
)paren
suffix:semicolon
id|p
op_assign
id|xdr_encode_sattr
c_func
(paren
id|p
comma
id|args-&gt;sattr
)paren
suffix:semicolon
id|req-&gt;rq_slen
op_assign
id|xdr_adjust_iovec
c_func
(paren
id|req-&gt;rq_svec
comma
id|p
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Encode arguments to readdir call&n; */
r_static
r_int
DECL|function|nfs_xdr_readdirargs
id|nfs_xdr_readdirargs
c_func
(paren
r_struct
id|rpc_rqst
op_star
id|req
comma
id|u32
op_star
id|p
comma
r_struct
id|nfs_readdirargs
op_star
id|args
)paren
(brace
r_struct
id|rpc_task
op_star
id|task
op_assign
id|req-&gt;rq_task
suffix:semicolon
r_struct
id|rpc_auth
op_star
id|auth
op_assign
id|task-&gt;tk_auth
suffix:semicolon
r_int
r_int
id|replen
suffix:semicolon
id|u32
id|count
op_assign
id|args-&gt;count
suffix:semicolon
id|p
op_assign
id|xdr_encode_fhandle
c_func
(paren
id|p
comma
id|args-&gt;fh
)paren
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|htonl
c_func
(paren
id|args-&gt;cookie
)paren
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|htonl
c_func
(paren
id|count
)paren
suffix:semicolon
multiline_comment|/* see above */
id|req-&gt;rq_slen
op_assign
id|xdr_adjust_iovec
c_func
(paren
id|req-&gt;rq_svec
comma
id|p
)paren
suffix:semicolon
multiline_comment|/* Inline the page array */
id|replen
op_assign
(paren
id|RPC_REPHDRSIZE
op_plus
id|auth-&gt;au_rslack
op_plus
id|NFS_readdirres_sz
)paren
op_lshift
l_int|2
suffix:semicolon
id|xdr_inline_pages
c_func
(paren
op_amp
id|req-&gt;rq_rcv_buf
comma
id|replen
comma
id|args-&gt;pages
comma
l_int|0
comma
id|count
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Decode the result of a readdir call.&n; * We&squot;re not really decoding anymore, we just leave the buffer untouched&n; * and only check that it is syntactically correct.&n; * The real decoding happens in nfs_decode_entry below, called directly&n; * from nfs_readdir for each entry.&n; */
r_static
r_int
DECL|function|nfs_xdr_readdirres
id|nfs_xdr_readdirres
c_func
(paren
r_struct
id|rpc_rqst
op_star
id|req
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
r_struct
id|xdr_buf
op_star
id|rcvbuf
op_assign
op_amp
id|req-&gt;rq_rcv_buf
suffix:semicolon
r_struct
id|iovec
op_star
id|iov
op_assign
id|rcvbuf-&gt;head
suffix:semicolon
r_struct
id|page
op_star
op_star
id|page
suffix:semicolon
r_int
id|hdrlen
comma
id|recvd
suffix:semicolon
r_int
id|status
comma
id|nr
suffix:semicolon
r_int
r_int
id|len
comma
id|pglen
suffix:semicolon
id|u32
op_star
id|end
comma
op_star
id|entry
suffix:semicolon
r_if
c_cond
(paren
(paren
id|status
op_assign
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
)paren
)paren
r_return
op_minus
id|nfs_stat_to_errno
c_func
(paren
id|status
)paren
suffix:semicolon
id|hdrlen
op_assign
(paren
id|u8
op_star
)paren
id|p
op_minus
(paren
id|u8
op_star
)paren
id|iov-&gt;iov_base
suffix:semicolon
r_if
c_cond
(paren
id|iov-&gt;iov_len
OL
id|hdrlen
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;NFS: READDIR reply header overflowed:&quot;
l_string|&quot;length %d &gt; %Zu&bslash;n&quot;
comma
id|hdrlen
comma
id|iov-&gt;iov_len
)paren
suffix:semicolon
r_return
op_minus
id|errno_NFSERR_IO
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|iov-&gt;iov_len
op_ne
id|hdrlen
)paren
(brace
id|dprintk
c_func
(paren
l_string|&quot;NFS: READDIR header is short. iovec will be shifted.&bslash;n&quot;
)paren
suffix:semicolon
id|xdr_shift_buf
c_func
(paren
id|rcvbuf
comma
id|iov-&gt;iov_len
op_minus
id|hdrlen
)paren
suffix:semicolon
)brace
id|pglen
op_assign
id|rcvbuf-&gt;page_len
suffix:semicolon
id|recvd
op_assign
id|req-&gt;rq_received
op_minus
id|hdrlen
suffix:semicolon
r_if
c_cond
(paren
id|pglen
OG
id|recvd
)paren
id|pglen
op_assign
id|recvd
suffix:semicolon
id|page
op_assign
id|rcvbuf-&gt;pages
suffix:semicolon
id|p
op_assign
id|kmap
c_func
(paren
op_star
id|page
)paren
suffix:semicolon
id|end
op_assign
(paren
id|u32
op_star
)paren
(paren
(paren
r_char
op_star
)paren
id|p
op_plus
id|pglen
)paren
suffix:semicolon
id|entry
op_assign
id|p
suffix:semicolon
r_for
c_loop
(paren
id|nr
op_assign
l_int|0
suffix:semicolon
op_star
id|p
op_increment
suffix:semicolon
id|nr
op_increment
)paren
(brace
r_if
c_cond
(paren
id|p
op_plus
l_int|2
OG
id|end
)paren
r_goto
id|short_pkt
suffix:semicolon
id|p
op_increment
suffix:semicolon
multiline_comment|/* fileid */
id|len
op_assign
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
suffix:semicolon
id|p
op_add_assign
id|XDR_QUADLEN
c_func
(paren
id|len
)paren
op_plus
l_int|1
suffix:semicolon
multiline_comment|/* name plus cookie */
r_if
c_cond
(paren
id|len
OG
id|NFS2_MAXNAMLEN
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;NFS: giant filename in readdir (len 0x%x)!&bslash;n&quot;
comma
id|len
)paren
suffix:semicolon
r_goto
id|err_unmap
suffix:semicolon
)brace
r_if
c_cond
(paren
id|p
op_plus
l_int|2
OG
id|end
)paren
r_goto
id|short_pkt
suffix:semicolon
id|entry
op_assign
id|p
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|nr
op_logical_and
(paren
id|entry
(braket
l_int|0
)braket
op_ne
l_int|0
op_logical_or
id|entry
(braket
l_int|1
)braket
op_eq
l_int|0
)paren
)paren
r_goto
id|short_pkt
suffix:semicolon
id|out
suffix:colon
id|kunmap
c_func
(paren
op_star
id|page
)paren
suffix:semicolon
r_return
id|nr
suffix:semicolon
id|short_pkt
suffix:colon
id|entry
(braket
l_int|0
)braket
op_assign
id|entry
(braket
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* truncate listing ? */
r_if
c_cond
(paren
op_logical_neg
id|nr
)paren
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;NFS: readdir reply truncated!&bslash;n&quot;
)paren
suffix:semicolon
id|entry
(braket
l_int|1
)braket
op_assign
l_int|1
suffix:semicolon
)brace
r_goto
id|out
suffix:semicolon
id|err_unmap
suffix:colon
id|kunmap
c_func
(paren
op_star
id|page
)paren
suffix:semicolon
r_return
op_minus
id|errno_NFSERR_IO
suffix:semicolon
)brace
id|u32
op_star
DECL|function|nfs_decode_dirent
id|nfs_decode_dirent
c_func
(paren
id|u32
op_star
id|p
comma
r_struct
id|nfs_entry
op_star
id|entry
comma
r_int
id|plus
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
op_star
id|p
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
op_star
id|p
)paren
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|EAGAIN
)paren
suffix:semicolon
id|entry-&gt;eof
op_assign
l_int|1
suffix:semicolon
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|EBADCOOKIE
)paren
suffix:semicolon
)brace
id|entry-&gt;ino
op_assign
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
suffix:semicolon
id|entry-&gt;len
op_assign
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
suffix:semicolon
id|entry-&gt;name
op_assign
(paren
r_const
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
id|entry-&gt;len
)paren
suffix:semicolon
id|entry-&gt;prev_cookie
op_assign
id|entry-&gt;cookie
suffix:semicolon
id|entry-&gt;cookie
op_assign
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
suffix:semicolon
id|entry-&gt;eof
op_assign
op_logical_neg
id|p
(braket
l_int|0
)braket
op_logical_and
id|p
(braket
l_int|1
)braket
suffix:semicolon
r_return
id|p
suffix:semicolon
)brace
multiline_comment|/*&n; * NFS XDR decode functions&n; */
multiline_comment|/*&n; * Decode void reply&n; */
r_static
r_int
DECL|function|nfs_xdr_dec_void
id|nfs_xdr_dec_void
c_func
(paren
r_struct
id|rpc_rqst
op_star
id|req
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
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Decode simple status reply&n; */
r_static
r_int
DECL|function|nfs_xdr_stat
id|nfs_xdr_stat
c_func
(paren
r_struct
id|rpc_rqst
op_star
id|req
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
r_int
id|status
suffix:semicolon
r_if
c_cond
(paren
(paren
id|status
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
l_int|0
)paren
id|status
op_assign
op_minus
id|nfs_stat_to_errno
c_func
(paren
id|status
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
multiline_comment|/*&n; * Decode attrstat reply&n; * GETATTR, SETATTR, WRITE&n; */
r_static
r_int
DECL|function|nfs_xdr_attrstat
id|nfs_xdr_attrstat
c_func
(paren
r_struct
id|rpc_rqst
op_star
id|req
comma
id|u32
op_star
id|p
comma
r_struct
id|nfs_fattr
op_star
id|fattr
)paren
(brace
r_int
id|status
suffix:semicolon
r_if
c_cond
(paren
(paren
id|status
op_assign
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
)paren
)paren
r_return
op_minus
id|nfs_stat_to_errno
c_func
(paren
id|status
)paren
suffix:semicolon
id|xdr_decode_fattr
c_func
(paren
id|p
comma
id|fattr
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Decode diropres reply&n; * LOOKUP, CREATE, MKDIR&n; */
r_static
r_int
DECL|function|nfs_xdr_diropres
id|nfs_xdr_diropres
c_func
(paren
r_struct
id|rpc_rqst
op_star
id|req
comma
id|u32
op_star
id|p
comma
r_struct
id|nfs_diropok
op_star
id|res
)paren
(brace
r_int
id|status
suffix:semicolon
r_if
c_cond
(paren
(paren
id|status
op_assign
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
)paren
)paren
r_return
op_minus
id|nfs_stat_to_errno
c_func
(paren
id|status
)paren
suffix:semicolon
id|p
op_assign
id|xdr_decode_fhandle
c_func
(paren
id|p
comma
id|res-&gt;fh
)paren
suffix:semicolon
id|xdr_decode_fattr
c_func
(paren
id|p
comma
id|res-&gt;fattr
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Encode READLINK args&n; */
r_static
r_int
DECL|function|nfs_xdr_readlinkargs
id|nfs_xdr_readlinkargs
c_func
(paren
r_struct
id|rpc_rqst
op_star
id|req
comma
id|u32
op_star
id|p
comma
r_struct
id|nfs_readlinkargs
op_star
id|args
)paren
(brace
r_struct
id|rpc_auth
op_star
id|auth
op_assign
id|req-&gt;rq_task-&gt;tk_auth
suffix:semicolon
r_int
r_int
id|replen
suffix:semicolon
id|u32
id|count
op_assign
id|args-&gt;count
op_minus
l_int|4
suffix:semicolon
id|p
op_assign
id|xdr_encode_fhandle
c_func
(paren
id|p
comma
id|args-&gt;fh
)paren
suffix:semicolon
id|req-&gt;rq_slen
op_assign
id|xdr_adjust_iovec
c_func
(paren
id|req-&gt;rq_svec
comma
id|p
)paren
suffix:semicolon
multiline_comment|/* Inline the page array */
id|replen
op_assign
(paren
id|RPC_REPHDRSIZE
op_plus
id|auth-&gt;au_rslack
op_plus
id|NFS_readlinkres_sz
)paren
op_lshift
l_int|2
suffix:semicolon
id|xdr_inline_pages
c_func
(paren
op_amp
id|req-&gt;rq_rcv_buf
comma
id|replen
comma
id|args-&gt;pages
comma
l_int|0
comma
id|count
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Decode READLINK reply&n; */
r_static
r_int
DECL|function|nfs_xdr_readlinkres
id|nfs_xdr_readlinkres
c_func
(paren
r_struct
id|rpc_rqst
op_star
id|req
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
r_struct
id|xdr_buf
op_star
id|rcvbuf
op_assign
op_amp
id|req-&gt;rq_rcv_buf
suffix:semicolon
r_struct
id|iovec
op_star
id|iov
op_assign
id|rcvbuf-&gt;head
suffix:semicolon
r_int
r_int
id|hdrlen
suffix:semicolon
id|u32
op_star
id|strlen
comma
id|len
suffix:semicolon
r_char
op_star
id|string
suffix:semicolon
r_int
id|status
suffix:semicolon
r_if
c_cond
(paren
(paren
id|status
op_assign
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
)paren
)paren
r_return
op_minus
id|nfs_stat_to_errno
c_func
(paren
id|status
)paren
suffix:semicolon
id|hdrlen
op_assign
(paren
id|u8
op_star
)paren
id|p
op_minus
(paren
id|u8
op_star
)paren
id|iov-&gt;iov_base
suffix:semicolon
r_if
c_cond
(paren
id|iov-&gt;iov_len
OG
id|hdrlen
)paren
(brace
id|dprintk
c_func
(paren
l_string|&quot;NFS: READLINK header is short. iovec will be shifted.&bslash;n&quot;
)paren
suffix:semicolon
id|xdr_shift_buf
c_func
(paren
id|rcvbuf
comma
id|iov-&gt;iov_len
op_minus
id|hdrlen
)paren
suffix:semicolon
)brace
id|strlen
op_assign
(paren
id|u32
op_star
)paren
id|kmap
c_func
(paren
id|rcvbuf-&gt;pages
(braket
l_int|0
)braket
)paren
suffix:semicolon
multiline_comment|/* Convert length of symlink */
id|len
op_assign
id|ntohl
c_func
(paren
op_star
id|strlen
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
id|rcvbuf-&gt;page_len
)paren
id|len
op_assign
id|rcvbuf-&gt;page_len
suffix:semicolon
op_star
id|strlen
op_assign
id|len
suffix:semicolon
multiline_comment|/* NULL terminate the string we got */
id|string
op_assign
(paren
r_char
op_star
)paren
(paren
id|strlen
op_plus
l_int|1
)paren
suffix:semicolon
id|string
(braket
id|len
)braket
op_assign
l_int|0
suffix:semicolon
id|kunmap
c_func
(paren
id|rcvbuf-&gt;pages
(braket
l_int|0
)braket
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Decode WRITE reply&n; */
r_static
r_int
DECL|function|nfs_xdr_writeres
id|nfs_xdr_writeres
c_func
(paren
r_struct
id|rpc_rqst
op_star
id|req
comma
id|u32
op_star
id|p
comma
r_struct
id|nfs_writeres
op_star
id|res
)paren
(brace
id|res-&gt;verf-&gt;committed
op_assign
id|NFS_FILE_SYNC
suffix:semicolon
r_return
id|nfs_xdr_attrstat
c_func
(paren
id|req
comma
id|p
comma
id|res-&gt;fattr
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Decode STATFS reply&n; */
r_static
r_int
DECL|function|nfs_xdr_statfsres
id|nfs_xdr_statfsres
c_func
(paren
r_struct
id|rpc_rqst
op_star
id|req
comma
id|u32
op_star
id|p
comma
r_struct
id|nfs2_fsstat
op_star
id|res
)paren
(brace
r_int
id|status
suffix:semicolon
r_if
c_cond
(paren
(paren
id|status
op_assign
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
)paren
)paren
r_return
op_minus
id|nfs_stat_to_errno
c_func
(paren
id|status
)paren
suffix:semicolon
id|res-&gt;tsize
op_assign
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
suffix:semicolon
id|res-&gt;bsize
op_assign
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
suffix:semicolon
id|res-&gt;blocks
op_assign
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
suffix:semicolon
id|res-&gt;bfree
op_assign
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
suffix:semicolon
id|res-&gt;bavail
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
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * We need to translate between nfs status return values and&n; * the local errno values which may not be the same.&n; */
r_static
r_struct
(brace
DECL|member|stat
r_int
id|stat
suffix:semicolon
DECL|member|errno
r_int
id|errno
suffix:semicolon
DECL|variable|nfs_errtbl
)brace
id|nfs_errtbl
(braket
)braket
op_assign
(brace
(brace
id|NFS_OK
comma
l_int|0
)brace
comma
(brace
id|NFSERR_PERM
comma
id|EPERM
)brace
comma
(brace
id|NFSERR_NOENT
comma
id|ENOENT
)brace
comma
(brace
id|NFSERR_IO
comma
id|errno_NFSERR_IO
)brace
comma
(brace
id|NFSERR_NXIO
comma
id|ENXIO
)brace
comma
multiline_comment|/*&t;{ NFSERR_EAGAIN,&t;EAGAIN&t;&t;}, */
(brace
id|NFSERR_ACCES
comma
id|EACCES
)brace
comma
(brace
id|NFSERR_EXIST
comma
id|EEXIST
)brace
comma
(brace
id|NFSERR_XDEV
comma
id|EXDEV
)brace
comma
(brace
id|NFSERR_NODEV
comma
id|ENODEV
)brace
comma
(brace
id|NFSERR_NOTDIR
comma
id|ENOTDIR
)brace
comma
(brace
id|NFSERR_ISDIR
comma
id|EISDIR
)brace
comma
(brace
id|NFSERR_INVAL
comma
id|EINVAL
)brace
comma
(brace
id|NFSERR_FBIG
comma
id|EFBIG
)brace
comma
(brace
id|NFSERR_NOSPC
comma
id|ENOSPC
)brace
comma
(brace
id|NFSERR_ROFS
comma
id|EROFS
)brace
comma
(brace
id|NFSERR_MLINK
comma
id|EMLINK
)brace
comma
(brace
id|NFSERR_NAMETOOLONG
comma
id|ENAMETOOLONG
)brace
comma
(brace
id|NFSERR_NOTEMPTY
comma
id|ENOTEMPTY
)brace
comma
(brace
id|NFSERR_DQUOT
comma
id|EDQUOT
)brace
comma
(brace
id|NFSERR_STALE
comma
id|ESTALE
)brace
comma
(brace
id|NFSERR_REMOTE
comma
id|EREMOTE
)brace
comma
macro_line|#ifdef EWFLUSH
(brace
id|NFSERR_WFLUSH
comma
id|EWFLUSH
)brace
comma
macro_line|#endif
(brace
id|NFSERR_BADHANDLE
comma
id|EBADHANDLE
)brace
comma
(brace
id|NFSERR_NOT_SYNC
comma
id|ENOTSYNC
)brace
comma
(brace
id|NFSERR_BAD_COOKIE
comma
id|EBADCOOKIE
)brace
comma
(brace
id|NFSERR_NOTSUPP
comma
id|ENOTSUPP
)brace
comma
(brace
id|NFSERR_TOOSMALL
comma
id|ETOOSMALL
)brace
comma
(brace
id|NFSERR_SERVERFAULT
comma
id|ESERVERFAULT
)brace
comma
(brace
id|NFSERR_BADTYPE
comma
id|EBADTYPE
)brace
comma
(brace
id|NFSERR_JUKEBOX
comma
id|EJUKEBOX
)brace
comma
(brace
op_minus
l_int|1
comma
id|EIO
)brace
)brace
suffix:semicolon
multiline_comment|/*&n; * Convert an NFS error code to a local one.&n; * This one is used jointly by NFSv2 and NFSv3.&n; */
r_int
DECL|function|nfs_stat_to_errno
id|nfs_stat_to_errno
c_func
(paren
r_int
id|stat
)paren
(brace
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|nfs_errtbl
(braket
id|i
)braket
dot
id|stat
op_ne
op_minus
l_int|1
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|nfs_errtbl
(braket
id|i
)braket
dot
id|stat
op_eq
id|stat
)paren
r_return
id|nfs_errtbl
(braket
id|i
)braket
dot
id|errno
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;nfs_stat_to_errno: bad nfs status return value: %d&bslash;n&quot;
comma
id|stat
)paren
suffix:semicolon
r_return
id|nfs_errtbl
(braket
id|i
)braket
dot
id|errno
suffix:semicolon
)brace
macro_line|#ifndef MAX
DECL|macro|MAX
macro_line|# define MAX(a, b)&t;(((a) &gt; (b))? (a) : (b))
macro_line|#endif
DECL|macro|PROC
mdefine_line|#define PROC(proc, argtype, restype, timer)&t;&t;&t;&t;&bslash;&n;    { .p_procname =  &quot;nfs_&quot; #proc,&t;&t;&t;&t;&t;&bslash;&n;      .p_encode   =  (kxdrproc_t) nfs_xdr_##argtype,&t;&t;&t;&bslash;&n;      .p_decode   =  (kxdrproc_t) nfs_xdr_##restype,&t;&t;&t;&bslash;&n;      .p_bufsiz   =  MAX(NFS_##argtype##_sz,NFS_##restype##_sz) &lt;&lt; 2,&t;&bslash;&n;      .p_timer    =  timer&t;&t;&t;&t;&t;&t;&bslash;&n;    }
DECL|variable|nfs_procedures
r_static
r_struct
id|rpc_procinfo
id|nfs_procedures
(braket
l_int|18
)braket
op_assign
(brace
id|PROC
c_func
(paren
id|null
comma
id|enc_void
comma
id|dec_void
comma
l_int|0
)paren
comma
id|PROC
c_func
(paren
id|getattr
comma
id|fhandle
comma
id|attrstat
comma
l_int|1
)paren
comma
id|PROC
c_func
(paren
id|setattr
comma
id|sattrargs
comma
id|attrstat
comma
l_int|0
)paren
comma
id|PROC
c_func
(paren
id|root
comma
id|enc_void
comma
id|dec_void
comma
l_int|0
)paren
comma
id|PROC
c_func
(paren
id|lookup
comma
id|diropargs
comma
id|diropres
comma
l_int|2
)paren
comma
id|PROC
c_func
(paren
id|readlink
comma
id|readlinkargs
comma
id|readlinkres
comma
l_int|3
)paren
comma
id|PROC
c_func
(paren
id|read
comma
id|readargs
comma
id|readres
comma
l_int|3
)paren
comma
id|PROC
c_func
(paren
id|writecache
comma
id|enc_void
comma
id|dec_void
comma
l_int|0
)paren
comma
id|PROC
c_func
(paren
id|write
comma
id|writeargs
comma
id|writeres
comma
l_int|4
)paren
comma
id|PROC
c_func
(paren
id|create
comma
id|createargs
comma
id|diropres
comma
l_int|0
)paren
comma
id|PROC
c_func
(paren
id|remove
comma
id|diropargs
comma
id|stat
comma
l_int|0
)paren
comma
id|PROC
c_func
(paren
id|rename
comma
id|renameargs
comma
id|stat
comma
l_int|0
)paren
comma
id|PROC
c_func
(paren
id|link
comma
id|linkargs
comma
id|stat
comma
l_int|0
)paren
comma
id|PROC
c_func
(paren
id|symlink
comma
id|symlinkargs
comma
id|stat
comma
l_int|0
)paren
comma
id|PROC
c_func
(paren
id|mkdir
comma
id|createargs
comma
id|diropres
comma
l_int|0
)paren
comma
id|PROC
c_func
(paren
id|rmdir
comma
id|diropargs
comma
id|stat
comma
l_int|0
)paren
comma
id|PROC
c_func
(paren
id|readdir
comma
id|readdirargs
comma
id|readdirres
comma
l_int|3
)paren
comma
id|PROC
c_func
(paren
id|statfs
comma
id|fhandle
comma
id|statfsres
comma
l_int|0
)paren
comma
)brace
suffix:semicolon
DECL|variable|nfs_version2
r_struct
id|rpc_version
id|nfs_version2
op_assign
(brace
dot
id|number
op_assign
l_int|2
comma
dot
id|nrprocs
op_assign
r_sizeof
(paren
id|nfs_procedures
)paren
op_div
r_sizeof
(paren
id|nfs_procedures
(braket
l_int|0
)braket
)paren
comma
dot
id|procs
op_assign
id|nfs_procedures
)brace
suffix:semicolon
eof
