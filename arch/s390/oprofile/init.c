multiline_comment|/**&n; * arch/s390/oprofile/init.c&n; *&n; * S390 Version&n; *   Copyright (C) 2003 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; *   Author(s): Thomas Spatzier (tspat@de.ibm.com)&n; *&n; * @remark Copyright 2002 OProfile authors&n; */
macro_line|#include &lt;linux/oprofile.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
singleline_comment|//extern int irq_init(struct oprofile_operations** ops);
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
