multiline_comment|/*&n; *  linux/include/asm-arm/bugs.h&n; *&n; *  Copyright (C) 1995-2003 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#ifndef __ASM_BUGS_H
DECL|macro|__ASM_BUGS_H
mdefine_line|#define __ASM_BUGS_H
r_extern
r_void
id|check_writebuffer_bugs
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|check_bugs
mdefine_line|#define check_bugs() check_writebuffer_bugs()
macro_line|#endif
eof
