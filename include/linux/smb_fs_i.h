multiline_comment|/*&n; *  smb_fs_i.h&n; *&n; *  Copyright (C) 1995 by Paal-Kr. Engstad and Volker Lendecke&n; *  Copyright (C) 1997 by Volker Lendecke&n; *&n; */
macro_line|#ifndef _LINUX_SMB_FS_I
DECL|macro|_LINUX_SMB_FS_I
mdefine_line|#define _LINUX_SMB_FS_I
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/types.h&gt;
multiline_comment|/*&n; * smb fs inode data (in memory only)&n; */
DECL|struct|smb_inode_info
r_struct
id|smb_inode_info
(brace
multiline_comment|/*&n;&t; * file handles are local to a connection. A file is open if&n;&t; * (open == generation).&n;&t; */
DECL|member|open
r_int
r_int
id|open
suffix:semicolon
multiline_comment|/* open generation */
DECL|member|fileid
id|__u16
id|fileid
suffix:semicolon
multiline_comment|/* What id to handle a file with? */
DECL|member|attr
id|__u16
id|attr
suffix:semicolon
multiline_comment|/* Attribute fields, DOS value */
DECL|member|access
id|__u16
id|access
suffix:semicolon
multiline_comment|/* Access mode */
DECL|member|flags
id|__u16
id|flags
suffix:semicolon
multiline_comment|/* status flags */
DECL|member|oldmtime
r_int
r_int
id|oldmtime
suffix:semicolon
multiline_comment|/* last time refreshed */
DECL|member|closed
r_int
r_int
id|closed
suffix:semicolon
multiline_comment|/* timestamp when closed */
DECL|member|openers
r_int
id|openers
suffix:semicolon
multiline_comment|/* number of fileid users */
)brace
suffix:semicolon
macro_line|#endif
macro_line|#endif
eof
