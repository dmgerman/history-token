macro_line|#ifndef _ASM_IA64_UCONTEXT_H
DECL|macro|_ASM_IA64_UCONTEXT_H
mdefine_line|#define _ASM_IA64_UCONTEXT_H
DECL|struct|ucontext
r_struct
id|ucontext
(brace
DECL|member|uc_mcontext
r_struct
id|sigcontext
id|uc_mcontext
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|uc_link
mdefine_line|#define uc_link&t;&t;uc_mcontext.sc_gr[0]&t;/* wrong type; nobody cares */
DECL|macro|uc_sigmask
mdefine_line|#define uc_sigmask&t;uc_mcontext.sc_sigmask
DECL|macro|uc_stack
mdefine_line|#define uc_stack&t;uc_mcontext.sc_stack
macro_line|#endif /* _ASM_IA64_UCONTEXT_H */
eof
