multiline_comment|/*&n; * Copyright (C) 2001 Sistina Software (UK) Limited&n; *&n; * This file is released under the GPL.&n; */
macro_line|#include &quot;dm.h&quot;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kmod.h&gt;
macro_line|#include &lt;linux/bio.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
DECL|struct|tt_internal
r_struct
id|tt_internal
(brace
DECL|member|tt
r_struct
id|target_type
id|tt
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
r_static
id|LIST_HEAD
c_func
(paren
id|_targets
)paren
suffix:semicolon
r_static
id|DECLARE_RWSEM
c_func
(paren
id|_lock
)paren
suffix:semicolon
DECL|macro|DM_MOD_NAME_SIZE
mdefine_line|#define DM_MOD_NAME_SIZE 32
DECL|function|__find_target_type
r_static
r_inline
r_struct
id|tt_internal
op_star
id|__find_target_type
c_func
(paren
r_const
r_char
op_star
id|name
)paren
(brace
r_struct
id|tt_internal
op_star
id|ti
suffix:semicolon
id|list_for_each_entry
(paren
id|ti
comma
op_amp
id|_targets
comma
id|list
)paren
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|name
comma
id|ti-&gt;tt.name
)paren
)paren
r_return
id|ti
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|get_target_type
r_static
r_struct
id|tt_internal
op_star
id|get_target_type
c_func
(paren
r_const
r_char
op_star
id|name
)paren
(brace
r_struct
id|tt_internal
op_star
id|ti
suffix:semicolon
id|down_read
c_func
(paren
op_amp
id|_lock
)paren
suffix:semicolon
id|ti
op_assign
id|__find_target_type
c_func
(paren
id|name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ti
)paren
(brace
r_if
c_cond
(paren
(paren
id|ti-&gt;use
op_eq
l_int|0
)paren
op_logical_and
op_logical_neg
id|try_module_get
c_func
(paren
id|ti-&gt;tt.module
)paren
)paren
id|ti
op_assign
l_int|NULL
suffix:semicolon
r_else
id|ti-&gt;use
op_increment
suffix:semicolon
)brace
id|up_read
c_func
(paren
op_amp
id|_lock
)paren
suffix:semicolon
r_return
id|ti
suffix:semicolon
)brace
DECL|function|load_module
r_static
r_void
id|load_module
c_func
(paren
r_const
r_char
op_star
id|name
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
)brace
DECL|function|dm_get_target_type
r_struct
id|target_type
op_star
id|dm_get_target_type
c_func
(paren
r_const
r_char
op_star
id|name
)paren
(brace
r_struct
id|tt_internal
op_star
id|ti
op_assign
id|get_target_type
c_func
(paren
id|name
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ti
)paren
(brace
id|load_module
c_func
(paren
id|name
)paren
suffix:semicolon
id|ti
op_assign
id|get_target_type
c_func
(paren
id|name
)paren
suffix:semicolon
)brace
r_return
id|ti
ques
c_cond
op_amp
id|ti-&gt;tt
suffix:colon
l_int|NULL
suffix:semicolon
)brace
DECL|function|dm_put_target_type
r_void
id|dm_put_target_type
c_func
(paren
r_struct
id|target_type
op_star
id|t
)paren
(brace
r_struct
id|tt_internal
op_star
id|ti
op_assign
(paren
r_struct
id|tt_internal
op_star
)paren
id|t
suffix:semicolon
id|down_read
c_func
(paren
op_amp
id|_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_decrement
id|ti-&gt;use
op_eq
l_int|0
)paren
id|module_put
c_func
(paren
id|ti-&gt;tt.module
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ti-&gt;use
OL
l_int|0
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|up_read
c_func
(paren
op_amp
id|_lock
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|alloc_target
r_static
r_struct
id|tt_internal
op_star
id|alloc_target
c_func
(paren
r_struct
id|target_type
op_star
id|t
)paren
(brace
r_struct
id|tt_internal
op_star
id|ti
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|ti
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ti
)paren
(brace
id|memset
c_func
(paren
id|ti
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|ti
)paren
)paren
suffix:semicolon
id|ti-&gt;tt
op_assign
op_star
id|t
suffix:semicolon
)brace
r_return
id|ti
suffix:semicolon
)brace
DECL|function|dm_target_iterate
r_int
id|dm_target_iterate
c_func
(paren
r_void
(paren
op_star
id|iter_func
)paren
(paren
r_struct
id|target_type
op_star
id|tt
comma
r_void
op_star
id|param
)paren
comma
r_void
op_star
id|param
)paren
(brace
r_struct
id|tt_internal
op_star
id|ti
suffix:semicolon
id|down_read
c_func
(paren
op_amp
id|_lock
)paren
suffix:semicolon
id|list_for_each_entry
(paren
id|ti
comma
op_amp
id|_targets
comma
id|list
)paren
id|iter_func
c_func
(paren
op_amp
id|ti-&gt;tt
comma
id|param
)paren
suffix:semicolon
id|up_read
c_func
(paren
op_amp
id|_lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dm_register_target
r_int
id|dm_register_target
c_func
(paren
r_struct
id|target_type
op_star
id|t
)paren
(brace
r_int
id|rv
op_assign
l_int|0
suffix:semicolon
r_struct
id|tt_internal
op_star
id|ti
op_assign
id|alloc_target
c_func
(paren
id|t
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ti
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|down_write
c_func
(paren
op_amp
id|_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|__find_target_type
c_func
(paren
id|t-&gt;name
)paren
)paren
id|rv
op_assign
op_minus
id|EEXIST
suffix:semicolon
r_else
id|list_add
c_func
(paren
op_amp
id|ti-&gt;list
comma
op_amp
id|_targets
)paren
suffix:semicolon
id|up_write
c_func
(paren
op_amp
id|_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rv
)paren
id|kfree
c_func
(paren
id|ti
)paren
suffix:semicolon
r_return
id|rv
suffix:semicolon
)brace
DECL|function|dm_unregister_target
r_int
id|dm_unregister_target
c_func
(paren
r_struct
id|target_type
op_star
id|t
)paren
(brace
r_struct
id|tt_internal
op_star
id|ti
suffix:semicolon
id|down_write
c_func
(paren
op_amp
id|_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|ti
op_assign
id|__find_target_type
c_func
(paren
id|t-&gt;name
)paren
)paren
)paren
(brace
id|up_write
c_func
(paren
op_amp
id|_lock
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
id|ti-&gt;use
)paren
(brace
id|up_write
c_func
(paren
op_amp
id|_lock
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
id|ti-&gt;list
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|ti
)paren
suffix:semicolon
id|up_write
c_func
(paren
op_amp
id|_lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * io-err: always fails an io, useful for bringing&n; * up LVs that have holes in them.&n; */
DECL|function|io_err_ctr
r_static
r_int
id|io_err_ctr
c_func
(paren
r_struct
id|dm_target
op_star
id|ti
comma
r_int
r_int
id|argc
comma
r_char
op_star
op_star
id|args
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|io_err_dtr
r_static
r_void
id|io_err_dtr
c_func
(paren
r_struct
id|dm_target
op_star
id|ti
)paren
(brace
multiline_comment|/* empty */
)brace
DECL|function|io_err_map
r_static
r_int
id|io_err_map
c_func
(paren
r_struct
id|dm_target
op_star
id|ti
comma
r_struct
id|bio
op_star
id|bio
comma
r_union
id|map_info
op_star
id|map_context
)paren
(brace
r_return
op_minus
id|EIO
suffix:semicolon
)brace
DECL|variable|error_target
r_static
r_struct
id|target_type
id|error_target
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;error&quot;
comma
dot
id|version
op_assign
(brace
l_int|1
comma
l_int|0
comma
l_int|1
)brace
comma
dot
id|ctr
op_assign
id|io_err_ctr
comma
dot
id|dtr
op_assign
id|io_err_dtr
comma
dot
id|map
op_assign
id|io_err_map
comma
)brace
suffix:semicolon
DECL|function|dm_target_init
r_int
id|__init
id|dm_target_init
c_func
(paren
r_void
)paren
(brace
r_return
id|dm_register_target
c_func
(paren
op_amp
id|error_target
)paren
suffix:semicolon
)brace
DECL|function|dm_target_exit
r_void
id|dm_target_exit
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|dm_unregister_target
c_func
(paren
op_amp
id|error_target
)paren
)paren
id|DMWARN
c_func
(paren
l_string|&quot;error target unregistration failed&quot;
)paren
suffix:semicolon
)brace
DECL|variable|dm_register_target
id|EXPORT_SYMBOL
c_func
(paren
id|dm_register_target
)paren
suffix:semicolon
DECL|variable|dm_unregister_target
id|EXPORT_SYMBOL
c_func
(paren
id|dm_unregister_target
)paren
suffix:semicolon
eof
