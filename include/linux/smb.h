multiline_comment|/*&n; *  smb.h&n; *&n; *  Copyright (C) 1995, 1996 by Paal-Kr. Engstad and Volker Lendecke&n; *  Copyright (C) 1997 by Volker Lendecke&n; *&n; */
macro_line|#ifndef _LINUX_SMB_H
DECL|macro|_LINUX_SMB_H
mdefine_line|#define _LINUX_SMB_H
macro_line|#include &lt;linux/types.h&gt;
DECL|enum|smb_protocol
r_enum
id|smb_protocol
(brace
DECL|enumerator|SMB_PROTOCOL_NONE
id|SMB_PROTOCOL_NONE
comma
DECL|enumerator|SMB_PROTOCOL_CORE
id|SMB_PROTOCOL_CORE
comma
DECL|enumerator|SMB_PROTOCOL_COREPLUS
id|SMB_PROTOCOL_COREPLUS
comma
DECL|enumerator|SMB_PROTOCOL_LANMAN1
id|SMB_PROTOCOL_LANMAN1
comma
DECL|enumerator|SMB_PROTOCOL_LANMAN2
id|SMB_PROTOCOL_LANMAN2
comma
DECL|enumerator|SMB_PROTOCOL_NT1
id|SMB_PROTOCOL_NT1
)brace
suffix:semicolon
DECL|enum|smb_case_hndl
r_enum
id|smb_case_hndl
(brace
DECL|enumerator|SMB_CASE_DEFAULT
id|SMB_CASE_DEFAULT
comma
DECL|enumerator|SMB_CASE_LOWER
id|SMB_CASE_LOWER
comma
DECL|enumerator|SMB_CASE_UPPER
id|SMB_CASE_UPPER
)brace
suffix:semicolon
DECL|struct|smb_dskattr
r_struct
id|smb_dskattr
(brace
DECL|member|total
id|__u16
id|total
suffix:semicolon
DECL|member|allocblocks
id|__u16
id|allocblocks
suffix:semicolon
DECL|member|blocksize
id|__u16
id|blocksize
suffix:semicolon
DECL|member|free
id|__u16
id|free
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|smb_conn_opt
r_struct
id|smb_conn_opt
(brace
multiline_comment|/* The socket */
DECL|member|fd
r_int
r_int
id|fd
suffix:semicolon
DECL|member|protocol
r_enum
id|smb_protocol
id|protocol
suffix:semicolon
DECL|member|case_handling
r_enum
id|smb_case_hndl
id|case_handling
suffix:semicolon
multiline_comment|/* Connection-Options */
DECL|member|max_xmit
id|__u32
id|max_xmit
suffix:semicolon
DECL|member|server_uid
id|__u16
id|server_uid
suffix:semicolon
DECL|member|tid
id|__u16
id|tid
suffix:semicolon
multiline_comment|/* The following are LANMAN 1.0 options */
DECL|member|secmode
id|__u16
id|secmode
suffix:semicolon
DECL|member|maxmux
id|__u16
id|maxmux
suffix:semicolon
DECL|member|maxvcs
id|__u16
id|maxvcs
suffix:semicolon
DECL|member|rawmode
id|__u16
id|rawmode
suffix:semicolon
DECL|member|sesskey
id|__u32
id|sesskey
suffix:semicolon
multiline_comment|/* The following are NT LM 0.12 options */
DECL|member|maxraw
id|__u32
id|maxraw
suffix:semicolon
DECL|member|capabilities
id|__u32
id|capabilities
suffix:semicolon
DECL|member|serverzone
id|__s16
id|serverzone
suffix:semicolon
)brace
suffix:semicolon
macro_line|#ifdef __KERNEL__
DECL|macro|SMB_NLS_MAXNAMELEN
mdefine_line|#define SMB_NLS_MAXNAMELEN 20
DECL|struct|smb_nls_codepage
r_struct
id|smb_nls_codepage
(brace
DECL|member|local_name
r_char
id|local_name
(braket
id|SMB_NLS_MAXNAMELEN
)braket
suffix:semicolon
DECL|member|remote_name
r_char
id|remote_name
(braket
id|SMB_NLS_MAXNAMELEN
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|SMB_MAXNAMELEN
mdefine_line|#define SMB_MAXNAMELEN 255
DECL|macro|SMB_MAXPATHLEN
mdefine_line|#define SMB_MAXPATHLEN 1024
multiline_comment|/*&n; * Contains all relevant data on a SMB networked file.&n; */
DECL|struct|smb_fattr
r_struct
id|smb_fattr
(brace
DECL|member|attr
id|__u16
id|attr
suffix:semicolon
DECL|member|f_ino
r_int
r_int
id|f_ino
suffix:semicolon
DECL|member|f_mode
id|umode_t
id|f_mode
suffix:semicolon
DECL|member|f_nlink
id|nlink_t
id|f_nlink
suffix:semicolon
DECL|member|f_uid
id|uid_t
id|f_uid
suffix:semicolon
DECL|member|f_gid
id|gid_t
id|f_gid
suffix:semicolon
DECL|member|f_rdev
id|kdev_t
id|f_rdev
suffix:semicolon
DECL|member|f_size
id|off_t
id|f_size
suffix:semicolon
DECL|member|f_atime
id|time_t
id|f_atime
suffix:semicolon
DECL|member|f_mtime
id|time_t
id|f_mtime
suffix:semicolon
DECL|member|f_ctime
id|time_t
id|f_ctime
suffix:semicolon
DECL|member|f_blksize
r_int
r_int
id|f_blksize
suffix:semicolon
DECL|member|f_blocks
r_int
r_int
id|f_blocks
suffix:semicolon
)brace
suffix:semicolon
DECL|enum|smb_conn_state
r_enum
id|smb_conn_state
(brace
DECL|enumerator|CONN_VALID
id|CONN_VALID
comma
multiline_comment|/* everything&squot;s fine */
DECL|enumerator|CONN_INVALID
id|CONN_INVALID
comma
multiline_comment|/* Something went wrong, but did not&n;                                   try to reconnect yet. */
DECL|enumerator|CONN_RETRIED
id|CONN_RETRIED
multiline_comment|/* Tried a reconnection, but was refused */
)brace
suffix:semicolon
multiline_comment|/*&n; * The readdir cache size controls how many directory entries are cached.&n; */
DECL|macro|SMB_READDIR_CACHE_SIZE
mdefine_line|#define SMB_READDIR_CACHE_SIZE        64
DECL|macro|SMB_SUPER_MAGIC
mdefine_line|#define SMB_SUPER_MAGIC               0x517B
DECL|macro|SMB_SERVER
mdefine_line|#define SMB_SERVER(inode)    (&amp;(inode-&gt;i_sb-&gt;u.smbfs_sb))
DECL|macro|SMB_INOP
mdefine_line|#define SMB_INOP(inode)      (&amp;(inode-&gt;u.smbfs_i))
DECL|macro|SMB_HEADER_LEN
mdefine_line|#define SMB_HEADER_LEN   37     /* includes everything up to, but not&n;                                 * including smb_bcc */
DECL|macro|SMB_INITIAL_PACKET_SIZE
mdefine_line|#define SMB_INITIAL_PACKET_SIZE&t;&t;4000
DECL|macro|SMB_MAX_PACKET_SIZE
mdefine_line|#define SMB_MAX_PACKET_SIZE&t;&t;32768
multiline_comment|/* reserve this much space for trans2 parameters. Shouldn&squot;t have to be more&n;   than 10 or so, but OS/2 seems happier like this. */
DECL|macro|SMB_TRANS2_MAX_PARAM
mdefine_line|#define SMB_TRANS2_MAX_PARAM 64
macro_line|#endif
macro_line|#endif
eof
