multiline_comment|/* $Id: sigcontext.h,v 1.14 1999/09/06 08:22:05 jj Exp $ */
macro_line|#ifndef __SPARC_SIGCONTEXT_H
DECL|macro|__SPARC_SIGCONTEXT_H
mdefine_line|#define __SPARC_SIGCONTEXT_H
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#endif
macro_line|#ifndef __ASSEMBLY__
DECL|macro|__SUNOS_MAXWIN
mdefine_line|#define __SUNOS_MAXWIN   31
multiline_comment|/* This is what SunOS does, so shall I. */
DECL|struct|sigcontext
r_struct
id|sigcontext
(brace
DECL|member|sigc_onstack
r_int
id|sigc_onstack
suffix:semicolon
multiline_comment|/* state to restore */
DECL|member|sigc_mask
r_int
id|sigc_mask
suffix:semicolon
multiline_comment|/* sigmask to restore */
DECL|member|sigc_sp
r_int
id|sigc_sp
suffix:semicolon
multiline_comment|/* stack pointer */
DECL|member|sigc_pc
r_int
id|sigc_pc
suffix:semicolon
multiline_comment|/* program counter */
DECL|member|sigc_npc
r_int
id|sigc_npc
suffix:semicolon
multiline_comment|/* next program counter */
DECL|member|sigc_psr
r_int
id|sigc_psr
suffix:semicolon
multiline_comment|/* for condition codes etc */
DECL|member|sigc_g1
r_int
id|sigc_g1
suffix:semicolon
multiline_comment|/* User uses these two registers */
DECL|member|sigc_o0
r_int
id|sigc_o0
suffix:semicolon
multiline_comment|/* within the trampoline code. */
multiline_comment|/* Now comes information regarding the users window set&n;&t; * at the time of the signal.&n;&t; */
DECL|member|sigc_oswins
r_int
id|sigc_oswins
suffix:semicolon
multiline_comment|/* outstanding windows */
multiline_comment|/* stack ptrs for each regwin buf */
DECL|member|sigc_spbuf
r_char
op_star
id|sigc_spbuf
(braket
id|__SUNOS_MAXWIN
)braket
suffix:semicolon
multiline_comment|/* Windows to restore after signal */
r_struct
(brace
DECL|member|locals
r_int
r_int
id|locals
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|ins
r_int
r_int
id|ins
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|sigc_wbuf
)brace
id|sigc_wbuf
(braket
id|__SUNOS_MAXWIN
)braket
suffix:semicolon
)brace
suffix:semicolon
r_typedef
r_struct
(brace
r_struct
(brace
DECL|member|psr
r_int
r_int
id|psr
suffix:semicolon
DECL|member|pc
r_int
r_int
id|pc
suffix:semicolon
DECL|member|npc
r_int
r_int
id|npc
suffix:semicolon
DECL|member|y
r_int
r_int
id|y
suffix:semicolon
DECL|member|u_regs
r_int
r_int
id|u_regs
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* globals and ins */
DECL|member|si_regs
)brace
id|si_regs
suffix:semicolon
DECL|member|si_mask
r_int
id|si_mask
suffix:semicolon
DECL|typedef|__siginfo_t
)brace
id|__siginfo_t
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|si_float_regs
r_int
r_int
id|si_float_regs
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|si_fsr
r_int
r_int
id|si_fsr
suffix:semicolon
DECL|member|si_fpqdepth
r_int
r_int
id|si_fpqdepth
suffix:semicolon
r_struct
(brace
DECL|member|insn_addr
r_int
r_int
op_star
id|insn_addr
suffix:semicolon
DECL|member|insn
r_int
r_int
id|insn
suffix:semicolon
DECL|member|si_fpqueue
)brace
id|si_fpqueue
(braket
l_int|16
)braket
suffix:semicolon
DECL|typedef|__siginfo_fpu_t
)brace
id|__siginfo_fpu_t
suffix:semicolon
macro_line|#endif /* !(__ASSEMBLY__) */
macro_line|#endif /* !(__SPARC_SIGCONTEXT_H) */
eof
