multiline_comment|/* kmap.c: ioremapping handlers&n; *&n; * Copyright (C) 2003-5 Red Hat, Inc. All Rights Reserved.&n; * Written by David Howells (dhowells@redhat.com)&n; * - Derived from arch/m68k/mm/kmap.c&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/system.h&gt;
DECL|macro|DEBUG
macro_line|#undef DEBUG
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * Map some physical address range into the kernel address space.&n; */
DECL|function|__ioremap
r_void
op_star
id|__ioremap
c_func
(paren
r_int
r_int
id|physaddr
comma
r_int
r_int
id|size
comma
r_int
id|cacheflag
)paren
(brace
r_return
(paren
r_void
op_star
)paren
id|physaddr
suffix:semicolon
)brace
multiline_comment|/*&n; * Unmap a ioremap()ed region again&n; */
DECL|function|iounmap
r_void
id|iounmap
c_func
(paren
r_void
op_star
id|addr
)paren
(brace
)brace
multiline_comment|/*&n; * __iounmap unmaps nearly everything, so be careful&n; * it doesn&squot;t free currently pointer/page tables anymore but it&n; * wans&squot;t used anyway and might be added later.&n; */
DECL|function|__iounmap
r_void
id|__iounmap
c_func
(paren
r_void
op_star
id|addr
comma
r_int
r_int
id|size
)paren
(brace
)brace
multiline_comment|/*&n; * Set new cache mode for some kernel address space.&n; * The caller must push data for that range itself, if such data may already&n; * be in the cache.&n; */
DECL|function|kernel_set_cachemode
r_void
id|kernel_set_cachemode
c_func
(paren
r_void
op_star
id|addr
comma
r_int
r_int
id|size
comma
r_int
id|cmode
)paren
(brace
)brace
eof
