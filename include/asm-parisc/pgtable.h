macro_line|#ifndef _PARISC_PGTABLE_H
DECL|macro|_PARISC_PGTABLE_H
mdefine_line|#define _PARISC_PGTABLE_H
macro_line|#include &lt;asm-generic/4level-fixup.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/fixmap.h&gt;
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/*&n; * we simulate an x86-style page table for the linux mm code&n; */
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/cache.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
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
mdefine_line|#define pmd_ERROR(e) &bslash;&n;&t;printk(&quot;%s:%d: bad pmd %08lx.&bslash;n&quot;, __FILE__, __LINE__, (unsigned long)pmd_val(e))
DECL|macro|pgd_ERROR
mdefine_line|#define pgd_ERROR(e) &bslash;&n;&t;printk(&quot;%s:%d: bad pgd %08lx.&bslash;n&quot;, __FILE__, __LINE__, (unsigned long)pgd_val(e))
multiline_comment|/* Note: If you change ISTACK_SIZE, you need to change the corresponding&n;  * values in vmlinux.lds and vmlinux64.lds (init_istack section). Also,&n;  * the &quot;order&quot; and size need to agree.&n;  */
DECL|macro|ISTACK_SIZE
mdefine_line|#define  ISTACK_SIZE  32768 /* Interrupt Stack Size */
DECL|macro|ISTACK_ORDER
mdefine_line|#define  ISTACK_ORDER 3
multiline_comment|/* This is the size of the initially mapped kernel memory (i.e. currently&n; * 0 to 1&lt;&lt;23 == 8MB */
macro_line|#ifdef CONFIG_64BIT
DECL|macro|KERNEL_INITIAL_ORDER
mdefine_line|#define KERNEL_INITIAL_ORDER&t;24
macro_line|#else
DECL|macro|KERNEL_INITIAL_ORDER
mdefine_line|#define KERNEL_INITIAL_ORDER&t;23
macro_line|#endif
DECL|macro|KERNEL_INITIAL_SIZE
mdefine_line|#define KERNEL_INITIAL_SIZE&t;(1 &lt;&lt; KERNEL_INITIAL_ORDER)
macro_line|#ifdef CONFIG_64BIT
DECL|macro|PT_NLEVELS
mdefine_line|#define PT_NLEVELS&t;3
DECL|macro|PGD_ORDER
mdefine_line|#define PGD_ORDER&t;1 /* Number of pages per pgd */
DECL|macro|PMD_ORDER
mdefine_line|#define PMD_ORDER&t;1 /* Number of pages per pmd */
DECL|macro|PGD_ALLOC_ORDER
mdefine_line|#define PGD_ALLOC_ORDER&t;2 /* first pgd contains pmd */
macro_line|#else
DECL|macro|PT_NLEVELS
mdefine_line|#define PT_NLEVELS&t;2
DECL|macro|PGD_ORDER
mdefine_line|#define PGD_ORDER&t;1 /* Number of pages per pgd */
DECL|macro|PGD_ALLOC_ORDER
mdefine_line|#define PGD_ALLOC_ORDER&t;PGD_ORDER
macro_line|#endif
multiline_comment|/* Definitions for 3rd level (we use PLD here for Page Lower directory&n; * because PTE_SHIFT is used lower down to mean shift that has to be&n; * done to get usable bits out of the PTE) */
DECL|macro|PLD_SHIFT
mdefine_line|#define PLD_SHIFT&t;PAGE_SHIFT
DECL|macro|PLD_SIZE
mdefine_line|#define PLD_SIZE&t;PAGE_SIZE
DECL|macro|BITS_PER_PTE
mdefine_line|#define BITS_PER_PTE&t;(PAGE_SHIFT - BITS_PER_PTE_ENTRY)
DECL|macro|PTRS_PER_PTE
mdefine_line|#define PTRS_PER_PTE    (1UL &lt;&lt; BITS_PER_PTE)
multiline_comment|/* Definitions for 2nd level */
DECL|macro|pgtable_cache_init
mdefine_line|#define pgtable_cache_init()&t;do { } while (0)
DECL|macro|PMD_SHIFT
mdefine_line|#define PMD_SHIFT       (PLD_SHIFT + BITS_PER_PTE)
DECL|macro|PMD_SIZE
mdefine_line|#define PMD_SIZE&t;(1UL &lt;&lt; PMD_SHIFT)
DECL|macro|PMD_MASK
mdefine_line|#define PMD_MASK&t;(~(PMD_SIZE-1))
macro_line|#if PT_NLEVELS == 3
DECL|macro|BITS_PER_PMD
mdefine_line|#define BITS_PER_PMD&t;(PAGE_SHIFT + PMD_ORDER - BITS_PER_PMD_ENTRY)
macro_line|#else
DECL|macro|BITS_PER_PMD
mdefine_line|#define BITS_PER_PMD&t;0
macro_line|#endif
DECL|macro|PTRS_PER_PMD
mdefine_line|#define PTRS_PER_PMD    (1UL &lt;&lt; BITS_PER_PMD)
multiline_comment|/* Definitions for 1st level */
DECL|macro|PGDIR_SHIFT
mdefine_line|#define PGDIR_SHIFT&t;(PMD_SHIFT + BITS_PER_PMD)
DECL|macro|BITS_PER_PGD
mdefine_line|#define BITS_PER_PGD&t;(PAGE_SHIFT + PGD_ORDER - BITS_PER_PGD_ENTRY)
DECL|macro|PGDIR_SIZE
mdefine_line|#define PGDIR_SIZE&t;(1UL &lt;&lt; PGDIR_SHIFT)
DECL|macro|PGDIR_MASK
mdefine_line|#define PGDIR_MASK&t;(~(PGDIR_SIZE-1))
DECL|macro|PTRS_PER_PGD
mdefine_line|#define PTRS_PER_PGD    (1UL &lt;&lt; BITS_PER_PGD)
DECL|macro|USER_PTRS_PER_PGD
mdefine_line|#define USER_PTRS_PER_PGD       PTRS_PER_PGD
DECL|macro|MAX_ADDRBITS
mdefine_line|#define MAX_ADDRBITS&t;(PGDIR_SHIFT + BITS_PER_PGD)
DECL|macro|MAX_ADDRESS
mdefine_line|#define MAX_ADDRESS&t;(1UL &lt;&lt; MAX_ADDRBITS)
DECL|macro|SPACEID_SHIFT
mdefine_line|#define SPACEID_SHIFT (MAX_ADDRBITS - 32)
multiline_comment|/* This calculates the number of initial pages we need for the initial&n; * page tables */
DECL|macro|PT_INITIAL
mdefine_line|#define PT_INITIAL&t;(1 &lt;&lt; (KERNEL_INITIAL_ORDER - PMD_SHIFT))
multiline_comment|/*&n; * pgd entries used up by user/kernel:&n; */
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
multiline_comment|/* this is a fixmap remnant, see fixmap.h */
DECL|macro|VMALLOC_END
mdefine_line|#define VMALLOC_END&t;(KERNEL_MAP_END)
macro_line|#endif
multiline_comment|/* NB: The tlb miss handlers make certain assumptions about the order */
multiline_comment|/*     of the following bits, so be careful (One example, bits 25-31  */
multiline_comment|/*     are moved together in one instruction).                        */
DECL|macro|_PAGE_READ_BIT
mdefine_line|#define _PAGE_READ_BIT     31   /* (0x001) read access allowed */
DECL|macro|_PAGE_WRITE_BIT
mdefine_line|#define _PAGE_WRITE_BIT    30   /* (0x002) write access allowed */
DECL|macro|_PAGE_EXEC_BIT
mdefine_line|#define _PAGE_EXEC_BIT     29   /* (0x004) execute access allowed */
DECL|macro|_PAGE_GATEWAY_BIT
mdefine_line|#define _PAGE_GATEWAY_BIT  28   /* (0x008) privilege promotion allowed */
DECL|macro|_PAGE_DMB_BIT
mdefine_line|#define _PAGE_DMB_BIT      27   /* (0x010) Data Memory Break enable (B bit) */
DECL|macro|_PAGE_DIRTY_BIT
mdefine_line|#define _PAGE_DIRTY_BIT    26   /* (0x020) Page Dirty (D bit) */
DECL|macro|_PAGE_FILE_BIT
mdefine_line|#define _PAGE_FILE_BIT&t;_PAGE_DIRTY_BIT&t;/* overload this bit */
DECL|macro|_PAGE_REFTRAP_BIT
mdefine_line|#define _PAGE_REFTRAP_BIT  25   /* (0x040) Page Ref. Trap enable (T bit) */
DECL|macro|_PAGE_NO_CACHE_BIT
mdefine_line|#define _PAGE_NO_CACHE_BIT 24   /* (0x080) Uncached Page (U bit) */
DECL|macro|_PAGE_ACCESSED_BIT
mdefine_line|#define _PAGE_ACCESSED_BIT 23   /* (0x100) Software: Page Accessed */
DECL|macro|_PAGE_PRESENT_BIT
mdefine_line|#define _PAGE_PRESENT_BIT  22   /* (0x200) Software: translation valid */
DECL|macro|_PAGE_FLUSH_BIT
mdefine_line|#define _PAGE_FLUSH_BIT    21   /* (0x400) Software: translation valid */
multiline_comment|/*             for cache flushing only */
DECL|macro|_PAGE_USER_BIT
mdefine_line|#define _PAGE_USER_BIT     20   /* (0x800) Software: User accessible page */
multiline_comment|/* N.B. The bits are defined in terms of a 32 bit word above, so the */
multiline_comment|/*      following macro is ok for both 32 and 64 bit.                */
DECL|macro|xlate_pabit
mdefine_line|#define xlate_pabit(x) (31 - x)
multiline_comment|/* this defines the shift to the usable bits in the PTE it is set so&n; * that the valid bits _PAGE_PRESENT_BIT and _PAGE_USER_BIT are set&n; * to zero */
DECL|macro|PTE_SHIFT
mdefine_line|#define PTE_SHIFT&t;   &t;xlate_pabit(_PAGE_USER_BIT)
multiline_comment|/* this is how many bits may be used by the file functions */
DECL|macro|PTE_FILE_MAX_BITS
mdefine_line|#define PTE_FILE_MAX_BITS&t;(BITS_PER_LONG - PTE_SHIFT)
DECL|macro|pte_to_pgoff
mdefine_line|#define pte_to_pgoff(pte) (pte_val(pte) &gt;&gt; PTE_SHIFT)
DECL|macro|pgoff_to_pte
mdefine_line|#define pgoff_to_pte(off) ((pte_t) { ((off) &lt;&lt; PTE_SHIFT) | _PAGE_FILE })
DECL|macro|_PAGE_READ
mdefine_line|#define _PAGE_READ     (1 &lt;&lt; xlate_pabit(_PAGE_READ_BIT))
DECL|macro|_PAGE_WRITE
mdefine_line|#define _PAGE_WRITE    (1 &lt;&lt; xlate_pabit(_PAGE_WRITE_BIT))
DECL|macro|_PAGE_RW
mdefine_line|#define _PAGE_RW       (_PAGE_READ | _PAGE_WRITE)
DECL|macro|_PAGE_EXEC
mdefine_line|#define _PAGE_EXEC     (1 &lt;&lt; xlate_pabit(_PAGE_EXEC_BIT))
DECL|macro|_PAGE_GATEWAY
mdefine_line|#define _PAGE_GATEWAY  (1 &lt;&lt; xlate_pabit(_PAGE_GATEWAY_BIT))
DECL|macro|_PAGE_DMB
mdefine_line|#define _PAGE_DMB      (1 &lt;&lt; xlate_pabit(_PAGE_DMB_BIT))
DECL|macro|_PAGE_DIRTY
mdefine_line|#define _PAGE_DIRTY    (1 &lt;&lt; xlate_pabit(_PAGE_DIRTY_BIT))
DECL|macro|_PAGE_REFTRAP
mdefine_line|#define _PAGE_REFTRAP  (1 &lt;&lt; xlate_pabit(_PAGE_REFTRAP_BIT))
DECL|macro|_PAGE_NO_CACHE
mdefine_line|#define _PAGE_NO_CACHE (1 &lt;&lt; xlate_pabit(_PAGE_NO_CACHE_BIT))
DECL|macro|_PAGE_ACCESSED
mdefine_line|#define _PAGE_ACCESSED (1 &lt;&lt; xlate_pabit(_PAGE_ACCESSED_BIT))
DECL|macro|_PAGE_PRESENT
mdefine_line|#define _PAGE_PRESENT  (1 &lt;&lt; xlate_pabit(_PAGE_PRESENT_BIT))
DECL|macro|_PAGE_FLUSH
mdefine_line|#define _PAGE_FLUSH    (1 &lt;&lt; xlate_pabit(_PAGE_FLUSH_BIT))
DECL|macro|_PAGE_USER
mdefine_line|#define _PAGE_USER     (1 &lt;&lt; xlate_pabit(_PAGE_USER_BIT))
DECL|macro|_PAGE_FILE
mdefine_line|#define _PAGE_FILE     (1 &lt;&lt; xlate_pabit(_PAGE_FILE_BIT))
DECL|macro|_PAGE_TABLE
mdefine_line|#define _PAGE_TABLE&t;(_PAGE_PRESENT | _PAGE_READ | _PAGE_WRITE |  _PAGE_DIRTY | _PAGE_ACCESSED)
DECL|macro|_PAGE_CHG_MASK
mdefine_line|#define _PAGE_CHG_MASK&t;(PAGE_MASK | _PAGE_ACCESSED | _PAGE_DIRTY)
DECL|macro|_PAGE_KERNEL
mdefine_line|#define _PAGE_KERNEL&t;(_PAGE_PRESENT | _PAGE_EXEC | _PAGE_READ | _PAGE_WRITE | _PAGE_DIRTY | _PAGE_ACCESSED)
multiline_comment|/* The pgd/pmd contains a ptr (in phys addr space); since all pgds/pmds&n; * are page-aligned, we don&squot;t care about the PAGE_OFFSET bits, except&n; * for a few meta-information bits, so we shift the address to be&n; * able to effectively address 40-bits of physical address space. */
DECL|macro|_PxD_PRESENT_BIT
mdefine_line|#define _PxD_PRESENT_BIT   31
DECL|macro|_PxD_ATTACHED_BIT
mdefine_line|#define _PxD_ATTACHED_BIT  30
DECL|macro|_PxD_VALID_BIT
mdefine_line|#define _PxD_VALID_BIT     29
DECL|macro|PxD_FLAG_PRESENT
mdefine_line|#define PxD_FLAG_PRESENT  (1 &lt;&lt; xlate_pabit(_PxD_PRESENT_BIT))
DECL|macro|PxD_FLAG_ATTACHED
mdefine_line|#define PxD_FLAG_ATTACHED (1 &lt;&lt; xlate_pabit(_PxD_ATTACHED_BIT))
DECL|macro|PxD_FLAG_VALID
mdefine_line|#define PxD_FLAG_VALID    (1 &lt;&lt; xlate_pabit(_PxD_VALID_BIT))
DECL|macro|PxD_FLAG_MASK
mdefine_line|#define PxD_FLAG_MASK     (0xf)
DECL|macro|PxD_FLAG_SHIFT
mdefine_line|#define PxD_FLAG_SHIFT    (4)
DECL|macro|PxD_VALUE_SHIFT
mdefine_line|#define PxD_VALUE_SHIFT   (8)
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
DECL|macro|PAGE_FLUSH
mdefine_line|#define PAGE_FLUSH      __pgprot(_PAGE_FLUSH)
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
id|pgd_t
id|swapper_pg_dir
(braket
)braket
suffix:semicolon
multiline_comment|/* declared in init_task.c */
multiline_comment|/* initial page tables for 0-8MB for kernel */
r_extern
id|pte_t
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
multiline_comment|/*&n; * ZERO_PAGE is a global shared page that is always zero: used&n; * for zero-mapped memory areas etc..&n; */
DECL|macro|ZERO_PAGE
mdefine_line|#define ZERO_PAGE(vaddr) (virt_to_page(empty_zero_page))
DECL|macro|pte_none
mdefine_line|#define pte_none(x)     ((pte_val(x) == 0) || (pte_val(x) &amp; _PAGE_FLUSH))
DECL|macro|pte_present
mdefine_line|#define pte_present(x)&t;(pte_val(x) &amp; _PAGE_PRESENT)
DECL|macro|pte_clear
mdefine_line|#define pte_clear(xp)&t;do { pte_val(*(xp)) = 0; } while (0)
DECL|macro|pmd_flag
mdefine_line|#define pmd_flag(x)&t;(pmd_val(x) &amp; PxD_FLAG_MASK)
DECL|macro|pmd_address
mdefine_line|#define pmd_address(x)&t;((unsigned long)(pmd_val(x) &amp;~ PxD_FLAG_MASK) &lt;&lt; PxD_VALUE_SHIFT)
DECL|macro|pgd_flag
mdefine_line|#define pgd_flag(x)&t;(pgd_val(x) &amp; PxD_FLAG_MASK)
DECL|macro|pgd_address
mdefine_line|#define pgd_address(x)&t;((unsigned long)(pgd_val(x) &amp;~ PxD_FLAG_MASK) &lt;&lt; PxD_VALUE_SHIFT)
macro_line|#ifdef CONFIG_64BIT
multiline_comment|/* The first entry of the permanent pmd is not there if it contains&n; * the gateway marker */
DECL|macro|pmd_none
mdefine_line|#define pmd_none(x)&t;(!pmd_val(x) || pmd_flag(x) == PxD_FLAG_ATTACHED)
macro_line|#else
DECL|macro|pmd_none
mdefine_line|#define pmd_none(x)&t;(!pmd_val(x))
macro_line|#endif
DECL|macro|pmd_bad
mdefine_line|#define pmd_bad(x)&t;(!(pmd_flag(x) &amp; PxD_FLAG_VALID))
DECL|macro|pmd_present
mdefine_line|#define pmd_present(x)&t;(pmd_flag(x) &amp; PxD_FLAG_PRESENT)
DECL|function|pmd_clear
r_static
r_inline
r_void
id|pmd_clear
c_func
(paren
id|pmd_t
op_star
id|pmd
)paren
(brace
macro_line|#ifdef CONFIG_64BIT
r_if
c_cond
(paren
id|pmd_flag
c_func
(paren
op_star
id|pmd
)paren
op_amp
id|PxD_FLAG_ATTACHED
)paren
multiline_comment|/* This is the entry pointing to the permanent pmd&n;&t;&t; * attached to the pgd; cannot clear it */
id|__pmd_val_set
c_func
(paren
op_star
id|pmd
comma
id|PxD_FLAG_ATTACHED
)paren
suffix:semicolon
r_else
macro_line|#endif
id|__pmd_val_set
c_func
(paren
op_star
id|pmd
comma
l_int|0
)paren
suffix:semicolon
)brace
macro_line|#if PT_NLEVELS == 3
DECL|macro|pgd_page
mdefine_line|#define pgd_page(pgd) ((unsigned long) __va(pgd_address(pgd)))
multiline_comment|/* For 64 bit we have three level tables */
DECL|macro|pgd_none
mdefine_line|#define pgd_none(x)     (!pgd_val(x))
DECL|macro|pgd_bad
mdefine_line|#define pgd_bad(x)      (!(pgd_flag(x) &amp; PxD_FLAG_VALID))
DECL|macro|pgd_present
mdefine_line|#define pgd_present(x)  (pgd_flag(x) &amp; PxD_FLAG_PRESENT)
DECL|function|pgd_clear
r_static
r_inline
r_void
id|pgd_clear
c_func
(paren
id|pgd_t
op_star
id|pgd
)paren
(brace
macro_line|#ifdef CONFIG_64BIT
r_if
c_cond
(paren
id|pgd_flag
c_func
(paren
op_star
id|pgd
)paren
op_amp
id|PxD_FLAG_ATTACHED
)paren
(brace
multiline_comment|/* This is the permanent pmd attached to the pgd; cannot&n;&t;&t; * free it */
r_return
suffix:semicolon
)brace
macro_line|#endif
id|__pgd_val_set
c_func
(paren
op_star
id|pgd
comma
l_int|0
)paren
suffix:semicolon
)brace
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
DECL|function|pte_file
r_extern
r_inline
r_int
id|pte_file
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
id|_PAGE_FILE
suffix:semicolon
)brace
DECL|function|pte_user
r_extern
r_inline
r_int
id|pte_user
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
id|_PAGE_USER
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
mdefine_line|#define mk_pte(page, pgprot)&t;pfn_pte(page_to_pfn(page), (pgprot))
DECL|function|pfn_pte
r_static
r_inline
id|pte_t
id|pfn_pte
c_func
(paren
r_int
r_int
id|pfn
comma
id|pgprot_t
id|pgprot
)paren
(brace
id|pte_t
id|pte
suffix:semicolon
id|pte_val
c_func
(paren
id|pte
)paren
op_assign
(paren
id|pfn
op_lshift
id|PAGE_SHIFT
)paren
op_or
id|pgprot_val
c_func
(paren
id|pgprot
)paren
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
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
multiline_comment|/* Permanent address of a page.  On parisc we don&squot;t have highmem. */
DECL|macro|pte_pfn
mdefine_line|#define pte_pfn(x) (pte_val(x) &gt;&gt; PAGE_SHIFT)
DECL|macro|pte_page
mdefine_line|#define pte_page(pte)&t;&t;(pfn_to_page(pte_pfn(pte)))
DECL|macro|pmd_page_kernel
mdefine_line|#define pmd_page_kernel(pmd)&t;((unsigned long) __va(pmd_address(pmd)))
DECL|macro|__pmd_page
mdefine_line|#define __pmd_page(pmd) ((unsigned long) __va(pmd_address(pmd)))
DECL|macro|pmd_page
mdefine_line|#define pmd_page(pmd)&t;virt_to_page((void *)__pmd_page(pmd))
DECL|macro|pgd_index
mdefine_line|#define pgd_index(address) ((address) &gt;&gt; PGDIR_SHIFT)
multiline_comment|/* to find an entry in a page-table-directory */
DECL|macro|pgd_offset
mdefine_line|#define pgd_offset(mm, address) &bslash;&n;((mm)-&gt;pgd + ((address) &gt;&gt; PGDIR_SHIFT))
multiline_comment|/* to find an entry in a kernel page-table-directory */
DECL|macro|pgd_offset_k
mdefine_line|#define pgd_offset_k(address) pgd_offset(&amp;init_mm, address)
multiline_comment|/* Find an entry in the second-level page table.. */
macro_line|#if PT_NLEVELS == 3
DECL|macro|pmd_offset
mdefine_line|#define pmd_offset(dir,address) &bslash;&n;((pmd_t *) pgd_page(*(dir)) + (((address)&gt;&gt;PMD_SHIFT) &amp; (PTRS_PER_PMD-1)))
macro_line|#else
DECL|macro|pmd_offset
mdefine_line|#define pmd_offset(dir,addr) ((pmd_t *) dir)
macro_line|#endif
multiline_comment|/* Find an entry in the third-level page table.. */
DECL|macro|pte_index
mdefine_line|#define pte_index(address) (((address) &gt;&gt; PAGE_SHIFT) &amp; (PTRS_PER_PTE-1))
DECL|macro|pte_offset_kernel
mdefine_line|#define pte_offset_kernel(pmd, address) &bslash;&n;&t;((pte_t *) pmd_page_kernel(*(pmd)) + pte_index(address))
DECL|macro|pte_offset_map
mdefine_line|#define pte_offset_map(pmd, address) pte_offset_kernel(pmd, address)
DECL|macro|pte_offset_map_nested
mdefine_line|#define pte_offset_map_nested(pmd, address) pte_offset_kernel(pmd, address)
DECL|macro|pte_unmap
mdefine_line|#define pte_unmap(pte) do { } while (0)
DECL|macro|pte_unmap_nested
mdefine_line|#define pte_unmap_nested(pte) do { } while (0)
DECL|macro|pte_unmap
mdefine_line|#define pte_unmap(pte)&t;&t;&t;do { } while (0)
DECL|macro|pte_unmap_nested
mdefine_line|#define pte_unmap_nested(pte)&t;&t;do { } while (0)
r_extern
r_void
id|paging_init
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Used for deferring calls to flush_dcache_page() */
DECL|macro|PG_dcache_dirty
mdefine_line|#define PG_dcache_dirty         PG_arch_1
r_struct
id|vm_area_struct
suffix:semicolon
multiline_comment|/* forward declaration (include/linux/mm.h) */
r_extern
r_void
id|update_mmu_cache
c_func
(paren
r_struct
id|vm_area_struct
op_star
comma
r_int
r_int
comma
id|pte_t
)paren
suffix:semicolon
multiline_comment|/* Encode and de-code a swap entry */
DECL|macro|__swp_type
mdefine_line|#define __swp_type(x)                     ((x).val &amp; 0x1f)
DECL|macro|__swp_offset
mdefine_line|#define __swp_offset(x)                   ( (((x).val &gt;&gt; 6) &amp;  0x7) | &bslash;&n;&t;&t;&t;&t;&t;  (((x).val &gt;&gt; 8) &amp; ~0x7) )
DECL|macro|__swp_entry
mdefine_line|#define __swp_entry(type, offset)         ((swp_entry_t) { (type) | &bslash;&n;&t;&t;&t;&t;&t;    ((offset &amp;  0x7) &lt;&lt; 6) | &bslash;&n;&t;&t;&t;&t;&t;    ((offset &amp; ~0x7) &lt;&lt; 8) })
DECL|macro|__pte_to_swp_entry
mdefine_line|#define __pte_to_swp_entry(pte)&t;&t;((swp_entry_t) { pte_val(pte) })
DECL|macro|__swp_entry_to_pte
mdefine_line|#define __swp_entry_to_pte(x)&t;&t;((pte_t) { (x).val })
DECL|function|ptep_test_and_clear_young
r_static
r_inline
r_int
id|ptep_test_and_clear_young
c_func
(paren
id|pte_t
op_star
id|ptep
)paren
(brace
macro_line|#ifdef CONFIG_SMP
r_if
c_cond
(paren
op_logical_neg
id|pte_young
c_func
(paren
op_star
id|ptep
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|test_and_clear_bit
c_func
(paren
id|xlate_pabit
c_func
(paren
id|_PAGE_ACCESSED_BIT
)paren
comma
op_amp
id|pte_val
c_func
(paren
op_star
id|ptep
)paren
)paren
suffix:semicolon
macro_line|#else
id|pte_t
id|pte
op_assign
op_star
id|ptep
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pte_young
c_func
(paren
id|pte
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|set_pte
c_func
(paren
id|ptep
comma
id|pte_mkold
c_func
(paren
id|pte
)paren
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
macro_line|#endif
)brace
DECL|function|ptep_test_and_clear_dirty
r_static
r_inline
r_int
id|ptep_test_and_clear_dirty
c_func
(paren
id|pte_t
op_star
id|ptep
)paren
(brace
macro_line|#ifdef CONFIG_SMP
r_if
c_cond
(paren
op_logical_neg
id|pte_dirty
c_func
(paren
op_star
id|ptep
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|test_and_clear_bit
c_func
(paren
id|xlate_pabit
c_func
(paren
id|_PAGE_DIRTY_BIT
)paren
comma
op_amp
id|pte_val
c_func
(paren
op_star
id|ptep
)paren
)paren
suffix:semicolon
macro_line|#else
id|pte_t
id|pte
op_assign
op_star
id|ptep
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pte_dirty
c_func
(paren
id|pte
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|set_pte
c_func
(paren
id|ptep
comma
id|pte_mkclean
c_func
(paren
id|pte
)paren
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
macro_line|#endif
)brace
r_extern
id|spinlock_t
id|pa_dbit_lock
suffix:semicolon
DECL|function|ptep_get_and_clear
r_static
r_inline
id|pte_t
id|ptep_get_and_clear
c_func
(paren
id|pte_t
op_star
id|ptep
)paren
(brace
id|pte_t
id|old_pte
suffix:semicolon
id|pte_t
id|pte
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|pa_dbit_lock
)paren
suffix:semicolon
id|pte
op_assign
id|old_pte
op_assign
op_star
id|ptep
suffix:semicolon
id|pte_val
c_func
(paren
id|pte
)paren
op_and_assign
op_complement
id|_PAGE_PRESENT
suffix:semicolon
id|pte_val
c_func
(paren
id|pte
)paren
op_or_assign
id|_PAGE_FLUSH
suffix:semicolon
id|set_pte
c_func
(paren
id|ptep
comma
id|pte
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|pa_dbit_lock
)paren
suffix:semicolon
r_return
id|old_pte
suffix:semicolon
)brace
DECL|function|ptep_set_wrprotect
r_static
r_inline
r_void
id|ptep_set_wrprotect
c_func
(paren
id|pte_t
op_star
id|ptep
)paren
(brace
macro_line|#ifdef CONFIG_SMP
r_int
r_int
r_new
comma
id|old
suffix:semicolon
r_do
(brace
id|old
op_assign
id|pte_val
c_func
(paren
op_star
id|ptep
)paren
suffix:semicolon
r_new
op_assign
id|pte_val
c_func
(paren
id|pte_wrprotect
c_func
(paren
id|__pte
(paren
id|old
)paren
)paren
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|cmpxchg
c_func
(paren
(paren
r_int
r_int
op_star
)paren
id|ptep
comma
id|old
comma
r_new
)paren
op_ne
id|old
)paren
suffix:semicolon
macro_line|#else
id|pte_t
id|old_pte
op_assign
op_star
id|ptep
suffix:semicolon
id|set_pte
c_func
(paren
id|ptep
comma
id|pte_wrprotect
c_func
(paren
id|old_pte
)paren
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|function|ptep_mkdirty
r_static
r_inline
r_void
id|ptep_mkdirty
c_func
(paren
id|pte_t
op_star
id|ptep
)paren
(brace
macro_line|#ifdef CONFIG_SMP
id|set_bit
c_func
(paren
id|xlate_pabit
c_func
(paren
id|_PAGE_DIRTY_BIT
)paren
comma
op_amp
id|pte_val
c_func
(paren
op_star
id|ptep
)paren
)paren
suffix:semicolon
macro_line|#else
id|pte_t
id|old_pte
op_assign
op_star
id|ptep
suffix:semicolon
id|set_pte
c_func
(paren
id|ptep
comma
id|pte_mkdirty
c_func
(paren
id|old_pte
)paren
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|macro|pte_same
mdefine_line|#define pte_same(A,B)&t;(pte_val(A) == pte_val(B))
macro_line|#endif /* !__ASSEMBLY__ */
DECL|macro|io_remap_page_range
mdefine_line|#define io_remap_page_range(vma, vaddr, paddr, size, prot)&t;&t;&bslash;&n;&t;&t;remap_pfn_range(vma, vaddr, (paddr) &gt;&gt; PAGE_SHIFT, size, prot)
multiline_comment|/* We provide our own get_unmapped_area to provide cache coherency */
DECL|macro|HAVE_ARCH_UNMAPPED_AREA
mdefine_line|#define HAVE_ARCH_UNMAPPED_AREA
DECL|macro|__HAVE_ARCH_PTEP_TEST_AND_CLEAR_YOUNG
mdefine_line|#define __HAVE_ARCH_PTEP_TEST_AND_CLEAR_YOUNG
DECL|macro|__HAVE_ARCH_PTEP_TEST_AND_CLEAR_DIRTY
mdefine_line|#define __HAVE_ARCH_PTEP_TEST_AND_CLEAR_DIRTY
DECL|macro|__HAVE_ARCH_PTEP_GET_AND_CLEAR
mdefine_line|#define __HAVE_ARCH_PTEP_GET_AND_CLEAR
DECL|macro|__HAVE_ARCH_PTEP_SET_WRPROTECT
mdefine_line|#define __HAVE_ARCH_PTEP_SET_WRPROTECT
DECL|macro|__HAVE_ARCH_PTEP_MKDIRTY
mdefine_line|#define __HAVE_ARCH_PTEP_MKDIRTY
DECL|macro|__HAVE_ARCH_PTE_SAME
mdefine_line|#define __HAVE_ARCH_PTE_SAME
macro_line|#include &lt;asm-generic/pgtable.h&gt;
macro_line|#endif /* _PARISC_PGTABLE_H */
eof
