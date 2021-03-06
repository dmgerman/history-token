multiline_comment|/*&n; * Copyright (C) 2001 Sistina Software&n; *&n; * This file is released under the GPL.&n; *&n; * Kcopyd provides a simple interface for copying an area of one&n; * block-device to one or more other block-devices, with an asynchronous&n; * completion notification.&n; */
macro_line|#ifndef DM_KCOPYD_H
DECL|macro|DM_KCOPYD_H
mdefine_line|#define DM_KCOPYD_H
macro_line|#include &quot;dm-io.h&quot;
multiline_comment|/* FIXME: make this configurable */
DECL|macro|KCOPYD_MAX_REGIONS
mdefine_line|#define KCOPYD_MAX_REGIONS 8
DECL|macro|KCOPYD_IGNORE_ERROR
mdefine_line|#define KCOPYD_IGNORE_ERROR 1
multiline_comment|/*&n; * To use kcopyd you must first create a kcopyd client object.&n; */
r_struct
id|kcopyd_client
suffix:semicolon
r_int
id|kcopyd_client_create
c_func
(paren
r_int
r_int
id|num_pages
comma
r_struct
id|kcopyd_client
op_star
op_star
id|result
)paren
suffix:semicolon
r_void
id|kcopyd_client_destroy
c_func
(paren
r_struct
id|kcopyd_client
op_star
id|kc
)paren
suffix:semicolon
multiline_comment|/*&n; * Submit a copy job to kcopyd.  This is built on top of the&n; * previous three fns.&n; *&n; * read_err is a boolean,&n; * write_err is a bitset, with 1 bit for each destination region&n; */
DECL|typedef|kcopyd_notify_fn
r_typedef
r_void
(paren
op_star
id|kcopyd_notify_fn
)paren
(paren
r_int
id|read_err
comma
r_int
r_int
id|write_err
comma
r_void
op_star
id|context
)paren
suffix:semicolon
r_int
id|kcopyd_copy
c_func
(paren
r_struct
id|kcopyd_client
op_star
id|kc
comma
r_struct
id|io_region
op_star
id|from
comma
r_int
r_int
id|num_dests
comma
r_struct
id|io_region
op_star
id|dests
comma
r_int
r_int
id|flags
comma
id|kcopyd_notify_fn
id|fn
comma
r_void
op_star
id|context
)paren
suffix:semicolon
macro_line|#endif
eof
