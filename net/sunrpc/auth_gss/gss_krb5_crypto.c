multiline_comment|/*&n; *  linux/net/sunrpc/gss_krb5_crypto.c&n; *&n; *  Copyright (c) 2000 The Regents of the University of Michigan.&n; *  All rights reserved.&n; *&n; *  Andy Adamson   &lt;andros@umich.edu&gt;&n; *  Bruce Fields   &lt;bfields@umich.edu&gt;&n; */
multiline_comment|/*&n; * Copyright (C) 1998 by the FundsXpress, INC.&n; *&n; * All rights reserved.&n; *&n; * Export of this software from the United States of America may require&n; * a specific license from the United States Government.  It is the&n; * responsibility of any person or organization contemplating export to&n; * obtain such a license before exporting.&n; *&n; * WITHIN THAT CONSTRAINT, permission to use, copy, modify, and&n; * distribute this software and its documentation for any purpose and&n; * without fee is hereby granted, provided that the above copyright&n; * notice appear in all copies and that both that copyright notice and&n; * this permission notice appear in supporting documentation, and that&n; * the name of FundsXpress. not be used in advertising or publicity pertaining&n; * to distribution of the software without specific, written prior&n; * permission.  FundsXpress makes no representations about the suitability of&n; * this software for any purpose.  It is provided &quot;as is&quot; without express&n; * or implied warranty.&n; *&n; * THIS SOFTWARE IS PROVIDED ``AS IS&squot;&squot; AND WITHOUT ANY EXPRESS OR&n; * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED&n; * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;asm/scatterlist.h&gt;
macro_line|#include &lt;linux/crypto.h&gt;
macro_line|#include &lt;linux/highmem.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;linux/sunrpc/gss_krb5.h&gt;
macro_line|#ifdef RPC_DEBUG
DECL|macro|RPCDBG_FACILITY
macro_line|# define RPCDBG_FACILITY        RPCDBG_AUTH
macro_line|#endif
id|u32
DECL|function|krb5_encrypt
id|krb5_encrypt
c_func
(paren
r_struct
id|crypto_tfm
op_star
id|tfm
comma
r_void
op_star
id|iv
comma
r_void
op_star
id|in
comma
r_void
op_star
id|out
comma
r_int
id|length
)paren
(brace
id|u32
id|ret
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_struct
id|scatterlist
id|sg
(braket
l_int|1
)braket
suffix:semicolon
id|u8
id|local_iv
(braket
l_int|16
)braket
op_assign
(brace
l_int|0
)brace
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;RPC:      krb5_encrypt: input data:&bslash;n&quot;
)paren
suffix:semicolon
id|print_hexl
c_func
(paren
(paren
id|u32
op_star
)paren
id|in
comma
id|length
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|length
op_mod
id|crypto_tfm_alg_blocksize
c_func
(paren
id|tfm
)paren
op_ne
l_int|0
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|crypto_tfm_alg_ivsize
c_func
(paren
id|tfm
)paren
OG
l_int|16
)paren
(brace
id|dprintk
c_func
(paren
l_string|&quot;RPC:      gss_k5encrypt: tfm iv size to large %d&bslash;n&quot;
comma
id|crypto_tfm_alg_ivsize
c_func
(paren
id|tfm
)paren
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|iv
)paren
id|memcpy
c_func
(paren
id|local_iv
comma
id|iv
comma
id|crypto_tfm_alg_ivsize
c_func
(paren
id|tfm
)paren
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|out
comma
id|in
comma
id|length
)paren
suffix:semicolon
id|sg
(braket
l_int|0
)braket
dot
id|page
op_assign
id|virt_to_page
c_func
(paren
id|out
)paren
suffix:semicolon
id|sg
(braket
l_int|0
)braket
dot
id|offset
op_assign
id|offset_in_page
c_func
(paren
id|out
)paren
suffix:semicolon
id|sg
(braket
l_int|0
)braket
dot
id|length
op_assign
id|length
suffix:semicolon
id|ret
op_assign
id|crypto_cipher_encrypt_iv
c_func
(paren
id|tfm
comma
id|sg
comma
id|sg
comma
id|length
comma
id|local_iv
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;RPC:      krb5_encrypt: output data:&bslash;n&quot;
)paren
suffix:semicolon
id|print_hexl
c_func
(paren
(paren
id|u32
op_star
)paren
id|out
comma
id|length
comma
l_int|0
)paren
suffix:semicolon
id|out
suffix:colon
id|dprintk
c_func
(paren
l_string|&quot;RPC:      krb5_encrypt returns %d&bslash;n&quot;
comma
id|ret
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|variable|krb5_encrypt
id|EXPORT_SYMBOL
c_func
(paren
id|krb5_encrypt
)paren
suffix:semicolon
id|u32
DECL|function|krb5_decrypt
id|krb5_decrypt
c_func
(paren
r_struct
id|crypto_tfm
op_star
id|tfm
comma
r_void
op_star
id|iv
comma
r_void
op_star
id|in
comma
r_void
op_star
id|out
comma
r_int
id|length
)paren
(brace
id|u32
id|ret
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_struct
id|scatterlist
id|sg
(braket
l_int|1
)braket
suffix:semicolon
id|u8
id|local_iv
(braket
l_int|16
)braket
op_assign
(brace
l_int|0
)brace
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;RPC:      krb5_decrypt: input data:&bslash;n&quot;
)paren
suffix:semicolon
id|print_hexl
c_func
(paren
(paren
id|u32
op_star
)paren
id|in
comma
id|length
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|length
op_mod
id|crypto_tfm_alg_blocksize
c_func
(paren
id|tfm
)paren
op_ne
l_int|0
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|crypto_tfm_alg_ivsize
c_func
(paren
id|tfm
)paren
OG
l_int|16
)paren
(brace
id|dprintk
c_func
(paren
l_string|&quot;RPC:      gss_k5decrypt: tfm iv size to large %d&bslash;n&quot;
comma
id|crypto_tfm_alg_ivsize
c_func
(paren
id|tfm
)paren
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|iv
)paren
id|memcpy
c_func
(paren
id|local_iv
comma
id|iv
comma
id|crypto_tfm_alg_ivsize
c_func
(paren
id|tfm
)paren
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|out
comma
id|in
comma
id|length
)paren
suffix:semicolon
id|sg
(braket
l_int|0
)braket
dot
id|page
op_assign
id|virt_to_page
c_func
(paren
id|out
)paren
suffix:semicolon
id|sg
(braket
l_int|0
)braket
dot
id|offset
op_assign
id|offset_in_page
c_func
(paren
id|out
)paren
suffix:semicolon
id|sg
(braket
l_int|0
)braket
dot
id|length
op_assign
id|length
suffix:semicolon
id|ret
op_assign
id|crypto_cipher_decrypt_iv
c_func
(paren
id|tfm
comma
id|sg
comma
id|sg
comma
id|length
comma
id|local_iv
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;RPC:      krb5_decrypt: output_data:&bslash;n&quot;
)paren
suffix:semicolon
id|print_hexl
c_func
(paren
(paren
id|u32
op_star
)paren
id|out
comma
id|length
comma
l_int|0
)paren
suffix:semicolon
id|out
suffix:colon
id|dprintk
c_func
(paren
l_string|&quot;RPC:      gss_k5decrypt returns %d&bslash;n&quot;
comma
id|ret
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|variable|krb5_decrypt
id|EXPORT_SYMBOL
c_func
(paren
id|krb5_decrypt
)paren
suffix:semicolon
r_void
DECL|function|buf_to_sg
id|buf_to_sg
c_func
(paren
r_struct
id|scatterlist
op_star
id|sg
comma
r_char
op_star
id|ptr
comma
r_int
id|len
)paren
(brace
id|sg-&gt;page
op_assign
id|virt_to_page
c_func
(paren
id|ptr
)paren
suffix:semicolon
id|sg-&gt;offset
op_assign
id|offset_in_page
c_func
(paren
id|ptr
)paren
suffix:semicolon
id|sg-&gt;length
op_assign
id|len
suffix:semicolon
)brace
multiline_comment|/* checksum the plaintext data and hdrlen bytes of the token header */
id|s32
DECL|function|make_checksum
id|make_checksum
c_func
(paren
id|s32
id|cksumtype
comma
r_char
op_star
id|header
comma
r_int
id|hdrlen
comma
r_struct
id|xdr_buf
op_star
id|body
comma
r_struct
id|xdr_netobj
op_star
id|cksum
)paren
(brace
r_char
op_star
id|cksumname
suffix:semicolon
r_struct
id|crypto_tfm
op_star
id|tfm
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* XXX add to ctx? */
r_struct
id|scatterlist
id|sg
(braket
l_int|1
)braket
suffix:semicolon
id|u32
id|code
op_assign
id|GSS_S_FAILURE
suffix:semicolon
r_int
id|len
comma
id|thislen
comma
id|offset
suffix:semicolon
r_int
id|i
suffix:semicolon
r_switch
c_cond
(paren
id|cksumtype
)paren
(brace
r_case
id|CKSUMTYPE_RSA_MD5
suffix:colon
id|cksumname
op_assign
l_string|&quot;md5&quot;
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|dprintk
c_func
(paren
l_string|&quot;RPC:      krb5_make_checksum:&quot;
l_string|&quot; unsupported checksum %d&quot;
comma
id|cksumtype
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|tfm
op_assign
id|crypto_alloc_tfm
c_func
(paren
id|cksumname
comma
l_int|0
)paren
)paren
)paren
r_goto
id|out
suffix:semicolon
id|cksum-&gt;len
op_assign
id|crypto_tfm_alg_digestsize
c_func
(paren
id|tfm
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|cksum-&gt;data
op_assign
id|kmalloc
c_func
(paren
id|cksum-&gt;len
comma
id|GFP_KERNEL
)paren
)paren
op_eq
l_int|NULL
)paren
r_goto
id|out
suffix:semicolon
id|crypto_digest_init
c_func
(paren
id|tfm
)paren
suffix:semicolon
id|buf_to_sg
c_func
(paren
id|sg
comma
id|header
comma
id|hdrlen
)paren
suffix:semicolon
id|crypto_digest_update
c_func
(paren
id|tfm
comma
id|sg
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|body-&gt;head
(braket
l_int|0
)braket
dot
id|iov_len
)paren
(brace
id|buf_to_sg
c_func
(paren
id|sg
comma
id|body-&gt;head
(braket
l_int|0
)braket
dot
id|iov_base
comma
id|body-&gt;head
(braket
l_int|0
)braket
dot
id|iov_len
)paren
suffix:semicolon
id|crypto_digest_update
c_func
(paren
id|tfm
comma
id|sg
comma
l_int|1
)paren
suffix:semicolon
)brace
id|len
op_assign
id|body-&gt;page_len
suffix:semicolon
r_if
c_cond
(paren
id|len
op_ne
l_int|0
)paren
(brace
id|offset
op_assign
id|body-&gt;page_base
op_amp
(paren
id|PAGE_CACHE_SIZE
op_minus
l_int|1
)paren
suffix:semicolon
id|i
op_assign
id|body-&gt;page_base
op_rshift
id|PAGE_CACHE_SHIFT
suffix:semicolon
id|thislen
op_assign
id|PAGE_CACHE_SIZE
op_minus
id|offset
suffix:semicolon
r_do
(brace
r_if
c_cond
(paren
id|thislen
OG
id|len
)paren
id|thislen
op_assign
id|len
suffix:semicolon
id|sg-&gt;page
op_assign
id|body-&gt;pages
(braket
id|i
)braket
suffix:semicolon
id|sg-&gt;offset
op_assign
id|offset
suffix:semicolon
id|sg-&gt;length
op_assign
id|thislen
suffix:semicolon
id|kmap
c_func
(paren
id|sg-&gt;page
)paren
suffix:semicolon
multiline_comment|/* XXX kmap_atomic? */
id|crypto_digest_update
c_func
(paren
id|tfm
comma
id|sg
comma
l_int|1
)paren
suffix:semicolon
id|kunmap
c_func
(paren
id|sg-&gt;page
)paren
suffix:semicolon
id|len
op_sub_assign
id|thislen
suffix:semicolon
id|i
op_increment
suffix:semicolon
id|offset
op_assign
l_int|0
suffix:semicolon
id|thislen
op_assign
id|PAGE_CACHE_SIZE
suffix:semicolon
)brace
r_while
c_loop
(paren
id|len
op_ne
l_int|0
)paren
(brace
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|body-&gt;tail
(braket
l_int|0
)braket
dot
id|iov_len
)paren
(brace
id|buf_to_sg
c_func
(paren
id|sg
comma
id|body-&gt;tail
(braket
l_int|0
)braket
dot
id|iov_base
comma
id|body-&gt;tail
(braket
l_int|0
)braket
dot
id|iov_len
)paren
suffix:semicolon
id|crypto_digest_update
c_func
(paren
id|tfm
comma
id|sg
comma
l_int|1
)paren
suffix:semicolon
)brace
id|crypto_digest_final
c_func
(paren
id|tfm
comma
id|cksum-&gt;data
)paren
suffix:semicolon
id|code
op_assign
l_int|0
suffix:semicolon
id|out
suffix:colon
r_if
c_cond
(paren
id|tfm
)paren
id|crypto_free_tfm
c_func
(paren
id|tfm
)paren
suffix:semicolon
r_return
id|code
suffix:semicolon
)brace
DECL|variable|make_checksum
id|EXPORT_SYMBOL
c_func
(paren
id|make_checksum
)paren
suffix:semicolon
eof
