multiline_comment|/* sigcontext.h: FRV signal context&n; *&n; * Copyright (C) 2003 Red Hat, Inc. All Rights Reserved.&n; * Written by David Howells (dhowells@redhat.com)&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _ASM_SIGCONTEXT_H
DECL|macro|_ASM_SIGCONTEXT_H
mdefine_line|#define _ASM_SIGCONTEXT_H
macro_line|#include &lt;asm/registers.h&gt;
multiline_comment|/*&n; * Signal context structure - contains all info to do with the state&n; * before the signal handler was invoked.  Note: only add new entries&n; * to the end of the structure.&n; */
DECL|struct|sigcontext
r_struct
id|sigcontext
(brace
DECL|member|sc_context
r_struct
id|user_context
id|sc_context
suffix:semicolon
DECL|member|sc_oldmask
r_int
r_int
id|sc_oldmask
suffix:semicolon
multiline_comment|/* old sigmask */
)brace
id|__attribute__
c_func
(paren
(paren
id|aligned
c_func
(paren
l_int|8
)paren
)paren
)paren
suffix:semicolon
macro_line|#endif
eof
