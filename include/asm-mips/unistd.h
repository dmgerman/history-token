multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1995, 96, 97, 98, 99, 2000 by Ralf Baechle&n; * Copyright (C) 1999, 2000 Silicon Graphics, Inc.&n; *&n; * Changed system calls macros _syscall5 - _syscall7 to push args 5 to 7 onto&n; * the stack. Robin Farine for ACN S.A, Copyright (C) 1996 by ACN S.A&n; */
macro_line|#ifndef _ASM_UNISTD_H
DECL|macro|_ASM_UNISTD_H
mdefine_line|#define _ASM_UNISTD_H
macro_line|#include &lt;asm/sgidefs.h&gt;
macro_line|#if _MIPS_SIM == _MIPS_SIM_ABI32
multiline_comment|/*&n; * Linux o32 style syscalls are in the range from 4000 to 4999.&n; */
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
DECL|macro|__NR_unused18
mdefine_line|#define __NR_unused18&t;&t;&t;(__NR_Linux +  18)
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
DECL|macro|__NR_unused28
mdefine_line|#define __NR_unused28&t;&t;&t;(__NR_Linux +  28)
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
DECL|macro|__NR_unused84
mdefine_line|#define __NR_unused84&t;&t;&t;(__NR_Linux +  84)
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
DECL|macro|__NR_pread64
mdefine_line|#define __NR_pread64&t;&t;&t;(__NR_Linux + 200)
DECL|macro|__NR_pwrite64
mdefine_line|#define __NR_pwrite64&t;&t;&t;(__NR_Linux + 201)
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
DECL|macro|__NR_reserved221
mdefine_line|#define __NR_reserved221&t;&t;(__NR_Linux + 221)
DECL|macro|__NR_gettid
mdefine_line|#define __NR_gettid&t;&t;&t;(__NR_Linux + 222)
DECL|macro|__NR_readahead
mdefine_line|#define __NR_readahead&t;&t;&t;(__NR_Linux + 223)
DECL|macro|__NR_setxattr
mdefine_line|#define __NR_setxattr&t;&t;&t;(__NR_Linux + 224)
DECL|macro|__NR_lsetxattr
mdefine_line|#define __NR_lsetxattr&t;&t;&t;(__NR_Linux + 225)
DECL|macro|__NR_fsetxattr
mdefine_line|#define __NR_fsetxattr&t;&t;&t;(__NR_Linux + 226)
DECL|macro|__NR_getxattr
mdefine_line|#define __NR_getxattr&t;&t;&t;(__NR_Linux + 227)
DECL|macro|__NR_lgetxattr
mdefine_line|#define __NR_lgetxattr&t;&t;&t;(__NR_Linux + 228)
DECL|macro|__NR_fgetxattr
mdefine_line|#define __NR_fgetxattr&t;&t;&t;(__NR_Linux + 229)
DECL|macro|__NR_listxattr
mdefine_line|#define __NR_listxattr&t;&t;&t;(__NR_Linux + 230)
DECL|macro|__NR_llistxattr
mdefine_line|#define __NR_llistxattr&t;&t;&t;(__NR_Linux + 231)
DECL|macro|__NR_flistxattr
mdefine_line|#define __NR_flistxattr&t;&t;&t;(__NR_Linux + 232)
DECL|macro|__NR_removexattr
mdefine_line|#define __NR_removexattr&t;&t;(__NR_Linux + 233)
DECL|macro|__NR_lremovexattr
mdefine_line|#define __NR_lremovexattr&t;&t;(__NR_Linux + 234)
DECL|macro|__NR_fremovexattr
mdefine_line|#define __NR_fremovexattr&t;&t;(__NR_Linux + 235)
DECL|macro|__NR_tkill
mdefine_line|#define __NR_tkill&t;&t;&t;(__NR_Linux + 236)
DECL|macro|__NR_sendfile64
mdefine_line|#define __NR_sendfile64&t;&t;&t;(__NR_Linux + 237)
DECL|macro|__NR_futex
mdefine_line|#define __NR_futex&t;&t;&t;(__NR_Linux + 238)
DECL|macro|__NR_sched_setaffinity
mdefine_line|#define __NR_sched_setaffinity&t;&t;(__NR_Linux + 239)
DECL|macro|__NR_sched_getaffinity
mdefine_line|#define __NR_sched_getaffinity&t;&t;(__NR_Linux + 240)
DECL|macro|__NR_io_setup
mdefine_line|#define __NR_io_setup&t;&t;&t;(__NR_Linux + 241)
DECL|macro|__NR_io_destroy
mdefine_line|#define __NR_io_destroy&t;&t;&t;(__NR_Linux + 242)
DECL|macro|__NR_io_getevents
mdefine_line|#define __NR_io_getevents&t;&t;(__NR_Linux + 243)
DECL|macro|__NR_io_submit
mdefine_line|#define __NR_io_submit&t;&t;&t;(__NR_Linux + 244)
DECL|macro|__NR_io_cancel
mdefine_line|#define __NR_io_cancel&t;&t;&t;(__NR_Linux + 245)
DECL|macro|__NR_exit_group
mdefine_line|#define __NR_exit_group&t;&t;&t;(__NR_Linux + 246)
DECL|macro|__NR_lookup_dcookie
mdefine_line|#define __NR_lookup_dcookie&t;&t;(__NR_Linux + 247)
DECL|macro|__NR_epoll_create
mdefine_line|#define __NR_epoll_create&t;&t;(__NR_Linux + 248)
DECL|macro|__NR_epoll_ctl
mdefine_line|#define __NR_epoll_ctl&t;&t;&t;(__NR_Linux + 249)
DECL|macro|__NR_epoll_wait
mdefine_line|#define __NR_epoll_wait&t;&t;&t;(__NR_Linux + 250)
DECL|macro|__NR_remap_file_pages
mdefine_line|#define __NR_remap_file_pages&t;&t;(__NR_Linux + 251)
DECL|macro|__NR_set_tid_address
mdefine_line|#define __NR_set_tid_address&t;&t;(__NR_Linux + 252)
DECL|macro|__NR_restart_syscall
mdefine_line|#define __NR_restart_syscall&t;&t;(__NR_Linux + 253)
DECL|macro|__NR_fadvise64
mdefine_line|#define __NR_fadvise64&t;&t;&t;(__NR_Linux + 254)
DECL|macro|__NR_statfs64
mdefine_line|#define __NR_statfs64&t;&t;&t;(__NR_Linux + 255)
DECL|macro|__NR_fstatfs64
mdefine_line|#define __NR_fstatfs64&t;&t;&t;(__NR_Linux + 256)
DECL|macro|__NR_timer_create
mdefine_line|#define __NR_timer_create&t;&t;(__NR_Linux + 257)
DECL|macro|__NR_timer_settime
mdefine_line|#define __NR_timer_settime&t;&t;(__NR_Linux + 258)
DECL|macro|__NR_timer_gettime
mdefine_line|#define __NR_timer_gettime&t;&t;(__NR_Linux + 259)
DECL|macro|__NR_timer_getoverrun
mdefine_line|#define __NR_timer_getoverrun&t;&t;(__NR_Linux + 260)
DECL|macro|__NR_timer_delete
mdefine_line|#define __NR_timer_delete&t;&t;(__NR_Linux + 261)
DECL|macro|__NR_clock_settime
mdefine_line|#define __NR_clock_settime&t;&t;(__NR_Linux + 262)
DECL|macro|__NR_clock_gettime
mdefine_line|#define __NR_clock_gettime&t;&t;(__NR_Linux + 263)
DECL|macro|__NR_clock_getres
mdefine_line|#define __NR_clock_getres&t;&t;(__NR_Linux + 264)
DECL|macro|__NR_clock_nanosleep
mdefine_line|#define __NR_clock_nanosleep&t;&t;(__NR_Linux + 265)
DECL|macro|__NR_tgkill
mdefine_line|#define __NR_tgkill&t;&t;&t;(__NR_Linux + 266)
DECL|macro|__NR_utimes
mdefine_line|#define __NR_utimes&t;&t;&t;(__NR_Linux + 267)
DECL|macro|__NR_mbind
mdefine_line|#define __NR_mbind&t;&t;&t;(__NR_Linux + 268)
DECL|macro|__NR_get_mempolicy
mdefine_line|#define __NR_get_mempolicy&t;&t;(__NR_Linux + 269)
DECL|macro|__NR_set_mempolicy
mdefine_line|#define __NR_set_mempolicy&t;&t;(__NR_Linux + 270)
DECL|macro|__NR_mq_open
mdefine_line|#define __NR_mq_open&t;&t;&t;(__NR_Linux + 271)
DECL|macro|__NR_mq_unlink
mdefine_line|#define __NR_mq_unlink&t;&t;&t;(__NR_Linux + 272)
DECL|macro|__NR_mq_timedsend
mdefine_line|#define __NR_mq_timedsend&t;&t;(__NR_Linux + 273)
DECL|macro|__NR_mq_timedreceive
mdefine_line|#define __NR_mq_timedreceive&t;&t;(__NR_Linux + 274)
DECL|macro|__NR_mq_notify
mdefine_line|#define __NR_mq_notify&t;&t;&t;(__NR_Linux + 275)
DECL|macro|__NR_mq_getsetattr
mdefine_line|#define __NR_mq_getsetattr&t;&t;(__NR_Linux + 276)
DECL|macro|__NR_vserver
mdefine_line|#define __NR_vserver&t;&t;&t;(__NR_Linux + 277)
DECL|macro|__NR_waitid
mdefine_line|#define __NR_waitid&t;&t;&t;(__NR_Linux + 278)
multiline_comment|/* #define __NR_sys_setaltroot&t;&t;(__NR_Linux + 279) */
DECL|macro|__NR_add_key
mdefine_line|#define __NR_add_key&t;&t;&t;(__NR_Linux + 280)
DECL|macro|__NR_request_key
mdefine_line|#define __NR_request_key&t;&t;(__NR_Linux + 281)
DECL|macro|__NR_keyctl
mdefine_line|#define __NR_keyctl&t;&t;&t;(__NR_Linux + 282)
multiline_comment|/*&n; * Offset of the last Linux o32 flavoured syscall&n; */
DECL|macro|__NR_Linux_syscalls
mdefine_line|#define __NR_Linux_syscalls&t;&t;282
macro_line|#endif /* _MIPS_SIM == _MIPS_SIM_ABI32 */
DECL|macro|__NR_O32_Linux
mdefine_line|#define __NR_O32_Linux&t;&t;&t;4000
DECL|macro|__NR_O32_Linux_syscalls
mdefine_line|#define __NR_O32_Linux_syscalls&t;&t;282
macro_line|#if _MIPS_SIM == _MIPS_SIM_ABI64
multiline_comment|/*&n; * Linux 64-bit syscalls are in the range from 5000 to 5999.&n; */
DECL|macro|__NR_Linux
mdefine_line|#define __NR_Linux&t;&t;&t;5000
DECL|macro|__NR_read
mdefine_line|#define __NR_read&t;&t;&t;(__NR_Linux +   0)
DECL|macro|__NR_write
mdefine_line|#define __NR_write&t;&t;&t;(__NR_Linux +   1)
DECL|macro|__NR_open
mdefine_line|#define __NR_open&t;&t;&t;(__NR_Linux +   2)
DECL|macro|__NR_close
mdefine_line|#define __NR_close&t;&t;&t;(__NR_Linux +   3)
DECL|macro|__NR_stat
mdefine_line|#define __NR_stat&t;&t;&t;(__NR_Linux +   4)
DECL|macro|__NR_fstat
mdefine_line|#define __NR_fstat&t;&t;&t;(__NR_Linux +   5)
DECL|macro|__NR_lstat
mdefine_line|#define __NR_lstat&t;&t;&t;(__NR_Linux +   6)
DECL|macro|__NR_poll
mdefine_line|#define __NR_poll&t;&t;&t;(__NR_Linux +   7)
DECL|macro|__NR_lseek
mdefine_line|#define __NR_lseek&t;&t;&t;(__NR_Linux +   8)
DECL|macro|__NR_mmap
mdefine_line|#define __NR_mmap&t;&t;&t;(__NR_Linux +   9)
DECL|macro|__NR_mprotect
mdefine_line|#define __NR_mprotect&t;&t;&t;(__NR_Linux +  10)
DECL|macro|__NR_munmap
mdefine_line|#define __NR_munmap&t;&t;&t;(__NR_Linux +  11)
DECL|macro|__NR_brk
mdefine_line|#define __NR_brk&t;&t;&t;(__NR_Linux +  12)
DECL|macro|__NR_rt_sigaction
mdefine_line|#define __NR_rt_sigaction&t;&t;(__NR_Linux +  13)
DECL|macro|__NR_rt_sigprocmask
mdefine_line|#define __NR_rt_sigprocmask&t;&t;(__NR_Linux +  14)
DECL|macro|__NR_ioctl
mdefine_line|#define __NR_ioctl&t;&t;&t;(__NR_Linux +  15)
DECL|macro|__NR_pread64
mdefine_line|#define __NR_pread64&t;&t;&t;(__NR_Linux +  16)
DECL|macro|__NR_pwrite64
mdefine_line|#define __NR_pwrite64&t;&t;&t;(__NR_Linux +  17)
DECL|macro|__NR_readv
mdefine_line|#define __NR_readv&t;&t;&t;(__NR_Linux +  18)
DECL|macro|__NR_writev
mdefine_line|#define __NR_writev&t;&t;&t;(__NR_Linux +  19)
DECL|macro|__NR_access
mdefine_line|#define __NR_access&t;&t;&t;(__NR_Linux +  20)
DECL|macro|__NR_pipe
mdefine_line|#define __NR_pipe&t;&t;&t;(__NR_Linux +  21)
DECL|macro|__NR__newselect
mdefine_line|#define __NR__newselect&t;&t;&t;(__NR_Linux +  22)
DECL|macro|__NR_sched_yield
mdefine_line|#define __NR_sched_yield&t;&t;(__NR_Linux +  23)
DECL|macro|__NR_mremap
mdefine_line|#define __NR_mremap&t;&t;&t;(__NR_Linux +  24)
DECL|macro|__NR_msync
mdefine_line|#define __NR_msync&t;&t;&t;(__NR_Linux +  25)
DECL|macro|__NR_mincore
mdefine_line|#define __NR_mincore&t;&t;&t;(__NR_Linux +  26)
DECL|macro|__NR_madvise
mdefine_line|#define __NR_madvise&t;&t;&t;(__NR_Linux +  27)
DECL|macro|__NR_shmget
mdefine_line|#define __NR_shmget&t;&t;&t;(__NR_Linux +  28)
DECL|macro|__NR_shmat
mdefine_line|#define __NR_shmat&t;&t;&t;(__NR_Linux +  29)
DECL|macro|__NR_shmctl
mdefine_line|#define __NR_shmctl&t;&t;&t;(__NR_Linux +  30)
DECL|macro|__NR_dup
mdefine_line|#define __NR_dup&t;&t;&t;(__NR_Linux +  31)
DECL|macro|__NR_dup2
mdefine_line|#define __NR_dup2&t;&t;&t;(__NR_Linux +  32)
DECL|macro|__NR_pause
mdefine_line|#define __NR_pause&t;&t;&t;(__NR_Linux +  33)
DECL|macro|__NR_nanosleep
mdefine_line|#define __NR_nanosleep&t;&t;&t;(__NR_Linux +  34)
DECL|macro|__NR_getitimer
mdefine_line|#define __NR_getitimer&t;&t;&t;(__NR_Linux +  35)
DECL|macro|__NR_setitimer
mdefine_line|#define __NR_setitimer&t;&t;&t;(__NR_Linux +  36)
DECL|macro|__NR_alarm
mdefine_line|#define __NR_alarm&t;&t;&t;(__NR_Linux +  37)
DECL|macro|__NR_getpid
mdefine_line|#define __NR_getpid&t;&t;&t;(__NR_Linux +  38)
DECL|macro|__NR_sendfile
mdefine_line|#define __NR_sendfile&t;&t;&t;(__NR_Linux +  39)
DECL|macro|__NR_socket
mdefine_line|#define __NR_socket&t;&t;&t;(__NR_Linux +  40)
DECL|macro|__NR_connect
mdefine_line|#define __NR_connect&t;&t;&t;(__NR_Linux +  41)
DECL|macro|__NR_accept
mdefine_line|#define __NR_accept&t;&t;&t;(__NR_Linux +  42)
DECL|macro|__NR_sendto
mdefine_line|#define __NR_sendto&t;&t;&t;(__NR_Linux +  43)
DECL|macro|__NR_recvfrom
mdefine_line|#define __NR_recvfrom&t;&t;&t;(__NR_Linux +  44)
DECL|macro|__NR_sendmsg
mdefine_line|#define __NR_sendmsg&t;&t;&t;(__NR_Linux +  45)
DECL|macro|__NR_recvmsg
mdefine_line|#define __NR_recvmsg&t;&t;&t;(__NR_Linux +  46)
DECL|macro|__NR_shutdown
mdefine_line|#define __NR_shutdown&t;&t;&t;(__NR_Linux +  47)
DECL|macro|__NR_bind
mdefine_line|#define __NR_bind&t;&t;&t;(__NR_Linux +  48)
DECL|macro|__NR_listen
mdefine_line|#define __NR_listen&t;&t;&t;(__NR_Linux +  49)
DECL|macro|__NR_getsockname
mdefine_line|#define __NR_getsockname&t;&t;(__NR_Linux +  50)
DECL|macro|__NR_getpeername
mdefine_line|#define __NR_getpeername&t;&t;(__NR_Linux +  51)
DECL|macro|__NR_socketpair
mdefine_line|#define __NR_socketpair&t;&t;&t;(__NR_Linux +  52)
DECL|macro|__NR_setsockopt
mdefine_line|#define __NR_setsockopt&t;&t;&t;(__NR_Linux +  53)
DECL|macro|__NR_getsockopt
mdefine_line|#define __NR_getsockopt&t;&t;&t;(__NR_Linux +  54)
DECL|macro|__NR_clone
mdefine_line|#define __NR_clone&t;&t;&t;(__NR_Linux +  55)
DECL|macro|__NR_fork
mdefine_line|#define __NR_fork&t;&t;&t;(__NR_Linux +  56)
DECL|macro|__NR_execve
mdefine_line|#define __NR_execve&t;&t;&t;(__NR_Linux +  57)
DECL|macro|__NR_exit
mdefine_line|#define __NR_exit&t;&t;&t;(__NR_Linux +  58)
DECL|macro|__NR_wait4
mdefine_line|#define __NR_wait4&t;&t;&t;(__NR_Linux +  59)
DECL|macro|__NR_kill
mdefine_line|#define __NR_kill&t;&t;&t;(__NR_Linux +  60)
DECL|macro|__NR_uname
mdefine_line|#define __NR_uname&t;&t;&t;(__NR_Linux +  61)
DECL|macro|__NR_semget
mdefine_line|#define __NR_semget&t;&t;&t;(__NR_Linux +  62)
DECL|macro|__NR_semop
mdefine_line|#define __NR_semop&t;&t;&t;(__NR_Linux +  63)
DECL|macro|__NR_semctl
mdefine_line|#define __NR_semctl&t;&t;&t;(__NR_Linux +  64)
DECL|macro|__NR_shmdt
mdefine_line|#define __NR_shmdt&t;&t;&t;(__NR_Linux +  65)
DECL|macro|__NR_msgget
mdefine_line|#define __NR_msgget&t;&t;&t;(__NR_Linux +  66)
DECL|macro|__NR_msgsnd
mdefine_line|#define __NR_msgsnd&t;&t;&t;(__NR_Linux +  67)
DECL|macro|__NR_msgrcv
mdefine_line|#define __NR_msgrcv&t;&t;&t;(__NR_Linux +  68)
DECL|macro|__NR_msgctl
mdefine_line|#define __NR_msgctl&t;&t;&t;(__NR_Linux +  69)
DECL|macro|__NR_fcntl
mdefine_line|#define __NR_fcntl&t;&t;&t;(__NR_Linux +  70)
DECL|macro|__NR_flock
mdefine_line|#define __NR_flock&t;&t;&t;(__NR_Linux +  71)
DECL|macro|__NR_fsync
mdefine_line|#define __NR_fsync&t;&t;&t;(__NR_Linux +  72)
DECL|macro|__NR_fdatasync
mdefine_line|#define __NR_fdatasync&t;&t;&t;(__NR_Linux +  73)
DECL|macro|__NR_truncate
mdefine_line|#define __NR_truncate&t;&t;&t;(__NR_Linux +  74)
DECL|macro|__NR_ftruncate
mdefine_line|#define __NR_ftruncate&t;&t;&t;(__NR_Linux +  75)
DECL|macro|__NR_getdents
mdefine_line|#define __NR_getdents&t;&t;&t;(__NR_Linux +  76)
DECL|macro|__NR_getcwd
mdefine_line|#define __NR_getcwd&t;&t;&t;(__NR_Linux +  77)
DECL|macro|__NR_chdir
mdefine_line|#define __NR_chdir&t;&t;&t;(__NR_Linux +  78)
DECL|macro|__NR_fchdir
mdefine_line|#define __NR_fchdir&t;&t;&t;(__NR_Linux +  79)
DECL|macro|__NR_rename
mdefine_line|#define __NR_rename&t;&t;&t;(__NR_Linux +  80)
DECL|macro|__NR_mkdir
mdefine_line|#define __NR_mkdir&t;&t;&t;(__NR_Linux +  81)
DECL|macro|__NR_rmdir
mdefine_line|#define __NR_rmdir&t;&t;&t;(__NR_Linux +  82)
DECL|macro|__NR_creat
mdefine_line|#define __NR_creat&t;&t;&t;(__NR_Linux +  83)
DECL|macro|__NR_link
mdefine_line|#define __NR_link&t;&t;&t;(__NR_Linux +  84)
DECL|macro|__NR_unlink
mdefine_line|#define __NR_unlink&t;&t;&t;(__NR_Linux +  85)
DECL|macro|__NR_symlink
mdefine_line|#define __NR_symlink&t;&t;&t;(__NR_Linux +  86)
DECL|macro|__NR_readlink
mdefine_line|#define __NR_readlink&t;&t;&t;(__NR_Linux +  87)
DECL|macro|__NR_chmod
mdefine_line|#define __NR_chmod&t;&t;&t;(__NR_Linux +  88)
DECL|macro|__NR_fchmod
mdefine_line|#define __NR_fchmod&t;&t;&t;(__NR_Linux +  89)
DECL|macro|__NR_chown
mdefine_line|#define __NR_chown&t;&t;&t;(__NR_Linux +  90)
DECL|macro|__NR_fchown
mdefine_line|#define __NR_fchown&t;&t;&t;(__NR_Linux +  91)
DECL|macro|__NR_lchown
mdefine_line|#define __NR_lchown&t;&t;&t;(__NR_Linux +  92)
DECL|macro|__NR_umask
mdefine_line|#define __NR_umask&t;&t;&t;(__NR_Linux +  93)
DECL|macro|__NR_gettimeofday
mdefine_line|#define __NR_gettimeofday&t;&t;(__NR_Linux +  94)
DECL|macro|__NR_getrlimit
mdefine_line|#define __NR_getrlimit&t;&t;&t;(__NR_Linux +  95)
DECL|macro|__NR_getrusage
mdefine_line|#define __NR_getrusage&t;&t;&t;(__NR_Linux +  96)
DECL|macro|__NR_sysinfo
mdefine_line|#define __NR_sysinfo&t;&t;&t;(__NR_Linux +  97)
DECL|macro|__NR_times
mdefine_line|#define __NR_times&t;&t;&t;(__NR_Linux +  98)
DECL|macro|__NR_ptrace
mdefine_line|#define __NR_ptrace&t;&t;&t;(__NR_Linux +  99)
DECL|macro|__NR_getuid
mdefine_line|#define __NR_getuid&t;&t;&t;(__NR_Linux + 100)
DECL|macro|__NR_syslog
mdefine_line|#define __NR_syslog&t;&t;&t;(__NR_Linux + 101)
DECL|macro|__NR_getgid
mdefine_line|#define __NR_getgid&t;&t;&t;(__NR_Linux + 102)
DECL|macro|__NR_setuid
mdefine_line|#define __NR_setuid&t;&t;&t;(__NR_Linux + 103)
DECL|macro|__NR_setgid
mdefine_line|#define __NR_setgid&t;&t;&t;(__NR_Linux + 104)
DECL|macro|__NR_geteuid
mdefine_line|#define __NR_geteuid&t;&t;&t;(__NR_Linux + 105)
DECL|macro|__NR_getegid
mdefine_line|#define __NR_getegid&t;&t;&t;(__NR_Linux + 106)
DECL|macro|__NR_setpgid
mdefine_line|#define __NR_setpgid&t;&t;&t;(__NR_Linux + 107)
DECL|macro|__NR_getppid
mdefine_line|#define __NR_getppid&t;&t;&t;(__NR_Linux + 108)
DECL|macro|__NR_getpgrp
mdefine_line|#define __NR_getpgrp&t;&t;&t;(__NR_Linux + 109)
DECL|macro|__NR_setsid
mdefine_line|#define __NR_setsid&t;&t;&t;(__NR_Linux + 110)
DECL|macro|__NR_setreuid
mdefine_line|#define __NR_setreuid&t;&t;&t;(__NR_Linux + 111)
DECL|macro|__NR_setregid
mdefine_line|#define __NR_setregid&t;&t;&t;(__NR_Linux + 112)
DECL|macro|__NR_getgroups
mdefine_line|#define __NR_getgroups&t;&t;&t;(__NR_Linux + 113)
DECL|macro|__NR_setgroups
mdefine_line|#define __NR_setgroups&t;&t;&t;(__NR_Linux + 114)
DECL|macro|__NR_setresuid
mdefine_line|#define __NR_setresuid&t;&t;&t;(__NR_Linux + 115)
DECL|macro|__NR_getresuid
mdefine_line|#define __NR_getresuid&t;&t;&t;(__NR_Linux + 116)
DECL|macro|__NR_setresgid
mdefine_line|#define __NR_setresgid&t;&t;&t;(__NR_Linux + 117)
DECL|macro|__NR_getresgid
mdefine_line|#define __NR_getresgid&t;&t;&t;(__NR_Linux + 118)
DECL|macro|__NR_getpgid
mdefine_line|#define __NR_getpgid&t;&t;&t;(__NR_Linux + 119)
DECL|macro|__NR_setfsuid
mdefine_line|#define __NR_setfsuid&t;&t;&t;(__NR_Linux + 120)
DECL|macro|__NR_setfsgid
mdefine_line|#define __NR_setfsgid&t;&t;&t;(__NR_Linux + 121)
DECL|macro|__NR_getsid
mdefine_line|#define __NR_getsid&t;&t;&t;(__NR_Linux + 122)
DECL|macro|__NR_capget
mdefine_line|#define __NR_capget&t;&t;&t;(__NR_Linux + 123)
DECL|macro|__NR_capset
mdefine_line|#define __NR_capset&t;&t;&t;(__NR_Linux + 124)
DECL|macro|__NR_rt_sigpending
mdefine_line|#define __NR_rt_sigpending&t;&t;(__NR_Linux + 125)
DECL|macro|__NR_rt_sigtimedwait
mdefine_line|#define __NR_rt_sigtimedwait&t;&t;(__NR_Linux + 126)
DECL|macro|__NR_rt_sigqueueinfo
mdefine_line|#define __NR_rt_sigqueueinfo&t;&t;(__NR_Linux + 127)
DECL|macro|__NR_rt_sigsuspend
mdefine_line|#define __NR_rt_sigsuspend&t;&t;(__NR_Linux + 128)
DECL|macro|__NR_sigaltstack
mdefine_line|#define __NR_sigaltstack&t;&t;(__NR_Linux + 129)
DECL|macro|__NR_utime
mdefine_line|#define __NR_utime&t;&t;&t;(__NR_Linux + 130)
DECL|macro|__NR_mknod
mdefine_line|#define __NR_mknod&t;&t;&t;(__NR_Linux + 131)
DECL|macro|__NR_personality
mdefine_line|#define __NR_personality&t;&t;(__NR_Linux + 132)
DECL|macro|__NR_ustat
mdefine_line|#define __NR_ustat&t;&t;&t;(__NR_Linux + 133)
DECL|macro|__NR_statfs
mdefine_line|#define __NR_statfs&t;&t;&t;(__NR_Linux + 134)
DECL|macro|__NR_fstatfs
mdefine_line|#define __NR_fstatfs&t;&t;&t;(__NR_Linux + 135)
DECL|macro|__NR_sysfs
mdefine_line|#define __NR_sysfs&t;&t;&t;(__NR_Linux + 136)
DECL|macro|__NR_getpriority
mdefine_line|#define __NR_getpriority&t;&t;(__NR_Linux + 137)
DECL|macro|__NR_setpriority
mdefine_line|#define __NR_setpriority&t;&t;(__NR_Linux + 138)
DECL|macro|__NR_sched_setparam
mdefine_line|#define __NR_sched_setparam&t;&t;(__NR_Linux + 139)
DECL|macro|__NR_sched_getparam
mdefine_line|#define __NR_sched_getparam&t;&t;(__NR_Linux + 140)
DECL|macro|__NR_sched_setscheduler
mdefine_line|#define __NR_sched_setscheduler&t;&t;(__NR_Linux + 141)
DECL|macro|__NR_sched_getscheduler
mdefine_line|#define __NR_sched_getscheduler&t;&t;(__NR_Linux + 142)
DECL|macro|__NR_sched_get_priority_max
mdefine_line|#define __NR_sched_get_priority_max&t;(__NR_Linux + 143)
DECL|macro|__NR_sched_get_priority_min
mdefine_line|#define __NR_sched_get_priority_min&t;(__NR_Linux + 144)
DECL|macro|__NR_sched_rr_get_interval
mdefine_line|#define __NR_sched_rr_get_interval&t;(__NR_Linux + 145)
DECL|macro|__NR_mlock
mdefine_line|#define __NR_mlock&t;&t;&t;(__NR_Linux + 146)
DECL|macro|__NR_munlock
mdefine_line|#define __NR_munlock&t;&t;&t;(__NR_Linux + 147)
DECL|macro|__NR_mlockall
mdefine_line|#define __NR_mlockall&t;&t;&t;(__NR_Linux + 148)
DECL|macro|__NR_munlockall
mdefine_line|#define __NR_munlockall&t;&t;&t;(__NR_Linux + 149)
DECL|macro|__NR_vhangup
mdefine_line|#define __NR_vhangup&t;&t;&t;(__NR_Linux + 150)
DECL|macro|__NR_pivot_root
mdefine_line|#define __NR_pivot_root&t;&t;&t;(__NR_Linux + 151)
DECL|macro|__NR__sysctl
mdefine_line|#define __NR__sysctl&t;&t;&t;(__NR_Linux + 152)
DECL|macro|__NR_prctl
mdefine_line|#define __NR_prctl&t;&t;&t;(__NR_Linux + 153)
DECL|macro|__NR_adjtimex
mdefine_line|#define __NR_adjtimex&t;&t;&t;(__NR_Linux + 154)
DECL|macro|__NR_setrlimit
mdefine_line|#define __NR_setrlimit&t;&t;&t;(__NR_Linux + 155)
DECL|macro|__NR_chroot
mdefine_line|#define __NR_chroot&t;&t;&t;(__NR_Linux + 156)
DECL|macro|__NR_sync
mdefine_line|#define __NR_sync&t;&t;&t;(__NR_Linux + 157)
DECL|macro|__NR_acct
mdefine_line|#define __NR_acct&t;&t;&t;(__NR_Linux + 158)
DECL|macro|__NR_settimeofday
mdefine_line|#define __NR_settimeofday&t;&t;(__NR_Linux + 159)
DECL|macro|__NR_mount
mdefine_line|#define __NR_mount&t;&t;&t;(__NR_Linux + 160)
DECL|macro|__NR_umount2
mdefine_line|#define __NR_umount2&t;&t;&t;(__NR_Linux + 161)
DECL|macro|__NR_swapon
mdefine_line|#define __NR_swapon&t;&t;&t;(__NR_Linux + 162)
DECL|macro|__NR_swapoff
mdefine_line|#define __NR_swapoff&t;&t;&t;(__NR_Linux + 163)
DECL|macro|__NR_reboot
mdefine_line|#define __NR_reboot&t;&t;&t;(__NR_Linux + 164)
DECL|macro|__NR_sethostname
mdefine_line|#define __NR_sethostname&t;&t;(__NR_Linux + 165)
DECL|macro|__NR_setdomainname
mdefine_line|#define __NR_setdomainname&t;&t;(__NR_Linux + 166)
DECL|macro|__NR_create_module
mdefine_line|#define __NR_create_module&t;&t;(__NR_Linux + 167)
DECL|macro|__NR_init_module
mdefine_line|#define __NR_init_module&t;&t;(__NR_Linux + 168)
DECL|macro|__NR_delete_module
mdefine_line|#define __NR_delete_module&t;&t;(__NR_Linux + 169)
DECL|macro|__NR_get_kernel_syms
mdefine_line|#define __NR_get_kernel_syms&t;&t;(__NR_Linux + 170)
DECL|macro|__NR_query_module
mdefine_line|#define __NR_query_module&t;&t;(__NR_Linux + 171)
DECL|macro|__NR_quotactl
mdefine_line|#define __NR_quotactl&t;&t;&t;(__NR_Linux + 172)
DECL|macro|__NR_nfsservctl
mdefine_line|#define __NR_nfsservctl&t;&t;&t;(__NR_Linux + 173)
DECL|macro|__NR_getpmsg
mdefine_line|#define __NR_getpmsg&t;&t;&t;(__NR_Linux + 174)
DECL|macro|__NR_putpmsg
mdefine_line|#define __NR_putpmsg&t;&t;&t;(__NR_Linux + 175)
DECL|macro|__NR_afs_syscall
mdefine_line|#define __NR_afs_syscall&t;&t;(__NR_Linux + 176)
DECL|macro|__NR_reserved177
mdefine_line|#define __NR_reserved177&t;&t;(__NR_Linux + 177)
DECL|macro|__NR_gettid
mdefine_line|#define __NR_gettid&t;&t;&t;(__NR_Linux + 178)
DECL|macro|__NR_readahead
mdefine_line|#define __NR_readahead&t;&t;&t;(__NR_Linux + 179)
DECL|macro|__NR_setxattr
mdefine_line|#define __NR_setxattr&t;&t;&t;(__NR_Linux + 180)
DECL|macro|__NR_lsetxattr
mdefine_line|#define __NR_lsetxattr&t;&t;&t;(__NR_Linux + 181)
DECL|macro|__NR_fsetxattr
mdefine_line|#define __NR_fsetxattr&t;&t;&t;(__NR_Linux + 182)
DECL|macro|__NR_getxattr
mdefine_line|#define __NR_getxattr&t;&t;&t;(__NR_Linux + 183)
DECL|macro|__NR_lgetxattr
mdefine_line|#define __NR_lgetxattr&t;&t;&t;(__NR_Linux + 184)
DECL|macro|__NR_fgetxattr
mdefine_line|#define __NR_fgetxattr&t;&t;&t;(__NR_Linux + 185)
DECL|macro|__NR_listxattr
mdefine_line|#define __NR_listxattr&t;&t;&t;(__NR_Linux + 186)
DECL|macro|__NR_llistxattr
mdefine_line|#define __NR_llistxattr&t;&t;&t;(__NR_Linux + 187)
DECL|macro|__NR_flistxattr
mdefine_line|#define __NR_flistxattr&t;&t;&t;(__NR_Linux + 188)
DECL|macro|__NR_removexattr
mdefine_line|#define __NR_removexattr&t;&t;(__NR_Linux + 189)
DECL|macro|__NR_lremovexattr
mdefine_line|#define __NR_lremovexattr&t;&t;(__NR_Linux + 190)
DECL|macro|__NR_fremovexattr
mdefine_line|#define __NR_fremovexattr&t;&t;(__NR_Linux + 191)
DECL|macro|__NR_tkill
mdefine_line|#define __NR_tkill&t;&t;&t;(__NR_Linux + 192)
DECL|macro|__NR_reserved193
mdefine_line|#define __NR_reserved193&t;&t;(__NR_Linux + 193)
DECL|macro|__NR_futex
mdefine_line|#define __NR_futex&t;&t;&t;(__NR_Linux + 194)
DECL|macro|__NR_sched_setaffinity
mdefine_line|#define __NR_sched_setaffinity&t;&t;(__NR_Linux + 195)
DECL|macro|__NR_sched_getaffinity
mdefine_line|#define __NR_sched_getaffinity&t;&t;(__NR_Linux + 196)
DECL|macro|__NR_cacheflush
mdefine_line|#define __NR_cacheflush&t;&t;&t;(__NR_Linux + 197)
DECL|macro|__NR_cachectl
mdefine_line|#define __NR_cachectl&t;&t;&t;(__NR_Linux + 198)
DECL|macro|__NR_sysmips
mdefine_line|#define __NR_sysmips&t;&t;&t;(__NR_Linux + 199)
DECL|macro|__NR_io_setup
mdefine_line|#define __NR_io_setup&t;&t;&t;(__NR_Linux + 200)
DECL|macro|__NR_io_destroy
mdefine_line|#define __NR_io_destroy&t;&t;&t;(__NR_Linux + 201)
DECL|macro|__NR_io_getevents
mdefine_line|#define __NR_io_getevents&t;&t;(__NR_Linux + 202)
DECL|macro|__NR_io_submit
mdefine_line|#define __NR_io_submit&t;&t;&t;(__NR_Linux + 203)
DECL|macro|__NR_io_cancel
mdefine_line|#define __NR_io_cancel&t;&t;&t;(__NR_Linux + 204)
DECL|macro|__NR_exit_group
mdefine_line|#define __NR_exit_group&t;&t;&t;(__NR_Linux + 205)
DECL|macro|__NR_lookup_dcookie
mdefine_line|#define __NR_lookup_dcookie&t;&t;(__NR_Linux + 206)
DECL|macro|__NR_epoll_create
mdefine_line|#define __NR_epoll_create&t;&t;(__NR_Linux + 207)
DECL|macro|__NR_epoll_ctl
mdefine_line|#define __NR_epoll_ctl&t;&t;&t;(__NR_Linux + 208)
DECL|macro|__NR_epoll_wait
mdefine_line|#define __NR_epoll_wait&t;&t;&t;(__NR_Linux + 209)
DECL|macro|__NR_remap_file_pages
mdefine_line|#define __NR_remap_file_pages&t;&t;(__NR_Linux + 210)
DECL|macro|__NR_rt_sigreturn
mdefine_line|#define __NR_rt_sigreturn&t;&t;(__NR_Linux + 211)
DECL|macro|__NR_set_tid_address
mdefine_line|#define __NR_set_tid_address&t;&t;(__NR_Linux + 212)
DECL|macro|__NR_restart_syscall
mdefine_line|#define __NR_restart_syscall&t;&t;(__NR_Linux + 213)
DECL|macro|__NR_semtimedop
mdefine_line|#define __NR_semtimedop&t;&t;&t;(__NR_Linux + 214)
DECL|macro|__NR_fadvise64
mdefine_line|#define __NR_fadvise64&t;&t;&t;(__NR_Linux + 215)
DECL|macro|__NR_timer_create
mdefine_line|#define __NR_timer_create&t;&t;(__NR_Linux + 216)
DECL|macro|__NR_timer_settime
mdefine_line|#define __NR_timer_settime&t;&t;(__NR_Linux + 217)
DECL|macro|__NR_timer_gettime
mdefine_line|#define __NR_timer_gettime&t;&t;(__NR_Linux + 218)
DECL|macro|__NR_timer_getoverrun
mdefine_line|#define __NR_timer_getoverrun&t;&t;(__NR_Linux + 219)
DECL|macro|__NR_timer_delete
mdefine_line|#define __NR_timer_delete&t;&t;(__NR_Linux + 220)
DECL|macro|__NR_clock_settime
mdefine_line|#define __NR_clock_settime&t;&t;(__NR_Linux + 221)
DECL|macro|__NR_clock_gettime
mdefine_line|#define __NR_clock_gettime&t;&t;(__NR_Linux + 222)
DECL|macro|__NR_clock_getres
mdefine_line|#define __NR_clock_getres&t;&t;(__NR_Linux + 223)
DECL|macro|__NR_clock_nanosleep
mdefine_line|#define __NR_clock_nanosleep&t;&t;(__NR_Linux + 224)
DECL|macro|__NR_tgkill
mdefine_line|#define __NR_tgkill&t;&t;&t;(__NR_Linux + 225)
DECL|macro|__NR_utimes
mdefine_line|#define __NR_utimes&t;&t;&t;(__NR_Linux + 226)
DECL|macro|__NR_mbind
mdefine_line|#define __NR_mbind&t;&t;&t;(__NR_Linux + 227)
DECL|macro|__NR_get_mempolicy
mdefine_line|#define __NR_get_mempolicy&t;&t;(__NR_Linux + 228)
DECL|macro|__NR_set_mempolicy
mdefine_line|#define __NR_set_mempolicy&t;&t;(__NR_Linux + 229)
DECL|macro|__NR_mq_open
mdefine_line|#define __NR_mq_open&t;&t;&t;(__NR_Linux + 230)
DECL|macro|__NR_mq_unlink
mdefine_line|#define __NR_mq_unlink&t;&t;&t;(__NR_Linux + 231)
DECL|macro|__NR_mq_timedsend
mdefine_line|#define __NR_mq_timedsend&t;&t;(__NR_Linux + 232)
DECL|macro|__NR_mq_timedreceive
mdefine_line|#define __NR_mq_timedreceive&t;&t;(__NR_Linux + 233)
DECL|macro|__NR_mq_notify
mdefine_line|#define __NR_mq_notify&t;&t;&t;(__NR_Linux + 234)
DECL|macro|__NR_mq_getsetattr
mdefine_line|#define __NR_mq_getsetattr&t;&t;(__NR_Linux + 235)
DECL|macro|__NR_vserver
mdefine_line|#define __NR_vserver&t;&t;&t;(__NR_Linux + 236)
DECL|macro|__NR_waitid
mdefine_line|#define __NR_waitid&t;&t;&t;(__NR_Linux + 237)
multiline_comment|/* #define __NR_sys_setaltroot&t;&t;(__NR_Linux + 238) */
DECL|macro|__NR_add_key
mdefine_line|#define __NR_add_key&t;&t;&t;(__NR_Linux + 239)
DECL|macro|__NR_request_key
mdefine_line|#define __NR_request_key&t;&t;(__NR_Linux + 240)
DECL|macro|__NR_keyctl
mdefine_line|#define __NR_keyctl&t;&t;&t;(__NR_Linux + 241)
multiline_comment|/*&n; * Offset of the last Linux 64-bit flavoured syscall&n; */
DECL|macro|__NR_Linux_syscalls
mdefine_line|#define __NR_Linux_syscalls&t;&t;241
macro_line|#endif /* _MIPS_SIM == _MIPS_SIM_ABI64 */
DECL|macro|__NR_64_Linux
mdefine_line|#define __NR_64_Linux&t;&t;&t;5000
DECL|macro|__NR_64_Linux_syscalls
mdefine_line|#define __NR_64_Linux_syscalls&t;&t;241
macro_line|#if _MIPS_SIM == _MIPS_SIM_NABI32
multiline_comment|/*&n; * Linux N32 syscalls are in the range from 6000 to 6999.&n; */
DECL|macro|__NR_Linux
mdefine_line|#define __NR_Linux&t;&t;&t;6000
DECL|macro|__NR_read
mdefine_line|#define __NR_read&t;&t;&t;(__NR_Linux +   0)
DECL|macro|__NR_write
mdefine_line|#define __NR_write&t;&t;&t;(__NR_Linux +   1)
DECL|macro|__NR_open
mdefine_line|#define __NR_open&t;&t;&t;(__NR_Linux +   2)
DECL|macro|__NR_close
mdefine_line|#define __NR_close&t;&t;&t;(__NR_Linux +   3)
DECL|macro|__NR_stat
mdefine_line|#define __NR_stat&t;&t;&t;(__NR_Linux +   4)
DECL|macro|__NR_fstat
mdefine_line|#define __NR_fstat&t;&t;&t;(__NR_Linux +   5)
DECL|macro|__NR_lstat
mdefine_line|#define __NR_lstat&t;&t;&t;(__NR_Linux +   6)
DECL|macro|__NR_poll
mdefine_line|#define __NR_poll&t;&t;&t;(__NR_Linux +   7)
DECL|macro|__NR_lseek
mdefine_line|#define __NR_lseek&t;&t;&t;(__NR_Linux +   8)
DECL|macro|__NR_mmap
mdefine_line|#define __NR_mmap&t;&t;&t;(__NR_Linux +   9)
DECL|macro|__NR_mprotect
mdefine_line|#define __NR_mprotect&t;&t;&t;(__NR_Linux +  10)
DECL|macro|__NR_munmap
mdefine_line|#define __NR_munmap&t;&t;&t;(__NR_Linux +  11)
DECL|macro|__NR_brk
mdefine_line|#define __NR_brk&t;&t;&t;(__NR_Linux +  12)
DECL|macro|__NR_rt_sigaction
mdefine_line|#define __NR_rt_sigaction&t;&t;(__NR_Linux +  13)
DECL|macro|__NR_rt_sigprocmask
mdefine_line|#define __NR_rt_sigprocmask&t;&t;(__NR_Linux +  14)
DECL|macro|__NR_ioctl
mdefine_line|#define __NR_ioctl&t;&t;&t;(__NR_Linux +  15)
DECL|macro|__NR_pread64
mdefine_line|#define __NR_pread64&t;&t;&t;(__NR_Linux +  16)
DECL|macro|__NR_pwrite64
mdefine_line|#define __NR_pwrite64&t;&t;&t;(__NR_Linux +  17)
DECL|macro|__NR_readv
mdefine_line|#define __NR_readv&t;&t;&t;(__NR_Linux +  18)
DECL|macro|__NR_writev
mdefine_line|#define __NR_writev&t;&t;&t;(__NR_Linux +  19)
DECL|macro|__NR_access
mdefine_line|#define __NR_access&t;&t;&t;(__NR_Linux +  20)
DECL|macro|__NR_pipe
mdefine_line|#define __NR_pipe&t;&t;&t;(__NR_Linux +  21)
DECL|macro|__NR__newselect
mdefine_line|#define __NR__newselect&t;&t;&t;(__NR_Linux +  22)
DECL|macro|__NR_sched_yield
mdefine_line|#define __NR_sched_yield&t;&t;(__NR_Linux +  23)
DECL|macro|__NR_mremap
mdefine_line|#define __NR_mremap&t;&t;&t;(__NR_Linux +  24)
DECL|macro|__NR_msync
mdefine_line|#define __NR_msync&t;&t;&t;(__NR_Linux +  25)
DECL|macro|__NR_mincore
mdefine_line|#define __NR_mincore&t;&t;&t;(__NR_Linux +  26)
DECL|macro|__NR_madvise
mdefine_line|#define __NR_madvise&t;&t;&t;(__NR_Linux +  27)
DECL|macro|__NR_shmget
mdefine_line|#define __NR_shmget&t;&t;&t;(__NR_Linux +  28)
DECL|macro|__NR_shmat
mdefine_line|#define __NR_shmat&t;&t;&t;(__NR_Linux +  29)
DECL|macro|__NR_shmctl
mdefine_line|#define __NR_shmctl&t;&t;&t;(__NR_Linux +  30)
DECL|macro|__NR_dup
mdefine_line|#define __NR_dup&t;&t;&t;(__NR_Linux +  31)
DECL|macro|__NR_dup2
mdefine_line|#define __NR_dup2&t;&t;&t;(__NR_Linux +  32)
DECL|macro|__NR_pause
mdefine_line|#define __NR_pause&t;&t;&t;(__NR_Linux +  33)
DECL|macro|__NR_nanosleep
mdefine_line|#define __NR_nanosleep&t;&t;&t;(__NR_Linux +  34)
DECL|macro|__NR_getitimer
mdefine_line|#define __NR_getitimer&t;&t;&t;(__NR_Linux +  35)
DECL|macro|__NR_setitimer
mdefine_line|#define __NR_setitimer&t;&t;&t;(__NR_Linux +  36)
DECL|macro|__NR_alarm
mdefine_line|#define __NR_alarm&t;&t;&t;(__NR_Linux +  37)
DECL|macro|__NR_getpid
mdefine_line|#define __NR_getpid&t;&t;&t;(__NR_Linux +  38)
DECL|macro|__NR_sendfile
mdefine_line|#define __NR_sendfile&t;&t;&t;(__NR_Linux +  39)
DECL|macro|__NR_socket
mdefine_line|#define __NR_socket&t;&t;&t;(__NR_Linux +  40)
DECL|macro|__NR_connect
mdefine_line|#define __NR_connect&t;&t;&t;(__NR_Linux +  41)
DECL|macro|__NR_accept
mdefine_line|#define __NR_accept&t;&t;&t;(__NR_Linux +  42)
DECL|macro|__NR_sendto
mdefine_line|#define __NR_sendto&t;&t;&t;(__NR_Linux +  43)
DECL|macro|__NR_recvfrom
mdefine_line|#define __NR_recvfrom&t;&t;&t;(__NR_Linux +  44)
DECL|macro|__NR_sendmsg
mdefine_line|#define __NR_sendmsg&t;&t;&t;(__NR_Linux +  45)
DECL|macro|__NR_recvmsg
mdefine_line|#define __NR_recvmsg&t;&t;&t;(__NR_Linux +  46)
DECL|macro|__NR_shutdown
mdefine_line|#define __NR_shutdown&t;&t;&t;(__NR_Linux +  47)
DECL|macro|__NR_bind
mdefine_line|#define __NR_bind&t;&t;&t;(__NR_Linux +  48)
DECL|macro|__NR_listen
mdefine_line|#define __NR_listen&t;&t;&t;(__NR_Linux +  49)
DECL|macro|__NR_getsockname
mdefine_line|#define __NR_getsockname&t;&t;(__NR_Linux +  50)
DECL|macro|__NR_getpeername
mdefine_line|#define __NR_getpeername&t;&t;(__NR_Linux +  51)
DECL|macro|__NR_socketpair
mdefine_line|#define __NR_socketpair&t;&t;&t;(__NR_Linux +  52)
DECL|macro|__NR_setsockopt
mdefine_line|#define __NR_setsockopt&t;&t;&t;(__NR_Linux +  53)
DECL|macro|__NR_getsockopt
mdefine_line|#define __NR_getsockopt&t;&t;&t;(__NR_Linux +  54)
DECL|macro|__NR_clone
mdefine_line|#define __NR_clone&t;&t;&t;(__NR_Linux +  55)
DECL|macro|__NR_fork
mdefine_line|#define __NR_fork&t;&t;&t;(__NR_Linux +  56)
DECL|macro|__NR_execve
mdefine_line|#define __NR_execve&t;&t;&t;(__NR_Linux +  57)
DECL|macro|__NR_exit
mdefine_line|#define __NR_exit&t;&t;&t;(__NR_Linux +  58)
DECL|macro|__NR_wait4
mdefine_line|#define __NR_wait4&t;&t;&t;(__NR_Linux +  59)
DECL|macro|__NR_kill
mdefine_line|#define __NR_kill&t;&t;&t;(__NR_Linux +  60)
DECL|macro|__NR_uname
mdefine_line|#define __NR_uname&t;&t;&t;(__NR_Linux +  61)
DECL|macro|__NR_semget
mdefine_line|#define __NR_semget&t;&t;&t;(__NR_Linux +  62)
DECL|macro|__NR_semop
mdefine_line|#define __NR_semop&t;&t;&t;(__NR_Linux +  63)
DECL|macro|__NR_semctl
mdefine_line|#define __NR_semctl&t;&t;&t;(__NR_Linux +  64)
DECL|macro|__NR_shmdt
mdefine_line|#define __NR_shmdt&t;&t;&t;(__NR_Linux +  65)
DECL|macro|__NR_msgget
mdefine_line|#define __NR_msgget&t;&t;&t;(__NR_Linux +  66)
DECL|macro|__NR_msgsnd
mdefine_line|#define __NR_msgsnd&t;&t;&t;(__NR_Linux +  67)
DECL|macro|__NR_msgrcv
mdefine_line|#define __NR_msgrcv&t;&t;&t;(__NR_Linux +  68)
DECL|macro|__NR_msgctl
mdefine_line|#define __NR_msgctl&t;&t;&t;(__NR_Linux +  69)
DECL|macro|__NR_fcntl
mdefine_line|#define __NR_fcntl&t;&t;&t;(__NR_Linux +  70)
DECL|macro|__NR_flock
mdefine_line|#define __NR_flock&t;&t;&t;(__NR_Linux +  71)
DECL|macro|__NR_fsync
mdefine_line|#define __NR_fsync&t;&t;&t;(__NR_Linux +  72)
DECL|macro|__NR_fdatasync
mdefine_line|#define __NR_fdatasync&t;&t;&t;(__NR_Linux +  73)
DECL|macro|__NR_truncate
mdefine_line|#define __NR_truncate&t;&t;&t;(__NR_Linux +  74)
DECL|macro|__NR_ftruncate
mdefine_line|#define __NR_ftruncate&t;&t;&t;(__NR_Linux +  75)
DECL|macro|__NR_getdents
mdefine_line|#define __NR_getdents&t;&t;&t;(__NR_Linux +  76)
DECL|macro|__NR_getcwd
mdefine_line|#define __NR_getcwd&t;&t;&t;(__NR_Linux +  77)
DECL|macro|__NR_chdir
mdefine_line|#define __NR_chdir&t;&t;&t;(__NR_Linux +  78)
DECL|macro|__NR_fchdir
mdefine_line|#define __NR_fchdir&t;&t;&t;(__NR_Linux +  79)
DECL|macro|__NR_rename
mdefine_line|#define __NR_rename&t;&t;&t;(__NR_Linux +  80)
DECL|macro|__NR_mkdir
mdefine_line|#define __NR_mkdir&t;&t;&t;(__NR_Linux +  81)
DECL|macro|__NR_rmdir
mdefine_line|#define __NR_rmdir&t;&t;&t;(__NR_Linux +  82)
DECL|macro|__NR_creat
mdefine_line|#define __NR_creat&t;&t;&t;(__NR_Linux +  83)
DECL|macro|__NR_link
mdefine_line|#define __NR_link&t;&t;&t;(__NR_Linux +  84)
DECL|macro|__NR_unlink
mdefine_line|#define __NR_unlink&t;&t;&t;(__NR_Linux +  85)
DECL|macro|__NR_symlink
mdefine_line|#define __NR_symlink&t;&t;&t;(__NR_Linux +  86)
DECL|macro|__NR_readlink
mdefine_line|#define __NR_readlink&t;&t;&t;(__NR_Linux +  87)
DECL|macro|__NR_chmod
mdefine_line|#define __NR_chmod&t;&t;&t;(__NR_Linux +  88)
DECL|macro|__NR_fchmod
mdefine_line|#define __NR_fchmod&t;&t;&t;(__NR_Linux +  89)
DECL|macro|__NR_chown
mdefine_line|#define __NR_chown&t;&t;&t;(__NR_Linux +  90)
DECL|macro|__NR_fchown
mdefine_line|#define __NR_fchown&t;&t;&t;(__NR_Linux +  91)
DECL|macro|__NR_lchown
mdefine_line|#define __NR_lchown&t;&t;&t;(__NR_Linux +  92)
DECL|macro|__NR_umask
mdefine_line|#define __NR_umask&t;&t;&t;(__NR_Linux +  93)
DECL|macro|__NR_gettimeofday
mdefine_line|#define __NR_gettimeofday&t;&t;(__NR_Linux +  94)
DECL|macro|__NR_getrlimit
mdefine_line|#define __NR_getrlimit&t;&t;&t;(__NR_Linux +  95)
DECL|macro|__NR_getrusage
mdefine_line|#define __NR_getrusage&t;&t;&t;(__NR_Linux +  96)
DECL|macro|__NR_sysinfo
mdefine_line|#define __NR_sysinfo&t;&t;&t;(__NR_Linux +  97)
DECL|macro|__NR_times
mdefine_line|#define __NR_times&t;&t;&t;(__NR_Linux +  98)
DECL|macro|__NR_ptrace
mdefine_line|#define __NR_ptrace&t;&t;&t;(__NR_Linux +  99)
DECL|macro|__NR_getuid
mdefine_line|#define __NR_getuid&t;&t;&t;(__NR_Linux + 100)
DECL|macro|__NR_syslog
mdefine_line|#define __NR_syslog&t;&t;&t;(__NR_Linux + 101)
DECL|macro|__NR_getgid
mdefine_line|#define __NR_getgid&t;&t;&t;(__NR_Linux + 102)
DECL|macro|__NR_setuid
mdefine_line|#define __NR_setuid&t;&t;&t;(__NR_Linux + 103)
DECL|macro|__NR_setgid
mdefine_line|#define __NR_setgid&t;&t;&t;(__NR_Linux + 104)
DECL|macro|__NR_geteuid
mdefine_line|#define __NR_geteuid&t;&t;&t;(__NR_Linux + 105)
DECL|macro|__NR_getegid
mdefine_line|#define __NR_getegid&t;&t;&t;(__NR_Linux + 106)
DECL|macro|__NR_setpgid
mdefine_line|#define __NR_setpgid&t;&t;&t;(__NR_Linux + 107)
DECL|macro|__NR_getppid
mdefine_line|#define __NR_getppid&t;&t;&t;(__NR_Linux + 108)
DECL|macro|__NR_getpgrp
mdefine_line|#define __NR_getpgrp&t;&t;&t;(__NR_Linux + 109)
DECL|macro|__NR_setsid
mdefine_line|#define __NR_setsid&t;&t;&t;(__NR_Linux + 110)
DECL|macro|__NR_setreuid
mdefine_line|#define __NR_setreuid&t;&t;&t;(__NR_Linux + 111)
DECL|macro|__NR_setregid
mdefine_line|#define __NR_setregid&t;&t;&t;(__NR_Linux + 112)
DECL|macro|__NR_getgroups
mdefine_line|#define __NR_getgroups&t;&t;&t;(__NR_Linux + 113)
DECL|macro|__NR_setgroups
mdefine_line|#define __NR_setgroups&t;&t;&t;(__NR_Linux + 114)
DECL|macro|__NR_setresuid
mdefine_line|#define __NR_setresuid&t;&t;&t;(__NR_Linux + 115)
DECL|macro|__NR_getresuid
mdefine_line|#define __NR_getresuid&t;&t;&t;(__NR_Linux + 116)
DECL|macro|__NR_setresgid
mdefine_line|#define __NR_setresgid&t;&t;&t;(__NR_Linux + 117)
DECL|macro|__NR_getresgid
mdefine_line|#define __NR_getresgid&t;&t;&t;(__NR_Linux + 118)
DECL|macro|__NR_getpgid
mdefine_line|#define __NR_getpgid&t;&t;&t;(__NR_Linux + 119)
DECL|macro|__NR_setfsuid
mdefine_line|#define __NR_setfsuid&t;&t;&t;(__NR_Linux + 120)
DECL|macro|__NR_setfsgid
mdefine_line|#define __NR_setfsgid&t;&t;&t;(__NR_Linux + 121)
DECL|macro|__NR_getsid
mdefine_line|#define __NR_getsid&t;&t;&t;(__NR_Linux + 122)
DECL|macro|__NR_capget
mdefine_line|#define __NR_capget&t;&t;&t;(__NR_Linux + 123)
DECL|macro|__NR_capset
mdefine_line|#define __NR_capset&t;&t;&t;(__NR_Linux + 124)
DECL|macro|__NR_rt_sigpending
mdefine_line|#define __NR_rt_sigpending&t;&t;(__NR_Linux + 125)
DECL|macro|__NR_rt_sigtimedwait
mdefine_line|#define __NR_rt_sigtimedwait&t;&t;(__NR_Linux + 126)
DECL|macro|__NR_rt_sigqueueinfo
mdefine_line|#define __NR_rt_sigqueueinfo&t;&t;(__NR_Linux + 127)
DECL|macro|__NR_rt_sigsuspend
mdefine_line|#define __NR_rt_sigsuspend&t;&t;(__NR_Linux + 128)
DECL|macro|__NR_sigaltstack
mdefine_line|#define __NR_sigaltstack&t;&t;(__NR_Linux + 129)
DECL|macro|__NR_utime
mdefine_line|#define __NR_utime&t;&t;&t;(__NR_Linux + 130)
DECL|macro|__NR_mknod
mdefine_line|#define __NR_mknod&t;&t;&t;(__NR_Linux + 131)
DECL|macro|__NR_personality
mdefine_line|#define __NR_personality&t;&t;(__NR_Linux + 132)
DECL|macro|__NR_ustat
mdefine_line|#define __NR_ustat&t;&t;&t;(__NR_Linux + 133)
DECL|macro|__NR_statfs
mdefine_line|#define __NR_statfs&t;&t;&t;(__NR_Linux + 134)
DECL|macro|__NR_fstatfs
mdefine_line|#define __NR_fstatfs&t;&t;&t;(__NR_Linux + 135)
DECL|macro|__NR_sysfs
mdefine_line|#define __NR_sysfs&t;&t;&t;(__NR_Linux + 136)
DECL|macro|__NR_getpriority
mdefine_line|#define __NR_getpriority&t;&t;(__NR_Linux + 137)
DECL|macro|__NR_setpriority
mdefine_line|#define __NR_setpriority&t;&t;(__NR_Linux + 138)
DECL|macro|__NR_sched_setparam
mdefine_line|#define __NR_sched_setparam&t;&t;(__NR_Linux + 139)
DECL|macro|__NR_sched_getparam
mdefine_line|#define __NR_sched_getparam&t;&t;(__NR_Linux + 140)
DECL|macro|__NR_sched_setscheduler
mdefine_line|#define __NR_sched_setscheduler&t;&t;(__NR_Linux + 141)
DECL|macro|__NR_sched_getscheduler
mdefine_line|#define __NR_sched_getscheduler&t;&t;(__NR_Linux + 142)
DECL|macro|__NR_sched_get_priority_max
mdefine_line|#define __NR_sched_get_priority_max&t;(__NR_Linux + 143)
DECL|macro|__NR_sched_get_priority_min
mdefine_line|#define __NR_sched_get_priority_min&t;(__NR_Linux + 144)
DECL|macro|__NR_sched_rr_get_interval
mdefine_line|#define __NR_sched_rr_get_interval&t;(__NR_Linux + 145)
DECL|macro|__NR_mlock
mdefine_line|#define __NR_mlock&t;&t;&t;(__NR_Linux + 146)
DECL|macro|__NR_munlock
mdefine_line|#define __NR_munlock&t;&t;&t;(__NR_Linux + 147)
DECL|macro|__NR_mlockall
mdefine_line|#define __NR_mlockall&t;&t;&t;(__NR_Linux + 148)
DECL|macro|__NR_munlockall
mdefine_line|#define __NR_munlockall&t;&t;&t;(__NR_Linux + 149)
DECL|macro|__NR_vhangup
mdefine_line|#define __NR_vhangup&t;&t;&t;(__NR_Linux + 150)
DECL|macro|__NR_pivot_root
mdefine_line|#define __NR_pivot_root&t;&t;&t;(__NR_Linux + 151)
DECL|macro|__NR__sysctl
mdefine_line|#define __NR__sysctl&t;&t;&t;(__NR_Linux + 152)
DECL|macro|__NR_prctl
mdefine_line|#define __NR_prctl&t;&t;&t;(__NR_Linux + 153)
DECL|macro|__NR_adjtimex
mdefine_line|#define __NR_adjtimex&t;&t;&t;(__NR_Linux + 154)
DECL|macro|__NR_setrlimit
mdefine_line|#define __NR_setrlimit&t;&t;&t;(__NR_Linux + 155)
DECL|macro|__NR_chroot
mdefine_line|#define __NR_chroot&t;&t;&t;(__NR_Linux + 156)
DECL|macro|__NR_sync
mdefine_line|#define __NR_sync&t;&t;&t;(__NR_Linux + 157)
DECL|macro|__NR_acct
mdefine_line|#define __NR_acct&t;&t;&t;(__NR_Linux + 158)
DECL|macro|__NR_settimeofday
mdefine_line|#define __NR_settimeofday&t;&t;(__NR_Linux + 159)
DECL|macro|__NR_mount
mdefine_line|#define __NR_mount&t;&t;&t;(__NR_Linux + 160)
DECL|macro|__NR_umount2
mdefine_line|#define __NR_umount2&t;&t;&t;(__NR_Linux + 161)
DECL|macro|__NR_swapon
mdefine_line|#define __NR_swapon&t;&t;&t;(__NR_Linux + 162)
DECL|macro|__NR_swapoff
mdefine_line|#define __NR_swapoff&t;&t;&t;(__NR_Linux + 163)
DECL|macro|__NR_reboot
mdefine_line|#define __NR_reboot&t;&t;&t;(__NR_Linux + 164)
DECL|macro|__NR_sethostname
mdefine_line|#define __NR_sethostname&t;&t;(__NR_Linux + 165)
DECL|macro|__NR_setdomainname
mdefine_line|#define __NR_setdomainname&t;&t;(__NR_Linux + 166)
DECL|macro|__NR_create_module
mdefine_line|#define __NR_create_module&t;&t;(__NR_Linux + 167)
DECL|macro|__NR_init_module
mdefine_line|#define __NR_init_module&t;&t;(__NR_Linux + 168)
DECL|macro|__NR_delete_module
mdefine_line|#define __NR_delete_module&t;&t;(__NR_Linux + 169)
DECL|macro|__NR_get_kernel_syms
mdefine_line|#define __NR_get_kernel_syms&t;&t;(__NR_Linux + 170)
DECL|macro|__NR_query_module
mdefine_line|#define __NR_query_module&t;&t;(__NR_Linux + 171)
DECL|macro|__NR_quotactl
mdefine_line|#define __NR_quotactl&t;&t;&t;(__NR_Linux + 172)
DECL|macro|__NR_nfsservctl
mdefine_line|#define __NR_nfsservctl&t;&t;&t;(__NR_Linux + 173)
DECL|macro|__NR_getpmsg
mdefine_line|#define __NR_getpmsg&t;&t;&t;(__NR_Linux + 174)
DECL|macro|__NR_putpmsg
mdefine_line|#define __NR_putpmsg&t;&t;&t;(__NR_Linux + 175)
DECL|macro|__NR_afs_syscall
mdefine_line|#define __NR_afs_syscall&t;&t;(__NR_Linux + 176)
DECL|macro|__NR_reserved177
mdefine_line|#define __NR_reserved177&t;&t;(__NR_Linux + 177)
DECL|macro|__NR_gettid
mdefine_line|#define __NR_gettid&t;&t;&t;(__NR_Linux + 178)
DECL|macro|__NR_readahead
mdefine_line|#define __NR_readahead&t;&t;&t;(__NR_Linux + 179)
DECL|macro|__NR_setxattr
mdefine_line|#define __NR_setxattr&t;&t;&t;(__NR_Linux + 180)
DECL|macro|__NR_lsetxattr
mdefine_line|#define __NR_lsetxattr&t;&t;&t;(__NR_Linux + 181)
DECL|macro|__NR_fsetxattr
mdefine_line|#define __NR_fsetxattr&t;&t;&t;(__NR_Linux + 182)
DECL|macro|__NR_getxattr
mdefine_line|#define __NR_getxattr&t;&t;&t;(__NR_Linux + 183)
DECL|macro|__NR_lgetxattr
mdefine_line|#define __NR_lgetxattr&t;&t;&t;(__NR_Linux + 184)
DECL|macro|__NR_fgetxattr
mdefine_line|#define __NR_fgetxattr&t;&t;&t;(__NR_Linux + 185)
DECL|macro|__NR_listxattr
mdefine_line|#define __NR_listxattr&t;&t;&t;(__NR_Linux + 186)
DECL|macro|__NR_llistxattr
mdefine_line|#define __NR_llistxattr&t;&t;&t;(__NR_Linux + 187)
DECL|macro|__NR_flistxattr
mdefine_line|#define __NR_flistxattr&t;&t;&t;(__NR_Linux + 188)
DECL|macro|__NR_removexattr
mdefine_line|#define __NR_removexattr&t;&t;(__NR_Linux + 189)
DECL|macro|__NR_lremovexattr
mdefine_line|#define __NR_lremovexattr&t;&t;(__NR_Linux + 190)
DECL|macro|__NR_fremovexattr
mdefine_line|#define __NR_fremovexattr&t;&t;(__NR_Linux + 191)
DECL|macro|__NR_tkill
mdefine_line|#define __NR_tkill&t;&t;&t;(__NR_Linux + 192)
DECL|macro|__NR_reserved193
mdefine_line|#define __NR_reserved193&t;&t;(__NR_Linux + 193)
DECL|macro|__NR_futex
mdefine_line|#define __NR_futex&t;&t;&t;(__NR_Linux + 194)
DECL|macro|__NR_sched_setaffinity
mdefine_line|#define __NR_sched_setaffinity&t;&t;(__NR_Linux + 195)
DECL|macro|__NR_sched_getaffinity
mdefine_line|#define __NR_sched_getaffinity&t;&t;(__NR_Linux + 196)
DECL|macro|__NR_cacheflush
mdefine_line|#define __NR_cacheflush&t;&t;&t;(__NR_Linux + 197)
DECL|macro|__NR_cachectl
mdefine_line|#define __NR_cachectl&t;&t;&t;(__NR_Linux + 198)
DECL|macro|__NR_sysmips
mdefine_line|#define __NR_sysmips&t;&t;&t;(__NR_Linux + 199)
DECL|macro|__NR_io_setup
mdefine_line|#define __NR_io_setup&t;&t;&t;(__NR_Linux + 200)
DECL|macro|__NR_io_destroy
mdefine_line|#define __NR_io_destroy&t;&t;&t;(__NR_Linux + 201)
DECL|macro|__NR_io_getevents
mdefine_line|#define __NR_io_getevents&t;&t;(__NR_Linux + 202)
DECL|macro|__NR_io_submit
mdefine_line|#define __NR_io_submit&t;&t;&t;(__NR_Linux + 203)
DECL|macro|__NR_io_cancel
mdefine_line|#define __NR_io_cancel&t;&t;&t;(__NR_Linux + 204)
DECL|macro|__NR_exit_group
mdefine_line|#define __NR_exit_group&t;&t;&t;(__NR_Linux + 205)
DECL|macro|__NR_lookup_dcookie
mdefine_line|#define __NR_lookup_dcookie&t;&t;(__NR_Linux + 206)
DECL|macro|__NR_epoll_create
mdefine_line|#define __NR_epoll_create&t;&t;(__NR_Linux + 207)
DECL|macro|__NR_epoll_ctl
mdefine_line|#define __NR_epoll_ctl&t;&t;&t;(__NR_Linux + 208)
DECL|macro|__NR_epoll_wait
mdefine_line|#define __NR_epoll_wait&t;&t;&t;(__NR_Linux + 209)
DECL|macro|__NR_remap_file_pages
mdefine_line|#define __NR_remap_file_pages&t;&t;(__NR_Linux + 210)
DECL|macro|__NR_rt_sigreturn
mdefine_line|#define __NR_rt_sigreturn&t;&t;(__NR_Linux + 211)
DECL|macro|__NR_fcntl64
mdefine_line|#define __NR_fcntl64&t;&t;&t;(__NR_Linux + 212)
DECL|macro|__NR_set_tid_address
mdefine_line|#define __NR_set_tid_address&t;&t;(__NR_Linux + 213)
DECL|macro|__NR_restart_syscall
mdefine_line|#define __NR_restart_syscall&t;&t;(__NR_Linux + 214)
DECL|macro|__NR_semtimedop
mdefine_line|#define __NR_semtimedop&t;&t;&t;(__NR_Linux + 215)
DECL|macro|__NR_fadvise64
mdefine_line|#define __NR_fadvise64&t;&t;&t;(__NR_Linux + 216)
DECL|macro|__NR_statfs64
mdefine_line|#define __NR_statfs64&t;&t;&t;(__NR_Linux + 217)
DECL|macro|__NR_fstatfs64
mdefine_line|#define __NR_fstatfs64&t;&t;&t;(__NR_Linux + 218)
DECL|macro|__NR_sendfile64
mdefine_line|#define __NR_sendfile64&t;&t;&t;(__NR_Linux + 219)
DECL|macro|__NR_timer_create
mdefine_line|#define __NR_timer_create&t;&t;(__NR_Linux + 220)
DECL|macro|__NR_timer_settime
mdefine_line|#define __NR_timer_settime&t;&t;(__NR_Linux + 221)
DECL|macro|__NR_timer_gettime
mdefine_line|#define __NR_timer_gettime&t;&t;(__NR_Linux + 222)
DECL|macro|__NR_timer_getoverrun
mdefine_line|#define __NR_timer_getoverrun&t;&t;(__NR_Linux + 223)
DECL|macro|__NR_timer_delete
mdefine_line|#define __NR_timer_delete&t;&t;(__NR_Linux + 224)
DECL|macro|__NR_clock_settime
mdefine_line|#define __NR_clock_settime&t;&t;(__NR_Linux + 225)
DECL|macro|__NR_clock_gettime
mdefine_line|#define __NR_clock_gettime&t;&t;(__NR_Linux + 226)
DECL|macro|__NR_clock_getres
mdefine_line|#define __NR_clock_getres&t;&t;(__NR_Linux + 227)
DECL|macro|__NR_clock_nanosleep
mdefine_line|#define __NR_clock_nanosleep&t;&t;(__NR_Linux + 228)
DECL|macro|__NR_tgkill
mdefine_line|#define __NR_tgkill&t;&t;&t;(__NR_Linux + 229)
DECL|macro|__NR_utimes
mdefine_line|#define __NR_utimes&t;&t;&t;(__NR_Linux + 230)
DECL|macro|__NR_mbind
mdefine_line|#define __NR_mbind&t;&t;&t;(__NR_Linux + 231)
DECL|macro|__NR_get_mempolicy
mdefine_line|#define __NR_get_mempolicy&t;&t;(__NR_Linux + 232)
DECL|macro|__NR_set_mempolicy
mdefine_line|#define __NR_set_mempolicy&t;&t;(__NR_Linux + 233)
DECL|macro|__NR_mq_open
mdefine_line|#define __NR_mq_open&t;&t;&t;(__NR_Linux + 234)
DECL|macro|__NR_mq_unlink
mdefine_line|#define __NR_mq_unlink&t;&t;&t;(__NR_Linux + 235)
DECL|macro|__NR_mq_timedsend
mdefine_line|#define __NR_mq_timedsend&t;&t;(__NR_Linux + 236)
DECL|macro|__NR_mq_timedreceive
mdefine_line|#define __NR_mq_timedreceive&t;&t;(__NR_Linux + 237)
DECL|macro|__NR_mq_notify
mdefine_line|#define __NR_mq_notify&t;&t;&t;(__NR_Linux + 238)
DECL|macro|__NR_mq_getsetattr
mdefine_line|#define __NR_mq_getsetattr&t;&t;(__NR_Linux + 239)
DECL|macro|__NR_vserver
mdefine_line|#define __NR_vserver&t;&t;&t;(__NR_Linux + 240)
DECL|macro|__NR_waitid
mdefine_line|#define __NR_waitid&t;&t;&t;(__NR_Linux + 241)
multiline_comment|/* #define __NR_sys_setaltroot&t;&t;(__NR_Linux + 242) */
DECL|macro|__NR_add_key
mdefine_line|#define __NR_add_key&t;&t;&t;(__NR_Linux + 243)
DECL|macro|__NR_request_key
mdefine_line|#define __NR_request_key&t;&t;(__NR_Linux + 244)
DECL|macro|__NR_keyctl
mdefine_line|#define __NR_keyctl&t;&t;&t;(__NR_Linux + 245)
multiline_comment|/*&n; * Offset of the last N32 flavoured syscall&n; */
DECL|macro|__NR_Linux_syscalls
mdefine_line|#define __NR_Linux_syscalls&t;&t;245
macro_line|#endif /* _MIPS_SIM == _MIPS_SIM_NABI32 */
DECL|macro|__NR_N32_Linux
mdefine_line|#define __NR_N32_Linux&t;&t;&t;6000
DECL|macro|__NR_N32_Linux_syscalls
mdefine_line|#define __NR_N32_Linux_syscalls&t;&t;245
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/* XXX - _foo needs to be __foo, while __NR_bar could be _NR_bar. */
DECL|macro|_syscall0
mdefine_line|#define _syscall0(type,name) &bslash;&n;type name(void) &bslash;&n;{ &bslash;&n;&t;register unsigned long __a3 asm(&quot;$7&quot;); &bslash;&n;&t;unsigned long __v0; &bslash;&n;&t;&bslash;&n;&t;__asm__ volatile ( &bslash;&n;&t;&quot;.set&bslash;tnoreorder&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;li&bslash;t$2, %2&bslash;t&bslash;t&bslash;t# &quot; #name &quot;&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;syscall&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;move&bslash;t%0, $2&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;.set&bslash;treorder&quot; &bslash;&n;&t;: &quot;=&amp;r&quot; (__v0), &quot;=r&quot; (__a3) &bslash;&n;&t;: &quot;i&quot; (__NR_##name) &bslash;&n;&t;: &quot;$2&quot;, &quot;$8&quot;, &quot;$9&quot;, &quot;$10&quot;, &quot;$11&quot;, &quot;$12&quot;, &quot;$13&quot;, &quot;$14&quot;, &quot;$15&quot;, &quot;$24&quot;, &bslash;&n;&t;  &quot;memory&quot;); &bslash;&n;&t;&bslash;&n;&t;if (__a3 == 0) &bslash;&n;&t;&t;return (type) __v0; &bslash;&n;&t;errno = __v0; &bslash;&n;&t;return (type) -1; &bslash;&n;}
multiline_comment|/*&n; * DANGER: This macro isn&squot;t usable for the pipe(2) call&n; * which has a unusual return convention.&n; */
DECL|macro|_syscall1
mdefine_line|#define _syscall1(type,name,atype,a) &bslash;&n;type name(atype a) &bslash;&n;{ &bslash;&n;&t;register unsigned long __a0 asm(&quot;$4&quot;) = (unsigned long) a; &bslash;&n;&t;register unsigned long __a3 asm(&quot;$7&quot;); &bslash;&n;&t;unsigned long __v0; &bslash;&n;&t;&bslash;&n;&t;__asm__ volatile ( &bslash;&n;&t;&quot;.set&bslash;tnoreorder&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;li&bslash;t$2, %3&bslash;t&bslash;t&bslash;t# &quot; #name &quot;&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;syscall&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;move&bslash;t%0, $2&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;.set&bslash;treorder&quot; &bslash;&n;&t;: &quot;=&amp;r&quot; (__v0), &quot;=r&quot; (__a3) &bslash;&n;&t;: &quot;r&quot; (__a0), &quot;i&quot; (__NR_##name) &bslash;&n;&t;: &quot;$2&quot;, &quot;$8&quot;, &quot;$9&quot;, &quot;$10&quot;, &quot;$11&quot;, &quot;$12&quot;, &quot;$13&quot;, &quot;$14&quot;, &quot;$15&quot;, &quot;$24&quot;, &bslash;&n;&t;  &quot;memory&quot;); &bslash;&n;&t;&bslash;&n;&t;if (__a3 == 0) &bslash;&n;&t;&t;return (type) __v0; &bslash;&n;&t;errno = __v0; &bslash;&n;&t;return (type) -1; &bslash;&n;}
DECL|macro|_syscall2
mdefine_line|#define _syscall2(type,name,atype,a,btype,b) &bslash;&n;type name(atype a, btype b) &bslash;&n;{ &bslash;&n;&t;register unsigned long __a0 asm(&quot;$4&quot;) = (unsigned long) a; &bslash;&n;&t;register unsigned long __a1 asm(&quot;$5&quot;) = (unsigned long) b; &bslash;&n;&t;register unsigned long __a3 asm(&quot;$7&quot;); &bslash;&n;&t;unsigned long __v0; &bslash;&n;&t;&bslash;&n;&t;__asm__ volatile ( &bslash;&n;&t;&quot;.set&bslash;tnoreorder&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;li&bslash;t$2, %4&bslash;t&bslash;t&bslash;t# &quot; #name &quot;&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;syscall&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;move&bslash;t%0, $2&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;.set&bslash;treorder&quot; &bslash;&n;&t;: &quot;=&amp;r&quot; (__v0), &quot;=r&quot; (__a3) &bslash;&n;&t;: &quot;r&quot; (__a0), &quot;r&quot; (__a1), &quot;i&quot; (__NR_##name) &bslash;&n;&t;: &quot;$2&quot;, &quot;$8&quot;, &quot;$9&quot;, &quot;$10&quot;, &quot;$11&quot;, &quot;$12&quot;, &quot;$13&quot;, &quot;$14&quot;, &quot;$15&quot;, &quot;$24&quot;, &bslash;&n;&t;  &quot;memory&quot;); &bslash;&n;&t;&bslash;&n;&t;if (__a3 == 0) &bslash;&n;&t;&t;return (type) __v0; &bslash;&n;&t;errno = __v0; &bslash;&n;&t;return (type) -1; &bslash;&n;}
DECL|macro|_syscall3
mdefine_line|#define _syscall3(type,name,atype,a,btype,b,ctype,c) &bslash;&n;type name(atype a, btype b, ctype c) &bslash;&n;{ &bslash;&n;&t;register unsigned long __a0 asm(&quot;$4&quot;) = (unsigned long) a; &bslash;&n;&t;register unsigned long __a1 asm(&quot;$5&quot;) = (unsigned long) b; &bslash;&n;&t;register unsigned long __a2 asm(&quot;$6&quot;) = (unsigned long) c; &bslash;&n;&t;register unsigned long __a3 asm(&quot;$7&quot;); &bslash;&n;&t;unsigned long __v0; &bslash;&n;&t;&bslash;&n;&t;__asm__ volatile ( &bslash;&n;&t;&quot;.set&bslash;tnoreorder&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;li&bslash;t$2, %5&bslash;t&bslash;t&bslash;t# &quot; #name &quot;&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;syscall&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;move&bslash;t%0, $2&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;.set&bslash;treorder&quot; &bslash;&n;&t;: &quot;=&amp;r&quot; (__v0), &quot;=r&quot; (__a3) &bslash;&n;&t;: &quot;r&quot; (__a0), &quot;r&quot; (__a1), &quot;r&quot; (__a2), &quot;i&quot; (__NR_##name) &bslash;&n;&t;: &quot;$2&quot;, &quot;$8&quot;, &quot;$9&quot;, &quot;$10&quot;, &quot;$11&quot;, &quot;$12&quot;, &quot;$13&quot;, &quot;$14&quot;, &quot;$15&quot;, &quot;$24&quot;, &bslash;&n;&t;  &quot;memory&quot;); &bslash;&n;&t;&bslash;&n;&t;if (__a3 == 0) &bslash;&n;&t;&t;return (type) __v0; &bslash;&n;&t;errno = __v0; &bslash;&n;&t;return (type) -1; &bslash;&n;}
DECL|macro|_syscall4
mdefine_line|#define _syscall4(type,name,atype,a,btype,b,ctype,c,dtype,d) &bslash;&n;type name(atype a, btype b, ctype c, dtype d) &bslash;&n;{ &bslash;&n;&t;register unsigned long __a0 asm(&quot;$4&quot;) = (unsigned long) a; &bslash;&n;&t;register unsigned long __a1 asm(&quot;$5&quot;) = (unsigned long) b; &bslash;&n;&t;register unsigned long __a2 asm(&quot;$6&quot;) = (unsigned long) c; &bslash;&n;&t;register unsigned long __a3 asm(&quot;$7&quot;) = (unsigned long) d; &bslash;&n;&t;unsigned long __v0; &bslash;&n;&t;&bslash;&n;&t;__asm__ volatile ( &bslash;&n;&t;&quot;.set&bslash;tnoreorder&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;li&bslash;t$2, %5&bslash;t&bslash;t&bslash;t# &quot; #name &quot;&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;syscall&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;move&bslash;t%0, $2&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;.set&bslash;treorder&quot; &bslash;&n;&t;: &quot;=&amp;r&quot; (__v0), &quot;+r&quot; (__a3) &bslash;&n;&t;: &quot;r&quot; (__a0), &quot;r&quot; (__a1), &quot;r&quot; (__a2), &quot;i&quot; (__NR_##name) &bslash;&n;&t;: &quot;$2&quot;, &quot;$8&quot;, &quot;$9&quot;, &quot;$10&quot;, &quot;$11&quot;, &quot;$12&quot;, &quot;$13&quot;, &quot;$14&quot;, &quot;$15&quot;, &quot;$24&quot;, &bslash;&n;&t;  &quot;memory&quot;); &bslash;&n;&t;&bslash;&n;&t;if (__a3 == 0) &bslash;&n;&t;&t;return (type) __v0; &bslash;&n;&t;errno = __v0; &bslash;&n;&t;return (type) -1; &bslash;&n;}
macro_line|#if (_MIPS_SIM == _MIPS_SIM_ABI32)
multiline_comment|/*&n; * Using those means your brain needs more than an oil change ;-)&n; */
DECL|macro|_syscall5
mdefine_line|#define _syscall5(type,name,atype,a,btype,b,ctype,c,dtype,d,etype,e) &bslash;&n;type name(atype a, btype b, ctype c, dtype d, etype e) &bslash;&n;{ &bslash;&n;&t;register unsigned long __a0 asm(&quot;$4&quot;) = (unsigned long) a; &bslash;&n;&t;register unsigned long __a1 asm(&quot;$5&quot;) = (unsigned long) b; &bslash;&n;&t;register unsigned long __a2 asm(&quot;$6&quot;) = (unsigned long) c; &bslash;&n;&t;register unsigned long __a3 asm(&quot;$7&quot;) = (unsigned long) d; &bslash;&n;&t;unsigned long __v0; &bslash;&n;&t;&bslash;&n;&t;__asm__ volatile ( &bslash;&n;&t;&quot;.set&bslash;tnoreorder&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;lw&bslash;t$2, %6&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;subu&bslash;t$29, 32&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;sw&bslash;t$2, 16($29)&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;li&bslash;t$2, %5&bslash;t&bslash;t&bslash;t# &quot; #name &quot;&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;syscall&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;move&bslash;t%0, $2&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;addiu&bslash;t$29, 32&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;.set&bslash;treorder&quot; &bslash;&n;&t;: &quot;=&amp;r&quot; (__v0), &quot;+r&quot; (__a3) &bslash;&n;&t;: &quot;r&quot; (__a0), &quot;r&quot; (__a1), &quot;r&quot; (__a2), &quot;i&quot; (__NR_##name), &bslash;&n;&t;  &quot;m&quot; ((unsigned long)e) &bslash;&n;&t;: &quot;$2&quot;, &quot;$8&quot;, &quot;$9&quot;, &quot;$10&quot;, &quot;$11&quot;, &quot;$12&quot;, &quot;$13&quot;, &quot;$14&quot;, &quot;$15&quot;, &quot;$24&quot;, &bslash;&n;&t;  &quot;memory&quot;); &bslash;&n;&t;&bslash;&n;&t;if (__a3 == 0) &bslash;&n;&t;&t;return (type) __v0; &bslash;&n;&t;errno = __v0; &bslash;&n;&t;return (type) -1; &bslash;&n;}
DECL|macro|_syscall6
mdefine_line|#define _syscall6(type,name,atype,a,btype,b,ctype,c,dtype,d,etype,e,ftype,f) &bslash;&n;type name(atype a, btype b, ctype c, dtype d, etype e, ftype f) &bslash;&n;{ &bslash;&n;&t;register unsigned long __a0 asm(&quot;$4&quot;) = (unsigned long) a; &bslash;&n;&t;register unsigned long __a1 asm(&quot;$5&quot;) = (unsigned long) b; &bslash;&n;&t;register unsigned long __a2 asm(&quot;$6&quot;) = (unsigned long) c; &bslash;&n;&t;register unsigned long __a3 asm(&quot;$7&quot;) = (unsigned long) d; &bslash;&n;&t;unsigned long __v0; &bslash;&n;&t;&bslash;&n;&t;__asm__ volatile ( &bslash;&n;&t;&quot;.set&bslash;tnoreorder&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;lw&bslash;t$2, %6&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;lw&bslash;t$8, %7&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;subu&bslash;t$29, 32&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;sw&bslash;t$2, 16($29)&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;sw&bslash;t$8, 20($29)&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;li&bslash;t$2, %5&bslash;t&bslash;t&bslash;t# &quot; #name &quot;&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;syscall&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;move&bslash;t%0, $2&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;addiu&bslash;t$29, 32&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;.set&bslash;treorder&quot; &bslash;&n;&t;: &quot;=&amp;r&quot; (__v0), &quot;+r&quot; (__a3) &bslash;&n;&t;: &quot;r&quot; (__a0), &quot;r&quot; (__a1), &quot;r&quot; (__a2), &quot;i&quot; (__NR_##name), &bslash;&n;&t;  &quot;m&quot; ((unsigned long)e), &quot;m&quot; ((unsigned long)f) &bslash;&n;&t;: &quot;$2&quot;, &quot;$8&quot;, &quot;$9&quot;, &quot;$10&quot;, &quot;$11&quot;, &quot;$12&quot;, &quot;$13&quot;, &quot;$14&quot;, &quot;$15&quot;, &quot;$24&quot;, &bslash;&n;&t;  &quot;memory&quot;); &bslash;&n;&t;&bslash;&n;&t;if (__a3 == 0) &bslash;&n;&t;&t;return (type) __v0; &bslash;&n;&t;errno = __v0; &bslash;&n;&t;return (type) -1; &bslash;&n;}
macro_line|#endif /* (_MIPS_SIM == _MIPS_SIM_ABI32) */
macro_line|#if (_MIPS_SIM == _MIPS_SIM_NABI32) || (_MIPS_SIM == _MIPS_SIM_ABI64)
DECL|macro|_syscall5
mdefine_line|#define _syscall5(type,name,atype,a,btype,b,ctype,c,dtype,d,etype,e) &bslash;&n;type name (atype a,btype b,ctype c,dtype d,etype e) &bslash;&n;{ &bslash;&n;&t;register unsigned long __a0 asm(&quot;$4&quot;) = (unsigned long) a; &bslash;&n;&t;register unsigned long __a1 asm(&quot;$5&quot;) = (unsigned long) b; &bslash;&n;&t;register unsigned long __a2 asm(&quot;$6&quot;) = (unsigned long) c; &bslash;&n;&t;register unsigned long __a3 asm(&quot;$7&quot;) = (unsigned long) d; &bslash;&n;&t;register unsigned long __a4 asm(&quot;$8&quot;) = (unsigned long) e; &bslash;&n;&t;unsigned long __v0; &bslash;&n;&t;&bslash;&n;&t;__asm__ volatile ( &bslash;&n;&t;&quot;.set&bslash;tnoreorder&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;li&bslash;t$2, %6&bslash;t&bslash;t&bslash;t# &quot; #name &quot;&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;syscall&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;move&bslash;t%0, $2&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;.set&bslash;treorder&quot; &bslash;&n;&t;: &quot;=&amp;r&quot; (__v0), &quot;+r&quot; (__a3) &bslash;&n;&t;: &quot;r&quot; (__a0), &quot;r&quot; (__a1), &quot;r&quot; (__a2), &quot;r&quot; (__a4), &quot;i&quot; (__NR_##name) &bslash;&n;&t;: &quot;$2&quot;, &quot;$9&quot;, &quot;$10&quot;, &quot;$11&quot;, &quot;$12&quot;, &quot;$13&quot;, &quot;$14&quot;, &quot;$15&quot;, &quot;$24&quot;, &bslash;&n;&t;  &quot;memory&quot;); &bslash;&n;&t;&bslash;&n;&t;if (__a3 == 0) &bslash;&n;&t;&t;return (type) __v0; &bslash;&n;&t;errno = __v0; &bslash;&n;&t;return (type) -1; &bslash;&n;}
DECL|macro|_syscall6
mdefine_line|#define _syscall6(type,name,atype,a,btype,b,ctype,c,dtype,d,etype,e,ftype,f) &bslash;&n;type name (atype a,btype b,ctype c,dtype d,etype e,ftype f) &bslash;&n;{ &bslash;&n;&t;register unsigned long __a0 asm(&quot;$4&quot;) = (unsigned long) a; &bslash;&n;&t;register unsigned long __a1 asm(&quot;$5&quot;) = (unsigned long) b; &bslash;&n;&t;register unsigned long __a2 asm(&quot;$6&quot;) = (unsigned long) c; &bslash;&n;&t;register unsigned long __a3 asm(&quot;$7&quot;) = (unsigned long) d; &bslash;&n;&t;register unsigned long __a4 asm(&quot;$8&quot;) = (unsigned long) e; &bslash;&n;&t;register unsigned long __a5 asm(&quot;$9&quot;) = (unsigned long) f; &bslash;&n;&t;unsigned long __v0; &bslash;&n;&t;&bslash;&n;&t;__asm__ volatile ( &bslash;&n;&t;&quot;.set&bslash;tnoreorder&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;li&bslash;t$2, %7&bslash;t&bslash;t&bslash;t# &quot; #name &quot;&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;syscall&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;move&bslash;t%0, $2&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;.set&bslash;treorder&quot; &bslash;&n;&t;: &quot;=&amp;r&quot; (__v0), &quot;+r&quot; (__a3) &bslash;&n;&t;: &quot;r&quot; (__a0), &quot;r&quot; (__a1), &quot;r&quot; (__a2), &quot;r&quot; (__a4), &quot;r&quot; (__a5), &bslash;&n;&t;  &quot;i&quot; (__NR_##name) &bslash;&n;&t;: &quot;$2&quot;, &quot;$9&quot;, &quot;$10&quot;, &quot;$11&quot;, &quot;$12&quot;, &quot;$13&quot;, &quot;$14&quot;, &quot;$15&quot;, &quot;$24&quot;, &bslash;&n;&t;  &quot;memory&quot;); &bslash;&n;&t;&bslash;&n;&t;if (__a3 == 0) &bslash;&n;&t;&t;return (type) __v0; &bslash;&n;&t;errno = __v0; &bslash;&n;&t;return (type) -1; &bslash;&n;}
macro_line|#endif /* (_MIPS_SIM == _MIPS_SIM_NABI32) || (_MIPS_SIM == _MIPS_SIM_ABI64) */
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
DECL|macro|__ARCH_WANT_SYS_SGETMASK
mdefine_line|#define __ARCH_WANT_SYS_SGETMASK
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
macro_line|# ifndef __mips64
DECL|macro|__ARCH_WANT_STAT64
macro_line|#  define __ARCH_WANT_STAT64
macro_line|# endif
macro_line|# ifdef CONFIG_MIPS32
DECL|macro|__ARCH_WANT_SYS_TIME
macro_line|#  define __ARCH_WANT_SYS_TIME
macro_line|# endif
macro_line|# ifdef CONFIG_MIPS32_O32
DECL|macro|__ARCH_WANT_COMPAT_SYS_TIME
macro_line|#  define __ARCH_WANT_COMPAT_SYS_TIME
macro_line|# endif
macro_line|#endif
macro_line|#ifdef __KERNEL_SYSCALLS__
macro_line|#include &lt;linux/compiler.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/linkage.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/sim.h&gt;
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
id|prot
comma
r_int
id|flags
comma
r_int
id|fd
comma
id|off_t
id|offset
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
id|nabi_no_regargs
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
id|nabi_no_regargs
r_struct
id|pt_regs
id|regs
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
macro_line|#endif /* __KERNEL_SYSCALLS__ */
macro_line|#endif /* !__ASSEMBLY__ */
multiline_comment|/*&n; * &quot;Conditional&quot; syscalls&n; *&n; * What we want is __attribute__((weak,alias(&quot;sys_ni_syscall&quot;))),&n; * but it doesn&squot;t work on all toolchains, so we just do it by hand&n; */
DECL|macro|cond_syscall
mdefine_line|#define cond_syscall(x) asm(&quot;.weak&bslash;t&quot; #x &quot;&bslash;n&quot; #x &quot;&bslash;t=&bslash;tsys_ni_syscall&quot;);
macro_line|#endif /* _ASM_UNISTD_H */
eof
