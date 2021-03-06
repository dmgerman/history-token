multiline_comment|/*&n; * r2300.c: R2000 and R3000 specific mmu/cache code.&n; *&n; * Copyright (C) 1996 David S. Miller (dm@engr.sgi.com)&n; *&n; * with a lot of changes to make this thing work for R3000s&n; * Tx39XX R4k style caches added. HK&n; * Copyright (C) 1998, 1999, 2000 Harald Koerfgen&n; * Copyright (C) 1998 Gleb Raiko &amp; Vladimir Roganov&n; * Copyright (C) 2002  Ralf Baechle&n; * Copyright (C) 2002  Maciej W. Rozycki&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/mmu_context.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/isadep.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/cpu.h&gt;
DECL|macro|DEBUG_TLB
macro_line|#undef DEBUG_TLB
r_extern
r_void
id|build_tlb_refill_handler
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* CP0 hazard avoidance. */
DECL|macro|BARRIER
mdefine_line|#define BARRIER&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&bslash;&n;&t;&t;&quot;.set&t;push&bslash;n&bslash;t&quot;&t;&bslash;&n;&t;&t;&quot;.set&t;noreorder&bslash;n&bslash;t&quot;&t;&bslash;&n;&t;&t;&quot;nop&bslash;n&bslash;t&quot;&t;&t;&bslash;&n;&t;&t;&quot;.set&t;pop&bslash;n&bslash;t&quot;)
DECL|variable|r3k_have_wired_reg
r_int
id|r3k_have_wired_reg
suffix:semicolon
multiline_comment|/* should be in cpu_data? */
multiline_comment|/* TLB operations. */
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
macro_line|#ifdef DEBUG_TLB
id|printk
c_func
(paren
l_string|&quot;[tlball]&quot;
)paren
suffix:semicolon
macro_line|#endif
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
id|ASID_MASK
suffix:semicolon
id|write_c0_entrylo0
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|entry
op_assign
id|r3k_have_wired_reg
ques
c_cond
id|read_c0_wired
c_func
(paren
)paren
suffix:colon
l_int|8
suffix:semicolon
r_for
c_loop
(paren
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
op_lshift
l_int|8
)paren
suffix:semicolon
id|write_c0_entryhi
c_func
(paren
(paren
id|entry
op_or
l_int|0x80000
)paren
op_lshift
l_int|12
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
(brace
macro_line|#ifdef DEBUG_TLB
id|printk
c_func
(paren
l_string|&quot;[tlbmm&lt;%lu&gt;]&quot;
comma
(paren
r_int
r_int
)paren
id|cpu_context
c_func
(paren
id|cpu
comma
id|mm
)paren
)paren
suffix:semicolon
macro_line|#endif
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
macro_line|#ifdef DEBUG_TLB
id|printk
c_func
(paren
l_string|&quot;[tlbrange&lt;%lu,0x%08lx,0x%08lx&gt;]&quot;
comma
id|cpu_context
c_func
(paren
id|cpu
comma
id|mm
)paren
op_amp
id|ASID_MASK
comma
id|start
comma
id|end
)paren
suffix:semicolon
macro_line|#endif
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
r_if
c_cond
(paren
id|size
op_le
id|current_cpu_data.tlbsize
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
id|cpu_context
c_func
(paren
id|cpu
comma
id|mm
)paren
op_amp
id|ASID_MASK
suffix:semicolon
id|start
op_and_assign
id|PAGE_MASK
suffix:semicolon
id|end
op_add_assign
id|PAGE_SIZE
op_minus
l_int|1
suffix:semicolon
id|end
op_and_assign
id|PAGE_MASK
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
id|PAGE_SIZE
suffix:semicolon
multiline_comment|/* BARRIER */
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
id|write_c0_entryhi
c_func
(paren
id|KSEG0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|idx
OL
l_int|0
)paren
multiline_comment|/* BARRIER */
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
macro_line|#ifdef DEBUG_TLB
id|printk
c_func
(paren
l_string|&quot;[tlbrange&lt;%lu,0x%08lx,0x%08lx&gt;]&quot;
comma
id|start
comma
id|end
)paren
suffix:semicolon
macro_line|#endif
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
r_if
c_cond
(paren
id|size
op_le
id|current_cpu_data.tlbsize
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
id|PAGE_MASK
suffix:semicolon
id|end
op_add_assign
id|PAGE_SIZE
op_minus
l_int|1
suffix:semicolon
id|end
op_and_assign
id|PAGE_MASK
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
id|PAGE_SIZE
suffix:semicolon
multiline_comment|/* BARRIER */
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
id|write_c0_entryhi
c_func
(paren
id|KSEG0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|idx
OL
l_int|0
)paren
multiline_comment|/* BARRIER */
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
op_logical_neg
id|vma
op_logical_or
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
macro_line|#ifdef DEBUG_TLB
id|printk
c_func
(paren
l_string|&quot;[tlbpage&lt;%lu,0x%08lx&gt;]&quot;
comma
id|cpu_context
c_func
(paren
id|cpu
comma
id|vma-&gt;vm_mm
)paren
comma
id|page
)paren
suffix:semicolon
macro_line|#endif
id|newpid
op_assign
id|cpu_context
c_func
(paren
id|cpu
comma
id|vma-&gt;vm_mm
)paren
op_amp
id|ASID_MASK
suffix:semicolon
id|page
op_and_assign
id|PAGE_MASK
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
id|write_c0_entryhi
c_func
(paren
id|KSEG0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|idx
OL
l_int|0
)paren
multiline_comment|/* BARRIER */
r_goto
id|finish
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
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
)brace
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
macro_line|#ifdef DEBUG_TLB
r_if
c_cond
(paren
(paren
id|pid
op_ne
(paren
id|cpu_context
c_func
(paren
id|cpu
comma
id|vma-&gt;vm_mm
)paren
op_amp
id|ASID_MASK
)paren
)paren
op_logical_or
(paren
id|cpu_context
c_func
(paren
id|cpu
comma
id|vma-&gt;vm_mm
)paren
op_eq
l_int|0
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;update_mmu_cache: Wheee, bogus tlbpid mmpid=%lu tlbpid=%d&bslash;n&quot;
comma
(paren
id|cpu_context
c_func
(paren
id|cpu
comma
id|vma-&gt;vm_mm
)paren
)paren
comma
id|pid
)paren
suffix:semicolon
)brace
macro_line|#endif
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|address
op_and_assign
id|PAGE_MASK
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
id|pte_val
c_func
(paren
id|pte
)paren
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
r_if
c_cond
(paren
id|idx
OL
l_int|0
)paren
(brace
multiline_comment|/* BARRIER */
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
id|write_c0_entryhi
c_func
(paren
id|pid
)paren
suffix:semicolon
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
id|old_ctx
suffix:semicolon
r_static
r_int
r_int
id|wired
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|r3k_have_wired_reg
)paren
(brace
multiline_comment|/* TX39XX */
r_int
r_int
id|old_pagemask
suffix:semicolon
r_int
r_int
id|w
suffix:semicolon
macro_line|#ifdef DEBUG_TLB
id|printk
c_func
(paren
l_string|&quot;[tlbwired&lt;entry lo0 %8x, hi %8x&bslash;n, pagemask %8x&gt;]&bslash;n&quot;
comma
id|entrylo0
comma
id|entryhi
comma
id|pagemask
)paren
suffix:semicolon
macro_line|#endif
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
id|w
op_assign
id|read_c0_wired
c_func
(paren
)paren
suffix:semicolon
id|write_c0_wired
c_func
(paren
id|w
op_plus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|read_c0_wired
c_func
(paren
)paren
op_ne
id|w
op_plus
l_int|1
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;[tlbwired] No WIRED reg?&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|write_c0_index
c_func
(paren
id|w
op_lshift
l_int|8
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
id|BARRIER
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
r_else
r_if
c_cond
(paren
id|wired
OL
l_int|8
)paren
(brace
macro_line|#ifdef DEBUG_TLB
id|printk
c_func
(paren
l_string|&quot;[tlbwired&lt;entry lo0 %8x, hi %8x&bslash;n&gt;]&bslash;n&quot;
comma
id|entrylo0
comma
id|entryhi
)paren
suffix:semicolon
macro_line|#endif
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
id|ASID_MASK
suffix:semicolon
id|write_c0_entrylo0
c_func
(paren
id|entrylo0
)paren
suffix:semicolon
id|write_c0_entryhi
c_func
(paren
id|entryhi
)paren
suffix:semicolon
id|write_c0_index
c_func
(paren
id|wired
)paren
suffix:semicolon
id|wired
op_increment
suffix:semicolon
multiline_comment|/* BARRIER */
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
id|local_flush_tlb_all
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
