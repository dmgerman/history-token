macro_line|#ifndef _ASMPPC64_UCONTEXT_H
DECL|macro|_ASMPPC64_UCONTEXT_H
mdefine_line|#define _ASMPPC64_UCONTEXT_H
macro_line|#include &lt;asm/sigcontext.h&gt;
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
DECL|struct|ucontext
r_struct
id|ucontext
(brace
DECL|member|uc_flags
r_int
r_int
id|uc_flags
suffix:semicolon
DECL|member|uc_link
r_struct
id|ucontext
op_star
id|uc_link
suffix:semicolon
DECL|member|uc_stack
id|stack_t
id|uc_stack
suffix:semicolon
DECL|member|uc_sigmask
id|sigset_t
id|uc_sigmask
suffix:semicolon
DECL|member|__unsued
id|sigset_t
id|__unsued
(braket
l_int|15
)braket
suffix:semicolon
multiline_comment|/* Allow for uc_sigmask growth */
DECL|member|uc_mcontext
r_struct
id|sigcontext
id|uc_mcontext
suffix:semicolon
multiline_comment|/* last for extensibility */
)brace
suffix:semicolon
macro_line|#endif /* _ASMPPC64_UCONTEXT_H */
eof
