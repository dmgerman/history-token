multiline_comment|/*&n; * Copyright (C) 2002-2005 Roman Zippel &lt;zippel@linux-m68k.org&gt;&n; * Copyright (C) 2002-2005 Sam Ravnborg &lt;sam@ravnborg.org&gt;&n; *&n; * Released under the terms of the GNU GPL v2.0.&n; */
macro_line|#include &lt;string.h&gt;
macro_line|#include &quot;lkc.h&quot;
multiline_comment|/* file already present in list? If not add it */
DECL|function|file_lookup
r_struct
id|file
op_star
id|file_lookup
c_func
(paren
r_const
r_char
op_star
id|name
)paren
(brace
r_struct
id|file
op_star
id|file
suffix:semicolon
r_for
c_loop
(paren
id|file
op_assign
id|file_list
suffix:semicolon
id|file
suffix:semicolon
id|file
op_assign
id|file-&gt;next
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|name
comma
id|file-&gt;name
)paren
)paren
r_return
id|file
suffix:semicolon
)brace
id|file
op_assign
id|malloc
c_func
(paren
r_sizeof
(paren
op_star
id|file
)paren
)paren
suffix:semicolon
id|memset
c_func
(paren
id|file
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|file
)paren
)paren
suffix:semicolon
id|file-&gt;name
op_assign
id|strdup
c_func
(paren
id|name
)paren
suffix:semicolon
id|file-&gt;next
op_assign
id|file_list
suffix:semicolon
id|file_list
op_assign
id|file
suffix:semicolon
r_return
id|file
suffix:semicolon
)brace
multiline_comment|/* write a dependency file as used by kbuild to track dependencies */
DECL|function|file_write_dep
r_int
id|file_write_dep
c_func
(paren
r_const
r_char
op_star
id|name
)paren
(brace
r_struct
id|file
op_star
id|file
suffix:semicolon
id|FILE
op_star
id|out
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|name
)paren
id|name
op_assign
l_string|&quot;.config.cmd&quot;
suffix:semicolon
id|out
op_assign
id|fopen
c_func
(paren
l_string|&quot;..config.tmp&quot;
comma
l_string|&quot;w&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|out
)paren
r_return
l_int|1
suffix:semicolon
id|fprintf
c_func
(paren
id|out
comma
l_string|&quot;deps_config := &bslash;&bslash;&bslash;n&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|file
op_assign
id|file_list
suffix:semicolon
id|file
suffix:semicolon
id|file
op_assign
id|file-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|file-&gt;next
)paren
id|fprintf
c_func
(paren
id|out
comma
l_string|&quot;&bslash;t%s &bslash;&bslash;&bslash;n&quot;
comma
id|file-&gt;name
)paren
suffix:semicolon
r_else
id|fprintf
c_func
(paren
id|out
comma
l_string|&quot;&bslash;t%s&bslash;n&quot;
comma
id|file-&gt;name
)paren
suffix:semicolon
)brace
id|fprintf
c_func
(paren
id|out
comma
l_string|&quot;&bslash;n.config include/linux/autoconf.h: $(deps_config)&bslash;n&bslash;n$(deps_config):&bslash;n&quot;
)paren
suffix:semicolon
id|fclose
c_func
(paren
id|out
)paren
suffix:semicolon
id|rename
c_func
(paren
l_string|&quot;..config.tmp&quot;
comma
id|name
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Allocate initial growable sting */
DECL|function|str_new
r_struct
id|gstr
id|str_new
c_func
(paren
r_void
)paren
(brace
r_struct
id|gstr
id|gs
suffix:semicolon
id|gs.s
op_assign
id|malloc
c_func
(paren
r_sizeof
(paren
r_char
)paren
op_star
l_int|64
)paren
suffix:semicolon
id|gs.len
op_assign
l_int|16
suffix:semicolon
id|strcpy
c_func
(paren
id|gs.s
comma
l_string|&quot;&bslash;0&quot;
)paren
suffix:semicolon
r_return
id|gs
suffix:semicolon
)brace
multiline_comment|/* Allocate and assign growable string */
DECL|function|str_assign
r_struct
id|gstr
id|str_assign
c_func
(paren
r_const
r_char
op_star
id|s
)paren
(brace
r_struct
id|gstr
id|gs
suffix:semicolon
id|gs.s
op_assign
id|strdup
c_func
(paren
id|s
)paren
suffix:semicolon
id|gs.len
op_assign
id|strlen
c_func
(paren
id|s
)paren
op_plus
l_int|1
suffix:semicolon
r_return
id|gs
suffix:semicolon
)brace
multiline_comment|/* Free storage for growable string */
DECL|function|str_free
r_void
id|str_free
c_func
(paren
r_struct
id|gstr
op_star
id|gs
)paren
(brace
r_if
c_cond
(paren
id|gs-&gt;s
)paren
id|free
c_func
(paren
id|gs-&gt;s
)paren
suffix:semicolon
id|gs-&gt;s
op_assign
l_int|NULL
suffix:semicolon
id|gs-&gt;len
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Append to growable string */
DECL|function|str_append
r_void
id|str_append
c_func
(paren
r_struct
id|gstr
op_star
id|gs
comma
r_const
r_char
op_star
id|s
)paren
(brace
r_int
id|l
op_assign
id|strlen
c_func
(paren
id|gs-&gt;s
)paren
op_plus
id|strlen
c_func
(paren
id|s
)paren
op_plus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|l
OG
id|gs-&gt;len
)paren
(brace
id|gs-&gt;s
op_assign
id|realloc
c_func
(paren
id|gs-&gt;s
comma
id|l
)paren
suffix:semicolon
id|gs-&gt;len
op_assign
id|l
suffix:semicolon
)brace
id|strcat
c_func
(paren
id|gs-&gt;s
comma
id|s
)paren
suffix:semicolon
)brace
multiline_comment|/* Append printf formatted string to growable string */
DECL|function|str_printf
r_void
id|str_printf
c_func
(paren
r_struct
id|gstr
op_star
id|gs
comma
r_const
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
(brace
id|va_list
id|ap
suffix:semicolon
r_char
id|s
(braket
l_int|10000
)braket
suffix:semicolon
multiline_comment|/* big enough... */
id|va_start
c_func
(paren
id|ap
comma
id|fmt
)paren
suffix:semicolon
id|vsnprintf
c_func
(paren
id|s
comma
r_sizeof
(paren
id|s
)paren
comma
id|fmt
comma
id|ap
)paren
suffix:semicolon
id|str_append
c_func
(paren
id|gs
comma
id|s
)paren
suffix:semicolon
id|va_end
c_func
(paren
id|ap
)paren
suffix:semicolon
)brace
multiline_comment|/* Retreive value of growable string */
DECL|function|str_get
r_const
r_char
op_star
id|str_get
c_func
(paren
r_struct
id|gstr
op_star
id|gs
)paren
(brace
r_return
id|gs-&gt;s
suffix:semicolon
)brace
eof
