macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/uio.h&gt;
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;linux/sunrpc/auth_gss.h&gt;
macro_line|#include &lt;linux/sunrpc/gss_asn1.h&gt;
multiline_comment|/* sec_triples: */
DECL|variable|gss_register_triple
id|EXPORT_SYMBOL
c_func
(paren
id|gss_register_triple
)paren
suffix:semicolon
DECL|variable|gss_unregister_triple
id|EXPORT_SYMBOL
c_func
(paren
id|gss_unregister_triple
)paren
suffix:semicolon
DECL|variable|gss_cmp_triples
id|EXPORT_SYMBOL
c_func
(paren
id|gss_cmp_triples
)paren
suffix:semicolon
DECL|variable|gss_pseudoflavor_to_mechOID
id|EXPORT_SYMBOL
c_func
(paren
id|gss_pseudoflavor_to_mechOID
)paren
suffix:semicolon
DECL|variable|gss_pseudoflavor_supported
id|EXPORT_SYMBOL
c_func
(paren
id|gss_pseudoflavor_supported
)paren
suffix:semicolon
DECL|variable|gss_pseudoflavor_to_service
id|EXPORT_SYMBOL
c_func
(paren
id|gss_pseudoflavor_to_service
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
DECL|variable|gss_mech_get
id|EXPORT_SYMBOL
c_func
(paren
id|gss_mech_get
)paren
suffix:semicolon
DECL|variable|gss_mech_get_by_OID
id|EXPORT_SYMBOL
c_func
(paren
id|gss_mech_get_by_OID
)paren
suffix:semicolon
DECL|variable|gss_mech_put
id|EXPORT_SYMBOL
c_func
(paren
id|gss_mech_put
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
multiline_comment|/* debug */
DECL|variable|print_hexl
id|EXPORT_SYMBOL
c_func
(paren
id|print_hexl
)paren
suffix:semicolon
eof
