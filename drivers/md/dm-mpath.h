multiline_comment|/*&n; * Copyright (C) 2004 Red Hat, Inc. All rights reserved.&n; *&n; * This file is released under the GPL.&n; *&n; * Multipath.&n; */
macro_line|#ifndef&t;DM_MPATH_H
DECL|macro|DM_MPATH_H
mdefine_line|#define&t;DM_MPATH_H
r_struct
id|dm_dev
suffix:semicolon
DECL|struct|path
r_struct
id|path
(brace
DECL|member|dev
r_struct
id|dm_dev
op_star
id|dev
suffix:semicolon
multiline_comment|/* Read-only */
DECL|member|is_active
r_int
id|is_active
suffix:semicolon
multiline_comment|/* Read-only */
DECL|member|pscontext
r_void
op_star
id|pscontext
suffix:semicolon
multiline_comment|/* For path-selector use */
DECL|member|hwhcontext
r_void
op_star
id|hwhcontext
suffix:semicolon
multiline_comment|/* For hw-handler use */
)brace
suffix:semicolon
multiline_comment|/* Callback for hwh_pg_init_fn to use when complete */
r_void
id|dm_pg_init_complete
c_func
(paren
r_struct
id|path
op_star
id|path
comma
r_int
id|err_flags
)paren
suffix:semicolon
macro_line|#endif
eof
