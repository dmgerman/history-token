multiline_comment|/* mount.h: mount parameters&n; *&n; * Copyright (C) 2002 Red Hat, Inc. All Rights Reserved.&n; * Written by David Howells (dhowells@redhat.com)&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _LINUX_AFS_MOUNT_H
DECL|macro|_LINUX_AFS_MOUNT_H
mdefine_line|#define _LINUX_AFS_MOUNT_H
DECL|struct|afs_mountdata
r_struct
id|afs_mountdata
(brace
DECL|member|volume
r_const
r_char
op_star
id|volume
suffix:semicolon
multiline_comment|/* name of volume */
DECL|member|cell
r_const
r_char
op_star
id|cell
suffix:semicolon
multiline_comment|/* name of cell containing volume */
DECL|member|cache
r_const
r_char
op_star
id|cache
suffix:semicolon
multiline_comment|/* name of cache block device */
DECL|member|nservers
r_int
id|nservers
suffix:semicolon
multiline_comment|/* number of server addresses listed */
DECL|member|servers
r_uint32
id|servers
(braket
l_int|10
)braket
suffix:semicolon
multiline_comment|/* IP addresses of servers in this cell */
)brace
suffix:semicolon
macro_line|#endif /* _LINUX_AFS_MOUNT_H */
eof
