multiline_comment|/* current.h: FRV current task pointer&n; *&n; * Copyright (C) 2004 Red Hat, Inc. All Rights Reserved.&n; * Written by David Howells (dhowells@redhat.com)&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _ASM_CURRENT_H
DECL|macro|_ASM_CURRENT_H
mdefine_line|#define _ASM_CURRENT_H
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/*&n; * dedicate GR29 to keeping the current task pointer&n; */
r_register
r_struct
id|task_struct
op_star
id|current
id|asm
c_func
(paren
l_string|&quot;gr29&quot;
)paren
suffix:semicolon
DECL|macro|get_current
mdefine_line|#define get_current() current
macro_line|#else
DECL|macro|CURRENT
mdefine_line|#define CURRENT gr29
macro_line|#endif
macro_line|#endif /* _ASM_CURRENT_H */
eof
