multiline_comment|/*&n; *  linux/arch/arm26/lib/calls.h&n; *&n; *  Copyright (C) 2003 Ian Molton&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; *  FIXME&n; *  This file is included twice in entry-common.S which may not be necessary&n; */
macro_line|#ifndef NR_syscalls
DECL|macro|NR_syscalls
mdefine_line|#define NR_syscalls 256
macro_line|#else
id|__syscall_start
suffix:colon
multiline_comment|/* 0 */
dot
r_int
id|sys_ni_syscall
dot
r_int
id|sys_exit
dot
r_int
id|sys_fork_wrapper
dot
r_int
id|sys_read
dot
r_int
id|sys_write
multiline_comment|/* 5 */
dot
r_int
id|sys_open
dot
r_int
id|sys_close
dot
r_int
id|sys_ni_syscall
multiline_comment|/* was sys_waitpid */
dot
r_int
id|sys_creat
dot
r_int
id|sys_link
multiline_comment|/* 10 */
dot
r_int
id|sys_unlink
dot
r_int
id|sys_execve_wrapper
dot
r_int
id|sys_chdir
dot
r_int
id|sys_time
multiline_comment|/* used by libc4 */
dot
r_int
id|sys_mknod
multiline_comment|/* 15 */
dot
r_int
id|sys_chmod
dot
r_int
id|sys_lchown16
dot
r_int
id|sys_ni_syscall
multiline_comment|/* was sys_break */
dot
r_int
id|sys_ni_syscall
multiline_comment|/* was sys_stat */
dot
r_int
id|sys_lseek
multiline_comment|/* 20 */
dot
r_int
id|sys_getpid
dot
r_int
id|sys_mount
dot
r_int
id|sys_oldumount
multiline_comment|/* used by libc4 */
dot
r_int
id|sys_setuid16
dot
r_int
id|sys_getuid16
multiline_comment|/* 25 */
dot
r_int
id|sys_stime
dot
r_int
id|sys_ptrace
dot
r_int
id|sys_alarm
multiline_comment|/* used by libc4 */
dot
r_int
id|sys_ni_syscall
multiline_comment|/* was sys_fstat */
dot
r_int
id|sys_pause
multiline_comment|/* 30 */
dot
r_int
id|sys_utime
multiline_comment|/* used by libc4 */
dot
r_int
id|sys_ni_syscall
multiline_comment|/* was sys_stty */
dot
r_int
id|sys_ni_syscall
multiline_comment|/* was sys_getty */
dot
r_int
id|sys_access
dot
r_int
id|sys_nice
multiline_comment|/* 35 */
dot
r_int
id|sys_ni_syscall
multiline_comment|/* was sys_ftime */
dot
r_int
id|sys_sync
dot
r_int
id|sys_kill
dot
r_int
id|sys_rename
dot
r_int
id|sys_mkdir
multiline_comment|/* 40 */
dot
r_int
id|sys_rmdir
dot
r_int
id|sys_dup
dot
r_int
id|sys_pipe
dot
r_int
id|sys_times
dot
r_int
id|sys_ni_syscall
multiline_comment|/* was sys_prof */
multiline_comment|/* 45 */
dot
r_int
id|sys_brk
dot
r_int
id|sys_setgid16
dot
r_int
id|sys_getgid16
dot
r_int
id|sys_ni_syscall
multiline_comment|/* was sys_signal */
dot
r_int
id|sys_geteuid16
multiline_comment|/* 50 */
dot
r_int
id|sys_getegid16
dot
r_int
id|sys_acct
dot
r_int
id|sys_umount
dot
r_int
id|sys_ni_syscall
multiline_comment|/* was sys_lock */
dot
r_int
id|sys_ioctl
multiline_comment|/* 55 */
dot
r_int
id|sys_fcntl
dot
r_int
id|sys_ni_syscall
multiline_comment|/* was sys_mpx */
dot
r_int
id|sys_setpgid
dot
r_int
id|sys_ni_syscall
multiline_comment|/* was sys_ulimit */
dot
r_int
id|sys_ni_syscall
multiline_comment|/* was sys_olduname */
multiline_comment|/* 60 */
dot
r_int
id|sys_umask
dot
r_int
id|sys_chroot
dot
r_int
id|sys_ustat
dot
r_int
id|sys_dup2
dot
r_int
id|sys_getppid
multiline_comment|/* 65 */
dot
r_int
id|sys_getpgrp
dot
r_int
id|sys_setsid
dot
r_int
id|sys_sigaction
dot
r_int
id|sys_ni_syscall
multiline_comment|/* was sys_sgetmask */
dot
r_int
id|sys_ni_syscall
multiline_comment|/* was sys_ssetmask */
multiline_comment|/* 70 */
dot
r_int
id|sys_setreuid16
dot
r_int
id|sys_setregid16
dot
r_int
id|sys_sigsuspend_wrapper
dot
r_int
id|sys_sigpending
dot
r_int
id|sys_sethostname
multiline_comment|/* 75 */
dot
r_int
id|sys_setrlimit
dot
r_int
id|sys_old_getrlimit
multiline_comment|/* used by libc4 */
dot
r_int
id|sys_getrusage
dot
r_int
id|sys_gettimeofday
dot
r_int
id|sys_settimeofday
multiline_comment|/* 80 */
dot
r_int
id|sys_getgroups16
dot
r_int
id|sys_setgroups16
dot
r_int
id|old_select
multiline_comment|/* used by libc4 */
dot
r_int
id|sys_symlink
dot
r_int
id|sys_ni_syscall
multiline_comment|/* was sys_lstat */
multiline_comment|/* 85 */
dot
r_int
id|sys_readlink
dot
r_int
id|sys_uselib
dot
r_int
id|sys_swapon
dot
r_int
id|sys_reboot
dot
r_int
id|old_readdir
multiline_comment|/* used by libc4 */
multiline_comment|/* 90 */
dot
r_int
id|old_mmap
multiline_comment|/* used by libc4 */
dot
r_int
id|sys_munmap
dot
r_int
id|sys_truncate
dot
r_int
id|sys_ftruncate
dot
r_int
id|sys_fchmod
multiline_comment|/* 95 */
dot
r_int
id|sys_fchown16
dot
r_int
id|sys_getpriority
dot
r_int
id|sys_setpriority
dot
r_int
id|sys_ni_syscall
multiline_comment|/* was sys_profil */
dot
r_int
id|sys_statfs
multiline_comment|/* 100 */
dot
r_int
id|sys_fstatfs
dot
r_int
id|sys_ni_syscall
dot
r_int
id|sys_socketcall
dot
r_int
id|sys_syslog
dot
r_int
id|sys_setitimer
multiline_comment|/* 105 */
dot
r_int
id|sys_getitimer
dot
r_int
id|sys_newstat
dot
r_int
id|sys_newlstat
dot
r_int
id|sys_newfstat
dot
r_int
id|sys_ni_syscall
multiline_comment|/* was sys_uname */
multiline_comment|/* 110 */
dot
r_int
id|sys_ni_syscall
multiline_comment|/* was sys_iopl */
dot
r_int
id|sys_vhangup
dot
r_int
id|sys_ni_syscall
dot
r_int
id|sys_syscall
multiline_comment|/* call a syscall */
dot
r_int
id|sys_wait4
multiline_comment|/* 115 */
dot
r_int
id|sys_swapoff
dot
r_int
id|sys_sysinfo
dot
r_int
id|sys_ipc
dot
r_int
id|sys_fsync
dot
r_int
id|sys_sigreturn_wrapper
multiline_comment|/* 120 */
dot
r_int
id|sys_clone_wapper
dot
r_int
id|sys_setdomainname
dot
r_int
id|sys_newuname
dot
r_int
id|sys_ni_syscall
dot
r_int
id|sys_adjtimex
multiline_comment|/* 125 */
dot
r_int
id|sys_mprotect
dot
r_int
id|sys_sigprocmask
dot
r_int
id|sys_ni_syscall
multiline_comment|/* WAS: sys_create_module */
dot
r_int
id|sys_init_module
dot
r_int
id|sys_delete_module
multiline_comment|/* 130 */
dot
r_int
id|sys_ni_syscall
multiline_comment|/* WAS: sys_get_kernel_syms */
dot
r_int
id|sys_quotactl
dot
r_int
id|sys_getpgid
dot
r_int
id|sys_fchdir
dot
r_int
id|sys_bdflush
multiline_comment|/* 135 */
dot
r_int
id|sys_sysfs
dot
r_int
id|sys_personality
dot
r_int
id|sys_ni_syscall
multiline_comment|/* .long&t;_sys_afs_syscall */
dot
r_int
id|sys_setfsuid16
dot
r_int
id|sys_setfsgid16
multiline_comment|/* 140 */
dot
r_int
id|sys_llseek
dot
r_int
id|sys_getdents
dot
r_int
id|sys_select
dot
r_int
id|sys_flock
dot
r_int
id|sys_msync
multiline_comment|/* 145 */
dot
r_int
id|sys_readv
dot
r_int
id|sys_writev
dot
r_int
id|sys_getsid
dot
r_int
id|sys_fdatasync
dot
r_int
id|sys_sysctl
multiline_comment|/* 150 */
dot
r_int
id|sys_mlock
dot
r_int
id|sys_munlock
dot
r_int
id|sys_mlockall
dot
r_int
id|sys_munlockall
dot
r_int
id|sys_sched_setparam
multiline_comment|/* 155 */
dot
r_int
id|sys_sched_getparam
dot
r_int
id|sys_sched_setscheduler
dot
r_int
id|sys_sched_getscheduler
dot
r_int
id|sys_sched_yield
dot
r_int
id|sys_sched_get_priority_max
multiline_comment|/* 160 */
dot
r_int
id|sys_sched_get_priority_min
dot
r_int
id|sys_sched_rr_get_interval
dot
r_int
id|sys_nanosleep
dot
r_int
id|sys_arm_mremap
dot
r_int
id|sys_setresuid16
multiline_comment|/* 165 */
dot
r_int
id|sys_getresuid16
dot
r_int
id|sys_ni_syscall
dot
r_int
id|sys_ni_syscall
multiline_comment|/* WAS: sys_query_module */
dot
r_int
id|sys_poll
dot
r_int
id|sys_nfsservctl
multiline_comment|/* 170 */
dot
r_int
id|sys_setresgid16
dot
r_int
id|sys_getresgid16
dot
r_int
id|sys_prctl
dot
r_int
id|sys_rt_sigreturn_wrapper
dot
r_int
id|sys_rt_sigaction
multiline_comment|/* 175 */
dot
r_int
id|sys_rt_sigprocmask
dot
r_int
id|sys_rt_sigpending
dot
r_int
id|sys_rt_sigtimedwait
dot
r_int
id|sys_rt_sigqueueinfo
dot
r_int
id|sys_rt_sigsuspend_wrapper
multiline_comment|/* 180 */
dot
r_int
id|sys_pread64
dot
r_int
id|sys_pwrite64
dot
r_int
id|sys_chown16
dot
r_int
id|sys_getcwd
dot
r_int
id|sys_capget
multiline_comment|/* 185 */
dot
r_int
id|sys_capset
dot
r_int
id|sys_sigaltstack_wrapper
dot
r_int
id|sys_sendfile
dot
r_int
id|sys_ni_syscall
dot
r_int
id|sys_ni_syscall
multiline_comment|/* 190 */
dot
r_int
id|sys_vfork_wrapper
dot
r_int
id|sys_getrlimit
dot
r_int
id|sys_mmap2
dot
r_int
id|sys_truncate64
dot
r_int
id|sys_ftruncate64
multiline_comment|/* 195 */
dot
r_int
id|sys_stat64
dot
r_int
id|sys_lstat64
dot
r_int
id|sys_fstat64
dot
r_int
id|sys_lchown
dot
r_int
id|sys_getuid
multiline_comment|/* 200 */
dot
r_int
id|sys_getgid
dot
r_int
id|sys_geteuid
dot
r_int
id|sys_getegid
dot
r_int
id|sys_setreuid
dot
r_int
id|sys_setregid
multiline_comment|/* 205 */
dot
r_int
id|sys_getgroups
dot
r_int
id|sys_setgroups
dot
r_int
id|sys_fchown
dot
r_int
id|sys_setresuid
dot
r_int
id|sys_getresuid
multiline_comment|/* 210 */
dot
r_int
id|sys_setresgid
dot
r_int
id|sys_getresgid
dot
r_int
id|sys_chown
dot
r_int
id|sys_setuid
dot
r_int
id|sys_setgid
multiline_comment|/* 215 */
dot
r_int
id|sys_setfsuid
dot
r_int
id|sys_setfsgid
dot
r_int
id|sys_getdents64
dot
r_int
id|sys_pivot_root
dot
r_int
id|sys_mincore
multiline_comment|/* 220 */
dot
r_int
id|sys_madvise
dot
r_int
id|sys_fcntl64
dot
r_int
id|sys_ni_syscall
multiline_comment|/* TUX */
dot
r_int
id|sys_ni_syscall
multiline_comment|/* WAS: sys_security */
dot
r_int
id|sys_gettid
multiline_comment|/* 225 */
dot
r_int
id|sys_readahead
dot
r_int
id|sys_setxattr
dot
r_int
id|sys_lsetxattr
dot
r_int
id|sys_fsetxattr
dot
r_int
id|sys_getxattr
multiline_comment|/* 230 */
dot
r_int
id|sys_lgetxattr
dot
r_int
id|sys_fgetxattr
dot
r_int
id|sys_listxattr
dot
r_int
id|sys_llistxattr
dot
r_int
id|sys_flistxattr
multiline_comment|/* 235 */
dot
r_int
id|sys_removexattr
dot
r_int
id|sys_lremovexattr
dot
r_int
id|sys_fremovexattr
dot
r_int
id|sys_tkill
id|__syscall_end
suffix:colon
dot
id|rept
id|NR_syscalls
op_minus
(paren
id|__syscall_end
op_minus
id|__syscall_start
)paren
op_div
l_int|4
dot
r_int
id|sys_ni_syscall
dot
id|endr
macro_line|#endif
eof
