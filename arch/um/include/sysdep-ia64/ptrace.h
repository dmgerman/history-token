multiline_comment|/* &n; * Copyright (C) 2000 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#ifndef __SYSDEP_IA64_PTRACE_H
DECL|macro|__SYSDEP_IA64_PTRACE_H
mdefine_line|#define __SYSDEP_IA64_PTRACE_H
DECL|struct|sys_pt_regs
r_struct
id|sys_pt_regs
(brace
DECL|member|foo
r_int
id|foo
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|EMPTY_REGS
mdefine_line|#define EMPTY_REGS { 0 }
macro_line|#endif
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
