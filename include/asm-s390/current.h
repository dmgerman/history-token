multiline_comment|/*&n; *  include/asm-s390/current.h&n; *&n; *  S390 version&n; *    Copyright (C) 1999 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; *    Author(s): Martin Schwidefsky (schwidefsky@de.ibm.com)&n; *&n; *  Derived from &quot;include/asm-i386/current.h&quot;&n; */
macro_line|#ifndef _S390_CURRENT_H
DECL|macro|_S390_CURRENT_H
mdefine_line|#define _S390_CURRENT_H
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;asm/thread_info.h&gt;
r_struct
id|task_struct
suffix:semicolon
DECL|function|get_current
r_static
r_inline
r_struct
id|task_struct
op_star
id|get_current
c_func
(paren
r_void
)paren
(brace
r_return
id|current_thread_info
c_func
(paren
)paren
op_member_access_from_pointer
id|task
suffix:semicolon
)brace
DECL|macro|current
mdefine_line|#define current get_current()
macro_line|#endif
macro_line|#endif /* !(_S390_CURRENT_H) */
eof
