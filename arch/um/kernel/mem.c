multiline_comment|/* &n; * Copyright (C) 2000 - 2003 Jeff Dike (jdike@addtoit.com)&n; * Licensed under the GPL&n; */
macro_line|#include &quot;linux/stddef.h&quot;
macro_line|#include &quot;linux/kernel.h&quot;
macro_line|#include &quot;linux/mm.h&quot;
macro_line|#include &quot;linux/bootmem.h&quot;
macro_line|#include &quot;linux/swap.h&quot;
macro_line|#include &quot;linux/highmem.h&quot;
macro_line|#include &quot;linux/gfp.h&quot;
macro_line|#include &quot;asm/page.h&quot;
macro_line|#include &quot;asm/fixmap.h&quot;
macro_line|#include &quot;asm/pgalloc.h&quot;
macro_line|#include &quot;user_util.h&quot;
macro_line|#include &quot;kern_util.h&quot;
macro_line|#include &quot;kern.h&quot;
macro_line|#include &quot;mem_user.h&quot;
macro_line|#include &quot;uml_uaccess.h&quot;
macro_line|#include &quot;os.h&quot;
r_extern
r_char
id|__binary_start
suffix:semicolon
multiline_comment|/* Changed during early boot */
DECL|variable|empty_zero_page
r_int
r_int
op_star
id|empty_zero_page
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|empty_bad_page
r_int
r_int
op_star
id|empty_bad_page
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|swapper_pg_dir
id|pgd_t
id|swapper_pg_dir
(braket
id|PTRS_PER_PGD
)braket
suffix:semicolon
DECL|variable|highmem
r_int
r_int
id|highmem
suffix:semicolon
DECL|variable|kmalloc_ok
r_int
id|kmalloc_ok
op_assign
l_int|0
suffix:semicolon
DECL|variable|brk_end
r_static
r_int
r_int
id|brk_end
suffix:semicolon
DECL|function|unmap_physmem
r_void
id|unmap_physmem
c_func
(paren
r_void
)paren
(brace
id|os_unmap_memory
c_func
(paren
(paren
r_void
op_star
)paren
id|brk_end
comma
id|uml_reserved
op_minus
id|brk_end
)paren
suffix:semicolon
)brace
DECL|function|map_cb
r_static
r_void
id|map_cb
c_func
(paren
r_void
op_star
id|unused
)paren
(brace
id|map_memory
c_func
(paren
id|brk_end
comma
id|__pa
c_func
(paren
id|brk_end
)paren
comma
id|uml_reserved
op_minus
id|brk_end
comma
l_int|1
comma
l_int|1
comma
l_int|0
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_HIGHMEM
DECL|function|setup_highmem
r_static
r_void
id|setup_highmem
c_func
(paren
r_int
r_int
id|highmem_start
comma
r_int
r_int
id|highmem_len
)paren
(brace
r_struct
id|page
op_star
id|page
suffix:semicolon
r_int
r_int
id|highmem_pfn
suffix:semicolon
r_int
id|i
suffix:semicolon
id|highmem_pfn
op_assign
id|__pa
c_func
(paren
id|highmem_start
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|highmem_len
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|i
op_increment
)paren
(brace
id|page
op_assign
op_amp
id|mem_map
(braket
id|highmem_pfn
op_plus
id|i
)braket
suffix:semicolon
id|ClearPageReserved
c_func
(paren
id|page
)paren
suffix:semicolon
id|set_bit
c_func
(paren
id|PG_highmem
comma
op_amp
id|page-&gt;flags
)paren
suffix:semicolon
id|set_page_count
c_func
(paren
id|page
comma
l_int|1
)paren
suffix:semicolon
id|__free_page
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif
DECL|function|mem_init
r_void
id|mem_init
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|start
suffix:semicolon
id|max_low_pfn
op_assign
(paren
id|high_physmem
op_minus
id|uml_physmem
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
multiline_comment|/* clear the zero-page */
id|memset
c_func
(paren
(paren
r_void
op_star
)paren
id|empty_zero_page
comma
l_int|0
comma
id|PAGE_SIZE
)paren
suffix:semicolon
multiline_comment|/* Map in the area just after the brk now that kmalloc is about&n;&t; * to be turned on.&n;&t; */
id|brk_end
op_assign
(paren
r_int
r_int
)paren
id|UML_ROUND_UP
c_func
(paren
id|sbrk
c_func
(paren
l_int|0
)paren
)paren
suffix:semicolon
id|map_cb
c_func
(paren
l_int|NULL
)paren
suffix:semicolon
id|initial_thread_cb
c_func
(paren
id|map_cb
comma
l_int|NULL
)paren
suffix:semicolon
id|free_bootmem
c_func
(paren
id|__pa
c_func
(paren
id|brk_end
)paren
comma
id|uml_reserved
op_minus
id|brk_end
)paren
suffix:semicolon
id|uml_reserved
op_assign
id|brk_end
suffix:semicolon
multiline_comment|/* Fill in any hole at the start of the binary */
id|start
op_assign
(paren
r_int
r_int
)paren
op_amp
id|__binary_start
op_amp
id|PAGE_MASK
suffix:semicolon
r_if
c_cond
(paren
id|uml_physmem
op_ne
id|start
)paren
(brace
id|map_memory
c_func
(paren
id|uml_physmem
comma
id|__pa
c_func
(paren
id|uml_physmem
)paren
comma
id|start
op_minus
id|uml_physmem
comma
l_int|1
comma
l_int|1
comma
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/* this will put all low memory onto the freelists */
id|totalram_pages
op_assign
id|free_all_bootmem
c_func
(paren
)paren
suffix:semicolon
id|totalhigh_pages
op_assign
id|highmem
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|totalram_pages
op_add_assign
id|totalhigh_pages
suffix:semicolon
id|num_physpages
op_assign
id|totalram_pages
suffix:semicolon
id|max_pfn
op_assign
id|totalram_pages
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Memory: %luk available&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
id|nr_free_pages
c_func
(paren
)paren
op_lshift
(paren
id|PAGE_SHIFT
op_minus
l_int|10
)paren
)paren
suffix:semicolon
id|kmalloc_ok
op_assign
l_int|1
suffix:semicolon
macro_line|#ifdef CONFIG_HIGHMEM
id|setup_highmem
c_func
(paren
id|end_iomem
comma
id|highmem
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|function|fixrange_init
r_static
r_void
id|__init
id|fixrange_init
c_func
(paren
r_int
r_int
id|start
comma
r_int
r_int
id|end
comma
id|pgd_t
op_star
id|pgd_base
)paren
(brace
id|pgd_t
op_star
id|pgd
suffix:semicolon
id|pmd_t
op_star
id|pmd
suffix:semicolon
id|pte_t
op_star
id|pte
suffix:semicolon
r_int
id|i
comma
id|j
suffix:semicolon
r_int
r_int
id|vaddr
suffix:semicolon
id|vaddr
op_assign
id|start
suffix:semicolon
id|i
op_assign
id|pgd_index
c_func
(paren
id|vaddr
)paren
suffix:semicolon
id|j
op_assign
id|pmd_index
c_func
(paren
id|vaddr
)paren
suffix:semicolon
id|pgd
op_assign
id|pgd_base
op_plus
id|i
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
(paren
id|i
OL
id|PTRS_PER_PGD
)paren
op_logical_and
(paren
id|vaddr
OL
id|end
)paren
suffix:semicolon
id|pgd
op_increment
comma
id|i
op_increment
)paren
(brace
id|pmd
op_assign
(paren
id|pmd_t
op_star
)paren
id|pgd
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
(paren
id|j
OL
id|PTRS_PER_PMD
)paren
op_logical_and
(paren
id|vaddr
op_ne
id|end
)paren
suffix:semicolon
id|pmd
op_increment
comma
id|j
op_increment
)paren
(brace
r_if
c_cond
(paren
id|pmd_none
c_func
(paren
op_star
id|pmd
)paren
)paren
(brace
id|pte
op_assign
(paren
id|pte_t
op_star
)paren
id|alloc_bootmem_low_pages
c_func
(paren
id|PAGE_SIZE
)paren
suffix:semicolon
id|set_pmd
c_func
(paren
id|pmd
comma
id|__pmd
c_func
(paren
id|_KERNPG_TABLE
op_plus
(paren
r_int
r_int
)paren
id|__pa
c_func
(paren
id|pte
)paren
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pte
op_ne
id|pte_offset_kernel
c_func
(paren
id|pmd
comma
l_int|0
)paren
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
id|vaddr
op_add_assign
id|PMD_SIZE
suffix:semicolon
)brace
id|j
op_assign
l_int|0
suffix:semicolon
)brace
)brace
macro_line|#ifdef CONFIG_HIGHMEM
DECL|variable|kmap_pte
id|pte_t
op_star
id|kmap_pte
suffix:semicolon
DECL|variable|kmap_prot
id|pgprot_t
id|kmap_prot
suffix:semicolon
DECL|macro|kmap_get_fixmap_pte
mdefine_line|#define kmap_get_fixmap_pte(vaddr)&t;&t;&t;&t;&t;&bslash;&n;&t;pte_offset_kernel(pmd_offset(pud_offset(pgd_offset_k(vaddr), (vaddr)),&bslash;&n; &t;&t;&t;  (vaddr)), (vaddr))
DECL|function|kmap_init
r_void
id|__init
id|kmap_init
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|kmap_vstart
suffix:semicolon
multiline_comment|/* cache the first kmap pte */
id|kmap_vstart
op_assign
id|__fix_to_virt
c_func
(paren
id|FIX_KMAP_BEGIN
)paren
suffix:semicolon
id|kmap_pte
op_assign
id|kmap_get_fixmap_pte
c_func
(paren
id|kmap_vstart
)paren
suffix:semicolon
id|kmap_prot
op_assign
id|PAGE_KERNEL
suffix:semicolon
)brace
DECL|function|init_highmem
r_static
r_void
id|init_highmem
c_func
(paren
r_void
)paren
(brace
id|pgd_t
op_star
id|pgd
suffix:semicolon
id|pud_t
op_star
id|pud
suffix:semicolon
id|pmd_t
op_star
id|pmd
suffix:semicolon
id|pte_t
op_star
id|pte
suffix:semicolon
r_int
r_int
id|vaddr
suffix:semicolon
multiline_comment|/*&n;&t; * Permanent kmaps:&n;&t; */
id|vaddr
op_assign
id|PKMAP_BASE
suffix:semicolon
id|fixrange_init
c_func
(paren
id|vaddr
comma
id|vaddr
op_plus
id|PAGE_SIZE
op_star
id|LAST_PKMAP
comma
id|swapper_pg_dir
)paren
suffix:semicolon
id|pgd
op_assign
id|swapper_pg_dir
op_plus
id|pgd_index
c_func
(paren
id|vaddr
)paren
suffix:semicolon
id|pud
op_assign
id|pud_offset
c_func
(paren
id|pgd
comma
id|vaddr
)paren
suffix:semicolon
id|pmd
op_assign
id|pmd_offset
c_func
(paren
id|pud
comma
id|vaddr
)paren
suffix:semicolon
id|pte
op_assign
id|pte_offset_kernel
c_func
(paren
id|pmd
comma
id|vaddr
)paren
suffix:semicolon
id|pkmap_page_table
op_assign
id|pte
suffix:semicolon
id|kmap_init
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_HIGHMEM */
DECL|function|fixaddr_user_init
r_static
r_void
id|__init
id|fixaddr_user_init
c_func
(paren
r_void
)paren
(brace
macro_line|#if CONFIG_ARCH_REUSE_HOST_VSYSCALL_AREA
r_int
id|size
op_assign
id|FIXADDR_USER_END
op_minus
id|FIXADDR_USER_START
suffix:semicolon
id|pgd_t
op_star
id|pgd
suffix:semicolon
id|pud_t
op_star
id|pud
suffix:semicolon
id|pmd_t
op_star
id|pmd
suffix:semicolon
id|pte_t
op_star
id|pte
suffix:semicolon
r_int
r_int
id|paddr
comma
id|vaddr
op_assign
id|FIXADDR_USER_START
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|size
)paren
r_return
suffix:semicolon
id|fixrange_init
c_func
(paren
id|FIXADDR_USER_START
comma
id|FIXADDR_USER_END
comma
id|swapper_pg_dir
)paren
suffix:semicolon
id|paddr
op_assign
(paren
r_int
r_int
)paren
id|alloc_bootmem_low_pages
c_func
(paren
id|size
)paren
suffix:semicolon
id|memcpy
c_func
(paren
(paren
r_void
op_star
)paren
id|paddr
comma
(paren
r_void
op_star
)paren
id|FIXADDR_USER_START
comma
id|size
)paren
suffix:semicolon
id|paddr
op_assign
id|__pa
c_func
(paren
id|paddr
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|size
OG
l_int|0
suffix:semicolon
id|size
op_sub_assign
id|PAGE_SIZE
comma
id|vaddr
op_add_assign
id|PAGE_SIZE
comma
id|paddr
op_add_assign
id|PAGE_SIZE
)paren
(brace
id|pgd
op_assign
id|swapper_pg_dir
op_plus
id|pgd_index
c_func
(paren
id|vaddr
)paren
suffix:semicolon
id|pud
op_assign
id|pud_offset
c_func
(paren
id|pgd
comma
id|vaddr
)paren
suffix:semicolon
id|pmd
op_assign
id|pmd_offset
c_func
(paren
id|pud
comma
id|vaddr
)paren
suffix:semicolon
id|pte
op_assign
id|pte_offset_kernel
c_func
(paren
id|pmd
comma
id|vaddr
)paren
suffix:semicolon
id|pte_set_val
c_func
(paren
(paren
op_star
id|pte
)paren
comma
id|paddr
comma
id|PAGE_READONLY
)paren
suffix:semicolon
)brace
macro_line|#endif
)brace
DECL|function|paging_init
r_void
id|paging_init
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|zones_size
(braket
id|MAX_NR_ZONES
)braket
comma
id|vaddr
suffix:semicolon
r_int
id|i
suffix:semicolon
id|empty_zero_page
op_assign
(paren
r_int
r_int
op_star
)paren
id|alloc_bootmem_low_pages
c_func
(paren
id|PAGE_SIZE
)paren
suffix:semicolon
id|empty_bad_page
op_assign
(paren
r_int
r_int
op_star
)paren
id|alloc_bootmem_low_pages
c_func
(paren
id|PAGE_SIZE
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
r_sizeof
(paren
id|zones_size
)paren
op_div
r_sizeof
(paren
id|zones_size
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
id|zones_size
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
)brace
id|zones_size
(braket
l_int|0
)braket
op_assign
(paren
id|end_iomem
op_rshift
id|PAGE_SHIFT
)paren
op_minus
(paren
id|uml_physmem
op_rshift
id|PAGE_SHIFT
)paren
suffix:semicolon
id|zones_size
(braket
l_int|2
)braket
op_assign
id|highmem
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|free_area_init
c_func
(paren
id|zones_size
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Fixed mappings, only the page table structure has to be&n;&t; * created - mappings will be set by set_fixmap():&n;&t; */
id|vaddr
op_assign
id|__fix_to_virt
c_func
(paren
id|__end_of_fixed_addresses
op_minus
l_int|1
)paren
op_amp
id|PMD_MASK
suffix:semicolon
id|fixrange_init
c_func
(paren
id|vaddr
comma
id|FIXADDR_TOP
comma
id|swapper_pg_dir
)paren
suffix:semicolon
id|fixaddr_user_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_HIGHMEM
id|init_highmem
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|function|arch_validate
r_struct
id|page
op_star
id|arch_validate
c_func
(paren
r_struct
id|page
op_star
id|page
comma
r_int
id|mask
comma
r_int
id|order
)paren
(brace
r_int
r_int
id|addr
comma
id|zero
op_assign
l_int|0
suffix:semicolon
r_int
id|i
suffix:semicolon
id|again
suffix:colon
r_if
c_cond
(paren
id|page
op_eq
l_int|NULL
)paren
(brace
r_return
id|page
suffix:semicolon
)brace
r_if
c_cond
(paren
id|PageHighMem
c_func
(paren
id|page
)paren
)paren
(brace
r_return
id|page
suffix:semicolon
)brace
id|addr
op_assign
(paren
r_int
r_int
)paren
id|page_address
c_func
(paren
id|page
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
(paren
l_int|1
op_lshift
id|order
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
id|current-&gt;thread.fault_addr
op_assign
(paren
r_void
op_star
)paren
id|addr
suffix:semicolon
r_if
c_cond
(paren
id|__do_copy_to_user
c_func
(paren
(paren
r_void
id|__user
op_star
)paren
id|addr
comma
op_amp
id|zero
comma
r_sizeof
(paren
id|zero
)paren
comma
op_amp
id|current-&gt;thread.fault_addr
comma
op_amp
id|current-&gt;thread.fault_catcher
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|mask
op_amp
id|__GFP_WAIT
)paren
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
r_else
r_break
suffix:semicolon
)brace
id|addr
op_add_assign
id|PAGE_SIZE
suffix:semicolon
)brace
r_if
c_cond
(paren
id|i
op_eq
(paren
l_int|1
op_lshift
id|order
)paren
)paren
(brace
r_return
id|page
suffix:semicolon
)brace
id|page
op_assign
id|alloc_pages
c_func
(paren
id|mask
comma
id|order
)paren
suffix:semicolon
r_goto
id|again
suffix:semicolon
)brace
multiline_comment|/* This can&squot;t do anything because nothing in the kernel image can be freed&n; * since it&squot;s not in kernel physical memory.&n; */
DECL|function|free_initmem
r_void
id|free_initmem
c_func
(paren
r_void
)paren
(brace
)brace
macro_line|#ifdef CONFIG_BLK_DEV_INITRD
DECL|function|free_initrd_mem
r_void
id|free_initrd_mem
c_func
(paren
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
id|start
OL
id|end
)paren
id|printk
(paren
l_string|&quot;Freeing initrd memory: %ldk freed&bslash;n&quot;
comma
(paren
id|end
op_minus
id|start
)paren
op_rshift
l_int|10
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|start
OL
id|end
suffix:semicolon
id|start
op_add_assign
id|PAGE_SIZE
)paren
(brace
id|ClearPageReserved
c_func
(paren
id|virt_to_page
c_func
(paren
id|start
)paren
)paren
suffix:semicolon
id|set_page_count
c_func
(paren
id|virt_to_page
c_func
(paren
id|start
)paren
comma
l_int|1
)paren
suffix:semicolon
id|free_page
c_func
(paren
id|start
)paren
suffix:semicolon
id|totalram_pages
op_increment
suffix:semicolon
)brace
)brace
macro_line|#endif
DECL|function|show_mem
r_void
id|show_mem
c_func
(paren
r_void
)paren
(brace
r_int
id|pfn
comma
id|total
op_assign
l_int|0
comma
id|reserved
op_assign
l_int|0
suffix:semicolon
r_int
id|shared
op_assign
l_int|0
comma
id|cached
op_assign
l_int|0
suffix:semicolon
r_int
id|highmem
op_assign
l_int|0
suffix:semicolon
r_struct
id|page
op_star
id|page
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Mem-info:&bslash;n&quot;
)paren
suffix:semicolon
id|show_free_areas
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Free swap:       %6ldkB&bslash;n&quot;
comma
id|nr_swap_pages
op_lshift
(paren
id|PAGE_SHIFT
op_minus
l_int|10
)paren
)paren
suffix:semicolon
id|pfn
op_assign
id|max_mapnr
suffix:semicolon
r_while
c_loop
(paren
id|pfn
op_decrement
OG
l_int|0
)paren
(brace
id|page
op_assign
id|pfn_to_page
c_func
(paren
id|pfn
)paren
suffix:semicolon
id|total
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|PageHighMem
c_func
(paren
id|page
)paren
)paren
(brace
id|highmem
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|PageReserved
c_func
(paren
id|page
)paren
)paren
(brace
id|reserved
op_increment
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|PageSwapCache
c_func
(paren
id|page
)paren
)paren
(brace
id|cached
op_increment
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|page_count
c_func
(paren
id|page
)paren
)paren
(brace
id|shared
op_add_assign
id|page_count
c_func
(paren
id|page
)paren
op_minus
l_int|1
suffix:semicolon
)brace
)brace
id|printk
c_func
(paren
l_string|&quot;%d pages of RAM&bslash;n&quot;
comma
id|total
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%d pages of HIGHMEM&bslash;n&quot;
comma
id|highmem
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%d reserved pages&bslash;n&quot;
comma
id|reserved
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%d pages shared&bslash;n&quot;
comma
id|shared
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%d pages swap cached&bslash;n&quot;
comma
id|cached
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Allocate and free page tables.&n; */
DECL|function|pgd_alloc
id|pgd_t
op_star
id|pgd_alloc
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
(brace
id|pgd_t
op_star
id|pgd
op_assign
(paren
id|pgd_t
op_star
)paren
id|__get_free_page
c_func
(paren
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pgd
)paren
(brace
id|memset
c_func
(paren
id|pgd
comma
l_int|0
comma
id|USER_PTRS_PER_PGD
op_star
r_sizeof
(paren
id|pgd_t
)paren
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|pgd
op_plus
id|USER_PTRS_PER_PGD
comma
id|swapper_pg_dir
op_plus
id|USER_PTRS_PER_PGD
comma
(paren
id|PTRS_PER_PGD
op_minus
id|USER_PTRS_PER_PGD
)paren
op_star
r_sizeof
(paren
id|pgd_t
)paren
)paren
suffix:semicolon
)brace
r_return
id|pgd
suffix:semicolon
)brace
DECL|function|pgd_free
r_void
id|pgd_free
c_func
(paren
id|pgd_t
op_star
id|pgd
)paren
(brace
id|free_page
c_func
(paren
(paren
r_int
r_int
)paren
id|pgd
)paren
suffix:semicolon
)brace
DECL|function|pte_alloc_one_kernel
id|pte_t
op_star
id|pte_alloc_one_kernel
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
r_int
r_int
id|address
)paren
(brace
id|pte_t
op_star
id|pte
suffix:semicolon
id|pte
op_assign
(paren
id|pte_t
op_star
)paren
id|__get_free_page
c_func
(paren
id|GFP_KERNEL
op_or
id|__GFP_REPEAT
op_or
id|__GFP_ZERO
)paren
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|function|pte_alloc_one
r_struct
id|page
op_star
id|pte_alloc_one
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
r_int
r_int
id|address
)paren
(brace
r_struct
id|page
op_star
id|pte
suffix:semicolon
id|pte
op_assign
id|alloc_page
c_func
(paren
id|GFP_KERNEL
op_or
id|__GFP_REPEAT
op_or
id|__GFP_ZERO
)paren
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
