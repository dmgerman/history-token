multiline_comment|/* &n; * Copyright (C) 2001 Chris Emerson (cemerson@chiark.greenend.org.uk)&n; * Copyright (C) 2001 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#include &lt;setjmp.h&gt;
macro_line|#include &lt;string.h&gt;
macro_line|#include &quot;user_util.h&quot;
macro_line|#include &quot;uml_uaccess.h&quot;
macro_line|#include &quot;task.h&quot;
macro_line|#include &quot;kern_util.h&quot;
DECL|function|__do_copy_from_user
r_int
id|__do_copy_from_user
c_func
(paren
r_void
op_star
id|to
comma
r_const
r_void
op_star
id|from
comma
r_int
id|n
comma
r_void
op_star
op_star
id|fault_addr
comma
r_void
op_star
op_star
id|fault_catcher
)paren
(brace
r_struct
id|tt_regs
id|save
op_assign
id|TASK_REGS
c_func
(paren
id|get_current
c_func
(paren
)paren
)paren
op_member_access_from_pointer
id|tt
suffix:semicolon
r_int
r_int
id|fault
suffix:semicolon
r_int
id|faulted
suffix:semicolon
id|fault
op_assign
id|__do_user_copy
c_func
(paren
id|to
comma
id|from
comma
id|n
comma
id|fault_addr
comma
id|fault_catcher
comma
id|__do_copy
comma
op_amp
id|faulted
)paren
suffix:semicolon
id|TASK_REGS
c_func
(paren
id|get_current
c_func
(paren
)paren
)paren
op_member_access_from_pointer
id|tt
op_assign
id|save
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|faulted
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
r_else
r_return
id|n
op_minus
(paren
id|fault
op_minus
(paren
r_int
r_int
)paren
id|from
)paren
suffix:semicolon
)brace
DECL|function|__do_strncpy
r_static
r_void
id|__do_strncpy
c_func
(paren
r_void
op_star
id|dst
comma
r_const
r_void
op_star
id|src
comma
r_int
id|count
)paren
(brace
id|strncpy
c_func
(paren
id|dst
comma
id|src
comma
id|count
)paren
suffix:semicolon
)brace
DECL|function|__do_strncpy_from_user
r_int
id|__do_strncpy_from_user
c_func
(paren
r_char
op_star
id|dst
comma
r_const
r_char
op_star
id|src
comma
r_int
r_int
id|count
comma
r_void
op_star
op_star
id|fault_addr
comma
r_void
op_star
op_star
id|fault_catcher
)paren
(brace
r_struct
id|tt_regs
id|save
op_assign
id|TASK_REGS
c_func
(paren
id|get_current
c_func
(paren
)paren
)paren
op_member_access_from_pointer
id|tt
suffix:semicolon
r_int
r_int
id|fault
suffix:semicolon
r_int
id|faulted
suffix:semicolon
id|fault
op_assign
id|__do_user_copy
c_func
(paren
id|dst
comma
id|src
comma
id|count
comma
id|fault_addr
comma
id|fault_catcher
comma
id|__do_strncpy
comma
op_amp
id|faulted
)paren
suffix:semicolon
id|TASK_REGS
c_func
(paren
id|get_current
c_func
(paren
)paren
)paren
op_member_access_from_pointer
id|tt
op_assign
id|save
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|faulted
)paren
(brace
r_return
id|strlen
c_func
(paren
id|dst
)paren
suffix:semicolon
)brace
r_else
r_return
op_minus
l_int|1
suffix:semicolon
)brace
DECL|function|__do_clear
r_static
r_void
id|__do_clear
c_func
(paren
r_void
op_star
id|to
comma
r_const
r_void
op_star
id|from
comma
r_int
id|n
)paren
(brace
id|memset
c_func
(paren
id|to
comma
l_int|0
comma
id|n
)paren
suffix:semicolon
)brace
DECL|function|__do_clear_user
r_int
id|__do_clear_user
c_func
(paren
r_void
op_star
id|mem
comma
r_int
r_int
id|len
comma
r_void
op_star
op_star
id|fault_addr
comma
r_void
op_star
op_star
id|fault_catcher
)paren
(brace
r_struct
id|tt_regs
id|save
op_assign
id|TASK_REGS
c_func
(paren
id|get_current
c_func
(paren
)paren
)paren
op_member_access_from_pointer
id|tt
suffix:semicolon
r_int
r_int
id|fault
suffix:semicolon
r_int
id|faulted
suffix:semicolon
id|fault
op_assign
id|__do_user_copy
c_func
(paren
id|mem
comma
l_int|NULL
comma
id|len
comma
id|fault_addr
comma
id|fault_catcher
comma
id|__do_clear
comma
op_amp
id|faulted
)paren
suffix:semicolon
id|TASK_REGS
c_func
(paren
id|get_current
c_func
(paren
)paren
)paren
op_member_access_from_pointer
id|tt
op_assign
id|save
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|faulted
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
r_else
r_return
id|len
op_minus
(paren
id|fault
op_minus
(paren
r_int
r_int
)paren
id|mem
)paren
suffix:semicolon
)brace
DECL|function|__do_strnlen_user
r_int
id|__do_strnlen_user
c_func
(paren
r_const
r_char
op_star
id|str
comma
r_int
r_int
id|n
comma
r_void
op_star
op_star
id|fault_addr
comma
r_void
op_star
op_star
id|fault_catcher
)paren
(brace
r_struct
id|tt_regs
id|save
op_assign
id|TASK_REGS
c_func
(paren
id|get_current
c_func
(paren
)paren
)paren
op_member_access_from_pointer
id|tt
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_int
r_int
op_star
id|faddrp
op_assign
(paren
r_int
r_int
op_star
)paren
id|fault_addr
suffix:semicolon
id|sigjmp_buf
id|jbuf
suffix:semicolon
op_star
id|fault_catcher
op_assign
op_amp
id|jbuf
suffix:semicolon
r_if
c_cond
(paren
id|sigsetjmp
c_func
(paren
id|jbuf
comma
l_int|1
)paren
op_eq
l_int|0
)paren
(brace
id|ret
op_assign
id|strlen
c_func
(paren
id|str
)paren
op_plus
l_int|1
suffix:semicolon
)brace
r_else
id|ret
op_assign
op_star
id|faddrp
op_minus
(paren
r_int
r_int
)paren
id|str
suffix:semicolon
op_star
id|fault_addr
op_assign
l_int|NULL
suffix:semicolon
op_star
id|fault_catcher
op_assign
l_int|NULL
suffix:semicolon
id|TASK_REGS
c_func
(paren
id|get_current
c_func
(paren
)paren
)paren
op_member_access_from_pointer
id|tt
op_assign
id|save
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
