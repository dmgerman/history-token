multiline_comment|/*&n; * Cryptographic API.&n; *&n; * Copyright (c) 2002 James Morris &lt;jmorris@intercode.com.au&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License as published by the Free&n; * Software Foundation; either version 2 of the License, or (at your option) &n; * any later version.&n; *&n; */
macro_line|#ifndef _CRYPTO_INTERNAL_H
DECL|macro|_CRYPTO_INTERNAL_H
mdefine_line|#define _CRYPTO_INTERNAL_H
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/highmem.h&gt;
macro_line|#include &lt;asm/hardirq.h&gt;
macro_line|#include &lt;asm/softirq.h&gt;
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
)paren
(brace
r_return
id|kmap_atomic
c_func
(paren
id|page
comma
id|in_softirq
c_func
(paren
)paren
ques
c_cond
id|KM_CRYPTO_SOFTIRQ
suffix:colon
id|KM_CRYPTO_USER
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
)paren
(brace
id|kunmap_atomic
c_func
(paren
id|vaddr
comma
id|in_softirq
c_func
(paren
)paren
ques
c_cond
id|KM_CRYPTO_SOFTIRQ
suffix:colon
id|KM_CRYPTO_USER
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
DECL|function|crypto_cipher_flags
r_static
r_inline
id|u32
id|crypto_cipher_flags
c_func
(paren
id|u32
id|flags
)paren
(brace
r_return
id|flags
op_amp
(paren
id|CRYPTO_TFM_MODE_MASK
op_or
id|CRYPTO_TFM_REQ_WEAK_KEY
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_KMOD
r_void
id|crypto_alg_autoload
c_func
(paren
r_const
r_char
op_star
id|name
)paren
suffix:semicolon
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
r_void
id|crypto_init_digest_ops
c_func
(paren
r_struct
id|crypto_tfm
op_star
id|tfm
)paren
suffix:semicolon
r_void
id|crypto_init_cipher_ops
c_func
(paren
r_struct
id|crypto_tfm
op_star
id|tfm
)paren
suffix:semicolon
r_void
id|crypto_init_compress_ops
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
