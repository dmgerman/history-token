multiline_comment|/*&n; * BK Id: %F% %I% %G% %U% %#%&n; */
multiline_comment|/*&n; * Procedures for MMU handling on iSeries systems, where we&n; * have to call the hypervisor to change things in the hash&n; * table.&n; *&n; * Copyright (C) 2001 IBM Corp.&n; * updated by Dave Boutcher (boutcher@us.ibm.com)&n; *&n; *  This program is free software; you can redistribute it and/or&n; *  modify it under the terms of the GNU General Public License&n; *  as published by the Free Software Foundation; either version&n; *  2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/mman.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/swap.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;linux/highmem.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
macro_line|#include &lt;asm/prom.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/mmu_context.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/mmu.h&gt;
macro_line|#include &lt;asm/bootx.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/iSeries/LparData.h&gt;
macro_line|#include &lt;asm/iSeries/HvCallHpt.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;asm/iSeries/iSeries_dma.h&gt;
macro_line|#include &quot;mmu_decl.h&quot;
DECL|variable|iSeries_max_kernel_hpt_slot
r_int
id|iSeries_max_kernel_hpt_slot
op_assign
l_int|0
suffix:semicolon
r_extern
r_int
id|maxPacas
suffix:semicolon
r_extern
r_int
id|iSeries_hpt_loaded
suffix:semicolon
DECL|variable|Hash
id|PTE
op_star
id|Hash
op_assign
l_int|0
suffix:semicolon
macro_line|#ifdef CONFIG_PCI
r_extern
r_int
id|iSeries_Is_IoMmAddress
c_func
(paren
r_int
r_int
id|address
)paren
suffix:semicolon
multiline_comment|/*********************************************************************/
multiline_comment|/* iSeries maps I/O space to device, just leave the address where is.*/
multiline_comment|/*********************************************************************/
DECL|function|ioremap
r_void
op_star
id|ioremap
c_func
(paren
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
(paren
r_void
op_star
)paren
id|addr
suffix:semicolon
)brace
DECL|function|__ioremap
r_void
op_star
id|__ioremap
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
r_int
id|flags
)paren
(brace
r_return
(paren
r_void
op_star
)paren
id|addr
suffix:semicolon
)brace
multiline_comment|/********************************************************************/
multiline_comment|/* iSeries did not remapped the space.                              */
multiline_comment|/********************************************************************/
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
r_return
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_PCI */
multiline_comment|/* &n; * Map as much of memory as will fit into the first entry of each&n; * PPC HPTE Group.  (These are the &quot;bolted&quot; entries which will&n; * never be cast out).  The iSeries Hypervisor has already mapped&n; * the first 32 MB (specified in LparMap.h).  Here we map as&n; * much more as we can.&n; */
DECL|function|MMU_init_hw
r_void
id|__init
id|MMU_init_hw
c_func
(paren
r_void
)paren
(brace
id|PTE
id|hpte
suffix:semicolon
id|u64
op_star
id|hpte0Ptr
comma
op_star
id|hpte1Ptr
suffix:semicolon
id|u32
id|HptSizeGroups
comma
id|msPages
comma
id|rpn
comma
id|vsid
comma
id|ea
suffix:semicolon
id|u64
id|rtnIndex
suffix:semicolon
id|u32
id|hpteIndex
suffix:semicolon
id|u32
id|group
suffix:semicolon
r_int
r_int
id|numAdded
suffix:semicolon
r_if
c_cond
(paren
id|ppc_md.progress
)paren
id|ppc_md
dot
id|progress
c_func
(paren
l_string|&quot;hash:enter&quot;
comma
l_int|0x105
)paren
suffix:semicolon
id|hpte0Ptr
op_assign
(paren
id|u64
op_star
)paren
op_amp
id|hpte
suffix:semicolon
id|hpte1Ptr
op_assign
id|hpte0Ptr
op_plus
l_int|1
suffix:semicolon
multiline_comment|/* Get the number of Hpt groups */
id|HptSizeGroups
op_assign
(paren
id|u32
)paren
id|HvCallHpt_getHptPages
c_func
(paren
)paren
op_star
l_int|32
suffix:semicolon
id|Hash_mask
op_assign
id|HptSizeGroups
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* Number of pages in memory */
id|msPages
op_assign
id|totalLpChunks
op_lshift
l_int|6
suffix:semicolon
multiline_comment|/* For each virtual page in kernel space, add a hpte if there&n;&t;   isn&squot;t one already in slot 0 of the primary pteg.  */
id|numAdded
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|ea
op_assign
(paren
id|u32
)paren
id|KERNELBASE
suffix:semicolon
id|ea
OL
(paren
id|u32
)paren
id|high_memory
suffix:semicolon
id|ea
op_add_assign
id|PAGE_SIZE
)paren
(brace
id|rpn
op_assign
id|ea
op_rshift
l_int|12
suffix:semicolon
id|vsid
op_assign
(paren
(paren
id|ea
op_rshift
l_int|28
)paren
op_star
l_int|0x111
)paren
suffix:semicolon
id|rtnIndex
op_assign
id|HvCallHpt_findValid
c_func
(paren
op_amp
id|hpte
comma
(paren
id|rpn
op_amp
l_int|0xffff
)paren
op_or
(paren
id|vsid
op_lshift
l_int|16
)paren
)paren
suffix:semicolon
id|hpteIndex
op_assign
(paren
id|u32
)paren
id|rtnIndex
suffix:semicolon
r_if
c_cond
(paren
id|hpte.v
)paren
multiline_comment|/* If valid entry found */
r_continue
suffix:semicolon
multiline_comment|/* Already mapped, nothing to do */
r_if
c_cond
(paren
id|rtnIndex
op_eq
op_complement
l_int|0
)paren
multiline_comment|/* If no free entry found */
id|BUG
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Can&squot;t map this page bolted */
r_if
c_cond
(paren
id|rtnIndex
op_rshift
l_int|63
)paren
multiline_comment|/* If first free slot is secondary */
id|BUG
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Can&squot;t map this page bolted */
r_if
c_cond
(paren
(paren
id|hpteIndex
op_amp
l_int|7
)paren
OG
l_int|2
)paren
multiline_comment|/* Not in first 3 slots  */
id|BUG
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * If returned index is the first in the primary group&n;&t;&t; * then build an hpt entry for this page.  &n;&t;&t; */
op_star
id|hpte0Ptr
op_assign
op_star
id|hpte1Ptr
op_assign
l_int|0
suffix:semicolon
id|hpte.vsid
op_assign
id|vsid
suffix:semicolon
id|hpte.api
op_assign
(paren
id|rpn
op_rshift
l_int|11
)paren
op_amp
l_int|0x1f
suffix:semicolon
id|hpte.h
op_assign
l_int|0
suffix:semicolon
id|hpte.v
op_assign
l_int|1
suffix:semicolon
id|hpte.rpn
op_assign
id|physRpn_to_absRpn
c_func
(paren
id|rpn
)paren
suffix:semicolon
id|hpte.r
op_assign
l_int|1
suffix:semicolon
id|hpte.c
op_assign
l_int|1
suffix:semicolon
id|hpte.m
op_assign
l_int|1
suffix:semicolon
id|hpte.w
op_assign
l_int|0
suffix:semicolon
id|hpte.i
op_assign
l_int|0
suffix:semicolon
id|hpte.g
op_assign
l_int|0
suffix:semicolon
id|hpte.pp
op_assign
l_int|0
suffix:semicolon
id|HvCallHpt_addValidate
c_func
(paren
id|hpteIndex
comma
l_int|0
comma
op_amp
id|hpte
)paren
suffix:semicolon
op_increment
id|numAdded
suffix:semicolon
id|group
op_assign
id|rtnIndex
op_amp
l_int|0x07
suffix:semicolon
r_if
c_cond
(paren
id|group
OG
id|iSeries_max_kernel_hpt_slot
)paren
id|iSeries_max_kernel_hpt_slot
op_assign
id|group
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;iSeries_hashinit: added %ld hptes to existing mapping. Max group %x&bslash;n&quot;
comma
id|numAdded
comma
id|iSeries_max_kernel_hpt_slot
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ppc_md.progress
)paren
id|ppc_md
dot
id|progress
c_func
(paren
l_string|&quot;hash:done&quot;
comma
l_int|0x205
)paren
suffix:semicolon
id|iSeries_hpt_loaded
op_assign
l_int|1
suffix:semicolon
id|Hash
op_assign
(paren
r_void
op_star
)paren
l_int|0xFFFFFFFF
suffix:semicolon
)brace
multiline_comment|/*&n; * This is called at the end of handling a user page fault, when the&n; * fault has been handled by updating a PTE in the linux page tables.&n; * We use it to preload an HPTE into the hash table corresponding to&n; * the updated linux PTE.&n; */
DECL|function|update_mmu_cache
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
r_struct
id|mm_struct
op_star
id|mm
suffix:semicolon
id|pmd_t
op_star
id|pmd
suffix:semicolon
id|pte_t
op_star
id|ptep
suffix:semicolon
r_static
r_int
id|nopreload
suffix:semicolon
r_if
c_cond
(paren
id|nopreload
op_logical_or
id|address
op_ge
id|TASK_SIZE
)paren
r_return
suffix:semicolon
id|mm
op_assign
id|vma-&gt;vm_mm
suffix:semicolon
id|pmd
op_assign
id|pmd_offset
c_func
(paren
id|pgd_offset
c_func
(paren
id|mm
comma
id|address
)paren
comma
id|address
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pmd_none
c_func
(paren
op_star
id|pmd
)paren
)paren
(brace
id|ptep
op_assign
id|pte_offset_map
c_func
(paren
id|pmd
comma
id|address
)paren
suffix:semicolon
id|add_hash_page
c_func
(paren
id|mm-&gt;context
comma
id|address
comma
id|ptep
)paren
suffix:semicolon
id|pte_unmap
c_func
(paren
id|ptep
)paren
suffix:semicolon
)brace
)brace
eof
