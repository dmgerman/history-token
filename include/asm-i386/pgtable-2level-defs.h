macro_line|#ifndef _I386_PGTABLE_2LEVEL_DEFS_H
DECL|macro|_I386_PGTABLE_2LEVEL_DEFS_H
mdefine_line|#define _I386_PGTABLE_2LEVEL_DEFS_H
multiline_comment|/*&n; * traditional i386 two-level paging structure:&n; */
DECL|macro|PGDIR_SHIFT
mdefine_line|#define PGDIR_SHIFT&t;22
DECL|macro|PTRS_PER_PGD
mdefine_line|#define PTRS_PER_PGD&t;1024
multiline_comment|/*&n; * the i386 is two-level, so we don&squot;t really have any&n; * PMD directory physically.&n; */
DECL|macro|PTRS_PER_PTE
mdefine_line|#define PTRS_PER_PTE&t;1024
macro_line|#endif /* _I386_PGTABLE_2LEVEL_DEFS_H */
eof
