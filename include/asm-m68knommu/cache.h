macro_line|#ifndef __ARCH_M68KNOMMU_CACHE_H
DECL|macro|__ARCH_M68KNOMMU_CACHE_H
mdefine_line|#define __ARCH_M68KNOMMU_CACHE_H
multiline_comment|/* bytes per L1 cache line */
DECL|macro|L1_CACHE_BYTES
mdefine_line|#define        L1_CACHE_BYTES  16&t;/* this need to be at least 1 */
multiline_comment|/* m68k-elf-gcc  2.95.2 doesn&squot;t like these */
DECL|macro|__cacheline_aligned
mdefine_line|#define __cacheline_aligned
DECL|macro|____cacheline_aligned
mdefine_line|#define ____cacheline_aligned
macro_line|#endif
eof
