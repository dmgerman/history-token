multiline_comment|/*&n; * Copyright (C) 1996 Paul Mackerras.&n; *&n; *      This program is free software; you can redistribute it and/or&n; *      modify it under the terms of the GNU General Public License&n; *      as published by the Free Software Foundation; either version&n; *      2 of the License, or (at your option) any later version.&n; *&n; * NB this file must be compiled with -O2.&n; */
r_int
DECL|function|xmon_setjmp
id|xmon_setjmp
c_func
(paren
r_int
op_star
id|buf
)paren
multiline_comment|/* NOTE: assert(sizeof(buf) &gt; 184) */
(brace
multiline_comment|/* XXX should save fp regs as well */
id|asm
r_volatile
(paren
l_string|&quot;mflr 0; std 0,0(%0)&bslash;n&bslash;&n;&t; std&t;1,8(%0)&bslash;n&bslash;&n;&t; std&t;2,16(%0)&bslash;n&bslash;&n;&t; mfcr 0; std 0,24(%0)&bslash;n&bslash;&n;&t; std&t;13,32(%0)&bslash;n&bslash;&n;&t; std&t;14,40(%0)&bslash;n&bslash;&n;&t; std&t;15,48(%0)&bslash;n&bslash;&n;&t; std&t;16,56(%0)&bslash;n&bslash;&n;&t; std&t;17,64(%0)&bslash;n&bslash;&n;&t; std&t;18,72(%0)&bslash;n&bslash;&n;&t; std&t;19,80(%0)&bslash;n&bslash;&n;&t; std&t;20,88(%0)&bslash;n&bslash;&n;&t; std&t;21,96(%0)&bslash;n&bslash;&n;&t; std&t;22,104(%0)&bslash;n&bslash;&n;&t; std&t;23,112(%0)&bslash;n&bslash;&n;&t; std&t;24,120(%0)&bslash;n&bslash;&n;&t; std&t;25,128(%0)&bslash;n&bslash;&n;&t; std&t;26,136(%0)&bslash;n&bslash;&n;&t; std&t;27,144(%0)&bslash;n&bslash;&n;&t; std&t;28,152(%0)&bslash;n&bslash;&n;&t; std&t;29,160(%0)&bslash;n&bslash;&n;&t; std&t;30,168(%0)&bslash;n&bslash;&n;&t; std&t;31,176(%0)&bslash;n&bslash;&n;&t; &quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|buf
)paren
)paren
suffix:semicolon
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
r_volatile
(paren
l_string|&quot;ld&t;13,32(%0)&bslash;n&bslash;&n;&t; ld&t;14,40(%0)&bslash;n&bslash;&n;&t; ld&t;15,48(%0)&bslash;n&bslash;&n;&t; ld&t;16,56(%0)&bslash;n&bslash;&n;&t; ld&t;17,64(%0)&bslash;n&bslash;&n;&t; ld&t;18,72(%0)&bslash;n&bslash;&n;&t; ld&t;19,80(%0)&bslash;n&bslash;&n;&t; ld&t;20,88(%0)&bslash;n&bslash;&n;&t; ld&t;21,96(%0)&bslash;n&bslash;&n;&t; ld&t;22,104(%0)&bslash;n&bslash;&n;&t; ld&t;23,112(%0)&bslash;n&bslash;&n;&t; ld&t;24,120(%0)&bslash;n&bslash;&n;&t; ld&t;25,128(%0)&bslash;n&bslash;&n;&t; ld&t;26,136(%0)&bslash;n&bslash;&n;&t; ld&t;27,144(%0)&bslash;n&bslash;&n;&t; ld&t;28,152(%0)&bslash;n&bslash;&n;&t; ld&t;29,160(%0)&bslash;n&bslash;&n;&t; ld&t;30,168(%0)&bslash;n&bslash;&n;&t; ld&t;31,176(%0)&bslash;n&bslash;&n;&t; ld&t;0,24(%0)&bslash;n&bslash;&n;&t; mtcrf&t;0x38,0&bslash;n&bslash;&n;&t; ld&t;0,0(%0)&bslash;n&bslash;&n;&t; ld&t;1,8(%0)&bslash;n&bslash;&n;&t; ld&t;2,16(%0)&bslash;n&bslash;&n;&t; mtlr&t;0&bslash;n&bslash;&n;&t; mr&t;3,%1&bslash;n&bslash;&n;&t; &quot;
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
