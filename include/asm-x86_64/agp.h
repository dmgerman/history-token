macro_line|#ifndef AGP_H
DECL|macro|AGP_H
mdefine_line|#define AGP_H 1
macro_line|#include &lt;asm/cacheflush.h&gt;
multiline_comment|/* &n; * Functions to keep the agpgart mappings coherent.&n; * The GART gives the CPU a physical alias of memory. The alias is&n; * mapped uncacheable. Make sure there are no conflicting mappings&n; * with different cachability attributes for the same page.&n; */
r_int
id|map_page_into_agp
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
suffix:semicolon
r_int
id|unmap_page_from_agp
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
suffix:semicolon
DECL|macro|flush_agp_mappings
mdefine_line|#define flush_agp_mappings() global_flush_tlb()
multiline_comment|/* Could use CLFLUSH here if the cpu supports it. But then it would&n;   need to be called for each cacheline of the whole page so it may not be &n;   worth it. Would need a page for it. */
DECL|macro|flush_agp_cache
mdefine_line|#define flush_agp_cache() asm volatile(&quot;wbinvd&quot;:::&quot;memory&quot;)
macro_line|#endif
eof
