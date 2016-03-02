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
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#ifdef CONFIG_DISCONTIGMEM
macro_line|#include &lt;asm/numnodes.h&gt;
macro_line|#endif
macro_line|#ifndef MAX_NUMNODES
DECL|macro|MAX_NUMNODES
mdefine_line|#define MAX_NUMNODES 1
macro_line|#endif
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
r_int
id|x
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
DECL|variable|____cacheline_aligned_in_smp
)brace
id|____cacheline_aligned_in_smp
suffix:semicolon
multiline_comment|/*&n; * On machines where it is needed (eg PCs) we divide physical memory&n; * into multiple physical zones. On a PC we have 3 zones:&n; *&n; * ZONE_DMA&t;  &lt; 16 MB&t;ISA DMA capable memory&n; * ZONE_NORMAL&t;16-896 MB&t;direct mapped by the kernel&n; * ZONE_HIGHMEM&t; &gt; 896 MB&t;only page cache and user processes&n; */
DECL|struct|zone
r_struct
id|zone
(brace
multiline_comment|/*&n;&t; * Commonly accessed fields:&n;&t; */
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
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
id|ZONE_PADDING
c_func
(paren
id|_pad1_
)paren
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
DECL|member|refill_counter
id|atomic_t
id|refill_counter
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
id|ZONE_PADDING
c_func
(paren
id|_pad2_
)paren
multiline_comment|/*&n;&t; * free areas of different sizes&n;&t; */
r_struct
id|free_area
id|free_area
(braket
id|MAX_ORDER
)braket
suffix:semicolon
multiline_comment|/*&n;&t; * wait_table&t;&t;-- the array holding the hash table&n;&t; * wait_table_size&t;-- the size of the hash table array&n;&t; * wait_table_bits&t;-- wait_table_size == (1 &lt;&lt; wait_table_bits)&n;&t; *&n;&t; * The purpose of all these is to keep track of the people&n;&t; * waiting for a page to become available and make them&n;&t; * runnable again when possible. The trouble is that this&n;&t; * consumes a lot of space, especially when so few things&n;&t; * wait on pages at a given time. So instead of using&n;&t; * per-page waitqueues, we use a waitqueue hash table.&n;&t; *&n;&t; * The bucket discipline is to sleep on the same queue when&n;&t; * colliding and wake all in that wait queue when removing.&n;&t; * When something wakes, it must check to be sure its page is&n;&t; * truly available, a la thundering herd. The cost of a&n;&t; * collision is great, but given the expected load of the&n;&t; * table, they should be so rare as to be outweighed by the&n;&t; * benefits from the saved space.&n;&t; *&n;&t; * __wait_on_page_locked() and unlock_page() in mm/filemap.c, are the&n;&t; * primary users of these fields, and in mm/page_alloc.c&n;&t; * free_area_init_core() performs the initialization of them.&n;&t; */
DECL|member|wait_table
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
id|ZONE_PADDING
c_func
(paren
id|_pad3_
)paren
r_struct
id|per_cpu_pageset
id|pageset
(braket
id|NR_CPUS
)braket
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
multiline_comment|/*&n;&t; * rarely used fields:&n;&t; */
DECL|member|name
r_char
op_star
id|name
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
DECL|variable|____cacheline_maxaligned_in_smp
)brace
id|____cacheline_maxaligned_in_smp
suffix:semicolon
DECL|macro|ZONE_DMA
mdefine_line|#define ZONE_DMA&t;&t;0
DECL|macro|ZONE_NORMAL
mdefine_line|#define ZONE_NORMAL&t;&t;1
DECL|macro|ZONE_HIGHMEM
mdefine_line|#define ZONE_HIGHMEM&t;&t;2
DECL|macro|MAX_NR_ZONES
mdefine_line|#define MAX_NR_ZONES&t;&t;3
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
DECL|macro|GFP_ZONEMASK
mdefine_line|#define GFP_ZONEMASK&t;0x0f
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
id|GFP_ZONEMASK
op_plus
l_int|1
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
DECL|member|valid_addr_bitmap
r_int
r_int
op_star
id|valid_addr_bitmap
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
DECL|member|node_size
r_int
r_int
id|node_size
suffix:semicolon
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
DECL|typedef|pg_data_t
)brace
id|pg_data_t
suffix:semicolon
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
r_static
r_inline
r_int
DECL|function|memclass
id|memclass
c_func
(paren
r_struct
id|zone
op_star
id|pgzone
comma
r_struct
id|zone
op_star
id|classzone
)paren
(brace
r_if
c_cond
(paren
id|pgzone-&gt;zone_pgdat
op_ne
id|classzone-&gt;zone_pgdat
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|pgzone
OG
id|classzone
)paren
r_return
l_int|0
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
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
)paren
suffix:semicolon
r_void
id|build_all_zonelists
c_func
(paren
r_void
)paren
suffix:semicolon
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
macro_line|#ifdef CONFIG_NUMA
DECL|macro|MAX_NR_MEMBLKS
mdefine_line|#define MAX_NR_MEMBLKS&t;BITS_PER_LONG /* Max number of Memory Blocks */
macro_line|#else /* !CONFIG_NUMA */
DECL|macro|MAX_NR_MEMBLKS
mdefine_line|#define MAX_NR_MEMBLKS&t;1
macro_line|#endif /* CONFIG_NUMA */
macro_line|#include &lt;asm/topology.h&gt;
multiline_comment|/* Returns the number of the current Node. */
DECL|macro|numa_node_id
mdefine_line|#define numa_node_id()&t;&t;(__cpu_to_node(smp_processor_id()))
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
DECL|macro|MAX_NR_NODES
mdefine_line|#define MAX_NR_NODES&t;&t;1
macro_line|#else /* CONFIG_DISCONTIGMEM */
macro_line|#include &lt;asm/mmzone.h&gt;
multiline_comment|/* page-&gt;zone is currently 8 bits ... */
DECL|macro|MAX_NR_NODES
mdefine_line|#define MAX_NR_NODES&t;&t;(255 / MAX_NR_ZONES)
macro_line|#endif /* !CONFIG_DISCONTIGMEM */
r_extern
id|DECLARE_BITMAP
c_func
(paren
id|memblk_online_map
comma
id|MAX_NR_MEMBLKS
)paren
suffix:semicolon
macro_line|#if defined(CONFIG_DISCONTIGMEM) || defined(CONFIG_NUMA)
DECL|macro|memblk_online
mdefine_line|#define memblk_online(memblk)&t;&t;test_bit(memblk, memblk_online_map)
DECL|macro|memblk_set_online
mdefine_line|#define memblk_set_online(memblk)&t;set_bit(memblk, memblk_online_map)
DECL|macro|memblk_set_offline
mdefine_line|#define memblk_set_offline(memblk)&t;clear_bit(memblk, memblk_online_map)
DECL|function|num_online_memblks
r_static
r_inline
r_int
r_int
id|num_online_memblks
c_func
(paren
r_void
)paren
(brace
r_int
id|i
comma
id|num
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
id|MAX_NR_MEMBLKS
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|memblk_online
c_func
(paren
id|i
)paren
)paren
id|num
op_increment
suffix:semicolon
)brace
r_return
id|num
suffix:semicolon
)brace
macro_line|#else /* !CONFIG_DISCONTIGMEM &amp;&amp; !CONFIG_NUMA */
DECL|macro|memblk_online
mdefine_line|#define memblk_online(memblk) &bslash;&n;&t;({ BUG_ON((memblk) != 0); test_bit(memblk, memblk_online_map); })
DECL|macro|memblk_set_online
mdefine_line|#define memblk_set_online(memblk) &bslash;&n;&t;({ BUG_ON((memblk) != 0); set_bit(memblk, memblk_online_map); })
DECL|macro|memblk_set_offline
mdefine_line|#define memblk_set_offline(memblk) &bslash;&n;&t;({ BUG_ON((memblk) != 0); clear_bit(memblk, memblk_online_map); })
DECL|macro|num_online_memblks
mdefine_line|#define num_online_memblks()&t;&t;1
macro_line|#endif /* CONFIG_DISCONTIGMEM || CONFIG_NUMA */
DECL|macro|MAP_ALIGN
mdefine_line|#define MAP_ALIGN(x)&t;((((x) % sizeof(struct page)) == 0) ? (x) : ((x) + &bslash;&n;&t;&t;sizeof(struct page) - ((x) % sizeof(struct page))))
macro_line|#endif /* !__ASSEMBLY__ */
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _LINUX_MMZONE_H */
eof
