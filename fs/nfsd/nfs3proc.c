multiline_comment|/*&n; * linux/fs/nfsd/nfs3proc.c&n; *&n; * Process version 3 NFS requests.&n; *&n; * Copyright (C) 1996, 1997, 1998 Olaf Kirch &lt;okir@monad.swb.de&gt;&n; */
macro_line|#include &lt;linux/linkage.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/ext2_fs.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/net.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/sunrpc/svc.h&gt;
macro_line|#include &lt;linux/nfsd/nfsd.h&gt;
macro_line|#include &lt;linux/nfsd/cache.h&gt;
macro_line|#include &lt;linux/nfsd/xdr3.h&gt;
macro_line|#include &lt;linux/nfs3.h&gt;
DECL|macro|NFSDDBG_FACILITY
mdefine_line|#define NFSDDBG_FACILITY&t;&t;NFSDDBG_PROC
DECL|macro|RETURN_STATUS
mdefine_line|#define RETURN_STATUS(st)&t;{ resp-&gt;status = (st); return (st); }
DECL|variable|nfs3_ftypes
r_static
r_int
id|nfs3_ftypes
(braket
)braket
op_assign
(brace
l_int|0
comma
multiline_comment|/* NF3NON */
id|S_IFREG
comma
multiline_comment|/* NF3REG */
id|S_IFDIR
comma
multiline_comment|/* NF3DIR */
id|S_IFBLK
comma
multiline_comment|/* NF3BLK */
id|S_IFCHR
comma
multiline_comment|/* NF3CHR */
id|S_IFLNK
comma
multiline_comment|/* NF3LNK */
id|S_IFSOCK
comma
multiline_comment|/* NF3SOCK */
id|S_IFIFO
comma
multiline_comment|/* NF3FIFO */
)brace
suffix:semicolon
multiline_comment|/*&n; * Reserve room in the send buffer&n; */
r_static
r_inline
r_void
DECL|function|svcbuf_reserve
id|svcbuf_reserve
c_func
(paren
r_struct
id|xdr_buf
op_star
id|buf
comma
id|u32
op_star
op_star
id|ptr
comma
r_int
op_star
id|len
comma
r_int
id|nr
)paren
(brace
op_star
id|ptr
op_assign
(paren
id|u32
op_star
)paren
(paren
id|buf-&gt;head
(braket
l_int|0
)braket
dot
id|iov_base
op_plus
id|buf-&gt;head
(braket
l_int|0
)braket
dot
id|iov_len
)paren
op_plus
id|nr
suffix:semicolon
op_star
id|len
op_assign
(paren
(paren
id|PAGE_SIZE
op_minus
id|buf-&gt;head
(braket
l_int|0
)braket
dot
id|iov_len
)paren
op_rshift
l_int|2
)paren
op_minus
id|nr
suffix:semicolon
)brace
multiline_comment|/*&n; * NULL call.&n; */
r_static
r_int
DECL|function|nfsd3_proc_null
id|nfsd3_proc_null
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
r_void
op_star
id|argp
comma
r_void
op_star
id|resp
)paren
(brace
r_return
id|nfs_ok
suffix:semicolon
)brace
multiline_comment|/*&n; * Get a file&squot;s attributes&n; */
r_static
r_int
DECL|function|nfsd3_proc_getattr
id|nfsd3_proc_getattr
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
r_struct
id|nfsd_fhandle
op_star
id|argp
comma
r_struct
id|nfsd3_attrstat
op_star
id|resp
)paren
(brace
r_int
id|nfserr
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;nfsd: GETATTR(3)  %s&bslash;n&quot;
comma
id|SVCFH_fmt
c_func
(paren
op_amp
id|argp-&gt;fh
)paren
)paren
suffix:semicolon
id|fh_copy
c_func
(paren
op_amp
id|resp-&gt;fh
comma
op_amp
id|argp-&gt;fh
)paren
suffix:semicolon
id|nfserr
op_assign
id|fh_verify
c_func
(paren
id|rqstp
comma
op_amp
id|resp-&gt;fh
comma
l_int|0
comma
id|MAY_NOP
)paren
suffix:semicolon
id|RETURN_STATUS
c_func
(paren
id|nfserr
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Set a file&squot;s attributes&n; */
r_static
r_int
DECL|function|nfsd3_proc_setattr
id|nfsd3_proc_setattr
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
r_struct
id|nfsd3_sattrargs
op_star
id|argp
comma
r_struct
id|nfsd3_attrstat
op_star
id|resp
)paren
(brace
r_int
id|nfserr
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;nfsd: SETATTR(3)  %s&bslash;n&quot;
comma
id|SVCFH_fmt
c_func
(paren
op_amp
id|argp-&gt;fh
)paren
)paren
suffix:semicolon
id|fh_copy
c_func
(paren
op_amp
id|resp-&gt;fh
comma
op_amp
id|argp-&gt;fh
)paren
suffix:semicolon
id|nfserr
op_assign
id|nfsd_setattr
c_func
(paren
id|rqstp
comma
op_amp
id|resp-&gt;fh
comma
op_amp
id|argp-&gt;attrs
comma
id|argp-&gt;check_guard
comma
id|argp-&gt;guardtime
)paren
suffix:semicolon
id|RETURN_STATUS
c_func
(paren
id|nfserr
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Look up a path name component&n; */
r_static
r_int
DECL|function|nfsd3_proc_lookup
id|nfsd3_proc_lookup
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
r_struct
id|nfsd3_diropargs
op_star
id|argp
comma
r_struct
id|nfsd3_diropres
op_star
id|resp
)paren
(brace
r_int
id|nfserr
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;nfsd: LOOKUP(3)   %s %.*s&bslash;n&quot;
comma
id|SVCFH_fmt
c_func
(paren
op_amp
id|argp-&gt;fh
)paren
comma
id|argp-&gt;len
comma
id|argp-&gt;name
)paren
suffix:semicolon
id|fh_copy
c_func
(paren
op_amp
id|resp-&gt;dirfh
comma
op_amp
id|argp-&gt;fh
)paren
suffix:semicolon
id|fh_init
c_func
(paren
op_amp
id|resp-&gt;fh
comma
id|NFS3_FHSIZE
)paren
suffix:semicolon
id|nfserr
op_assign
id|nfsd_lookup
c_func
(paren
id|rqstp
comma
op_amp
id|resp-&gt;dirfh
comma
id|argp-&gt;name
comma
id|argp-&gt;len
comma
op_amp
id|resp-&gt;fh
)paren
suffix:semicolon
id|RETURN_STATUS
c_func
(paren
id|nfserr
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Check file access&n; */
r_static
r_int
DECL|function|nfsd3_proc_access
id|nfsd3_proc_access
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
r_struct
id|nfsd3_accessargs
op_star
id|argp
comma
r_struct
id|nfsd3_accessres
op_star
id|resp
)paren
(brace
r_int
id|nfserr
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;nfsd: ACCESS(3)   %s 0x%x&bslash;n&quot;
comma
id|SVCFH_fmt
c_func
(paren
op_amp
id|argp-&gt;fh
)paren
comma
id|argp-&gt;access
)paren
suffix:semicolon
id|fh_copy
c_func
(paren
op_amp
id|resp-&gt;fh
comma
op_amp
id|argp-&gt;fh
)paren
suffix:semicolon
id|resp-&gt;access
op_assign
id|argp-&gt;access
suffix:semicolon
id|nfserr
op_assign
id|nfsd_access
c_func
(paren
id|rqstp
comma
op_amp
id|resp-&gt;fh
comma
op_amp
id|resp-&gt;access
comma
l_int|NULL
)paren
suffix:semicolon
id|RETURN_STATUS
c_func
(paren
id|nfserr
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Read a symlink.&n; */
r_static
r_int
DECL|function|nfsd3_proc_readlink
id|nfsd3_proc_readlink
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
r_struct
id|nfsd_fhandle
op_star
id|argp
comma
r_struct
id|nfsd3_readlinkres
op_star
id|resp
)paren
(brace
id|u32
op_star
id|path
suffix:semicolon
r_int
id|dummy
comma
id|nfserr
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;nfsd: READLINK(3) %s&bslash;n&quot;
comma
id|SVCFH_fmt
c_func
(paren
op_amp
id|argp-&gt;fh
)paren
)paren
suffix:semicolon
multiline_comment|/* Reserve room for status, post_op_attr, and path length */
id|svcbuf_reserve
c_func
(paren
op_amp
id|rqstp-&gt;rq_res
comma
op_amp
id|path
comma
op_amp
id|dummy
comma
l_int|1
op_plus
id|NFS3_POST_OP_ATTR_WORDS
op_plus
l_int|1
)paren
suffix:semicolon
multiline_comment|/* Read the symlink. */
id|fh_copy
c_func
(paren
op_amp
id|resp-&gt;fh
comma
op_amp
id|argp-&gt;fh
)paren
suffix:semicolon
id|resp-&gt;len
op_assign
id|NFS3_MAXPATHLEN
suffix:semicolon
id|nfserr
op_assign
id|nfsd_readlink
c_func
(paren
id|rqstp
comma
op_amp
id|resp-&gt;fh
comma
(paren
r_char
op_star
)paren
id|path
comma
op_amp
id|resp-&gt;len
)paren
suffix:semicolon
id|RETURN_STATUS
c_func
(paren
id|nfserr
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Read a portion of a file.&n; */
r_static
r_int
DECL|function|nfsd3_proc_read
id|nfsd3_proc_read
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
r_struct
id|nfsd3_readargs
op_star
id|argp
comma
r_struct
id|nfsd3_readres
op_star
id|resp
)paren
(brace
r_int
id|nfserr
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;nfsd: READ(3) %s %lu bytes at %lu&bslash;n&quot;
comma
id|SVCFH_fmt
c_func
(paren
op_amp
id|argp-&gt;fh
)paren
comma
(paren
r_int
r_int
)paren
id|argp-&gt;count
comma
(paren
r_int
r_int
)paren
id|argp-&gt;offset
)paren
suffix:semicolon
multiline_comment|/* Obtain buffer pointer for payload.&n;&t; * 1 (status) + 22 (post_op_attr) + 1 (count) + 1 (eof)&n;&t; * + 1 (xdr opaque byte count) = 26&n;&t; */
id|resp-&gt;count
op_assign
id|argp-&gt;count
suffix:semicolon
r_if
c_cond
(paren
id|NFSSVC_MAXBLKSIZE
OL
id|resp-&gt;count
)paren
id|resp-&gt;count
op_assign
id|NFSSVC_MAXBLKSIZE
suffix:semicolon
id|svc_reserve
c_func
(paren
id|rqstp
comma
(paren
(paren
l_int|1
op_plus
id|NFS3_POST_OP_ATTR_WORDS
op_plus
l_int|3
)paren
op_lshift
l_int|2
)paren
op_plus
id|resp-&gt;count
op_plus
l_int|4
)paren
suffix:semicolon
id|fh_copy
c_func
(paren
op_amp
id|resp-&gt;fh
comma
op_amp
id|argp-&gt;fh
)paren
suffix:semicolon
id|nfserr
op_assign
id|nfsd_read
c_func
(paren
id|rqstp
comma
op_amp
id|resp-&gt;fh
comma
id|argp-&gt;offset
comma
id|argp-&gt;vec
comma
id|argp-&gt;vlen
comma
op_amp
id|resp-&gt;count
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nfserr
op_eq
l_int|0
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|resp-&gt;fh.fh_dentry-&gt;d_inode
suffix:semicolon
id|resp-&gt;eof
op_assign
(paren
id|argp-&gt;offset
op_plus
id|resp-&gt;count
)paren
op_ge
id|inode-&gt;i_size
suffix:semicolon
)brace
id|RETURN_STATUS
c_func
(paren
id|nfserr
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Write data to a file&n; */
r_static
r_int
DECL|function|nfsd3_proc_write
id|nfsd3_proc_write
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
r_struct
id|nfsd3_writeargs
op_star
id|argp
comma
r_struct
id|nfsd3_writeres
op_star
id|resp
)paren
(brace
r_int
id|nfserr
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;nfsd: WRITE(3)    %s %d bytes at %ld%s&bslash;n&quot;
comma
id|SVCFH_fmt
c_func
(paren
op_amp
id|argp-&gt;fh
)paren
comma
id|argp-&gt;len
comma
(paren
r_int
r_int
)paren
id|argp-&gt;offset
comma
id|argp-&gt;stable
ques
c_cond
l_string|&quot; stable&quot;
suffix:colon
l_string|&quot;&quot;
)paren
suffix:semicolon
id|fh_copy
c_func
(paren
op_amp
id|resp-&gt;fh
comma
op_amp
id|argp-&gt;fh
)paren
suffix:semicolon
id|resp-&gt;committed
op_assign
id|argp-&gt;stable
suffix:semicolon
id|nfserr
op_assign
id|nfsd_write
c_func
(paren
id|rqstp
comma
op_amp
id|resp-&gt;fh
comma
id|argp-&gt;offset
comma
id|argp-&gt;vec
comma
id|argp-&gt;vlen
comma
id|argp-&gt;len
comma
op_amp
id|resp-&gt;committed
)paren
suffix:semicolon
id|resp-&gt;count
op_assign
id|argp-&gt;count
suffix:semicolon
id|RETURN_STATUS
c_func
(paren
id|nfserr
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * With NFSv3, CREATE processing is a lot easier than with NFSv2.&n; * At least in theory; we&squot;ll see how it fares in practice when the&n; * first reports about SunOS compatibility problems start to pour in...&n; */
r_static
r_int
DECL|function|nfsd3_proc_create
id|nfsd3_proc_create
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
r_struct
id|nfsd3_createargs
op_star
id|argp
comma
r_struct
id|nfsd3_diropres
op_star
id|resp
)paren
(brace
id|svc_fh
op_star
id|dirfhp
comma
op_star
id|newfhp
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|iattr
op_star
id|attr
suffix:semicolon
id|u32
id|nfserr
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;nfsd: CREATE(3)   %s %.*s&bslash;n&quot;
comma
id|SVCFH_fmt
c_func
(paren
op_amp
id|argp-&gt;fh
)paren
comma
id|argp-&gt;len
comma
id|argp-&gt;name
)paren
suffix:semicolon
id|dirfhp
op_assign
id|fh_copy
c_func
(paren
op_amp
id|resp-&gt;dirfh
comma
op_amp
id|argp-&gt;fh
)paren
suffix:semicolon
id|newfhp
op_assign
id|fh_init
c_func
(paren
op_amp
id|resp-&gt;fh
comma
id|NFS3_FHSIZE
)paren
suffix:semicolon
id|attr
op_assign
op_amp
id|argp-&gt;attrs
suffix:semicolon
multiline_comment|/* Get the directory inode */
id|nfserr
op_assign
id|fh_verify
c_func
(paren
id|rqstp
comma
id|dirfhp
comma
id|S_IFDIR
comma
id|MAY_CREATE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nfserr
)paren
id|RETURN_STATUS
c_func
(paren
id|nfserr
)paren
suffix:semicolon
multiline_comment|/* Unfudge the mode bits */
id|attr-&gt;ia_mode
op_and_assign
op_complement
id|S_IFMT
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|attr-&gt;ia_valid
op_amp
id|ATTR_MODE
)paren
)paren
(brace
id|attr-&gt;ia_valid
op_or_assign
id|ATTR_MODE
suffix:semicolon
id|attr-&gt;ia_mode
op_assign
id|S_IFREG
suffix:semicolon
)brace
r_else
(brace
id|attr-&gt;ia_mode
op_assign
(paren
id|attr-&gt;ia_mode
op_amp
op_complement
id|S_IFMT
)paren
op_or
id|S_IFREG
suffix:semicolon
)brace
multiline_comment|/* Now create the file and set attributes */
id|nfserr
op_assign
id|nfsd_create_v3
c_func
(paren
id|rqstp
comma
id|dirfhp
comma
id|argp-&gt;name
comma
id|argp-&gt;len
comma
id|attr
comma
id|newfhp
comma
id|argp-&gt;createmode
comma
id|argp-&gt;verf
comma
l_int|NULL
)paren
suffix:semicolon
id|RETURN_STATUS
c_func
(paren
id|nfserr
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Make directory. This operation is not idempotent.&n; */
r_static
r_int
DECL|function|nfsd3_proc_mkdir
id|nfsd3_proc_mkdir
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
r_struct
id|nfsd3_createargs
op_star
id|argp
comma
r_struct
id|nfsd3_diropres
op_star
id|resp
)paren
(brace
r_int
id|nfserr
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;nfsd: MKDIR(3)    %s %.*s&bslash;n&quot;
comma
id|SVCFH_fmt
c_func
(paren
op_amp
id|argp-&gt;fh
)paren
comma
id|argp-&gt;len
comma
id|argp-&gt;name
)paren
suffix:semicolon
id|argp-&gt;attrs.ia_valid
op_and_assign
op_complement
id|ATTR_SIZE
suffix:semicolon
id|fh_copy
c_func
(paren
op_amp
id|resp-&gt;dirfh
comma
op_amp
id|argp-&gt;fh
)paren
suffix:semicolon
id|fh_init
c_func
(paren
op_amp
id|resp-&gt;fh
comma
id|NFS3_FHSIZE
)paren
suffix:semicolon
id|nfserr
op_assign
id|nfsd_create
c_func
(paren
id|rqstp
comma
op_amp
id|resp-&gt;dirfh
comma
id|argp-&gt;name
comma
id|argp-&gt;len
comma
op_amp
id|argp-&gt;attrs
comma
id|S_IFDIR
comma
l_int|0
comma
op_amp
id|resp-&gt;fh
)paren
suffix:semicolon
id|RETURN_STATUS
c_func
(paren
id|nfserr
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|nfsd3_proc_symlink
id|nfsd3_proc_symlink
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
r_struct
id|nfsd3_symlinkargs
op_star
id|argp
comma
r_struct
id|nfsd3_diropres
op_star
id|resp
)paren
(brace
r_int
id|nfserr
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;nfsd: SYMLINK(3)  %s %.*s -&gt; %.*s&bslash;n&quot;
comma
id|SVCFH_fmt
c_func
(paren
op_amp
id|argp-&gt;ffh
)paren
comma
id|argp-&gt;flen
comma
id|argp-&gt;fname
comma
id|argp-&gt;tlen
comma
id|argp-&gt;tname
)paren
suffix:semicolon
id|fh_copy
c_func
(paren
op_amp
id|resp-&gt;dirfh
comma
op_amp
id|argp-&gt;ffh
)paren
suffix:semicolon
id|fh_init
c_func
(paren
op_amp
id|resp-&gt;fh
comma
id|NFS3_FHSIZE
)paren
suffix:semicolon
id|nfserr
op_assign
id|nfsd_symlink
c_func
(paren
id|rqstp
comma
op_amp
id|resp-&gt;dirfh
comma
id|argp-&gt;fname
comma
id|argp-&gt;flen
comma
id|argp-&gt;tname
comma
id|argp-&gt;tlen
comma
op_amp
id|resp-&gt;fh
comma
op_amp
id|argp-&gt;attrs
)paren
suffix:semicolon
id|RETURN_STATUS
c_func
(paren
id|nfserr
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Make socket/fifo/device.&n; */
r_static
r_int
DECL|function|nfsd3_proc_mknod
id|nfsd3_proc_mknod
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
r_struct
id|nfsd3_mknodargs
op_star
id|argp
comma
r_struct
id|nfsd3_diropres
op_star
id|resp
)paren
(brace
r_int
id|nfserr
comma
id|type
suffix:semicolon
id|dev_t
id|rdev
op_assign
l_int|0
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;nfsd: MKNOD(3)    %s %.*s&bslash;n&quot;
comma
id|SVCFH_fmt
c_func
(paren
op_amp
id|argp-&gt;fh
)paren
comma
id|argp-&gt;len
comma
id|argp-&gt;name
)paren
suffix:semicolon
id|fh_copy
c_func
(paren
op_amp
id|resp-&gt;dirfh
comma
op_amp
id|argp-&gt;fh
)paren
suffix:semicolon
id|fh_init
c_func
(paren
op_amp
id|resp-&gt;fh
comma
id|NFS3_FHSIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|argp-&gt;ftype
op_eq
l_int|0
op_logical_or
id|argp-&gt;ftype
op_ge
id|NF3BAD
)paren
id|RETURN_STATUS
c_func
(paren
id|nfserr_inval
)paren
suffix:semicolon
r_if
c_cond
(paren
id|argp-&gt;ftype
op_eq
id|NF3CHR
op_logical_or
id|argp-&gt;ftype
op_eq
id|NF3BLK
)paren
(brace
r_if
c_cond
(paren
(paren
id|argp-&gt;ftype
op_eq
id|NF3CHR
op_logical_and
id|argp-&gt;major
op_ge
id|MAX_CHRDEV
)paren
op_logical_or
(paren
id|argp-&gt;ftype
op_eq
id|NF3BLK
op_logical_and
id|argp-&gt;major
op_ge
id|MAX_BLKDEV
)paren
op_logical_or
id|argp-&gt;minor
OG
l_int|0xFF
)paren
id|RETURN_STATUS
c_func
(paren
id|nfserr_inval
)paren
suffix:semicolon
id|rdev
op_assign
id|MKDEV
c_func
(paren
id|argp-&gt;major
comma
id|argp-&gt;minor
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|argp-&gt;ftype
op_ne
id|NF3SOCK
op_logical_and
id|argp-&gt;ftype
op_ne
id|NF3FIFO
)paren
id|RETURN_STATUS
c_func
(paren
id|nfserr_inval
)paren
suffix:semicolon
id|type
op_assign
id|nfs3_ftypes
(braket
id|argp-&gt;ftype
)braket
suffix:semicolon
id|nfserr
op_assign
id|nfsd_create
c_func
(paren
id|rqstp
comma
op_amp
id|resp-&gt;dirfh
comma
id|argp-&gt;name
comma
id|argp-&gt;len
comma
op_amp
id|argp-&gt;attrs
comma
id|type
comma
id|rdev
comma
op_amp
id|resp-&gt;fh
)paren
suffix:semicolon
id|RETURN_STATUS
c_func
(paren
id|nfserr
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Remove file/fifo/socket etc.&n; */
r_static
r_int
DECL|function|nfsd3_proc_remove
id|nfsd3_proc_remove
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
r_struct
id|nfsd3_diropargs
op_star
id|argp
comma
r_struct
id|nfsd3_attrstat
op_star
id|resp
)paren
(brace
r_int
id|nfserr
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;nfsd: REMOVE(3)   %s %.*s&bslash;n&quot;
comma
id|SVCFH_fmt
c_func
(paren
op_amp
id|argp-&gt;fh
)paren
comma
id|argp-&gt;len
comma
id|argp-&gt;name
)paren
suffix:semicolon
multiline_comment|/* Unlink. -S_IFDIR means file must not be a directory */
id|fh_copy
c_func
(paren
op_amp
id|resp-&gt;fh
comma
op_amp
id|argp-&gt;fh
)paren
suffix:semicolon
id|nfserr
op_assign
id|nfsd_unlink
c_func
(paren
id|rqstp
comma
op_amp
id|resp-&gt;fh
comma
op_minus
id|S_IFDIR
comma
id|argp-&gt;name
comma
id|argp-&gt;len
)paren
suffix:semicolon
id|RETURN_STATUS
c_func
(paren
id|nfserr
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Remove a directory&n; */
r_static
r_int
DECL|function|nfsd3_proc_rmdir
id|nfsd3_proc_rmdir
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
r_struct
id|nfsd3_diropargs
op_star
id|argp
comma
r_struct
id|nfsd3_attrstat
op_star
id|resp
)paren
(brace
r_int
id|nfserr
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;nfsd: RMDIR(3)    %s %.*s&bslash;n&quot;
comma
id|SVCFH_fmt
c_func
(paren
op_amp
id|argp-&gt;fh
)paren
comma
id|argp-&gt;len
comma
id|argp-&gt;name
)paren
suffix:semicolon
id|fh_copy
c_func
(paren
op_amp
id|resp-&gt;fh
comma
op_amp
id|argp-&gt;fh
)paren
suffix:semicolon
id|nfserr
op_assign
id|nfsd_unlink
c_func
(paren
id|rqstp
comma
op_amp
id|resp-&gt;fh
comma
id|S_IFDIR
comma
id|argp-&gt;name
comma
id|argp-&gt;len
)paren
suffix:semicolon
id|RETURN_STATUS
c_func
(paren
id|nfserr
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|nfsd3_proc_rename
id|nfsd3_proc_rename
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
r_struct
id|nfsd3_renameargs
op_star
id|argp
comma
r_struct
id|nfsd3_renameres
op_star
id|resp
)paren
(brace
r_int
id|nfserr
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;nfsd: RENAME(3)   %s %.*s -&gt;&bslash;n&quot;
comma
id|SVCFH_fmt
c_func
(paren
op_amp
id|argp-&gt;ffh
)paren
comma
id|argp-&gt;flen
comma
id|argp-&gt;fname
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;nfsd: -&gt; %s %.*s&bslash;n&quot;
comma
id|SVCFH_fmt
c_func
(paren
op_amp
id|argp-&gt;tfh
)paren
comma
id|argp-&gt;tlen
comma
id|argp-&gt;tname
)paren
suffix:semicolon
id|fh_copy
c_func
(paren
op_amp
id|resp-&gt;ffh
comma
op_amp
id|argp-&gt;ffh
)paren
suffix:semicolon
id|fh_copy
c_func
(paren
op_amp
id|resp-&gt;tfh
comma
op_amp
id|argp-&gt;tfh
)paren
suffix:semicolon
id|nfserr
op_assign
id|nfsd_rename
c_func
(paren
id|rqstp
comma
op_amp
id|resp-&gt;ffh
comma
id|argp-&gt;fname
comma
id|argp-&gt;flen
comma
op_amp
id|resp-&gt;tfh
comma
id|argp-&gt;tname
comma
id|argp-&gt;tlen
)paren
suffix:semicolon
id|RETURN_STATUS
c_func
(paren
id|nfserr
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|nfsd3_proc_link
id|nfsd3_proc_link
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
r_struct
id|nfsd3_linkargs
op_star
id|argp
comma
r_struct
id|nfsd3_linkres
op_star
id|resp
)paren
(brace
r_int
id|nfserr
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;nfsd: LINK(3)     %s -&gt;&bslash;n&quot;
comma
id|SVCFH_fmt
c_func
(paren
op_amp
id|argp-&gt;ffh
)paren
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;nfsd:   -&gt; %s %.*s&bslash;n&quot;
comma
id|SVCFH_fmt
c_func
(paren
op_amp
id|argp-&gt;tfh
)paren
comma
id|argp-&gt;tlen
comma
id|argp-&gt;tname
)paren
suffix:semicolon
id|fh_copy
c_func
(paren
op_amp
id|resp-&gt;fh
comma
op_amp
id|argp-&gt;ffh
)paren
suffix:semicolon
id|fh_copy
c_func
(paren
op_amp
id|resp-&gt;tfh
comma
op_amp
id|argp-&gt;tfh
)paren
suffix:semicolon
id|nfserr
op_assign
id|nfsd_link
c_func
(paren
id|rqstp
comma
op_amp
id|resp-&gt;tfh
comma
id|argp-&gt;tname
comma
id|argp-&gt;tlen
comma
op_amp
id|resp-&gt;fh
)paren
suffix:semicolon
id|RETURN_STATUS
c_func
(paren
id|nfserr
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Read a portion of a directory.&n; */
r_static
r_int
DECL|function|nfsd3_proc_readdir
id|nfsd3_proc_readdir
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
r_struct
id|nfsd3_readdirargs
op_star
id|argp
comma
r_struct
id|nfsd3_readdirres
op_star
id|resp
)paren
(brace
id|u32
op_star
id|buffer
suffix:semicolon
r_int
id|nfserr
comma
id|count
suffix:semicolon
r_int
r_int
id|want
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;nfsd: READDIR(3)  %s %d bytes at %d&bslash;n&quot;
comma
id|SVCFH_fmt
c_func
(paren
op_amp
id|argp-&gt;fh
)paren
comma
id|argp-&gt;count
comma
(paren
id|u32
)paren
id|argp-&gt;cookie
)paren
suffix:semicolon
multiline_comment|/* Reserve buffer space for status, attributes and verifier */
id|svcbuf_reserve
c_func
(paren
op_amp
id|rqstp-&gt;rq_res
comma
op_amp
id|buffer
comma
op_amp
id|count
comma
l_int|1
op_plus
id|NFS3_POST_OP_ATTR_WORDS
op_plus
l_int|2
)paren
suffix:semicolon
multiline_comment|/* Make sure we&squot;ve room for the NULL ptr &amp; eof flag, and shrink to&n;&t; * client read size */
r_if
c_cond
(paren
(paren
id|count
op_sub_assign
l_int|2
)paren
OG
(paren
id|want
op_assign
(paren
id|argp-&gt;count
op_rshift
l_int|2
)paren
op_minus
l_int|2
)paren
)paren
id|count
op_assign
id|want
suffix:semicolon
multiline_comment|/* Read directory and encode entries on the fly */
id|fh_copy
c_func
(paren
op_amp
id|resp-&gt;fh
comma
op_amp
id|argp-&gt;fh
)paren
suffix:semicolon
id|resp-&gt;buflen
op_assign
id|count
suffix:semicolon
id|resp-&gt;common.err
op_assign
id|nfs_ok
suffix:semicolon
id|resp-&gt;buffer
op_assign
id|buffer
suffix:semicolon
id|resp-&gt;offset
op_assign
l_int|NULL
suffix:semicolon
id|resp-&gt;rqstp
op_assign
id|rqstp
suffix:semicolon
id|nfserr
op_assign
id|nfsd_readdir
c_func
(paren
id|rqstp
comma
op_amp
id|resp-&gt;fh
comma
(paren
id|loff_t
op_star
)paren
op_amp
id|argp-&gt;cookie
comma
op_amp
id|resp-&gt;common
comma
id|nfs3svc_encode_entry
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|resp-&gt;verf
comma
id|argp-&gt;verf
comma
l_int|8
)paren
suffix:semicolon
id|resp-&gt;count
op_assign
id|resp-&gt;buffer
op_minus
id|buffer
suffix:semicolon
r_if
c_cond
(paren
id|resp-&gt;offset
)paren
id|xdr_encode_hyper
c_func
(paren
id|resp-&gt;offset
comma
id|argp-&gt;cookie
)paren
suffix:semicolon
id|RETURN_STATUS
c_func
(paren
id|nfserr
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Read a portion of a directory, including file handles and attrs.&n; * For now, we choose to ignore the dircount parameter.&n; */
r_static
r_int
DECL|function|nfsd3_proc_readdirplus
id|nfsd3_proc_readdirplus
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
r_struct
id|nfsd3_readdirargs
op_star
id|argp
comma
r_struct
id|nfsd3_readdirres
op_star
id|resp
)paren
(brace
id|u32
op_star
id|buffer
suffix:semicolon
r_int
id|nfserr
comma
id|count
comma
id|want
suffix:semicolon
id|loff_t
id|offset
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;nfsd: READDIR+(3) %s %d bytes at %d&bslash;n&quot;
comma
id|SVCFH_fmt
c_func
(paren
op_amp
id|argp-&gt;fh
)paren
comma
id|argp-&gt;count
comma
(paren
id|u32
)paren
id|argp-&gt;cookie
)paren
suffix:semicolon
multiline_comment|/* Reserve buffer space for status, attributes and verifier */
id|svcbuf_reserve
c_func
(paren
op_amp
id|rqstp-&gt;rq_res
comma
op_amp
id|buffer
comma
op_amp
id|count
comma
l_int|1
op_plus
id|NFS3_POST_OP_ATTR_WORDS
op_plus
l_int|2
)paren
suffix:semicolon
multiline_comment|/* Make sure we&squot;ve room for the NULL ptr &amp; eof flag, and shrink to&n;&t; * client read size */
r_if
c_cond
(paren
(paren
id|count
op_sub_assign
l_int|2
)paren
OG
(paren
id|want
op_assign
id|argp-&gt;count
op_rshift
l_int|2
)paren
)paren
id|count
op_assign
id|want
suffix:semicolon
multiline_comment|/* Read directory and encode entries on the fly */
id|fh_copy
c_func
(paren
op_amp
id|resp-&gt;fh
comma
op_amp
id|argp-&gt;fh
)paren
suffix:semicolon
id|resp-&gt;buflen
op_assign
id|count
suffix:semicolon
id|resp-&gt;common.err
op_assign
id|nfs_ok
suffix:semicolon
id|resp-&gt;buffer
op_assign
id|buffer
suffix:semicolon
id|resp-&gt;rqstp
op_assign
id|rqstp
suffix:semicolon
id|offset
op_assign
id|argp-&gt;cookie
suffix:semicolon
id|nfserr
op_assign
id|nfsd_readdir
c_func
(paren
id|rqstp
comma
op_amp
id|resp-&gt;fh
comma
op_amp
id|offset
comma
op_amp
id|resp-&gt;common
comma
id|nfs3svc_encode_entry_plus
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|resp-&gt;verf
comma
id|argp-&gt;verf
comma
l_int|8
)paren
suffix:semicolon
id|resp-&gt;count
op_assign
id|resp-&gt;buffer
op_minus
id|buffer
suffix:semicolon
r_if
c_cond
(paren
id|resp-&gt;offset
)paren
id|xdr_encode_hyper
c_func
(paren
id|resp-&gt;offset
comma
id|offset
)paren
suffix:semicolon
id|RETURN_STATUS
c_func
(paren
id|nfserr
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Get file system stats&n; */
r_static
r_int
DECL|function|nfsd3_proc_fsstat
id|nfsd3_proc_fsstat
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
r_struct
id|nfsd_fhandle
op_star
id|argp
comma
r_struct
id|nfsd3_fsstatres
op_star
id|resp
)paren
(brace
r_int
id|nfserr
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;nfsd: FSSTAT(3)   %s&bslash;n&quot;
comma
id|SVCFH_fmt
c_func
(paren
op_amp
id|argp-&gt;fh
)paren
)paren
suffix:semicolon
id|nfserr
op_assign
id|nfsd_statfs
c_func
(paren
id|rqstp
comma
op_amp
id|argp-&gt;fh
comma
op_amp
id|resp-&gt;stats
)paren
suffix:semicolon
id|fh_put
c_func
(paren
op_amp
id|argp-&gt;fh
)paren
suffix:semicolon
id|RETURN_STATUS
c_func
(paren
id|nfserr
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Get file system info&n; */
r_static
r_int
DECL|function|nfsd3_proc_fsinfo
id|nfsd3_proc_fsinfo
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
r_struct
id|nfsd_fhandle
op_star
id|argp
comma
r_struct
id|nfsd3_fsinfores
op_star
id|resp
)paren
(brace
r_int
id|nfserr
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;nfsd: FSINFO(3)   %s&bslash;n&quot;
comma
id|SVCFH_fmt
c_func
(paren
op_amp
id|argp-&gt;fh
)paren
)paren
suffix:semicolon
id|resp-&gt;f_rtmax
op_assign
id|NFSSVC_MAXBLKSIZE
suffix:semicolon
id|resp-&gt;f_rtpref
op_assign
id|NFSSVC_MAXBLKSIZE
suffix:semicolon
id|resp-&gt;f_rtmult
op_assign
id|PAGE_SIZE
suffix:semicolon
id|resp-&gt;f_wtmax
op_assign
id|NFSSVC_MAXBLKSIZE
suffix:semicolon
id|resp-&gt;f_wtpref
op_assign
id|NFSSVC_MAXBLKSIZE
suffix:semicolon
id|resp-&gt;f_wtmult
op_assign
id|PAGE_SIZE
suffix:semicolon
id|resp-&gt;f_dtpref
op_assign
id|PAGE_SIZE
suffix:semicolon
id|resp-&gt;f_maxfilesize
op_assign
op_complement
(paren
id|u32
)paren
l_int|0
suffix:semicolon
id|resp-&gt;f_properties
op_assign
id|NFS3_FSF_DEFAULT
suffix:semicolon
id|nfserr
op_assign
id|fh_verify
c_func
(paren
id|rqstp
comma
op_amp
id|argp-&gt;fh
comma
l_int|0
comma
id|MAY_NOP
)paren
suffix:semicolon
multiline_comment|/* Check special features of the file system. May request&n;&t; * different read/write sizes for file systems known to have&n;&t; * problems with large blocks */
r_if
c_cond
(paren
id|nfserr
op_eq
l_int|0
)paren
(brace
r_struct
id|super_block
op_star
id|sb
op_assign
id|argp-&gt;fh.fh_dentry-&gt;d_inode-&gt;i_sb
suffix:semicolon
multiline_comment|/* Note that we don&squot;t care for remote fs&squot;s here */
r_if
c_cond
(paren
id|sb-&gt;s_magic
op_eq
l_int|0x4d44
multiline_comment|/* MSDOS_SUPER_MAGIC */
)paren
(brace
id|resp-&gt;f_properties
op_assign
id|NFS3_FSF_BILLYBOY
suffix:semicolon
)brace
id|resp-&gt;f_maxfilesize
op_assign
id|sb-&gt;s_maxbytes
suffix:semicolon
)brace
id|fh_put
c_func
(paren
op_amp
id|argp-&gt;fh
)paren
suffix:semicolon
id|RETURN_STATUS
c_func
(paren
id|nfserr
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Get pathconf info for the specified file&n; */
r_static
r_int
DECL|function|nfsd3_proc_pathconf
id|nfsd3_proc_pathconf
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
r_struct
id|nfsd_fhandle
op_star
id|argp
comma
r_struct
id|nfsd3_pathconfres
op_star
id|resp
)paren
(brace
r_int
id|nfserr
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;nfsd: PATHCONF(3) %s&bslash;n&quot;
comma
id|SVCFH_fmt
c_func
(paren
op_amp
id|argp-&gt;fh
)paren
)paren
suffix:semicolon
multiline_comment|/* Set default pathconf */
id|resp-&gt;p_link_max
op_assign
l_int|255
suffix:semicolon
multiline_comment|/* at least */
id|resp-&gt;p_name_max
op_assign
l_int|255
suffix:semicolon
multiline_comment|/* at least */
id|resp-&gt;p_no_trunc
op_assign
l_int|0
suffix:semicolon
id|resp-&gt;p_chown_restricted
op_assign
l_int|1
suffix:semicolon
id|resp-&gt;p_case_insensitive
op_assign
l_int|0
suffix:semicolon
id|resp-&gt;p_case_preserving
op_assign
l_int|1
suffix:semicolon
id|nfserr
op_assign
id|fh_verify
c_func
(paren
id|rqstp
comma
op_amp
id|argp-&gt;fh
comma
l_int|0
comma
id|MAY_NOP
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nfserr
op_eq
l_int|0
)paren
(brace
r_struct
id|super_block
op_star
id|sb
op_assign
id|argp-&gt;fh.fh_dentry-&gt;d_inode-&gt;i_sb
suffix:semicolon
multiline_comment|/* Note that we don&squot;t care for remote fs&squot;s here */
r_switch
c_cond
(paren
id|sb-&gt;s_magic
)paren
(brace
r_case
id|EXT2_SUPER_MAGIC
suffix:colon
id|resp-&gt;p_link_max
op_assign
id|EXT2_LINK_MAX
suffix:semicolon
id|resp-&gt;p_name_max
op_assign
id|EXT2_NAME_LEN
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x4d44
suffix:colon
multiline_comment|/* MSDOS_SUPER_MAGIC */
id|resp-&gt;p_case_insensitive
op_assign
l_int|1
suffix:semicolon
id|resp-&gt;p_case_preserving
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|fh_put
c_func
(paren
op_amp
id|argp-&gt;fh
)paren
suffix:semicolon
id|RETURN_STATUS
c_func
(paren
id|nfserr
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Commit a file (range) to stable storage.&n; */
r_static
r_int
DECL|function|nfsd3_proc_commit
id|nfsd3_proc_commit
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
r_struct
id|nfsd3_commitargs
op_star
id|argp
comma
r_struct
id|nfsd3_commitres
op_star
id|resp
)paren
(brace
r_int
id|nfserr
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;nfsd: COMMIT(3)   %s %d@%ld&bslash;n&quot;
comma
id|SVCFH_fmt
c_func
(paren
op_amp
id|argp-&gt;fh
)paren
comma
id|argp-&gt;count
comma
(paren
r_int
r_int
)paren
id|argp-&gt;offset
)paren
suffix:semicolon
r_if
c_cond
(paren
id|argp-&gt;offset
OG
id|NFS_OFFSET_MAX
)paren
id|RETURN_STATUS
c_func
(paren
id|nfserr_inval
)paren
suffix:semicolon
id|fh_copy
c_func
(paren
op_amp
id|resp-&gt;fh
comma
op_amp
id|argp-&gt;fh
)paren
suffix:semicolon
id|nfserr
op_assign
id|nfsd_commit
c_func
(paren
id|rqstp
comma
op_amp
id|resp-&gt;fh
comma
id|argp-&gt;offset
comma
id|argp-&gt;count
)paren
suffix:semicolon
id|RETURN_STATUS
c_func
(paren
id|nfserr
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * NFSv3 Server procedures.&n; * Only the results of non-idempotent operations are cached.&n; */
DECL|macro|nfs3svc_decode_voidargs
mdefine_line|#define nfs3svc_decode_voidargs&t;&t;NULL
DECL|macro|nfs3svc_release_void
mdefine_line|#define nfs3svc_release_void&t;&t;NULL
DECL|macro|nfs3svc_decode_fhandleargs
mdefine_line|#define nfs3svc_decode_fhandleargs&t;nfs3svc_decode_fhandle
DECL|macro|nfs3svc_encode_attrstatres
mdefine_line|#define nfs3svc_encode_attrstatres&t;nfs3svc_encode_attrstat
DECL|macro|nfs3svc_encode_wccstatres
mdefine_line|#define nfs3svc_encode_wccstatres&t;nfs3svc_encode_wccstat
DECL|macro|nfsd3_mkdirargs
mdefine_line|#define nfsd3_mkdirargs&t;&t;&t;nfsd3_createargs
DECL|macro|nfsd3_readdirplusargs
mdefine_line|#define nfsd3_readdirplusargs&t;&t;nfsd3_readdirargs
DECL|macro|nfsd3_fhandleargs
mdefine_line|#define nfsd3_fhandleargs&t;&t;nfsd_fhandle
DECL|macro|nfsd3_fhandleres
mdefine_line|#define nfsd3_fhandleres&t;&t;nfsd3_attrstat
DECL|macro|nfsd3_attrstatres
mdefine_line|#define nfsd3_attrstatres&t;&t;nfsd3_attrstat
DECL|macro|nfsd3_wccstatres
mdefine_line|#define nfsd3_wccstatres&t;&t;nfsd3_attrstat
DECL|macro|nfsd3_createres
mdefine_line|#define nfsd3_createres&t;&t;&t;nfsd3_diropres
DECL|macro|nfsd3_voidres
mdefine_line|#define nfsd3_voidres&t;&t;&t;nfsd3_voidargs
DECL|struct|nfsd3_voidargs
DECL|member|dummy
r_struct
id|nfsd3_voidargs
(brace
r_int
id|dummy
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|PROC
mdefine_line|#define PROC(name, argt, rest, relt, cache, respsize)&t;&bslash;&n; { (svc_procfunc) nfsd3_proc_##name,&t;&t;&bslash;&n;   (kxdrproc_t) nfs3svc_decode_##argt##args,&t;&bslash;&n;   (kxdrproc_t) nfs3svc_encode_##rest##res,&t;&bslash;&n;   (kxdrproc_t) nfs3svc_release_##relt,&t;&t;&bslash;&n;   sizeof(struct nfsd3_##argt##args),&t;&t;&bslash;&n;   sizeof(struct nfsd3_##rest##res),&t;&t;&bslash;&n;   0,&t;&t;&t;&t;&t;&t;&bslash;&n;   cache,&t;&t;&t;&t;&t;&bslash;&n;   respsize,&t;&t;&t;&t;&t;&bslash;&n; }
DECL|macro|ST
mdefine_line|#define ST 1&t;&t;/* status*/
DECL|macro|FH
mdefine_line|#define FH 17&t;&t;/* filehandle with length */
DECL|macro|AT
mdefine_line|#define AT 21&t;&t;/* attributes */
DECL|macro|pAT
mdefine_line|#define pAT (1+AT)&t;/* post attributes - conditional */
DECL|macro|WC
mdefine_line|#define WC (7+pAT)&t;/* WCC attributes */
DECL|variable|nfsd_procedures3
r_static
r_struct
id|svc_procedure
id|nfsd_procedures3
(braket
l_int|22
)braket
op_assign
(brace
id|PROC
c_func
(paren
id|null
comma
r_void
comma
r_void
comma
r_void
comma
id|RC_NOCACHE
comma
id|ST
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
id|fhandle
comma
id|RC_NOCACHE
comma
id|ST
op_plus
id|AT
)paren
comma
id|PROC
c_func
(paren
id|setattr
comma
id|sattr
comma
id|wccstat
comma
id|fhandle
comma
id|RC_REPLBUFF
comma
id|ST
op_plus
id|WC
)paren
comma
id|PROC
c_func
(paren
id|lookup
comma
id|dirop
comma
id|dirop
comma
id|fhandle2
comma
id|RC_NOCACHE
comma
id|ST
op_plus
id|FH
op_plus
id|pAT
op_plus
id|pAT
)paren
comma
id|PROC
c_func
(paren
id|access
comma
id|access
comma
id|access
comma
id|fhandle
comma
id|RC_NOCACHE
comma
id|ST
op_plus
id|pAT
op_plus
l_int|1
)paren
comma
id|PROC
c_func
(paren
id|readlink
comma
id|fhandle
comma
id|readlink
comma
id|fhandle
comma
id|RC_NOCACHE
comma
id|ST
op_plus
id|pAT
op_plus
l_int|1
op_plus
id|NFS3_MAXPATHLEN
op_div
l_int|4
)paren
comma
id|PROC
c_func
(paren
id|read
comma
id|read
comma
id|read
comma
id|fhandle
comma
id|RC_NOCACHE
comma
id|ST
op_plus
id|pAT
op_plus
l_int|4
op_plus
id|NFSSVC_MAXBLKSIZE
)paren
comma
id|PROC
c_func
(paren
id|write
comma
id|write
comma
id|write
comma
id|fhandle
comma
id|RC_REPLBUFF
comma
id|ST
op_plus
id|WC
op_plus
l_int|4
)paren
comma
id|PROC
c_func
(paren
id|create
comma
id|create
comma
id|create
comma
id|fhandle2
comma
id|RC_REPLBUFF
comma
id|ST
op_plus
(paren
l_int|1
op_plus
id|FH
op_plus
id|pAT
)paren
op_plus
id|WC
)paren
comma
id|PROC
c_func
(paren
id|mkdir
comma
id|mkdir
comma
id|create
comma
id|fhandle2
comma
id|RC_REPLBUFF
comma
id|ST
op_plus
(paren
l_int|1
op_plus
id|FH
op_plus
id|pAT
)paren
op_plus
id|WC
)paren
comma
id|PROC
c_func
(paren
id|symlink
comma
id|symlink
comma
id|create
comma
id|fhandle2
comma
id|RC_REPLBUFF
comma
id|ST
op_plus
(paren
l_int|1
op_plus
id|FH
op_plus
id|pAT
)paren
op_plus
id|WC
)paren
comma
id|PROC
c_func
(paren
id|mknod
comma
id|mknod
comma
id|create
comma
id|fhandle2
comma
id|RC_REPLBUFF
comma
id|ST
op_plus
(paren
l_int|1
op_plus
id|FH
op_plus
id|pAT
)paren
op_plus
id|WC
)paren
comma
id|PROC
c_func
(paren
id|remove
comma
id|dirop
comma
id|wccstat
comma
id|fhandle
comma
id|RC_REPLBUFF
comma
id|ST
op_plus
id|WC
)paren
comma
id|PROC
c_func
(paren
id|rmdir
comma
id|dirop
comma
id|wccstat
comma
id|fhandle
comma
id|RC_REPLBUFF
comma
id|ST
op_plus
id|WC
)paren
comma
id|PROC
c_func
(paren
id|rename
comma
id|rename
comma
id|rename
comma
id|fhandle2
comma
id|RC_REPLBUFF
comma
id|ST
op_plus
id|WC
op_plus
id|WC
)paren
comma
id|PROC
c_func
(paren
id|link
comma
id|link
comma
id|link
comma
id|fhandle2
comma
id|RC_REPLBUFF
comma
id|ST
op_plus
id|pAT
op_plus
id|WC
)paren
comma
id|PROC
c_func
(paren
id|readdir
comma
id|readdir
comma
id|readdir
comma
id|fhandle
comma
id|RC_NOCACHE
comma
l_int|0
)paren
comma
id|PROC
c_func
(paren
id|readdirplus
comma
id|readdirplus
comma
id|readdir
comma
id|fhandle
comma
id|RC_NOCACHE
comma
l_int|0
)paren
comma
id|PROC
c_func
(paren
id|fsstat
comma
id|fhandle
comma
id|fsstat
comma
r_void
comma
id|RC_NOCACHE
comma
id|ST
op_plus
id|pAT
op_plus
l_int|2
op_star
l_int|6
op_plus
l_int|1
)paren
comma
id|PROC
c_func
(paren
id|fsinfo
comma
id|fhandle
comma
id|fsinfo
comma
r_void
comma
id|RC_NOCACHE
comma
id|ST
op_plus
id|pAT
op_plus
l_int|12
)paren
comma
id|PROC
c_func
(paren
id|pathconf
comma
id|fhandle
comma
id|pathconf
comma
r_void
comma
id|RC_NOCACHE
comma
id|ST
op_plus
id|pAT
op_plus
l_int|6
)paren
comma
id|PROC
c_func
(paren
id|commit
comma
id|commit
comma
id|commit
comma
id|fhandle
comma
id|RC_NOCACHE
comma
id|ST
op_plus
id|WC
op_plus
l_int|2
)paren
comma
)brace
suffix:semicolon
DECL|variable|nfsd_version3
r_struct
id|svc_version
id|nfsd_version3
op_assign
(brace
dot
id|vs_vers
op_assign
l_int|3
comma
dot
id|vs_nproc
op_assign
l_int|22
comma
dot
id|vs_proc
op_assign
id|nfsd_procedures3
comma
dot
id|vs_dispatch
op_assign
id|nfsd_dispatch
comma
dot
id|vs_xdrsize
op_assign
id|NFS3_SVC_XDRSIZE
comma
)brace
suffix:semicolon
eof
