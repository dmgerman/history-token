multiline_comment|/*&n; * Copyright (C) 2002 Roman Zippel &lt;zippel@linux-m68k.org&gt;&n; * Released under the terms of the GNU GPL v2.0.&n; */
macro_line|#include &lt;ctype.h&gt;
macro_line|#include &lt;stdlib.h&gt;
macro_line|#include &lt;string.h&gt;
macro_line|#include &lt;unistd.h&gt;
macro_line|#include &lt;time.h&gt;
macro_line|#include &lt;sys/stat.h&gt;
DECL|macro|LKC_DIRECT_LINK
mdefine_line|#define LKC_DIRECT_LINK
macro_line|#include &quot;lkc.h&quot;
r_static
r_void
id|conf
c_func
(paren
r_struct
id|menu
op_star
id|menu
)paren
suffix:semicolon
r_static
r_void
id|check_conf
c_func
(paren
r_struct
id|menu
op_star
id|menu
)paren
suffix:semicolon
r_enum
(brace
DECL|enumerator|ask_all
id|ask_all
comma
DECL|enumerator|ask_new
id|ask_new
comma
DECL|enumerator|ask_silent
id|ask_silent
comma
DECL|enumerator|set_default
id|set_default
comma
DECL|enumerator|set_yes
id|set_yes
comma
DECL|enumerator|set_mod
id|set_mod
comma
DECL|enumerator|set_no
id|set_no
comma
DECL|enumerator|set_random
id|set_random
DECL|variable|input_mode
)brace
id|input_mode
op_assign
id|ask_all
suffix:semicolon
DECL|variable|defconfig_file
r_char
op_star
id|defconfig_file
suffix:semicolon
DECL|variable|indent
r_static
r_int
id|indent
op_assign
l_int|1
suffix:semicolon
DECL|variable|valid_stdin
r_static
r_int
id|valid_stdin
op_assign
l_int|1
suffix:semicolon
DECL|variable|conf_cnt
r_static
r_int
id|conf_cnt
suffix:semicolon
DECL|variable|line
r_static
r_char
id|line
(braket
l_int|128
)braket
suffix:semicolon
DECL|variable|rootEntry
r_static
r_struct
id|menu
op_star
id|rootEntry
suffix:semicolon
DECL|variable|nohelp_text
r_static
r_char
id|nohelp_text
(braket
)braket
op_assign
l_string|&quot;Sorry, no help available for this option yet.&bslash;n&quot;
suffix:semicolon
DECL|function|strip
r_static
r_void
id|strip
c_func
(paren
r_char
op_star
id|str
)paren
(brace
r_char
op_star
id|p
op_assign
id|str
suffix:semicolon
r_int
id|l
suffix:semicolon
r_while
c_loop
(paren
(paren
id|isspace
c_func
(paren
op_star
id|p
)paren
)paren
)paren
id|p
op_increment
suffix:semicolon
id|l
op_assign
id|strlen
c_func
(paren
id|p
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p
op_ne
id|str
)paren
id|memmove
c_func
(paren
id|str
comma
id|p
comma
id|l
op_plus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|l
)paren
r_return
suffix:semicolon
id|p
op_assign
id|str
op_plus
id|l
op_minus
l_int|1
suffix:semicolon
r_while
c_loop
(paren
(paren
id|isspace
c_func
(paren
op_star
id|p
)paren
)paren
)paren
op_star
id|p
op_decrement
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|check_stdin
r_static
r_void
id|check_stdin
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|valid_stdin
op_logical_and
id|input_mode
op_eq
id|ask_silent
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;aborted!&bslash;n&bslash;n&quot;
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;Console input/output is redirected. &quot;
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;Run &squot;make oldconfig&squot; to update configuration.&bslash;n&bslash;n&quot;
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
)brace
DECL|function|conf_askvalue
r_static
r_void
id|conf_askvalue
c_func
(paren
r_struct
id|symbol
op_star
id|sym
comma
r_const
r_char
op_star
id|def
)paren
(brace
r_enum
id|symbol_type
id|type
op_assign
id|sym_get_type
c_func
(paren
id|sym
)paren
suffix:semicolon
id|tristate
id|val
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sym_has_value
c_func
(paren
id|sym
)paren
)paren
id|printf
c_func
(paren
l_string|&quot;(NEW) &quot;
)paren
suffix:semicolon
id|line
(braket
l_int|0
)braket
op_assign
l_char|&squot;&bslash;n&squot;
suffix:semicolon
id|line
(braket
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sym_is_changable
c_func
(paren
id|sym
)paren
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|def
)paren
suffix:semicolon
id|line
(braket
l_int|0
)braket
op_assign
l_char|&squot;&bslash;n&squot;
suffix:semicolon
id|line
(braket
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
r_return
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|input_mode
)paren
(brace
r_case
id|ask_new
suffix:colon
r_case
id|ask_silent
suffix:colon
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
id|printf
c_func
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|def
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|check_stdin
c_func
(paren
)paren
suffix:semicolon
r_case
id|ask_all
suffix:colon
id|fflush
c_func
(paren
id|stdout
)paren
suffix:semicolon
id|fgets
c_func
(paren
id|line
comma
l_int|128
comma
id|stdin
)paren
suffix:semicolon
r_return
suffix:semicolon
r_case
id|set_default
suffix:colon
id|printf
c_func
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|def
)paren
suffix:semicolon
r_return
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|type
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
id|printf
c_func
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|def
)paren
suffix:semicolon
r_return
suffix:semicolon
r_default
suffix:colon
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|input_mode
)paren
(brace
r_case
id|set_yes
suffix:colon
r_if
c_cond
(paren
id|sym_tristate_within_range
c_func
(paren
id|sym
comma
id|yes
)paren
)paren
(brace
id|line
(braket
l_int|0
)braket
op_assign
l_char|&squot;y&squot;
suffix:semicolon
id|line
(braket
l_int|1
)braket
op_assign
l_char|&squot;&bslash;n&squot;
suffix:semicolon
id|line
(braket
l_int|2
)braket
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|set_mod
suffix:colon
r_if
c_cond
(paren
id|type
op_eq
id|S_TRISTATE
)paren
(brace
r_if
c_cond
(paren
id|sym_tristate_within_range
c_func
(paren
id|sym
comma
id|mod
)paren
)paren
(brace
id|line
(braket
l_int|0
)braket
op_assign
l_char|&squot;m&squot;
suffix:semicolon
id|line
(braket
l_int|1
)braket
op_assign
l_char|&squot;&bslash;n&squot;
suffix:semicolon
id|line
(braket
l_int|2
)braket
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_else
(brace
r_if
c_cond
(paren
id|sym_tristate_within_range
c_func
(paren
id|sym
comma
id|yes
)paren
)paren
(brace
id|line
(braket
l_int|0
)braket
op_assign
l_char|&squot;y&squot;
suffix:semicolon
id|line
(braket
l_int|1
)braket
op_assign
l_char|&squot;&bslash;n&squot;
suffix:semicolon
id|line
(braket
l_int|2
)braket
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_case
id|set_no
suffix:colon
r_if
c_cond
(paren
id|sym_tristate_within_range
c_func
(paren
id|sym
comma
id|no
)paren
)paren
(brace
id|line
(braket
l_int|0
)braket
op_assign
l_char|&squot;n&squot;
suffix:semicolon
id|line
(braket
l_int|1
)braket
op_assign
l_char|&squot;&bslash;n&squot;
suffix:semicolon
id|line
(braket
l_int|2
)braket
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|set_random
suffix:colon
r_do
(brace
id|val
op_assign
(paren
id|tristate
)paren
(paren
id|random
c_func
(paren
)paren
op_mod
l_int|3
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
op_logical_neg
id|sym_tristate_within_range
c_func
(paren
id|sym
comma
id|val
)paren
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|val
)paren
(brace
r_case
id|no
suffix:colon
id|line
(braket
l_int|0
)braket
op_assign
l_char|&squot;n&squot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|mod
suffix:colon
id|line
(braket
l_int|0
)braket
op_assign
l_char|&squot;m&squot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|yes
suffix:colon
id|line
(braket
l_int|0
)braket
op_assign
l_char|&squot;y&squot;
suffix:semicolon
r_break
suffix:semicolon
)brace
id|line
(braket
l_int|1
)braket
op_assign
l_char|&squot;&bslash;n&squot;
suffix:semicolon
id|line
(braket
l_int|2
)braket
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
id|printf
c_func
(paren
l_string|&quot;%s&quot;
comma
id|line
)paren
suffix:semicolon
)brace
DECL|function|conf_string
r_int
id|conf_string
c_func
(paren
r_struct
id|menu
op_star
id|menu
)paren
(brace
r_struct
id|symbol
op_star
id|sym
op_assign
id|menu-&gt;sym
suffix:semicolon
r_const
r_char
op_star
id|def
comma
op_star
id|help
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;%*s%s &quot;
comma
id|indent
op_minus
l_int|1
comma
l_string|&quot;&quot;
comma
id|menu-&gt;prompt-&gt;text
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;(%s) &quot;
comma
id|sym-&gt;name
)paren
suffix:semicolon
id|def
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
id|sym_get_string_value
c_func
(paren
id|sym
)paren
)paren
id|printf
c_func
(paren
l_string|&quot;[%s] &quot;
comma
id|def
)paren
suffix:semicolon
id|conf_askvalue
c_func
(paren
id|sym
comma
id|def
)paren
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
l_char|&squot;&bslash;n&squot;
suffix:colon
r_break
suffix:semicolon
r_case
l_char|&squot;?&squot;
suffix:colon
multiline_comment|/* print help */
r_if
c_cond
(paren
id|line
(braket
l_int|1
)braket
op_eq
l_int|0
)paren
(brace
id|help
op_assign
id|nohelp_text
suffix:semicolon
r_if
c_cond
(paren
id|menu-&gt;sym-&gt;help
)paren
id|help
op_assign
id|menu-&gt;sym-&gt;help
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;&bslash;n%s&bslash;n&quot;
comma
id|menu-&gt;sym-&gt;help
)paren
suffix:semicolon
id|def
op_assign
l_int|NULL
suffix:semicolon
r_break
suffix:semicolon
)brace
r_default
suffix:colon
id|line
(braket
id|strlen
c_func
(paren
id|line
)paren
op_minus
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
id|def
op_assign
id|line
suffix:semicolon
)brace
r_if
c_cond
(paren
id|def
op_logical_and
id|sym_set_string_value
c_func
(paren
id|sym
comma
id|def
)paren
)paren
r_return
l_int|0
suffix:semicolon
)brace
)brace
DECL|function|conf_sym
r_static
r_int
id|conf_sym
c_func
(paren
r_struct
id|menu
op_star
id|menu
)paren
(brace
r_struct
id|symbol
op_star
id|sym
op_assign
id|menu-&gt;sym
suffix:semicolon
r_int
id|type
suffix:semicolon
id|tristate
id|oldval
comma
id|newval
suffix:semicolon
r_const
r_char
op_star
id|help
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;%*s%s &quot;
comma
id|indent
op_minus
l_int|1
comma
l_string|&quot;&quot;
comma
id|menu-&gt;prompt-&gt;text
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sym-&gt;name
)paren
id|printf
c_func
(paren
l_string|&quot;(%s) &quot;
comma
id|sym-&gt;name
)paren
suffix:semicolon
id|type
op_assign
id|sym_get_type
c_func
(paren
id|sym
)paren
suffix:semicolon
id|putchar
c_func
(paren
l_char|&squot;[&squot;
)paren
suffix:semicolon
id|oldval
op_assign
id|sym_get_tristate_value
c_func
(paren
id|sym
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|oldval
)paren
(brace
r_case
id|no
suffix:colon
id|putchar
c_func
(paren
l_char|&squot;N&squot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|mod
suffix:colon
id|putchar
c_func
(paren
l_char|&squot;M&squot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|yes
suffix:colon
id|putchar
c_func
(paren
l_char|&squot;Y&squot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|oldval
op_ne
id|no
op_logical_and
id|sym_tristate_within_range
c_func
(paren
id|sym
comma
id|no
)paren
)paren
id|printf
c_func
(paren
l_string|&quot;/n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|oldval
op_ne
id|mod
op_logical_and
id|sym_tristate_within_range
c_func
(paren
id|sym
comma
id|mod
)paren
)paren
id|printf
c_func
(paren
l_string|&quot;/m&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|oldval
op_ne
id|yes
op_logical_and
id|sym_tristate_within_range
c_func
(paren
id|sym
comma
id|yes
)paren
)paren
id|printf
c_func
(paren
l_string|&quot;/y&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sym-&gt;help
)paren
id|printf
c_func
(paren
l_string|&quot;/?&quot;
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;] &quot;
)paren
suffix:semicolon
id|conf_askvalue
c_func
(paren
id|sym
comma
id|sym_get_string_value
c_func
(paren
id|sym
)paren
)paren
suffix:semicolon
id|strip
c_func
(paren
id|line
)paren
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
l_char|&squot;n&squot;
suffix:colon
r_case
l_char|&squot;N&squot;
suffix:colon
id|newval
op_assign
id|no
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|line
(braket
l_int|1
)braket
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
op_amp
id|line
(braket
l_int|1
)braket
comma
l_string|&quot;o&quot;
)paren
)paren
r_break
suffix:semicolon
r_continue
suffix:semicolon
r_case
l_char|&squot;m&squot;
suffix:colon
r_case
l_char|&squot;M&squot;
suffix:colon
id|newval
op_assign
id|mod
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|line
(braket
l_int|1
)braket
)paren
r_break
suffix:semicolon
r_continue
suffix:semicolon
r_case
l_char|&squot;y&squot;
suffix:colon
r_case
l_char|&squot;Y&squot;
suffix:colon
id|newval
op_assign
id|yes
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|line
(braket
l_int|1
)braket
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
op_amp
id|line
(braket
l_int|1
)braket
comma
l_string|&quot;es&quot;
)paren
)paren
r_break
suffix:semicolon
r_continue
suffix:semicolon
r_case
l_int|0
suffix:colon
id|newval
op_assign
id|oldval
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;?&squot;
suffix:colon
r_goto
id|help
suffix:semicolon
r_default
suffix:colon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sym_set_tristate_value
c_func
(paren
id|sym
comma
id|newval
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|help
suffix:colon
id|help
op_assign
id|nohelp_text
suffix:semicolon
r_if
c_cond
(paren
id|sym-&gt;help
)paren
id|help
op_assign
id|sym-&gt;help
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;&bslash;n%s&bslash;n&quot;
comma
id|help
)paren
suffix:semicolon
)brace
)brace
DECL|function|conf_choice
r_static
r_int
id|conf_choice
c_func
(paren
r_struct
id|menu
op_star
id|menu
)paren
(brace
r_struct
id|symbol
op_star
id|sym
comma
op_star
id|def_sym
suffix:semicolon
r_struct
id|menu
op_star
id|child
suffix:semicolon
r_int
id|type
suffix:semicolon
r_bool
id|is_new
suffix:semicolon
id|sym
op_assign
id|menu-&gt;sym
suffix:semicolon
id|type
op_assign
id|sym_get_type
c_func
(paren
id|sym
)paren
suffix:semicolon
id|is_new
op_assign
op_logical_neg
id|sym_has_value
c_func
(paren
id|sym
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sym_is_changable
c_func
(paren
id|sym
)paren
)paren
(brace
id|conf_sym
c_func
(paren
id|menu
)paren
suffix:semicolon
id|sym_calc_value
c_func
(paren
id|sym
)paren
suffix:semicolon
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
r_return
l_int|1
suffix:semicolon
r_case
id|mod
suffix:colon
r_return
l_int|0
suffix:semicolon
r_case
id|yes
suffix:colon
r_break
suffix:semicolon
)brace
)brace
r_else
(brace
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
r_return
l_int|1
suffix:semicolon
r_case
id|mod
suffix:colon
id|printf
c_func
(paren
l_string|&quot;%*s%s&bslash;n&quot;
comma
id|indent
op_minus
l_int|1
comma
l_string|&quot;&quot;
comma
id|menu_get_prompt
c_func
(paren
id|menu
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|yes
suffix:colon
r_break
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
l_int|1
)paren
(brace
r_int
id|cnt
comma
id|def
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;%*s%s&bslash;n&quot;
comma
id|indent
op_minus
l_int|1
comma
l_string|&quot;&quot;
comma
id|menu_get_prompt
c_func
(paren
id|menu
)paren
)paren
suffix:semicolon
id|def_sym
op_assign
id|sym_get_choice_value
c_func
(paren
id|sym
)paren
suffix:semicolon
id|cnt
op_assign
id|def
op_assign
l_int|0
suffix:semicolon
id|line
(braket
l_int|0
)braket
op_assign
l_char|&squot;0&squot;
suffix:semicolon
id|line
(braket
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|child
op_assign
id|menu-&gt;list
suffix:semicolon
id|child
suffix:semicolon
id|child
op_assign
id|child-&gt;next
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|menu_is_visible
c_func
(paren
id|child
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|child-&gt;sym
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;%*c %s&bslash;n&quot;
comma
id|indent
comma
l_char|&squot;*&squot;
comma
id|menu_get_prompt
c_func
(paren
id|child
)paren
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|cnt
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|child-&gt;sym
op_eq
id|def_sym
)paren
(brace
id|def
op_assign
id|cnt
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;%*c&quot;
comma
id|indent
comma
l_char|&squot;&gt;&squot;
)paren
suffix:semicolon
)brace
r_else
id|printf
c_func
(paren
l_string|&quot;%*c&quot;
comma
id|indent
comma
l_char|&squot; &squot;
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot; %d. %s&quot;
comma
id|cnt
comma
id|menu_get_prompt
c_func
(paren
id|child
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|child-&gt;sym-&gt;name
)paren
id|printf
c_func
(paren
l_string|&quot; (%s)&quot;
comma
id|child-&gt;sym-&gt;name
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sym_has_value
c_func
(paren
id|child-&gt;sym
)paren
)paren
id|printf
c_func
(paren
l_string|&quot; (NEW)&quot;
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|printf
c_func
(paren
l_string|&quot;%*schoice&quot;
comma
id|indent
op_minus
l_int|1
comma
l_string|&quot;&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cnt
op_eq
l_int|1
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;[1]: 1&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|conf_childs
suffix:semicolon
)brace
id|printf
c_func
(paren
l_string|&quot;[1-%d&quot;
comma
id|cnt
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sym-&gt;help
)paren
id|printf
c_func
(paren
l_string|&quot;?&quot;
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;]: &quot;
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|input_mode
)paren
(brace
r_case
id|ask_new
suffix:colon
r_case
id|ask_silent
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|is_new
)paren
(brace
id|cnt
op_assign
id|def
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;%d&bslash;n&quot;
comma
id|cnt
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|check_stdin
c_func
(paren
)paren
suffix:semicolon
r_case
id|ask_all
suffix:colon
id|fflush
c_func
(paren
id|stdout
)paren
suffix:semicolon
id|fgets
c_func
(paren
id|line
comma
l_int|128
comma
id|stdin
)paren
suffix:semicolon
id|strip
c_func
(paren
id|line
)paren
suffix:semicolon
r_if
c_cond
(paren
id|line
(braket
l_int|0
)braket
op_eq
l_char|&squot;?&squot;
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;&bslash;n%s&bslash;n&quot;
comma
id|menu-&gt;sym-&gt;help
ques
c_cond
id|menu-&gt;sym-&gt;help
suffix:colon
id|nohelp_text
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|line
(braket
l_int|0
)braket
)paren
id|cnt
op_assign
id|def
suffix:semicolon
r_else
r_if
c_cond
(paren
id|isdigit
c_func
(paren
id|line
(braket
l_int|0
)braket
)paren
)paren
id|cnt
op_assign
id|atoi
c_func
(paren
id|line
)paren
suffix:semicolon
r_else
r_continue
suffix:semicolon
r_break
suffix:semicolon
r_case
id|set_random
suffix:colon
id|def
op_assign
(paren
id|random
c_func
(paren
)paren
op_mod
id|cnt
)paren
op_plus
l_int|1
suffix:semicolon
r_case
id|set_default
suffix:colon
r_case
id|set_yes
suffix:colon
r_case
id|set_mod
suffix:colon
r_case
id|set_no
suffix:colon
id|cnt
op_assign
id|def
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;%d&bslash;n&quot;
comma
id|cnt
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|conf_childs
suffix:colon
r_for
c_loop
(paren
id|child
op_assign
id|menu-&gt;list
suffix:semicolon
id|child
suffix:semicolon
id|child
op_assign
id|child-&gt;next
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|child-&gt;sym
op_logical_or
op_logical_neg
id|menu_is_visible
c_func
(paren
id|child
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_decrement
id|cnt
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|child
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|line
(braket
id|strlen
c_func
(paren
id|line
)paren
op_minus
l_int|1
)braket
op_eq
l_char|&squot;?&squot;
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;&bslash;n%s&bslash;n&quot;
comma
id|child-&gt;sym-&gt;help
ques
c_cond
id|child-&gt;sym-&gt;help
suffix:colon
id|nohelp_text
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|sym_set_choice_value
c_func
(paren
id|sym
comma
id|child-&gt;sym
)paren
suffix:semicolon
r_if
c_cond
(paren
id|child-&gt;list
)paren
(brace
id|indent
op_add_assign
l_int|2
suffix:semicolon
id|conf
c_func
(paren
id|child-&gt;list
)paren
suffix:semicolon
id|indent
op_sub_assign
l_int|2
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
)brace
DECL|function|conf
r_static
r_void
id|conf
c_func
(paren
r_struct
id|menu
op_star
id|menu
)paren
(brace
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
id|menu
op_star
id|child
suffix:semicolon
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
r_return
suffix:semicolon
id|sym
op_assign
id|menu-&gt;sym
suffix:semicolon
id|prop
op_assign
id|menu-&gt;prompt
suffix:semicolon
r_if
c_cond
(paren
id|prop
)paren
(brace
r_const
r_char
op_star
id|prompt
suffix:semicolon
r_switch
c_cond
(paren
id|prop-&gt;type
)paren
(brace
r_case
id|P_MENU
suffix:colon
r_if
c_cond
(paren
id|input_mode
op_eq
id|ask_silent
op_logical_and
id|rootEntry
op_ne
id|menu
)paren
(brace
id|check_conf
c_func
(paren
id|menu
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_case
id|P_COMMENT
suffix:colon
id|prompt
op_assign
id|menu_get_prompt
c_func
(paren
id|menu
)paren
suffix:semicolon
r_if
c_cond
(paren
id|prompt
)paren
id|printf
c_func
(paren
l_string|&quot;%*c&bslash;n%*c %s&bslash;n%*c&bslash;n&quot;
comma
id|indent
comma
l_char|&squot;*&squot;
comma
id|indent
comma
l_char|&squot;*&squot;
comma
id|prompt
comma
id|indent
comma
l_char|&squot;*&squot;
)paren
suffix:semicolon
r_default
suffix:colon
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|sym
)paren
r_goto
id|conf_childs
suffix:semicolon
r_if
c_cond
(paren
id|sym_is_choice
c_func
(paren
id|sym
)paren
)paren
(brace
id|conf_choice
c_func
(paren
id|menu
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sym-&gt;curr.tri
op_ne
id|mod
)paren
r_return
suffix:semicolon
r_goto
id|conf_childs
suffix:semicolon
)brace
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
id|conf_string
c_func
(paren
id|menu
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|conf_sym
c_func
(paren
id|menu
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|conf_childs
suffix:colon
r_if
c_cond
(paren
id|sym
)paren
id|indent
op_add_assign
l_int|2
suffix:semicolon
r_for
c_loop
(paren
id|child
op_assign
id|menu-&gt;list
suffix:semicolon
id|child
suffix:semicolon
id|child
op_assign
id|child-&gt;next
)paren
id|conf
c_func
(paren
id|child
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sym
)paren
id|indent
op_sub_assign
l_int|2
suffix:semicolon
)brace
DECL|function|check_conf
r_static
r_void
id|check_conf
c_func
(paren
r_struct
id|menu
op_star
id|menu
)paren
(brace
r_struct
id|symbol
op_star
id|sym
suffix:semicolon
r_struct
id|menu
op_star
id|child
suffix:semicolon
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
r_return
suffix:semicolon
id|sym
op_assign
id|menu-&gt;sym
suffix:semicolon
r_if
c_cond
(paren
id|sym
)paren
(brace
r_if
c_cond
(paren
id|sym_is_changable
c_func
(paren
id|sym
)paren
op_logical_and
op_logical_neg
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
op_logical_neg
id|conf_cnt
op_increment
)paren
id|printf
c_func
(paren
l_string|&quot;*&bslash;n* Restart config...&bslash;n*&bslash;n&quot;
)paren
suffix:semicolon
id|rootEntry
op_assign
id|menu_get_parent_menu
c_func
(paren
id|menu
)paren
suffix:semicolon
id|conf
c_func
(paren
id|rootEntry
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sym_is_choice
c_func
(paren
id|sym
)paren
op_logical_and
id|sym_get_tristate_value
c_func
(paren
id|sym
)paren
op_ne
id|mod
)paren
r_return
suffix:semicolon
)brace
r_for
c_loop
(paren
id|child
op_assign
id|menu-&gt;list
suffix:semicolon
id|child
suffix:semicolon
id|child
op_assign
id|child-&gt;next
)paren
id|check_conf
c_func
(paren
id|child
)paren
suffix:semicolon
)brace
DECL|function|main
r_int
id|main
c_func
(paren
r_int
id|ac
comma
r_char
op_star
op_star
id|av
)paren
(brace
r_int
id|i
op_assign
l_int|1
suffix:semicolon
r_const
r_char
op_star
id|name
suffix:semicolon
r_struct
id|stat
id|tmpstat
suffix:semicolon
r_if
c_cond
(paren
id|ac
OG
id|i
op_logical_and
id|av
(braket
id|i
)braket
(braket
l_int|0
)braket
op_eq
l_char|&squot;-&squot;
)paren
(brace
r_switch
c_cond
(paren
id|av
(braket
id|i
op_increment
)braket
(braket
l_int|1
)braket
)paren
(brace
r_case
l_char|&squot;o&squot;
suffix:colon
id|input_mode
op_assign
id|ask_new
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;s&squot;
suffix:colon
id|input_mode
op_assign
id|ask_silent
suffix:semicolon
id|valid_stdin
op_assign
id|isatty
c_func
(paren
l_int|0
)paren
op_logical_and
id|isatty
c_func
(paren
l_int|1
)paren
op_logical_and
id|isatty
c_func
(paren
l_int|2
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;d&squot;
suffix:colon
id|input_mode
op_assign
id|set_default
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;D&squot;
suffix:colon
id|input_mode
op_assign
id|set_default
suffix:semicolon
id|defconfig_file
op_assign
id|av
(braket
id|i
op_increment
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|defconfig_file
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;%s: No default config file specified&bslash;n&quot;
comma
id|av
(braket
l_int|0
)braket
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
r_case
l_char|&squot;n&squot;
suffix:colon
id|input_mode
op_assign
id|set_no
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;m&squot;
suffix:colon
id|input_mode
op_assign
id|set_mod
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;y&squot;
suffix:colon
id|input_mode
op_assign
id|set_yes
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;r&squot;
suffix:colon
id|input_mode
op_assign
id|set_random
suffix:semicolon
id|srandom
c_func
(paren
id|time
c_func
(paren
l_int|NULL
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;h&squot;
suffix:colon
r_case
l_char|&squot;?&squot;
suffix:colon
id|printf
c_func
(paren
l_string|&quot;%s [-o|-s] config&bslash;n&quot;
comma
id|av
(braket
l_int|0
)braket
)paren
suffix:semicolon
m_exit
(paren
l_int|0
)paren
suffix:semicolon
)brace
)brace
id|name
op_assign
id|av
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|name
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;%s: Kconfig file missing&bslash;n&quot;
comma
id|av
(braket
l_int|0
)braket
)paren
suffix:semicolon
)brace
id|conf_parse
c_func
(paren
id|name
)paren
suffix:semicolon
singleline_comment|//zconfdump(stdout);
r_switch
c_cond
(paren
id|input_mode
)paren
(brace
r_case
id|set_default
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|defconfig_file
)paren
id|defconfig_file
op_assign
id|conf_get_default_confname
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|conf_read
c_func
(paren
id|defconfig_file
)paren
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;***&bslash;n&quot;
l_string|&quot;*** Can&squot;t find default configuration &bslash;&quot;%s&bslash;&quot;!&bslash;n&quot;
l_string|&quot;***&bslash;n&quot;
comma
id|defconfig_file
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
r_case
id|ask_silent
suffix:colon
r_if
c_cond
(paren
id|stat
c_func
(paren
l_string|&quot;.config&quot;
comma
op_amp
id|tmpstat
)paren
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;***&bslash;n&quot;
l_string|&quot;*** You have not yet configured your kernel!&bslash;n&quot;
l_string|&quot;***&bslash;n&quot;
l_string|&quot;*** Please run some configurator (e.g. &bslash;&quot;make oldconfig&bslash;&quot; or&bslash;n&quot;
l_string|&quot;*** &bslash;&quot;make menuconfig&bslash;&quot; or &bslash;&quot;make xconfig&bslash;&quot;).&bslash;n&quot;
l_string|&quot;***&bslash;n&quot;
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
r_case
id|ask_all
suffix:colon
r_case
id|ask_new
suffix:colon
id|conf_read
c_func
(paren
l_int|NULL
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|input_mode
op_ne
id|ask_silent
)paren
(brace
id|rootEntry
op_assign
op_amp
id|rootmenu
suffix:semicolon
id|conf
c_func
(paren
op_amp
id|rootmenu
)paren
suffix:semicolon
r_if
c_cond
(paren
id|input_mode
op_eq
id|ask_all
)paren
(brace
id|input_mode
op_assign
id|ask_silent
suffix:semicolon
id|valid_stdin
op_assign
l_int|1
suffix:semicolon
)brace
)brace
r_do
(brace
id|conf_cnt
op_assign
l_int|0
suffix:semicolon
id|check_conf
c_func
(paren
op_amp
id|rootmenu
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|conf_cnt
)paren
suffix:semicolon
id|conf_write
c_func
(paren
l_int|NULL
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
