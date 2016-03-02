multiline_comment|/*&n; *   fs/cifs/cifs_fs_sb.h&n; *&n; *   Copyright (c) International Business Machines  Corp., 2002&n; *   Author(s): Steve French (sfrench@us.ibm.com)&n; *&n; *   This library is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU Lesser General Public License as published&n; *   by the Free Software Foundation; either version 2.1 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This library is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See&n; *   the GNU Lesser General Public License for more details.&n; *&n; */
macro_line|#ifndef _CIFS_FS_SB_H
DECL|macro|_CIFS_FS_SB_H
mdefine_line|#define _CIFS_FS_SB_H
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
multiline_comment|/* list of implicit mounts beneath this mount point - needed in dfs case */
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
)brace
suffix:semicolon
macro_line|#endif&t;&t;&t;&t;/* _CIFS_FS_SB_H */
eof
