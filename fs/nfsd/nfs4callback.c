multiline_comment|/*&n; *  linux/fs/nfsd/nfs4callback.c&n; *&n; *  Copyright (c) 2001 The Regents of the University of Michigan.&n; *  All rights reserved.&n; *&n; *  Kendrick Smith &lt;kmsmith@umich.edu&gt;&n; *  Andy Adamson &lt;andros@umich.edu&gt;&n; *&n; *  Redistribution and use in source and binary forms, with or without&n; *  modification, are permitted provided that the following conditions&n; *  are met:&n; *&n; *  1. Redistributions of source code must retain the above copyright&n; *     notice, this list of conditions and the following disclaimer.&n; *  2. Redistributions in binary form must reproduce the above copyright&n; *     notice, this list of conditions and the following disclaimer in the&n; *     documentation and/or other materials provided with the distribution.&n; *  3. Neither the name of the University nor the names of its&n; *     contributors may be used to endorse or promote products derived&n; *     from this software without specific prior written permission.&n; *&n; *  THIS SOFTWARE IS PROVIDED ``AS IS&squot;&squot; AND ANY EXPRESS OR IMPLIED&n; *  WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF&n; *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE&n; *  DISCLAIMED. IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE&n; *  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR&n; *  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF&n; *  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR&n; *  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF&n; *  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING&n; *  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS&n; *  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/inet.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sunrpc/xdr.h&gt;
macro_line|#include &lt;linux/sunrpc/svc.h&gt;
macro_line|#include &lt;linux/sunrpc/clnt.h&gt;
macro_line|#include &lt;linux/nfsd/nfsd.h&gt;
macro_line|#include &lt;linux/nfsd/state.h&gt;
macro_line|#include &lt;linux/sunrpc/sched.h&gt;
macro_line|#include &lt;linux/nfs4.h&gt;
DECL|macro|NFSDDBG_FACILITY
mdefine_line|#define NFSDDBG_FACILITY                NFSDDBG_PROC
DECL|macro|NFSPROC4_CB_NULL
mdefine_line|#define NFSPROC4_CB_NULL 0
DECL|macro|NFSPROC4_CB_COMPOUND
mdefine_line|#define NFSPROC4_CB_COMPOUND 1
multiline_comment|/* declarations */
r_static
r_void
id|nfs4_cb_null
c_func
(paren
r_struct
id|rpc_task
op_star
id|task
)paren
suffix:semicolon
r_extern
id|spinlock_t
id|recall_lock
suffix:semicolon
multiline_comment|/* Index of predefined Linux callback client operations */
r_enum
(brace
DECL|enumerator|NFSPROC4_CLNT_CB_NULL
id|NFSPROC4_CLNT_CB_NULL
op_assign
l_int|0
comma
DECL|enumerator|NFSPROC4_CLNT_CB_RECALL
id|NFSPROC4_CLNT_CB_RECALL
comma
)brace
suffix:semicolon
DECL|enum|nfs_cb_opnum4
r_enum
id|nfs_cb_opnum4
(brace
DECL|enumerator|OP_CB_RECALL
id|OP_CB_RECALL
op_assign
l_int|4
comma
)brace
suffix:semicolon
DECL|macro|NFS4_MAXTAGLEN
mdefine_line|#define NFS4_MAXTAGLEN&t;&t;20
DECL|macro|NFS4_enc_cb_null_sz
mdefine_line|#define NFS4_enc_cb_null_sz&t;&t;0
DECL|macro|NFS4_dec_cb_null_sz
mdefine_line|#define NFS4_dec_cb_null_sz&t;&t;0
DECL|macro|cb_compound_enc_hdr_sz
mdefine_line|#define cb_compound_enc_hdr_sz&t;&t;4
DECL|macro|cb_compound_dec_hdr_sz
mdefine_line|#define cb_compound_dec_hdr_sz&t;&t;(3 + (NFS4_MAXTAGLEN &gt;&gt; 2))
DECL|macro|op_enc_sz
mdefine_line|#define op_enc_sz&t;&t;&t;1
DECL|macro|op_dec_sz
mdefine_line|#define op_dec_sz&t;&t;&t;2
DECL|macro|enc_nfs4_fh_sz
mdefine_line|#define enc_nfs4_fh_sz&t;&t;&t;(1 + (NFS4_FHSIZE &gt;&gt; 2))
DECL|macro|enc_stateid_sz
mdefine_line|#define enc_stateid_sz&t;&t;&t;16
DECL|macro|NFS4_enc_cb_recall_sz
mdefine_line|#define NFS4_enc_cb_recall_sz&t;&t;(cb_compound_enc_hdr_sz +       &bslash;&n;&t;&t;&t;&t;&t;1 + enc_stateid_sz +            &bslash;&n;&t;&t;&t;&t;&t;enc_nfs4_fh_sz)
DECL|macro|NFS4_dec_cb_recall_sz
mdefine_line|#define NFS4_dec_cb_recall_sz&t;&t;(cb_compound_dec_hdr_sz  +      &bslash;&n;&t;&t;&t;&t;&t;op_dec_sz)
multiline_comment|/*&n;* Generic encode routines from fs/nfs/nfs4xdr.c&n;*/
r_static
r_inline
id|u32
op_star
DECL|function|xdr_writemem
id|xdr_writemem
c_func
(paren
id|u32
op_star
id|p
comma
r_const
r_void
op_star
id|ptr
comma
r_int
id|nbytes
)paren
(brace
r_int
id|tmp
op_assign
id|XDR_QUADLEN
c_func
(paren
id|nbytes
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tmp
)paren
r_return
id|p
suffix:semicolon
id|p
(braket
id|tmp
op_minus
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
id|memcpy
c_func
(paren
id|p
comma
id|ptr
comma
id|nbytes
)paren
suffix:semicolon
r_return
id|p
op_plus
id|tmp
suffix:semicolon
)brace
DECL|macro|WRITE32
mdefine_line|#define WRITE32(n)               *p++ = htonl(n)
DECL|macro|WRITEMEM
mdefine_line|#define WRITEMEM(ptr,nbytes)     do {                           &bslash;&n;&t;p = xdr_writemem(p, ptr, nbytes);                       &bslash;&n;} while (0)
DECL|macro|RESERVE_SPACE
mdefine_line|#define RESERVE_SPACE(nbytes)   do {                            &bslash;&n;&t;p = xdr_reserve_space(xdr, nbytes);                     &bslash;&n;&t;if (!p) dprintk(&quot;NFSD: RESERVE_SPACE(%d) failed in function %s&bslash;n&quot;, (int) (nbytes), __FUNCTION__); &bslash;&n;&t;BUG_ON(!p);                                             &bslash;&n;} while (0)
multiline_comment|/*&n; * Generic decode routines from fs/nfs/nfs4xdr.c&n; */
DECL|macro|DECODE_TAIL
mdefine_line|#define DECODE_TAIL                             &bslash;&n;&t;status = 0;                             &bslash;&n;out:                                            &bslash;&n;&t;return status;                          &bslash;&n;xdr_error:                                      &bslash;&n;&t;dprintk(&quot;NFSD: xdr error! (%s:%d)&bslash;n&quot;, __FILE__, __LINE__); &bslash;&n;&t;status = -EIO;                          &bslash;&n;&t;goto out
DECL|macro|READ32
mdefine_line|#define READ32(x)         (x) = ntohl(*p++)
DECL|macro|READ64
mdefine_line|#define READ64(x)         do {                  &bslash;&n;&t;(x) = (u64)ntohl(*p++) &lt;&lt; 32;           &bslash;&n;&t;(x) |= ntohl(*p++);                     &bslash;&n;} while (0)
DECL|macro|READTIME
mdefine_line|#define READTIME(x)       do {                  &bslash;&n;&t;p++;                                    &bslash;&n;&t;(x.tv_sec) = ntohl(*p++);               &bslash;&n;&t;(x.tv_nsec) = ntohl(*p++);              &bslash;&n;} while (0)
DECL|macro|READ_BUF
mdefine_line|#define READ_BUF(nbytes)  do { &bslash;&n;&t;p = xdr_inline_decode(xdr, nbytes); &bslash;&n;&t;if (!p) { &bslash;&n;&t;&t;dprintk(&quot;NFSD: %s: reply buffer overflowed in line %d.&quot;, &bslash;&n;&t;&t;&t;__FUNCTION__, __LINE__); &bslash;&n;&t;&t;return -EIO; &bslash;&n;&t;} &bslash;&n;} while (0)
DECL|struct|nfs4_cb_compound_hdr
r_struct
id|nfs4_cb_compound_hdr
(brace
DECL|member|status
r_int
id|status
suffix:semicolon
DECL|member|ident
id|u32
id|ident
suffix:semicolon
DECL|member|nops
id|u32
id|nops
suffix:semicolon
DECL|member|taglen
id|u32
id|taglen
suffix:semicolon
DECL|member|tag
r_char
op_star
id|tag
suffix:semicolon
)brace
suffix:semicolon
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
DECL|variable|nfs_cb_errtbl
)brace
id|nfs_cb_errtbl
(braket
)braket
op_assign
(brace
(brace
id|NFS4_OK
comma
l_int|0
)brace
comma
(brace
id|NFS4ERR_PERM
comma
id|EPERM
)brace
comma
(brace
id|NFS4ERR_NOENT
comma
id|ENOENT
)brace
comma
(brace
id|NFS4ERR_IO
comma
id|EIO
)brace
comma
(brace
id|NFS4ERR_NXIO
comma
id|ENXIO
)brace
comma
(brace
id|NFS4ERR_ACCESS
comma
id|EACCES
)brace
comma
(brace
id|NFS4ERR_EXIST
comma
id|EEXIST
)brace
comma
(brace
id|NFS4ERR_XDEV
comma
id|EXDEV
)brace
comma
(brace
id|NFS4ERR_NOTDIR
comma
id|ENOTDIR
)brace
comma
(brace
id|NFS4ERR_ISDIR
comma
id|EISDIR
)brace
comma
(brace
id|NFS4ERR_INVAL
comma
id|EINVAL
)brace
comma
(brace
id|NFS4ERR_FBIG
comma
id|EFBIG
)brace
comma
(brace
id|NFS4ERR_NOSPC
comma
id|ENOSPC
)brace
comma
(brace
id|NFS4ERR_ROFS
comma
id|EROFS
)brace
comma
(brace
id|NFS4ERR_MLINK
comma
id|EMLINK
)brace
comma
(brace
id|NFS4ERR_NAMETOOLONG
comma
id|ENAMETOOLONG
)brace
comma
(brace
id|NFS4ERR_NOTEMPTY
comma
id|ENOTEMPTY
)brace
comma
(brace
id|NFS4ERR_DQUOT
comma
id|EDQUOT
)brace
comma
(brace
id|NFS4ERR_STALE
comma
id|ESTALE
)brace
comma
(brace
id|NFS4ERR_BADHANDLE
comma
id|EBADHANDLE
)brace
comma
(brace
id|NFS4ERR_BAD_COOKIE
comma
id|EBADCOOKIE
)brace
comma
(brace
id|NFS4ERR_NOTSUPP
comma
id|ENOTSUPP
)brace
comma
(brace
id|NFS4ERR_TOOSMALL
comma
id|ETOOSMALL
)brace
comma
(brace
id|NFS4ERR_SERVERFAULT
comma
id|ESERVERFAULT
)brace
comma
(brace
id|NFS4ERR_BADTYPE
comma
id|EBADTYPE
)brace
comma
(brace
id|NFS4ERR_LOCKED
comma
id|EAGAIN
)brace
comma
(brace
id|NFS4ERR_RESOURCE
comma
id|EREMOTEIO
)brace
comma
(brace
id|NFS4ERR_SYMLINK
comma
id|ELOOP
)brace
comma
(brace
id|NFS4ERR_OP_ILLEGAL
comma
id|EOPNOTSUPP
)brace
comma
(brace
id|NFS4ERR_DEADLOCK
comma
id|EDEADLK
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
r_static
r_int
DECL|function|nfs_cb_stat_to_errno
id|nfs_cb_stat_to_errno
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
id|nfs_cb_errtbl
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
id|nfs_cb_errtbl
(braket
id|i
)braket
dot
id|stat
op_eq
id|stat
)paren
r_return
id|nfs_cb_errtbl
(braket
id|i
)braket
dot
id|errno
suffix:semicolon
)brace
multiline_comment|/* If we cannot translate the error, the recovery routines should&n;&t;* handle it.&n;&t;* Note: remaining NFSv4 error codes have values &gt; 10000, so should&n;&t;* not conflict with native Linux error codes.&n;&t;*/
r_return
id|stat
suffix:semicolon
)brace
multiline_comment|/*&n; * XDR encode&n; */
r_static
r_int
DECL|function|encode_cb_compound_hdr
id|encode_cb_compound_hdr
c_func
(paren
r_struct
id|xdr_stream
op_star
id|xdr
comma
r_struct
id|nfs4_cb_compound_hdr
op_star
id|hdr
)paren
(brace
id|u32
op_star
id|p
suffix:semicolon
id|RESERVE_SPACE
c_func
(paren
l_int|16
)paren
suffix:semicolon
id|WRITE32
c_func
(paren
l_int|0
)paren
suffix:semicolon
multiline_comment|/* tag length is always 0 */
id|WRITE32
c_func
(paren
id|NFS4_MINOR_VERSION
)paren
suffix:semicolon
id|WRITE32
c_func
(paren
id|hdr-&gt;ident
)paren
suffix:semicolon
id|WRITE32
c_func
(paren
id|hdr-&gt;nops
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|encode_cb_recall
id|encode_cb_recall
c_func
(paren
r_struct
id|xdr_stream
op_star
id|xdr
comma
r_struct
id|nfs4_cb_recall
op_star
id|cb_rec
)paren
(brace
id|u32
op_star
id|p
suffix:semicolon
r_int
id|len
op_assign
id|cb_rec-&gt;cbr_fhlen
suffix:semicolon
id|RESERVE_SPACE
c_func
(paren
l_int|12
op_plus
r_sizeof
(paren
id|cb_rec-&gt;cbr_stateid
)paren
op_plus
id|len
)paren
suffix:semicolon
id|WRITE32
c_func
(paren
id|OP_CB_RECALL
)paren
suffix:semicolon
id|WRITEMEM
c_func
(paren
op_amp
id|cb_rec-&gt;cbr_stateid
comma
r_sizeof
(paren
id|stateid_t
)paren
)paren
suffix:semicolon
id|WRITE32
c_func
(paren
id|cb_rec-&gt;cbr_trunc
)paren
suffix:semicolon
id|WRITE32
c_func
(paren
id|len
)paren
suffix:semicolon
id|WRITEMEM
c_func
(paren
id|cb_rec-&gt;cbr_fhval
comma
id|len
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|nfs4_xdr_enc_cb_null
id|nfs4_xdr_enc_cb_null
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
)paren
(brace
r_struct
id|xdr_stream
id|xdrs
comma
op_star
id|xdr
op_assign
op_amp
id|xdrs
suffix:semicolon
id|xdr_init_encode
c_func
(paren
op_amp
id|xdrs
comma
op_amp
id|req-&gt;rq_snd_buf
comma
id|p
)paren
suffix:semicolon
id|RESERVE_SPACE
c_func
(paren
l_int|0
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|nfs4_xdr_enc_cb_recall
id|nfs4_xdr_enc_cb_recall
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
id|nfs4_cb_recall
op_star
id|args
)paren
(brace
r_struct
id|xdr_stream
id|xdr
suffix:semicolon
r_struct
id|nfs4_cb_compound_hdr
id|hdr
op_assign
(brace
dot
id|ident
op_assign
id|args-&gt;cbr_ident
comma
dot
id|nops
op_assign
l_int|1
comma
)brace
suffix:semicolon
id|xdr_init_encode
c_func
(paren
op_amp
id|xdr
comma
op_amp
id|req-&gt;rq_snd_buf
comma
id|p
)paren
suffix:semicolon
id|encode_cb_compound_hdr
c_func
(paren
op_amp
id|xdr
comma
op_amp
id|hdr
)paren
suffix:semicolon
r_return
(paren
id|encode_cb_recall
c_func
(paren
op_amp
id|xdr
comma
id|args
)paren
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|decode_cb_compound_hdr
(def_block
id|decode_cb_compound_hdr
c_func
(paren
r_struct
id|xdr_stream
op_star
id|xdr
comma
r_struct
id|nfs4_cb_compound_hdr
op_star
id|hdr
)paren
(brace
id|u32
op_star
id|p
suffix:semicolon
id|READ_BUF
c_func
(paren
l_int|8
)paren
suffix:semicolon
id|READ32
c_func
(paren
id|hdr-&gt;status
)paren
suffix:semicolon
id|READ32
c_func
(paren
id|hdr-&gt;taglen
)paren
suffix:semicolon
id|READ_BUF
c_func
(paren
id|hdr-&gt;taglen
op_plus
l_int|4
)paren
suffix:semicolon
id|hdr-&gt;tag
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
id|hdr-&gt;taglen
)paren
suffix:semicolon
id|READ32
c_func
(paren
id|hdr-&gt;nops
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)def_block
r_static
r_int
DECL|function|decode_cb_op_hdr
id|decode_cb_op_hdr
c_func
(paren
r_struct
id|xdr_stream
op_star
id|xdr
comma
r_enum
id|nfs_opnum4
id|expected
)paren
(brace
id|u32
op_star
id|p
suffix:semicolon
id|u32
id|op
suffix:semicolon
r_int32
id|nfserr
suffix:semicolon
id|READ_BUF
c_func
(paren
l_int|8
)paren
suffix:semicolon
id|READ32
c_func
(paren
id|op
)paren
suffix:semicolon
r_if
c_cond
(paren
id|op
op_ne
id|expected
)paren
(brace
id|dprintk
c_func
(paren
l_string|&quot;NFSD: decode_cb_op_hdr: Callback server returned &quot;
l_string|&quot; operation %d but we issued a request for %d&bslash;n&quot;
comma
id|op
comma
id|expected
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
id|READ32
c_func
(paren
id|nfserr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nfserr
op_ne
id|NFS_OK
)paren
r_return
op_minus
id|nfs_cb_stat_to_errno
c_func
(paren
id|nfserr
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|nfs4_xdr_dec_cb_null
id|nfs4_xdr_dec_cb_null
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
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|nfs4_xdr_dec_cb_recall
id|nfs4_xdr_dec_cb_recall
c_func
(paren
r_struct
id|rpc_rqst
op_star
id|rqstp
comma
id|u32
op_star
id|p
)paren
(brace
r_struct
id|xdr_stream
id|xdr
suffix:semicolon
r_struct
id|nfs4_cb_compound_hdr
id|hdr
suffix:semicolon
r_int
id|status
suffix:semicolon
id|xdr_init_decode
c_func
(paren
op_amp
id|xdr
comma
op_amp
id|rqstp-&gt;rq_rcv_buf
comma
id|p
)paren
suffix:semicolon
id|status
op_assign
id|decode_cb_compound_hdr
c_func
(paren
op_amp
id|xdr
comma
op_amp
id|hdr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
)paren
r_goto
id|out
suffix:semicolon
id|status
op_assign
id|decode_cb_op_hdr
c_func
(paren
op_amp
id|xdr
comma
id|OP_CB_RECALL
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|status
suffix:semicolon
)brace
multiline_comment|/*&n; * RPC procedure tables&n; */
macro_line|#ifndef MAX
DECL|macro|MAX
macro_line|# define MAX(a, b)      (((a) &gt; (b))? (a) : (b))
macro_line|#endif
DECL|macro|PROC
mdefine_line|#define PROC(proc, call, argtype, restype)                              &bslash;&n;[NFSPROC4_CLNT_##proc] = {                                      &t;&bslash;&n;        .p_proc   = NFSPROC4_CB_##call,&t;&t;&t;&t;&t;&bslash;&n;        .p_encode = (kxdrproc_t) nfs4_xdr_##argtype,                    &bslash;&n;        .p_decode = (kxdrproc_t) nfs4_xdr_##restype,                    &bslash;&n;        .p_bufsiz = MAX(NFS4_##argtype##_sz,NFS4_##restype##_sz) &lt;&lt; 2,  &bslash;&n;}
DECL|variable|nfs4_cb_procedures
r_struct
id|rpc_procinfo
id|nfs4_cb_procedures
(braket
)braket
op_assign
(brace
id|PROC
c_func
(paren
id|CB_NULL
comma
l_int|NULL
comma
id|enc_cb_null
comma
id|dec_cb_null
)paren
comma
id|PROC
c_func
(paren
id|CB_RECALL
comma
id|COMPOUND
comma
id|enc_cb_recall
comma
id|dec_cb_recall
)paren
comma
)brace
suffix:semicolon
DECL|variable|nfs_cb_version4
r_struct
id|rpc_version
id|nfs_cb_version4
op_assign
(brace
dot
id|number
op_assign
l_int|1
comma
dot
id|nrprocs
op_assign
r_sizeof
(paren
id|nfs4_cb_procedures
)paren
op_div
r_sizeof
(paren
id|nfs4_cb_procedures
(braket
l_int|0
)braket
)paren
comma
dot
id|procs
op_assign
id|nfs4_cb_procedures
)brace
suffix:semicolon
DECL|variable|nfs_cb_version
r_static
r_struct
id|rpc_version
op_star
id|nfs_cb_version
(braket
)braket
op_assign
(brace
l_int|NULL
comma
op_amp
id|nfs_cb_version4
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * Use the SETCLIENTID credential&n; */
r_struct
id|rpc_cred
op_star
DECL|function|nfsd4_lookupcred
id|nfsd4_lookupcred
c_func
(paren
r_struct
id|nfs4_client
op_star
id|clp
comma
r_int
id|taskflags
)paren
(brace
r_struct
id|auth_cred
id|acred
suffix:semicolon
r_struct
id|rpc_clnt
op_star
id|clnt
op_assign
id|clp-&gt;cl_callback.cb_client
suffix:semicolon
r_struct
id|rpc_cred
op_star
id|ret
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|clnt
)paren
r_goto
id|out
suffix:semicolon
id|get_group_info
c_func
(paren
id|clp-&gt;cl_cred.cr_group_info
)paren
suffix:semicolon
id|acred.uid
op_assign
id|clp-&gt;cl_cred.cr_uid
suffix:semicolon
id|acred.gid
op_assign
id|clp-&gt;cl_cred.cr_gid
suffix:semicolon
id|acred.group_info
op_assign
id|clp-&gt;cl_cred.cr_group_info
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;NFSD:     looking up %s cred&bslash;n&quot;
comma
id|clnt-&gt;cl_auth-&gt;au_ops-&gt;au_name
)paren
suffix:semicolon
id|ret
op_assign
id|rpcauth_lookup_credcache
c_func
(paren
id|clnt-&gt;cl_auth
comma
op_amp
id|acred
comma
id|taskflags
)paren
suffix:semicolon
id|put_group_info
c_func
(paren
id|clp-&gt;cl_cred.cr_group_info
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * Set up the callback client and put a NFSPROC4_CB_NULL on the wire...&n; */
r_void
DECL|function|nfsd4_probe_callback
id|nfsd4_probe_callback
c_func
(paren
r_struct
id|nfs4_client
op_star
id|clp
)paren
(brace
r_struct
id|sockaddr_in
id|addr
suffix:semicolon
r_struct
id|nfs4_callback
op_star
id|cb
op_assign
op_amp
id|clp-&gt;cl_callback
suffix:semicolon
r_struct
id|rpc_timeout
id|timeparms
suffix:semicolon
r_struct
id|rpc_xprt
op_star
id|xprt
suffix:semicolon
r_struct
id|rpc_program
op_star
id|program
op_assign
op_amp
id|cb-&gt;cb_program
suffix:semicolon
r_struct
id|rpc_stat
op_star
id|stat
op_assign
op_amp
id|cb-&gt;cb_stat
suffix:semicolon
r_struct
id|rpc_clnt
op_star
id|clnt
suffix:semicolon
r_struct
id|rpc_message
id|msg
op_assign
(brace
dot
id|rpc_proc
op_assign
op_amp
id|nfs4_cb_procedures
(braket
id|NFSPROC4_CLNT_CB_NULL
)braket
comma
dot
id|rpc_argp
op_assign
id|clp
comma
)brace
suffix:semicolon
r_char
id|hostname
(braket
l_int|32
)braket
suffix:semicolon
r_int
id|status
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;NFSD: probe_callback. cb_parsed %d cb_set %d&bslash;n&quot;
comma
id|cb-&gt;cb_parsed
comma
id|atomic_read
c_func
(paren
op_amp
id|cb-&gt;cb_set
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cb-&gt;cb_parsed
op_logical_or
id|atomic_read
c_func
(paren
op_amp
id|cb-&gt;cb_set
)paren
)paren
r_return
suffix:semicolon
multiline_comment|/* Initialize address */
id|memset
c_func
(paren
op_amp
id|addr
comma
l_int|0
comma
r_sizeof
(paren
id|addr
)paren
)paren
suffix:semicolon
id|addr.sin_family
op_assign
id|AF_INET
suffix:semicolon
id|addr.sin_port
op_assign
id|htons
c_func
(paren
id|cb-&gt;cb_port
)paren
suffix:semicolon
id|addr.sin_addr.s_addr
op_assign
id|htonl
c_func
(paren
id|cb-&gt;cb_addr
)paren
suffix:semicolon
multiline_comment|/* Initialize timeout */
id|timeparms.to_initval
op_assign
(paren
id|NFSD_LEASE_TIME
op_div
l_int|4
)paren
op_star
id|HZ
suffix:semicolon
id|timeparms.to_retries
op_assign
l_int|0
suffix:semicolon
id|timeparms.to_maxval
op_assign
(paren
id|NFSD_LEASE_TIME
op_div
l_int|2
)paren
op_star
id|HZ
suffix:semicolon
id|timeparms.to_exponential
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* Create RPC transport */
r_if
c_cond
(paren
op_logical_neg
(paren
id|xprt
op_assign
id|xprt_create_proto
c_func
(paren
id|IPPROTO_TCP
comma
op_amp
id|addr
comma
op_amp
id|timeparms
)paren
)paren
)paren
(brace
id|dprintk
c_func
(paren
l_string|&quot;NFSD: couldn&squot;t create callback transport!&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|out_err
suffix:semicolon
)brace
multiline_comment|/* Initialize rpc_program */
id|program-&gt;name
op_assign
l_string|&quot;nfs4_cb&quot;
suffix:semicolon
id|program-&gt;number
op_assign
id|cb-&gt;cb_prog
suffix:semicolon
id|program-&gt;nrvers
op_assign
r_sizeof
(paren
id|nfs_cb_version
)paren
op_div
r_sizeof
(paren
id|nfs_cb_version
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|program-&gt;version
op_assign
id|nfs_cb_version
suffix:semicolon
id|program-&gt;stats
op_assign
id|stat
suffix:semicolon
multiline_comment|/* Initialize rpc_stat */
id|memset
c_func
(paren
id|stat
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|rpc_stat
)paren
)paren
suffix:semicolon
id|stat-&gt;program
op_assign
id|program
suffix:semicolon
multiline_comment|/* Create RPC client&n; &t; *&n;&t; * XXX AUTH_UNIX only - need AUTH_GSS....&n;&t; */
id|sprintf
c_func
(paren
id|hostname
comma
l_string|&quot;%u.%u.%u.%u&quot;
comma
id|NIPQUAD
c_func
(paren
id|addr.sin_addr.s_addr
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|clnt
op_assign
id|rpc_create_client
c_func
(paren
id|xprt
comma
id|hostname
comma
id|program
comma
l_int|1
comma
id|RPC_AUTH_UNIX
)paren
)paren
)paren
(brace
id|dprintk
c_func
(paren
l_string|&quot;NFSD: couldn&squot;t create callback client&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|out_xprt
suffix:semicolon
)brace
id|clnt-&gt;cl_intr
op_assign
l_int|0
suffix:semicolon
id|clnt-&gt;cl_softrtry
op_assign
l_int|1
suffix:semicolon
id|clnt-&gt;cl_chatty
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* Kick rpciod, put the call on the wire. */
r_if
c_cond
(paren
id|rpciod_up
c_func
(paren
)paren
op_ne
l_int|0
)paren
(brace
id|dprintk
c_func
(paren
l_string|&quot;nfsd: couldn&squot;t start rpciod for callbacks!&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|out_clnt
suffix:semicolon
)brace
multiline_comment|/* the task holds a reference to the nfs4_client struct */
id|cb-&gt;cb_client
op_assign
id|clnt
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|clp-&gt;cl_count
)paren
suffix:semicolon
id|msg.rpc_cred
op_assign
id|nfsd4_lookupcred
c_func
(paren
id|clp
comma
l_int|0
)paren
suffix:semicolon
id|status
op_assign
id|rpc_call_async
c_func
(paren
id|clnt
comma
op_amp
id|msg
comma
id|RPC_TASK_ASYNC
comma
id|nfs4_cb_null
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_ne
l_int|0
)paren
(brace
id|dprintk
c_func
(paren
l_string|&quot;NFSD: asynchronous NFSPROC4_CB_NULL failed!&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|out_rpciod
suffix:semicolon
)brace
r_return
suffix:semicolon
id|out_rpciod
suffix:colon
id|atomic_dec
c_func
(paren
op_amp
id|clp-&gt;cl_count
)paren
suffix:semicolon
id|rpciod_down
c_func
(paren
)paren
suffix:semicolon
id|out_clnt
suffix:colon
id|rpc_shutdown_client
c_func
(paren
id|clnt
)paren
suffix:semicolon
r_goto
id|out_err
suffix:semicolon
id|out_xprt
suffix:colon
id|xprt_destroy
c_func
(paren
id|xprt
)paren
suffix:semicolon
id|out_err
suffix:colon
id|dprintk
c_func
(paren
l_string|&quot;NFSD: warning: no callback path to client %.*s&bslash;n&quot;
comma
(paren
r_int
)paren
id|clp-&gt;cl_name.len
comma
id|clp-&gt;cl_name.data
)paren
suffix:semicolon
id|cb-&gt;cb_client
op_assign
l_int|NULL
suffix:semicolon
)brace
r_static
r_void
DECL|function|nfs4_cb_null
id|nfs4_cb_null
c_func
(paren
r_struct
id|rpc_task
op_star
id|task
)paren
(brace
r_struct
id|nfs4_client
op_star
id|clp
op_assign
(paren
r_struct
id|nfs4_client
op_star
)paren
id|task-&gt;tk_msg.rpc_argp
suffix:semicolon
r_struct
id|nfs4_callback
op_star
id|cb
op_assign
op_amp
id|clp-&gt;cl_callback
suffix:semicolon
id|u32
id|addr
op_assign
id|htonl
c_func
(paren
id|cb-&gt;cb_addr
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;NFSD: nfs4_cb_null task-&gt;tk_status %d&bslash;n&quot;
comma
id|task-&gt;tk_status
)paren
suffix:semicolon
r_if
c_cond
(paren
id|task-&gt;tk_status
OL
l_int|0
)paren
(brace
id|dprintk
c_func
(paren
l_string|&quot;NFSD: callback establishment to client %.*s failed&bslash;n&quot;
comma
(paren
r_int
)paren
id|clp-&gt;cl_name.len
comma
id|clp-&gt;cl_name.data
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|atomic_set
c_func
(paren
op_amp
id|cb-&gt;cb_set
comma
l_int|1
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;NFSD: callback set to client %u.%u.%u.%u&bslash;n&quot;
comma
id|NIPQUAD
c_func
(paren
id|addr
)paren
)paren
suffix:semicolon
id|out
suffix:colon
id|put_nfs4_client
c_func
(paren
id|clp
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *  Called with dp-&gt;dl_count incremented&n; */
r_static
r_void
DECL|function|nfs4_cb_recall_done
id|nfs4_cb_recall_done
c_func
(paren
r_struct
id|rpc_task
op_star
id|task
)paren
(brace
r_struct
id|nfs4_cb_recall
op_star
id|cbr
op_assign
(paren
r_struct
id|nfs4_cb_recall
op_star
)paren
id|task-&gt;tk_calldata
suffix:semicolon
r_struct
id|nfs4_delegation
op_star
id|dp
op_assign
id|cbr-&gt;cbr_dp
suffix:semicolon
r_int
id|status
suffix:semicolon
multiline_comment|/* all is well... */
r_if
c_cond
(paren
id|task-&gt;tk_status
op_eq
l_int|0
)paren
r_goto
id|out
suffix:semicolon
multiline_comment|/* network partition, retry nfsd4_cb_recall once.  */
r_if
c_cond
(paren
id|task-&gt;tk_status
op_eq
op_minus
id|EIO
)paren
(brace
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|dp-&gt;dl_recall_cnt
)paren
op_eq
l_int|0
)paren
r_goto
id|retry
suffix:semicolon
r_else
multiline_comment|/* callback channel no longer available */
id|atomic_set
c_func
(paren
op_amp
id|dp-&gt;dl_client-&gt;cl_callback.cb_set
comma
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/* Race: a recall occurred miliseconds after a delegation was granted.&n;&t;* Client may have received recall prior to delegation. retry recall&n;&t;* once.&n;&t;*/
r_if
c_cond
(paren
(paren
id|task-&gt;tk_status
op_eq
op_minus
id|EBADHANDLE
)paren
op_logical_or
(paren
id|task-&gt;tk_status
op_eq
op_minus
id|NFS4ERR_BAD_STATEID
)paren
)paren
(brace
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|dp-&gt;dl_recall_cnt
)paren
op_eq
l_int|0
)paren
r_goto
id|retry
suffix:semicolon
)brace
id|atomic_set
c_func
(paren
op_amp
id|dp-&gt;dl_state
comma
id|NFS4_RECALL_COMPLETE
)paren
suffix:semicolon
id|out
suffix:colon
r_if
c_cond
(paren
id|atomic_dec_and_test
c_func
(paren
op_amp
id|dp-&gt;dl_count
)paren
)paren
id|atomic_set
c_func
(paren
op_amp
id|dp-&gt;dl_state
comma
id|NFS4_REAP_DELEG
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
id|atomic_read
c_func
(paren
op_amp
id|dp-&gt;dl_count
)paren
OL
l_int|0
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;NFSD: nfs4_cb_recall_done: dp %p dl_flock %p dl_count %d&bslash;n&quot;
comma
id|dp
comma
id|dp-&gt;dl_flock
comma
id|atomic_read
c_func
(paren
op_amp
id|dp-&gt;dl_count
)paren
)paren
suffix:semicolon
r_return
suffix:semicolon
id|retry
suffix:colon
id|dprintk
c_func
(paren
l_string|&quot;NFSD: nfs4_cb_recall_done RETRY&bslash;n&quot;
)paren
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|dp-&gt;dl_recall_cnt
)paren
suffix:semicolon
multiline_comment|/* sleep 2 seconds before retrying recall */
id|set_current_state
c_func
(paren
id|TASK_UNINTERRUPTIBLE
)paren
suffix:semicolon
id|schedule_timeout
c_func
(paren
l_int|2
op_star
id|HZ
)paren
suffix:semicolon
id|status
op_assign
id|nfsd4_cb_recall
c_func
(paren
id|dp
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;NFSD: nfs4_cb_recall_done: retry status: %d  dp %p dl_flock %p&bslash;n&quot;
comma
id|status
comma
id|dp
comma
id|dp-&gt;dl_flock
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * called with dp-&gt;dl_count inc&squot;ed.&n; * nfs4_lock_state() may or may not have been called.&n; */
r_int
DECL|function|nfsd4_cb_recall
id|nfsd4_cb_recall
c_func
(paren
r_struct
id|nfs4_delegation
op_star
id|dp
)paren
(brace
r_struct
id|nfs4_client
op_star
id|clp
suffix:semicolon
r_struct
id|rpc_clnt
op_star
id|clnt
suffix:semicolon
r_struct
id|rpc_message
id|msg
op_assign
(brace
dot
id|rpc_proc
op_assign
op_amp
id|nfs4_cb_procedures
(braket
id|NFSPROC4_CLNT_CB_RECALL
)braket
comma
)brace
suffix:semicolon
r_struct
id|nfs4_cb_recall
op_star
id|cbr
op_assign
op_amp
id|dp-&gt;dl_recall
suffix:semicolon
r_int
id|status
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;NFSD: nfsd4_cb_recall NFS4_enc_cb_recall_sz %d NFS4_dec_cb_recall_sz %d &bslash;n&quot;
comma
id|NFS4_enc_cb_recall_sz
comma
id|NFS4_dec_cb_recall_sz
)paren
suffix:semicolon
id|clp
op_assign
id|dp-&gt;dl_client
suffix:semicolon
id|clnt
op_assign
id|clp-&gt;cl_callback.cb_client
suffix:semicolon
id|status
op_assign
id|EIO
suffix:semicolon
r_if
c_cond
(paren
(paren
op_logical_neg
id|atomic_read
c_func
(paren
op_amp
id|clp-&gt;cl_callback.cb_set
)paren
)paren
op_logical_or
op_logical_neg
id|clnt
)paren
r_goto
id|out_free
suffix:semicolon
id|msg.rpc_argp
op_assign
id|cbr
suffix:semicolon
id|msg.rpc_resp
op_assign
id|cbr
suffix:semicolon
id|msg.rpc_cred
op_assign
id|nfsd4_lookupcred
c_func
(paren
id|clp
comma
l_int|0
)paren
suffix:semicolon
id|cbr-&gt;cbr_trunc
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* XXX need to implement truncate optimization */
id|cbr-&gt;cbr_dp
op_assign
id|dp
suffix:semicolon
r_if
c_cond
(paren
(paren
id|status
op_assign
id|rpc_call_async
c_func
(paren
id|clnt
comma
op_amp
id|msg
comma
id|RPC_TASK_SOFT
comma
id|nfs4_cb_recall_done
comma
id|cbr
)paren
)paren
)paren
(brace
id|dprintk
c_func
(paren
l_string|&quot;NFSD: recall_delegation: rpc_call_async failed %d&bslash;n&quot;
comma
id|status
)paren
suffix:semicolon
r_goto
id|out_fail
suffix:semicolon
)brace
id|out
suffix:colon
r_return
id|status
suffix:semicolon
id|out_fail
suffix:colon
id|status
op_assign
id|nfserrno
c_func
(paren
id|status
)paren
suffix:semicolon
id|out_free
suffix:colon
id|kfree
c_func
(paren
id|cbr
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
eof
