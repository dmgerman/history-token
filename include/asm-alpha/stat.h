macro_line|#ifndef _ALPHA_STAT_H
DECL|macro|_ALPHA_STAT_H
mdefine_line|#define _ALPHA_STAT_H
DECL|struct|stat
r_struct
id|stat
(brace
DECL|member|st_dev
r_int
r_int
id|st_dev
suffix:semicolon
DECL|member|st_ino
r_int
r_int
id|st_ino
suffix:semicolon
DECL|member|st_mode
r_int
r_int
id|st_mode
suffix:semicolon
DECL|member|st_nlink
r_int
r_int
id|st_nlink
suffix:semicolon
DECL|member|st_uid
r_int
r_int
id|st_uid
suffix:semicolon
DECL|member|st_gid
r_int
r_int
id|st_gid
suffix:semicolon
DECL|member|st_rdev
r_int
r_int
id|st_rdev
suffix:semicolon
DECL|member|st_size
r_int
id|st_size
suffix:semicolon
DECL|member|st_atime
r_int
r_int
id|st_atime
suffix:semicolon
DECL|member|st_mtime
r_int
r_int
id|st_mtime
suffix:semicolon
DECL|member|st_ctime
r_int
r_int
id|st_ctime
suffix:semicolon
DECL|member|st_blksize
r_int
r_int
id|st_blksize
suffix:semicolon
DECL|member|st_blocks
r_int
r_int
id|st_blocks
suffix:semicolon
DECL|member|st_flags
r_int
r_int
id|st_flags
suffix:semicolon
DECL|member|st_gen
r_int
r_int
id|st_gen
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* The stat64 structure increases the size of dev_t, blkcnt_t, adds&n;   nanosecond resolution times, and padding for expansion.  */
DECL|struct|stat64
r_struct
id|stat64
(brace
DECL|member|st_dev
r_int
r_int
id|st_dev
suffix:semicolon
DECL|member|st_ino
r_int
r_int
id|st_ino
suffix:semicolon
DECL|member|st_rdev
r_int
r_int
id|st_rdev
suffix:semicolon
DECL|member|st_size
r_int
id|st_size
suffix:semicolon
DECL|member|st_blocks
r_int
r_int
id|st_blocks
suffix:semicolon
DECL|member|st_mode
r_int
r_int
id|st_mode
suffix:semicolon
DECL|member|st_uid
r_int
r_int
id|st_uid
suffix:semicolon
DECL|member|st_gid
r_int
r_int
id|st_gid
suffix:semicolon
DECL|member|st_blksize
r_int
r_int
id|st_blksize
suffix:semicolon
DECL|member|st_nlink
r_int
r_int
id|st_nlink
suffix:semicolon
DECL|member|__pad0
r_int
r_int
id|__pad0
suffix:semicolon
DECL|member|st_atime
r_int
r_int
id|st_atime
suffix:semicolon
DECL|member|st_atime_nsec
r_int
r_int
id|st_atime_nsec
suffix:semicolon
DECL|member|st_mtime
r_int
r_int
id|st_mtime
suffix:semicolon
DECL|member|st_mtime_nsec
r_int
r_int
id|st_mtime_nsec
suffix:semicolon
DECL|member|st_ctime
r_int
r_int
id|st_ctime
suffix:semicolon
DECL|member|st_ctime_nsec
r_int
r_int
id|st_ctime_nsec
suffix:semicolon
DECL|member|__unused
r_int
id|__unused
(braket
l_int|3
)braket
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
eof
