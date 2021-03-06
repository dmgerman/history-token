multiline_comment|/*&n; * Copyright (C) 2002 Roman Zippel &lt;zippel@linux-m68k.org&gt;&n; * Released under the terms of the GNU GPL v2.0.&n; */
macro_line|#ifndef EXPR_H
DECL|macro|EXPR_H
mdefine_line|#define EXPR_H
macro_line|#ifdef __cplusplus
r_extern
l_string|&quot;C&quot;
(brace
macro_line|#endif
macro_line|#include &lt;stdio.h&gt;
macro_line|#ifndef __cplusplus
macro_line|#include &lt;stdbool.h&gt;
macro_line|#endif
DECL|struct|file
r_struct
id|file
(brace
DECL|member|next
r_struct
id|file
op_star
id|next
suffix:semicolon
DECL|member|parent
r_struct
id|file
op_star
id|parent
suffix:semicolon
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|lineno
r_int
id|lineno
suffix:semicolon
DECL|member|flags
r_int
id|flags
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|FILE_BUSY
mdefine_line|#define FILE_BUSY&t;&t;0x0001
DECL|macro|FILE_SCANNED
mdefine_line|#define FILE_SCANNED&t;&t;0x0002
DECL|macro|FILE_PRINTED
mdefine_line|#define FILE_PRINTED&t;&t;0x0004
DECL|enum|tristate
r_typedef
r_enum
id|tristate
(brace
DECL|enumerator|no
DECL|enumerator|mod
DECL|enumerator|yes
id|no
comma
id|mod
comma
id|yes
DECL|typedef|tristate
)brace
id|tristate
suffix:semicolon
DECL|enum|expr_type
r_enum
id|expr_type
(brace
DECL|enumerator|E_NONE
DECL|enumerator|E_OR
DECL|enumerator|E_AND
DECL|enumerator|E_NOT
DECL|enumerator|E_EQUAL
DECL|enumerator|E_UNEQUAL
DECL|enumerator|E_CHOICE
DECL|enumerator|E_SYMBOL
DECL|enumerator|E_RANGE
id|E_NONE
comma
id|E_OR
comma
id|E_AND
comma
id|E_NOT
comma
id|E_EQUAL
comma
id|E_UNEQUAL
comma
id|E_CHOICE
comma
id|E_SYMBOL
comma
id|E_RANGE
)brace
suffix:semicolon
DECL|union|expr_data
r_union
id|expr_data
(brace
DECL|member|expr
r_struct
id|expr
op_star
id|expr
suffix:semicolon
DECL|member|sym
r_struct
id|symbol
op_star
id|sym
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|expr
r_struct
id|expr
(brace
DECL|member|type
r_enum
id|expr_type
id|type
suffix:semicolon
DECL|member|left
DECL|member|right
r_union
id|expr_data
id|left
comma
id|right
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|E_OR
mdefine_line|#define E_OR(dep1, dep2)&t;(((dep1)&gt;(dep2))?(dep1):(dep2))
DECL|macro|E_AND
mdefine_line|#define E_AND(dep1, dep2)&t;(((dep1)&lt;(dep2))?(dep1):(dep2))
DECL|macro|E_NOT
mdefine_line|#define E_NOT(dep)&t;&t;(2-(dep))
DECL|struct|expr_value
r_struct
id|expr_value
(brace
DECL|member|expr
r_struct
id|expr
op_star
id|expr
suffix:semicolon
DECL|member|tri
id|tristate
id|tri
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|symbol_value
r_struct
id|symbol_value
(brace
DECL|member|val
r_void
op_star
id|val
suffix:semicolon
DECL|member|tri
id|tristate
id|tri
suffix:semicolon
)brace
suffix:semicolon
DECL|enum|symbol_type
r_enum
id|symbol_type
(brace
DECL|enumerator|S_UNKNOWN
DECL|enumerator|S_BOOLEAN
DECL|enumerator|S_TRISTATE
DECL|enumerator|S_INT
DECL|enumerator|S_HEX
DECL|enumerator|S_STRING
DECL|enumerator|S_OTHER
id|S_UNKNOWN
comma
id|S_BOOLEAN
comma
id|S_TRISTATE
comma
id|S_INT
comma
id|S_HEX
comma
id|S_STRING
comma
id|S_OTHER
)brace
suffix:semicolon
DECL|struct|symbol
r_struct
id|symbol
(brace
DECL|member|next
r_struct
id|symbol
op_star
id|next
suffix:semicolon
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|help
r_char
op_star
id|help
suffix:semicolon
DECL|member|type
r_enum
id|symbol_type
id|type
suffix:semicolon
DECL|member|curr
DECL|member|user
r_struct
id|symbol_value
id|curr
comma
id|user
suffix:semicolon
DECL|member|visible
id|tristate
id|visible
suffix:semicolon
DECL|member|flags
r_int
id|flags
suffix:semicolon
DECL|member|prop
r_struct
id|property
op_star
id|prop
suffix:semicolon
DECL|member|dep
DECL|member|dep2
r_struct
id|expr
op_star
id|dep
comma
op_star
id|dep2
suffix:semicolon
DECL|member|rev_dep
r_struct
id|expr_value
id|rev_dep
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|for_all_symbols
mdefine_line|#define for_all_symbols(i, sym) for (i = 0; i &lt; 257; i++) for (sym = symbol_hash[i]; sym; sym = sym-&gt;next) if (sym-&gt;type != S_OTHER)
DECL|macro|SYMBOL_YES
mdefine_line|#define SYMBOL_YES&t;&t;0x0001
DECL|macro|SYMBOL_MOD
mdefine_line|#define SYMBOL_MOD&t;&t;0x0002
DECL|macro|SYMBOL_NO
mdefine_line|#define SYMBOL_NO&t;&t;0x0004
DECL|macro|SYMBOL_CONST
mdefine_line|#define SYMBOL_CONST&t;&t;0x0007
DECL|macro|SYMBOL_CHECK
mdefine_line|#define SYMBOL_CHECK&t;&t;0x0008
DECL|macro|SYMBOL_CHOICE
mdefine_line|#define SYMBOL_CHOICE&t;&t;0x0010
DECL|macro|SYMBOL_CHOICEVAL
mdefine_line|#define SYMBOL_CHOICEVAL&t;0x0020
DECL|macro|SYMBOL_PRINTED
mdefine_line|#define SYMBOL_PRINTED&t;&t;0x0040
DECL|macro|SYMBOL_VALID
mdefine_line|#define SYMBOL_VALID&t;&t;0x0080
DECL|macro|SYMBOL_OPTIONAL
mdefine_line|#define SYMBOL_OPTIONAL&t;&t;0x0100
DECL|macro|SYMBOL_WRITE
mdefine_line|#define SYMBOL_WRITE&t;&t;0x0200
DECL|macro|SYMBOL_CHANGED
mdefine_line|#define SYMBOL_CHANGED&t;&t;0x0400
DECL|macro|SYMBOL_NEW
mdefine_line|#define SYMBOL_NEW&t;&t;0x0800
DECL|macro|SYMBOL_AUTO
mdefine_line|#define SYMBOL_AUTO&t;&t;0x1000
DECL|macro|SYMBOL_CHECKED
mdefine_line|#define SYMBOL_CHECKED&t;&t;0x2000
DECL|macro|SYMBOL_CHECK_DONE
mdefine_line|#define SYMBOL_CHECK_DONE&t;0x4000
DECL|macro|SYMBOL_WARNED
mdefine_line|#define SYMBOL_WARNED&t;&t;0x8000
DECL|macro|SYMBOL_MAXLENGTH
mdefine_line|#define SYMBOL_MAXLENGTH&t;256
DECL|macro|SYMBOL_HASHSIZE
mdefine_line|#define SYMBOL_HASHSIZE&t;&t;257
DECL|macro|SYMBOL_HASHMASK
mdefine_line|#define SYMBOL_HASHMASK&t;&t;0xff
DECL|enum|prop_type
r_enum
id|prop_type
(brace
DECL|enumerator|P_UNKNOWN
DECL|enumerator|P_PROMPT
DECL|enumerator|P_COMMENT
DECL|enumerator|P_MENU
DECL|enumerator|P_DEFAULT
DECL|enumerator|P_CHOICE
DECL|enumerator|P_SELECT
DECL|enumerator|P_RANGE
id|P_UNKNOWN
comma
id|P_PROMPT
comma
id|P_COMMENT
comma
id|P_MENU
comma
id|P_DEFAULT
comma
id|P_CHOICE
comma
id|P_SELECT
comma
id|P_RANGE
)brace
suffix:semicolon
DECL|struct|property
r_struct
id|property
(brace
DECL|member|next
r_struct
id|property
op_star
id|next
suffix:semicolon
DECL|member|sym
r_struct
id|symbol
op_star
id|sym
suffix:semicolon
DECL|member|type
r_enum
id|prop_type
id|type
suffix:semicolon
DECL|member|text
r_const
r_char
op_star
id|text
suffix:semicolon
DECL|member|visible
r_struct
id|expr_value
id|visible
suffix:semicolon
DECL|member|expr
r_struct
id|expr
op_star
id|expr
suffix:semicolon
DECL|member|menu
r_struct
id|menu
op_star
id|menu
suffix:semicolon
DECL|member|file
r_struct
id|file
op_star
id|file
suffix:semicolon
DECL|member|lineno
r_int
id|lineno
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|for_all_properties
mdefine_line|#define for_all_properties(sym, st, tok) &bslash;&n;&t;for (st = sym-&gt;prop; st; st = st-&gt;next) &bslash;&n;&t;&t;if (st-&gt;type == (tok))
DECL|macro|for_all_defaults
mdefine_line|#define for_all_defaults(sym, st) for_all_properties(sym, st, P_DEFAULT)
DECL|macro|for_all_choices
mdefine_line|#define for_all_choices(sym, st) for_all_properties(sym, st, P_CHOICE)
DECL|macro|for_all_prompts
mdefine_line|#define for_all_prompts(sym, st) &bslash;&n;&t;for (st = sym-&gt;prop; st; st = st-&gt;next) &bslash;&n;&t;&t;if (st-&gt;text)
DECL|struct|menu
r_struct
id|menu
(brace
DECL|member|next
r_struct
id|menu
op_star
id|next
suffix:semicolon
DECL|member|parent
r_struct
id|menu
op_star
id|parent
suffix:semicolon
DECL|member|list
r_struct
id|menu
op_star
id|list
suffix:semicolon
DECL|member|sym
r_struct
id|symbol
op_star
id|sym
suffix:semicolon
DECL|member|prompt
r_struct
id|property
op_star
id|prompt
suffix:semicolon
DECL|member|dep
r_struct
id|expr
op_star
id|dep
suffix:semicolon
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
singleline_comment|//char *help;
DECL|member|file
r_struct
id|file
op_star
id|file
suffix:semicolon
DECL|member|lineno
r_int
id|lineno
suffix:semicolon
DECL|member|data
r_void
op_star
id|data
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|MENU_CHANGED
mdefine_line|#define MENU_CHANGED&t;&t;0x0001
DECL|macro|MENU_ROOT
mdefine_line|#define MENU_ROOT&t;&t;0x0002
macro_line|#ifndef SWIG
r_extern
r_struct
id|file
op_star
id|file_list
suffix:semicolon
r_extern
r_struct
id|file
op_star
id|current_file
suffix:semicolon
r_struct
id|file
op_star
id|lookup_file
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
id|symbol
id|symbol_yes
comma
id|symbol_no
comma
id|symbol_mod
suffix:semicolon
r_extern
r_struct
id|symbol
op_star
id|modules_sym
suffix:semicolon
r_extern
r_int
id|cdebug
suffix:semicolon
r_struct
id|expr
op_star
id|expr_alloc_symbol
c_func
(paren
r_struct
id|symbol
op_star
id|sym
)paren
suffix:semicolon
r_struct
id|expr
op_star
id|expr_alloc_one
c_func
(paren
r_enum
id|expr_type
id|type
comma
r_struct
id|expr
op_star
id|ce
)paren
suffix:semicolon
r_struct
id|expr
op_star
id|expr_alloc_two
c_func
(paren
r_enum
id|expr_type
id|type
comma
r_struct
id|expr
op_star
id|e1
comma
r_struct
id|expr
op_star
id|e2
)paren
suffix:semicolon
r_struct
id|expr
op_star
id|expr_alloc_comp
c_func
(paren
r_enum
id|expr_type
id|type
comma
r_struct
id|symbol
op_star
id|s1
comma
r_struct
id|symbol
op_star
id|s2
)paren
suffix:semicolon
r_struct
id|expr
op_star
id|expr_alloc_and
c_func
(paren
r_struct
id|expr
op_star
id|e1
comma
r_struct
id|expr
op_star
id|e2
)paren
suffix:semicolon
r_struct
id|expr
op_star
id|expr_alloc_or
c_func
(paren
r_struct
id|expr
op_star
id|e1
comma
r_struct
id|expr
op_star
id|e2
)paren
suffix:semicolon
r_struct
id|expr
op_star
id|expr_copy
c_func
(paren
r_struct
id|expr
op_star
id|org
)paren
suffix:semicolon
r_void
id|expr_free
c_func
(paren
r_struct
id|expr
op_star
id|e
)paren
suffix:semicolon
r_int
id|expr_eq
c_func
(paren
r_struct
id|expr
op_star
id|e1
comma
r_struct
id|expr
op_star
id|e2
)paren
suffix:semicolon
r_void
id|expr_eliminate_eq
c_func
(paren
r_struct
id|expr
op_star
op_star
id|ep1
comma
r_struct
id|expr
op_star
op_star
id|ep2
)paren
suffix:semicolon
id|tristate
id|expr_calc_value
c_func
(paren
r_struct
id|expr
op_star
id|e
)paren
suffix:semicolon
r_struct
id|expr
op_star
id|expr_eliminate_yn
c_func
(paren
r_struct
id|expr
op_star
id|e
)paren
suffix:semicolon
r_struct
id|expr
op_star
id|expr_trans_bool
c_func
(paren
r_struct
id|expr
op_star
id|e
)paren
suffix:semicolon
r_struct
id|expr
op_star
id|expr_eliminate_dups
c_func
(paren
r_struct
id|expr
op_star
id|e
)paren
suffix:semicolon
r_struct
id|expr
op_star
id|expr_transform
c_func
(paren
r_struct
id|expr
op_star
id|e
)paren
suffix:semicolon
r_int
id|expr_contains_symbol
c_func
(paren
r_struct
id|expr
op_star
id|dep
comma
r_struct
id|symbol
op_star
id|sym
)paren
suffix:semicolon
r_bool
id|expr_depends_symbol
c_func
(paren
r_struct
id|expr
op_star
id|dep
comma
r_struct
id|symbol
op_star
id|sym
)paren
suffix:semicolon
r_struct
id|expr
op_star
id|expr_extract_eq_and
c_func
(paren
r_struct
id|expr
op_star
op_star
id|ep1
comma
r_struct
id|expr
op_star
op_star
id|ep2
)paren
suffix:semicolon
r_struct
id|expr
op_star
id|expr_extract_eq_or
c_func
(paren
r_struct
id|expr
op_star
op_star
id|ep1
comma
r_struct
id|expr
op_star
op_star
id|ep2
)paren
suffix:semicolon
r_void
id|expr_extract_eq
c_func
(paren
r_enum
id|expr_type
id|type
comma
r_struct
id|expr
op_star
op_star
id|ep
comma
r_struct
id|expr
op_star
op_star
id|ep1
comma
r_struct
id|expr
op_star
op_star
id|ep2
)paren
suffix:semicolon
r_struct
id|expr
op_star
id|expr_trans_compare
c_func
(paren
r_struct
id|expr
op_star
id|e
comma
r_enum
id|expr_type
id|type
comma
r_struct
id|symbol
op_star
id|sym
)paren
suffix:semicolon
r_void
id|expr_fprint
c_func
(paren
r_struct
id|expr
op_star
id|e
comma
id|FILE
op_star
id|out
)paren
suffix:semicolon
r_struct
id|gstr
suffix:semicolon
multiline_comment|/* forward */
r_void
id|expr_gstr_print
c_func
(paren
r_struct
id|expr
op_star
id|e
comma
r_struct
id|gstr
op_star
id|gs
)paren
suffix:semicolon
DECL|function|expr_is_yes
r_static
r_inline
r_int
id|expr_is_yes
c_func
(paren
r_struct
id|expr
op_star
id|e
)paren
(brace
r_return
op_logical_neg
id|e
op_logical_or
(paren
id|e-&gt;type
op_eq
id|E_SYMBOL
op_logical_and
id|e-&gt;left.sym
op_eq
op_amp
id|symbol_yes
)paren
suffix:semicolon
)brace
DECL|function|expr_is_no
r_static
r_inline
r_int
id|expr_is_no
c_func
(paren
r_struct
id|expr
op_star
id|e
)paren
(brace
r_return
id|e
op_logical_and
(paren
id|e-&gt;type
op_eq
id|E_SYMBOL
op_logical_and
id|e-&gt;left.sym
op_eq
op_amp
id|symbol_no
)paren
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifdef __cplusplus
)brace
macro_line|#endif
macro_line|#endif /* EXPR_H */
eof
