multiline_comment|/*&n; *  linux/include/asm-arm/unistd.h&n; *&n; *  Copyright (C) 2001 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; * Please forward _all_ changes to this file to rmk@arm.linux.org.uk,&n; * no matter what the change is.  Thanks!&n; */
macro_line|#ifndef __ASM_ARM_UNISTD_H
DECL|macro|__ASM_ARM_UNISTD_H
mdefine_line|#define __ASM_ARM_UNISTD_H
DECL|macro|__NR_SYSCALL_BASE
mdefine_line|#define __NR_SYSCALL_BASE&t;0x900000
multiline_comment|/*&n; * This file contains the system call numbers.&n; */
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
DECL|macro|__NR_waitpid
mdefine_line|#define __NR_waitpid&t;&t;&t;(__NR_SYSCALL_BASE+  7)
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
DECL|macro|__NR_break
mdefine_line|#define __NR_break&t;&t;&t;(__NR_SYSCALL_BASE+ 17)
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
DECL|macro|__NR_pause
mdefine_line|#define __NR_pause&t;&t;&t;(__NR_SYSCALL_BASE+ 29)
DECL|macro|__NR_utime
mdefine_line|#define __NR_utime&t;&t;&t;(__NR_SYSCALL_BASE+ 30)
DECL|macro|__NR_stty
mdefine_line|#define __NR_stty&t;&t;&t;(__NR_SYSCALL_BASE+ 31)
DECL|macro|__NR_gtty
mdefine_line|#define __NR_gtty&t;&t;&t;(__NR_SYSCALL_BASE+ 32)
DECL|macro|__NR_access
mdefine_line|#define __NR_access&t;&t;&t;(__NR_SYSCALL_BASE+ 33)
DECL|macro|__NR_nice
mdefine_line|#define __NR_nice&t;&t;&t;(__NR_SYSCALL_BASE+ 34)
DECL|macro|__NR_ftime
mdefine_line|#define __NR_ftime&t;&t;&t;(__NR_SYSCALL_BASE+ 35)
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
DECL|macro|__NR_prof
mdefine_line|#define __NR_prof&t;&t;&t;(__NR_SYSCALL_BASE+ 44)
DECL|macro|__NR_brk
mdefine_line|#define __NR_brk&t;&t;&t;(__NR_SYSCALL_BASE+ 45)
DECL|macro|__NR_setgid
mdefine_line|#define __NR_setgid&t;&t;&t;(__NR_SYSCALL_BASE+ 46)
DECL|macro|__NR_getgid
mdefine_line|#define __NR_getgid&t;&t;&t;(__NR_SYSCALL_BASE+ 47)
DECL|macro|__NR_signal
mdefine_line|#define __NR_signal&t;&t;&t;(__NR_SYSCALL_BASE+ 48)
DECL|macro|__NR_geteuid
mdefine_line|#define __NR_geteuid&t;&t;&t;(__NR_SYSCALL_BASE+ 49)
DECL|macro|__NR_getegid
mdefine_line|#define __NR_getegid&t;&t;&t;(__NR_SYSCALL_BASE+ 50)
DECL|macro|__NR_acct
mdefine_line|#define __NR_acct&t;&t;&t;(__NR_SYSCALL_BASE+ 51)
DECL|macro|__NR_umount2
mdefine_line|#define __NR_umount2&t;&t;&t;(__NR_SYSCALL_BASE+ 52)
DECL|macro|__NR_lock
mdefine_line|#define __NR_lock&t;&t;&t;(__NR_SYSCALL_BASE+ 53)
DECL|macro|__NR_ioctl
mdefine_line|#define __NR_ioctl&t;&t;&t;(__NR_SYSCALL_BASE+ 54)
DECL|macro|__NR_fcntl
mdefine_line|#define __NR_fcntl&t;&t;&t;(__NR_SYSCALL_BASE+ 55)
DECL|macro|__NR_mpx
mdefine_line|#define __NR_mpx&t;&t;&t;(__NR_SYSCALL_BASE+ 56)
DECL|macro|__NR_setpgid
mdefine_line|#define __NR_setpgid&t;&t;&t;(__NR_SYSCALL_BASE+ 57)
DECL|macro|__NR_ulimit
mdefine_line|#define __NR_ulimit&t;&t;&t;(__NR_SYSCALL_BASE+ 58)
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
DECL|macro|__NR_sgetmask
mdefine_line|#define __NR_sgetmask&t;&t;&t;(__NR_SYSCALL_BASE+ 68)
DECL|macro|__NR_ssetmask
mdefine_line|#define __NR_ssetmask&t;&t;&t;(__NR_SYSCALL_BASE+ 69)
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
DECL|macro|__NR_profil
mdefine_line|#define __NR_profil&t;&t;&t;(__NR_SYSCALL_BASE+ 98)
DECL|macro|__NR_statfs
mdefine_line|#define __NR_statfs&t;&t;&t;(__NR_SYSCALL_BASE+ 99)
DECL|macro|__NR_fstatfs
mdefine_line|#define __NR_fstatfs&t;&t;&t;(__NR_SYSCALL_BASE+100)
DECL|macro|__NR_ioperm
mdefine_line|#define __NR_ioperm&t;&t;&t;(__NR_SYSCALL_BASE+101)
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
DECL|macro|__NR_vhangup
mdefine_line|#define __NR_vhangup&t;&t;&t;(__NR_SYSCALL_BASE+111)
DECL|macro|__NR_idle
mdefine_line|#define __NR_idle&t;&t;&t;(__NR_SYSCALL_BASE+112)
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
DECL|macro|__NR_modify_ldt
mdefine_line|#define __NR_modify_ldt&t;&t;&t;(__NR_SYSCALL_BASE+123)
DECL|macro|__NR_adjtimex
mdefine_line|#define __NR_adjtimex&t;&t;&t;(__NR_SYSCALL_BASE+124)
DECL|macro|__NR_mprotect
mdefine_line|#define __NR_mprotect&t;&t;&t;(__NR_SYSCALL_BASE+125)
DECL|macro|__NR_sigprocmask
mdefine_line|#define __NR_sigprocmask&t;&t;(__NR_SYSCALL_BASE+126)
DECL|macro|__NR_create_module
mdefine_line|#define __NR_create_module&t;&t;(__NR_SYSCALL_BASE+127)
DECL|macro|__NR_init_module
mdefine_line|#define __NR_init_module&t;&t;(__NR_SYSCALL_BASE+128)
DECL|macro|__NR_delete_module
mdefine_line|#define __NR_delete_module&t;&t;(__NR_SYSCALL_BASE+129)
DECL|macro|__NR_get_kernel_syms
mdefine_line|#define __NR_get_kernel_syms&t;&t;(__NR_SYSCALL_BASE+130)
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
DECL|macro|__NR_afs_syscall
mdefine_line|#define __NR_afs_syscall&t;&t;(__NR_SYSCALL_BASE+137) /* Syscall for Andrew File System */
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
DECL|macro|__NR_vm86
mdefine_line|#define __NR_vm86&t;&t;&t;(__NR_SYSCALL_BASE+166)
DECL|macro|__NR_query_module
mdefine_line|#define __NR_query_module&t;&t;(__NR_SYSCALL_BASE+167)
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
DECL|macro|__NR_pread
mdefine_line|#define __NR_pread&t;&t;&t;(__NR_SYSCALL_BASE+180)
DECL|macro|__NR_pwrite
mdefine_line|#define __NR_pwrite&t;&t;&t;(__NR_SYSCALL_BASE+181)
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
DECL|macro|__NR_security
mdefine_line|#define __NR_security&t;&t;&t;(__NR_SYSCALL_BASE+223)
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
mdefine_line|#define __NR_tkill&t;&t;&t;(__NR_SYSCALL_BASE+238
multiline_comment|/*&n; * The following SWIs are ARM private.&n; */
DECL|macro|__ARM_NR_BASE
mdefine_line|#define __ARM_NR_BASE&t;&t;&t;(__NR_SYSCALL_BASE+0x0f0000)
DECL|macro|__ARM_NR_breakpoint
mdefine_line|#define __ARM_NR_breakpoint&t;&t;(__ARM_NR_BASE+1)
DECL|macro|__ARM_NR_cacheflush
mdefine_line|#define __ARM_NR_cacheflush&t;&t;(__ARM_NR_BASE+2)
DECL|macro|__ARM_NR_usr26
mdefine_line|#define __ARM_NR_usr26&t;&t;&t;(__ARM_NR_BASE+3)
DECL|macro|__ARM_NR_usr32
mdefine_line|#define __ARM_NR_usr32&t;&t;&t;(__ARM_NR_BASE+4)
DECL|macro|__sys2
mdefine_line|#define __sys2(x) #x
DECL|macro|__sys1
mdefine_line|#define __sys1(x) __sys2(x)
macro_line|#ifndef __syscall
DECL|macro|__syscall
mdefine_line|#define __syscall(name) &quot;swi&bslash;t&quot; __sys1(__NR_##name) &quot;&bslash;n&bslash;t&quot;
macro_line|#endif
DECL|macro|__syscall_return
mdefine_line|#define __syscall_return(type, res)&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if ((unsigned long)(res) &gt;= (unsigned long)(-125)) {&t;&t;&bslash;&n;&t;&t;errno = -(res);&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;res = -1;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;return (type) (res);&t;&t;&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|_syscall0
mdefine_line|#define _syscall0(type,name)&t;&t;&t;&t;&t;&t;&bslash;&n;type name(void) {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  long __res;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  __asm__ __volatile__ (&t;&t;&t;&t;&t;&t;&bslash;&n;  __syscall(name)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  &quot;mov %0,r0&quot;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  :&quot;=r&quot; (__res) : : &quot;r0&quot;,&quot;lr&quot;);&t;&t;&t;&t;&t;&t;&bslash;&n;  __syscall_return(type,__res);&t;&t;&t;&t;&t;&t;&bslash;&n;}
DECL|macro|_syscall1
mdefine_line|#define _syscall1(type,name,type1,arg1)&t;&t;&t;&t;&t;&bslash;&n;type name(type1 arg1) {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  long __res;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  __asm__ __volatile__ (&t;&t;&t;&t;&t;&t;&bslash;&n;  &quot;mov&bslash;tr0,%1&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  __syscall(name)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  &quot;mov %0,r0&quot;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;        : &quot;=r&quot; (__res)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;        : &quot;r&quot; ((long)(arg1))&t;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;r0&quot;,&quot;lr&quot;);&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  __syscall_return(type,__res);&t;&t;&t;&t;&t;&t;&bslash;&n;}
DECL|macro|_syscall2
mdefine_line|#define _syscall2(type,name,type1,arg1,type2,arg2)&t;&t;&t;&bslash;&n;type name(type1 arg1,type2 arg2) {&t;&t;&t;&t;&t;&bslash;&n;  long __res;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  __asm__ __volatile__ (&t;&t;&t;&t;&t;&t;&bslash;&n;  &quot;mov&bslash;tr0,%1&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  &quot;mov&bslash;tr1,%2&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  __syscall(name)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  &quot;mov&bslash;t%0,r0&quot;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;        : &quot;=r&quot; (__res)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;        : &quot;r&quot; ((long)(arg1)),&quot;r&quot; ((long)(arg2))&t;&t;&t;&t;&bslash;&n;&t;: &quot;r0&quot;,&quot;r1&quot;,&quot;lr&quot;);&t;&t;&t;&t;&t;&t;&bslash;&n;  __syscall_return(type,__res);&t;&t;&t;&t;&t;&t;&bslash;&n;}
DECL|macro|_syscall3
mdefine_line|#define _syscall3(type,name,type1,arg1,type2,arg2,type3,arg3)&t;&t;&bslash;&n;type name(type1 arg1,type2 arg2,type3 arg3) {&t;&t;&t;&t;&bslash;&n;  long __res;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  __asm__ __volatile__ (&t;&t;&t;&t;&t;&t;&bslash;&n;  &quot;mov&bslash;tr0,%1&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  &quot;mov&bslash;tr1,%2&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  &quot;mov&bslash;tr2,%3&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  __syscall(name)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  &quot;mov&bslash;t%0,r0&quot;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;        : &quot;=r&quot; (__res)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;        : &quot;r&quot; ((long)(arg1)),&quot;r&quot; ((long)(arg2)),&quot;r&quot; ((long)(arg3))&t;&bslash;&n;        : &quot;r0&quot;,&quot;r1&quot;,&quot;r2&quot;,&quot;lr&quot;);&t;&t;&t;&t;&t;&t;&bslash;&n;  __syscall_return(type,__res);&t;&t;&t;&t;&t;&t;&bslash;&n;}
DECL|macro|_syscall4
mdefine_line|#define _syscall4(type,name,type1,arg1,type2,arg2,type3,arg3,type4,arg4)&t;&t;&bslash;&n;type name(type1 arg1, type2 arg2, type3 arg3, type4 arg4) {&t;&t;&t;&t;&bslash;&n;  long __res;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  __asm__ __volatile__ (&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  &quot;mov&bslash;tr0,%1&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  &quot;mov&bslash;tr1,%2&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  &quot;mov&bslash;tr2,%3&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  &quot;mov&bslash;tr3,%4&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  __syscall(name)&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  &quot;mov&bslash;t%0,r0&quot;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  &t;: &quot;=r&quot; (__res)&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  &t;: &quot;r&quot; ((long)(arg1)),&quot;r&quot; ((long)(arg2)),&quot;r&quot; ((long)(arg3)),&quot;r&quot; ((long)(arg4))&t;&bslash;&n;  &t;: &quot;r0&quot;,&quot;r1&quot;,&quot;r2&quot;,&quot;r3&quot;,&quot;lr&quot;);&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  __syscall_return(type,__res);&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;}
DECL|macro|_syscall5
mdefine_line|#define _syscall5(type,name,type1,arg1,type2,arg2,type3,arg3,type4,arg4,type5,arg5)&t;&bslash;&n;type name(type1 arg1, type2 arg2, type3 arg3, type4 arg4, type5 arg5) {&t;&t;&t;&bslash;&n;  long __res;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  __asm__ __volatile__ (&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  &quot;mov&bslash;tr0,%1&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  &quot;mov&bslash;tr1,%2&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  &quot;mov&bslash;tr2,%3&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  &quot;mov&bslash;tr3,%4&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  &quot;mov&bslash;tr4,%5&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  __syscall(name)&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  &quot;mov&bslash;t%0,r0&quot;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  &t;: &quot;=r&quot; (__res)&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  &t;: &quot;r&quot; ((long)(arg1)),&quot;r&quot; ((long)(arg2)),&quot;r&quot; ((long)(arg3)),&quot;r&quot; ((long)(arg4)),&t;&bslash;&n;&t;  &quot;r&quot; ((long)(arg5))&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;r0&quot;,&quot;r1&quot;,&quot;r2&quot;,&quot;r3&quot;,&quot;r4&quot;,&quot;lr&quot;);&t;&t;&t;&t;&t;&t;&bslash;&n;  __syscall_return(type,__res);&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;}
macro_line|#ifdef __KERNEL_SYSCALLS__
r_struct
id|rusage
suffix:semicolon
id|asmlinkage
r_int
id|sys_wait4
c_func
(paren
id|pid_t
id|pid
comma
r_int
r_int
op_star
id|stat_addr
comma
r_int
id|options
comma
r_struct
id|rusage
op_star
id|ru
)paren
suffix:semicolon
DECL|function|idle
r_static
r_inline
r_int
id|idle
c_func
(paren
r_void
)paren
(brace
r_extern
r_int
id|sys_idle
c_func
(paren
r_void
)paren
suffix:semicolon
r_return
id|sys_idle
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|pause
r_static
r_inline
r_int
id|pause
c_func
(paren
r_void
)paren
(brace
r_extern
r_int
id|sys_pause
c_func
(paren
r_void
)paren
suffix:semicolon
r_return
id|sys_pause
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|sync
r_static
r_inline
r_int
id|sync
c_func
(paren
r_void
)paren
(brace
r_extern
r_int
id|sys_sync
c_func
(paren
r_void
)paren
suffix:semicolon
r_return
id|sys_sync
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|setsid
r_static
r_inline
id|pid_t
id|setsid
c_func
(paren
r_void
)paren
(brace
r_extern
r_int
id|sys_setsid
c_func
(paren
r_void
)paren
suffix:semicolon
r_return
id|sys_setsid
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|write
r_static
r_inline
r_int
id|write
c_func
(paren
r_int
id|fd
comma
r_const
r_char
op_star
id|buf
comma
id|off_t
id|count
)paren
(brace
r_extern
r_int
id|sys_write
c_func
(paren
r_int
comma
r_const
r_char
op_star
comma
r_int
)paren
suffix:semicolon
r_return
id|sys_write
c_func
(paren
id|fd
comma
id|buf
comma
id|count
)paren
suffix:semicolon
)brace
DECL|function|read
r_static
r_inline
r_int
id|read
c_func
(paren
r_int
id|fd
comma
r_char
op_star
id|buf
comma
id|off_t
id|count
)paren
(brace
r_extern
r_int
id|sys_read
c_func
(paren
r_int
comma
r_char
op_star
comma
r_int
)paren
suffix:semicolon
r_return
id|sys_read
c_func
(paren
id|fd
comma
id|buf
comma
id|count
)paren
suffix:semicolon
)brace
DECL|function|lseek
r_static
r_inline
id|off_t
id|lseek
c_func
(paren
r_int
id|fd
comma
id|off_t
id|offset
comma
r_int
id|count
)paren
(brace
r_extern
id|off_t
id|sys_lseek
c_func
(paren
r_int
comma
id|off_t
comma
r_int
)paren
suffix:semicolon
r_return
id|sys_lseek
c_func
(paren
id|fd
comma
id|offset
comma
id|count
)paren
suffix:semicolon
)brace
DECL|function|dup
r_static
r_inline
r_int
id|dup
c_func
(paren
r_int
id|fd
)paren
(brace
r_extern
r_int
id|sys_dup
c_func
(paren
r_int
)paren
suffix:semicolon
r_return
id|sys_dup
c_func
(paren
id|fd
)paren
suffix:semicolon
)brace
DECL|function|open
r_static
r_inline
r_int
id|open
c_func
(paren
r_const
r_char
op_star
id|file
comma
r_int
id|flag
comma
r_int
id|mode
)paren
(brace
r_extern
r_int
id|sys_open
c_func
(paren
r_const
r_char
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_return
id|sys_open
c_func
(paren
id|file
comma
id|flag
comma
id|mode
)paren
suffix:semicolon
)brace
DECL|function|close
r_static
r_inline
r_int
id|close
c_func
(paren
r_int
id|fd
)paren
(brace
r_extern
r_int
id|sys_close
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_return
id|sys_close
c_func
(paren
id|fd
)paren
suffix:semicolon
)brace
DECL|function|_exit
r_static
r_inline
r_int
id|_exit
c_func
(paren
r_int
id|exitcode
)paren
(brace
r_extern
r_int
id|sys_exit
c_func
(paren
r_int
)paren
id|__attribute__
c_func
(paren
(paren
id|noreturn
)paren
)paren
suffix:semicolon
r_return
id|sys_exit
c_func
(paren
id|exitcode
)paren
suffix:semicolon
)brace
DECL|function|waitpid
r_static
r_inline
id|pid_t
id|waitpid
c_func
(paren
id|pid_t
id|pid
comma
r_int
op_star
id|wait_stat
comma
r_int
id|options
)paren
(brace
r_return
id|sys_wait4
c_func
(paren
(paren
r_int
)paren
id|pid
comma
id|wait_stat
comma
id|options
comma
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|function|delete_module
r_static
r_inline
r_int
id|delete_module
c_func
(paren
r_const
r_char
op_star
id|name
)paren
(brace
r_extern
r_int
id|sys_delete_module
c_func
(paren
r_const
r_char
op_star
id|name
)paren
suffix:semicolon
r_return
id|sys_delete_module
c_func
(paren
id|name
)paren
suffix:semicolon
)brace
DECL|function|wait
r_static
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
id|sys_wait4
c_func
(paren
op_minus
l_int|1
comma
id|wait_stat
comma
l_int|0
comma
l_int|NULL
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * The following two can&squot;t be eliminated yet - they rely on&n; * specific conditions.&n; */
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
suffix:semicolon
macro_line|#endif
macro_line|#endif /* __ASM_ARM_UNISTD_H */
eof
