multiline_comment|/*&n; * Copyright (C) 2003 Sistina Software.&n; * Copyright (C) 2004 Red Hat, Inc. All rights reserved.&n; *&n; * Module Author: Heinz Mauelshagen&n; *&n; * This file is released under the GPL.&n; *&n; * Path selector registration.&n; */
macro_line|#include &quot;dm.h&quot;
macro_line|#include &quot;dm-path-selector.h&quot;
macro_line|#include &lt;linux/slab.h&gt;
DECL|struct|ps_internal
r_struct
id|ps_internal
(brace
DECL|member|pst
r_struct
id|path_selector_type
id|pst
suffix:semicolon
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|use
r_int
id|use
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|pst_to_psi
mdefine_line|#define pst_to_psi(__pst) container_of((__pst), struct ps_internal, pst)
r_static
id|LIST_HEAD
c_func
(paren
id|_path_selectors
)paren
suffix:semicolon
r_static
id|DECLARE_RWSEM
c_func
(paren
id|_ps_lock
)paren
suffix:semicolon
DECL|function|__find_path_selector_type
r_struct
id|ps_internal
op_star
id|__find_path_selector_type
c_func
(paren
r_const
r_char
op_star
id|name
)paren
(brace
r_struct
id|ps_internal
op_star
id|psi
suffix:semicolon
id|list_for_each_entry
(paren
id|psi
comma
op_amp
id|_path_selectors
comma
id|list
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
id|psi-&gt;pst.name
)paren
)paren
r_return
id|psi
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|get_path_selector
r_static
r_struct
id|ps_internal
op_star
id|get_path_selector
c_func
(paren
r_const
r_char
op_star
id|name
)paren
(brace
r_struct
id|ps_internal
op_star
id|psi
suffix:semicolon
id|down_read
c_func
(paren
op_amp
id|_ps_lock
)paren
suffix:semicolon
id|psi
op_assign
id|__find_path_selector_type
c_func
(paren
id|name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|psi
)paren
(brace
r_if
c_cond
(paren
(paren
id|psi-&gt;use
op_eq
l_int|0
)paren
op_logical_and
op_logical_neg
id|try_module_get
c_func
(paren
id|psi-&gt;pst.module
)paren
)paren
id|psi
op_assign
l_int|NULL
suffix:semicolon
r_else
id|psi-&gt;use
op_increment
suffix:semicolon
)brace
id|up_read
c_func
(paren
op_amp
id|_ps_lock
)paren
suffix:semicolon
r_return
id|psi
suffix:semicolon
)brace
DECL|function|dm_get_path_selector
r_struct
id|path_selector_type
op_star
id|dm_get_path_selector
c_func
(paren
r_const
r_char
op_star
id|name
)paren
(brace
r_struct
id|ps_internal
op_star
id|psi
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|name
)paren
r_return
l_int|NULL
suffix:semicolon
id|psi
op_assign
id|get_path_selector
c_func
(paren
id|name
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|psi
)paren
(brace
id|request_module
c_func
(paren
l_string|&quot;dm-%s&quot;
comma
id|name
)paren
suffix:semicolon
id|psi
op_assign
id|get_path_selector
c_func
(paren
id|name
)paren
suffix:semicolon
)brace
r_return
id|psi
ques
c_cond
op_amp
id|psi-&gt;pst
suffix:colon
l_int|NULL
suffix:semicolon
)brace
DECL|function|dm_put_path_selector
r_void
id|dm_put_path_selector
c_func
(paren
r_struct
id|path_selector_type
op_star
id|pst
)paren
(brace
r_struct
id|ps_internal
op_star
id|psi
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pst
)paren
r_return
suffix:semicolon
id|down_read
c_func
(paren
op_amp
id|_ps_lock
)paren
suffix:semicolon
id|psi
op_assign
id|__find_path_selector_type
c_func
(paren
id|pst-&gt;name
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|psi
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
op_decrement
id|psi-&gt;use
op_eq
l_int|0
)paren
id|module_put
c_func
(paren
id|psi-&gt;pst.module
)paren
suffix:semicolon
r_if
c_cond
(paren
id|psi-&gt;use
OL
l_int|0
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|out
suffix:colon
id|up_read
c_func
(paren
op_amp
id|_ps_lock
)paren
suffix:semicolon
)brace
DECL|function|_alloc_path_selector
r_static
r_struct
id|ps_internal
op_star
id|_alloc_path_selector
c_func
(paren
r_struct
id|path_selector_type
op_star
id|pst
)paren
(brace
r_struct
id|ps_internal
op_star
id|psi
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|psi
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|psi
)paren
(brace
id|memset
c_func
(paren
id|psi
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|psi
)paren
)paren
suffix:semicolon
id|psi-&gt;pst
op_assign
op_star
id|pst
suffix:semicolon
)brace
r_return
id|psi
suffix:semicolon
)brace
DECL|function|dm_register_path_selector
r_int
id|dm_register_path_selector
c_func
(paren
r_struct
id|path_selector_type
op_star
id|pst
)paren
(brace
r_int
id|r
op_assign
l_int|0
suffix:semicolon
r_struct
id|ps_internal
op_star
id|psi
op_assign
id|_alloc_path_selector
c_func
(paren
id|pst
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|psi
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|down_write
c_func
(paren
op_amp
id|_ps_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|__find_path_selector_type
c_func
(paren
id|pst-&gt;name
)paren
)paren
(brace
id|kfree
c_func
(paren
id|psi
)paren
suffix:semicolon
id|r
op_assign
op_minus
id|EEXIST
suffix:semicolon
)brace
r_else
id|list_add
c_func
(paren
op_amp
id|psi-&gt;list
comma
op_amp
id|_path_selectors
)paren
suffix:semicolon
id|up_write
c_func
(paren
op_amp
id|_ps_lock
)paren
suffix:semicolon
r_return
id|r
suffix:semicolon
)brace
DECL|function|dm_unregister_path_selector
r_int
id|dm_unregister_path_selector
c_func
(paren
r_struct
id|path_selector_type
op_star
id|pst
)paren
(brace
r_struct
id|ps_internal
op_star
id|psi
suffix:semicolon
id|down_write
c_func
(paren
op_amp
id|_ps_lock
)paren
suffix:semicolon
id|psi
op_assign
id|__find_path_selector_type
c_func
(paren
id|pst-&gt;name
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|psi
)paren
(brace
id|up_write
c_func
(paren
op_amp
id|_ps_lock
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|psi-&gt;use
)paren
(brace
id|up_write
c_func
(paren
op_amp
id|_ps_lock
)paren
suffix:semicolon
r_return
op_minus
id|ETXTBSY
suffix:semicolon
)brace
id|list_del
c_func
(paren
op_amp
id|psi-&gt;list
)paren
suffix:semicolon
id|up_write
c_func
(paren
op_amp
id|_ps_lock
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|psi
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|dm_register_path_selector
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|dm_register_path_selector
)paren
suffix:semicolon
DECL|variable|dm_unregister_path_selector
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|dm_unregister_path_selector
)paren
suffix:semicolon
eof
