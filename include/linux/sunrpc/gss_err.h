multiline_comment|/*&n; *  linux/include/sunrpc/gss_err.h&n; *&n; *  Adapted from MIT Kerberos 5-1.2.1 include/gssapi/gssapi.h&n; *&n; *  Copyright (c) 2002 The Regents of the University of Michigan.&n; *  All rights reserved.&n; *&n; *  Andy Adamson   &lt;andros@umich.edu&gt;&n; */
multiline_comment|/*&n; * Copyright 1993 by OpenVision Technologies, Inc.&n; * &n; * Permission to use, copy, modify, distribute, and sell this software&n; * and its documentation for any purpose is hereby granted without fee,&n; * provided that the above copyright notice appears in all copies and&n; * that both that copyright notice and this permission notice appear in&n; * supporting documentation, and that the name of OpenVision not be used&n; * in advertising or publicity pertaining to distribution of the software&n; * without specific, written prior permission. OpenVision makes no&n; * representations about the suitability of this software for any&n; * purpose.  It is provided &quot;as is&quot; without express or implied warranty.&n; * &n; * OPENVISION DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,&n; * INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO&n; * EVENT SHALL OPENVISION BE LIABLE FOR ANY SPECIAL, INDIRECT OR&n; * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF&n; * USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR&n; * OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR&n; * PERFORMANCE OF THIS SOFTWARE.&n; */
macro_line|#ifndef _LINUX_SUNRPC_GSS_ERR_H
DECL|macro|_LINUX_SUNRPC_GSS_ERR_H
mdefine_line|#define _LINUX_SUNRPC_GSS_ERR_H
macro_line|#ifdef __KERNEL__
DECL|typedef|OM_uint32
r_typedef
r_int
r_int
id|OM_uint32
suffix:semicolon
multiline_comment|/*&n; * Flag bits for context-level services.&n; */
DECL|macro|GSS_C_DELEG_FLAG
mdefine_line|#define GSS_C_DELEG_FLAG 1
DECL|macro|GSS_C_MUTUAL_FLAG
mdefine_line|#define GSS_C_MUTUAL_FLAG 2
DECL|macro|GSS_C_REPLAY_FLAG
mdefine_line|#define GSS_C_REPLAY_FLAG 4
DECL|macro|GSS_C_SEQUENCE_FLAG
mdefine_line|#define GSS_C_SEQUENCE_FLAG 8
DECL|macro|GSS_C_CONF_FLAG
mdefine_line|#define GSS_C_CONF_FLAG 16
DECL|macro|GSS_C_INTEG_FLAG
mdefine_line|#define GSS_C_INTEG_FLAG 32
DECL|macro|GSS_C_ANON_FLAG
mdefine_line|#define&t;GSS_C_ANON_FLAG 64
DECL|macro|GSS_C_PROT_READY_FLAG
mdefine_line|#define GSS_C_PROT_READY_FLAG 128
DECL|macro|GSS_C_TRANS_FLAG
mdefine_line|#define GSS_C_TRANS_FLAG 256
multiline_comment|/*&n; * Credential usage options&n; */
DECL|macro|GSS_C_BOTH
mdefine_line|#define GSS_C_BOTH 0
DECL|macro|GSS_C_INITIATE
mdefine_line|#define GSS_C_INITIATE 1
DECL|macro|GSS_C_ACCEPT
mdefine_line|#define GSS_C_ACCEPT 2
multiline_comment|/*&n; * Status code types for gss_display_status&n; */
DECL|macro|GSS_C_GSS_CODE
mdefine_line|#define GSS_C_GSS_CODE 1
DECL|macro|GSS_C_MECH_CODE
mdefine_line|#define GSS_C_MECH_CODE 2
multiline_comment|/*&n; * Define the default Quality of Protection for per-message services.  Note&n; * that an implementation that offers multiple levels of QOP may either reserve&n; * a value (for example zero, as assumed here) to mean &quot;default protection&quot;, or&n; * alternatively may simply equate GSS_C_QOP_DEFAULT to a specific explicit&n; * QOP value.  However a value of 0 should always be interpreted by a GSSAPI&n; * implementation as a request for the default protection level.&n; */
DECL|macro|GSS_C_QOP_DEFAULT
mdefine_line|#define GSS_C_QOP_DEFAULT 0
multiline_comment|/*&n; * Expiration time of 2^32-1 seconds means infinite lifetime for a&n; * credential or security context&n; */
DECL|macro|GSS_C_INDEFINITE
mdefine_line|#define GSS_C_INDEFINITE ((OM_uint32) 0xfffffffful)
multiline_comment|/* Major status codes */
DECL|macro|GSS_S_COMPLETE
mdefine_line|#define GSS_S_COMPLETE 0
multiline_comment|/*&n; * Some &quot;helper&quot; definitions to make the status code macros obvious.&n; */
DECL|macro|GSS_C_CALLING_ERROR_OFFSET
mdefine_line|#define GSS_C_CALLING_ERROR_OFFSET 24
DECL|macro|GSS_C_ROUTINE_ERROR_OFFSET
mdefine_line|#define GSS_C_ROUTINE_ERROR_OFFSET 16
DECL|macro|GSS_C_SUPPLEMENTARY_OFFSET
mdefine_line|#define GSS_C_SUPPLEMENTARY_OFFSET 0
DECL|macro|GSS_C_CALLING_ERROR_MASK
mdefine_line|#define GSS_C_CALLING_ERROR_MASK ((OM_uint32) 0377ul)
DECL|macro|GSS_C_ROUTINE_ERROR_MASK
mdefine_line|#define GSS_C_ROUTINE_ERROR_MASK ((OM_uint32) 0377ul)
DECL|macro|GSS_C_SUPPLEMENTARY_MASK
mdefine_line|#define GSS_C_SUPPLEMENTARY_MASK ((OM_uint32) 0177777ul)
multiline_comment|/*&n; * The macros that test status codes for error conditions.  Note that the&n; * GSS_ERROR() macro has changed slightly from the V1 GSSAPI so that it now&n; * evaluates its argument only once.&n; */
DECL|macro|GSS_CALLING_ERROR
mdefine_line|#define GSS_CALLING_ERROR(x) &bslash;&n;  ((x) &amp; (GSS_C_CALLING_ERROR_MASK &lt;&lt; GSS_C_CALLING_ERROR_OFFSET))
DECL|macro|GSS_ROUTINE_ERROR
mdefine_line|#define GSS_ROUTINE_ERROR(x) &bslash;&n;  ((x) &amp; (GSS_C_ROUTINE_ERROR_MASK &lt;&lt; GSS_C_ROUTINE_ERROR_OFFSET))
DECL|macro|GSS_SUPPLEMENTARY_INFO
mdefine_line|#define GSS_SUPPLEMENTARY_INFO(x) &bslash;&n;  ((x) &amp; (GSS_C_SUPPLEMENTARY_MASK &lt;&lt; GSS_C_SUPPLEMENTARY_OFFSET))
DECL|macro|GSS_ERROR
mdefine_line|#define GSS_ERROR(x) &bslash;&n;  ((x) &amp; ((GSS_C_CALLING_ERROR_MASK &lt;&lt; GSS_C_CALLING_ERROR_OFFSET) | &bslash;&n;&t;  (GSS_C_ROUTINE_ERROR_MASK &lt;&lt; GSS_C_ROUTINE_ERROR_OFFSET)))
multiline_comment|/*&n; * Now the actual status code definitions&n; */
multiline_comment|/*&n; * Calling errors:&n; */
DECL|macro|GSS_S_CALL_INACCESSIBLE_READ
mdefine_line|#define GSS_S_CALL_INACCESSIBLE_READ &bslash;&n;                             (((OM_uint32) 1ul) &lt;&lt; GSS_C_CALLING_ERROR_OFFSET)
DECL|macro|GSS_S_CALL_INACCESSIBLE_WRITE
mdefine_line|#define GSS_S_CALL_INACCESSIBLE_WRITE &bslash;&n;                             (((OM_uint32) 2ul) &lt;&lt; GSS_C_CALLING_ERROR_OFFSET)
DECL|macro|GSS_S_CALL_BAD_STRUCTURE
mdefine_line|#define GSS_S_CALL_BAD_STRUCTURE &bslash;&n;                             (((OM_uint32) 3ul) &lt;&lt; GSS_C_CALLING_ERROR_OFFSET)
multiline_comment|/*&n; * Routine errors:&n; */
DECL|macro|GSS_S_BAD_MECH
mdefine_line|#define GSS_S_BAD_MECH (((OM_uint32) 1ul) &lt;&lt; GSS_C_ROUTINE_ERROR_OFFSET)
DECL|macro|GSS_S_BAD_NAME
mdefine_line|#define GSS_S_BAD_NAME (((OM_uint32) 2ul) &lt;&lt; GSS_C_ROUTINE_ERROR_OFFSET)
DECL|macro|GSS_S_BAD_NAMETYPE
mdefine_line|#define GSS_S_BAD_NAMETYPE (((OM_uint32) 3ul) &lt;&lt; GSS_C_ROUTINE_ERROR_OFFSET)
DECL|macro|GSS_S_BAD_BINDINGS
mdefine_line|#define GSS_S_BAD_BINDINGS (((OM_uint32) 4ul) &lt;&lt; GSS_C_ROUTINE_ERROR_OFFSET)
DECL|macro|GSS_S_BAD_STATUS
mdefine_line|#define GSS_S_BAD_STATUS (((OM_uint32) 5ul) &lt;&lt; GSS_C_ROUTINE_ERROR_OFFSET)
DECL|macro|GSS_S_BAD_SIG
mdefine_line|#define GSS_S_BAD_SIG (((OM_uint32) 6ul) &lt;&lt; GSS_C_ROUTINE_ERROR_OFFSET)
DECL|macro|GSS_S_NO_CRED
mdefine_line|#define GSS_S_NO_CRED (((OM_uint32) 7ul) &lt;&lt; GSS_C_ROUTINE_ERROR_OFFSET)
DECL|macro|GSS_S_NO_CONTEXT
mdefine_line|#define GSS_S_NO_CONTEXT (((OM_uint32) 8ul) &lt;&lt; GSS_C_ROUTINE_ERROR_OFFSET)
DECL|macro|GSS_S_DEFECTIVE_TOKEN
mdefine_line|#define GSS_S_DEFECTIVE_TOKEN (((OM_uint32) 9ul) &lt;&lt; GSS_C_ROUTINE_ERROR_OFFSET)
DECL|macro|GSS_S_DEFECTIVE_CREDENTIAL
mdefine_line|#define GSS_S_DEFECTIVE_CREDENTIAL &bslash;&n;     (((OM_uint32) 10ul) &lt;&lt; GSS_C_ROUTINE_ERROR_OFFSET)
DECL|macro|GSS_S_CREDENTIALS_EXPIRED
mdefine_line|#define GSS_S_CREDENTIALS_EXPIRED &bslash;&n;     (((OM_uint32) 11ul) &lt;&lt; GSS_C_ROUTINE_ERROR_OFFSET)
DECL|macro|GSS_S_CONTEXT_EXPIRED
mdefine_line|#define GSS_S_CONTEXT_EXPIRED &bslash;&n;     (((OM_uint32) 12ul) &lt;&lt; GSS_C_ROUTINE_ERROR_OFFSET)
DECL|macro|GSS_S_FAILURE
mdefine_line|#define GSS_S_FAILURE (((OM_uint32) 13ul) &lt;&lt; GSS_C_ROUTINE_ERROR_OFFSET)
DECL|macro|GSS_S_BAD_QOP
mdefine_line|#define GSS_S_BAD_QOP (((OM_uint32) 14ul) &lt;&lt; GSS_C_ROUTINE_ERROR_OFFSET)
DECL|macro|GSS_S_UNAUTHORIZED
mdefine_line|#define GSS_S_UNAUTHORIZED (((OM_uint32) 15ul) &lt;&lt; GSS_C_ROUTINE_ERROR_OFFSET)
DECL|macro|GSS_S_UNAVAILABLE
mdefine_line|#define GSS_S_UNAVAILABLE (((OM_uint32) 16ul) &lt;&lt; GSS_C_ROUTINE_ERROR_OFFSET)
DECL|macro|GSS_S_DUPLICATE_ELEMENT
mdefine_line|#define GSS_S_DUPLICATE_ELEMENT &bslash;&n;     (((OM_uint32) 17ul) &lt;&lt; GSS_C_ROUTINE_ERROR_OFFSET)
DECL|macro|GSS_S_NAME_NOT_MN
mdefine_line|#define GSS_S_NAME_NOT_MN &bslash;&n;     (((OM_uint32) 18ul) &lt;&lt; GSS_C_ROUTINE_ERROR_OFFSET)
multiline_comment|/*&n; * Supplementary info bits:&n; */
DECL|macro|GSS_S_CONTINUE_NEEDED
mdefine_line|#define GSS_S_CONTINUE_NEEDED (1 &lt;&lt; (GSS_C_SUPPLEMENTARY_OFFSET + 0))
DECL|macro|GSS_S_DUPLICATE_TOKEN
mdefine_line|#define GSS_S_DUPLICATE_TOKEN (1 &lt;&lt; (GSS_C_SUPPLEMENTARY_OFFSET + 1))
DECL|macro|GSS_S_OLD_TOKEN
mdefine_line|#define GSS_S_OLD_TOKEN (1 &lt;&lt; (GSS_C_SUPPLEMENTARY_OFFSET + 2))
DECL|macro|GSS_S_UNSEQ_TOKEN
mdefine_line|#define GSS_S_UNSEQ_TOKEN (1 &lt;&lt; (GSS_C_SUPPLEMENTARY_OFFSET + 3))
DECL|macro|GSS_S_GAP_TOKEN
mdefine_line|#define GSS_S_GAP_TOKEN (1 &lt;&lt; (GSS_C_SUPPLEMENTARY_OFFSET + 4))
multiline_comment|/* XXXX these are not part of the GSSAPI C bindings!  (but should be) */
DECL|macro|GSS_CALLING_ERROR_FIELD
mdefine_line|#define GSS_CALLING_ERROR_FIELD(x) &bslash;&n;   (((x) &gt;&gt; GSS_C_CALLING_ERROR_OFFSET) &amp; GSS_C_CALLING_ERROR_MASK)
DECL|macro|GSS_ROUTINE_ERROR_FIELD
mdefine_line|#define GSS_ROUTINE_ERROR_FIELD(x) &bslash;&n;   (((x) &gt;&gt; GSS_C_ROUTINE_ERROR_OFFSET) &amp; GSS_C_ROUTINE_ERROR_MASK)
DECL|macro|GSS_SUPPLEMENTARY_INFO_FIELD
mdefine_line|#define GSS_SUPPLEMENTARY_INFO_FIELD(x) &bslash;&n;   (((x) &gt;&gt; GSS_C_SUPPLEMENTARY_OFFSET) &amp; GSS_C_SUPPLEMENTARY_MASK)
multiline_comment|/* XXXX This is a necessary evil until the spec is fixed */
DECL|macro|GSS_S_CRED_UNAVAIL
mdefine_line|#define GSS_S_CRED_UNAVAIL GSS_S_FAILURE
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* __LINUX_SUNRPC_GSS_ERR_H */
eof
