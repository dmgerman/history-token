multiline_comment|/*&n; * Written by Kanoj Sarcar (kanoj@sgi.com) Aug 99&n; *&n; * PowerPC64 port:&n; * Copyright (C) 2002 Anton Blanchard, IBM Corp.&n; */
macro_line|#ifndef _ASM_MMZONE_H_
DECL|macro|_ASM_MMZONE_H_
mdefine_line|#define _ASM_MMZONE_H_
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_DISCONTIGMEM
r_extern
r_struct
id|pglist_data
op_star
id|node_data
(braket
)braket
suffix:semicolon
multiline_comment|/*&n; * Following are specific to this numa platform.&n; */
r_extern
r_int
id|numa_node_exists
(braket
)braket
suffix:semicolon
r_extern
r_int
id|numa_cpu_lookup_table
(braket
)braket
suffix:semicolon
r_extern
r_int
id|numa_memory_lookup_table
(braket
)braket
suffix:semicolon
DECL|macro|MAX_NUMNODES
mdefine_line|#define MAX_NUMNODES 16
DECL|macro|MAX_MEMORY
mdefine_line|#define MAX_MEMORY (1UL &lt;&lt; 41)
multiline_comment|/* 256MB regions */
DECL|macro|MEMORY_INCREMENT_SHIFT
mdefine_line|#define MEMORY_INCREMENT_SHIFT 28
DECL|macro|MEMORY_INCREMENT
mdefine_line|#define MEMORY_INCREMENT (1UL &lt;&lt; MEMORY_INCREMENT_SHIFT)
DECL|macro|DEBUG_NUMA
macro_line|#undef DEBUG_NUMA
DECL|function|pa_to_nid
r_static
r_inline
r_int
id|pa_to_nid
c_func
(paren
r_int
r_int
id|pa
)paren
(brace
r_int
id|nid
suffix:semicolon
id|nid
op_assign
id|numa_memory_lookup_table
(braket
id|pa
op_rshift
id|MEMORY_INCREMENT_SHIFT
)braket
suffix:semicolon
macro_line|#ifdef DEBUG_NUMA
multiline_comment|/* the physical address passed in is not in the map for the system */
r_if
c_cond
(paren
id|nid
op_eq
op_minus
l_int|1
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;bad address: %lx&bslash;n&quot;
comma
id|pa
)paren
suffix:semicolon
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#endif
r_return
id|nid
suffix:semicolon
)brace
DECL|macro|pfn_to_nid
mdefine_line|#define pfn_to_nid(pfn)&t;&t;pa_to_nid((pfn) &lt;&lt; PAGE_SHIFT)
DECL|macro|node_startnr
mdefine_line|#define node_startnr(nid)&t;(node_data[nid]-&gt;node_start_mapnr)
DECL|macro|node_size
mdefine_line|#define node_size(nid)&t;&t;(node_data[nid]-&gt;node_size)
DECL|macro|node_localnr
mdefine_line|#define node_localnr(pfn, nid)&t;((pfn) - node_data[nid]-&gt;node_start_pfn)
macro_line|#ifdef CONFIG_NUMA
DECL|function|__cpu_to_node
r_static
r_inline
r_int
id|__cpu_to_node
c_func
(paren
r_int
id|cpu
)paren
(brace
r_int
id|node
suffix:semicolon
id|node
op_assign
id|numa_cpu_lookup_table
(braket
id|cpu
)braket
suffix:semicolon
macro_line|#ifdef DEBUG_NUMA
r_if
c_cond
(paren
id|node
op_eq
op_minus
l_int|1
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
r_return
id|node
suffix:semicolon
)brace
DECL|macro|numa_node_id
mdefine_line|#define numa_node_id()&t;__cpu_to_node(smp_processor_id())
macro_line|#endif /* CONFIG_NUMA */
multiline_comment|/*&n; * Following are macros that each numa implmentation must define.&n; */
multiline_comment|/*&n; * Given a kernel address, find the home node of the underlying memory.&n; */
DECL|macro|kvaddr_to_nid
mdefine_line|#define kvaddr_to_nid(kaddr)&t;pa_to_nid(__pa(kaddr))
multiline_comment|/*&n; * Return a pointer to the node data for node n.&n; */
DECL|macro|NODE_DATA
mdefine_line|#define NODE_DATA(nid)&t;&t;(node_data[nid])
DECL|macro|node_mem_map
mdefine_line|#define node_mem_map(nid)&t;(NODE_DATA(nid)-&gt;node_mem_map)
DECL|macro|node_start_pfn
mdefine_line|#define node_start_pfn(nid)&t;(NODE_DATA(nid)-&gt;node_start_pfn)
DECL|macro|local_mapnr
mdefine_line|#define local_mapnr(kvaddr) &bslash;&n;&t;( (__pa(kvaddr) &gt;&gt; PAGE_SHIFT) - node_start_pfn(kvaddr_to_nid(kvaddr)) 
macro_line|#if 0
multiline_comment|/* XXX fix - Anton */
mdefine_line|#define kern_addr_valid(kaddr)&t;test_bit(local_mapnr(kaddr), &bslash;&n;&t;&t; NODE_DATA(kvaddr_to_nid(kaddr))-&gt;valid_addr_bitmap)
macro_line|#endif
multiline_comment|/* Written this way to avoid evaluating arguments twice */
DECL|macro|discontigmem_pfn_to_page
mdefine_line|#define discontigmem_pfn_to_page(pfn) &bslash;&n;({ &bslash;&n;&t;unsigned long __tmp = pfn; &bslash;&n;&t;(node_mem_map(pfn_to_nid(__tmp)) + &bslash;&n;&t; node_localnr(__tmp, pfn_to_nid(__tmp))); &bslash;&n;})
DECL|macro|discontigmem_page_to_pfn
mdefine_line|#define discontigmem_page_to_pfn(p)&t;&bslash;&n;({ &bslash;&n;&t;struct page *__tmp = p; &bslash;&n;&t;(((__tmp) - page_zone(__tmp)-&gt;zone_mem_map) + &bslash;&n;&t; page_zone(__tmp)-&gt;zone_start_pfn); &bslash;&n;})
macro_line|#endif /* CONFIG_DISCONTIGMEM */
macro_line|#endif /* _ASM_MMZONE_H_ */
eof
