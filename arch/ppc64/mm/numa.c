multiline_comment|/*&n; * pSeries NUMA support&n; *&n; * Copyright (C) 2002 Anton Blanchard &lt;anton@au.ibm.com&gt;, IBM&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/mmzone.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;asm/lmb.h&gt;
macro_line|#if 1
DECL|macro|dbg
mdefine_line|#define dbg(args...) udbg_printf(args)
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
r_int
id|numa_memory_lookup_table
(braket
id|MAX_MEMORY
op_rshift
id|MEMORY_INCREMENT_SHIFT
)braket
op_assign
(brace
(braket
l_int|0
dot
dot
dot
(paren
(paren
id|MAX_MEMORY
op_rshift
id|MEMORY_INCREMENT_SHIFT
)paren
op_minus
l_int|1
)paren
)braket
op_assign
id|ARRAY_INITIALISER
)brace
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
op_star
id|cpu_associativity
suffix:semicolon
r_int
op_star
id|memory_associativity
suffix:semicolon
r_int
id|depth
suffix:semicolon
r_int
id|max_domain
op_assign
l_int|0
suffix:semicolon
id|cpu
op_assign
id|of_find_node_by_type
c_func
(paren
l_int|NULL
comma
l_string|&quot;cpu&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cpu
)paren
r_goto
id|err
suffix:semicolon
id|memory
op_assign
id|of_find_node_by_type
c_func
(paren
l_int|NULL
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|memory
)paren
r_goto
id|err
suffix:semicolon
id|cpu_associativity
op_assign
(paren
r_int
op_star
)paren
id|get_property
c_func
(paren
id|cpu
comma
l_string|&quot;ibm,associativity&quot;
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cpu_associativity
)paren
r_goto
id|err
suffix:semicolon
id|memory_associativity
op_assign
(paren
r_int
op_star
)paren
id|get_property
c_func
(paren
id|memory
comma
l_string|&quot;ibm,associativity&quot;
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|memory_associativity
)paren
r_goto
id|err
suffix:semicolon
multiline_comment|/* find common depth */
r_if
c_cond
(paren
id|cpu_associativity
(braket
l_int|0
)braket
OL
id|memory_associativity
(braket
l_int|0
)braket
)paren
id|depth
op_assign
id|cpu_associativity
(braket
l_int|0
)braket
suffix:semicolon
r_else
id|depth
op_assign
id|memory_associativity
(braket
l_int|0
)braket
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|cpu
suffix:semicolon
id|cpu
op_assign
id|of_find_node_by_type
c_func
(paren
id|cpu
comma
l_string|&quot;cpu&quot;
)paren
)paren
(brace
r_int
op_star
id|tmp
suffix:semicolon
r_int
id|cpu_nr
comma
id|numa_domain
suffix:semicolon
id|tmp
op_assign
(paren
r_int
op_star
)paren
id|get_property
c_func
(paren
id|cpu
comma
l_string|&quot;reg&quot;
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tmp
)paren
r_continue
suffix:semicolon
id|cpu_nr
op_assign
op_star
id|tmp
suffix:semicolon
id|tmp
op_assign
(paren
r_int
op_star
)paren
id|get_property
c_func
(paren
id|cpu
comma
l_string|&quot;ibm,associativity&quot;
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tmp
)paren
r_continue
suffix:semicolon
id|numa_domain
op_assign
id|tmp
(braket
id|depth
)braket
suffix:semicolon
multiline_comment|/* FIXME */
r_if
c_cond
(paren
id|numa_domain
op_eq
l_int|0xffff
)paren
(brace
id|dbg
c_func
(paren
l_string|&quot;cpu %d has no numa doman&bslash;n&quot;
comma
id|cpu_nr
)paren
suffix:semicolon
id|numa_domain
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|numa_domain
op_ge
id|MAX_NUMNODES
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
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
id|cpu_nr
comma
id|numa_domain
)paren
suffix:semicolon
)brace
r_for
c_loop
(paren
suffix:semicolon
id|memory
suffix:semicolon
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
(brace
r_int
r_int
op_star
id|tmp1
comma
op_star
id|tmp2
suffix:semicolon
r_int
r_int
id|i
suffix:semicolon
r_int
r_int
id|start
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|size
op_assign
l_int|0
suffix:semicolon
r_int
id|numa_domain
suffix:semicolon
r_int
id|ranges
suffix:semicolon
id|tmp1
op_assign
(paren
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
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tmp1
)paren
r_continue
suffix:semicolon
id|ranges
op_assign
id|memory-&gt;n_addrs
suffix:semicolon
id|new_range
suffix:colon
id|i
op_assign
id|prom_n_size_cells
c_func
(paren
id|memory
)paren
suffix:semicolon
r_while
c_loop
(paren
id|i
op_decrement
)paren
(brace
id|start
op_assign
(paren
id|start
op_lshift
l_int|32
)paren
op_or
op_star
id|tmp1
suffix:semicolon
id|tmp1
op_increment
suffix:semicolon
)brace
id|i
op_assign
id|prom_n_size_cells
c_func
(paren
id|memory
)paren
suffix:semicolon
r_while
c_loop
(paren
id|i
op_decrement
)paren
(brace
id|size
op_assign
(paren
id|size
op_lshift
l_int|32
)paren
op_or
op_star
id|tmp1
suffix:semicolon
id|tmp1
op_increment
suffix:semicolon
)brace
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
r_if
c_cond
(paren
(paren
id|start
op_plus
id|size
)paren
OG
id|MAX_MEMORY
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|tmp2
op_assign
(paren
r_int
op_star
)paren
id|get_property
c_func
(paren
id|memory
comma
l_string|&quot;ibm,associativity&quot;
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tmp2
)paren
r_continue
suffix:semicolon
id|numa_domain
op_assign
id|tmp2
(braket
id|depth
)braket
suffix:semicolon
multiline_comment|/* FIXME */
r_if
c_cond
(paren
id|numa_domain
op_eq
l_int|0xffff
)paren
(brace
id|dbg
c_func
(paren
l_string|&quot;memory has no numa doman&bslash;n&quot;
)paren
suffix:semicolon
id|numa_domain
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|numa_domain
op_ge
id|MAX_NUMNODES
)paren
id|BUG
c_func
(paren
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
id|err
suffix:colon
id|of_node_put
c_func
(paren
id|cpu
)paren
suffix:semicolon
id|of_node_put
c_func
(paren
id|memory
)paren
suffix:semicolon
r_return
op_minus
l_int|1
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
