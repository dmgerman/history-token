multiline_comment|/*&n; * Definitions for the statfs(2) call.&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1995 by Ralf Baechle&n; */
macro_line|#ifndef __ASM_MIPS_STATFS_H
DECL|macro|__ASM_MIPS_STATFS_H
mdefine_line|#define __ASM_MIPS_STATFS_H
macro_line|#include &lt;linux/posix_types.h&gt;
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
macro_line|#endif /* __ASM_MIPS_STATFS_H */
eof
