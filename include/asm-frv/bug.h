multiline_comment|/* bug.h: FRV bug trapping&n; *&n; * Copyright (C) 2004 Red Hat, Inc. All Rights Reserved.&n; * Written by David Howells (dhowells@redhat.com)&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _ASM_BUG_H
DECL|macro|_ASM_BUG_H
mdefine_line|#define _ASM_BUG_H
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/*&n; * Tell the user there is some problem.&n; */
r_extern
id|asmlinkage
r_void
id|__debug_bug_trap
c_func
(paren
r_int
id|signr
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_NO_KERNEL_MSG
DECL|macro|_debug_bug_printk
mdefine_line|#define&t;_debug_bug_printk()
macro_line|#else
r_extern
r_void
id|__debug_bug_printk
c_func
(paren
r_const
r_char
op_star
id|file
comma
r_int
id|line
)paren
suffix:semicolon
DECL|macro|_debug_bug_printk
mdefine_line|#define&t;_debug_bug_printk() __debug_bug_printk(__FILE__, __LINE__)
macro_line|#endif
DECL|macro|_debug_bug_trap
mdefine_line|#define _debug_bug_trap(signr)&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__debug_bug_trap(signr);&t;&t;&bslash;&n;&t;asm volatile(&quot;nop&quot;);&t;&t;&t;&bslash;&n;} while(0)
DECL|macro|HAVE_ARCH_BUG
mdefine_line|#define HAVE_ARCH_BUG
DECL|macro|BUG
mdefine_line|#define BUG()&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;_debug_bug_printk();&t;&t;&t;&bslash;&n;&t;_debug_bug_trap(6 /*SIGABRT*/);&t;&t;&bslash;&n;} while (0)
macro_line|#ifdef CONFIG_GDBSTUB
DECL|macro|HAVE_ARCH_KGDB_RAISE
mdefine_line|#define HAVE_ARCH_KGDB_RAISE
DECL|macro|kgdb_raise
mdefine_line|#define kgdb_raise(signr) do { _debug_bug_trap(signr); } while(0)
DECL|macro|HAVE_ARCH_KGDB_BAD_PAGE
mdefine_line|#define HAVE_ARCH_KGDB_BAD_PAGE
DECL|macro|kgdb_bad_page
mdefine_line|#define kgdb_bad_page(page) do { kgdb_raise(SIGABRT); } while(0)
macro_line|#endif
macro_line|#include &lt;asm-generic/bug.h&gt;
macro_line|#endif
eof
