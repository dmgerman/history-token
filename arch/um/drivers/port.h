multiline_comment|/* &n; * Copyright (C) 2001 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#ifndef __PORT_H__
DECL|macro|__PORT_H__
mdefine_line|#define __PORT_H__
r_extern
r_void
op_star
id|port_data
c_func
(paren
r_int
id|port
)paren
suffix:semicolon
r_extern
r_int
id|port_wait
c_func
(paren
r_void
op_star
id|data
)paren
suffix:semicolon
r_extern
r_void
id|port_kern_close
c_func
(paren
r_void
op_star
id|d
)paren
suffix:semicolon
r_extern
r_int
id|port_connection
c_func
(paren
r_int
id|fd
comma
r_int
op_star
id|socket_out
comma
r_int
op_star
id|pid_out
)paren
suffix:semicolon
r_extern
r_int
id|port_listen_fd
c_func
(paren
r_int
id|port
)paren
suffix:semicolon
r_extern
r_void
id|port_read
c_func
(paren
r_int
id|fd
comma
r_void
op_star
id|data
)paren
suffix:semicolon
r_extern
r_void
id|port_kern_free
c_func
(paren
r_void
op_star
id|d
)paren
suffix:semicolon
r_extern
r_int
id|port_rcv_fd
c_func
(paren
r_int
id|fd
)paren
suffix:semicolon
r_extern
r_void
id|port_remove_dev
c_func
(paren
r_void
op_star
id|d
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof