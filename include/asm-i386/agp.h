macro_line|#ifndef AGP_H
DECL|macro|AGP_H
mdefine_line|#define AGP_H 1
macro_line|#include &lt;asm/pgtable.h&gt;
multiline_comment|/* &n; * Functions to keep the agpgart mappings coherent with the MMU.&n; * The GART gives the CPU a physical alias of pages in memory. The alias region is&n; * mapped uncacheable. Make sure there are no conflicting mappings&n; * with different cachability attributes for the same page. This avoids&n; * data corruption on some CPUs.&n; */
DECL|macro|map_page_into_agp
mdefine_line|#define map_page_into_agp(page) change_page_attr(page, 1, PAGE_KERNEL_NOCACHE)
DECL|macro|unmap_page_from_agp
mdefine_line|#define unmap_page_from_agp(page) change_page_attr(page, 1, PAGE_KERNEL)
DECL|macro|flush_agp_mappings
mdefine_line|#define flush_agp_mappings() global_flush_tlb()
multiline_comment|/* Could use CLFLUSH here if the cpu supports it. But then it would&n;   need to be called for each cacheline of the whole page so it may not be &n;   worth it. Would need a page for it. */
DECL|macro|flush_agp_cache
mdefine_line|#define flush_agp_cache() asm volatile(&quot;wbinvd&quot;:::&quot;memory&quot;)
macro_line|#endif
eof
