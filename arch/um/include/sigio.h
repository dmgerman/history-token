multiline_comment|/* &n; * Copyright (C) 2002 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#ifndef __SIGIO_H__
DECL|macro|__SIGIO_H__
mdefine_line|#define __SIGIO_H__
r_extern
r_int
id|write_sigio_irq
c_func
(paren
r_int
id|fd
)paren
suffix:semicolon
r_extern
r_int
id|register_sigio_fd
c_func
(paren
r_int
id|fd
)paren
suffix:semicolon
r_extern
r_int
id|read_sigio_fd
c_func
(paren
r_int
id|fd
)paren
suffix:semicolon
r_extern
r_int
id|add_sigio_fd
c_func
(paren
r_int
id|fd
comma
r_int
id|read
)paren
suffix:semicolon
r_extern
r_int
id|ignore_sigio_fd
c_func
(paren
r_int
id|fd
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof