multiline_comment|/*&n; *  linux/include/linux/sunrpc/gss_asn1.h&n; *&n; *  minimal asn1 for generic encoding/decoding of gss tokens&n; *&n; *  Adapted from MIT Kerberos 5-1.2.1 lib/include/krb5.h,&n; *  lib/gssapi/krb5/gssapiP_krb5.h, and others&n; *&n; *  Copyright (c) 2000 The Regents of the University of Michigan.&n; *  All rights reserved.&n; *&n; *  Andy Adamson   &lt;andros@umich.edu&gt;&n; */
multiline_comment|/*&n; * Copyright 1995 by the Massachusetts Institute of Technology.&n; * All Rights Reserved.&n; *&n; * Export of this software from the United States of America may&n; *   require a specific license from the United States Government.&n; *   It is the responsibility of any person or organization contemplating&n; *   export to obtain such a license before exporting.&n; *&n; * WITHIN THAT CONSTRAINT, permission to use, copy, modify, and&n; * distribute this software and its documentation for any purpose and&n; * without fee is hereby granted, provided that the above copyright&n; * notice appear in all copies and that both that copyright notice and&n; * this permission notice appear in supporting documentation, and that&n; * the name of M.I.T. not be used in advertising or publicity pertaining&n; * to distribution of the software without specific, written prior&n; * permission.  Furthermore if you modify this software you must label&n; * your software as modified software and not distribute it in such a&n; * fashion that it might be confused with the original M.I.T. software.&n; * M.I.T. makes no representations about the suitability of&n; * this software for any purpose.  It is provided &quot;as is&quot; without express&n; * or implied warranty.&n; *&n; */
macro_line|#include &lt;linux/sunrpc/gss_api.h&gt;
DECL|macro|SIZEOF_INT
mdefine_line|#define SIZEOF_INT 4
multiline_comment|/* from gssapi_err_generic.h */
DECL|macro|G_BAD_SERVICE_NAME
mdefine_line|#define G_BAD_SERVICE_NAME                       (-2045022976L)
DECL|macro|G_BAD_STRING_UID
mdefine_line|#define G_BAD_STRING_UID                         (-2045022975L)
DECL|macro|G_NOUSER
mdefine_line|#define G_NOUSER                                 (-2045022974L)
DECL|macro|G_VALIDATE_FAILED
mdefine_line|#define G_VALIDATE_FAILED                        (-2045022973L)
DECL|macro|G_BUFFER_ALLOC
mdefine_line|#define G_BUFFER_ALLOC                           (-2045022972L)
DECL|macro|G_BAD_MSG_CTX
mdefine_line|#define G_BAD_MSG_CTX                            (-2045022971L)
DECL|macro|G_WRONG_SIZE
mdefine_line|#define G_WRONG_SIZE                             (-2045022970L)
DECL|macro|G_BAD_USAGE
mdefine_line|#define G_BAD_USAGE                              (-2045022969L)
DECL|macro|G_UNKNOWN_QOP
mdefine_line|#define G_UNKNOWN_QOP                            (-2045022968L)
DECL|macro|G_NO_HOSTNAME
mdefine_line|#define G_NO_HOSTNAME                            (-2045022967L)
DECL|macro|G_BAD_HOSTNAME
mdefine_line|#define G_BAD_HOSTNAME                           (-2045022966L)
DECL|macro|G_WRONG_MECH
mdefine_line|#define G_WRONG_MECH                             (-2045022965L)
DECL|macro|G_BAD_TOK_HEADER
mdefine_line|#define G_BAD_TOK_HEADER                         (-2045022964L)
DECL|macro|G_BAD_DIRECTION
mdefine_line|#define G_BAD_DIRECTION                          (-2045022963L)
DECL|macro|G_TOK_TRUNC
mdefine_line|#define G_TOK_TRUNC                              (-2045022962L)
DECL|macro|G_REFLECT
mdefine_line|#define G_REFLECT                                (-2045022961L)
DECL|macro|G_WRONG_TOKID
mdefine_line|#define G_WRONG_TOKID                            (-2045022960L)
DECL|macro|g_OID_equal
mdefine_line|#define g_OID_equal(o1,o2) &bslash;&n;   (((o1)-&gt;len == (o2)-&gt;len) &amp;&amp; &bslash;&n;    (memcmp((o1)-&gt;data,(o2)-&gt;data,(int) (o1)-&gt;len) == 0))
id|u32
id|g_verify_token_header
c_func
(paren
r_struct
id|xdr_netobj
op_star
id|mech
comma
r_int
op_star
id|body_size
comma
r_int
r_char
op_star
op_star
id|buf_in
comma
r_int
id|toksize
)paren
suffix:semicolon
r_int
id|g_token_size
c_func
(paren
r_struct
id|xdr_netobj
op_star
id|mech
comma
r_int
r_int
id|body_size
)paren
suffix:semicolon
r_void
id|g_make_token_header
c_func
(paren
r_struct
id|xdr_netobj
op_star
id|mech
comma
r_int
id|body_size
comma
r_int
r_char
op_star
op_star
id|buf
)paren
suffix:semicolon
eof
