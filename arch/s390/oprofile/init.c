multiline_comment|/**&n; * arch/s390/oprofile/init.c&n; *&n; * S390 Version&n; *   Copyright (C) 2003 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; *   Author(s): Thomas Spatzier (tspat@de.ibm.com)&n; *&n; * @remark Copyright 2002 OProfile authors&n; */
macro_line|#include &lt;linux/oprofile.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
DECL|function|oprofile_arch_init
r_int
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
r_void
)paren
(brace
)brace
eof
