macro_line|#ifndef _ASM_IA64_CURRENT_H
DECL|macro|_ASM_IA64_CURRENT_H
mdefine_line|#define _ASM_IA64_CURRENT_H
multiline_comment|/*&n; * Copyright (C) 1998-2000 Hewlett-Packard Co&n; * Copyright (C) 1998-2000 David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; */
multiline_comment|/* In kernel mode, thread pointer (r13) is used to point to the&n;   current task structure.  */
r_register
r_struct
id|task_struct
op_star
id|current
id|asm
(paren
l_string|&quot;r13&quot;
)paren
suffix:semicolon
macro_line|#endif /* _ASM_IA64_CURRENT_H */
eof
