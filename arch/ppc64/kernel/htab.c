multiline_comment|/*&n; * PowerPC64 port by Mike Corrigan and Dave Engebretsen&n; *   {mikejc|engebret}@us.ibm.com&n; *&n; *    Copyright (c) 2000 Mike Corrigan &lt;mikejc@us.ibm.com&gt;&n; *&n; * SMP scalability work:&n; *    Copyright (C) 2001 Anton Blanchard &lt;anton@au.ibm.com&gt;, IBM&n; * &n; *    Module name: htab.c&n; *&n; *    Description:&n; *      PowerPC Hashed Page Table functions&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/sysctl.h&gt;
macro_line|#include &lt;linux/ctype.h&gt;
macro_line|#include &lt;linux/cache.h&gt;
macro_line|#include &lt;asm/ppcdebug.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/mmu.h&gt;
macro_line|#include &lt;asm/mmu_context.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/types.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/naca.h&gt;
macro_line|#include &lt;asm/pmc.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;asm/lmb.h&gt;
macro_line|#include &lt;asm/abs_addr.h&gt;
macro_line|#include &lt;asm/tlbflush.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/eeh.h&gt;
macro_line|#include &lt;asm/tlb.h&gt;
macro_line|#include &lt;asm/cacheflush.h&gt;
macro_line|#include &lt;asm/cputable.h&gt;
multiline_comment|/*&n; * Note:  pte   --&gt; Linux PTE&n; *        HPTE  --&gt; PowerPC Hashed Page Table Entry&n; *&n; * Execution context:&n; *   htab_initialize is called with the MMU off (of course), but&n; *   the kernel has been copied down to zero so it can directly&n; *   reference global data.  At this point it is very difficult&n; *   to print debug info.&n; *&n; */
DECL|variable|htab_data
id|HTAB
id|htab_data
op_assign
(brace
l_int|NULL
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
suffix:semicolon
r_extern
r_int
r_int
id|_SDR1
suffix:semicolon
DECL|macro|KB
mdefine_line|#define KB (1024)
DECL|macro|MB
mdefine_line|#define MB (1024*KB)
r_static
r_inline
r_void
DECL|function|loop_forever
id|loop_forever
c_func
(paren
r_void
)paren
(brace
r_volatile
r_int
r_int
id|x
op_assign
l_int|1
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|x
suffix:semicolon
id|x
op_or_assign
l_int|1
)paren
(brace
suffix:semicolon
)brace
)brace
macro_line|#ifdef CONFIG_PPC_PSERIES
r_static
r_inline
r_void
DECL|function|create_pte_mapping
id|create_pte_mapping
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
r_int
r_int
id|mode
comma
r_int
id|large
)paren
(brace
r_int
r_int
id|addr
suffix:semicolon
r_int
r_int
id|step
suffix:semicolon
r_if
c_cond
(paren
id|large
)paren
id|step
op_assign
l_int|16
op_star
id|MB
suffix:semicolon
r_else
id|step
op_assign
l_int|4
op_star
id|KB
suffix:semicolon
r_for
c_loop
(paren
id|addr
op_assign
id|start
suffix:semicolon
id|addr
OL
id|end
suffix:semicolon
id|addr
op_add_assign
id|step
)paren
(brace
r_int
r_int
id|vpn
comma
id|hash
comma
id|hpteg
suffix:semicolon
r_int
r_int
id|vsid
op_assign
id|get_kernel_vsid
c_func
(paren
id|addr
)paren
suffix:semicolon
r_int
r_int
id|va
op_assign
(paren
id|vsid
op_lshift
l_int|28
)paren
op_or
(paren
id|addr
op_amp
l_int|0xfffffff
)paren
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
id|large
)paren
id|vpn
op_assign
id|va
op_rshift
id|LARGE_PAGE_SHIFT
suffix:semicolon
r_else
id|vpn
op_assign
id|va
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|hash
op_assign
id|hpt_hash
c_func
(paren
id|vpn
comma
id|large
)paren
suffix:semicolon
id|hpteg
op_assign
(paren
(paren
id|hash
op_amp
id|htab_data.htab_hash_mask
)paren
op_star
id|HPTES_PER_GROUP
)paren
suffix:semicolon
r_if
c_cond
(paren
id|systemcfg-&gt;platform
op_eq
id|PLATFORM_PSERIES_LPAR
)paren
id|ret
op_assign
id|pSeries_lpar_hpte_insert
c_func
(paren
id|hpteg
comma
id|va
comma
(paren
r_int
r_int
)paren
id|__v2a
c_func
(paren
id|addr
)paren
op_rshift
id|PAGE_SHIFT
comma
l_int|0
comma
id|mode
comma
l_int|1
comma
id|large
)paren
suffix:semicolon
r_else
id|ret
op_assign
id|pSeries_hpte_insert
c_func
(paren
id|hpteg
comma
id|va
comma
(paren
r_int
r_int
)paren
id|__v2a
c_func
(paren
id|addr
)paren
op_rshift
id|PAGE_SHIFT
comma
l_int|0
comma
id|mode
comma
l_int|1
comma
id|large
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
op_minus
l_int|1
)paren
(brace
id|ppc64_terminate_msg
c_func
(paren
l_int|0x20
comma
l_string|&quot;create_pte_mapping&quot;
)paren
suffix:semicolon
id|loop_forever
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
)brace
r_void
DECL|function|htab_initialize
id|htab_initialize
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|table
comma
id|htab_size_bytes
suffix:semicolon
r_int
r_int
id|pteg_count
suffix:semicolon
r_int
r_int
id|mode_rw
suffix:semicolon
multiline_comment|/*&n;&t; * Calculate the required size of the htab.  We want the number of&n;&t; * PTEGs to equal one half the number of real pages.&n;&t; */
id|htab_size_bytes
op_assign
l_int|1UL
op_lshift
id|naca-&gt;pftSize
suffix:semicolon
id|pteg_count
op_assign
id|htab_size_bytes
op_rshift
l_int|7
suffix:semicolon
multiline_comment|/* For debug, make the HTAB 1/8 as big as it normally would be. */
id|ifppcdebug
c_func
(paren
id|PPCDBG_HTABSIZE
)paren
(brace
id|pteg_count
op_rshift_assign
l_int|3
suffix:semicolon
id|htab_size_bytes
op_assign
id|pteg_count
op_lshift
l_int|7
suffix:semicolon
)brace
id|htab_data.htab_num_ptegs
op_assign
id|pteg_count
suffix:semicolon
id|htab_data.htab_hash_mask
op_assign
id|pteg_count
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|systemcfg-&gt;platform
op_eq
id|PLATFORM_PSERIES
)paren
(brace
multiline_comment|/* Find storage for the HPT.  Must be contiguous in&n;&t;&t; * the absolute address space.&n;&t;&t; */
id|table
op_assign
id|lmb_alloc
c_func
(paren
id|htab_size_bytes
comma
id|htab_size_bytes
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|table
)paren
(brace
id|ppc64_terminate_msg
c_func
(paren
l_int|0x20
comma
l_string|&quot;hpt space&quot;
)paren
suffix:semicolon
id|loop_forever
c_func
(paren
)paren
suffix:semicolon
)brace
id|htab_data.htab
op_assign
(paren
id|HPTE
op_star
)paren
id|__a2v
c_func
(paren
id|table
)paren
suffix:semicolon
multiline_comment|/* htab absolute addr + encoded htabsize */
id|_SDR1
op_assign
id|table
op_plus
id|__ilog2
c_func
(paren
id|pteg_count
)paren
op_minus
l_int|11
suffix:semicolon
multiline_comment|/* Initialize the HPT with no entries */
id|memset
c_func
(paren
(paren
r_void
op_star
)paren
id|table
comma
l_int|0
comma
id|htab_size_bytes
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Using a hypervisor which owns the htab */
id|htab_data.htab
op_assign
l_int|NULL
suffix:semicolon
id|_SDR1
op_assign
l_int|0
suffix:semicolon
)brace
id|mode_rw
op_assign
id|_PAGE_ACCESSED
op_or
id|_PAGE_COHERENT
op_or
id|PP_RWXX
suffix:semicolon
multiline_comment|/* XXX we currently map kernel text rw, should fix this */
r_if
c_cond
(paren
(paren
id|cur_cpu_spec-&gt;cpu_features
op_amp
id|CPU_FTR_16M_PAGE
)paren
op_logical_and
id|systemcfg-&gt;physicalMemorySize
OG
l_int|256
op_star
id|MB
)paren
(brace
id|create_pte_mapping
c_func
(paren
(paren
r_int
r_int
)paren
id|KERNELBASE
comma
id|KERNELBASE
op_plus
l_int|256
op_star
id|MB
comma
id|mode_rw
comma
l_int|0
)paren
suffix:semicolon
id|create_pte_mapping
c_func
(paren
(paren
r_int
r_int
)paren
id|KERNELBASE
op_plus
l_int|256
op_star
id|MB
comma
id|KERNELBASE
op_plus
(paren
id|systemcfg-&gt;physicalMemorySize
)paren
comma
id|mode_rw
comma
l_int|1
)paren
suffix:semicolon
)brace
r_else
(brace
id|create_pte_mapping
c_func
(paren
(paren
r_int
r_int
)paren
id|KERNELBASE
comma
id|KERNELBASE
op_plus
(paren
id|systemcfg-&gt;physicalMemorySize
)paren
comma
id|mode_rw
comma
l_int|0
)paren
suffix:semicolon
)brace
)brace
DECL|macro|KB
macro_line|#undef KB
DECL|macro|MB
macro_line|#undef MB
macro_line|#endif
multiline_comment|/*&n; * find_linux_pte returns the address of a linux pte for a given &n; * effective address and directory.  If not found, it returns zero.&n; */
DECL|function|find_linux_pte
id|pte_t
op_star
id|find_linux_pte
c_func
(paren
id|pgd_t
op_star
id|pgdir
comma
r_int
r_int
id|ea
)paren
(brace
id|pgd_t
op_star
id|pg
suffix:semicolon
id|pmd_t
op_star
id|pm
suffix:semicolon
id|pte_t
op_star
id|pt
op_assign
l_int|NULL
suffix:semicolon
id|pte_t
id|pte
suffix:semicolon
id|pg
op_assign
id|pgdir
op_plus
id|pgd_index
c_func
(paren
id|ea
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pgd_none
c_func
(paren
op_star
id|pg
)paren
)paren
(brace
id|pm
op_assign
id|pmd_offset
c_func
(paren
id|pg
comma
id|ea
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pmd_present
c_func
(paren
op_star
id|pm
)paren
)paren
(brace
id|pt
op_assign
id|pte_offset_kernel
c_func
(paren
id|pm
comma
id|ea
)paren
suffix:semicolon
id|pte
op_assign
op_star
id|pt
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pte_present
c_func
(paren
id|pte
)paren
)paren
id|pt
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
r_return
id|pt
suffix:semicolon
)brace
DECL|function|computeHptePP
r_static
r_inline
r_int
r_int
id|computeHptePP
c_func
(paren
r_int
r_int
id|pte
)paren
(brace
r_return
(paren
id|pte
op_amp
id|_PAGE_USER
)paren
op_or
(paren
(paren
(paren
id|pte
op_amp
id|_PAGE_USER
)paren
op_rshift
l_int|1
)paren
op_amp
(paren
(paren
op_complement
(paren
(paren
id|pte
op_rshift
l_int|2
)paren
op_amp
multiline_comment|/* _PAGE_RW */
(paren
id|pte
op_rshift
l_int|7
)paren
)paren
)paren
op_amp
multiline_comment|/* _PAGE_DIRTY */
l_int|1
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Handle a fault by adding an HPTE. If the address can&squot;t be determined&n; * to be valid via Linux page tables, return 1. If handled return 0&n; */
DECL|function|__hash_page
r_int
id|__hash_page
c_func
(paren
r_int
r_int
id|ea
comma
r_int
r_int
id|access
comma
r_int
r_int
id|vsid
comma
id|pte_t
op_star
id|ptep
comma
r_int
r_int
id|trap
comma
r_int
id|local
)paren
(brace
r_int
r_int
id|va
comma
id|vpn
suffix:semicolon
r_int
r_int
id|newpp
comma
id|prpn
suffix:semicolon
r_int
r_int
id|hpteflags
suffix:semicolon
r_int
id|slot
suffix:semicolon
id|pte_t
id|old_pte
comma
id|new_pte
suffix:semicolon
multiline_comment|/* XXX fix for large ptes */
r_int
id|large
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Search the Linux page table for a match with va */
id|va
op_assign
(paren
id|vsid
op_lshift
l_int|28
)paren
op_or
(paren
id|ea
op_amp
l_int|0x0fffffff
)paren
suffix:semicolon
r_if
c_cond
(paren
id|large
)paren
id|vpn
op_assign
id|va
op_rshift
id|LARGE_PAGE_SHIFT
suffix:semicolon
r_else
id|vpn
op_assign
id|va
op_rshift
id|PAGE_SHIFT
suffix:semicolon
multiline_comment|/*&n;&t; * If no pte found or not present, send the problem up to&n;&t; * do_page_fault&n;&t; */
r_if
c_cond
(paren
id|unlikely
c_func
(paren
op_logical_neg
id|ptep
op_logical_or
op_logical_neg
id|pte_present
c_func
(paren
op_star
id|ptep
)paren
)paren
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/* &n;&t; * Check the user&squot;s access rights to the page.  If access should be&n;&t; * prevented then send the problem up to do_page_fault.&n;&t; */
id|access
op_or_assign
id|_PAGE_PRESENT
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|access
op_amp
op_complement
(paren
id|pte_val
c_func
(paren
op_star
id|ptep
)paren
)paren
)paren
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t; * At this point, we have a pte (old_pte) which can be used to build&n;&t; * or update an HPTE. There are 2 cases:&n;&t; *&n;&t; * 1. There is a valid (present) pte with no associated HPTE (this is &n;&t; *&t;the most common case)&n;&t; * 2. There is a valid (present) pte with an associated HPTE. The&n;&t; *&t;current values of the pp bits in the HPTE prevent access&n;&t; *&t;because we are doing software DIRTY bit management and the&n;&t; *&t;page is currently not DIRTY. &n;&t; */
id|old_pte
op_assign
op_star
id|ptep
suffix:semicolon
id|new_pte
op_assign
id|old_pte
suffix:semicolon
multiline_comment|/* If the attempted access was a store */
r_if
c_cond
(paren
id|access
op_amp
id|_PAGE_RW
)paren
id|pte_val
c_func
(paren
id|new_pte
)paren
op_or_assign
id|_PAGE_ACCESSED
op_or
id|_PAGE_DIRTY
suffix:semicolon
r_else
id|pte_val
c_func
(paren
id|new_pte
)paren
op_or_assign
id|_PAGE_ACCESSED
suffix:semicolon
id|newpp
op_assign
id|computeHptePP
c_func
(paren
id|pte_val
c_func
(paren
id|new_pte
)paren
)paren
suffix:semicolon
DECL|macro|PPC64_HWNOEXEC
mdefine_line|#define PPC64_HWNOEXEC (1 &lt;&lt; 2)
multiline_comment|/* We do lazy icache flushing on cpus that support it */
r_if
c_cond
(paren
id|unlikely
c_func
(paren
(paren
id|cur_cpu_spec-&gt;cpu_features
op_amp
id|CPU_FTR_NOEXECUTE
)paren
op_logical_and
id|pfn_valid
c_func
(paren
id|pte_pfn
c_func
(paren
id|new_pte
)paren
)paren
)paren
)paren
(brace
r_struct
id|page
op_star
id|page
op_assign
id|pte_page
c_func
(paren
id|new_pte
)paren
suffix:semicolon
multiline_comment|/* page is dirty */
r_if
c_cond
(paren
op_logical_neg
id|PageReserved
c_func
(paren
id|page
)paren
op_logical_and
op_logical_neg
id|test_bit
c_func
(paren
id|PG_arch_1
comma
op_amp
id|page-&gt;flags
)paren
)paren
(brace
r_if
c_cond
(paren
id|trap
op_eq
l_int|0x400
)paren
(brace
id|__flush_dcache_icache
c_func
(paren
id|page_address
c_func
(paren
id|page
)paren
)paren
suffix:semicolon
id|set_bit
c_func
(paren
id|PG_arch_1
comma
op_amp
id|page-&gt;flags
)paren
suffix:semicolon
)brace
r_else
(brace
id|newpp
op_or_assign
id|PPC64_HWNOEXEC
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/* Check if pte already has an hpte (case 2) */
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|pte_val
c_func
(paren
id|old_pte
)paren
op_amp
id|_PAGE_HASHPTE
)paren
)paren
(brace
multiline_comment|/* There MIGHT be an HPTE for this pte */
r_int
r_int
id|hash
comma
id|slot
comma
id|secondary
suffix:semicolon
id|hash
op_assign
id|hpt_hash
c_func
(paren
id|vpn
comma
id|large
)paren
suffix:semicolon
id|secondary
op_assign
(paren
id|pte_val
c_func
(paren
id|old_pte
)paren
op_amp
id|_PAGE_SECONDARY
)paren
op_rshift
l_int|15
suffix:semicolon
r_if
c_cond
(paren
id|secondary
)paren
id|hash
op_assign
op_complement
id|hash
suffix:semicolon
id|slot
op_assign
(paren
id|hash
op_amp
id|htab_data.htab_hash_mask
)paren
op_star
id|HPTES_PER_GROUP
suffix:semicolon
id|slot
op_add_assign
(paren
id|pte_val
c_func
(paren
id|old_pte
)paren
op_amp
id|_PAGE_GROUP_IX
)paren
op_rshift
l_int|12
suffix:semicolon
r_if
c_cond
(paren
id|ppc_md
dot
id|hpte_updatepp
c_func
(paren
id|slot
comma
id|newpp
comma
id|va
comma
id|large
comma
id|local
)paren
op_eq
op_minus
l_int|1
)paren
id|pte_val
c_func
(paren
id|old_pte
)paren
op_and_assign
op_complement
id|_PAGE_HPTEFLAGS
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|pte_same
c_func
(paren
id|old_pte
comma
id|new_pte
)paren
)paren
op_star
id|ptep
op_assign
id|new_pte
suffix:semicolon
)brace
r_if
c_cond
(paren
id|likely
c_func
(paren
op_logical_neg
(paren
id|pte_val
c_func
(paren
id|old_pte
)paren
op_amp
id|_PAGE_HASHPTE
)paren
)paren
)paren
(brace
r_int
r_int
id|hash
op_assign
id|hpt_hash
c_func
(paren
id|vpn
comma
id|large
)paren
suffix:semicolon
r_int
r_int
id|hpte_group
suffix:semicolon
id|prpn
op_assign
id|pte_val
c_func
(paren
id|old_pte
)paren
op_rshift
id|PTE_SHIFT
suffix:semicolon
id|repeat
suffix:colon
id|hpte_group
op_assign
(paren
(paren
id|hash
op_amp
id|htab_data.htab_hash_mask
)paren
op_star
id|HPTES_PER_GROUP
)paren
op_amp
op_complement
l_int|0x7UL
suffix:semicolon
multiline_comment|/* Update the linux pte with the HPTE slot */
id|pte_val
c_func
(paren
id|new_pte
)paren
op_and_assign
op_complement
id|_PAGE_HPTEFLAGS
suffix:semicolon
id|pte_val
c_func
(paren
id|new_pte
)paren
op_or_assign
id|_PAGE_HASHPTE
suffix:semicolon
multiline_comment|/* copy appropriate flags from linux pte */
id|hpteflags
op_assign
(paren
id|pte_val
c_func
(paren
id|new_pte
)paren
op_amp
l_int|0x1f8
)paren
op_or
id|newpp
suffix:semicolon
id|slot
op_assign
id|ppc_md
dot
id|hpte_insert
c_func
(paren
id|hpte_group
comma
id|va
comma
id|prpn
comma
l_int|0
comma
id|hpteflags
comma
l_int|0
comma
id|large
)paren
suffix:semicolon
multiline_comment|/* Primary is full, try the secondary */
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|slot
op_eq
op_minus
l_int|1
)paren
)paren
(brace
id|pte_val
c_func
(paren
id|new_pte
)paren
op_or_assign
l_int|1
op_lshift
l_int|15
suffix:semicolon
id|hpte_group
op_assign
(paren
(paren
op_complement
id|hash
op_amp
id|htab_data.htab_hash_mask
)paren
op_star
id|HPTES_PER_GROUP
)paren
op_amp
op_complement
l_int|0x7UL
suffix:semicolon
id|slot
op_assign
id|ppc_md
dot
id|hpte_insert
c_func
(paren
id|hpte_group
comma
id|va
comma
id|prpn
comma
l_int|1
comma
id|hpteflags
comma
l_int|0
comma
id|large
)paren
suffix:semicolon
r_if
c_cond
(paren
id|slot
op_eq
op_minus
l_int|1
)paren
(brace
r_if
c_cond
(paren
id|mftb
c_func
(paren
)paren
op_amp
l_int|0x1
)paren
id|hpte_group
op_assign
(paren
(paren
id|hash
op_amp
id|htab_data.htab_hash_mask
)paren
op_star
id|HPTES_PER_GROUP
)paren
op_amp
op_complement
l_int|0x7UL
suffix:semicolon
id|ppc_md
dot
id|hpte_remove
c_func
(paren
id|hpte_group
)paren
suffix:semicolon
r_goto
id|repeat
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|slot
op_eq
op_minus
l_int|2
)paren
)paren
id|panic
c_func
(paren
l_string|&quot;hash_page: pte_insert failed&bslash;n&quot;
)paren
suffix:semicolon
id|pte_val
c_func
(paren
id|new_pte
)paren
op_or_assign
(paren
id|slot
op_lshift
l_int|12
)paren
op_amp
id|_PAGE_GROUP_IX
suffix:semicolon
multiline_comment|/* &n;&t;&t; * No need to use ldarx/stdcx here because all who&n;&t;&t; * might be updating the pte will hold the&n;&t;&t; * page_table_lock or the hash_table_lock&n;&t;&t; * (we hold both)&n;&t;&t; */
op_star
id|ptep
op_assign
id|new_pte
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|hash_page
r_int
id|hash_page
c_func
(paren
r_int
r_int
id|ea
comma
r_int
r_int
id|access
comma
r_int
r_int
id|trap
)paren
(brace
r_void
op_star
id|pgdir
suffix:semicolon
r_int
r_int
id|vsid
suffix:semicolon
r_struct
id|mm_struct
op_star
id|mm
suffix:semicolon
id|pte_t
op_star
id|ptep
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_int
id|user_region
op_assign
l_int|0
suffix:semicolon
r_int
id|local
op_assign
l_int|0
suffix:semicolon
id|cpumask_t
id|tmp
suffix:semicolon
multiline_comment|/* Check for invalid addresses. */
r_if
c_cond
(paren
op_logical_neg
id|IS_VALID_EA
c_func
(paren
id|ea
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_switch
c_cond
(paren
id|REGION_ID
c_func
(paren
id|ea
)paren
)paren
(brace
r_case
id|USER_REGION_ID
suffix:colon
id|user_region
op_assign
l_int|1
suffix:semicolon
id|mm
op_assign
id|current-&gt;mm
suffix:semicolon
r_if
c_cond
(paren
id|mm
op_eq
l_int|NULL
)paren
r_return
l_int|1
suffix:semicolon
id|vsid
op_assign
id|get_vsid
c_func
(paren
id|mm-&gt;context
comma
id|ea
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IO_REGION_ID
suffix:colon
id|mm
op_assign
op_amp
id|ioremap_mm
suffix:semicolon
id|vsid
op_assign
id|get_kernel_vsid
c_func
(paren
id|ea
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|VMALLOC_REGION_ID
suffix:colon
id|mm
op_assign
op_amp
id|init_mm
suffix:semicolon
id|vsid
op_assign
id|get_kernel_vsid
c_func
(paren
id|ea
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#if 0
r_case
id|EEH_REGION_ID
suffix:colon
multiline_comment|/*&n;&t;&t; * Should only be hit if there is an access to MMIO space&n;&t;&t; * which is protected by EEH.&n;&t;&t; * Send the problem up to do_page_fault &n;&t;&t; */
r_case
id|KERNEL_REGION_ID
suffix:colon
multiline_comment|/*&n;&t;&t; * Should never get here - entire 0xC0... region is bolted.&n;&t;&t; * Send the problem up to do_page_fault &n;&t;&t; */
macro_line|#endif
r_default
suffix:colon
multiline_comment|/* Not a valid range&n;&t;&t; * Send the problem up to do_page_fault &n;&t;&t; */
r_return
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
id|pgdir
op_assign
id|mm-&gt;pgd
suffix:semicolon
r_if
c_cond
(paren
id|pgdir
op_eq
l_int|NULL
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t; * Lock the Linux page table to prevent mmap and kswapd&n;&t; * from modifying entries while we search and update&n;&t; */
id|spin_lock
c_func
(paren
op_amp
id|mm-&gt;page_table_lock
)paren
suffix:semicolon
id|tmp
op_assign
id|cpumask_of_cpu
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|user_region
op_logical_and
id|cpus_equal
c_func
(paren
id|mm-&gt;cpu_vm_mask
comma
id|tmp
)paren
)paren
id|local
op_assign
l_int|1
suffix:semicolon
id|ret
op_assign
id|hash_huge_page
c_func
(paren
id|mm
comma
id|access
comma
id|ea
comma
id|vsid
comma
id|local
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
(brace
id|ptep
op_assign
id|find_linux_pte
c_func
(paren
id|pgdir
comma
id|ea
)paren
suffix:semicolon
id|ret
op_assign
id|__hash_page
c_func
(paren
id|ea
comma
id|access
comma
id|vsid
comma
id|ptep
comma
id|trap
comma
id|local
)paren
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|mm-&gt;page_table_lock
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|flush_hash_page
r_void
id|flush_hash_page
c_func
(paren
r_int
r_int
id|context
comma
r_int
r_int
id|ea
comma
id|pte_t
id|pte
comma
r_int
id|local
)paren
(brace
r_int
r_int
id|vsid
comma
id|vpn
comma
id|va
comma
id|hash
comma
id|secondary
comma
id|slot
suffix:semicolon
multiline_comment|/* XXX fix for large ptes */
r_int
r_int
id|large
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ea
op_ge
id|USER_START
)paren
op_logical_and
(paren
id|ea
op_le
id|USER_END
)paren
)paren
id|vsid
op_assign
id|get_vsid
c_func
(paren
id|context
comma
id|ea
)paren
suffix:semicolon
r_else
id|vsid
op_assign
id|get_kernel_vsid
c_func
(paren
id|ea
)paren
suffix:semicolon
id|va
op_assign
(paren
id|vsid
op_lshift
l_int|28
)paren
op_or
(paren
id|ea
op_amp
l_int|0x0fffffff
)paren
suffix:semicolon
r_if
c_cond
(paren
id|large
)paren
id|vpn
op_assign
id|va
op_rshift
id|LARGE_PAGE_SHIFT
suffix:semicolon
r_else
id|vpn
op_assign
id|va
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|hash
op_assign
id|hpt_hash
c_func
(paren
id|vpn
comma
id|large
)paren
suffix:semicolon
id|secondary
op_assign
(paren
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
id|_PAGE_SECONDARY
)paren
op_rshift
l_int|15
suffix:semicolon
r_if
c_cond
(paren
id|secondary
)paren
id|hash
op_assign
op_complement
id|hash
suffix:semicolon
id|slot
op_assign
(paren
id|hash
op_amp
id|htab_data.htab_hash_mask
)paren
op_star
id|HPTES_PER_GROUP
suffix:semicolon
id|slot
op_add_assign
(paren
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
id|_PAGE_GROUP_IX
)paren
op_rshift
l_int|12
suffix:semicolon
id|ppc_md
dot
id|hpte_invalidate
c_func
(paren
id|slot
comma
id|va
comma
id|large
comma
id|local
)paren
suffix:semicolon
)brace
DECL|function|flush_hash_range
r_void
id|flush_hash_range
c_func
(paren
r_int
r_int
id|context
comma
r_int
r_int
id|number
comma
r_int
id|local
)paren
(brace
r_if
c_cond
(paren
id|ppc_md.flush_hash_range
)paren
(brace
id|ppc_md
dot
id|flush_hash_range
c_func
(paren
id|context
comma
id|number
comma
id|local
)paren
suffix:semicolon
)brace
r_else
(brace
r_int
id|i
suffix:semicolon
r_struct
id|ppc64_tlb_batch
op_star
id|batch
op_assign
op_amp
id|ppc64_tlb_batch
(braket
id|smp_processor_id
c_func
(paren
)paren
)braket
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
id|number
suffix:semicolon
id|i
op_increment
)paren
id|flush_hash_page
c_func
(paren
id|context
comma
id|batch-&gt;addr
(braket
id|i
)braket
comma
id|batch-&gt;pte
(braket
id|i
)braket
comma
id|local
)paren
suffix:semicolon
)brace
)brace
eof
