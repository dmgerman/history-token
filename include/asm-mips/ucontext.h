multiline_comment|/* $Id: ucontext.h,v 1.2 1999/09/27 16:01:40 ralf Exp $&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Low level exception handling&n; *&n; * Copyright (C) 1998, 1999 by Ralf Baechle&n; */
macro_line|#ifndef _ASM_UCONTEXT_H
DECL|macro|_ASM_UCONTEXT_H
mdefine_line|#define _ASM_UCONTEXT_H
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
DECL|member|uc_mcontext
r_struct
id|sigcontext
id|uc_mcontext
suffix:semicolon
DECL|member|uc_sigmask
id|sigset_t
id|uc_sigmask
suffix:semicolon
multiline_comment|/* mask last for extensibility */
)brace
suffix:semicolon
macro_line|#endif /* _ASM_UCONTEXT_H */
eof
