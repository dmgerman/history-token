macro_line|#ifdef __KERNEL__
macro_line|#ifndef _PPC_CURRENT_H
DECL|macro|_PPC_CURRENT_H
mdefine_line|#define _PPC_CURRENT_H
multiline_comment|/*&n; * We keep `current&squot; in r2 for speed.&n; */
r_register
r_struct
id|task_struct
op_star
id|current
id|asm
(paren
l_string|&quot;r2&quot;
)paren
suffix:semicolon
macro_line|#endif /* !(_PPC_CURRENT_H) */
macro_line|#endif /* __KERNEL__ */
eof
