multiline_comment|/* &n; * Copyright (C) 2000 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#ifndef __UMN_H
DECL|macro|__UMN_H
mdefine_line|#define __UMN_H
r_extern
r_int
id|open_umn_tty
c_func
(paren
r_int
op_star
id|slave_out
comma
r_int
op_star
id|slipno_out
)paren
suffix:semicolon
r_extern
r_void
id|close_umn_tty
c_func
(paren
r_int
id|master
comma
r_int
id|slave
)paren
suffix:semicolon
r_extern
r_int
id|umn_send_packet
c_func
(paren
r_int
id|fd
comma
r_void
op_star
id|data
comma
r_int
id|len
)paren
suffix:semicolon
r_extern
r_int
id|set_umn_addr
c_func
(paren
r_int
id|fd
comma
r_char
op_star
id|addr
comma
r_char
op_star
id|ptp_addr
)paren
suffix:semicolon
r_extern
r_void
id|slip_unesc
c_func
(paren
r_int
r_char
id|s
)paren
suffix:semicolon
r_extern
r_void
id|umn_read
c_func
(paren
r_int
id|fd
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof