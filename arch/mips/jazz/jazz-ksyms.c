multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1996, 1997, 1998, 2000, 2001, 2003 by Ralf Baechle&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/jazzdma.h&gt;
DECL|variable|vdma_alloc
id|EXPORT_SYMBOL
c_func
(paren
id|vdma_alloc
)paren
suffix:semicolon
DECL|variable|vdma_free
id|EXPORT_SYMBOL
c_func
(paren
id|vdma_free
)paren
suffix:semicolon
DECL|variable|vdma_log2phys
id|EXPORT_SYMBOL
c_func
(paren
id|vdma_log2phys
)paren
suffix:semicolon
eof
