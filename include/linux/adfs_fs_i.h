multiline_comment|/*&n; *  linux/include/linux/adfs_fs_i.h&n; *&n; * Copyright (C) 1997 Russell King&n; */
macro_line|#ifndef _ADFS_FS_I
DECL|macro|_ADFS_FS_I
mdefine_line|#define _ADFS_FS_I
multiline_comment|/*&n; * adfs file system inode data in memory&n; */
DECL|struct|adfs_inode_info
r_struct
id|adfs_inode_info
(brace
DECL|member|mmu_private
r_int
r_int
id|mmu_private
suffix:semicolon
DECL|member|parent_id
r_int
r_int
id|parent_id
suffix:semicolon
multiline_comment|/* object id of parent&t;&t;*/
DECL|member|loadaddr
id|__u32
id|loadaddr
suffix:semicolon
multiline_comment|/* RISC OS load address&t;&t;*/
DECL|member|execaddr
id|__u32
id|execaddr
suffix:semicolon
multiline_comment|/* RISC OS exec address&t;&t;*/
DECL|member|filetype
r_int
r_int
id|filetype
suffix:semicolon
multiline_comment|/* RISC OS file type&t;&t;*/
DECL|member|attr
r_int
r_int
id|attr
suffix:semicolon
multiline_comment|/* RISC OS permissions&t;&t;*/
DECL|member|stamped
r_int
id|stamped
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* RISC OS file has date/time&t;*/
DECL|member|vfs_inode
r_struct
id|inode
id|vfs_inode
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
eof
