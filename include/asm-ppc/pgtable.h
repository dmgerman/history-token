multiline_comment|/*&n; * BK Id: SCCS/s.pgtable.h 1.15 09/22/01 11:26:52 trini&n; */
macro_line|#ifdef __KERNEL__
macro_line|#ifndef _PPC_PGTABLE_H
DECL|macro|_PPC_PGTABLE_H
mdefine_line|#define _PPC_PGTABLE_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;asm/processor.h&gt;&t;&t;/* For TASK_SIZE */
macro_line|#include &lt;asm/mmu.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#if defined(CONFIG_4xx)
r_extern
r_void
id|local_flush_tlb_all
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|local_flush_tlb_mm
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
suffix:semicolon
r_extern
r_void
id|local_flush_tlb_page
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
suffix:semicolon
r_extern
r_void
id|local_flush_tlb_range
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
r_int
r_int
id|start
comma
r_int
r_int
id|end
)paren
suffix:semicolon
DECL|macro|update_mmu_cache
mdefine_line|#define update_mmu_cache(vma, addr, pte)&t;do { } while (0)
macro_line|#elif defined(CONFIG_8xx)
DECL|macro|__tlbia
mdefine_line|#define __tlbia()&t;asm volatile (&quot;tlbia&quot; : : )
DECL|function|local_flush_tlb_all
r_static
r_inline
r_void
id|local_flush_tlb_all
c_func
(paren
r_void
)paren
(brace
id|__tlbia
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|local_flush_tlb_mm
r_static
r_inline
r_void
id|local_flush_tlb_mm
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
(brace
id|__tlbia
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|local_flush_tlb_page
r_static
r_inline
r_void
id|local_flush_tlb_page
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
id|__tlbia
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|local_flush_tlb_range
r_static
r_inline
r_void
id|local_flush_tlb_range
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
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
id|__tlbia
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|macro|update_mmu_cache
mdefine_line|#define update_mmu_cache(vma, addr, pte)&t;do { } while (0)
macro_line|#else&t;/* 6xx, 7xx, 7xxx cpus */
r_struct
id|mm_struct
suffix:semicolon
r_struct
id|vm_area_struct
suffix:semicolon
r_extern
r_void
id|local_flush_tlb_all
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|local_flush_tlb_mm
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
suffix:semicolon
r_extern
r_void
id|local_flush_tlb_page
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
suffix:semicolon
r_extern
r_void
id|local_flush_tlb_range
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
r_int
r_int
id|start
comma
r_int
r_int
id|end
)paren
suffix:semicolon
multiline_comment|/*&n; * This gets called at the end of handling a page fault, when&n; * the kernel has put a new PTE into the page table for the process.&n; * We use it to put a corresponding HPTE into the hash table&n; * ahead of time, instead of waiting for the inevitable extra&n; * hash-table miss exception.&n; */
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
macro_line|#endif
DECL|macro|flush_tlb_all
mdefine_line|#define flush_tlb_all local_flush_tlb_all
DECL|macro|flush_tlb_mm
mdefine_line|#define flush_tlb_mm local_flush_tlb_mm
DECL|macro|flush_tlb_page
mdefine_line|#define flush_tlb_page local_flush_tlb_page
DECL|macro|flush_tlb_range
mdefine_line|#define flush_tlb_range local_flush_tlb_range
multiline_comment|/*&n; * This is called in munmap when we have freed up some page-table&n; * pages.  We don&squot;t need to do anything here, there&squot;s nothing special&n; * about our page-table pages.  -- paulus&n; */
DECL|function|flush_tlb_pgtables
r_static
r_inline
r_void
id|flush_tlb_pgtables
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
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
)brace
multiline_comment|/*&n; * No cache flushing is required when address mappings are&n; * changed, because the caches on PowerPCs are physically&n; * addressed.  -- paulus&n; * Also, when SMP we use the coherency (M) bit of the&n; * BATs and PTEs.  -- Cort&n; */
DECL|macro|flush_cache_all
mdefine_line|#define flush_cache_all()&t;&t;do { } while (0)
DECL|macro|flush_cache_mm
mdefine_line|#define flush_cache_mm(mm)&t;&t;do { } while (0)
DECL|macro|flush_cache_range
mdefine_line|#define flush_cache_range(mm, a, b)&t;do { } while (0)
DECL|macro|flush_cache_page
mdefine_line|#define flush_cache_page(vma, p)&t;do { } while (0)
DECL|macro|flush_icache_page
mdefine_line|#define flush_icache_page(vma, page)&t;do { } while (0)
r_extern
r_void
id|flush_icache_range
c_func
(paren
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|__flush_page_to_ram
c_func
(paren
r_int
r_int
id|page_va
)paren
suffix:semicolon
r_extern
r_void
id|flush_page_to_ram
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
suffix:semicolon
DECL|macro|flush_dcache_page
mdefine_line|#define flush_dcache_page(page)&t;&t;&t;do { } while (0)
r_extern
r_int
r_int
id|va_to_phys
c_func
(paren
r_int
r_int
id|address
)paren
suffix:semicolon
r_extern
id|pte_t
op_star
id|va_to_pte
c_func
(paren
r_int
r_int
id|address
)paren
suffix:semicolon
r_extern
r_int
r_int
id|ioremap_bot
comma
id|ioremap_base
suffix:semicolon
macro_line|#endif /* __ASSEMBLY__ */
multiline_comment|/*&n; * The PowerPC MMU uses a hash table containing PTEs, together with&n; * a set of 16 segment registers (on 32-bit implementations), to define&n; * the virtual to physical address mapping.&n; *&n; * We use the hash table as an extended TLB, i.e. a cache of currently&n; * active mappings.  We maintain a two-level page table tree, much&n; * like that used by the i386, for the sake of the Linux memory&n; * management code.  Low-level assembler code in hashtable.S&n; * (procedure hash_page) is responsible for extracting ptes from the&n; * tree and putting them into the hash table when necessary, and&n; * updating the accessed and modified bits in the page table tree.&n; */
multiline_comment|/*&n; * The PowerPC MPC8xx uses a TLB with hardware assisted, software tablewalk.&n; * We also use the two level tables, but we can put the real bits in them&n; * needed for the TLB and tablewalk.  These definitions require Mx_CTR.PPM = 0,&n; * Mx_CTR.PPCS = 0, and MD_CTR.TWAM = 1.  The level 2 descriptor has&n; * additional page protection (when Mx_CTR.PPCS = 1) that allows TLB hit&n; * based upon user/super access.  The TLB does not have accessed nor write&n; * protect.  We assume that if the TLB get loaded with an entry it is&n; * accessed, and overload the changed bit for write protect.  We use&n; * two bits in the software pte that are supposed to be set to zero in&n; * the TLB entry (24 and 25) for these indicators.  Although the level 1&n; * descriptor contains the guarded and writethrough/copyback bits, we can&n; * set these at the page level since they get copied from the Mx_TWC&n; * register when the TLB entry is loaded.  We will use bit 27 for guard, since&n; * that is where it exists in the MD_TWC, and bit 26 for writethrough.&n; * These will get masked from the level 2 descriptor at TLB load time, and&n; * copied to the MD_TWC before it gets loaded.&n; */
multiline_comment|/*&n; * At present, all PowerPC 400-class processors share a similar TLB&n; * architecture. The instruction and data sides share a unified,&n; * 64-entry, fully-associative TLB which is maintained totally under&n; * software control. In addition, the instruction side has a&n; * hardware-managed, 4-entry, fully-associative TLB which serves as a&n; * first level to the shared TLB. These two TLBs are known as the UTLB&n; * and ITLB, respectively (see &quot;mmu.h&quot; for definitions).&n; */
multiline_comment|/* PMD_SHIFT determines the size of the area mapped by the second-level page tables */
DECL|macro|PMD_SHIFT
mdefine_line|#define PMD_SHIFT&t;22
DECL|macro|PMD_SIZE
mdefine_line|#define PMD_SIZE&t;(1UL &lt;&lt; PMD_SHIFT)
DECL|macro|PMD_MASK
mdefine_line|#define PMD_MASK&t;(~(PMD_SIZE-1))
multiline_comment|/* PGDIR_SHIFT determines what a third-level page table entry can map */
DECL|macro|PGDIR_SHIFT
mdefine_line|#define PGDIR_SHIFT&t;22
DECL|macro|PGDIR_SIZE
mdefine_line|#define PGDIR_SIZE&t;(1UL &lt;&lt; PGDIR_SHIFT)
DECL|macro|PGDIR_MASK
mdefine_line|#define PGDIR_MASK&t;(~(PGDIR_SIZE-1))
multiline_comment|/*&n; * entries per page directory level: our page-table tree is two-level, so&n; * we don&squot;t really have any PMD directory.&n; */
DECL|macro|PTRS_PER_PTE
mdefine_line|#define PTRS_PER_PTE&t;1024
DECL|macro|PTRS_PER_PMD
mdefine_line|#define PTRS_PER_PMD&t;1
DECL|macro|PTRS_PER_PGD
mdefine_line|#define PTRS_PER_PGD&t;1024
DECL|macro|USER_PTRS_PER_PGD
mdefine_line|#define USER_PTRS_PER_PGD&t;(TASK_SIZE / PGDIR_SIZE)
DECL|macro|FIRST_USER_PGD_NR
mdefine_line|#define FIRST_USER_PGD_NR&t;0
DECL|macro|USER_PGD_PTRS
mdefine_line|#define USER_PGD_PTRS (PAGE_OFFSET &gt;&gt; PGDIR_SHIFT)
DECL|macro|KERNEL_PGD_PTRS
mdefine_line|#define KERNEL_PGD_PTRS (PTRS_PER_PGD-USER_PGD_PTRS)
DECL|macro|pte_ERROR
mdefine_line|#define pte_ERROR(e) &bslash;&n;&t;printk(&quot;%s:%d: bad pte %08lx.&bslash;n&quot;, __FILE__, __LINE__, pte_val(e))
DECL|macro|pmd_ERROR
mdefine_line|#define pmd_ERROR(e) &bslash;&n;&t;printk(&quot;%s:%d: bad pmd %08lx.&bslash;n&quot;, __FILE__, __LINE__, pmd_val(e))
DECL|macro|pgd_ERROR
mdefine_line|#define pgd_ERROR(e) &bslash;&n;&t;printk(&quot;%s:%d: bad pgd %08lx.&bslash;n&quot;, __FILE__, __LINE__, pgd_val(e))
multiline_comment|/*&n; * Just any arbitrary offset to the start of the vmalloc VM area: the&n; * current 64MB value just means that there will be a 64MB &quot;hole&quot; after the&n; * physical memory until the kernel virtual memory starts.  That means that&n; * any out-of-bounds memory accesses will hopefully be caught.&n; * The vmalloc() routines leaves a hole of 4kB between each vmalloced&n; * area for the same reason. ;)&n; *&n; * We no longer map larger than phys RAM with the BATs so we don&squot;t have&n; * to worry about the VMALLOC_OFFSET causing problems.  We do have to worry&n; * about clashes between our early calls to ioremap() that start growing down&n; * from ioremap_base being run into the VM area allocations (growing upwards&n; * from VMALLOC_START).  For this reason we have ioremap_bot to check when&n; * we actually run into our mappings setup in the early boot with the VM&n; * system.  This really does become a problem for machines with good amounts&n; * of RAM.  -- Cort&n; */
DECL|macro|VMALLOC_OFFSET
mdefine_line|#define VMALLOC_OFFSET (0x1000000) /* 16M */
DECL|macro|VMALLOC_START
mdefine_line|#define VMALLOC_START ((((long)high_memory + VMALLOC_OFFSET) &amp; ~(VMALLOC_OFFSET-1)))
DECL|macro|VMALLOC_VMADDR
mdefine_line|#define VMALLOC_VMADDR(x) ((unsigned long)(x))
DECL|macro|VMALLOC_END
mdefine_line|#define VMALLOC_END&t;ioremap_bot
multiline_comment|/*&n; * Bits in a linux-style PTE.  These match the bits in the&n; * (hardware-defined) PowerPC PTE as closely as possible.&n; */
macro_line|#if defined(CONFIG_4xx)
multiline_comment|/* Definitions for 4xx embedded chips. */
DECL|macro|_PAGE_GUARDED
mdefine_line|#define&t;_PAGE_GUARDED&t;0x001&t;/* G: page is guarded from prefetch */
DECL|macro|_PAGE_COHERENT
mdefine_line|#define&t;_PAGE_COHERENT&t;0x002&t;/* M: enforece memory coherence */
DECL|macro|_PAGE_NO_CACHE
mdefine_line|#define&t;_PAGE_NO_CACHE&t;0x004&t;/* I: caching is inhibited */
DECL|macro|_PAGE_WRITETHRU
mdefine_line|#define&t;_PAGE_WRITETHRU&t;0x008&t;/* W: caching is write-through */
DECL|macro|_PAGE_USER
mdefine_line|#define&t;_PAGE_USER&t;0x010&t;/* matches one of the zone permission bits */
DECL|macro|_PAGE_EXEC
mdefine_line|#define _PAGE_EXEC&t;0x020&t;/* software: i-cache coherency required */
DECL|macro|_PAGE_PRESENT
mdefine_line|#define&t;_PAGE_PRESENT&t;0x040&t;/* software: PTE contains a translation */
DECL|macro|_PAGE_DIRTY
mdefine_line|#define _PAGE_DIRTY&t;0x100&t;/* C: page changed */
DECL|macro|_PAGE_RW
mdefine_line|#define&t;_PAGE_RW&t;0x200&t;/* Writes permitted */
DECL|macro|_PAGE_ACCESSED
mdefine_line|#define _PAGE_ACCESSED&t;0x400&t;/* R: page referenced */
macro_line|#elif defined(CONFIG_8xx)
multiline_comment|/* Definitions for 8xx embedded chips. */
DECL|macro|_PAGE_PRESENT
mdefine_line|#define _PAGE_PRESENT&t;0x0001&t;/* Page is valid */
DECL|macro|_PAGE_NO_CACHE
mdefine_line|#define _PAGE_NO_CACHE&t;0x0002&t;/* I: cache inhibit */
DECL|macro|_PAGE_SHARED
mdefine_line|#define _PAGE_SHARED&t;0x0004&t;/* No ASID (context) compare */
multiline_comment|/* These five software bits must be masked out when the entry is loaded&n; * into the TLB.&n; */
DECL|macro|_PAGE_EXEC
mdefine_line|#define _PAGE_EXEC&t;0x0008&t;/* software: i-cache coherency required */
DECL|macro|_PAGE_GUARDED
mdefine_line|#define _PAGE_GUARDED&t;0x0010&t;/* software: guarded access */
DECL|macro|_PAGE_WRITETHRU
mdefine_line|#define _PAGE_WRITETHRU 0x0020&t;/* software: use writethrough cache */
DECL|macro|_PAGE_RW
mdefine_line|#define _PAGE_RW&t;0x0040&t;/* software: user write access allowed */
DECL|macro|_PAGE_ACCESSED
mdefine_line|#define _PAGE_ACCESSED&t;0x0080&t;/* software: page referenced */
DECL|macro|_PAGE_HWWRITE
mdefine_line|#define _PAGE_HWWRITE&t;0x0100&t;/* h/w write enable: never set in Linux PTE */
DECL|macro|_PAGE_DIRTY
mdefine_line|#define _PAGE_DIRTY&t;0x0200&t;/* software: page changed */
DECL|macro|_PAGE_USER
mdefine_line|#define _PAGE_USER&t;0x0800&t;/* One of the PP bits, the other is USER&amp;~RW */
macro_line|#else /* CONFIG_6xx */
multiline_comment|/* Definitions for 60x, 740/750, etc. */
DECL|macro|_PAGE_PRESENT
mdefine_line|#define _PAGE_PRESENT&t;0x001&t;/* software: pte contains a translation */
DECL|macro|_PAGE_HASHPTE
mdefine_line|#define _PAGE_HASHPTE&t;0x002&t;/* hash_page has made an HPTE for this pte */
DECL|macro|_PAGE_USER
mdefine_line|#define _PAGE_USER&t;0x004&t;/* usermode access allowed */
DECL|macro|_PAGE_GUARDED
mdefine_line|#define _PAGE_GUARDED&t;0x008&t;/* G: prohibit speculative access */
DECL|macro|_PAGE_COHERENT
mdefine_line|#define _PAGE_COHERENT&t;0x010&t;/* M: enforce memory coherence (SMP systems) */
DECL|macro|_PAGE_NO_CACHE
mdefine_line|#define _PAGE_NO_CACHE&t;0x020&t;/* I: cache inhibit */
DECL|macro|_PAGE_WRITETHRU
mdefine_line|#define _PAGE_WRITETHRU&t;0x040&t;/* W: cache write-through */
DECL|macro|_PAGE_DIRTY
mdefine_line|#define _PAGE_DIRTY&t;0x080&t;/* C: page changed */
DECL|macro|_PAGE_ACCESSED
mdefine_line|#define _PAGE_ACCESSED&t;0x100&t;/* R: page referenced */
DECL|macro|_PAGE_EXEC
mdefine_line|#define _PAGE_EXEC&t;0x200&t;/* software: i-cache coherency required */
DECL|macro|_PAGE_RW
mdefine_line|#define _PAGE_RW&t;0x400&t;/* software: user write access allowed */
macro_line|#endif
multiline_comment|/* The non-standard PowerPC MMUs, which includes the 4xx and 8xx (and&n; * mabe 603e) have TLB miss handlers that unconditionally set the&n; * _PAGE_ACCESSED flag as a performance optimization.  This causes&n; * problems for the page_none() macro, just like the HASHPTE flag does&n; * for the standard PowerPC MMUs.  Depending upon the MMU configuration,&n; * either HASHPTE or ACCESSED will have to be masked to give us a&n; * proper pte_none() condition.&n; */
macro_line|#ifndef _PAGE_HASHPTE
DECL|macro|_PAGE_HASHPTE
mdefine_line|#define _PAGE_HASHPTE&t;0
DECL|macro|_PTE_NONE_MASK
mdefine_line|#define _PTE_NONE_MASK _PAGE_ACCESSED
macro_line|#else
DECL|macro|_PTE_NONE_MASK
mdefine_line|#define _PTE_NONE_MASK _PAGE_HASHPTE
macro_line|#endif
macro_line|#ifndef _PAGE_SHARED
DECL|macro|_PAGE_SHARED
mdefine_line|#define _PAGE_SHARED&t;0
macro_line|#endif
macro_line|#ifndef _PAGE_HWWRITE
DECL|macro|_PAGE_HWWRITE
mdefine_line|#define _PAGE_HWWRITE&t;0
macro_line|#endif
multiline_comment|/* We can&squot;t use _PAGE_HWWRITE on any SMP due to the lack of ability&n; * to atomically manage _PAGE_HWWRITE and it&squot;s coordination flags,&n; * _PAGE_DIRTY or _PAGE_RW.  The SMP systems must manage HWWRITE&n; * or its logical equivalent in the MMU management software.&n; */
macro_line|#if CONFIG_SMP &amp;&amp; _PAGE_HWWRITE
macro_line|#error &quot;You can&squot;t configure SMP and HWWRITE&quot;
macro_line|#endif
DECL|macro|_PAGE_CHG_MASK
mdefine_line|#define _PAGE_CHG_MASK&t;(PAGE_MASK | _PAGE_ACCESSED | _PAGE_DIRTY)
multiline_comment|/*&n; * Note: the _PAGE_COHERENT bit automatically gets set in the hardware&n; * PTE if CONFIG_SMP is defined (hash_page does this); there is no need&n; * to have it in the Linux PTE, and in fact the bit could be reused for&n; * another purpose.  -- paulus.&n; */
DECL|macro|_PAGE_BASE
mdefine_line|#define _PAGE_BASE&t;_PAGE_PRESENT | _PAGE_ACCESSED
DECL|macro|_PAGE_WRENABLE
mdefine_line|#define _PAGE_WRENABLE&t;_PAGE_RW | _PAGE_DIRTY
DECL|macro|_PAGE_KERNEL
mdefine_line|#define _PAGE_KERNEL&t;_PAGE_BASE | _PAGE_WRENABLE | _PAGE_SHARED
DECL|macro|_PAGE_IO
mdefine_line|#define _PAGE_IO&t;_PAGE_KERNEL | _PAGE_NO_CACHE | _PAGE_GUARDED
DECL|macro|PAGE_NONE
mdefine_line|#define PAGE_NONE&t;__pgprot(_PAGE_BASE)
DECL|macro|PAGE_READONLY
mdefine_line|#define PAGE_READONLY&t;__pgprot(_PAGE_BASE | _PAGE_USER)
DECL|macro|PAGE_READONLY_X
mdefine_line|#define PAGE_READONLY_X&t;__pgprot(_PAGE_BASE | _PAGE_USER | _PAGE_EXEC)
DECL|macro|PAGE_SHARED
mdefine_line|#define PAGE_SHARED&t;__pgprot(_PAGE_BASE | _PAGE_USER | _PAGE_RW)
DECL|macro|PAGE_SHARED_X
mdefine_line|#define PAGE_SHARED_X&t;__pgprot(_PAGE_BASE | _PAGE_USER | _PAGE_RW | _PAGE_EXEC)
DECL|macro|PAGE_COPY
mdefine_line|#define PAGE_COPY&t;__pgprot(_PAGE_BASE | _PAGE_USER)
DECL|macro|PAGE_COPY_X
mdefine_line|#define PAGE_COPY_X&t;__pgprot(_PAGE_BASE | _PAGE_USER | _PAGE_EXEC)
DECL|macro|PAGE_KERNEL
mdefine_line|#define PAGE_KERNEL&t;__pgprot(_PAGE_KERNEL)
DECL|macro|PAGE_KERNEL_RO
mdefine_line|#define PAGE_KERNEL_RO&t;__pgprot(_PAGE_BASE | _PAGE_SHARED)
DECL|macro|PAGE_KERNEL_CI
mdefine_line|#define PAGE_KERNEL_CI&t;__pgprot(_PAGE_IO)
multiline_comment|/*&n; * The PowerPC can only do execute protection on a segment (256MB) basis,&n; * not on a page basis.  So we consider execute permission the same as read.&n; * Also, write permissions imply read permissions.&n; * This is the closest we can get..&n; */
DECL|macro|__P000
mdefine_line|#define __P000&t;PAGE_NONE
DECL|macro|__P001
mdefine_line|#define __P001&t;PAGE_READONLY_X
DECL|macro|__P010
mdefine_line|#define __P010&t;PAGE_COPY
DECL|macro|__P011
mdefine_line|#define __P011&t;PAGE_COPY_X
DECL|macro|__P100
mdefine_line|#define __P100&t;PAGE_READONLY
DECL|macro|__P101
mdefine_line|#define __P101&t;PAGE_READONLY_X
DECL|macro|__P110
mdefine_line|#define __P110&t;PAGE_COPY
DECL|macro|__P111
mdefine_line|#define __P111&t;PAGE_COPY_X
DECL|macro|__S000
mdefine_line|#define __S000&t;PAGE_NONE
DECL|macro|__S001
mdefine_line|#define __S001&t;PAGE_READONLY_X
DECL|macro|__S010
mdefine_line|#define __S010&t;PAGE_SHARED
DECL|macro|__S011
mdefine_line|#define __S011&t;PAGE_SHARED_X
DECL|macro|__S100
mdefine_line|#define __S100&t;PAGE_READONLY
DECL|macro|__S101
mdefine_line|#define __S101&t;PAGE_READONLY_X
DECL|macro|__S110
mdefine_line|#define __S110&t;PAGE_SHARED
DECL|macro|__S111
mdefine_line|#define __S111&t;PAGE_SHARED_X
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/*&n; * ZERO_PAGE is a global shared page that is always zero: used&n; * for zero-mapped memory areas etc..&n; */
r_extern
r_int
r_int
id|empty_zero_page
(braket
l_int|1024
)braket
suffix:semicolon
DECL|macro|ZERO_PAGE
mdefine_line|#define ZERO_PAGE(vaddr) (virt_to_page(empty_zero_page))
macro_line|#endif /* __ASSEMBLY__ */
DECL|macro|pte_none
mdefine_line|#define pte_none(pte)&t;&t;((pte_val(pte) &amp; ~_PTE_NONE_MASK) == 0)
DECL|macro|pte_present
mdefine_line|#define pte_present(pte)&t;(pte_val(pte) &amp; _PAGE_PRESENT)
DECL|macro|pte_clear
mdefine_line|#define pte_clear(ptep)&t;&t;do { set_pte((ptep), __pte(0)); } while (0)
DECL|macro|pmd_none
mdefine_line|#define pmd_none(pmd)&t;&t;(!pmd_val(pmd))
DECL|macro|pmd_bad
mdefine_line|#define&t;pmd_bad(pmd)&t;&t;((pmd_val(pmd) &amp; ~PAGE_MASK) != 0)
DECL|macro|pmd_present
mdefine_line|#define&t;pmd_present(pmd)&t;((pmd_val(pmd) &amp; PAGE_MASK) != 0)
DECL|macro|pmd_clear
mdefine_line|#define&t;pmd_clear(pmdp)&t;&t;do { pmd_val(*(pmdp)) = 0; } while (0)
multiline_comment|/*&n; * Permanent address of a page.&n; */
DECL|macro|page_address
mdefine_line|#define page_address(page)&t;((page)-&gt;virtual)
DECL|macro|pte_page
mdefine_line|#define pte_page(x)&t;&t;(mem_map+(unsigned long)((pte_val(x) &gt;&gt; PAGE_SHIFT)))
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/*&n; * The &quot;pgd_xxx()&quot; functions here are trivial for a folded two-level&n; * setup: the pgd is never bad, and a pmd always exists (as it&squot;s folded&n; * into the pgd entry)&n; */
DECL|function|pgd_none
r_static
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
r_static
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
r_static
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
DECL|macro|pgd_clear
mdefine_line|#define pgd_clear(xp)&t;&t;&t;&t;do { } while (0)
DECL|macro|pgd_page
mdefine_line|#define pgd_page(pgd) &bslash;&n;&t;((unsigned long) __va(pgd_val(pgd) &amp; PAGE_MASK))
multiline_comment|/*&n; * The following only work if pte_present() is true.&n; * Undefined behaviour if not..&n; */
DECL|function|pte_read
r_static
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
id|_PAGE_USER
suffix:semicolon
)brace
DECL|function|pte_write
r_static
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
id|_PAGE_RW
suffix:semicolon
)brace
DECL|function|pte_exec
r_static
r_inline
r_int
id|pte_exec
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
id|_PAGE_EXEC
suffix:semicolon
)brace
DECL|function|pte_dirty
r_static
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
r_static
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
DECL|function|pte_uncache
r_static
r_inline
r_void
id|pte_uncache
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
id|_PAGE_NO_CACHE
suffix:semicolon
)brace
DECL|function|pte_cache
r_static
r_inline
r_void
id|pte_cache
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
id|_PAGE_NO_CACHE
suffix:semicolon
)brace
DECL|function|pte_rdprotect
r_static
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
id|_PAGE_USER
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|function|pte_wrprotect
r_static
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
(paren
id|_PAGE_RW
op_or
id|_PAGE_HWWRITE
)paren
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|function|pte_exprotect
r_static
r_inline
id|pte_t
id|pte_exprotect
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
id|_PAGE_EXEC
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|function|pte_mkclean
r_static
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
(paren
id|_PAGE_DIRTY
op_or
id|_PAGE_HWWRITE
)paren
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|function|pte_mkold
r_static
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
DECL|function|pte_mkread
r_static
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
id|_PAGE_USER
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|function|pte_mkexec
r_static
r_inline
id|pte_t
id|pte_mkexec
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
id|_PAGE_USER
op_or
id|_PAGE_EXEC
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|function|pte_mkwrite
r_static
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
id|_PAGE_RW
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|function|pte_mkdirty
r_static
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
r_static
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
multiline_comment|/*&n; * Conversion functions: convert a page and protection to a page entry,&n; * and a page entry and page directory to the page they refer to.&n; */
DECL|function|mk_pte_phys
r_static
r_inline
id|pte_t
id|mk_pte_phys
c_func
(paren
r_int
r_int
id|physpage
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
id|physpage
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
DECL|macro|mk_pte
mdefine_line|#define mk_pte(page,pgprot) &bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;pte_t pte;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;pte_val(pte) = ((page - mem_map) &lt;&lt; PAGE_SHIFT) | pgprot_val(pgprot); &bslash;&n;&t;pte;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|function|pte_modify
r_static
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
multiline_comment|/*&n; * Atomic PTE updates.&n; *&n; * pte_update clears and sets bit atomically, and returns&n; * the old pte value.&n; */
DECL|function|pte_update
r_static
r_inline
r_int
r_int
id|pte_update
c_func
(paren
id|pte_t
op_star
id|p
comma
r_int
r_int
id|clr
comma
r_int
r_int
id|set
)paren
(brace
r_int
r_int
id|old
comma
id|tmp
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;&bslash;&n;1:&t;lwarx&t;%0,0,%3&bslash;n&bslash;&n;&t;andc&t;%1,%0,%4&bslash;n&bslash;&n;&t;or&t;%1,%1,%5&bslash;n&bslash;&n;&t;stwcx.&t;%1,0,%3&bslash;n&bslash;&n;&t;bne-&t;1b&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|old
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|tmp
)paren
comma
l_string|&quot;=m&quot;
(paren
op_star
id|p
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|p
)paren
comma
l_string|&quot;r&quot;
(paren
id|clr
)paren
comma
l_string|&quot;r&quot;
(paren
id|set
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
id|p
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_return
id|old
suffix:semicolon
)brace
multiline_comment|/*&n; * Writing a new value into the PTE doesn&squot;t disturb the state of the&n; * _PAGE_HASHPTE bit, on those machines which use an MMU hash table.&n; */
r_extern
r_void
id|set_pte
c_func
(paren
id|pte_t
op_star
id|ptep
comma
id|pte_t
id|pte
)paren
suffix:semicolon
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
r_return
(paren
id|pte_update
c_func
(paren
id|ptep
comma
id|_PAGE_ACCESSED
comma
l_int|0
)paren
op_amp
id|_PAGE_ACCESSED
)paren
op_ne
l_int|0
suffix:semicolon
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
r_return
(paren
id|pte_update
c_func
(paren
id|ptep
comma
(paren
id|_PAGE_DIRTY
op_or
id|_PAGE_HWWRITE
)paren
comma
l_int|0
)paren
op_amp
id|_PAGE_DIRTY
)paren
op_ne
l_int|0
suffix:semicolon
)brace
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
r_return
id|__pte
c_func
(paren
id|pte_update
c_func
(paren
id|ptep
comma
op_complement
id|_PAGE_HASHPTE
comma
l_int|0
)paren
)paren
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
id|pte_update
c_func
(paren
id|ptep
comma
(paren
id|_PAGE_RW
op_or
id|_PAGE_HWWRITE
)paren
comma
l_int|0
)paren
suffix:semicolon
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
id|pte_update
c_func
(paren
id|ptep
comma
l_int|0
comma
id|_PAGE_DIRTY
)paren
suffix:semicolon
)brace
DECL|macro|pte_same
mdefine_line|#define pte_same(A,B)&t;(((pte_val(A) ^ pte_val(B)) &amp; ~_PAGE_HASHPTE) == 0)
DECL|macro|pmd_page
mdefine_line|#define pmd_page(pmd)&t;(pmd_val(pmd))
multiline_comment|/* to find an entry in a kernel page-table-directory */
DECL|macro|pgd_offset_k
mdefine_line|#define pgd_offset_k(address) pgd_offset(&amp;init_mm, address)
multiline_comment|/* to find an entry in a page-table-directory */
DECL|macro|pgd_index
mdefine_line|#define pgd_index(address)&t; ((address) &gt;&gt; PGDIR_SHIFT)
DECL|macro|pgd_offset
mdefine_line|#define pgd_offset(mm, address)&t; ((mm)-&gt;pgd + pgd_index(address))
multiline_comment|/* Find an entry in the second-level page table.. */
DECL|function|pmd_offset
r_static
r_inline
id|pmd_t
op_star
id|pmd_offset
c_func
(paren
id|pgd_t
op_star
id|dir
comma
r_int
r_int
id|address
)paren
(brace
r_return
(paren
id|pmd_t
op_star
)paren
id|dir
suffix:semicolon
)brace
multiline_comment|/* Find an entry in the third-level page table.. */
DECL|function|pte_offset
r_static
r_inline
id|pte_t
op_star
id|pte_offset
c_func
(paren
id|pmd_t
op_star
id|dir
comma
r_int
r_int
id|address
)paren
(brace
r_return
(paren
id|pte_t
op_star
)paren
id|pmd_page
c_func
(paren
op_star
id|dir
)paren
op_plus
(paren
(paren
id|address
op_rshift
id|PAGE_SHIFT
)paren
op_amp
(paren
id|PTRS_PER_PTE
op_minus
l_int|1
)paren
)paren
suffix:semicolon
)brace
r_extern
id|pgd_t
id|swapper_pg_dir
(braket
l_int|1024
)braket
suffix:semicolon
r_extern
r_void
id|paging_init
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * When flushing the tlb entry for a page, we also need to flush the hash&n; * table entry.  flush_hash_page is assembler (for speed) in hashtable.S.&n; */
r_extern
r_int
id|flush_hash_page
c_func
(paren
r_int
id|context
comma
r_int
r_int
id|va
comma
id|pte_t
op_star
id|ptep
)paren
suffix:semicolon
multiline_comment|/* Add an HPTE to the hash table */
r_extern
r_void
id|add_hash_page
c_func
(paren
r_int
id|context
comma
r_int
r_int
id|va
comma
id|pte_t
op_star
id|ptep
)paren
suffix:semicolon
multiline_comment|/*&n; * Encode and decode a swap entry.&n; * Note that the bits we use in a PTE for representing a swap entry&n; * must not include the _PAGE_PRESENT bit, or the _PAGE_HASHPTE bit&n; * (if used).  -- paulus&n; */
DECL|macro|SWP_TYPE
mdefine_line|#define SWP_TYPE(entry)&t;&t;&t;((entry).val &amp; 0x3f)
DECL|macro|SWP_OFFSET
mdefine_line|#define SWP_OFFSET(entry)&t;&t;((entry).val &gt;&gt; 6)
DECL|macro|SWP_ENTRY
mdefine_line|#define SWP_ENTRY(type, offset)&t;&t;((swp_entry_t) { (type) | ((offset) &lt;&lt; 6) })
DECL|macro|pte_to_swp_entry
mdefine_line|#define pte_to_swp_entry(pte)&t;&t;((swp_entry_t) { pte_val(pte) &gt;&gt; 2 })
DECL|macro|swp_entry_to_pte
mdefine_line|#define swp_entry_to_pte(x)&t;&t;((pte_t) { (x).val &lt;&lt; 2 })
multiline_comment|/* CONFIG_APUS */
multiline_comment|/* For virtual address to physical address conversion */
r_extern
r_void
id|cache_clear
c_func
(paren
id|__u32
id|addr
comma
r_int
id|length
)paren
suffix:semicolon
r_extern
r_void
id|cache_push
c_func
(paren
id|__u32
id|addr
comma
r_int
id|length
)paren
suffix:semicolon
r_extern
r_int
id|mm_end_of_chunk
(paren
r_int
r_int
id|addr
comma
r_int
id|len
)paren
suffix:semicolon
r_extern
r_int
r_int
id|iopa
c_func
(paren
r_int
r_int
id|addr
)paren
suffix:semicolon
r_extern
r_int
r_int
id|mm_ptov
c_func
(paren
r_int
r_int
id|addr
)paren
id|__attribute__
(paren
(paren
r_const
)paren
)paren
suffix:semicolon
multiline_comment|/* Values for nocacheflag and cmode */
multiline_comment|/* These are not used by the APUS kernel_map, but prevents&n;   compilation errors. */
DECL|macro|KERNELMAP_FULL_CACHING
mdefine_line|#define&t;KERNELMAP_FULL_CACHING&t;&t;0
DECL|macro|KERNELMAP_NOCACHE_SER
mdefine_line|#define&t;KERNELMAP_NOCACHE_SER&t;&t;1
DECL|macro|KERNELMAP_NOCACHE_NONSER
mdefine_line|#define&t;KERNELMAP_NOCACHE_NONSER&t;2
DECL|macro|KERNELMAP_NO_COPYBACK
mdefine_line|#define&t;KERNELMAP_NO_COPYBACK&t;&t;3
multiline_comment|/*&n; * Map some physical address range into the kernel address space.&n; */
r_extern
r_int
r_int
id|kernel_map
c_func
(paren
r_int
r_int
id|paddr
comma
r_int
r_int
id|size
comma
r_int
id|nocacheflag
comma
r_int
r_int
op_star
id|memavailp
)paren
suffix:semicolon
multiline_comment|/*&n; * Set cache mode of (kernel space) address range. &n; */
r_extern
r_void
id|kernel_set_cachemode
(paren
r_int
r_int
id|address
comma
r_int
r_int
id|size
comma
r_int
r_int
id|cmode
)paren
suffix:semicolon
multiline_comment|/* Needs to be defined here and not in linux/mm.h, as it is arch dependent */
DECL|macro|kern_addr_valid
mdefine_line|#define kern_addr_valid(addr)&t;(1)
DECL|macro|io_remap_page_range
mdefine_line|#define io_remap_page_range remap_page_range 
multiline_comment|/*&n; * No page table caches to initialise&n; */
DECL|macro|pgtable_cache_init
mdefine_line|#define pgtable_cache_init()&t;do { } while (0)
macro_line|#endif /* __ASSEMBLY__ */
macro_line|#endif /* _PPC_PGTABLE_H */
macro_line|#endif /* __KERNEL__ */
eof
