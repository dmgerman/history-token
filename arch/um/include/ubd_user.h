multiline_comment|/* &n; * Copyright (C) 2000 Jeff Dike (jdike@karaya.com)&n; * Copyright (C) 2001 RidgeRun, Inc (glonnon@ridgerun.com)&n; * Licensed under the GPL&n; */
macro_line|#ifndef __UM_UBD_USER_H
DECL|macro|__UM_UBD_USER_H
mdefine_line|#define __UM_UBD_USER_H
r_extern
r_void
id|ignore_sigwinch_sig
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|start_io_thread
c_func
(paren
r_int
r_int
id|sp
comma
r_int
op_star
id|fds_out
)paren
suffix:semicolon
r_extern
r_int
id|io_thread
c_func
(paren
r_void
op_star
id|arg
)paren
suffix:semicolon
r_extern
r_int
id|kernel_fd
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
