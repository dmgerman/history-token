multiline_comment|/*&n; *  linux/include/asm-arm/proc-armo/pgalloc.h&n; *&n; *  Copyright (C) 2001 Russell King&n; *&n; * Page table allocation/freeing primitives for 26-bit ARM processors.&n; */
multiline_comment|/* unfortunately, this includes linux/mm.h and the rest of the universe. */
macro_line|#include &lt;linux/slab.h&gt;
r_extern
id|kmem_cache_t
op_star
id|pte_cache
suffix:semicolon
multiline_comment|/*&n; * Allocate one PTE table.&n; *&n; * Note that we keep the processor copy of the PTE entries separate&n; * from the Linux copy.  The processor copies are offset by -PTRS_PER_PTE&n; * words from the Linux copy.&n; */
DECL|function|pte_alloc_one
r_static
r_inline
id|pte_t
op_star
id|pte_alloc_one
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
r_int
r_int
id|address
)paren
(brace
r_return
id|kmem_cache_alloc
c_func
(paren
id|pte_cache
comma
id|GFP_KERNEL
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Free one PTE table.&n; */
DECL|function|pte_free_slow
r_static
r_inline
r_void
id|pte_free_slow
c_func
(paren
id|pte_t
op_star
id|pte
)paren
(brace
r_if
c_cond
(paren
id|pte
)paren
id|kmem_cache_free
c_func
(paren
id|pte_cache
comma
id|pte
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Populate the pmdp entry with a pointer to the pte.  This pmd is part&n; * of the mm address space.&n; *&n; * If &squot;mm&squot; is the init tasks mm, then we are doing a vmalloc, and we&n; * need to set stuff up correctly for it.&n; */
DECL|macro|pmd_populate
mdefine_line|#define pmd_populate(mm,pmdp,pte)&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;set_pmd(pmdp, __mk_pmd(pte, _PAGE_TABLE));&t;&bslash;&n;&t;} while (0)
eof
