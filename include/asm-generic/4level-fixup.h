macro_line|#ifndef _4LEVEL_FIXUP_H
DECL|macro|_4LEVEL_FIXUP_H
mdefine_line|#define _4LEVEL_FIXUP_H
DECL|macro|__ARCH_HAS_4LEVEL_HACK
mdefine_line|#define __ARCH_HAS_4LEVEL_HACK
DECL|macro|PUD_SIZE
mdefine_line|#define PUD_SIZE&t;&t;&t;PGDIR_SIZE
DECL|macro|PUD_MASK
mdefine_line|#define PUD_MASK&t;&t;&t;PGDIR_MASK
DECL|macro|PTRS_PER_PUD
mdefine_line|#define PTRS_PER_PUD&t;&t;&t;1
DECL|macro|pud_t
mdefine_line|#define pud_t&t;&t;&t;&t;pgd_t
DECL|macro|pmd_alloc
mdefine_line|#define pmd_alloc(mm, pud, address)&t;&t;&t;&bslash;&n;({&t;pmd_t *ret;&t;&t;&t;&t;&t;&bslash;&n;&t;if (pgd_none(*pud))&t;&t;&t;&t;&bslash;&n; &t;&t;ret = __pmd_alloc(mm, pud, address);&t;&bslash;&n; &t;else&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;ret = pmd_offset(pud, address);&t;&t;&bslash;&n; &t;ret;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|pud_alloc
mdefine_line|#define pud_alloc(mm, pgd, address)&t;(pgd)
DECL|macro|pud_offset
mdefine_line|#define pud_offset(pgd, start)&t;&t;(pgd)
DECL|macro|pud_none
mdefine_line|#define pud_none(pud)&t;&t;&t;0
DECL|macro|pud_bad
mdefine_line|#define pud_bad(pud)&t;&t;&t;0
DECL|macro|pud_present
mdefine_line|#define pud_present(pud)&t;&t;1
DECL|macro|pud_ERROR
mdefine_line|#define pud_ERROR(pud)&t;&t;&t;do { } while (0)
DECL|macro|pud_clear
mdefine_line|#define pud_clear(pud)&t;&t;&t;pgd_clear(pud)
DECL|macro|pud_free_tlb
macro_line|#undef pud_free_tlb
DECL|macro|pud_free_tlb
mdefine_line|#define pud_free_tlb(tlb, x)            do { } while (0)
DECL|macro|pud_free
mdefine_line|#define pud_free(x)&t;&t;&t;do { } while (0)
DECL|macro|__pud_free_tlb
mdefine_line|#define __pud_free_tlb(tlb, x)&t;&t;do { } while (0)
macro_line|#endif
eof
