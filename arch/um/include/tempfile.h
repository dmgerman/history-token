multiline_comment|/* &n; * Copyright (C) 2000, 2001, 2002 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#ifndef __TEMPFILE_H__
DECL|macro|__TEMPFILE_H__
mdefine_line|#define __TEMPFILE_H__
r_extern
r_int
id|make_tempfile
c_func
(paren
r_const
r_char
op_star
r_template
comma
r_char
op_star
op_star
id|tempname
comma
r_int
id|do_unlink
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
