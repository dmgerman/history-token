multiline_comment|/*&n; * Copyright (C) 2001 Sistina Software (UK) Limited.&n; *&n; * This file is released under the GPL.&n; */
macro_line|#include &quot;dm.h&quot;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/bio.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
multiline_comment|/*&n; * Linear: maps a linear range of a device.&n; */
DECL|struct|linear_c
r_struct
id|linear_c
(brace
DECL|member|dev
r_struct
id|dm_dev
op_star
id|dev
suffix:semicolon
DECL|member|start
id|sector_t
id|start
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Construct a linear mapping: &lt;dev_path&gt; &lt;offset&gt;&n; */
DECL|function|linear_ctr
r_static
r_int
id|linear_ctr
c_func
(paren
r_struct
id|dm_target
op_star
id|ti
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
id|linear_c
op_star
id|lc
suffix:semicolon
r_if
c_cond
(paren
id|argc
op_ne
l_int|2
)paren
(brace
id|ti-&gt;error
op_assign
l_string|&quot;dm-linear: Not enough arguments&quot;
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|lc
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|lc
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lc
op_eq
l_int|NULL
)paren
(brace
id|ti-&gt;error
op_assign
l_string|&quot;dm-linear: Cannot allocate linear context&quot;
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sscanf
c_func
(paren
id|argv
(braket
l_int|1
)braket
comma
id|SECTOR_FORMAT
comma
op_amp
id|lc-&gt;start
)paren
op_ne
l_int|1
)paren
(brace
id|ti-&gt;error
op_assign
l_string|&quot;dm-linear: Invalid device sector&quot;
suffix:semicolon
r_goto
id|bad
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dm_get_device
c_func
(paren
id|ti
comma
id|argv
(braket
l_int|0
)braket
comma
id|ti-&gt;begin
comma
id|ti-&gt;len
comma
id|dm_table_get_mode
c_func
(paren
id|ti-&gt;table
)paren
comma
op_amp
id|lc-&gt;dev
)paren
)paren
(brace
id|ti-&gt;error
op_assign
l_string|&quot;dm-linear: Device lookup failed&quot;
suffix:semicolon
r_goto
id|bad
suffix:semicolon
)brace
id|ti
op_member_access_from_pointer
r_private
op_assign
id|lc
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|bad
suffix:colon
id|kfree
c_func
(paren
id|lc
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|function|linear_dtr
r_static
r_void
id|linear_dtr
c_func
(paren
r_struct
id|dm_target
op_star
id|ti
)paren
(brace
r_struct
id|linear_c
op_star
id|lc
op_assign
(paren
r_struct
id|linear_c
op_star
)paren
id|ti
op_member_access_from_pointer
r_private
suffix:semicolon
id|dm_put_device
c_func
(paren
id|ti
comma
id|lc-&gt;dev
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|lc
)paren
suffix:semicolon
)brace
DECL|function|linear_map
r_static
r_int
id|linear_map
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
)paren
(brace
r_struct
id|linear_c
op_star
id|lc
op_assign
(paren
r_struct
id|linear_c
op_star
)paren
id|ti
op_member_access_from_pointer
r_private
suffix:semicolon
id|bio-&gt;bi_bdev
op_assign
id|lc-&gt;dev-&gt;bdev
suffix:semicolon
id|bio-&gt;bi_sector
op_assign
id|lc-&gt;start
op_plus
(paren
id|bio-&gt;bi_sector
op_minus
id|ti-&gt;begin
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|linear_status
r_static
r_int
id|linear_status
c_func
(paren
r_struct
id|dm_target
op_star
id|ti
comma
id|status_type_t
id|type
comma
r_char
op_star
id|result
comma
r_int
id|maxlen
)paren
(brace
r_struct
id|linear_c
op_star
id|lc
op_assign
(paren
r_struct
id|linear_c
op_star
)paren
id|ti
op_member_access_from_pointer
r_private
suffix:semicolon
r_switch
c_cond
(paren
id|type
)paren
(brace
r_case
id|STATUSTYPE_INFO
suffix:colon
id|result
(braket
l_int|0
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|STATUSTYPE_TABLE
suffix:colon
id|snprintf
c_func
(paren
id|result
comma
id|maxlen
comma
l_string|&quot;%s &quot;
id|SECTOR_FORMAT
comma
id|bdevname
c_func
(paren
id|lc-&gt;dev-&gt;bdev
)paren
comma
id|lc-&gt;start
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|linear_target
r_static
r_struct
id|target_type
id|linear_target
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;linear&quot;
comma
dot
id|module
op_assign
id|THIS_MODULE
comma
dot
id|ctr
op_assign
id|linear_ctr
comma
dot
id|dtr
op_assign
id|linear_dtr
comma
dot
id|map
op_assign
id|linear_map
comma
dot
id|status
op_assign
id|linear_status
comma
)brace
suffix:semicolon
DECL|function|dm_linear_init
r_int
id|__init
id|dm_linear_init
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
id|linear_target
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
l_string|&quot;linear: register failed %d&quot;
comma
id|r
)paren
suffix:semicolon
r_return
id|r
suffix:semicolon
)brace
DECL|function|dm_linear_exit
r_void
id|dm_linear_exit
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
id|linear_target
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
l_string|&quot;linear: unregister failed %d&quot;
comma
id|r
)paren
suffix:semicolon
)brace
eof
