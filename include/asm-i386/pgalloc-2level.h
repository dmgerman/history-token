macro_line|#ifndef _I386_PGALLOC_2LEVEL_H
DECL|macro|_I386_PGALLOC_2LEVEL_H
mdefine_line|#define _I386_PGALLOC_2LEVEL_H
multiline_comment|/*&n; * traditional i386 two-level paging, page table allocation routines:&n; * We don&squot;t have any real pmd&squot;s, and this code never triggers because&n; * the pgd will always be present..&n; */
DECL|macro|pmd_alloc_one_fast
mdefine_line|#define pmd_alloc_one_fast()&t;&t;({ BUG(); ((pmd_t *)1); })
DECL|macro|pmd_alloc_one
mdefine_line|#define pmd_alloc_one()&t;&t;&t;({ BUG(); ((pmd_t *)2); })
DECL|macro|pmd_free_slow
mdefine_line|#define pmd_free_slow(x)&t;&t;do { } while (0)
DECL|macro|pmd_free_fast
mdefine_line|#define pmd_free_fast(x)&t;&t;do { } while (0)
DECL|macro|pmd_free
mdefine_line|#define pmd_free(x)&t;&t;&t;do { } while (0)
DECL|macro|pgd_populate
mdefine_line|#define pgd_populate(pmd, pte)&t;&t;BUG()
macro_line|#endif /* _I386_PGALLOC_2LEVEL_H */
eof
