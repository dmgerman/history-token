macro_line|#ifndef _S390_TLBFLUSH_H
DECL|macro|_S390_TLBFLUSH_H
mdefine_line|#define _S390_TLBFLUSH_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
multiline_comment|/*&n; * TLB flushing:&n; *&n; *  - flush_tlb() flushes the current mm struct TLBs&n; *  - flush_tlb_all() flushes all processes TLBs &n; *  - flush_tlb_mm(mm) flushes the specified mm context TLB&squot;s&n; *  - flush_tlb_page(vma, vmaddr) flushes one page&n; *  - flush_tlb_range(vma, start, end) flushes a range of pages&n; *  - flush_tlb_kernel_range(start, end) flushes a range of kernel pages&n; *  - flush_tlb_pgtables(mm, start, end) flushes a range of page tables&n; */
multiline_comment|/*&n; * S/390 has three ways of flushing TLBs&n; * &squot;ptlb&squot; does a flush of the local processor&n; * &squot;csp&squot; flushes the TLBs on all PUs of a SMP&n; * &squot;ipte&squot; invalidates a pte in a page table and flushes that out of&n; * the TLBs of all PUs of a SMP&n; */
DECL|macro|local_flush_tlb
mdefine_line|#define local_flush_tlb() &bslash;&n;do {  __asm__ __volatile__(&quot;ptlb&quot;: : :&quot;memory&quot;); } while (0)
macro_line|#ifndef CONFIG_SMP
multiline_comment|/*&n; * We always need to flush, since s390 does not flush tlb&n; * on each context switch&n; */
DECL|function|flush_tlb
r_static
r_inline
r_void
id|flush_tlb
c_func
(paren
r_void
)paren
(brace
id|local_flush_tlb
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|flush_tlb_all
r_static
r_inline
r_void
id|flush_tlb_all
c_func
(paren
r_void
)paren
(brace
id|local_flush_tlb
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|flush_tlb_mm
r_static
r_inline
r_void
id|flush_tlb_mm
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
(brace
id|local_flush_tlb
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|flush_tlb_page
r_static
r_inline
r_void
id|flush_tlb_page
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|addr
)paren
(brace
id|local_flush_tlb
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|flush_tlb_range
r_static
r_inline
r_void
id|flush_tlb_range
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
id|local_flush_tlb
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|macro|flush_tlb_kernel_range
mdefine_line|#define flush_tlb_kernel_range(start, end) &bslash;&n;&t;local_flush_tlb();
macro_line|#else
macro_line|#include &lt;asm/smp.h&gt;
r_extern
r_void
id|smp_ptlb_all
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|function|global_flush_tlb
r_static
r_inline
r_void
id|global_flush_tlb
c_func
(paren
r_void
)paren
(brace
macro_line|#ifndef __s390x__
r_if
c_cond
(paren
op_logical_neg
id|MACHINE_HAS_CSP
)paren
(brace
id|smp_ptlb_all
c_func
(paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
macro_line|#endif /* __s390x__ */
(brace
r_register
r_int
r_int
id|addr
id|asm
c_func
(paren
l_string|&quot;4&quot;
)paren
suffix:semicolon
r_int
id|dummy
suffix:semicolon
id|dummy
op_assign
l_int|0
suffix:semicolon
id|addr
op_assign
(paren
(paren
r_int
r_int
)paren
op_amp
id|dummy
)paren
op_plus
l_int|1
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;    slr  2,2&bslash;n&quot;
l_string|&quot;    slr  3,3&bslash;n&quot;
l_string|&quot;    csp  2,%0&quot;
suffix:colon
suffix:colon
l_string|&quot;a&quot;
(paren
id|addr
)paren
comma
l_string|&quot;m&quot;
(paren
id|dummy
)paren
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;2&quot;
comma
l_string|&quot;3&quot;
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * We only have to do global flush of tlb if process run since last&n; * flush on any other pu than current. &n; * If we have threads (mm-&gt;count &gt; 1) we always do a global flush, &n; * since the process runs on more than one processor at the same time.&n; */
DECL|function|__flush_tlb_mm
r_static
r_inline
r_void
id|__flush_tlb_mm
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
(brace
id|cpumask_t
id|local_cpumask
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|cpus_empty
c_func
(paren
id|mm-&gt;cpu_vm_mask
)paren
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|MACHINE_HAS_IDTE
)paren
(brace
id|asm
r_volatile
(paren
l_string|&quot;.insn rrf,0xb98e0000,0,%0,%1,0&quot;
suffix:colon
suffix:colon
l_string|&quot;a&quot;
(paren
l_int|2048
)paren
comma
l_string|&quot;a&quot;
(paren
id|__pa
c_func
(paren
id|mm-&gt;pgd
)paren
op_amp
id|PAGE_MASK
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|preempt_disable
c_func
(paren
)paren
suffix:semicolon
id|local_cpumask
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
id|cpus_equal
c_func
(paren
id|mm-&gt;cpu_vm_mask
comma
id|local_cpumask
)paren
)paren
id|local_flush_tlb
c_func
(paren
)paren
suffix:semicolon
r_else
id|global_flush_tlb
c_func
(paren
)paren
suffix:semicolon
id|preempt_enable
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|flush_tlb
r_static
r_inline
r_void
id|flush_tlb
c_func
(paren
r_void
)paren
(brace
id|__flush_tlb_mm
c_func
(paren
id|current-&gt;mm
)paren
suffix:semicolon
)brace
DECL|function|flush_tlb_all
r_static
r_inline
r_void
id|flush_tlb_all
c_func
(paren
r_void
)paren
(brace
id|global_flush_tlb
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|flush_tlb_mm
r_static
r_inline
r_void
id|flush_tlb_mm
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
(brace
id|__flush_tlb_mm
c_func
(paren
id|mm
)paren
suffix:semicolon
)brace
DECL|function|flush_tlb_page
r_static
r_inline
r_void
id|flush_tlb_page
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|addr
)paren
(brace
id|__flush_tlb_mm
c_func
(paren
id|vma-&gt;vm_mm
)paren
suffix:semicolon
)brace
DECL|function|flush_tlb_range
r_static
r_inline
r_void
id|flush_tlb_range
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
id|__flush_tlb_mm
c_func
(paren
id|vma-&gt;vm_mm
)paren
suffix:semicolon
)brace
DECL|macro|flush_tlb_kernel_range
mdefine_line|#define flush_tlb_kernel_range(start, end) global_flush_tlb()
macro_line|#endif
DECL|function|flush_tlb_pgtables
r_static
r_inline
r_void
id|flush_tlb_pgtables
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
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
multiline_comment|/* S/390 does not keep any page table caches in TLB */
)brace
macro_line|#endif /* _S390_TLBFLUSH_H */
eof
