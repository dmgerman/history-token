macro_line|#ifndef _ASM_I386_UNISTD_H_
DECL|macro|_ASM_I386_UNISTD_H_
mdefine_line|#define _ASM_I386_UNISTD_H_
multiline_comment|/*&n; * This file contains the system call numbers.&n; */
DECL|macro|__NR_restart_syscall
mdefine_line|#define __NR_restart_syscall      0
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
DECL|macro|__NR_lchown
mdefine_line|#define __NR_lchown&t;&t; 16
DECL|macro|__NR_break
mdefine_line|#define __NR_break&t;&t; 17
DECL|macro|__NR_oldstat
mdefine_line|#define __NR_oldstat&t;&t; 18
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
DECL|macro|__NR_oldfstat
mdefine_line|#define __NR_oldfstat&t;&t; 28
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
DECL|macro|__NR_mpx
mdefine_line|#define __NR_mpx&t;&t; 56
DECL|macro|__NR_setpgid
mdefine_line|#define __NR_setpgid&t;&t; 57
DECL|macro|__NR_ulimit
mdefine_line|#define __NR_ulimit&t;&t; 58
DECL|macro|__NR_oldolduname
mdefine_line|#define __NR_oldolduname&t; 59
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
DECL|macro|__NR_getrlimit
mdefine_line|#define __NR_getrlimit&t;&t; 76&t;/* Back compatible 2Gig limited rlimit */
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
DECL|macro|__NR_oldlstat
mdefine_line|#define __NR_oldlstat&t;&t; 84
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
DECL|macro|__NR_ioperm
mdefine_line|#define __NR_ioperm&t;&t;101
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
DECL|macro|__NR_olduname
mdefine_line|#define __NR_olduname&t;&t;109
DECL|macro|__NR_iopl
mdefine_line|#define __NR_iopl&t;&t;110
DECL|macro|__NR_vhangup
mdefine_line|#define __NR_vhangup&t;&t;111
DECL|macro|__NR_idle
mdefine_line|#define __NR_idle&t;&t;112
DECL|macro|__NR_vm86old
mdefine_line|#define __NR_vm86old&t;&t;113
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
DECL|macro|__NR_modify_ldt
mdefine_line|#define __NR_modify_ldt&t;&t;123
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
DECL|macro|__NR__newselect
mdefine_line|#define __NR__newselect&t;&t;142
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
DECL|macro|__NR_vm86
mdefine_line|#define __NR_vm86&t;&t;166
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
mdefine_line|#define __NR_prctl              172
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
DECL|macro|__NR_pread64
mdefine_line|#define __NR_pread64&t;&t;180
DECL|macro|__NR_pwrite64
mdefine_line|#define __NR_pwrite64&t;&t;181
DECL|macro|__NR_chown
mdefine_line|#define __NR_chown&t;&t;182
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
DECL|macro|__NR_ugetrlimit
mdefine_line|#define __NR_ugetrlimit&t;&t;191&t;/* SuS compliant getrlimit */
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
DECL|macro|__NR_lchown32
mdefine_line|#define __NR_lchown32&t;&t;198
DECL|macro|__NR_getuid32
mdefine_line|#define __NR_getuid32&t;&t;199
DECL|macro|__NR_getgid32
mdefine_line|#define __NR_getgid32&t;&t;200
DECL|macro|__NR_geteuid32
mdefine_line|#define __NR_geteuid32&t;&t;201
DECL|macro|__NR_getegid32
mdefine_line|#define __NR_getegid32&t;&t;202
DECL|macro|__NR_setreuid32
mdefine_line|#define __NR_setreuid32&t;&t;203
DECL|macro|__NR_setregid32
mdefine_line|#define __NR_setregid32&t;&t;204
DECL|macro|__NR_getgroups32
mdefine_line|#define __NR_getgroups32&t;205
DECL|macro|__NR_setgroups32
mdefine_line|#define __NR_setgroups32&t;206
DECL|macro|__NR_fchown32
mdefine_line|#define __NR_fchown32&t;&t;207
DECL|macro|__NR_setresuid32
mdefine_line|#define __NR_setresuid32&t;208
DECL|macro|__NR_getresuid32
mdefine_line|#define __NR_getresuid32&t;209
DECL|macro|__NR_setresgid32
mdefine_line|#define __NR_setresgid32&t;210
DECL|macro|__NR_getresgid32
mdefine_line|#define __NR_getresgid32&t;211
DECL|macro|__NR_chown32
mdefine_line|#define __NR_chown32&t;&t;212
DECL|macro|__NR_setuid32
mdefine_line|#define __NR_setuid32&t;&t;213
DECL|macro|__NR_setgid32
mdefine_line|#define __NR_setgid32&t;&t;214
DECL|macro|__NR_setfsuid32
mdefine_line|#define __NR_setfsuid32&t;&t;215
DECL|macro|__NR_setfsgid32
mdefine_line|#define __NR_setfsgid32&t;&t;216
DECL|macro|__NR_pivot_root
mdefine_line|#define __NR_pivot_root&t;&t;217
DECL|macro|__NR_mincore
mdefine_line|#define __NR_mincore&t;&t;218
DECL|macro|__NR_madvise
mdefine_line|#define __NR_madvise&t;&t;219
DECL|macro|__NR_madvise1
mdefine_line|#define __NR_madvise1&t;&t;219&t;/* delete when C lib stub is removed */
DECL|macro|__NR_getdents64
mdefine_line|#define __NR_getdents64&t;&t;220
DECL|macro|__NR_fcntl64
mdefine_line|#define __NR_fcntl64&t;&t;221
multiline_comment|/* 223 is unused */
DECL|macro|__NR_gettid
mdefine_line|#define __NR_gettid&t;&t;224
DECL|macro|__NR_readahead
mdefine_line|#define __NR_readahead&t;&t;225
DECL|macro|__NR_setxattr
mdefine_line|#define __NR_setxattr&t;&t;226
DECL|macro|__NR_lsetxattr
mdefine_line|#define __NR_lsetxattr&t;&t;227
DECL|macro|__NR_fsetxattr
mdefine_line|#define __NR_fsetxattr&t;&t;228
DECL|macro|__NR_getxattr
mdefine_line|#define __NR_getxattr&t;&t;229
DECL|macro|__NR_lgetxattr
mdefine_line|#define __NR_lgetxattr&t;&t;230
DECL|macro|__NR_fgetxattr
mdefine_line|#define __NR_fgetxattr&t;&t;231
DECL|macro|__NR_listxattr
mdefine_line|#define __NR_listxattr&t;&t;232
DECL|macro|__NR_llistxattr
mdefine_line|#define __NR_llistxattr&t;&t;233
DECL|macro|__NR_flistxattr
mdefine_line|#define __NR_flistxattr&t;&t;234
DECL|macro|__NR_removexattr
mdefine_line|#define __NR_removexattr&t;235
DECL|macro|__NR_lremovexattr
mdefine_line|#define __NR_lremovexattr&t;236
DECL|macro|__NR_fremovexattr
mdefine_line|#define __NR_fremovexattr&t;237
DECL|macro|__NR_tkill
mdefine_line|#define __NR_tkill&t;&t;238
DECL|macro|__NR_sendfile64
mdefine_line|#define __NR_sendfile64&t;&t;239
DECL|macro|__NR_futex
mdefine_line|#define __NR_futex&t;&t;240
DECL|macro|__NR_sched_setaffinity
mdefine_line|#define __NR_sched_setaffinity&t;241
DECL|macro|__NR_sched_getaffinity
mdefine_line|#define __NR_sched_getaffinity&t;242
DECL|macro|__NR_set_thread_area
mdefine_line|#define __NR_set_thread_area&t;243
DECL|macro|__NR_get_thread_area
mdefine_line|#define __NR_get_thread_area&t;244
DECL|macro|__NR_io_setup
mdefine_line|#define __NR_io_setup&t;&t;245
DECL|macro|__NR_io_destroy
mdefine_line|#define __NR_io_destroy&t;&t;246
DECL|macro|__NR_io_getevents
mdefine_line|#define __NR_io_getevents&t;247
DECL|macro|__NR_io_submit
mdefine_line|#define __NR_io_submit&t;&t;248
DECL|macro|__NR_io_cancel
mdefine_line|#define __NR_io_cancel&t;&t;249
DECL|macro|__NR_fadvise64
mdefine_line|#define __NR_fadvise64&t;&t;250
DECL|macro|__NR_exit_group
mdefine_line|#define __NR_exit_group&t;&t;252
DECL|macro|__NR_lookup_dcookie
mdefine_line|#define __NR_lookup_dcookie&t;253
DECL|macro|__NR_epoll_create
mdefine_line|#define __NR_epoll_create&t;254
DECL|macro|__NR_epoll_ctl
mdefine_line|#define __NR_epoll_ctl&t;&t;255
DECL|macro|__NR_epoll_wait
mdefine_line|#define __NR_epoll_wait&t;&t;256
DECL|macro|__NR_remap_file_pages
mdefine_line|#define __NR_remap_file_pages&t;257
DECL|macro|__NR_set_tid_address
mdefine_line|#define __NR_set_tid_address&t;258
DECL|macro|__NR_timer_create
mdefine_line|#define __NR_timer_create&t;259
DECL|macro|__NR_timer_settime
mdefine_line|#define __NR_timer_settime&t;(__NR_timer_create+1)
DECL|macro|__NR_timer_gettime
mdefine_line|#define __NR_timer_gettime&t;(__NR_timer_create+2)
DECL|macro|__NR_timer_getoverrun
mdefine_line|#define __NR_timer_getoverrun&t;(__NR_timer_create+3)
DECL|macro|__NR_timer_delete
mdefine_line|#define __NR_timer_delete&t;(__NR_timer_create+4)
DECL|macro|__NR_clock_settime
mdefine_line|#define __NR_clock_settime&t;(__NR_timer_create+5)
DECL|macro|__NR_clock_gettime
mdefine_line|#define __NR_clock_gettime&t;(__NR_timer_create+6)
DECL|macro|__NR_clock_getres
mdefine_line|#define __NR_clock_getres&t;(__NR_timer_create+7)
DECL|macro|__NR_clock_nanosleep
mdefine_line|#define __NR_clock_nanosleep&t;(__NR_timer_create+8)
DECL|macro|__NR_statfs64
mdefine_line|#define __NR_statfs64&t;&t;268
DECL|macro|__NR_fstatfs64
mdefine_line|#define __NR_fstatfs64&t;&t;269
DECL|macro|__NR_tgkill
mdefine_line|#define __NR_tgkill&t;&t;270
DECL|macro|__NR_utimes
mdefine_line|#define __NR_utimes&t;&t;271
DECL|macro|__NR_fadvise64_64
mdefine_line|#define __NR_fadvise64_64&t;272
DECL|macro|__NR_vserver
mdefine_line|#define __NR_vserver&t;&t;273
DECL|macro|__NR_mbind
mdefine_line|#define __NR_mbind&t;&t;274
DECL|macro|__NR_get_mempolicy
mdefine_line|#define __NR_get_mempolicy&t;275
DECL|macro|__NR_set_mempolicy
mdefine_line|#define __NR_set_mempolicy&t;276
DECL|macro|__NR_mq_open
mdefine_line|#define __NR_mq_open &t;&t;277
DECL|macro|__NR_mq_unlink
mdefine_line|#define __NR_mq_unlink&t;&t;(__NR_mq_open+1)
DECL|macro|__NR_mq_timedsend
mdefine_line|#define __NR_mq_timedsend&t;(__NR_mq_open+2)
DECL|macro|__NR_mq_timedreceive
mdefine_line|#define __NR_mq_timedreceive&t;(__NR_mq_open+3)
DECL|macro|__NR_mq_notify
mdefine_line|#define __NR_mq_notify&t;&t;(__NR_mq_open+4)
DECL|macro|__NR_mq_getsetattr
mdefine_line|#define __NR_mq_getsetattr&t;(__NR_mq_open+5)
DECL|macro|__NR_sys_kexec_load
mdefine_line|#define __NR_sys_kexec_load&t;283
DECL|macro|__NR_waitid
mdefine_line|#define __NR_waitid&t;&t;284
multiline_comment|/* #define __NR_sys_setaltroot&t;285 */
DECL|macro|__NR_add_key
mdefine_line|#define __NR_add_key&t;&t;286
DECL|macro|__NR_request_key
mdefine_line|#define __NR_request_key&t;287
DECL|macro|__NR_keyctl
mdefine_line|#define __NR_keyctl&t;&t;288
DECL|macro|NR_syscalls
mdefine_line|#define NR_syscalls 289
multiline_comment|/*&n; * user-visible error numbers are in the range -1 - -128: see&n; * &lt;asm-i386/errno.h&gt;&n; */
DECL|macro|__syscall_return
mdefine_line|#define __syscall_return(type, res) &bslash;&n;do { &bslash;&n;&t;if ((unsigned long)(res) &gt;= (unsigned long)(-(128 + 1))) { &bslash;&n;&t;&t;errno = -(res); &bslash;&n;&t;&t;res = -1; &bslash;&n;&t;} &bslash;&n;&t;return (type) (res); &bslash;&n;} while (0)
multiline_comment|/* XXX - _foo needs to be __foo, while __NR_bar could be _NR_bar. */
DECL|macro|_syscall0
mdefine_line|#define _syscall0(type,name) &bslash;&n;type name(void) &bslash;&n;{ &bslash;&n;long __res; &bslash;&n;__asm__ volatile (&quot;int $0x80&quot; &bslash;&n;&t;: &quot;=a&quot; (__res) &bslash;&n;&t;: &quot;0&quot; (__NR_##name)); &bslash;&n;__syscall_return(type,__res); &bslash;&n;}
DECL|macro|_syscall1
mdefine_line|#define _syscall1(type,name,type1,arg1) &bslash;&n;type name(type1 arg1) &bslash;&n;{ &bslash;&n;long __res; &bslash;&n;__asm__ volatile (&quot;int $0x80&quot; &bslash;&n;&t;: &quot;=a&quot; (__res) &bslash;&n;&t;: &quot;0&quot; (__NR_##name),&quot;b&quot; ((long)(arg1))); &bslash;&n;__syscall_return(type,__res); &bslash;&n;}
DECL|macro|_syscall2
mdefine_line|#define _syscall2(type,name,type1,arg1,type2,arg2) &bslash;&n;type name(type1 arg1,type2 arg2) &bslash;&n;{ &bslash;&n;long __res; &bslash;&n;__asm__ volatile (&quot;int $0x80&quot; &bslash;&n;&t;: &quot;=a&quot; (__res) &bslash;&n;&t;: &quot;0&quot; (__NR_##name),&quot;b&quot; ((long)(arg1)),&quot;c&quot; ((long)(arg2))); &bslash;&n;__syscall_return(type,__res); &bslash;&n;}
DECL|macro|_syscall3
mdefine_line|#define _syscall3(type,name,type1,arg1,type2,arg2,type3,arg3) &bslash;&n;type name(type1 arg1,type2 arg2,type3 arg3) &bslash;&n;{ &bslash;&n;long __res; &bslash;&n;__asm__ volatile (&quot;int $0x80&quot; &bslash;&n;&t;: &quot;=a&quot; (__res) &bslash;&n;&t;: &quot;0&quot; (__NR_##name),&quot;b&quot; ((long)(arg1)),&quot;c&quot; ((long)(arg2)), &bslash;&n;&t;&t;  &quot;d&quot; ((long)(arg3))); &bslash;&n;__syscall_return(type,__res); &bslash;&n;}
DECL|macro|_syscall4
mdefine_line|#define _syscall4(type,name,type1,arg1,type2,arg2,type3,arg3,type4,arg4) &bslash;&n;type name (type1 arg1, type2 arg2, type3 arg3, type4 arg4) &bslash;&n;{ &bslash;&n;long __res; &bslash;&n;__asm__ volatile (&quot;int $0x80&quot; &bslash;&n;&t;: &quot;=a&quot; (__res) &bslash;&n;&t;: &quot;0&quot; (__NR_##name),&quot;b&quot; ((long)(arg1)),&quot;c&quot; ((long)(arg2)), &bslash;&n;&t;  &quot;d&quot; ((long)(arg3)),&quot;S&quot; ((long)(arg4))); &bslash;&n;__syscall_return(type,__res); &bslash;&n;} 
DECL|macro|_syscall5
mdefine_line|#define _syscall5(type,name,type1,arg1,type2,arg2,type3,arg3,type4,arg4, &bslash;&n;&t;  type5,arg5) &bslash;&n;type name (type1 arg1,type2 arg2,type3 arg3,type4 arg4,type5 arg5) &bslash;&n;{ &bslash;&n;long __res; &bslash;&n;__asm__ volatile (&quot;int $0x80&quot; &bslash;&n;&t;: &quot;=a&quot; (__res) &bslash;&n;&t;: &quot;0&quot; (__NR_##name),&quot;b&quot; ((long)(arg1)),&quot;c&quot; ((long)(arg2)), &bslash;&n;&t;  &quot;d&quot; ((long)(arg3)),&quot;S&quot; ((long)(arg4)),&quot;D&quot; ((long)(arg5))); &bslash;&n;__syscall_return(type,__res); &bslash;&n;}
DECL|macro|_syscall6
mdefine_line|#define _syscall6(type,name,type1,arg1,type2,arg2,type3,arg3,type4,arg4, &bslash;&n;&t;  type5,arg5,type6,arg6) &bslash;&n;type name (type1 arg1,type2 arg2,type3 arg3,type4 arg4,type5 arg5,type6 arg6) &bslash;&n;{ &bslash;&n;long __res; &bslash;&n;__asm__ volatile (&quot;push %%ebp ; movl %%eax,%%ebp ; movl %1,%%eax ; int $0x80 ; pop %%ebp&quot; &bslash;&n;&t;: &quot;=a&quot; (__res) &bslash;&n;&t;: &quot;i&quot; (__NR_##name),&quot;b&quot; ((long)(arg1)),&quot;c&quot; ((long)(arg2)), &bslash;&n;&t;  &quot;d&quot; ((long)(arg3)),&quot;S&quot; ((long)(arg4)),&quot;D&quot; ((long)(arg5)), &bslash;&n;&t;  &quot;0&quot; ((long)(arg6))); &bslash;&n;__syscall_return(type,__res); &bslash;&n;}
macro_line|#ifdef __KERNEL__
DECL|macro|__ARCH_WANT_IPC_PARSE_VERSION
mdefine_line|#define __ARCH_WANT_IPC_PARSE_VERSION
DECL|macro|__ARCH_WANT_OLD_READDIR
mdefine_line|#define __ARCH_WANT_OLD_READDIR
DECL|macro|__ARCH_WANT_OLD_STAT
mdefine_line|#define __ARCH_WANT_OLD_STAT
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
DECL|macro|__ARCH_WANT_SYS_OLD_GETRLIMIT
mdefine_line|#define __ARCH_WANT_SYS_OLD_GETRLIMIT
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
macro_line|#include &lt;linux/linkage.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
multiline_comment|/*&n; * we need this inline - forking from kernel space will result&n; * in NO COPY ON WRITE (!!!), until an execve is executed. This&n; * is no problem, but for the stack. This is handled by not letting&n; * main() use the stack at all after fork(). Thus, no function&n; * calls - which means inline code for fork too, as otherwise we&n; * would use the stack upon exit from &squot;fork()&squot;.&n; *&n; * Actually only pause and fork are needed inline, so that there&n; * won&squot;t be any messing with the stack from main(), but we define&n; * some others too.&n; */
r_static
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
id|asmlinkage
r_int
id|sys_modify_ldt
c_func
(paren
r_int
id|func
comma
r_void
id|__user
op_star
id|ptr
comma
r_int
r_int
id|bytecount
)paren
suffix:semicolon
id|asmlinkage
r_int
id|sys_mmap2
c_func
(paren
r_int
r_int
id|addr
comma
r_int
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
id|asmlinkage
r_int
id|sys_execve
c_func
(paren
r_struct
id|pt_regs
id|regs
)paren
suffix:semicolon
id|asmlinkage
r_int
id|sys_clone
c_func
(paren
r_struct
id|pt_regs
id|regs
)paren
suffix:semicolon
id|asmlinkage
r_int
id|sys_fork
c_func
(paren
r_struct
id|pt_regs
id|regs
)paren
suffix:semicolon
id|asmlinkage
r_int
id|sys_vfork
c_func
(paren
r_struct
id|pt_regs
id|regs
)paren
suffix:semicolon
id|asmlinkage
r_int
id|sys_pipe
c_func
(paren
r_int
r_int
id|__user
op_star
id|fildes
)paren
suffix:semicolon
id|asmlinkage
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
id|asmlinkage
r_int
id|sys_iopl
c_func
(paren
r_int
r_int
id|unused
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
multiline_comment|/*&n; * &quot;Conditional&quot; syscalls&n; *&n; * What we want is __attribute__((weak,alias(&quot;sys_ni_syscall&quot;))),&n; * but it doesn&squot;t work on all toolchains, so we just do it by hand&n; */
macro_line|#ifndef cond_syscall
DECL|macro|cond_syscall
mdefine_line|#define cond_syscall(x) asm(&quot;.weak&bslash;t&quot; #x &quot;&bslash;n&bslash;t.set&bslash;t&quot; #x &quot;,sys_ni_syscall&quot;);
macro_line|#endif
macro_line|#endif /* _ASM_I386_UNISTD_H_ */
eof
