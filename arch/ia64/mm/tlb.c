multiline_comment|/*&n; * TLB support routines.&n; *&n; * Copyright (C) 1998-2001, 2003 Hewlett-Packard Co&n; *&t;David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; *&n; * 08/02/00 A. Mallick &lt;asit.k.mallick@intel.com&gt;&n; *&t;&t;Modified RID allocation for SMP&n; *          Goutham Rao &lt;goutham.rao@intel.com&gt;&n; *              IPI based ptc implementation and A-step IPI implementation.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;asm/delay.h&gt;
macro_line|#include &lt;asm/mmu_context.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
macro_line|#include &lt;asm/pal.h&gt;
macro_line|#include &lt;asm/tlbflush.h&gt;
r_static
r_struct
(brace
DECL|member|mask
r_int
r_int
id|mask
suffix:semicolon
multiline_comment|/* mask of supported purge page-sizes */
DECL|member|max_bits
r_int
r_int
id|max_bits
suffix:semicolon
multiline_comment|/* log2() of largest supported purge page-size */
DECL|variable|purge
)brace
id|purge
suffix:semicolon
DECL|variable|ia64_ctx
r_struct
id|ia64_ctx
id|ia64_ctx
op_assign
(brace
dot
id|lock
op_assign
id|SPIN_LOCK_UNLOCKED
comma
dot
id|next
op_assign
l_int|1
comma
dot
id|limit
op_assign
(paren
l_int|1
op_lshift
l_int|15
)paren
op_minus
l_int|1
comma
multiline_comment|/* start out with the safe (architected) limit */
dot
id|max_ctx
op_assign
op_complement
l_int|0U
)brace
suffix:semicolon
id|DEFINE_PER_CPU
c_func
(paren
id|u8
comma
id|ia64_need_tlb_flush
)paren
suffix:semicolon
multiline_comment|/*&n; * Acquire the ia64_ctx.lock before calling this function!&n; */
r_void
DECL|function|wrap_mmu_context
id|wrap_mmu_context
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
(brace
r_int
r_int
id|tsk_context
comma
id|max_ctx
op_assign
id|ia64_ctx.max_ctx
suffix:semicolon
r_struct
id|task_struct
op_star
id|tsk
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|ia64_ctx.next
OG
id|max_ctx
)paren
id|ia64_ctx.next
op_assign
l_int|300
suffix:semicolon
multiline_comment|/* skip daemons */
id|ia64_ctx.limit
op_assign
id|max_ctx
op_plus
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t; * Scan all the task&squot;s mm-&gt;context and set proper safe range&n;&t; */
id|read_lock
c_func
(paren
op_amp
id|tasklist_lock
)paren
suffix:semicolon
id|repeat
suffix:colon
id|for_each_process
c_func
(paren
id|tsk
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|tsk-&gt;mm
)paren
r_continue
suffix:semicolon
id|tsk_context
op_assign
id|tsk-&gt;mm-&gt;context
suffix:semicolon
r_if
c_cond
(paren
id|tsk_context
op_eq
id|ia64_ctx.next
)paren
(brace
r_if
c_cond
(paren
op_increment
id|ia64_ctx.next
op_ge
id|ia64_ctx.limit
)paren
(brace
multiline_comment|/* empty range: reset the range limit and start over */
r_if
c_cond
(paren
id|ia64_ctx.next
OG
id|max_ctx
)paren
id|ia64_ctx.next
op_assign
l_int|300
suffix:semicolon
id|ia64_ctx.limit
op_assign
id|max_ctx
op_plus
l_int|1
suffix:semicolon
r_goto
id|repeat
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
(paren
id|tsk_context
OG
id|ia64_ctx.next
)paren
op_logical_and
(paren
id|tsk_context
OL
id|ia64_ctx.limit
)paren
)paren
id|ia64_ctx.limit
op_assign
id|tsk_context
suffix:semicolon
)brace
id|read_unlock
c_func
(paren
op_amp
id|tasklist_lock
)paren
suffix:semicolon
multiline_comment|/* can&squot;t call flush_tlb_all() here because of race condition with O(1) scheduler [EF] */
(brace
r_int
id|cpu
op_assign
id|get_cpu
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* prevent preemption/migration */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|NR_CPUS
suffix:semicolon
op_increment
id|i
)paren
r_if
c_cond
(paren
id|cpu_online
c_func
(paren
id|i
)paren
op_logical_and
(paren
id|i
op_ne
id|cpu
)paren
)paren
id|per_cpu
c_func
(paren
id|ia64_need_tlb_flush
comma
id|i
)paren
op_assign
l_int|1
suffix:semicolon
id|put_cpu
c_func
(paren
)paren
suffix:semicolon
)brace
id|local_flush_tlb_all
c_func
(paren
)paren
suffix:semicolon
)brace
r_void
DECL|function|ia64_global_tlb_purge
id|ia64_global_tlb_purge
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
id|nbits
)paren
(brace
r_static
id|DEFINE_SPINLOCK
c_func
(paren
id|ptcg_lock
)paren
suffix:semicolon
multiline_comment|/* HW requires global serialization of ptc.ga.  */
id|spin_lock
c_func
(paren
op_amp
id|ptcg_lock
)paren
suffix:semicolon
(brace
r_do
(brace
multiline_comment|/*&n;&t;&t;&t; * Flush ALAT entries also.&n;&t;&t;&t; */
id|ia64_ptcga
c_func
(paren
id|start
comma
(paren
id|nbits
op_lshift
l_int|2
)paren
)paren
suffix:semicolon
id|ia64_srlz_i
c_func
(paren
)paren
suffix:semicolon
id|start
op_add_assign
(paren
l_int|1UL
op_lshift
id|nbits
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|start
OL
id|end
)paren
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|ptcg_lock
)paren
suffix:semicolon
)brace
r_void
DECL|function|local_flush_tlb_all
id|local_flush_tlb_all
(paren
r_void
)paren
(brace
r_int
r_int
id|i
comma
id|j
comma
id|flags
comma
id|count0
comma
id|count1
comma
id|stride0
comma
id|stride1
comma
id|addr
suffix:semicolon
id|addr
op_assign
id|local_cpu_data-&gt;ptce_base
suffix:semicolon
id|count0
op_assign
id|local_cpu_data-&gt;ptce_count
(braket
l_int|0
)braket
suffix:semicolon
id|count1
op_assign
id|local_cpu_data-&gt;ptce_count
(braket
l_int|1
)braket
suffix:semicolon
id|stride0
op_assign
id|local_cpu_data-&gt;ptce_stride
(braket
l_int|0
)braket
suffix:semicolon
id|stride1
op_assign
id|local_cpu_data-&gt;ptce_stride
(braket
l_int|1
)braket
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
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
id|count0
suffix:semicolon
op_increment
id|i
)paren
(brace
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|count1
suffix:semicolon
op_increment
id|j
)paren
(brace
id|ia64_ptce
c_func
(paren
id|addr
)paren
suffix:semicolon
id|addr
op_add_assign
id|stride1
suffix:semicolon
)brace
id|addr
op_add_assign
id|stride0
suffix:semicolon
)brace
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
id|ia64_srlz_i
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* srlz.i implies srlz.d */
)brace
DECL|variable|local_flush_tlb_all
id|EXPORT_SYMBOL
c_func
(paren
id|local_flush_tlb_all
)paren
suffix:semicolon
r_void
DECL|function|flush_tlb_range
id|flush_tlb_range
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
id|size
op_assign
id|end
op_minus
id|start
suffix:semicolon
r_int
r_int
id|nbits
suffix:semicolon
r_if
c_cond
(paren
id|mm
op_ne
id|current-&gt;active_mm
)paren
(brace
multiline_comment|/* this does happen, but perhaps it&squot;s not worth optimizing for? */
macro_line|#ifdef CONFIG_SMP
id|flush_tlb_all
c_func
(paren
)paren
suffix:semicolon
macro_line|#else
id|mm-&gt;context
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
r_return
suffix:semicolon
)brace
id|nbits
op_assign
id|ia64_fls
c_func
(paren
id|size
op_plus
l_int|0xfff
)paren
suffix:semicolon
r_while
c_loop
(paren
id|unlikely
(paren
(paren
(paren
l_int|1UL
op_lshift
id|nbits
)paren
op_amp
id|purge.mask
)paren
op_eq
l_int|0
)paren
op_logical_and
(paren
id|nbits
OL
id|purge.max_bits
)paren
)paren
op_increment
id|nbits
suffix:semicolon
r_if
c_cond
(paren
id|nbits
OG
id|purge.max_bits
)paren
id|nbits
op_assign
id|purge.max_bits
suffix:semicolon
id|start
op_and_assign
op_complement
(paren
(paren
l_int|1UL
op_lshift
id|nbits
)paren
op_minus
l_int|1
)paren
suffix:semicolon
macro_line|# ifdef CONFIG_SMP
id|platform_global_tlb_purge
c_func
(paren
id|start
comma
id|end
comma
id|nbits
)paren
suffix:semicolon
macro_line|# else
r_do
(brace
id|ia64_ptcl
c_func
(paren
id|start
comma
(paren
id|nbits
op_lshift
l_int|2
)paren
)paren
suffix:semicolon
id|start
op_add_assign
(paren
l_int|1UL
op_lshift
id|nbits
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|start
OL
id|end
)paren
suffix:semicolon
macro_line|# endif
id|ia64_srlz_i
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* srlz.i implies srlz.d */
)brace
DECL|variable|flush_tlb_range
id|EXPORT_SYMBOL
c_func
(paren
id|flush_tlb_range
)paren
suffix:semicolon
r_void
id|__devinit
DECL|function|ia64_tlb_init
id|ia64_tlb_init
(paren
r_void
)paren
(brace
id|ia64_ptce_info_t
id|ptce_info
suffix:semicolon
r_int
r_int
id|tr_pgbits
suffix:semicolon
r_int
id|status
suffix:semicolon
r_if
c_cond
(paren
(paren
id|status
op_assign
id|ia64_pal_vm_page_size
c_func
(paren
op_amp
id|tr_pgbits
comma
op_amp
id|purge.mask
)paren
)paren
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;PAL_VM_PAGE_SIZE failed with status=%ld;&quot;
l_string|&quot;defaulting to architected purge page-sizes.&bslash;n&quot;
comma
id|status
)paren
suffix:semicolon
id|purge.mask
op_assign
l_int|0x115557000UL
suffix:semicolon
)brace
id|purge.max_bits
op_assign
id|ia64_fls
c_func
(paren
id|purge.mask
)paren
suffix:semicolon
id|ia64_get_ptce
c_func
(paren
op_amp
id|ptce_info
)paren
suffix:semicolon
id|local_cpu_data-&gt;ptce_base
op_assign
id|ptce_info.base
suffix:semicolon
id|local_cpu_data-&gt;ptce_count
(braket
l_int|0
)braket
op_assign
id|ptce_info.count
(braket
l_int|0
)braket
suffix:semicolon
id|local_cpu_data-&gt;ptce_count
(braket
l_int|1
)braket
op_assign
id|ptce_info.count
(braket
l_int|1
)braket
suffix:semicolon
id|local_cpu_data-&gt;ptce_stride
(braket
l_int|0
)braket
op_assign
id|ptce_info.stride
(braket
l_int|0
)braket
suffix:semicolon
id|local_cpu_data-&gt;ptce_stride
(braket
l_int|1
)braket
op_assign
id|ptce_info.stride
(braket
l_int|1
)braket
suffix:semicolon
id|local_flush_tlb_all
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* nuke left overs from bootstrapping... */
)brace
eof
