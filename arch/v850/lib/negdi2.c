multiline_comment|/*&n; * arch/v850/lib/negdi2.c -- 64-bit negation&n; *&n; *  Copyright (C) 2001  NEC Corporation&n; *  Copyright (C) 2001  Miles Bader &lt;miles@gnu.org&gt;&n; *&n; * This file is subject to the terms and conditions of the GNU General&n; * Public License.  See the file COPYING in the main directory of this&n; * archive for more details.&n; *&n; * Written by Miles Bader &lt;miles@gnu.org&gt;&n; */
DECL|typedef|DItype
r_typedef
r_int
id|DItype
id|__attribute__
(paren
(paren
id|mode
(paren
id|DI
)paren
)paren
)paren
suffix:semicolon
DECL|function|__negdi2
id|DItype
id|__negdi2
(paren
id|DItype
id|x
)paren
(brace
id|__asm__
id|__volatile__
(paren
l_string|&quot;not&t;r6, r10;&quot;
l_string|&quot;add&t;1, r10;&quot;
l_string|&quot;setf&t;c, r6;&quot;
l_string|&quot;not&t;r7, r11;&quot;
l_string|&quot;add&t;r6, r11&quot;
op_scope_resolution
suffix:colon
l_string|&quot;r6&quot;
comma
l_string|&quot;r7&quot;
comma
l_string|&quot;r10&quot;
comma
l_string|&quot;r11&quot;
)paren
suffix:semicolon
)brace
eof
