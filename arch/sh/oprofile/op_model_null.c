multiline_comment|/*&n; * arch/sh/oprofile/op_model_null.c&n; *&n; * Copyright (C) 2003  Paul Mundt&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/oprofile.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
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
)brace
DECL|function|oprofile_arch_exit
r_void
id|oprofile_arch_exit
c_func
(paren
r_void
)paren
(brace
)brace
eof
