multiline_comment|/*&n; * Copyright (C) 2003 Sistina Software.&n; * Copyright (C) 2004-2005 Red Hat, Inc. All rights reserved.&n; *&n; * Module Author: Heinz Mauelshagen&n; *&n; * This file is released under the GPL.&n; *&n; * Round-robin path selector.&n; */
macro_line|#include &quot;dm.h&quot;
macro_line|#include &quot;dm-path-selector.h&quot;
macro_line|#include &lt;linux/slab.h&gt;
multiline_comment|/*-----------------------------------------------------------------&n; * Path-handling code, paths are held in lists&n; *---------------------------------------------------------------*/
DECL|struct|path_info
r_struct
id|path_info
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|path
r_struct
id|path
op_star
id|path
suffix:semicolon
DECL|member|repeat_count
r_int
id|repeat_count
suffix:semicolon
)brace
suffix:semicolon
DECL|function|free_paths
r_static
r_void
id|free_paths
c_func
(paren
r_struct
id|list_head
op_star
id|paths
)paren
(brace
r_struct
id|path_info
op_star
id|pi
comma
op_star
id|next
suffix:semicolon
id|list_for_each_entry_safe
c_func
(paren
id|pi
comma
id|next
comma
id|paths
comma
id|list
)paren
(brace
id|list_del
c_func
(paren
op_amp
id|pi-&gt;list
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|pi
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*-----------------------------------------------------------------&n; * Round-robin selector&n; *---------------------------------------------------------------*/
DECL|macro|RR_MIN_IO
mdefine_line|#define RR_MIN_IO&t;&t;1000
DECL|struct|selector
r_struct
id|selector
(brace
DECL|member|valid_paths
r_struct
id|list_head
id|valid_paths
suffix:semicolon
DECL|member|invalid_paths
r_struct
id|list_head
id|invalid_paths
suffix:semicolon
)brace
suffix:semicolon
DECL|function|alloc_selector
r_static
r_struct
id|selector
op_star
id|alloc_selector
c_func
(paren
r_void
)paren
(brace
r_struct
id|selector
op_star
id|s
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|s
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|s
)paren
(brace
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|s-&gt;valid_paths
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|s-&gt;invalid_paths
)paren
suffix:semicolon
)brace
r_return
id|s
suffix:semicolon
)brace
DECL|function|rr_ctr
r_static
r_int
id|rr_ctr
c_func
(paren
r_struct
id|path_selector
op_star
id|ps
comma
r_int
id|argc
comma
r_char
op_star
op_star
id|argv
)paren
(brace
r_struct
id|selector
op_star
id|s
suffix:semicolon
id|s
op_assign
id|alloc_selector
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|s
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|ps-&gt;context
op_assign
id|s
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|rr_dtr
r_static
r_void
id|rr_dtr
c_func
(paren
r_struct
id|path_selector
op_star
id|ps
)paren
(brace
r_struct
id|selector
op_star
id|s
op_assign
(paren
r_struct
id|selector
op_star
)paren
id|ps-&gt;context
suffix:semicolon
id|free_paths
c_func
(paren
op_amp
id|s-&gt;valid_paths
)paren
suffix:semicolon
id|free_paths
c_func
(paren
op_amp
id|s-&gt;invalid_paths
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|s
)paren
suffix:semicolon
id|ps-&gt;context
op_assign
l_int|NULL
suffix:semicolon
)brace
DECL|function|rr_status
r_static
r_int
id|rr_status
c_func
(paren
r_struct
id|path_selector
op_star
id|ps
comma
r_struct
id|path
op_star
id|path
comma
id|status_type_t
id|type
comma
r_char
op_star
id|result
comma
r_int
r_int
id|maxlen
)paren
(brace
r_struct
id|path_info
op_star
id|pi
suffix:semicolon
r_int
id|sz
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|path
)paren
id|DMEMIT
c_func
(paren
l_string|&quot;0 &quot;
)paren
suffix:semicolon
r_else
(brace
r_switch
c_cond
(paren
id|type
)paren
(brace
r_case
id|STATUSTYPE_INFO
suffix:colon
r_break
suffix:semicolon
r_case
id|STATUSTYPE_TABLE
suffix:colon
id|pi
op_assign
id|path-&gt;pscontext
suffix:semicolon
id|DMEMIT
c_func
(paren
l_string|&quot;%u &quot;
comma
id|pi-&gt;repeat_count
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_return
id|sz
suffix:semicolon
)brace
multiline_comment|/*&n; * Called during initialisation to register each path with an&n; * optional repeat_count.&n; */
DECL|function|rr_add_path
r_static
r_int
id|rr_add_path
c_func
(paren
r_struct
id|path_selector
op_star
id|ps
comma
r_struct
id|path
op_star
id|path
comma
r_int
id|argc
comma
r_char
op_star
op_star
id|argv
comma
r_char
op_star
op_star
id|error
)paren
(brace
r_struct
id|selector
op_star
id|s
op_assign
(paren
r_struct
id|selector
op_star
)paren
id|ps-&gt;context
suffix:semicolon
r_struct
id|path_info
op_star
id|pi
suffix:semicolon
r_int
id|repeat_count
op_assign
id|RR_MIN_IO
suffix:semicolon
r_if
c_cond
(paren
id|argc
OG
l_int|1
)paren
(brace
op_star
id|error
op_assign
l_string|&quot;round-robin ps: incorrect number of arguments&quot;
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/* First path argument is number of I/Os before switching path */
r_if
c_cond
(paren
(paren
id|argc
op_eq
l_int|1
)paren
op_logical_and
(paren
id|sscanf
c_func
(paren
id|argv
(braket
l_int|0
)braket
comma
l_string|&quot;%u&quot;
comma
op_amp
id|repeat_count
)paren
op_ne
l_int|1
)paren
)paren
(brace
op_star
id|error
op_assign
l_string|&quot;round-robin ps: invalid repeat count&quot;
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/* allocate the path */
id|pi
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|pi
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pi
)paren
(brace
op_star
id|error
op_assign
l_string|&quot;round-robin ps: Error allocating path context&quot;
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|pi-&gt;path
op_assign
id|path
suffix:semicolon
id|pi-&gt;repeat_count
op_assign
id|repeat_count
suffix:semicolon
id|path-&gt;pscontext
op_assign
id|pi
suffix:semicolon
id|list_add
c_func
(paren
op_amp
id|pi-&gt;list
comma
op_amp
id|s-&gt;valid_paths
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|rr_fail_path
r_static
r_void
id|rr_fail_path
c_func
(paren
r_struct
id|path_selector
op_star
id|ps
comma
r_struct
id|path
op_star
id|p
)paren
(brace
r_struct
id|selector
op_star
id|s
op_assign
(paren
r_struct
id|selector
op_star
)paren
id|ps-&gt;context
suffix:semicolon
r_struct
id|path_info
op_star
id|pi
op_assign
id|p-&gt;pscontext
suffix:semicolon
id|list_move
c_func
(paren
op_amp
id|pi-&gt;list
comma
op_amp
id|s-&gt;invalid_paths
)paren
suffix:semicolon
)brace
DECL|function|rr_reinstate_path
r_static
r_int
id|rr_reinstate_path
c_func
(paren
r_struct
id|path_selector
op_star
id|ps
comma
r_struct
id|path
op_star
id|p
)paren
(brace
r_struct
id|selector
op_star
id|s
op_assign
(paren
r_struct
id|selector
op_star
)paren
id|ps-&gt;context
suffix:semicolon
r_struct
id|path_info
op_star
id|pi
op_assign
id|p-&gt;pscontext
suffix:semicolon
id|list_move
c_func
(paren
op_amp
id|pi-&gt;list
comma
op_amp
id|s-&gt;valid_paths
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|rr_select_path
r_static
r_struct
id|path
op_star
id|rr_select_path
c_func
(paren
r_struct
id|path_selector
op_star
id|ps
comma
r_int
op_star
id|repeat_count
)paren
(brace
r_struct
id|selector
op_star
id|s
op_assign
(paren
r_struct
id|selector
op_star
)paren
id|ps-&gt;context
suffix:semicolon
r_struct
id|path_info
op_star
id|pi
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|s-&gt;valid_paths
)paren
)paren
(brace
id|pi
op_assign
id|list_entry
c_func
(paren
id|s-&gt;valid_paths.next
comma
r_struct
id|path_info
comma
id|list
)paren
suffix:semicolon
id|list_move_tail
c_func
(paren
op_amp
id|pi-&gt;list
comma
op_amp
id|s-&gt;valid_paths
)paren
suffix:semicolon
op_star
id|repeat_count
op_assign
id|pi-&gt;repeat_count
suffix:semicolon
)brace
r_return
id|pi
ques
c_cond
id|pi-&gt;path
suffix:colon
l_int|NULL
suffix:semicolon
)brace
DECL|variable|rr_ps
r_static
r_struct
id|path_selector_type
id|rr_ps
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;round-robin&quot;
comma
dot
id|module
op_assign
id|THIS_MODULE
comma
dot
id|table_args
op_assign
l_int|1
comma
dot
id|info_args
op_assign
l_int|0
comma
dot
id|ctr
op_assign
id|rr_ctr
comma
dot
id|dtr
op_assign
id|rr_dtr
comma
dot
id|status
op_assign
id|rr_status
comma
dot
id|add_path
op_assign
id|rr_add_path
comma
dot
id|fail_path
op_assign
id|rr_fail_path
comma
dot
id|reinstate_path
op_assign
id|rr_reinstate_path
comma
dot
id|select_path
op_assign
id|rr_select_path
comma
)brace
suffix:semicolon
DECL|function|dm_rr_init
r_static
r_int
id|__init
id|dm_rr_init
c_func
(paren
r_void
)paren
(brace
r_int
id|r
op_assign
id|dm_register_path_selector
c_func
(paren
op_amp
id|rr_ps
)paren
suffix:semicolon
r_if
c_cond
(paren
id|r
OL
l_int|0
)paren
id|DMERR
c_func
(paren
l_string|&quot;round-robin: register failed %d&quot;
comma
id|r
)paren
suffix:semicolon
id|DMINFO
c_func
(paren
l_string|&quot;dm-round-robin version 1.0.0 loaded&quot;
)paren
suffix:semicolon
r_return
id|r
suffix:semicolon
)brace
DECL|function|dm_rr_exit
r_static
r_void
id|__exit
id|dm_rr_exit
c_func
(paren
r_void
)paren
(brace
r_int
id|r
op_assign
id|dm_unregister_path_selector
c_func
(paren
op_amp
id|rr_ps
)paren
suffix:semicolon
r_if
c_cond
(paren
id|r
OL
l_int|0
)paren
id|DMERR
c_func
(paren
l_string|&quot;round-robin: unregister failed %d&quot;
comma
id|r
)paren
suffix:semicolon
)brace
DECL|variable|dm_rr_init
id|module_init
c_func
(paren
id|dm_rr_init
)paren
suffix:semicolon
DECL|variable|dm_rr_exit
id|module_exit
c_func
(paren
id|dm_rr_exit
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
id|DM_NAME
l_string|&quot; round-robin multipath path selector&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Sistina Software &lt;dm-devel@redhat.com&gt;&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
