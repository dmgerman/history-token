multiline_comment|/*&n; * BK Id: SCCS/s.setjmp.c 1.5 05/17/01 18:14:23 cort&n; */
multiline_comment|/*&n; * Copyright (C) 1996 Paul Mackerras.&n; *&n; * NB this file must be compiled with -O2.&n; */
r_int
DECL|function|xmon_setjmp
id|xmon_setjmp
c_func
(paren
r_int
op_star
id|buf
)paren
(brace
id|asm
(paren
l_string|&quot;mflr 0; stw 0,0(%0);&quot;
l_string|&quot;stw 1,4(%0); stw 2,8(%0);&quot;
l_string|&quot;mfcr 0; stw 0,12(%0);&quot;
l_string|&quot;stmw 13,16(%0)&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|buf
)paren
)paren
suffix:semicolon
multiline_comment|/* XXX should save fp regs as well */
r_return
l_int|0
suffix:semicolon
)brace
r_void
DECL|function|xmon_longjmp
id|xmon_longjmp
c_func
(paren
r_int
op_star
id|buf
comma
r_int
id|val
)paren
(brace
r_if
c_cond
(paren
id|val
op_eq
l_int|0
)paren
id|val
op_assign
l_int|1
suffix:semicolon
id|asm
(paren
l_string|&quot;lmw 13,16(%0);&quot;
l_string|&quot;lwz 0,12(%0); mtcrf 0x38,0;&quot;
l_string|&quot;lwz 0,0(%0); lwz 1,4(%0); lwz 2,8(%0);&quot;
l_string|&quot;mtlr 0; mr 3,%1&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|buf
)paren
comma
l_string|&quot;r&quot;
(paren
id|val
)paren
)paren
suffix:semicolon
)brace
eof
