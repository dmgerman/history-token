multiline_comment|/*&n; *  linux/include/asm-arm/proc-armo/page.h&n; *&n; *  Copyright (C) 1995-2002 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#ifndef __ASM_PROC_PAGE_H
DECL|macro|__ASM_PROC_PAGE_H
mdefine_line|#define __ASM_PROC_PAGE_H
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/* PAGE_SHIFT determines the page size.  This is configurable. */
macro_line|#if defined(CONFIG_PAGESIZE_16)
DECL|macro|PAGE_SHIFT
mdefine_line|#define PAGE_SHIFT&t;14&t;&t;/* 16K */
macro_line|#else&t;&t;/* default */
DECL|macro|PAGE_SHIFT
mdefine_line|#define PAGE_SHIFT&t;15&t;&t;/* 32K */
macro_line|#endif
DECL|macro|EXEC_PAGESIZE
mdefine_line|#define EXEC_PAGESIZE   32768
macro_line|#ifndef __ASSEMBLY__
macro_line|#ifdef STRICT_MM_TYPECHECKS
DECL|member|pgd
DECL|typedef|pgd_t
r_typedef
r_struct
(brace
r_int
r_int
id|pgd
suffix:semicolon
)brace
id|pgd_t
suffix:semicolon
DECL|macro|pgd_val
mdefine_line|#define pgd_val(x)&t;((x).pgd)
macro_line|#else
DECL|typedef|pgd_t
r_typedef
r_int
r_int
id|pgd_t
suffix:semicolon
DECL|macro|pgd_val
mdefine_line|#define pgd_val(x)&t;(x)
macro_line|#endif
macro_line|#endif /* __ASSEMBLY__ */
macro_line|#endif /* __ASM_PROC_PAGE_H */
eof
