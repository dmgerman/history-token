multiline_comment|/* &n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 2004 Silicon Graphics, Inc. All rights reserved.&n; *&n; * SGI Altix topology and hardware performance monitoring API.&n; * Mark Goodwin &lt;markgw@sgi.com&gt;. &n; *&n; * Creates /proc/sgi_sn/sn_topology (read-only) to export&n; * info about Altix nodes, routers, CPUs and NumaLink&n; * interconnection/topology.&n; *&n; * Also creates a dynamic misc device named &quot;sn_hwperf&quot;&n; * that supports an ioctl interface to call down into SAL&n; * to discover hw objects, topology and to read/write&n; * memory mapped registers, e.g. for performance monitoring.&n; * The &quot;sn_hwperf&quot; device is registered only after the procfs&n; * file is first opened, i.e. only if/when it&squot;s needed. &n; *&n; * This API is used by SGI Performance Co-Pilot and other&n; * tools, see http://oss.sgi.com/projects/pcp&n; */
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;linux/seq_file.h&gt;
macro_line|#include &lt;linux/miscdevice.h&gt;
macro_line|#include &lt;linux/cpumask.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/topology.h&gt;
macro_line|#include &lt;asm/smp.h&gt;
macro_line|#include &lt;asm/semaphore.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/sal.h&gt;
macro_line|#include &lt;asm/sn/io.h&gt;
macro_line|#include &lt;asm/sn/sn_sal.h&gt;
macro_line|#include &lt;asm/sn/module.h&gt;
macro_line|#include &lt;asm/sn/geo.h&gt;
macro_line|#include &lt;asm/sn/sn2/sn_hwperf.h&gt;
DECL|variable|sn_hwperf_salheap
r_static
r_void
op_star
id|sn_hwperf_salheap
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|sn_hwperf_obj_cnt
r_static
r_int
id|sn_hwperf_obj_cnt
op_assign
l_int|0
suffix:semicolon
DECL|variable|sn_hwperf_master_nasid
r_static
id|nasid_t
id|sn_hwperf_master_nasid
op_assign
id|INVALID_NASID
suffix:semicolon
r_static
r_int
id|sn_hwperf_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
id|DECLARE_MUTEX
c_func
(paren
id|sn_hwperf_init_mutex
)paren
suffix:semicolon
DECL|function|sn_hwperf_enum_objects
r_static
r_int
id|sn_hwperf_enum_objects
c_func
(paren
r_int
op_star
id|nobj
comma
r_struct
id|sn_hwperf_object_info
op_star
op_star
id|ret
)paren
(brace
r_int
id|e
suffix:semicolon
id|u64
id|sz
suffix:semicolon
r_struct
id|sn_hwperf_object_info
op_star
id|objbuf
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
(paren
id|e
op_assign
id|sn_hwperf_init
c_func
(paren
)paren
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;sn_hwperf_init failed: err %d&bslash;n&quot;
comma
id|e
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|sz
op_assign
id|sn_hwperf_obj_cnt
op_star
r_sizeof
(paren
r_struct
id|sn_hwperf_object_info
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|objbuf
op_assign
(paren
r_struct
id|sn_hwperf_object_info
op_star
)paren
id|vmalloc
c_func
(paren
id|sz
)paren
)paren
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;sn_hwperf_enum_objects: vmalloc(%d) failed&bslash;n&quot;
comma
(paren
r_int
)paren
id|sz
)paren
suffix:semicolon
id|e
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|e
op_assign
id|ia64_sn_hwperf_op
c_func
(paren
id|sn_hwperf_master_nasid
comma
id|SN_HWPERF_ENUM_OBJECTS
comma
l_int|0
comma
id|sz
comma
(paren
id|u64
)paren
id|objbuf
comma
l_int|0
comma
l_int|0
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|e
op_ne
id|SN_HWPERF_OP_OK
)paren
(brace
id|e
op_assign
op_minus
id|EINVAL
suffix:semicolon
id|vfree
c_func
(paren
id|objbuf
)paren
suffix:semicolon
)brace
id|out
suffix:colon
op_star
id|nobj
op_assign
id|sn_hwperf_obj_cnt
suffix:semicolon
op_star
id|ret
op_assign
id|objbuf
suffix:semicolon
r_return
id|e
suffix:semicolon
)brace
DECL|function|sn_hwperf_geoid_to_cnode
r_static
r_int
id|sn_hwperf_geoid_to_cnode
c_func
(paren
r_char
op_star
id|location
)paren
(brace
r_int
id|cnode
suffix:semicolon
id|geoid_t
id|geoid
suffix:semicolon
id|moduleid_t
id|module_id
suffix:semicolon
r_char
id|type
suffix:semicolon
r_int
id|rack
comma
id|slot
comma
id|slab
suffix:semicolon
r_int
id|this_rack
comma
id|this_slot
comma
id|this_slab
suffix:semicolon
r_if
c_cond
(paren
id|sscanf
c_func
(paren
id|location
comma
l_string|&quot;%03d%c%02d#%d&quot;
comma
op_amp
id|rack
comma
op_amp
id|type
comma
op_amp
id|slot
comma
op_amp
id|slab
)paren
op_ne
l_int|4
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_for
c_loop
(paren
id|cnode
op_assign
l_int|0
suffix:semicolon
id|cnode
OL
id|numionodes
suffix:semicolon
id|cnode
op_increment
)paren
(brace
id|geoid
op_assign
id|cnodeid_get_geoid
c_func
(paren
id|cnode
)paren
suffix:semicolon
id|module_id
op_assign
id|geo_module
c_func
(paren
id|geoid
)paren
suffix:semicolon
id|this_rack
op_assign
id|MODULE_GET_RACK
c_func
(paren
id|module_id
)paren
suffix:semicolon
id|this_slot
op_assign
id|MODULE_GET_BPOS
c_func
(paren
id|module_id
)paren
suffix:semicolon
id|this_slab
op_assign
id|geo_slab
c_func
(paren
id|geoid
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rack
op_eq
id|this_rack
op_logical_and
id|slot
op_eq
id|this_slot
op_logical_and
id|slab
op_eq
id|this_slab
)paren
r_break
suffix:semicolon
)brace
r_return
id|cnode
OL
id|numionodes
ques
c_cond
id|cnode
suffix:colon
op_minus
l_int|1
suffix:semicolon
)brace
DECL|function|sn_hwperf_obj_to_cnode
r_static
r_int
id|sn_hwperf_obj_to_cnode
c_func
(paren
r_struct
id|sn_hwperf_object_info
op_star
id|obj
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|obj-&gt;sn_hwp_this_part
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_return
id|sn_hwperf_geoid_to_cnode
c_func
(paren
id|obj-&gt;location
)paren
suffix:semicolon
)brace
DECL|function|sn_hwperf_generic_ordinal
r_static
r_int
id|sn_hwperf_generic_ordinal
c_func
(paren
r_struct
id|sn_hwperf_object_info
op_star
id|obj
comma
r_struct
id|sn_hwperf_object_info
op_star
id|objs
)paren
(brace
r_int
id|ordinal
suffix:semicolon
r_struct
id|sn_hwperf_object_info
op_star
id|p
suffix:semicolon
r_for
c_loop
(paren
id|ordinal
op_assign
l_int|0
comma
id|p
op_assign
id|objs
suffix:semicolon
id|p
op_ne
id|obj
suffix:semicolon
id|p
op_increment
)paren
(brace
r_if
c_cond
(paren
id|SN_HWPERF_FOREIGN
c_func
(paren
id|p
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;location
(braket
l_int|3
)braket
op_eq
id|obj-&gt;location
(braket
l_int|3
)braket
)paren
id|ordinal
op_increment
suffix:semicolon
)brace
r_return
id|ordinal
suffix:semicolon
)brace
r_static
r_struct
(brace
DECL|member|brick_chars
r_char
op_star
id|brick_chars
suffix:semicolon
DECL|member|brick_name
r_char
op_star
id|brick_name
suffix:semicolon
DECL|variable|brick_names
)brace
id|brick_names
(braket
)braket
op_assign
(brace
(brace
l_string|&quot;c^jbf&quot;
comma
l_string|&quot;node&quot;
)brace
comma
(brace
l_string|&quot;r&quot;
comma
l_string|&quot;router&quot;
)brace
comma
(brace
l_int|NULL
comma
l_string|&quot;?-brick&quot;
)brace
)brace
suffix:semicolon
DECL|function|sn_hwperf_get_brickname
r_static
r_char
op_star
id|sn_hwperf_get_brickname
c_func
(paren
r_struct
id|sn_hwperf_object_info
op_star
id|obj
comma
r_struct
id|sn_hwperf_object_info
op_star
id|objs
comma
r_int
op_star
id|ordinal
)paren
(brace
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|brick_names
(braket
id|i
)braket
dot
id|brick_chars
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|strchr
c_func
(paren
id|brick_names
(braket
id|i
)braket
dot
id|brick_chars
comma
id|obj-&gt;location
(braket
l_int|3
)braket
)paren
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|brick_names
(braket
id|i
)braket
dot
id|brick_name
comma
l_string|&quot;node&quot;
)paren
op_eq
l_int|0
)paren
op_star
id|ordinal
op_assign
id|sn_hwperf_obj_to_cnode
c_func
(paren
id|obj
)paren
suffix:semicolon
r_else
(brace
op_star
id|ordinal
op_assign
id|sn_hwperf_generic_ordinal
c_func
(paren
id|obj
comma
id|objs
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|brick_names
(braket
id|i
)braket
dot
id|brick_chars
)paren
id|brick_names
(braket
id|i
)braket
dot
id|brick_name
(braket
l_int|0
)braket
op_assign
id|obj-&gt;location
(braket
l_int|3
)braket
suffix:semicolon
)brace
r_return
id|brick_names
(braket
id|i
)braket
dot
id|brick_name
suffix:semicolon
)brace
DECL|function|sn_topology_show
r_static
r_int
id|sn_topology_show
c_func
(paren
r_struct
id|seq_file
op_star
id|s
comma
r_void
op_star
id|d
)paren
(brace
r_int
id|sz
suffix:semicolon
r_int
id|pt
suffix:semicolon
r_int
id|e
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
id|j
suffix:semicolon
r_const
r_char
op_star
id|brickname
suffix:semicolon
r_int
id|ordinal
suffix:semicolon
id|cpumask_t
id|cpumask
suffix:semicolon
r_char
id|slice
suffix:semicolon
r_struct
id|cpuinfo_ia64
op_star
id|c
suffix:semicolon
r_struct
id|sn_hwperf_port_info
op_star
id|ptdata
suffix:semicolon
r_struct
id|sn_hwperf_object_info
op_star
id|p
suffix:semicolon
r_struct
id|sn_hwperf_object_info
op_star
id|obj
op_assign
id|d
suffix:semicolon
multiline_comment|/* this object */
r_struct
id|sn_hwperf_object_info
op_star
id|objs
op_assign
id|s
op_member_access_from_pointer
r_private
suffix:semicolon
multiline_comment|/* all objects */
r_if
c_cond
(paren
id|obj
op_eq
id|objs
)paren
(brace
id|seq_printf
c_func
(paren
id|s
comma
l_string|&quot;# sn_topology version 1&bslash;n&quot;
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|s
comma
l_string|&quot;# objtype ordinal location partition&quot;
l_string|&quot; [attribute value [, ...]]&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|SN_HWPERF_FOREIGN
c_func
(paren
id|obj
)paren
)paren
(brace
multiline_comment|/* private in another partition: not interesting */
r_return
l_int|0
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|obj-&gt;name
(braket
id|i
)braket
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|obj-&gt;name
(braket
id|i
)braket
op_eq
l_char|&squot; &squot;
)paren
id|obj-&gt;name
(braket
id|i
)braket
op_assign
l_char|&squot;_&squot;
suffix:semicolon
)brace
id|brickname
op_assign
id|sn_hwperf_get_brickname
c_func
(paren
id|obj
comma
id|objs
comma
op_amp
id|ordinal
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|s
comma
l_string|&quot;%s %d %s %s asic %s&quot;
comma
id|brickname
comma
id|ordinal
comma
id|obj-&gt;location
comma
id|obj-&gt;sn_hwp_this_part
ques
c_cond
l_string|&quot;local&quot;
suffix:colon
l_string|&quot;shared&quot;
comma
id|obj-&gt;name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|brickname
comma
l_string|&quot;node&quot;
)paren
op_ne
l_int|0
)paren
id|seq_putc
c_func
(paren
id|s
comma
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
r_else
(brace
id|seq_printf
c_func
(paren
id|s
comma
l_string|&quot;, nasid 0x%x&quot;
comma
id|cnodeid_to_nasid
c_func
(paren
id|ordinal
)paren
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
id|numionodes
suffix:semicolon
id|i
op_increment
)paren
(brace
id|seq_printf
c_func
(paren
id|s
comma
id|i
ques
c_cond
l_string|&quot;:%d&quot;
suffix:colon
l_string|&quot;, dist %d&quot;
comma
id|node_distance
c_func
(paren
id|ordinal
comma
id|i
)paren
)paren
suffix:semicolon
)brace
id|seq_putc
c_func
(paren
id|s
comma
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * CPUs on this node&n;&t;&t; */
id|cpumask
op_assign
id|node_to_cpumask
c_func
(paren
id|ordinal
)paren
suffix:semicolon
id|for_each_online_cpu
c_func
(paren
id|i
)paren
(brace
r_if
c_cond
(paren
id|cpu_isset
c_func
(paren
id|i
comma
id|cpumask
)paren
)paren
(brace
id|slice
op_assign
l_char|&squot;a&squot;
op_plus
id|cpuid_to_slice
c_func
(paren
id|i
)paren
suffix:semicolon
id|c
op_assign
id|cpu_data
c_func
(paren
id|i
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|s
comma
l_string|&quot;cpu %d %s%c local&quot;
l_string|&quot; freq %luMHz, arch ia64&quot;
comma
id|i
comma
id|obj-&gt;location
comma
id|slice
comma
id|c-&gt;proc_freq
op_div
l_int|1000000
)paren
suffix:semicolon
id|for_each_online_cpu
c_func
(paren
id|j
)paren
(brace
id|seq_printf
c_func
(paren
id|s
comma
id|j
ques
c_cond
l_string|&quot;:%d&quot;
suffix:colon
l_string|&quot;, dist %d&quot;
comma
id|node_distance
c_func
(paren
id|cpuid_to_cnodeid
c_func
(paren
id|i
)paren
comma
id|cpuid_to_cnodeid
c_func
(paren
id|j
)paren
)paren
)paren
suffix:semicolon
)brace
id|seq_putc
c_func
(paren
id|s
comma
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
)brace
)brace
)brace
r_if
c_cond
(paren
id|obj-&gt;ports
)paren
(brace
multiline_comment|/*&n;&t;&t; * numalink ports&n;&t;&t; */
id|sz
op_assign
id|obj-&gt;ports
op_star
r_sizeof
(paren
r_struct
id|sn_hwperf_port_info
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ptdata
op_assign
id|vmalloc
c_func
(paren
id|sz
)paren
)paren
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|e
op_assign
id|ia64_sn_hwperf_op
c_func
(paren
id|sn_hwperf_master_nasid
comma
id|SN_HWPERF_ENUM_PORTS
comma
id|obj-&gt;id
comma
id|sz
comma
(paren
id|u64
)paren
id|ptdata
comma
l_int|0
comma
l_int|0
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|e
op_ne
id|SN_HWPERF_OP_OK
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_for
c_loop
(paren
id|ordinal
op_assign
l_int|0
comma
id|p
op_assign
id|objs
suffix:semicolon
id|p
op_ne
id|obj
suffix:semicolon
id|p
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|SN_HWPERF_FOREIGN
c_func
(paren
id|p
)paren
)paren
id|ordinal
op_add_assign
id|p-&gt;ports
suffix:semicolon
)brace
r_for
c_loop
(paren
id|pt
op_assign
l_int|0
suffix:semicolon
id|pt
OL
id|obj-&gt;ports
suffix:semicolon
id|pt
op_increment
)paren
(brace
r_for
c_loop
(paren
id|p
op_assign
id|objs
comma
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|sn_hwperf_obj_cnt
suffix:semicolon
id|i
op_increment
comma
id|p
op_increment
)paren
(brace
r_if
c_cond
(paren
id|ptdata
(braket
id|pt
)braket
dot
id|conn_id
op_eq
id|p-&gt;id
)paren
(brace
r_break
suffix:semicolon
)brace
)brace
id|seq_printf
c_func
(paren
id|s
comma
l_string|&quot;numalink %d %s-%d&quot;
comma
id|ordinal
op_plus
id|pt
comma
id|obj-&gt;location
comma
id|ptdata
(braket
id|pt
)braket
dot
id|port
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
op_ge
id|sn_hwperf_obj_cnt
)paren
(brace
multiline_comment|/* no connection */
id|seq_puts
c_func
(paren
id|s
comma
l_string|&quot; local endpoint disconnected&quot;
l_string|&quot;, protocol unknown&bslash;n&quot;
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|obj-&gt;sn_hwp_this_part
op_logical_and
id|p-&gt;sn_hwp_this_part
)paren
multiline_comment|/* both ends local to this partition */
id|seq_puts
c_func
(paren
id|s
comma
l_string|&quot; local&quot;
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|obj-&gt;sn_hwp_this_part
op_logical_and
op_logical_neg
id|p-&gt;sn_hwp_this_part
)paren
multiline_comment|/* both ends of the link in foreign partiton */
id|seq_puts
c_func
(paren
id|s
comma
l_string|&quot; foreign&quot;
)paren
suffix:semicolon
r_else
multiline_comment|/* link straddles a partition */
id|seq_puts
c_func
(paren
id|s
comma
l_string|&quot; shared&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * Unlikely, but strictly should query the LLP config&n;&t;&t;&t; * registers because an NL4R can be configured to run&n;&t;&t;&t; * NL3 protocol, even when not talking to an NL3 router.&n;&t;&t;&t; * Ditto for node-node.&n;&t;&t;&t; */
id|seq_printf
c_func
(paren
id|s
comma
l_string|&quot; endpoint %s-%d, protocol %s&bslash;n&quot;
comma
id|p-&gt;location
comma
id|ptdata
(braket
id|pt
)braket
dot
id|conn_port
comma
id|strcmp
c_func
(paren
id|obj-&gt;name
comma
l_string|&quot;NL3Router&quot;
)paren
op_eq
l_int|0
op_logical_or
id|strcmp
c_func
(paren
id|p-&gt;name
comma
l_string|&quot;NL3Router&quot;
)paren
op_eq
l_int|0
ques
c_cond
l_string|&quot;LLP3&quot;
suffix:colon
l_string|&quot;LLP4&quot;
)paren
suffix:semicolon
)brace
id|vfree
c_func
(paren
id|ptdata
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sn_topology_start
r_static
r_void
op_star
id|sn_topology_start
c_func
(paren
r_struct
id|seq_file
op_star
id|s
comma
id|loff_t
op_star
id|pos
)paren
(brace
r_struct
id|sn_hwperf_object_info
op_star
id|objs
op_assign
id|s
op_member_access_from_pointer
r_private
suffix:semicolon
r_if
c_cond
(paren
op_star
id|pos
OL
id|sn_hwperf_obj_cnt
)paren
r_return
(paren
r_void
op_star
)paren
(paren
id|objs
op_plus
op_star
id|pos
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|sn_topology_next
r_static
r_void
op_star
id|sn_topology_next
c_func
(paren
r_struct
id|seq_file
op_star
id|s
comma
r_void
op_star
id|v
comma
id|loff_t
op_star
id|pos
)paren
(brace
op_increment
op_star
id|pos
suffix:semicolon
r_return
id|sn_topology_start
c_func
(paren
id|s
comma
id|pos
)paren
suffix:semicolon
)brace
DECL|function|sn_topology_stop
r_static
r_void
id|sn_topology_stop
c_func
(paren
r_struct
id|seq_file
op_star
id|m
comma
r_void
op_star
id|v
)paren
(brace
r_return
suffix:semicolon
)brace
multiline_comment|/*&n; * /proc/sgi_sn/sn_topology, read-only using seq_file&n; */
DECL|variable|sn_topology_seq_ops
r_static
r_struct
id|seq_operations
id|sn_topology_seq_ops
op_assign
(brace
dot
id|start
op_assign
id|sn_topology_start
comma
dot
id|next
op_assign
id|sn_topology_next
comma
dot
id|stop
op_assign
id|sn_topology_stop
comma
dot
id|show
op_assign
id|sn_topology_show
)brace
suffix:semicolon
DECL|struct|sn_hwperf_op_info
r_struct
id|sn_hwperf_op_info
(brace
DECL|member|op
id|u64
id|op
suffix:semicolon
DECL|member|a
r_struct
id|sn_hwperf_ioctl_args
op_star
id|a
suffix:semicolon
DECL|member|p
r_void
op_star
id|p
suffix:semicolon
DECL|member|v0
r_int
op_star
id|v0
suffix:semicolon
DECL|member|ret
r_int
id|ret
suffix:semicolon
)brace
suffix:semicolon
DECL|function|sn_hwperf_call_sal
r_static
r_void
id|sn_hwperf_call_sal
c_func
(paren
r_void
op_star
id|info
)paren
(brace
r_struct
id|sn_hwperf_op_info
op_star
id|op_info
op_assign
id|info
suffix:semicolon
r_int
id|r
suffix:semicolon
id|r
op_assign
id|ia64_sn_hwperf_op
c_func
(paren
id|sn_hwperf_master_nasid
comma
id|op_info-&gt;op
comma
id|op_info-&gt;a-&gt;arg
comma
id|op_info-&gt;a-&gt;sz
comma
(paren
id|u64
)paren
id|op_info-&gt;p
comma
l_int|0
comma
l_int|0
comma
id|op_info-&gt;v0
)paren
suffix:semicolon
id|op_info-&gt;ret
op_assign
id|r
suffix:semicolon
)brace
DECL|function|sn_hwperf_op_cpu
r_static
r_int
id|sn_hwperf_op_cpu
c_func
(paren
r_struct
id|sn_hwperf_op_info
op_star
id|op_info
)paren
(brace
id|u32
id|cpu
suffix:semicolon
id|u32
id|use_ipi
suffix:semicolon
r_int
id|r
op_assign
l_int|0
suffix:semicolon
id|cpumask_t
id|save_allowed
suffix:semicolon
id|cpu
op_assign
(paren
id|op_info-&gt;a-&gt;arg
op_amp
id|SN_HWPERF_ARG_CPU_MASK
)paren
op_rshift
l_int|32
suffix:semicolon
id|use_ipi
op_assign
id|op_info-&gt;a-&gt;arg
op_amp
id|SN_HWPERF_ARG_USE_IPI_MASK
suffix:semicolon
id|op_info-&gt;a-&gt;arg
op_and_assign
id|SN_HWPERF_ARG_OBJID_MASK
suffix:semicolon
r_if
c_cond
(paren
id|cpu
op_ne
id|SN_HWPERF_ARG_ANY_CPU
)paren
(brace
r_if
c_cond
(paren
id|cpu
op_ge
id|num_online_cpus
c_func
(paren
)paren
op_logical_or
op_logical_neg
id|cpu_online
c_func
(paren
id|cpu
)paren
)paren
(brace
id|r
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|cpu
op_eq
id|SN_HWPERF_ARG_ANY_CPU
op_logical_or
id|cpu
op_eq
id|get_cpu
c_func
(paren
)paren
)paren
(brace
multiline_comment|/* don&squot;t care, or already on correct cpu */
id|sn_hwperf_call_sal
c_func
(paren
id|op_info
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|use_ipi
)paren
(brace
multiline_comment|/* use an interprocessor interrupt to call SAL */
id|smp_call_function_single
c_func
(paren
id|cpu
comma
id|sn_hwperf_call_sal
comma
id|op_info
comma
l_int|1
comma
l_int|1
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* migrate the task before calling SAL */
id|save_allowed
op_assign
id|current-&gt;cpus_allowed
suffix:semicolon
id|set_cpus_allowed
c_func
(paren
id|current
comma
id|cpumask_of_cpu
c_func
(paren
id|cpu
)paren
)paren
suffix:semicolon
id|sn_hwperf_call_sal
c_func
(paren
id|op_info
)paren
suffix:semicolon
id|set_cpus_allowed
c_func
(paren
id|current
comma
id|save_allowed
)paren
suffix:semicolon
)brace
)brace
id|r
op_assign
id|op_info-&gt;ret
suffix:semicolon
id|out
suffix:colon
r_return
id|r
suffix:semicolon
)brace
multiline_comment|/*&n; * ioctl for &quot;sn_hwperf&quot; misc device&n; */
r_static
r_int
DECL|function|sn_hwperf_ioctl
id|sn_hwperf_ioctl
c_func
(paren
r_struct
id|inode
op_star
id|in
comma
r_struct
id|file
op_star
id|fp
comma
id|u32
id|op
comma
id|u64
id|arg
)paren
(brace
r_struct
id|sn_hwperf_ioctl_args
id|a
suffix:semicolon
r_struct
id|cpuinfo_ia64
op_star
id|cdata
suffix:semicolon
r_struct
id|sn_hwperf_object_info
op_star
id|objs
suffix:semicolon
r_struct
id|sn_hwperf_object_info
op_star
id|cpuobj
suffix:semicolon
r_struct
id|sn_hwperf_op_info
id|op_info
suffix:semicolon
r_void
op_star
id|p
op_assign
l_int|NULL
suffix:semicolon
r_int
id|nobj
suffix:semicolon
r_char
id|slice
suffix:semicolon
r_int
id|node
suffix:semicolon
r_int
id|r
suffix:semicolon
r_int
id|v0
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
id|j
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* only user requests are allowed here */
r_if
c_cond
(paren
(paren
id|op
op_amp
id|SN_HWPERF_OP_MASK
)paren
OL
l_int|10
)paren
(brace
id|r
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|error
suffix:semicolon
)brace
id|r
op_assign
id|copy_from_user
c_func
(paren
op_amp
id|a
comma
(paren
r_const
r_void
id|__user
op_star
)paren
id|arg
comma
r_sizeof
(paren
r_struct
id|sn_hwperf_ioctl_args
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|r
op_ne
l_int|0
)paren
(brace
id|r
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_goto
id|error
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Allocate memory to hold a kernel copy of the user buffer. The&n;&t; * buffer contents are either copied in or out (or both) of user&n;&t; * space depending on the flags encoded in the requested operation.&n;&t; */
r_if
c_cond
(paren
id|a.ptr
)paren
(brace
id|p
op_assign
id|vmalloc
c_func
(paren
id|a.sz
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p
)paren
(brace
id|r
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|error
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|op
op_amp
id|SN_HWPERF_OP_MEM_COPYIN
)paren
(brace
id|r
op_assign
id|copy_from_user
c_func
(paren
id|p
comma
(paren
r_const
r_void
id|__user
op_star
)paren
id|a.ptr
comma
id|a.sz
)paren
suffix:semicolon
r_if
c_cond
(paren
id|r
op_ne
l_int|0
)paren
(brace
id|r
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_goto
id|error
suffix:semicolon
)brace
)brace
r_switch
c_cond
(paren
id|op
)paren
(brace
r_case
id|SN_HWPERF_GET_CPU_INFO
suffix:colon
r_if
c_cond
(paren
id|a.sz
op_eq
r_sizeof
(paren
id|u64
)paren
)paren
(brace
multiline_comment|/* special case to get size needed */
op_star
(paren
id|u64
op_star
)paren
id|p
op_assign
(paren
id|u64
)paren
id|num_online_cpus
c_func
(paren
)paren
op_star
r_sizeof
(paren
r_struct
id|sn_hwperf_object_info
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|a.sz
OL
id|num_online_cpus
c_func
(paren
)paren
op_star
r_sizeof
(paren
r_struct
id|sn_hwperf_object_info
)paren
)paren
(brace
id|r
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|error
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|r
op_assign
id|sn_hwperf_enum_objects
c_func
(paren
op_amp
id|nobj
comma
op_amp
id|objs
)paren
)paren
op_eq
l_int|0
)paren
(brace
id|memset
c_func
(paren
id|p
comma
l_int|0
comma
id|a.sz
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
id|nobj
suffix:semicolon
id|i
op_increment
)paren
(brace
id|node
op_assign
id|sn_hwperf_obj_to_cnode
c_func
(paren
id|objs
op_plus
id|i
)paren
suffix:semicolon
id|for_each_online_cpu
c_func
(paren
id|j
)paren
(brace
r_if
c_cond
(paren
id|node
op_ne
id|cpu_to_node
c_func
(paren
id|j
)paren
)paren
r_continue
suffix:semicolon
id|cpuobj
op_assign
(paren
r_struct
id|sn_hwperf_object_info
op_star
)paren
id|p
op_plus
id|j
suffix:semicolon
id|slice
op_assign
l_char|&squot;a&squot;
op_plus
id|cpuid_to_slice
c_func
(paren
id|j
)paren
suffix:semicolon
id|cdata
op_assign
id|cpu_data
c_func
(paren
id|j
)paren
suffix:semicolon
id|cpuobj-&gt;id
op_assign
id|j
suffix:semicolon
id|snprintf
c_func
(paren
id|cpuobj-&gt;name
comma
r_sizeof
(paren
id|cpuobj-&gt;name
)paren
comma
l_string|&quot;CPU %luMHz %s&quot;
comma
id|cdata-&gt;proc_freq
op_div
l_int|1000000
comma
id|cdata-&gt;vendor
)paren
suffix:semicolon
id|snprintf
c_func
(paren
id|cpuobj-&gt;location
comma
r_sizeof
(paren
id|cpuobj-&gt;location
)paren
comma
l_string|&quot;%s%c&quot;
comma
id|objs
(braket
id|i
)braket
dot
id|location
comma
id|slice
)paren
suffix:semicolon
)brace
)brace
id|vfree
c_func
(paren
id|objs
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|SN_HWPERF_GET_NODE_NASID
suffix:colon
r_if
c_cond
(paren
id|a.sz
op_ne
r_sizeof
(paren
id|u64
)paren
op_logical_or
(paren
id|node
op_assign
id|a.arg
)paren
OL
l_int|0
op_logical_or
id|node
op_ge
id|numionodes
)paren
(brace
id|r
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|error
suffix:semicolon
)brace
op_star
(paren
id|u64
op_star
)paren
id|p
op_assign
(paren
id|u64
)paren
id|cnodeid_to_nasid
c_func
(paren
id|node
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SN_HWPERF_GET_OBJ_NODE
suffix:colon
r_if
c_cond
(paren
id|a.sz
op_ne
r_sizeof
(paren
id|u64
)paren
op_logical_or
id|a.arg
OL
l_int|0
)paren
(brace
id|r
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|error
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|r
op_assign
id|sn_hwperf_enum_objects
c_func
(paren
op_amp
id|nobj
comma
op_amp
id|objs
)paren
)paren
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|a.arg
op_ge
id|nobj
)paren
(brace
id|r
op_assign
op_minus
id|EINVAL
suffix:semicolon
id|vfree
c_func
(paren
id|objs
)paren
suffix:semicolon
r_goto
id|error
suffix:semicolon
)brace
r_if
c_cond
(paren
id|objs
(braket
(paren
id|i
op_assign
id|a.arg
)paren
)braket
dot
id|id
op_ne
id|a.arg
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|nobj
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|objs
(braket
id|i
)braket
dot
id|id
op_eq
id|a.arg
)paren
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|i
op_eq
id|nobj
)paren
(brace
id|r
op_assign
op_minus
id|EINVAL
suffix:semicolon
id|vfree
c_func
(paren
id|objs
)paren
suffix:semicolon
r_goto
id|error
suffix:semicolon
)brace
op_star
(paren
id|u64
op_star
)paren
id|p
op_assign
(paren
id|u64
)paren
id|sn_hwperf_obj_to_cnode
c_func
(paren
id|objs
op_plus
id|i
)paren
suffix:semicolon
id|vfree
c_func
(paren
id|objs
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|SN_HWPERF_GET_MMRS
suffix:colon
r_case
id|SN_HWPERF_SET_MMRS
suffix:colon
r_case
id|SN_HWPERF_OBJECT_DISTANCE
suffix:colon
id|op_info.p
op_assign
id|p
suffix:semicolon
id|op_info.a
op_assign
op_amp
id|a
suffix:semicolon
id|op_info.v0
op_assign
op_amp
id|v0
suffix:semicolon
id|op_info.op
op_assign
id|op
suffix:semicolon
id|r
op_assign
id|sn_hwperf_op_cpu
c_func
(paren
op_amp
id|op_info
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* all other ops are a direct SAL call */
id|r
op_assign
id|ia64_sn_hwperf_op
c_func
(paren
id|sn_hwperf_master_nasid
comma
id|op
comma
id|a.arg
comma
id|a.sz
comma
(paren
id|u64
)paren
id|p
comma
l_int|0
comma
l_int|0
comma
op_amp
id|v0
)paren
suffix:semicolon
id|a.v0
op_assign
id|v0
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|op
op_amp
id|SN_HWPERF_OP_MEM_COPYOUT
)paren
(brace
id|r
op_assign
id|copy_to_user
c_func
(paren
(paren
r_void
id|__user
op_star
)paren
id|a.ptr
comma
id|p
comma
id|a.sz
)paren
suffix:semicolon
r_if
c_cond
(paren
id|r
op_ne
l_int|0
)paren
(brace
id|r
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_goto
id|error
suffix:semicolon
)brace
)brace
id|error
suffix:colon
r_if
c_cond
(paren
id|p
)paren
id|vfree
c_func
(paren
id|p
)paren
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
id|r
suffix:semicolon
)brace
DECL|variable|sn_hwperf_fops
r_static
r_struct
id|file_operations
id|sn_hwperf_fops
op_assign
(brace
dot
id|ioctl
op_assign
id|sn_hwperf_ioctl
comma
)brace
suffix:semicolon
DECL|variable|sn_hwperf_dev
r_static
r_struct
id|miscdevice
id|sn_hwperf_dev
op_assign
(brace
id|MISC_DYNAMIC_MINOR
comma
l_string|&quot;sn_hwperf&quot;
comma
op_amp
id|sn_hwperf_fops
)brace
suffix:semicolon
DECL|function|sn_hwperf_init
r_static
r_int
id|sn_hwperf_init
c_func
(paren
r_void
)paren
(brace
id|u64
id|v
suffix:semicolon
r_int
id|salr
suffix:semicolon
r_int
id|e
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* single threaded, once-only initialization */
id|down
c_func
(paren
op_amp
id|sn_hwperf_init_mutex
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sn_hwperf_salheap
)paren
(brace
id|up
c_func
(paren
op_amp
id|sn_hwperf_init_mutex
)paren
suffix:semicolon
r_return
id|e
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * The PROM code needs a fixed reference node. For convenience the&n;&t; * same node as the console I/O is used.&n;&t; */
id|sn_hwperf_master_nasid
op_assign
(paren
id|nasid_t
)paren
id|ia64_sn_get_console_nasid
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Request the needed size and install the PROM scratch area.&n;&t; * The PROM keeps various tracking bits in this memory area.&n;&t; */
id|salr
op_assign
id|ia64_sn_hwperf_op
c_func
(paren
id|sn_hwperf_master_nasid
comma
(paren
id|u64
)paren
id|SN_HWPERF_GET_HEAPSIZE
comma
l_int|0
comma
(paren
id|u64
)paren
r_sizeof
(paren
id|u64
)paren
comma
(paren
id|u64
)paren
op_amp
id|v
comma
l_int|0
comma
l_int|0
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|salr
op_ne
id|SN_HWPERF_OP_OK
)paren
(brace
id|e
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|sn_hwperf_salheap
op_assign
id|vmalloc
c_func
(paren
id|v
)paren
)paren
op_eq
l_int|NULL
)paren
(brace
id|e
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|salr
op_assign
id|ia64_sn_hwperf_op
c_func
(paren
id|sn_hwperf_master_nasid
comma
id|SN_HWPERF_INSTALL_HEAP
comma
l_int|0
comma
id|v
comma
(paren
id|u64
)paren
id|sn_hwperf_salheap
comma
l_int|0
comma
l_int|0
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|salr
op_ne
id|SN_HWPERF_OP_OK
)paren
(brace
id|e
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|salr
op_assign
id|ia64_sn_hwperf_op
c_func
(paren
id|sn_hwperf_master_nasid
comma
id|SN_HWPERF_OBJECT_COUNT
comma
l_int|0
comma
r_sizeof
(paren
id|u64
)paren
comma
(paren
id|u64
)paren
op_amp
id|v
comma
l_int|0
comma
l_int|0
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|salr
op_ne
id|SN_HWPERF_OP_OK
)paren
(brace
id|e
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|sn_hwperf_obj_cnt
op_assign
(paren
r_int
)paren
id|v
suffix:semicolon
id|out
suffix:colon
r_if
c_cond
(paren
id|e
OL
l_int|0
op_logical_and
id|sn_hwperf_salheap
)paren
(brace
id|vfree
c_func
(paren
id|sn_hwperf_salheap
)paren
suffix:semicolon
id|sn_hwperf_salheap
op_assign
l_int|NULL
suffix:semicolon
id|sn_hwperf_obj_cnt
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|e
)paren
(brace
multiline_comment|/*&n;&t;&t; * Register a dynamic misc device for ioctl. Platforms&n;&t;&t; * supporting hotplug will create /dev/sn_hwperf, else&n;&t;&t; * user can to look up the minor number in /proc/misc.&n;&t;&t; */
r_if
c_cond
(paren
(paren
id|e
op_assign
id|misc_register
c_func
(paren
op_amp
id|sn_hwperf_dev
)paren
)paren
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;sn_hwperf_init: misc register &quot;
l_string|&quot;for &bslash;&quot;sn_hwperf&bslash;&quot; failed, err %d&bslash;n&quot;
comma
id|e
)paren
suffix:semicolon
)brace
)brace
id|up
c_func
(paren
op_amp
id|sn_hwperf_init_mutex
)paren
suffix:semicolon
r_return
id|e
suffix:semicolon
)brace
DECL|function|sn_topology_open
r_int
id|sn_topology_open
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
)paren
(brace
r_int
id|e
suffix:semicolon
r_struct
id|seq_file
op_star
id|seq
suffix:semicolon
r_struct
id|sn_hwperf_object_info
op_star
id|objbuf
suffix:semicolon
r_int
id|nobj
suffix:semicolon
r_if
c_cond
(paren
(paren
id|e
op_assign
id|sn_hwperf_enum_objects
c_func
(paren
op_amp
id|nobj
comma
op_amp
id|objbuf
)paren
)paren
op_eq
l_int|0
)paren
(brace
id|e
op_assign
id|seq_open
c_func
(paren
id|file
comma
op_amp
id|sn_topology_seq_ops
)paren
suffix:semicolon
id|seq
op_assign
id|file-&gt;private_data
suffix:semicolon
id|seq
op_member_access_from_pointer
r_private
op_assign
id|objbuf
suffix:semicolon
)brace
r_return
id|e
suffix:semicolon
)brace
DECL|function|sn_topology_release
r_int
id|sn_topology_release
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
)paren
(brace
r_struct
id|seq_file
op_star
id|seq
op_assign
id|file-&gt;private_data
suffix:semicolon
r_if
c_cond
(paren
id|seq
op_member_access_from_pointer
r_private
)paren
id|vfree
c_func
(paren
id|seq
op_member_access_from_pointer
r_private
)paren
suffix:semicolon
r_return
id|seq_release
c_func
(paren
id|inode
comma
id|file
)paren
suffix:semicolon
)brace
eof
