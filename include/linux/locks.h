macro_line|#ifndef _LINUX_LOCKS_H
DECL|macro|_LINUX_LOCKS_H
mdefine_line|#define _LINUX_LOCKS_H
macro_line|#ifndef _LINUX_MM_H
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#endif
macro_line|#ifndef _LINUX_PAGEMAP_H
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#endif
multiline_comment|/*&n; * super-block locking. Again, interrupts may only unlock&n; * a super-block (although even this isn&squot;t done right now.&n; * nfs may need it).&n; */
DECL|function|lock_super
r_static
r_inline
r_void
id|lock_super
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
id|down
c_func
(paren
op_amp
id|sb-&gt;s_lock
)paren
suffix:semicolon
)brace
DECL|function|unlock_super
r_static
r_inline
r_void
id|unlock_super
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
id|up
c_func
(paren
op_amp
id|sb-&gt;s_lock
)paren
suffix:semicolon
)brace
macro_line|#endif /* _LINUX_LOCKS_H */
eof
