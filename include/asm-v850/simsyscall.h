multiline_comment|/*&n; * include/asm-v850/simsyscall.h -- `System calls&squot; under the v850e emulator&n; *&n; *  Copyright (C) 2001  NEC Corporation&n; *  Copyright (C) 2001  Miles Bader &lt;miles@gnu.org&gt;&n; *&n; * This file is subject to the terms and conditions of the GNU General&n; * Public License.  See the file COPYING in the main directory of this&n; * archive for more details.&n; *&n; * Written by Miles Bader &lt;miles@gnu.org&gt;&n; */
macro_line|#ifndef __V850_SIMSYSCALL_H__
DECL|macro|__V850_SIMSYSCALL_H__
mdefine_line|#define __V850_SIMSYSCALL_H__
DECL|macro|V850_SIM_SYS_exit
mdefine_line|#define V850_SIM_SYS_exit(a...)&t;&t;V850_SIM_SYSCALL_1 (1&t;, ##a)
DECL|macro|V850_SIM_SYS_fork
mdefine_line|#define V850_SIM_SYS_fork(a...)&t;&t;V850_SIM_SYSCALL_0 (2&t;, ##a)
DECL|macro|V850_SIM_SYS_read
mdefine_line|#define V850_SIM_SYS_read(a...)&t;&t;V850_SIM_SYSCALL_3 (3&t;, ##a)
DECL|macro|V850_SIM_SYS_write
mdefine_line|#define V850_SIM_SYS_write(a...)&t;V850_SIM_SYSCALL_3 (4&t;, ##a)
DECL|macro|V850_SIM_SYS_open
mdefine_line|#define V850_SIM_SYS_open(a...)&t;&t;V850_SIM_SYSCALL_2 (5&t;, ##a)
DECL|macro|V850_SIM_SYS_close
mdefine_line|#define V850_SIM_SYS_close(a...)&t;V850_SIM_SYSCALL_1 (6&t;, ##a)
DECL|macro|V850_SIM_SYS_wait4
mdefine_line|#define V850_SIM_SYS_wait4(a...)&t;V850_SIM_SYSCALL_4 (7&t;, ##a)
multiline_comment|/* #define V850_SIM_SYS_creat(a...)&t;V850_SIM_SYSCALL_1 (8&t;, ##a) */
multiline_comment|/* #define V850_SIM_SYS_link(a...)&t;V850_SIM_SYSCALL_1 (9&t;, ##a) */
multiline_comment|/* #define V850_SIM_SYS_unlink(a...)&t;V850_SIM_SYSCALL_1 (10&t;, ##a) */
DECL|macro|V850_SIM_SYS_execv
mdefine_line|#define V850_SIM_SYS_execv(a...)&t;V850_SIM_SYSCALL_2 (11&t;, ##a)
multiline_comment|/* #define V850_SIM_SYS_chdir(a...)&t;V850_SIM_SYSCALL_1 (12&t;, ##a) */
multiline_comment|/* #define V850_SIM_SYS_mknod(a...)&t;V850_SIM_SYSCALL_1 (14&t;, ##a) */
DECL|macro|V850_SIM_SYS_chmod
mdefine_line|#define V850_SIM_SYS_chmod(a...)&t;V850_SIM_SYSCALL_2 (15&t;, ##a)
DECL|macro|V850_SIM_SYS_chown
mdefine_line|#define V850_SIM_SYS_chown(a...)&t;V850_SIM_SYSCALL_2 (16&t;, ##a)
DECL|macro|V850_SIM_SYS_lseek
mdefine_line|#define V850_SIM_SYS_lseek(a...)&t;V850_SIM_SYSCALL_3 (19&t;, ##a)
multiline_comment|/* #define V850_SIM_SYS_getpid(a...)&t;V850_SIM_SYSCALL_1 (20&t;, ##a) */
multiline_comment|/* #define V850_SIM_SYS_isatty(a...)&t;V850_SIM_SYSCALL_1 (21&t;, ##a) */
multiline_comment|/* #define V850_SIM_SYS_fstat(a...)&t;V850_SIM_SYSCALL_1 (22&t;, ##a) */
DECL|macro|V850_SIM_SYS_time
mdefine_line|#define V850_SIM_SYS_time(a...)&t;&t;V850_SIM_SYSCALL_1 (23&t;, ##a)
DECL|macro|V850_SIM_SYS_poll
mdefine_line|#define V850_SIM_SYS_poll(a...)&t;&t;V850_SIM_SYSCALL_3 (24&t;, ##a)
DECL|macro|V850_SIM_SYS_stat
mdefine_line|#define V850_SIM_SYS_stat(a...)&t;&t;V850_SIM_SYSCALL_2 (38&t;, ##a)
DECL|macro|V850_SIM_SYS_pipe
mdefine_line|#define V850_SIM_SYS_pipe(a...)&t;&t;V850_SIM_SYSCALL_1 (42&t;, ##a)
DECL|macro|V850_SIM_SYS_times
mdefine_line|#define V850_SIM_SYS_times(a...)&t;V850_SIM_SYSCALL_1 (43&t;, ##a)
DECL|macro|V850_SIM_SYS_execve
mdefine_line|#define V850_SIM_SYS_execve(a...)&t;V850_SIM_SYSCALL_3 (59&t;, ##a)
DECL|macro|V850_SIM_SYS_gettimeofday
mdefine_line|#define V850_SIM_SYS_gettimeofday(a...)&t;V850_SIM_SYSCALL_2 (116&t;, ##a)
multiline_comment|/* #define V850_SIM_SYS_utime(a...)&t;V850_SIM_SYSCALL_2 (201&t;, ##a) */
multiline_comment|/* #define V850_SIM_SYS_wait(a...)&t;V850_SIM_SYSCALL_1 (202&t;, ##a) */
DECL|macro|V850_SIM_SYS_make_raw
mdefine_line|#define V850_SIM_SYS_make_raw(a...)&t;V850_SIM_SYSCALL_1 (1024 , ##a)
DECL|macro|V850_SIM_SYSCALL_0
mdefine_line|#define V850_SIM_SYSCALL_0(_call)&t;&t;&t;&t;&t;      &bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;      &bslash;&n;&t;register int call __asm__ (&quot;r6&quot;) = _call;&t;&t;&t;      &bslash;&n;&t;register int rval __asm__ (&quot;r10&quot;);&t;&t;&t;&t;      &bslash;&n;&t;__asm__ __volatile__ (&quot;trap 31&quot;&t;&t;&t;&t;&t;      &bslash;&n;&t;&t;&t;      : &quot;=r&quot; (rval)&t;&t;&t;&t;      &bslash;&n;&t;&t;&t;      : &quot;r&quot; (call)&t;&t;&t;&t;      &bslash;&n;&t;&t;&t;      : &quot;r11&quot;, &quot;memory&quot;);&t;&t;&t;      &bslash;&n;&t;rval;&t;&t;&t;&t;&t;&t;&t;&t;      &bslash;&n;})
DECL|macro|V850_SIM_SYSCALL_1
mdefine_line|#define V850_SIM_SYSCALL_1(_call, _arg0)&t;&t;&t;&t;      &bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;      &bslash;&n;&t;register int call __asm__ (&quot;r6&quot;) = _call;&t;&t;&t;      &bslash;&n;&t;register long arg0 __asm__ (&quot;r7&quot;) = (long)_arg0;&t;&t;      &bslash;&n;&t;register int rval __asm__ (&quot;r10&quot;);&t;&t;&t;&t;      &bslash;&n;&t;__asm__ __volatile__ (&quot;trap 31&quot;&t;&t;&t;&t;&t;      &bslash;&n;&t;&t;&t;      : &quot;=r&quot; (rval)&t;&t;&t;&t;      &bslash;&n;&t;&t;&t;      : &quot;r&quot; (call), &quot;r&quot; (arg0)&t;&t;&t;      &bslash;&n;&t;&t;&t;      : &quot;r11&quot;, &quot;memory&quot;);&t;&t;&t;      &bslash;&n;&t;rval;&t;&t;&t;&t;&t;&t;&t;&t;      &bslash;&n;})
DECL|macro|V850_SIM_SYSCALL_2
mdefine_line|#define V850_SIM_SYSCALL_2(_call, _arg0, _arg1)&t;&t;&t;&t;      &bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;      &bslash;&n;&t;register int call __asm__ (&quot;r6&quot;) = _call;&t;&t;&t;      &bslash;&n;&t;register long arg0 __asm__ (&quot;r7&quot;) = (long)_arg0;&t;&t;      &bslash;&n;&t;register long arg1 __asm__ (&quot;r8&quot;) = (long)_arg1;&t;&t;      &bslash;&n;&t;register int rval __asm__ (&quot;r10&quot;);&t;&t;&t;&t;      &bslash;&n;&t;__asm__ __volatile__ (&quot;trap 31&quot;&t;&t;&t;&t;&t;      &bslash;&n;&t;&t;&t;      : &quot;=r&quot; (rval)&t;&t;&t;&t;      &bslash;&n;&t;&t;&t;      : &quot;r&quot; (call), &quot;r&quot; (arg0), &quot;r&quot; (arg1)&t;      &bslash;&n;&t;&t;&t;      : &quot;r11&quot;, &quot;memory&quot;);&t;&t;&t;      &bslash;&n;&t;rval;&t;&t;&t;&t;&t;&t;&t;&t;      &bslash;&n;})
DECL|macro|V850_SIM_SYSCALL_3
mdefine_line|#define V850_SIM_SYSCALL_3(_call, _arg0, _arg1, _arg2)&t;&t;&t;      &bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;      &bslash;&n;&t;register int call __asm__ (&quot;r6&quot;) = _call;&t;&t;&t;      &bslash;&n;&t;register long arg0 __asm__ (&quot;r7&quot;) = (long)_arg0;&t;&t;      &bslash;&n;&t;register long arg1 __asm__ (&quot;r8&quot;) = (long)_arg1;&t;&t;      &bslash;&n;&t;register long arg2 __asm__ (&quot;r9&quot;) = (long)_arg2;&t;&t;      &bslash;&n;&t;register int rval __asm__ (&quot;r10&quot;);&t;&t;&t;&t;      &bslash;&n;&t;__asm__ __volatile__ (&quot;trap 31&quot;&t;&t;&t;&t;&t;      &bslash;&n;&t;&t;&t;      : &quot;=r&quot; (rval)&t;&t;&t;&t;      &bslash;&n;&t;&t;&t;      : &quot;r&quot; (call), &quot;r&quot; (arg0), &quot;r&quot; (arg1), &quot;r&quot; (arg2)&bslash;&n;&t;&t;&t;      : &quot;r11&quot;, &quot;memory&quot;);&t;&t;&t;      &bslash;&n;&t;rval;&t;&t;&t;&t;&t;&t;&t;&t;      &bslash;&n;})
DECL|macro|V850_SIM_SYSCALL
mdefine_line|#define V850_SIM_SYSCALL(call, args...) &bslash;&n;   V850_SIM_SYS_##call (args)
macro_line|#endif /* __V850_SIMSYSCALL_H__ */
eof
