multiline_comment|/* &n; * Copyright (C) 2000, 2001, 2002 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#include &lt;stddef.h&gt;
macro_line|#include &lt;string.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/sigcontext.h&gt;
macro_line|#include &quot;sysdep/ptrace.h&quot;
macro_line|#include &quot;kern_util.h&quot;
DECL|function|sc_to_sc
r_void
id|sc_to_sc
c_func
(paren
r_void
op_star
id|to_ptr
comma
r_void
op_star
id|from_ptr
)paren
(brace
r_struct
id|sigcontext
op_star
id|to
op_assign
id|to_ptr
comma
op_star
id|from
op_assign
id|from_ptr
suffix:semicolon
id|memcpy
c_func
(paren
id|to
comma
id|from
comma
r_sizeof
(paren
op_star
id|to
)paren
op_plus
r_sizeof
(paren
r_struct
id|_fpstate
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|from-&gt;fpstate
op_ne
l_int|NULL
)paren
(brace
id|to-&gt;fpstate
op_assign
(paren
r_struct
id|_fpstate
op_star
)paren
(paren
id|to
op_plus
l_int|1
)paren
suffix:semicolon
)brace
)brace
DECL|function|sc_sigmask
r_int
r_int
op_star
id|sc_sigmask
c_func
(paren
r_void
op_star
id|sc_ptr
)paren
(brace
r_struct
id|sigcontext
op_star
id|sc
op_assign
id|sc_ptr
suffix:semicolon
r_return
op_amp
id|sc-&gt;oldmask
suffix:semicolon
)brace
DECL|function|sc_get_fpregs
r_int
id|sc_get_fpregs
c_func
(paren
r_int
r_int
id|buf
comma
r_void
op_star
id|sc_ptr
)paren
(brace
r_struct
id|sigcontext
op_star
id|sc
op_assign
id|sc_ptr
suffix:semicolon
r_struct
id|_fpstate
op_star
id|from
op_assign
id|sc-&gt;fpstate
comma
op_star
id|to
op_assign
(paren
r_struct
id|_fpstate
op_star
)paren
id|buf
suffix:semicolon
r_int
id|err
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|from
op_eq
l_int|NULL
)paren
(brace
id|err
op_or_assign
id|clear_user_proc
c_func
(paren
op_amp
id|to-&gt;cw
comma
r_sizeof
(paren
id|to-&gt;cw
)paren
)paren
suffix:semicolon
id|err
op_or_assign
id|clear_user_proc
c_func
(paren
op_amp
id|to-&gt;sw
comma
r_sizeof
(paren
id|to-&gt;sw
)paren
)paren
suffix:semicolon
id|err
op_or_assign
id|clear_user_proc
c_func
(paren
op_amp
id|to-&gt;tag
comma
r_sizeof
(paren
id|to-&gt;tag
)paren
)paren
suffix:semicolon
id|err
op_or_assign
id|clear_user_proc
c_func
(paren
op_amp
id|to-&gt;ipoff
comma
r_sizeof
(paren
id|to-&gt;ipoff
)paren
)paren
suffix:semicolon
id|err
op_or_assign
id|clear_user_proc
c_func
(paren
op_amp
id|to-&gt;cssel
comma
r_sizeof
(paren
id|to-&gt;cssel
)paren
)paren
suffix:semicolon
id|err
op_or_assign
id|clear_user_proc
c_func
(paren
op_amp
id|to-&gt;dataoff
comma
r_sizeof
(paren
id|to-&gt;dataoff
)paren
)paren
suffix:semicolon
id|err
op_or_assign
id|clear_user_proc
c_func
(paren
op_amp
id|to-&gt;datasel
comma
r_sizeof
(paren
id|to-&gt;datasel
)paren
)paren
suffix:semicolon
id|err
op_or_assign
id|clear_user_proc
c_func
(paren
op_amp
id|to-&gt;_st
comma
r_sizeof
(paren
id|to-&gt;_st
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|err
op_or_assign
id|copy_to_user_proc
c_func
(paren
op_amp
id|to-&gt;cw
comma
op_amp
id|from-&gt;cw
comma
r_sizeof
(paren
id|to-&gt;cw
)paren
)paren
suffix:semicolon
id|err
op_or_assign
id|copy_to_user_proc
c_func
(paren
op_amp
id|to-&gt;sw
comma
op_amp
id|from-&gt;sw
comma
r_sizeof
(paren
id|to-&gt;sw
)paren
)paren
suffix:semicolon
id|err
op_or_assign
id|copy_to_user_proc
c_func
(paren
op_amp
id|to-&gt;tag
comma
op_amp
id|from-&gt;tag
comma
r_sizeof
(paren
id|to-&gt;tag
)paren
)paren
suffix:semicolon
id|err
op_or_assign
id|copy_to_user_proc
c_func
(paren
op_amp
id|to-&gt;ipoff
comma
op_amp
id|from-&gt;ipoff
comma
r_sizeof
(paren
id|to-&gt;ipoff
)paren
)paren
suffix:semicolon
id|err
op_or_assign
id|copy_to_user_proc
c_func
(paren
op_amp
id|to-&gt;cssel
comma
op_amp
id|from-&gt;cssel
comma
r_sizeof
(paren
id|to-&gt;cssel
)paren
)paren
suffix:semicolon
id|err
op_or_assign
id|copy_to_user_proc
c_func
(paren
op_amp
id|to-&gt;dataoff
comma
op_amp
id|from-&gt;dataoff
comma
r_sizeof
(paren
id|to-&gt;dataoff
)paren
)paren
suffix:semicolon
id|err
op_or_assign
id|copy_to_user_proc
c_func
(paren
op_amp
id|to-&gt;datasel
comma
op_amp
id|from-&gt;datasel
comma
r_sizeof
(paren
id|to-&gt;datasel
)paren
)paren
suffix:semicolon
id|err
op_or_assign
id|copy_to_user_proc
c_func
(paren
id|to-&gt;_st
comma
id|from-&gt;_st
comma
r_sizeof
(paren
id|to-&gt;_st
)paren
)paren
suffix:semicolon
)brace
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
