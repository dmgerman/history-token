macro_line|#ifndef _MSDOS_FS_I
DECL|macro|_MSDOS_FS_I
mdefine_line|#define _MSDOS_FS_I
multiline_comment|/*&n; * MS-DOS file system inode data in memory&n; */
DECL|struct|msdos_inode_info
r_struct
id|msdos_inode_info
(brace
DECL|member|mmu_private
r_int
r_int
id|mmu_private
suffix:semicolon
DECL|member|i_start
r_int
id|i_start
suffix:semicolon
multiline_comment|/* first cluster or 0 */
DECL|member|i_logstart
r_int
id|i_logstart
suffix:semicolon
multiline_comment|/* logical first cluster */
DECL|member|i_attrs
r_int
id|i_attrs
suffix:semicolon
multiline_comment|/* unused attribute bits */
DECL|member|i_ctime_ms
r_int
id|i_ctime_ms
suffix:semicolon
multiline_comment|/* unused change time in milliseconds */
DECL|member|i_location
r_int
id|i_location
suffix:semicolon
multiline_comment|/* on-disk position of directory entry or 0 */
DECL|member|i_fat_inode
r_struct
id|inode
op_star
id|i_fat_inode
suffix:semicolon
multiline_comment|/* struct inode of this one */
DECL|member|i_fat_hash
r_struct
id|list_head
id|i_fat_hash
suffix:semicolon
multiline_comment|/* hash by i_location */
)brace
suffix:semicolon
macro_line|#endif
eof
