multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1995, 96, 97, 98, 99, 2000 by Ralf Baechle&n; *&n; * Changed system calls macros _syscall5 - _syscall7 to push args 5 to 7 onto&n; * the stack. Robin Farine for ACN S.A, Copyright (C) 1996 by ACN S.A&n; */
macro_line|#ifndef _ASM_UNISTD_H
DECL|macro|_ASM_UNISTD_H
mdefine_line|#define _ASM_UNISTD_H
DECL|macro|__NR_Linux
mdefine_line|#define __NR_Linux&t;&t;&t;4000
DECL|macro|__NR_syscall
mdefine_line|#define __NR_syscall&t;&t;&t;(__NR_Linux +   0)
DECL|macro|__NR_exit
mdefine_line|#define __NR_exit&t;&t;&t;(__NR_Linux +   1)
DECL|macro|__NR_fork
mdefine_line|#define __NR_fork&t;&t;&t;(__NR_Linux +   2)
DECL|macro|__NR_read
mdefine_line|#define __NR_read&t;&t;&t;(__NR_Linux +   3)
DECL|macro|__NR_write
mdefine_line|#define __NR_write&t;&t;&t;(__NR_Linux +   4)
DECL|macro|__NR_open
mdefine_line|#define __NR_open&t;&t;&t;(__NR_Linux +   5)
DECL|macro|__NR_close
mdefine_line|#define __NR_close&t;&t;&t;(__NR_Linux +   6)
DECL|macro|__NR_waitpid
mdefine_line|#define __NR_waitpid&t;&t;&t;(__NR_Linux +   7)
DECL|macro|__NR_creat
mdefine_line|#define __NR_creat&t;&t;&t;(__NR_Linux +   8)
DECL|macro|__NR_link
mdefine_line|#define __NR_link&t;&t;&t;(__NR_Linux +   9)
DECL|macro|__NR_unlink
mdefine_line|#define __NR_unlink&t;&t;&t;(__NR_Linux +  10)
DECL|macro|__NR_execve
mdefine_line|#define __NR_execve&t;&t;&t;(__NR_Linux +  11)
DECL|macro|__NR_chdir
mdefine_line|#define __NR_chdir&t;&t;&t;(__NR_Linux +  12)
DECL|macro|__NR_time
mdefine_line|#define __NR_time&t;&t;&t;(__NR_Linux +  13)
DECL|macro|__NR_mknod
mdefine_line|#define __NR_mknod&t;&t;&t;(__NR_Linux +  14)
DECL|macro|__NR_chmod
mdefine_line|#define __NR_chmod&t;&t;&t;(__NR_Linux +  15)
DECL|macro|__NR_lchown
mdefine_line|#define __NR_lchown&t;&t;&t;(__NR_Linux +  16)
DECL|macro|__NR_break
mdefine_line|#define __NR_break&t;&t;&t;(__NR_Linux +  17)
DECL|macro|__NR_oldstat
mdefine_line|#define __NR_oldstat&t;&t;&t;(__NR_Linux +  18)
DECL|macro|__NR_lseek
mdefine_line|#define __NR_lseek&t;&t;&t;(__NR_Linux +  19)
DECL|macro|__NR_getpid
mdefine_line|#define __NR_getpid&t;&t;&t;(__NR_Linux +  20)
DECL|macro|__NR_mount
mdefine_line|#define __NR_mount&t;&t;&t;(__NR_Linux +  21)
DECL|macro|__NR_umount
mdefine_line|#define __NR_umount&t;&t;&t;(__NR_Linux +  22)
DECL|macro|__NR_setuid
mdefine_line|#define __NR_setuid&t;&t;&t;(__NR_Linux +  23)
DECL|macro|__NR_getuid
mdefine_line|#define __NR_getuid&t;&t;&t;(__NR_Linux +  24)
DECL|macro|__NR_stime
mdefine_line|#define __NR_stime&t;&t;&t;(__NR_Linux +  25)
DECL|macro|__NR_ptrace
mdefine_line|#define __NR_ptrace&t;&t;&t;(__NR_Linux +  26)
DECL|macro|__NR_alarm
mdefine_line|#define __NR_alarm&t;&t;&t;(__NR_Linux +  27)
DECL|macro|__NR_oldfstat
mdefine_line|#define __NR_oldfstat&t;&t;&t;(__NR_Linux +  28)
DECL|macro|__NR_pause
mdefine_line|#define __NR_pause&t;&t;&t;(__NR_Linux +  29)
DECL|macro|__NR_utime
mdefine_line|#define __NR_utime&t;&t;&t;(__NR_Linux +  30)
DECL|macro|__NR_stty
mdefine_line|#define __NR_stty&t;&t;&t;(__NR_Linux +  31)
DECL|macro|__NR_gtty
mdefine_line|#define __NR_gtty&t;&t;&t;(__NR_Linux +  32)
DECL|macro|__NR_access
mdefine_line|#define __NR_access&t;&t;&t;(__NR_Linux +  33)
DECL|macro|__NR_nice
mdefine_line|#define __NR_nice&t;&t;&t;(__NR_Linux +  34)
DECL|macro|__NR_ftime
mdefine_line|#define __NR_ftime&t;&t;&t;(__NR_Linux +  35)
DECL|macro|__NR_sync
mdefine_line|#define __NR_sync&t;&t;&t;(__NR_Linux +  36)
DECL|macro|__NR_kill
mdefine_line|#define __NR_kill&t;&t;&t;(__NR_Linux +  37)
DECL|macro|__NR_rename
mdefine_line|#define __NR_rename&t;&t;&t;(__NR_Linux +  38)
DECL|macro|__NR_mkdir
mdefine_line|#define __NR_mkdir&t;&t;&t;(__NR_Linux +  39)
DECL|macro|__NR_rmdir
mdefine_line|#define __NR_rmdir&t;&t;&t;(__NR_Linux +  40)
DECL|macro|__NR_dup
mdefine_line|#define __NR_dup&t;&t;&t;(__NR_Linux +  41)
DECL|macro|__NR_pipe
mdefine_line|#define __NR_pipe&t;&t;&t;(__NR_Linux +  42)
DECL|macro|__NR_times
mdefine_line|#define __NR_times&t;&t;&t;(__NR_Linux +  43)
DECL|macro|__NR_prof
mdefine_line|#define __NR_prof&t;&t;&t;(__NR_Linux +  44)
DECL|macro|__NR_brk
mdefine_line|#define __NR_brk&t;&t;&t;(__NR_Linux +  45)
DECL|macro|__NR_setgid
mdefine_line|#define __NR_setgid&t;&t;&t;(__NR_Linux +  46)
DECL|macro|__NR_getgid
mdefine_line|#define __NR_getgid&t;&t;&t;(__NR_Linux +  47)
DECL|macro|__NR_signal
mdefine_line|#define __NR_signal&t;&t;&t;(__NR_Linux +  48)
DECL|macro|__NR_geteuid
mdefine_line|#define __NR_geteuid&t;&t;&t;(__NR_Linux +  49)
DECL|macro|__NR_getegid
mdefine_line|#define __NR_getegid&t;&t;&t;(__NR_Linux +  50)
DECL|macro|__NR_acct
mdefine_line|#define __NR_acct&t;&t;&t;(__NR_Linux +  51)
DECL|macro|__NR_umount2
mdefine_line|#define __NR_umount2&t;&t;&t;(__NR_Linux +  52)
DECL|macro|__NR_lock
mdefine_line|#define __NR_lock&t;&t;&t;(__NR_Linux +  53)
DECL|macro|__NR_ioctl
mdefine_line|#define __NR_ioctl&t;&t;&t;(__NR_Linux +  54)
DECL|macro|__NR_fcntl
mdefine_line|#define __NR_fcntl&t;&t;&t;(__NR_Linux +  55)
DECL|macro|__NR_mpx
mdefine_line|#define __NR_mpx&t;&t;&t;(__NR_Linux +  56)
DECL|macro|__NR_setpgid
mdefine_line|#define __NR_setpgid&t;&t;&t;(__NR_Linux +  57)
DECL|macro|__NR_ulimit
mdefine_line|#define __NR_ulimit&t;&t;&t;(__NR_Linux +  58)
DECL|macro|__NR_unused59
mdefine_line|#define __NR_unused59&t;&t;&t;(__NR_Linux +  59)
DECL|macro|__NR_umask
mdefine_line|#define __NR_umask&t;&t;&t;(__NR_Linux +  60)
DECL|macro|__NR_chroot
mdefine_line|#define __NR_chroot&t;&t;&t;(__NR_Linux +  61)
DECL|macro|__NR_ustat
mdefine_line|#define __NR_ustat&t;&t;&t;(__NR_Linux +  62)
DECL|macro|__NR_dup2
mdefine_line|#define __NR_dup2&t;&t;&t;(__NR_Linux +  63)
DECL|macro|__NR_getppid
mdefine_line|#define __NR_getppid&t;&t;&t;(__NR_Linux +  64)
DECL|macro|__NR_getpgrp
mdefine_line|#define __NR_getpgrp&t;&t;&t;(__NR_Linux +  65)
DECL|macro|__NR_setsid
mdefine_line|#define __NR_setsid&t;&t;&t;(__NR_Linux +  66)
DECL|macro|__NR_sigaction
mdefine_line|#define __NR_sigaction&t;&t;&t;(__NR_Linux +  67)
DECL|macro|__NR_sgetmask
mdefine_line|#define __NR_sgetmask&t;&t;&t;(__NR_Linux +  68)
DECL|macro|__NR_ssetmask
mdefine_line|#define __NR_ssetmask&t;&t;&t;(__NR_Linux +  69)
DECL|macro|__NR_setreuid
mdefine_line|#define __NR_setreuid&t;&t;&t;(__NR_Linux +  70)
DECL|macro|__NR_setregid
mdefine_line|#define __NR_setregid&t;&t;&t;(__NR_Linux +  71)
DECL|macro|__NR_sigsuspend
mdefine_line|#define __NR_sigsuspend&t;&t;&t;(__NR_Linux +  72)
DECL|macro|__NR_sigpending
mdefine_line|#define __NR_sigpending&t;&t;&t;(__NR_Linux +  73)
DECL|macro|__NR_sethostname
mdefine_line|#define __NR_sethostname&t;&t;(__NR_Linux +  74)
DECL|macro|__NR_setrlimit
mdefine_line|#define __NR_setrlimit&t;&t;&t;(__NR_Linux +  75)
DECL|macro|__NR_getrlimit
mdefine_line|#define __NR_getrlimit&t;&t;&t;(__NR_Linux +  76)
DECL|macro|__NR_getrusage
mdefine_line|#define __NR_getrusage&t;&t;&t;(__NR_Linux +  77)
DECL|macro|__NR_gettimeofday
mdefine_line|#define __NR_gettimeofday&t;&t;(__NR_Linux +  78)
DECL|macro|__NR_settimeofday
mdefine_line|#define __NR_settimeofday&t;&t;(__NR_Linux +  79)
DECL|macro|__NR_getgroups
mdefine_line|#define __NR_getgroups&t;&t;&t;(__NR_Linux +  80)
DECL|macro|__NR_setgroups
mdefine_line|#define __NR_setgroups&t;&t;&t;(__NR_Linux +  81)
DECL|macro|__NR_reserved82
mdefine_line|#define __NR_reserved82&t;&t;&t;(__NR_Linux +  82)
DECL|macro|__NR_symlink
mdefine_line|#define __NR_symlink&t;&t;&t;(__NR_Linux +  83)
DECL|macro|__NR_oldlstat
mdefine_line|#define __NR_oldlstat&t;&t;&t;(__NR_Linux +  84)
DECL|macro|__NR_readlink
mdefine_line|#define __NR_readlink&t;&t;&t;(__NR_Linux +  85)
DECL|macro|__NR_uselib
mdefine_line|#define __NR_uselib&t;&t;&t;(__NR_Linux +  86)
DECL|macro|__NR_swapon
mdefine_line|#define __NR_swapon&t;&t;&t;(__NR_Linux +  87)
DECL|macro|__NR_reboot
mdefine_line|#define __NR_reboot&t;&t;&t;(__NR_Linux +  88)
DECL|macro|__NR_readdir
mdefine_line|#define __NR_readdir&t;&t;&t;(__NR_Linux +  89)
DECL|macro|__NR_mmap
mdefine_line|#define __NR_mmap&t;&t;&t;(__NR_Linux +  90)
DECL|macro|__NR_munmap
mdefine_line|#define __NR_munmap&t;&t;&t;(__NR_Linux +  91)
DECL|macro|__NR_truncate
mdefine_line|#define __NR_truncate&t;&t;&t;(__NR_Linux +  92)
DECL|macro|__NR_ftruncate
mdefine_line|#define __NR_ftruncate&t;&t;&t;(__NR_Linux +  93)
DECL|macro|__NR_fchmod
mdefine_line|#define __NR_fchmod&t;&t;&t;(__NR_Linux +  94)
DECL|macro|__NR_fchown
mdefine_line|#define __NR_fchown&t;&t;&t;(__NR_Linux +  95)
DECL|macro|__NR_getpriority
mdefine_line|#define __NR_getpriority&t;&t;(__NR_Linux +  96)
DECL|macro|__NR_setpriority
mdefine_line|#define __NR_setpriority&t;&t;(__NR_Linux +  97)
DECL|macro|__NR_profil
mdefine_line|#define __NR_profil&t;&t;&t;(__NR_Linux +  98)
DECL|macro|__NR_statfs
mdefine_line|#define __NR_statfs&t;&t;&t;(__NR_Linux +  99)
DECL|macro|__NR_fstatfs
mdefine_line|#define __NR_fstatfs&t;&t;&t;(__NR_Linux + 100)
DECL|macro|__NR_ioperm
mdefine_line|#define __NR_ioperm&t;&t;&t;(__NR_Linux + 101)
DECL|macro|__NR_socketcall
mdefine_line|#define __NR_socketcall&t;&t;&t;(__NR_Linux + 102)
DECL|macro|__NR_syslog
mdefine_line|#define __NR_syslog&t;&t;&t;(__NR_Linux + 103)
DECL|macro|__NR_setitimer
mdefine_line|#define __NR_setitimer&t;&t;&t;(__NR_Linux + 104)
DECL|macro|__NR_getitimer
mdefine_line|#define __NR_getitimer&t;&t;&t;(__NR_Linux + 105)
DECL|macro|__NR_stat
mdefine_line|#define __NR_stat&t;&t;&t;(__NR_Linux + 106)
DECL|macro|__NR_lstat
mdefine_line|#define __NR_lstat&t;&t;&t;(__NR_Linux + 107)
DECL|macro|__NR_fstat
mdefine_line|#define __NR_fstat&t;&t;&t;(__NR_Linux + 108)
DECL|macro|__NR_unused109
mdefine_line|#define __NR_unused109&t;&t;&t;(__NR_Linux + 109)
DECL|macro|__NR_iopl
mdefine_line|#define __NR_iopl&t;&t;&t;(__NR_Linux + 110)
DECL|macro|__NR_vhangup
mdefine_line|#define __NR_vhangup&t;&t;&t;(__NR_Linux + 111)
DECL|macro|__NR_idle
mdefine_line|#define __NR_idle&t;&t;&t;(__NR_Linux + 112)
DECL|macro|__NR_vm86
mdefine_line|#define __NR_vm86&t;&t;&t;(__NR_Linux + 113)
DECL|macro|__NR_wait4
mdefine_line|#define __NR_wait4&t;&t;&t;(__NR_Linux + 114)
DECL|macro|__NR_swapoff
mdefine_line|#define __NR_swapoff&t;&t;&t;(__NR_Linux + 115)
DECL|macro|__NR_sysinfo
mdefine_line|#define __NR_sysinfo&t;&t;&t;(__NR_Linux + 116)
DECL|macro|__NR_ipc
mdefine_line|#define __NR_ipc&t;&t;&t;(__NR_Linux + 117)
DECL|macro|__NR_fsync
mdefine_line|#define __NR_fsync&t;&t;&t;(__NR_Linux + 118)
DECL|macro|__NR_sigreturn
mdefine_line|#define __NR_sigreturn&t;&t;&t;(__NR_Linux + 119)
DECL|macro|__NR_clone
mdefine_line|#define __NR_clone&t;&t;&t;(__NR_Linux + 120)
DECL|macro|__NR_setdomainname
mdefine_line|#define __NR_setdomainname&t;&t;(__NR_Linux + 121)
DECL|macro|__NR_uname
mdefine_line|#define __NR_uname&t;&t;&t;(__NR_Linux + 122)
DECL|macro|__NR_modify_ldt
mdefine_line|#define __NR_modify_ldt&t;&t;&t;(__NR_Linux + 123)
DECL|macro|__NR_adjtimex
mdefine_line|#define __NR_adjtimex&t;&t;&t;(__NR_Linux + 124)
DECL|macro|__NR_mprotect
mdefine_line|#define __NR_mprotect&t;&t;&t;(__NR_Linux + 125)
DECL|macro|__NR_sigprocmask
mdefine_line|#define __NR_sigprocmask&t;&t;(__NR_Linux + 126)
DECL|macro|__NR_create_module
mdefine_line|#define __NR_create_module&t;&t;(__NR_Linux + 127)
DECL|macro|__NR_init_module
mdefine_line|#define __NR_init_module&t;&t;(__NR_Linux + 128)
DECL|macro|__NR_delete_module
mdefine_line|#define __NR_delete_module&t;&t;(__NR_Linux + 129)
DECL|macro|__NR_get_kernel_syms
mdefine_line|#define __NR_get_kernel_syms&t;&t;(__NR_Linux + 130)
DECL|macro|__NR_quotactl
mdefine_line|#define __NR_quotactl&t;&t;&t;(__NR_Linux + 131)
DECL|macro|__NR_getpgid
mdefine_line|#define __NR_getpgid&t;&t;&t;(__NR_Linux + 132)
DECL|macro|__NR_fchdir
mdefine_line|#define __NR_fchdir&t;&t;&t;(__NR_Linux + 133)
DECL|macro|__NR_bdflush
mdefine_line|#define __NR_bdflush&t;&t;&t;(__NR_Linux + 134)
DECL|macro|__NR_sysfs
mdefine_line|#define __NR_sysfs&t;&t;&t;(__NR_Linux + 135)
DECL|macro|__NR_personality
mdefine_line|#define __NR_personality&t;&t;(__NR_Linux + 136)
DECL|macro|__NR_afs_syscall
mdefine_line|#define __NR_afs_syscall&t;&t;(__NR_Linux + 137) /* Syscall for Andrew File System */
DECL|macro|__NR_setfsuid
mdefine_line|#define __NR_setfsuid&t;&t;&t;(__NR_Linux + 138)
DECL|macro|__NR_setfsgid
mdefine_line|#define __NR_setfsgid&t;&t;&t;(__NR_Linux + 139)
DECL|macro|__NR__llseek
mdefine_line|#define __NR__llseek&t;&t;&t;(__NR_Linux + 140)
DECL|macro|__NR_getdents
mdefine_line|#define __NR_getdents&t;&t;&t;(__NR_Linux + 141)
DECL|macro|__NR__newselect
mdefine_line|#define __NR__newselect&t;&t;&t;(__NR_Linux + 142)
DECL|macro|__NR_flock
mdefine_line|#define __NR_flock&t;&t;&t;(__NR_Linux + 143)
DECL|macro|__NR_msync
mdefine_line|#define __NR_msync&t;&t;&t;(__NR_Linux + 144)
DECL|macro|__NR_readv
mdefine_line|#define __NR_readv&t;&t;&t;(__NR_Linux + 145)
DECL|macro|__NR_writev
mdefine_line|#define __NR_writev&t;&t;&t;(__NR_Linux + 146)
DECL|macro|__NR_cacheflush
mdefine_line|#define __NR_cacheflush&t;&t;&t;(__NR_Linux + 147)
DECL|macro|__NR_cachectl
mdefine_line|#define __NR_cachectl&t;&t;&t;(__NR_Linux + 148)
DECL|macro|__NR_sysmips
mdefine_line|#define __NR_sysmips&t;&t;&t;(__NR_Linux + 149)
DECL|macro|__NR_unused150
mdefine_line|#define __NR_unused150&t;&t;&t;(__NR_Linux + 150)
DECL|macro|__NR_getsid
mdefine_line|#define __NR_getsid&t;&t;&t;(__NR_Linux + 151)
DECL|macro|__NR_fdatasync
mdefine_line|#define __NR_fdatasync&t;&t;&t;(__NR_Linux + 152)
DECL|macro|__NR__sysctl
mdefine_line|#define __NR__sysctl&t;&t;&t;(__NR_Linux + 153)
DECL|macro|__NR_mlock
mdefine_line|#define __NR_mlock&t;&t;&t;(__NR_Linux + 154)
DECL|macro|__NR_munlock
mdefine_line|#define __NR_munlock&t;&t;&t;(__NR_Linux + 155)
DECL|macro|__NR_mlockall
mdefine_line|#define __NR_mlockall&t;&t;&t;(__NR_Linux + 156)
DECL|macro|__NR_munlockall
mdefine_line|#define __NR_munlockall&t;&t;&t;(__NR_Linux + 157)
DECL|macro|__NR_sched_setparam
mdefine_line|#define __NR_sched_setparam&t;&t;(__NR_Linux + 158)
DECL|macro|__NR_sched_getparam
mdefine_line|#define __NR_sched_getparam&t;&t;(__NR_Linux + 159)
DECL|macro|__NR_sched_setscheduler
mdefine_line|#define __NR_sched_setscheduler&t;&t;(__NR_Linux + 160)
DECL|macro|__NR_sched_getscheduler
mdefine_line|#define __NR_sched_getscheduler&t;&t;(__NR_Linux + 161)
DECL|macro|__NR_sched_yield
mdefine_line|#define __NR_sched_yield&t;&t;(__NR_Linux + 162)
DECL|macro|__NR_sched_get_priority_max
mdefine_line|#define __NR_sched_get_priority_max&t;(__NR_Linux + 163)
DECL|macro|__NR_sched_get_priority_min
mdefine_line|#define __NR_sched_get_priority_min&t;(__NR_Linux + 164)
DECL|macro|__NR_sched_rr_get_interval
mdefine_line|#define __NR_sched_rr_get_interval&t;(__NR_Linux + 165)
DECL|macro|__NR_nanosleep
mdefine_line|#define __NR_nanosleep&t;&t;&t;(__NR_Linux + 166)
DECL|macro|__NR_mremap
mdefine_line|#define __NR_mremap&t;&t;&t;(__NR_Linux + 167)
DECL|macro|__NR_accept
mdefine_line|#define __NR_accept&t;&t;&t;(__NR_Linux + 168)
DECL|macro|__NR_bind
mdefine_line|#define __NR_bind&t;&t;&t;(__NR_Linux + 169)
DECL|macro|__NR_connect
mdefine_line|#define __NR_connect&t;&t;&t;(__NR_Linux + 170)
DECL|macro|__NR_getpeername
mdefine_line|#define __NR_getpeername&t;&t;(__NR_Linux + 171)
DECL|macro|__NR_getsockname
mdefine_line|#define __NR_getsockname&t;&t;(__NR_Linux + 172)
DECL|macro|__NR_getsockopt
mdefine_line|#define __NR_getsockopt&t;&t;&t;(__NR_Linux + 173)
DECL|macro|__NR_listen
mdefine_line|#define __NR_listen&t;&t;&t;(__NR_Linux + 174)
DECL|macro|__NR_recv
mdefine_line|#define __NR_recv&t;&t;&t;(__NR_Linux + 175)
DECL|macro|__NR_recvfrom
mdefine_line|#define __NR_recvfrom&t;&t;&t;(__NR_Linux + 176)
DECL|macro|__NR_recvmsg
mdefine_line|#define __NR_recvmsg&t;&t;&t;(__NR_Linux + 177)
DECL|macro|__NR_send
mdefine_line|#define __NR_send&t;&t;&t;(__NR_Linux + 178)
DECL|macro|__NR_sendmsg
mdefine_line|#define __NR_sendmsg&t;&t;&t;(__NR_Linux + 179)
DECL|macro|__NR_sendto
mdefine_line|#define __NR_sendto&t;&t;&t;(__NR_Linux + 180)
DECL|macro|__NR_setsockopt
mdefine_line|#define __NR_setsockopt&t;&t;&t;(__NR_Linux + 181)
DECL|macro|__NR_shutdown
mdefine_line|#define __NR_shutdown&t;&t;&t;(__NR_Linux + 182)
DECL|macro|__NR_socket
mdefine_line|#define __NR_socket&t;&t;&t;(__NR_Linux + 183)
DECL|macro|__NR_socketpair
mdefine_line|#define __NR_socketpair&t;&t;&t;(__NR_Linux + 184)
DECL|macro|__NR_setresuid
mdefine_line|#define __NR_setresuid&t;&t;&t;(__NR_Linux + 185)
DECL|macro|__NR_getresuid
mdefine_line|#define __NR_getresuid&t;&t;&t;(__NR_Linux + 186)
DECL|macro|__NR_query_module
mdefine_line|#define __NR_query_module&t;&t;(__NR_Linux + 187)
DECL|macro|__NR_poll
mdefine_line|#define __NR_poll&t;&t;&t;(__NR_Linux + 188)
DECL|macro|__NR_nfsservctl
mdefine_line|#define __NR_nfsservctl&t;&t;&t;(__NR_Linux + 189)
DECL|macro|__NR_setresgid
mdefine_line|#define __NR_setresgid&t;&t;&t;(__NR_Linux + 190)
DECL|macro|__NR_getresgid
mdefine_line|#define __NR_getresgid&t;&t;&t;(__NR_Linux + 191)
DECL|macro|__NR_prctl
mdefine_line|#define __NR_prctl&t;&t;&t;(__NR_Linux + 192)
DECL|macro|__NR_rt_sigreturn
mdefine_line|#define __NR_rt_sigreturn&t;&t;(__NR_Linux + 193)
DECL|macro|__NR_rt_sigaction
mdefine_line|#define __NR_rt_sigaction&t;&t;(__NR_Linux + 194)
DECL|macro|__NR_rt_sigprocmask
mdefine_line|#define __NR_rt_sigprocmask&t;&t;(__NR_Linux + 195)
DECL|macro|__NR_rt_sigpending
mdefine_line|#define __NR_rt_sigpending&t;&t;(__NR_Linux + 196)
DECL|macro|__NR_rt_sigtimedwait
mdefine_line|#define __NR_rt_sigtimedwait&t;&t;(__NR_Linux + 197)
DECL|macro|__NR_rt_sigqueueinfo
mdefine_line|#define __NR_rt_sigqueueinfo&t;&t;(__NR_Linux + 198)
DECL|macro|__NR_rt_sigsuspend
mdefine_line|#define __NR_rt_sigsuspend&t;&t;(__NR_Linux + 199)
DECL|macro|__NR_pread
mdefine_line|#define __NR_pread&t;&t;&t;(__NR_Linux + 200)
DECL|macro|__NR_pwrite
mdefine_line|#define __NR_pwrite&t;&t;&t;(__NR_Linux + 201)
DECL|macro|__NR_chown
mdefine_line|#define __NR_chown&t;&t;&t;(__NR_Linux + 202)
DECL|macro|__NR_getcwd
mdefine_line|#define __NR_getcwd&t;&t;&t;(__NR_Linux + 203)
DECL|macro|__NR_capget
mdefine_line|#define __NR_capget&t;&t;&t;(__NR_Linux + 204)
DECL|macro|__NR_capset
mdefine_line|#define __NR_capset&t;&t;&t;(__NR_Linux + 205)
DECL|macro|__NR_sigaltstack
mdefine_line|#define __NR_sigaltstack&t;&t;(__NR_Linux + 206)
DECL|macro|__NR_sendfile
mdefine_line|#define __NR_sendfile&t;&t;&t;(__NR_Linux + 207)
DECL|macro|__NR_getpmsg
mdefine_line|#define __NR_getpmsg&t;&t;&t;(__NR_Linux + 208)
DECL|macro|__NR_putpmsg
mdefine_line|#define __NR_putpmsg&t;&t;&t;(__NR_Linux + 209)
DECL|macro|__NR_mmap2
mdefine_line|#define __NR_mmap2&t;&t;&t;(__NR_Linux + 210)
DECL|macro|__NR_truncate64
mdefine_line|#define __NR_truncate64&t;&t;&t;(__NR_Linux + 211)
DECL|macro|__NR_ftruncate64
mdefine_line|#define __NR_ftruncate64&t;&t;(__NR_Linux + 212)
DECL|macro|__NR_stat64
mdefine_line|#define __NR_stat64&t;&t;&t;(__NR_Linux + 213)
DECL|macro|__NR_lstat64
mdefine_line|#define __NR_lstat64&t;&t;&t;(__NR_Linux + 214)
DECL|macro|__NR_fstat64
mdefine_line|#define __NR_fstat64&t;&t;&t;(__NR_Linux + 215)
DECL|macro|__NR_pivot_root
mdefine_line|#define __NR_pivot_root&t;&t;&t;(__NR_Linux + 216)
DECL|macro|__NR_mincore
mdefine_line|#define __NR_mincore&t;&t;&t;(__NR_Linux + 217)
DECL|macro|__NR_madvise
mdefine_line|#define __NR_madvise&t;&t;&t;(__NR_Linux + 218)
DECL|macro|__NR_getdents64
mdefine_line|#define __NR_getdents64&t;&t;&t;(__NR_Linux + 219)
DECL|macro|__NR_fcntl64
mdefine_line|#define __NR_fcntl64&t;&t;&t;(__NR_Linux + 220)
DECL|macro|__NR_gettid
mdefine_line|#define __NR_gettid&t;&t;&t;(__NR_Linux + 221)
DECL|macro|__NR_tkill
mdefine_line|#define __NR_tkill&t;&t;&t;(__NR_Linux + 222)
multiline_comment|/*&n; * Offset of the last Linux flavoured syscall&n; */
DECL|macro|__NR_Linux_syscalls
mdefine_line|#define __NR_Linux_syscalls&t;&t;220
macro_line|#ifndef _LANGUAGE_ASSEMBLY
multiline_comment|/* XXX - _foo needs to be __foo, while __NR_bar could be _NR_bar. */
DECL|macro|_syscall0
mdefine_line|#define _syscall0(type,name) &bslash;&n;type name(void) &bslash;&n;{ &bslash;&n;long __res, __err; &bslash;&n;__asm__ volatile (&quot;li&bslash;t$2,%2&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;  &quot;syscall&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;  &quot;move&bslash;t%0, $2&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;  &quot;move&bslash;t%1, $7&quot; &bslash;&n;                  : &quot;=r&quot; (__res), &quot;=r&quot; (__err) &bslash;&n;                  : &quot;i&quot; (__NR_##name) &bslash;&n;                  : &quot;$2&quot;,&quot;$7&quot;,&quot;$8&quot;,&quot;$9&quot;,&quot;$10&quot;,&quot;$11&quot;,&quot;$12&quot;,&quot;$13&quot;,&quot;$14&quot;,&quot;$15&quot;, &bslash;&n;&t;&t;    &quot;$24&quot;); &bslash;&n;if (__err == 0) &bslash;&n;&t;return (type) __res; &bslash;&n;errno = __res; &bslash;&n;return -1; &bslash;&n;}
multiline_comment|/*&n; * DANGER: This macro isn&squot;t usable for the pipe(2) call&n; * which has a unusual return convention.&n; */
DECL|macro|_syscall1
mdefine_line|#define _syscall1(type,name,atype,a) &bslash;&n;type name(atype a) &bslash;&n;{ &bslash;&n;long __res, __err; &bslash;&n;__asm__ volatile (&quot;move&bslash;t$4,%3&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;  &quot;li&bslash;t$2,%2&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;  &quot;syscall&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;  &quot;move&bslash;t%0, $2&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;  &quot;move&bslash;t%1, $7&quot; &bslash;&n;&t;&t;  : &quot;=r&quot; (__res), &quot;=r&quot; (__err) &bslash;&n;&t;&t;  : &quot;i&quot; (__NR_##name),&quot;r&quot; ((long)(a)) &bslash;&n;&t;&t;  : &quot;$2&quot;,&quot;$4&quot;,&quot;$7&quot;,&quot;$8&quot;,&quot;$9&quot;,&quot;$10&quot;,&quot;$11&quot;,&quot;$12&quot;,&quot;$13&quot;,&quot;$14&quot;,&quot;$15&quot;,&quot;$24&quot;); &bslash;&n;if (__err == 0) &bslash;&n;&t;return (type) __res; &bslash;&n;errno = __res; &bslash;&n;return -1; &bslash;&n;}
DECL|macro|_syscall2
mdefine_line|#define _syscall2(type,name,atype,a,btype,b) &bslash;&n;type name(atype a,btype b) &bslash;&n;{ &bslash;&n;long __res, __err; &bslash;&n;__asm__ volatile (&quot;move&bslash;t$4,%3&bslash;n&bslash;t&quot; &bslash;&n;                  &quot;move&bslash;t$5,%4&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;  &quot;li&bslash;t$2,%2&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;  &quot;syscall&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;  &quot;move&bslash;t%0, $2&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;  &quot;move&bslash;t%1, $7&quot; &bslash;&n;                  : &quot;=r&quot; (__res), &quot;=r&quot; (__err) &bslash;&n;                  : &quot;i&quot; (__NR_##name),&quot;r&quot; ((long)(a)), &bslash;&n;                                      &quot;r&quot; ((long)(b)) &bslash;&n;                  : &quot;$2&quot;,&quot;$4&quot;,&quot;$5&quot;,&quot;$7&quot;,&quot;$8&quot;,&quot;$9&quot;,&quot;$10&quot;,&quot;$11&quot;,&quot;$12&quot;,&quot;$13&quot;, &bslash;&n;&t;&t;    &quot;$14&quot;,&quot;$15&quot;, &quot;$24&quot;); &bslash;&n;if (__err == 0) &bslash;&n;&t;return (type) __res; &bslash;&n;errno = __res; &bslash;&n;return -1; &bslash;&n;}
DECL|macro|_syscall3
mdefine_line|#define _syscall3(type,name,atype,a,btype,b,ctype,c) &bslash;&n;type name (atype a, btype b, ctype c) &bslash;&n;{ &bslash;&n;long __res, __err; &bslash;&n;__asm__ volatile (&quot;move&bslash;t$4,%3&bslash;n&bslash;t&quot; &bslash;&n;                  &quot;move&bslash;t$5,%4&bslash;n&bslash;t&quot; &bslash;&n;                  &quot;move&bslash;t$6,%5&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;  &quot;li&bslash;t$2,%2&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;  &quot;syscall&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;  &quot;move&bslash;t%0, $2&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;  &quot;move&bslash;t%1, $7&quot; &bslash;&n;                  : &quot;=r&quot; (__res), &quot;=r&quot; (__err) &bslash;&n;                  : &quot;i&quot; (__NR_##name),&quot;r&quot; ((long)(a)), &bslash;&n;                                      &quot;r&quot; ((long)(b)), &bslash;&n;                                      &quot;r&quot; ((long)(c)) &bslash;&n;                  : &quot;$2&quot;,&quot;$4&quot;,&quot;$5&quot;,&quot;$6&quot;,&quot;$7&quot;,&quot;$8&quot;,&quot;$9&quot;,&quot;$10&quot;,&quot;$11&quot;,&quot;$12&quot;, &bslash;&n;&t;&t;    &quot;$13&quot;,&quot;$14&quot;,&quot;$15&quot;,&quot;$24&quot;); &bslash;&n;if (__err == 0) &bslash;&n;&t;return (type) __res; &bslash;&n;errno = __res; &bslash;&n;return -1; &bslash;&n;}
DECL|macro|_syscall4
mdefine_line|#define _syscall4(type,name,atype,a,btype,b,ctype,c,dtype,d) &bslash;&n;type name (atype a, btype b, ctype c, dtype d) &bslash;&n;{ &bslash;&n;long __res, __err; &bslash;&n;__asm__ volatile (&quot;move&bslash;t$4,%3&bslash;n&bslash;t&quot; &bslash;&n;                  &quot;move&bslash;t$5,%4&bslash;n&bslash;t&quot; &bslash;&n;                  &quot;move&bslash;t$6,%5&bslash;n&bslash;t&quot; &bslash;&n;                  &quot;move&bslash;t$7,%6&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;  &quot;li&bslash;t$2,%2&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;  &quot;syscall&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;  &quot;move&bslash;t%0, $2&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;  &quot;move&bslash;t%1, $7&quot; &bslash;&n;                  : &quot;=r&quot; (__res), &quot;=r&quot; (__err) &bslash;&n;                  : &quot;i&quot; (__NR_##name),&quot;r&quot; ((long)(a)), &bslash;&n;                                      &quot;r&quot; ((long)(b)), &bslash;&n;                                      &quot;r&quot; ((long)(c)), &bslash;&n;                                      &quot;r&quot; ((long)(d)) &bslash;&n;                  : &quot;$2&quot;,&quot;$4&quot;,&quot;$5&quot;,&quot;$6&quot;,&quot;$7&quot;,&quot;$8&quot;,&quot;$9&quot;,&quot;$10&quot;,&quot;$11&quot;,&quot;$12&quot;, &bslash;&n;&t;&t;    &quot;$13&quot;,&quot;$14&quot;,&quot;$15&quot;,&quot;$24&quot;); &bslash;&n;if (__err == 0) &bslash;&n;&t;return (type) __res; &bslash;&n;errno = __res; &bslash;&n;return -1; &bslash;&n;}
DECL|macro|_syscall5
mdefine_line|#define _syscall5(type,name,atype,a,btype,b,ctype,c,dtype,d,etype,e) &bslash;&n;type name (atype a,btype b,ctype c,dtype d,etype e) &bslash;&n;{ &bslash;&n;long __res, __err; &bslash;&n;__asm__ volatile (&quot;move&bslash;t$4,%3&bslash;n&bslash;t&quot; &bslash;&n;                  &quot;move&bslash;t$5,%4&bslash;n&bslash;t&quot; &bslash;&n;                  &quot;move&bslash;t$6,%5&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;  &quot;lw&bslash;t$2,%7&bslash;n&bslash;t&quot; &bslash;&n;                  &quot;move&bslash;t$7,%6&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;  &quot;subu&bslash;t$29,24&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;  &quot;sw&bslash;t$2,16($29)&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;  &quot;li&bslash;t$2,%2&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;  &quot;syscall&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;  &quot;move&bslash;t%0, $2&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;  &quot;move&bslash;t%1, $7&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;  &quot;addiu&bslash;t$29,24&quot; &bslash;&n;                  : &quot;=r&quot; (__res), &quot;=r&quot; (__err) &bslash;&n;                  : &quot;i&quot; (__NR_##name),&quot;r&quot; ((long)(a)), &bslash;&n;                                      &quot;r&quot; ((long)(b)), &bslash;&n;                                      &quot;r&quot; ((long)(c)), &bslash;&n;                                      &quot;r&quot; ((long)(d)), &bslash;&n;                                      &quot;m&quot; ((long)(e)) &bslash;&n;                  : &quot;$2&quot;,&quot;$4&quot;,&quot;$5&quot;,&quot;$6&quot;,&quot;$7&quot;,&quot;$8&quot;,&quot;$9&quot;,&quot;$10&quot;,&quot;$11&quot;,&quot;$12&quot;, &bslash;&n;                    &quot;$13&quot;,&quot;$14&quot;,&quot;$15&quot;,&quot;$24&quot;); &bslash;&n;if (__err == 0) &bslash;&n;&t;return (type) __res; &bslash;&n;errno = __res; &bslash;&n;return -1; &bslash;&n;}
DECL|macro|_syscall6
mdefine_line|#define _syscall6(type,name,atype,a,btype,b,ctype,c,dtype,d,etype,e,ftype,f) &bslash;&n;type name (atype a,btype b,ctype c,dtype d,etype e,ftype f) &bslash;&n;{ &bslash;&n;long __res, __err; &bslash;&n;__asm__ volatile (&quot;move&bslash;t$4,%3&bslash;n&bslash;t&quot; &bslash;&n;                  &quot;move&bslash;t$5,%4&bslash;n&bslash;t&quot; &bslash;&n;                  &quot;move&bslash;t$6,%5&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;  &quot;lw&bslash;t$2,%7&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;  &quot;lw&bslash;t$3,%8&bslash;n&bslash;t&quot; &bslash;&n;                  &quot;move&bslash;t$7,%6&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;  &quot;subu&bslash;t$29,24&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;  &quot;sw&bslash;t$2,16($29)&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;  &quot;sw&bslash;t$3,20($29)&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;  &quot;li&bslash;t$2,%2&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;  &quot;syscall&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;  &quot;move&bslash;t%0, $2&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;  &quot;move&bslash;t%1, $7&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;  &quot;addiu&bslash;t$29,24&quot; &bslash;&n;                  : &quot;=r&quot; (__res), &quot;=r&quot; (__err) &bslash;&n;                  : &quot;i&quot; (__NR_##name),&quot;r&quot; ((long)(a)), &bslash;&n;                                      &quot;r&quot; ((long)(b)), &bslash;&n;                                      &quot;r&quot; ((long)(c)), &bslash;&n;                                      &quot;r&quot; ((long)(d)), &bslash;&n;                                      &quot;m&quot; ((long)(e)), &bslash;&n;                                      &quot;m&quot; ((long)(f)) &bslash;&n;                  : &quot;$2&quot;,&quot;$3&quot;,&quot;$4&quot;,&quot;$5&quot;,&quot;$6&quot;,&quot;$7&quot;,&quot;$8&quot;,&quot;$9&quot;,&quot;$10&quot;,&quot;$11&quot;, &bslash;&n;                    &quot;$12&quot;,&quot;$13&quot;,&quot;$14&quot;,&quot;$15&quot;,&quot;$24&quot;); &bslash;&n;if (__err == 0) &bslash;&n;&t;return (type) __res; &bslash;&n;errno = __res; &bslash;&n;return -1; &bslash;&n;}
DECL|macro|_syscall7
mdefine_line|#define _syscall7(type,name,atype,a,btype,b,ctype,c,dtype,d,etype,e,ftype,f,gtype,g) &bslash;&n;type name (atype a,btype b,ctype c,dtype d,etype e,ftype f,gtype g) &bslash;&n;{ &bslash;&n;long __res, __err; &bslash;&n;__asm__ volatile (&quot;move&bslash;t$4,%3&bslash;n&bslash;t&quot; &bslash;&n;                  &quot;move&bslash;t$5,%4&bslash;n&bslash;t&quot; &bslash;&n;                  &quot;move&bslash;t$6,%5&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;  &quot;lw&bslash;t$2,%7&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;  &quot;lw&bslash;t$3,%8&bslash;n&bslash;t&quot; &bslash;&n;                  &quot;move&bslash;t$7,%6&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;  &quot;subu&bslash;t$29,32&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;  &quot;sw&bslash;t$2,16($29)&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;  &quot;lw&bslash;t$2,%9&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;  &quot;sw&bslash;t$3,20($29)&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;  &quot;sw&bslash;t$2,24($29)&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;  &quot;li&bslash;t$2,%2&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;  &quot;syscall&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;  &quot;move&bslash;t%0, $2&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;  &quot;move&bslash;t%1, $7&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;  &quot;addiu&bslash;t$29,32&quot; &bslash;&n;                  : &quot;=r&quot; (__res), &quot;=r&quot; (__err) &bslash;&n;                  : &quot;i&quot; (__NR_##name),&quot;r&quot; ((long)(a)), &bslash;&n;                                      &quot;r&quot; ((long)(b)), &bslash;&n;                                      &quot;r&quot; ((long)(c)), &bslash;&n;                                      &quot;r&quot; ((long)(d)), &bslash;&n;                                      &quot;m&quot; ((long)(e)), &bslash;&n;                                      &quot;m&quot; ((long)(f)), &bslash;&n;                                      &quot;m&quot; ((long)(g)) &bslash;&n;                  : &quot;$2&quot;,&quot;$3&quot;,&quot;$4&quot;,&quot;$5&quot;,&quot;$6&quot;,&quot;$7&quot;,&quot;$8&quot;,&quot;$9&quot;,&quot;$10&quot;,&quot;$11&quot;, &bslash;&n;                    &quot;$12&quot;,&quot;$13&quot;,&quot;$14&quot;,&quot;$15&quot;,&quot;$24&quot;); &bslash;&n;if (__err == 0) &bslash;&n;&t;return (type) __res; &bslash;&n;errno = __res; &bslash;&n;return -1; &bslash;&n;}
macro_line|#ifdef __KERNEL_SYSCALLS__
multiline_comment|/*&n; * we need this inline - forking from kernel space will result&n; * in NO COPY ON WRITE (!!!), until an execve is executed. This&n; * is no problem, but for the stack. This is handled by not letting&n; * main() use the stack at all after fork(). Thus, no function&n; * calls - which means inline code for fork too, as otherwise we&n; * would use the stack upon exit from &squot;fork()&squot;.&n; *&n; * Actually only pause and fork are needed inline, so that there&n; * won&squot;t be any messing with the stack from main(), but we define&n; * some others too.&n; */
DECL|macro|__NR__exit
mdefine_line|#define __NR__exit __NR_exit
r_static
r_inline
id|_syscall0
c_func
(paren
r_int
comma
id|sync
)paren
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
r_static
r_inline
id|_syscall1
c_func
(paren
r_int
comma
id|delete_module
comma
r_const
r_char
op_star
comma
id|name
)paren
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
id|waitpid
c_func
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
macro_line|#endif /* !defined (__KERNEL_SYSCALLS__) */
macro_line|#endif /* !defined (_LANGUAGE_ASSEMBLY) */
multiline_comment|/*&n; * &quot;Conditional&quot; syscalls&n; *&n; * What we want is __attribute__((weak,alias(&quot;sys_ni_syscall&quot;))),&n; * but it doesn&squot;t work on all toolchains, so we just do it by hand&n; */
DECL|macro|cond_syscall
mdefine_line|#define cond_syscall(x) asm(&quot;.weak&bslash;t&quot; #x &quot;&bslash;n&bslash;t.set&bslash;t&quot; #x &quot;,sys_ni_syscall&quot;);
macro_line|#endif /* _ASM_UNISTD_H */
eof
