multiline_comment|/* &n; * Copyright (C) 2001, 2002 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#ifndef __UML_SIGCONTEXT_H__
DECL|macro|__UML_SIGCONTEXT_H__
mdefine_line|#define __UML_SIGCONTEXT_H__
macro_line|#include &quot;sysdep/sigcontext.h&quot;
r_extern
r_int
id|sc_size
c_func
(paren
r_void
op_star
id|data
)paren
suffix:semicolon
r_extern
r_void
id|sc_to_sc
c_func
(paren
r_void
op_star
id|to_ptr
comma
r_void
op_star
id|from_ptr
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
