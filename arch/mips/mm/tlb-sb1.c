multiline_comment|/*&n; * Copyright (C) 1996 David S. Miller (dm@engr.sgi.com)&n; * Copyright (C) 1997, 2001 Ralf Baechle (ralf@gnu.org)&n; * Copyright (C) 2000, 2001, 2002, 2003 Broadcom Corporation&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version 2&n; * of the License, or (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/mmu_context.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/cpu.h&gt;
r_extern
r_void
id|build_tlb_refill_handler
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|UNIQUE_ENTRYHI
mdefine_line|#define UNIQUE_ENTRYHI(idx) (KSEG0 + ((idx) &lt;&lt; (PAGE_SHIFT + 1)))
multiline_comment|/* Dump the current entry* and pagemask registers */
DECL|function|dump_cur_tlb_regs
r_static
r_inline
r_void
id|dump_cur_tlb_regs
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|entryhihi
comma
id|entryhilo
comma
id|entrylo0hi
comma
id|entrylo0lo
comma
id|entrylo1hi
suffix:semicolon
r_int
r_int
id|entrylo1lo
comma
id|pagemask
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;.set push             &bslash;n&quot;
l_string|&quot;.set noreorder        &bslash;n&quot;
l_string|&quot;.set mips64           &bslash;n&quot;
l_string|&quot;.set noat             &bslash;n&quot;
l_string|&quot;     tlbr             &bslash;n&quot;
l_string|&quot;     dmfc0  $1, $10   &bslash;n&quot;
l_string|&quot;     dsrl32 %0, $1, 0 &bslash;n&quot;
l_string|&quot;     sll    %1, $1, 0 &bslash;n&quot;
l_string|&quot;     dmfc0  $1, $2    &bslash;n&quot;
l_string|&quot;     dsrl32 %2, $1, 0 &bslash;n&quot;
l_string|&quot;     sll    %3, $1, 0 &bslash;n&quot;
l_string|&quot;     dmfc0  $1, $3    &bslash;n&quot;
l_string|&quot;     dsrl32 %4, $1, 0 &bslash;n&quot;
l_string|&quot;     sll    %5, $1, 0 &bslash;n&quot;
l_string|&quot;     mfc0   %6, $5    &bslash;n&quot;
l_string|&quot;.set pop              &bslash;n&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|entryhihi
)paren
comma
l_string|&quot;=r&quot;
(paren
id|entryhilo
)paren
comma
l_string|&quot;=r&quot;
(paren
id|entrylo0hi
)paren
comma
l_string|&quot;=r&quot;
(paren
id|entrylo0lo
)paren
comma
l_string|&quot;=r&quot;
(paren
id|entrylo1hi
)paren
comma
l_string|&quot;=r&quot;
(paren
id|entrylo1lo
)paren
comma
l_string|&quot;=r&quot;
(paren
id|pagemask
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%08X%08X %08X%08X %08X%08X %08X&quot;
comma
id|entryhihi
comma
id|entryhilo
comma
id|entrylo0hi
comma
id|entrylo0lo
comma
id|entrylo1hi
comma
id|entrylo1lo
comma
id|pagemask
)paren
suffix:semicolon
)brace
DECL|function|sb1_dump_tlb
r_void
id|sb1_dump_tlb
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|old_ctx
suffix:semicolon
r_int
r_int
id|flags
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
id|old_ctx
op_assign
id|read_c0_entryhi
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Current TLB registers state:&bslash;n&quot;
l_string|&quot;      EntryHi       EntryLo0          EntryLo1     PageMask  Index&bslash;n&quot;
l_string|&quot;--------------------------------------------------------------------&bslash;n&quot;
)paren
suffix:semicolon
id|dump_cur_tlb_regs
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; %08X&bslash;n&quot;
comma
id|read_c0_index
c_func
(paren
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;n&bslash;nFull TLB Dump:&bslash;n&quot;
l_string|&quot;Idx      EntryHi       EntryLo0          EntryLo1     PageMask&bslash;n&quot;
l_string|&quot;--------------------------------------------------------------&bslash;n&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|entry
op_assign
l_int|0
suffix:semicolon
id|entry
OL
id|current_cpu_data.tlbsize
suffix:semicolon
id|entry
op_increment
)paren
(brace
id|write_c0_index
c_func
(paren
id|entry
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;n%02i &quot;
comma
id|entry
)paren
suffix:semicolon
id|dump_cur_tlb_regs
c_func
(paren
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
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
id|entry
op_assign
id|read_c0_wired
c_func
(paren
)paren
suffix:semicolon
r_while
c_loop
(paren
id|entry
OL
id|current_cpu_data.tlbsize
)paren
(brace
id|write_c0_entryhi
c_func
(paren
id|UNIQUE_ENTRYHI
c_func
(paren
id|entry
)paren
)paren
suffix:semicolon
id|write_c0_index
c_func
(paren
id|entry
)paren
suffix:semicolon
id|tlb_write_indexed
c_func
(paren
)paren
suffix:semicolon
id|entry
op_increment
suffix:semicolon
)brace
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
multiline_comment|/*&n; * Use a bogus region of memory (starting at 0) to sanitize the TLB&squot;s.&n; * Use increments of the maximum page size (16MB), and check for duplicate&n; * entries before doing a given write.  Then, when we&squot;re safe from collisions&n; * with the firmware, go back and give all the entries invalid addresses with&n; * the normal flush routine.  Wired entries will be killed as well!&n; */
DECL|function|sb1_sanitize_tlb
r_static
r_void
id|__init
id|sb1_sanitize_tlb
c_func
(paren
r_void
)paren
(brace
r_int
id|entry
suffix:semicolon
r_int
id|addr
op_assign
l_int|0
suffix:semicolon
r_int
id|inc
op_assign
l_int|1
op_lshift
l_int|24
suffix:semicolon
multiline_comment|/* 16MB */
multiline_comment|/* Save old context and create impossible VPN2 value */
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
r_for
c_loop
(paren
id|entry
op_assign
l_int|0
suffix:semicolon
id|entry
OL
id|current_cpu_data.tlbsize
suffix:semicolon
id|entry
op_increment
)paren
(brace
r_do
(brace
id|addr
op_add_assign
id|inc
suffix:semicolon
id|write_c0_entryhi
c_func
(paren
id|addr
)paren
suffix:semicolon
id|tlb_probe
c_func
(paren
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
r_int
)paren
(paren
id|read_c0_index
c_func
(paren
)paren
)paren
op_ge
l_int|0
)paren
suffix:semicolon
id|write_c0_index
c_func
(paren
id|entry
)paren
suffix:semicolon
id|tlb_write_indexed
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Now that we know we&squot;re safe from collisions, we can safely flush&n;&t;   the TLB with the &quot;normal&quot; routine. */
id|local_flush_tlb_all
c_func
(paren
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
r_int
id|flags
suffix:semicolon
r_int
id|cpu
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
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
id|size
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
(paren
id|current_cpu_data.tlbsize
op_div
l_int|2
)paren
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
id|tlb_probe
c_func
(paren
)paren
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
id|write_c0_entryhi
c_func
(paren
id|UNIQUE_ENTRYHI
c_func
(paren
id|idx
)paren
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
id|tlb_write_indexed
c_func
(paren
)paren
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
)brace
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
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
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|size
op_le
(paren
id|current_cpu_data.tlbsize
op_div
l_int|2
)paren
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
id|tlb_probe
c_func
(paren
)paren
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
id|write_c0_entryhi
c_func
(paren
id|UNIQUE_ENTRYHI
c_func
(paren
id|idx
)paren
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
id|tlb_write_indexed
c_func
(paren
)paren
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
r_int
id|flags
suffix:semicolon
r_int
id|cpu
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
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
id|tlb_probe
c_func
(paren
)paren
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
id|UNIQUE_ENTRYHI
c_func
(paren
id|idx
)paren
)paren
suffix:semicolon
id|tlb_write_indexed
c_func
(paren
)paren
suffix:semicolon
id|finish
suffix:colon
id|write_c0_entryhi
c_func
(paren
id|oldpid
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
multiline_comment|/*&n; * Remove one kernel space TLB entry.  This entry is assumed to be marked&n; * global so we don&squot;t do the ASID thing.&n; */
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
id|ASID_MASK
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|write_c0_entryhi
c_func
(paren
id|page
)paren
suffix:semicolon
id|tlb_probe
c_func
(paren
)paren
suffix:semicolon
id|idx
op_assign
id|read_c0_index
c_func
(paren
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
id|UNIQUE_ENTRYHI
c_func
(paren
id|idx
)paren
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
id|tlb_write_indexed
c_func
(paren
)paren
suffix:semicolon
)brace
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
multiline_comment|/* All entries common to a mm share an asid.  To effectively flush&n;   these entries, we just bump the asid. */
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
suffix:semicolon
id|preempt_disable
c_func
(paren
)paren
suffix:semicolon
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
id|drop_mmu_context
c_func
(paren
id|mm
comma
id|cpu
)paren
suffix:semicolon
)brace
id|preempt_enable
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Stolen from mips32 routines */
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
id|local_irq_save
c_func
(paren
id|flags
)paren
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
id|pid
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
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
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
id|old_ctx
op_assign
id|read_c0_entryhi
c_func
(paren
)paren
op_amp
l_int|0xff
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
id|tlb_write_indexed
c_func
(paren
)paren
suffix:semicolon
id|write_c0_entryhi
c_func
(paren
id|old_ctx
)paren
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
multiline_comment|/*&n; * This is called from loadmmu.c.  We have to set up all the&n; * memory management function pointers, as well as initialize&n; * the caches and tlbs&n; */
DECL|function|tlb_init
r_void
id|tlb_init
c_func
(paren
r_void
)paren
(brace
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
multiline_comment|/*&n;&t; * We don&squot;t know what state the firmware left the TLB&squot;s in, so this is&n;&t; * the ultra-conservative way to flush the TLB&squot;s and avoid machine&n;&t; * check exceptions due to duplicate TLB entries&n;&t; */
id|sb1_sanitize_tlb
c_func
(paren
)paren
suffix:semicolon
id|build_tlb_refill_handler
c_func
(paren
)paren
suffix:semicolon
)brace
eof
