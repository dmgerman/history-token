macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/uio.h&gt;
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;linux/sunrpc/auth_gss.h&gt;
macro_line|#include &lt;linux/sunrpc/svcauth_gss.h&gt;
macro_line|#include &lt;linux/sunrpc/gss_asn1.h&gt;
macro_line|#include &lt;linux/sunrpc/gss_krb5.h&gt;
multiline_comment|/* svcauth_gss.c: */
DECL|variable|svcauth_gss_register_pseudoflavor
id|EXPORT_SYMBOL
c_func
(paren
id|svcauth_gss_register_pseudoflavor
)paren
suffix:semicolon
multiline_comment|/* registering gss mechanisms to the mech switching code: */
DECL|variable|gss_mech_register
id|EXPORT_SYMBOL
c_func
(paren
id|gss_mech_register
)paren
suffix:semicolon
DECL|variable|gss_mech_unregister
id|EXPORT_SYMBOL
c_func
(paren
id|gss_mech_unregister
)paren
suffix:semicolon
DECL|variable|gss_mech_get
id|EXPORT_SYMBOL
c_func
(paren
id|gss_mech_get
)paren
suffix:semicolon
DECL|variable|gss_mech_get_by_pseudoflavor
id|EXPORT_SYMBOL
c_func
(paren
id|gss_mech_get_by_pseudoflavor
)paren
suffix:semicolon
DECL|variable|gss_mech_get_by_name
id|EXPORT_SYMBOL
c_func
(paren
id|gss_mech_get_by_name
)paren
suffix:semicolon
DECL|variable|gss_mech_put
id|EXPORT_SYMBOL
c_func
(paren
id|gss_mech_put
)paren
suffix:semicolon
DECL|variable|gss_pseudoflavor_to_service
id|EXPORT_SYMBOL
c_func
(paren
id|gss_pseudoflavor_to_service
)paren
suffix:semicolon
DECL|variable|gss_service_to_auth_domain_name
id|EXPORT_SYMBOL
c_func
(paren
id|gss_service_to_auth_domain_name
)paren
suffix:semicolon
multiline_comment|/* generic functionality in gss code: */
DECL|variable|g_make_token_header
id|EXPORT_SYMBOL
c_func
(paren
id|g_make_token_header
)paren
suffix:semicolon
DECL|variable|g_verify_token_header
id|EXPORT_SYMBOL
c_func
(paren
id|g_verify_token_header
)paren
suffix:semicolon
DECL|variable|g_token_size
id|EXPORT_SYMBOL
c_func
(paren
id|g_token_size
)paren
suffix:semicolon
DECL|variable|make_checksum
id|EXPORT_SYMBOL
c_func
(paren
id|make_checksum
)paren
suffix:semicolon
DECL|variable|krb5_encrypt
id|EXPORT_SYMBOL
c_func
(paren
id|krb5_encrypt
)paren
suffix:semicolon
DECL|variable|krb5_decrypt
id|EXPORT_SYMBOL
c_func
(paren
id|krb5_decrypt
)paren
suffix:semicolon
multiline_comment|/* debug */
DECL|variable|print_hexl
id|EXPORT_SYMBOL
c_func
(paren
id|print_hexl
)paren
suffix:semicolon
eof
