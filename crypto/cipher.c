multiline_comment|/*&n; * Cryptographic API.&n; *&n; * Cipher operations.&n; *&n; * Copyright (c) 2002 James Morris &lt;jmorris@intercode.com.au&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License as published by the Free&n; * Software Foundation; either version 2 of the License, or (at your option) &n; * any later version.&n; *&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/crypto.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;asm/scatterlist.h&gt;
macro_line|#include &quot;internal.h&quot;
macro_line|#include &quot;scatterwalk.h&quot;
DECL|typedef|cryptfn_t
r_typedef
r_void
(paren
id|cryptfn_t
)paren
(paren
r_void
op_star
comma
id|u8
op_star
comma
r_const
id|u8
op_star
)paren
suffix:semicolon
DECL|typedef|procfn_t
r_typedef
r_void
(paren
id|procfn_t
)paren
(paren
r_struct
id|crypto_tfm
op_star
comma
id|u8
op_star
comma
id|u8
op_star
comma
id|cryptfn_t
comma
r_int
id|enc
comma
r_void
op_star
comma
r_int
)paren
suffix:semicolon
DECL|function|xor_64
r_static
r_inline
r_void
id|xor_64
c_func
(paren
id|u8
op_star
id|a
comma
r_const
id|u8
op_star
id|b
)paren
(brace
(paren
(paren
id|u32
op_star
)paren
id|a
)paren
(braket
l_int|0
)braket
op_xor_assign
(paren
(paren
id|u32
op_star
)paren
id|b
)paren
(braket
l_int|0
)braket
suffix:semicolon
(paren
(paren
id|u32
op_star
)paren
id|a
)paren
(braket
l_int|1
)braket
op_xor_assign
(paren
(paren
id|u32
op_star
)paren
id|b
)paren
(braket
l_int|1
)braket
suffix:semicolon
)brace
DECL|function|xor_128
r_static
r_inline
r_void
id|xor_128
c_func
(paren
id|u8
op_star
id|a
comma
r_const
id|u8
op_star
id|b
)paren
(brace
(paren
(paren
id|u32
op_star
)paren
id|a
)paren
(braket
l_int|0
)braket
op_xor_assign
(paren
(paren
id|u32
op_star
)paren
id|b
)paren
(braket
l_int|0
)braket
suffix:semicolon
(paren
(paren
id|u32
op_star
)paren
id|a
)paren
(braket
l_int|1
)braket
op_xor_assign
(paren
(paren
id|u32
op_star
)paren
id|b
)paren
(braket
l_int|1
)braket
suffix:semicolon
(paren
(paren
id|u32
op_star
)paren
id|a
)paren
(braket
l_int|2
)braket
op_xor_assign
(paren
(paren
id|u32
op_star
)paren
id|b
)paren
(braket
l_int|2
)braket
suffix:semicolon
(paren
(paren
id|u32
op_star
)paren
id|a
)paren
(braket
l_int|3
)braket
op_xor_assign
(paren
(paren
id|u32
op_star
)paren
id|b
)paren
(braket
l_int|3
)braket
suffix:semicolon
)brace
multiline_comment|/* &n; * Generic encrypt/decrypt wrapper for ciphers, handles operations across&n; * multiple page boundaries by using temporary blocks.  In user context,&n; * the kernel is given a chance to schedule us once per block.&n; */
DECL|function|crypt
r_static
r_int
id|crypt
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
id|dst
comma
r_struct
id|scatterlist
op_star
id|src
comma
r_int
r_int
id|nbytes
comma
id|cryptfn_t
id|crfn
comma
id|procfn_t
id|prfn
comma
r_int
id|enc
comma
r_void
op_star
id|info
)paren
(brace
r_struct
id|scatter_walk
id|walk_in
comma
id|walk_out
suffix:semicolon
r_const
r_int
r_int
id|bsize
op_assign
id|crypto_tfm_alg_blocksize
c_func
(paren
id|tfm
)paren
suffix:semicolon
id|u8
id|tmp_src
(braket
id|nbytes
OG
id|src-&gt;length
ques
c_cond
id|bsize
suffix:colon
l_int|0
)braket
suffix:semicolon
id|u8
id|tmp_dst
(braket
id|nbytes
OG
id|dst-&gt;length
ques
c_cond
id|bsize
suffix:colon
l_int|0
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|nbytes
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|nbytes
op_mod
id|bsize
)paren
(brace
id|tfm-&gt;crt_flags
op_or_assign
id|CRYPTO_TFM_RES_BAD_BLOCK_LEN
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|scatterwalk_start
c_func
(paren
op_amp
id|walk_in
comma
id|src
)paren
suffix:semicolon
id|scatterwalk_start
c_func
(paren
op_amp
id|walk_out
comma
id|dst
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
id|u8
op_star
id|src_p
comma
op_star
id|dst_p
suffix:semicolon
id|scatterwalk_map
c_func
(paren
op_amp
id|walk_in
comma
l_int|0
)paren
suffix:semicolon
id|scatterwalk_map
c_func
(paren
op_amp
id|walk_out
comma
l_int|1
)paren
suffix:semicolon
id|src_p
op_assign
id|scatterwalk_whichbuf
c_func
(paren
op_amp
id|walk_in
comma
id|bsize
comma
id|tmp_src
)paren
suffix:semicolon
id|dst_p
op_assign
id|scatterwalk_whichbuf
c_func
(paren
op_amp
id|walk_out
comma
id|bsize
comma
id|tmp_dst
)paren
suffix:semicolon
id|nbytes
op_sub_assign
id|bsize
suffix:semicolon
id|scatterwalk_copychunks
c_func
(paren
id|src_p
comma
op_amp
id|walk_in
comma
id|bsize
comma
l_int|0
)paren
suffix:semicolon
id|prfn
c_func
(paren
id|tfm
comma
id|dst_p
comma
id|src_p
comma
id|crfn
comma
id|enc
comma
id|info
comma
id|scatterwalk_samebuf
c_func
(paren
op_amp
id|walk_in
comma
op_amp
id|walk_out
comma
id|src_p
comma
id|dst_p
)paren
)paren
suffix:semicolon
id|scatterwalk_done
c_func
(paren
op_amp
id|walk_in
comma
l_int|0
comma
id|nbytes
)paren
suffix:semicolon
id|scatterwalk_copychunks
c_func
(paren
id|dst_p
comma
op_amp
id|walk_out
comma
id|bsize
comma
l_int|1
)paren
suffix:semicolon
id|scatterwalk_done
c_func
(paren
op_amp
id|walk_out
comma
l_int|1
comma
id|nbytes
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|nbytes
)paren
r_return
l_int|0
suffix:semicolon
id|crypto_yield
c_func
(paren
id|tfm
)paren
suffix:semicolon
)brace
)brace
DECL|function|cbc_process
r_static
r_void
id|cbc_process
c_func
(paren
r_struct
id|crypto_tfm
op_star
id|tfm
comma
id|u8
op_star
id|dst
comma
id|u8
op_star
id|src
comma
id|cryptfn_t
id|fn
comma
r_int
id|enc
comma
r_void
op_star
id|info
comma
r_int
id|in_place
)paren
(brace
id|u8
op_star
id|iv
op_assign
id|info
suffix:semicolon
multiline_comment|/* Null encryption */
r_if
c_cond
(paren
op_logical_neg
id|iv
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|enc
)paren
(brace
id|tfm-&gt;crt_u.cipher
dot
id|cit_xor_block
c_func
(paren
id|iv
comma
id|src
)paren
suffix:semicolon
id|fn
c_func
(paren
id|crypto_tfm_ctx
c_func
(paren
id|tfm
)paren
comma
id|dst
comma
id|iv
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|iv
comma
id|dst
comma
id|crypto_tfm_alg_blocksize
c_func
(paren
id|tfm
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|u8
id|stack
(braket
id|in_place
ques
c_cond
id|crypto_tfm_alg_blocksize
c_func
(paren
id|tfm
)paren
suffix:colon
l_int|0
)braket
suffix:semicolon
id|u8
op_star
id|buf
op_assign
id|in_place
ques
c_cond
id|stack
suffix:colon
id|dst
suffix:semicolon
id|fn
c_func
(paren
id|crypto_tfm_ctx
c_func
(paren
id|tfm
)paren
comma
id|buf
comma
id|src
)paren
suffix:semicolon
id|tfm-&gt;crt_u.cipher
dot
id|cit_xor_block
c_func
(paren
id|buf
comma
id|iv
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|iv
comma
id|src
comma
id|crypto_tfm_alg_blocksize
c_func
(paren
id|tfm
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|buf
op_ne
id|dst
)paren
id|memcpy
c_func
(paren
id|dst
comma
id|buf
comma
id|crypto_tfm_alg_blocksize
c_func
(paren
id|tfm
)paren
)paren
suffix:semicolon
)brace
)brace
DECL|function|ecb_process
r_static
r_void
id|ecb_process
c_func
(paren
r_struct
id|crypto_tfm
op_star
id|tfm
comma
id|u8
op_star
id|dst
comma
id|u8
op_star
id|src
comma
id|cryptfn_t
id|fn
comma
r_int
id|enc
comma
r_void
op_star
id|info
comma
r_int
id|in_place
)paren
(brace
id|fn
c_func
(paren
id|crypto_tfm_ctx
c_func
(paren
id|tfm
)paren
comma
id|dst
comma
id|src
)paren
suffix:semicolon
)brace
DECL|function|setkey
r_static
r_int
id|setkey
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
r_int
id|keylen
)paren
(brace
r_struct
id|cipher_alg
op_star
id|cia
op_assign
op_amp
id|tfm-&gt;__crt_alg-&gt;cra_cipher
suffix:semicolon
r_if
c_cond
(paren
id|keylen
template_param
id|cia-&gt;cia_max_keysize
)paren
(brace
id|tfm-&gt;crt_flags
op_or_assign
id|CRYPTO_TFM_RES_BAD_KEY_LEN
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_else
r_return
id|cia
op_member_access_from_pointer
id|cia_setkey
c_func
(paren
id|crypto_tfm_ctx
c_func
(paren
id|tfm
)paren
comma
id|key
comma
id|keylen
comma
op_amp
id|tfm-&gt;crt_flags
)paren
suffix:semicolon
)brace
DECL|function|ecb_encrypt
r_static
r_int
id|ecb_encrypt
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
id|dst
comma
r_struct
id|scatterlist
op_star
id|src
comma
r_int
r_int
id|nbytes
)paren
(brace
r_return
id|crypt
c_func
(paren
id|tfm
comma
id|dst
comma
id|src
comma
id|nbytes
comma
id|tfm-&gt;__crt_alg-&gt;cra_cipher.cia_encrypt
comma
id|ecb_process
comma
l_int|1
comma
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|function|ecb_decrypt
r_static
r_int
id|ecb_decrypt
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
id|dst
comma
r_struct
id|scatterlist
op_star
id|src
comma
r_int
r_int
id|nbytes
)paren
(brace
r_return
id|crypt
c_func
(paren
id|tfm
comma
id|dst
comma
id|src
comma
id|nbytes
comma
id|tfm-&gt;__crt_alg-&gt;cra_cipher.cia_decrypt
comma
id|ecb_process
comma
l_int|1
comma
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|function|cbc_encrypt
r_static
r_int
id|cbc_encrypt
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
id|dst
comma
r_struct
id|scatterlist
op_star
id|src
comma
r_int
r_int
id|nbytes
)paren
(brace
r_return
id|crypt
c_func
(paren
id|tfm
comma
id|dst
comma
id|src
comma
id|nbytes
comma
id|tfm-&gt;__crt_alg-&gt;cra_cipher.cia_encrypt
comma
id|cbc_process
comma
l_int|1
comma
id|tfm-&gt;crt_cipher.cit_iv
)paren
suffix:semicolon
)brace
DECL|function|cbc_encrypt_iv
r_static
r_int
id|cbc_encrypt_iv
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
id|dst
comma
r_struct
id|scatterlist
op_star
id|src
comma
r_int
r_int
id|nbytes
comma
id|u8
op_star
id|iv
)paren
(brace
r_return
id|crypt
c_func
(paren
id|tfm
comma
id|dst
comma
id|src
comma
id|nbytes
comma
id|tfm-&gt;__crt_alg-&gt;cra_cipher.cia_encrypt
comma
id|cbc_process
comma
l_int|1
comma
id|iv
)paren
suffix:semicolon
)brace
DECL|function|cbc_decrypt
r_static
r_int
id|cbc_decrypt
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
id|dst
comma
r_struct
id|scatterlist
op_star
id|src
comma
r_int
r_int
id|nbytes
)paren
(brace
r_return
id|crypt
c_func
(paren
id|tfm
comma
id|dst
comma
id|src
comma
id|nbytes
comma
id|tfm-&gt;__crt_alg-&gt;cra_cipher.cia_decrypt
comma
id|cbc_process
comma
l_int|0
comma
id|tfm-&gt;crt_cipher.cit_iv
)paren
suffix:semicolon
)brace
DECL|function|cbc_decrypt_iv
r_static
r_int
id|cbc_decrypt_iv
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
id|dst
comma
r_struct
id|scatterlist
op_star
id|src
comma
r_int
r_int
id|nbytes
comma
id|u8
op_star
id|iv
)paren
(brace
r_return
id|crypt
c_func
(paren
id|tfm
comma
id|dst
comma
id|src
comma
id|nbytes
comma
id|tfm-&gt;__crt_alg-&gt;cra_cipher.cia_decrypt
comma
id|cbc_process
comma
l_int|0
comma
id|iv
)paren
suffix:semicolon
)brace
DECL|function|nocrypt
r_static
r_int
id|nocrypt
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
id|dst
comma
r_struct
id|scatterlist
op_star
id|src
comma
r_int
r_int
id|nbytes
)paren
(brace
r_return
op_minus
id|ENOSYS
suffix:semicolon
)brace
DECL|function|nocrypt_iv
r_static
r_int
id|nocrypt_iv
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
id|dst
comma
r_struct
id|scatterlist
op_star
id|src
comma
r_int
r_int
id|nbytes
comma
id|u8
op_star
id|iv
)paren
(brace
r_return
op_minus
id|ENOSYS
suffix:semicolon
)brace
DECL|function|crypto_init_cipher_flags
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
(brace
id|u32
id|mode
op_assign
id|flags
op_amp
id|CRYPTO_TFM_MODE_MASK
suffix:semicolon
id|tfm-&gt;crt_cipher.cit_mode
op_assign
id|mode
ques
c_cond
id|mode
suffix:colon
id|CRYPTO_TFM_MODE_ECB
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
id|CRYPTO_TFM_REQ_WEAK_KEY
)paren
id|tfm-&gt;crt_flags
op_assign
id|CRYPTO_TFM_REQ_WEAK_KEY
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|crypto_init_cipher_ops
r_int
id|crypto_init_cipher_ops
c_func
(paren
r_struct
id|crypto_tfm
op_star
id|tfm
)paren
(brace
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_struct
id|cipher_tfm
op_star
id|ops
op_assign
op_amp
id|tfm-&gt;crt_cipher
suffix:semicolon
id|ops-&gt;cit_setkey
op_assign
id|setkey
suffix:semicolon
r_switch
c_cond
(paren
id|tfm-&gt;crt_cipher.cit_mode
)paren
(brace
r_case
id|CRYPTO_TFM_MODE_ECB
suffix:colon
id|ops-&gt;cit_encrypt
op_assign
id|ecb_encrypt
suffix:semicolon
id|ops-&gt;cit_decrypt
op_assign
id|ecb_decrypt
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CRYPTO_TFM_MODE_CBC
suffix:colon
id|ops-&gt;cit_encrypt
op_assign
id|cbc_encrypt
suffix:semicolon
id|ops-&gt;cit_decrypt
op_assign
id|cbc_decrypt
suffix:semicolon
id|ops-&gt;cit_encrypt_iv
op_assign
id|cbc_encrypt_iv
suffix:semicolon
id|ops-&gt;cit_decrypt_iv
op_assign
id|cbc_decrypt_iv
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CRYPTO_TFM_MODE_CFB
suffix:colon
id|ops-&gt;cit_encrypt
op_assign
id|nocrypt
suffix:semicolon
id|ops-&gt;cit_decrypt
op_assign
id|nocrypt
suffix:semicolon
id|ops-&gt;cit_encrypt_iv
op_assign
id|nocrypt_iv
suffix:semicolon
id|ops-&gt;cit_decrypt_iv
op_assign
id|nocrypt_iv
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CRYPTO_TFM_MODE_CTR
suffix:colon
id|ops-&gt;cit_encrypt
op_assign
id|nocrypt
suffix:semicolon
id|ops-&gt;cit_decrypt
op_assign
id|nocrypt
suffix:semicolon
id|ops-&gt;cit_encrypt_iv
op_assign
id|nocrypt_iv
suffix:semicolon
id|ops-&gt;cit_decrypt_iv
op_assign
id|nocrypt_iv
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ops-&gt;cit_mode
op_eq
id|CRYPTO_TFM_MODE_CBC
)paren
(brace
r_switch
c_cond
(paren
id|crypto_tfm_alg_blocksize
c_func
(paren
id|tfm
)paren
)paren
(brace
r_case
l_int|8
suffix:colon
id|ops-&gt;cit_xor_block
op_assign
id|xor_64
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|16
suffix:colon
id|ops-&gt;cit_xor_block
op_assign
id|xor_128
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s: block size %u not supported&bslash;n&quot;
comma
id|crypto_tfm_alg_name
c_func
(paren
id|tfm
)paren
comma
id|crypto_tfm_alg_blocksize
c_func
(paren
id|tfm
)paren
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|ops-&gt;cit_ivsize
op_assign
id|crypto_tfm_alg_blocksize
c_func
(paren
id|tfm
)paren
suffix:semicolon
id|ops-&gt;cit_iv
op_assign
id|kmalloc
c_func
(paren
id|ops-&gt;cit_ivsize
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ops-&gt;cit_iv
op_eq
l_int|NULL
)paren
id|ret
op_assign
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|out
suffix:colon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|crypto_exit_cipher_ops
r_void
id|crypto_exit_cipher_ops
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
id|tfm-&gt;crt_cipher.cit_iv
)paren
id|kfree
c_func
(paren
id|tfm-&gt;crt_cipher.cit_iv
)paren
suffix:semicolon
)brace
eof
