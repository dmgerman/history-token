multiline_comment|/**&n; * @file init.c&n; *&n; * @remark Copyright 2002 OProfile authors&n; * @remark Read the file COPYING&n; *&n; * @author John Levon &lt;levon@movementarian.org&gt;&n; */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/oprofile.h&gt;
r_extern
r_void
id|timer_init
c_func
(paren
r_struct
id|oprofile_operations
op_star
op_star
id|ops
)paren
suffix:semicolon
DECL|function|oprofile_arch_init
r_int
id|__init
id|oprofile_arch_init
c_func
(paren
r_struct
id|oprofile_operations
op_star
op_star
id|ops
)paren
(brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
DECL|function|oprofile_arch_exit
r_void
id|oprofile_arch_exit
c_func
(paren
)paren
(brace
)brace
eof
