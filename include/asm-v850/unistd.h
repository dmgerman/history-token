multiline_comment|/*&n; * include/asm-v850/unistd.h -- System call numbers and invocation mechanism&n; *&n; *  Copyright (C) 2001,02,03,04  NEC Electronics Corporation&n; *  Copyright (C) 2001,02,03,04  Miles Bader &lt;miles@gnu.org&gt;&n; *&n; * This file is subject to the terms and conditions of the GNU General&n; * Public License.  See the file COPYING in the main directory of this&n; * archive for more details.&n; *&n; * Written by Miles Bader &lt;miles@gnu.org&gt;&n; */
macro_line|#ifndef __V850_UNISTD_H__
DECL|macro|__V850_UNISTD_H__
mdefine_line|#define __V850_UNISTD_H__
macro_line|#include &lt;asm/clinkage.h&gt;
DECL|macro|__NR_restart_syscall
mdefine_line|#define __NR_restart_syscall&t;  0
DECL|macro|__NR_exit
mdefine_line|#define __NR_exit&t;&t;  1
DECL|macro|__NR_fork
mdefine_line|#define __NR_fork&t;&t;  2
DECL|macro|__NR_read
mdefine_line|#define __NR_read&t;&t;  3
DECL|macro|__NR_write
mdefine_line|#define __NR_write&t;&t;  4
DECL|macro|__NR_open
mdefine_line|#define __NR_open&t;&t;  5
DECL|macro|__NR_close
mdefine_line|#define __NR_close&t;&t;  6
DECL|macro|__NR_waitpid
mdefine_line|#define __NR_waitpid&t;&t;  7
DECL|macro|__NR_creat
mdefine_line|#define __NR_creat&t;&t;  8
DECL|macro|__NR_link
mdefine_line|#define __NR_link&t;&t;  9
DECL|macro|__NR_unlink
mdefine_line|#define __NR_unlink&t;&t; 10
DECL|macro|__NR_execve
mdefine_line|#define __NR_execve&t;&t; 11
DECL|macro|__NR_chdir
mdefine_line|#define __NR_chdir&t;&t; 12
DECL|macro|__NR_time
mdefine_line|#define __NR_time&t;&t; 13
DECL|macro|__NR_mknod
mdefine_line|#define __NR_mknod&t;&t; 14
DECL|macro|__NR_chmod
mdefine_line|#define __NR_chmod&t;&t; 15
DECL|macro|__NR_chown
mdefine_line|#define __NR_chown&t;&t; 16
DECL|macro|__NR_break
mdefine_line|#define __NR_break&t;&t; 17
DECL|macro|__NR_lseek
mdefine_line|#define __NR_lseek&t;&t; 19
DECL|macro|__NR_getpid
mdefine_line|#define __NR_getpid&t;&t; 20
DECL|macro|__NR_mount
mdefine_line|#define __NR_mount&t;&t; 21
DECL|macro|__NR_umount
mdefine_line|#define __NR_umount&t;&t; 22
DECL|macro|__NR_setuid
mdefine_line|#define __NR_setuid&t;&t; 23
DECL|macro|__NR_getuid
mdefine_line|#define __NR_getuid&t;&t; 24
DECL|macro|__NR_stime
mdefine_line|#define __NR_stime&t;&t; 25
DECL|macro|__NR_ptrace
mdefine_line|#define __NR_ptrace&t;&t; 26
DECL|macro|__NR_alarm
mdefine_line|#define __NR_alarm&t;&t; 27
DECL|macro|__NR_pause
mdefine_line|#define __NR_pause&t;&t; 29
DECL|macro|__NR_utime
mdefine_line|#define __NR_utime&t;&t; 30
DECL|macro|__NR_stty
mdefine_line|#define __NR_stty&t;&t; 31
DECL|macro|__NR_gtty
mdefine_line|#define __NR_gtty&t;&t; 32
DECL|macro|__NR_access
mdefine_line|#define __NR_access&t;&t; 33
DECL|macro|__NR_nice
mdefine_line|#define __NR_nice&t;&t; 34
DECL|macro|__NR_ftime
mdefine_line|#define __NR_ftime&t;&t; 35
DECL|macro|__NR_sync
mdefine_line|#define __NR_sync&t;&t; 36
DECL|macro|__NR_kill
mdefine_line|#define __NR_kill&t;&t; 37
DECL|macro|__NR_rename
mdefine_line|#define __NR_rename&t;&t; 38
DECL|macro|__NR_mkdir
mdefine_line|#define __NR_mkdir&t;&t; 39
DECL|macro|__NR_rmdir
mdefine_line|#define __NR_rmdir&t;&t; 40
DECL|macro|__NR_dup
mdefine_line|#define __NR_dup&t;&t; 41
DECL|macro|__NR_pipe
mdefine_line|#define __NR_pipe&t;&t; 42
DECL|macro|__NR_times
mdefine_line|#define __NR_times&t;&t; 43
DECL|macro|__NR_prof
mdefine_line|#define __NR_prof&t;&t; 44
DECL|macro|__NR_brk
mdefine_line|#define __NR_brk&t;&t; 45
DECL|macro|__NR_setgid
mdefine_line|#define __NR_setgid&t;&t; 46
DECL|macro|__NR_getgid
mdefine_line|#define __NR_getgid&t;&t; 47
DECL|macro|__NR_signal
mdefine_line|#define __NR_signal&t;&t; 48
DECL|macro|__NR_geteuid
mdefine_line|#define __NR_geteuid&t;&t; 49
DECL|macro|__NR_getegid
mdefine_line|#define __NR_getegid&t;&t; 50
DECL|macro|__NR_acct
mdefine_line|#define __NR_acct&t;&t; 51
DECL|macro|__NR_umount2
mdefine_line|#define __NR_umount2&t;&t; 52
DECL|macro|__NR_lock
mdefine_line|#define __NR_lock&t;&t; 53
DECL|macro|__NR_ioctl
mdefine_line|#define __NR_ioctl&t;&t; 54
DECL|macro|__NR_fcntl
mdefine_line|#define __NR_fcntl&t;&t; 55
DECL|macro|__NR_setpgid
mdefine_line|#define __NR_setpgid&t;&t; 57
DECL|macro|__NR_umask
mdefine_line|#define __NR_umask&t;&t; 60
DECL|macro|__NR_chroot
mdefine_line|#define __NR_chroot&t;&t; 61
DECL|macro|__NR_ustat
mdefine_line|#define __NR_ustat&t;&t; 62
DECL|macro|__NR_dup2
mdefine_line|#define __NR_dup2&t;&t; 63
DECL|macro|__NR_getppid
mdefine_line|#define __NR_getppid&t;&t; 64
DECL|macro|__NR_getpgrp
mdefine_line|#define __NR_getpgrp&t;&t; 65
DECL|macro|__NR_setsid
mdefine_line|#define __NR_setsid&t;&t; 66
DECL|macro|__NR_sigaction
mdefine_line|#define __NR_sigaction&t;&t; 67
DECL|macro|__NR_sgetmask
mdefine_line|#define __NR_sgetmask&t;&t; 68
DECL|macro|__NR_ssetmask
mdefine_line|#define __NR_ssetmask&t;&t; 69
DECL|macro|__NR_setreuid
mdefine_line|#define __NR_setreuid&t;&t; 70
DECL|macro|__NR_setregid
mdefine_line|#define __NR_setregid&t;&t; 71
DECL|macro|__NR_sigsuspend
mdefine_line|#define __NR_sigsuspend&t;&t; 72
DECL|macro|__NR_sigpending
mdefine_line|#define __NR_sigpending&t;&t; 73
DECL|macro|__NR_sethostname
mdefine_line|#define __NR_sethostname&t; 74
DECL|macro|__NR_setrlimit
mdefine_line|#define __NR_setrlimit&t;&t; 75
DECL|macro|__NR_ugetrlimit
mdefine_line|#define __NR_ugetrlimit&t; &t; 76
DECL|macro|__NR_getrusage
mdefine_line|#define __NR_getrusage&t;&t; 77
DECL|macro|__NR_gettimeofday
mdefine_line|#define __NR_gettimeofday&t; 78
DECL|macro|__NR_settimeofday
mdefine_line|#define __NR_settimeofday&t; 79
DECL|macro|__NR_getgroups
mdefine_line|#define __NR_getgroups&t;&t; 80
DECL|macro|__NR_setgroups
mdefine_line|#define __NR_setgroups&t;&t; 81
DECL|macro|__NR_select
mdefine_line|#define __NR_select&t;&t; 82
DECL|macro|__NR_symlink
mdefine_line|#define __NR_symlink&t;&t; 83
DECL|macro|__NR_readlink
mdefine_line|#define __NR_readlink&t;&t; 85
DECL|macro|__NR_uselib
mdefine_line|#define __NR_uselib&t;&t; 86
DECL|macro|__NR_swapon
mdefine_line|#define __NR_swapon&t;&t; 87
DECL|macro|__NR_reboot
mdefine_line|#define __NR_reboot&t;&t; 88
DECL|macro|__NR_readdir
mdefine_line|#define __NR_readdir&t;&t; 89
DECL|macro|__NR_mmap
mdefine_line|#define __NR_mmap&t;&t; 90
DECL|macro|__NR_munmap
mdefine_line|#define __NR_munmap&t;&t; 91
DECL|macro|__NR_truncate
mdefine_line|#define __NR_truncate&t;&t; 92
DECL|macro|__NR_ftruncate
mdefine_line|#define __NR_ftruncate&t;&t; 93
DECL|macro|__NR_fchmod
mdefine_line|#define __NR_fchmod&t;&t; 94
DECL|macro|__NR_fchown
mdefine_line|#define __NR_fchown&t;&t; 95
DECL|macro|__NR_getpriority
mdefine_line|#define __NR_getpriority&t; 96
DECL|macro|__NR_setpriority
mdefine_line|#define __NR_setpriority&t; 97
DECL|macro|__NR_profil
mdefine_line|#define __NR_profil&t;&t; 98
DECL|macro|__NR_statfs
mdefine_line|#define __NR_statfs&t;&t; 99
DECL|macro|__NR_fstatfs
mdefine_line|#define __NR_fstatfs&t;&t;100
DECL|macro|__NR_socketcall
mdefine_line|#define __NR_socketcall&t;&t;102
DECL|macro|__NR_syslog
mdefine_line|#define __NR_syslog&t;&t;103
DECL|macro|__NR_setitimer
mdefine_line|#define __NR_setitimer&t;&t;104
DECL|macro|__NR_getitimer
mdefine_line|#define __NR_getitimer&t;&t;105
DECL|macro|__NR_stat
mdefine_line|#define __NR_stat&t;&t;106
DECL|macro|__NR_lstat
mdefine_line|#define __NR_lstat&t;&t;107
DECL|macro|__NR_fstat
mdefine_line|#define __NR_fstat&t;&t;108
DECL|macro|__NR_vhangup
mdefine_line|#define __NR_vhangup&t;&t;111
DECL|macro|__NR_wait4
mdefine_line|#define __NR_wait4&t;&t;114
DECL|macro|__NR_swapoff
mdefine_line|#define __NR_swapoff&t;&t;115
DECL|macro|__NR_sysinfo
mdefine_line|#define __NR_sysinfo&t;&t;116
DECL|macro|__NR_ipc
mdefine_line|#define __NR_ipc&t;&t;117
DECL|macro|__NR_fsync
mdefine_line|#define __NR_fsync&t;&t;118
DECL|macro|__NR_sigreturn
mdefine_line|#define __NR_sigreturn&t;&t;119
DECL|macro|__NR_clone
mdefine_line|#define __NR_clone&t;&t;120
DECL|macro|__NR_setdomainname
mdefine_line|#define __NR_setdomainname&t;121
DECL|macro|__NR_uname
mdefine_line|#define __NR_uname&t;&t;122
DECL|macro|__NR_cacheflush
mdefine_line|#define __NR_cacheflush&t;&t;123
DECL|macro|__NR_adjtimex
mdefine_line|#define __NR_adjtimex&t;&t;124
DECL|macro|__NR_mprotect
mdefine_line|#define __NR_mprotect&t;&t;125
DECL|macro|__NR_sigprocmask
mdefine_line|#define __NR_sigprocmask&t;126
DECL|macro|__NR_create_module
mdefine_line|#define __NR_create_module&t;127
DECL|macro|__NR_init_module
mdefine_line|#define __NR_init_module&t;128
DECL|macro|__NR_delete_module
mdefine_line|#define __NR_delete_module&t;129
DECL|macro|__NR_get_kernel_syms
mdefine_line|#define __NR_get_kernel_syms&t;130
DECL|macro|__NR_quotactl
mdefine_line|#define __NR_quotactl&t;&t;131
DECL|macro|__NR_getpgid
mdefine_line|#define __NR_getpgid&t;&t;132
DECL|macro|__NR_fchdir
mdefine_line|#define __NR_fchdir&t;&t;133
DECL|macro|__NR_bdflush
mdefine_line|#define __NR_bdflush&t;&t;134
DECL|macro|__NR_sysfs
mdefine_line|#define __NR_sysfs&t;&t;135
DECL|macro|__NR_personality
mdefine_line|#define __NR_personality&t;136
DECL|macro|__NR_afs_syscall
mdefine_line|#define __NR_afs_syscall&t;137 /* Syscall for Andrew File System */
DECL|macro|__NR_setfsuid
mdefine_line|#define __NR_setfsuid&t;&t;138
DECL|macro|__NR_setfsgid
mdefine_line|#define __NR_setfsgid&t;&t;139
DECL|macro|__NR__llseek
mdefine_line|#define __NR__llseek&t;&t;140
DECL|macro|__NR_getdents
mdefine_line|#define __NR_getdents&t;&t;141
DECL|macro|__NR_flock
mdefine_line|#define __NR_flock&t;&t;143
DECL|macro|__NR_msync
mdefine_line|#define __NR_msync&t;&t;144
DECL|macro|__NR_readv
mdefine_line|#define __NR_readv&t;&t;145
DECL|macro|__NR_writev
mdefine_line|#define __NR_writev&t;&t;146
DECL|macro|__NR_getsid
mdefine_line|#define __NR_getsid&t;&t;147
DECL|macro|__NR_fdatasync
mdefine_line|#define __NR_fdatasync&t;&t;148
DECL|macro|__NR__sysctl
mdefine_line|#define __NR__sysctl&t;&t;149
DECL|macro|__NR_mlock
mdefine_line|#define __NR_mlock&t;&t;150
DECL|macro|__NR_munlock
mdefine_line|#define __NR_munlock&t;&t;151
DECL|macro|__NR_mlockall
mdefine_line|#define __NR_mlockall&t;&t;152
DECL|macro|__NR_munlockall
mdefine_line|#define __NR_munlockall&t;&t;153
DECL|macro|__NR_sched_setparam
mdefine_line|#define __NR_sched_setparam&t;&t;154
DECL|macro|__NR_sched_getparam
mdefine_line|#define __NR_sched_getparam&t;&t;155
DECL|macro|__NR_sched_setscheduler
mdefine_line|#define __NR_sched_setscheduler&t;&t;156
DECL|macro|__NR_sched_getscheduler
mdefine_line|#define __NR_sched_getscheduler&t;&t;157
DECL|macro|__NR_sched_yield
mdefine_line|#define __NR_sched_yield&t;&t;158
DECL|macro|__NR_sched_get_priority_max
mdefine_line|#define __NR_sched_get_priority_max&t;159
DECL|macro|__NR_sched_get_priority_min
mdefine_line|#define __NR_sched_get_priority_min&t;160
DECL|macro|__NR_sched_rr_get_interval
mdefine_line|#define __NR_sched_rr_get_interval&t;161
DECL|macro|__NR_nanosleep
mdefine_line|#define __NR_nanosleep&t;&t;162
DECL|macro|__NR_mremap
mdefine_line|#define __NR_mremap&t;&t;163
DECL|macro|__NR_setresuid
mdefine_line|#define __NR_setresuid&t;&t;164
DECL|macro|__NR_getresuid
mdefine_line|#define __NR_getresuid&t;&t;165
DECL|macro|__NR_query_module
mdefine_line|#define __NR_query_module&t;167
DECL|macro|__NR_poll
mdefine_line|#define __NR_poll&t;&t;168
DECL|macro|__NR_nfsservctl
mdefine_line|#define __NR_nfsservctl&t;&t;169
DECL|macro|__NR_setresgid
mdefine_line|#define __NR_setresgid&t;&t;170
DECL|macro|__NR_getresgid
mdefine_line|#define __NR_getresgid&t;&t;171
DECL|macro|__NR_prctl
mdefine_line|#define __NR_prctl&t;&t;172
DECL|macro|__NR_rt_sigreturn
mdefine_line|#define __NR_rt_sigreturn&t;173
DECL|macro|__NR_rt_sigaction
mdefine_line|#define __NR_rt_sigaction&t;174
DECL|macro|__NR_rt_sigprocmask
mdefine_line|#define __NR_rt_sigprocmask&t;175
DECL|macro|__NR_rt_sigpending
mdefine_line|#define __NR_rt_sigpending&t;176
DECL|macro|__NR_rt_sigtimedwait
mdefine_line|#define __NR_rt_sigtimedwait&t;177
DECL|macro|__NR_rt_sigqueueinfo
mdefine_line|#define __NR_rt_sigqueueinfo&t;178
DECL|macro|__NR_rt_sigsuspend
mdefine_line|#define __NR_rt_sigsuspend&t;179
DECL|macro|__NR_pread
mdefine_line|#define __NR_pread&t;&t;180
DECL|macro|__NR_pwrite
mdefine_line|#define __NR_pwrite&t;&t;181
DECL|macro|__NR_lchown
mdefine_line|#define __NR_lchown&t;&t;182
DECL|macro|__NR_getcwd
mdefine_line|#define __NR_getcwd&t;&t;183
DECL|macro|__NR_capget
mdefine_line|#define __NR_capget&t;&t;184
DECL|macro|__NR_capset
mdefine_line|#define __NR_capset&t;&t;185
DECL|macro|__NR_sigaltstack
mdefine_line|#define __NR_sigaltstack&t;186
DECL|macro|__NR_sendfile
mdefine_line|#define __NR_sendfile&t;&t;187
DECL|macro|__NR_getpmsg
mdefine_line|#define __NR_getpmsg&t;&t;188&t;/* some people actually want streams */
DECL|macro|__NR_putpmsg
mdefine_line|#define __NR_putpmsg&t;&t;189&t;/* some people actually want streams */
DECL|macro|__NR_vfork
mdefine_line|#define __NR_vfork&t;&t;190
DECL|macro|__NR_mmap2
mdefine_line|#define __NR_mmap2&t;&t;192
DECL|macro|__NR_truncate64
mdefine_line|#define __NR_truncate64&t;&t;193
DECL|macro|__NR_ftruncate64
mdefine_line|#define __NR_ftruncate64&t;194
DECL|macro|__NR_stat64
mdefine_line|#define __NR_stat64&t;&t;195
DECL|macro|__NR_lstat64
mdefine_line|#define __NR_lstat64&t;&t;196
DECL|macro|__NR_fstat64
mdefine_line|#define __NR_fstat64&t;&t;197
DECL|macro|__NR_fcntl64
mdefine_line|#define __NR_fcntl64&t;&t;198
DECL|macro|__NR_getdents64
mdefine_line|#define __NR_getdents64&t;&t;199
DECL|macro|__NR_pivot_root
mdefine_line|#define __NR_pivot_root&t;&t;200
DECL|macro|__NR_gettid
mdefine_line|#define __NR_gettid&t;&t;201
DECL|macro|__NR_tkill
mdefine_line|#define __NR_tkill&t;&t;202
multiline_comment|/* Syscall protocol:&n;   Syscall number in r12, args in r6-r9, r13-r14&n;   Return value in r10&n;   Trap 0 for `short&squot; syscalls, where all the args can fit in function&n;   call argument registers, and trap 1 when there are additional args in&n;   r13-r14.  */
DECL|macro|SYSCALL_NUM
mdefine_line|#define SYSCALL_NUM&t;&quot;r12&quot;
DECL|macro|SYSCALL_ARG0
mdefine_line|#define SYSCALL_ARG0&t;&quot;r6&quot;
DECL|macro|SYSCALL_ARG1
mdefine_line|#define SYSCALL_ARG1&t;&quot;r7&quot;
DECL|macro|SYSCALL_ARG2
mdefine_line|#define SYSCALL_ARG2&t;&quot;r8&quot;
DECL|macro|SYSCALL_ARG3
mdefine_line|#define SYSCALL_ARG3&t;&quot;r9&quot;
DECL|macro|SYSCALL_ARG4
mdefine_line|#define SYSCALL_ARG4&t;&quot;r13&quot;
DECL|macro|SYSCALL_ARG5
mdefine_line|#define SYSCALL_ARG5&t;&quot;r14&quot;
DECL|macro|SYSCALL_RET
mdefine_line|#define SYSCALL_RET&t;&quot;r10&quot;
DECL|macro|SYSCALL_SHORT_TRAP
mdefine_line|#define SYSCALL_SHORT_TRAP&t;&quot;0&quot;
DECL|macro|SYSCALL_LONG_TRAP
mdefine_line|#define SYSCALL_LONG_TRAP&t;&quot;1&quot;
multiline_comment|/* Registers clobbered by any syscall.  This _doesn&squot;t_ include the syscall&n;   number (r12) or the `extended arg&squot; registers (r13, r14), even though&n;   they are actually clobbered too (this is because gcc&squot;s `asm&squot; statement&n;   doesn&squot;t allow a clobber to be used as an input or output).  */
DECL|macro|SYSCALL_CLOBBERS
mdefine_line|#define SYSCALL_CLOBBERS&t;&quot;r1&quot;, &quot;r5&quot;, &quot;r11&quot;, &quot;r15&quot;, &quot;r16&quot;, &bslash;&n;&t;&t;&t;&t;&quot;r17&quot;, &quot;r18&quot;, &quot;r19&quot;
multiline_comment|/* Registers clobbered by a `short&squot; syscall.  This includes all clobbers&n;   except the syscall number (r12).  */
DECL|macro|SYSCALL_SHORT_CLOBBERS
mdefine_line|#define SYSCALL_SHORT_CLOBBERS&t;SYSCALL_CLOBBERS, &quot;r13&quot;, &quot;r14&quot;
multiline_comment|/* User programs sometimes end up including this header file&n;   (indirectly, via uClibc header files), so I&squot;m a bit nervous just&n;   including &lt;linux/compiler.h&gt;.  */
macro_line|#if !defined(__builtin_expect) &amp;&amp; __GNUC__ == 2 &amp;&amp; __GNUC_MINOR__ &lt; 96
DECL|macro|__builtin_expect
mdefine_line|#define __builtin_expect(x, expected_value) (x)
macro_line|#endif
DECL|macro|__syscall_return
mdefine_line|#define __syscall_return(type, res)&t;&t;&t;&t;&t;      &bslash;&n;  do {&t;&t;&t;&t;&t;&t;&t;&t;&t;      &bslash;&n;&t;  /* user-visible error numbers are in the range -1 - -124:&t;      &bslash;&n;&t;     see &lt;asm-v850/errno.h&gt; */&t;&t;&t;&t;&t;      &bslash;&n;&t;  if (__builtin_expect ((unsigned long)(res) &gt;= (unsigned long)(-125), 0)) { &bslash;&n;&t;&t;  errno = -(res);&t;&t;&t;&t;&t;      &bslash;&n;&t;&t;  res = -1;&t;&t;&t;&t;&t;&t;      &bslash;&n;&t;  }&t;&t;&t;&t;&t;&t;&t;&t;      &bslash;&n;&t;  return (type) (res);&t;&t;&t;&t;&t;&t;      &bslash;&n;  } while (0)
DECL|macro|_syscall0
mdefine_line|#define _syscall0(type, name)&t;&t;&t;&t;&t;&t;      &bslash;&n;type name (void)&t;&t;&t;&t;&t;&t;&t;      &bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;      &bslash;&n;  register unsigned long __syscall __asm__ (SYSCALL_NUM) = __NR_##name;&t;      &bslash;&n;  register unsigned long __ret __asm__ (SYSCALL_RET);&t;&t;&t;      &bslash;&n;  __asm__ __volatile__ (&quot;trap &quot; SYSCALL_SHORT_TRAP&t;&t;&t;      &bslash;&n;&t;&t;&t;: &quot;=r&quot; (__ret), &quot;=r&quot; (__syscall)&t; &t;      &bslash;&n;&t;&t;&t;: &quot;1&quot; (__syscall)&t;&t;&t;&t;      &bslash;&n;&t;&t;&t;: SYSCALL_SHORT_CLOBBERS);&t;&t;&t;      &bslash;&n;  __syscall_return (type, __ret);&t;&t;&t;&t;&t;      &bslash;&n;}
DECL|macro|_syscall1
mdefine_line|#define _syscall1(type, name, atype, a)&t;&t;&t;&t;&t;      &bslash;&n;type name (atype a)&t;&t;&t;&t;&t;&t;&t;      &bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;      &bslash;&n;  register atype __a __asm__ (SYSCALL_ARG0) = a;&t;&t;&t;      &bslash;&n;  register unsigned long __syscall __asm__ (SYSCALL_NUM) = __NR_##name;&t;      &bslash;&n;  register unsigned long __ret __asm__ (SYSCALL_RET);&t;&t;&t;      &bslash;&n;  __asm__ __volatile__ (&quot;trap &quot; SYSCALL_SHORT_TRAP&t;&t;&t;      &bslash;&n;&t;&t;&t;: &quot;=r&quot; (__ret), &quot;=r&quot; (__syscall)&t;&t;      &bslash;&n;&t;&t;&t;: &quot;1&quot; (__syscall), &quot;r&quot; (__a)&t;&t;&t;      &bslash;&n;&t;&t;&t;: SYSCALL_SHORT_CLOBBERS);&t;&t;&t;      &bslash;&n;  __syscall_return (type, __ret);&t;&t;&t;&t;&t;      &bslash;&n;}
DECL|macro|_syscall2
mdefine_line|#define _syscall2(type, name, atype, a, btype, b)&t;&t;&t;      &bslash;&n;type name (atype a, btype b)&t;&t;&t;&t;&t;&t;      &bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;      &bslash;&n;  register atype __a __asm__ (SYSCALL_ARG0) = a;&t;&t;&t;      &bslash;&n;  register btype __b __asm__ (SYSCALL_ARG1) = b;&t;&t;&t;      &bslash;&n;  register unsigned long __syscall __asm__ (SYSCALL_NUM) = __NR_##name;&t;      &bslash;&n;  register unsigned long __ret __asm__ (SYSCALL_RET);&t;&t;&t;      &bslash;&n;  __asm__ __volatile__ (&quot;trap &quot; SYSCALL_SHORT_TRAP&t;&t;&t;      &bslash;&n;&t;&t;&t;: &quot;=r&quot; (__ret), &quot;=r&quot; (__syscall)&t;&t;      &bslash;&n;&t;&t;&t;: &quot;1&quot; (__syscall), &quot;r&quot; (__a), &quot;r&quot; (__b)&t;&t;      &bslash;&n;&t;&t;&t;: SYSCALL_SHORT_CLOBBERS);&t;&t;&t;      &bslash;&n;  __syscall_return (type, __ret);&t;&t;&t;&t;&t;      &bslash;&n;}
DECL|macro|_syscall3
mdefine_line|#define _syscall3(type, name, atype, a, btype, b, ctype, c)&t;&t;      &bslash;&n;type name (atype a, btype b, ctype c)&t;&t;&t;&t;&t;      &bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;      &bslash;&n;  register atype __a __asm__ (SYSCALL_ARG0) = a;&t;&t;&t;      &bslash;&n;  register btype __b __asm__ (SYSCALL_ARG1) = b;&t;&t;&t;      &bslash;&n;  register ctype __c __asm__ (SYSCALL_ARG2) = c;&t;&t;&t;      &bslash;&n;  register unsigned long __syscall __asm__ (SYSCALL_NUM) = __NR_##name;&t;      &bslash;&n;  register unsigned long __ret __asm__ (SYSCALL_RET);&t;&t;&t;      &bslash;&n;  __asm__ __volatile__ (&quot;trap &quot; SYSCALL_SHORT_TRAP&t;&t;&t;      &bslash;&n;&t;&t;&t;: &quot;=r&quot; (__ret), &quot;=r&quot; (__syscall)&t;&t;      &bslash;&n;&t;&t;&t;: &quot;1&quot; (__syscall), &quot;r&quot; (__a), &quot;r&quot; (__b), &quot;r&quot; (__c)    &bslash;&n;&t;&t;&t;: SYSCALL_SHORT_CLOBBERS);&t;&t;&t;      &bslash;&n;  __syscall_return (type, __ret);&t;&t;&t;&t;&t;      &bslash;&n;}
DECL|macro|_syscall4
mdefine_line|#define _syscall4(type, name, atype, a, btype, b, ctype, c, dtype, d)&t;      &bslash;&n;type name (atype a, btype b, ctype c, dtype d)&t;&t;&t;&t;      &bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;      &bslash;&n;  register atype __a __asm__ (SYSCALL_ARG0) = a;&t;&t;&t;      &bslash;&n;  register btype __b __asm__ (SYSCALL_ARG1) = b;&t;&t;&t;      &bslash;&n;  register ctype __c __asm__ (SYSCALL_ARG2) = c;&t;&t;&t;      &bslash;&n;  register dtype __d __asm__ (SYSCALL_ARG3) = d;&t;&t;&t;      &bslash;&n;  register unsigned long __syscall __asm__ (SYSCALL_NUM) = __NR_##name;&t;      &bslash;&n;  register unsigned long __ret __asm__ (SYSCALL_RET);&t;&t;&t;      &bslash;&n;  __asm__ __volatile__ (&quot;trap &quot; SYSCALL_SHORT_TRAP&t;&t;&t;      &bslash;&n;&t;&t;&t;: &quot;=r&quot; (__ret), &quot;=r&quot; (__syscall)&t;&t;      &bslash;&n;&t;&t;&t;: &quot;1&quot; (__syscall),&t;&t;&t;&t;      &bslash;&n;&t;&t;&t;&quot;r&quot; (__a), &quot;r&quot; (__b), &quot;r&quot; (__c), &quot;r&quot; (__d)&t;      &bslash;&n;&t;&t;&t;: SYSCALL_SHORT_CLOBBERS);&t;&t;&t;      &bslash;&n;  __syscall_return (type, __ret);&t;&t;&t;&t;&t;      &bslash;&n;}
DECL|macro|_syscall5
mdefine_line|#define _syscall5(type, name, atype, a, btype, b, ctype, c, dtype, d, etype,e)&bslash;&n;type name (atype a, btype b, ctype c, dtype d, etype e)&t;&t;&t;      &bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;      &bslash;&n;  register atype __a __asm__ (SYSCALL_ARG0) = a;&t;&t;&t;      &bslash;&n;  register btype __b __asm__ (SYSCALL_ARG1) = b;&t;&t;&t;      &bslash;&n;  register ctype __c __asm__ (SYSCALL_ARG2) = c;&t;&t;&t;      &bslash;&n;  register dtype __d __asm__ (SYSCALL_ARG3) = d;&t;&t;&t;      &bslash;&n;  register etype __e __asm__ (SYSCALL_ARG4) = e;&t;&t;&t;      &bslash;&n;  register unsigned long __syscall __asm__ (SYSCALL_NUM) = __NR_##name;&t;      &bslash;&n;  register unsigned long __ret __asm__ (SYSCALL_RET);&t;&t;&t;      &bslash;&n;  __asm__ __volatile__ (&quot;trap &quot; SYSCALL_LONG_TRAP&t;&t;&t;      &bslash;&n;&t;&t;&t;: &quot;=r&quot; (__ret), &quot;=r&quot; (__syscall), &quot;=r&quot; (__e)&t;      &bslash;&n;&t;&t;&t;: &quot;1&quot; (__syscall),&t;&t;&t;&t;      &bslash;&n;&t;&t;&t;&quot;r&quot; (__a), &quot;r&quot; (__b), &quot;r&quot; (__c), &quot;r&quot; (__d), &quot;2&quot; (__e) &bslash;&n;&t;&t;&t;: SYSCALL_CLOBBERS);&t;&t;&t;&t;      &bslash;&n;  __syscall_return (type, __ret);&t;&t;&t;&t;&t;      &bslash;&n;}
macro_line|#if __GNUC__ &lt; 3
multiline_comment|/* In older versions of gcc, `asm&squot; statements with more than 10&n;   input/output arguments produce a fatal error.  To work around this&n;   problem, we use two versions, one for gcc-3.x and one for earlier&n;   versions of gcc (the `earlier gcc&squot; version doesn&squot;t work with gcc-3.x&n;   because gcc-3.x doesn&squot;t allow clobbers to also be input arguments).  */
DECL|macro|__SYSCALL6_TRAP
mdefine_line|#define __SYSCALL6_TRAP(syscall, ret, a, b, c, d, e, f)&t;&t;&t;      &bslash;&n;  __asm__ __volatile__ (&quot;trap &quot; SYSCALL_LONG_TRAP&t;&t;&t;      &bslash;&n;&t;&t;&t;: &quot;=r&quot; (ret), &quot;=r&quot; (syscall)&t;&t;&t;      &bslash;&n;&t;&t;&t;: &quot;1&quot; (syscall),&t;&t;&t;&t;      &bslash;&n;&t;&t;&t;&quot;r&quot; (a), &quot;r&quot; (b), &quot;r&quot; (c), &quot;r&quot; (d),&t;&t;      &bslash;&n; &t;&t;&t;&quot;r&quot; (e), &quot;r&quot; (f)&t;&t;&t;&t;      &bslash;&n;&t;&t;&t;: SYSCALL_CLOBBERS, SYSCALL_ARG4, SYSCALL_ARG5);
macro_line|#else /* __GNUC__ &gt;= 3 */
DECL|macro|__SYSCALL6_TRAP
mdefine_line|#define __SYSCALL6_TRAP(syscall, ret, a, b, c, d, e, f)&t;&t;&t;      &bslash;&n;  __asm__ __volatile__ (&quot;trap &quot; SYSCALL_LONG_TRAP&t;&t;&t;      &bslash;&n;&t;&t;&t;: &quot;=r&quot; (ret), &quot;=r&quot; (syscall),&t;&t;&t;      &bslash;&n; &t;&t;&t;&quot;=r&quot; (e), &quot;=r&quot; (f)&t;&t;&t;&t;      &bslash;&n;&t;&t;&t;: &quot;1&quot; (syscall),&t;&t;&t;&t;      &bslash;&n;&t;&t;&t;&quot;r&quot; (a), &quot;r&quot; (b), &quot;r&quot; (c), &quot;r&quot; (d),&t;&t;      &bslash;&n;&t;&t;&t;&quot;2&quot; (e), &quot;3&quot; (f)&t;&t;&t;&t;      &bslash;&n;&t;&t;&t;: SYSCALL_CLOBBERS);
macro_line|#endif
DECL|macro|_syscall6
mdefine_line|#define _syscall6(type, name, atype, a, btype, b, ctype, c, dtype, d, etype, e, ftype, f) &bslash;&n;type name (atype a, btype b, ctype c, dtype d, etype e, ftype f)&t;      &bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;      &bslash;&n;  register atype __a __asm__ (SYSCALL_ARG0) = a;&t;&t;&t;      &bslash;&n;  register btype __b __asm__ (SYSCALL_ARG1) = b;&t;&t;&t;      &bslash;&n;  register ctype __c __asm__ (SYSCALL_ARG2) = c;&t;&t;&t;      &bslash;&n;  register dtype __d __asm__ (SYSCALL_ARG3) = d;&t;&t;&t;      &bslash;&n;  register etype __e __asm__ (SYSCALL_ARG4) = e;&t;&t;&t;      &bslash;&n;  register etype __f __asm__ (SYSCALL_ARG5) = f;&t;&t;&t;      &bslash;&n;  register unsigned long __syscall __asm__ (SYSCALL_NUM) = __NR_##name;&t;      &bslash;&n;  register unsigned long __ret __asm__ (SYSCALL_RET);&t;&t;&t;      &bslash;&n;  __SYSCALL6_TRAP(__syscall, __ret, __a, __b, __c, __d, __e, __f);&t;      &bslash;&n;  __syscall_return (type, __ret);&t;&t;&t;&t;&t;      &bslash;&n;}
macro_line|#ifdef __KERNEL__
DECL|macro|__ARCH_WANT_IPC_PARSE_VERSION
mdefine_line|#define __ARCH_WANT_IPC_PARSE_VERSION
DECL|macro|__ARCH_WANT_OLD_READDIR
mdefine_line|#define __ARCH_WANT_OLD_READDIR
DECL|macro|__ARCH_WANT_STAT64
mdefine_line|#define __ARCH_WANT_STAT64
DECL|macro|__ARCH_WANT_SYS_ALARM
mdefine_line|#define __ARCH_WANT_SYS_ALARM
DECL|macro|__ARCH_WANT_SYS_GETHOSTNAME
mdefine_line|#define __ARCH_WANT_SYS_GETHOSTNAME
DECL|macro|__ARCH_WANT_SYS_PAUSE
mdefine_line|#define __ARCH_WANT_SYS_PAUSE
DECL|macro|__ARCH_WANT_SYS_SGETMASK
mdefine_line|#define __ARCH_WANT_SYS_SGETMASK
DECL|macro|__ARCH_WANT_SYS_SIGNAL
mdefine_line|#define __ARCH_WANT_SYS_SIGNAL
DECL|macro|__ARCH_WANT_SYS_TIME
mdefine_line|#define __ARCH_WANT_SYS_TIME
DECL|macro|__ARCH_WANT_SYS_UTIME
mdefine_line|#define __ARCH_WANT_SYS_UTIME
DECL|macro|__ARCH_WANT_SYS_WAITPID
mdefine_line|#define __ARCH_WANT_SYS_WAITPID
DECL|macro|__ARCH_WANT_SYS_SOCKETCALL
mdefine_line|#define __ARCH_WANT_SYS_SOCKETCALL
DECL|macro|__ARCH_WANT_SYS_FADVISE64
mdefine_line|#define __ARCH_WANT_SYS_FADVISE64
DECL|macro|__ARCH_WANT_SYS_GETPGRP
mdefine_line|#define __ARCH_WANT_SYS_GETPGRP
DECL|macro|__ARCH_WANT_SYS_LLSEEK
mdefine_line|#define __ARCH_WANT_SYS_LLSEEK
DECL|macro|__ARCH_WANT_SYS_NICE
mdefine_line|#define __ARCH_WANT_SYS_NICE
DECL|macro|__ARCH_WANT_SYS_OLDUMOUNT
mdefine_line|#define __ARCH_WANT_SYS_OLDUMOUNT
DECL|macro|__ARCH_WANT_SYS_SIGPENDING
mdefine_line|#define __ARCH_WANT_SYS_SIGPENDING
DECL|macro|__ARCH_WANT_SYS_SIGPROCMASK
mdefine_line|#define __ARCH_WANT_SYS_SIGPROCMASK
DECL|macro|__ARCH_WANT_SYS_RT_SIGACTION
mdefine_line|#define __ARCH_WANT_SYS_RT_SIGACTION
macro_line|#endif
macro_line|#ifdef __KERNEL_SYSCALLS__
macro_line|#include &lt;linux/compiler.h&gt;
macro_line|#include &lt;linux/types.h&gt;
multiline_comment|/*&n; * we need this inline - forking from kernel space will result&n; * in NO COPY ON WRITE (!!!), until an execve is executed. This&n; * is no problem, but for the stack. This is handled by not letting&n; * main() use the stack at all after fork(). Thus, no function&n; * calls - which means inline code for fork too, as otherwise we&n; * would use the stack upon exit from &squot;fork()&squot;.&n; *&n; * Actually only pause and fork are needed inline, so that there&n; * won&squot;t be any messing with the stack from main(), but we define&n; * some others too.&n; */
DECL|macro|__NR__exit
mdefine_line|#define __NR__exit __NR_exit
r_extern
r_inline
id|_syscall0
c_func
(paren
id|pid_t
comma
id|setsid
)paren
r_extern
r_inline
id|_syscall3
c_func
(paren
r_int
comma
id|write
comma
r_int
comma
id|fd
comma
r_const
r_char
op_star
comma
id|buf
comma
id|off_t
comma
id|count
)paren
r_extern
r_inline
id|_syscall3
c_func
(paren
r_int
comma
id|read
comma
r_int
comma
id|fd
comma
r_char
op_star
comma
id|buf
comma
id|off_t
comma
id|count
)paren
r_extern
r_inline
id|_syscall3
c_func
(paren
id|off_t
comma
id|lseek
comma
r_int
comma
id|fd
comma
id|off_t
comma
id|offset
comma
r_int
comma
id|count
)paren
r_extern
r_inline
id|_syscall1
c_func
(paren
r_int
comma
id|dup
comma
r_int
comma
id|fd
)paren
r_extern
r_inline
id|_syscall3
c_func
(paren
r_int
comma
id|execve
comma
r_const
r_char
op_star
comma
id|file
comma
r_char
op_star
op_star
comma
id|argv
comma
r_char
op_star
op_star
comma
id|envp
)paren
r_extern
r_inline
id|_syscall3
c_func
(paren
r_int
comma
id|open
comma
r_const
r_char
op_star
comma
id|file
comma
r_int
comma
id|flag
comma
r_int
comma
id|mode
)paren
r_extern
r_inline
id|_syscall1
c_func
(paren
r_int
comma
id|close
comma
r_int
comma
id|fd
)paren
r_extern
r_inline
id|_syscall1
c_func
(paren
r_int
comma
id|_exit
comma
r_int
comma
id|exitcode
)paren
r_extern
r_inline
id|_syscall3
c_func
(paren
id|pid_t
comma
id|waitpid
comma
id|pid_t
comma
id|pid
comma
r_int
op_star
comma
id|wait_stat
comma
r_int
comma
id|options
)paren
DECL|function|wait
r_extern
r_inline
id|pid_t
id|wait
c_func
(paren
r_int
op_star
id|wait_stat
)paren
(brace
r_return
id|waitpid
(paren
op_minus
l_int|1
comma
id|wait_stat
comma
l_int|0
)paren
suffix:semicolon
)brace
r_int
r_int
id|sys_mmap
c_func
(paren
r_int
r_int
id|addr
comma
r_int
id|len
comma
r_int
r_int
id|prot
comma
r_int
r_int
id|flags
comma
r_int
r_int
id|fd
comma
id|off_t
id|offset
)paren
suffix:semicolon
r_int
r_int
id|sys_mmap2
c_func
(paren
r_int
r_int
id|addr
comma
r_int
id|len
comma
r_int
r_int
id|prot
comma
r_int
r_int
id|flags
comma
r_int
r_int
id|fd
comma
r_int
r_int
id|pgoff
)paren
suffix:semicolon
r_struct
id|pt_regs
suffix:semicolon
r_int
id|sys_execve
(paren
r_char
op_star
id|name
comma
r_char
op_star
op_star
id|argv
comma
r_char
op_star
op_star
id|envp
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_int
id|sys_pipe
(paren
r_int
op_star
id|fildes
)paren
suffix:semicolon
r_int
id|sys_ptrace
c_func
(paren
r_int
id|request
comma
r_int
id|pid
comma
r_int
id|addr
comma
r_int
id|data
)paren
suffix:semicolon
r_struct
id|sigaction
suffix:semicolon
id|asmlinkage
r_int
id|sys_rt_sigaction
c_func
(paren
r_int
id|sig
comma
r_const
r_struct
id|sigaction
id|__user
op_star
id|act
comma
r_struct
id|sigaction
id|__user
op_star
id|oact
comma
r_int
id|sigsetsize
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * &quot;Conditional&quot; syscalls&n; */
DECL|macro|cond_syscall
mdefine_line|#define cond_syscall(name)&t;&t;&t;&t;&t;&t;      &bslash;&n;  asm (&quot;.weak&bslash;t&quot; C_SYMBOL_STRING(name) &quot;;&quot;&t;&t;&t;&t;      &bslash;&n;       &quot;.set&bslash;t&quot; C_SYMBOL_STRING(name) &quot;,&quot; C_SYMBOL_STRING(sys_ni_syscall))
macro_line|#if 0
multiline_comment|/* This doesn&squot;t work if there&squot;s a function prototype for NAME visible,&n;   because the argument types probably won&squot;t match.  */
mdefine_line|#define cond_syscall(name)  &bslash;&n;  void name (void) __attribute__ ((weak, alias (&quot;sys_ni_syscall&quot;)));
macro_line|#endif
macro_line|#endif /* __V850_UNISTD_H__ */
eof
