macro_line|#ifndef __MMU_H
DECL|macro|__MMU_H
mdefine_line|#define __MMU_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/const.h&gt;
multiline_comment|/*&n; * For the 8k pagesize kernel, use only 10 hw context bits to optimize some&n; * shifts in the fast tlbmiss handlers, instead of all 13 bits (specifically&n; * for vpte offset calculation). For other pagesizes, this optimization in&n; * the tlbhandlers can not be done; but still, all 13 bits can not be used&n; * because the tlb handlers use &quot;andcc&quot; instruction which sign extends 13&n; * bit arguments.&n; */
macro_line|#if PAGE_SHIFT == 13
DECL|macro|CTX_NR_BITS
mdefine_line|#define CTX_NR_BITS&t;&t;10
macro_line|#else
DECL|macro|CTX_NR_BITS
mdefine_line|#define CTX_NR_BITS&t;&t;12
macro_line|#endif
DECL|macro|TAG_CONTEXT_BITS
mdefine_line|#define TAG_CONTEXT_BITS&t;((_AC(1,UL) &lt;&lt; CTX_NR_BITS) - _AC(1,UL))
multiline_comment|/* UltraSPARC-III+ and later have a feature whereby you can&n; * select what page size the various Data-TLB instances in the&n; * chip.  In order to gracefully support this, we put the version&n; * field in a spot outside of the areas of the context register&n; * where this parameter is specified.&n; */
DECL|macro|CTX_VERSION_SHIFT
mdefine_line|#define CTX_VERSION_SHIFT&t;22
DECL|macro|CTX_VERSION_MASK
mdefine_line|#define CTX_VERSION_MASK&t;((~0UL) &lt;&lt; CTX_VERSION_SHIFT)
DECL|macro|CTX_PGSZ_8KB
mdefine_line|#define CTX_PGSZ_8KB&t;&t;_AC(0x0,UL)
DECL|macro|CTX_PGSZ_64KB
mdefine_line|#define CTX_PGSZ_64KB&t;&t;_AC(0x1,UL)
DECL|macro|CTX_PGSZ_512KB
mdefine_line|#define CTX_PGSZ_512KB&t;&t;_AC(0x2,UL)
DECL|macro|CTX_PGSZ_4MB
mdefine_line|#define CTX_PGSZ_4MB&t;&t;_AC(0x3,UL)
DECL|macro|CTX_PGSZ_BITS
mdefine_line|#define CTX_PGSZ_BITS&t;&t;_AC(0x7,UL)
DECL|macro|CTX_PGSZ0_NUC_SHIFT
mdefine_line|#define CTX_PGSZ0_NUC_SHIFT&t;61
DECL|macro|CTX_PGSZ1_NUC_SHIFT
mdefine_line|#define CTX_PGSZ1_NUC_SHIFT&t;58
DECL|macro|CTX_PGSZ0_SHIFT
mdefine_line|#define CTX_PGSZ0_SHIFT&t;&t;16
DECL|macro|CTX_PGSZ1_SHIFT
mdefine_line|#define CTX_PGSZ1_SHIFT&t;&t;19
DECL|macro|CTX_PGSZ_MASK
mdefine_line|#define CTX_PGSZ_MASK&t;&t;((CTX_PGSZ_BITS &lt;&lt; CTX_PGSZ0_SHIFT) | &bslash;&n;&t;&t;&t;&t; (CTX_PGSZ_BITS &lt;&lt; CTX_PGSZ1_SHIFT))
macro_line|#if defined(CONFIG_SPARC64_PAGE_SIZE_8KB)
DECL|macro|CTX_PGSZ_BASE
mdefine_line|#define CTX_PGSZ_BASE&t;CTX_PGSZ_8KB
macro_line|#elif defined(CONFIG_SPARC64_PAGE_SIZE_64KB)
DECL|macro|CTX_PGSZ_BASE
mdefine_line|#define CTX_PGSZ_BASE&t;CTX_PGSZ_64KB
macro_line|#elif defined(CONFIG_SPARC64_PAGE_SIZE_512KB)
DECL|macro|CTX_PGSZ_BASE
mdefine_line|#define CTX_PGSZ_BASE&t;CTX_PGSZ_512KB
macro_line|#elif defined(CONFIG_SPARC64_PAGE_SIZE_4MB)
DECL|macro|CTX_PGSZ_BASE
mdefine_line|#define CTX_PGSZ_BASE&t;CTX_PGSZ_4MB
macro_line|#else
macro_line|#error No page size specified in kernel configuration
macro_line|#endif
macro_line|#if defined(CONFIG_HUGETLB_PAGE_SIZE_4MB)
DECL|macro|CTX_PGSZ_HUGE
mdefine_line|#define CTX_PGSZ_HUGE&t;&t;CTX_PGSZ_4MB
macro_line|#elif defined(CONFIG_HUGETLB_PAGE_SIZE_512K)
DECL|macro|CTX_PGSZ_HUGE
mdefine_line|#define CTX_PGSZ_HUGE&t;&t;CTX_PGSZ_512KB
macro_line|#elif defined(CONFIG_HUGETLB_PAGE_SIZE_64K)
DECL|macro|CTX_PGSZ_HUGE
mdefine_line|#define CTX_PGSZ_HUGE&t;&t;CTX_PGSZ_64KB
macro_line|#endif
DECL|macro|CTX_PGSZ_KERN
mdefine_line|#define CTX_PGSZ_KERN&t;CTX_PGSZ_4MB
multiline_comment|/* Thus, when running on UltraSPARC-III+ and later, we use the following&n; * PRIMARY_CONTEXT register values for the kernel context.&n; */
DECL|macro|CTX_CHEETAH_PLUS_NUC
mdefine_line|#define CTX_CHEETAH_PLUS_NUC &bslash;&n;&t;((CTX_PGSZ_KERN &lt;&lt; CTX_PGSZ0_NUC_SHIFT) | &bslash;&n;&t; (CTX_PGSZ_BASE &lt;&lt; CTX_PGSZ1_NUC_SHIFT))
DECL|macro|CTX_CHEETAH_PLUS_CTX0
mdefine_line|#define CTX_CHEETAH_PLUS_CTX0 &bslash;&n;&t;((CTX_PGSZ_KERN &lt;&lt; CTX_PGSZ0_SHIFT) | &bslash;&n;&t; (CTX_PGSZ_BASE &lt;&lt; CTX_PGSZ1_SHIFT))
multiline_comment|/* If you want &quot;the TLB context number&quot; use CTX_NR_MASK.  If you&n; * want &quot;the bits I program into the context registers&quot; use&n; * CTX_HW_MASK.&n; */
DECL|macro|CTX_NR_MASK
mdefine_line|#define CTX_NR_MASK&t;&t;TAG_CONTEXT_BITS
DECL|macro|CTX_HW_MASK
mdefine_line|#define CTX_HW_MASK&t;&t;(CTX_NR_MASK | CTX_PGSZ_MASK)
DECL|macro|CTX_FIRST_VERSION
mdefine_line|#define CTX_FIRST_VERSION&t;((_AC(1,UL) &lt;&lt; CTX_VERSION_SHIFT) + _AC(1,UL))
DECL|macro|CTX_VALID
mdefine_line|#define CTX_VALID(__ctx)&t;&bslash;&n;&t; (!(((__ctx.sparc64_ctx_val) ^ tlb_context_cache) &amp; CTX_VERSION_MASK))
DECL|macro|CTX_HWBITS
mdefine_line|#define CTX_HWBITS(__ctx)&t;((__ctx.sparc64_ctx_val) &amp; CTX_HW_MASK)
DECL|macro|CTX_NRBITS
mdefine_line|#define CTX_NRBITS(__ctx)&t;((__ctx.sparc64_ctx_val) &amp; CTX_NR_MASK)
macro_line|#ifndef __ASSEMBLY__
r_typedef
r_struct
(brace
DECL|member|sparc64_ctx_val
r_int
r_int
id|sparc64_ctx_val
suffix:semicolon
DECL|typedef|mm_context_t
)brace
id|mm_context_t
suffix:semicolon
macro_line|#endif /* !__ASSEMBLY__ */
macro_line|#endif /* __MMU_H */
eof
