multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1995, 96, 97, 98, 99, 2000 by Ralf Baechle&n; * Copyright (C) 1999, 2000 Silicon Graphics, Inc.&n; *&n; * Changed system calls macros _syscall5 - _syscall7 to push args 5 to 7 onto&n; * the stack. Robin Farine for ACN S.A, Copyright (C) 1996 by ACN S.A&n; */
macro_line|#ifndef _ASM_UNISTD_H
DECL|macro|_ASM_UNISTD_H
mdefine_line|#define _ASM_UNISTD_H
multiline_comment|/*&n; * Linux o32 style syscalls are in the range from 4000 to 4999.&n; */
DECL|macro|__NR_O32_Linux
mdefine_line|#define __NR_O32_Linux&t;&t;&t;4000
DECL|macro|__NR_O32_syscall
mdefine_line|#define __NR_O32_syscall&t;&t;(__NR_O32_Linux +   0)
DECL|macro|__NR_O32_exit
mdefine_line|#define __NR_O32_exit&t;&t;&t;(__NR_O32_Linux +   1)
DECL|macro|__NR_O32_fork
mdefine_line|#define __NR_O32_fork&t;&t;&t;(__NR_O32_Linux +   2)
DECL|macro|__NR_O32_read
mdefine_line|#define __NR_O32_read&t;&t;&t;(__NR_O32_Linux +   3)
DECL|macro|__NR_O32_write
mdefine_line|#define __NR_O32_write&t;&t;&t;(__NR_O32_Linux +   4)
DECL|macro|__NR_O32_open
mdefine_line|#define __NR_O32_open&t;&t;&t;(__NR_O32_Linux +   5)
DECL|macro|__NR_O32_close
mdefine_line|#define __NR_O32_close&t;&t;&t;(__NR_O32_Linux +   6)
DECL|macro|__NR_O32_waitpid
mdefine_line|#define __NR_O32_waitpid&t;&t;(__NR_O32_Linux +   7)
DECL|macro|__NR_O32_creat
mdefine_line|#define __NR_O32_creat&t;&t;&t;(__NR_O32_Linux +   8)
DECL|macro|__NR_O32_link
mdefine_line|#define __NR_O32_link&t;&t;&t;(__NR_O32_Linux +   9)
DECL|macro|__NR_O32_unlink
mdefine_line|#define __NR_O32_unlink&t;&t;&t;(__NR_O32_Linux +  10)
DECL|macro|__NR_O32_execve
mdefine_line|#define __NR_O32_execve&t;&t;&t;(__NR_O32_Linux +  11)
DECL|macro|__NR_O32_chdir
mdefine_line|#define __NR_O32_chdir&t;&t;&t;(__NR_O32_Linux +  12)
DECL|macro|__NR_O32_time
mdefine_line|#define __NR_O32_time&t;&t;&t;(__NR_O32_Linux +  13)
DECL|macro|__NR_O32_mknod
mdefine_line|#define __NR_O32_mknod&t;&t;&t;(__NR_O32_Linux +  14)
DECL|macro|__NR_O32_chmod
mdefine_line|#define __NR_O32_chmod&t;&t;&t;(__NR_O32_Linux +  15)
DECL|macro|__NR_O32_lchown
mdefine_line|#define __NR_O32_lchown&t;&t;&t;(__NR_O32_Linux +  16)
DECL|macro|__NR_O32_break
mdefine_line|#define __NR_O32_break&t;&t;&t;(__NR_O32_Linux +  17)
DECL|macro|__NR_O32_unused18
mdefine_line|#define __NR_O32_unused18&t;&t;(__NR_O32_Linux +  18)
DECL|macro|__NR_O32_lseek
mdefine_line|#define __NR_O32_lseek&t;&t;&t;(__NR_O32_Linux +  19)
DECL|macro|__NR_O32_getpid
mdefine_line|#define __NR_O32_getpid&t;&t;&t;(__NR_O32_Linux +  20)
DECL|macro|__NR_O32_mount
mdefine_line|#define __NR_O32_mount&t;&t;&t;(__NR_O32_Linux +  21)
DECL|macro|__NR_O32_umount
mdefine_line|#define __NR_O32_umount&t;&t;&t;(__NR_O32_Linux +  22)
DECL|macro|__NR_O32_setuid
mdefine_line|#define __NR_O32_setuid&t;&t;&t;(__NR_O32_Linux +  23)
DECL|macro|__NR_O32_getuid
mdefine_line|#define __NR_O32_getuid&t;&t;&t;(__NR_O32_Linux +  24)
DECL|macro|__NR_O32_stime
mdefine_line|#define __NR_O32_stime&t;&t;&t;(__NR_O32_Linux +  25)
DECL|macro|__NR_O32_ptrace
mdefine_line|#define __NR_O32_ptrace&t;&t;&t;(__NR_O32_Linux +  26)
DECL|macro|__NR_O32_alarm
mdefine_line|#define __NR_O32_alarm&t;&t;&t;(__NR_O32_Linux +  27)
DECL|macro|__NR_O32_unused28
mdefine_line|#define __NR_O32_unused28&t;&t;(__NR_O32_Linux +  28)
DECL|macro|__NR_O32_pause
mdefine_line|#define __NR_O32_pause&t;&t;&t;(__NR_O32_Linux +  29)
DECL|macro|__NR_O32_utime
mdefine_line|#define __NR_O32_utime&t;&t;&t;(__NR_O32_Linux +  30)
DECL|macro|__NR_O32_stty
mdefine_line|#define __NR_O32_stty&t;&t;&t;(__NR_O32_Linux +  31)
DECL|macro|__NR_O32_gtty
mdefine_line|#define __NR_O32_gtty&t;&t;&t;(__NR_O32_Linux +  32)
DECL|macro|__NR_O32_access
mdefine_line|#define __NR_O32_access&t;&t;&t;(__NR_O32_Linux +  33)
DECL|macro|__NR_O32_nice
mdefine_line|#define __NR_O32_nice&t;&t;&t;(__NR_O32_Linux +  34)
DECL|macro|__NR_O32_ftime
mdefine_line|#define __NR_O32_ftime&t;&t;&t;(__NR_O32_Linux +  35)
DECL|macro|__NR_O32_sync
mdefine_line|#define __NR_O32_sync&t;&t;&t;(__NR_O32_Linux +  36)
DECL|macro|__NR_O32_kill
mdefine_line|#define __NR_O32_kill&t;&t;&t;(__NR_O32_Linux +  37)
DECL|macro|__NR_O32_rename
mdefine_line|#define __NR_O32_rename&t;&t;&t;(__NR_O32_Linux +  38)
DECL|macro|__NR_O32_mkdir
mdefine_line|#define __NR_O32_mkdir&t;&t;&t;(__NR_O32_Linux +  39)
DECL|macro|__NR_O32_rmdir
mdefine_line|#define __NR_O32_rmdir&t;&t;&t;(__NR_O32_Linux +  40)
DECL|macro|__NR_O32_dup
mdefine_line|#define __NR_O32_dup&t;&t;&t;(__NR_O32_Linux +  41)
DECL|macro|__NR_O32_pipe
mdefine_line|#define __NR_O32_pipe&t;&t;&t;(__NR_O32_Linux +  42)
DECL|macro|__NR_O32_times
mdefine_line|#define __NR_O32_times&t;&t;&t;(__NR_O32_Linux +  43)
DECL|macro|__NR_O32_prof
mdefine_line|#define __NR_O32_prof&t;&t;&t;(__NR_O32_Linux +  44)
DECL|macro|__NR_O32_brk
mdefine_line|#define __NR_O32_brk&t;&t;&t;(__NR_O32_Linux +  45)
DECL|macro|__NR_O32_setgid
mdefine_line|#define __NR_O32_setgid&t;&t;&t;(__NR_O32_Linux +  46)
DECL|macro|__NR_O32_getgid
mdefine_line|#define __NR_O32_getgid&t;&t;&t;(__NR_O32_Linux +  47)
DECL|macro|__NR_O32_signal
mdefine_line|#define __NR_O32_signal&t;&t;&t;(__NR_O32_Linux +  48)
DECL|macro|__NR_O32_geteuid
mdefine_line|#define __NR_O32_geteuid&t;&t;(__NR_O32_Linux +  49)
DECL|macro|__NR_O32_getegid
mdefine_line|#define __NR_O32_getegid&t;&t;(__NR_O32_Linux +  50)
DECL|macro|__NR_O32_acct
mdefine_line|#define __NR_O32_acct&t;&t;&t;(__NR_O32_Linux +  51)
DECL|macro|__NR_O32_umount2
mdefine_line|#define __NR_O32_umount2&t;&t;(__NR_O32_Linux +  52)
DECL|macro|__NR_O32_lock
mdefine_line|#define __NR_O32_lock&t;&t;&t;(__NR_O32_Linux +  53)
DECL|macro|__NR_O32_ioctl
mdefine_line|#define __NR_O32_ioctl&t;&t;&t;(__NR_O32_Linux +  54)
DECL|macro|__NR_O32_fcntl
mdefine_line|#define __NR_O32_fcntl&t;&t;&t;(__NR_O32_Linux +  55)
DECL|macro|__NR_O32_mpx
mdefine_line|#define __NR_O32_mpx&t;&t;&t;(__NR_O32_Linux +  56)
DECL|macro|__NR_O32_setpgid
mdefine_line|#define __NR_O32_setpgid&t;&t;(__NR_O32_Linux +  57)
DECL|macro|__NR_O32_ulimit
mdefine_line|#define __NR_O32_ulimit&t;&t;&t;(__NR_O32_Linux +  58)
DECL|macro|__NR_O32_unused59
mdefine_line|#define __NR_O32_unused59&t;&t;(__NR_O32_Linux +  59)
DECL|macro|__NR_O32_umask
mdefine_line|#define __NR_O32_umask&t;&t;&t;(__NR_O32_Linux +  60)
DECL|macro|__NR_O32_chroot
mdefine_line|#define __NR_O32_chroot&t;&t;&t;(__NR_O32_Linux +  61)
DECL|macro|__NR_O32_ustat
mdefine_line|#define __NR_O32_ustat&t;&t;&t;(__NR_O32_Linux +  62)
DECL|macro|__NR_O32_dup2
mdefine_line|#define __NR_O32_dup2&t;&t;&t;(__NR_O32_Linux +  63)
DECL|macro|__NR_O32_getppid
mdefine_line|#define __NR_O32_getppid&t;&t;(__NR_O32_Linux +  64)
DECL|macro|__NR_O32_getpgrp
mdefine_line|#define __NR_O32_getpgrp&t;&t;(__NR_O32_Linux +  65)
DECL|macro|__NR_O32_setsid
mdefine_line|#define __NR_O32_setsid&t;&t;&t;(__NR_O32_Linux +  66)
DECL|macro|__NR_O32_sigaction
mdefine_line|#define __NR_O32_sigaction&t;&t;(__NR_O32_Linux +  67)
DECL|macro|__NR_O32_sgetmask
mdefine_line|#define __NR_O32_sgetmask&t;&t;(__NR_O32_Linux +  68)
DECL|macro|__NR_O32_ssetmask
mdefine_line|#define __NR_O32_ssetmask&t;&t;(__NR_O32_Linux +  69)
DECL|macro|__NR_O32_setreuid
mdefine_line|#define __NR_O32_setreuid&t;&t;(__NR_O32_Linux +  70)
DECL|macro|__NR_O32_setregid
mdefine_line|#define __NR_O32_setregid&t;&t;(__NR_O32_Linux +  71)
DECL|macro|__NR_O32_sigsuspend
mdefine_line|#define __NR_O32_sigsuspend&t;&t;(__NR_O32_Linux +  72)
DECL|macro|__NR_O32_sigpending
mdefine_line|#define __NR_O32_sigpending&t;&t;(__NR_O32_Linux +  73)
DECL|macro|__NR_O32_sethostname
mdefine_line|#define __NR_O32_sethostname&t;&t;(__NR_O32_Linux +  74)
DECL|macro|__NR_O32_setrlimit
mdefine_line|#define __NR_O32_setrlimit&t;&t;(__NR_O32_Linux +  75)
DECL|macro|__NR_O32_getrlimit
mdefine_line|#define __NR_O32_getrlimit&t;&t;(__NR_O32_Linux +  76)
DECL|macro|__NR_O32_getrusage
mdefine_line|#define __NR_O32_getrusage&t;&t;(__NR_O32_Linux +  77)
DECL|macro|__NR_O32_gettimeofday
mdefine_line|#define __NR_O32_gettimeofday&t;&t;(__NR_O32_Linux +  78)
DECL|macro|__NR_O32_settimeofday
mdefine_line|#define __NR_O32_settimeofday&t;&t;(__NR_O32_Linux +  79)
DECL|macro|__NR_O32_getgroups
mdefine_line|#define __NR_O32_getgroups&t;&t;(__NR_O32_Linux +  80)
DECL|macro|__NR_O32_setgroups
mdefine_line|#define __NR_O32_setgroups&t;&t;(__NR_O32_Linux +  81)
DECL|macro|__NR_O32_reserved82
mdefine_line|#define __NR_O32_reserved82&t;&t;(__NR_O32_Linux +  82)
DECL|macro|__NR_O32_symlink
mdefine_line|#define __NR_O32_symlink&t;&t;(__NR_O32_Linux +  83)
DECL|macro|__NR_O32_unused84
mdefine_line|#define __NR_O32_unused84&t;&t;(__NR_O32_Linux +  84)
DECL|macro|__NR_O32_readlink
mdefine_line|#define __NR_O32_readlink&t;&t;(__NR_O32_Linux +  85)
DECL|macro|__NR_O32_uselib
mdefine_line|#define __NR_O32_uselib&t;&t;&t;(__NR_O32_Linux +  86)
DECL|macro|__NR_O32_swapon
mdefine_line|#define __NR_O32_swapon&t;&t;&t;(__NR_O32_Linux +  87)
DECL|macro|__NR_O32_reboot
mdefine_line|#define __NR_O32_reboot&t;&t;&t;(__NR_O32_Linux +  88)
DECL|macro|__NR_O32_readdir
mdefine_line|#define __NR_O32_readdir&t;&t;(__NR_O32_Linux +  89)
DECL|macro|__NR_O32_mmap
mdefine_line|#define __NR_O32_mmap&t;&t;&t;(__NR_O32_Linux +  90)
DECL|macro|__NR_O32_munmap
mdefine_line|#define __NR_O32_munmap&t;&t;&t;(__NR_O32_Linux +  91)
DECL|macro|__NR_O32_truncate
mdefine_line|#define __NR_O32_truncate&t;&t;(__NR_O32_Linux +  92)
DECL|macro|__NR_O32_ftruncate
mdefine_line|#define __NR_O32_ftruncate&t;&t;(__NR_O32_Linux +  93)
DECL|macro|__NR_O32_fchmod
mdefine_line|#define __NR_O32_fchmod&t;&t;&t;(__NR_O32_Linux +  94)
DECL|macro|__NR_O32_fchown
mdefine_line|#define __NR_O32_fchown&t;&t;&t;(__NR_O32_Linux +  95)
DECL|macro|__NR_O32_getpriority
mdefine_line|#define __NR_O32_getpriority&t;&t;(__NR_O32_Linux +  96)
DECL|macro|__NR_O32_setpriority
mdefine_line|#define __NR_O32_setpriority&t;&t;(__NR_O32_Linux +  97)
DECL|macro|__NR_O32_profil
mdefine_line|#define __NR_O32_profil&t;&t;&t;(__NR_O32_Linux +  98)
DECL|macro|__NR_O32_statfs
mdefine_line|#define __NR_O32_statfs&t;&t;&t;(__NR_O32_Linux +  99)
DECL|macro|__NR_O32_fstatfs
mdefine_line|#define __NR_O32_fstatfs&t;&t;(__NR_O32_Linux + 100)
DECL|macro|__NR_O32_ioperm
mdefine_line|#define __NR_O32_ioperm&t;&t;&t;(__NR_O32_Linux + 101)
DECL|macro|__NR_O32_socketcall
mdefine_line|#define __NR_O32_socketcall&t;&t;(__NR_O32_Linux + 102)
DECL|macro|__NR_O32_syslog
mdefine_line|#define __NR_O32_syslog&t;&t;&t;(__NR_O32_Linux + 103)
DECL|macro|__NR_O32_setitimer
mdefine_line|#define __NR_O32_setitimer&t;&t;(__NR_O32_Linux + 104)
DECL|macro|__NR_O32_getitimer
mdefine_line|#define __NR_O32_getitimer&t;&t;(__NR_O32_Linux + 105)
DECL|macro|__NR_O32_stat
mdefine_line|#define __NR_O32_stat&t;&t;&t;(__NR_O32_Linux + 106)
DECL|macro|__NR_O32_lstat
mdefine_line|#define __NR_O32_lstat&t;&t;&t;(__NR_O32_Linux + 107)
DECL|macro|__NR_O32_fstat
mdefine_line|#define __NR_O32_fstat&t;&t;&t;(__NR_O32_Linux + 108)
DECL|macro|__NR_O32_unused109
mdefine_line|#define __NR_O32_unused109&t;&t;(__NR_O32_Linux + 109)
DECL|macro|__NR_O32_iopl
mdefine_line|#define __NR_O32_iopl&t;&t;&t;(__NR_O32_Linux + 110)
DECL|macro|__NR_O32_vhangup
mdefine_line|#define __NR_O32_vhangup&t;&t;(__NR_O32_Linux + 111)
DECL|macro|__NR_O32_idle
mdefine_line|#define __NR_O32_idle&t;&t;&t;(__NR_O32_Linux + 112)
DECL|macro|__NR_O32_vm86
mdefine_line|#define __NR_O32_vm86&t;&t;&t;(__NR_O32_Linux + 113)
DECL|macro|__NR_O32_wait4
mdefine_line|#define __NR_O32_wait4&t;&t;&t;(__NR_O32_Linux + 114)
DECL|macro|__NR_O32_swapoff
mdefine_line|#define __NR_O32_swapoff&t;&t;(__NR_O32_Linux + 115)
DECL|macro|__NR_O32_sysinfo
mdefine_line|#define __NR_O32_sysinfo&t;&t;(__NR_O32_Linux + 116)
DECL|macro|__NR_O32_ipc
mdefine_line|#define __NR_O32_ipc&t;&t;&t;(__NR_O32_Linux + 117)
DECL|macro|__NR_O32_fsync
mdefine_line|#define __NR_O32_fsync&t;&t;&t;(__NR_O32_Linux + 118)
DECL|macro|__NR_O32_sigreturn
mdefine_line|#define __NR_O32_sigreturn&t;&t;(__NR_O32_Linux + 119)
DECL|macro|__NR_O32_clone
mdefine_line|#define __NR_O32_clone&t;&t;&t;(__NR_O32_Linux + 120)
DECL|macro|__NR_O32_setdomainname
mdefine_line|#define __NR_O32_setdomainname&t;&t;(__NR_O32_Linux + 121)
DECL|macro|__NR_O32_uname
mdefine_line|#define __NR_O32_uname&t;&t;&t;(__NR_O32_Linux + 122)
DECL|macro|__NR_O32_modify_ldt
mdefine_line|#define __NR_O32_modify_ldt&t;&t;(__NR_O32_Linux + 123)
DECL|macro|__NR_O32_adjtimex
mdefine_line|#define __NR_O32_adjtimex&t;&t;(__NR_O32_Linux + 124)
DECL|macro|__NR_O32_mprotect
mdefine_line|#define __NR_O32_mprotect&t;&t;(__NR_O32_Linux + 125)
DECL|macro|__NR_O32_sigprocmask
mdefine_line|#define __NR_O32_sigprocmask&t;&t;(__NR_O32_Linux + 126)
DECL|macro|__NR_O32_create_module
mdefine_line|#define __NR_O32_create_module&t;&t;(__NR_O32_Linux + 127)
DECL|macro|__NR_O32_init_module
mdefine_line|#define __NR_O32_init_module&t;&t;(__NR_O32_Linux + 128)
DECL|macro|__NR_O32_delete_module
mdefine_line|#define __NR_O32_delete_module&t;&t;(__NR_O32_Linux + 129)
DECL|macro|__NR_O32_get_kernel_syms
mdefine_line|#define __NR_O32_get_kernel_syms&t;(__NR_O32_Linux + 130)
DECL|macro|__NR_O32_quotactl
mdefine_line|#define __NR_O32_quotactl&t;&t;(__NR_O32_Linux + 131)
DECL|macro|__NR_O32_getpgid
mdefine_line|#define __NR_O32_getpgid&t;&t;(__NR_O32_Linux + 132)
DECL|macro|__NR_O32_fchdir
mdefine_line|#define __NR_O32_fchdir&t;&t;&t;(__NR_O32_Linux + 133)
DECL|macro|__NR_O32_bdflush
mdefine_line|#define __NR_O32_bdflush&t;&t;(__NR_O32_Linux + 134)
DECL|macro|__NR_O32_sysfs
mdefine_line|#define __NR_O32_sysfs&t;&t;&t;(__NR_O32_Linux + 135)
DECL|macro|__NR_O32_personality
mdefine_line|#define __NR_O32_personality&t;&t;(__NR_O32_Linux + 136)
DECL|macro|__NR_O32_afs_syscall
mdefine_line|#define __NR_O32_afs_syscall&t;&t;(__NR_O32_Linux + 137) /* Syscall for Andrew File System */
DECL|macro|__NR_O32_setfsuid
mdefine_line|#define __NR_O32_setfsuid&t;&t;(__NR_O32_Linux + 138)
DECL|macro|__NR_O32_setfsgid
mdefine_line|#define __NR_O32_setfsgid&t;&t;(__NR_O32_Linux + 139)
DECL|macro|__NR_O32__llseek
mdefine_line|#define __NR_O32__llseek&t;&t;(__NR_O32_Linux + 140)
DECL|macro|__NR_O32_getdents
mdefine_line|#define __NR_O32_getdents&t;&t;(__NR_O32_Linux + 141)
DECL|macro|__NR_O32__newselect
mdefine_line|#define __NR_O32__newselect&t;&t;(__NR_O32_Linux + 142)
DECL|macro|__NR_O32_flock
mdefine_line|#define __NR_O32_flock&t;&t;&t;(__NR_O32_Linux + 143)
DECL|macro|__NR_O32_msync
mdefine_line|#define __NR_O32_msync&t;&t;&t;(__NR_O32_Linux + 144)
DECL|macro|__NR_O32_readv
mdefine_line|#define __NR_O32_readv&t;&t;&t;(__NR_O32_Linux + 145)
DECL|macro|__NR_O32_writev
mdefine_line|#define __NR_O32_writev&t;&t;&t;(__NR_O32_Linux + 146)
DECL|macro|__NR_O32_cacheflush
mdefine_line|#define __NR_O32_cacheflush&t;&t;(__NR_O32_Linux + 147)
DECL|macro|__NR_O32_cachectl
mdefine_line|#define __NR_O32_cachectl&t;&t;(__NR_O32_Linux + 148)
DECL|macro|__NR_O32_sysmips
mdefine_line|#define __NR_O32_sysmips&t;&t;(__NR_O32_Linux + 149)
DECL|macro|__NR_O32_unused150
mdefine_line|#define __NR_O32_unused150&t;&t;(__NR_O32_Linux + 150)
DECL|macro|__NR_O32_getsid
mdefine_line|#define __NR_O32_getsid&t;&t;&t;(__NR_O32_Linux + 151)
DECL|macro|__NR_O32_fdatasync
mdefine_line|#define __NR_O32_fdatasync&t;&t;(__NR_O32_Linux + 152)
DECL|macro|__NR_O32__sysctl
mdefine_line|#define __NR_O32__sysctl&t;&t;(__NR_O32_Linux + 153)
DECL|macro|__NR_O32_mlock
mdefine_line|#define __NR_O32_mlock&t;&t;&t;(__NR_O32_Linux + 154)
DECL|macro|__NR_O32_munlock
mdefine_line|#define __NR_O32_munlock&t;&t;(__NR_O32_Linux + 155)
DECL|macro|__NR_O32_mlockall
mdefine_line|#define __NR_O32_mlockall&t;&t;(__NR_O32_Linux + 156)
DECL|macro|__NR_O32_munlockall
mdefine_line|#define __NR_O32_munlockall&t;&t;(__NR_O32_Linux + 157)
DECL|macro|__NR_O32_sched_setparam
mdefine_line|#define __NR_O32_sched_setparam&t;&t;(__NR_O32_Linux + 158)
DECL|macro|__NR_O32_sched_getparam
mdefine_line|#define __NR_O32_sched_getparam&t;&t;(__NR_O32_Linux + 159)
DECL|macro|__NR_O32_sched_setscheduler
mdefine_line|#define __NR_O32_sched_setscheduler&t;(__NR_O32_Linux + 160)
DECL|macro|__NR_O32_sched_getscheduler
mdefine_line|#define __NR_O32_sched_getscheduler&t;(__NR_O32_Linux + 161)
DECL|macro|__NR_O32_sched_yield
mdefine_line|#define __NR_O32_sched_yield&t;&t;(__NR_O32_Linux + 162)
DECL|macro|__NR_O32_sched_get_priority_max
mdefine_line|#define __NR_O32_sched_get_priority_max&t;(__NR_O32_Linux + 163)
DECL|macro|__NR_O32_sched_get_priority_min
mdefine_line|#define __NR_O32_sched_get_priority_min&t;(__NR_O32_Linux + 164)
DECL|macro|__NR_O32_sched_rr_get_interval
mdefine_line|#define __NR_O32_sched_rr_get_interval&t;(__NR_O32_Linux + 165)
DECL|macro|__NR_O32_nanosleep
mdefine_line|#define __NR_O32_nanosleep&t;&t;(__NR_O32_Linux + 166)
DECL|macro|__NR_O32_mremap
mdefine_line|#define __NR_O32_mremap&t;&t;&t;(__NR_O32_Linux + 167)
DECL|macro|__NR_O32_accept
mdefine_line|#define __NR_O32_accept&t;&t;&t;(__NR_O32_Linux + 168)
DECL|macro|__NR_O32_bind
mdefine_line|#define __NR_O32_bind&t;&t;&t;(__NR_O32_Linux + 169)
DECL|macro|__NR_O32_connect
mdefine_line|#define __NR_O32_connect&t;&t;(__NR_O32_Linux + 170)
DECL|macro|__NR_O32_getpeername
mdefine_line|#define __NR_O32_getpeername&t;&t;(__NR_O32_Linux + 171)
DECL|macro|__NR_O32_getsockname
mdefine_line|#define __NR_O32_getsockname&t;&t;(__NR_O32_Linux + 172)
DECL|macro|__NR_O32_getsockopt
mdefine_line|#define __NR_O32_getsockopt&t;&t;(__NR_O32_Linux + 173)
DECL|macro|__NR_O32_listen
mdefine_line|#define __NR_O32_listen&t;&t;&t;(__NR_O32_Linux + 174)
DECL|macro|__NR_O32_recv
mdefine_line|#define __NR_O32_recv&t;&t;&t;(__NR_O32_Linux + 175)
DECL|macro|__NR_O32_recvfrom
mdefine_line|#define __NR_O32_recvfrom&t;&t;(__NR_O32_Linux + 176)
DECL|macro|__NR_O32_recvmsg
mdefine_line|#define __NR_O32_recvmsg&t;&t;(__NR_O32_Linux + 177)
DECL|macro|__NR_O32_send
mdefine_line|#define __NR_O32_send&t;&t;&t;(__NR_O32_Linux + 178)
DECL|macro|__NR_O32_sendmsg
mdefine_line|#define __NR_O32_sendmsg&t;&t;(__NR_O32_Linux + 179)
DECL|macro|__NR_O32_sendto
mdefine_line|#define __NR_O32_sendto&t;&t;&t;(__NR_O32_Linux + 180)
DECL|macro|__NR_O32_setsockopt
mdefine_line|#define __NR_O32_setsockopt&t;&t;(__NR_O32_Linux + 181)
DECL|macro|__NR_O32_shutdown
mdefine_line|#define __NR_O32_shutdown&t;&t;(__NR_O32_Linux + 182)
DECL|macro|__NR_O32_socket
mdefine_line|#define __NR_O32_socket&t;&t;&t;(__NR_O32_Linux + 183)
DECL|macro|__NR_O32_socketpair
mdefine_line|#define __NR_O32_socketpair&t;&t;(__NR_O32_Linux + 184)
DECL|macro|__NR_O32_setresuid
mdefine_line|#define __NR_O32_setresuid&t;&t;(__NR_O32_Linux + 185)
DECL|macro|__NR_O32_getresuid
mdefine_line|#define __NR_O32_getresuid&t;&t;(__NR_O32_Linux + 186)
DECL|macro|__NR_O32_query_module
mdefine_line|#define __NR_O32_query_module&t;&t;(__NR_O32_Linux + 187)
DECL|macro|__NR_O32_poll
mdefine_line|#define __NR_O32_poll&t;&t;&t;(__NR_O32_Linux + 188)
DECL|macro|__NR_O32_nfsservctl
mdefine_line|#define __NR_O32_nfsservctl&t;&t;(__NR_O32_Linux + 189)
DECL|macro|__NR_O32_setresgid
mdefine_line|#define __NR_O32_setresgid&t;&t;(__NR_O32_Linux + 190)
DECL|macro|__NR_O32_getresgid
mdefine_line|#define __NR_O32_getresgid&t;&t;(__NR_O32_Linux + 191)
DECL|macro|__NR_O32_prctl
mdefine_line|#define __NR_O32_prctl&t;&t;&t;(__NR_O32_Linux + 192)
DECL|macro|__NR_O32_rt_sigreturn
mdefine_line|#define __NR_O32_rt_sigreturn&t;&t;(__NR_O32_Linux + 193)
DECL|macro|__NR_O32_rt_sigaction
mdefine_line|#define __NR_O32_rt_sigaction&t;&t;(__NR_O32_Linux + 194)
DECL|macro|__NR_O32_rt_sigprocmask
mdefine_line|#define __NR_O32_rt_sigprocmask&t;&t;(__NR_O32_Linux + 195)
DECL|macro|__NR_O32_rt_sigpending
mdefine_line|#define __NR_O32_rt_sigpending&t;&t;(__NR_O32_Linux + 196)
DECL|macro|__NR_O32_rt_sigtimedwait
mdefine_line|#define __NR_O32_rt_sigtimedwait&t;(__NR_O32_Linux + 197)
DECL|macro|__NR_O32_rt_sigqueueinfo
mdefine_line|#define __NR_O32_rt_sigqueueinfo&t;(__NR_O32_Linux + 198)
DECL|macro|__NR_O32_rt_sigsuspend
mdefine_line|#define __NR_O32_rt_sigsuspend&t;&t;(__NR_O32_Linux + 199)
DECL|macro|__NR_O32_pread64
mdefine_line|#define __NR_O32_pread64&t;&t;(__NR_O32_Linux + 200)
DECL|macro|__NR_O32_pwrite64
mdefine_line|#define __NR_O32_pwrite64&t;&t;(__NR_O32_Linux + 201)
DECL|macro|__NR_O32_chown
mdefine_line|#define __NR_O32_chown&t;&t;&t;(__NR_O32_Linux + 202)
DECL|macro|__NR_O32_getcwd
mdefine_line|#define __NR_O32_getcwd&t;&t;&t;(__NR_O32_Linux + 203)
DECL|macro|__NR_O32_capget
mdefine_line|#define __NR_O32_capget&t;&t;&t;(__NR_O32_Linux + 204)
DECL|macro|__NR_O32_capset
mdefine_line|#define __NR_O32_capset&t;&t;&t;(__NR_O32_Linux + 205)
DECL|macro|__NR_O32_sigaltstack
mdefine_line|#define __NR_O32_sigaltstack&t;&t;(__NR_O32_Linux + 206)
DECL|macro|__NR_O32_sendfile
mdefine_line|#define __NR_O32_sendfile&t;&t;(__NR_O32_Linux + 207)
DECL|macro|__NR_O32_getpmsg
mdefine_line|#define __NR_O32_getpmsg&t;&t;(__NR_O32_Linux + 208)
DECL|macro|__NR_O32_putpmsg
mdefine_line|#define __NR_O32_putpmsg&t;&t;(__NR_O32_Linux + 209)
DECL|macro|__NR_O32_mmap2
mdefine_line|#define __NR_O32_mmap2&t;&t;&t;(__NR_O32_Linux + 210)
DECL|macro|__NR_O32_truncate64
mdefine_line|#define __NR_O32_truncate64&t;&t;(__NR_O32_Linux + 211)
DECL|macro|__NR_O32_ftruncate64
mdefine_line|#define __NR_O32_ftruncate64&t;&t;(__NR_O32_Linux + 212)
DECL|macro|__NR_O32_stat64
mdefine_line|#define __NR_O32_stat64&t;&t;&t;(__NR_O32_Linux + 213)
DECL|macro|__NR_O32_lstat64
mdefine_line|#define __NR_O32_lstat64&t;&t;(__NR_O32_Linux + 214)
DECL|macro|__NR_O32_fstat64
mdefine_line|#define __NR_O32_fstat64&t;&t;(__NR_O32_Linux + 215)
DECL|macro|__NR_O32_root_pivot
mdefine_line|#define __NR_O32_root_pivot&t;&t;(__NR_O32_Linux + 216)
DECL|macro|__NR_O32_mincore
mdefine_line|#define __NR_O32_mincore&t;&t;(__NR_O32_Linux + 217)
DECL|macro|__NR_O32_madvise
mdefine_line|#define __NR_O32_madvise&t;&t;(__NR_O32_Linux + 218)
DECL|macro|__NR_O32_getdents64
mdefine_line|#define __NR_O32_getdents64&t;&t;(__NR_O32_Linux + 219)
DECL|macro|__NR_O32_fcntl64
mdefine_line|#define __NR_O32_fcntl64&t;&t;(__NR_O32_Linux + 220)
DECL|macro|__NR_O32_reserved221
mdefine_line|#define __NR_O32_reserved221&t;&t;(__NR_O32_Linux + 221)
DECL|macro|__NR_O32_gettid
mdefine_line|#define __NR_O32_gettid&t;&t;&t;(__NR_O32_Linux + 222)
DECL|macro|__NR_O32_readahead
mdefine_line|#define __NR_O32_readahead&t;&t;(__NR_O32_Linux + 223)
DECL|macro|__NR_O32_setxattr
mdefine_line|#define __NR_O32_setxattr&t;&t;(__NR_O32_Linux + 224)
DECL|macro|__NR_O32_lsetxattr
mdefine_line|#define __NR_O32_lsetxattr&t;&t;(__NR_O32_Linux + 225)
DECL|macro|__NR_O32_fsetxattr
mdefine_line|#define __NR_O32_fsetxattr&t;&t;(__NR_O32_Linux + 226)
DECL|macro|__NR_O32_getxattr
mdefine_line|#define __NR_O32_getxattr&t;&t;(__NR_O32_Linux + 227)
DECL|macro|__NR_O32_lgetxattr
mdefine_line|#define __NR_O32_lgetxattr&t;&t;(__NR_O32_Linux + 228)
DECL|macro|__NR_O32_fgetxattr
mdefine_line|#define __NR_O32_fgetxattr&t;&t;(__NR_O32_Linux + 229)
DECL|macro|__NR_O32_listxattr
mdefine_line|#define __NR_O32_listxattr&t;&t;(__NR_O32_Linux + 230)
DECL|macro|__NR_O32_llistxattr
mdefine_line|#define __NR_O32_llistxattr&t;&t;(__NR_O32_Linux + 231)
DECL|macro|__NR_O32_flistxattr
mdefine_line|#define __NR_O32_flistxattr&t;&t;(__NR_O32_Linux + 232)
DECL|macro|__NR_O32_removexattr
mdefine_line|#define __NR_O32_removexattr&t;&t;(__NR_O32_Linux + 233)
DECL|macro|__NR_O32_lremovexattr
mdefine_line|#define __NR_O32_lremovexattr&t;&t;(__NR_O32_Linux + 234)
DECL|macro|__NR_O32_fremovexattr
mdefine_line|#define __NR_O32_fremovexattr&t;&t;(__NR_O32_Linux + 235)
DECL|macro|__NR_O32_tkill
mdefine_line|#define __NR_O32_tkill&t;&t;&t;(__NR_O32_Linux + 236)
DECL|macro|__NR_O32_sendfile64
mdefine_line|#define __NR_O32_sendfile64&t;&t;(__NR_O32_Linux + 237)
DECL|macro|__NR_O32_futex
mdefine_line|#define __NR_O32_futex&t;&t;&t;(__NR_O32_Linux + 238)
DECL|macro|__NR_O32_sched_setaffinity
mdefine_line|#define __NR_O32_sched_setaffinity&t;(__NR_O32_Linux + 239)
DECL|macro|__NR_O32_sched_getaffinity
mdefine_line|#define __NR_O32_sched_getaffinity&t;(__NR_O32_Linux + 240)
DECL|macro|__NR_O32_io_setup
mdefine_line|#define __NR_O32_io_setup&t;&t;(__NR_O32_Linux + 241)
DECL|macro|__NR_O32_io_destroy
mdefine_line|#define __NR_O32_io_destroy&t;&t;(__NR_O32_Linux + 242)
DECL|macro|__NR_O32_io_getevents
mdefine_line|#define __NR_O32_io_getevents&t;&t;(__NR_O32_Linux + 243)
DECL|macro|__NR_O32_io_submit
mdefine_line|#define __NR_O32_io_submit&t;&t;(__NR_O32_Linux + 244)
DECL|macro|__NR_O32_io_cancel
mdefine_line|#define __NR_O32_io_cancel&t;&t;(__NR_O32_Linux + 245)
DECL|macro|__NR_O32_exit_group
mdefine_line|#define __NR_O32_exit_group&t;&t;(__NR_O32_Linux + 246)
DECL|macro|__NR_O32_lookup_dcookie
mdefine_line|#define __NR_O32_lookup_dcookie&t;&t;(__NR_O32_Linux + 247)
DECL|macro|__NR_O32_epoll_create
mdefine_line|#define __NR_O32_epoll_create&t;&t;(__NR_O32_Linux + 248)
DECL|macro|__NR_O32_epoll_ctl
mdefine_line|#define __NR_O32_epoll_ctl&t;&t;(__NR_O32_Linux + 249)
DECL|macro|__NR_O32_epoll_wait
mdefine_line|#define __NR_O32_epoll_wait&t;&t;(__NR_O32_Linux + 250)
DECL|macro|__NR_O32_remap_file_page
mdefine_line|#define __NR_O32_remap_file_page&t;(__NR_O32_Linux + 251)
DECL|macro|__NR_O32_set_tid_address
mdefine_line|#define __NR_O32_set_tid_address&t;(__NR_O32_Linux + 252)
DECL|macro|__NR_O32_restart_syscall
mdefine_line|#define __NR_O32_restart_syscall&t;(__NR_O32_Linux + 253)
DECL|macro|__NR_O32_fadvise64
mdefine_line|#define __NR_O32_fadvise64&t;&t;(__NR_O32_Linux + 254)
DECL|macro|__NR_O32_statfs64
mdefine_line|#define __NR_O32_statfs64&t;&t;(__NR_O32_Linux + 255)
DECL|macro|__NR_O32_fstatfs64
mdefine_line|#define __NR_O32_fstatfs64&t;&t;(__NR_O32_Linux + 256)
multiline_comment|/*&n; * Offset of the last Linux o32 flavoured syscall&n; */
DECL|macro|__NR_O32_Linux_syscalls
mdefine_line|#define __NR_O32_Linux_syscalls&t;&t;256
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
DECL|macro|__NR_time
mdefine_line|#define __NR_time&t;&t;&t;(__NR_Linux + 193)
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
DECL|macro|__NR_remap_file_page
mdefine_line|#define __NR_remap_file_page&t;&t;(__NR_Linux + 210)
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
multiline_comment|/*&n; * Offset of the last Linux flavoured syscall&n; */
DECL|macro|__NR_Linux_syscalls
mdefine_line|#define __NR_Linux_syscalls&t;&t;215
multiline_comment|/*&n; * Linux N32 syscalls are in the range from 6000 to 6999.&n; */
DECL|macro|__NR_N32_Linux
mdefine_line|#define __NR_N32_Linux&t;&t;&t;6000
DECL|macro|__NR_N32_read
mdefine_line|#define __NR_N32_read&t;&t;&t;(__NR_N32_Linux +   0)
DECL|macro|__NR_N32_write
mdefine_line|#define __NR_N32_write&t;&t;&t;(__NR_N32_Linux +   1)
DECL|macro|__NR_N32_open
mdefine_line|#define __NR_N32_open&t;&t;&t;(__NR_N32_Linux +   2)
DECL|macro|__NR_N32_close
mdefine_line|#define __NR_N32_close&t;&t;&t;(__NR_N32_Linux +   3)
DECL|macro|__NR_N32_stat
mdefine_line|#define __NR_N32_stat&t;&t;&t;(__NR_N32_Linux +   4)
DECL|macro|__NR_N32_fstat
mdefine_line|#define __NR_N32_fstat&t;&t;&t;(__NR_N32_Linux +   5)
DECL|macro|__NR_N32_lstat
mdefine_line|#define __NR_N32_lstat&t;&t;&t;(__NR_N32_Linux +   6)
DECL|macro|__NR_N32_poll
mdefine_line|#define __NR_N32_poll&t;&t;&t;(__NR_N32_Linux +   7)
DECL|macro|__NR_N32_lseek
mdefine_line|#define __NR_N32_lseek&t;&t;&t;(__NR_N32_Linux +   8)
DECL|macro|__NR_N32_mmap
mdefine_line|#define __NR_N32_mmap&t;&t;&t;(__NR_N32_Linux +   9)
DECL|macro|__NR_N32_mprotect
mdefine_line|#define __NR_N32_mprotect&t;&t;(__NR_N32_Linux +  10)
DECL|macro|__NR_N32_munmap
mdefine_line|#define __NR_N32_munmap&t;&t;&t;(__NR_N32_Linux +  11)
DECL|macro|__NR_N32_brk
mdefine_line|#define __NR_N32_brk&t;&t;&t;(__NR_N32_Linux +  12)
DECL|macro|__NR_N32_rt_sigaction
mdefine_line|#define __NR_N32_rt_sigaction&t;&t;(__NR_N32_Linux +  13)
DECL|macro|__NR_N32_rt_sigprocmask
mdefine_line|#define __NR_N32_rt_sigprocmask&t;&t;(__NR_N32_Linux +  14)
DECL|macro|__NR_N32_ioctl
mdefine_line|#define __NR_N32_ioctl&t;&t;&t;(__NR_N32_Linux +  15)
DECL|macro|__NR_N32_pread64
mdefine_line|#define __NR_N32_pread64&t;&t;(__NR_N32_Linux +  16)
DECL|macro|__NR_N32_pwrite64
mdefine_line|#define __NR_N32_pwrite64&t;&t;(__NR_N32_Linux +  17)
DECL|macro|__NR_N32_readv
mdefine_line|#define __NR_N32_readv&t;&t;&t;(__NR_N32_Linux +  18)
DECL|macro|__NR_N32_writev
mdefine_line|#define __NR_N32_writev&t;&t;&t;(__NR_N32_Linux +  19)
DECL|macro|__NR_N32_access
mdefine_line|#define __NR_N32_access&t;&t;&t;(__NR_N32_Linux +  20)
DECL|macro|__NR_N32_pipe
mdefine_line|#define __NR_N32_pipe&t;&t;&t;(__NR_N32_Linux +  21)
DECL|macro|__NR_N32__newselect
mdefine_line|#define __NR_N32__newselect&t;&t;(__NR_N32_Linux +  22)
DECL|macro|__NR_N32_sched_yield
mdefine_line|#define __NR_N32_sched_yield&t;&t;(__NR_N32_Linux +  23)
DECL|macro|__NR_N32_mremap
mdefine_line|#define __NR_N32_mremap&t;&t;&t;(__NR_N32_Linux +  24)
DECL|macro|__NR_N32_msync
mdefine_line|#define __NR_N32_msync&t;&t;&t;(__NR_N32_Linux +  25)
DECL|macro|__NR_N32_mincore
mdefine_line|#define __NR_N32_mincore&t;&t;(__NR_N32_Linux +  26)
DECL|macro|__NR_N32_madvise
mdefine_line|#define __NR_N32_madvise&t;&t;(__NR_N32_Linux +  27)
DECL|macro|__NR_N32_shmget
mdefine_line|#define __NR_N32_shmget&t;&t;&t;(__NR_N32_Linux +  28)
DECL|macro|__NR_N32_shmat
mdefine_line|#define __NR_N32_shmat&t;&t;&t;(__NR_N32_Linux +  29)
DECL|macro|__NR_N32_shmctl
mdefine_line|#define __NR_N32_shmctl&t;&t;&t;(__NR_N32_Linux +  30)
DECL|macro|__NR_N32_dup
mdefine_line|#define __NR_N32_dup&t;&t;&t;(__NR_N32_Linux +  31)
DECL|macro|__NR_N32_dup2
mdefine_line|#define __NR_N32_dup2&t;&t;&t;(__NR_N32_Linux +  32)
DECL|macro|__NR_N32_pause
mdefine_line|#define __NR_N32_pause&t;&t;&t;(__NR_N32_Linux +  33)
DECL|macro|__NR_N32_nanosleep
mdefine_line|#define __NR_N32_nanosleep&t;&t;(__NR_N32_Linux +  34)
DECL|macro|__NR_N32_getitimer
mdefine_line|#define __NR_N32_getitimer&t;&t;(__NR_N32_Linux +  35)
DECL|macro|__NR_N32_setitimer
mdefine_line|#define __NR_N32_setitimer&t;&t;(__NR_N32_Linux +  36)
DECL|macro|__NR_N32_alarm
mdefine_line|#define __NR_N32_alarm&t;&t;&t;(__NR_N32_Linux +  37)
DECL|macro|__NR_N32_getpid
mdefine_line|#define __NR_N32_getpid&t;&t;&t;(__NR_N32_Linux +  38)
DECL|macro|__NR_N32_sendfile
mdefine_line|#define __NR_N32_sendfile&t;&t;(__NR_N32_Linux +  39)
DECL|macro|__NR_N32_socket
mdefine_line|#define __NR_N32_socket&t;&t;&t;(__NR_N32_Linux +  40)
DECL|macro|__NR_N32_connect
mdefine_line|#define __NR_N32_connect&t;&t;(__NR_N32_Linux +  41)
DECL|macro|__NR_N32_accept
mdefine_line|#define __NR_N32_accept&t;&t;&t;(__NR_N32_Linux +  42)
DECL|macro|__NR_N32_sendto
mdefine_line|#define __NR_N32_sendto&t;&t;&t;(__NR_N32_Linux +  43)
DECL|macro|__NR_N32_recvfrom
mdefine_line|#define __NR_N32_recvfrom&t;&t;(__NR_N32_Linux +  44)
DECL|macro|__NR_N32_sendmsg
mdefine_line|#define __NR_N32_sendmsg&t;&t;(__NR_N32_Linux +  45)
DECL|macro|__NR_N32_recvmsg
mdefine_line|#define __NR_N32_recvmsg&t;&t;(__NR_N32_Linux +  46)
DECL|macro|__NR_N32_shutdown
mdefine_line|#define __NR_N32_shutdown&t;&t;(__NR_N32_Linux +  47)
DECL|macro|__NR_N32_bind
mdefine_line|#define __NR_N32_bind&t;&t;&t;(__NR_N32_Linux +  48)
DECL|macro|__NR_N32_listen
mdefine_line|#define __NR_N32_listen&t;&t;&t;(__NR_N32_Linux +  49)
DECL|macro|__NR_N32_getsockname
mdefine_line|#define __NR_N32_getsockname&t;&t;(__NR_N32_Linux +  50)
DECL|macro|__NR_N32_getpeername
mdefine_line|#define __NR_N32_getpeername&t;&t;(__NR_N32_Linux +  51)
DECL|macro|__NR_N32_socketpair
mdefine_line|#define __NR_N32_socketpair&t;&t;(__NR_N32_Linux +  52)
DECL|macro|__NR_N32_setsockopt
mdefine_line|#define __NR_N32_setsockopt&t;&t;(__NR_N32_Linux +  53)
DECL|macro|__NR_N32_getsockopt
mdefine_line|#define __NR_N32_getsockopt&t;&t;(__NR_N32_Linux +  54)
DECL|macro|__NR_N32_clone
mdefine_line|#define __NR_N32_clone&t;&t;&t;(__NR_N32_Linux +  55)
DECL|macro|__NR_N32_fork
mdefine_line|#define __NR_N32_fork&t;&t;&t;(__NR_N32_Linux +  56)
DECL|macro|__NR_N32_execve
mdefine_line|#define __NR_N32_execve&t;&t;&t;(__NR_N32_Linux +  57)
DECL|macro|__NR_N32_exit
mdefine_line|#define __NR_N32_exit&t;&t;&t;(__NR_N32_Linux +  58)
DECL|macro|__NR_N32_wait4
mdefine_line|#define __NR_N32_wait4&t;&t;&t;(__NR_N32_Linux +  59)
DECL|macro|__NR_N32_kill
mdefine_line|#define __NR_N32_kill&t;&t;&t;(__NR_N32_Linux +  60)
DECL|macro|__NR_N32_uname
mdefine_line|#define __NR_N32_uname&t;&t;&t;(__NR_N32_Linux +  61)
DECL|macro|__NR_N32_semget
mdefine_line|#define __NR_N32_semget&t;&t;&t;(__NR_N32_Linux +  62)
DECL|macro|__NR_N32_semop
mdefine_line|#define __NR_N32_semop&t;&t;&t;(__NR_N32_Linux +  63)
DECL|macro|__NR_N32_semctl
mdefine_line|#define __NR_N32_semctl&t;&t;&t;(__NR_N32_Linux +  64)
DECL|macro|__NR_N32_shmdt
mdefine_line|#define __NR_N32_shmdt&t;&t;&t;(__NR_N32_Linux +  65)
DECL|macro|__NR_N32_msgget
mdefine_line|#define __NR_N32_msgget&t;&t;&t;(__NR_N32_Linux +  66)
DECL|macro|__NR_N32_msgsnd
mdefine_line|#define __NR_N32_msgsnd&t;&t;&t;(__NR_N32_Linux +  67)
DECL|macro|__NR_N32_msgrcv
mdefine_line|#define __NR_N32_msgrcv&t;&t;&t;(__NR_N32_Linux +  68)
DECL|macro|__NR_N32_msgctl
mdefine_line|#define __NR_N32_msgctl&t;&t;&t;(__NR_N32_Linux +  69)
DECL|macro|__NR_N32_fcntl
mdefine_line|#define __NR_N32_fcntl&t;&t;&t;(__NR_N32_Linux +  70)
DECL|macro|__NR_N32_flock
mdefine_line|#define __NR_N32_flock&t;&t;&t;(__NR_N32_Linux +  71)
DECL|macro|__NR_N32_fsync
mdefine_line|#define __NR_N32_fsync&t;&t;&t;(__NR_N32_Linux +  72)
DECL|macro|__NR_N32_fdatasync
mdefine_line|#define __NR_N32_fdatasync&t;&t;(__NR_N32_Linux +  73)
DECL|macro|__NR_N32_truncate
mdefine_line|#define __NR_N32_truncate&t;&t;(__NR_N32_Linux +  74)
DECL|macro|__NR_N32_ftruncate
mdefine_line|#define __NR_N32_ftruncate&t;&t;(__NR_N32_Linux +  75)
DECL|macro|__NR_N32_getdents
mdefine_line|#define __NR_N32_getdents&t;&t;(__NR_N32_Linux +  76)
DECL|macro|__NR_N32_getcwd
mdefine_line|#define __NR_N32_getcwd&t;&t;&t;(__NR_N32_Linux +  77)
DECL|macro|__NR_N32_chdir
mdefine_line|#define __NR_N32_chdir&t;&t;&t;(__NR_N32_Linux +  78)
DECL|macro|__NR_N32_fchdir
mdefine_line|#define __NR_N32_fchdir&t;&t;&t;(__NR_N32_Linux +  79)
DECL|macro|__NR_N32_rename
mdefine_line|#define __NR_N32_rename&t;&t;&t;(__NR_N32_Linux +  80)
DECL|macro|__NR_N32_mkdir
mdefine_line|#define __NR_N32_mkdir&t;&t;&t;(__NR_N32_Linux +  81)
DECL|macro|__NR_N32_rmdir
mdefine_line|#define __NR_N32_rmdir&t;&t;&t;(__NR_N32_Linux +  82)
DECL|macro|__NR_N32_creat
mdefine_line|#define __NR_N32_creat&t;&t;&t;(__NR_N32_Linux +  83)
DECL|macro|__NR_N32_link
mdefine_line|#define __NR_N32_link&t;&t;&t;(__NR_N32_Linux +  84)
DECL|macro|__NR_N32_unlink
mdefine_line|#define __NR_N32_unlink&t;&t;&t;(__NR_N32_Linux +  85)
DECL|macro|__NR_N32_symlink
mdefine_line|#define __NR_N32_symlink&t;&t;(__NR_N32_Linux +  86)
DECL|macro|__NR_N32_readlink
mdefine_line|#define __NR_N32_readlink&t;&t;(__NR_N32_Linux +  87)
DECL|macro|__NR_N32_chmod
mdefine_line|#define __NR_N32_chmod&t;&t;&t;(__NR_N32_Linux +  88)
DECL|macro|__NR_N32_fchmod
mdefine_line|#define __NR_N32_fchmod&t;&t;&t;(__NR_N32_Linux +  89)
DECL|macro|__NR_N32_chown
mdefine_line|#define __NR_N32_chown&t;&t;&t;(__NR_N32_Linux +  90)
DECL|macro|__NR_N32_fchown
mdefine_line|#define __NR_N32_fchown&t;&t;&t;(__NR_N32_Linux +  91)
DECL|macro|__NR_N32_lchown
mdefine_line|#define __NR_N32_lchown&t;&t;&t;(__NR_N32_Linux +  92)
DECL|macro|__NR_N32_umask
mdefine_line|#define __NR_N32_umask&t;&t;&t;(__NR_N32_Linux +  93)
DECL|macro|__NR_N32_gettimeofday
mdefine_line|#define __NR_N32_gettimeofday&t;&t;(__NR_N32_Linux +  94)
DECL|macro|__NR_N32_getrlimit
mdefine_line|#define __NR_N32_getrlimit&t;&t;(__NR_N32_Linux +  95)
DECL|macro|__NR_N32_getrusage
mdefine_line|#define __NR_N32_getrusage&t;&t;(__NR_N32_Linux +  96)
DECL|macro|__NR_N32_sysinfo
mdefine_line|#define __NR_N32_sysinfo&t;&t;(__NR_N32_Linux +  97)
DECL|macro|__NR_N32_times
mdefine_line|#define __NR_N32_times&t;&t;&t;(__NR_N32_Linux +  98)
DECL|macro|__NR_N32_ptrace
mdefine_line|#define __NR_N32_ptrace&t;&t;&t;(__NR_N32_Linux +  99)
DECL|macro|__NR_N32_getuid
mdefine_line|#define __NR_N32_getuid&t;&t;&t;(__NR_N32_Linux + 100)
DECL|macro|__NR_N32_syslog
mdefine_line|#define __NR_N32_syslog&t;&t;&t;(__NR_N32_Linux + 101)
DECL|macro|__NR_N32_getgid
mdefine_line|#define __NR_N32_getgid&t;&t;&t;(__NR_N32_Linux + 102)
DECL|macro|__NR_N32_setuid
mdefine_line|#define __NR_N32_setuid&t;&t;&t;(__NR_N32_Linux + 103)
DECL|macro|__NR_N32_setgid
mdefine_line|#define __NR_N32_setgid&t;&t;&t;(__NR_N32_Linux + 104)
DECL|macro|__NR_N32_geteuid
mdefine_line|#define __NR_N32_geteuid&t;&t;(__NR_N32_Linux + 105)
DECL|macro|__NR_N32_getegid
mdefine_line|#define __NR_N32_getegid&t;&t;(__NR_N32_Linux + 106)
DECL|macro|__NR_N32_setpgid
mdefine_line|#define __NR_N32_setpgid&t;&t;(__NR_N32_Linux + 107)
DECL|macro|__NR_N32_getppid
mdefine_line|#define __NR_N32_getppid&t;&t;(__NR_N32_Linux + 108)
DECL|macro|__NR_N32_getpgrp
mdefine_line|#define __NR_N32_getpgrp&t;&t;(__NR_N32_Linux + 109)
DECL|macro|__NR_N32_setsid
mdefine_line|#define __NR_N32_setsid&t;&t;&t;(__NR_N32_Linux + 110)
DECL|macro|__NR_N32_setreuid
mdefine_line|#define __NR_N32_setreuid&t;&t;(__NR_N32_Linux + 111)
DECL|macro|__NR_N32_setregid
mdefine_line|#define __NR_N32_setregid&t;&t;(__NR_N32_Linux + 112)
DECL|macro|__NR_N32_getgroups
mdefine_line|#define __NR_N32_getgroups&t;&t;(__NR_N32_Linux + 113)
DECL|macro|__NR_N32_setgroups
mdefine_line|#define __NR_N32_setgroups&t;&t;(__NR_N32_Linux + 114)
DECL|macro|__NR_N32_setresuid
mdefine_line|#define __NR_N32_setresuid&t;&t;(__NR_N32_Linux + 115)
DECL|macro|__NR_N32_getresuid
mdefine_line|#define __NR_N32_getresuid&t;&t;(__NR_N32_Linux + 116)
DECL|macro|__NR_N32_setresgid
mdefine_line|#define __NR_N32_setresgid&t;&t;(__NR_N32_Linux + 117)
DECL|macro|__NR_N32_getresgid
mdefine_line|#define __NR_N32_getresgid&t;&t;(__NR_N32_Linux + 118)
DECL|macro|__NR_N32_getpgid
mdefine_line|#define __NR_N32_getpgid&t;&t;(__NR_N32_Linux + 119)
DECL|macro|__NR_N32_setfsuid
mdefine_line|#define __NR_N32_setfsuid&t;&t;(__NR_N32_Linux + 120)
DECL|macro|__NR_N32_setfsgid
mdefine_line|#define __NR_N32_setfsgid&t;&t;(__NR_N32_Linux + 121)
DECL|macro|__NR_N32_getsid
mdefine_line|#define __NR_N32_getsid&t;&t;&t;(__NR_N32_Linux + 122)
DECL|macro|__NR_N32_capget
mdefine_line|#define __NR_N32_capget&t;&t;&t;(__NR_N32_Linux + 123)
DECL|macro|__NR_N32_capset
mdefine_line|#define __NR_N32_capset&t;&t;&t;(__NR_N32_Linux + 124)
DECL|macro|__NR_N32_rt_sigpending
mdefine_line|#define __NR_N32_rt_sigpending&t;&t;(__NR_N32_Linux + 125)
DECL|macro|__NR_N32_rt_sigtimedwait
mdefine_line|#define __NR_N32_rt_sigtimedwait&t;(__NR_N32_Linux + 126)
DECL|macro|__NR_N32_rt_sigqueueinfo
mdefine_line|#define __NR_N32_rt_sigqueueinfo&t;(__NR_N32_Linux + 127)
DECL|macro|__NR_N32_rt_sigsuspend
mdefine_line|#define __NR_N32_rt_sigsuspend&t;&t;(__NR_N32_Linux + 128)
DECL|macro|__NR_N32_sigaltstack
mdefine_line|#define __NR_N32_sigaltstack&t;&t;(__NR_N32_Linux + 129)
DECL|macro|__NR_N32_utime
mdefine_line|#define __NR_N32_utime&t;&t;&t;(__NR_N32_Linux + 130)
DECL|macro|__NR_N32_mknod
mdefine_line|#define __NR_N32_mknod&t;&t;&t;(__NR_N32_Linux + 131)
DECL|macro|__NR_N32_personality
mdefine_line|#define __NR_N32_personality&t;&t;(__NR_N32_Linux + 132)
DECL|macro|__NR_N32_ustat
mdefine_line|#define __NR_N32_ustat&t;&t;&t;(__NR_N32_Linux + 133)
DECL|macro|__NR_N32_statfs
mdefine_line|#define __NR_N32_statfs&t;&t;&t;(__NR_N32_Linux + 134)
DECL|macro|__NR_N32_fstatfs
mdefine_line|#define __NR_N32_fstatfs&t;&t;(__NR_N32_Linux + 135)
DECL|macro|__NR_N32_sysfs
mdefine_line|#define __NR_N32_sysfs&t;&t;&t;(__NR_N32_Linux + 136)
DECL|macro|__NR_N32_getpriority
mdefine_line|#define __NR_N32_getpriority&t;&t;(__NR_N32_Linux + 137)
DECL|macro|__NR_N32_setpriority
mdefine_line|#define __NR_N32_setpriority&t;&t;(__NR_N32_Linux + 138)
DECL|macro|__NR_N32_sched_setparam
mdefine_line|#define __NR_N32_sched_setparam&t;&t;(__NR_N32_Linux + 139)
DECL|macro|__NR_N32_sched_getparam
mdefine_line|#define __NR_N32_sched_getparam&t;&t;(__NR_N32_Linux + 140)
DECL|macro|__NR_N32_sched_setscheduler
mdefine_line|#define __NR_N32_sched_setscheduler&t;(__NR_N32_Linux + 141)
DECL|macro|__NR_N32_sched_getscheduler
mdefine_line|#define __NR_N32_sched_getscheduler&t;(__NR_N32_Linux + 142)
DECL|macro|__NR_N32_sched_get_priority_max
mdefine_line|#define __NR_N32_sched_get_priority_max&t;(__NR_N32_Linux + 143)
DECL|macro|__NR_N32_sched_get_priority_min
mdefine_line|#define __NR_N32_sched_get_priority_min&t;(__NR_N32_Linux + 144)
DECL|macro|__NR_N32_sched_rr_get_interval
mdefine_line|#define __NR_N32_sched_rr_get_interval&t;(__NR_N32_Linux + 145)
DECL|macro|__NR_N32_mlock
mdefine_line|#define __NR_N32_mlock&t;&t;&t;(__NR_N32_Linux + 146)
DECL|macro|__NR_N32_munlock
mdefine_line|#define __NR_N32_munlock&t;&t;(__NR_N32_Linux + 147)
DECL|macro|__NR_N32_mlockall
mdefine_line|#define __NR_N32_mlockall&t;&t;(__NR_N32_Linux + 148)
DECL|macro|__NR_N32_munlockall
mdefine_line|#define __NR_N32_munlockall&t;&t;(__NR_N32_Linux + 149)
DECL|macro|__NR_N32_vhangup
mdefine_line|#define __NR_N32_vhangup&t;&t;(__NR_N32_Linux + 150)
DECL|macro|__NR_N32_pivot_root
mdefine_line|#define __NR_N32_pivot_root&t;&t;(__NR_N32_Linux + 151)
DECL|macro|__NR_N32__sysctl
mdefine_line|#define __NR_N32__sysctl&t;&t;(__NR_N32_Linux + 152)
DECL|macro|__NR_N32_prctl
mdefine_line|#define __NR_N32_prctl&t;&t;&t;(__NR_N32_Linux + 153)
DECL|macro|__NR_N32_adjtimex
mdefine_line|#define __NR_N32_adjtimex&t;&t;(__NR_N32_Linux + 154)
DECL|macro|__NR_N32_setrlimit
mdefine_line|#define __NR_N32_setrlimit&t;&t;(__NR_N32_Linux + 155)
DECL|macro|__NR_N32_chroot
mdefine_line|#define __NR_N32_chroot&t;&t;&t;(__NR_N32_Linux + 156)
DECL|macro|__NR_N32_sync
mdefine_line|#define __NR_N32_sync&t;&t;&t;(__NR_N32_Linux + 157)
DECL|macro|__NR_N32_acct
mdefine_line|#define __NR_N32_acct&t;&t;&t;(__NR_N32_Linux + 158)
DECL|macro|__NR_N32_settimeofday
mdefine_line|#define __NR_N32_settimeofday&t;&t;(__NR_N32_Linux + 159)
DECL|macro|__NR_N32_mount
mdefine_line|#define __NR_N32_mount&t;&t;&t;(__NR_N32_Linux + 160)
DECL|macro|__NR_N32_umount2
mdefine_line|#define __NR_N32_umount2&t;&t;(__NR_N32_Linux + 161)
DECL|macro|__NR_N32_swapon
mdefine_line|#define __NR_N32_swapon&t;&t;&t;(__NR_N32_Linux + 162)
DECL|macro|__NR_N32_swapoff
mdefine_line|#define __NR_N32_swapoff&t;&t;(__NR_N32_Linux + 163)
DECL|macro|__NR_N32_reboot
mdefine_line|#define __NR_N32_reboot&t;&t;&t;(__NR_N32_Linux + 164)
DECL|macro|__NR_N32_sethostname
mdefine_line|#define __NR_N32_sethostname&t;&t;(__NR_N32_Linux + 165)
DECL|macro|__NR_N32_setdomainname
mdefine_line|#define __NR_N32_setdomainname&t;&t;(__NR_N32_Linux + 166)
DECL|macro|__NR_N32_create_module
mdefine_line|#define __NR_N32_create_module&t;&t;(__NR_N32_Linux + 167)
DECL|macro|__NR_N32_init_module
mdefine_line|#define __NR_N32_init_module&t;&t;(__NR_N32_Linux + 168)
DECL|macro|__NR_N32_delete_module
mdefine_line|#define __NR_N32_delete_module&t;&t;(__NR_N32_Linux + 169)
DECL|macro|__NR_N32_get_kernel_syms
mdefine_line|#define __NR_N32_get_kernel_syms&t;(__NR_N32_Linux + 170)
DECL|macro|__NR_N32_query_module
mdefine_line|#define __NR_N32_query_module&t;&t;(__NR_N32_Linux + 171)
DECL|macro|__NR_N32_quotactl
mdefine_line|#define __NR_N32_quotactl&t;&t;(__NR_N32_Linux + 172)
DECL|macro|__NR_N32_nfsservctl
mdefine_line|#define __NR_N32_nfsservctl&t;&t;(__NR_N32_Linux + 173)
DECL|macro|__NR_N32_getpmsg
mdefine_line|#define __NR_N32_getpmsg&t;&t;(__NR_N32_Linux + 174)
DECL|macro|__NR_N32_putpmsg
mdefine_line|#define __NR_N32_putpmsg&t;&t;(__NR_N32_Linux + 175)
DECL|macro|__NR_N32_afs_syscall
mdefine_line|#define __NR_N32_afs_syscall&t;&t;(__NR_N32_Linux + 176)
DECL|macro|__NR_N32_reserved177
mdefine_line|#define __NR_N32_reserved177&t;&t;(__NR_N32_Linux + 177)
DECL|macro|__NR_N32_gettid
mdefine_line|#define __NR_N32_gettid&t;&t;&t;(__NR_N32_Linux + 178)
DECL|macro|__NR_N32_readahead
mdefine_line|#define __NR_N32_readahead&t;&t;(__NR_N32_Linux + 179)
DECL|macro|__NR_N32_setxattr
mdefine_line|#define __NR_N32_setxattr&t;&t;(__NR_N32_Linux + 180)
DECL|macro|__NR_N32_lsetxattr
mdefine_line|#define __NR_N32_lsetxattr&t;&t;(__NR_N32_Linux + 181)
DECL|macro|__NR_N32_fsetxattr
mdefine_line|#define __NR_N32_fsetxattr&t;&t;(__NR_N32_Linux + 182)
DECL|macro|__NR_N32_getxattr
mdefine_line|#define __NR_N32_getxattr&t;&t;(__NR_N32_Linux + 183)
DECL|macro|__NR_N32_lgetxattr
mdefine_line|#define __NR_N32_lgetxattr&t;&t;(__NR_N32_Linux + 184)
DECL|macro|__NR_N32_fgetxattr
mdefine_line|#define __NR_N32_fgetxattr&t;&t;(__NR_N32_Linux + 185)
DECL|macro|__NR_N32_listxattr
mdefine_line|#define __NR_N32_listxattr&t;&t;(__NR_N32_Linux + 186)
DECL|macro|__NR_N32_llistxattr
mdefine_line|#define __NR_N32_llistxattr&t;&t;(__NR_N32_Linux + 187)
DECL|macro|__NR_N32_flistxattr
mdefine_line|#define __NR_N32_flistxattr&t;&t;(__NR_N32_Linux + 188)
DECL|macro|__NR_N32_removexattr
mdefine_line|#define __NR_N32_removexattr&t;&t;(__NR_N32_Linux + 189)
DECL|macro|__NR_N32_lremovexattr
mdefine_line|#define __NR_N32_lremovexattr&t;&t;(__NR_N32_Linux + 190)
DECL|macro|__NR_N32_fremovexattr
mdefine_line|#define __NR_N32_fremovexattr&t;&t;(__NR_N32_Linux + 191)
DECL|macro|__NR_N32_tkill
mdefine_line|#define __NR_N32_tkill&t;&t;&t;(__NR_N32_Linux + 192)
DECL|macro|__NR_N32_time
mdefine_line|#define __NR_N32_time&t;&t;&t;(__NR_N32_Linux + 193)
DECL|macro|__NR_N32_futex
mdefine_line|#define __NR_N32_futex&t;&t;&t;(__NR_N32_Linux + 194)
DECL|macro|__NR_N32_sched_setaffinity
mdefine_line|#define __NR_N32_sched_setaffinity&t;(__NR_N32_Linux + 195)
DECL|macro|__NR_N32_sched_getaffinity
mdefine_line|#define __NR_N32_sched_getaffinity&t;(__NR_N32_Linux + 196)
DECL|macro|__NR_N32_cacheflush
mdefine_line|#define __NR_N32_cacheflush&t;&t;(__NR_N32_Linux + 197)
DECL|macro|__NR_N32_cachectl
mdefine_line|#define __NR_N32_cachectl&t;&t;(__NR_N32_Linux + 198)
DECL|macro|__NR_N32_sysmips
mdefine_line|#define __NR_N32_sysmips&t;&t;(__NR_N32_Linux + 199)
DECL|macro|__NR_N32_io_setup
mdefine_line|#define __NR_N32_io_setup&t;&t;(__NR_N32_Linux + 200)
DECL|macro|__NR_N32_io_destroy
mdefine_line|#define __NR_N32_io_destroy&t;&t;(__NR_N32_Linux + 201)
DECL|macro|__NR_N32_io_getevents
mdefine_line|#define __NR_N32_io_getevents&t;&t;(__NR_N32_Linux + 202)
DECL|macro|__NR_N32_io_submit
mdefine_line|#define __NR_N32_io_submit&t;&t;(__NR_N32_Linux + 203)
DECL|macro|__NR_N32_io_cancel
mdefine_line|#define __NR_N32_io_cancel&t;&t;(__NR_N32_Linux + 204)
DECL|macro|__NR_N32_exit_group
mdefine_line|#define __NR_N32_exit_group&t;&t;(__NR_N32_Linux + 205)
DECL|macro|__NR_N32_lookup_dcookie
mdefine_line|#define __NR_N32_lookup_dcookie&t;&t;(__NR_N32_Linux + 206)
DECL|macro|__NR_N32_epoll_create
mdefine_line|#define __NR_N32_epoll_create&t;&t;(__NR_N32_Linux + 207)
DECL|macro|__NR_N32_epoll_ctl
mdefine_line|#define __NR_N32_epoll_ctl&t;&t;(__NR_N32_Linux + 208)
DECL|macro|__NR_N32_epoll_wait
mdefine_line|#define __NR_N32_epoll_wait&t;&t;(__NR_N32_Linux + 209)
DECL|macro|__NR_N32_remap_file_page
mdefine_line|#define __NR_N32_remap_file_page&t;(__NR_N32_Linux + 210)
DECL|macro|__NR_N32_rt_sigreturn
mdefine_line|#define __NR_N32_rt_sigreturn&t;&t;(__NR_N32_Linux + 211)
DECL|macro|__NR_N32_fcntl64
mdefine_line|#define __NR_N32_fcntl64&t;&t;(__NR_N32_Linux + 212)
DECL|macro|__NR_N32_set_tid_address
mdefine_line|#define __NR_N32_set_tid_address&t;(__NR_N32_Linux + 213)
DECL|macro|__NR_N32_restart_syscall
mdefine_line|#define __NR_N32_restart_syscall&t;(__NR_N32_Linux + 214)
DECL|macro|__NR_N32_semtimedop
mdefine_line|#define __NR_N32_semtimedop&t;&t;(__NR_N32_Linux + 215)
DECL|macro|__NR_N32_fadvise64
mdefine_line|#define __NR_N32_fadvise64&t;&t;(__NR_N32_Linux + 216)
DECL|macro|__NR_N32_statfs64
mdefine_line|#define __NR_N32_statfs64&t;&t;(__NR_N32_Linux + 217)
DECL|macro|__NR_N32_fstatfs64
mdefine_line|#define __NR_N32_fstatfs64&t;&t;(__NR_N32_Linux + 218)
multiline_comment|/*&n; * Offset of the last N32 flavoured syscall&n; */
DECL|macro|__NR_N32_Linux_syscalls
mdefine_line|#define __NR_N32_Linux_syscalls&t;&t;218
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/* XXX - _foo needs to be __foo, while __NR_bar could be _NR_bar. */
DECL|macro|_syscall0
mdefine_line|#define _syscall0(type,name) &bslash;&n;type name(void) &bslash;&n;{ &bslash;&n;&t;register unsigned long __v0 asm(&quot;$2&quot;) = __NR_##name; &bslash;&n;&t;register unsigned long __a3 asm(&quot;$7&quot;); &bslash;&n;&t;&bslash;&n;&t;__asm__ volatile ( &bslash;&n;&t;&quot;.set&bslash;tnoreorder&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;li&bslash;t$2, %2&bslash;t&bslash;t&bslash;t# &quot; #name &quot;&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;syscall&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;.set&bslash;treorder&quot; &bslash;&n;&t;: &quot;=&amp;r&quot; (__v0), &quot;=r&quot; (__a3) &bslash;&n;&t;: &quot;i&quot; (__NR_##name) &bslash;&n;&t;: &quot;$8&quot;, &quot;$9&quot;, &quot;$10&quot;, &quot;$11&quot;, &quot;$12&quot;, &quot;$13&quot;, &quot;$14&quot;, &quot;$15&quot;, &quot;$24&quot;); &bslash;&n;&t;&bslash;&n;&t;if (__a3 == 0) &bslash;&n;&t;&t;return (type) __v0; &bslash;&n;&t;errno = __v0; &bslash;&n;&t;return -1; &bslash;&n;}
multiline_comment|/*&n; * DANGER: This macro isn&squot;t usable for the pipe(2) call&n; * which has a unusual return convention.&n; */
DECL|macro|_syscall1
mdefine_line|#define _syscall1(type,name,atype,a) &bslash;&n;type name(atype a) &bslash;&n;{ &bslash;&n;&t;register unsigned long __v0 asm(&quot;$2&quot;) = __NR_##name; &bslash;&n;&t;register unsigned long __a0 asm(&quot;$4&quot;) = (unsigned long) a; &bslash;&n;&t;register unsigned long __a3 asm(&quot;$7&quot;); &bslash;&n;&t;&bslash;&n;&t;__asm__ volatile ( &bslash;&n;&t;&quot;.set&bslash;tnoreorder&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;li&bslash;t$2, %3&bslash;t&bslash;t&bslash;t# &quot; #name &quot;&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;syscall&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;.set&bslash;treorder&quot; &bslash;&n;&t;: &quot;=&amp;r&quot; (__v0), &quot;=r&quot; (__a3) &bslash;&n;&t;: &quot;r&quot; (__a0), &quot;i&quot; (__NR_##name) &bslash;&n;&t;: &quot;$8&quot;, &quot;$9&quot;, &quot;$10&quot;, &quot;$11&quot;, &quot;$12&quot;, &quot;$13&quot;, &quot;$14&quot;, &quot;$15&quot;, &quot;$24&quot;); &bslash;&n;&t;&bslash;&n;&t;if (__a3 == 0) &bslash;&n;&t;&t;return (type) __v0; &bslash;&n;&t;errno = __v0; &bslash;&n;&t;return -1; &bslash;&n;}
DECL|macro|_syscall2
mdefine_line|#define _syscall2(type,name,atype,a,btype,b) &bslash;&n;type name(atype a, btype b) &bslash;&n;{ &bslash;&n;&t;register unsigned long __v0 asm(&quot;$2&quot;) = __NR_##name; &bslash;&n;&t;register unsigned long __a0 asm(&quot;$4&quot;) = (unsigned long) a; &bslash;&n;&t;register unsigned long __a1 asm(&quot;$5&quot;) = (unsigned long) b; &bslash;&n;&t;register unsigned long __a3 asm(&quot;$7&quot;); &bslash;&n;&t;&bslash;&n;&t;__asm__ volatile ( &bslash;&n;&t;&quot;.set&bslash;tnoreorder&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;li&bslash;t$2, %4&bslash;t&bslash;t&bslash;t# &quot; #name &quot;&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;syscall&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;.set&bslash;treorder&quot; &bslash;&n;&t;: &quot;=&amp;r&quot; (__v0), &quot;=r&quot; (__a3) &bslash;&n;&t;: &quot;r&quot; (__a0), &quot;r&quot; (__a1), &quot;i&quot; (__NR_##name) &bslash;&n;&t;: &quot;$8&quot;, &quot;$9&quot;, &quot;$10&quot;, &quot;$11&quot;, &quot;$12&quot;, &quot;$13&quot;, &quot;$14&quot;, &quot;$15&quot;, &quot;$24&quot;); &bslash;&n;&t;&bslash;&n;&t;if (__a3 == 0) &bslash;&n;&t;&t;return (type) __v0; &bslash;&n;&t;errno = __v0; &bslash;&n;&t;return -1; &bslash;&n;}
DECL|macro|_syscall3
mdefine_line|#define _syscall3(type,name,atype,a,btype,b,ctype,c) &bslash;&n;type name(atype a, btype b, ctype c) &bslash;&n;{ &bslash;&n;&t;register unsigned long __v0 asm(&quot;$2&quot;) = __NR_##name; &bslash;&n;&t;register unsigned long __a0 asm(&quot;$4&quot;) = (unsigned long) a; &bslash;&n;&t;register unsigned long __a1 asm(&quot;$5&quot;) = (unsigned long) b; &bslash;&n;&t;register unsigned long __a2 asm(&quot;$6&quot;) = (unsigned long) c; &bslash;&n;&t;register unsigned long __a3 asm(&quot;$7&quot;); &bslash;&n;&t;&bslash;&n;&t;__asm__ volatile ( &bslash;&n;&t;&quot;.set&bslash;tnoreorder&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;li&bslash;t$2, %5&bslash;t&bslash;t&bslash;t# &quot; #name &quot;&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;syscall&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;.set&bslash;treorder&quot; &bslash;&n;&t;: &quot;=&amp;r&quot; (__v0), &quot;=r&quot; (__a3) &bslash;&n;&t;: &quot;r&quot; (__a0), &quot;r&quot; (__a1), &quot;r&quot; (__a2), &quot;i&quot; (__NR_##name) &bslash;&n;&t;: &quot;$8&quot;, &quot;$9&quot;, &quot;$10&quot;, &quot;$11&quot;, &quot;$12&quot;, &quot;$13&quot;, &quot;$14&quot;, &quot;$15&quot;, &quot;$24&quot;); &bslash;&n;&t;&bslash;&n;&t;if (__a3 == 0) &bslash;&n;&t;&t;return (type) __v0; &bslash;&n;&t;errno = __v0; &bslash;&n;&t;return -1; &bslash;&n;}
DECL|macro|_syscall4
mdefine_line|#define _syscall4(type,name,atype,a,btype,b,ctype,c,dtype,d) &bslash;&n;type name(atype a, btype b, ctype c, dtype d) &bslash;&n;{ &bslash;&n;&t;register unsigned long __v0 asm(&quot;$2&quot;) = __NR_##name; &bslash;&n;&t;register unsigned long __a0 asm(&quot;$4&quot;) = (unsigned long) a; &bslash;&n;&t;register unsigned long __a1 asm(&quot;$5&quot;) = (unsigned long) b; &bslash;&n;&t;register unsigned long __a2 asm(&quot;$6&quot;) = (unsigned long) c; &bslash;&n;&t;register unsigned long __a3 asm(&quot;$7&quot;) = (unsigned long) d; &bslash;&n;&t;&bslash;&n;&t;__asm__ volatile ( &bslash;&n;&t;&quot;.set&bslash;tnoreorder&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;li&bslash;t$2, %5&bslash;t&bslash;t&bslash;t# &quot; #name &quot;&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;syscall&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;.set&bslash;treorder&quot; &bslash;&n;&t;: &quot;=&amp;r&quot; (__v0), &quot;+r&quot; (__a3) &bslash;&n;&t;: &quot;r&quot; (__a0), &quot;r&quot; (__a1), &quot;r&quot; (__a2), &quot;i&quot; (__NR_##name) &bslash;&n;&t;: &quot;$8&quot;, &quot;$9&quot;, &quot;$10&quot;, &quot;$11&quot;, &quot;$12&quot;, &quot;$13&quot;, &quot;$14&quot;, &quot;$15&quot;, &quot;$24&quot;); &bslash;&n;&t;&bslash;&n;&t;if (__a3 == 0) &bslash;&n;&t;&t;return (type) __v0; &bslash;&n;&t;errno = __v0; &bslash;&n;&t;return -1; &bslash;&n;}
macro_line|#if (_MIPS_SIM == _ABIN32) || (_MIPS_SIM == _ABI64)
DECL|macro|_syscall5
mdefine_line|#define _syscall5(type,name,atype,a,btype,b,ctype,c,dtype,d,etype,e) &bslash;&n;type name (atype a,btype b,ctype c,dtype d,etype e) &bslash;&n;{ &bslash;&n;&t;register unsigned long __v0 asm(&quot;$2&quot;) = __NR_##name; &bslash;&n;&t;register unsigned long __a0 asm(&quot;$4&quot;) = (unsigned long) a; &bslash;&n;&t;register unsigned long __a1 asm(&quot;$5&quot;) = (unsigned long) b; &bslash;&n;&t;register unsigned long __a2 asm(&quot;$6&quot;) = (unsigned long) c; &bslash;&n;&t;register unsigned long __a3 asm(&quot;$7&quot;) = (unsigned long) d; &bslash;&n;&t;register unsigned long __a4 asm(&quot;$8&quot;) = (unsigned long) e; &bslash;&n;&t;&bslash;&n;&t;__asm__ volatile ( &bslash;&n;&t;&quot;.set&bslash;tnoreorder&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;li&bslash;t$2, %6&bslash;t&bslash;t&bslash;t# &quot; #name &quot;&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;syscall&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;.set&bslash;treorder&quot; &bslash;&n;&t;: &quot;=&amp;r&quot; (__v0), &quot;+r&quot; (__a3), &quot;+r&quot; (__a4) &bslash;&n;&t;: &quot;r&quot; (__a0), &quot;r&quot; (__a1), &quot;r&quot; (__a2), &quot;i&quot; (__NR_##name) &bslash;&n;&t;: &quot;$9&quot;, &quot;$10&quot;, &quot;$11&quot;, &quot;$12&quot;, &quot;$13&quot;, &quot;$14&quot;, &quot;$15&quot;, &quot;$24&quot;); &bslash;&n;&t;&bslash;&n;&t;if (__a3 == 0) &bslash;&n;&t;&t;return (type) __v0; &bslash;&n;&t;errno = __v0; &bslash;&n;&t;return -1; &bslash;&n;}
DECL|macro|_syscall6
mdefine_line|#define _syscall6(type,name,atype,a,btype,b,ctype,c,dtype,d,etype,e,ftype,f) &bslash;&n;type name (atype a,btype b,ctype c,dtype d,etype e,ftype f) &bslash;&n;{ &bslash;&n;&t;register unsigned long __v0 asm(&quot;$2&quot;) = __NR_##name; &bslash;&n;&t;register unsigned long __a0 asm(&quot;$4&quot;) = (unsigned long) a; &bslash;&n;&t;register unsigned long __a1 asm(&quot;$5&quot;) = (unsigned long) b; &bslash;&n;&t;register unsigned long __a2 asm(&quot;$6&quot;) = (unsigned long) c; &bslash;&n;&t;register unsigned long __a3 asm(&quot;$7&quot;) = (unsigned long) d; &bslash;&n;&t;register unsigned long __a4 asm(&quot;$8&quot;) = (unsigned long) e; &bslash;&n;&t;register unsigned long __a5 asm(&quot;$9&quot;) = (unsigned long) f; &bslash;&n;&t;&bslash;&n;&t;__asm__ volatile ( &quot;&quot; &bslash;&n;&t;: &quot;+r&quot; (__a5) &bslash;&n;&t;: &bslash;&n;&t;: &quot;$9&quot;, &quot;$10&quot;, &quot;$11&quot;, &quot;$12&quot;, &quot;$13&quot;, &quot;$14&quot;, &quot;$15&quot;, &quot;$24&quot;); &bslash;&n;&t;&bslash;&n;&t;__asm__ volatile ( &bslash;&n;&t;&quot;.set&bslash;tnoreorder&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;li&bslash;t$2, %6&bslash;t&bslash;t&bslash;t# &quot; #name &quot;&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;syscall&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;.set&bslash;treorder&quot; &bslash;&n;&t;: &quot;=&amp;r&quot; (__v0), &quot;+r&quot; (__a3), &quot;+r&quot; (__a4) &bslash;&n;&t;: &quot;r&quot; (__a0), &quot;r&quot; (__a1), &quot;r&quot; (__a2), &quot;i&quot; (__NR_##name) &bslash;&n;&t;: &quot;$9&quot;, &quot;$10&quot;, &quot;$11&quot;, &quot;$12&quot;, &quot;$13&quot;, &quot;$14&quot;, &quot;$15&quot;, &quot;$24&quot;); &bslash;&n;&t;&bslash;&n;&t;if (__a3 == 0) &bslash;&n;&t;&t;return (type) __v0; &bslash;&n;&t;errno = __v0; &bslash;&n;&t;return -1; &bslash;&n;}
DECL|macro|_syscall7
mdefine_line|#define _syscall7(type,name,atype,a,btype,b,ctype,c,dtype,d,etype,e,ftype,f,gtype,g) &bslash;&n;type name (atype a,btype b,ctype c,dtype d,etype e,ftype f,gtype g) &bslash;&n;{ &bslash;&n;&t;register unsigned long __v0 asm(&quot;$2&quot;) = __NR_##name; &bslash;&n;&t;register unsigned long __a0 asm(&quot;$4&quot;) = (unsigned long) a; &bslash;&n;&t;register unsigned long __a1 asm(&quot;$5&quot;) = (unsigned long) b; &bslash;&n;&t;register unsigned long __a2 asm(&quot;$6&quot;) = (unsigned long) c; &bslash;&n;&t;register unsigned long __a3 asm(&quot;$7&quot;) = (unsigned long) d; &bslash;&n;&t;register unsigned long __a4 asm(&quot;$8&quot;) = (unsigned long) e; &bslash;&n;&t;register unsigned long __a5 asm(&quot;$9&quot;) = (unsigned long) f; &bslash;&n;&t;register unsigned long __a6 asm(&quot;$10&quot;) = (unsigned long) g; &bslash;&n;&t;&bslash;&n;&t;__asm__ volatile ( &quot;&quot; &bslash;&n;&t;: &quot;+r&quot; (__a5), &quot;+r&quot; (__a6) &bslash;&n;&t;: &bslash;&n;&t;: &quot;$9&quot;, &quot;$10&quot;, &quot;$11&quot;, &quot;$12&quot;, &quot;$13&quot;, &quot;$14&quot;, &quot;$15&quot;, &quot;$24&quot;); &bslash;&n;&t;&bslash;&n;&t;__asm__ volatile ( &bslash;&n;&t;&quot;.set&bslash;tnoreorder&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;li&bslash;t$2, %6&bslash;t&bslash;t&bslash;t# &quot; #name &quot;&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;syscall&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;.set&bslash;treorder&quot; &bslash;&n;&t;: &quot;=&amp;r&quot; (__v0), &quot;+r&quot; (__a3), &quot;+r&quot; (__a4) &bslash;&n;&t;: &quot;r&quot; (__a0), &quot;r&quot; (__a1), &quot;r&quot; (__a2), &quot;i&quot; (__NR_##name) &bslash;&n;&t;: &quot;$9&quot;, &quot;$10&quot;, &quot;$11&quot;, &quot;$12&quot;, &quot;$13&quot;, &quot;$14&quot;, &quot;$15&quot;, &quot;$24&quot;); &bslash;&n;&t;&bslash;&n;&t;if (__a3 == 0) &bslash;&n;&t;&t;return (type) __v0; &bslash;&n;&t;errno = __v0; &bslash;&n;&t;return -1; &bslash;&n;}
macro_line|#else /* not N32 or 64 ABI */
multiline_comment|/*&n; * Using those means your brain needs more than an oil change ;-)&n; */
DECL|macro|_syscall5
mdefine_line|#define _syscall5(type,name,atype,a,btype,b,ctype,c,dtype,d,etype,e) &bslash;&n;type name(atype a, btype b, ctype c, dtype d, etype e) &bslash;&n;{ &bslash;&n;&t;register unsigned long __v0 asm(&quot;$2&quot;) = __NR_##name; &bslash;&n;&t;register unsigned long __a0 asm(&quot;$4&quot;) = (unsigned long) a; &bslash;&n;&t;register unsigned long __a1 asm(&quot;$5&quot;) = (unsigned long) b; &bslash;&n;&t;register unsigned long __a2 asm(&quot;$6&quot;) = (unsigned long) c; &bslash;&n;&t;register unsigned long __a3 asm(&quot;$7&quot;) = (unsigned long) d; &bslash;&n;&t;&bslash;&n;&t;__asm__ volatile ( &bslash;&n;&t;&quot;.set&bslash;tnoreorder&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;lw&bslash;t$2, %6&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;subu&bslash;t$29, 32&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;sw&bslash;t$2, 16($29)&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;li&bslash;t$2, %5&bslash;t&bslash;t&bslash;t# &quot; #name &quot;&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;syscall&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;addiu&bslash;t$29, 32&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;.set&bslash;treorder&quot; &bslash;&n;&t;: &quot;=&amp;r&quot; (__v0), &quot;+r&quot; (__a3) &bslash;&n;&t;: &quot;r&quot; (__a0), &quot;r&quot; (__a1), &quot;r&quot; (__a2), &quot;i&quot; (__NR_##name), &bslash;&n;&t;  &quot;m&quot; ((unsigned long)e) &bslash;&n;&t;: &quot;$8&quot;, &quot;$9&quot;, &quot;$10&quot;, &quot;$11&quot;, &quot;$12&quot;, &quot;$13&quot;, &quot;$14&quot;, &quot;$15&quot;, &quot;$24&quot;); &bslash;&n;&t;&bslash;&n;&t;if (__a3 == 0) &bslash;&n;&t;&t;return (type) __v0; &bslash;&n;&t;errno = __v0; &bslash;&n;&t;return -1; &bslash;&n;}
DECL|macro|_syscall6
mdefine_line|#define _syscall6(type,name,atype,a,btype,b,ctype,c,dtype,d,etype,e,ftype,f) &bslash;&n;type name(atype a, btype b, ctype c, dtype d, etype e, ftype f) &bslash;&n;{ &bslash;&n;&t;register unsigned long __v0 asm(&quot;$2&quot;) = __NR_##name; &bslash;&n;&t;register unsigned long __a0 asm(&quot;$4&quot;) = (unsigned long) a; &bslash;&n;&t;register unsigned long __a1 asm(&quot;$5&quot;) = (unsigned long) b; &bslash;&n;&t;register unsigned long __a2 asm(&quot;$6&quot;) = (unsigned long) c; &bslash;&n;&t;register unsigned long __a3 asm(&quot;$7&quot;) = (unsigned long) d; &bslash;&n;&t;&bslash;&n;&t;__asm__ volatile ( &bslash;&n;&t;&quot;.set&bslash;tnoreorder&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;lw&bslash;t$2, %6&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;lw&bslash;t$8, %7&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;subu&bslash;t$29, 32&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;sw&bslash;t$2, 16($29)&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;sw&bslash;t$8, 20($29)&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;li&bslash;t$2, %5&bslash;t&bslash;t&bslash;t# &quot; #name &quot;&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;syscall&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;addiu&bslash;t$29, 32&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;.set&bslash;treorder&quot; &bslash;&n;&t;: &quot;=&amp;r&quot; (__v0), &quot;+r&quot; (__a3) &bslash;&n;&t;: &quot;r&quot; (__a0), &quot;r&quot; (__a1), &quot;r&quot; (__a2), &quot;i&quot; (__NR_##name), &bslash;&n;&t;  &quot;m&quot; ((unsigned long)e), &quot;m&quot; ((unsigned long)f) &bslash;&n;&t;: &quot;$8&quot;, &quot;$9&quot;, &quot;$10&quot;, &quot;$11&quot;, &quot;$12&quot;, &quot;$13&quot;, &quot;$14&quot;, &quot;$15&quot;, &quot;$24&quot;); &bslash;&n;&t;&bslash;&n;&t;if (__a3 == 0) &bslash;&n;&t;&t;return (type) __v0; &bslash;&n;&t;errno = __v0; &bslash;&n;&t;return -1; &bslash;&n;}
DECL|macro|_syscall7
mdefine_line|#define _syscall7(type,name,atype,a,btype,b,ctype,c,dtype,d,etype,e,ftype,f,gtype,g) &bslash;&n;type name(atype a, btype b, ctype c, dtype d, etype e, ftype f, gtype g) &bslash;&n;{ &bslash;&n;&t;register unsigned long __v0 asm(&quot;$2&quot;) = __NR_##name; &bslash;&n;&t;register unsigned long __a0 asm(&quot;$4&quot;) = (unsigned long) a; &bslash;&n;&t;register unsigned long __a1 asm(&quot;$5&quot;) = (unsigned long) b; &bslash;&n;&t;register unsigned long __a2 asm(&quot;$6&quot;) = (unsigned long) c; &bslash;&n;&t;register unsigned long __a3 asm(&quot;$7&quot;) = (unsigned long) d; &bslash;&n;&t;&bslash;&n;&t;__asm__ volatile ( &bslash;&n;&t;&quot;.set&bslash;tnoreorder&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;lw&bslash;t$2, %6&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;lw&bslash;t$8, %7&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;lw&bslash;t$9, %8&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;subu&bslash;t$29, 32&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;sw&bslash;t$2, 16($29)&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;sw&bslash;t$8, 20($29)&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;sw&bslash;t$9, 24($29)&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;li&bslash;t$2, %5&bslash;t&bslash;t&bslash;t# &quot; #name &quot;&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;syscall&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;addiu&bslash;t$29, 32&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;.set&bslash;treorder&quot; &bslash;&n;&t;: &quot;=&amp;r&quot; (__v0), &quot;+r&quot; (__a3) &bslash;&n;&t;: &quot;r&quot; (__a0), &quot;r&quot; (__a1), &quot;r&quot; (__a2), &quot;i&quot; (__NR_##name), &bslash;&n;&t;  &quot;m&quot; ((unsigned long)e), &quot;m&quot; ((unsigned long)f), &bslash;&n;&t;  &quot;m&quot; ((unsigned long)g), &bslash;&n;&t;: &quot;$8&quot;, &quot;$9&quot;, &quot;$10&quot;, &quot;$11&quot;, &quot;$12&quot;, &quot;$13&quot;, &quot;$14&quot;, &quot;$15&quot;, &quot;$24&quot;); &bslash;&n;&t;&bslash;&n;&t;if (__a3 == 0) &bslash;&n;&t;&t;return (type) __v0; &bslash;&n;&t;errno = __v0; &bslash;&n;&t;return -1; &bslash;&n;}
macro_line|#endif
macro_line|#ifdef __KERNEL_SYSCALLS__
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
r_struct
id|rusage
suffix:semicolon
r_static
r_inline
id|_syscall4
c_func
(paren
id|pid_t
comma
id|wait4
comma
id|pid_t
comma
id|pid
comma
r_int
op_star
comma
id|stat_addr
comma
r_int
comma
id|options
comma
r_struct
id|rusage
op_star
comma
id|ru
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
id|wait4
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
macro_line|#endif /* __KERNEL_SYSCALLS__ */
macro_line|#endif /* !__ASSEMBLY__ */
multiline_comment|/*&n; * &quot;Conditional&quot; syscalls&n; *&n; * What we want is __attribute__((weak,alias(&quot;sys_ni_syscall&quot;))),&n; * but it doesn&squot;t work on all toolchains, so we just do it by hand&n; */
DECL|macro|cond_syscall
mdefine_line|#define cond_syscall(x) asm(&quot;.weak&bslash;t&quot; #x &quot;&bslash;n&quot; #x &quot;&bslash;t=&bslash;tsys_ni_syscall&quot;);
macro_line|#endif /* _ASM_UNISTD_H */
eof
