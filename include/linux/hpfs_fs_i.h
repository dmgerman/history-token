macro_line|#ifndef _HPFS_FS_I
DECL|macro|_HPFS_FS_I
mdefine_line|#define _HPFS_FS_I
DECL|struct|hpfs_inode_info
r_struct
id|hpfs_inode_info
(brace
DECL|member|mmu_private
r_int
r_int
id|mmu_private
suffix:semicolon
DECL|member|i_parent_dir
id|ino_t
id|i_parent_dir
suffix:semicolon
multiline_comment|/* (directories) gives fnode of parent dir */
DECL|member|i_dno
r_int
id|i_dno
suffix:semicolon
multiline_comment|/* (directories) root dnode */
DECL|member|i_dpos
r_int
id|i_dpos
suffix:semicolon
multiline_comment|/* (directories) temp for readdir */
DECL|member|i_dsubdno
r_int
id|i_dsubdno
suffix:semicolon
multiline_comment|/* (directories) temp for readdir */
DECL|member|i_file_sec
r_int
id|i_file_sec
suffix:semicolon
multiline_comment|/* (files) minimalist cache of alloc info */
DECL|member|i_disk_sec
r_int
id|i_disk_sec
suffix:semicolon
multiline_comment|/* (files) minimalist cache of alloc info */
DECL|member|i_n_secs
r_int
id|i_n_secs
suffix:semicolon
multiline_comment|/* (files) minimalist cache of alloc info */
DECL|member|i_ea_size
r_int
id|i_ea_size
suffix:semicolon
multiline_comment|/* size of extended attributes */
DECL|member|i_conv
r_int
id|i_conv
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* (files) crlf-&gt;newline hackery */
DECL|member|i_ea_mode
r_int
id|i_ea_mode
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* file&squot;s permission is stored in ea */
DECL|member|i_ea_uid
r_int
id|i_ea_uid
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* file&squot;s uid is stored in ea */
DECL|member|i_ea_gid
r_int
id|i_ea_gid
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* file&squot;s gid is stored in ea */
DECL|member|i_dirty
r_int
id|i_dirty
suffix:colon
l_int|1
suffix:semicolon
DECL|member|i_sem
r_struct
id|semaphore
id|i_sem
suffix:semicolon
multiline_comment|/* semaphore */
DECL|member|i_rddir_off
id|loff_t
op_star
op_star
id|i_rddir_off
suffix:semicolon
DECL|member|vfs_inode
r_struct
id|inode
id|vfs_inode
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
eof
