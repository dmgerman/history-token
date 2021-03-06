multiline_comment|/* SHA-512 code by Jean-Luc Cooke &lt;jlcooke@certainkey.com&gt;&n; *&n; * Copyright (c) Jean-Luc Cooke &lt;jlcooke@certainkey.com&gt;&n; * Copyright (c) Andrew McDonald &lt;andrew@mcdonald.org.uk&gt;&n; * Copyright (c) 2003 Kyle McMartin &lt;kyle@debian.org&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License as published by the&n; * Free Software Foundation; either version 2, or (at your option) any&n; * later version.&n; *&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/crypto.h&gt;
macro_line|#include &lt;asm/scatterlist.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
DECL|macro|SHA384_DIGEST_SIZE
mdefine_line|#define SHA384_DIGEST_SIZE 48
DECL|macro|SHA512_DIGEST_SIZE
mdefine_line|#define SHA512_DIGEST_SIZE 64
DECL|macro|SHA384_HMAC_BLOCK_SIZE
mdefine_line|#define SHA384_HMAC_BLOCK_SIZE  96
DECL|macro|SHA512_HMAC_BLOCK_SIZE
mdefine_line|#define SHA512_HMAC_BLOCK_SIZE 128
DECL|struct|sha512_ctx
r_struct
id|sha512_ctx
(brace
DECL|member|state
id|u64
id|state
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|count
id|u32
id|count
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|buf
id|u8
id|buf
(braket
l_int|128
)braket
suffix:semicolon
DECL|member|W
id|u64
id|W
(braket
l_int|80
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|function|Ch
r_static
r_inline
id|u64
id|Ch
c_func
(paren
id|u64
id|x
comma
id|u64
id|y
comma
id|u64
id|z
)paren
(brace
r_return
id|z
op_xor
(paren
id|x
op_amp
(paren
id|y
op_xor
id|z
)paren
)paren
suffix:semicolon
)brace
DECL|function|Maj
r_static
r_inline
id|u64
id|Maj
c_func
(paren
id|u64
id|x
comma
id|u64
id|y
comma
id|u64
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
id|z
op_amp
(paren
id|x
op_or
id|y
)paren
)paren
suffix:semicolon
)brace
DECL|function|RORu64
r_static
r_inline
id|u64
id|RORu64
c_func
(paren
id|u64
id|x
comma
id|u64
id|y
)paren
(brace
r_return
(paren
id|x
op_rshift
id|y
)paren
op_or
(paren
id|x
op_lshift
(paren
l_int|64
op_minus
id|y
)paren
)paren
suffix:semicolon
)brace
DECL|variable|sha512_K
r_static
r_const
id|u64
id|sha512_K
(braket
l_int|80
)braket
op_assign
(brace
l_int|0x428a2f98d728ae22ULL
comma
l_int|0x7137449123ef65cdULL
comma
l_int|0xb5c0fbcfec4d3b2fULL
comma
l_int|0xe9b5dba58189dbbcULL
comma
l_int|0x3956c25bf348b538ULL
comma
l_int|0x59f111f1b605d019ULL
comma
l_int|0x923f82a4af194f9bULL
comma
l_int|0xab1c5ed5da6d8118ULL
comma
l_int|0xd807aa98a3030242ULL
comma
l_int|0x12835b0145706fbeULL
comma
l_int|0x243185be4ee4b28cULL
comma
l_int|0x550c7dc3d5ffb4e2ULL
comma
l_int|0x72be5d74f27b896fULL
comma
l_int|0x80deb1fe3b1696b1ULL
comma
l_int|0x9bdc06a725c71235ULL
comma
l_int|0xc19bf174cf692694ULL
comma
l_int|0xe49b69c19ef14ad2ULL
comma
l_int|0xefbe4786384f25e3ULL
comma
l_int|0x0fc19dc68b8cd5b5ULL
comma
l_int|0x240ca1cc77ac9c65ULL
comma
l_int|0x2de92c6f592b0275ULL
comma
l_int|0x4a7484aa6ea6e483ULL
comma
l_int|0x5cb0a9dcbd41fbd4ULL
comma
l_int|0x76f988da831153b5ULL
comma
l_int|0x983e5152ee66dfabULL
comma
l_int|0xa831c66d2db43210ULL
comma
l_int|0xb00327c898fb213fULL
comma
l_int|0xbf597fc7beef0ee4ULL
comma
l_int|0xc6e00bf33da88fc2ULL
comma
l_int|0xd5a79147930aa725ULL
comma
l_int|0x06ca6351e003826fULL
comma
l_int|0x142929670a0e6e70ULL
comma
l_int|0x27b70a8546d22ffcULL
comma
l_int|0x2e1b21385c26c926ULL
comma
l_int|0x4d2c6dfc5ac42aedULL
comma
l_int|0x53380d139d95b3dfULL
comma
l_int|0x650a73548baf63deULL
comma
l_int|0x766a0abb3c77b2a8ULL
comma
l_int|0x81c2c92e47edaee6ULL
comma
l_int|0x92722c851482353bULL
comma
l_int|0xa2bfe8a14cf10364ULL
comma
l_int|0xa81a664bbc423001ULL
comma
l_int|0xc24b8b70d0f89791ULL
comma
l_int|0xc76c51a30654be30ULL
comma
l_int|0xd192e819d6ef5218ULL
comma
l_int|0xd69906245565a910ULL
comma
l_int|0xf40e35855771202aULL
comma
l_int|0x106aa07032bbd1b8ULL
comma
l_int|0x19a4c116b8d2d0c8ULL
comma
l_int|0x1e376c085141ab53ULL
comma
l_int|0x2748774cdf8eeb99ULL
comma
l_int|0x34b0bcb5e19b48a8ULL
comma
l_int|0x391c0cb3c5c95a63ULL
comma
l_int|0x4ed8aa4ae3418acbULL
comma
l_int|0x5b9cca4f7763e373ULL
comma
l_int|0x682e6ff3d6b2b8a3ULL
comma
l_int|0x748f82ee5defb2fcULL
comma
l_int|0x78a5636f43172f60ULL
comma
l_int|0x84c87814a1f0ab72ULL
comma
l_int|0x8cc702081a6439ecULL
comma
l_int|0x90befffa23631e28ULL
comma
l_int|0xa4506cebde82bde9ULL
comma
l_int|0xbef9a3f7b2c67915ULL
comma
l_int|0xc67178f2e372532bULL
comma
l_int|0xca273eceea26619cULL
comma
l_int|0xd186b8c721c0c207ULL
comma
l_int|0xeada7dd6cde0eb1eULL
comma
l_int|0xf57d4f7fee6ed178ULL
comma
l_int|0x06f067aa72176fbaULL
comma
l_int|0x0a637dc5a2c898a6ULL
comma
l_int|0x113f9804bef90daeULL
comma
l_int|0x1b710b35131c471bULL
comma
l_int|0x28db77f523047d84ULL
comma
l_int|0x32caab7b40c72493ULL
comma
l_int|0x3c9ebe0a15c9bebcULL
comma
l_int|0x431d67c49c100d4cULL
comma
l_int|0x4cc5d4becb3e42b6ULL
comma
l_int|0x597f299cfc657e2aULL
comma
l_int|0x5fcb6fab3ad6faecULL
comma
l_int|0x6c44198c4a475817ULL
comma
)brace
suffix:semicolon
DECL|macro|e0
mdefine_line|#define e0(x)       (RORu64(x,28) ^ RORu64(x,34) ^ RORu64(x,39))
DECL|macro|e1
mdefine_line|#define e1(x)       (RORu64(x,14) ^ RORu64(x,18) ^ RORu64(x,41))
DECL|macro|s0
mdefine_line|#define s0(x)       (RORu64(x, 1) ^ RORu64(x, 8) ^ (x &gt;&gt; 7))
DECL|macro|s1
mdefine_line|#define s1(x)       (RORu64(x,19) ^ RORu64(x,61) ^ (x &gt;&gt; 6))
multiline_comment|/* H* initial state for SHA-512 */
DECL|macro|H0
mdefine_line|#define H0         0x6a09e667f3bcc908ULL
DECL|macro|H1
mdefine_line|#define H1         0xbb67ae8584caa73bULL
DECL|macro|H2
mdefine_line|#define H2         0x3c6ef372fe94f82bULL
DECL|macro|H3
mdefine_line|#define H3         0xa54ff53a5f1d36f1ULL
DECL|macro|H4
mdefine_line|#define H4         0x510e527fade682d1ULL
DECL|macro|H5
mdefine_line|#define H5         0x9b05688c2b3e6c1fULL
DECL|macro|H6
mdefine_line|#define H6         0x1f83d9abfb41bd6bULL
DECL|macro|H7
mdefine_line|#define H7         0x5be0cd19137e2179ULL
multiline_comment|/* H&squot;* initial state for SHA-384 */
DECL|macro|HP0
mdefine_line|#define HP0 0xcbbb9d5dc1059ed8ULL
DECL|macro|HP1
mdefine_line|#define HP1 0x629a292a367cd507ULL
DECL|macro|HP2
mdefine_line|#define HP2 0x9159015a3070dd17ULL
DECL|macro|HP3
mdefine_line|#define HP3 0x152fecd8f70e5939ULL
DECL|macro|HP4
mdefine_line|#define HP4 0x67332667ffc00b31ULL
DECL|macro|HP5
mdefine_line|#define HP5 0x8eb44a8768581511ULL
DECL|macro|HP6
mdefine_line|#define HP6 0xdb0c2e0d64f98fa7ULL
DECL|macro|HP7
mdefine_line|#define HP7 0x47b5481dbefa4fa4ULL
DECL|function|LOAD_OP
r_static
r_inline
r_void
id|LOAD_OP
c_func
(paren
r_int
id|I
comma
id|u64
op_star
id|W
comma
r_const
id|u8
op_star
id|input
)paren
(brace
id|W
(braket
id|I
)braket
op_assign
id|__be64_to_cpu
c_func
(paren
(paren
(paren
id|__be64
op_star
)paren
(paren
id|input
)paren
)paren
(braket
id|I
)braket
)paren
suffix:semicolon
)brace
DECL|function|BLEND_OP
r_static
r_inline
r_void
id|BLEND_OP
c_func
(paren
r_int
id|I
comma
id|u64
op_star
id|W
)paren
(brace
id|W
(braket
id|I
)braket
op_assign
id|s1
c_func
(paren
id|W
(braket
id|I
op_minus
l_int|2
)braket
)paren
op_plus
id|W
(braket
id|I
op_minus
l_int|7
)braket
op_plus
id|s0
c_func
(paren
id|W
(braket
id|I
op_minus
l_int|15
)braket
)paren
op_plus
id|W
(braket
id|I
op_minus
l_int|16
)braket
suffix:semicolon
)brace
r_static
r_void
DECL|function|sha512_transform
id|sha512_transform
c_func
(paren
id|u64
op_star
id|state
comma
id|u64
op_star
id|W
comma
r_const
id|u8
op_star
id|input
)paren
(brace
id|u64
id|a
comma
id|b
comma
id|c
comma
id|d
comma
id|e
comma
id|f
comma
id|g
comma
id|h
comma
id|t1
comma
id|t2
suffix:semicolon
r_int
id|i
suffix:semicolon
multiline_comment|/* load the input */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|16
suffix:semicolon
id|i
op_increment
)paren
id|LOAD_OP
c_func
(paren
id|i
comma
id|W
comma
id|input
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|16
suffix:semicolon
id|i
OL
l_int|80
suffix:semicolon
id|i
op_increment
)paren
(brace
id|BLEND_OP
c_func
(paren
id|i
comma
id|W
)paren
suffix:semicolon
)brace
multiline_comment|/* load the state into our registers */
id|a
op_assign
id|state
(braket
l_int|0
)braket
suffix:semicolon
id|b
op_assign
id|state
(braket
l_int|1
)braket
suffix:semicolon
id|c
op_assign
id|state
(braket
l_int|2
)braket
suffix:semicolon
id|d
op_assign
id|state
(braket
l_int|3
)braket
suffix:semicolon
id|e
op_assign
id|state
(braket
l_int|4
)braket
suffix:semicolon
id|f
op_assign
id|state
(braket
l_int|5
)braket
suffix:semicolon
id|g
op_assign
id|state
(braket
l_int|6
)braket
suffix:semicolon
id|h
op_assign
id|state
(braket
l_int|7
)braket
suffix:semicolon
multiline_comment|/* now iterate */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|80
suffix:semicolon
id|i
op_add_assign
l_int|8
)paren
(brace
id|t1
op_assign
id|h
op_plus
id|e1
c_func
(paren
id|e
)paren
op_plus
id|Ch
c_func
(paren
id|e
comma
id|f
comma
id|g
)paren
op_plus
id|sha512_K
(braket
id|i
)braket
op_plus
id|W
(braket
id|i
)braket
suffix:semicolon
id|t2
op_assign
id|e0
c_func
(paren
id|a
)paren
op_plus
id|Maj
c_func
(paren
id|a
comma
id|b
comma
id|c
)paren
suffix:semicolon
id|d
op_add_assign
id|t1
suffix:semicolon
id|h
op_assign
id|t1
op_plus
id|t2
suffix:semicolon
id|t1
op_assign
id|g
op_plus
id|e1
c_func
(paren
id|d
)paren
op_plus
id|Ch
c_func
(paren
id|d
comma
id|e
comma
id|f
)paren
op_plus
id|sha512_K
(braket
id|i
op_plus
l_int|1
)braket
op_plus
id|W
(braket
id|i
op_plus
l_int|1
)braket
suffix:semicolon
id|t2
op_assign
id|e0
c_func
(paren
id|h
)paren
op_plus
id|Maj
c_func
(paren
id|h
comma
id|a
comma
id|b
)paren
suffix:semicolon
id|c
op_add_assign
id|t1
suffix:semicolon
id|g
op_assign
id|t1
op_plus
id|t2
suffix:semicolon
id|t1
op_assign
id|f
op_plus
id|e1
c_func
(paren
id|c
)paren
op_plus
id|Ch
c_func
(paren
id|c
comma
id|d
comma
id|e
)paren
op_plus
id|sha512_K
(braket
id|i
op_plus
l_int|2
)braket
op_plus
id|W
(braket
id|i
op_plus
l_int|2
)braket
suffix:semicolon
id|t2
op_assign
id|e0
c_func
(paren
id|g
)paren
op_plus
id|Maj
c_func
(paren
id|g
comma
id|h
comma
id|a
)paren
suffix:semicolon
id|b
op_add_assign
id|t1
suffix:semicolon
id|f
op_assign
id|t1
op_plus
id|t2
suffix:semicolon
id|t1
op_assign
id|e
op_plus
id|e1
c_func
(paren
id|b
)paren
op_plus
id|Ch
c_func
(paren
id|b
comma
id|c
comma
id|d
)paren
op_plus
id|sha512_K
(braket
id|i
op_plus
l_int|3
)braket
op_plus
id|W
(braket
id|i
op_plus
l_int|3
)braket
suffix:semicolon
id|t2
op_assign
id|e0
c_func
(paren
id|f
)paren
op_plus
id|Maj
c_func
(paren
id|f
comma
id|g
comma
id|h
)paren
suffix:semicolon
id|a
op_add_assign
id|t1
suffix:semicolon
id|e
op_assign
id|t1
op_plus
id|t2
suffix:semicolon
id|t1
op_assign
id|d
op_plus
id|e1
c_func
(paren
id|a
)paren
op_plus
id|Ch
c_func
(paren
id|a
comma
id|b
comma
id|c
)paren
op_plus
id|sha512_K
(braket
id|i
op_plus
l_int|4
)braket
op_plus
id|W
(braket
id|i
op_plus
l_int|4
)braket
suffix:semicolon
id|t2
op_assign
id|e0
c_func
(paren
id|e
)paren
op_plus
id|Maj
c_func
(paren
id|e
comma
id|f
comma
id|g
)paren
suffix:semicolon
id|h
op_add_assign
id|t1
suffix:semicolon
id|d
op_assign
id|t1
op_plus
id|t2
suffix:semicolon
id|t1
op_assign
id|c
op_plus
id|e1
c_func
(paren
id|h
)paren
op_plus
id|Ch
c_func
(paren
id|h
comma
id|a
comma
id|b
)paren
op_plus
id|sha512_K
(braket
id|i
op_plus
l_int|5
)braket
op_plus
id|W
(braket
id|i
op_plus
l_int|5
)braket
suffix:semicolon
id|t2
op_assign
id|e0
c_func
(paren
id|d
)paren
op_plus
id|Maj
c_func
(paren
id|d
comma
id|e
comma
id|f
)paren
suffix:semicolon
id|g
op_add_assign
id|t1
suffix:semicolon
id|c
op_assign
id|t1
op_plus
id|t2
suffix:semicolon
id|t1
op_assign
id|b
op_plus
id|e1
c_func
(paren
id|g
)paren
op_plus
id|Ch
c_func
(paren
id|g
comma
id|h
comma
id|a
)paren
op_plus
id|sha512_K
(braket
id|i
op_plus
l_int|6
)braket
op_plus
id|W
(braket
id|i
op_plus
l_int|6
)braket
suffix:semicolon
id|t2
op_assign
id|e0
c_func
(paren
id|c
)paren
op_plus
id|Maj
c_func
(paren
id|c
comma
id|d
comma
id|e
)paren
suffix:semicolon
id|f
op_add_assign
id|t1
suffix:semicolon
id|b
op_assign
id|t1
op_plus
id|t2
suffix:semicolon
id|t1
op_assign
id|a
op_plus
id|e1
c_func
(paren
id|f
)paren
op_plus
id|Ch
c_func
(paren
id|f
comma
id|g
comma
id|h
)paren
op_plus
id|sha512_K
(braket
id|i
op_plus
l_int|7
)braket
op_plus
id|W
(braket
id|i
op_plus
l_int|7
)braket
suffix:semicolon
id|t2
op_assign
id|e0
c_func
(paren
id|b
)paren
op_plus
id|Maj
c_func
(paren
id|b
comma
id|c
comma
id|d
)paren
suffix:semicolon
id|e
op_add_assign
id|t1
suffix:semicolon
id|a
op_assign
id|t1
op_plus
id|t2
suffix:semicolon
)brace
id|state
(braket
l_int|0
)braket
op_add_assign
id|a
suffix:semicolon
id|state
(braket
l_int|1
)braket
op_add_assign
id|b
suffix:semicolon
id|state
(braket
l_int|2
)braket
op_add_assign
id|c
suffix:semicolon
id|state
(braket
l_int|3
)braket
op_add_assign
id|d
suffix:semicolon
id|state
(braket
l_int|4
)braket
op_add_assign
id|e
suffix:semicolon
id|state
(braket
l_int|5
)braket
op_add_assign
id|f
suffix:semicolon
id|state
(braket
l_int|6
)braket
op_add_assign
id|g
suffix:semicolon
id|state
(braket
l_int|7
)braket
op_add_assign
id|h
suffix:semicolon
multiline_comment|/* erase our data */
id|a
op_assign
id|b
op_assign
id|c
op_assign
id|d
op_assign
id|e
op_assign
id|f
op_assign
id|g
op_assign
id|h
op_assign
id|t1
op_assign
id|t2
op_assign
l_int|0
suffix:semicolon
)brace
r_static
r_void
DECL|function|sha512_init
id|sha512_init
c_func
(paren
r_void
op_star
id|ctx
)paren
(brace
r_struct
id|sha512_ctx
op_star
id|sctx
op_assign
id|ctx
suffix:semicolon
id|sctx-&gt;state
(braket
l_int|0
)braket
op_assign
id|H0
suffix:semicolon
id|sctx-&gt;state
(braket
l_int|1
)braket
op_assign
id|H1
suffix:semicolon
id|sctx-&gt;state
(braket
l_int|2
)braket
op_assign
id|H2
suffix:semicolon
id|sctx-&gt;state
(braket
l_int|3
)braket
op_assign
id|H3
suffix:semicolon
id|sctx-&gt;state
(braket
l_int|4
)braket
op_assign
id|H4
suffix:semicolon
id|sctx-&gt;state
(braket
l_int|5
)braket
op_assign
id|H5
suffix:semicolon
id|sctx-&gt;state
(braket
l_int|6
)braket
op_assign
id|H6
suffix:semicolon
id|sctx-&gt;state
(braket
l_int|7
)braket
op_assign
id|H7
suffix:semicolon
id|sctx-&gt;count
(braket
l_int|0
)braket
op_assign
id|sctx-&gt;count
(braket
l_int|1
)braket
op_assign
id|sctx-&gt;count
(braket
l_int|2
)braket
op_assign
id|sctx-&gt;count
(braket
l_int|3
)braket
op_assign
l_int|0
suffix:semicolon
id|memset
c_func
(paren
id|sctx-&gt;buf
comma
l_int|0
comma
r_sizeof
(paren
id|sctx-&gt;buf
)paren
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|sha384_init
id|sha384_init
c_func
(paren
r_void
op_star
id|ctx
)paren
(brace
r_struct
id|sha512_ctx
op_star
id|sctx
op_assign
id|ctx
suffix:semicolon
id|sctx-&gt;state
(braket
l_int|0
)braket
op_assign
id|HP0
suffix:semicolon
id|sctx-&gt;state
(braket
l_int|1
)braket
op_assign
id|HP1
suffix:semicolon
id|sctx-&gt;state
(braket
l_int|2
)braket
op_assign
id|HP2
suffix:semicolon
id|sctx-&gt;state
(braket
l_int|3
)braket
op_assign
id|HP3
suffix:semicolon
id|sctx-&gt;state
(braket
l_int|4
)braket
op_assign
id|HP4
suffix:semicolon
id|sctx-&gt;state
(braket
l_int|5
)braket
op_assign
id|HP5
suffix:semicolon
id|sctx-&gt;state
(braket
l_int|6
)braket
op_assign
id|HP6
suffix:semicolon
id|sctx-&gt;state
(braket
l_int|7
)braket
op_assign
id|HP7
suffix:semicolon
id|sctx-&gt;count
(braket
l_int|0
)braket
op_assign
id|sctx-&gt;count
(braket
l_int|1
)braket
op_assign
id|sctx-&gt;count
(braket
l_int|2
)braket
op_assign
id|sctx-&gt;count
(braket
l_int|3
)braket
op_assign
l_int|0
suffix:semicolon
id|memset
c_func
(paren
id|sctx-&gt;buf
comma
l_int|0
comma
r_sizeof
(paren
id|sctx-&gt;buf
)paren
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|sha512_update
id|sha512_update
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
r_struct
id|sha512_ctx
op_star
id|sctx
op_assign
id|ctx
suffix:semicolon
r_int
r_int
id|i
comma
id|index
comma
id|part_len
suffix:semicolon
multiline_comment|/* Compute number of bytes mod 128 */
id|index
op_assign
(paren
r_int
r_int
)paren
(paren
(paren
id|sctx-&gt;count
(braket
l_int|0
)braket
op_rshift
l_int|3
)paren
op_amp
l_int|0x7F
)paren
suffix:semicolon
multiline_comment|/* Update number of bits */
r_if
c_cond
(paren
(paren
id|sctx-&gt;count
(braket
l_int|0
)braket
op_add_assign
(paren
id|len
op_lshift
l_int|3
)paren
)paren
OL
(paren
id|len
op_lshift
l_int|3
)paren
)paren
(brace
r_if
c_cond
(paren
(paren
id|sctx-&gt;count
(braket
l_int|1
)braket
op_add_assign
l_int|1
)paren
OL
l_int|1
)paren
r_if
c_cond
(paren
(paren
id|sctx-&gt;count
(braket
l_int|2
)braket
op_add_assign
l_int|1
)paren
OL
l_int|1
)paren
id|sctx-&gt;count
(braket
l_int|3
)braket
op_increment
suffix:semicolon
id|sctx-&gt;count
(braket
l_int|1
)braket
op_add_assign
(paren
id|len
op_rshift
l_int|29
)paren
suffix:semicolon
)brace
id|part_len
op_assign
l_int|128
op_minus
id|index
suffix:semicolon
multiline_comment|/* Transform as many times as possible. */
r_if
c_cond
(paren
id|len
op_ge
id|part_len
)paren
(brace
id|memcpy
c_func
(paren
op_amp
id|sctx-&gt;buf
(braket
id|index
)braket
comma
id|data
comma
id|part_len
)paren
suffix:semicolon
id|sha512_transform
c_func
(paren
id|sctx-&gt;state
comma
id|sctx-&gt;W
comma
id|sctx-&gt;buf
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|part_len
suffix:semicolon
id|i
op_plus
l_int|127
OL
id|len
suffix:semicolon
id|i
op_add_assign
l_int|128
)paren
id|sha512_transform
c_func
(paren
id|sctx-&gt;state
comma
id|sctx-&gt;W
comma
op_amp
id|data
(braket
id|i
)braket
)paren
suffix:semicolon
id|index
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|i
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Buffer remaining input */
id|memcpy
c_func
(paren
op_amp
id|sctx-&gt;buf
(braket
id|index
)braket
comma
op_amp
id|data
(braket
id|i
)braket
comma
id|len
op_minus
id|i
)paren
suffix:semicolon
multiline_comment|/* erase our data */
id|memset
c_func
(paren
id|sctx-&gt;W
comma
l_int|0
comma
r_sizeof
(paren
id|sctx-&gt;W
)paren
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|sha512_final
id|sha512_final
c_func
(paren
r_void
op_star
id|ctx
comma
id|u8
op_star
id|hash
)paren
(brace
r_struct
id|sha512_ctx
op_star
id|sctx
op_assign
id|ctx
suffix:semicolon
r_static
id|u8
id|padding
(braket
l_int|128
)braket
op_assign
(brace
l_int|0x80
comma
)brace
suffix:semicolon
id|u32
id|t
suffix:semicolon
id|u64
id|t2
suffix:semicolon
id|u8
id|bits
(braket
l_int|128
)braket
suffix:semicolon
r_int
r_int
id|index
comma
id|pad_len
suffix:semicolon
r_int
id|i
comma
id|j
suffix:semicolon
id|index
op_assign
id|pad_len
op_assign
id|t
op_assign
id|i
op_assign
id|j
op_assign
l_int|0
suffix:semicolon
id|t2
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Save number of bits */
id|t
op_assign
id|sctx-&gt;count
(braket
l_int|0
)braket
suffix:semicolon
id|bits
(braket
l_int|15
)braket
op_assign
id|t
suffix:semicolon
id|t
op_rshift_assign
l_int|8
suffix:semicolon
id|bits
(braket
l_int|14
)braket
op_assign
id|t
suffix:semicolon
id|t
op_rshift_assign
l_int|8
suffix:semicolon
id|bits
(braket
l_int|13
)braket
op_assign
id|t
suffix:semicolon
id|t
op_rshift_assign
l_int|8
suffix:semicolon
id|bits
(braket
l_int|12
)braket
op_assign
id|t
suffix:semicolon
id|t
op_assign
id|sctx-&gt;count
(braket
l_int|1
)braket
suffix:semicolon
id|bits
(braket
l_int|11
)braket
op_assign
id|t
suffix:semicolon
id|t
op_rshift_assign
l_int|8
suffix:semicolon
id|bits
(braket
l_int|10
)braket
op_assign
id|t
suffix:semicolon
id|t
op_rshift_assign
l_int|8
suffix:semicolon
id|bits
(braket
l_int|9
)braket
op_assign
id|t
suffix:semicolon
id|t
op_rshift_assign
l_int|8
suffix:semicolon
id|bits
(braket
l_int|8
)braket
op_assign
id|t
suffix:semicolon
id|t
op_assign
id|sctx-&gt;count
(braket
l_int|2
)braket
suffix:semicolon
id|bits
(braket
l_int|7
)braket
op_assign
id|t
suffix:semicolon
id|t
op_rshift_assign
l_int|8
suffix:semicolon
id|bits
(braket
l_int|6
)braket
op_assign
id|t
suffix:semicolon
id|t
op_rshift_assign
l_int|8
suffix:semicolon
id|bits
(braket
l_int|5
)braket
op_assign
id|t
suffix:semicolon
id|t
op_rshift_assign
l_int|8
suffix:semicolon
id|bits
(braket
l_int|4
)braket
op_assign
id|t
suffix:semicolon
id|t
op_assign
id|sctx-&gt;count
(braket
l_int|3
)braket
suffix:semicolon
id|bits
(braket
l_int|3
)braket
op_assign
id|t
suffix:semicolon
id|t
op_rshift_assign
l_int|8
suffix:semicolon
id|bits
(braket
l_int|2
)braket
op_assign
id|t
suffix:semicolon
id|t
op_rshift_assign
l_int|8
suffix:semicolon
id|bits
(braket
l_int|1
)braket
op_assign
id|t
suffix:semicolon
id|t
op_rshift_assign
l_int|8
suffix:semicolon
id|bits
(braket
l_int|0
)braket
op_assign
id|t
suffix:semicolon
multiline_comment|/* Pad out to 112 mod 128. */
id|index
op_assign
(paren
id|sctx-&gt;count
(braket
l_int|0
)braket
op_rshift
l_int|3
)paren
op_amp
l_int|0x7f
suffix:semicolon
id|pad_len
op_assign
(paren
id|index
OL
l_int|112
)paren
ques
c_cond
(paren
l_int|112
op_minus
id|index
)paren
suffix:colon
(paren
(paren
l_int|128
op_plus
l_int|112
)paren
op_minus
id|index
)paren
suffix:semicolon
id|sha512_update
c_func
(paren
id|sctx
comma
id|padding
comma
id|pad_len
)paren
suffix:semicolon
multiline_comment|/* Append length (before padding) */
id|sha512_update
c_func
(paren
id|sctx
comma
id|bits
comma
l_int|16
)paren
suffix:semicolon
multiline_comment|/* Store state in digest */
r_for
c_loop
(paren
id|i
op_assign
id|j
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|8
suffix:semicolon
id|i
op_increment
comma
id|j
op_add_assign
l_int|8
)paren
(brace
id|t2
op_assign
id|sctx-&gt;state
(braket
id|i
)braket
suffix:semicolon
id|hash
(braket
id|j
op_plus
l_int|7
)braket
op_assign
(paren
r_char
)paren
id|t2
op_amp
l_int|0xff
suffix:semicolon
id|t2
op_rshift_assign
l_int|8
suffix:semicolon
id|hash
(braket
id|j
op_plus
l_int|6
)braket
op_assign
(paren
r_char
)paren
id|t2
op_amp
l_int|0xff
suffix:semicolon
id|t2
op_rshift_assign
l_int|8
suffix:semicolon
id|hash
(braket
id|j
op_plus
l_int|5
)braket
op_assign
(paren
r_char
)paren
id|t2
op_amp
l_int|0xff
suffix:semicolon
id|t2
op_rshift_assign
l_int|8
suffix:semicolon
id|hash
(braket
id|j
op_plus
l_int|4
)braket
op_assign
(paren
r_char
)paren
id|t2
op_amp
l_int|0xff
suffix:semicolon
id|t2
op_rshift_assign
l_int|8
suffix:semicolon
id|hash
(braket
id|j
op_plus
l_int|3
)braket
op_assign
(paren
r_char
)paren
id|t2
op_amp
l_int|0xff
suffix:semicolon
id|t2
op_rshift_assign
l_int|8
suffix:semicolon
id|hash
(braket
id|j
op_plus
l_int|2
)braket
op_assign
(paren
r_char
)paren
id|t2
op_amp
l_int|0xff
suffix:semicolon
id|t2
op_rshift_assign
l_int|8
suffix:semicolon
id|hash
(braket
id|j
op_plus
l_int|1
)braket
op_assign
(paren
r_char
)paren
id|t2
op_amp
l_int|0xff
suffix:semicolon
id|t2
op_rshift_assign
l_int|8
suffix:semicolon
id|hash
(braket
id|j
)braket
op_assign
(paren
r_char
)paren
id|t2
op_amp
l_int|0xff
suffix:semicolon
)brace
multiline_comment|/* Zeroize sensitive information. */
id|memset
c_func
(paren
id|sctx
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|sha512_ctx
)paren
)paren
suffix:semicolon
)brace
DECL|function|sha384_final
r_static
r_void
id|sha384_final
c_func
(paren
r_void
op_star
id|ctx
comma
id|u8
op_star
id|hash
)paren
(brace
r_struct
id|sha512_ctx
op_star
id|sctx
op_assign
id|ctx
suffix:semicolon
id|u8
id|D
(braket
l_int|64
)braket
suffix:semicolon
id|sha512_final
c_func
(paren
id|sctx
comma
id|D
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|hash
comma
id|D
comma
l_int|48
)paren
suffix:semicolon
id|memset
c_func
(paren
id|D
comma
l_int|0
comma
l_int|64
)paren
suffix:semicolon
)brace
DECL|variable|sha512
r_static
r_struct
id|crypto_alg
id|sha512
op_assign
(brace
dot
id|cra_name
op_assign
l_string|&quot;sha512&quot;
comma
dot
id|cra_flags
op_assign
id|CRYPTO_ALG_TYPE_DIGEST
comma
dot
id|cra_blocksize
op_assign
id|SHA512_HMAC_BLOCK_SIZE
comma
dot
id|cra_ctxsize
op_assign
r_sizeof
(paren
r_struct
id|sha512_ctx
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
id|sha512.cra_list
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
id|SHA512_DIGEST_SIZE
comma
dot
id|dia_init
op_assign
id|sha512_init
comma
dot
id|dia_update
op_assign
id|sha512_update
comma
dot
id|dia_final
op_assign
id|sha512_final
)brace
)brace
)brace
suffix:semicolon
DECL|variable|sha384
r_static
r_struct
id|crypto_alg
id|sha384
op_assign
(brace
dot
id|cra_name
op_assign
l_string|&quot;sha384&quot;
comma
dot
id|cra_flags
op_assign
id|CRYPTO_ALG_TYPE_DIGEST
comma
dot
id|cra_blocksize
op_assign
id|SHA384_HMAC_BLOCK_SIZE
comma
dot
id|cra_ctxsize
op_assign
r_sizeof
(paren
r_struct
id|sha512_ctx
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
id|sha384.cra_list
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
id|SHA384_DIGEST_SIZE
comma
dot
id|dia_init
op_assign
id|sha384_init
comma
dot
id|dia_update
op_assign
id|sha512_update
comma
dot
id|dia_final
op_assign
id|sha384_final
)brace
)brace
)brace
suffix:semicolon
id|MODULE_ALIAS
c_func
(paren
l_string|&quot;sha384&quot;
)paren
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
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|crypto_register_alg
c_func
(paren
op_amp
id|sha384
)paren
)paren
OL
l_int|0
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|crypto_register_alg
c_func
(paren
op_amp
id|sha512
)paren
)paren
OL
l_int|0
)paren
id|crypto_unregister_alg
c_func
(paren
op_amp
id|sha384
)paren
suffix:semicolon
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
id|sha384
)paren
suffix:semicolon
id|crypto_unregister_alg
c_func
(paren
op_amp
id|sha512
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
l_string|&quot;SHA-512 and SHA-384 Secure Hash Algorithms&quot;
)paren
suffix:semicolon
eof
