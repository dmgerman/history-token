multiline_comment|/* &n; * Cryptographic API.&n; *&n; * MD4 Message Digest Algorithm (RFC1320).&n; *&n; * Implementation derived from Andrew Tridgell and Steve French&squot;s&n; * CIFS MD4 implementation, and the cryptoapi implementation&n; * originally based on the public domain implementation written&n; * by Colin Plumb in 1993.&n; *&n; * Copyright (c) Andrew Tridgell 1997-1998.&n; * Modified by Steve French (sfrench@us.ibm.com) 2002&n; * Copyright (c) Cryptoapi developers.&n; * Copyright (c) 2002 David S. Miller (davem@redhat.com)&n; * Copyright (c) 2002 James Morris &lt;jmorris@intercode.com.au&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/crypto.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
DECL|macro|MD4_DIGEST_SIZE
mdefine_line|#define MD4_DIGEST_SIZE&t;&t;16
DECL|macro|MD4_HMAC_BLOCK_SIZE
mdefine_line|#define MD4_HMAC_BLOCK_SIZE&t;64
DECL|macro|MD4_BLOCK_WORDS
mdefine_line|#define MD4_BLOCK_WORDS&t;&t;16
DECL|macro|MD4_HASH_WORDS
mdefine_line|#define MD4_HASH_WORDS&t;&t;4
DECL|struct|md4_ctx
r_struct
id|md4_ctx
(brace
DECL|member|hash
id|u32
id|hash
(braket
id|MD4_HASH_WORDS
)braket
suffix:semicolon
DECL|member|block
id|u32
id|block
(braket
id|MD4_BLOCK_WORDS
)braket
suffix:semicolon
DECL|member|byte_count
id|u64
id|byte_count
suffix:semicolon
)brace
suffix:semicolon
DECL|function|lshift
r_static
id|u32
id|lshift
c_func
(paren
id|u32
id|x
comma
r_int
id|s
)paren
(brace
id|x
op_and_assign
l_int|0xFFFFFFFF
suffix:semicolon
r_return
(paren
(paren
id|x
op_lshift
id|s
)paren
op_amp
l_int|0xFFFFFFFF
)paren
op_or
(paren
id|x
op_rshift
(paren
l_int|32
op_minus
id|s
)paren
)paren
suffix:semicolon
)brace
DECL|function|F
r_static
r_inline
id|u32
id|F
c_func
(paren
id|u32
id|x
comma
id|u32
id|y
comma
id|u32
id|z
)paren
(brace
r_return
(paren
id|x
op_amp
id|y
)paren
op_or
(paren
(paren
op_complement
id|x
)paren
op_amp
id|z
)paren
suffix:semicolon
)brace
DECL|function|G
r_static
r_inline
id|u32
id|G
c_func
(paren
id|u32
id|x
comma
id|u32
id|y
comma
id|u32
id|z
)paren
(brace
r_return
(paren
id|x
op_amp
id|y
)paren
op_or
(paren
id|x
op_amp
id|z
)paren
op_or
(paren
id|y
op_amp
id|z
)paren
suffix:semicolon
)brace
DECL|function|H
r_static
r_inline
id|u32
id|H
c_func
(paren
id|u32
id|x
comma
id|u32
id|y
comma
id|u32
id|z
)paren
(brace
r_return
id|x
op_xor
id|y
op_xor
id|z
suffix:semicolon
)brace
DECL|macro|ROUND1
mdefine_line|#define ROUND1(a,b,c,d,k,s) (a = lshift(a + F(b,c,d) + k, s))
DECL|macro|ROUND2
mdefine_line|#define ROUND2(a,b,c,d,k,s) (a = lshift(a + G(b,c,d) + k + (u32)0x5A827999,s))
DECL|macro|ROUND3
mdefine_line|#define ROUND3(a,b,c,d,k,s) (a = lshift(a + H(b,c,d) + k + (u32)0x6ED9EBA1,s))
multiline_comment|/* XXX: this stuff can be optimized */
DECL|function|le32_to_cpu_array
r_static
r_inline
r_void
id|le32_to_cpu_array
c_func
(paren
id|u32
op_star
id|buf
comma
r_int
id|words
)paren
(brace
r_while
c_loop
(paren
id|words
op_decrement
)paren
(brace
id|__le32_to_cpus
c_func
(paren
id|buf
)paren
suffix:semicolon
id|buf
op_increment
suffix:semicolon
)brace
)brace
DECL|function|cpu_to_le32_array
r_static
r_inline
r_void
id|cpu_to_le32_array
c_func
(paren
id|u32
op_star
id|buf
comma
r_int
id|words
)paren
(brace
r_while
c_loop
(paren
id|words
op_decrement
)paren
(brace
id|__cpu_to_le32s
c_func
(paren
id|buf
)paren
suffix:semicolon
id|buf
op_increment
suffix:semicolon
)brace
)brace
DECL|function|md4_transform
r_static
r_inline
r_void
id|md4_transform
c_func
(paren
id|u32
op_star
id|hash
comma
id|u32
r_const
op_star
id|in
)paren
(brace
id|u32
id|a
comma
id|b
comma
id|c
comma
id|d
suffix:semicolon
id|a
op_assign
id|hash
(braket
l_int|0
)braket
suffix:semicolon
id|b
op_assign
id|hash
(braket
l_int|1
)braket
suffix:semicolon
id|c
op_assign
id|hash
(braket
l_int|2
)braket
suffix:semicolon
id|d
op_assign
id|hash
(braket
l_int|3
)braket
suffix:semicolon
id|ROUND1
c_func
(paren
id|a
comma
id|b
comma
id|c
comma
id|d
comma
id|in
(braket
l_int|0
)braket
comma
l_int|3
)paren
suffix:semicolon
id|ROUND1
c_func
(paren
id|d
comma
id|a
comma
id|b
comma
id|c
comma
id|in
(braket
l_int|1
)braket
comma
l_int|7
)paren
suffix:semicolon
id|ROUND1
c_func
(paren
id|c
comma
id|d
comma
id|a
comma
id|b
comma
id|in
(braket
l_int|2
)braket
comma
l_int|11
)paren
suffix:semicolon
id|ROUND1
c_func
(paren
id|b
comma
id|c
comma
id|d
comma
id|a
comma
id|in
(braket
l_int|3
)braket
comma
l_int|19
)paren
suffix:semicolon
id|ROUND1
c_func
(paren
id|a
comma
id|b
comma
id|c
comma
id|d
comma
id|in
(braket
l_int|4
)braket
comma
l_int|3
)paren
suffix:semicolon
id|ROUND1
c_func
(paren
id|d
comma
id|a
comma
id|b
comma
id|c
comma
id|in
(braket
l_int|5
)braket
comma
l_int|7
)paren
suffix:semicolon
id|ROUND1
c_func
(paren
id|c
comma
id|d
comma
id|a
comma
id|b
comma
id|in
(braket
l_int|6
)braket
comma
l_int|11
)paren
suffix:semicolon
id|ROUND1
c_func
(paren
id|b
comma
id|c
comma
id|d
comma
id|a
comma
id|in
(braket
l_int|7
)braket
comma
l_int|19
)paren
suffix:semicolon
id|ROUND1
c_func
(paren
id|a
comma
id|b
comma
id|c
comma
id|d
comma
id|in
(braket
l_int|8
)braket
comma
l_int|3
)paren
suffix:semicolon
id|ROUND1
c_func
(paren
id|d
comma
id|a
comma
id|b
comma
id|c
comma
id|in
(braket
l_int|9
)braket
comma
l_int|7
)paren
suffix:semicolon
id|ROUND1
c_func
(paren
id|c
comma
id|d
comma
id|a
comma
id|b
comma
id|in
(braket
l_int|10
)braket
comma
l_int|11
)paren
suffix:semicolon
id|ROUND1
c_func
(paren
id|b
comma
id|c
comma
id|d
comma
id|a
comma
id|in
(braket
l_int|11
)braket
comma
l_int|19
)paren
suffix:semicolon
id|ROUND1
c_func
(paren
id|a
comma
id|b
comma
id|c
comma
id|d
comma
id|in
(braket
l_int|12
)braket
comma
l_int|3
)paren
suffix:semicolon
id|ROUND1
c_func
(paren
id|d
comma
id|a
comma
id|b
comma
id|c
comma
id|in
(braket
l_int|13
)braket
comma
l_int|7
)paren
suffix:semicolon
id|ROUND1
c_func
(paren
id|c
comma
id|d
comma
id|a
comma
id|b
comma
id|in
(braket
l_int|14
)braket
comma
l_int|11
)paren
suffix:semicolon
id|ROUND1
c_func
(paren
id|b
comma
id|c
comma
id|d
comma
id|a
comma
id|in
(braket
l_int|15
)braket
comma
l_int|19
)paren
suffix:semicolon
id|ROUND2
c_func
(paren
id|a
comma
id|b
comma
id|c
comma
id|d
comma
id|in
(braket
l_int|0
)braket
comma
l_int|3
)paren
suffix:semicolon
id|ROUND2
c_func
(paren
id|d
comma
id|a
comma
id|b
comma
id|c
comma
id|in
(braket
l_int|4
)braket
comma
l_int|5
)paren
suffix:semicolon
id|ROUND2
c_func
(paren
id|c
comma
id|d
comma
id|a
comma
id|b
comma
id|in
(braket
l_int|8
)braket
comma
l_int|9
)paren
suffix:semicolon
id|ROUND2
c_func
(paren
id|b
comma
id|c
comma
id|d
comma
id|a
comma
id|in
(braket
l_int|12
)braket
comma
l_int|13
)paren
suffix:semicolon
id|ROUND2
c_func
(paren
id|a
comma
id|b
comma
id|c
comma
id|d
comma
id|in
(braket
l_int|1
)braket
comma
l_int|3
)paren
suffix:semicolon
id|ROUND2
c_func
(paren
id|d
comma
id|a
comma
id|b
comma
id|c
comma
id|in
(braket
l_int|5
)braket
comma
l_int|5
)paren
suffix:semicolon
id|ROUND2
c_func
(paren
id|c
comma
id|d
comma
id|a
comma
id|b
comma
id|in
(braket
l_int|9
)braket
comma
l_int|9
)paren
suffix:semicolon
id|ROUND2
c_func
(paren
id|b
comma
id|c
comma
id|d
comma
id|a
comma
id|in
(braket
l_int|13
)braket
comma
l_int|13
)paren
suffix:semicolon
id|ROUND2
c_func
(paren
id|a
comma
id|b
comma
id|c
comma
id|d
comma
id|in
(braket
l_int|2
)braket
comma
l_int|3
)paren
suffix:semicolon
id|ROUND2
c_func
(paren
id|d
comma
id|a
comma
id|b
comma
id|c
comma
id|in
(braket
l_int|6
)braket
comma
l_int|5
)paren
suffix:semicolon
id|ROUND2
c_func
(paren
id|c
comma
id|d
comma
id|a
comma
id|b
comma
id|in
(braket
l_int|10
)braket
comma
l_int|9
)paren
suffix:semicolon
id|ROUND2
c_func
(paren
id|b
comma
id|c
comma
id|d
comma
id|a
comma
id|in
(braket
l_int|14
)braket
comma
l_int|13
)paren
suffix:semicolon
id|ROUND2
c_func
(paren
id|a
comma
id|b
comma
id|c
comma
id|d
comma
id|in
(braket
l_int|3
)braket
comma
l_int|3
)paren
suffix:semicolon
id|ROUND2
c_func
(paren
id|d
comma
id|a
comma
id|b
comma
id|c
comma
id|in
(braket
l_int|7
)braket
comma
l_int|5
)paren
suffix:semicolon
id|ROUND2
c_func
(paren
id|c
comma
id|d
comma
id|a
comma
id|b
comma
id|in
(braket
l_int|11
)braket
comma
l_int|9
)paren
suffix:semicolon
id|ROUND2
c_func
(paren
id|b
comma
id|c
comma
id|d
comma
id|a
comma
id|in
(braket
l_int|15
)braket
comma
l_int|13
)paren
suffix:semicolon
id|ROUND3
c_func
(paren
id|a
comma
id|b
comma
id|c
comma
id|d
comma
id|in
(braket
l_int|0
)braket
comma
l_int|3
)paren
suffix:semicolon
id|ROUND3
c_func
(paren
id|d
comma
id|a
comma
id|b
comma
id|c
comma
id|in
(braket
l_int|8
)braket
comma
l_int|9
)paren
suffix:semicolon
id|ROUND3
c_func
(paren
id|c
comma
id|d
comma
id|a
comma
id|b
comma
id|in
(braket
l_int|4
)braket
comma
l_int|11
)paren
suffix:semicolon
id|ROUND3
c_func
(paren
id|b
comma
id|c
comma
id|d
comma
id|a
comma
id|in
(braket
l_int|12
)braket
comma
l_int|15
)paren
suffix:semicolon
id|ROUND3
c_func
(paren
id|a
comma
id|b
comma
id|c
comma
id|d
comma
id|in
(braket
l_int|2
)braket
comma
l_int|3
)paren
suffix:semicolon
id|ROUND3
c_func
(paren
id|d
comma
id|a
comma
id|b
comma
id|c
comma
id|in
(braket
l_int|10
)braket
comma
l_int|9
)paren
suffix:semicolon
id|ROUND3
c_func
(paren
id|c
comma
id|d
comma
id|a
comma
id|b
comma
id|in
(braket
l_int|6
)braket
comma
l_int|11
)paren
suffix:semicolon
id|ROUND3
c_func
(paren
id|b
comma
id|c
comma
id|d
comma
id|a
comma
id|in
(braket
l_int|14
)braket
comma
l_int|15
)paren
suffix:semicolon
id|ROUND3
c_func
(paren
id|a
comma
id|b
comma
id|c
comma
id|d
comma
id|in
(braket
l_int|1
)braket
comma
l_int|3
)paren
suffix:semicolon
id|ROUND3
c_func
(paren
id|d
comma
id|a
comma
id|b
comma
id|c
comma
id|in
(braket
l_int|9
)braket
comma
l_int|9
)paren
suffix:semicolon
id|ROUND3
c_func
(paren
id|c
comma
id|d
comma
id|a
comma
id|b
comma
id|in
(braket
l_int|5
)braket
comma
l_int|11
)paren
suffix:semicolon
id|ROUND3
c_func
(paren
id|b
comma
id|c
comma
id|d
comma
id|a
comma
id|in
(braket
l_int|13
)braket
comma
l_int|15
)paren
suffix:semicolon
id|ROUND3
c_func
(paren
id|a
comma
id|b
comma
id|c
comma
id|d
comma
id|in
(braket
l_int|3
)braket
comma
l_int|3
)paren
suffix:semicolon
id|ROUND3
c_func
(paren
id|d
comma
id|a
comma
id|b
comma
id|c
comma
id|in
(braket
l_int|11
)braket
comma
l_int|9
)paren
suffix:semicolon
id|ROUND3
c_func
(paren
id|c
comma
id|d
comma
id|a
comma
id|b
comma
id|in
(braket
l_int|7
)braket
comma
l_int|11
)paren
suffix:semicolon
id|ROUND3
c_func
(paren
id|b
comma
id|c
comma
id|d
comma
id|a
comma
id|in
(braket
l_int|15
)braket
comma
l_int|15
)paren
suffix:semicolon
id|hash
(braket
l_int|0
)braket
op_add_assign
id|a
suffix:semicolon
id|hash
(braket
l_int|1
)braket
op_add_assign
id|b
suffix:semicolon
id|hash
(braket
l_int|2
)braket
op_add_assign
id|c
suffix:semicolon
id|hash
(braket
l_int|3
)braket
op_add_assign
id|d
suffix:semicolon
)brace
DECL|function|md4_transform_helper
r_static
r_inline
r_void
id|md4_transform_helper
c_func
(paren
r_struct
id|md4_ctx
op_star
id|ctx
)paren
(brace
id|le32_to_cpu_array
c_func
(paren
id|ctx-&gt;block
comma
r_sizeof
(paren
id|ctx-&gt;block
)paren
op_div
r_sizeof
(paren
id|u32
)paren
)paren
suffix:semicolon
id|md4_transform
c_func
(paren
id|ctx-&gt;hash
comma
id|ctx-&gt;block
)paren
suffix:semicolon
)brace
DECL|function|md4_init
r_static
r_void
id|md4_init
c_func
(paren
r_void
op_star
id|ctx
)paren
(brace
r_struct
id|md4_ctx
op_star
id|mctx
op_assign
id|ctx
suffix:semicolon
id|mctx-&gt;hash
(braket
l_int|0
)braket
op_assign
l_int|0x67452301
suffix:semicolon
id|mctx-&gt;hash
(braket
l_int|1
)braket
op_assign
l_int|0xefcdab89
suffix:semicolon
id|mctx-&gt;hash
(braket
l_int|2
)braket
op_assign
l_int|0x98badcfe
suffix:semicolon
id|mctx-&gt;hash
(braket
l_int|3
)braket
op_assign
l_int|0x10325476
suffix:semicolon
id|mctx-&gt;byte_count
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|md4_update
r_static
r_void
id|md4_update
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
id|len
)paren
(brace
r_struct
id|md4_ctx
op_star
id|mctx
op_assign
id|ctx
suffix:semicolon
r_const
id|u32
id|avail
op_assign
r_sizeof
(paren
id|mctx-&gt;block
)paren
op_minus
(paren
id|mctx-&gt;byte_count
op_amp
l_int|0x3f
)paren
suffix:semicolon
id|mctx-&gt;byte_count
op_add_assign
id|len
suffix:semicolon
r_if
c_cond
(paren
id|avail
OG
id|len
)paren
(brace
id|memcpy
c_func
(paren
(paren
r_char
op_star
)paren
id|mctx-&gt;block
op_plus
(paren
r_sizeof
(paren
id|mctx-&gt;block
)paren
op_minus
id|avail
)paren
comma
id|data
comma
id|len
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|memcpy
c_func
(paren
(paren
r_char
op_star
)paren
id|mctx-&gt;block
op_plus
(paren
r_sizeof
(paren
id|mctx-&gt;block
)paren
op_minus
id|avail
)paren
comma
id|data
comma
id|avail
)paren
suffix:semicolon
id|md4_transform_helper
c_func
(paren
id|mctx
)paren
suffix:semicolon
id|data
op_add_assign
id|avail
suffix:semicolon
id|len
op_sub_assign
id|avail
suffix:semicolon
r_while
c_loop
(paren
id|len
op_ge
r_sizeof
(paren
id|mctx-&gt;block
)paren
)paren
(brace
id|memcpy
c_func
(paren
id|mctx-&gt;block
comma
id|data
comma
r_sizeof
(paren
id|mctx-&gt;block
)paren
)paren
suffix:semicolon
id|md4_transform_helper
c_func
(paren
id|mctx
)paren
suffix:semicolon
id|data
op_add_assign
r_sizeof
(paren
id|mctx-&gt;block
)paren
suffix:semicolon
id|len
op_sub_assign
r_sizeof
(paren
id|mctx-&gt;block
)paren
suffix:semicolon
)brace
id|memcpy
c_func
(paren
id|mctx-&gt;block
comma
id|data
comma
id|len
)paren
suffix:semicolon
)brace
DECL|function|md4_final
r_static
r_void
id|md4_final
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
id|md4_ctx
op_star
id|mctx
op_assign
id|ctx
suffix:semicolon
r_const
r_int
id|offset
op_assign
id|mctx-&gt;byte_count
op_amp
l_int|0x3f
suffix:semicolon
r_char
op_star
id|p
op_assign
(paren
r_char
op_star
)paren
id|mctx-&gt;block
op_plus
id|offset
suffix:semicolon
r_int
id|padding
op_assign
l_int|56
op_minus
(paren
id|offset
op_plus
l_int|1
)paren
suffix:semicolon
op_star
id|p
op_increment
op_assign
l_int|0x80
suffix:semicolon
r_if
c_cond
(paren
id|padding
OL
l_int|0
)paren
(brace
id|memset
c_func
(paren
id|p
comma
l_int|0x00
comma
id|padding
op_plus
r_sizeof
(paren
id|u64
)paren
)paren
suffix:semicolon
id|md4_transform_helper
c_func
(paren
id|mctx
)paren
suffix:semicolon
id|p
op_assign
(paren
r_char
op_star
)paren
id|mctx-&gt;block
suffix:semicolon
id|padding
op_assign
l_int|56
suffix:semicolon
)brace
id|memset
c_func
(paren
id|p
comma
l_int|0
comma
id|padding
)paren
suffix:semicolon
id|mctx-&gt;block
(braket
l_int|14
)braket
op_assign
id|mctx-&gt;byte_count
op_lshift
l_int|3
suffix:semicolon
id|mctx-&gt;block
(braket
l_int|15
)braket
op_assign
id|mctx-&gt;byte_count
op_rshift
l_int|29
suffix:semicolon
id|le32_to_cpu_array
c_func
(paren
id|mctx-&gt;block
comma
(paren
r_sizeof
(paren
id|mctx-&gt;block
)paren
op_minus
r_sizeof
(paren
id|u64
)paren
)paren
op_div
r_sizeof
(paren
id|u32
)paren
)paren
suffix:semicolon
id|md4_transform
c_func
(paren
id|mctx-&gt;hash
comma
id|mctx-&gt;block
)paren
suffix:semicolon
id|cpu_to_le32_array
c_func
(paren
id|mctx-&gt;hash
comma
r_sizeof
(paren
id|mctx-&gt;hash
)paren
op_div
r_sizeof
(paren
id|u32
)paren
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|out
comma
id|mctx-&gt;hash
comma
r_sizeof
(paren
id|mctx-&gt;hash
)paren
)paren
suffix:semicolon
id|memset
c_func
(paren
id|mctx
comma
l_int|0
comma
r_sizeof
(paren
id|mctx
)paren
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
l_string|&quot;md4&quot;
comma
dot
id|cra_flags
op_assign
id|CRYPTO_ALG_TYPE_DIGEST
comma
dot
id|cra_blocksize
op_assign
id|MD4_HMAC_BLOCK_SIZE
comma
dot
id|cra_ctxsize
op_assign
r_sizeof
(paren
r_struct
id|md4_ctx
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
id|MD4_DIGEST_SIZE
comma
dot
id|dia_init
op_assign
id|md4_init
comma
dot
id|dia_update
op_assign
id|md4_update
comma
dot
id|dia_final
op_assign
id|md4_final
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
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;MD4 Message Digest Algorithm&quot;
)paren
suffix:semicolon
eof
