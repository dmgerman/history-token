multiline_comment|/*&n; * arch/sh64/mach-cayman/iomap.c&n; *&n; * Cayman iomap interface&n; *&n; * Copyright (C) 2004  Paul Mundt&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/cayman.h&gt;
DECL|function|ioport_map
r_void
id|__iomem
op_star
id|ioport_map
c_func
(paren
r_int
r_int
id|port
comma
r_int
r_int
id|len
)paren
(brace
r_if
c_cond
(paren
id|port
OL
l_int|0x400
)paren
r_return
(paren
r_void
id|__iomem
op_star
)paren
(paren
(paren
id|port
op_lshift
l_int|2
)paren
op_or
id|smsc_superio_virt
)paren
suffix:semicolon
r_return
(paren
r_void
id|__iomem
op_star
)paren
id|port
suffix:semicolon
)brace
eof
