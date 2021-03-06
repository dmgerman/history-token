macro_line|#ifndef meminit_h
DECL|macro|meminit_h
mdefine_line|#define meminit_h
multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; */
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/*&n; * Entries defined so far:&n; * &t;- boot param structure itself&n; * &t;- memory map&n; * &t;- initrd (optional)&n; * &t;- command line string&n; * &t;- kernel code &amp; data&n; *&n; * More could be added if necessary&n; */
DECL|macro|IA64_MAX_RSVD_REGIONS
mdefine_line|#define IA64_MAX_RSVD_REGIONS 5
DECL|struct|rsvd_region
r_struct
id|rsvd_region
(brace
DECL|member|start
r_int
r_int
id|start
suffix:semicolon
multiline_comment|/* virtual address of beginning of element */
DECL|member|end
r_int
r_int
id|end
suffix:semicolon
multiline_comment|/* virtual address of end of element + 1 */
)brace
suffix:semicolon
r_extern
r_struct
id|rsvd_region
id|rsvd_region
(braket
id|IA64_MAX_RSVD_REGIONS
op_plus
l_int|1
)braket
suffix:semicolon
r_extern
r_int
id|num_rsvd_regions
suffix:semicolon
r_extern
r_void
id|find_memory
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|reserve_memory
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|find_initrd
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|filter_rsvd_memory
(paren
r_int
r_int
id|start
comma
r_int
r_int
id|end
comma
r_void
op_star
id|arg
)paren
suffix:semicolon
multiline_comment|/*&n; * For rounding an address to the next IA64_GRANULE_SIZE or order&n; */
DECL|macro|GRANULEROUNDDOWN
mdefine_line|#define GRANULEROUNDDOWN(n)&t;((n) &amp; ~(IA64_GRANULE_SIZE-1))
DECL|macro|GRANULEROUNDUP
mdefine_line|#define GRANULEROUNDUP(n)&t;(((n)+IA64_GRANULE_SIZE-1) &amp; ~(IA64_GRANULE_SIZE-1))
DECL|macro|ORDERROUNDDOWN
mdefine_line|#define ORDERROUNDDOWN(n)&t;((n) &amp; ~((PAGE_SIZE&lt;&lt;MAX_ORDER)-1))
macro_line|#ifdef CONFIG_DISCONTIGMEM
r_extern
r_void
id|call_pernode_memory
(paren
r_int
r_int
id|start
comma
r_int
r_int
id|len
comma
r_void
op_star
id|func
)paren
suffix:semicolon
macro_line|#else
DECL|macro|call_pernode_memory
macro_line|# define call_pernode_memory(start, len, func)&t;(*func)(start, len, 0)
macro_line|#endif
DECL|macro|IGNORE_PFN0
mdefine_line|#define IGNORE_PFN0&t;1&t;/* XXX fix me: ignore pfn 0 until TLB miss handler is updated... */
macro_line|#ifdef CONFIG_VIRTUAL_MEM_MAP
DECL|macro|LARGE_GAP
macro_line|# define LARGE_GAP&t;0x40000000 /* Use virtual mem map if hole is &gt; than this */
r_extern
r_int
r_int
id|vmalloc_end
suffix:semicolon
r_extern
r_struct
id|page
op_star
id|vmem_map
suffix:semicolon
r_extern
r_int
id|find_largest_hole
(paren
id|u64
id|start
comma
id|u64
id|end
comma
r_void
op_star
id|arg
)paren
suffix:semicolon
r_extern
r_int
id|create_mem_map_page_table
(paren
id|u64
id|start
comma
id|u64
id|end
comma
r_void
op_star
id|arg
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif /* meminit_h */
eof
