multiline_comment|/* mem-layout.h: memory layout&n; *&n; * Copyright (C) 2004 Red Hat, Inc. All Rights Reserved.&n; * Written by David Howells (dhowells@redhat.com)&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _ASM_MEM_LAYOUT_H
DECL|macro|_ASM_MEM_LAYOUT_H
mdefine_line|#define _ASM_MEM_LAYOUT_H
macro_line|#ifndef __ASSEMBLY__
DECL|macro|__UL
mdefine_line|#define __UL(X)&t;((unsigned long) (X))
macro_line|#else
DECL|macro|__UL
mdefine_line|#define __UL(X)&t;(X)
macro_line|#endif
multiline_comment|/*&n; * PAGE_SHIFT determines the page size&n; */
DECL|macro|PAGE_SHIFT
mdefine_line|#define PAGE_SHIFT&t;&t;&t;14
macro_line|#ifndef __ASSEMBLY__
DECL|macro|PAGE_SIZE
mdefine_line|#define PAGE_SIZE&t;&t;&t;(1UL &lt;&lt; PAGE_SHIFT)
macro_line|#else
DECL|macro|PAGE_SIZE
mdefine_line|#define PAGE_SIZE&t;&t;&t;(1 &lt;&lt; PAGE_SHIFT)
macro_line|#endif
DECL|macro|PAGE_MASK
mdefine_line|#define PAGE_MASK&t;&t;&t;(~(PAGE_SIZE-1))
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * virtual memory layout from kernel&squot;s point of view&n; */
DECL|macro|PAGE_OFFSET
mdefine_line|#define PAGE_OFFSET&t;&t;&t;((unsigned long) &amp;__page_offset)
macro_line|#ifdef CONFIG_MMU
multiline_comment|/* see Documentation/fujitsu/frv/mmu-layout.txt */
DECL|macro|KERNEL_LOWMEM_START
mdefine_line|#define KERNEL_LOWMEM_START&t;&t;__UL(0xc0000000)
DECL|macro|KERNEL_LOWMEM_END
mdefine_line|#define KERNEL_LOWMEM_END&t;&t;__UL(0xd0000000)
DECL|macro|VMALLOC_START
mdefine_line|#define VMALLOC_START&t;&t;&t;__UL(0xd0000000)
DECL|macro|VMALLOC_END
mdefine_line|#define VMALLOC_END&t;&t;&t;__UL(0xd8000000)
DECL|macro|PKMAP_BASE
mdefine_line|#define PKMAP_BASE&t;&t;&t;__UL(0xd8000000)
DECL|macro|PKMAP_END
mdefine_line|#define PKMAP_END&t;&t;&t;__UL(0xdc000000)
DECL|macro|KMAP_ATOMIC_SECONDARY_FRAME
mdefine_line|#define KMAP_ATOMIC_SECONDARY_FRAME&t;__UL(0xdc000000)
DECL|macro|KMAP_ATOMIC_PRIMARY_FRAME
mdefine_line|#define KMAP_ATOMIC_PRIMARY_FRAME&t;__UL(0xdd000000)
macro_line|#endif
DECL|macro|KERNEL_IO_START
mdefine_line|#define KERNEL_IO_START&t;&t;&t;__UL(0xe0000000)
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * memory layout from userspace&squot;s point of view&n; */
DECL|macro|BRK_BASE
mdefine_line|#define BRK_BASE&t;&t;&t;__UL(2 * 1024 * 1024 + PAGE_SIZE)
DECL|macro|STACK_TOP
mdefine_line|#define STACK_TOP&t;&t;&t;__UL(2 * 1024 * 1024)
multiline_comment|/* userspace process size */
macro_line|#ifdef CONFIG_MMU
DECL|macro|TASK_SIZE
mdefine_line|#define TASK_SIZE&t;&t;&t;(PAGE_OFFSET)
macro_line|#else
DECL|macro|TASK_SIZE
mdefine_line|#define TASK_SIZE&t;&t;&t;__UL(0xFFFFFFFFUL)
macro_line|#endif
multiline_comment|/* base of area at which unspecified mmaps will start */
macro_line|#ifdef CONFIG_BINFMT_ELF_FDPIC
DECL|macro|TASK_UNMAPPED_BASE
mdefine_line|#define TASK_UNMAPPED_BASE&t;&t;__UL(16 * 1024 * 1024)
macro_line|#else
DECL|macro|TASK_UNMAPPED_BASE
mdefine_line|#define TASK_UNMAPPED_BASE&t;&t;__UL(TASK_SIZE / 3)
macro_line|#endif
macro_line|#endif /* _ASM_MEM_LAYOUT_H */
eof
