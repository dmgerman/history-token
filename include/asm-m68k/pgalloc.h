macro_line|#ifndef M68K_PGALLOC_H
DECL|macro|M68K_PGALLOC_H
mdefine_line|#define M68K_PGALLOC_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/virtconvert.h&gt;
multiline_comment|/*&n; * Cache handling functions&n; */
DECL|macro|flush_icache
mdefine_line|#define flush_icache()&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (CPU_IS_040_OR_060)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__asm__ __volatile__(&quot;nop&bslash;n&bslash;t&quot;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;     &quot;.chip 68040&bslash;n&bslash;t&quot;&t;&t;&bslash;&n;&t;&t;&t;&t;     &quot;cinva %%ic&bslash;n&bslash;t&quot;&t;&t;&bslash;&n;&t;&t;&t;&t;     &quot;.chip 68k&quot; : );&t;&t;&bslash;&n;&t;else {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;unsigned long _tmp;&t;&t;&t;&t;&bslash;&n;&t;&t;__asm__ __volatile__(&quot;movec %%cacr,%0&bslash;n&bslash;t&quot;&t;&bslash;&n;&t;&t;&t;&t;     &quot;orw %1,%0&bslash;n&bslash;t&quot;&t;&t;&bslash;&n;&t;&t;&t;&t;     &quot;movec %0,%%cacr&quot;&t;&t;&bslash;&n;&t;&t;&t;&t;     : &quot;=&amp;d&quot; (_tmp)&t;&t;&bslash;&n;&t;&t;&t;&t;     : &quot;id&quot; (FLUSH_I));&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
multiline_comment|/*&n; * invalidate the cache for the specified memory range.&n; * It starts at the physical address specified for&n; * the given number of bytes.&n; */
r_extern
r_void
id|cache_clear
c_func
(paren
r_int
r_int
id|paddr
comma
r_int
id|len
)paren
suffix:semicolon
multiline_comment|/*&n; * push any dirty cache in the specified memory range.&n; * It starts at the physical address specified for&n; * the given number of bytes.&n; */
r_extern
r_void
id|cache_push
c_func
(paren
r_int
r_int
id|paddr
comma
r_int
id|len
)paren
suffix:semicolon
multiline_comment|/*&n; * push and invalidate pages in the specified user virtual&n; * memory range.&n; */
r_extern
r_void
id|cache_push_v
c_func
(paren
r_int
r_int
id|vaddr
comma
r_int
id|len
)paren
suffix:semicolon
multiline_comment|/* cache code */
DECL|macro|FLUSH_I_AND_D
mdefine_line|#define FLUSH_I_AND_D&t;(0x00000808)
DECL|macro|FLUSH_I
mdefine_line|#define FLUSH_I &t;(0x00000008)
multiline_comment|/* This is needed whenever the virtual mapping of the current&n;   process changes.  */
DECL|macro|__flush_cache_all
mdefine_line|#define __flush_cache_all()&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (CPU_IS_040_OR_060)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__asm__ __volatile__(&quot;nop&bslash;n&bslash;t&quot;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;     &quot;.chip 68040&bslash;n&bslash;t&quot;&t;&t;&bslash;&n;&t;&t;&t;&t;     &quot;cpusha %dc&bslash;n&bslash;t&quot;&t;&t;&bslash;&n;&t;&t;&t;&t;     &quot;.chip 68k&quot;);&t;&t;&bslash;&n;&t;else {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;unsigned long _tmp;&t;&t;&t;&t;&bslash;&n;&t;&t;__asm__ __volatile__(&quot;movec %%cacr,%0&bslash;n&bslash;t&quot;&t;&bslash;&n;&t;&t;&t;&t;     &quot;orw %1,%0&bslash;n&bslash;t&quot;&t;&t;&bslash;&n;&t;&t;&t;&t;     &quot;movec %0,%%cacr&quot;&t;&t;&bslash;&n;&t;&t;&t;&t;     : &quot;=&amp;d&quot; (_tmp)&t;&t;&bslash;&n;&t;&t;&t;&t;     : &quot;di&quot; (FLUSH_I_AND_D));&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|__flush_cache_030
mdefine_line|#define __flush_cache_030()&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (CPU_IS_020_OR_030) {&t;&t;&t;&t;&bslash;&n;&t;&t;unsigned long _tmp;&t;&t;&t;&t;&bslash;&n;&t;&t;__asm__ __volatile__(&quot;movec %%cacr,%0&bslash;n&bslash;t&quot;&t;&bslash;&n;&t;&t;&t;&t;     &quot;orw %1,%0&bslash;n&bslash;t&quot;&t;&t;&bslash;&n;&t;&t;&t;&t;     &quot;movec %0,%%cacr&quot;&t;&t;&bslash;&n;&t;&t;&t;&t;     : &quot;=&amp;d&quot; (_tmp)&t;&t;&bslash;&n;&t;&t;&t;&t;     : &quot;di&quot; (FLUSH_I_AND_D));&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|flush_cache_all
mdefine_line|#define flush_cache_all() __flush_cache_all()
DECL|function|flush_cache_mm
r_extern
r_inline
r_void
id|flush_cache_mm
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
(brace
r_if
c_cond
(paren
id|mm
op_eq
id|current-&gt;mm
)paren
id|__flush_cache_030
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|flush_cache_range
r_extern
r_inline
r_void
id|flush_cache_range
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
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
r_if
c_cond
(paren
id|vma-&gt;vm_mm
op_eq
id|current-&gt;mm
)paren
id|__flush_cache_030
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|flush_cache_page
r_extern
r_inline
r_void
id|flush_cache_page
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|vmaddr
)paren
(brace
r_if
c_cond
(paren
id|vma-&gt;vm_mm
op_eq
id|current-&gt;mm
)paren
id|__flush_cache_030
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Push the page at kernel virtual address and clear the icache */
multiline_comment|/* RZ: use cpush %bc instead of cpush %dc, cinv %ic */
DECL|macro|flush_page_to_ram
mdefine_line|#define flush_page_to_ram(page) __flush_page_to_ram((unsigned long) page_address(page))
DECL|function|__flush_page_to_ram
r_extern
r_inline
r_void
id|__flush_page_to_ram
c_func
(paren
r_int
r_int
id|address
)paren
(brace
r_if
c_cond
(paren
id|CPU_IS_040_OR_060
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;nop&bslash;n&bslash;t&quot;
l_string|&quot;.chip 68040&bslash;n&bslash;t&quot;
l_string|&quot;cpushp %%bc,(%0)&bslash;n&bslash;t&quot;
l_string|&quot;.chip 68k&quot;
suffix:colon
suffix:colon
l_string|&quot;a&quot;
(paren
id|__pa
c_func
(paren
(paren
r_void
op_star
)paren
id|address
)paren
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
r_int
r_int
id|_tmp
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;movec %%cacr,%0&bslash;n&bslash;t&quot;
l_string|&quot;orw %1,%0&bslash;n&bslash;t&quot;
l_string|&quot;movec %0,%%cacr&quot;
suffix:colon
l_string|&quot;=&amp;d&quot;
(paren
id|_tmp
)paren
suffix:colon
l_string|&quot;di&quot;
(paren
id|FLUSH_I
)paren
)paren
suffix:semicolon
)brace
)brace
DECL|macro|flush_dcache_page
mdefine_line|#define flush_dcache_page(page)&t;&t;&t;do { } while (0)
DECL|macro|flush_icache_page
mdefine_line|#define flush_icache_page(vma,pg)              do { } while (0)
DECL|macro|flush_icache_user_range
mdefine_line|#define flush_icache_user_range(vma,pg,adr,len)&t;do { } while (0)
multiline_comment|/* Push n pages at kernel virtual address and clear the icache */
multiline_comment|/* RZ: use cpush %bc instead of cpush %dc, cinv %ic */
DECL|function|flush_icache_range
r_extern
r_inline
r_void
id|flush_icache_range
(paren
r_int
r_int
id|address
comma
r_int
r_int
id|endaddr
)paren
(brace
r_if
c_cond
(paren
id|CPU_IS_040_OR_060
)paren
(brace
r_int
id|n
op_assign
(paren
id|endaddr
op_minus
id|address
op_plus
id|PAGE_SIZE
op_minus
l_int|1
)paren
op_div
id|PAGE_SIZE
suffix:semicolon
r_while
c_loop
(paren
op_decrement
id|n
op_ge
l_int|0
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;nop&bslash;n&bslash;t&quot;
l_string|&quot;.chip 68040&bslash;n&bslash;t&quot;
l_string|&quot;cpushp %%bc,(%0)&bslash;n&bslash;t&quot;
l_string|&quot;.chip 68k&quot;
suffix:colon
suffix:colon
l_string|&quot;a&quot;
(paren
id|virt_to_phys
c_func
(paren
(paren
r_void
op_star
)paren
id|address
)paren
)paren
)paren
suffix:semicolon
id|address
op_add_assign
id|PAGE_SIZE
suffix:semicolon
)brace
)brace
r_else
(brace
r_int
r_int
id|tmp
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;movec %%cacr,%0&bslash;n&bslash;t&quot;
l_string|&quot;orw %1,%0&bslash;n&bslash;t&quot;
l_string|&quot;movec %0,%%cacr&quot;
suffix:colon
l_string|&quot;=&amp;d&quot;
(paren
id|tmp
)paren
suffix:colon
l_string|&quot;di&quot;
(paren
id|FLUSH_I
)paren
)paren
suffix:semicolon
)brace
)brace
macro_line|#ifdef CONFIG_SUN3
macro_line|#include &lt;asm/sun3_pgalloc.h&gt;
macro_line|#else
macro_line|#include &lt;asm/motorola_pgalloc.h&gt;
macro_line|#endif
macro_line|#endif /* M68K_PGALLOC_H */
eof
