multiline_comment|/*&n; *  linux/include/asm-arm/pgalloc.h&n; *&n; *  Copyright (C) 2000-2001 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#ifndef _ASMARM_PGALLOC_H
DECL|macro|_ASMARM_PGALLOC_H
mdefine_line|#define _ASMARM_PGALLOC_H
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/cacheflush.h&gt;
macro_line|#include &lt;asm/tlbflush.h&gt;
macro_line|#include &lt;asm/proc/pgalloc.h&gt;
multiline_comment|/*&n; * Since we have only two-level page tables, these are trivial&n; */
DECL|macro|pmd_alloc_one
mdefine_line|#define pmd_alloc_one(mm,addr)&t;&t;({ BUG(); ((pmd_t *)2); })
DECL|macro|pmd_free
mdefine_line|#define pmd_free(pmd)&t;&t;&t;do { } while (0)
DECL|macro|pgd_populate
mdefine_line|#define pgd_populate(mm,pmd,pte)&t;BUG()
r_extern
id|pgd_t
op_star
id|get_pgd_slow
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
suffix:semicolon
r_extern
r_void
id|free_pgd_slow
c_func
(paren
id|pgd_t
op_star
id|pgd
)paren
suffix:semicolon
DECL|macro|pgd_alloc
mdefine_line|#define pgd_alloc(mm)&t;&t;&t;get_pgd_slow(mm)
DECL|macro|pgd_free
mdefine_line|#define pgd_free(pgd)&t;&t;&t;free_pgd_slow(pgd)
DECL|macro|check_pgt_cache
mdefine_line|#define check_pgt_cache()&t;&t;do { } while (0)
macro_line|#endif
eof
