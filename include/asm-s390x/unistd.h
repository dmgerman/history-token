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
DECL|macro|__NR_mknod
mdefine_line|#define __NR_mknod               14
DECL|macro|__NR_chmod
mdefine_line|#define __NR_chmod               15
DECL|macro|__NR_lseek
mdefine_line|#define __NR_lseek               19
DECL|macro|__NR_getpid
mdefine_line|#define __NR_getpid              20
DECL|macro|__NR_mount
mdefine_line|#define __NR_mount               21
DECL|macro|__NR_umount
mdefine_line|#define __NR_umount              22
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
DECL|macro|__NR_signal
mdefine_line|#define __NR_signal              48
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
DECL|macro|__NR_sigsuspend
mdefine_line|#define __NR_sigsuspend          72
DECL|macro|__NR_sigpending
mdefine_line|#define __NR_sigpending          73
DECL|macro|__NR_sethostname
mdefine_line|#define __NR_sethostname         74
DECL|macro|__NR_setrlimit
mdefine_line|#define __NR_setrlimit           75
DECL|macro|__NR_getrusage
mdefine_line|#define __NR_getrusage           77
DECL|macro|__NR_gettimeofday
mdefine_line|#define __NR_gettimeofday        78
DECL|macro|__NR_settimeofday
mdefine_line|#define __NR_settimeofday        79
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
DECL|macro|__NR_getpriority
mdefine_line|#define __NR_getpriority         96
DECL|macro|__NR_setpriority
mdefine_line|#define __NR_setpriority         97
DECL|macro|__NR_statfs
mdefine_line|#define __NR_statfs              99
DECL|macro|__NR_fstatfs
mdefine_line|#define __NR_fstatfs            100
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
DECL|macro|__NR_getdents
mdefine_line|#define __NR_getdents           141
DECL|macro|__NR_select
mdefine_line|#define __NR_select             142
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
DECL|macro|__NR_query_module
mdefine_line|#define __NR_query_module       167
DECL|macro|__NR_poll
mdefine_line|#define __NR_poll               168
DECL|macro|__NR_nfsservctl
mdefine_line|#define __NR_nfsservctl         169
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
DECL|macro|__NR_pivot_root
mdefine_line|#define __NR_pivot_root         217
DECL|macro|__NR_mincore
mdefine_line|#define __NR_mincore            218
DECL|macro|__NR_madvise
mdefine_line|#define __NR_madvise            219
DECL|macro|__NR_readahead
mdefine_line|#define __NR_readahead&t;&t;222
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
multiline_comment|/*&n; * Number 241 is currently unused&n; */
multiline_comment|/*&n; * Number 242 is reserved for tux&n; */
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
multiline_comment|/* user-visible error numbers are in the range -1 - -122: see &lt;asm-s390/errno.h&gt; */
DECL|macro|__syscall_return
mdefine_line|#define __syscall_return(type, res)                          &bslash;&n;do {                                                         &bslash;&n;        if ((unsigned long)(res) &gt;= (unsigned long)(-125)) { &bslash;&n;                errno = -(res);                              &bslash;&n;                res = -1;                                    &bslash;&n;        }                                                    &bslash;&n;        return (type) (res);                                 &bslash;&n;} while (0)
DECL|macro|_svc_clobber
mdefine_line|#define _svc_clobber &quot;cc&quot;, &quot;memory&quot;
DECL|macro|_syscall0
mdefine_line|#define _syscall0(type,name)                                 &bslash;&n;type name(void) {                                            &bslash;&n;        register long __res asm(&quot;2&quot;);                        &bslash;&n;        __asm__ __volatile__ (                               &bslash;&n;                &quot;    svc %b1&bslash;n&quot;                              &bslash;&n;                &quot;    lgr  %0,2&quot;                              &bslash;&n;                : &quot;=d&quot; (__res)                               &bslash;&n;                : &quot;i&quot; (__NR_##name)                          &bslash;&n;                : _svc_clobber );                            &bslash;&n;        __syscall_return(type,__res);                        &bslash;&n;}
DECL|macro|_syscall1
mdefine_line|#define _syscall1(type,name,type1,arg1)                      &bslash;&n;type name(type1 arg1) {                                      &bslash;&n;        register type1 __arg1 asm(&quot;2&quot;) = arg1;               &bslash;&n;        register long __res asm(&quot;2&quot;);                        &bslash;&n;        __asm__ __volatile__ (                               &bslash;&n;                &quot;    svc %b1&bslash;n&quot;                              &bslash;&n;                &quot;    lgr  %0,2&quot;                              &bslash;&n;                : &quot;=d&quot; (__res)                               &bslash;&n;                : &quot;i&quot; (__NR_##name),                         &bslash;&n;                  &quot;0&quot; (__arg1)                               &bslash;&n;                : _svc_clobber );                            &bslash;&n;        __syscall_return(type,__res);                        &bslash;&n;}
DECL|macro|_syscall2
mdefine_line|#define _syscall2(type,name,type1,arg1,type2,arg2)           &bslash;&n;type name(type1 arg1, type2 arg2) {                          &bslash;&n;        register type1 __arg1 asm(&quot;2&quot;) = arg1;               &bslash;&n;        register type2 __arg2 asm(&quot;3&quot;) = arg2;               &bslash;&n;        register long __res asm(&quot;2&quot;);                        &bslash;&n;        __asm__ __volatile__ (                               &bslash;&n;                &quot;    svc %b1&bslash;n&quot;                              &bslash;&n;                &quot;    lgr  %0,2&quot;                              &bslash;&n;                : &quot;=d&quot; (__res)                               &bslash;&n;                : &quot;i&quot; (__NR_##name),                         &bslash;&n;                  &quot;0&quot; (__arg1),                              &bslash;&n;                  &quot;d&quot; (__arg2)                               &bslash;&n;                : _svc_clobber );                            &bslash;&n;        __syscall_return(type,__res);                        &bslash;&n;}
DECL|macro|_syscall3
mdefine_line|#define _syscall3(type,name,type1,arg1,type2,arg2,type3,arg3)&bslash;&n;type name(type1 arg1, type2 arg2, type3 arg3) {              &bslash;&n;        register type1 __arg1 asm(&quot;2&quot;) = arg1;               &bslash;&n;        register type2 __arg2 asm(&quot;3&quot;) = arg2;               &bslash;&n;        register type3 __arg3 asm(&quot;4&quot;) = arg3;               &bslash;&n;        register long __res asm(&quot;2&quot;);                        &bslash;&n;        __asm__ __volatile__ (                               &bslash;&n;                &quot;    svc %b1&bslash;n&quot;                              &bslash;&n;                &quot;    lgr  %0,2&quot;                              &bslash;&n;                : &quot;=d&quot; (__res)                               &bslash;&n;                : &quot;i&quot; (__NR_##name),                         &bslash;&n;                  &quot;0&quot; (__arg1),                              &bslash;&n;                  &quot;d&quot; (__arg2),                              &bslash;&n;                  &quot;d&quot; (__arg3)                               &bslash;&n;                : _svc_clobber );                            &bslash;&n;        __syscall_return(type,__res);                        &bslash;&n;}
DECL|macro|_syscall4
mdefine_line|#define _syscall4(type,name,type1,arg1,type2,arg2,type3,arg3,&bslash;&n;                  type4,name4)                               &bslash;&n;type name(type1 arg1, type2 arg2, type3 arg3, type4 arg4) {  &bslash;&n;        register type1 __arg1 asm(&quot;2&quot;) = arg1;               &bslash;&n;        register type2 __arg2 asm(&quot;3&quot;) = arg2;               &bslash;&n;        register type3 __arg3 asm(&quot;4&quot;) = arg3;               &bslash;&n;        register type4 __arg4 asm(&quot;5&quot;) = arg4;               &bslash;&n;        register long __res asm(&quot;2&quot;);                        &bslash;&n;        __asm__ __volatile__ (                               &bslash;&n;                &quot;    svc %b1&bslash;n&quot;                              &bslash;&n;                &quot;    lgr  %0,2&quot;                              &bslash;&n;                : &quot;=d&quot; (__res)                               &bslash;&n;                : &quot;i&quot; (__NR_##name),                         &bslash;&n;                  &quot;0&quot; (__arg1),                              &bslash;&n;                  &quot;d&quot; (__arg2),                              &bslash;&n;                  &quot;d&quot; (__arg3),                              &bslash;&n;                  &quot;d&quot; (__arg4)                               &bslash;&n;                : _svc_clobber );                            &bslash;&n;        __syscall_return(type,__res);                        &bslash;&n;}
DECL|macro|_syscall5
mdefine_line|#define _syscall5(type,name,type1,arg1,type2,arg2,type3,arg3,&bslash;&n;                  type4,name4,type5,name5)                   &bslash;&n;type name(type1 arg1, type2 arg2, type3 arg3, type4 arg4,    &bslash;&n;          type5 arg5) {                                      &bslash;&n;        register type1 __arg1 asm(&quot;2&quot;) = arg1;               &bslash;&n;        register type2 __arg2 asm(&quot;3&quot;) = arg2;               &bslash;&n;        register type3 __arg3 asm(&quot;4&quot;) = arg3;               &bslash;&n;        register type4 __arg4 asm(&quot;5&quot;) = arg4;               &bslash;&n;        register type5 __arg5 asm(&quot;6&quot;) = arg5;               &bslash;&n;        register long __res asm(&quot;2&quot;);                        &bslash;&n;        __asm__ __volatile__ (                               &bslash;&n;                &quot;    svc %b1&bslash;n&quot;                              &bslash;&n;                &quot;    lgr  %0,2&quot;                              &bslash;&n;                : &quot;=d&quot; (__res)                               &bslash;&n;                : &quot;i&quot; (__NR_##name),                         &bslash;&n;                  &quot;0&quot; (__arg1),                              &bslash;&n;                  &quot;d&quot; (__arg2),                              &bslash;&n;                  &quot;d&quot; (__arg3),                              &bslash;&n;                  &quot;d&quot; (__arg4),                              &bslash;&n;                  &quot;d&quot; (__arg5)                               &bslash;&n;                : _svc_clobber );                            &bslash;&n;        __syscall_return(type,__res);                        &bslash;&n;}
macro_line|#ifdef __KERNEL_SYSCALLS__
macro_line|#include &lt;asm/stat.h&gt;
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
r_struct
id|rusage
suffix:semicolon
r_extern
r_int
id|sys_wait4
c_func
(paren
id|pid_t
comma
r_int
r_int
op_star
comma
r_int
comma
r_struct
id|rusage
op_star
)paren
suffix:semicolon
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
macro_line|#endif
multiline_comment|/*&n; * &quot;Conditional&quot; syscalls&n; *&n; * What we want is __attribute__((weak,alias(&quot;sys_ni_syscall&quot;))),&n; * but it doesn&squot;t work on all toolchains, so we just do it by hand&n; */
DECL|macro|cond_syscall
mdefine_line|#define cond_syscall(x) asm(&quot;.weak&bslash;t&quot; #x &quot;&bslash;n&bslash;t.set&bslash;t&quot; #x &quot;,sys_ni_syscall&quot;);
macro_line|#endif /* _ASM_S390_UNISTD_H_ */
eof
