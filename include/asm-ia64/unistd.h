macro_line|#ifndef _ASM_IA64_UNISTD_H
DECL|macro|_ASM_IA64_UNISTD_H
mdefine_line|#define _ASM_IA64_UNISTD_H
multiline_comment|/*&n; * IA-64 Linux syscall numbers and inline-functions.&n; *&n; * Copyright (C) 1998-2002 Hewlett-Packard Co&n; *&t;David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; */
macro_line|#include &lt;asm/break.h&gt;
DECL|macro|__BREAK_SYSCALL
mdefine_line|#define __BREAK_SYSCALL&t;&t;&t;__IA64_BREAK_SYSCALL
DECL|macro|__NR_ni_syscall
mdefine_line|#define __NR_ni_syscall&t;&t;&t;1024
DECL|macro|__NR_exit
mdefine_line|#define __NR_exit&t;&t;&t;1025
DECL|macro|__NR_read
mdefine_line|#define __NR_read&t;&t;&t;1026
DECL|macro|__NR_write
mdefine_line|#define __NR_write&t;&t;&t;1027
DECL|macro|__NR_open
mdefine_line|#define __NR_open&t;&t;&t;1028
DECL|macro|__NR_close
mdefine_line|#define __NR_close&t;&t;&t;1029
DECL|macro|__NR_creat
mdefine_line|#define __NR_creat&t;&t;&t;1030
DECL|macro|__NR_link
mdefine_line|#define __NR_link&t;&t;&t;1031
DECL|macro|__NR_unlink
mdefine_line|#define __NR_unlink&t;&t;&t;1032
DECL|macro|__NR_execve
mdefine_line|#define __NR_execve&t;&t;&t;1033
DECL|macro|__NR_chdir
mdefine_line|#define __NR_chdir&t;&t;&t;1034
DECL|macro|__NR_fchdir
mdefine_line|#define __NR_fchdir&t;&t;&t;1035
DECL|macro|__NR_utimes
mdefine_line|#define __NR_utimes&t;&t;&t;1036
DECL|macro|__NR_mknod
mdefine_line|#define __NR_mknod&t;&t;&t;1037
DECL|macro|__NR_chmod
mdefine_line|#define __NR_chmod&t;&t;&t;1038
DECL|macro|__NR_chown
mdefine_line|#define __NR_chown&t;&t;&t;1039
DECL|macro|__NR_lseek
mdefine_line|#define __NR_lseek&t;&t;&t;1040
DECL|macro|__NR_getpid
mdefine_line|#define __NR_getpid&t;&t;&t;1041
DECL|macro|__NR_getppid
mdefine_line|#define __NR_getppid&t;&t;&t;1042
DECL|macro|__NR_mount
mdefine_line|#define __NR_mount&t;&t;&t;1043
DECL|macro|__NR_umount
mdefine_line|#define __NR_umount&t;&t;&t;1044
DECL|macro|__NR_setuid
mdefine_line|#define __NR_setuid&t;&t;&t;1045
DECL|macro|__NR_getuid
mdefine_line|#define __NR_getuid&t;&t;&t;1046
DECL|macro|__NR_geteuid
mdefine_line|#define __NR_geteuid&t;&t;&t;1047
DECL|macro|__NR_ptrace
mdefine_line|#define __NR_ptrace&t;&t;&t;1048
DECL|macro|__NR_access
mdefine_line|#define __NR_access&t;&t;&t;1049
DECL|macro|__NR_sync
mdefine_line|#define __NR_sync&t;&t;&t;1050
DECL|macro|__NR_fsync
mdefine_line|#define __NR_fsync&t;&t;&t;1051
DECL|macro|__NR_fdatasync
mdefine_line|#define __NR_fdatasync&t;&t;&t;1052
DECL|macro|__NR_kill
mdefine_line|#define __NR_kill&t;&t;&t;1053
DECL|macro|__NR_rename
mdefine_line|#define __NR_rename&t;&t;&t;1054
DECL|macro|__NR_mkdir
mdefine_line|#define __NR_mkdir&t;&t;&t;1055
DECL|macro|__NR_rmdir
mdefine_line|#define __NR_rmdir&t;&t;&t;1056
DECL|macro|__NR_dup
mdefine_line|#define __NR_dup&t;&t;&t;1057
DECL|macro|__NR_pipe
mdefine_line|#define __NR_pipe&t;&t;&t;1058
DECL|macro|__NR_times
mdefine_line|#define __NR_times&t;&t;&t;1059
DECL|macro|__NR_brk
mdefine_line|#define __NR_brk&t;&t;&t;1060
DECL|macro|__NR_setgid
mdefine_line|#define __NR_setgid&t;&t;&t;1061
DECL|macro|__NR_getgid
mdefine_line|#define __NR_getgid&t;&t;&t;1062
DECL|macro|__NR_getegid
mdefine_line|#define __NR_getegid&t;&t;&t;1063
DECL|macro|__NR_acct
mdefine_line|#define __NR_acct&t;&t;&t;1064
DECL|macro|__NR_ioctl
mdefine_line|#define __NR_ioctl&t;&t;&t;1065
DECL|macro|__NR_fcntl
mdefine_line|#define __NR_fcntl&t;&t;&t;1066
DECL|macro|__NR_umask
mdefine_line|#define __NR_umask&t;&t;&t;1067
DECL|macro|__NR_chroot
mdefine_line|#define __NR_chroot&t;&t;&t;1068
DECL|macro|__NR_ustat
mdefine_line|#define __NR_ustat&t;&t;&t;1069
DECL|macro|__NR_dup2
mdefine_line|#define __NR_dup2&t;&t;&t;1070
DECL|macro|__NR_setreuid
mdefine_line|#define __NR_setreuid&t;&t;&t;1071
DECL|macro|__NR_setregid
mdefine_line|#define __NR_setregid&t;&t;&t;1072
DECL|macro|__NR_getresuid
mdefine_line|#define __NR_getresuid&t;&t;&t;1073
DECL|macro|__NR_setresuid
mdefine_line|#define __NR_setresuid&t;&t;&t;1074
DECL|macro|__NR_getresgid
mdefine_line|#define __NR_getresgid&t;&t;&t;1075
DECL|macro|__NR_setresgid
mdefine_line|#define __NR_setresgid&t;&t;&t;1076
DECL|macro|__NR_getgroups
mdefine_line|#define __NR_getgroups&t;&t;&t;1077
DECL|macro|__NR_setgroups
mdefine_line|#define __NR_setgroups&t;&t;&t;1078
DECL|macro|__NR_getpgid
mdefine_line|#define __NR_getpgid&t;&t;&t;1079
DECL|macro|__NR_setpgid
mdefine_line|#define __NR_setpgid&t;&t;&t;1080
DECL|macro|__NR_setsid
mdefine_line|#define __NR_setsid&t;&t;&t;1081
DECL|macro|__NR_getsid
mdefine_line|#define __NR_getsid&t;&t;&t;1082
DECL|macro|__NR_sethostname
mdefine_line|#define __NR_sethostname&t;&t;1083
DECL|macro|__NR_setrlimit
mdefine_line|#define __NR_setrlimit&t;&t;&t;1084
DECL|macro|__NR_getrlimit
mdefine_line|#define __NR_getrlimit&t;&t;&t;1085
DECL|macro|__NR_getrusage
mdefine_line|#define __NR_getrusage&t;&t;&t;1086
DECL|macro|__NR_gettimeofday
mdefine_line|#define __NR_gettimeofday&t;&t;1087
DECL|macro|__NR_settimeofday
mdefine_line|#define __NR_settimeofday&t;&t;1088
DECL|macro|__NR_select
mdefine_line|#define __NR_select&t;&t;&t;1089
DECL|macro|__NR_poll
mdefine_line|#define __NR_poll&t;&t;&t;1090
DECL|macro|__NR_symlink
mdefine_line|#define __NR_symlink&t;&t;&t;1091
DECL|macro|__NR_readlink
mdefine_line|#define __NR_readlink&t;&t;&t;1092
DECL|macro|__NR_uselib
mdefine_line|#define __NR_uselib&t;&t;&t;1093
DECL|macro|__NR_swapon
mdefine_line|#define __NR_swapon&t;&t;&t;1094
DECL|macro|__NR_swapoff
mdefine_line|#define __NR_swapoff&t;&t;&t;1095
DECL|macro|__NR_reboot
mdefine_line|#define __NR_reboot&t;&t;&t;1096
DECL|macro|__NR_truncate
mdefine_line|#define __NR_truncate&t;&t;&t;1097
DECL|macro|__NR_ftruncate
mdefine_line|#define __NR_ftruncate&t;&t;&t;1098
DECL|macro|__NR_fchmod
mdefine_line|#define __NR_fchmod&t;&t;&t;1099
DECL|macro|__NR_fchown
mdefine_line|#define __NR_fchown&t;&t;&t;1100
DECL|macro|__NR_getpriority
mdefine_line|#define __NR_getpriority&t;&t;1101
DECL|macro|__NR_setpriority
mdefine_line|#define __NR_setpriority&t;&t;1102
DECL|macro|__NR_statfs
mdefine_line|#define __NR_statfs&t;&t;&t;1103
DECL|macro|__NR_fstatfs
mdefine_line|#define __NR_fstatfs&t;&t;&t;1104
DECL|macro|__NR_gettid
mdefine_line|#define __NR_gettid&t;&t;&t;1105
DECL|macro|__NR_semget
mdefine_line|#define __NR_semget&t;&t;&t;1106
DECL|macro|__NR_semop
mdefine_line|#define __NR_semop&t;&t;&t;1107
DECL|macro|__NR_semctl
mdefine_line|#define __NR_semctl&t;&t;&t;1108
DECL|macro|__NR_msgget
mdefine_line|#define __NR_msgget&t;&t;&t;1109
DECL|macro|__NR_msgsnd
mdefine_line|#define __NR_msgsnd&t;&t;&t;1110
DECL|macro|__NR_msgrcv
mdefine_line|#define __NR_msgrcv&t;&t;&t;1111
DECL|macro|__NR_msgctl
mdefine_line|#define __NR_msgctl&t;&t;&t;1112
DECL|macro|__NR_shmget
mdefine_line|#define __NR_shmget&t;&t;&t;1113
DECL|macro|__NR_shmat
mdefine_line|#define __NR_shmat&t;&t;&t;1114
DECL|macro|__NR_shmdt
mdefine_line|#define __NR_shmdt&t;&t;&t;1115
DECL|macro|__NR_shmctl
mdefine_line|#define __NR_shmctl&t;&t;&t;1116
multiline_comment|/* also known as klogctl() in GNU libc: */
DECL|macro|__NR_syslog
mdefine_line|#define __NR_syslog&t;&t;&t;1117
DECL|macro|__NR_setitimer
mdefine_line|#define __NR_setitimer&t;&t;&t;1118
DECL|macro|__NR_getitimer
mdefine_line|#define __NR_getitimer&t;&t;&t;1119
multiline_comment|/* 1120 was __NR_old_stat */
multiline_comment|/* 1121 was __NR_old_lstat */
multiline_comment|/* 1122 was __NR_old_fstat */
DECL|macro|__NR_vhangup
mdefine_line|#define __NR_vhangup&t;&t;&t;1123
DECL|macro|__NR_lchown
mdefine_line|#define __NR_lchown&t;&t;&t;1124
DECL|macro|__NR_vm86
mdefine_line|#define __NR_vm86&t;&t;&t;1125
DECL|macro|__NR_wait4
mdefine_line|#define __NR_wait4&t;&t;&t;1126
DECL|macro|__NR_sysinfo
mdefine_line|#define __NR_sysinfo&t;&t;&t;1127
DECL|macro|__NR_clone
mdefine_line|#define __NR_clone&t;&t;&t;1128
DECL|macro|__NR_setdomainname
mdefine_line|#define __NR_setdomainname&t;&t;1129
DECL|macro|__NR_uname
mdefine_line|#define __NR_uname&t;&t;&t;1130
DECL|macro|__NR_adjtimex
mdefine_line|#define __NR_adjtimex&t;&t;&t;1131
DECL|macro|__NR_create_module
mdefine_line|#define __NR_create_module&t;&t;1132
DECL|macro|__NR_init_module
mdefine_line|#define __NR_init_module&t;&t;1133
DECL|macro|__NR_delete_module
mdefine_line|#define __NR_delete_module&t;&t;1134
DECL|macro|__NR_get_kernel_syms
mdefine_line|#define __NR_get_kernel_syms&t;&t;1135
DECL|macro|__NR_query_module
mdefine_line|#define __NR_query_module&t;&t;1136
DECL|macro|__NR_quotactl
mdefine_line|#define __NR_quotactl&t;&t;&t;1137
DECL|macro|__NR_bdflush
mdefine_line|#define __NR_bdflush&t;&t;&t;1138
DECL|macro|__NR_sysfs
mdefine_line|#define __NR_sysfs&t;&t;&t;1139
DECL|macro|__NR_personality
mdefine_line|#define __NR_personality&t;&t;1140
DECL|macro|__NR_afs_syscall
mdefine_line|#define __NR_afs_syscall&t;&t;1141
DECL|macro|__NR_setfsuid
mdefine_line|#define __NR_setfsuid&t;&t;&t;1142
DECL|macro|__NR_setfsgid
mdefine_line|#define __NR_setfsgid&t;&t;&t;1143
DECL|macro|__NR_getdents
mdefine_line|#define __NR_getdents&t;&t;&t;1144
DECL|macro|__NR_flock
mdefine_line|#define __NR_flock&t;&t;&t;1145
DECL|macro|__NR_readv
mdefine_line|#define __NR_readv&t;&t;&t;1146
DECL|macro|__NR_writev
mdefine_line|#define __NR_writev&t;&t;&t;1147
DECL|macro|__NR_pread
mdefine_line|#define __NR_pread&t;&t;&t;1148
DECL|macro|__NR_pwrite
mdefine_line|#define __NR_pwrite&t;&t;&t;1149
DECL|macro|__NR__sysctl
mdefine_line|#define __NR__sysctl&t;&t;&t;1150
DECL|macro|__NR_mmap
mdefine_line|#define __NR_mmap&t;&t;&t;1151
DECL|macro|__NR_munmap
mdefine_line|#define __NR_munmap&t;&t;&t;1152
DECL|macro|__NR_mlock
mdefine_line|#define __NR_mlock&t;&t;&t;1153
DECL|macro|__NR_mlockall
mdefine_line|#define __NR_mlockall&t;&t;&t;1154
DECL|macro|__NR_mprotect
mdefine_line|#define __NR_mprotect&t;&t;&t;1155
DECL|macro|__NR_mremap
mdefine_line|#define __NR_mremap&t;&t;&t;1156
DECL|macro|__NR_msync
mdefine_line|#define __NR_msync&t;&t;&t;1157
DECL|macro|__NR_munlock
mdefine_line|#define __NR_munlock&t;&t;&t;1158
DECL|macro|__NR_munlockall
mdefine_line|#define __NR_munlockall&t;&t;&t;1159
DECL|macro|__NR_sched_getparam
mdefine_line|#define __NR_sched_getparam&t;&t;1160
DECL|macro|__NR_sched_setparam
mdefine_line|#define __NR_sched_setparam&t;&t;1161
DECL|macro|__NR_sched_getscheduler
mdefine_line|#define __NR_sched_getscheduler&t;&t;1162
DECL|macro|__NR_sched_setscheduler
mdefine_line|#define __NR_sched_setscheduler&t;&t;1163
DECL|macro|__NR_sched_yield
mdefine_line|#define __NR_sched_yield&t;&t;1164
DECL|macro|__NR_sched_get_priority_max
mdefine_line|#define __NR_sched_get_priority_max&t;1165
DECL|macro|__NR_sched_get_priority_min
mdefine_line|#define __NR_sched_get_priority_min&t;1166
DECL|macro|__NR_sched_rr_get_interval
mdefine_line|#define __NR_sched_rr_get_interval&t;1167
DECL|macro|__NR_nanosleep
mdefine_line|#define __NR_nanosleep&t;&t;&t;1168
DECL|macro|__NR_nfsservctl
mdefine_line|#define __NR_nfsservctl&t;&t;&t;1169
DECL|macro|__NR_prctl
mdefine_line|#define __NR_prctl&t;&t;&t;1170
multiline_comment|/* 1171 is reserved for backwards compatibility with old __NR_getpagesize */
DECL|macro|__NR_mmap2
mdefine_line|#define __NR_mmap2&t;&t;&t;1172
DECL|macro|__NR_pciconfig_read
mdefine_line|#define __NR_pciconfig_read&t;&t;1173
DECL|macro|__NR_pciconfig_write
mdefine_line|#define __NR_pciconfig_write&t;&t;1174
DECL|macro|__NR_perfmonctl
mdefine_line|#define __NR_perfmonctl&t;&t;&t;1175
DECL|macro|__NR_sigaltstack
mdefine_line|#define __NR_sigaltstack&t;&t;1176
DECL|macro|__NR_rt_sigaction
mdefine_line|#define __NR_rt_sigaction&t;&t;1177
DECL|macro|__NR_rt_sigpending
mdefine_line|#define __NR_rt_sigpending&t;&t;1178
DECL|macro|__NR_rt_sigprocmask
mdefine_line|#define __NR_rt_sigprocmask&t;&t;1179
DECL|macro|__NR_rt_sigqueueinfo
mdefine_line|#define __NR_rt_sigqueueinfo&t;&t;1180
DECL|macro|__NR_rt_sigreturn
mdefine_line|#define __NR_rt_sigreturn&t;&t;1181
DECL|macro|__NR_rt_sigsuspend
mdefine_line|#define __NR_rt_sigsuspend&t;&t;1182
DECL|macro|__NR_rt_sigtimedwait
mdefine_line|#define __NR_rt_sigtimedwait&t;&t;1183
DECL|macro|__NR_getcwd
mdefine_line|#define __NR_getcwd&t;&t;&t;1184
DECL|macro|__NR_capget
mdefine_line|#define __NR_capget&t;&t;&t;1185
DECL|macro|__NR_capset
mdefine_line|#define __NR_capset&t;&t;&t;1186
DECL|macro|__NR_sendfile
mdefine_line|#define __NR_sendfile&t;&t;&t;1187
DECL|macro|__NR_getpmsg
mdefine_line|#define __NR_getpmsg&t;&t;&t;1188
DECL|macro|__NR_putpmsg
mdefine_line|#define __NR_putpmsg&t;&t;&t;1189
DECL|macro|__NR_socket
mdefine_line|#define __NR_socket&t;&t;&t;1190
DECL|macro|__NR_bind
mdefine_line|#define __NR_bind&t;&t;&t;1191
DECL|macro|__NR_connect
mdefine_line|#define __NR_connect&t;&t;&t;1192
DECL|macro|__NR_listen
mdefine_line|#define __NR_listen&t;&t;&t;1193
DECL|macro|__NR_accept
mdefine_line|#define __NR_accept&t;&t;&t;1194
DECL|macro|__NR_getsockname
mdefine_line|#define __NR_getsockname&t;&t;1195
DECL|macro|__NR_getpeername
mdefine_line|#define __NR_getpeername&t;&t;1196
DECL|macro|__NR_socketpair
mdefine_line|#define __NR_socketpair&t;&t;&t;1197
DECL|macro|__NR_send
mdefine_line|#define __NR_send&t;&t;&t;1198
DECL|macro|__NR_sendto
mdefine_line|#define __NR_sendto&t;&t;&t;1199
DECL|macro|__NR_recv
mdefine_line|#define __NR_recv&t;&t;&t;1200
DECL|macro|__NR_recvfrom
mdefine_line|#define __NR_recvfrom&t;&t;&t;1201
DECL|macro|__NR_shutdown
mdefine_line|#define __NR_shutdown&t;&t;&t;1202
DECL|macro|__NR_setsockopt
mdefine_line|#define __NR_setsockopt&t;&t;&t;1203
DECL|macro|__NR_getsockopt
mdefine_line|#define __NR_getsockopt&t;&t;&t;1204
DECL|macro|__NR_sendmsg
mdefine_line|#define __NR_sendmsg&t;&t;&t;1205
DECL|macro|__NR_recvmsg
mdefine_line|#define __NR_recvmsg&t;&t;&t;1206
DECL|macro|__NR_pivot_root
mdefine_line|#define __NR_pivot_root&t;&t;&t;1207
DECL|macro|__NR_mincore
mdefine_line|#define __NR_mincore&t;&t;&t;1208
DECL|macro|__NR_madvise
mdefine_line|#define __NR_madvise&t;&t;&t;1209
DECL|macro|__NR_stat
mdefine_line|#define __NR_stat&t;&t;&t;1210
DECL|macro|__NR_lstat
mdefine_line|#define __NR_lstat&t;&t;&t;1211
DECL|macro|__NR_fstat
mdefine_line|#define __NR_fstat&t;&t;&t;1212
DECL|macro|__NR_clone2
mdefine_line|#define __NR_clone2&t;&t;&t;1213
DECL|macro|__NR_getdents64
mdefine_line|#define __NR_getdents64&t;&t;&t;1214
DECL|macro|__NR_getunwind
mdefine_line|#define __NR_getunwind&t;&t;&t;1215
DECL|macro|__NR_readahead
mdefine_line|#define __NR_readahead&t;&t;&t;1216
DECL|macro|__NR_setxattr
mdefine_line|#define __NR_setxattr&t;&t;&t;1217
DECL|macro|__NR_lsetxattr
mdefine_line|#define __NR_lsetxattr&t;&t;&t;1218
DECL|macro|__NR_fsetxattr
mdefine_line|#define __NR_fsetxattr&t;&t;&t;1219
DECL|macro|__NR_getxattr
mdefine_line|#define __NR_getxattr&t;&t;&t;1220
DECL|macro|__NR_lgetxattr
mdefine_line|#define __NR_lgetxattr&t;&t;&t;1221
DECL|macro|__NR_fgetxattr
mdefine_line|#define __NR_fgetxattr&t;&t;&t;1222
DECL|macro|__NR_listxattr
mdefine_line|#define __NR_listxattr&t;&t;&t;1223
DECL|macro|__NR_llistxattr
mdefine_line|#define __NR_llistxattr&t;&t;&t;1224
DECL|macro|__NR_flistxattr
mdefine_line|#define __NR_flistxattr&t;&t;&t;1225
DECL|macro|__NR_removexattr
mdefine_line|#define __NR_removexattr&t;&t;1226
DECL|macro|__NR_lremovexattr
mdefine_line|#define __NR_lremovexattr&t;&t;1227
DECL|macro|__NR_fremovexattr
mdefine_line|#define __NR_fremovexattr&t;&t;1228
DECL|macro|__NR_tkill
mdefine_line|#define __NR_tkill&t;&t;&t;1229
DECL|macro|__NR_futex
mdefine_line|#define __NR_futex&t;&t;&t;1230
DECL|macro|__NR_sched_setaffinity
mdefine_line|#define __NR_sched_setaffinity&t;&t;1231
DECL|macro|__NR_sched_getaffinity
mdefine_line|#define __NR_sched_getaffinity&t;&t;1232
macro_line|#if !defined(__ASSEMBLY__) &amp;&amp; !defined(ASSEMBLER)
r_extern
r_int
id|__ia64_syscall
(paren
r_int
id|a0
comma
r_int
id|a1
comma
r_int
id|a2
comma
r_int
id|a3
comma
r_int
id|a4
comma
r_int
id|nr
)paren
suffix:semicolon
DECL|macro|_syscall0
mdefine_line|#define _syscall0(type,name)&t;&t;&t;&t;&t;&t;&bslash;&n;type&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;name (void)&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;register long dummy1 __asm__ (&quot;out0&quot;);&t;&t;&t;&t;&bslash;&n;&t;register long dummy2 __asm__ (&quot;out1&quot;);&t;&t;&t;&t;&bslash;&n;&t;register long dummy3 __asm__ (&quot;out2&quot;);&t;&t;&t;&t;&bslash;&n;&t;register long dummy4 __asm__ (&quot;out3&quot;);&t;&t;&t;&t;&bslash;&n;&t;register long dummy5 __asm__ (&quot;out4&quot;);&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;return __ia64_syscall(dummy1, dummy2, dummy3, dummy4, dummy5,&t;&bslash;&n;&t;&t;&t;      __NR_##name);&t;&t;&t;&t;&bslash;&n;}
DECL|macro|_syscall1
mdefine_line|#define _syscall1(type,name,type1,arg1)&t;&t;&t;&t;&t;&bslash;&n;type&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;name (type1 arg1)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;register long dummy2 __asm__ (&quot;out1&quot;);&t;&t;&t;&t;&bslash;&n;&t;register long dummy3 __asm__ (&quot;out2&quot;);&t;&t;&t;&t;&bslash;&n;&t;register long dummy4 __asm__ (&quot;out3&quot;);&t;&t;&t;&t;&bslash;&n;&t;register long dummy5 __asm__ (&quot;out4&quot;);&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;return __ia64_syscall((long) arg1, dummy2, dummy3, dummy4,&t;&bslash;&n;&t;&t;&t;      dummy5, __NR_##name);&t;&t;&t;&bslash;&n;}
DECL|macro|_syscall2
mdefine_line|#define _syscall2(type,name,type1,arg1,type2,arg2)&t;&t;&t;&bslash;&n;type&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;name (type1 arg1, type2 arg2)&t;&t;&t;&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;register long dummy3 __asm__ (&quot;out2&quot;);&t;&t;&t;&t;&bslash;&n;&t;register long dummy4 __asm__ (&quot;out3&quot;);&t;&t;&t;&t;&bslash;&n;&t;register long dummy5 __asm__ (&quot;out4&quot;);&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;return __ia64_syscall((long) arg1, (long) arg2, dummy3, dummy4,&t;&bslash;&n;&t;&t;&t;      dummy5, __NR_##name);&t;&t;&t;&bslash;&n;}
DECL|macro|_syscall3
mdefine_line|#define _syscall3(type,name,type1,arg1,type2,arg2,type3,arg3)&t;&t;&bslash;&n;type&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;name (type1 arg1, type2 arg2, type3 arg3)&t;&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;register long dummy4 __asm__ (&quot;out3&quot;);&t;&t;&t;&t;&bslash;&n;&t;register long dummy5 __asm__ (&quot;out4&quot;);&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;return __ia64_syscall((long) arg1, (long) arg2, (long) arg3,&t;&bslash;&n;&t;&t;&t;      dummy4, dummy5, __NR_##name);&t;&t;&bslash;&n;}
DECL|macro|_syscall4
mdefine_line|#define _syscall4(type,name,type1,arg1,type2,arg2,type3,arg3,type4,arg4)&t;&bslash;&n;type&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;name (type1 arg1, type2 arg2, type3 arg3, type4 arg4)&t;&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;register long dummy5 __asm__ (&quot;out4&quot;);&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;return __ia64_syscall((long) arg1, (long) arg2, (long) arg3,&t;&t;&bslash;&n;&t;&t;&t;      (long) arg4, dummy5, __NR_##name);&t;&t;&bslash;&n;}
DECL|macro|_syscall5
mdefine_line|#define _syscall5(type,name,type1,arg1,type2,arg2,type3,arg3,type4,arg4,type5,arg5)&t;&bslash;&n;type&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;name (type1 arg1, type2 arg2, type3 arg3, type4 arg4, type5 arg5)&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;return __ia64_syscall((long) arg1, (long) arg2, (long) arg3,&t;&t;&t;&bslash;&n;&t;&t;&t;      (long) arg4, (long) arg5, __NR_##name);&t;&t;&t;&bslash;&n;}
macro_line|#ifdef __KERNEL_SYSCALLS__
r_struct
id|rusage
suffix:semicolon
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
id|wait_stat
comma
r_int
comma
id|options
comma
r_struct
id|rusage
op_star
comma
id|rusage
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
r_static
r_inline
id|_syscall2
c_func
(paren
id|pid_t
comma
id|clone
comma
r_int
r_int
comma
id|flags
comma
r_void
op_star
comma
id|sp
)paren
suffix:semicolon
DECL|macro|__NR__exit
mdefine_line|#define __NR__exit __NR_exit
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
id|pid_t
DECL|function|waitpid
id|waitpid
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
r_static
r_inline
id|pid_t
DECL|function|wait
id|wait
(paren
r_int
op_star
id|wait_stat
)paren
(brace
r_return
id|wait4
c_func
(paren
op_minus
l_int|1
comma
id|wait_stat
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
)brace
macro_line|#endif /* __KERNEL_SYSCALLS__ */
multiline_comment|/*&n; * &quot;Conditional&quot; syscalls&n; *&n; * What we want is __attribute__((weak,alias(&quot;sys_ni_syscall&quot;))),&n; * but it doesn&squot;t work on all toolchains, so we just do it by hand&n; */
DECL|macro|cond_syscall
mdefine_line|#define cond_syscall(x) asm(&quot;.weak&bslash;t&quot; #x &quot;&bslash;n&bslash;t.set&bslash;t&quot; #x &quot;,sys_ni_syscall&quot;);
macro_line|#endif /* !__ASSEMBLY__ */
macro_line|#endif /* _ASM_IA64_UNISTD_H */
eof
