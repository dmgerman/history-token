multiline_comment|/*&n; * Copyright (C) Cort Dougan 1999.&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; *&n; * Generate a note section as per the CHRP specification.&n; *&n; */
macro_line|#include &lt;stdio.h&gt;
DECL|macro|PL
mdefine_line|#define PL(x) printf(&quot;%c%c%c%c&quot;, ((x)&gt;&gt;24)&amp;0xff, ((x)&gt;&gt;16)&amp;0xff, ((x)&gt;&gt;8)&amp;0xff, (x)&amp;0xff );
DECL|function|main
r_int
id|main
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* header */
multiline_comment|/* namesz */
id|PL
c_func
(paren
id|strlen
c_func
(paren
l_string|&quot;PowerPC&quot;
)paren
op_plus
l_int|1
)paren
suffix:semicolon
multiline_comment|/* descrsz */
id|PL
c_func
(paren
l_int|6
op_star
l_int|4
)paren
suffix:semicolon
multiline_comment|/* type */
id|PL
c_func
(paren
l_int|0x1275
)paren
suffix:semicolon
multiline_comment|/* name */
id|printf
c_func
(paren
l_string|&quot;PowerPC&quot;
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;%c&quot;
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* descriptor */
multiline_comment|/* real-mode */
id|PL
c_func
(paren
l_int|0xffffffff
)paren
suffix:semicolon
multiline_comment|/* real-base */
id|PL
c_func
(paren
l_int|0x00c00000
)paren
suffix:semicolon
multiline_comment|/* real-size */
id|PL
c_func
(paren
l_int|0xffffffff
)paren
suffix:semicolon
multiline_comment|/* virt-base */
id|PL
c_func
(paren
l_int|0xffffffff
)paren
suffix:semicolon
multiline_comment|/* virt-size */
id|PL
c_func
(paren
l_int|0xffffffff
)paren
suffix:semicolon
multiline_comment|/* load-base */
id|PL
c_func
(paren
l_int|0x4000
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
