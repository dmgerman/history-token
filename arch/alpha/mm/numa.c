multiline_comment|/*&n; *  linux/arch/alpha/mm/numa.c&n; *&n; *  DISCONTIGMEM NUMA alpha support.&n; *&n; *  Copyright (C) 2001 Andrea Arcangeli &lt;andrea@suse.de&gt; SuSE&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;linux/swap.h&gt;
macro_line|#ifdef CONFIG_BLK_DEV_INITRD
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#endif
macro_line|#include &lt;asm/hwrpb.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
DECL|variable|plat_node_data
id|plat_pg_data_t
op_star
id|plat_node_data
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
DECL|macro|DEBUG_DISCONTIG
macro_line|#undef DEBUG_DISCONTIG
macro_line|#ifdef DEBUG_DISCONTIG
DECL|macro|DBGDCONT
mdefine_line|#define DBGDCONT(args...) printk(args)
macro_line|#else
DECL|macro|DBGDCONT
mdefine_line|#define DBGDCONT(args...)
macro_line|#endif
DECL|macro|PFN_UP
mdefine_line|#define PFN_UP(x)       (((x) + PAGE_SIZE-1) &gt;&gt; PAGE_SHIFT)
DECL|macro|PFN_DOWN
mdefine_line|#define PFN_DOWN(x)     ((x) &gt;&gt; PAGE_SHIFT)
DECL|macro|PFN_PHYS
mdefine_line|#define PFN_PHYS(x)     ((x) &lt;&lt; PAGE_SHIFT)
DECL|macro|for_each_mem_cluster
mdefine_line|#define for_each_mem_cluster(memdesc, cluster, i)&t;&t;&bslash;&n;&t;for ((cluster) = (memdesc)-&gt;cluster, (i) = 0;&t;&t;&bslash;&n;&t;     (i) &lt; (memdesc)-&gt;numclusters; (i)++, (cluster)++)
DECL|function|show_mem_layout
r_static
r_void
id|__init
id|show_mem_layout
c_func
(paren
r_void
)paren
(brace
r_struct
id|memclust_struct
op_star
id|cluster
suffix:semicolon
r_struct
id|memdesc_struct
op_star
id|memdesc
suffix:semicolon
r_int
id|i
suffix:semicolon
multiline_comment|/* Find free clusters, and init and free the bootmem accordingly.  */
id|memdesc
op_assign
(paren
r_struct
id|memdesc_struct
op_star
)paren
(paren
id|hwrpb-&gt;mddt_offset
op_plus
(paren
r_int
r_int
)paren
id|hwrpb
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Raw memory layout:&bslash;n&quot;
)paren
suffix:semicolon
id|for_each_mem_cluster
c_func
(paren
id|memdesc
comma
id|cluster
comma
id|i
)paren
(brace
id|printk
c_func
(paren
l_string|&quot; memcluster %2d, usage %1lx, start %8lu, end %8lu&bslash;n&quot;
comma
id|i
comma
id|cluster-&gt;usage
comma
id|cluster-&gt;start_pfn
comma
id|cluster-&gt;start_pfn
op_plus
id|cluster-&gt;numpages
)paren
suffix:semicolon
)brace
)brace
r_static
r_void
id|__init
DECL|function|setup_memory_node
id|setup_memory_node
c_func
(paren
r_int
id|nid
comma
r_void
op_star
id|kernel_end
)paren
(brace
r_extern
r_int
r_int
id|mem_size_limit
suffix:semicolon
r_struct
id|memclust_struct
op_star
id|cluster
suffix:semicolon
r_struct
id|memdesc_struct
op_star
id|memdesc
suffix:semicolon
r_int
r_int
id|start_kernel_pfn
comma
id|end_kernel_pfn
suffix:semicolon
r_int
r_int
id|bootmap_size
comma
id|bootmap_pages
comma
id|bootmap_start
suffix:semicolon
r_int
r_int
id|start
comma
id|end
suffix:semicolon
r_int
r_int
id|node_pfn_start
comma
id|node_pfn_end
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
r_int
id|node_datasz
op_assign
id|PFN_UP
c_func
(paren
r_sizeof
(paren
id|plat_pg_data_t
)paren
)paren
suffix:semicolon
r_int
id|show_init
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Find the bounds of current node */
id|node_pfn_start
op_assign
(paren
id|nid
op_star
id|NODE_MAX_MEM_SIZE
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|node_pfn_end
op_assign
id|node_pfn_start
op_plus
(paren
id|NODE_MAX_MEM_SIZE
op_rshift
id|PAGE_SHIFT
)paren
suffix:semicolon
multiline_comment|/* Find free clusters, and init and free the bootmem accordingly.  */
id|memdesc
op_assign
(paren
r_struct
id|memdesc_struct
op_star
)paren
(paren
id|hwrpb-&gt;mddt_offset
op_plus
(paren
r_int
r_int
)paren
id|hwrpb
)paren
suffix:semicolon
multiline_comment|/* find the bounds of this node (min_low_pfn/max_low_pfn) */
id|min_low_pfn
op_assign
op_complement
l_int|0UL
suffix:semicolon
id|for_each_mem_cluster
c_func
(paren
id|memdesc
comma
id|cluster
comma
id|i
)paren
(brace
multiline_comment|/* Bit 0 is console/PALcode reserved.  Bit 1 is&n;&t;&t;   non-volatile memory -- we might want to mark&n;&t;&t;   this for later.  */
r_if
c_cond
(paren
id|cluster-&gt;usage
op_amp
l_int|3
)paren
r_continue
suffix:semicolon
id|start
op_assign
id|cluster-&gt;start_pfn
suffix:semicolon
id|end
op_assign
id|start
op_plus
id|cluster-&gt;numpages
suffix:semicolon
r_if
c_cond
(paren
id|start
op_ge
id|node_pfn_end
op_logical_or
id|end
op_le
id|node_pfn_start
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|show_init
)paren
(brace
id|show_init
op_assign
l_int|1
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Initialing bootmem allocator on Node ID %d&bslash;n&quot;
comma
id|nid
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot; memcluster %2d, usage %1lx, start %8lu, end %8lu&bslash;n&quot;
comma
id|i
comma
id|cluster-&gt;usage
comma
id|cluster-&gt;start_pfn
comma
id|cluster-&gt;start_pfn
op_plus
id|cluster-&gt;numpages
)paren
suffix:semicolon
r_if
c_cond
(paren
id|start
OL
id|node_pfn_start
)paren
id|start
op_assign
id|node_pfn_start
suffix:semicolon
r_if
c_cond
(paren
id|end
OG
id|node_pfn_end
)paren
id|end
op_assign
id|node_pfn_end
suffix:semicolon
r_if
c_cond
(paren
id|start
OL
id|min_low_pfn
)paren
id|min_low_pfn
op_assign
id|start
suffix:semicolon
r_if
c_cond
(paren
id|end
OG
id|max_low_pfn
)paren
id|max_low_pfn
op_assign
id|end
suffix:semicolon
)brace
r_if
c_cond
(paren
id|mem_size_limit
op_logical_and
id|max_low_pfn
op_ge
id|mem_size_limit
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;setup: forcing memory size to %ldK (from %ldK).&bslash;n&quot;
comma
id|mem_size_limit
op_lshift
(paren
id|PAGE_SHIFT
op_minus
l_int|10
)paren
comma
id|max_low_pfn
op_lshift
(paren
id|PAGE_SHIFT
op_minus
l_int|10
)paren
)paren
suffix:semicolon
id|max_low_pfn
op_assign
id|mem_size_limit
suffix:semicolon
)brace
r_if
c_cond
(paren
id|min_low_pfn
op_ge
id|max_low_pfn
)paren
r_return
suffix:semicolon
id|num_physpages
op_add_assign
id|max_low_pfn
op_minus
id|min_low_pfn
suffix:semicolon
multiline_comment|/* Cute trick to make sure our local node data is on local memory */
id|PLAT_NODE_DATA
c_func
(paren
id|nid
)paren
op_assign
(paren
id|plat_pg_data_t
op_star
)paren
(paren
id|__va
c_func
(paren
id|min_low_pfn
op_lshift
id|PAGE_SHIFT
)paren
)paren
suffix:semicolon
multiline_comment|/* Quasi-mark the plat_pg_data_t as in-use */
id|min_low_pfn
op_add_assign
id|node_datasz
suffix:semicolon
r_if
c_cond
(paren
id|min_low_pfn
op_ge
id|max_low_pfn
)paren
(brace
id|printk
c_func
(paren
l_string|&quot; not enough mem to reserve PLAT_NODE_DATA&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
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
id|printk
c_func
(paren
l_string|&quot; Detected node memory:   start %8lu, end %8lu&bslash;n&quot;
comma
id|min_low_pfn
comma
id|max_low_pfn
)paren
suffix:semicolon
id|DBGDCONT
c_func
(paren
l_string|&quot; DISCONTIG: plat_node_data[%d]   is at 0x%p&bslash;n&quot;
comma
id|nid
comma
id|PLAT_NODE_DATA
c_func
(paren
id|nid
)paren
)paren
suffix:semicolon
id|DBGDCONT
c_func
(paren
l_string|&quot; DISCONTIG: NODE_DATA(%d)-&gt;bdata is at 0x%p&bslash;n&quot;
comma
id|nid
comma
id|NODE_DATA
c_func
(paren
id|nid
)paren
op_member_access_from_pointer
id|bdata
)paren
suffix:semicolon
multiline_comment|/* Find the bounds of kernel memory.  */
id|start_kernel_pfn
op_assign
id|PFN_DOWN
c_func
(paren
id|KERNEL_START_PHYS
)paren
suffix:semicolon
id|end_kernel_pfn
op_assign
id|PFN_UP
c_func
(paren
id|virt_to_phys
c_func
(paren
id|kernel_end
)paren
)paren
suffix:semicolon
id|bootmap_start
op_assign
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|nid
op_logical_and
(paren
id|max_low_pfn
template_param
id|start_kernel_pfn
)paren
)paren
id|panic
c_func
(paren
l_string|&quot;kernel loaded out of ram&quot;
)paren
suffix:semicolon
multiline_comment|/* Zone start phys-addr must be 2^(MAX_ORDER-1) aligned */
id|min_low_pfn
op_assign
(paren
id|min_low_pfn
op_plus
(paren
(paren
l_int|1UL
op_lshift
(paren
id|MAX_ORDER
op_minus
l_int|1
)paren
)paren
op_minus
l_int|1
)paren
)paren
op_amp
op_complement
(paren
(paren
l_int|1UL
op_lshift
(paren
id|MAX_ORDER
op_minus
l_int|1
)paren
)paren
op_minus
l_int|1
)paren
suffix:semicolon
multiline_comment|/* We need to know how many physically contiguous pages&n;&t;   we&squot;ll need for the bootmap.  */
id|bootmap_pages
op_assign
id|bootmem_bootmap_pages
c_func
(paren
id|max_low_pfn
op_minus
id|min_low_pfn
)paren
suffix:semicolon
multiline_comment|/* Now find a good region where to allocate the bootmap.  */
id|for_each_mem_cluster
c_func
(paren
id|memdesc
comma
id|cluster
comma
id|i
)paren
(brace
r_if
c_cond
(paren
id|cluster-&gt;usage
op_amp
l_int|3
)paren
r_continue
suffix:semicolon
id|start
op_assign
id|cluster-&gt;start_pfn
suffix:semicolon
id|end
op_assign
id|start
op_plus
id|cluster-&gt;numpages
suffix:semicolon
r_if
c_cond
(paren
id|start
op_ge
id|max_low_pfn
op_logical_or
id|end
op_le
id|min_low_pfn
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|end
OG
id|max_low_pfn
)paren
id|end
op_assign
id|max_low_pfn
suffix:semicolon
r_if
c_cond
(paren
id|start
OL
id|min_low_pfn
)paren
id|start
op_assign
id|min_low_pfn
suffix:semicolon
r_if
c_cond
(paren
id|start
OL
id|start_kernel_pfn
)paren
(brace
r_if
c_cond
(paren
id|end
OG
id|end_kernel_pfn
op_logical_and
id|end
op_minus
id|end_kernel_pfn
op_ge
id|bootmap_pages
)paren
(brace
id|bootmap_start
op_assign
id|end_kernel_pfn
suffix:semicolon
r_break
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|end
OG
id|start_kernel_pfn
)paren
id|end
op_assign
id|start_kernel_pfn
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|start
OL
id|end_kernel_pfn
)paren
id|start
op_assign
id|end_kernel_pfn
suffix:semicolon
r_if
c_cond
(paren
id|end
op_minus
id|start
op_ge
id|bootmap_pages
)paren
(brace
id|bootmap_start
op_assign
id|start
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|bootmap_start
op_eq
op_minus
l_int|1
)paren
id|panic
c_func
(paren
l_string|&quot;couldn&squot;t find a contigous place for the bootmap&quot;
)paren
suffix:semicolon
multiline_comment|/* Allocate the bootmap and mark the whole MM as reserved.  */
id|bootmap_size
op_assign
id|init_bootmem_node
c_func
(paren
id|NODE_DATA
c_func
(paren
id|nid
)paren
comma
id|bootmap_start
comma
id|min_low_pfn
comma
id|max_low_pfn
)paren
suffix:semicolon
id|DBGDCONT
c_func
(paren
l_string|&quot; bootmap_start %lu, bootmap_size %lu, bootmap_pages %lu&bslash;n&quot;
comma
id|bootmap_start
comma
id|bootmap_size
comma
id|bootmap_pages
)paren
suffix:semicolon
multiline_comment|/* Mark the free regions.  */
id|for_each_mem_cluster
c_func
(paren
id|memdesc
comma
id|cluster
comma
id|i
)paren
(brace
r_if
c_cond
(paren
id|cluster-&gt;usage
op_amp
l_int|3
)paren
r_continue
suffix:semicolon
id|start
op_assign
id|cluster-&gt;start_pfn
suffix:semicolon
id|end
op_assign
id|cluster-&gt;start_pfn
op_plus
id|cluster-&gt;numpages
suffix:semicolon
r_if
c_cond
(paren
id|start
op_ge
id|max_low_pfn
op_logical_or
id|end
op_le
id|min_low_pfn
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|end
OG
id|max_low_pfn
)paren
id|end
op_assign
id|max_low_pfn
suffix:semicolon
r_if
c_cond
(paren
id|start
OL
id|min_low_pfn
)paren
id|start
op_assign
id|min_low_pfn
suffix:semicolon
r_if
c_cond
(paren
id|start
OL
id|start_kernel_pfn
)paren
(brace
r_if
c_cond
(paren
id|end
OG
id|end_kernel_pfn
)paren
(brace
id|free_bootmem_node
c_func
(paren
id|NODE_DATA
c_func
(paren
id|nid
)paren
comma
id|PFN_PHYS
c_func
(paren
id|start
)paren
comma
(paren
id|PFN_PHYS
c_func
(paren
id|start_kernel_pfn
)paren
op_minus
id|PFN_PHYS
c_func
(paren
id|start
)paren
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; freeing pages %ld:%ld&bslash;n&quot;
comma
id|start
comma
id|start_kernel_pfn
)paren
suffix:semicolon
id|start
op_assign
id|end_kernel_pfn
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|end
OG
id|start_kernel_pfn
)paren
id|end
op_assign
id|start_kernel_pfn
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|start
OL
id|end_kernel_pfn
)paren
id|start
op_assign
id|end_kernel_pfn
suffix:semicolon
r_if
c_cond
(paren
id|start
op_ge
id|end
)paren
r_continue
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
id|PFN_PHYS
c_func
(paren
id|start
)paren
comma
id|PFN_PHYS
c_func
(paren
id|end
)paren
op_minus
id|PFN_PHYS
c_func
(paren
id|start
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; freeing pages %ld:%ld&bslash;n&quot;
comma
id|start
comma
id|end
)paren
suffix:semicolon
)brace
multiline_comment|/* Reserve the bootmap memory.  */
id|reserve_bootmem_node
c_func
(paren
id|NODE_DATA
c_func
(paren
id|nid
)paren
comma
id|PFN_PHYS
c_func
(paren
id|bootmap_start
)paren
comma
id|bootmap_size
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; reserving pages %ld:%ld&bslash;n&quot;
comma
id|bootmap_start
comma
id|bootmap_start
op_plus
id|PFN_UP
c_func
(paren
id|bootmap_size
)paren
)paren
suffix:semicolon
id|numnodes
op_increment
suffix:semicolon
)brace
r_void
id|__init
DECL|function|setup_memory
id|setup_memory
c_func
(paren
r_void
op_star
id|kernel_end
)paren
(brace
r_int
id|nid
suffix:semicolon
id|show_mem_layout
c_func
(paren
)paren
suffix:semicolon
id|numnodes
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
id|MAX_NUMNODES
suffix:semicolon
id|nid
op_increment
)paren
id|setup_memory_node
c_func
(paren
id|nid
comma
id|kernel_end
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_BLK_DEV_INITRD
id|initrd_start
op_assign
id|INITRD_START
suffix:semicolon
r_if
c_cond
(paren
id|initrd_start
)paren
(brace
id|initrd_end
op_assign
id|initrd_start
op_plus
id|INITRD_SIZE
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Initial ramdisk at: 0x%p (%lu bytes)&bslash;n&quot;
comma
(paren
r_void
op_star
)paren
id|initrd_start
comma
id|INITRD_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
r_void
op_star
)paren
id|initrd_end
OG
id|phys_to_virt
c_func
(paren
id|PFN_PHYS
c_func
(paren
id|max_low_pfn
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;initrd extends beyond end of memory &quot;
l_string|&quot;(0x%08lx &gt; 0x%p)&bslash;ndisabling initrd&bslash;n&quot;
comma
id|initrd_end
comma
id|phys_to_virt
c_func
(paren
id|PFN_PHYS
c_func
(paren
id|max_low_pfn
)paren
)paren
)paren
suffix:semicolon
id|initrd_start
op_assign
id|initrd_end
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|reserve_bootmem_node
c_func
(paren
id|NODE_DATA
c_func
(paren
id|KVADDR_TO_NID
c_func
(paren
id|initrd_start
)paren
)paren
comma
id|virt_to_phys
c_func
(paren
(paren
r_void
op_star
)paren
id|initrd_start
)paren
comma
id|INITRD_SIZE
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif /* CONFIG_BLK_DEV_INITRD */
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
id|nid
suffix:semicolon
r_int
r_int
id|zones_size
(braket
id|MAX_NR_ZONES
)braket
op_assign
(brace
l_int|0
comma
)brace
suffix:semicolon
r_int
r_int
id|dma_local_pfn
suffix:semicolon
multiline_comment|/*&n;&t; * The old global MAX_DMA_ADDRESS per-arch API doesn&squot;t fit&n;&t; * in the NUMA model, for now we convert it to a pfn and&n;&t; * we interpret this pfn as a local per-node information.&n;&t; * This issue isn&squot;t very important since none of these machines&n;&t; * have legacy ISA slots anyways.&n;&t; */
id|dma_local_pfn
op_assign
id|virt_to_phys
c_func
(paren
(paren
r_char
op_star
)paren
id|MAX_DMA_ADDRESS
)paren
op_rshift
id|PAGE_SHIFT
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
r_int
r_int
id|end_pfn
op_assign
id|plat_node_bdata
(braket
id|nid
)braket
dot
id|node_low_pfn
suffix:semicolon
r_int
r_int
id|lmax_mapnr
suffix:semicolon
r_if
c_cond
(paren
id|dma_local_pfn
op_ge
id|end_pfn
op_minus
id|start_pfn
)paren
id|zones_size
(braket
id|ZONE_DMA
)braket
op_assign
id|end_pfn
op_minus
id|start_pfn
suffix:semicolon
r_else
(brace
id|zones_size
(braket
id|ZONE_DMA
)braket
op_assign
id|dma_local_pfn
suffix:semicolon
id|zones_size
(braket
id|ZONE_NORMAL
)braket
op_assign
(paren
id|end_pfn
op_minus
id|start_pfn
)paren
op_minus
id|dma_local_pfn
suffix:semicolon
)brace
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
op_lshift
id|PAGE_SHIFT
comma
l_int|NULL
)paren
suffix:semicolon
id|lmax_mapnr
op_assign
id|PLAT_NODE_DATA_STARTNR
c_func
(paren
id|nid
)paren
op_plus
id|PLAT_NODE_DATA_SIZE
c_func
(paren
id|nid
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lmax_mapnr
OG
id|max_mapnr
)paren
(brace
id|max_mapnr
op_assign
id|lmax_mapnr
suffix:semicolon
id|DBGDCONT
c_func
(paren
l_string|&quot;Grow max_mapnr to %ld&bslash;n&quot;
comma
id|max_mapnr
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* Initialize the kernel&squot;s ZERO_PGE. */
id|memset
c_func
(paren
(paren
r_void
op_star
)paren
id|ZERO_PGE
comma
l_int|0
comma
id|PAGE_SIZE
)paren
suffix:semicolon
)brace
DECL|macro|printkdot
mdefine_line|#define printkdot()&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (!(i++ % ((100UL*1024*1024)&gt;&gt;PAGE_SHIFT)))&t;&bslash;&n;&t;&t;printk(&quot;.&quot;);&t;&t;&t;&t;&bslash;&n;} while(0)
DECL|macro|clobber
mdefine_line|#define clobber(p, size) memset((p)-&gt;virtual, 0xaa, (size))
DECL|function|mem_stress
r_void
id|__init
id|mem_stress
c_func
(paren
r_void
)paren
(brace
id|LIST_HEAD
c_func
(paren
id|x
)paren
suffix:semicolon
id|LIST_HEAD
c_func
(paren
id|xx
)paren
suffix:semicolon
r_struct
id|page
op_star
id|p
suffix:semicolon
r_int
r_int
id|i
op_assign
l_int|0
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;starting memstress&quot;
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|p
op_assign
id|alloc_pages
c_func
(paren
id|GFP_ATOMIC
comma
l_int|1
)paren
)paren
)paren
(brace
id|clobber
c_func
(paren
id|p
comma
id|PAGE_SIZE
op_star
l_int|2
)paren
suffix:semicolon
id|list_add
c_func
(paren
op_amp
id|p-&gt;list
comma
op_amp
id|x
)paren
suffix:semicolon
id|printkdot
c_func
(paren
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
id|p
op_assign
id|alloc_page
c_func
(paren
id|GFP_ATOMIC
)paren
)paren
)paren
(brace
id|clobber
c_func
(paren
id|p
comma
id|PAGE_SIZE
)paren
suffix:semicolon
id|list_add
c_func
(paren
op_amp
id|p-&gt;list
comma
op_amp
id|xx
)paren
suffix:semicolon
id|printkdot
c_func
(paren
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|x
)paren
)paren
(brace
id|p
op_assign
id|list_entry
c_func
(paren
id|x.next
comma
r_struct
id|page
comma
id|list
)paren
suffix:semicolon
id|clobber
c_func
(paren
id|p
comma
id|PAGE_SIZE
op_star
l_int|2
)paren
suffix:semicolon
id|list_del
c_func
(paren
id|x.next
)paren
suffix:semicolon
id|__free_pages
c_func
(paren
id|p
comma
l_int|1
)paren
suffix:semicolon
id|printkdot
c_func
(paren
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|xx
)paren
)paren
(brace
id|p
op_assign
id|list_entry
c_func
(paren
id|xx.next
comma
r_struct
id|page
comma
id|list
)paren
suffix:semicolon
id|clobber
c_func
(paren
id|p
comma
id|PAGE_SIZE
)paren
suffix:semicolon
id|list_del
c_func
(paren
id|xx.next
)paren
suffix:semicolon
id|__free_pages
c_func
(paren
id|p
comma
l_int|0
)paren
suffix:semicolon
id|printkdot
c_func
(paren
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;I&squot;m still alive duh!&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|macro|printkdot
macro_line|#undef printkdot
DECL|macro|clobber
macro_line|#undef clobber
DECL|function|mem_init
r_void
id|__init
id|mem_init
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|codesize
comma
id|reservedpages
comma
id|datasize
comma
id|initsize
comma
id|pfn
suffix:semicolon
r_extern
r_int
id|page_is_ram
c_func
(paren
r_int
r_int
)paren
id|__init
suffix:semicolon
r_extern
r_char
id|_text
comma
id|_etext
comma
id|_data
comma
id|_edata
suffix:semicolon
r_extern
r_char
id|__init_begin
comma
id|__init_end
suffix:semicolon
r_extern
r_int
r_int
id|totalram_pages
suffix:semicolon
r_int
r_int
id|nid
comma
id|i
suffix:semicolon
id|mem_map_t
op_star
id|lmem_map
suffix:semicolon
id|high_memory
op_assign
(paren
r_void
op_star
)paren
id|__va
c_func
(paren
id|max_mapnr
op_lshift
id|PAGE_SHIFT
)paren
suffix:semicolon
id|reservedpages
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
multiline_comment|/*&n;&t;&t; * This will free up the bootmem, ie, slot 0 memory&n;&t;&t; */
id|totalram_pages
op_add_assign
id|free_all_bootmem_node
c_func
(paren
id|NODE_DATA
c_func
(paren
id|nid
)paren
)paren
suffix:semicolon
id|lmem_map
op_assign
id|NODE_MEM_MAP
c_func
(paren
id|nid
)paren
suffix:semicolon
id|pfn
op_assign
id|NODE_DATA
c_func
(paren
id|nid
)paren
op_member_access_from_pointer
id|node_start_paddr
op_rshift
id|PAGE_SHIFT
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
id|PLAT_NODE_DATA_SIZE
c_func
(paren
id|nid
)paren
suffix:semicolon
id|i
op_increment
comma
id|pfn
op_increment
)paren
r_if
c_cond
(paren
id|page_is_ram
c_func
(paren
id|pfn
)paren
op_logical_and
id|PageReserved
c_func
(paren
id|lmem_map
op_plus
id|i
)paren
)paren
id|reservedpages
op_increment
suffix:semicolon
)brace
id|codesize
op_assign
(paren
r_int
r_int
)paren
op_amp
id|_etext
op_minus
(paren
r_int
r_int
)paren
op_amp
id|_text
suffix:semicolon
id|datasize
op_assign
(paren
r_int
r_int
)paren
op_amp
id|_edata
op_minus
(paren
r_int
r_int
)paren
op_amp
id|_data
suffix:semicolon
id|initsize
op_assign
(paren
r_int
r_int
)paren
op_amp
id|__init_end
op_minus
(paren
r_int
r_int
)paren
op_amp
id|__init_begin
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Memory: %luk/%luk available (%luk kernel code, %luk reserved, &quot;
l_string|&quot;%luk data, %luk init)&bslash;n&quot;
comma
id|nr_free_pages
c_func
(paren
)paren
op_lshift
(paren
id|PAGE_SHIFT
op_minus
l_int|10
)paren
comma
id|num_physpages
op_lshift
(paren
id|PAGE_SHIFT
op_minus
l_int|10
)paren
comma
id|codesize
op_rshift
l_int|10
comma
id|reservedpages
op_lshift
(paren
id|PAGE_SHIFT
op_minus
l_int|10
)paren
comma
id|datasize
op_rshift
l_int|10
comma
id|initsize
op_rshift
l_int|10
)paren
suffix:semicolon
macro_line|#if 0
id|mem_stress
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
)brace
r_void
DECL|function|show_mem
id|show_mem
c_func
(paren
r_void
)paren
(brace
r_int
id|i
comma
id|free
op_assign
l_int|0
comma
id|total
op_assign
l_int|0
comma
id|reserved
op_assign
l_int|0
suffix:semicolon
r_int
id|shared
op_assign
l_int|0
comma
id|cached
op_assign
l_int|0
suffix:semicolon
r_int
id|nid
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;nMem-info:&bslash;n&quot;
)paren
suffix:semicolon
id|show_free_areas
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Free swap:       %6dkB&bslash;n&quot;
comma
id|nr_swap_pages
op_lshift
(paren
id|PAGE_SHIFT
op_minus
l_int|10
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
id|mem_map_t
op_star
id|lmem_map
op_assign
id|NODE_MEM_MAP
c_func
(paren
id|nid
)paren
suffix:semicolon
id|i
op_assign
id|PLAT_NODE_DATA_SIZE
c_func
(paren
id|nid
)paren
suffix:semicolon
r_while
c_loop
(paren
id|i
op_decrement
OG
l_int|0
)paren
(brace
id|total
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|PageReserved
c_func
(paren
id|lmem_map
op_plus
id|i
)paren
)paren
id|reserved
op_increment
suffix:semicolon
r_else
r_if
c_cond
(paren
id|PageSwapCache
c_func
(paren
id|lmem_map
op_plus
id|i
)paren
)paren
id|cached
op_increment
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|page_count
c_func
(paren
id|lmem_map
op_plus
id|i
)paren
)paren
id|free
op_increment
suffix:semicolon
r_else
id|shared
op_add_assign
id|atomic_read
c_func
(paren
op_amp
id|lmem_map
(braket
id|i
)braket
dot
id|count
)paren
op_minus
l_int|1
suffix:semicolon
)brace
)brace
id|printk
c_func
(paren
l_string|&quot;%ld pages of RAM&bslash;n&quot;
comma
id|total
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%ld free pages&bslash;n&quot;
comma
id|free
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%ld reserved pages&bslash;n&quot;
comma
id|reserved
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%ld pages shared&bslash;n&quot;
comma
id|shared
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%ld pages swap cached&bslash;n&quot;
comma
id|cached
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%ld pages in page table cache&bslash;n&quot;
comma
id|pgtable_cache_size
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%ld buffermem pages&bslash;n&quot;
comma
id|nr_buffermem_pages
c_func
(paren
)paren
)paren
suffix:semicolon
)brace
eof
