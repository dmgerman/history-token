multiline_comment|/*&n; *   fs/cifs/cifs_fs_sb.h&n; *&n; *   Copyright (c) International Business Machines  Corp., 2002&n; *   Author(s): Steve French (sfrench@us.ibm.com)&n; *&n; *   This library is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU Lesser General Public License as published&n; *   by the Free Software Foundation; either version 2.1 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This library is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See&n; *   the GNU Lesser General Public License for more details.&n; *&n; */
macro_line|#ifndef _CIFS_FS_SB_H
DECL|macro|_CIFS_FS_SB_H
mdefine_line|#define _CIFS_FS_SB_H
DECL|macro|CIFS_MOUNT_NO_PERM
mdefine_line|#define CIFS_MOUNT_NO_PERM      1 /* do not do client vfs_perm check */
DECL|macro|CIFS_MOUNT_SET_UID
mdefine_line|#define CIFS_MOUNT_SET_UID      2 /* set current-&gt;euid in create etc. */
DECL|macro|CIFS_MOUNT_SERVER_INUM
mdefine_line|#define CIFS_MOUNT_SERVER_INUM  4 /* inode numbers from uniqueid from server */
DECL|struct|cifs_sb_info
r_struct
id|cifs_sb_info
(brace
DECL|member|tcon
r_struct
id|cifsTconInfo
op_star
id|tcon
suffix:semicolon
multiline_comment|/* primary mount */
DECL|member|nested_tcon_q
r_struct
id|list_head
id|nested_tcon_q
suffix:semicolon
DECL|member|local_nls
r_struct
id|nls_table
op_star
id|local_nls
suffix:semicolon
DECL|member|rsize
r_int
r_int
id|rsize
suffix:semicolon
DECL|member|wsize
r_int
r_int
id|wsize
suffix:semicolon
DECL|member|mnt_uid
id|uid_t
id|mnt_uid
suffix:semicolon
DECL|member|mnt_gid
id|gid_t
id|mnt_gid
suffix:semicolon
DECL|member|mnt_file_mode
id|mode_t
id|mnt_file_mode
suffix:semicolon
DECL|member|mnt_dir_mode
id|mode_t
id|mnt_dir_mode
suffix:semicolon
DECL|member|mnt_cifs_flags
r_int
id|mnt_cifs_flags
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif&t;&t;&t;&t;/* _CIFS_FS_SB_H */
eof
