multiline_comment|/* linux/arch/cris/entryoffsets.c&n; *&n; * Copyright (C) 2001 Axis Communications AB&n; *&n; * Generate structure offsets for use in entry.S.  No extra processing&n; * needed more than compiling this file to assembly code.  Horrendous&n; * assembly code will be generated, so don&squot;t look at that.&n; *&n; * Authors:&t;Hans-Peter Nilsson (hp@axis.com)&n; */
multiline_comment|/* There can be string constants fallout from inline functions, so we&squot;d&n;   better make sure we don&squot;t assemble anything emitted from inclusions.  */
id|__asm__
(paren
l_string|&quot;.if 0&quot;
)paren
suffix:semicolon
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
multiline_comment|/* Exclude everything except the assembly by wrapping it in &quot;.if 0&quot;.  */
DECL|macro|VAL
macro_line|#undef VAL
DECL|macro|VAL
mdefine_line|#define VAL(NAME, VALUE)&t;&t;&t;&bslash;&n;void NAME ## _fun (void)&t;&t;&t;&bslash;&n; {&t;&t;&t;&t;&t;&t;&bslash;&n;  __asm__ (&quot;.endif &bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;   #NAME &quot; = %0 &bslash;n&quot;&t;&t;&t;&bslash;&n;&t;   &quot;.if 0&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;   : : &quot;i&quot; (VALUE));&t;&t;&t;&bslash;&n; }
DECL|macro|OF
macro_line|#undef OF
DECL|macro|OF
mdefine_line|#define OF(NAME, TYPE, MEMBER)&t;&t;&t;&bslash;&n;  VAL (NAME, offsetof (TYPE, MEMBER))
multiline_comment|/* task_struct offsets.  */
macro_line|#error OF (LTASK_SIGPENDING, struct task_struct, sigpending)
macro_line|#error OF (LTASK_NEEDRESCHED, struct task_struct, need_resched)
macro_line|#error OF (LTASK_PTRACE, struct task_struct, ptrace)
id|OF
(paren
id|LTASK_PID
comma
r_struct
id|task_struct
comma
id|pid
)paren
multiline_comment|/* pt_regs offsets.  */
id|OF
(paren
id|LORIG_R10
comma
r_struct
id|pt_regs
comma
id|orig_r10
)paren
id|OF
(paren
id|LR13
comma
r_struct
id|pt_regs
comma
id|r13
)paren
id|OF
(paren
id|LR12
comma
r_struct
id|pt_regs
comma
id|r12
)paren
id|OF
(paren
id|LR11
comma
r_struct
id|pt_regs
comma
id|r11
)paren
id|OF
(paren
id|LR10
comma
r_struct
id|pt_regs
comma
id|r10
)paren
id|OF
(paren
id|LR9
comma
r_struct
id|pt_regs
comma
id|r9
)paren
id|OF
(paren
id|LMOF
comma
r_struct
id|pt_regs
comma
id|mof
)paren
id|OF
(paren
id|LDCCR
comma
r_struct
id|pt_regs
comma
id|dccr
)paren
id|OF
(paren
id|LSRP
comma
r_struct
id|pt_regs
comma
id|srp
)paren
id|OF
(paren
id|LIRP
comma
r_struct
id|pt_regs
comma
id|irp
)paren
multiline_comment|/* thread_struct offsets.  */
id|OF
(paren
id|LTHREAD_KSP
comma
r_struct
id|thread_struct
comma
id|ksp
)paren
id|OF
(paren
id|LTHREAD_USP
comma
r_struct
id|thread_struct
comma
id|usp
)paren
id|OF
(paren
id|LTHREAD_DCCR
comma
r_struct
id|thread_struct
comma
id|dccr
)paren
multiline_comment|/* linux/sched.h values - doesn&squot;t have an #ifdef __ASSEMBLY__ for these.  */
id|VAL
(paren
id|LCLONE_VM
comma
id|CLONE_VM
)paren
id|__asm__
(paren
l_string|&quot;.endif&quot;
)paren
suffix:semicolon
eof
