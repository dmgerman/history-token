multiline_comment|/*&n; * linux/fs/nls_koi8-ru.c&n; *&n; * Charset koi8-ru translation based on charset koi8-u.&n; * The Unicode to charset table has only exact mappings.&n; */
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
DECL|function|uni2char
r_static
r_int
id|uni2char
c_func
(paren
r_const
m_wchar_t
id|uni
comma
r_int
r_char
op_star
id|out
comma
r_int
id|boundlen
)paren
(brace
r_if
c_cond
(paren
id|boundlen
op_le
l_int|0
)paren
r_return
op_minus
id|ENAMETOOLONG
suffix:semicolon
r_if
c_cond
(paren
(paren
id|uni
op_amp
l_int|0xffaf
)paren
op_eq
l_int|0x040e
op_logical_or
(paren
id|uni
op_amp
l_int|0xffce
)paren
op_eq
l_int|0x254c
)paren
(brace
multiline_comment|/* koi8-ru and koi8-u differ only on two characters */
r_if
c_cond
(paren
id|uni
op_eq
l_int|0x040e
)paren
id|out
(braket
l_int|0
)braket
op_assign
l_int|0xbe
suffix:semicolon
r_else
r_if
c_cond
(paren
id|uni
op_eq
l_int|0x045e
)paren
id|out
(braket
l_int|0
)braket
op_assign
l_int|0xae
suffix:semicolon
r_else
r_if
c_cond
(paren
id|uni
op_eq
l_int|0x255d
op_logical_or
id|uni
op_eq
l_int|0x256c
)paren
r_return
l_int|0
suffix:semicolon
r_else
r_return
id|p_nls
op_member_access_from_pointer
id|uni2char
c_func
(paren
id|uni
comma
id|out
comma
id|boundlen
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_else
multiline_comment|/* fast path */
r_return
id|p_nls
op_member_access_from_pointer
id|uni2char
c_func
(paren
id|uni
comma
id|out
comma
id|boundlen
)paren
suffix:semicolon
)brace
DECL|function|char2uni
r_static
r_int
id|char2uni
c_func
(paren
r_const
r_int
r_char
op_star
id|rawstring
comma
r_int
id|boundlen
comma
m_wchar_t
op_star
id|uni
)paren
(brace
r_int
id|n
suffix:semicolon
r_if
c_cond
(paren
(paren
op_star
id|rawstring
op_amp
l_int|0xef
)paren
op_ne
l_int|0xae
)paren
(brace
multiline_comment|/* koi8-ru and koi8-u differ only on two characters */
op_star
id|uni
op_assign
(paren
op_star
id|rawstring
op_amp
l_int|0x10
)paren
ques
c_cond
l_int|0x040e
suffix:colon
l_int|0x045e
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|n
op_assign
id|p_nls
op_member_access_from_pointer
id|char2uni
c_func
(paren
id|rawstring
comma
id|boundlen
comma
id|uni
)paren
suffix:semicolon
r_return
id|n
suffix:semicolon
)brace
DECL|variable|table
r_static
r_struct
id|nls_table
id|table
op_assign
(brace
dot
id|charset
op_assign
l_string|&quot;koi8-ru&quot;
comma
dot
id|uni2char
op_assign
id|uni2char
comma
dot
id|char2uni
op_assign
id|char2uni
comma
dot
id|owner
op_assign
id|THIS_MODULE
comma
)brace
suffix:semicolon
DECL|function|init_nls_koi8_ru
r_static
r_int
id|__init
id|init_nls_koi8_ru
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
l_string|&quot;koi8-u&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p_nls
)paren
(brace
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
DECL|function|exit_nls_koi8_ru
r_static
r_void
id|__exit
id|exit_nls_koi8_ru
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
id|init_nls_koi8_ru
)paren
id|module_exit
c_func
(paren
id|exit_nls_koi8_ru
)paren
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;Dual BSD/GPL&quot;
)paren
suffix:semicolon
eof
