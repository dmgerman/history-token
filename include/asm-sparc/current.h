multiline_comment|/*&n; *  include/asm-sparc/current.h&n; *&n; * Copyright (C) 1999 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; * Copyright (C) 2002 Pete Zaitcev (zaitcev@yahoo.com)&n; *&n; *  Derived from &quot;include/asm-s390/current.h&quot; by&n; *  Martin Schwidefsky (schwidefsky@de.ibm.com)&n; *  Derived from &quot;include/asm-i386/current.h&quot;&n; */
macro_line|#ifndef _ASM_CURRENT_H
DECL|macro|_ASM_CURRENT_H
mdefine_line|#define _ASM_CURRENT_H
multiline_comment|/*&n; * At the sparc64 DaveM keeps current_thread_info in %g4.&n; * We might want to consider doing the same to shave a few cycles.&n; */
singleline_comment|// Applications do not include kernel headers anymore, period.
singleline_comment|// #ifdef __KERNEL__
macro_line|#ifndef _ASM_THREAD_INFO_H
macro_line|#include &lt;asm/thread_info.h&gt;
macro_line|#endif
r_struct
id|task_struct
suffix:semicolon
multiline_comment|/* Two stage process (inline + #define) for type-checking. */
multiline_comment|/* We also obfuscate get_current() to check if anyone used that by mistake. */
DECL|function|__get_current
r_static
r_inline
r_struct
id|task_struct
op_star
id|__get_current
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
mdefine_line|#define current __get_current()
singleline_comment|// #endif /* __KERNEL__ */
macro_line|#endif /* !(_ASM_CURRENT_H) */
eof
