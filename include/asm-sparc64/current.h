macro_line|#ifndef _SPARC64_CURRENT_H
DECL|macro|_SPARC64_CURRENT_H
mdefine_line|#define _SPARC64_CURRENT_H
macro_line|#include &lt;asm/thread_info.h&gt;
DECL|macro|current
mdefine_line|#define current&t;&t;(current_thread_info()-&gt;task)
macro_line|#endif /* !(_SPARC64_CURRENT_H) */
eof
