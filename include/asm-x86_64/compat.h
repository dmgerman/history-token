macro_line|#ifndef _ASM_X86_64_COMPAT_H
DECL|macro|_ASM_X86_64_COMPAT_H
mdefine_line|#define _ASM_X86_64_COMPAT_H
multiline_comment|/*&n; * Architecture specific compatibility types&n; */
macro_line|#include &lt;linux/types.h&gt;
DECL|macro|COMPAT_USER_HZ
mdefine_line|#define COMPAT_USER_HZ&t;100
DECL|typedef|compat_size_t
r_typedef
id|u32
id|compat_size_t
suffix:semicolon
DECL|typedef|compat_ssize_t
r_typedef
id|s32
id|compat_ssize_t
suffix:semicolon
DECL|typedef|compat_time_t
r_typedef
id|s32
id|compat_time_t
suffix:semicolon
DECL|typedef|compat_clock_t
r_typedef
id|s32
id|compat_clock_t
suffix:semicolon
DECL|typedef|compat_pid_t
r_typedef
id|s32
id|compat_pid_t
suffix:semicolon
DECL|typedef|compat_uid_t
r_typedef
id|u16
id|compat_uid_t
suffix:semicolon
DECL|typedef|compat_gid_t
r_typedef
id|u16
id|compat_gid_t
suffix:semicolon
DECL|typedef|compat_uid32_t
r_typedef
id|u32
id|compat_uid32_t
suffix:semicolon
DECL|typedef|compat_gid32_t
r_typedef
id|u32
id|compat_gid32_t
suffix:semicolon
DECL|typedef|compat_mode_t
r_typedef
id|u16
id|compat_mode_t
suffix:semicolon
DECL|typedef|compat_ino_t
r_typedef
id|u32
id|compat_ino_t
suffix:semicolon
DECL|typedef|compat_dev_t
r_typedef
id|u16
id|compat_dev_t
suffix:semicolon
DECL|typedef|compat_off_t
r_typedef
id|s32
id|compat_off_t
suffix:semicolon
DECL|typedef|compat_loff_t
r_typedef
id|s64
id|compat_loff_t
suffix:semicolon
DECL|typedef|compat_nlink_t
r_typedef
id|u16
id|compat_nlink_t
suffix:semicolon
DECL|typedef|compat_ipc_pid_t
r_typedef
id|u16
id|compat_ipc_pid_t
suffix:semicolon
DECL|typedef|compat_daddr_t
r_typedef
id|s32
id|compat_daddr_t
suffix:semicolon
DECL|typedef|compat_caddr_t
r_typedef
id|u32
id|compat_caddr_t
suffix:semicolon
DECL|typedef|compat_fsid_t
r_typedef
id|__kernel_fsid_t
id|compat_fsid_t
suffix:semicolon
DECL|struct|compat_timespec
r_struct
id|compat_timespec
(brace
DECL|member|tv_sec
id|compat_time_t
id|tv_sec
suffix:semicolon
DECL|member|tv_nsec
id|s32
id|tv_nsec
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|compat_timeval
r_struct
id|compat_timeval
(brace
DECL|member|tv_sec
id|compat_time_t
id|tv_sec
suffix:semicolon
DECL|member|tv_usec
id|s32
id|tv_usec
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|compat_stat
r_struct
id|compat_stat
(brace
DECL|member|st_dev
id|compat_dev_t
id|st_dev
suffix:semicolon
DECL|member|__pad1
id|u16
id|__pad1
suffix:semicolon
DECL|member|st_ino
id|compat_ino_t
id|st_ino
suffix:semicolon
DECL|member|st_mode
id|compat_mode_t
id|st_mode
suffix:semicolon
DECL|member|st_nlink
id|compat_nlink_t
id|st_nlink
suffix:semicolon
DECL|member|st_uid
id|compat_uid_t
id|st_uid
suffix:semicolon
DECL|member|st_gid
id|compat_gid_t
id|st_gid
suffix:semicolon
DECL|member|st_rdev
id|compat_dev_t
id|st_rdev
suffix:semicolon
DECL|member|__pad2
id|u16
id|__pad2
suffix:semicolon
DECL|member|st_size
id|u32
id|st_size
suffix:semicolon
DECL|member|st_blksize
id|u32
id|st_blksize
suffix:semicolon
DECL|member|st_blocks
id|u32
id|st_blocks
suffix:semicolon
DECL|member|st_atime
id|u32
id|st_atime
suffix:semicolon
DECL|member|st_atime_nsec
id|u32
id|st_atime_nsec
suffix:semicolon
DECL|member|st_mtime
id|u32
id|st_mtime
suffix:semicolon
DECL|member|st_mtime_nsec
id|u32
id|st_mtime_nsec
suffix:semicolon
DECL|member|st_ctime
id|u32
id|st_ctime
suffix:semicolon
DECL|member|st_ctime_nsec
id|u32
id|st_ctime_nsec
suffix:semicolon
DECL|member|__unused4
id|u32
id|__unused4
suffix:semicolon
DECL|member|__unused5
id|u32
id|__unused5
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* _ASM_X86_64_COMPAT_H */
eof
