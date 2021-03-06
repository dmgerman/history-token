macro_line|#ifndef _PPC64_STATFS_H
DECL|macro|_PPC64_STATFS_H
mdefine_line|#define _PPC64_STATFS_H
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef __KERNEL_STRICT_NAMES
macro_line|#include &lt;linux/types.h&gt;
DECL|typedef|fsid_t
r_typedef
id|__kernel_fsid_t
id|fsid_t
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * We&squot;re already 64-bit, so duplicate the definition&n; */
DECL|struct|statfs
r_struct
id|statfs
(brace
DECL|member|f_type
r_int
id|f_type
suffix:semicolon
DECL|member|f_bsize
r_int
id|f_bsize
suffix:semicolon
DECL|member|f_blocks
r_int
id|f_blocks
suffix:semicolon
DECL|member|f_bfree
r_int
id|f_bfree
suffix:semicolon
DECL|member|f_bavail
r_int
id|f_bavail
suffix:semicolon
DECL|member|f_files
r_int
id|f_files
suffix:semicolon
DECL|member|f_ffree
r_int
id|f_ffree
suffix:semicolon
DECL|member|f_fsid
id|__kernel_fsid_t
id|f_fsid
suffix:semicolon
DECL|member|f_namelen
r_int
id|f_namelen
suffix:semicolon
DECL|member|f_frsize
r_int
id|f_frsize
suffix:semicolon
DECL|member|f_spare
r_int
id|f_spare
(braket
l_int|5
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|statfs64
r_struct
id|statfs64
(brace
DECL|member|f_type
r_int
id|f_type
suffix:semicolon
DECL|member|f_bsize
r_int
id|f_bsize
suffix:semicolon
DECL|member|f_blocks
r_int
id|f_blocks
suffix:semicolon
DECL|member|f_bfree
r_int
id|f_bfree
suffix:semicolon
DECL|member|f_bavail
r_int
id|f_bavail
suffix:semicolon
DECL|member|f_files
r_int
id|f_files
suffix:semicolon
DECL|member|f_ffree
r_int
id|f_ffree
suffix:semicolon
DECL|member|f_fsid
id|__kernel_fsid_t
id|f_fsid
suffix:semicolon
DECL|member|f_namelen
r_int
id|f_namelen
suffix:semicolon
DECL|member|f_frsize
r_int
id|f_frsize
suffix:semicolon
DECL|member|f_spare
r_int
id|f_spare
(braket
l_int|5
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|compat_statfs64
r_struct
id|compat_statfs64
(brace
DECL|member|f_type
id|__u32
id|f_type
suffix:semicolon
DECL|member|f_bsize
id|__u32
id|f_bsize
suffix:semicolon
DECL|member|f_blocks
id|__u64
id|f_blocks
suffix:semicolon
DECL|member|f_bfree
id|__u64
id|f_bfree
suffix:semicolon
DECL|member|f_bavail
id|__u64
id|f_bavail
suffix:semicolon
DECL|member|f_files
id|__u64
id|f_files
suffix:semicolon
DECL|member|f_ffree
id|__u64
id|f_ffree
suffix:semicolon
DECL|member|f_fsid
id|__kernel_fsid_t
id|f_fsid
suffix:semicolon
DECL|member|f_namelen
id|__u32
id|f_namelen
suffix:semicolon
DECL|member|f_frsize
id|__u32
id|f_frsize
suffix:semicolon
DECL|member|f_spare
id|__u32
id|f_spare
(braket
l_int|5
)braket
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif  /* _PPC64_STATFS_H */
eof
