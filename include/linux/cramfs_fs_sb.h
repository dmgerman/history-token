macro_line|#ifndef _CRAMFS_FS_SB
DECL|macro|_CRAMFS_FS_SB
mdefine_line|#define _CRAMFS_FS_SB
multiline_comment|/*&n; * cramfs super-block data in memory&n; */
DECL|struct|cramfs_sb_info
r_struct
id|cramfs_sb_info
(brace
DECL|member|magic
r_int
r_int
id|magic
suffix:semicolon
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
DECL|member|blocks
r_int
r_int
id|blocks
suffix:semicolon
DECL|member|files
r_int
r_int
id|files
suffix:semicolon
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
eof
