multiline_comment|/*&n; * Copyright (C) 2002 Roman Zippel &lt;zippel@linux-m68k.org&gt;&n; * Released under the terms of the GNU GPL v2.0.&n; */
macro_line|#include &lt;stdlib.h&gt;
macro_line|#include &lt;string.h&gt;
DECL|macro|LKC_DIRECT_LINK
mdefine_line|#define LKC_DIRECT_LINK
macro_line|#include &quot;lkc.h&quot;
DECL|variable|rootmenu
r_struct
id|menu
id|rootmenu
suffix:semicolon
DECL|variable|current_menu
DECL|variable|current_entry
r_struct
id|menu
op_star
id|current_menu
comma
op_star
id|current_entry
suffix:semicolon
DECL|variable|last_entry_ptr
r_static
r_struct
id|menu
op_star
op_star
id|last_entry_ptr
suffix:semicolon
DECL|variable|file_list
r_struct
id|file
op_star
id|file_list
suffix:semicolon
DECL|variable|current_file
r_struct
id|file
op_star
id|current_file
suffix:semicolon
DECL|function|menu_init
r_void
id|menu_init
c_func
(paren
r_void
)paren
(brace
id|current_entry
op_assign
id|current_menu
op_assign
op_amp
id|rootmenu
suffix:semicolon
id|last_entry_ptr
op_assign
op_amp
id|rootmenu.list
suffix:semicolon
)brace
DECL|function|menu_add_entry
r_void
id|menu_add_entry
c_func
(paren
r_struct
id|symbol
op_star
id|sym
)paren
(brace
r_struct
id|menu
op_star
id|menu
suffix:semicolon
id|menu
op_assign
id|malloc
c_func
(paren
r_sizeof
(paren
op_star
id|menu
)paren
)paren
suffix:semicolon
id|memset
c_func
(paren
id|menu
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|menu
)paren
)paren
suffix:semicolon
id|menu-&gt;sym
op_assign
id|sym
suffix:semicolon
id|menu-&gt;parent
op_assign
id|current_menu
suffix:semicolon
id|menu-&gt;file
op_assign
id|current_file
suffix:semicolon
id|menu-&gt;lineno
op_assign
id|zconf_lineno
c_func
(paren
)paren
suffix:semicolon
op_star
id|last_entry_ptr
op_assign
id|menu
suffix:semicolon
id|last_entry_ptr
op_assign
op_amp
id|menu-&gt;next
suffix:semicolon
id|current_entry
op_assign
id|menu
suffix:semicolon
)brace
DECL|function|menu_end_entry
r_void
id|menu_end_entry
c_func
(paren
r_void
)paren
(brace
)brace
DECL|function|menu_add_menu
r_void
id|menu_add_menu
c_func
(paren
r_void
)paren
(brace
id|current_menu
op_assign
id|current_entry
suffix:semicolon
id|last_entry_ptr
op_assign
op_amp
id|current_entry-&gt;list
suffix:semicolon
)brace
DECL|function|menu_end_menu
r_void
id|menu_end_menu
c_func
(paren
r_void
)paren
(brace
id|last_entry_ptr
op_assign
op_amp
id|current_menu-&gt;next
suffix:semicolon
id|current_menu
op_assign
id|current_menu-&gt;parent
suffix:semicolon
)brace
DECL|function|menu_check_dep
r_struct
id|expr
op_star
id|menu_check_dep
c_func
(paren
r_struct
id|expr
op_star
id|e
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|e
)paren
r_return
id|e
suffix:semicolon
r_switch
c_cond
(paren
id|e-&gt;type
)paren
(brace
r_case
id|E_NOT
suffix:colon
id|e-&gt;left.expr
op_assign
id|menu_check_dep
c_func
(paren
id|e-&gt;left.expr
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|E_OR
suffix:colon
r_case
id|E_AND
suffix:colon
id|e-&gt;left.expr
op_assign
id|menu_check_dep
c_func
(paren
id|e-&gt;left.expr
)paren
suffix:semicolon
id|e-&gt;right.expr
op_assign
id|menu_check_dep
c_func
(paren
id|e-&gt;right.expr
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|E_SYMBOL
suffix:colon
multiline_comment|/* change &squot;m&squot; into &squot;m&squot; &amp;&amp; MODULES */
r_if
c_cond
(paren
id|e-&gt;left.sym
op_eq
op_amp
id|symbol_mod
)paren
r_return
id|expr_alloc_and
c_func
(paren
id|e
comma
id|expr_alloc_symbol
c_func
(paren
id|modules_sym
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
r_return
id|e
suffix:semicolon
)brace
DECL|function|menu_add_dep
r_void
id|menu_add_dep
c_func
(paren
r_struct
id|expr
op_star
id|dep
)paren
(brace
id|current_entry-&gt;dep
op_assign
id|expr_alloc_and
c_func
(paren
id|current_entry-&gt;dep
comma
id|menu_check_dep
c_func
(paren
id|dep
)paren
)paren
suffix:semicolon
)brace
DECL|function|menu_set_type
r_void
id|menu_set_type
c_func
(paren
r_int
id|type
)paren
(brace
r_struct
id|symbol
op_star
id|sym
op_assign
id|current_entry-&gt;sym
suffix:semicolon
r_if
c_cond
(paren
id|sym-&gt;type
op_eq
id|type
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|sym-&gt;type
op_eq
id|S_UNKNOWN
)paren
(brace
id|sym-&gt;type
op_assign
id|type
suffix:semicolon
r_return
suffix:semicolon
)brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;%s:%d: type of &squot;%s&squot; redefined from &squot;%s&squot; to &squot;%s&squot;&bslash;n&quot;
comma
id|current_entry-&gt;file-&gt;name
comma
id|current_entry-&gt;lineno
comma
id|sym-&gt;name
ques
c_cond
id|sym-&gt;name
suffix:colon
l_string|&quot;&lt;choice&gt;&quot;
comma
id|sym_type_name
c_func
(paren
id|sym-&gt;type
)paren
comma
id|sym_type_name
c_func
(paren
id|type
)paren
)paren
suffix:semicolon
)brace
DECL|function|create_prop
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
(brace
r_struct
id|property
op_star
id|prop
suffix:semicolon
id|prop
op_assign
id|malloc
c_func
(paren
r_sizeof
(paren
op_star
id|prop
)paren
)paren
suffix:semicolon
id|memset
c_func
(paren
id|prop
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|prop
)paren
)paren
suffix:semicolon
id|prop-&gt;type
op_assign
id|type
suffix:semicolon
id|prop-&gt;file
op_assign
id|current_file
suffix:semicolon
id|prop-&gt;lineno
op_assign
id|zconf_lineno
c_func
(paren
)paren
suffix:semicolon
r_return
id|prop
suffix:semicolon
)brace
DECL|function|menu_add_prop
r_struct
id|property
op_star
id|menu_add_prop
c_func
(paren
r_enum
id|prop_type
id|type
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
(brace
r_struct
id|property
op_star
id|prop
op_assign
id|create_prop
c_func
(paren
id|type
)paren
suffix:semicolon
r_struct
id|property
op_star
op_star
id|propp
suffix:semicolon
id|prop-&gt;sym
op_assign
id|current_entry-&gt;sym
suffix:semicolon
id|prop-&gt;menu
op_assign
id|current_entry
suffix:semicolon
id|prop-&gt;text
op_assign
id|prompt
suffix:semicolon
id|prop-&gt;def
op_assign
id|def
suffix:semicolon
id|prop-&gt;visible.expr
op_assign
id|menu_check_dep
c_func
(paren
id|dep
)paren
suffix:semicolon
r_if
c_cond
(paren
id|prompt
)paren
id|current_entry-&gt;prompt
op_assign
id|prop
suffix:semicolon
multiline_comment|/* append property to the prop list of symbol */
r_if
c_cond
(paren
id|prop-&gt;sym
)paren
(brace
r_for
c_loop
(paren
id|propp
op_assign
op_amp
id|prop-&gt;sym-&gt;prop
suffix:semicolon
op_star
id|propp
suffix:semicolon
id|propp
op_assign
op_amp
(paren
op_star
id|propp
)paren
op_member_access_from_pointer
id|next
)paren
suffix:semicolon
op_star
id|propp
op_assign
id|prop
suffix:semicolon
)brace
r_return
id|prop
suffix:semicolon
)brace
DECL|function|menu_add_prompt
r_void
id|menu_add_prompt
c_func
(paren
r_enum
id|prop_type
id|type
comma
r_char
op_star
id|prompt
comma
r_struct
id|expr
op_star
id|dep
)paren
(brace
id|current_entry-&gt;prompt
op_assign
id|menu_add_prop
c_func
(paren
id|type
comma
id|prompt
comma
l_int|NULL
comma
id|dep
)paren
suffix:semicolon
)brace
DECL|function|menu_add_default
r_void
id|menu_add_default
c_func
(paren
r_enum
id|prop_type
id|type
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
(brace
id|current_entry-&gt;prompt
op_assign
id|menu_add_prop
c_func
(paren
id|type
comma
l_int|NULL
comma
id|def
comma
id|dep
)paren
suffix:semicolon
)brace
DECL|function|menu_finalize
r_void
id|menu_finalize
c_func
(paren
r_struct
id|menu
op_star
id|parent
)paren
(brace
r_struct
id|menu
op_star
id|menu
comma
op_star
id|last_menu
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
id|parentdep
comma
op_star
id|basedep
comma
op_star
id|dep
comma
op_star
id|dep2
suffix:semicolon
id|sym
op_assign
id|parent-&gt;sym
suffix:semicolon
r_if
c_cond
(paren
id|parent-&gt;list
)paren
(brace
r_if
c_cond
(paren
id|sym
op_logical_and
id|sym_is_choice
c_func
(paren
id|sym
)paren
)paren
(brace
multiline_comment|/* find the first choice value and find out choice type */
r_for
c_loop
(paren
id|menu
op_assign
id|parent-&gt;list
suffix:semicolon
id|menu
suffix:semicolon
id|menu
op_assign
id|menu-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|menu-&gt;sym
)paren
(brace
id|current_entry
op_assign
id|parent
suffix:semicolon
id|menu_set_type
c_func
(paren
id|menu-&gt;sym-&gt;type
)paren
suffix:semicolon
id|current_entry
op_assign
id|menu
suffix:semicolon
id|menu_set_type
c_func
(paren
id|sym-&gt;type
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|parentdep
op_assign
id|expr_alloc_symbol
c_func
(paren
id|sym
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|parent-&gt;prompt
)paren
id|parentdep
op_assign
id|parent-&gt;prompt-&gt;visible.expr
suffix:semicolon
r_else
id|parentdep
op_assign
id|parent-&gt;dep
suffix:semicolon
r_for
c_loop
(paren
id|menu
op_assign
id|parent-&gt;list
suffix:semicolon
id|menu
suffix:semicolon
id|menu
op_assign
id|menu-&gt;next
)paren
(brace
id|basedep
op_assign
id|expr_transform
c_func
(paren
id|menu-&gt;dep
)paren
suffix:semicolon
id|basedep
op_assign
id|expr_alloc_and
c_func
(paren
id|expr_copy
c_func
(paren
id|parentdep
)paren
comma
id|basedep
)paren
suffix:semicolon
id|basedep
op_assign
id|expr_eliminate_dups
c_func
(paren
id|basedep
)paren
suffix:semicolon
id|menu-&gt;dep
op_assign
id|basedep
suffix:semicolon
r_if
c_cond
(paren
id|menu-&gt;sym
)paren
id|prop
op_assign
id|menu-&gt;sym-&gt;prop
suffix:semicolon
r_else
id|prop
op_assign
id|menu-&gt;prompt
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|prop
suffix:semicolon
id|prop
op_assign
id|prop-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|prop-&gt;menu
op_ne
id|menu
)paren
r_continue
suffix:semicolon
id|dep
op_assign
id|expr_transform
c_func
(paren
id|prop-&gt;visible.expr
)paren
suffix:semicolon
id|dep
op_assign
id|expr_alloc_and
c_func
(paren
id|expr_copy
c_func
(paren
id|basedep
)paren
comma
id|dep
)paren
suffix:semicolon
id|dep
op_assign
id|expr_eliminate_dups
c_func
(paren
id|dep
)paren
suffix:semicolon
r_if
c_cond
(paren
id|menu-&gt;sym
op_logical_and
id|menu-&gt;sym-&gt;type
op_ne
id|S_TRISTATE
)paren
id|dep
op_assign
id|expr_trans_bool
c_func
(paren
id|dep
)paren
suffix:semicolon
id|prop-&gt;visible.expr
op_assign
id|dep
suffix:semicolon
)brace
)brace
r_for
c_loop
(paren
id|menu
op_assign
id|parent-&gt;list
suffix:semicolon
id|menu
suffix:semicolon
id|menu
op_assign
id|menu-&gt;next
)paren
id|menu_finalize
c_func
(paren
id|menu
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|sym
)paren
(brace
id|basedep
op_assign
id|parent-&gt;prompt
ques
c_cond
id|parent-&gt;prompt-&gt;visible.expr
suffix:colon
l_int|NULL
suffix:semicolon
id|basedep
op_assign
id|expr_trans_compare
c_func
(paren
id|basedep
comma
id|E_UNEQUAL
comma
op_amp
id|symbol_no
)paren
suffix:semicolon
id|basedep
op_assign
id|expr_eliminate_dups
c_func
(paren
id|expr_transform
c_func
(paren
id|basedep
)paren
)paren
suffix:semicolon
id|last_menu
op_assign
l_int|NULL
suffix:semicolon
r_for
c_loop
(paren
id|menu
op_assign
id|parent-&gt;next
suffix:semicolon
id|menu
suffix:semicolon
id|menu
op_assign
id|menu-&gt;next
)paren
(brace
id|dep
op_assign
id|menu-&gt;prompt
ques
c_cond
id|menu-&gt;prompt-&gt;visible.expr
suffix:colon
id|menu-&gt;dep
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|expr_contains_symbol
c_func
(paren
id|dep
comma
id|sym
)paren
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|expr_depends_symbol
c_func
(paren
id|dep
comma
id|sym
)paren
)paren
r_goto
id|next
suffix:semicolon
id|dep
op_assign
id|expr_trans_compare
c_func
(paren
id|dep
comma
id|E_UNEQUAL
comma
op_amp
id|symbol_no
)paren
suffix:semicolon
id|dep
op_assign
id|expr_eliminate_dups
c_func
(paren
id|expr_transform
c_func
(paren
id|dep
)paren
)paren
suffix:semicolon
id|dep2
op_assign
id|expr_copy
c_func
(paren
id|basedep
)paren
suffix:semicolon
id|expr_eliminate_eq
c_func
(paren
op_amp
id|dep
comma
op_amp
id|dep2
)paren
suffix:semicolon
id|expr_free
c_func
(paren
id|dep
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|expr_is_yes
c_func
(paren
id|dep2
)paren
)paren
(brace
id|expr_free
c_func
(paren
id|dep2
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|expr_free
c_func
(paren
id|dep2
)paren
suffix:semicolon
id|next
suffix:colon
id|menu_finalize
c_func
(paren
id|menu
)paren
suffix:semicolon
id|menu-&gt;parent
op_assign
id|parent
suffix:semicolon
id|last_menu
op_assign
id|menu
suffix:semicolon
)brace
r_if
c_cond
(paren
id|last_menu
)paren
(brace
id|parent-&gt;list
op_assign
id|parent-&gt;next
suffix:semicolon
id|parent-&gt;next
op_assign
id|last_menu-&gt;next
suffix:semicolon
id|last_menu-&gt;next
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
r_for
c_loop
(paren
id|menu
op_assign
id|parent-&gt;list
suffix:semicolon
id|menu
suffix:semicolon
id|menu
op_assign
id|menu-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|sym
op_logical_and
id|sym_is_choice
c_func
(paren
id|sym
)paren
op_logical_and
id|menu-&gt;sym
)paren
(brace
id|menu-&gt;sym-&gt;flags
op_or_assign
id|SYMBOL_CHOICEVAL
suffix:semicolon
id|current_entry
op_assign
id|menu
suffix:semicolon
id|menu_set_type
c_func
(paren
id|sym-&gt;type
)paren
suffix:semicolon
id|menu_add_prop
c_func
(paren
id|P_CHOICE
comma
l_int|NULL
comma
id|parent-&gt;sym
comma
l_int|NULL
)paren
suffix:semicolon
id|prop
op_assign
id|sym_get_choice_prop
c_func
(paren
id|parent-&gt;sym
)paren
suffix:semicolon
id|prop-&gt;expr
op_assign
id|expr_alloc_one
c_func
(paren
id|E_CHOICE
comma
id|prop-&gt;expr
)paren
suffix:semicolon
id|prop-&gt;expr-&gt;right.sym
op_assign
id|menu-&gt;sym
suffix:semicolon
)brace
r_if
c_cond
(paren
id|menu-&gt;list
op_logical_and
(paren
op_logical_neg
id|menu-&gt;prompt
op_logical_or
op_logical_neg
id|menu-&gt;prompt-&gt;text
)paren
)paren
(brace
r_for
c_loop
(paren
id|last_menu
op_assign
id|menu-&gt;list
suffix:semicolon
suffix:semicolon
id|last_menu
op_assign
id|last_menu-&gt;next
)paren
(brace
id|last_menu-&gt;parent
op_assign
id|parent
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|last_menu-&gt;next
)paren
r_break
suffix:semicolon
)brace
id|last_menu-&gt;next
op_assign
id|menu-&gt;next
suffix:semicolon
id|menu-&gt;next
op_assign
id|menu-&gt;list
suffix:semicolon
id|menu-&gt;list
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
)brace
DECL|function|menu_is_visible
r_bool
id|menu_is_visible
c_func
(paren
r_struct
id|menu
op_star
id|menu
)paren
(brace
id|tristate
id|visible
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|menu-&gt;prompt
)paren
r_return
l_bool|false
suffix:semicolon
r_if
c_cond
(paren
id|menu-&gt;sym
)paren
(brace
id|sym_calc_value
c_func
(paren
id|menu-&gt;sym
)paren
suffix:semicolon
id|visible
op_assign
id|menu-&gt;prompt-&gt;visible.tri
suffix:semicolon
)brace
r_else
id|visible
op_assign
id|menu-&gt;prompt-&gt;visible.tri
op_assign
id|expr_calc_value
c_func
(paren
id|menu-&gt;prompt-&gt;visible.expr
)paren
suffix:semicolon
r_return
id|visible
op_ne
id|no
suffix:semicolon
)brace
DECL|function|menu_get_prompt
r_const
r_char
op_star
id|menu_get_prompt
c_func
(paren
r_struct
id|menu
op_star
id|menu
)paren
(brace
r_if
c_cond
(paren
id|menu-&gt;prompt
)paren
r_return
id|menu-&gt;prompt-&gt;text
suffix:semicolon
r_else
r_if
c_cond
(paren
id|menu-&gt;sym
)paren
r_return
id|menu-&gt;sym-&gt;name
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|menu_get_root_menu
r_struct
id|menu
op_star
id|menu_get_root_menu
c_func
(paren
r_struct
id|menu
op_star
id|menu
)paren
(brace
r_return
op_amp
id|rootmenu
suffix:semicolon
)brace
DECL|function|menu_get_parent_menu
r_struct
id|menu
op_star
id|menu_get_parent_menu
c_func
(paren
r_struct
id|menu
op_star
id|menu
)paren
(brace
r_enum
id|prop_type
id|type
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|menu
op_ne
op_amp
id|rootmenu
suffix:semicolon
id|menu
op_assign
id|menu-&gt;parent
)paren
(brace
id|type
op_assign
id|menu-&gt;prompt
ques
c_cond
id|menu-&gt;prompt-&gt;type
suffix:colon
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|type
op_eq
id|P_MENU
op_logical_or
id|type
op_eq
id|P_ROOTMENU
)paren
r_break
suffix:semicolon
)brace
r_return
id|menu
suffix:semicolon
)brace
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
eof
