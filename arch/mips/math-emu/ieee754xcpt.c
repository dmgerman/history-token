multiline_comment|/*&n; * MIPS floating point support&n; * Copyright (C) 1994-2000 Algorithmics Ltd.  All rights reserved.&n; * http://www.algor.co.uk&n; *&n; * ########################################################################&n; *&n; *  This program is free software; you can distribute it and/or modify it&n; *  under the terms of the GNU General Public License (Version 2) as&n; *  published by the Free Software Foundation.&n; *&n; *  This program is distributed in the hope it will be useful, but WITHOUT&n; *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or&n; *  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License&n; *  for more details.&n; *&n; *  You should have received a copy of the GNU General Public License along&n; *  with this program; if not, write to the Free Software Foundation, Inc.,&n; *  59 Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * ########################################################################&n; */
multiline_comment|/**************************************************************************&n; *  Nov 7, 2000&n; *  Added preprocessor hacks to map to Linux kernel diagnostics. &n; *&n; *  Kevin D. Kissell, kevink@mips.com and Carsten Langgaard, carstenl@mips.com&n; *  Copyright (C) 2000 MIPS Technologies, Inc.  All rights reserved.&n; *************************************************************************/
macro_line|#include &quot;ieee754.h&quot;
multiline_comment|/*&n; * Very naff exception handler (you can plug in your own and&n; * override this).&n; */
DECL|variable|rtnames
r_static
r_const
r_char
op_star
r_const
id|rtnames
(braket
)braket
op_assign
(brace
l_string|&quot;sp&quot;
comma
l_string|&quot;dp&quot;
comma
l_string|&quot;xp&quot;
comma
l_string|&quot;si&quot;
comma
l_string|&quot;di&quot;
)brace
suffix:semicolon
DECL|function|ieee754_xcpt
r_void
id|ieee754_xcpt
c_func
(paren
r_struct
id|ieee754xctx
op_star
id|xcp
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;floating point exception in &bslash;&quot;%s&bslash;&quot;, type=%s&bslash;n&quot;
comma
id|xcp-&gt;op
comma
id|rtnames
(braket
id|xcp-&gt;rt
)braket
)paren
suffix:semicolon
)brace
eof
