macro_line|#ifndef _PPC64_CURRENT_H
DECL|macro|_PPC64_CURRENT_H
mdefine_line|#define _PPC64_CURRENT_H
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; *&n; * Use r13 for current since the ppc64 ABI reserves it - Anton&n; */
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
macro_line|#endif /* !(_PPC64_CURRENT_H) */
eof
