multiline_comment|/*&n; *&t;Definitions of structures for vfsv0 quota format&n; */
macro_line|#ifndef _LINUX_DQBLK_V2_H
DECL|macro|_LINUX_DQBLK_V2_H
mdefine_line|#define _LINUX_DQBLK_V2_H
macro_line|#include &lt;linux/types.h&gt;
multiline_comment|/* id numbers of quota format */
DECL|macro|QFMT_VFS_V0
mdefine_line|#define QFMT_VFS_V0 2
multiline_comment|/* Inmemory copy of version specific information */
DECL|struct|v2_mem_dqinfo
r_struct
id|v2_mem_dqinfo
(brace
DECL|member|dqi_blocks
r_int
r_int
id|dqi_blocks
suffix:semicolon
DECL|member|dqi_free_blk
r_int
r_int
id|dqi_free_blk
suffix:semicolon
DECL|member|dqi_free_entry
r_int
r_int
id|dqi_free_entry
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* _LINUX_DQBLK_V2_H */
eof
