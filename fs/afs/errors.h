multiline_comment|/* errors.h: AFS abort/error codes&n; *&n; * Copyright (C) 2002 Red Hat, Inc. All Rights Reserved.&n; * Written by David Howells (dhowells@redhat.com)&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _LINUX_AFS_ERRORS_H
DECL|macro|_LINUX_AFS_ERRORS_H
mdefine_line|#define _LINUX_AFS_ERRORS_H
macro_line|#include &quot;types.h&quot;
multiline_comment|/* file server abort codes */
r_typedef
r_enum
(brace
DECL|enumerator|VSALVAGE
id|VSALVAGE
op_assign
l_int|101
comma
multiline_comment|/* volume needs salvaging */
DECL|enumerator|VNOVNODE
id|VNOVNODE
op_assign
l_int|102
comma
multiline_comment|/* no such file/dir (vnode) */
DECL|enumerator|VNOVOL
id|VNOVOL
op_assign
l_int|103
comma
multiline_comment|/* no such volume or volume unavailable */
DECL|enumerator|VVOLEXISTS
id|VVOLEXISTS
op_assign
l_int|104
comma
multiline_comment|/* volume name already exists */
DECL|enumerator|VNOSERVICE
id|VNOSERVICE
op_assign
l_int|105
comma
multiline_comment|/* volume not currently in service */
DECL|enumerator|VOFFLINE
id|VOFFLINE
op_assign
l_int|106
comma
multiline_comment|/* volume is currently offline (more info available [VVL-spec]) */
DECL|enumerator|VONLINE
id|VONLINE
op_assign
l_int|107
comma
multiline_comment|/* volume is already online */
DECL|enumerator|VDISKFULL
id|VDISKFULL
op_assign
l_int|108
comma
multiline_comment|/* disk partition is full */
DECL|enumerator|VOVERQUOTA
id|VOVERQUOTA
op_assign
l_int|109
comma
multiline_comment|/* volume&squot;s maximum quota exceeded */
DECL|enumerator|VBUSY
id|VBUSY
op_assign
l_int|110
comma
multiline_comment|/* volume is temporarily unavailable */
DECL|enumerator|VMOVED
id|VMOVED
op_assign
l_int|111
comma
multiline_comment|/* volume moved to new server - ask this FS where */
DECL|typedef|afs_rxfs_abort_t
)brace
id|afs_rxfs_abort_t
suffix:semicolon
r_extern
r_int
id|afs_abort_to_error
c_func
(paren
r_int
id|abortcode
)paren
suffix:semicolon
macro_line|#endif /* _LINUX_AFS_ERRORS_H */
eof
