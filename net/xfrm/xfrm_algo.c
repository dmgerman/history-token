multiline_comment|/* &n; * xfrm algorithm interface&n; *&n; * Copyright (c) 2002 James Morris &lt;jmorris@intercode.com.au&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License as published by the Free&n; * Software Foundation; either version 2 of the License, or (at your option) &n; * any later version.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/pfkeyv2.h&gt;
macro_line|#include &lt;net/xfrm.h&gt;
macro_line|#if defined(CONFIG_INET_AH) || defined(CONFIG_INET_AH_MODULE) || defined(CONFIG_INET6_AH) || defined(CONFIG_INET6_AH_MODULE)
macro_line|#include &lt;net/ah.h&gt;
macro_line|#endif
macro_line|#if defined(CONFIG_INET_ESP) || defined(CONFIG_INET_ESP_MODULE) || defined(CONFIG_INET6_ESP) || defined(CONFIG_INET6_ESP_MODULE)
macro_line|#include &lt;net/esp.h&gt;
macro_line|#endif
macro_line|#include &lt;asm/scatterlist.h&gt;
multiline_comment|/*&n; * Algorithms supported by IPsec.  These entries contain properties which&n; * are used in key negotiation and xfrm processing, and are used to verify&n; * that instantiated crypto transforms have correct parameters for IPsec&n; * purposes.&n; */
DECL|variable|aalg_list
r_static
r_struct
id|xfrm_algo_desc
id|aalg_list
(braket
)braket
op_assign
(brace
(brace
dot
id|name
op_assign
l_string|&quot;digest_null&quot;
comma
dot
id|uinfo
op_assign
(brace
dot
id|auth
op_assign
(brace
dot
id|icv_truncbits
op_assign
l_int|0
comma
dot
id|icv_fullbits
op_assign
l_int|0
comma
)brace
)brace
comma
dot
id|desc
op_assign
(brace
dot
id|sadb_alg_id
op_assign
id|SADB_X_AALG_NULL
comma
dot
id|sadb_alg_ivlen
op_assign
l_int|0
comma
dot
id|sadb_alg_minbits
op_assign
l_int|0
comma
dot
id|sadb_alg_maxbits
op_assign
l_int|0
)brace
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;md5&quot;
comma
dot
id|uinfo
op_assign
(brace
dot
id|auth
op_assign
(brace
dot
id|icv_truncbits
op_assign
l_int|96
comma
dot
id|icv_fullbits
op_assign
l_int|128
comma
)brace
)brace
comma
dot
id|desc
op_assign
(brace
dot
id|sadb_alg_id
op_assign
id|SADB_AALG_MD5HMAC
comma
dot
id|sadb_alg_ivlen
op_assign
l_int|0
comma
dot
id|sadb_alg_minbits
op_assign
l_int|128
comma
dot
id|sadb_alg_maxbits
op_assign
l_int|128
)brace
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;sha1&quot;
comma
dot
id|uinfo
op_assign
(brace
dot
id|auth
op_assign
(brace
dot
id|icv_truncbits
op_assign
l_int|96
comma
dot
id|icv_fullbits
op_assign
l_int|160
comma
)brace
)brace
comma
dot
id|desc
op_assign
(brace
dot
id|sadb_alg_id
op_assign
id|SADB_AALG_SHA1HMAC
comma
dot
id|sadb_alg_ivlen
op_assign
l_int|0
comma
dot
id|sadb_alg_minbits
op_assign
l_int|160
comma
dot
id|sadb_alg_maxbits
op_assign
l_int|160
)brace
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;sha256&quot;
comma
dot
id|uinfo
op_assign
(brace
dot
id|auth
op_assign
(brace
dot
id|icv_truncbits
op_assign
l_int|128
comma
dot
id|icv_fullbits
op_assign
l_int|256
comma
)brace
)brace
comma
dot
id|desc
op_assign
(brace
dot
id|sadb_alg_id
op_assign
id|SADB_X_AALG_SHA2_256HMAC
comma
dot
id|sadb_alg_ivlen
op_assign
l_int|0
comma
dot
id|sadb_alg_minbits
op_assign
l_int|256
comma
dot
id|sadb_alg_maxbits
op_assign
l_int|256
)brace
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;ripemd160&quot;
comma
dot
id|uinfo
op_assign
(brace
dot
id|auth
op_assign
(brace
dot
id|icv_truncbits
op_assign
l_int|96
comma
dot
id|icv_fullbits
op_assign
l_int|160
comma
)brace
)brace
comma
dot
id|desc
op_assign
(brace
dot
id|sadb_alg_id
op_assign
id|SADB_X_AALG_RIPEMD160HMAC
comma
dot
id|sadb_alg_ivlen
op_assign
l_int|0
comma
dot
id|sadb_alg_minbits
op_assign
l_int|160
comma
dot
id|sadb_alg_maxbits
op_assign
l_int|160
)brace
)brace
comma
)brace
suffix:semicolon
DECL|variable|ealg_list
r_static
r_struct
id|xfrm_algo_desc
id|ealg_list
(braket
)braket
op_assign
(brace
(brace
dot
id|name
op_assign
l_string|&quot;cipher_null&quot;
comma
dot
id|uinfo
op_assign
(brace
dot
id|encr
op_assign
(brace
dot
id|blockbits
op_assign
l_int|8
comma
dot
id|defkeybits
op_assign
l_int|0
comma
)brace
)brace
comma
dot
id|desc
op_assign
(brace
dot
id|sadb_alg_id
op_assign
id|SADB_EALG_NULL
comma
dot
id|sadb_alg_ivlen
op_assign
l_int|0
comma
dot
id|sadb_alg_minbits
op_assign
l_int|0
comma
dot
id|sadb_alg_maxbits
op_assign
l_int|0
)brace
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;des&quot;
comma
dot
id|uinfo
op_assign
(brace
dot
id|encr
op_assign
(brace
dot
id|blockbits
op_assign
l_int|64
comma
dot
id|defkeybits
op_assign
l_int|64
comma
)brace
)brace
comma
dot
id|desc
op_assign
(brace
dot
id|sadb_alg_id
op_assign
id|SADB_EALG_DESCBC
comma
dot
id|sadb_alg_ivlen
op_assign
l_int|8
comma
dot
id|sadb_alg_minbits
op_assign
l_int|64
comma
dot
id|sadb_alg_maxbits
op_assign
l_int|64
)brace
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;des3_ede&quot;
comma
dot
id|uinfo
op_assign
(brace
dot
id|encr
op_assign
(brace
dot
id|blockbits
op_assign
l_int|64
comma
dot
id|defkeybits
op_assign
l_int|192
comma
)brace
)brace
comma
dot
id|desc
op_assign
(brace
dot
id|sadb_alg_id
op_assign
id|SADB_EALG_3DESCBC
comma
dot
id|sadb_alg_ivlen
op_assign
l_int|8
comma
dot
id|sadb_alg_minbits
op_assign
l_int|192
comma
dot
id|sadb_alg_maxbits
op_assign
l_int|192
)brace
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;cast128&quot;
comma
dot
id|uinfo
op_assign
(brace
dot
id|encr
op_assign
(brace
dot
id|blockbits
op_assign
l_int|64
comma
dot
id|defkeybits
op_assign
l_int|128
comma
)brace
)brace
comma
dot
id|desc
op_assign
(brace
dot
id|sadb_alg_id
op_assign
id|SADB_X_EALG_CASTCBC
comma
dot
id|sadb_alg_ivlen
op_assign
l_int|8
comma
dot
id|sadb_alg_minbits
op_assign
l_int|40
comma
dot
id|sadb_alg_maxbits
op_assign
l_int|128
)brace
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;blowfish&quot;
comma
dot
id|uinfo
op_assign
(brace
dot
id|encr
op_assign
(brace
dot
id|blockbits
op_assign
l_int|64
comma
dot
id|defkeybits
op_assign
l_int|128
comma
)brace
)brace
comma
dot
id|desc
op_assign
(brace
dot
id|sadb_alg_id
op_assign
id|SADB_X_EALG_BLOWFISHCBC
comma
dot
id|sadb_alg_ivlen
op_assign
l_int|8
comma
dot
id|sadb_alg_minbits
op_assign
l_int|40
comma
dot
id|sadb_alg_maxbits
op_assign
l_int|448
)brace
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;aes&quot;
comma
dot
id|uinfo
op_assign
(brace
dot
id|encr
op_assign
(brace
dot
id|blockbits
op_assign
l_int|128
comma
dot
id|defkeybits
op_assign
l_int|128
comma
)brace
)brace
comma
dot
id|desc
op_assign
(brace
dot
id|sadb_alg_id
op_assign
id|SADB_X_EALG_AESCBC
comma
dot
id|sadb_alg_ivlen
op_assign
l_int|8
comma
dot
id|sadb_alg_minbits
op_assign
l_int|128
comma
dot
id|sadb_alg_maxbits
op_assign
l_int|256
)brace
)brace
comma
)brace
suffix:semicolon
DECL|variable|calg_list
r_static
r_struct
id|xfrm_algo_desc
id|calg_list
(braket
)braket
op_assign
(brace
(brace
dot
id|name
op_assign
l_string|&quot;deflate&quot;
comma
dot
id|uinfo
op_assign
(brace
dot
id|comp
op_assign
(brace
dot
id|threshold
op_assign
l_int|90
comma
)brace
)brace
comma
dot
id|desc
op_assign
(brace
dot
id|sadb_alg_id
op_assign
id|SADB_X_CALG_DEFLATE
)brace
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;lzs&quot;
comma
dot
id|uinfo
op_assign
(brace
dot
id|comp
op_assign
(brace
dot
id|threshold
op_assign
l_int|90
comma
)brace
)brace
comma
dot
id|desc
op_assign
(brace
dot
id|sadb_alg_id
op_assign
id|SADB_X_CALG_LZS
)brace
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;lzjh&quot;
comma
dot
id|uinfo
op_assign
(brace
dot
id|comp
op_assign
(brace
dot
id|threshold
op_assign
l_int|50
comma
)brace
)brace
comma
dot
id|desc
op_assign
(brace
dot
id|sadb_alg_id
op_assign
id|SADB_X_CALG_LZJH
)brace
)brace
comma
)brace
suffix:semicolon
DECL|function|aalg_entries
r_static
r_inline
r_int
id|aalg_entries
c_func
(paren
r_void
)paren
(brace
r_return
id|ARRAY_SIZE
c_func
(paren
id|aalg_list
)paren
suffix:semicolon
)brace
DECL|function|ealg_entries
r_static
r_inline
r_int
id|ealg_entries
c_func
(paren
r_void
)paren
(brace
r_return
id|ARRAY_SIZE
c_func
(paren
id|ealg_list
)paren
suffix:semicolon
)brace
DECL|function|calg_entries
r_static
r_inline
r_int
id|calg_entries
c_func
(paren
r_void
)paren
(brace
r_return
id|ARRAY_SIZE
c_func
(paren
id|calg_list
)paren
suffix:semicolon
)brace
multiline_comment|/* Todo: generic iterators */
DECL|function|xfrm_aalg_get_byid
r_struct
id|xfrm_algo_desc
op_star
id|xfrm_aalg_get_byid
c_func
(paren
r_int
id|alg_id
)paren
(brace
r_int
id|i
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
id|aalg_entries
c_func
(paren
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|aalg_list
(braket
id|i
)braket
dot
id|desc.sadb_alg_id
op_eq
id|alg_id
)paren
(brace
r_if
c_cond
(paren
id|aalg_list
(braket
id|i
)braket
dot
id|available
)paren
r_return
op_amp
id|aalg_list
(braket
id|i
)braket
suffix:semicolon
r_else
r_break
suffix:semicolon
)brace
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|xfrm_ealg_get_byid
r_struct
id|xfrm_algo_desc
op_star
id|xfrm_ealg_get_byid
c_func
(paren
r_int
id|alg_id
)paren
(brace
r_int
id|i
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
id|ealg_entries
c_func
(paren
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|ealg_list
(braket
id|i
)braket
dot
id|desc.sadb_alg_id
op_eq
id|alg_id
)paren
(brace
r_if
c_cond
(paren
id|ealg_list
(braket
id|i
)braket
dot
id|available
)paren
r_return
op_amp
id|ealg_list
(braket
id|i
)braket
suffix:semicolon
r_else
r_break
suffix:semicolon
)brace
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|xfrm_calg_get_byid
r_struct
id|xfrm_algo_desc
op_star
id|xfrm_calg_get_byid
c_func
(paren
r_int
id|alg_id
)paren
(brace
r_int
id|i
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
id|calg_entries
c_func
(paren
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|calg_list
(braket
id|i
)braket
dot
id|desc.sadb_alg_id
op_eq
id|alg_id
)paren
(brace
r_if
c_cond
(paren
id|calg_list
(braket
id|i
)braket
dot
id|available
)paren
r_return
op_amp
id|calg_list
(braket
id|i
)braket
suffix:semicolon
r_else
r_break
suffix:semicolon
)brace
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|xfrm_aalg_get_byname
r_struct
id|xfrm_algo_desc
op_star
id|xfrm_aalg_get_byname
c_func
(paren
r_char
op_star
id|name
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|name
)paren
r_return
l_int|NULL
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
id|aalg_entries
c_func
(paren
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|name
comma
id|aalg_list
(braket
id|i
)braket
dot
id|name
)paren
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|aalg_list
(braket
id|i
)braket
dot
id|available
)paren
r_return
op_amp
id|aalg_list
(braket
id|i
)braket
suffix:semicolon
r_else
r_break
suffix:semicolon
)brace
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|xfrm_ealg_get_byname
r_struct
id|xfrm_algo_desc
op_star
id|xfrm_ealg_get_byname
c_func
(paren
r_char
op_star
id|name
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|name
)paren
r_return
l_int|NULL
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
id|ealg_entries
c_func
(paren
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|name
comma
id|ealg_list
(braket
id|i
)braket
dot
id|name
)paren
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|ealg_list
(braket
id|i
)braket
dot
id|available
)paren
r_return
op_amp
id|ealg_list
(braket
id|i
)braket
suffix:semicolon
r_else
r_break
suffix:semicolon
)brace
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|xfrm_calg_get_byname
r_struct
id|xfrm_algo_desc
op_star
id|xfrm_calg_get_byname
c_func
(paren
r_char
op_star
id|name
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|name
)paren
r_return
l_int|NULL
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
id|calg_entries
c_func
(paren
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|name
comma
id|calg_list
(braket
id|i
)braket
dot
id|name
)paren
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|calg_list
(braket
id|i
)braket
dot
id|available
)paren
r_return
op_amp
id|calg_list
(braket
id|i
)braket
suffix:semicolon
r_else
r_break
suffix:semicolon
)brace
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|xfrm_aalg_get_byidx
r_struct
id|xfrm_algo_desc
op_star
id|xfrm_aalg_get_byidx
c_func
(paren
r_int
r_int
id|idx
)paren
(brace
r_if
c_cond
(paren
id|idx
op_ge
id|aalg_entries
c_func
(paren
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
r_return
op_amp
id|aalg_list
(braket
id|idx
)braket
suffix:semicolon
)brace
DECL|function|xfrm_ealg_get_byidx
r_struct
id|xfrm_algo_desc
op_star
id|xfrm_ealg_get_byidx
c_func
(paren
r_int
r_int
id|idx
)paren
(brace
r_if
c_cond
(paren
id|idx
op_ge
id|ealg_entries
c_func
(paren
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
r_return
op_amp
id|ealg_list
(braket
id|idx
)braket
suffix:semicolon
)brace
DECL|function|xfrm_calg_get_byidx
r_struct
id|xfrm_algo_desc
op_star
id|xfrm_calg_get_byidx
c_func
(paren
r_int
r_int
id|idx
)paren
(brace
r_if
c_cond
(paren
id|idx
op_ge
id|calg_entries
c_func
(paren
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
r_return
op_amp
id|calg_list
(braket
id|idx
)braket
suffix:semicolon
)brace
multiline_comment|/*&n; * Probe for the availability of crypto algorithms, and set the available&n; * flag for any algorithms found on the system.  This is typically called by&n; * pfkey during userspace SA add, update or register.&n; */
DECL|function|xfrm_probe_algs
r_void
id|xfrm_probe_algs
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_CRYPTO
r_int
id|i
comma
id|status
suffix:semicolon
id|BUG_ON
c_func
(paren
id|in_softirq
c_func
(paren
)paren
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
id|aalg_entries
c_func
(paren
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
id|status
op_assign
id|crypto_alg_available
c_func
(paren
id|aalg_list
(braket
id|i
)braket
dot
id|name
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|aalg_list
(braket
id|i
)braket
dot
id|available
op_ne
id|status
)paren
id|aalg_list
(braket
id|i
)braket
dot
id|available
op_assign
id|status
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
id|ealg_entries
c_func
(paren
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
id|status
op_assign
id|crypto_alg_available
c_func
(paren
id|ealg_list
(braket
id|i
)braket
dot
id|name
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ealg_list
(braket
id|i
)braket
dot
id|available
op_ne
id|status
)paren
id|ealg_list
(braket
id|i
)braket
dot
id|available
op_assign
id|status
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
id|calg_entries
c_func
(paren
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
id|status
op_assign
id|crypto_alg_available
c_func
(paren
id|calg_list
(braket
id|i
)braket
dot
id|name
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|calg_list
(braket
id|i
)braket
dot
id|available
op_ne
id|status
)paren
id|calg_list
(braket
id|i
)braket
dot
id|available
op_assign
id|status
suffix:semicolon
)brace
macro_line|#endif
)brace
DECL|function|xfrm_count_auth_supported
r_int
id|xfrm_count_auth_supported
c_func
(paren
r_void
)paren
(brace
r_int
id|i
comma
id|n
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
comma
id|n
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|aalg_entries
c_func
(paren
)paren
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|aalg_list
(braket
id|i
)braket
dot
id|available
)paren
id|n
op_increment
suffix:semicolon
r_return
id|n
suffix:semicolon
)brace
DECL|function|xfrm_count_enc_supported
r_int
id|xfrm_count_enc_supported
c_func
(paren
r_void
)paren
(brace
r_int
id|i
comma
id|n
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
comma
id|n
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|ealg_entries
c_func
(paren
)paren
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|ealg_list
(braket
id|i
)braket
dot
id|available
)paren
id|n
op_increment
suffix:semicolon
r_return
id|n
suffix:semicolon
)brace
multiline_comment|/* Move to common area: it is shared with AH. */
DECL|function|skb_icv_walk
r_void
id|skb_icv_walk
c_func
(paren
r_const
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|crypto_tfm
op_star
id|tfm
comma
r_int
id|offset
comma
r_int
id|len
comma
id|icv_update_fn_t
id|icv_update
)paren
(brace
r_int
id|start
op_assign
id|skb_headlen
c_func
(paren
id|skb
)paren
suffix:semicolon
r_int
id|i
comma
id|copy
op_assign
id|start
op_minus
id|offset
suffix:semicolon
r_struct
id|scatterlist
id|sg
suffix:semicolon
multiline_comment|/* Checksum header. */
r_if
c_cond
(paren
id|copy
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|copy
OG
id|len
)paren
id|copy
op_assign
id|len
suffix:semicolon
id|sg.page
op_assign
id|virt_to_page
c_func
(paren
id|skb-&gt;data
op_plus
id|offset
)paren
suffix:semicolon
id|sg.offset
op_assign
(paren
r_int
r_int
)paren
(paren
id|skb-&gt;data
op_plus
id|offset
)paren
op_mod
id|PAGE_SIZE
suffix:semicolon
id|sg.length
op_assign
id|copy
suffix:semicolon
id|icv_update
c_func
(paren
id|tfm
comma
op_amp
id|sg
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|len
op_sub_assign
id|copy
)paren
op_eq
l_int|0
)paren
r_return
suffix:semicolon
id|offset
op_add_assign
id|copy
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
id|skb_shinfo
c_func
(paren
id|skb
)paren
op_member_access_from_pointer
id|nr_frags
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
id|end
suffix:semicolon
id|BUG_TRAP
c_func
(paren
id|start
op_le
id|offset
op_plus
id|len
)paren
suffix:semicolon
id|end
op_assign
id|start
op_plus
id|skb_shinfo
c_func
(paren
id|skb
)paren
op_member_access_from_pointer
id|frags
(braket
id|i
)braket
dot
id|size
suffix:semicolon
r_if
c_cond
(paren
(paren
id|copy
op_assign
id|end
op_minus
id|offset
)paren
OG
l_int|0
)paren
(brace
id|skb_frag_t
op_star
id|frag
op_assign
op_amp
id|skb_shinfo
c_func
(paren
id|skb
)paren
op_member_access_from_pointer
id|frags
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|copy
OG
id|len
)paren
id|copy
op_assign
id|len
suffix:semicolon
id|sg.page
op_assign
id|frag-&gt;page
suffix:semicolon
id|sg.offset
op_assign
id|frag-&gt;page_offset
op_plus
id|offset
op_minus
id|start
suffix:semicolon
id|sg.length
op_assign
id|copy
suffix:semicolon
id|icv_update
c_func
(paren
id|tfm
comma
op_amp
id|sg
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|len
op_sub_assign
id|copy
)paren
)paren
r_return
suffix:semicolon
id|offset
op_add_assign
id|copy
suffix:semicolon
)brace
id|start
op_assign
id|end
suffix:semicolon
)brace
r_if
c_cond
(paren
id|skb_shinfo
c_func
(paren
id|skb
)paren
op_member_access_from_pointer
id|frag_list
)paren
(brace
r_struct
id|sk_buff
op_star
id|list
op_assign
id|skb_shinfo
c_func
(paren
id|skb
)paren
op_member_access_from_pointer
id|frag_list
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|list
suffix:semicolon
id|list
op_assign
id|list-&gt;next
)paren
(brace
r_int
id|end
suffix:semicolon
id|BUG_TRAP
c_func
(paren
id|start
op_le
id|offset
op_plus
id|len
)paren
suffix:semicolon
id|end
op_assign
id|start
op_plus
id|list-&gt;len
suffix:semicolon
r_if
c_cond
(paren
(paren
id|copy
op_assign
id|end
op_minus
id|offset
)paren
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|copy
OG
id|len
)paren
id|copy
op_assign
id|len
suffix:semicolon
id|skb_icv_walk
c_func
(paren
id|list
comma
id|tfm
comma
id|offset
op_minus
id|start
comma
id|copy
comma
id|icv_update
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|len
op_sub_assign
id|copy
)paren
op_eq
l_int|0
)paren
r_return
suffix:semicolon
id|offset
op_add_assign
id|copy
suffix:semicolon
)brace
id|start
op_assign
id|end
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|len
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#if defined(CONFIG_INET_ESP) || defined(CONFIG_INET_ESP_MODULE) || defined(CONFIG_INET6_ESP) || defined(CONFIG_INET6_ESP_MODULE)
multiline_comment|/* Looking generic it is not used in another places. */
r_int
DECL|function|skb_to_sgvec
id|skb_to_sgvec
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|scatterlist
op_star
id|sg
comma
r_int
id|offset
comma
r_int
id|len
)paren
(brace
r_int
id|start
op_assign
id|skb_headlen
c_func
(paren
id|skb
)paren
suffix:semicolon
r_int
id|i
comma
id|copy
op_assign
id|start
op_minus
id|offset
suffix:semicolon
r_int
id|elt
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|copy
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|copy
OG
id|len
)paren
id|copy
op_assign
id|len
suffix:semicolon
id|sg
(braket
id|elt
)braket
dot
id|page
op_assign
id|virt_to_page
c_func
(paren
id|skb-&gt;data
op_plus
id|offset
)paren
suffix:semicolon
id|sg
(braket
id|elt
)braket
dot
id|offset
op_assign
(paren
r_int
r_int
)paren
(paren
id|skb-&gt;data
op_plus
id|offset
)paren
op_mod
id|PAGE_SIZE
suffix:semicolon
id|sg
(braket
id|elt
)braket
dot
id|length
op_assign
id|copy
suffix:semicolon
id|elt
op_increment
suffix:semicolon
r_if
c_cond
(paren
(paren
id|len
op_sub_assign
id|copy
)paren
op_eq
l_int|0
)paren
r_return
id|elt
suffix:semicolon
id|offset
op_add_assign
id|copy
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
id|skb_shinfo
c_func
(paren
id|skb
)paren
op_member_access_from_pointer
id|nr_frags
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
id|end
suffix:semicolon
id|BUG_TRAP
c_func
(paren
id|start
op_le
id|offset
op_plus
id|len
)paren
suffix:semicolon
id|end
op_assign
id|start
op_plus
id|skb_shinfo
c_func
(paren
id|skb
)paren
op_member_access_from_pointer
id|frags
(braket
id|i
)braket
dot
id|size
suffix:semicolon
r_if
c_cond
(paren
(paren
id|copy
op_assign
id|end
op_minus
id|offset
)paren
OG
l_int|0
)paren
(brace
id|skb_frag_t
op_star
id|frag
op_assign
op_amp
id|skb_shinfo
c_func
(paren
id|skb
)paren
op_member_access_from_pointer
id|frags
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|copy
OG
id|len
)paren
id|copy
op_assign
id|len
suffix:semicolon
id|sg
(braket
id|elt
)braket
dot
id|page
op_assign
id|frag-&gt;page
suffix:semicolon
id|sg
(braket
id|elt
)braket
dot
id|offset
op_assign
id|frag-&gt;page_offset
op_plus
id|offset
op_minus
id|start
suffix:semicolon
id|sg
(braket
id|elt
)braket
dot
id|length
op_assign
id|copy
suffix:semicolon
id|elt
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|len
op_sub_assign
id|copy
)paren
)paren
r_return
id|elt
suffix:semicolon
id|offset
op_add_assign
id|copy
suffix:semicolon
)brace
id|start
op_assign
id|end
suffix:semicolon
)brace
r_if
c_cond
(paren
id|skb_shinfo
c_func
(paren
id|skb
)paren
op_member_access_from_pointer
id|frag_list
)paren
(brace
r_struct
id|sk_buff
op_star
id|list
op_assign
id|skb_shinfo
c_func
(paren
id|skb
)paren
op_member_access_from_pointer
id|frag_list
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|list
suffix:semicolon
id|list
op_assign
id|list-&gt;next
)paren
(brace
r_int
id|end
suffix:semicolon
id|BUG_TRAP
c_func
(paren
id|start
op_le
id|offset
op_plus
id|len
)paren
suffix:semicolon
id|end
op_assign
id|start
op_plus
id|list-&gt;len
suffix:semicolon
r_if
c_cond
(paren
(paren
id|copy
op_assign
id|end
op_minus
id|offset
)paren
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|copy
OG
id|len
)paren
id|copy
op_assign
id|len
suffix:semicolon
id|elt
op_add_assign
id|skb_to_sgvec
c_func
(paren
id|list
comma
id|sg
op_plus
id|elt
comma
id|offset
op_minus
id|start
comma
id|copy
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|len
op_sub_assign
id|copy
)paren
op_eq
l_int|0
)paren
r_return
id|elt
suffix:semicolon
id|offset
op_add_assign
id|copy
suffix:semicolon
)brace
id|start
op_assign
id|end
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|len
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_return
id|elt
suffix:semicolon
)brace
multiline_comment|/* Check that skb data bits are writable. If they are not, copy data&n; * to newly created private area. If &quot;tailbits&quot; is given, make sure that&n; * tailbits bytes beyond current end of skb are writable.&n; *&n; * Returns amount of elements of scatterlist to load for subsequent&n; * transformations and pointer to writable trailer skb.&n; */
DECL|function|skb_cow_data
r_int
id|skb_cow_data
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_int
id|tailbits
comma
r_struct
id|sk_buff
op_star
op_star
id|trailer
)paren
(brace
r_int
id|copyflag
suffix:semicolon
r_int
id|elt
suffix:semicolon
r_struct
id|sk_buff
op_star
id|skb1
comma
op_star
op_star
id|skb_p
suffix:semicolon
multiline_comment|/* If skb is cloned or its head is paged, reallocate&n;&t; * head pulling out all the pages (pages are considered not writable&n;&t; * at the moment even if they are anonymous).&n;&t; */
r_if
c_cond
(paren
(paren
id|skb_cloned
c_func
(paren
id|skb
)paren
op_logical_or
id|skb_shinfo
c_func
(paren
id|skb
)paren
op_member_access_from_pointer
id|nr_frags
)paren
op_logical_and
id|__pskb_pull_tail
c_func
(paren
id|skb
comma
id|skb_pagelen
c_func
(paren
id|skb
)paren
op_minus
id|skb_headlen
c_func
(paren
id|skb
)paren
)paren
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
multiline_comment|/* Easy case. Most of packets will go this way. */
r_if
c_cond
(paren
op_logical_neg
id|skb_shinfo
c_func
(paren
id|skb
)paren
op_member_access_from_pointer
id|frag_list
)paren
(brace
multiline_comment|/* A little of trouble, not enough of space for trailer.&n;&t;&t; * This should not happen, when stack is tuned to generate&n;&t;&t; * good frames. OK, on miss we reallocate and reserve even more&n;&t;&t; * space, 128 bytes is fair. */
r_if
c_cond
(paren
id|skb_tailroom
c_func
(paren
id|skb
)paren
OL
id|tailbits
op_logical_and
id|pskb_expand_head
c_func
(paren
id|skb
comma
l_int|0
comma
id|tailbits
op_minus
id|skb_tailroom
c_func
(paren
id|skb
)paren
op_plus
l_int|128
comma
id|GFP_ATOMIC
)paren
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
multiline_comment|/* Voila! */
op_star
id|trailer
op_assign
id|skb
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Misery. We are in troubles, going to mincer fragments... */
id|elt
op_assign
l_int|1
suffix:semicolon
id|skb_p
op_assign
op_amp
id|skb_shinfo
c_func
(paren
id|skb
)paren
op_member_access_from_pointer
id|frag_list
suffix:semicolon
id|copyflag
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
(paren
id|skb1
op_assign
op_star
id|skb_p
)paren
op_ne
l_int|NULL
)paren
(brace
r_int
id|ntail
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* The fragment is partially pulled by someone,&n;&t;&t; * this can happen on input. Copy it and everything&n;&t;&t; * after it. */
r_if
c_cond
(paren
id|skb_shared
c_func
(paren
id|skb1
)paren
)paren
id|copyflag
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* If the skb is the last, worry about trailer. */
r_if
c_cond
(paren
id|skb1-&gt;next
op_eq
l_int|NULL
op_logical_and
id|tailbits
)paren
(brace
r_if
c_cond
(paren
id|skb_shinfo
c_func
(paren
id|skb1
)paren
op_member_access_from_pointer
id|nr_frags
op_logical_or
id|skb_shinfo
c_func
(paren
id|skb1
)paren
op_member_access_from_pointer
id|frag_list
op_logical_or
id|skb_tailroom
c_func
(paren
id|skb1
)paren
OL
id|tailbits
)paren
id|ntail
op_assign
id|tailbits
op_plus
l_int|128
suffix:semicolon
)brace
r_if
c_cond
(paren
id|copyflag
op_logical_or
id|skb_cloned
c_func
(paren
id|skb1
)paren
op_logical_or
id|ntail
op_logical_or
id|skb_shinfo
c_func
(paren
id|skb1
)paren
op_member_access_from_pointer
id|nr_frags
op_logical_or
id|skb_shinfo
c_func
(paren
id|skb1
)paren
op_member_access_from_pointer
id|frag_list
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb2
suffix:semicolon
multiline_comment|/* Fuck, we are miserable poor guys... */
r_if
c_cond
(paren
id|ntail
op_eq
l_int|0
)paren
id|skb2
op_assign
id|skb_copy
c_func
(paren
id|skb1
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_else
id|skb2
op_assign
id|skb_copy_expand
c_func
(paren
id|skb1
comma
id|skb_headroom
c_func
(paren
id|skb1
)paren
comma
id|ntail
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|skb2
op_eq
l_int|NULL
)paren
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
id|skb1-&gt;sk
)paren
id|skb_set_owner_w
c_func
(paren
id|skb
comma
id|skb1-&gt;sk
)paren
suffix:semicolon
multiline_comment|/* Looking around. Are we still alive?&n;&t;&t;&t; * OK, link new skb, drop old one */
id|skb2-&gt;next
op_assign
id|skb1-&gt;next
suffix:semicolon
op_star
id|skb_p
op_assign
id|skb2
suffix:semicolon
id|kfree_skb
c_func
(paren
id|skb1
)paren
suffix:semicolon
id|skb1
op_assign
id|skb2
suffix:semicolon
)brace
id|elt
op_increment
suffix:semicolon
op_star
id|trailer
op_assign
id|skb1
suffix:semicolon
id|skb_p
op_assign
op_amp
id|skb1-&gt;next
suffix:semicolon
)brace
r_return
id|elt
suffix:semicolon
)brace
DECL|function|pskb_put
r_void
op_star
id|pskb_put
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|sk_buff
op_star
id|tail
comma
r_int
id|len
)paren
(brace
r_if
c_cond
(paren
id|tail
op_ne
id|skb
)paren
(brace
id|skb-&gt;data_len
op_add_assign
id|len
suffix:semicolon
id|skb-&gt;len
op_add_assign
id|len
suffix:semicolon
)brace
r_return
id|skb_put
c_func
(paren
id|tail
comma
id|len
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
