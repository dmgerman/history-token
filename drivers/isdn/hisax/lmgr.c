multiline_comment|/* $Id: lmgr.c,v 1.7.6.2 2001/09/23 22:24:50 kai Exp $&n; *&n; * Layermanagement module&n; *&n; * Author       Karsten Keil&n; * Copyright    by Karsten Keil      &lt;keil@isdn4linux.de&gt;&n; * &n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; *&n; */
DECL|macro|__NO_VERSION__
mdefine_line|#define __NO_VERSION__
macro_line|#include &quot;hisax.h&quot;
r_static
r_void
DECL|function|error_handling_dchan
id|error_handling_dchan
c_func
(paren
r_struct
id|PStack
op_star
id|st
comma
r_int
id|Error
)paren
(brace
r_switch
c_cond
(paren
id|Error
)paren
(brace
r_case
l_char|&squot;C&squot;
suffix:colon
r_case
l_char|&squot;D&squot;
suffix:colon
r_case
l_char|&squot;G&squot;
suffix:colon
r_case
l_char|&squot;H&squot;
suffix:colon
id|st-&gt;l2
dot
id|l2tei
c_func
(paren
id|st
comma
id|MDL_ERROR
op_or
id|REQUEST
comma
l_int|NULL
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_static
r_void
DECL|function|hisax_manager
id|hisax_manager
c_func
(paren
r_struct
id|PStack
op_star
id|st
comma
r_int
id|pr
comma
r_void
op_star
id|arg
)paren
(brace
r_int
id|Code
suffix:semicolon
r_switch
c_cond
(paren
id|pr
)paren
(brace
r_case
(paren
id|MDL_ERROR
op_or
id|INDICATION
)paren
suffix:colon
id|Code
op_assign
(paren
r_int
)paren
id|arg
suffix:semicolon
id|HiSax_putstatus
c_func
(paren
id|st-&gt;l1.hardware
comma
l_string|&quot;manager: MDL_ERROR&quot;
comma
l_string|&quot; %c %s&quot;
comma
(paren
r_char
)paren
id|Code
comma
id|test_bit
c_func
(paren
id|FLG_LAPD
comma
op_amp
id|st-&gt;l2.flag
)paren
ques
c_cond
l_string|&quot;D-channel&quot;
suffix:colon
l_string|&quot;B-channel&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|FLG_LAPD
comma
op_amp
id|st-&gt;l2.flag
)paren
)paren
id|error_handling_dchan
c_func
(paren
id|st
comma
id|Code
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_void
DECL|function|setstack_manager
id|setstack_manager
c_func
(paren
r_struct
id|PStack
op_star
id|st
)paren
(brace
id|st-&gt;ma.layer
op_assign
id|hisax_manager
suffix:semicolon
)brace
eof
