multiline_comment|/**&n; * @file init.c&n; *&n; * @remark Copyright 2002 OProfile authors&n; * @remark Read the file COPYING&n; *&n; * @author John Levon &lt;levon@movementarian.org&gt;&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/oprofile.h&gt;
macro_line|#include &lt;linux/init.h&gt;
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
id|timer_init
c_func
(paren
id|ops
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
