macro_line|#ifndef __ASM_SH_SIGCONTEXT_H
DECL|macro|__ASM_SH_SIGCONTEXT_H
mdefine_line|#define __ASM_SH_SIGCONTEXT_H
DECL|struct|sigcontext
r_struct
id|sigcontext
(brace
DECL|member|oldmask
r_int
r_int
id|oldmask
suffix:semicolon
multiline_comment|/* CPU registers */
DECL|member|sc_regs
r_int
r_int
id|sc_regs
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|sc_pc
r_int
r_int
id|sc_pc
suffix:semicolon
DECL|member|sc_pr
r_int
r_int
id|sc_pr
suffix:semicolon
DECL|member|sc_sr
r_int
r_int
id|sc_sr
suffix:semicolon
DECL|member|sc_gbr
r_int
r_int
id|sc_gbr
suffix:semicolon
DECL|member|sc_mach
r_int
r_int
id|sc_mach
suffix:semicolon
DECL|member|sc_macl
r_int
r_int
id|sc_macl
suffix:semicolon
macro_line|#if defined(CONFIG_CPU_SH4)
multiline_comment|/* FPU registers */
DECL|member|sc_fpregs
r_int
r_int
id|sc_fpregs
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|sc_xfpregs
r_int
r_int
id|sc_xfpregs
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|sc_fpscr
r_int
r_int
id|sc_fpscr
suffix:semicolon
DECL|member|sc_fpul
r_int
r_int
id|sc_fpul
suffix:semicolon
DECL|member|sc_ownedfp
r_int
r_int
id|sc_ownedfp
suffix:semicolon
macro_line|#endif
)brace
suffix:semicolon
macro_line|#endif /* __ASM_SH_SIGCONTEXT_H */
eof
