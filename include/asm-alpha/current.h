macro_line|#ifndef _ALPHA_CURRENT_H
DECL|macro|_ALPHA_CURRENT_H
mdefine_line|#define _ALPHA_CURRENT_H
macro_line|#include &lt;asm/thread_info.h&gt;
DECL|macro|get_current
mdefine_line|#define get_current()&t;(current_thread_info()-&gt;task + 0)
DECL|macro|current
mdefine_line|#define current&t;&t;get_current()
macro_line|#endif /* _ALPHA_CURRENT_H */
eof
