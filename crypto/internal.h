multiline_comment|/*&n; * Cryptographic API.&n; *&n; * Copyright (c) 2002 James Morris &lt;jmorris@intercode.com.au&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License as published by the Free&n; * Software Foundation; either version 2 of the License, or (at your option) &n; * any later version.&n; *&n; */
macro_line|#ifndef _CRYPTO_INTERNAL_H
DECL|macro|_CRYPTO_INTERNAL_H
mdefine_line|#define _CRYPTO_INTERNAL_H
macro_line|#include &lt;linux/crypto.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/highmem.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kmod.h&gt;
macro_line|#include &lt;asm/kmap_types.h&gt;
r_extern
r_enum
id|km_type
id|crypto_km_types
(braket
)braket
suffix:semicolon
DECL|function|crypto_kmap_type
r_static
r_inline
r_enum
id|km_type
id|crypto_kmap_type
c_func
(paren
r_int
id|out
)paren
(brace
r_return
id|crypto_km_types
(braket
(paren
id|in_softirq
c_func
(paren
)paren
ques
c_cond
l_int|2
suffix:colon
l_int|0
)paren
op_plus
id|out
)braket
suffix:semicolon
)brace
DECL|function|crypto_kmap
r_static
r_inline
r_void
op_star
id|crypto_kmap
c_func
(paren
r_struct
id|page
op_star
id|page
comma
r_int
id|out
)paren
(brace
r_return
id|kmap_atomic
c_func
(paren
id|page
comma
id|crypto_kmap_type
c_func
(paren
id|out
)paren
)paren
suffix:semicolon
)brace
DECL|function|crypto_kunmap
r_static
r_inline
r_void
id|crypto_kunmap
c_func
(paren
r_void
op_star
id|vaddr
comma
r_int
id|out
)paren
(brace
id|kunmap_atomic
c_func
(paren
id|vaddr
comma
id|crypto_kmap_type
c_func
(paren
id|out
)paren
)paren
suffix:semicolon
)brace
DECL|function|crypto_yield
r_static
r_inline
r_void
id|crypto_yield
c_func
(paren
r_struct
id|crypto_tfm
op_star
id|tfm
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|in_softirq
c_func
(paren
)paren
)paren
id|cond_resched
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|crypto_tfm_ctx
r_static
r_inline
r_void
op_star
id|crypto_tfm_ctx
c_func
(paren
r_struct
id|crypto_tfm
op_star
id|tfm
)paren
(brace
r_return
(paren
r_void
op_star
)paren
op_amp
id|tfm
(braket
l_int|1
)braket
suffix:semicolon
)brace
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
suffix:semicolon
multiline_comment|/* A far more intelligent version of this is planned.  For now, just&n; * try an exact match on the name of the algorithm. */
DECL|function|crypto_alg_mod_lookup
r_static
r_inline
r_struct
id|crypto_alg
op_star
id|crypto_alg_mod_lookup
c_func
(paren
r_const
r_char
op_star
id|name
)paren
(brace
r_return
id|try_then_request_module
c_func
(paren
id|crypto_alg_lookup
c_func
(paren
id|name
)paren
comma
id|name
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_CRYPTO_HMAC
r_int
id|crypto_alloc_hmac_block
c_func
(paren
r_struct
id|crypto_tfm
op_star
id|tfm
)paren
suffix:semicolon
r_void
id|crypto_free_hmac_block
c_func
(paren
r_struct
id|crypto_tfm
op_star
id|tfm
)paren
suffix:semicolon
macro_line|#else
DECL|function|crypto_alloc_hmac_block
r_static
r_inline
r_int
id|crypto_alloc_hmac_block
c_func
(paren
r_struct
id|crypto_tfm
op_star
id|tfm
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|crypto_free_hmac_block
r_static
r_inline
r_void
id|crypto_free_hmac_block
c_func
(paren
r_struct
id|crypto_tfm
op_star
id|tfm
)paren
(brace
)brace
macro_line|#endif
macro_line|#ifdef CONFIG_PROC_FS
r_void
id|__init
id|crypto_init_proc
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#else
DECL|function|crypto_init_proc
r_static
r_inline
r_void
id|crypto_init_proc
c_func
(paren
r_void
)paren
(brace
)brace
macro_line|#endif
r_int
id|crypto_init_digest_flags
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
suffix:semicolon
r_int
id|crypto_init_cipher_flags
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
suffix:semicolon
r_int
id|crypto_init_compress_flags
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
suffix:semicolon
r_int
id|crypto_init_digest_ops
c_func
(paren
r_struct
id|crypto_tfm
op_star
id|tfm
)paren
suffix:semicolon
r_int
id|crypto_init_cipher_ops
c_func
(paren
r_struct
id|crypto_tfm
op_star
id|tfm
)paren
suffix:semicolon
r_int
id|crypto_init_compress_ops
c_func
(paren
r_struct
id|crypto_tfm
op_star
id|tfm
)paren
suffix:semicolon
r_void
id|crypto_exit_digest_ops
c_func
(paren
r_struct
id|crypto_tfm
op_star
id|tfm
)paren
suffix:semicolon
r_void
id|crypto_exit_cipher_ops
c_func
(paren
r_struct
id|crypto_tfm
op_star
id|tfm
)paren
suffix:semicolon
r_void
id|crypto_exit_compress_ops
c_func
(paren
r_struct
id|crypto_tfm
op_star
id|tfm
)paren
suffix:semicolon
macro_line|#endif&t;/* _CRYPTO_INTERNAL_H */
eof
