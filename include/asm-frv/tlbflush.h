multiline_comment|/* tlbflush.h: TLB flushing functions&n; *&n; * Copyright (C) 2004 Red Hat, Inc. All Rights Reserved.&n; * Written by David Howells (dhowells@redhat.com)&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _ASM_TLBFLUSH_H
DECL|macro|_ASM_TLBFLUSH_H
mdefine_line|#define _ASM_TLBFLUSH_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#ifdef CONFIG_MMU
macro_line|#ifndef __ASSEMBLY__
r_extern
r_void
id|asmlinkage
id|__flush_tlb_all
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|asmlinkage
id|__flush_tlb_mm
c_func
(paren
r_int
r_int
id|contextid
)paren
suffix:semicolon
r_extern
r_void
id|asmlinkage
id|__flush_tlb_page
c_func
(paren
r_int
r_int
id|contextid
comma
r_int
r_int
id|start
)paren
suffix:semicolon
r_extern
r_void
id|asmlinkage
id|__flush_tlb_range
c_func
(paren
r_int
r_int
id|contextid
comma
r_int
r_int
id|start
comma
r_int
r_int
id|end
)paren
suffix:semicolon
macro_line|#endif /* !__ASSEMBLY__ */
DECL|macro|flush_tlb_all
mdefine_line|#define flush_tlb_all()&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;preempt_disable();&t;&t;&t;&bslash;&n;&t;__flush_tlb_all();&t;&t;&t;&bslash;&n;&t;preempt_enable();&t;&t;&t;&bslash;&n;} while(0)
DECL|macro|flush_tlb_mm
mdefine_line|#define flush_tlb_mm(mm)&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;preempt_disable();&t;&t;&t;&bslash;&n;&t;__flush_tlb_mm((mm)-&gt;context.id);&t;&bslash;&n;&t;preempt_enable();&t;&t;&t;&bslash;&n;} while(0)
DECL|macro|flush_tlb_range
mdefine_line|#define flush_tlb_range(vma,start,end)&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;preempt_disable();&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__flush_tlb_range((vma)-&gt;vm_mm-&gt;context.id, start, end);&t;&bslash;&n;&t;preempt_enable();&t;&t;&t;&t;&t;&t;&bslash;&n;} while(0)
DECL|macro|flush_tlb_page
mdefine_line|#define flush_tlb_page(vma,addr)&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;preempt_disable();&t;&t;&t;&t;&t;&bslash;&n;&t;__flush_tlb_page((vma)-&gt;vm_mm-&gt;context.id, addr);&t;&bslash;&n;&t;preempt_enable();&t;&t;&t;&t;&t;&bslash;&n;} while(0)
DECL|macro|__flush_tlb_global
mdefine_line|#define __flush_tlb_global()&t;&t;&t;flush_tlb_all()
DECL|macro|flush_tlb
mdefine_line|#define flush_tlb()&t;&t;&t;&t;flush_tlb_all()
DECL|macro|flush_tlb_kernel_range
mdefine_line|#define flush_tlb_kernel_range(start, end)&t;flush_tlb_all()
DECL|macro|flush_tlb_pgtables
mdefine_line|#define flush_tlb_pgtables(mm,start,end)&t;asm volatile(&quot;movgs gr0,scr0 ! movgs gr0,scr1&quot;);
macro_line|#else
DECL|macro|flush_tlb
mdefine_line|#define flush_tlb()&t;&t;&t;&t;BUG()
DECL|macro|flush_tlb_all
mdefine_line|#define flush_tlb_all()&t;&t;&t;&t;BUG()
DECL|macro|flush_tlb_mm
mdefine_line|#define flush_tlb_mm(mm)&t;&t;&t;BUG()
DECL|macro|flush_tlb_page
mdefine_line|#define flush_tlb_page(vma,addr)&t;&t;BUG()
DECL|macro|flush_tlb_range
mdefine_line|#define flush_tlb_range(mm,start,end)&t;&t;BUG()
DECL|macro|flush_tlb_pgtables
mdefine_line|#define flush_tlb_pgtables(mm,start,end)&t;BUG()
DECL|macro|flush_tlb_kernel_range
mdefine_line|#define flush_tlb_kernel_range(start, end)&t;BUG()
macro_line|#endif
macro_line|#endif /* _ASM_TLBFLUSH_H */
eof
