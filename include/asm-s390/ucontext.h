multiline_comment|/*&n; *  include/asm-s390/ucontext.h&n; *&n; *  S390 version&n; *&n; *  Derived from &quot;include/asm-i386/ucontext.h&quot;&n; */
macro_line|#ifndef _ASM_S390_UCONTEXT_H
DECL|macro|_ASM_S390_UCONTEXT_H
mdefine_line|#define _ASM_S390_UCONTEXT_H
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
macro_line|#endif /* !_ASM_S390_UCONTEXT_H */
eof
