multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1995, 1999 by Ralf Baechle&n; */
macro_line|#ifndef _ASM_STATFS_H
DECL|macro|_ASM_STATFS_H
mdefine_line|#define _ASM_STATFS_H
macro_line|#include &lt;linux/posix_types.h&gt;
macro_line|#include &lt;asm/sgidefs.h&gt;
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
DECL|member|f_type
r_int
id|f_type
suffix:semicolon
DECL|macro|f_fstyp
mdefine_line|#define f_fstyp f_type
DECL|member|f_bsize
r_int
id|f_bsize
suffix:semicolon
DECL|member|f_frsize
r_int
id|f_frsize
suffix:semicolon
multiline_comment|/* Fragment size - unsupported */
DECL|member|f_blocks
r_int
id|f_blocks
suffix:semicolon
DECL|member|f_bfree
r_int
id|f_bfree
suffix:semicolon
DECL|member|f_files
r_int
id|f_files
suffix:semicolon
DECL|member|f_ffree
r_int
id|f_ffree
suffix:semicolon
multiline_comment|/* Linux specials */
DECL|member|f_bavail
r_int
id|f_bavail
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
)brace
suffix:semicolon
macro_line|#if (_MIPS_SIM == _MIPS_SIM_ABI32) || (_MIPS_SIM == _MIPS_SIM_NABI32)
multiline_comment|/*&n; * Unlike the traditional version the LFAPI version has none of the ABI junk&n; */
DECL|struct|statfs64
r_struct
id|statfs64
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
macro_line|#endif /* _MIPS_SIM == _MIPS_SIM_ABI32 */
macro_line|#if _MIPS_SIM == _MIPS_SIM_ABI64
DECL|struct|statfs64
r_struct
id|statfs64
(brace
multiline_comment|/* Same as struct statfs */
DECL|member|f_type
r_int
id|f_type
suffix:semicolon
DECL|member|f_bsize
r_int
id|f_bsize
suffix:semicolon
DECL|member|f_frsize
r_int
id|f_frsize
suffix:semicolon
multiline_comment|/* Fragment size - unsupported */
DECL|member|f_blocks
r_int
id|f_blocks
suffix:semicolon
DECL|member|f_bfree
r_int
id|f_bfree
suffix:semicolon
DECL|member|f_files
r_int
id|f_files
suffix:semicolon
DECL|member|f_ffree
r_int
id|f_ffree
suffix:semicolon
multiline_comment|/* Linux specials */
DECL|member|f_bavail
r_int
id|f_bavail
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
)brace
suffix:semicolon
macro_line|#endif /* _MIPS_SIM == _MIPS_SIM_ABI64 */
macro_line|#endif /* _ASM_STATFS_H */
eof
