macro_line|#ifndef _ASM_PARISC_RT_SIGFRAME_H
DECL|macro|_ASM_PARISC_RT_SIGFRAME_H
mdefine_line|#define _ASM_PARISC_RT_SIGFRAME_H
macro_line|#ifdef CONFIG_COMPAT
macro_line|#include &lt;asm/compat_rt_sigframe.h&gt;
macro_line|#endif
DECL|macro|SIGRETURN_TRAMP
mdefine_line|#define SIGRETURN_TRAMP 4
DECL|macro|SIGRESTARTBLOCK_TRAMP
mdefine_line|#define SIGRESTARTBLOCK_TRAMP 5 
DECL|macro|TRAMP_SIZE
mdefine_line|#define TRAMP_SIZE (SIGRETURN_TRAMP + SIGRESTARTBLOCK_TRAMP)
DECL|struct|rt_sigframe
r_struct
id|rt_sigframe
(brace
multiline_comment|/* XXX: Must match trampoline size in arch/parisc/kernel/signal.c &n;&t;        Secondary to that it must protect the ERESTART_RESTARTBLOCK&n;&t;&t;trampoline we left on the stack (we were bad and didn&squot;t &n;&t;&t;change sp so we could run really fast.) */
DECL|member|tramp
r_int
r_int
id|tramp
(braket
id|TRAMP_SIZE
)braket
suffix:semicolon
DECL|member|info
r_struct
id|siginfo
id|info
suffix:semicolon
DECL|member|uc
r_struct
id|ucontext
id|uc
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|SIGFRAME
mdefine_line|#define&t;SIGFRAME&t;&t;128
DECL|macro|FUNCTIONCALLFRAME
mdefine_line|#define FUNCTIONCALLFRAME&t;96
DECL|macro|PARISC_RT_SIGFRAME_SIZE
mdefine_line|#define PARISC_RT_SIGFRAME_SIZE&t;&t;&t;&t;&t;&bslash;&n;&t;(((sizeof(struct rt_sigframe) + FUNCTIONCALLFRAME) + SIGFRAME) &amp; -SIGFRAME)
macro_line|#endif
eof
