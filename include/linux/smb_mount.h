multiline_comment|/*&n; *  smb_mount.h&n; *&n; *  Copyright (C) 1995, 1996 by Paal-Kr. Engstad and Volker Lendecke&n; *  Copyright (C) 1997 by Volker Lendecke&n; *&n; */
macro_line|#ifndef _LINUX_SMB_MOUNT_H
DECL|macro|_LINUX_SMB_MOUNT_H
mdefine_line|#define _LINUX_SMB_MOUNT_H
macro_line|#include &lt;linux/types.h&gt;
DECL|macro|SMB_MOUNT_VERSION
mdefine_line|#define SMB_MOUNT_VERSION&t;6
DECL|struct|smb_mount_data
r_struct
id|smb_mount_data
(brace
DECL|member|version
r_int
id|version
suffix:semicolon
DECL|member|mounted_uid
id|__kernel_uid_t
id|mounted_uid
suffix:semicolon
multiline_comment|/* Who may umount() this filesystem? */
DECL|member|uid
id|__kernel_uid_t
id|uid
suffix:semicolon
DECL|member|gid
id|__kernel_gid_t
id|gid
suffix:semicolon
DECL|member|file_mode
id|__kernel_mode_t
id|file_mode
suffix:semicolon
DECL|member|dir_mode
id|__kernel_mode_t
id|dir_mode
suffix:semicolon
)brace
suffix:semicolon
macro_line|#ifdef __KERNEL__
multiline_comment|/* &quot;vers&quot; in big-endian */
DECL|macro|SMB_MOUNT_ASCII
mdefine_line|#define SMB_MOUNT_ASCII 0x76657273
DECL|macro|SMB_MOUNT_OLDVERSION
mdefine_line|#define SMB_MOUNT_OLDVERSION&t;6
DECL|macro|SMB_MOUNT_VERSION
macro_line|#undef SMB_MOUNT_VERSION
DECL|macro|SMB_MOUNT_VERSION
mdefine_line|#define SMB_MOUNT_VERSION&t;7
multiline_comment|/* flags */
DECL|macro|SMB_MOUNT_WIN95
mdefine_line|#define SMB_MOUNT_WIN95&t;&t;0x0001&t;/* Win 95 server */
DECL|macro|SMB_MOUNT_OLDATTR
mdefine_line|#define SMB_MOUNT_OLDATTR&t;0x0002&t;/* Use core getattr (Win 95 speedup) */
DECL|macro|SMB_MOUNT_DIRATTR
mdefine_line|#define SMB_MOUNT_DIRATTR&t;0x0004&t;/* Use find_first for getattr */
DECL|macro|SMB_MOUNT_CASE
mdefine_line|#define SMB_MOUNT_CASE&t;&t;0x0008&t;/* Be case sensitive */
DECL|struct|smb_mount_data_kernel
r_struct
id|smb_mount_data_kernel
(brace
DECL|member|version
r_int
id|version
suffix:semicolon
DECL|member|mounted_uid
id|__kernel_uid_t
id|mounted_uid
suffix:semicolon
multiline_comment|/* Who may umount() this filesystem? */
DECL|member|uid
id|__kernel_uid_t
id|uid
suffix:semicolon
DECL|member|gid
id|__kernel_gid_t
id|gid
suffix:semicolon
DECL|member|file_mode
id|__kernel_mode_t
id|file_mode
suffix:semicolon
DECL|member|dir_mode
id|__kernel_mode_t
id|dir_mode
suffix:semicolon
DECL|member|flags
id|u32
id|flags
suffix:semicolon
DECL|member|codepage
r_struct
id|smb_nls_codepage
id|codepage
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
macro_line|#endif
eof
