multiline_comment|/* $Id: sigcontext.h,v 1.12 1999/09/06 08:22:09 jj Exp $ */
macro_line|#ifndef __SPARC64_SIGCONTEXT_H
DECL|macro|__SPARC64_SIGCONTEXT_H
mdefine_line|#define __SPARC64_SIGCONTEXT_H
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#endif
macro_line|#ifndef __ASSEMBLY__
macro_line|#ifdef __KERNEL__
DECL|macro|__SUNOS_MAXWIN
mdefine_line|#define __SUNOS_MAXWIN   31
multiline_comment|/* This is what SunOS does, so shall I unless we use new 32bit signals or rt signals. */
DECL|struct|sigcontext32
r_struct
id|sigcontext32
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
r_int
id|sigc_spbuf
(braket
id|__SUNOS_MAXWIN
)braket
suffix:semicolon
multiline_comment|/* Windows to restore after signal */
DECL|member|sigc_wbuf
r_struct
id|reg_window32
id|sigc_wbuf
(braket
id|__SUNOS_MAXWIN
)braket
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
macro_line|#ifdef __KERNEL__
multiline_comment|/* This is what we use for 32bit new non-rt signals. */
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
DECL|typedef|__siginfo32_t
)brace
id|__siginfo32_t
suffix:semicolon
macro_line|#endif
r_typedef
r_struct
(brace
DECL|member|si_float_regs
r_int
r_int
id|si_float_regs
(braket
l_int|64
)braket
suffix:semicolon
DECL|member|si_fsr
r_int
r_int
id|si_fsr
suffix:semicolon
DECL|member|si_gsr
r_int
r_int
id|si_gsr
suffix:semicolon
DECL|member|si_fprs
r_int
r_int
id|si_fprs
suffix:semicolon
DECL|typedef|__siginfo_fpu_t
)brace
id|__siginfo_fpu_t
suffix:semicolon
multiline_comment|/* This is what SunOS doesn&squot;t, so we have to write this alone&n;   and do it properly. */
DECL|struct|sigcontext
r_struct
id|sigcontext
(brace
multiline_comment|/* The size of this array has to match SI_MAX_SIZE from siginfo.h */
DECL|member|sigc_info
r_char
id|sigc_info
(braket
l_int|128
)braket
suffix:semicolon
r_struct
(brace
DECL|member|u_regs
r_int
r_int
id|u_regs
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* globals and ins */
DECL|member|tstate
r_int
r_int
id|tstate
suffix:semicolon
DECL|member|tpc
r_int
r_int
id|tpc
suffix:semicolon
DECL|member|tnpc
r_int
r_int
id|tnpc
suffix:semicolon
DECL|member|y
r_int
r_int
id|y
suffix:semicolon
DECL|member|fprs
r_int
r_int
id|fprs
suffix:semicolon
DECL|member|sigc_regs
)brace
id|sigc_regs
suffix:semicolon
DECL|member|sigc_fpu_save
id|__siginfo_fpu_t
op_star
id|sigc_fpu_save
suffix:semicolon
r_struct
(brace
DECL|member|ss_sp
r_void
op_star
id|ss_sp
suffix:semicolon
DECL|member|ss_flags
r_int
id|ss_flags
suffix:semicolon
DECL|member|ss_size
r_int
r_int
id|ss_size
suffix:semicolon
DECL|member|sigc_stack
)brace
id|sigc_stack
suffix:semicolon
DECL|member|sigc_mask
r_int
r_int
id|sigc_mask
suffix:semicolon
)brace
suffix:semicolon
macro_line|#ifdef __KERNEL__
multiline_comment|/* This magic should be in g_upper[0] for all upper parts&n;   to be valid.  */
DECL|macro|SIGINFO_EXTRA_V8PLUS_MAGIC
mdefine_line|#define SIGINFO_EXTRA_V8PLUS_MAGIC&t;0x130e269
r_typedef
r_struct
(brace
DECL|member|g_upper
r_int
r_int
id|g_upper
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|o_upper
r_int
r_int
id|o_upper
(braket
l_int|8
)braket
suffix:semicolon
DECL|typedef|siginfo_extra_v8plus_t
)brace
id|siginfo_extra_v8plus_t
suffix:semicolon
macro_line|#endif
macro_line|#endif /* !(__ASSEMBLY__) */
macro_line|#endif /* !(__SPARC64_SIGCONTEXT_H) */
eof
