multiline_comment|/* setup.h: setup stuff&n; *&n; * Copyright (C) 2004 Red Hat, Inc. All Rights Reserved.&n; * Written by David Howells (dhowells@redhat.com)&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _ASM_SETUP_H
DECL|macro|_ASM_SETUP_H
mdefine_line|#define _ASM_SETUP_H
macro_line|#include &lt;linux/init.h&gt;
macro_line|#ifndef __ASSEMBLY__
macro_line|#ifdef CONFIG_MMU
r_extern
r_int
r_int
id|__initdata
id|num_mappedpages
suffix:semicolon
macro_line|#endif
macro_line|#endif /* !__ASSEMBLY__ */
macro_line|#endif /* _ASM_SETUP_H */
eof
