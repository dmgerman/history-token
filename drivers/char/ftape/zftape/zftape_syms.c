multiline_comment|/*&n; *      Copyright (C) 1997 Claus-Justus Heine&n;&n; This program is free software; you can redistribute it and/or modify&n; it under the terms of the GNU General Public License as published by&n; the Free Software Foundation; either version 2, or (at your option)&n; any later version.&n;&n; This program is distributed in the hope that it will be useful,&n; but WITHOUT ANY WARRANTY; without even the implied warranty of&n; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; GNU General Public License for more details.&n;&n; You should have received a copy of the GNU General Public License&n; along with this program; see the file COPYING.  If not, write to&n; the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.&n;&n; *&n; * $Source: /homes/cvs/ftape-stacked/ftape/zftape/zftape_syms.c,v $&n; * $Revision: 1.3 $&n; * $Date: 1997/10/05 19:19:14 $&n; *&n; *      This file contains the symbols that the zftape frontend to &n; *      the ftape floppy tape driver exports &n; */
DECL|macro|__NO_VERSION__
mdefine_line|#define __NO_VERSION__
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/zftape.h&gt;
macro_line|#include &quot;../zftape/zftape-init.h&quot;
macro_line|#include &quot;../zftape/zftape-read.h&quot;
macro_line|#include &quot;../zftape/zftape-buffers.h&quot;
macro_line|#include &quot;../zftape/zftape-ctl.h&quot;
macro_line|#if LINUX_VERSION_CODE &gt;= KERNEL_VER(2,1,18)
DECL|macro|FT_KSYM
macro_line|# define FT_KSYM(sym) EXPORT_SYMBOL(sym);
macro_line|#else
DECL|macro|FT_KSYM
macro_line|# define FT_KSYM(sym) X(sym),
macro_line|#endif
macro_line|#if LINUX_VERSION_CODE &lt; KERNEL_VER(2,1,18)
DECL|variable|zft_symbol_table
r_struct
id|symbol_table
id|zft_symbol_table
op_assign
(brace
macro_line|#include &lt;linux/symtab_begin.h&gt;
macro_line|#endif
multiline_comment|/* zftape-init.c */
id|FT_KSYM
c_func
(paren
id|zft_cmpr_register
)paren
id|FT_KSYM
c_func
(paren
id|zft_cmpr_unregister
)paren
multiline_comment|/* zftape-read.c */
id|FT_KSYM
c_func
(paren
id|zft_fetch_segment_fraction
)paren
multiline_comment|/* zftape-buffers.c */
id|FT_KSYM
c_func
(paren
id|zft_vmalloc_once
)paren
id|FT_KSYM
c_func
(paren
id|zft_vmalloc_always
)paren
id|FT_KSYM
c_func
(paren
id|zft_vfree
)paren
macro_line|#if LINUX_VERSION_CODE &lt; KERNEL_VER(2,1,18)
macro_line|#include &lt;linux/symtab_end.h&gt;
)brace
suffix:semicolon
macro_line|#endif
eof
