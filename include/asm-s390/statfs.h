multiline_comment|/*&n; *  include/asm-s390/statfs.h&n; *&n; *  S390 version&n; *&n; *  Derived from &quot;include/asm-i386/statfs.h&quot;&n; */
macro_line|#ifndef _S390_STATFS_H
DECL|macro|_S390_STATFS_H
mdefine_line|#define _S390_STATFS_H
macro_line|#ifndef __KERNEL_STRICT_NAMES
macro_line|#include &lt;linux/types.h&gt;
DECL|typedef|fsid_t
r_typedef
id|__kernel_fsid_t
id|fsid_t
suffix:semicolon
macro_line|#endif
DECL|struct|statfs
r_struct
id|statfs
(brace
macro_line|#ifndef __s390x__
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
DECL|member|f_spare
r_int
id|f_spare
(braket
l_int|6
)braket
suffix:semicolon
macro_line|#else /* __s390x__ */
r_int
id|f_type
suffix:semicolon
r_int
id|f_bsize
suffix:semicolon
r_int
id|f_blocks
suffix:semicolon
r_int
id|f_bfree
suffix:semicolon
r_int
id|f_bavail
suffix:semicolon
r_int
id|f_files
suffix:semicolon
r_int
id|f_ffree
suffix:semicolon
id|__kernel_fsid_t
id|f_fsid
suffix:semicolon
r_int
id|f_namelen
suffix:semicolon
r_int
id|f_spare
(braket
l_int|6
)braket
suffix:semicolon
macro_line|#endif /* __s390x__ */
)brace
suffix:semicolon
macro_line|#endif
eof
