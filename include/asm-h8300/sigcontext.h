macro_line|#ifndef _ASM_H8300_SIGCONTEXT_H
DECL|macro|_ASM_H8300_SIGCONTEXT_H
mdefine_line|#define _ASM_H8300_SIGCONTEXT_H
DECL|struct|sigcontext
r_struct
id|sigcontext
(brace
DECL|member|sc_mask
r_int
r_int
id|sc_mask
suffix:semicolon
multiline_comment|/* old sigmask */
DECL|member|sc_usp
r_int
r_int
id|sc_usp
suffix:semicolon
multiline_comment|/* old user stack pointer */
DECL|member|sc_er0
r_int
r_int
id|sc_er0
suffix:semicolon
DECL|member|sc_er1
r_int
r_int
id|sc_er1
suffix:semicolon
DECL|member|sc_er2
r_int
r_int
id|sc_er2
suffix:semicolon
DECL|member|sc_er3
r_int
r_int
id|sc_er3
suffix:semicolon
DECL|member|sc_ccr
r_int
r_int
id|sc_ccr
suffix:semicolon
DECL|member|sc_pc
r_int
r_int
id|sc_pc
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
eof
