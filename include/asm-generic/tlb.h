multiline_comment|/* asm-generic/tlb.h&n; *&n; *&t;Generic TLB shootdown code&n; *&n; * Copyright 2001 Red Hat, Inc.&n; * Based on code from mm/memory.c Copyright Linus Torvalds and others.&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _ASM_GENERIC__TLB_H
DECL|macro|_ASM_GENERIC__TLB_H
mdefine_line|#define _ASM_GENERIC__TLB_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/tlbflush.h&gt;
macro_line|#ifdef CONFIG_SMP
multiline_comment|/* aim for something that fits in the L1 cache */
DECL|macro|FREE_PTE_NR
mdefine_line|#define FREE_PTE_NR&t;508
multiline_comment|/* mmu_gather_t is an opaque type used by the mm code for passing around any&n; * data needed by arch specific code for tlb_remove_page.  This structure can&n; * be per-CPU or per-MM as the page table lock is held for the duration of TLB&n; * shootdown.&n; */
DECL|struct|free_pte_ctx
r_typedef
r_struct
id|free_pte_ctx
(brace
DECL|member|vma
r_struct
id|vm_area_struct
op_star
id|vma
suffix:semicolon
DECL|member|nr
r_int
r_int
id|nr
suffix:semicolon
multiline_comment|/* set to ~0UL means fast mode */
DECL|member|start_addr
DECL|member|end_addr
r_int
r_int
id|start_addr
comma
id|end_addr
suffix:semicolon
DECL|member|ptes
id|pte_t
id|ptes
(braket
id|FREE_PTE_NR
)braket
suffix:semicolon
DECL|typedef|mmu_gather_t
)brace
id|mmu_gather_t
suffix:semicolon
multiline_comment|/* Users of the generic TLB shootdown code must declare this storage space. */
r_extern
id|mmu_gather_t
id|mmu_gathers
(braket
id|NR_CPUS
)braket
suffix:semicolon
multiline_comment|/* tlb_gather_mmu&n; *&t;Return a pointer to an initialized mmu_gather_t.&n; */
DECL|function|tlb_gather_mmu
r_static
r_inline
id|mmu_gather_t
op_star
id|tlb_gather_mmu
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
)paren
(brace
id|mmu_gather_t
op_star
id|tlb
op_assign
op_amp
id|mmu_gathers
(braket
id|smp_processor_id
c_func
(paren
)paren
)braket
suffix:semicolon
r_struct
id|mm_struct
op_star
id|mm
op_assign
id|vma-&gt;vm_mm
suffix:semicolon
id|tlb-&gt;vma
op_assign
id|vma
suffix:semicolon
multiline_comment|/* Use fast mode if there is only one user of this mm (this process) */
id|tlb-&gt;nr
op_assign
(paren
id|atomic_read
c_func
(paren
op_amp
(paren
id|mm
)paren
op_member_access_from_pointer
id|mm_users
)paren
op_eq
l_int|1
)paren
ques
c_cond
op_complement
l_int|0UL
suffix:colon
l_int|0UL
suffix:semicolon
r_return
id|tlb
suffix:semicolon
)brace
multiline_comment|/* void tlb_remove_page(mmu_gather_t *tlb, pte_t *ptep, unsigned long addr)&n; *&t;Must perform the equivalent to __free_pte(pte_get_and_clear(ptep)), while&n; *&t;handling the additional races in SMP caused by other CPUs caching valid&n; *&t;mappings in their TLBs.&n; */
DECL|macro|tlb_remove_page
mdefine_line|#define tlb_remove_page(ctxp, pte, addr) do {&bslash;&n;&t;&t;/* Handle the common case fast, first. */&bslash;&n;&t;&t;if ((ctxp)-&gt;nr == ~0UL) {&bslash;&n;&t;&t;&t;__free_pte(*(pte));&bslash;&n;&t;&t;&t;pte_clear((pte));&bslash;&n;&t;&t;&t;break;&bslash;&n;&t;&t;}&bslash;&n;&t;&t;if (!(ctxp)-&gt;nr) &bslash;&n;&t;&t;&t;(ctxp)-&gt;start_addr = (addr);&bslash;&n;&t;&t;(ctxp)-&gt;ptes[(ctxp)-&gt;nr++] = ptep_get_and_clear(pte);&bslash;&n;&t;&t;(ctxp)-&gt;end_addr = (addr) + PAGE_SIZE;&bslash;&n;&t;&t;if ((ctxp)-&gt;nr &gt;= FREE_PTE_NR)&bslash;&n;&t;&t;&t;tlb_finish_mmu((ctxp), 0, 0);&bslash;&n;&t;} while (0)
multiline_comment|/* tlb_finish_mmu&n; *&t;Called at the end of the shootdown operation to free up any resources&n; *&t;that were required.  The page table lock is still held at this point.&n; */
DECL|function|tlb_finish_mmu
r_static
r_inline
r_void
id|tlb_finish_mmu
c_func
(paren
r_struct
id|free_pte_ctx
op_star
id|ctx
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
r_int
r_int
id|i
comma
id|nr
suffix:semicolon
multiline_comment|/* Handle the fast case first. */
r_if
c_cond
(paren
id|ctx-&gt;nr
op_eq
op_complement
l_int|0UL
)paren
(brace
id|flush_tlb_range
c_func
(paren
id|ctx-&gt;vma
comma
id|start
comma
id|end
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|nr
op_assign
id|ctx-&gt;nr
suffix:semicolon
id|ctx-&gt;nr
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|nr
)paren
id|flush_tlb_range
c_func
(paren
id|ctx-&gt;vma
comma
id|ctx-&gt;start_addr
comma
id|ctx-&gt;end_addr
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
id|nr
suffix:semicolon
id|i
op_increment
)paren
(brace
id|pte_t
id|pte
op_assign
id|ctx-&gt;ptes
(braket
id|i
)braket
suffix:semicolon
id|__free_pte
c_func
(paren
id|pte
)paren
suffix:semicolon
)brace
)brace
macro_line|#else
multiline_comment|/* The uniprocessor functions are quite simple and are inline macros in an&n; * attempt to get gcc to generate optimal code since this code is run on each&n; * page in a process at exit.&n; */
DECL|typedef|mmu_gather_t
r_typedef
r_struct
id|vm_area_struct
id|mmu_gather_t
suffix:semicolon
DECL|macro|tlb_gather_mmu
mdefine_line|#define tlb_gather_mmu(vma)&t;(vma)
DECL|macro|tlb_finish_mmu
mdefine_line|#define tlb_finish_mmu(tlb, start, end)&t;flush_tlb_range(tlb, start, end)
DECL|macro|tlb_remove_page
mdefine_line|#define tlb_remove_page(tlb, ptep, addr)&t;do {&bslash;&n;&t;&t;pte_t __pte = *(ptep);&bslash;&n;&t;&t;pte_clear(ptep);&bslash;&n;&t;&t;__free_pte(__pte);&bslash;&n;&t;} while (0)
macro_line|#endif
macro_line|#endif /* _ASM_GENERIC__TLB_H */
eof
