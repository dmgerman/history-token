multiline_comment|/* &n; * Copyright (C) 2000, 2001, 2002 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#ifndef __PROCESS_H__
DECL|macro|__PROCESS_H__
mdefine_line|#define __PROCESS_H__
macro_line|#include &lt;signal.h&gt;
r_extern
r_void
id|sig_handler
c_func
(paren
r_int
id|sig
comma
r_struct
id|sigcontext
id|sc
)paren
suffix:semicolon
r_extern
r_void
id|alarm_handler
c_func
(paren
r_int
id|sig
comma
r_struct
id|sigcontext
id|sc
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
