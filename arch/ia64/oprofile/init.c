multiline_comment|/**&n; * @file init.c&n; *&n; * @remark Copyright 2002 OProfile authors&n; * @remark Read the file COPYING&n; *&n; * @author John Levon &lt;levon@movementarian.org&gt;&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/oprofile.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
r_extern
r_int
id|perfmon_init
c_func
(paren
r_struct
id|oprofile_operations
op_star
id|ops
)paren
suffix:semicolon
r_extern
r_void
id|perfmon_exit
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|ia64_backtrace
c_func
(paren
r_struct
id|pt_regs
op_star
r_const
id|regs
comma
r_int
r_int
id|depth
)paren
suffix:semicolon
DECL|function|oprofile_arch_init
r_void
id|__init
id|oprofile_arch_init
c_func
(paren
r_struct
id|oprofile_operations
op_star
id|ops
)paren
(brace
macro_line|#ifdef CONFIG_PERFMON
multiline_comment|/* perfmon_init() can fail, but we have no way to report it */
id|perfmon_init
c_func
(paren
id|ops
)paren
suffix:semicolon
macro_line|#endif
id|ops-&gt;backtrace
op_assign
id|ia64_backtrace
suffix:semicolon
)brace
DECL|function|oprofile_arch_exit
r_void
id|oprofile_arch_exit
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_PERFMON
id|perfmon_exit
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
)brace
eof
