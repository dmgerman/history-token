multiline_comment|/* &n; * Copyright (C) 2002 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#ifndef __FRAME_KERN_H_
DECL|macro|__FRAME_KERN_H_
mdefine_line|#define __FRAME_KERN_H_
macro_line|#include &quot;frame.h&quot;
macro_line|#include &quot;sysdep/frame_kern.h&quot;
r_extern
r_int
id|setup_signal_stack_sc
c_func
(paren
r_int
r_int
id|stack_top
comma
r_int
id|sig
comma
r_struct
id|k_sigaction
op_star
id|ka
comma
r_struct
id|pt_regs
op_star
id|regs
comma
id|sigset_t
op_star
id|mask
)paren
suffix:semicolon
r_extern
r_int
id|setup_signal_stack_si
c_func
(paren
r_int
r_int
id|stack_top
comma
r_int
id|sig
comma
r_struct
id|k_sigaction
op_star
id|ka
comma
r_struct
id|pt_regs
op_star
id|regs
comma
id|siginfo_t
op_star
id|info
comma
id|sigset_t
op_star
id|mask
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
