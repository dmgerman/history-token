multiline_comment|/*&n; * linux/fs/nls_iso8859-8.c&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/nls.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
DECL|variable|p_nls
r_static
r_struct
id|nls_table
op_star
id|p_nls
suffix:semicolon
DECL|variable|table
r_static
r_struct
id|nls_table
id|table
op_assign
(brace
id|charset
suffix:colon
l_string|&quot;iso8859-8&quot;
comma
id|owner
suffix:colon
id|THIS_MODULE
comma
)brace
suffix:semicolon
DECL|function|init_nls_iso8859_8
r_static
r_int
id|__init
id|init_nls_iso8859_8
c_func
(paren
r_void
)paren
(brace
id|p_nls
op_assign
id|load_nls
c_func
(paren
l_string|&quot;cp1255&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p_nls
)paren
(brace
id|table.uni2char
op_assign
id|p_nls-&gt;uni2char
suffix:semicolon
id|table.char2uni
op_assign
id|p_nls-&gt;char2uni
suffix:semicolon
id|table.charset2upper
op_assign
id|p_nls-&gt;charset2upper
suffix:semicolon
id|table.charset2lower
op_assign
id|p_nls-&gt;charset2lower
suffix:semicolon
r_return
id|register_nls
c_func
(paren
op_amp
id|table
)paren
suffix:semicolon
)brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|function|exit_nls_iso8859_8
r_static
r_void
id|__exit
id|exit_nls_iso8859_8
c_func
(paren
r_void
)paren
(brace
id|unregister_nls
c_func
(paren
op_amp
id|table
)paren
suffix:semicolon
id|unload_nls
c_func
(paren
id|p_nls
)paren
suffix:semicolon
)brace
id|module_init
c_func
(paren
id|init_nls_iso8859_8
)paren
id|module_exit
c_func
(paren
id|exit_nls_iso8859_8
)paren
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;Dual BSD/GPL&quot;
)paren
suffix:semicolon
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; *&n;---------------------------------------------------------------------------&n; * Local variables:&n; * c-indent-level: 8&n; * c-brace-imaginary-offset: 0&n; * c-brace-offset: -8&n; * c-argdecl-indent: 8&n; * c-label-offset: -8&n; * c-continued-statement-offset: 8&n; * c-continued-brace-offset: 0&n; * End:&n; */
eof
