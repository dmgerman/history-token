multiline_comment|/*&n; *  linux/net/sunrpc/gss_spkm3_mech.c&n; *&n; *  Copyright (c) 2003 The Regents of the University of Michigan.&n; *  All rights reserved.&n; *&n; *  Andy Adamson &lt;andros@umich.edu&gt;&n; *  J. Bruce Fields &lt;bfields@umich.edu&gt;&n; *&n; *  Redistribution and use in source and binary forms, with or without&n; *  modification, are permitted provided that the following conditions&n; *  are met:&n; *&n; *  1. Redistributions of source code must retain the above copyright&n; *     notice, this list of conditions and the following disclaimer.&n; *  2. Redistributions in binary form must reproduce the above copyright&n; *     notice, this list of conditions and the following disclaimer in the&n; *     documentation and/or other materials provided with the distribution.&n; *  3. Neither the name of the University nor the names of its&n; *     contributors may be used to endorse or promote products derived&n; *     from this software without specific prior written permission.&n; *&n; *  THIS SOFTWARE IS PROVIDED ``AS IS&squot;&squot; AND ANY EXPRESS OR IMPLIED&n; *  WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF&n; *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE&n; *  DISCLAIMED. IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE&n; *  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR&n; *  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF&n; *  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR&n; *  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF&n; *  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING&n; *  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS&n; *  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/sunrpc/auth.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/sunrpc/svcauth_gss.h&gt;
macro_line|#include &lt;linux/sunrpc/gss_spkm3.h&gt;
macro_line|#include &lt;linux/sunrpc/xdr.h&gt;
macro_line|#include &lt;linux/crypto.h&gt;
macro_line|#ifdef RPC_DEBUG
DECL|macro|RPCDBG_FACILITY
macro_line|# define RPCDBG_FACILITY&t;RPCDBG_AUTH
macro_line|#endif
DECL|variable|gss_mech_spkm3_oid
r_struct
id|xdr_netobj
id|gss_mech_spkm3_oid
op_assign
(brace
l_int|7
comma
l_string|&quot;&bslash;053&bslash;006&bslash;001&bslash;005&bslash;005&bslash;001&bslash;003&quot;
)brace
suffix:semicolon
r_static
r_inline
r_int
DECL|function|get_bytes
id|get_bytes
c_func
(paren
r_char
op_star
op_star
id|ptr
comma
r_const
r_char
op_star
id|end
comma
r_void
op_star
id|res
comma
r_int
id|len
)paren
(brace
r_char
op_star
id|p
comma
op_star
id|q
suffix:semicolon
id|p
op_assign
op_star
id|ptr
suffix:semicolon
id|q
op_assign
id|p
op_plus
id|len
suffix:semicolon
r_if
c_cond
(paren
id|q
OG
id|end
op_logical_or
id|q
OL
id|p
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|memcpy
c_func
(paren
id|res
comma
id|p
comma
id|len
)paren
suffix:semicolon
op_star
id|ptr
op_assign
id|q
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|get_netobj
id|get_netobj
c_func
(paren
r_char
op_star
op_star
id|ptr
comma
r_const
r_char
op_star
id|end
comma
r_struct
id|xdr_netobj
op_star
id|res
)paren
(brace
r_char
op_star
id|p
comma
op_star
id|q
suffix:semicolon
id|p
op_assign
op_star
id|ptr
suffix:semicolon
r_if
c_cond
(paren
id|get_bytes
c_func
(paren
op_amp
id|p
comma
id|end
comma
op_amp
id|res-&gt;len
comma
r_sizeof
(paren
id|res-&gt;len
)paren
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|q
op_assign
id|p
op_plus
id|res-&gt;len
suffix:semicolon
r_if
c_cond
(paren
id|res-&gt;len
op_eq
l_int|0
)paren
(brace
r_goto
id|out_nocopy
suffix:semicolon
)brace
r_if
c_cond
(paren
id|q
OG
id|end
op_logical_or
id|q
OL
id|p
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|res-&gt;data
op_assign
id|kmalloc
c_func
(paren
id|res-&gt;len
comma
id|GFP_KERNEL
)paren
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|memcpy
c_func
(paren
id|res-&gt;data
comma
id|p
comma
id|res-&gt;len
)paren
suffix:semicolon
id|out_nocopy
suffix:colon
op_star
id|ptr
op_assign
id|q
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|get_key
id|get_key
c_func
(paren
r_char
op_star
op_star
id|p
comma
r_char
op_star
id|end
comma
r_struct
id|crypto_tfm
op_star
op_star
id|res
comma
r_int
op_star
id|resalg
)paren
(brace
r_struct
id|xdr_netobj
id|key
op_assign
(brace
dot
id|len
op_assign
l_int|0
comma
dot
id|data
op_assign
l_int|NULL
comma
)brace
suffix:semicolon
r_int
id|alg_mode
comma
id|setkey
op_assign
l_int|0
suffix:semicolon
r_char
op_star
id|alg_name
suffix:semicolon
r_if
c_cond
(paren
id|get_bytes
c_func
(paren
id|p
comma
id|end
comma
id|resalg
comma
r_sizeof
(paren
r_int
)paren
)paren
)paren
r_goto
id|out_err
suffix:semicolon
r_if
c_cond
(paren
(paren
id|get_netobj
c_func
(paren
id|p
comma
id|end
comma
op_amp
id|key
)paren
)paren
)paren
r_goto
id|out_err
suffix:semicolon
r_switch
c_cond
(paren
op_star
id|resalg
)paren
(brace
r_case
id|NID_des_cbc
suffix:colon
id|alg_name
op_assign
l_string|&quot;des&quot;
suffix:semicolon
id|alg_mode
op_assign
id|CRYPTO_TFM_MODE_CBC
suffix:semicolon
id|setkey
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
id|NID_md5
suffix:colon
r_if
c_cond
(paren
id|key.len
op_eq
l_int|0
)paren
(brace
id|dprintk
c_func
(paren
l_string|&quot;RPC: SPKM3 get_key: NID_md5 zero Key length&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|alg_name
op_assign
l_string|&quot;md5&quot;
suffix:semicolon
id|alg_mode
op_assign
l_int|0
suffix:semicolon
id|setkey
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|NID_cast5_cbc
suffix:colon
id|dprintk
c_func
(paren
l_string|&quot;RPC: SPKM3 get_key: case cast5_cbc, UNSUPPORTED &bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|out_err
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|dprintk
c_func
(paren
l_string|&quot;RPC: SPKM3 get_key: unsupported algorithm %d&quot;
comma
op_star
id|resalg
)paren
suffix:semicolon
r_goto
id|out_err_free_key
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
op_star
id|res
op_assign
id|crypto_alloc_tfm
c_func
(paren
id|alg_name
comma
id|alg_mode
)paren
)paren
)paren
r_goto
id|out_err_free_key
suffix:semicolon
r_if
c_cond
(paren
id|setkey
)paren
(brace
r_if
c_cond
(paren
id|crypto_cipher_setkey
c_func
(paren
op_star
id|res
comma
id|key.data
comma
id|key.len
)paren
)paren
r_goto
id|out_err_free_tfm
suffix:semicolon
)brace
r_if
c_cond
(paren
id|key.len
OG
l_int|0
)paren
(brace
id|kfree
c_func
(paren
id|key.data
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
id|out_err_free_tfm
suffix:colon
id|crypto_free_tfm
c_func
(paren
op_star
id|res
)paren
suffix:semicolon
id|out_err_free_key
suffix:colon
r_if
c_cond
(paren
id|key.len
OG
l_int|0
)paren
(brace
id|kfree
c_func
(paren
id|key.data
)paren
suffix:semicolon
)brace
id|out_err
suffix:colon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_static
id|u32
DECL|function|gss_import_sec_context_spkm3
id|gss_import_sec_context_spkm3
c_func
(paren
r_struct
id|xdr_netobj
op_star
id|inbuf
comma
r_struct
id|gss_ctx
op_star
id|ctx_id
)paren
(brace
r_char
op_star
id|p
op_assign
id|inbuf-&gt;data
suffix:semicolon
r_char
op_star
id|end
op_assign
id|inbuf-&gt;data
op_plus
id|inbuf-&gt;len
suffix:semicolon
r_struct
id|spkm3_ctx
op_star
id|ctx
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|ctx
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|ctx
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
id|ctx
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|ctx
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|get_netobj
c_func
(paren
op_amp
id|p
comma
id|end
comma
op_amp
id|ctx-&gt;ctx_id
)paren
)paren
r_goto
id|out_err_free_ctx
suffix:semicolon
r_if
c_cond
(paren
id|get_bytes
c_func
(paren
op_amp
id|p
comma
id|end
comma
op_amp
id|ctx-&gt;qop
comma
r_sizeof
(paren
id|ctx-&gt;qop
)paren
)paren
)paren
r_goto
id|out_err_free_ctx_id
suffix:semicolon
r_if
c_cond
(paren
id|get_netobj
c_func
(paren
op_amp
id|p
comma
id|end
comma
op_amp
id|ctx-&gt;mech_used
)paren
)paren
r_goto
id|out_err_free_mech
suffix:semicolon
r_if
c_cond
(paren
id|get_bytes
c_func
(paren
op_amp
id|p
comma
id|end
comma
op_amp
id|ctx-&gt;ret_flags
comma
r_sizeof
(paren
id|ctx-&gt;ret_flags
)paren
)paren
)paren
r_goto
id|out_err_free_mech
suffix:semicolon
r_if
c_cond
(paren
id|get_bytes
c_func
(paren
op_amp
id|p
comma
id|end
comma
op_amp
id|ctx-&gt;req_flags
comma
r_sizeof
(paren
id|ctx-&gt;req_flags
)paren
)paren
)paren
r_goto
id|out_err_free_mech
suffix:semicolon
r_if
c_cond
(paren
id|get_netobj
c_func
(paren
op_amp
id|p
comma
id|end
comma
op_amp
id|ctx-&gt;share_key
)paren
)paren
r_goto
id|out_err_free_s_key
suffix:semicolon
r_if
c_cond
(paren
id|get_key
c_func
(paren
op_amp
id|p
comma
id|end
comma
op_amp
id|ctx-&gt;derived_conf_key
comma
op_amp
id|ctx-&gt;conf_alg
)paren
)paren
(brace
id|dprintk
c_func
(paren
l_string|&quot;RPC: SPKM3 confidentiality key will be NULL&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|get_key
c_func
(paren
op_amp
id|p
comma
id|end
comma
op_amp
id|ctx-&gt;derived_integ_key
comma
op_amp
id|ctx-&gt;intg_alg
)paren
)paren
(brace
id|dprintk
c_func
(paren
l_string|&quot;RPC: SPKM3 integrity key will be NULL&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|get_bytes
c_func
(paren
op_amp
id|p
comma
id|end
comma
op_amp
id|ctx-&gt;owf_alg
comma
r_sizeof
(paren
id|ctx-&gt;owf_alg
)paren
)paren
)paren
r_goto
id|out_err_free_s_key
suffix:semicolon
r_if
c_cond
(paren
id|get_bytes
c_func
(paren
op_amp
id|p
comma
id|end
comma
op_amp
id|ctx-&gt;owf_alg
comma
r_sizeof
(paren
id|ctx-&gt;owf_alg
)paren
)paren
)paren
r_goto
id|out_err_free_s_key
suffix:semicolon
r_if
c_cond
(paren
id|p
op_ne
id|end
)paren
r_goto
id|out_err_free_s_key
suffix:semicolon
id|ctx_id-&gt;internal_ctx_id
op_assign
id|ctx
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;Succesfully imported new spkm context.&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|out_err_free_s_key
suffix:colon
id|kfree
c_func
(paren
id|ctx-&gt;share_key.data
)paren
suffix:semicolon
id|out_err_free_mech
suffix:colon
id|kfree
c_func
(paren
id|ctx-&gt;mech_used.data
)paren
suffix:semicolon
id|out_err_free_ctx_id
suffix:colon
id|kfree
c_func
(paren
id|ctx-&gt;ctx_id.data
)paren
suffix:semicolon
id|out_err_free_ctx
suffix:colon
id|kfree
c_func
(paren
id|ctx
)paren
suffix:semicolon
id|out_err
suffix:colon
r_return
id|GSS_S_FAILURE
suffix:semicolon
)brace
r_void
DECL|function|gss_delete_sec_context_spkm3
id|gss_delete_sec_context_spkm3
c_func
(paren
r_void
op_star
id|internal_ctx
)paren
(brace
r_struct
id|spkm3_ctx
op_star
id|sctx
op_assign
id|internal_ctx
suffix:semicolon
r_if
c_cond
(paren
id|sctx-&gt;derived_integ_key
)paren
(brace
id|crypto_free_tfm
c_func
(paren
id|sctx-&gt;derived_integ_key
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sctx-&gt;derived_conf_key
)paren
(brace
id|crypto_free_tfm
c_func
(paren
id|sctx-&gt;derived_conf_key
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sctx-&gt;share_key.data
)paren
(brace
id|kfree
c_func
(paren
id|sctx-&gt;share_key.data
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sctx-&gt;mech_used.data
)paren
(brace
id|kfree
c_func
(paren
id|sctx-&gt;mech_used.data
)paren
suffix:semicolon
)brace
id|kfree
c_func
(paren
id|sctx
)paren
suffix:semicolon
)brace
id|u32
DECL|function|gss_verify_mic_spkm3
id|gss_verify_mic_spkm3
c_func
(paren
r_struct
id|gss_ctx
op_star
id|ctx
comma
r_struct
id|xdr_buf
op_star
id|signbuf
comma
r_struct
id|xdr_netobj
op_star
id|checksum
comma
id|u32
op_star
id|qstate
)paren
(brace
id|u32
id|maj_stat
op_assign
l_int|0
suffix:semicolon
r_int
id|qop_state
op_assign
l_int|0
suffix:semicolon
r_struct
id|spkm3_ctx
op_star
id|sctx
op_assign
id|ctx-&gt;internal_ctx_id
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;RPC: gss_verify_mic_spkm3 calling spkm3_read_token&bslash;n&quot;
)paren
suffix:semicolon
id|maj_stat
op_assign
id|spkm3_read_token
c_func
(paren
id|sctx
comma
id|checksum
comma
id|signbuf
comma
op_amp
id|qop_state
comma
id|SPKM_MIC_TOK
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|maj_stat
op_logical_and
id|qop_state
)paren
op_star
id|qstate
op_assign
id|qop_state
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;RPC: gss_verify_mic_spkm3 returning %d&bslash;n&quot;
comma
id|maj_stat
)paren
suffix:semicolon
r_return
id|maj_stat
suffix:semicolon
)brace
id|u32
DECL|function|gss_get_mic_spkm3
id|gss_get_mic_spkm3
c_func
(paren
r_struct
id|gss_ctx
op_star
id|ctx
comma
id|u32
id|qop
comma
r_struct
id|xdr_buf
op_star
id|message_buffer
comma
r_struct
id|xdr_netobj
op_star
id|message_token
)paren
(brace
id|u32
id|err
op_assign
l_int|0
suffix:semicolon
r_struct
id|spkm3_ctx
op_star
id|sctx
op_assign
id|ctx-&gt;internal_ctx_id
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;RPC: gss_get_mic_spkm3&bslash;n&quot;
)paren
suffix:semicolon
id|err
op_assign
id|spkm3_make_token
c_func
(paren
id|sctx
comma
id|qop
comma
id|message_buffer
comma
id|message_token
comma
id|SPKM_MIC_TOK
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|variable|gss_spkm3_ops
r_static
r_struct
id|gss_api_ops
id|gss_spkm3_ops
op_assign
(brace
dot
id|gss_import_sec_context
op_assign
id|gss_import_sec_context_spkm3
comma
dot
id|gss_get_mic
op_assign
id|gss_get_mic_spkm3
comma
dot
id|gss_verify_mic
op_assign
id|gss_verify_mic_spkm3
comma
dot
id|gss_delete_sec_context
op_assign
id|gss_delete_sec_context_spkm3
comma
)brace
suffix:semicolon
DECL|variable|gss_spkm3_pfs
r_static
r_struct
id|pf_desc
id|gss_spkm3_pfs
(braket
)braket
op_assign
(brace
(brace
id|RPC_AUTH_GSS_SPKM
comma
l_int|0
comma
id|RPC_GSS_SVC_NONE
comma
l_string|&quot;spkm3&quot;
)brace
comma
(brace
id|RPC_AUTH_GSS_SPKMI
comma
l_int|0
comma
id|RPC_GSS_SVC_INTEGRITY
comma
l_string|&quot;spkm3i&quot;
)brace
comma
)brace
suffix:semicolon
DECL|variable|gss_spkm3_mech
r_static
r_struct
id|gss_api_mech
id|gss_spkm3_mech
op_assign
(brace
dot
id|gm_name
op_assign
l_string|&quot;spkm3&quot;
comma
dot
id|gm_owner
op_assign
id|THIS_MODULE
comma
dot
id|gm_ops
op_assign
op_amp
id|gss_spkm3_ops
comma
dot
id|gm_pf_num
op_assign
id|ARRAY_SIZE
c_func
(paren
id|gss_spkm3_pfs
)paren
comma
dot
id|gm_pfs
op_assign
id|gss_spkm3_pfs
comma
)brace
suffix:semicolon
DECL|function|init_spkm3_module
r_static
r_int
id|__init
id|init_spkm3_module
c_func
(paren
r_void
)paren
(brace
r_int
id|status
suffix:semicolon
id|status
op_assign
id|gss_mech_register
c_func
(paren
op_amp
id|gss_spkm3_mech
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
)paren
id|printk
c_func
(paren
l_string|&quot;Failed to register spkm3 gss mechanism!&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cleanup_spkm3_module
r_static
r_void
id|__exit
id|cleanup_spkm3_module
c_func
(paren
r_void
)paren
(brace
id|gss_mech_unregister
c_func
(paren
op_amp
id|gss_spkm3_mech
)paren
suffix:semicolon
)brace
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|init_spkm3_module
id|module_init
c_func
(paren
id|init_spkm3_module
)paren
suffix:semicolon
DECL|variable|cleanup_spkm3_module
id|module_exit
c_func
(paren
id|cleanup_spkm3_module
)paren
suffix:semicolon
eof
