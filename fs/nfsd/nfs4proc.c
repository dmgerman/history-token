multiline_comment|/*&n; *  fs/nfsd/nfs4proc.c&n; *&n; *  Server-side procedures for NFSv4.&n; *&n; *  Copyright (c) 2002 The Regents of the University of Michigan.&n; *  All rights reserved.&n; *&n; *  Kendrick Smith &lt;kmsmith@umich.edu&gt;&n; *  Andy Adamson   &lt;andros@umich.edu&gt;&n; *&n; *  Redistribution and use in source and binary forms, with or without&n; *  modification, are permitted provided that the following conditions&n; *  are met:&n; *&n; *  1. Redistributions of source code must retain the above copyright&n; *     notice, this list of conditions and the following disclaimer.&n; *  2. Redistributions in binary form must reproduce the above copyright&n; *     notice, this list of conditions and the following disclaimer in the&n; *     documentation and/or other materials provided with the distribution.&n; *  3. Neither the name of the University nor the names of its&n; *     contributors may be used to endorse or promote products derived&n; *     from this software without specific prior written permission.&n; *&n; *  THIS SOFTWARE IS PROVIDED ``AS IS&squot;&squot; AND ANY EXPRESS OR IMPLIED&n; *  WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF&n; *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE&n; *  DISCLAIMED. IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE&n; *  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR&n; *  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF&n; *  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR&n; *  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF&n; *  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING&n; *  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS&n; *  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; * Note: some routines in this file are just trivial wrappers&n; * (e.g. nfsd4_lookup()) defined solely for the sake of consistent&n; * naming.  Since all such routines have been declared &quot;inline&quot;,&n; * there shouldn&squot;t be any associated overhead.  At some point in&n; * the future, I might inline these &quot;by hand&quot; to clean up a&n; * little.&n; */
macro_line|#include &lt;linux/param.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/sunrpc/svc.h&gt;
macro_line|#include &lt;linux/nfsd/nfsd.h&gt;
macro_line|#include &lt;linux/nfsd/cache.h&gt;
macro_line|#include &lt;linux/nfs4.h&gt;
macro_line|#include &lt;linux/nfsd/state.h&gt;
macro_line|#include &lt;linux/nfsd/xdr4.h&gt;
DECL|macro|NFSDDBG_FACILITY
mdefine_line|#define NFSDDBG_FACILITY&t;&t;NFSDDBG_PROC
r_static
r_inline
r_int
DECL|function|nfsd4_close
id|nfsd4_close
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
r_struct
id|svc_fh
op_star
id|current_fh
comma
r_struct
id|nfsd4_close
op_star
id|close
)paren
(brace
r_return
id|nfs_ok
suffix:semicolon
)brace
multiline_comment|/* Note: The organization of the OPEN code seems a little strange; it&n; * has been superfluously split into three routines, one of which is named&n; * nfsd4_process_open2() even though there is no nfsd4_process_open1()!&n; * This is because the code has been organized in anticipation of a&n; * subsequent patch which will implement more of the NFSv4 state model.&n; */
r_static
r_int
DECL|function|do_open_lookup
id|do_open_lookup
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
r_struct
id|svc_fh
op_star
id|current_fh
comma
r_struct
id|nfsd4_open
op_star
id|open
)paren
(brace
r_struct
id|svc_fh
id|resfh
suffix:semicolon
r_int
id|accmode
comma
id|status
suffix:semicolon
id|fh_init
c_func
(paren
op_amp
id|resfh
comma
id|NFS4_FHSIZE
)paren
suffix:semicolon
id|open-&gt;op_truncate
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|open-&gt;op_create
)paren
(brace
multiline_comment|/*&n;&t;&t; * Note: create modes (UNCHECKED,GUARDED...) are the same&n;&t;&t; * in NFSv4 as in v3.&n;&t;&t; */
id|status
op_assign
id|nfsd_create_v3
c_func
(paren
id|rqstp
comma
id|current_fh
comma
id|open-&gt;op_fname.data
comma
id|open-&gt;op_fname.len
comma
op_amp
id|open-&gt;op_iattr
comma
op_amp
id|resfh
comma
id|open-&gt;op_createmode
comma
(paren
id|u32
op_star
)paren
id|open-&gt;op_verf
comma
op_amp
id|open-&gt;op_truncate
)paren
suffix:semicolon
)brace
r_else
(brace
id|status
op_assign
id|nfsd_lookup
c_func
(paren
id|rqstp
comma
id|current_fh
comma
id|open-&gt;op_fname.data
comma
id|open-&gt;op_fname.len
comma
op_amp
id|resfh
)paren
suffix:semicolon
id|fh_unlock
c_func
(paren
id|current_fh
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|status
)paren
(brace
id|set_change_info
c_func
(paren
op_amp
id|open-&gt;op_cinfo
comma
id|current_fh
)paren
suffix:semicolon
id|fh_dup2
c_func
(paren
id|current_fh
comma
op_amp
id|resfh
)paren
suffix:semicolon
id|accmode
op_assign
id|MAY_NOP
suffix:semicolon
r_if
c_cond
(paren
id|open-&gt;op_share_access
op_amp
id|NFS4_SHARE_ACCESS_READ
)paren
id|accmode
op_assign
id|MAY_READ
suffix:semicolon
r_if
c_cond
(paren
id|open-&gt;op_share_deny
op_amp
id|NFS4_SHARE_ACCESS_WRITE
)paren
id|accmode
op_or_assign
(paren
id|MAY_WRITE
op_or
id|MAY_TRUNC
)paren
suffix:semicolon
id|status
op_assign
id|fh_verify
c_func
(paren
id|rqstp
comma
id|current_fh
comma
id|S_IFREG
comma
id|accmode
)paren
suffix:semicolon
)brace
id|fh_put
c_func
(paren
op_amp
id|resfh
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|nfsd4_open
id|nfsd4_open
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
r_struct
id|svc_fh
op_star
id|current_fh
comma
r_struct
id|nfsd4_open
op_star
id|open
)paren
(brace
r_int
id|status
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;NFSD: nfsd4_open filename %.*s&bslash;n&quot;
comma
id|open-&gt;op_fname.len
comma
id|open-&gt;op_fname.data
)paren
suffix:semicolon
multiline_comment|/* This check required by spec. */
r_if
c_cond
(paren
id|open-&gt;op_create
op_logical_and
id|open-&gt;op_claim_type
op_ne
id|NFS4_OPEN_CLAIM_NULL
)paren
r_return
id|nfserr_inval
suffix:semicolon
multiline_comment|/* check seqid for replay. set nfs4_owner */
id|status
op_assign
id|nfsd4_process_open1
c_func
(paren
id|open
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
)paren
r_return
id|status
suffix:semicolon
multiline_comment|/*&n;&t; * This block of code will (1) set CURRENT_FH to the file being opened,&n;&t; * creating it if necessary, (2) set open-&gt;op_cinfo, &n;&t; * (3) set open-&gt;op_truncate if the file is to be truncated &n;&t; * after opening, (4) do permission checking.&n;&t; */
id|status
op_assign
id|do_open_lookup
c_func
(paren
id|rqstp
comma
id|current_fh
comma
id|open
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
)paren
r_return
id|status
suffix:semicolon
multiline_comment|/*&n;&t; * nfsd4_process_open2() does the actual opening of the file.  If&n;&t; * successful, it (1) truncates the file if open-&gt;op_truncate was&n;&t; * set, (2) sets open-&gt;op_stateid, (3) sets open-&gt;op_delegation.&n;&t; */
id|status
op_assign
id|nfsd4_process_open2
c_func
(paren
id|rqstp
comma
id|current_fh
comma
id|open
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
)paren
r_return
id|status
suffix:semicolon
multiline_comment|/*&n;&t; * To finish the open response, we just need to set the rflags.&n;&t; */
id|open-&gt;op_rflags
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|nfsd4_renew
id|nfsd4_renew
c_func
(paren
id|clientid_t
op_star
id|clientid
)paren
(brace
r_return
id|nfs_ok
suffix:semicolon
)brace
multiline_comment|/*&n; * filehandle-manipulating ops.&n; */
r_static
r_inline
r_int
DECL|function|nfsd4_getfh
id|nfsd4_getfh
c_func
(paren
r_struct
id|svc_fh
op_star
id|current_fh
comma
r_struct
id|svc_fh
op_star
op_star
id|getfh
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|current_fh-&gt;fh_dentry
)paren
r_return
id|nfserr_nofilehandle
suffix:semicolon
op_star
id|getfh
op_assign
id|current_fh
suffix:semicolon
r_return
id|nfs_ok
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|nfsd4_putfh
id|nfsd4_putfh
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
r_struct
id|svc_fh
op_star
id|current_fh
comma
r_struct
id|nfsd4_putfh
op_star
id|putfh
)paren
(brace
id|fh_put
c_func
(paren
id|current_fh
)paren
suffix:semicolon
id|current_fh-&gt;fh_handle.fh_size
op_assign
id|putfh-&gt;pf_fhlen
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|current_fh-&gt;fh_handle.fh_base
comma
id|putfh-&gt;pf_fhval
comma
id|putfh-&gt;pf_fhlen
)paren
suffix:semicolon
r_return
id|fh_verify
c_func
(paren
id|rqstp
comma
id|current_fh
comma
l_int|0
comma
id|MAY_NOP
)paren
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|nfsd4_putrootfh
id|nfsd4_putrootfh
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
r_struct
id|svc_fh
op_star
id|current_fh
)paren
(brace
id|fh_put
c_func
(paren
id|current_fh
)paren
suffix:semicolon
r_return
id|exp_pseudoroot
c_func
(paren
id|rqstp-&gt;rq_client
comma
id|current_fh
)paren
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|nfsd4_restorefh
id|nfsd4_restorefh
c_func
(paren
r_struct
id|svc_fh
op_star
id|current_fh
comma
r_struct
id|svc_fh
op_star
id|save_fh
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|save_fh-&gt;fh_dentry
)paren
r_return
id|nfserr_nofilehandle
suffix:semicolon
id|fh_dup2
c_func
(paren
id|current_fh
comma
id|save_fh
)paren
suffix:semicolon
r_return
id|nfs_ok
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|nfsd4_savefh
id|nfsd4_savefh
c_func
(paren
r_struct
id|svc_fh
op_star
id|current_fh
comma
r_struct
id|svc_fh
op_star
id|save_fh
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|current_fh-&gt;fh_dentry
)paren
r_return
id|nfserr_nofilehandle
suffix:semicolon
id|fh_dup2
c_func
(paren
id|save_fh
comma
id|current_fh
)paren
suffix:semicolon
r_return
id|nfs_ok
suffix:semicolon
)brace
multiline_comment|/*&n; * misc nfsv4 ops&n; */
r_static
r_inline
r_int
DECL|function|nfsd4_access
id|nfsd4_access
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
r_struct
id|svc_fh
op_star
id|current_fh
comma
r_struct
id|nfsd4_access
op_star
id|access
)paren
(brace
r_if
c_cond
(paren
id|access-&gt;ac_req_access
op_amp
op_complement
id|NFS3_ACCESS_FULL
)paren
r_return
id|nfserr_inval
suffix:semicolon
id|access-&gt;ac_resp_access
op_assign
id|access-&gt;ac_req_access
suffix:semicolon
r_return
id|nfsd_access
c_func
(paren
id|rqstp
comma
id|current_fh
comma
op_amp
id|access-&gt;ac_resp_access
comma
op_amp
id|access-&gt;ac_supported
)paren
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|nfsd4_commit
id|nfsd4_commit
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
r_struct
id|svc_fh
op_star
id|current_fh
comma
r_struct
id|nfsd4_commit
op_star
id|commit
)paren
(brace
id|u32
op_star
id|p
op_assign
(paren
id|u32
op_star
)paren
id|commit-&gt;co_verf
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|nfssvc_boot.tv_sec
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|nfssvc_boot.tv_usec
suffix:semicolon
r_return
id|nfsd_commit
c_func
(paren
id|rqstp
comma
id|current_fh
comma
id|commit-&gt;co_offset
comma
id|commit-&gt;co_count
)paren
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|nfsd4_create
id|nfsd4_create
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
r_struct
id|svc_fh
op_star
id|current_fh
comma
r_struct
id|nfsd4_create
op_star
id|create
)paren
(brace
r_struct
id|svc_fh
id|resfh
suffix:semicolon
r_int
id|status
suffix:semicolon
id|dev_t
id|rdev
suffix:semicolon
id|fh_init
c_func
(paren
op_amp
id|resfh
comma
id|NFS4_FHSIZE
)paren
suffix:semicolon
id|status
op_assign
id|fh_verify
c_func
(paren
id|rqstp
comma
id|current_fh
comma
id|S_IFDIR
comma
id|MAY_CREATE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
)paren
r_return
id|status
suffix:semicolon
r_switch
c_cond
(paren
id|create-&gt;cr_type
)paren
(brace
r_case
id|NF4LNK
suffix:colon
multiline_comment|/* ugh! we have to null-terminate the linktext, or&n;&t;&t; * vfs_symlink() will choke.  it is always safe to&n;&t;&t; * null-terminate by brute force, since at worst we&n;&t;&t; * will overwrite the first byte of the create namelen&n;&t;&t; * in the XDR buffer, which has already been extracted&n;&t;&t; * during XDR decode.&n;&t;&t; */
id|create-&gt;cr_linkname
(braket
id|create-&gt;cr_linklen
)braket
op_assign
l_int|0
suffix:semicolon
id|status
op_assign
id|nfsd_symlink
c_func
(paren
id|rqstp
comma
id|current_fh
comma
id|create-&gt;cr_name
comma
id|create-&gt;cr_namelen
comma
id|create-&gt;cr_linkname
comma
id|create-&gt;cr_linklen
comma
op_amp
id|resfh
comma
op_amp
id|create-&gt;cr_iattr
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|NF4BLK
suffix:colon
id|rdev
op_assign
id|MKDEV
c_func
(paren
id|create-&gt;cr_specdata1
comma
id|create-&gt;cr_specdata2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|MAJOR
c_func
(paren
id|rdev
)paren
op_ne
id|create-&gt;cr_specdata1
op_logical_or
id|MINOR
c_func
(paren
id|rdev
)paren
op_ne
id|create-&gt;cr_specdata2
)paren
r_return
id|nfserr_inval
suffix:semicolon
id|status
op_assign
id|nfsd_create
c_func
(paren
id|rqstp
comma
id|current_fh
comma
id|create-&gt;cr_name
comma
id|create-&gt;cr_namelen
comma
op_amp
id|create-&gt;cr_iattr
comma
id|S_IFBLK
comma
id|rdev
comma
op_amp
id|resfh
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|NF4CHR
suffix:colon
id|rdev
op_assign
id|MKDEV
c_func
(paren
id|create-&gt;cr_specdata1
comma
id|create-&gt;cr_specdata2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|MAJOR
c_func
(paren
id|rdev
)paren
op_ne
id|create-&gt;cr_specdata1
op_logical_or
id|MINOR
c_func
(paren
id|rdev
)paren
op_ne
id|create-&gt;cr_specdata2
)paren
r_return
id|nfserr_inval
suffix:semicolon
id|status
op_assign
id|nfsd_create
c_func
(paren
id|rqstp
comma
id|current_fh
comma
id|create-&gt;cr_name
comma
id|create-&gt;cr_namelen
comma
op_amp
id|create-&gt;cr_iattr
comma
id|S_IFCHR
comma
id|rdev
comma
op_amp
id|resfh
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|NF4SOCK
suffix:colon
id|status
op_assign
id|nfsd_create
c_func
(paren
id|rqstp
comma
id|current_fh
comma
id|create-&gt;cr_name
comma
id|create-&gt;cr_namelen
comma
op_amp
id|create-&gt;cr_iattr
comma
id|S_IFSOCK
comma
l_int|0
comma
op_amp
id|resfh
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|NF4FIFO
suffix:colon
id|status
op_assign
id|nfsd_create
c_func
(paren
id|rqstp
comma
id|current_fh
comma
id|create-&gt;cr_name
comma
id|create-&gt;cr_namelen
comma
op_amp
id|create-&gt;cr_iattr
comma
id|S_IFIFO
comma
l_int|0
comma
op_amp
id|resfh
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|NF4DIR
suffix:colon
id|create-&gt;cr_iattr.ia_valid
op_and_assign
op_complement
id|ATTR_SIZE
suffix:semicolon
id|status
op_assign
id|nfsd_create
c_func
(paren
id|rqstp
comma
id|current_fh
comma
id|create-&gt;cr_name
comma
id|create-&gt;cr_namelen
comma
op_amp
id|create-&gt;cr_iattr
comma
id|S_IFDIR
comma
l_int|0
comma
op_amp
id|resfh
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|status
)paren
(brace
id|fh_unlock
c_func
(paren
id|current_fh
)paren
suffix:semicolon
id|set_change_info
c_func
(paren
op_amp
id|create-&gt;cr_cinfo
comma
id|current_fh
)paren
suffix:semicolon
id|fh_dup2
c_func
(paren
id|current_fh
comma
op_amp
id|resfh
)paren
suffix:semicolon
)brace
id|fh_put
c_func
(paren
op_amp
id|resfh
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|nfsd4_getattr
id|nfsd4_getattr
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
r_struct
id|svc_fh
op_star
id|current_fh
comma
r_struct
id|nfsd4_getattr
op_star
id|getattr
)paren
(brace
r_int
id|status
suffix:semicolon
id|status
op_assign
id|fh_verify
c_func
(paren
id|rqstp
comma
id|current_fh
comma
l_int|0
comma
id|MAY_NOP
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
)paren
r_return
id|status
suffix:semicolon
r_if
c_cond
(paren
id|getattr-&gt;ga_bmval
(braket
l_int|1
)braket
op_amp
id|NFSD_WRITEONLY_ATTRS_WORD1
)paren
r_return
id|nfserr_inval
suffix:semicolon
id|getattr-&gt;ga_bmval
(braket
l_int|0
)braket
op_and_assign
id|NFSD_SUPPORTED_ATTRS_WORD0
suffix:semicolon
id|getattr-&gt;ga_bmval
(braket
l_int|1
)braket
op_and_assign
id|NFSD_SUPPORTED_ATTRS_WORD1
suffix:semicolon
id|getattr-&gt;ga_fhp
op_assign
id|current_fh
suffix:semicolon
r_return
id|nfs_ok
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|nfsd4_link
id|nfsd4_link
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
r_struct
id|svc_fh
op_star
id|current_fh
comma
r_struct
id|svc_fh
op_star
id|save_fh
comma
r_struct
id|nfsd4_link
op_star
id|link
)paren
(brace
r_int
id|status
suffix:semicolon
id|status
op_assign
id|nfsd_link
c_func
(paren
id|rqstp
comma
id|current_fh
comma
id|link-&gt;li_name
comma
id|link-&gt;li_namelen
comma
id|save_fh
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|status
)paren
id|set_change_info
c_func
(paren
op_amp
id|link-&gt;li_cinfo
comma
id|current_fh
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|nfsd4_lookupp
id|nfsd4_lookupp
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
r_struct
id|svc_fh
op_star
id|current_fh
)paren
(brace
multiline_comment|/*&n;&t; * XXX: We currently violate the spec in one small respect&n;&t; * here.  If LOOKUPP is done at the root of the pseudofs,&n;&t; * the spec requires us to return NFSERR_NOENT.  Personally,&n;&t; * I think that leaving the filehandle unchanged is more&n;&t; * logical, but this is an academic question anyway, since&n;&t; * no clients actually use LOOKUPP.&n;&t; */
r_return
id|nfsd_lookup
c_func
(paren
id|rqstp
comma
id|current_fh
comma
l_string|&quot;..&quot;
comma
l_int|2
comma
id|current_fh
)paren
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|nfsd4_lookup
id|nfsd4_lookup
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
r_struct
id|svc_fh
op_star
id|current_fh
comma
r_struct
id|nfsd4_lookup
op_star
id|lookup
)paren
(brace
r_return
id|nfsd_lookup
c_func
(paren
id|rqstp
comma
id|current_fh
comma
id|lookup-&gt;lo_name
comma
id|lookup-&gt;lo_len
comma
id|current_fh
)paren
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|nfsd4_read
id|nfsd4_read
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
r_struct
id|svc_fh
op_star
id|current_fh
comma
r_struct
id|nfsd4_read
op_star
id|read
)paren
(brace
multiline_comment|/* no need to check permission - this will be done in nfsd_read() */
r_if
c_cond
(paren
id|read-&gt;rd_offset
op_ge
id|OFFSET_MAX
)paren
r_return
id|nfserr_inval
suffix:semicolon
id|read-&gt;rd_rqstp
op_assign
id|rqstp
suffix:semicolon
id|read-&gt;rd_fhp
op_assign
id|current_fh
suffix:semicolon
r_return
id|nfs_ok
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|nfsd4_readdir
id|nfsd4_readdir
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
r_struct
id|svc_fh
op_star
id|current_fh
comma
r_struct
id|nfsd4_readdir
op_star
id|readdir
)paren
(brace
multiline_comment|/* no need to check permission - this will be done in nfsd_readdir() */
r_if
c_cond
(paren
id|readdir-&gt;rd_bmval
(braket
l_int|1
)braket
op_amp
id|NFSD_WRITEONLY_ATTRS_WORD1
)paren
r_return
id|nfserr_inval
suffix:semicolon
id|readdir-&gt;rd_bmval
(braket
l_int|0
)braket
op_and_assign
id|NFSD_SUPPORTED_ATTRS_WORD0
suffix:semicolon
id|readdir-&gt;rd_bmval
(braket
l_int|1
)braket
op_and_assign
id|NFSD_SUPPORTED_ATTRS_WORD1
suffix:semicolon
r_if
c_cond
(paren
id|readdir-&gt;rd_cookie
OG
op_complement
(paren
id|u32
)paren
l_int|0
)paren
r_return
id|nfserr_bad_cookie
suffix:semicolon
id|readdir-&gt;rd_rqstp
op_assign
id|rqstp
suffix:semicolon
id|readdir-&gt;rd_fhp
op_assign
id|current_fh
suffix:semicolon
r_return
id|nfs_ok
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|nfsd4_readlink
id|nfsd4_readlink
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
r_struct
id|svc_fh
op_star
id|current_fh
comma
r_struct
id|nfsd4_readlink
op_star
id|readlink
)paren
(brace
id|readlink-&gt;rl_rqstp
op_assign
id|rqstp
suffix:semicolon
id|readlink-&gt;rl_fhp
op_assign
id|current_fh
suffix:semicolon
r_return
id|nfs_ok
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|nfsd4_remove
id|nfsd4_remove
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
r_struct
id|svc_fh
op_star
id|current_fh
comma
r_struct
id|nfsd4_remove
op_star
id|remove
)paren
(brace
r_int
id|status
suffix:semicolon
id|status
op_assign
id|nfsd_unlink
c_func
(paren
id|rqstp
comma
id|current_fh
comma
l_int|0
comma
id|remove-&gt;rm_name
comma
id|remove-&gt;rm_namelen
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|status
)paren
(brace
id|fh_unlock
c_func
(paren
id|current_fh
)paren
suffix:semicolon
id|set_change_info
c_func
(paren
op_amp
id|remove-&gt;rm_cinfo
comma
id|current_fh
)paren
suffix:semicolon
)brace
r_return
id|status
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|nfsd4_rename
id|nfsd4_rename
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
r_struct
id|svc_fh
op_star
id|current_fh
comma
r_struct
id|svc_fh
op_star
id|save_fh
comma
r_struct
id|nfsd4_rename
op_star
id|rename
)paren
(brace
r_int
id|status
suffix:semicolon
id|status
op_assign
id|nfsd_rename
c_func
(paren
id|rqstp
comma
id|save_fh
comma
id|rename-&gt;rn_sname
comma
id|rename-&gt;rn_snamelen
comma
id|current_fh
comma
id|rename-&gt;rn_tname
comma
id|rename-&gt;rn_tnamelen
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|status
)paren
(brace
id|set_change_info
c_func
(paren
op_amp
id|rename-&gt;rn_sinfo
comma
id|current_fh
)paren
suffix:semicolon
id|set_change_info
c_func
(paren
op_amp
id|rename-&gt;rn_tinfo
comma
id|save_fh
)paren
suffix:semicolon
)brace
r_return
id|status
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|nfsd4_setattr
id|nfsd4_setattr
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
r_struct
id|svc_fh
op_star
id|current_fh
comma
r_struct
id|nfsd4_setattr
op_star
id|setattr
)paren
(brace
r_return
id|nfsd_setattr
c_func
(paren
id|rqstp
comma
id|current_fh
comma
op_amp
id|setattr-&gt;sa_iattr
comma
l_int|0
comma
(paren
id|time_t
)paren
l_int|0
)paren
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|nfsd4_write
id|nfsd4_write
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
r_struct
id|svc_fh
op_star
id|current_fh
comma
r_struct
id|nfsd4_write
op_star
id|write
)paren
(brace
id|u32
op_star
id|p
suffix:semicolon
multiline_comment|/* no need to check permission - this will be done in nfsd_write() */
r_if
c_cond
(paren
id|write-&gt;wr_offset
op_ge
id|OFFSET_MAX
)paren
r_return
id|nfserr_inval
suffix:semicolon
id|write-&gt;wr_bytes_written
op_assign
id|write-&gt;wr_buflen
suffix:semicolon
id|write-&gt;wr_how_written
op_assign
id|write-&gt;wr_stable_how
suffix:semicolon
id|p
op_assign
(paren
id|u32
op_star
)paren
id|write-&gt;wr_verifier
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|nfssvc_boot.tv_sec
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|nfssvc_boot.tv_usec
suffix:semicolon
r_return
id|nfsd_write
c_func
(paren
id|rqstp
comma
id|current_fh
comma
id|write-&gt;wr_offset
comma
id|write-&gt;wr_vec
comma
id|write-&gt;wr_vlen
comma
id|write-&gt;wr_buflen
comma
op_amp
id|write-&gt;wr_how_written
)paren
suffix:semicolon
)brace
multiline_comment|/* This routine never returns NFS_OK!  If there are no other errors, it&n; * will return NFSERR_SAME or NFSERR_NOT_SAME depending on whether the&n; * attributes matched.  VERIFY is implemented by mapping NFSERR_SAME&n; * to NFS_OK after the call; NVERIFY by mapping NFSERR_NOT_SAME to NFS_OK.&n; */
r_static
r_int
DECL|function|nfsd4_verify
id|nfsd4_verify
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
r_struct
id|svc_fh
op_star
id|current_fh
comma
r_struct
id|nfsd4_verify
op_star
id|verify
)paren
(brace
id|u32
op_star
id|buf
comma
op_star
id|p
suffix:semicolon
r_int
id|count
suffix:semicolon
r_int
id|status
suffix:semicolon
id|status
op_assign
id|fh_verify
c_func
(paren
id|rqstp
comma
id|current_fh
comma
l_int|0
comma
id|MAY_NOP
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
)paren
r_return
id|status
suffix:semicolon
r_if
c_cond
(paren
(paren
id|verify-&gt;ve_bmval
(braket
l_int|0
)braket
op_amp
op_complement
id|NFSD_SUPPORTED_ATTRS_WORD0
)paren
op_logical_or
(paren
id|verify-&gt;ve_bmval
(braket
l_int|1
)braket
op_amp
op_complement
id|NFSD_SUPPORTED_ATTRS_WORD1
)paren
)paren
r_return
id|nfserr_notsupp
suffix:semicolon
r_if
c_cond
(paren
id|verify-&gt;ve_bmval
(braket
l_int|1
)braket
op_amp
id|NFSD_WRITEONLY_ATTRS_WORD1
)paren
r_return
id|nfserr_inval
suffix:semicolon
r_if
c_cond
(paren
id|verify-&gt;ve_attrlen
op_amp
l_int|3
)paren
r_return
id|nfserr_inval
suffix:semicolon
multiline_comment|/* count in words:&n;&t; *   bitmap_len(1) + bitmap(2) + attr_len(1) = 4&n;&t; */
id|count
op_assign
l_int|4
op_plus
(paren
id|verify-&gt;ve_attrlen
op_rshift
l_int|2
)paren
suffix:semicolon
id|buf
op_assign
id|kmalloc
c_func
(paren
id|count
op_lshift
l_int|2
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|buf
)paren
r_return
id|nfserr_resource
suffix:semicolon
id|status
op_assign
id|nfsd4_encode_fattr
c_func
(paren
id|current_fh
comma
id|current_fh-&gt;fh_export
comma
id|current_fh-&gt;fh_dentry
comma
id|buf
comma
op_amp
id|count
comma
id|verify-&gt;ve_bmval
)paren
suffix:semicolon
multiline_comment|/* this means that nfsd4_encode_fattr() ran out of space */
r_if
c_cond
(paren
id|status
op_eq
id|nfserr_resource
op_logical_and
id|count
op_eq
l_int|0
)paren
id|status
op_assign
id|nfserr_not_same
suffix:semicolon
r_if
c_cond
(paren
id|status
)paren
r_goto
id|out_kfree
suffix:semicolon
id|p
op_assign
id|buf
op_plus
l_int|3
suffix:semicolon
id|status
op_assign
id|nfserr_not_same
suffix:semicolon
r_if
c_cond
(paren
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
op_ne
id|verify-&gt;ve_attrlen
)paren
r_goto
id|out_kfree
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|memcmp
c_func
(paren
id|p
comma
id|verify-&gt;ve_attrval
comma
id|verify-&gt;ve_attrlen
)paren
)paren
id|status
op_assign
id|nfserr_same
suffix:semicolon
id|out_kfree
suffix:colon
id|kfree
c_func
(paren
id|buf
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
multiline_comment|/*&n; * NULL call.&n; */
r_static
r_int
DECL|function|nfsd4_proc_null
id|nfsd4_proc_null
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
multiline_comment|/*&n; * COMPOUND call.&n; */
r_static
r_int
DECL|function|nfsd4_proc_compound
id|nfsd4_proc_compound
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
r_struct
id|nfsd4_compoundargs
op_star
id|args
comma
r_struct
id|nfsd4_compoundres
op_star
id|resp
)paren
(brace
r_struct
id|nfsd4_op
op_star
id|op
suffix:semicolon
r_struct
id|svc_fh
id|current_fh
suffix:semicolon
r_struct
id|svc_fh
id|save_fh
suffix:semicolon
r_int
id|slack_space
suffix:semicolon
multiline_comment|/* in words, not bytes! */
r_int
id|status
suffix:semicolon
id|fh_init
c_func
(paren
op_amp
id|current_fh
comma
id|NFS4_FHSIZE
)paren
suffix:semicolon
id|fh_init
c_func
(paren
op_amp
id|save_fh
comma
id|NFS4_FHSIZE
)paren
suffix:semicolon
id|resp-&gt;xbuf
op_assign
op_amp
id|rqstp-&gt;rq_res
suffix:semicolon
id|resp-&gt;p
op_assign
id|rqstp-&gt;rq_res.head
(braket
l_int|0
)braket
dot
id|iov_base
op_plus
id|rqstp-&gt;rq_res.head
(braket
l_int|0
)braket
dot
id|iov_len
suffix:semicolon
id|resp-&gt;tagp
op_assign
id|resp-&gt;p
suffix:semicolon
multiline_comment|/* reserve space for: taglen, tag, and opcnt */
id|resp-&gt;p
op_add_assign
l_int|2
op_plus
id|XDR_QUADLEN
c_func
(paren
id|args-&gt;taglen
)paren
suffix:semicolon
id|resp-&gt;end
op_assign
id|rqstp-&gt;rq_res.head
(braket
l_int|0
)braket
dot
id|iov_base
op_plus
id|PAGE_SIZE
suffix:semicolon
id|resp-&gt;taglen
op_assign
id|args-&gt;taglen
suffix:semicolon
id|resp-&gt;tag
op_assign
id|args-&gt;tag
suffix:semicolon
id|resp-&gt;opcnt
op_assign
l_int|0
suffix:semicolon
id|resp-&gt;rqstp
op_assign
id|rqstp
suffix:semicolon
multiline_comment|/*&n;&t; * According to RFC3010, this takes precedence over all other errors.&n;&t; */
id|status
op_assign
id|nfserr_minor_vers_mismatch
suffix:semicolon
r_if
c_cond
(paren
id|args-&gt;minorversion
OG
id|NFSD_SUPPORTED_MINOR_VERSION
)paren
r_goto
id|out
suffix:semicolon
id|status
op_assign
id|nfs_ok
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|status
op_logical_and
id|resp-&gt;opcnt
OL
id|args-&gt;opcnt
)paren
(brace
id|op
op_assign
op_amp
id|args-&gt;ops
(braket
id|resp-&gt;opcnt
op_increment
)braket
suffix:semicolon
multiline_comment|/*&n;&t;&t; * The XDR decode routines may have pre-set op-&gt;status;&n;&t;&t; * for example, if there is a miscellaneous XDR error&n;&t;&t; * it will be set to nfserr_bad_xdr.&n;&t;&t; */
r_if
c_cond
(paren
id|op-&gt;status
)paren
r_goto
id|encode_op
suffix:semicolon
multiline_comment|/* We must be able to encode a successful response to&n;&t;&t; * this operation, with enough room left over to encode a&n;&t;&t; * failed response to the next operation.  If we don&squot;t&n;&t;&t; * have enough room, fail with ERR_RESOURCE.&n;&t;&t; */
multiline_comment|/* FIXME - is slack_space *really* words, or bytes??? - neilb */
id|slack_space
op_assign
(paren
r_char
op_star
)paren
id|resp-&gt;end
op_minus
(paren
r_char
op_star
)paren
id|resp-&gt;p
suffix:semicolon
r_if
c_cond
(paren
id|slack_space
OL
id|COMPOUND_SLACK_SPACE
op_plus
id|COMPOUND_ERR_SLACK_SPACE
)paren
(brace
id|BUG_ON
c_func
(paren
id|slack_space
OL
id|COMPOUND_ERR_SLACK_SPACE
)paren
suffix:semicolon
id|op-&gt;status
op_assign
id|nfserr_resource
suffix:semicolon
r_goto
id|encode_op
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|op-&gt;opnum
)paren
(brace
r_case
id|OP_ACCESS
suffix:colon
id|op-&gt;status
op_assign
id|nfsd4_access
c_func
(paren
id|rqstp
comma
op_amp
id|current_fh
comma
op_amp
id|op-&gt;u.access
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|OP_CLOSE
suffix:colon
id|op-&gt;status
op_assign
id|nfsd4_close
c_func
(paren
id|rqstp
comma
op_amp
id|current_fh
comma
op_amp
id|op-&gt;u.close
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|OP_COMMIT
suffix:colon
id|op-&gt;status
op_assign
id|nfsd4_commit
c_func
(paren
id|rqstp
comma
op_amp
id|current_fh
comma
op_amp
id|op-&gt;u.commit
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|OP_CREATE
suffix:colon
id|op-&gt;status
op_assign
id|nfsd4_create
c_func
(paren
id|rqstp
comma
op_amp
id|current_fh
comma
op_amp
id|op-&gt;u.create
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|OP_GETATTR
suffix:colon
id|op-&gt;status
op_assign
id|nfsd4_getattr
c_func
(paren
id|rqstp
comma
op_amp
id|current_fh
comma
op_amp
id|op-&gt;u.getattr
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|OP_GETFH
suffix:colon
id|op-&gt;status
op_assign
id|nfsd4_getfh
c_func
(paren
op_amp
id|current_fh
comma
op_amp
id|op-&gt;u.getfh
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|OP_LINK
suffix:colon
id|op-&gt;status
op_assign
id|nfsd4_link
c_func
(paren
id|rqstp
comma
op_amp
id|current_fh
comma
op_amp
id|save_fh
comma
op_amp
id|op-&gt;u.link
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|OP_LOOKUP
suffix:colon
id|op-&gt;status
op_assign
id|nfsd4_lookup
c_func
(paren
id|rqstp
comma
op_amp
id|current_fh
comma
op_amp
id|op-&gt;u.lookup
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|OP_LOOKUPP
suffix:colon
id|op-&gt;status
op_assign
id|nfsd4_lookupp
c_func
(paren
id|rqstp
comma
op_amp
id|current_fh
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|OP_NVERIFY
suffix:colon
id|op-&gt;status
op_assign
id|nfsd4_verify
c_func
(paren
id|rqstp
comma
op_amp
id|current_fh
comma
op_amp
id|op-&gt;u.nverify
)paren
suffix:semicolon
r_if
c_cond
(paren
id|op-&gt;status
op_eq
id|nfserr_not_same
)paren
id|op-&gt;status
op_assign
id|nfs_ok
suffix:semicolon
r_break
suffix:semicolon
r_case
id|OP_OPEN
suffix:colon
id|op-&gt;status
op_assign
id|nfsd4_open
c_func
(paren
id|rqstp
comma
op_amp
id|current_fh
comma
op_amp
id|op-&gt;u.open
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|OP_PUTFH
suffix:colon
id|op-&gt;status
op_assign
id|nfsd4_putfh
c_func
(paren
id|rqstp
comma
op_amp
id|current_fh
comma
op_amp
id|op-&gt;u.putfh
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|OP_PUTROOTFH
suffix:colon
id|op-&gt;status
op_assign
id|nfsd4_putrootfh
c_func
(paren
id|rqstp
comma
op_amp
id|current_fh
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|OP_READ
suffix:colon
id|op-&gt;status
op_assign
id|nfsd4_read
c_func
(paren
id|rqstp
comma
op_amp
id|current_fh
comma
op_amp
id|op-&gt;u.read
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|OP_READDIR
suffix:colon
id|op-&gt;status
op_assign
id|nfsd4_readdir
c_func
(paren
id|rqstp
comma
op_amp
id|current_fh
comma
op_amp
id|op-&gt;u.readdir
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|OP_READLINK
suffix:colon
id|op-&gt;status
op_assign
id|nfsd4_readlink
c_func
(paren
id|rqstp
comma
op_amp
id|current_fh
comma
op_amp
id|op-&gt;u.readlink
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|OP_REMOVE
suffix:colon
id|op-&gt;status
op_assign
id|nfsd4_remove
c_func
(paren
id|rqstp
comma
op_amp
id|current_fh
comma
op_amp
id|op-&gt;u.remove
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|OP_RENAME
suffix:colon
id|op-&gt;status
op_assign
id|nfsd4_rename
c_func
(paren
id|rqstp
comma
op_amp
id|current_fh
comma
op_amp
id|save_fh
comma
op_amp
id|op-&gt;u.rename
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|OP_RENEW
suffix:colon
id|op-&gt;status
op_assign
id|nfsd4_renew
c_func
(paren
op_amp
id|op-&gt;u.renew
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|OP_RESTOREFH
suffix:colon
id|op-&gt;status
op_assign
id|nfsd4_restorefh
c_func
(paren
op_amp
id|current_fh
comma
op_amp
id|save_fh
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|OP_SAVEFH
suffix:colon
id|op-&gt;status
op_assign
id|nfsd4_savefh
c_func
(paren
op_amp
id|current_fh
comma
op_amp
id|save_fh
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|OP_SETATTR
suffix:colon
id|op-&gt;status
op_assign
id|nfsd4_setattr
c_func
(paren
id|rqstp
comma
op_amp
id|current_fh
comma
op_amp
id|op-&gt;u.setattr
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|OP_SETCLIENTID
suffix:colon
id|op-&gt;status
op_assign
id|nfsd4_setclientid
c_func
(paren
id|rqstp
comma
op_amp
id|op-&gt;u.setclientid
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|OP_SETCLIENTID_CONFIRM
suffix:colon
id|op-&gt;status
op_assign
id|nfsd4_setclientid_confirm
c_func
(paren
id|rqstp
comma
op_amp
id|op-&gt;u.setclientid_confirm
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|OP_VERIFY
suffix:colon
id|op-&gt;status
op_assign
id|nfsd4_verify
c_func
(paren
id|rqstp
comma
op_amp
id|current_fh
comma
op_amp
id|op-&gt;u.verify
)paren
suffix:semicolon
r_if
c_cond
(paren
id|op-&gt;status
op_eq
id|nfserr_same
)paren
id|op-&gt;status
op_assign
id|nfs_ok
suffix:semicolon
r_break
suffix:semicolon
r_case
id|OP_WRITE
suffix:colon
id|op-&gt;status
op_assign
id|nfsd4_write
c_func
(paren
id|rqstp
comma
op_amp
id|current_fh
comma
op_amp
id|op-&gt;u.write
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|BUG_ON
c_func
(paren
id|op-&gt;status
op_eq
id|nfs_ok
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|encode_op
suffix:colon
id|nfsd4_encode_operation
c_func
(paren
id|resp
comma
id|op
)paren
suffix:semicolon
id|status
op_assign
id|op-&gt;status
suffix:semicolon
)brace
id|out
suffix:colon
r_if
c_cond
(paren
id|args-&gt;ops
op_ne
id|args-&gt;iops
)paren
(brace
id|kfree
c_func
(paren
id|args-&gt;ops
)paren
suffix:semicolon
id|args-&gt;ops
op_assign
id|args-&gt;iops
suffix:semicolon
)brace
r_if
c_cond
(paren
id|args-&gt;tmpp
)paren
(brace
id|kfree
c_func
(paren
id|args-&gt;tmpp
)paren
suffix:semicolon
id|args-&gt;tmpp
op_assign
l_int|NULL
suffix:semicolon
)brace
r_while
c_loop
(paren
id|args-&gt;to_free
)paren
(brace
r_struct
id|tmpbuf
op_star
id|tb
op_assign
id|args-&gt;to_free
suffix:semicolon
id|args-&gt;to_free
op_assign
id|tb-&gt;next
suffix:semicolon
id|kfree
c_func
(paren
id|tb-&gt;buf
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|tb
)paren
suffix:semicolon
)brace
id|fh_put
c_func
(paren
op_amp
id|current_fh
)paren
suffix:semicolon
id|fh_put
c_func
(paren
op_amp
id|save_fh
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
DECL|macro|nfs4svc_decode_voidargs
mdefine_line|#define nfs4svc_decode_voidargs&t;&t;NULL
DECL|macro|nfs4svc_release_void
mdefine_line|#define nfs4svc_release_void&t;&t;NULL
DECL|macro|nfsd4_voidres
mdefine_line|#define nfsd4_voidres&t;&t;&t;nfsd4_voidargs
DECL|macro|nfs4svc_release_compound
mdefine_line|#define nfs4svc_release_compound&t;NULL
DECL|struct|nfsd4_voidargs
DECL|member|dummy
r_struct
id|nfsd4_voidargs
(brace
r_int
id|dummy
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|PROC
mdefine_line|#define PROC(name, argt, rest, relt, cache, respsize)&t;&bslash;&n; { (svc_procfunc) nfsd4_proc_##name,&t;&t;&bslash;&n;   (kxdrproc_t) nfs4svc_decode_##argt##args,&t;&bslash;&n;   (kxdrproc_t) nfs4svc_encode_##rest##res,&t;&bslash;&n;   (kxdrproc_t) nfs4svc_release_##relt,&t;&t;&bslash;&n;   sizeof(struct nfsd4_##argt##args),&t;&t;&bslash;&n;   sizeof(struct nfsd4_##rest##res),&t;&t;&bslash;&n;   0,&t;&t;&t;&t;&t;&t;&bslash;&n;   cache,&t;&t;&t;&t;&t;&bslash;&n;   respsize,&t;&t;&t;&t;&t;&bslash;&n; }
multiline_comment|/*&n; * TODO: At the present time, the NFSv4 server does not do XID caching&n; * of requests.  Implementing XID caching would not be a serious problem,&n; * although it would require a mild change in interfaces since one&n; * doesn&squot;t know whether an NFSv4 request is idempotent until after the&n; * XDR decode.  However, XID caching totally confuses pynfs (Peter&n; * Astrand&squot;s regression testsuite for NFSv4 servers), which reuses&n; * XID&squot;s liberally, so I&squot;ve left it unimplemented until pynfs generates&n; * better XID&squot;s.&n; */
DECL|variable|nfsd_procedures4
r_static
r_struct
id|svc_procedure
id|nfsd_procedures4
(braket
l_int|2
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
l_int|1
)paren
comma
id|PROC
c_func
(paren
id|compound
comma
id|compound
comma
id|compound
comma
id|compound
comma
id|RC_NOCACHE
comma
id|NFSD_BUFSIZE
)paren
)brace
suffix:semicolon
DECL|variable|nfsd_version4
r_struct
id|svc_version
id|nfsd_version4
op_assign
(brace
dot
id|vs_vers
op_assign
l_int|4
comma
dot
id|vs_nproc
op_assign
l_int|2
comma
dot
id|vs_proc
op_assign
id|nfsd_procedures4
comma
dot
id|vs_dispatch
op_assign
id|nfsd_dispatch
comma
dot
id|vs_xdrsize
op_assign
id|NFS4_SVC_XDRSIZE
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * Local variables:&n; *  c-basic-offset: 8&n; * End:&n; */
eof
