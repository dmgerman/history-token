multiline_comment|/*&n; * linux/net/sunrpc/auth_gss.c&n; *&n; * RPCSEC_GSS client authentication.&n; * &n; *  Copyright (c) 2000 The Regents of the University of Michigan.&n; *  All rights reserved.&n; *&n; *  Dug Song       &lt;dugsong@monkey.org&gt;&n; *  Andy Adamson   &lt;andros@umich.edu&gt;&n; *&n; *  Redistribution and use in source and binary forms, with or without&n; *  modification, are permitted provided that the following conditions&n; *  are met:&n; *&n; *  1. Redistributions of source code must retain the above copyright&n; *     notice, this list of conditions and the following disclaimer.&n; *  2. Redistributions in binary form must reproduce the above copyright&n; *     notice, this list of conditions and the following disclaimer in the&n; *     documentation and/or other materials provided with the distribution.&n; *  3. Neither the name of the University nor the names of its&n; *     contributors may be used to endorse or promote products derived&n; *     from this software without specific prior written permission.&n; *&n; *  THIS SOFTWARE IS PROVIDED ``AS IS&squot;&squot; AND ANY EXPRESS OR IMPLIED&n; *  WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF&n; *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE&n; *  DISCLAIMED. IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE&n; *  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR&n; *  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF&n; *  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR&n; *  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF&n; *  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING&n; *  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS&n; *  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; * $Id$&n; */
DECL|macro|__NO_VERSION__
mdefine_line|#define __NO_VERSION__
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/sunrpc/clnt.h&gt;
macro_line|#include &lt;linux/sunrpc/auth.h&gt;
macro_line|#include &lt;linux/sunrpc/auth_gss.h&gt;
macro_line|#include &lt;linux/sunrpc/gss_err.h&gt;
DECL|variable|authgss_ops
r_static
r_struct
id|rpc_authops
id|authgss_ops
suffix:semicolon
DECL|variable|gss_credops
r_static
r_struct
id|rpc_credops
id|gss_credops
suffix:semicolon
macro_line|#ifdef RPC_DEBUG
DECL|macro|RPCDBG_FACILITY
macro_line|# define RPCDBG_FACILITY&t;RPCDBG_AUTH
macro_line|#endif
DECL|macro|NFS_NGROUPS
mdefine_line|#define NFS_NGROUPS&t;16
DECL|macro|GSS_CRED_EXPIRE
mdefine_line|#define GSS_CRED_EXPIRE&t;&t;(60 * HZ)&t;/* XXX: reasonable? */
DECL|macro|GSS_CRED_SLACK
mdefine_line|#define GSS_CRED_SLACK&t;&t;1024&t;&t;/* XXX: unused */
DECL|macro|GSS_VERF_SLACK
mdefine_line|#define GSS_VERF_SLACK&t;&t;48&t;&t;/* length of a krb5 verifier.*/
multiline_comment|/* XXX this define must match the gssd define&n;* as it is passed to gssd to signal the use of&n;* machine creds should be part of the shared rpc interface */
DECL|macro|CA_RUN_AS_MACHINE
mdefine_line|#define CA_RUN_AS_MACHINE  0x00000200 
multiline_comment|/* dump the buffer in `emacs-hexl&squot; style */
DECL|macro|isprint
mdefine_line|#define isprint(c)      ((c &gt; 0x1f) &amp;&amp; (c &lt; 0x7f))
r_void
DECL|function|print_hexl
id|print_hexl
c_func
(paren
id|u32
op_star
id|p
comma
id|u_int
id|length
comma
id|u_int
id|offset
)paren
(brace
id|u_int
id|i
comma
id|j
comma
id|jm
suffix:semicolon
id|u8
id|c
comma
op_star
id|cp
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;RPC: print_hexl: length %d&bslash;n&quot;
comma
id|length
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|cp
op_assign
(paren
id|u8
op_star
)paren
id|p
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
id|length
suffix:semicolon
id|i
op_add_assign
l_int|0x10
)paren
(brace
id|dprintk
c_func
(paren
l_string|&quot;  %04x: &quot;
comma
(paren
id|u_int
)paren
(paren
id|i
op_plus
id|offset
)paren
)paren
suffix:semicolon
id|jm
op_assign
id|length
op_minus
id|i
suffix:semicolon
id|jm
op_assign
id|jm
OG
l_int|16
ques
c_cond
l_int|16
suffix:colon
id|jm
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|jm
suffix:semicolon
id|j
op_increment
)paren
(brace
r_if
c_cond
(paren
(paren
id|j
op_mod
l_int|2
)paren
op_eq
l_int|1
)paren
id|dprintk
c_func
(paren
l_string|&quot;%02x &quot;
comma
(paren
id|u_int
)paren
id|cp
(braket
id|i
op_plus
id|j
)braket
)paren
suffix:semicolon
r_else
id|dprintk
c_func
(paren
l_string|&quot;%02x&quot;
comma
(paren
id|u_int
)paren
id|cp
(braket
id|i
op_plus
id|j
)braket
)paren
suffix:semicolon
)brace
r_for
c_loop
(paren
suffix:semicolon
id|j
OL
l_int|16
suffix:semicolon
id|j
op_increment
)paren
(brace
r_if
c_cond
(paren
(paren
id|j
op_mod
l_int|2
)paren
op_eq
l_int|1
)paren
id|dprintk
c_func
(paren
l_string|&quot;   &quot;
)paren
suffix:semicolon
r_else
id|dprintk
c_func
(paren
l_string|&quot;  &quot;
)paren
suffix:semicolon
)brace
id|dprintk
c_func
(paren
l_string|&quot; &quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|jm
suffix:semicolon
id|j
op_increment
)paren
(brace
id|c
op_assign
id|cp
(braket
id|i
op_plus
id|j
)braket
suffix:semicolon
id|c
op_assign
id|isprint
c_func
(paren
id|c
)paren
ques
c_cond
id|c
suffix:colon
l_char|&squot;.&squot;
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;%c&quot;
comma
id|c
)paren
suffix:semicolon
)brace
id|dprintk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* &n; * NOTE: we have the opportunity to use different &n; * parameters based on the input flavor (which must be a pseudoflavor)&n; */
r_static
r_struct
id|rpc_auth
op_star
DECL|function|gss_create
id|gss_create
c_func
(paren
r_struct
id|rpc_clnt
op_star
id|clnt
comma
id|rpc_authflavor_t
id|flavor
)paren
(brace
r_struct
id|rpc_auth
op_star
id|auth
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;RPC: creating GSS authenticator for client %p&bslash;n&quot;
comma
id|clnt
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|try_module_get
c_func
(paren
id|THIS_MODULE
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|auth
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|auth
)paren
comma
id|GFP_KERNEL
)paren
)paren
)paren
r_goto
id|out_dec
suffix:semicolon
id|auth-&gt;au_cslack
op_assign
id|GSS_CRED_SLACK
op_rshift
l_int|2
suffix:semicolon
id|auth-&gt;au_rslack
op_assign
id|GSS_VERF_SLACK
op_rshift
l_int|2
suffix:semicolon
id|auth-&gt;au_expire
op_assign
id|GSS_CRED_EXPIRE
suffix:semicolon
id|auth-&gt;au_ops
op_assign
op_amp
id|authgss_ops
suffix:semicolon
id|auth-&gt;au_flavor
op_assign
id|flavor
suffix:semicolon
id|rpcauth_init_credcache
c_func
(paren
id|auth
)paren
suffix:semicolon
r_return
id|auth
suffix:semicolon
id|out_dec
suffix:colon
id|module_put
c_func
(paren
id|THIS_MODULE
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_static
r_void
DECL|function|gss_destroy
id|gss_destroy
c_func
(paren
r_struct
id|rpc_auth
op_star
id|auth
)paren
(brace
id|dprintk
c_func
(paren
l_string|&quot;RPC: destroying GSS authenticator %p flavor %d&bslash;n&quot;
comma
id|auth
comma
id|auth-&gt;au_flavor
)paren
suffix:semicolon
id|rpcauth_free_credcache
c_func
(paren
id|auth
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|auth
)paren
suffix:semicolon
id|module_put
c_func
(paren
id|THIS_MODULE
)paren
suffix:semicolon
)brace
multiline_comment|/* gss_destroy_cred (and gss_destroy_ctx) are used to clean up after failure&n; * to create a new cred or context, so they check that things have been&n; * allocated before freeing them. */
r_void
DECL|function|gss_destroy_ctx
id|gss_destroy_ctx
c_func
(paren
r_struct
id|gss_cl_ctx
op_star
id|ctx
)paren
(brace
id|dprintk
c_func
(paren
l_string|&quot;RPC: gss_destroy_ctx&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ctx-&gt;gc_gss_ctx
)paren
id|gss_delete_sec_context
c_func
(paren
op_amp
id|ctx-&gt;gc_gss_ctx
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ctx-&gt;gc_wire_ctx.len
OG
l_int|0
)paren
(brace
id|kfree
c_func
(paren
id|ctx-&gt;gc_wire_ctx.data
)paren
suffix:semicolon
id|ctx-&gt;gc_wire_ctx.len
op_assign
l_int|0
suffix:semicolon
)brace
id|kfree
c_func
(paren
id|ctx
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|gss_destroy_cred
id|gss_destroy_cred
c_func
(paren
r_struct
id|rpc_cred
op_star
id|rc
)paren
(brace
r_struct
id|gss_cred
op_star
id|cred
op_assign
(paren
r_struct
id|gss_cred
op_star
)paren
id|rc
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;RPC: gss_destroy_cred &bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cred-&gt;gc_ctx
)paren
id|gss_destroy_ctx
c_func
(paren
id|cred-&gt;gc_ctx
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|cred
)paren
suffix:semicolon
)brace
r_static
r_struct
id|rpc_cred
op_star
DECL|function|gss_create_cred
id|gss_create_cred
c_func
(paren
r_struct
id|rpc_auth
op_star
id|auth
comma
r_struct
id|auth_cred
op_star
id|acred
comma
r_int
id|taskflags
)paren
(brace
r_struct
id|gss_cred
op_star
id|cred
op_assign
l_int|NULL
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;RPC: gss_create_cred for uid %d, flavor %d&bslash;n&quot;
comma
id|acred-&gt;uid
comma
id|auth-&gt;au_flavor
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|cred
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|cred
)paren
comma
id|GFP_KERNEL
)paren
)paren
)paren
r_goto
id|out_err
suffix:semicolon
id|memset
c_func
(paren
id|cred
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|cred
)paren
)paren
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|cred-&gt;gc_count
comma
l_int|0
)paren
suffix:semicolon
id|cred-&gt;gc_uid
op_assign
id|acred-&gt;uid
suffix:semicolon
multiline_comment|/*&n;&t; * Note: in order to force a call to call_refresh(), we deliberately&n;&t; * fail to flag the credential as RPCAUTH_CRED_UPTODATE.&n;&t; */
id|cred-&gt;gc_flags
op_assign
l_int|0
suffix:semicolon
id|cred-&gt;gc_base.cr_ops
op_assign
op_amp
id|gss_credops
suffix:semicolon
id|cred-&gt;gc_flavor
op_assign
id|auth-&gt;au_flavor
suffix:semicolon
r_return
(paren
r_struct
id|rpc_cred
op_star
)paren
id|cred
suffix:semicolon
id|out_err
suffix:colon
id|dprintk
c_func
(paren
l_string|&quot;RPC: gss_create_cred failed&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cred
)paren
id|gss_destroy_cred
c_func
(paren
(paren
r_struct
id|rpc_cred
op_star
)paren
id|cred
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_static
r_int
DECL|function|gss_match
id|gss_match
c_func
(paren
r_struct
id|auth_cred
op_star
id|acred
comma
r_struct
id|rpc_cred
op_star
id|rc
comma
r_int
id|taskflags
)paren
(brace
r_return
(paren
id|rc-&gt;cr_uid
op_eq
id|acred-&gt;uid
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;* Marshal credentials.&n;* Maybe we should keep a cached credential for performance reasons.&n;*/
r_static
id|u32
op_star
DECL|function|gss_marshal
id|gss_marshal
c_func
(paren
r_struct
id|rpc_task
op_star
id|task
comma
id|u32
op_star
id|p
comma
r_int
id|ruid
)paren
(brace
r_struct
id|gss_cred
op_star
id|cred
op_assign
(paren
r_struct
id|gss_cred
op_star
)paren
id|task-&gt;tk_msg.rpc_cred
suffix:semicolon
r_struct
id|gss_cl_ctx
op_star
id|ctx
op_assign
id|cred-&gt;gc_ctx
suffix:semicolon
id|u32
op_star
id|cred_len
suffix:semicolon
r_struct
id|rpc_rqst
op_star
id|req
op_assign
id|task-&gt;tk_rqstp
suffix:semicolon
r_struct
id|rpc_clnt
op_star
id|clnt
op_assign
id|task-&gt;tk_client
suffix:semicolon
r_struct
id|rpc_xprt
op_star
id|xprt
op_assign
id|clnt-&gt;cl_xprt
suffix:semicolon
id|u32
op_star
id|verfbase
op_assign
id|req-&gt;rq_svec
(braket
l_int|0
)braket
dot
id|iov_base
suffix:semicolon
id|u32
id|maj_stat
op_assign
l_int|0
suffix:semicolon
r_struct
id|xdr_netobj
id|bufin
comma
id|bufout
suffix:semicolon
id|u32
id|service
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;RPC: gss_marshal&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* We compute the checksum for the verifier over the xdr-encoded bytes&n;&t; * starting with the xid (which verfbase points to) and ending at&n;&t; * the end of the credential. */
r_if
c_cond
(paren
id|xprt-&gt;stream
)paren
id|verfbase
op_increment
suffix:semicolon
multiline_comment|/* See clnt.c:call_header() */
op_star
id|p
op_increment
op_assign
id|htonl
c_func
(paren
id|RPC_AUTH_GSS
)paren
suffix:semicolon
id|cred_len
op_assign
id|p
op_increment
suffix:semicolon
id|service
op_assign
id|gss_pseudoflavor_to_service
c_func
(paren
id|cred-&gt;gc_flavor
)paren
suffix:semicolon
r_if
c_cond
(paren
id|service
op_eq
l_int|0
)paren
(brace
id|dprintk
c_func
(paren
l_string|&quot;Bad pseudoflavor %d in gss_marshal&bslash;n&quot;
comma
id|cred-&gt;gc_flavor
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|spin_lock
c_func
(paren
op_amp
id|ctx-&gt;gc_seq_lock
)paren
suffix:semicolon
id|task-&gt;tk_gss_seqno
op_assign
id|ctx-&gt;gc_seq
op_increment
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|ctx-&gt;gc_seq_lock
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
id|RPC_GSS_VERSION
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
id|ctx-&gt;gc_proc
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
id|task-&gt;tk_gss_seqno
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
id|service
)paren
suffix:semicolon
id|p
op_assign
id|xdr_encode_netobj
c_func
(paren
id|p
comma
op_amp
id|ctx-&gt;gc_wire_ctx
)paren
suffix:semicolon
op_star
id|cred_len
op_assign
id|htonl
c_func
(paren
(paren
id|p
op_minus
(paren
id|cred_len
op_plus
l_int|1
)paren
)paren
op_lshift
l_int|2
)paren
suffix:semicolon
multiline_comment|/* Marshal verifier. */
id|bufin.data
op_assign
(paren
id|u8
op_star
)paren
id|verfbase
suffix:semicolon
id|bufin.len
op_assign
(paren
id|p
op_minus
id|verfbase
)paren
op_lshift
l_int|2
suffix:semicolon
multiline_comment|/* set verifier flavor*/
op_star
id|p
op_increment
op_assign
id|htonl
c_func
(paren
id|RPC_AUTH_GSS
)paren
suffix:semicolon
id|maj_stat
op_assign
id|gss_get_mic
c_func
(paren
id|ctx-&gt;gc_gss_ctx
comma
id|GSS_C_QOP_DEFAULT
comma
op_amp
id|bufin
comma
op_amp
id|bufout
)paren
suffix:semicolon
r_if
c_cond
(paren
id|maj_stat
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;gss_marshal: gss_get_mic FAILED (%d)&bslash;n&quot;
comma
id|maj_stat
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|p
op_assign
id|xdr_encode_netobj
c_func
(paren
id|p
comma
op_amp
id|bufout
)paren
suffix:semicolon
r_return
id|p
suffix:semicolon
)brace
multiline_comment|/*&n;* Refresh credentials. XXX - finish&n;*/
r_static
r_int
DECL|function|gss_refresh
id|gss_refresh
c_func
(paren
r_struct
id|rpc_task
op_star
id|task
)paren
(brace
multiline_comment|/* Insert upcall here ! */
id|task-&gt;tk_msg.rpc_cred-&gt;cr_flags
op_or_assign
id|RPCAUTH_CRED_UPTODATE
suffix:semicolon
r_return
id|task-&gt;tk_status
op_assign
op_minus
id|EACCES
suffix:semicolon
)brace
r_static
id|u32
op_star
DECL|function|gss_validate
id|gss_validate
c_func
(paren
r_struct
id|rpc_task
op_star
id|task
comma
id|u32
op_star
id|p
)paren
(brace
r_struct
id|gss_cred
op_star
id|cred
op_assign
(paren
r_struct
id|gss_cred
op_star
)paren
id|task-&gt;tk_msg.rpc_cred
suffix:semicolon
r_struct
id|gss_cl_ctx
op_star
id|ctx
op_assign
id|cred-&gt;gc_ctx
suffix:semicolon
id|u32
id|seq
comma
id|qop_state
suffix:semicolon
r_struct
id|xdr_netobj
id|bufin
suffix:semicolon
r_struct
id|xdr_netobj
id|bufout
suffix:semicolon
id|u32
id|flav
comma
id|len
suffix:semicolon
r_int
id|code
op_assign
l_int|0
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;RPC: gss_validate&bslash;n&quot;
)paren
suffix:semicolon
id|flav
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
(paren
id|len
op_assign
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
)paren
OG
id|RPC_MAX_AUTH_SIZE
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;RPC: giant verf size: %ld&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
id|len
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|dprintk
c_func
(paren
l_string|&quot;RPC: gss_validate: verifier flavor %d, len %d&bslash;n&quot;
comma
id|flav
comma
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|flav
op_ne
id|RPC_AUTH_GSS
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;RPC: bad verf flavor: %ld&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
id|flav
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|seq
op_assign
id|htonl
c_func
(paren
id|task-&gt;tk_gss_seqno
)paren
suffix:semicolon
id|bufin.data
op_assign
(paren
id|u8
op_star
)paren
op_amp
id|seq
suffix:semicolon
id|bufin.len
op_assign
r_sizeof
(paren
id|seq
)paren
suffix:semicolon
id|bufout.data
op_assign
(paren
id|u8
op_star
)paren
id|p
suffix:semicolon
id|bufout.len
op_assign
id|len
suffix:semicolon
r_if
c_cond
(paren
(paren
id|code
op_assign
id|gss_verify_mic
c_func
(paren
id|ctx-&gt;gc_gss_ctx
comma
op_amp
id|bufin
comma
op_amp
id|bufout
comma
op_amp
id|qop_state
)paren
OL
l_int|0
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
id|task-&gt;tk_auth-&gt;au_rslack
op_assign
id|XDR_QUADLEN
c_func
(paren
id|len
)paren
op_plus
l_int|2
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;RPC: GSS gss_validate: gss_verify_mic succeeded.&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|p
op_plus
id|XDR_QUADLEN
c_func
(paren
id|len
)paren
suffix:semicolon
)brace
DECL|variable|authgss_ops
r_static
r_struct
id|rpc_authops
id|authgss_ops
op_assign
(brace
dot
id|au_flavor
op_assign
id|RPC_AUTH_GSS
comma
macro_line|#ifdef RPC_DEBUG
dot
id|au_name
op_assign
l_string|&quot;RPCSEC_GSS&quot;
comma
macro_line|#endif
dot
id|create
op_assign
id|gss_create
comma
dot
id|destroy
op_assign
id|gss_destroy
comma
dot
id|crcreate
op_assign
id|gss_create_cred
)brace
suffix:semicolon
DECL|variable|gss_credops
r_static
r_struct
id|rpc_credops
id|gss_credops
op_assign
(brace
dot
id|crdestroy
op_assign
id|gss_destroy_cred
comma
dot
id|crmatch
op_assign
id|gss_match
comma
dot
id|crmarshal
op_assign
id|gss_marshal
comma
dot
id|crrefresh
op_assign
id|gss_refresh
comma
dot
id|crvalidate
op_assign
id|gss_validate
comma
)brace
suffix:semicolon
r_extern
r_void
id|gss_svc_ctx_init
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * Initialize RPCSEC_GSS module&n; */
DECL|function|init_rpcsec_gss
r_static
r_int
id|__init
id|init_rpcsec_gss
c_func
(paren
r_void
)paren
(brace
r_int
id|err
op_assign
l_int|0
suffix:semicolon
id|err
op_assign
id|rpcauth_register
c_func
(paren
op_amp
id|authgss_ops
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|exit_rpcsec_gss
r_static
r_void
id|__exit
id|exit_rpcsec_gss
c_func
(paren
r_void
)paren
(brace
id|gss_mech_unregister_all
c_func
(paren
)paren
suffix:semicolon
id|rpcauth_unregister
c_func
(paren
op_amp
id|authgss_ops
)paren
suffix:semicolon
)brace
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|module_init
c_func
(paren
id|init_rpcsec_gss
)paren
id|module_exit
c_func
(paren
id|exit_rpcsec_gss
)paren
eof
