multiline_comment|/*&n; * Copyright (C) 2004 PathScale, Inc&n; * Licensed under the GPL&n; */
macro_line|#ifndef __REGISTERS_H
DECL|macro|__REGISTERS_H
mdefine_line|#define __REGISTERS_H
macro_line|#include &quot;sysdep/ptrace.h&quot;
r_extern
r_void
id|init_thread_registers
c_func
(paren
r_union
id|uml_pt_regs
op_star
id|to
)paren
suffix:semicolon
r_extern
r_void
id|save_registers
c_func
(paren
r_int
id|pid
comma
r_union
id|uml_pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_extern
r_void
id|restore_registers
c_func
(paren
r_int
id|pid
comma
r_union
id|uml_pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_extern
r_void
id|init_registers
c_func
(paren
r_int
id|pid
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
