macro_line|#ifndef _ASM_PARISC_COMPAT_UCONTEXT_H
DECL|macro|_ASM_PARISC_COMPAT_UCONTEXT_H
mdefine_line|#define _ASM_PARISC_COMPAT_UCONTEXT_H
macro_line|#include&lt;linux/compat.h&gt;
macro_line|#include&lt;asm/compat_signal.h&gt;
multiline_comment|/* 32-bit ucontext as seen from an 64-bit kernel */
DECL|struct|compat_ucontext
r_struct
id|compat_ucontext
(brace
DECL|member|uc_flags
id|compat_uint_t
id|uc_flags
suffix:semicolon
DECL|member|uc_link
id|compat_uptr_t
id|uc_link
suffix:semicolon
DECL|member|uc_stack
id|compat_stack_t
id|uc_stack
suffix:semicolon
multiline_comment|/* struct compat_sigaltstack (12 bytes)*/
multiline_comment|/* FIXME: Pad out to get uc_mcontext to start at an 8-byte aligned boundary */
DECL|member|pad
id|compat_uint_t
id|pad
(braket
l_int|1
)braket
suffix:semicolon
DECL|member|uc_mcontext
r_struct
id|compat_sigcontext
id|uc_mcontext
suffix:semicolon
DECL|member|uc_sigmask
id|compat_sigset_t
id|uc_sigmask
suffix:semicolon
multiline_comment|/* mask last for extensibility */
)brace
suffix:semicolon
macro_line|#endif /* !_ASM_PARISC_COMPAT_UCONTEXT_H */
eof
