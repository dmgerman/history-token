multiline_comment|/* &n; * linux/include/linux/hfs_fs_i.h&n; *&n; * Copyright (C) 1995, 1996  Paul H. Hargrove&n; * This file may be distributed under the terms of the GNU General Public License.&n; *&n; * This file defines the type (struct hfs_inode_info) and the two&n; * subordinate types hfs_extent and hfs_file.&n; */
macro_line|#ifndef _LINUX_HFS_FS_I_H
DECL|macro|_LINUX_HFS_FS_I_H
mdefine_line|#define _LINUX_HFS_FS_I_H
multiline_comment|/*&n; * struct hfs_inode_info&n; *&n; * The HFS-specific part of a Linux (struct inode)&n; */
DECL|struct|hfs_inode_info
r_struct
id|hfs_inode_info
(brace
DECL|member|magic
r_int
id|magic
suffix:semicolon
multiline_comment|/* A magic number */
DECL|member|mmu_private
r_int
r_int
id|mmu_private
suffix:semicolon
DECL|member|entry
r_struct
id|hfs_cat_entry
op_star
id|entry
suffix:semicolon
multiline_comment|/* For a regular or header file */
DECL|member|fork
r_struct
id|hfs_fork
op_star
id|fork
suffix:semicolon
DECL|member|convert
r_int
id|convert
suffix:semicolon
multiline_comment|/* For a directory */
DECL|member|file_type
id|ino_t
id|file_type
suffix:semicolon
DECL|member|dir_size
r_char
id|dir_size
suffix:semicolon
multiline_comment|/* For header files */
DECL|member|default_layout
r_const
r_struct
id|hfs_hdr_layout
op_star
id|default_layout
suffix:semicolon
DECL|member|layout
r_struct
id|hfs_hdr_layout
op_star
id|layout
suffix:semicolon
multiline_comment|/* to deal with localtime ugliness */
DECL|member|tz_secondswest
r_int
id|tz_secondswest
suffix:semicolon
multiline_comment|/* for dentry cleanup */
DECL|member|d_drop_op
r_void
(paren
op_star
id|d_drop_op
)paren
(paren
r_struct
id|dentry
op_star
comma
r_const
id|ino_t
)paren
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
eof
