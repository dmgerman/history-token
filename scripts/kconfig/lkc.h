multiline_comment|/*&n; * Copyright (C) 2002 Roman Zippel &lt;zippel@linux-m68k.org&gt;&n; * Released under the terms of the GNU GPL v2.0.&n; */
macro_line|#ifndef LKC_H
DECL|macro|LKC_H
mdefine_line|#define LKC_H
macro_line|#include &quot;expr.h&quot;
macro_line|#ifdef __cplusplus
r_extern
l_string|&quot;C&quot;
(brace
macro_line|#endif
macro_line|#ifdef LKC_DIRECT_LINK
DECL|macro|P
mdefine_line|#define P(name,type,arg)&t;extern type name arg
macro_line|#else
macro_line|#include &quot;lkc_defs.h&quot;
DECL|macro|P
mdefine_line|#define P(name,type,arg)&t;extern type (*name ## _p) arg
macro_line|#endif
macro_line|#include &quot;lkc_proto.h&quot;
DECL|macro|P
macro_line|#undef P
DECL|macro|SRCTREE
mdefine_line|#define SRCTREE &quot;srctree&quot;
r_int
id|zconfparse
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|zconfdump
c_func
(paren
id|FILE
op_star
id|out
)paren
suffix:semicolon
r_extern
r_int
id|zconfdebug
suffix:semicolon
r_void
id|zconf_starthelp
c_func
(paren
r_void
)paren
suffix:semicolon
id|FILE
op_star
id|zconf_fopen
c_func
(paren
r_const
r_char
op_star
id|name
)paren
suffix:semicolon
r_void
id|zconf_initscan
c_func
(paren
r_const
r_char
op_star
id|name
)paren
suffix:semicolon
r_void
id|zconf_nextfile
c_func
(paren
r_const
r_char
op_star
id|name
)paren
suffix:semicolon
r_int
id|zconf_lineno
c_func
(paren
r_void
)paren
suffix:semicolon
r_char
op_star
id|zconf_curname
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* confdata.c */
r_extern
r_const
r_char
id|conf_def_filename
(braket
)braket
suffix:semicolon
r_extern
r_char
id|conf_filename
(braket
)braket
suffix:semicolon
r_char
op_star
id|conf_get_default_confname
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* kconfig_load.c */
r_void
id|kconfig_load
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* menu.c */
r_void
id|menu_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|menu_add_menu
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|menu_end_menu
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|menu_add_entry
c_func
(paren
r_struct
id|symbol
op_star
id|sym
)paren
suffix:semicolon
r_void
id|menu_end_entry
c_func
(paren
r_void
)paren
suffix:semicolon
r_struct
id|property
op_star
id|create_prop
c_func
(paren
r_enum
id|prop_type
id|type
)paren
suffix:semicolon
r_void
id|menu_add_dep
c_func
(paren
r_struct
id|expr
op_star
id|dep
)paren
suffix:semicolon
r_struct
id|property
op_star
id|menu_add_prop
c_func
(paren
r_int
id|token
comma
r_char
op_star
id|prompt
comma
r_struct
id|symbol
op_star
id|def
comma
r_struct
id|expr
op_star
id|dep
)paren
suffix:semicolon
r_void
id|menu_finalize
c_func
(paren
r_struct
id|menu
op_star
id|parent
)paren
suffix:semicolon
r_void
id|menu_set_type
c_func
(paren
r_int
id|type
)paren
suffix:semicolon
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
suffix:semicolon
r_int
id|file_write_dep
c_func
(paren
r_const
r_char
op_star
id|name
)paren
suffix:semicolon
r_extern
r_struct
id|menu
op_star
id|current_entry
suffix:semicolon
r_extern
r_struct
id|menu
op_star
id|current_menu
suffix:semicolon
multiline_comment|/* symbol.c */
r_void
id|sym_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|sym_clear_all_valid
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|sym_set_changed
c_func
(paren
r_struct
id|symbol
op_star
id|sym
)paren
suffix:semicolon
DECL|function|sym_get_tristate_value
r_static
r_inline
id|tristate
id|sym_get_tristate_value
c_func
(paren
r_struct
id|symbol
op_star
id|sym
)paren
(brace
r_return
id|S_TRI
c_func
(paren
id|sym-&gt;curr
)paren
suffix:semicolon
)brace
DECL|function|sym_get_choice_value
r_static
r_inline
r_struct
id|symbol
op_star
id|sym_get_choice_value
c_func
(paren
r_struct
id|symbol
op_star
id|sym
)paren
(brace
r_return
(paren
r_struct
id|symbol
op_star
)paren
id|S_VAL
c_func
(paren
id|sym-&gt;curr
)paren
suffix:semicolon
)brace
DECL|function|sym_set_choice_value
r_static
r_inline
r_bool
id|sym_set_choice_value
c_func
(paren
r_struct
id|symbol
op_star
id|ch
comma
r_struct
id|symbol
op_star
id|chval
)paren
(brace
r_return
id|sym_set_tristate_value
c_func
(paren
id|chval
comma
id|yes
)paren
suffix:semicolon
)brace
DECL|function|sym_is_choice
r_static
r_inline
r_bool
id|sym_is_choice
c_func
(paren
r_struct
id|symbol
op_star
id|sym
)paren
(brace
r_return
id|sym-&gt;flags
op_amp
id|SYMBOL_CHOICE
ques
c_cond
l_bool|true
suffix:colon
l_bool|false
suffix:semicolon
)brace
DECL|function|sym_is_choice_value
r_static
r_inline
r_bool
id|sym_is_choice_value
c_func
(paren
r_struct
id|symbol
op_star
id|sym
)paren
(brace
r_return
id|sym-&gt;flags
op_amp
id|SYMBOL_CHOICEVAL
ques
c_cond
l_bool|true
suffix:colon
l_bool|false
suffix:semicolon
)brace
DECL|function|sym_is_optional
r_static
r_inline
r_bool
id|sym_is_optional
c_func
(paren
r_struct
id|symbol
op_star
id|sym
)paren
(brace
r_return
id|sym-&gt;flags
op_amp
id|SYMBOL_OPTIONAL
ques
c_cond
l_bool|true
suffix:colon
l_bool|false
suffix:semicolon
)brace
DECL|function|sym_has_value
r_static
r_inline
r_bool
id|sym_has_value
c_func
(paren
r_struct
id|symbol
op_star
id|sym
)paren
(brace
singleline_comment|//return S_VAL(sym-&gt;def) != NULL;
r_return
id|sym-&gt;flags
op_amp
id|SYMBOL_NEW
ques
c_cond
l_bool|false
suffix:colon
l_bool|true
suffix:semicolon
)brace
macro_line|#ifdef __cplusplus
)brace
macro_line|#endif
macro_line|#endif /* LKC_H */
eof
