multiline_comment|/*&n; *  include/linux/nfsd/xdr4.h&n; *&n; *  Server-side types for NFSv4.&n; *&n; *  Copyright (c) 2002 The Regents of the University of Michigan.&n; *  All rights reserved.&n; *&n; *  Kendrick Smith &lt;kmsmith@umich.edu&gt;&n; *  Andy Adamson   &lt;andros@umich.edu&gt;&n; *&n; *  Redistribution and use in source and binary forms, with or without&n; *  modification, are permitted provided that the following conditions&n; *  are met:&n; *&n; *  1. Redistributions of source code must retain the above copyright&n; *     notice, this list of conditions and the following disclaimer.&n; *  2. Redistributions in binary form must reproduce the above copyright&n; *     notice, this list of conditions and the following disclaimer in the&n; *     documentation and/or other materials provided with the distribution.&n; *  3. Neither the name of the University nor the names of its&n; *     contributors may be used to endorse or promote products derived&n; *     from this software without specific prior written permission.&n; *&n; *  THIS SOFTWARE IS PROVIDED ``AS IS&squot;&squot; AND ANY EXPRESS OR IMPLIED&n; *  WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF&n; *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE&n; *  DISCLAIMED. IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE&n; *  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR&n; *  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF&n; *  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR&n; *  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF&n; *  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING&n; *  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS&n; *  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; */
macro_line|#ifndef _LINUX_NFSD_XDR4_H
DECL|macro|_LINUX_NFSD_XDR4_H
mdefine_line|#define _LINUX_NFSD_XDR4_H
DECL|macro|NFSD4_MAX_TAGLEN
mdefine_line|#define NFSD4_MAX_TAGLEN&t;128
r_typedef
r_struct
(brace
DECL|member|cl_boot
id|u32
id|cl_boot
suffix:semicolon
DECL|member|cl_id
id|u32
id|cl_id
suffix:semicolon
DECL|typedef|clientid_t
)brace
id|clientid_t
suffix:semicolon
DECL|typedef|stateid_boot_t
r_typedef
id|u32
id|stateid_boot_t
suffix:semicolon
multiline_comment|/* used to detect stale stateids */
DECL|typedef|stateid_lockowner_t
r_typedef
id|u32
id|stateid_lockowner_t
suffix:semicolon
multiline_comment|/* lockowner id - used in various places */
DECL|typedef|stateid_file_t
r_typedef
id|u32
id|stateid_file_t
suffix:semicolon
multiline_comment|/* identifies a unique file per lockowner */
DECL|typedef|stateid_generation_t
r_typedef
id|u32
id|stateid_generation_t
suffix:semicolon
multiline_comment|/* used to update stateids */
r_typedef
r_struct
(brace
DECL|member|so_boot
id|stateid_boot_t
id|so_boot
suffix:semicolon
DECL|member|so_lockowner
id|stateid_lockowner_t
id|so_lockowner
suffix:semicolon
DECL|member|so_file
id|stateid_file_t
id|so_file
suffix:semicolon
DECL|typedef|stateid_other_t
)brace
id|stateid_other_t
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|st_generation
id|stateid_generation_t
id|st_generation
suffix:semicolon
DECL|member|st_other
id|stateid_other_t
id|st_other
suffix:semicolon
DECL|typedef|stateid_t
)brace
id|stateid_t
suffix:semicolon
DECL|typedef|delegation_zero_t
r_typedef
id|u32
id|delegation_zero_t
suffix:semicolon
DECL|typedef|delegation_boot_t
r_typedef
id|u32
id|delegation_boot_t
suffix:semicolon
DECL|typedef|delegation_id_t
r_typedef
id|u64
id|delegation_id_t
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|ds_zero
id|delegation_zero_t
id|ds_zero
suffix:semicolon
DECL|member|ds_boot
id|delegation_boot_t
id|ds_boot
suffix:semicolon
DECL|member|ds_id
id|delegation_id_t
id|ds_id
suffix:semicolon
DECL|typedef|delegation_stateid_t
)brace
id|delegation_stateid_t
suffix:semicolon
DECL|struct|nfsd4_change_info
r_struct
id|nfsd4_change_info
(brace
DECL|member|atomic
id|u32
id|atomic
suffix:semicolon
DECL|member|before_size
id|u32
id|before_size
suffix:semicolon
DECL|member|before_ctime
id|u32
id|before_ctime
suffix:semicolon
DECL|member|after_size
id|u32
id|after_size
suffix:semicolon
DECL|member|after_ctime
id|u32
id|after_ctime
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|nfsd4_access
r_struct
id|nfsd4_access
(brace
DECL|member|ac_req_access
id|u32
id|ac_req_access
suffix:semicolon
multiline_comment|/* request */
DECL|member|ac_supported
id|u32
id|ac_supported
suffix:semicolon
multiline_comment|/* response */
DECL|member|ac_resp_access
id|u32
id|ac_resp_access
suffix:semicolon
multiline_comment|/* response */
)brace
suffix:semicolon
DECL|struct|nfsd4_close
r_struct
id|nfsd4_close
(brace
DECL|member|cl_seqid
id|u32
id|cl_seqid
suffix:semicolon
multiline_comment|/* request */
DECL|member|cl_stateid
id|stateid_t
id|cl_stateid
suffix:semicolon
multiline_comment|/* request+response */
)brace
suffix:semicolon
DECL|struct|nfsd4_commit
r_struct
id|nfsd4_commit
(brace
DECL|member|co_offset
id|u64
id|co_offset
suffix:semicolon
multiline_comment|/* request */
DECL|member|co_count
id|u32
id|co_count
suffix:semicolon
multiline_comment|/* request */
DECL|member|co_verf
id|nfs4_verifier
id|co_verf
suffix:semicolon
multiline_comment|/* response */
)brace
suffix:semicolon
DECL|struct|nfsd4_create
r_struct
id|nfsd4_create
(brace
DECL|member|cr_namelen
id|u32
id|cr_namelen
suffix:semicolon
multiline_comment|/* request */
DECL|member|cr_name
r_char
op_star
id|cr_name
suffix:semicolon
multiline_comment|/* request */
DECL|member|cr_type
id|u32
id|cr_type
suffix:semicolon
multiline_comment|/* request */
r_union
(brace
multiline_comment|/* request */
r_struct
(brace
DECL|member|namelen
id|u32
id|namelen
suffix:semicolon
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|link
)brace
id|link
suffix:semicolon
multiline_comment|/* NF4LNK */
r_struct
(brace
DECL|member|specdata1
id|u32
id|specdata1
suffix:semicolon
DECL|member|specdata2
id|u32
id|specdata2
suffix:semicolon
DECL|member|dev
)brace
id|dev
suffix:semicolon
multiline_comment|/* NF4BLK, NF4CHR */
DECL|member|u
)brace
id|u
suffix:semicolon
DECL|member|cr_bmval
id|u32
id|cr_bmval
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* request */
DECL|member|cr_iattr
r_struct
id|iattr
id|cr_iattr
suffix:semicolon
multiline_comment|/* request */
DECL|member|cr_cinfo
r_struct
id|nfsd4_change_info
id|cr_cinfo
suffix:semicolon
multiline_comment|/* response */
)brace
suffix:semicolon
DECL|macro|cr_linklen
mdefine_line|#define cr_linklen&t;u.link.namelen
DECL|macro|cr_linkname
mdefine_line|#define cr_linkname&t;u.link.name
DECL|macro|cr_specdata1
mdefine_line|#define cr_specdata1&t;u.dev.specdata1
DECL|macro|cr_specdata2
mdefine_line|#define cr_specdata2&t;u.dev.specdata2
DECL|struct|nfsd4_getattr
r_struct
id|nfsd4_getattr
(brace
DECL|member|ga_bmval
id|u32
id|ga_bmval
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* request */
DECL|member|ga_fhp
r_struct
id|svc_fh
op_star
id|ga_fhp
suffix:semicolon
multiline_comment|/* response */
)brace
suffix:semicolon
DECL|struct|nfsd4_link
r_struct
id|nfsd4_link
(brace
DECL|member|li_namelen
id|u32
id|li_namelen
suffix:semicolon
multiline_comment|/* request */
DECL|member|li_name
r_char
op_star
id|li_name
suffix:semicolon
multiline_comment|/* request */
DECL|member|li_cinfo
r_struct
id|nfsd4_change_info
id|li_cinfo
suffix:semicolon
multiline_comment|/* response */
)brace
suffix:semicolon
DECL|struct|nfsd4_lookup
r_struct
id|nfsd4_lookup
(brace
DECL|member|lo_len
id|u32
id|lo_len
suffix:semicolon
multiline_comment|/* request */
DECL|member|lo_name
r_char
op_star
id|lo_name
suffix:semicolon
multiline_comment|/* request */
)brace
suffix:semicolon
DECL|struct|nfsd4_putfh
r_struct
id|nfsd4_putfh
(brace
DECL|member|pf_fhlen
id|u32
id|pf_fhlen
suffix:semicolon
multiline_comment|/* request */
DECL|member|pf_fhval
r_char
op_star
id|pf_fhval
suffix:semicolon
multiline_comment|/* request */
)brace
suffix:semicolon
DECL|struct|nfsd4_open
r_struct
id|nfsd4_open
(brace
DECL|member|op_claim_type
id|u32
id|op_claim_type
suffix:semicolon
multiline_comment|/* request */
DECL|member|op_namelen
id|u32
id|op_namelen
suffix:semicolon
multiline_comment|/* request - everything but CLAIM_PREV */
DECL|member|op_name
r_char
op_star
id|op_name
suffix:semicolon
multiline_comment|/* request - everything but CLAIM_PREV */
DECL|member|op_delegate_type
id|u32
id|op_delegate_type
suffix:semicolon
multiline_comment|/* request - CLAIM_PREV only */
DECL|member|op_delegate_stateid
id|delegation_stateid_t
id|op_delegate_stateid
suffix:semicolon
multiline_comment|/* request - CLAIM_DELEGATE_CUR only */
DECL|member|op_create
id|u32
id|op_create
suffix:semicolon
multiline_comment|/* request */
DECL|member|op_createmode
id|u32
id|op_createmode
suffix:semicolon
multiline_comment|/* request */
DECL|member|op_bmval
id|u32
id|op_bmval
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* request */
r_union
(brace
multiline_comment|/* request */
DECL|member|iattr
r_struct
id|iattr
id|iattr
suffix:semicolon
multiline_comment|/* UNCHECKED4,GUARDED4 */
DECL|member|verf
id|nfs4_verifier
id|verf
suffix:semicolon
multiline_comment|/* EXCLUSIVE4 */
DECL|member|u
)brace
id|u
suffix:semicolon
DECL|member|op_clientid
id|clientid_t
id|op_clientid
suffix:semicolon
multiline_comment|/* request */
DECL|member|op_ownerlen
id|u32
id|op_ownerlen
suffix:semicolon
multiline_comment|/* request */
DECL|member|op_owner
r_char
op_star
id|op_owner
suffix:semicolon
multiline_comment|/* request */
DECL|member|op_seqid
id|u32
id|op_seqid
suffix:semicolon
multiline_comment|/* request */
DECL|member|op_share_access
id|u32
id|op_share_access
suffix:semicolon
multiline_comment|/* request */
DECL|member|op_share_deny
id|u32
id|op_share_deny
suffix:semicolon
multiline_comment|/* request */
DECL|member|op_stateid
id|stateid_t
id|op_stateid
suffix:semicolon
multiline_comment|/* response */
DECL|member|op_cinfo
r_struct
id|nfsd4_change_info
id|op_cinfo
suffix:semicolon
multiline_comment|/* response */
DECL|member|op_rflags
id|u32
id|op_rflags
suffix:semicolon
multiline_comment|/* response */
DECL|member|op_truncate
r_int
id|op_truncate
suffix:semicolon
multiline_comment|/* used during processing */
)brace
suffix:semicolon
DECL|macro|op_iattr
mdefine_line|#define op_iattr&t;u.iattr
DECL|macro|op_verf
mdefine_line|#define op_verf&t;&t;u.verf
DECL|struct|nfsd4_read
r_struct
id|nfsd4_read
(brace
DECL|member|rd_stateid
id|stateid_t
id|rd_stateid
suffix:semicolon
multiline_comment|/* request */
DECL|member|rd_offset
id|u64
id|rd_offset
suffix:semicolon
multiline_comment|/* request */
DECL|member|rd_length
id|u32
id|rd_length
suffix:semicolon
multiline_comment|/* request */
DECL|member|rd_rqstp
r_struct
id|svc_rqst
op_star
id|rd_rqstp
suffix:semicolon
multiline_comment|/* response */
DECL|member|rd_fhp
r_struct
id|svc_fh
op_star
id|rd_fhp
suffix:semicolon
multiline_comment|/* response */
)brace
suffix:semicolon
DECL|struct|nfsd4_readdir
r_struct
id|nfsd4_readdir
(brace
DECL|member|rd_cookie
id|u64
id|rd_cookie
suffix:semicolon
multiline_comment|/* request */
DECL|member|rd_verf
id|nfs4_verifier
id|rd_verf
suffix:semicolon
multiline_comment|/* request */
DECL|member|rd_dircount
id|u32
id|rd_dircount
suffix:semicolon
multiline_comment|/* request */
DECL|member|rd_maxcount
id|u32
id|rd_maxcount
suffix:semicolon
multiline_comment|/* request */
DECL|member|rd_bmval
id|u32
id|rd_bmval
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* request */
DECL|member|rd_rqstp
r_struct
id|svc_rqst
op_star
id|rd_rqstp
suffix:semicolon
multiline_comment|/* response */
DECL|member|rd_fhp
r_struct
id|svc_fh
op_star
id|rd_fhp
suffix:semicolon
multiline_comment|/* response */
)brace
suffix:semicolon
DECL|struct|nfsd4_readlink
r_struct
id|nfsd4_readlink
(brace
DECL|member|rl_rqstp
r_struct
id|svc_rqst
op_star
id|rl_rqstp
suffix:semicolon
multiline_comment|/* request */
DECL|member|rl_fhp
r_struct
id|svc_fh
op_star
id|rl_fhp
suffix:semicolon
multiline_comment|/* request */
)brace
suffix:semicolon
DECL|struct|nfsd4_remove
r_struct
id|nfsd4_remove
(brace
DECL|member|rm_namelen
id|u32
id|rm_namelen
suffix:semicolon
multiline_comment|/* request */
DECL|member|rm_name
r_char
op_star
id|rm_name
suffix:semicolon
multiline_comment|/* request */
DECL|member|rm_cinfo
r_struct
id|nfsd4_change_info
id|rm_cinfo
suffix:semicolon
multiline_comment|/* response */
)brace
suffix:semicolon
DECL|struct|nfsd4_rename
r_struct
id|nfsd4_rename
(brace
DECL|member|rn_snamelen
id|u32
id|rn_snamelen
suffix:semicolon
multiline_comment|/* request */
DECL|member|rn_sname
r_char
op_star
id|rn_sname
suffix:semicolon
multiline_comment|/* request */
DECL|member|rn_tnamelen
id|u32
id|rn_tnamelen
suffix:semicolon
multiline_comment|/* request */
DECL|member|rn_tname
r_char
op_star
id|rn_tname
suffix:semicolon
multiline_comment|/* request */
DECL|member|rn_sinfo
r_struct
id|nfsd4_change_info
id|rn_sinfo
suffix:semicolon
multiline_comment|/* response */
DECL|member|rn_tinfo
r_struct
id|nfsd4_change_info
id|rn_tinfo
suffix:semicolon
multiline_comment|/* response */
)brace
suffix:semicolon
DECL|struct|nfsd4_setattr
r_struct
id|nfsd4_setattr
(brace
DECL|member|sa_stateid
id|stateid_t
id|sa_stateid
suffix:semicolon
multiline_comment|/* request */
DECL|member|sa_bmval
id|u32
id|sa_bmval
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* request */
DECL|member|sa_iattr
r_struct
id|iattr
id|sa_iattr
suffix:semicolon
multiline_comment|/* request */
)brace
suffix:semicolon
DECL|struct|nfsd4_setclientid
r_struct
id|nfsd4_setclientid
(brace
DECL|member|se_verf
id|nfs4_verifier
id|se_verf
suffix:semicolon
multiline_comment|/* request */
DECL|member|se_namelen
id|u32
id|se_namelen
suffix:semicolon
multiline_comment|/* request */
DECL|member|se_name
r_char
op_star
id|se_name
suffix:semicolon
multiline_comment|/* request */
DECL|member|se_callback_prog
id|u32
id|se_callback_prog
suffix:semicolon
multiline_comment|/* request */
DECL|member|se_callback_netid_len
id|u32
id|se_callback_netid_len
suffix:semicolon
multiline_comment|/* request */
DECL|member|se_callback_netid_val
r_char
op_star
id|se_callback_netid_val
suffix:semicolon
multiline_comment|/* request */
DECL|member|se_callback_addr_len
id|u32
id|se_callback_addr_len
suffix:semicolon
multiline_comment|/* request */
DECL|member|se_callback_addr_val
r_char
op_star
id|se_callback_addr_val
suffix:semicolon
multiline_comment|/* request */
DECL|member|se_callback_ident
id|u32
id|se_callback_ident
suffix:semicolon
multiline_comment|/* request */
DECL|member|se_clientid
id|clientid_t
id|se_clientid
suffix:semicolon
multiline_comment|/* response */
)brace
suffix:semicolon
multiline_comment|/* also used for NVERIFY */
DECL|struct|nfsd4_verify
r_struct
id|nfsd4_verify
(brace
DECL|member|ve_bmval
id|u32
id|ve_bmval
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* request */
DECL|member|ve_attrlen
id|u32
id|ve_attrlen
suffix:semicolon
multiline_comment|/* request */
DECL|member|ve_attrval
r_char
op_star
id|ve_attrval
suffix:semicolon
multiline_comment|/* request */
)brace
suffix:semicolon
DECL|struct|nfsd4_write
r_struct
id|nfsd4_write
(brace
DECL|member|wr_stateid
id|stateid_t
id|wr_stateid
suffix:semicolon
multiline_comment|/* request */
DECL|member|wr_offset
id|u64
id|wr_offset
suffix:semicolon
multiline_comment|/* request */
DECL|member|wr_stable_how
id|u32
id|wr_stable_how
suffix:semicolon
multiline_comment|/* request */
DECL|member|wr_buflen
id|u32
id|wr_buflen
suffix:semicolon
multiline_comment|/* request */
DECL|member|wr_buf
r_char
op_star
id|wr_buf
suffix:semicolon
multiline_comment|/* request */
DECL|member|wr_bytes_written
id|u32
id|wr_bytes_written
suffix:semicolon
multiline_comment|/* response */
DECL|member|wr_how_written
id|u32
id|wr_how_written
suffix:semicolon
multiline_comment|/* response */
DECL|member|wr_verifier
id|nfs4_verifier
id|wr_verifier
suffix:semicolon
multiline_comment|/* response */
)brace
suffix:semicolon
DECL|struct|nfsd4_op
r_struct
id|nfsd4_op
(brace
DECL|member|opnum
r_int
id|opnum
suffix:semicolon
DECL|member|status
r_int
id|status
suffix:semicolon
r_union
(brace
DECL|member|access
r_struct
id|nfsd4_access
id|access
suffix:semicolon
DECL|member|close
r_struct
id|nfsd4_close
id|close
suffix:semicolon
DECL|member|commit
r_struct
id|nfsd4_commit
id|commit
suffix:semicolon
DECL|member|create
r_struct
id|nfsd4_create
id|create
suffix:semicolon
DECL|member|getattr
r_struct
id|nfsd4_getattr
id|getattr
suffix:semicolon
DECL|member|getfh
r_struct
id|svc_fh
op_star
id|getfh
suffix:semicolon
DECL|member|link
r_struct
id|nfsd4_link
id|link
suffix:semicolon
DECL|member|lookup
r_struct
id|nfsd4_lookup
id|lookup
suffix:semicolon
DECL|member|nverify
r_struct
id|nfsd4_verify
id|nverify
suffix:semicolon
DECL|member|open
r_struct
id|nfsd4_open
id|open
suffix:semicolon
DECL|member|putfh
r_struct
id|nfsd4_putfh
id|putfh
suffix:semicolon
DECL|member|read
r_struct
id|nfsd4_read
id|read
suffix:semicolon
DECL|member|readdir
r_struct
id|nfsd4_readdir
id|readdir
suffix:semicolon
DECL|member|readlink
r_struct
id|nfsd4_readlink
id|readlink
suffix:semicolon
DECL|member|remove
r_struct
id|nfsd4_remove
id|remove
suffix:semicolon
DECL|member|rename
r_struct
id|nfsd4_rename
id|rename
suffix:semicolon
DECL|member|renew
id|clientid_t
id|renew
suffix:semicolon
DECL|member|setattr
r_struct
id|nfsd4_setattr
id|setattr
suffix:semicolon
DECL|member|setclientid
r_struct
id|nfsd4_setclientid
id|setclientid
suffix:semicolon
DECL|member|setclientid_confirm
id|clientid_t
id|setclientid_confirm
suffix:semicolon
DECL|member|verify
r_struct
id|nfsd4_verify
id|verify
suffix:semicolon
DECL|member|write
r_struct
id|nfsd4_write
id|write
suffix:semicolon
DECL|member|u
)brace
id|u
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|nfsd4_compoundargs
r_struct
id|nfsd4_compoundargs
(brace
multiline_comment|/* scratch variables for XDR decode */
DECL|member|p
id|u32
op_star
id|p
suffix:semicolon
DECL|member|end
id|u32
op_star
id|end
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
DECL|member|minorversion
id|u32
id|minorversion
suffix:semicolon
DECL|member|opcnt
id|u32
id|opcnt
suffix:semicolon
DECL|member|ops
r_struct
id|nfsd4_op
op_star
id|ops
suffix:semicolon
DECL|member|iops
r_struct
id|nfsd4_op
id|iops
(braket
l_int|8
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|nfsd4_compoundres
r_struct
id|nfsd4_compoundres
(brace
multiline_comment|/* scratch variables for XDR encode */
DECL|member|p
id|u32
op_star
id|p
suffix:semicolon
DECL|member|end
id|u32
op_star
id|end
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
DECL|member|opcnt
id|u32
id|opcnt
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|NFS4_SVC_XDRSIZE
mdefine_line|#define NFS4_SVC_XDRSIZE&t;&t;sizeof(struct nfsd4_compoundargs)
macro_line|#if CONFIG_NFSD_V3
r_static
r_inline
r_void
DECL|function|set_change_info
id|set_change_info
c_func
(paren
r_struct
id|nfsd4_change_info
op_star
id|cinfo
comma
r_struct
id|svc_fh
op_star
id|fhp
)paren
(brace
id|BUG_ON
c_func
(paren
op_logical_neg
id|fhp-&gt;fh_pre_saved
op_logical_or
op_logical_neg
id|fhp-&gt;fh_post_saved
)paren
suffix:semicolon
id|cinfo-&gt;atomic
op_assign
l_int|1
suffix:semicolon
id|cinfo-&gt;before_size
op_assign
id|fhp-&gt;fh_pre_size
suffix:semicolon
id|cinfo-&gt;before_ctime
op_assign
id|fhp-&gt;fh_pre_ctime
suffix:semicolon
id|cinfo-&gt;after_size
op_assign
id|fhp-&gt;fh_post_size
suffix:semicolon
id|cinfo-&gt;after_ctime
op_assign
id|fhp-&gt;fh_post_ctime
suffix:semicolon
)brace
macro_line|#endif
r_int
id|nfs4svc_encode_voidres
c_func
(paren
r_struct
id|svc_rqst
op_star
comma
id|u32
op_star
comma
r_void
op_star
)paren
suffix:semicolon
r_int
id|nfs4svc_decode_compoundargs
c_func
(paren
r_struct
id|svc_rqst
op_star
comma
id|u32
op_star
comma
r_struct
id|nfsd4_compoundargs
op_star
)paren
suffix:semicolon
r_int
id|nfs4svc_encode_compoundres
c_func
(paren
r_struct
id|svc_rqst
op_star
comma
id|u32
op_star
comma
r_struct
id|nfsd4_compoundres
op_star
)paren
suffix:semicolon
r_void
id|nfsd4_encode_operation
c_func
(paren
r_struct
id|nfsd4_compoundres
op_star
comma
r_struct
id|nfsd4_op
op_star
)paren
suffix:semicolon
r_int
id|nfsd4_encode_fattr
c_func
(paren
r_struct
id|svc_fh
op_star
id|fhp
comma
r_struct
id|svc_export
op_star
id|exp
comma
r_struct
id|dentry
op_star
id|dentry
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
id|bmval
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * Local variables:&n; *  c-basic-offset: 8&n; * End:&n; */
eof
