multiline_comment|/*&n; *  linux/net/sunrpc/gss_krb5_unseal.c&n; *&n; *  Adapted from MIT Kerberos 5-1.2.1 lib/gssapi/krb5/k5unseal.c&n; *&n; *  Copyright (c) 2000 The Regents of the University of Michigan.&n; *  All rights reserved.&n; *&n; *  Andy Adamson   &lt;andros@umich.edu&gt;&n; */
multiline_comment|/*&n; * Copyright 1993 by OpenVision Technologies, Inc.&n; *&n; * Permission to use, copy, modify, distribute, and sell this software&n; * and its documentation for any purpose is hereby granted without fee,&n; * provided that the above copyright notice appears in all copies and&n; * that both that copyright notice and this permission notice appear in&n; * supporting documentation, and that the name of OpenVision not be used&n; * in advertising or publicity pertaining to distribution of the software&n; * without specific, written prior permission. OpenVision makes no&n; * representations about the suitability of this software for any&n; * purpose.  It is provided &quot;as is&quot; without express or implied warranty.&n; *&n; * OPENVISION DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,&n; * INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO&n; * EVENT SHALL OPENVISION BE LIABLE FOR ANY SPECIAL, INDIRECT OR&n; * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF&n; * USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR&n; * OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR&n; * PERFORMANCE OF THIS SOFTWARE.&n; */
multiline_comment|/*&n; * Copyright (C) 1998 by the FundsXpress, INC.&n; *&n; * All rights reserved.&n; *&n; * Export of this software from the United States of America may require&n; * a specific license from the United States Government.  It is the&n; * responsibility of any person or organization contemplating export to&n; * obtain such a license before exporting.&n; *&n; * WITHIN THAT CONSTRAINT, permission to use, copy, modify, and&n; * distribute this software and its documentation for any purpose and&n; * without fee is hereby granted, provided that the above copyright&n; * notice appear in all copies and that both that copyright notice and&n; * this permission notice appear in supporting documentation, and that&n; * the name of FundsXpress. not be used in advertising or publicity pertaining&n; * to distribution of the software without specific, written prior&n; * permission.  FundsXpress makes no representations about the suitability of&n; * this software for any purpose.  It is provided &quot;as is&quot; without express&n; * or implied warranty.&n; *&n; * THIS SOFTWARE IS PROVIDED ``AS IS&squot;&squot; AND WITHOUT ANY EXPRESS OR&n; * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED&n; * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/jiffies.h&gt;
macro_line|#include &lt;linux/sunrpc/gss_krb5.h&gt;
macro_line|#include &lt;linux/crypto.h&gt;
macro_line|#ifdef RPC_DEBUG
DECL|macro|RPCDBG_FACILITY
macro_line|# define RPCDBG_FACILITY        RPCDBG_AUTH
macro_line|#endif
multiline_comment|/* message_buffer is an input if toktype is MIC and an output if it is WRAP:&n; * If toktype is MIC: read_token is a mic token, and message_buffer is the&n; *   data that the mic was supposedly taken over.&n; * If toktype is WRAP: read_token is a wrap token, and message_buffer is used&n; *   to return the decrypted data.&n; */
id|u32
DECL|function|krb5_read_token
id|krb5_read_token
c_func
(paren
r_struct
id|krb5_ctx
op_star
id|ctx
comma
r_struct
id|xdr_netobj
op_star
id|read_token
comma
r_struct
id|xdr_netobj
op_star
id|message_buffer
comma
r_int
op_star
id|qop_state
comma
r_int
id|toktype
)paren
(brace
r_int
id|signalg
suffix:semicolon
r_int
id|sealalg
suffix:semicolon
r_struct
id|xdr_netobj
id|token
op_assign
(brace
dot
id|len
op_assign
l_int|0
comma
dot
id|data
op_assign
l_int|NULL
)brace
suffix:semicolon
id|s32
id|checksum_type
suffix:semicolon
r_struct
id|xdr_netobj
id|md5cksum
op_assign
(brace
dot
id|len
op_assign
l_int|0
comma
dot
id|data
op_assign
l_int|NULL
)brace
suffix:semicolon
id|s32
id|now
suffix:semicolon
r_int
r_char
op_star
id|plain
op_assign
l_int|NULL
suffix:semicolon
r_int
id|plainlen
op_assign
l_int|0
suffix:semicolon
r_int
id|direction
suffix:semicolon
id|s32
id|seqnum
suffix:semicolon
r_int
r_char
op_star
id|ptr
op_assign
(paren
r_int
r_char
op_star
)paren
id|read_token-&gt;data
suffix:semicolon
r_int
id|bodysize
suffix:semicolon
id|u32
id|ret
op_assign
id|GSS_S_DEFECTIVE_TOKEN
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;RPC:      krb5_read_token&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|g_verify_token_header
c_func
(paren
op_amp
id|ctx-&gt;mech_used
comma
op_amp
id|bodysize
comma
op_amp
id|ptr
comma
id|toktype
comma
id|read_token-&gt;len
)paren
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|toktype
op_eq
id|KG_TOK_WRAP_MSG
)paren
(brace
id|message_buffer-&gt;len
op_assign
l_int|0
suffix:semicolon
id|message_buffer-&gt;data
op_assign
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* get the sign and seal algorithms */
id|signalg
op_assign
id|ptr
(braket
l_int|0
)braket
op_plus
(paren
id|ptr
(braket
l_int|1
)braket
op_lshift
l_int|8
)paren
suffix:semicolon
id|sealalg
op_assign
id|ptr
(braket
l_int|2
)braket
op_plus
(paren
id|ptr
(braket
l_int|3
)braket
op_lshift
l_int|8
)paren
suffix:semicolon
multiline_comment|/* Sanity checks */
r_if
c_cond
(paren
(paren
id|ptr
(braket
l_int|4
)braket
op_ne
l_int|0xff
)paren
op_logical_or
(paren
id|ptr
(braket
l_int|5
)braket
op_ne
l_int|0xff
)paren
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
id|toktype
op_ne
id|KG_TOK_WRAP_MSG
)paren
op_logical_and
(paren
id|sealalg
op_ne
l_int|0xffff
)paren
)paren
op_logical_or
(paren
(paren
id|toktype
op_eq
id|KG_TOK_WRAP_MSG
)paren
op_logical_and
(paren
id|sealalg
op_eq
l_int|0xffff
)paren
)paren
)paren
r_goto
id|out
suffix:semicolon
multiline_comment|/* in the current spec, there is only one valid seal algorithm per&n;&t;   key type, so a simple comparison is ok */
r_if
c_cond
(paren
(paren
id|toktype
op_eq
id|KG_TOK_WRAP_MSG
)paren
op_logical_and
op_logical_neg
(paren
id|sealalg
op_eq
id|ctx-&gt;sealalg
)paren
)paren
r_goto
id|out
suffix:semicolon
multiline_comment|/* there are several mappings of seal algorithms to sign algorithms,&n;&t;   but few enough that we can try them all. */
r_if
c_cond
(paren
(paren
id|ctx-&gt;sealalg
op_eq
id|SEAL_ALG_NONE
op_logical_and
id|signalg
OG
l_int|1
)paren
op_logical_or
(paren
id|ctx-&gt;sealalg
op_eq
id|SEAL_ALG_1
op_logical_and
id|signalg
op_ne
id|SGN_ALG_3
)paren
op_logical_or
(paren
id|ctx-&gt;sealalg
op_eq
id|SEAL_ALG_DES3KD
op_logical_and
id|signalg
op_ne
id|SGN_ALG_HMAC_SHA1_DES3_KD
)paren
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|toktype
op_eq
id|KG_TOK_WRAP_MSG
)paren
(brace
r_int
id|conflen
op_assign
id|crypto_tfm_alg_blocksize
c_func
(paren
id|ctx-&gt;enc
)paren
suffix:semicolon
r_int
id|padlen
suffix:semicolon
id|plainlen
op_assign
id|bodysize
op_minus
(paren
l_int|14
op_plus
id|KRB5_CKSUM_LENGTH
)paren
suffix:semicolon
id|plain
op_assign
id|ptr
op_plus
l_int|14
op_plus
id|KRB5_CKSUM_LENGTH
suffix:semicolon
id|ret
op_assign
id|krb5_decrypt
c_func
(paren
id|ctx-&gt;enc
comma
l_int|NULL
comma
id|plain
comma
id|plain
comma
id|plainlen
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_goto
id|out
suffix:semicolon
id|ret
op_assign
id|GSS_S_FAILURE
suffix:semicolon
id|padlen
op_assign
id|plain
(braket
id|plainlen
op_minus
l_int|1
)braket
suffix:semicolon
r_if
c_cond
(paren
(paren
id|padlen
OL
l_int|1
)paren
op_logical_or
(paren
id|padlen
OG
l_int|8
)paren
)paren
r_goto
id|out
suffix:semicolon
id|token.len
op_assign
id|plainlen
op_minus
id|conflen
op_minus
id|padlen
suffix:semicolon
r_if
c_cond
(paren
id|token.len
)paren
(brace
id|token.data
op_assign
id|kmalloc
c_func
(paren
id|token.len
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|token.data
op_eq
l_int|NULL
)paren
r_goto
id|out
suffix:semicolon
id|memcpy
c_func
(paren
id|token.data
comma
id|plain
op_plus
id|conflen
comma
id|token.len
)paren
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|toktype
op_eq
id|KG_TOK_MIC_MSG
)paren
(brace
id|token
op_assign
op_star
id|message_buffer
suffix:semicolon
id|plain
op_assign
id|token.data
suffix:semicolon
id|plainlen
op_assign
id|token.len
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
l_string|&quot;RPC: bad toktype in krb5_read_token&quot;
)paren
suffix:semicolon
id|ret
op_assign
id|GSS_S_FAILURE
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|dprintk
c_func
(paren
l_string|&quot;RPC krb5_read_token: token.len %d plainlen %d&bslash;n&quot;
comma
id|token.len
comma
id|plainlen
)paren
suffix:semicolon
multiline_comment|/* compute the checksum of the message */
multiline_comment|/* initialize the the cksum */
r_switch
c_cond
(paren
id|signalg
)paren
(brace
r_case
id|SGN_ALG_DES_MAC_MD5
suffix:colon
id|checksum_type
op_assign
id|CKSUMTYPE_RSA_MD5
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|ret
op_assign
id|GSS_S_DEFECTIVE_TOKEN
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|signalg
)paren
(brace
r_case
id|SGN_ALG_DES_MAC_MD5
suffix:colon
id|ret
op_assign
id|krb5_make_checksum
c_func
(paren
id|checksum_type
comma
id|ptr
op_minus
l_int|2
comma
id|plain
comma
id|plainlen
comma
op_amp
id|md5cksum
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_goto
id|out
suffix:semicolon
id|ret
op_assign
id|krb5_encrypt
c_func
(paren
id|ctx-&gt;seq
comma
l_int|NULL
comma
id|md5cksum.data
comma
id|md5cksum.data
comma
l_int|16
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|memcmp
c_func
(paren
id|md5cksum.data
op_plus
l_int|8
comma
id|ptr
op_plus
l_int|14
comma
l_int|8
)paren
)paren
(brace
id|ret
op_assign
id|GSS_S_BAD_SIG
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_break
suffix:semicolon
r_default
suffix:colon
id|ret
op_assign
id|GSS_S_DEFECTIVE_TOKEN
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/* it got through unscathed.  Make sure the context is unexpired */
r_if
c_cond
(paren
id|toktype
op_eq
id|KG_TOK_WRAP_MSG
)paren
op_star
id|message_buffer
op_assign
id|token
suffix:semicolon
r_if
c_cond
(paren
id|qop_state
)paren
op_star
id|qop_state
op_assign
id|GSS_C_QOP_DEFAULT
suffix:semicolon
id|now
op_assign
id|jiffies
suffix:semicolon
id|ret
op_assign
id|GSS_S_CONTEXT_EXPIRED
suffix:semicolon
r_if
c_cond
(paren
id|now
OG
id|ctx-&gt;endtime
)paren
r_goto
id|out
suffix:semicolon
multiline_comment|/* do sequencing checks */
id|ret
op_assign
id|GSS_S_BAD_SIG
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|krb5_get_seq_num
c_func
(paren
id|ctx-&gt;seq
comma
id|ptr
op_plus
l_int|14
comma
id|ptr
op_plus
l_int|6
comma
op_amp
id|direction
comma
op_amp
id|seqnum
)paren
)paren
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ctx-&gt;initiate
op_logical_and
id|direction
op_ne
l_int|0xff
)paren
op_logical_or
(paren
op_logical_neg
id|ctx-&gt;initiate
op_logical_and
id|direction
op_ne
l_int|0
)paren
)paren
r_goto
id|out
suffix:semicolon
id|ret
op_assign
id|GSS_S_COMPLETE
suffix:semicolon
id|out
suffix:colon
r_if
c_cond
(paren
id|md5cksum.data
)paren
id|kfree
c_func
(paren
id|md5cksum.data
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|toktype
op_eq
id|KG_TOK_WRAP_MSG
)paren
op_logical_and
id|ret
op_logical_and
id|token.data
)paren
id|kfree
c_func
(paren
id|token.data
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
eof
