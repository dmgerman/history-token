macro_line|#ifndef __ASM_SH_CURRENT_H
DECL|macro|__ASM_SH_CURRENT_H
mdefine_line|#define __ASM_SH_CURRENT_H
multiline_comment|/*&n; * Copyright (C) 1999 Niibe Yutaka&n; *&n; */
r_struct
id|task_struct
suffix:semicolon
DECL|function|get_current
r_static
id|__inline__
r_struct
id|task_struct
op_star
id|get_current
c_func
(paren
r_void
)paren
(brace
r_struct
id|task_struct
op_star
id|current
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;stc&t;$r7_bank, %0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|current
)paren
)paren
suffix:semicolon
r_return
id|current
suffix:semicolon
)brace
DECL|macro|current
mdefine_line|#define current get_current()
macro_line|#endif /* __ASM_SH_CURRENT_H */
eof
