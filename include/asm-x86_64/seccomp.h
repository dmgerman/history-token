macro_line|#ifndef _ASM_SECCOMP_H
macro_line|#include &lt;linux/thread_info.h&gt;
macro_line|#ifdef TIF_32BIT
macro_line|#error &quot;unexpected TIF_32BIT on x86_64&quot;
macro_line|#else
DECL|macro|TIF_32BIT
mdefine_line|#define TIF_32BIT TIF_IA32
macro_line|#endif
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;asm/ia32_unistd.h&gt;
DECL|macro|__NR_seccomp_read
mdefine_line|#define __NR_seccomp_read __NR_read
DECL|macro|__NR_seccomp_write
mdefine_line|#define __NR_seccomp_write __NR_write
DECL|macro|__NR_seccomp_exit
mdefine_line|#define __NR_seccomp_exit __NR_exit
DECL|macro|__NR_seccomp_sigreturn
mdefine_line|#define __NR_seccomp_sigreturn __NR_rt_sigreturn
DECL|macro|__NR_seccomp_read_32
mdefine_line|#define __NR_seccomp_read_32 __NR_ia32_read
DECL|macro|__NR_seccomp_write_32
mdefine_line|#define __NR_seccomp_write_32 __NR_ia32_write
DECL|macro|__NR_seccomp_exit_32
mdefine_line|#define __NR_seccomp_exit_32 __NR_ia32_exit
DECL|macro|__NR_seccomp_sigreturn_32
mdefine_line|#define __NR_seccomp_sigreturn_32 __NR_ia32_sigreturn
macro_line|#endif /* _ASM_SECCOMP_H */
eof
