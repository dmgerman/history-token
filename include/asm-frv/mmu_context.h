multiline_comment|/* mmu_context.h: MMU context management routines&n; *&n; * Copyright (C) 2004 Red Hat, Inc. All Rights Reserved.&n; * Written by David Howells (dhowells@redhat.com)&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _ASM_MMU_CONTEXT_H
DECL|macro|_ASM_MMU_CONTEXT_H
mdefine_line|#define _ASM_MMU_CONTEXT_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
DECL|function|enter_lazy_tlb
r_static
r_inline
r_void
id|enter_lazy_tlb
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
r_struct
id|task_struct
op_star
id|tsk
)paren
(brace
)brace
macro_line|#ifdef CONFIG_MMU
r_extern
r_int
id|init_new_context
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
comma
r_struct
id|mm_struct
op_star
id|mm
)paren
suffix:semicolon
r_extern
r_void
id|change_mm_context
c_func
(paren
id|mm_context_t
op_star
id|old
comma
id|mm_context_t
op_star
id|ctx
comma
id|pml4_t
op_star
id|_pml4
)paren
suffix:semicolon
r_extern
r_void
id|destroy_context
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
suffix:semicolon
macro_line|#else
DECL|macro|init_new_context
mdefine_line|#define init_new_context(tsk, mm)&t;&t;({ 0; })
DECL|macro|change_mm_context
mdefine_line|#define change_mm_context(old, ctx, _pml4)&t;do {} while(0)
DECL|macro|destroy_context
mdefine_line|#define destroy_context(mm)&t;&t;&t;do {} while(0)
macro_line|#endif
DECL|macro|switch_mm
mdefine_line|#define switch_mm(prev, next, tsk)&t;&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (prev != next)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;change_mm_context(&amp;prev-&gt;context, &amp;next-&gt;context, next-&gt;pml4);&t;&bslash;&n;} while(0)
DECL|macro|activate_mm
mdefine_line|#define activate_mm(prev, next)&t;&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;change_mm_context(&amp;prev-&gt;context, &amp;next-&gt;context, next-&gt;pml4);&t;&bslash;&n;} while(0)
DECL|macro|deactivate_mm
mdefine_line|#define deactivate_mm(tsk, mm)&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&bslash;&n;} while(0)
macro_line|#endif
eof
