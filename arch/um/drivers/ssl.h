multiline_comment|/* &n; * Copyright (C) 2000 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#ifndef __SSL_H__
DECL|macro|__SSL_H__
mdefine_line|#define __SSL_H__
r_extern
r_int
id|ssl_read
c_func
(paren
r_int
id|fd
comma
r_int
id|line
)paren
suffix:semicolon
r_extern
r_void
id|ssl_receive_char
c_func
(paren
r_int
id|line
comma
r_char
id|ch
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
