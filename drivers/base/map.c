multiline_comment|/*&n; *  linux/drivers/base/map.c&n; *&n; * (C) Copyright Al Viro 2002,2003&n; *&t;Released under GPL v2.&n; *&n; * NOTE: data structure needs to be changed.  It works, but for large dev_t&n; * it will be too slow.  It is isolated, though, so these changes will be&n; * local to that file.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/kdev_t.h&gt;
macro_line|#include &lt;linux/kobject.h&gt;
macro_line|#include &lt;linux/kobj_map.h&gt;
DECL|struct|kobj_map
r_struct
id|kobj_map
(brace
DECL|struct|probe
r_struct
id|probe
(brace
DECL|member|next
r_struct
id|probe
op_star
id|next
suffix:semicolon
DECL|member|dev
id|dev_t
id|dev
suffix:semicolon
DECL|member|range
r_int
r_int
id|range
suffix:semicolon
DECL|member|owner
r_struct
id|module
op_star
id|owner
suffix:semicolon
DECL|member|get
id|kobj_probe_t
op_star
id|get
suffix:semicolon
DECL|member|lock
r_int
(paren
op_star
id|lock
)paren
(paren
id|dev_t
comma
r_void
op_star
)paren
suffix:semicolon
DECL|member|data
r_void
op_star
id|data
suffix:semicolon
DECL|member|probes
)brace
op_star
id|probes
(braket
l_int|255
)braket
suffix:semicolon
DECL|member|sem
r_struct
id|rw_semaphore
op_star
id|sem
suffix:semicolon
)brace
suffix:semicolon
DECL|function|dev_to_index
r_static
r_inline
r_int
id|dev_to_index
c_func
(paren
id|dev_t
id|dev
)paren
(brace
r_return
id|MAJOR
c_func
(paren
id|dev
)paren
op_mod
l_int|255
suffix:semicolon
)brace
DECL|function|kobj_map
r_int
id|kobj_map
c_func
(paren
r_struct
id|kobj_map
op_star
id|domain
comma
id|dev_t
id|dev
comma
r_int
r_int
id|range
comma
r_struct
id|module
op_star
id|module
comma
id|kobj_probe_t
op_star
id|probe
comma
r_int
(paren
op_star
id|lock
)paren
(paren
id|dev_t
comma
r_void
op_star
)paren
comma
r_void
op_star
id|data
)paren
(brace
r_int
id|n
op_assign
id|MAJOR
c_func
(paren
id|dev
op_plus
id|range
op_minus
l_int|1
)paren
op_minus
id|MAJOR
c_func
(paren
id|dev
)paren
op_plus
l_int|1
suffix:semicolon
r_int
id|index
op_assign
id|MAJOR
c_func
(paren
id|dev
)paren
suffix:semicolon
r_int
id|i
suffix:semicolon
r_struct
id|probe
op_star
id|p
suffix:semicolon
r_if
c_cond
(paren
id|n
OG
l_int|255
)paren
id|n
op_assign
l_int|255
suffix:semicolon
id|p
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|probe
)paren
op_star
id|n
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOMEM
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
id|n
suffix:semicolon
id|i
op_increment
comma
id|p
op_increment
)paren
(brace
id|p-&gt;owner
op_assign
id|module
suffix:semicolon
id|p-&gt;get
op_assign
id|probe
suffix:semicolon
id|p-&gt;lock
op_assign
id|lock
suffix:semicolon
id|p-&gt;dev
op_assign
id|dev
suffix:semicolon
id|p-&gt;range
op_assign
id|range
suffix:semicolon
id|p-&gt;data
op_assign
id|data
suffix:semicolon
)brace
id|down_write
c_func
(paren
id|domain-&gt;sem
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
comma
id|p
op_sub_assign
id|n
suffix:semicolon
id|i
OL
id|n
suffix:semicolon
id|i
op_increment
comma
id|p
op_increment
comma
id|index
op_increment
)paren
(brace
r_struct
id|probe
op_star
op_star
id|s
op_assign
op_amp
id|domain-&gt;probes
(braket
id|index
op_mod
l_int|255
)braket
suffix:semicolon
r_while
c_loop
(paren
op_star
id|s
op_logical_and
(paren
op_star
id|s
)paren
op_member_access_from_pointer
id|range
OL
id|range
)paren
id|s
op_assign
op_amp
(paren
op_star
id|s
)paren
op_member_access_from_pointer
id|next
suffix:semicolon
id|p-&gt;next
op_assign
op_star
id|s
suffix:semicolon
op_star
id|s
op_assign
id|p
suffix:semicolon
)brace
id|up_write
c_func
(paren
id|domain-&gt;sem
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|kobj_unmap
r_void
id|kobj_unmap
c_func
(paren
r_struct
id|kobj_map
op_star
id|domain
comma
id|dev_t
id|dev
comma
r_int
r_int
id|range
)paren
(brace
r_int
id|n
op_assign
id|MAJOR
c_func
(paren
id|dev
op_plus
id|range
op_minus
l_int|1
)paren
op_minus
id|MAJOR
c_func
(paren
id|dev
)paren
op_plus
l_int|1
suffix:semicolon
r_int
id|index
op_assign
id|MAJOR
c_func
(paren
id|dev
)paren
suffix:semicolon
r_int
id|i
suffix:semicolon
r_struct
id|probe
op_star
id|found
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|n
OG
l_int|255
)paren
id|n
op_assign
l_int|255
suffix:semicolon
id|down_write
c_func
(paren
id|domain-&gt;sem
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
id|n
suffix:semicolon
id|i
op_increment
comma
id|index
op_increment
)paren
(brace
r_struct
id|probe
op_star
op_star
id|s
suffix:semicolon
r_for
c_loop
(paren
id|s
op_assign
op_amp
id|domain-&gt;probes
(braket
id|index
op_mod
l_int|255
)braket
suffix:semicolon
op_star
id|s
suffix:semicolon
id|s
op_assign
op_amp
(paren
op_star
id|s
)paren
op_member_access_from_pointer
id|next
)paren
(brace
r_struct
id|probe
op_star
id|p
op_assign
op_star
id|s
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;dev
op_eq
id|dev
op_logical_and
id|p-&gt;range
op_eq
id|range
)paren
(brace
op_star
id|s
op_assign
id|p-&gt;next
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|found
)paren
id|found
op_assign
id|p
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
)brace
id|up_write
c_func
(paren
id|domain-&gt;sem
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|found
)paren
suffix:semicolon
)brace
DECL|function|kobj_lookup
r_struct
id|kobject
op_star
id|kobj_lookup
c_func
(paren
r_struct
id|kobj_map
op_star
id|domain
comma
id|dev_t
id|dev
comma
r_int
op_star
id|index
)paren
(brace
r_struct
id|kobject
op_star
id|kobj
suffix:semicolon
r_struct
id|probe
op_star
id|p
suffix:semicolon
r_int
id|best
op_assign
op_complement
l_int|0U
suffix:semicolon
id|retry
suffix:colon
id|down_read
c_func
(paren
id|domain-&gt;sem
)paren
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
id|domain-&gt;probes
(braket
id|MAJOR
c_func
(paren
id|dev
)paren
op_mod
l_int|255
)braket
suffix:semicolon
id|p
suffix:semicolon
id|p
op_assign
id|p-&gt;next
)paren
(brace
r_struct
id|kobject
op_star
(paren
op_star
id|probe
)paren
(paren
id|dev_t
comma
r_int
op_star
comma
r_void
op_star
)paren
suffix:semicolon
r_struct
id|module
op_star
id|owner
suffix:semicolon
r_void
op_star
id|data
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;dev
OG
id|dev
op_logical_or
id|p-&gt;dev
op_plus
id|p-&gt;range
op_minus
l_int|1
OL
id|dev
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;range
op_minus
l_int|1
op_ge
id|best
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|try_module_get
c_func
(paren
id|p-&gt;owner
)paren
)paren
r_continue
suffix:semicolon
id|owner
op_assign
id|p-&gt;owner
suffix:semicolon
id|data
op_assign
id|p-&gt;data
suffix:semicolon
id|probe
op_assign
id|p-&gt;get
suffix:semicolon
id|best
op_assign
id|p-&gt;range
op_minus
l_int|1
suffix:semicolon
op_star
id|index
op_assign
id|dev
op_minus
id|p-&gt;dev
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;lock
op_logical_and
id|p
op_member_access_from_pointer
id|lock
c_func
(paren
id|dev
comma
id|data
)paren
OL
l_int|0
)paren
(brace
id|module_put
c_func
(paren
id|owner
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|up_read
c_func
(paren
id|domain-&gt;sem
)paren
suffix:semicolon
id|kobj
op_assign
id|probe
c_func
(paren
id|dev
comma
id|index
comma
id|data
)paren
suffix:semicolon
multiline_comment|/* Currently -&gt;owner protects _only_ -&gt;probe() itself. */
id|module_put
c_func
(paren
id|owner
)paren
suffix:semicolon
r_if
c_cond
(paren
id|kobj
)paren
r_return
id|kobj
suffix:semicolon
r_goto
id|retry
suffix:semicolon
)brace
id|up_read
c_func
(paren
id|domain-&gt;sem
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|kobj_map_init
r_struct
id|kobj_map
op_star
id|kobj_map_init
c_func
(paren
id|kobj_probe_t
op_star
id|base_probe
comma
r_struct
id|subsystem
op_star
id|s
)paren
(brace
r_struct
id|kobj_map
op_star
id|p
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|kobj_map
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_struct
id|probe
op_star
id|base
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|probe
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_int
id|i
suffix:semicolon
id|memset
c_func
(paren
id|base
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|probe
)paren
)paren
suffix:semicolon
id|base-&gt;dev
op_assign
l_int|1
suffix:semicolon
id|base-&gt;range
op_assign
op_complement
l_int|0
suffix:semicolon
id|base-&gt;get
op_assign
id|base_probe
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
l_int|255
suffix:semicolon
id|i
op_increment
)paren
id|p-&gt;probes
(braket
id|i
)braket
op_assign
id|base
suffix:semicolon
id|p-&gt;sem
op_assign
op_amp
id|s-&gt;rwsem
suffix:semicolon
r_return
id|p
suffix:semicolon
)brace
eof
