multiline_comment|/*&n;*  linux/fs/nfsd/nfs4state.c&n;*&n;*  Copyright (c) 2001 The Regents of the University of Michigan.&n;*  All rights reserved.&n;*&n;*  Kendrick Smith &lt;kmsmith@umich.edu&gt;&n;*  Andy Adamson &lt;kandros@umich.edu&gt;&n;*&n;*  Redistribution and use in source and binary forms, with or without&n;*  modification, are permitted provided that the following conditions&n;*  are met:&n;*&n;*  1. Redistributions of source code must retain the above copyright&n;*     notice, this list of conditions and the following disclaimer.&n;*  2. Redistributions in binary form must reproduce the above copyright&n;*     notice, this list of conditions and the following disclaimer in the&n;*     documentation and/or other materials provided with the distribution.&n;*  3. Neither the name of the University nor the names of its&n;*     contributors may be used to endorse or promote products derived&n;*     from this software without specific prior written permission.&n;*&n;*  THIS SOFTWARE IS PROVIDED ``AS IS&squot;&squot; AND ANY EXPRESS OR IMPLIED&n;*  WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF&n;*  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE&n;*  DISCLAIMED. IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE&n;*  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR&n;*  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF&n;*  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR&n;*  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF&n;*  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING&n;*  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS&n;*  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n;*&n;*/
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
mdefine_line|#define NFSDDBG_FACILITY                NFSDDBG_PROC
multiline_comment|/* Globals */
DECL|variable|boot_time
id|time_t
id|boot_time
suffix:semicolon
DECL|variable|current_clientid
r_static
id|u32
id|current_clientid
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* Locking:&n; *&n; * client_sema: &n; * &t;protects clientid_hashtbl[], clientstr_hashtbl[],&n; * &t;unconfstr_hashtbl[], uncofid_hashtbl[].&n; */
DECL|variable|client_sema
r_static
r_struct
id|semaphore
id|client_sema
suffix:semicolon
r_static
r_inline
id|u32
DECL|function|opaque_hashval
id|opaque_hashval
c_func
(paren
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
r_char
op_star
id|cptr
op_assign
(paren
r_int
r_char
op_star
)paren
id|ptr
suffix:semicolon
id|u32
id|x
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|nbytes
op_decrement
)paren
(brace
id|x
op_mul_assign
l_int|37
suffix:semicolon
id|x
op_add_assign
op_star
id|cptr
op_increment
suffix:semicolon
)brace
r_return
id|x
suffix:semicolon
)brace
multiline_comment|/* Hash tables for nfs4_clientid state */
DECL|macro|CLIENT_HASH_BITS
mdefine_line|#define CLIENT_HASH_BITS                 4
DECL|macro|CLIENT_HASH_SIZE
mdefine_line|#define CLIENT_HASH_SIZE                (1 &lt;&lt; CLIENT_HASH_BITS)
DECL|macro|CLIENT_HASH_MASK
mdefine_line|#define CLIENT_HASH_MASK                (CLIENT_HASH_SIZE - 1)
DECL|macro|clientid_hashval
mdefine_line|#define clientid_hashval(id) &bslash;&n;&t;((id) &amp; CLIENT_HASH_MASK)
DECL|macro|clientstr_hashval
mdefine_line|#define clientstr_hashval(name, namelen) &bslash;&n;&t;(opaque_hashval((name), (namelen)) &amp; CLIENT_HASH_MASK)
multiline_comment|/* conf_id_hashtbl[], and conf_str_hashtbl[] hold confirmed&n; * setclientid_confirmed info. &n; *&n; * unconf_str_hastbl[] and unconf_id_hashtbl[] hold unconfirmed &n; * setclientid info.&n; */
DECL|variable|conf_id_hashtbl
r_static
r_struct
id|list_head
id|conf_id_hashtbl
(braket
id|CLIENT_HASH_SIZE
)braket
suffix:semicolon
DECL|variable|conf_str_hashtbl
r_static
r_struct
id|list_head
id|conf_str_hashtbl
(braket
id|CLIENT_HASH_SIZE
)braket
suffix:semicolon
DECL|variable|unconf_str_hashtbl
r_static
r_struct
id|list_head
id|unconf_str_hashtbl
(braket
id|CLIENT_HASH_SIZE
)braket
suffix:semicolon
DECL|variable|unconf_id_hashtbl
r_static
r_struct
id|list_head
id|unconf_id_hashtbl
(braket
id|CLIENT_HASH_SIZE
)braket
suffix:semicolon
multiline_comment|/* SETCLIENTID and SETCLIENTID_CONFIRM Helper functions */
r_static
r_int
DECL|function|STALE_CLIENTID
id|STALE_CLIENTID
c_func
(paren
id|clientid_t
op_star
id|clid
)paren
(brace
r_if
c_cond
(paren
id|clid-&gt;cl_boot
op_eq
id|boot_time
)paren
r_return
l_int|0
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;NFSD stale clientid (%08x/%08x)&bslash;n&quot;
comma
id|clid-&gt;cl_boot
comma
id|clid-&gt;cl_id
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/* &n; * XXX Should we use a slab cache ?&n; * This type of memory management is somewhat inefficient, but we use it&n; * anyway since SETCLIENTID is not a common operation.&n; */
r_static
r_inline
r_struct
id|nfs4_client
op_star
DECL|function|alloc_client
id|alloc_client
c_func
(paren
r_struct
id|xdr_netobj
id|name
)paren
(brace
r_struct
id|nfs4_client
op_star
id|clp
suffix:semicolon
r_if
c_cond
(paren
(paren
id|clp
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|nfs4_client
)paren
comma
id|GFP_KERNEL
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
id|memset
c_func
(paren
id|clp
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|clp
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|clp-&gt;cl_name.data
op_assign
id|kmalloc
c_func
(paren
id|name.len
comma
id|GFP_KERNEL
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
id|memcpy
c_func
(paren
id|clp-&gt;cl_name.data
comma
id|name.data
comma
id|name.len
)paren
suffix:semicolon
id|clp-&gt;cl_name.len
op_assign
id|name.len
suffix:semicolon
)brace
r_else
(brace
id|kfree
c_func
(paren
id|clp
)paren
suffix:semicolon
id|clp
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
r_return
id|clp
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|free_client
id|free_client
c_func
(paren
r_struct
id|nfs4_client
op_star
id|clp
)paren
(brace
id|kfree
c_func
(paren
id|clp-&gt;cl_name.data
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|clp
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|expire_client
id|expire_client
c_func
(paren
r_struct
id|nfs4_client
op_star
id|clp
)paren
(brace
id|dprintk
c_func
(paren
l_string|&quot;NFSD: expire_client&bslash;n&quot;
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|clp-&gt;cl_idhash
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|clp-&gt;cl_strhash
)paren
suffix:semicolon
id|free_client
c_func
(paren
id|clp
)paren
suffix:semicolon
)brace
r_static
r_struct
id|nfs4_client
op_star
DECL|function|create_client
id|create_client
c_func
(paren
r_struct
id|xdr_netobj
id|name
)paren
(brace
r_struct
id|nfs4_client
op_star
id|clp
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|clp
op_assign
id|alloc_client
c_func
(paren
id|name
)paren
)paren
)paren
(brace
r_goto
id|out
suffix:semicolon
)brace
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|clp-&gt;cl_idhash
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|clp-&gt;cl_strhash
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|clp
suffix:semicolon
)brace
r_static
r_void
DECL|function|copy_verf
id|copy_verf
c_func
(paren
r_struct
id|nfs4_client
op_star
id|target
comma
id|nfs4_verifier
id|source
)paren
(brace
id|memcpy
c_func
(paren
op_amp
id|target-&gt;cl_verifier
comma
id|source
comma
r_sizeof
(paren
id|nfs4_verifier
)paren
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|copy_clid
id|copy_clid
c_func
(paren
r_struct
id|nfs4_client
op_star
id|target
comma
r_struct
id|nfs4_client
op_star
id|source
)paren
(brace
id|target-&gt;cl_clientid.cl_boot
op_assign
id|source-&gt;cl_clientid.cl_boot
suffix:semicolon
id|target-&gt;cl_clientid.cl_id
op_assign
id|source-&gt;cl_clientid.cl_id
suffix:semicolon
)brace
r_static
r_void
DECL|function|copy_cred
id|copy_cred
c_func
(paren
r_struct
id|svc_cred
op_star
id|target
comma
r_struct
id|svc_cred
op_star
id|source
)paren
(brace
r_int
id|i
suffix:semicolon
id|target-&gt;cr_uid
op_assign
id|source-&gt;cr_uid
suffix:semicolon
id|target-&gt;cr_gid
op_assign
id|source-&gt;cr_gid
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|NGROUPS
suffix:semicolon
id|i
op_increment
)paren
(brace
id|target-&gt;cr_groups
(braket
id|i
)braket
op_assign
id|source-&gt;cr_groups
(braket
id|i
)braket
suffix:semicolon
)brace
)brace
r_static
r_int
DECL|function|cmp_name
id|cmp_name
c_func
(paren
r_struct
id|xdr_netobj
op_star
id|n1
comma
r_struct
id|xdr_netobj
op_star
id|n2
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|n1
op_logical_or
op_logical_neg
id|n2
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
r_return
(paren
id|n1-&gt;len
op_eq
id|n2-&gt;len
)paren
op_logical_and
op_logical_neg
id|memcmp
c_func
(paren
id|n1-&gt;data
comma
id|n2-&gt;data
comma
id|n2-&gt;len
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|cmp_verf
id|cmp_verf
c_func
(paren
id|nfs4_verifier
id|v1
comma
id|nfs4_verifier
id|v2
)paren
(brace
r_return
op_logical_neg
id|memcmp
c_func
(paren
id|v1
comma
id|v2
comma
r_sizeof
(paren
id|nfs4_verifier
)paren
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|cmp_clid
id|cmp_clid
c_func
(paren
id|clientid_t
op_star
id|cl1
comma
id|clientid_t
op_star
id|cl2
)paren
(brace
r_return
(paren
id|cl1-&gt;cl_boot
op_eq
id|cl2-&gt;cl_boot
)paren
op_logical_and
(paren
id|cl1-&gt;cl_id
op_eq
id|cl2-&gt;cl_id
)paren
suffix:semicolon
)brace
multiline_comment|/* XXX what about NGROUP */
r_static
r_int
DECL|function|cmp_creds
(def_block
id|cmp_creds
c_func
(paren
r_struct
id|svc_cred
op_star
id|cr1
comma
r_struct
id|svc_cred
op_star
id|cr2
)paren
(brace
r_return
(paren
id|cr1-&gt;cr_uid
op_eq
id|cr2-&gt;cr_uid
)paren
op_logical_and
(paren
id|cr1-&gt;cr_gid
op_eq
id|cr2-&gt;cr_gid
)paren
suffix:semicolon
)brace
)def_block
r_static
r_void
DECL|function|gen_clid
id|gen_clid
c_func
(paren
r_struct
id|nfs4_client
op_star
id|clp
)paren
(brace
id|clp-&gt;cl_clientid.cl_boot
op_assign
id|boot_time
suffix:semicolon
id|clp-&gt;cl_clientid.cl_id
op_assign
id|current_clientid
op_increment
suffix:semicolon
)brace
r_static
r_void
DECL|function|gen_confirm
id|gen_confirm
c_func
(paren
r_struct
id|nfs4_client
op_star
id|clp
)paren
(brace
r_struct
id|timespec
id|tv
suffix:semicolon
id|u32
op_star
id|p
suffix:semicolon
id|tv
op_assign
id|CURRENT_TIME
suffix:semicolon
id|p
op_assign
(paren
id|u32
op_star
)paren
id|clp-&gt;cl_confirm
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|tv.tv_sec
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|tv.tv_nsec
suffix:semicolon
)brace
r_static
r_int
DECL|function|check_name
id|check_name
c_func
(paren
r_struct
id|xdr_netobj
id|name
)paren
(brace
r_if
c_cond
(paren
id|name.len
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|name.len
OG
id|NFS4_OPAQUE_LIMIT
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;NFSD: check_name: name too long(%d)!&bslash;n&quot;
comma
id|name.len
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
r_void
DECL|function|add_to_unconfirmed
id|add_to_unconfirmed
c_func
(paren
r_struct
id|nfs4_client
op_star
id|clp
comma
r_int
r_int
id|strhashval
)paren
(brace
r_int
r_int
id|idhashval
suffix:semicolon
id|list_add
c_func
(paren
op_amp
id|clp-&gt;cl_strhash
comma
op_amp
id|unconf_str_hashtbl
(braket
id|strhashval
)braket
)paren
suffix:semicolon
id|idhashval
op_assign
id|clientid_hashval
c_func
(paren
id|clp-&gt;cl_clientid.cl_id
)paren
suffix:semicolon
id|list_add
c_func
(paren
op_amp
id|clp-&gt;cl_idhash
comma
op_amp
id|unconf_id_hashtbl
(braket
id|idhashval
)braket
)paren
suffix:semicolon
)brace
r_void
DECL|function|move_to_confirmed
id|move_to_confirmed
c_func
(paren
r_struct
id|nfs4_client
op_star
id|clp
comma
r_int
r_int
id|idhashval
)paren
(brace
r_int
r_int
id|strhashval
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;ANDROS: move_to_confirm nfs4_client %p&bslash;n&quot;
comma
id|clp
)paren
suffix:semicolon
id|list_del_init
c_func
(paren
op_amp
id|clp-&gt;cl_strhash
)paren
suffix:semicolon
id|list_del_init
c_func
(paren
op_amp
id|clp-&gt;cl_idhash
)paren
suffix:semicolon
id|list_add
c_func
(paren
op_amp
id|clp-&gt;cl_idhash
comma
op_amp
id|conf_id_hashtbl
(braket
id|idhashval
)braket
)paren
suffix:semicolon
id|strhashval
op_assign
id|clientstr_hashval
c_func
(paren
id|clp-&gt;cl_name.data
comma
id|clp-&gt;cl_name.len
)paren
suffix:semicolon
id|list_add
c_func
(paren
op_amp
id|clp-&gt;cl_strhash
comma
op_amp
id|conf_str_hashtbl
(braket
id|strhashval
)braket
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * RFC 3010 has a complex implmentation description of processing a &n; * SETCLIENTID request consisting of 5 bullets, labeled as &n; * CASE0 - CASE4 below.&n; *&n; * NOTES:&n; * &t;callback information will be processed in a future patch&n; *&n; *&t;an unconfirmed record is added when:&n; *      NORMAL (part of CASE 4): there is no confirmed nor unconfirmed record.&n; *&t;CASE 1: confirmed record found with matching name, principal,&n; *&t;&t;verifier, and clientid.&n; *&t;CASE 2: confirmed record found with matching name, principal,&n; *&t;&t;and there is no unconfirmed record with matching&n; *&t;&t;name and principal&n; *&n; *      an unconfirmed record is replaced when:&n; *&t;CASE 3: confirmed record found with matching name, principal,&n; *&t;&t;and an unconfirmed record is found with matching &n; *&t;&t;name, principal, and with clientid and&n; *&t;&t;confirm that does not match the confirmed record.&n; *&t;CASE 4: there is no confirmed record with matching name and &n; *&t;&t;principal. there is an unconfirmed record with &n; *&t;&t;matching name, principal.&n; *&n; *&t;an unconfirmed record is deleted when:&n; *&t;CASE 1: an unconfirmed record that matches input name, verifier,&n; *&t;&t;and confirmed clientid.&n; *&t;CASE 4: any unconfirmed records with matching name and principal&n; *&t;&t;that exist after an unconfirmed record has been replaced&n; *&t;&t;as described above.&n; *&n; */
r_int
DECL|function|nfsd4_setclientid
id|nfsd4_setclientid
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
r_struct
id|nfsd4_setclientid
op_star
id|setclid
)paren
(brace
id|u32
id|ip_addr
op_assign
id|rqstp-&gt;rq_addr.sin_addr.s_addr
suffix:semicolon
r_struct
id|xdr_netobj
id|clname
op_assign
(brace
dot
id|len
op_assign
id|setclid-&gt;se_namelen
comma
dot
id|data
op_assign
id|setclid-&gt;se_name
comma
)brace
suffix:semicolon
r_char
op_star
id|clverifier
op_assign
id|setclid-&gt;se_verf
suffix:semicolon
r_int
r_int
id|strhashval
suffix:semicolon
r_struct
id|nfs4_client
op_star
id|conf
comma
op_star
id|unconf
comma
op_star
r_new
comma
op_star
id|clp
suffix:semicolon
r_int
id|status
suffix:semicolon
r_struct
id|list_head
op_star
id|pos
comma
op_star
id|next
suffix:semicolon
id|status
op_assign
id|nfserr_inval
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|check_name
c_func
(paren
id|clname
)paren
)paren
r_goto
id|out
suffix:semicolon
multiline_comment|/* &n;&t; * XXX The Duplicate Request Cache (DRC) has been checked (??)&n;&t; * We get here on a DRC miss.&n;&t; */
id|strhashval
op_assign
id|clientstr_hashval
c_func
(paren
id|clname.data
comma
id|clname.len
)paren
suffix:semicolon
id|conf
op_assign
l_int|NULL
suffix:semicolon
id|down
c_func
(paren
op_amp
id|client_sema
)paren
suffix:semicolon
id|list_for_each_safe
c_func
(paren
id|pos
comma
id|next
comma
op_amp
id|conf_str_hashtbl
(braket
id|strhashval
)braket
)paren
(brace
id|clp
op_assign
id|list_entry
c_func
(paren
id|pos
comma
r_struct
id|nfs4_client
comma
id|cl_strhash
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cmp_name
c_func
(paren
op_amp
id|clp-&gt;cl_name
comma
op_amp
id|clname
)paren
)paren
r_continue
suffix:semicolon
multiline_comment|/* &n;&t;&t; * CASE 0:&n;&t;&t; * clname match, confirmed, different principal&n;&t;&t; * or different ip_address&n;&t;&t; */
id|status
op_assign
id|nfserr_clid_inuse
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cmp_creds
c_func
(paren
op_amp
id|clp-&gt;cl_cred
comma
op_amp
id|rqstp-&gt;rq_cred
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;NFSD: setclientid: string in use by client&quot;
l_string|&quot;(clientid %08x/%08x)&bslash;n&quot;
comma
id|clp-&gt;cl_clientid.cl_boot
comma
id|clp-&gt;cl_clientid.cl_id
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|clp-&gt;cl_addr
op_ne
id|ip_addr
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;NFSD: setclientid: string in use by client&quot;
l_string|&quot;(clientid %08x/%08x)&bslash;n&quot;
comma
id|clp-&gt;cl_clientid.cl_boot
comma
id|clp-&gt;cl_clientid.cl_id
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/* &n;&t; &t; * cl_name match from a previous SETCLIENTID operation&n;&t; &t; * XXX check for additional matches?&n;&t;&t; */
id|conf
op_assign
id|clp
suffix:semicolon
r_break
suffix:semicolon
)brace
id|unconf
op_assign
l_int|NULL
suffix:semicolon
id|list_for_each_safe
c_func
(paren
id|pos
comma
id|next
comma
op_amp
id|unconf_str_hashtbl
(braket
id|strhashval
)braket
)paren
(brace
id|clp
op_assign
id|list_entry
c_func
(paren
id|pos
comma
r_struct
id|nfs4_client
comma
id|cl_strhash
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cmp_name
c_func
(paren
op_amp
id|clp-&gt;cl_name
comma
op_amp
id|clname
)paren
)paren
r_continue
suffix:semicolon
multiline_comment|/* cl_name match from a previous SETCLIENTID operation */
id|unconf
op_assign
id|clp
suffix:semicolon
r_break
suffix:semicolon
)brace
id|status
op_assign
id|nfserr_resource
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|conf
)paren
(brace
multiline_comment|/* &n;&t;&t; * CASE 4:&n;&t;&t; * placed first, because it is the normal case.&n;&t;&t; */
r_if
c_cond
(paren
id|unconf
)paren
id|expire_client
c_func
(paren
id|unconf
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
r_new
op_assign
id|create_client
c_func
(paren
id|clname
)paren
)paren
)paren
r_goto
id|out
suffix:semicolon
id|copy_verf
c_func
(paren
r_new
comma
id|clverifier
)paren
suffix:semicolon
r_new
op_member_access_from_pointer
id|cl_addr
op_assign
id|ip_addr
suffix:semicolon
id|copy_cred
c_func
(paren
op_amp
r_new
op_member_access_from_pointer
id|cl_cred
comma
op_amp
id|rqstp-&gt;rq_cred
)paren
suffix:semicolon
id|gen_clid
c_func
(paren
r_new
)paren
suffix:semicolon
id|gen_confirm
c_func
(paren
r_new
)paren
suffix:semicolon
id|add_to_unconfirmed
c_func
(paren
r_new
comma
id|strhashval
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|cmp_verf
c_func
(paren
id|conf-&gt;cl_verifier
comma
id|clverifier
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t; * CASE 1:&n;&t;&t; * cl_name match, confirmed, principal match&n;&t;&t; * verifier match: probable callback update&n;&t;&t; *&n;&t;&t; * remove any unconfirmed nfs4_client with &n;&t;&t; * matching cl_name, cl_verifier, and cl_clientid&n;&t;&t; *&n;&t;&t; * create and insert an unconfirmed nfs4_client with same &n;&t;&t; * cl_name, cl_verifier, and cl_clientid as existing &n;&t;&t; * nfs4_client,  but with the new callback info and a &n;&t;&t; * new cl_confirm&n;&t;&t; */
r_if
c_cond
(paren
(paren
id|unconf
)paren
op_logical_and
id|cmp_verf
c_func
(paren
id|unconf-&gt;cl_verifier
comma
id|conf-&gt;cl_verifier
)paren
op_logical_and
id|cmp_clid
c_func
(paren
op_amp
id|unconf-&gt;cl_clientid
comma
op_amp
id|conf-&gt;cl_clientid
)paren
)paren
(brace
id|expire_client
c_func
(paren
id|unconf
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
r_new
op_assign
id|create_client
c_func
(paren
id|clname
)paren
)paren
)paren
r_goto
id|out
suffix:semicolon
id|copy_verf
c_func
(paren
r_new
comma
id|conf-&gt;cl_verifier
)paren
suffix:semicolon
r_new
op_member_access_from_pointer
id|cl_addr
op_assign
id|ip_addr
suffix:semicolon
id|copy_cred
c_func
(paren
op_amp
r_new
op_member_access_from_pointer
id|cl_cred
comma
op_amp
id|rqstp-&gt;rq_cred
)paren
suffix:semicolon
id|copy_clid
c_func
(paren
r_new
comma
id|conf
)paren
suffix:semicolon
id|gen_confirm
c_func
(paren
r_new
)paren
suffix:semicolon
id|add_to_unconfirmed
c_func
(paren
r_new
comma
id|strhashval
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|unconf
)paren
(brace
multiline_comment|/*&n;&t;&t; * CASE 2:&n;&t;&t; * clname match, confirmed, principal match&n;&t;&t; * verfier does not match&n;&t;&t; * no unconfirmed. create a new unconfirmed nfs4_client&n;&t;&t; * using input clverifier, clname, and callback info&n;&t;&t; * and generate a new cl_clientid and cl_confirm.&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
(paren
r_new
op_assign
id|create_client
c_func
(paren
id|clname
)paren
)paren
)paren
r_goto
id|out
suffix:semicolon
id|copy_verf
c_func
(paren
r_new
comma
id|clverifier
)paren
suffix:semicolon
r_new
op_member_access_from_pointer
id|cl_addr
op_assign
id|ip_addr
suffix:semicolon
id|copy_cred
c_func
(paren
op_amp
r_new
op_member_access_from_pointer
id|cl_cred
comma
op_amp
id|rqstp-&gt;rq_cred
)paren
suffix:semicolon
id|gen_clid
c_func
(paren
r_new
)paren
suffix:semicolon
id|gen_confirm
c_func
(paren
r_new
)paren
suffix:semicolon
id|add_to_unconfirmed
c_func
(paren
r_new
comma
id|strhashval
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|cmp_clid
c_func
(paren
op_amp
id|conf-&gt;cl_clientid
comma
op_amp
id|unconf-&gt;cl_clientid
)paren
op_logical_and
op_logical_neg
id|cmp_verf
c_func
(paren
id|conf-&gt;cl_confirm
comma
id|unconf-&gt;cl_confirm
)paren
)paren
(brace
multiline_comment|/*&t;&n;&t;&t; * CASE3:&n;&t;&t; * confirmed found (name, principal match)&n;&t;&t; * confirmed verifier does not match input clverifier&n;&t;&t; *&n;&t;&t; * unconfirmed found (name match)&n;&t;&t; * confirmed-&gt;cl_clientid != unconfirmed-&gt;cl_clientid and&n;&t;&t; * confirmed-&gt;cl_confirm != unconfirmed-&gt;cl_confirm&n;&t;&t; *&n;&t;&t; * remove unconfirmed.&n;&t;&t; *&n;&t;&t; * create an unconfirmed nfs4_client &n;&t;&t; * with same cl_name as existing confirmed nfs4_client, &n;&t;&t; * but with new callback info, new cl_clientid,&n;&t;&t; * new cl_verifier and a new cl_confirm&n;&t;&t; */
id|expire_client
c_func
(paren
id|unconf
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
r_new
op_assign
id|create_client
c_func
(paren
id|clname
)paren
)paren
)paren
r_goto
id|out
suffix:semicolon
id|copy_verf
c_func
(paren
r_new
comma
id|clverifier
)paren
suffix:semicolon
r_new
op_member_access_from_pointer
id|cl_addr
op_assign
id|ip_addr
suffix:semicolon
id|copy_cred
c_func
(paren
op_amp
r_new
op_member_access_from_pointer
id|cl_cred
comma
op_amp
id|rqstp-&gt;rq_cred
)paren
suffix:semicolon
id|gen_clid
c_func
(paren
r_new
)paren
suffix:semicolon
id|gen_confirm
c_func
(paren
r_new
)paren
suffix:semicolon
id|add_to_unconfirmed
c_func
(paren
r_new
comma
id|strhashval
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* No cases hit !!! */
id|status
op_assign
id|nfserr_inval
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|setclid-&gt;se_clientid.cl_boot
op_assign
r_new
op_member_access_from_pointer
id|cl_clientid.cl_boot
suffix:semicolon
id|setclid-&gt;se_clientid.cl_id
op_assign
r_new
op_member_access_from_pointer
id|cl_clientid.cl_id
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|setclid-&gt;se_confirm
comma
r_new
op_member_access_from_pointer
id|cl_confirm
comma
r_sizeof
(paren
id|nfs4_verifier
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;NFSD: this client will not receive delegations&bslash;n&quot;
)paren
suffix:semicolon
id|status
op_assign
id|nfs_ok
suffix:semicolon
id|out
suffix:colon
id|up
c_func
(paren
op_amp
id|client_sema
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
multiline_comment|/*&n; * RFC 3010 has a complex implmentation description of processing a &n; * SETCLIENTID_CONFIRM request consisting of 4 bullets describing&n; * processing on a DRC miss, labeled as CASE1 - CASE4 below.&n; *&n; * NOTE: callback information will be processed here in a future patch&n; */
r_int
DECL|function|nfsd4_setclientid_confirm
id|nfsd4_setclientid_confirm
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
r_struct
id|nfsd4_setclientid_confirm
op_star
id|setclientid_confirm
)paren
(brace
id|u32
id|ip_addr
op_assign
id|rqstp-&gt;rq_addr.sin_addr.s_addr
suffix:semicolon
r_int
r_int
id|idhashval
suffix:semicolon
r_struct
id|nfs4_client
op_star
id|clp
comma
op_star
id|conf
op_assign
l_int|NULL
comma
op_star
id|unconf
op_assign
l_int|NULL
suffix:semicolon
r_char
op_star
id|confirm
op_assign
id|setclientid_confirm-&gt;sc_confirm
suffix:semicolon
id|clientid_t
op_star
id|clid
op_assign
op_amp
id|setclientid_confirm-&gt;sc_clientid
suffix:semicolon
r_struct
id|list_head
op_star
id|pos
comma
op_star
id|next
suffix:semicolon
r_int
id|status
suffix:semicolon
id|status
op_assign
id|nfserr_stale_clientid
suffix:semicolon
r_if
c_cond
(paren
id|STALE_CLIENTID
c_func
(paren
id|clid
)paren
)paren
r_goto
id|out
suffix:semicolon
multiline_comment|/* &n;&t; * XXX The Duplicate Request Cache (DRC) has been checked (??)&n;&t; * We get here on a DRC miss.&n;&t; */
id|idhashval
op_assign
id|clientid_hashval
c_func
(paren
id|clid-&gt;cl_id
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|client_sema
)paren
suffix:semicolon
id|list_for_each_safe
c_func
(paren
id|pos
comma
id|next
comma
op_amp
id|conf_id_hashtbl
(braket
id|idhashval
)braket
)paren
(brace
id|clp
op_assign
id|list_entry
c_func
(paren
id|pos
comma
r_struct
id|nfs4_client
comma
id|cl_idhash
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cmp_clid
c_func
(paren
op_amp
id|clp-&gt;cl_clientid
comma
id|clid
)paren
)paren
r_continue
suffix:semicolon
id|status
op_assign
id|nfserr_inval
suffix:semicolon
multiline_comment|/* &n;&t;&t; * Found a record for this clientid. If the IP addresses&n;&t;&t; * don&squot;t match, return ERR_INVAL just as if the record had&n;&t;&t; * not been found.&n;&t;&t; */
r_if
c_cond
(paren
id|clp-&gt;cl_addr
op_ne
id|ip_addr
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;NFSD: setclientid: string in use by client&quot;
l_string|&quot;(clientid %08x/%08x)&bslash;n&quot;
comma
id|clp-&gt;cl_clientid.cl_boot
comma
id|clp-&gt;cl_clientid.cl_id
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|conf
op_assign
id|clp
suffix:semicolon
r_break
suffix:semicolon
)brace
id|list_for_each_safe
c_func
(paren
id|pos
comma
id|next
comma
op_amp
id|unconf_id_hashtbl
(braket
id|idhashval
)braket
)paren
(brace
id|clp
op_assign
id|list_entry
c_func
(paren
id|pos
comma
r_struct
id|nfs4_client
comma
id|cl_idhash
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cmp_clid
c_func
(paren
op_amp
id|clp-&gt;cl_clientid
comma
id|clid
)paren
)paren
r_continue
suffix:semicolon
id|status
op_assign
id|nfserr_inval
suffix:semicolon
r_if
c_cond
(paren
id|clp-&gt;cl_addr
op_ne
id|ip_addr
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;NFSD: setclientid: string in use by client&quot;
l_string|&quot;(clientid %08x/%08x)&bslash;n&quot;
comma
id|clp-&gt;cl_clientid.cl_boot
comma
id|clp-&gt;cl_clientid.cl_id
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|unconf
op_assign
id|clp
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* CASE 1: &n;&t;* unconf record that matches input clientid and input confirm.&n;&t;* conf record that matches input clientid.&n;&t;* conf  and unconf records match names, verifiers &n;&t;*/
r_if
c_cond
(paren
(paren
id|conf
op_logical_and
id|unconf
)paren
op_logical_and
(paren
id|cmp_verf
c_func
(paren
id|unconf-&gt;cl_confirm
comma
id|confirm
)paren
)paren
op_logical_and
(paren
id|cmp_verf
c_func
(paren
id|conf-&gt;cl_verifier
comma
id|unconf-&gt;cl_verifier
)paren
)paren
op_logical_and
(paren
id|cmp_name
c_func
(paren
op_amp
id|conf-&gt;cl_name
comma
op_amp
id|unconf-&gt;cl_name
)paren
)paren
op_logical_and
(paren
op_logical_neg
id|cmp_verf
c_func
(paren
id|conf-&gt;cl_confirm
comma
id|unconf-&gt;cl_confirm
)paren
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|cmp_creds
c_func
(paren
op_amp
id|conf-&gt;cl_cred
comma
op_amp
id|unconf-&gt;cl_cred
)paren
)paren
id|status
op_assign
id|nfserr_clid_inuse
suffix:semicolon
r_else
(brace
id|expire_client
c_func
(paren
id|conf
)paren
suffix:semicolon
id|move_to_confirmed
c_func
(paren
id|unconf
comma
id|idhashval
)paren
suffix:semicolon
id|status
op_assign
id|nfs_ok
suffix:semicolon
)brace
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/* CASE 2:&n;&t; * conf record that matches input clientid.&n;&t; * if unconf record that matches input clientid, then unconf-&gt;cl_name&n;&t; * or unconf-&gt;cl_verifier don&squot;t match the conf record.&n;&t; */
r_if
c_cond
(paren
(paren
id|conf
op_logical_and
op_logical_neg
id|unconf
)paren
op_logical_or
(paren
(paren
id|conf
op_logical_and
id|unconf
)paren
op_logical_and
(paren
op_logical_neg
id|cmp_verf
c_func
(paren
id|conf-&gt;cl_verifier
comma
id|unconf-&gt;cl_verifier
)paren
op_logical_or
op_logical_neg
id|cmp_name
c_func
(paren
op_amp
id|conf-&gt;cl_name
comma
op_amp
id|unconf-&gt;cl_name
)paren
)paren
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|cmp_creds
c_func
(paren
op_amp
id|conf-&gt;cl_cred
comma
op_amp
id|rqstp-&gt;rq_cred
)paren
)paren
(brace
id|status
op_assign
id|nfserr_clid_inuse
suffix:semicolon
)brace
r_else
(brace
id|status
op_assign
id|nfs_ok
suffix:semicolon
)brace
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/* CASE 3:&n;&t; * conf record not found.&n;&t; * unconf record found. &n;&t; * unconf-&gt;cl_confirm matches input confirm&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|conf
op_logical_and
id|unconf
op_logical_and
id|cmp_verf
c_func
(paren
id|unconf-&gt;cl_confirm
comma
id|confirm
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|cmp_creds
c_func
(paren
op_amp
id|unconf-&gt;cl_cred
comma
op_amp
id|rqstp-&gt;rq_cred
)paren
)paren
(brace
id|status
op_assign
id|nfserr_clid_inuse
suffix:semicolon
)brace
r_else
(brace
id|status
op_assign
id|nfs_ok
suffix:semicolon
id|move_to_confirmed
c_func
(paren
id|unconf
comma
id|idhashval
)paren
suffix:semicolon
)brace
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/* CASE 4:&n;&t; * conf record not found, or if conf, then conf-&gt;cl_confirm does not&n;&t; * match input confirm.&n;&t; * unconf record not found, or if unconf, then unconf-&gt;cl_confirm &n;&t; * does not match input confirm.&n;&t; */
r_if
c_cond
(paren
(paren
op_logical_neg
id|conf
op_logical_or
(paren
id|conf
op_logical_and
op_logical_neg
id|cmp_verf
c_func
(paren
id|conf-&gt;cl_confirm
comma
id|confirm
)paren
)paren
)paren
op_logical_and
(paren
op_logical_neg
id|unconf
op_logical_or
(paren
id|unconf
op_logical_and
op_logical_neg
id|cmp_verf
c_func
(paren
id|unconf-&gt;cl_confirm
comma
id|confirm
)paren
)paren
)paren
)paren
(brace
id|status
op_assign
id|nfserr_stale_clientid
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/* check that we have hit one of the cases...*/
id|status
op_assign
id|nfserr_inval
suffix:semicolon
r_goto
id|out
suffix:semicolon
id|out
suffix:colon
multiline_comment|/* XXX if status == nfs_ok, probe callback path */
id|up
c_func
(paren
op_amp
id|client_sema
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
r_void
DECL|function|nfs4_state_init
id|nfs4_state_init
c_func
(paren
r_void
)paren
(brace
r_struct
id|timespec
id|tv
suffix:semicolon
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
id|i
OL
id|CLIENT_HASH_SIZE
suffix:semicolon
id|i
op_increment
)paren
(brace
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|conf_id_hashtbl
(braket
id|i
)braket
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|conf_str_hashtbl
(braket
id|i
)braket
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|unconf_str_hashtbl
(braket
id|i
)braket
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|unconf_id_hashtbl
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
id|init_MUTEX
c_func
(paren
op_amp
id|client_sema
)paren
suffix:semicolon
id|tv
op_assign
id|CURRENT_TIME
suffix:semicolon
id|boot_time
op_assign
id|tv.tv_sec
suffix:semicolon
)brace
r_static
r_void
DECL|function|__nfs4_state_shutdown
id|__nfs4_state_shutdown
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|nfs4_client
op_star
id|clp
op_assign
l_int|NULL
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|CLIENT_HASH_SIZE
suffix:semicolon
id|i
op_increment
)paren
(brace
r_while
c_loop
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|conf_id_hashtbl
(braket
id|i
)braket
)paren
)paren
(brace
id|clp
op_assign
id|list_entry
c_func
(paren
id|conf_id_hashtbl
(braket
id|i
)braket
dot
id|next
comma
r_struct
id|nfs4_client
comma
id|cl_idhash
)paren
suffix:semicolon
id|expire_client
c_func
(paren
id|clp
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|unconf_str_hashtbl
(braket
id|i
)braket
)paren
)paren
(brace
id|clp
op_assign
id|list_entry
c_func
(paren
id|unconf_str_hashtbl
(braket
id|i
)braket
dot
id|next
comma
r_struct
id|nfs4_client
comma
id|cl_strhash
)paren
suffix:semicolon
id|expire_client
c_func
(paren
id|clp
)paren
suffix:semicolon
)brace
)brace
)brace
r_void
DECL|function|nfs4_state_shutdown
id|nfs4_state_shutdown
c_func
(paren
r_void
)paren
(brace
id|down
c_func
(paren
op_amp
id|client_sema
)paren
suffix:semicolon
id|__nfs4_state_shutdown
c_func
(paren
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|client_sema
)paren
suffix:semicolon
)brace
eof
