multiline_comment|/* &n; * Cryptographic API.&n; *&n; * CRC32C chksum&n; *&n; * This module file is a wrapper to invoke the lib/crc32c routines.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License as published by the Free&n; * Software Foundation; either version 2 of the License, or (at your option) &n; * any later version.&n; *&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/crypto.h&gt;
macro_line|#include &lt;linux/crc32c.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
DECL|macro|CHKSUM_BLOCK_SIZE
mdefine_line|#define CHKSUM_BLOCK_SIZE&t;32
DECL|macro|CHKSUM_DIGEST_SIZE
mdefine_line|#define CHKSUM_DIGEST_SIZE&t;4
DECL|struct|chksum_ctx
r_struct
id|chksum_ctx
(brace
DECL|member|crc
id|u32
id|crc
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Steps through buffer one byte at at time, calculates reflected &n; * crc using table.&n; */
DECL|function|chksum_init
r_static
r_void
id|chksum_init
c_func
(paren
r_void
op_star
id|ctx
)paren
(brace
r_struct
id|chksum_ctx
op_star
id|mctx
op_assign
id|ctx
suffix:semicolon
id|mctx-&gt;crc
op_assign
op_complement
(paren
id|u32
)paren
l_int|0
suffix:semicolon
multiline_comment|/* common usage */
)brace
multiline_comment|/*&n; * Setting the seed allows arbitrary accumulators and flexible XOR policy&n; * If your algorithm starts with ~0, then XOR with ~0 before you set&n; * the seed.&n; */
DECL|function|chksum_setkey
r_static
r_int
id|chksum_setkey
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
r_struct
id|chksum_ctx
op_star
id|mctx
op_assign
id|ctx
suffix:semicolon
r_if
c_cond
(paren
id|keylen
op_ne
r_sizeof
(paren
id|mctx-&gt;crc
)paren
)paren
(brace
r_if
c_cond
(paren
id|flags
)paren
op_star
id|flags
op_assign
id|CRYPTO_TFM_RES_BAD_KEY_LEN
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|mctx-&gt;crc
op_assign
id|__cpu_to_le32
c_func
(paren
op_star
(paren
id|u32
op_star
)paren
id|key
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|chksum_update
r_static
r_void
id|chksum_update
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
id|length
)paren
(brace
r_struct
id|chksum_ctx
op_star
id|mctx
op_assign
id|ctx
suffix:semicolon
id|u32
id|mcrc
suffix:semicolon
id|mcrc
op_assign
id|crc32c
c_func
(paren
id|mctx-&gt;crc
comma
id|data
comma
id|length
)paren
suffix:semicolon
id|mctx-&gt;crc
op_assign
id|mcrc
suffix:semicolon
)brace
DECL|function|chksum_final
r_static
r_void
id|chksum_final
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
r_struct
id|chksum_ctx
op_star
id|mctx
op_assign
id|ctx
suffix:semicolon
id|u32
id|mcrc
op_assign
(paren
id|mctx-&gt;crc
op_xor
op_complement
(paren
id|u32
)paren
l_int|0
)paren
suffix:semicolon
op_star
(paren
id|u32
op_star
)paren
id|out
op_assign
id|__le32_to_cpu
c_func
(paren
id|mcrc
)paren
suffix:semicolon
)brace
DECL|variable|alg
r_static
r_struct
id|crypto_alg
id|alg
op_assign
(brace
dot
id|cra_name
op_assign
l_string|&quot;crc32c&quot;
comma
dot
id|cra_flags
op_assign
id|CRYPTO_ALG_TYPE_DIGEST
comma
dot
id|cra_blocksize
op_assign
id|CHKSUM_BLOCK_SIZE
comma
dot
id|cra_ctxsize
op_assign
r_sizeof
(paren
r_struct
id|chksum_ctx
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
id|alg.cra_list
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
id|CHKSUM_DIGEST_SIZE
comma
dot
id|dia_setkey
op_assign
id|chksum_setkey
comma
dot
id|dia_init
op_assign
id|chksum_init
comma
dot
id|dia_update
op_assign
id|chksum_update
comma
dot
id|dia_final
op_assign
id|chksum_final
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
r_return
id|crypto_register_alg
c_func
(paren
op_amp
id|alg
)paren
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
id|alg
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
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Clay Haapala &lt;chaapala@cisco.com&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;CRC32c (Castagnoli) calculations wrapper for lib/crc32c&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
