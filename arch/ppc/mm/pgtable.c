multiline_comment|/*&n; * This file contains the routines setting up the linux page tables.&n; *  -- paulus&n; * &n; *  Derived from arch/ppc/mm/init.c:&n; *    Copyright (C) 1995-1996 Gary Thomas (gdt@linuxppc.org)&n; *&n; *  Modifications by Paul Mackerras (PowerMac) (paulus@cs.anu.edu.au)&n; *  and Cort Dougan (PReP) (cort@cs.nmt.edu)&n; *    Copyright (C) 1996 Paul Mackerras&n; *  Amiga/APUS changes by Jesper Skov (jskov@cygnus.co.uk).&n; *&n; *  Derived from &quot;arch/i386/mm/init.c&quot;&n; *    Copyright (C) 1991, 1992, 1993, 1994  Linus Torvalds&n; *&n; *  This program is free software; you can redistribute it and/or&n; *  modify it under the terms of the GNU General Public License&n; *  as published by the Free Software Foundation; either version&n; *  2 of the License, or (at your option) any later version.&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/highmem.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &quot;mmu_decl.h&quot;
DECL|variable|ioremap_base
r_int
r_int
id|ioremap_base
suffix:semicolon
DECL|variable|ioremap_bot
r_int
r_int
id|ioremap_bot
suffix:semicolon
DECL|variable|io_bat_index
r_int
id|io_bat_index
suffix:semicolon
macro_line|#if defined(CONFIG_6xx) || defined(CONFIG_POWER3)
DECL|macro|HAVE_BATS
mdefine_line|#define HAVE_BATS&t;1
macro_line|#endif
r_extern
r_char
id|etext
(braket
)braket
comma
id|_stext
(braket
)braket
suffix:semicolon
macro_line|#ifdef HAVE_BATS
r_extern
r_int
r_int
id|v_mapped_by_bats
c_func
(paren
r_int
r_int
id|va
)paren
suffix:semicolon
r_extern
r_int
r_int
id|p_mapped_by_bats
c_func
(paren
r_int
r_int
id|pa
)paren
suffix:semicolon
r_void
id|setbat
c_func
(paren
r_int
id|index
comma
r_int
r_int
id|virt
comma
r_int
r_int
id|phys
comma
r_int
r_int
id|size
comma
r_int
id|flags
)paren
suffix:semicolon
macro_line|#else /* !HAVE_BATS */
DECL|macro|v_mapped_by_bats
mdefine_line|#define v_mapped_by_bats(x)&t;(0UL)
DECL|macro|p_mapped_by_bats
mdefine_line|#define p_mapped_by_bats(x)&t;(0UL)
macro_line|#endif /* HAVE_BATS */
macro_line|#ifdef CONFIG_44x
multiline_comment|/* 44x uses an 8kB pgdir because it has 8-byte Linux PTEs. */
DECL|macro|PGDIR_ORDER
mdefine_line|#define PGDIR_ORDER&t;1
macro_line|#else
DECL|macro|PGDIR_ORDER
mdefine_line|#define PGDIR_ORDER&t;0
macro_line|#endif
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
id|ret
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret
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
id|PGDIR_ORDER
)paren
)paren
op_ne
l_int|NULL
)paren
id|clear_page
c_func
(paren
id|ret
)paren
suffix:semicolon
r_return
id|ret
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
r_extern
r_int
id|mem_init_done
suffix:semicolon
r_extern
r_void
op_star
id|early_get_page
c_func
(paren
r_void
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mem_init_done
)paren
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
)paren
suffix:semicolon
r_else
id|pte
op_assign
(paren
id|pte_t
op_star
)paren
id|early_get_page
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pte
)paren
id|clear_page
c_func
(paren
id|pte
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
macro_line|#ifdef CONFIG_HIGHPTE
r_int
id|flags
op_assign
id|GFP_KERNEL
op_or
id|__GFP_HIGHMEM
op_or
id|__GFP_REPEAT
suffix:semicolon
macro_line|#else
r_int
id|flags
op_assign
id|GFP_KERNEL
op_or
id|__GFP_REPEAT
suffix:semicolon
macro_line|#endif
id|pte
op_assign
id|alloc_pages
c_func
(paren
id|flags
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pte
)paren
id|clear_highpage
c_func
(paren
id|pte
)paren
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|function|pte_free_kernel
r_void
id|pte_free_kernel
c_func
(paren
id|pte_t
op_star
id|pte
)paren
(brace
id|free_page
c_func
(paren
(paren
r_int
r_int
)paren
id|pte
)paren
suffix:semicolon
)brace
DECL|function|pte_free
r_void
id|pte_free
c_func
(paren
r_struct
id|page
op_star
id|pte
)paren
(brace
id|__free_page
c_func
(paren
id|pte
)paren
suffix:semicolon
)brace
macro_line|#ifndef CONFIG_44x
r_void
op_star
DECL|function|ioremap
id|ioremap
c_func
(paren
id|phys_addr_t
id|addr
comma
r_int
r_int
id|size
)paren
(brace
r_return
id|__ioremap
c_func
(paren
id|addr
comma
id|size
comma
id|_PAGE_NO_CACHE
)paren
suffix:semicolon
)brace
macro_line|#else /* CONFIG_44x */
r_void
op_star
DECL|function|ioremap64
id|ioremap64
c_func
(paren
r_int
r_int
r_int
id|addr
comma
r_int
r_int
id|size
)paren
(brace
r_return
id|__ioremap
c_func
(paren
id|addr
comma
id|size
comma
id|_PAGE_NO_CACHE
)paren
suffix:semicolon
)brace
r_void
op_star
DECL|function|ioremap
id|ioremap
c_func
(paren
id|phys_addr_t
id|addr
comma
r_int
r_int
id|size
)paren
(brace
id|phys_addr_t
id|addr64
op_assign
id|fixup_bigphys_addr
c_func
(paren
id|addr
comma
id|size
)paren
suffix:semicolon
suffix:semicolon
r_return
id|ioremap64
c_func
(paren
id|addr64
comma
id|size
)paren
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_44x */
r_void
op_star
DECL|function|__ioremap
id|__ioremap
c_func
(paren
id|phys_addr_t
id|addr
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
r_int
r_int
id|v
comma
id|i
suffix:semicolon
id|phys_addr_t
id|p
suffix:semicolon
r_int
id|err
suffix:semicolon
multiline_comment|/*&n;&t; * Choose an address to map it to.&n;&t; * Once the vmalloc system is running, we use it.&n;&t; * Before then, we use space going down from ioremap_base&n;&t; * (ioremap_bot records where we&squot;re up to).&n;&t; */
id|p
op_assign
id|addr
op_amp
id|PAGE_MASK
suffix:semicolon
id|size
op_assign
id|PAGE_ALIGN
c_func
(paren
id|addr
op_plus
id|size
)paren
op_minus
id|p
suffix:semicolon
multiline_comment|/*&n;&t; * If the address lies within the first 16 MB, assume it&squot;s in ISA&n;&t; * memory space&n;&t; */
r_if
c_cond
(paren
id|p
OL
l_int|16
op_star
l_int|1024
op_star
l_int|1024
)paren
id|p
op_add_assign
id|_ISA_MEM_BASE
suffix:semicolon
multiline_comment|/*&n;&t; * Don&squot;t allow anybody to remap normal RAM that we&squot;re using.&n;&t; * mem_init() sets high_memory so only do the check after that.&n;&t; */
r_if
c_cond
(paren
id|mem_init_done
op_logical_and
(paren
id|p
OL
id|virt_to_phys
c_func
(paren
id|high_memory
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;__ioremap(): phys addr &quot;
id|PTE_FMT
l_string|&quot; is RAM lr %p&bslash;n&quot;
comma
id|p
comma
id|__builtin_return_address
c_func
(paren
l_int|0
)paren
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|size
op_eq
l_int|0
)paren
r_return
l_int|NULL
suffix:semicolon
multiline_comment|/*&n;&t; * Is it already mapped?  Perhaps overlapped by a previous&n;&t; * BAT mapping.  If the whole area is mapped then we&squot;re done,&n;&t; * otherwise remap it since we want to keep the virt addrs for&n;&t; * each request contiguous.&n;&t; *&n;&t; * We make the assumption here that if the bottom and top&n;&t; * of the range we want are mapped then it&squot;s mapped to the&n;&t; * same virt address (and this is contiguous).&n;&t; *  -- Cort&n;&t; */
r_if
c_cond
(paren
(paren
id|v
op_assign
id|p_mapped_by_bats
c_func
(paren
id|p
)paren
)paren
multiline_comment|/*&amp;&amp; p_mapped_by_bats(p+size-1)*/
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|mem_init_done
)paren
(brace
r_struct
id|vm_struct
op_star
id|area
suffix:semicolon
id|area
op_assign
id|get_vm_area
c_func
(paren
id|size
comma
id|VM_IOREMAP
)paren
suffix:semicolon
r_if
c_cond
(paren
id|area
op_eq
l_int|0
)paren
r_return
l_int|NULL
suffix:semicolon
id|v
op_assign
id|VMALLOC_VMADDR
c_func
(paren
id|area-&gt;addr
)paren
suffix:semicolon
)brace
r_else
(brace
id|v
op_assign
(paren
id|ioremap_bot
op_sub_assign
id|size
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|flags
op_amp
id|_PAGE_PRESENT
)paren
op_eq
l_int|0
)paren
id|flags
op_or_assign
id|_PAGE_KERNEL
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
id|_PAGE_NO_CACHE
)paren
id|flags
op_or_assign
id|_PAGE_GUARDED
suffix:semicolon
multiline_comment|/*&n;&t; * Should check if it is a candidate for a BAT mapping&n;&t; */
id|err
op_assign
l_int|0
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
id|size
op_logical_and
id|err
op_eq
l_int|0
suffix:semicolon
id|i
op_add_assign
id|PAGE_SIZE
)paren
id|err
op_assign
id|map_page
c_func
(paren
id|v
op_plus
id|i
comma
id|p
op_plus
id|i
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
r_if
c_cond
(paren
id|mem_init_done
)paren
id|vunmap
c_func
(paren
(paren
r_void
op_star
)paren
id|v
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|out
suffix:colon
r_return
(paren
r_void
op_star
)paren
(paren
id|v
op_plus
(paren
(paren
r_int
r_int
)paren
id|addr
op_amp
op_complement
id|PAGE_MASK
)paren
)paren
suffix:semicolon
)brace
DECL|function|iounmap
r_void
id|iounmap
c_func
(paren
r_void
op_star
id|addr
)paren
(brace
multiline_comment|/*&n;&t; * If mapped by BATs then there is nothing to do.&n;&t; * Calling vfree() generates a benign warning.&n;&t; */
r_if
c_cond
(paren
id|v_mapped_by_bats
c_func
(paren
(paren
r_int
r_int
)paren
id|addr
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|addr
OG
id|high_memory
op_logical_and
(paren
r_int
r_int
)paren
id|addr
OL
id|ioremap_bot
)paren
id|vunmap
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
)paren
id|addr
)paren
)paren
suffix:semicolon
)brace
r_int
DECL|function|map_page
id|map_page
c_func
(paren
r_int
r_int
id|va
comma
id|phys_addr_t
id|pa
comma
r_int
id|flags
)paren
(brace
id|pmd_t
op_star
id|pd
suffix:semicolon
id|pte_t
op_star
id|pg
suffix:semicolon
r_int
id|err
op_assign
op_minus
id|ENOMEM
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|init_mm.page_table_lock
)paren
suffix:semicolon
multiline_comment|/* Use upper 10 bits of VA to index the first level map */
id|pd
op_assign
id|pmd_offset
c_func
(paren
id|pgd_offset_k
c_func
(paren
id|va
)paren
comma
id|va
)paren
suffix:semicolon
multiline_comment|/* Use middle 10 bits of VA to index the second-level map */
id|pg
op_assign
id|pte_alloc_kernel
c_func
(paren
op_amp
id|init_mm
comma
id|pd
comma
id|va
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pg
op_ne
l_int|0
)paren
(brace
id|err
op_assign
l_int|0
suffix:semicolon
id|set_pte
c_func
(paren
id|pg
comma
id|pfn_pte
c_func
(paren
id|pa
op_rshift
id|PAGE_SHIFT
comma
id|__pgprot
c_func
(paren
id|flags
)paren
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mem_init_done
)paren
id|flush_HPTE
c_func
(paren
l_int|0
comma
id|va
comma
id|pmd_val
c_func
(paren
op_star
id|pd
)paren
)paren
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|init_mm.page_table_lock
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/*&n; * Map in all of physical memory starting at KERNELBASE.&n; */
DECL|function|mapin_ram
r_void
id|__init
id|mapin_ram
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|v
comma
id|p
comma
id|s
comma
id|f
suffix:semicolon
id|s
op_assign
id|mmu_mapin_ram
c_func
(paren
)paren
suffix:semicolon
id|v
op_assign
id|KERNELBASE
op_plus
id|s
suffix:semicolon
id|p
op_assign
id|PPC_MEMSTART
op_plus
id|s
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|s
OL
id|total_lowmem
suffix:semicolon
id|s
op_add_assign
id|PAGE_SIZE
)paren
(brace
r_if
c_cond
(paren
(paren
r_char
op_star
)paren
id|v
op_ge
id|_stext
op_logical_and
(paren
r_char
op_star
)paren
id|v
OL
id|etext
)paren
id|f
op_assign
id|_PAGE_RAM_TEXT
suffix:semicolon
r_else
id|f
op_assign
id|_PAGE_RAM
suffix:semicolon
id|map_page
c_func
(paren
id|v
comma
id|p
comma
id|f
)paren
suffix:semicolon
id|v
op_add_assign
id|PAGE_SIZE
suffix:semicolon
id|p
op_add_assign
id|PAGE_SIZE
suffix:semicolon
)brace
)brace
multiline_comment|/* is x a power of 2? */
DECL|macro|is_power_of_2
mdefine_line|#define is_power_of_2(x)&t;((x) != 0 &amp;&amp; (((x) &amp; ((x) - 1)) == 0))
multiline_comment|/*&n; * Set up a mapping for a block of I/O.&n; * virt, phys, size must all be page-aligned.&n; * This should only be called before ioremap is called.&n; */
DECL|function|io_block_mapping
r_void
id|__init
id|io_block_mapping
c_func
(paren
r_int
r_int
id|virt
comma
id|phys_addr_t
id|phys
comma
r_int
r_int
id|size
comma
r_int
id|flags
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|virt
OG
id|KERNELBASE
op_logical_and
id|virt
OL
id|ioremap_bot
)paren
id|ioremap_bot
op_assign
id|ioremap_base
op_assign
id|virt
suffix:semicolon
macro_line|#ifdef HAVE_BATS
multiline_comment|/*&n;&t; * Use a BAT for this if possible...&n;&t; */
r_if
c_cond
(paren
id|io_bat_index
OL
l_int|2
op_logical_and
id|is_power_of_2
c_func
(paren
id|size
)paren
op_logical_and
(paren
id|virt
op_amp
(paren
id|size
op_minus
l_int|1
)paren
)paren
op_eq
l_int|0
op_logical_and
(paren
id|phys
op_amp
(paren
id|size
op_minus
l_int|1
)paren
)paren
op_eq
l_int|0
)paren
(brace
id|setbat
c_func
(paren
id|io_bat_index
comma
id|virt
comma
id|phys
comma
id|size
comma
id|flags
)paren
suffix:semicolon
op_increment
id|io_bat_index
suffix:semicolon
r_return
suffix:semicolon
)brace
macro_line|#endif /* HAVE_BATS */
multiline_comment|/* No BATs available, put it in the page tables. */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|size
suffix:semicolon
id|i
op_add_assign
id|PAGE_SIZE
)paren
id|map_page
c_func
(paren
id|virt
op_plus
id|i
comma
id|phys
op_plus
id|i
comma
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/* Scan the real Linux page tables and return a PTE pointer for&n; * a virtual address in a context.&n; * Returns true (1) if PTE was found, zero otherwise.  The pointer to&n; * the PTE pointer is unmodified if PTE is not found.&n; */
r_int
DECL|function|get_pteptr
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
id|retval
op_assign
l_int|0
suffix:semicolon
id|pgd
op_assign
id|pgd_offset
c_func
(paren
id|mm
comma
id|addr
op_amp
id|PAGE_MASK
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pgd
)paren
(brace
id|pmd
op_assign
id|pmd_offset
c_func
(paren
id|pgd
comma
id|addr
op_amp
id|PAGE_MASK
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pmd_present
c_func
(paren
op_star
id|pmd
)paren
)paren
(brace
id|pte
op_assign
id|pte_offset_map
c_func
(paren
id|pmd
comma
id|addr
op_amp
id|PAGE_MASK
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pte
)paren
(brace
id|retval
op_assign
l_int|1
suffix:semicolon
op_star
id|ptep
op_assign
id|pte
suffix:semicolon
multiline_comment|/* XXX caller needs to do pte_unmap, yuck */
)brace
)brace
)brace
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/* Find physical address for this virtual address.  Normally used by&n; * I/O functions, but anyone can call it.&n; */
DECL|function|iopa
r_int
r_int
id|iopa
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_int
r_int
id|pa
suffix:semicolon
multiline_comment|/* I don&squot;t know why this won&squot;t work on PMacs or CHRP.  It&n;&t; * appears there is some bug, or there is some implicit&n;&t; * mapping done not properly represented by BATs or in page&n;&t; * tables.......I am actively working on resolving this, but&n;&t; * can&squot;t hold up other stuff.  -- Dan&n;&t; */
id|pte_t
op_star
id|pte
suffix:semicolon
r_struct
id|mm_struct
op_star
id|mm
suffix:semicolon
multiline_comment|/* Check the BATs */
id|pa
op_assign
id|v_mapped_by_bats
c_func
(paren
id|addr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pa
)paren
r_return
id|pa
suffix:semicolon
multiline_comment|/* Allow mapping of user addresses (within the thread)&n;&t; * for DMA if necessary.&n;&t; */
r_if
c_cond
(paren
id|addr
OL
id|TASK_SIZE
)paren
id|mm
op_assign
id|current-&gt;mm
suffix:semicolon
r_else
id|mm
op_assign
op_amp
id|init_mm
suffix:semicolon
id|pa
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|get_pteptr
c_func
(paren
id|mm
comma
id|addr
comma
op_amp
id|pte
)paren
)paren
(brace
id|pa
op_assign
(paren
id|pte_val
c_func
(paren
op_star
id|pte
)paren
op_amp
id|PAGE_MASK
)paren
op_or
(paren
id|addr
op_amp
op_complement
id|PAGE_MASK
)paren
suffix:semicolon
id|pte_unmap
c_func
(paren
id|pte
)paren
suffix:semicolon
)brace
r_return
id|pa
suffix:semicolon
)brace
multiline_comment|/* This is will find the virtual address for a physical one....&n; * Swiped from APUS, could be dangerous :-).&n; * This is only a placeholder until I really find a way to make this&n; * work.  -- Dan&n; */
r_int
r_int
DECL|function|mm_ptov
id|mm_ptov
(paren
r_int
r_int
id|paddr
)paren
(brace
r_int
r_int
id|ret
suffix:semicolon
macro_line|#if 0
r_if
c_cond
(paren
id|paddr
OL
l_int|16
op_star
l_int|1024
op_star
l_int|1024
)paren
id|ret
op_assign
id|ZTWO_VADDR
c_func
(paren
id|paddr
)paren
suffix:semicolon
r_else
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
id|i
OL
id|kmap_chunk_count
suffix:semicolon
)paren
(brace
r_int
r_int
id|phys
op_assign
id|kmap_chunks
(braket
id|i
op_increment
)braket
suffix:semicolon
r_int
r_int
id|size
op_assign
id|kmap_chunks
(braket
id|i
op_increment
)braket
suffix:semicolon
r_int
r_int
id|virt
op_assign
id|kmap_chunks
(braket
id|i
op_increment
)braket
suffix:semicolon
r_if
c_cond
(paren
id|paddr
op_ge
id|phys
op_logical_and
id|paddr
OL
(paren
id|phys
op_plus
id|size
)paren
)paren
(brace
id|ret
op_assign
id|virt
op_plus
id|paddr
op_minus
id|phys
suffix:semicolon
r_goto
m_exit
suffix:semicolon
)brace
)brace
id|ret
op_assign
(paren
r_int
r_int
)paren
id|__va
c_func
(paren
id|paddr
)paren
suffix:semicolon
)brace
m_exit
suffix:colon
macro_line|#ifdef DEBUGPV
id|printk
(paren
l_string|&quot;PTOV(%lx)=%lx&bslash;n&quot;
comma
id|paddr
comma
id|ret
)paren
suffix:semicolon
macro_line|#endif
macro_line|#else
id|ret
op_assign
(paren
r_int
r_int
)paren
id|paddr
op_plus
id|KERNELBASE
suffix:semicolon
macro_line|#endif
r_return
id|ret
suffix:semicolon
)brace
eof
