macro_line|#ifndef _MSDOS_FS_I
DECL|macro|_MSDOS_FS_I
mdefine_line|#define _MSDOS_FS_I
macro_line|#include &lt;linux/fs.h&gt;
multiline_comment|/*&n; * MS-DOS file system inode data in memory&n; */
DECL|struct|msdos_inode_info
r_struct
id|msdos_inode_info
(brace
DECL|member|cache_lru_lock
id|spinlock_t
id|cache_lru_lock
suffix:semicolon
DECL|member|cache_lru
r_struct
id|list_head
id|cache_lru
suffix:semicolon
DECL|member|nr_caches
r_int
id|nr_caches
suffix:semicolon
DECL|member|mmu_private
id|loff_t
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
DECL|member|i_pos
id|loff_t
id|i_pos
suffix:semicolon
multiline_comment|/* on-disk position of directory entry or 0 */
DECL|member|i_fat_hash
r_struct
id|hlist_node
id|i_fat_hash
suffix:semicolon
multiline_comment|/* hash by i_location */
DECL|member|vfs_inode
r_struct
id|inode
id|vfs_inode
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
eof
