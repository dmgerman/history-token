multiline_comment|/* &n; * Copyright (C) 2001 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#ifndef __SIGNAL_KERN_H__
DECL|macro|__SIGNAL_KERN_H__
mdefine_line|#define __SIGNAL_KERN_H__
macro_line|#include &quot;sysdep/ptrace.h&quot;
r_extern
r_void
id|signal_deliverer
c_func
(paren
r_int
id|sig
)paren
suffix:semicolon
r_extern
r_int
id|probe_stack
c_func
(paren
r_int
r_int
id|sp
comma
r_int
id|delta
)paren
suffix:semicolon
r_extern
r_int
id|have_signals
c_func
(paren
r_void
op_star
id|t
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
