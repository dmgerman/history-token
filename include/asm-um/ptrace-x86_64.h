multiline_comment|/*&n; * Copyright 2003 PathScale, Inc.&n; *&n; * Licensed under the GPL&n; */
macro_line|#ifndef __UM_PTRACE_X86_64_H
DECL|macro|__UM_PTRACE_X86_64_H
mdefine_line|#define __UM_PTRACE_X86_64_H
macro_line|#include &quot;linux/compiler.h&quot;
DECL|macro|signal_fault
mdefine_line|#define signal_fault signal_fault_x86_64
DECL|macro|__FRAME_OFFSETS
mdefine_line|#define __FRAME_OFFSETS /* Needed to get the R* macros */
macro_line|#include &quot;asm/ptrace-generic.h&quot;
DECL|macro|signal_fault
macro_line|#undef signal_fault
r_void
id|signal_fault
c_func
(paren
r_struct
id|pt_regs_subarch
op_star
id|regs
comma
r_void
op_star
id|frame
comma
r_char
op_star
id|where
)paren
suffix:semicolon
DECL|macro|FS_BASE
mdefine_line|#define FS_BASE (21 * sizeof(unsigned long))
DECL|macro|GS_BASE
mdefine_line|#define GS_BASE (22 * sizeof(unsigned long))
DECL|macro|DS
mdefine_line|#define DS (23 * sizeof(unsigned long))
DECL|macro|ES
mdefine_line|#define ES (24 * sizeof(unsigned long))
DECL|macro|FS
mdefine_line|#define FS (25 * sizeof(unsigned long))
DECL|macro|GS
mdefine_line|#define GS (26 * sizeof(unsigned long))
DECL|macro|PT_REGS_RBX
mdefine_line|#define PT_REGS_RBX(r) UPT_RBX(&amp;(r)-&gt;regs)
DECL|macro|PT_REGS_RCX
mdefine_line|#define PT_REGS_RCX(r) UPT_RCX(&amp;(r)-&gt;regs)
DECL|macro|PT_REGS_RDX
mdefine_line|#define PT_REGS_RDX(r) UPT_RDX(&amp;(r)-&gt;regs)
DECL|macro|PT_REGS_RSI
mdefine_line|#define PT_REGS_RSI(r) UPT_RSI(&amp;(r)-&gt;regs)
DECL|macro|PT_REGS_RDI
mdefine_line|#define PT_REGS_RDI(r) UPT_RDI(&amp;(r)-&gt;regs)
DECL|macro|PT_REGS_RBP
mdefine_line|#define PT_REGS_RBP(r) UPT_RBP(&amp;(r)-&gt;regs)
DECL|macro|PT_REGS_RAX
mdefine_line|#define PT_REGS_RAX(r) UPT_RAX(&amp;(r)-&gt;regs)
DECL|macro|PT_REGS_R8
mdefine_line|#define PT_REGS_R8(r) UPT_R8(&amp;(r)-&gt;regs)
DECL|macro|PT_REGS_R9
mdefine_line|#define PT_REGS_R9(r) UPT_R9(&amp;(r)-&gt;regs)
DECL|macro|PT_REGS_R10
mdefine_line|#define PT_REGS_R10(r) UPT_R10(&amp;(r)-&gt;regs)
DECL|macro|PT_REGS_R11
mdefine_line|#define PT_REGS_R11(r) UPT_R11(&amp;(r)-&gt;regs)
DECL|macro|PT_REGS_R12
mdefine_line|#define PT_REGS_R12(r) UPT_R12(&amp;(r)-&gt;regs)
DECL|macro|PT_REGS_R13
mdefine_line|#define PT_REGS_R13(r) UPT_R13(&amp;(r)-&gt;regs)
DECL|macro|PT_REGS_R14
mdefine_line|#define PT_REGS_R14(r) UPT_R14(&amp;(r)-&gt;regs)
DECL|macro|PT_REGS_R15
mdefine_line|#define PT_REGS_R15(r) UPT_R15(&amp;(r)-&gt;regs)
DECL|macro|PT_REGS_FS
mdefine_line|#define PT_REGS_FS(r) UPT_FS(&amp;(r)-&gt;regs)
DECL|macro|PT_REGS_GS
mdefine_line|#define PT_REGS_GS(r) UPT_GS(&amp;(r)-&gt;regs)
DECL|macro|PT_REGS_DS
mdefine_line|#define PT_REGS_DS(r) UPT_DS(&amp;(r)-&gt;regs)
DECL|macro|PT_REGS_ES
mdefine_line|#define PT_REGS_ES(r) UPT_ES(&amp;(r)-&gt;regs)
DECL|macro|PT_REGS_SS
mdefine_line|#define PT_REGS_SS(r) UPT_SS(&amp;(r)-&gt;regs)
DECL|macro|PT_REGS_CS
mdefine_line|#define PT_REGS_CS(r) UPT_CS(&amp;(r)-&gt;regs)
DECL|macro|PT_REGS_ORIG_RAX
mdefine_line|#define PT_REGS_ORIG_RAX(r) UPT_ORIG_RAX(&amp;(r)-&gt;regs)
DECL|macro|PT_REGS_RIP
mdefine_line|#define PT_REGS_RIP(r) UPT_IP(&amp;(r)-&gt;regs)
DECL|macro|PT_REGS_RSP
mdefine_line|#define PT_REGS_RSP(r) UPT_SP(&amp;(r)-&gt;regs)
DECL|macro|PT_REGS_EFLAGS
mdefine_line|#define PT_REGS_EFLAGS(r) UPT_EFLAGS(&amp;(r)-&gt;regs)
multiline_comment|/* XXX */
DECL|macro|user_mode
mdefine_line|#define user_mode(r) UPT_IS_USER(&amp;(r)-&gt;regs)
DECL|macro|PT_REGS_ORIG_SYSCALL
mdefine_line|#define PT_REGS_ORIG_SYSCALL(r) PT_REGS_RAX(r)
DECL|macro|PT_REGS_SYSCALL_RET
mdefine_line|#define PT_REGS_SYSCALL_RET(r) PT_REGS_RAX(r)
DECL|macro|PT_FIX_EXEC_STACK
mdefine_line|#define PT_FIX_EXEC_STACK(sp) do ; while(0)
DECL|macro|profile_pc
mdefine_line|#define profile_pc(regs) PT_REGS_IP(regs)
macro_line|#endif
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
