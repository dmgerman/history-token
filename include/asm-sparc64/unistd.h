multiline_comment|/* $Id: unistd.h,v 1.50 2002/02/08 03:57:18 davem Exp $ */
macro_line|#ifndef _SPARC64_UNISTD_H
DECL|macro|_SPARC64_UNISTD_H
mdefine_line|#define _SPARC64_UNISTD_H
multiline_comment|/*&n; * System calls under the Sparc.&n; *&n; * Don&squot;t be scared by the ugly clobbers, it is the only way I can&n; * think of right now to force the arguments into fixed registers&n; * before the trap into the system call with gcc &squot;asm&squot; statements.&n; *&n; * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)&n; *&n; * SunOS compatibility based upon preliminary work which is:&n; *&n; * Copyright (C) 1995 Adrian M. Rodriguez (adrian@remus.rutgers.edu)&n; */
DECL|macro|__NR_restart_syscall
mdefine_line|#define __NR_restart_syscall      0 /* Linux Specific&t;&t;&t;&t;   */
DECL|macro|__NR_exit
mdefine_line|#define __NR_exit                 1 /* Common                                      */
DECL|macro|__NR_fork
mdefine_line|#define __NR_fork                 2 /* Common                                      */
DECL|macro|__NR_read
mdefine_line|#define __NR_read                 3 /* Common                                      */
DECL|macro|__NR_write
mdefine_line|#define __NR_write                4 /* Common                                      */
DECL|macro|__NR_open
mdefine_line|#define __NR_open                 5 /* Common                                      */
DECL|macro|__NR_close
mdefine_line|#define __NR_close                6 /* Common                                      */
DECL|macro|__NR_wait4
mdefine_line|#define __NR_wait4                7 /* Common                                      */
DECL|macro|__NR_creat
mdefine_line|#define __NR_creat                8 /* Common                                      */
DECL|macro|__NR_link
mdefine_line|#define __NR_link                 9 /* Common                                      */
DECL|macro|__NR_unlink
mdefine_line|#define __NR_unlink              10 /* Common                                      */
DECL|macro|__NR_execv
mdefine_line|#define __NR_execv               11 /* SunOS Specific                              */
DECL|macro|__NR_chdir
mdefine_line|#define __NR_chdir               12 /* Common                                      */
DECL|macro|__NR_chown
mdefine_line|#define __NR_chown&t;&t; 13 /* Common&t;&t;&t;&t;&t;   */
DECL|macro|__NR_mknod
mdefine_line|#define __NR_mknod               14 /* Common                                      */
DECL|macro|__NR_chmod
mdefine_line|#define __NR_chmod               15 /* Common                                      */
DECL|macro|__NR_lchown
mdefine_line|#define __NR_lchown              16 /* Common                                      */
DECL|macro|__NR_brk
mdefine_line|#define __NR_brk                 17 /* Common                                      */
DECL|macro|__NR_perfctr
mdefine_line|#define __NR_perfctr             18 /* Performance counter operations              */
DECL|macro|__NR_lseek
mdefine_line|#define __NR_lseek               19 /* Common                                      */
DECL|macro|__NR_getpid
mdefine_line|#define __NR_getpid              20 /* Common                                      */
DECL|macro|__NR_capget
mdefine_line|#define __NR_capget&t;&t; 21 /* Linux Specific&t;&t;&t;&t;   */
DECL|macro|__NR_capset
mdefine_line|#define __NR_capset&t;&t; 22 /* Linux Specific&t;&t;&t;&t;   */
DECL|macro|__NR_setuid
mdefine_line|#define __NR_setuid              23 /* Implemented via setreuid in SunOS           */
DECL|macro|__NR_getuid
mdefine_line|#define __NR_getuid              24 /* Common                                      */
multiline_comment|/* #define __NR_time alias&t; 25    ENOSYS under SunOS&t;&t;&t;   */
DECL|macro|__NR_ptrace
mdefine_line|#define __NR_ptrace              26 /* Common                                      */
DECL|macro|__NR_alarm
mdefine_line|#define __NR_alarm               27 /* Implemented via setitimer in SunOS          */
DECL|macro|__NR_sigaltstack
mdefine_line|#define __NR_sigaltstack&t; 28 /* Common&t;&t;&t;&t;&t;   */
DECL|macro|__NR_pause
mdefine_line|#define __NR_pause               29 /* Is sigblock(0)-&gt;sigpause() in SunOS         */
DECL|macro|__NR_utime
mdefine_line|#define __NR_utime               30 /* Implemented via utimes() under SunOS        */
multiline_comment|/* #define __NR_lchown32         31    Linux sparc32 specific                      */
multiline_comment|/* #define __NR_fchown32         32    Linux sparc32 specific                      */
DECL|macro|__NR_access
mdefine_line|#define __NR_access              33 /* Common                                      */
DECL|macro|__NR_nice
mdefine_line|#define __NR_nice                34 /* Implemented via get/setpriority() in SunOS  */
multiline_comment|/* #define __NR_chown32          35    Linux sparc32 specific                      */
DECL|macro|__NR_sync
mdefine_line|#define __NR_sync                36 /* Common                                      */
DECL|macro|__NR_kill
mdefine_line|#define __NR_kill                37 /* Common                                      */
DECL|macro|__NR_stat
mdefine_line|#define __NR_stat                38 /* Common                                      */
DECL|macro|__NR_sendfile
mdefine_line|#define __NR_sendfile&t;&t; 39 /* Linux Specific&t;&t;&t;&t;   */
DECL|macro|__NR_lstat
mdefine_line|#define __NR_lstat               40 /* Common                                      */
DECL|macro|__NR_dup
mdefine_line|#define __NR_dup                 41 /* Common                                      */
DECL|macro|__NR_pipe
mdefine_line|#define __NR_pipe                42 /* Common                                      */
DECL|macro|__NR_times
mdefine_line|#define __NR_times               43 /* Implemented via getrusage() in SunOS        */
multiline_comment|/* #define __NR_getuid32         44    Linux sparc32 specific                      */
DECL|macro|__NR_umount2
mdefine_line|#define __NR_umount2             45 /* Linux Specific                              */
DECL|macro|__NR_setgid
mdefine_line|#define __NR_setgid              46 /* Implemented via setregid() in SunOS         */
DECL|macro|__NR_getgid
mdefine_line|#define __NR_getgid              47 /* Common                                      */
DECL|macro|__NR_signal
mdefine_line|#define __NR_signal              48 /* Implemented via sigvec() in SunOS           */
DECL|macro|__NR_geteuid
mdefine_line|#define __NR_geteuid             49 /* SunOS calls getuid()                        */
DECL|macro|__NR_getegid
mdefine_line|#define __NR_getegid             50 /* SunOS calls getgid()                        */
DECL|macro|__NR_acct
mdefine_line|#define __NR_acct                51 /* Common                                      */
DECL|macro|__NR_memory_ordering
mdefine_line|#define __NR_memory_ordering&t; 52 /* Linux Specific&t;&t;&t;&t;   */
multiline_comment|/* #define __NR_getgid32         53    Linux sparc32 specific                      */
DECL|macro|__NR_ioctl
mdefine_line|#define __NR_ioctl               54 /* Common                                      */
DECL|macro|__NR_reboot
mdefine_line|#define __NR_reboot              55 /* Common                                      */
multiline_comment|/* #define __NR_mmap2&t;&t; 56    Linux sparc32 Specific                      */
DECL|macro|__NR_symlink
mdefine_line|#define __NR_symlink             57 /* Common                                      */
DECL|macro|__NR_readlink
mdefine_line|#define __NR_readlink            58 /* Common                                      */
DECL|macro|__NR_execve
mdefine_line|#define __NR_execve              59 /* Common                                      */
DECL|macro|__NR_umask
mdefine_line|#define __NR_umask               60 /* Common                                      */
DECL|macro|__NR_chroot
mdefine_line|#define __NR_chroot              61 /* Common                                      */
DECL|macro|__NR_fstat
mdefine_line|#define __NR_fstat               62 /* Common                                      */
multiline_comment|/* #define __NR_fstat64          63    Linux sparc32 Specific                      */
DECL|macro|__NR_getpagesize
mdefine_line|#define __NR_getpagesize         64 /* Common                                      */
DECL|macro|__NR_msync
mdefine_line|#define __NR_msync               65 /* Common in newer 1.3.x revs...               */
DECL|macro|__NR_vfork
mdefine_line|#define __NR_vfork               66 /* Common                                      */
DECL|macro|__NR_pread64
mdefine_line|#define __NR_pread64             67 /* Linux Specific                              */
DECL|macro|__NR_pwrite64
mdefine_line|#define __NR_pwrite64            68 /* Linux Specific                              */
multiline_comment|/* #define __NR_geteuid32        69    Linux sparc32, sbrk under SunOS             */
multiline_comment|/* #define __NR_getegid32        70    Linux sparc32, sstk under SunOS             */
DECL|macro|__NR_mmap
mdefine_line|#define __NR_mmap                71 /* Common                                      */
multiline_comment|/* #define __NR_setreuid32       72    Linux sparc32, vadvise under SunOS          */
DECL|macro|__NR_munmap
mdefine_line|#define __NR_munmap              73 /* Common                                      */
DECL|macro|__NR_mprotect
mdefine_line|#define __NR_mprotect            74 /* Common                                      */
DECL|macro|__NR_madvise
mdefine_line|#define __NR_madvise             75 /* Common                                      */
DECL|macro|__NR_vhangup
mdefine_line|#define __NR_vhangup             76 /* Common                                      */
multiline_comment|/* #define __NR_truncate64       77    Linux sparc32 Specific&t;&t;&t;   */
DECL|macro|__NR_mincore
mdefine_line|#define __NR_mincore             78 /* Common                                      */
DECL|macro|__NR_getgroups
mdefine_line|#define __NR_getgroups           79 /* Common                                      */
DECL|macro|__NR_setgroups
mdefine_line|#define __NR_setgroups           80 /* Common                                      */
DECL|macro|__NR_getpgrp
mdefine_line|#define __NR_getpgrp             81 /* Common                                      */
multiline_comment|/* #define __NR_setgroups32      82    Linux sparc32, setpgrp under SunOS          */
DECL|macro|__NR_setitimer
mdefine_line|#define __NR_setitimer           83 /* Common                                      */
multiline_comment|/* #define __NR_ftruncate64      84    Linux sparc32 Specific&t;&t;&t;   */
DECL|macro|__NR_swapon
mdefine_line|#define __NR_swapon              85 /* Common                                      */
DECL|macro|__NR_getitimer
mdefine_line|#define __NR_getitimer           86 /* Common                                      */
multiline_comment|/* #define __NR_setuid32         87    Linux sparc32, gethostname under SunOS      */
DECL|macro|__NR_sethostname
mdefine_line|#define __NR_sethostname         88 /* Common                                      */
multiline_comment|/* #define __NR_setgid32         89    Linux sparc32, getdtablesize under SunOS    */
DECL|macro|__NR_dup2
mdefine_line|#define __NR_dup2                90 /* Common                                      */
multiline_comment|/* #define __NR_setfsuid32       91    Linux sparc32, getdopt under SunOS          */
DECL|macro|__NR_fcntl
mdefine_line|#define __NR_fcntl               92 /* Common                                      */
DECL|macro|__NR_select
mdefine_line|#define __NR_select              93 /* Common                                      */
multiline_comment|/* #define __NR_setfsgid32       94    Linux sparc32, setdopt under SunOS          */
DECL|macro|__NR_fsync
mdefine_line|#define __NR_fsync               95 /* Common                                      */
DECL|macro|__NR_setpriority
mdefine_line|#define __NR_setpriority         96 /* Common                                      */
DECL|macro|__NR_socket
mdefine_line|#define __NR_socket              97 /* Common                                      */
DECL|macro|__NR_connect
mdefine_line|#define __NR_connect             98 /* Common                                      */
DECL|macro|__NR_accept
mdefine_line|#define __NR_accept              99 /* Common                                      */
DECL|macro|__NR_getpriority
mdefine_line|#define __NR_getpriority        100 /* Common                                      */
DECL|macro|__NR_rt_sigreturn
mdefine_line|#define __NR_rt_sigreturn       101 /* Linux Specific                              */
DECL|macro|__NR_rt_sigaction
mdefine_line|#define __NR_rt_sigaction       102 /* Linux Specific                              */
DECL|macro|__NR_rt_sigprocmask
mdefine_line|#define __NR_rt_sigprocmask     103 /* Linux Specific                              */
DECL|macro|__NR_rt_sigpending
mdefine_line|#define __NR_rt_sigpending      104 /* Linux Specific                              */
DECL|macro|__NR_rt_sigtimedwait
mdefine_line|#define __NR_rt_sigtimedwait    105 /* Linux Specific                              */
DECL|macro|__NR_rt_sigqueueinfo
mdefine_line|#define __NR_rt_sigqueueinfo    106 /* Linux Specific                              */
DECL|macro|__NR_rt_sigsuspend
mdefine_line|#define __NR_rt_sigsuspend      107 /* Linux Specific                              */
DECL|macro|__NR_setresuid
mdefine_line|#define __NR_setresuid          108 /* Linux Specific, sigvec under SunOS&t;   */
DECL|macro|__NR_getresuid
mdefine_line|#define __NR_getresuid          109 /* Linux Specific, sigblock under SunOS&t;   */
DECL|macro|__NR_setresgid
mdefine_line|#define __NR_setresgid          110 /* Linux Specific, sigsetmask under SunOS&t;   */
DECL|macro|__NR_getresgid
mdefine_line|#define __NR_getresgid          111 /* Linux Specific, sigpause under SunOS&t;   */
multiline_comment|/* #define __NR_setregid32       75    Linux sparc32, sigstack under SunOS         */
DECL|macro|__NR_recvmsg
mdefine_line|#define __NR_recvmsg            113 /* Common                                      */
DECL|macro|__NR_sendmsg
mdefine_line|#define __NR_sendmsg            114 /* Common                                      */
multiline_comment|/* #define __NR_getgroups32     115    Linux sparc32, vtrace under SunOS           */
DECL|macro|__NR_gettimeofday
mdefine_line|#define __NR_gettimeofday       116 /* Common                                      */
DECL|macro|__NR_getrusage
mdefine_line|#define __NR_getrusage          117 /* Common                                      */
DECL|macro|__NR_getsockopt
mdefine_line|#define __NR_getsockopt         118 /* Common                                      */
DECL|macro|__NR_getcwd
mdefine_line|#define __NR_getcwd&t;&t;119 /* Linux Specific&t;&t;&t;&t;   */
DECL|macro|__NR_readv
mdefine_line|#define __NR_readv              120 /* Common                                      */
DECL|macro|__NR_writev
mdefine_line|#define __NR_writev             121 /* Common                                      */
DECL|macro|__NR_settimeofday
mdefine_line|#define __NR_settimeofday       122 /* Common                                      */
DECL|macro|__NR_fchown
mdefine_line|#define __NR_fchown             123 /* Common                                      */
DECL|macro|__NR_fchmod
mdefine_line|#define __NR_fchmod             124 /* Common                                      */
DECL|macro|__NR_recvfrom
mdefine_line|#define __NR_recvfrom           125 /* Common                                      */
DECL|macro|__NR_setreuid
mdefine_line|#define __NR_setreuid           126 /* Common                                      */
DECL|macro|__NR_setregid
mdefine_line|#define __NR_setregid           127 /* Common                                      */
DECL|macro|__NR_rename
mdefine_line|#define __NR_rename             128 /* Common                                      */
DECL|macro|__NR_truncate
mdefine_line|#define __NR_truncate           129 /* Common                                      */
DECL|macro|__NR_ftruncate
mdefine_line|#define __NR_ftruncate          130 /* Common                                      */
DECL|macro|__NR_flock
mdefine_line|#define __NR_flock              131 /* Common                                      */
multiline_comment|/* #define __NR_lstat64&t;&t;132    Linux sparc32 Specific                      */
DECL|macro|__NR_sendto
mdefine_line|#define __NR_sendto             133 /* Common                                      */
DECL|macro|__NR_shutdown
mdefine_line|#define __NR_shutdown           134 /* Common                                      */
DECL|macro|__NR_socketpair
mdefine_line|#define __NR_socketpair         135 /* Common                                      */
DECL|macro|__NR_mkdir
mdefine_line|#define __NR_mkdir              136 /* Common                                      */
DECL|macro|__NR_rmdir
mdefine_line|#define __NR_rmdir              137 /* Common                                      */
DECL|macro|__NR_utimes
mdefine_line|#define __NR_utimes             138 /* SunOS Specific                              */
multiline_comment|/* #define __NR_stat64&t;&t;139    Linux sparc32 Specific&t;&t;&t;   */
DECL|macro|__NR_sendfile64
mdefine_line|#define __NR_sendfile64         140 /* adjtime under SunOS                         */
DECL|macro|__NR_getpeername
mdefine_line|#define __NR_getpeername        141 /* Common                                      */
DECL|macro|__NR_futex
mdefine_line|#define __NR_futex              142 /* gethostid under SunOS                       */
DECL|macro|__NR_gettid
mdefine_line|#define __NR_gettid             143 /* ENOSYS under SunOS                          */
DECL|macro|__NR_getrlimit
mdefine_line|#define __NR_getrlimit&t;&t;144 /* Common                                      */
DECL|macro|__NR_setrlimit
mdefine_line|#define __NR_setrlimit          145 /* Common                                      */
DECL|macro|__NR_pivot_root
mdefine_line|#define __NR_pivot_root&t;&t;146 /* Linux Specific, killpg under SunOS          */
DECL|macro|__NR_prctl
mdefine_line|#define __NR_prctl&t;&t;147 /* ENOSYS under SunOS                          */
DECL|macro|__NR_pciconfig_read
mdefine_line|#define __NR_pciconfig_read&t;148 /* ENOSYS under SunOS                          */
DECL|macro|__NR_pciconfig_write
mdefine_line|#define __NR_pciconfig_write&t;149 /* ENOSYS under SunOS                          */
DECL|macro|__NR_getsockname
mdefine_line|#define __NR_getsockname        150 /* Common                                      */
multiline_comment|/* #define __NR_getmsg          151    SunOS Specific                              */
multiline_comment|/* #define __NR_putmsg          152    SunOS Specific                              */
DECL|macro|__NR_poll
mdefine_line|#define __NR_poll               153 /* Common                                      */
DECL|macro|__NR_getdents64
mdefine_line|#define __NR_getdents64&t;&t;154 /* Linux specific&t;&t;&t;&t;   */
multiline_comment|/* #define __NR_fcntl64         155    Linux sparc32 Specific                      */
multiline_comment|/* #define __NR_getdirentries   156    SunOS Specific                              */
DECL|macro|__NR_statfs
mdefine_line|#define __NR_statfs             157 /* Common                                      */
DECL|macro|__NR_fstatfs
mdefine_line|#define __NR_fstatfs            158 /* Common                                      */
DECL|macro|__NR_umount
mdefine_line|#define __NR_umount             159 /* Common                                      */
DECL|macro|__NR_sched_set_affinity
mdefine_line|#define __NR_sched_set_affinity 160 /* Linux specific, async_daemon under SunOS    */
DECL|macro|__NR_sched_get_affinity
mdefine_line|#define __NR_sched_get_affinity 161 /* Linux specific, getfh under SunOS           */
DECL|macro|__NR_getdomainname
mdefine_line|#define __NR_getdomainname      162 /* SunOS Specific                              */
DECL|macro|__NR_setdomainname
mdefine_line|#define __NR_setdomainname      163 /* Common                                      */
DECL|macro|__NR_utrap_install
mdefine_line|#define __NR_utrap_install&t;164 /* SYSV ABI/v9 required&t;&t;&t;   */
DECL|macro|__NR_quotactl
mdefine_line|#define __NR_quotactl           165 /* Common                                      */
DECL|macro|__NR_set_tid_address
mdefine_line|#define __NR_set_tid_address    166 /* Linux specific, exportfs under SunOS        */
DECL|macro|__NR_mount
mdefine_line|#define __NR_mount              167 /* Common                                      */
DECL|macro|__NR_ustat
mdefine_line|#define __NR_ustat              168 /* Common                                      */
DECL|macro|__NR_setxattr
mdefine_line|#define __NR_setxattr           169 /* SunOS: semsys                               */
DECL|macro|__NR_lsetxattr
mdefine_line|#define __NR_lsetxattr          170 /* SunOS: msgsys                               */
DECL|macro|__NR_fsetxattr
mdefine_line|#define __NR_fsetxattr          171 /* SunOS: shmsys                               */
DECL|macro|__NR_getxattr
mdefine_line|#define __NR_getxattr           172 /* SunOS: auditsys                             */
DECL|macro|__NR_lgetxattr
mdefine_line|#define __NR_lgetxattr          173 /* SunOS: rfssys                               */
DECL|macro|__NR_getdents
mdefine_line|#define __NR_getdents           174 /* Common                                      */
DECL|macro|__NR_setsid
mdefine_line|#define __NR_setsid             175 /* Common                                      */
DECL|macro|__NR_fchdir
mdefine_line|#define __NR_fchdir             176 /* Common                                      */
DECL|macro|__NR_fgetxattr
mdefine_line|#define __NR_fgetxattr          177 /* SunOS: fchroot                              */
DECL|macro|__NR_listxattr
mdefine_line|#define __NR_listxattr          178 /* SunOS: vpixsys                              */
DECL|macro|__NR_llistxattr
mdefine_line|#define __NR_llistxattr         179 /* SunOS: aioread                              */
DECL|macro|__NR_flistxattr
mdefine_line|#define __NR_flistxattr         180 /* SunOS: aiowrite                             */
DECL|macro|__NR_removexattr
mdefine_line|#define __NR_removexattr        181 /* SunOS: aiowait                              */
DECL|macro|__NR_lremovexattr
mdefine_line|#define __NR_lremovexattr       182 /* SunOS: aiocancel                            */
DECL|macro|__NR_sigpending
mdefine_line|#define __NR_sigpending         183 /* Common                                      */
DECL|macro|__NR_query_module
mdefine_line|#define __NR_query_module&t;184 /* Linux Specific&t;&t;&t;&t;   */
DECL|macro|__NR_setpgid
mdefine_line|#define __NR_setpgid            185 /* Common                                      */
DECL|macro|__NR_fremovexattr
mdefine_line|#define __NR_fremovexattr       186 /* SunOS: pathconf                             */
DECL|macro|__NR_tkill
mdefine_line|#define __NR_tkill              187 /* SunOS: fpathconf                            */
DECL|macro|__NR_exit_group
mdefine_line|#define __NR_exit_group&t;&t;188 /* Linux specific, sysconf undef SunOS         */
DECL|macro|__NR_uname
mdefine_line|#define __NR_uname              189 /* Linux Specific                              */
DECL|macro|__NR_init_module
mdefine_line|#define __NR_init_module        190 /* Linux Specific                              */
DECL|macro|__NR_personality
mdefine_line|#define __NR_personality        191 /* Linux Specific                              */
DECL|macro|__NR_remap_file_pages
mdefine_line|#define __NR_remap_file_pages   192 /* Linux Specific                              */
DECL|macro|__NR_epoll_create
mdefine_line|#define __NR_epoll_create       193 /* Linux Specific                              */
DECL|macro|__NR_epoll_ctl
mdefine_line|#define __NR_epoll_ctl          194 /* Linux Specific                              */
DECL|macro|__NR_epoll_wait
mdefine_line|#define __NR_epoll_wait         195 /* Linux Specific                              */
multiline_comment|/* #define __NR_ulimit          196    Linux Specific                              */
DECL|macro|__NR_getppid
mdefine_line|#define __NR_getppid            197 /* Linux Specific                              */
DECL|macro|__NR_sigaction
mdefine_line|#define __NR_sigaction          198 /* Linux Specific                              */
DECL|macro|__NR_sgetmask
mdefine_line|#define __NR_sgetmask           199 /* Linux Specific                              */
DECL|macro|__NR_ssetmask
mdefine_line|#define __NR_ssetmask           200 /* Linux Specific                              */
DECL|macro|__NR_sigsuspend
mdefine_line|#define __NR_sigsuspend         201 /* Linux Specific                              */
DECL|macro|__NR_oldlstat
mdefine_line|#define __NR_oldlstat           202 /* Linux Specific                              */
DECL|macro|__NR_uselib
mdefine_line|#define __NR_uselib             203 /* Linux Specific                              */
DECL|macro|__NR_readdir
mdefine_line|#define __NR_readdir            204 /* Linux Specific                              */
DECL|macro|__NR_readahead
mdefine_line|#define __NR_readahead          205 /* Linux Specific                              */
DECL|macro|__NR_socketcall
mdefine_line|#define __NR_socketcall         206 /* Linux Specific                              */
DECL|macro|__NR_syslog
mdefine_line|#define __NR_syslog             207 /* Linux Specific                              */
DECL|macro|__NR_lookup_dcookie
mdefine_line|#define __NR_lookup_dcookie     208 /* Linux Specific                              */
DECL|macro|__NR_fadvise64
mdefine_line|#define __NR_fadvise64          209 /* Linux Specific                              */
DECL|macro|__NR_fadvise64_64
mdefine_line|#define __NR_fadvise64_64       210 /* Linux Specific                              */
DECL|macro|__NR_tgkill
mdefine_line|#define __NR_tgkill             211 /* Linux Specific                              */
DECL|macro|__NR_waitpid
mdefine_line|#define __NR_waitpid            212 /* Linux Specific                              */
DECL|macro|__NR_swapoff
mdefine_line|#define __NR_swapoff            213 /* Linux Specific                              */
DECL|macro|__NR_sysinfo
mdefine_line|#define __NR_sysinfo            214 /* Linux Specific                              */
DECL|macro|__NR_ipc
mdefine_line|#define __NR_ipc                215 /* Linux Specific                              */
DECL|macro|__NR_sigreturn
mdefine_line|#define __NR_sigreturn          216 /* Linux Specific                              */
DECL|macro|__NR_clone
mdefine_line|#define __NR_clone              217 /* Linux Specific                              */
multiline_comment|/* #define __NR_modify_ldt      218    Linux Specific - i386 specific, unused      */
DECL|macro|__NR_adjtimex
mdefine_line|#define __NR_adjtimex           219 /* Linux Specific                              */
DECL|macro|__NR_sigprocmask
mdefine_line|#define __NR_sigprocmask        220 /* Linux Specific                              */
DECL|macro|__NR_create_module
mdefine_line|#define __NR_create_module      221 /* Linux Specific                              */
DECL|macro|__NR_delete_module
mdefine_line|#define __NR_delete_module      222 /* Linux Specific                              */
DECL|macro|__NR_get_kernel_syms
mdefine_line|#define __NR_get_kernel_syms    223 /* Linux Specific                              */
DECL|macro|__NR_getpgid
mdefine_line|#define __NR_getpgid            224 /* Linux Specific                              */
DECL|macro|__NR_bdflush
mdefine_line|#define __NR_bdflush            225 /* Linux Specific                              */
DECL|macro|__NR_sysfs
mdefine_line|#define __NR_sysfs              226 /* Linux Specific                              */
DECL|macro|__NR_afs_syscall
mdefine_line|#define __NR_afs_syscall        227 /* Linux Specific                              */
DECL|macro|__NR_setfsuid
mdefine_line|#define __NR_setfsuid           228 /* Linux Specific                              */
DECL|macro|__NR_setfsgid
mdefine_line|#define __NR_setfsgid           229 /* Linux Specific                              */
DECL|macro|__NR__newselect
mdefine_line|#define __NR__newselect         230 /* Linux Specific                              */
macro_line|#ifdef __KERNEL__
DECL|macro|__NR_time
mdefine_line|#define __NR_time&t;&t;231 /* Linux sparc32                               */
macro_line|#endif
multiline_comment|/* #define __NR_oldstat         232    Linux Specific                              */
DECL|macro|__NR_stime
mdefine_line|#define __NR_stime              233 /* Linux Specific                              */
DECL|macro|__NR_statfs64
mdefine_line|#define __NR_statfs64           234 /* Linux Specific                              */
DECL|macro|__NR_fstatfs64
mdefine_line|#define __NR_fstatfs64          235 /* Linux Specific                              */
DECL|macro|__NR__llseek
mdefine_line|#define __NR__llseek            236 /* Linux Specific                              */
DECL|macro|__NR_mlock
mdefine_line|#define __NR_mlock              237
DECL|macro|__NR_munlock
mdefine_line|#define __NR_munlock            238
DECL|macro|__NR_mlockall
mdefine_line|#define __NR_mlockall           239
DECL|macro|__NR_munlockall
mdefine_line|#define __NR_munlockall         240
DECL|macro|__NR_sched_setparam
mdefine_line|#define __NR_sched_setparam     241
DECL|macro|__NR_sched_getparam
mdefine_line|#define __NR_sched_getparam     242
DECL|macro|__NR_sched_setscheduler
mdefine_line|#define __NR_sched_setscheduler 243
DECL|macro|__NR_sched_getscheduler
mdefine_line|#define __NR_sched_getscheduler 244
DECL|macro|__NR_sched_yield
mdefine_line|#define __NR_sched_yield        245
DECL|macro|__NR_sched_get_priority_max
mdefine_line|#define __NR_sched_get_priority_max 246
DECL|macro|__NR_sched_get_priority_min
mdefine_line|#define __NR_sched_get_priority_min 247
DECL|macro|__NR_sched_rr_get_interval
mdefine_line|#define __NR_sched_rr_get_interval  248
DECL|macro|__NR_nanosleep
mdefine_line|#define __NR_nanosleep          249
DECL|macro|__NR_mremap
mdefine_line|#define __NR_mremap             250
DECL|macro|__NR__sysctl
mdefine_line|#define __NR__sysctl            251
DECL|macro|__NR_getsid
mdefine_line|#define __NR_getsid             252
DECL|macro|__NR_fdatasync
mdefine_line|#define __NR_fdatasync          253
DECL|macro|__NR_nfsservctl
mdefine_line|#define __NR_nfsservctl         254
DECL|macro|__NR_aplib
mdefine_line|#define __NR_aplib              255
DECL|macro|__NR_clock_settime
mdefine_line|#define __NR_clock_settime&t;256
DECL|macro|__NR_clock_gettime
mdefine_line|#define __NR_clock_gettime&t;257
DECL|macro|__NR_clock_getres
mdefine_line|#define __NR_clock_getres&t;258
DECL|macro|__NR_clock_nanosleep
mdefine_line|#define __NR_clock_nanosleep&t;259
DECL|macro|__NR_sched_getaffinity
mdefine_line|#define __NR_sched_getaffinity&t;260
DECL|macro|__NR_sched_setaffinity
mdefine_line|#define __NR_sched_setaffinity&t;261
DECL|macro|__NR_timer_settime
mdefine_line|#define __NR_timer_settime&t;262
DECL|macro|__NR_timer_gettime
mdefine_line|#define __NR_timer_gettime&t;263
DECL|macro|__NR_timer_getoverrun
mdefine_line|#define __NR_timer_getoverrun&t;264
DECL|macro|__NR_timer_delete
mdefine_line|#define __NR_timer_delete&t;265
DECL|macro|__NR_timer_create
mdefine_line|#define __NR_timer_create&t;266
multiline_comment|/* #define __NR_vserver&t;&t;267 Reserved for VSERVER */
multiline_comment|/* WARNING: You MAY NOT add syscall numbers larger than 267, since&n; *          all of the syscall tables in the Sparc kernel are&n; *          sized to have 267 entries (starting at zero).  Therefore&n; *          find a free slot in the 0-266 range.&n; */
DECL|macro|_syscall0
mdefine_line|#define _syscall0(type,name) &bslash;&n;type name(void) &bslash;&n;{ &bslash;&n;long __res; &bslash;&n;register long __g1 __asm__ (&quot;g1&quot;) = __NR_##name; &bslash;&n;__asm__ __volatile__ (&quot;t 0x6d&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;      &quot;sub %%g0, %%o0, %0&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;      &quot;movcc %%xcc, %%o0, %0&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;      : &quot;=r&quot; (__res)&bslash;&n;&t;&t;      : &quot;r&quot; (__g1) &bslash;&n;&t;&t;      : &quot;o0&quot;, &quot;cc&quot;); &bslash;&n;if (__res &gt;= 0) &bslash;&n;    return (type) __res; &bslash;&n;errno = -__res; &bslash;&n;return -1; &bslash;&n;}
DECL|macro|_syscall1
mdefine_line|#define _syscall1(type,name,type1,arg1) &bslash;&n;type name(type1 arg1) &bslash;&n;{ &bslash;&n;long __res; &bslash;&n;register long __g1 __asm__ (&quot;g1&quot;) = __NR_##name; &bslash;&n;register long __o0 __asm__ (&quot;o0&quot;) = (long)(arg1); &bslash;&n;__asm__ __volatile__ (&quot;t 0x6d&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;      &quot;sub %%g0, %%o0, %0&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;      &quot;movcc %%xcc, %%o0, %0&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;      : &quot;=r&quot; (__res), &quot;=&amp;r&quot; (__o0) &bslash;&n;&t;&t;      : &quot;1&quot; (__o0), &quot;r&quot; (__g1) &bslash;&n;&t;&t;      : &quot;cc&quot;); &bslash;&n;if (__res &gt;= 0) &bslash;&n;&t;return (type) __res; &bslash;&n;errno = -__res; &bslash;&n;return -1; &bslash;&n;}
DECL|macro|_syscall2
mdefine_line|#define _syscall2(type,name,type1,arg1,type2,arg2) &bslash;&n;type name(type1 arg1,type2 arg2) &bslash;&n;{ &bslash;&n;long __res; &bslash;&n;register long __g1 __asm__ (&quot;g1&quot;) = __NR_##name; &bslash;&n;register long __o0 __asm__ (&quot;o0&quot;) = (long)(arg1); &bslash;&n;register long __o1 __asm__ (&quot;o1&quot;) = (long)(arg2); &bslash;&n;__asm__ __volatile__ (&quot;t 0x6d&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;      &quot;sub %%g0, %%o0, %0&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;      &quot;movcc %%xcc, %%o0, %0&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;      : &quot;=r&quot; (__res), &quot;=&amp;r&quot; (__o0) &bslash;&n;&t;&t;      : &quot;1&quot; (__o0), &quot;r&quot; (__o1), &quot;r&quot; (__g1) &bslash;&n;&t;&t;      : &quot;cc&quot;); &bslash;&n;if (__res &gt;= 0) &bslash;&n;&t;return (type) __res; &bslash;&n;errno = -__res; &bslash;&n;return -1; &bslash;&n;}
DECL|macro|_syscall3
mdefine_line|#define _syscall3(type,name,type1,arg1,type2,arg2,type3,arg3) &bslash;&n;type name(type1 arg1,type2 arg2,type3 arg3) &bslash;&n;{ &bslash;&n;long __res; &bslash;&n;register long __g1 __asm__ (&quot;g1&quot;) = __NR_##name; &bslash;&n;register long __o0 __asm__ (&quot;o0&quot;) = (long)(arg1); &bslash;&n;register long __o1 __asm__ (&quot;o1&quot;) = (long)(arg2); &bslash;&n;register long __o2 __asm__ (&quot;o2&quot;) = (long)(arg3); &bslash;&n;__asm__ __volatile__ (&quot;t 0x6d&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;      &quot;sub %%g0, %%o0, %0&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;      &quot;movcc %%xcc, %%o0, %0&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;      : &quot;=r&quot; (__res), &quot;=&amp;r&quot; (__o0) &bslash;&n;&t;&t;      : &quot;1&quot; (__o0), &quot;r&quot; (__o1), &quot;r&quot; (__o2), &quot;r&quot; (__g1) &bslash;&n;&t;&t;      : &quot;cc&quot;); &bslash;&n;if (__res&gt;=0) &bslash;&n;&t;return (type) __res; &bslash;&n;errno = -__res; &bslash;&n;return -1; &bslash;&n;}
DECL|macro|_syscall4
mdefine_line|#define _syscall4(type,name,type1,arg1,type2,arg2,type3,arg3,type4,arg4) &bslash;&n;type name (type1 arg1, type2 arg2, type3 arg3, type4 arg4) &bslash;&n;{ &bslash;&n;long __res; &bslash;&n;register long __g1 __asm__ (&quot;g1&quot;) = __NR_##name; &bslash;&n;register long __o0 __asm__ (&quot;o0&quot;) = (long)(arg1); &bslash;&n;register long __o1 __asm__ (&quot;o1&quot;) = (long)(arg2); &bslash;&n;register long __o2 __asm__ (&quot;o2&quot;) = (long)(arg3); &bslash;&n;register long __o3 __asm__ (&quot;o3&quot;) = (long)(arg4); &bslash;&n;__asm__ __volatile__ (&quot;t 0x6d&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;      &quot;sub %%g0, %%o0, %0&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;      &quot;movcc %%xcc, %%o0, %0&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;      : &quot;=r&quot; (__res), &quot;=&amp;r&quot; (__o0) &bslash;&n;&t;&t;      : &quot;1&quot; (__o0), &quot;r&quot; (__o1), &quot;r&quot; (__o2), &quot;r&quot; (__o3), &quot;r&quot; (__g1) &bslash;&n;&t;&t;      : &quot;cc&quot;); &bslash;&n;if (__res&gt;=0) &bslash;&n;&t;return (type) __res; &bslash;&n;errno = -__res; &bslash;&n;return -1; &bslash;&n;} 
DECL|macro|_syscall5
mdefine_line|#define _syscall5(type,name,type1,arg1,type2,arg2,type3,arg3,type4,arg4, &bslash;&n;&t;  type5,arg5) &bslash;&n;type name (type1 arg1,type2 arg2,type3 arg3,type4 arg4,type5 arg5) &bslash;&n;{ &bslash;&n;long __res; &bslash;&n;register long __g1 __asm__ (&quot;g1&quot;) = __NR_##name; &bslash;&n;register long __o0 __asm__ (&quot;o0&quot;) = (long)(arg1); &bslash;&n;register long __o1 __asm__ (&quot;o1&quot;) = (long)(arg2); &bslash;&n;register long __o2 __asm__ (&quot;o2&quot;) = (long)(arg3); &bslash;&n;register long __o3 __asm__ (&quot;o3&quot;) = (long)(arg4); &bslash;&n;register long __o4 __asm__ (&quot;o4&quot;) = (long)(arg5); &bslash;&n;__asm__ __volatile__ (&quot;t 0x6d&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;      &quot;sub %%g0, %%o0, %0&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;      &quot;movcc %%xcc, %%o0, %0&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;      : &quot;=r&quot; (__res), &quot;=&amp;r&quot; (__o0) &bslash;&n;&t;&t;      : &quot;1&quot; (__o0), &quot;r&quot; (__o1), &quot;r&quot; (__o2), &quot;r&quot; (__o3), &quot;r&quot; (__o4), &quot;r&quot; (__g1) &bslash;&n;&t;&t;      : &quot;cc&quot;); &bslash;&n;if (__res&gt;=0) &bslash;&n;&t;return (type) __res; &bslash;&n;errno = -__res; &bslash;&n;return -1; &bslash;&n;}
macro_line|#ifdef __KERNEL_SYSCALLS__
multiline_comment|/*&n; * we need this inline - forking from kernel space will result&n; * in NO COPY ON WRITE (!!!), until an execve is executed. This&n; * is no problem, but for the stack. This is handled by not letting&n; * main() use the stack at all after fork(). Thus, no function&n; * calls - which means inline code for fork too, as otherwise we&n; * would use the stack upon exit from &squot;fork()&squot;.&n; *&n; * Actually only pause and fork are needed inline, so that there&n; * won&squot;t be any messing with the stack from main(), but we define&n; * some others too.&n; */
DECL|macro|__NR__exit
mdefine_line|#define __NR__exit __NR_exit
r_static
id|__inline__
id|_syscall0
c_func
(paren
id|pid_t
comma
id|setsid
)paren
r_static
id|__inline__
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
id|__const__
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
id|__inline__
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
id|__inline__
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
id|__inline__
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
id|__inline__
id|_syscall3
c_func
(paren
r_int
comma
id|execve
comma
id|__const__
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
id|__inline__
id|_syscall3
c_func
(paren
r_int
comma
id|open
comma
id|__const__
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
id|__inline__
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
id|__inline__
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
id|__inline__
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
macro_line|#endif /* __KERNEL_SYSCALLS__ */
macro_line|#ifdef __KERNEL__
multiline_comment|/* sysconf options, for SunOS compatibility */
DECL|macro|_SC_ARG_MAX
mdefine_line|#define   _SC_ARG_MAX             1
DECL|macro|_SC_CHILD_MAX
mdefine_line|#define   _SC_CHILD_MAX           2
DECL|macro|_SC_CLK_TCK
mdefine_line|#define   _SC_CLK_TCK             3
DECL|macro|_SC_NGROUPS_MAX
mdefine_line|#define   _SC_NGROUPS_MAX         4
DECL|macro|_SC_OPEN_MAX
mdefine_line|#define   _SC_OPEN_MAX            5
DECL|macro|_SC_JOB_CONTROL
mdefine_line|#define   _SC_JOB_CONTROL         6
DECL|macro|_SC_SAVED_IDS
mdefine_line|#define   _SC_SAVED_IDS           7
DECL|macro|_SC_VERSION
mdefine_line|#define   _SC_VERSION             8
macro_line|#endif
multiline_comment|/*&n; * &quot;Conditional&quot; syscalls&n; *&n; * What we want is __attribute__((weak,alias(&quot;sys_ni_syscall&quot;))),&n; * but it doesn&squot;t work on all toolchains, so we just do it by hand&n; */
DECL|macro|cond_syscall
mdefine_line|#define cond_syscall(x) asm(&quot;.weak&bslash;t&quot; #x &quot;&bslash;n&bslash;t.set&bslash;t&quot; #x &quot;,sys_ni_syscall&quot;);
macro_line|#endif /* _SPARC64_UNISTD_H */
eof
