multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1998, 2002 Ralf Baechle&n; * Copyright (C) 1999 Silicon Graphics, Inc.&n; */
macro_line|#ifndef _ASM_CURRENT_H
DECL|macro|_ASM_CURRENT_H
mdefine_line|#define _ASM_CURRENT_H
macro_line|#include &lt;linux/thread_info.h&gt;
r_struct
id|task_struct
suffix:semicolon
DECL|function|get_current
r_static
r_inline
r_struct
id|task_struct
op_star
id|get_current
c_func
(paren
r_void
)paren
(brace
r_return
id|current_thread_info
c_func
(paren
)paren
op_member_access_from_pointer
id|task
suffix:semicolon
)brace
DECL|macro|current
mdefine_line|#define current&t;&t;get_current()
macro_line|#endif /* _ASM_CURRENT_H */
eof
