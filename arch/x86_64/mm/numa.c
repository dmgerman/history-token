multiline_comment|/* &n; * Generic VM initialization for x86-64 NUMA setups.&n; * Copyright 2002,2003 Andi Kleen, SuSE Labs.&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;linux/mmzone.h&gt;
macro_line|#include &lt;linux/ctype.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/nodemask.h&gt;
macro_line|#include &lt;asm/e820.h&gt;
macro_line|#include &lt;asm/proto.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &lt;asm/numa.h&gt;
macro_line|#ifndef Dprintk
DECL|macro|Dprintk
mdefine_line|#define Dprintk(x...)
macro_line|#endif
DECL|variable|node_data
r_struct
id|pglist_data
op_star
id|node_data
(braket
id|MAXNODE
)braket
suffix:semicolon
DECL|variable|plat_node_bdata
id|bootmem_data_t
id|plat_node_bdata
(braket
id|MAX_NUMNODES
)braket
suffix:semicolon
DECL|variable|memnode_shift
r_int
id|memnode_shift
suffix:semicolon
DECL|variable|memnodemap
id|u8
id|memnodemap
(braket
id|NODEMAPSIZE
)braket
suffix:semicolon
DECL|variable|cpu_to_node
r_int
r_char
id|cpu_to_node
(braket
id|NR_CPUS
)braket
suffix:semicolon
DECL|variable|node_to_cpumask
id|cpumask_t
id|node_to_cpumask
(braket
id|MAXNODE
)braket
suffix:semicolon
DECL|variable|__initdata
r_static
r_int
id|numa_off
id|__initdata
suffix:semicolon
DECL|variable|nodes_present
r_int
r_int
id|nodes_present
suffix:semicolon
DECL|function|compute_hash_shift
r_int
id|__init
id|compute_hash_shift
c_func
(paren
r_struct
id|node
op_star
id|nodes
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
id|shift
op_assign
l_int|24
suffix:semicolon
id|u64
id|addr
suffix:semicolon
multiline_comment|/* When in doubt use brute force. */
r_while
c_loop
(paren
id|shift
OL
l_int|48
)paren
(brace
id|memset
c_func
(paren
id|memnodemap
comma
l_int|0xff
comma
r_sizeof
(paren
op_star
id|memnodemap
)paren
op_star
id|NODEMAPSIZE
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
id|numnodes
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|nodes
(braket
id|i
)braket
dot
id|start
op_eq
id|nodes
(braket
id|i
)braket
dot
id|end
)paren
r_continue
suffix:semicolon
r_for
c_loop
(paren
id|addr
op_assign
id|nodes
(braket
id|i
)braket
dot
id|start
suffix:semicolon
id|addr
OL
id|nodes
(braket
id|i
)braket
dot
id|end
suffix:semicolon
id|addr
op_add_assign
(paren
l_int|1UL
op_lshift
id|shift
)paren
)paren
(brace
r_if
c_cond
(paren
id|memnodemap
(braket
id|addr
op_rshift
id|shift
)braket
op_ne
l_int|0xff
op_logical_and
id|memnodemap
(braket
id|addr
op_rshift
id|shift
)braket
op_ne
id|i
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;node %d shift %d addr %Lx conflict %d&bslash;n&quot;
comma
id|i
comma
id|shift
comma
id|addr
comma
id|memnodemap
(braket
id|addr
op_rshift
id|shift
)braket
)paren
suffix:semicolon
r_goto
id|next
suffix:semicolon
)brace
id|memnodemap
(braket
id|addr
op_rshift
id|shift
)braket
op_assign
id|i
suffix:semicolon
)brace
)brace
r_return
id|shift
suffix:semicolon
id|next
suffix:colon
id|shift
op_increment
suffix:semicolon
)brace
id|memset
c_func
(paren
id|memnodemap
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|memnodemap
)paren
op_star
id|NODEMAPSIZE
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Initialize bootmem allocator for a node */
DECL|function|setup_node_bootmem
r_void
id|__init
id|setup_node_bootmem
c_func
(paren
r_int
id|nodeid
comma
r_int
r_int
id|start
comma
r_int
r_int
id|end
)paren
(brace
r_int
r_int
id|start_pfn
comma
id|end_pfn
comma
id|bootmap_pages
comma
id|bootmap_size
comma
id|bootmap_start
suffix:semicolon
r_int
r_int
id|nodedata_phys
suffix:semicolon
r_const
r_int
id|pgdat_size
op_assign
id|round_up
c_func
(paren
r_sizeof
(paren
id|pg_data_t
)paren
comma
id|PAGE_SIZE
)paren
suffix:semicolon
id|start
op_assign
id|round_up
c_func
(paren
id|start
comma
id|ZONE_ALIGN
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Bootmem setup node %d %016lx-%016lx&bslash;n&quot;
comma
id|nodeid
comma
id|start
comma
id|end
)paren
suffix:semicolon
id|start_pfn
op_assign
id|start
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|end_pfn
op_assign
id|end
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|nodedata_phys
op_assign
id|find_e820_area
c_func
(paren
id|start
comma
id|end
comma
id|pgdat_size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nodedata_phys
op_eq
op_minus
l_int|1L
)paren
id|panic
c_func
(paren
l_string|&quot;Cannot find memory pgdat in node %d&bslash;n&quot;
comma
id|nodeid
)paren
suffix:semicolon
id|Dprintk
c_func
(paren
l_string|&quot;nodedata_phys %lx&bslash;n&quot;
comma
id|nodedata_phys
)paren
suffix:semicolon
id|node_data
(braket
id|nodeid
)braket
op_assign
id|phys_to_virt
c_func
(paren
id|nodedata_phys
)paren
suffix:semicolon
id|memset
c_func
(paren
id|NODE_DATA
c_func
(paren
id|nodeid
)paren
comma
l_int|0
comma
r_sizeof
(paren
id|pg_data_t
)paren
)paren
suffix:semicolon
id|NODE_DATA
c_func
(paren
id|nodeid
)paren
op_member_access_from_pointer
id|bdata
op_assign
op_amp
id|plat_node_bdata
(braket
id|nodeid
)braket
suffix:semicolon
id|NODE_DATA
c_func
(paren
id|nodeid
)paren
op_member_access_from_pointer
id|node_start_pfn
op_assign
id|start_pfn
suffix:semicolon
id|NODE_DATA
c_func
(paren
id|nodeid
)paren
op_member_access_from_pointer
id|node_spanned_pages
op_assign
id|end_pfn
op_minus
id|start_pfn
suffix:semicolon
multiline_comment|/* Find a place for the bootmem map */
id|bootmap_pages
op_assign
id|bootmem_bootmap_pages
c_func
(paren
id|end_pfn
op_minus
id|start_pfn
)paren
suffix:semicolon
id|bootmap_start
op_assign
id|round_up
c_func
(paren
id|nodedata_phys
op_plus
id|pgdat_size
comma
id|PAGE_SIZE
)paren
suffix:semicolon
id|bootmap_start
op_assign
id|find_e820_area
c_func
(paren
id|bootmap_start
comma
id|end
comma
id|bootmap_pages
op_lshift
id|PAGE_SHIFT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bootmap_start
op_eq
op_minus
l_int|1L
)paren
id|panic
c_func
(paren
l_string|&quot;Not enough continuous space for bootmap on node %d&quot;
comma
id|nodeid
)paren
suffix:semicolon
id|Dprintk
c_func
(paren
l_string|&quot;bootmap start %lu pages %lu&bslash;n&quot;
comma
id|bootmap_start
comma
id|bootmap_pages
)paren
suffix:semicolon
id|bootmap_size
op_assign
id|init_bootmem_node
c_func
(paren
id|NODE_DATA
c_func
(paren
id|nodeid
)paren
comma
id|bootmap_start
op_rshift
id|PAGE_SHIFT
comma
id|start_pfn
comma
id|end_pfn
)paren
suffix:semicolon
id|e820_bootmem_free
c_func
(paren
id|NODE_DATA
c_func
(paren
id|nodeid
)paren
comma
id|start
comma
id|end
)paren
suffix:semicolon
id|reserve_bootmem_node
c_func
(paren
id|NODE_DATA
c_func
(paren
id|nodeid
)paren
comma
id|nodedata_phys
comma
id|pgdat_size
)paren
suffix:semicolon
id|reserve_bootmem_node
c_func
(paren
id|NODE_DATA
c_func
(paren
id|nodeid
)paren
comma
id|bootmap_start
comma
id|bootmap_pages
op_lshift
id|PAGE_SHIFT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nodeid
op_plus
l_int|1
OG
id|numnodes
)paren
id|numnodes
op_assign
id|nodeid
op_plus
l_int|1
suffix:semicolon
id|node_set_online
c_func
(paren
id|nodeid
)paren
suffix:semicolon
)brace
multiline_comment|/* Initialize final allocator for a zone */
DECL|function|setup_node_zones
r_void
id|__init
id|setup_node_zones
c_func
(paren
r_int
id|nodeid
)paren
(brace
r_int
r_int
id|start_pfn
comma
id|end_pfn
suffix:semicolon
r_int
r_int
id|zones
(braket
id|MAX_NR_ZONES
)braket
suffix:semicolon
r_int
r_int
id|dma_end_pfn
suffix:semicolon
id|memset
c_func
(paren
id|zones
comma
l_int|0
comma
r_sizeof
(paren
r_int
r_int
)paren
op_star
id|MAX_NR_ZONES
)paren
suffix:semicolon
id|start_pfn
op_assign
id|node_start_pfn
c_func
(paren
id|nodeid
)paren
suffix:semicolon
id|end_pfn
op_assign
id|node_end_pfn
c_func
(paren
id|nodeid
)paren
suffix:semicolon
id|Dprintk
c_func
(paren
id|KERN_INFO
l_string|&quot;setting up node %d %lx-%lx&bslash;n&quot;
comma
id|nodeid
comma
id|start_pfn
comma
id|end_pfn
)paren
suffix:semicolon
multiline_comment|/* All nodes &gt; 0 have a zero length zone DMA */
id|dma_end_pfn
op_assign
id|__pa
c_func
(paren
id|MAX_DMA_ADDRESS
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
r_if
c_cond
(paren
id|start_pfn
OL
id|dma_end_pfn
)paren
(brace
id|zones
(braket
id|ZONE_DMA
)braket
op_assign
id|dma_end_pfn
op_minus
id|start_pfn
suffix:semicolon
id|zones
(braket
id|ZONE_NORMAL
)braket
op_assign
id|end_pfn
op_minus
id|dma_end_pfn
suffix:semicolon
)brace
r_else
(brace
id|zones
(braket
id|ZONE_NORMAL
)braket
op_assign
id|end_pfn
op_minus
id|start_pfn
suffix:semicolon
)brace
id|free_area_init_node
c_func
(paren
id|nodeid
comma
id|NODE_DATA
c_func
(paren
id|nodeid
)paren
comma
id|zones
comma
id|start_pfn
comma
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|function|numa_init_array
r_void
id|__init
id|numa_init_array
c_func
(paren
r_void
)paren
(brace
r_int
id|rr
comma
id|i
suffix:semicolon
multiline_comment|/* There are unfortunately some poorly designed mainboards around&n;&t;   that only connect memory to a single CPU. This breaks the 1:1 cpu-&gt;node&n;&t;   mapping. To avoid this fill in the mapping for all possible&n;&t;   CPUs, as the number of CPUs is not known yet. &n;&t;   We round robin the existing nodes. */
id|rr
op_assign
l_int|0
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
id|MAXNODE
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|node_online
c_func
(paren
id|i
)paren
)paren
r_continue
suffix:semicolon
id|rr
op_assign
id|next_node
c_func
(paren
id|rr
comma
id|node_online_map
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rr
op_eq
id|MAX_NUMNODES
)paren
id|rr
op_assign
id|first_node
c_func
(paren
id|node_online_map
)paren
suffix:semicolon
id|node_data
(braket
id|i
)braket
op_assign
id|node_data
(braket
id|rr
)braket
suffix:semicolon
id|cpu_to_node
(braket
id|i
)braket
op_assign
id|rr
suffix:semicolon
id|rr
op_increment
suffix:semicolon
)brace
id|set_bit
c_func
(paren
l_int|0
comma
op_amp
id|node_to_cpumask
(braket
id|cpu_to_node
c_func
(paren
l_int|0
)paren
)braket
)paren
suffix:semicolon
)brace
DECL|variable|__initdata
r_int
id|numa_fake
id|__initdata
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Numa emulation */
DECL|function|numa_emulation
r_static
r_int
id|numa_emulation
c_func
(paren
r_int
r_int
id|start_pfn
comma
r_int
r_int
id|end_pfn
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|node
id|nodes
(braket
id|MAXNODE
)braket
suffix:semicolon
r_int
r_int
id|sz
op_assign
(paren
(paren
id|end_pfn
op_minus
id|start_pfn
)paren
op_lshift
id|PAGE_SHIFT
)paren
op_div
id|numa_fake
suffix:semicolon
multiline_comment|/* Kludge needed for the hash function */
r_if
c_cond
(paren
id|hweight64
c_func
(paren
id|sz
)paren
OG
l_int|1
)paren
(brace
r_int
r_int
id|x
op_assign
l_int|1
suffix:semicolon
r_while
c_loop
(paren
(paren
id|x
op_lshift
l_int|1
)paren
OL
id|sz
)paren
id|x
op_lshift_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|x
OL
id|sz
op_div
l_int|2
)paren
id|printk
c_func
(paren
l_string|&quot;Numa emulation unbalanced. Complain to maintainer&bslash;n&quot;
)paren
suffix:semicolon
id|sz
op_assign
id|x
suffix:semicolon
)brace
id|memset
c_func
(paren
op_amp
id|nodes
comma
l_int|0
comma
r_sizeof
(paren
id|nodes
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
id|numa_fake
suffix:semicolon
id|i
op_increment
)paren
(brace
id|nodes
(braket
id|i
)braket
dot
id|start
op_assign
(paren
id|start_pfn
op_lshift
id|PAGE_SHIFT
)paren
op_plus
id|i
op_star
id|sz
suffix:semicolon
r_if
c_cond
(paren
id|i
op_eq
id|numa_fake
op_minus
l_int|1
)paren
id|sz
op_assign
(paren
id|end_pfn
op_lshift
id|PAGE_SHIFT
)paren
op_minus
id|nodes
(braket
id|i
)braket
dot
id|start
suffix:semicolon
id|nodes
(braket
id|i
)braket
dot
id|end
op_assign
id|nodes
(braket
id|i
)braket
dot
id|start
op_plus
id|sz
suffix:semicolon
r_if
c_cond
(paren
id|i
op_ne
id|numa_fake
op_minus
l_int|1
)paren
id|nodes
(braket
id|i
)braket
dot
id|end
op_decrement
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Faking node %d at %016Lx-%016Lx (%LuMB)&bslash;n&quot;
comma
id|i
comma
id|nodes
(braket
id|i
)braket
dot
id|start
comma
id|nodes
(braket
id|i
)braket
dot
id|end
comma
(paren
id|nodes
(braket
id|i
)braket
dot
id|end
op_minus
id|nodes
(braket
id|i
)braket
dot
id|start
)paren
op_rshift
l_int|20
)paren
suffix:semicolon
)brace
id|numnodes
op_assign
id|numa_fake
suffix:semicolon
id|memnode_shift
op_assign
id|compute_hash_shift
c_func
(paren
id|nodes
)paren
suffix:semicolon
r_if
c_cond
(paren
id|memnode_shift
OL
l_int|0
)paren
(brace
id|memnode_shift
op_assign
l_int|0
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;No NUMA hash function found. Emulation disabled.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
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
id|numa_fake
suffix:semicolon
id|i
op_increment
)paren
id|setup_node_bootmem
c_func
(paren
id|i
comma
id|nodes
(braket
id|i
)braket
dot
id|start
comma
id|nodes
(braket
id|i
)braket
dot
id|end
)paren
suffix:semicolon
id|numa_init_array
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|numa_initmem_init
r_void
id|__init
id|numa_initmem_init
c_func
(paren
r_int
r_int
id|start_pfn
comma
r_int
r_int
id|end_pfn
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|numa_fake
op_logical_and
op_logical_neg
id|numa_emulation
c_func
(paren
id|start_pfn
comma
id|end_pfn
)paren
)paren
r_return
suffix:semicolon
macro_line|#ifdef CONFIG_K8_NUMA
r_if
c_cond
(paren
op_logical_neg
id|numa_off
op_logical_and
op_logical_neg
id|k8_scan_nodes
c_func
(paren
id|start_pfn
op_lshift
id|PAGE_SHIFT
comma
id|end_pfn
op_lshift
id|PAGE_SHIFT
)paren
)paren
r_return
suffix:semicolon
macro_line|#endif
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s&bslash;n&quot;
comma
id|numa_off
ques
c_cond
l_string|&quot;NUMA turned off&quot;
suffix:colon
l_string|&quot;No NUMA configuration found&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Faking a node at %016lx-%016lx&bslash;n&quot;
comma
id|start_pfn
op_lshift
id|PAGE_SHIFT
comma
id|end_pfn
op_lshift
id|PAGE_SHIFT
)paren
suffix:semicolon
multiline_comment|/* setup dummy node covering all memory */
id|memnode_shift
op_assign
l_int|63
suffix:semicolon
id|memnodemap
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
id|numnodes
op_assign
l_int|1
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
id|cpu_to_node
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
id|node_to_cpumask
(braket
l_int|0
)braket
op_assign
id|cpumask_of_cpu
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|setup_node_bootmem
c_func
(paren
l_int|0
comma
id|start_pfn
op_lshift
id|PAGE_SHIFT
comma
id|end_pfn
op_lshift
id|PAGE_SHIFT
)paren
suffix:semicolon
)brace
DECL|function|numa_add_cpu
id|__init
r_void
id|numa_add_cpu
c_func
(paren
r_int
id|cpu
)paren
(brace
multiline_comment|/* BP is initialized elsewhere */
r_if
c_cond
(paren
id|cpu
)paren
id|set_bit
c_func
(paren
id|cpu
comma
op_amp
id|node_to_cpumask
(braket
id|cpu_to_node
c_func
(paren
id|cpu
)paren
)braket
)paren
suffix:semicolon
)brace
DECL|function|numa_free_all_bootmem
r_int
r_int
id|__init
id|numa_free_all_bootmem
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
r_int
id|pages
op_assign
l_int|0
suffix:semicolon
id|for_all_nodes
c_func
(paren
id|i
)paren
(brace
id|pages
op_add_assign
id|free_all_bootmem_node
c_func
(paren
id|NODE_DATA
c_func
(paren
id|i
)paren
)paren
suffix:semicolon
)brace
r_return
id|pages
suffix:semicolon
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
id|i
suffix:semicolon
id|for_all_nodes
c_func
(paren
id|i
)paren
(brace
id|setup_node_zones
c_func
(paren
id|i
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* [numa=off] */
DECL|function|numa_setup
id|__init
r_int
id|numa_setup
c_func
(paren
r_char
op_star
id|opt
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|opt
comma
l_string|&quot;off&quot;
)paren
)paren
id|numa_off
op_assign
l_int|1
suffix:semicolon
macro_line|#ifdef CONFIG_NUMA_EMU
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|opt
comma
l_string|&quot;fake=&quot;
comma
l_int|5
)paren
)paren
(brace
id|numa_fake
op_assign
id|simple_strtoul
c_func
(paren
id|opt
op_plus
l_int|5
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
suffix:semicolon
r_if
c_cond
(paren
id|numa_fake
op_ge
id|MAX_NUMNODES
)paren
id|numa_fake
op_assign
id|MAX_NUMNODES
suffix:semicolon
)brace
macro_line|#endif
r_return
l_int|1
suffix:semicolon
)brace
DECL|variable|cpu_to_node
id|EXPORT_SYMBOL
c_func
(paren
id|cpu_to_node
)paren
suffix:semicolon
DECL|variable|node_to_cpumask
id|EXPORT_SYMBOL
c_func
(paren
id|node_to_cpumask
)paren
suffix:semicolon
DECL|variable|memnode_shift
id|EXPORT_SYMBOL
c_func
(paren
id|memnode_shift
)paren
suffix:semicolon
DECL|variable|memnodemap
id|EXPORT_SYMBOL
c_func
(paren
id|memnodemap
)paren
suffix:semicolon
DECL|variable|node_data
id|EXPORT_SYMBOL
c_func
(paren
id|node_data
)paren
suffix:semicolon
eof
