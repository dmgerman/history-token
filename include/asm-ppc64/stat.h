macro_line|#ifndef _PPC64_STAT_H
DECL|macro|_PPC64_STAT_H
mdefine_line|#define _PPC64_STAT_H
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/types.h&gt;
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
id|ino_t
id|st_ino
suffix:semicolon
DECL|member|st_nlink
id|nlink_t
id|st_nlink
suffix:semicolon
DECL|member|st_mode
id|mode_t
id|st_mode
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
r_int
r_int
id|st_rdev
suffix:semicolon
DECL|member|st_size
id|off_t
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
DECL|member|__unused6
r_int
r_int
id|__unused6
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|STAT_HAVE_NSEC
mdefine_line|#define STAT_HAVE_NSEC 1
multiline_comment|/* This matches struct stat64 in glibc2.1. Only used for 32 bit. */
DECL|struct|stat64
r_struct
id|stat64
(brace
DECL|member|st_dev
r_int
r_int
id|st_dev
suffix:semicolon
multiline_comment|/* Device.  */
DECL|member|st_ino
r_int
r_int
id|st_ino
suffix:semicolon
multiline_comment|/* File serial number.  */
DECL|member|st_mode
r_int
r_int
id|st_mode
suffix:semicolon
multiline_comment|/* File mode.  */
DECL|member|st_nlink
r_int
r_int
id|st_nlink
suffix:semicolon
multiline_comment|/* Link count.  */
DECL|member|st_uid
r_int
r_int
id|st_uid
suffix:semicolon
multiline_comment|/* User ID of the file&squot;s owner.  */
DECL|member|st_gid
r_int
r_int
id|st_gid
suffix:semicolon
multiline_comment|/* Group ID of the file&squot;s group. */
DECL|member|st_rdev
r_int
r_int
id|st_rdev
suffix:semicolon
multiline_comment|/* Device number, if device.  */
DECL|member|__pad2
r_int
r_int
id|__pad2
suffix:semicolon
DECL|member|st_size
r_int
id|st_size
suffix:semicolon
multiline_comment|/* Size of file, in bytes.  */
DECL|member|st_blksize
r_int
id|st_blksize
suffix:semicolon
multiline_comment|/* Optimal block size for I/O.  */
DECL|member|st_blocks
r_int
id|st_blocks
suffix:semicolon
multiline_comment|/* Number 512-byte blocks allocated. */
DECL|member|st_atime
r_int
id|st_atime
suffix:semicolon
multiline_comment|/* Time of last access.  */
DECL|member|st_atime_nsec
r_int
id|st_atime_nsec
suffix:semicolon
DECL|member|st_mtime
r_int
id|st_mtime
suffix:semicolon
multiline_comment|/* Time of last modification.  */
DECL|member|st_mtime_nsec
r_int
id|st_mtime_nsec
suffix:semicolon
DECL|member|st_ctime
r_int
id|st_ctime
suffix:semicolon
multiline_comment|/* Time of last status change.  */
DECL|member|st_ctime_nsec
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
eof
