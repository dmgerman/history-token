macro_line|#ifndef _M68K_STAT_H
DECL|macro|_M68K_STAT_H
mdefine_line|#define _M68K_STAT_H
DECL|struct|__old_kernel_stat
r_struct
id|__old_kernel_stat
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
)brace
suffix:semicolon
DECL|struct|stat
r_struct
id|stat
(brace
DECL|member|st_dev
r_int
r_int
id|st_dev
suffix:semicolon
DECL|member|__pad1
r_int
r_int
id|__pad1
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
DECL|member|__pad2
r_int
r_int
id|__pad2
suffix:semicolon
DECL|member|st_size
r_int
r_int
id|st_size
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
DECL|member|st_atime
r_int
r_int
id|st_atime
suffix:semicolon
DECL|member|__unused1
r_int
r_int
id|__unused1
suffix:semicolon
DECL|member|st_mtime
r_int
r_int
id|st_mtime
suffix:semicolon
DECL|member|__unused2
r_int
r_int
id|__unused2
suffix:semicolon
DECL|member|st_ctime
r_int
r_int
id|st_ctime
suffix:semicolon
DECL|member|__unused3
r_int
r_int
id|__unused3
suffix:semicolon
DECL|member|__unused4
r_int
r_int
id|__unused4
suffix:semicolon
DECL|member|__unused5
r_int
r_int
id|__unused5
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* This matches struct stat64 in glibc2.1, hence the absolutely&n; * insane amounts of padding around dev_t&squot;s.&n; */
DECL|struct|stat64
r_struct
id|stat64
(brace
DECL|member|st_dev
r_int
r_int
r_int
id|st_dev
suffix:semicolon
DECL|member|__pad1
r_int
r_char
id|__pad1
(braket
l_int|2
)braket
suffix:semicolon
DECL|macro|STAT64_HAS_BROKEN_ST_INO
mdefine_line|#define STAT64_HAS_BROKEN_ST_INO&t;1
DECL|member|__st_ino
r_int
r_int
id|__st_ino
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
r_int
id|st_rdev
suffix:semicolon
DECL|member|__pad3
r_int
r_char
id|__pad3
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|st_size
r_int
r_int
id|st_size
suffix:semicolon
DECL|member|st_blksize
r_int
r_int
id|st_blksize
suffix:semicolon
DECL|member|__pad4
r_int
r_int
id|__pad4
suffix:semicolon
multiline_comment|/* future possible st_blocks high bits */
DECL|member|st_blocks
r_int
r_int
id|st_blocks
suffix:semicolon
multiline_comment|/* Number 512-byte blocks allocated. */
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
DECL|member|st_ino
r_int
r_int
r_int
id|st_ino
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* _M68K_STAT_H */
eof
