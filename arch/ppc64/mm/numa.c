multiline_comment|/*&n; * pSeries NUMA support&n; *&n; * Copyright (C) 2002 Anton Blanchard &lt;anton@au.ibm.com&gt;, IBM&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/mmzone.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;asm/lmb.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;asm/abs_addr.h&gt;
macro_line|#if 1
DECL|macro|dbg
mdefine_line|#define dbg(args...) printk(KERN_INFO args)
macro_line|#else
DECL|macro|dbg
mdefine_line|#define dbg(args...)
macro_line|#endif
macro_line|#ifdef DEBUG_NUMA
DECL|macro|ARRAY_INITIALISER
mdefine_line|#define ARRAY_INITIALISER -1
macro_line|#else
DECL|macro|ARRAY_INITIALISER
mdefine_line|#define ARRAY_INITIALISER 0
macro_line|#endif
DECL|variable|numa_cpu_lookup_table
r_int
id|numa_cpu_lookup_table
(braket
id|NR_CPUS
)braket
op_assign
(brace
(braket
l_int|0
dot
dot
dot
(paren
id|NR_CPUS
op_minus
l_int|1
)paren
)braket
op_assign
id|ARRAY_INITIALISER
)brace
suffix:semicolon
DECL|variable|numa_memory_lookup_table
r_char
op_star
id|numa_memory_lookup_table
suffix:semicolon
DECL|variable|numa_cpumask_lookup_table
id|cpumask_t
id|numa_cpumask_lookup_table
(braket
id|MAX_NUMNODES
)braket
suffix:semicolon
DECL|variable|nr_cpus_in_node
r_int
id|nr_cpus_in_node
(braket
id|MAX_NUMNODES
)braket
op_assign
(brace
(braket
l_int|0
dot
dot
dot
(paren
id|MAX_NUMNODES
op_minus
l_int|1
)paren
)braket
op_assign
l_int|0
)brace
suffix:semicolon
DECL|variable|node_data
r_struct
id|pglist_data
id|node_data
(braket
id|MAX_NUMNODES
)braket
suffix:semicolon
DECL|variable|plat_node_bdata
id|bootmem_data_t
id|plat_node_bdata
(braket
id|MAX_NUMNODES
)braket
suffix:semicolon
DECL|variable|node0_io_hole_size
r_static
r_int
r_int
id|node0_io_hole_size
suffix:semicolon
DECL|variable|node_data
id|EXPORT_SYMBOL
c_func
(paren
id|node_data
)paren
suffix:semicolon
DECL|variable|numa_cpu_lookup_table
id|EXPORT_SYMBOL
c_func
(paren
id|numa_cpu_lookup_table
)paren
suffix:semicolon
DECL|variable|numa_memory_lookup_table
id|EXPORT_SYMBOL
c_func
(paren
id|numa_memory_lookup_table
)paren
suffix:semicolon
DECL|variable|numa_cpumask_lookup_table
id|EXPORT_SYMBOL
c_func
(paren
id|numa_cpumask_lookup_table
)paren
suffix:semicolon
DECL|variable|nr_cpus_in_node
id|EXPORT_SYMBOL
c_func
(paren
id|nr_cpus_in_node
)paren
suffix:semicolon
DECL|function|map_cpu_to_node
r_static
r_inline
r_void
id|map_cpu_to_node
c_func
(paren
r_int
id|cpu
comma
r_int
id|node
)paren
(brace
id|dbg
c_func
(paren
l_string|&quot;cpu %d maps to domain %d&bslash;n&quot;
comma
id|cpu
comma
id|node
)paren
suffix:semicolon
id|numa_cpu_lookup_table
(braket
id|cpu
)braket
op_assign
id|node
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|cpu_isset
c_func
(paren
id|cpu
comma
id|numa_cpumask_lookup_table
(braket
id|node
)braket
)paren
)paren
)paren
(brace
id|cpu_set
c_func
(paren
id|cpu
comma
id|numa_cpumask_lookup_table
(braket
id|node
)braket
)paren
suffix:semicolon
id|nr_cpus_in_node
(braket
id|node
)braket
op_increment
suffix:semicolon
)brace
)brace
DECL|function|find_cpu_node
r_static
r_struct
id|device_node
op_star
id|__init
id|find_cpu_node
c_func
(paren
r_int
r_int
id|cpu
)paren
(brace
r_int
r_int
id|hw_cpuid
op_assign
id|get_hard_smp_processor_id
c_func
(paren
id|cpu
)paren
suffix:semicolon
r_struct
id|device_node
op_star
id|cpu_node
op_assign
l_int|NULL
suffix:semicolon
r_int
r_int
op_star
id|interrupt_server
comma
op_star
id|reg
suffix:semicolon
r_int
id|len
suffix:semicolon
r_while
c_loop
(paren
(paren
id|cpu_node
op_assign
id|of_find_node_by_type
c_func
(paren
id|cpu_node
comma
l_string|&quot;cpu&quot;
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
multiline_comment|/* Try interrupt server first */
id|interrupt_server
op_assign
(paren
r_int
r_int
op_star
)paren
id|get_property
c_func
(paren
id|cpu_node
comma
l_string|&quot;ibm,ppc-interrupt-server#s&quot;
comma
op_amp
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|interrupt_server
op_logical_and
(paren
id|len
OG
l_int|0
)paren
)paren
(brace
r_while
c_loop
(paren
id|len
op_decrement
)paren
(brace
r_if
c_cond
(paren
id|interrupt_server
(braket
id|len
op_minus
l_int|1
)braket
op_eq
id|hw_cpuid
)paren
r_return
id|cpu_node
suffix:semicolon
)brace
)brace
r_else
(brace
id|reg
op_assign
(paren
r_int
r_int
op_star
)paren
id|get_property
c_func
(paren
id|cpu_node
comma
l_string|&quot;reg&quot;
comma
op_amp
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|reg
op_logical_and
(paren
id|len
OG
l_int|0
)paren
op_logical_and
(paren
id|reg
(braket
l_int|0
)braket
op_eq
id|hw_cpuid
)paren
)paren
r_return
id|cpu_node
suffix:semicolon
)brace
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* must hold reference to node during call */
DECL|function|of_get_associativity
r_static
r_int
op_star
id|of_get_associativity
c_func
(paren
r_struct
id|device_node
op_star
id|dev
)paren
(brace
r_int
r_int
op_star
id|result
suffix:semicolon
r_int
id|len
suffix:semicolon
id|result
op_assign
(paren
r_int
r_int
op_star
)paren
id|get_property
c_func
(paren
id|dev
comma
l_string|&quot;ibm,associativity&quot;
comma
op_amp
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
op_le
l_int|0
)paren
r_return
l_int|NULL
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
DECL|function|of_node_numa_domain
r_static
r_int
id|of_node_numa_domain
c_func
(paren
r_struct
id|device_node
op_star
id|device
comma
r_int
id|depth
)paren
(brace
r_int
id|numa_domain
suffix:semicolon
r_int
r_int
op_star
id|tmp
suffix:semicolon
id|tmp
op_assign
id|of_get_associativity
c_func
(paren
id|device
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_logical_and
(paren
id|tmp
(braket
l_int|0
)braket
op_ge
id|depth
)paren
)paren
(brace
id|numa_domain
op_assign
id|tmp
(braket
id|depth
)braket
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;WARNING: no NUMA information for &quot;
l_string|&quot;%s&bslash;n&quot;
comma
id|device-&gt;full_name
)paren
suffix:semicolon
id|numa_domain
op_assign
l_int|0
suffix:semicolon
)brace
r_return
id|numa_domain
suffix:semicolon
)brace
multiline_comment|/*&n; * In theory, the &quot;ibm,associativity&quot; property may contain multiple&n; * associativity lists because a resource may be multiply connected&n; * into the machine.  This resource then has different associativity&n; * characteristics relative to its multiple connections.  We ignore&n; * this for now.  We also assume that all cpu and memory sets have&n; * their distances represented at a common level.  This won&squot;t be&n; * true for heirarchical NUMA.&n; *&n; * In any case the ibm,associativity-reference-points should give&n; * the correct depth for a normal NUMA system.&n; *&n; * - Dave Hansen &lt;haveblue@us.ibm.com&gt;&n; */
DECL|function|find_min_common_depth
r_static
r_int
id|find_min_common_depth
c_func
(paren
r_void
)paren
(brace
r_int
id|depth
suffix:semicolon
r_int
r_int
op_star
id|ref_points
suffix:semicolon
r_struct
id|device_node
op_star
id|rtas_root
suffix:semicolon
r_int
r_int
id|len
suffix:semicolon
id|rtas_root
op_assign
id|of_find_node_by_path
c_func
(paren
l_string|&quot;/rtas&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rtas_root
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;WARNING: %s() could not find rtas root&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * this property is 2 32-bit integers, each representing a level of&n;&t; * depth in the associativity nodes.  The first is for an SMP&n;&t; * configuration (should be all 0&squot;s) and the second is for a normal&n;&t; * NUMA configuration.&n;&t; */
id|ref_points
op_assign
(paren
r_int
r_int
op_star
)paren
id|get_property
c_func
(paren
id|rtas_root
comma
l_string|&quot;ibm,associativity-reference-points&quot;
comma
op_amp
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|len
op_ge
l_int|1
)paren
op_logical_and
id|ref_points
)paren
(brace
id|depth
op_assign
id|ref_points
(braket
l_int|1
)braket
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;WARNING: could not find NUMA &quot;
l_string|&quot;associativity reference point&bslash;n&quot;
)paren
suffix:semicolon
id|depth
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
id|of_node_put
c_func
(paren
id|rtas_root
)paren
suffix:semicolon
r_return
id|depth
suffix:semicolon
)brace
DECL|function|read_cell_ul
r_static
r_int
r_int
id|read_cell_ul
c_func
(paren
r_struct
id|device_node
op_star
id|device
comma
r_int
r_int
op_star
op_star
id|buf
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
r_int
id|result
op_assign
l_int|0
suffix:semicolon
id|i
op_assign
id|prom_n_size_cells
c_func
(paren
id|device
)paren
suffix:semicolon
multiline_comment|/* bug on i&gt;2 ?? */
r_while
c_loop
(paren
id|i
op_decrement
)paren
(brace
id|result
op_assign
(paren
id|result
op_lshift
l_int|32
)paren
op_or
op_star
op_star
id|buf
suffix:semicolon
(paren
op_star
id|buf
)paren
op_increment
suffix:semicolon
)brace
r_return
id|result
suffix:semicolon
)brace
DECL|function|parse_numa_properties
r_static
r_int
id|__init
id|parse_numa_properties
c_func
(paren
r_void
)paren
(brace
r_struct
id|device_node
op_star
id|cpu
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|device_node
op_star
id|memory
op_assign
l_int|NULL
suffix:semicolon
r_int
id|depth
suffix:semicolon
r_int
id|max_domain
op_assign
l_int|0
suffix:semicolon
r_int
id|entries
op_assign
id|lmb_end_of_DRAM
c_func
(paren
)paren
op_rshift
id|MEMORY_INCREMENT_SHIFT
suffix:semicolon
r_int
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|strstr
c_func
(paren
id|saved_command_line
comma
l_string|&quot;numa=off&quot;
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;NUMA disabled by user&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|numa_memory_lookup_table
op_assign
(paren
r_char
op_star
)paren
id|abs_to_virt
c_func
(paren
id|lmb_alloc
c_func
(paren
id|entries
op_star
r_sizeof
(paren
r_char
)paren
comma
l_int|1
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
id|entries
suffix:semicolon
id|i
op_increment
)paren
id|numa_memory_lookup_table
(braket
id|i
)braket
op_assign
id|ARRAY_INITIALISER
suffix:semicolon
id|depth
op_assign
id|find_min_common_depth
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;NUMA associativity depth for CPU/Memory: %d&bslash;n&quot;
comma
id|depth
)paren
suffix:semicolon
r_if
c_cond
(paren
id|depth
OL
l_int|0
)paren
r_return
id|depth
suffix:semicolon
id|for_each_cpu
c_func
(paren
id|i
)paren
(brace
r_int
id|numa_domain
suffix:semicolon
id|cpu
op_assign
id|find_cpu_node
c_func
(paren
id|i
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cpu
)paren
(brace
id|numa_domain
op_assign
id|of_node_numa_domain
c_func
(paren
id|cpu
comma
id|depth
)paren
suffix:semicolon
id|of_node_put
c_func
(paren
id|cpu
)paren
suffix:semicolon
r_if
c_cond
(paren
id|numa_domain
op_ge
id|MAX_NUMNODES
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; &t; * POWER4 LPAR uses 0xffff as invalid node,&n;&t;&t;&t;&t; * dont warn in this case.&n;&t;&t;&t; &t; */
r_if
c_cond
(paren
id|numa_domain
op_ne
l_int|0xffff
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;WARNING: cpu %ld &quot;
l_string|&quot;maps to invalid NUMA node %d&bslash;n&quot;
comma
id|i
comma
id|numa_domain
)paren
suffix:semicolon
id|numa_domain
op_assign
l_int|0
suffix:semicolon
)brace
)brace
r_else
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;WARNING: no NUMA information for &quot;
l_string|&quot;cpu %ld&bslash;n&quot;
comma
id|i
)paren
suffix:semicolon
id|numa_domain
op_assign
l_int|0
suffix:semicolon
)brace
id|node_set_online
c_func
(paren
id|numa_domain
)paren
suffix:semicolon
r_if
c_cond
(paren
id|max_domain
OL
id|numa_domain
)paren
id|max_domain
op_assign
id|numa_domain
suffix:semicolon
id|map_cpu_to_node
c_func
(paren
id|i
comma
id|numa_domain
)paren
suffix:semicolon
)brace
id|memory
op_assign
l_int|NULL
suffix:semicolon
r_while
c_loop
(paren
(paren
id|memory
op_assign
id|of_find_node_by_type
c_func
(paren
id|memory
comma
l_string|&quot;memory&quot;
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
r_int
r_int
id|start
suffix:semicolon
r_int
r_int
id|size
suffix:semicolon
r_int
id|numa_domain
suffix:semicolon
r_int
id|ranges
suffix:semicolon
r_int
r_int
op_star
id|memcell_buf
suffix:semicolon
r_int
r_int
id|len
suffix:semicolon
id|memcell_buf
op_assign
(paren
r_int
r_int
op_star
)paren
id|get_property
c_func
(paren
id|memory
comma
l_string|&quot;reg&quot;
comma
op_amp
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|memcell_buf
op_logical_or
id|len
op_le
l_int|0
)paren
r_continue
suffix:semicolon
id|ranges
op_assign
id|memory-&gt;n_addrs
suffix:semicolon
id|new_range
suffix:colon
multiline_comment|/* these are order-sensitive, and modify the buffer pointer */
id|start
op_assign
id|read_cell_ul
c_func
(paren
id|memory
comma
op_amp
id|memcell_buf
)paren
suffix:semicolon
id|size
op_assign
id|read_cell_ul
c_func
(paren
id|memory
comma
op_amp
id|memcell_buf
)paren
suffix:semicolon
id|start
op_assign
id|_ALIGN_DOWN
c_func
(paren
id|start
comma
id|MEMORY_INCREMENT
)paren
suffix:semicolon
id|size
op_assign
id|_ALIGN_UP
c_func
(paren
id|size
comma
id|MEMORY_INCREMENT
)paren
suffix:semicolon
id|numa_domain
op_assign
id|of_node_numa_domain
c_func
(paren
id|memory
comma
id|depth
)paren
suffix:semicolon
r_if
c_cond
(paren
id|numa_domain
op_ge
id|MAX_NUMNODES
)paren
(brace
r_if
c_cond
(paren
id|numa_domain
op_ne
l_int|0xffff
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;WARNING: memory at %lx maps &quot;
l_string|&quot;to invalid NUMA node %d&bslash;n&quot;
comma
id|start
comma
id|numa_domain
)paren
suffix:semicolon
id|numa_domain
op_assign
l_int|0
suffix:semicolon
)brace
id|node_set_online
c_func
(paren
id|numa_domain
)paren
suffix:semicolon
r_if
c_cond
(paren
id|max_domain
OL
id|numa_domain
)paren
id|max_domain
op_assign
id|numa_domain
suffix:semicolon
multiline_comment|/* &n;&t;&t; * For backwards compatibility, OF splits the first node&n;&t;&t; * into two regions (the first being 0-4GB). Check for&n;&t;&t; * this simple case and complain if there is a gap in&n;&t;&t; * memory&n;&t;&t; */
r_if
c_cond
(paren
id|node_data
(braket
id|numa_domain
)braket
dot
id|node_spanned_pages
)paren
(brace
r_int
r_int
id|shouldstart
op_assign
id|node_data
(braket
id|numa_domain
)braket
dot
id|node_start_pfn
op_plus
id|node_data
(braket
id|numa_domain
)braket
dot
id|node_spanned_pages
suffix:semicolon
r_if
c_cond
(paren
id|shouldstart
op_ne
(paren
id|start
op_div
id|PAGE_SIZE
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Hole in node, disabling &quot;
l_string|&quot;region start %lx length %lx&bslash;n&quot;
comma
id|start
comma
id|size
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|node_data
(braket
id|numa_domain
)braket
dot
id|node_spanned_pages
op_add_assign
id|size
op_div
id|PAGE_SIZE
suffix:semicolon
)brace
r_else
(brace
id|node_data
(braket
id|numa_domain
)braket
dot
id|node_start_pfn
op_assign
id|start
op_div
id|PAGE_SIZE
suffix:semicolon
id|node_data
(braket
id|numa_domain
)braket
dot
id|node_spanned_pages
op_assign
id|size
op_div
id|PAGE_SIZE
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
id|start
suffix:semicolon
id|i
OL
(paren
id|start
op_plus
id|size
)paren
suffix:semicolon
id|i
op_add_assign
id|MEMORY_INCREMENT
)paren
id|numa_memory_lookup_table
(braket
id|i
op_rshift
id|MEMORY_INCREMENT_SHIFT
)braket
op_assign
id|numa_domain
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;memory region %lx to %lx maps to domain %d&bslash;n&quot;
comma
id|start
comma
id|start
op_plus
id|size
comma
id|numa_domain
)paren
suffix:semicolon
id|ranges
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|ranges
)paren
r_goto
id|new_range
suffix:semicolon
)brace
id|numnodes
op_assign
id|max_domain
op_plus
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|setup_nonnuma
r_static
r_void
id|__init
id|setup_nonnuma
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|top_of_ram
op_assign
id|lmb_end_of_DRAM
c_func
(paren
)paren
suffix:semicolon
r_int
r_int
id|total_ram
op_assign
id|lmb_phys_mem_size
c_func
(paren
)paren
suffix:semicolon
r_int
r_int
id|i
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Top of RAM: 0x%lx, Total RAM: 0x%lx&bslash;n&quot;
comma
id|top_of_ram
comma
id|total_ram
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Memory hole size: %ldMB&bslash;n&quot;
comma
(paren
id|top_of_ram
op_minus
id|total_ram
)paren
op_rshift
l_int|20
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|numa_memory_lookup_table
)paren
(brace
r_int
id|entries
op_assign
id|top_of_ram
op_rshift
id|MEMORY_INCREMENT_SHIFT
suffix:semicolon
id|numa_memory_lookup_table
op_assign
(paren
r_char
op_star
)paren
id|abs_to_virt
c_func
(paren
id|lmb_alloc
c_func
(paren
id|entries
op_star
r_sizeof
(paren
r_char
)paren
comma
l_int|1
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
id|entries
suffix:semicolon
id|i
op_increment
)paren
id|numa_memory_lookup_table
(braket
id|i
)braket
op_assign
id|ARRAY_INITIALISER
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|NR_CPUS
suffix:semicolon
id|i
op_increment
)paren
id|map_cpu_to_node
c_func
(paren
id|i
comma
l_int|0
)paren
suffix:semicolon
id|node_set_online
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|node_data
(braket
l_int|0
)braket
dot
id|node_start_pfn
op_assign
l_int|0
suffix:semicolon
id|node_data
(braket
l_int|0
)braket
dot
id|node_spanned_pages
op_assign
id|lmb_end_of_DRAM
c_func
(paren
)paren
op_div
id|PAGE_SIZE
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
id|top_of_ram
suffix:semicolon
id|i
op_add_assign
id|MEMORY_INCREMENT
)paren
id|numa_memory_lookup_table
(braket
id|i
op_rshift
id|MEMORY_INCREMENT_SHIFT
)braket
op_assign
l_int|0
suffix:semicolon
id|node0_io_hole_size
op_assign
id|top_of_ram
op_minus
id|total_ram
suffix:semicolon
)brace
DECL|function|do_init_bootmem
r_void
id|__init
id|do_init_bootmem
c_func
(paren
r_void
)paren
(brace
r_int
id|nid
suffix:semicolon
id|min_low_pfn
op_assign
l_int|0
suffix:semicolon
id|max_low_pfn
op_assign
id|lmb_end_of_DRAM
c_func
(paren
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
r_if
c_cond
(paren
id|parse_numa_properties
c_func
(paren
)paren
)paren
id|setup_nonnuma
c_func
(paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|nid
op_assign
l_int|0
suffix:semicolon
id|nid
OL
id|numnodes
suffix:semicolon
id|nid
op_increment
)paren
(brace
r_int
r_int
id|start_paddr
comma
id|end_paddr
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
r_int
id|bootmem_paddr
suffix:semicolon
r_int
r_int
id|bootmap_pages
suffix:semicolon
r_if
c_cond
(paren
id|node_data
(braket
id|nid
)braket
dot
id|node_spanned_pages
op_eq
l_int|0
)paren
r_continue
suffix:semicolon
id|start_paddr
op_assign
id|node_data
(braket
id|nid
)braket
dot
id|node_start_pfn
op_star
id|PAGE_SIZE
suffix:semicolon
id|end_paddr
op_assign
id|start_paddr
op_plus
(paren
id|node_data
(braket
id|nid
)braket
dot
id|node_spanned_pages
op_star
id|PAGE_SIZE
)paren
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;node %d&bslash;n&quot;
comma
id|nid
)paren
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;start_paddr = %lx&bslash;n&quot;
comma
id|start_paddr
)paren
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;end_paddr = %lx&bslash;n&quot;
comma
id|end_paddr
)paren
suffix:semicolon
id|NODE_DATA
c_func
(paren
id|nid
)paren
op_member_access_from_pointer
id|bdata
op_assign
op_amp
id|plat_node_bdata
(braket
id|nid
)braket
suffix:semicolon
id|bootmap_pages
op_assign
id|bootmem_bootmap_pages
c_func
(paren
(paren
id|end_paddr
op_minus
id|start_paddr
)paren
op_rshift
id|PAGE_SHIFT
)paren
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;bootmap_pages = %lx&bslash;n&quot;
comma
id|bootmap_pages
)paren
suffix:semicolon
id|bootmem_paddr
op_assign
id|lmb_alloc_base
c_func
(paren
id|bootmap_pages
op_lshift
id|PAGE_SHIFT
comma
id|PAGE_SIZE
comma
id|end_paddr
)paren
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;bootmap_paddr = %lx&bslash;n&quot;
comma
id|bootmem_paddr
)paren
suffix:semicolon
id|init_bootmem_node
c_func
(paren
id|NODE_DATA
c_func
(paren
id|nid
)paren
comma
id|bootmem_paddr
op_rshift
id|PAGE_SHIFT
comma
id|start_paddr
op_rshift
id|PAGE_SHIFT
comma
id|end_paddr
op_rshift
id|PAGE_SHIFT
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
id|lmb.memory.cnt
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
r_int
id|physbase
comma
id|size
suffix:semicolon
id|physbase
op_assign
id|lmb.memory.region
(braket
id|i
)braket
dot
id|physbase
suffix:semicolon
id|size
op_assign
id|lmb.memory.region
(braket
id|i
)braket
dot
id|size
suffix:semicolon
r_if
c_cond
(paren
id|physbase
template_param
id|start_paddr
)paren
(brace
multiline_comment|/* overlaps */
r_if
c_cond
(paren
id|physbase
OL
id|start_paddr
)paren
(brace
id|size
op_sub_assign
id|start_paddr
op_minus
id|physbase
suffix:semicolon
id|physbase
op_assign
id|start_paddr
suffix:semicolon
)brace
r_if
c_cond
(paren
id|size
OG
id|end_paddr
op_minus
id|physbase
)paren
id|size
op_assign
id|end_paddr
op_minus
id|physbase
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;free_bootmem %lx %lx&bslash;n&quot;
comma
id|physbase
comma
id|size
)paren
suffix:semicolon
id|free_bootmem_node
c_func
(paren
id|NODE_DATA
c_func
(paren
id|nid
)paren
comma
id|physbase
comma
id|size
)paren
suffix:semicolon
)brace
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|lmb.reserved.cnt
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
r_int
id|physbase
op_assign
id|lmb.reserved.region
(braket
id|i
)braket
dot
id|physbase
suffix:semicolon
r_int
r_int
id|size
op_assign
id|lmb.reserved.region
(braket
id|i
)braket
dot
id|size
suffix:semicolon
r_if
c_cond
(paren
id|physbase
template_param
id|start_paddr
)paren
(brace
multiline_comment|/* overlaps */
r_if
c_cond
(paren
id|physbase
OL
id|start_paddr
)paren
(brace
id|size
op_sub_assign
id|start_paddr
op_minus
id|physbase
suffix:semicolon
id|physbase
op_assign
id|start_paddr
suffix:semicolon
)brace
r_if
c_cond
(paren
id|size
OG
id|end_paddr
op_minus
id|physbase
)paren
id|size
op_assign
id|end_paddr
op_minus
id|physbase
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;reserve_bootmem %lx %lx&bslash;n&quot;
comma
id|physbase
comma
id|size
)paren
suffix:semicolon
id|reserve_bootmem_node
c_func
(paren
id|NODE_DATA
c_func
(paren
id|nid
)paren
comma
id|physbase
comma
id|size
)paren
suffix:semicolon
)brace
)brace
)brace
)brace
DECL|function|paging_init
r_void
id|__init
id|paging_init
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|zones_size
(braket
id|MAX_NR_ZONES
)braket
suffix:semicolon
r_int
r_int
id|zholes_size
(braket
id|MAX_NR_ZONES
)braket
suffix:semicolon
r_struct
id|page
op_star
id|node_mem_map
suffix:semicolon
r_int
id|nid
suffix:semicolon
id|memset
c_func
(paren
id|zones_size
comma
l_int|0
comma
r_sizeof
(paren
id|zones_size
)paren
)paren
suffix:semicolon
id|memset
c_func
(paren
id|zholes_size
comma
l_int|0
comma
r_sizeof
(paren
id|zholes_size
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|nid
op_assign
l_int|0
suffix:semicolon
id|nid
OL
id|numnodes
suffix:semicolon
id|nid
op_increment
)paren
(brace
r_int
r_int
id|start_pfn
suffix:semicolon
r_int
r_int
id|end_pfn
suffix:semicolon
id|start_pfn
op_assign
id|plat_node_bdata
(braket
id|nid
)braket
dot
id|node_boot_start
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|end_pfn
op_assign
id|plat_node_bdata
(braket
id|nid
)braket
dot
id|node_low_pfn
suffix:semicolon
id|zones_size
(braket
id|ZONE_DMA
)braket
op_assign
id|end_pfn
op_minus
id|start_pfn
suffix:semicolon
id|zholes_size
(braket
id|ZONE_DMA
)braket
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|nid
op_eq
l_int|0
)paren
id|zholes_size
(braket
id|ZONE_DMA
)braket
op_assign
id|node0_io_hole_size
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;free_area_init node %d %lx %lx (hole: %lx)&bslash;n&quot;
comma
id|nid
comma
id|zones_size
(braket
id|ZONE_DMA
)braket
comma
id|start_pfn
comma
id|zholes_size
(braket
id|ZONE_DMA
)braket
)paren
suffix:semicolon
multiline_comment|/* &n;&t;&t; * Give this empty node a dummy struct page to avoid&n;&t;&t; * us from trying to allocate a node local mem_map&n;&t;&t; * in free_area_init_node (which will fail).&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|node_data
(braket
id|nid
)braket
dot
id|node_spanned_pages
)paren
id|node_mem_map
op_assign
id|alloc_bootmem
c_func
(paren
r_sizeof
(paren
r_struct
id|page
)paren
)paren
suffix:semicolon
r_else
id|node_mem_map
op_assign
l_int|NULL
suffix:semicolon
id|free_area_init_node
c_func
(paren
id|nid
comma
id|NODE_DATA
c_func
(paren
id|nid
)paren
comma
id|node_mem_map
comma
id|zones_size
comma
id|start_pfn
comma
id|zholes_size
)paren
suffix:semicolon
)brace
)brace
eof
