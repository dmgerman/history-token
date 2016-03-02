macro_line|#ifndef _ASM_X86_64_UNISTD_H_
DECL|macro|_ASM_X86_64_UNISTD_H_
mdefine_line|#define _ASM_X86_64_UNISTD_H_
macro_line|#ifndef __SYSCALL
DECL|macro|__SYSCALL
mdefine_line|#define __SYSCALL(a,b) 
macro_line|#endif
multiline_comment|/*&n; * This file contains the system call numbers.&n; * &n; * Note: holes are not allowed.&n; */
multiline_comment|/* at least 8 syscall per cacheline */
DECL|macro|__NR_read
mdefine_line|#define __NR_read                                0
id|__SYSCALL
c_func
(paren
id|__NR_read
comma
id|sys_read
)paren
DECL|macro|__NR_write
mdefine_line|#define __NR_write                               1
id|__SYSCALL
c_func
(paren
id|__NR_write
comma
id|sys_write
)paren
DECL|macro|__NR_open
mdefine_line|#define __NR_open                                2
id|__SYSCALL
c_func
(paren
id|__NR_open
comma
id|sys_open
)paren
DECL|macro|__NR_close
mdefine_line|#define __NR_close                               3
id|__SYSCALL
c_func
(paren
id|__NR_close
comma
id|sys_close
)paren
DECL|macro|__NR_stat
mdefine_line|#define __NR_stat                                4
id|__SYSCALL
c_func
(paren
id|__NR_stat
comma
id|sys_newstat
)paren
DECL|macro|__NR_fstat
mdefine_line|#define __NR_fstat                               5
id|__SYSCALL
c_func
(paren
id|__NR_fstat
comma
id|sys_newfstat
)paren
DECL|macro|__NR_lstat
mdefine_line|#define __NR_lstat                               6
id|__SYSCALL
c_func
(paren
id|__NR_lstat
comma
id|sys_newlstat
)paren
DECL|macro|__NR_poll
mdefine_line|#define __NR_poll                                7
id|__SYSCALL
c_func
(paren
id|__NR_poll
comma
id|sys_poll
)paren
DECL|macro|__NR_lseek
mdefine_line|#define __NR_lseek                               8
id|__SYSCALL
c_func
(paren
id|__NR_lseek
comma
id|sys_lseek
)paren
DECL|macro|__NR_mmap
mdefine_line|#define __NR_mmap                                9
id|__SYSCALL
c_func
(paren
id|__NR_mmap
comma
id|sys_mmap
)paren
DECL|macro|__NR_mprotect
mdefine_line|#define __NR_mprotect                           10
id|__SYSCALL
c_func
(paren
id|__NR_mprotect
comma
id|sys_mprotect
)paren
DECL|macro|__NR_munmap
mdefine_line|#define __NR_munmap                             11
id|__SYSCALL
c_func
(paren
id|__NR_munmap
comma
id|sys_munmap
)paren
DECL|macro|__NR_brk
mdefine_line|#define __NR_brk                                12
id|__SYSCALL
c_func
(paren
id|__NR_brk
comma
id|sys_brk
)paren
DECL|macro|__NR_rt_sigaction
mdefine_line|#define __NR_rt_sigaction                       13
id|__SYSCALL
c_func
(paren
id|__NR_rt_sigaction
comma
id|sys_rt_sigaction
)paren
DECL|macro|__NR_rt_sigprocmask
mdefine_line|#define __NR_rt_sigprocmask                     14
id|__SYSCALL
c_func
(paren
id|__NR_rt_sigprocmask
comma
id|sys_rt_sigprocmask
)paren
DECL|macro|__NR_rt_sigreturn
mdefine_line|#define __NR_rt_sigreturn                       15
id|__SYSCALL
c_func
(paren
id|__NR_rt_sigreturn
comma
id|stub_rt_sigreturn
)paren
DECL|macro|__NR_ioctl
mdefine_line|#define __NR_ioctl                              16
id|__SYSCALL
c_func
(paren
id|__NR_ioctl
comma
id|sys_ioctl
)paren
DECL|macro|__NR_pread64
mdefine_line|#define __NR_pread64                            17
id|__SYSCALL
c_func
(paren
id|__NR_pread64
comma
id|sys_pread64
)paren
DECL|macro|__NR_pwrite64
mdefine_line|#define __NR_pwrite64                           18
id|__SYSCALL
c_func
(paren
id|__NR_pwrite64
comma
id|sys_pwrite64
)paren
DECL|macro|__NR_readv
mdefine_line|#define __NR_readv                              19
id|__SYSCALL
c_func
(paren
id|__NR_readv
comma
id|sys_readv
)paren
DECL|macro|__NR_writev
mdefine_line|#define __NR_writev                             20
id|__SYSCALL
c_func
(paren
id|__NR_writev
comma
id|sys_writev
)paren
DECL|macro|__NR_access
mdefine_line|#define __NR_access                             21
id|__SYSCALL
c_func
(paren
id|__NR_access
comma
id|sys_access
)paren
DECL|macro|__NR_pipe
mdefine_line|#define __NR_pipe                               22
id|__SYSCALL
c_func
(paren
id|__NR_pipe
comma
id|sys_pipe
)paren
DECL|macro|__NR_select
mdefine_line|#define __NR_select                             23
id|__SYSCALL
c_func
(paren
id|__NR_select
comma
id|sys_select
)paren
DECL|macro|__NR_sched_yield
mdefine_line|#define __NR_sched_yield                        24
id|__SYSCALL
c_func
(paren
id|__NR_sched_yield
comma
id|sys_sched_yield
)paren
DECL|macro|__NR_mremap
mdefine_line|#define __NR_mremap                             25
id|__SYSCALL
c_func
(paren
id|__NR_mremap
comma
id|sys_mremap
)paren
DECL|macro|__NR_msync
mdefine_line|#define __NR_msync                              26
id|__SYSCALL
c_func
(paren
id|__NR_msync
comma
id|sys_msync
)paren
DECL|macro|__NR_mincore
mdefine_line|#define __NR_mincore                            27
id|__SYSCALL
c_func
(paren
id|__NR_mincore
comma
id|sys_mincore
)paren
DECL|macro|__NR_madvise
mdefine_line|#define __NR_madvise                            28
id|__SYSCALL
c_func
(paren
id|__NR_madvise
comma
id|sys_madvise
)paren
DECL|macro|__NR_shmget
mdefine_line|#define __NR_shmget                             29
id|__SYSCALL
c_func
(paren
id|__NR_shmget
comma
id|sys_shmget
)paren
DECL|macro|__NR_shmat
mdefine_line|#define __NR_shmat                              30
id|__SYSCALL
c_func
(paren
id|__NR_shmat
comma
id|wrap_sys_shmat
)paren
DECL|macro|__NR_shmctl
mdefine_line|#define __NR_shmctl                             31
id|__SYSCALL
c_func
(paren
id|__NR_shmctl
comma
id|sys_shmctl
)paren
DECL|macro|__NR_dup
mdefine_line|#define __NR_dup                                32
id|__SYSCALL
c_func
(paren
id|__NR_dup
comma
id|sys_dup
)paren
DECL|macro|__NR_dup2
mdefine_line|#define __NR_dup2                               33
id|__SYSCALL
c_func
(paren
id|__NR_dup2
comma
id|sys_dup2
)paren
DECL|macro|__NR_pause
mdefine_line|#define __NR_pause                              34
id|__SYSCALL
c_func
(paren
id|__NR_pause
comma
id|sys_pause
)paren
DECL|macro|__NR_nanosleep
mdefine_line|#define __NR_nanosleep                          35
id|__SYSCALL
c_func
(paren
id|__NR_nanosleep
comma
id|sys_nanosleep
)paren
DECL|macro|__NR_getitimer
mdefine_line|#define __NR_getitimer                          36
id|__SYSCALL
c_func
(paren
id|__NR_getitimer
comma
id|sys_getitimer
)paren
DECL|macro|__NR_alarm
mdefine_line|#define __NR_alarm                              37
id|__SYSCALL
c_func
(paren
id|__NR_alarm
comma
id|sys_alarm
)paren
DECL|macro|__NR_setitimer
mdefine_line|#define __NR_setitimer                          38
id|__SYSCALL
c_func
(paren
id|__NR_setitimer
comma
id|sys_setitimer
)paren
DECL|macro|__NR_getpid
mdefine_line|#define __NR_getpid                             39
id|__SYSCALL
c_func
(paren
id|__NR_getpid
comma
id|sys_getpid
)paren
DECL|macro|__NR_sendfile
mdefine_line|#define __NR_sendfile                           40
id|__SYSCALL
c_func
(paren
id|__NR_sendfile
comma
id|sys_sendfile64
)paren
DECL|macro|__NR_socket
mdefine_line|#define __NR_socket                             41
id|__SYSCALL
c_func
(paren
id|__NR_socket
comma
id|sys_socket
)paren
DECL|macro|__NR_connect
mdefine_line|#define __NR_connect                            42
id|__SYSCALL
c_func
(paren
id|__NR_connect
comma
id|sys_connect
)paren
DECL|macro|__NR_accept
mdefine_line|#define __NR_accept                             43
id|__SYSCALL
c_func
(paren
id|__NR_accept
comma
id|sys_accept
)paren
DECL|macro|__NR_sendto
mdefine_line|#define __NR_sendto                             44
id|__SYSCALL
c_func
(paren
id|__NR_sendto
comma
id|sys_sendto
)paren
DECL|macro|__NR_recvfrom
mdefine_line|#define __NR_recvfrom                           45
id|__SYSCALL
c_func
(paren
id|__NR_recvfrom
comma
id|sys_recvfrom
)paren
DECL|macro|__NR_sendmsg
mdefine_line|#define __NR_sendmsg                            46
id|__SYSCALL
c_func
(paren
id|__NR_sendmsg
comma
id|sys_sendmsg
)paren
DECL|macro|__NR_recvmsg
mdefine_line|#define __NR_recvmsg                            47
id|__SYSCALL
c_func
(paren
id|__NR_recvmsg
comma
id|sys_recvmsg
)paren
DECL|macro|__NR_shutdown
mdefine_line|#define __NR_shutdown                           48
id|__SYSCALL
c_func
(paren
id|__NR_shutdown
comma
id|sys_shutdown
)paren
DECL|macro|__NR_bind
mdefine_line|#define __NR_bind                               49
id|__SYSCALL
c_func
(paren
id|__NR_bind
comma
id|sys_bind
)paren
DECL|macro|__NR_listen
mdefine_line|#define __NR_listen                             50
id|__SYSCALL
c_func
(paren
id|__NR_listen
comma
id|sys_listen
)paren
DECL|macro|__NR_getsockname
mdefine_line|#define __NR_getsockname                        51
id|__SYSCALL
c_func
(paren
id|__NR_getsockname
comma
id|sys_getsockname
)paren
DECL|macro|__NR_getpeername
mdefine_line|#define __NR_getpeername                        52
id|__SYSCALL
c_func
(paren
id|__NR_getpeername
comma
id|sys_getpeername
)paren
DECL|macro|__NR_socketpair
mdefine_line|#define __NR_socketpair                         53
id|__SYSCALL
c_func
(paren
id|__NR_socketpair
comma
id|sys_socketpair
)paren
DECL|macro|__NR_setsockopt
mdefine_line|#define __NR_setsockopt                         54
id|__SYSCALL
c_func
(paren
id|__NR_setsockopt
comma
id|sys_setsockopt
)paren
DECL|macro|__NR_getsockopt
mdefine_line|#define __NR_getsockopt                         55
id|__SYSCALL
c_func
(paren
id|__NR_getsockopt
comma
id|sys_getsockopt
)paren
DECL|macro|__NR_clone
mdefine_line|#define __NR_clone                              56
id|__SYSCALL
c_func
(paren
id|__NR_clone
comma
id|stub_clone
)paren
DECL|macro|__NR_fork
mdefine_line|#define __NR_fork                               57
id|__SYSCALL
c_func
(paren
id|__NR_fork
comma
id|stub_fork
)paren
DECL|macro|__NR_vfork
mdefine_line|#define __NR_vfork                              58
id|__SYSCALL
c_func
(paren
id|__NR_vfork
comma
id|stub_vfork
)paren
DECL|macro|__NR_execve
mdefine_line|#define __NR_execve                             59
id|__SYSCALL
c_func
(paren
id|__NR_execve
comma
id|stub_execve
)paren
DECL|macro|__NR_exit
mdefine_line|#define __NR_exit                               60
id|__SYSCALL
c_func
(paren
id|__NR_exit
comma
id|sys_exit
)paren
DECL|macro|__NR_wait4
mdefine_line|#define __NR_wait4                              61
id|__SYSCALL
c_func
(paren
id|__NR_wait4
comma
id|sys_wait4
)paren
DECL|macro|__NR_kill
mdefine_line|#define __NR_kill                               62
id|__SYSCALL
c_func
(paren
id|__NR_kill
comma
id|sys_kill
)paren
DECL|macro|__NR_uname
mdefine_line|#define __NR_uname                              63
id|__SYSCALL
c_func
(paren
id|__NR_uname
comma
id|sys_uname
)paren
DECL|macro|__NR_semget
mdefine_line|#define __NR_semget                             64
id|__SYSCALL
c_func
(paren
id|__NR_semget
comma
id|sys_semget
)paren
DECL|macro|__NR_semop
mdefine_line|#define __NR_semop                              65
id|__SYSCALL
c_func
(paren
id|__NR_semop
comma
id|sys_semop
)paren
DECL|macro|__NR_semctl
mdefine_line|#define __NR_semctl                             66
id|__SYSCALL
c_func
(paren
id|__NR_semctl
comma
id|sys_semctl
)paren
DECL|macro|__NR_shmdt
mdefine_line|#define __NR_shmdt                              67
id|__SYSCALL
c_func
(paren
id|__NR_shmdt
comma
id|sys_shmdt
)paren
DECL|macro|__NR_msgget
mdefine_line|#define __NR_msgget                             68
id|__SYSCALL
c_func
(paren
id|__NR_msgget
comma
id|sys_msgget
)paren
DECL|macro|__NR_msgsnd
mdefine_line|#define __NR_msgsnd                             69
id|__SYSCALL
c_func
(paren
id|__NR_msgsnd
comma
id|sys_msgsnd
)paren
DECL|macro|__NR_msgrcv
mdefine_line|#define __NR_msgrcv                             70
id|__SYSCALL
c_func
(paren
id|__NR_msgrcv
comma
id|sys_msgrcv
)paren
DECL|macro|__NR_msgctl
mdefine_line|#define __NR_msgctl                             71
id|__SYSCALL
c_func
(paren
id|__NR_msgctl
comma
id|sys_msgctl
)paren
DECL|macro|__NR_fcntl
mdefine_line|#define __NR_fcntl                              72
id|__SYSCALL
c_func
(paren
id|__NR_fcntl
comma
id|sys_fcntl
)paren
DECL|macro|__NR_flock
mdefine_line|#define __NR_flock                              73
id|__SYSCALL
c_func
(paren
id|__NR_flock
comma
id|sys_flock
)paren
DECL|macro|__NR_fsync
mdefine_line|#define __NR_fsync                              74
id|__SYSCALL
c_func
(paren
id|__NR_fsync
comma
id|sys_fsync
)paren
DECL|macro|__NR_fdatasync
mdefine_line|#define __NR_fdatasync                          75
id|__SYSCALL
c_func
(paren
id|__NR_fdatasync
comma
id|sys_fdatasync
)paren
DECL|macro|__NR_truncate
mdefine_line|#define __NR_truncate                           76
id|__SYSCALL
c_func
(paren
id|__NR_truncate
comma
id|sys_truncate
)paren
DECL|macro|__NR_ftruncate
mdefine_line|#define __NR_ftruncate                          77
id|__SYSCALL
c_func
(paren
id|__NR_ftruncate
comma
id|sys_ftruncate
)paren
DECL|macro|__NR_getdents
mdefine_line|#define __NR_getdents                           78
id|__SYSCALL
c_func
(paren
id|__NR_getdents
comma
id|sys_getdents
)paren
DECL|macro|__NR_getcwd
mdefine_line|#define __NR_getcwd                             79
id|__SYSCALL
c_func
(paren
id|__NR_getcwd
comma
id|sys_getcwd
)paren
DECL|macro|__NR_chdir
mdefine_line|#define __NR_chdir                              80
id|__SYSCALL
c_func
(paren
id|__NR_chdir
comma
id|sys_chdir
)paren
DECL|macro|__NR_fchdir
mdefine_line|#define __NR_fchdir                             81
id|__SYSCALL
c_func
(paren
id|__NR_fchdir
comma
id|sys_fchdir
)paren
DECL|macro|__NR_rename
mdefine_line|#define __NR_rename                             82
id|__SYSCALL
c_func
(paren
id|__NR_rename
comma
id|sys_rename
)paren
DECL|macro|__NR_mkdir
mdefine_line|#define __NR_mkdir                              83
id|__SYSCALL
c_func
(paren
id|__NR_mkdir
comma
id|sys_mkdir
)paren
DECL|macro|__NR_rmdir
mdefine_line|#define __NR_rmdir                              84
id|__SYSCALL
c_func
(paren
id|__NR_rmdir
comma
id|sys_rmdir
)paren
DECL|macro|__NR_creat
mdefine_line|#define __NR_creat                              85
id|__SYSCALL
c_func
(paren
id|__NR_creat
comma
id|sys_creat
)paren
DECL|macro|__NR_link
mdefine_line|#define __NR_link                               86
id|__SYSCALL
c_func
(paren
id|__NR_link
comma
id|sys_link
)paren
DECL|macro|__NR_unlink
mdefine_line|#define __NR_unlink                             87
id|__SYSCALL
c_func
(paren
id|__NR_unlink
comma
id|sys_unlink
)paren
DECL|macro|__NR_symlink
mdefine_line|#define __NR_symlink                            88
id|__SYSCALL
c_func
(paren
id|__NR_symlink
comma
id|sys_symlink
)paren
DECL|macro|__NR_readlink
mdefine_line|#define __NR_readlink                           89
id|__SYSCALL
c_func
(paren
id|__NR_readlink
comma
id|sys_readlink
)paren
DECL|macro|__NR_chmod
mdefine_line|#define __NR_chmod                              90
id|__SYSCALL
c_func
(paren
id|__NR_chmod
comma
id|sys_chmod
)paren
DECL|macro|__NR_fchmod
mdefine_line|#define __NR_fchmod                             91
id|__SYSCALL
c_func
(paren
id|__NR_fchmod
comma
id|sys_fchmod
)paren
DECL|macro|__NR_chown
mdefine_line|#define __NR_chown                              92
id|__SYSCALL
c_func
(paren
id|__NR_chown
comma
id|sys_chown
)paren
DECL|macro|__NR_fchown
mdefine_line|#define __NR_fchown                             93
id|__SYSCALL
c_func
(paren
id|__NR_fchown
comma
id|sys_fchown
)paren
DECL|macro|__NR_lchown
mdefine_line|#define __NR_lchown                             94
id|__SYSCALL
c_func
(paren
id|__NR_lchown
comma
id|sys_lchown
)paren
DECL|macro|__NR_umask
mdefine_line|#define __NR_umask                              95
id|__SYSCALL
c_func
(paren
id|__NR_umask
comma
id|sys_umask
)paren
DECL|macro|__NR_gettimeofday
mdefine_line|#define __NR_gettimeofday                       96
id|__SYSCALL
c_func
(paren
id|__NR_gettimeofday
comma
id|sys_gettimeofday
)paren
DECL|macro|__NR_getrlimit
mdefine_line|#define __NR_getrlimit                          97
id|__SYSCALL
c_func
(paren
id|__NR_getrlimit
comma
id|sys_getrlimit
)paren
DECL|macro|__NR_getrusage
mdefine_line|#define __NR_getrusage                          98
id|__SYSCALL
c_func
(paren
id|__NR_getrusage
comma
id|sys_getrusage
)paren
DECL|macro|__NR_sysinfo
mdefine_line|#define __NR_sysinfo                            99
id|__SYSCALL
c_func
(paren
id|__NR_sysinfo
comma
id|sys_sysinfo
)paren
DECL|macro|__NR_times
mdefine_line|#define __NR_times                             100
id|__SYSCALL
c_func
(paren
id|__NR_times
comma
id|sys_times
)paren
DECL|macro|__NR_ptrace
mdefine_line|#define __NR_ptrace                            101
id|__SYSCALL
c_func
(paren
id|__NR_ptrace
comma
id|sys_ptrace
)paren
DECL|macro|__NR_getuid
mdefine_line|#define __NR_getuid                            102
id|__SYSCALL
c_func
(paren
id|__NR_getuid
comma
id|sys_getuid
)paren
DECL|macro|__NR_syslog
mdefine_line|#define __NR_syslog                            103
id|__SYSCALL
c_func
(paren
id|__NR_syslog
comma
id|sys_syslog
)paren
multiline_comment|/* at the very end the stuff that never runs during the benchmarks */
DECL|macro|__NR_getgid
mdefine_line|#define __NR_getgid                            104
id|__SYSCALL
c_func
(paren
id|__NR_getgid
comma
id|sys_getgid
)paren
DECL|macro|__NR_setuid
mdefine_line|#define __NR_setuid                            105
id|__SYSCALL
c_func
(paren
id|__NR_setuid
comma
id|sys_setuid
)paren
DECL|macro|__NR_setgid
mdefine_line|#define __NR_setgid                            106
id|__SYSCALL
c_func
(paren
id|__NR_setgid
comma
id|sys_setgid
)paren
DECL|macro|__NR_geteuid
mdefine_line|#define __NR_geteuid                           107
id|__SYSCALL
c_func
(paren
id|__NR_geteuid
comma
id|sys_geteuid
)paren
DECL|macro|__NR_getegid
mdefine_line|#define __NR_getegid                           108
id|__SYSCALL
c_func
(paren
id|__NR_getegid
comma
id|sys_getegid
)paren
DECL|macro|__NR_setpgid
mdefine_line|#define __NR_setpgid                           109
id|__SYSCALL
c_func
(paren
id|__NR_setpgid
comma
id|sys_setpgid
)paren
DECL|macro|__NR_getppid
mdefine_line|#define __NR_getppid                           110
id|__SYSCALL
c_func
(paren
id|__NR_getppid
comma
id|sys_getppid
)paren
DECL|macro|__NR_getpgrp
mdefine_line|#define __NR_getpgrp                           111
id|__SYSCALL
c_func
(paren
id|__NR_getpgrp
comma
id|sys_getpgrp
)paren
DECL|macro|__NR_setsid
mdefine_line|#define __NR_setsid                            112
id|__SYSCALL
c_func
(paren
id|__NR_setsid
comma
id|sys_setsid
)paren
DECL|macro|__NR_setreuid
mdefine_line|#define __NR_setreuid                          113
id|__SYSCALL
c_func
(paren
id|__NR_setreuid
comma
id|sys_setreuid
)paren
DECL|macro|__NR_setregid
mdefine_line|#define __NR_setregid                          114
id|__SYSCALL
c_func
(paren
id|__NR_setregid
comma
id|sys_setregid
)paren
DECL|macro|__NR_getgroups
mdefine_line|#define __NR_getgroups                         115
id|__SYSCALL
c_func
(paren
id|__NR_getgroups
comma
id|sys_getgroups
)paren
DECL|macro|__NR_setgroups
mdefine_line|#define __NR_setgroups                         116
id|__SYSCALL
c_func
(paren
id|__NR_setgroups
comma
id|sys_setgroups
)paren
DECL|macro|__NR_setresuid
mdefine_line|#define __NR_setresuid                         117
id|__SYSCALL
c_func
(paren
id|__NR_setresuid
comma
id|sys_setresuid
)paren
DECL|macro|__NR_getresuid
mdefine_line|#define __NR_getresuid                         118
id|__SYSCALL
c_func
(paren
id|__NR_getresuid
comma
id|sys_getresuid
)paren
DECL|macro|__NR_setresgid
mdefine_line|#define __NR_setresgid                         119
id|__SYSCALL
c_func
(paren
id|__NR_setresgid
comma
id|sys_setresgid
)paren
DECL|macro|__NR_getresgid
mdefine_line|#define __NR_getresgid                         120
id|__SYSCALL
c_func
(paren
id|__NR_getresgid
comma
id|sys_getresgid
)paren
DECL|macro|__NR_getpgid
mdefine_line|#define __NR_getpgid                           121
id|__SYSCALL
c_func
(paren
id|__NR_getpgid
comma
id|sys_getpgid
)paren
DECL|macro|__NR_setfsuid
mdefine_line|#define __NR_setfsuid                          122
id|__SYSCALL
c_func
(paren
id|__NR_setfsuid
comma
id|sys_setfsuid
)paren
DECL|macro|__NR_setfsgid
mdefine_line|#define __NR_setfsgid                          123
id|__SYSCALL
c_func
(paren
id|__NR_setfsgid
comma
id|sys_setfsgid
)paren
DECL|macro|__NR_getsid
mdefine_line|#define __NR_getsid                            124
id|__SYSCALL
c_func
(paren
id|__NR_getsid
comma
id|sys_getsid
)paren
DECL|macro|__NR_capget
mdefine_line|#define __NR_capget                            125
id|__SYSCALL
c_func
(paren
id|__NR_capget
comma
id|sys_capget
)paren
DECL|macro|__NR_capset
mdefine_line|#define __NR_capset                            126
id|__SYSCALL
c_func
(paren
id|__NR_capset
comma
id|sys_capset
)paren
DECL|macro|__NR_rt_sigpending
mdefine_line|#define __NR_rt_sigpending                     127
id|__SYSCALL
c_func
(paren
id|__NR_rt_sigpending
comma
id|sys_rt_sigpending
)paren
DECL|macro|__NR_rt_sigtimedwait
mdefine_line|#define __NR_rt_sigtimedwait                   128
id|__SYSCALL
c_func
(paren
id|__NR_rt_sigtimedwait
comma
id|sys_rt_sigtimedwait
)paren
DECL|macro|__NR_rt_sigqueueinfo
mdefine_line|#define __NR_rt_sigqueueinfo                   129
id|__SYSCALL
c_func
(paren
id|__NR_rt_sigqueueinfo
comma
id|sys_rt_sigqueueinfo
)paren
DECL|macro|__NR_rt_sigsuspend
mdefine_line|#define __NR_rt_sigsuspend                     130
id|__SYSCALL
c_func
(paren
id|__NR_rt_sigsuspend
comma
id|stub_rt_sigsuspend
)paren
DECL|macro|__NR_sigaltstack
mdefine_line|#define __NR_sigaltstack                       131
id|__SYSCALL
c_func
(paren
id|__NR_sigaltstack
comma
id|stub_sigaltstack
)paren
DECL|macro|__NR_utime
mdefine_line|#define __NR_utime                             132
id|__SYSCALL
c_func
(paren
id|__NR_utime
comma
id|sys_utime
)paren
DECL|macro|__NR_mknod
mdefine_line|#define __NR_mknod                             133
id|__SYSCALL
c_func
(paren
id|__NR_mknod
comma
id|sys_mknod
)paren
DECL|macro|__NR_uselib
mdefine_line|#define __NR_uselib                            134
id|__SYSCALL
c_func
(paren
id|__NR_uselib
comma
id|sys_uselib
)paren
DECL|macro|__NR_personality
mdefine_line|#define __NR_personality                       135
id|__SYSCALL
c_func
(paren
id|__NR_personality
comma
id|sys_personality
)paren
DECL|macro|__NR_ustat
mdefine_line|#define __NR_ustat                             136
id|__SYSCALL
c_func
(paren
id|__NR_ustat
comma
id|sys_ustat
)paren
DECL|macro|__NR_statfs
mdefine_line|#define __NR_statfs                            137
id|__SYSCALL
c_func
(paren
id|__NR_statfs
comma
id|sys_statfs
)paren
DECL|macro|__NR_fstatfs
mdefine_line|#define __NR_fstatfs                           138
id|__SYSCALL
c_func
(paren
id|__NR_fstatfs
comma
id|sys_fstatfs
)paren
DECL|macro|__NR_sysfs
mdefine_line|#define __NR_sysfs                             139
id|__SYSCALL
c_func
(paren
id|__NR_sysfs
comma
id|sys_sysfs
)paren
DECL|macro|__NR_getpriority
mdefine_line|#define __NR_getpriority                       140
id|__SYSCALL
c_func
(paren
id|__NR_getpriority
comma
id|sys_getpriority
)paren
DECL|macro|__NR_setpriority
mdefine_line|#define __NR_setpriority                       141
id|__SYSCALL
c_func
(paren
id|__NR_setpriority
comma
id|sys_setpriority
)paren
DECL|macro|__NR_sched_setparam
mdefine_line|#define __NR_sched_setparam                    142
id|__SYSCALL
c_func
(paren
id|__NR_sched_setparam
comma
id|sys_sched_setparam
)paren
DECL|macro|__NR_sched_getparam
mdefine_line|#define __NR_sched_getparam                    143
id|__SYSCALL
c_func
(paren
id|__NR_sched_getparam
comma
id|sys_sched_getparam
)paren
DECL|macro|__NR_sched_setscheduler
mdefine_line|#define __NR_sched_setscheduler                144
id|__SYSCALL
c_func
(paren
id|__NR_sched_setscheduler
comma
id|sys_sched_setscheduler
)paren
DECL|macro|__NR_sched_getscheduler
mdefine_line|#define __NR_sched_getscheduler                145
id|__SYSCALL
c_func
(paren
id|__NR_sched_getscheduler
comma
id|sys_sched_getscheduler
)paren
DECL|macro|__NR_sched_get_priority_max
mdefine_line|#define __NR_sched_get_priority_max            146
id|__SYSCALL
c_func
(paren
id|__NR_sched_get_priority_max
comma
id|sys_sched_get_priority_max
)paren
DECL|macro|__NR_sched_get_priority_min
mdefine_line|#define __NR_sched_get_priority_min            147
id|__SYSCALL
c_func
(paren
id|__NR_sched_get_priority_min
comma
id|sys_sched_get_priority_min
)paren
DECL|macro|__NR_sched_rr_get_interval
mdefine_line|#define __NR_sched_rr_get_interval             148
id|__SYSCALL
c_func
(paren
id|__NR_sched_rr_get_interval
comma
id|sys_sched_rr_get_interval
)paren
DECL|macro|__NR_mlock
mdefine_line|#define __NR_mlock                             149
id|__SYSCALL
c_func
(paren
id|__NR_mlock
comma
id|sys_mlock
)paren
DECL|macro|__NR_munlock
mdefine_line|#define __NR_munlock                           150
id|__SYSCALL
c_func
(paren
id|__NR_munlock
comma
id|sys_munlock
)paren
DECL|macro|__NR_mlockall
mdefine_line|#define __NR_mlockall                          151
id|__SYSCALL
c_func
(paren
id|__NR_mlockall
comma
id|sys_mlockall
)paren
DECL|macro|__NR_munlockall
mdefine_line|#define __NR_munlockall                        152
id|__SYSCALL
c_func
(paren
id|__NR_munlockall
comma
id|sys_munlockall
)paren
DECL|macro|__NR_vhangup
mdefine_line|#define __NR_vhangup                           153
id|__SYSCALL
c_func
(paren
id|__NR_vhangup
comma
id|sys_vhangup
)paren
DECL|macro|__NR_modify_ldt
mdefine_line|#define __NR_modify_ldt                        154
id|__SYSCALL
c_func
(paren
id|__NR_modify_ldt
comma
id|sys_modify_ldt
)paren
DECL|macro|__NR_pivot_root
mdefine_line|#define __NR_pivot_root                        155
id|__SYSCALL
c_func
(paren
id|__NR_pivot_root
comma
id|sys_pivot_root
)paren
DECL|macro|__NR__sysctl
mdefine_line|#define __NR__sysctl                           156
id|__SYSCALL
c_func
(paren
id|__NR__sysctl
comma
id|sys_sysctl
)paren
DECL|macro|__NR_prctl
mdefine_line|#define __NR_prctl                             157
id|__SYSCALL
c_func
(paren
id|__NR_prctl
comma
id|sys_prctl
)paren
DECL|macro|__NR_arch_prctl
mdefine_line|#define __NR_arch_prctl                        158
id|__SYSCALL
c_func
(paren
id|__NR_arch_prctl
comma
id|sys_arch_prctl
)paren
DECL|macro|__NR_adjtimex
mdefine_line|#define __NR_adjtimex                          159
id|__SYSCALL
c_func
(paren
id|__NR_adjtimex
comma
id|sys_adjtimex
)paren
DECL|macro|__NR_setrlimit
mdefine_line|#define __NR_setrlimit                         160
id|__SYSCALL
c_func
(paren
id|__NR_setrlimit
comma
id|sys_setrlimit
)paren
DECL|macro|__NR_chroot
mdefine_line|#define __NR_chroot                            161
id|__SYSCALL
c_func
(paren
id|__NR_chroot
comma
id|sys_chroot
)paren
DECL|macro|__NR_sync
mdefine_line|#define __NR_sync                              162
id|__SYSCALL
c_func
(paren
id|__NR_sync
comma
id|sys_sync
)paren
DECL|macro|__NR_acct
mdefine_line|#define __NR_acct                              163
id|__SYSCALL
c_func
(paren
id|__NR_acct
comma
id|sys_acct
)paren
DECL|macro|__NR_settimeofday
mdefine_line|#define __NR_settimeofday                      164
id|__SYSCALL
c_func
(paren
id|__NR_settimeofday
comma
id|sys_settimeofday
)paren
DECL|macro|__NR_mount
mdefine_line|#define __NR_mount                             165
id|__SYSCALL
c_func
(paren
id|__NR_mount
comma
id|sys_mount
)paren
DECL|macro|__NR_umount2
mdefine_line|#define __NR_umount2                           166
id|__SYSCALL
c_func
(paren
id|__NR_umount2
comma
id|sys_umount
)paren
DECL|macro|__NR_swapon
mdefine_line|#define __NR_swapon                            167
id|__SYSCALL
c_func
(paren
id|__NR_swapon
comma
id|sys_swapon
)paren
DECL|macro|__NR_swapoff
mdefine_line|#define __NR_swapoff                           168
id|__SYSCALL
c_func
(paren
id|__NR_swapoff
comma
id|sys_swapoff
)paren
DECL|macro|__NR_reboot
mdefine_line|#define __NR_reboot                            169
id|__SYSCALL
c_func
(paren
id|__NR_reboot
comma
id|sys_reboot
)paren
DECL|macro|__NR_sethostname
mdefine_line|#define __NR_sethostname                       170
id|__SYSCALL
c_func
(paren
id|__NR_sethostname
comma
id|sys_sethostname
)paren
DECL|macro|__NR_setdomainname
mdefine_line|#define __NR_setdomainname                     171
id|__SYSCALL
c_func
(paren
id|__NR_setdomainname
comma
id|sys_setdomainname
)paren
DECL|macro|__NR_iopl
mdefine_line|#define __NR_iopl                              172
id|__SYSCALL
c_func
(paren
id|__NR_iopl
comma
id|stub_iopl
)paren
DECL|macro|__NR_ioperm
mdefine_line|#define __NR_ioperm                            173
id|__SYSCALL
c_func
(paren
id|__NR_ioperm
comma
id|sys_ioperm
)paren
DECL|macro|__NR_create_module
mdefine_line|#define __NR_create_module                     174
id|__SYSCALL
c_func
(paren
id|__NR_create_module
comma
id|sys_ni_syscall
)paren
DECL|macro|__NR_init_module
mdefine_line|#define __NR_init_module                       175
id|__SYSCALL
c_func
(paren
id|__NR_init_module
comma
id|sys_init_module
)paren
DECL|macro|__NR_delete_module
mdefine_line|#define __NR_delete_module                     176
id|__SYSCALL
c_func
(paren
id|__NR_delete_module
comma
id|sys_delete_module
)paren
DECL|macro|__NR_get_kernel_syms
mdefine_line|#define __NR_get_kernel_syms                   177
id|__SYSCALL
c_func
(paren
id|__NR_get_kernel_syms
comma
id|sys_ni_syscall
)paren
DECL|macro|__NR_query_module
mdefine_line|#define __NR_query_module                      178
id|__SYSCALL
c_func
(paren
id|__NR_query_module
comma
id|sys_ni_syscall
)paren
DECL|macro|__NR_quotactl
mdefine_line|#define __NR_quotactl                          179
id|__SYSCALL
c_func
(paren
id|__NR_quotactl
comma
id|sys_quotactl
)paren
DECL|macro|__NR_nfsservctl
mdefine_line|#define __NR_nfsservctl                        180
id|__SYSCALL
c_func
(paren
id|__NR_nfsservctl
comma
id|sys_nfsservctl
)paren
DECL|macro|__NR_getpmsg
mdefine_line|#define __NR_getpmsg                           181&t;/* reserved for LiS/STREAMS */
id|__SYSCALL
c_func
(paren
id|__NR_getpmsg
comma
id|sys_ni_syscall
)paren
DECL|macro|__NR_putpmsg
mdefine_line|#define __NR_putpmsg                           182&t;/* reserved for LiS/STREAMS */
id|__SYSCALL
c_func
(paren
id|__NR_putpmsg
comma
id|sys_ni_syscall
)paren
DECL|macro|__NR_afs_syscall
mdefine_line|#define __NR_afs_syscall                       183&t;/* reserved for AFS */ 
id|__SYSCALL
c_func
(paren
id|__NR_afs_syscall
comma
id|sys_ni_syscall
)paren
DECL|macro|__NR_tuxcall
mdefine_line|#define __NR_tuxcall      &t;&t;184 /* reserved for tux */
id|__SYSCALL
c_func
(paren
id|__NR_tuxcall
comma
id|sys_ni_syscall
)paren
DECL|macro|__NR_security
mdefine_line|#define __NR_security&t;&t;&t;185
id|__SYSCALL
c_func
(paren
id|__NR_security
comma
id|sys_ni_syscall
)paren
DECL|macro|__NR_gettid
mdefine_line|#define __NR_gettid&t;&t;186
id|__SYSCALL
c_func
(paren
id|__NR_gettid
comma
id|sys_gettid
)paren
DECL|macro|__NR_readahead
mdefine_line|#define __NR_readahead&t;&t;187
id|__SYSCALL
c_func
(paren
id|__NR_readahead
comma
id|sys_readahead
)paren
DECL|macro|__NR_setxattr
mdefine_line|#define __NR_setxattr&t;&t;188
id|__SYSCALL
c_func
(paren
id|__NR_setxattr
comma
id|sys_setxattr
)paren
DECL|macro|__NR_lsetxattr
mdefine_line|#define __NR_lsetxattr&t;&t;189
id|__SYSCALL
c_func
(paren
id|__NR_lsetxattr
comma
id|sys_lsetxattr
)paren
DECL|macro|__NR_fsetxattr
mdefine_line|#define __NR_fsetxattr&t;&t;190
id|__SYSCALL
c_func
(paren
id|__NR_fsetxattr
comma
id|sys_fsetxattr
)paren
DECL|macro|__NR_getxattr
mdefine_line|#define __NR_getxattr&t;&t;191
id|__SYSCALL
c_func
(paren
id|__NR_getxattr
comma
id|sys_getxattr
)paren
DECL|macro|__NR_lgetxattr
mdefine_line|#define __NR_lgetxattr&t;&t;192
id|__SYSCALL
c_func
(paren
id|__NR_lgetxattr
comma
id|sys_lgetxattr
)paren
DECL|macro|__NR_fgetxattr
mdefine_line|#define __NR_fgetxattr&t;&t;193
id|__SYSCALL
c_func
(paren
id|__NR_fgetxattr
comma
id|sys_fgetxattr
)paren
DECL|macro|__NR_listxattr
mdefine_line|#define __NR_listxattr&t;&t;194
id|__SYSCALL
c_func
(paren
id|__NR_listxattr
comma
id|sys_listxattr
)paren
DECL|macro|__NR_llistxattr
mdefine_line|#define __NR_llistxattr&t;&t;195
id|__SYSCALL
c_func
(paren
id|__NR_llistxattr
comma
id|sys_llistxattr
)paren
DECL|macro|__NR_flistxattr
mdefine_line|#define __NR_flistxattr&t;&t;196
id|__SYSCALL
c_func
(paren
id|__NR_flistxattr
comma
id|sys_flistxattr
)paren
DECL|macro|__NR_removexattr
mdefine_line|#define __NR_removexattr&t;197
id|__SYSCALL
c_func
(paren
id|__NR_removexattr
comma
id|sys_removexattr
)paren
DECL|macro|__NR_lremovexattr
mdefine_line|#define __NR_lremovexattr&t;198
id|__SYSCALL
c_func
(paren
id|__NR_lremovexattr
comma
id|sys_lremovexattr
)paren
DECL|macro|__NR_fremovexattr
mdefine_line|#define __NR_fremovexattr&t;199
id|__SYSCALL
c_func
(paren
id|__NR_fremovexattr
comma
id|sys_fremovexattr
)paren
DECL|macro|__NR_tkill
mdefine_line|#define __NR_tkill&t;200
id|__SYSCALL
c_func
(paren
id|__NR_tkill
comma
id|sys_tkill
)paren
DECL|macro|__NR_time
mdefine_line|#define __NR_time      201
id|__SYSCALL
c_func
(paren
id|__NR_time
comma
id|sys_time64
)paren
DECL|macro|__NR_futex
mdefine_line|#define __NR_futex     202
id|__SYSCALL
c_func
(paren
id|__NR_futex
comma
id|sys_futex
)paren
DECL|macro|__NR_sched_setaffinity
mdefine_line|#define __NR_sched_setaffinity    203
id|__SYSCALL
c_func
(paren
id|__NR_sched_setaffinity
comma
id|sys_sched_setaffinity
)paren
DECL|macro|__NR_sched_getaffinity
mdefine_line|#define __NR_sched_getaffinity     204
id|__SYSCALL
c_func
(paren
id|__NR_sched_getaffinity
comma
id|sys_sched_getaffinity
)paren
DECL|macro|__NR_set_thread_area
mdefine_line|#define __NR_set_thread_area&t;205
id|__SYSCALL
c_func
(paren
id|__NR_set_thread_area
comma
id|sys_ni_syscall
)paren
multiline_comment|/* use arch_prctl */
DECL|macro|__NR_io_setup
mdefine_line|#define __NR_io_setup&t;206
id|__SYSCALL
c_func
(paren
id|__NR_io_setup
comma
id|sys_io_setup
)paren
DECL|macro|__NR_io_destroy
mdefine_line|#define __NR_io_destroy&t;207
id|__SYSCALL
c_func
(paren
id|__NR_io_destroy
comma
id|sys_io_destroy
)paren
DECL|macro|__NR_io_getevents
mdefine_line|#define __NR_io_getevents&t;208
id|__SYSCALL
c_func
(paren
id|__NR_io_getevents
comma
id|sys_io_getevents
)paren
DECL|macro|__NR_io_submit
mdefine_line|#define __NR_io_submit&t;209
id|__SYSCALL
c_func
(paren
id|__NR_io_submit
comma
id|sys_io_submit
)paren
DECL|macro|__NR_io_cancel
mdefine_line|#define __NR_io_cancel&t;210
id|__SYSCALL
c_func
(paren
id|__NR_io_cancel
comma
id|sys_io_cancel
)paren
DECL|macro|__NR_get_thread_area
mdefine_line|#define __NR_get_thread_area&t;211
id|__SYSCALL
c_func
(paren
id|__NR_get_thread_area
comma
id|sys_ni_syscall
)paren
multiline_comment|/* use arch_prctl */
DECL|macro|__NR_lookup_dcookie
mdefine_line|#define __NR_lookup_dcookie&t;212
id|__SYSCALL
c_func
(paren
id|__NR_lookup_dcookie
comma
id|sys_lookup_dcookie
)paren
DECL|macro|__NR_epoll_create
mdefine_line|#define __NR_epoll_create&t;213
id|__SYSCALL
c_func
(paren
id|__NR_epoll_create
comma
id|sys_epoll_create
)paren
DECL|macro|__NR_epoll_ctl_old
mdefine_line|#define __NR_epoll_ctl_old&t;214
id|__SYSCALL
c_func
(paren
id|__NR_epoll_ctl_old
comma
id|sys_ni_syscall
)paren
DECL|macro|__NR_epoll_wait_old
mdefine_line|#define __NR_epoll_wait_old&t;215
id|__SYSCALL
c_func
(paren
id|__NR_epoll_wait_old
comma
id|sys_ni_syscall
)paren
DECL|macro|__NR_remap_file_pages
mdefine_line|#define __NR_remap_file_pages&t;216
id|__SYSCALL
c_func
(paren
id|__NR_remap_file_pages
comma
id|sys_remap_file_pages
)paren
DECL|macro|__NR_getdents64
mdefine_line|#define __NR_getdents64&t;217
id|__SYSCALL
c_func
(paren
id|__NR_getdents64
comma
id|sys_getdents64
)paren
DECL|macro|__NR_set_tid_address
mdefine_line|#define __NR_set_tid_address&t;218
id|__SYSCALL
c_func
(paren
id|__NR_set_tid_address
comma
id|sys_set_tid_address
)paren
DECL|macro|__NR_restart_syscall
mdefine_line|#define __NR_restart_syscall&t;219
id|__SYSCALL
c_func
(paren
id|__NR_restart_syscall
comma
id|sys_restart_syscall
)paren
DECL|macro|__NR_semtimedop
mdefine_line|#define __NR_semtimedop&t;&t;220
id|__SYSCALL
c_func
(paren
id|__NR_semtimedop
comma
id|sys_semtimedop
)paren
DECL|macro|__NR_fadvise64
mdefine_line|#define __NR_fadvise64&t;&t;221
id|__SYSCALL
c_func
(paren
id|__NR_fadvise64
comma
id|sys_fadvise64
)paren
DECL|macro|__NR_timer_create
mdefine_line|#define __NR_timer_create&t;&t;222
id|__SYSCALL
c_func
(paren
id|__NR_timer_create
comma
id|sys_timer_create
)paren
DECL|macro|__NR_timer_settime
mdefine_line|#define __NR_timer_settime&t;&t;223
id|__SYSCALL
c_func
(paren
id|__NR_timer_settime
comma
id|sys_timer_settime
)paren
DECL|macro|__NR_timer_gettime
mdefine_line|#define __NR_timer_gettime&t;&t;224
id|__SYSCALL
c_func
(paren
id|__NR_timer_gettime
comma
id|sys_timer_gettime
)paren
DECL|macro|__NR_timer_getoverrun
mdefine_line|#define __NR_timer_getoverrun&t;&t;225
id|__SYSCALL
c_func
(paren
id|__NR_timer_getoverrun
comma
id|sys_timer_getoverrun
)paren
DECL|macro|__NR_timer_delete
mdefine_line|#define __NR_timer_delete&t;226
id|__SYSCALL
c_func
(paren
id|__NR_timer_delete
comma
id|sys_timer_delete
)paren
DECL|macro|__NR_clock_settime
mdefine_line|#define __NR_clock_settime&t;227
id|__SYSCALL
c_func
(paren
id|__NR_clock_settime
comma
id|sys_clock_settime
)paren
DECL|macro|__NR_clock_gettime
mdefine_line|#define __NR_clock_gettime&t;228
id|__SYSCALL
c_func
(paren
id|__NR_clock_gettime
comma
id|sys_clock_gettime
)paren
DECL|macro|__NR_clock_getres
mdefine_line|#define __NR_clock_getres&t;229
id|__SYSCALL
c_func
(paren
id|__NR_clock_getres
comma
id|sys_clock_getres
)paren
DECL|macro|__NR_clock_nanosleep
mdefine_line|#define __NR_clock_nanosleep&t;230
id|__SYSCALL
c_func
(paren
id|__NR_clock_nanosleep
comma
id|sys_clock_nanosleep
)paren
DECL|macro|__NR_exit_group
mdefine_line|#define __NR_exit_group&t;&t;231
id|__SYSCALL
c_func
(paren
id|__NR_exit_group
comma
id|sys_exit_group
)paren
DECL|macro|__NR_epoll_wait
mdefine_line|#define __NR_epoll_wait&t;&t;232
id|__SYSCALL
c_func
(paren
id|__NR_epoll_wait
comma
id|sys_epoll_wait
)paren
DECL|macro|__NR_epoll_ctl
mdefine_line|#define __NR_epoll_ctl&t;&t;233
id|__SYSCALL
c_func
(paren
id|__NR_epoll_ctl
comma
id|sys_epoll_ctl
)paren
DECL|macro|__NR_tgkill
mdefine_line|#define __NR_tgkill&t;&t;234
id|__SYSCALL
c_func
(paren
id|__NR_tgkill
comma
id|sys_tgkill
)paren
DECL|macro|__NR_utimes
mdefine_line|#define __NR_utimes&t;&t;235
id|__SYSCALL
c_func
(paren
id|__NR_utimes
comma
id|sys_utimes
)paren
DECL|macro|__NR_vserver
mdefine_line|#define __NR_vserver&t;&t;236
id|__SYSCALL
c_func
(paren
id|__NR_vserver
comma
id|sys_ni_syscall
)paren
DECL|macro|__NR_vserver
mdefine_line|#define __NR_vserver&t;&t;236
id|__SYSCALL
c_func
(paren
id|__NR_vserver
comma
id|sys_ni_syscall
)paren
DECL|macro|__NR_mbind
mdefine_line|#define __NR_mbind &t;&t;237
id|__SYSCALL
c_func
(paren
id|__NR_mbind
comma
id|sys_mbind
)paren
DECL|macro|__NR_set_mempolicy
mdefine_line|#define __NR_set_mempolicy &t;238
id|__SYSCALL
c_func
(paren
id|__NR_set_mempolicy
comma
id|sys_set_mempolicy
)paren
DECL|macro|__NR_get_mempolicy
mdefine_line|#define __NR_get_mempolicy &t;239
id|__SYSCALL
c_func
(paren
id|__NR_get_mempolicy
comma
id|sys_get_mempolicy
)paren
DECL|macro|__NR_mq_open
mdefine_line|#define __NR_mq_open &t;&t;240
id|__SYSCALL
c_func
(paren
id|__NR_mq_open
comma
id|sys_mq_open
)paren
DECL|macro|__NR_mq_unlink
mdefine_line|#define __NR_mq_unlink &t;&t;241
id|__SYSCALL
c_func
(paren
id|__NR_mq_unlink
comma
id|sys_mq_unlink
)paren
DECL|macro|__NR_mq_timedsend
mdefine_line|#define __NR_mq_timedsend &t;242
id|__SYSCALL
c_func
(paren
id|__NR_mq_timedsend
comma
id|sys_mq_timedsend
)paren
DECL|macro|__NR_mq_timedreceive
mdefine_line|#define __NR_mq_timedreceive&t;243
id|__SYSCALL
c_func
(paren
id|__NR_mq_timedreceive
comma
id|sys_mq_timedreceive
)paren
DECL|macro|__NR_mq_notify
mdefine_line|#define __NR_mq_notify &t;&t;244
id|__SYSCALL
c_func
(paren
id|__NR_mq_notify
comma
id|sys_mq_notify
)paren
DECL|macro|__NR_mq_getsetattr
mdefine_line|#define __NR_mq_getsetattr &t;245
id|__SYSCALL
c_func
(paren
id|__NR_mq_getsetattr
comma
id|sys_mq_getsetattr
)paren
DECL|macro|__NR_kexec_load
mdefine_line|#define __NR_kexec_load &t;246
id|__SYSCALL
c_func
(paren
id|__NR_kexec_load
comma
id|sys_ni_syscall
)paren
DECL|macro|__NR_syscall_max
mdefine_line|#define __NR_syscall_max __NR_kexec_load
macro_line|#ifndef __NO_STUBS
multiline_comment|/* user-visible error numbers are in the range -1 - -4095 */
DECL|macro|__syscall_clobber
mdefine_line|#define __syscall_clobber &quot;r11&quot;,&quot;rcx&quot;,&quot;memory&quot; 
DECL|macro|__syscall_return
mdefine_line|#define __syscall_return(type, res) &bslash;&n;do { &bslash;&n;&t;if ((unsigned long)(res) &gt;= (unsigned long)(-127)) { &bslash;&n;&t;&t;errno = -(res); &bslash;&n;&t;&t;res = -1; &bslash;&n;&t;} &bslash;&n;&t;return (type) (res); &bslash;&n;} while (0)
macro_line|#ifdef __KERNEL__
DECL|macro|__ARCH_WANT_OLD_READDIR
mdefine_line|#define __ARCH_WANT_OLD_READDIR
DECL|macro|__ARCH_WANT_OLD_STAT
mdefine_line|#define __ARCH_WANT_OLD_STAT
DECL|macro|__ARCH_WANT_SYS_ALARM
mdefine_line|#define __ARCH_WANT_SYS_ALARM
DECL|macro|__ARCH_WANT_SYS_GETHOSTNAME
mdefine_line|#define __ARCH_WANT_SYS_GETHOSTNAME
DECL|macro|__ARCH_WANT_SYS_PAUSE
mdefine_line|#define __ARCH_WANT_SYS_PAUSE
DECL|macro|__ARCH_WANT_SYS_SGETMASK
mdefine_line|#define __ARCH_WANT_SYS_SGETMASK
DECL|macro|__ARCH_WANT_SYS_SIGNAL
mdefine_line|#define __ARCH_WANT_SYS_SIGNAL
DECL|macro|__ARCH_WANT_SYS_TIME
mdefine_line|#define __ARCH_WANT_SYS_TIME
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
macro_line|#endif
macro_line|#ifndef __KERNEL_SYSCALLS__
DECL|macro|__syscall
mdefine_line|#define __syscall &quot;syscall&quot;
DECL|macro|_syscall0
mdefine_line|#define _syscall0(type,name) &bslash;&n;type name(void) &bslash;&n;{ &bslash;&n;long __res; &bslash;&n;__asm__ volatile (__syscall &bslash;&n;&t;: &quot;=a&quot; (__res) &bslash;&n;&t;: &quot;0&quot; (__NR_##name) : __syscall_clobber ); &bslash;&n;__syscall_return(type,__res); &bslash;&n;}
DECL|macro|_syscall1
mdefine_line|#define _syscall1(type,name,type1,arg1) &bslash;&n;type name(type1 arg1) &bslash;&n;{ &bslash;&n;long __res; &bslash;&n;__asm__ volatile (__syscall &bslash;&n;&t;: &quot;=a&quot; (__res) &bslash;&n;&t;: &quot;0&quot; (__NR_##name),&quot;D&quot; ((long)(arg1)) : __syscall_clobber ); &bslash;&n;__syscall_return(type,__res); &bslash;&n;}
DECL|macro|_syscall2
mdefine_line|#define _syscall2(type,name,type1,arg1,type2,arg2) &bslash;&n;type name(type1 arg1,type2 arg2) &bslash;&n;{ &bslash;&n;long __res; &bslash;&n;__asm__ volatile (__syscall &bslash;&n;&t;: &quot;=a&quot; (__res) &bslash;&n;&t;: &quot;0&quot; (__NR_##name),&quot;D&quot; ((long)(arg1)),&quot;S&quot; ((long)(arg2)) : __syscall_clobber ); &bslash;&n;__syscall_return(type,__res); &bslash;&n;}
DECL|macro|_syscall3
mdefine_line|#define _syscall3(type,name,type1,arg1,type2,arg2,type3,arg3) &bslash;&n;type name(type1 arg1,type2 arg2,type3 arg3) &bslash;&n;{ &bslash;&n;long __res; &bslash;&n;__asm__ volatile (__syscall &bslash;&n;&t;: &quot;=a&quot; (__res) &bslash;&n;&t;: &quot;0&quot; (__NR_##name),&quot;D&quot; ((long)(arg1)),&quot;S&quot; ((long)(arg2)), &bslash;&n;&t;&t;  &quot;d&quot; ((long)(arg3)) : __syscall_clobber); &bslash;&n;__syscall_return(type,__res); &bslash;&n;}
DECL|macro|_syscall4
mdefine_line|#define _syscall4(type,name,type1,arg1,type2,arg2,type3,arg3,type4,arg4) &bslash;&n;type name (type1 arg1, type2 arg2, type3 arg3, type4 arg4) &bslash;&n;{ &bslash;&n;long __res; &bslash;&n;__asm__ volatile (&quot;movq %5,%%r10 ;&quot; __syscall &bslash;&n;&t;: &quot;=a&quot; (__res) &bslash;&n;&t;: &quot;0&quot; (__NR_##name),&quot;D&quot; ((long)(arg1)),&quot;S&quot; ((long)(arg2)), &bslash;&n;&t;  &quot;d&quot; ((long)(arg3)),&quot;g&quot; ((long)(arg4)) : __syscall_clobber,&quot;r10&quot; ); &bslash;&n;__syscall_return(type,__res); &bslash;&n;} 
DECL|macro|_syscall5
mdefine_line|#define _syscall5(type,name,type1,arg1,type2,arg2,type3,arg3,type4,arg4, &bslash;&n;&t;  type5,arg5) &bslash;&n;type name (type1 arg1,type2 arg2,type3 arg3,type4 arg4,type5 arg5) &bslash;&n;{ &bslash;&n;long __res; &bslash;&n;__asm__ volatile (&quot;movq %5,%%r10 ; movq %6,%%r8 ; &quot; __syscall &bslash;&n;&t;: &quot;=a&quot; (__res) &bslash;&n;&t;: &quot;0&quot; (__NR_##name),&quot;D&quot; ((long)(arg1)),&quot;S&quot; ((long)(arg2)), &bslash;&n;&t;  &quot;d&quot; ((long)(arg3)),&quot;g&quot; ((long)(arg4)),&quot;g&quot; ((long)(arg5)) : &bslash;&n;&t;__syscall_clobber,&quot;r8&quot;,&quot;r10&quot; ); &bslash;&n;__syscall_return(type,__res); &bslash;&n;}
DECL|macro|_syscall6
mdefine_line|#define _syscall6(type,name,type1,arg1,type2,arg2,type3,arg3,type4,arg4, &bslash;&n;&t;  type5,arg5,type6,arg6) &bslash;&n;type name (type1 arg1,type2 arg2,type3 arg3,type4 arg4,type5 arg5,type6 arg6) &bslash;&n;{ &bslash;&n;long __res; &bslash;&n;__asm__ volatile (&quot;movq %5,%%r10 ; movq %6,%%r8 ; movq %7,%%r9 ; &quot; __syscall &bslash;&n;&t;: &quot;=a&quot; (__res) &bslash;&n;&t;: &quot;0&quot; (__NR_##name),&quot;D&quot; ((long)(arg1)),&quot;S&quot; ((long)(arg2)), &bslash;&n;&t;  &quot;d&quot; ((long)(arg3)), &quot;g&quot; ((long)(arg4)), &quot;g&quot; ((long)(arg5)), &bslash;&n;&t;  &quot;g&quot; ((long)(arg6)) : &bslash;&n;&t;__syscall_clobber,&quot;r8&quot;,&quot;r10&quot;,&quot;r9&quot; ); &bslash;&n;__syscall_return(type,__res); &bslash;&n;}
macro_line|#else /* __KERNEL_SYSCALLS__ */
macro_line|#include &lt;linux/syscalls.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
multiline_comment|/*&n; * we need this inline - forking from kernel space will result&n; * in NO COPY ON WRITE (!!!), until an execve is executed. This&n; * is no problem, but for the stack. This is handled by not letting&n; * main() use the stack at all after fork(). Thus, no function&n; * calls - which means inline code for fork too, as otherwise we&n; * would use the stack upon exit from &squot;fork()&squot;.&n; *&n; * Actually only pause and fork are needed inline, so that there&n; * won&squot;t be any messing with the stack from main(), but we define&n; * some others too.&n; */
mdefine_line|#define __NR__exit __NR_exit
r_static
r_inline
id|pid_t
id|setsid
c_func
(paren
r_void
)paren
(brace
r_return
id|sys_setsid
c_func
(paren
)paren
suffix:semicolon
)brace
r_static
r_inline
id|ssize_t
id|write
c_func
(paren
r_int
r_int
id|fd
comma
r_char
op_star
id|buf
comma
r_int
id|count
)paren
(brace
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
r_static
r_inline
id|ssize_t
id|read
c_func
(paren
r_int
r_int
id|fd
comma
r_char
op_star
id|buf
comma
r_int
id|count
)paren
(brace
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
r_static
r_inline
id|off_t
id|lseek
c_func
(paren
r_int
r_int
id|fd
comma
id|off_t
id|offset
comma
r_int
r_int
id|origin
)paren
(brace
r_return
id|sys_lseek
c_func
(paren
id|fd
comma
id|offset
comma
id|origin
)paren
suffix:semicolon
)brace
r_static
r_inline
r_int
id|dup
c_func
(paren
r_int
r_int
id|fd
)paren
(brace
r_return
id|sys_dup
c_func
(paren
id|fd
)paren
suffix:semicolon
)brace
multiline_comment|/* implemented in asm in arch/x86_64/kernel/entry.S */
r_extern
r_int
id|execve
c_func
(paren
r_char
op_star
comma
r_char
op_star
op_star
comma
r_char
op_star
op_star
)paren
suffix:semicolon
r_static
r_inline
r_int
id|open
c_func
(paren
r_const
r_char
op_star
id|filename
comma
r_int
id|flags
comma
r_int
id|mode
)paren
(brace
r_return
id|sys_open
c_func
(paren
id|filename
comma
id|flags
comma
id|mode
)paren
suffix:semicolon
)brace
r_static
r_inline
r_int
id|close
c_func
(paren
r_int
r_int
id|fd
)paren
(brace
r_return
id|sys_close
c_func
(paren
id|fd
)paren
suffix:semicolon
)brace
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
r_extern
r_int
id|sys_mmap
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
id|off
)paren
suffix:semicolon
r_extern
r_int
id|sys_modify_ldt
c_func
(paren
r_int
id|func
comma
r_void
op_star
id|ptr
comma
r_int
r_int
id|bytecount
)paren
suffix:semicolon
id|asmlinkage
r_int
id|sys_execve
c_func
(paren
r_char
op_star
id|name
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
r_void
op_star
id|parent_tid
comma
r_void
op_star
id|child_tid
comma
r_struct
id|pt_regs
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
id|regs
)paren
suffix:semicolon
id|asmlinkage
r_int
id|sys_pipe
c_func
(paren
r_int
op_star
id|fildes
)paren
suffix:semicolon
macro_line|#endif /* __KERNEL_SYSCALLS__ */
macro_line|#if !defined(__ASSEMBLY__) &amp;&amp; defined(__KERNEL__)
macro_line|#include &lt;linux/linkage.h&gt;
macro_line|#include &lt;linux/compiler.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
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
r_int
id|addr
comma
r_int
id|data
)paren
suffix:semicolon
id|asmlinkage
r_int
id|sys_iopl
c_func
(paren
r_int
r_int
id|level
comma
r_struct
id|pt_regs
id|regs
)paren
suffix:semicolon
DECL|variable|sys_ioperm
id|asmlinkage
r_int
id|sys_ioperm
c_func
(paren
r_int
r_int
id|from
comma
r_int
r_int
id|num
comma
r_int
id|turn_on
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
macro_line|#endif&t;/* __ASSEMBLY__ */
macro_line|#endif /* __NO_STUBS */
multiline_comment|/*&n; * &quot;Conditional&quot; syscalls&n; *&n; * What we want is __attribute__((weak,alias(&quot;sys_ni_syscall&quot;))),&n; * but it doesn&squot;t work on all toolchains, so we just do it by hand&n; */
DECL|macro|cond_syscall
mdefine_line|#define cond_syscall(x) asm(&quot;.weak&bslash;t&quot; #x &quot;&bslash;n&bslash;t.set&bslash;t&quot; #x &quot;,sys_ni_syscall&quot;);
macro_line|#endif
eof
