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
macro_line|#include &lt;linux/init.h&gt;
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
macro_line|#ifdef CONFIG_PMAC_DART
r_extern
r_int
r_int
id|dart_tablebase
suffix:semicolon
macro_line|#endif /* CONFIG_PMAC_DART */
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
DECL|function|loop_forever
r_static
r_inline
r_void
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
DECL|function|create_pte_mapping
r_static
r_inline
r_void
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
DECL|function|htab_initialize
r_void
id|__init
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
r_int
id|i
comma
id|use_largepages
op_assign
l_int|0
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
op_logical_or
id|systemcfg-&gt;platform
op_eq
id|PLATFORM_POWERMAC
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
multiline_comment|/* On U3 based machines, we need to reserve the DART area and&n;&t; * _NOT_ map it to avoid cache paradoxes as it&squot;s remapped non&n;&t; * cacheable later on&n;&t; */
r_if
c_cond
(paren
id|cur_cpu_spec-&gt;cpu_features
op_amp
id|CPU_FTR_16M_PAGE
)paren
id|use_largepages
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* add all physical memory to the bootmem map */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|lmb.memory.cnt
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
r_int
id|base
comma
id|size
suffix:semicolon
id|base
op_assign
id|lmb.memory.region
(braket
id|i
)braket
dot
id|physbase
op_plus
id|KERNELBASE
suffix:semicolon
id|size
op_assign
id|lmb.memory.region
(braket
id|i
)braket
dot
id|size
suffix:semicolon
macro_line|#ifdef CONFIG_PMAC_DART
multiline_comment|/* Do not map the DART space. Fortunately, it will be aligned&n;&t;&t; * in such a way that it will not cross two lmb regions and will&n;&t;&t; * fit within a single 16Mb page.&n;&t;&t; * The DART space is assumed to be a full 16Mb region even if we&n;&t;&t; * only use 2Mb of that space. We will use more of it later for&n;&t;&t; * AGP GART. We have to use a full 16Mb large page.&n;&t;&t; */
r_if
c_cond
(paren
id|dart_tablebase
op_ne
l_int|0
op_logical_and
id|dart_tablebase
op_ge
id|base
op_logical_and
id|dart_tablebase
OL
(paren
id|base
op_plus
id|size
)paren
)paren
(brace
r_if
c_cond
(paren
id|base
op_ne
id|dart_tablebase
)paren
id|create_pte_mapping
c_func
(paren
id|base
comma
id|dart_tablebase
comma
id|mode_rw
comma
id|use_largepages
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|base
op_plus
id|size
)paren
OG
(paren
id|dart_tablebase
op_plus
l_int|16
op_star
id|MB
)paren
)paren
id|create_pte_mapping
c_func
(paren
id|dart_tablebase
op_plus
l_int|16
op_star
id|MB
comma
id|base
op_plus
id|size
comma
id|mode_rw
comma
id|use_largepages
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_PMAC_DART */
id|create_pte_mapping
c_func
(paren
id|base
comma
id|base
op_plus
id|size
comma
id|mode_rw
comma
id|use_largepages
)paren
suffix:semicolon
)brace
)brace
DECL|macro|KB
macro_line|#undef KB
DECL|macro|MB
macro_line|#undef MB
macro_line|#endif
multiline_comment|/*&n; * Called by asm hashtable.S for doing lazy icache flush&n; */
DECL|function|hash_page_do_lazy_icache
r_int
r_int
id|hash_page_do_lazy_icache
c_func
(paren
r_int
r_int
id|pp
comma
id|pte_t
id|pte
comma
r_int
id|trap
)paren
(brace
r_struct
id|page
op_star
id|page
suffix:semicolon
DECL|macro|PPC64_HWNOEXEC
mdefine_line|#define PPC64_HWNOEXEC (1 &lt;&lt; 2)
r_if
c_cond
(paren
op_logical_neg
id|pfn_valid
c_func
(paren
id|pte_pfn
c_func
(paren
id|pte
)paren
)paren
)paren
r_return
id|pp
suffix:semicolon
id|page
op_assign
id|pte_page
c_func
(paren
id|pte
)paren
suffix:semicolon
multiline_comment|/* page is dirty */
r_if
c_cond
(paren
op_logical_neg
id|test_bit
c_func
(paren
id|PG_arch_1
comma
op_amp
id|page-&gt;flags
)paren
op_logical_and
op_logical_neg
id|PageReserved
c_func
(paren
id|page
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
id|pp
op_or_assign
id|PPC64_HWNOEXEC
suffix:semicolon
)brace
r_return
id|pp
suffix:semicolon
)brace
multiline_comment|/*&n; * Called by asm hashtable.S in case of critical insert failure&n; */
DECL|function|htab_insert_failure
r_void
id|htab_insert_failure
c_func
(paren
r_void
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;hash_page: pte_insert failed&bslash;n&quot;
)paren
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
id|mm-&gt;context.id
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
multiline_comment|/* Is this a huge page ? */
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|in_hugepage_area
c_func
(paren
id|mm-&gt;context
comma
id|ea
)paren
)paren
)paren
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
r_else
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
r_if
c_cond
(paren
id|ptep
op_eq
l_int|NULL
)paren
r_return
l_int|1
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
id|__get_cpu_var
c_func
(paren
id|ppc64_tlb_batch
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
DECL|function|make_bl
r_static
r_inline
r_void
id|make_bl
c_func
(paren
r_int
r_int
op_star
id|insn_addr
comma
r_void
op_star
id|func
)paren
(brace
r_int
r_int
id|funcp
op_assign
op_star
(paren
(paren
r_int
r_int
op_star
)paren
id|func
)paren
suffix:semicolon
r_int
id|offset
op_assign
id|funcp
op_minus
(paren
r_int
r_int
)paren
id|insn_addr
suffix:semicolon
op_star
id|insn_addr
op_assign
(paren
r_int
r_int
)paren
(paren
l_int|0x48000001
op_or
(paren
id|offset
op_amp
l_int|0x03fffffc
)paren
)paren
suffix:semicolon
id|flush_icache_range
c_func
(paren
(paren
r_int
r_int
)paren
id|insn_addr
comma
l_int|4
op_plus
(paren
r_int
r_int
)paren
id|insn_addr
)paren
suffix:semicolon
)brace
DECL|function|htab_finish_init
r_void
id|__init
id|htab_finish_init
c_func
(paren
r_void
)paren
(brace
r_extern
r_int
r_int
op_star
id|htab_call_hpte_insert1
suffix:semicolon
r_extern
r_int
r_int
op_star
id|htab_call_hpte_insert2
suffix:semicolon
r_extern
r_int
r_int
op_star
id|htab_call_hpte_remove
suffix:semicolon
r_extern
r_int
r_int
op_star
id|htab_call_hpte_updatepp
suffix:semicolon
id|make_bl
c_func
(paren
id|htab_call_hpte_insert1
comma
id|ppc_md.hpte_insert
)paren
suffix:semicolon
id|make_bl
c_func
(paren
id|htab_call_hpte_insert2
comma
id|ppc_md.hpte_insert
)paren
suffix:semicolon
id|make_bl
c_func
(paren
id|htab_call_hpte_remove
comma
id|ppc_md.hpte_remove
)paren
suffix:semicolon
id|make_bl
c_func
(paren
id|htab_call_hpte_updatepp
comma
id|ppc_md.hpte_updatepp
)paren
suffix:semicolon
)brace
eof
