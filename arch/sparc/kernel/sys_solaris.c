multiline_comment|/*&n; * linux/arch/sparc/sys_solaris.c&n; *&n; * Copyright (C) 1996 Miguel de Icaza (miguel@nuclecu.unam.mx)&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/personality.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/module.h&gt;
id|asmlinkage
r_int
DECL|function|do_solaris_syscall
id|do_solaris_syscall
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_static
r_int
id|cnt
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_increment
id|cnt
OL
l_int|10
)paren
id|printk
(paren
l_string|&quot;No solaris handler&bslash;n&quot;
)paren
suffix:semicolon
id|force_sig
c_func
(paren
id|SIGSEGV
comma
id|current
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifndef CONFIG_SUNOS_EMUL
id|asmlinkage
r_int
DECL|function|do_sunos_syscall
id|do_sunos_syscall
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_static
r_int
id|cnt
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_increment
id|cnt
OL
l_int|10
)paren
id|printk
(paren
l_string|&quot;SunOS binary emulation not compiled in&bslash;n&quot;
)paren
suffix:semicolon
id|force_sig
(paren
id|SIGSEGV
comma
id|current
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
eof
