macro_line|#ifndef _ASM_IA64_UNISTD_H
DECL|macro|_ASM_IA64_UNISTD_H
mdefine_line|#define _ASM_IA64_UNISTD_H
multiline_comment|/*&n; * IA-64 Linux syscall numbers and inline-functions.&n; *&n; * Copyright (C) 1998-2004 Hewlett-Packard Co&n; *&t;David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; */
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
DECL|macro|__NR_remap_file_pages
mdefine_line|#define __NR_remap_file_pages&t;&t;1125
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
multiline_comment|/* 1132 was __NR_create_module */
DECL|macro|__NR_init_module
mdefine_line|#define __NR_init_module&t;&t;1133
DECL|macro|__NR_delete_module
mdefine_line|#define __NR_delete_module&t;&t;1134
multiline_comment|/* 1135 was __NR_get_kernel_syms */
multiline_comment|/* 1136 was __NR_query_module */
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
DECL|macro|__NR_pread64
mdefine_line|#define __NR_pread64&t;&t;&t;1148
DECL|macro|__NR_pwrite64
mdefine_line|#define __NR_pwrite64&t;&t;&t;1149
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
DECL|macro|__NR_set_tid_address
mdefine_line|#define __NR_set_tid_address&t;&t;1233
DECL|macro|__NR_fadvise64
mdefine_line|#define __NR_fadvise64&t;&t;&t;1234
DECL|macro|__NR_tgkill
mdefine_line|#define __NR_tgkill&t;&t;&t;1235
DECL|macro|__NR_exit_group
mdefine_line|#define __NR_exit_group&t;&t;&t;1236
DECL|macro|__NR_lookup_dcookie
mdefine_line|#define __NR_lookup_dcookie&t;&t;1237
DECL|macro|__NR_io_setup
mdefine_line|#define __NR_io_setup&t;&t;&t;1238
DECL|macro|__NR_io_destroy
mdefine_line|#define __NR_io_destroy&t;&t;&t;1239
DECL|macro|__NR_io_getevents
mdefine_line|#define __NR_io_getevents&t;&t;1240
DECL|macro|__NR_io_submit
mdefine_line|#define __NR_io_submit&t;&t;&t;1241
DECL|macro|__NR_io_cancel
mdefine_line|#define __NR_io_cancel&t;&t;&t;1242
DECL|macro|__NR_epoll_create
mdefine_line|#define __NR_epoll_create&t;&t;1243
DECL|macro|__NR_epoll_ctl
mdefine_line|#define __NR_epoll_ctl&t;&t;&t;1244
DECL|macro|__NR_epoll_wait
mdefine_line|#define __NR_epoll_wait&t;&t;&t;1245
DECL|macro|__NR_restart_syscall
mdefine_line|#define __NR_restart_syscall&t;&t;1246
DECL|macro|__NR_semtimedop
mdefine_line|#define __NR_semtimedop&t;&t;&t;1247
DECL|macro|__NR_timer_create
mdefine_line|#define __NR_timer_create&t;&t;1248
DECL|macro|__NR_timer_settime
mdefine_line|#define __NR_timer_settime&t;&t;1249
DECL|macro|__NR_timer_gettime
mdefine_line|#define __NR_timer_gettime&t;&t;1250
DECL|macro|__NR_timer_getoverrun
mdefine_line|#define __NR_timer_getoverrun&t;&t;1251
DECL|macro|__NR_timer_delete
mdefine_line|#define __NR_timer_delete&t;&t;1252
DECL|macro|__NR_clock_settime
mdefine_line|#define __NR_clock_settime&t;&t;1253
DECL|macro|__NR_clock_gettime
mdefine_line|#define __NR_clock_gettime&t;&t;1254
DECL|macro|__NR_clock_getres
mdefine_line|#define __NR_clock_getres&t;&t;1255
DECL|macro|__NR_clock_nanosleep
mdefine_line|#define __NR_clock_nanosleep&t;&t;1256
DECL|macro|__NR_fstatfs64
mdefine_line|#define __NR_fstatfs64&t;&t;&t;1257
DECL|macro|__NR_statfs64
mdefine_line|#define __NR_statfs64&t;&t;&t;1258
DECL|macro|__NR_mbind
mdefine_line|#define __NR_mbind&t;&t;&t;1259
DECL|macro|__NR_get_mempolicy
mdefine_line|#define __NR_get_mempolicy&t;&t;1260
DECL|macro|__NR_set_mempolicy
mdefine_line|#define __NR_set_mempolicy&t;&t;1261
DECL|macro|__NR_mq_open
mdefine_line|#define __NR_mq_open&t;&t;&t;1262
DECL|macro|__NR_mq_unlink
mdefine_line|#define __NR_mq_unlink&t;&t;&t;1263
DECL|macro|__NR_mq_timedsend
mdefine_line|#define __NR_mq_timedsend&t;&t;1264
DECL|macro|__NR_mq_timedreceive
mdefine_line|#define __NR_mq_timedreceive&t;&t;1265
DECL|macro|__NR_mq_notify
mdefine_line|#define __NR_mq_notify&t;&t;&t;1266
DECL|macro|__NR_mq_getsetattr
mdefine_line|#define __NR_mq_getsetattr&t;&t;1267
DECL|macro|__NR_kexec_load
mdefine_line|#define __NR_kexec_load&t;&t;&t;1268
DECL|macro|__NR_vserver
mdefine_line|#define __NR_vserver&t;&t;&t;1269
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/config.h&gt;
DECL|macro|NR_syscalls
mdefine_line|#define NR_syscalls&t;&t;&t;256 /* length of syscall table */
DECL|macro|__ARCH_WANT_SYS_RT_SIGACTION
mdefine_line|#define __ARCH_WANT_SYS_RT_SIGACTION
macro_line|#ifdef CONFIG_IA32_SUPPORT
DECL|macro|__ARCH_WANT_SYS_FADVISE64
macro_line|# define __ARCH_WANT_SYS_FADVISE64
DECL|macro|__ARCH_WANT_SYS_GETPGRP
macro_line|# define __ARCH_WANT_SYS_GETPGRP
DECL|macro|__ARCH_WANT_SYS_LLSEEK
macro_line|# define __ARCH_WANT_SYS_LLSEEK
DECL|macro|__ARCH_WANT_SYS_NICE
macro_line|# define __ARCH_WANT_SYS_NICE
DECL|macro|__ARCH_WANT_SYS_OLD_GETRLIMIT
macro_line|# define __ARCH_WANT_SYS_OLD_GETRLIMIT
DECL|macro|__ARCH_WANT_SYS_OLDUMOUNT
macro_line|# define __ARCH_WANT_SYS_OLDUMOUNT
DECL|macro|__ARCH_WANT_SYS_SIGPENDING
macro_line|# define __ARCH_WANT_SYS_SIGPENDING
DECL|macro|__ARCH_WANT_SYS_SIGPROCMASK
macro_line|# define __ARCH_WANT_SYS_SIGPROCMASK
macro_line|#endif
macro_line|#if !defined(__ASSEMBLY__) &amp;&amp; !defined(ASSEMBLER)
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/linkage.h&gt;
macro_line|#include &lt;linux/compiler.h&gt;
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
macro_line|#ifdef __KERNEL_SYSCALLS__
macro_line|#include &lt;linux/compiler.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;linux/stringify.h&gt;
macro_line|#include &lt;linux/syscalls.h&gt;
r_static
r_inline
r_int
DECL|function|open
id|open
(paren
r_const
r_char
op_star
id|name
comma
r_int
id|mode
comma
r_int
id|flags
)paren
(brace
r_return
id|sys_open
c_func
(paren
id|name
comma
id|mode
comma
id|flags
)paren
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|dup
id|dup
(paren
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
r_static
r_inline
r_int
DECL|function|close
id|close
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
r_static
r_inline
id|off_t
DECL|function|lseek
id|lseek
(paren
r_int
id|fd
comma
id|off_t
id|off
comma
r_int
id|whence
)paren
(brace
r_return
id|sys_lseek
c_func
(paren
id|fd
comma
id|off
comma
id|whence
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|_exit
id|_exit
(paren
r_int
id|value
)paren
(brace
id|sys_exit
c_func
(paren
id|value
)paren
suffix:semicolon
)brace
DECL|macro|exit
mdefine_line|#define exit(x) _exit(x)
r_static
r_inline
r_int
DECL|function|write
id|write
(paren
r_int
id|fd
comma
r_const
r_char
op_star
id|buf
comma
r_int
id|nr
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
id|nr
)paren
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|read
id|read
(paren
r_int
id|fd
comma
r_char
op_star
id|buf
comma
r_int
id|nr
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
id|nr
)paren
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|setsid
id|setsid
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
id|execve
(paren
r_const
r_char
op_star
id|filename
comma
r_char
op_star
r_const
id|av
(braket
)braket
comma
r_char
op_star
r_const
id|ep
(braket
)braket
)paren
suffix:semicolon
r_extern
id|pid_t
id|clone
(paren
r_int
r_int
id|flags
comma
r_void
op_star
id|sp
)paren
suffix:semicolon
macro_line|#endif /* __KERNEL_SYSCALLS__ */
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
r_int
id|off
)paren
suffix:semicolon
id|asmlinkage
r_int
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
id|prot
comma
r_int
id|flags
comma
r_int
id|fd
comma
r_int
id|pgoff
)paren
suffix:semicolon
r_struct
id|pt_regs
suffix:semicolon
r_struct
id|sigaction
suffix:semicolon
id|asmlinkage
r_int
id|sys_execve
c_func
(paren
r_char
id|__user
op_star
id|filename
comma
r_char
id|__user
op_star
id|__user
op_star
id|argv
comma
r_char
id|__user
op_star
id|__user
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
id|sys_pipe
c_func
(paren
r_int
id|arg0
comma
r_int
id|arg1
comma
r_int
id|arg2
comma
r_int
id|arg3
comma
r_int
id|arg4
comma
r_int
id|arg5
comma
r_int
id|arg6
comma
r_int
id|arg7
comma
r_int
id|stack
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
id|pid_t
id|pid
comma
r_int
r_int
id|addr
comma
r_int
r_int
id|data
comma
r_int
id|arg4
comma
r_int
id|arg5
comma
r_int
id|arg6
comma
r_int
id|arg7
comma
r_int
id|stack
)paren
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
multiline_comment|/*&n; * &quot;Conditional&quot; syscalls&n; *&n; * Note, this macro can only be used in the file which defines sys_ni_syscall, i.e., in&n; * kernel/sys.c.  This version causes warnings because the declaration isn&squot;t a&n; * proper prototype, but we can&squot;t use __typeof__ either, because not all cond_syscall()&n; * declarations have prototypes at the moment.&n; */
DECL|macro|cond_syscall
mdefine_line|#define cond_syscall(x) asmlinkage long x (void) __attribute__((weak,alias(&quot;sys_ni_syscall&quot;)));
macro_line|#endif /* !__ASSEMBLY__ */
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _ASM_IA64_UNISTD_H */
eof
