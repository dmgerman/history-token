multiline_comment|/* $Id: stat.h,v 1.7 2000/08/04 05:35:55 davem Exp $ */
macro_line|#ifndef _SPARC64_STAT_H
DECL|macro|_SPARC64_STAT_H
mdefine_line|#define _SPARC64_STAT_H
macro_line|#include &lt;linux/types.h&gt;
DECL|struct|stat
r_struct
id|stat
(brace
DECL|member|st_dev
id|dev_t
id|st_dev
suffix:semicolon
DECL|member|st_ino
id|ino_t
id|st_ino
suffix:semicolon
DECL|member|st_mode
id|mode_t
id|st_mode
suffix:semicolon
DECL|member|st_nlink
r_int
id|st_nlink
suffix:semicolon
DECL|member|st_uid
id|uid_t
id|st_uid
suffix:semicolon
DECL|member|st_gid
id|gid_t
id|st_gid
suffix:semicolon
DECL|member|st_rdev
id|dev_t
id|st_rdev
suffix:semicolon
DECL|member|st_size
id|off_t
id|st_size
suffix:semicolon
DECL|member|st_atime
id|time_t
id|st_atime
suffix:semicolon
DECL|member|st_mtime
id|time_t
id|st_mtime
suffix:semicolon
DECL|member|st_ctime
id|time_t
id|st_ctime
suffix:semicolon
DECL|member|st_blksize
id|off_t
id|st_blksize
suffix:semicolon
DECL|member|st_blocks
id|off_t
id|st_blocks
suffix:semicolon
DECL|member|__unused4
r_int
r_int
id|__unused4
(braket
l_int|2
)braket
suffix:semicolon
)brace
suffix:semicolon
macro_line|#ifdef __KERNEL__
multiline_comment|/* This is sparc32 stat64 structure. */
DECL|struct|stat64
r_struct
id|stat64
(brace
DECL|member|__pad0
r_int
r_char
id|__pad0
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
DECL|member|__pad3
r_int
r_char
id|__pad3
(braket
l_int|8
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
r_char
id|__pad4
(braket
l_int|8
)braket
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
macro_line|#endif
macro_line|#endif
eof
