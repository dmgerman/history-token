multiline_comment|/* sections.h: linkage layout variables&n; *&n; * Copyright (C) 2004 Red Hat, Inc. All Rights Reserved.&n; * Written by David Howells (dhowells@redhat.com)&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _ASM_SECTIONS_H
DECL|macro|_ASM_SECTIONS_H
mdefine_line|#define _ASM_SECTIONS_H
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm-generic/sections.h&gt;
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * we don&squot;t want to put variables in the GP-REL section if they&squot;re not used very much - that would&n; * be waste since GP-REL addressing is limited to GP16+/-2048&n; */
DECL|macro|__nongpreldata
mdefine_line|#define __nongpreldata&t;__attribute__((section(&quot;.data&quot;)))
DECL|macro|__nongprelbss
mdefine_line|#define __nongprelbss&t;__attribute__((section(&quot;.bss&quot;)))
multiline_comment|/*&n; * linker symbols&n; */
r_extern
r_const
r_void
id|__kernel_image_start
comma
id|__kernel_image_end
comma
id|__page_offset
suffix:semicolon
r_extern
r_int
r_int
id|__nongprelbss
id|memory_start
suffix:semicolon
r_extern
r_int
r_int
id|__nongprelbss
id|memory_end
suffix:semicolon
r_extern
r_int
r_int
id|__nongprelbss
id|rom_length
suffix:semicolon
multiline_comment|/* determine if we&squot;re running from ROM */
DECL|function|is_in_rom
r_static
r_inline
r_int
id|is_in_rom
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_return
l_int|0
suffix:semicolon
multiline_comment|/* default case: not in ROM */
)brace
macro_line|#endif
macro_line|#endif
macro_line|#endif /* _ASM_SECTIONS_H */
eof
