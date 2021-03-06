multiline_comment|/*&n; * linux/include/linux/gss_api.h&n; *&n; * Somewhat simplified version of the gss api.&n; *&n; * Dug Song &lt;dugsong@monkey.org&gt;&n; * Andy Adamson &lt;andros@umich.edu&gt;&n; * Bruce Fields &lt;bfields@umich.edu&gt;&n; * Copyright (c) 2000 The Regents of the University of Michigan&n; *&n; * $Id$&n; */
macro_line|#ifndef _LINUX_SUNRPC_GSS_API_H
DECL|macro|_LINUX_SUNRPC_GSS_API_H
mdefine_line|#define _LINUX_SUNRPC_GSS_API_H
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/sunrpc/xdr.h&gt;
macro_line|#include &lt;linux/uio.h&gt;
multiline_comment|/* The mechanism-independent gss-api context: */
DECL|struct|gss_ctx
r_struct
id|gss_ctx
(brace
DECL|member|mech_type
r_struct
id|gss_api_mech
op_star
id|mech_type
suffix:semicolon
DECL|member|internal_ctx_id
r_void
op_star
id|internal_ctx_id
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|GSS_C_NO_BUFFER
mdefine_line|#define GSS_C_NO_BUFFER&t;&t;((struct xdr_netobj) 0)
DECL|macro|GSS_C_NO_CONTEXT
mdefine_line|#define GSS_C_NO_CONTEXT&t;((struct gss_ctx *) 0)
DECL|macro|GSS_C_NULL_OID
mdefine_line|#define GSS_C_NULL_OID&t;&t;((struct xdr_netobj) 0)
multiline_comment|/*XXX  arbitrary length - is this set somewhere? */
DECL|macro|GSS_OID_MAX_LEN
mdefine_line|#define GSS_OID_MAX_LEN 32
multiline_comment|/* gss-api prototypes; note that these are somewhat simplified versions of&n; * the prototypes specified in RFC 2744. */
r_int
id|gss_import_sec_context
c_func
(paren
r_const
r_void
op_star
id|input_token
comma
r_int
id|bufsize
comma
r_struct
id|gss_api_mech
op_star
id|mech
comma
r_struct
id|gss_ctx
op_star
op_star
id|ctx_id
)paren
suffix:semicolon
id|u32
id|gss_get_mic
c_func
(paren
r_struct
id|gss_ctx
op_star
id|ctx_id
comma
id|u32
id|qop
comma
r_struct
id|xdr_buf
op_star
id|message
comma
r_struct
id|xdr_netobj
op_star
id|mic_token
)paren
suffix:semicolon
id|u32
id|gss_verify_mic
c_func
(paren
r_struct
id|gss_ctx
op_star
id|ctx_id
comma
r_struct
id|xdr_buf
op_star
id|message
comma
r_struct
id|xdr_netobj
op_star
id|mic_token
comma
id|u32
op_star
id|qstate
)paren
suffix:semicolon
id|u32
id|gss_delete_sec_context
c_func
(paren
r_struct
id|gss_ctx
op_star
op_star
id|ctx_id
)paren
suffix:semicolon
id|u32
id|gss_pseudoflavor_to_service
c_func
(paren
r_struct
id|gss_api_mech
op_star
comma
id|u32
id|pseudoflavor
)paren
suffix:semicolon
r_char
op_star
id|gss_service_to_auth_domain_name
c_func
(paren
r_struct
id|gss_api_mech
op_star
comma
id|u32
id|service
)paren
suffix:semicolon
DECL|struct|pf_desc
r_struct
id|pf_desc
(brace
DECL|member|pseudoflavor
id|u32
id|pseudoflavor
suffix:semicolon
DECL|member|qop
id|u32
id|qop
suffix:semicolon
DECL|member|service
id|u32
id|service
suffix:semicolon
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|auth_domain_name
r_char
op_star
id|auth_domain_name
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Different mechanisms (e.g., krb5 or spkm3) may implement gss-api, and&n; * mechanisms may be dynamically registered or unregistered by modules. */
multiline_comment|/* Each mechanism is described by the following struct: */
DECL|struct|gss_api_mech
r_struct
id|gss_api_mech
(brace
DECL|member|gm_list
r_struct
id|list_head
id|gm_list
suffix:semicolon
DECL|member|gm_owner
r_struct
id|module
op_star
id|gm_owner
suffix:semicolon
DECL|member|gm_oid
r_struct
id|xdr_netobj
id|gm_oid
suffix:semicolon
DECL|member|gm_name
r_char
op_star
id|gm_name
suffix:semicolon
DECL|member|gm_ops
r_struct
id|gss_api_ops
op_star
id|gm_ops
suffix:semicolon
multiline_comment|/* pseudoflavors supported by this mechanism: */
DECL|member|gm_pf_num
r_int
id|gm_pf_num
suffix:semicolon
DECL|member|gm_pfs
r_struct
id|pf_desc
op_star
id|gm_pfs
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* and must provide the following operations: */
DECL|struct|gss_api_ops
r_struct
id|gss_api_ops
(brace
DECL|member|gss_import_sec_context
r_int
(paren
op_star
id|gss_import_sec_context
)paren
(paren
r_const
r_void
op_star
id|input_token
comma
r_int
id|bufsize
comma
r_struct
id|gss_ctx
op_star
id|ctx_id
)paren
suffix:semicolon
DECL|member|gss_get_mic
id|u32
(paren
op_star
id|gss_get_mic
)paren
(paren
r_struct
id|gss_ctx
op_star
id|ctx_id
comma
id|u32
id|qop
comma
r_struct
id|xdr_buf
op_star
id|message
comma
r_struct
id|xdr_netobj
op_star
id|mic_token
)paren
suffix:semicolon
DECL|member|gss_verify_mic
id|u32
(paren
op_star
id|gss_verify_mic
)paren
(paren
r_struct
id|gss_ctx
op_star
id|ctx_id
comma
r_struct
id|xdr_buf
op_star
id|message
comma
r_struct
id|xdr_netobj
op_star
id|mic_token
comma
id|u32
op_star
id|qstate
)paren
suffix:semicolon
DECL|member|gss_delete_sec_context
r_void
(paren
op_star
id|gss_delete_sec_context
)paren
(paren
r_void
op_star
id|internal_ctx_id
)paren
suffix:semicolon
)brace
suffix:semicolon
r_int
id|gss_mech_register
c_func
(paren
r_struct
id|gss_api_mech
op_star
)paren
suffix:semicolon
r_void
id|gss_mech_unregister
c_func
(paren
r_struct
id|gss_api_mech
op_star
)paren
suffix:semicolon
multiline_comment|/* returns a mechanism descriptor given an OID, and increments the mechanism&squot;s&n; * reference count. */
r_struct
id|gss_api_mech
op_star
id|gss_mech_get_by_OID
c_func
(paren
r_struct
id|xdr_netobj
op_star
)paren
suffix:semicolon
multiline_comment|/* Returns a reference to a mechanism, given a name like &quot;krb5&quot; etc. */
r_struct
id|gss_api_mech
op_star
id|gss_mech_get_by_name
c_func
(paren
r_const
r_char
op_star
)paren
suffix:semicolon
multiline_comment|/* Similar, but get by pseudoflavor. */
r_struct
id|gss_api_mech
op_star
id|gss_mech_get_by_pseudoflavor
c_func
(paren
id|u32
)paren
suffix:semicolon
multiline_comment|/* Just increments the mechanism&squot;s reference count and returns its input: */
r_struct
id|gss_api_mech
op_star
id|gss_mech_get
c_func
(paren
r_struct
id|gss_api_mech
op_star
)paren
suffix:semicolon
multiline_comment|/* For every succesful gss_mech_get or gss_mech_get_by_* call there must be a&n; * corresponding call to gss_mech_put. */
r_void
id|gss_mech_put
c_func
(paren
r_struct
id|gss_api_mech
op_star
)paren
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _LINUX_SUNRPC_GSS_API_H */
eof
