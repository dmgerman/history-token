multiline_comment|/*&n; *      Copyright (C) 1997 Claus-Justus Heine&n;&n; This program is free software; you can redistribute it and/or modify&n; it under the terms of the GNU General Public License as published by&n; the Free Software Foundation; either version 2, or (at your option)&n; any later version.&n;&n; This program is distributed in the hope that it will be useful,&n; but WITHOUT ANY WARRANTY; without even the implied warranty of&n; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; GNU General Public License for more details.&n;&n; You should have received a copy of the GNU General Public License&n; along with this program; see the file COPYING.  If not, write to&n; the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.&n;&n; *&n; * $Source: /homes/cvs/ftape-stacked/ftape/zftape/zftape_syms.c,v $&n; * $Revision: 1.3 $&n; * $Date: 1997/10/05 19:19:14 $&n; *&n; *      This file contains the symbols that the zftape frontend to &n; *      the ftape floppy tape driver exports &n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/zftape.h&gt;
macro_line|#include &quot;../zftape/zftape-init.h&quot;
macro_line|#include &quot;../zftape/zftape-read.h&quot;
macro_line|#include &quot;../zftape/zftape-buffers.h&quot;
macro_line|#include &quot;../zftape/zftape-ctl.h&quot;
multiline_comment|/* zftape-init.c */
DECL|variable|zft_cmpr_register
id|EXPORT_SYMBOL
c_func
(paren
id|zft_cmpr_register
)paren
suffix:semicolon
multiline_comment|/* zftape-read.c */
DECL|variable|zft_fetch_segment_fraction
id|EXPORT_SYMBOL
c_func
(paren
id|zft_fetch_segment_fraction
)paren
suffix:semicolon
multiline_comment|/* zftape-buffers.c */
DECL|variable|zft_vmalloc_once
id|EXPORT_SYMBOL
c_func
(paren
id|zft_vmalloc_once
)paren
suffix:semicolon
DECL|variable|zft_vmalloc_always
id|EXPORT_SYMBOL
c_func
(paren
id|zft_vmalloc_always
)paren
suffix:semicolon
DECL|variable|zft_vfree
id|EXPORT_SYMBOL
c_func
(paren
id|zft_vfree
)paren
suffix:semicolon
eof
