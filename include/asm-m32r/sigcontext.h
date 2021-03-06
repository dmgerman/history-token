macro_line|#ifndef _ASM_M32R_SIGCONTEXT_H
DECL|macro|_ASM_M32R_SIGCONTEXT_H
mdefine_line|#define _ASM_M32R_SIGCONTEXT_H
multiline_comment|/* $Id$ */
macro_line|#include &lt;linux/config.h&gt;
DECL|struct|sigcontext
r_struct
id|sigcontext
(brace
multiline_comment|/* CPU registers */
multiline_comment|/* Saved main processor registers. */
DECL|member|sc_r4
r_int
r_int
id|sc_r4
suffix:semicolon
DECL|member|sc_r5
r_int
r_int
id|sc_r5
suffix:semicolon
DECL|member|sc_r6
r_int
r_int
id|sc_r6
suffix:semicolon
DECL|member|sc_pt_regs
r_struct
id|pt_regs
op_star
id|sc_pt_regs
suffix:semicolon
DECL|member|sc_r0
r_int
r_int
id|sc_r0
suffix:semicolon
DECL|member|sc_r1
r_int
r_int
id|sc_r1
suffix:semicolon
DECL|member|sc_r2
r_int
r_int
id|sc_r2
suffix:semicolon
DECL|member|sc_r3
r_int
r_int
id|sc_r3
suffix:semicolon
DECL|member|sc_r7
r_int
r_int
id|sc_r7
suffix:semicolon
DECL|member|sc_r8
r_int
r_int
id|sc_r8
suffix:semicolon
DECL|member|sc_r9
r_int
r_int
id|sc_r9
suffix:semicolon
DECL|member|sc_r10
r_int
r_int
id|sc_r10
suffix:semicolon
DECL|member|sc_r11
r_int
r_int
id|sc_r11
suffix:semicolon
DECL|member|sc_r12
r_int
r_int
id|sc_r12
suffix:semicolon
multiline_comment|/* Saved main processor status and miscellaneous context registers. */
macro_line|#if defined(CONFIG_ISA_M32R2) &amp;&amp; defined(CONFIG_ISA_DSP_LEVEL2)
DECL|member|sc_acc0h
r_int
r_int
id|sc_acc0h
suffix:semicolon
DECL|member|sc_acc0l
r_int
r_int
id|sc_acc0l
suffix:semicolon
DECL|member|sc_acc1h
r_int
r_int
id|sc_acc1h
suffix:semicolon
DECL|member|sc_acc1l
r_int
r_int
id|sc_acc1l
suffix:semicolon
macro_line|#elif defined(CONFIG_ISA_M32R2) || defined(CONFIG_ISA_M32R)
DECL|member|sc_acch
r_int
r_int
id|sc_acch
suffix:semicolon
DECL|member|sc_accl
r_int
r_int
id|sc_accl
suffix:semicolon
macro_line|#else
macro_line|#error unknown isa configuration
macro_line|#endif
DECL|member|sc_psw
r_int
r_int
id|sc_psw
suffix:semicolon
DECL|member|sc_bpc
r_int
r_int
id|sc_bpc
suffix:semicolon
multiline_comment|/* saved PC for TRAP syscalls */
DECL|member|sc_bbpsw
r_int
r_int
id|sc_bbpsw
suffix:semicolon
DECL|member|sc_bbpc
r_int
r_int
id|sc_bbpc
suffix:semicolon
DECL|member|sc_spu
r_int
r_int
id|sc_spu
suffix:semicolon
multiline_comment|/* saved user stack */
DECL|member|sc_fp
r_int
r_int
id|sc_fp
suffix:semicolon
DECL|member|sc_lr
r_int
r_int
id|sc_lr
suffix:semicolon
multiline_comment|/* saved PC for JL syscalls */
DECL|member|sc_spi
r_int
r_int
id|sc_spi
suffix:semicolon
multiline_comment|/* saved kernel stack */
DECL|member|oldmask
r_int
r_int
id|oldmask
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif  /* _ASM_M32R_SIGCONTEXT_H */
eof
