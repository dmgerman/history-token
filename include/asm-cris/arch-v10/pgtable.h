macro_line|#ifndef _CRIS_ARCH_PGTABLE_H
DECL|macro|_CRIS_ARCH_PGTABLE_H
mdefine_line|#define _CRIS_ARCH_PGTABLE_H
multiline_comment|/*&n; * Kernels own virtual memory area. &n; */
macro_line|#ifdef CONFIG_CRIS_LOW_MAP
DECL|macro|VMALLOC_START
mdefine_line|#define VMALLOC_START     KSEG_7
DECL|macro|VMALLOC_VMADDR
mdefine_line|#define VMALLOC_VMADDR(x) ((unsigned long)(x))
DECL|macro|VMALLOC_END
mdefine_line|#define VMALLOC_END       KSEG_8
macro_line|#else
DECL|macro|VMALLOC_START
mdefine_line|#define VMALLOC_START     KSEG_D
DECL|macro|VMALLOC_VMADDR
mdefine_line|#define VMALLOC_VMADDR(x) ((unsigned long)(x))
DECL|macro|VMALLOC_END
mdefine_line|#define VMALLOC_END       KSEG_E
macro_line|#endif
macro_line|#endif
eof
