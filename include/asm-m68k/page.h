macro_line|#ifndef _M68K_PAGE_H
DECL|macro|_M68K_PAGE_H
mdefine_line|#define _M68K_PAGE_H
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/* PAGE_SHIFT determines the page size */
macro_line|#ifndef CONFIG_SUN3
DECL|macro|PAGE_SHIFT
mdefine_line|#define PAGE_SHIFT&t;(12)
DECL|macro|PAGE_SIZE
mdefine_line|#define PAGE_SIZE&t;(4096)
macro_line|#else
DECL|macro|PAGE_SHIFT
mdefine_line|#define PAGE_SHIFT&t;(13)
DECL|macro|PAGE_SIZE
mdefine_line|#define PAGE_SIZE&t;(8192)
macro_line|#endif
DECL|macro|PAGE_MASK
mdefine_line|#define PAGE_MASK&t;(~(PAGE_SIZE-1))
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#if PAGE_SHIFT &lt; 13
DECL|macro|THREAD_SIZE
mdefine_line|#define THREAD_SIZE (8192)
macro_line|#else
DECL|macro|THREAD_SIZE
mdefine_line|#define THREAD_SIZE PAGE_SIZE
macro_line|#endif
macro_line|#ifndef __ASSEMBLY__
DECL|macro|get_user_page
mdefine_line|#define get_user_page(vaddr)&t;&t;__get_free_page(GFP_KERNEL)
DECL|macro|free_user_page
mdefine_line|#define free_user_page(page, addr)&t;free_page(addr)
multiline_comment|/*&n; * We don&squot;t need to check for alignment etc.&n; */
macro_line|#ifdef CPU_M68040_OR_M68060_ONLY
DECL|function|copy_page
r_static
r_inline
r_void
id|copy_page
c_func
(paren
r_void
op_star
id|to
comma
r_void
op_star
id|from
)paren
(brace
r_int
r_int
id|tmp
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;1:&bslash;t&quot;
l_string|&quot;.chip 68040&bslash;n&bslash;t&quot;
l_string|&quot;move16 %1@+,%0@+&bslash;n&bslash;t&quot;
l_string|&quot;move16 %1@+,%0@+&bslash;n&bslash;t&quot;
l_string|&quot;.chip 68k&bslash;n&bslash;t&quot;
l_string|&quot;dbra  %2,1b&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|to
)paren
comma
l_string|&quot;=a&quot;
(paren
id|from
)paren
comma
l_string|&quot;=d&quot;
(paren
id|tmp
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|to
)paren
comma
l_string|&quot;1&quot;
(paren
id|from
)paren
comma
l_string|&quot;2&quot;
(paren
id|PAGE_SIZE
op_div
l_int|32
op_minus
l_int|1
)paren
)paren
suffix:semicolon
)brace
DECL|function|clear_page
r_static
r_inline
r_void
id|clear_page
c_func
(paren
r_void
op_star
id|page
)paren
(brace
r_int
r_int
id|data
comma
id|tmp
suffix:semicolon
r_void
op_star
id|sp
op_assign
id|page
suffix:semicolon
id|data
op_assign
l_int|0
suffix:semicolon
op_star
(paren
(paren
r_int
r_int
op_star
)paren
(paren
id|page
)paren
)paren
op_increment
op_assign
l_int|0
suffix:semicolon
op_star
(paren
(paren
r_int
r_int
op_star
)paren
(paren
id|page
)paren
)paren
op_increment
op_assign
l_int|0
suffix:semicolon
op_star
(paren
(paren
r_int
r_int
op_star
)paren
(paren
id|page
)paren
)paren
op_increment
op_assign
l_int|0
suffix:semicolon
op_star
(paren
(paren
r_int
r_int
op_star
)paren
(paren
id|page
)paren
)paren
op_increment
op_assign
l_int|0
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;1:&bslash;t&quot;
l_string|&quot;.chip 68040&bslash;n&bslash;t&quot;
l_string|&quot;move16 %2@+,%0@+&bslash;n&bslash;t&quot;
l_string|&quot;.chip 68k&bslash;n&bslash;t&quot;
l_string|&quot;subqw  #8,%2&bslash;n&bslash;t&quot;
l_string|&quot;subqw  #8,%2&bslash;n&bslash;t&quot;
l_string|&quot;dbra   %1,1b&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|page
)paren
comma
l_string|&quot;=d&quot;
(paren
id|tmp
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
id|sp
)paren
comma
l_string|&quot;0&quot;
(paren
id|page
)paren
comma
l_string|&quot;1&quot;
(paren
(paren
id|PAGE_SIZE
op_minus
l_int|16
)paren
op_div
l_int|16
op_minus
l_int|1
)paren
)paren
suffix:semicolon
)brace
macro_line|#else
DECL|macro|clear_page
mdefine_line|#define clear_page(page)&t;memset((page), 0, PAGE_SIZE)
DECL|macro|copy_page
mdefine_line|#define copy_page(to,from)&t;memcpy((to), (from), PAGE_SIZE)
macro_line|#endif
DECL|macro|clear_user_page
mdefine_line|#define clear_user_page(page, vaddr)&t;clear_page(page)
DECL|macro|copy_user_page
mdefine_line|#define copy_user_page(to, from, vaddr)&t;copy_page(to, from)
multiline_comment|/*&n; * These are used to make use of C type-checking..&n; */
DECL|member|pte
DECL|typedef|pte_t
r_typedef
r_struct
(brace
r_int
r_int
id|pte
suffix:semicolon
)brace
id|pte_t
suffix:semicolon
DECL|member|pmd
DECL|typedef|pmd_t
r_typedef
r_struct
(brace
r_int
r_int
id|pmd
(braket
l_int|16
)braket
suffix:semicolon
)brace
id|pmd_t
suffix:semicolon
DECL|member|pgd
DECL|typedef|pgd_t
r_typedef
r_struct
(brace
r_int
r_int
id|pgd
suffix:semicolon
)brace
id|pgd_t
suffix:semicolon
DECL|member|pgprot
DECL|typedef|pgprot_t
r_typedef
r_struct
(brace
r_int
r_int
id|pgprot
suffix:semicolon
)brace
id|pgprot_t
suffix:semicolon
DECL|macro|pte_val
mdefine_line|#define pte_val(x)&t;((x).pte)
DECL|macro|pmd_val
mdefine_line|#define pmd_val(x)&t;((&amp;x)-&gt;pmd[0])
DECL|macro|pgd_val
mdefine_line|#define pgd_val(x)&t;((x).pgd)
DECL|macro|pgprot_val
mdefine_line|#define pgprot_val(x)&t;((x).pgprot)
DECL|macro|__pte
mdefine_line|#define __pte(x)&t;((pte_t) { (x) } )
DECL|macro|__pmd
mdefine_line|#define __pmd(x)&t;((pmd_t) { (x) } )
DECL|macro|__pgd
mdefine_line|#define __pgd(x)&t;((pgd_t) { (x) } )
DECL|macro|__pgprot
mdefine_line|#define __pgprot(x)&t;((pgprot_t) { (x) } )
multiline_comment|/* to align the pointer to the (next) page boundary */
DECL|macro|PAGE_ALIGN
mdefine_line|#define PAGE_ALIGN(addr)&t;(((addr)+PAGE_SIZE-1)&amp;PAGE_MASK)
multiline_comment|/* Pure 2^n version of get_order */
DECL|function|get_order
r_extern
id|__inline__
r_int
id|get_order
c_func
(paren
r_int
r_int
id|size
)paren
(brace
r_int
id|order
suffix:semicolon
id|size
op_assign
(paren
id|size
op_minus
l_int|1
)paren
op_rshift
(paren
id|PAGE_SHIFT
op_minus
l_int|1
)paren
suffix:semicolon
id|order
op_assign
op_minus
l_int|1
suffix:semicolon
r_do
(brace
id|size
op_rshift_assign
l_int|1
suffix:semicolon
id|order
op_increment
suffix:semicolon
)brace
r_while
c_loop
(paren
id|size
)paren
suffix:semicolon
r_return
id|order
suffix:semicolon
)brace
macro_line|#endif /* !__ASSEMBLY__ */
macro_line|#include &lt;asm/page_offset.h&gt;
DECL|macro|PAGE_OFFSET
mdefine_line|#define PAGE_OFFSET&t;&t;(PAGE_OFFSET_RAW)
macro_line|#ifndef __ASSEMBLY__
macro_line|#ifndef CONFIG_SUN3
macro_line|#ifdef CONFIG_SINGLE_MEMORY_CHUNK
r_extern
r_int
r_int
id|m68k_memoffset
suffix:semicolon
DECL|macro|__pa
mdefine_line|#define __pa(vaddr)&t;&t;((unsigned long)(vaddr)+m68k_memoffset)
DECL|macro|__va
mdefine_line|#define __va(paddr)&t;&t;((void *)((unsigned long)(paddr)-m68k_memoffset))
macro_line|#else
DECL|macro|__pa
mdefine_line|#define __pa(vaddr)&t;&t;virt_to_phys((void *)vaddr)
DECL|macro|__va
mdefine_line|#define __va(paddr)&t;&t;phys_to_virt((unsigned long)paddr)
macro_line|#endif
macro_line|#else&t;/* !CONFIG_SUN3 */
multiline_comment|/* This #define is a horrible hack to suppress lots of warnings. --m */
DECL|macro|__pa
mdefine_line|#define __pa(x) ___pa((unsigned long)x)
DECL|function|___pa
r_static
r_inline
r_int
r_int
id|___pa
c_func
(paren
r_int
r_int
id|x
)paren
(brace
r_if
c_cond
(paren
id|x
op_eq
l_int|0
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|x
OG
id|PAGE_OFFSET
)paren
(brace
r_return
(paren
id|x
op_minus
id|PAGE_OFFSET
)paren
suffix:semicolon
)brace
r_else
r_return
(paren
id|x
op_plus
l_int|0x2000000
)paren
suffix:semicolon
)brace
DECL|function|__va
r_static
r_inline
r_void
op_star
id|__va
c_func
(paren
r_int
r_int
id|x
)paren
(brace
r_if
c_cond
(paren
id|x
op_eq
l_int|0
)paren
(brace
r_return
(paren
r_void
op_star
)paren
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|x
OL
l_int|0x2000000
)paren
(brace
r_return
(paren
r_void
op_star
)paren
(paren
id|x
op_plus
id|PAGE_OFFSET
)paren
suffix:semicolon
)brace
r_else
r_return
(paren
r_void
op_star
)paren
(paren
id|x
op_minus
l_int|0x2000000
)paren
suffix:semicolon
)brace
macro_line|#endif&t;/* CONFIG_SUN3 */
DECL|macro|MAP_NR
mdefine_line|#define MAP_NR(addr)&t;&t;(((unsigned long)(addr)-PAGE_OFFSET) &gt;&gt; PAGE_SHIFT)
DECL|macro|virt_to_page
mdefine_line|#define virt_to_page(kaddr)&t;(mem_map + (((unsigned long)(kaddr)-PAGE_OFFSET) &gt;&gt; PAGE_SHIFT))
DECL|macro|VALID_PAGE
mdefine_line|#define VALID_PAGE(page)&t;((page - mem_map) &lt; max_mapnr)
macro_line|#ifndef CONFIG_SUN3
DECL|macro|BUG
mdefine_line|#define BUG() do { &bslash;&n;&t;printk(&quot;kernel BUG at %s:%d!&bslash;n&quot;, __FILE__, __LINE__); &bslash;&n;&t;asm volatile(&quot;illegal&quot;); &bslash;&n;} while (0)
macro_line|#else
DECL|macro|BUG
mdefine_line|#define BUG() do { &bslash;&n;&t;printk(&quot;kernel BUG at %s:%d!&bslash;n&quot;, __FILE__, __LINE__); &bslash;&n;&t;panic(&quot;BUG!&quot;); &bslash;&n;} while (0)
macro_line|#endif
DECL|macro|PAGE_BUG
mdefine_line|#define PAGE_BUG(page) do { &bslash;&n;&t;BUG(); &bslash;&n;} while (0)
macro_line|#endif /* __ASSEMBLY__ */
DECL|macro|VM_DATA_DEFAULT_FLAGS
mdefine_line|#define VM_DATA_DEFAULT_FLAGS&t;(VM_READ | VM_WRITE | VM_EXEC | &bslash;&n;&t;&t;&t;&t; VM_MAYREAD | VM_MAYWRITE | VM_MAYEXEC)
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _M68K_PAGE_H */
eof
