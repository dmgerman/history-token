multiline_comment|/*&n; *  linux/include/asm-arm/proc-armv/page.h&n; *&n; *  Copyright (C) 1995-2002 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#ifndef __ASM_PROC_PAGE_H
DECL|macro|__ASM_PROC_PAGE_H
mdefine_line|#define __ASM_PROC_PAGE_H
multiline_comment|/* PAGE_SHIFT determines the page size */
DECL|macro|PAGE_SHIFT
mdefine_line|#define PAGE_SHIFT&t;12
DECL|macro|EXEC_PAGESIZE
mdefine_line|#define EXEC_PAGESIZE   4096
macro_line|#ifndef __ASSEMBLY__
macro_line|#ifdef STRICT_MM_TYPECHECKS
r_typedef
r_struct
(brace
DECL|member|pgd0
r_int
r_int
id|pgd0
suffix:semicolon
DECL|member|pgd1
r_int
r_int
id|pgd1
suffix:semicolon
DECL|typedef|pgd_t
)brace
id|pgd_t
suffix:semicolon
DECL|macro|pgd_val
mdefine_line|#define pgd_val(x)&t;((x).pgd0)
macro_line|#else
DECL|typedef|pgd_t
r_typedef
r_int
r_int
id|pgd_t
(braket
l_int|2
)braket
suffix:semicolon
DECL|macro|pgd_val
mdefine_line|#define pgd_val(x)&t;((x)[0])
macro_line|#endif
macro_line|#endif /* __ASSEMBLY__ */
macro_line|#endif /* __ASM_PROC_PAGE_H */
eof
