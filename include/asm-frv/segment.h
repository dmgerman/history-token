multiline_comment|/* segment.h: MMU segment settings&n; *&n; * Copyright (C) 2003 Red Hat, Inc. All Rights Reserved.&n; * Written by David Howells (dhowells@redhat.com)&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _ASM_SEGMENT_H
DECL|macro|_ASM_SEGMENT_H
mdefine_line|#define _ASM_SEGMENT_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifndef __ASSEMBLY__
r_typedef
r_struct
(brace
DECL|member|seg
r_int
r_int
id|seg
suffix:semicolon
DECL|typedef|mm_segment_t
)brace
id|mm_segment_t
suffix:semicolon
DECL|macro|MAKE_MM_SEG
mdefine_line|#define MAKE_MM_SEG(s)&t;((mm_segment_t) { (s) })
DECL|macro|KERNEL_DS
mdefine_line|#define KERNEL_DS&t;&t;MAKE_MM_SEG(0xdfffffffUL)
macro_line|#ifdef CONFIG_MMU
DECL|macro|USER_DS
mdefine_line|#define USER_DS&t;&t;&t;MAKE_MM_SEG(TASK_SIZE - 1)
macro_line|#else
DECL|macro|USER_DS
mdefine_line|#define USER_DS&t;&t;&t;KERNEL_DS
macro_line|#endif
DECL|macro|get_ds
mdefine_line|#define get_ds()&t;&t;(KERNEL_DS)
DECL|macro|get_fs
mdefine_line|#define get_fs()&t;&t;(__current_thread_info-&gt;addr_limit)
DECL|macro|segment_eq
mdefine_line|#define segment_eq(a,b)&t;&t;((a).seg == (b).seg)
DECL|macro|__kernel_ds_p
mdefine_line|#define __kernel_ds_p()&t;&t;segment_eq(get_fs(), KERNEL_DS)
DECL|macro|get_addr_limit
mdefine_line|#define get_addr_limit()&t;(get_fs().seg)
DECL|macro|set_fs
mdefine_line|#define set_fs(_x)&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__current_thread_info-&gt;addr_limit = (_x);&t;&bslash;&n;} while(0)
macro_line|#endif /* __ASSEMBLY__ */
macro_line|#endif /* _ASM_SEGMENT_H */
eof
