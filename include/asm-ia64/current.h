macro_line|#ifndef _ASM_IA64_CURRENT_H
DECL|macro|_ASM_IA64_CURRENT_H
mdefine_line|#define _ASM_IA64_CURRENT_H
multiline_comment|/*&n; * Copyright (C) 1998-2000 Hewlett-Packard Co&n; *&t;David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; */
macro_line|#include &lt;asm/intrinsics.h&gt;
multiline_comment|/*&n; * In kernel mode, thread pointer (r13) is used to point to the current task&n; * structure.&n; */
DECL|macro|current
mdefine_line|#define current&t;((struct task_struct *) ia64_getreg(_IA64_REG_TP))
macro_line|#endif /* _ASM_IA64_CURRENT_H */
eof
