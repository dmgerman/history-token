multiline_comment|/*&n; *  linux/include/linux/sunrpc/gss_krb5_types.h&n; *&n; *  Adapted from MIT Kerberos 5-1.2.1 lib/include/krb5.h,&n; *  lib/gssapi/krb5/gssapiP_krb5.h, and others&n; *&n; *  Copyright (c) 2000 The Regents of the University of Michigan.&n; *  All rights reserved.&n; *&n; *  Andy Adamson   &lt;andros@umich.edu&gt;&n; *  Bruce Fields   &lt;bfields@umich.edu&gt;&n; */
multiline_comment|/*&n; * Copyright 1995 by the Massachusetts Institute of Technology.&n; * All Rights Reserved.&n; *&n; * Export of this software from the United States of America may&n; *   require a specific license from the United States Government.&n; *   It is the responsibility of any person or organization contemplating&n; *   export to obtain such a license before exporting.&n; *&n; * WITHIN THAT CONSTRAINT, permission to use, copy, modify, and&n; * distribute this software and its documentation for any purpose and&n; * without fee is hereby granted, provided that the above copyright&n; * notice appear in all copies and that both that copyright notice and&n; * this permission notice appear in supporting documentation, and that&n; * the name of M.I.T. not be used in advertising or publicity pertaining&n; * to distribution of the software without specific, written prior&n; * permission.  Furthermore if you modify this software you must label&n; * your software as modified software and not distribute it in such a&n; * fashion that it might be confused with the original M.I.T. software.&n; * M.I.T. makes no representations about the suitability of&n; * this software for any purpose.  It is provided &quot;as is&quot; without express&n; * or implied warranty.&n; *&n; */
macro_line|#include &lt;linux/sunrpc/auth_gss.h&gt;
macro_line|#include &lt;linux/sunrpc/gss_err.h&gt;
macro_line|#include &lt;linux/sunrpc/gss_asn1.h&gt;
DECL|struct|krb5_ctx
r_struct
id|krb5_ctx
(brace
DECL|member|initiate
r_int
id|initiate
suffix:semicolon
multiline_comment|/* 1 = initiating, 0 = accepting */
DECL|member|seed_init
r_int
id|seed_init
suffix:semicolon
DECL|member|seed
r_int
r_char
id|seed
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|signalg
r_int
id|signalg
suffix:semicolon
DECL|member|sealalg
r_int
id|sealalg
suffix:semicolon
DECL|member|enc
r_struct
id|crypto_tfm
op_star
id|enc
suffix:semicolon
DECL|member|seq
r_struct
id|crypto_tfm
op_star
id|seq
suffix:semicolon
DECL|member|endtime
id|s32
id|endtime
suffix:semicolon
DECL|member|seq_send
id|u32
id|seq_send
suffix:semicolon
DECL|member|seq_recv
id|u32
id|seq_recv
suffix:semicolon
DECL|member|mech_used
r_struct
id|xdr_netobj
id|mech_used
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|KG_TOK_MIC_MSG
mdefine_line|#define KG_TOK_MIC_MSG    0x0101
DECL|macro|KG_TOK_WRAP_MSG
mdefine_line|#define KG_TOK_WRAP_MSG   0x0201
DECL|enum|sgn_alg
r_enum
id|sgn_alg
(brace
DECL|enumerator|SGN_ALG_DES_MAC_MD5
id|SGN_ALG_DES_MAC_MD5
op_assign
l_int|0x0000
comma
DECL|enumerator|SGN_ALG_MD2_5
id|SGN_ALG_MD2_5
op_assign
l_int|0x0001
comma
DECL|enumerator|SGN_ALG_DES_MAC
id|SGN_ALG_DES_MAC
op_assign
l_int|0x0002
comma
DECL|enumerator|SGN_ALG_3
id|SGN_ALG_3
op_assign
l_int|0x0003
comma
multiline_comment|/* not published */
DECL|enumerator|SGN_ALG_HMAC_MD5
id|SGN_ALG_HMAC_MD5
op_assign
l_int|0x0011
comma
multiline_comment|/* microsoft w2k; no support */
DECL|enumerator|SGN_ALG_HMAC_SHA1_DES3_KD
id|SGN_ALG_HMAC_SHA1_DES3_KD
op_assign
l_int|0x0004
)brace
suffix:semicolon
DECL|enum|seal_alg
r_enum
id|seal_alg
(brace
DECL|enumerator|SEAL_ALG_NONE
id|SEAL_ALG_NONE
op_assign
l_int|0xffff
comma
DECL|enumerator|SEAL_ALG_DES
id|SEAL_ALG_DES
op_assign
l_int|0x0000
comma
DECL|enumerator|SEAL_ALG_1
id|SEAL_ALG_1
op_assign
l_int|0x0001
comma
multiline_comment|/* not published */
DECL|enumerator|SEAL_ALG_MICROSOFT_RC4
id|SEAL_ALG_MICROSOFT_RC4
op_assign
l_int|0x0010
comma
multiline_comment|/* microsoft w2k; no support */
DECL|enumerator|SEAL_ALG_DES3KD
id|SEAL_ALG_DES3KD
op_assign
l_int|0x0002
)brace
suffix:semicolon
DECL|macro|RSA_MD5_CKSUM_LENGTH
mdefine_line|#define RSA_MD5_CKSUM_LENGTH 16
DECL|macro|CKSUMTYPE_CRC32
mdefine_line|#define CKSUMTYPE_CRC32&t;&t;&t;0x0001
DECL|macro|CKSUMTYPE_RSA_MD4
mdefine_line|#define CKSUMTYPE_RSA_MD4&t;&t;0x0002
DECL|macro|CKSUMTYPE_RSA_MD4_DES
mdefine_line|#define CKSUMTYPE_RSA_MD4_DES&t;&t;0x0003
DECL|macro|CKSUMTYPE_DESCBC
mdefine_line|#define CKSUMTYPE_DESCBC&t;&t;0x0004
DECL|macro|CKSUMTYPE_RSA_MD5
mdefine_line|#define CKSUMTYPE_RSA_MD5&t;&t;0x0007
DECL|macro|CKSUMTYPE_RSA_MD5_DES
mdefine_line|#define CKSUMTYPE_RSA_MD5_DES&t;&t;0x0008
DECL|macro|CKSUMTYPE_NIST_SHA
mdefine_line|#define CKSUMTYPE_NIST_SHA&t;&t;0x0009
DECL|macro|CKSUMTYPE_HMAC_SHA1_DES3
mdefine_line|#define CKSUMTYPE_HMAC_SHA1_DES3&t;0x000c
multiline_comment|/* from gssapi_err_krb5.h */
DECL|macro|KG_CCACHE_NOMATCH
mdefine_line|#define KG_CCACHE_NOMATCH                        (39756032L)
DECL|macro|KG_KEYTAB_NOMATCH
mdefine_line|#define KG_KEYTAB_NOMATCH                        (39756033L)
DECL|macro|KG_TGT_MISSING
mdefine_line|#define KG_TGT_MISSING                           (39756034L)
DECL|macro|KG_NO_SUBKEY
mdefine_line|#define KG_NO_SUBKEY                             (39756035L)
DECL|macro|KG_CONTEXT_ESTABLISHED
mdefine_line|#define KG_CONTEXT_ESTABLISHED                   (39756036L)
DECL|macro|KG_BAD_SIGN_TYPE
mdefine_line|#define KG_BAD_SIGN_TYPE                         (39756037L)
DECL|macro|KG_BAD_LENGTH
mdefine_line|#define KG_BAD_LENGTH                            (39756038L)
DECL|macro|KG_CTX_INCOMPLETE
mdefine_line|#define KG_CTX_INCOMPLETE                        (39756039L)
DECL|macro|KG_CONTEXT
mdefine_line|#define KG_CONTEXT                               (39756040L)
DECL|macro|KG_CRED
mdefine_line|#define KG_CRED                                  (39756041L)
DECL|macro|KG_ENC_DESC
mdefine_line|#define KG_ENC_DESC                              (39756042L)
DECL|macro|KG_BAD_SEQ
mdefine_line|#define KG_BAD_SEQ                               (39756043L)
DECL|macro|KG_EMPTY_CCACHE
mdefine_line|#define KG_EMPTY_CCACHE                          (39756044L)
DECL|macro|KG_NO_CTYPES
mdefine_line|#define KG_NO_CTYPES                             (39756045L)
DECL|macro|KV5M_PRINCIPAL
mdefine_line|#define KV5M_PRINCIPAL                           (-1760647423L)
DECL|macro|KV5M_KEYBLOCK
mdefine_line|#define KV5M_KEYBLOCK                            (-1760647421L)
DECL|macro|KV5M_CHECKSUM
mdefine_line|#define KV5M_CHECKSUM                            (-1760647420L)
DECL|macro|KV5M_ADDRESS
mdefine_line|#define KV5M_ADDRESS                             (-1760647390L)
DECL|macro|KV5M_AUTHENTICATOR
mdefine_line|#define KV5M_AUTHENTICATOR                       (-1760647410L)
DECL|macro|KV5M_AUTH_CONTEXT
mdefine_line|#define KV5M_AUTH_CONTEXT                        (-1760647383L)
DECL|macro|KV5M_AUTHDATA
mdefine_line|#define KV5M_AUTHDATA                            (-1760647414L)
DECL|macro|KV5M_GSS_OID
mdefine_line|#define KV5M_GSS_OID                             (-1760647372L)
DECL|macro|KV5M_GSS_QUEUE
mdefine_line|#define KV5M_GSS_QUEUE                           (-1760647371L)
multiline_comment|/* per Kerberos v5 protocol spec crypto types from the wire. &n; * these get mapped to linux kernel crypto routines.  &n; */
DECL|macro|ENCTYPE_NULL
mdefine_line|#define ENCTYPE_NULL            0x0000
DECL|macro|ENCTYPE_DES_CBC_CRC
mdefine_line|#define ENCTYPE_DES_CBC_CRC     0x0001&t;/* DES cbc mode with CRC-32 */
DECL|macro|ENCTYPE_DES_CBC_MD4
mdefine_line|#define ENCTYPE_DES_CBC_MD4     0x0002&t;/* DES cbc mode with RSA-MD4 */
DECL|macro|ENCTYPE_DES_CBC_MD5
mdefine_line|#define ENCTYPE_DES_CBC_MD5     0x0003&t;/* DES cbc mode with RSA-MD5 */
DECL|macro|ENCTYPE_DES_CBC_RAW
mdefine_line|#define ENCTYPE_DES_CBC_RAW     0x0004&t;/* DES cbc mode raw */
multiline_comment|/* XXX deprecated? */
DECL|macro|ENCTYPE_DES3_CBC_SHA
mdefine_line|#define ENCTYPE_DES3_CBC_SHA    0x0005&t;/* DES-3 cbc mode with NIST-SHA */
DECL|macro|ENCTYPE_DES3_CBC_RAW
mdefine_line|#define ENCTYPE_DES3_CBC_RAW    0x0006&t;/* DES-3 cbc mode raw */
DECL|macro|ENCTYPE_DES_HMAC_SHA1
mdefine_line|#define ENCTYPE_DES_HMAC_SHA1   0x0008
DECL|macro|ENCTYPE_DES3_CBC_SHA1
mdefine_line|#define ENCTYPE_DES3_CBC_SHA1   0x0010
DECL|macro|ENCTYPE_UNKNOWN
mdefine_line|#define ENCTYPE_UNKNOWN         0x01ff
id|s32
id|krb5_make_checksum
c_func
(paren
id|s32
id|cksumtype
comma
r_struct
id|xdr_netobj
op_star
id|input
comma
r_struct
id|xdr_netobj
op_star
id|cksum
)paren
suffix:semicolon
id|u32
id|krb5_make_token
c_func
(paren
r_struct
id|krb5_ctx
op_star
id|context_handle
comma
r_int
id|qop_req
comma
r_struct
id|xdr_netobj
op_star
id|input_message_buffer
comma
r_struct
id|xdr_netobj
op_star
id|output_message_buffer
comma
r_int
id|toktype
)paren
suffix:semicolon
id|u32
id|krb5_read_token
c_func
(paren
r_struct
id|krb5_ctx
op_star
id|context_handle
comma
r_struct
id|xdr_netobj
op_star
id|input_token_buffer
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
suffix:semicolon
id|u32
id|krb5_encrypt
c_func
(paren
r_struct
id|crypto_tfm
op_star
id|key
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
suffix:semicolon
id|u32
id|krb5_decrypt
c_func
(paren
r_struct
id|crypto_tfm
op_star
id|key
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
suffix:semicolon
id|s32
id|krb5_make_seq_num
c_func
(paren
r_struct
id|crypto_tfm
op_star
id|key
comma
r_int
id|direction
comma
id|s32
id|seqnum
comma
r_int
r_char
op_star
id|cksum
comma
r_int
r_char
op_star
id|buf
)paren
suffix:semicolon
id|s32
id|krb5_get_seq_num
c_func
(paren
r_struct
id|crypto_tfm
op_star
id|key
comma
r_int
r_char
op_star
id|cksum
comma
r_int
r_char
op_star
id|buf
comma
r_int
op_star
id|direction
comma
id|s32
op_star
id|seqnum
)paren
suffix:semicolon
eof
