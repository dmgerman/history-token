multiline_comment|/*&n; *  linux/net/sunrpc/gss_mech_switch.c&n; *&n; *  Copyright (c) 2001 The Regents of the University of Michigan.&n; *  All rights reserved.&n; *&n; *  J. Bruce Fields   &lt;bfields@umich.edu&gt;&n; *&n; *  Redistribution and use in source and binary forms, with or without &n; *  modification, are permitted provided that the following conditions&n; *  are met:&n; *&n; *  1. Redistributions of source code must retain the above copyright&n; *     notice, this list of conditions and the following disclaimer.&n; *  2. Redistributions in binary form must reproduce the above copyright&n; *     notice, this list of conditions and the following disclaimer in the &n; *     documentation and/or other materials provided with the distribution.&n; *  3. Neither the name of the University nor the names of its&n; *     contributors may be used to endorse or promote products derived&n; *     from this software without specific prior written permission.&n; *&n; *  THIS SOFTWARE IS PROVIDED ``AS IS&squot;&squot; AND ANY EXPRESS OR IMPLIED&n; *  WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF&n; *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE&n; *  DISCLAIMED. IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE&n; *  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR&n; *  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF&n; *  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR&n; *  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF&n; *  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING&n; *  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS&n; *  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/sunrpc/msg_prot.h&gt;
macro_line|#include &lt;linux/sunrpc/gss_asn1.h&gt;
macro_line|#include &lt;linux/sunrpc/auth_gss.h&gt;
macro_line|#include &lt;linux/sunrpc/gss_err.h&gt;
macro_line|#include &lt;linux/sunrpc/sched.h&gt;
macro_line|#include &lt;linux/sunrpc/gss_api.h&gt;
macro_line|#include &lt;linux/sunrpc/clnt.h&gt;
macro_line|#ifdef RPC_DEBUG
DECL|macro|RPCDBG_FACILITY
macro_line|# define RPCDBG_FACILITY        RPCDBG_AUTH
macro_line|#endif
r_static
id|LIST_HEAD
c_func
(paren
id|registered_mechs
)paren
suffix:semicolon
DECL|variable|registered_mechs_lock
r_static
id|spinlock_t
id|registered_mechs_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
multiline_comment|/* Reference counting: The reference count includes the reference in the&n; * global registered_mechs list.  That reference will never diseappear&n; * (so the reference count will never go below 1) until after the mech&n; * is removed from the list.  Nothing can be removed from the list without&n; * first getting the registered_mechs_lock, so a gss_api_mech won&squot;t diseappear&n; * from underneath us while we hold the registered_mech_lock.  */
r_int
DECL|function|gss_mech_register
id|gss_mech_register
c_func
(paren
r_struct
id|xdr_netobj
op_star
id|mech_type
comma
r_struct
id|gss_api_ops
op_star
id|ops
)paren
(brace
r_struct
id|gss_api_mech
op_star
id|gm
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|gm
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|gm
)paren
comma
id|GFP_KERNEL
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Failed to allocate memory in gss_mech_register&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|gm-&gt;gm_oid.len
op_assign
id|mech_type-&gt;len
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|gm-&gt;gm_oid.data
op_assign
id|kmalloc
c_func
(paren
id|mech_type-&gt;len
comma
id|GFP_KERNEL
)paren
)paren
)paren
(brace
id|kfree
c_func
(paren
id|gm
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Failed to allocate memory in gss_mech_register&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|memcpy
c_func
(paren
id|gm-&gt;gm_oid.data
comma
id|mech_type-&gt;data
comma
id|mech_type-&gt;len
)paren
suffix:semicolon
multiline_comment|/* We&squot;re counting the reference in the registered_mechs list: */
id|atomic_set
c_func
(paren
op_amp
id|gm-&gt;gm_count
comma
l_int|1
)paren
suffix:semicolon
id|gm-&gt;gm_ops
op_assign
id|ops
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|registered_mechs_lock
)paren
suffix:semicolon
id|list_add
c_func
(paren
op_amp
id|gm-&gt;gm_list
comma
op_amp
id|registered_mechs
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|registered_mechs_lock
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;RPC:      gss_mech_register: registered mechanism with oid:&bslash;n&quot;
)paren
suffix:semicolon
id|print_hexl
c_func
(paren
(paren
id|u32
op_star
)paren
id|mech_type-&gt;data
comma
id|mech_type-&gt;len
comma
l_int|0
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* The following must be called with spinlock held: */
r_int
DECL|function|do_gss_mech_unregister
id|do_gss_mech_unregister
c_func
(paren
r_struct
id|gss_api_mech
op_star
id|gm
)paren
(brace
id|list_del
c_func
(paren
op_amp
id|gm-&gt;gm_list
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;RPC:      unregistered mechanism with oid:&bslash;n&quot;
)paren
suffix:semicolon
id|print_hexl
c_func
(paren
(paren
id|u32
op_star
)paren
id|gm-&gt;gm_oid.data
comma
id|gm-&gt;gm_oid.len
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|gss_mech_put
c_func
(paren
id|gm
)paren
)paren
(brace
id|dprintk
c_func
(paren
l_string|&quot;RPC:      We just unregistered a gss_mechanism which someone is still using.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_else
(brace
r_return
l_int|0
suffix:semicolon
)brace
)brace
r_int
DECL|function|gss_mech_unregister
id|gss_mech_unregister
c_func
(paren
r_struct
id|gss_api_mech
op_star
id|gm
)paren
(brace
r_int
id|status
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|registered_mechs_lock
)paren
suffix:semicolon
id|status
op_assign
id|do_gss_mech_unregister
c_func
(paren
id|gm
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|registered_mechs_lock
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
r_int
DECL|function|gss_mech_unregister_all
id|gss_mech_unregister_all
c_func
(paren
r_void
)paren
(brace
r_struct
id|list_head
op_star
id|pos
suffix:semicolon
r_struct
id|gss_api_mech
op_star
id|gm
suffix:semicolon
r_int
id|status
op_assign
l_int|0
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|registered_mechs_lock
)paren
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|registered_mechs
)paren
)paren
(brace
id|pos
op_assign
id|registered_mechs.next
suffix:semicolon
id|gm
op_assign
id|list_entry
c_func
(paren
id|pos
comma
r_struct
id|gss_api_mech
comma
id|gm_list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|do_gss_mech_unregister
c_func
(paren
id|gm
)paren
)paren
id|status
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|registered_mechs_lock
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
r_struct
id|gss_api_mech
op_star
DECL|function|gss_mech_get
id|gss_mech_get
c_func
(paren
r_struct
id|gss_api_mech
op_star
id|gm
)paren
(brace
id|atomic_inc
c_func
(paren
op_amp
id|gm-&gt;gm_count
)paren
suffix:semicolon
r_return
id|gm
suffix:semicolon
)brace
r_struct
id|gss_api_mech
op_star
DECL|function|gss_mech_get_by_OID
id|gss_mech_get_by_OID
c_func
(paren
r_struct
id|xdr_netobj
op_star
id|mech_type
)paren
(brace
r_struct
id|gss_api_mech
op_star
id|pos
comma
op_star
id|gm
op_assign
l_int|NULL
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;RPC:      gss_mech_get_by_OID searching for mechanism with OID:&bslash;n&quot;
)paren
suffix:semicolon
id|print_hexl
c_func
(paren
(paren
id|u32
op_star
)paren
id|mech_type-&gt;data
comma
id|mech_type-&gt;len
comma
l_int|0
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|registered_mechs_lock
)paren
suffix:semicolon
id|list_for_each_entry
c_func
(paren
id|pos
comma
op_amp
id|registered_mechs
comma
id|gm_list
)paren
(brace
r_if
c_cond
(paren
(paren
id|pos-&gt;gm_oid.len
op_eq
id|mech_type-&gt;len
)paren
op_logical_and
op_logical_neg
id|memcmp
c_func
(paren
id|pos-&gt;gm_oid.data
comma
id|mech_type-&gt;data
comma
id|mech_type-&gt;len
)paren
)paren
(brace
id|gm
op_assign
id|gss_mech_get
c_func
(paren
id|pos
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|spin_unlock
c_func
(paren
op_amp
id|registered_mechs_lock
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;RPC:      gss_mech_get_by_OID %s it&bslash;n&quot;
comma
id|gm
ques
c_cond
l_string|&quot;found&quot;
suffix:colon
l_string|&quot;didn&squot;t find&quot;
)paren
suffix:semicolon
r_return
id|gm
suffix:semicolon
)brace
r_struct
id|gss_api_mech
op_star
DECL|function|gss_mech_get_by_name
id|gss_mech_get_by_name
c_func
(paren
r_char
op_star
id|name
)paren
(brace
r_struct
id|gss_api_mech
op_star
id|pos
comma
op_star
id|gm
op_assign
l_int|NULL
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|registered_mechs_lock
)paren
suffix:semicolon
id|list_for_each_entry
c_func
(paren
id|pos
comma
op_amp
id|registered_mechs
comma
id|gm_list
)paren
(brace
r_if
c_cond
(paren
l_int|0
op_eq
id|strcmp
c_func
(paren
id|name
comma
id|pos-&gt;gm_ops-&gt;name
)paren
)paren
(brace
id|gm
op_assign
id|gss_mech_get
c_func
(paren
id|pos
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|spin_unlock
c_func
(paren
op_amp
id|registered_mechs_lock
)paren
suffix:semicolon
r_return
id|gm
suffix:semicolon
)brace
r_int
DECL|function|gss_mech_put
id|gss_mech_put
c_func
(paren
r_struct
id|gss_api_mech
op_star
id|gm
)paren
(brace
r_if
c_cond
(paren
id|atomic_dec_and_test
c_func
(paren
op_amp
id|gm-&gt;gm_count
)paren
)paren
(brace
r_if
c_cond
(paren
id|gm-&gt;gm_oid.len
OG
l_int|0
)paren
id|kfree
c_func
(paren
id|gm-&gt;gm_oid.data
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|gm
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_else
(brace
r_return
l_int|0
suffix:semicolon
)brace
)brace
multiline_comment|/* The mech could probably be determined from the token instead, but it&squot;s just&n; * as easy for now to pass it in. */
id|u32
DECL|function|gss_import_sec_context
id|gss_import_sec_context
c_func
(paren
r_struct
id|xdr_netobj
op_star
id|input_token
comma
r_struct
id|gss_api_mech
op_star
id|mech
comma
r_struct
id|gss_ctx
op_star
op_star
id|ctx_id
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
op_star
id|ctx_id
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
op_star
id|ctx_id
)paren
comma
id|GFP_KERNEL
)paren
)paren
)paren
r_return
id|GSS_S_FAILURE
suffix:semicolon
id|memset
c_func
(paren
op_star
id|ctx_id
comma
l_int|0
comma
r_sizeof
(paren
op_star
op_star
id|ctx_id
)paren
)paren
suffix:semicolon
(paren
op_star
id|ctx_id
)paren
op_member_access_from_pointer
id|mech_type
op_assign
id|gss_mech_get
c_func
(paren
id|mech
)paren
suffix:semicolon
r_return
id|mech-&gt;gm_ops
op_member_access_from_pointer
id|gss_import_sec_context
c_func
(paren
id|input_token
comma
op_star
id|ctx_id
)paren
suffix:semicolon
)brace
multiline_comment|/* gss_get_mic: compute a mic over message and return mic_token. */
id|u32
DECL|function|gss_get_mic
id|gss_get_mic
c_func
(paren
r_struct
id|gss_ctx
op_star
id|context_handle
comma
id|u32
id|qop
comma
r_struct
id|xdr_buf
op_star
id|message
comma
r_struct
id|xdr_netobj
op_star
id|mic_token
)paren
(brace
r_return
id|context_handle-&gt;mech_type-&gt;gm_ops
op_member_access_from_pointer
id|gss_get_mic
c_func
(paren
id|context_handle
comma
id|qop
comma
id|message
comma
id|mic_token
)paren
suffix:semicolon
)brace
multiline_comment|/* gss_verify_mic: check whether the provided mic_token verifies message. */
id|u32
DECL|function|gss_verify_mic
id|gss_verify_mic
c_func
(paren
r_struct
id|gss_ctx
op_star
id|context_handle
comma
r_struct
id|xdr_buf
op_star
id|message
comma
r_struct
id|xdr_netobj
op_star
id|mic_token
comma
id|u32
op_star
id|qstate
)paren
(brace
r_return
id|context_handle-&gt;mech_type-&gt;gm_ops
op_member_access_from_pointer
id|gss_verify_mic
c_func
(paren
id|context_handle
comma
id|message
comma
id|mic_token
comma
id|qstate
)paren
suffix:semicolon
)brace
multiline_comment|/* gss_delete_sec_context: free all resources associated with context_handle.&n; * Note this differs from the RFC 2744-specified prototype in that we don&squot;t&n; * bother returning an output token, since it would never be used anyway. */
id|u32
DECL|function|gss_delete_sec_context
id|gss_delete_sec_context
c_func
(paren
r_struct
id|gss_ctx
op_star
op_star
id|context_handle
)paren
(brace
id|dprintk
c_func
(paren
l_string|&quot;RPC:      gss_delete_sec_context deleting %p&bslash;n&quot;
comma
op_star
id|context_handle
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_star
id|context_handle
)paren
r_return
id|GSS_S_NO_CONTEXT
suffix:semicolon
r_if
c_cond
(paren
(paren
op_star
id|context_handle
)paren
op_member_access_from_pointer
id|internal_ctx_id
op_ne
l_int|0
)paren
(paren
op_star
id|context_handle
)paren
op_member_access_from_pointer
id|mech_type-&gt;gm_ops
op_member_access_from_pointer
id|gss_delete_sec_context
c_func
(paren
(paren
op_star
id|context_handle
)paren
op_member_access_from_pointer
id|internal_ctx_id
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
op_star
id|context_handle
)paren
op_member_access_from_pointer
id|mech_type
)paren
id|gss_mech_put
c_func
(paren
(paren
op_star
id|context_handle
)paren
op_member_access_from_pointer
id|mech_type
)paren
suffix:semicolon
id|kfree
c_func
(paren
op_star
id|context_handle
)paren
suffix:semicolon
op_star
id|context_handle
op_assign
l_int|NULL
suffix:semicolon
r_return
id|GSS_S_COMPLETE
suffix:semicolon
)brace
eof
