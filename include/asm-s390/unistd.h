multiline_comment|/*&n; *  include/asm-s390/unistd.h&n; *&n; *  S390 version&n; *&n; *  Derived from &quot;include/asm-i386/unistd.h&quot;&n; */
macro_line|#ifndef _ASM_S390_UNISTD_H_
DECL|macro|_ASM_S390_UNISTD_H_
mdefine_line|#define _ASM_S390_UNISTD_H_
multiline_comment|/*&n; * This file contains the system call numbers.&n; */
DECL|macro|__NR_exit
mdefine_line|#define __NR_exit                 1
DECL|macro|__NR_fork
mdefine_line|#define __NR_fork                 2
DECL|macro|__NR_read
mdefine_line|#define __NR_read                 3
DECL|macro|__NR_write
mdefine_line|#define __NR_write                4
DECL|macro|__NR_open
mdefine_line|#define __NR_open                 5
DECL|macro|__NR_close
mdefine_line|#define __NR_close                6
DECL|macro|__NR_restart_syscall
mdefine_line|#define __NR_restart_syscall&t;  7
DECL|macro|__NR_creat
mdefine_line|#define __NR_creat                8
DECL|macro|__NR_link
mdefine_line|#define __NR_link                 9
DECL|macro|__NR_unlink
mdefine_line|#define __NR_unlink              10
DECL|macro|__NR_execve
mdefine_line|#define __NR_execve              11
DECL|macro|__NR_chdir
mdefine_line|#define __NR_chdir               12
DECL|macro|__NR_time
mdefine_line|#define __NR_time                13
DECL|macro|__NR_mknod
mdefine_line|#define __NR_mknod               14
DECL|macro|__NR_chmod
mdefine_line|#define __NR_chmod               15
DECL|macro|__NR_lchown
mdefine_line|#define __NR_lchown              16
DECL|macro|__NR_lseek
mdefine_line|#define __NR_lseek               19
DECL|macro|__NR_getpid
mdefine_line|#define __NR_getpid              20
DECL|macro|__NR_mount
mdefine_line|#define __NR_mount               21
DECL|macro|__NR_umount
mdefine_line|#define __NR_umount              22
DECL|macro|__NR_setuid
mdefine_line|#define __NR_setuid              23
DECL|macro|__NR_getuid
mdefine_line|#define __NR_getuid              24
DECL|macro|__NR_stime
mdefine_line|#define __NR_stime               25
DECL|macro|__NR_ptrace
mdefine_line|#define __NR_ptrace              26
DECL|macro|__NR_alarm
mdefine_line|#define __NR_alarm               27
DECL|macro|__NR_pause
mdefine_line|#define __NR_pause               29
DECL|macro|__NR_utime
mdefine_line|#define __NR_utime               30
DECL|macro|__NR_access
mdefine_line|#define __NR_access              33
DECL|macro|__NR_nice
mdefine_line|#define __NR_nice                34
DECL|macro|__NR_sync
mdefine_line|#define __NR_sync                36
DECL|macro|__NR_kill
mdefine_line|#define __NR_kill                37
DECL|macro|__NR_rename
mdefine_line|#define __NR_rename              38
DECL|macro|__NR_mkdir
mdefine_line|#define __NR_mkdir               39
DECL|macro|__NR_rmdir
mdefine_line|#define __NR_rmdir               40
DECL|macro|__NR_dup
mdefine_line|#define __NR_dup                 41
DECL|macro|__NR_pipe
mdefine_line|#define __NR_pipe                42
DECL|macro|__NR_times
mdefine_line|#define __NR_times               43
DECL|macro|__NR_brk
mdefine_line|#define __NR_brk                 45
DECL|macro|__NR_setgid
mdefine_line|#define __NR_setgid              46
DECL|macro|__NR_getgid
mdefine_line|#define __NR_getgid              47
DECL|macro|__NR_signal
mdefine_line|#define __NR_signal              48
DECL|macro|__NR_geteuid
mdefine_line|#define __NR_geteuid             49
DECL|macro|__NR_getegid
mdefine_line|#define __NR_getegid             50
DECL|macro|__NR_acct
mdefine_line|#define __NR_acct                51
DECL|macro|__NR_umount2
mdefine_line|#define __NR_umount2             52
DECL|macro|__NR_ioctl
mdefine_line|#define __NR_ioctl               54
DECL|macro|__NR_fcntl
mdefine_line|#define __NR_fcntl               55
DECL|macro|__NR_setpgid
mdefine_line|#define __NR_setpgid             57
DECL|macro|__NR_umask
mdefine_line|#define __NR_umask               60
DECL|macro|__NR_chroot
mdefine_line|#define __NR_chroot              61
DECL|macro|__NR_ustat
mdefine_line|#define __NR_ustat               62
DECL|macro|__NR_dup2
mdefine_line|#define __NR_dup2                63
DECL|macro|__NR_getppid
mdefine_line|#define __NR_getppid             64
DECL|macro|__NR_getpgrp
mdefine_line|#define __NR_getpgrp             65
DECL|macro|__NR_setsid
mdefine_line|#define __NR_setsid              66
DECL|macro|__NR_sigaction
mdefine_line|#define __NR_sigaction           67
DECL|macro|__NR_setreuid
mdefine_line|#define __NR_setreuid            70
DECL|macro|__NR_setregid
mdefine_line|#define __NR_setregid            71
DECL|macro|__NR_sigsuspend
mdefine_line|#define __NR_sigsuspend          72
DECL|macro|__NR_sigpending
mdefine_line|#define __NR_sigpending          73
DECL|macro|__NR_sethostname
mdefine_line|#define __NR_sethostname         74
DECL|macro|__NR_setrlimit
mdefine_line|#define __NR_setrlimit           75
DECL|macro|__NR_getrlimit
mdefine_line|#define __NR_getrlimit           76
DECL|macro|__NR_getrusage
mdefine_line|#define __NR_getrusage           77
DECL|macro|__NR_gettimeofday
mdefine_line|#define __NR_gettimeofday        78
DECL|macro|__NR_settimeofday
mdefine_line|#define __NR_settimeofday        79
DECL|macro|__NR_getgroups
mdefine_line|#define __NR_getgroups           80
DECL|macro|__NR_setgroups
mdefine_line|#define __NR_setgroups           81
DECL|macro|__NR_symlink
mdefine_line|#define __NR_symlink             83
DECL|macro|__NR_readlink
mdefine_line|#define __NR_readlink            85
DECL|macro|__NR_uselib
mdefine_line|#define __NR_uselib              86
DECL|macro|__NR_swapon
mdefine_line|#define __NR_swapon              87
DECL|macro|__NR_reboot
mdefine_line|#define __NR_reboot              88
DECL|macro|__NR_readdir
mdefine_line|#define __NR_readdir             89
DECL|macro|__NR_mmap
mdefine_line|#define __NR_mmap                90
DECL|macro|__NR_munmap
mdefine_line|#define __NR_munmap              91
DECL|macro|__NR_truncate
mdefine_line|#define __NR_truncate            92
DECL|macro|__NR_ftruncate
mdefine_line|#define __NR_ftruncate           93
DECL|macro|__NR_fchmod
mdefine_line|#define __NR_fchmod              94
DECL|macro|__NR_fchown
mdefine_line|#define __NR_fchown              95
DECL|macro|__NR_getpriority
mdefine_line|#define __NR_getpriority         96
DECL|macro|__NR_setpriority
mdefine_line|#define __NR_setpriority         97
DECL|macro|__NR_statfs
mdefine_line|#define __NR_statfs              99
DECL|macro|__NR_fstatfs
mdefine_line|#define __NR_fstatfs            100
DECL|macro|__NR_ioperm
mdefine_line|#define __NR_ioperm             101
DECL|macro|__NR_socketcall
mdefine_line|#define __NR_socketcall         102
DECL|macro|__NR_syslog
mdefine_line|#define __NR_syslog             103
DECL|macro|__NR_setitimer
mdefine_line|#define __NR_setitimer          104
DECL|macro|__NR_getitimer
mdefine_line|#define __NR_getitimer          105
DECL|macro|__NR_stat
mdefine_line|#define __NR_stat               106
DECL|macro|__NR_lstat
mdefine_line|#define __NR_lstat              107
DECL|macro|__NR_fstat
mdefine_line|#define __NR_fstat              108
DECL|macro|__NR_lookup_dcookie
mdefine_line|#define __NR_lookup_dcookie     110
DECL|macro|__NR_vhangup
mdefine_line|#define __NR_vhangup            111
DECL|macro|__NR_idle
mdefine_line|#define __NR_idle               112
DECL|macro|__NR_wait4
mdefine_line|#define __NR_wait4              114
DECL|macro|__NR_swapoff
mdefine_line|#define __NR_swapoff            115
DECL|macro|__NR_sysinfo
mdefine_line|#define __NR_sysinfo            116
DECL|macro|__NR_ipc
mdefine_line|#define __NR_ipc                117
DECL|macro|__NR_fsync
mdefine_line|#define __NR_fsync              118
DECL|macro|__NR_sigreturn
mdefine_line|#define __NR_sigreturn          119
DECL|macro|__NR_clone
mdefine_line|#define __NR_clone              120
DECL|macro|__NR_setdomainname
mdefine_line|#define __NR_setdomainname      121
DECL|macro|__NR_uname
mdefine_line|#define __NR_uname              122
DECL|macro|__NR_adjtimex
mdefine_line|#define __NR_adjtimex           124
DECL|macro|__NR_mprotect
mdefine_line|#define __NR_mprotect           125
DECL|macro|__NR_sigprocmask
mdefine_line|#define __NR_sigprocmask        126
DECL|macro|__NR_create_module
mdefine_line|#define __NR_create_module      127
DECL|macro|__NR_init_module
mdefine_line|#define __NR_init_module        128
DECL|macro|__NR_delete_module
mdefine_line|#define __NR_delete_module      129
DECL|macro|__NR_get_kernel_syms
mdefine_line|#define __NR_get_kernel_syms    130
DECL|macro|__NR_quotactl
mdefine_line|#define __NR_quotactl           131
DECL|macro|__NR_getpgid
mdefine_line|#define __NR_getpgid            132
DECL|macro|__NR_fchdir
mdefine_line|#define __NR_fchdir             133
DECL|macro|__NR_bdflush
mdefine_line|#define __NR_bdflush            134
DECL|macro|__NR_sysfs
mdefine_line|#define __NR_sysfs              135
DECL|macro|__NR_personality
mdefine_line|#define __NR_personality        136
DECL|macro|__NR_afs_syscall
mdefine_line|#define __NR_afs_syscall        137 /* Syscall for Andrew File System */
DECL|macro|__NR_setfsuid
mdefine_line|#define __NR_setfsuid           138
DECL|macro|__NR_setfsgid
mdefine_line|#define __NR_setfsgid           139
DECL|macro|__NR__llseek
mdefine_line|#define __NR__llseek            140
DECL|macro|__NR_getdents
mdefine_line|#define __NR_getdents           141
DECL|macro|__NR__newselect
mdefine_line|#define __NR__newselect         142
DECL|macro|__NR_flock
mdefine_line|#define __NR_flock              143
DECL|macro|__NR_msync
mdefine_line|#define __NR_msync              144
DECL|macro|__NR_readv
mdefine_line|#define __NR_readv              145
DECL|macro|__NR_writev
mdefine_line|#define __NR_writev             146
DECL|macro|__NR_getsid
mdefine_line|#define __NR_getsid             147
DECL|macro|__NR_fdatasync
mdefine_line|#define __NR_fdatasync          148
DECL|macro|__NR__sysctl
mdefine_line|#define __NR__sysctl            149
DECL|macro|__NR_mlock
mdefine_line|#define __NR_mlock              150
DECL|macro|__NR_munlock
mdefine_line|#define __NR_munlock            151
DECL|macro|__NR_mlockall
mdefine_line|#define __NR_mlockall           152
DECL|macro|__NR_munlockall
mdefine_line|#define __NR_munlockall         153
DECL|macro|__NR_sched_setparam
mdefine_line|#define __NR_sched_setparam             154
DECL|macro|__NR_sched_getparam
mdefine_line|#define __NR_sched_getparam             155
DECL|macro|__NR_sched_setscheduler
mdefine_line|#define __NR_sched_setscheduler         156
DECL|macro|__NR_sched_getscheduler
mdefine_line|#define __NR_sched_getscheduler         157
DECL|macro|__NR_sched_yield
mdefine_line|#define __NR_sched_yield                158
DECL|macro|__NR_sched_get_priority_max
mdefine_line|#define __NR_sched_get_priority_max     159
DECL|macro|__NR_sched_get_priority_min
mdefine_line|#define __NR_sched_get_priority_min     160
DECL|macro|__NR_sched_rr_get_interval
mdefine_line|#define __NR_sched_rr_get_interval      161
DECL|macro|__NR_nanosleep
mdefine_line|#define __NR_nanosleep          162
DECL|macro|__NR_mremap
mdefine_line|#define __NR_mremap             163
DECL|macro|__NR_setresuid
mdefine_line|#define __NR_setresuid          164
DECL|macro|__NR_getresuid
mdefine_line|#define __NR_getresuid          165
DECL|macro|__NR_query_module
mdefine_line|#define __NR_query_module       167
DECL|macro|__NR_poll
mdefine_line|#define __NR_poll               168
DECL|macro|__NR_nfsservctl
mdefine_line|#define __NR_nfsservctl         169
DECL|macro|__NR_setresgid
mdefine_line|#define __NR_setresgid          170
DECL|macro|__NR_getresgid
mdefine_line|#define __NR_getresgid          171
DECL|macro|__NR_prctl
mdefine_line|#define __NR_prctl              172
DECL|macro|__NR_rt_sigreturn
mdefine_line|#define __NR_rt_sigreturn       173
DECL|macro|__NR_rt_sigaction
mdefine_line|#define __NR_rt_sigaction       174
DECL|macro|__NR_rt_sigprocmask
mdefine_line|#define __NR_rt_sigprocmask     175
DECL|macro|__NR_rt_sigpending
mdefine_line|#define __NR_rt_sigpending      176
DECL|macro|__NR_rt_sigtimedwait
mdefine_line|#define __NR_rt_sigtimedwait    177
DECL|macro|__NR_rt_sigqueueinfo
mdefine_line|#define __NR_rt_sigqueueinfo    178
DECL|macro|__NR_rt_sigsuspend
mdefine_line|#define __NR_rt_sigsuspend      179
DECL|macro|__NR_pread64
mdefine_line|#define __NR_pread64            180
DECL|macro|__NR_pwrite64
mdefine_line|#define __NR_pwrite64           181
DECL|macro|__NR_chown
mdefine_line|#define __NR_chown              182
DECL|macro|__NR_getcwd
mdefine_line|#define __NR_getcwd             183
DECL|macro|__NR_capget
mdefine_line|#define __NR_capget             184
DECL|macro|__NR_capset
mdefine_line|#define __NR_capset             185
DECL|macro|__NR_sigaltstack
mdefine_line|#define __NR_sigaltstack        186
DECL|macro|__NR_sendfile
mdefine_line|#define __NR_sendfile           187
DECL|macro|__NR_getpmsg
mdefine_line|#define __NR_getpmsg&t;&t;188
DECL|macro|__NR_putpmsg
mdefine_line|#define __NR_putpmsg&t;&t;189
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
mdefine_line|#define __NR_pivot_root         217
DECL|macro|__NR_mincore
mdefine_line|#define __NR_mincore            218
DECL|macro|__NR_madvise
mdefine_line|#define __NR_madvise            219
DECL|macro|__NR_getdents64
mdefine_line|#define __NR_getdents64&t;&t;220
DECL|macro|__NR_fcntl64
mdefine_line|#define __NR_fcntl64&t;&t;221
DECL|macro|__NR_readahead
mdefine_line|#define __NR_readahead&t;&t;222
DECL|macro|__NR_sendfile64
mdefine_line|#define __NR_sendfile64&t;&t;223
DECL|macro|__NR_setxattr
mdefine_line|#define __NR_setxattr&t;&t;224
DECL|macro|__NR_lsetxattr
mdefine_line|#define __NR_lsetxattr&t;&t;225
DECL|macro|__NR_fsetxattr
mdefine_line|#define __NR_fsetxattr&t;&t;226
DECL|macro|__NR_getxattr
mdefine_line|#define __NR_getxattr&t;&t;227
DECL|macro|__NR_lgetxattr
mdefine_line|#define __NR_lgetxattr&t;&t;228
DECL|macro|__NR_fgetxattr
mdefine_line|#define __NR_fgetxattr&t;&t;229
DECL|macro|__NR_listxattr
mdefine_line|#define __NR_listxattr&t;&t;230
DECL|macro|__NR_llistxattr
mdefine_line|#define __NR_llistxattr&t;&t;231
DECL|macro|__NR_flistxattr
mdefine_line|#define __NR_flistxattr&t;&t;232
DECL|macro|__NR_removexattr
mdefine_line|#define __NR_removexattr&t;233
DECL|macro|__NR_lremovexattr
mdefine_line|#define __NR_lremovexattr&t;234
DECL|macro|__NR_fremovexattr
mdefine_line|#define __NR_fremovexattr&t;235
DECL|macro|__NR_gettid
mdefine_line|#define __NR_gettid&t;&t;236
DECL|macro|__NR_tkill
mdefine_line|#define __NR_tkill&t;&t;237
DECL|macro|__NR_futex
mdefine_line|#define __NR_futex&t;&t;238
DECL|macro|__NR_sched_setaffinity
mdefine_line|#define __NR_sched_setaffinity&t;239
DECL|macro|__NR_sched_getaffinity
mdefine_line|#define __NR_sched_getaffinity&t;240
DECL|macro|__NR_tgkill
mdefine_line|#define __NR_tgkill&t;&t;241
multiline_comment|/* Number 242 is reserved for tux */
DECL|macro|__NR_io_setup
mdefine_line|#define __NR_io_setup&t;&t;243
DECL|macro|__NR_io_destroy
mdefine_line|#define __NR_io_destroy&t;&t;244
DECL|macro|__NR_io_getevents
mdefine_line|#define __NR_io_getevents&t;245
DECL|macro|__NR_io_submit
mdefine_line|#define __NR_io_submit&t;&t;246
DECL|macro|__NR_io_cancel
mdefine_line|#define __NR_io_cancel&t;&t;247
DECL|macro|__NR_exit_group
mdefine_line|#define __NR_exit_group&t;&t;248
DECL|macro|__NR_epoll_create
mdefine_line|#define __NR_epoll_create&t;249
DECL|macro|__NR_epoll_ctl
mdefine_line|#define __NR_epoll_ctl&t;&t;250
DECL|macro|__NR_epoll_wait
mdefine_line|#define __NR_epoll_wait&t;&t;251
DECL|macro|__NR_set_tid_address
mdefine_line|#define __NR_set_tid_address&t;252
DECL|macro|__NR_fadvise64
mdefine_line|#define __NR_fadvise64&t;&t;253
DECL|macro|__NR_timer_create
mdefine_line|#define __NR_timer_create&t;254
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
multiline_comment|/* Number 263 is reserved for vserver */
DECL|macro|__NR_fadvise64_64
mdefine_line|#define __NR_fadvise64_64&t;264
DECL|macro|__NR_statfs64
mdefine_line|#define __NR_statfs64&t;&t;265
DECL|macro|__NR_fstatfs64
mdefine_line|#define __NR_fstatfs64&t;&t;266
multiline_comment|/* Number 267 is reserved for new sys_remap_file_pages */
multiline_comment|/* Number 268 is reserved for new sys_mbind */
multiline_comment|/* Number 269 is reserved for new sys_get_mempolicy */
multiline_comment|/* Number 270 is reserved for new sys_set_mempolicy */
DECL|macro|__NR_mq_open
mdefine_line|#define __NR_mq_open&t;&t;271
DECL|macro|__NR_mq_unlink
mdefine_line|#define __NR_mq_unlink&t;&t;272
DECL|macro|__NR_mq_timedsend
mdefine_line|#define __NR_mq_timedsend&t;273
DECL|macro|__NR_mq_timedreceive
mdefine_line|#define __NR_mq_timedreceive&t;274
DECL|macro|__NR_mq_notify
mdefine_line|#define __NR_mq_notify&t;&t;275
DECL|macro|__NR_mq_getsetattr
mdefine_line|#define __NR_mq_getsetattr&t;276
multiline_comment|/* Number 277 is reserved for new sys_kexec_load */
DECL|macro|NR_syscalls
mdefine_line|#define NR_syscalls 278
multiline_comment|/* &n; * There are some system calls that are not present on 64 bit, some&n; * have a different name although they do the same (e.g. __NR_chown32&n; * is __NR_chown on 64 bit).&n; */
macro_line|#ifdef __s390x__
DECL|macro|__NR_time
macro_line|#undef  __NR_time
DECL|macro|__NR_lchown
macro_line|#undef  __NR_lchown
DECL|macro|__NR_setuid
macro_line|#undef  __NR_setuid
DECL|macro|__NR_getuid
macro_line|#undef  __NR_getuid
DECL|macro|__NR_stime
macro_line|#undef  __NR_stime
DECL|macro|__NR_setgid
macro_line|#undef  __NR_setgid
DECL|macro|__NR_getgid
macro_line|#undef  __NR_getgid
DECL|macro|__NR_geteuid
macro_line|#undef  __NR_geteuid
DECL|macro|__NR_getegid
macro_line|#undef  __NR_getegid
DECL|macro|__NR_setreuid
macro_line|#undef  __NR_setreuid
DECL|macro|__NR_setregid
macro_line|#undef  __NR_setregid
DECL|macro|__NR_getrlimit
macro_line|#undef  __NR_getrlimit
DECL|macro|__NR_getgroups
macro_line|#undef  __NR_getgroups
DECL|macro|__NR_setgroups
macro_line|#undef  __NR_setgroups
DECL|macro|__NR_fchown
macro_line|#undef  __NR_fchown
DECL|macro|__NR_ioperm
macro_line|#undef  __NR_ioperm
DECL|macro|__NR_setfsuid
macro_line|#undef  __NR_setfsuid
DECL|macro|__NR_setfsgid
macro_line|#undef  __NR_setfsgid
DECL|macro|__NR__llseek
macro_line|#undef  __NR__llseek
DECL|macro|__NR__newselect
macro_line|#undef  __NR__newselect
DECL|macro|__NR_setresuid
macro_line|#undef  __NR_setresuid
DECL|macro|__NR_getresuid
macro_line|#undef  __NR_getresuid
DECL|macro|__NR_setresgid
macro_line|#undef  __NR_setresgid
DECL|macro|__NR_getresgid
macro_line|#undef  __NR_getresgid
DECL|macro|__NR_chown
macro_line|#undef  __NR_chown
DECL|macro|__NR_ugetrlimit
macro_line|#undef  __NR_ugetrlimit
DECL|macro|__NR_mmap2
macro_line|#undef  __NR_mmap2
DECL|macro|__NR_truncate64
macro_line|#undef  __NR_truncate64
DECL|macro|__NR_ftruncate64
macro_line|#undef  __NR_ftruncate64
DECL|macro|__NR_stat64
macro_line|#undef  __NR_stat64
DECL|macro|__NR_lstat64
macro_line|#undef  __NR_lstat64
DECL|macro|__NR_fstat64
macro_line|#undef  __NR_fstat64
DECL|macro|__NR_lchown32
macro_line|#undef  __NR_lchown32
DECL|macro|__NR_getuid32
macro_line|#undef  __NR_getuid32
DECL|macro|__NR_getgid32
macro_line|#undef  __NR_getgid32
DECL|macro|__NR_geteuid32
macro_line|#undef  __NR_geteuid32
DECL|macro|__NR_getegid32
macro_line|#undef  __NR_getegid32
DECL|macro|__NR_setreuid32
macro_line|#undef  __NR_setreuid32
DECL|macro|__NR_setregid32
macro_line|#undef  __NR_setregid32
DECL|macro|__NR_getgroups32
macro_line|#undef  __NR_getgroups32
DECL|macro|__NR_setgroups32
macro_line|#undef  __NR_setgroups32
DECL|macro|__NR_fchown32
macro_line|#undef  __NR_fchown32
DECL|macro|__NR_setresuid32
macro_line|#undef  __NR_setresuid32
DECL|macro|__NR_getresuid32
macro_line|#undef  __NR_getresuid32
DECL|macro|__NR_setresgid32
macro_line|#undef  __NR_setresgid32
DECL|macro|__NR_getresgid32
macro_line|#undef  __NR_getresgid32
DECL|macro|__NR_chown32
macro_line|#undef  __NR_chown32
DECL|macro|__NR_setuid32
macro_line|#undef  __NR_setuid32
DECL|macro|__NR_setgid32
macro_line|#undef  __NR_setgid32
DECL|macro|__NR_setfsuid32
macro_line|#undef  __NR_setfsuid32
DECL|macro|__NR_setfsgid32
macro_line|#undef  __NR_setfsgid32
DECL|macro|__NR_getdents64
macro_line|#undef  __NR_getdents64
DECL|macro|__NR_fcntl64
macro_line|#undef  __NR_fcntl64
DECL|macro|__NR_sendfile64
macro_line|#undef  __NR_sendfile64
DECL|macro|__NR_fadvise64_64
macro_line|#undef  __NR_fadvise64_64
DECL|macro|__NR_select
mdefine_line|#define __NR_select&t;&t;142
DECL|macro|__NR_getrlimit
mdefine_line|#define __NR_getrlimit&t;&t;191&t;/* SuS compliant getrlimit */
DECL|macro|__NR_lchown
mdefine_line|#define __NR_lchown  &t;&t;198
DECL|macro|__NR_getuid
mdefine_line|#define __NR_getuid  &t;&t;199
DECL|macro|__NR_getgid
mdefine_line|#define __NR_getgid  &t;&t;200
DECL|macro|__NR_geteuid
mdefine_line|#define __NR_geteuid  &t;&t;201
DECL|macro|__NR_getegid
mdefine_line|#define __NR_getegid  &t;&t;202
DECL|macro|__NR_setreuid
mdefine_line|#define __NR_setreuid  &t;&t;203
DECL|macro|__NR_setregid
mdefine_line|#define __NR_setregid  &t;&t;204
DECL|macro|__NR_getgroups
mdefine_line|#define __NR_getgroups  &t;205
DECL|macro|__NR_setgroups
mdefine_line|#define __NR_setgroups  &t;206
DECL|macro|__NR_fchown
mdefine_line|#define __NR_fchown  &t;&t;207
DECL|macro|__NR_setresuid
mdefine_line|#define __NR_setresuid  &t;208
DECL|macro|__NR_getresuid
mdefine_line|#define __NR_getresuid  &t;209
DECL|macro|__NR_setresgid
mdefine_line|#define __NR_setresgid  &t;210
DECL|macro|__NR_getresgid
mdefine_line|#define __NR_getresgid  &t;211
DECL|macro|__NR_chown
mdefine_line|#define __NR_chown  &t;&t;212
DECL|macro|__NR_setuid
mdefine_line|#define __NR_setuid  &t;&t;213
DECL|macro|__NR_setgid
mdefine_line|#define __NR_setgid  &t;&t;214
DECL|macro|__NR_setfsuid
mdefine_line|#define __NR_setfsuid  &t;&t;215
DECL|macro|__NR_setfsgid
mdefine_line|#define __NR_setfsgid  &t;&t;216
macro_line|#endif
multiline_comment|/* user-visible error numbers are in the range -1 - -122: see &lt;asm-s390/errno.h&gt; */
DECL|macro|__syscall_return
mdefine_line|#define __syscall_return(type, res)&t;&t;&t;     &bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;     &bslash;&n;&t;if ((unsigned long)(res) &gt;= (unsigned long)(-125)) { &bslash;&n;&t;&t;errno = -(res);&t;&t;&t;&t;     &bslash;&n;&t;&t;res = -1;&t;&t;&t;&t;     &bslash;&n;&t;}&t;&t;&t;&t;&t;&t;     &bslash;&n;&t;return (type) (res);&t;&t;&t;&t;     &bslash;&n;} while (0)
DECL|macro|_svc_clobber
mdefine_line|#define _svc_clobber &quot;1&quot;, &quot;cc&quot;, &quot;memory&quot;
DECL|macro|_syscall0
mdefine_line|#define _syscall0(type,name)&t;&t;&t;&t;     &bslash;&n;type name(void) {&t;&t;&t;&t;&t;     &bslash;&n;&t;register long __svcres asm(&quot;2&quot;);&t;&t;     &bslash;&n;&t;long __res;&t;&t;&t;&t;&t;     &bslash;&n;&t;__asm__ __volatile__ (&t;&t;&t;&t;     &bslash;&n;&t;&t;&quot;    .if %1 &lt; 256&bslash;n&quot;&t;&t;&t;     &bslash;&n;&t;&t;&quot;    svc %b1&bslash;n&quot;&t;&t;&t;&t;     &bslash;&n;&t;&t;&quot;    .else&bslash;n&quot;&t;&t;&t;&t;     &bslash;&n;&t;&t;&quot;    la  %%r1,%1&bslash;n&quot;&t;&t;&t;     &bslash;&n;&t;&t;&quot;    svc 0&bslash;n&quot;&t;&t;&t;&t;     &bslash;&n;&t;&t;&quot;    .endif&quot;&t;&t;&t;&t;     &bslash;&n;&t;&t;: &quot;=d&quot; (__svcres)&t;&t;&t;     &bslash;&n;&t;&t;: &quot;i&quot; (__NR_##name)&t;&t;&t;     &bslash;&n;&t;&t;: _svc_clobber );&t;&t;&t;     &bslash;&n;&t;__res = __svcres;&t;&t;&t;&t;     &bslash;&n;&t;__syscall_return(type,__res);&t;&t;&t;     &bslash;&n;}
DECL|macro|_syscall1
mdefine_line|#define _syscall1(type,name,type1,arg1)&t;&t;&t;     &bslash;&n;type name(type1 arg1) {&t;&t;&t;&t;&t;     &bslash;&n;&t;register type1 __arg1 asm(&quot;2&quot;) = arg1;&t;&t;     &bslash;&n;&t;register long __svcres asm(&quot;2&quot;);&t;&t;     &bslash;&n;&t;long __res;&t;&t;&t;&t;&t;     &bslash;&n;&t;__asm__ __volatile__ (&t;&t;&t;&t;     &bslash;&n;&t;&t;&quot;    .if %1 &lt; 256&bslash;n&quot;&t;&t;&t;     &bslash;&n;&t;&t;&quot;    svc %b1&bslash;n&quot;&t;&t;&t;&t;     &bslash;&n;&t;&t;&quot;    .else&bslash;n&quot;&t;&t;&t;&t;     &bslash;&n;&t;&t;&quot;    la  %%r1,%1&bslash;n&quot;&t;&t;&t;     &bslash;&n;&t;&t;&quot;    svc 0&bslash;n&quot;&t;&t;&t;&t;     &bslash;&n;&t;&t;&quot;    .endif&quot;&t;&t;&t;&t;     &bslash;&n;&t;&t;: &quot;=d&quot; (__svcres)&t;&t;&t;     &bslash;&n;&t;&t;: &quot;i&quot; (__NR_##name),&t;&t;&t;     &bslash;&n;&t;&t;  &quot;0&quot; (__arg1)&t;&t;&t;&t;     &bslash;&n;&t;&t;: _svc_clobber );&t;&t;&t;     &bslash;&n;&t;__res = __svcres;&t;&t;&t;&t;     &bslash;&n;&t;__syscall_return(type,__res);&t;&t;&t;     &bslash;&n;}
DECL|macro|_syscall2
mdefine_line|#define _syscall2(type,name,type1,arg1,type2,arg2)&t;     &bslash;&n;type name(type1 arg1, type2 arg2) {&t;&t;&t;     &bslash;&n;&t;register type1 __arg1 asm(&quot;2&quot;) = arg1;&t;&t;     &bslash;&n;&t;register type2 __arg2 asm(&quot;3&quot;) = arg2;&t;&t;     &bslash;&n;&t;register long __svcres asm(&quot;2&quot;);&t;&t;     &bslash;&n;&t;long __res;&t;&t;&t;&t;&t;     &bslash;&n;&t;__asm__ __volatile__ (&t;&t;&t;&t;     &bslash;&n;&t;&t;&quot;    .if %1 &lt; 256&bslash;n&quot;&t;&t;&t;     &bslash;&n;&t;&t;&quot;    svc %b1&bslash;n&quot;&t;&t;&t;&t;     &bslash;&n;&t;&t;&quot;    .else&bslash;n&quot;&t;&t;&t;&t;     &bslash;&n;&t;&t;&quot;    la %%r1,%1&bslash;n&quot;&t;&t;&t;     &bslash;&n;&t;&t;&quot;    svc 0&bslash;n&quot;&t;&t;&t;&t;     &bslash;&n;&t;&t;&quot;    .endif&quot;&t;&t;&t;&t;     &bslash;&n;&t;&t;: &quot;=d&quot; (__svcres)&t;&t;&t;     &bslash;&n;&t;&t;: &quot;i&quot; (__NR_##name),&t;&t;&t;     &bslash;&n;&t;&t;  &quot;0&quot; (__arg1),&t;&t;&t;&t;     &bslash;&n;&t;&t;  &quot;d&quot; (__arg2)&t;&t;&t;&t;     &bslash;&n;&t;&t;: _svc_clobber );&t;&t;&t;     &bslash;&n;&t;__res = __svcres;&t;&t;&t;&t;     &bslash;&n;&t;__syscall_return(type,__res);&t;&t;&t;     &bslash;&n;}
DECL|macro|_syscall3
mdefine_line|#define _syscall3(type,name,type1,arg1,type2,arg2,type3,arg3)&bslash;&n;type name(type1 arg1, type2 arg2, type3 arg3) {&t;&t;     &bslash;&n;&t;register type1 __arg1 asm(&quot;2&quot;) = arg1;&t;&t;     &bslash;&n;&t;register type2 __arg2 asm(&quot;3&quot;) = arg2;&t;&t;     &bslash;&n;&t;register type3 __arg3 asm(&quot;4&quot;) = arg3;&t;&t;     &bslash;&n;&t;register long __svcres asm(&quot;2&quot;);&t;&t;     &bslash;&n;&t;long __res;&t;&t;&t;&t;&t;     &bslash;&n;&t;__asm__ __volatile__ (&t;&t;&t;&t;     &bslash;&n;&t;&t;&quot;    .if %1 &lt; 256&bslash;n&quot;&t;&t;&t;     &bslash;&n;&t;&t;&quot;    svc %b1&bslash;n&quot;&t;&t;&t;&t;     &bslash;&n;&t;&t;&quot;    .else&bslash;n&quot;&t;&t;&t;&t;     &bslash;&n;&t;&t;&quot;    la  %%r1,%1&bslash;n&quot;&t;&t;&t;     &bslash;&n;&t;&t;&quot;    svc 0&bslash;n&quot;&t;&t;&t;&t;     &bslash;&n;&t;&t;&quot;    .endif&quot;&t;&t;&t;&t;     &bslash;&n;&t;&t;: &quot;=d&quot; (__svcres)&t;&t;&t;     &bslash;&n;&t;&t;: &quot;i&quot; (__NR_##name),&t;&t;&t;     &bslash;&n;&t;&t;  &quot;0&quot; (__arg1),&t;&t;&t;&t;     &bslash;&n;&t;&t;  &quot;d&quot; (__arg2),&t;&t;&t;&t;     &bslash;&n;&t;&t;  &quot;d&quot; (__arg3)&t;&t;&t;&t;     &bslash;&n;&t;&t;: _svc_clobber );&t;&t;&t;     &bslash;&n;&t;__res = __svcres;&t;&t;&t;&t;     &bslash;&n;&t;__syscall_return(type,__res);&t;&t;&t;     &bslash;&n;}
DECL|macro|_syscall4
mdefine_line|#define _syscall4(type,name,type1,arg1,type2,arg2,type3,arg3,&bslash;&n;&t;&t;  type4,name4)&t;&t;&t;&t;     &bslash;&n;type name(type1 arg1, type2 arg2, type3 arg3, type4 arg4) {  &bslash;&n;&t;register type1 __arg1 asm(&quot;2&quot;) = arg1;&t;&t;     &bslash;&n;&t;register type2 __arg2 asm(&quot;3&quot;) = arg2;&t;&t;     &bslash;&n;&t;register type3 __arg3 asm(&quot;4&quot;) = arg3;&t;&t;     &bslash;&n;&t;register type4 __arg4 asm(&quot;5&quot;) = arg4;&t;&t;     &bslash;&n;&t;register long __svcres asm(&quot;2&quot;);&t;&t;     &bslash;&n;&t;long __res;&t;&t;&t;&t;&t;     &bslash;&n;&t;__asm__ __volatile__ (&t;&t;&t;&t;     &bslash;&n;&t;&t;&quot;    .if %1 &lt; 256&bslash;n&quot;&t;&t;&t;     &bslash;&n;&t;&t;&quot;    svc %b1&bslash;n&quot;&t;&t;&t;&t;     &bslash;&n;&t;&t;&quot;    .else&bslash;n&quot;&t;&t;&t;&t;     &bslash;&n;&t;&t;&quot;    la  %%r1,%1&bslash;n&quot;&t;&t;&t;     &bslash;&n;&t;&t;&quot;    svc 0&bslash;n&quot;&t;&t;&t;&t;     &bslash;&n;&t;&t;&quot;    .endif&quot;&t;&t;&t;&t;     &bslash;&n;&t;&t;: &quot;=d&quot; (__svcres)&t;&t;&t;     &bslash;&n;&t;&t;: &quot;i&quot; (__NR_##name),&t;&t;&t;     &bslash;&n;&t;&t;  &quot;0&quot; (__arg1),&t;&t;&t;&t;     &bslash;&n;&t;&t;  &quot;d&quot; (__arg2),&t;&t;&t;&t;     &bslash;&n;&t;&t;  &quot;d&quot; (__arg3),&t;&t;&t;&t;     &bslash;&n;&t;&t;  &quot;d&quot; (__arg4)&t;&t;&t;&t;     &bslash;&n;&t;&t;: _svc_clobber );&t;&t;&t;     &bslash;&n;&t;__res = __svcres;&t;&t;&t;&t;     &bslash;&n;&t;__syscall_return(type,__res);&t;&t;&t;     &bslash;&n;}
DECL|macro|_syscall5
mdefine_line|#define _syscall5(type,name,type1,arg1,type2,arg2,type3,arg3,&bslash;&n;&t;&t;  type4,name4,type5,name5)&t;&t;     &bslash;&n;type name(type1 arg1, type2 arg2, type3 arg3, type4 arg4,    &bslash;&n;&t;  type5 arg5) {&t;&t;&t;&t;&t;     &bslash;&n;&t;register type1 __arg1 asm(&quot;2&quot;) = arg1;&t;&t;     &bslash;&n;&t;register type2 __arg2 asm(&quot;3&quot;) = arg2;&t;&t;     &bslash;&n;&t;register type3 __arg3 asm(&quot;4&quot;) = arg3;&t;&t;     &bslash;&n;&t;register type4 __arg4 asm(&quot;5&quot;) = arg4;&t;&t;     &bslash;&n;&t;register type5 __arg5 asm(&quot;6&quot;) = arg5;&t;&t;     &bslash;&n;&t;register long __svcres asm(&quot;2&quot;);&t;&t;     &bslash;&n;&t;long __res;&t;&t;&t;&t;&t;     &bslash;&n;&t;__asm__ __volatile__ (&t;&t;&t;&t;     &bslash;&n;&t;&t;&quot;    .if %1 &lt; 256&bslash;n&quot;&t;&t;&t;     &bslash;&n;&t;&t;&quot;    svc %b1&bslash;n&quot;&t;&t;&t;&t;     &bslash;&n;&t;&t;&quot;    .else&bslash;n&quot;&t;&t;&t;&t;     &bslash;&n;&t;&t;&quot;    la  %%r1,%1&bslash;n&quot;&t;&t;&t;     &bslash;&n;&t;&t;&quot;    svc 0&bslash;n&quot;&t;&t;&t;&t;     &bslash;&n;&t;&t;&quot;    .endif&quot;&t;&t;&t;&t;     &bslash;&n;&t;&t;: &quot;=d&quot; (__svcres)&t;&t;&t;     &bslash;&n;&t;&t;: &quot;i&quot; (__NR_##name),&t;&t;&t;     &bslash;&n;&t;&t;  &quot;0&quot; (__arg1),&t;&t;&t;&t;     &bslash;&n;&t;&t;  &quot;d&quot; (__arg2),&t;&t;&t;&t;     &bslash;&n;&t;&t;  &quot;d&quot; (__arg3),&t;&t;&t;&t;     &bslash;&n;&t;&t;  &quot;d&quot; (__arg4),&t;&t;&t;&t;     &bslash;&n;&t;&t;  &quot;d&quot; (__arg5)&t;&t;&t;&t;     &bslash;&n;&t;&t;: _svc_clobber );&t;&t;&t;     &bslash;&n;&t;__res = __svcres;&t;&t;&t;&t;     &bslash;&n;&t;__syscall_return(type,__res);&t;&t;&t;     &bslash;&n;}
macro_line|#ifdef __KERNEL__
DECL|macro|__ARCH_WANT_IPC_PARSE_VERSION
mdefine_line|#define __ARCH_WANT_IPC_PARSE_VERSION
DECL|macro|__ARCH_WANT_OLD_READDIR
mdefine_line|#define __ARCH_WANT_OLD_READDIR
DECL|macro|__ARCH_WANT_SYS_ALARM
mdefine_line|#define __ARCH_WANT_SYS_ALARM
DECL|macro|__ARCH_WANT_SYS_GETHOSTNAME
mdefine_line|#define __ARCH_WANT_SYS_GETHOSTNAME
DECL|macro|__ARCH_WANT_SYS_PAUSE
mdefine_line|#define __ARCH_WANT_SYS_PAUSE
DECL|macro|__ARCH_WANT_SYS_SIGNAL
mdefine_line|#define __ARCH_WANT_SYS_SIGNAL
DECL|macro|__ARCH_WANT_SYS_UTIME
mdefine_line|#define __ARCH_WANT_SYS_UTIME
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
macro_line|# ifdef CONFIG_ARCH_S390_31
DECL|macro|__ARCH_WANT_STAT64
macro_line|#   define __ARCH_WANT_STAT64
DECL|macro|__ARCH_WANT_SYS_TIME
macro_line|#   define __ARCH_WANT_SYS_TIME
macro_line|# endif
DECL|macro|__ARCH_WANT_COMPAT_SYS_TIME
macro_line|# define __ARCH_WANT_COMPAT_SYS_TIME
macro_line|#endif
macro_line|#ifdef __KERNEL_SYSCALLS__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/compiler.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/stat.h&gt;
macro_line|#include &lt;linux/syscalls.h&gt;
multiline_comment|/*&n; * we need this inline - forking from kernel space will result&n; * in NO COPY ON WRITE (!!!), until an execve is executed. This&n; * is no problem, but for the stack. This is handled by not letting&n; * main() use the stack at all after fork(). Thus, no function&n; * calls - which means inline code for fork too, as otherwise we&n; * would use the stack upon exit from &squot;fork()&squot;.&n; *&n; * Actually only pause and fork are needed inline, so that there&n; * won&squot;t be any messing with the stack from main(), but we define&n; * some others too.&n; */
DECL|macro|__NR__exit
mdefine_line|#define __NR__exit __NR_exit
r_static
r_inline
id|_syscall0
c_func
(paren
id|pid_t
comma
id|setsid
)paren
r_static
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
r_static
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
r_static
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
r_static
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
r_static
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
r_static
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
r_static
r_inline
id|_syscall2
c_func
(paren
r_int
comma
id|stat
comma
r_char
op_star
comma
id|filename
comma
r_struct
id|stat
op_star
comma
id|statbuf
)paren
DECL|function|waitpid
r_static
r_inline
id|pid_t
id|waitpid
c_func
(paren
r_int
id|pid
comma
r_int
op_star
id|wait_stat
comma
r_int
id|flags
)paren
(brace
r_return
id|sys_wait4
c_func
(paren
id|pid
comma
id|wait_stat
comma
id|flags
comma
l_int|NULL
)paren
suffix:semicolon
)brace
r_struct
id|mmap_arg_struct
suffix:semicolon
id|asmlinkage
r_int
id|sys_mmap2
c_func
(paren
r_struct
id|mmap_arg_struct
id|__user
op_star
id|arg
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
DECL|macro|cond_syscall
mdefine_line|#define cond_syscall(x) asm(&quot;.weak&bslash;t&quot; #x &quot;&bslash;n&bslash;t.set&bslash;t&quot; #x &quot;,sys_ni_syscall&quot;);
macro_line|#endif /* _ASM_S390_UNISTD_H_ */
eof
