macro_line|#ifndef _ASM_PARISC_UNISTD_H_
DECL|macro|_ASM_PARISC_UNISTD_H_
mdefine_line|#define _ASM_PARISC_UNISTD_H_
multiline_comment|/*&n; * This file contains the system call numbers.&n; */
multiline_comment|/*&n; *   HP-UX system calls get their native numbers for binary compatibility.&n; */
DECL|macro|__NR_HPUX_exit
mdefine_line|#define __NR_HPUX_exit                    1
DECL|macro|__NR_HPUX_fork
mdefine_line|#define __NR_HPUX_fork                    2
DECL|macro|__NR_HPUX_read
mdefine_line|#define __NR_HPUX_read                    3
DECL|macro|__NR_HPUX_write
mdefine_line|#define __NR_HPUX_write                   4
DECL|macro|__NR_HPUX_open
mdefine_line|#define __NR_HPUX_open                    5
DECL|macro|__NR_HPUX_close
mdefine_line|#define __NR_HPUX_close                   6
DECL|macro|__NR_HPUX_wait
mdefine_line|#define __NR_HPUX_wait                    7
DECL|macro|__NR_HPUX_creat
mdefine_line|#define __NR_HPUX_creat                   8
DECL|macro|__NR_HPUX_link
mdefine_line|#define __NR_HPUX_link                    9
DECL|macro|__NR_HPUX_unlink
mdefine_line|#define __NR_HPUX_unlink                 10
DECL|macro|__NR_HPUX_execv
mdefine_line|#define __NR_HPUX_execv                  11
DECL|macro|__NR_HPUX_chdir
mdefine_line|#define __NR_HPUX_chdir                  12
DECL|macro|__NR_HPUX_time
mdefine_line|#define __NR_HPUX_time                   13
DECL|macro|__NR_HPUX_mknod
mdefine_line|#define __NR_HPUX_mknod                  14
DECL|macro|__NR_HPUX_chmod
mdefine_line|#define __NR_HPUX_chmod                  15
DECL|macro|__NR_HPUX_chown
mdefine_line|#define __NR_HPUX_chown                  16
DECL|macro|__NR_HPUX_break
mdefine_line|#define __NR_HPUX_break                  17
DECL|macro|__NR_HPUX_lchmod
mdefine_line|#define __NR_HPUX_lchmod                 18
DECL|macro|__NR_HPUX_lseek
mdefine_line|#define __NR_HPUX_lseek                  19
DECL|macro|__NR_HPUX_getpid
mdefine_line|#define __NR_HPUX_getpid                 20
DECL|macro|__NR_HPUX_mount
mdefine_line|#define __NR_HPUX_mount                  21
DECL|macro|__NR_HPUX_umount
mdefine_line|#define __NR_HPUX_umount                 22
DECL|macro|__NR_HPUX_setuid
mdefine_line|#define __NR_HPUX_setuid                 23
DECL|macro|__NR_HPUX_getuid
mdefine_line|#define __NR_HPUX_getuid                 24
DECL|macro|__NR_HPUX_stime
mdefine_line|#define __NR_HPUX_stime                  25
DECL|macro|__NR_HPUX_ptrace
mdefine_line|#define __NR_HPUX_ptrace                 26
DECL|macro|__NR_HPUX_alarm
mdefine_line|#define __NR_HPUX_alarm                  27
DECL|macro|__NR_HPUX_oldfstat
mdefine_line|#define __NR_HPUX_oldfstat               28
DECL|macro|__NR_HPUX_pause
mdefine_line|#define __NR_HPUX_pause                  29
DECL|macro|__NR_HPUX_utime
mdefine_line|#define __NR_HPUX_utime                  30
DECL|macro|__NR_HPUX_stty
mdefine_line|#define __NR_HPUX_stty                   31
DECL|macro|__NR_HPUX_gtty
mdefine_line|#define __NR_HPUX_gtty                   32
DECL|macro|__NR_HPUX_access
mdefine_line|#define __NR_HPUX_access                 33
DECL|macro|__NR_HPUX_nice
mdefine_line|#define __NR_HPUX_nice                   34
DECL|macro|__NR_HPUX_ftime
mdefine_line|#define __NR_HPUX_ftime                  35
DECL|macro|__NR_HPUX_sync
mdefine_line|#define __NR_HPUX_sync                   36
DECL|macro|__NR_HPUX_kill
mdefine_line|#define __NR_HPUX_kill                   37
DECL|macro|__NR_HPUX_stat
mdefine_line|#define __NR_HPUX_stat                   38
DECL|macro|__NR_HPUX_setpgrp3
mdefine_line|#define __NR_HPUX_setpgrp3               39
DECL|macro|__NR_HPUX_lstat
mdefine_line|#define __NR_HPUX_lstat                  40
DECL|macro|__NR_HPUX_dup
mdefine_line|#define __NR_HPUX_dup                    41
DECL|macro|__NR_HPUX_pipe
mdefine_line|#define __NR_HPUX_pipe                   42
DECL|macro|__NR_HPUX_times
mdefine_line|#define __NR_HPUX_times                  43
DECL|macro|__NR_HPUX_profil
mdefine_line|#define __NR_HPUX_profil                 44
DECL|macro|__NR_HPUX_ki_call
mdefine_line|#define __NR_HPUX_ki_call                45
DECL|macro|__NR_HPUX_setgid
mdefine_line|#define __NR_HPUX_setgid                 46
DECL|macro|__NR_HPUX_getgid
mdefine_line|#define __NR_HPUX_getgid                 47
DECL|macro|__NR_HPUX_sigsys
mdefine_line|#define __NR_HPUX_sigsys                 48
DECL|macro|__NR_HPUX_reserved1
mdefine_line|#define __NR_HPUX_reserved1              49
DECL|macro|__NR_HPUX_reserved2
mdefine_line|#define __NR_HPUX_reserved2              50
DECL|macro|__NR_HPUX_acct
mdefine_line|#define __NR_HPUX_acct                   51
DECL|macro|__NR_HPUX_set_userthreadid
mdefine_line|#define __NR_HPUX_set_userthreadid       52
DECL|macro|__NR_HPUX_oldlock
mdefine_line|#define __NR_HPUX_oldlock                53
DECL|macro|__NR_HPUX_ioctl
mdefine_line|#define __NR_HPUX_ioctl                  54
DECL|macro|__NR_HPUX_reboot
mdefine_line|#define __NR_HPUX_reboot                 55
DECL|macro|__NR_HPUX_symlink
mdefine_line|#define __NR_HPUX_symlink                56
DECL|macro|__NR_HPUX_utssys
mdefine_line|#define __NR_HPUX_utssys                 57
DECL|macro|__NR_HPUX_readlink
mdefine_line|#define __NR_HPUX_readlink               58
DECL|macro|__NR_HPUX_execve
mdefine_line|#define __NR_HPUX_execve                 59
DECL|macro|__NR_HPUX_umask
mdefine_line|#define __NR_HPUX_umask                  60
DECL|macro|__NR_HPUX_chroot
mdefine_line|#define __NR_HPUX_chroot                 61
DECL|macro|__NR_HPUX_fcntl
mdefine_line|#define __NR_HPUX_fcntl                  62
DECL|macro|__NR_HPUX_ulimit
mdefine_line|#define __NR_HPUX_ulimit                 63
DECL|macro|__NR_HPUX_getpagesize
mdefine_line|#define __NR_HPUX_getpagesize            64
DECL|macro|__NR_HPUX_mremap
mdefine_line|#define __NR_HPUX_mremap                 65
DECL|macro|__NR_HPUX_vfork
mdefine_line|#define __NR_HPUX_vfork                  66
DECL|macro|__NR_HPUX_vread
mdefine_line|#define __NR_HPUX_vread                  67
DECL|macro|__NR_HPUX_vwrite
mdefine_line|#define __NR_HPUX_vwrite                 68
DECL|macro|__NR_HPUX_sbrk
mdefine_line|#define __NR_HPUX_sbrk                   69
DECL|macro|__NR_HPUX_sstk
mdefine_line|#define __NR_HPUX_sstk                   70
DECL|macro|__NR_HPUX_mmap
mdefine_line|#define __NR_HPUX_mmap                   71
DECL|macro|__NR_HPUX_vadvise
mdefine_line|#define __NR_HPUX_vadvise                72
DECL|macro|__NR_HPUX_munmap
mdefine_line|#define __NR_HPUX_munmap                 73
DECL|macro|__NR_HPUX_mprotect
mdefine_line|#define __NR_HPUX_mprotect               74
DECL|macro|__NR_HPUX_madvise
mdefine_line|#define __NR_HPUX_madvise                75
DECL|macro|__NR_HPUX_vhangup
mdefine_line|#define __NR_HPUX_vhangup                76
DECL|macro|__NR_HPUX_swapoff
mdefine_line|#define __NR_HPUX_swapoff                77
DECL|macro|__NR_HPUX_mincore
mdefine_line|#define __NR_HPUX_mincore                78
DECL|macro|__NR_HPUX_getgroups
mdefine_line|#define __NR_HPUX_getgroups              79
DECL|macro|__NR_HPUX_setgroups
mdefine_line|#define __NR_HPUX_setgroups              80
DECL|macro|__NR_HPUX_getpgrp2
mdefine_line|#define __NR_HPUX_getpgrp2               81
DECL|macro|__NR_HPUX_setpgrp2
mdefine_line|#define __NR_HPUX_setpgrp2               82
DECL|macro|__NR_HPUX_setitimer
mdefine_line|#define __NR_HPUX_setitimer              83
DECL|macro|__NR_HPUX_wait3
mdefine_line|#define __NR_HPUX_wait3                  84
DECL|macro|__NR_HPUX_swapon
mdefine_line|#define __NR_HPUX_swapon                 85
DECL|macro|__NR_HPUX_getitimer
mdefine_line|#define __NR_HPUX_getitimer              86
DECL|macro|__NR_HPUX_gethostname42
mdefine_line|#define __NR_HPUX_gethostname42          87
DECL|macro|__NR_HPUX_sethostname42
mdefine_line|#define __NR_HPUX_sethostname42          88
DECL|macro|__NR_HPUX_getdtablesize
mdefine_line|#define __NR_HPUX_getdtablesize          89
DECL|macro|__NR_HPUX_dup2
mdefine_line|#define __NR_HPUX_dup2                   90
DECL|macro|__NR_HPUX_getdopt
mdefine_line|#define __NR_HPUX_getdopt                91
DECL|macro|__NR_HPUX_fstat
mdefine_line|#define __NR_HPUX_fstat                  92
DECL|macro|__NR_HPUX_select
mdefine_line|#define __NR_HPUX_select                 93
DECL|macro|__NR_HPUX_setdopt
mdefine_line|#define __NR_HPUX_setdopt                94
DECL|macro|__NR_HPUX_fsync
mdefine_line|#define __NR_HPUX_fsync                  95
DECL|macro|__NR_HPUX_setpriority
mdefine_line|#define __NR_HPUX_setpriority            96
DECL|macro|__NR_HPUX_socket_old
mdefine_line|#define __NR_HPUX_socket_old             97
DECL|macro|__NR_HPUX_connect_old
mdefine_line|#define __NR_HPUX_connect_old            98
DECL|macro|__NR_HPUX_accept_old
mdefine_line|#define __NR_HPUX_accept_old             99
DECL|macro|__NR_HPUX_getpriority
mdefine_line|#define __NR_HPUX_getpriority           100
DECL|macro|__NR_HPUX_send_old
mdefine_line|#define __NR_HPUX_send_old              101
DECL|macro|__NR_HPUX_recv_old
mdefine_line|#define __NR_HPUX_recv_old              102
DECL|macro|__NR_HPUX_socketaddr_old
mdefine_line|#define __NR_HPUX_socketaddr_old        103
DECL|macro|__NR_HPUX_bind_old
mdefine_line|#define __NR_HPUX_bind_old              104
DECL|macro|__NR_HPUX_setsockopt_old
mdefine_line|#define __NR_HPUX_setsockopt_old        105
DECL|macro|__NR_HPUX_listen_old
mdefine_line|#define __NR_HPUX_listen_old            106
DECL|macro|__NR_HPUX_vtimes_old
mdefine_line|#define __NR_HPUX_vtimes_old            107
DECL|macro|__NR_HPUX_sigvector
mdefine_line|#define __NR_HPUX_sigvector             108
DECL|macro|__NR_HPUX_sigblock
mdefine_line|#define __NR_HPUX_sigblock              109
DECL|macro|__NR_HPUX_siggetmask
mdefine_line|#define __NR_HPUX_siggetmask            110
DECL|macro|__NR_HPUX_sigpause
mdefine_line|#define __NR_HPUX_sigpause              111
DECL|macro|__NR_HPUX_sigstack
mdefine_line|#define __NR_HPUX_sigstack              112
DECL|macro|__NR_HPUX_recvmsg_old
mdefine_line|#define __NR_HPUX_recvmsg_old           113
DECL|macro|__NR_HPUX_sendmsg_old
mdefine_line|#define __NR_HPUX_sendmsg_old           114
DECL|macro|__NR_HPUX_vtrace_old
mdefine_line|#define __NR_HPUX_vtrace_old            115
DECL|macro|__NR_HPUX_gettimeofday
mdefine_line|#define __NR_HPUX_gettimeofday          116
DECL|macro|__NR_HPUX_getrusage
mdefine_line|#define __NR_HPUX_getrusage             117
DECL|macro|__NR_HPUX_getsockopt_old
mdefine_line|#define __NR_HPUX_getsockopt_old        118
DECL|macro|__NR_HPUX_resuba_old
mdefine_line|#define __NR_HPUX_resuba_old            119
DECL|macro|__NR_HPUX_readv
mdefine_line|#define __NR_HPUX_readv                 120
DECL|macro|__NR_HPUX_writev
mdefine_line|#define __NR_HPUX_writev                121
DECL|macro|__NR_HPUX_settimeofday
mdefine_line|#define __NR_HPUX_settimeofday          122
DECL|macro|__NR_HPUX_fchown
mdefine_line|#define __NR_HPUX_fchown                123
DECL|macro|__NR_HPUX_fchmod
mdefine_line|#define __NR_HPUX_fchmod                124
DECL|macro|__NR_HPUX_recvfrom_old
mdefine_line|#define __NR_HPUX_recvfrom_old          125
DECL|macro|__NR_HPUX_setresuid
mdefine_line|#define __NR_HPUX_setresuid             126
DECL|macro|__NR_HPUX_setresgid
mdefine_line|#define __NR_HPUX_setresgid             127
DECL|macro|__NR_HPUX_rename
mdefine_line|#define __NR_HPUX_rename                128
DECL|macro|__NR_HPUX_truncate
mdefine_line|#define __NR_HPUX_truncate              129
DECL|macro|__NR_HPUX_ftruncate
mdefine_line|#define __NR_HPUX_ftruncate             130
DECL|macro|__NR_HPUX_flock_old
mdefine_line|#define __NR_HPUX_flock_old             131
DECL|macro|__NR_HPUX_sysconf
mdefine_line|#define __NR_HPUX_sysconf               132
DECL|macro|__NR_HPUX_sendto_old
mdefine_line|#define __NR_HPUX_sendto_old            133
DECL|macro|__NR_HPUX_shutdown_old
mdefine_line|#define __NR_HPUX_shutdown_old          134
DECL|macro|__NR_HPUX_socketpair_old
mdefine_line|#define __NR_HPUX_socketpair_old        135
DECL|macro|__NR_HPUX_mkdir
mdefine_line|#define __NR_HPUX_mkdir                 136
DECL|macro|__NR_HPUX_rmdir
mdefine_line|#define __NR_HPUX_rmdir                 137
DECL|macro|__NR_HPUX_utimes_old
mdefine_line|#define __NR_HPUX_utimes_old            138
DECL|macro|__NR_HPUX_sigcleanup_old
mdefine_line|#define __NR_HPUX_sigcleanup_old        139
DECL|macro|__NR_HPUX_setcore
mdefine_line|#define __NR_HPUX_setcore               140
DECL|macro|__NR_HPUX_getpeername_old
mdefine_line|#define __NR_HPUX_getpeername_old       141
DECL|macro|__NR_HPUX_gethostid
mdefine_line|#define __NR_HPUX_gethostid             142
DECL|macro|__NR_HPUX_sethostid
mdefine_line|#define __NR_HPUX_sethostid             143
DECL|macro|__NR_HPUX_getrlimit
mdefine_line|#define __NR_HPUX_getrlimit             144
DECL|macro|__NR_HPUX_setrlimit
mdefine_line|#define __NR_HPUX_setrlimit             145
DECL|macro|__NR_HPUX_killpg_old
mdefine_line|#define __NR_HPUX_killpg_old            146
DECL|macro|__NR_HPUX_cachectl
mdefine_line|#define __NR_HPUX_cachectl              147
DECL|macro|__NR_HPUX_quotactl
mdefine_line|#define __NR_HPUX_quotactl              148
DECL|macro|__NR_HPUX_get_sysinfo
mdefine_line|#define __NR_HPUX_get_sysinfo           149
DECL|macro|__NR_HPUX_getsockname_old
mdefine_line|#define __NR_HPUX_getsockname_old       150
DECL|macro|__NR_HPUX_privgrp
mdefine_line|#define __NR_HPUX_privgrp               151
DECL|macro|__NR_HPUX_rtprio
mdefine_line|#define __NR_HPUX_rtprio                152
DECL|macro|__NR_HPUX_plock
mdefine_line|#define __NR_HPUX_plock                 153
DECL|macro|__NR_HPUX_reserved3
mdefine_line|#define __NR_HPUX_reserved3             154
DECL|macro|__NR_HPUX_lockf
mdefine_line|#define __NR_HPUX_lockf                 155
DECL|macro|__NR_HPUX_semget
mdefine_line|#define __NR_HPUX_semget                156
DECL|macro|__NR_HPUX_osemctl
mdefine_line|#define __NR_HPUX_osemctl               157
DECL|macro|__NR_HPUX_semop
mdefine_line|#define __NR_HPUX_semop                 158
DECL|macro|__NR_HPUX_msgget
mdefine_line|#define __NR_HPUX_msgget                159
DECL|macro|__NR_HPUX_omsgctl
mdefine_line|#define __NR_HPUX_omsgctl               160
DECL|macro|__NR_HPUX_msgsnd
mdefine_line|#define __NR_HPUX_msgsnd                161
DECL|macro|__NR_HPUX_msgrecv
mdefine_line|#define __NR_HPUX_msgrecv               162
DECL|macro|__NR_HPUX_shmget
mdefine_line|#define __NR_HPUX_shmget                163
DECL|macro|__NR_HPUX_oshmctl
mdefine_line|#define __NR_HPUX_oshmctl               164
DECL|macro|__NR_HPUX_shmat
mdefine_line|#define __NR_HPUX_shmat                 165
DECL|macro|__NR_HPUX_shmdt
mdefine_line|#define __NR_HPUX_shmdt                 166
DECL|macro|__NR_HPUX_m68020_advise
mdefine_line|#define __NR_HPUX_m68020_advise         167
multiline_comment|/* [168,189] are for Discless/DUX */
DECL|macro|__NR_HPUX_csp
mdefine_line|#define __NR_HPUX_csp                   168
DECL|macro|__NR_HPUX_cluster
mdefine_line|#define __NR_HPUX_cluster               169
DECL|macro|__NR_HPUX_mkrnod
mdefine_line|#define __NR_HPUX_mkrnod                170
DECL|macro|__NR_HPUX_test
mdefine_line|#define __NR_HPUX_test                  171
DECL|macro|__NR_HPUX_unsp_open
mdefine_line|#define __NR_HPUX_unsp_open             172
DECL|macro|__NR_HPUX_reserved4
mdefine_line|#define __NR_HPUX_reserved4             173
DECL|macro|__NR_HPUX_getcontext_old
mdefine_line|#define __NR_HPUX_getcontext_old        174
DECL|macro|__NR_HPUX_osetcontext
mdefine_line|#define __NR_HPUX_osetcontext           175
DECL|macro|__NR_HPUX_bigio
mdefine_line|#define __NR_HPUX_bigio                 176
DECL|macro|__NR_HPUX_pipenode
mdefine_line|#define __NR_HPUX_pipenode              177
DECL|macro|__NR_HPUX_lsync
mdefine_line|#define __NR_HPUX_lsync                 178
DECL|macro|__NR_HPUX_getmachineid
mdefine_line|#define __NR_HPUX_getmachineid          179
DECL|macro|__NR_HPUX_cnodeid
mdefine_line|#define __NR_HPUX_cnodeid               180
DECL|macro|__NR_HPUX_cnodes
mdefine_line|#define __NR_HPUX_cnodes                181
DECL|macro|__NR_HPUX_swapclients
mdefine_line|#define __NR_HPUX_swapclients           182
DECL|macro|__NR_HPUX_rmt_process
mdefine_line|#define __NR_HPUX_rmt_process           183
DECL|macro|__NR_HPUX_dskless_stats
mdefine_line|#define __NR_HPUX_dskless_stats         184
DECL|macro|__NR_HPUX_sigprocmask
mdefine_line|#define __NR_HPUX_sigprocmask           185
DECL|macro|__NR_HPUX_sigpending
mdefine_line|#define __NR_HPUX_sigpending            186
DECL|macro|__NR_HPUX_sigsuspend
mdefine_line|#define __NR_HPUX_sigsuspend            187
DECL|macro|__NR_HPUX_sigaction
mdefine_line|#define __NR_HPUX_sigaction             188
DECL|macro|__NR_HPUX_reserved5
mdefine_line|#define __NR_HPUX_reserved5             189
DECL|macro|__NR_HPUX_nfssvc
mdefine_line|#define __NR_HPUX_nfssvc                190
DECL|macro|__NR_HPUX_getfh
mdefine_line|#define __NR_HPUX_getfh                 191
DECL|macro|__NR_HPUX_getdomainname
mdefine_line|#define __NR_HPUX_getdomainname         192
DECL|macro|__NR_HPUX_setdomainname
mdefine_line|#define __NR_HPUX_setdomainname         193
DECL|macro|__NR_HPUX_async_daemon
mdefine_line|#define __NR_HPUX_async_daemon          194
DECL|macro|__NR_HPUX_getdirentries
mdefine_line|#define __NR_HPUX_getdirentries         195
DECL|macro|__NR_HPUX_statfs
mdefine_line|#define __NR_HPUX_statfs                196
DECL|macro|__NR_HPUX_fstatfs
mdefine_line|#define __NR_HPUX_fstatfs               197
DECL|macro|__NR_HPUX_vfsmount
mdefine_line|#define __NR_HPUX_vfsmount              198
DECL|macro|__NR_HPUX_reserved6
mdefine_line|#define __NR_HPUX_reserved6             199
DECL|macro|__NR_HPUX_waitpid
mdefine_line|#define __NR_HPUX_waitpid               200
multiline_comment|/* 201 - 223 missing */
DECL|macro|__NR_HPUX_sigsetreturn
mdefine_line|#define __NR_HPUX_sigsetreturn          224
DECL|macro|__NR_HPUX_sigsetstatemask
mdefine_line|#define __NR_HPUX_sigsetstatemask       225
multiline_comment|/* 226 missing */
DECL|macro|__NR_HPUX_cs
mdefine_line|#define __NR_HPUX_cs                    227
DECL|macro|__NR_HPUX_cds
mdefine_line|#define __NR_HPUX_cds                   228
DECL|macro|__NR_HPUX_set_no_trunc
mdefine_line|#define __NR_HPUX_set_no_trunc          229
DECL|macro|__NR_HPUX_pathconf
mdefine_line|#define __NR_HPUX_pathconf              230
DECL|macro|__NR_HPUX_fpathconf
mdefine_line|#define __NR_HPUX_fpathconf             231
multiline_comment|/* 232, 233 missing */
DECL|macro|__NR_HPUX_nfs_fcntl
mdefine_line|#define __NR_HPUX_nfs_fcntl             234
DECL|macro|__NR_HPUX_ogetacl
mdefine_line|#define __NR_HPUX_ogetacl               235
DECL|macro|__NR_HPUX_ofgetacl
mdefine_line|#define __NR_HPUX_ofgetacl              236
DECL|macro|__NR_HPUX_osetacl
mdefine_line|#define __NR_HPUX_osetacl               237
DECL|macro|__NR_HPUX_ofsetacl
mdefine_line|#define __NR_HPUX_ofsetacl              238
DECL|macro|__NR_HPUX_pstat
mdefine_line|#define __NR_HPUX_pstat                 239
DECL|macro|__NR_HPUX_getaudid
mdefine_line|#define __NR_HPUX_getaudid              240
DECL|macro|__NR_HPUX_setaudid
mdefine_line|#define __NR_HPUX_setaudid              241
DECL|macro|__NR_HPUX_getaudproc
mdefine_line|#define __NR_HPUX_getaudproc            242
DECL|macro|__NR_HPUX_setaudproc
mdefine_line|#define __NR_HPUX_setaudproc            243
DECL|macro|__NR_HPUX_getevent
mdefine_line|#define __NR_HPUX_getevent              244
DECL|macro|__NR_HPUX_setevent
mdefine_line|#define __NR_HPUX_setevent              245
DECL|macro|__NR_HPUX_audwrite
mdefine_line|#define __NR_HPUX_audwrite              246
DECL|macro|__NR_HPUX_audswitch
mdefine_line|#define __NR_HPUX_audswitch             247
DECL|macro|__NR_HPUX_audctl
mdefine_line|#define __NR_HPUX_audctl                248
DECL|macro|__NR_HPUX_ogetaccess
mdefine_line|#define __NR_HPUX_ogetaccess            249
DECL|macro|__NR_HPUX_fsctl
mdefine_line|#define __NR_HPUX_fsctl                 250
multiline_comment|/* 251 - 258 missing */
DECL|macro|__NR_HPUX_swapfs
mdefine_line|#define __NR_HPUX_swapfs                259
DECL|macro|__NR_HPUX_fss
mdefine_line|#define __NR_HPUX_fss                   260
multiline_comment|/* 261 - 266 missing */
DECL|macro|__NR_HPUX_tsync
mdefine_line|#define __NR_HPUX_tsync                 267
DECL|macro|__NR_HPUX_getnumfds
mdefine_line|#define __NR_HPUX_getnumfds             268
DECL|macro|__NR_HPUX_poll
mdefine_line|#define __NR_HPUX_poll                  269
DECL|macro|__NR_HPUX_getmsg
mdefine_line|#define __NR_HPUX_getmsg                270
DECL|macro|__NR_HPUX_putmsg
mdefine_line|#define __NR_HPUX_putmsg                271
DECL|macro|__NR_HPUX_fchdir
mdefine_line|#define __NR_HPUX_fchdir                272
DECL|macro|__NR_HPUX_getmount_cnt
mdefine_line|#define __NR_HPUX_getmount_cnt          273
DECL|macro|__NR_HPUX_getmount_entry
mdefine_line|#define __NR_HPUX_getmount_entry        274
DECL|macro|__NR_HPUX_accept
mdefine_line|#define __NR_HPUX_accept                275
DECL|macro|__NR_HPUX_bind
mdefine_line|#define __NR_HPUX_bind                  276
DECL|macro|__NR_HPUX_connect
mdefine_line|#define __NR_HPUX_connect               277
DECL|macro|__NR_HPUX_getpeername
mdefine_line|#define __NR_HPUX_getpeername           278
DECL|macro|__NR_HPUX_getsockname
mdefine_line|#define __NR_HPUX_getsockname           279
DECL|macro|__NR_HPUX_getsockopt
mdefine_line|#define __NR_HPUX_getsockopt            280
DECL|macro|__NR_HPUX_listen
mdefine_line|#define __NR_HPUX_listen                281
DECL|macro|__NR_HPUX_recv
mdefine_line|#define __NR_HPUX_recv                  282
DECL|macro|__NR_HPUX_recvfrom
mdefine_line|#define __NR_HPUX_recvfrom              283
DECL|macro|__NR_HPUX_recvmsg
mdefine_line|#define __NR_HPUX_recvmsg               284
DECL|macro|__NR_HPUX_send
mdefine_line|#define __NR_HPUX_send                  285
DECL|macro|__NR_HPUX_sendmsg
mdefine_line|#define __NR_HPUX_sendmsg               286
DECL|macro|__NR_HPUX_sendto
mdefine_line|#define __NR_HPUX_sendto                287
DECL|macro|__NR_HPUX_setsockopt
mdefine_line|#define __NR_HPUX_setsockopt            288
DECL|macro|__NR_HPUX_shutdown
mdefine_line|#define __NR_HPUX_shutdown              289
DECL|macro|__NR_HPUX_socket
mdefine_line|#define __NR_HPUX_socket                290
DECL|macro|__NR_HPUX_socketpair
mdefine_line|#define __NR_HPUX_socketpair            291
DECL|macro|__NR_HPUX_proc_open
mdefine_line|#define __NR_HPUX_proc_open             292
DECL|macro|__NR_HPUX_proc_close
mdefine_line|#define __NR_HPUX_proc_close            293
DECL|macro|__NR_HPUX_proc_send
mdefine_line|#define __NR_HPUX_proc_send             294
DECL|macro|__NR_HPUX_proc_recv
mdefine_line|#define __NR_HPUX_proc_recv             295
DECL|macro|__NR_HPUX_proc_sendrecv
mdefine_line|#define __NR_HPUX_proc_sendrecv         296
DECL|macro|__NR_HPUX_proc_syscall
mdefine_line|#define __NR_HPUX_proc_syscall          297
multiline_comment|/* 298 - 311 missing */
DECL|macro|__NR_HPUX_semctl
mdefine_line|#define __NR_HPUX_semctl                312
DECL|macro|__NR_HPUX_msgctl
mdefine_line|#define __NR_HPUX_msgctl                313
DECL|macro|__NR_HPUX_shmctl
mdefine_line|#define __NR_HPUX_shmctl                314
DECL|macro|__NR_HPUX_mpctl
mdefine_line|#define __NR_HPUX_mpctl                 315
DECL|macro|__NR_HPUX_exportfs
mdefine_line|#define __NR_HPUX_exportfs              316
DECL|macro|__NR_HPUX_getpmsg
mdefine_line|#define __NR_HPUX_getpmsg               317
DECL|macro|__NR_HPUX_putpmsg
mdefine_line|#define __NR_HPUX_putpmsg               318
multiline_comment|/* 319 missing */
DECL|macro|__NR_HPUX_msync
mdefine_line|#define __NR_HPUX_msync                 320
DECL|macro|__NR_HPUX_msleep
mdefine_line|#define __NR_HPUX_msleep                321
DECL|macro|__NR_HPUX_mwakeup
mdefine_line|#define __NR_HPUX_mwakeup               322
DECL|macro|__NR_HPUX_msem_init
mdefine_line|#define __NR_HPUX_msem_init             323
DECL|macro|__NR_HPUX_msem_remove
mdefine_line|#define __NR_HPUX_msem_remove           324
DECL|macro|__NR_HPUX_adjtime
mdefine_line|#define __NR_HPUX_adjtime               325
DECL|macro|__NR_HPUX_kload
mdefine_line|#define __NR_HPUX_kload                 326
DECL|macro|__NR_HPUX_fattach
mdefine_line|#define __NR_HPUX_fattach               327
DECL|macro|__NR_HPUX_fdetach
mdefine_line|#define __NR_HPUX_fdetach               328
DECL|macro|__NR_HPUX_serialize
mdefine_line|#define __NR_HPUX_serialize             329
DECL|macro|__NR_HPUX_statvfs
mdefine_line|#define __NR_HPUX_statvfs               330
DECL|macro|__NR_HPUX_fstatvfs
mdefine_line|#define __NR_HPUX_fstatvfs              331
DECL|macro|__NR_HPUX_lchown
mdefine_line|#define __NR_HPUX_lchown                332
DECL|macro|__NR_HPUX_getsid
mdefine_line|#define __NR_HPUX_getsid                333
DECL|macro|__NR_HPUX_sysfs
mdefine_line|#define __NR_HPUX_sysfs                 334
multiline_comment|/* 335, 336 missing */
DECL|macro|__NR_HPUX_sched_setparam
mdefine_line|#define __NR_HPUX_sched_setparam        337
DECL|macro|__NR_HPUX_sched_getparam
mdefine_line|#define __NR_HPUX_sched_getparam        338
DECL|macro|__NR_HPUX_sched_setscheduler
mdefine_line|#define __NR_HPUX_sched_setscheduler    339
DECL|macro|__NR_HPUX_sched_getscheduler
mdefine_line|#define __NR_HPUX_sched_getscheduler    340
DECL|macro|__NR_HPUX_sched_yield
mdefine_line|#define __NR_HPUX_sched_yield           341
DECL|macro|__NR_HPUX_sched_get_priority_max
mdefine_line|#define __NR_HPUX_sched_get_priority_max 342
DECL|macro|__NR_HPUX_sched_get_priority_min
mdefine_line|#define __NR_HPUX_sched_get_priority_min 343
DECL|macro|__NR_HPUX_sched_rr_get_interval
mdefine_line|#define __NR_HPUX_sched_rr_get_interval 344
DECL|macro|__NR_HPUX_clock_settime
mdefine_line|#define __NR_HPUX_clock_settime         345
DECL|macro|__NR_HPUX_clock_gettime
mdefine_line|#define __NR_HPUX_clock_gettime         346
DECL|macro|__NR_HPUX_clock_getres
mdefine_line|#define __NR_HPUX_clock_getres          347
DECL|macro|__NR_HPUX_timer_create
mdefine_line|#define __NR_HPUX_timer_create          348
DECL|macro|__NR_HPUX_timer_delete
mdefine_line|#define __NR_HPUX_timer_delete          349
DECL|macro|__NR_HPUX_timer_settime
mdefine_line|#define __NR_HPUX_timer_settime         350
DECL|macro|__NR_HPUX_timer_gettime
mdefine_line|#define __NR_HPUX_timer_gettime         351
DECL|macro|__NR_HPUX_timer_getoverrun
mdefine_line|#define __NR_HPUX_timer_getoverrun      352
DECL|macro|__NR_HPUX_nanosleep
mdefine_line|#define __NR_HPUX_nanosleep             353
DECL|macro|__NR_HPUX_toolbox
mdefine_line|#define __NR_HPUX_toolbox               354
multiline_comment|/* 355 missing */
DECL|macro|__NR_HPUX_getdents
mdefine_line|#define __NR_HPUX_getdents              356
DECL|macro|__NR_HPUX_getcontext
mdefine_line|#define __NR_HPUX_getcontext            357
DECL|macro|__NR_HPUX_sysinfo
mdefine_line|#define __NR_HPUX_sysinfo               358
DECL|macro|__NR_HPUX_fcntl64
mdefine_line|#define __NR_HPUX_fcntl64               359
DECL|macro|__NR_HPUX_ftruncate64
mdefine_line|#define __NR_HPUX_ftruncate64           360
DECL|macro|__NR_HPUX_fstat64
mdefine_line|#define __NR_HPUX_fstat64               361
DECL|macro|__NR_HPUX_getdirentries64
mdefine_line|#define __NR_HPUX_getdirentries64       362
DECL|macro|__NR_HPUX_getrlimit64
mdefine_line|#define __NR_HPUX_getrlimit64           363
DECL|macro|__NR_HPUX_lockf64
mdefine_line|#define __NR_HPUX_lockf64               364
DECL|macro|__NR_HPUX_lseek64
mdefine_line|#define __NR_HPUX_lseek64               365
DECL|macro|__NR_HPUX_lstat64
mdefine_line|#define __NR_HPUX_lstat64               366
DECL|macro|__NR_HPUX_mmap64
mdefine_line|#define __NR_HPUX_mmap64                367
DECL|macro|__NR_HPUX_setrlimit64
mdefine_line|#define __NR_HPUX_setrlimit64           368
DECL|macro|__NR_HPUX_stat64
mdefine_line|#define __NR_HPUX_stat64                369
DECL|macro|__NR_HPUX_truncate64
mdefine_line|#define __NR_HPUX_truncate64            370
DECL|macro|__NR_HPUX_ulimit64
mdefine_line|#define __NR_HPUX_ulimit64              371
DECL|macro|__NR_HPUX_pread
mdefine_line|#define __NR_HPUX_pread                 372
DECL|macro|__NR_HPUX_preadv
mdefine_line|#define __NR_HPUX_preadv                373
DECL|macro|__NR_HPUX_pwrite
mdefine_line|#define __NR_HPUX_pwrite                374
DECL|macro|__NR_HPUX_pwritev
mdefine_line|#define __NR_HPUX_pwritev               375
DECL|macro|__NR_HPUX_pread64
mdefine_line|#define __NR_HPUX_pread64               376
DECL|macro|__NR_HPUX_preadv64
mdefine_line|#define __NR_HPUX_preadv64              377
DECL|macro|__NR_HPUX_pwrite64
mdefine_line|#define __NR_HPUX_pwrite64              378
DECL|macro|__NR_HPUX_pwritev64
mdefine_line|#define __NR_HPUX_pwritev64             379
DECL|macro|__NR_HPUX_setcontext
mdefine_line|#define __NR_HPUX_setcontext            380
DECL|macro|__NR_HPUX_sigaltstack
mdefine_line|#define __NR_HPUX_sigaltstack           381
DECL|macro|__NR_HPUX_waitid
mdefine_line|#define __NR_HPUX_waitid                382
DECL|macro|__NR_HPUX_setpgrp
mdefine_line|#define __NR_HPUX_setpgrp               383
DECL|macro|__NR_HPUX_recvmsg2
mdefine_line|#define __NR_HPUX_recvmsg2              384
DECL|macro|__NR_HPUX_sendmsg2
mdefine_line|#define __NR_HPUX_sendmsg2              385
DECL|macro|__NR_HPUX_socket2
mdefine_line|#define __NR_HPUX_socket2               386
DECL|macro|__NR_HPUX_socketpair2
mdefine_line|#define __NR_HPUX_socketpair2           387
DECL|macro|__NR_HPUX_setregid
mdefine_line|#define __NR_HPUX_setregid              388
DECL|macro|__NR_HPUX_lwp_create
mdefine_line|#define __NR_HPUX_lwp_create            389
DECL|macro|__NR_HPUX_lwp_terminate
mdefine_line|#define __NR_HPUX_lwp_terminate         390
DECL|macro|__NR_HPUX_lwp_wait
mdefine_line|#define __NR_HPUX_lwp_wait              391
DECL|macro|__NR_HPUX_lwp_suspend
mdefine_line|#define __NR_HPUX_lwp_suspend           392
DECL|macro|__NR_HPUX_lwp_resume
mdefine_line|#define __NR_HPUX_lwp_resume            393
multiline_comment|/* 394 missing */
DECL|macro|__NR_HPUX_lwp_abort_syscall
mdefine_line|#define __NR_HPUX_lwp_abort_syscall     395
DECL|macro|__NR_HPUX_lwp_info
mdefine_line|#define __NR_HPUX_lwp_info              396
DECL|macro|__NR_HPUX_lwp_kill
mdefine_line|#define __NR_HPUX_lwp_kill              397
DECL|macro|__NR_HPUX_ksleep
mdefine_line|#define __NR_HPUX_ksleep                398
DECL|macro|__NR_HPUX_kwakeup
mdefine_line|#define __NR_HPUX_kwakeup               399
multiline_comment|/* 400 missing */
DECL|macro|__NR_HPUX_pstat_getlwp
mdefine_line|#define __NR_HPUX_pstat_getlwp          401
DECL|macro|__NR_HPUX_lwp_exit
mdefine_line|#define __NR_HPUX_lwp_exit              402
DECL|macro|__NR_HPUX_lwp_continue
mdefine_line|#define __NR_HPUX_lwp_continue          403
DECL|macro|__NR_HPUX_getacl
mdefine_line|#define __NR_HPUX_getacl                404
DECL|macro|__NR_HPUX_fgetacl
mdefine_line|#define __NR_HPUX_fgetacl               405
DECL|macro|__NR_HPUX_setacl
mdefine_line|#define __NR_HPUX_setacl                406
DECL|macro|__NR_HPUX_fsetacl
mdefine_line|#define __NR_HPUX_fsetacl               407
DECL|macro|__NR_HPUX_getaccess
mdefine_line|#define __NR_HPUX_getaccess             408
DECL|macro|__NR_HPUX_lwp_mutex_init
mdefine_line|#define __NR_HPUX_lwp_mutex_init        409
DECL|macro|__NR_HPUX_lwp_mutex_lock_sys
mdefine_line|#define __NR_HPUX_lwp_mutex_lock_sys    410
DECL|macro|__NR_HPUX_lwp_mutex_unlock
mdefine_line|#define __NR_HPUX_lwp_mutex_unlock      411
DECL|macro|__NR_HPUX_lwp_cond_init
mdefine_line|#define __NR_HPUX_lwp_cond_init         412
DECL|macro|__NR_HPUX_lwp_cond_signal
mdefine_line|#define __NR_HPUX_lwp_cond_signal       413
DECL|macro|__NR_HPUX_lwp_cond_broadcast
mdefine_line|#define __NR_HPUX_lwp_cond_broadcast    414
DECL|macro|__NR_HPUX_lwp_cond_wait_sys
mdefine_line|#define __NR_HPUX_lwp_cond_wait_sys     415
DECL|macro|__NR_HPUX_lwp_getscheduler
mdefine_line|#define __NR_HPUX_lwp_getscheduler      416
DECL|macro|__NR_HPUX_lwp_setscheduler
mdefine_line|#define __NR_HPUX_lwp_setscheduler      417
DECL|macro|__NR_HPUX_lwp_getstate
mdefine_line|#define __NR_HPUX_lwp_getstate          418
DECL|macro|__NR_HPUX_lwp_setstate
mdefine_line|#define __NR_HPUX_lwp_setstate          419
DECL|macro|__NR_HPUX_lwp_detach
mdefine_line|#define __NR_HPUX_lwp_detach            420
DECL|macro|__NR_HPUX_mlock
mdefine_line|#define __NR_HPUX_mlock                 421
DECL|macro|__NR_HPUX_munlock
mdefine_line|#define __NR_HPUX_munlock               422
DECL|macro|__NR_HPUX_mlockall
mdefine_line|#define __NR_HPUX_mlockall              423
DECL|macro|__NR_HPUX_munlockall
mdefine_line|#define __NR_HPUX_munlockall            424
DECL|macro|__NR_HPUX_shm_open
mdefine_line|#define __NR_HPUX_shm_open              425
DECL|macro|__NR_HPUX_shm_unlink
mdefine_line|#define __NR_HPUX_shm_unlink            426
DECL|macro|__NR_HPUX_sigqueue
mdefine_line|#define __NR_HPUX_sigqueue              427
DECL|macro|__NR_HPUX_sigwaitinfo
mdefine_line|#define __NR_HPUX_sigwaitinfo           428
DECL|macro|__NR_HPUX_sigtimedwait
mdefine_line|#define __NR_HPUX_sigtimedwait          429
DECL|macro|__NR_HPUX_sigwait
mdefine_line|#define __NR_HPUX_sigwait               430
DECL|macro|__NR_HPUX_aio_read
mdefine_line|#define __NR_HPUX_aio_read              431
DECL|macro|__NR_HPUX_aio_write
mdefine_line|#define __NR_HPUX_aio_write             432
DECL|macro|__NR_HPUX_lio_listio
mdefine_line|#define __NR_HPUX_lio_listio            433
DECL|macro|__NR_HPUX_aio_error
mdefine_line|#define __NR_HPUX_aio_error             434
DECL|macro|__NR_HPUX_aio_return
mdefine_line|#define __NR_HPUX_aio_return            435
DECL|macro|__NR_HPUX_aio_cancel
mdefine_line|#define __NR_HPUX_aio_cancel            436
DECL|macro|__NR_HPUX_aio_suspend
mdefine_line|#define __NR_HPUX_aio_suspend           437
DECL|macro|__NR_HPUX_aio_fsync
mdefine_line|#define __NR_HPUX_aio_fsync             438
DECL|macro|__NR_HPUX_mq_open
mdefine_line|#define __NR_HPUX_mq_open               439
DECL|macro|__NR_HPUX_mq_close
mdefine_line|#define __NR_HPUX_mq_close              440
DECL|macro|__NR_HPUX_mq_unlink
mdefine_line|#define __NR_HPUX_mq_unlink             441
DECL|macro|__NR_HPUX_mq_send
mdefine_line|#define __NR_HPUX_mq_send               442
DECL|macro|__NR_HPUX_mq_receive
mdefine_line|#define __NR_HPUX_mq_receive            443
DECL|macro|__NR_HPUX_mq_notify
mdefine_line|#define __NR_HPUX_mq_notify             444
DECL|macro|__NR_HPUX_mq_setattr
mdefine_line|#define __NR_HPUX_mq_setattr            445
DECL|macro|__NR_HPUX_mq_getattr
mdefine_line|#define __NR_HPUX_mq_getattr            446
DECL|macro|__NR_HPUX_ksem_open
mdefine_line|#define __NR_HPUX_ksem_open             447
DECL|macro|__NR_HPUX_ksem_unlink
mdefine_line|#define __NR_HPUX_ksem_unlink           448
DECL|macro|__NR_HPUX_ksem_close
mdefine_line|#define __NR_HPUX_ksem_close            449
DECL|macro|__NR_HPUX_ksem_post
mdefine_line|#define __NR_HPUX_ksem_post             450
DECL|macro|__NR_HPUX_ksem_wait
mdefine_line|#define __NR_HPUX_ksem_wait             451
DECL|macro|__NR_HPUX_ksem_read
mdefine_line|#define __NR_HPUX_ksem_read             452
DECL|macro|__NR_HPUX_ksem_trywait
mdefine_line|#define __NR_HPUX_ksem_trywait          453
DECL|macro|__NR_HPUX_lwp_rwlock_init
mdefine_line|#define __NR_HPUX_lwp_rwlock_init       454
DECL|macro|__NR_HPUX_lwp_rwlock_destroy
mdefine_line|#define __NR_HPUX_lwp_rwlock_destroy    455
DECL|macro|__NR_HPUX_lwp_rwlock_rdlock_sys
mdefine_line|#define __NR_HPUX_lwp_rwlock_rdlock_sys 456
DECL|macro|__NR_HPUX_lwp_rwlock_wrlock_sys
mdefine_line|#define __NR_HPUX_lwp_rwlock_wrlock_sys 457
DECL|macro|__NR_HPUX_lwp_rwlock_tryrdlock
mdefine_line|#define __NR_HPUX_lwp_rwlock_tryrdlock  458
DECL|macro|__NR_HPUX_lwp_rwlock_trywrlock
mdefine_line|#define __NR_HPUX_lwp_rwlock_trywrlock  459
DECL|macro|__NR_HPUX_lwp_rwlock_unlock
mdefine_line|#define __NR_HPUX_lwp_rwlock_unlock     460
DECL|macro|__NR_HPUX_ttrace
mdefine_line|#define __NR_HPUX_ttrace                461
DECL|macro|__NR_HPUX_ttrace_wait
mdefine_line|#define __NR_HPUX_ttrace_wait           462
DECL|macro|__NR_HPUX_lf_wire_mem
mdefine_line|#define __NR_HPUX_lf_wire_mem           463
DECL|macro|__NR_HPUX_lf_unwire_mem
mdefine_line|#define __NR_HPUX_lf_unwire_mem         464
DECL|macro|__NR_HPUX_lf_send_pin_map
mdefine_line|#define __NR_HPUX_lf_send_pin_map       465
DECL|macro|__NR_HPUX_lf_free_buf
mdefine_line|#define __NR_HPUX_lf_free_buf           466
DECL|macro|__NR_HPUX_lf_wait_nq
mdefine_line|#define __NR_HPUX_lf_wait_nq            467
DECL|macro|__NR_HPUX_lf_wakeup_conn_q
mdefine_line|#define __NR_HPUX_lf_wakeup_conn_q      468
DECL|macro|__NR_HPUX_lf_unused
mdefine_line|#define __NR_HPUX_lf_unused             469
DECL|macro|__NR_HPUX_lwp_sema_init
mdefine_line|#define __NR_HPUX_lwp_sema_init         470
DECL|macro|__NR_HPUX_lwp_sema_post
mdefine_line|#define __NR_HPUX_lwp_sema_post         471
DECL|macro|__NR_HPUX_lwp_sema_wait
mdefine_line|#define __NR_HPUX_lwp_sema_wait         472
DECL|macro|__NR_HPUX_lwp_sema_trywait
mdefine_line|#define __NR_HPUX_lwp_sema_trywait      473
DECL|macro|__NR_HPUX_lwp_sema_destroy
mdefine_line|#define __NR_HPUX_lwp_sema_destroy      474
DECL|macro|__NR_HPUX_statvfs64
mdefine_line|#define __NR_HPUX_statvfs64             475
DECL|macro|__NR_HPUX_fstatvfs64
mdefine_line|#define __NR_HPUX_fstatvfs64            476
DECL|macro|__NR_HPUX_msh_register
mdefine_line|#define __NR_HPUX_msh_register          477
DECL|macro|__NR_HPUX_ptrace64
mdefine_line|#define __NR_HPUX_ptrace64              478
DECL|macro|__NR_HPUX_sendfile
mdefine_line|#define __NR_HPUX_sendfile              479
DECL|macro|__NR_HPUX_sendpath
mdefine_line|#define __NR_HPUX_sendpath              480
DECL|macro|__NR_HPUX_sendfile64
mdefine_line|#define __NR_HPUX_sendfile64            481
DECL|macro|__NR_HPUX_sendpath64
mdefine_line|#define __NR_HPUX_sendpath64            482
DECL|macro|__NR_HPUX_modload
mdefine_line|#define __NR_HPUX_modload               483
DECL|macro|__NR_HPUX_moduload
mdefine_line|#define __NR_HPUX_moduload              484
DECL|macro|__NR_HPUX_modpath
mdefine_line|#define __NR_HPUX_modpath               485
DECL|macro|__NR_HPUX_getksym
mdefine_line|#define __NR_HPUX_getksym               486
DECL|macro|__NR_HPUX_modadm
mdefine_line|#define __NR_HPUX_modadm                487
DECL|macro|__NR_HPUX_modstat
mdefine_line|#define __NR_HPUX_modstat               488
DECL|macro|__NR_HPUX_lwp_detached_exit
mdefine_line|#define __NR_HPUX_lwp_detached_exit     489
DECL|macro|__NR_HPUX_crashconf
mdefine_line|#define __NR_HPUX_crashconf             490
DECL|macro|__NR_HPUX_siginhibit
mdefine_line|#define __NR_HPUX_siginhibit            491
DECL|macro|__NR_HPUX_sigenable
mdefine_line|#define __NR_HPUX_sigenable             492
DECL|macro|__NR_HPUX_spuctl
mdefine_line|#define __NR_HPUX_spuctl                493
DECL|macro|__NR_HPUX_zerokernelsum
mdefine_line|#define __NR_HPUX_zerokernelsum         494
DECL|macro|__NR_HPUX_nfs_kstat
mdefine_line|#define __NR_HPUX_nfs_kstat             495
DECL|macro|__NR_HPUX_aio_read64
mdefine_line|#define __NR_HPUX_aio_read64            496
DECL|macro|__NR_HPUX_aio_write64
mdefine_line|#define __NR_HPUX_aio_write64           497
DECL|macro|__NR_HPUX_aio_error64
mdefine_line|#define __NR_HPUX_aio_error64           498
DECL|macro|__NR_HPUX_aio_return64
mdefine_line|#define __NR_HPUX_aio_return64          499
DECL|macro|__NR_HPUX_aio_cancel64
mdefine_line|#define __NR_HPUX_aio_cancel64          500
DECL|macro|__NR_HPUX_aio_suspend64
mdefine_line|#define __NR_HPUX_aio_suspend64         501
DECL|macro|__NR_HPUX_aio_fsync64
mdefine_line|#define __NR_HPUX_aio_fsync64           502
DECL|macro|__NR_HPUX_lio_listio64
mdefine_line|#define __NR_HPUX_lio_listio64          503
DECL|macro|__NR_HPUX_recv2
mdefine_line|#define __NR_HPUX_recv2                 504
DECL|macro|__NR_HPUX_recvfrom2
mdefine_line|#define __NR_HPUX_recvfrom2             505
DECL|macro|__NR_HPUX_send2
mdefine_line|#define __NR_HPUX_send2                 506
DECL|macro|__NR_HPUX_sendto2
mdefine_line|#define __NR_HPUX_sendto2               507
DECL|macro|__NR_HPUX_acl
mdefine_line|#define __NR_HPUX_acl                   508
DECL|macro|__NR_HPUX___cnx_p2p_ctl
mdefine_line|#define __NR_HPUX___cnx_p2p_ctl         509
DECL|macro|__NR_HPUX___cnx_gsched_ctl
mdefine_line|#define __NR_HPUX___cnx_gsched_ctl      510
DECL|macro|__NR_HPUX___cnx_pmon_ctl
mdefine_line|#define __NR_HPUX___cnx_pmon_ctl        511
DECL|macro|__NR_HPUX_syscalls
mdefine_line|#define __NR_HPUX_syscalls&t;&t;512
multiline_comment|/*&n; * Linux system call numbers.&n; *&n; * Cary Coutant says that we should just use another syscall gateway&n; * page to avoid clashing with the HPUX space, and I think he&squot;s right:&n; * it will would keep a branch out of our syscall entry path, at the&n; * very least.  If we decide to change it later, we can ``just&squot;&squot; tweak&n; * the LINUX_GATEWAY_ADDR define at the bottom and make __NR_Linux be&n; * 1024 or something.  Oh, and recompile libc. =)&n; *&n; * 64-bit HPUX binaries get the syscall gateway address passed in a register&n; * from the kernel at startup, which seems a sane strategy.&n; */
DECL|macro|__NR_Linux
mdefine_line|#define __NR_Linux                0
DECL|macro|__NR_syscall
mdefine_line|#define __NR_syscall              (__NR_Linux + 0)
DECL|macro|__NR_exit
mdefine_line|#define __NR_exit                 (__NR_Linux + 1)
DECL|macro|__NR_fork
mdefine_line|#define __NR_fork                 (__NR_Linux + 2)
DECL|macro|__NR_read
mdefine_line|#define __NR_read                 (__NR_Linux + 3)
DECL|macro|__NR_write
mdefine_line|#define __NR_write                (__NR_Linux + 4)
DECL|macro|__NR_open
mdefine_line|#define __NR_open                 (__NR_Linux + 5)
DECL|macro|__NR_close
mdefine_line|#define __NR_close                (__NR_Linux + 6)
DECL|macro|__NR_waitpid
mdefine_line|#define __NR_waitpid              (__NR_Linux + 7)
DECL|macro|__NR_creat
mdefine_line|#define __NR_creat                (__NR_Linux + 8)
DECL|macro|__NR_link
mdefine_line|#define __NR_link                 (__NR_Linux + 9)
DECL|macro|__NR_unlink
mdefine_line|#define __NR_unlink              (__NR_Linux + 10)
DECL|macro|__NR_execve
mdefine_line|#define __NR_execve              (__NR_Linux + 11)
DECL|macro|__NR_chdir
mdefine_line|#define __NR_chdir               (__NR_Linux + 12)
DECL|macro|__NR_time
mdefine_line|#define __NR_time                (__NR_Linux + 13)
DECL|macro|__NR_mknod
mdefine_line|#define __NR_mknod               (__NR_Linux + 14)
DECL|macro|__NR_chmod
mdefine_line|#define __NR_chmod               (__NR_Linux + 15)
DECL|macro|__NR_lchown
mdefine_line|#define __NR_lchown              (__NR_Linux + 16)
DECL|macro|__NR_socket
mdefine_line|#define __NR_socket              (__NR_Linux + 17)
DECL|macro|__NR_stat
mdefine_line|#define __NR_stat                (__NR_Linux + 18)
DECL|macro|__NR_lseek
mdefine_line|#define __NR_lseek               (__NR_Linux + 19)
DECL|macro|__NR_getpid
mdefine_line|#define __NR_getpid              (__NR_Linux + 20)
DECL|macro|__NR_mount
mdefine_line|#define __NR_mount               (__NR_Linux + 21)
DECL|macro|__NR_bind
mdefine_line|#define __NR_bind                (__NR_Linux + 22)
DECL|macro|__NR_setuid
mdefine_line|#define __NR_setuid              (__NR_Linux + 23)
DECL|macro|__NR_getuid
mdefine_line|#define __NR_getuid              (__NR_Linux + 24)
DECL|macro|__NR_stime
mdefine_line|#define __NR_stime               (__NR_Linux + 25)
DECL|macro|__NR_ptrace
mdefine_line|#define __NR_ptrace              (__NR_Linux + 26)
DECL|macro|__NR_alarm
mdefine_line|#define __NR_alarm               (__NR_Linux + 27)
DECL|macro|__NR_fstat
mdefine_line|#define __NR_fstat               (__NR_Linux + 28)
DECL|macro|__NR_pause
mdefine_line|#define __NR_pause               (__NR_Linux + 29)
DECL|macro|__NR_utime
mdefine_line|#define __NR_utime               (__NR_Linux + 30)
DECL|macro|__NR_connect
mdefine_line|#define __NR_connect             (__NR_Linux + 31)
DECL|macro|__NR_listen
mdefine_line|#define __NR_listen              (__NR_Linux + 32)
DECL|macro|__NR_access
mdefine_line|#define __NR_access              (__NR_Linux + 33)
DECL|macro|__NR_nice
mdefine_line|#define __NR_nice                (__NR_Linux + 34)
DECL|macro|__NR_accept
mdefine_line|#define __NR_accept              (__NR_Linux + 35)
DECL|macro|__NR_sync
mdefine_line|#define __NR_sync                (__NR_Linux + 36)
DECL|macro|__NR_kill
mdefine_line|#define __NR_kill                (__NR_Linux + 37)
DECL|macro|__NR_rename
mdefine_line|#define __NR_rename              (__NR_Linux + 38)
DECL|macro|__NR_mkdir
mdefine_line|#define __NR_mkdir               (__NR_Linux + 39)
DECL|macro|__NR_rmdir
mdefine_line|#define __NR_rmdir               (__NR_Linux + 40)
DECL|macro|__NR_dup
mdefine_line|#define __NR_dup                 (__NR_Linux + 41)
DECL|macro|__NR_pipe
mdefine_line|#define __NR_pipe                (__NR_Linux + 42)
DECL|macro|__NR_times
mdefine_line|#define __NR_times               (__NR_Linux + 43)
DECL|macro|__NR_getsockname
mdefine_line|#define __NR_getsockname         (__NR_Linux + 44)
DECL|macro|__NR_brk
mdefine_line|#define __NR_brk                 (__NR_Linux + 45)
DECL|macro|__NR_setgid
mdefine_line|#define __NR_setgid              (__NR_Linux + 46)
DECL|macro|__NR_getgid
mdefine_line|#define __NR_getgid              (__NR_Linux + 47)
DECL|macro|__NR_signal
mdefine_line|#define __NR_signal              (__NR_Linux + 48)
DECL|macro|__NR_geteuid
mdefine_line|#define __NR_geteuid             (__NR_Linux + 49)
DECL|macro|__NR_getegid
mdefine_line|#define __NR_getegid             (__NR_Linux + 50)
DECL|macro|__NR_acct
mdefine_line|#define __NR_acct                (__NR_Linux + 51)
DECL|macro|__NR_umount2
mdefine_line|#define __NR_umount2             (__NR_Linux + 52)
DECL|macro|__NR_getpeername
mdefine_line|#define __NR_getpeername         (__NR_Linux + 53)
DECL|macro|__NR_ioctl
mdefine_line|#define __NR_ioctl               (__NR_Linux + 54)
DECL|macro|__NR_fcntl
mdefine_line|#define __NR_fcntl               (__NR_Linux + 55)
DECL|macro|__NR_socketpair
mdefine_line|#define __NR_socketpair          (__NR_Linux + 56)
DECL|macro|__NR_setpgid
mdefine_line|#define __NR_setpgid             (__NR_Linux + 57)
DECL|macro|__NR_send
mdefine_line|#define __NR_send                (__NR_Linux + 58)
DECL|macro|__NR_uname
mdefine_line|#define __NR_uname               (__NR_Linux + 59)
DECL|macro|__NR_umask
mdefine_line|#define __NR_umask               (__NR_Linux + 60)
DECL|macro|__NR_chroot
mdefine_line|#define __NR_chroot              (__NR_Linux + 61)
DECL|macro|__NR_ustat
mdefine_line|#define __NR_ustat               (__NR_Linux + 62)
DECL|macro|__NR_dup2
mdefine_line|#define __NR_dup2                (__NR_Linux + 63)
DECL|macro|__NR_getppid
mdefine_line|#define __NR_getppid             (__NR_Linux + 64)
DECL|macro|__NR_getpgrp
mdefine_line|#define __NR_getpgrp             (__NR_Linux + 65)
DECL|macro|__NR_setsid
mdefine_line|#define __NR_setsid              (__NR_Linux + 66)
DECL|macro|__NR_pivot_root
mdefine_line|#define __NR_pivot_root          (__NR_Linux + 67)
DECL|macro|__NR_sgetmask
mdefine_line|#define __NR_sgetmask            (__NR_Linux + 68)
DECL|macro|__NR_ssetmask
mdefine_line|#define __NR_ssetmask            (__NR_Linux + 69)
DECL|macro|__NR_setreuid
mdefine_line|#define __NR_setreuid            (__NR_Linux + 70)
DECL|macro|__NR_setregid
mdefine_line|#define __NR_setregid            (__NR_Linux + 71)
DECL|macro|__NR_mincore
mdefine_line|#define __NR_mincore             (__NR_Linux + 72)
DECL|macro|__NR_sigpending
mdefine_line|#define __NR_sigpending          (__NR_Linux + 73)
DECL|macro|__NR_sethostname
mdefine_line|#define __NR_sethostname         (__NR_Linux + 74)
DECL|macro|__NR_setrlimit
mdefine_line|#define __NR_setrlimit           (__NR_Linux + 75)
DECL|macro|__NR_getrlimit
mdefine_line|#define __NR_getrlimit           (__NR_Linux + 76)
DECL|macro|__NR_getrusage
mdefine_line|#define __NR_getrusage           (__NR_Linux + 77)
DECL|macro|__NR_gettimeofday
mdefine_line|#define __NR_gettimeofday        (__NR_Linux + 78)
DECL|macro|__NR_settimeofday
mdefine_line|#define __NR_settimeofday        (__NR_Linux + 79)
DECL|macro|__NR_getgroups
mdefine_line|#define __NR_getgroups           (__NR_Linux + 80)
DECL|macro|__NR_setgroups
mdefine_line|#define __NR_setgroups           (__NR_Linux + 81)
DECL|macro|__NR_sendto
mdefine_line|#define __NR_sendto              (__NR_Linux + 82)
DECL|macro|__NR_symlink
mdefine_line|#define __NR_symlink             (__NR_Linux + 83)
DECL|macro|__NR_lstat
mdefine_line|#define __NR_lstat               (__NR_Linux + 84)
DECL|macro|__NR_readlink
mdefine_line|#define __NR_readlink            (__NR_Linux + 85)
DECL|macro|__NR_uselib
mdefine_line|#define __NR_uselib              (__NR_Linux + 86)
DECL|macro|__NR_swapon
mdefine_line|#define __NR_swapon              (__NR_Linux + 87)
DECL|macro|__NR_reboot
mdefine_line|#define __NR_reboot              (__NR_Linux + 88)
DECL|macro|__NR_readdir
mdefine_line|#define __NR_readdir             (__NR_Linux + 89)
DECL|macro|__NR_mmap
mdefine_line|#define __NR_mmap                (__NR_Linux + 90)
DECL|macro|__NR_munmap
mdefine_line|#define __NR_munmap              (__NR_Linux + 91)
DECL|macro|__NR_truncate
mdefine_line|#define __NR_truncate            (__NR_Linux + 92)
DECL|macro|__NR_ftruncate
mdefine_line|#define __NR_ftruncate           (__NR_Linux + 93)
DECL|macro|__NR_fchmod
mdefine_line|#define __NR_fchmod              (__NR_Linux + 94)
DECL|macro|__NR_fchown
mdefine_line|#define __NR_fchown              (__NR_Linux + 95)
DECL|macro|__NR_getpriority
mdefine_line|#define __NR_getpriority         (__NR_Linux + 96)
DECL|macro|__NR_setpriority
mdefine_line|#define __NR_setpriority         (__NR_Linux + 97)
DECL|macro|__NR_recv
mdefine_line|#define __NR_recv                (__NR_Linux + 98)
DECL|macro|__NR_statfs
mdefine_line|#define __NR_statfs              (__NR_Linux + 99)
DECL|macro|__NR_fstatfs
mdefine_line|#define __NR_fstatfs            (__NR_Linux + 100)
DECL|macro|__NR_ioperm
mdefine_line|#define __NR_ioperm             (__NR_Linux + 101)
DECL|macro|__NR_socketcall
mdefine_line|#define __NR_socketcall         (__NR_Linux + 102)
DECL|macro|__NR_syslog
mdefine_line|#define __NR_syslog             (__NR_Linux + 103)
DECL|macro|__NR_setitimer
mdefine_line|#define __NR_setitimer          (__NR_Linux + 104)
DECL|macro|__NR_getitimer
mdefine_line|#define __NR_getitimer          (__NR_Linux + 105)
DECL|macro|__NR_capget
mdefine_line|#define __NR_capget             (__NR_Linux + 106)
DECL|macro|__NR_capset
mdefine_line|#define __NR_capset             (__NR_Linux + 107)
DECL|macro|__NR_pread
mdefine_line|#define __NR_pread              (__NR_Linux + 108)
DECL|macro|__NR_pwrite
mdefine_line|#define __NR_pwrite             (__NR_Linux + 109)
DECL|macro|__NR_getcwd
mdefine_line|#define __NR_getcwd             (__NR_Linux + 110)
DECL|macro|__NR_vhangup
mdefine_line|#define __NR_vhangup            (__NR_Linux + 111)
DECL|macro|__NR_idle
mdefine_line|#define __NR_idle               (__NR_Linux + 112)
DECL|macro|__NR_vfork
mdefine_line|#define __NR_vfork              (__NR_Linux + 113)
DECL|macro|__NR_wait4
mdefine_line|#define __NR_wait4              (__NR_Linux + 114)
DECL|macro|__NR_swapoff
mdefine_line|#define __NR_swapoff            (__NR_Linux + 115)
DECL|macro|__NR_sysinfo
mdefine_line|#define __NR_sysinfo            (__NR_Linux + 116)
DECL|macro|__NR_shutdown
mdefine_line|#define __NR_shutdown           (__NR_Linux + 117)
DECL|macro|__NR_fsync
mdefine_line|#define __NR_fsync              (__NR_Linux + 118)
DECL|macro|__NR_madvise
mdefine_line|#define __NR_madvise            (__NR_Linux + 119)
DECL|macro|__NR_clone
mdefine_line|#define __NR_clone              (__NR_Linux + 120)
DECL|macro|__NR_setdomainname
mdefine_line|#define __NR_setdomainname      (__NR_Linux + 121)
DECL|macro|__NR_sendfile
mdefine_line|#define __NR_sendfile           (__NR_Linux + 122)
DECL|macro|__NR_recvfrom
mdefine_line|#define __NR_recvfrom           (__NR_Linux + 123)
DECL|macro|__NR_adjtimex
mdefine_line|#define __NR_adjtimex           (__NR_Linux + 124)
DECL|macro|__NR_mprotect
mdefine_line|#define __NR_mprotect           (__NR_Linux + 125)
DECL|macro|__NR_sigprocmask
mdefine_line|#define __NR_sigprocmask        (__NR_Linux + 126)
DECL|macro|__NR_create_module
mdefine_line|#define __NR_create_module      (__NR_Linux + 127)
DECL|macro|__NR_init_module
mdefine_line|#define __NR_init_module        (__NR_Linux + 128)
DECL|macro|__NR_delete_module
mdefine_line|#define __NR_delete_module      (__NR_Linux + 129)
DECL|macro|__NR_get_kernel_syms
mdefine_line|#define __NR_get_kernel_syms    (__NR_Linux + 130)
DECL|macro|__NR_quotactl
mdefine_line|#define __NR_quotactl           (__NR_Linux + 131)
DECL|macro|__NR_getpgid
mdefine_line|#define __NR_getpgid            (__NR_Linux + 132)
DECL|macro|__NR_fchdir
mdefine_line|#define __NR_fchdir             (__NR_Linux + 133)
DECL|macro|__NR_bdflush
mdefine_line|#define __NR_bdflush            (__NR_Linux + 134)
DECL|macro|__NR_sysfs
mdefine_line|#define __NR_sysfs              (__NR_Linux + 135)
DECL|macro|__NR_personality
mdefine_line|#define __NR_personality        (__NR_Linux + 136)
DECL|macro|__NR_afs_syscall
mdefine_line|#define __NR_afs_syscall        (__NR_Linux + 137) /* Syscall for Andrew File System */
DECL|macro|__NR_setfsuid
mdefine_line|#define __NR_setfsuid           (__NR_Linux + 138)
DECL|macro|__NR_setfsgid
mdefine_line|#define __NR_setfsgid           (__NR_Linux + 139)
DECL|macro|__NR__llseek
mdefine_line|#define __NR__llseek            (__NR_Linux + 140)
DECL|macro|__NR_getdents
mdefine_line|#define __NR_getdents           (__NR_Linux + 141)
DECL|macro|__NR__newselect
mdefine_line|#define __NR__newselect         (__NR_Linux + 142)
DECL|macro|__NR_flock
mdefine_line|#define __NR_flock              (__NR_Linux + 143)
DECL|macro|__NR_msync
mdefine_line|#define __NR_msync              (__NR_Linux + 144)
DECL|macro|__NR_readv
mdefine_line|#define __NR_readv              (__NR_Linux + 145)
DECL|macro|__NR_writev
mdefine_line|#define __NR_writev             (__NR_Linux + 146)
DECL|macro|__NR_getsid
mdefine_line|#define __NR_getsid             (__NR_Linux + 147)
DECL|macro|__NR_fdatasync
mdefine_line|#define __NR_fdatasync          (__NR_Linux + 148)
DECL|macro|__NR__sysctl
mdefine_line|#define __NR__sysctl            (__NR_Linux + 149)
DECL|macro|__NR_mlock
mdefine_line|#define __NR_mlock              (__NR_Linux + 150)
DECL|macro|__NR_munlock
mdefine_line|#define __NR_munlock            (__NR_Linux + 151)
DECL|macro|__NR_mlockall
mdefine_line|#define __NR_mlockall           (__NR_Linux + 152)
DECL|macro|__NR_munlockall
mdefine_line|#define __NR_munlockall         (__NR_Linux + 153)
DECL|macro|__NR_sched_setparam
mdefine_line|#define __NR_sched_setparam             (__NR_Linux + 154)
DECL|macro|__NR_sched_getparam
mdefine_line|#define __NR_sched_getparam             (__NR_Linux + 155)
DECL|macro|__NR_sched_setscheduler
mdefine_line|#define __NR_sched_setscheduler         (__NR_Linux + 156)
DECL|macro|__NR_sched_getscheduler
mdefine_line|#define __NR_sched_getscheduler         (__NR_Linux + 157)
DECL|macro|__NR_sched_yield
mdefine_line|#define __NR_sched_yield                (__NR_Linux + 158)
DECL|macro|__NR_sched_get_priority_max
mdefine_line|#define __NR_sched_get_priority_max     (__NR_Linux + 159)
DECL|macro|__NR_sched_get_priority_min
mdefine_line|#define __NR_sched_get_priority_min     (__NR_Linux + 160)
DECL|macro|__NR_sched_rr_get_interval
mdefine_line|#define __NR_sched_rr_get_interval      (__NR_Linux + 161)
DECL|macro|__NR_nanosleep
mdefine_line|#define __NR_nanosleep          (__NR_Linux + 162)
DECL|macro|__NR_mremap
mdefine_line|#define __NR_mremap             (__NR_Linux + 163)
DECL|macro|__NR_setresuid
mdefine_line|#define __NR_setresuid          (__NR_Linux + 164)
DECL|macro|__NR_getresuid
mdefine_line|#define __NR_getresuid          (__NR_Linux + 165)
DECL|macro|__NR_sigaltstack
mdefine_line|#define __NR_sigaltstack        (__NR_Linux + 166)
DECL|macro|__NR_query_module
mdefine_line|#define __NR_query_module       (__NR_Linux + 167)
DECL|macro|__NR_poll
mdefine_line|#define __NR_poll               (__NR_Linux + 168)
DECL|macro|__NR_nfsservctl
mdefine_line|#define __NR_nfsservctl         (__NR_Linux + 169)
DECL|macro|__NR_setresgid
mdefine_line|#define __NR_setresgid          (__NR_Linux + 170)
DECL|macro|__NR_getresgid
mdefine_line|#define __NR_getresgid          (__NR_Linux + 171)
DECL|macro|__NR_prctl
mdefine_line|#define __NR_prctl              (__NR_Linux + 172)
DECL|macro|__NR_rt_sigreturn
mdefine_line|#define __NR_rt_sigreturn       (__NR_Linux + 173)
DECL|macro|__NR_rt_sigaction
mdefine_line|#define __NR_rt_sigaction       (__NR_Linux + 174)
DECL|macro|__NR_rt_sigprocmask
mdefine_line|#define __NR_rt_sigprocmask     (__NR_Linux + 175)
DECL|macro|__NR_rt_sigpending
mdefine_line|#define __NR_rt_sigpending      (__NR_Linux + 176)
DECL|macro|__NR_rt_sigtimedwait
mdefine_line|#define __NR_rt_sigtimedwait    (__NR_Linux + 177)
DECL|macro|__NR_rt_sigqueueinfo
mdefine_line|#define __NR_rt_sigqueueinfo    (__NR_Linux + 178)
DECL|macro|__NR_rt_sigsuspend
mdefine_line|#define __NR_rt_sigsuspend      (__NR_Linux + 179)
DECL|macro|__NR_chown
mdefine_line|#define __NR_chown              (__NR_Linux + 180)
DECL|macro|__NR_setsockopt
mdefine_line|#define __NR_setsockopt         (__NR_Linux + 181)
DECL|macro|__NR_getsockopt
mdefine_line|#define __NR_getsockopt         (__NR_Linux + 182)
DECL|macro|__NR_sendmsg
mdefine_line|#define __NR_sendmsg            (__NR_Linux + 183)
DECL|macro|__NR_recvmsg
mdefine_line|#define __NR_recvmsg            (__NR_Linux + 184)
DECL|macro|__NR_semop
mdefine_line|#define __NR_semop              (__NR_Linux + 185)
DECL|macro|__NR_semget
mdefine_line|#define __NR_semget             (__NR_Linux + 186)
DECL|macro|__NR_semctl
mdefine_line|#define __NR_semctl             (__NR_Linux + 187)
DECL|macro|__NR_msgsnd
mdefine_line|#define __NR_msgsnd             (__NR_Linux + 188)
DECL|macro|__NR_msgrcv
mdefine_line|#define __NR_msgrcv             (__NR_Linux + 189)
DECL|macro|__NR_msgget
mdefine_line|#define __NR_msgget             (__NR_Linux + 190)
DECL|macro|__NR_msgctl
mdefine_line|#define __NR_msgctl             (__NR_Linux + 191)
DECL|macro|__NR_shmat
mdefine_line|#define __NR_shmat              (__NR_Linux + 192)
DECL|macro|__NR_shmdt
mdefine_line|#define __NR_shmdt              (__NR_Linux + 193)
DECL|macro|__NR_shmget
mdefine_line|#define __NR_shmget             (__NR_Linux + 194)
DECL|macro|__NR_shmctl
mdefine_line|#define __NR_shmctl             (__NR_Linux + 195)
DECL|macro|__NR_getpmsg
mdefine_line|#define __NR_getpmsg            (__NR_Linux + 196)      /* some people actually want streams */
DECL|macro|__NR_putpmsg
mdefine_line|#define __NR_putpmsg            (__NR_Linux + 197)      /* some people actually want streams */
DECL|macro|__NR_Linux_syscalls
mdefine_line|#define __NR_Linux_syscalls     197
DECL|macro|HPUX_GATEWAY_ADDR
mdefine_line|#define HPUX_GATEWAY_ADDR       0xC0000004
DECL|macro|LINUX_GATEWAY_ADDR
mdefine_line|#define LINUX_GATEWAY_ADDR      0x100
DECL|macro|LINUX_GATEWAY_STR
mdefine_line|#define LINUX_GATEWAY_STR       &quot;0x100&quot;
multiline_comment|/* The old syscall code here didn&squot;t work, and it looks like it&squot;s only used&n; * by applications such as fdisk which for some reason need to produce&n; * their own syscall instead of using same from libc.  The code below&n; * is leveraged from glibc/sysdeps/unix/sysv/linux/hppa/sysdep.h where&n; * it is essentially duplicated -- which sucks.  -PB&n; */
DECL|macro|SYS_ify
mdefine_line|#define SYS_ify(syscall_name)   __NR_##syscall_name
multiline_comment|/* The system call number MUST ALWAYS be loaded in the delay slot of&n;   the ble instruction, or restarting system calls WILL NOT WORK.  See&n;   arch/parisc/kernel/signal.c - dhd, 2000-07-26 */
DECL|macro|K_INLINE_SYSCALL
mdefine_line|#define K_INLINE_SYSCALL(name, nr, args...)       ({              &bslash;&n;        unsigned long __sys_res;                                &bslash;&n;        {                                                       &bslash;&n;                register unsigned long __res asm(&quot;r28&quot;);        &bslash;&n;                K_LOAD_ARGS_##nr(args)                            &bslash;&n;                asm volatile(                                   &bslash;&n;&t;&t;&t;&quot;ble  0x100(%%sr2, %%r0)&bslash;n&bslash;t&quot;           &bslash;&n;                        &quot; ldi %1, %%r20&quot;                        &bslash;&n;                        : &quot;=r&quot; (__res)                          &bslash;&n;                        : &quot;i&quot; (SYS_ify(name)) K_ASM_ARGS_##nr   &bslash;&n;&t;&t;&t;  );                                    &bslash;&n;                __sys_res = __res;                              &bslash;&n;        }                                                       &bslash;&n;        if (__sys_res &gt;= (unsigned long)-4095) {                &bslash;&n;&t;&t;errno = -__sys_res;&t;&t;&t;&t;&bslash;&n;                __sys_res == (unsigned long)-1;                 &bslash;&n;        }                                                       &bslash;&n;        __sys_res;                                              &bslash;&n;})
DECL|macro|K_LOAD_ARGS_0
mdefine_line|#define K_LOAD_ARGS_0()
DECL|macro|K_LOAD_ARGS_1
mdefine_line|#define K_LOAD_ARGS_1(r26)                                        &bslash;&n;        register unsigned long __r26 __asm__(&quot;r26&quot;) = (unsigned long)r26;       &bslash;&n;        K_LOAD_ARGS_0()
DECL|macro|K_LOAD_ARGS_2
mdefine_line|#define K_LOAD_ARGS_2(r26,r25)                                    &bslash;&n;        register unsigned long __r25 __asm__(&quot;r25&quot;) = (unsigned long)r25;       &bslash;&n;        K_LOAD_ARGS_1(r26)
DECL|macro|K_LOAD_ARGS_3
mdefine_line|#define K_LOAD_ARGS_3(r26,r25,r24)                                &bslash;&n;        register unsigned long __r24 __asm__(&quot;r24&quot;) = (unsigned long)r24;       &bslash;&n;        K_LOAD_ARGS_2(r26,r25)
DECL|macro|K_LOAD_ARGS_4
mdefine_line|#define K_LOAD_ARGS_4(r26,r25,r24,r23)                            &bslash;&n;        register unsigned long __r23 __asm__(&quot;r23&quot;) = (unsigned long)r23;       &bslash;&n;        K_LOAD_ARGS_3(r26,r25,r24)
DECL|macro|K_LOAD_ARGS_5
mdefine_line|#define K_LOAD_ARGS_5(r26,r25,r24,r23,r22)                        &bslash;&n;        register unsigned long __r22 __asm__(&quot;r22&quot;) = (unsigned long)r22;       &bslash;&n;        K_LOAD_ARGS_4(r26,r25,r24,r23)
DECL|macro|K_LOAD_ARGS_6
mdefine_line|#define K_LOAD_ARGS_6(r26,r25,r24,r23,r22,r21)                    &bslash;&n;        register unsigned long __r21 __asm__(&quot;r21&quot;) = (unsigned long)r21;       &bslash;&n;        K_LOAD_ARGS_5(r26,r25,r24,r23,r22)
DECL|macro|K_ASM_ARGS_0
mdefine_line|#define K_ASM_ARGS_0
DECL|macro|K_ASM_ARGS_1
mdefine_line|#define K_ASM_ARGS_1 , &quot;r&quot; (__r26)
DECL|macro|K_ASM_ARGS_2
mdefine_line|#define K_ASM_ARGS_2 , &quot;r&quot; (__r26), &quot;r&quot; (__r25)
DECL|macro|K_ASM_ARGS_3
mdefine_line|#define K_ASM_ARGS_3 , &quot;r&quot; (__r26), &quot;r&quot; (__r25), &quot;r&quot; (__r24)
DECL|macro|K_ASM_ARGS_4
mdefine_line|#define K_ASM_ARGS_4 , &quot;r&quot; (__r26), &quot;r&quot; (__r25), &quot;r&quot; (__r24), &quot;r&quot; (__r23)
DECL|macro|K_ASM_ARGS_5
mdefine_line|#define K_ASM_ARGS_5 , &quot;r&quot; (__r26), &quot;r&quot; (__r25), &quot;r&quot; (__r24), &quot;r&quot; (__r23), &quot;r&quot; (__r22)
DECL|macro|K_ASM_ARGS_6
mdefine_line|#define K_ASM_ARGS_6 , &quot;r&quot; (__r26), &quot;r&quot; (__r25), &quot;r&quot; (__r24), &quot;r&quot; (__r23), &quot;r&quot; (__r22), &quot;r&quot; (__r21)
DECL|macro|_syscall0
mdefine_line|#define _syscall0(type,name)&t;&t;&t;&t;&t;&t;      &bslash;&n;type name(void)&t;&t;&t;&t;&t;&t;&t;&t;      &bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;      &bslash;&n;    return K_INLINE_SYSCALL(name, 0);&t;&bslash;&n;}
DECL|macro|_syscall1
mdefine_line|#define _syscall1(type,name,type1,arg1)&t;&t;&t;&t;&t;      &bslash;&n;type name(type1 arg1)&t;&t;&t;&t;&t;&t;&t;      &bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;      &bslash;&n;    return K_INLINE_SYSCALL(name, 1, arg1);&t;&bslash;&n;}
DECL|macro|_syscall2
mdefine_line|#define _syscall2(type,name,type1,arg1,type2,arg2)&t;&t;&t;      &bslash;&n;type name(type1 arg1, type2 arg2)&t;&t;&t;&t;&t;      &bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;      &bslash;&n;    return K_INLINE_SYSCALL(name, 2, arg1, arg2);&t;&bslash;&n;}
DECL|macro|_syscall3
mdefine_line|#define _syscall3(type,name,type1,arg1,type2,arg2,type3,arg3)&t;&t;      &bslash;&n;type name(type1 arg1, type2 arg2, type3 arg3)&t;&t;&t;&t;      &bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;      &bslash;&n;    return K_INLINE_SYSCALL(name, 3, arg1, arg2, arg3);&t;&bslash;&n;}
DECL|macro|_syscall4
mdefine_line|#define _syscall4(type,name,type1,arg1,type2,arg2,type3,arg3,type4,arg4)      &bslash;&n;type name(type1 arg1, type2 arg2, type3 arg3, type4 arg4)&t;&t;      &bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;      &bslash;&n;    return K_INLINE_SYSCALL(name, 4, arg1, arg2, arg3, arg4);&t;&bslash;&n;}
multiline_comment|/* select takes 5 arguments */
DECL|macro|_syscall5
mdefine_line|#define _syscall5(type,name,type1,arg1,type2,arg2,type3,arg3,type4,arg4,type5,arg5) &bslash;&n;type name(type1 arg1, type2 arg2, type3 arg3, type4 arg4, type5 arg5)&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    return K_INLINE_SYSCALL(name, 5, arg1, arg2, arg3, arg4, arg5);&t;&bslash;&n;}
multiline_comment|/* mmap takes 6 arguments */
DECL|macro|_syscall6
mdefine_line|#define _syscall6(type,name,type1,arg1,type2,arg2,type3,arg3,type4,arg4,type5,arg5,type6,arg6) &bslash;&n;type name(type1 arg1, type2 arg2, type3 arg3, type4 arg4, type5 arg5, type6 arg6) &bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    return K_INLINE_SYSCALL(name, 6, arg1, arg2, arg3, arg4, arg5, arg6);&t;&bslash;&n;}
macro_line|#ifdef __KERNEL_SYSCALLS__
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
r_extern
r_int
id|sys_wait4
c_func
(paren
r_int
comma
r_int
op_star
comma
r_int
comma
r_struct
id|rusage
op_star
)paren
suffix:semicolon
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
r_extern
r_int
id|sys_wait4
c_func
(paren
r_int
comma
r_int
op_star
comma
r_int
comma
r_struct
id|rusage
op_star
)paren
suffix:semicolon
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
DECL|function|execve
r_static
r_inline
r_int
id|execve
c_func
(paren
r_char
op_star
id|filename
comma
r_char
op_star
id|argv
(braket
)braket
comma
r_char
op_star
id|envp
(braket
)braket
)paren
(brace
r_extern
r_int
id|__execve
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
comma
r_struct
id|task_struct
op_star
)paren
suffix:semicolon
r_return
id|__execve
c_func
(paren
id|filename
comma
id|argv
comma
id|envp
comma
id|current
)paren
suffix:semicolon
)brace
macro_line|#endif
DECL|macro|STR
macro_line|#undef STR
macro_line|#endif /* _ASM_PARISC_UNISTD_H_ */
eof
