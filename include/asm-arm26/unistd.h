multiline_comment|/*&n; *  linux/include/asm-arm/unistd.h&n; *&n; *  Copyright (C) 2001-2003 Russell King&n; *  Modified 25/11/04 Ian Molton for arm26.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; * Please forward _all_ changes to this file to spyro@f2s.com&n; * no matter what the change is.  Thanks!&n; */
macro_line|#ifndef __ASM_ARM_UNISTD_H
DECL|macro|__ASM_ARM_UNISTD_H
mdefine_line|#define __ASM_ARM_UNISTD_H
macro_line|#include &lt;linux/linkage.h&gt;
DECL|macro|__NR_SYSCALL_BASE
mdefine_line|#define __NR_SYSCALL_BASE&t;0x900000
multiline_comment|/*&n; * This file contains the system call numbers.&n; */
DECL|macro|__NR_restart_syscall
mdefine_line|#define __NR_restart_syscall&t;&t;(__NR_SYSCALL_BASE+  0)
DECL|macro|__NR_exit
mdefine_line|#define __NR_exit&t;&t;&t;(__NR_SYSCALL_BASE+  1)
DECL|macro|__NR_fork
mdefine_line|#define __NR_fork&t;&t;&t;(__NR_SYSCALL_BASE+  2)
DECL|macro|__NR_read
mdefine_line|#define __NR_read&t;&t;&t;(__NR_SYSCALL_BASE+  3)
DECL|macro|__NR_write
mdefine_line|#define __NR_write&t;&t;&t;(__NR_SYSCALL_BASE+  4)
DECL|macro|__NR_open
mdefine_line|#define __NR_open&t;&t;&t;(__NR_SYSCALL_BASE+  5)
DECL|macro|__NR_close
mdefine_line|#define __NR_close&t;&t;&t;(__NR_SYSCALL_BASE+  6)
multiline_comment|/* 7 was sys_waitpid */
DECL|macro|__NR_creat
mdefine_line|#define __NR_creat&t;&t;&t;(__NR_SYSCALL_BASE+  8)
DECL|macro|__NR_link
mdefine_line|#define __NR_link&t;&t;&t;(__NR_SYSCALL_BASE+  9)
DECL|macro|__NR_unlink
mdefine_line|#define __NR_unlink&t;&t;&t;(__NR_SYSCALL_BASE+ 10)
DECL|macro|__NR_execve
mdefine_line|#define __NR_execve&t;&t;&t;(__NR_SYSCALL_BASE+ 11)
DECL|macro|__NR_chdir
mdefine_line|#define __NR_chdir&t;&t;&t;(__NR_SYSCALL_BASE+ 12)
DECL|macro|__NR_time
mdefine_line|#define __NR_time&t;&t;&t;(__NR_SYSCALL_BASE+ 13)
DECL|macro|__NR_mknod
mdefine_line|#define __NR_mknod&t;&t;&t;(__NR_SYSCALL_BASE+ 14)
DECL|macro|__NR_chmod
mdefine_line|#define __NR_chmod&t;&t;&t;(__NR_SYSCALL_BASE+ 15)
DECL|macro|__NR_lchown
mdefine_line|#define __NR_lchown&t;&t;&t;(__NR_SYSCALL_BASE+ 16)
multiline_comment|/* 17 was sys_break */
multiline_comment|/* 18 was sys_stat */
DECL|macro|__NR_lseek
mdefine_line|#define __NR_lseek&t;&t;&t;(__NR_SYSCALL_BASE+ 19)
DECL|macro|__NR_getpid
mdefine_line|#define __NR_getpid&t;&t;&t;(__NR_SYSCALL_BASE+ 20)
DECL|macro|__NR_mount
mdefine_line|#define __NR_mount&t;&t;&t;(__NR_SYSCALL_BASE+ 21)
DECL|macro|__NR_umount
mdefine_line|#define __NR_umount&t;&t;&t;(__NR_SYSCALL_BASE+ 22)
DECL|macro|__NR_setuid
mdefine_line|#define __NR_setuid&t;&t;&t;(__NR_SYSCALL_BASE+ 23)
DECL|macro|__NR_getuid
mdefine_line|#define __NR_getuid&t;&t;&t;(__NR_SYSCALL_BASE+ 24)
DECL|macro|__NR_stime
mdefine_line|#define __NR_stime&t;&t;&t;(__NR_SYSCALL_BASE+ 25)
DECL|macro|__NR_ptrace
mdefine_line|#define __NR_ptrace&t;&t;&t;(__NR_SYSCALL_BASE+ 26)
DECL|macro|__NR_alarm
mdefine_line|#define __NR_alarm&t;&t;&t;(__NR_SYSCALL_BASE+ 27)
multiline_comment|/* 28 was sys_fstat */
DECL|macro|__NR_pause
mdefine_line|#define __NR_pause&t;&t;&t;(__NR_SYSCALL_BASE+ 29)
DECL|macro|__NR_utime
mdefine_line|#define __NR_utime&t;&t;&t;(__NR_SYSCALL_BASE+ 30)
multiline_comment|/* 31 was sys_stty */
multiline_comment|/* 32 was sys_gtty */
DECL|macro|__NR_access
mdefine_line|#define __NR_access&t;&t;&t;(__NR_SYSCALL_BASE+ 33)
DECL|macro|__NR_nice
mdefine_line|#define __NR_nice&t;&t;&t;(__NR_SYSCALL_BASE+ 34)
multiline_comment|/* 35 was sys_ftime */
DECL|macro|__NR_sync
mdefine_line|#define __NR_sync&t;&t;&t;(__NR_SYSCALL_BASE+ 36)
DECL|macro|__NR_kill
mdefine_line|#define __NR_kill&t;&t;&t;(__NR_SYSCALL_BASE+ 37)
DECL|macro|__NR_rename
mdefine_line|#define __NR_rename&t;&t;&t;(__NR_SYSCALL_BASE+ 38)
DECL|macro|__NR_mkdir
mdefine_line|#define __NR_mkdir&t;&t;&t;(__NR_SYSCALL_BASE+ 39)
DECL|macro|__NR_rmdir
mdefine_line|#define __NR_rmdir&t;&t;&t;(__NR_SYSCALL_BASE+ 40)
DECL|macro|__NR_dup
mdefine_line|#define __NR_dup&t;&t;&t;(__NR_SYSCALL_BASE+ 41)
DECL|macro|__NR_pipe
mdefine_line|#define __NR_pipe&t;&t;&t;(__NR_SYSCALL_BASE+ 42)
DECL|macro|__NR_times
mdefine_line|#define __NR_times&t;&t;&t;(__NR_SYSCALL_BASE+ 43)
multiline_comment|/* 44 was sys_prof */
DECL|macro|__NR_brk
mdefine_line|#define __NR_brk&t;&t;&t;(__NR_SYSCALL_BASE+ 45)
DECL|macro|__NR_setgid
mdefine_line|#define __NR_setgid&t;&t;&t;(__NR_SYSCALL_BASE+ 46)
DECL|macro|__NR_getgid
mdefine_line|#define __NR_getgid&t;&t;&t;(__NR_SYSCALL_BASE+ 47)
multiline_comment|/* 48 was sys_signal */
DECL|macro|__NR_geteuid
mdefine_line|#define __NR_geteuid&t;&t;&t;(__NR_SYSCALL_BASE+ 49)
DECL|macro|__NR_getegid
mdefine_line|#define __NR_getegid&t;&t;&t;(__NR_SYSCALL_BASE+ 50)
DECL|macro|__NR_acct
mdefine_line|#define __NR_acct&t;&t;&t;(__NR_SYSCALL_BASE+ 51)
DECL|macro|__NR_umount2
mdefine_line|#define __NR_umount2&t;&t;&t;(__NR_SYSCALL_BASE+ 52)
multiline_comment|/* 53 was sys_lock */
DECL|macro|__NR_ioctl
mdefine_line|#define __NR_ioctl&t;&t;&t;(__NR_SYSCALL_BASE+ 54)
DECL|macro|__NR_fcntl
mdefine_line|#define __NR_fcntl&t;&t;&t;(__NR_SYSCALL_BASE+ 55)
multiline_comment|/* 56 was sys_mpx */
DECL|macro|__NR_setpgid
mdefine_line|#define __NR_setpgid&t;&t;&t;(__NR_SYSCALL_BASE+ 57)
multiline_comment|/* 58 was sys_ulimit */
multiline_comment|/* 59 was sys_olduname */
DECL|macro|__NR_umask
mdefine_line|#define __NR_umask&t;&t;&t;(__NR_SYSCALL_BASE+ 60)
DECL|macro|__NR_chroot
mdefine_line|#define __NR_chroot&t;&t;&t;(__NR_SYSCALL_BASE+ 61)
DECL|macro|__NR_ustat
mdefine_line|#define __NR_ustat&t;&t;&t;(__NR_SYSCALL_BASE+ 62)
DECL|macro|__NR_dup2
mdefine_line|#define __NR_dup2&t;&t;&t;(__NR_SYSCALL_BASE+ 63)
DECL|macro|__NR_getppid
mdefine_line|#define __NR_getppid&t;&t;&t;(__NR_SYSCALL_BASE+ 64)
DECL|macro|__NR_getpgrp
mdefine_line|#define __NR_getpgrp&t;&t;&t;(__NR_SYSCALL_BASE+ 65)
DECL|macro|__NR_setsid
mdefine_line|#define __NR_setsid&t;&t;&t;(__NR_SYSCALL_BASE+ 66)
DECL|macro|__NR_sigaction
mdefine_line|#define __NR_sigaction&t;&t;&t;(__NR_SYSCALL_BASE+ 67)
multiline_comment|/* 68 was sys_sgetmask */
multiline_comment|/* 69 was sys_ssetmask */
DECL|macro|__NR_setreuid
mdefine_line|#define __NR_setreuid&t;&t;&t;(__NR_SYSCALL_BASE+ 70)
DECL|macro|__NR_setregid
mdefine_line|#define __NR_setregid&t;&t;&t;(__NR_SYSCALL_BASE+ 71)
DECL|macro|__NR_sigsuspend
mdefine_line|#define __NR_sigsuspend&t;&t;&t;(__NR_SYSCALL_BASE+ 72)
DECL|macro|__NR_sigpending
mdefine_line|#define __NR_sigpending&t;&t;&t;(__NR_SYSCALL_BASE+ 73)
DECL|macro|__NR_sethostname
mdefine_line|#define __NR_sethostname&t;&t;(__NR_SYSCALL_BASE+ 74)
DECL|macro|__NR_setrlimit
mdefine_line|#define __NR_setrlimit&t;&t;&t;(__NR_SYSCALL_BASE+ 75)
DECL|macro|__NR_getrlimit
mdefine_line|#define __NR_getrlimit&t;&t;&t;(__NR_SYSCALL_BASE+ 76)&t;/* Back compat 2GB limited rlimit */
DECL|macro|__NR_getrusage
mdefine_line|#define __NR_getrusage&t;&t;&t;(__NR_SYSCALL_BASE+ 77)
DECL|macro|__NR_gettimeofday
mdefine_line|#define __NR_gettimeofday&t;&t;(__NR_SYSCALL_BASE+ 78)
DECL|macro|__NR_settimeofday
mdefine_line|#define __NR_settimeofday&t;&t;(__NR_SYSCALL_BASE+ 79)
DECL|macro|__NR_getgroups
mdefine_line|#define __NR_getgroups&t;&t;&t;(__NR_SYSCALL_BASE+ 80)
DECL|macro|__NR_setgroups
mdefine_line|#define __NR_setgroups&t;&t;&t;(__NR_SYSCALL_BASE+ 81)
DECL|macro|__NR_select
mdefine_line|#define __NR_select&t;&t;&t;(__NR_SYSCALL_BASE+ 82)
DECL|macro|__NR_symlink
mdefine_line|#define __NR_symlink&t;&t;&t;(__NR_SYSCALL_BASE+ 83)
multiline_comment|/* 84 was sys_lstat */
DECL|macro|__NR_readlink
mdefine_line|#define __NR_readlink&t;&t;&t;(__NR_SYSCALL_BASE+ 85)
DECL|macro|__NR_uselib
mdefine_line|#define __NR_uselib&t;&t;&t;(__NR_SYSCALL_BASE+ 86)
DECL|macro|__NR_swapon
mdefine_line|#define __NR_swapon&t;&t;&t;(__NR_SYSCALL_BASE+ 87)
DECL|macro|__NR_reboot
mdefine_line|#define __NR_reboot&t;&t;&t;(__NR_SYSCALL_BASE+ 88)
DECL|macro|__NR_readdir
mdefine_line|#define __NR_readdir&t;&t;&t;(__NR_SYSCALL_BASE+ 89)
DECL|macro|__NR_mmap
mdefine_line|#define __NR_mmap&t;&t;&t;(__NR_SYSCALL_BASE+ 90)
DECL|macro|__NR_munmap
mdefine_line|#define __NR_munmap&t;&t;&t;(__NR_SYSCALL_BASE+ 91)
DECL|macro|__NR_truncate
mdefine_line|#define __NR_truncate&t;&t;&t;(__NR_SYSCALL_BASE+ 92)
DECL|macro|__NR_ftruncate
mdefine_line|#define __NR_ftruncate&t;&t;&t;(__NR_SYSCALL_BASE+ 93)
DECL|macro|__NR_fchmod
mdefine_line|#define __NR_fchmod&t;&t;&t;(__NR_SYSCALL_BASE+ 94)
DECL|macro|__NR_fchown
mdefine_line|#define __NR_fchown&t;&t;&t;(__NR_SYSCALL_BASE+ 95)
DECL|macro|__NR_getpriority
mdefine_line|#define __NR_getpriority&t;&t;(__NR_SYSCALL_BASE+ 96)
DECL|macro|__NR_setpriority
mdefine_line|#define __NR_setpriority&t;&t;(__NR_SYSCALL_BASE+ 97)
multiline_comment|/* 98 was sys_profil */
DECL|macro|__NR_statfs
mdefine_line|#define __NR_statfs&t;&t;&t;(__NR_SYSCALL_BASE+ 99)
DECL|macro|__NR_fstatfs
mdefine_line|#define __NR_fstatfs&t;&t;&t;(__NR_SYSCALL_BASE+100)
multiline_comment|/* 101 was sys_ioperm */
DECL|macro|__NR_socketcall
mdefine_line|#define __NR_socketcall&t;&t;&t;(__NR_SYSCALL_BASE+102)
DECL|macro|__NR_syslog
mdefine_line|#define __NR_syslog&t;&t;&t;(__NR_SYSCALL_BASE+103)
DECL|macro|__NR_setitimer
mdefine_line|#define __NR_setitimer&t;&t;&t;(__NR_SYSCALL_BASE+104)
DECL|macro|__NR_getitimer
mdefine_line|#define __NR_getitimer&t;&t;&t;(__NR_SYSCALL_BASE+105)
DECL|macro|__NR_stat
mdefine_line|#define __NR_stat&t;&t;&t;(__NR_SYSCALL_BASE+106)
DECL|macro|__NR_lstat
mdefine_line|#define __NR_lstat&t;&t;&t;(__NR_SYSCALL_BASE+107)
DECL|macro|__NR_fstat
mdefine_line|#define __NR_fstat&t;&t;&t;(__NR_SYSCALL_BASE+108)
multiline_comment|/* 109 was sys_uname */
multiline_comment|/* 110 was sys_iopl */
DECL|macro|__NR_vhangup
mdefine_line|#define __NR_vhangup&t;&t;&t;(__NR_SYSCALL_BASE+111)
multiline_comment|/* 112 was sys_idle */
DECL|macro|__NR_syscall
mdefine_line|#define __NR_syscall&t;&t;&t;(__NR_SYSCALL_BASE+113) /* syscall to call a syscall! */
DECL|macro|__NR_wait4
mdefine_line|#define __NR_wait4&t;&t;&t;(__NR_SYSCALL_BASE+114)
DECL|macro|__NR_swapoff
mdefine_line|#define __NR_swapoff&t;&t;&t;(__NR_SYSCALL_BASE+115)
DECL|macro|__NR_sysinfo
mdefine_line|#define __NR_sysinfo&t;&t;&t;(__NR_SYSCALL_BASE+116)
DECL|macro|__NR_ipc
mdefine_line|#define __NR_ipc&t;&t;&t;(__NR_SYSCALL_BASE+117)
DECL|macro|__NR_fsync
mdefine_line|#define __NR_fsync&t;&t;&t;(__NR_SYSCALL_BASE+118)
DECL|macro|__NR_sigreturn
mdefine_line|#define __NR_sigreturn&t;&t;&t;(__NR_SYSCALL_BASE+119)
DECL|macro|__NR_clone
mdefine_line|#define __NR_clone&t;&t;&t;(__NR_SYSCALL_BASE+120)
DECL|macro|__NR_setdomainname
mdefine_line|#define __NR_setdomainname&t;&t;(__NR_SYSCALL_BASE+121)
DECL|macro|__NR_uname
mdefine_line|#define __NR_uname&t;&t;&t;(__NR_SYSCALL_BASE+122)
multiline_comment|/* 123 was sys_modify_ldt */
DECL|macro|__NR_adjtimex
mdefine_line|#define __NR_adjtimex&t;&t;&t;(__NR_SYSCALL_BASE+124)
DECL|macro|__NR_mprotect
mdefine_line|#define __NR_mprotect&t;&t;&t;(__NR_SYSCALL_BASE+125)
DECL|macro|__NR_sigprocmask
mdefine_line|#define __NR_sigprocmask&t;&t;(__NR_SYSCALL_BASE+126)
multiline_comment|/* 127 was sys_create_module */
DECL|macro|__NR_init_module
mdefine_line|#define __NR_init_module&t;&t;(__NR_SYSCALL_BASE+128)
DECL|macro|__NR_delete_module
mdefine_line|#define __NR_delete_module&t;&t;(__NR_SYSCALL_BASE+129)
multiline_comment|/* 130 was sys_get_kernel_syms */
DECL|macro|__NR_quotactl
mdefine_line|#define __NR_quotactl&t;&t;&t;(__NR_SYSCALL_BASE+131)
DECL|macro|__NR_getpgid
mdefine_line|#define __NR_getpgid&t;&t;&t;(__NR_SYSCALL_BASE+132)
DECL|macro|__NR_fchdir
mdefine_line|#define __NR_fchdir&t;&t;&t;(__NR_SYSCALL_BASE+133)
DECL|macro|__NR_bdflush
mdefine_line|#define __NR_bdflush&t;&t;&t;(__NR_SYSCALL_BASE+134)
DECL|macro|__NR_sysfs
mdefine_line|#define __NR_sysfs&t;&t;&t;(__NR_SYSCALL_BASE+135)
DECL|macro|__NR_personality
mdefine_line|#define __NR_personality&t;&t;(__NR_SYSCALL_BASE+136)
multiline_comment|/* 137 was sys_afs_syscall */
DECL|macro|__NR_setfsuid
mdefine_line|#define __NR_setfsuid&t;&t;&t;(__NR_SYSCALL_BASE+138)
DECL|macro|__NR_setfsgid
mdefine_line|#define __NR_setfsgid&t;&t;&t;(__NR_SYSCALL_BASE+139)
DECL|macro|__NR__llseek
mdefine_line|#define __NR__llseek&t;&t;&t;(__NR_SYSCALL_BASE+140)
DECL|macro|__NR_getdents
mdefine_line|#define __NR_getdents&t;&t;&t;(__NR_SYSCALL_BASE+141)
DECL|macro|__NR__newselect
mdefine_line|#define __NR__newselect&t;&t;&t;(__NR_SYSCALL_BASE+142)
DECL|macro|__NR_flock
mdefine_line|#define __NR_flock&t;&t;&t;(__NR_SYSCALL_BASE+143)
DECL|macro|__NR_msync
mdefine_line|#define __NR_msync&t;&t;&t;(__NR_SYSCALL_BASE+144)
DECL|macro|__NR_readv
mdefine_line|#define __NR_readv&t;&t;&t;(__NR_SYSCALL_BASE+145)
DECL|macro|__NR_writev
mdefine_line|#define __NR_writev&t;&t;&t;(__NR_SYSCALL_BASE+146)
DECL|macro|__NR_getsid
mdefine_line|#define __NR_getsid&t;&t;&t;(__NR_SYSCALL_BASE+147)
DECL|macro|__NR_fdatasync
mdefine_line|#define __NR_fdatasync&t;&t;&t;(__NR_SYSCALL_BASE+148)
DECL|macro|__NR__sysctl
mdefine_line|#define __NR__sysctl&t;&t;&t;(__NR_SYSCALL_BASE+149)
DECL|macro|__NR_mlock
mdefine_line|#define __NR_mlock&t;&t;&t;(__NR_SYSCALL_BASE+150)
DECL|macro|__NR_munlock
mdefine_line|#define __NR_munlock&t;&t;&t;(__NR_SYSCALL_BASE+151)
DECL|macro|__NR_mlockall
mdefine_line|#define __NR_mlockall&t;&t;&t;(__NR_SYSCALL_BASE+152)
DECL|macro|__NR_munlockall
mdefine_line|#define __NR_munlockall&t;&t;&t;(__NR_SYSCALL_BASE+153)
DECL|macro|__NR_sched_setparam
mdefine_line|#define __NR_sched_setparam&t;&t;(__NR_SYSCALL_BASE+154)
DECL|macro|__NR_sched_getparam
mdefine_line|#define __NR_sched_getparam&t;&t;(__NR_SYSCALL_BASE+155)
DECL|macro|__NR_sched_setscheduler
mdefine_line|#define __NR_sched_setscheduler&t;&t;(__NR_SYSCALL_BASE+156)
DECL|macro|__NR_sched_getscheduler
mdefine_line|#define __NR_sched_getscheduler&t;&t;(__NR_SYSCALL_BASE+157)
DECL|macro|__NR_sched_yield
mdefine_line|#define __NR_sched_yield&t;&t;(__NR_SYSCALL_BASE+158)
DECL|macro|__NR_sched_get_priority_max
mdefine_line|#define __NR_sched_get_priority_max&t;(__NR_SYSCALL_BASE+159)
DECL|macro|__NR_sched_get_priority_min
mdefine_line|#define __NR_sched_get_priority_min&t;(__NR_SYSCALL_BASE+160)
DECL|macro|__NR_sched_rr_get_interval
mdefine_line|#define __NR_sched_rr_get_interval&t;(__NR_SYSCALL_BASE+161)
DECL|macro|__NR_nanosleep
mdefine_line|#define __NR_nanosleep&t;&t;&t;(__NR_SYSCALL_BASE+162)
DECL|macro|__NR_mremap
mdefine_line|#define __NR_mremap&t;&t;&t;(__NR_SYSCALL_BASE+163)
DECL|macro|__NR_setresuid
mdefine_line|#define __NR_setresuid&t;&t;&t;(__NR_SYSCALL_BASE+164)
DECL|macro|__NR_getresuid
mdefine_line|#define __NR_getresuid&t;&t;&t;(__NR_SYSCALL_BASE+165)
multiline_comment|/* 166 was sys_vm86 */
multiline_comment|/* 167 was sys_query_module */
DECL|macro|__NR_poll
mdefine_line|#define __NR_poll&t;&t;&t;(__NR_SYSCALL_BASE+168)
DECL|macro|__NR_nfsservctl
mdefine_line|#define __NR_nfsservctl&t;&t;&t;(__NR_SYSCALL_BASE+169)
DECL|macro|__NR_setresgid
mdefine_line|#define __NR_setresgid&t;&t;&t;(__NR_SYSCALL_BASE+170)
DECL|macro|__NR_getresgid
mdefine_line|#define __NR_getresgid&t;&t;&t;(__NR_SYSCALL_BASE+171)
DECL|macro|__NR_prctl
mdefine_line|#define __NR_prctl&t;&t;&t;(__NR_SYSCALL_BASE+172)
DECL|macro|__NR_rt_sigreturn
mdefine_line|#define __NR_rt_sigreturn&t;&t;(__NR_SYSCALL_BASE+173)
DECL|macro|__NR_rt_sigaction
mdefine_line|#define __NR_rt_sigaction&t;&t;(__NR_SYSCALL_BASE+174)
DECL|macro|__NR_rt_sigprocmask
mdefine_line|#define __NR_rt_sigprocmask&t;&t;(__NR_SYSCALL_BASE+175)
DECL|macro|__NR_rt_sigpending
mdefine_line|#define __NR_rt_sigpending&t;&t;(__NR_SYSCALL_BASE+176)
DECL|macro|__NR_rt_sigtimedwait
mdefine_line|#define __NR_rt_sigtimedwait&t;&t;(__NR_SYSCALL_BASE+177)
DECL|macro|__NR_rt_sigqueueinfo
mdefine_line|#define __NR_rt_sigqueueinfo&t;&t;(__NR_SYSCALL_BASE+178)
DECL|macro|__NR_rt_sigsuspend
mdefine_line|#define __NR_rt_sigsuspend&t;&t;(__NR_SYSCALL_BASE+179)
DECL|macro|__NR_pread64
mdefine_line|#define __NR_pread64&t;&t;&t;(__NR_SYSCALL_BASE+180)
DECL|macro|__NR_pwrite64
mdefine_line|#define __NR_pwrite64&t;&t;&t;(__NR_SYSCALL_BASE+181)
DECL|macro|__NR_chown
mdefine_line|#define __NR_chown&t;&t;&t;(__NR_SYSCALL_BASE+182)
DECL|macro|__NR_getcwd
mdefine_line|#define __NR_getcwd&t;&t;&t;(__NR_SYSCALL_BASE+183)
DECL|macro|__NR_capget
mdefine_line|#define __NR_capget&t;&t;&t;(__NR_SYSCALL_BASE+184)
DECL|macro|__NR_capset
mdefine_line|#define __NR_capset&t;&t;&t;(__NR_SYSCALL_BASE+185)
DECL|macro|__NR_sigaltstack
mdefine_line|#define __NR_sigaltstack&t;&t;(__NR_SYSCALL_BASE+186)
DECL|macro|__NR_sendfile
mdefine_line|#define __NR_sendfile&t;&t;&t;(__NR_SYSCALL_BASE+187)
multiline_comment|/* 188 reserved */
multiline_comment|/* 189 reserved */
DECL|macro|__NR_vfork
mdefine_line|#define __NR_vfork&t;&t;&t;(__NR_SYSCALL_BASE+190)
DECL|macro|__NR_ugetrlimit
mdefine_line|#define __NR_ugetrlimit&t;&t;&t;(__NR_SYSCALL_BASE+191)&t;/* SuS compliant getrlimit */
DECL|macro|__NR_mmap2
mdefine_line|#define __NR_mmap2&t;&t;&t;(__NR_SYSCALL_BASE+192)
DECL|macro|__NR_truncate64
mdefine_line|#define __NR_truncate64&t;&t;&t;(__NR_SYSCALL_BASE+193)
DECL|macro|__NR_ftruncate64
mdefine_line|#define __NR_ftruncate64&t;&t;(__NR_SYSCALL_BASE+194)
DECL|macro|__NR_stat64
mdefine_line|#define __NR_stat64&t;&t;&t;(__NR_SYSCALL_BASE+195)
DECL|macro|__NR_lstat64
mdefine_line|#define __NR_lstat64&t;&t;&t;(__NR_SYSCALL_BASE+196)
DECL|macro|__NR_fstat64
mdefine_line|#define __NR_fstat64&t;&t;&t;(__NR_SYSCALL_BASE+197)
DECL|macro|__NR_lchown32
mdefine_line|#define __NR_lchown32&t;&t;&t;(__NR_SYSCALL_BASE+198)
DECL|macro|__NR_getuid32
mdefine_line|#define __NR_getuid32&t;&t;&t;(__NR_SYSCALL_BASE+199)
DECL|macro|__NR_getgid32
mdefine_line|#define __NR_getgid32&t;&t;&t;(__NR_SYSCALL_BASE+200)
DECL|macro|__NR_geteuid32
mdefine_line|#define __NR_geteuid32&t;&t;&t;(__NR_SYSCALL_BASE+201)
DECL|macro|__NR_getegid32
mdefine_line|#define __NR_getegid32&t;&t;&t;(__NR_SYSCALL_BASE+202)
DECL|macro|__NR_setreuid32
mdefine_line|#define __NR_setreuid32&t;&t;&t;(__NR_SYSCALL_BASE+203)
DECL|macro|__NR_setregid32
mdefine_line|#define __NR_setregid32&t;&t;&t;(__NR_SYSCALL_BASE+204)
DECL|macro|__NR_getgroups32
mdefine_line|#define __NR_getgroups32&t;&t;(__NR_SYSCALL_BASE+205)
DECL|macro|__NR_setgroups32
mdefine_line|#define __NR_setgroups32&t;&t;(__NR_SYSCALL_BASE+206)
DECL|macro|__NR_fchown32
mdefine_line|#define __NR_fchown32&t;&t;&t;(__NR_SYSCALL_BASE+207)
DECL|macro|__NR_setresuid32
mdefine_line|#define __NR_setresuid32&t;&t;(__NR_SYSCALL_BASE+208)
DECL|macro|__NR_getresuid32
mdefine_line|#define __NR_getresuid32&t;&t;(__NR_SYSCALL_BASE+209)
DECL|macro|__NR_setresgid32
mdefine_line|#define __NR_setresgid32&t;&t;(__NR_SYSCALL_BASE+210)
DECL|macro|__NR_getresgid32
mdefine_line|#define __NR_getresgid32&t;&t;(__NR_SYSCALL_BASE+211)
DECL|macro|__NR_chown32
mdefine_line|#define __NR_chown32&t;&t;&t;(__NR_SYSCALL_BASE+212)
DECL|macro|__NR_setuid32
mdefine_line|#define __NR_setuid32&t;&t;&t;(__NR_SYSCALL_BASE+213)
DECL|macro|__NR_setgid32
mdefine_line|#define __NR_setgid32&t;&t;&t;(__NR_SYSCALL_BASE+214)
DECL|macro|__NR_setfsuid32
mdefine_line|#define __NR_setfsuid32&t;&t;&t;(__NR_SYSCALL_BASE+215)
DECL|macro|__NR_setfsgid32
mdefine_line|#define __NR_setfsgid32&t;&t;&t;(__NR_SYSCALL_BASE+216)
DECL|macro|__NR_getdents64
mdefine_line|#define __NR_getdents64&t;&t;&t;(__NR_SYSCALL_BASE+217)
DECL|macro|__NR_pivot_root
mdefine_line|#define __NR_pivot_root&t;&t;&t;(__NR_SYSCALL_BASE+218)
DECL|macro|__NR_mincore
mdefine_line|#define __NR_mincore&t;&t;&t;(__NR_SYSCALL_BASE+219)
DECL|macro|__NR_madvise
mdefine_line|#define __NR_madvise&t;&t;&t;(__NR_SYSCALL_BASE+220)
DECL|macro|__NR_fcntl64
mdefine_line|#define __NR_fcntl64&t;&t;&t;(__NR_SYSCALL_BASE+221)
multiline_comment|/* 222 for tux */
multiline_comment|/* 223 is unused */
DECL|macro|__NR_gettid
mdefine_line|#define __NR_gettid&t;&t;&t;(__NR_SYSCALL_BASE+224)
DECL|macro|__NR_readahead
mdefine_line|#define __NR_readahead&t;&t;&t;(__NR_SYSCALL_BASE+225)
DECL|macro|__NR_setxattr
mdefine_line|#define __NR_setxattr&t;&t;&t;(__NR_SYSCALL_BASE+226)
DECL|macro|__NR_lsetxattr
mdefine_line|#define __NR_lsetxattr&t;&t;&t;(__NR_SYSCALL_BASE+227)
DECL|macro|__NR_fsetxattr
mdefine_line|#define __NR_fsetxattr&t;&t;&t;(__NR_SYSCALL_BASE+228)
DECL|macro|__NR_getxattr
mdefine_line|#define __NR_getxattr&t;&t;&t;(__NR_SYSCALL_BASE+229)
DECL|macro|__NR_lgetxattr
mdefine_line|#define __NR_lgetxattr&t;&t;&t;(__NR_SYSCALL_BASE+230)
DECL|macro|__NR_fgetxattr
mdefine_line|#define __NR_fgetxattr&t;&t;&t;(__NR_SYSCALL_BASE+231)
DECL|macro|__NR_listxattr
mdefine_line|#define __NR_listxattr&t;&t;&t;(__NR_SYSCALL_BASE+232)
DECL|macro|__NR_llistxattr
mdefine_line|#define __NR_llistxattr&t;&t;&t;(__NR_SYSCALL_BASE+233)
DECL|macro|__NR_flistxattr
mdefine_line|#define __NR_flistxattr&t;&t;&t;(__NR_SYSCALL_BASE+234)
DECL|macro|__NR_removexattr
mdefine_line|#define __NR_removexattr&t;&t;(__NR_SYSCALL_BASE+235)
DECL|macro|__NR_lremovexattr
mdefine_line|#define __NR_lremovexattr&t;&t;(__NR_SYSCALL_BASE+236)
DECL|macro|__NR_fremovexattr
mdefine_line|#define __NR_fremovexattr&t;&t;(__NR_SYSCALL_BASE+237)
DECL|macro|__NR_tkill
mdefine_line|#define __NR_tkill&t;&t;&t;(__NR_SYSCALL_BASE+238)
DECL|macro|__NR_sendfile64
mdefine_line|#define __NR_sendfile64&t;&t;&t;(__NR_SYSCALL_BASE+239)
DECL|macro|__NR_futex
mdefine_line|#define __NR_futex&t;&t;&t;(__NR_SYSCALL_BASE+240)
DECL|macro|__NR_sched_setaffinity
mdefine_line|#define __NR_sched_setaffinity&t;&t;(__NR_SYSCALL_BASE+241)
DECL|macro|__NR_sched_getaffinity
mdefine_line|#define __NR_sched_getaffinity&t;&t;(__NR_SYSCALL_BASE+242)
DECL|macro|__NR_io_setup
mdefine_line|#define __NR_io_setup&t;&t;&t;(__NR_SYSCALL_BASE+243)
DECL|macro|__NR_io_destroy
mdefine_line|#define __NR_io_destroy&t;&t;&t;(__NR_SYSCALL_BASE+244)
DECL|macro|__NR_io_getevents
mdefine_line|#define __NR_io_getevents&t;&t;(__NR_SYSCALL_BASE+245)
DECL|macro|__NR_io_submit
mdefine_line|#define __NR_io_submit&t;&t;&t;(__NR_SYSCALL_BASE+246)
DECL|macro|__NR_io_cancel
mdefine_line|#define __NR_io_cancel&t;&t;&t;(__NR_SYSCALL_BASE+247)
DECL|macro|__NR_exit_group
mdefine_line|#define __NR_exit_group&t;&t;&t;(__NR_SYSCALL_BASE+248)
DECL|macro|__NR_lookup_dcookie
mdefine_line|#define __NR_lookup_dcookie&t;&t;(__NR_SYSCALL_BASE+249)
DECL|macro|__NR_epoll_create
mdefine_line|#define __NR_epoll_create&t;&t;(__NR_SYSCALL_BASE+250)
DECL|macro|__NR_epoll_ctl
mdefine_line|#define __NR_epoll_ctl&t;&t;&t;(__NR_SYSCALL_BASE+251)
DECL|macro|__NR_epoll_wait
mdefine_line|#define __NR_epoll_wait&t;&t;&t;(__NR_SYSCALL_BASE+252)
DECL|macro|__NR_remap_file_pages
mdefine_line|#define __NR_remap_file_pages&t;&t;(__NR_SYSCALL_BASE+253)
multiline_comment|/* 254 for set_thread_area */
multiline_comment|/* 255 for get_thread_area */
multiline_comment|/* 256 for set_tid_address */
DECL|macro|__NR_timer_create
mdefine_line|#define __NR_timer_create&t;&t;(__NR_SYSCALL_BASE+257)
DECL|macro|__NR_timer_settime
mdefine_line|#define __NR_timer_settime&t;&t;(__NR_SYSCALL_BASE+258)
DECL|macro|__NR_timer_gettime
mdefine_line|#define __NR_timer_gettime&t;&t;(__NR_SYSCALL_BASE+259)
DECL|macro|__NR_timer_getoverrun
mdefine_line|#define __NR_timer_getoverrun&t;&t;(__NR_SYSCALL_BASE+260)
DECL|macro|__NR_timer_delete
mdefine_line|#define __NR_timer_delete&t;&t;(__NR_SYSCALL_BASE+261)
DECL|macro|__NR_clock_settime
mdefine_line|#define __NR_clock_settime&t;&t;(__NR_SYSCALL_BASE+262)
DECL|macro|__NR_clock_gettime
mdefine_line|#define __NR_clock_gettime&t;&t;(__NR_SYSCALL_BASE+263)
DECL|macro|__NR_clock_getres
mdefine_line|#define __NR_clock_getres&t;&t;(__NR_SYSCALL_BASE+264)
DECL|macro|__NR_clock_nanosleep
mdefine_line|#define __NR_clock_nanosleep&t;&t;(__NR_SYSCALL_BASE+265)
DECL|macro|__NR_statfs64
mdefine_line|#define __NR_statfs64&t;&t;&t;(__NR_SYSCALL_BASE+266)
DECL|macro|__NR_fstatfs64
mdefine_line|#define __NR_fstatfs64&t;&t;&t;(__NR_SYSCALL_BASE+267)
DECL|macro|__NR_tgkill
mdefine_line|#define __NR_tgkill&t;&t;&t;(__NR_SYSCALL_BASE+268)
DECL|macro|__NR_utimes
mdefine_line|#define __NR_utimes&t;&t;&t;(__NR_SYSCALL_BASE+269)
DECL|macro|__NR_fadvise64_64
mdefine_line|#define __NR_fadvise64_64&t;&t;(__NR_SYSCALL_BASE+270)
DECL|macro|__NR_pciconfig_iobase
mdefine_line|#define __NR_pciconfig_iobase&t;&t;(__NR_SYSCALL_BASE+271)
DECL|macro|__NR_pciconfig_read
mdefine_line|#define __NR_pciconfig_read&t;&t;(__NR_SYSCALL_BASE+272)
DECL|macro|__NR_pciconfig_write
mdefine_line|#define __NR_pciconfig_write&t;&t;(__NR_SYSCALL_BASE+273)
DECL|macro|__NR_mq_open
mdefine_line|#define __NR_mq_open&t;&t;&t;(__NR_SYSCALL_BASE+274)
DECL|macro|__NR_mq_unlink
mdefine_line|#define __NR_mq_unlink&t;&t;&t;(__NR_SYSCALL_BASE+275)
DECL|macro|__NR_mq_timedsend
mdefine_line|#define __NR_mq_timedsend&t;&t;(__NR_SYSCALL_BASE+276)
DECL|macro|__NR_mq_timedreceive
mdefine_line|#define __NR_mq_timedreceive&t;&t;(__NR_SYSCALL_BASE+277)
DECL|macro|__NR_mq_notify
mdefine_line|#define __NR_mq_notify&t;&t;&t;(__NR_SYSCALL_BASE+278)
DECL|macro|__NR_mq_getsetattr
mdefine_line|#define __NR_mq_getsetattr&t;&t;(__NR_SYSCALL_BASE+279)
DECL|macro|__NR_waitid
mdefine_line|#define __NR_waitid&t;&t;&t;(__NR_SYSCALL_BASE+280)
multiline_comment|/*&n; * The following SWIs are ARM private. FIXME - make appropriate for arm26&n; */
DECL|macro|__ARM_NR_BASE
mdefine_line|#define __ARM_NR_BASE&t;&t;&t;(__NR_SYSCALL_BASE+0x0f0000)
DECL|macro|__ARM_NR_breakpoint
mdefine_line|#define __ARM_NR_breakpoint&t;&t;(__ARM_NR_BASE+1)
DECL|macro|__ARM_NR_cacheflush
mdefine_line|#define __ARM_NR_cacheflush&t;&t;(__ARM_NR_BASE+2)
DECL|macro|__ARM_NR_usr26
mdefine_line|#define __ARM_NR_usr26&t;&t;&t;(__ARM_NR_BASE+3)
DECL|macro|__sys2
mdefine_line|#define __sys2(x) #x
DECL|macro|__sys1
mdefine_line|#define __sys1(x) __sys2(x)
macro_line|#ifndef __syscall
DECL|macro|__syscall
mdefine_line|#define __syscall(name) &quot;swi&bslash;t&quot; __sys1(__NR_##name) &quot;&quot;
macro_line|#endif
DECL|macro|__syscall_return
mdefine_line|#define __syscall_return(type, res)&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if ((unsigned long)(res) &gt;= (unsigned long)(-125)) {&t;&t;&bslash;&n;&t;&t;errno = -(res);&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;res = -1;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;return (type) (res);&t;&t;&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|_syscall0
mdefine_line|#define _syscall0(type,name)&t;&t;&t;&t;&t;&t;&bslash;&n;type name(void) {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  register long __res_r0 __asm__(&quot;r0&quot;);&t;&t;&t;&t;&t;&bslash;&n;  long __res;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  __asm__ __volatile__ (&t;&t;&t;&t;&t;&t;&bslash;&n;  __syscall(name)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;=r&quot; (__res_r0)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;:&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;lr&quot;);&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  __res = __res_r0;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  __syscall_return(type,__res);&t;&t;&t;&t;&t;&t;&bslash;&n;}
DECL|macro|_syscall1
mdefine_line|#define _syscall1(type,name,type1,arg1) &t;&t;&t;&t;&bslash;&n;type name(type1 arg1) { &t;&t;&t;&t;&t;&t;&bslash;&n;  register long __r0 __asm__(&quot;r0&quot;) = (long)arg1;&t;&t;&t;&bslash;&n;  register long __res_r0 __asm__(&quot;r0&quot;);&t;&t;&t;&t;&t;&bslash;&n;  long __res;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  __asm__ __volatile__ (&t;&t;&t;&t;&t;&t;&bslash;&n;  __syscall(name)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;=r&quot; (__res_r0)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;r&quot; (__r0)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;lr&quot;);&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  __res = __res_r0;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  __syscall_return(type,__res);&t;&t;&t;&t;&t;&t;&bslash;&n;}
DECL|macro|_syscall2
mdefine_line|#define _syscall2(type,name,type1,arg1,type2,arg2)&t;&t;&t;&bslash;&n;type name(type1 arg1,type2 arg2) {&t;&t;&t;&t;&t;&bslash;&n;  register long __r0 __asm__(&quot;r0&quot;) = (long)arg1;&t;&t;&t;&bslash;&n;  register long __r1 __asm__(&quot;r1&quot;) = (long)arg2;&t;&t;&t;&bslash;&n;  register long __res_r0 __asm__(&quot;r0&quot;);&t;&t;&t;&t;&t;&bslash;&n;  long __res;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  __asm__ __volatile__ (&t;&t;&t;&t;&t;&t;&bslash;&n;  __syscall(name)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;=r&quot; (__res_r0)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;r&quot; (__r0),&quot;r&quot; (__r1) &t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;lr&quot;);&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  __res = __res_r0;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  __syscall_return(type,__res);&t;&t;&t;&t;&t;&t;&bslash;&n;}
DECL|macro|_syscall3
mdefine_line|#define _syscall3(type,name,type1,arg1,type2,arg2,type3,arg3)&t;&t;&bslash;&n;type name(type1 arg1,type2 arg2,type3 arg3) {&t;&t;&t;&t;&bslash;&n;  register long __r0 __asm__(&quot;r0&quot;) = (long)arg1;&t;&t;&t;&bslash;&n;  register long __r1 __asm__(&quot;r1&quot;) = (long)arg2;&t;&t;&t;&bslash;&n;  register long __r2 __asm__(&quot;r2&quot;) = (long)arg3;&t;&t;&t;&bslash;&n;  register long __res_r0 __asm__(&quot;r0&quot;);&t;&t;&t;&t;&t;&bslash;&n;  long __res;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  __asm__ __volatile__ (&t;&t;&t;&t;&t;&t;&bslash;&n;  __syscall(name)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;=r&quot; (__res_r0)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;r&quot; (__r0),&quot;r&quot; (__r1),&quot;r&quot; (__r2)&t;&t;&t;&t;&bslash;&n;&t;: &quot;lr&quot;);&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  __res = __res_r0;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  __syscall_return(type,__res);&t;&t;&t;&t;&t;&t;&bslash;&n;}
DECL|macro|_syscall4
mdefine_line|#define _syscall4(type,name,type1,arg1,type2,arg2,type3,arg3,type4,arg4)&bslash;&n;type name(type1 arg1, type2 arg2, type3 arg3, type4 arg4) {&t;&t;&bslash;&n;  register long __r0 __asm__(&quot;r0&quot;) = (long)arg1;&t;&t;&t;&bslash;&n;  register long __r1 __asm__(&quot;r1&quot;) = (long)arg2;&t;&t;&t;&bslash;&n;  register long __r2 __asm__(&quot;r2&quot;) = (long)arg3;&t;&t;&t;&bslash;&n;  register long __r3 __asm__(&quot;r3&quot;) = (long)arg4;&t;&t;&t;&bslash;&n;  register long __res_r0 __asm__(&quot;r0&quot;);&t;&t;&t;&t;&t;&bslash;&n;  long __res;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  __asm__ __volatile__ (&t;&t;&t;&t;&t;&t;&bslash;&n;  __syscall(name)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;=r&quot; (__res_r0)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;r&quot; (__r0),&quot;r&quot; (__r1),&quot;r&quot; (__r2),&quot;r&quot; (__r3)&t;&t;&t;&bslash;&n;&t;: &quot;lr&quot;);&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  __res = __res_r0;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  __syscall_return(type,__res);&t;&t;&t;&t;&t;&t;&bslash;&n;}
DECL|macro|_syscall5
mdefine_line|#define _syscall5(type,name,type1,arg1,type2,arg2,type3,arg3,type4,arg4,type5,arg5)&t;&bslash;&n;type name(type1 arg1, type2 arg2, type3 arg3, type4 arg4, type5 arg5) {&t;&bslash;&n;  register long __r0 __asm__(&quot;r0&quot;) = (long)arg1;&t;&t;&t;&bslash;&n;  register long __r1 __asm__(&quot;r1&quot;) = (long)arg2;&t;&t;&t;&bslash;&n;  register long __r2 __asm__(&quot;r2&quot;) = (long)arg3;&t;&t;&t;&bslash;&n;  register long __r3 __asm__(&quot;r3&quot;) = (long)arg4;&t;&t;&t;&bslash;&n;  register long __r4 __asm__(&quot;r4&quot;) = (long)arg5;&t;&t;&t;&bslash;&n;  register long __res_r0 __asm__(&quot;r0&quot;);&t;&t;&t;&t;&t;&bslash;&n;  long __res;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  __asm__ __volatile__ (&t;&t;&t;&t;&t;&t;&bslash;&n;  __syscall(name)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;=r&quot; (__res_r0)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;r&quot; (__r0),&quot;r&quot; (__r1),&quot;r&quot; (__r2),&quot;r&quot; (__r3),&quot;r&quot; (__r4)&t;&bslash;&n;&t;: &quot;lr&quot;);&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  __res = __res_r0;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  __syscall_return(type,__res);&t;&t;&t;&t;&t;&t;&bslash;&n;}
DECL|macro|_syscall6
mdefine_line|#define _syscall6(type,name,type1,arg1,type2,arg2,type3,arg3,type4,arg4,type5,arg5,type6,arg6)&t;&bslash;&n;type name(type1 arg1, type2 arg2, type3 arg3, type4 arg4, type5 arg5, type6 arg6) {&t;&bslash;&n;  register long __r0 __asm__(&quot;r0&quot;) = (long)arg1;&t;&t;&t;&bslash;&n;  register long __r1 __asm__(&quot;r1&quot;) = (long)arg2;&t;&t;&t;&bslash;&n;  register long __r2 __asm__(&quot;r2&quot;) = (long)arg3;&t;&t;&t;&bslash;&n;  register long __r3 __asm__(&quot;r3&quot;) = (long)arg4;&t;&t;&t;&bslash;&n;  register long __r4 __asm__(&quot;r4&quot;) = (long)arg5;&t;&t;&t;&bslash;&n;  register long __r5 __asm__(&quot;r5&quot;) = (long)arg6;&t;&t;&t;&bslash;&n;  register long __res_r0 __asm__(&quot;r0&quot;);&t;&t;&t;&t;&t;&bslash;&n;  long __res;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  __asm__ __volatile__ (&t;&t;&t;&t;&t;&t;&bslash;&n;  __syscall(name)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;=r&quot; (__res_r0)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;r&quot; (__r0),&quot;r&quot; (__r1),&quot;r&quot; (__r2),&quot;r&quot; (__r3), &quot;r&quot; (__r4),&quot;r&quot; (__r5)&t;&t;&bslash;&n;&t;: &quot;lr&quot;);&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  __res = __res_r0;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  __syscall_return(type,__res);&t;&t;&t;&t;&t;&t;&bslash;&n;}
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
DECL|macro|__ARCH_WANT_SYS_TIME
mdefine_line|#define __ARCH_WANT_SYS_TIME
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
macro_line|#endif
macro_line|#ifdef __KERNEL_SYSCALLS__
macro_line|#include &lt;linux/compiler.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/syscalls.h&gt;
r_extern
r_int
id|execve
c_func
(paren
r_const
r_char
op_star
id|file
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
)paren
suffix:semicolon
r_struct
id|pt_regs
suffix:semicolon
id|asmlinkage
r_int
id|sys_execve
c_func
(paren
r_char
op_star
id|filenamei
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
id|asmlinkage
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
id|newsp
comma
r_struct
id|pt_regs
op_star
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
op_star
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
op_star
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
macro_line|#endif /* __ASM_ARM_UNISTD_H */
eof
