multiline_comment|/* &n; * Copyright (C) 2000, 2001, 2002 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#ifndef __UM_PTRACE_I386_H
DECL|macro|__UM_PTRACE_I386_H
mdefine_line|#define __UM_PTRACE_I386_H
macro_line|#include &quot;sysdep/ptrace.h&quot;
macro_line|#include &quot;asm/ptrace-generic.h&quot;
DECL|macro|PT_REGS_EAX
mdefine_line|#define PT_REGS_EAX(r) UPT_EAX(&amp;(r)-&gt;regs)
DECL|macro|PT_REGS_EBX
mdefine_line|#define PT_REGS_EBX(r) UPT_EBX(&amp;(r)-&gt;regs)
DECL|macro|PT_REGS_ECX
mdefine_line|#define PT_REGS_ECX(r) UPT_ECX(&amp;(r)-&gt;regs)
DECL|macro|PT_REGS_EDX
mdefine_line|#define PT_REGS_EDX(r) UPT_EDX(&amp;(r)-&gt;regs)
DECL|macro|PT_REGS_ESI
mdefine_line|#define PT_REGS_ESI(r) UPT_ESI(&amp;(r)-&gt;regs)
DECL|macro|PT_REGS_EDI
mdefine_line|#define PT_REGS_EDI(r) UPT_EDI(&amp;(r)-&gt;regs)
DECL|macro|PT_REGS_EBP
mdefine_line|#define PT_REGS_EBP(r) UPT_EBP(&amp;(r)-&gt;regs)
DECL|macro|PT_REGS_CS
mdefine_line|#define PT_REGS_CS(r) UPT_CS(&amp;(r)-&gt;regs)
DECL|macro|PT_REGS_SS
mdefine_line|#define PT_REGS_SS(r) UPT_SS(&amp;(r)-&gt;regs)
DECL|macro|PT_REGS_DS
mdefine_line|#define PT_REGS_DS(r) UPT_DS(&amp;(r)-&gt;regs)
DECL|macro|PT_REGS_ES
mdefine_line|#define PT_REGS_ES(r) UPT_ES(&amp;(r)-&gt;regs)
DECL|macro|PT_REGS_FS
mdefine_line|#define PT_REGS_FS(r) UPT_FS(&amp;(r)-&gt;regs)
DECL|macro|PT_REGS_GS
mdefine_line|#define PT_REGS_GS(r) UPT_GS(&amp;(r)-&gt;regs)
DECL|macro|PT_REGS_EFLAGS
mdefine_line|#define PT_REGS_EFLAGS(r) UPT_EFLAGS(&amp;(r)-&gt;regs)
DECL|macro|PT_REGS_ORIG_SYSCALL
mdefine_line|#define PT_REGS_ORIG_SYSCALL(r) PT_REGS_EAX(r)
DECL|macro|PT_REGS_SYSCALL_RET
mdefine_line|#define PT_REGS_SYSCALL_RET(r) PT_REGS_EAX(r)
DECL|macro|PT_FIX_EXEC_STACK
mdefine_line|#define PT_FIX_EXEC_STACK(sp) do ; while(0)
DECL|macro|user_mode
mdefine_line|#define user_mode(r) UPT_IS_USER(&amp;(r)-&gt;regs)
macro_line|#endif
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
