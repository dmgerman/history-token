multiline_comment|/* &n; * Copyright (C) 2002 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#include &lt;stdlib.h&gt;
macro_line|#include &lt;asm/sigcontext.h&gt;
macro_line|#include &quot;kern_util.h&quot;
macro_line|#include &quot;sysdep/frame.h&quot;
DECL|function|copy_sc_from_user_tt
r_int
id|copy_sc_from_user_tt
c_func
(paren
r_void
op_star
id|to_ptr
comma
r_void
op_star
id|from_ptr
comma
r_void
op_star
id|data
)paren
(brace
r_struct
id|arch_frame_data
op_star
id|arch
op_assign
id|data
suffix:semicolon
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
r_struct
id|_fpstate
op_star
id|to_fp
comma
op_star
id|from_fp
suffix:semicolon
r_int
r_int
id|sigs
suffix:semicolon
r_int
id|err
suffix:semicolon
id|to_fp
op_assign
id|to-&gt;fpstate
suffix:semicolon
id|from_fp
op_assign
id|from-&gt;fpstate
suffix:semicolon
id|sigs
op_assign
id|to-&gt;oldmask
suffix:semicolon
id|err
op_assign
id|copy_from_user_proc
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
)paren
suffix:semicolon
id|to-&gt;oldmask
op_assign
id|sigs
suffix:semicolon
r_if
c_cond
(paren
id|to_fp
op_ne
l_int|NULL
)paren
(brace
id|err
op_or_assign
id|copy_from_user_proc
c_func
(paren
op_amp
id|to-&gt;fpstate
comma
op_amp
id|to_fp
comma
r_sizeof
(paren
id|to-&gt;fpstate
)paren
)paren
suffix:semicolon
id|err
op_or_assign
id|copy_from_user_proc
c_func
(paren
id|to_fp
comma
id|from_fp
comma
id|arch-&gt;fpstate_size
)paren
suffix:semicolon
)brace
r_return
id|err
suffix:semicolon
)brace
DECL|function|copy_sc_to_user_tt
r_int
id|copy_sc_to_user_tt
c_func
(paren
r_void
op_star
id|to_ptr
comma
r_void
op_star
id|from_ptr
comma
r_void
op_star
id|data
)paren
(brace
r_struct
id|arch_frame_data
op_star
id|arch
op_assign
id|data
suffix:semicolon
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
r_struct
id|_fpstate
op_star
id|to_fp
comma
op_star
id|from_fp
suffix:semicolon
r_int
id|err
suffix:semicolon
id|to_fp
op_assign
(paren
r_struct
id|_fpstate
op_star
)paren
(paren
(paren
r_int
r_int
)paren
id|to
op_plus
r_sizeof
(paren
op_star
id|to
)paren
)paren
suffix:semicolon
id|from_fp
op_assign
id|from-&gt;fpstate
suffix:semicolon
id|err
op_assign
id|copy_to_user_proc
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
)paren
suffix:semicolon
r_if
c_cond
(paren
id|from_fp
op_ne
l_int|NULL
)paren
(brace
id|err
op_or_assign
id|copy_to_user_proc
c_func
(paren
op_amp
id|to-&gt;fpstate
comma
op_amp
id|to_fp
comma
r_sizeof
(paren
id|to-&gt;fpstate
)paren
)paren
suffix:semicolon
id|err
op_or_assign
id|copy_to_user_proc
c_func
(paren
id|to_fp
comma
id|from_fp
comma
id|arch-&gt;fpstate_size
)paren
suffix:semicolon
)brace
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
