multiline_comment|/* &n; * Copyright (C) 2000 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#include &quot;linux/config.h&quot;
macro_line|#include &quot;linux/unistd.h&quot;
macro_line|#include &quot;linux/version.h&quot;
macro_line|#include &quot;linux/sys.h&quot;
macro_line|#include &quot;linux/swap.h&quot;
macro_line|#include &quot;asm/signal.h&quot;
macro_line|#include &quot;sysdep/syscalls.h&quot;
macro_line|#include &quot;kern_util.h&quot;
r_extern
id|syscall_handler_t
id|sys_ni_syscall
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_exit
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_fork
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_creat
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_link
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_unlink
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_chdir
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_mknod
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_chmod
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_lchown16
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_ni_syscall
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_stat
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_getpid
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_oldumount
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_setuid16
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_getuid16
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_ptrace
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_alarm
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_fstat
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_pause
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_utime
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_ni_syscall
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_ni_syscall
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_access
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_nice
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_ni_syscall
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_sync
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_kill
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_rename
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_mkdir
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_rmdir
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_pipe
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_times
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_ni_syscall
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_brk
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_setgid16
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_getgid16
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_signal
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_geteuid16
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_getegid16
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_acct
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_umount
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_ni_syscall
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_ioctl
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_fcntl
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_ni_syscall
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_setpgid
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_ni_syscall
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_olduname
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_umask
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_chroot
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_ustat
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_dup2
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_getppid
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_getpgrp
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_sigaction
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_sgetmask
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_ssetmask
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_setreuid16
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_setregid16
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_sigsuspend
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_sigpending
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_sethostname
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_setrlimit
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_old_getrlimit
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_getrusage
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_gettimeofday
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_settimeofday
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_getgroups16
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_setgroups16
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_symlink
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_lstat
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_readlink
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_swapon
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_uselib
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_reboot
suffix:semicolon
r_extern
id|syscall_handler_t
id|old_readdir
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_munmap
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_truncate
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_ftruncate
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_fchmod
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_fchown16
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_getpriority
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_setpriority
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_ni_syscall
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_statfs
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_fstatfs
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_ni_syscall
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_socketcall
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_syslog
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_setitimer
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_getitimer
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_newstat
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_newlstat
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_newfstat
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_uname
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_ni_syscall
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_vhangup
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_ni_syscall
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_ni_syscall
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_swapoff
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_sysinfo
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_ipc
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_fsync
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_sigreturn
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_rt_sigreturn
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_clone
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_setdomainname
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_newuname
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_ni_syscall
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_adjtimex
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_mprotect
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_sigprocmask
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_create_module
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_init_module
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_delete_module
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_get_kernel_syms
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_quotactl
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_getpgid
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_fchdir
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_bdflush
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_sysfs
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_personality
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_ni_syscall
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_setfsuid16
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_setfsgid16
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_llseek
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_getdents
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_flock
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_msync
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_readv
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_writev
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_getsid
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_fdatasync
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_mlock
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_munlock
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_mlockall
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_munlockall
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_sched_setparam
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_sched_getparam
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_sched_setscheduler
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_sched_getscheduler
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_sched_get_priority_max
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_sched_get_priority_min
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_sched_rr_get_interval
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_nanosleep
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_mremap
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_setresuid16
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_getresuid16
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_ni_syscall
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_query_module
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_poll
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_nfsservctl
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_setresgid16
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_getresgid16
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_prctl
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_ni_syscall
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_rt_sigaction
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_rt_sigprocmask
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_rt_sigpending
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_rt_sigtimedwait
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_rt_sigqueueinfo
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_rt_sigsuspend
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_pread64
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_pwrite64
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_chown16
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_getcwd
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_capget
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_capset
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_sigaltstack
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_sendfile
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_ni_syscall
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_ni_syscall
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_vfork
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_getrlimit
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_mmap2
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_truncate64
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_ftruncate64
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_stat64
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_lstat64
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_fstat64
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_lchown
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_getuid
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_getgid
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_geteuid
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_getegid
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_setreuid
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_setregid
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_getgroups
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_setgroups
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_fchown
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_setresuid
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_getresuid
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_setresgid
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_getresgid
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_chown
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_setuid
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_setgid
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_setfsuid
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_setfsgid
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_pivot_root
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_mincore
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_madvise
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_fcntl64
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_getdents64
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_gettid
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_readahead
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_tkill
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_sendfile64
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_futex
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_sched_setaffinity
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_sched_getaffinity
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_io_setup
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_io_destroy
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_io_getevents
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_io_submit
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_io_cancel
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_exit_group
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_lookup_dcookie
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_epoll_create
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_epoll_ctl
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_epoll_wait
suffix:semicolon
r_extern
id|syscall_handler_t
id|sys_remap_file_pages
suffix:semicolon
macro_line|#if CONFIG_NFSD
DECL|macro|NFSSERVCTL
mdefine_line|#define NFSSERVCTL sys_nfsserctl
macro_line|#else
DECL|macro|NFSSERVCTL
mdefine_line|#define NFSSERVCTL sys_ni_syscall
macro_line|#endif
r_extern
id|syscall_handler_t
id|um_mount
suffix:semicolon
r_extern
id|syscall_handler_t
id|um_time
suffix:semicolon
r_extern
id|syscall_handler_t
id|um_stime
suffix:semicolon
DECL|macro|LAST_GENERIC_SYSCALL
mdefine_line|#define LAST_GENERIC_SYSCALL __NR_remap_file_pages
macro_line|#if LAST_GENERIC_SYSCALL &gt; LAST_ARCH_SYSCALL
DECL|macro|LAST_SYSCALL
mdefine_line|#define LAST_SYSCALL LAST_GENERIC_SYSCALL
macro_line|#else
DECL|macro|LAST_SYSCALL
mdefine_line|#define LAST_SYSCALL LAST_ARCH_SYSCALL
macro_line|#endif
DECL|variable|sys_call_table
id|syscall_handler_t
op_star
id|sys_call_table
(braket
)braket
op_assign
(brace
(braket
l_int|0
)braket
op_assign
id|sys_ni_syscall
comma
(braket
id|__NR_exit
)braket
op_assign
id|sys_exit
comma
(braket
id|__NR_fork
)braket
op_assign
id|sys_fork
comma
(braket
id|__NR_read
)braket
op_assign
(paren
id|syscall_handler_t
op_star
)paren
id|sys_read
comma
(braket
id|__NR_write
)braket
op_assign
(paren
id|syscall_handler_t
op_star
)paren
id|sys_write
comma
multiline_comment|/* These three are declared differently in asm/unistd.h */
(braket
id|__NR_open
)braket
op_assign
(paren
id|syscall_handler_t
op_star
)paren
id|sys_open
comma
(braket
id|__NR_close
)braket
op_assign
(paren
id|syscall_handler_t
op_star
)paren
id|sys_close
comma
(braket
id|__NR_waitpid
)braket
op_assign
(paren
id|syscall_handler_t
op_star
)paren
id|sys_waitpid
comma
(braket
id|__NR_creat
)braket
op_assign
id|sys_creat
comma
(braket
id|__NR_link
)braket
op_assign
id|sys_link
comma
(braket
id|__NR_unlink
)braket
op_assign
id|sys_unlink
comma
multiline_comment|/* declared differently in kern_util.h */
(braket
id|__NR_execve
)braket
op_assign
(paren
id|syscall_handler_t
op_star
)paren
id|sys_execve
comma
(braket
id|__NR_chdir
)braket
op_assign
id|sys_chdir
comma
(braket
id|__NR_time
)braket
op_assign
id|um_time
comma
(braket
id|__NR_mknod
)braket
op_assign
id|sys_mknod
comma
(braket
id|__NR_chmod
)braket
op_assign
id|sys_chmod
comma
(braket
id|__NR_lchown
)braket
op_assign
id|sys_lchown16
comma
(braket
id|__NR_break
)braket
op_assign
id|sys_ni_syscall
comma
(braket
id|__NR_oldstat
)braket
op_assign
id|sys_stat
comma
(braket
id|__NR_lseek
)braket
op_assign
(paren
id|syscall_handler_t
op_star
)paren
id|sys_lseek
comma
(braket
id|__NR_getpid
)braket
op_assign
id|sys_getpid
comma
(braket
id|__NR_mount
)braket
op_assign
id|um_mount
comma
(braket
id|__NR_umount
)braket
op_assign
id|sys_oldumount
comma
(braket
id|__NR_setuid
)braket
op_assign
id|sys_setuid16
comma
(braket
id|__NR_getuid
)braket
op_assign
id|sys_getuid16
comma
(braket
id|__NR_stime
)braket
op_assign
id|um_stime
comma
(braket
id|__NR_ptrace
)braket
op_assign
id|sys_ptrace
comma
(braket
id|__NR_alarm
)braket
op_assign
id|sys_alarm
comma
(braket
id|__NR_oldfstat
)braket
op_assign
id|sys_fstat
comma
(braket
id|__NR_pause
)braket
op_assign
id|sys_pause
comma
(braket
id|__NR_utime
)braket
op_assign
id|sys_utime
comma
(braket
id|__NR_stty
)braket
op_assign
id|sys_ni_syscall
comma
(braket
id|__NR_gtty
)braket
op_assign
id|sys_ni_syscall
comma
(braket
id|__NR_access
)braket
op_assign
id|sys_access
comma
(braket
id|__NR_nice
)braket
op_assign
id|sys_nice
comma
(braket
id|__NR_ftime
)braket
op_assign
id|sys_ni_syscall
comma
(braket
id|__NR_sync
)braket
op_assign
id|sys_sync
comma
(braket
id|__NR_kill
)braket
op_assign
id|sys_kill
comma
(braket
id|__NR_rename
)braket
op_assign
id|sys_rename
comma
(braket
id|__NR_mkdir
)braket
op_assign
id|sys_mkdir
comma
(braket
id|__NR_rmdir
)braket
op_assign
id|sys_rmdir
comma
multiline_comment|/* Declared differently in asm/unistd.h */
(braket
id|__NR_dup
)braket
op_assign
(paren
id|syscall_handler_t
op_star
)paren
id|sys_dup
comma
(braket
id|__NR_pipe
)braket
op_assign
id|sys_pipe
comma
(braket
id|__NR_times
)braket
op_assign
id|sys_times
comma
(braket
id|__NR_prof
)braket
op_assign
id|sys_ni_syscall
comma
(braket
id|__NR_brk
)braket
op_assign
id|sys_brk
comma
(braket
id|__NR_setgid
)braket
op_assign
id|sys_setgid16
comma
(braket
id|__NR_getgid
)braket
op_assign
id|sys_getgid16
comma
(braket
id|__NR_signal
)braket
op_assign
id|sys_signal
comma
(braket
id|__NR_geteuid
)braket
op_assign
id|sys_geteuid16
comma
(braket
id|__NR_getegid
)braket
op_assign
id|sys_getegid16
comma
(braket
id|__NR_acct
)braket
op_assign
id|sys_acct
comma
(braket
id|__NR_umount2
)braket
op_assign
id|sys_umount
comma
(braket
id|__NR_lock
)braket
op_assign
id|sys_ni_syscall
comma
(braket
id|__NR_ioctl
)braket
op_assign
id|sys_ioctl
comma
(braket
id|__NR_fcntl
)braket
op_assign
id|sys_fcntl
comma
(braket
id|__NR_mpx
)braket
op_assign
id|sys_ni_syscall
comma
(braket
id|__NR_setpgid
)braket
op_assign
id|sys_setpgid
comma
(braket
id|__NR_ulimit
)braket
op_assign
id|sys_ni_syscall
comma
(braket
id|__NR_oldolduname
)braket
op_assign
id|sys_olduname
comma
(braket
id|__NR_umask
)braket
op_assign
id|sys_umask
comma
(braket
id|__NR_chroot
)braket
op_assign
id|sys_chroot
comma
(braket
id|__NR_ustat
)braket
op_assign
id|sys_ustat
comma
(braket
id|__NR_dup2
)braket
op_assign
id|sys_dup2
comma
(braket
id|__NR_getppid
)braket
op_assign
id|sys_getppid
comma
(braket
id|__NR_getpgrp
)braket
op_assign
id|sys_getpgrp
comma
(braket
id|__NR_setsid
)braket
op_assign
(paren
id|syscall_handler_t
op_star
)paren
id|sys_setsid
comma
(braket
id|__NR_sigaction
)braket
op_assign
id|sys_sigaction
comma
(braket
id|__NR_sgetmask
)braket
op_assign
id|sys_sgetmask
comma
(braket
id|__NR_ssetmask
)braket
op_assign
id|sys_ssetmask
comma
(braket
id|__NR_setreuid
)braket
op_assign
id|sys_setreuid16
comma
(braket
id|__NR_setregid
)braket
op_assign
id|sys_setregid16
comma
(braket
id|__NR_sigsuspend
)braket
op_assign
id|sys_sigsuspend
comma
(braket
id|__NR_sigpending
)braket
op_assign
id|sys_sigpending
comma
(braket
id|__NR_sethostname
)braket
op_assign
id|sys_sethostname
comma
(braket
id|__NR_setrlimit
)braket
op_assign
id|sys_setrlimit
comma
(braket
id|__NR_getrlimit
)braket
op_assign
id|sys_old_getrlimit
comma
(braket
id|__NR_getrusage
)braket
op_assign
id|sys_getrusage
comma
(braket
id|__NR_gettimeofday
)braket
op_assign
id|sys_gettimeofday
comma
(braket
id|__NR_settimeofday
)braket
op_assign
id|sys_settimeofday
comma
(braket
id|__NR_getgroups
)braket
op_assign
id|sys_getgroups16
comma
(braket
id|__NR_setgroups
)braket
op_assign
id|sys_setgroups16
comma
(braket
id|__NR_symlink
)braket
op_assign
id|sys_symlink
comma
(braket
id|__NR_oldlstat
)braket
op_assign
id|sys_lstat
comma
(braket
id|__NR_readlink
)braket
op_assign
id|sys_readlink
comma
(braket
id|__NR_uselib
)braket
op_assign
id|sys_uselib
comma
(braket
id|__NR_swapon
)braket
op_assign
(paren
id|syscall_handler_t
op_star
)paren
id|sys_swapon
comma
(braket
id|__NR_reboot
)braket
op_assign
id|sys_reboot
comma
(braket
id|__NR_readdir
)braket
op_assign
id|old_readdir
comma
(braket
id|__NR_munmap
)braket
op_assign
id|sys_munmap
comma
(braket
id|__NR_truncate
)braket
op_assign
id|sys_truncate
comma
(braket
id|__NR_ftruncate
)braket
op_assign
id|sys_ftruncate
comma
(braket
id|__NR_fchmod
)braket
op_assign
id|sys_fchmod
comma
(braket
id|__NR_fchown
)braket
op_assign
id|sys_fchown16
comma
(braket
id|__NR_getpriority
)braket
op_assign
id|sys_getpriority
comma
(braket
id|__NR_setpriority
)braket
op_assign
id|sys_setpriority
comma
(braket
id|__NR_profil
)braket
op_assign
id|sys_ni_syscall
comma
(braket
id|__NR_statfs
)braket
op_assign
id|sys_statfs
comma
(braket
id|__NR_fstatfs
)braket
op_assign
id|sys_fstatfs
comma
(braket
id|__NR_ioperm
)braket
op_assign
id|sys_ni_syscall
comma
(braket
id|__NR_socketcall
)braket
op_assign
id|sys_socketcall
comma
(braket
id|__NR_syslog
)braket
op_assign
id|sys_syslog
comma
(braket
id|__NR_setitimer
)braket
op_assign
id|sys_setitimer
comma
(braket
id|__NR_getitimer
)braket
op_assign
id|sys_getitimer
comma
(braket
id|__NR_stat
)braket
op_assign
id|sys_newstat
comma
(braket
id|__NR_lstat
)braket
op_assign
id|sys_newlstat
comma
(braket
id|__NR_fstat
)braket
op_assign
id|sys_newfstat
comma
(braket
id|__NR_olduname
)braket
op_assign
id|sys_uname
comma
(braket
id|__NR_iopl
)braket
op_assign
id|sys_ni_syscall
comma
(braket
id|__NR_vhangup
)braket
op_assign
id|sys_vhangup
comma
(braket
id|__NR_idle
)braket
op_assign
id|sys_ni_syscall
comma
(braket
id|__NR_wait4
)braket
op_assign
(paren
id|syscall_handler_t
op_star
)paren
id|sys_wait4
comma
(braket
id|__NR_swapoff
)braket
op_assign
(paren
id|syscall_handler_t
op_star
)paren
id|sys_swapoff
comma
(braket
id|__NR_sysinfo
)braket
op_assign
id|sys_sysinfo
comma
(braket
id|__NR_ipc
)braket
op_assign
id|sys_ipc
comma
(braket
id|__NR_fsync
)braket
op_assign
id|sys_fsync
comma
(braket
id|__NR_sigreturn
)braket
op_assign
id|sys_sigreturn
comma
(braket
id|__NR_clone
)braket
op_assign
id|sys_clone
comma
(braket
id|__NR_setdomainname
)braket
op_assign
id|sys_setdomainname
comma
(braket
id|__NR_uname
)braket
op_assign
id|sys_newuname
comma
(braket
id|__NR_adjtimex
)braket
op_assign
id|sys_adjtimex
comma
(braket
id|__NR_mprotect
)braket
op_assign
id|sys_mprotect
comma
(braket
id|__NR_sigprocmask
)braket
op_assign
id|sys_sigprocmask
comma
(braket
id|__NR_create_module
)braket
op_assign
id|sys_create_module
comma
(braket
id|__NR_init_module
)braket
op_assign
id|sys_init_module
comma
(braket
id|__NR_delete_module
)braket
op_assign
id|sys_delete_module
comma
(braket
id|__NR_get_kernel_syms
)braket
op_assign
id|sys_get_kernel_syms
comma
(braket
id|__NR_quotactl
)braket
op_assign
id|sys_quotactl
comma
(braket
id|__NR_getpgid
)braket
op_assign
id|sys_getpgid
comma
(braket
id|__NR_fchdir
)braket
op_assign
id|sys_fchdir
comma
(braket
id|__NR_bdflush
)braket
op_assign
id|sys_bdflush
comma
(braket
id|__NR_sysfs
)braket
op_assign
id|sys_sysfs
comma
(braket
id|__NR_personality
)braket
op_assign
id|sys_personality
comma
(braket
id|__NR_afs_syscall
)braket
op_assign
id|sys_ni_syscall
comma
(braket
id|__NR_setfsuid
)braket
op_assign
id|sys_setfsuid16
comma
(braket
id|__NR_setfsgid
)braket
op_assign
id|sys_setfsgid16
comma
(braket
id|__NR__llseek
)braket
op_assign
id|sys_llseek
comma
(braket
id|__NR_getdents
)braket
op_assign
id|sys_getdents
comma
(braket
id|__NR__newselect
)braket
op_assign
(paren
id|syscall_handler_t
op_star
)paren
id|sys_select
comma
(braket
id|__NR_flock
)braket
op_assign
id|sys_flock
comma
(braket
id|__NR_msync
)braket
op_assign
id|sys_msync
comma
(braket
id|__NR_readv
)braket
op_assign
id|sys_readv
comma
(braket
id|__NR_writev
)braket
op_assign
id|sys_writev
comma
(braket
id|__NR_getsid
)braket
op_assign
id|sys_getsid
comma
(braket
id|__NR_fdatasync
)braket
op_assign
id|sys_fdatasync
comma
(braket
id|__NR__sysctl
)braket
op_assign
(paren
id|syscall_handler_t
op_star
)paren
id|sys_sysctl
comma
(braket
id|__NR_mlock
)braket
op_assign
id|sys_mlock
comma
(braket
id|__NR_munlock
)braket
op_assign
id|sys_munlock
comma
(braket
id|__NR_mlockall
)braket
op_assign
id|sys_mlockall
comma
(braket
id|__NR_munlockall
)braket
op_assign
id|sys_munlockall
comma
(braket
id|__NR_sched_setparam
)braket
op_assign
id|sys_sched_setparam
comma
(braket
id|__NR_sched_getparam
)braket
op_assign
id|sys_sched_getparam
comma
(braket
id|__NR_sched_setscheduler
)braket
op_assign
id|sys_sched_setscheduler
comma
(braket
id|__NR_sched_getscheduler
)braket
op_assign
id|sys_sched_getscheduler
comma
(braket
id|__NR_sched_yield
)braket
op_assign
(paren
id|syscall_handler_t
op_star
)paren
id|yield
comma
(braket
id|__NR_sched_get_priority_max
)braket
op_assign
id|sys_sched_get_priority_max
comma
(braket
id|__NR_sched_get_priority_min
)braket
op_assign
id|sys_sched_get_priority_min
comma
(braket
id|__NR_sched_rr_get_interval
)braket
op_assign
id|sys_sched_rr_get_interval
comma
(braket
id|__NR_nanosleep
)braket
op_assign
id|sys_nanosleep
comma
(braket
id|__NR_mremap
)braket
op_assign
id|sys_mremap
comma
(braket
id|__NR_setresuid
)braket
op_assign
id|sys_setresuid16
comma
(braket
id|__NR_getresuid
)braket
op_assign
id|sys_getresuid16
comma
(braket
id|__NR_vm86
)braket
op_assign
id|sys_ni_syscall
comma
(braket
id|__NR_query_module
)braket
op_assign
id|sys_query_module
comma
(braket
id|__NR_poll
)braket
op_assign
id|sys_poll
comma
(braket
id|__NR_nfsservctl
)braket
op_assign
id|NFSSERVCTL
comma
(braket
id|__NR_setresgid
)braket
op_assign
id|sys_setresgid16
comma
(braket
id|__NR_getresgid
)braket
op_assign
id|sys_getresgid16
comma
(braket
id|__NR_prctl
)braket
op_assign
id|sys_prctl
comma
(braket
id|__NR_rt_sigreturn
)braket
op_assign
id|sys_rt_sigreturn
comma
(braket
id|__NR_rt_sigaction
)braket
op_assign
id|sys_rt_sigaction
comma
(braket
id|__NR_rt_sigprocmask
)braket
op_assign
id|sys_rt_sigprocmask
comma
(braket
id|__NR_rt_sigpending
)braket
op_assign
id|sys_rt_sigpending
comma
(braket
id|__NR_rt_sigtimedwait
)braket
op_assign
id|sys_rt_sigtimedwait
comma
(braket
id|__NR_rt_sigqueueinfo
)braket
op_assign
id|sys_rt_sigqueueinfo
comma
(braket
id|__NR_rt_sigsuspend
)braket
op_assign
id|sys_rt_sigsuspend
comma
(braket
id|__NR_pread64
)braket
op_assign
id|sys_pread64
comma
(braket
id|__NR_pwrite64
)braket
op_assign
id|sys_pwrite64
comma
(braket
id|__NR_chown
)braket
op_assign
id|sys_chown16
comma
(braket
id|__NR_getcwd
)braket
op_assign
id|sys_getcwd
comma
(braket
id|__NR_capget
)braket
op_assign
id|sys_capget
comma
(braket
id|__NR_capset
)braket
op_assign
id|sys_capset
comma
(braket
id|__NR_sigaltstack
)braket
op_assign
id|sys_sigaltstack
comma
(braket
id|__NR_sendfile
)braket
op_assign
id|sys_sendfile
comma
(braket
id|__NR_getpmsg
)braket
op_assign
id|sys_ni_syscall
comma
(braket
id|__NR_putpmsg
)braket
op_assign
id|sys_ni_syscall
comma
(braket
id|__NR_vfork
)braket
op_assign
id|sys_vfork
comma
(braket
id|__NR_ugetrlimit
)braket
op_assign
id|sys_getrlimit
comma
(braket
id|__NR_mmap2
)braket
op_assign
id|sys_mmap2
comma
(braket
id|__NR_truncate64
)braket
op_assign
id|sys_truncate64
comma
(braket
id|__NR_ftruncate64
)braket
op_assign
id|sys_ftruncate64
comma
(braket
id|__NR_stat64
)braket
op_assign
id|sys_stat64
comma
(braket
id|__NR_lstat64
)braket
op_assign
id|sys_lstat64
comma
(braket
id|__NR_fstat64
)braket
op_assign
id|sys_fstat64
comma
(braket
id|__NR_fcntl64
)braket
op_assign
id|sys_fcntl64
comma
(braket
id|__NR_getdents64
)braket
op_assign
id|sys_getdents64
comma
(braket
id|__NR_gettid
)braket
op_assign
id|sys_gettid
comma
(braket
id|__NR_readahead
)braket
op_assign
id|sys_readahead
comma
(braket
id|__NR_setxattr
)braket
op_assign
id|sys_ni_syscall
comma
(braket
id|__NR_lsetxattr
)braket
op_assign
id|sys_ni_syscall
comma
(braket
id|__NR_fsetxattr
)braket
op_assign
id|sys_ni_syscall
comma
(braket
id|__NR_getxattr
)braket
op_assign
id|sys_ni_syscall
comma
(braket
id|__NR_lgetxattr
)braket
op_assign
id|sys_ni_syscall
comma
(braket
id|__NR_fgetxattr
)braket
op_assign
id|sys_ni_syscall
comma
(braket
id|__NR_listxattr
)braket
op_assign
id|sys_ni_syscall
comma
(braket
id|__NR_llistxattr
)braket
op_assign
id|sys_ni_syscall
comma
(braket
id|__NR_flistxattr
)braket
op_assign
id|sys_ni_syscall
comma
(braket
id|__NR_removexattr
)braket
op_assign
id|sys_ni_syscall
comma
(braket
id|__NR_lremovexattr
)braket
op_assign
id|sys_ni_syscall
comma
(braket
id|__NR_fremovexattr
)braket
op_assign
id|sys_ni_syscall
comma
(braket
id|__NR_tkill
)braket
op_assign
id|sys_tkill
comma
(braket
id|__NR_sendfile64
)braket
op_assign
id|sys_sendfile64
comma
(braket
id|__NR_futex
)braket
op_assign
id|sys_futex
comma
(braket
id|__NR_sched_setaffinity
)braket
op_assign
id|sys_sched_setaffinity
comma
(braket
id|__NR_sched_getaffinity
)braket
op_assign
id|sys_sched_getaffinity
comma
(braket
id|__NR_io_setup
)braket
op_assign
id|sys_io_setup
comma
(braket
id|__NR_io_destroy
)braket
op_assign
id|sys_io_destroy
comma
(braket
id|__NR_io_getevents
)braket
op_assign
id|sys_io_getevents
comma
(braket
id|__NR_io_submit
)braket
op_assign
id|sys_io_submit
comma
(braket
id|__NR_io_cancel
)braket
op_assign
id|sys_io_cancel
comma
(braket
id|__NR_alloc_hugepages
)braket
op_assign
id|sys_ni_syscall
comma
(braket
id|__NR_free_hugepages
)braket
op_assign
id|sys_ni_syscall
comma
(braket
id|__NR_exit_group
)braket
op_assign
id|sys_exit_group
comma
(braket
id|__NR_lookup_dcookie
)braket
op_assign
id|sys_lookup_dcookie
comma
(braket
id|__NR_epoll_create
)braket
op_assign
id|sys_epoll_create
comma
(braket
id|__NR_epoll_ctl
)braket
op_assign
id|sys_epoll_ctl
comma
(braket
id|__NR_epoll_wait
)braket
op_assign
id|sys_epoll_wait
comma
(braket
id|__NR_remap_file_pages
)braket
op_assign
id|sys_remap_file_pages
comma
id|ARCH_SYSCALLS
(braket
id|LAST_SYSCALL
op_plus
l_int|1
dot
dot
dot
id|NR_syscalls
)braket
op_assign
(paren
id|syscall_handler_t
op_star
)paren
id|sys_ni_syscall
)brace
suffix:semicolon
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
