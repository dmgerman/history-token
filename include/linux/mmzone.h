macro_line|#ifndef _LINUX_MMZONE_H
DECL|macro|_LINUX_MMZONE_H
mdefine_line|#define _LINUX_MMZONE_H
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
multiline_comment|/*&n; * Free memory management - zoned buddy allocator.&n; */
macro_line|#ifndef CONFIG_FORCE_MAX_ZONEORDER
DECL|macro|MAX_ORDER
mdefine_line|#define MAX_ORDER 10
macro_line|#else
DECL|macro|MAX_ORDER
mdefine_line|#define MAX_ORDER CONFIG_FORCE_MAX_ZONEORDER
macro_line|#endif
DECL|struct|free_area_struct
r_typedef
r_struct
id|free_area_struct
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
DECL|typedef|free_area_t
)brace
id|free_area_t
suffix:semicolon
r_struct
id|pglist_data
suffix:semicolon
multiline_comment|/*&n; * On machines where it is needed (eg PCs) we divide physical memory&n; * into multiple physical zones. On a PC we have 3 zones:&n; *&n; * ZONE_DMA&t;  &lt; 16 MB&t;ISA DMA capable memory&n; * ZONE_NORMAL&t;16-896 MB&t;direct mapped by the kernel&n; * ZONE_HIGHMEM&t; &gt; 896 MB&t;only page cache and user processes&n; */
DECL|struct|zone_struct
r_typedef
r_struct
id|zone_struct
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
DECL|member|need_balance
r_int
id|need_balance
suffix:semicolon
multiline_comment|/*&n;&t; * free areas of different sizes&n;&t; */
DECL|member|free_area
id|free_area_t
id|free_area
(braket
id|MAX_ORDER
)braket
suffix:semicolon
multiline_comment|/*&n;&t; * wait_table&t;&t;-- the array holding the hash table&n;&t; * wait_table_size&t;-- the size of the hash table array&n;&t; * wait_table_bits&t;-- wait_table_size == (1 &lt;&lt; wait_table_bits)&n;&t; *&n;&t; * The purpose of all these is to keep track of the people&n;&t; * waiting for a page to become available and make them&n;&t; * runnable again when possible. The trouble is that this&n;&t; * consumes a lot of space, especially when so few things&n;&t; * wait on pages at a given time. So instead of using&n;&t; * per-page waitqueues, we use a waitqueue hash table.&n;&t; *&n;&t; * The bucket discipline is to sleep on the same queue when&n;&t; * colliding and wake all in that wait queue when removing.&n;&t; * When something wakes, it must check to be sure its page is&n;&t; * truly available, a la thundering herd. The cost of a&n;&t; * collision is great, but given the expected load of the&n;&t; * table, they should be so rare as to be outweighed by the&n;&t; * benefits from the saved space.&n;&t; *&n;&t; * __wait_on_page() and unlock_page() in mm/filemap.c, are the&n;&t; * primary users of these fields, and in mm/page_alloc.c&n;&t; * free_area_init_core() performs the initialization of them.&n;&t; */
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
DECL|member|zone_start_paddr
r_int
r_int
id|zone_start_paddr
suffix:semicolon
DECL|member|zone_start_mapnr
r_int
r_int
id|zone_start_mapnr
suffix:semicolon
multiline_comment|/*&n;&t; * rarely used fields:&n;&t; */
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
DECL|typedef|zone_t
)brace
id|zone_t
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
DECL|struct|zonelist_struct
r_typedef
r_struct
id|zonelist_struct
(brace
DECL|member|zones
id|zone_t
op_star
id|zones
(braket
id|MAX_NR_ZONES
op_plus
l_int|1
)braket
suffix:semicolon
singleline_comment|// NULL delimited
DECL|typedef|zonelist_t
)brace
id|zonelist_t
suffix:semicolon
DECL|macro|GFP_ZONEMASK
mdefine_line|#define GFP_ZONEMASK&t;0x0f
multiline_comment|/*&n; * The pg_data_t structure is used in machines with CONFIG_DISCONTIGMEM&n; * (mostly NUMA machines?) to denote a higher-level memory zone than the&n; * zone_struct denotes.&n; *&n; * On NUMA machines, each NUMA node would have a pg_data_t to describe&n; * it&squot;s memory layout.&n; *&n; * XXX: we need to move the global memory statistics (active_list, ...)&n; *      into the pg_data_t to properly support NUMA.&n; */
r_struct
id|bootmem_data
suffix:semicolon
DECL|struct|pglist_data
r_typedef
r_struct
id|pglist_data
(brace
DECL|member|node_zones
id|zone_t
id|node_zones
(braket
id|MAX_NR_ZONES
)braket
suffix:semicolon
DECL|member|node_zonelists
id|zonelist_t
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
DECL|member|node_start_paddr
r_int
r_int
id|node_start_paddr
suffix:semicolon
DECL|member|node_start_mapnr
r_int
r_int
id|node_start_mapnr
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
DECL|member|node_next
r_struct
id|pglist_data
op_star
id|node_next
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
id|pg_data_t
op_star
id|pgdat_list
suffix:semicolon
DECL|macro|memclass
mdefine_line|#define memclass(pgzone, classzone)&t;(((pgzone)-&gt;zone_pgdat == (classzone)-&gt;zone_pgdat) &bslash;&n;&t;&t;&t;&amp;&amp; ((pgzone) &lt;= (classzone)))
multiline_comment|/*&n; * The following two are not meant for general usage. They are here as&n; * prototypes for the discontig memory code.&n; */
r_struct
id|page
suffix:semicolon
r_extern
r_void
id|show_free_areas_core
c_func
(paren
id|pg_data_t
op_star
id|pgdat
)paren
suffix:semicolon
r_extern
r_void
id|free_area_init_core
c_func
(paren
r_int
id|nid
comma
id|pg_data_t
op_star
id|pgdat
comma
r_struct
id|page
op_star
op_star
id|gmap
comma
r_int
r_int
op_star
id|zones_size
comma
r_int
r_int
id|paddr
comma
r_int
r_int
op_star
id|zholes_size
comma
r_struct
id|page
op_star
id|pmap
)paren
suffix:semicolon
r_extern
id|pg_data_t
id|contig_page_data
suffix:semicolon
macro_line|#ifndef CONFIG_DISCONTIGMEM
DECL|macro|NODE_DATA
mdefine_line|#define NODE_DATA(nid)&t;&t;(&amp;contig_page_data)
DECL|macro|NODE_MEM_MAP
mdefine_line|#define NODE_MEM_MAP(nid)&t;mem_map
DECL|macro|MAX_NR_NODES
mdefine_line|#define MAX_NR_NODES&t;&t;1
macro_line|#else /* !CONFIG_DISCONTIGMEM */
macro_line|#include &lt;asm/mmzone.h&gt;
multiline_comment|/* page-&gt;zone is currently 8 bits ... */
DECL|macro|MAX_NR_NODES
mdefine_line|#define MAX_NR_NODES&t;&t;(255 / MAX_NR_ZONES)
macro_line|#endif /* !CONFIG_DISCONTIGMEM */
DECL|macro|MAP_ALIGN
mdefine_line|#define MAP_ALIGN(x)&t;((((x) % sizeof(mem_map_t)) == 0) ? (x) : ((x) + &bslash;&n;&t;&t;sizeof(mem_map_t) - ((x) % sizeof(mem_map_t))))
macro_line|#endif /* !__ASSEMBLY__ */
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _LINUX_MMZONE_H */
eof
