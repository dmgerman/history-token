multiline_comment|/*&n; * Scatterlist Cryptographic API.&n; *&n; * Copyright (c) 2002 James Morris &lt;jmorris@intercode.com.au&gt;&n; * Copyright (c) 2002 David S. Miller (davem@redhat.com)&n; *&n; * Portions derived from Cryptoapi, by Alexander Kjeldaas &lt;astor@fast.no&gt;&n; * and Nettle, by Niels M&#xfffd;ller.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License as published by the Free&n; * Software Foundation; either version 2 of the License, or (at your option) &n; * any later version.&n; *&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/crypto.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/rwsem.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &quot;internal.h&quot;
DECL|variable|crypto_alg_list
id|LIST_HEAD
c_func
(paren
id|crypto_alg_list
)paren
suffix:semicolon
DECL|variable|crypto_alg_sem
id|DECLARE_RWSEM
c_func
(paren
id|crypto_alg_sem
)paren
suffix:semicolon
DECL|function|crypto_alg_get
r_static
r_inline
r_int
id|crypto_alg_get
c_func
(paren
r_struct
id|crypto_alg
op_star
id|alg
)paren
(brace
r_return
id|try_module_get
c_func
(paren
id|alg-&gt;cra_module
)paren
suffix:semicolon
)brace
DECL|function|crypto_alg_put
r_static
r_inline
r_void
id|crypto_alg_put
c_func
(paren
r_struct
id|crypto_alg
op_star
id|alg
)paren
(brace
id|module_put
c_func
(paren
id|alg-&gt;cra_module
)paren
suffix:semicolon
)brace
DECL|function|crypto_alg_lookup
r_struct
id|crypto_alg
op_star
id|crypto_alg_lookup
c_func
(paren
r_const
r_char
op_star
id|name
)paren
(brace
r_struct
id|crypto_alg
op_star
id|q
comma
op_star
id|alg
op_assign
l_int|NULL
suffix:semicolon
id|down_read
c_func
(paren
op_amp
id|crypto_alg_sem
)paren
suffix:semicolon
id|list_for_each_entry
c_func
(paren
id|q
comma
op_amp
id|crypto_alg_list
comma
id|cra_list
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|strcmp
c_func
(paren
id|q-&gt;cra_name
comma
id|name
)paren
)paren
)paren
(brace
r_if
c_cond
(paren
id|crypto_alg_get
c_func
(paren
id|q
)paren
)paren
id|alg
op_assign
id|q
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|up_read
c_func
(paren
op_amp
id|crypto_alg_sem
)paren
suffix:semicolon
r_return
id|alg
suffix:semicolon
)brace
DECL|function|crypto_init_flags
r_static
r_int
id|crypto_init_flags
c_func
(paren
r_struct
id|crypto_tfm
op_star
id|tfm
comma
id|u32
id|flags
)paren
(brace
id|tfm-&gt;crt_flags
op_assign
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|crypto_tfm_alg_type
c_func
(paren
id|tfm
)paren
)paren
(brace
r_case
id|CRYPTO_ALG_TYPE_CIPHER
suffix:colon
r_return
id|crypto_init_cipher_flags
c_func
(paren
id|tfm
comma
id|flags
)paren
suffix:semicolon
r_case
id|CRYPTO_ALG_TYPE_DIGEST
suffix:colon
r_return
id|crypto_init_digest_flags
c_func
(paren
id|tfm
comma
id|flags
)paren
suffix:semicolon
r_case
id|CRYPTO_ALG_TYPE_COMPRESS
suffix:colon
r_return
id|crypto_init_compress_flags
c_func
(paren
id|tfm
comma
id|flags
)paren
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|function|crypto_init_ops
r_static
r_int
id|crypto_init_ops
c_func
(paren
r_struct
id|crypto_tfm
op_star
id|tfm
)paren
(brace
r_switch
c_cond
(paren
id|crypto_tfm_alg_type
c_func
(paren
id|tfm
)paren
)paren
(brace
r_case
id|CRYPTO_ALG_TYPE_CIPHER
suffix:colon
r_return
id|crypto_init_cipher_ops
c_func
(paren
id|tfm
)paren
suffix:semicolon
r_case
id|CRYPTO_ALG_TYPE_DIGEST
suffix:colon
r_return
id|crypto_init_digest_ops
c_func
(paren
id|tfm
)paren
suffix:semicolon
r_case
id|CRYPTO_ALG_TYPE_COMPRESS
suffix:colon
r_return
id|crypto_init_compress_ops
c_func
(paren
id|tfm
)paren
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|function|crypto_exit_ops
r_static
r_void
id|crypto_exit_ops
c_func
(paren
r_struct
id|crypto_tfm
op_star
id|tfm
)paren
(brace
r_switch
c_cond
(paren
id|crypto_tfm_alg_type
c_func
(paren
id|tfm
)paren
)paren
(brace
r_case
id|CRYPTO_ALG_TYPE_CIPHER
suffix:colon
id|crypto_exit_cipher_ops
c_func
(paren
id|tfm
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CRYPTO_ALG_TYPE_DIGEST
suffix:colon
id|crypto_exit_digest_ops
c_func
(paren
id|tfm
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CRYPTO_ALG_TYPE_COMPRESS
suffix:colon
id|crypto_exit_compress_ops
c_func
(paren
id|tfm
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
)brace
DECL|function|crypto_alloc_tfm
r_struct
id|crypto_tfm
op_star
id|crypto_alloc_tfm
c_func
(paren
r_const
r_char
op_star
id|name
comma
id|u32
id|flags
)paren
(brace
r_struct
id|crypto_tfm
op_star
id|tfm
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|crypto_alg
op_star
id|alg
suffix:semicolon
id|alg
op_assign
id|crypto_alg_mod_lookup
c_func
(paren
id|name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|alg
op_eq
l_int|NULL
)paren
r_goto
id|out
suffix:semicolon
id|tfm
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|tfm
)paren
op_plus
id|alg-&gt;cra_ctxsize
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tfm
op_eq
l_int|NULL
)paren
r_goto
id|out_put
suffix:semicolon
id|memset
c_func
(paren
id|tfm
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|tfm
)paren
)paren
suffix:semicolon
id|tfm-&gt;__crt_alg
op_assign
id|alg
suffix:semicolon
r_if
c_cond
(paren
id|crypto_init_flags
c_func
(paren
id|tfm
comma
id|flags
)paren
)paren
r_goto
id|out_free_tfm
suffix:semicolon
r_if
c_cond
(paren
id|crypto_init_ops
c_func
(paren
id|tfm
)paren
)paren
(brace
id|crypto_exit_ops
c_func
(paren
id|tfm
)paren
suffix:semicolon
r_goto
id|out_free_tfm
suffix:semicolon
)brace
r_goto
id|out
suffix:semicolon
id|out_free_tfm
suffix:colon
id|kfree
c_func
(paren
id|tfm
)paren
suffix:semicolon
id|tfm
op_assign
l_int|NULL
suffix:semicolon
id|out_put
suffix:colon
id|crypto_alg_put
c_func
(paren
id|alg
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|tfm
suffix:semicolon
)brace
DECL|function|crypto_free_tfm
r_void
id|crypto_free_tfm
c_func
(paren
r_struct
id|crypto_tfm
op_star
id|tfm
)paren
(brace
id|crypto_exit_ops
c_func
(paren
id|tfm
)paren
suffix:semicolon
id|crypto_alg_put
c_func
(paren
id|tfm-&gt;__crt_alg
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|tfm
)paren
suffix:semicolon
)brace
DECL|function|crypto_register_alg
r_int
id|crypto_register_alg
c_func
(paren
r_struct
id|crypto_alg
op_star
id|alg
)paren
(brace
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_struct
id|crypto_alg
op_star
id|q
suffix:semicolon
id|down_write
c_func
(paren
op_amp
id|crypto_alg_sem
)paren
suffix:semicolon
id|list_for_each_entry
c_func
(paren
id|q
comma
op_amp
id|crypto_alg_list
comma
id|cra_list
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|strcmp
c_func
(paren
id|q-&gt;cra_name
comma
id|alg-&gt;cra_name
)paren
)paren
)paren
(brace
id|ret
op_assign
op_minus
id|EEXIST
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
)brace
id|list_add_tail
c_func
(paren
op_amp
id|alg-&gt;cra_list
comma
op_amp
id|crypto_alg_list
)paren
suffix:semicolon
id|out
suffix:colon
id|up_write
c_func
(paren
op_amp
id|crypto_alg_sem
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|crypto_unregister_alg
r_int
id|crypto_unregister_alg
c_func
(paren
r_struct
id|crypto_alg
op_star
id|alg
)paren
(brace
r_int
id|ret
op_assign
op_minus
id|ENOENT
suffix:semicolon
r_struct
id|crypto_alg
op_star
id|q
suffix:semicolon
id|BUG_ON
c_func
(paren
op_logical_neg
id|alg-&gt;cra_module
)paren
suffix:semicolon
id|down_write
c_func
(paren
op_amp
id|crypto_alg_sem
)paren
suffix:semicolon
id|list_for_each_entry
c_func
(paren
id|q
comma
op_amp
id|crypto_alg_list
comma
id|cra_list
)paren
(brace
r_if
c_cond
(paren
id|alg
op_eq
id|q
)paren
(brace
id|list_del
c_func
(paren
op_amp
id|alg-&gt;cra_list
)paren
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
)brace
id|out
suffix:colon
id|up_write
c_func
(paren
op_amp
id|crypto_alg_sem
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|crypto_alg_available
r_int
id|crypto_alg_available
c_func
(paren
r_const
r_char
op_star
id|name
comma
id|u32
id|flags
)paren
(brace
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_struct
id|crypto_alg
op_star
id|alg
op_assign
id|crypto_alg_mod_lookup
c_func
(paren
id|name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|alg
)paren
(brace
id|crypto_alg_put
c_func
(paren
id|alg
)paren
suffix:semicolon
id|ret
op_assign
l_int|1
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|function|init_crypto
r_static
r_int
id|__init
id|init_crypto
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Initializing Cryptographic API&bslash;n&quot;
)paren
suffix:semicolon
id|crypto_init_proc
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|init_crypto
id|__initcall
c_func
(paren
id|init_crypto
)paren
suffix:semicolon
DECL|variable|crypto_register_alg
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|crypto_register_alg
)paren
suffix:semicolon
DECL|variable|crypto_unregister_alg
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|crypto_unregister_alg
)paren
suffix:semicolon
DECL|variable|crypto_alloc_tfm
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|crypto_alloc_tfm
)paren
suffix:semicolon
DECL|variable|crypto_free_tfm
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|crypto_free_tfm
)paren
suffix:semicolon
DECL|variable|crypto_alg_available
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|crypto_alg_available
)paren
suffix:semicolon
eof
