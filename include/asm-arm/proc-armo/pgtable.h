multiline_comment|/*&n; *  linux/include/asm-arm/proc-armo/pgtable.h&n; *&n; *  Copyright (C) 1995-1999 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; *  18-Oct-1997&t;RMK&t;Now two-level (32x32)&n; */
macro_line|#ifndef __ASM_PROC_PGTABLE_H
DECL|macro|__ASM_PROC_PGTABLE_H
mdefine_line|#define __ASM_PROC_PGTABLE_H
multiline_comment|/*&n; * entries per page directory level: they are two-level, so&n; * we don&squot;t really have any PMD directory.&n; */
DECL|macro|PTRS_PER_PTE
mdefine_line|#define PTRS_PER_PTE&t;&t;32
DECL|macro|PTRS_PER_PMD
mdefine_line|#define PTRS_PER_PMD&t;&t;1
DECL|macro|PTRS_PER_PGD
mdefine_line|#define PTRS_PER_PGD&t;&t;32
multiline_comment|/*&n; * The vmalloc() routines leaves a hole of 4kB between each vmalloced&n; * area for the same reason. ;)&n; */
DECL|macro|VMALLOC_START
mdefine_line|#define VMALLOC_START&t;  0x01a00000
DECL|macro|VMALLOC_VMADDR
mdefine_line|#define VMALLOC_VMADDR(x) ((unsigned long)(x))
DECL|macro|VMALLOC_END
mdefine_line|#define VMALLOC_END&t;  0x01c00000
DECL|macro|_PAGE_TABLE
mdefine_line|#define _PAGE_TABLE     (0x01)
DECL|macro|pmd_bad
mdefine_line|#define pmd_bad(pmd)&t;&t;((pmd_val(pmd) &amp; 0xfc000002))
DECL|macro|set_pmd
mdefine_line|#define set_pmd(pmdp,pmd)&t;((*(pmdp)) = (pmd))
DECL|function|__mk_pmd
r_extern
id|__inline__
id|pmd_t
id|__mk_pmd
c_func
(paren
id|pte_t
op_star
id|ptep
comma
r_int
r_int
id|prot
)paren
(brace
r_int
r_int
id|pte_ptr
op_assign
(paren
r_int
r_int
)paren
id|ptep
suffix:semicolon
id|pmd_t
id|pmd
suffix:semicolon
id|pmd_val
c_func
(paren
id|pmd
)paren
op_assign
id|__virt_to_phys
c_func
(paren
id|pte_ptr
)paren
op_or
id|prot
suffix:semicolon
r_return
id|pmd
suffix:semicolon
)brace
multiline_comment|/* these are aliases for the above function */
DECL|macro|mk_user_pmd
mdefine_line|#define mk_user_pmd(ptep)&t;__mk_pmd(ptep, _PAGE_TABLE)
DECL|macro|mk_kernel_pmd
mdefine_line|#define mk_kernel_pmd(ptep)&t;__mk_pmd(ptep, _PAGE_TABLE)
DECL|function|pmd_page
r_extern
id|__inline__
r_int
r_int
id|pmd_page
c_func
(paren
id|pmd_t
id|pmd
)paren
(brace
r_return
id|__phys_to_virt
c_func
(paren
id|pmd_val
c_func
(paren
id|pmd
)paren
op_amp
op_complement
id|_PAGE_TABLE
)paren
suffix:semicolon
)brace
DECL|macro|set_pte
mdefine_line|#define set_pte(pteptr, pteval)&t;((*(pteptr)) = (pteval))
DECL|macro|_PAGE_PRESENT
mdefine_line|#define _PAGE_PRESENT&t;0x01
DECL|macro|_PAGE_READONLY
mdefine_line|#define _PAGE_READONLY&t;0x02
DECL|macro|_PAGE_NOT_USER
mdefine_line|#define _PAGE_NOT_USER&t;0x04
DECL|macro|_PAGE_OLD
mdefine_line|#define _PAGE_OLD&t;0x08
DECL|macro|_PAGE_CLEAN
mdefine_line|#define _PAGE_CLEAN&t;0x10
multiline_comment|/*                               -- present --   -- !dirty --  --- !write ---   ---- !user --- */
DECL|macro|PAGE_NONE
mdefine_line|#define PAGE_NONE       __pgprot(_PAGE_PRESENT | _PAGE_CLEAN | _PAGE_READONLY | _PAGE_NOT_USER)
DECL|macro|PAGE_SHARED
mdefine_line|#define PAGE_SHARED     __pgprot(_PAGE_PRESENT | _PAGE_CLEAN                                  )
DECL|macro|PAGE_COPY
mdefine_line|#define PAGE_COPY       __pgprot(_PAGE_PRESENT | _PAGE_CLEAN | _PAGE_READONLY                 )
DECL|macro|PAGE_READONLY
mdefine_line|#define PAGE_READONLY   __pgprot(_PAGE_PRESENT | _PAGE_CLEAN | _PAGE_READONLY                 )
DECL|macro|PAGE_KERNEL
mdefine_line|#define PAGE_KERNEL     __pgprot(_PAGE_PRESENT                                | _PAGE_NOT_USER)
DECL|macro|_PAGE_CHG_MASK
mdefine_line|#define _PAGE_CHG_MASK&t;(PAGE_MASK | _PAGE_OLD | _PAGE_CLEAN)
multiline_comment|/*&n; * The following only work if pte_present() is true.&n; * Undefined behaviour if not..&n; */
DECL|macro|pte_present
mdefine_line|#define pte_present(pte)&t;&t;(pte_val(pte) &amp; _PAGE_PRESENT)
DECL|macro|pte_read
mdefine_line|#define pte_read(pte)&t;&t;&t;(!(pte_val(pte) &amp; _PAGE_NOT_USER))
DECL|macro|pte_write
mdefine_line|#define pte_write(pte)&t;&t;&t;(!(pte_val(pte) &amp; _PAGE_READONLY))
DECL|macro|pte_exec
mdefine_line|#define pte_exec(pte)&t;&t;&t;(!(pte_val(pte) &amp; _PAGE_NOT_USER))
DECL|macro|pte_dirty
mdefine_line|#define pte_dirty(pte)&t;&t;&t;(!(pte_val(pte) &amp; _PAGE_CLEAN))
DECL|macro|pte_young
mdefine_line|#define pte_young(pte)&t;&t;&t;(!(pte_val(pte) &amp; _PAGE_OLD))
DECL|function|pte_nocache
r_extern
r_inline
id|pte_t
id|pte_nocache
c_func
(paren
id|pte_t
id|pte
)paren
(brace
r_return
id|pte
suffix:semicolon
)brace
DECL|function|pte_wrprotect
r_extern
r_inline
id|pte_t
id|pte_wrprotect
c_func
(paren
id|pte_t
id|pte
)paren
(brace
id|pte_val
c_func
(paren
id|pte
)paren
op_or_assign
id|_PAGE_READONLY
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|function|pte_rdprotect
r_extern
r_inline
id|pte_t
id|pte_rdprotect
c_func
(paren
id|pte_t
id|pte
)paren
(brace
id|pte_val
c_func
(paren
id|pte
)paren
op_or_assign
id|_PAGE_NOT_USER
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|function|pte_exprotect
r_extern
r_inline
id|pte_t
id|pte_exprotect
c_func
(paren
id|pte_t
id|pte
)paren
(brace
id|pte_val
c_func
(paren
id|pte
)paren
op_or_assign
id|_PAGE_NOT_USER
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|function|pte_mkclean
r_extern
r_inline
id|pte_t
id|pte_mkclean
c_func
(paren
id|pte_t
id|pte
)paren
(brace
id|pte_val
c_func
(paren
id|pte
)paren
op_or_assign
id|_PAGE_CLEAN
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|function|pte_mkold
r_extern
r_inline
id|pte_t
id|pte_mkold
c_func
(paren
id|pte_t
id|pte
)paren
(brace
id|pte_val
c_func
(paren
id|pte
)paren
op_or_assign
id|_PAGE_OLD
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|function|pte_mkwrite
r_extern
r_inline
id|pte_t
id|pte_mkwrite
c_func
(paren
id|pte_t
id|pte
)paren
(brace
id|pte_val
c_func
(paren
id|pte
)paren
op_and_assign
op_complement
id|_PAGE_READONLY
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|function|pte_mkread
r_extern
r_inline
id|pte_t
id|pte_mkread
c_func
(paren
id|pte_t
id|pte
)paren
(brace
id|pte_val
c_func
(paren
id|pte
)paren
op_and_assign
op_complement
id|_PAGE_NOT_USER
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|function|pte_mkexec
r_extern
r_inline
id|pte_t
id|pte_mkexec
c_func
(paren
id|pte_t
id|pte
)paren
(brace
id|pte_val
c_func
(paren
id|pte
)paren
op_and_assign
op_complement
id|_PAGE_NOT_USER
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|function|pte_mkdirty
r_extern
r_inline
id|pte_t
id|pte_mkdirty
c_func
(paren
id|pte_t
id|pte
)paren
(brace
id|pte_val
c_func
(paren
id|pte
)paren
op_and_assign
op_complement
id|_PAGE_CLEAN
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|function|pte_mkyoung
r_extern
r_inline
id|pte_t
id|pte_mkyoung
c_func
(paren
id|pte_t
id|pte
)paren
(brace
id|pte_val
c_func
(paren
id|pte
)paren
op_and_assign
op_complement
id|_PAGE_OLD
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|macro|pte_alloc_kernel
mdefine_line|#define pte_alloc_kernel        pte_alloc
macro_line|#endif /* __ASM_PROC_PGTABLE_H */
eof
