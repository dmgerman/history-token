multiline_comment|/* &n; * Copyright (C) 2002 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#ifndef __SYSCALL_USER_H
DECL|macro|__SYSCALL_USER_H
mdefine_line|#define __SYSCALL_USER_H
r_extern
r_int
id|record_syscall_start
c_func
(paren
r_int
id|syscall
)paren
suffix:semicolon
r_extern
r_void
id|record_syscall_end
c_func
(paren
r_int
id|index
comma
r_int
id|result
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
