multiline_comment|/*&n; *  ncp_mount.h&n; *&n; *  Copyright (C) 1995, 1996 by Volker Lendecke&n; *&n; */
macro_line|#ifndef _LINUX_NCP_MOUNT_H
DECL|macro|_LINUX_NCP_MOUNT_H
mdefine_line|#define _LINUX_NCP_MOUNT_H
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/ncp.h&gt;
DECL|macro|NCP_MOUNT_VERSION
mdefine_line|#define NCP_MOUNT_VERSION 3
multiline_comment|/* Values for flags */
DECL|macro|NCP_MOUNT_SOFT
mdefine_line|#define NCP_MOUNT_SOFT&t;&t;0x0001
DECL|macro|NCP_MOUNT_INTR
mdefine_line|#define NCP_MOUNT_INTR&t;&t;0x0002
DECL|macro|NCP_MOUNT_STRONG
mdefine_line|#define NCP_MOUNT_STRONG&t;0x0004&t;/* enable delete/rename of r/o files */
DECL|macro|NCP_MOUNT_NO_OS2
mdefine_line|#define NCP_MOUNT_NO_OS2&t;0x0008&t;/* do not use OS/2 (LONG) namespace */
DECL|macro|NCP_MOUNT_NO_NFS
mdefine_line|#define NCP_MOUNT_NO_NFS&t;0x0010&t;/* do not use NFS namespace */
DECL|macro|NCP_MOUNT_EXTRAS
mdefine_line|#define NCP_MOUNT_EXTRAS&t;0x0020
DECL|macro|NCP_MOUNT_SYMLINKS
mdefine_line|#define NCP_MOUNT_SYMLINKS&t;0x0040&t;/* enable symlinks */
DECL|struct|ncp_mount_data
r_struct
id|ncp_mount_data
(brace
DECL|member|version
r_int
id|version
suffix:semicolon
DECL|member|ncp_fd
r_int
r_int
id|ncp_fd
suffix:semicolon
multiline_comment|/* The socket to the ncp port */
DECL|member|mounted_uid
id|__kernel_uid_t
id|mounted_uid
suffix:semicolon
multiline_comment|/* Who may umount() this filesystem? */
DECL|member|wdog_pid
id|__kernel_pid_t
id|wdog_pid
suffix:semicolon
multiline_comment|/* Who cares for our watchdog packets? */
DECL|member|mounted_vol
r_int
r_char
id|mounted_vol
(braket
id|NCP_VOLNAME_LEN
op_plus
l_int|1
)braket
suffix:semicolon
DECL|member|time_out
r_int
r_int
id|time_out
suffix:semicolon
multiline_comment|/* How long should I wait after&n;&t;&t;&t;&t;   sending a NCP request? */
DECL|member|retry_count
r_int
r_int
id|retry_count
suffix:semicolon
multiline_comment|/* And how often should I retry? */
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
DECL|member|uid
id|__kernel_uid_t
id|uid
suffix:semicolon
DECL|member|gid
id|__kernel_gid_t
id|gid
suffix:semicolon
DECL|member|file_mode
id|__kernel_mode_t
id|file_mode
suffix:semicolon
DECL|member|dir_mode
id|__kernel_mode_t
id|dir_mode
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|NCP_MOUNT_VERSION_V4
mdefine_line|#define NCP_MOUNT_VERSION_V4&t;(4)
DECL|struct|ncp_mount_data_v4
r_struct
id|ncp_mount_data_v4
(brace
DECL|member|version
r_int
id|version
suffix:semicolon
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* NCP_MOUNT_* flags */
multiline_comment|/* MIPS uses long __kernel_uid_t, but... */
multiline_comment|/* we neever pass -1, so it is safe */
DECL|member|mounted_uid
r_int
r_int
id|mounted_uid
suffix:semicolon
multiline_comment|/* Who may umount() this filesystem? */
multiline_comment|/* MIPS uses long __kernel_pid_t */
DECL|member|wdog_pid
r_int
id|wdog_pid
suffix:semicolon
multiline_comment|/* Who cares for our watchdog packets? */
DECL|member|ncp_fd
r_int
r_int
id|ncp_fd
suffix:semicolon
multiline_comment|/* The socket to the ncp port */
DECL|member|time_out
r_int
r_int
id|time_out
suffix:semicolon
multiline_comment|/* How long should I wait after&n;&t;&t;&t;&t;   sending a NCP request? */
DECL|member|retry_count
r_int
r_int
id|retry_count
suffix:semicolon
multiline_comment|/* And how often should I retry? */
multiline_comment|/* MIPS uses long __kernel_uid_t... */
multiline_comment|/* we never pass -1, so it is safe */
DECL|member|uid
r_int
r_int
id|uid
suffix:semicolon
DECL|member|gid
r_int
r_int
id|gid
suffix:semicolon
multiline_comment|/* MIPS uses unsigned long __kernel_mode_t */
DECL|member|file_mode
r_int
r_int
id|file_mode
suffix:semicolon
DECL|member|dir_mode
r_int
r_int
id|dir_mode
suffix:semicolon
)brace
suffix:semicolon
macro_line|#ifdef __KERNEL__
DECL|struct|ncp_mount_data_kernel
r_struct
id|ncp_mount_data_kernel
(brace
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* NCP_MOUNT_* flags */
DECL|member|int_flags
r_int
r_int
id|int_flags
suffix:semicolon
multiline_comment|/* internal flags */
DECL|macro|NCP_IMOUNT_LOGGEDIN_POSSIBLE
mdefine_line|#define NCP_IMOUNT_LOGGEDIN_POSSIBLE&t;0x0001
DECL|member|mounted_uid
id|__kernel_uid32_t
id|mounted_uid
suffix:semicolon
multiline_comment|/* Who may umount() this filesystem? */
DECL|member|wdog_pid
id|__kernel_pid_t
id|wdog_pid
suffix:semicolon
multiline_comment|/* Who cares for our watchdog packets? */
DECL|member|ncp_fd
r_int
r_int
id|ncp_fd
suffix:semicolon
multiline_comment|/* The socket to the ncp port */
DECL|member|time_out
r_int
r_int
id|time_out
suffix:semicolon
multiline_comment|/* How long should I wait after&n;&t;&t;&t;&t;&t;   sending a NCP request? */
DECL|member|retry_count
r_int
r_int
id|retry_count
suffix:semicolon
multiline_comment|/* And how often should I retry? */
DECL|member|mounted_vol
r_int
r_char
id|mounted_vol
(braket
id|NCP_VOLNAME_LEN
op_plus
l_int|1
)braket
suffix:semicolon
DECL|member|uid
id|__kernel_uid32_t
id|uid
suffix:semicolon
DECL|member|gid
id|__kernel_gid32_t
id|gid
suffix:semicolon
DECL|member|file_mode
id|__kernel_mode_t
id|file_mode
suffix:semicolon
DECL|member|dir_mode
id|__kernel_mode_t
id|dir_mode
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#endif
eof
