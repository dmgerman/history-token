multiline_comment|/* cmservice.h: AFS Cache Manager Service declarations&n; *&n; * Copyright (C) 2002 Red Hat, Inc. All Rights Reserved.&n; * Written by David Howells (dhowells@redhat.com)&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _LINUX_AFS_CMSERVICE_H
DECL|macro|_LINUX_AFS_CMSERVICE_H
mdefine_line|#define _LINUX_AFS_CMSERVICE_H
macro_line|#include &lt;rxrpc/transport.h&gt;
macro_line|#include &quot;types.h&quot;
multiline_comment|/* cache manager start/stop */
r_extern
r_int
id|afscm_start
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|afscm_stop
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* cache manager server functions */
r_extern
r_int
id|SRXAFSCM_InitCallBackState
c_func
(paren
r_struct
id|afs_server
op_star
id|server
)paren
suffix:semicolon
r_extern
r_int
id|SRXAFSCM_CallBack
c_func
(paren
r_struct
id|afs_server
op_star
id|server
comma
r_int
id|count
comma
r_struct
id|afs_callback
id|callbacks
(braket
)braket
)paren
suffix:semicolon
r_extern
r_int
id|SRXAFSCM_Probe
c_func
(paren
r_struct
id|afs_server
op_star
id|server
)paren
suffix:semicolon
macro_line|#endif /* _LINUX_AFS_CMSERVICE_H */
eof
