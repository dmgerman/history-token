multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1995, 96, 97, 98, 99, 2000 by Ralf Baechle&n; */
macro_line|#ifndef _ASM_RISCOS_SYSCALL_H
DECL|macro|_ASM_RISCOS_SYSCALL_H
mdefine_line|#define _ASM_RISCOS_SYSCALL_H
multiline_comment|/*&n; * The syscalls 0 - 3999 are reserved for a down to the root syscall&n; * compatibility with RISC/os and IRIX.  We&squot;ll see how to deal with the&n; * various &quot;real&quot; BSD variants like Ultrix, NetBSD ...&n; */
multiline_comment|/*&n; * SVR4 syscalls are in the range from 1 to 999&n; */
DECL|macro|__NR_SVR4
mdefine_line|#define __NR_SVR4&t;&t;&t;0
DECL|macro|__NR_SVR4_syscall
mdefine_line|#define __NR_SVR4_syscall&t;&t;(__NR_SVR4 +   0)
DECL|macro|__NR_SVR4_exit
mdefine_line|#define __NR_SVR4_exit&t;&t;&t;(__NR_SVR4 +   1)
DECL|macro|__NR_SVR4_fork
mdefine_line|#define __NR_SVR4_fork&t;&t;&t;(__NR_SVR4 +   2)
DECL|macro|__NR_SVR4_read
mdefine_line|#define __NR_SVR4_read&t;&t;&t;(__NR_SVR4 +   3)
DECL|macro|__NR_SVR4_write
mdefine_line|#define __NR_SVR4_write&t;&t;&t;(__NR_SVR4 +   4)
DECL|macro|__NR_SVR4_open
mdefine_line|#define __NR_SVR4_open&t;&t;&t;(__NR_SVR4 +   5)
DECL|macro|__NR_SVR4_close
mdefine_line|#define __NR_SVR4_close&t;&t;&t;(__NR_SVR4 +   6)
DECL|macro|__NR_SVR4_wait
mdefine_line|#define __NR_SVR4_wait&t;&t;&t;(__NR_SVR4 +   7)
DECL|macro|__NR_SVR4_creat
mdefine_line|#define __NR_SVR4_creat&t;&t;&t;(__NR_SVR4 +   8)
DECL|macro|__NR_SVR4_link
mdefine_line|#define __NR_SVR4_link&t;&t;&t;(__NR_SVR4 +   9)
DECL|macro|__NR_SVR4_unlink
mdefine_line|#define __NR_SVR4_unlink&t;&t;(__NR_SVR4 +  10)
DECL|macro|__NR_SVR4_exec
mdefine_line|#define __NR_SVR4_exec&t;&t;&t;(__NR_SVR4 +  11)
DECL|macro|__NR_SVR4_chdir
mdefine_line|#define __NR_SVR4_chdir&t;&t;&t;(__NR_SVR4 +  12)
DECL|macro|__NR_SVR4_gtime
mdefine_line|#define __NR_SVR4_gtime&t;&t;&t;(__NR_SVR4 +  13)
DECL|macro|__NR_SVR4_mknod
mdefine_line|#define __NR_SVR4_mknod&t;&t;&t;(__NR_SVR4 +  14)
DECL|macro|__NR_SVR4_chmod
mdefine_line|#define __NR_SVR4_chmod&t;&t;&t;(__NR_SVR4 +  15)
DECL|macro|__NR_SVR4_chown
mdefine_line|#define __NR_SVR4_chown&t;&t;&t;(__NR_SVR4 +  16)
DECL|macro|__NR_SVR4_sbreak
mdefine_line|#define __NR_SVR4_sbreak&t;&t;(__NR_SVR4 +  17)
DECL|macro|__NR_SVR4_stat
mdefine_line|#define __NR_SVR4_stat&t;&t;&t;(__NR_SVR4 +  18)
DECL|macro|__NR_SVR4_lseek
mdefine_line|#define __NR_SVR4_lseek&t;&t;&t;(__NR_SVR4 +  19)
DECL|macro|__NR_SVR4_getpid
mdefine_line|#define __NR_SVR4_getpid&t;&t;(__NR_SVR4 +  20)
DECL|macro|__NR_SVR4_mount
mdefine_line|#define __NR_SVR4_mount&t;&t;&t;(__NR_SVR4 +  21)
DECL|macro|__NR_SVR4_umount
mdefine_line|#define __NR_SVR4_umount&t;&t;(__NR_SVR4 +  22)
DECL|macro|__NR_SVR4_setuid
mdefine_line|#define __NR_SVR4_setuid&t;&t;(__NR_SVR4 +  23)
DECL|macro|__NR_SVR4_getuid
mdefine_line|#define __NR_SVR4_getuid&t;&t;(__NR_SVR4 +  24)
DECL|macro|__NR_SVR4_stime
mdefine_line|#define __NR_SVR4_stime&t;&t;&t;(__NR_SVR4 +  25)
DECL|macro|__NR_SVR4_ptrace
mdefine_line|#define __NR_SVR4_ptrace&t;&t;(__NR_SVR4 +  26)
DECL|macro|__NR_SVR4_alarm
mdefine_line|#define __NR_SVR4_alarm&t;&t;&t;(__NR_SVR4 +  27)
DECL|macro|__NR_SVR4_fstat
mdefine_line|#define __NR_SVR4_fstat&t;&t;&t;(__NR_SVR4 +  28)
DECL|macro|__NR_SVR4_pause
mdefine_line|#define __NR_SVR4_pause&t;&t;&t;(__NR_SVR4 +  29)
DECL|macro|__NR_SVR4_utime
mdefine_line|#define __NR_SVR4_utime&t;&t;&t;(__NR_SVR4 +  30)
DECL|macro|__NR_SVR4_stty
mdefine_line|#define __NR_SVR4_stty&t;&t;&t;(__NR_SVR4 +  31)
DECL|macro|__NR_SVR4_gtty
mdefine_line|#define __NR_SVR4_gtty&t;&t;&t;(__NR_SVR4 +  32)
DECL|macro|__NR_SVR4_access
mdefine_line|#define __NR_SVR4_access&t;&t;(__NR_SVR4 +  33)
DECL|macro|__NR_SVR4_nice
mdefine_line|#define __NR_SVR4_nice&t;&t;&t;(__NR_SVR4 +  34)
DECL|macro|__NR_SVR4_statfs
mdefine_line|#define __NR_SVR4_statfs&t;&t;(__NR_SVR4 +  35)
DECL|macro|__NR_SVR4_sync
mdefine_line|#define __NR_SVR4_sync&t;&t;&t;(__NR_SVR4 +  36)
DECL|macro|__NR_SVR4_kill
mdefine_line|#define __NR_SVR4_kill&t;&t;&t;(__NR_SVR4 +  37)
DECL|macro|__NR_SVR4_fstatfs
mdefine_line|#define __NR_SVR4_fstatfs&t;&t;(__NR_SVR4 +  38)
DECL|macro|__NR_SVR4_setpgrp
mdefine_line|#define __NR_SVR4_setpgrp&t;&t;(__NR_SVR4 +  39)
DECL|macro|__NR_SVR4_cxenix
mdefine_line|#define __NR_SVR4_cxenix&t;&t;(__NR_SVR4 +  40)
DECL|macro|__NR_SVR4_dup
mdefine_line|#define __NR_SVR4_dup&t;&t;&t;(__NR_SVR4 +  41)
DECL|macro|__NR_SVR4_pipe
mdefine_line|#define __NR_SVR4_pipe&t;&t;&t;(__NR_SVR4 +  42)
DECL|macro|__NR_SVR4_times
mdefine_line|#define __NR_SVR4_times&t;&t;&t;(__NR_SVR4 +  43)
DECL|macro|__NR_SVR4_profil
mdefine_line|#define __NR_SVR4_profil&t;&t;(__NR_SVR4 +  44)
DECL|macro|__NR_SVR4_plock
mdefine_line|#define __NR_SVR4_plock&t;&t;&t;(__NR_SVR4 +  45)
DECL|macro|__NR_SVR4_setgid
mdefine_line|#define __NR_SVR4_setgid&t;&t;(__NR_SVR4 +  46)
DECL|macro|__NR_SVR4_getgid
mdefine_line|#define __NR_SVR4_getgid&t;&t;(__NR_SVR4 +  47)
DECL|macro|__NR_SVR4_sig
mdefine_line|#define __NR_SVR4_sig&t;&t;&t;(__NR_SVR4 +  48)
DECL|macro|__NR_SVR4_msgsys
mdefine_line|#define __NR_SVR4_msgsys&t;&t;(__NR_SVR4 +  49)
DECL|macro|__NR_SVR4_sysmips
mdefine_line|#define __NR_SVR4_sysmips&t;&t;(__NR_SVR4 +  50)
DECL|macro|__NR_SVR4_sysacct
mdefine_line|#define __NR_SVR4_sysacct&t;&t;(__NR_SVR4 +  51)
DECL|macro|__NR_SVR4_shmsys
mdefine_line|#define __NR_SVR4_shmsys&t;&t;(__NR_SVR4 +  52)
DECL|macro|__NR_SVR4_semsys
mdefine_line|#define __NR_SVR4_semsys&t;&t;(__NR_SVR4 +  53)
DECL|macro|__NR_SVR4_ioctl
mdefine_line|#define __NR_SVR4_ioctl&t;&t;&t;(__NR_SVR4 +  54)
DECL|macro|__NR_SVR4_uadmin
mdefine_line|#define __NR_SVR4_uadmin&t;&t;(__NR_SVR4 +  55)
DECL|macro|__NR_SVR4_exch
mdefine_line|#define __NR_SVR4_exch &t;&t;&t;(__NR_SVR4 +  56)
DECL|macro|__NR_SVR4_utssys
mdefine_line|#define __NR_SVR4_utssys&t;&t;(__NR_SVR4 +  57)
DECL|macro|__NR_SVR4_fsync
mdefine_line|#define __NR_SVR4_fsync&t;&t;&t;(__NR_SVR4 +  58)
DECL|macro|__NR_SVR4_exece
mdefine_line|#define __NR_SVR4_exece&t;&t;&t;(__NR_SVR4 +  59)
DECL|macro|__NR_SVR4_umask
mdefine_line|#define __NR_SVR4_umask&t;&t;&t;(__NR_SVR4 +  60)
DECL|macro|__NR_SVR4_chroot
mdefine_line|#define __NR_SVR4_chroot&t;&t;(__NR_SVR4 +  61)
DECL|macro|__NR_SVR4_fcntl
mdefine_line|#define __NR_SVR4_fcntl&t;&t;&t;(__NR_SVR4 +  62)
DECL|macro|__NR_SVR4_ulimit
mdefine_line|#define __NR_SVR4_ulimit&t;&t;(__NR_SVR4 +  63)
DECL|macro|__NR_SVR4_reserved1
mdefine_line|#define __NR_SVR4_reserved1&t;&t;(__NR_SVR4 +  64)
DECL|macro|__NR_SVR4_reserved2
mdefine_line|#define __NR_SVR4_reserved2&t;&t;(__NR_SVR4 +  65)
DECL|macro|__NR_SVR4_reserved3
mdefine_line|#define __NR_SVR4_reserved3&t;&t;(__NR_SVR4 +  66)
DECL|macro|__NR_SVR4_reserved4
mdefine_line|#define __NR_SVR4_reserved4&t;&t;(__NR_SVR4 +  67)
DECL|macro|__NR_SVR4_reserved5
mdefine_line|#define __NR_SVR4_reserved5&t;&t;(__NR_SVR4 +  68)
DECL|macro|__NR_SVR4_reserved6
mdefine_line|#define __NR_SVR4_reserved6&t;&t;(__NR_SVR4 +  69)
DECL|macro|__NR_SVR4_advfs
mdefine_line|#define __NR_SVR4_advfs&t;&t;&t;(__NR_SVR4 +  70)
DECL|macro|__NR_SVR4_unadvfs
mdefine_line|#define __NR_SVR4_unadvfs&t;&t;(__NR_SVR4 +  71)
DECL|macro|__NR_SVR4_unused1
mdefine_line|#define __NR_SVR4_unused1&t;&t;(__NR_SVR4 +  72)
DECL|macro|__NR_SVR4_unused2
mdefine_line|#define __NR_SVR4_unused2&t;&t;(__NR_SVR4 +  73)
DECL|macro|__NR_SVR4_rfstart
mdefine_line|#define __NR_SVR4_rfstart&t;&t;(__NR_SVR4 +  74)
DECL|macro|__NR_SVR4_unused3
mdefine_line|#define __NR_SVR4_unused3&t;&t;(__NR_SVR4 +  75)
DECL|macro|__NR_SVR4_rdebug
mdefine_line|#define __NR_SVR4_rdebug&t;&t;(__NR_SVR4 +  76)
DECL|macro|__NR_SVR4_rfstop
mdefine_line|#define __NR_SVR4_rfstop&t;&t;(__NR_SVR4 +  77)
DECL|macro|__NR_SVR4_rfsys
mdefine_line|#define __NR_SVR4_rfsys&t;&t;&t;(__NR_SVR4 +  78)
DECL|macro|__NR_SVR4_rmdir
mdefine_line|#define __NR_SVR4_rmdir&t;&t;&t;(__NR_SVR4 +  79)
DECL|macro|__NR_SVR4_mkdir
mdefine_line|#define __NR_SVR4_mkdir&t;&t;&t;(__NR_SVR4 +  80)
DECL|macro|__NR_SVR4_getdents
mdefine_line|#define __NR_SVR4_getdents&t;&t;(__NR_SVR4 +  81)
DECL|macro|__NR_SVR4_libattach
mdefine_line|#define __NR_SVR4_libattach&t;&t;(__NR_SVR4 +  82)
DECL|macro|__NR_SVR4_libdetach
mdefine_line|#define __NR_SVR4_libdetach&t;&t;(__NR_SVR4 +  83)
DECL|macro|__NR_SVR4_sysfs
mdefine_line|#define __NR_SVR4_sysfs&t;&t;&t;(__NR_SVR4 +  84)
DECL|macro|__NR_SVR4_getmsg
mdefine_line|#define __NR_SVR4_getmsg&t;&t;(__NR_SVR4 +  85)
DECL|macro|__NR_SVR4_putmsg
mdefine_line|#define __NR_SVR4_putmsg&t;&t;(__NR_SVR4 +  86)
DECL|macro|__NR_SVR4_poll
mdefine_line|#define __NR_SVR4_poll&t;&t;&t;(__NR_SVR4 +  87)
DECL|macro|__NR_SVR4_lstat
mdefine_line|#define __NR_SVR4_lstat&t;&t;&t;(__NR_SVR4 +  88)
DECL|macro|__NR_SVR4_symlink
mdefine_line|#define __NR_SVR4_symlink&t;&t;(__NR_SVR4 +  89)
DECL|macro|__NR_SVR4_readlink
mdefine_line|#define __NR_SVR4_readlink&t;&t;(__NR_SVR4 +  90)
DECL|macro|__NR_SVR4_setgroups
mdefine_line|#define __NR_SVR4_setgroups&t;&t;(__NR_SVR4 +  91)
DECL|macro|__NR_SVR4_getgroups
mdefine_line|#define __NR_SVR4_getgroups&t;&t;(__NR_SVR4 +  92)
DECL|macro|__NR_SVR4_fchmod
mdefine_line|#define __NR_SVR4_fchmod&t;&t;(__NR_SVR4 +  93)
DECL|macro|__NR_SVR4_fchown
mdefine_line|#define __NR_SVR4_fchown&t;&t;(__NR_SVR4 +  94)
DECL|macro|__NR_SVR4_sigprocmask
mdefine_line|#define __NR_SVR4_sigprocmask&t;&t;(__NR_SVR4 +  95)
DECL|macro|__NR_SVR4_sigsuspend
mdefine_line|#define __NR_SVR4_sigsuspend&t;&t;(__NR_SVR4 +  96)
DECL|macro|__NR_SVR4_sigaltstack
mdefine_line|#define __NR_SVR4_sigaltstack&t;&t;(__NR_SVR4 +  97)
DECL|macro|__NR_SVR4_sigaction
mdefine_line|#define __NR_SVR4_sigaction&t;&t;(__NR_SVR4 +  98)
DECL|macro|__NR_SVR4_sigpending
mdefine_line|#define __NR_SVR4_sigpending&t;&t;(__NR_SVR4 +  99)
DECL|macro|__NR_SVR4_setcontext
mdefine_line|#define __NR_SVR4_setcontext&t;&t;(__NR_SVR4 + 100)
DECL|macro|__NR_SVR4_evsys
mdefine_line|#define __NR_SVR4_evsys&t;&t;&t;(__NR_SVR4 + 101)
DECL|macro|__NR_SVR4_evtrapret
mdefine_line|#define __NR_SVR4_evtrapret&t;&t;(__NR_SVR4 + 102)
DECL|macro|__NR_SVR4_statvfs
mdefine_line|#define __NR_SVR4_statvfs&t;&t;(__NR_SVR4 + 103)
DECL|macro|__NR_SVR4_fstatvfs
mdefine_line|#define __NR_SVR4_fstatvfs&t;&t;(__NR_SVR4 + 104)
DECL|macro|__NR_SVR4_reserved7
mdefine_line|#define __NR_SVR4_reserved7&t;&t;(__NR_SVR4 + 105)
DECL|macro|__NR_SVR4_nfssys
mdefine_line|#define __NR_SVR4_nfssys&t;&t;(__NR_SVR4 + 106)
DECL|macro|__NR_SVR4_waitid
mdefine_line|#define __NR_SVR4_waitid&t;&t;(__NR_SVR4 + 107)
DECL|macro|__NR_SVR4_sigsendset
mdefine_line|#define __NR_SVR4_sigsendset&t;&t;(__NR_SVR4 + 108)
DECL|macro|__NR_SVR4_hrtsys
mdefine_line|#define __NR_SVR4_hrtsys&t;&t;(__NR_SVR4 + 109)
DECL|macro|__NR_SVR4_acancel
mdefine_line|#define __NR_SVR4_acancel&t;&t;(__NR_SVR4 + 110)
DECL|macro|__NR_SVR4_async
mdefine_line|#define __NR_SVR4_async&t;&t;&t;(__NR_SVR4 + 111)
DECL|macro|__NR_SVR4_priocntlset
mdefine_line|#define __NR_SVR4_priocntlset&t;&t;(__NR_SVR4 + 112)
DECL|macro|__NR_SVR4_pathconf
mdefine_line|#define __NR_SVR4_pathconf&t;&t;(__NR_SVR4 + 113)
DECL|macro|__NR_SVR4_mincore
mdefine_line|#define __NR_SVR4_mincore&t;&t;(__NR_SVR4 + 114)
DECL|macro|__NR_SVR4_mmap
mdefine_line|#define __NR_SVR4_mmap&t;&t;&t;(__NR_SVR4 + 115)
DECL|macro|__NR_SVR4_mprotect
mdefine_line|#define __NR_SVR4_mprotect&t;&t;(__NR_SVR4 + 116)
DECL|macro|__NR_SVR4_munmap
mdefine_line|#define __NR_SVR4_munmap&t;&t;(__NR_SVR4 + 117)
DECL|macro|__NR_SVR4_fpathconf
mdefine_line|#define __NR_SVR4_fpathconf&t;&t;(__NR_SVR4 + 118)
DECL|macro|__NR_SVR4_vfork
mdefine_line|#define __NR_SVR4_vfork&t;&t;&t;(__NR_SVR4 + 119)
DECL|macro|__NR_SVR4_fchdir
mdefine_line|#define __NR_SVR4_fchdir&t;&t;(__NR_SVR4 + 120)
DECL|macro|__NR_SVR4_readv
mdefine_line|#define __NR_SVR4_readv&t;&t;&t;(__NR_SVR4 + 121)
DECL|macro|__NR_SVR4_writev
mdefine_line|#define __NR_SVR4_writev&t;&t;(__NR_SVR4 + 122)
DECL|macro|__NR_SVR4_xstat
mdefine_line|#define __NR_SVR4_xstat&t;&t;&t;(__NR_SVR4 + 123)
DECL|macro|__NR_SVR4_lxstat
mdefine_line|#define __NR_SVR4_lxstat&t;&t;(__NR_SVR4 + 124)
DECL|macro|__NR_SVR4_fxstat
mdefine_line|#define __NR_SVR4_fxstat&t;&t;(__NR_SVR4 + 125)
DECL|macro|__NR_SVR4_xmknod
mdefine_line|#define __NR_SVR4_xmknod&t;&t;(__NR_SVR4 + 126)
DECL|macro|__NR_SVR4_clocal
mdefine_line|#define __NR_SVR4_clocal&t;&t;(__NR_SVR4 + 127)
DECL|macro|__NR_SVR4_setrlimit
mdefine_line|#define __NR_SVR4_setrlimit&t;&t;(__NR_SVR4 + 128)
DECL|macro|__NR_SVR4_getrlimit
mdefine_line|#define __NR_SVR4_getrlimit&t;&t;(__NR_SVR4 + 129)
DECL|macro|__NR_SVR4_lchown
mdefine_line|#define __NR_SVR4_lchown&t;&t;(__NR_SVR4 + 130)
DECL|macro|__NR_SVR4_memcntl
mdefine_line|#define __NR_SVR4_memcntl&t;&t;(__NR_SVR4 + 131)
DECL|macro|__NR_SVR4_getpmsg
mdefine_line|#define __NR_SVR4_getpmsg&t;&t;(__NR_SVR4 + 132)
DECL|macro|__NR_SVR4_putpmsg
mdefine_line|#define __NR_SVR4_putpmsg&t;&t;(__NR_SVR4 + 133)
DECL|macro|__NR_SVR4_rename
mdefine_line|#define __NR_SVR4_rename&t;&t;(__NR_SVR4 + 134)
DECL|macro|__NR_SVR4_nuname
mdefine_line|#define __NR_SVR4_nuname&t;&t;(__NR_SVR4 + 135)
DECL|macro|__NR_SVR4_setegid
mdefine_line|#define __NR_SVR4_setegid&t;&t;(__NR_SVR4 + 136)
DECL|macro|__NR_SVR4_sysconf
mdefine_line|#define __NR_SVR4_sysconf&t;&t;(__NR_SVR4 + 137)
DECL|macro|__NR_SVR4_adjtime
mdefine_line|#define __NR_SVR4_adjtime&t;&t;(__NR_SVR4 + 138)
DECL|macro|__NR_SVR4_sysinfo
mdefine_line|#define __NR_SVR4_sysinfo&t;&t;(__NR_SVR4 + 139)
DECL|macro|__NR_SVR4_reserved8
mdefine_line|#define __NR_SVR4_reserved8&t;&t;(__NR_SVR4 + 140)
DECL|macro|__NR_SVR4_seteuid
mdefine_line|#define __NR_SVR4_seteuid&t;&t;(__NR_SVR4 + 141)
DECL|macro|__NR_SVR4_PYRAMID_statis
mdefine_line|#define __NR_SVR4_PYRAMID_statis&t;(__NR_SVR4 + 142)
DECL|macro|__NR_SVR4_PYRAMID_tuning
mdefine_line|#define __NR_SVR4_PYRAMID_tuning&t;(__NR_SVR4 + 143)
DECL|macro|__NR_SVR4_PYRAMID_forcerr
mdefine_line|#define __NR_SVR4_PYRAMID_forcerr&t;(__NR_SVR4 + 144)
DECL|macro|__NR_SVR4_PYRAMID_mpcntl
mdefine_line|#define __NR_SVR4_PYRAMID_mpcntl&t;(__NR_SVR4 + 145)
DECL|macro|__NR_SVR4_reserved9
mdefine_line|#define __NR_SVR4_reserved9&t;&t;(__NR_SVR4 + 146)
DECL|macro|__NR_SVR4_reserved10
mdefine_line|#define __NR_SVR4_reserved10&t;&t;(__NR_SVR4 + 147)
DECL|macro|__NR_SVR4_reserved11
mdefine_line|#define __NR_SVR4_reserved11&t;&t;(__NR_SVR4 + 148)
DECL|macro|__NR_SVR4_reserved12
mdefine_line|#define __NR_SVR4_reserved12&t;&t;(__NR_SVR4 + 149)
DECL|macro|__NR_SVR4_reserved13
mdefine_line|#define __NR_SVR4_reserved13&t;&t;(__NR_SVR4 + 150)
DECL|macro|__NR_SVR4_reserved14
mdefine_line|#define __NR_SVR4_reserved14&t;&t;(__NR_SVR4 + 151)
DECL|macro|__NR_SVR4_reserved15
mdefine_line|#define __NR_SVR4_reserved15&t;&t;(__NR_SVR4 + 152)
DECL|macro|__NR_SVR4_reserved16
mdefine_line|#define __NR_SVR4_reserved16&t;&t;(__NR_SVR4 + 153)
DECL|macro|__NR_SVR4_reserved17
mdefine_line|#define __NR_SVR4_reserved17&t;&t;(__NR_SVR4 + 154)
DECL|macro|__NR_SVR4_reserved18
mdefine_line|#define __NR_SVR4_reserved18&t;&t;(__NR_SVR4 + 155)
DECL|macro|__NR_SVR4_reserved19
mdefine_line|#define __NR_SVR4_reserved19&t;&t;(__NR_SVR4 + 156)
DECL|macro|__NR_SVR4_reserved20
mdefine_line|#define __NR_SVR4_reserved20&t;&t;(__NR_SVR4 + 157)
DECL|macro|__NR_SVR4_reserved21
mdefine_line|#define __NR_SVR4_reserved21&t;&t;(__NR_SVR4 + 158)
DECL|macro|__NR_SVR4_reserved22
mdefine_line|#define __NR_SVR4_reserved22&t;&t;(__NR_SVR4 + 159)
DECL|macro|__NR_SVR4_reserved23
mdefine_line|#define __NR_SVR4_reserved23&t;&t;(__NR_SVR4 + 160)
DECL|macro|__NR_SVR4_reserved24
mdefine_line|#define __NR_SVR4_reserved24&t;&t;(__NR_SVR4 + 161)
DECL|macro|__NR_SVR4_reserved25
mdefine_line|#define __NR_SVR4_reserved25&t;&t;(__NR_SVR4 + 162)
DECL|macro|__NR_SVR4_reserved26
mdefine_line|#define __NR_SVR4_reserved26&t;&t;(__NR_SVR4 + 163)
DECL|macro|__NR_SVR4_reserved27
mdefine_line|#define __NR_SVR4_reserved27&t;&t;(__NR_SVR4 + 164)
DECL|macro|__NR_SVR4_reserved28
mdefine_line|#define __NR_SVR4_reserved28&t;&t;(__NR_SVR4 + 165)
DECL|macro|__NR_SVR4_reserved29
mdefine_line|#define __NR_SVR4_reserved29&t;&t;(__NR_SVR4 + 166)
DECL|macro|__NR_SVR4_reserved30
mdefine_line|#define __NR_SVR4_reserved30&t;&t;(__NR_SVR4 + 167)
DECL|macro|__NR_SVR4_reserved31
mdefine_line|#define __NR_SVR4_reserved31&t;&t;(__NR_SVR4 + 168)
DECL|macro|__NR_SVR4_reserved32
mdefine_line|#define __NR_SVR4_reserved32&t;&t;(__NR_SVR4 + 169)
DECL|macro|__NR_SVR4_reserved33
mdefine_line|#define __NR_SVR4_reserved33&t;&t;(__NR_SVR4 + 170)
DECL|macro|__NR_SVR4_reserved34
mdefine_line|#define __NR_SVR4_reserved34&t;&t;(__NR_SVR4 + 171)
DECL|macro|__NR_SVR4_reserved35
mdefine_line|#define __NR_SVR4_reserved35&t;&t;(__NR_SVR4 + 172)
DECL|macro|__NR_SVR4_reserved36
mdefine_line|#define __NR_SVR4_reserved36&t;&t;(__NR_SVR4 + 173)
DECL|macro|__NR_SVR4_reserved37
mdefine_line|#define __NR_SVR4_reserved37&t;&t;(__NR_SVR4 + 174)
DECL|macro|__NR_SVR4_reserved38
mdefine_line|#define __NR_SVR4_reserved38&t;&t;(__NR_SVR4 + 175)
DECL|macro|__NR_SVR4_reserved39
mdefine_line|#define __NR_SVR4_reserved39&t;&t;(__NR_SVR4 + 176)
DECL|macro|__NR_SVR4_reserved40
mdefine_line|#define __NR_SVR4_reserved40&t;&t;(__NR_SVR4 + 177)
DECL|macro|__NR_SVR4_reserved41
mdefine_line|#define __NR_SVR4_reserved41&t;&t;(__NR_SVR4 + 178)
DECL|macro|__NR_SVR4_reserved42
mdefine_line|#define __NR_SVR4_reserved42&t;&t;(__NR_SVR4 + 179)
DECL|macro|__NR_SVR4_reserved43
mdefine_line|#define __NR_SVR4_reserved43&t;&t;(__NR_SVR4 + 180)
DECL|macro|__NR_SVR4_reserved44
mdefine_line|#define __NR_SVR4_reserved44&t;&t;(__NR_SVR4 + 181)
DECL|macro|__NR_SVR4_reserved45
mdefine_line|#define __NR_SVR4_reserved45&t;&t;(__NR_SVR4 + 182)
DECL|macro|__NR_SVR4_reserved46
mdefine_line|#define __NR_SVR4_reserved46&t;&t;(__NR_SVR4 + 183)
DECL|macro|__NR_SVR4_reserved47
mdefine_line|#define __NR_SVR4_reserved47&t;&t;(__NR_SVR4 + 184)
DECL|macro|__NR_SVR4_reserved48
mdefine_line|#define __NR_SVR4_reserved48&t;&t;(__NR_SVR4 + 185)
DECL|macro|__NR_SVR4_reserved49
mdefine_line|#define __NR_SVR4_reserved49&t;&t;(__NR_SVR4 + 186)
DECL|macro|__NR_SVR4_reserved50
mdefine_line|#define __NR_SVR4_reserved50&t;&t;(__NR_SVR4 + 187)
DECL|macro|__NR_SVR4_reserved51
mdefine_line|#define __NR_SVR4_reserved51&t;&t;(__NR_SVR4 + 188)
DECL|macro|__NR_SVR4_reserved52
mdefine_line|#define __NR_SVR4_reserved52&t;&t;(__NR_SVR4 + 189)
DECL|macro|__NR_SVR4_reserved53
mdefine_line|#define __NR_SVR4_reserved53&t;&t;(__NR_SVR4 + 190)
DECL|macro|__NR_SVR4_reserved54
mdefine_line|#define __NR_SVR4_reserved54&t;&t;(__NR_SVR4 + 191)
DECL|macro|__NR_SVR4_reserved55
mdefine_line|#define __NR_SVR4_reserved55&t;&t;(__NR_SVR4 + 192)
DECL|macro|__NR_SVR4_reserved56
mdefine_line|#define __NR_SVR4_reserved56&t;&t;(__NR_SVR4 + 193)
DECL|macro|__NR_SVR4_reserved57
mdefine_line|#define __NR_SVR4_reserved57&t;&t;(__NR_SVR4 + 194)
DECL|macro|__NR_SVR4_reserved58
mdefine_line|#define __NR_SVR4_reserved58&t;&t;(__NR_SVR4 + 195)
DECL|macro|__NR_SVR4_reserved59
mdefine_line|#define __NR_SVR4_reserved59&t;&t;(__NR_SVR4 + 196)
DECL|macro|__NR_SVR4_reserved60
mdefine_line|#define __NR_SVR4_reserved60&t;&t;(__NR_SVR4 + 197)
DECL|macro|__NR_SVR4_reserved61
mdefine_line|#define __NR_SVR4_reserved61&t;&t;(__NR_SVR4 + 198)
DECL|macro|__NR_SVR4_reserved62
mdefine_line|#define __NR_SVR4_reserved62&t;&t;(__NR_SVR4 + 199)
DECL|macro|__NR_SVR4_reserved63
mdefine_line|#define __NR_SVR4_reserved63&t;&t;(__NR_SVR4 + 200)
DECL|macro|__NR_SVR4_aread
mdefine_line|#define __NR_SVR4_aread&t;&t;&t;(__NR_SVR4 + 201)
DECL|macro|__NR_SVR4_awrite
mdefine_line|#define __NR_SVR4_awrite&t;&t;(__NR_SVR4 + 202)&t;
DECL|macro|__NR_SVR4_listio
mdefine_line|#define __NR_SVR4_listio&t;&t;(__NR_SVR4 + 203)
DECL|macro|__NR_SVR4_mips_acancel
mdefine_line|#define __NR_SVR4_mips_acancel&t;&t;(__NR_SVR4 + 204)
DECL|macro|__NR_SVR4_astatus
mdefine_line|#define __NR_SVR4_astatus&t;&t;(__NR_SVR4 + 205)
DECL|macro|__NR_SVR4_await
mdefine_line|#define __NR_SVR4_await&t;&t;&t;(__NR_SVR4 + 206)
DECL|macro|__NR_SVR4_areadv
mdefine_line|#define __NR_SVR4_areadv&t;&t;(__NR_SVR4 + 207)
DECL|macro|__NR_SVR4_awritev
mdefine_line|#define __NR_SVR4_awritev&t;&t;(__NR_SVR4 + 208)
DECL|macro|__NR_SVR4_MIPS_reserved1
mdefine_line|#define __NR_SVR4_MIPS_reserved1&t;(__NR_SVR4 + 209)
DECL|macro|__NR_SVR4_MIPS_reserved2
mdefine_line|#define __NR_SVR4_MIPS_reserved2&t;(__NR_SVR4 + 210)
DECL|macro|__NR_SVR4_MIPS_reserved3
mdefine_line|#define __NR_SVR4_MIPS_reserved3&t;(__NR_SVR4 + 211)
DECL|macro|__NR_SVR4_MIPS_reserved4
mdefine_line|#define __NR_SVR4_MIPS_reserved4&t;(__NR_SVR4 + 212)
DECL|macro|__NR_SVR4_MIPS_reserved5
mdefine_line|#define __NR_SVR4_MIPS_reserved5&t;(__NR_SVR4 + 213)
DECL|macro|__NR_SVR4_MIPS_reserved6
mdefine_line|#define __NR_SVR4_MIPS_reserved6&t;(__NR_SVR4 + 214)
DECL|macro|__NR_SVR4_MIPS_reserved7
mdefine_line|#define __NR_SVR4_MIPS_reserved7&t;(__NR_SVR4 + 215)
DECL|macro|__NR_SVR4_MIPS_reserved8
mdefine_line|#define __NR_SVR4_MIPS_reserved8&t;(__NR_SVR4 + 216)
DECL|macro|__NR_SVR4_MIPS_reserved9
mdefine_line|#define __NR_SVR4_MIPS_reserved9&t;(__NR_SVR4 + 217)
DECL|macro|__NR_SVR4_MIPS_reserved10
mdefine_line|#define __NR_SVR4_MIPS_reserved10&t;(__NR_SVR4 + 218)
DECL|macro|__NR_SVR4_MIPS_reserved11
mdefine_line|#define __NR_SVR4_MIPS_reserved11&t;(__NR_SVR4 + 219)
DECL|macro|__NR_SVR4_MIPS_reserved12
mdefine_line|#define __NR_SVR4_MIPS_reserved12&t;(__NR_SVR4 + 220)
DECL|macro|__NR_SVR4_CDC_reserved1
mdefine_line|#define __NR_SVR4_CDC_reserved1&t;&t;(__NR_SVR4 + 221)
DECL|macro|__NR_SVR4_CDC_reserved2
mdefine_line|#define __NR_SVR4_CDC_reserved2&t;&t;(__NR_SVR4 + 222)
DECL|macro|__NR_SVR4_CDC_reserved3
mdefine_line|#define __NR_SVR4_CDC_reserved3&t;&t;(__NR_SVR4 + 223)
DECL|macro|__NR_SVR4_CDC_reserved4
mdefine_line|#define __NR_SVR4_CDC_reserved4&t;&t;(__NR_SVR4 + 224)
DECL|macro|__NR_SVR4_CDC_reserved5
mdefine_line|#define __NR_SVR4_CDC_reserved5&t;&t;(__NR_SVR4 + 225)
DECL|macro|__NR_SVR4_CDC_reserved6
mdefine_line|#define __NR_SVR4_CDC_reserved6&t;&t;(__NR_SVR4 + 226)
DECL|macro|__NR_SVR4_CDC_reserved7
mdefine_line|#define __NR_SVR4_CDC_reserved7&t;&t;(__NR_SVR4 + 227)
DECL|macro|__NR_SVR4_CDC_reserved8
mdefine_line|#define __NR_SVR4_CDC_reserved8&t;&t;(__NR_SVR4 + 228)
DECL|macro|__NR_SVR4_CDC_reserved9
mdefine_line|#define __NR_SVR4_CDC_reserved9&t;&t;(__NR_SVR4 + 229)
DECL|macro|__NR_SVR4_CDC_reserved10
mdefine_line|#define __NR_SVR4_CDC_reserved10&t;(__NR_SVR4 + 230)
DECL|macro|__NR_SVR4_CDC_reserved11
mdefine_line|#define __NR_SVR4_CDC_reserved11&t;(__NR_SVR4 + 231)
DECL|macro|__NR_SVR4_CDC_reserved12
mdefine_line|#define __NR_SVR4_CDC_reserved12&t;(__NR_SVR4 + 232)
DECL|macro|__NR_SVR4_CDC_reserved13
mdefine_line|#define __NR_SVR4_CDC_reserved13&t;(__NR_SVR4 + 233)
DECL|macro|__NR_SVR4_CDC_reserved14
mdefine_line|#define __NR_SVR4_CDC_reserved14&t;(__NR_SVR4 + 234)
DECL|macro|__NR_SVR4_CDC_reserved15
mdefine_line|#define __NR_SVR4_CDC_reserved15&t;(__NR_SVR4 + 235)
DECL|macro|__NR_SVR4_CDC_reserved16
mdefine_line|#define __NR_SVR4_CDC_reserved16&t;(__NR_SVR4 + 236)
DECL|macro|__NR_SVR4_CDC_reserved17
mdefine_line|#define __NR_SVR4_CDC_reserved17&t;(__NR_SVR4 + 237)
DECL|macro|__NR_SVR4_CDC_reserved18
mdefine_line|#define __NR_SVR4_CDC_reserved18&t;(__NR_SVR4 + 238)
DECL|macro|__NR_SVR4_CDC_reserved19
mdefine_line|#define __NR_SVR4_CDC_reserved19&t;(__NR_SVR4 + 239)
DECL|macro|__NR_SVR4_CDC_reserved20
mdefine_line|#define __NR_SVR4_CDC_reserved20&t;(__NR_SVR4 + 240)
multiline_comment|/*&n; * SYS V syscalls are in the range from 1000 to 1999&n; */
DECL|macro|__NR_SYSV
mdefine_line|#define __NR_SYSV&t;&t;&t;1000
DECL|macro|__NR_SYSV_syscall
mdefine_line|#define __NR_SYSV_syscall&t;&t;(__NR_SYSV +   0)
DECL|macro|__NR_SYSV_exit
mdefine_line|#define __NR_SYSV_exit&t;&t;&t;(__NR_SYSV +   1)
DECL|macro|__NR_SYSV_fork
mdefine_line|#define __NR_SYSV_fork&t;&t;&t;(__NR_SYSV +   2)
DECL|macro|__NR_SYSV_read
mdefine_line|#define __NR_SYSV_read&t;&t;&t;(__NR_SYSV +   3)
DECL|macro|__NR_SYSV_write
mdefine_line|#define __NR_SYSV_write&t;&t;&t;(__NR_SYSV +   4)
DECL|macro|__NR_SYSV_open
mdefine_line|#define __NR_SYSV_open&t;&t;&t;(__NR_SYSV +   5)
DECL|macro|__NR_SYSV_close
mdefine_line|#define __NR_SYSV_close&t;&t;&t;(__NR_SYSV +   6)
DECL|macro|__NR_SYSV_wait
mdefine_line|#define __NR_SYSV_wait&t;&t;&t;(__NR_SYSV +   7)
DECL|macro|__NR_SYSV_creat
mdefine_line|#define __NR_SYSV_creat&t;&t;&t;(__NR_SYSV +   8)
DECL|macro|__NR_SYSV_link
mdefine_line|#define __NR_SYSV_link&t;&t;&t;(__NR_SYSV +   9)
DECL|macro|__NR_SYSV_unlink
mdefine_line|#define __NR_SYSV_unlink&t;&t;(__NR_SYSV +  10)
DECL|macro|__NR_SYSV_execv
mdefine_line|#define __NR_SYSV_execv&t;&t;&t;(__NR_SYSV +  11)
DECL|macro|__NR_SYSV_chdir
mdefine_line|#define __NR_SYSV_chdir&t;&t;&t;(__NR_SYSV +  12)
DECL|macro|__NR_SYSV_time
mdefine_line|#define __NR_SYSV_time&t;&t;&t;(__NR_SYSV +  13)
DECL|macro|__NR_SYSV_mknod
mdefine_line|#define __NR_SYSV_mknod&t;&t;&t;(__NR_SYSV +  14)
DECL|macro|__NR_SYSV_chmod
mdefine_line|#define __NR_SYSV_chmod&t;&t;&t;(__NR_SYSV +  15)
DECL|macro|__NR_SYSV_chown
mdefine_line|#define __NR_SYSV_chown&t;&t;&t;(__NR_SYSV +  16)
DECL|macro|__NR_SYSV_brk
mdefine_line|#define __NR_SYSV_brk&t;&t;&t;(__NR_SYSV +  17)
DECL|macro|__NR_SYSV_stat
mdefine_line|#define __NR_SYSV_stat&t;&t;&t;(__NR_SYSV +  18)
DECL|macro|__NR_SYSV_lseek
mdefine_line|#define __NR_SYSV_lseek&t;&t;&t;(__NR_SYSV +  19)
DECL|macro|__NR_SYSV_getpid
mdefine_line|#define __NR_SYSV_getpid&t;&t;(__NR_SYSV +  20)
DECL|macro|__NR_SYSV_mount
mdefine_line|#define __NR_SYSV_mount&t;&t;&t;(__NR_SYSV +  21)
DECL|macro|__NR_SYSV_umount
mdefine_line|#define __NR_SYSV_umount&t;&t;(__NR_SYSV +  22)
DECL|macro|__NR_SYSV_setuid
mdefine_line|#define __NR_SYSV_setuid&t;&t;(__NR_SYSV +  23)
DECL|macro|__NR_SYSV_getuid
mdefine_line|#define __NR_SYSV_getuid&t;&t;(__NR_SYSV +  24)
DECL|macro|__NR_SYSV_stime
mdefine_line|#define __NR_SYSV_stime&t;&t;&t;(__NR_SYSV +  25)
DECL|macro|__NR_SYSV_ptrace
mdefine_line|#define __NR_SYSV_ptrace&t;&t;(__NR_SYSV +  26)
DECL|macro|__NR_SYSV_alarm
mdefine_line|#define __NR_SYSV_alarm&t;&t;&t;(__NR_SYSV +  27)
DECL|macro|__NR_SYSV_fstat
mdefine_line|#define __NR_SYSV_fstat&t;&t;&t;(__NR_SYSV +  28)
DECL|macro|__NR_SYSV_pause
mdefine_line|#define __NR_SYSV_pause&t;&t;&t;(__NR_SYSV +  29)
DECL|macro|__NR_SYSV_utime
mdefine_line|#define __NR_SYSV_utime&t;&t;&t;(__NR_SYSV +  30)
DECL|macro|__NR_SYSV_stty
mdefine_line|#define __NR_SYSV_stty&t;&t;&t;(__NR_SYSV +  31)
DECL|macro|__NR_SYSV_gtty
mdefine_line|#define __NR_SYSV_gtty&t;&t;&t;(__NR_SYSV +  32)
DECL|macro|__NR_SYSV_access
mdefine_line|#define __NR_SYSV_access&t;&t;(__NR_SYSV +  33)
DECL|macro|__NR_SYSV_nice
mdefine_line|#define __NR_SYSV_nice&t;&t;&t;(__NR_SYSV +  34)
DECL|macro|__NR_SYSV_statfs
mdefine_line|#define __NR_SYSV_statfs&t;&t;(__NR_SYSV +  35)
DECL|macro|__NR_SYSV_sync
mdefine_line|#define __NR_SYSV_sync&t;&t;&t;(__NR_SYSV +  36)
DECL|macro|__NR_SYSV_kill
mdefine_line|#define __NR_SYSV_kill&t;&t;&t;(__NR_SYSV +  37)
DECL|macro|__NR_SYSV_fstatfs
mdefine_line|#define __NR_SYSV_fstatfs&t;&t;(__NR_SYSV +  38)
DECL|macro|__NR_SYSV_setpgrp
mdefine_line|#define __NR_SYSV_setpgrp&t;&t;(__NR_SYSV +  39)
DECL|macro|__NR_SYSV_syssgi
mdefine_line|#define __NR_SYSV_syssgi&t;&t;(__NR_SYSV +  40)
DECL|macro|__NR_SYSV_dup
mdefine_line|#define __NR_SYSV_dup&t;&t;&t;(__NR_SYSV +  41)
DECL|macro|__NR_SYSV_pipe
mdefine_line|#define __NR_SYSV_pipe&t;&t;&t;(__NR_SYSV +  42)
DECL|macro|__NR_SYSV_times
mdefine_line|#define __NR_SYSV_times&t;&t;&t;(__NR_SYSV +  43)
DECL|macro|__NR_SYSV_profil
mdefine_line|#define __NR_SYSV_profil&t;&t;(__NR_SYSV +  44)
DECL|macro|__NR_SYSV_plock
mdefine_line|#define __NR_SYSV_plock&t;&t;&t;(__NR_SYSV +  45)
DECL|macro|__NR_SYSV_setgid
mdefine_line|#define __NR_SYSV_setgid&t;&t;(__NR_SYSV +  46)
DECL|macro|__NR_SYSV_getgid
mdefine_line|#define __NR_SYSV_getgid&t;&t;(__NR_SYSV +  47)
DECL|macro|__NR_SYSV_sig
mdefine_line|#define __NR_SYSV_sig&t;&t;&t;(__NR_SYSV +  48)
DECL|macro|__NR_SYSV_msgsys
mdefine_line|#define __NR_SYSV_msgsys&t;&t;(__NR_SYSV +  49)
DECL|macro|__NR_SYSV_sysmips
mdefine_line|#define __NR_SYSV_sysmips&t;&t;(__NR_SYSV +  50)
DECL|macro|__NR_SYSV_acct
mdefine_line|#define __NR_SYSV_acct&t;&t;&t;(__NR_SYSV +  51)
DECL|macro|__NR_SYSV_shmsys
mdefine_line|#define __NR_SYSV_shmsys&t;&t;(__NR_SYSV +  52)
DECL|macro|__NR_SYSV_semsys
mdefine_line|#define __NR_SYSV_semsys&t;&t;(__NR_SYSV +  53)
DECL|macro|__NR_SYSV_ioctl
mdefine_line|#define __NR_SYSV_ioctl&t;&t;&t;(__NR_SYSV +  54)
DECL|macro|__NR_SYSV_uadmin
mdefine_line|#define __NR_SYSV_uadmin&t;&t;(__NR_SYSV +  55)
DECL|macro|__NR_SYSV_sysmp
mdefine_line|#define __NR_SYSV_sysmp&t;&t;&t;(__NR_SYSV +  56)
DECL|macro|__NR_SYSV_utssys
mdefine_line|#define __NR_SYSV_utssys&t;&t;(__NR_SYSV +  57)
DECL|macro|__NR_SYSV_USG_reserved1
mdefine_line|#define __NR_SYSV_USG_reserved1&t;&t;(__NR_SYSV +  58)
DECL|macro|__NR_SYSV_execve
mdefine_line|#define __NR_SYSV_execve&t;&t;(__NR_SYSV +  59)
DECL|macro|__NR_SYSV_umask
mdefine_line|#define __NR_SYSV_umask&t;&t;&t;(__NR_SYSV +  60)
DECL|macro|__NR_SYSV_chroot
mdefine_line|#define __NR_SYSV_chroot&t;&t;(__NR_SYSV +  61)
DECL|macro|__NR_SYSV_fcntl
mdefine_line|#define __NR_SYSV_fcntl&t;&t;&t;(__NR_SYSV +  62)
DECL|macro|__NR_SYSV_ulimit
mdefine_line|#define __NR_SYSV_ulimit&t;&t;(__NR_SYSV +  63)
DECL|macro|__NR_SYSV_SAFARI4_reserved1
mdefine_line|#define __NR_SYSV_SAFARI4_reserved1&t;(__NR_SYSV +  64)
DECL|macro|__NR_SYSV_SAFARI4_reserved2
mdefine_line|#define __NR_SYSV_SAFARI4_reserved2&t;(__NR_SYSV +  65)
DECL|macro|__NR_SYSV_SAFARI4_reserved3
mdefine_line|#define __NR_SYSV_SAFARI4_reserved3&t;(__NR_SYSV +  66)
DECL|macro|__NR_SYSV_SAFARI4_reserved4
mdefine_line|#define __NR_SYSV_SAFARI4_reserved4&t;(__NR_SYSV +  67)
DECL|macro|__NR_SYSV_SAFARI4_reserved5
mdefine_line|#define __NR_SYSV_SAFARI4_reserved5&t;(__NR_SYSV +  68)
DECL|macro|__NR_SYSV_SAFARI4_reserved6
mdefine_line|#define __NR_SYSV_SAFARI4_reserved6&t;(__NR_SYSV +  69)
DECL|macro|__NR_SYSV_advfs
mdefine_line|#define __NR_SYSV_advfs&t;&t;&t;(__NR_SYSV +  70)
DECL|macro|__NR_SYSV_unadvfs
mdefine_line|#define __NR_SYSV_unadvfs&t;&t;(__NR_SYSV +  71)
DECL|macro|__NR_SYSV_rmount
mdefine_line|#define __NR_SYSV_rmount&t;&t;(__NR_SYSV +  72)
DECL|macro|__NR_SYSV_rumount
mdefine_line|#define __NR_SYSV_rumount&t;&t;(__NR_SYSV +  73)
DECL|macro|__NR_SYSV_rfstart
mdefine_line|#define __NR_SYSV_rfstart&t;&t;(__NR_SYSV +  74)
DECL|macro|__NR_SYSV_getrlimit64
mdefine_line|#define __NR_SYSV_getrlimit64&t;&t;(__NR_SYSV +  75)
DECL|macro|__NR_SYSV_setrlimit64
mdefine_line|#define __NR_SYSV_setrlimit64&t;&t;(__NR_SYSV +  76)
DECL|macro|__NR_SYSV_nanosleep
mdefine_line|#define __NR_SYSV_nanosleep&t;&t;(__NR_SYSV +  77)
DECL|macro|__NR_SYSV_lseek64
mdefine_line|#define __NR_SYSV_lseek64&t;&t;(__NR_SYSV +  78)
DECL|macro|__NR_SYSV_rmdir
mdefine_line|#define __NR_SYSV_rmdir&t;&t;&t;(__NR_SYSV +  79)
DECL|macro|__NR_SYSV_mkdir
mdefine_line|#define __NR_SYSV_mkdir&t;&t;&t;(__NR_SYSV +  80)
DECL|macro|__NR_SYSV_getdents
mdefine_line|#define __NR_SYSV_getdents&t;&t;(__NR_SYSV +  81)
DECL|macro|__NR_SYSV_sginap
mdefine_line|#define __NR_SYSV_sginap&t;&t;(__NR_SYSV +  82)
DECL|macro|__NR_SYSV_sgikopt
mdefine_line|#define __NR_SYSV_sgikopt&t;&t;(__NR_SYSV +  83)
DECL|macro|__NR_SYSV_sysfs
mdefine_line|#define __NR_SYSV_sysfs&t;&t;&t;(__NR_SYSV +  84)
DECL|macro|__NR_SYSV_getmsg
mdefine_line|#define __NR_SYSV_getmsg&t;&t;(__NR_SYSV +  85)
DECL|macro|__NR_SYSV_putmsg
mdefine_line|#define __NR_SYSV_putmsg&t;&t;(__NR_SYSV +  86)
DECL|macro|__NR_SYSV_poll
mdefine_line|#define __NR_SYSV_poll&t;&t;&t;(__NR_SYSV +  87)
DECL|macro|__NR_SYSV_sigreturn
mdefine_line|#define __NR_SYSV_sigreturn&t;&t;(__NR_SYSV +  88)
DECL|macro|__NR_SYSV_accept
mdefine_line|#define __NR_SYSV_accept&t;&t;(__NR_SYSV +  89)
DECL|macro|__NR_SYSV_bind
mdefine_line|#define __NR_SYSV_bind&t;&t;&t;(__NR_SYSV +  90)
DECL|macro|__NR_SYSV_connect
mdefine_line|#define __NR_SYSV_connect&t;&t;(__NR_SYSV +  91)
DECL|macro|__NR_SYSV_gethostid
mdefine_line|#define __NR_SYSV_gethostid&t;&t;(__NR_SYSV +  92)
DECL|macro|__NR_SYSV_getpeername
mdefine_line|#define __NR_SYSV_getpeername&t;&t;(__NR_SYSV +  93)
DECL|macro|__NR_SYSV_getsockname
mdefine_line|#define __NR_SYSV_getsockname&t;&t;(__NR_SYSV +  94)
DECL|macro|__NR_SYSV_getsockopt
mdefine_line|#define __NR_SYSV_getsockopt&t;&t;(__NR_SYSV +  95)
DECL|macro|__NR_SYSV_listen
mdefine_line|#define __NR_SYSV_listen&t;&t;(__NR_SYSV +  96)
DECL|macro|__NR_SYSV_recv
mdefine_line|#define __NR_SYSV_recv&t;&t;&t;(__NR_SYSV +  97)
DECL|macro|__NR_SYSV_recvfrom
mdefine_line|#define __NR_SYSV_recvfrom&t;&t;(__NR_SYSV +  98)
DECL|macro|__NR_SYSV_recvmsg
mdefine_line|#define __NR_SYSV_recvmsg&t;&t;(__NR_SYSV +  99)
DECL|macro|__NR_SYSV_select
mdefine_line|#define __NR_SYSV_select&t;&t;(__NR_SYSV + 100)
DECL|macro|__NR_SYSV_send
mdefine_line|#define __NR_SYSV_send&t;&t;&t;(__NR_SYSV + 101)
DECL|macro|__NR_SYSV_sendmsg
mdefine_line|#define __NR_SYSV_sendmsg&t;&t;(__NR_SYSV + 102)
DECL|macro|__NR_SYSV_sendto
mdefine_line|#define __NR_SYSV_sendto&t;&t;(__NR_SYSV + 103)
DECL|macro|__NR_SYSV_sethostid
mdefine_line|#define __NR_SYSV_sethostid&t;&t;(__NR_SYSV + 104)
DECL|macro|__NR_SYSV_setsockopt
mdefine_line|#define __NR_SYSV_setsockopt&t;&t;(__NR_SYSV + 105)
DECL|macro|__NR_SYSV_shutdown
mdefine_line|#define __NR_SYSV_shutdown&t;&t;(__NR_SYSV + 106)
DECL|macro|__NR_SYSV_socket
mdefine_line|#define __NR_SYSV_socket&t;&t;(__NR_SYSV + 107)
DECL|macro|__NR_SYSV_gethostname
mdefine_line|#define __NR_SYSV_gethostname&t;&t;(__NR_SYSV + 108)
DECL|macro|__NR_SYSV_sethostname
mdefine_line|#define __NR_SYSV_sethostname&t;&t;(__NR_SYSV + 109)
DECL|macro|__NR_SYSV_getdomainname
mdefine_line|#define __NR_SYSV_getdomainname&t;&t;(__NR_SYSV + 110)
DECL|macro|__NR_SYSV_setdomainname
mdefine_line|#define __NR_SYSV_setdomainname&t;&t;(__NR_SYSV + 111)
DECL|macro|__NR_SYSV_truncate
mdefine_line|#define __NR_SYSV_truncate&t;&t;(__NR_SYSV + 112)
DECL|macro|__NR_SYSV_ftruncate
mdefine_line|#define __NR_SYSV_ftruncate&t;&t;(__NR_SYSV + 113)
DECL|macro|__NR_SYSV_rename
mdefine_line|#define __NR_SYSV_rename&t;&t;(__NR_SYSV + 114)
DECL|macro|__NR_SYSV_symlink
mdefine_line|#define __NR_SYSV_symlink&t;&t;(__NR_SYSV + 115)
DECL|macro|__NR_SYSV_readlink
mdefine_line|#define __NR_SYSV_readlink&t;&t;(__NR_SYSV + 116)
DECL|macro|__NR_SYSV_lstat
mdefine_line|#define __NR_SYSV_lstat&t;&t;&t;(__NR_SYSV + 117)
DECL|macro|__NR_SYSV_nfsmount
mdefine_line|#define __NR_SYSV_nfsmount&t;&t;(__NR_SYSV + 118)
DECL|macro|__NR_SYSV_nfssvc
mdefine_line|#define __NR_SYSV_nfssvc&t;&t;(__NR_SYSV + 119)
DECL|macro|__NR_SYSV_getfh
mdefine_line|#define __NR_SYSV_getfh&t;&t;&t;(__NR_SYSV + 120)
DECL|macro|__NR_SYSV_async_daemon
mdefine_line|#define __NR_SYSV_async_daemon&t;&t;(__NR_SYSV + 121)
DECL|macro|__NR_SYSV_exportfs
mdefine_line|#define __NR_SYSV_exportfs&t;&t;(__NR_SYSV + 122)
DECL|macro|__NR_SYSV_setregid
mdefine_line|#define __NR_SYSV_setregid&t;&t;(__NR_SYSV + 123)
DECL|macro|__NR_SYSV_setreuid
mdefine_line|#define __NR_SYSV_setreuid&t;&t;(__NR_SYSV + 124)
DECL|macro|__NR_SYSV_getitimer
mdefine_line|#define __NR_SYSV_getitimer&t;&t;(__NR_SYSV + 125)
DECL|macro|__NR_SYSV_setitimer
mdefine_line|#define __NR_SYSV_setitimer&t;&t;(__NR_SYSV + 126)
DECL|macro|__NR_SYSV_adjtime
mdefine_line|#define __NR_SYSV_adjtime&t;&t;(__NR_SYSV + 127)
DECL|macro|__NR_SYSV_BSD_getime
mdefine_line|#define __NR_SYSV_BSD_getime&t;&t;(__NR_SYSV + 128)
DECL|macro|__NR_SYSV_sproc
mdefine_line|#define __NR_SYSV_sproc&t;&t;&t;(__NR_SYSV + 129)
DECL|macro|__NR_SYSV_prctl
mdefine_line|#define __NR_SYSV_prctl&t;&t;&t;(__NR_SYSV + 130)
DECL|macro|__NR_SYSV_procblk
mdefine_line|#define __NR_SYSV_procblk&t;&t;(__NR_SYSV + 131)
DECL|macro|__NR_SYSV_sprocsp
mdefine_line|#define __NR_SYSV_sprocsp&t;&t;(__NR_SYSV + 132)
DECL|macro|__NR_SYSV_sgigsc
mdefine_line|#define __NR_SYSV_sgigsc&t;&t;(__NR_SYSV + 133)
DECL|macro|__NR_SYSV_mmap
mdefine_line|#define __NR_SYSV_mmap&t;&t;&t;(__NR_SYSV + 134)
DECL|macro|__NR_SYSV_munmap
mdefine_line|#define __NR_SYSV_munmap&t;&t;(__NR_SYSV + 135)
DECL|macro|__NR_SYSV_mprotect
mdefine_line|#define __NR_SYSV_mprotect&t;&t;(__NR_SYSV + 136)
DECL|macro|__NR_SYSV_msync
mdefine_line|#define __NR_SYSV_msync&t;&t;&t;(__NR_SYSV + 137)
DECL|macro|__NR_SYSV_madvise
mdefine_line|#define __NR_SYSV_madvise&t;&t;(__NR_SYSV + 138)
DECL|macro|__NR_SYSV_pagelock
mdefine_line|#define __NR_SYSV_pagelock&t;&t;(__NR_SYSV + 139)
DECL|macro|__NR_SYSV_getpagesize
mdefine_line|#define __NR_SYSV_getpagesize&t;&t;(__NR_SYSV + 140)
DECL|macro|__NR_SYSV_quotactl
mdefine_line|#define __NR_SYSV_quotactl&t;&t;(__NR_SYSV + 141)
DECL|macro|__NR_SYSV_libdetach
mdefine_line|#define __NR_SYSV_libdetach&t;&t;(__NR_SYSV + 142)
DECL|macro|__NR_SYSV_BSDgetpgrp
mdefine_line|#define __NR_SYSV_BSDgetpgrp&t;&t;(__NR_SYSV + 143)
DECL|macro|__NR_SYSV_BSDsetpgrp
mdefine_line|#define __NR_SYSV_BSDsetpgrp&t;&t;(__NR_SYSV + 144)
DECL|macro|__NR_SYSV_vhangup
mdefine_line|#define __NR_SYSV_vhangup&t;&t;(__NR_SYSV + 145)
DECL|macro|__NR_SYSV_fsync
mdefine_line|#define __NR_SYSV_fsync&t;&t;&t;(__NR_SYSV + 146)
DECL|macro|__NR_SYSV_fchdir
mdefine_line|#define __NR_SYSV_fchdir&t;&t;(__NR_SYSV + 147)
DECL|macro|__NR_SYSV_getrlimit
mdefine_line|#define __NR_SYSV_getrlimit&t;&t;(__NR_SYSV + 148)
DECL|macro|__NR_SYSV_setrlimit
mdefine_line|#define __NR_SYSV_setrlimit&t;&t;(__NR_SYSV + 149)
DECL|macro|__NR_SYSV_cacheflush
mdefine_line|#define __NR_SYSV_cacheflush&t;&t;(__NR_SYSV + 150)
DECL|macro|__NR_SYSV_cachectl
mdefine_line|#define __NR_SYSV_cachectl&t;&t;(__NR_SYSV + 151)
DECL|macro|__NR_SYSV_fchown
mdefine_line|#define __NR_SYSV_fchown&t;&t;(__NR_SYSV + 152)
DECL|macro|__NR_SYSV_fchmod
mdefine_line|#define __NR_SYSV_fchmod&t;&t;(__NR_SYSV + 153)
DECL|macro|__NR_SYSV_wait3
mdefine_line|#define __NR_SYSV_wait3&t;&t;&t;(__NR_SYSV + 154)
DECL|macro|__NR_SYSV_socketpair
mdefine_line|#define __NR_SYSV_socketpair&t;&t;(__NR_SYSV + 155)
DECL|macro|__NR_SYSV_sysinfo
mdefine_line|#define __NR_SYSV_sysinfo&t;&t;(__NR_SYSV + 156)
DECL|macro|__NR_SYSV_nuname
mdefine_line|#define __NR_SYSV_nuname&t;&t;(__NR_SYSV + 157)
DECL|macro|__NR_SYSV_xstat
mdefine_line|#define __NR_SYSV_xstat&t;&t;&t;(__NR_SYSV + 158)
DECL|macro|__NR_SYSV_lxstat
mdefine_line|#define __NR_SYSV_lxstat&t;&t;(__NR_SYSV + 159)
DECL|macro|__NR_SYSV_fxstat
mdefine_line|#define __NR_SYSV_fxstat&t;&t;(__NR_SYSV + 160)
DECL|macro|__NR_SYSV_xmknod
mdefine_line|#define __NR_SYSV_xmknod&t;&t;(__NR_SYSV + 161)
DECL|macro|__NR_SYSV_ksigaction
mdefine_line|#define __NR_SYSV_ksigaction&t;&t;(__NR_SYSV + 162)
DECL|macro|__NR_SYSV_sigpending
mdefine_line|#define __NR_SYSV_sigpending&t;&t;(__NR_SYSV + 163)
DECL|macro|__NR_SYSV_sigprocmask
mdefine_line|#define __NR_SYSV_sigprocmask&t;&t;(__NR_SYSV + 164)
DECL|macro|__NR_SYSV_sigsuspend
mdefine_line|#define __NR_SYSV_sigsuspend&t;&t;(__NR_SYSV + 165)
DECL|macro|__NR_SYSV_sigpoll
mdefine_line|#define __NR_SYSV_sigpoll&t;&t;(__NR_SYSV + 166)
DECL|macro|__NR_SYSV_swapctl
mdefine_line|#define __NR_SYSV_swapctl&t;&t;(__NR_SYSV + 167)
DECL|macro|__NR_SYSV_getcontext
mdefine_line|#define __NR_SYSV_getcontext&t;&t;(__NR_SYSV + 168)
DECL|macro|__NR_SYSV_setcontext
mdefine_line|#define __NR_SYSV_setcontext&t;&t;(__NR_SYSV + 169)
DECL|macro|__NR_SYSV_waitsys
mdefine_line|#define __NR_SYSV_waitsys&t;&t;(__NR_SYSV + 170)
DECL|macro|__NR_SYSV_sigstack
mdefine_line|#define __NR_SYSV_sigstack&t;&t;(__NR_SYSV + 171)
DECL|macro|__NR_SYSV_sigaltstack
mdefine_line|#define __NR_SYSV_sigaltstack&t;&t;(__NR_SYSV + 172)
DECL|macro|__NR_SYSV_sigsendset
mdefine_line|#define __NR_SYSV_sigsendset&t;&t;(__NR_SYSV + 173)
DECL|macro|__NR_SYSV_statvfs
mdefine_line|#define __NR_SYSV_statvfs&t;&t;(__NR_SYSV + 174)
DECL|macro|__NR_SYSV_fstatvfs
mdefine_line|#define __NR_SYSV_fstatvfs&t;&t;(__NR_SYSV + 175)
DECL|macro|__NR_SYSV_getpmsg
mdefine_line|#define __NR_SYSV_getpmsg&t;&t;(__NR_SYSV + 176)
DECL|macro|__NR_SYSV_putpmsg
mdefine_line|#define __NR_SYSV_putpmsg&t;&t;(__NR_SYSV + 177)
DECL|macro|__NR_SYSV_lchown
mdefine_line|#define __NR_SYSV_lchown&t;&t;(__NR_SYSV + 178)
DECL|macro|__NR_SYSV_priocntl
mdefine_line|#define __NR_SYSV_priocntl&t;&t;(__NR_SYSV + 179)
DECL|macro|__NR_SYSV_ksigqueue
mdefine_line|#define __NR_SYSV_ksigqueue&t;&t;(__NR_SYSV + 180)
DECL|macro|__NR_SYSV_readv
mdefine_line|#define __NR_SYSV_readv&t;&t;&t;(__NR_SYSV + 181)
DECL|macro|__NR_SYSV_writev
mdefine_line|#define __NR_SYSV_writev&t;&t;(__NR_SYSV + 182)
DECL|macro|__NR_SYSV_truncate64
mdefine_line|#define __NR_SYSV_truncate64&t;&t;(__NR_SYSV + 183)
DECL|macro|__NR_SYSV_ftruncate64
mdefine_line|#define __NR_SYSV_ftruncate64&t;&t;(__NR_SYSV + 184)
DECL|macro|__NR_SYSV_mmap64
mdefine_line|#define __NR_SYSV_mmap64&t;&t;(__NR_SYSV + 185)
DECL|macro|__NR_SYSV_dmi
mdefine_line|#define __NR_SYSV_dmi&t;&t;&t;(__NR_SYSV + 186)
DECL|macro|__NR_SYSV_pread
mdefine_line|#define __NR_SYSV_pread&t;&t;&t;(__NR_SYSV + 187)
DECL|macro|__NR_SYSV_pwrite
mdefine_line|#define __NR_SYSV_pwrite&t;&t;(__NR_SYSV + 188)
multiline_comment|/*&n; * BSD 4.3 syscalls are in the range from 2000 to 2999&n; */
DECL|macro|__NR_BSD43
mdefine_line|#define __NR_BSD43&t;&t;&t;2000
DECL|macro|__NR_BSD43_syscall
mdefine_line|#define __NR_BSD43_syscall&t;&t;(__NR_BSD43 +   0)
DECL|macro|__NR_BSD43_exit
mdefine_line|#define __NR_BSD43_exit&t;&t;&t;(__NR_BSD43 +   1)
DECL|macro|__NR_BSD43_fork
mdefine_line|#define __NR_BSD43_fork&t;&t;&t;(__NR_BSD43 +   2)
DECL|macro|__NR_BSD43_read
mdefine_line|#define __NR_BSD43_read&t;&t;&t;(__NR_BSD43 +   3)
DECL|macro|__NR_BSD43_write
mdefine_line|#define __NR_BSD43_write&t;&t;(__NR_BSD43 +   4)
DECL|macro|__NR_BSD43_open
mdefine_line|#define __NR_BSD43_open&t;&t;&t;(__NR_BSD43 +   5)
DECL|macro|__NR_BSD43_close
mdefine_line|#define __NR_BSD43_close&t;&t;(__NR_BSD43 +   6)
DECL|macro|__NR_BSD43_wait
mdefine_line|#define __NR_BSD43_wait&t;&t;&t;(__NR_BSD43 +   7)
DECL|macro|__NR_BSD43_creat
mdefine_line|#define __NR_BSD43_creat&t;&t;(__NR_BSD43 +   8)
DECL|macro|__NR_BSD43_link
mdefine_line|#define __NR_BSD43_link&t;&t;&t;(__NR_BSD43 +   9)
DECL|macro|__NR_BSD43_unlink
mdefine_line|#define __NR_BSD43_unlink&t;&t;(__NR_BSD43 +  10)
DECL|macro|__NR_BSD43_exec
mdefine_line|#define __NR_BSD43_exec&t;&t;&t;(__NR_BSD43 +  11)
DECL|macro|__NR_BSD43_chdir
mdefine_line|#define __NR_BSD43_chdir&t;&t;(__NR_BSD43 +  12)
DECL|macro|__NR_BSD43_time
mdefine_line|#define __NR_BSD43_time&t;&t;&t;(__NR_BSD43 +  13)
DECL|macro|__NR_BSD43_mknod
mdefine_line|#define __NR_BSD43_mknod&t;&t;(__NR_BSD43 +  14)
DECL|macro|__NR_BSD43_chmod
mdefine_line|#define __NR_BSD43_chmod&t;&t;(__NR_BSD43 +  15)
DECL|macro|__NR_BSD43_chown
mdefine_line|#define __NR_BSD43_chown&t;&t;(__NR_BSD43 +  16)
DECL|macro|__NR_BSD43_sbreak
mdefine_line|#define __NR_BSD43_sbreak&t;&t;(__NR_BSD43 +  17)
DECL|macro|__NR_BSD43_oldstat
mdefine_line|#define __NR_BSD43_oldstat&t;&t;(__NR_BSD43 +  18)
DECL|macro|__NR_BSD43_lseek
mdefine_line|#define __NR_BSD43_lseek&t;&t;(__NR_BSD43 +  19)
DECL|macro|__NR_BSD43_getpid
mdefine_line|#define __NR_BSD43_getpid&t;&t;(__NR_BSD43 +  20)
DECL|macro|__NR_BSD43_oldmount
mdefine_line|#define __NR_BSD43_oldmount&t;&t;(__NR_BSD43 +  21)
DECL|macro|__NR_BSD43_umount
mdefine_line|#define __NR_BSD43_umount&t;&t;(__NR_BSD43 +  22)
DECL|macro|__NR_BSD43_setuid
mdefine_line|#define __NR_BSD43_setuid&t;&t;(__NR_BSD43 +  23)
DECL|macro|__NR_BSD43_getuid
mdefine_line|#define __NR_BSD43_getuid&t;&t;(__NR_BSD43 +  24)
DECL|macro|__NR_BSD43_stime
mdefine_line|#define __NR_BSD43_stime&t;&t;(__NR_BSD43 +  25)
DECL|macro|__NR_BSD43_ptrace
mdefine_line|#define __NR_BSD43_ptrace&t;&t;(__NR_BSD43 +  26)
DECL|macro|__NR_BSD43_alarm
mdefine_line|#define __NR_BSD43_alarm&t;&t;(__NR_BSD43 +  27)
DECL|macro|__NR_BSD43_oldfstat
mdefine_line|#define __NR_BSD43_oldfstat&t;&t;(__NR_BSD43 +  28)
DECL|macro|__NR_BSD43_pause
mdefine_line|#define __NR_BSD43_pause&t;&t;(__NR_BSD43 +  29)
DECL|macro|__NR_BSD43_utime
mdefine_line|#define __NR_BSD43_utime&t;&t;(__NR_BSD43 +  30)
DECL|macro|__NR_BSD43_stty
mdefine_line|#define __NR_BSD43_stty&t;&t;&t;(__NR_BSD43 +  31)
DECL|macro|__NR_BSD43_gtty
mdefine_line|#define __NR_BSD43_gtty&t;&t;&t;(__NR_BSD43 +  32)
DECL|macro|__NR_BSD43_access
mdefine_line|#define __NR_BSD43_access&t;&t;(__NR_BSD43 +  33)
DECL|macro|__NR_BSD43_nice
mdefine_line|#define __NR_BSD43_nice&t;&t;&t;(__NR_BSD43 +  34)
DECL|macro|__NR_BSD43_ftime
mdefine_line|#define __NR_BSD43_ftime&t;&t;(__NR_BSD43 +  35)
DECL|macro|__NR_BSD43_sync
mdefine_line|#define __NR_BSD43_sync&t;&t;&t;(__NR_BSD43 +  36)
DECL|macro|__NR_BSD43_kill
mdefine_line|#define __NR_BSD43_kill&t;&t;&t;(__NR_BSD43 +  37)
DECL|macro|__NR_BSD43_stat
mdefine_line|#define __NR_BSD43_stat&t;&t;&t;(__NR_BSD43 +  38)
DECL|macro|__NR_BSD43_oldsetpgrp
mdefine_line|#define __NR_BSD43_oldsetpgrp&t;&t;(__NR_BSD43 +  39)
DECL|macro|__NR_BSD43_lstat
mdefine_line|#define __NR_BSD43_lstat&t;&t;(__NR_BSD43 +  40)
DECL|macro|__NR_BSD43_dup
mdefine_line|#define __NR_BSD43_dup&t;&t;&t;(__NR_BSD43 +  41)
DECL|macro|__NR_BSD43_pipe
mdefine_line|#define __NR_BSD43_pipe&t;&t;&t;(__NR_BSD43 +  42)
DECL|macro|__NR_BSD43_times
mdefine_line|#define __NR_BSD43_times&t;&t;(__NR_BSD43 +  43)
DECL|macro|__NR_BSD43_profil
mdefine_line|#define __NR_BSD43_profil&t;&t;(__NR_BSD43 +  44)
DECL|macro|__NR_BSD43_msgsys
mdefine_line|#define __NR_BSD43_msgsys&t;&t;(__NR_BSD43 +  45)
DECL|macro|__NR_BSD43_setgid
mdefine_line|#define __NR_BSD43_setgid&t;&t;(__NR_BSD43 +  46)
DECL|macro|__NR_BSD43_getgid
mdefine_line|#define __NR_BSD43_getgid&t;&t;(__NR_BSD43 +  47)
DECL|macro|__NR_BSD43_ssig
mdefine_line|#define __NR_BSD43_ssig&t;&t;&t;(__NR_BSD43 +  48)
DECL|macro|__NR_BSD43_reserved1
mdefine_line|#define __NR_BSD43_reserved1&t;&t;(__NR_BSD43 +  49)
DECL|macro|__NR_BSD43_reserved2
mdefine_line|#define __NR_BSD43_reserved2&t;&t;(__NR_BSD43 +  50)
DECL|macro|__NR_BSD43_sysacct
mdefine_line|#define __NR_BSD43_sysacct&t;&t;(__NR_BSD43 +  51)
DECL|macro|__NR_BSD43_phys
mdefine_line|#define __NR_BSD43_phys&t;&t;&t;(__NR_BSD43 +  52)
DECL|macro|__NR_BSD43_lock
mdefine_line|#define __NR_BSD43_lock&t;&t;&t;(__NR_BSD43 +  53)
DECL|macro|__NR_BSD43_ioctl
mdefine_line|#define __NR_BSD43_ioctl&t;&t;(__NR_BSD43 +  54)
DECL|macro|__NR_BSD43_reboot
mdefine_line|#define __NR_BSD43_reboot&t;&t;(__NR_BSD43 +  55)
DECL|macro|__NR_BSD43_mpxchan
mdefine_line|#define __NR_BSD43_mpxchan&t;&t;(__NR_BSD43 +  56)
DECL|macro|__NR_BSD43_symlink
mdefine_line|#define __NR_BSD43_symlink&t;&t;(__NR_BSD43 +  57)
DECL|macro|__NR_BSD43_readlink
mdefine_line|#define __NR_BSD43_readlink&t;&t;(__NR_BSD43 +  58)
DECL|macro|__NR_BSD43_execve
mdefine_line|#define __NR_BSD43_execve&t;&t;(__NR_BSD43 +  59)
DECL|macro|__NR_BSD43_umask
mdefine_line|#define __NR_BSD43_umask&t;&t;(__NR_BSD43 +  60)
DECL|macro|__NR_BSD43_chroot
mdefine_line|#define __NR_BSD43_chroot&t;&t;(__NR_BSD43 +  61)
DECL|macro|__NR_BSD43_fstat
mdefine_line|#define __NR_BSD43_fstat&t;&t;(__NR_BSD43 +  62)
DECL|macro|__NR_BSD43_reserved3
mdefine_line|#define __NR_BSD43_reserved3&t;&t;(__NR_BSD43 +  63)
DECL|macro|__NR_BSD43_getpagesize
mdefine_line|#define __NR_BSD43_getpagesize&t;&t;(__NR_BSD43 +  64)
DECL|macro|__NR_BSD43_mremap
mdefine_line|#define __NR_BSD43_mremap&t;&t;(__NR_BSD43 +  65)
DECL|macro|__NR_BSD43_vfork
mdefine_line|#define __NR_BSD43_vfork&t;&t;(__NR_BSD43 +  66)
DECL|macro|__NR_BSD43_vread
mdefine_line|#define __NR_BSD43_vread&t;&t;(__NR_BSD43 +  67)
DECL|macro|__NR_BSD43_vwrite
mdefine_line|#define __NR_BSD43_vwrite&t;&t;(__NR_BSD43 +  68)
DECL|macro|__NR_BSD43_sbrk
mdefine_line|#define __NR_BSD43_sbrk&t;&t;&t;(__NR_BSD43 +  69)
DECL|macro|__NR_BSD43_sstk
mdefine_line|#define __NR_BSD43_sstk&t;&t;&t;(__NR_BSD43 +  70)
DECL|macro|__NR_BSD43_mmap
mdefine_line|#define __NR_BSD43_mmap&t;&t;&t;(__NR_BSD43 +  71)
DECL|macro|__NR_BSD43_vadvise
mdefine_line|#define __NR_BSD43_vadvise&t;&t;(__NR_BSD43 +  72)
DECL|macro|__NR_BSD43_munmap
mdefine_line|#define __NR_BSD43_munmap&t;&t;(__NR_BSD43 +  73)
DECL|macro|__NR_BSD43_mprotect
mdefine_line|#define __NR_BSD43_mprotect&t;&t;(__NR_BSD43 +  74)
DECL|macro|__NR_BSD43_madvise
mdefine_line|#define __NR_BSD43_madvise&t;&t;(__NR_BSD43 +  75)
DECL|macro|__NR_BSD43_vhangup
mdefine_line|#define __NR_BSD43_vhangup&t;&t;(__NR_BSD43 +  76)
DECL|macro|__NR_BSD43_vlimit
mdefine_line|#define __NR_BSD43_vlimit&t;&t;(__NR_BSD43 +  77)
DECL|macro|__NR_BSD43_mincore
mdefine_line|#define __NR_BSD43_mincore&t;&t;(__NR_BSD43 +  78)
DECL|macro|__NR_BSD43_getgroups
mdefine_line|#define __NR_BSD43_getgroups&t;&t;(__NR_BSD43 +  79)
DECL|macro|__NR_BSD43_setgroups
mdefine_line|#define __NR_BSD43_setgroups&t;&t;(__NR_BSD43 +  80)
DECL|macro|__NR_BSD43_getpgrp
mdefine_line|#define __NR_BSD43_getpgrp&t;&t;(__NR_BSD43 +  81)
DECL|macro|__NR_BSD43_setpgrp
mdefine_line|#define __NR_BSD43_setpgrp&t;&t;(__NR_BSD43 +  82)
DECL|macro|__NR_BSD43_setitimer
mdefine_line|#define __NR_BSD43_setitimer&t;&t;(__NR_BSD43 +  83)
DECL|macro|__NR_BSD43_wait3
mdefine_line|#define __NR_BSD43_wait3&t;&t;(__NR_BSD43 +  84)
DECL|macro|__NR_BSD43_swapon
mdefine_line|#define __NR_BSD43_swapon&t;&t;(__NR_BSD43 +  85)
DECL|macro|__NR_BSD43_getitimer
mdefine_line|#define __NR_BSD43_getitimer&t;&t;(__NR_BSD43 +  86)
DECL|macro|__NR_BSD43_gethostname
mdefine_line|#define __NR_BSD43_gethostname&t;&t;(__NR_BSD43 +  87)
DECL|macro|__NR_BSD43_sethostname
mdefine_line|#define __NR_BSD43_sethostname&t;&t;(__NR_BSD43 +  88)
DECL|macro|__NR_BSD43_getdtablesize
mdefine_line|#define __NR_BSD43_getdtablesize&t;(__NR_BSD43 +  89)
DECL|macro|__NR_BSD43_dup2
mdefine_line|#define __NR_BSD43_dup2&t;&t;&t;(__NR_BSD43 +  90)
DECL|macro|__NR_BSD43_getdopt
mdefine_line|#define __NR_BSD43_getdopt&t;&t;(__NR_BSD43 +  91)
DECL|macro|__NR_BSD43_fcntl
mdefine_line|#define __NR_BSD43_fcntl&t;&t;(__NR_BSD43 +  92)
DECL|macro|__NR_BSD43_select
mdefine_line|#define __NR_BSD43_select&t;&t;(__NR_BSD43 +  93)
DECL|macro|__NR_BSD43_setdopt
mdefine_line|#define __NR_BSD43_setdopt&t;&t;(__NR_BSD43 +  94)
DECL|macro|__NR_BSD43_fsync
mdefine_line|#define __NR_BSD43_fsync&t;&t;(__NR_BSD43 +  95)
DECL|macro|__NR_BSD43_setpriority
mdefine_line|#define __NR_BSD43_setpriority&t;&t;(__NR_BSD43 +  96)
DECL|macro|__NR_BSD43_socket
mdefine_line|#define __NR_BSD43_socket&t;&t;(__NR_BSD43 +  97)
DECL|macro|__NR_BSD43_connect
mdefine_line|#define __NR_BSD43_connect&t;&t;(__NR_BSD43 +  98)
DECL|macro|__NR_BSD43_oldaccept
mdefine_line|#define __NR_BSD43_oldaccept&t;&t;(__NR_BSD43 +  99)
DECL|macro|__NR_BSD43_getpriority
mdefine_line|#define __NR_BSD43_getpriority&t;&t;(__NR_BSD43 + 100)
DECL|macro|__NR_BSD43_send
mdefine_line|#define __NR_BSD43_send&t;&t;&t;(__NR_BSD43 + 101)
DECL|macro|__NR_BSD43_recv
mdefine_line|#define __NR_BSD43_recv&t;&t;&t;(__NR_BSD43 + 102)
DECL|macro|__NR_BSD43_sigreturn
mdefine_line|#define __NR_BSD43_sigreturn&t;&t;(__NR_BSD43 + 103)
DECL|macro|__NR_BSD43_bind
mdefine_line|#define __NR_BSD43_bind&t;&t;&t;(__NR_BSD43 + 104)
DECL|macro|__NR_BSD43_setsockopt
mdefine_line|#define __NR_BSD43_setsockopt&t;&t;(__NR_BSD43 + 105)
DECL|macro|__NR_BSD43_listen
mdefine_line|#define __NR_BSD43_listen&t;&t;(__NR_BSD43 + 106)
DECL|macro|__NR_BSD43_vtimes
mdefine_line|#define __NR_BSD43_vtimes&t;&t;(__NR_BSD43 + 107)
DECL|macro|__NR_BSD43_sigvec
mdefine_line|#define __NR_BSD43_sigvec&t;&t;(__NR_BSD43 + 108)
DECL|macro|__NR_BSD43_sigblock
mdefine_line|#define __NR_BSD43_sigblock&t;&t;(__NR_BSD43 + 109)
DECL|macro|__NR_BSD43_sigsetmask
mdefine_line|#define __NR_BSD43_sigsetmask&t;&t;(__NR_BSD43 + 110)
DECL|macro|__NR_BSD43_sigpause
mdefine_line|#define __NR_BSD43_sigpause&t;&t;(__NR_BSD43 + 111)
DECL|macro|__NR_BSD43_sigstack
mdefine_line|#define __NR_BSD43_sigstack&t;&t;(__NR_BSD43 + 112)
DECL|macro|__NR_BSD43_oldrecvmsg
mdefine_line|#define __NR_BSD43_oldrecvmsg&t;&t;(__NR_BSD43 + 113)
DECL|macro|__NR_BSD43_oldsendmsg
mdefine_line|#define __NR_BSD43_oldsendmsg&t;&t;(__NR_BSD43 + 114)
DECL|macro|__NR_BSD43_vtrace
mdefine_line|#define __NR_BSD43_vtrace&t;&t;(__NR_BSD43 + 115)
DECL|macro|__NR_BSD43_gettimeofday
mdefine_line|#define __NR_BSD43_gettimeofday&t;&t;(__NR_BSD43 + 116)
DECL|macro|__NR_BSD43_getrusage
mdefine_line|#define __NR_BSD43_getrusage&t;&t;(__NR_BSD43 + 117)
DECL|macro|__NR_BSD43_getsockopt
mdefine_line|#define __NR_BSD43_getsockopt&t;&t;(__NR_BSD43 + 118)
DECL|macro|__NR_BSD43_reserved4
mdefine_line|#define __NR_BSD43_reserved4&t;&t;(__NR_BSD43 + 119)
DECL|macro|__NR_BSD43_readv
mdefine_line|#define __NR_BSD43_readv&t;&t;(__NR_BSD43 + 120)
DECL|macro|__NR_BSD43_writev
mdefine_line|#define __NR_BSD43_writev&t;&t;(__NR_BSD43 + 121)
DECL|macro|__NR_BSD43_settimeofday
mdefine_line|#define __NR_BSD43_settimeofday&t;&t;(__NR_BSD43 + 122)
DECL|macro|__NR_BSD43_fchown
mdefine_line|#define __NR_BSD43_fchown&t;&t;(__NR_BSD43 + 123)
DECL|macro|__NR_BSD43_fchmod
mdefine_line|#define __NR_BSD43_fchmod&t;&t;(__NR_BSD43 + 124)
DECL|macro|__NR_BSD43_oldrecvfrom
mdefine_line|#define __NR_BSD43_oldrecvfrom&t;&t;(__NR_BSD43 + 125)
DECL|macro|__NR_BSD43_setreuid
mdefine_line|#define __NR_BSD43_setreuid&t;&t;(__NR_BSD43 + 126)
DECL|macro|__NR_BSD43_setregid
mdefine_line|#define __NR_BSD43_setregid&t;&t;(__NR_BSD43 + 127)
DECL|macro|__NR_BSD43_rename
mdefine_line|#define __NR_BSD43_rename&t;&t;(__NR_BSD43 + 128)
DECL|macro|__NR_BSD43_truncate
mdefine_line|#define __NR_BSD43_truncate&t;&t;(__NR_BSD43 + 129)
DECL|macro|__NR_BSD43_ftruncate
mdefine_line|#define __NR_BSD43_ftruncate&t;&t;(__NR_BSD43 + 130)
DECL|macro|__NR_BSD43_flock
mdefine_line|#define __NR_BSD43_flock&t;&t;(__NR_BSD43 + 131)
DECL|macro|__NR_BSD43_semsys
mdefine_line|#define __NR_BSD43_semsys&t;&t;(__NR_BSD43 + 132)
DECL|macro|__NR_BSD43_sendto
mdefine_line|#define __NR_BSD43_sendto&t;&t;(__NR_BSD43 + 133)
DECL|macro|__NR_BSD43_shutdown
mdefine_line|#define __NR_BSD43_shutdown&t;&t;(__NR_BSD43 + 134)
DECL|macro|__NR_BSD43_socketpair
mdefine_line|#define __NR_BSD43_socketpair&t;&t;(__NR_BSD43 + 135)
DECL|macro|__NR_BSD43_mkdir
mdefine_line|#define __NR_BSD43_mkdir&t;&t;(__NR_BSD43 + 136)
DECL|macro|__NR_BSD43_rmdir
mdefine_line|#define __NR_BSD43_rmdir&t;&t;(__NR_BSD43 + 137)
DECL|macro|__NR_BSD43_utimes
mdefine_line|#define __NR_BSD43_utimes&t;&t;(__NR_BSD43 + 138)
DECL|macro|__NR_BSD43_sigcleanup
mdefine_line|#define __NR_BSD43_sigcleanup&t;&t;(__NR_BSD43 + 139)
DECL|macro|__NR_BSD43_adjtime
mdefine_line|#define __NR_BSD43_adjtime&t;&t;(__NR_BSD43 + 140)
DECL|macro|__NR_BSD43_oldgetpeername
mdefine_line|#define __NR_BSD43_oldgetpeername&t;(__NR_BSD43 + 141)
DECL|macro|__NR_BSD43_gethostid
mdefine_line|#define __NR_BSD43_gethostid&t;&t;(__NR_BSD43 + 142)
DECL|macro|__NR_BSD43_sethostid
mdefine_line|#define __NR_BSD43_sethostid&t;&t;(__NR_BSD43 + 143)
DECL|macro|__NR_BSD43_getrlimit
mdefine_line|#define __NR_BSD43_getrlimit&t;&t;(__NR_BSD43 + 144)
DECL|macro|__NR_BSD43_setrlimit
mdefine_line|#define __NR_BSD43_setrlimit&t;&t;(__NR_BSD43 + 145)
DECL|macro|__NR_BSD43_killpg
mdefine_line|#define __NR_BSD43_killpg&t;&t;(__NR_BSD43 + 146)
DECL|macro|__NR_BSD43_shmsys
mdefine_line|#define __NR_BSD43_shmsys&t;&t;(__NR_BSD43 + 147)
DECL|macro|__NR_BSD43_quota
mdefine_line|#define __NR_BSD43_quota&t;&t;(__NR_BSD43 + 148)
DECL|macro|__NR_BSD43_qquota
mdefine_line|#define __NR_BSD43_qquota&t;&t;(__NR_BSD43 + 149)
DECL|macro|__NR_BSD43_oldgetsockname
mdefine_line|#define __NR_BSD43_oldgetsockname&t;(__NR_BSD43 + 150)
DECL|macro|__NR_BSD43_sysmips
mdefine_line|#define __NR_BSD43_sysmips&t;&t;(__NR_BSD43 + 151)
DECL|macro|__NR_BSD43_cacheflush
mdefine_line|#define __NR_BSD43_cacheflush&t;&t;(__NR_BSD43 + 152)
DECL|macro|__NR_BSD43_cachectl
mdefine_line|#define __NR_BSD43_cachectl&t;&t;(__NR_BSD43 + 153)
DECL|macro|__NR_BSD43_debug
mdefine_line|#define __NR_BSD43_debug&t;&t;(__NR_BSD43 + 154)
DECL|macro|__NR_BSD43_reserved5
mdefine_line|#define __NR_BSD43_reserved5&t;&t;(__NR_BSD43 + 155)
DECL|macro|__NR_BSD43_reserved6
mdefine_line|#define __NR_BSD43_reserved6&t;&t;(__NR_BSD43 + 156)
DECL|macro|__NR_BSD43_nfs_mount
mdefine_line|#define __NR_BSD43_nfs_mount&t;&t;(__NR_BSD43 + 157)
DECL|macro|__NR_BSD43_nfs_svc
mdefine_line|#define __NR_BSD43_nfs_svc&t;&t;(__NR_BSD43 + 158)
DECL|macro|__NR_BSD43_getdirentries
mdefine_line|#define __NR_BSD43_getdirentries&t;(__NR_BSD43 + 159)
DECL|macro|__NR_BSD43_statfs
mdefine_line|#define __NR_BSD43_statfs&t;&t;(__NR_BSD43 + 160)
DECL|macro|__NR_BSD43_fstatfs
mdefine_line|#define __NR_BSD43_fstatfs&t;&t;(__NR_BSD43 + 161)
DECL|macro|__NR_BSD43_unmount
mdefine_line|#define __NR_BSD43_unmount&t;&t;(__NR_BSD43 + 162)
DECL|macro|__NR_BSD43_async_daemon
mdefine_line|#define __NR_BSD43_async_daemon&t;&t;(__NR_BSD43 + 163)
DECL|macro|__NR_BSD43_nfs_getfh
mdefine_line|#define __NR_BSD43_nfs_getfh&t;&t;(__NR_BSD43 + 164)
DECL|macro|__NR_BSD43_getdomainname
mdefine_line|#define __NR_BSD43_getdomainname&t;(__NR_BSD43 + 165)
DECL|macro|__NR_BSD43_setdomainname
mdefine_line|#define __NR_BSD43_setdomainname&t;(__NR_BSD43 + 166)
DECL|macro|__NR_BSD43_pcfs_mount
mdefine_line|#define __NR_BSD43_pcfs_mount&t;&t;(__NR_BSD43 + 167)
DECL|macro|__NR_BSD43_quotactl
mdefine_line|#define __NR_BSD43_quotactl&t;&t;(__NR_BSD43 + 168)
DECL|macro|__NR_BSD43_oldexportfs
mdefine_line|#define __NR_BSD43_oldexportfs&t;&t;(__NR_BSD43 + 169)
DECL|macro|__NR_BSD43_smount
mdefine_line|#define __NR_BSD43_smount&t;&t;(__NR_BSD43 + 170)
DECL|macro|__NR_BSD43_mipshwconf
mdefine_line|#define __NR_BSD43_mipshwconf&t;&t;(__NR_BSD43 + 171)
DECL|macro|__NR_BSD43_exportfs
mdefine_line|#define __NR_BSD43_exportfs&t;&t;(__NR_BSD43 + 172)
DECL|macro|__NR_BSD43_nfsfh_open
mdefine_line|#define __NR_BSD43_nfsfh_open&t;&t;(__NR_BSD43 + 173)
DECL|macro|__NR_BSD43_libattach
mdefine_line|#define __NR_BSD43_libattach&t;&t;(__NR_BSD43 + 174)
DECL|macro|__NR_BSD43_libdetach
mdefine_line|#define __NR_BSD43_libdetach&t;&t;(__NR_BSD43 + 175)
DECL|macro|__NR_BSD43_accept
mdefine_line|#define __NR_BSD43_accept&t;&t;(__NR_BSD43 + 176)
DECL|macro|__NR_BSD43_reserved7
mdefine_line|#define __NR_BSD43_reserved7&t;&t;(__NR_BSD43 + 177)
DECL|macro|__NR_BSD43_reserved8
mdefine_line|#define __NR_BSD43_reserved8&t;&t;(__NR_BSD43 + 178)
DECL|macro|__NR_BSD43_recvmsg
mdefine_line|#define __NR_BSD43_recvmsg&t;&t;(__NR_BSD43 + 179)
DECL|macro|__NR_BSD43_recvfrom
mdefine_line|#define __NR_BSD43_recvfrom&t;&t;(__NR_BSD43 + 180)
DECL|macro|__NR_BSD43_sendmsg
mdefine_line|#define __NR_BSD43_sendmsg&t;&t;(__NR_BSD43 + 181)
DECL|macro|__NR_BSD43_getpeername
mdefine_line|#define __NR_BSD43_getpeername&t;&t;(__NR_BSD43 + 182)
DECL|macro|__NR_BSD43_getsockname
mdefine_line|#define __NR_BSD43_getsockname&t;&t;(__NR_BSD43 + 183)
DECL|macro|__NR_BSD43_aread
mdefine_line|#define __NR_BSD43_aread&t;&t;(__NR_BSD43 + 184)
DECL|macro|__NR_BSD43_awrite
mdefine_line|#define __NR_BSD43_awrite&t;&t;(__NR_BSD43 + 185)
DECL|macro|__NR_BSD43_listio
mdefine_line|#define __NR_BSD43_listio&t;&t;(__NR_BSD43 + 186)
DECL|macro|__NR_BSD43_acancel
mdefine_line|#define __NR_BSD43_acancel&t;&t;(__NR_BSD43 + 187)
DECL|macro|__NR_BSD43_astatus
mdefine_line|#define __NR_BSD43_astatus&t;&t;(__NR_BSD43 + 188)
DECL|macro|__NR_BSD43_await
mdefine_line|#define __NR_BSD43_await&t;&t;(__NR_BSD43 + 189)
DECL|macro|__NR_BSD43_areadv
mdefine_line|#define __NR_BSD43_areadv&t;&t;(__NR_BSD43 + 190)
DECL|macro|__NR_BSD43_awritev
mdefine_line|#define __NR_BSD43_awritev&t;&t;(__NR_BSD43 + 191)
multiline_comment|/*&n; * POSIX syscalls are in the range from 3000 to 3999&n; */
DECL|macro|__NR_POSIX
mdefine_line|#define __NR_POSIX&t;&t;&t;3000
DECL|macro|__NR_POSIX_syscall
mdefine_line|#define __NR_POSIX_syscall&t;&t;(__NR_POSIX +   0)
DECL|macro|__NR_POSIX_exit
mdefine_line|#define __NR_POSIX_exit&t;&t;&t;(__NR_POSIX +   1)
DECL|macro|__NR_POSIX_fork
mdefine_line|#define __NR_POSIX_fork&t;&t;&t;(__NR_POSIX +   2)
DECL|macro|__NR_POSIX_read
mdefine_line|#define __NR_POSIX_read&t;&t;&t;(__NR_POSIX +   3)
DECL|macro|__NR_POSIX_write
mdefine_line|#define __NR_POSIX_write&t;&t;(__NR_POSIX +   4)
DECL|macro|__NR_POSIX_open
mdefine_line|#define __NR_POSIX_open&t;&t;&t;(__NR_POSIX +   5)
DECL|macro|__NR_POSIX_close
mdefine_line|#define __NR_POSIX_close&t;&t;(__NR_POSIX +   6)
DECL|macro|__NR_POSIX_wait
mdefine_line|#define __NR_POSIX_wait&t;&t;&t;(__NR_POSIX +   7)
DECL|macro|__NR_POSIX_creat
mdefine_line|#define __NR_POSIX_creat&t;&t;(__NR_POSIX +   8)
DECL|macro|__NR_POSIX_link
mdefine_line|#define __NR_POSIX_link&t;&t;&t;(__NR_POSIX +   9)
DECL|macro|__NR_POSIX_unlink
mdefine_line|#define __NR_POSIX_unlink&t;&t;(__NR_POSIX +  10)
DECL|macro|__NR_POSIX_exec
mdefine_line|#define __NR_POSIX_exec&t;&t;&t;(__NR_POSIX +  11)
DECL|macro|__NR_POSIX_chdir
mdefine_line|#define __NR_POSIX_chdir&t;&t;(__NR_POSIX +  12)
DECL|macro|__NR_POSIX_gtime
mdefine_line|#define __NR_POSIX_gtime&t;&t;(__NR_POSIX +  13)
DECL|macro|__NR_POSIX_mknod
mdefine_line|#define __NR_POSIX_mknod&t;&t;(__NR_POSIX +  14)
DECL|macro|__NR_POSIX_chmod
mdefine_line|#define __NR_POSIX_chmod&t;&t;(__NR_POSIX +  15)
DECL|macro|__NR_POSIX_chown
mdefine_line|#define __NR_POSIX_chown&t;&t;(__NR_POSIX +  16)
DECL|macro|__NR_POSIX_sbreak
mdefine_line|#define __NR_POSIX_sbreak&t;&t;(__NR_POSIX +  17)
DECL|macro|__NR_POSIX_stat
mdefine_line|#define __NR_POSIX_stat&t;&t;&t;(__NR_POSIX +  18)
DECL|macro|__NR_POSIX_lseek
mdefine_line|#define __NR_POSIX_lseek&t;&t;(__NR_POSIX +  19)
DECL|macro|__NR_POSIX_getpid
mdefine_line|#define __NR_POSIX_getpid&t;&t;(__NR_POSIX +  20)
DECL|macro|__NR_POSIX_mount
mdefine_line|#define __NR_POSIX_mount&t;&t;(__NR_POSIX +  21)
DECL|macro|__NR_POSIX_umount
mdefine_line|#define __NR_POSIX_umount&t;&t;(__NR_POSIX +  22)
DECL|macro|__NR_POSIX_setuid
mdefine_line|#define __NR_POSIX_setuid&t;&t;(__NR_POSIX +  23)
DECL|macro|__NR_POSIX_getuid
mdefine_line|#define __NR_POSIX_getuid&t;&t;(__NR_POSIX +  24)
DECL|macro|__NR_POSIX_stime
mdefine_line|#define __NR_POSIX_stime&t;&t;(__NR_POSIX +  25)
DECL|macro|__NR_POSIX_ptrace
mdefine_line|#define __NR_POSIX_ptrace&t;&t;(__NR_POSIX +  26)
DECL|macro|__NR_POSIX_alarm
mdefine_line|#define __NR_POSIX_alarm&t;&t;(__NR_POSIX +  27)
DECL|macro|__NR_POSIX_fstat
mdefine_line|#define __NR_POSIX_fstat&t;&t;(__NR_POSIX +  28)
DECL|macro|__NR_POSIX_pause
mdefine_line|#define __NR_POSIX_pause&t;&t;(__NR_POSIX +  29)
DECL|macro|__NR_POSIX_utime
mdefine_line|#define __NR_POSIX_utime&t;&t;(__NR_POSIX +  30)
DECL|macro|__NR_POSIX_stty
mdefine_line|#define __NR_POSIX_stty&t;&t;&t;(__NR_POSIX +  31)
DECL|macro|__NR_POSIX_gtty
mdefine_line|#define __NR_POSIX_gtty&t;&t;&t;(__NR_POSIX +  32)
DECL|macro|__NR_POSIX_access
mdefine_line|#define __NR_POSIX_access&t;&t;(__NR_POSIX +  33)
DECL|macro|__NR_POSIX_nice
mdefine_line|#define __NR_POSIX_nice&t;&t;&t;(__NR_POSIX +  34)
DECL|macro|__NR_POSIX_statfs
mdefine_line|#define __NR_POSIX_statfs&t;&t;(__NR_POSIX +  35)
DECL|macro|__NR_POSIX_sync
mdefine_line|#define __NR_POSIX_sync&t;&t;&t;(__NR_POSIX +  36)
DECL|macro|__NR_POSIX_kill
mdefine_line|#define __NR_POSIX_kill&t;&t;&t;(__NR_POSIX +  37)
DECL|macro|__NR_POSIX_fstatfs
mdefine_line|#define __NR_POSIX_fstatfs&t;&t;(__NR_POSIX +  38)
DECL|macro|__NR_POSIX_getpgrp
mdefine_line|#define __NR_POSIX_getpgrp&t;&t;(__NR_POSIX +  39)
DECL|macro|__NR_POSIX_syssgi
mdefine_line|#define __NR_POSIX_syssgi&t;&t;(__NR_POSIX +  40)
DECL|macro|__NR_POSIX_dup
mdefine_line|#define __NR_POSIX_dup&t;&t;&t;(__NR_POSIX +  41)
DECL|macro|__NR_POSIX_pipe
mdefine_line|#define __NR_POSIX_pipe&t;&t;&t;(__NR_POSIX +  42)
DECL|macro|__NR_POSIX_times
mdefine_line|#define __NR_POSIX_times&t;&t;(__NR_POSIX +  43)
DECL|macro|__NR_POSIX_profil
mdefine_line|#define __NR_POSIX_profil&t;&t;(__NR_POSIX +  44)
DECL|macro|__NR_POSIX_lock
mdefine_line|#define __NR_POSIX_lock&t;&t;&t;(__NR_POSIX +  45)
DECL|macro|__NR_POSIX_setgid
mdefine_line|#define __NR_POSIX_setgid&t;&t;(__NR_POSIX +  46)
DECL|macro|__NR_POSIX_getgid
mdefine_line|#define __NR_POSIX_getgid&t;&t;(__NR_POSIX +  47)
DECL|macro|__NR_POSIX_sig
mdefine_line|#define __NR_POSIX_sig&t;&t;&t;(__NR_POSIX +  48)
DECL|macro|__NR_POSIX_msgsys
mdefine_line|#define __NR_POSIX_msgsys&t;&t;(__NR_POSIX +  49)
DECL|macro|__NR_POSIX_sysmips
mdefine_line|#define __NR_POSIX_sysmips&t;&t;(__NR_POSIX +  50)
DECL|macro|__NR_POSIX_sysacct
mdefine_line|#define __NR_POSIX_sysacct&t;&t;(__NR_POSIX +  51)
DECL|macro|__NR_POSIX_shmsys
mdefine_line|#define __NR_POSIX_shmsys&t;&t;(__NR_POSIX +  52)
DECL|macro|__NR_POSIX_semsys
mdefine_line|#define __NR_POSIX_semsys&t;&t;(__NR_POSIX +  53)
DECL|macro|__NR_POSIX_ioctl
mdefine_line|#define __NR_POSIX_ioctl&t;&t;(__NR_POSIX +  54)
DECL|macro|__NR_POSIX_uadmin
mdefine_line|#define __NR_POSIX_uadmin&t;&t;(__NR_POSIX +  55)
DECL|macro|__NR_POSIX_exch
mdefine_line|#define __NR_POSIX_exch&t;&t;&t;(__NR_POSIX +  56)
DECL|macro|__NR_POSIX_utssys
mdefine_line|#define __NR_POSIX_utssys&t;&t;(__NR_POSIX +  57)
DECL|macro|__NR_POSIX_USG_reserved1
mdefine_line|#define __NR_POSIX_USG_reserved1&t;(__NR_POSIX +  58)
DECL|macro|__NR_POSIX_exece
mdefine_line|#define __NR_POSIX_exece&t;&t;(__NR_POSIX +  59)
DECL|macro|__NR_POSIX_umask
mdefine_line|#define __NR_POSIX_umask&t;&t;(__NR_POSIX +  60)
DECL|macro|__NR_POSIX_chroot
mdefine_line|#define __NR_POSIX_chroot&t;&t;(__NR_POSIX +  61)
DECL|macro|__NR_POSIX_fcntl
mdefine_line|#define __NR_POSIX_fcntl&t;&t;(__NR_POSIX +  62)
DECL|macro|__NR_POSIX_ulimit
mdefine_line|#define __NR_POSIX_ulimit&t;&t;(__NR_POSIX +  63)
DECL|macro|__NR_POSIX_SAFARI4_reserved1
mdefine_line|#define __NR_POSIX_SAFARI4_reserved1&t;(__NR_POSIX +  64)
DECL|macro|__NR_POSIX_SAFARI4_reserved2
mdefine_line|#define __NR_POSIX_SAFARI4_reserved2&t;(__NR_POSIX +  65)
DECL|macro|__NR_POSIX_SAFARI4_reserved3
mdefine_line|#define __NR_POSIX_SAFARI4_reserved3&t;(__NR_POSIX +  66)
DECL|macro|__NR_POSIX_SAFARI4_reserved4
mdefine_line|#define __NR_POSIX_SAFARI4_reserved4&t;(__NR_POSIX +  67)
DECL|macro|__NR_POSIX_SAFARI4_reserved5
mdefine_line|#define __NR_POSIX_SAFARI4_reserved5&t;(__NR_POSIX +  68)
DECL|macro|__NR_POSIX_SAFARI4_reserved6
mdefine_line|#define __NR_POSIX_SAFARI4_reserved6&t;(__NR_POSIX +  69)
DECL|macro|__NR_POSIX_advfs
mdefine_line|#define __NR_POSIX_advfs&t;&t;(__NR_POSIX +  70)
DECL|macro|__NR_POSIX_unadvfs
mdefine_line|#define __NR_POSIX_unadvfs&t;&t;(__NR_POSIX +  71)
DECL|macro|__NR_POSIX_rmount
mdefine_line|#define __NR_POSIX_rmount&t;&t;(__NR_POSIX +  72)
DECL|macro|__NR_POSIX_rumount
mdefine_line|#define __NR_POSIX_rumount&t;&t;(__NR_POSIX +  73)
DECL|macro|__NR_POSIX_rfstart
mdefine_line|#define __NR_POSIX_rfstart&t;&t;(__NR_POSIX +  74)
DECL|macro|__NR_POSIX_reserved1
mdefine_line|#define __NR_POSIX_reserved1&t;&t;(__NR_POSIX +  75)
DECL|macro|__NR_POSIX_rdebug
mdefine_line|#define __NR_POSIX_rdebug&t;&t;(__NR_POSIX +  76)
DECL|macro|__NR_POSIX_rfstop
mdefine_line|#define __NR_POSIX_rfstop&t;&t;(__NR_POSIX +  77)
DECL|macro|__NR_POSIX_rfsys
mdefine_line|#define __NR_POSIX_rfsys&t;&t;(__NR_POSIX +  78)
DECL|macro|__NR_POSIX_rmdir
mdefine_line|#define __NR_POSIX_rmdir&t;&t;(__NR_POSIX +  79)
DECL|macro|__NR_POSIX_mkdir
mdefine_line|#define __NR_POSIX_mkdir&t;&t;(__NR_POSIX +  80)
DECL|macro|__NR_POSIX_getdents
mdefine_line|#define __NR_POSIX_getdents&t;&t;(__NR_POSIX +  81)
DECL|macro|__NR_POSIX_sginap
mdefine_line|#define __NR_POSIX_sginap&t;&t;(__NR_POSIX +  82)
DECL|macro|__NR_POSIX_sgikopt
mdefine_line|#define __NR_POSIX_sgikopt&t;&t;(__NR_POSIX +  83)
DECL|macro|__NR_POSIX_sysfs
mdefine_line|#define __NR_POSIX_sysfs&t;&t;(__NR_POSIX +  84)
DECL|macro|__NR_POSIX_getmsg
mdefine_line|#define __NR_POSIX_getmsg&t;&t;(__NR_POSIX +  85)
DECL|macro|__NR_POSIX_putmsg
mdefine_line|#define __NR_POSIX_putmsg&t;&t;(__NR_POSIX +  86)
DECL|macro|__NR_POSIX_poll
mdefine_line|#define __NR_POSIX_poll&t;&t;&t;(__NR_POSIX +  87)
DECL|macro|__NR_POSIX_sigreturn
mdefine_line|#define __NR_POSIX_sigreturn&t;&t;(__NR_POSIX +  88)
DECL|macro|__NR_POSIX_accept
mdefine_line|#define __NR_POSIX_accept&t;&t;(__NR_POSIX +  89)
DECL|macro|__NR_POSIX_bind
mdefine_line|#define __NR_POSIX_bind&t;&t;&t;(__NR_POSIX +  90)
DECL|macro|__NR_POSIX_connect
mdefine_line|#define __NR_POSIX_connect&t;&t;(__NR_POSIX +  91)
DECL|macro|__NR_POSIX_gethostid
mdefine_line|#define __NR_POSIX_gethostid&t;&t;(__NR_POSIX +  92)
DECL|macro|__NR_POSIX_getpeername
mdefine_line|#define __NR_POSIX_getpeername&t;&t;(__NR_POSIX +  93)
DECL|macro|__NR_POSIX_getsockname
mdefine_line|#define __NR_POSIX_getsockname&t;&t;(__NR_POSIX +  94)
DECL|macro|__NR_POSIX_getsockopt
mdefine_line|#define __NR_POSIX_getsockopt&t;&t;(__NR_POSIX +  95)
DECL|macro|__NR_POSIX_listen
mdefine_line|#define __NR_POSIX_listen&t;&t;(__NR_POSIX +  96)
DECL|macro|__NR_POSIX_recv
mdefine_line|#define __NR_POSIX_recv&t;&t;&t;(__NR_POSIX +  97)
DECL|macro|__NR_POSIX_recvfrom
mdefine_line|#define __NR_POSIX_recvfrom&t;&t;(__NR_POSIX +  98)
DECL|macro|__NR_POSIX_recvmsg
mdefine_line|#define __NR_POSIX_recvmsg&t;&t;(__NR_POSIX +  99)
DECL|macro|__NR_POSIX_select
mdefine_line|#define __NR_POSIX_select&t;&t;(__NR_POSIX + 100)
DECL|macro|__NR_POSIX_send
mdefine_line|#define __NR_POSIX_send&t;&t;&t;(__NR_POSIX + 101)
DECL|macro|__NR_POSIX_sendmsg
mdefine_line|#define __NR_POSIX_sendmsg&t;&t;(__NR_POSIX + 102)
DECL|macro|__NR_POSIX_sendto
mdefine_line|#define __NR_POSIX_sendto&t;&t;(__NR_POSIX + 103)
DECL|macro|__NR_POSIX_sethostid
mdefine_line|#define __NR_POSIX_sethostid&t;&t;(__NR_POSIX + 104)
DECL|macro|__NR_POSIX_setsockopt
mdefine_line|#define __NR_POSIX_setsockopt&t;&t;(__NR_POSIX + 105)
DECL|macro|__NR_POSIX_shutdown
mdefine_line|#define __NR_POSIX_shutdown&t;&t;(__NR_POSIX + 106)
DECL|macro|__NR_POSIX_socket
mdefine_line|#define __NR_POSIX_socket&t;&t;(__NR_POSIX + 107)
DECL|macro|__NR_POSIX_gethostname
mdefine_line|#define __NR_POSIX_gethostname&t;&t;(__NR_POSIX + 108)
DECL|macro|__NR_POSIX_sethostname
mdefine_line|#define __NR_POSIX_sethostname&t;&t;(__NR_POSIX + 109)
DECL|macro|__NR_POSIX_getdomainname
mdefine_line|#define __NR_POSIX_getdomainname&t;(__NR_POSIX + 110)
DECL|macro|__NR_POSIX_setdomainname
mdefine_line|#define __NR_POSIX_setdomainname&t;(__NR_POSIX + 111)
DECL|macro|__NR_POSIX_truncate
mdefine_line|#define __NR_POSIX_truncate&t;&t;(__NR_POSIX + 112)
DECL|macro|__NR_POSIX_ftruncate
mdefine_line|#define __NR_POSIX_ftruncate&t;&t;(__NR_POSIX + 113)
DECL|macro|__NR_POSIX_rename
mdefine_line|#define __NR_POSIX_rename&t;&t;(__NR_POSIX + 114)
DECL|macro|__NR_POSIX_symlink
mdefine_line|#define __NR_POSIX_symlink&t;&t;(__NR_POSIX + 115)
DECL|macro|__NR_POSIX_readlink
mdefine_line|#define __NR_POSIX_readlink&t;&t;(__NR_POSIX + 116)
DECL|macro|__NR_POSIX_lstat
mdefine_line|#define __NR_POSIX_lstat&t;&t;(__NR_POSIX + 117)
DECL|macro|__NR_POSIX_nfs_mount
mdefine_line|#define __NR_POSIX_nfs_mount&t;&t;(__NR_POSIX + 118)
DECL|macro|__NR_POSIX_nfs_svc
mdefine_line|#define __NR_POSIX_nfs_svc&t;&t;(__NR_POSIX + 119)
DECL|macro|__NR_POSIX_nfs_getfh
mdefine_line|#define __NR_POSIX_nfs_getfh&t;&t;(__NR_POSIX + 120)
DECL|macro|__NR_POSIX_async_daemon
mdefine_line|#define __NR_POSIX_async_daemon&t;&t;(__NR_POSIX + 121)
DECL|macro|__NR_POSIX_exportfs
mdefine_line|#define __NR_POSIX_exportfs&t;&t;(__NR_POSIX + 122)
DECL|macro|__NR_POSIX_SGI_setregid
mdefine_line|#define __NR_POSIX_SGI_setregid&t;&t;(__NR_POSIX + 123)
DECL|macro|__NR_POSIX_SGI_setreuid
mdefine_line|#define __NR_POSIX_SGI_setreuid&t;&t;(__NR_POSIX + 124)
DECL|macro|__NR_POSIX_getitimer
mdefine_line|#define __NR_POSIX_getitimer&t;&t;(__NR_POSIX + 125)
DECL|macro|__NR_POSIX_setitimer
mdefine_line|#define __NR_POSIX_setitimer&t;&t;(__NR_POSIX + 126)
DECL|macro|__NR_POSIX_adjtime
mdefine_line|#define __NR_POSIX_adjtime&t;&t;(__NR_POSIX + 127)
DECL|macro|__NR_POSIX_SGI_bsdgettime
mdefine_line|#define __NR_POSIX_SGI_bsdgettime&t;(__NR_POSIX + 128)
DECL|macro|__NR_POSIX_SGI_sproc
mdefine_line|#define __NR_POSIX_SGI_sproc&t;&t;(__NR_POSIX + 129)
DECL|macro|__NR_POSIX_SGI_prctl
mdefine_line|#define __NR_POSIX_SGI_prctl&t;&t;(__NR_POSIX + 130)
DECL|macro|__NR_POSIX_SGI_blkproc
mdefine_line|#define __NR_POSIX_SGI_blkproc&t;&t;(__NR_POSIX + 131)
DECL|macro|__NR_POSIX_SGI_reserved1
mdefine_line|#define __NR_POSIX_SGI_reserved1&t;(__NR_POSIX + 132)
DECL|macro|__NR_POSIX_SGI_sgigsc
mdefine_line|#define __NR_POSIX_SGI_sgigsc&t;&t;(__NR_POSIX + 133)
DECL|macro|__NR_POSIX_SGI_mmap
mdefine_line|#define __NR_POSIX_SGI_mmap&t;&t;(__NR_POSIX + 134)
DECL|macro|__NR_POSIX_SGI_munmap
mdefine_line|#define __NR_POSIX_SGI_munmap&t;&t;(__NR_POSIX + 135)
DECL|macro|__NR_POSIX_SGI_mprotect
mdefine_line|#define __NR_POSIX_SGI_mprotect&t;&t;(__NR_POSIX + 136)
DECL|macro|__NR_POSIX_SGI_msync
mdefine_line|#define __NR_POSIX_SGI_msync&t;&t;(__NR_POSIX + 137)
DECL|macro|__NR_POSIX_SGI_madvise
mdefine_line|#define __NR_POSIX_SGI_madvise&t;&t;(__NR_POSIX + 138)
DECL|macro|__NR_POSIX_SGI_mpin
mdefine_line|#define __NR_POSIX_SGI_mpin&t;&t;(__NR_POSIX + 139)
DECL|macro|__NR_POSIX_SGI_getpagesize
mdefine_line|#define __NR_POSIX_SGI_getpagesize&t;(__NR_POSIX + 140)
DECL|macro|__NR_POSIX_SGI_libattach
mdefine_line|#define __NR_POSIX_SGI_libattach&t;(__NR_POSIX + 141)
DECL|macro|__NR_POSIX_SGI_libdetach
mdefine_line|#define __NR_POSIX_SGI_libdetach&t;(__NR_POSIX + 142)
DECL|macro|__NR_POSIX_SGI_getpgrp
mdefine_line|#define __NR_POSIX_SGI_getpgrp&t;&t;(__NR_POSIX + 143)
DECL|macro|__NR_POSIX_SGI_setpgrp
mdefine_line|#define __NR_POSIX_SGI_setpgrp&t;&t;(__NR_POSIX + 144)
DECL|macro|__NR_POSIX_SGI_reserved2
mdefine_line|#define __NR_POSIX_SGI_reserved2&t;(__NR_POSIX + 145)
DECL|macro|__NR_POSIX_SGI_reserved3
mdefine_line|#define __NR_POSIX_SGI_reserved3&t;(__NR_POSIX + 146)
DECL|macro|__NR_POSIX_SGI_reserved4
mdefine_line|#define __NR_POSIX_SGI_reserved4&t;(__NR_POSIX + 147)
DECL|macro|__NR_POSIX_SGI_reserved5
mdefine_line|#define __NR_POSIX_SGI_reserved5&t;(__NR_POSIX + 148)
DECL|macro|__NR_POSIX_SGI_reserved6
mdefine_line|#define __NR_POSIX_SGI_reserved6&t;(__NR_POSIX + 149)
DECL|macro|__NR_POSIX_cacheflush
mdefine_line|#define __NR_POSIX_cacheflush&t;&t;(__NR_POSIX + 150)
DECL|macro|__NR_POSIX_cachectl
mdefine_line|#define __NR_POSIX_cachectl&t;&t;(__NR_POSIX + 151)
DECL|macro|__NR_POSIX_fchown
mdefine_line|#define __NR_POSIX_fchown&t;&t;(__NR_POSIX + 152)
DECL|macro|__NR_POSIX_fchmod
mdefine_line|#define __NR_POSIX_fchmod&t;&t;(__NR_POSIX + 153)
DECL|macro|__NR_POSIX_wait3
mdefine_line|#define __NR_POSIX_wait3&t;&t;(__NR_POSIX + 154)
DECL|macro|__NR_POSIX_mmap
mdefine_line|#define __NR_POSIX_mmap&t;&t;&t;(__NR_POSIX + 155)
DECL|macro|__NR_POSIX_munmap
mdefine_line|#define __NR_POSIX_munmap&t;&t;(__NR_POSIX + 156)
DECL|macro|__NR_POSIX_madvise
mdefine_line|#define __NR_POSIX_madvise&t;&t;(__NR_POSIX + 157)
DECL|macro|__NR_POSIX_BSD_getpagesize
mdefine_line|#define __NR_POSIX_BSD_getpagesize&t;(__NR_POSIX + 158)
DECL|macro|__NR_POSIX_setreuid
mdefine_line|#define __NR_POSIX_setreuid&t;&t;(__NR_POSIX + 159)
DECL|macro|__NR_POSIX_setregid
mdefine_line|#define __NR_POSIX_setregid&t;&t;(__NR_POSIX + 160)
DECL|macro|__NR_POSIX_setpgid
mdefine_line|#define __NR_POSIX_setpgid&t;&t;(__NR_POSIX + 161)
DECL|macro|__NR_POSIX_getgroups
mdefine_line|#define __NR_POSIX_getgroups&t;&t;(__NR_POSIX + 162)
DECL|macro|__NR_POSIX_setgroups
mdefine_line|#define __NR_POSIX_setgroups&t;&t;(__NR_POSIX + 163)
DECL|macro|__NR_POSIX_gettimeofday
mdefine_line|#define __NR_POSIX_gettimeofday&t;&t;(__NR_POSIX + 164)
DECL|macro|__NR_POSIX_getrusage
mdefine_line|#define __NR_POSIX_getrusage&t;&t;(__NR_POSIX + 165)
DECL|macro|__NR_POSIX_getrlimit
mdefine_line|#define __NR_POSIX_getrlimit&t;&t;(__NR_POSIX + 166)
DECL|macro|__NR_POSIX_setrlimit
mdefine_line|#define __NR_POSIX_setrlimit&t;&t;(__NR_POSIX + 167)
DECL|macro|__NR_POSIX_waitpid
mdefine_line|#define __NR_POSIX_waitpid&t;&t;(__NR_POSIX + 168)
DECL|macro|__NR_POSIX_dup2
mdefine_line|#define __NR_POSIX_dup2&t;&t;&t;(__NR_POSIX + 169)
DECL|macro|__NR_POSIX_reserved2
mdefine_line|#define __NR_POSIX_reserved2&t;&t;(__NR_POSIX + 170)
DECL|macro|__NR_POSIX_reserved3
mdefine_line|#define __NR_POSIX_reserved3&t;&t;(__NR_POSIX + 171)
DECL|macro|__NR_POSIX_reserved4
mdefine_line|#define __NR_POSIX_reserved4&t;&t;(__NR_POSIX + 172)
DECL|macro|__NR_POSIX_reserved5
mdefine_line|#define __NR_POSIX_reserved5&t;&t;(__NR_POSIX + 173)
DECL|macro|__NR_POSIX_reserved6
mdefine_line|#define __NR_POSIX_reserved6&t;&t;(__NR_POSIX + 174)
DECL|macro|__NR_POSIX_reserved7
mdefine_line|#define __NR_POSIX_reserved7&t;&t;(__NR_POSIX + 175)
DECL|macro|__NR_POSIX_reserved8
mdefine_line|#define __NR_POSIX_reserved8&t;&t;(__NR_POSIX + 176)
DECL|macro|__NR_POSIX_reserved9
mdefine_line|#define __NR_POSIX_reserved9&t;&t;(__NR_POSIX + 177)
DECL|macro|__NR_POSIX_reserved10
mdefine_line|#define __NR_POSIX_reserved10&t;&t;(__NR_POSIX + 178)
DECL|macro|__NR_POSIX_reserved11
mdefine_line|#define __NR_POSIX_reserved11&t;&t;(__NR_POSIX + 179)
DECL|macro|__NR_POSIX_reserved12
mdefine_line|#define __NR_POSIX_reserved12&t;&t;(__NR_POSIX + 180)
DECL|macro|__NR_POSIX_reserved13
mdefine_line|#define __NR_POSIX_reserved13&t;&t;(__NR_POSIX + 181)
DECL|macro|__NR_POSIX_reserved14
mdefine_line|#define __NR_POSIX_reserved14&t;&t;(__NR_POSIX + 182)
DECL|macro|__NR_POSIX_reserved15
mdefine_line|#define __NR_POSIX_reserved15&t;&t;(__NR_POSIX + 183)
DECL|macro|__NR_POSIX_reserved16
mdefine_line|#define __NR_POSIX_reserved16&t;&t;(__NR_POSIX + 184)
DECL|macro|__NR_POSIX_reserved17
mdefine_line|#define __NR_POSIX_reserved17&t;&t;(__NR_POSIX + 185)
DECL|macro|__NR_POSIX_reserved18
mdefine_line|#define __NR_POSIX_reserved18&t;&t;(__NR_POSIX + 186)
DECL|macro|__NR_POSIX_reserved19
mdefine_line|#define __NR_POSIX_reserved19&t;&t;(__NR_POSIX + 187)
DECL|macro|__NR_POSIX_reserved20
mdefine_line|#define __NR_POSIX_reserved20&t;&t;(__NR_POSIX + 188)
DECL|macro|__NR_POSIX_reserved21
mdefine_line|#define __NR_POSIX_reserved21&t;&t;(__NR_POSIX + 189)
DECL|macro|__NR_POSIX_reserved22
mdefine_line|#define __NR_POSIX_reserved22&t;&t;(__NR_POSIX + 190)
DECL|macro|__NR_POSIX_reserved23
mdefine_line|#define __NR_POSIX_reserved23&t;&t;(__NR_POSIX + 191)
DECL|macro|__NR_POSIX_reserved24
mdefine_line|#define __NR_POSIX_reserved24&t;&t;(__NR_POSIX + 192)
DECL|macro|__NR_POSIX_reserved25
mdefine_line|#define __NR_POSIX_reserved25&t;&t;(__NR_POSIX + 193)
DECL|macro|__NR_POSIX_reserved26
mdefine_line|#define __NR_POSIX_reserved26&t;&t;(__NR_POSIX + 194)
DECL|macro|__NR_POSIX_reserved27
mdefine_line|#define __NR_POSIX_reserved27&t;&t;(__NR_POSIX + 195)
DECL|macro|__NR_POSIX_reserved28
mdefine_line|#define __NR_POSIX_reserved28&t;&t;(__NR_POSIX + 196)
DECL|macro|__NR_POSIX_reserved29
mdefine_line|#define __NR_POSIX_reserved29&t;&t;(__NR_POSIX + 197)
DECL|macro|__NR_POSIX_reserved30
mdefine_line|#define __NR_POSIX_reserved30&t;&t;(__NR_POSIX + 198)
DECL|macro|__NR_POSIX_reserved31
mdefine_line|#define __NR_POSIX_reserved31&t;&t;(__NR_POSIX + 199)
DECL|macro|__NR_POSIX_reserved32
mdefine_line|#define __NR_POSIX_reserved32&t;&t;(__NR_POSIX + 200)
DECL|macro|__NR_POSIX_reserved33
mdefine_line|#define __NR_POSIX_reserved33&t;&t;(__NR_POSIX + 201)
DECL|macro|__NR_POSIX_reserved34
mdefine_line|#define __NR_POSIX_reserved34&t;&t;(__NR_POSIX + 202)
DECL|macro|__NR_POSIX_reserved35
mdefine_line|#define __NR_POSIX_reserved35&t;&t;(__NR_POSIX + 203)
DECL|macro|__NR_POSIX_reserved36
mdefine_line|#define __NR_POSIX_reserved36&t;&t;(__NR_POSIX + 204)
DECL|macro|__NR_POSIX_reserved37
mdefine_line|#define __NR_POSIX_reserved37&t;&t;(__NR_POSIX + 205)
DECL|macro|__NR_POSIX_reserved38
mdefine_line|#define __NR_POSIX_reserved38&t;&t;(__NR_POSIX + 206)
DECL|macro|__NR_POSIX_reserved39
mdefine_line|#define __NR_POSIX_reserved39&t;&t;(__NR_POSIX + 207)
DECL|macro|__NR_POSIX_reserved40
mdefine_line|#define __NR_POSIX_reserved40&t;&t;(__NR_POSIX + 208)
DECL|macro|__NR_POSIX_reserved41
mdefine_line|#define __NR_POSIX_reserved41&t;&t;(__NR_POSIX + 209)
DECL|macro|__NR_POSIX_reserved42
mdefine_line|#define __NR_POSIX_reserved42&t;&t;(__NR_POSIX + 210)
DECL|macro|__NR_POSIX_reserved43
mdefine_line|#define __NR_POSIX_reserved43&t;&t;(__NR_POSIX + 211)
DECL|macro|__NR_POSIX_reserved44
mdefine_line|#define __NR_POSIX_reserved44&t;&t;(__NR_POSIX + 212)
DECL|macro|__NR_POSIX_reserved45
mdefine_line|#define __NR_POSIX_reserved45&t;&t;(__NR_POSIX + 213)
DECL|macro|__NR_POSIX_reserved46
mdefine_line|#define __NR_POSIX_reserved46&t;&t;(__NR_POSIX + 214)
DECL|macro|__NR_POSIX_reserved47
mdefine_line|#define __NR_POSIX_reserved47&t;&t;(__NR_POSIX + 215)
DECL|macro|__NR_POSIX_reserved48
mdefine_line|#define __NR_POSIX_reserved48&t;&t;(__NR_POSIX + 216)
DECL|macro|__NR_POSIX_reserved49
mdefine_line|#define __NR_POSIX_reserved49&t;&t;(__NR_POSIX + 217)
DECL|macro|__NR_POSIX_reserved50
mdefine_line|#define __NR_POSIX_reserved50&t;&t;(__NR_POSIX + 218)
DECL|macro|__NR_POSIX_reserved51
mdefine_line|#define __NR_POSIX_reserved51&t;&t;(__NR_POSIX + 219)
DECL|macro|__NR_POSIX_reserved52
mdefine_line|#define __NR_POSIX_reserved52&t;&t;(__NR_POSIX + 220)
DECL|macro|__NR_POSIX_reserved53
mdefine_line|#define __NR_POSIX_reserved53&t;&t;(__NR_POSIX + 221)
DECL|macro|__NR_POSIX_reserved54
mdefine_line|#define __NR_POSIX_reserved54&t;&t;(__NR_POSIX + 222)
DECL|macro|__NR_POSIX_reserved55
mdefine_line|#define __NR_POSIX_reserved55&t;&t;(__NR_POSIX + 223)
DECL|macro|__NR_POSIX_reserved56
mdefine_line|#define __NR_POSIX_reserved56&t;&t;(__NR_POSIX + 224)
DECL|macro|__NR_POSIX_reserved57
mdefine_line|#define __NR_POSIX_reserved57&t;&t;(__NR_POSIX + 225)
DECL|macro|__NR_POSIX_reserved58
mdefine_line|#define __NR_POSIX_reserved58&t;&t;(__NR_POSIX + 226)
DECL|macro|__NR_POSIX_reserved59
mdefine_line|#define __NR_POSIX_reserved59&t;&t;(__NR_POSIX + 227)
DECL|macro|__NR_POSIX_reserved60
mdefine_line|#define __NR_POSIX_reserved60&t;&t;(__NR_POSIX + 228)
DECL|macro|__NR_POSIX_reserved61
mdefine_line|#define __NR_POSIX_reserved61&t;&t;(__NR_POSIX + 229)
DECL|macro|__NR_POSIX_reserved62
mdefine_line|#define __NR_POSIX_reserved62&t;&t;(__NR_POSIX + 230)
DECL|macro|__NR_POSIX_reserved63
mdefine_line|#define __NR_POSIX_reserved63&t;&t;(__NR_POSIX + 231)
DECL|macro|__NR_POSIX_reserved64
mdefine_line|#define __NR_POSIX_reserved64&t;&t;(__NR_POSIX + 232)
DECL|macro|__NR_POSIX_reserved65
mdefine_line|#define __NR_POSIX_reserved65&t;&t;(__NR_POSIX + 233)
DECL|macro|__NR_POSIX_reserved66
mdefine_line|#define __NR_POSIX_reserved66&t;&t;(__NR_POSIX + 234)
DECL|macro|__NR_POSIX_reserved67
mdefine_line|#define __NR_POSIX_reserved67&t;&t;(__NR_POSIX + 235)
DECL|macro|__NR_POSIX_reserved68
mdefine_line|#define __NR_POSIX_reserved68&t;&t;(__NR_POSIX + 236)
DECL|macro|__NR_POSIX_reserved69
mdefine_line|#define __NR_POSIX_reserved69&t;&t;(__NR_POSIX + 237)
DECL|macro|__NR_POSIX_reserved70
mdefine_line|#define __NR_POSIX_reserved70&t;&t;(__NR_POSIX + 238)
DECL|macro|__NR_POSIX_reserved71
mdefine_line|#define __NR_POSIX_reserved71&t;&t;(__NR_POSIX + 239)
DECL|macro|__NR_POSIX_reserved72
mdefine_line|#define __NR_POSIX_reserved72&t;&t;(__NR_POSIX + 240)
DECL|macro|__NR_POSIX_reserved73
mdefine_line|#define __NR_POSIX_reserved73&t;&t;(__NR_POSIX + 241)
DECL|macro|__NR_POSIX_reserved74
mdefine_line|#define __NR_POSIX_reserved74&t;&t;(__NR_POSIX + 242)
DECL|macro|__NR_POSIX_reserved75
mdefine_line|#define __NR_POSIX_reserved75&t;&t;(__NR_POSIX + 243)
DECL|macro|__NR_POSIX_reserved76
mdefine_line|#define __NR_POSIX_reserved76&t;&t;(__NR_POSIX + 244)
DECL|macro|__NR_POSIX_reserved77
mdefine_line|#define __NR_POSIX_reserved77&t;&t;(__NR_POSIX + 245)
DECL|macro|__NR_POSIX_reserved78
mdefine_line|#define __NR_POSIX_reserved78&t;&t;(__NR_POSIX + 246)
DECL|macro|__NR_POSIX_reserved79
mdefine_line|#define __NR_POSIX_reserved79&t;&t;(__NR_POSIX + 247)
DECL|macro|__NR_POSIX_reserved80
mdefine_line|#define __NR_POSIX_reserved80&t;&t;(__NR_POSIX + 248)
DECL|macro|__NR_POSIX_reserved81
mdefine_line|#define __NR_POSIX_reserved81&t;&t;(__NR_POSIX + 249)
DECL|macro|__NR_POSIX_reserved82
mdefine_line|#define __NR_POSIX_reserved82&t;&t;(__NR_POSIX + 250)
DECL|macro|__NR_POSIX_reserved83
mdefine_line|#define __NR_POSIX_reserved83&t;&t;(__NR_POSIX + 251)
DECL|macro|__NR_POSIX_reserved84
mdefine_line|#define __NR_POSIX_reserved84&t;&t;(__NR_POSIX + 252)
DECL|macro|__NR_POSIX_reserved85
mdefine_line|#define __NR_POSIX_reserved85&t;&t;(__NR_POSIX + 253)
DECL|macro|__NR_POSIX_reserved86
mdefine_line|#define __NR_POSIX_reserved86&t;&t;(__NR_POSIX + 254)
DECL|macro|__NR_POSIX_reserved87
mdefine_line|#define __NR_POSIX_reserved87&t;&t;(__NR_POSIX + 255)
DECL|macro|__NR_POSIX_reserved88
mdefine_line|#define __NR_POSIX_reserved88&t;&t;(__NR_POSIX + 256)
DECL|macro|__NR_POSIX_reserved89
mdefine_line|#define __NR_POSIX_reserved89&t;&t;(__NR_POSIX + 257)
DECL|macro|__NR_POSIX_reserved90
mdefine_line|#define __NR_POSIX_reserved90&t;&t;(__NR_POSIX + 258)
DECL|macro|__NR_POSIX_reserved91
mdefine_line|#define __NR_POSIX_reserved91&t;&t;(__NR_POSIX + 259)
DECL|macro|__NR_POSIX_netboot
mdefine_line|#define __NR_POSIX_netboot&t;&t;(__NR_POSIX + 260)
DECL|macro|__NR_POSIX_netunboot
mdefine_line|#define __NR_POSIX_netunboot&t;&t;(__NR_POSIX + 261)
DECL|macro|__NR_POSIX_rdump
mdefine_line|#define __NR_POSIX_rdump&t;&t;(__NR_POSIX + 262)
DECL|macro|__NR_POSIX_setsid
mdefine_line|#define __NR_POSIX_setsid&t;&t;(__NR_POSIX + 263)
DECL|macro|__NR_POSIX_getmaxsig
mdefine_line|#define __NR_POSIX_getmaxsig&t;&t;(__NR_POSIX + 264)
DECL|macro|__NR_POSIX_sigpending
mdefine_line|#define __NR_POSIX_sigpending&t;&t;(__NR_POSIX + 265)
DECL|macro|__NR_POSIX_sigprocmask
mdefine_line|#define __NR_POSIX_sigprocmask&t;&t;(__NR_POSIX + 266)
DECL|macro|__NR_POSIX_sigsuspend
mdefine_line|#define __NR_POSIX_sigsuspend&t;&t;(__NR_POSIX + 267)
DECL|macro|__NR_POSIX_sigaction
mdefine_line|#define __NR_POSIX_sigaction&t;&t;(__NR_POSIX + 268)
DECL|macro|__NR_POSIX_MIPS_reserved1
mdefine_line|#define __NR_POSIX_MIPS_reserved1&t;(__NR_POSIX + 269)
DECL|macro|__NR_POSIX_MIPS_reserved2
mdefine_line|#define __NR_POSIX_MIPS_reserved2&t;(__NR_POSIX + 270)
DECL|macro|__NR_POSIX_MIPS_reserved3
mdefine_line|#define __NR_POSIX_MIPS_reserved3&t;(__NR_POSIX + 271)
DECL|macro|__NR_POSIX_MIPS_reserved4
mdefine_line|#define __NR_POSIX_MIPS_reserved4&t;(__NR_POSIX + 272)
DECL|macro|__NR_POSIX_MIPS_reserved5
mdefine_line|#define __NR_POSIX_MIPS_reserved5&t;(__NR_POSIX + 273)
DECL|macro|__NR_POSIX_MIPS_reserved6
mdefine_line|#define __NR_POSIX_MIPS_reserved6&t;(__NR_POSIX + 274)
DECL|macro|__NR_POSIX_MIPS_reserved7
mdefine_line|#define __NR_POSIX_MIPS_reserved7&t;(__NR_POSIX + 275)
DECL|macro|__NR_POSIX_MIPS_reserved8
mdefine_line|#define __NR_POSIX_MIPS_reserved8&t;(__NR_POSIX + 276)
DECL|macro|__NR_POSIX_MIPS_reserved9
mdefine_line|#define __NR_POSIX_MIPS_reserved9&t;(__NR_POSIX + 277)
DECL|macro|__NR_POSIX_MIPS_reserved10
mdefine_line|#define __NR_POSIX_MIPS_reserved10&t;(__NR_POSIX + 278)
DECL|macro|__NR_POSIX_MIPS_reserved11
mdefine_line|#define __NR_POSIX_MIPS_reserved11&t;(__NR_POSIX + 279)
DECL|macro|__NR_POSIX_TANDEM_reserved1
mdefine_line|#define __NR_POSIX_TANDEM_reserved1&t;(__NR_POSIX + 280)
DECL|macro|__NR_POSIX_TANDEM_reserved2
mdefine_line|#define __NR_POSIX_TANDEM_reserved2&t;(__NR_POSIX + 281)
DECL|macro|__NR_POSIX_TANDEM_reserved3
mdefine_line|#define __NR_POSIX_TANDEM_reserved3&t;(__NR_POSIX + 282)
DECL|macro|__NR_POSIX_TANDEM_reserved4
mdefine_line|#define __NR_POSIX_TANDEM_reserved4&t;(__NR_POSIX + 283)
DECL|macro|__NR_POSIX_TANDEM_reserved5
mdefine_line|#define __NR_POSIX_TANDEM_reserved5&t;(__NR_POSIX + 284)
DECL|macro|__NR_POSIX_TANDEM_reserved6
mdefine_line|#define __NR_POSIX_TANDEM_reserved6&t;(__NR_POSIX + 285)
DECL|macro|__NR_POSIX_TANDEM_reserved7
mdefine_line|#define __NR_POSIX_TANDEM_reserved7&t;(__NR_POSIX + 286)
DECL|macro|__NR_POSIX_TANDEM_reserved8
mdefine_line|#define __NR_POSIX_TANDEM_reserved8&t;(__NR_POSIX + 287)
DECL|macro|__NR_POSIX_TANDEM_reserved9
mdefine_line|#define __NR_POSIX_TANDEM_reserved9&t;(__NR_POSIX + 288)
DECL|macro|__NR_POSIX_TANDEM_reserved10
mdefine_line|#define __NR_POSIX_TANDEM_reserved10&t;(__NR_POSIX + 289)
DECL|macro|__NR_POSIX_TANDEM_reserved11
mdefine_line|#define __NR_POSIX_TANDEM_reserved11&t;(__NR_POSIX + 290)
DECL|macro|__NR_POSIX_TANDEM_reserved12
mdefine_line|#define __NR_POSIX_TANDEM_reserved12&t;(__NR_POSIX + 291)
DECL|macro|__NR_POSIX_TANDEM_reserved13
mdefine_line|#define __NR_POSIX_TANDEM_reserved13&t;(__NR_POSIX + 292)
DECL|macro|__NR_POSIX_TANDEM_reserved14
mdefine_line|#define __NR_POSIX_TANDEM_reserved14&t;(__NR_POSIX + 293)
DECL|macro|__NR_POSIX_TANDEM_reserved15
mdefine_line|#define __NR_POSIX_TANDEM_reserved15&t;(__NR_POSIX + 294)
DECL|macro|__NR_POSIX_TANDEM_reserved16
mdefine_line|#define __NR_POSIX_TANDEM_reserved16&t;(__NR_POSIX + 295)
DECL|macro|__NR_POSIX_TANDEM_reserved17
mdefine_line|#define __NR_POSIX_TANDEM_reserved17&t;(__NR_POSIX + 296)
DECL|macro|__NR_POSIX_TANDEM_reserved18
mdefine_line|#define __NR_POSIX_TANDEM_reserved18&t;(__NR_POSIX + 297)
DECL|macro|__NR_POSIX_TANDEM_reserved19
mdefine_line|#define __NR_POSIX_TANDEM_reserved19&t;(__NR_POSIX + 298)
DECL|macro|__NR_POSIX_TANDEM_reserved20
mdefine_line|#define __NR_POSIX_TANDEM_reserved20&t;(__NR_POSIX + 299)
DECL|macro|__NR_POSIX_SGI_reserved7
mdefine_line|#define __NR_POSIX_SGI_reserved7&t;(__NR_POSIX + 300)
DECL|macro|__NR_POSIX_SGI_reserved8
mdefine_line|#define __NR_POSIX_SGI_reserved8&t;(__NR_POSIX + 301)
DECL|macro|__NR_POSIX_SGI_reserved9
mdefine_line|#define __NR_POSIX_SGI_reserved9&t;(__NR_POSIX + 302)
DECL|macro|__NR_POSIX_SGI_reserved10
mdefine_line|#define __NR_POSIX_SGI_reserved10&t;(__NR_POSIX + 303)
DECL|macro|__NR_POSIX_SGI_reserved11
mdefine_line|#define __NR_POSIX_SGI_reserved11&t;(__NR_POSIX + 304)
DECL|macro|__NR_POSIX_SGI_reserved12
mdefine_line|#define __NR_POSIX_SGI_reserved12&t;(__NR_POSIX + 305)
DECL|macro|__NR_POSIX_SGI_reserved13
mdefine_line|#define __NR_POSIX_SGI_reserved13&t;(__NR_POSIX + 306)
DECL|macro|__NR_POSIX_SGI_reserved14
mdefine_line|#define __NR_POSIX_SGI_reserved14&t;(__NR_POSIX + 307)
DECL|macro|__NR_POSIX_SGI_reserved15
mdefine_line|#define __NR_POSIX_SGI_reserved15&t;(__NR_POSIX + 308)
DECL|macro|__NR_POSIX_SGI_reserved16
mdefine_line|#define __NR_POSIX_SGI_reserved16&t;(__NR_POSIX + 309)
DECL|macro|__NR_POSIX_SGI_reserved17
mdefine_line|#define __NR_POSIX_SGI_reserved17&t;(__NR_POSIX + 310)
DECL|macro|__NR_POSIX_SGI_reserved18
mdefine_line|#define __NR_POSIX_SGI_reserved18&t;(__NR_POSIX + 311)
DECL|macro|__NR_POSIX_SGI_reserved19
mdefine_line|#define __NR_POSIX_SGI_reserved19&t;(__NR_POSIX + 312)
DECL|macro|__NR_POSIX_SGI_reserved20
mdefine_line|#define __NR_POSIX_SGI_reserved20&t;(__NR_POSIX + 313)
DECL|macro|__NR_POSIX_SGI_reserved21
mdefine_line|#define __NR_POSIX_SGI_reserved21&t;(__NR_POSIX + 314)
DECL|macro|__NR_POSIX_SGI_reserved22
mdefine_line|#define __NR_POSIX_SGI_reserved22&t;(__NR_POSIX + 315)
DECL|macro|__NR_POSIX_SGI_reserved23
mdefine_line|#define __NR_POSIX_SGI_reserved23&t;(__NR_POSIX + 316)
DECL|macro|__NR_POSIX_SGI_reserved24
mdefine_line|#define __NR_POSIX_SGI_reserved24&t;(__NR_POSIX + 317)
DECL|macro|__NR_POSIX_SGI_reserved25
mdefine_line|#define __NR_POSIX_SGI_reserved25&t;(__NR_POSIX + 318)
DECL|macro|__NR_POSIX_SGI_reserved26
mdefine_line|#define __NR_POSIX_SGI_reserved26&t;(__NR_POSIX + 319)
macro_line|#endif /* _ASM_RISCOS_SYSCALL_H */
eof
