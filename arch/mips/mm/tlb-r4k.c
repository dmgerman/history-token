multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1996 David S. Miller (dm@engr.sgi.com)&n; * Copyright (C) 1997, 1998, 1999, 2000 Ralf Baechle ralf@gnu.org&n; * Carsten Langgaard, carstenl@mips.com&n; * Copyright (C) 2002 MIPS Technologies, Inc.  All rights reserved.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;asm/cpu.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/mmu_context.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/system.h&gt;
r_extern
r_void
id|except_vec0_generic
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|except_vec0_nevada
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|except_vec0_r4000
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|except_vec0_r4600
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|except_vec1_generic
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|except_vec1_r4k
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* CP0 hazard avoidance. */
DECL|macro|BARRIER
mdefine_line|#define BARRIER __asm__ __volatile__(&quot;.set noreorder&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;&t;&t;     &quot;nop; nop; nop; nop; nop; nop;&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;&t;&t;     &quot;.set reorder&bslash;n&bslash;t&quot;)
DECL|function|local_flush_tlb_all
r_void
id|local_flush_tlb_all
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
r_int
id|old_ctx
suffix:semicolon
r_int
id|entry
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
multiline_comment|/* Save old context and create impossible VPN2 value */
id|old_ctx
op_assign
id|read_c0_entryhi
c_func
(paren
)paren
op_amp
id|ASID_MASK
suffix:semicolon
id|write_c0_entrylo0
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|write_c0_entrylo1
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|BARRIER
suffix:semicolon
id|entry
op_assign
id|read_c0_wired
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Blast &squot;em all away. */
r_while
c_loop
(paren
id|entry
OL
id|current_cpu_data.tlbsize
)paren
(brace
multiline_comment|/*&n;&t;&t; * Make sure all entries differ.  If they&squot;re not different&n;&t;&t; * MIPS32 will take revenge ...&n;&t;&t; */
id|write_c0_entryhi
c_func
(paren
id|CKSEG0
op_plus
(paren
id|entry
op_lshift
(paren
id|PAGE_SHIFT
op_plus
l_int|1
)paren
)paren
)paren
suffix:semicolon
id|write_c0_index
c_func
(paren
id|entry
)paren
suffix:semicolon
id|BARRIER
suffix:semicolon
id|tlb_write_indexed
c_func
(paren
)paren
suffix:semicolon
id|BARRIER
suffix:semicolon
id|entry
op_increment
suffix:semicolon
)brace
id|BARRIER
suffix:semicolon
id|write_c0_entryhi
c_func
(paren
id|old_ctx
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|function|local_flush_tlb_mm
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
r_int
id|cpu
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cpu_context
c_func
(paren
id|cpu
comma
id|mm
)paren
op_ne
l_int|0
)paren
id|drop_mmu_context
c_func
(paren
id|mm
comma
id|cpu
)paren
suffix:semicolon
)brace
DECL|function|local_flush_tlb_range
r_void
id|local_flush_tlb_range
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
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
r_struct
id|mm_struct
op_star
id|mm
op_assign
id|vma-&gt;vm_mm
suffix:semicolon
r_int
id|cpu
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cpu_context
c_func
(paren
id|cpu
comma
id|mm
)paren
op_ne
l_int|0
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
id|size
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|size
op_assign
(paren
id|end
op_minus
id|start
op_plus
(paren
id|PAGE_SIZE
op_minus
l_int|1
)paren
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|size
op_assign
(paren
id|size
op_plus
l_int|1
)paren
op_rshift
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|size
op_le
id|current_cpu_data.tlbsize
op_div
l_int|2
)paren
(brace
r_int
id|oldpid
op_assign
id|read_c0_entryhi
c_func
(paren
)paren
op_amp
id|ASID_MASK
suffix:semicolon
r_int
id|newpid
op_assign
id|cpu_asid
c_func
(paren
id|cpu
comma
id|mm
)paren
suffix:semicolon
id|start
op_and_assign
(paren
id|PAGE_MASK
op_lshift
l_int|1
)paren
suffix:semicolon
id|end
op_add_assign
(paren
(paren
id|PAGE_SIZE
op_lshift
l_int|1
)paren
op_minus
l_int|1
)paren
suffix:semicolon
id|end
op_and_assign
(paren
id|PAGE_MASK
op_lshift
l_int|1
)paren
suffix:semicolon
r_while
c_loop
(paren
id|start
OL
id|end
)paren
(brace
r_int
id|idx
suffix:semicolon
id|write_c0_entryhi
c_func
(paren
id|start
op_or
id|newpid
)paren
suffix:semicolon
id|start
op_add_assign
(paren
id|PAGE_SIZE
op_lshift
l_int|1
)paren
suffix:semicolon
id|BARRIER
suffix:semicolon
id|tlb_probe
c_func
(paren
)paren
suffix:semicolon
id|BARRIER
suffix:semicolon
id|idx
op_assign
id|read_c0_index
c_func
(paren
)paren
suffix:semicolon
id|write_c0_entrylo0
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|write_c0_entrylo1
c_func
(paren
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|idx
OL
l_int|0
)paren
r_continue
suffix:semicolon
multiline_comment|/* Make sure all entries differ. */
id|write_c0_entryhi
c_func
(paren
id|CKSEG0
op_plus
(paren
id|idx
op_lshift
(paren
id|PAGE_SHIFT
op_plus
l_int|1
)paren
)paren
)paren
suffix:semicolon
id|BARRIER
suffix:semicolon
id|tlb_write_indexed
c_func
(paren
)paren
suffix:semicolon
id|BARRIER
suffix:semicolon
)brace
id|write_c0_entryhi
c_func
(paren
id|oldpid
)paren
suffix:semicolon
)brace
r_else
(brace
id|drop_mmu_context
c_func
(paren
id|mm
comma
id|cpu
)paren
suffix:semicolon
)brace
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
)brace
DECL|function|local_flush_tlb_kernel_range
r_void
id|local_flush_tlb_kernel_range
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
r_int
r_int
id|flags
suffix:semicolon
r_int
id|size
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|size
op_assign
(paren
id|end
op_minus
id|start
op_plus
(paren
id|PAGE_SIZE
op_minus
l_int|1
)paren
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|size
op_assign
(paren
id|size
op_plus
l_int|1
)paren
op_rshift
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|size
op_le
id|current_cpu_data.tlbsize
op_div
l_int|2
)paren
(brace
r_int
id|pid
op_assign
id|read_c0_entryhi
c_func
(paren
)paren
suffix:semicolon
id|start
op_and_assign
(paren
id|PAGE_MASK
op_lshift
l_int|1
)paren
suffix:semicolon
id|end
op_add_assign
(paren
(paren
id|PAGE_SIZE
op_lshift
l_int|1
)paren
op_minus
l_int|1
)paren
suffix:semicolon
id|end
op_and_assign
(paren
id|PAGE_MASK
op_lshift
l_int|1
)paren
suffix:semicolon
r_while
c_loop
(paren
id|start
OL
id|end
)paren
(brace
r_int
id|idx
suffix:semicolon
id|write_c0_entryhi
c_func
(paren
id|start
)paren
suffix:semicolon
id|start
op_add_assign
(paren
id|PAGE_SIZE
op_lshift
l_int|1
)paren
suffix:semicolon
id|BARRIER
suffix:semicolon
id|tlb_probe
c_func
(paren
)paren
suffix:semicolon
id|BARRIER
suffix:semicolon
id|idx
op_assign
id|read_c0_index
c_func
(paren
)paren
suffix:semicolon
id|write_c0_entrylo0
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|write_c0_entrylo1
c_func
(paren
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|idx
OL
l_int|0
)paren
r_continue
suffix:semicolon
multiline_comment|/* Make sure all entries differ. */
id|write_c0_entryhi
c_func
(paren
id|CKSEG0
op_plus
(paren
id|idx
op_lshift
(paren
id|PAGE_SHIFT
op_plus
l_int|1
)paren
)paren
)paren
suffix:semicolon
id|BARRIER
suffix:semicolon
id|tlb_write_indexed
c_func
(paren
)paren
suffix:semicolon
id|BARRIER
suffix:semicolon
)brace
id|write_c0_entryhi
c_func
(paren
id|pid
)paren
suffix:semicolon
)brace
r_else
(brace
id|local_flush_tlb_all
c_func
(paren
)paren
suffix:semicolon
)brace
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|function|local_flush_tlb_page
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
id|page
)paren
(brace
r_int
id|cpu
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cpu_context
c_func
(paren
id|cpu
comma
id|vma-&gt;vm_mm
)paren
op_ne
l_int|0
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
id|oldpid
comma
id|newpid
comma
id|idx
suffix:semicolon
id|newpid
op_assign
id|cpu_asid
c_func
(paren
id|cpu
comma
id|vma-&gt;vm_mm
)paren
suffix:semicolon
id|page
op_and_assign
(paren
id|PAGE_MASK
op_lshift
l_int|1
)paren
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|oldpid
op_assign
id|read_c0_entryhi
c_func
(paren
)paren
op_amp
id|ASID_MASK
suffix:semicolon
id|write_c0_entryhi
c_func
(paren
id|page
op_or
id|newpid
)paren
suffix:semicolon
id|BARRIER
suffix:semicolon
id|tlb_probe
c_func
(paren
)paren
suffix:semicolon
id|BARRIER
suffix:semicolon
id|idx
op_assign
id|read_c0_index
c_func
(paren
)paren
suffix:semicolon
id|write_c0_entrylo0
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|write_c0_entrylo1
c_func
(paren
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|idx
OL
l_int|0
)paren
r_goto
id|finish
suffix:semicolon
multiline_comment|/* Make sure all entries differ. */
id|write_c0_entryhi
c_func
(paren
id|CKSEG0
op_plus
(paren
id|idx
op_lshift
(paren
id|PAGE_SHIFT
op_plus
l_int|1
)paren
)paren
)paren
suffix:semicolon
id|BARRIER
suffix:semicolon
id|tlb_write_indexed
c_func
(paren
)paren
suffix:semicolon
id|finish
suffix:colon
id|BARRIER
suffix:semicolon
id|write_c0_entryhi
c_func
(paren
id|oldpid
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * This one is only used for pages with the global bit set so we don&squot;t care&n; * much about the ASID.&n; */
DECL|function|local_flush_tlb_one
r_void
id|local_flush_tlb_one
c_func
(paren
r_int
r_int
id|page
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
id|oldpid
comma
id|idx
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|page
op_and_assign
(paren
id|PAGE_MASK
op_lshift
l_int|1
)paren
suffix:semicolon
id|oldpid
op_assign
id|read_c0_entryhi
c_func
(paren
)paren
op_amp
l_int|0xff
suffix:semicolon
id|write_c0_entryhi
c_func
(paren
id|page
)paren
suffix:semicolon
id|BARRIER
suffix:semicolon
id|tlb_probe
c_func
(paren
)paren
suffix:semicolon
id|BARRIER
suffix:semicolon
id|idx
op_assign
id|read_c0_index
c_func
(paren
)paren
suffix:semicolon
id|write_c0_entrylo0
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|write_c0_entrylo1
c_func
(paren
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|idx
op_ge
l_int|0
)paren
(brace
multiline_comment|/* Make sure all entries differ. */
id|write_c0_entryhi
c_func
(paren
id|CKSEG0
op_plus
(paren
id|idx
op_lshift
(paren
id|PAGE_SHIFT
op_plus
l_int|1
)paren
)paren
)paren
suffix:semicolon
id|BARRIER
suffix:semicolon
id|tlb_write_indexed
c_func
(paren
)paren
suffix:semicolon
)brace
id|BARRIER
suffix:semicolon
id|write_c0_entryhi
c_func
(paren
id|oldpid
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * We will need multiple versions of update_mmu_cache(), one that just&n; * updates the TLB with the new pte(s), and another which also checks&n; * for the R4k &quot;end of page&quot; hardware bug and does the needy.&n; */
DECL|function|__update_tlb
r_void
id|__update_tlb
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
r_int
r_int
id|flags
suffix:semicolon
id|pgd_t
op_star
id|pgdp
suffix:semicolon
id|pmd_t
op_star
id|pmdp
suffix:semicolon
id|pte_t
op_star
id|ptep
suffix:semicolon
r_int
id|idx
comma
id|pid
suffix:semicolon
multiline_comment|/*&n;&t; * Handle debugger faulting in for debugee.&n;&t; */
r_if
c_cond
(paren
id|current-&gt;active_mm
op_ne
id|vma-&gt;vm_mm
)paren
r_return
suffix:semicolon
id|pid
op_assign
id|read_c0_entryhi
c_func
(paren
)paren
op_amp
id|ASID_MASK
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|address
op_and_assign
(paren
id|PAGE_MASK
op_lshift
l_int|1
)paren
suffix:semicolon
id|write_c0_entryhi
c_func
(paren
id|address
op_or
id|pid
)paren
suffix:semicolon
id|pgdp
op_assign
id|pgd_offset
c_func
(paren
id|vma-&gt;vm_mm
comma
id|address
)paren
suffix:semicolon
id|BARRIER
suffix:semicolon
id|tlb_probe
c_func
(paren
)paren
suffix:semicolon
id|BARRIER
suffix:semicolon
id|pmdp
op_assign
id|pmd_offset
c_func
(paren
id|pgdp
comma
id|address
)paren
suffix:semicolon
id|idx
op_assign
id|read_c0_index
c_func
(paren
)paren
suffix:semicolon
id|ptep
op_assign
id|pte_offset_map
c_func
(paren
id|pmdp
comma
id|address
)paren
suffix:semicolon
id|BARRIER
suffix:semicolon
id|write_c0_entrylo0
c_func
(paren
id|pte_val
c_func
(paren
op_star
id|ptep
op_increment
)paren
op_rshift
l_int|6
)paren
suffix:semicolon
id|write_c0_entrylo1
c_func
(paren
id|pte_val
c_func
(paren
op_star
id|ptep
)paren
op_rshift
l_int|6
)paren
suffix:semicolon
id|write_c0_entryhi
c_func
(paren
id|address
op_or
id|pid
)paren
suffix:semicolon
id|BARRIER
suffix:semicolon
r_if
c_cond
(paren
id|idx
OL
l_int|0
)paren
(brace
id|tlb_write_random
c_func
(paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|tlb_write_indexed
c_func
(paren
)paren
suffix:semicolon
)brace
id|BARRIER
suffix:semicolon
id|write_c0_entryhi
c_func
(paren
id|pid
)paren
suffix:semicolon
id|BARRIER
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
macro_line|#if 0
r_static
r_void
id|r4k_update_mmu_cache_hwbug
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
r_int
r_int
id|flags
suffix:semicolon
id|pgd_t
op_star
id|pgdp
suffix:semicolon
id|pmd_t
op_star
id|pmdp
suffix:semicolon
id|pte_t
op_star
id|ptep
suffix:semicolon
r_int
id|idx
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|address
op_and_assign
(paren
id|PAGE_MASK
op_lshift
l_int|1
)paren
suffix:semicolon
id|write_c0_entryhi
c_func
(paren
id|address
op_or
(paren
id|read_c0_entryhi
c_func
(paren
)paren
op_amp
id|ASID_MASK
)paren
)paren
suffix:semicolon
id|pgdp
op_assign
id|pgd_offset
c_func
(paren
id|vma-&gt;vm_mm
comma
id|address
)paren
suffix:semicolon
id|tlb_probe
c_func
(paren
)paren
suffix:semicolon
id|pmdp
op_assign
id|pmd_offset
c_func
(paren
id|pgdp
comma
id|address
)paren
suffix:semicolon
id|idx
op_assign
id|read_c0_index
c_func
(paren
)paren
suffix:semicolon
id|ptep
op_assign
id|pte_offset_map
c_func
(paren
id|pmdp
comma
id|address
)paren
suffix:semicolon
id|write_c0_entrylo0
c_func
(paren
id|pte_val
c_func
(paren
op_star
id|ptep
op_increment
)paren
op_rshift
l_int|6
)paren
suffix:semicolon
id|write_c0_entrylo1
c_func
(paren
id|pte_val
c_func
(paren
op_star
id|ptep
)paren
op_rshift
l_int|6
)paren
suffix:semicolon
id|BARRIER
suffix:semicolon
r_if
c_cond
(paren
id|idx
OL
l_int|0
)paren
id|tlb_write_random
c_func
(paren
)paren
suffix:semicolon
r_else
id|tlb_write_indexed
c_func
(paren
)paren
suffix:semicolon
id|BARRIER
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
macro_line|#endif
DECL|function|add_wired_entry
r_void
id|__init
id|add_wired_entry
c_func
(paren
r_int
r_int
id|entrylo0
comma
r_int
r_int
id|entrylo1
comma
r_int
r_int
id|entryhi
comma
r_int
r_int
id|pagemask
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
r_int
id|wired
suffix:semicolon
r_int
r_int
id|old_pagemask
suffix:semicolon
r_int
r_int
id|old_ctx
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
multiline_comment|/* Save old context and create impossible VPN2 value */
id|old_ctx
op_assign
id|read_c0_entryhi
c_func
(paren
)paren
op_amp
id|ASID_MASK
suffix:semicolon
id|old_pagemask
op_assign
id|read_c0_pagemask
c_func
(paren
)paren
suffix:semicolon
id|wired
op_assign
id|read_c0_wired
c_func
(paren
)paren
suffix:semicolon
id|write_c0_wired
c_func
(paren
id|wired
op_plus
l_int|1
)paren
suffix:semicolon
id|write_c0_index
c_func
(paren
id|wired
)paren
suffix:semicolon
id|BARRIER
suffix:semicolon
id|write_c0_pagemask
c_func
(paren
id|pagemask
)paren
suffix:semicolon
id|write_c0_entryhi
c_func
(paren
id|entryhi
)paren
suffix:semicolon
id|write_c0_entrylo0
c_func
(paren
id|entrylo0
)paren
suffix:semicolon
id|write_c0_entrylo1
c_func
(paren
id|entrylo1
)paren
suffix:semicolon
id|BARRIER
suffix:semicolon
id|tlb_write_indexed
c_func
(paren
)paren
suffix:semicolon
id|BARRIER
suffix:semicolon
id|write_c0_entryhi
c_func
(paren
id|old_ctx
)paren
suffix:semicolon
id|BARRIER
suffix:semicolon
id|write_c0_pagemask
c_func
(paren
id|old_pagemask
)paren
suffix:semicolon
id|local_flush_tlb_all
c_func
(paren
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Used for loading TLB entries before trap_init() has started, when we&n; * don&squot;t actually want to add a wired entry which remains throughout the&n; * lifetime of the system&n; */
DECL|variable|__initdata
r_static
r_int
id|temp_tlb_entry
id|__initdata
suffix:semicolon
DECL|function|add_temporary_entry
id|__init
r_int
id|add_temporary_entry
c_func
(paren
r_int
r_int
id|entrylo0
comma
r_int
r_int
id|entrylo1
comma
r_int
r_int
id|entryhi
comma
r_int
r_int
id|pagemask
)paren
(brace
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
r_int
id|wired
suffix:semicolon
r_int
r_int
id|old_pagemask
suffix:semicolon
r_int
r_int
id|old_ctx
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
multiline_comment|/* Save old context and create impossible VPN2 value */
id|old_ctx
op_assign
id|read_c0_entryhi
c_func
(paren
)paren
op_amp
id|ASID_MASK
suffix:semicolon
id|old_pagemask
op_assign
id|read_c0_pagemask
c_func
(paren
)paren
suffix:semicolon
id|wired
op_assign
id|read_c0_wired
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_decrement
id|temp_tlb_entry
OL
id|wired
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;No TLB space left for add_temporary_entry&bslash;n&quot;
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|ENOSPC
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|write_c0_index
c_func
(paren
id|temp_tlb_entry
)paren
suffix:semicolon
id|BARRIER
suffix:semicolon
id|write_c0_pagemask
c_func
(paren
id|pagemask
)paren
suffix:semicolon
id|write_c0_entryhi
c_func
(paren
id|entryhi
)paren
suffix:semicolon
id|write_c0_entrylo0
c_func
(paren
id|entrylo0
)paren
suffix:semicolon
id|write_c0_entrylo1
c_func
(paren
id|entrylo1
)paren
suffix:semicolon
id|BARRIER
suffix:semicolon
id|tlb_write_indexed
c_func
(paren
)paren
suffix:semicolon
id|BARRIER
suffix:semicolon
id|write_c0_entryhi
c_func
(paren
id|old_ctx
)paren
suffix:semicolon
id|BARRIER
suffix:semicolon
id|write_c0_pagemask
c_func
(paren
id|old_pagemask
)paren
suffix:semicolon
id|out
suffix:colon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|probe_tlb
r_static
r_void
id|__init
id|probe_tlb
c_func
(paren
r_int
r_int
id|config
)paren
(brace
r_struct
id|cpuinfo_mips
op_star
id|c
op_assign
op_amp
id|current_cpu_data
suffix:semicolon
r_int
r_int
id|reg
suffix:semicolon
multiline_comment|/*&n;&t; * If this isn&squot;t a MIPS32 / MIPS64 compliant CPU.  Config 1 register&n;&t; * is not supported, we assume R4k style.  Cpu probing already figured&n;&t; * out the number of tlb entries.&n;&t; */
r_if
c_cond
(paren
(paren
id|c-&gt;processor_id
op_amp
l_int|0xff0000
)paren
op_eq
id|PRID_COMP_LEGACY
)paren
r_return
suffix:semicolon
id|reg
op_assign
id|read_c0_config1
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
(paren
id|config
op_rshift
l_int|7
)paren
op_amp
l_int|3
)paren
)paren
id|panic
c_func
(paren
l_string|&quot;No TLB present&quot;
)paren
suffix:semicolon
id|c-&gt;tlbsize
op_assign
(paren
(paren
id|reg
op_rshift
l_int|25
)paren
op_amp
l_int|0x3f
)paren
op_plus
l_int|1
suffix:semicolon
)brace
DECL|function|tlb_init
r_void
id|__init
id|tlb_init
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|config
op_assign
id|read_c0_config
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * You should never change this register:&n;&t; *   - On R4600 1.7 the tlbp never hits for pages smaller than&n;&t; *     the value in the c0_pagemask register.&n;&t; *   - The entire mm handling assumes the c0_pagemask register to&n;&t; *     be set for 4kb pages.&n;&t; */
id|probe_tlb
c_func
(paren
id|config
)paren
suffix:semicolon
id|write_c0_pagemask
c_func
(paren
id|PM_DEFAULT_MASK
)paren
suffix:semicolon
id|write_c0_wired
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|temp_tlb_entry
op_assign
id|current_cpu_data.tlbsize
op_minus
l_int|1
suffix:semicolon
id|local_flush_tlb_all
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_MIPS32
r_if
c_cond
(paren
id|current_cpu_data.cputype
op_eq
id|CPU_NEVADA
)paren
id|memcpy
c_func
(paren
(paren
r_void
op_star
)paren
id|KSEG0
comma
op_amp
id|except_vec0_nevada
comma
l_int|0x80
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|current_cpu_data.cputype
op_eq
id|CPU_R4600
)paren
id|memcpy
c_func
(paren
(paren
r_void
op_star
)paren
id|KSEG0
comma
op_amp
id|except_vec0_r4600
comma
l_int|0x80
)paren
suffix:semicolon
r_else
id|memcpy
c_func
(paren
(paren
r_void
op_star
)paren
id|KSEG0
comma
op_amp
id|except_vec0_r4000
comma
l_int|0x80
)paren
suffix:semicolon
id|memcpy
c_func
(paren
(paren
r_void
op_star
)paren
(paren
id|KSEG0
op_plus
l_int|0x080
)paren
comma
op_amp
id|except_vec1_generic
comma
l_int|0x80
)paren
suffix:semicolon
id|flush_icache_range
c_func
(paren
id|KSEG0
comma
id|KSEG0
op_plus
l_int|0x100
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_MIPS64
id|memcpy
c_func
(paren
(paren
r_void
op_star
)paren
(paren
id|CKSEG0
op_plus
l_int|0x00
)paren
comma
op_amp
id|except_vec0_generic
comma
l_int|0x80
)paren
suffix:semicolon
id|memcpy
c_func
(paren
(paren
r_void
op_star
)paren
(paren
id|CKSEG0
op_plus
l_int|0x80
)paren
comma
id|except_vec1_r4k
comma
l_int|0x80
)paren
suffix:semicolon
id|flush_icache_range
c_func
(paren
id|CKSEG0
op_plus
l_int|0x80
comma
id|CKSEG0
op_plus
l_int|0x100
)paren
suffix:semicolon
macro_line|#endif
)brace
eof
