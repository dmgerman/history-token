multiline_comment|/*&n; *  linux/include/nfsd/state.h&n; *&n; *  Copyright (c) 2001 The Regents of the University of Michigan.&n; *  All rights reserved.&n; *&n; *  Kendrick Smith &lt;kmsmith@umich.edu&gt;&n; *  Andy Adamson &lt;andros@umich.edu&gt;&n; *  &n; *  Redistribution and use in source and binary forms, with or without&n; *  modification, are permitted provided that the following conditions&n; *  are met:&n; *  &n; *  1. Redistributions of source code must retain the above copyright&n; *     notice, this list of conditions and the following disclaimer.&n; *  2. Redistributions in binary form must reproduce the above copyright&n; *     notice, this list of conditions and the following disclaimer in the&n; *     documentation and/or other materials provided with the distribution.&n; *  3. Neither the name of the University nor the names of its&n; *     contributors may be used to endorse or promote products derived&n; *     from this software without specific prior written permission.&n; *&n; *  THIS SOFTWARE IS PROVIDED ``AS IS&squot;&squot; AND ANY EXPRESS OR IMPLIED&n; *  WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF&n; *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE&n; *  DISCLAIMED. IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE&n; *  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR&n; *  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF&n; *  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR&n; *  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF&n; *  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING&n; *  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS&n; *  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; */
macro_line|#ifndef _NFSD4_STATE_H
DECL|macro|_NFSD4_STATE_H
mdefine_line|#define _NFSD4_STATE_H
macro_line|#include &lt;linux/list.h&gt;
DECL|macro|NFS4_OPAQUE_LIMIT
mdefine_line|#define NFS4_OPAQUE_LIMIT 1024
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
r_typedef
r_struct
(brace
DECL|member|so_boot
id|u32
id|so_boot
suffix:semicolon
DECL|member|so_stateownerid
id|u32
id|so_stateownerid
suffix:semicolon
DECL|member|so_fileid
id|u32
id|so_fileid
suffix:semicolon
DECL|typedef|stateid_opaque_t
)brace
id|stateid_opaque_t
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|si_generation
id|u32
id|si_generation
suffix:semicolon
DECL|member|si_opaque
id|stateid_opaque_t
id|si_opaque
suffix:semicolon
DECL|typedef|stateid_t
)brace
id|stateid_t
suffix:semicolon
DECL|macro|si_boot
mdefine_line|#define si_boot           si_opaque.so_boot
DECL|macro|si_stateownerid
mdefine_line|#define si_stateownerid   si_opaque.so_stateownerid
DECL|macro|si_fileid
mdefine_line|#define si_fileid         si_opaque.so_fileid
r_extern
id|stateid_t
id|zerostateid
suffix:semicolon
r_extern
id|stateid_t
id|onestateid
suffix:semicolon
DECL|macro|ZERO_STATEID
mdefine_line|#define ZERO_STATEID(stateid)       (!memcmp((stateid), &amp;zerostateid, sizeof(stateid_t)))
DECL|macro|ONE_STATEID
mdefine_line|#define ONE_STATEID(stateid)        (!memcmp((stateid), &amp;onestateid, sizeof(stateid_t)))
multiline_comment|/*&n; * struct nfs4_client - one per client.  Clientids live here.&n; * &t;o Each nfs4_client is hashed by clientid.&n; *&n; * &t;o Each nfs4_clients is also hashed by name &n; * &t;  (the opaque quantity initially sent by the client to identify itself).&n; * &t;  &n; *&t;o cl_perclient list is used to ensure no dangling stateowner references&n; *&t;  when we expire the nfs4_client&n; */
DECL|struct|nfs4_client
r_struct
id|nfs4_client
(brace
DECL|member|cl_idhash
r_struct
id|list_head
id|cl_idhash
suffix:semicolon
multiline_comment|/* hash by cl_clientid.id */
DECL|member|cl_strhash
r_struct
id|list_head
id|cl_strhash
suffix:semicolon
multiline_comment|/* hash by cl_name */
DECL|member|cl_perclient
r_struct
id|list_head
id|cl_perclient
suffix:semicolon
multiline_comment|/* list: stateowners */
DECL|member|cl_lru
r_struct
id|list_head
id|cl_lru
suffix:semicolon
multiline_comment|/* tail queue */
DECL|member|cl_name
r_struct
id|xdr_netobj
id|cl_name
suffix:semicolon
multiline_comment|/* id generated by client */
DECL|member|cl_verifier
id|nfs4_verifier
id|cl_verifier
suffix:semicolon
multiline_comment|/* generated by client */
DECL|member|cl_time
id|time_t
id|cl_time
suffix:semicolon
multiline_comment|/* time of last lease renewal */
DECL|member|cl_addr
id|u32
id|cl_addr
suffix:semicolon
multiline_comment|/* client ipaddress */
DECL|member|cl_cred
r_struct
id|svc_cred
id|cl_cred
suffix:semicolon
multiline_comment|/* setclientid principal */
DECL|member|cl_clientid
id|clientid_t
id|cl_clientid
suffix:semicolon
multiline_comment|/* generated by server */
DECL|member|cl_confirm
id|nfs4_verifier
id|cl_confirm
suffix:semicolon
multiline_comment|/* generated by server */
)brace
suffix:semicolon
r_static
r_inline
r_void
DECL|function|update_stateid
id|update_stateid
c_func
(paren
id|stateid_t
op_star
id|stateid
)paren
(brace
id|stateid-&gt;si_generation
op_increment
suffix:semicolon
)brace
multiline_comment|/* A reasonable value for REPLAY_ISIZE was estimated as follows:  &n; * The OPEN response, typically the largest, requires &n; *   4(status) + 8(stateid) + 20(changeinfo) + 4(rflags) +  8(verifier) + &n; *   4(deleg. type) + 8(deleg. stateid) + 4(deleg. recall flag) + &n; *   20(deleg. space limit) + ~32(deleg. ace) = 112 bytes &n; */
DECL|macro|NFSD4_REPLAY_ISIZE
mdefine_line|#define NFSD4_REPLAY_ISIZE       112 
multiline_comment|/*&n; * Replay buffer, where the result of the last seqid-mutating operation &n; * is cached. &n; */
DECL|struct|nfs4_replay
r_struct
id|nfs4_replay
(brace
DECL|member|rp_status
id|u32
id|rp_status
suffix:semicolon
DECL|member|rp_buflen
r_int
r_int
id|rp_buflen
suffix:semicolon
DECL|member|rp_buf
r_char
op_star
id|rp_buf
suffix:semicolon
DECL|member|intrp_allocated
r_int
id|intrp_allocated
suffix:semicolon
DECL|member|rp_ibuf
r_char
id|rp_ibuf
(braket
id|NFSD4_REPLAY_ISIZE
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n;* nfs4_stateowner can either be an open_owner, or a lock_owner&n;*&n;*    so_idhash:  stateid_hashtbl[] for open owner, lockstateid_hashtbl[]&n;*         for lock_owner&n;*    so_strhash: ownerstr_hashtbl[] for open_owner, lock_ownerstr_hashtbl[]&n;*         for lock_owner&n;*    so_perclient: nfs4_client-&gt;cl_perclient entry - used when nfs4_client&n;*         struct is reaped.&n;*    so_perfilestate: heads the list of nfs4_stateid (either open or lock) &n;*         and is used to ensure no dangling nfs4_stateid references when we &n;*         release a stateowner.&n;*/
DECL|struct|nfs4_stateowner
r_struct
id|nfs4_stateowner
(brace
DECL|member|so_idhash
r_struct
id|list_head
id|so_idhash
suffix:semicolon
multiline_comment|/* hash by so_id */
DECL|member|so_strhash
r_struct
id|list_head
id|so_strhash
suffix:semicolon
multiline_comment|/* hash by op_name */
DECL|member|so_perclient
r_struct
id|list_head
id|so_perclient
suffix:semicolon
multiline_comment|/* nfs4_client-&gt;cl_perclient */
DECL|member|so_perfilestate
r_struct
id|list_head
id|so_perfilestate
suffix:semicolon
multiline_comment|/* list: nfs4_stateid */
DECL|member|so_is_open_owner
r_int
id|so_is_open_owner
suffix:semicolon
multiline_comment|/* 1=openowner,0=lockowner */
DECL|member|so_id
id|u32
id|so_id
suffix:semicolon
DECL|member|so_client
r_struct
id|nfs4_client
op_star
id|so_client
suffix:semicolon
DECL|member|so_seqid
id|u32
id|so_seqid
suffix:semicolon
DECL|member|so_owner
r_struct
id|xdr_netobj
id|so_owner
suffix:semicolon
multiline_comment|/* open owner name */
DECL|member|so_confirmed
r_int
id|so_confirmed
suffix:semicolon
multiline_comment|/* successful OPEN_CONFIRM? */
DECL|member|so_replay
r_struct
id|nfs4_replay
id|so_replay
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n;*  nfs4_file: a file opened by some number of (open) nfs4_stateowners.&n;*    o fi_perfile list is used to search for conflicting &n;*      share_acces, share_deny on the file.&n;*/
DECL|struct|nfs4_file
r_struct
id|nfs4_file
(brace
DECL|member|fi_hash
r_struct
id|list_head
id|fi_hash
suffix:semicolon
multiline_comment|/* hash by &quot;struct inode *&quot; */
DECL|member|fi_perfile
r_struct
id|list_head
id|fi_perfile
suffix:semicolon
multiline_comment|/* list: nfs4_stateid */
DECL|member|fi_inode
r_struct
id|inode
op_star
id|fi_inode
suffix:semicolon
DECL|member|fi_id
id|u32
id|fi_id
suffix:semicolon
multiline_comment|/* used with stateowner-&gt;so_id &n;&t;&t;&t;&t;&t;     * for stateid_hashtbl hash */
)brace
suffix:semicolon
multiline_comment|/*&n;* nfs4_stateid can either be an open stateid or (eventually) a lock stateid&n;*&n;* (open)nfs4_stateid: one per (open)nfs4_stateowner, nfs4_file&n;*&n;* &t;st_hash: stateid_hashtbl[] entry or lockstateid_hashtbl entry&n;* &t;st_perfile: file_hashtbl[] entry.&n;* &t;st_perfile_state: nfs4_stateowner-&gt;so_perfilestate&n;* &t;st_share_access: used only for open stateid&n;* &t;st_share_deny: used only for open stateid&n;*/
DECL|struct|nfs4_stateid
r_struct
id|nfs4_stateid
(brace
DECL|member|st_hash
r_struct
id|list_head
id|st_hash
suffix:semicolon
DECL|member|st_perfile
r_struct
id|list_head
id|st_perfile
suffix:semicolon
DECL|member|st_perfilestate
r_struct
id|list_head
id|st_perfilestate
suffix:semicolon
DECL|member|st_stateowner
r_struct
id|nfs4_stateowner
op_star
id|st_stateowner
suffix:semicolon
DECL|member|st_file
r_struct
id|nfs4_file
op_star
id|st_file
suffix:semicolon
DECL|member|st_stateid
id|stateid_t
id|st_stateid
suffix:semicolon
DECL|member|st_vfs_file
r_struct
id|file
id|st_vfs_file
suffix:semicolon
DECL|member|st_vfs_set
r_int
id|st_vfs_set
suffix:semicolon
DECL|member|st_share_access
r_int
r_int
id|st_share_access
suffix:semicolon
DECL|member|st_share_deny
r_int
r_int
id|st_share_deny
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* flags for preprocess_seqid_op() */
DECL|macro|CHECK_FH
mdefine_line|#define CHECK_FH                0x00000001
DECL|macro|CONFIRM
mdefine_line|#define CONFIRM                 0x00000002
DECL|macro|OPEN_STATE
mdefine_line|#define OPEN_STATE              0x00000004
DECL|macro|LOCK_STATE
mdefine_line|#define LOCK_STATE              0x00000008
DECL|macro|RDWR_STATE
mdefine_line|#define RDWR_STATE              0x00000010
DECL|macro|seqid_mutating_err
mdefine_line|#define seqid_mutating_err(err)                       &bslash;&n;&t;(((err) != nfserr_stale_clientid) &amp;&amp;    &bslash;&n;&t;((err) != nfserr_bad_seqid) &amp;&amp;          &bslash;&n;&t;((err) != nfserr_stale_stateid) &amp;&amp;      &bslash;&n;&t;((err) != nfserr_bad_stateid))
r_extern
id|time_t
id|nfs4_laundromat
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|nfsd4_renew
c_func
(paren
id|clientid_t
op_star
id|clid
)paren
suffix:semicolon
r_extern
r_int
id|nfs4_preprocess_stateid_op
c_func
(paren
r_struct
id|svc_fh
op_star
id|current_fh
comma
id|stateid_t
op_star
id|stateid
comma
r_int
id|flags
comma
r_struct
id|nfs4_stateid
op_star
op_star
id|stpp
)paren
suffix:semicolon
r_extern
r_int
id|nfs4_share_conflict
c_func
(paren
r_struct
id|svc_fh
op_star
id|current_fh
comma
r_int
r_int
id|deny_type
)paren
suffix:semicolon
r_extern
r_void
id|nfs4_lock_state
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|nfs4_unlock_state
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif   /* NFSD4_STATE_H */
eof
