macro_line|#ifndef _ASM_X86_64_IA32_UNISTD_H_
DECL|macro|_ASM_X86_64_IA32_UNISTD_H_
mdefine_line|#define _ASM_X86_64_IA32_UNISTD_H_
multiline_comment|/*&n; * This file contains the system call numbers of the ia32 port,&n; * this is for the kernel only.&n; */
DECL|macro|__NR_ia32_exit
mdefine_line|#define __NR_ia32_exit&t;&t;  1
DECL|macro|__NR_ia32_fork
mdefine_line|#define __NR_ia32_fork&t;&t;  2
DECL|macro|__NR_ia32_read
mdefine_line|#define __NR_ia32_read&t;&t;  3
DECL|macro|__NR_ia32_write
mdefine_line|#define __NR_ia32_write&t;&t;  4
DECL|macro|__NR_ia32_open
mdefine_line|#define __NR_ia32_open&t;&t;  5
DECL|macro|__NR_ia32_close
mdefine_line|#define __NR_ia32_close&t;&t;  6
DECL|macro|__NR_ia32_waitpid
mdefine_line|#define __NR_ia32_waitpid&t;&t;  7
DECL|macro|__NR_ia32_creat
mdefine_line|#define __NR_ia32_creat&t;&t;  8
DECL|macro|__NR_ia32_link
mdefine_line|#define __NR_ia32_link&t;&t;  9
DECL|macro|__NR_ia32_unlink
mdefine_line|#define __NR_ia32_unlink&t;&t; 10
DECL|macro|__NR_ia32_execve
mdefine_line|#define __NR_ia32_execve&t;&t; 11
DECL|macro|__NR_ia32_chdir
mdefine_line|#define __NR_ia32_chdir&t;&t; 12
DECL|macro|__NR_ia32_time
mdefine_line|#define __NR_ia32_time&t;&t; 13
DECL|macro|__NR_ia32_mknod
mdefine_line|#define __NR_ia32_mknod&t;&t; 14
DECL|macro|__NR_ia32_chmod
mdefine_line|#define __NR_ia32_chmod&t;&t; 15
DECL|macro|__NR_ia32_lchown
mdefine_line|#define __NR_ia32_lchown&t;&t; 16
DECL|macro|__NR_ia32_break
mdefine_line|#define __NR_ia32_break&t;&t; 17
DECL|macro|__NR_ia32_oldstat
mdefine_line|#define __NR_ia32_oldstat&t;&t; 18
DECL|macro|__NR_ia32_lseek
mdefine_line|#define __NR_ia32_lseek&t;&t; 19
DECL|macro|__NR_ia32_getpid
mdefine_line|#define __NR_ia32_getpid&t;&t; 20
DECL|macro|__NR_ia32_mount
mdefine_line|#define __NR_ia32_mount&t;&t; 21
DECL|macro|__NR_ia32_umount
mdefine_line|#define __NR_ia32_umount&t;&t; 22
DECL|macro|__NR_ia32_setuid
mdefine_line|#define __NR_ia32_setuid&t;&t; 23
DECL|macro|__NR_ia32_getuid
mdefine_line|#define __NR_ia32_getuid&t;&t; 24
DECL|macro|__NR_ia32_stime
mdefine_line|#define __NR_ia32_stime&t;&t; 25
DECL|macro|__NR_ia32_ptrace
mdefine_line|#define __NR_ia32_ptrace&t;&t; 26
DECL|macro|__NR_ia32_alarm
mdefine_line|#define __NR_ia32_alarm&t;&t; 27
DECL|macro|__NR_ia32_oldfstat
mdefine_line|#define __NR_ia32_oldfstat&t;&t; 28
DECL|macro|__NR_ia32_pause
mdefine_line|#define __NR_ia32_pause&t;&t; 29
DECL|macro|__NR_ia32_utime
mdefine_line|#define __NR_ia32_utime&t;&t; 30
DECL|macro|__NR_ia32_stty
mdefine_line|#define __NR_ia32_stty&t;&t; 31
DECL|macro|__NR_ia32_gtty
mdefine_line|#define __NR_ia32_gtty&t;&t; 32
DECL|macro|__NR_ia32_access
mdefine_line|#define __NR_ia32_access&t;&t; 33
DECL|macro|__NR_ia32_nice
mdefine_line|#define __NR_ia32_nice&t;&t; 34
DECL|macro|__NR_ia32_ftime
mdefine_line|#define __NR_ia32_ftime&t;&t; 35
DECL|macro|__NR_ia32_sync
mdefine_line|#define __NR_ia32_sync&t;&t; 36
DECL|macro|__NR_ia32_kill
mdefine_line|#define __NR_ia32_kill&t;&t; 37
DECL|macro|__NR_ia32_rename
mdefine_line|#define __NR_ia32_rename&t;&t; 38
DECL|macro|__NR_ia32_mkdir
mdefine_line|#define __NR_ia32_mkdir&t;&t; 39
DECL|macro|__NR_ia32_rmdir
mdefine_line|#define __NR_ia32_rmdir&t;&t; 40
DECL|macro|__NR_ia32_dup
mdefine_line|#define __NR_ia32_dup&t;&t; 41
DECL|macro|__NR_ia32_pipe
mdefine_line|#define __NR_ia32_pipe&t;&t; 42
DECL|macro|__NR_ia32_times
mdefine_line|#define __NR_ia32_times&t;&t; 43
DECL|macro|__NR_ia32_prof
mdefine_line|#define __NR_ia32_prof&t;&t; 44
DECL|macro|__NR_ia32_brk
mdefine_line|#define __NR_ia32_brk&t;&t; 45
DECL|macro|__NR_ia32_setgid
mdefine_line|#define __NR_ia32_setgid&t;&t; 46
DECL|macro|__NR_ia32_getgid
mdefine_line|#define __NR_ia32_getgid&t;&t; 47
DECL|macro|__NR_ia32_signal
mdefine_line|#define __NR_ia32_signal&t;&t; 48
DECL|macro|__NR_ia32_geteuid
mdefine_line|#define __NR_ia32_geteuid&t;&t; 49
DECL|macro|__NR_ia32_getegid
mdefine_line|#define __NR_ia32_getegid&t;&t; 50
DECL|macro|__NR_ia32_acct
mdefine_line|#define __NR_ia32_acct&t;&t; 51
DECL|macro|__NR_ia32_umount2
mdefine_line|#define __NR_ia32_umount2&t;&t; 52
DECL|macro|__NR_ia32_lock
mdefine_line|#define __NR_ia32_lock&t;&t; 53
DECL|macro|__NR_ia32_ioctl
mdefine_line|#define __NR_ia32_ioctl&t;&t; 54
DECL|macro|__NR_ia32_fcntl
mdefine_line|#define __NR_ia32_fcntl&t;&t; 55
DECL|macro|__NR_ia32_mpx
mdefine_line|#define __NR_ia32_mpx&t;&t; 56
DECL|macro|__NR_ia32_setpgid
mdefine_line|#define __NR_ia32_setpgid&t;&t; 57
DECL|macro|__NR_ia32_ulimit
mdefine_line|#define __NR_ia32_ulimit&t;&t; 58
DECL|macro|__NR_ia32_oldolduname
mdefine_line|#define __NR_ia32_oldolduname&t; 59
DECL|macro|__NR_ia32_umask
mdefine_line|#define __NR_ia32_umask&t;&t; 60
DECL|macro|__NR_ia32_chroot
mdefine_line|#define __NR_ia32_chroot&t;&t; 61
DECL|macro|__NR_ia32_ustat
mdefine_line|#define __NR_ia32_ustat&t;&t; 62
DECL|macro|__NR_ia32_dup2
mdefine_line|#define __NR_ia32_dup2&t;&t; 63
DECL|macro|__NR_ia32_getppid
mdefine_line|#define __NR_ia32_getppid&t;&t; 64
DECL|macro|__NR_ia32_getpgrp
mdefine_line|#define __NR_ia32_getpgrp&t;&t; 65
DECL|macro|__NR_ia32_setsid
mdefine_line|#define __NR_ia32_setsid&t;&t; 66
DECL|macro|__NR_ia32_sigaction
mdefine_line|#define __NR_ia32_sigaction&t;&t; 67
DECL|macro|__NR_ia32_sgetmask
mdefine_line|#define __NR_ia32_sgetmask&t;&t; 68
DECL|macro|__NR_ia32_ssetmask
mdefine_line|#define __NR_ia32_ssetmask&t;&t; 69
DECL|macro|__NR_ia32_setreuid
mdefine_line|#define __NR_ia32_setreuid&t;&t; 70
DECL|macro|__NR_ia32_setregid
mdefine_line|#define __NR_ia32_setregid&t;&t; 71
DECL|macro|__NR_ia32_sigsuspend
mdefine_line|#define __NR_ia32_sigsuspend&t;&t; 72
DECL|macro|__NR_ia32_sigpending
mdefine_line|#define __NR_ia32_sigpending&t;&t; 73
DECL|macro|__NR_ia32_sethostname
mdefine_line|#define __NR_ia32_sethostname&t; 74
DECL|macro|__NR_ia32_setrlimit
mdefine_line|#define __NR_ia32_setrlimit&t;&t; 75
DECL|macro|__NR_ia32_getrlimit
mdefine_line|#define __NR_ia32_getrlimit&t;&t; 76&t;/* Back compatible 2Gig limited rlimit */
DECL|macro|__NR_ia32_getrusage
mdefine_line|#define __NR_ia32_getrusage&t;&t; 77
DECL|macro|__NR_ia32_gettimeofday
mdefine_line|#define __NR_ia32_gettimeofday&t; 78
DECL|macro|__NR_ia32_settimeofday
mdefine_line|#define __NR_ia32_settimeofday&t; 79
DECL|macro|__NR_ia32_getgroups
mdefine_line|#define __NR_ia32_getgroups&t;&t; 80
DECL|macro|__NR_ia32_setgroups
mdefine_line|#define __NR_ia32_setgroups&t;&t; 81
DECL|macro|__NR_ia32_select
mdefine_line|#define __NR_ia32_select&t;&t; 82
DECL|macro|__NR_ia32_symlink
mdefine_line|#define __NR_ia32_symlink&t;&t; 83
DECL|macro|__NR_ia32_oldlstat
mdefine_line|#define __NR_ia32_oldlstat&t;&t; 84
DECL|macro|__NR_ia32_readlink
mdefine_line|#define __NR_ia32_readlink&t;&t; 85
DECL|macro|__NR_ia32_uselib
mdefine_line|#define __NR_ia32_uselib&t;&t; 86
DECL|macro|__NR_ia32_swapon
mdefine_line|#define __NR_ia32_swapon&t;&t; 87
DECL|macro|__NR_ia32_reboot
mdefine_line|#define __NR_ia32_reboot&t;&t; 88
DECL|macro|__NR_ia32_readdir
mdefine_line|#define __NR_ia32_readdir&t;&t; 89
DECL|macro|__NR_ia32_mmap
mdefine_line|#define __NR_ia32_mmap&t;&t; 90
DECL|macro|__NR_ia32_munmap
mdefine_line|#define __NR_ia32_munmap&t;&t; 91
DECL|macro|__NR_ia32_truncate
mdefine_line|#define __NR_ia32_truncate&t;&t; 92
DECL|macro|__NR_ia32_ftruncate
mdefine_line|#define __NR_ia32_ftruncate&t;&t; 93
DECL|macro|__NR_ia32_fchmod
mdefine_line|#define __NR_ia32_fchmod&t;&t; 94
DECL|macro|__NR_ia32_fchown
mdefine_line|#define __NR_ia32_fchown&t;&t; 95
DECL|macro|__NR_ia32_getpriority
mdefine_line|#define __NR_ia32_getpriority&t; 96
DECL|macro|__NR_ia32_setpriority
mdefine_line|#define __NR_ia32_setpriority&t; 97
DECL|macro|__NR_ia32_profil
mdefine_line|#define __NR_ia32_profil&t;&t; 98
DECL|macro|__NR_ia32_statfs
mdefine_line|#define __NR_ia32_statfs&t;&t; 99
DECL|macro|__NR_ia32_fstatfs
mdefine_line|#define __NR_ia32_fstatfs&t;&t;100
DECL|macro|__NR_ia32_ioperm
mdefine_line|#define __NR_ia32_ioperm&t;&t;101
DECL|macro|__NR_ia32_socketcall
mdefine_line|#define __NR_ia32_socketcall&t;&t;102
DECL|macro|__NR_ia32_syslog
mdefine_line|#define __NR_ia32_syslog&t;&t;103
DECL|macro|__NR_ia32_setitimer
mdefine_line|#define __NR_ia32_setitimer&t;&t;104
DECL|macro|__NR_ia32_getitimer
mdefine_line|#define __NR_ia32_getitimer&t;&t;105
DECL|macro|__NR_ia32_stat
mdefine_line|#define __NR_ia32_stat&t;&t;106
DECL|macro|__NR_ia32_lstat
mdefine_line|#define __NR_ia32_lstat&t;&t;107
DECL|macro|__NR_ia32_fstat
mdefine_line|#define __NR_ia32_fstat&t;&t;108
DECL|macro|__NR_ia32_olduname
mdefine_line|#define __NR_ia32_olduname&t;&t;109
DECL|macro|__NR_ia32_iopl
mdefine_line|#define __NR_ia32_iopl&t;&t;110
DECL|macro|__NR_ia32_vhangup
mdefine_line|#define __NR_ia32_vhangup&t;&t;111
DECL|macro|__NR_ia32_idle
mdefine_line|#define __NR_ia32_idle&t;&t;112
DECL|macro|__NR_ia32_vm86old
mdefine_line|#define __NR_ia32_vm86old&t;&t;113
DECL|macro|__NR_ia32_wait4
mdefine_line|#define __NR_ia32_wait4&t;&t;114
DECL|macro|__NR_ia32_swapoff
mdefine_line|#define __NR_ia32_swapoff&t;&t;115
DECL|macro|__NR_ia32_sysinfo
mdefine_line|#define __NR_ia32_sysinfo&t;&t;116
DECL|macro|__NR_ia32_ipc
mdefine_line|#define __NR_ia32_ipc&t;&t;117
DECL|macro|__NR_ia32_fsync
mdefine_line|#define __NR_ia32_fsync&t;&t;118
DECL|macro|__NR_ia32_sigreturn
mdefine_line|#define __NR_ia32_sigreturn&t;&t;119
DECL|macro|__NR_ia32_clone
mdefine_line|#define __NR_ia32_clone&t;&t;120
DECL|macro|__NR_ia32_setdomainname
mdefine_line|#define __NR_ia32_setdomainname&t;121
DECL|macro|__NR_ia32_uname
mdefine_line|#define __NR_ia32_uname&t;&t;122
DECL|macro|__NR_ia32_modify_ldt
mdefine_line|#define __NR_ia32_modify_ldt&t;&t;123
DECL|macro|__NR_ia32_adjtimex
mdefine_line|#define __NR_ia32_adjtimex&t;&t;124
DECL|macro|__NR_ia32_mprotect
mdefine_line|#define __NR_ia32_mprotect&t;&t;125
DECL|macro|__NR_ia32_sigprocmask
mdefine_line|#define __NR_ia32_sigprocmask&t;126
DECL|macro|__NR_ia32_create_module
mdefine_line|#define __NR_ia32_create_module&t;127
DECL|macro|__NR_ia32_init_module
mdefine_line|#define __NR_ia32_init_module&t;128
DECL|macro|__NR_ia32_delete_module
mdefine_line|#define __NR_ia32_delete_module&t;129
DECL|macro|__NR_ia32_get_kernel_syms
mdefine_line|#define __NR_ia32_get_kernel_syms&t;130
DECL|macro|__NR_ia32_quotactl
mdefine_line|#define __NR_ia32_quotactl&t;&t;131
DECL|macro|__NR_ia32_getpgid
mdefine_line|#define __NR_ia32_getpgid&t;&t;132
DECL|macro|__NR_ia32_fchdir
mdefine_line|#define __NR_ia32_fchdir&t;&t;133
DECL|macro|__NR_ia32_bdflush
mdefine_line|#define __NR_ia32_bdflush&t;&t;134
DECL|macro|__NR_ia32_sysfs
mdefine_line|#define __NR_ia32_sysfs&t;&t;135
DECL|macro|__NR_ia32_personality
mdefine_line|#define __NR_ia32_personality&t;136
DECL|macro|__NR_ia32_afs_syscall
mdefine_line|#define __NR_ia32_afs_syscall&t;137 /* Syscall for Andrew File System */
DECL|macro|__NR_ia32_setfsuid
mdefine_line|#define __NR_ia32_setfsuid&t;&t;138
DECL|macro|__NR_ia32_setfsgid
mdefine_line|#define __NR_ia32_setfsgid&t;&t;139
DECL|macro|__NR_ia32__llseek
mdefine_line|#define __NR_ia32__llseek&t;&t;140
DECL|macro|__NR_ia32_getdents
mdefine_line|#define __NR_ia32_getdents&t;&t;141
DECL|macro|__NR_ia32__newselect
mdefine_line|#define __NR_ia32__newselect&t;&t;142
DECL|macro|__NR_ia32_flock
mdefine_line|#define __NR_ia32_flock&t;&t;143
DECL|macro|__NR_ia32_msync
mdefine_line|#define __NR_ia32_msync&t;&t;144
DECL|macro|__NR_ia32_readv
mdefine_line|#define __NR_ia32_readv&t;&t;145
DECL|macro|__NR_ia32_writev
mdefine_line|#define __NR_ia32_writev&t;&t;146
DECL|macro|__NR_ia32_getsid
mdefine_line|#define __NR_ia32_getsid&t;&t;147
DECL|macro|__NR_ia32_fdatasync
mdefine_line|#define __NR_ia32_fdatasync&t;&t;148
DECL|macro|__NR_ia32__sysctl
mdefine_line|#define __NR_ia32__sysctl&t;&t;149
DECL|macro|__NR_ia32_mlock
mdefine_line|#define __NR_ia32_mlock&t;&t;150
DECL|macro|__NR_ia32_munlock
mdefine_line|#define __NR_ia32_munlock&t;&t;151
DECL|macro|__NR_ia32_mlockall
mdefine_line|#define __NR_ia32_mlockall&t;&t;152
DECL|macro|__NR_ia32_munlockall
mdefine_line|#define __NR_ia32_munlockall&t;&t;153
DECL|macro|__NR_ia32_sched_setparam
mdefine_line|#define __NR_ia32_sched_setparam&t;&t;154
DECL|macro|__NR_ia32_sched_getparam
mdefine_line|#define __NR_ia32_sched_getparam&t;&t;155
DECL|macro|__NR_ia32_sched_setscheduler
mdefine_line|#define __NR_ia32_sched_setscheduler&t;&t;156
DECL|macro|__NR_ia32_sched_getscheduler
mdefine_line|#define __NR_ia32_sched_getscheduler&t;&t;157
DECL|macro|__NR_ia32_sched_yield
mdefine_line|#define __NR_ia32_sched_yield&t;&t;158
DECL|macro|__NR_ia32_sched_get_priority_max
mdefine_line|#define __NR_ia32_sched_get_priority_max&t;159
DECL|macro|__NR_ia32_sched_get_priority_min
mdefine_line|#define __NR_ia32_sched_get_priority_min&t;160
DECL|macro|__NR_ia32_sched_rr_get_interval
mdefine_line|#define __NR_ia32_sched_rr_get_interval&t;161
DECL|macro|__NR_ia32_nanosleep
mdefine_line|#define __NR_ia32_nanosleep&t;&t;162
DECL|macro|__NR_ia32_mremap
mdefine_line|#define __NR_ia32_mremap&t;&t;163
DECL|macro|__NR_ia32_setresuid
mdefine_line|#define __NR_ia32_setresuid&t;&t;164
DECL|macro|__NR_ia32_getresuid
mdefine_line|#define __NR_ia32_getresuid&t;&t;165
DECL|macro|__NR_ia32_vm86
mdefine_line|#define __NR_ia32_vm86&t;&t;166
DECL|macro|__NR_ia32_query_module
mdefine_line|#define __NR_ia32_query_module&t;167
DECL|macro|__NR_ia32_poll
mdefine_line|#define __NR_ia32_poll&t;&t;168
DECL|macro|__NR_ia32_nfsservctl
mdefine_line|#define __NR_ia32_nfsservctl&t;&t;169
DECL|macro|__NR_ia32_setresgid
mdefine_line|#define __NR_ia32_setresgid&t;&t;170
DECL|macro|__NR_ia32_getresgid
mdefine_line|#define __NR_ia32_getresgid&t;&t;171
DECL|macro|__NR_ia32_prctl
mdefine_line|#define __NR_ia32_prctl              172
DECL|macro|__NR_ia32_rt_sigreturn
mdefine_line|#define __NR_ia32_rt_sigreturn&t;173
DECL|macro|__NR_ia32_rt_sigaction
mdefine_line|#define __NR_ia32_rt_sigaction&t;174
DECL|macro|__NR_ia32_rt_sigprocmask
mdefine_line|#define __NR_ia32_rt_sigprocmask&t;175
DECL|macro|__NR_ia32_rt_sigpending
mdefine_line|#define __NR_ia32_rt_sigpending&t;176
DECL|macro|__NR_ia32_rt_sigtimedwait
mdefine_line|#define __NR_ia32_rt_sigtimedwait&t;177
DECL|macro|__NR_ia32_rt_sigqueueinfo
mdefine_line|#define __NR_ia32_rt_sigqueueinfo&t;178
DECL|macro|__NR_ia32_rt_sigsuspend
mdefine_line|#define __NR_ia32_rt_sigsuspend&t;179
DECL|macro|__NR_ia32_pread
mdefine_line|#define __NR_ia32_pread&t;&t;180
DECL|macro|__NR_ia32_pwrite
mdefine_line|#define __NR_ia32_pwrite&t;&t;181
DECL|macro|__NR_ia32_chown
mdefine_line|#define __NR_ia32_chown&t;&t;182
DECL|macro|__NR_ia32_getcwd
mdefine_line|#define __NR_ia32_getcwd&t;&t;183
DECL|macro|__NR_ia32_capget
mdefine_line|#define __NR_ia32_capget&t;&t;184
DECL|macro|__NR_ia32_capset
mdefine_line|#define __NR_ia32_capset&t;&t;185
DECL|macro|__NR_ia32_sigaltstack
mdefine_line|#define __NR_ia32_sigaltstack&t;186
DECL|macro|__NR_ia32_sendfile
mdefine_line|#define __NR_ia32_sendfile&t;&t;187
DECL|macro|__NR_ia32_getpmsg
mdefine_line|#define __NR_ia32_getpmsg&t;&t;188&t;/* some people actually want streams */
DECL|macro|__NR_ia32_putpmsg
mdefine_line|#define __NR_ia32_putpmsg&t;&t;189&t;/* some people actually want streams */
DECL|macro|__NR_ia32_vfork
mdefine_line|#define __NR_ia32_vfork&t;&t;190
DECL|macro|__NR_ia32_ugetrlimit
mdefine_line|#define __NR_ia32_ugetrlimit&t;&t;191&t;/* SuS compliant getrlimit */
DECL|macro|__NR_ia32_mmap2
mdefine_line|#define __NR_ia32_mmap2&t;&t;192
DECL|macro|__NR_ia32_truncate64
mdefine_line|#define __NR_ia32_truncate64&t;&t;193
DECL|macro|__NR_ia32_ftruncate64
mdefine_line|#define __NR_ia32_ftruncate64&t;194
DECL|macro|__NR_ia32_stat64
mdefine_line|#define __NR_ia32_stat64&t;&t;195
DECL|macro|__NR_ia32_lstat64
mdefine_line|#define __NR_ia32_lstat64&t;&t;196
DECL|macro|__NR_ia32_fstat64
mdefine_line|#define __NR_ia32_fstat64&t;&t;197
DECL|macro|__NR_ia32_lchown32
mdefine_line|#define __NR_ia32_lchown32&t;&t;198
DECL|macro|__NR_ia32_getuid32
mdefine_line|#define __NR_ia32_getuid32&t;&t;199
DECL|macro|__NR_ia32_getgid32
mdefine_line|#define __NR_ia32_getgid32&t;&t;200
DECL|macro|__NR_ia32_geteuid32
mdefine_line|#define __NR_ia32_geteuid32&t;&t;201
DECL|macro|__NR_ia32_getegid32
mdefine_line|#define __NR_ia32_getegid32&t;&t;202
DECL|macro|__NR_ia32_setreuid32
mdefine_line|#define __NR_ia32_setreuid32&t;&t;203
DECL|macro|__NR_ia32_setregid32
mdefine_line|#define __NR_ia32_setregid32&t;&t;204
DECL|macro|__NR_ia32_getgroups32
mdefine_line|#define __NR_ia32_getgroups32&t;205
DECL|macro|__NR_ia32_setgroups32
mdefine_line|#define __NR_ia32_setgroups32&t;206
DECL|macro|__NR_ia32_fchown32
mdefine_line|#define __NR_ia32_fchown32&t;&t;207
DECL|macro|__NR_ia32_setresuid32
mdefine_line|#define __NR_ia32_setresuid32&t;208
DECL|macro|__NR_ia32_getresuid32
mdefine_line|#define __NR_ia32_getresuid32&t;209
DECL|macro|__NR_ia32_setresgid32
mdefine_line|#define __NR_ia32_setresgid32&t;210
DECL|macro|__NR_ia32_getresgid32
mdefine_line|#define __NR_ia32_getresgid32&t;211
DECL|macro|__NR_ia32_chown32
mdefine_line|#define __NR_ia32_chown32&t;&t;212
DECL|macro|__NR_ia32_setuid32
mdefine_line|#define __NR_ia32_setuid32&t;&t;213
DECL|macro|__NR_ia32_setgid32
mdefine_line|#define __NR_ia32_setgid32&t;&t;214
DECL|macro|__NR_ia32_setfsuid32
mdefine_line|#define __NR_ia32_setfsuid32&t;&t;215
DECL|macro|__NR_ia32_setfsgid32
mdefine_line|#define __NR_ia32_setfsgid32&t;&t;216
DECL|macro|__NR_ia32_pivot_root
mdefine_line|#define __NR_ia32_pivot_root&t;&t;217
DECL|macro|__NR_ia32_mincore
mdefine_line|#define __NR_ia32_mincore&t;&t;218
DECL|macro|__NR_ia32_madvise
mdefine_line|#define __NR_ia32_madvise&t;&t;219
DECL|macro|__NR_ia32_madvise1
mdefine_line|#define __NR_ia32_madvise1&t;&t;219&t;/* delete when C lib stub is removed */
DECL|macro|__NR_ia32_getdents64
mdefine_line|#define __NR_ia32_getdents64&t;&t;220
DECL|macro|__NR_ia32_fcntl64
mdefine_line|#define __NR_ia32_fcntl64&t;&t;221
DECL|macro|__NR_ia32_tuxcall
mdefine_line|#define __NR_ia32_tuxcall&t;&t;222
DECL|macro|__NR_ia32_security
mdefine_line|#define __NR_ia32_security&t;&t;223
DECL|macro|__NR_ia32_gettid
mdefine_line|#define __NR_ia32_gettid&t;&t;224
DECL|macro|__NR_ia32_readahead
mdefine_line|#define __NR_ia32_readahead&t;&t;225
DECL|macro|__NR_ia32_setxattr
mdefine_line|#define __NR_ia32_setxattr&t;&t;226
DECL|macro|__NR_ia32_lsetxattr
mdefine_line|#define __NR_ia32_lsetxattr&t;&t;227
DECL|macro|__NR_ia32_fsetxattr
mdefine_line|#define __NR_ia32_fsetxattr&t;&t;228
DECL|macro|__NR_ia32_getxattr
mdefine_line|#define __NR_ia32_getxattr&t;&t;229
DECL|macro|__NR_ia32_lgetxattr
mdefine_line|#define __NR_ia32_lgetxattr&t;&t;230
DECL|macro|__NR_ia32_fgetxattr
mdefine_line|#define __NR_ia32_fgetxattr&t;&t;231
DECL|macro|__NR_ia32_listxattr
mdefine_line|#define __NR_ia32_listxattr&t;&t;232
DECL|macro|__NR_ia32_llistxattr
mdefine_line|#define __NR_ia32_llistxattr&t;&t;233
DECL|macro|__NR_ia32_flistxattr
mdefine_line|#define __NR_ia32_flistxattr&t;&t;234
DECL|macro|__NR_ia32_removexattr
mdefine_line|#define __NR_ia32_removexattr&t;235
DECL|macro|__NR_ia32_lremovexattr
mdefine_line|#define __NR_ia32_lremovexattr&t;236
DECL|macro|__NR_ia32_fremovexattr
mdefine_line|#define __NR_ia32_fremovexattr&t;237
DECL|macro|__NR_ia32_tkill
mdefine_line|#define __NR_ia32_tkill&t;&t;238
DECL|macro|__NR_ia32_sendfile64
mdefine_line|#define __NR_ia32_sendfile64&t;&t;239
DECL|macro|__NR_ia32_futex
mdefine_line|#define __NR_ia32_futex&t;&t;240
DECL|macro|__NR_ia32_sched_setaffinity
mdefine_line|#define __NR_ia32_sched_setaffinity&t;241
DECL|macro|__NR_ia32_sched_getaffinity
mdefine_line|#define __NR_ia32_sched_getaffinity&t;242
DECL|macro|IA32_NR_syscalls
mdefine_line|#define IA32_NR_syscalls 243&t;/* must be &gt; than biggest syscall! */&t;
macro_line|#endif /* _ASM_X86_64_IA32_UNISTD_H_ */
eof
