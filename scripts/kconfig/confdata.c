multiline_comment|/*&n; * Copyright (C) 2002 Roman Zippel &lt;zippel@linux-m68k.org&gt;&n; * Released under the terms of the GNU GPL v2.0.&n; */
macro_line|#include &lt;sys/stat.h&gt;
macro_line|#include &lt;ctype.h&gt;
macro_line|#include &lt;stdio.h&gt;
macro_line|#include &lt;stdlib.h&gt;
macro_line|#include &lt;string.h&gt;
macro_line|#include &lt;unistd.h&gt;
DECL|macro|LKC_DIRECT_LINK
mdefine_line|#define LKC_DIRECT_LINK
macro_line|#include &quot;lkc.h&quot;
DECL|variable|conf_def_filename
r_const
r_char
id|conf_def_filename
(braket
)braket
op_assign
l_string|&quot;.config&quot;
suffix:semicolon
DECL|variable|conf_defname
r_const
r_char
id|conf_defname
(braket
)braket
op_assign
l_string|&quot;arch/$ARCH/defconfig&quot;
suffix:semicolon
DECL|variable|conf_confnames
r_const
r_char
op_star
id|conf_confnames
(braket
)braket
op_assign
(brace
l_string|&quot;.config&quot;
comma
l_string|&quot;/lib/modules/$UNAME_RELEASE/.config&quot;
comma
l_string|&quot;/etc/kernel-config&quot;
comma
l_string|&quot;/boot/config-$UNAME_RELEASE&quot;
comma
id|conf_defname
comma
l_int|NULL
comma
)brace
suffix:semicolon
DECL|function|conf_expand_value
r_static
r_char
op_star
id|conf_expand_value
c_func
(paren
r_const
r_char
op_star
id|in
)paren
(brace
r_struct
id|symbol
op_star
id|sym
suffix:semicolon
r_const
r_char
op_star
id|src
suffix:semicolon
r_static
r_char
id|res_value
(braket
id|SYMBOL_MAXLENGTH
)braket
suffix:semicolon
r_char
op_star
id|dst
comma
id|name
(braket
id|SYMBOL_MAXLENGTH
)braket
suffix:semicolon
id|res_value
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
id|dst
op_assign
id|name
suffix:semicolon
r_while
c_loop
(paren
(paren
id|src
op_assign
id|strchr
c_func
(paren
id|in
comma
l_char|&squot;$&squot;
)paren
)paren
)paren
(brace
id|strncat
c_func
(paren
id|res_value
comma
id|in
comma
id|src
op_minus
id|in
)paren
suffix:semicolon
id|src
op_increment
suffix:semicolon
id|dst
op_assign
id|name
suffix:semicolon
r_while
c_loop
(paren
id|isalnum
c_func
(paren
op_star
id|src
)paren
op_logical_or
op_star
id|src
op_eq
l_char|&squot;_&squot;
)paren
op_star
id|dst
op_increment
op_assign
op_star
id|src
op_increment
suffix:semicolon
op_star
id|dst
op_assign
l_int|0
suffix:semicolon
id|sym
op_assign
id|sym_lookup
c_func
(paren
id|name
comma
l_int|0
)paren
suffix:semicolon
id|sym_calc_value
c_func
(paren
id|sym
)paren
suffix:semicolon
id|strcat
c_func
(paren
id|res_value
comma
id|sym_get_string_value
c_func
(paren
id|sym
)paren
)paren
suffix:semicolon
id|in
op_assign
id|src
suffix:semicolon
)brace
id|strcat
c_func
(paren
id|res_value
comma
id|in
)paren
suffix:semicolon
r_return
id|res_value
suffix:semicolon
)brace
DECL|function|conf_get_default_confname
r_char
op_star
id|conf_get_default_confname
c_func
(paren
r_void
)paren
(brace
r_struct
id|stat
id|buf
suffix:semicolon
r_static
r_char
id|fullname
(braket
id|PATH_MAX
op_plus
l_int|1
)braket
suffix:semicolon
r_char
op_star
id|env
comma
op_star
id|name
suffix:semicolon
id|name
op_assign
id|conf_expand_value
c_func
(paren
id|conf_defname
)paren
suffix:semicolon
id|env
op_assign
id|getenv
c_func
(paren
id|SRCTREE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|env
)paren
(brace
id|sprintf
c_func
(paren
id|fullname
comma
l_string|&quot;%s/%s&quot;
comma
id|env
comma
id|name
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|stat
c_func
(paren
id|fullname
comma
op_amp
id|buf
)paren
)paren
r_return
id|fullname
suffix:semicolon
)brace
r_return
id|name
suffix:semicolon
)brace
DECL|function|conf_read
r_int
id|conf_read
c_func
(paren
r_const
r_char
op_star
id|name
)paren
(brace
id|FILE
op_star
id|in
op_assign
l_int|NULL
suffix:semicolon
r_char
id|line
(braket
l_int|1024
)braket
suffix:semicolon
r_char
op_star
id|p
comma
op_star
id|p2
suffix:semicolon
r_int
id|lineno
op_assign
l_int|0
suffix:semicolon
r_struct
id|symbol
op_star
id|sym
suffix:semicolon
r_struct
id|property
op_star
id|prop
suffix:semicolon
r_struct
id|expr
op_star
id|e
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|name
)paren
(brace
id|in
op_assign
id|zconf_fopen
c_func
(paren
id|name
)paren
suffix:semicolon
)brace
r_else
(brace
r_const
r_char
op_star
op_star
id|names
op_assign
id|conf_confnames
suffix:semicolon
r_while
c_loop
(paren
(paren
id|name
op_assign
op_star
id|names
op_increment
)paren
)paren
(brace
id|name
op_assign
id|conf_expand_value
c_func
(paren
id|name
)paren
suffix:semicolon
id|in
op_assign
id|zconf_fopen
c_func
(paren
id|name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|in
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;#&bslash;n&quot;
l_string|&quot;# using defaults found in %s&bslash;n&quot;
l_string|&quot;#&bslash;n&quot;
comma
id|name
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|in
)paren
r_return
l_int|1
suffix:semicolon
id|for_all_symbols
c_func
(paren
id|i
comma
id|sym
)paren
(brace
id|sym-&gt;flags
op_or_assign
id|SYMBOL_NEW
op_or
id|SYMBOL_CHANGED
suffix:semicolon
id|sym-&gt;flags
op_and_assign
op_complement
id|SYMBOL_VALID
suffix:semicolon
r_switch
c_cond
(paren
id|sym-&gt;type
)paren
(brace
r_case
id|S_INT
suffix:colon
r_case
id|S_HEX
suffix:colon
r_case
id|S_STRING
suffix:colon
r_if
c_cond
(paren
id|sym-&gt;user.val
)paren
id|free
c_func
(paren
id|sym-&gt;user.val
)paren
suffix:semicolon
r_default
suffix:colon
id|sym-&gt;user.val
op_assign
l_int|NULL
suffix:semicolon
id|sym-&gt;user.tri
op_assign
id|no
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
id|fgets
c_func
(paren
id|line
comma
r_sizeof
(paren
id|line
)paren
comma
id|in
)paren
)paren
(brace
id|lineno
op_increment
suffix:semicolon
r_switch
c_cond
(paren
id|line
(braket
l_int|0
)braket
)paren
(brace
r_case
l_char|&squot;#&squot;
suffix:colon
r_if
c_cond
(paren
id|memcmp
c_func
(paren
id|line
op_plus
l_int|2
comma
l_string|&quot;CONFIG_&quot;
comma
l_int|7
)paren
)paren
r_continue
suffix:semicolon
id|p
op_assign
id|strchr
c_func
(paren
id|line
op_plus
l_int|9
comma
l_char|&squot; &squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p
)paren
r_continue
suffix:semicolon
op_star
id|p
op_increment
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|p
comma
l_string|&quot;is not set&quot;
comma
l_int|10
)paren
)paren
r_continue
suffix:semicolon
id|sym
op_assign
id|sym_lookup
c_func
(paren
id|line
op_plus
l_int|9
comma
l_int|0
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|sym-&gt;type
)paren
(brace
r_case
id|S_BOOLEAN
suffix:colon
r_case
id|S_TRISTATE
suffix:colon
id|sym-&gt;user
op_assign
id|symbol_no.curr
suffix:semicolon
id|sym-&gt;flags
op_and_assign
op_complement
id|SYMBOL_NEW
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
l_char|&squot;C&squot;
suffix:colon
r_if
c_cond
(paren
id|memcmp
c_func
(paren
id|line
comma
l_string|&quot;CONFIG_&quot;
comma
l_int|7
)paren
)paren
r_continue
suffix:semicolon
id|p
op_assign
id|strchr
c_func
(paren
id|line
op_plus
l_int|7
comma
l_char|&squot;=&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p
)paren
r_continue
suffix:semicolon
op_star
id|p
op_increment
op_assign
l_int|0
suffix:semicolon
id|p2
op_assign
id|strchr
c_func
(paren
id|p
comma
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p2
)paren
op_star
id|p2
op_assign
l_int|0
suffix:semicolon
id|sym
op_assign
id|sym_find
c_func
(paren
id|line
op_plus
l_int|7
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sym
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;%s:%d: trying to assign nonexistent symbol %s&bslash;n&quot;
comma
id|name
comma
id|lineno
comma
id|line
op_plus
l_int|7
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|sym-&gt;type
)paren
(brace
r_case
id|S_TRISTATE
suffix:colon
r_if
c_cond
(paren
id|p
(braket
l_int|0
)braket
op_eq
l_char|&squot;m&squot;
)paren
(brace
id|sym-&gt;user.tri
op_assign
id|mod
suffix:semicolon
id|sym-&gt;flags
op_and_assign
op_complement
id|SYMBOL_NEW
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|S_BOOLEAN
suffix:colon
r_if
c_cond
(paren
id|p
(braket
l_int|0
)braket
op_eq
l_char|&squot;y&squot;
)paren
(brace
id|sym-&gt;user.tri
op_assign
id|yes
suffix:semicolon
id|sym-&gt;flags
op_and_assign
op_complement
id|SYMBOL_NEW
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|p
(braket
l_int|0
)braket
op_eq
l_char|&squot;n&squot;
)paren
(brace
id|sym-&gt;user.tri
op_assign
id|no
suffix:semicolon
id|sym-&gt;flags
op_and_assign
op_complement
id|SYMBOL_NEW
suffix:semicolon
r_break
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|S_STRING
suffix:colon
r_if
c_cond
(paren
op_star
id|p
op_increment
op_ne
l_char|&squot;&quot;&squot;
)paren
r_break
suffix:semicolon
r_for
c_loop
(paren
id|p2
op_assign
id|p
suffix:semicolon
(paren
id|p2
op_assign
id|strpbrk
c_func
(paren
id|p2
comma
l_string|&quot;&bslash;&quot;&bslash;&bslash;&quot;
)paren
)paren
suffix:semicolon
id|p2
op_increment
)paren
(brace
r_if
c_cond
(paren
op_star
id|p2
op_eq
l_char|&squot;&quot;&squot;
)paren
(brace
op_star
id|p2
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
id|memmove
c_func
(paren
id|p2
comma
id|p2
op_plus
l_int|1
comma
id|strlen
c_func
(paren
id|p2
)paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|p2
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;%s:%d: invalid string found&bslash;n&quot;
comma
id|name
comma
id|lineno
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
r_case
id|S_INT
suffix:colon
r_case
id|S_HEX
suffix:colon
r_if
c_cond
(paren
id|sym_string_valid
c_func
(paren
id|sym
comma
id|p
)paren
)paren
(brace
id|sym-&gt;user.val
op_assign
id|strdup
c_func
(paren
id|p
)paren
suffix:semicolon
id|sym-&gt;flags
op_and_assign
op_complement
id|SYMBOL_NEW
suffix:semicolon
)brace
r_else
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;%s:%d: symbol value &squot;%s&squot; invalid for %s&bslash;n&quot;
comma
id|name
comma
id|lineno
comma
id|p
comma
id|sym-&gt;name
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_default
suffix:colon
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sym_is_choice_value
c_func
(paren
id|sym
)paren
)paren
(brace
r_struct
id|symbol
op_star
id|cs
op_assign
id|prop_get_symbol
c_func
(paren
id|sym_get_choice_prop
c_func
(paren
id|sym
)paren
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|sym-&gt;user.tri
)paren
(brace
r_case
id|mod
suffix:colon
r_if
c_cond
(paren
id|cs-&gt;user.tri
op_eq
id|yes
)paren
multiline_comment|/* warn? */
suffix:semicolon
r_break
suffix:semicolon
r_case
id|yes
suffix:colon
r_if
c_cond
(paren
id|cs-&gt;user.tri
op_ne
id|no
)paren
multiline_comment|/* warn? */
suffix:semicolon
id|cs-&gt;user.val
op_assign
id|sym
suffix:semicolon
r_break
suffix:semicolon
r_case
id|no
suffix:colon
r_break
suffix:semicolon
)brace
id|cs-&gt;user.tri
op_assign
id|sym-&gt;user.tri
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
l_char|&squot;&bslash;n&squot;
suffix:colon
r_break
suffix:semicolon
r_default
suffix:colon
r_continue
suffix:semicolon
)brace
)brace
id|fclose
c_func
(paren
id|in
)paren
suffix:semicolon
id|for_all_symbols
c_func
(paren
id|i
comma
id|sym
)paren
(brace
id|sym_calc_value
c_func
(paren
id|sym
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sym_has_value
c_func
(paren
id|sym
)paren
)paren
(brace
r_if
c_cond
(paren
id|sym-&gt;visible
op_eq
id|no
)paren
id|sym-&gt;flags
op_or_assign
id|SYMBOL_NEW
suffix:semicolon
r_switch
c_cond
(paren
id|sym-&gt;type
)paren
(brace
r_case
id|S_STRING
suffix:colon
r_case
id|S_INT
suffix:colon
r_case
id|S_HEX
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|sym_string_within_range
c_func
(paren
id|sym
comma
id|sym-&gt;user.val
)paren
)paren
id|sym-&gt;flags
op_or_assign
id|SYMBOL_NEW
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|sym_is_choice
c_func
(paren
id|sym
)paren
)paren
r_continue
suffix:semicolon
id|prop
op_assign
id|sym_get_choice_prop
c_func
(paren
id|sym
)paren
suffix:semicolon
id|sym-&gt;flags
op_and_assign
op_complement
id|SYMBOL_NEW
suffix:semicolon
r_for
c_loop
(paren
id|e
op_assign
id|prop-&gt;expr
suffix:semicolon
id|e
suffix:semicolon
id|e
op_assign
id|e-&gt;left.expr
)paren
r_if
c_cond
(paren
id|e-&gt;right.sym-&gt;visible
op_ne
id|no
)paren
id|sym-&gt;flags
op_or_assign
id|e-&gt;right.sym-&gt;flags
op_amp
id|SYMBOL_NEW
suffix:semicolon
)brace
id|sym_change_count
op_assign
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|conf_write
r_int
id|conf_write
c_func
(paren
r_const
r_char
op_star
id|name
)paren
(brace
id|FILE
op_star
id|out
comma
op_star
id|out_h
suffix:semicolon
r_struct
id|symbol
op_star
id|sym
suffix:semicolon
r_struct
id|menu
op_star
id|menu
suffix:semicolon
r_const
r_char
op_star
id|basename
suffix:semicolon
r_char
id|dirname
(braket
l_int|128
)braket
comma
id|tmpname
(braket
l_int|128
)braket
comma
id|newname
(braket
l_int|128
)braket
suffix:semicolon
r_int
id|type
comma
id|l
suffix:semicolon
r_const
r_char
op_star
id|str
suffix:semicolon
id|dirname
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|name
op_logical_and
id|name
(braket
l_int|0
)braket
)paren
(brace
r_char
op_star
id|slash
op_assign
id|strrchr
c_func
(paren
id|name
comma
l_char|&squot;/&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|slash
)paren
(brace
r_int
id|size
op_assign
id|slash
op_minus
id|name
op_plus
l_int|1
suffix:semicolon
id|memcpy
c_func
(paren
id|dirname
comma
id|name
comma
id|size
)paren
suffix:semicolon
id|dirname
(braket
id|size
)braket
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|slash
(braket
l_int|1
)braket
)paren
id|basename
op_assign
id|slash
op_plus
l_int|1
suffix:semicolon
r_else
id|basename
op_assign
id|conf_def_filename
suffix:semicolon
)brace
r_else
id|basename
op_assign
id|name
suffix:semicolon
)brace
r_else
id|basename
op_assign
id|conf_def_filename
suffix:semicolon
id|sprintf
c_func
(paren
id|newname
comma
l_string|&quot;%s.tmpconfig.%d&quot;
comma
id|dirname
comma
id|getpid
c_func
(paren
)paren
)paren
suffix:semicolon
id|out
op_assign
id|fopen
c_func
(paren
id|newname
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
id|out_h
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|name
)paren
(brace
id|out_h
op_assign
id|fopen
c_func
(paren
l_string|&quot;.tmpconfig.h&quot;
comma
l_string|&quot;w&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|out_h
)paren
r_return
l_int|1
suffix:semicolon
)brace
id|fprintf
c_func
(paren
id|out
comma
l_string|&quot;#&bslash;n&quot;
l_string|&quot;# Automatically generated make config: don&squot;t edit&bslash;n&quot;
l_string|&quot;#&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|out_h
)paren
id|fprintf
c_func
(paren
id|out_h
comma
l_string|&quot;/*&bslash;n&quot;
l_string|&quot; * Automatically generated C config: don&squot;t edit&bslash;n&quot;
l_string|&quot; */&bslash;n&quot;
l_string|&quot;#define AUTOCONF_INCLUDED&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sym_change_count
)paren
id|sym_clear_all_valid
c_func
(paren
)paren
suffix:semicolon
id|menu
op_assign
id|rootmenu.list
suffix:semicolon
r_while
c_loop
(paren
id|menu
)paren
(brace
id|sym
op_assign
id|menu-&gt;sym
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sym
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|menu_is_visible
c_func
(paren
id|menu
)paren
)paren
r_goto
id|next
suffix:semicolon
id|str
op_assign
id|menu_get_prompt
c_func
(paren
id|menu
)paren
suffix:semicolon
id|fprintf
c_func
(paren
id|out
comma
l_string|&quot;&bslash;n&quot;
l_string|&quot;#&bslash;n&quot;
l_string|&quot;# %s&bslash;n&quot;
l_string|&quot;#&bslash;n&quot;
comma
id|str
)paren
suffix:semicolon
r_if
c_cond
(paren
id|out_h
)paren
id|fprintf
c_func
(paren
id|out_h
comma
l_string|&quot;&bslash;n&quot;
l_string|&quot;/*&bslash;n&quot;
l_string|&quot; * %s&bslash;n&quot;
l_string|&quot; */&bslash;n&quot;
comma
id|str
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
(paren
id|sym-&gt;flags
op_amp
id|SYMBOL_CHOICE
)paren
)paren
(brace
id|sym_calc_value
c_func
(paren
id|sym
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|sym-&gt;flags
op_amp
id|SYMBOL_WRITE
)paren
)paren
r_goto
id|next
suffix:semicolon
id|sym-&gt;flags
op_and_assign
op_complement
id|SYMBOL_WRITE
suffix:semicolon
id|type
op_assign
id|sym-&gt;type
suffix:semicolon
r_if
c_cond
(paren
id|type
op_eq
id|S_TRISTATE
)paren
(brace
id|sym_calc_value
c_func
(paren
id|modules_sym
)paren
suffix:semicolon
r_if
c_cond
(paren
id|modules_sym-&gt;curr.tri
op_eq
id|no
)paren
id|type
op_assign
id|S_BOOLEAN
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|type
)paren
(brace
r_case
id|S_BOOLEAN
suffix:colon
r_case
id|S_TRISTATE
suffix:colon
r_switch
c_cond
(paren
id|sym_get_tristate_value
c_func
(paren
id|sym
)paren
)paren
(brace
r_case
id|no
suffix:colon
id|fprintf
c_func
(paren
id|out
comma
l_string|&quot;# CONFIG_%s is not set&bslash;n&quot;
comma
id|sym-&gt;name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|out_h
)paren
id|fprintf
c_func
(paren
id|out_h
comma
l_string|&quot;#undef CONFIG_%s&bslash;n&quot;
comma
id|sym-&gt;name
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|mod
suffix:colon
id|fprintf
c_func
(paren
id|out
comma
l_string|&quot;CONFIG_%s=m&bslash;n&quot;
comma
id|sym-&gt;name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|out_h
)paren
id|fprintf
c_func
(paren
id|out_h
comma
l_string|&quot;#define CONFIG_%s_MODULE 1&bslash;n&quot;
comma
id|sym-&gt;name
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|yes
suffix:colon
id|fprintf
c_func
(paren
id|out
comma
l_string|&quot;CONFIG_%s=y&bslash;n&quot;
comma
id|sym-&gt;name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|out_h
)paren
id|fprintf
c_func
(paren
id|out_h
comma
l_string|&quot;#define CONFIG_%s 1&bslash;n&quot;
comma
id|sym-&gt;name
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|S_STRING
suffix:colon
singleline_comment|// fix me
id|str
op_assign
id|sym_get_string_value
c_func
(paren
id|sym
)paren
suffix:semicolon
id|fprintf
c_func
(paren
id|out
comma
l_string|&quot;CONFIG_%s=&bslash;&quot;&quot;
comma
id|sym-&gt;name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|out_h
)paren
id|fprintf
c_func
(paren
id|out_h
comma
l_string|&quot;#define CONFIG_%s &bslash;&quot;&quot;
comma
id|sym-&gt;name
)paren
suffix:semicolon
r_do
(brace
id|l
op_assign
id|strcspn
c_func
(paren
id|str
comma
l_string|&quot;&bslash;&quot;&bslash;&bslash;&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|l
)paren
(brace
id|fwrite
c_func
(paren
id|str
comma
id|l
comma
l_int|1
comma
id|out
)paren
suffix:semicolon
r_if
c_cond
(paren
id|out_h
)paren
id|fwrite
c_func
(paren
id|str
comma
id|l
comma
l_int|1
comma
id|out_h
)paren
suffix:semicolon
)brace
id|str
op_add_assign
id|l
suffix:semicolon
r_while
c_loop
(paren
op_star
id|str
op_eq
l_char|&squot;&bslash;&bslash;&squot;
op_logical_or
op_star
id|str
op_eq
l_char|&squot;&quot;&squot;
)paren
(brace
id|fprintf
c_func
(paren
id|out
comma
l_string|&quot;&bslash;&bslash;%c&quot;
comma
op_star
id|str
)paren
suffix:semicolon
r_if
c_cond
(paren
id|out_h
)paren
id|fprintf
c_func
(paren
id|out_h
comma
l_string|&quot;&bslash;&bslash;%c&quot;
comma
op_star
id|str
)paren
suffix:semicolon
id|str
op_increment
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
op_star
id|str
)paren
suffix:semicolon
id|fputs
c_func
(paren
l_string|&quot;&bslash;&quot;&bslash;n&quot;
comma
id|out
)paren
suffix:semicolon
r_if
c_cond
(paren
id|out_h
)paren
id|fputs
c_func
(paren
l_string|&quot;&bslash;&quot;&bslash;n&quot;
comma
id|out_h
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|S_HEX
suffix:colon
id|str
op_assign
id|sym_get_string_value
c_func
(paren
id|sym
)paren
suffix:semicolon
r_if
c_cond
(paren
id|str
(braket
l_int|0
)braket
op_ne
l_char|&squot;0&squot;
op_logical_or
(paren
id|str
(braket
l_int|1
)braket
op_ne
l_char|&squot;x&squot;
op_logical_and
id|str
(braket
l_int|1
)braket
op_ne
l_char|&squot;X&squot;
)paren
)paren
(brace
id|fprintf
c_func
(paren
id|out
comma
l_string|&quot;CONFIG_%s=%s&bslash;n&quot;
comma
id|sym-&gt;name
comma
id|str
)paren
suffix:semicolon
r_if
c_cond
(paren
id|out_h
)paren
id|fprintf
c_func
(paren
id|out_h
comma
l_string|&quot;#define CONFIG_%s 0x%s&bslash;n&quot;
comma
id|sym-&gt;name
comma
id|str
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|S_INT
suffix:colon
id|str
op_assign
id|sym_get_string_value
c_func
(paren
id|sym
)paren
suffix:semicolon
id|fprintf
c_func
(paren
id|out
comma
l_string|&quot;CONFIG_%s=%s&bslash;n&quot;
comma
id|sym-&gt;name
comma
id|str
)paren
suffix:semicolon
r_if
c_cond
(paren
id|out_h
)paren
id|fprintf
c_func
(paren
id|out_h
comma
l_string|&quot;#define CONFIG_%s %s&bslash;n&quot;
comma
id|sym-&gt;name
comma
id|str
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|next
suffix:colon
r_if
c_cond
(paren
id|menu-&gt;list
)paren
(brace
id|menu
op_assign
id|menu-&gt;list
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|menu-&gt;next
)paren
id|menu
op_assign
id|menu-&gt;next
suffix:semicolon
r_else
r_while
c_loop
(paren
(paren
id|menu
op_assign
id|menu-&gt;parent
)paren
)paren
(brace
r_if
c_cond
(paren
id|menu-&gt;next
)paren
(brace
id|menu
op_assign
id|menu-&gt;next
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
)brace
id|fclose
c_func
(paren
id|out
)paren
suffix:semicolon
r_if
c_cond
(paren
id|out_h
)paren
(brace
id|fclose
c_func
(paren
id|out_h
)paren
suffix:semicolon
id|rename
c_func
(paren
l_string|&quot;.tmpconfig.h&quot;
comma
l_string|&quot;include/linux/autoconf.h&quot;
)paren
suffix:semicolon
id|file_write_dep
c_func
(paren
l_int|NULL
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|name
op_logical_or
id|basename
op_ne
id|conf_def_filename
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|name
)paren
id|name
op_assign
id|conf_def_filename
suffix:semicolon
id|sprintf
c_func
(paren
id|tmpname
comma
l_string|&quot;%s.old&quot;
comma
id|name
)paren
suffix:semicolon
id|rename
c_func
(paren
id|name
comma
id|tmpname
)paren
suffix:semicolon
)brace
id|sprintf
c_func
(paren
id|tmpname
comma
l_string|&quot;%s%s&quot;
comma
id|dirname
comma
id|basename
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rename
c_func
(paren
id|newname
comma
id|tmpname
)paren
)paren
r_return
l_int|1
suffix:semicolon
id|sym_change_count
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
