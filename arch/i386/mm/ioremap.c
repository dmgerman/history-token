multiline_comment|/*&n; * arch/i386/mm/ioremap.c&n; *&n; * Re-map IO memory to kernel address space so that we can access it.&n; * This is needed for high PCI addresses that aren&squot;t mapped in the&n; * 640k-1MB IO memory area on PC&squot;s&n; *&n; * (C) Copyright 1995 1996 Linus Torvalds&n; */
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/fixmap.h&gt;
macro_line|#include &lt;asm/cacheflush.h&gt;
macro_line|#include &lt;asm/tlbflush.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
DECL|macro|ISA_START_ADDRESS
mdefine_line|#define ISA_START_ADDRESS&t;0xa0000
DECL|macro|ISA_END_ADDRESS
mdefine_line|#define ISA_END_ADDRESS&t;&t;0x100000
DECL|function|ioremap_pte_range
r_static
r_int
id|ioremap_pte_range
c_func
(paren
id|pmd_t
op_star
id|pmd
comma
r_int
r_int
id|addr
comma
r_int
r_int
id|end
comma
r_int
r_int
id|phys_addr
comma
r_int
r_int
id|flags
)paren
(brace
id|pte_t
op_star
id|pte
suffix:semicolon
r_int
r_int
id|pfn
suffix:semicolon
id|pfn
op_assign
id|phys_addr
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|pte
op_assign
id|pte_alloc_kernel
c_func
(paren
op_amp
id|init_mm
comma
id|pmd
comma
id|addr
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pte
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_do
(brace
id|BUG_ON
c_func
(paren
op_logical_neg
id|pte_none
c_func
(paren
op_star
id|pte
)paren
)paren
suffix:semicolon
id|set_pte
c_func
(paren
id|pte
comma
id|pfn_pte
c_func
(paren
id|pfn
comma
id|__pgprot
c_func
(paren
id|_PAGE_PRESENT
op_or
id|_PAGE_RW
op_or
id|_PAGE_DIRTY
op_or
id|_PAGE_ACCESSED
op_or
id|flags
)paren
)paren
)paren
suffix:semicolon
id|pfn
op_increment
suffix:semicolon
)brace
r_while
c_loop
(paren
id|pte
op_increment
comma
id|addr
op_add_assign
id|PAGE_SIZE
comma
id|addr
op_ne
id|end
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ioremap_pmd_range
r_static
r_inline
r_int
id|ioremap_pmd_range
c_func
(paren
id|pud_t
op_star
id|pud
comma
r_int
r_int
id|addr
comma
r_int
r_int
id|end
comma
r_int
r_int
id|phys_addr
comma
r_int
r_int
id|flags
)paren
(brace
id|pmd_t
op_star
id|pmd
suffix:semicolon
r_int
r_int
id|next
suffix:semicolon
id|phys_addr
op_sub_assign
id|addr
suffix:semicolon
id|pmd
op_assign
id|pmd_alloc
c_func
(paren
op_amp
id|init_mm
comma
id|pud
comma
id|addr
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pmd
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_do
(brace
id|next
op_assign
id|pmd_addr_end
c_func
(paren
id|addr
comma
id|end
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ioremap_pte_range
c_func
(paren
id|pmd
comma
id|addr
comma
id|next
comma
id|phys_addr
op_plus
id|addr
comma
id|flags
)paren
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
r_while
c_loop
(paren
id|pmd
op_increment
comma
id|addr
op_assign
id|next
comma
id|addr
op_ne
id|end
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ioremap_pud_range
r_static
r_inline
r_int
id|ioremap_pud_range
c_func
(paren
id|pgd_t
op_star
id|pgd
comma
r_int
r_int
id|addr
comma
r_int
r_int
id|end
comma
r_int
r_int
id|phys_addr
comma
r_int
r_int
id|flags
)paren
(brace
id|pud_t
op_star
id|pud
suffix:semicolon
r_int
r_int
id|next
suffix:semicolon
id|phys_addr
op_sub_assign
id|addr
suffix:semicolon
id|pud
op_assign
id|pud_alloc
c_func
(paren
op_amp
id|init_mm
comma
id|pgd
comma
id|addr
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pud
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_do
(brace
id|next
op_assign
id|pud_addr_end
c_func
(paren
id|addr
comma
id|end
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ioremap_pmd_range
c_func
(paren
id|pud
comma
id|addr
comma
id|next
comma
id|phys_addr
op_plus
id|addr
comma
id|flags
)paren
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
r_while
c_loop
(paren
id|pud
op_increment
comma
id|addr
op_assign
id|next
comma
id|addr
op_ne
id|end
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ioremap_page_range
r_static
r_int
id|ioremap_page_range
c_func
(paren
r_int
r_int
id|addr
comma
r_int
r_int
id|end
comma
r_int
r_int
id|phys_addr
comma
r_int
r_int
id|flags
)paren
(brace
id|pgd_t
op_star
id|pgd
suffix:semicolon
r_int
r_int
id|next
suffix:semicolon
r_int
id|err
suffix:semicolon
id|BUG_ON
c_func
(paren
id|addr
op_ge
id|end
)paren
suffix:semicolon
id|flush_cache_all
c_func
(paren
)paren
suffix:semicolon
id|phys_addr
op_sub_assign
id|addr
suffix:semicolon
id|pgd
op_assign
id|pgd_offset_k
c_func
(paren
id|addr
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|init_mm.page_table_lock
)paren
suffix:semicolon
r_do
(brace
id|next
op_assign
id|pgd_addr_end
c_func
(paren
id|addr
comma
id|end
)paren
suffix:semicolon
id|err
op_assign
id|ioremap_pud_range
c_func
(paren
id|pgd
comma
id|addr
comma
id|next
comma
id|phys_addr
op_plus
id|addr
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_break
suffix:semicolon
)brace
r_while
c_loop
(paren
id|pgd
op_increment
comma
id|addr
op_assign
id|next
comma
id|addr
op_ne
id|end
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|init_mm.page_table_lock
)paren
suffix:semicolon
id|flush_tlb_all
c_func
(paren
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/*&n; * Generic mapping function (not visible outside):&n; */
multiline_comment|/*&n; * Remap an arbitrary physical address space into the kernel virtual&n; * address space. Needed when the kernel wants to access high addresses&n; * directly.&n; *&n; * NOTE! We need to allow non-page-aligned mappings too: we will obviously&n; * have to convert them into an offset in a page-aligned mapping, but the&n; * caller shouldn&squot;t need to know that small detail.&n; */
DECL|function|__ioremap
r_void
id|__iomem
op_star
id|__ioremap
c_func
(paren
r_int
r_int
id|phys_addr
comma
r_int
r_int
id|size
comma
r_int
r_int
id|flags
)paren
(brace
r_void
id|__iomem
op_star
id|addr
suffix:semicolon
r_struct
id|vm_struct
op_star
id|area
suffix:semicolon
r_int
r_int
id|offset
comma
id|last_addr
suffix:semicolon
multiline_comment|/* Don&squot;t allow wraparound or zero size */
id|last_addr
op_assign
id|phys_addr
op_plus
id|size
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|size
op_logical_or
id|last_addr
OL
id|phys_addr
)paren
r_return
l_int|NULL
suffix:semicolon
multiline_comment|/*&n;&t; * Don&squot;t remap the low PCI/ISA area, it&squot;s always mapped..&n;&t; */
r_if
c_cond
(paren
id|phys_addr
op_ge
id|ISA_START_ADDRESS
op_logical_and
id|last_addr
OL
id|ISA_END_ADDRESS
)paren
r_return
(paren
r_void
id|__iomem
op_star
)paren
id|phys_to_virt
c_func
(paren
id|phys_addr
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Don&squot;t allow anybody to remap normal RAM that we&squot;re using..&n;&t; */
r_if
c_cond
(paren
id|phys_addr
op_le
id|virt_to_phys
c_func
(paren
id|high_memory
op_minus
l_int|1
)paren
)paren
(brace
r_char
op_star
id|t_addr
comma
op_star
id|t_end
suffix:semicolon
r_struct
id|page
op_star
id|page
suffix:semicolon
id|t_addr
op_assign
id|__va
c_func
(paren
id|phys_addr
)paren
suffix:semicolon
id|t_end
op_assign
id|t_addr
op_plus
(paren
id|size
op_minus
l_int|1
)paren
suffix:semicolon
r_for
c_loop
(paren
id|page
op_assign
id|virt_to_page
c_func
(paren
id|t_addr
)paren
suffix:semicolon
id|page
op_le
id|virt_to_page
c_func
(paren
id|t_end
)paren
suffix:semicolon
id|page
op_increment
)paren
r_if
c_cond
(paren
op_logical_neg
id|PageReserved
c_func
(paren
id|page
)paren
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t; * Mappings have to be page-aligned&n;&t; */
id|offset
op_assign
id|phys_addr
op_amp
op_complement
id|PAGE_MASK
suffix:semicolon
id|phys_addr
op_and_assign
id|PAGE_MASK
suffix:semicolon
id|size
op_assign
id|PAGE_ALIGN
c_func
(paren
id|last_addr
op_plus
l_int|1
)paren
op_minus
id|phys_addr
suffix:semicolon
multiline_comment|/*&n;&t; * Ok, go for it..&n;&t; */
id|area
op_assign
id|get_vm_area
c_func
(paren
id|size
comma
id|VM_IOREMAP
op_or
(paren
id|flags
op_lshift
l_int|20
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|area
)paren
r_return
l_int|NULL
suffix:semicolon
id|area-&gt;phys_addr
op_assign
id|phys_addr
suffix:semicolon
id|addr
op_assign
(paren
r_void
id|__iomem
op_star
)paren
id|area-&gt;addr
suffix:semicolon
r_if
c_cond
(paren
id|ioremap_page_range
c_func
(paren
(paren
r_int
r_int
)paren
id|addr
comma
(paren
r_int
r_int
)paren
id|addr
op_plus
id|size
comma
id|phys_addr
comma
id|flags
)paren
)paren
(brace
id|vunmap
c_func
(paren
(paren
r_void
id|__force
op_star
)paren
id|addr
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_return
(paren
r_void
id|__iomem
op_star
)paren
(paren
id|offset
op_plus
(paren
r_char
id|__iomem
op_star
)paren
id|addr
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * ioremap_nocache     -   map bus memory into CPU space&n; * @offset:    bus address of the memory&n; * @size:      size of the resource to map&n; *&n; * ioremap_nocache performs a platform specific sequence of operations to&n; * make bus memory CPU accessible via the readb/readw/readl/writeb/&n; * writew/writel functions and the other mmio helpers. The returned&n; * address is not guaranteed to be usable directly as a virtual&n; * address. &n; *&n; * This version of ioremap ensures that the memory is marked uncachable&n; * on the CPU as well as honouring existing caching rules from things like&n; * the PCI bus. Note that there are other caches and buffers on many &n; * busses. In particular driver authors should read up on PCI writes&n; *&n; * It&squot;s useful if some control registers are in such an area and&n; * write combining or read caching is not desirable:&n; * &n; * Must be freed with iounmap.&n; */
DECL|function|ioremap_nocache
r_void
id|__iomem
op_star
id|ioremap_nocache
(paren
r_int
r_int
id|phys_addr
comma
r_int
r_int
id|size
)paren
(brace
r_int
r_int
id|last_addr
suffix:semicolon
r_void
id|__iomem
op_star
id|p
op_assign
id|__ioremap
c_func
(paren
id|phys_addr
comma
id|size
comma
id|_PAGE_PCD
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p
)paren
r_return
id|p
suffix:semicolon
multiline_comment|/* Guaranteed to be &gt; phys_addr, as per __ioremap() */
id|last_addr
op_assign
id|phys_addr
op_plus
id|size
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|last_addr
OL
id|virt_to_phys
c_func
(paren
id|high_memory
)paren
op_minus
l_int|1
)paren
(brace
r_struct
id|page
op_star
id|ppage
op_assign
id|virt_to_page
c_func
(paren
id|__va
c_func
(paren
id|phys_addr
)paren
)paren
suffix:semicolon
r_int
r_int
id|npages
suffix:semicolon
id|phys_addr
op_and_assign
id|PAGE_MASK
suffix:semicolon
multiline_comment|/* This might overflow and become zero.. */
id|last_addr
op_assign
id|PAGE_ALIGN
c_func
(paren
id|last_addr
)paren
suffix:semicolon
multiline_comment|/* .. but that&squot;s ok, because modulo-2**n arithmetic will make&n;&t; &t;* the page-aligned &quot;last - first&quot; come out right.&n;&t; &t;*/
id|npages
op_assign
(paren
id|last_addr
op_minus
id|phys_addr
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
r_if
c_cond
(paren
id|change_page_attr
c_func
(paren
id|ppage
comma
id|npages
comma
id|PAGE_KERNEL_NOCACHE
)paren
OL
l_int|0
)paren
(brace
id|iounmap
c_func
(paren
id|p
)paren
suffix:semicolon
id|p
op_assign
l_int|NULL
suffix:semicolon
)brace
id|global_flush_tlb
c_func
(paren
)paren
suffix:semicolon
)brace
r_return
id|p
suffix:semicolon
)brace
DECL|function|iounmap
r_void
id|iounmap
c_func
(paren
r_volatile
r_void
id|__iomem
op_star
id|addr
)paren
(brace
r_struct
id|vm_struct
op_star
id|p
suffix:semicolon
r_if
c_cond
(paren
(paren
r_void
id|__force
op_star
)paren
id|addr
op_le
id|high_memory
)paren
r_return
suffix:semicolon
multiline_comment|/*&n;&t; * __ioremap special-cases the PCI/ISA range by not instantiating a&n;&t; * vm_area and by simply returning an address into the kernel mapping&n;&t; * of ISA space.   So handle that here.&n;&t; */
r_if
c_cond
(paren
id|addr
op_ge
id|phys_to_virt
c_func
(paren
id|ISA_START_ADDRESS
)paren
op_logical_and
id|addr
OL
id|phys_to_virt
c_func
(paren
id|ISA_END_ADDRESS
)paren
)paren
r_return
suffix:semicolon
id|p
op_assign
id|remove_vm_area
c_func
(paren
(paren
r_void
op_star
)paren
(paren
id|PAGE_MASK
op_amp
(paren
r_int
r_int
id|__force
)paren
id|addr
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;__iounmap: bad address %p&bslash;n&quot;
comma
id|addr
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|p-&gt;flags
op_rshift
l_int|20
)paren
op_logical_and
id|p-&gt;phys_addr
OL
id|virt_to_phys
c_func
(paren
id|high_memory
)paren
op_minus
l_int|1
)paren
(brace
multiline_comment|/* p-&gt;size includes the guard page, but cpa doesn&squot;t like that */
id|change_page_attr
c_func
(paren
id|virt_to_page
c_func
(paren
id|__va
c_func
(paren
id|p-&gt;phys_addr
)paren
)paren
comma
id|p-&gt;size
op_rshift
id|PAGE_SHIFT
comma
id|PAGE_KERNEL
)paren
suffix:semicolon
id|global_flush_tlb
c_func
(paren
)paren
suffix:semicolon
)brace
id|kfree
c_func
(paren
id|p
)paren
suffix:semicolon
)brace
DECL|function|bt_ioremap
r_void
id|__init
op_star
id|bt_ioremap
c_func
(paren
r_int
r_int
id|phys_addr
comma
r_int
r_int
id|size
)paren
(brace
r_int
r_int
id|offset
comma
id|last_addr
suffix:semicolon
r_int
r_int
id|nrpages
suffix:semicolon
r_enum
id|fixed_addresses
id|idx
suffix:semicolon
multiline_comment|/* Don&squot;t allow wraparound or zero size */
id|last_addr
op_assign
id|phys_addr
op_plus
id|size
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|size
op_logical_or
id|last_addr
OL
id|phys_addr
)paren
r_return
l_int|NULL
suffix:semicolon
multiline_comment|/*&n;&t; * Don&squot;t remap the low PCI/ISA area, it&squot;s always mapped..&n;&t; */
r_if
c_cond
(paren
id|phys_addr
op_ge
id|ISA_START_ADDRESS
op_logical_and
id|last_addr
OL
id|ISA_END_ADDRESS
)paren
r_return
id|phys_to_virt
c_func
(paren
id|phys_addr
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Mappings have to be page-aligned&n;&t; */
id|offset
op_assign
id|phys_addr
op_amp
op_complement
id|PAGE_MASK
suffix:semicolon
id|phys_addr
op_and_assign
id|PAGE_MASK
suffix:semicolon
id|size
op_assign
id|PAGE_ALIGN
c_func
(paren
id|last_addr
)paren
op_minus
id|phys_addr
suffix:semicolon
multiline_comment|/*&n;&t; * Mappings have to fit in the FIX_BTMAP area.&n;&t; */
id|nrpages
op_assign
id|size
op_rshift
id|PAGE_SHIFT
suffix:semicolon
r_if
c_cond
(paren
id|nrpages
OG
id|NR_FIX_BTMAPS
)paren
r_return
l_int|NULL
suffix:semicolon
multiline_comment|/*&n;&t; * Ok, go for it..&n;&t; */
id|idx
op_assign
id|FIX_BTMAP_BEGIN
suffix:semicolon
r_while
c_loop
(paren
id|nrpages
OG
l_int|0
)paren
(brace
id|set_fixmap
c_func
(paren
id|idx
comma
id|phys_addr
)paren
suffix:semicolon
id|phys_addr
op_add_assign
id|PAGE_SIZE
suffix:semicolon
op_decrement
id|idx
suffix:semicolon
op_decrement
id|nrpages
suffix:semicolon
)brace
r_return
(paren
r_void
op_star
)paren
(paren
id|offset
op_plus
id|fix_to_virt
c_func
(paren
id|FIX_BTMAP_BEGIN
)paren
)paren
suffix:semicolon
)brace
DECL|function|bt_iounmap
r_void
id|__init
id|bt_iounmap
c_func
(paren
r_void
op_star
id|addr
comma
r_int
r_int
id|size
)paren
(brace
r_int
r_int
id|virt_addr
suffix:semicolon
r_int
r_int
id|offset
suffix:semicolon
r_int
r_int
id|nrpages
suffix:semicolon
r_enum
id|fixed_addresses
id|idx
suffix:semicolon
id|virt_addr
op_assign
(paren
r_int
r_int
)paren
id|addr
suffix:semicolon
r_if
c_cond
(paren
id|virt_addr
OL
id|fix_to_virt
c_func
(paren
id|FIX_BTMAP_BEGIN
)paren
)paren
r_return
suffix:semicolon
id|offset
op_assign
id|virt_addr
op_amp
op_complement
id|PAGE_MASK
suffix:semicolon
id|nrpages
op_assign
id|PAGE_ALIGN
c_func
(paren
id|offset
op_plus
id|size
op_minus
l_int|1
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|idx
op_assign
id|FIX_BTMAP_BEGIN
suffix:semicolon
r_while
c_loop
(paren
id|nrpages
OG
l_int|0
)paren
(brace
id|clear_fixmap
c_func
(paren
id|idx
)paren
suffix:semicolon
op_decrement
id|idx
suffix:semicolon
op_decrement
id|nrpages
suffix:semicolon
)brace
)brace
eof
