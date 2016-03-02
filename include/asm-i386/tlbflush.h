macro_line|#ifndef _I386_TLBFLUSH_H
DECL|macro|_I386_TLBFLUSH_H
mdefine_line|#define _I386_TLBFLUSH_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
DECL|macro|__flush_tlb
mdefine_line|#define __flush_tlb()&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;unsigned int tmpreg;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&quot;movl %%cr3, %0;              &bslash;n&quot;&t;&t;&bslash;&n;&t;&t;&t;&quot;movl %0, %%cr3;  # flush TLB &bslash;n&quot;&t;&t;&bslash;&n;&t;&t;&t;: &quot;=r&quot; (tmpreg)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;:: &quot;memory&quot;);&t;&t;&t;&t;&t;&bslash;&n;&t;} while (0)
multiline_comment|/*&n; * Global pages have to be flushed a bit differently. Not a real&n; * performance problem because this does not happen often.&n; */
DECL|macro|__flush_tlb_global
mdefine_line|#define __flush_tlb_global()&t;&t;&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;unsigned int tmpreg;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&quot;movl %1, %%cr4;  # turn off PGE     &bslash;n&quot;&t;&bslash;&n;&t;&t;&t;&quot;movl %%cr3, %0;                     &bslash;n&quot;&t;&bslash;&n;&t;&t;&t;&quot;movl %0, %%cr3;  # flush TLB        &bslash;n&quot;&t;&bslash;&n;&t;&t;&t;&quot;movl %2, %%cr4;  # turn PGE back on &bslash;n&quot;&t;&bslash;&n;&t;&t;&t;: &quot;=&amp;r&quot; (tmpreg)&t;&t;&t;&t;&bslash;&n;&t;&t;&t;: &quot;r&quot; (mmu_cr4_features &amp; ~X86_CR4_PGE),&t;&bslash;&n;&t;&t;&t;  &quot;r&quot; (mmu_cr4_features)&t;&t;&t;&bslash;&n;&t;&t;&t;: &quot;memory&quot;);&t;&t;&t;&t;&t;&bslash;&n;&t;} while (0)
r_extern
r_int
r_int
id|pgkern_mask
suffix:semicolon
DECL|macro|__flush_tlb_all
macro_line|# define __flush_tlb_all()&t;&t;&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;if (cpu_has_pge)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;__flush_tlb_global();&t;&t;&t;&t;&bslash;&n;&t;&t;else&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;__flush_tlb();&t;&t;&t;&t;&t;&bslash;&n;&t;} while (0)
DECL|macro|cpu_has_invlpg
mdefine_line|#define cpu_has_invlpg&t;(boot_cpu_data.x86 &gt; 3)
DECL|macro|__flush_tlb_single
mdefine_line|#define __flush_tlb_single(addr) &bslash;&n;&t;__asm__ __volatile__(&quot;invlpg %0&quot;: :&quot;m&quot; (*(char *) addr))
macro_line|#ifdef CONFIG_X86_INVLPG
DECL|macro|__flush_tlb_one
macro_line|# define __flush_tlb_one(addr) __flush_tlb_single(addr)
macro_line|#else
DECL|macro|__flush_tlb_one
macro_line|# define __flush_tlb_one(addr)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;if (cpu_has_invlpg)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;__flush_tlb_single(addr);&t;&t;&t;&bslash;&n;&t;&t;else&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;__flush_tlb();&t;&t;&t;&t;&t;&bslash;&n;&t;} while (0)
macro_line|#endif
multiline_comment|/*&n; * TLB flushing:&n; *&n; *  - flush_tlb() flushes the current mm struct TLBs&n; *  - flush_tlb_all() flushes all processes TLBs&n; *  - flush_tlb_mm(mm) flushes the specified mm context TLB&squot;s&n; *  - flush_tlb_page(vma, vmaddr) flushes one page&n; *  - flush_tlb_range(vma, start, end) flushes a range of pages&n; *  - flush_tlb_kernel_range(start, end) flushes a range of kernel pages&n; *  - flush_tlb_pgtables(mm, start, end) flushes a range of page tables&n; *&n; * ..but the i386 has somewhat limited tlb flushing capabilities,&n; * and page-granular flushes are available only on i486 and up.&n; */
macro_line|#ifndef CONFIG_SMP
DECL|macro|flush_tlb
mdefine_line|#define flush_tlb() __flush_tlb()
DECL|macro|flush_tlb_all
mdefine_line|#define flush_tlb_all() __flush_tlb_all()
DECL|macro|local_flush_tlb
mdefine_line|#define local_flush_tlb() __flush_tlb()
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
r_if
c_cond
(paren
id|mm
op_eq
id|current-&gt;active_mm
)paren
id|__flush_tlb
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
r_if
c_cond
(paren
id|vma-&gt;vm_mm
op_eq
id|current-&gt;active_mm
)paren
id|__flush_tlb_one
c_func
(paren
id|addr
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
r_if
c_cond
(paren
id|vma-&gt;vm_mm
op_eq
id|current-&gt;active_mm
)paren
id|__flush_tlb
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#else
macro_line|#include &lt;asm/smp.h&gt;
DECL|macro|local_flush_tlb
mdefine_line|#define local_flush_tlb() &bslash;&n;&t;__flush_tlb()
r_extern
r_void
id|flush_tlb_all
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|flush_tlb_current_task
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|flush_tlb_mm
c_func
(paren
r_struct
id|mm_struct
op_star
)paren
suffix:semicolon
r_extern
r_void
id|flush_tlb_page
c_func
(paren
r_struct
id|vm_area_struct
op_star
comma
r_int
r_int
)paren
suffix:semicolon
DECL|macro|flush_tlb
mdefine_line|#define flush_tlb()&t;flush_tlb_current_task()
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
id|flush_tlb_mm
c_func
(paren
id|vma-&gt;vm_mm
)paren
suffix:semicolon
)brace
DECL|macro|TLBSTATE_OK
mdefine_line|#define TLBSTATE_OK&t;1
DECL|macro|TLBSTATE_LAZY
mdefine_line|#define TLBSTATE_LAZY&t;2
DECL|struct|tlb_state
r_struct
id|tlb_state
(brace
DECL|member|active_mm
r_struct
id|mm_struct
op_star
id|active_mm
suffix:semicolon
DECL|member|state
r_int
id|state
suffix:semicolon
DECL|member|__cacheline_padding
r_char
id|__cacheline_padding
(braket
id|L1_CACHE_BYTES
op_minus
l_int|8
)braket
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|tlb_state
id|cpu_tlbstate
(braket
id|NR_CPUS
)braket
suffix:semicolon
macro_line|#endif
DECL|macro|flush_tlb_kernel_range
mdefine_line|#define flush_tlb_kernel_range(start, end) flush_tlb_all()
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
multiline_comment|/* i386 does not keep any page table caches in TLB */
)brace
macro_line|#endif /* _I386_TLBFLUSH_H */
eof
