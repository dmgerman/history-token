multiline_comment|/*&n; *  ncp_fs_i.h&n; *&n; *  Copyright (C) 1995 Volker Lendecke&n; *&n; */
macro_line|#ifndef _LINUX_NCP_FS_I
DECL|macro|_LINUX_NCP_FS_I
mdefine_line|#define _LINUX_NCP_FS_I
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * This is the ncpfs part of the inode structure. This must contain&n; * all the information we need to work with an inode after creation.&n; */
DECL|struct|ncp_inode_info
r_struct
id|ncp_inode_info
(brace
DECL|member|dirEntNum
id|__u32
id|dirEntNum
suffix:semicolon
DECL|member|DosDirNum
id|__u32
id|DosDirNum
suffix:semicolon
DECL|member|volNumber
id|__u32
id|volNumber
suffix:semicolon
DECL|member|nwattr
id|__u32
id|nwattr
suffix:semicolon
DECL|member|open_sem
r_struct
id|semaphore
id|open_sem
suffix:semicolon
DECL|member|opened
id|atomic_t
id|opened
suffix:semicolon
DECL|member|access
r_int
id|access
suffix:semicolon
DECL|member|server_file_handle
id|__u32
id|server_file_handle
suffix:semicolon
DECL|member|file_handle
id|__u8
id|file_handle
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|vfs_inode
r_struct
id|inode
id|vfs_inode
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif&t;/* __KERNEL__ */
macro_line|#endif&t;/* _LINUX_NCP_FS_I */
eof
