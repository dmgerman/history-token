multiline_comment|/*&n; * Copyright (C) 2003 Christophe Saout &lt;christophe@saout.de&gt;&n; *&n; * This file is released under the GPL.&n; */
macro_line|#include &quot;dm.h&quot;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/bio.h&gt;
multiline_comment|/*&n; * Construct a dummy mapping that only returns zeros&n; */
DECL|function|zero_ctr
r_static
r_int
id|zero_ctr
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
id|argv
)paren
(brace
r_if
c_cond
(paren
id|argc
op_ne
l_int|0
)paren
(brace
id|ti-&gt;error
op_assign
l_string|&quot;dm-zero: No arguments required&quot;
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Return zeros only on reads&n; */
DECL|function|zero_map
r_static
r_int
id|zero_map
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
r_switch
c_cond
(paren
id|bio_rw
c_func
(paren
id|bio
)paren
)paren
(brace
r_case
id|READ
suffix:colon
id|zero_fill_bio
c_func
(paren
id|bio
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|READA
suffix:colon
multiline_comment|/* readahead of null bytes only wastes buffer cache */
r_return
op_minus
id|EIO
suffix:semicolon
r_case
id|WRITE
suffix:colon
multiline_comment|/* writes get silently dropped */
r_break
suffix:semicolon
)brace
id|bio_endio
c_func
(paren
id|bio
comma
id|bio-&gt;bi_size
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* accepted bio, don&squot;t make new request */
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|zero_target
r_static
r_struct
id|target_type
id|zero_target
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;zero&quot;
comma
dot
id|version
op_assign
(brace
l_int|1
comma
l_int|0
comma
l_int|0
)brace
comma
dot
id|module
op_assign
id|THIS_MODULE
comma
dot
id|ctr
op_assign
id|zero_ctr
comma
dot
id|map
op_assign
id|zero_map
comma
)brace
suffix:semicolon
DECL|function|dm_zero_init
r_int
id|__init
id|dm_zero_init
c_func
(paren
r_void
)paren
(brace
r_int
id|r
op_assign
id|dm_register_target
c_func
(paren
op_amp
id|zero_target
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
l_string|&quot;zero: register failed %d&quot;
comma
id|r
)paren
suffix:semicolon
r_return
id|r
suffix:semicolon
)brace
DECL|function|dm_zero_exit
r_void
id|__exit
id|dm_zero_exit
c_func
(paren
r_void
)paren
(brace
r_int
id|r
op_assign
id|dm_unregister_target
c_func
(paren
op_amp
id|zero_target
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
l_string|&quot;zero: unregister failed %d&quot;
comma
id|r
)paren
suffix:semicolon
)brace
id|module_init
c_func
(paren
id|dm_zero_init
)paren
id|module_exit
c_func
(paren
id|dm_zero_exit
)paren
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Christophe Saout &lt;christophe@saout.de&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
id|DM_NAME
l_string|&quot; dummy target returning zeros&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
