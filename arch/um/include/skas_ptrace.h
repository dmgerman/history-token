multiline_comment|/* &n; * Copyright (C) 2002 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#ifndef __SKAS_PTRACE_H
DECL|macro|__SKAS_PTRACE_H
mdefine_line|#define __SKAS_PTRACE_H
DECL|struct|ptrace_faultinfo
r_struct
id|ptrace_faultinfo
(brace
DECL|member|is_write
r_int
id|is_write
suffix:semicolon
DECL|member|addr
r_int
r_int
id|addr
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ptrace_ldt
r_struct
id|ptrace_ldt
(brace
DECL|member|func
r_int
id|func
suffix:semicolon
DECL|member|ptr
r_void
op_star
id|ptr
suffix:semicolon
DECL|member|bytecount
r_int
r_int
id|bytecount
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|PTRACE_FAULTINFO
mdefine_line|#define PTRACE_FAULTINFO 52
DECL|macro|PTRACE_SIGPENDING
mdefine_line|#define PTRACE_SIGPENDING 53
DECL|macro|PTRACE_LDT
mdefine_line|#define PTRACE_LDT 54
DECL|macro|PTRACE_SWITCH_MM
mdefine_line|#define PTRACE_SWITCH_MM 55
macro_line|#endif
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
