macro_line|#ifndef _ASM_STAT_H
DECL|macro|_ASM_STAT_H
mdefine_line|#define _ASM_STAT_H
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
multiline_comment|/* This matches struct stat in uClibc/glibc.  */
DECL|struct|stat
r_struct
id|stat
(brace
DECL|member|__pad1
r_int
r_char
id|__pad1
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|st_dev
r_int
r_int
id|st_dev
suffix:semicolon
DECL|member|__pad2
r_int
r_int
id|__pad2
suffix:semicolon
DECL|member|st_ino
r_int
r_int
id|st_ino
suffix:semicolon
DECL|member|__pad3
r_int
r_int
id|__pad3
suffix:semicolon
DECL|member|st_mode
r_int
r_int
id|st_mode
suffix:semicolon
DECL|member|__pad4
r_int
r_int
id|__pad4
suffix:semicolon
DECL|member|st_nlink
r_int
r_int
id|st_nlink
suffix:semicolon
DECL|member|__pad5
r_int
r_int
id|__pad5
suffix:semicolon
DECL|member|st_uid
r_int
r_int
id|st_uid
suffix:semicolon
DECL|member|__pad6
r_int
r_int
id|__pad6
suffix:semicolon
DECL|member|st_gid
r_int
r_int
id|st_gid
suffix:semicolon
DECL|member|__pad7
r_int
r_char
id|__pad7
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|st_rdev
r_int
r_int
id|st_rdev
suffix:semicolon
DECL|member|__pad8
r_int
r_int
id|__pad8
suffix:semicolon
DECL|member|st_size
r_int
r_int
id|st_size
suffix:semicolon
DECL|member|__pad9
r_int
r_int
id|__pad9
suffix:semicolon
multiline_comment|/* align 64-bit st_blocks to 2-word */
DECL|member|st_blksize
r_int
r_int
id|st_blksize
suffix:semicolon
DECL|member|__pad10
r_int
r_int
id|__pad10
suffix:semicolon
multiline_comment|/* future possible st_blocks high bits */
DECL|member|st_blocks
r_int
r_int
id|st_blocks
suffix:semicolon
multiline_comment|/* Number 512-byte blocks allocated. */
DECL|member|__unused1
r_int
r_int
id|__unused1
suffix:semicolon
DECL|member|st_atime
r_int
r_int
id|st_atime
suffix:semicolon
DECL|member|__unused2
r_int
r_int
id|__unused2
suffix:semicolon
DECL|member|st_mtime
r_int
r_int
id|st_mtime
suffix:semicolon
DECL|member|__unused3
r_int
r_int
id|__unused3
suffix:semicolon
DECL|member|st_ctime
r_int
r_int
id|st_ctime
suffix:semicolon
DECL|member|__unused4
r_int
r_int
r_int
id|__unused4
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* This matches struct stat64 in uClibc/glibc.  The layout is exactly&n;   the same as that of struct stat above, with 64-bit types taking up&n;   space that was formerly used by padding.  stat syscalls are still&n;   different from stat64, though, in that the former tests for&n;   overflow.  */
DECL|struct|stat64
r_struct
id|stat64
(brace
DECL|member|__pad1
r_int
r_char
id|__pad1
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|st_dev
r_int
r_int
id|st_dev
suffix:semicolon
DECL|member|st_ino
r_int
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
DECL|member|__pad2
r_int
r_char
id|__pad2
(braket
l_int|6
)braket
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
DECL|member|__pad3
r_int
r_int
id|__pad3
suffix:semicolon
multiline_comment|/* align 64-bit st_blocks to 2-word */
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
DECL|member|st_atime_nsec
r_int
r_int
id|st_atime_nsec
suffix:semicolon
DECL|member|st_atime
r_int
r_int
id|st_atime
suffix:semicolon
DECL|member|st_mtime_nsec
r_int
r_int
id|st_mtime_nsec
suffix:semicolon
DECL|member|st_mtime
r_int
r_int
id|st_mtime
suffix:semicolon
DECL|member|st_ctime_nsec
r_int
r_int
id|st_ctime_nsec
suffix:semicolon
DECL|member|st_ctime
r_int
r_int
id|st_ctime
suffix:semicolon
DECL|member|__unused4
r_int
r_int
r_int
id|__unused4
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* _ASM_STAT_H */
eof
