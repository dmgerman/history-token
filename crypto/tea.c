multiline_comment|/* &n; * Cryptographic API.&n; *&n; * TEA and Xtended TEA Algorithms&n; *&n; * The TEA and Xtended TEA algorithms were developed by David Wheeler &n; * and Roger Needham at the Computer Laboratory of Cambridge University.&n; *&n; * Copyright (c) 2004 Aaron Grothe ajgrothe@yahoo.com&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;asm/scatterlist.h&gt;
macro_line|#include &lt;linux/crypto.h&gt;
DECL|macro|TEA_KEY_SIZE
mdefine_line|#define TEA_KEY_SIZE&t;&t;16
DECL|macro|TEA_BLOCK_SIZE
mdefine_line|#define TEA_BLOCK_SIZE&t;&t;8
DECL|macro|TEA_ROUNDS
mdefine_line|#define TEA_ROUNDS&t;&t;32
DECL|macro|TEA_DELTA
mdefine_line|#define TEA_DELTA&t;&t;0x9e3779b9
DECL|macro|XTEA_KEY_SIZE
mdefine_line|#define XTEA_KEY_SIZE&t;&t;16
DECL|macro|XTEA_BLOCK_SIZE
mdefine_line|#define XTEA_BLOCK_SIZE&t;&t;8
DECL|macro|XTEA_ROUNDS
mdefine_line|#define XTEA_ROUNDS&t;&t;32
DECL|macro|XTEA_DELTA
mdefine_line|#define XTEA_DELTA&t;&t;0x9e3779b9
DECL|macro|u32_in
mdefine_line|#define u32_in(x) le32_to_cpu(*(const __le32 *)(x))
DECL|macro|u32_out
mdefine_line|#define u32_out(to, from) (*(__le32 *)(to) = cpu_to_le32(from))
DECL|struct|tea_ctx
r_struct
id|tea_ctx
(brace
DECL|member|KEY
id|u32
id|KEY
(braket
l_int|4
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|xtea_ctx
r_struct
id|xtea_ctx
(brace
DECL|member|KEY
id|u32
id|KEY
(braket
l_int|4
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|function|tea_setkey
r_static
r_int
id|tea_setkey
c_func
(paren
r_void
op_star
id|ctx_arg
comma
r_const
id|u8
op_star
id|in_key
comma
r_int
r_int
id|key_len
comma
id|u32
op_star
id|flags
)paren
(brace
r_struct
id|tea_ctx
op_star
id|ctx
op_assign
id|ctx_arg
suffix:semicolon
r_if
c_cond
(paren
id|key_len
op_ne
l_int|16
)paren
(brace
op_star
id|flags
op_or_assign
id|CRYPTO_TFM_RES_BAD_KEY_LEN
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|ctx-&gt;KEY
(braket
l_int|0
)braket
op_assign
id|u32_in
(paren
id|in_key
)paren
suffix:semicolon
id|ctx-&gt;KEY
(braket
l_int|1
)braket
op_assign
id|u32_in
(paren
id|in_key
op_plus
l_int|4
)paren
suffix:semicolon
id|ctx-&gt;KEY
(braket
l_int|2
)braket
op_assign
id|u32_in
(paren
id|in_key
op_plus
l_int|8
)paren
suffix:semicolon
id|ctx-&gt;KEY
(braket
l_int|3
)braket
op_assign
id|u32_in
(paren
id|in_key
op_plus
l_int|12
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|tea_encrypt
r_static
r_void
id|tea_encrypt
c_func
(paren
r_void
op_star
id|ctx_arg
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
id|u32
id|y
comma
id|z
comma
id|n
comma
id|sum
op_assign
l_int|0
suffix:semicolon
id|u32
id|k0
comma
id|k1
comma
id|k2
comma
id|k3
suffix:semicolon
r_struct
id|tea_ctx
op_star
id|ctx
op_assign
id|ctx_arg
suffix:semicolon
id|y
op_assign
id|u32_in
(paren
id|src
)paren
suffix:semicolon
id|z
op_assign
id|u32_in
(paren
id|src
op_plus
l_int|4
)paren
suffix:semicolon
id|k0
op_assign
id|ctx-&gt;KEY
(braket
l_int|0
)braket
suffix:semicolon
id|k1
op_assign
id|ctx-&gt;KEY
(braket
l_int|1
)braket
suffix:semicolon
id|k2
op_assign
id|ctx-&gt;KEY
(braket
l_int|2
)braket
suffix:semicolon
id|k3
op_assign
id|ctx-&gt;KEY
(braket
l_int|3
)braket
suffix:semicolon
id|n
op_assign
id|TEA_ROUNDS
suffix:semicolon
r_while
c_loop
(paren
id|n
op_decrement
OG
l_int|0
)paren
(brace
id|sum
op_add_assign
id|TEA_DELTA
suffix:semicolon
id|y
op_add_assign
(paren
(paren
id|z
op_lshift
l_int|4
)paren
op_plus
id|k0
)paren
op_xor
(paren
id|z
op_plus
id|sum
)paren
op_xor
(paren
(paren
id|z
op_rshift
l_int|5
)paren
op_plus
id|k1
)paren
suffix:semicolon
id|z
op_add_assign
(paren
(paren
id|y
op_lshift
l_int|4
)paren
op_plus
id|k2
)paren
op_xor
(paren
id|y
op_plus
id|sum
)paren
op_xor
(paren
(paren
id|y
op_rshift
l_int|5
)paren
op_plus
id|k3
)paren
suffix:semicolon
)brace
id|u32_out
(paren
id|dst
comma
id|y
)paren
suffix:semicolon
id|u32_out
(paren
id|dst
op_plus
l_int|4
comma
id|z
)paren
suffix:semicolon
)brace
DECL|function|tea_decrypt
r_static
r_void
id|tea_decrypt
c_func
(paren
r_void
op_star
id|ctx_arg
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
id|u32
id|y
comma
id|z
comma
id|n
comma
id|sum
suffix:semicolon
id|u32
id|k0
comma
id|k1
comma
id|k2
comma
id|k3
suffix:semicolon
r_struct
id|tea_ctx
op_star
id|ctx
op_assign
id|ctx_arg
suffix:semicolon
id|y
op_assign
id|u32_in
(paren
id|src
)paren
suffix:semicolon
id|z
op_assign
id|u32_in
(paren
id|src
op_plus
l_int|4
)paren
suffix:semicolon
id|k0
op_assign
id|ctx-&gt;KEY
(braket
l_int|0
)braket
suffix:semicolon
id|k1
op_assign
id|ctx-&gt;KEY
(braket
l_int|1
)braket
suffix:semicolon
id|k2
op_assign
id|ctx-&gt;KEY
(braket
l_int|2
)braket
suffix:semicolon
id|k3
op_assign
id|ctx-&gt;KEY
(braket
l_int|3
)braket
suffix:semicolon
id|sum
op_assign
id|TEA_DELTA
op_lshift
l_int|5
suffix:semicolon
id|n
op_assign
id|TEA_ROUNDS
suffix:semicolon
r_while
c_loop
(paren
id|n
op_decrement
OG
l_int|0
)paren
(brace
id|z
op_sub_assign
(paren
(paren
id|y
op_lshift
l_int|4
)paren
op_plus
id|k2
)paren
op_xor
(paren
id|y
op_plus
id|sum
)paren
op_xor
(paren
(paren
id|y
op_rshift
l_int|5
)paren
op_plus
id|k3
)paren
suffix:semicolon
id|y
op_sub_assign
(paren
(paren
id|z
op_lshift
l_int|4
)paren
op_plus
id|k0
)paren
op_xor
(paren
id|z
op_plus
id|sum
)paren
op_xor
(paren
(paren
id|z
op_rshift
l_int|5
)paren
op_plus
id|k1
)paren
suffix:semicolon
id|sum
op_sub_assign
id|TEA_DELTA
suffix:semicolon
)brace
id|u32_out
(paren
id|dst
comma
id|y
)paren
suffix:semicolon
id|u32_out
(paren
id|dst
op_plus
l_int|4
comma
id|z
)paren
suffix:semicolon
)brace
DECL|function|xtea_setkey
r_static
r_int
id|xtea_setkey
c_func
(paren
r_void
op_star
id|ctx_arg
comma
r_const
id|u8
op_star
id|in_key
comma
r_int
r_int
id|key_len
comma
id|u32
op_star
id|flags
)paren
(brace
r_struct
id|xtea_ctx
op_star
id|ctx
op_assign
id|ctx_arg
suffix:semicolon
r_if
c_cond
(paren
id|key_len
op_ne
l_int|16
)paren
(brace
op_star
id|flags
op_or_assign
id|CRYPTO_TFM_RES_BAD_KEY_LEN
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|ctx-&gt;KEY
(braket
l_int|0
)braket
op_assign
id|u32_in
(paren
id|in_key
)paren
suffix:semicolon
id|ctx-&gt;KEY
(braket
l_int|1
)braket
op_assign
id|u32_in
(paren
id|in_key
op_plus
l_int|4
)paren
suffix:semicolon
id|ctx-&gt;KEY
(braket
l_int|2
)braket
op_assign
id|u32_in
(paren
id|in_key
op_plus
l_int|8
)paren
suffix:semicolon
id|ctx-&gt;KEY
(braket
l_int|3
)braket
op_assign
id|u32_in
(paren
id|in_key
op_plus
l_int|12
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|xtea_encrypt
r_static
r_void
id|xtea_encrypt
c_func
(paren
r_void
op_star
id|ctx_arg
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
id|u32
id|y
comma
id|z
comma
id|sum
op_assign
l_int|0
suffix:semicolon
id|u32
id|limit
op_assign
id|XTEA_DELTA
op_star
id|XTEA_ROUNDS
suffix:semicolon
r_struct
id|xtea_ctx
op_star
id|ctx
op_assign
id|ctx_arg
suffix:semicolon
id|y
op_assign
id|u32_in
(paren
id|src
)paren
suffix:semicolon
id|z
op_assign
id|u32_in
(paren
id|src
op_plus
l_int|4
)paren
suffix:semicolon
r_while
c_loop
(paren
id|sum
op_ne
id|limit
)paren
(brace
id|y
op_add_assign
(paren
id|z
op_lshift
l_int|4
op_xor
id|z
op_rshift
l_int|5
)paren
op_plus
(paren
id|z
op_xor
id|sum
)paren
op_plus
id|ctx-&gt;KEY
(braket
id|sum
op_amp
l_int|3
)braket
suffix:semicolon
id|sum
op_add_assign
id|XTEA_DELTA
suffix:semicolon
id|z
op_add_assign
(paren
id|y
op_lshift
l_int|4
op_xor
id|y
op_rshift
l_int|5
)paren
op_plus
(paren
id|y
op_xor
id|sum
)paren
op_plus
id|ctx-&gt;KEY
(braket
id|sum
op_rshift
l_int|11
op_amp
l_int|3
)braket
suffix:semicolon
)brace
id|u32_out
(paren
id|dst
comma
id|y
)paren
suffix:semicolon
id|u32_out
(paren
id|dst
op_plus
l_int|4
comma
id|z
)paren
suffix:semicolon
)brace
DECL|function|xtea_decrypt
r_static
r_void
id|xtea_decrypt
c_func
(paren
r_void
op_star
id|ctx_arg
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
id|u32
id|y
comma
id|z
comma
id|sum
suffix:semicolon
r_struct
id|tea_ctx
op_star
id|ctx
op_assign
id|ctx_arg
suffix:semicolon
id|y
op_assign
id|u32_in
(paren
id|src
)paren
suffix:semicolon
id|z
op_assign
id|u32_in
(paren
id|src
op_plus
l_int|4
)paren
suffix:semicolon
id|sum
op_assign
id|XTEA_DELTA
op_star
id|XTEA_ROUNDS
suffix:semicolon
r_while
c_loop
(paren
id|sum
)paren
(brace
id|z
op_sub_assign
(paren
id|y
op_lshift
l_int|4
op_xor
id|y
op_rshift
l_int|5
)paren
op_plus
(paren
id|y
op_xor
id|sum
)paren
op_plus
id|ctx-&gt;KEY
(braket
id|sum
op_rshift
l_int|11
op_amp
l_int|3
)braket
suffix:semicolon
id|sum
op_sub_assign
id|XTEA_DELTA
suffix:semicolon
id|y
op_sub_assign
(paren
id|z
op_lshift
l_int|4
op_xor
id|z
op_rshift
l_int|5
)paren
op_plus
(paren
id|z
op_xor
id|sum
)paren
op_plus
id|ctx-&gt;KEY
(braket
id|sum
op_amp
l_int|3
)braket
suffix:semicolon
)brace
id|u32_out
(paren
id|dst
comma
id|y
)paren
suffix:semicolon
id|u32_out
(paren
id|dst
op_plus
l_int|4
comma
id|z
)paren
suffix:semicolon
)brace
DECL|variable|tea_alg
r_static
r_struct
id|crypto_alg
id|tea_alg
op_assign
(brace
dot
id|cra_name
op_assign
l_string|&quot;tea&quot;
comma
dot
id|cra_flags
op_assign
id|CRYPTO_ALG_TYPE_CIPHER
comma
dot
id|cra_blocksize
op_assign
id|TEA_BLOCK_SIZE
comma
dot
id|cra_ctxsize
op_assign
r_sizeof
(paren
r_struct
id|tea_ctx
)paren
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
id|tea_alg.cra_list
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
id|TEA_KEY_SIZE
comma
dot
id|cia_max_keysize
op_assign
id|TEA_KEY_SIZE
comma
dot
id|cia_setkey
op_assign
id|tea_setkey
comma
dot
id|cia_encrypt
op_assign
id|tea_encrypt
comma
dot
id|cia_decrypt
op_assign
id|tea_decrypt
)brace
)brace
)brace
suffix:semicolon
DECL|variable|xtea_alg
r_static
r_struct
id|crypto_alg
id|xtea_alg
op_assign
(brace
dot
id|cra_name
op_assign
l_string|&quot;xtea&quot;
comma
dot
id|cra_flags
op_assign
id|CRYPTO_ALG_TYPE_CIPHER
comma
dot
id|cra_blocksize
op_assign
id|XTEA_BLOCK_SIZE
comma
dot
id|cra_ctxsize
op_assign
r_sizeof
(paren
r_struct
id|xtea_ctx
)paren
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
id|xtea_alg.cra_list
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
id|XTEA_KEY_SIZE
comma
dot
id|cia_max_keysize
op_assign
id|XTEA_KEY_SIZE
comma
dot
id|cia_setkey
op_assign
id|xtea_setkey
comma
dot
id|cia_encrypt
op_assign
id|xtea_encrypt
comma
dot
id|cia_decrypt
op_assign
id|xtea_decrypt
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
id|tea_alg
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
id|xtea_alg
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
id|tea_alg
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
id|tea_alg
)paren
suffix:semicolon
id|crypto_unregister_alg
c_func
(paren
op_amp
id|xtea_alg
)paren
suffix:semicolon
)brace
id|MODULE_ALIAS
c_func
(paren
l_string|&quot;xtea&quot;
)paren
suffix:semicolon
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
l_string|&quot;TEA &amp; XTEA Cryptographic Algorithms&quot;
)paren
suffix:semicolon
eof
