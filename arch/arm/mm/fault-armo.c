multiline_comment|/*&n; *  linux/arch/arm/mm/fault-armo.c&n; *&n; *  Copyright (C) 1995  Linus Torvalds&n; *  Modifications for ARM processor (c) 1995-1999 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/mman.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
DECL|macro|FAULT_CODE_FORCECOW
mdefine_line|#define FAULT_CODE_FORCECOW&t;0x80
DECL|macro|FAULT_CODE_PREFETCH
mdefine_line|#define FAULT_CODE_PREFETCH&t;0x04
DECL|macro|FAULT_CODE_WRITE
mdefine_line|#define FAULT_CODE_WRITE&t;0x02
DECL|macro|DO_COW
mdefine_line|#define DO_COW(m)&t;&t;((m) &amp; (FAULT_CODE_WRITE|FAULT_CODE_FORCECOW))
DECL|macro|READ_FAULT
mdefine_line|#define READ_FAULT(m)&t;&t;(!((m) &amp; FAULT_CODE_WRITE))
macro_line|#include &quot;fault-common.c&quot;
multiline_comment|/*&n; * Handle a data abort.  Note that we have to handle a range of addresses&n; * on ARM2/3 for ldm.  If both pages are zero-mapped, then we have to force&n; * a copy-on-write.  However, on the second page, we always force COW.&n; */
id|asmlinkage
r_void
DECL|function|do_DataAbort
id|do_DataAbort
c_func
(paren
r_int
r_int
id|min_addr
comma
r_int
r_int
id|max_addr
comma
r_int
id|mode
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|do_page_fault
c_func
(paren
id|min_addr
comma
id|mode
comma
id|regs
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|min_addr
op_xor
id|max_addr
)paren
op_rshift
id|PAGE_SHIFT
)paren
id|do_page_fault
c_func
(paren
id|max_addr
comma
id|mode
op_or
id|FAULT_CODE_FORCECOW
comma
id|regs
)paren
suffix:semicolon
)brace
id|asmlinkage
r_int
DECL|function|do_PrefetchAbort
id|do_PrefetchAbort
c_func
(paren
r_int
r_int
id|addr
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
macro_line|#if 0
r_if
c_cond
(paren
id|the
id|memc
id|mapping
r_for
id|this
id|page
id|exists
)paren
(brace
id|printk
(paren
l_string|&quot;Page in, but got abort (undefined instruction?)&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
id|do_page_fault
c_func
(paren
id|addr
comma
id|FAULT_CODE_PREFETCH
comma
id|regs
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
eof
