macro_line|#ifdef __KERNEL__
macro_line|#ifndef _PPC_PGTABLE_H
DECL|macro|_PPC_PGTABLE_H
mdefine_line|#define _PPC_PGTABLE_H
macro_line|#include &lt;asm-generic/4level-fixup.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;asm/processor.h&gt;&t;&t;/* For TASK_SIZE */
macro_line|#include &lt;asm/mmu.h&gt;
macro_line|#include &lt;asm/page.h&gt;
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
multiline_comment|/*&n; * The PowerPC MPC8xx uses a TLB with hardware assisted, software tablewalk.&n; * We also use the two level tables, but we can put the real bits in them&n; * needed for the TLB and tablewalk.  These definitions require Mx_CTR.PPM = 0,&n; * Mx_CTR.PPCS = 0, and MD_CTR.TWAM = 1.  The level 2 descriptor has&n; * additional page protection (when Mx_CTR.PPCS = 1) that allows TLB hit&n; * based upon user/super access.  The TLB does not have accessed nor write&n; * protect.  We assume that if the TLB get loaded with an entry it is&n; * accessed, and overload the changed bit for write protect.  We use&n; * two bits in the software pte that are supposed to be set to zero in&n; * the TLB entry (24 and 25) for these indicators.  Although the level 1&n; * descriptor contains the guarded and writethrough/copyback bits, we can&n; * set these at the page level since they get copied from the Mx_TWC&n; * register when the TLB entry is loaded.  We will use bit 27 for guard, since&n; * that is where it exists in the MD_TWC, and bit 26 for writethrough.&n; * These will get masked from the level 2 descriptor at TLB load time, and&n; * copied to the MD_TWC before it gets loaded.&n; * Large page sizes added.  We currently support two sizes, 4K and 8M.&n; * This also allows a TLB hander optimization because we can directly&n; * load the PMD into MD_TWC.  The 8M pages are only used for kernel&n; * mapping of well known areas.  The PMD (PGD) entries contain control&n; * flags in addition to the address, so care must be taken that the&n; * software no longer assumes these are only pointers.&n; */
multiline_comment|/*&n; * At present, all PowerPC 400-class processors share a similar TLB&n; * architecture. The instruction and data sides share a unified,&n; * 64-entry, fully-associative TLB which is maintained totally under&n; * software control. In addition, the instruction side has a&n; * hardware-managed, 4-entry, fully-associative TLB which serves as a&n; * first level to the shared TLB. These two TLBs are known as the UTLB&n; * and ITLB, respectively (see &quot;mmu.h&quot; for definitions).&n; */
multiline_comment|/*&n; * The normal case is that PTEs are 32-bits and we have a 1-page&n; * 1024-entry pgdir pointing to 1-page 1024-entry PTE pages.  -- paulus&n; *&n; * For any &gt;32-bit physical address platform, we can use the following&n; * two level page table layout where the pgdir is 8KB and the MS 13 bits&n; * are an index to the second level table.  The combined pgdir/pmd first&n; * level has 2048 entries and the second level has 512 64-bit PTE entries.&n; * -Matt&n; */
multiline_comment|/* PMD_SHIFT determines the size of the area mapped by the PTE pages */
DECL|macro|PMD_SHIFT
mdefine_line|#define PMD_SHIFT&t;(PAGE_SHIFT + PTE_SHIFT)
DECL|macro|PMD_SIZE
mdefine_line|#define PMD_SIZE&t;(1UL &lt;&lt; PMD_SHIFT)
DECL|macro|PMD_MASK
mdefine_line|#define PMD_MASK&t;(~(PMD_SIZE-1))
multiline_comment|/* PGDIR_SHIFT determines what a top-level page table entry can map */
DECL|macro|PGDIR_SHIFT
mdefine_line|#define PGDIR_SHIFT&t;PMD_SHIFT
DECL|macro|PGDIR_SIZE
mdefine_line|#define PGDIR_SIZE&t;(1UL &lt;&lt; PGDIR_SHIFT)
DECL|macro|PGDIR_MASK
mdefine_line|#define PGDIR_MASK&t;(~(PGDIR_SIZE-1))
multiline_comment|/*&n; * entries per page directory level: our page-table tree is two-level, so&n; * we don&squot;t really have any PMD directory.&n; */
DECL|macro|PTRS_PER_PTE
mdefine_line|#define PTRS_PER_PTE&t;(1 &lt;&lt; PTE_SHIFT)
DECL|macro|PTRS_PER_PMD
mdefine_line|#define PTRS_PER_PMD&t;1
DECL|macro|PTRS_PER_PGD
mdefine_line|#define PTRS_PER_PGD&t;(1 &lt;&lt; (32 - PGDIR_SHIFT))
DECL|macro|USER_PTRS_PER_PGD
mdefine_line|#define USER_PTRS_PER_PGD&t;(TASK_SIZE / PGDIR_SIZE)
DECL|macro|FIRST_USER_PGD_NR
mdefine_line|#define FIRST_USER_PGD_NR&t;0
DECL|macro|USER_PGD_PTRS
mdefine_line|#define USER_PGD_PTRS (PAGE_OFFSET &gt;&gt; PGDIR_SHIFT)
DECL|macro|KERNEL_PGD_PTRS
mdefine_line|#define KERNEL_PGD_PTRS (PTRS_PER_PGD-USER_PGD_PTRS)
DECL|macro|pte_ERROR
mdefine_line|#define pte_ERROR(e) &bslash;&n;&t;printk(&quot;%s:%d: bad pte &quot;PTE_FMT&quot;.&bslash;n&quot;, __FILE__, __LINE__, pte_val(e))
DECL|macro|pmd_ERROR
mdefine_line|#define pmd_ERROR(e) &bslash;&n;&t;printk(&quot;%s:%d: bad pmd %08lx.&bslash;n&quot;, __FILE__, __LINE__, pmd_val(e))
DECL|macro|pgd_ERROR
mdefine_line|#define pgd_ERROR(e) &bslash;&n;&t;printk(&quot;%s:%d: bad pgd %08lx.&bslash;n&quot;, __FILE__, __LINE__, pgd_val(e))
multiline_comment|/*&n; * Just any arbitrary offset to the start of the vmalloc VM area: the&n; * current 64MB value just means that there will be a 64MB &quot;hole&quot; after the&n; * physical memory until the kernel virtual memory starts.  That means that&n; * any out-of-bounds memory accesses will hopefully be caught.&n; * The vmalloc() routines leaves a hole of 4kB between each vmalloced&n; * area for the same reason. ;)&n; *&n; * We no longer map larger than phys RAM with the BATs so we don&squot;t have&n; * to worry about the VMALLOC_OFFSET causing problems.  We do have to worry&n; * about clashes between our early calls to ioremap() that start growing down&n; * from ioremap_base being run into the VM area allocations (growing upwards&n; * from VMALLOC_START).  For this reason we have ioremap_bot to check when&n; * we actually run into our mappings setup in the early boot with the VM&n; * system.  This really does become a problem for machines with good amounts&n; * of RAM.  -- Cort&n; */
DECL|macro|VMALLOC_OFFSET
mdefine_line|#define VMALLOC_OFFSET (0x1000000) /* 16M */
macro_line|#ifdef CONFIG_44x
DECL|macro|VMALLOC_START
mdefine_line|#define VMALLOC_START (((_ALIGN((long)high_memory, PPC44x_PIN_SIZE) + VMALLOC_OFFSET) &amp; ~(VMALLOC_OFFSET-1)))
macro_line|#else
DECL|macro|VMALLOC_START
mdefine_line|#define VMALLOC_START ((((long)high_memory + VMALLOC_OFFSET) &amp; ~(VMALLOC_OFFSET-1)))
macro_line|#endif
DECL|macro|VMALLOC_END
mdefine_line|#define VMALLOC_END&t;ioremap_bot
multiline_comment|/*&n; * Bits in a linux-style PTE.  These match the bits in the&n; * (hardware-defined) PowerPC PTE as closely as possible.&n; */
macro_line|#if defined(CONFIG_40x)
multiline_comment|/* There are several potential gotchas here.  The 40x hardware TLBLO&n;   field looks like this:&n;&n;   0  1  2  3  4  ... 18 19 20 21 22 23 24 25 26 27 28 29 30 31&n;   RPN.....................  0  0 EX WR ZSEL.......  W  I  M  G&n;&n;   Where possible we make the Linux PTE bits match up with this&n;&n;   - bits 20 and 21 must be cleared, because we use 4k pages (40x can&n;     support down to 1k pages), this is done in the TLBMiss exception&n;     handler.&n;   - We use only zones 0 (for kernel pages) and 1 (for user pages)&n;     of the 16 available.  Bit 24-26 of the TLB are cleared in the TLB&n;     miss handler.  Bit 27 is PAGE_USER, thus selecting the correct&n;     zone.&n;   - PRESENT *must* be in the bottom two bits because swap cache&n;     entries use the top 30 bits.  Because 40x doesn&squot;t support SMP&n;     anyway, M is irrelevant so we borrow it for PAGE_PRESENT.  Bit 30&n;     is cleared in the TLB miss handler before the TLB entry is loaded.&n;   - All other bits of the PTE are loaded into TLBLO without&n;     modification, leaving us only the bits 20, 21, 24, 25, 26, 30 for&n;     software PTE bits.  We actually use use bits 21, 24, 25, and&n;     30 respectively for the software bits: ACCESSED, DIRTY, RW, and&n;     PRESENT.&n;*/
multiline_comment|/* Definitions for 40x embedded chips. */
DECL|macro|_PAGE_GUARDED
mdefine_line|#define&t;_PAGE_GUARDED&t;0x001&t;/* G: page is guarded from prefetch */
DECL|macro|_PAGE_FILE
mdefine_line|#define _PAGE_FILE&t;0x001&t;/* when !present: nonlinear file mapping */
DECL|macro|_PAGE_PRESENT
mdefine_line|#define _PAGE_PRESENT&t;0x002&t;/* software: PTE contains a translation */
DECL|macro|_PAGE_NO_CACHE
mdefine_line|#define&t;_PAGE_NO_CACHE&t;0x004&t;/* I: caching is inhibited */
DECL|macro|_PAGE_WRITETHRU
mdefine_line|#define&t;_PAGE_WRITETHRU&t;0x008&t;/* W: caching is write-through */
DECL|macro|_PAGE_USER
mdefine_line|#define&t;_PAGE_USER&t;0x010&t;/* matches one of the zone permission bits */
DECL|macro|_PAGE_RW
mdefine_line|#define&t;_PAGE_RW&t;0x040&t;/* software: Writes permitted */
DECL|macro|_PAGE_DIRTY
mdefine_line|#define&t;_PAGE_DIRTY&t;0x080&t;/* software: dirty page */
DECL|macro|_PAGE_HWWRITE
mdefine_line|#define _PAGE_HWWRITE&t;0x100&t;/* hardware: Dirty &amp; RW, set in exception */
DECL|macro|_PAGE_HWEXEC
mdefine_line|#define _PAGE_HWEXEC&t;0x200&t;/* hardware: EX permission */
DECL|macro|_PAGE_ACCESSED
mdefine_line|#define _PAGE_ACCESSED&t;0x400&t;/* software: R: page referenced */
DECL|macro|_PMD_PRESENT
mdefine_line|#define _PMD_PRESENT&t;0x400&t;/* PMD points to page of PTEs */
DECL|macro|_PMD_BAD
mdefine_line|#define _PMD_BAD&t;0x802
DECL|macro|_PMD_SIZE
mdefine_line|#define _PMD_SIZE&t;0x0e0&t;/* size field, != 0 for large-page PMD entry */
DECL|macro|_PMD_SIZE_4M
mdefine_line|#define _PMD_SIZE_4M&t;0x0c0
DECL|macro|_PMD_SIZE_16M
mdefine_line|#define _PMD_SIZE_16M&t;0x0e0
DECL|macro|PMD_PAGE_SIZE
mdefine_line|#define PMD_PAGE_SIZE(pmdval)&t;(1024 &lt;&lt; (((pmdval) &amp; _PMD_SIZE) &gt;&gt; 4))
macro_line|#elif defined(CONFIG_44x)
multiline_comment|/*&n; * Definitions for PPC440&n; *&n; * Because of the 3 word TLB entries to support 36-bit addressing,&n; * the attribute are difficult to map in such a fashion that they&n; * are easily loaded during exception processing.  I decided to&n; * organize the entry so the ERPN is the only portion in the&n; * upper word of the PTE and the attribute bits below are packed&n; * in as sensibly as they can be in the area below a 4KB page size&n; * oriented RPN.  This at least makes it easy to load the RPN and&n; * ERPN fields in the TLB. -Matt&n; *&n; * Note that these bits preclude future use of a page size&n; * less than 4KB.&n; */
DECL|macro|_PAGE_PRESENT
mdefine_line|#define _PAGE_PRESENT&t;0x00000001&t;&t;/* S: PTE valid */
DECL|macro|_PAGE_RW
mdefine_line|#define&t;_PAGE_RW&t;0x00000002&t;&t;/* S: Write permission */
DECL|macro|_PAGE_DIRTY
mdefine_line|#define&t;_PAGE_DIRTY&t;0x00000004&t;&t;/* S: Page dirty */
DECL|macro|_PAGE_ACCESSED
mdefine_line|#define _PAGE_ACCESSED&t;0x00000008&t;&t;/* S: Page referenced */
DECL|macro|_PAGE_HWWRITE
mdefine_line|#define _PAGE_HWWRITE&t;0x00000010&t;&t;/* H: Dirty &amp; RW */
DECL|macro|_PAGE_HWEXEC
mdefine_line|#define _PAGE_HWEXEC&t;0x00000020&t;&t;/* H: Execute permission */
DECL|macro|_PAGE_USER
mdefine_line|#define&t;_PAGE_USER&t;0x00000040&t;&t;/* S: User page */
DECL|macro|_PAGE_ENDIAN
mdefine_line|#define&t;_PAGE_ENDIAN&t;0x00000080&t;&t;/* H: E bit */
DECL|macro|_PAGE_GUARDED
mdefine_line|#define&t;_PAGE_GUARDED&t;0x00000100&t;&t;/* H: G bit */
DECL|macro|_PAGE_COHERENT
mdefine_line|#define&t;_PAGE_COHERENT&t;0x00000200&t;&t;/* H: M bit */
DECL|macro|_PAGE_FILE
mdefine_line|#define _PAGE_FILE&t;0x00000400&t;&t;/* S: nonlinear file mapping */
DECL|macro|_PAGE_NO_CACHE
mdefine_line|#define&t;_PAGE_NO_CACHE&t;0x00000400&t;&t;/* H: I bit */
DECL|macro|_PAGE_WRITETHRU
mdefine_line|#define&t;_PAGE_WRITETHRU&t;0x00000800&t;&t;/* H: W bit */
multiline_comment|/* TODO: Add large page lowmem mapping support */
DECL|macro|_PMD_PRESENT
mdefine_line|#define _PMD_PRESENT&t;0
DECL|macro|_PMD_PRESENT_MASK
mdefine_line|#define _PMD_PRESENT_MASK (PAGE_MASK)
DECL|macro|_PMD_BAD
mdefine_line|#define _PMD_BAD&t;(~PAGE_MASK)
multiline_comment|/* ERPN in a PTE never gets cleared, ignore it */
DECL|macro|_PTE_NONE_MASK
mdefine_line|#define _PTE_NONE_MASK&t;0xffffffff00000000ULL
macro_line|#elif defined(CONFIG_E500)
multiline_comment|/*&n;   MMU Assist Register 3:&n;&n;   32 33 34 35 36  ... 50 51 52 53 54 55 56 57 58 59 60 61 62 63&n;   RPN......................  0  0 U0 U1 U2 U3 UX SX UW SW UR SR&n;&n;   - PRESENT *must* be in the bottom three bits because swap cache&n;     entries use the top 29 bits.&n;&n;   - FILE *must* be in the bottom three bits because swap cache&n;     entries use the top 29 bits.&n;*/
multiline_comment|/* Definitions for e500 core */
DECL|macro|_PAGE_PRESENT
mdefine_line|#define _PAGE_PRESENT&t;0x001&t;/* S: PTE contains a translation */
DECL|macro|_PAGE_USER
mdefine_line|#define _PAGE_USER&t;0x002&t;/* S: User page (maps to UR) */
DECL|macro|_PAGE_FILE
mdefine_line|#define _PAGE_FILE&t;0x002&t;/* S: when !present: nonlinear file mapping */
DECL|macro|_PAGE_ACCESSED
mdefine_line|#define _PAGE_ACCESSED&t;0x004&t;/* S: Page referenced */
DECL|macro|_PAGE_HWWRITE
mdefine_line|#define _PAGE_HWWRITE&t;0x008&t;/* H: Dirty &amp; RW, set in exception */
DECL|macro|_PAGE_RW
mdefine_line|#define _PAGE_RW&t;0x010&t;/* S: Write permission */
DECL|macro|_PAGE_HWEXEC
mdefine_line|#define _PAGE_HWEXEC&t;0x020&t;/* H: UX permission */
DECL|macro|_PAGE_ENDIAN
mdefine_line|#define _PAGE_ENDIAN&t;0x040&t;/* H: E bit */
DECL|macro|_PAGE_GUARDED
mdefine_line|#define _PAGE_GUARDED&t;0x080&t;/* H: G bit */
DECL|macro|_PAGE_COHERENT
mdefine_line|#define _PAGE_COHERENT&t;0x100&t;/* H: M bit */
DECL|macro|_PAGE_NO_CACHE
mdefine_line|#define _PAGE_NO_CACHE&t;0x200&t;/* H: I bit */
DECL|macro|_PAGE_WRITETHRU
mdefine_line|#define _PAGE_WRITETHRU&t;0x400&t;/* H: W bit */
DECL|macro|_PAGE_DIRTY
mdefine_line|#define _PAGE_DIRTY&t;0x800&t;/* S: Page dirty */
DECL|macro|_PMD_PRESENT
mdefine_line|#define _PMD_PRESENT&t;0
DECL|macro|_PMD_PRESENT_MASK
mdefine_line|#define _PMD_PRESENT_MASK (PAGE_MASK)
DECL|macro|_PMD_BAD
mdefine_line|#define _PMD_BAD&t;(~PAGE_MASK)
DECL|macro|NUM_TLBCAMS
mdefine_line|#define NUM_TLBCAMS&t;(16)
macro_line|#elif defined(CONFIG_8xx)
multiline_comment|/* Definitions for 8xx embedded chips. */
DECL|macro|_PAGE_PRESENT
mdefine_line|#define _PAGE_PRESENT&t;0x0001&t;/* Page is valid */
DECL|macro|_PAGE_FILE
mdefine_line|#define _PAGE_FILE&t;0x0002&t;/* when !present: nonlinear file mapping */
DECL|macro|_PAGE_NO_CACHE
mdefine_line|#define _PAGE_NO_CACHE&t;0x0002&t;/* I: cache inhibit */
DECL|macro|_PAGE_SHARED
mdefine_line|#define _PAGE_SHARED&t;0x0004&t;/* No ASID (context) compare */
multiline_comment|/* These five software bits must be masked out when the entry is loaded&n; * into the TLB.&n; */
DECL|macro|_PAGE_EXEC
mdefine_line|#define _PAGE_EXEC&t;0x0008&t;/* software: i-cache coherency required */
DECL|macro|_PAGE_GUARDED
mdefine_line|#define _PAGE_GUARDED&t;0x0010&t;/* software: guarded access */
DECL|macro|_PAGE_DIRTY
mdefine_line|#define _PAGE_DIRTY&t;0x0020&t;/* software: page changed */
DECL|macro|_PAGE_RW
mdefine_line|#define _PAGE_RW&t;0x0040&t;/* software: user write access allowed */
DECL|macro|_PAGE_ACCESSED
mdefine_line|#define _PAGE_ACCESSED&t;0x0080&t;/* software: page referenced */
multiline_comment|/* Setting any bits in the nibble with the follow two controls will&n; * require a TLB exception handler change.  It is assumed unused bits&n; * are always zero.&n; */
DECL|macro|_PAGE_HWWRITE
mdefine_line|#define _PAGE_HWWRITE&t;0x0100&t;/* h/w write enable: never set in Linux PTE */
DECL|macro|_PAGE_USER
mdefine_line|#define _PAGE_USER&t;0x0800&t;/* One of the PP bits, the other is USER&amp;~RW */
DECL|macro|_PMD_PRESENT
mdefine_line|#define _PMD_PRESENT&t;0x0001
DECL|macro|_PMD_BAD
mdefine_line|#define _PMD_BAD&t;0x0ff0
DECL|macro|_PMD_PAGE_MASK
mdefine_line|#define _PMD_PAGE_MASK&t;0x000c
DECL|macro|_PMD_PAGE_8M
mdefine_line|#define _PMD_PAGE_8M&t;0x000c
multiline_comment|/*&n; * The 8xx TLB miss handler allegedly sets _PAGE_ACCESSED in the PTE&n; * for an address even if _PAGE_PRESENT is not set, as a performance&n; * optimization.  This is a bug if you ever want to use swap unless&n; * _PAGE_ACCESSED is 2, which it isn&squot;t, or unless you have 8xx-specific&n; * definitions for __swp_entry etc. below, which would be gross.&n; *  -- paulus&n; */
DECL|macro|_PTE_NONE_MASK
mdefine_line|#define _PTE_NONE_MASK _PAGE_ACCESSED
macro_line|#else /* CONFIG_6xx */
multiline_comment|/* Definitions for 60x, 740/750, etc. */
DECL|macro|_PAGE_PRESENT
mdefine_line|#define _PAGE_PRESENT&t;0x001&t;/* software: pte contains a translation */
DECL|macro|_PAGE_HASHPTE
mdefine_line|#define _PAGE_HASHPTE&t;0x002&t;/* hash_page has made an HPTE for this pte */
DECL|macro|_PAGE_FILE
mdefine_line|#define _PAGE_FILE&t;0x004&t;/* when !present: nonlinear file mapping */
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
DECL|macro|_PTE_NONE_MASK
mdefine_line|#define _PTE_NONE_MASK&t;_PAGE_HASHPTE
DECL|macro|_PMD_PRESENT
mdefine_line|#define _PMD_PRESENT&t;0
DECL|macro|_PMD_PRESENT_MASK
mdefine_line|#define _PMD_PRESENT_MASK (PAGE_MASK)
DECL|macro|_PMD_BAD
mdefine_line|#define _PMD_BAD&t;(~PAGE_MASK)
macro_line|#endif
multiline_comment|/*&n; * Some bits are only used on some cpu families...&n; */
macro_line|#ifndef _PAGE_HASHPTE
DECL|macro|_PAGE_HASHPTE
mdefine_line|#define _PAGE_HASHPTE&t;0
macro_line|#endif
macro_line|#ifndef _PTE_NONE_MASK
DECL|macro|_PTE_NONE_MASK
mdefine_line|#define _PTE_NONE_MASK 0
macro_line|#endif
macro_line|#ifndef _PAGE_SHARED
DECL|macro|_PAGE_SHARED
mdefine_line|#define _PAGE_SHARED&t;0
macro_line|#endif
macro_line|#ifndef _PAGE_HWWRITE
DECL|macro|_PAGE_HWWRITE
mdefine_line|#define _PAGE_HWWRITE&t;0
macro_line|#endif
macro_line|#ifndef _PAGE_HWEXEC
DECL|macro|_PAGE_HWEXEC
mdefine_line|#define _PAGE_HWEXEC&t;0
macro_line|#endif
macro_line|#ifndef _PAGE_EXEC
DECL|macro|_PAGE_EXEC
mdefine_line|#define _PAGE_EXEC&t;0
macro_line|#endif
macro_line|#ifndef _PMD_PRESENT_MASK
DECL|macro|_PMD_PRESENT_MASK
mdefine_line|#define _PMD_PRESENT_MASK&t;_PMD_PRESENT
macro_line|#endif
macro_line|#ifndef _PMD_SIZE
DECL|macro|_PMD_SIZE
mdefine_line|#define _PMD_SIZE&t;0
DECL|macro|PMD_PAGE_SIZE
mdefine_line|#define PMD_PAGE_SIZE(pmd)&t;bad_call_to_PMD_PAGE_SIZE()
macro_line|#endif
DECL|macro|_PAGE_CHG_MASK
mdefine_line|#define _PAGE_CHG_MASK&t;(PAGE_MASK | _PAGE_ACCESSED | _PAGE_DIRTY)
multiline_comment|/*&n; * Note: the _PAGE_COHERENT bit automatically gets set in the hardware&n; * PTE if CONFIG_SMP is defined (hash_page does this); there is no need&n; * to have it in the Linux PTE, and in fact the bit could be reused for&n; * another purpose.  -- paulus.&n; */
macro_line|#ifdef CONFIG_44x
DECL|macro|_PAGE_BASE
mdefine_line|#define _PAGE_BASE&t;(_PAGE_PRESENT | _PAGE_ACCESSED | _PAGE_GUARDED)
macro_line|#else
DECL|macro|_PAGE_BASE
mdefine_line|#define _PAGE_BASE&t;(_PAGE_PRESENT | _PAGE_ACCESSED)
macro_line|#endif
DECL|macro|_PAGE_WRENABLE
mdefine_line|#define _PAGE_WRENABLE&t;(_PAGE_RW | _PAGE_DIRTY | _PAGE_HWWRITE)
DECL|macro|_PAGE_KERNEL
mdefine_line|#define _PAGE_KERNEL&t;(_PAGE_BASE | _PAGE_SHARED | _PAGE_WRENABLE)
macro_line|#ifdef CONFIG_PPC_STD_MMU
multiline_comment|/* On standard PPC MMU, no user access implies kernel read/write access,&n; * so to write-protect kernel memory we must turn on user access */
DECL|macro|_PAGE_KERNEL_RO
mdefine_line|#define _PAGE_KERNEL_RO&t;(_PAGE_BASE | _PAGE_SHARED | _PAGE_USER)
macro_line|#else
DECL|macro|_PAGE_KERNEL_RO
mdefine_line|#define _PAGE_KERNEL_RO&t;(_PAGE_BASE | _PAGE_SHARED)
macro_line|#endif
DECL|macro|_PAGE_IO
mdefine_line|#define _PAGE_IO&t;(_PAGE_KERNEL | _PAGE_NO_CACHE | _PAGE_GUARDED)
DECL|macro|_PAGE_RAM
mdefine_line|#define _PAGE_RAM&t;(_PAGE_KERNEL | _PAGE_HWEXEC)
macro_line|#if defined(CONFIG_KGDB) || defined(CONFIG_XMON) || defined(CONFIG_BDI_SWITCH)
multiline_comment|/* We want the debuggers to be able to set breakpoints anywhere, so&n; * don&squot;t write protect the kernel text */
DECL|macro|_PAGE_RAM_TEXT
mdefine_line|#define _PAGE_RAM_TEXT&t;_PAGE_RAM
macro_line|#else
DECL|macro|_PAGE_RAM_TEXT
mdefine_line|#define _PAGE_RAM_TEXT&t;(_PAGE_KERNEL_RO | _PAGE_HWEXEC)
macro_line|#endif
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
mdefine_line|#define PAGE_KERNEL&t;&t;__pgprot(_PAGE_RAM)
DECL|macro|PAGE_KERNEL_NOCACHE
mdefine_line|#define PAGE_KERNEL_NOCACHE&t;__pgprot(_PAGE_IO)
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
multiline_comment|/* Make sure we get a link error if PMD_PAGE_SIZE is ever called on a&n; * kernel without large page PMD support */
r_extern
r_int
r_int
id|bad_call_to_PMD_PAGE_SIZE
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * Conversions between PTE values and page frame numbers.&n; */
DECL|macro|pte_pfn
mdefine_line|#define pte_pfn(x)&t;&t;(pte_val(x) &gt;&gt; PAGE_SHIFT)
DECL|macro|pte_page
mdefine_line|#define pte_page(x)&t;&t;pfn_to_page(pte_pfn(x))
DECL|macro|pfn_pte
mdefine_line|#define pfn_pte(pfn, prot)&t;__pte(((pte_t)(pfn) &lt;&lt; PAGE_SHIFT) | pgprot_val(prot))
DECL|macro|mk_pte
mdefine_line|#define mk_pte(page, prot)&t;pfn_pte(page_to_pfn(page), prot)
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
mdefine_line|#define&t;pmd_bad(pmd)&t;&t;(pmd_val(pmd) &amp; _PMD_BAD)
DECL|macro|pmd_present
mdefine_line|#define&t;pmd_present(pmd)&t;(pmd_val(pmd) &amp; _PMD_PRESENT_MASK)
DECL|macro|pmd_clear
mdefine_line|#define&t;pmd_clear(pmdp)&t;&t;do { pmd_val(*(pmdp)) = 0; } while (0)
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
DECL|function|pte_file
r_static
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
multiline_comment|/*&n; * Atomic PTE updates.&n; *&n; * pte_update clears and sets bit atomically, and returns&n; * the old pte value.&n; * The ((unsigned long)(p+1) - 4) hack is to get to the least-significant&n; * 32 bits of the PTE regardless of whether PTEs are 32 or 64 bits.&n; */
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
l_string|&quot;&bslash;&n;1:&t;lwarx&t;%0,0,%3&bslash;n&bslash;&n;&t;andc&t;%1,%0,%4&bslash;n&bslash;&n;&t;or&t;%1,%1,%5&bslash;n&quot;
id|PPC405_ERR77
c_func
(paren
l_int|0
comma
op_mod
l_int|3
)paren
l_string|&quot;&t;stwcx.&t;%1,0,%3&bslash;n&bslash;&n;&t;bne-&t;1b&quot;
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
(paren
r_int
r_int
)paren
(paren
id|p
op_plus
l_int|1
)paren
op_minus
l_int|4
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
multiline_comment|/*&n; * set_pte stores a linux PTE into the linux page table.&n; * On machines which use an MMU hash table we avoid changing the&n; * _PAGE_HASHPTE bit.&n; */
DECL|function|set_pte
r_static
r_inline
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
(brace
macro_line|#if _PAGE_HASHPTE != 0
id|pte_update
c_func
(paren
id|ptep
comma
op_complement
id|_PAGE_HASHPTE
comma
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
op_complement
id|_PAGE_HASHPTE
)paren
suffix:semicolon
macro_line|#else
op_star
id|ptep
op_assign
id|pte
suffix:semicolon
macro_line|#endif
)brace
r_extern
r_void
id|flush_hash_one_pte
c_func
(paren
id|pte_t
op_star
id|ptep
)paren
suffix:semicolon
multiline_comment|/*&n; * 2.6 calles this without flushing the TLB entry, this is wrong&n; * for our hash-based implementation, we fix that up here&n; */
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
r_int
r_int
id|old
suffix:semicolon
id|old
op_assign
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
suffix:semicolon
macro_line|#if _PAGE_HASHPTE != 0
r_if
c_cond
(paren
id|old
op_amp
id|_PAGE_HASHPTE
)paren
id|flush_hash_one_pte
c_func
(paren
id|ptep
)paren
suffix:semicolon
macro_line|#endif
r_return
id|old
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
DECL|macro|__HAVE_ARCH_PTEP_SET_ACCESS_FLAGS
mdefine_line|#define __HAVE_ARCH_PTEP_SET_ACCESS_FLAGS
DECL|function|__ptep_set_access_flags
r_static
r_inline
r_void
id|__ptep_set_access_flags
c_func
(paren
id|pte_t
op_star
id|ptep
comma
id|pte_t
id|entry
comma
r_int
id|dirty
)paren
(brace
r_int
r_int
id|bits
op_assign
id|pte_val
c_func
(paren
id|entry
)paren
op_amp
(paren
id|_PAGE_DIRTY
op_or
id|_PAGE_ACCESSED
op_or
id|_PAGE_RW
)paren
suffix:semicolon
id|pte_update
c_func
(paren
id|ptep
comma
l_int|0
comma
id|bits
)paren
suffix:semicolon
)brace
DECL|macro|ptep_set_access_flags
mdefine_line|#define  ptep_set_access_flags(__vma, __address, __ptep, __entry, __dirty) &bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&t;   &bslash;&n;&t;&t;__ptep_set_access_flags(__ptep, __entry, __dirty);&t;   &bslash;&n;&t;&t;flush_tlb_page_nohash(__vma, __address);&t;       &t;   &bslash;&n;&t;} while(0)
multiline_comment|/*&n; * Macro to mark a page protection value as &quot;uncacheable&quot;.&n; */
DECL|macro|pgprot_noncached
mdefine_line|#define pgprot_noncached(prot)&t;(__pgprot(pgprot_val(prot) | _PAGE_NO_CACHE | _PAGE_GUARDED))
DECL|macro|pte_same
mdefine_line|#define pte_same(A,B)&t;(((pte_val(A) ^ pte_val(B)) &amp; ~_PAGE_HASHPTE) == 0)
multiline_comment|/*&n; * Note that on Book E processors, the pmd contains the kernel virtual&n; * (lowmem) address of the pte page.  The physical address is less useful&n; * because everything runs with translation enabled (even the TLB miss&n; * handler).  On everything else the pmd contains the physical address&n; * of the pte page.  -- paulus&n; */
macro_line|#ifndef CONFIG_BOOKE
DECL|macro|pmd_page_kernel
mdefine_line|#define pmd_page_kernel(pmd)&t;&bslash;&n;&t;((unsigned long) __va(pmd_val(pmd) &amp; PAGE_MASK))
DECL|macro|pmd_page
mdefine_line|#define pmd_page(pmd)&t;&t;&bslash;&n;&t;(mem_map + (pmd_val(pmd) &gt;&gt; PAGE_SHIFT))
macro_line|#else
DECL|macro|pmd_page_kernel
mdefine_line|#define pmd_page_kernel(pmd)&t;&bslash;&n;&t;((unsigned long) (pmd_val(pmd) &amp; PAGE_MASK))
DECL|macro|pmd_page
mdefine_line|#define pmd_page(pmd)&t;&t;&bslash;&n;&t;(mem_map + (__pa(pmd_val(pmd)) &gt;&gt; PAGE_SHIFT))
macro_line|#endif
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
DECL|macro|pte_index
mdefine_line|#define pte_index(address)&t;&t;&bslash;&n;&t;(((address) &gt;&gt; PAGE_SHIFT) &amp; (PTRS_PER_PTE - 1))
DECL|macro|pte_offset_kernel
mdefine_line|#define pte_offset_kernel(dir, addr)&t;&bslash;&n;&t;((pte_t *) pmd_page_kernel(*(dir)) + pte_index(addr))
DECL|macro|pte_offset_map
mdefine_line|#define pte_offset_map(dir, addr)&t;&t;&bslash;&n;&t;((pte_t *) kmap_atomic(pmd_page(*(dir)), KM_PTE0) + pte_index(addr))
DECL|macro|pte_offset_map_nested
mdefine_line|#define pte_offset_map_nested(dir, addr)&t;&bslash;&n;&t;((pte_t *) kmap_atomic(pmd_page(*(dir)), KM_PTE1) + pte_index(addr))
DECL|macro|pte_unmap
mdefine_line|#define pte_unmap(pte)&t;&t;kunmap_atomic(pte, KM_PTE0)
DECL|macro|pte_unmap_nested
mdefine_line|#define pte_unmap_nested(pte)&t;kunmap_atomic(pte, KM_PTE1)
r_extern
id|pgd_t
id|swapper_pg_dir
(braket
id|PTRS_PER_PGD
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
multiline_comment|/*&n; * When flushing the tlb entry for a page, we also need to flush the hash&n; * table entry.  flush_hash_pages is assembler (for speed) in hashtable.S.&n; */
r_extern
r_int
id|flush_hash_pages
c_func
(paren
r_int
id|context
comma
r_int
r_int
id|va
comma
r_int
r_int
id|pmdval
comma
r_int
id|count
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
r_int
r_int
id|pmdval
)paren
suffix:semicolon
multiline_comment|/*&n; * Encode and decode a swap entry.&n; * Note that the bits we use in a PTE for representing a swap entry&n; * must not include the _PAGE_PRESENT bit, the _PAGE_FILE bit, or the&n; *_PAGE_HASHPTE bit (if used).  -- paulus&n; */
DECL|macro|__swp_type
mdefine_line|#define __swp_type(entry)&t;&t;((entry).val &amp; 0x1f)
DECL|macro|__swp_offset
mdefine_line|#define __swp_offset(entry)&t;&t;((entry).val &gt;&gt; 5)
DECL|macro|__swp_entry
mdefine_line|#define __swp_entry(type, offset)&t;((swp_entry_t) { (type) | ((offset) &lt;&lt; 5) })
DECL|macro|__pte_to_swp_entry
mdefine_line|#define __pte_to_swp_entry(pte)&t;&t;((swp_entry_t) { pte_val(pte) &gt;&gt; 3 })
DECL|macro|__swp_entry_to_pte
mdefine_line|#define __swp_entry_to_pte(x)&t;&t;((pte_t) { (x).val &lt;&lt; 3 })
multiline_comment|/* Encode and decode a nonlinear file mapping entry */
DECL|macro|PTE_FILE_MAX_BITS
mdefine_line|#define PTE_FILE_MAX_BITS&t;29
DECL|macro|pte_to_pgoff
mdefine_line|#define pte_to_pgoff(pte)&t;(pte_val(pte) &gt;&gt; 3)
DECL|macro|pgoff_to_pte
mdefine_line|#define pgoff_to_pte(off)&t;((pte_t) { ((off) &lt;&lt; 3) | _PAGE_FILE })
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
id|__attribute_const__
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
multiline_comment|/*&n; * Set cache mode of (kernel space) address range.&n; */
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
macro_line|#ifdef CONFIG_PHYS_64BIT
r_extern
r_int
id|remap_pfn_range
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|from
comma
r_int
r_int
id|paddr
comma
r_int
r_int
id|size
comma
id|pgprot_t
id|prot
)paren
suffix:semicolon
DECL|function|io_remap_page_range
r_static
r_inline
r_int
id|io_remap_page_range
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|vaddr
comma
r_int
r_int
id|paddr
comma
r_int
r_int
id|size
comma
id|pgprot_t
id|prot
)paren
(brace
id|phys_addr_t
id|paddr64
op_assign
id|fixup_bigphys_addr
c_func
(paren
id|paddr
comma
id|size
)paren
suffix:semicolon
r_return
id|remap_pfn_range
c_func
(paren
id|vma
comma
id|vaddr
comma
id|paddr64
op_rshift
id|PAGE_SHIFT
comma
id|size
comma
id|prot
)paren
suffix:semicolon
)brace
macro_line|#else
DECL|macro|io_remap_page_range
mdefine_line|#define io_remap_page_range(vma, vaddr, paddr, size, prot)&t;&t;&bslash;&n;&t;&t;remap_pfn_range(vma, vaddr, (paddr) &gt;&gt; PAGE_SHIFT, size, prot)
macro_line|#endif
multiline_comment|/*&n; * No page table caches to initialise&n; */
DECL|macro|pgtable_cache_init
mdefine_line|#define pgtable_cache_init()&t;do { } while (0)
r_extern
r_int
id|get_pteptr
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
r_int
r_int
id|addr
comma
id|pte_t
op_star
op_star
id|ptep
)paren
suffix:semicolon
macro_line|#endif /* !__ASSEMBLY__ */
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
macro_line|#endif /* _PPC_PGTABLE_H */
macro_line|#endif /* __KERNEL__ */
eof
