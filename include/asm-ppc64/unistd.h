macro_line|#ifndef _ASM_PPC_UNISTD_H_
DECL|macro|_ASM_PPC_UNISTD_H_
mdefine_line|#define _ASM_PPC_UNISTD_H_
multiline_comment|/*&n; * This file contains the system call numbers.&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
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
mdefine_line|#define __NR_getrlimit&t;&t; 76
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
DECL|macro|__NR_vm86
mdefine_line|#define __NR_vm86&t;&t;113
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
DECL|macro|__NR_query_module
mdefine_line|#define __NR_query_module&t;166
DECL|macro|__NR_poll
mdefine_line|#define __NR_poll&t;&t;167
DECL|macro|__NR_nfsservctl
mdefine_line|#define __NR_nfsservctl&t;&t;168
DECL|macro|__NR_setresgid
mdefine_line|#define __NR_setresgid&t;&t;169
DECL|macro|__NR_getresgid
mdefine_line|#define __NR_getresgid&t;&t;170
DECL|macro|__NR_prctl
mdefine_line|#define __NR_prctl&t;&t;171
DECL|macro|__NR_rt_sigreturn
mdefine_line|#define __NR_rt_sigreturn&t;172
DECL|macro|__NR_rt_sigaction
mdefine_line|#define __NR_rt_sigaction&t;173
DECL|macro|__NR_rt_sigprocmask
mdefine_line|#define __NR_rt_sigprocmask&t;174
DECL|macro|__NR_rt_sigpending
mdefine_line|#define __NR_rt_sigpending&t;175
DECL|macro|__NR_rt_sigtimedwait
mdefine_line|#define __NR_rt_sigtimedwait&t;176
DECL|macro|__NR_rt_sigqueueinfo
mdefine_line|#define __NR_rt_sigqueueinfo&t;177
DECL|macro|__NR_rt_sigsuspend
mdefine_line|#define __NR_rt_sigsuspend&t;178
DECL|macro|__NR_pread64
mdefine_line|#define __NR_pread64&t;&t;179
DECL|macro|__NR_pwrite64
mdefine_line|#define __NR_pwrite64&t;&t;180
DECL|macro|__NR_chown
mdefine_line|#define __NR_chown&t;&t;181
DECL|macro|__NR_getcwd
mdefine_line|#define __NR_getcwd&t;&t;182
DECL|macro|__NR_capget
mdefine_line|#define __NR_capget&t;&t;183
DECL|macro|__NR_capset
mdefine_line|#define __NR_capset&t;&t;184
DECL|macro|__NR_sigaltstack
mdefine_line|#define __NR_sigaltstack&t;185
DECL|macro|__NR_sendfile
mdefine_line|#define __NR_sendfile&t;&t;186
DECL|macro|__NR_getpmsg
mdefine_line|#define __NR_getpmsg&t;&t;187&t;/* some people actually want streams */
DECL|macro|__NR_putpmsg
mdefine_line|#define __NR_putpmsg&t;&t;188&t;/* some people actually want streams */
DECL|macro|__NR_vfork
mdefine_line|#define __NR_vfork&t;&t;189
DECL|macro|__NR_ugetrlimit
mdefine_line|#define __NR_ugetrlimit&t;&t;190&t;/* SuS compliant getrlimit */
DECL|macro|__NR_readahead
mdefine_line|#define __NR_readahead&t;&t;191
multiline_comment|/* #define __NR_mmap2&t;&t;192&t;32bit only */
multiline_comment|/* #define __NR_truncate64&t;193&t;32bit only */
multiline_comment|/* #define __NR_ftruncate64&t;194&t;32bit only */
multiline_comment|/* #define __NR_stat64&t;&t;195&t;32bit only */
multiline_comment|/* #define __NR_lstat64&t;&t;196&t;32bit only */
multiline_comment|/* #define __NR_fstat64&t;&t;197&t;32bit only */
DECL|macro|__NR_pciconfig_read
mdefine_line|#define __NR_pciconfig_read&t;198
DECL|macro|__NR_pciconfig_write
mdefine_line|#define __NR_pciconfig_write&t;199
DECL|macro|__NR_pciconfig_iobase
mdefine_line|#define __NR_pciconfig_iobase&t;200
DECL|macro|__NR_multiplexer
mdefine_line|#define __NR_multiplexer&t;201
DECL|macro|__NR_getdents64
mdefine_line|#define __NR_getdents64&t;&t;202
DECL|macro|__NR_pivot_root
mdefine_line|#define __NR_pivot_root&t;&t;203
multiline_comment|/* #define __NR_fcntl64&t;&t;204&t;32bit only */
DECL|macro|__NR_madvise
mdefine_line|#define __NR_madvise&t;&t;205
DECL|macro|__NR_mincore
mdefine_line|#define __NR_mincore&t;&t;206
DECL|macro|__NR_gettid
mdefine_line|#define __NR_gettid&t;&t;207
DECL|macro|__NR_tkill
mdefine_line|#define __NR_tkill&t;&t;208
DECL|macro|__NR_setxattr
mdefine_line|#define __NR_setxattr&t;&t;209
DECL|macro|__NR_lsetxattr
mdefine_line|#define __NR_lsetxattr&t;&t;210
DECL|macro|__NR_fsetxattr
mdefine_line|#define __NR_fsetxattr&t;&t;211
DECL|macro|__NR_getxattr
mdefine_line|#define __NR_getxattr&t;&t;212
DECL|macro|__NR_lgetxattr
mdefine_line|#define __NR_lgetxattr&t;&t;213
DECL|macro|__NR_fgetxattr
mdefine_line|#define __NR_fgetxattr&t;&t;214
DECL|macro|__NR_listxattr
mdefine_line|#define __NR_listxattr&t;&t;215
DECL|macro|__NR_llistxattr
mdefine_line|#define __NR_llistxattr&t;&t;216
DECL|macro|__NR_flistxattr
mdefine_line|#define __NR_flistxattr&t;&t;217
DECL|macro|__NR_removexattr
mdefine_line|#define __NR_removexattr&t;218
DECL|macro|__NR_lremovexattr
mdefine_line|#define __NR_lremovexattr&t;219
DECL|macro|__NR_fremovexattr
mdefine_line|#define __NR_fremovexattr&t;220
DECL|macro|__NR_futex
mdefine_line|#define __NR_futex&t;&t;221
DECL|macro|__NR_sched_setaffinity
mdefine_line|#define __NR_sched_setaffinity&t;222
DECL|macro|__NR_sched_getaffinity
mdefine_line|#define __NR_sched_getaffinity&t;223
multiline_comment|/* 224 currently unused */
DECL|macro|__NR_tuxcall
mdefine_line|#define __NR_tuxcall&t;&t;225
multiline_comment|/* #define __NR_sendfile64&t;226&t;32bit only */
DECL|macro|__NR_io_setup
mdefine_line|#define __NR_io_setup&t;&t;227
DECL|macro|__NR_io_destroy
mdefine_line|#define __NR_io_destroy&t;&t;228
DECL|macro|__NR_io_getevents
mdefine_line|#define __NR_io_getevents&t;229
DECL|macro|__NR_io_submit
mdefine_line|#define __NR_io_submit&t;&t;230
DECL|macro|__NR_io_cancel
mdefine_line|#define __NR_io_cancel&t;&t;231
DECL|macro|__NR_set_tid_address
mdefine_line|#define __NR_set_tid_address&t;232
DECL|macro|__NR_fadvise64
mdefine_line|#define __NR_fadvise64&t;&t;233
DECL|macro|__NR_exit_group
mdefine_line|#define __NR_exit_group&t;&t;234
DECL|macro|__NR_lookup_dcookie
mdefine_line|#define __NR_lookup_dcookie&t;235
DECL|macro|__NR_epoll_create
mdefine_line|#define __NR_epoll_create&t;236
DECL|macro|__NR_epoll_ctl
mdefine_line|#define __NR_epoll_ctl&t;&t;237
DECL|macro|__NR_epoll_wait
mdefine_line|#define __NR_epoll_wait&t;&t;238
DECL|macro|__NR_remap_file_pages
mdefine_line|#define __NR_remap_file_pages&t;239
DECL|macro|__NR_timer_create
mdefine_line|#define __NR_timer_create&t;240
DECL|macro|__NR_timer_settime
mdefine_line|#define __NR_timer_settime&t;241
DECL|macro|__NR_timer_gettime
mdefine_line|#define __NR_timer_gettime&t;242
DECL|macro|__NR_timer_getoverrun
mdefine_line|#define __NR_timer_getoverrun&t;243
DECL|macro|__NR_timer_delete
mdefine_line|#define __NR_timer_delete&t;244
DECL|macro|__NR_clock_settime
mdefine_line|#define __NR_clock_settime&t;245
DECL|macro|__NR_clock_gettime
mdefine_line|#define __NR_clock_gettime&t;246
DECL|macro|__NR_clock_getres
mdefine_line|#define __NR_clock_getres&t;247
DECL|macro|__NR_clock_nanosleep
mdefine_line|#define __NR_clock_nanosleep&t;248
DECL|macro|__NR_swapcontext
mdefine_line|#define __NR_swapcontext&t;249
DECL|macro|__NR_tgkill
mdefine_line|#define __NR_tgkill&t;&t;250
DECL|macro|__NR_utimes
mdefine_line|#define __NR_utimes&t;&t;251
DECL|macro|__NR_statfs64
mdefine_line|#define __NR_statfs64&t;&t;252
DECL|macro|__NR_fstatfs64
mdefine_line|#define __NR_fstatfs64&t;&t;253
multiline_comment|/* #define __NR_fadvise64_64&t;254&t;32bit only */
DECL|macro|__NR_rtas
mdefine_line|#define __NR_rtas&t;&t;255
multiline_comment|/* Number 256 is reserved for sys_debug_setcontext */
multiline_comment|/* Number 257 is reserved for vserver */
multiline_comment|/* Number 258 is reserved for new sys_remap_file_pages */
DECL|macro|__NR_mbind
mdefine_line|#define __NR_mbind&t;&t;259
DECL|macro|__NR_get_mempolicy
mdefine_line|#define __NR_get_mempolicy&t;260
DECL|macro|__NR_set_mempolicy
mdefine_line|#define __NR_set_mempolicy&t;261
DECL|macro|__NR_mq_open
mdefine_line|#define __NR_mq_open&t;&t;262
DECL|macro|__NR_mq_unlink
mdefine_line|#define __NR_mq_unlink&t;&t;263
DECL|macro|__NR_mq_timedsend
mdefine_line|#define __NR_mq_timedsend&t;264
DECL|macro|__NR_mq_timedreceive
mdefine_line|#define __NR_mq_timedreceive&t;265
DECL|macro|__NR_mq_notify
mdefine_line|#define __NR_mq_notify&t;&t;266
DECL|macro|__NR_mq_getsetattr
mdefine_line|#define __NR_mq_getsetattr&t;267
DECL|macro|__NR_kexec_load
mdefine_line|#define __NR_kexec_load&t;&t;268
DECL|macro|__NR_add_key
mdefine_line|#define __NR_add_key&t;&t;269
DECL|macro|__NR_request_key
mdefine_line|#define __NR_request_key&t;270
DECL|macro|__NR_keyctl
mdefine_line|#define __NR_keyctl&t;&t;271
DECL|macro|__NR_waitid
mdefine_line|#define __NR_waitid&t;&t;272
DECL|macro|__NR_syscalls
mdefine_line|#define __NR_syscalls&t;&t;273
macro_line|#ifdef __KERNEL__
DECL|macro|NR_syscalls
mdefine_line|#define NR_syscalls&t;__NR_syscalls
macro_line|#endif
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/* On powerpc a system call basically clobbers the same registers like a&n; * function call, with the exception of LR (which is needed for the&n; * &quot;sc; bnslr&quot; sequence) and CR (where only CR0.SO is clobbered to signal&n; * an error return status).&n; */
DECL|macro|__syscall_nr
mdefine_line|#define __syscall_nr(nr, type, name, args...)&t;&t;&t;&t;&bslash;&n;&t;unsigned long __sc_ret, __sc_err;&t;&t;&t;&t;&bslash;&n;&t;{&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;register unsigned long __sc_0  __asm__ (&quot;r0&quot;);&t;&t;&bslash;&n;&t;&t;register unsigned long __sc_3  __asm__ (&quot;r3&quot;);&t;&t;&bslash;&n;&t;&t;register unsigned long __sc_4  __asm__ (&quot;r4&quot;);&t;&t;&bslash;&n;&t;&t;register unsigned long __sc_5  __asm__ (&quot;r5&quot;);&t;&t;&bslash;&n;&t;&t;register unsigned long __sc_6  __asm__ (&quot;r6&quot;);&t;&t;&bslash;&n;&t;&t;register unsigned long __sc_7  __asm__ (&quot;r7&quot;);&t;&t;&bslash;&n;&t;&t;register unsigned long __sc_8  __asm__ (&quot;r8&quot;);&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__sc_loadargs_##nr(name, args);&t;&t;&t;&t;&bslash;&n;&t;&t;__asm__ __volatile__&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;(&quot;sc           &bslash;n&bslash;t&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&t; &quot;mfcr %0      &quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;: &quot;=&amp;r&quot; (__sc_0),&t;&t;&t;&t;&bslash;&n;&t;&t;&t;  &quot;=&amp;r&quot; (__sc_3),  &quot;=&amp;r&quot; (__sc_4),&t;&t;&bslash;&n;&t;&t;&t;  &quot;=&amp;r&quot; (__sc_5),  &quot;=&amp;r&quot; (__sc_6),&t;&t;&bslash;&n;&t;&t;&t;  &quot;=&amp;r&quot; (__sc_7),  &quot;=&amp;r&quot; (__sc_8)&t;&t;&bslash;&n;&t;&t;&t;: __sc_asm_input_##nr&t;&t;&t;&t;&bslash;&n;&t;&t;&t;: &quot;cr0&quot;, &quot;ctr&quot;, &quot;memory&quot;,&t;&t;&t;&bslash;&n;&t;&t;&t;        &quot;r9&quot;, &quot;r10&quot;,&quot;r11&quot;, &quot;r12&quot;);&t;&t;&bslash;&n;&t;&t;__sc_ret = __sc_3;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__sc_err = __sc_0;&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (__sc_err &amp; 0x10000000)&t;&t;&t;&t;&t;&bslash;&n;&t;{&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;errno = __sc_ret;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__sc_ret = -1;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;return (type) __sc_ret
DECL|macro|__sc_loadargs_0
mdefine_line|#define __sc_loadargs_0(name, dummy...)&t;&t;&t;&t;&t;&bslash;&n;&t;__sc_0 = __NR_##name
DECL|macro|__sc_loadargs_1
mdefine_line|#define __sc_loadargs_1(name, arg1)&t;&t;&t;&t;&t;&bslash;&n;&t;__sc_loadargs_0(name);&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__sc_3 = (unsigned long) (arg1)
DECL|macro|__sc_loadargs_2
mdefine_line|#define __sc_loadargs_2(name, arg1, arg2)&t;&t;&t;&t;&bslash;&n;&t;__sc_loadargs_1(name, arg1);&t;&t;&t;&t;&t;&bslash;&n;&t;__sc_4 = (unsigned long) (arg2)
DECL|macro|__sc_loadargs_3
mdefine_line|#define __sc_loadargs_3(name, arg1, arg2, arg3)&t;&t;&t;&t;&bslash;&n;&t;__sc_loadargs_2(name, arg1, arg2);&t;&t;&t;&t;&bslash;&n;&t;__sc_5 = (unsigned long) (arg3)
DECL|macro|__sc_loadargs_4
mdefine_line|#define __sc_loadargs_4(name, arg1, arg2, arg3, arg4)&t;&t;&t;&bslash;&n;&t;__sc_loadargs_3(name, arg1, arg2, arg3);&t;&t;&t;&bslash;&n;&t;__sc_6 = (unsigned long) (arg4)
DECL|macro|__sc_loadargs_5
mdefine_line|#define __sc_loadargs_5(name, arg1, arg2, arg3, arg4, arg5)&t;&t;&bslash;&n;&t;__sc_loadargs_4(name, arg1, arg2, arg3, arg4);&t;&t;&t;&bslash;&n;&t;__sc_7 = (unsigned long) (arg5)
DECL|macro|__sc_loadargs_6
mdefine_line|#define __sc_loadargs_6(name, arg1, arg2, arg3, arg4, arg5, arg6)&t;&bslash;&n;&t;__sc_loadargs_5(name, arg1, arg2, arg3, arg4, arg5);&t;&t;&bslash;&n;&t;__sc_8 = (unsigned long) (arg6)
DECL|macro|__sc_asm_input_0
mdefine_line|#define __sc_asm_input_0 &quot;0&quot; (__sc_0)
DECL|macro|__sc_asm_input_1
mdefine_line|#define __sc_asm_input_1 __sc_asm_input_0, &quot;1&quot; (__sc_3)
DECL|macro|__sc_asm_input_2
mdefine_line|#define __sc_asm_input_2 __sc_asm_input_1, &quot;2&quot; (__sc_4)
DECL|macro|__sc_asm_input_3
mdefine_line|#define __sc_asm_input_3 __sc_asm_input_2, &quot;3&quot; (__sc_5)
DECL|macro|__sc_asm_input_4
mdefine_line|#define __sc_asm_input_4 __sc_asm_input_3, &quot;4&quot; (__sc_6)
DECL|macro|__sc_asm_input_5
mdefine_line|#define __sc_asm_input_5 __sc_asm_input_4, &quot;5&quot; (__sc_7)
DECL|macro|__sc_asm_input_6
mdefine_line|#define __sc_asm_input_6 __sc_asm_input_5, &quot;6&quot; (__sc_8)
DECL|macro|_syscall0
mdefine_line|#define _syscall0(type,name)&t;&t;&t;&t;&t;&t;&bslash;&n;type name(void)&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__syscall_nr(0, type, name);&t;&t;&t;&t;&t;&bslash;&n;}
DECL|macro|_syscall1
mdefine_line|#define _syscall1(type,name,type1,arg1)&t;&t;&t;&t;&t;&bslash;&n;type name(type1 arg1)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__syscall_nr(1, type, name, arg1);&t;&t;&t;&t;&bslash;&n;}
DECL|macro|_syscall2
mdefine_line|#define _syscall2(type,name,type1,arg1,type2,arg2)&t;&t;&t;&bslash;&n;type name(type1 arg1, type2 arg2)&t;&t;&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__syscall_nr(2, type, name, arg1, arg2);&t;&t;&t;&bslash;&n;}
DECL|macro|_syscall3
mdefine_line|#define _syscall3(type,name,type1,arg1,type2,arg2,type3,arg3)&t;&t;&bslash;&n;type name(type1 arg1, type2 arg2, type3 arg3)&t;&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__syscall_nr(3, type, name, arg1, arg2, arg3);&t;&t;&t;&bslash;&n;}
DECL|macro|_syscall4
mdefine_line|#define _syscall4(type,name,type1,arg1,type2,arg2,type3,arg3,type4,arg4) &bslash;&n;type name(type1 arg1, type2 arg2, type3 arg3, type4 arg4)&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__syscall_nr(4, type, name, arg1, arg2, arg3, arg4);&t;&t;&bslash;&n;}
DECL|macro|_syscall5
mdefine_line|#define _syscall5(type,name,type1,arg1,type2,arg2,type3,arg3,type4,arg4,type5,arg5) &bslash;&n;type name(type1 arg1, type2 arg2, type3 arg3, type4 arg4, type5 arg5)&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__syscall_nr(5, type, name, arg1, arg2, arg3, arg4, arg5);&t;&bslash;&n;}
DECL|macro|_syscall6
mdefine_line|#define _syscall6(type,name,type1,arg1,type2,arg2,type3,arg3,type4,arg4,type5,arg5,type6,arg6) &bslash;&n;type name(type1 arg1, type2 arg2, type3 arg3, type4 arg4, type5 arg5, type6 arg6)&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__syscall_nr(6, type, name, arg1, arg2, arg3, arg4, arg5, arg6);&t;&bslash;&n;}
macro_line|#ifdef __KERNEL_SYSCALLS__
multiline_comment|/*&n; * Forking from kernel space will result in the child getting a new,&n; * empty kernel stack area.  Thus the child cannot access automatic&n; * variables set in the parent unless they are in registers, and the&n; * procedure where the fork was done cannot return to its caller in&n; * the child.&n; */
multiline_comment|/*&n; * System call prototypes.&n; */
r_static
r_inline
id|_syscall3
c_func
(paren
r_int
comma
id|execve
comma
id|__const__
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
macro_line|#endif /* __KERNEL_SYSCALLS__ */
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/compiler.h&gt;
macro_line|#include &lt;linux/linkage.h&gt;
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
DECL|macro|__ARCH_WANT_COMPAT_SYS_TIME
mdefine_line|#define __ARCH_WANT_COMPAT_SYS_TIME
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
r_struct
id|pt_regs
suffix:semicolon
r_int
id|sys_execve
c_func
(paren
r_int
r_int
id|a0
comma
r_int
r_int
id|a1
comma
r_int
r_int
id|a2
comma
r_int
r_int
id|a3
comma
r_int
r_int
id|a4
comma
r_int
r_int
id|a5
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_int
id|sys_clone
c_func
(paren
r_int
r_int
id|clone_flags
comma
r_int
r_int
id|p2
comma
r_int
r_int
id|p3
comma
r_int
r_int
id|p4
comma
r_int
r_int
id|p5
comma
r_int
r_int
id|p6
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_int
id|sys_fork
c_func
(paren
r_int
r_int
id|p1
comma
r_int
r_int
id|p2
comma
r_int
r_int
id|p3
comma
r_int
r_int
id|p4
comma
r_int
r_int
id|p5
comma
r_int
r_int
id|p6
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_int
id|sys_vfork
c_func
(paren
r_int
r_int
id|p1
comma
r_int
r_int
id|p2
comma
r_int
r_int
id|p3
comma
r_int
r_int
id|p4
comma
r_int
r_int
id|p5
comma
r_int
r_int
id|p6
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_int
id|sys_pipe
c_func
(paren
r_int
id|__user
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
multiline_comment|/*&n; * &quot;Conditional&quot; syscalls&n; *&n; * What we want is __attribute__((weak,alias(&quot;sys_ni_syscall&quot;))),&n; * but it doesn&squot;t work on all toolchains, so we just do it by hand&n; */
DECL|macro|cond_syscall
mdefine_line|#define cond_syscall(x) asm(&quot;.weak&bslash;t.&quot; #x &quot;&bslash;n&bslash;t.set&bslash;t.&quot; #x &quot;,.sys_ni_syscall&quot;)
macro_line|#endif&t;&t;/* __KERNEL__ */
macro_line|#endif&t;&t;/* __ASSEMBLY__ */
macro_line|#endif /* _ASM_PPC_UNISTD_H_ */
eof
