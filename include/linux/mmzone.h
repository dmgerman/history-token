macro_line|#ifndef _LINUX_MMZONE_H
DECL|macro|_LINUX_MMZONE_H
mdefine_line|#define _LINUX_MMZONE_H
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#include &lt;linux/cache.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;linux/numa.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
multiline_comment|/* Free memory management - zoned buddy allocator.  */
macro_line|#ifndef CONFIG_FORCE_MAX_ZONEORDER
DECL|macro|MAX_ORDER
mdefine_line|#define MAX_ORDER 11
macro_line|#else
DECL|macro|MAX_ORDER
mdefine_line|#define MAX_ORDER CONFIG_FORCE_MAX_ZONEORDER
macro_line|#endif
DECL|struct|free_area
r_struct
id|free_area
(brace
DECL|member|free_list
r_struct
id|list_head
id|free_list
suffix:semicolon
DECL|member|map
r_int
r_int
op_star
id|map
suffix:semicolon
DECL|member|nr_free
r_int
r_int
id|nr_free
suffix:semicolon
)brace
suffix:semicolon
r_struct
id|pglist_data
suffix:semicolon
multiline_comment|/*&n; * zone-&gt;lock and zone-&gt;lru_lock are two of the hottest locks in the kernel.&n; * So add a wild amount of padding here to ensure that they fall into separate&n; * cachelines.  There are very few zone structures in the machine, so space&n; * consumption is not a concern here.&n; */
macro_line|#if defined(CONFIG_SMP)
DECL|struct|zone_padding
r_struct
id|zone_padding
(brace
DECL|member|x
r_char
id|x
(braket
l_int|0
)braket
suffix:semicolon
DECL|variable|____cacheline_maxaligned_in_smp
)brace
id|____cacheline_maxaligned_in_smp
suffix:semicolon
DECL|macro|ZONE_PADDING
mdefine_line|#define ZONE_PADDING(name)&t;struct zone_padding name;
macro_line|#else
DECL|macro|ZONE_PADDING
mdefine_line|#define ZONE_PADDING(name)
macro_line|#endif
DECL|struct|per_cpu_pages
r_struct
id|per_cpu_pages
(brace
DECL|member|count
r_int
id|count
suffix:semicolon
multiline_comment|/* number of pages in the list */
DECL|member|low
r_int
id|low
suffix:semicolon
multiline_comment|/* low watermark, refill needed */
DECL|member|high
r_int
id|high
suffix:semicolon
multiline_comment|/* high watermark, emptying needed */
DECL|member|batch
r_int
id|batch
suffix:semicolon
multiline_comment|/* chunk size for buddy add/remove */
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
multiline_comment|/* the list of pages */
)brace
suffix:semicolon
DECL|struct|per_cpu_pageset
r_struct
id|per_cpu_pageset
(brace
DECL|member|pcp
r_struct
id|per_cpu_pages
id|pcp
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* 0: hot.  1: cold */
macro_line|#ifdef CONFIG_NUMA
DECL|member|numa_hit
r_int
r_int
id|numa_hit
suffix:semicolon
multiline_comment|/* allocated in intended node */
DECL|member|numa_miss
r_int
r_int
id|numa_miss
suffix:semicolon
multiline_comment|/* allocated in non intended node */
DECL|member|numa_foreign
r_int
r_int
id|numa_foreign
suffix:semicolon
multiline_comment|/* was intended here, hit elsewhere */
DECL|member|interleave_hit
r_int
r_int
id|interleave_hit
suffix:semicolon
multiline_comment|/* interleaver prefered this zone */
DECL|member|local_node
r_int
r_int
id|local_node
suffix:semicolon
multiline_comment|/* allocation from local node */
DECL|member|other_node
r_int
r_int
id|other_node
suffix:semicolon
multiline_comment|/* allocation from other node */
macro_line|#endif
DECL|variable|____cacheline_aligned_in_smp
)brace
id|____cacheline_aligned_in_smp
suffix:semicolon
DECL|macro|ZONE_DMA
mdefine_line|#define ZONE_DMA&t;&t;0
DECL|macro|ZONE_NORMAL
mdefine_line|#define ZONE_NORMAL&t;&t;1
DECL|macro|ZONE_HIGHMEM
mdefine_line|#define ZONE_HIGHMEM&t;&t;2
DECL|macro|MAX_NR_ZONES
mdefine_line|#define MAX_NR_ZONES&t;&t;3&t;/* Sync this with ZONES_SHIFT */
DECL|macro|ZONES_SHIFT
mdefine_line|#define ZONES_SHIFT&t;&t;2&t;/* ceil(log2(MAX_NR_ZONES)) */
multiline_comment|/*&n; * When a memory allocation must conform to specific limitations (such&n; * as being suitable for DMA) the caller will pass in hints to the&n; * allocator in the gfp_mask, in the zone modifier bits.  These bits&n; * are used to select a priority ordered list of memory zones which&n; * match the requested limits.  GFP_ZONEMASK defines which bits within&n; * the gfp_mask should be considered as zone modifiers.  Each valid&n; * combination of the zone modifier bits has a corresponding list&n; * of zones (in node_zonelists).  Thus for two zone modifiers there&n; * will be a maximum of 4 (2 ** 2) zonelists, for 3 modifiers there will&n; * be 8 (2 ** 3) zonelists.  GFP_ZONETYPES defines the number of possible&n; * combinations of zone modifiers in &quot;zone modifier space&quot;.&n; */
DECL|macro|GFP_ZONEMASK
mdefine_line|#define GFP_ZONEMASK&t;0x03
multiline_comment|/*&n; * As an optimisation any zone modifier bits which are only valid when&n; * no other zone modifier bits are set (loners) should be placed in&n; * the highest order bits of this field.  This allows us to reduce the&n; * extent of the zonelists thus saving space.  For example in the case&n; * of three zone modifier bits, we could require up to eight zonelists.&n; * If the left most zone modifier is a &quot;loner&quot; then the highest valid&n; * zonelist would be four allowing us to allocate only five zonelists.&n; * Use the first form when the left most bit is not a &quot;loner&quot;, otherwise&n; * use the second.&n; */
multiline_comment|/* #define GFP_ZONETYPES&t;(GFP_ZONEMASK + 1) */
multiline_comment|/* Non-loner */
DECL|macro|GFP_ZONETYPES
mdefine_line|#define GFP_ZONETYPES&t;((GFP_ZONEMASK + 1) / 2 + 1)&t;&t;/* Loner */
multiline_comment|/*&n; * On machines where it is needed (eg PCs) we divide physical memory&n; * into multiple physical zones. On a PC we have 3 zones:&n; *&n; * ZONE_DMA&t;  &lt; 16 MB&t;ISA DMA capable memory&n; * ZONE_NORMAL&t;16-896 MB&t;direct mapped by the kernel&n; * ZONE_HIGHMEM&t; &gt; 896 MB&t;only page cache and user processes&n; */
DECL|struct|zone
r_struct
id|zone
(brace
multiline_comment|/* Fields commonly accessed by the page allocator */
DECL|member|free_pages
r_int
r_int
id|free_pages
suffix:semicolon
DECL|member|pages_min
DECL|member|pages_low
DECL|member|pages_high
r_int
r_int
id|pages_min
comma
id|pages_low
comma
id|pages_high
suffix:semicolon
multiline_comment|/*&n;&t; * protection[] is a pre-calculated number of extra pages that must be&n;&t; * available in a zone in order for __alloc_pages() to allocate memory&n;&t; * from the zone. i.e., for a GFP_KERNEL alloc of &quot;order&quot; there must&n;&t; * be &quot;(1&lt;&lt;order) + protection[ZONE_NORMAL]&quot; free pages in the zone&n;&t; * for us to choose to allocate the page from that zone.&n;&t; *&n;&t; * It uses both min_free_kbytes and sysctl_lower_zone_protection.&n;&t; * The protection values are recalculated if either of these values&n;&t; * change.  The array elements are in zonelist order:&n;&t; *&t;[0] == GFP_DMA, [1] == GFP_KERNEL, [2] == GFP_HIGHMEM.&n;&t; */
DECL|member|protection
r_int
r_int
id|protection
(braket
id|MAX_NR_ZONES
)braket
suffix:semicolon
DECL|member|pageset
r_struct
id|per_cpu_pageset
id|pageset
(braket
id|NR_CPUS
)braket
suffix:semicolon
multiline_comment|/*&n;&t; * free areas of different sizes&n;&t; */
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|free_area
r_struct
id|free_area
id|free_area
(braket
id|MAX_ORDER
)braket
suffix:semicolon
id|ZONE_PADDING
c_func
(paren
id|_pad1_
)paren
multiline_comment|/* Fields commonly accessed by the page reclaim scanner */
id|spinlock_t
id|lru_lock
suffix:semicolon
DECL|member|active_list
r_struct
id|list_head
id|active_list
suffix:semicolon
DECL|member|inactive_list
r_struct
id|list_head
id|inactive_list
suffix:semicolon
DECL|member|nr_scan_active
r_int
r_int
id|nr_scan_active
suffix:semicolon
DECL|member|nr_scan_inactive
r_int
r_int
id|nr_scan_inactive
suffix:semicolon
DECL|member|nr_active
r_int
r_int
id|nr_active
suffix:semicolon
DECL|member|nr_inactive
r_int
r_int
id|nr_inactive
suffix:semicolon
DECL|member|pages_scanned
r_int
r_int
id|pages_scanned
suffix:semicolon
multiline_comment|/* since last reclaim */
DECL|member|all_unreclaimable
r_int
id|all_unreclaimable
suffix:semicolon
multiline_comment|/* All pages pinned */
multiline_comment|/*&n;&t; * prev_priority holds the scanning priority for this zone.  It is&n;&t; * defined as the scanning priority at which we achieved our reclaim&n;&t; * target at the previous try_to_free_pages() or balance_pgdat()&n;&t; * invokation.&n;&t; *&n;&t; * We use prev_priority as a measure of how much stress page reclaim is&n;&t; * under - it drives the swappiness decision: whether to unmap mapped&n;&t; * pages.&n;&t; *&n;&t; * temp_priority is used to remember the scanning priority at which&n;&t; * this zone was successfully refilled to free_pages == pages_high.&n;&t; *&n;&t; * Access to both these fields is quite racy even on uniprocessor.  But&n;&t; * it is expected to average out OK.&n;&t; */
DECL|member|temp_priority
r_int
id|temp_priority
suffix:semicolon
DECL|member|prev_priority
r_int
id|prev_priority
suffix:semicolon
id|ZONE_PADDING
c_func
(paren
id|_pad2_
)paren
multiline_comment|/* Rarely used or read-mostly fields */
multiline_comment|/*&n;&t; * wait_table&t;&t;-- the array holding the hash table&n;&t; * wait_table_size&t;-- the size of the hash table array&n;&t; * wait_table_bits&t;-- wait_table_size == (1 &lt;&lt; wait_table_bits)&n;&t; *&n;&t; * The purpose of all these is to keep track of the people&n;&t; * waiting for a page to become available and make them&n;&t; * runnable again when possible. The trouble is that this&n;&t; * consumes a lot of space, especially when so few things&n;&t; * wait on pages at a given time. So instead of using&n;&t; * per-page waitqueues, we use a waitqueue hash table.&n;&t; *&n;&t; * The bucket discipline is to sleep on the same queue when&n;&t; * colliding and wake all in that wait queue when removing.&n;&t; * When something wakes, it must check to be sure its page is&n;&t; * truly available, a la thundering herd. The cost of a&n;&t; * collision is great, but given the expected load of the&n;&t; * table, they should be so rare as to be outweighed by the&n;&t; * benefits from the saved space.&n;&t; *&n;&t; * __wait_on_page_locked() and unlock_page() in mm/filemap.c, are the&n;&t; * primary users of these fields, and in mm/page_alloc.c&n;&t; * free_area_init_core() performs the initialization of them.&n;&t; */
id|wait_queue_head_t
op_star
id|wait_table
suffix:semicolon
DECL|member|wait_table_size
r_int
r_int
id|wait_table_size
suffix:semicolon
DECL|member|wait_table_bits
r_int
r_int
id|wait_table_bits
suffix:semicolon
multiline_comment|/*&n;&t; * Discontig memory support fields.&n;&t; */
DECL|member|zone_pgdat
r_struct
id|pglist_data
op_star
id|zone_pgdat
suffix:semicolon
DECL|member|zone_mem_map
r_struct
id|page
op_star
id|zone_mem_map
suffix:semicolon
multiline_comment|/* zone_start_pfn == zone_start_paddr &gt;&gt; PAGE_SHIFT */
DECL|member|zone_start_pfn
r_int
r_int
id|zone_start_pfn
suffix:semicolon
DECL|member|spanned_pages
r_int
r_int
id|spanned_pages
suffix:semicolon
multiline_comment|/* total size, including holes */
DECL|member|present_pages
r_int
r_int
id|present_pages
suffix:semicolon
multiline_comment|/* amount of memory (excluding holes) */
multiline_comment|/*&n;&t; * rarely used fields:&n;&t; */
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|variable|____cacheline_maxaligned_in_smp
)brace
id|____cacheline_maxaligned_in_smp
suffix:semicolon
multiline_comment|/*&n; * The &quot;priority&quot; of VM scanning is how much of the queues we will scan in one&n; * go. A value of 12 for DEF_PRIORITY implies that we will scan 1/4096th of the&n; * queues (&quot;queue_length &gt;&gt; 12&quot;) during an aging round.&n; */
DECL|macro|DEF_PRIORITY
mdefine_line|#define DEF_PRIORITY 12
multiline_comment|/*&n; * One allocation request operates on a zonelist. A zonelist&n; * is a list of zones, the first one is the &squot;goal&squot; of the&n; * allocation, the other zones are fallback zones, in decreasing&n; * priority.&n; *&n; * Right now a zonelist takes up less than a cacheline. We never&n; * modify it apart from boot-up, and only a few indices are used,&n; * so despite the zonelist table being relatively big, the cache&n; * footprint of this construct is very small.&n; */
DECL|struct|zonelist
r_struct
id|zonelist
(brace
DECL|member|zones
r_struct
id|zone
op_star
id|zones
(braket
id|MAX_NUMNODES
op_star
id|MAX_NR_ZONES
op_plus
l_int|1
)braket
suffix:semicolon
singleline_comment|// NULL delimited
)brace
suffix:semicolon
multiline_comment|/*&n; * The pg_data_t structure is used in machines with CONFIG_DISCONTIGMEM&n; * (mostly NUMA machines?) to denote a higher-level memory zone than the&n; * zone denotes.&n; *&n; * On NUMA machines, each NUMA node would have a pg_data_t to describe&n; * it&squot;s memory layout.&n; *&n; * Memory statistics and page replacement data structures are maintained on a&n; * per-zone basis.&n; */
r_struct
id|bootmem_data
suffix:semicolon
DECL|struct|pglist_data
r_typedef
r_struct
id|pglist_data
(brace
DECL|member|node_zones
r_struct
id|zone
id|node_zones
(braket
id|MAX_NR_ZONES
)braket
suffix:semicolon
DECL|member|node_zonelists
r_struct
id|zonelist
id|node_zonelists
(braket
id|GFP_ZONETYPES
)braket
suffix:semicolon
DECL|member|nr_zones
r_int
id|nr_zones
suffix:semicolon
DECL|member|node_mem_map
r_struct
id|page
op_star
id|node_mem_map
suffix:semicolon
DECL|member|bdata
r_struct
id|bootmem_data
op_star
id|bdata
suffix:semicolon
DECL|member|node_start_pfn
r_int
r_int
id|node_start_pfn
suffix:semicolon
DECL|member|node_present_pages
r_int
r_int
id|node_present_pages
suffix:semicolon
multiline_comment|/* total number of physical pages */
DECL|member|node_spanned_pages
r_int
r_int
id|node_spanned_pages
suffix:semicolon
multiline_comment|/* total size of physical page&n;&t;&t;&t;&t;&t;     range, including holes */
DECL|member|node_id
r_int
id|node_id
suffix:semicolon
DECL|member|pgdat_next
r_struct
id|pglist_data
op_star
id|pgdat_next
suffix:semicolon
DECL|member|kswapd_wait
id|wait_queue_head_t
id|kswapd_wait
suffix:semicolon
DECL|member|kswapd
r_struct
id|task_struct
op_star
id|kswapd
suffix:semicolon
DECL|member|kswapd_max_order
r_int
id|kswapd_max_order
suffix:semicolon
DECL|typedef|pg_data_t
)brace
id|pg_data_t
suffix:semicolon
DECL|macro|node_present_pages
mdefine_line|#define node_present_pages(nid)&t;(NODE_DATA(nid)-&gt;node_present_pages)
DECL|macro|node_spanned_pages
mdefine_line|#define node_spanned_pages(nid)&t;(NODE_DATA(nid)-&gt;node_spanned_pages)
r_extern
r_int
id|numnodes
suffix:semicolon
r_extern
r_struct
id|pglist_data
op_star
id|pgdat_list
suffix:semicolon
r_void
id|__get_zone_counts
c_func
(paren
r_int
r_int
op_star
id|active
comma
r_int
r_int
op_star
id|inactive
comma
r_int
r_int
op_star
id|free
comma
r_struct
id|pglist_data
op_star
id|pgdat
)paren
suffix:semicolon
r_void
id|get_zone_counts
c_func
(paren
r_int
r_int
op_star
id|active
comma
r_int
r_int
op_star
id|inactive
comma
r_int
r_int
op_star
id|free
)paren
suffix:semicolon
r_void
id|build_all_zonelists
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|wakeup_kswapd
c_func
(paren
r_struct
id|zone
op_star
id|zone
comma
r_int
id|order
)paren
suffix:semicolon
r_int
id|zone_watermark_ok
c_func
(paren
r_struct
id|zone
op_star
id|z
comma
r_int
id|order
comma
r_int
r_int
id|mark
comma
r_int
id|alloc_type
comma
r_int
id|can_try_harder
comma
r_int
id|gfp_high
)paren
suffix:semicolon
multiline_comment|/*&n; * zone_idx() returns 0 for the ZONE_DMA zone, 1 for the ZONE_NORMAL zone, etc.&n; */
DECL|macro|zone_idx
mdefine_line|#define zone_idx(zone)&t;&t;((zone) - (zone)-&gt;zone_pgdat-&gt;node_zones)
multiline_comment|/**&n; * for_each_pgdat - helper macro to iterate over all nodes&n; * @pgdat - pointer to a pg_data_t variable&n; *&n; * Meant to help with common loops of the form&n; * pgdat = pgdat_list;&n; * while(pgdat) {&n; * &t;...&n; * &t;pgdat = pgdat-&gt;pgdat_next;&n; * }&n; */
DECL|macro|for_each_pgdat
mdefine_line|#define for_each_pgdat(pgdat) &bslash;&n;&t;for (pgdat = pgdat_list; pgdat; pgdat = pgdat-&gt;pgdat_next)
multiline_comment|/*&n; * next_zone - helper magic for for_each_zone()&n; * Thanks to William Lee Irwin III for this piece of ingenuity.&n; */
DECL|function|next_zone
r_static
r_inline
r_struct
id|zone
op_star
id|next_zone
c_func
(paren
r_struct
id|zone
op_star
id|zone
)paren
(brace
id|pg_data_t
op_star
id|pgdat
op_assign
id|zone-&gt;zone_pgdat
suffix:semicolon
r_if
c_cond
(paren
id|zone
op_minus
id|pgdat-&gt;node_zones
OL
id|MAX_NR_ZONES
op_minus
l_int|1
)paren
id|zone
op_increment
suffix:semicolon
r_else
r_if
c_cond
(paren
id|pgdat-&gt;pgdat_next
)paren
(brace
id|pgdat
op_assign
id|pgdat-&gt;pgdat_next
suffix:semicolon
id|zone
op_assign
id|pgdat-&gt;node_zones
suffix:semicolon
)brace
r_else
id|zone
op_assign
l_int|NULL
suffix:semicolon
r_return
id|zone
suffix:semicolon
)brace
multiline_comment|/**&n; * for_each_zone - helper macro to iterate over all memory zones&n; * @zone - pointer to struct zone variable&n; *&n; * The user only needs to declare the zone variable, for_each_zone&n; * fills it in. This basically means for_each_zone() is an&n; * easier to read version of this piece of code:&n; *&n; * for (pgdat = pgdat_list; pgdat; pgdat = pgdat-&gt;node_next)&n; * &t;for (i = 0; i &lt; MAX_NR_ZONES; ++i) {&n; * &t;&t;struct zone * z = pgdat-&gt;node_zones + i;&n; * &t;&t;...&n; * &t;}&n; * }&n; */
DECL|macro|for_each_zone
mdefine_line|#define for_each_zone(zone) &bslash;&n;&t;for (zone = pgdat_list-&gt;node_zones; zone; zone = next_zone(zone))
DECL|function|is_highmem_idx
r_static
r_inline
r_int
id|is_highmem_idx
c_func
(paren
r_int
id|idx
)paren
(brace
r_return
(paren
id|idx
op_eq
id|ZONE_HIGHMEM
)paren
suffix:semicolon
)brace
DECL|function|is_normal_idx
r_static
r_inline
r_int
id|is_normal_idx
c_func
(paren
r_int
id|idx
)paren
(brace
r_return
(paren
id|idx
op_eq
id|ZONE_NORMAL
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * is_highmem - helper function to quickly check if a struct zone is a &n; *              highmem zone or not.  This is an attempt to keep references&n; *              to ZONE_{DMA/NORMAL/HIGHMEM/etc} in general code to a minimum.&n; * @zone - pointer to struct zone variable&n; */
DECL|function|is_highmem
r_static
r_inline
r_int
id|is_highmem
c_func
(paren
r_struct
id|zone
op_star
id|zone
)paren
(brace
r_return
(paren
id|is_highmem_idx
c_func
(paren
id|zone
op_minus
id|zone-&gt;zone_pgdat-&gt;node_zones
)paren
)paren
suffix:semicolon
)brace
DECL|function|is_normal
r_static
r_inline
r_int
id|is_normal
c_func
(paren
r_struct
id|zone
op_star
id|zone
)paren
(brace
r_return
(paren
id|is_normal_idx
c_func
(paren
id|zone
op_minus
id|zone-&gt;zone_pgdat-&gt;node_zones
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* These two functions are used to setup the per zone pages min values */
r_struct
id|ctl_table
suffix:semicolon
r_struct
id|file
suffix:semicolon
r_int
id|min_free_kbytes_sysctl_handler
c_func
(paren
r_struct
id|ctl_table
op_star
comma
r_int
comma
r_struct
id|file
op_star
comma
r_void
id|__user
op_star
comma
r_int
op_star
comma
id|loff_t
op_star
)paren
suffix:semicolon
r_int
id|lower_zone_protection_sysctl_handler
c_func
(paren
r_struct
id|ctl_table
op_star
comma
r_int
comma
r_struct
id|file
op_star
comma
r_void
id|__user
op_star
comma
r_int
op_star
comma
id|loff_t
op_star
)paren
suffix:semicolon
macro_line|#include &lt;linux/topology.h&gt;
multiline_comment|/* Returns the number of the current Node. */
DECL|macro|numa_node_id
mdefine_line|#define numa_node_id()&t;&t;(cpu_to_node(smp_processor_id()))
macro_line|#ifndef CONFIG_DISCONTIGMEM
r_extern
r_struct
id|pglist_data
id|contig_page_data
suffix:semicolon
DECL|macro|NODE_DATA
mdefine_line|#define NODE_DATA(nid)&t;&t;(&amp;contig_page_data)
DECL|macro|NODE_MEM_MAP
mdefine_line|#define NODE_MEM_MAP(nid)&t;mem_map
DECL|macro|MAX_NODES_SHIFT
mdefine_line|#define MAX_NODES_SHIFT&t;&t;1
DECL|macro|pfn_to_nid
mdefine_line|#define pfn_to_nid(pfn)&t;&t;(0)
macro_line|#else /* CONFIG_DISCONTIGMEM */
macro_line|#include &lt;asm/mmzone.h&gt;
macro_line|#if BITS_PER_LONG == 32 || defined(ARCH_HAS_ATOMIC_UNSIGNED)
multiline_comment|/*&n; * with 32 bit page-&gt;flags field, we reserve 8 bits for node/zone info.&n; * there are 3 zones (2 bits) and this leaves 8-2=6 bits for nodes.&n; */
DECL|macro|MAX_NODES_SHIFT
mdefine_line|#define MAX_NODES_SHIFT&t;&t;6
macro_line|#elif BITS_PER_LONG == 64
multiline_comment|/*&n; * with 64 bit flags field, there&squot;s plenty of room.&n; */
DECL|macro|MAX_NODES_SHIFT
mdefine_line|#define MAX_NODES_SHIFT&t;&t;10
macro_line|#endif
macro_line|#endif /* !CONFIG_DISCONTIGMEM */
macro_line|#if NODES_SHIFT &gt; MAX_NODES_SHIFT
macro_line|#error NODES_SHIFT &gt; MAX_NODES_SHIFT
macro_line|#endif
multiline_comment|/* There are currently 3 zones: DMA, Normal &amp; Highmem, thus we need 2 bits */
DECL|macro|MAX_ZONES_SHIFT
mdefine_line|#define MAX_ZONES_SHIFT&t;&t;2
macro_line|#if ZONES_SHIFT &gt; MAX_ZONES_SHIFT
macro_line|#error ZONES_SHIFT &gt; MAX_ZONES_SHIFT
macro_line|#endif
macro_line|#endif /* !__ASSEMBLY__ */
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _LINUX_MMZONE_H */
eof
