macro_line|#ifndef _S390X_TLBFLUSH_H
DECL|macro|_S390X_TLBFLUSH_H
mdefine_line|#define _S390X_TLBFLUSH_H
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
r_int
id|dummy
op_assign
l_int|0
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;    la   4,1(%0)&bslash;n&quot;
l_string|&quot;    slr  2,2&bslash;n&quot;
l_string|&quot;    slr  3,3&bslash;n&quot;
l_string|&quot;    csp  2,4&quot;
suffix:colon
suffix:colon
l_string|&quot;a&quot;
(paren
op_amp
id|dummy
)paren
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;2&quot;
comma
l_string|&quot;3&quot;
comma
l_string|&quot;4&quot;
)paren
suffix:semicolon
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
r_if
c_cond
(paren
(paren
id|smp_num_cpus
OG
l_int|1
)paren
op_logical_and
(paren
(paren
id|atomic_read
c_func
(paren
op_amp
id|mm-&gt;mm_count
)paren
op_ne
l_int|1
)paren
op_logical_or
(paren
id|mm-&gt;cpu_vm_mask
op_ne
(paren
l_int|1UL
op_lshift
id|smp_processor_id
c_func
(paren
)paren
)paren
)paren
)paren
)paren
(brace
id|mm-&gt;cpu_vm_mask
op_assign
(paren
l_int|1UL
op_lshift
id|smp_processor_id
c_func
(paren
)paren
)paren
suffix:semicolon
id|global_flush_tlb
c_func
(paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|local_flush_tlb
c_func
(paren
)paren
suffix:semicolon
)brace
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
mdefine_line|#define flush_tlb_kernel_range(start, end) &bslash;&n;&t;__flush_tlb_mm(&amp;init_mm)
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
macro_line|#endif /* _S390X_TLBFLUSH_H */
eof