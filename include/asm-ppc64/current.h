macro_line|#ifndef _PPC64_CURRENT_H
DECL|macro|_PPC64_CURRENT_H
mdefine_line|#define _PPC64_CURRENT_H
macro_line|#include &lt;asm/paca.h&gt;
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;asm/thread_info.h&gt;
DECL|macro|get_current
mdefine_line|#define get_current()   (get_paca()-&gt;xCurrent)
DECL|macro|current
mdefine_line|#define current         get_current()
macro_line|#endif /* !(_PPC64_CURRENT_H) */
eof
