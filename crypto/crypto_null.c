multiline_comment|/* &n; * Cryptographic API.&n; *&n; * Null algorithms, aka Much Ado About Nothing.&n; *&n; * These are needed for IPsec, and may be useful in general for&n; * testing &amp; debugging.&n; * &n; * The null cipher is compliant with RFC2410.&n; *&n; * Copyright (c) 2002 James Morris &lt;jmorris@intercode.com.au&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;asm/scatterlist.h&gt;
macro_line|#include &lt;linux/crypto.h&gt;
DECL|macro|NULL_KEY_SIZE
mdefine_line|#define NULL_KEY_SIZE&t;&t;0
DECL|macro|NULL_BLOCK_SIZE
mdefine_line|#define NULL_BLOCK_SIZE&t;&t;1
DECL|macro|NULL_DIGEST_SIZE
mdefine_line|#define NULL_DIGEST_SIZE&t;0
DECL|function|null_compress
r_static
r_int
id|null_compress
c_func
(paren
r_void
op_star
id|ctx
comma
r_const
id|u8
op_star
id|src
comma
r_int
r_int
id|slen
comma
id|u8
op_star
id|dst
comma
r_int
r_int
op_star
id|dlen
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|null_decompress
r_static
r_int
id|null_decompress
c_func
(paren
r_void
op_star
id|ctx
comma
r_const
id|u8
op_star
id|src
comma
r_int
r_int
id|slen
comma
id|u8
op_star
id|dst
comma
r_int
r_int
op_star
id|dlen
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|null_init
r_static
r_void
id|null_init
c_func
(paren
r_void
op_star
id|ctx
)paren
(brace
)brace
DECL|function|null_update
r_static
r_void
id|null_update
c_func
(paren
r_void
op_star
id|ctx
comma
r_const
id|u8
op_star
id|data
comma
r_int
r_int
id|len
)paren
(brace
)brace
DECL|function|null_final
r_static
r_void
id|null_final
c_func
(paren
r_void
op_star
id|ctx
comma
id|u8
op_star
id|out
)paren
(brace
)brace
DECL|function|null_setkey
r_static
r_int
id|null_setkey
c_func
(paren
r_void
op_star
id|ctx
comma
r_const
id|u8
op_star
id|key
comma
r_int
r_int
id|keylen
comma
id|u32
op_star
id|flags
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|null_encrypt
r_static
r_void
id|null_encrypt
c_func
(paren
r_void
op_star
id|ctx
comma
id|u8
op_star
id|dst
comma
r_const
id|u8
op_star
id|src
)paren
(brace
)brace
DECL|function|null_decrypt
r_static
r_void
id|null_decrypt
c_func
(paren
r_void
op_star
id|ctx
comma
id|u8
op_star
id|dst
comma
r_const
id|u8
op_star
id|src
)paren
(brace
)brace
DECL|variable|compress_null
r_static
r_struct
id|crypto_alg
id|compress_null
op_assign
(brace
dot
id|cra_name
op_assign
l_string|&quot;compress_null&quot;
comma
dot
id|cra_flags
op_assign
id|CRYPTO_ALG_TYPE_COMPRESS
comma
dot
id|cra_blocksize
op_assign
id|NULL_BLOCK_SIZE
comma
dot
id|cra_ctxsize
op_assign
l_int|0
comma
dot
id|cra_module
op_assign
id|THIS_MODULE
comma
dot
id|cra_list
op_assign
id|LIST_HEAD_INIT
c_func
(paren
id|compress_null.cra_list
)paren
comma
dot
id|cra_u
op_assign
(brace
dot
id|compress
op_assign
(brace
dot
id|coa_compress
op_assign
id|null_compress
comma
dot
id|coa_decompress
op_assign
id|null_decompress
)brace
)brace
)brace
suffix:semicolon
DECL|variable|digest_null
r_static
r_struct
id|crypto_alg
id|digest_null
op_assign
(brace
dot
id|cra_name
op_assign
l_string|&quot;digest_null&quot;
comma
dot
id|cra_flags
op_assign
id|CRYPTO_ALG_TYPE_DIGEST
comma
dot
id|cra_blocksize
op_assign
id|NULL_BLOCK_SIZE
comma
dot
id|cra_ctxsize
op_assign
l_int|0
comma
dot
id|cra_module
op_assign
id|THIS_MODULE
comma
dot
id|cra_list
op_assign
id|LIST_HEAD_INIT
c_func
(paren
id|digest_null.cra_list
)paren
comma
dot
id|cra_u
op_assign
(brace
dot
id|digest
op_assign
(brace
dot
id|dia_digestsize
op_assign
id|NULL_DIGEST_SIZE
comma
dot
id|dia_init
op_assign
id|null_init
comma
dot
id|dia_update
op_assign
id|null_update
comma
dot
id|dia_final
op_assign
id|null_final
)brace
)brace
)brace
suffix:semicolon
DECL|variable|cipher_null
r_static
r_struct
id|crypto_alg
id|cipher_null
op_assign
(brace
dot
id|cra_name
op_assign
l_string|&quot;cipher_null&quot;
comma
dot
id|cra_flags
op_assign
id|CRYPTO_ALG_TYPE_CIPHER
comma
dot
id|cra_blocksize
op_assign
id|NULL_BLOCK_SIZE
comma
dot
id|cra_ctxsize
op_assign
l_int|0
comma
dot
id|cra_module
op_assign
id|THIS_MODULE
comma
dot
id|cra_list
op_assign
id|LIST_HEAD_INIT
c_func
(paren
id|cipher_null.cra_list
)paren
comma
dot
id|cra_u
op_assign
(brace
dot
id|cipher
op_assign
(brace
dot
id|cia_min_keysize
op_assign
id|NULL_KEY_SIZE
comma
dot
id|cia_max_keysize
op_assign
id|NULL_KEY_SIZE
comma
dot
id|cia_setkey
op_assign
id|null_setkey
comma
dot
id|cia_encrypt
op_assign
id|null_encrypt
comma
dot
id|cia_decrypt
op_assign
id|null_decrypt
)brace
)brace
)brace
suffix:semicolon
DECL|function|init
r_static
r_int
id|__init
id|init
c_func
(paren
r_void
)paren
(brace
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
id|ret
op_assign
id|crypto_register_alg
c_func
(paren
op_amp
id|cipher_null
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
r_goto
id|out
suffix:semicolon
id|ret
op_assign
id|crypto_register_alg
c_func
(paren
op_amp
id|digest_null
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
(brace
id|crypto_unregister_alg
c_func
(paren
op_amp
id|cipher_null
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|ret
op_assign
id|crypto_register_alg
c_func
(paren
op_amp
id|compress_null
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
(brace
id|crypto_unregister_alg
c_func
(paren
op_amp
id|digest_null
)paren
suffix:semicolon
id|crypto_unregister_alg
c_func
(paren
op_amp
id|cipher_null
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|out
suffix:colon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|fini
r_static
r_void
id|__exit
id|fini
c_func
(paren
r_void
)paren
(brace
id|crypto_unregister_alg
c_func
(paren
op_amp
id|compress_null
)paren
suffix:semicolon
id|crypto_unregister_alg
c_func
(paren
op_amp
id|digest_null
)paren
suffix:semicolon
id|crypto_unregister_alg
c_func
(paren
op_amp
id|cipher_null
)paren
suffix:semicolon
)brace
DECL|variable|init
id|module_init
c_func
(paren
id|init
)paren
suffix:semicolon
DECL|variable|fini
id|module_exit
c_func
(paren
id|fini
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Null Cryptographic Algorithms&quot;
)paren
suffix:semicolon
eof
