macro_line|#ifndef _PARISC_PGTABLE_H
DECL|macro|_PARISC_PGTABLE_H
mdefine_line|#define _PARISC_PGTABLE_H
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/*&n; * we simulate an x86-style page table for the linux mm code&n; */
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/fixmap.h&gt;
macro_line|#include &lt;asm/cache.h&gt;
multiline_comment|/* To make 53c7xx.c happy */
DECL|macro|IOMAP_FULL_CACHING
mdefine_line|#define IOMAP_FULL_CACHING&t;2&t;&t;/* used for &squot;what&squot; below */
DECL|macro|IOMAP_NOCACHE_SER
mdefine_line|#define IOMAP_NOCACHE_SER&t;3
r_extern
r_void
id|kernel_set_cachemode
c_func
(paren
r_int
r_int
id|addr
comma
r_int
r_int
id|size
comma
r_int
id|what
)paren
suffix:semicolon
multiline_comment|/*&n; * cache_clear() semantics: Clear any cache entries for the area in question,&n; * without writing back dirty entries first. This is useful if the data will&n; * be overwritten anyway, e.g. by DMA to memory. The range is defined by a&n; * _physical_ address.&n; */
DECL|macro|cache_clear
mdefine_line|#define cache_clear(paddr, len)&t;&t;&t;do { } while (0)
multiline_comment|/*&n; * cache_push() semantics: Write back any dirty cache data in the given area,&n; * and invalidate the range in the instruction cache. It needs not (but may)&n; * invalidate those entries also in the data cache. The range is defined by a&n; * _physical_ address.&n; */
DECL|macro|cache_push
mdefine_line|#define cache_push(paddr, len) &bslash;&n;&t;do { &bslash;&n;&t;&t;unsigned long vaddr = phys_to_virt(paddr); &bslash;&n;&t;&t;flush_cache_range(0, vaddr, vaddr + len); &bslash;&n;&t;} while(0)
DECL|macro|cache_push_v
mdefine_line|#define cache_push_v(vaddr, len) &bslash;&n;&t;&t;&t;flush_cache_range(0, vaddr, vaddr + len)
multiline_comment|/*&n; * kern_addr_valid(ADDR) tests if ADDR is pointing to valid kernel&n; * memory.  For the return value to be meaningful, ADDR must be &gt;=&n; * PAGE_OFFSET.  This operation can be relatively expensive (e.g.,&n; * require a hash-, or multi-level tree-lookup or something of that&n; * sort) but it guarantees to return TRUE only if accessing the page&n; * at that address does not cause an error.  Note that there may be&n; * addresses for which kern_addr_valid() returns FALSE even though an&n; * access would not cause an error (e.g., this is typically true for&n; * memory mapped I/O regions.&n; *&n; * XXX Need to implement this for parisc.&n; */
DECL|macro|kern_addr_valid
mdefine_line|#define kern_addr_valid(addr)&t;(1)
multiline_comment|/* Certain architectures need to do special things when PTEs&n; * within a page table are directly modified.  Thus, the following&n; * hook is made available.&n; */
DECL|macro|set_pte
mdefine_line|#define set_pte(pteptr, pteval)                                 &bslash;&n;        do{                                                     &bslash;&n;                *(pteptr) = (pteval);                           &bslash;&n;        } while(0)
macro_line|#endif /* !__ASSEMBLY__ */
DECL|macro|pte_ERROR
mdefine_line|#define pte_ERROR(e) &bslash;&n;&t;printk(&quot;%s:%d: bad pte %08lx.&bslash;n&quot;, __FILE__, __LINE__, pte_val(e))
DECL|macro|pmd_ERROR
mdefine_line|#define pmd_ERROR(e) &bslash;&n;&t;printk(&quot;%s:%d: bad pmd %08lx.&bslash;n&quot;, __FILE__, __LINE__, pmd_val(e))
DECL|macro|pgd_ERROR
mdefine_line|#define pgd_ERROR(e) &bslash;&n;&t;printk(&quot;%s:%d: bad pgd %08lx.&bslash;n&quot;, __FILE__, __LINE__, pgd_val(e))
multiline_comment|/*&n; * pgd entries used up by user/kernel:&n; */
DECL|macro|USER_PGD_PTRS
mdefine_line|#define USER_PGD_PTRS (PAGE_OFFSET &gt;&gt; PGDIR_SHIFT)
DECL|macro|FIRST_USER_PGD_NR
mdefine_line|#define FIRST_USER_PGD_NR&t;0
macro_line|#ifndef __ASSEMBLY__
r_extern
r_void
op_star
id|vmalloc_start
suffix:semicolon
DECL|macro|PCXL_DMA_MAP_SIZE
mdefine_line|#define PCXL_DMA_MAP_SIZE   (8*1024*1024)
DECL|macro|VMALLOC_START
mdefine_line|#define VMALLOC_START   ((unsigned long)vmalloc_start)
DECL|macro|VMALLOC_VMADDR
mdefine_line|#define VMALLOC_VMADDR(x) ((unsigned long)(x))
DECL|macro|VMALLOC_END
mdefine_line|#define VMALLOC_END&t;(FIXADDR_START)
macro_line|#endif
DECL|macro|_PAGE_READ
mdefine_line|#define _PAGE_READ&t;0x001&t;/* read access allowed */
DECL|macro|_PAGE_WRITE
mdefine_line|#define _PAGE_WRITE&t;0x002&t;/* write access allowed */
DECL|macro|_PAGE_EXEC
mdefine_line|#define _PAGE_EXEC&t;0x004&t;/* execute access allowed */
DECL|macro|_PAGE_GATEWAY
mdefine_line|#define _PAGE_GATEWAY&t;0x008&t;/* privilege promotion allowed */
DECL|macro|_PAGE_GATEWAY_BIT
mdefine_line|#define _PAGE_GATEWAY_BIT 28&t;/* _PAGE_GATEWAY &amp; _PAGE_GATEWAY_BIT need */
multiline_comment|/* to agree. One could be defined in relation */
multiline_comment|/* to the other, but that&squot;s kind of ugly. */
multiline_comment|/* 0x010 reserved (B bit) */
DECL|macro|_PAGE_DIRTY
mdefine_line|#define _PAGE_DIRTY&t;0x020&t;/* D: dirty */
multiline_comment|/* 0x040 reserved (T bit) */
DECL|macro|_PAGE_NO_CACHE
mdefine_line|#define _PAGE_NO_CACHE  0x080   /* Software: Uncacheable */
DECL|macro|_PAGE_NO_CACHE_BIT
mdefine_line|#define _PAGE_NO_CACHE_BIT 24   /* Needs to agree with _PAGE_NO_CACHE above */
DECL|macro|_PAGE_ACCESSED
mdefine_line|#define _PAGE_ACCESSED&t;0x100&t;/* R: page cache referenced */
DECL|macro|_PAGE_PRESENT
mdefine_line|#define _PAGE_PRESENT   0x200   /* Software: pte contains a translation */
DECL|macro|_PAGE_PRESENT_BIT
mdefine_line|#define _PAGE_PRESENT_BIT  22   /* Needs to agree with _PAGE_PRESENT above */
DECL|macro|_PAGE_USER
mdefine_line|#define _PAGE_USER      0x400   /* Software: User accessable page */
DECL|macro|_PAGE_USER_BIT
mdefine_line|#define _PAGE_USER_BIT     21   /* Needs to agree with _PAGE_USER above */
multiline_comment|/* 0x800 still available */
macro_line|#ifdef __ASSEMBLY__
DECL|macro|_PGB_
mdefine_line|#define _PGB_(x)&t;(1 &lt;&lt; (63 - (x)))
DECL|macro|__PAGE_O
mdefine_line|#define __PAGE_O&t;_PGB_(13)
DECL|macro|__PAGE_U
mdefine_line|#define __PAGE_U&t;_PGB_(12)
DECL|macro|__PAGE_T
mdefine_line|#define __PAGE_T&t;_PGB_(2)
DECL|macro|__PAGE_D
mdefine_line|#define __PAGE_D&t;_PGB_(3)
DECL|macro|__PAGE_B
mdefine_line|#define __PAGE_B&t;_PGB_(4)
DECL|macro|__PAGE_P
mdefine_line|#define __PAGE_P&t;_PGB_(14)
macro_line|#endif
DECL|macro|_PAGE_TABLE
mdefine_line|#define _PAGE_TABLE&t;(_PAGE_PRESENT | _PAGE_READ | _PAGE_WRITE |  _PAGE_DIRTY | _PAGE_ACCESSED)
DECL|macro|_PAGE_CHG_MASK
mdefine_line|#define _PAGE_CHG_MASK&t;(PAGE_MASK | _PAGE_ACCESSED | _PAGE_DIRTY)
DECL|macro|_PAGE_KERNEL
mdefine_line|#define _PAGE_KERNEL&t;(_PAGE_PRESENT | _PAGE_EXEC | _PAGE_READ | _PAGE_WRITE | _PAGE_DIRTY | _PAGE_ACCESSED)
macro_line|#ifndef __ASSEMBLY__
DECL|macro|PAGE_NONE
mdefine_line|#define PAGE_NONE&t;__pgprot(_PAGE_PRESENT | _PAGE_USER | _PAGE_ACCESSED)
DECL|macro|PAGE_SHARED
mdefine_line|#define PAGE_SHARED&t;__pgprot(_PAGE_PRESENT | _PAGE_USER | _PAGE_READ | _PAGE_WRITE | _PAGE_ACCESSED)
multiline_comment|/* Others seem to make this executable, I don&squot;t know if that&squot;s correct&n;   or not.  The stack is mapped this way though so this is necessary&n;   in the short term - dhd@linuxcare.com, 2000-08-08 */
DECL|macro|PAGE_READONLY
mdefine_line|#define PAGE_READONLY&t;__pgprot(_PAGE_PRESENT | _PAGE_USER | _PAGE_READ | _PAGE_ACCESSED)
DECL|macro|PAGE_WRITEONLY
mdefine_line|#define PAGE_WRITEONLY  __pgprot(_PAGE_PRESENT | _PAGE_USER | _PAGE_WRITE | _PAGE_ACCESSED)
DECL|macro|PAGE_EXECREAD
mdefine_line|#define PAGE_EXECREAD   __pgprot(_PAGE_PRESENT | _PAGE_USER | _PAGE_READ | _PAGE_EXEC |_PAGE_ACCESSED)
DECL|macro|PAGE_COPY
mdefine_line|#define PAGE_COPY       PAGE_EXECREAD
DECL|macro|PAGE_RWX
mdefine_line|#define PAGE_RWX        __pgprot(_PAGE_PRESENT | _PAGE_USER | _PAGE_READ | _PAGE_WRITE | _PAGE_EXEC |_PAGE_ACCESSED)
DECL|macro|PAGE_KERNEL
mdefine_line|#define PAGE_KERNEL&t;__pgprot(_PAGE_KERNEL)
DECL|macro|PAGE_KERNEL_RO
mdefine_line|#define PAGE_KERNEL_RO&t;__pgprot(_PAGE_PRESENT | _PAGE_EXEC | _PAGE_READ | _PAGE_DIRTY | _PAGE_ACCESSED)
DECL|macro|PAGE_KERNEL_UNC
mdefine_line|#define PAGE_KERNEL_UNC&t;__pgprot(_PAGE_KERNEL | _PAGE_NO_CACHE)
DECL|macro|PAGE_GATEWAY
mdefine_line|#define PAGE_GATEWAY    __pgprot(_PAGE_PRESENT | _PAGE_USER | _PAGE_ACCESSED | _PAGE_GATEWAY| _PAGE_READ)
multiline_comment|/*&n; * We could have an execute only page using &quot;gateway - promote to priv&n; * level 3&quot;, but that is kind of silly. So, the way things are defined&n; * now, we must always have read permission for pages with execute&n; * permission. For the fun of it we&squot;ll go ahead and support write only&n; * pages.&n; */
multiline_comment|/*xwr*/
DECL|macro|__P000
mdefine_line|#define __P000  PAGE_NONE
DECL|macro|__P001
mdefine_line|#define __P001  PAGE_READONLY
DECL|macro|__P010
mdefine_line|#define __P010  __P000 /* copy on write */
DECL|macro|__P011
mdefine_line|#define __P011  __P001 /* copy on write */
DECL|macro|__P100
mdefine_line|#define __P100  PAGE_EXECREAD
DECL|macro|__P101
mdefine_line|#define __P101  PAGE_EXECREAD
DECL|macro|__P110
mdefine_line|#define __P110  __P100 /* copy on write */
DECL|macro|__P111
mdefine_line|#define __P111  __P101 /* copy on write */
DECL|macro|__S000
mdefine_line|#define __S000  PAGE_NONE
DECL|macro|__S001
mdefine_line|#define __S001  PAGE_READONLY
DECL|macro|__S010
mdefine_line|#define __S010  PAGE_WRITEONLY
DECL|macro|__S011
mdefine_line|#define __S011  PAGE_SHARED
DECL|macro|__S100
mdefine_line|#define __S100  PAGE_EXECREAD
DECL|macro|__S101
mdefine_line|#define __S101  PAGE_EXECREAD
DECL|macro|__S110
mdefine_line|#define __S110  PAGE_RWX
DECL|macro|__S111
mdefine_line|#define __S111  PAGE_RWX
r_extern
r_int
r_int
id|swapper_pg_dir
(braket
)braket
suffix:semicolon
multiline_comment|/* declared in init_task.c */
multiline_comment|/* initial page tables for 0-8MB for kernel */
r_extern
r_int
r_int
id|pg0
(braket
)braket
suffix:semicolon
multiline_comment|/* zero page used for uninitialized stuff */
r_extern
r_int
r_int
op_star
id|empty_zero_page
suffix:semicolon
multiline_comment|/*&n; * BAD_PAGETABLE is used when we need a bogus page-table, while&n; * BAD_PAGE is used for a bogus page.&n; *&n; * ZERO_PAGE is a global shared page that is always zero: used&n; * for zero-mapped memory areas etc..&n; */
r_extern
id|pte_t
id|__bad_page
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
id|pte_t
op_star
id|__bad_pagetable
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|BAD_PAGETABLE
mdefine_line|#define BAD_PAGETABLE __bad_pagetable()
DECL|macro|BAD_PAGE
mdefine_line|#define BAD_PAGE __bad_page()
DECL|macro|ZERO_PAGE
mdefine_line|#define ZERO_PAGE(vaddr) (virt_to_page(empty_zero_page))
DECL|macro|pte_none
mdefine_line|#define pte_none(x)&t;(!pte_val(x))
DECL|macro|pte_present
mdefine_line|#define pte_present(x)&t;(pte_val(x) &amp; _PAGE_PRESENT)
DECL|macro|pte_clear
mdefine_line|#define pte_clear(xp)&t;do { pte_val(*(xp)) = 0; } while (0)
DECL|macro|pte_pagenr
mdefine_line|#define pte_pagenr(x)&t;((unsigned long)((pte_val(x) &gt;&gt; PAGE_SHIFT)))
DECL|macro|pmd_none
mdefine_line|#define pmd_none(x)&t;(!pmd_val(x))
DECL|macro|pmd_bad
mdefine_line|#define pmd_bad(x)&t;((pmd_val(x) &amp; ~PAGE_MASK) != _PAGE_TABLE)
DECL|macro|pmd_present
mdefine_line|#define pmd_present(x)&t;(pmd_val(x) &amp; _PAGE_PRESENT)
DECL|macro|pmd_clear
mdefine_line|#define pmd_clear(xp)&t;do { pmd_val(*(xp)) = 0; } while (0)
macro_line|#ifdef __LP64__
DECL|macro|pgd_page
mdefine_line|#define pgd_page(pgd) ((unsigned long) __va(pgd_val(pgd) &amp; PAGE_MASK))
multiline_comment|/* For 64 bit we have three level tables */
DECL|macro|pgd_none
mdefine_line|#define pgd_none(x)     (!pgd_val(x))
DECL|macro|pgd_bad
mdefine_line|#define pgd_bad(x)      ((pgd_val(x) &amp; ~PAGE_MASK) != _PAGE_TABLE)
DECL|macro|pgd_present
mdefine_line|#define pgd_present(x)  (pgd_val(x) &amp; _PAGE_PRESENT)
DECL|macro|pgd_clear
mdefine_line|#define pgd_clear(xp)   do { pgd_val(*(xp)) = 0; } while (0)
macro_line|#else
multiline_comment|/*&n; * The &quot;pgd_xxx()&quot; functions here are trivial for a folded two-level&n; * setup: the pgd is never bad, and a pmd always exists (as it&squot;s folded&n; * into the pgd entry)&n; */
DECL|function|pgd_none
r_extern
r_inline
r_int
id|pgd_none
c_func
(paren
id|pgd_t
id|pgd
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pgd_bad
r_extern
r_inline
r_int
id|pgd_bad
c_func
(paren
id|pgd_t
id|pgd
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pgd_present
r_extern
r_inline
r_int
id|pgd_present
c_func
(paren
id|pgd_t
id|pgd
)paren
(brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|pgd_clear
r_extern
r_inline
r_void
id|pgd_clear
c_func
(paren
id|pgd_t
op_star
id|pgdp
)paren
(brace
)brace
macro_line|#endif
multiline_comment|/*&n; * The following only work if pte_present() is true.&n; * Undefined behaviour if not..&n; */
DECL|function|pte_read
r_extern
r_inline
r_int
id|pte_read
c_func
(paren
id|pte_t
id|pte
)paren
(brace
r_return
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
id|_PAGE_READ
suffix:semicolon
)brace
DECL|function|pte_dirty
r_extern
r_inline
r_int
id|pte_dirty
c_func
(paren
id|pte_t
id|pte
)paren
(brace
r_return
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
id|_PAGE_DIRTY
suffix:semicolon
)brace
DECL|function|pte_young
r_extern
r_inline
r_int
id|pte_young
c_func
(paren
id|pte_t
id|pte
)paren
(brace
r_return
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
id|_PAGE_ACCESSED
suffix:semicolon
)brace
DECL|function|pte_write
r_extern
r_inline
r_int
id|pte_write
c_func
(paren
id|pte_t
id|pte
)paren
(brace
r_return
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
id|_PAGE_WRITE
suffix:semicolon
)brace
DECL|function|pte_rdprotect
r_extern
r_inline
id|pte_t
id|pte_rdprotect
c_func
(paren
id|pte_t
id|pte
)paren
(brace
id|pte_val
c_func
(paren
id|pte
)paren
op_and_assign
op_complement
id|_PAGE_READ
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|function|pte_mkclean
r_extern
r_inline
id|pte_t
id|pte_mkclean
c_func
(paren
id|pte_t
id|pte
)paren
(brace
id|pte_val
c_func
(paren
id|pte
)paren
op_and_assign
op_complement
id|_PAGE_DIRTY
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|function|pte_mkold
r_extern
r_inline
id|pte_t
id|pte_mkold
c_func
(paren
id|pte_t
id|pte
)paren
(brace
id|pte_val
c_func
(paren
id|pte
)paren
op_and_assign
op_complement
id|_PAGE_ACCESSED
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|function|pte_wrprotect
r_extern
r_inline
id|pte_t
id|pte_wrprotect
c_func
(paren
id|pte_t
id|pte
)paren
(brace
id|pte_val
c_func
(paren
id|pte
)paren
op_and_assign
op_complement
id|_PAGE_WRITE
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|function|pte_mkread
r_extern
r_inline
id|pte_t
id|pte_mkread
c_func
(paren
id|pte_t
id|pte
)paren
(brace
id|pte_val
c_func
(paren
id|pte
)paren
op_or_assign
id|_PAGE_READ
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|function|pte_mkdirty
r_extern
r_inline
id|pte_t
id|pte_mkdirty
c_func
(paren
id|pte_t
id|pte
)paren
(brace
id|pte_val
c_func
(paren
id|pte
)paren
op_or_assign
id|_PAGE_DIRTY
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|function|pte_mkyoung
r_extern
r_inline
id|pte_t
id|pte_mkyoung
c_func
(paren
id|pte_t
id|pte
)paren
(brace
id|pte_val
c_func
(paren
id|pte
)paren
op_or_assign
id|_PAGE_ACCESSED
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|function|pte_mkwrite
r_extern
r_inline
id|pte_t
id|pte_mkwrite
c_func
(paren
id|pte_t
id|pte
)paren
(brace
id|pte_val
c_func
(paren
id|pte
)paren
op_or_assign
id|_PAGE_WRITE
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
multiline_comment|/*&n; * Conversion functions: convert a page and protection to a page entry,&n; * and a page entry and page directory to the page they refer to.&n; */
DECL|macro|__mk_pte
mdefine_line|#define __mk_pte(addr,pgprot) &bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;pte_t __pte;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;pte_val(__pte) = ((addr)+pgprot_val(pgprot));&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__pte;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|mk_pte
mdefine_line|#define mk_pte(page,pgprot) &bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;pte_t __pte;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;pte_val(__pte) = ((page)-mem_map)*PAGE_SIZE +&t;&t;&t;&bslash;&n;&t;&t;&t;&t;pgprot_val(pgprot);&t;&t;&t;&bslash;&n;&t;__pte;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
multiline_comment|/* This takes a physical page address that is used by the remapping functions */
DECL|macro|mk_pte_phys
mdefine_line|#define mk_pte_phys(physpage, pgprot) &bslash;&n;({ pte_t __pte; pte_val(__pte) = physpage + pgprot_val(pgprot); __pte; })
DECL|function|pte_modify
r_extern
r_inline
id|pte_t
id|pte_modify
c_func
(paren
id|pte_t
id|pte
comma
id|pgprot_t
id|newprot
)paren
(brace
id|pte_val
c_func
(paren
id|pte
)paren
op_assign
(paren
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
id|_PAGE_CHG_MASK
)paren
op_or
id|pgprot_val
c_func
(paren
id|newprot
)paren
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
multiline_comment|/*&n; * Permanent address of a page. Obviously must never be&n; * called on a highmem page.&n; */
DECL|macro|__page_address
mdefine_line|#define __page_address(page) ({ if (PageHighMem(page)) BUG(); PAGE_OFFSET + (((page) - mem_map) &lt;&lt; PAGE_SHIFT); })
DECL|macro|pages_to_mb
mdefine_line|#define pages_to_mb(x) ((x) &gt;&gt; (20-PAGE_SHIFT))
DECL|macro|pte_page
mdefine_line|#define pte_page(x) (mem_map+pte_pagenr(x))
DECL|macro|pmd_page
mdefine_line|#define pmd_page(pmd) ((unsigned long) __va(pmd_val(pmd) &amp; PAGE_MASK))
DECL|macro|pgd_index
mdefine_line|#define pgd_index(address) ((address) &gt;&gt; PGDIR_SHIFT)
multiline_comment|/* to find an entry in a page-table-directory */
DECL|macro|pgd_offset
mdefine_line|#define pgd_offset(mm, address) &bslash;&n;((mm)-&gt;pgd + ((address) &gt;&gt; PGDIR_SHIFT))
multiline_comment|/* to find an entry in a kernel page-table-directory */
DECL|macro|pgd_offset_k
mdefine_line|#define pgd_offset_k(address) pgd_offset(&amp;init_mm, address)
multiline_comment|/* Find an entry in the second-level page table.. */
macro_line|#ifdef __LP64__
DECL|macro|pmd_offset
mdefine_line|#define pmd_offset(dir,address) &bslash;&n;((pmd_t *) pgd_page(*(dir)) + (((address)&gt;&gt;PMD_SHIFT) &amp; (PTRS_PER_PMD-1)))
macro_line|#else
DECL|macro|pmd_offset
mdefine_line|#define pmd_offset(dir,addr) ((pmd_t *) dir)
macro_line|#endif
multiline_comment|/* Find an entry in the third-level page table.. */
DECL|macro|pte_offset
mdefine_line|#define pte_offset(pmd, address) &bslash;&n;((pte_t *) pmd_page(*(pmd)) + (((address)&gt;&gt;PAGE_SHIFT) &amp; (PTRS_PER_PTE-1)))
r_extern
r_void
id|paging_init
(paren
r_void
)paren
suffix:semicolon
DECL|function|update_mmu_cache
r_extern
r_inline
r_void
id|update_mmu_cache
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|address
comma
id|pte_t
id|pte
)paren
(brace
)brace
multiline_comment|/* Encode and de-code a swap entry */
DECL|macro|SWP_TYPE
mdefine_line|#define SWP_TYPE(x)                     ((x).val &amp; 0x3f)
DECL|macro|SWP_OFFSET
mdefine_line|#define SWP_OFFSET(x)                   ( (((x).val &gt;&gt; 6) &amp;  0x7) | &bslash;&n;&t;&t;&t;&t;&t;  (((x).val &gt;&gt; 7) &amp; ~0x7) )
DECL|macro|SWP_ENTRY
mdefine_line|#define SWP_ENTRY(type, offset)         ((swp_entry_t) { (type) | &bslash;&n;&t;&t;&t;&t;&t;    ((offset &amp;  0x7) &lt;&lt; 6) | &bslash;&n;&t;&t;&t;&t;&t;    ((offset &amp; ~0x7) &lt;&lt; 7) })
DECL|macro|pte_to_swp_entry
mdefine_line|#define pte_to_swp_entry(pte)&t;&t;((swp_entry_t) { pte_val(pte) })
DECL|macro|swp_entry_to_pte
mdefine_line|#define swp_entry_to_pte(x)&t;&t;((pte_t) { (x).val })
DECL|macro|module_map
mdefine_line|#define module_map&t;vmalloc
DECL|macro|module_unmap
mdefine_line|#define module_unmap&t;vfree
macro_line|#include &lt;asm-generic/pgtable.h&gt;
macro_line|#endif /* !__ASSEMBLY__ */
DECL|macro|io_remap_page_range
mdefine_line|#define io_remap_page_range remap_page_range
multiline_comment|/*&n; * No page table caches to initialise&n; */
DECL|macro|pgtable_cache_init
mdefine_line|#define pgtable_cache_init()&t;do { } while (0)
macro_line|#endif /* _PARISC_PAGE_H */
eof
