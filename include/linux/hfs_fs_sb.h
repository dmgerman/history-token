multiline_comment|/* &n; * linux/include/linux/hfs_fs_sb.h&n; *&n; * Copyright (C) 1995-1997  Paul H. Hargrove&n; * This file may be distributed under the terms of the GNU Public License.&n; *&n; * This file defines the type (struct hfs_sb_info) which contains the&n; * HFS-specific information in the in-core superblock.&n; */
macro_line|#ifndef _LINUX_HFS_FS_SB_H
DECL|macro|_LINUX_HFS_FS_SB_H
mdefine_line|#define _LINUX_HFS_FS_SB_H
multiline_comment|/* forward declaration: */
r_struct
id|hfs_name
suffix:semicolon
DECL|typedef|hfs_namein_fn
r_typedef
r_int
(paren
op_star
id|hfs_namein_fn
)paren
(paren
r_char
op_star
comma
r_const
r_struct
id|hfs_name
op_star
)paren
suffix:semicolon
DECL|typedef|hfs_nameout_fn
r_typedef
r_void
(paren
op_star
id|hfs_nameout_fn
)paren
(paren
r_struct
id|hfs_name
op_star
comma
r_const
r_char
op_star
comma
r_int
)paren
suffix:semicolon
DECL|typedef|hfs_ifill_fn
r_typedef
r_void
(paren
op_star
id|hfs_ifill_fn
)paren
(paren
r_struct
id|inode
op_star
comma
id|ino_t
comma
r_const
r_int
)paren
suffix:semicolon
multiline_comment|/*&n; * struct hfs_sb_info&n; *&n; * The HFS-specific part of a Linux (struct super_block)&n; */
DECL|struct|hfs_sb_info
r_struct
id|hfs_sb_info
(brace
DECL|member|magic
r_int
id|magic
suffix:semicolon
multiline_comment|/* A magic number */
DECL|member|s_mdb
r_struct
id|hfs_mdb
op_star
id|s_mdb
suffix:semicolon
multiline_comment|/* The HFS MDB */
DECL|member|s_quiet
r_int
id|s_quiet
suffix:semicolon
multiline_comment|/* Silent failure when &n;&t;&t;&t;&t;&t;&t;   changing owner or mode? */
DECL|member|s_lowercase
r_int
id|s_lowercase
suffix:semicolon
multiline_comment|/* Map names to lowercase? */
DECL|member|s_afpd
r_int
id|s_afpd
suffix:semicolon
multiline_comment|/* AFPD compatible mode? */
DECL|member|s_version
r_int
id|s_version
suffix:semicolon
multiline_comment|/* version info */
DECL|member|s_namein
id|hfs_namein_fn
id|s_namein
suffix:semicolon
multiline_comment|/* The function used to&n;&t;&t;&t;&t;&t;&t;   map Mac filenames to&n;&t;&t;&t;&t;&t;&t;   Linux filenames */
DECL|member|s_nameout
id|hfs_nameout_fn
id|s_nameout
suffix:semicolon
multiline_comment|/* The function used to&n;&t;&t;&t;&t;&t;&t;    map Linux filenames&n;&t;&t;&t;&t;&t;&t;    to Mac filenames */
DECL|member|s_ifill
id|hfs_ifill_fn
id|s_ifill
suffix:semicolon
multiline_comment|/* The function used&n;&t;&t;&t;&t;&t;&t;   to fill in inode fields */
DECL|member|s_reserved1
r_const
r_struct
id|hfs_name
op_star
id|s_reserved1
suffix:semicolon
multiline_comment|/* Reserved names */
DECL|member|s_reserved2
r_const
r_struct
id|hfs_name
op_star
id|s_reserved2
suffix:semicolon
multiline_comment|/* Reserved names */
DECL|member|s_type
id|__u32
id|s_type
suffix:semicolon
multiline_comment|/* Type for new files */
DECL|member|s_creator
id|__u32
id|s_creator
suffix:semicolon
multiline_comment|/* Creator for new files */
DECL|member|s_umask
id|umode_t
id|s_umask
suffix:semicolon
multiline_comment|/* The umask applied to the&n;&t;&t;&t;&t;&t;&t;   permissions on all files */
DECL|member|s_uid
id|uid_t
id|s_uid
suffix:semicolon
multiline_comment|/* The uid of all files */
DECL|member|s_gid
id|gid_t
id|s_gid
suffix:semicolon
multiline_comment|/* The gid of all files */
DECL|member|s_conv
r_char
id|s_conv
suffix:semicolon
multiline_comment|/* Type of text conversion */
)brace
suffix:semicolon
macro_line|#endif
eof
