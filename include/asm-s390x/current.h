multiline_comment|/*&n; *  include/asm-s390/current.h&n; *&n; *  S390 version&n; *    Copyright (C) 1999 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; *    Author(s): Martin Schwidefsky (schwidefsky@de.ibm.com)&n; *&n; *  Derived from &quot;include/asm-i386/current.h&quot;&n; */
macro_line|#ifndef _S390_CURRENT_H
DECL|macro|_S390_CURRENT_H
mdefine_line|#define _S390_CURRENT_H
macro_line|#ifdef __KERNEL__
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
r_struct
id|task_struct
op_star
id|current
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;lghi  %0,-16384&bslash;n&bslash;t&quot;
l_string|&quot;ngr   %0,15&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|current
)paren
suffix:colon
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_return
id|current
suffix:semicolon
)brace
DECL|macro|current
mdefine_line|#define current get_current()
macro_line|#endif
macro_line|#endif /* !(_S390_CURRENT_H) */
eof
