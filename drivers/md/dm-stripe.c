multiline_comment|/*&n; * Copyright (C) 2001-2003 Sistina Software (UK) Limited.&n; *&n; * This file is released under the GPL.&n; */
macro_line|#include &quot;dm.h&quot;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/bio.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
DECL|struct|stripe
r_struct
id|stripe
(brace
DECL|member|dev
r_struct
id|dm_dev
op_star
id|dev
suffix:semicolon
DECL|member|physical_start
id|sector_t
id|physical_start
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|stripe_c
r_struct
id|stripe_c
(brace
DECL|member|stripes
r_uint32
id|stripes
suffix:semicolon
multiline_comment|/* The size of this target / num. stripes */
DECL|member|stripe_width
id|sector_t
id|stripe_width
suffix:semicolon
multiline_comment|/* stripe chunk size */
DECL|member|chunk_shift
r_uint32
id|chunk_shift
suffix:semicolon
DECL|member|chunk_mask
id|sector_t
id|chunk_mask
suffix:semicolon
DECL|member|stripe
r_struct
id|stripe
id|stripe
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|function|alloc_context
r_static
r_inline
r_struct
id|stripe_c
op_star
id|alloc_context
c_func
(paren
r_int
r_int
id|stripes
)paren
(brace
r_int
id|len
suffix:semicolon
r_if
c_cond
(paren
id|array_too_big
c_func
(paren
r_sizeof
(paren
r_struct
id|stripe_c
)paren
comma
r_sizeof
(paren
r_struct
id|stripe
)paren
comma
id|stripes
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
id|len
op_assign
r_sizeof
(paren
r_struct
id|stripe_c
)paren
op_plus
(paren
r_sizeof
(paren
r_struct
id|stripe
)paren
op_star
id|stripes
)paren
suffix:semicolon
r_return
id|kmalloc
c_func
(paren
id|len
comma
id|GFP_KERNEL
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Parse a single &lt;dev&gt; &lt;sector&gt; pair&n; */
DECL|function|get_stripe
r_static
r_int
id|get_stripe
c_func
(paren
r_struct
id|dm_target
op_star
id|ti
comma
r_struct
id|stripe_c
op_star
id|sc
comma
r_int
r_int
id|stripe
comma
r_char
op_star
op_star
id|argv
)paren
(brace
id|sector_t
id|start
suffix:semicolon
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
id|start
)paren
op_ne
l_int|1
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
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
id|start
comma
id|sc-&gt;stripe_width
comma
id|dm_table_get_mode
c_func
(paren
id|ti-&gt;table
)paren
comma
op_amp
id|sc-&gt;stripe
(braket
id|stripe
)braket
dot
id|dev
)paren
)paren
r_return
op_minus
id|ENXIO
suffix:semicolon
id|sc-&gt;stripe
(braket
id|stripe
)braket
dot
id|physical_start
op_assign
id|start
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Construct a striped mapping.&n; * &lt;number of stripes&gt; &lt;chunk size (2^^n)&gt; [&lt;dev_path&gt; &lt;offset&gt;]+&n; */
DECL|function|stripe_ctr
r_static
r_int
id|stripe_ctr
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
r_struct
id|stripe_c
op_star
id|sc
suffix:semicolon
id|sector_t
id|width
suffix:semicolon
r_uint32
id|stripes
suffix:semicolon
r_uint32
id|chunk_size
suffix:semicolon
r_char
op_star
id|end
suffix:semicolon
r_int
id|r
suffix:semicolon
r_int
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|argc
OL
l_int|2
)paren
(brace
id|ti-&gt;error
op_assign
l_string|&quot;dm-stripe: Not enough arguments&quot;
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|stripes
op_assign
id|simple_strtoul
c_func
(paren
id|argv
(braket
l_int|0
)braket
comma
op_amp
id|end
comma
l_int|10
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|end
)paren
(brace
id|ti-&gt;error
op_assign
l_string|&quot;dm-stripe: Invalid stripe count&quot;
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|chunk_size
op_assign
id|simple_strtoul
c_func
(paren
id|argv
(braket
l_int|1
)braket
comma
op_amp
id|end
comma
l_int|10
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|end
)paren
(brace
id|ti-&gt;error
op_assign
l_string|&quot;dm-stripe: Invalid chunk_size&quot;
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * chunk_size is a power of two&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|chunk_size
op_logical_or
(paren
id|chunk_size
op_amp
(paren
id|chunk_size
op_minus
l_int|1
)paren
)paren
op_logical_or
(paren
id|chunk_size
OL
(paren
id|PAGE_SIZE
op_rshift
id|SECTOR_SHIFT
)paren
)paren
)paren
(brace
id|ti-&gt;error
op_assign
l_string|&quot;dm-stripe: Invalid chunk size&quot;
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|width
op_assign
id|ti-&gt;len
suffix:semicolon
r_if
c_cond
(paren
id|sector_div
c_func
(paren
id|width
comma
id|stripes
)paren
)paren
(brace
id|ti-&gt;error
op_assign
l_string|&quot;dm-stripe: Target length not divisable by &quot;
l_string|&quot;number of stripes&quot;
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Do we have enough arguments for that many stripes ?&n;&t; */
r_if
c_cond
(paren
id|argc
op_ne
(paren
l_int|2
op_plus
l_int|2
op_star
id|stripes
)paren
)paren
(brace
id|ti-&gt;error
op_assign
l_string|&quot;dm-stripe: Not enough destinations &quot;
l_string|&quot;specified&quot;
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|sc
op_assign
id|alloc_context
c_func
(paren
id|stripes
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sc
)paren
(brace
id|ti-&gt;error
op_assign
l_string|&quot;dm-stripe: Memory allocation for striped context &quot;
l_string|&quot;failed&quot;
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|sc-&gt;stripes
op_assign
id|stripes
suffix:semicolon
id|sc-&gt;stripe_width
op_assign
id|width
suffix:semicolon
id|ti-&gt;split_io
op_assign
id|chunk_size
suffix:semicolon
id|sc-&gt;chunk_mask
op_assign
(paren
(paren
id|sector_t
)paren
id|chunk_size
)paren
op_minus
l_int|1
suffix:semicolon
r_for
c_loop
(paren
id|sc-&gt;chunk_shift
op_assign
l_int|0
suffix:semicolon
id|chunk_size
suffix:semicolon
id|sc-&gt;chunk_shift
op_increment
)paren
id|chunk_size
op_rshift_assign
l_int|1
suffix:semicolon
id|sc-&gt;chunk_shift
op_decrement
suffix:semicolon
multiline_comment|/*&n;&t; * Get the stripe destinations.&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|stripes
suffix:semicolon
id|i
op_increment
)paren
(brace
id|argv
op_add_assign
l_int|2
suffix:semicolon
id|r
op_assign
id|get_stripe
c_func
(paren
id|ti
comma
id|sc
comma
id|i
comma
id|argv
)paren
suffix:semicolon
r_if
c_cond
(paren
id|r
OL
l_int|0
)paren
(brace
id|ti-&gt;error
op_assign
l_string|&quot;dm-stripe: Couldn&squot;t parse stripe &quot;
l_string|&quot;destination&quot;
suffix:semicolon
r_while
c_loop
(paren
id|i
op_decrement
)paren
id|dm_put_device
c_func
(paren
id|ti
comma
id|sc-&gt;stripe
(braket
id|i
)braket
dot
id|dev
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|sc
)paren
suffix:semicolon
r_return
id|r
suffix:semicolon
)brace
)brace
id|ti
op_member_access_from_pointer
r_private
op_assign
id|sc
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|stripe_dtr
r_static
r_void
id|stripe_dtr
c_func
(paren
r_struct
id|dm_target
op_star
id|ti
)paren
(brace
r_int
r_int
id|i
suffix:semicolon
r_struct
id|stripe_c
op_star
id|sc
op_assign
(paren
r_struct
id|stripe_c
op_star
)paren
id|ti
op_member_access_from_pointer
r_private
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|sc-&gt;stripes
suffix:semicolon
id|i
op_increment
)paren
id|dm_put_device
c_func
(paren
id|ti
comma
id|sc-&gt;stripe
(braket
id|i
)braket
dot
id|dev
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|sc
)paren
suffix:semicolon
)brace
DECL|function|stripe_map
r_static
r_int
id|stripe_map
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
r_struct
id|stripe_c
op_star
id|sc
op_assign
(paren
r_struct
id|stripe_c
op_star
)paren
id|ti
op_member_access_from_pointer
r_private
suffix:semicolon
id|sector_t
id|offset
op_assign
id|bio-&gt;bi_sector
op_minus
id|ti-&gt;begin
suffix:semicolon
id|sector_t
id|chunk
op_assign
id|offset
op_rshift
id|sc-&gt;chunk_shift
suffix:semicolon
r_uint32
id|stripe
op_assign
id|sector_div
c_func
(paren
id|chunk
comma
id|sc-&gt;stripes
)paren
suffix:semicolon
id|bio-&gt;bi_bdev
op_assign
id|sc-&gt;stripe
(braket
id|stripe
)braket
dot
id|dev-&gt;bdev
suffix:semicolon
id|bio-&gt;bi_sector
op_assign
id|sc-&gt;stripe
(braket
id|stripe
)braket
dot
id|physical_start
op_plus
(paren
id|chunk
op_lshift
id|sc-&gt;chunk_shift
)paren
op_plus
(paren
id|offset
op_amp
id|sc-&gt;chunk_mask
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|stripe_status
r_static
r_int
id|stripe_status
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
r_int
id|maxlen
)paren
(brace
r_struct
id|stripe_c
op_star
id|sc
op_assign
(paren
r_struct
id|stripe_c
op_star
)paren
id|ti
op_member_access_from_pointer
r_private
suffix:semicolon
r_int
r_int
id|sz
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|i
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
id|DMEMIT
c_func
(paren
l_string|&quot;%d &quot;
id|SECTOR_FORMAT
comma
id|sc-&gt;stripes
comma
id|sc-&gt;chunk_mask
op_plus
l_int|1
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|sc-&gt;stripes
suffix:semicolon
id|i
op_increment
)paren
id|DMEMIT
c_func
(paren
l_string|&quot; %s &quot;
id|SECTOR_FORMAT
comma
id|sc-&gt;stripe
(braket
id|i
)braket
dot
id|dev-&gt;name
comma
id|sc-&gt;stripe
(braket
id|i
)braket
dot
id|physical_start
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|stripe_target
r_static
r_struct
id|target_type
id|stripe_target
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;striped&quot;
comma
dot
id|version
op_assign
(brace
l_int|1
comma
l_int|0
comma
l_int|2
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
id|stripe_ctr
comma
dot
id|dtr
op_assign
id|stripe_dtr
comma
dot
id|map
op_assign
id|stripe_map
comma
dot
id|status
op_assign
id|stripe_status
comma
)brace
suffix:semicolon
DECL|function|dm_stripe_init
r_int
id|__init
id|dm_stripe_init
c_func
(paren
r_void
)paren
(brace
r_int
id|r
suffix:semicolon
id|r
op_assign
id|dm_register_target
c_func
(paren
op_amp
id|stripe_target
)paren
suffix:semicolon
r_if
c_cond
(paren
id|r
OL
l_int|0
)paren
id|DMWARN
c_func
(paren
l_string|&quot;striped target registration failed&quot;
)paren
suffix:semicolon
r_return
id|r
suffix:semicolon
)brace
DECL|function|dm_stripe_exit
r_void
id|dm_stripe_exit
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
id|stripe_target
)paren
)paren
id|DMWARN
c_func
(paren
l_string|&quot;striped target unregistration failed&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
eof
