multiline_comment|/*&n; *  linux/arch/arm/mm/mm-armv.c&n; *&n; *  Copyright (C) 1998-2002 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; *  Page table sludge for ARM v3 and v4 processor architectures.&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/mach/map.h&gt;
multiline_comment|/*&n; * These are useful for identifing cache coherency&n; * problems by allowing the cache or the cache and&n; * writebuffer to be turned off.  (Note: the write&n; * buffer should not be on and the cache off).&n; */
DECL|function|nocache_setup
r_static
r_int
id|__init
id|nocache_setup
c_func
(paren
r_char
op_star
id|__unused
)paren
(brace
id|cr_alignment
op_and_assign
op_complement
id|CR1_C
suffix:semicolon
id|cr_no_alignment
op_and_assign
op_complement
id|CR1_C
suffix:semicolon
id|flush_cache_all
c_func
(paren
)paren
suffix:semicolon
id|set_cr
c_func
(paren
id|cr_alignment
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|nowrite_setup
r_static
r_int
id|__init
id|nowrite_setup
c_func
(paren
r_char
op_star
id|__unused
)paren
(brace
id|cr_alignment
op_and_assign
op_complement
(paren
id|CR1_W
op_or
id|CR1_C
)paren
suffix:semicolon
id|cr_no_alignment
op_and_assign
op_complement
(paren
id|CR1_W
op_or
id|CR1_C
)paren
suffix:semicolon
id|flush_cache_all
c_func
(paren
)paren
suffix:semicolon
id|set_cr
c_func
(paren
id|cr_alignment
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|noalign_setup
r_static
r_int
id|__init
id|noalign_setup
c_func
(paren
r_char
op_star
id|__unused
)paren
(brace
id|cr_alignment
op_and_assign
op_complement
id|CR1_A
suffix:semicolon
id|cr_no_alignment
op_and_assign
op_complement
id|CR1_A
suffix:semicolon
id|set_cr
c_func
(paren
id|cr_alignment
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|__setup
c_func
(paren
l_string|&quot;noalign&quot;
comma
id|noalign_setup
)paren
suffix:semicolon
id|__setup
c_func
(paren
l_string|&quot;nocache&quot;
comma
id|nocache_setup
)paren
suffix:semicolon
id|__setup
c_func
(paren
l_string|&quot;nowb&quot;
comma
id|nowrite_setup
)paren
suffix:semicolon
DECL|macro|FIRST_KERNEL_PGD_NR
mdefine_line|#define FIRST_KERNEL_PGD_NR&t;(FIRST_USER_PGD_NR + USER_PTRS_PER_PGD)
multiline_comment|/*&n; * need to get a 16k page for level 1&n; */
DECL|function|get_pgd_slow
id|pgd_t
op_star
id|get_pgd_slow
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
id|new_pgd
comma
op_star
id|init_pgd
suffix:semicolon
id|pmd_t
op_star
id|new_pmd
comma
op_star
id|init_pmd
suffix:semicolon
id|pte_t
op_star
id|new_pte
comma
op_star
id|init_pte
suffix:semicolon
id|new_pgd
op_assign
(paren
id|pgd_t
op_star
)paren
id|__get_free_pages
c_func
(paren
id|GFP_KERNEL
comma
l_int|2
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|new_pgd
)paren
r_goto
id|no_pgd
suffix:semicolon
id|memzero
c_func
(paren
id|new_pgd
comma
id|FIRST_KERNEL_PGD_NR
op_star
r_sizeof
(paren
id|pgd_t
)paren
)paren
suffix:semicolon
id|init_pgd
op_assign
id|pgd_offset_k
c_func
(paren
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|vectors_base
c_func
(paren
)paren
op_eq
l_int|0
)paren
(brace
multiline_comment|/*&n;&t;&t; * This lock is here just to satisfy pmd_alloc and pte_lock&n;&t;&t; */
id|spin_lock
c_func
(paren
op_amp
id|mm-&gt;page_table_lock
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * On ARM, first page must always be allocated since it&n;&t;&t; * contains the machine vectors.&n;&t;&t; */
id|new_pmd
op_assign
id|pmd_alloc
c_func
(paren
id|mm
comma
id|new_pgd
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|new_pmd
)paren
r_goto
id|no_pmd
suffix:semicolon
id|new_pte
op_assign
id|pte_alloc_map
c_func
(paren
id|mm
comma
id|new_pmd
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|new_pte
)paren
r_goto
id|no_pte
suffix:semicolon
id|init_pmd
op_assign
id|pmd_offset
c_func
(paren
id|init_pgd
comma
l_int|0
)paren
suffix:semicolon
id|init_pte
op_assign
id|pte_offset_map_nested
c_func
(paren
id|init_pmd
comma
l_int|0
)paren
suffix:semicolon
id|set_pte
c_func
(paren
id|new_pte
comma
op_star
id|init_pte
)paren
suffix:semicolon
id|pte_unmap_nested
c_func
(paren
id|init_pte
)paren
suffix:semicolon
id|pte_unmap
c_func
(paren
id|new_pte
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|mm-&gt;page_table_lock
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Copy over the kernel and IO PGD entries&n;&t; */
id|memcpy
c_func
(paren
id|new_pgd
op_plus
id|FIRST_KERNEL_PGD_NR
comma
id|init_pgd
op_plus
id|FIRST_KERNEL_PGD_NR
comma
(paren
id|PTRS_PER_PGD
op_minus
id|FIRST_KERNEL_PGD_NR
)paren
op_star
r_sizeof
(paren
id|pgd_t
)paren
)paren
suffix:semicolon
id|clean_dcache_area
c_func
(paren
id|new_pgd
comma
id|PTRS_PER_PGD
op_star
r_sizeof
(paren
id|pgd_t
)paren
)paren
suffix:semicolon
r_return
id|new_pgd
suffix:semicolon
id|no_pte
suffix:colon
id|spin_unlock
c_func
(paren
op_amp
id|mm-&gt;page_table_lock
)paren
suffix:semicolon
id|pmd_free
c_func
(paren
id|new_pmd
)paren
suffix:semicolon
id|free_pages
c_func
(paren
(paren
r_int
r_int
)paren
id|new_pgd
comma
l_int|2
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
id|no_pmd
suffix:colon
id|spin_unlock
c_func
(paren
op_amp
id|mm-&gt;page_table_lock
)paren
suffix:semicolon
id|free_pages
c_func
(paren
(paren
r_int
r_int
)paren
id|new_pgd
comma
l_int|2
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
id|no_pgd
suffix:colon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|free_pgd_slow
r_void
id|free_pgd_slow
c_func
(paren
id|pgd_t
op_star
id|pgd
)paren
(brace
id|pmd_t
op_star
id|pmd
suffix:semicolon
r_struct
id|page
op_star
id|pte
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pgd
)paren
r_return
suffix:semicolon
multiline_comment|/* pgd is always present and good */
id|pmd
op_assign
(paren
id|pmd_t
op_star
)paren
id|pgd
suffix:semicolon
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
r_goto
id|free
suffix:semicolon
r_if
c_cond
(paren
id|pmd_bad
c_func
(paren
op_star
id|pmd
)paren
)paren
(brace
id|pmd_ERROR
c_func
(paren
op_star
id|pmd
)paren
suffix:semicolon
id|pmd_clear
c_func
(paren
id|pmd
)paren
suffix:semicolon
r_goto
id|free
suffix:semicolon
)brace
id|pte
op_assign
id|pmd_page
c_func
(paren
op_star
id|pmd
)paren
suffix:semicolon
id|pmd_clear
c_func
(paren
id|pmd
)paren
suffix:semicolon
id|pte_free
c_func
(paren
id|pte
)paren
suffix:semicolon
id|pmd_free
c_func
(paren
id|pmd
)paren
suffix:semicolon
id|free
suffix:colon
id|free_pages
c_func
(paren
(paren
r_int
r_int
)paren
id|pgd
comma
l_int|2
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Create a SECTION PGD between VIRT and PHYS in domain&n; * DOMAIN with protection PROT&n; */
r_static
r_inline
r_void
DECL|function|alloc_init_section
id|alloc_init_section
c_func
(paren
r_int
r_int
id|virt
comma
r_int
r_int
id|phys
comma
r_int
id|prot
)paren
(brace
id|pmd_t
op_star
id|pmdp
comma
id|pmd
suffix:semicolon
id|pmdp
op_assign
id|pmd_offset
c_func
(paren
id|pgd_offset_k
c_func
(paren
id|virt
)paren
comma
id|virt
)paren
suffix:semicolon
r_if
c_cond
(paren
id|virt
op_amp
(paren
l_int|1
op_lshift
id|PMD_SHIFT
)paren
)paren
id|pmdp
op_increment
suffix:semicolon
id|pmd_val
c_func
(paren
id|pmd
)paren
op_assign
id|phys
op_or
id|prot
suffix:semicolon
id|set_pmd
c_func
(paren
id|pmdp
comma
id|pmd
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Add a PAGE mapping between VIRT and PHYS in domain&n; * DOMAIN with protection PROT.  Note that due to the&n; * way we map the PTEs, we must allocate two PTE_SIZE&squot;d&n; * blocks - one for the Linux pte table, and one for&n; * the hardware pte table.&n; */
r_static
r_inline
r_void
DECL|function|alloc_init_page
id|alloc_init_page
c_func
(paren
r_int
r_int
id|virt
comma
r_int
r_int
id|phys
comma
r_int
id|domain
comma
r_int
id|prot
)paren
(brace
id|pmd_t
op_star
id|pmdp
comma
id|pmd
suffix:semicolon
id|pte_t
op_star
id|ptep
suffix:semicolon
id|pmdp
op_assign
id|pmd_offset
c_func
(paren
id|pgd_offset_k
c_func
(paren
id|virt
)paren
comma
id|virt
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pmd_none
c_func
(paren
op_star
id|pmdp
)paren
)paren
(brace
id|ptep
op_assign
id|alloc_bootmem_low_pages
c_func
(paren
l_int|2
op_star
id|PTRS_PER_PTE
op_star
r_sizeof
(paren
id|pte_t
)paren
)paren
suffix:semicolon
id|pmd_val
c_func
(paren
id|pmd
)paren
op_assign
id|__pa
c_func
(paren
id|ptep
)paren
op_or
id|PMD_TYPE_TABLE
op_or
id|PMD_DOMAIN
c_func
(paren
id|domain
)paren
suffix:semicolon
id|set_pmd
c_func
(paren
id|pmdp
comma
id|pmd
)paren
suffix:semicolon
id|pmd_val
c_func
(paren
id|pmd
)paren
op_add_assign
l_int|256
op_star
r_sizeof
(paren
id|pte_t
)paren
suffix:semicolon
id|set_pmd
c_func
(paren
id|pmdp
op_plus
l_int|1
comma
id|pmd
)paren
suffix:semicolon
)brace
id|ptep
op_assign
id|pte_offset_kernel
c_func
(paren
id|pmdp
comma
id|virt
)paren
suffix:semicolon
id|set_pte
c_func
(paren
id|ptep
comma
id|mk_pte_phys
c_func
(paren
id|phys
comma
id|__pgprot
c_func
(paren
id|prot
)paren
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Clear any PGD mapping.  On a two-level page table system,&n; * the clearance is done by the middle-level functions (pmd)&n; * rather than the top-level (pgd) functions.&n; */
DECL|function|clear_mapping
r_static
r_inline
r_void
id|clear_mapping
c_func
(paren
r_int
r_int
id|virt
)paren
(brace
id|pmd_clear
c_func
(paren
id|pmd_offset
c_func
(paren
id|pgd_offset_k
c_func
(paren
id|virt
)paren
comma
id|virt
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Create the page directory entries and any necessary&n; * page tables for the mapping specified by `md&squot;.  We&n; * are able to cope here with varying sizes and address&n; * offsets, and we take full advantage of sections.&n; */
DECL|function|create_mapping
r_static
r_void
id|__init
id|create_mapping
c_func
(paren
r_struct
id|map_desc
op_star
id|md
)paren
(brace
r_int
r_int
id|virt
comma
id|length
suffix:semicolon
r_int
id|prot_sect
comma
id|prot_pte
suffix:semicolon
r_int
id|off
suffix:semicolon
r_if
c_cond
(paren
id|md-&gt;prot_read
op_logical_and
id|md-&gt;prot_write
op_logical_and
op_logical_neg
id|md-&gt;cacheable
op_logical_and
op_logical_neg
id|md-&gt;bufferable
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Security risk: creating user &quot;
l_string|&quot;accessible mapping for 0x%08lx at 0x%08lx&bslash;n&quot;
comma
id|md-&gt;physical
comma
id|md
op_member_access_from_pointer
r_virtual
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|md
op_member_access_from_pointer
r_virtual
op_ne
id|vectors_base
c_func
(paren
)paren
op_logical_and
id|md
op_member_access_from_pointer
r_virtual
OL
id|PAGE_OFFSET
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;MM: not creating mapping for &quot;
l_string|&quot;0x%08lx at 0x%08lx in user region&bslash;n&quot;
comma
id|md-&gt;physical
comma
id|md
op_member_access_from_pointer
r_virtual
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|prot_pte
op_assign
id|L_PTE_PRESENT
op_or
id|L_PTE_YOUNG
op_or
id|L_PTE_DIRTY
op_or
(paren
id|md-&gt;prot_read
ques
c_cond
id|L_PTE_USER
suffix:colon
l_int|0
)paren
op_or
(paren
id|md-&gt;prot_write
ques
c_cond
id|L_PTE_WRITE
suffix:colon
l_int|0
)paren
op_or
(paren
id|md-&gt;cacheable
ques
c_cond
id|L_PTE_CACHEABLE
suffix:colon
l_int|0
)paren
op_or
(paren
id|md-&gt;bufferable
ques
c_cond
id|L_PTE_BUFFERABLE
suffix:colon
l_int|0
)paren
suffix:semicolon
id|prot_sect
op_assign
id|PMD_TYPE_SECT
op_or
id|PMD_DOMAIN
c_func
(paren
id|md-&gt;domain
)paren
op_or
(paren
id|md-&gt;prot_read
ques
c_cond
id|PMD_SECT_AP_READ
suffix:colon
l_int|0
)paren
op_or
(paren
id|md-&gt;prot_write
ques
c_cond
id|PMD_SECT_AP_WRITE
suffix:colon
l_int|0
)paren
op_or
(paren
id|md-&gt;cacheable
ques
c_cond
id|PMD_SECT_CACHEABLE
suffix:colon
l_int|0
)paren
op_or
(paren
id|md-&gt;bufferable
ques
c_cond
id|PMD_SECT_BUFFERABLE
suffix:colon
l_int|0
)paren
suffix:semicolon
id|virt
op_assign
id|md
op_member_access_from_pointer
r_virtual
suffix:semicolon
id|off
op_assign
id|md-&gt;physical
op_minus
id|virt
suffix:semicolon
id|length
op_assign
id|md-&gt;length
suffix:semicolon
r_while
c_loop
(paren
(paren
id|virt
op_amp
l_int|0xfffff
op_logical_or
(paren
id|virt
op_plus
id|off
)paren
op_amp
l_int|0xfffff
)paren
op_logical_and
id|length
op_ge
id|PAGE_SIZE
)paren
(brace
id|alloc_init_page
c_func
(paren
id|virt
comma
id|virt
op_plus
id|off
comma
id|md-&gt;domain
comma
id|prot_pte
)paren
suffix:semicolon
id|virt
op_add_assign
id|PAGE_SIZE
suffix:semicolon
id|length
op_sub_assign
id|PAGE_SIZE
suffix:semicolon
)brace
r_while
c_loop
(paren
id|length
op_ge
(paren
id|PGDIR_SIZE
op_div
l_int|2
)paren
)paren
(brace
id|alloc_init_section
c_func
(paren
id|virt
comma
id|virt
op_plus
id|off
comma
id|prot_sect
)paren
suffix:semicolon
id|virt
op_add_assign
(paren
id|PGDIR_SIZE
op_div
l_int|2
)paren
suffix:semicolon
id|length
op_sub_assign
(paren
id|PGDIR_SIZE
op_div
l_int|2
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|length
op_ge
id|PAGE_SIZE
)paren
(brace
id|alloc_init_page
c_func
(paren
id|virt
comma
id|virt
op_plus
id|off
comma
id|md-&gt;domain
comma
id|prot_pte
)paren
suffix:semicolon
id|virt
op_add_assign
id|PAGE_SIZE
suffix:semicolon
id|length
op_sub_assign
id|PAGE_SIZE
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * In order to soft-boot, we need to insert a 1:1 mapping in place of&n; * the user-mode pages.  This will then ensure that we have predictable&n; * results when turning the mmu off&n; */
DECL|function|setup_mm_for_reboot
r_void
id|setup_mm_for_reboot
c_func
(paren
r_char
id|mode
)paren
(brace
id|pgd_t
op_star
id|pgd
suffix:semicolon
id|pmd_t
id|pmd
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;mm
op_logical_and
id|current-&gt;mm-&gt;pgd
)paren
id|pgd
op_assign
id|current-&gt;mm-&gt;pgd
suffix:semicolon
r_else
id|pgd
op_assign
id|init_mm.pgd
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
id|FIRST_USER_PGD_NR
op_plus
id|USER_PTRS_PER_PGD
suffix:semicolon
id|i
op_increment
)paren
(brace
id|pmd_val
c_func
(paren
id|pmd
)paren
op_assign
(paren
id|i
op_lshift
id|PGDIR_SHIFT
)paren
op_or
id|PMD_SECT_AP_WRITE
op_or
id|PMD_SECT_AP_READ
op_or
id|PMD_TYPE_SECT
suffix:semicolon
id|set_pmd
c_func
(paren
id|pmd_offset
c_func
(paren
id|pgd
op_plus
id|i
comma
id|i
op_lshift
id|PGDIR_SHIFT
)paren
comma
id|pmd
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Setup initial mappings.  We use the page we allocated for zero page to hold&n; * the mappings, which will get overwritten by the vectors in traps_init().&n; * The mappings must be in virtual address order.&n; */
DECL|function|memtable_init
r_void
id|__init
id|memtable_init
c_func
(paren
r_struct
id|meminfo
op_star
id|mi
)paren
(brace
r_struct
id|map_desc
op_star
id|init_maps
comma
op_star
id|p
comma
op_star
id|q
suffix:semicolon
r_int
r_int
id|address
op_assign
l_int|0
suffix:semicolon
r_int
id|i
suffix:semicolon
id|init_maps
op_assign
id|p
op_assign
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
id|mi-&gt;nr_banks
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|mi-&gt;bank
(braket
id|i
)braket
dot
id|size
op_eq
l_int|0
)paren
r_continue
suffix:semicolon
id|p-&gt;physical
op_assign
id|mi-&gt;bank
(braket
id|i
)braket
dot
id|start
suffix:semicolon
id|p
op_member_access_from_pointer
r_virtual
op_assign
id|__phys_to_virt
c_func
(paren
id|p-&gt;physical
)paren
suffix:semicolon
id|p-&gt;length
op_assign
id|mi-&gt;bank
(braket
id|i
)braket
dot
id|size
suffix:semicolon
id|p-&gt;domain
op_assign
id|DOMAIN_KERNEL
suffix:semicolon
id|p-&gt;prot_read
op_assign
l_int|0
suffix:semicolon
id|p-&gt;prot_write
op_assign
l_int|1
suffix:semicolon
id|p-&gt;cacheable
op_assign
l_int|1
suffix:semicolon
id|p-&gt;bufferable
op_assign
l_int|1
suffix:semicolon
id|p
op_increment
suffix:semicolon
)brace
macro_line|#ifdef FLUSH_BASE
id|p-&gt;physical
op_assign
id|FLUSH_BASE_PHYS
suffix:semicolon
id|p
op_member_access_from_pointer
r_virtual
op_assign
id|FLUSH_BASE
suffix:semicolon
id|p-&gt;length
op_assign
id|PGDIR_SIZE
suffix:semicolon
id|p-&gt;domain
op_assign
id|DOMAIN_KERNEL
suffix:semicolon
id|p-&gt;prot_read
op_assign
l_int|1
suffix:semicolon
id|p-&gt;prot_write
op_assign
l_int|0
suffix:semicolon
id|p-&gt;cacheable
op_assign
l_int|1
suffix:semicolon
id|p-&gt;bufferable
op_assign
l_int|1
suffix:semicolon
id|p
op_increment
suffix:semicolon
macro_line|#endif
macro_line|#ifdef FLUSH_BASE_MINICACHE
id|p-&gt;physical
op_assign
id|FLUSH_BASE_PHYS
op_plus
id|PGDIR_SIZE
suffix:semicolon
id|p
op_member_access_from_pointer
r_virtual
op_assign
id|FLUSH_BASE_MINICACHE
suffix:semicolon
id|p-&gt;length
op_assign
id|PGDIR_SIZE
suffix:semicolon
id|p-&gt;domain
op_assign
id|DOMAIN_KERNEL
suffix:semicolon
id|p-&gt;prot_read
op_assign
l_int|1
suffix:semicolon
id|p-&gt;prot_write
op_assign
l_int|0
suffix:semicolon
id|p-&gt;cacheable
op_assign
l_int|1
suffix:semicolon
id|p-&gt;bufferable
op_assign
l_int|0
suffix:semicolon
id|p
op_increment
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;&t; * Go through the initial mappings, but clear out any&n;&t; * pgdir entries that are not in the description.&n;&t; */
id|q
op_assign
id|init_maps
suffix:semicolon
r_do
(brace
r_if
c_cond
(paren
id|address
OL
id|q
op_member_access_from_pointer
r_virtual
op_logical_or
id|q
op_eq
id|p
)paren
(brace
id|clear_mapping
c_func
(paren
id|address
)paren
suffix:semicolon
id|address
op_add_assign
id|PGDIR_SIZE
suffix:semicolon
)brace
r_else
(brace
id|create_mapping
c_func
(paren
id|q
)paren
suffix:semicolon
id|address
op_assign
id|q
op_member_access_from_pointer
r_virtual
op_plus
id|q-&gt;length
suffix:semicolon
id|address
op_assign
(paren
id|address
op_plus
id|PGDIR_SIZE
op_minus
l_int|1
)paren
op_amp
id|PGDIR_MASK
suffix:semicolon
id|q
op_increment
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
id|address
op_ne
l_int|0
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Create a mapping for the machine vectors at virtual address 0&n;&t; * or 0xffff0000.  We should always try the high mapping.&n;&t; */
id|init_maps-&gt;physical
op_assign
id|virt_to_phys
c_func
(paren
id|init_maps
)paren
suffix:semicolon
id|init_maps
op_member_access_from_pointer
r_virtual
op_assign
id|vectors_base
c_func
(paren
)paren
suffix:semicolon
id|init_maps-&gt;length
op_assign
id|PAGE_SIZE
suffix:semicolon
id|init_maps-&gt;domain
op_assign
id|DOMAIN_USER
suffix:semicolon
id|init_maps-&gt;prot_read
op_assign
l_int|0
suffix:semicolon
id|init_maps-&gt;prot_write
op_assign
l_int|0
suffix:semicolon
id|init_maps-&gt;cacheable
op_assign
l_int|1
suffix:semicolon
id|init_maps-&gt;bufferable
op_assign
l_int|0
suffix:semicolon
id|create_mapping
c_func
(paren
id|init_maps
)paren
suffix:semicolon
id|flush_cache_all
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Create the architecture specific mappings&n; */
DECL|function|iotable_init
r_void
id|__init
id|iotable_init
c_func
(paren
r_struct
id|map_desc
op_star
id|io_desc
)paren
(brace
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|io_desc
(braket
id|i
)braket
dot
id|last
op_eq
l_int|0
suffix:semicolon
id|i
op_increment
)paren
id|create_mapping
c_func
(paren
id|io_desc
op_plus
id|i
)paren
suffix:semicolon
)brace
DECL|function|free_memmap
r_static
r_inline
r_void
id|free_memmap
c_func
(paren
r_int
id|node
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
r_int
r_int
id|pg
comma
id|pgend
suffix:semicolon
id|start
op_assign
id|__phys_to_virt
c_func
(paren
id|start
)paren
suffix:semicolon
id|end
op_assign
id|__phys_to_virt
c_func
(paren
id|end
)paren
suffix:semicolon
id|pg
op_assign
id|PAGE_ALIGN
c_func
(paren
(paren
r_int
r_int
)paren
(paren
id|virt_to_page
c_func
(paren
id|start
)paren
)paren
)paren
suffix:semicolon
id|pgend
op_assign
(paren
(paren
r_int
r_int
)paren
(paren
id|virt_to_page
c_func
(paren
id|end
)paren
)paren
)paren
op_amp
id|PAGE_MASK
suffix:semicolon
id|start
op_assign
id|__virt_to_phys
c_func
(paren
id|pg
)paren
suffix:semicolon
id|end
op_assign
id|__virt_to_phys
c_func
(paren
id|pgend
)paren
suffix:semicolon
id|free_bootmem_node
c_func
(paren
id|NODE_DATA
c_func
(paren
id|node
)paren
comma
id|start
comma
id|end
op_minus
id|start
)paren
suffix:semicolon
)brace
DECL|function|free_unused_memmap_node
r_static
r_inline
r_void
id|free_unused_memmap_node
c_func
(paren
r_int
id|node
comma
r_struct
id|meminfo
op_star
id|mi
)paren
(brace
r_int
r_int
id|bank_start
comma
id|prev_bank_end
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|i
suffix:semicolon
multiline_comment|/*&n;&t; * [FIXME] This relies on each bank being in address order.  This&n;&t; * may not be the case, especially if the user has provided the&n;&t; * information on the command line.&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|mi-&gt;nr_banks
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|mi-&gt;bank
(braket
id|i
)braket
dot
id|size
op_eq
l_int|0
op_logical_or
id|mi-&gt;bank
(braket
id|i
)braket
dot
id|node
op_ne
id|node
)paren
r_continue
suffix:semicolon
id|bank_start
op_assign
id|mi-&gt;bank
(braket
id|i
)braket
dot
id|start
op_amp
id|PAGE_MASK
suffix:semicolon
multiline_comment|/*&n;&t;&t; * If we had a previous bank, and there is a space&n;&t;&t; * between the current bank and the previous, free it.&n;&t;&t; */
r_if
c_cond
(paren
id|prev_bank_end
op_logical_and
id|prev_bank_end
op_ne
id|bank_start
)paren
id|free_memmap
c_func
(paren
id|node
comma
id|prev_bank_end
comma
id|bank_start
)paren
suffix:semicolon
id|prev_bank_end
op_assign
id|PAGE_ALIGN
c_func
(paren
id|mi-&gt;bank
(braket
id|i
)braket
dot
id|start
op_plus
id|mi-&gt;bank
(braket
id|i
)braket
dot
id|size
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * The mem_map array can get very big.  Free&n; * the unused area of the memory map.&n; */
DECL|function|create_memmap_holes
r_void
id|__init
id|create_memmap_holes
c_func
(paren
r_struct
id|meminfo
op_star
id|mi
)paren
(brace
r_int
id|node
suffix:semicolon
r_for
c_loop
(paren
id|node
op_assign
l_int|0
suffix:semicolon
id|node
OL
id|numnodes
suffix:semicolon
id|node
op_increment
)paren
id|free_unused_memmap_node
c_func
(paren
id|node
comma
id|mi
)paren
suffix:semicolon
)brace
eof
