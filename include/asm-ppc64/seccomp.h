macro_line|#ifndef _ASM_SECCOMP_H
macro_line|#include &lt;linux/thread_info.h&gt; /* already defines TIF_32BIT */
macro_line|#ifndef TIF_32BIT
macro_line|#error &quot;unexpected TIF_32BIT on ppc64&quot;
macro_line|#endif
macro_line|#include &lt;linux/unistd.h&gt;
DECL|macro|__NR_seccomp_read
mdefine_line|#define __NR_seccomp_read __NR_read
DECL|macro|__NR_seccomp_write
mdefine_line|#define __NR_seccomp_write __NR_write
DECL|macro|__NR_seccomp_exit
mdefine_line|#define __NR_seccomp_exit __NR_exit
DECL|macro|__NR_seccomp_sigreturn
mdefine_line|#define __NR_seccomp_sigreturn __NR_rt_sigreturn
DECL|macro|__NR_seccomp_read_32
mdefine_line|#define __NR_seccomp_read_32 __NR_read
DECL|macro|__NR_seccomp_write_32
mdefine_line|#define __NR_seccomp_write_32 __NR_write
DECL|macro|__NR_seccomp_exit_32
mdefine_line|#define __NR_seccomp_exit_32 __NR_exit
DECL|macro|__NR_seccomp_sigreturn_32
mdefine_line|#define __NR_seccomp_sigreturn_32 __NR_sigreturn
macro_line|#endif /* _ASM_SECCOMP_H */
eof
