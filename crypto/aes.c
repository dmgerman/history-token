multiline_comment|/* &n; * Cryptographic API.&n; *&n; * AES Cipher Algorithm.&n; *&n; * Based on Brian Gladman&squot;s code.&n; *&n; * Linux developers:&n; *  Alexander Kjeldaas &lt;astor@fast.no&gt;&n; *  Herbert Valerio Riedel &lt;hvr@hvrlab.org&gt;&n; *  Kyle McMartin &lt;kyle@debian.org&gt;&n; *  Adam J. Richter &lt;adam@yggdrasil.com&gt; (conversion to 2.5 API).&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * ---------------------------------------------------------------------------&n; * Copyright (c) 2002, Dr Brian Gladman &lt;brg@gladman.me.uk&gt;, Worcester, UK.&n; * All rights reserved.&n; *&n; * LICENSE TERMS&n; *&n; * The free distribution and use of this software in both source and binary&n; * form is allowed (with or without changes) provided that:&n; *&n; *   1. distributions of this source code include the above copyright&n; *      notice, this list of conditions and the following disclaimer;&n; *&n; *   2. distributions in binary form include the above copyright&n; *      notice, this list of conditions and the following disclaimer&n; *      in the documentation and/or other associated materials;&n; *&n; *   3. the copyright holder&squot;s name is not used to endorse products&n; *      built using this software without specific written permission.&n; *&n; * ALTERNATIVELY, provided that this notice is retained in full, this product&n; * may be distributed under the terms of the GNU General Public License (GPL),&n; * in which case the provisions of the GPL apply INSTEAD OF those given above.&n; *&n; * DISCLAIMER&n; *&n; * This software is provided &squot;as is&squot; with no explicit or implied warranties&n; * in respect of its properties, including, but not limited to, correctness&n; * and/or fitness for purpose.&n; * ---------------------------------------------------------------------------&n; */
multiline_comment|/* Some changes from the Gladman version:&n;    s/RIJNDAEL(e_key)/E_KEY/g&n;    s/RIJNDAEL(d_key)/D_KEY/g&n;*/
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/crypto.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
DECL|macro|AES_MIN_KEY_SIZE
mdefine_line|#define AES_MIN_KEY_SIZE&t;16
DECL|macro|AES_MAX_KEY_SIZE
mdefine_line|#define AES_MAX_KEY_SIZE&t;32
DECL|macro|AES_BLOCK_SIZE
mdefine_line|#define AES_BLOCK_SIZE&t;&t;16
r_static
r_inline
DECL|function|generic_rotr32
id|u32
id|generic_rotr32
(paren
r_const
id|u32
id|x
comma
r_const
r_int
id|bits
)paren
(brace
r_const
r_int
id|n
op_assign
id|bits
op_mod
l_int|32
suffix:semicolon
r_return
(paren
id|x
op_rshift
id|n
)paren
op_or
(paren
id|x
op_lshift
(paren
l_int|32
op_minus
id|n
)paren
)paren
suffix:semicolon
)brace
r_static
r_inline
DECL|function|generic_rotl32
id|u32
id|generic_rotl32
(paren
r_const
id|u32
id|x
comma
r_const
r_int
id|bits
)paren
(brace
r_const
r_int
id|n
op_assign
id|bits
op_mod
l_int|32
suffix:semicolon
r_return
(paren
id|x
op_lshift
id|n
)paren
op_or
(paren
id|x
op_rshift
(paren
l_int|32
op_minus
id|n
)paren
)paren
suffix:semicolon
)brace
DECL|macro|rotl
mdefine_line|#define rotl generic_rotl32
DECL|macro|rotr
mdefine_line|#define rotr generic_rotr32
multiline_comment|/*&n; * #define byte(x, nr) ((unsigned char)((x) &gt;&gt; (nr*8))) &n; */
r_inline
r_static
id|u8
DECL|function|byte
id|byte
c_func
(paren
r_const
id|u32
id|x
comma
r_const
r_int
id|n
)paren
(brace
r_return
id|x
op_rshift
(paren
id|n
op_lshift
l_int|3
)paren
suffix:semicolon
)brace
DECL|macro|u32_in
mdefine_line|#define u32_in(x) le32_to_cpu(*(const u32 *)(x))
DECL|macro|u32_out
mdefine_line|#define u32_out(to, from) (*(u32 *)(to) = cpu_to_le32(from))
DECL|struct|aes_ctx
r_struct
id|aes_ctx
(brace
DECL|member|key_length
r_int
id|key_length
suffix:semicolon
DECL|member|E
id|u32
id|E
(braket
l_int|60
)braket
suffix:semicolon
DECL|member|D
id|u32
id|D
(braket
l_int|60
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|E_KEY
mdefine_line|#define E_KEY ctx-&gt;E
DECL|macro|D_KEY
mdefine_line|#define D_KEY ctx-&gt;D
DECL|variable|pow_tab
r_static
id|u8
id|pow_tab
(braket
l_int|256
)braket
suffix:semicolon
DECL|variable|log_tab
r_static
id|u8
id|log_tab
(braket
l_int|256
)braket
suffix:semicolon
DECL|variable|sbx_tab
r_static
id|u8
id|sbx_tab
(braket
l_int|256
)braket
suffix:semicolon
DECL|variable|isb_tab
r_static
id|u8
id|isb_tab
(braket
l_int|256
)braket
suffix:semicolon
DECL|variable|rco_tab
r_static
id|u32
id|rco_tab
(braket
l_int|10
)braket
suffix:semicolon
DECL|variable|ft_tab
r_static
id|u32
id|ft_tab
(braket
l_int|4
)braket
(braket
l_int|256
)braket
suffix:semicolon
DECL|variable|it_tab
r_static
id|u32
id|it_tab
(braket
l_int|4
)braket
(braket
l_int|256
)braket
suffix:semicolon
DECL|variable|fl_tab
r_static
id|u32
id|fl_tab
(braket
l_int|4
)braket
(braket
l_int|256
)braket
suffix:semicolon
DECL|variable|il_tab
r_static
id|u32
id|il_tab
(braket
l_int|4
)braket
(braket
l_int|256
)braket
suffix:semicolon
r_static
r_inline
id|u8
DECL|function|f_mult
id|f_mult
(paren
id|u8
id|a
comma
id|u8
id|b
)paren
(brace
id|u8
id|aa
op_assign
id|log_tab
(braket
id|a
)braket
comma
id|cc
op_assign
id|aa
op_plus
id|log_tab
(braket
id|b
)braket
suffix:semicolon
r_return
id|pow_tab
(braket
id|cc
op_plus
(paren
id|cc
OL
id|aa
ques
c_cond
l_int|1
suffix:colon
l_int|0
)paren
)braket
suffix:semicolon
)brace
DECL|macro|ff_mult
mdefine_line|#define ff_mult(a,b)    (a &amp;&amp; b ? f_mult(a, b) : 0)
DECL|macro|f_rn
mdefine_line|#define f_rn(bo, bi, n, k)&t;&t;&t;&t;&t;&bslash;&n;    bo[n] =  ft_tab[0][byte(bi[n],0)] ^&t;&t;&t;&t;&bslash;&n;             ft_tab[1][byte(bi[(n + 1) &amp; 3],1)] ^&t;&t;&bslash;&n;             ft_tab[2][byte(bi[(n + 2) &amp; 3],2)] ^&t;&t;&bslash;&n;             ft_tab[3][byte(bi[(n + 3) &amp; 3],3)] ^ *(k + n)
DECL|macro|i_rn
mdefine_line|#define i_rn(bo, bi, n, k)&t;&t;&t;&t;&t;&bslash;&n;    bo[n] =  it_tab[0][byte(bi[n],0)] ^&t;&t;&t;&t;&bslash;&n;             it_tab[1][byte(bi[(n + 3) &amp; 3],1)] ^&t;&t;&bslash;&n;             it_tab[2][byte(bi[(n + 2) &amp; 3],2)] ^&t;&t;&bslash;&n;             it_tab[3][byte(bi[(n + 1) &amp; 3],3)] ^ *(k + n)
DECL|macro|ls_box
mdefine_line|#define ls_box(x)&t;&t;&t;&t;&bslash;&n;    ( fl_tab[0][byte(x, 0)] ^&t;&t;&t;&bslash;&n;      fl_tab[1][byte(x, 1)] ^&t;&t;&t;&bslash;&n;      fl_tab[2][byte(x, 2)] ^&t;&t;&t;&bslash;&n;      fl_tab[3][byte(x, 3)] )
DECL|macro|f_rl
mdefine_line|#define f_rl(bo, bi, n, k)&t;&t;&t;&t;&t;&bslash;&n;    bo[n] =  fl_tab[0][byte(bi[n],0)] ^&t;&t;&t;&t;&bslash;&n;             fl_tab[1][byte(bi[(n + 1) &amp; 3],1)] ^&t;&t;&bslash;&n;             fl_tab[2][byte(bi[(n + 2) &amp; 3],2)] ^&t;&t;&bslash;&n;             fl_tab[3][byte(bi[(n + 3) &amp; 3],3)] ^ *(k + n)
DECL|macro|i_rl
mdefine_line|#define i_rl(bo, bi, n, k)&t;&t;&t;&t;&t;&bslash;&n;    bo[n] =  il_tab[0][byte(bi[n],0)] ^&t;&t;&t;&t;&bslash;&n;             il_tab[1][byte(bi[(n + 3) &amp; 3],1)] ^&t;&t;&bslash;&n;             il_tab[2][byte(bi[(n + 2) &amp; 3],2)] ^&t;&t;&bslash;&n;             il_tab[3][byte(bi[(n + 1) &amp; 3],3)] ^ *(k + n)
r_static
r_void
DECL|function|gen_tabs
id|gen_tabs
(paren
r_void
)paren
(brace
id|u32
id|i
comma
id|t
suffix:semicolon
id|u8
id|p
comma
id|q
suffix:semicolon
multiline_comment|/* log and power tables for GF(2**8) finite field with&n;&t;   0x011b as modular polynomial - the simplest primitive&n;&t;   root is 0x03, used here to generate the tables */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
comma
id|p
op_assign
l_int|1
suffix:semicolon
id|i
OL
l_int|256
suffix:semicolon
op_increment
id|i
)paren
(brace
id|pow_tab
(braket
id|i
)braket
op_assign
(paren
id|u8
)paren
id|p
suffix:semicolon
id|log_tab
(braket
id|p
)braket
op_assign
(paren
id|u8
)paren
id|i
suffix:semicolon
id|p
op_xor_assign
(paren
id|p
op_lshift
l_int|1
)paren
op_xor
(paren
id|p
op_amp
l_int|0x80
ques
c_cond
l_int|0x01b
suffix:colon
l_int|0
)paren
suffix:semicolon
)brace
id|log_tab
(braket
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
comma
id|p
op_assign
l_int|1
suffix:semicolon
id|i
OL
l_int|10
suffix:semicolon
op_increment
id|i
)paren
(brace
id|rco_tab
(braket
id|i
)braket
op_assign
id|p
suffix:semicolon
id|p
op_assign
(paren
id|p
op_lshift
l_int|1
)paren
op_xor
(paren
id|p
op_amp
l_int|0x80
ques
c_cond
l_int|0x01b
suffix:colon
l_int|0
)paren
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|256
suffix:semicolon
op_increment
id|i
)paren
(brace
id|p
op_assign
(paren
id|i
ques
c_cond
id|pow_tab
(braket
l_int|255
op_minus
id|log_tab
(braket
id|i
)braket
)braket
suffix:colon
l_int|0
)paren
suffix:semicolon
id|q
op_assign
(paren
(paren
id|p
op_rshift
l_int|7
)paren
op_or
(paren
id|p
op_lshift
l_int|1
)paren
)paren
op_xor
(paren
(paren
id|p
op_rshift
l_int|6
)paren
op_or
(paren
id|p
op_lshift
l_int|2
)paren
)paren
suffix:semicolon
id|p
op_xor_assign
l_int|0x63
op_xor
id|q
op_xor
(paren
(paren
id|q
op_rshift
l_int|6
)paren
op_or
(paren
id|q
op_lshift
l_int|2
)paren
)paren
suffix:semicolon
id|sbx_tab
(braket
id|i
)braket
op_assign
id|p
suffix:semicolon
id|isb_tab
(braket
id|p
)braket
op_assign
(paren
id|u8
)paren
id|i
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|256
suffix:semicolon
op_increment
id|i
)paren
(brace
id|p
op_assign
id|sbx_tab
(braket
id|i
)braket
suffix:semicolon
id|t
op_assign
id|p
suffix:semicolon
id|fl_tab
(braket
l_int|0
)braket
(braket
id|i
)braket
op_assign
id|t
suffix:semicolon
id|fl_tab
(braket
l_int|1
)braket
(braket
id|i
)braket
op_assign
id|rotl
(paren
id|t
comma
l_int|8
)paren
suffix:semicolon
id|fl_tab
(braket
l_int|2
)braket
(braket
id|i
)braket
op_assign
id|rotl
(paren
id|t
comma
l_int|16
)paren
suffix:semicolon
id|fl_tab
(braket
l_int|3
)braket
(braket
id|i
)braket
op_assign
id|rotl
(paren
id|t
comma
l_int|24
)paren
suffix:semicolon
id|t
op_assign
(paren
(paren
id|u32
)paren
id|ff_mult
(paren
l_int|2
comma
id|p
)paren
)paren
op_or
(paren
(paren
id|u32
)paren
id|p
op_lshift
l_int|8
)paren
op_or
(paren
(paren
id|u32
)paren
id|p
op_lshift
l_int|16
)paren
op_or
(paren
(paren
id|u32
)paren
id|ff_mult
(paren
l_int|3
comma
id|p
)paren
op_lshift
l_int|24
)paren
suffix:semicolon
id|ft_tab
(braket
l_int|0
)braket
(braket
id|i
)braket
op_assign
id|t
suffix:semicolon
id|ft_tab
(braket
l_int|1
)braket
(braket
id|i
)braket
op_assign
id|rotl
(paren
id|t
comma
l_int|8
)paren
suffix:semicolon
id|ft_tab
(braket
l_int|2
)braket
(braket
id|i
)braket
op_assign
id|rotl
(paren
id|t
comma
l_int|16
)paren
suffix:semicolon
id|ft_tab
(braket
l_int|3
)braket
(braket
id|i
)braket
op_assign
id|rotl
(paren
id|t
comma
l_int|24
)paren
suffix:semicolon
id|p
op_assign
id|isb_tab
(braket
id|i
)braket
suffix:semicolon
id|t
op_assign
id|p
suffix:semicolon
id|il_tab
(braket
l_int|0
)braket
(braket
id|i
)braket
op_assign
id|t
suffix:semicolon
id|il_tab
(braket
l_int|1
)braket
(braket
id|i
)braket
op_assign
id|rotl
(paren
id|t
comma
l_int|8
)paren
suffix:semicolon
id|il_tab
(braket
l_int|2
)braket
(braket
id|i
)braket
op_assign
id|rotl
(paren
id|t
comma
l_int|16
)paren
suffix:semicolon
id|il_tab
(braket
l_int|3
)braket
(braket
id|i
)braket
op_assign
id|rotl
(paren
id|t
comma
l_int|24
)paren
suffix:semicolon
id|t
op_assign
(paren
(paren
id|u32
)paren
id|ff_mult
(paren
l_int|14
comma
id|p
)paren
)paren
op_or
(paren
(paren
id|u32
)paren
id|ff_mult
(paren
l_int|9
comma
id|p
)paren
op_lshift
l_int|8
)paren
op_or
(paren
(paren
id|u32
)paren
id|ff_mult
(paren
l_int|13
comma
id|p
)paren
op_lshift
l_int|16
)paren
op_or
(paren
(paren
id|u32
)paren
id|ff_mult
(paren
l_int|11
comma
id|p
)paren
op_lshift
l_int|24
)paren
suffix:semicolon
id|it_tab
(braket
l_int|0
)braket
(braket
id|i
)braket
op_assign
id|t
suffix:semicolon
id|it_tab
(braket
l_int|1
)braket
(braket
id|i
)braket
op_assign
id|rotl
(paren
id|t
comma
l_int|8
)paren
suffix:semicolon
id|it_tab
(braket
l_int|2
)braket
(braket
id|i
)braket
op_assign
id|rotl
(paren
id|t
comma
l_int|16
)paren
suffix:semicolon
id|it_tab
(braket
l_int|3
)braket
(braket
id|i
)braket
op_assign
id|rotl
(paren
id|t
comma
l_int|24
)paren
suffix:semicolon
)brace
)brace
DECL|macro|star_x
mdefine_line|#define star_x(x) (((x) &amp; 0x7f7f7f7f) &lt;&lt; 1) ^ ((((x) &amp; 0x80808080) &gt;&gt; 7) * 0x1b)
DECL|macro|imix_col
mdefine_line|#define imix_col(y,x)       &bslash;&n;    u   = star_x(x);        &bslash;&n;    v   = star_x(u);        &bslash;&n;    w   = star_x(v);        &bslash;&n;    t   = w ^ (x);          &bslash;&n;   (y)  = u ^ v ^ w;        &bslash;&n;   (y) ^= rotr(u ^ t,  8) ^ &bslash;&n;          rotr(v ^ t, 16) ^ &bslash;&n;          rotr(t,24)
multiline_comment|/* initialise the key schedule from the user supplied key */
DECL|macro|loop4
mdefine_line|#define loop4(i)                                    &bslash;&n;{   t = rotr(t,  8); t = ls_box(t) ^ rco_tab[i];    &bslash;&n;    t ^= E_KEY[4 * i];     E_KEY[4 * i + 4] = t;    &bslash;&n;    t ^= E_KEY[4 * i + 1]; E_KEY[4 * i + 5] = t;    &bslash;&n;    t ^= E_KEY[4 * i + 2]; E_KEY[4 * i + 6] = t;    &bslash;&n;    t ^= E_KEY[4 * i + 3]; E_KEY[4 * i + 7] = t;    &bslash;&n;}
DECL|macro|loop6
mdefine_line|#define loop6(i)                                    &bslash;&n;{   t = rotr(t,  8); t = ls_box(t) ^ rco_tab[i];    &bslash;&n;    t ^= E_KEY[6 * i];     E_KEY[6 * i + 6] = t;    &bslash;&n;    t ^= E_KEY[6 * i + 1]; E_KEY[6 * i + 7] = t;    &bslash;&n;    t ^= E_KEY[6 * i + 2]; E_KEY[6 * i + 8] = t;    &bslash;&n;    t ^= E_KEY[6 * i + 3]; E_KEY[6 * i + 9] = t;    &bslash;&n;    t ^= E_KEY[6 * i + 4]; E_KEY[6 * i + 10] = t;   &bslash;&n;    t ^= E_KEY[6 * i + 5]; E_KEY[6 * i + 11] = t;   &bslash;&n;}
DECL|macro|loop8
mdefine_line|#define loop8(i)                                    &bslash;&n;{   t = rotr(t,  8); ; t = ls_box(t) ^ rco_tab[i];  &bslash;&n;    t ^= E_KEY[8 * i];     E_KEY[8 * i + 8] = t;    &bslash;&n;    t ^= E_KEY[8 * i + 1]; E_KEY[8 * i + 9] = t;    &bslash;&n;    t ^= E_KEY[8 * i + 2]; E_KEY[8 * i + 10] = t;   &bslash;&n;    t ^= E_KEY[8 * i + 3]; E_KEY[8 * i + 11] = t;   &bslash;&n;    t  = E_KEY[8 * i + 4] ^ ls_box(t);    &bslash;&n;    E_KEY[8 * i + 12] = t;                &bslash;&n;    t ^= E_KEY[8 * i + 5]; E_KEY[8 * i + 13] = t;   &bslash;&n;    t ^= E_KEY[8 * i + 6]; E_KEY[8 * i + 14] = t;   &bslash;&n;    t ^= E_KEY[8 * i + 7]; E_KEY[8 * i + 15] = t;   &bslash;&n;}
r_static
r_int
DECL|function|aes_set_key
id|aes_set_key
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
id|aes_ctx
op_star
id|ctx
op_assign
id|ctx_arg
suffix:semicolon
id|u32
id|i
comma
id|t
comma
id|u
comma
id|v
comma
id|w
suffix:semicolon
r_if
c_cond
(paren
id|key_len
op_ne
l_int|16
op_logical_and
id|key_len
op_ne
l_int|24
op_logical_and
id|key_len
op_ne
l_int|32
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
id|ctx-&gt;key_length
op_assign
id|key_len
suffix:semicolon
id|E_KEY
(braket
l_int|0
)braket
op_assign
id|u32_in
(paren
id|in_key
)paren
suffix:semicolon
id|E_KEY
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
id|E_KEY
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
id|E_KEY
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
r_switch
c_cond
(paren
id|key_len
)paren
(brace
r_case
l_int|16
suffix:colon
id|t
op_assign
id|E_KEY
(braket
l_int|3
)braket
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|10
suffix:semicolon
op_increment
id|i
)paren
id|loop4
(paren
id|i
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|24
suffix:colon
id|E_KEY
(braket
l_int|4
)braket
op_assign
id|u32_in
(paren
id|in_key
op_plus
l_int|16
)paren
suffix:semicolon
id|t
op_assign
id|E_KEY
(braket
l_int|5
)braket
op_assign
id|u32_in
(paren
id|in_key
op_plus
l_int|20
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|8
suffix:semicolon
op_increment
id|i
)paren
id|loop6
(paren
id|i
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|32
suffix:colon
id|E_KEY
(braket
l_int|4
)braket
op_assign
id|u32_in
(paren
id|in_key
op_plus
l_int|16
)paren
suffix:semicolon
id|E_KEY
(braket
l_int|5
)braket
op_assign
id|u32_in
(paren
id|in_key
op_plus
l_int|20
)paren
suffix:semicolon
id|E_KEY
(braket
l_int|6
)braket
op_assign
id|u32_in
(paren
id|in_key
op_plus
l_int|24
)paren
suffix:semicolon
id|t
op_assign
id|E_KEY
(braket
l_int|7
)braket
op_assign
id|u32_in
(paren
id|in_key
op_plus
l_int|28
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|7
suffix:semicolon
op_increment
id|i
)paren
id|loop8
(paren
id|i
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|D_KEY
(braket
l_int|0
)braket
op_assign
id|E_KEY
(braket
l_int|0
)braket
suffix:semicolon
id|D_KEY
(braket
l_int|1
)braket
op_assign
id|E_KEY
(braket
l_int|1
)braket
suffix:semicolon
id|D_KEY
(braket
l_int|2
)braket
op_assign
id|E_KEY
(braket
l_int|2
)braket
suffix:semicolon
id|D_KEY
(braket
l_int|3
)braket
op_assign
id|E_KEY
(braket
l_int|3
)braket
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|4
suffix:semicolon
id|i
OL
id|key_len
op_plus
l_int|24
suffix:semicolon
op_increment
id|i
)paren
(brace
id|imix_col
(paren
id|D_KEY
(braket
id|i
)braket
comma
id|E_KEY
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* encrypt a block of text */
DECL|macro|f_nround
mdefine_line|#define f_nround(bo, bi, k) &bslash;&n;    f_rn(bo, bi, 0, k);     &bslash;&n;    f_rn(bo, bi, 1, k);     &bslash;&n;    f_rn(bo, bi, 2, k);     &bslash;&n;    f_rn(bo, bi, 3, k);     &bslash;&n;    k += 4
DECL|macro|f_lround
mdefine_line|#define f_lround(bo, bi, k) &bslash;&n;    f_rl(bo, bi, 0, k);     &bslash;&n;    f_rl(bo, bi, 1, k);     &bslash;&n;    f_rl(bo, bi, 2, k);     &bslash;&n;    f_rl(bo, bi, 3, k)
DECL|function|aes_encrypt
r_static
r_void
id|aes_encrypt
c_func
(paren
r_void
op_star
id|ctx_arg
comma
id|u8
op_star
id|out
comma
r_const
id|u8
op_star
id|in
)paren
(brace
r_const
r_struct
id|aes_ctx
op_star
id|ctx
op_assign
id|ctx_arg
suffix:semicolon
id|u32
id|b0
(braket
l_int|4
)braket
comma
id|b1
(braket
l_int|4
)braket
suffix:semicolon
r_const
id|u32
op_star
id|kp
op_assign
id|E_KEY
op_plus
l_int|4
suffix:semicolon
id|b0
(braket
l_int|0
)braket
op_assign
id|u32_in
(paren
id|in
)paren
op_xor
id|E_KEY
(braket
l_int|0
)braket
suffix:semicolon
id|b0
(braket
l_int|1
)braket
op_assign
id|u32_in
(paren
id|in
op_plus
l_int|4
)paren
op_xor
id|E_KEY
(braket
l_int|1
)braket
suffix:semicolon
id|b0
(braket
l_int|2
)braket
op_assign
id|u32_in
(paren
id|in
op_plus
l_int|8
)paren
op_xor
id|E_KEY
(braket
l_int|2
)braket
suffix:semicolon
id|b0
(braket
l_int|3
)braket
op_assign
id|u32_in
(paren
id|in
op_plus
l_int|12
)paren
op_xor
id|E_KEY
(braket
l_int|3
)braket
suffix:semicolon
r_if
c_cond
(paren
id|ctx-&gt;key_length
OG
l_int|24
)paren
(brace
id|f_nround
(paren
id|b1
comma
id|b0
comma
id|kp
)paren
suffix:semicolon
id|f_nround
(paren
id|b0
comma
id|b1
comma
id|kp
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ctx-&gt;key_length
OG
l_int|16
)paren
(brace
id|f_nround
(paren
id|b1
comma
id|b0
comma
id|kp
)paren
suffix:semicolon
id|f_nround
(paren
id|b0
comma
id|b1
comma
id|kp
)paren
suffix:semicolon
)brace
id|f_nround
(paren
id|b1
comma
id|b0
comma
id|kp
)paren
suffix:semicolon
id|f_nround
(paren
id|b0
comma
id|b1
comma
id|kp
)paren
suffix:semicolon
id|f_nround
(paren
id|b1
comma
id|b0
comma
id|kp
)paren
suffix:semicolon
id|f_nround
(paren
id|b0
comma
id|b1
comma
id|kp
)paren
suffix:semicolon
id|f_nround
(paren
id|b1
comma
id|b0
comma
id|kp
)paren
suffix:semicolon
id|f_nround
(paren
id|b0
comma
id|b1
comma
id|kp
)paren
suffix:semicolon
id|f_nround
(paren
id|b1
comma
id|b0
comma
id|kp
)paren
suffix:semicolon
id|f_nround
(paren
id|b0
comma
id|b1
comma
id|kp
)paren
suffix:semicolon
id|f_nround
(paren
id|b1
comma
id|b0
comma
id|kp
)paren
suffix:semicolon
id|f_lround
(paren
id|b0
comma
id|b1
comma
id|kp
)paren
suffix:semicolon
id|u32_out
(paren
id|out
comma
id|b0
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|u32_out
(paren
id|out
op_plus
l_int|4
comma
id|b0
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|u32_out
(paren
id|out
op_plus
l_int|8
comma
id|b0
(braket
l_int|2
)braket
)paren
suffix:semicolon
id|u32_out
(paren
id|out
op_plus
l_int|12
comma
id|b0
(braket
l_int|3
)braket
)paren
suffix:semicolon
)brace
multiline_comment|/* decrypt a block of text */
DECL|macro|i_nround
mdefine_line|#define i_nround(bo, bi, k) &bslash;&n;    i_rn(bo, bi, 0, k);     &bslash;&n;    i_rn(bo, bi, 1, k);     &bslash;&n;    i_rn(bo, bi, 2, k);     &bslash;&n;    i_rn(bo, bi, 3, k);     &bslash;&n;    k -= 4
DECL|macro|i_lround
mdefine_line|#define i_lround(bo, bi, k) &bslash;&n;    i_rl(bo, bi, 0, k);     &bslash;&n;    i_rl(bo, bi, 1, k);     &bslash;&n;    i_rl(bo, bi, 2, k);     &bslash;&n;    i_rl(bo, bi, 3, k)
DECL|function|aes_decrypt
r_static
r_void
id|aes_decrypt
c_func
(paren
r_void
op_star
id|ctx_arg
comma
id|u8
op_star
id|out
comma
r_const
id|u8
op_star
id|in
)paren
(brace
r_const
r_struct
id|aes_ctx
op_star
id|ctx
op_assign
id|ctx_arg
suffix:semicolon
id|u32
id|b0
(braket
l_int|4
)braket
comma
id|b1
(braket
l_int|4
)braket
suffix:semicolon
r_const
r_int
id|key_len
op_assign
id|ctx-&gt;key_length
suffix:semicolon
r_const
id|u32
op_star
id|kp
op_assign
id|D_KEY
op_plus
id|key_len
op_plus
l_int|20
suffix:semicolon
id|b0
(braket
l_int|0
)braket
op_assign
id|u32_in
(paren
id|in
)paren
op_xor
id|E_KEY
(braket
id|key_len
op_plus
l_int|24
)braket
suffix:semicolon
id|b0
(braket
l_int|1
)braket
op_assign
id|u32_in
(paren
id|in
op_plus
l_int|4
)paren
op_xor
id|E_KEY
(braket
id|key_len
op_plus
l_int|25
)braket
suffix:semicolon
id|b0
(braket
l_int|2
)braket
op_assign
id|u32_in
(paren
id|in
op_plus
l_int|8
)paren
op_xor
id|E_KEY
(braket
id|key_len
op_plus
l_int|26
)braket
suffix:semicolon
id|b0
(braket
l_int|3
)braket
op_assign
id|u32_in
(paren
id|in
op_plus
l_int|12
)paren
op_xor
id|E_KEY
(braket
id|key_len
op_plus
l_int|27
)braket
suffix:semicolon
r_if
c_cond
(paren
id|key_len
OG
l_int|24
)paren
(brace
id|i_nround
(paren
id|b1
comma
id|b0
comma
id|kp
)paren
suffix:semicolon
id|i_nround
(paren
id|b0
comma
id|b1
comma
id|kp
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|key_len
OG
l_int|16
)paren
(brace
id|i_nround
(paren
id|b1
comma
id|b0
comma
id|kp
)paren
suffix:semicolon
id|i_nround
(paren
id|b0
comma
id|b1
comma
id|kp
)paren
suffix:semicolon
)brace
id|i_nround
(paren
id|b1
comma
id|b0
comma
id|kp
)paren
suffix:semicolon
id|i_nround
(paren
id|b0
comma
id|b1
comma
id|kp
)paren
suffix:semicolon
id|i_nround
(paren
id|b1
comma
id|b0
comma
id|kp
)paren
suffix:semicolon
id|i_nround
(paren
id|b0
comma
id|b1
comma
id|kp
)paren
suffix:semicolon
id|i_nround
(paren
id|b1
comma
id|b0
comma
id|kp
)paren
suffix:semicolon
id|i_nround
(paren
id|b0
comma
id|b1
comma
id|kp
)paren
suffix:semicolon
id|i_nround
(paren
id|b1
comma
id|b0
comma
id|kp
)paren
suffix:semicolon
id|i_nround
(paren
id|b0
comma
id|b1
comma
id|kp
)paren
suffix:semicolon
id|i_nround
(paren
id|b1
comma
id|b0
comma
id|kp
)paren
suffix:semicolon
id|i_lround
(paren
id|b0
comma
id|b1
comma
id|kp
)paren
suffix:semicolon
id|u32_out
(paren
id|out
comma
id|b0
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|u32_out
(paren
id|out
op_plus
l_int|4
comma
id|b0
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|u32_out
(paren
id|out
op_plus
l_int|8
comma
id|b0
(braket
l_int|2
)braket
)paren
suffix:semicolon
id|u32_out
(paren
id|out
op_plus
l_int|12
comma
id|b0
(braket
l_int|3
)braket
)paren
suffix:semicolon
)brace
DECL|variable|aes_alg
r_static
r_struct
id|crypto_alg
id|aes_alg
op_assign
(brace
dot
id|cra_name
op_assign
l_string|&quot;aes&quot;
comma
dot
id|cra_flags
op_assign
id|CRYPTO_ALG_TYPE_CIPHER
comma
dot
id|cra_blocksize
op_assign
id|AES_BLOCK_SIZE
comma
dot
id|cra_ctxsize
op_assign
r_sizeof
(paren
r_struct
id|aes_ctx
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
id|aes_alg.cra_list
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
id|AES_MIN_KEY_SIZE
comma
dot
id|cia_max_keysize
op_assign
id|AES_MAX_KEY_SIZE
comma
dot
id|cia_setkey
op_assign
id|aes_set_key
comma
dot
id|cia_encrypt
op_assign
id|aes_encrypt
comma
dot
id|cia_decrypt
op_assign
id|aes_decrypt
)brace
)brace
)brace
suffix:semicolon
DECL|function|aes_init
r_static
r_int
id|__init
id|aes_init
c_func
(paren
r_void
)paren
(brace
id|gen_tabs
c_func
(paren
)paren
suffix:semicolon
r_return
id|crypto_register_alg
c_func
(paren
op_amp
id|aes_alg
)paren
suffix:semicolon
)brace
DECL|function|aes_fini
r_static
r_void
id|__exit
id|aes_fini
c_func
(paren
r_void
)paren
(brace
id|crypto_unregister_alg
c_func
(paren
op_amp
id|aes_alg
)paren
suffix:semicolon
)brace
DECL|variable|aes_init
id|module_init
c_func
(paren
id|aes_init
)paren
suffix:semicolon
DECL|variable|aes_fini
id|module_exit
c_func
(paren
id|aes_fini
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Rijndael (AES) Cipher Algorithm&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;Dual BSD/GPL&quot;
)paren
suffix:semicolon
eof
