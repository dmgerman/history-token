multiline_comment|/*&n; *  arch/mips/vm86.c&n; *&n; *  Copyright (C) 1994  Waldorf GMBH,&n; *  written by Ralf Baechle&n; */
macro_line|#include &lt;linux/linkage.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
DECL|function|sys_vm86
id|asmlinkage
r_int
id|sys_vm86
c_func
(paren
r_void
op_star
id|v86
)paren
(brace
r_return
op_minus
id|ENOSYS
suffix:semicolon
)brace
eof
