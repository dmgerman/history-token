multiline_comment|/*&n; * BK Id: %F% %I% %G% %U% %#%&n; */
multiline_comment|/*&n; * This file contains the routines for handling the MMU on those&n; * PowerPC implementations where the MMU substantially follows the&n; * architecture specification.  This includes the 6xx, 7xx, 7xxx,&n; * 8260, and POWER3 implementations but excludes the 8xx and 4xx.&n; * Although the iSeries hardware does comply with the architecture&n; * specification, the need to work through the hypervisor makes&n; * things sufficiently different that it is handled elsewhere.&n; *  -- paulus&n; * &n; *  Derived from arch/ppc/mm/init.c:&n; *    Copyright (C) 1995-1996 Gary Thomas (gdt@linuxppc.org)&n; *&n; *  Modifications by Paul Mackerras (PowerMac) (paulus@cs.anu.edu.au)&n; *  and Cort Dougan (PReP) (cort@cs.nmt.edu)&n; *    Copyright (C) 1996 Paul Mackerras&n; *  Amiga/APUS changes by Jesper Skov (jskov@cygnus.co.uk).&n; *&n; *  Derived from &quot;arch/i386/mm/init.c&quot;&n; *    Copyright (C) 1991, 1992, 1993, 1994  Linus Torvalds&n; *&n; *  This program is free software; you can redistribute it and/or&n; *  modify it under the terms of the GNU General Public License&n; *  as published by the Free Software Foundation; either version&n; *  2 of the License, or (at your option) any later version.&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/mmu_context.h&gt;
macro_line|#include &lt;asm/tlbflush.h&gt;
DECL|variable|next_mmu_context
id|mm_context_t
id|next_mmu_context
suffix:semicolon
DECL|variable|context_map
r_int
r_int
id|context_map
(braket
id|LAST_CONTEXT
op_div
id|BITS_PER_LONG
op_plus
l_int|1
)braket
suffix:semicolon
macro_line|#ifdef FEW_CONTEXTS
DECL|variable|nr_free_contexts
id|atomic_t
id|nr_free_contexts
suffix:semicolon
DECL|variable|context_mm
r_struct
id|mm_struct
op_star
id|context_mm
(braket
id|LAST_CONTEXT
op_plus
l_int|1
)braket
suffix:semicolon
r_void
id|steal_context
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* FEW_CONTEXTS */
multiline_comment|/*&n; * Initialize the context management stuff.&n; */
r_void
id|__init
DECL|function|mmu_context_init
id|mmu_context_init
c_func
(paren
r_void
)paren
(brace
multiline_comment|/*&n;&t; * Some processors have too few contexts to reserve one for&n;&t; * init_mm, and require using context 0 for a normal task.&n;&t; * Other processors reserve the use of context zero for the kernel.&n;&t; * This code assumes FIRST_CONTEXT &lt; 32.&n;&t; */
id|context_map
(braket
l_int|0
)braket
op_assign
(paren
l_int|1
op_lshift
id|FIRST_CONTEXT
)paren
op_minus
l_int|1
suffix:semicolon
id|next_mmu_context
op_assign
id|FIRST_CONTEXT
suffix:semicolon
macro_line|#ifdef FEW_CONTEXTS
id|atomic_set
c_func
(paren
op_amp
id|nr_free_contexts
comma
id|LAST_CONTEXT
op_minus
id|FIRST_CONTEXT
op_plus
l_int|1
)paren
suffix:semicolon
macro_line|#endif /* FEW_CONTEXTS */
)brace
macro_line|#ifdef FEW_CONTEXTS
multiline_comment|/*&n; * Steal a context from a task that has one at the moment.&n; * This is only used on 8xx and 4xx and we presently assume that&n; * they don&squot;t do SMP.  If they do then this will have to check&n; * whether the MM we steal is in use.&n; * We also assume that this is only used on systems that don&squot;t&n; * use an MMU hash table - this is true for 8xx and 4xx.&n; * This isn&squot;t an LRU system, it just frees up each context in&n; * turn (sort-of pseudo-random replacement :).  This would be the&n; * place to implement an LRU scheme if anyone was motivated to do it.&n; *  -- paulus&n; */
r_void
DECL|function|steal_context
id|steal_context
c_func
(paren
r_void
)paren
(brace
r_struct
id|mm_struct
op_star
id|mm
suffix:semicolon
multiline_comment|/* free up context `next_mmu_context&squot; */
multiline_comment|/* if we shouldn&squot;t free context 0, don&squot;t... */
r_if
c_cond
(paren
id|next_mmu_context
OL
id|FIRST_CONTEXT
)paren
id|next_mmu_context
op_assign
id|FIRST_CONTEXT
suffix:semicolon
id|mm
op_assign
id|context_mm
(braket
id|next_mmu_context
)braket
suffix:semicolon
id|flush_tlb_mm
c_func
(paren
id|mm
)paren
suffix:semicolon
id|destroy_context
c_func
(paren
id|mm
)paren
suffix:semicolon
)brace
macro_line|#endif /* FEW_CONTEXTS */
eof
