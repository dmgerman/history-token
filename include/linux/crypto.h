multiline_comment|/*&n; * Scatterlist Cryptographic API.&n; *&n; * Copyright (c) 2002 James Morris &lt;jmorris@intercode.com.au&gt;&n; * Copyright (c) 2002 David S. Miller (davem@redhat.com)&n; *&n; * Portions derived from Cryptoapi, by Alexander Kjeldaas &lt;astor@fast.no&gt;&n; * and Nettle, by Niels M&#xfffd;ller.&n; * &n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License as published by the Free&n; * Software Foundation; either version 2 of the License, or (at your option) &n; * any later version.&n; *&n; */
macro_line|#ifndef _LINUX_CRYPTO_H
DECL|macro|_LINUX_CRYPTO_H
mdefine_line|#define _LINUX_CRYPTO_H
multiline_comment|/* &n; * Crypto context flags.&n; */
DECL|macro|CRYPTO_WEAK_KEY_CHECK
mdefine_line|#define CRYPTO_WEAK_KEY_CHECK&t;0x0001
DECL|macro|CRYPTO_WEAK_KEY
mdefine_line|#define CRYPTO_WEAK_KEY&t;&t;0x0008
DECL|macro|CRYPTO_BAD_KEY_LEN
mdefine_line|#define CRYPTO_BAD_KEY_LEN&t;0x0010
DECL|macro|CRYPTO_BAD_KEY_SCHED
mdefine_line|#define CRYPTO_BAD_KEY_SCHED&t;0x0020
DECL|macro|CRYPTO_BAD_BLOCK_LEN
mdefine_line|#define CRYPTO_BAD_BLOCK_LEN&t;0x0040
DECL|macro|CRYPTO_ATOMIC
mdefine_line|#define CRYPTO_ATOMIC&t;&t;0x1000
multiline_comment|/*&n; * Algorithm identifiers.  These may be expanded later to 64 bits&n; * and include vendor id info, so we can have multiple versions&n; * (e.g. asm, various hardware versions etc).&n; *&n; * Todo: sadb translation.&n; */
DECL|macro|CRYPTO_TYPE_MASK
mdefine_line|#define CRYPTO_TYPE_MASK        0xf0000000
DECL|macro|CRYPTO_MODE_MASK
mdefine_line|#define CRYPTO_MODE_MASK        0x0ff00000
DECL|macro|CRYPTO_ALG_MASK
mdefine_line|#define CRYPTO_ALG_MASK&t;&t;0x000fffff
DECL|macro|CRYPTO_TYPE_CIPHER
mdefine_line|#define CRYPTO_TYPE_CIPHER&t;0x00000000
DECL|macro|CRYPTO_TYPE_DIGEST
mdefine_line|#define CRYPTO_TYPE_DIGEST&t;0x10000000
DECL|macro|CRYPTO_TYPE_COMP
mdefine_line|#define CRYPTO_TYPE_COMP&t;0x20000000
DECL|macro|CRYPTO_MODE_ECB
mdefine_line|#define CRYPTO_MODE_ECB&t;&t;0x00000000
DECL|macro|CRYPTO_MODE_CBC
mdefine_line|#define CRYPTO_MODE_CBC&t;&t;0x00100000
DECL|macro|CRYPTO_MODE_CFB
mdefine_line|#define CRYPTO_MODE_CFB&t;&t;0x00200000
DECL|macro|CRYPTO_MODE_CTR
mdefine_line|#define CRYPTO_MODE_CTR&t;&t;0x00400000
DECL|macro|CRYPTO_ALG_NULL
mdefine_line|#define CRYPTO_ALG_NULL&t;&t;0x00000000
DECL|macro|CRYPTO_ALG_DES
mdefine_line|#define CRYPTO_ALG_DES&t;&t;(0x00000001|CRYPTO_TYPE_CIPHER)
DECL|macro|CRYPTO_ALG_DES_ECB
mdefine_line|#define CRYPTO_ALG_DES_ECB&t;(CRYPTO_ALG_DES|CRYPTO_MODE_ECB)
DECL|macro|CRYPTO_ALG_DES_CBC
mdefine_line|#define CRYPTO_ALG_DES_CBC&t;(CRYPTO_ALG_DES|CRYPTO_MODE_CBC)
DECL|macro|CRYPTO_ALG_DES3_EDE
mdefine_line|#define CRYPTO_ALG_DES3_EDE&t;(0x00000002|CRYPTO_TYPE_CIPHER)
DECL|macro|CRYPTO_ALG_DES3_EDE_ECB
mdefine_line|#define CRYPTO_ALG_DES3_EDE_ECB&t;(CRYPTO_ALG_DES3_EDE|CRYPTO_MODE_ECB)
DECL|macro|CRYPTO_ALG_DES3_EDE_CBC
mdefine_line|#define CRYPTO_ALG_DES3_EDE_CBC&t;(CRYPTO_ALG_DES3_EDE|CRYPTO_MODE_CBC)
DECL|macro|CRYPTO_ALG_MD5
mdefine_line|#define CRYPTO_ALG_MD5&t;&t;(0x00000f00|CRYPTO_TYPE_DIGEST)
DECL|macro|CRYPTO_ALG_SHA1
mdefine_line|#define CRYPTO_ALG_SHA1&t;&t;(0x00000f01|CRYPTO_TYPE_DIGEST)
DECL|macro|CRYPTO_MAX_ALG_NAME
mdefine_line|#define CRYPTO_MAX_ALG_NAME&t;64
DECL|macro|CRYPTO_MAX_BLOCK_SIZE
mdefine_line|#define CRYPTO_MAX_BLOCK_SIZE&t;16
r_struct
id|scatterlist
suffix:semicolon
DECL|struct|cipher_alg
r_struct
id|cipher_alg
(brace
DECL|member|cia_keysize
r_int
id|cia_keysize
suffix:semicolon
DECL|member|cia_ivsize
r_int
id|cia_ivsize
suffix:semicolon
DECL|member|cia_setkey
r_int
(paren
op_star
id|cia_setkey
)paren
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
id|keylen
comma
r_int
op_star
id|flags
)paren
suffix:semicolon
DECL|member|cia_encrypt
r_void
(paren
op_star
id|cia_encrypt
)paren
(paren
r_void
op_star
id|ctx
comma
id|u8
op_star
id|dst
comma
id|u8
op_star
id|src
)paren
suffix:semicolon
DECL|member|cia_decrypt
r_void
(paren
op_star
id|cia_decrypt
)paren
(paren
r_void
op_star
id|ctx
comma
id|u8
op_star
id|dst
comma
id|u8
op_star
id|src
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|digest_alg
r_struct
id|digest_alg
(brace
DECL|member|dia_digestsize
r_int
id|dia_digestsize
suffix:semicolon
DECL|member|dia_init
r_void
(paren
op_star
id|dia_init
)paren
(paren
r_void
op_star
id|ctx
)paren
suffix:semicolon
DECL|member|dia_update
r_void
(paren
op_star
id|dia_update
)paren
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
suffix:semicolon
DECL|member|dia_final
r_void
(paren
op_star
id|dia_final
)paren
(paren
r_void
op_star
id|ctx
comma
id|u8
op_star
id|out
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|compress_alg
r_struct
id|compress_alg
(brace
DECL|member|coa_compress
r_void
(paren
op_star
id|coa_compress
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|coa_decompress
r_void
(paren
op_star
id|coa_decompress
)paren
(paren
r_void
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|cra_cipher
mdefine_line|#define cra_cipher&t;cra_u.cipher
DECL|macro|cra_digest
mdefine_line|#define cra_digest&t;cra_u.digest
DECL|macro|cra_compress
mdefine_line|#define cra_compress&t;cra_u.compress
DECL|struct|crypto_alg
r_struct
id|crypto_alg
(brace
DECL|member|cra_list
r_struct
id|list_head
id|cra_list
suffix:semicolon
DECL|member|cra_id
id|u32
id|cra_id
suffix:semicolon
DECL|member|cra_blocksize
r_int
id|cra_blocksize
suffix:semicolon
DECL|member|cra_ctxsize
r_int
id|cra_ctxsize
suffix:semicolon
DECL|member|cra_name
r_char
id|cra_name
(braket
id|CRYPTO_MAX_ALG_NAME
)braket
suffix:semicolon
r_union
(brace
DECL|member|cipher
r_struct
id|cipher_alg
id|cipher
suffix:semicolon
DECL|member|digest
r_struct
id|digest_alg
id|digest
suffix:semicolon
DECL|member|compress
r_struct
id|compress_alg
id|compress
suffix:semicolon
DECL|member|cra_u
)brace
id|cra_u
suffix:semicolon
DECL|member|cra_module
r_struct
id|module
op_star
id|cra_module
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Algorithm registration interface.&n; */
r_int
id|crypto_register_alg
c_func
(paren
r_struct
id|crypto_alg
op_star
id|alg
)paren
suffix:semicolon
r_int
id|crypto_unregister_alg
c_func
(paren
r_struct
id|crypto_alg
op_star
id|alg
)paren
suffix:semicolon
r_struct
id|crypto_tfm
suffix:semicolon
multiline_comment|/*&n; * Transformations: user-instantiated algorithms.&n; */
DECL|struct|cipher_tfm
r_struct
id|cipher_tfm
(brace
DECL|member|cit_iv
r_void
op_star
id|cit_iv
suffix:semicolon
DECL|member|cit_mode
id|u32
id|cit_mode
suffix:semicolon
DECL|member|cit_setkey
r_int
(paren
op_star
id|cit_setkey
)paren
(paren
r_struct
id|crypto_tfm
op_star
id|tfm
comma
r_const
id|u8
op_star
id|key
comma
r_int
id|keylen
)paren
suffix:semicolon
DECL|member|cit_encrypt
r_int
(paren
op_star
id|cit_encrypt
)paren
(paren
r_struct
id|crypto_tfm
op_star
id|tfm
comma
r_struct
id|scatterlist
op_star
id|sg
comma
r_int
id|nsg
)paren
suffix:semicolon
DECL|member|cit_decrypt
r_int
(paren
op_star
id|cit_decrypt
)paren
(paren
r_struct
id|crypto_tfm
op_star
id|tfm
comma
r_struct
id|scatterlist
op_star
id|sg
comma
r_int
id|nsg
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|digest_tfm
r_struct
id|digest_tfm
(brace
DECL|member|dit_init
r_void
(paren
op_star
id|dit_init
)paren
(paren
r_struct
id|crypto_tfm
op_star
id|tfm
)paren
suffix:semicolon
DECL|member|dit_update
r_void
(paren
op_star
id|dit_update
)paren
(paren
r_struct
id|crypto_tfm
op_star
id|tfm
comma
r_struct
id|scatterlist
op_star
id|sg
comma
r_int
id|nsg
)paren
suffix:semicolon
DECL|member|dit_final
r_void
(paren
op_star
id|dit_final
)paren
(paren
r_struct
id|crypto_tfm
op_star
id|tfm
comma
id|u8
op_star
id|out
)paren
suffix:semicolon
DECL|member|dit_digest
r_void
(paren
op_star
id|dit_digest
)paren
(paren
r_struct
id|crypto_tfm
op_star
id|tfm
comma
r_struct
id|scatterlist
op_star
id|sg
comma
r_int
id|nsg
comma
id|u8
op_star
id|out
)paren
suffix:semicolon
DECL|member|dit_hmac
r_void
(paren
op_star
id|dit_hmac
)paren
(paren
r_struct
id|crypto_tfm
op_star
id|tfm
comma
id|u8
op_star
id|key
comma
r_int
id|keylen
comma
r_struct
id|scatterlist
op_star
id|sg
comma
r_int
id|nsg
comma
id|u8
op_star
id|out
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|compress_tfm
r_struct
id|compress_tfm
(brace
DECL|member|cot_compress
r_void
(paren
op_star
id|cot_compress
)paren
(paren
r_struct
id|crypto_tfm
op_star
id|tfm
)paren
suffix:semicolon
DECL|member|cot_decompress
r_void
(paren
op_star
id|cot_decompress
)paren
(paren
r_struct
id|crypto_tfm
op_star
id|tfm
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|crt_cipher
mdefine_line|#define crt_cipher&t;crt_u.cipher
DECL|macro|crt_digest
mdefine_line|#define crt_digest&t;crt_u.digest
DECL|macro|crt_compress
mdefine_line|#define crt_compress&t;crt_u.compress
DECL|struct|crypto_tfm
r_struct
id|crypto_tfm
(brace
DECL|member|crt_ctx
r_void
op_star
id|crt_ctx
suffix:semicolon
DECL|member|crt_flags
r_int
id|crt_flags
suffix:semicolon
r_union
(brace
DECL|member|cipher
r_struct
id|cipher_tfm
id|cipher
suffix:semicolon
DECL|member|digest
r_struct
id|digest_tfm
id|digest
suffix:semicolon
DECL|member|compress
r_struct
id|compress_tfm
id|compress
suffix:semicolon
DECL|member|crt_u
)brace
id|crt_u
suffix:semicolon
DECL|member|__crt_alg
r_struct
id|crypto_alg
op_star
id|__crt_alg
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Finds specified algorithm, allocates and returns a transform for it.&n; * Will try an load a module based on the name if not present&n; * in the kernel.  Increments its algorithm refcount.&n; */
r_struct
id|crypto_tfm
op_star
id|crypto_alloc_tfm
c_func
(paren
id|u32
id|id
)paren
suffix:semicolon
multiline_comment|/*&n; * Frees the transform and decrements its algorithm&squot;s recount.&n; */
r_void
id|crypto_free_tfm
c_func
(paren
r_struct
id|crypto_tfm
op_star
id|tfm
)paren
suffix:semicolon
multiline_comment|/*&n; * API wrappers.&n; */
DECL|function|crypto_digest_init
r_static
r_inline
r_void
id|crypto_digest_init
c_func
(paren
r_struct
id|crypto_tfm
op_star
id|tfm
)paren
(brace
id|tfm-&gt;crt_digest
dot
id|dit_init
c_func
(paren
id|tfm
)paren
suffix:semicolon
)brace
DECL|function|crypto_digest_update
r_static
r_inline
r_void
id|crypto_digest_update
c_func
(paren
r_struct
id|crypto_tfm
op_star
id|tfm
comma
r_struct
id|scatterlist
op_star
id|sg
comma
r_int
id|nsg
)paren
(brace
id|tfm-&gt;crt_digest
dot
id|dit_update
c_func
(paren
id|tfm
comma
id|sg
comma
id|nsg
)paren
suffix:semicolon
)brace
DECL|function|crypto_digest_final
r_static
r_inline
r_void
id|crypto_digest_final
c_func
(paren
r_struct
id|crypto_tfm
op_star
id|tfm
comma
id|u8
op_star
id|out
)paren
(brace
id|tfm-&gt;crt_digest
dot
id|dit_final
c_func
(paren
id|tfm
comma
id|out
)paren
suffix:semicolon
)brace
DECL|function|crypto_digest_digest
r_static
r_inline
r_void
id|crypto_digest_digest
c_func
(paren
r_struct
id|crypto_tfm
op_star
id|tfm
comma
r_struct
id|scatterlist
op_star
id|sg
comma
r_int
id|nsg
comma
id|u8
op_star
id|out
)paren
(brace
id|tfm-&gt;crt_digest
dot
id|dit_digest
c_func
(paren
id|tfm
comma
id|sg
comma
id|nsg
comma
id|out
)paren
suffix:semicolon
)brace
DECL|function|crypto_digest_hmac
r_static
r_inline
r_void
id|crypto_digest_hmac
c_func
(paren
r_struct
id|crypto_tfm
op_star
id|tfm
comma
id|u8
op_star
id|key
comma
r_int
id|keylen
comma
r_struct
id|scatterlist
op_star
id|sg
comma
r_int
id|nsg
comma
id|u8
op_star
id|out
)paren
(brace
id|tfm-&gt;crt_digest
dot
id|dit_hmac
c_func
(paren
id|tfm
comma
id|key
comma
id|keylen
comma
id|sg
comma
id|nsg
comma
id|out
)paren
suffix:semicolon
)brace
DECL|function|crypto_cipher_setkey
r_static
r_inline
r_int
id|crypto_cipher_setkey
c_func
(paren
r_struct
id|crypto_tfm
op_star
id|tfm
comma
r_const
id|u8
op_star
id|key
comma
r_int
id|keylen
)paren
(brace
r_return
id|tfm-&gt;crt_cipher
dot
id|cit_setkey
c_func
(paren
id|tfm
comma
id|key
comma
id|keylen
)paren
suffix:semicolon
)brace
DECL|function|crypto_cipher_encrypt
r_static
r_inline
r_int
id|crypto_cipher_encrypt
c_func
(paren
r_struct
id|crypto_tfm
op_star
id|tfm
comma
r_struct
id|scatterlist
op_star
id|sg
comma
r_int
id|nsg
)paren
(brace
r_return
id|tfm-&gt;crt_cipher
dot
id|cit_encrypt
c_func
(paren
id|tfm
comma
id|sg
comma
id|nsg
)paren
suffix:semicolon
)brace
DECL|function|crypto_cipher_decrypt
r_static
r_inline
r_int
id|crypto_cipher_decrypt
c_func
(paren
r_struct
id|crypto_tfm
op_star
id|tfm
comma
r_struct
id|scatterlist
op_star
id|sg
comma
r_int
id|nsg
)paren
(brace
r_return
id|tfm-&gt;crt_cipher
dot
id|cit_decrypt
c_func
(paren
id|tfm
comma
id|sg
comma
id|nsg
)paren
suffix:semicolon
)brace
DECL|function|crypto_cipher_copy_iv
r_static
r_inline
r_void
id|crypto_cipher_copy_iv
c_func
(paren
r_struct
id|crypto_tfm
op_star
id|tfm
comma
id|u8
op_star
id|src
comma
r_int
id|len
)paren
(brace
id|memcpy
c_func
(paren
id|tfm-&gt;crt_cipher.cit_iv
comma
id|src
comma
id|len
)paren
suffix:semicolon
)brace
DECL|function|crypto_comp_compress
r_static
r_inline
r_void
id|crypto_comp_compress
c_func
(paren
r_struct
id|crypto_tfm
op_star
id|tfm
)paren
(brace
id|tfm-&gt;crt_compress
dot
id|cot_compress
c_func
(paren
id|tfm
)paren
suffix:semicolon
)brace
DECL|function|crypto_comp_decompress
r_static
r_inline
r_void
id|crypto_comp_decompress
c_func
(paren
r_struct
id|crypto_tfm
op_star
id|tfm
)paren
(brace
id|tfm-&gt;crt_compress
dot
id|cot_decompress
c_func
(paren
id|tfm
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Transform helpers which allow the underlying algorithm to be queried.&n; */
DECL|function|crypto_tfm_id
r_static
r_inline
r_int
id|crypto_tfm_id
c_func
(paren
r_struct
id|crypto_tfm
op_star
id|tfm
)paren
(brace
r_return
id|tfm-&gt;__crt_alg-&gt;cra_id
suffix:semicolon
)brace
DECL|function|crypto_tfm_alg
r_static
r_inline
r_int
id|crypto_tfm_alg
c_func
(paren
r_struct
id|crypto_tfm
op_star
id|tfm
)paren
(brace
r_return
id|tfm-&gt;__crt_alg-&gt;cra_id
op_amp
id|CRYPTO_ALG_MASK
suffix:semicolon
)brace
DECL|function|crypto_tfm_name
r_static
r_inline
r_char
op_star
id|crypto_tfm_name
c_func
(paren
r_struct
id|crypto_tfm
op_star
id|tfm
)paren
(brace
r_return
id|tfm-&gt;__crt_alg-&gt;cra_name
suffix:semicolon
)brace
DECL|function|crypto_tfm_type
r_static
r_inline
id|u32
id|crypto_tfm_type
c_func
(paren
r_struct
id|crypto_tfm
op_star
id|tfm
)paren
(brace
r_return
id|tfm-&gt;__crt_alg-&gt;cra_id
op_amp
id|CRYPTO_TYPE_MASK
suffix:semicolon
)brace
DECL|function|crypto_tfm_keysize
r_static
r_inline
r_int
id|crypto_tfm_keysize
c_func
(paren
r_struct
id|crypto_tfm
op_star
id|tfm
)paren
(brace
r_return
id|tfm-&gt;__crt_alg-&gt;cra_cipher.cia_keysize
suffix:semicolon
)brace
DECL|function|crypto_tfm_ivsize
r_static
r_inline
r_int
id|crypto_tfm_ivsize
c_func
(paren
r_struct
id|crypto_tfm
op_star
id|tfm
)paren
(brace
r_return
id|tfm-&gt;__crt_alg-&gt;cra_cipher.cia_ivsize
suffix:semicolon
)brace
DECL|function|crypto_tfm_blocksize
r_static
r_inline
r_int
id|crypto_tfm_blocksize
c_func
(paren
r_struct
id|crypto_tfm
op_star
id|tfm
)paren
(brace
r_return
id|tfm-&gt;__crt_alg-&gt;cra_blocksize
suffix:semicolon
)brace
DECL|function|crypto_tfm_digestsize
r_static
r_inline
r_int
id|crypto_tfm_digestsize
c_func
(paren
r_struct
id|crypto_tfm
op_star
id|tfm
)paren
(brace
r_return
id|tfm-&gt;__crt_alg-&gt;cra_digest.dia_digestsize
suffix:semicolon
)brace
macro_line|#endif&t;/* _LINUX_CRYPTO_H */
eof
