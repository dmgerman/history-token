multiline_comment|/*&n; * pSeries NUMA support&n; *&n; * Copyright (C) 2002 Anton Blanchard &lt;anton@au.ibm.com&gt;, IBM&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/mmzone.h&gt;
macro_line|#include &lt;asm/lmb.h&gt;
macro_line|#if 1
DECL|macro|dbg
mdefine_line|#define dbg(args...) udbg_printf(args)
macro_line|#else
DECL|macro|dbg
mdefine_line|#define dbg(args...)
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
op_minus
l_int|1
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
op_minus
l_int|1
)brace
suffix:semicolon
DECL|variable|numa_cpumask_lookup_table
r_int
r_int
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
id|numa_cpumask_lookup_table
(braket
id|node
)braket
op_amp
l_int|1UL
op_lshift
id|cpu
)paren
)paren
(brace
id|numa_cpumask_lookup_table
(braket
id|node
)braket
op_or_assign
l_int|1UL
op_lshift
id|cpu
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
suffix:semicolon
r_struct
id|device_node
op_star
id|memory
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
id|find_type_devices
c_func
(paren
l_string|&quot;cpu&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cpu
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|memory
op_assign
id|find_type_devices
c_func
(paren
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|memory
)paren
r_return
op_minus
l_int|1
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
r_return
op_minus
l_int|1
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
r_return
op_minus
l_int|1
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
id|cpu
op_assign
id|find_type_devices
c_func
(paren
l_string|&quot;cpu&quot;
)paren
suffix:semicolon
id|cpu
suffix:semicolon
id|cpu
op_assign
id|cpu-&gt;next
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
id|memory
op_assign
id|find_type_devices
c_func
(paren
l_string|&quot;memory&quot;
)paren
suffix:semicolon
id|memory
suffix:semicolon
id|memory
op_assign
id|memory-&gt;next
)paren
(brace
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
id|node_size
op_assign
id|size
op_div
id|PAGE_SIZE
suffix:semicolon
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
r_void
id|setup_nonnuma
c_func
(paren
r_void
)paren
(brace
r_int
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
id|node_size
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
id|lmb_end_of_DRAM
c_func
(paren
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
l_int|0
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
id|node_size
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
id|node_size
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
r_int
r_int
id|type
op_assign
id|lmb.memory.region
(braket
id|i
)braket
dot
id|type
suffix:semicolon
r_if
c_cond
(paren
id|type
op_ne
id|LMB_MEMORY_AREA
)paren
r_continue
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
id|start_paddr
)paren
id|size
op_assign
id|end_paddr
op_minus
id|start_paddr
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
id|start_paddr
)paren
id|size
op_assign
id|end_paddr
op_minus
id|start_paddr
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
id|i
comma
id|nid
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
OL
id|MAX_NR_ZONES
suffix:semicolon
id|i
op_increment
)paren
id|zones_size
(braket
id|i
)braket
op_assign
l_int|0
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
r_if
c_cond
(paren
id|node_data
(braket
id|nid
)braket
dot
id|node_size
op_eq
l_int|0
)paren
r_continue
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
id|dbg
c_func
(paren
l_string|&quot;free_area_init node %d %lx %lx&bslash;n&quot;
comma
id|nid
comma
id|zones_size
(braket
id|ZONE_DMA
)braket
comma
id|start_pfn
)paren
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
l_int|NULL
comma
id|zones_size
comma
id|start_pfn
comma
l_int|NULL
)paren
suffix:semicolon
)brace
)brace
eof
