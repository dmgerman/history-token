macro_line|#ifndef __ROMFS_FS_I
DECL|macro|__ROMFS_FS_I
mdefine_line|#define __ROMFS_FS_I
multiline_comment|/* inode in-kernel data */
DECL|struct|romfs_inode_info
r_struct
id|romfs_inode_info
(brace
DECL|member|i_metasize
r_int
r_int
id|i_metasize
suffix:semicolon
multiline_comment|/* size of non-data area */
DECL|member|i_dataoffset
r_int
r_int
id|i_dataoffset
suffix:semicolon
multiline_comment|/* from the start of fs */
)brace
suffix:semicolon
macro_line|#endif
eof
